glabel func_800C7350
/* 0C7F50 800C7350 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0C7F54 800C7354 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0C7F58 800C7358 3C048013 */  lui   $a0, %hi(D_8012ACA0) # $a0, 0x8013
/* 0C7F5C 800C735C 3C058013 */  lui   $a1, %hi(D_8012ACB8) # $a1, 0x8013
/* 0C7F60 800C7360 24A5ACB8 */  addiu $a1, %lo(D_8012ACB8) # addiu $a1, $a1, -0x5348
/* 0C7F64 800C7364 2484ACA0 */  addiu $a0, %lo(D_8012ACA0) # addiu $a0, $a0, -0x5360
/* 0C7F68 800C7368 0C032208 */  jal   osCreateMesgQueue
/* 0C7F6C 800C736C 24060002 */   li    $a2, 2
/* 0C7F70 800C7370 3C0E8013 */  lui   $t6, %hi(D_8012CCC0) # $t6, 0x8013
/* 0C7F74 800C7374 25CECCC0 */  addiu $t6, %lo(D_8012CCC0) # addiu $t6, $t6, -0x3340
/* 0C7F78 800C7378 3C048013 */  lui   $a0, %hi(D_8012AAF0) # $a0, 0x8013
/* 0C7F7C 800C737C 3C06800C */  lui   $a2, %hi(D_800C74A0) # $a2, 0x800c
/* 0C7F80 800C7380 240F0008 */  li    $t7, 8
/* 0C7F84 800C7384 AFAF0014 */  sw    $t7, 0x14($sp)
/* 0C7F88 800C7388 24C674A0 */  addiu $a2, %lo(D_800C74A0) # addiu $a2, $a2, 0x74a0
/* 0C7F8C 800C738C 2484AAF0 */  addiu $a0, %lo(D_8012AAF0) # addiu $a0, $a0, -0x5510
/* 0C7F90 800C7390 AFAE0010 */  sw    $t6, 0x10($sp)
/* 0C7F94 800C7394 2405001E */  li    $a1, 30
/* 0C7F98 800C7398 0C032214 */  jal   osCreateThread
/* 0C7F9C 800C739C 00003825 */   move  $a3, $zero
/* 0C7FA0 800C73A0 3C048013 */  lui   $a0, %hi(D_8012AAF0) # $a0, 0x8013
/* 0C7FA4 800C73A4 0C032268 */  jal   osStartThread
/* 0C7FA8 800C73A8 2484AAF0 */   addiu $a0, %lo(D_8012AAF0) # addiu $a0, $a0, -0x5510
/* 0C7FAC 800C73AC 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0C7FB0 800C73B0 27BD0020 */  addiu $sp, $sp, 0x20
/* 0C7FB4 800C73B4 03E00008 */  jr    $ra
/* 0C7FB8 800C73B8 00000000 */   nop   

