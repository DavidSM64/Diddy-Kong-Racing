.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C79C0
/* 0C85C0 800C79C0 AFA50004 */  sw    $a1, 4($sp)
/* 0C85C4 800C79C4 8C8F0060 */  lw    $t7, 0x60($a0)
/* 0C85C8 800C79C8 30AE00FF */  andi  $t6, $a1, 0xff
/* 0C85CC 800C79CC 000EC100 */  sll   $t8, $t6, 4
/* 0C85D0 800C79D0 01F8C821 */  addu  $t9, $t7, $t8
/* 0C85D4 800C79D4 03E00008 */  jr    $ra
/* 0C85D8 800C79D8 9322000A */   lbu   $v0, 0xa($t9)

/* 0C85DC 800C79DC 00000000 */  nop   
