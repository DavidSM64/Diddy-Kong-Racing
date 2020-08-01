/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2540 */

#include "libultra_internal.h"

extern OSThread *D_800E4890; //__osRunningThread;
OSPri osGetThreadPri(OSThread *thread)
{
    if (thread == NULL)
        thread = D_800E4890;
    return thread->priority;
}