glabel osCreatePiManager
/* 0C6C00 800C6000 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0C6C04 800C6004 AFB00020 */  sw    $s0, 0x20($sp)
/* 0C6C08 800C6008 3C10800E */  lui   $s0, %hi(__osPiDevMgr) # $s0, 0x800e
/* 0C6C0C 800C600C 26103740 */  addiu $s0, %lo(__osPiDevMgr) # addiu $s0, $s0, 0x3740
/* 0C6C10 800C6010 8E0E0000 */  lw    $t6, ($s0)
/* 0C6C14 800C6014 AFBF0024 */  sw    $ra, 0x24($sp)
/* 0C6C18 800C6018 AFA40030 */  sw    $a0, 0x30($sp)
/* 0C6C1C 800C601C AFA50034 */  sw    $a1, 0x34($sp)
/* 0C6C20 800C6020 15C0004F */  bnez  $t6, .L800C6160
/* 0C6C24 800C6024 AFA60038 */   sw    $a2, 0x38($sp)
/* 0C6C28 800C6028 00A02025 */  move  $a0, $a1
/* 0C6C2C 800C602C 00C02825 */  move  $a1, $a2
/* 0C6C30 800C6030 0C032208 */  jal   osCreateMesgQueue
/* 0C6C34 800C6034 00E03025 */   move  $a2, $a3
/* 0C6C38 800C6038 3C048013 */  lui   $a0, %hi(piEventQueue) # $a0, 0x8013
/* 0C6C3C 800C603C 3C058013 */  lui   $a1, %hi(piEventBuf) # $a1, 0x8013
/* 0C6C40 800C6040 24A5AAC8 */  addiu $a1, %lo(piEventBuf) # addiu $a1, $a1, -0x5538
/* 0C6C44 800C6044 2484AAB0 */  addiu $a0, %lo(piEventQueue) # addiu $a0, $a0, -0x5550
/* 0C6C48 800C6048 0C032208 */  jal   osCreateMesgQueue
/* 0C6C4C 800C604C 24060001 */   li    $a2, 1
/* 0C6C50 800C6050 3C0F800E */  lui   $t7, %hi(__osPiAccessQueueEnabled) # $t7, 0x800e
/* 0C6C54 800C6054 8DEF4800 */  lw    $t7, %lo(__osPiAccessQueueEnabled)($t7)
/* 0C6C58 800C6058 00000000 */  nop   
/* 0C6C5C 800C605C 15E00003 */  bnez  $t7, .L800C606C
/* 0C6C60 800C6060 00000000 */   nop   
/* 0C6C64 800C6064 0C034920 */  jal   __osPiCreateAccessQueue
/* 0C6C68 800C6068 00000000 */   nop   
.L800C606C:
/* 0C6C6C 800C606C 3C058013 */  lui   $a1, %hi(piEventQueue) # $a1, 0x8013
/* 0C6C70 800C6070 3C062222 */  lui   $a2, (0x22222222 >> 16) # lui $a2, 0x2222
/* 0C6C74 800C6074 34C62222 */  ori   $a2, (0x22222222 & 0xFFFF) # ori $a2, $a2, 0x2222
/* 0C6C78 800C6078 24A5AAB0 */  addiu $a1, %lo(piEventQueue) # addiu $a1, $a1, -0x5550
/* 0C6C7C 800C607C 0C0332EC */  jal   osSetEventMesg
/* 0C6C80 800C6080 24040008 */   li    $a0, 8
/* 0C6C84 800C6084 2418FFFF */  li    $t8, -1
/* 0C6C88 800C6088 AFB80028 */  sw    $t8, 0x28($sp)
/* 0C6C8C 800C608C 0C034950 */  jal   osGetThreadPri
/* 0C6C90 800C6090 00002025 */   move  $a0, $zero
/* 0C6C94 800C6094 8FB90030 */  lw    $t9, 0x30($sp)
/* 0C6C98 800C6098 00002025 */  move  $a0, $zero
/* 0C6C9C 800C609C 0059082A */  slt   $at, $v0, $t9
/* 0C6CA0 800C60A0 10200003 */  beqz  $at, .L800C60B0
/* 0C6CA4 800C60A4 03202825 */   move  $a1, $t9
/* 0C6CA8 800C60A8 0C033210 */  jal   osSetThreadPri
/* 0C6CAC 800C60AC AFA20028 */   sw    $v0, 0x28($sp)
.L800C60B0:
/* 0C6CB0 800C60B0 0C034958 */  jal   __osDisableInt
/* 0C6CB4 800C60B4 00000000 */   nop   
/* 0C6CB8 800C60B8 8FA90034 */  lw    $t1, 0x34($sp)
/* 0C6CBC 800C60BC 8FAF0030 */  lw    $t7, 0x30($sp)
/* 0C6CC0 800C60C0 3C048013 */  lui   $a0, %hi(piThread) # $a0, 0x8013
/* 0C6CC4 800C60C4 3C0A8013 */  lui   $t2, %hi(piEventQueue) # $t2, 0x8013
/* 0C6CC8 800C60C8 3C0B8013 */  lui   $t3, %hi(piAccessQueue) # $t3, 0x8013
/* 0C6CCC 800C60CC 3C0C800D */  lui   $t4, %hi(osPiRawStartDma) # $t4, 0x800d
/* 0C6CD0 800C60D0 3C0D800D */  lui   $t5, %hi(osEPiRawStartDma) # $t5, 0x800d
/* 0C6CD4 800C60D4 3C0E8013 */  lui   $t6, %hi(piEventQueue) # $t6, 0x8013
/* 0C6CD8 800C60D8 2484A800 */  addiu $a0, %lo(piThread) # addiu $a0, $a0, -0x5800
/* 0C6CDC 800C60DC 24080001 */  li    $t0, 1
/* 0C6CE0 800C60E0 254AAAB0 */  addiu $t2, %lo(piEventQueue) # addiu $t2, $t2, -0x5550
/* 0C6CE4 800C60E4 256BD1E8 */  addiu $t3, %lo(piAccessQueue) # addiu $t3, $t3, -0x2e18
/* 0C6CE8 800C60E8 258C25A0 */  addiu $t4, %lo(osPiRawStartDma) # addiu $t4, $t4, 0x25a0
/* 0C6CEC 800C60EC 25AD2680 */  addiu $t5, %lo(osEPiRawStartDma) # addiu $t5, $t5, 0x2680
/* 0C6CF0 800C60F0 25CEAAB0 */  addiu $t6, %lo(piEventQueue) # addiu $t6, $t6, -0x5550
/* 0C6CF4 800C60F4 3C06800D */  lui   $a2, %hi(__osDevMgrMain) # $a2, 0x800d
/* 0C6CF8 800C60F8 AFA2002C */  sw    $v0, 0x2c($sp)
/* 0C6CFC 800C60FC AE080000 */  sw    $t0, ($s0)
/* 0C6D00 800C6100 AE040004 */  sw    $a0, 4($s0)
/* 0C6D04 800C6104 AE0A000C */  sw    $t2, 0xc($s0)
/* 0C6D08 800C6108 AE0B0010 */  sw    $t3, 0x10($s0)
/* 0C6D0C 800C610C AE0C0014 */  sw    $t4, 0x14($s0)
/* 0C6D10 800C6110 AE0D0018 */  sw    $t5, 0x18($s0)
/* 0C6D14 800C6114 24C62760 */  addiu $a2, %lo(__osDevMgrMain) # addiu $a2, $a2, 0x2760
/* 0C6D18 800C6118 AFAE0010 */  sw    $t6, 0x10($sp)
/* 0C6D1C 800C611C 00002825 */  move  $a1, $zero
/* 0C6D20 800C6120 02003825 */  move  $a3, $s0
/* 0C6D24 800C6124 AE090008 */  sw    $t1, 8($s0)
/* 0C6D28 800C6128 0C032214 */  jal   osCreateThread
/* 0C6D2C 800C612C AFAF0014 */   sw    $t7, 0x14($sp)
/* 0C6D30 800C6130 3C048013 */  lui   $a0, %hi(piThread) # $a0, 0x8013
/* 0C6D34 800C6134 0C032268 */  jal   osStartThread
/* 0C6D38 800C6138 2484A800 */   addiu $a0, %lo(piThread) # addiu $a0, $a0, -0x5800
/* 0C6D3C 800C613C 8FA4002C */  lw    $a0, 0x2c($sp)
/* 0C6D40 800C6140 0C034960 */  jal   __osRestoreInt
/* 0C6D44 800C6144 00000000 */   nop   
/* 0C6D48 800C6148 8FB80028 */  lw    $t8, 0x28($sp)
/* 0C6D4C 800C614C 2401FFFF */  li    $at, -1
/* 0C6D50 800C6150 13010003 */  beq   $t8, $at, .L800C6160
/* 0C6D54 800C6154 00002025 */   move  $a0, $zero
/* 0C6D58 800C6158 0C033210 */  jal   osSetThreadPri
/* 0C6D5C 800C615C 03002825 */   move  $a1, $t8
.L800C6160:
/* 0C6D60 800C6160 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0C6D64 800C6164 8FB00020 */  lw    $s0, 0x20($sp)
/* 0C6D68 800C6168 03E00008 */  jr    $ra
/* 0C6D6C 800C616C 27BD0030 */   addiu $sp, $sp, 0x30

