/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007AC70 */

#include "types.h"
#include "macros.h"

extern s32 D_800DE7C4;
extern s32 D_80126338;
extern s32 D_8012633C;
extern s32 D_80126354;
extern s32 D_80126378;
extern s16 D_80126382;
extern s16 D_80126384;

GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007AC70.s")

void func_8007AE0C(s32 arg0) {
    D_80126378 |= arg0;
}

void func_8007AE28(s32 arg0) {
    D_80126378 &= ~arg0;
}

/* Unused? */
s32 func_8007AE44(void) {
    return D_80126338;
}

/* Unused? */
s32 func_8007AE54(void) {
    return D_8012633C;
}

/* Unused? */
s32 func_8007AE64(void) {
    return D_80126354;
}

GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007AE74.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B2BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B374.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B3D0.s")

void func_8007B43C(void) {
    D_80126384 = 1;
    D_80126382 = 1;
}

void func_8007B454(void) {
    D_80126384 = 0;
    D_80126382 = 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B46C.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B4C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007B4E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007BA5C.s")

void func_8007BF1C(s32 arg0) {
    D_800DE7C4 = arg0;
    D_80126382 = 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007BF34.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007C12C.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007C57C.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007C8E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007CA68.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007CCB0.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007CDC0.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007D0F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007EF64.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007EF80.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007F1E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007F24C.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007F414.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007F460.s")
GLOBAL_ASM("asm/non_matchings/unknown_07B870/func_8007F594.s")
