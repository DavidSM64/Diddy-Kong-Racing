glabel func_8007AC70
/* 07B870 8007AC70 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 07B874 8007AC74 AFBF0014 */  sw    $ra, 0x14($sp)
/* 07B878 8007AC78 3C05FF00 */  lui   $a1, (0xFF00FFFF >> 16) # lui $a1, 0xff00
/* 07B87C 8007AC7C 34A5FFFF */  ori   $a1, (0xFF00FFFF & 0xFFFF) # ori $a1, $a1, 0xffff
/* 07B880 8007AC80 0C01C327 */  jal   allocate_from_main_pool_safe
/* 07B884 8007AC84 240415E0 */   li    $a0, 5600
/* 07B888 8007AC88 3C018012 */  lui   $at, %hi(D_80126328) # $at, 0x8012
/* 07B88C 8007AC8C 3C05FF00 */  lui   $a1, (0xFF00FFFF >> 16) # lui $a1, 0xff00
/* 07B890 8007AC90 AC226328 */  sw    $v0, %lo(D_80126328)($at)
/* 07B894 8007AC94 34A5FFFF */  ori   $a1, (0xFF00FFFF & 0xFFFF) # ori $a1, $a1, 0xffff
/* 07B898 8007AC98 0C01C327 */  jal   allocate_from_main_pool_safe
/* 07B89C 8007AC9C 24040280 */   li    $a0, 640
/* 07B8A0 8007ACA0 3C018012 */  lui   $at, %hi(D_8012632C) # $at, 0x8012
/* 07B8A4 8007ACA4 AC22632C */  sw    $v0, %lo(D_8012632C)($at)
/* 07B8A8 8007ACA8 3C018012 */  lui   $at, %hi(D_80126330) # $at, 0x8012
/* 07B8AC 8007ACAC AC206330 */  sw    $zero, %lo(D_80126330)($at)
/* 07B8B0 8007ACB0 3C018012 */  lui   $at, %hi(D_80126340) # $at, 0x8012
/* 07B8B4 8007ACB4 AC206340 */  sw    $zero, %lo(D_80126340)($at)
/* 07B8B8 8007ACB8 0C01DB16 */  jal   load_asset_section_from_rom
/* 07B8BC 8007ACBC 24040005 */   li    $a0, 5
/* 07B8C0 8007ACC0 3C058012 */  lui   $a1, %hi(D_80126320) # $a1, 0x8012
/* 07B8C4 8007ACC4 24A56320 */  addiu $a1, %lo(D_80126320) # addiu $a1, $a1, 0x6320
/* 07B8C8 8007ACC8 ACA20000 */  sw    $v0, ($a1)
/* 07B8CC 8007ACCC 0C01DB16 */  jal   load_asset_section_from_rom
/* 07B8D0 8007ACD0 24040003 */   li    $a0, 3
/* 07B8D4 8007ACD4 3C058012 */  lui   $a1, %hi(D_80126320) # $a1, 0x8012
/* 07B8D8 8007ACD8 24A56320 */  addiu $a1, %lo(D_80126320) # addiu $a1, $a1, 0x6320
/* 07B8DC 8007ACDC 8CA40000 */  lw    $a0, ($a1)
/* 07B8E0 8007ACE0 ACA20004 */  sw    $v0, 4($a1)
/* 07B8E4 8007ACE4 8C8E0000 */  lw    $t6, ($a0)
/* 07B8E8 8007ACE8 2407FFFF */  li    $a3, -1
/* 07B8EC 8007ACEC 10EE0006 */  beq   $a3, $t6, .L8007AD08
/* 07B8F0 8007ACF0 00001825 */   move  $v1, $zero
/* 07B8F4 8007ACF4 00801025 */  move  $v0, $a0
.L8007ACF8:
/* 07B8F8 8007ACF8 8C4F0004 */  lw    $t7, 4($v0)
/* 07B8FC 8007ACFC 24630001 */  addiu $v1, $v1, 1
/* 07B900 8007AD00 14EFFFFD */  bne   $a3, $t7, .L8007ACF8
/* 07B904 8007AD04 24420004 */   addiu $v0, $v0, 4
.L8007AD08:
/* 07B908 8007AD08 3C068012 */  lui   $a2, %hi(D_80126338) # $a2, 0x8012
/* 07B90C 8007AD0C 8CA40004 */  lw    $a0, 4($a1)
/* 07B910 8007AD10 24C66338 */  addiu $a2, %lo(D_80126338) # addiu $a2, $a2, 0x6338
/* 07B914 8007AD14 2463FFFF */  addiu $v1, $v1, -1
/* 07B918 8007AD18 ACC30000 */  sw    $v1, ($a2)
/* 07B91C 8007AD1C 8C980000 */  lw    $t8, ($a0)
/* 07B920 8007AD20 00001825 */  move  $v1, $zero
/* 07B924 8007AD24 10F80006 */  beq   $a3, $t8, .L8007AD40
/* 07B928 8007AD28 3C05FF00 */   lui   $a1, (0xFF00FFFF >> 16) # lui $a1, 0xff00
/* 07B92C 8007AD2C 00801025 */  move  $v0, $a0
.L8007AD30:
/* 07B930 8007AD30 8C590004 */  lw    $t9, 4($v0)
/* 07B934 8007AD34 24630001 */  addiu $v1, $v1, 1
/* 07B938 8007AD38 14F9FFFD */  bne   $a3, $t9, .L8007AD30
/* 07B93C 8007AD3C 24420004 */   addiu $v0, $v0, 4
.L8007AD40:
/* 07B940 8007AD40 2463FFFF */  addiu $v1, $v1, -1
/* 07B944 8007AD44 ACC30004 */  sw    $v1, 4($a2)
/* 07B948 8007AD48 24040320 */  li    $a0, 800
/* 07B94C 8007AD4C 0C01C327 */  jal   allocate_from_main_pool_safe
/* 07B950 8007AD50 34A5FFFF */   ori   $a1, (0xFF00FFFF & 0xFFFF) # ori $a1, $a1, 0xffff
/* 07B954 8007AD54 3C018012 */  lui   $at, %hi(D_8012634C) # $at, 0x8012
/* 07B958 8007AD58 3C05FF00 */  lui   $a1, (0xFF00FFFF >> 16) # lui $a1, 0xff00
/* 07B95C 8007AD5C AC22634C */  sw    $v0, %lo(D_8012634C)($at)
/* 07B960 8007AD60 34A5FFFF */  ori   $a1, (0xFF00FFFF & 0xFFFF) # ori $a1, $a1, 0xffff
/* 07B964 8007AD64 0C01C327 */  jal   allocate_from_main_pool_safe
/* 07B968 8007AD68 24040200 */   li    $a0, 512
/* 07B96C 8007AD6C 3C018012 */  lui   $at, %hi(D_80126350) # $at, 0x8012
/* 07B970 8007AD70 AC226350 */  sw    $v0, %lo(D_80126350)($at)
/* 07B974 8007AD74 3C018012 */  lui   $at, %hi(D_80126358) # $at, 0x8012
/* 07B978 8007AD78 AC206358 */  sw    $zero, %lo(D_80126358)($at)
/* 07B97C 8007AD7C 0C01DB16 */  jal   load_asset_section_from_rom
/* 07B980 8007AD80 2404000D */   li    $a0, 13
/* 07B984 8007AD84 3C058012 */  lui   $a1, %hi(D_80126348) # $a1, 0x8012
/* 07B988 8007AD88 3C068012 */  lui   $a2, %hi(D_80126354) # $a2, 0x8012
/* 07B98C 8007AD8C 24C66354 */  addiu $a2, %lo(D_80126354) # addiu $a2, $a2, 0x6354
/* 07B990 8007AD90 24A56348 */  addiu $a1, %lo(D_80126348) # addiu $a1, $a1, 0x6348
/* 07B994 8007AD94 00004080 */  sll   $t0, $zero, 2
/* 07B998 8007AD98 ACA20000 */  sw    $v0, ($a1)
/* 07B99C 8007AD9C ACC00000 */  sw    $zero, ($a2)
/* 07B9A0 8007ADA0 00484821 */  addu  $t1, $v0, $t0
/* 07B9A4 8007ADA4 8D2A0000 */  lw    $t2, ($t1)
/* 07B9A8 8007ADA8 2407FFFF */  li    $a3, -1
/* 07B9AC 8007ADAC 00402025 */  move  $a0, $v0
/* 07B9B0 8007ADB0 10EA0009 */  beq   $a3, $t2, .L8007ADD8
/* 07B9B4 8007ADB4 00001825 */   move  $v1, $zero
/* 07B9B8 8007ADB8 246B0001 */  addiu $t3, $v1, 1
.L8007ADBC:
/* 07B9BC 8007ADBC 000B6080 */  sll   $t4, $t3, 2
/* 07B9C0 8007ADC0 008C6821 */  addu  $t5, $a0, $t4
/* 07B9C4 8007ADC4 ACCB0000 */  sw    $t3, ($a2)
/* 07B9C8 8007ADC8 8DAE0000 */  lw    $t6, ($t5)
/* 07B9CC 8007ADCC 01601825 */  move  $v1, $t3
/* 07B9D0 8007ADD0 14EEFFFA */  bne   $a3, $t6, .L8007ADBC
/* 07B9D4 8007ADD4 246B0001 */   addiu $t3, $v1, 1
.L8007ADD8:
/* 07B9D8 8007ADD8 246FFFFF */  addiu $t7, $v1, -1
/* 07B9DC 8007ADDC 3C05FF00 */  lui   $a1, (0xFF00FFFF >> 16) # lui $a1, 0xff00
/* 07B9E0 8007ADE0 ACCF0000 */  sw    $t7, ($a2)
/* 07B9E4 8007ADE4 34A5FFFF */  ori   $a1, (0xFF00FFFF & 0xFFFF) # ori $a1, $a1, 0xffff
/* 07B9E8 8007ADE8 0C01C327 */  jal   allocate_from_main_pool_safe
/* 07B9EC 8007ADEC 24040028 */   li    $a0, 40
/* 07B9F0 8007ADF0 3C018012 */  lui   $at, %hi(D_8012636C) # $at, 0x8012
/* 07B9F4 8007ADF4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 07B9F8 8007ADF8 AC22636C */  sw    $v0, %lo(D_8012636C)($at)
/* 07B9FC 8007ADFC 3C018012 */  lui   $at, %hi(D_80126344) # $at, 0x8012
/* 07BA00 8007AE00 AC206344 */  sw    $zero, %lo(D_80126344)($at)
/* 07BA04 8007AE04 03E00008 */  jr    $ra
/* 07BA08 8007AE08 27BD0018 */   addiu $sp, $sp, 0x18

