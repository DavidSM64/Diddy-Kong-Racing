/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065BD0 */

#include "types.h"
#include "macros.h"

extern s16 D_800DD050;

extern s32* D_80065D98;
extern s32* D_8011D750;
extern s32* D_8011F758;
extern s32* D_8011F760;
extern s32* D_8011F910;

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

GLOBAL_ASM("asm/non_matchings/unknown_0667D0/func_80065C38.s")

void func_80065D40(void) {
    osInitialize();
    osCreateThread(&D_8011F760, 1, &D_80065D98, 0, &D_8011D750, 0);
    osStartThread(&D_8011F760);
}

GLOBAL_ASM("asm/non_matchings/unknown_0667D0/func_80065D98.s")
GLOBAL_ASM("asm/non_matchings/unknown_0667D0/func_80065E30.s")


