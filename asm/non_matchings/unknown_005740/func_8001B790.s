glabel func_8001B790
/* 01C390 8001B790 240EFFFF */  li    $t6, -1
/* 01C394 8001B794 3C018012 */  lui   $at, %hi(D_8011D5AC) # $at, 0x8012
/* 01C398 8001B798 A42ED5AC */  sh    $t6, %lo(D_8011D5AC)($at)
/* 01C39C 8001B79C 3C01800E */  lui   $at, 0x800e
/* 01C3A0 8001B7A0 03E00008 */  jr    $ra
/* 01C3A4 8001B7A4 A020C730 */   sb    $zero, -0x38d0($at)

