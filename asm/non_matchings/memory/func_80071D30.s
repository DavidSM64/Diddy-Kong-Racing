glabel func_80071D30
/* 072930 80071D30 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 072934 80071D34 AFBF0014 */  sw    $ra, 0x14($sp)
/* 072938 80071D38 0C033594 */  jal   __osSiGetAccess
/* 07293C 80071D3C AFA40050 */   sw    $a0, 0x50($sp)
/* 072940 80071D40 8FAF0050 */  lw    $t7, 0x50($sp)
/* 072944 80071D44 240E0003 */  li    $t6, 3
/* 072948 80071D48 3C018013 */  lui   $at, %hi(__osContLastCmd) # $at, 0x8013
/* 07294C 80071D4C A02ECD90 */  sb    $t6, %lo(__osContLastCmd)($at)
/* 072950 80071D50 8DF80008 */  lw    $t8, 8($t7)
/* 072954 80071D54 3C088012 */  lui   $t0, %hi(D_80123DD0) # $t0, 0x8012
/* 072958 80071D58 25083DD0 */  addiu $t0, %lo(D_80123DD0) # addiu $t0, $t0, 0x3dd0
/* 07295C 80071D5C 0018C980 */  sll   $t9, $t8, 6
/* 072960 80071D60 03282821 */  addu  $a1, $t9, $t0
/* 072964 80071D64 0C0335B0 */  jal   __osSiRawStartDma
/* 072968 80071D68 24040001 */   li    $a0, 1
/* 07296C 80071D6C 8FA90050 */  lw    $t1, 0x50($sp)
/* 072970 80071D70 00002825 */  move  $a1, $zero
/* 072974 80071D74 8D240004 */  lw    $a0, 4($t1)
/* 072978 80071D78 0C0322EC */  jal   osRecvMesg
/* 07297C 80071D7C 24060001 */   li    $a2, 1
/* 072980 80071D80 3C058013 */  lui   $a1, %hi(__osPfsPifRam) # $a1, 0x8013
/* 072984 80071D84 24A5CDE0 */  addiu $a1, %lo(__osPfsPifRam) # addiu $a1, $a1, -0x3220
/* 072988 80071D88 0C0335B0 */  jal   __osSiRawStartDma
/* 07298C 80071D8C 00002025 */   move  $a0, $zero
/* 072990 80071D90 8FAA0050 */  lw    $t2, 0x50($sp)
/* 072994 80071D94 00002825 */  move  $a1, $zero
/* 072998 80071D98 8D440004 */  lw    $a0, 4($t2)
/* 07299C 80071D9C 0C0322EC */  jal   osRecvMesg
/* 0729A0 80071DA0 24060001 */   li    $a2, 1
/* 0729A4 80071DA4 8FAB0050 */  lw    $t3, 0x50($sp)
/* 0729A8 80071DA8 3C038013 */  lui   $v1, %hi(__osPfsPifRam) # $v1, 0x8013
/* 0729AC 80071DAC 8D640008 */  lw    $a0, 8($t3)
/* 0729B0 80071DB0 2463CDE0 */  addiu $v1, %lo(__osPfsPifRam) # addiu $v1, $v1, -0x3220
/* 0729B4 80071DB4 10800007 */  beqz  $a0, .L80071DD4
/* 0729B8 80071DB8 27AC001C */   addiu $t4, $sp, 0x1c
/* 0729BC 80071DBC 18800005 */  blez  $a0, .L80071DD4
/* 0729C0 80071DC0 00001025 */   move  $v0, $zero
.L80071DC4:
/* 0729C4 80071DC4 24420001 */  addiu $v0, $v0, 1
/* 0729C8 80071DC8 0044082A */  slt   $at, $v0, $a0
/* 0729CC 80071DCC 1420FFFD */  bnez  $at, .L80071DC4
/* 0729D0 80071DD0 24630001 */   addiu $v1, $v1, 1
.L80071DD4:
/* 0729D4 80071DD4 00607825 */  move  $t7, $v1
/* 0729D8 80071DD8 246E0024 */  addiu $t6, $v1, 0x24
.L80071DDC:
/* 0729DC 80071DDC 89E10000 */  lwl   $at, ($t7)
/* 0729E0 80071DE0 99E10003 */  lwr   $at, 3($t7)
/* 0729E4 80071DE4 25EF000C */  addiu $t7, $t7, 0xc
/* 0729E8 80071DE8 AD810000 */  sw    $at, ($t4)
/* 0729EC 80071DEC 89E1FFF8 */  lwl   $at, -8($t7)
/* 0729F0 80071DF0 99E1FFFB */  lwr   $at, -5($t7)
/* 0729F4 80071DF4 258C000C */  addiu $t4, $t4, 0xc
/* 0729F8 80071DF8 AD81FFF8 */  sw    $at, -8($t4)
/* 0729FC 80071DFC 89E1FFFC */  lwl   $at, -4($t7)
/* 072A00 80071E00 99E1FFFF */  lwr   $at, -1($t7)
/* 072A04 80071E04 15EEFFF5 */  bne   $t7, $t6, .L80071DDC
/* 072A08 80071E08 AD81FFFC */   sw    $at, -4($t4)
/* 072A0C 80071E0C 89E10000 */  lwl   $at, ($t7)
/* 072A10 80071E10 99E10003 */  lwr   $at, 3($t7)
/* 072A14 80071E14 00000000 */  nop   
/* 072A18 80071E18 AD810000 */  sw    $at, ($t4)
/* 072A1C 80071E1C 93A2001E */  lbu   $v0, 0x1e($sp)
/* 072A20 80071E20 93A80042 */  lbu   $t0, 0x42($sp)
/* 072A24 80071E24 305800C0 */  andi  $t8, $v0, 0xc0
/* 072A28 80071E28 00182103 */  sra   $a0, $t8, 4
/* 072A2C 80071E2C 14800004 */  bnez  $a0, .L80071E40
/* 072A30 80071E30 00000000 */   nop   
/* 072A34 80071E34 11000002 */  beqz  $t0, .L80071E40
/* 072A38 80071E38 00000000 */   nop   
/* 072A3C 80071E3C 24040004 */  li    $a0, 4
.L80071E40:
/* 072A40 80071E40 0C0335A5 */  jal   __osSiRelAccess
/* 072A44 80071E44 AFA40048 */   sw    $a0, 0x48($sp)
/* 072A48 80071E48 8FBF0014 */  lw    $ra, 0x14($sp)
/* 072A4C 80071E4C 8FA20048 */  lw    $v0, 0x48($sp)
/* 072A50 80071E50 03E00008 */  jr    $ra
/* 072A54 80071E54 27BD0050 */   addiu $sp, $sp, 0x50

