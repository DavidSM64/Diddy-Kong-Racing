.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel D_800C7340
/* 0C7F40 800C7340 03E00008 */  jr    $ra
/* 0C7F44 800C7344 00001025 */   move  $v0, $zero

/* 0C7F48 800C7348 00000000 */  nop   
/* 0C7F4C 800C734C 00000000 */  nop   
