glabel func_80071198
/* 071D98 80071198 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 071D9C 8007119C AFBF0024 */  sw    $ra, 0x24($sp)
/* 071DA0 800711A0 AFB20020 */  sw    $s2, 0x20($sp)
/* 071DA4 800711A4 AFB1001C */  sw    $s1, 0x1c($sp)
/* 071DA8 800711A8 0C01BD44 */  jal   func_8006F510
/* 071DAC 800711AC AFB00018 */   sw    $s0, 0x18($sp)
/* 071DB0 800711B0 3C118012 */  lui   $s1, %hi(gFreeQueueCount) # $s1, 0x8012
/* 071DB4 800711B4 26313DC8 */  addiu $s1, %lo(gFreeQueueCount) # addiu $s1, $s1, 0x3dc8
/* 071DB8 800711B8 8E230000 */  lw    $v1, ($s1)
/* 071DBC 800711BC AFA20028 */  sw    $v0, 0x28($sp)
/* 071DC0 800711C0 18600024 */  blez  $v1, .L80071254
/* 071DC4 800711C4 3C108012 */   lui   $s0, %hi(gFreeQueue) # $s0, 0x8012
/* 071DC8 800711C8 3C128012 */  lui   $s2, %hi(gFreeQueue) # $s2, 0x8012
/* 071DCC 800711CC 265235C8 */  addiu $s2, %lo(gFreeQueue) # addiu $s2, $s2, 0x35c8
/* 071DD0 800711D0 261035C8 */  addiu $s0, %lo(gFreeQueue) # addiu $s0, $s0, 0x35c8
.L800711D4:
/* 071DD4 800711D4 920E0004 */  lbu   $t6, 4($s0)
/* 071DD8 800711D8 00000000 */  nop   
/* 071DDC 800711DC 25CFFFFF */  addiu $t7, $t6, -1
/* 071DE0 800711E0 31F800FF */  andi  $t8, $t7, 0xff
/* 071DE4 800711E4 17000013 */  bnez  $t8, .L80071234
/* 071DE8 800711E8 A20F0004 */   sb    $t7, 4($s0)
/* 071DEC 800711EC 8E040000 */  lw    $a0, ($s0)
/* 071DF0 800711F0 0C01C49E */  jal   free_slot_containing_address
/* 071DF4 800711F4 00000000 */   nop   
/* 071DF8 800711F8 8E230000 */  lw    $v1, ($s1)
/* 071DFC 800711FC 3C0C8012 */  lui   $t4, %hi(gFreeQueue) # $t4, 0x8012
/* 071E00 80071200 0003C8C0 */  sll   $t9, $v1, 3
/* 071E04 80071204 02591021 */  addu  $v0, $s2, $t9
/* 071E08 80071208 8C48FFF8 */  lw    $t0, -8($v0)
/* 071E0C 8007120C 246AFFFF */  addiu $t2, $v1, -1
/* 071E10 80071210 AE080000 */  sw    $t0, ($s0)
/* 071E14 80071214 9049FFFC */  lbu   $t1, -4($v0)
/* 071E18 80071218 000A58C0 */  sll   $t3, $t2, 3
/* 071E1C 8007121C 258C35C8 */  addiu $t4, %lo(gFreeQueue) # addiu $t4, $t4, 0x35c8
/* 071E20 80071220 016C2021 */  addu  $a0, $t3, $t4
/* 071E24 80071224 AE2A0000 */  sw    $t2, ($s1)
/* 071E28 80071228 01401825 */  move  $v1, $t2
/* 071E2C 8007122C 10000006 */  b     .L80071248
/* 071E30 80071230 A2090004 */   sb    $t1, 4($s0)
.L80071234:
/* 071E34 80071234 3C0E8012 */  lui   $t6, %hi(gFreeQueue) # $t6, 0x8012
/* 071E38 80071238 25CE35C8 */  addiu $t6, %lo(gFreeQueue) # addiu $t6, $t6, 0x35c8
/* 071E3C 8007123C 000368C0 */  sll   $t5, $v1, 3
/* 071E40 80071240 01AE2021 */  addu  $a0, $t5, $t6
/* 071E44 80071244 26100008 */  addiu $s0, $s0, 8
.L80071248:
/* 071E48 80071248 0204082B */  sltu  $at, $s0, $a0
/* 071E4C 8007124C 1420FFE1 */  bnez  $at, .L800711D4
/* 071E50 80071250 00000000 */   nop   
.L80071254:
/* 071E54 80071254 8FA40028 */  lw    $a0, 0x28($sp)
/* 071E58 80071258 0C01BD4F */  jal   func_8006F53C
/* 071E5C 8007125C 00000000 */   nop   
/* 071E60 80071260 8FBF0024 */  lw    $ra, 0x24($sp)
/* 071E64 80071264 8FB00018 */  lw    $s0, 0x18($sp)
/* 071E68 80071268 8FB1001C */  lw    $s1, 0x1c($sp)
/* 071E6C 8007126C 8FB20020 */  lw    $s2, 0x20($sp)
/* 071E70 80071270 03E00008 */  jr    $ra
/* 071E74 80071274 27BD0030 */   addiu $sp, $sp, 0x30

