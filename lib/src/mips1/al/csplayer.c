/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80062290 */

#include "PR/os_exception.h"
#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "seqp.h"

/************ .rodata ************/

const char D_800E6C20[] = "CSP: oh oh \n";

/*********************************/

void __CSPPostNextSeqEvent(ALCSPlayer *seqp);
void __CSPHandleNextSeqEvent(ALCSPlayer *seqp);
void __CSPHandleMetaMsg(ALCSPlayer *seqp, ALEvent *event);
void  __CSPRepostEvent(ALEventQueue *evtq, ALEventListItem *item);
void __setUsptFromTempo(ALCSPlayer *seqp, f32 tempo);

GLOBAL_ASM("lib/asm/non_matchings/csplayer/alCSPNew.s")
GLOBAL_ASM("lib/asm/non_matchings/csplayer/__CSPVoiceHandler.s")

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
