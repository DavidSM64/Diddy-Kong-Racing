/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80062290 */

#include "PR/os_exception.h"
#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "seqp.h"
#include "cseqp.h"
#include "cseq.h"

/************ .rodata ************/

const char D_800E6C20[] = "CSP: oh oh \n";

/*********************************/

void __CSPPostNextSeqEvent(ALCSPlayer *seqp);
void __CSPHandleNextSeqEvent(ALCSPlayer *seqp);
void __CSPHandleMetaMsg(ALCSPlayer *seqp, ALEvent *event);
void  __CSPRepostEvent(ALEventQueue *evtq, ALEventListItem *item);
void __setUsptFromTempo(ALCSPlayer *seqp, f32 tempo);
u32 __alCSeqGetTrackEvent(ALCSeq *seq, ALEvent *event); 
void __CSPHandleMIDIMsg(ALCSPlayer *seqp, ALEvent *event);
ALMicroTime __CSPVoiceHandler(void *node);

/*
 * Sequence Player public functions
 */
void alCSPNew(ALCSPlayer *seqp, ALSeqpConfig *c)
{
    s32                 i;
    ALEventListItem     *items;
    ALVoiceState        *vs;
    ALVoiceState        *voices;
    
    ALHeap *hp = c->heap;    

    /*
     * initialize member variables
     */
    seqp->bank          = NULL;
    seqp->target        = NULL;
    seqp->drvr          = &alGlobals->drvr;
    seqp->chanMask      = 0xffff;
    seqp->uspt          = 488;
    seqp->nextDelta     = 0;
    seqp->state         = AL_STOPPED;
    seqp->vol           = 0x7FFF;              /* full volume  */
    seqp->frameTime     = AL_USEC_PER_FRAME; /* should get this from driver */
    seqp->curTime       = 0;
    seqp->initOsc       = c->initOsc;
    seqp->updateOsc     = c->updateOsc;
    seqp->stopOsc       = c->stopOsc;
    seqp->unk71         = 0;
    seqp->unk70         = c->unknown_0x10;
    
    seqp->nextEvent.type = AL_SEQP_API_EVT;	/* this will start the voice handler "spinning" */
    
    /*
     * init the channel state
     */
    seqp->maxChannels = c->maxChannels;
    seqp->chanState = alHeapAlloc(hp, c->maxChannels, sizeof(ALChanState)+4); //TODO: ALChanState likely has some added values as well
    __initChanState((ALCSPlayer*)seqp);	/* sct 11/6/95 */
    
    /*
     * init the voice state array
     */
    voices = alHeapAlloc(hp, c->maxVoices, sizeof(ALVoiceState));
    seqp->vFreeList = 0;
    for (i = 0; i < c->maxVoices; i++) {
        vs = &voices[i];
        vs->next = seqp->vFreeList;
        seqp->vFreeList = vs;        
    }
    
    seqp->vAllocHead = 0;
    seqp->vAllocTail = 0;    
        
    /*
     * init the event queue
     */
    items = alHeapAlloc(hp, c->maxEvents, sizeof(ALEventListItem));
    alEvtqNew(&seqp->evtq, items, c->maxEvents);

    
    /*
     * add ourselves to the driver
     */
    seqp->node.next       = NULL;
    seqp->node.handler    = __CSPVoiceHandler;
    seqp->node.clientData = seqp;
    alSynAddPlayer(&alGlobals->drvr, &seqp->node);  
}

/*************************************************************
 * private routines or driver callback routines
 *************************************************************/
