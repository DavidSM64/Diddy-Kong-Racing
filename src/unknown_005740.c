/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80004B40 */

#include "unknown_005740.h"

#include "types.h"
#include "macros.h"

/************ .data ************/

u8 D_800DC6D0 = 1;
s32 D_800DC6D4 = 0; // Currently unknown, might be a different type.
s32 D_800DC6D8 = 1; // Currently unknown, might be a different type.

/*******************************/

/************ .bss ************/

s32 D_80119C30[2];
s32 D_80119C38;
s32 D_80119C3C;
s32 D_80119C40;
s32 D_80119C44;
s32 **D_80119C48;
s32 D_80119C4C;
s32 D_80119C50[2];
s32 D_80119C58;
s32 D_80119C5C;
s32 D_80119C60[670];
s32 D_8011A6D8;
s32 D_8011A6DC;
s32 D_8011A6E0[334];
s32 D_8011AC18;
s32 D_8011AC1C;
s16 D_8011AC20[128];

/******************************/

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80004B40.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800050D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80005254.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80005D08.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800063EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006AC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006BFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006FC8.s")

UNUSED void func_80007F78(void) {
    D_800DC6D0 = 1;
}

UNUSED void func_80007F88(void) {
    D_800DC6D0 = 0;
}

UNUSED u8 func_80007F94(void) {
    return D_800DC6D0;
}

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80007FA4.s")
