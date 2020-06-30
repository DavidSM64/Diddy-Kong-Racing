glabel func_8006EBE0
/* 06F7E0 8006EBE0 3C02800E */  lui   $v0, %hi(D_800DD37C) # $v0, 0x800e
/* 06F7E4 8006EBE4 2442D37C */  addiu $v0, %lo(D_800DD37C) # addiu $v0, $v0, -0x2c84
/* 06F7E8 8006EBE8 8C4E0000 */  lw    $t6, ($v0)
/* 06F7EC 8006EBEC 00000000 */  nop   
/* 06F7F0 8006EBF0 35CF0020 */  ori   $t7, $t6, 0x20
/* 06F7F4 8006EBF4 03E00008 */  jr    $ra
/* 06F7F8 8006EBF8 AC4F0000 */   sw    $t7, ($v0)

