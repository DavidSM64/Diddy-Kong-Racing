glabel __initChanState
/* 00BA90 8000AE90 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 00BA94 8000AE94 AFBF0024 */  sw    $ra, 0x24($sp)
/* 00BA98 8000AE98 AFB20020 */  sw    $s2, 0x20($sp)
/* 00BA9C 8000AE9C AFB1001C */  sw    $s1, 0x1c($sp)
/* 00BAA0 8000AEA0 AFB00018 */  sw    $s0, 0x18($sp)
/* 00BAA4 8000AEA4 908E0034 */  lbu   $t6, 0x34($a0)
/* 00BAA8 8000AEA8 00808825 */  move  $s1, $a0
/* 00BAAC 8000AEAC 19C0000D */  blez  $t6, .L8000AEE4
/* 00BAB0 8000AEB0 00008025 */   move  $s0, $zero
/* 00BAB4 8000AEB4 00009025 */  move  $s2, $zero
.L8000AEB8:
/* 00BAB8 8000AEB8 8E2F0060 */  lw    $t7, 0x60($s1)
/* 00BABC 8000AEBC 02202025 */  move  $a0, $s1
/* 00BAC0 8000AEC0 01F2C021 */  addu  $t8, $t7, $s2
/* 00BAC4 8000AEC4 AF000000 */  sw    $zero, ($t8)
/* 00BAC8 8000AEC8 0C002B7D */  jal   func_8000ADF4
/* 00BACC 8000AECC 02002825 */   move  $a1, $s0
/* 00BAD0 8000AED0 92390034 */  lbu   $t9, 0x34($s1)
/* 00BAD4 8000AED4 26100001 */  addiu $s0, $s0, 1
/* 00BAD8 8000AED8 0219082A */  slt   $at, $s0, $t9
/* 00BADC 8000AEDC 1420FFF6 */  bnez  $at, .L8000AEB8
/* 00BAE0 8000AEE0 26520014 */   addiu $s2, $s2, 0x14
.L8000AEE4:
/* 00BAE4 8000AEE4 8FBF0024 */  lw    $ra, 0x24($sp)
/* 00BAE8 8000AEE8 8FB00018 */  lw    $s0, 0x18($sp)
/* 00BAEC 8000AEEC 8FB1001C */  lw    $s1, 0x1c($sp)
/* 00BAF0 8000AEF0 8FB20020 */  lw    $s2, 0x20($sp)
/* 00BAF4 8000AEF4 03E00008 */  jr    $ra
/* 00BAF8 8000AEF8 27BD0028 */   addiu $sp, $sp, 0x28

