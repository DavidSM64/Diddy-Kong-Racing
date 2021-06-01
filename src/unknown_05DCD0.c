/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005D0D0 */

#include "types.h"
#include "macros.h"

/************ .data ************/

s16 D_800DCE00[16] = {
    0x022D, 0x00A7, 0x00A8, 0x00B7,
    0x00B8, 0x00F4, 0x00F5, 0x00FA,
    0x00FB, 0x0229, 0x022A, 0x002E,
    0x002F, 0x0030, 0x0000, 0x0000
};

s16 D_800DCE20[16] = {
    0x022C, 0x00A5, 0x00A6, 0x00B5,
    0x00B6, 0x00F2, 0x00F3, 0x00F8,
    0x00F9, 0x0227, 0x0228, 0x002E,
    0x002F, 0x0030, 0x0000, 0x0000
};

/*******************************/

/************ .rodata ************/

const DoubleLiteral D_800E6A30 = { 0.3 };
const DoubleLiteral D_800E6A38 = { -0.1 };
const DoubleLiteral D_800E6A40 = { 0.1 };
const DoubleLiteral D_800E6A48 = { 700.0 };
const DoubleLiteral D_800E6A50 = { 0.3 };
const DoubleLiteral D_800E6A58 = { -0.3 };
const DoubleLiteral D_800E6A60 = { 0.27 };
const DoubleLiteral D_800E6A68 = { 0.45 };

// Jump table in func_8005D820
const u32 D_800E6A70[] = {
    0x8005DBEC, 0x8005DC10, 0x8005DC48, 0x8005DC64, 
    0x8005DCBC, 0x8005DCE8
};

const DoubleLiteral D_800E6A88 = { -0.1 };
const DoubleLiteral D_800E6A90 = { 0.1 };
const DoubleLiteral D_800E6A98 = { 700.0 };

/*********************************/

GLOBAL_ASM("asm/non_matchings/unknown_05DCD0/func_8005D0D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_05DCD0/func_8005D820.s")
GLOBAL_ASM("asm/non_matchings/unknown_05DCD0/func_8005E204.s")
