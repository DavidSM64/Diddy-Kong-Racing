/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B6E50 */

#include "types.h"
#include "macros.h"

/************ .rodata ************/

const char D_800E8E70[] = "\nAssertion failed: '%s' in file %s, line %d\n";
const char D_800E8EA0[] = "\nAssertion failed: '%s' in file %s, line %d\n";
const char D_800E8ED0[] = ">fault< ";
const char D_800E8EDC[] = "CORE";
const u8 D_800E8EE4[4] = { 0, 0, 0, 0 };
const char D_800E8EE8[] = "CORE";
const u8 D_800E8EF0[4] = { 0, 0, 0, 0 };
const char D_800E8EF4[] = "CORE";
const u8 D_800E8EFC[4] = { 0, 0, 0, 0 };

/*********************************/

/************ .data ************/

s32 D_800E3020 = -1;
s32 D_800E3024 = 0;
s32 D_800E3028 = 0;

char *D_800E302C[3] = {
    "setup", "control", "print"
};

/*******************************/


GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6E50.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6EE0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6F04.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6F40.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6F50.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/D_800B6FC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B70D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7144.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B71B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7460.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B76B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B76DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B77D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7810.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7D10.s")
