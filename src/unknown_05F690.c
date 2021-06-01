/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005EA90 */

#include "types.h"
#include "macros.h"

/************ .data ************/

s16 D_800DCE60[16] = {
    0x022C, 0x00A5, 0x00A6, 0x0057,
    0x0051, 0x006D, 0x0052, 0x00F8,
    0x00F9, 0x0227, 0x0228, 0x002E,
    0x002F, 0x0030, 0x0000, 0x0000
};


s16 D_800DCE80[16] = {
    0x022C, 0x00A5, 0x00A6, 0x0057,
    0x0051, 0x006D, 0x0052, 0x00F8,
    0x00F9, 0x0227, 0x0228, 0x002E,
    0x002F, 0x0030, 0x0000, 0x0000
};

s32 D_800DCEA0 = 116315;
s32 D_800DCEA4 = 1980;

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

// This is probably just file boundary padding.
const DoubleLiteral D_800E6AF8 = { 0.0 }; 

const DoubleLiteral D_800E6B00 = { 0.3 };
const DoubleLiteral D_800E6B08 = { -0.3 };
const DoubleLiteral D_800E6B10 = { 0.4 };

// This is another file boundary.
const DoubleLiteral D_800E6B18 = { 0.0 }; 

// I am not sure where these go. It is hard to tell without any glabels.
// Need to figure out which file handles creating models.
const char D_800E6B20[] = "Error: Model no. out of range on load. !!\n";
const char D_800E6B4C[] = "TEXTURE ERROR!!\n%d,%d\n";
const char D_800E6B64[] = "Error: Model table overflow!!\n";
const char D_800E6B84[] = "WARNING :: createModelInstance called with NULL pointer\n";
const char D_800E6BC0[] = "ModFreeModel : NULL mod_inst!!\n";
const char D_800E6BE0[] = "MOD Error: Tryed to deallocate non-existent model!!\n";

/*********************************/

GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005EA90.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005F310.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005F850.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005F99C.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005FCD0.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8005FF40.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060058.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_8006017C.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060910.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060AC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060C58.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80060EA8.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_800619F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80061A00.s")
GLOBAL_ASM("asm/non_matchings/unknown_05F690/func_80061C0C.s")
