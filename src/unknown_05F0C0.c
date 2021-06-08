/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005E4C0 */

#include "types.h"
#include "macros.h"

/************ .data ************/

s16 D_800DCE40[16] = {
    0x0244, 0x0242, 0x0243, 0x0245,
    0x0246, 0x0247, 0x0248, 0x00F6,
    0x00F7, 0x0225, 0x0226, 0x002E,
    0x002F, 0x0030, 0x0000, 0x0000
};

/*******************************/

/************ .bss ************/

s8 D_8011D5F0;
s8 D_8011D5F1;

/******************************/

GLOBAL_ASM("asm/non_matchings/unknown_05F0C0/func_8005E4C0.s")
