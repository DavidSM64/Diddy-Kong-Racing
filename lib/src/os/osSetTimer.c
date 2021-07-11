/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4DE0 */

#include "macros.h"

#if 1
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/osSetTimer.s")
#else
#include "libultra_internal.h"

extern OSTimer *D_800E4910;

u32 osSetTimer(OSTimer *t, OSTime value, OSTime interval, OSMesgQueue *mq, OSMesg msg)
{
    OSTime time;
    t->next = NULL;
    t->prev = NULL;
    t->interval = interval;
    if(value != 0) t->remaining = value;
    else t->remaining = interval;
    t->mq = mq;
    t->msg = msg;
    time = (OSTime) __osInsertTimer(t);
    if(D_800E4910->next == t) {
        __osSetTimerIntr(time);
    }
    return 0;
}
#endif
