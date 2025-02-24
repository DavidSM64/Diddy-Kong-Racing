/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D37F0 */

#include "PR/os_internal.h"
#include "PRinternal/piint.h"

OSMesgQueue* osPiGetCmdQueue(void) {
    if (!__osPiDevMgr.active) {
        return NULL;
    } else {
        return __osPiDevMgr.cmdQueue;
    }
}
