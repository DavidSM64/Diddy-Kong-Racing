glabel func_8006EBA8
/* 06F7A8 8006EBA8 3C02800E */  lui   $v0, %hi(D_800DD37C) # $v0, 0x800e
/* 06F7AC 8006EBAC 2442D37C */  addiu $v0, %lo(D_800DD37C) # addiu $v0, $v0, -0x2c84
/* 06F7B0 8006EBB0 8C4E0000 */  lw    $t6, ($v0)
/* 06F7B4 8006EBB4 00000000 */  nop   
/* 06F7B8 8006EBB8 35CF0008 */  ori   $t7, $t6, 8
/* 06F7BC 8006EBBC 03E00008 */  jr    $ra
/* 06F7C0 8006EBC0 AC4F0000 */   sw    $t7, ($v0)

