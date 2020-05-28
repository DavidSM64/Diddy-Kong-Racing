.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C7A50
/* 0C8650 800C7A50 03E00008 */  jr    $ra
/* 0C8654 800C7A54 8C82002C */   lw    $v0, 0x2c($a0)

/* 0C8658 800C7A58 00000000 */  nop   
/* 0C865C 800C7A5C 00000000 */  nop   
