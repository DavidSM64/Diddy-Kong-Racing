glabel func_80080E6C
/* 081A6C 80080E6C 3C02800E */  lui   $v0, %hi(D_800E1DB4) # $v0, 0x800e
/* 081A70 80080E70 3C01800E */  lui   $at, %hi(D_800E1DB8) # $at, 0x800e
/* 081A74 80080E74 24421DB4 */  addiu $v0, %lo(D_800E1DB4) # addiu $v0, $v0, 0x1db4
/* 081A78 80080E78 AC201DB8 */  sw    $zero, %lo(D_800E1DB8)($at)
/* 081A7C 80080E7C 8C4E0000 */  lw    $t6, ($v0)
/* 081A80 80080E80 240F0001 */  li    $t7, 1
/* 081A84 80080E84 01EEC023 */  subu  $t8, $t7, $t6
/* 081A88 80080E88 03E00008 */  jr    $ra
/* 081A8C 80080E8C AC580000 */   sw    $t8, ($v0)

