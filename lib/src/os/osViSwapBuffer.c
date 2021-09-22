/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2420 */

#include "libultra_internal.h"

extern OSViContext *__osViNext;

void osViSwapBuffer(void *frameBufPtr) {
    u32 saveMask = __osDisableInt();
    __osViNext->buffer = frameBufPtr;
    __osViNext->unk00 |= 0x10;
    __osRestoreInt(saveMask);
}
