glabel func_8002C7D4
/* 02D3D4 8002C7D4 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 02D3D8 8002C7D8 AFBF002C */  sw    $ra, 0x2c($sp)
/* 02D3DC 8002C7DC AFB40028 */  sw    $s4, 0x28($sp)
/* 02D3E0 8002C7E0 AFB30024 */  sw    $s3, 0x24($sp)
/* 02D3E4 8002C7E4 AFB20020 */  sw    $s2, 0x20($sp)
/* 02D3E8 8002C7E8 AFB1001C */  sw    $s1, 0x1c($sp)
/* 02D3EC 8002C7EC 0C002CA4 */  jal   func_8000B290
/* 02D3F0 8002C7F0 AFB00018 */   sw    $s0, 0x18($sp)
/* 02D3F4 8002C7F4 3C0E8012 */  lui   $t6, %hi(D_8011D384) # $t6, 0x8012
/* 02D3F8 8002C7F8 8DCED384 */  lw    $t6, %lo(D_8011D384)($t6)
/* 02D3FC 8002C7FC 00000000 */  nop   
/* 02D400 8002C800 11C00003 */  beqz  $t6, .L8002C810
/* 02D404 8002C804 00000000 */   nop   
/* 02D408 8002C808 0C02DF48 */  jal   func_800B7D20
/* 02D40C 8002C80C 00000000 */   nop   
.L8002C810:
/* 02D410 8002C810 3C14800E */  lui   $s4, %hi(D_800DC918) # $s4, 0x800e
/* 02D414 8002C814 2694C918 */  addiu $s4, %lo(D_800DC918) # addiu $s4, $s4, -0x36e8
/* 02D418 8002C818 8E910000 */  lw    $s1, ($s4)
/* 02D41C 8002C81C 00008025 */  move  $s0, $zero
/* 02D420 8002C820 862F0018 */  lh    $t7, 0x18($s1)
/* 02D424 8002C824 00009025 */  move  $s2, $zero
/* 02D428 8002C828 19E0000E */  blez  $t7, .L8002C864
/* 02D42C 8002C82C 00000000 */   nop   
.L8002C830:
/* 02D430 8002C830 8E380000 */  lw    $t8, ($s1)
/* 02D434 8002C834 00000000 */  nop   
/* 02D438 8002C838 0312C821 */  addu  $t9, $t8, $s2
/* 02D43C 8002C83C 8F240000 */  lw    $a0, ($t9)
/* 02D440 8002C840 0C01ECAF */  jal   free_texture
/* 02D444 8002C844 00000000 */   nop   
/* 02D448 8002C848 8E910000 */  lw    $s1, ($s4)
/* 02D44C 8002C84C 26100001 */  addiu $s0, $s0, 1
/* 02D450 8002C850 86280018 */  lh    $t0, 0x18($s1)
/* 02D454 8002C854 26520008 */  addiu $s2, $s2, 8
/* 02D458 8002C858 0208082A */  slt   $at, $s0, $t0
/* 02D45C 8002C85C 1420FFF4 */  bnez  $at, .L8002C830
/* 02D460 8002C860 00000000 */   nop   
.L8002C864:
/* 02D464 8002C864 3C048012 */  lui   $a0, %hi(D_8011D30C) # $a0, 0x8012
/* 02D468 8002C868 8C84D30C */  lw    $a0, %lo(D_8011D30C)($a0)
/* 02D46C 8002C86C 0C01C450 */  jal   free_from_memory_pool
/* 02D470 8002C870 00000000 */   nop   
/* 02D474 8002C874 3C048012 */  lui   $a0, %hi(D_8011D370) # $a0, 0x8012
/* 02D478 8002C878 8C84D370 */  lw    $a0, %lo(D_8011D370)($a0)
/* 02D47C 8002C87C 0C01C450 */  jal   free_from_memory_pool
/* 02D480 8002C880 00000000 */   nop   
/* 02D484 8002C884 3C048012 */  lui   $a0, %hi(D_8011D374) # $a0, 0x8012
/* 02D488 8002C888 8C84D374 */  lw    $a0, %lo(D_8011D374)($a0)
/* 02D48C 8002C88C 0C01C450 */  jal   free_from_memory_pool
/* 02D490 8002C890 00000000 */   nop   
/* 02D494 8002C894 8E890000 */  lw    $t1, ($s4)
/* 02D498 8002C898 00000000 */  nop   
/* 02D49C 8002C89C 8D240020 */  lw    $a0, 0x20($t1)
/* 02D4A0 8002C8A0 0C01F32C */  jal   free_sprite
/* 02D4A4 8002C8A4 00000000 */   nop   
/* 02D4A8 8002C8A8 3C118012 */  lui   $s1, %hi(D_8011D350) # $s1, 0x8012
/* 02D4AC 8002C8AC 3C128012 */  lui   $s2, %hi(D_8011D320) # $s2, 0x8012
/* 02D4B0 8002C8B0 3C108012 */  lui   $s0, %hi(D_8011D338) # $s0, 0x8012
/* 02D4B4 8002C8B4 3C138012 */  lui   $s3, %hi(D_8011D348) # $s3, 0x8012
/* 02D4B8 8002C8B8 2673D348 */  addiu $s3, %lo(D_8011D348) # addiu $s3, $s3, -0x2cb8
/* 02D4BC 8002C8BC 2610D338 */  addiu $s0, %lo(D_8011D338) # addiu $s0, $s0, -0x2cc8
/* 02D4C0 8002C8C0 2652D320 */  addiu $s2, %lo(D_8011D320) # addiu $s2, $s2, -0x2ce0
/* 02D4C4 8002C8C4 2631D350 */  addiu $s1, %lo(D_8011D350) # addiu $s1, $s1, -0x2cb0
.L8002C8C8:
/* 02D4C8 8002C8C8 8E240000 */  lw    $a0, ($s1)
/* 02D4CC 8002C8CC 0C01C450 */  jal   free_from_memory_pool
/* 02D4D0 8002C8D0 00000000 */   nop   
/* 02D4D4 8002C8D4 8E440000 */  lw    $a0, ($s2)
/* 02D4D8 8002C8D8 0C01C450 */  jal   free_from_memory_pool
/* 02D4DC 8002C8DC 00000000 */   nop   
/* 02D4E0 8002C8E0 8E040000 */  lw    $a0, ($s0)
/* 02D4E4 8002C8E4 0C01C450 */  jal   free_from_memory_pool
/* 02D4E8 8002C8E8 00000000 */   nop   
/* 02D4EC 8002C8EC 26100004 */  addiu $s0, $s0, 4
/* 02D4F0 8002C8F0 26310004 */  addiu $s1, $s1, 4
/* 02D4F4 8002C8F4 1613FFF4 */  bne   $s0, $s3, .L8002C8C8
/* 02D4F8 8002C8F8 26520004 */   addiu $s2, $s2, 4
/* 02D4FC 8002C8FC 0C0095F4 */  jal   func_800257D0
/* 02D500 8002C900 00000000 */   nop   
/* 02D504 8002C904 3C048012 */  lui   $a0, %hi(D_8011B0B8) # $a0, 0x8012
/* 02D508 8002C908 8C84B0B8 */  lw    $a0, %lo(D_8011B0B8)($a0)
/* 02D50C 8002C90C 00000000 */  nop   
/* 02D510 8002C910 10800005 */  beqz  $a0, .L8002C928
/* 02D514 8002C914 00000000 */   nop   
/* 02D518 8002C918 0C003FEE */  jal   gParticlePtrList_addObject
/* 02D51C 8002C91C 00000000 */   nop   
/* 02D520 8002C920 0C004013 */  jal   gParticlePtrList_flush
/* 02D524 8002C924 00000000 */   nop   
.L8002C928:
/* 02D528 8002C928 0C003181 */  jal   func_8000C604
/* 02D52C 8002C92C 00000000 */   nop   
/* 02D530 8002C930 8FBF002C */  lw    $ra, 0x2c($sp)
/* 02D534 8002C934 AE800000 */  sw    $zero, ($s4)
/* 02D538 8002C938 8FB40028 */  lw    $s4, 0x28($sp)
/* 02D53C 8002C93C 8FB00018 */  lw    $s0, 0x18($sp)
/* 02D540 8002C940 8FB1001C */  lw    $s1, 0x1c($sp)
/* 02D544 8002C944 8FB20020 */  lw    $s2, 0x20($sp)
/* 02D548 8002C948 8FB30024 */  lw    $s3, 0x24($sp)
/* 02D54C 8002C94C 03E00008 */  jr    $ra
/* 02D550 8002C950 27BD0030 */   addiu $sp, $sp, 0x30

