/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D6600 */

#include "macros.h"
#include "libultra_internal.h"
#include "osint.h"

void osDestroyThread(OSThread *t) {
    register u32 saveMask;
    register OSThread *pred;
    register OSThread *succ;

	saveMask = __osDisableInt();

	if (t == NULL) {
        t = __osRunningThread;
    } else if (t->state != OS_STATE_STOPPED) {
        __osDequeueThread(t->queue, t);
    }

    if (__osActiveQueue == t) {
        __osActiveQueue = __osActiveQueue->tlnext;
    } else {
        pred = __osActiveQueue;
		succ = pred->tlnext;
        while (succ != NULL) {
            if (succ == t) {
                pred->tlnext = t->tlnext;
                break;
            }

            pred = succ;
            succ = pred->tlnext;
        }
    }

    if (t == __osRunningThread) {
        __osDispatchThread();
    }

    __osRestoreInt(saveMask);
}
