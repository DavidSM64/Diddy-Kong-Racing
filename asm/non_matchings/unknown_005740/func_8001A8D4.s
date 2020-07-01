glabel func_8001A8D4
/* 01B4D4 8001A8D4 240E012C */  li    $t6, 300
/* 01B4D8 8001A8D8 3C018012 */  lui   $at, %hi(D_8011AD4E) # $at, 0x8012
/* 01B4DC 8001A8DC A42EAD4E */  sh    $t6, %lo(D_8011AD4E)($at)
/* 01B4E0 8001A8E0 3C018012 */  lui   $at, %hi(D_8011AD50) # $at, 0x8012
/* 01B4E4 8001A8E4 A020AD50 */  sb    $zero, %lo(D_8011AD50)($at)
/* 01B4E8 8001A8E8 3C018012 */  lui   $at, 0x8012
/* 01B4EC 8001A8EC 03E00008 */  jr    $ra
/* 01B4F0 8001A8F0 A024AD52 */   sb    $a0, -0x52ae($at)

