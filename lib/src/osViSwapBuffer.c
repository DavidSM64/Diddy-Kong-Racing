/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2420 */

#include "libultra_internal.h"

extern OSViContext* D_800E4874;

void osViSwapBuffer(void* frameBufPtr){
    u32 saveMask = __osDisableInt();
    D_800E4874->buffer = frameBufPtr;
    D_800E4874->unk00 |= 0x10;
    __osRestoreInt(saveMask);
}