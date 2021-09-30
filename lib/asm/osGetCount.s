/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C78D0 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel osGetCount
/* 0C84D0 800C78D0 40024800 */  mfc0  $v0, $9
/* 0C84D4 800C78D4 03E00008 */  jr    $ra
/* 0C84D8 800C78D8 00000000 */   nop   

/* 0C84DC 800C78DC 00000000 */  nop   

