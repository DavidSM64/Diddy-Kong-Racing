glabel func_8000E1B8
/* 00EDB8 8000E1B8 3C01800E */  lui   $at, %hi(D_800DC73C) # $at, 0x800e
/* 00EDBC 8000E1BC A020C73C */  sb    $zero, %lo(D_800DC73C)($at)
/* 00EDC0 8000E1C0 3C01800E */  lui   $at, 0x800e
/* 00EDC4 8000E1C4 03E00008 */  jr    $ra
/* 00EDC8 8000E1C8 A020C740 */   sb    $zero, -0x38c0($at)

