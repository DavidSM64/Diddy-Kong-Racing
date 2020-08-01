/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1D10 */

#include "libultra_internal.h"

extern OSViContext *D_800E4874;
// TODO: name magic constants
void osViBlack(u8 active) {
    register u32 int_disabled = __osDisableInt();
    if (active) {
        D_800E4874->unk00 |= 0x20;
    } else {
        D_800E4874->unk00 &= ~0x20;
    }
    __osRestoreInt(int_disabled);
}
