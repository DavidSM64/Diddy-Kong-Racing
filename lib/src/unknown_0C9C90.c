/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C9090 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/alEvtqFlushType.s")


GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/alEvtqPostEvent.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/alEvtqNextEvent.s")

//GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9C90/alEvtqNew.s")
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
