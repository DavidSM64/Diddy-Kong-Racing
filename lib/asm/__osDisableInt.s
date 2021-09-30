/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2560 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel __osDisableInt
/* 0D3160 800D2560 40086000 */  mfc0  $t0, $12
/* 0D3164 800D2564 2401FFFE */  li    $at, -2
/* 0D3168 800D2568 01014824 */  and   $t1, $t0, $at
/* 0D316C 800D256C 40896000 */  mtc0  $t1, $12
/* 0D3170 800D2570 31020001 */  andi  $v0, $t0, 1
/* 0D3174 800D2574 00000000 */  nop   
/* 0D3178 800D2578 03E00008 */  jr    $ra
/* 0D317C 800D257C 00000000 */   nop   
