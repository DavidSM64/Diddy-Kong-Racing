glabel func_80071E58
/* 072A58 80071E58 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 072A5C 80071E5C AFBF0014 */  sw    $ra, 0x14($sp)
/* 072A60 80071E60 0C033594 */  jal   __osSiGetAccess
/* 072A64 80071E64 AFA40050 */   sw    $a0, 0x50($sp)
/* 072A68 80071E68 8FAF0050 */  lw    $t7, 0x50($sp)
/* 072A6C 80071E6C 240E0003 */  li    $t6, 3
/* 072A70 80071E70 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 072A74 80071E74 A02ECD90 */  sb    $t6, %lo(D_8012CD90)($at)
/* 072A78 80071E78 8DF80008 */  lw    $t8, 8($t7)
/* 072A7C 80071E7C 3C088012 */  lui   $t0, %hi(D_80123ED0) # $t0, 0x8012
/* 072A80 80071E80 25083ED0 */  addiu $t0, %lo(D_80123ED0) # addiu $t0, $t0, 0x3ed0
/* 072A84 80071E84 0018C980 */  sll   $t9, $t8, 6
/* 072A88 80071E88 03282821 */  addu  $a1, $t9, $t0
/* 072A8C 80071E8C 0C0335B0 */  jal   __osSiRawStartDma
/* 072A90 80071E90 24040001 */   li    $a0, 1
/* 072A94 80071E94 8FA90050 */  lw    $t1, 0x50($sp)
/* 072A98 80071E98 00002825 */  move  $a1, $zero
/* 072A9C 80071E9C 8D240004 */  lw    $a0, 4($t1)
/* 072AA0 80071EA0 0C0322EC */  jal   osRecvMesg
/* 072AA4 80071EA4 24060001 */   li    $a2, 1
/* 072AA8 80071EA8 3C058013 */  lui   $a1, %hi(D_8012CDE0) # $a1, 0x8013
/* 072AAC 80071EAC 24A5CDE0 */  addiu $a1, %lo(D_8012CDE0) # addiu $a1, $a1, -0x3220
/* 072AB0 80071EB0 0C0335B0 */  jal   __osSiRawStartDma
/* 072AB4 80071EB4 00002025 */   move  $a0, $zero
/* 072AB8 80071EB8 8FAA0050 */  lw    $t2, 0x50($sp)
/* 072ABC 80071EBC 00002825 */  move  $a1, $zero
/* 072AC0 80071EC0 8D440004 */  lw    $a0, 4($t2)
/* 072AC4 80071EC4 0C0322EC */  jal   osRecvMesg
/* 072AC8 80071EC8 24060001 */   li    $a2, 1
/* 072ACC 80071ECC 8FAB0050 */  lw    $t3, 0x50($sp)
/* 072AD0 80071ED0 3C038013 */  lui   $v1, %hi(D_8012CDE0) # $v1, 0x8013
/* 072AD4 80071ED4 8D640008 */  lw    $a0, 8($t3)
/* 072AD8 80071ED8 2463CDE0 */  addiu $v1, %lo(D_8012CDE0) # addiu $v1, $v1, -0x3220
/* 072ADC 80071EDC 10800007 */  beqz  $a0, .L80071EFC
/* 072AE0 80071EE0 27AC001C */   addiu $t4, $sp, 0x1c
/* 072AE4 80071EE4 18800005 */  blez  $a0, .L80071EFC
/* 072AE8 80071EE8 00001025 */   move  $v0, $zero
.L80071EEC:
/* 072AEC 80071EEC 24420001 */  addiu $v0, $v0, 1
/* 072AF0 80071EF0 0044082A */  slt   $at, $v0, $a0
/* 072AF4 80071EF4 1420FFFD */  bnez  $at, .L80071EEC
/* 072AF8 80071EF8 24630001 */   addiu $v1, $v1, 1
.L80071EFC:
/* 072AFC 80071EFC 00607825 */  move  $t7, $v1
/* 072B00 80071F00 246E0024 */  addiu $t6, $v1, 0x24
.L80071F04:
/* 072B04 80071F04 89E10000 */  lwl   $at, ($t7)
/* 072B08 80071F08 99E10003 */  lwr   $at, 3($t7)
/* 072B0C 80071F0C 25EF000C */  addiu $t7, $t7, 0xc
/* 072B10 80071F10 AD810000 */  sw    $at, ($t4)
/* 072B14 80071F14 89E1FFF8 */  lwl   $at, -8($t7)
/* 072B18 80071F18 99E1FFFB */  lwr   $at, -5($t7)
/* 072B1C 80071F1C 258C000C */  addiu $t4, $t4, 0xc
/* 072B20 80071F20 AD81FFF8 */  sw    $at, -8($t4)
/* 072B24 80071F24 89E1FFFC */  lwl   $at, -4($t7)
/* 072B28 80071F28 99E1FFFF */  lwr   $at, -1($t7)
/* 072B2C 80071F2C 15EEFFF5 */  bne   $t7, $t6, .L80071F04
/* 072B30 80071F30 AD81FFFC */   sw    $at, -4($t4)
/* 072B34 80071F34 89E10000 */  lwl   $at, ($t7)
/* 072B38 80071F38 99E10003 */  lwr   $at, 3($t7)
/* 072B3C 80071F3C 00000000 */  nop   
/* 072B40 80071F40 AD810000 */  sw    $at, ($t4)
/* 072B44 80071F44 93A2001E */  lbu   $v0, 0x1e($sp)
/* 072B48 80071F48 93A80042 */  lbu   $t0, 0x42($sp)
/* 072B4C 80071F4C 305800C0 */  andi  $t8, $v0, 0xc0
/* 072B50 80071F50 00182103 */  sra   $a0, $t8, 4
/* 072B54 80071F54 14800004 */  bnez  $a0, .L80071F68
/* 072B58 80071F58 240100EB */   li    $at, 235
/* 072B5C 80071F5C 11010002 */  beq   $t0, $at, .L80071F68
/* 072B60 80071F60 00000000 */   nop   
/* 072B64 80071F64 24040004 */  li    $a0, 4
.L80071F68:
/* 072B68 80071F68 0C0335A5 */  jal   __osSiRelAccess
/* 072B6C 80071F6C AFA40048 */   sw    $a0, 0x48($sp)
/* 072B70 80071F70 8FBF0014 */  lw    $ra, 0x14($sp)
/* 072B74 80071F74 8FA20048 */  lw    $v0, 0x48($sp)
/* 072B78 80071F78 03E00008 */  jr    $ra
/* 072B7C 80071F7C 27BD0050 */   addiu $sp, $sp, 0x50

