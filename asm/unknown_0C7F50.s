.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

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

glabel func_800C73BC
/* 0C7FBC 800C73BC 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C7FC0 800C73C0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C7FC4 800C73C4 3C048013 */  lui   $a0, %hi(D_8012AAF0) # $a0, 0x8013
/* 0C7FC8 800C73C8 0C0322BC */  jal   func_800C8AF0
/* 0C7FCC 800C73CC 2484AAF0 */   addiu $a0, %lo(D_8012AAF0) # addiu $a0, $a0, -0x5510
/* 0C7FD0 800C73D0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C7FD4 800C73D4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0C7FD8 800C73D8 03E00008 */  jr    $ra
/* 0C7FDC 800C73DC 00000000 */   nop   

glabel func_800C73E0
/* 0C7FE0 800C73E0 3C02800E */  lui   $v0, %hi(D_800E3770) # $v0, 0x800e
/* 0C7FE4 800C73E4 8C423770 */  lw    $v0, %lo(D_800E3770)($v0)
/* 0C7FE8 800C73E8 03E00008 */  jr    $ra
/* 0C7FEC 800C73EC 00000000 */   nop   

glabel func_800C73F0
/* 0C7FF0 800C73F0 3C0E800E */  lui   $t6, %hi(D_800E3770) # $t6, 0x800e
/* 0C7FF4 800C73F4 8DCE3770 */  lw    $t6, %lo(D_800E3770)($t6)
/* 0C7FF8 800C73F8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C7FFC 800C73FC 11C0000E */  beqz  $t6, .L800C7438
/* 0C8000 800C7400 AFBF0014 */   sw    $ra, 0x14($sp)
/* 0C8004 800C7404 3C03800E */  lui   $v1, %hi(D_800E377C) # $v1, 0x800e
/* 0C8008 800C7408 2463377C */  addiu $v1, %lo(D_800E377C) # addiu $v1, $v1, 0x377c
/* 0C800C 800C740C 8C620000 */  lw    $v0, ($v1)
/* 0C8010 800C7410 00000000 */  nop   
/* 0C8014 800C7414 18400008 */  blez  $v0, .L800C7438
/* 0C8018 800C7418 244FFFFF */   addiu $t7, $v0, -1
/* 0C801C 800C741C 15E00006 */  bnez  $t7, .L800C7438
/* 0C8020 800C7420 AC6F0000 */   sw    $t7, ($v1)
/* 0C8024 800C7424 3C048013 */  lui   $a0, %hi(D_8012ACA0) # $a0, 0x8013
/* 0C8028 800C7428 2484ACA0 */  addiu $a0, %lo(D_8012ACA0) # addiu $a0, $a0, -0x5360
/* 0C802C 800C742C 2405000A */  li    $a1, 10
/* 0C8030 800C7430 0C03238C */  jal   func_800C8E30
/* 0C8034 800C7434 00003025 */   move  $a2, $zero
.L800C7438:
/* 0C8038 800C7438 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C803C 800C743C 27BD0018 */  addiu $sp, $sp, 0x18
/* 0C8040 800C7440 03E00008 */  jr    $ra
/* 0C8044 800C7444 00000000 */   nop   

/* 0C8048 800C7448 3C02800E */  lui   $v0, %hi(D_800E377C) # $v0, 0x800e
/* 0C804C 800C744C 8C42377C */  lw    $v0, %lo(D_800E377C)($v0)
/* 0C8050 800C7450 03E00008 */  jr    $ra
/* 0C8054 800C7454 00000000 */   nop   

glabel func_800C7458
/* 0C8058 800C7458 3C03800E */  lui   $v1, %hi(D_800E3770) # $v1, 0x800e
/* 0C805C 800C745C 24633770 */  addiu $v1, %lo(D_800E3770) # addiu $v1, $v1, 0x3770
/* 0C8060 800C7460 8C6E0000 */  lw    $t6, ($v1)
/* 0C8064 800C7464 240F0004 */  li    $t7, 4
/* 0C8068 800C7468 15C0000A */  bnez  $t6, .L800C7494
/* 0C806C 800C746C 3C01800E */   lui   $at, %hi(D_800E377C) # $at, 0x800e
/* 0C8070 800C7470 AC2F377C */  sw    $t7, %lo(D_800E377C)($at)
/* 0C8074 800C7474 3C01800E */  lui   $at, %hi(D_800E3774) # $at, 0x800e
/* 0C8078 800C7478 AC243774 */  sw    $a0, %lo(D_800E3774)($at)
/* 0C807C 800C747C 3C01800E */  lui   $at, %hi(D_800E3778) # $at, 0x800e
/* 0C8080 800C7480 AC253778 */  sw    $a1, %lo(D_800E3778)($at)
/* 0C8084 800C7484 24180001 */  li    $t8, 1
/* 0C8088 800C7488 AC780000 */  sw    $t8, ($v1)
/* 0C808C 800C748C 03E00008 */  jr    $ra
/* 0C8090 800C7490 24020001 */   li    $v0, 1

