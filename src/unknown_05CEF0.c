/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005C2F0 */

#include "types.h"
#include "macros.h"

/************ .data ************/

s16 D_800DCDE0[16] = {
    0x022B, 0x00A3, 0x00A4, 0x00B3,
    0x00B4, 0x00F0, 0x00F1, 0x00F6, 
    0x00F7, 0x0225, 0x0226, 0x002E, 
    0x002F, 0x0030, 0x0000, 0x0000
};

/*******************************/

/************ .rodata ************/

const DoubleLiteral D_800E6A10 = { 0.3 };
const DoubleLiteral D_800E6A18 = { -0.1 };
const DoubleLiteral D_800E6A20 = { 0.1 };
const DoubleLiteral D_800E6A28 = { 700.0 };

/*********************************/

GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005C2F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005C364.s")
GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005CA78.s")
GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005CA84.s")
GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005CB04.s")
GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005CB68.s")
GLOBAL_ASM("asm/non_matchings/unknown_05CEF0/func_8005D048.s")
