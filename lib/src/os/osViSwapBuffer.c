/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2420 */

#include "libultra_internal.h"
#include "viint.h"

void osViSwapBuffer(void *frameBufPtr) {
    u32 saveMask = __osDisableInt();
    __osViNext->framep = frameBufPtr;
    __osViNext->state |= VI_STATE_10;
    __osRestoreInt(saveMask);
}
