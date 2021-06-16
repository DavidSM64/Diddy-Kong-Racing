glabel func_8005CB04
/* 05D704 8005CB04 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 05D708 8005CB08 AFBF0014 */  sw    $ra, 0x14($sp)
/* 05D70C 8005CB0C 00803025 */  move  $a2, $a0
/* 05D710 8005CB10 AFA60018 */  sw    $a2, 0x18($sp)
/* 05D714 8005CB14 00002025 */  move  $a0, $zero
/* 05D718 8005CB18 0C01BE53 */  jal   get_random_number_from_range
/* 05D71C 8005CB1C 24050001 */   li    $a1, 1
/* 05D720 8005CB20 8FA60018 */  lw    $a2, 0x18($sp)
/* 05D724 8005CB24 00021E00 */  sll   $v1, $v0, 0x18
/* 05D728 8005CB28 00037603 */  sra   $t6, $v1, 0x18
/* 05D72C 8005CB2C 14C00002 */  bnez  $a2, .L8005CB38
/* 05D730 8005CB30 01C01825 */   move  $v1, $t6
/* 05D734 8005CB34 00001825 */  move  $v1, $zero
.L8005CB38:
/* 05D738 8005CB38 3C0F8012 */  lui   $t7, %hi(D_8011D5C8) # $t7, 0x8012
/* 05D73C 8005CB3C 8DEFD5C8 */  lw    $t7, %lo(D_8011D5C8)($t7)
/* 05D740 8005CB40 00C33021 */  addu  $a2, $a2, $v1
/* 05D744 8005CB44 0006C040 */  sll   $t8, $a2, 1
/* 05D748 8005CB48 01F8C821 */  addu  $t9, $t7, $t8
/* 05D74C 8005CB4C 97240000 */  lhu   $a0, ($t9)
/* 05D750 8005CB50 0C000741 */  jal   func_80001D04
/* 05D754 8005CB54 00002825 */   move  $a1, $zero
/* 05D758 8005CB58 8FBF0014 */  lw    $ra, 0x14($sp)
/* 05D75C 8005CB5C 27BD0018 */  addiu $sp, $sp, 0x18
/* 05D760 8005CB60 03E00008 */  jr    $ra
/* 05D764 8005CB64 00000000 */   nop   

