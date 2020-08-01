glabel osSetThreadPri
/* 0CD440 800CC840 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0CD444 800CC844 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0CD448 800CC848 AFA40028 */  sw    $a0, 0x28($sp)
/* 0CD44C 800CC84C AFA5002C */  sw    $a1, 0x2c($sp)
/* 0CD450 800CC850 0C034958 */  jal   __osDisableInt
/* 0CD454 800CC854 AFB00018 */   sw    $s0, 0x18($sp)
/* 0CD458 800CC858 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0CD45C 800CC85C 00408025 */  move  $s0, $v0
/* 0CD460 800CC860 15C00004 */  bnez  $t6, .L800CC874
/* 0CD464 800CC864 00000000 */   nop   
/* 0CD468 800CC868 3C0F800E */  lui   $t7, %hi(__osRunningThread) # $t7, 0x800e
/* 0CD46C 800CC86C 8DEF4890 */  lw    $t7, %lo(__osRunningThread)($t7)
/* 0CD470 800CC870 AFAF0028 */  sw    $t7, 0x28($sp)
.L800CC874:
/* 0CD474 800CC874 8FB80028 */  lw    $t8, 0x28($sp)
/* 0CD478 800CC878 8FA8002C */  lw    $t0, 0x2c($sp)
/* 0CD47C 800CC87C 8F190004 */  lw    $t9, 4($t8)
/* 0CD480 800CC880 13280020 */  beq   $t9, $t0, .L800CC904
/* 0CD484 800CC884 00000000 */   nop   
/* 0CD488 800CC888 AF080004 */  sw    $t0, 4($t8)
/* 0CD48C 800CC88C 3C0A800E */  lui   $t2, %hi(__osRunningThread) # $t2, 0x800e
/* 0CD490 800CC890 8D4A4890 */  lw    $t2, %lo(__osRunningThread)($t2)
/* 0CD494 800CC894 8FA90028 */  lw    $t1, 0x28($sp)
/* 0CD498 800CC898 112A000C */  beq   $t1, $t2, .L800CC8CC
/* 0CD49C 800CC89C 00000000 */   nop   
/* 0CD4A0 800CC8A0 952B0010 */  lhu   $t3, 0x10($t1)
/* 0CD4A4 800CC8A4 24010001 */  li    $at, 1
/* 0CD4A8 800CC8A8 11610008 */  beq   $t3, $at, .L800CC8CC
/* 0CD4AC 800CC8AC 00000000 */   nop   
/* 0CD4B0 800CC8B0 8D240008 */  lw    $a0, 8($t1)
/* 0CD4B4 800CC8B4 0C034B1C */  jal   __osDequeueThread
/* 0CD4B8 800CC8B8 01202825 */   move  $a1, $t1
/* 0CD4BC 800CC8BC 8FAC0028 */  lw    $t4, 0x28($sp)
/* 0CD4C0 800CC8C0 8D840008 */  lw    $a0, 8($t4)
/* 0CD4C4 800CC8C4 0C034CF3 */  jal   __osEnqueueThread
/* 0CD4C8 800CC8C8 01802825 */   move  $a1, $t4
.L800CC8CC:
/* 0CD4CC 800CC8CC 3C0D800E */  lui   $t5, %hi(__osRunningThread) # $t5, 0x800e
/* 0CD4D0 800CC8D0 3C0F800E */  lui   $t7, %hi(D_800E4888) # $t7, 0x800e
/* 0CD4D4 800CC8D4 8DEF4888 */  lw    $t7, %lo(D_800E4888)($t7)
/* 0CD4D8 800CC8D8 8DAD4890 */  lw    $t5, %lo(__osRunningThread)($t5)
/* 0CD4DC 800CC8DC 8DF90004 */  lw    $t9, 4($t7)
/* 0CD4E0 800CC8E0 8DAE0004 */  lw    $t6, 4($t5)
/* 0CD4E4 800CC8E4 01D9082A */  slt   $at, $t6, $t9
/* 0CD4E8 800CC8E8 10200006 */  beqz  $at, .L800CC904
/* 0CD4EC 800CC8EC 00000000 */   nop   
/* 0CD4F0 800CC8F0 24080002 */  li    $t0, 2
/* 0CD4F4 800CC8F4 3C04800E */  lui   $a0, %hi(D_800E4888) # $a0, 0x800e
/* 0CD4F8 800CC8F8 A5A80010 */  sh    $t0, 0x10($t5)
/* 0CD4FC 800CC8FC 0C034CB3 */  jal   __osEnqueueAndYield
/* 0CD500 800CC900 24844888 */   addiu $a0, %lo(D_800E4888) # addiu $a0, $a0, 0x4888
.L800CC904:
/* 0CD504 800CC904 0C034960 */  jal   __osRestoreInt
/* 0CD508 800CC908 02002025 */   move  $a0, $s0
/* 0CD50C 800CC90C 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0CD510 800CC910 8FB00018 */  lw    $s0, 0x18($sp)
/* 0CD514 800CC914 27BD0028 */  addiu $sp, $sp, 0x28
/* 0CD518 800CC918 03E00008 */  jr    $ra
/* 0CD51C 800CC91C 00000000 */   nop   

