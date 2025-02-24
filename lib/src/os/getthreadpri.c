/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2540 */

#include "PR/os_internal.h"
#include "PRinternal/osint.h"

OSPri osGetThreadPri(OSThread* thread) {
    if (thread == NULL) {
        thread = __osRunningThread;
    }

    return thread->priority;
}
