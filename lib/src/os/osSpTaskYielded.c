/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1DF0 */

#include "libultra_internal.h"
#include "viint.h"
#include "PR/sptask.h"

__OSViContext vi[2] = {0};
__OSViContext *__osViCurr = &vi[0];
__OSViContext *__osViNext = &vi[1];

//TODO: This should be defined above osInitialize
s32 osViClock = VI_NTSC_CLOCK;

OSYieldResult osSpTaskYielded(OSTask *tp) {
    u32 status;
    OSYieldResult result;
    status = __osSpGetStatus();
    if (status & SP_STATUS_YIELDED)
        result = OS_TASK_YIELDED;
    else
        result = 0;
    if (status & SP_STATUS_YIELD) {
        tp->t.flags |= result;
        tp->t.flags &= ~(OS_TASK_DP_WAIT);
    }
    return result;
}
