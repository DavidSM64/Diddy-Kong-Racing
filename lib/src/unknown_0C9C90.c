/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C9090 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "libultra_internal.h"

GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/alEvtqFlushType.s")


GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/alEvtqPostEvent.s")
//GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/alEvtqNextEvent.s")

ALMicroTime alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt) 
{
    ALEventListItem *item;
    ALMicroTime delta;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);
    
    item = (ALEventListItem *)evtq->allocList.next;

    if (item)
    {
        alUnlink((ALLink *)item);
        alCopy(&item->evt, evt, sizeof(*evt));
        alLink((ALLink *)item, &evtq->freeList);
	delta = item->delta;
    }
    else
    {
        /* sct 11/28/95 - If we get here, most like we overflowed the event queue */
	/* with non-self-perpetuating events.  Eg. if we filled the evtq with volume */
	/* events, then when the seqp is told to play it will handle all the events */
	/* at once completely emptying out the queue.  At this point this problem */
	/* must be treated as an out of resource error and the evtq should be increased. */
	evt->type = -1;
	delta = 0;	    
    }

    osSetIntMask(mask);
    
    return delta;
}


void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount)
{
    s32 i;
    
    evtq->eventCount     = 0;
    evtq->allocList.next = 0;
    evtq->allocList.prev = 0;
    evtq->freeList.next  = 0;
    evtq->freeList.prev  = 0;

    for (i = 0; i < itemCount; i++) {
        alLink((ALLink *)&items[i], &evtq->freeList);
    }
}

GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/alSynAddPlayer.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/_allocatePVoice.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/alSynAllocVoice.s")
