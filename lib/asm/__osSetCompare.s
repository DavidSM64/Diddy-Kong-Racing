/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D7460 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel __osSetCompare
/* 0D8060 800D7460 40845800 */  mtc0  $a0, $11
/* 0D8064 800D7464 03E00008 */  jr    $ra
/* 0D8068 800D7468 00000000 */   nop   

/* 0D806C 800D746C 00000000 */  nop   
