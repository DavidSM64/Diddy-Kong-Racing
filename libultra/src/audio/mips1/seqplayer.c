/*====================================================================
 * seqplayer.c
 *
 * Copyright 1993, Silicon Graphics, Inc.
 * All Rights Reserved.
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/
/*
 * Notes:
 *
 * Controller Numbers:
 *      1       Modulation
 *      7       Volume
 *      10      Pan
 *      11      Expression
 *      64      Sustain
 *      121     Reset All Controllers
 *      123     All Notes Off
 *
 * Registered Parameters
 *      0       Pitch Bend Sensitivity
 *      1       Fine Tuning
 *      2       Coarse Tuning
 */

#include <libaudio.h>
#include <os_internal.h>
#include <ultraerror.h>
#include <assert.h>
#include "seqp.h"
#include "seq.h"

#if defined(__sgi)
#define stubbed_printf
#else
#define stubbed_printf(...)
#endif

// TODO: this comes from a header
#ident "$Revision: 1.17 $"


static  ALMicroTime     __seqpVoiceHandler(void *node);
static  void            __handleMIDIMsg(ALSeqPlayer *seqp, ALEvent *event);
static  void            __handleMetaMsg(ALSeqPlayer *seqp, ALEvent *event);
static	void		__handleNextSeqEvent(ALSeqPlayer *seqp);

void alSeqpNew(ALSeqPlayer *seqp, ALSeqpConfig *c) { }

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
    
    /*
     * we could use doubly linked lists here and save some code and
     * execution time, but time spent here in negligible, so it won't
     * make much difference.
     */
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
#ifdef _DEBUG
    __osError(ERR_ALSEQPUNMAP, 1, voice);
#endif    
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

#define _AlChanState ALChanState_Custom

