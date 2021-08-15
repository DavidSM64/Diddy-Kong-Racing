glabel func_8008C698
/* 08D298 8008C698 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 08D29C 8008C69C 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 08D2A0 8008C6A0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 08D2A4 8008C6A4 2841FFEB */  slti  $at, $v0, -0x15
/* 08D2A8 8008C6A8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 08D2AC 8008C6AC 1420003F */  bnez  $at, .L8008C7AC
/* 08D2B0 8008C6B0 AFA40028 */   sw    $a0, 0x28($sp)
/* 08D2B4 8008C6B4 28410016 */  slti  $at, $v0, 0x16
/* 08D2B8 8008C6B8 1020003C */  beqz  $at, .L8008C7AC
/* 08D2BC 8008C6BC 3C068012 */   lui   $a2, %hi(D_801263BC) # $a2, 0x8012
/* 08D2C0 8008C6C0 8CC663BC */  lw    $a2, %lo(D_801263BC)($a2)
/* 08D2C4 8008C6C4 3C048012 */  lui   $a0, %hi(D_801263A0) # $a0, 0x8012
/* 08D2C8 8008C6C8 000670C0 */  sll   $t6, $a2, 3
/* 08D2CC 8008C6CC 29C10100 */  slti  $at, $t6, 0x100
/* 08D2D0 8008C6D0 14200003 */  bnez  $at, .L8008C6E0
/* 08D2D4 8008C6D4 01C03025 */   move  $a2, $t6
/* 08D2D8 8008C6D8 240F01FF */  li    $t7, 511
/* 08D2DC 8008C6DC 01EE3023 */  subu  $a2, $t7, $t6
.L8008C6E0:
/* 08D2E0 8008C6E0 3C058012 */  lui   $a1, %hi(D_801263A8) # $a1, 0x8012
/* 08D2E4 8008C6E4 24A563A8 */  addiu $a1, %lo(D_801263A8) # addiu $a1, $a1, 0x63a8
/* 08D2E8 8008C6E8 248463A0 */  addiu $a0, %lo(D_801263A0) # addiu $a0, $a0, 0x63a0
/* 08D2EC 8008C6EC 0C019FCB */  jal   func_80067F2C
/* 08D2F0 8008C6F0 AFA6001C */   sw    $a2, 0x1c($sp)
/* 08D2F4 8008C6F4 3C048012 */  lui   $a0, %hi(D_801263E0) # $a0, 0x8012
/* 08D2F8 8008C6F8 248463E0 */  addiu $a0, %lo(D_801263E0) # addiu $a0, $a0, 0x63e0
/* 08D2FC 8008C6FC 8C980000 */  lw    $t8, ($a0)
/* 08D300 8008C700 8FA6001C */  lw    $a2, 0x1c($sp)
/* 08D304 8008C704 07000013 */  bltz  $t8, .L8008C754
/* 08D308 8008C708 00001025 */   move  $v0, $zero
/* 08D30C 8008C70C 3C078012 */  lui   $a3, %hi(D_80126460) # $a3, 0x8012
/* 08D310 8008C710 3C05800E */  lui   $a1, %hi(D_800DF460) # $a1, 0x800e
/* 08D314 8008C714 24A5F460 */  addiu $a1, %lo(D_800DF460) # addiu $a1, $a1, -0xba0
/* 08D318 8008C718 24E76460 */  addiu $a3, %lo(D_80126460) # addiu $a3, $a3, 0x6460
.L8008C71C:
/* 08D31C 8008C71C 8CB90000 */  lw    $t9, ($a1)
/* 08D320 8008C720 00001825 */  move  $v1, $zero
/* 08D324 8008C724 14590002 */  bne   $v0, $t9, .L8008C730
/* 08D328 8008C728 00404825 */   move  $t1, $v0
/* 08D32C 8008C72C 00C01825 */  move  $v1, $a2
.L8008C730:
/* 08D330 8008C730 8CE80000 */  lw    $t0, ($a3)
/* 08D334 8008C734 00095180 */  sll   $t2, $t1, 6
/* 08D338 8008C738 010A5821 */  addu  $t3, $t0, $t2
/* 08D33C 8008C73C A163006F */  sb    $v1, 0x6f($t3)
/* 08D340 8008C740 8C8C0000 */  lw    $t4, ($a0)
/* 08D344 8008C744 24420001 */  addiu $v0, $v0, 1
/* 08D348 8008C748 0182082A */  slt   $at, $t4, $v0
/* 08D34C 8008C74C 1020FFF3 */  beqz  $at, .L8008C71C
/* 08D350 8008C750 00000000 */   nop   
.L8008C754:
/* 08D354 8008C754 3C0D8000 */  lui   $t5, %hi(osTvType) # $t5, 0x8000
/* 08D358 8008C758 8DAD0300 */  lw    $t5, %lo(osTvType)($t5)
/* 08D35C 8008C75C 3C078012 */  lui   $a3, %hi(D_80126460) # $a3, 0x8012
/* 08D360 8008C760 15A00007 */  bnez  $t5, .L8008C780
/* 08D364 8008C764 24E76460 */   addiu $a3, %lo(D_80126460) # addiu $a3, $a3, 0x6460
/* 08D368 8008C768 240E000C */  li    $t6, 12
/* 08D36C 8008C76C 3C01800E */  lui   $at, %hi(D_800DF79C) # $at, 0x800e
/* 08D370 8008C770 AC2EF79C */  sw    $t6, %lo(D_800DF79C)($at)
/* 08D374 8008C774 3C01800E */  lui   $at, %hi(D_800DF7A0) # $at, 0x800e
/* 08D378 8008C778 10000005 */  b     .L8008C790
/* 08D37C 8008C77C AC20F7A0 */   sw    $zero, %lo(D_800DF7A0)($at)
.L8008C780:
/* 08D380 8008C780 3C01800E */  lui   $at, %hi(D_800DF79C) # $at, 0x800e
/* 08D384 8008C784 AC20F79C */  sw    $zero, %lo(D_800DF79C)($at)
/* 08D388 8008C788 3C01800E */  lui   $at, %hi(D_800DF7A0) # $at, 0x800e
/* 08D38C 8008C78C AC20F7A0 */  sw    $zero, %lo(D_800DF7A0)($at)
.L8008C790:
/* 08D390 8008C790 8CE50000 */  lw    $a1, ($a3)
/* 08D394 8008C794 24040001 */  li    $a0, 1
/* 08D398 8008C798 0C02087B */  jal   draw_menu_elements
/* 08D39C 8008C79C 3C063F80 */   lui   $a2, 0x3f80
/* 08D3A0 8008C7A0 3C048012 */  lui   $a0, %hi(D_801263A0) # $a0, 0x8012
/* 08D3A4 8008C7A4 0C0202F2 */  jal   func_80080BC8
/* 08D3A8 8008C7A8 248463A0 */   addiu $a0, %lo(D_801263A0) # addiu $a0, $a0, 0x63a0
.L8008C7AC:
/* 08D3AC 8008C7AC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 08D3B0 8008C7B0 27BD0028 */  addiu $sp, $sp, 0x28
/* 08D3B4 8008C7B4 03E00008 */  jr    $ra
/* 08D3B8 8008C7B8 00000000 */   nop   

