glabel __initFromBank
/* 00B8E0 8000ACE0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 00B8E4 8000ACE4 AFB20020 */  sw    $s2, 0x20($sp)
/* 00B8E8 8000ACE8 00809025 */  move  $s2, $a0
/* 00B8EC 8000ACEC AFBF0024 */  sw    $ra, 0x24($sp)
/* 00B8F0 8000ACF0 AFB1001C */  sw    $s1, 0x1c($sp)
/* 00B8F4 8000ACF4 AFB00018 */  sw    $s0, 0x18($sp)
/* 00B8F8 8000ACF8 AFA5002C */  sw    $a1, 0x2c($sp)
/* 00B8FC 8000ACFC 00A01025 */  move  $v0, $a1
.L8000AD00:
/* 00B900 8000AD00 8C51000C */  lw    $s1, 0xc($v0)
/* 00B904 8000AD04 24420004 */  addiu $v0, $v0, 4
/* 00B908 8000AD08 1220FFFD */  beqz  $s1, .L8000AD00
/* 00B90C 8000AD0C 00000000 */   nop   
/* 00B910 8000AD10 924E0034 */  lbu   $t6, 0x34($s2)
/* 00B914 8000AD14 00008025 */  move  $s0, $zero
/* 00B918 8000AD18 19C0000C */  blez  $t6, .L8000AD4C
/* 00B91C 8000AD1C 02402025 */   move  $a0, $s2
.L8000AD20:
/* 00B920 8000AD20 0C002B7D */  jal   __resetPerfChanState
/* 00B924 8000AD24 02002825 */   move  $a1, $s0
/* 00B928 8000AD28 02402025 */  move  $a0, $s2
/* 00B92C 8000AD2C 02202825 */  move  $a1, $s1
/* 00B930 8000AD30 0C002B66 */  jal   __setInstChanState
/* 00B934 8000AD34 02003025 */   move  $a2, $s0
/* 00B938 8000AD38 924F0034 */  lbu   $t7, 0x34($s2)
/* 00B93C 8000AD3C 26100001 */  addiu $s0, $s0, 1
/* 00B940 8000AD40 020F082A */  slt   $at, $s0, $t7
/* 00B944 8000AD44 1420FFF6 */  bnez  $at, .L8000AD20
/* 00B948 8000AD48 02402025 */   move  $a0, $s2
.L8000AD4C:
/* 00B94C 8000AD4C 8FB8002C */  lw    $t8, 0x2c($sp)
/* 00B950 8000AD50 02402025 */  move  $a0, $s2
/* 00B954 8000AD54 8F190008 */  lw    $t9, 8($t8)
/* 00B958 8000AD58 00000000 */  nop   
/* 00B95C 8000AD5C 13200009 */  beqz  $t9, .L8000AD84
/* 00B960 8000AD60 8FBF0024 */   lw    $ra, 0x24($sp)
/* 00B964 8000AD64 0C002B7D */  jal   __resetPerfChanState
/* 00B968 8000AD68 02002825 */   move  $a1, $s0
/* 00B96C 8000AD6C 8FA8002C */  lw    $t0, 0x2c($sp)
/* 00B970 8000AD70 02402025 */  move  $a0, $s2
/* 00B974 8000AD74 8D050008 */  lw    $a1, 8($t0)
/* 00B978 8000AD78 0C002B66 */  jal   __setInstChanState
/* 00B97C 8000AD7C 24060009 */   li    $a2, 9
/* 00B980 8000AD80 8FBF0024 */  lw    $ra, 0x24($sp)
.L8000AD84:
/* 00B984 8000AD84 8FB00018 */  lw    $s0, 0x18($sp)
/* 00B988 8000AD88 8FB1001C */  lw    $s1, 0x1c($sp)
/* 00B98C 8000AD8C 8FB20020 */  lw    $s2, 0x20($sp)
/* 00B990 8000AD90 03E00008 */  jr    $ra
/* 00B994 8000AD94 27BD0028 */   addiu $sp, $sp, 0x28

