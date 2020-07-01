glabel func_8000E194
/* 00ED94 8000E194 3C02800E */  lui   $v0, %hi(D_800DC73C) # $v0, 0x800e
/* 00ED98 8000E198 2442C73C */  addiu $v0, %lo(D_800DC73C) # addiu $v0, $v0, -0x38c4
/* 00ED9C 8000E19C 804E0000 */  lb    $t6, ($v0)
/* 00EDA0 8000E1A0 240F0001 */  li    $t7, 1
/* 00EDA4 8000E1A4 01EEC023 */  subu  $t8, $t7, $t6
/* 00EDA8 8000E1A8 A0580000 */  sb    $t8, ($v0)
/* 00EDAC 8000E1AC 3C01800E */  lui   $at, 0x800e
/* 00EDB0 8000E1B0 03E00008 */  jr    $ra
/* 00EDB4 8000E1B4 A020C740 */   sb    $zero, -0x38c0($at)

