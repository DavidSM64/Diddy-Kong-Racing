/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8009EC70 */

#include "types.h"

extern s32 D_800DF494;
extern s32 gActiveMagicCodes;
extern s32 D_800DF4C0;

s32 func_8009EC70(void) {
    return D_800DF494;
}

s32 func_8009EC80(void) {
    if (func_8009C2D0() != 0) {
        return 0;
    }
    return D_800DF4C0;
}

s32 is_tt_unlocked(void) {
    return gActiveMagicCodes & 1;
}

s32 is_drumstick_unlocked(void) {
    return gActiveMagicCodes & 2;
}
