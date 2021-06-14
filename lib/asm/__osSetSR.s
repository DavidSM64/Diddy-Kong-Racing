/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4560 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel __osSetSR
/* 0D5160 800D4560 40846000 */  mtc0  $a0, $12
/* 0D5164 800D4564 00000000 */  nop   
/* 0D5168 800D4568 03E00008 */  jr    $ra
/* 0D516C 800D456C 00000000 */   nop   

