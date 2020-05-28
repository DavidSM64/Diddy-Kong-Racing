.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C79A0
/* 0C85A0 800C79A0 AFA50004 */  sw    $a1, 4($sp)
/* 0C85A4 800C79A4 8C8F0060 */  lw    $t7, 0x60($a0)
/* 0C85A8 800C79A8 30AE00FF */  andi  $t6, $a1, 0xff
/* 0C85AC 800C79AC 000EC100 */  sll   $t8, $t6, 4
/* 0C85B0 800C79B0 01F8C821 */  addu  $t9, $t7, $t8
/* 0C85B4 800C79B4 03E00008 */  jr    $ra
/* 0C85B8 800C79B8 93220009 */   lbu   $v0, 9($t9)

/* 0C85BC 800C79BC 00000000 */  nop   
