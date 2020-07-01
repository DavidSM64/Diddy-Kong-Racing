glabel func_8001BA00
/* 01C600 8001BA00 00047100 */  sll   $t6, $a0, 4
/* 01C604 8001BA04 3C0F8012 */  lui   $t7, %hi(D_8011AECC) # $t7, 0x8012
/* 01C608 8001BA08 8DEFAECC */  lw    $t7, %lo(D_8011AECC)($t7)
/* 01C60C 8001BA0C 01C47023 */  subu  $t6, $t6, $a0
/* 01C610 8001BA10 000E7080 */  sll   $t6, $t6, 2
/* 01C614 8001BA14 03E00008 */  jr    $ra
/* 01C618 8001BA18 01CF1021 */   addu  $v0, $t6, $t7