ALMicroTime __CSPVoiceHandler(void *node)
{
    ALCSPlayer_Custom *seqp = (ALCSPlayer_Custom *) node;
    ALEvent         evt;
    ALVoice         *voice;
    ALMicroTime     delta;
    ALVoiceState	*vs;
    void            *oscState;
    f32             oscValue;
    u8              chan;

    do {
        switch (seqp->nextEvent.type)
        {
	case (AL_SEQ_REF_EVT):
	    __CSPHandleNextSeqEvent(seqp);
	    break;

	case (AL_SEQP_API_EVT):
	    evt.type = AL_SEQP_API_EVT;
	    alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, seqp->frameTime);
	    break;

	case (AL_NOTE_END_EVT):
	    voice = seqp->nextEvent.msg.note.voice;

	    alSynStopVoice(seqp->drvr, voice);
	    alSynFreeVoice(seqp->drvr, voice);
	    vs = (ALVoiceState *)voice->clientPrivate;
	    if(vs->flags)
		__seqpStopOsc((ALSeqPlayer*)seqp,vs);
	    __unmapVoice((ALSeqPlayer*)seqp, voice); 
	    break;

	case (AL_SEQP_ENV_EVT):
	    voice = seqp->nextEvent.msg.vol.voice;
	    vs = (ALVoiceState *)voice->clientPrivate;

	    if(vs->envPhase == AL_PHASE_ATTACK)
		vs->envPhase = AL_PHASE_DECAY;

	    delta = seqp->nextEvent.msg.vol.delta;
	    vs->envEndTime = seqp->curTime + delta;
	    vs->envGain = seqp->nextEvent.msg.vol.vol;
	    alSynSetVol(seqp->drvr, voice, __vsVol(vs, (ALSeqPlayer*)seqp), delta);
	    break;
                
	case (AL_TREM_OSC_EVT):
	    vs = seqp->nextEvent.msg.osc.vs;
	    oscState = seqp->nextEvent.msg.osc.oscState;
	    delta = (*seqp->updateOsc)(oscState,&oscValue);
	    vs->tremelo = (u8)oscValue;
	    alSynSetVol(seqp->drvr, &vs->voice, __vsVol(vs,(ALSeqPlayer*)seqp),
			__vsDelta(vs,seqp->curTime));
	    evt.type = AL_TREM_OSC_EVT;
	    evt.msg.osc.vs = vs;
	    evt.msg.osc.oscState = oscState;
	    alEvtqPostEvent(&seqp->evtq, &evt, delta);
	    break;
                
	case (AL_VIB_OSC_EVT):
	    vs = seqp->nextEvent.msg.osc.vs;
	    oscState = seqp->nextEvent.msg.osc.oscState;
	    chan = seqp->nextEvent.msg.osc.chan;
	    delta = (*seqp->updateOsc)(oscState,&oscValue);
	    vs->vibrato = oscValue;
	    alSynSetPitch(seqp->drvr, &vs->voice, vs->pitch * vs->vibrato
			  * seqp->chanState[chan].pitchBend);
	    evt.type = AL_VIB_OSC_EVT;
	    evt.msg.osc.vs = vs;
	    evt.msg.osc.oscState = oscState;
	    evt.msg.osc.chan = chan;
	    alEvtqPostEvent(&seqp->evtq, &evt, delta);
	    break;

	case (AL_SEQP_MIDI_EVT):
	case (AL_CSP_NOTEOFF_EVT):			/* nextEvent is a note off midi message */
	    __CSPHandleMIDIMsg(seqp, &seqp->nextEvent);
	    break;

	case (AL_SEQP_META_EVT):
	    __CSPHandleMetaMsg(seqp, &seqp->nextEvent);
	    break;

	case (AL_SEQP_VOL_EVT):
	    seqp->vol =  seqp->nextEvent.msg.spvol.vol;
	    for (vs = seqp->vAllocHead; vs != 0; vs = vs->next)
	    {
		alSynSetVol(seqp->drvr, &vs->voice,
                            __vsVol(vs, (ALSeqPlayer*)seqp),
                            __vsDelta(vs, seqp->curTime));
	    }
	    break;

	case (AL_SEQP_PLAY_EVT):
	    if (seqp->state != AL_PLAYING)
	    {
		seqp->state = AL_PLAYING;
		__CSPPostNextSeqEvent(seqp);	/* seqp must be AL_PLAYING before we call this routine. */
	    }
	    break;

	case (AL_SEQP_STOP_EVT):
	    if ( seqp->state == AL_STOPPING )
	    {
        seqp->chanMask = 0xFFFF;
        for (chan = 0; chan < seqp->maxChannels; chan++)
        {
            seqp->chanState[chan].unk10 = 0x7F;
            seqp->chanState[chan].vol = seqp->chanState[chan].unk11;
        }

		for (vs = seqp->vAllocHead; vs != 0; vs = seqp->vAllocHead)
		{
#ifdef _DEBUG
                    __osError(ERR_ALCSPVNOTFREE, 2, vs->channel, vs->key);
#endif                    
		    alSynStopVoice(seqp->drvr, &vs->voice);
		    alSynFreeVoice(seqp->drvr, &vs->voice);
		    if(vs->flags)
			__seqpStopOsc((ALSeqPlayer*)seqp,vs);
		    __unmapVoice((ALSeqPlayer*)seqp, &vs->voice); 
		}
		seqp->state = AL_STOPPED;

		/* alEvtqFlush(&seqp->evtq); - Don't flush event queue
                   anymore. */
		/* sct 1/3/96 - Don't overwrite nextEvent with
		   AL_SEQP_API_EVT or set nextDelta to
		   AL_USEC_PER_FRAME since we're not stopping event
		   processing. */
		/* sct 1/3/96 - Don't return here since we keep
                   processing events as usual. */
	    }
	    break;

	case (AL_SEQP_STOPPING_EVT):
	    if (seqp->state == AL_PLAYING)
	    {
		/* sct 12/29/95 - Remove events associated with the
                 * stopping sequence.  For compact sequence player,
                 * also remove all queued note off events since they
                 * are not contained in a compact sequence but are
                 * generated in response to note ons.  Note that
                 * flushing AL_SEQP_MIDI_EVTs may flush events that
                 * were posted after the call to alSeqpStop, so the
                 * application must queue these events either when
                 * the player is fully stopped, or when it is
                 * playing. */
		alEvtqFlushType(&seqp->evtq, AL_SEQ_REF_EVT);
		alEvtqFlushType(&seqp->evtq, AL_CSP_NOTEOFF_EVT);
		alEvtqFlushType(&seqp->evtq, AL_SEQP_MIDI_EVT);

		/* sct 1/3/96 - Check to see which voices need to be
                   killed and release them. */
		/* Unkilled voices should have note end events
                   occurring prior to KILL_TIME. */
		for (vs = seqp->vAllocHead; vs != 0; vs = vs->next)
		{
		    if (__voiceNeedsNoteKill ((ALSeqPlayer*)seqp, &vs->voice, KILL_TIME))
			__seqpReleaseVoice((ALSeqPlayer*)seqp, &vs->voice, KILL_TIME);
		}

		seqp->state = AL_STOPPING;
		evt.type = AL_SEQP_STOP_EVT;
		alEvtqPostEvent(&seqp->evtq, &evt, AL_EVTQ_END);
	    }
	    break;

	case (AL_SEQP_PRIORITY_EVT):
	    chan = seqp->nextEvent.msg.sppriority.chan;
	    seqp->chanState[chan].priority = seqp->nextEvent.msg.sppriority.priority;
	    break;

	case (AL_SEQP_SEQ_EVT):

#ifdef _DEBUG
	    assert(seqp->state != AL_PLAYING);	/* Must be done playing to change sequences. */
#endif

	    seqp->target = seqp->nextEvent.msg.spseq.seq;
	    //__setUsptFromTempo (seqp, 500000.0);
	    if (seqp->bank)
		__initFromBank((ALSeqPlayer *)seqp, seqp->bank);
	    break;

	case (AL_SEQP_BANK_EVT):

#ifdef _DEBUG
	    assert(seqp->state == AL_STOPPED);	/* Must be fully stopped to change banks. */
#endif

	    seqp->bank = seqp->nextEvent.msg.spbank.bank;
	    __initFromBank((ALSeqPlayer *)seqp, seqp->bank);
	    break;

	    /* sct 11/6/95 - these events should now be handled by __CSPHandleNextSeqEvent */
	case (AL_SEQ_END_EVT):
	case (AL_TEMPO_EVT):
	case (AL_SEQ_MIDI_EVT):

#ifdef _DEBUG
	    assert(FALSE);		
#endif

	    break;
        }
        seqp->nextDelta = alEvtqNextEvent(&seqp->evtq, &seqp->nextEvent); 
        
    } while (seqp->nextDelta == 0);

    /*
     * assume that next callback won't be more than half an
     * hour away
     */
    seqp->curTime += seqp->nextDelta;		/* sct 11/7/95 */
    return seqp->nextDelta;
}

