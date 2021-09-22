/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2540 */

#include "libultra_internal.h"

extern OSThread *__osRunningThread;
OSPri osGetThreadPri(OSThread *thread) {
    if (thread == NULL)
        thread = __osRunningThread;
    return thread->priority;
}
