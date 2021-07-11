/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C89A0 */

#include "libultra_internal.h"

extern OSThread* __osRunningThread;
extern OSThread* __RunQueue; //__osRunQueue

void osStartThread(OSThread *t)
{
    register u32 saveMask = __osDisableInt();
    switch (t->state)
    {
    case OS_STATE_WAITING:
        t->state = OS_STATE_RUNNABLE;
        __osEnqueueThread(&__RunQueue, t);
        break;
    case OS_STATE_STOPPED:
        if (t->queue == NULL || t->queue == &__RunQueue)
        {
            t->state = OS_STATE_RUNNABLE;
            __osEnqueueThread(&__RunQueue, t);
        }
        else
        {
            t->state = OS_STATE_WAITING;
            __osEnqueueThread(t->queue, t);
            __osEnqueueThread(&__RunQueue, __osPopThread(t->queue));
        }
        break;
    }
    if (__osRunningThread == NULL)
    {
        __osDispatchThread();
    }
    else
    {
        if (__osRunningThread->priority < __RunQueue->priority)
        {
            __osRunningThread->state = OS_STATE_RUNNABLE;
            __osEnqueueAndYield(&__RunQueue);
        }
    }
    __osRestoreInt(saveMask);
}