/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8000A710 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

void __setInstChanState(ALSeqPlayer *seqp, ALInstrument *inst, s32 chan);
void __resetPerfChanState(ALSeqPlayer *seqp, s32 chan) ;

UNUSED void dummy_8000A710(UNUSED s32 arg0, UNUSED s32 arg1) {
}

ALVoiceState *__mapVoice(ALSeqPlayer *seqp, u8 key, u8 vel, u8 channel)
{
    ALVoiceState  *vs = seqp->vFreeList;
    
    if(seqp->voiceLimit < seqp->mappedVoices) {
        stubbed_printf("Exceeded voice limit of %d (%d)\n", seqp->voiceLimit, seqp->mappedVoices);
        return NULL;
    }

    if (vs) {

        seqp->vFreeList = vs->next;

        vs->next = 0;
        
        if (!seqp->vAllocHead)
            seqp->vAllocHead = vs;
        else
            seqp->vAllocTail->next = vs;
        
        seqp->vAllocTail = vs;

        vs->channel             = channel;
        vs->key                 = key;
        vs->velocity            = vel;
        vs->voice.clientPrivate = vs;
        seqp->mappedVoices++;
    }
    
    return vs;
}

void __unmapVoice(ALSeqPlayer *seqp, ALVoice *voice) 
{
    ALVoiceState *prev = 0;
    ALVoiceState *vs;

    for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
        if (&vs->voice == voice) {
            if (prev)
                prev->next = vs->next;
            else
                seqp->vAllocHead = vs->next;
            
            if (vs == seqp->vAllocTail) {
                seqp->vAllocTail = prev;
            }

            vs->next = seqp->vFreeList;
            seqp->vFreeList = vs;
            seqp->mappedVoices--;
            return;

        }
        prev = vs;
    }
}

ALVoiceState *__lookupVoice(ALSeqPlayer *seqp, u8 key, u8 channel)
{
    ALVoiceState  *vs;

    for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
        if ((vs->key == key) && (vs->channel == channel) &&
            (vs->phase != AL_PHASE_RELEASE) && (vs->phase != AL_PHASE_SUSTREL))
            return vs;
    }
    
    return 0;
}

ALSound *__lookupSoundQuick(ALSeqPlayer *seqp, u8 key, u8 vel, u8 chan)
{
    ALInstrument *inst = ((ALChanState_Custom*)seqp->chanState)[chan].instrument;
    s32 l = 1;
    s32 r = inst->soundCount;
    s32 i;
    ALKeyMap *keymap;
    
    while (r >= l) {
        i = (l+r)/2;

        keymap = inst->soundArray[i-1]->keyMap;

        if ((key >= keymap->keyMin) && (key <= keymap->keyMax) &&
            (vel >= keymap->velocityMin) && (vel <= keymap->velocityMax)) {
            return inst->soundArray[i-1];
        } else if ((key < keymap->keyMin) ||
                   ((vel < keymap->velocityMin) && (key <= keymap->keyMax))) {
            r = i - 1;
        } else {
            l = i + 1;
        }
    }
    
    return 0;
}

s16 __vsVol(ALVoiceState *vs, ALSeqPlayer *seqp) 
{
    u32 t1, t2;

    t1 = (vs->tremelo*vs->velocity*vs->envGain) >> 6;
    t2 = (vs->sound->sampleVolume*seqp->vol * ((ALChanState_Custom*)seqp->chanState)[vs->channel].vol) >> 14;

    t1 *= t2;
    t1 >>= 15;
    
    return((s16)t1);
}

ALMicroTime __vsDelta(ALVoiceState *vs, ALMicroTime t)
{
    s32 delta = vs->envEndTime - t;
    
    if (delta >= 0) {
        return delta;
    } else {
        return AL_GAIN_CHANGE_TIME;
    }
}

ALPan __vsPan(ALVoiceState *vs, ALSeqPlayer *seqp) 
{
    s32 tmp;

    tmp = ((ALChanState_Custom*)seqp->chanState)[vs->channel].pan - AL_PAN_CENTER + vs->sound->samplePan;
    tmp = MAX(tmp, AL_PAN_LEFT);
    tmp = MIN(tmp, AL_PAN_RIGHT);

    return (ALPan) tmp;
}

void __seqpReleaseVoice(ALSeqPlayer *seqp, ALVoice *voice, ALMicroTime deltaTime)
{
    ALEvent             evt;
    ALVoiceState	*vs = (ALVoiceState *)voice->clientPrivate;

    if (vs->envPhase == AL_PHASE_ATTACK) {
	ALLink              *thisNode;
	ALLink              *nextNode;
	ALEventListItem     *thisItem, *nextItem;

	thisNode = seqp->evtq.allocList.next;
	while( thisNode != 0 ) {
	    nextNode = thisNode->next;
	    thisItem = (ALEventListItem *)thisNode;
	    nextItem = (ALEventListItem *)nextNode;
	    if (thisItem->evt.type == AL_SEQP_ENV_EVT) {
		if(thisItem->evt.msg.vol.voice == voice) {
		    if( nextItem )
			nextItem->delta += thisItem->delta;
		    alUnlink(thisNode);
		    alLink(thisNode, &seqp->evtq.freeList);
		}
	    }
	    thisNode = nextNode;
	}
    }
    
    vs->velocity = 0;
    vs->envPhase = AL_PHASE_RELEASE;
    vs->envGain  = 0;
    vs->envEndTime = seqp->curTime + deltaTime;

    alSynSetPriority(seqp->drvr, voice, 0);
    alSynSetVol(seqp->drvr, voice, 0, deltaTime);
    evt.type  = AL_NOTE_END_EVT;
    evt.msg.note.voice = voice;
    
    alEvtqPostEvent(&seqp->evtq, &evt, deltaTime);
}

