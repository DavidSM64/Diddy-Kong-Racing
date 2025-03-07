/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B7D1F */

#include "stacks.h"

#include "types.h"
#include "macros.h"

// This file only contains .bss variables and needs to be located just before
// waves.c; that is why this is "located" at 0x800B7D1F.

/************ .bss ************/

UNUSED u8 D_80129AB0[0x100];
u16 D_80129BB0[512]; // epcStack?
s32 gObjectStackTrace[3];

/******************************/