ALSound *__lookupSoundQuick(ALSeqPlayer *seqp, u8 key, u8 vel, u8 chan)
{
    ALInstrument *inst = ((_AlChanState*)seqp->chanState)[chan].instrument;
    s32 l = 1;
    s32 r = inst->soundCount;
    s32 i;
    ALKeyMap *keymap;
#if BUILD_VERSION < VERSION_J
#line 885
#endif
    assert(inst != NULL);       /* sct 10/31/95 - If inst is NULL, then the seqp probably wasn't setup correctly. */

    
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


/*
 * __vsVol calculates the target volume for the voice based on the
 * note on velocity, envelope, sampleVolume and controller.
 */
s16 __vsVol(ALVoiceState *vs, ALSeqPlayer *seqp) 
{

    u32     t1,t2;

    t1 = (vs->tremelo*vs->velocity*vs->envGain) >> 6;
    t2 = (vs->sound->sampleVolume*seqp->vol*
          ((_AlChanState*)seqp->chanState)[vs->channel].vol) >> 14;
    t1 *= t2;
    t1 >>= 15;
    
    return( (s16)t1 );
    
}

ALMicroTime __vsDelta(ALVoiceState *vs, ALMicroTime t)
{
    /*
     * If we are interrupting a previously set envelope segment, we
     * need to recalculate the segment end time given the current
     * time. Note: this routine assumes that the voice is currently
     * playing.
     */
    
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

    tmp = ((_AlChanState*)seqp->chanState)[vs->channel].pan - AL_PAN_CENTER +
        vs->sound->samplePan;
    tmp = MAX(tmp, AL_PAN_LEFT);
    tmp = MIN(tmp, AL_PAN_RIGHT);

    return (ALPan) tmp;
}

#ifdef IMPLEMENTED

s32     seqpGetVoices(SEQP *seqp);
s32     seqpSetVoices(SEQP *seqp, s32 numvoices);

u16	seqpGetChannelMask(SEQP *seqp);
s32	seqpSetChannelMask(SEQP *seqp, u16 bitmask);

#endif

void __seqpReleaseVoice(ALSeqPlayer *seqp, ALVoice *voice,
                        ALMicroTime deltaTime)
{
    ALEvent             evt;
    ALVoiceState	*vs = (ALVoiceState *)voice->clientPrivate;

    /*
     * if in attack phase, remove all pending volume
     * events for this voice from the queue
     */

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

    alSynSetPriority(seqp->drvr, voice, 0); /* make candidate for stealing */
    alSynSetVol(seqp->drvr, voice, 0, deltaTime);
    evt.type  = AL_NOTE_END_EVT;
    evt.msg.note.voice = voice;
    
    alEvtqPostEvent(&seqp->evtq, &evt, deltaTime);
}



/*
  This special purpose routine is called only when processing
  a stopping event in order to properly kill all active voices.
  
  The routine searches through the seqp's event queue for an
  AL_NOTE_END_EVT for the given voice.  If the event's execution
  time is greater than kill time, it removes the event from the
  event queue and returns true that it needs to kill the voice.
  Otherwise, if the event's time is less than the kill time, it
  returns false that the voice needs to be killed.

  sct 1/3/96
*/

#define VOICENEEDSNOTEKILL_DEBUG	_DEBUG_INTERNAL&&0	/* For debugging voiceNeedsNoteKill routine. */

char __voiceNeedsNoteKill (ALSeqPlayer *seqp, ALVoice *voice, ALMicroTime killTime)
{
    ALLink              *thisNode;
    ALLink              *nextNode;
    ALEventListItem     *thisItem;
    ALMicroTime		itemTime = 0;
    char		needsNoteKill = TRUE;

#if VOICENEEDSNOTEKILL_DEBUG
    alEvtqPrintAllocEvts (&seqp->evtq);
#endif

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

#if VOICENEEDSNOTEKILL_DEBUG 
    if (thisNode)
	osSyncPrintf("vox 0x%0x: end time %d  kill time %d\n\n", voice, itemTime, killTime);
    else
	osSyncPrintf("vox 0x%0x: not found\n\n", voice);

    alEvtqPrintAllocEvts (&seqp->evtq);
#endif

   return needsNoteKill;
}



    
void __initFromBank(ALSeqPlayer *seqp, ALBank *b)
{
    /*
     * init the chanState with the default instrument
     */
    s32 i;    
    ALInstrument *inst = 0;
    
    /* set to the first available instrument. */
    for(i = 0; !inst ; i++)
      inst = b->instArray[i];
    
    /* sct 11/6/95 - Setup the channel state for the given instrument. */
    /* There is some wasted effort here since both calls the same state vars */
    /* but it's safer. */
    for (i = 0; i < seqp->maxChannels; i++) {
      __resetPerfChanState(seqp, i);
      __setInstChanState(seqp, inst, i);
    }

    if (b->percussion) {
      __resetPerfChanState(seqp, i);
      __setInstChanState(seqp, b->percussion, 9);
    }
}

/*
  sct 11/6/95 - Call this whenever a new instrument gets assigned to a channel
  such as when changing banks or in response to a MIDI program change event.
  Currently also gets called when changing sequences.
*/
void __setInstChanState(ALSeqPlayer *seqp, ALInstrument *inst, s32 chan)
{
    ((_AlChanState*)seqp->chanState)[chan].instrument = inst;
    ((_AlChanState*)seqp->chanState)[chan].pan = inst->pan;
    ((_AlChanState*)seqp->chanState)[chan].vol = inst->volume;
    ((_AlChanState*)seqp->chanState)[chan].priority = inst->priority;
    ((_AlChanState*)seqp->chanState)[chan].bendRange = inst->bendRange;
}


/*
  sct 11/6/95 -- Call this whenever a new sequence is to be played or when
  initializing a sequence player.
*/
void __resetPerfChanState(ALSeqPlayer *seqp, s32 chan) 
{
  ((_AlChanState*)seqp->chanState)[chan].fxId = AL_FX_NONE;
  ((_AlChanState*)seqp->chanState)[chan].fxmix = AL_DEFAULT_FXMIX;
  ((_AlChanState*)seqp->chanState)[chan].pan = AL_PAN_CENTER;
  ((_AlChanState*)seqp->chanState)[chan].vol = AL_VOL_FULL;
  ((_AlChanState*)seqp->chanState)[chan].fade = AL_VOL_FULL;
  ((_AlChanState*)seqp->chanState)[chan].priority = AL_DEFAULT_PRIORITY;
  ((_AlChanState*)seqp->chanState)[chan].sustain = 0;
  ((_AlChanState*)seqp->chanState)[chan].bendRange = 200;
  ((_AlChanState*)seqp->chanState)[chan].pitchBend = 1.0f;
}


/*
  sct 11/6/95 - Called only when creating a new sequence player.
*/
void __initChanState(ALSeqPlayer *seqp) 
{
    int i;
    
    for (i = 0; i < seqp->maxChannels; i++)
    {
        ((_AlChanState*)seqp->chanState)[i].instrument = 0;
	__resetPerfChanState (seqp, i);
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
                (*seqp->stopOsc)(thisNode->evt.msg.osc.oscState);
                alUnlink((ALLink*)thisNode);
                if(nextNode)
                    nextNode->delta += thisNode->delta;
                alLink((ALLink*)thisNode, &seqp->evtq.freeList);
                if(evtType == AL_TREM_OSC_EVT)
                    vs->flags = vs->flags & 0xFE;
                else /* must be a AL_VIB_OSC_EVT */
                    vs->flags = vs->flags & 0xFD;
                if(!vs->flags)
                    return;  /* there should be no more events */
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
