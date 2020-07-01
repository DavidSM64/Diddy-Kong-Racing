glabel func_80064F9C
/* 065B9C 80064F9C 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 065BA0 80064FA0 AFA5002C */  sw    $a1, 0x2c($sp)
/* 065BA4 80064FA4 AFBF0024 */  sw    $ra, 0x24($sp)
/* 065BA8 80064FA8 AFB00020 */  sw    $s0, 0x20($sp)
/* 065BAC 80064FAC 3C05800D */  lui   $a1, %hi(D_800CC17C) # $a1, 0x800d
/* 065BB0 80064FB0 3C06800D */  lui   $a2, %hi(D_800CC090) # $a2, 0x800d
/* 065BB4 80064FB4 00808025 */  move  $s0, $a0
/* 065BB8 80064FB8 24C6C090 */  addiu $a2, %lo(D_800CC090) # addiu $a2, $a2, -0x3f70
/* 065BBC 80064FBC 24A5C17C */  addiu $a1, %lo(D_800CC17C) # addiu $a1, $a1, -0x3e84
/* 065BC0 80064FC0 0C03282C */  jal   func_800CA0B0
/* 065BC4 80064FC4 24070001 */   li    $a3, 1
/* 065BC8 80064FC8 8FA6002C */  lw    $a2, 0x2c($sp)
/* 065BCC 80064FCC 240E0020 */  li    $t6, 32
/* 065BD0 80064FD0 AFAE0010 */  sw    $t6, 0x10($sp)
/* 065BD4 80064FD4 00002025 */  move  $a0, $zero
/* 065BD8 80064FD8 00002825 */  move  $a1, $zero
/* 065BDC 80064FDC 0C031DFC */  jal   func_800C77F0
/* 065BE0 80064FE0 24070001 */   li    $a3, 1
/* 065BE4 80064FE4 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 065BE8 80064FE8 44802000 */  mtc1  $zero, $f4
/* 065BEC 80064FEC 44813000 */  mtc1  $at, $f6
/* 065BF0 80064FF0 240F0001 */  li    $t7, 1
/* 065BF4 80064FF4 AE020014 */  sw    $v0, 0x14($s0)
/* 065BF8 80064FF8 AE0F0024 */  sw    $t7, 0x24($s0)
/* 065BFC 80064FFC AE000030 */  sw    $zero, 0x30($s0)
/* 065C00 80065000 AE00001C */  sw    $zero, 0x1c($s0)
/* 065C04 80065004 AE000028 */  sw    $zero, 0x28($s0)
/* 065C08 80065008 AE00002C */  sw    $zero, 0x2c($s0)
/* 065C0C 8006500C E6040020 */  swc1  $f4, 0x20($s0)
/* 065C10 80065010 E6060018 */  swc1  $f6, 0x18($s0)
/* 065C14 80065014 8FBF0024 */  lw    $ra, 0x24($sp)
/* 065C18 80065018 8FB00020 */  lw    $s0, 0x20($sp)
/* 065C1C 8006501C 03E00008 */  jr    $ra
/* 065C20 80065020 27BD0028 */   addiu $sp, $sp, 0x28

