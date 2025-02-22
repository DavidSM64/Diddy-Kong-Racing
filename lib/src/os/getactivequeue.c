/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2470 */

#include "PR/os_internal.h"
#include "PRinternal/osint.h"

OSThread* __osGetActiveQueue(void) {
    return __osActiveQueue;
}
