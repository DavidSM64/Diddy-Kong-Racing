glabel func_8001B4FC
/* 01C0FC 8001B4FC 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 01C100 8001B500 3C01800E */  lui   $at, %hi(gBeatStaffGhost) # $at, 0x800e
/* 01C104 8001B504 A020C738 */  sb    $zero, %lo(gBeatStaffGhost)($at)
/* 01C108 8001B508 AFBF001C */  sw    $ra, 0x1c($sp)
/* 01C10C 8001B50C AFB00018 */  sw    $s0, 0x18($sp)
/* 01C110 8001B510 3C01800E */  lui   $at, %hi(gTimeTrialStaffGhost) # $at, 0x800e
/* 01C114 8001B514 00808025 */  move  $s0, $a0
/* 01C118 8001B518 0C01BAA4 */  jal   get_settings
/* 01C11C 8001B51C A020C734 */   sb    $zero, %lo(gTimeTrialStaffGhost)($at)
/* 01C120 8001B520 AFA20020 */  sw    $v0, 0x20($sp)
/* 01C124 8001B524 0C01AC2B */  jal   get_map_default_vehicle
/* 01C128 8001B528 02002025 */   move  $a0, $s0
/* 01C12C 8001B52C 3C0E8012 */  lui   $t6, %hi(D_8011AE82) # $t6, 0x8012
/* 01C130 8001B530 85CEAE82 */  lh    $t6, %lo(D_8011AE82)($t6)
/* 01C134 8001B534 00000000 */  nop   
/* 01C138 8001B538 144E003C */  bne   $v0, $t6, .L8001B62C
/* 01C13C 8001B53C 8FBF001C */   lw    $ra, 0x1c($sp)
/* 01C140 8001B540 0C0078A7 */  jal   get_misc_asset
/* 01C144 8001B544 2404001C */   li    $a0, 28
/* 01C148 8001B548 24040018 */  li    $a0, 24
/* 01C14C 8001B54C 0C0078A7 */  jal   get_misc_asset
/* 01C150 8001B550 AFA20028 */   sw    $v0, 0x28($sp)
/* 01C154 8001B554 8FA80028 */  lw    $t0, 0x28($sp)
/* 01C158 8001B558 2407FFFF */  li    $a3, -1
/* 01C15C 8001B55C 810F0000 */  lb    $t7, ($t0)
/* 01C160 8001B560 8FAD0020 */  lw    $t5, 0x20($sp)
/* 01C164 8001B564 10EF000B */  beq   $a3, $t7, .L8001B594
/* 01C168 8001B568 00003025 */   move  $a2, $zero
/* 01C16C 8001B56C 81180000 */  lb    $t8, ($t0)
/* 01C170 8001B570 01002021 */  addu  $a0, $t0, $zero
/* 01C174 8001B574 12180008 */  beq   $s0, $t8, .L8001B598
/* 01C178 8001B578 0106C821 */   addu  $t9, $t0, $a2
.L8001B57C:
/* 01C17C 8001B57C 80850001 */  lb    $a1, 1($a0)
/* 01C180 8001B580 24C60001 */  addiu $a2, $a2, 1
/* 01C184 8001B584 10E50003 */  beq   $a3, $a1, .L8001B594
/* 01C188 8001B588 24840001 */   addiu $a0, $a0, 1
/* 01C18C 8001B58C 1605FFFB */  bne   $s0, $a1, .L8001B57C
/* 01C190 8001B590 00000000 */   nop   
.L8001B594:
/* 01C194 8001B594 0106C821 */  addu  $t9, $t0, $a2
.L8001B598:
/* 01C198 8001B598 83290000 */  lb    $t1, ($t9)
/* 01C19C 8001B59C 00065040 */  sll   $t2, $a2, 1
/* 01C1A0 8001B5A0 10E90021 */  beq   $a3, $t1, .L8001B628
/* 01C1A4 8001B5A4 004A5821 */   addu  $t3, $v0, $t2
/* 01C1A8 8001B5A8 3C0E8012 */  lui   $t6, %hi(D_8011AE82) # $t6, 0x8012
/* 01C1AC 8001B5AC 85CEAE82 */  lh    $t6, %lo(D_8011AE82)($t6)
/* 01C1B0 8001B5B0 00104840 */  sll   $t1, $s0, 1
/* 01C1B4 8001B5B4 000E7880 */  sll   $t7, $t6, 2
/* 01C1B8 8001B5B8 01AFC021 */  addu  $t8, $t5, $t7
/* 01C1BC 8001B5BC 8F19003C */  lw    $t9, 0x3c($t8)
/* 01C1C0 8001B5C0 956C0000 */  lhu   $t4, ($t3)
/* 01C1C4 8001B5C4 03295021 */  addu  $t2, $t9, $t1
/* 01C1C8 8001B5C8 954B0000 */  lhu   $t3, ($t2)
/* 01C1CC 8001B5CC 00000000 */  nop   
/* 01C1D0 8001B5D0 018B082A */  slt   $at, $t4, $t3
/* 01C1D4 8001B5D4 14200015 */  bnez  $at, .L8001B62C
/* 01C1D8 8001B5D8 8FBF001C */   lw    $ra, 0x1c($sp)
/* 01C1DC 8001B5DC 0C027AC2 */  jal   get_eeprom_settings
/* 01C1E0 8001B5E0 AFA6002C */   sw    $a2, 0x2c($sp)
/* 01C1E4 8001B5E4 8FA6002C */  lw    $a2, 0x2c($sp)
/* 01C1E8 8001B5E8 240E0010 */  li    $t6, 16
/* 01C1EC 8001B5EC 00CE6804 */  sllv  $t5, $t6, $a2
/* 01C1F0 8001B5F0 000DC7C3 */  sra   $t8, $t5, 0x1f
/* 01C1F4 8001B5F4 00585024 */  and   $t2, $v0, $t8
/* 01C1F8 8001B5F8 15400005 */  bnez  $t2, .L8001B610
/* 01C1FC 8001B5FC 006D5824 */   and   $t3, $v1, $t5
/* 01C200 8001B600 15600003 */  bnez  $t3, .L8001B610
/* 01C204 8001B604 240F0001 */   li    $t7, 1
/* 01C208 8001B608 3C01800E */  lui   $at, %hi(gBeatStaffGhost) # $at, 0x800e
/* 01C20C 8001B60C A02FC738 */  sb    $t7, %lo(gBeatStaffGhost)($at)
.L8001B610:
/* 01C210 8001B610 0C006CBC */  jal   func_8001B2F0
/* 01C214 8001B614 02002025 */   move  $a0, $s0
/* 01C218 8001B618 14400003 */  bnez  $v0, .L8001B628
/* 01C21C 8001B61C 24090001 */   li    $t1, 1
/* 01C220 8001B620 3C01800E */  lui   $at, %hi(gTimeTrialStaffGhost) # $at, 0x800e
/* 01C224 8001B624 A029C734 */  sb    $t1, %lo(gTimeTrialStaffGhost)($at)
.L8001B628:
/* 01C228 8001B628 8FBF001C */  lw    $ra, 0x1c($sp)
.L8001B62C:
/* 01C22C 8001B62C 3C02800E */  lui   $v0, %hi(gTimeTrialStaffGhost) # $v0, 0x800e
/* 01C230 8001B630 9042C734 */  lbu   $v0, %lo(gTimeTrialStaffGhost)($v0)
/* 01C234 8001B634 8FB00018 */  lw    $s0, 0x18($sp)
/* 01C238 8001B638 03E00008 */  jr    $ra
/* 01C23C 8001B63C 27BD0030 */   addiu $sp, $sp, 0x30