void __CSPPostNextSeqEvent(ALCSPlayer *seqp) 
{
    ALEvent     evt;
    s32		deltaTicks;
    
    if (seqp->state != AL_PLAYING || seqp->target == NULL)
        return;
    
    /* Get the next event time in ticks. */
    /* If false is returned, then there is no next delta (ie. end of sequence reached). */
    if (!__alCSeqNextDelta(seqp->target, &deltaTicks))
	return;
        
    evt.type = AL_SEQ_REF_EVT;
    alEvtqPostEvent(&seqp->evtq, &evt, deltaTicks * seqp->uspt);                
}

void __CSPHandleNextSeqEvent(ALCSPlayer *seqp)
{
    ALEvent	evt;

    if (seqp->target == NULL)
	return;

    __alCSeqGetTrackEvent(seqp->target, &evt);

    switch (evt.type)
    {
      case AL_SEQ_MIDI_EVT:
          __CSPHandleMIDIMsg(seqp, &evt);
	  __CSPPostNextSeqEvent(seqp);
	  break;

      case AL_TEMPO_EVT:
          __CSPHandleMetaMsg(seqp, &evt);
	  __CSPPostNextSeqEvent(seqp);
	  break;

      case AL_SEQ_END_EVT:
	  seqp->state = AL_STOPPING;      
	  evt.type    = AL_SEQP_STOP_EVT;
	  alEvtqPostEvent(&seqp->evtq, &evt, AL_EVTQ_END);
	  break;

      case AL_TRACK_END:
      case AL_CSP_LOOPSTART:
      case AL_CSP_LOOPEND:
	  __CSPPostNextSeqEvent(seqp);
	  break;
    }
}

