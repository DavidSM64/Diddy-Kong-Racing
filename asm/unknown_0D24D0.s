.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800D18D0
/* 0D24D0 800D18D0 3C0EA410 */  lui   $t6, 0xa410
/* 0D24D4 800D18D4 03E00008 */  jr    $ra
/* 0D24D8 800D18D8 8DC2000C */   lw    $v0, 0xc($t6)

/* 0D24DC 800D18DC 00000000 */  nop   
