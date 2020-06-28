/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065BD0 */

#include "types.h"
#include "macros.h"

extern s16 D_800DD050;

void func_80065BD0(s32 arg0) {
    D_800DD050 = arg0;
}

/* Unused? */
s16 func_80065BDC(void) {
    return D_800DD050;
}

s32 func_80065BEC(s32 arg0) {
    switch(D_800DD050) {
        case 0:
            return arg0;
        case 2:
            arg0 = ((arg0 - 0x40) >> 1) + 0x40;
            return arg0;
        case 1:
        default:
            return 0x40;
    }
}

GLOBAL_ASM("asm/non_matchings/func_80065C38.s")

