/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80031B60 */

#include "types.h"
#include "macros.h"
#include "structs.h"

/************ .data ************/

s32 D_800DC950 = 0;
s32 D_800DC954 = 0;
s32 D_800DC958 = 0;
s32 D_800DC95C = 0;
s32 D_800DC960 = 0;
s32 D_800DC964 = 0;
s32 D_800DC968 = 0; // Currently unknown, might be a different type.

/*******************************/

void func_80031B60(void) {
    if (D_800DC950 != 0) {
        func_80071140(D_800DC950);
        D_800DC950 = 0;
        D_800DC954 = 0;
        D_800DC960 = 0;
        D_800DC964 = 0;
    }
    D_800DC95C = 0;
    D_800DC958 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031BB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031CAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80031F88.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032398.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032424.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032BAC.s")

s32 func_80032C6C(void) {
    return D_800DC95C;
}

GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80032C7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_800337E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80033A14.s")
GLOBAL_ASM("asm/non_matchings/unknown_032760/func_80033C08.s")
