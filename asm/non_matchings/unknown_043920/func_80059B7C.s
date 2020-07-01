glabel func_80059B7C
/* 05A77C 80059B7C 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 05A780 80059B80 3C028012 */  lui   $v0, %hi(D_8011D59C) # $v0, 0x8012
/* 05A784 80059B84 8042D59C */  lb    $v0, %lo(D_8011D59C)($v0)
/* 05A788 80059B88 3C0A8012 */  lui   $t2, 0x8012
/* 05A78C 80059B8C 3C0C8012 */  lui   $t4, 0x8012
/* 05A790 80059B90 00024840 */  sll   $t1, $v0, 1
/* 05A794 80059B94 00025880 */  sll   $t3, $v0, 2
/* 05A798 80059B98 018B6021 */  addu  $t4, $t4, $t3
/* 05A79C 80059B9C 01495021 */  addu  $t2, $t2, $t1
/* 05A7A0 80059BA0 854AD5A0 */  lh    $t2, -0x2a60($t2)
/* 05A7A4 80059BA4 8D8CD590 */  lw    $t4, -0x2a70($t4)
/* 05A7A8 80059BA8 87A8003A */  lh    $t0, 0x3a($sp)
/* 05A7AC 80059BAC AFA5002C */  sw    $a1, 0x2c($sp)
/* 05A7B0 80059BB0 AFBF0024 */  sw    $ra, 0x24($sp)
/* 05A7B4 80059BB4 AFA60030 */  sw    $a2, 0x30($sp)
/* 05A7B8 80059BB8 AFA70034 */  sw    $a3, 0x34($sp)
/* 05A7BC 80059BBC 00067400 */  sll   $t6, $a2, 0x10
/* 05A7C0 80059BC0 0007C400 */  sll   $t8, $a3, 0x10
/* 05A7C4 80059BC4 87A5002E */  lh    $a1, 0x2e($sp)
/* 05A7C8 80059BC8 00183C03 */  sra   $a3, $t8, 0x10
/* 05A7CC 80059BCC 000E3403 */  sra   $a2, $t6, 0x10
/* 05A7D0 80059BD0 AFAA0014 */  sw    $t2, 0x14($sp)
/* 05A7D4 80059BD4 AFAC0018 */  sw    $t4, 0x18($sp)
/* 05A7D8 80059BD8 0C01D400 */  jal   func_80075000
/* 05A7DC 80059BDC AFA80010 */   sw    $t0, 0x10($sp)
/* 05A7E0 80059BE0 8FBF0024 */  lw    $ra, 0x24($sp)
/* 05A7E4 80059BE4 27BD0028 */  addiu $sp, $sp, 0x28
/* 05A7E8 80059BE8 03E00008 */  jr    $ra
/* 05A7EC 80059BEC 00000000 */   nop   

