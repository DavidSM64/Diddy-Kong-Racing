/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D65B0 */

#include "macros.h"
#include "libultra_internal.h"
#include "viint.h"

extern OSThread *__osRunningThread;
extern OSThread *__osRunQueue;

extern void __osEnqueueAndYield(OSThread **);
extern void   __osRestoreInt(u32);

void osYieldThread(void) {
    register u32 saveMask = __osDisableInt();
    __osRunningThread->state = OS_STATE_RUNNABLE;
    __osEnqueueAndYield(&__osRunQueue);
    __osRestoreInt(saveMask);
}
