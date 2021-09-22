/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1D10 */

#include "libultra_internal.h"
#include "viint.h"

void osViBlack(u8 active) {
    register u32 int_disabled = __osDisableInt();
    if (active) {
        __osViNext->state |= VI_STATE_BLACK;
    } else {
        __osViNext->state &= ~VI_STATE_BLACK;
    }
    __osRestoreInt(int_disabled);
}
