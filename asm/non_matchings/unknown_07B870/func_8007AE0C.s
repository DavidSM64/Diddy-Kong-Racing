glabel func_8007AE0C
/* 07BA0C 8007AE0C 3C028012 */  lui   $v0, %hi(D_80126378) # $v0, 0x8012
/* 07BA10 8007AE10 24426378 */  addiu $v0, %lo(D_80126378) # addiu $v0, $v0, 0x6378
/* 07BA14 8007AE14 8C4E0000 */  lw    $t6, ($v0)
/* 07BA18 8007AE18 00000000 */  nop   
/* 07BA1C 8007AE1C 01C47825 */  or    $t7, $t6, $a0
/* 07BA20 8007AE20 03E00008 */  jr    $ra
/* 07BA24 8007AE24 AC4F0000 */   sw    $t7, ($v0)

