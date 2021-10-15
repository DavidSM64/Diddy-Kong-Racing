/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C9AD0 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel sqrtf
/* 0CA6D0 800C9AD0 03E00008 */  jr    $ra
/* 0CA6D4 800C9AD4 46006004 */  sqrt.s $f0, $f12

/* 0CA6D8 800C9AD8 00000000 */  nop
/* 0CA6DC 800C9ADC 00000000 */  nop

