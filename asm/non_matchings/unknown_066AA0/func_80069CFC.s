glabel func_80069CFC
/* 06A8FC 80069CFC 3C0E8012 */  lui   $t6, %hi(D_80120CE4) # $t6, 0x8012
/* 06A900 80069D00 8DCE0CE4 */  lw    $t6, %lo(D_80120CE4)($t6)
/* 06A904 80069D04 3C188012 */  lui   $t8, %hi(D_80120AC0) # $t8, 0x8012
/* 06A908 80069D08 000E7900 */  sll   $t7, $t6, 4
/* 06A90C 80069D0C 01EE7821 */  addu  $t7, $t7, $t6
/* 06A910 80069D10 000F7880 */  sll   $t7, $t7, 2
/* 06A914 80069D14 27180AC0 */  addiu $t8, %lo(D_80120AC0) # addiu $t8, $t8, 0xac0
/* 06A918 80069D18 03E00008 */  jr    $ra
/* 06A91C 80069D1C 01F81021 */   addu  $v0, $t7, $t8

