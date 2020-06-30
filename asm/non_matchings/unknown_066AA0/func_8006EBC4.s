glabel func_8006EBC4
/* 06F7C4 8006EBC4 3C02800E */  lui   $v0, %hi(D_800DD37C) # $v0, 0x800e
/* 06F7C8 8006EBC8 2442D37C */  addiu $v0, %lo(D_800DD37C) # addiu $v0, $v0, -0x2c84
/* 06F7CC 8006EBCC 8C4E0000 */  lw    $t6, ($v0)
/* 06F7D0 8006EBD0 00000000 */  nop   
/* 06F7D4 8006EBD4 35CF0010 */  ori   $t7, $t6, 0x10
/* 06F7D8 8006EBD8 03E00008 */  jr    $ra
/* 06F7DC 8006EBDC AC4F0000 */   sw    $t7, ($v0)

