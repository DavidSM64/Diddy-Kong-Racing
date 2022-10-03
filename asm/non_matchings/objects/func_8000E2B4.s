.late_rodata
glabel D_800E51AC
.float 1.4
glabel D_800E51B0
.float 0.714

.text
glabel func_8000E2B4
/* 00EEB4 8000E2B4 3C038012 */  lui   $v1, %hi(D_8011AD44) # $v1, 0x8012
/* 00EEB8 8000E2B8 2463AD44 */  addiu $v1, %lo(D_8011AD44) # addiu $v1, $v1, -0x52bc
/* 00EEBC 8000E2BC 80620000 */  lb    $v0, ($v1)
/* 00EEC0 8000E2C0 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 00EEC4 8000E2C4 10400079 */  beqz  $v0, .L8000E4AC
/* 00EEC8 8000E2C8 AFBF0014 */   sw    $ra, 0x14($sp)
/* 00EECC 8000E2CC 244EFFFF */  addiu $t6, $v0, -1
/* 00EED0 8000E2D0 A06E0000 */  sb    $t6, ($v1)
/* 00EED4 8000E2D4 806F0000 */  lb    $t7, ($v1)
/* 00EED8 8000E2D8 00000000 */  nop   
/* 00EEDC 8000E2DC 15E00074 */  bnez  $t7, .L8000E4B0
/* 00EEE0 8000E2E0 8FBF0014 */   lw    $ra, 0x14($sp)
/* 00EEE4 8000E2E4 0C01BAA4 */  jal   get_settings
/* 00EEE8 8000E2E8 00000000 */   nop   
/* 00EEEC 8000E2EC 3C048012 */  lui   $a0, %hi(D_8011AD45) # $a0, 0x8012
/* 00EEF0 8000E2F0 8084AD45 */  lb    $a0, %lo(D_8011AD45)($a0)
/* 00EEF4 8000E2F4 24180010 */  li    $t8, 16
/* 00EEF8 8000E2F8 28810005 */  slti  $at, $a0, 5
/* 00EEFC 8000E2FC AFA20028 */  sw    $v0, 0x28($sp)
/* 00EF00 8000E300 A7A0003A */  sh    $zero, 0x3a($sp)
/* 00EF04 8000E304 1020000C */  beqz  $at, .L8000E338
/* 00EF08 8000E308 A3B8002D */   sb    $t8, 0x2d($sp)
/* 00EF0C 8000E30C 80590059 */  lb    $t9, 0x59($v0)
/* 00EF10 8000E310 00044880 */  sll   $t1, $a0, 2
/* 00EF14 8000E314 01244821 */  addu  $t1, $t1, $a0
/* 00EF18 8000E318 00095080 */  sll   $t2, $t1, 2
/* 00EF1C 8000E31C 00194040 */  sll   $t0, $t9, 1
/* 00EF20 8000E320 010A5821 */  addu  $t3, $t0, $t2
/* 00EF24 8000E324 3C03800E */  lui   $v1, %hi(D_800DC7A8) # $v1, 0x800e
/* 00EF28 8000E328 006B1821 */  addu  $v1, $v1, $t3
/* 00EF2C 8000E32C 8463C7A8 */  lh    $v1, %lo(D_800DC7A8)($v1)
/* 00EF30 8000E330 10000006 */  b     .L8000E34C
/* 00EF34 8000E334 00000000 */   nop   
.L8000E338:
/* 00EF38 8000E338 00046040 */  sll   $t4, $a0, 1
# Indexing into D_800DC7B8 starting at index 37?
/* 00EF3C 8000E33C 3C03800E */  lui   $v1, %hi(D_800DC7B8) # $v1, 0x800e
/* 00EF40 8000E340 006C1821 */  addu  $v1, $v1, $t4
/* 00EF44 8000E344 8463C802 */  lh    $v1, %lo(D_800DC7B8+0x4A)/*-0x37fe*/($v1)
/* 00EF48 8000E348 00000000 */  nop   
.L8000E34C:
/* 00EF4C 8000E34C 0C01B6C5 */  jal   set_level_default_vehicle
/* 00EF50 8000E350 A7A30022 */   sh    $v1, 0x22($sp)
/* 00EF54 8000E354 87A30022 */  lh    $v1, 0x22($sp)
/* 00EF58 8000E358 93AD002D */  lbu   $t5, 0x2d($sp)
/* 00EF5C 8000E35C 3C198012 */  lui   $t9, %hi(D_8011AD46) # $t9, 0x8012
/* 00EF60 8000E360 3C098012 */  lui   $t1, %hi(D_8011AD48) # $t1, 0x8012
/* 00EF64 8000E364 3C088012 */  lui   $t0, %hi(D_8011AD4A) # $t0, 0x8012
/* 00EF68 8000E368 3C0A8012 */  lui   $t2, %hi(D_8011AD4C) # $t2, 0x8012
/* 00EF6C 8000E36C 306E0100 */  andi  $t6, $v1, 0x100
/* 00EF70 8000E370 8739AD46 */  lh    $t9, %lo(D_8011AD46)($t9)
/* 00EF74 8000E374 8529AD48 */  lh    $t1, %lo(D_8011AD48)($t1)
/* 00EF78 8000E378 8508AD4A */  lh    $t0, %lo(D_8011AD4A)($t0)
/* 00EF7C 8000E37C 854AAD4C */  lh    $t2, %lo(D_8011AD4C)($t2)
/* 00EF80 8000E380 000E7843 */  sra   $t7, $t6, 1
/* 00EF84 8000E384 01AFC025 */  or    $t8, $t5, $t7
/* 00EF88 8000E388 A3B8002D */  sb    $t8, 0x2d($sp)
/* 00EF8C 8000E38C A7A00036 */  sh    $zero, 0x36($sp)
/* 00EF90 8000E390 A7A00034 */  sh    $zero, 0x34($sp)
/* 00EF94 8000E394 24040001 */  li    $a0, 1
/* 00EF98 8000E398 A3A3002C */  sb    $v1, 0x2c($sp)
/* 00EF9C 8000E39C A7B9002E */  sh    $t9, 0x2e($sp)
/* 00EFA0 8000E3A0 A7A90030 */  sh    $t1, 0x30($sp)
/* 00EFA4 8000E3A4 A7A80032 */  sh    $t0, 0x32($sp)
/* 00EFA8 8000E3A8 0C01486E */  jal   func_800521B8
/* 00EFAC 8000E3AC A7AA0038 */   sh    $t2, 0x38($sp)
/* 00EFB0 8000E3B0 27A4002C */  addiu $a0, $sp, 0x2c
/* 00EFB4 8000E3B4 0C003A95 */  jal   spawn_object
/* 00EFB8 8000E3B8 24050011 */   li    $a1, 17
/* 00EFBC 8000E3BC 3C0C8012 */  lui   $t4, %hi(gObjectStructArrayPtr) # $t4, 0x8012
/* 00EFC0 8000E3C0 8D8CAEE4 */  lw    $t4, %lo(gObjectStructArrayPtr)($t4)
/* 00EFC4 8000E3C4 240B0001 */  li    $t3, 1
/* 00EFC8 8000E3C8 3C018012 */  lui   $at, %hi(gObjectCount) # $at, 0x8012
/* 00EFCC 8000E3CC AC2BAEF0 */  sw    $t3, %lo(gObjectCount)($at)
/* 00EFD0 8000E3D0 3C0E8012 */  lui   $t6, %hi(D_8011AEEC) # $t6, 0x8012
/* 00EFD4 8000E3D4 AD820000 */  sw    $v0, ($t4)
/* 00EFD8 8000E3D8 8DCEAEEC */  lw    $t6, %lo(D_8011AEEC)($t6)
/* 00EFDC 8000E3DC 3C0D8012 */  lui   $t5, %hi(D_8011AEE8) # $t5, 0x8012
/* 00EFE0 8000E3E0 ADC20000 */  sw    $v0, ($t6)
/* 00EFE4 8000E3E4 8DADAEE8 */  lw    $t5, %lo(D_8011AEE8)($t5)
/* 00EFE8 8000E3E8 3C058012 */  lui   $a1, %hi(D_8011AD45) # $a1, 0x8012
/* 00EFEC 8000E3EC ADA20000 */  sw    $v0, ($t5)
/* 00EFF0 8000E3F0 24A5AD45 */  addiu $a1, %lo(D_8011AD45) # addiu $a1, $a1, -0x52bb
/* 00EFF4 8000E3F4 8C430064 */  lw    $v1, 0x64($v0)
/* 00EFF8 8000E3F8 80AF0000 */  lb    $t7, ($a1)
/* 00EFFC 8000E3FC 00000000 */  nop   
/* 00F000 8000E400 A06F01D6 */  sb    $t7, 0x1d6($v1)
/* 00F004 8000E404 80B80000 */  lb    $t8, ($a1)
/* 00F008 8000E408 A0600002 */  sb    $zero, 2($v1)
/* 00F00C 8000E40C A07801D7 */  sb    $t8, 0x1d7($v1)
/* 00F010 8000E410 8FB90028 */  lw    $t9, 0x28($sp)
/* 00F014 8000E414 00000000 */  nop   
/* 00F018 8000E418 83290059 */  lb    $t1, 0x59($t9)
/* 00F01C 8000E41C A4600000 */  sh    $zero, ($v1)
/* 00F020 8000E420 AC600118 */  sw    $zero, 0x118($v1)
/* 00F024 8000E424 A0690003 */  sb    $t1, 3($v1)
/* 00F028 8000E428 0C0270C3 */  jal   get_filtered_cheats
/* 00F02C 8000E42C AFA2003C */   sw    $v0, 0x3c($sp)
/* 00F030 8000E430 8FA4003C */  lw    $a0, 0x3c($sp)
/* 00F034 8000E434 30480010 */  andi  $t0, $v0, 0x10
/* 00F038 8000E438 11000006 */  beqz  $t0, .L8000E454
/* 00F03C 8000E43C 3C01800E */   lui   $at, %hi(D_800E51AC) # $at, 0x800e
/* 00F040 8000E440 C4840008 */  lwc1  $f4, 8($a0)
/* 00F044 8000E444 C42651AC */  lwc1  $f6, %lo(D_800E51AC)($at)
/* 00F048 8000E448 00000000 */  nop   
/* 00F04C 8000E44C 46062202 */  mul.s $f8, $f4, $f6
/* 00F050 8000E450 E4880008 */  swc1  $f8, 8($a0)
.L8000E454:
/* 00F054 8000E454 0C0270C3 */  jal   get_filtered_cheats
/* 00F058 8000E458 AFA4003C */   sw    $a0, 0x3c($sp)
/* 00F05C 8000E45C 8FA4003C */  lw    $a0, 0x3c($sp)
/* 00F060 8000E460 304A0020 */  andi  $t2, $v0, 0x20
/* 00F064 8000E464 11400007 */  beqz  $t2, .L8000E484
/* 00F068 8000E468 3C0B8012 */   lui   $t3, %hi(D_8011AD4C) # $t3, 0x8012
/* 00F06C 8000E46C 3C01800E */  lui   $at, %hi(D_800E51B0) # $at, 0x800e
/* 00F070 8000E470 C43051B0 */  lwc1  $f16, %lo(D_800E51B0)($at)
/* 00F074 8000E474 C48A0008 */  lwc1  $f10, 8($a0)
/* 00F078 8000E478 00000000 */  nop   
/* 00F07C 8000E47C 46105482 */  mul.s $f18, $f10, $f16
/* 00F080 8000E480 E4920008 */  swc1  $f18, 8($a0)
.L8000E484:
/* 00F084 8000E484 AC80003C */  sw    $zero, 0x3c($a0)
/* 00F088 8000E488 856BAD4C */  lh    $t3, %lo(D_8011AD4C)($t3)
/* 00F08C 8000E48C 3C0C8012 */  lui   $t4, %hi(D_8011AD48) # $t4, 0x8012
/* 00F090 8000E490 A48B0000 */  sh    $t3, ($a0)
/* 00F094 8000E494 858CAD48 */  lh    $t4, %lo(D_8011AD48)($t4)
/* 00F098 8000E498 00000000 */  nop   
/* 00F09C 8000E49C 448C2000 */  mtc1  $t4, $f4
/* 00F0A0 8000E4A0 00000000 */  nop   
/* 00F0A4 8000E4A4 468021A0 */  cvt.s.w $f6, $f4
/* 00F0A8 8000E4A8 E4860010 */  swc1  $f6, 0x10($a0)
.L8000E4AC:
/* 00F0AC 8000E4AC 8FBF0014 */  lw    $ra, 0x14($sp)
.L8000E4B0:
/* 00F0B0 8000E4B0 27BD0040 */  addiu $sp, $sp, 0x40
/* 00F0B4 8000E4B4 03E00008 */  jr    $ra
/* 00F0B8 8000E4B8 00000000 */   nop   

