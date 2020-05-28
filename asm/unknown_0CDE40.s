.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800CD240
/* 0CDE40 800CD240 3C0EA404 */  lui   $t6, 0xa404
/* 0CDE44 800CD244 03E00008 */  jr    $ra
/* 0CDE48 800CD248 ADC40010 */   sw    $a0, 0x10($t6)

/* 0CDE4C 800CD24C 00000000 */  nop   
