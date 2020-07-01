glabel func_80064E54
/* 065A54 80064E54 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 065A58 80064E58 AFA5002C */  sw    $a1, 0x2c($sp)
/* 065A5C 80064E5C AFBF0024 */  sw    $ra, 0x24($sp)
/* 065A60 80064E60 AFB00020 */  sw    $s0, 0x20($sp)
/* 065A64 80064E64 3C05800D */  lui   $a1, %hi(D_800CA0D0) # $a1, 0x800d
/* 065A68 80064E68 3C06800D */  lui   $a2, %hi(D_800CAA7C) # $a2, 0x800d
/* 065A6C 80064E6C 00808025 */  move  $s0, $a0
/* 065A70 80064E70 24C6AA7C */  addiu $a2, %lo(D_800CAA7C) # addiu $a2, $a2, -0x5584
/* 065A74 80064E74 24A5A0D0 */  addiu $a1, %lo(D_800CA0D0) # addiu $a1, $a1, -0x5f30
/* 065A78 80064E78 0C03282C */  jal   func_800CA0B0
/* 065A7C 80064E7C 24070004 */   li    $a3, 4
/* 065A80 80064E80 8FA6002C */  lw    $a2, 0x2c($sp)
/* 065A84 80064E84 240E0050 */  li    $t6, 80
/* 065A88 80064E88 AFAE0010 */  sw    $t6, 0x10($sp)
/* 065A8C 80064E8C 00002025 */  move  $a0, $zero
/* 065A90 80064E90 00002825 */  move  $a1, $zero
/* 065A94 80064E94 0C031DFC */  jal   func_800C77F0
/* 065A98 80064E98 24070001 */   li    $a3, 1
/* 065A9C 80064E9C 24030001 */  li    $v1, 1
/* 065AA0 80064EA0 AE020014 */  sw    $v0, 0x14($s0)
/* 065AA4 80064EA4 AE030038 */  sw    $v1, 0x38($s0)
/* 065AA8 80064EA8 AE000048 */  sw    $zero, 0x48($s0)
/* 065AAC 80064EAC A603001A */  sh    $v1, 0x1a($s0)
/* 065AB0 80064EB0 A6030028 */  sh    $v1, 0x28($s0)
/* 065AB4 80064EB4 A603002E */  sh    $v1, 0x2e($s0)
/* 065AB8 80064EB8 A603001C */  sh    $v1, 0x1c($s0)
/* 065ABC 80064EBC A603001E */  sh    $v1, 0x1e($s0)
/* 065AC0 80064EC0 A6000020 */  sh    $zero, 0x20($s0)
/* 065AC4 80064EC4 A6000022 */  sh    $zero, 0x22($s0)
/* 065AC8 80064EC8 A6030026 */  sh    $v1, 0x26($s0)
/* 065ACC 80064ECC A6000024 */  sh    $zero, 0x24($s0)
/* 065AD0 80064ED0 AE000030 */  sw    $zero, 0x30($s0)
/* 065AD4 80064ED4 AE000034 */  sw    $zero, 0x34($s0)
/* 065AD8 80064ED8 A6000018 */  sh    $zero, 0x18($s0)
/* 065ADC 80064EDC AE00003C */  sw    $zero, 0x3c($s0)
/* 065AE0 80064EE0 AE000040 */  sw    $zero, 0x40($s0)
/* 065AE4 80064EE4 AE000044 */  sw    $zero, 0x44($s0)
/* 065AE8 80064EE8 8FBF0024 */  lw    $ra, 0x24($sp)
/* 065AEC 80064EEC 8FB00020 */  lw    $s0, 0x20($sp)
/* 065AF0 80064EF0 03E00008 */  jr    $ra
/* 065AF4 80064EF4 27BD0028 */   addiu $sp, $sp, 0x28

