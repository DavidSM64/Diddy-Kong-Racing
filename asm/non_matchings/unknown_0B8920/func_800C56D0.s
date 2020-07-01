glabel func_800C56D0
/* 0C62D0 800C56D0 3C0E8013 */  lui   $t6, %hi(D_8012A7E8) # $t6, 0x8013
/* 0C62D4 800C56D4 00047880 */  sll   $t7, $a0, 2
/* 0C62D8 800C56D8 8DCEA7E8 */  lw    $t6, %lo(D_8012A7E8)($t6)
/* 0C62DC 800C56DC 01E47821 */  addu  $t7, $t7, $a0
/* 0C62E0 800C56E0 000F78C0 */  sll   $t7, $t7, 3
/* 0C62E4 800C56E4 01CF1021 */  addu  $v0, $t6, $t7
/* 0C62E8 800C56E8 9458001E */  lhu   $t8, 0x1e($v0)
/* 0C62EC 800C56EC 00000000 */  nop   
/* 0C62F0 800C56F0 3319BFFF */  andi  $t9, $t8, 0xbfff
/* 0C62F4 800C56F4 03E00008 */  jr    $ra
/* 0C62F8 800C56F8 A459001E */   sh    $t9, 0x1e($v0)