GLOBAL_ASM("lib/asm/non_matchings/csplayer/__CSPHandleMIDIMsg.s")

void __CSPHandleMetaMsg(ALCSPlayer *seqp, ALEvent *event)
{
    ALTempoEvent    *tevt = &event->msg.tempo;
    ALEvent         evt;
    s32             tempo;
    s32             oldUspt;
    u32             ticks;
    ALMicroTime         tempDelta,curDelta = 0;
    ALEventListItem     *thisNode,*nextNode,*firstTemp = 0;


    if (event->msg.tempo.status == AL_MIDI_Meta)
    {
        if (event->msg.tempo.type == AL_MIDI_META_TEMPO)
        {
	    oldUspt = seqp->uspt;
	    tempo = (tevt->byte1 << 16) | (tevt->byte2 <<  8) | (tevt->byte3 <<  0);
	    __setUsptFromTempo (seqp, (f32)tempo);	/* sct 1/8/96 */

	    thisNode = (ALEventListItem*)seqp->evtq.allocList.next;
	    while(thisNode)
	    {
		curDelta += thisNode->delta;
		nextNode = (ALEventListItem*)thisNode->node.next;
		if(thisNode->evt.type == AL_CSP_NOTEOFF_EVT)
		{
		    alUnlink((ALLink*)thisNode);

		    if(firstTemp)
			alLink((ALLink*)thisNode,(ALLink*)firstTemp);
		    else
		    {
			thisNode->node.next = 0;
			thisNode->node.prev = 0;
			firstTemp = thisNode;
		    }
		    tempDelta = curDelta;         /* record the current delta */
		    if(nextNode) /* don't do this if no nextNode */
		    {
			curDelta -= thisNode->delta;  /* subtract out this delta */
			nextNode->delta += thisNode->delta; /* add it to next event */
		    }
		    thisNode->delta = tempDelta; /* set this event delta from current */
		}
		thisNode = nextNode;
	    }

	    thisNode = firstTemp;
	    while(thisNode)
	    {
		nextNode = (ALEventListItem*)thisNode->node.next;
		ticks = thisNode->delta/oldUspt;
		thisNode->delta = ticks * seqp->uspt;
		__CSPRepostEvent(&seqp->evtq,thisNode);
		thisNode = nextNode;
	    }
        }
    }
}

void  __CSPRepostEvent(ALEventQueue *evtq, ALEventListItem *item)
{
    OSIntMask           mask;
    ALLink              *node;
    ALEventListItem     *nextItem;
    
    mask = osSetIntMask(OS_IM_NONE);

    for (node = &evtq->allocList; node != 0; node = node->next)
    {
        if (!node->next)  /* end of the list */
        {
            alLink((ALLink *)item, node);
            break;
        }
        else
        {
            nextItem = (ALEventListItem *)node->next;
            if (item->delta < nextItem->delta)
            {
                nextItem->delta -= item->delta;
                alLink((ALLink *)item, node);
                break;
            }
            item->delta -= nextItem->delta;
        }
    }
    osSetIntMask(mask);
}

void __setUsptFromTempo(ALCSPlayer *seqp, f32 tempo)
{
    if (seqp->target)
	seqp->uspt = (s32)((f32)tempo * seqp->target->qnpt);
    else
	seqp->uspt = 488;		/* This is the initial value set by alSeqpNew. */
}