u8 __voiceNeedsNoteKill (ALSeqPlayer *seqp, ALVoice *voice, ALMicroTime killTime)
{
    ALLink              *thisNode;
    ALLink              *nextNode;
    ALEventListItem     *thisItem;
    ALMicroTime		itemTime = 0;
    u8		needsNoteKill = TRUE;

    thisNode = seqp->evtq.allocList.next;
    while (thisNode != 0)
    {
	nextNode = thisNode->next;
	thisItem = (ALEventListItem *)thisNode;
	itemTime += thisItem->delta;

	if (thisItem->evt.type == AL_NOTE_END_EVT)
	{
	    if (thisItem->evt.msg.note.voice == voice)
	    {
		if (itemTime > killTime)
		{
		    if ((ALEventListItem *)nextNode)
			((ALEventListItem *)nextNode)->delta += thisItem->delta;
		    alUnlink(thisNode);
		    alLink(thisNode, &seqp->evtq.freeList);
		}
		else
		    needsNoteKill = FALSE;
		break;
	    }
	}
	thisNode = nextNode;
    }

   return needsNoteKill;
}

void __initFromBank(ALSeqPlayer *seqp, ALBank *b)
{
    s32 i;    
    ALInstrument *inst = 0;
    
    for(i = 0; !inst ; i++)
      inst = b->instArray[i];
    
    for (i = 0; i < seqp->maxChannels; i++) {
      __resetPerfChanState(seqp, i);
      __setInstChanState(seqp, inst, i);
    }

    if (b->percussion) {
      __resetPerfChanState(seqp, i);
      __setInstChanState(seqp, b->percussion, 9);
    }
}

void __setInstChanState(ALSeqPlayer *seqp, ALInstrument *inst, s32 chan)
{
    ((ALChanState_Custom*)seqp->chanState)[chan].instrument = inst;
    ((ALChanState_Custom*)seqp->chanState)[chan].pan = inst->pan;
    ((ALChanState_Custom*)seqp->chanState)[chan].vol = inst->volume;
    ((ALChanState_Custom*)seqp->chanState)[chan].priority = inst->priority;
    ((ALChanState_Custom*)seqp->chanState)[chan].bendRange = inst->bendRange;
}

void __resetPerfChanState(ALSeqPlayer *seqp, s32 chan) 
{
  ((ALChanState_Custom*)seqp->chanState)[chan].fxId = AL_FX_NONE;
  ((ALChanState_Custom*)seqp->chanState)[chan].fxmix = AL_DEFAULT_FXMIX;
  ((ALChanState_Custom*)seqp->chanState)[chan].pan = AL_PAN_CENTER;
  ((ALChanState_Custom*)seqp->chanState)[chan].vol = AL_VOL_FULL;
  ((ALChanState_Custom*)seqp->chanState)[chan].fade = AL_VOL_FULL;
  ((ALChanState_Custom*)seqp->chanState)[chan].priority = AL_DEFAULT_PRIORITY;
  ((ALChanState_Custom*)seqp->chanState)[chan].sustain = 0;
  ((ALChanState_Custom*)seqp->chanState)[chan].bendRange = 200;
  ((ALChanState_Custom*)seqp->chanState)[chan].pitchBend = 1.0f;
}

void __initChanState(ALSeqPlayer *seqp) 
{
    int i;
    
    for (i = 0; i < seqp->maxChannels; i++)
    {
        ((ALChanState_Custom*)seqp->chanState)[i].instrument = 0;
        __resetPerfChanState(seqp, i);
    }
}

void __seqpStopOsc(ALSeqPlayer *seqp, ALVoiceState *vs)
{
    ALEventListItem  *thisNode,*nextNode;
    s16              evtType;
    
    thisNode = (ALEventListItem*)seqp->evtq.allocList.next;
    while(thisNode)
    {
        nextNode = (ALEventListItem*)thisNode->node.next;
        evtType = thisNode->evt.type;
        if(evtType == AL_TREM_OSC_EVT || evtType == AL_VIB_OSC_EVT)
        {
            if(thisNode->evt.msg.osc.vs == vs)
            {
                (*(seqp->stopOsc))(thisNode->evt.msg.osc.oscState);
                alUnlink((ALLink*)thisNode);
                if(nextNode)
                    nextNode->delta += thisNode->delta;
                alLink((ALLink*)thisNode, &seqp->evtq.freeList);
                if(evtType == AL_TREM_OSC_EVT)
                    vs->flags = vs->flags & 0xFE;
                else
                    vs->flags = vs->flags & 0xFD;
                if(!vs->flags)
                    return;
            }
        }
        
        thisNode = nextNode;
    }
}

/**
 * The voice limit bytes seem to be unique to this game.
 */
void set_voice_limit(ALSeqPlayer *seqp, s8 voiceLimit) {
    seqp->voiceLimit = voiceLimit;
}
