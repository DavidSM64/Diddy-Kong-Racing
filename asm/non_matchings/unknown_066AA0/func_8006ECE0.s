glabel func_8006ECE0
/* 06F8E0 8006ECE0 3C02800E */  lui   $v0, %hi(D_800DD37C) # $v0, 0x800e
/* 06F8E4 8006ECE4 2442D37C */  addiu $v0, %lo(D_800DD37C) # addiu $v0, $v0, -0x2c84
/* 06F8E8 8006ECE8 8C4E0000 */  lw    $t6, ($v0)
/* 06F8EC 8006ECEC 00000000 */  nop   
/* 06F8F0 8006ECF0 35CF0200 */  ori   $t7, $t6, 0x200
/* 06F8F4 8006ECF4 03E00008 */  jr    $ra
/* 06F8F8 8006ECF8 AC4F0000 */   sw    $t7, ($v0)

