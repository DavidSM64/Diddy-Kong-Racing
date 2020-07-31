glabel osEepromRead
/* 0CEE80 800CE280 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0CEE84 800CE284 AFA5003C */  sw    $a1, 0x3c($sp)
/* 0CEE88 800CE288 93AF003F */  lbu   $t7, 0x3f($sp)
/* 0CEE8C 800CE28C 3C0E8013 */  lui   $t6, %hi(D_8012CE40) # $t6, 0x8013
/* 0CEE90 800CE290 25CECE40 */  addiu $t6, %lo(D_8012CE40) # addiu $t6, $t6, -0x31c0
/* 0CEE94 800CE294 29E10041 */  slti  $at, $t7, 0x41
/* 0CEE98 800CE298 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CEE9C 800CE29C AFA40038 */  sw    $a0, 0x38($sp)
/* 0CEEA0 800CE2A0 AFA60040 */  sw    $a2, 0x40($sp)
/* 0CEEA4 800CE2A4 AFA00034 */  sw    $zero, 0x34($sp)
/* 0CEEA8 800CE2A8 AFA00030 */  sw    $zero, 0x30($sp)
/* 0CEEAC 800CE2AC 14200003 */  bnez  $at, .L800CE2BC
/* 0CEEB0 800CE2B0 AFAE002C */   sw    $t6, 0x2c($sp)
/* 0CEEB4 800CE2B4 1000006A */  b     .L800CE460
/* 0CEEB8 800CE2B8 2402FFFF */   li    $v0, -1
.L800CE2BC:
/* 0CEEBC 800CE2BC 0C033594 */  jal   __osSiGetAccess
/* 0CEEC0 800CE2C0 00000000 */   nop   
/* 0CEEC4 800CE2C4 8FA40038 */  lw    $a0, 0x38($sp)
/* 0CEEC8 800CE2C8 0C033A0F */  jal   __osEepStatus
/* 0CEECC 800CE2CC 27A50028 */   addiu $a1, $sp, 0x28
/* 0CEED0 800CE2D0 AFA20034 */  sw    $v0, 0x34($sp)
/* 0CEED4 800CE2D4 8FB80034 */  lw    $t8, 0x34($sp)
/* 0CEED8 800CE2D8 17000005 */  bnez  $t8, .L800CE2F0
/* 0CEEDC 800CE2DC 00000000 */   nop   
/* 0CEEE0 800CE2E0 97B90028 */  lhu   $t9, 0x28($sp)
/* 0CEEE4 800CE2E4 34018000 */  li    $at, 32768
/* 0CEEE8 800CE2E8 13210003 */  beq   $t9, $at, .L800CE2F8
/* 0CEEEC 800CE2EC 00000000 */   nop   
.L800CE2F0:
/* 0CEEF0 800CE2F0 1000005B */  b     .L800CE460
/* 0CEEF4 800CE2F4 24020008 */   li    $v0, 8
.L800CE2F8:
/* 0CEEF8 800CE2F8 93A8002A */  lbu   $t0, 0x2a($sp)
/* 0CEEFC 800CE2FC 31090080 */  andi  $t1, $t0, 0x80
/* 0CEF00 800CE300 11200008 */  beqz  $t1, .L800CE324
/* 0CEF04 800CE304 00000000 */   nop   
.L800CE308:
/* 0CEF08 800CE308 8FA40038 */  lw    $a0, 0x38($sp)
/* 0CEF0C 800CE30C 0C033A0F */  jal   __osEepStatus
/* 0CEF10 800CE310 27A50028 */   addiu $a1, $sp, 0x28
/* 0CEF14 800CE314 93AA002A */  lbu   $t2, 0x2a($sp)
/* 0CEF18 800CE318 314B0080 */  andi  $t3, $t2, 0x80
/* 0CEF1C 800CE31C 1560FFFA */  bnez  $t3, .L800CE308
/* 0CEF20 800CE320 00000000 */   nop   
.L800CE324:
/* 0CEF24 800CE324 0C03391C */  jal   __osPackEepReadData
/* 0CEF28 800CE328 93A4003F */   lbu   $a0, 0x3f($sp)
/* 0CEF2C 800CE32C 3C058013 */  lui   $a1, %hi(D_8012CE40) # $a1, 0x8013
/* 0CEF30 800CE330 24A5CE40 */  addiu $a1, %lo(D_8012CE40) # addiu $a1, $a1, -0x31c0
/* 0CEF34 800CE334 0C0335B0 */  jal   __osSiRawStartDma
/* 0CEF38 800CE338 24040001 */   li    $a0, 1
/* 0CEF3C 800CE33C AFA20034 */  sw    $v0, 0x34($sp)
/* 0CEF40 800CE340 8FA40038 */  lw    $a0, 0x38($sp)
/* 0CEF44 800CE344 00002825 */  move  $a1, $zero
/* 0CEF48 800CE348 0C0322EC */  jal   osRecvMesg
/* 0CEF4C 800CE34C 24060001 */   li    $a2, 1
/* 0CEF50 800CE350 AFA00030 */  sw    $zero, 0x30($sp)
.L800CE354:
/* 0CEF54 800CE354 8FAD0030 */  lw    $t5, 0x30($sp)
/* 0CEF58 800CE358 8FAF0030 */  lw    $t7, 0x30($sp)
/* 0CEF5C 800CE35C 3C018013 */  lui   $at, 0x8013
/* 0CEF60 800CE360 000D7080 */  sll   $t6, $t5, 2
/* 0CEF64 800CE364 002E0821 */  addu  $at, $at, $t6
/* 0CEF68 800CE368 240C00FF */  li    $t4, 255
/* 0CEF6C 800CE36C AC2CCE40 */  sw    $t4, -0x31c0($at)
/* 0CEF70 800CE370 25F80001 */  addiu $t8, $t7, 1
/* 0CEF74 800CE374 2B010010 */  slti  $at, $t8, 0x10
/* 0CEF78 800CE378 1420FFF6 */  bnez  $at, .L800CE354
/* 0CEF7C 800CE37C AFB80030 */   sw    $t8, 0x30($sp)
/* 0CEF80 800CE380 3C018013 */  lui   $at, %hi(D_8012CE7C) # $at, 0x8013
/* 0CEF84 800CE384 3C058013 */  lui   $a1, %hi(D_8012CE40) # $a1, 0x8013
/* 0CEF88 800CE388 AC20CE7C */  sw    $zero, %lo(D_8012CE7C)($at)
/* 0CEF8C 800CE38C 24A5CE40 */  addiu $a1, %lo(D_8012CE40) # addiu $a1, $a1, -0x31c0
/* 0CEF90 800CE390 0C0335B0 */  jal   __osSiRawStartDma
/* 0CEF94 800CE394 00002025 */   move  $a0, $zero
/* 0CEF98 800CE398 24190004 */  li    $t9, 4
/* 0CEF9C 800CE39C 3C018013 */  lui   $at, %hi(D_8012CD90) # $at, 0x8013
/* 0CEFA0 800CE3A0 AFA20034 */  sw    $v0, 0x34($sp)
/* 0CEFA4 800CE3A4 A039CD90 */  sb    $t9, %lo(D_8012CD90)($at)
/* 0CEFA8 800CE3A8 8FA40038 */  lw    $a0, 0x38($sp)
/* 0CEFAC 800CE3AC 00002825 */  move  $a1, $zero
/* 0CEFB0 800CE3B0 0C0322EC */  jal   osRecvMesg
/* 0CEFB4 800CE3B4 24060001 */   li    $a2, 1
/* 0CEFB8 800CE3B8 AFA00030 */  sw    $zero, 0x30($sp)
.L800CE3BC:
/* 0CEFBC 800CE3BC 8FAA0030 */  lw    $t2, 0x30($sp)
/* 0CEFC0 800CE3C0 8FA8002C */  lw    $t0, 0x2c($sp)
/* 0CEFC4 800CE3C4 254B0001 */  addiu $t3, $t2, 1
/* 0CEFC8 800CE3C8 29610004 */  slti  $at, $t3, 4
/* 0CEFCC 800CE3CC 25090001 */  addiu $t1, $t0, 1
/* 0CEFD0 800CE3D0 AFAB0030 */  sw    $t3, 0x30($sp)
/* 0CEFD4 800CE3D4 1420FFF9 */  bnez  $at, .L800CE3BC
/* 0CEFD8 800CE3D8 AFA9002C */   sw    $t1, 0x2c($sp)
/* 0CEFDC 800CE3DC 8FAC002C */  lw    $t4, 0x2c($sp)
/* 0CEFE0 800CE3E0 27AD001C */  addiu $t5, $sp, 0x1c
/* 0CEFE4 800CE3E4 89810000 */  lwl   $at, ($t4)
/* 0CEFE8 800CE3E8 99810003 */  lwr   $at, 3($t4)
/* 0CEFEC 800CE3EC ADA10000 */  sw    $at, ($t5)
/* 0CEFF0 800CE3F0 898F0004 */  lwl   $t7, 4($t4)
/* 0CEFF4 800CE3F4 998F0007 */  lwr   $t7, 7($t4)
/* 0CEFF8 800CE3F8 ADAF0004 */  sw    $t7, 4($t5)
/* 0CEFFC 800CE3FC 89810008 */  lwl   $at, 8($t4)
/* 0CF000 800CE400 9981000B */  lwr   $at, 0xb($t4)
/* 0CF004 800CE404 ADA10008 */  sw    $at, 8($t5)
/* 0CF008 800CE408 93B8001D */  lbu   $t8, 0x1d($sp)
/* 0CF00C 800CE40C 331900C0 */  andi  $t9, $t8, 0xc0
/* 0CF010 800CE410 00194103 */  sra   $t0, $t9, 4
/* 0CF014 800CE414 1500000F */  bnez  $t0, .L800CE454
/* 0CF018 800CE418 AFA80034 */   sw    $t0, 0x34($sp)
/* 0CF01C 800CE41C AFA00030 */  sw    $zero, 0x30($sp)
.L800CE420:
/* 0CF020 800CE420 8FA90030 */  lw    $t1, 0x30($sp)
/* 0CF024 800CE424 8FAB0040 */  lw    $t3, 0x40($sp)
/* 0CF028 800CE428 03A95021 */  addu  $t2, $sp, $t1
/* 0CF02C 800CE42C 914A0020 */  lbu   $t2, 0x20($t2)
/* 0CF030 800CE430 A16A0000 */  sb    $t2, ($t3)
/* 0CF034 800CE434 8FAC0030 */  lw    $t4, 0x30($sp)
/* 0CF038 800CE438 8FAE0040 */  lw    $t6, 0x40($sp)
/* 0CF03C 800CE43C 258F0001 */  addiu $t7, $t4, 1
/* 0CF040 800CE440 29E10008 */  slti  $at, $t7, 8
/* 0CF044 800CE444 25CD0001 */  addiu $t5, $t6, 1
/* 0CF048 800CE448 AFAF0030 */  sw    $t7, 0x30($sp)
/* 0CF04C 800CE44C 1420FFF4 */  bnez  $at, .L800CE420
/* 0CF050 800CE450 AFAD0040 */   sw    $t5, 0x40($sp)
.L800CE454:
/* 0CF054 800CE454 0C0335A5 */  jal   __osSiRelAccess
/* 0CF058 800CE458 00000000 */   nop   
/* 0CF05C 800CE45C 8FA20034 */  lw    $v0, 0x34($sp)
.L800CE460:
/* 0CF060 800CE460 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CF064 800CE464 27BD0038 */  addiu $sp, $sp, 0x38
/* 0CF068 800CE468 03E00008 */  jr    $ra
/* 0CF06C 800CE46C 00000000 */   nop   

