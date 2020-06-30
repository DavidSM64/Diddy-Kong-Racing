glabel func_8006EB5C
/* 06F75C 8006EB5C 3C02800E */  lui   $v0, %hi(D_800DD37C) # $v0, 0x800e
/* 06F760 8006EB60 2442D37C */  addiu $v0, %lo(D_800DD37C) # addiu $v0, $v0, -0x2c84
/* 06F764 8006EB64 8C4E0000 */  lw    $t6, ($v0)
/* 06F768 8006EB68 00000000 */  nop   
/* 06F76C 8006EB6C 35CF0003 */  ori   $t7, $t6, 3
/* 06F770 8006EB70 03E00008 */  jr    $ra
/* 06F774 8006EB74 AC4F0000 */   sw    $t7, ($v0)

