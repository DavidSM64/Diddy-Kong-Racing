glabel func_800CDB20
/* 0CE720 800CDB20 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 0CE724 800CDB24 3C0E8013 */  lui   $t6, %hi(D_8012CDE0) # $t6, 0x8013
/* 0CE728 800CDB28 25CECDE0 */  addiu $t6, %lo(D_8012CDE0) # addiu $t6, $t6, -0x3220
/* 0CE72C 800CDB2C AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CE730 800CDB30 AFA40048 */  sw    $a0, 0x48($sp)
/* 0CE734 800CDB34 AFA5004C */  sw    $a1, 0x4c($sp)
/* 0CE738 800CDB38 AFA60050 */  sw    $a2, 0x50($sp)
/* 0CE73C 800CDB3C AFAE0044 */  sw    $t6, 0x44($sp)
/* 0CE740 800CDB40 AFA00018 */  sw    $zero, 0x18($sp)
.L800CDB44:
/* 0CE744 800CDB44 8FAF0018 */  lw    $t7, 0x18($sp)
/* 0CE748 800CDB48 8FB90018 */  lw    $t9, 0x18($sp)
/* 0CE74C 800CDB4C 3C018013 */  lui   $at, 0x8013
/* 0CE750 800CDB50 000FC080 */  sll   $t8, $t7, 2
/* 0CE754 800CDB54 00380821 */  addu  $at, $at, $t8
/* 0CE758 800CDB58 AC20CDE0 */  sw    $zero, -0x3220($at)
/* 0CE75C 800CDB5C 27280001 */  addiu $t0, $t9, 1
/* 0CE760 800CDB60 29010010 */  slti  $at, $t0, 0x10
/* 0CE764 800CDB64 1420FFF7 */  bnez  $at, .L800CDB44
/* 0CE768 800CDB68 AFA80018 */   sw    $t0, 0x18($sp)
/* 0CE76C 800CDB6C 24090001 */  li    $t1, 1
/* 0CE770 800CDB70 3C018013 */  lui   $at, %hi(D_8012CE1C) # $at, 0x8013
/* 0CE774 800CDB74 240A00FF */  li    $t2, 255
/* 0CE778 800CDB78 240B0023 */  li    $t3, 35
/* 0CE77C 800CDB7C 240C0001 */  li    $t4, 1
/* 0CE780 800CDB80 240D0003 */  li    $t5, 3
/* 0CE784 800CDB84 AC29CE1C */  sw    $t1, %lo(D_8012CE1C)($at)
/* 0CE788 800CDB88 A3AA001C */  sb    $t2, 0x1c($sp)
/* 0CE78C 800CDB8C A3AB001D */  sb    $t3, 0x1d($sp)
/* 0CE790 800CDB90 A3AC001E */  sb    $t4, 0x1e($sp)
/* 0CE794 800CDB94 A3AD001F */  sb    $t5, 0x1f($sp)
/* 0CE798 800CDB98 0C0335DC */  jal   func_800CD770
/* 0CE79C 800CDB9C 97A4004E */   lhu   $a0, 0x4e($sp)
/* 0CE7A0 800CDBA0 97AE004E */  lhu   $t6, 0x4e($sp)
/* 0CE7A4 800CDBA4 241900FF */  li    $t9, 255
/* 0CE7A8 800CDBA8 A3B90042 */  sb    $t9, 0x42($sp)
/* 0CE7AC 800CDBAC 000E7940 */  sll   $t7, $t6, 5
/* 0CE7B0 800CDBB0 004FC025 */  or    $t8, $v0, $t7
/* 0CE7B4 800CDBB4 A7B80020 */  sh    $t8, 0x20($sp)
/* 0CE7B8 800CDBB8 AFA00018 */  sw    $zero, 0x18($sp)
.L800CDBBC:
/* 0CE7BC 800CDBBC 8FA80050 */  lw    $t0, 0x50($sp)
/* 0CE7C0 800CDBC0 8FAA0018 */  lw    $t2, 0x18($sp)
/* 0CE7C4 800CDBC4 91090000 */  lbu   $t1, ($t0)
/* 0CE7C8 800CDBC8 03AA5821 */  addu  $t3, $sp, $t2
/* 0CE7CC 800CDBCC A1690022 */  sb    $t1, 0x22($t3)
/* 0CE7D0 800CDBD0 8FAE0018 */  lw    $t6, 0x18($sp)
/* 0CE7D4 800CDBD4 8FAC0050 */  lw    $t4, 0x50($sp)
/* 0CE7D8 800CDBD8 25CF0001 */  addiu $t7, $t6, 1
/* 0CE7DC 800CDBDC 29E10020 */  slti  $at, $t7, 0x20
/* 0CE7E0 800CDBE0 258D0001 */  addiu $t5, $t4, 1
/* 0CE7E4 800CDBE4 AFAF0018 */  sw    $t7, 0x18($sp)
/* 0CE7E8 800CDBE8 1420FFF4 */  bnez  $at, .L800CDBBC
/* 0CE7EC 800CDBEC AFAD0050 */   sw    $t5, 0x50($sp)
/* 0CE7F0 800CDBF0 8FB80048 */  lw    $t8, 0x48($sp)
/* 0CE7F4 800CDBF4 1300000E */  beqz  $t8, .L800CDC30
/* 0CE7F8 800CDBF8 00000000 */   nop   
/* 0CE7FC 800CDBFC 1B00000C */  blez  $t8, .L800CDC30
/* 0CE800 800CDC00 AFA00018 */   sw    $zero, 0x18($sp)
.L800CDC04:
/* 0CE804 800CDC04 8FB90044 */  lw    $t9, 0x44($sp)
/* 0CE808 800CDC08 A3200000 */  sb    $zero, ($t9)
/* 0CE80C 800CDC0C 8FAA0018 */  lw    $t2, 0x18($sp)
/* 0CE810 800CDC10 8FAC0048 */  lw    $t4, 0x48($sp)
/* 0CE814 800CDC14 8FA80044 */  lw    $t0, 0x44($sp)
/* 0CE818 800CDC18 254B0001 */  addiu $t3, $t2, 1
/* 0CE81C 800CDC1C 016C082A */  slt   $at, $t3, $t4
/* 0CE820 800CDC20 25090001 */  addiu $t1, $t0, 1
/* 0CE824 800CDC24 AFAB0018 */  sw    $t3, 0x18($sp)
/* 0CE828 800CDC28 1420FFF6 */  bnez  $at, .L800CDC04
/* 0CE82C 800CDC2C AFA90044 */   sw    $t1, 0x44($sp)
.L800CDC30:
/* 0CE830 800CDC30 27AE001C */  addiu $t6, $sp, 0x1c
/* 0CE834 800CDC34 25D80024 */  addiu $t8, $t6, 0x24
/* 0CE838 800CDC38 8FAD0044 */  lw    $t5, 0x44($sp)
.L800CDC3C:
/* 0CE83C 800CDC3C 8DC10000 */  lw    $at, ($t6)
/* 0CE840 800CDC40 25CE000C */  addiu $t6, $t6, 0xc
/* 0CE844 800CDC44 25AD000C */  addiu $t5, $t5, 0xc
/* 0CE848 800CDC48 A9A1FFF4 */  swl   $at, -0xc($t5)
/* 0CE84C 800CDC4C B9A1FFF7 */  swr   $at, -9($t5)
/* 0CE850 800CDC50 8DC1FFF8 */  lw    $at, -8($t6)
/* 0CE854 800CDC54 A9A1FFF8 */  swl   $at, -8($t5)
/* 0CE858 800CDC58 B9A1FFFB */  swr   $at, -5($t5)
/* 0CE85C 800CDC5C 8DC1FFFC */  lw    $at, -4($t6)
/* 0CE860 800CDC60 A9A1FFFC */  swl   $at, -4($t5)
/* 0CE864 800CDC64 15D8FFF5 */  bne   $t6, $t8, .L800CDC3C
/* 0CE868 800CDC68 B9A1FFFF */   swr   $at, -1($t5)
/* 0CE86C 800CDC6C 8DC10000 */  lw    $at, ($t6)
/* 0CE870 800CDC70 240900FE */  li    $t1, 254
/* 0CE874 800CDC74 A9A10000 */  swl   $at, ($t5)
/* 0CE878 800CDC78 B9A10003 */  swr   $at, 3($t5)
/* 0CE87C 800CDC7C 8FB90044 */  lw    $t9, 0x44($sp)
/* 0CE880 800CDC80 27280028 */  addiu $t0, $t9, 0x28
/* 0CE884 800CDC84 AFA80044 */  sw    $t0, 0x44($sp)
/* 0CE888 800CDC88 A1090000 */  sb    $t1, ($t0)
/* 0CE88C 800CDC8C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CE890 800CDC90 27BD0048 */  addiu $sp, $sp, 0x48
/* 0CE894 800CDC94 03E00008 */  jr    $ra
/* 0CE898 800CDC98 00000000 */   nop   

/* 0CE89C 800CDC9C 00000000 */  nop   

