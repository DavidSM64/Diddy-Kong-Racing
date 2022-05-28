/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B7D1F */

#include "stacks.h"

// This file only contains .bss variables and needs to be located just before
// waves.c; that is why this is "located" at 0x800B7D1F.

/************ .bss ************/

u8 piThreadStack[0x100]; // piThreadStack[OS_PIM_STACKSIZE];
u8 D_80129BB0[0x400]; // epcStack?
s32 D_80129FB0[3];
s32 D_80129FBC;

/******************************/
