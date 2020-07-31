glabel osCreateViManager
/* 0D2590 800D1990 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0D2594 800D1994 AFB00020 */  sw    $s0, 0x20($sp)
/* 0D2598 800D1998 3C10800E */  lui   $s0, %hi(D_800E38E0) # $s0, 0x800e
/* 0D259C 800D199C 261038E0 */  addiu $s0, %lo(D_800E38E0) # addiu $s0, $s0, 0x38e0
/* 0D25A0 800D19A0 8E0E0000 */  lw    $t6, ($s0)
/* 0D25A4 800D19A4 AFBF0024 */  sw    $ra, 0x24($sp)
/* 0D25A8 800D19A8 AFA40030 */  sw    $a0, 0x30($sp)
/* 0D25AC 800D19AC 55C00052 */  bnezl $t6, .L800D1AF8
/* 0D25B0 800D19B0 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0D25B4 800D19B4 0C0353B0 */  jal   __osTimerServicesInit
/* 0D25B8 800D19B8 00000000 */   nop   
/* 0D25BC 800D19BC 3C048013 */  lui   $a0, %hi(D_8012D130) # $a0, 0x8013
/* 0D25C0 800D19C0 3C058013 */  lui   $a1, %hi(D_8012D148) # $a1, 0x8013
/* 0D25C4 800D19C4 24A5D148 */  addiu $a1, %lo(D_8012D148) # addiu $a1, $a1, -0x2eb8
/* 0D25C8 800D19C8 2484D130 */  addiu $a0, %lo(D_8012D130) # addiu $a0, $a0, -0x2ed0
/* 0D25CC 800D19CC 0C032208 */  jal   osCreateMesgQueue
/* 0D25D0 800D19D0 24060005 */   li    $a2, 5
/* 0D25D4 800D19D4 3C068013 */  lui   $a2, %hi(D_8012D160) # $a2, 0x8013
/* 0D25D8 800D19D8 3C078013 */  lui   $a3, %hi(D_8012D178) # $a3, 0x8013
/* 0D25DC 800D19DC 24E7D178 */  addiu $a3, %lo(D_8012D178) # addiu $a3, $a3, -0x2e88
/* 0D25E0 800D19E0 24C6D160 */  addiu $a2, %lo(D_8012D160) # addiu $a2, $a2, -0x2ea0
/* 0D25E4 800D19E4 240F000D */  li    $t7, 13
/* 0D25E8 800D19E8 2418000E */  li    $t8, 14
/* 0D25EC 800D19EC 3C058013 */  lui   $a1, %hi(D_8012D130) # $a1, 0x8013
/* 0D25F0 800D19F0 A4CF0000 */  sh    $t7, ($a2)
/* 0D25F4 800D19F4 A0C00002 */  sb    $zero, 2($a2)
/* 0D25F8 800D19F8 ACC00004 */  sw    $zero, 4($a2)
/* 0D25FC 800D19FC A4F80000 */  sh    $t8, ($a3)
/* 0D2600 800D1A00 A0E00002 */  sb    $zero, 2($a3)
/* 0D2604 800D1A04 ACE00004 */  sw    $zero, 4($a3)
/* 0D2608 800D1A08 24A5D130 */  addiu $a1, %lo(D_8012D130) # addiu $a1, $a1, -0x2ed0
/* 0D260C 800D1A0C 0C0332EC */  jal   osSetEventMsg
/* 0D2610 800D1A10 24040007 */   li    $a0, 7
/* 0D2614 800D1A14 3C078013 */  lui   $a3, 0x8013
/* 0D2618 800D1A18 3C058013 */  lui   $a1, %hi(D_8012D130) # $a1, 0x8013
/* 0D261C 800D1A1C 24E6D178 */  addiu $a2, $a3, -0x2e88
/* 0D2620 800D1A20 24A5D130 */  addiu $a1, %lo(D_8012D130) # addiu $a1, $a1, -0x2ed0
/* 0D2624 800D1A24 0C0332EC */  jal   osSetEventMsg
/* 0D2628 800D1A28 24040003 */   li    $a0, 3
/* 0D262C 800D1A2C 2419FFFF */  li    $t9, -1
/* 0D2630 800D1A30 AFB90028 */  sw    $t9, 0x28($sp)
/* 0D2634 800D1A34 0C034950 */  jal   osGetThreadPri
/* 0D2638 800D1A38 00002025 */   move  $a0, $zero
/* 0D263C 800D1A3C 8FA80030 */  lw    $t0, 0x30($sp)
/* 0D2640 800D1A40 00002025 */  move  $a0, $zero
/* 0D2644 800D1A44 0048082A */  slt   $at, $v0, $t0
/* 0D2648 800D1A48 10200003 */  beqz  $at, .L800D1A58
/* 0D264C 800D1A4C 01002825 */   move  $a1, $t0
/* 0D2650 800D1A50 0C033210 */  jal   osSetThreadPri
/* 0D2654 800D1A54 AFA20028 */   sw    $v0, 0x28($sp)
.L800D1A58:
/* 0D2658 800D1A58 0C034958 */  jal   __osDisableInt
/* 0D265C 800D1A5C 00000000 */   nop   
/* 0D2660 800D1A60 8FAB0030 */  lw    $t3, 0x30($sp)
/* 0D2664 800D1A64 3C038013 */  lui   $v1, %hi(D_8012D130) # $v1, 0x8013
/* 0D2668 800D1A68 3C048013 */  lui   $a0, %hi(D_8012CE80) # $a0, 0x8013
/* 0D266C 800D1A6C 3C0A8013 */  lui   $t2, %hi(D_8012D130) # $t2, 0x8013
/* 0D2670 800D1A70 2484CE80 */  addiu $a0, %lo(D_8012CE80) # addiu $a0, $a0, -0x3180
/* 0D2674 800D1A74 2463D130 */  addiu $v1, %lo(D_8012D130) # addiu $v1, $v1, -0x2ed0
/* 0D2678 800D1A78 24090001 */  li    $t1, 1
/* 0D267C 800D1A7C 254AD130 */  addiu $t2, %lo(D_8012D130) # addiu $t2, $t2, -0x2ed0
/* 0D2680 800D1A80 3C06800D */  lui   $a2, %hi(viMgrMain) # $a2, 0x800d
/* 0D2684 800D1A84 AFA2002C */  sw    $v0, 0x2c($sp)
/* 0D2688 800D1A88 AE090000 */  sw    $t1, ($s0)
/* 0D268C 800D1A8C AE040004 */  sw    $a0, 4($s0)
/* 0D2690 800D1A90 AE030008 */  sw    $v1, 8($s0)
/* 0D2694 800D1A94 AE03000C */  sw    $v1, 0xc($s0)
/* 0D2698 800D1A98 AE000010 */  sw    $zero, 0x10($s0)
/* 0D269C 800D1A9C AE000014 */  sw    $zero, 0x14($s0)
/* 0D26A0 800D1AA0 AE000018 */  sw    $zero, 0x18($s0)
/* 0D26A4 800D1AA4 24C61B08 */  addiu $a2, %lo(viMgrMain) # addiu $a2, $a2, 0x1b08
/* 0D26A8 800D1AA8 AFAA0010 */  sw    $t2, 0x10($sp)
/* 0D26AC 800D1AAC 00002825 */  move  $a1, $zero
/* 0D26B0 800D1AB0 02003825 */  move  $a3, $s0
/* 0D26B4 800D1AB4 0C032214 */  jal   osCreateThread
/* 0D26B8 800D1AB8 AFAB0014 */   sw    $t3, 0x14($sp)
/* 0D26BC 800D1ABC 0C034AC4 */  jal   __osViInit
/* 0D26C0 800D1AC0 00000000 */   nop   
/* 0D26C4 800D1AC4 3C048013 */  lui   $a0, %hi(D_8012CE80) # $a0, 0x8013
/* 0D26C8 800D1AC8 0C032268 */  jal   osStartThread
/* 0D26CC 800D1ACC 2484CE80 */   addiu $a0, %lo(D_8012CE80) # addiu $a0, $a0, -0x3180
/* 0D26D0 800D1AD0 0C034960 */  jal   __osRestoreInt
/* 0D26D4 800D1AD4 8FA4002C */   lw    $a0, 0x2c($sp)
/* 0D26D8 800D1AD8 8FAC0028 */  lw    $t4, 0x28($sp)
/* 0D26DC 800D1ADC 2401FFFF */  li    $at, -1
/* 0D26E0 800D1AE0 00002025 */  move  $a0, $zero
/* 0D26E4 800D1AE4 51810004 */  beql  $t4, $at, .L800D1AF8
/* 0D26E8 800D1AE8 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0D26EC 800D1AEC 0C033210 */  jal   osSetThreadPri
/* 0D26F0 800D1AF0 01802825 */   move  $a1, $t4
/* 0D26F4 800D1AF4 8FBF0024 */  lw    $ra, 0x24($sp)
.L800D1AF8:
/* 0D26F8 800D1AF8 8FB00020 */  lw    $s0, 0x20($sp)
/* 0D26FC 800D1AFC 27BD0030 */  addiu $sp, $sp, 0x30
/* 0D2700 800D1B00 03E00008 */  jr    $ra
/* 0D2704 800D1B04 00000000 */   nop   

