glabel func_800AB1AC
/* 0ABDAC 800AB1AC 3C0E8012 */  lui   $t6, %hi(D_8012718B) # $t6, 0x8012
/* 0ABDB0 800AB1B0 91CE718B */  lbu   $t6, %lo(D_8012718B)($t6)
/* 0ABDB4 800AB1B4 3C018012 */  lui   $at, %hi(D_80126CD0) # $at, 0x8012
/* 0ABDB8 800AB1B8 A02E6CD0 */  sb    $t6, %lo(D_80126CD0)($at)
/* 0ABDBC 800AB1BC 3C018012 */  lui   $at, 0x8012
/* 0ABDC0 800AB1C0 03E00008 */  jr    $ra
/* 0ABDC4 800AB1C4 A0246CD3 */   sb    $a0, 0x6cd3($at)

/* 0ABDC8 800AB1C8 3C018012 */  lui   $at, 0x8012
/* 0ABDCC 800AB1CC 03E00008 */  jr    $ra
/* 0ABDD0 800AB1D0 A0206CD4 */   sb    $zero, 0x6cd4($at)

