/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D37F0 */

#include "libultra_internal.h"

extern OSDevMgr __osPiDevMgr;

OSMesgQueue *osPiGetCmdQueue(void) {
    if (!__osPiDevMgr.active)
        return NULL;
    return __osPiDevMgr.cmdQueue;
}
