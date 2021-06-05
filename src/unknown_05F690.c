/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005EA90 */

#include "types.h"
#include "macros.h"

/************ .data ************/

s16 D_800DCE60[14] = {
    0x022C, 0x00A5, 0x00A6, 0x0057,
    0x0051, 0x006D, 0x0052, 0x00F8,
    0x00F9, 0x0227, 0x0228, 0x002E,
    0x002F, 0x0030
};

/*******************************/

/************ .rodata ************/

const DoubleLiteral D_800E6AB0 = { 0.3 };
const DoubleLiteral D_800E6AB8 = { -0.3 };
const DoubleLiteral D_800E6AC0 = { 0.4 };
const DoubleLiteral D_800E6AC8 = { 0.45 };

// Jump table in func_8005EA90
const u32 D_800E6AD0[] = {
    0x8005EE9C, 0x8005EEC0, 0x8005EEF8, 0x8005EF14,
    0x8005EF6C, 0x8005EF98
};

const DoubleLiteral D_800E6AE8 = { -0.1 };
const DoubleLiteral D_800E6AF0 = { 0.1 };

/*********************************/

GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005EA90.s")
