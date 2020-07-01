glabel func_8007EF64
/* 07FB64 8007EF64 3C188012 */  lui   $t8, %hi(D_8012632C) # $t8, 0x8012
/* 07FB68 8007EF68 8F18632C */  lw    $t8, %lo(D_8012632C)($t8)
/* 07FB6C 8007EF6C 00047400 */  sll   $t6, $a0, 0x10
/* 07FB70 8007EF70 000E7C03 */  sra   $t7, $t6, 0x10
/* 07FB74 8007EF74 AFA40000 */  sw    $a0, ($sp)
/* 07FB78 8007EF78 03E00008 */  jr    $ra
/* 07FB7C 8007EF7C 01F81021 */   addu  $v0, $t7, $t8

