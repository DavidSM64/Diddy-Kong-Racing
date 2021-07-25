/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8005F310 */

#include "unknown_05FF10.h"

#include "types.h"
#include "macros.h"

/************ .data ************/

s16 D_800DCE80[14] = {
    0x022C, 0x00A5, 0x00A6, 0x0057,
    0x0051, 0x006D, 0x0052, 0x00F8,
    0x00F9, 0x0227, 0x0228, 0x002E,
    0x002F, 0x0030
};

/*******************************/

/************ .bss ************/

s8 D_8011D610;
s8 D_8011D611;

/******************************/

GLOBAL_ASM("asm/non_matchings/unknown_05FF10/func_8005F310.s")
