/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B7D1F */

#include "stacks.h"

#include "types.h"
#include "macros.h"

// This file only contains .bss variables and needs to be located just before
// waves.c; that is why this is "located" at 0x800B7D1F.

/************ .bss ************/

u16 D_80129BB0[512]; // epcStack?
s32 D_80129FB0[3];
s32 D_80129FBC;

/******************************/