.L800C7494:
/* 0C8094 800C7494 00001025 */  move  $v0, $zero
/* 0C8098 800C7498 03E00008 */  jr    $ra
/* 0C809C 800C749C 00000000 */   nop   

glabel D_800C74A0
/* 0C80A0 800C74A0 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0C80A4 800C74A4 AFB50028 */  sw    $s5, 0x28($sp)
/* 0C80A8 800C74A8 AFB40024 */  sw    $s4, 0x24($sp)
/* 0C80AC 800C74AC AFB30020 */  sw    $s3, 0x20($sp)
/* 0C80B0 800C74B0 AFB00014 */  sw    $s0, 0x14($sp)
/* 0C80B4 800C74B4 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0C80B8 800C74B8 AFB10018 */  sw    $s1, 0x18($sp)
/* 0C80BC 800C74BC 3C108013 */  lui   $s0, %hi(D_8012ACA0) # $s0, 0x8013
/* 0C80C0 800C74C0 3C13800E */  lui   $s3, %hi(D_800E3774) # $s3, 0x800e
/* 0C80C4 800C74C4 3C14800E */  lui   $s4, %hi(D_800E3778) # $s4, 0x800e
/* 0C80C8 800C74C8 3C15800E */  lui   $s5, %hi(D_800E3770) # $s5, 0x800e
/* 0C80CC 800C74CC AFBF002C */  sw    $ra, 0x2c($sp)
/* 0C80D0 800C74D0 AFA40038 */  sw    $a0, 0x38($sp)
/* 0C80D4 800C74D4 AFA00034 */  sw    $zero, 0x34($sp)
/* 0C80D8 800C74D8 26B53770 */  addiu $s5, %lo(D_800E3770) # addiu $s5, $s5, 0x3770
/* 0C80DC 800C74DC 26943778 */  addiu $s4, %lo(D_800E3778) # addiu $s4, $s4, 0x3778
/* 0C80E0 800C74E0 26733774 */  addiu $s3, %lo(D_800E3774) # addiu $s3, $s3, 0x3774
/* 0C80E4 800C74E4 2610ACA0 */  addiu $s0, %lo(D_8012ACA0) # addiu $s0, $s0, -0x5360
/* 0C80E8 800C74E8 27B10034 */  addiu $s1, $sp, 0x34
/* 0C80EC 800C74EC 2412000A */  li    $s2, 10
.L800C74F0:
/* 0C80F0 800C74F0 02002025 */  move  $a0, $s0
.L800C74F4:
/* 0C80F4 800C74F4 02202825 */  move  $a1, $s1
/* 0C80F8 800C74F8 0C0322EC */  jal   osRecvMesg
/* 0C80FC 800C74FC 24060001 */   li    $a2, 1
/* 0C8100 800C7500 8FAE0034 */  lw    $t6, 0x34($sp)
/* 0C8104 800C7504 00000000 */  nop   
/* 0C8108 800C7508 15D2FFFA */  bne   $t6, $s2, .L800C74F4
/* 0C810C 800C750C 02002025 */   move  $a0, $s0
/* 0C8110 800C7510 8E640000 */  lw    $a0, ($s3)
/* 0C8114 800C7514 8E860000 */  lw    $a2, ($s4)
/* 0C8118 800C7518 0C01B8BA */  jal   func_8006E2E8
/* 0C811C 800C751C 2405FFFF */   li    $a1, -1
/* 0C8120 800C7520 1000FFF3 */  b     .L800C74F0
/* 0C8124 800C7524 AEA00000 */   sw    $zero, ($s5)
/* 0C8128 800C7528 00000000 */  nop   
/* 0C812C 800C752C 00000000 */  nop   
/* 0C8130 800C7530 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0C8134 800C7534 8FB00014 */  lw    $s0, 0x14($sp)
/* 0C8138 800C7538 8FB10018 */  lw    $s1, 0x18($sp)
/* 0C813C 800C753C 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0C8140 800C7540 8FB30020 */  lw    $s3, 0x20($sp)
/* 0C8144 800C7544 8FB40024 */  lw    $s4, 0x24($sp)
/* 0C8148 800C7548 8FB50028 */  lw    $s5, 0x28($sp)
/* 0C814C 800C754C 03E00008 */  jr    $ra
/* 0C8150 800C7550 27BD0038 */   addiu $sp, $sp, 0x38

/* 0C8154 800C7554 00000000 */  nop   
/* 0C8158 800C7558 00000000 */  nop   
/* 0C815C 800C755C 00000000 */  nop   
