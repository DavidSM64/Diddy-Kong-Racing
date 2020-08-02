/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4570 */

.include "globals.inc"
.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel __osGetSR
/* 0D5170 800D4570 40026000 */  mfc0  $v0, $12
/* 0D5174 800D4574 03E00008 */  jr    $ra
/* 0D5178 800D4578 00000000 */   nop   

/* 0D517C 800D457C 00000000 */  nop   
