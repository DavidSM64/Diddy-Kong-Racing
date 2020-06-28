.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_80063C00
/* 064800 80063C00 30AE00FF */  andi  $t6, $a1, 0xff
/* 064804 80063C04 AFA50004 */  sw    $a1, 4($sp)
/* 064808 80063C08 000EC080 */  sll   $t8, $t6, 2
/* 06480C 80063C0C 8C8F0060 */  lw    $t7, 0x60($a0)
/* 064810 80063C10 030EC021 */  addu  $t8, $t8, $t6
/* 064814 80063C14 0018C080 */  sll   $t8, $t8, 2
/* 064818 80063C18 01F8C821 */  addu  $t9, $t7, $t8
/* 06481C 80063C1C 93220010 */  lbu   $v0, 0x10($t9)
/* 064820 80063C20 03E00008 */  jr    $ra
/* 064824 80063C24 00000000 */   nop   
/* 064828 80063C28 00000000 */  nop   
/* 06482C 80063C2C 00000000 */  nop   
