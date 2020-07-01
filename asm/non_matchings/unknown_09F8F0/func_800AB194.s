glabel func_800AB194
/* 0ABD94 800AB194 240E0001 */  li    $t6, 1
/* 0ABD98 800AB198 3C018012 */  lui   $at, %hi(D_80126CD1) # $at, 0x8012
/* 0ABD9C 800AB19C A02E6CD1 */  sb    $t6, %lo(D_80126CD1)($at)
/* 0ABDA0 800AB1A0 3C018012 */  lui   $at, 0x8012
/* 0ABDA4 800AB1A4 03E00008 */  jr    $ra
/* 0ABDA8 800AB1A8 A0246CD3 */   sb    $a0, 0x6cd3($at)

