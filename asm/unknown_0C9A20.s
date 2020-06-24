.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C8E20
/* 0C9A20 800C8E20 3C0EA450 */  lui   $t6, 0xa450
/* 0C9A24 800C8E24 03E00008 */  jr    $ra
/* 0C9A28 800C8E28 8DC20004 */   lw    $v0, 4($t6)

/* 0C9A2C 800C8E2C 00000000 */  nop   
