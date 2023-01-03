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
s32 D_80119C58; //Struct of size in func_8000A184 = 0x180 = 384 bytes
s32 D_80119C5C; //Struct of size in func_8000A184 = 0x180 = 384 bytes Likely the same as above
s32 D_80119C60[670];
s32 D_8011A6D8; //unk8011A6D8[]
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

f32 func_80007FA4(f32 arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 var_f14;
    f32 var_f2;
    s32 var_v0;

    var_f2 = 0.0f;
    temp_f0 = -1.0f;
    arg0 = (arg0 - 1.0f) / (1.0f + arg0);
    var_f14 = arg0;
    temp_f12 = arg0 * arg0;
    for (var_v0 = 1; (var_f2 - temp_f0) > 0.001f; var_v0 += 2) {
        temp_f0 = var_f2;
        var_f2 += var_f14 / var_v0;
        var_f14 *= temp_f12;
    }
    return var_f2 * 2;
}
