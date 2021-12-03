glabel __amDMA
/* 003A38 80002E38 3C098012 */  lui   $t1, %hi(dmaState) # $t1, 0x8012
/* 003A3C 80002E3C 25299230 */  addiu $t1, %lo(dmaState) # addiu $t1, $t1, -0x6dd0
/* 003A40 80002E40 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 003A44 80002E44 8D280004 */  lw    $t0, 4($t1)
/* 003A48 80002E48 AFB00028 */  sw    $s0, 0x28($sp)
/* 003A4C 80002E4C AFA60058 */  sw    $a2, 0x58($sp)
/* 003A50 80002E50 308A0001 */  andi  $t2, $a0, 1
/* 003A54 80002E54 AFBF002C */  sw    $ra, 0x2c($sp)
/* 003A58 80002E58 00803825 */  move  $a3, $a0
/* 003A5C 80002E5C 00003025 */  move  $a2, $zero
/* 003A60 80002E60 AFAA0048 */  sw    $t2, 0x48($sp)
/* 003A64 80002E64 11000016 */  beqz  $t0, .L80002EC0
/* 003A68 80002E68 01008025 */   move  $s0, $t0
.L80002E6C:
/* 003A6C 80002E6C 8E020008 */  lw    $v0, 8($s0)
/* 003A70 80002E70 00E57021 */  addu  $t6, $a3, $a1
/* 003A74 80002E74 00E2082B */  sltu  $at, $a3, $v0
/* 003A78 80002E78 14200011 */  bnez  $at, .L80002EC0
/* 003A7C 80002E7C 24430400 */   addiu $v1, $v0, 0x400
/* 003A80 80002E80 006E082A */  slt   $at, $v1, $t6
/* 003A84 80002E84 1420000A */  bnez  $at, .L80002EB0
/* 003A88 80002E88 02003025 */   move  $a2, $s0
/* 003A8C 80002E8C 8E180010 */  lw    $t8, 0x10($s0)
/* 003A90 80002E90 3C0F800E */  lui   $t7, %hi(audFrameCt) # $t7, 0x800e
/* 003A94 80002E94 8DEFC680 */  lw    $t7, %lo(audFrameCt)($t7)
/* 003A98 80002E98 0307C821 */  addu  $t9, $t8, $a3
/* 003A9C 80002E9C 03222023 */  subu  $a0, $t9, $v0
/* 003AA0 80002EA0 0C03233C */  jal   osVirtualToPhysical
/* 003AA4 80002EA4 AE0F000C */   sw    $t7, 0xc($s0)
/* 003AA8 80002EA8 10000054 */  b     .L80002FFC
/* 003AAC 80002EAC 8FBF002C */   lw    $ra, 0x2c($sp)
.L80002EB0:
/* 003AB0 80002EB0 8E100000 */  lw    $s0, ($s0)
/* 003AB4 80002EB4 00000000 */  nop   
/* 003AB8 80002EB8 1600FFEC */  bnez  $s0, .L80002E6C
/* 003ABC 80002EBC 00000000 */   nop   
.L80002EC0:
/* 003AC0 80002EC0 8D300008 */  lw    $s0, 8($t1)
/* 003AC4 80002EC4 00000000 */  nop   
/* 003AC8 80002EC8 16000004 */  bnez  $s0, .L80002EDC
/* 003ACC 80002ECC 02002025 */   move  $a0, $s0
/* 003AD0 80002ED0 14C00002 */  bnez  $a2, .L80002EDC
/* 003AD4 80002ED4 00000000 */   nop   
/* 003AD8 80002ED8 01003025 */  move  $a2, $t0
.L80002EDC:
/* 003ADC 80002EDC 16000007 */  bnez  $s0, .L80002EFC
/* 003AE0 80002EE0 00000000 */   nop   
/* 003AE4 80002EE4 8CC40010 */  lw    $a0, 0x10($a2)
/* 003AE8 80002EE8 0C03233C */  jal   osVirtualToPhysical
/* 003AEC 80002EEC AFAA0030 */   sw    $t2, 0x30($sp)
/* 003AF0 80002EF0 8FAA0030 */  lw    $t2, 0x30($sp)
/* 003AF4 80002EF4 10000040 */  b     .L80002FF8
/* 003AF8 80002EF8 004A1021 */   addu  $v0, $v0, $t2
.L80002EFC:
/* 003AFC 80002EFC 8E0B0000 */  lw    $t3, ($s0)
/* 003B00 80002F00 AFA70050 */  sw    $a3, 0x50($sp)
/* 003B04 80002F04 AFA60038 */  sw    $a2, 0x38($sp)
/* 003B08 80002F08 0C0321D8 */  jal   alUnlink
/* 003B0C 80002F0C AD2B0008 */   sw    $t3, 8($t1)
/* 003B10 80002F10 8FA60038 */  lw    $a2, 0x38($sp)
/* 003B14 80002F14 8FA70050 */  lw    $a3, 0x50($sp)
/* 003B18 80002F18 3C098012 */  lui   $t1, %hi(dmaState) # $t1, 0x8012
/* 003B1C 80002F1C 10C00008 */  beqz  $a2, .L80002F40
/* 003B20 80002F20 25299230 */   addiu $t1, %lo(dmaState) # addiu $t1, $t1, -0x6dd0
/* 003B24 80002F24 02002025 */  move  $a0, $s0
/* 003B28 80002F28 00C02825 */  move  $a1, $a2
/* 003B2C 80002F2C 0C0321E4 */  jal   alLink
/* 003B30 80002F30 AFA70050 */   sw    $a3, 0x50($sp)
/* 003B34 80002F34 8FA70050 */  lw    $a3, 0x50($sp)
/* 003B38 80002F38 1000000E */  b     .L80002F74
/* 003B3C 80002F3C 8FAC0048 */   lw    $t4, 0x48($sp)
.L80002F40:
/* 003B40 80002F40 8D280004 */  lw    $t0, 4($t1)
/* 003B44 80002F44 00000000 */  nop   
/* 003B48 80002F48 11000006 */  beqz  $t0, .L80002F64
/* 003B4C 80002F4C 00000000 */   nop   
/* 003B50 80002F50 AD300004 */  sw    $s0, 4($t1)
/* 003B54 80002F54 AE080000 */  sw    $t0, ($s0)
/* 003B58 80002F58 AE000004 */  sw    $zero, 4($s0)
/* 003B5C 80002F5C 10000004 */  b     .L80002F70
/* 003B60 80002F60 AD100004 */   sw    $s0, 4($t0)
.L80002F64:
/* 003B64 80002F64 AD300004 */  sw    $s0, 4($t1)
/* 003B68 80002F68 AE000000 */  sw    $zero, ($s0)
/* 003B6C 80002F6C AE000004 */  sw    $zero, 4($s0)
.L80002F70:
/* 003B70 80002F70 8FAC0048 */  lw    $t4, 0x48($sp)
.L80002F74:
/* 003B74 80002F74 3C0D800E */  lui   $t5, %hi(audFrameCt) # $t5, 0x800e
/* 003B78 80002F78 00EC3823 */  subu  $a3, $a3, $t4
/* 003B7C 80002F7C AE070008 */  sw    $a3, 8($s0)
/* 003B80 80002F80 8DADC680 */  lw    $t5, %lo(audFrameCt)($t5)
/* 003B84 80002F84 3C08800E */  lui   $t0, %hi(D_800DC684) # $t0, 0x800e
/* 003B88 80002F88 2508C684 */  addiu $t0, %lo(D_800DC684) # addiu $t0, $t0, -0x397c
/* 003B8C 80002F8C AE0D000C */  sw    $t5, 0xc($s0)
/* 003B90 80002F90 8E030010 */  lw    $v1, 0x10($s0)
/* 003B94 80002F94 8D020000 */  lw    $v0, ($t0)
/* 003B98 80002F98 3C0F8012 */  lui   $t7, %hi(audDMAIOMesgBuf) # $t7, 0x8012
/* 003B9C 80002F9C 00027080 */  sll   $t6, $v0, 2
/* 003BA0 80002FA0 3C198012 */  lui   $t9, %hi(audDMAMessageQ) # $t9, 0x8012
/* 003BA4 80002FA4 01C27023 */  subu  $t6, $t6, $v0
/* 003BA8 80002FA8 000E70C0 */  sll   $t6, $t6, 3
/* 003BAC 80002FAC 27399AF0 */  addiu $t9, %lo(audDMAMessageQ) # addiu $t9, $t9, -0x6510
/* 003BB0 80002FB0 25EF9640 */  addiu $t7, %lo(audDMAIOMesgBuf) # addiu $t7, $t7, -0x69c0
/* 003BB4 80002FB4 24180400 */  li    $t8, 1024
/* 003BB8 80002FB8 244B0001 */  addiu $t3, $v0, 1
/* 003BBC 80002FBC AD0B0000 */  sw    $t3, ($t0)
/* 003BC0 80002FC0 AFB80014 */  sw    $t8, 0x14($sp)
/* 003BC4 80002FC4 01CF2021 */  addu  $a0, $t6, $t7
/* 003BC8 80002FC8 AFB90018 */  sw    $t9, 0x18($sp)
/* 003BCC 80002FCC 24050001 */  li    $a1, 1
/* 003BD0 80002FD0 00003025 */  move  $a2, $zero
/* 003BD4 80002FD4 AFA30010 */  sw    $v1, 0x10($sp)
/* 003BD8 80002FD8 0C0323E0 */  jal   osPiStartDma
/* 003BDC 80002FDC AFA3004C */   sw    $v1, 0x4c($sp)
/* 003BE0 80002FE0 8FA4004C */  lw    $a0, 0x4c($sp)
/* 003BE4 80002FE4 0C03233C */  jal   osVirtualToPhysical
/* 003BE8 80002FE8 00000000 */   nop   
/* 003BEC 80002FEC 8FAC0048 */  lw    $t4, 0x48($sp)
/* 003BF0 80002FF0 00000000 */  nop   
/* 003BF4 80002FF4 004C1021 */  addu  $v0, $v0, $t4
.L80002FF8:
/* 003BF8 80002FF8 8FBF002C */  lw    $ra, 0x2c($sp)
.L80002FFC:
/* 003BFC 80002FFC 8FB00028 */  lw    $s0, 0x28($sp)
/* 003C00 80003000 03E00008 */  jr    $ra
/* 003C04 80003004 27BD0050 */   addiu $sp, $sp, 0x50

