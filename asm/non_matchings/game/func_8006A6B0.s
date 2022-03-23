glabel func_8006A6B0
/* 06B2B0 8006A6B0 27BDFFA8 */  addiu $sp, $sp, -0x58
/* 06B2B4 8006A6B4 AFBF0024 */  sw    $ra, 0x24($sp)
/* 06B2B8 8006A6B8 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 06B2BC 8006A6BC AFB30020 */  sw    $s3, 0x20($sp)
/* 06B2C0 8006A6C0 AFB2001C */  sw    $s2, 0x1c($sp)
/* 06B2C4 8006A6C4 AFB10018 */  sw    $s1, 0x18($sp)
/* 06B2C8 8006A6C8 AFB00014 */  sw    $s0, 0x14($sp)
/* 06B2CC 8006A6CC 34A500FF */  ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 06B2D0 8006A6D0 0C01C327 */  jal   allocate_from_main_pool_safe
/* 06B2D4 8006A6D4 240400C4 */   li    $a0, 196
/* 06B2D8 8006A6D8 AFA20044 */  sw    $v0, 0x44($sp)
/* 06B2DC 8006A6DC 0C01DB16 */  jal   load_asset_section_from_rom
/* 06B2E0 8006A6E0 24040016 */   li    $a0, 22
/* 06B2E4 8006A6E4 3C138012 */  lui   $s3, %hi(gTempAssetTable) # $s3, 0x8012
/* 06B2E8 8006A6E8 26731160 */  addiu $s3, %lo(gTempAssetTable) # addiu $s3, $s3, 0x1160
/* 06B2EC 8006A6EC AE620000 */  sw    $v0, ($s3)
/* 06B2F0 8006A6F0 3C028012 */  lui   $v0, %hi(D_801211C0) # $v0, 0x8012
/* 06B2F4 8006A6F4 3C038012 */  lui   $v1, %hi(D_80121180) # $v1, 0x8012
/* 06B2F8 8006A6F8 24631180 */  addiu $v1, %lo(D_80121180) # addiu $v1, $v1, 0x1180
/* 06B2FC 8006A6FC 244211C0 */  addiu $v0, %lo(D_801211C0) # addiu $v0, $v0, 0x11c0
.L8006A700:
/* 06B300 8006A700 24630010 */  addiu $v1, $v1, 0x10
/* 06B304 8006A704 AC60FFF0 */  sw    $zero, -0x10($v1)
/* 06B308 8006A708 AC60FFF4 */  sw    $zero, -0xc($v1)
/* 06B30C 8006A70C AC60FFF8 */  sw    $zero, -8($v1)
/* 06B310 8006A710 1462FFFB */  bne   $v1, $v0, .L8006A700
/* 06B314 8006A714 AC60FFFC */   sw    $zero, -4($v1)
/* 06B318 8006A718 8E630000 */  lw    $v1, ($s3)
/* 06B31C 8006A71C 3C0A8012 */  lui   $t2, %hi(gNumberOfLevelHeaders) # $t2, 0x8012
/* 06B320 8006A720 254A1170 */  addiu $t2, %lo(gNumberOfLevelHeaders) # addiu $t2, $t2, 0x1170
/* 06B324 8006A724 00007080 */  sll   $t6, $zero, 2
/* 06B328 8006A728 AD400000 */  sw    $zero, ($t2)
/* 06B32C 8006A72C 006E7821 */  addu  $t7, $v1, $t6
/* 06B330 8006A730 8DF80000 */  lw    $t8, ($t7)
/* 06B334 8006A734 240BFFFF */  li    $t3, -1
/* 06B338 8006A738 11780009 */  beq   $t3, $t8, .L8006A760
/* 06B33C 8006A73C 00003025 */   move  $a2, $zero
/* 06B340 8006A740 24D90001 */  addiu $t9, $a2, 1
.L8006A744:
/* 06B344 8006A744 00196080 */  sll   $t4, $t9, 2
/* 06B348 8006A748 006C6821 */  addu  $t5, $v1, $t4
/* 06B34C 8006A74C AD590000 */  sw    $t9, ($t2)
/* 06B350 8006A750 8DAE0000 */  lw    $t6, ($t5)
/* 06B354 8006A754 03203025 */  move  $a2, $t9
/* 06B358 8006A758 156EFFFA */  bne   $t3, $t6, .L8006A744
/* 06B35C 8006A75C 24D90001 */   addiu $t9, $a2, 1
.L8006A760:
/* 06B360 8006A760 24CFFFFF */  addiu $t7, $a2, -1
/* 06B364 8006A764 000FC080 */  sll   $t8, $t7, 2
/* 06B368 8006A768 030FC023 */  subu  $t8, $t8, $t7
/* 06B36C 8006A76C 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 06B370 8006A770 AD4F0000 */  sw    $t7, ($t2)
/* 06B374 8006A774 34A500FF */  ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 06B378 8006A778 0C01C327 */  jal   allocate_from_main_pool_safe
/* 06B37C 8006A77C 00182040 */   sll   $a0, $t8, 1
/* 06B380 8006A780 3C0A8012 */  lui   $t2, %hi(gNumberOfLevelHeaders) # $t2, 0x8012
/* 06B384 8006A784 254A1170 */  addiu $t2, %lo(gNumberOfLevelHeaders) # addiu $t2, $t2, 0x1170
/* 06B388 8006A788 8FB90044 */  lw    $t9, 0x44($sp)
/* 06B38C 8006A78C 8D4C0000 */  lw    $t4, ($t2)
/* 06B390 8006A790 3C088012 */  lui   $t0, %hi(D_80121178+4) # $t0, 0x8012
/* 06B394 8006A794 3C098012 */  lui   $t1, %hi(gNumberOfWorlds) # $t1, 0x8012
/* 06B398 8006A798 3C108012 */  lui   $s0, %hi(gCurrentLevelHeader) # $s0, 0x8012
/* 06B39C 8006A79C 26101168 */  addiu $s0, %lo(gCurrentLevelHeader) # addiu $s0, $s0, 0x1168
/* 06B3A0 8006A7A0 25291174 */  addiu $t1, %lo(gNumberOfWorlds) # addiu $t1, $t1, 0x1174
/* 06B3A4 8006A7A4 2508117C */  addiu $t0, %lo(D_80121178+4) # addiu $t0, $t0, 0x117c
/* 06B3A8 8006A7A8 240BFFFF */  li    $t3, -1
/* 06B3AC 8006A7AC AD020000 */  sw    $v0, ($t0)
/* 06B3B0 8006A7B0 AD2B0000 */  sw    $t3, ($t1)
/* 06B3B4 8006A7B4 00008825 */  move  $s1, $zero
/* 06B3B8 8006A7B8 1980004B */  blez  $t4, .L8006A8E8
/* 06B3BC 8006A7BC AE190000 */   sw    $t9, ($s0)
/* 06B3C0 8006A7C0 00009025 */  move  $s2, $zero
/* 06B3C4 8006A7C4 00001825 */  move  $v1, $zero
.L8006A7C8:
/* 06B3C8 8006A7C8 8E6D0000 */  lw    $t5, ($s3)
/* 06B3CC 8006A7CC 8E050000 */  lw    $a1, ($s0)
/* 06B3D0 8006A7D0 01B27021 */  addu  $t6, $t5, $s2
/* 06B3D4 8006A7D4 8DC60000 */  lw    $a2, ($t6)
/* 06B3D8 8006A7D8 AFA3002C */  sw    $v1, 0x2c($sp)
/* 06B3DC 8006A7DC 24040017 */  li    $a0, 23
/* 06B3E0 8006A7E0 0C01DB9A */  jal   load_asset_to_address
/* 06B3E4 8006A7E4 240700C4 */   li    $a3, 196
/* 06B3E8 8006A7E8 8E050000 */  lw    $a1, ($s0)
/* 06B3EC 8006A7EC 3C098012 */  lui   $t1, %hi(gNumberOfWorlds) # $t1, 0x8012
/* 06B3F0 8006A7F0 25291174 */  addiu $t1, %lo(gNumberOfWorlds) # addiu $t1, $t1, 0x1174
/* 06B3F4 8006A7F4 8D2F0000 */  lw    $t7, ($t1)
/* 06B3F8 8006A7F8 80A40000 */  lb    $a0, ($a1)
/* 06B3FC 8006A7FC 8FA3002C */  lw    $v1, 0x2c($sp)
/* 06B400 8006A800 3C088012 */  lui   $t0, %hi(D_80121178+4) # $t0, 0x8012
/* 06B404 8006A804 3C0A8012 */  lui   $t2, %hi(gNumberOfLevelHeaders) # $t2, 0x8012
/* 06B408 8006A808 01E4082A */  slt   $at, $t7, $a0
/* 06B40C 8006A80C 254A1170 */  addiu $t2, %lo(gNumberOfLevelHeaders) # addiu $t2, $t2, 0x1170
/* 06B410 8006A810 10200002 */  beqz  $at, .L8006A81C
/* 06B414 8006A814 2508117C */   addiu $t0, %lo(D_80121178+4) # addiu $t0, $t0, 0x117c
/* 06B418 8006A818 AD240000 */  sw    $a0, ($t1)
.L8006A81C:
/* 06B41C 8006A81C 80A4004C */  lb    $a0, 0x4c($a1)
/* 06B420 8006A820 26310001 */  addiu $s1, $s1, 1
/* 06B424 8006A824 0480000A */  bltz  $a0, .L8006A850
/* 06B428 8006A828 28810010 */   slti  $at, $a0, 0x10
/* 06B42C 8006A82C 10200008 */  beqz  $at, .L8006A850
/* 06B430 8006A830 0004C080 */   sll   $t8, $a0, 2
/* 06B434 8006A834 3C198012 */  lui   $t9, %hi(D_80121180) # $t9, 0x8012
/* 06B438 8006A838 27391180 */  addiu $t9, %lo(D_80121180) # addiu $t9, $t9, 0x1180
/* 06B43C 8006A83C 03191021 */  addu  $v0, $t8, $t9
/* 06B440 8006A840 8C4C0000 */  lw    $t4, ($v0)
/* 06B444 8006A844 00000000 */  nop   
/* 06B448 8006A848 258D0001 */  addiu $t5, $t4, 1
/* 06B44C 8006A84C AC4D0000 */  sw    $t5, ($v0)
.L8006A850:
/* 06B450 8006A850 8D0F0000 */  lw    $t7, ($t0)
/* 06B454 8006A854 80AE0000 */  lb    $t6, ($a1)
/* 06B458 8006A858 01E3C021 */  addu  $t8, $t7, $v1
/* 06B45C 8006A85C A30E0000 */  sb    $t6, ($t8)
/* 06B460 8006A860 8E190000 */  lw    $t9, ($s0)
/* 06B464 8006A864 8D0D0000 */  lw    $t5, ($t0)
/* 06B468 8006A868 832C004C */  lb    $t4, 0x4c($t9)
/* 06B46C 8006A86C 01A37821 */  addu  $t7, $t5, $v1
/* 06B470 8006A870 A1EC0001 */  sb    $t4, 1($t7)
/* 06B474 8006A874 8E0E0000 */  lw    $t6, ($s0)
/* 06B478 8006A878 8D0C0000 */  lw    $t4, ($t0)
/* 06B47C 8006A87C 81D9004E */  lb    $t9, 0x4e($t6)
/* 06B480 8006A880 01837821 */  addu  $t7, $t4, $v1
/* 06B484 8006A884 00196900 */  sll   $t5, $t9, 4
/* 06B488 8006A888 A1ED0002 */  sb    $t5, 2($t7)
/* 06B48C 8006A88C 8D0E0000 */  lw    $t6, ($t0)
/* 06B490 8006A890 8E190000 */  lw    $t9, ($s0)
/* 06B494 8006A894 01C31021 */  addu  $v0, $t6, $v1
/* 06B498 8006A898 832C004D */  lb    $t4, 0x4d($t9)
/* 06B49C 8006A89C 80580002 */  lb    $t8, 2($v0)
/* 06B4A0 8006A8A0 318D000F */  andi  $t5, $t4, 0xf
/* 06B4A4 8006A8A4 030D7825 */  or    $t7, $t8, $t5
/* 06B4A8 8006A8A8 A04F0002 */  sb    $t7, 2($v0)
/* 06B4AC 8006A8AC 8D190000 */  lw    $t9, ($t0)
/* 06B4B0 8006A8B0 240E0001 */  li    $t6, 1
/* 06B4B4 8006A8B4 03236021 */  addu  $t4, $t9, $v1
/* 06B4B8 8006A8B8 A18E0003 */  sb    $t6, 3($t4)
/* 06B4BC 8006A8BC 8E180000 */  lw    $t8, ($s0)
/* 06B4C0 8006A8C0 8D0F0000 */  lw    $t7, ($t0)
/* 06B4C4 8006A8C4 870D00B0 */  lh    $t5, 0xb0($t8)
/* 06B4C8 8006A8C8 01E3C821 */  addu  $t9, $t7, $v1
/* 06B4CC 8006A8CC A72D0004 */  sh    $t5, 4($t9)
/* 06B4D0 8006A8D0 8D4E0000 */  lw    $t6, ($t2)
/* 06B4D4 8006A8D4 24630006 */  addiu $v1, $v1, 6
/* 06B4D8 8006A8D8 022E082A */  slt   $at, $s1, $t6
/* 06B4DC 8006A8DC 1420FFBA */  bnez  $at, .L8006A7C8
/* 06B4E0 8006A8E0 26520004 */   addiu $s2, $s2, 4
/* 06B4E4 8006A8E4 00008825 */  move  $s1, $zero
.L8006A8E8:
/* 06B4E8 8006A8E8 8D2C0000 */  lw    $t4, ($t1)
/* 06B4EC 8006A8EC 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 06B4F0 8006A8F0 25840001 */  addiu $a0, $t4, 1
/* 06B4F4 8006A8F4 AD240000 */  sw    $a0, ($t1)
/* 06B4F8 8006A8F8 0C01C327 */  jal   allocate_from_main_pool_safe
/* 06B4FC 8006A8FC 34A500FF */   ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 06B500 8006A900 3C098012 */  lui   $t1, %hi(gNumberOfWorlds) # $t1, 0x8012
/* 06B504 8006A904 25291174 */  addiu $t1, %lo(gNumberOfWorlds) # addiu $t1, $t1, 0x1174
/* 06B508 8006A908 8D2F0000 */  lw    $t7, ($t1)
/* 06B50C 8006A90C 3C048012 */  lui   $a0, %hi(D_80121178) # $a0, 0x8012
/* 06B510 8006A910 24841178 */  addiu $a0, %lo(D_80121178) # addiu $a0, $a0, 0x1178
/* 06B514 8006A914 3C088012 */  lui   $t0, %hi(D_80121178+4) # $t0, 0x8012
/* 06B518 8006A918 3C0A8012 */  lui   $t2, %hi(gNumberOfLevelHeaders) # $t2, 0x8012
/* 06B51C 8006A91C 254A1170 */  addiu $t2, %lo(gNumberOfLevelHeaders) # addiu $t2, $t2, 0x1170
/* 06B520 8006A920 2508117C */  addiu $t0, %lo(D_80121178+4) # addiu $t0, $t0, 0x117c
/* 06B524 8006A924 AC820000 */  sw    $v0, ($a0)
/* 06B528 8006A928 19E0000B */  blez  $t7, .L8006A958
/* 06B52C 8006A92C 240BFFFF */   li    $t3, -1
.L8006A930:
/* 06B530 8006A930 8C8D0000 */  lw    $t5, ($a0)
/* 06B534 8006A934 00000000 */  nop   
/* 06B538 8006A938 01B1C821 */  addu  $t9, $t5, $s1
/* 06B53C 8006A93C A32B0000 */  sb    $t3, ($t9)
/* 06B540 8006A940 8D2E0000 */  lw    $t6, ($t1)
/* 06B544 8006A944 26310001 */  addiu $s1, $s1, 1
/* 06B548 8006A948 022E082A */  slt   $at, $s1, $t6
/* 06B54C 8006A94C 1420FFF8 */  bnez  $at, .L8006A930
/* 06B550 8006A950 00000000 */   nop   
/* 06B554 8006A954 00008825 */  move  $s1, $zero
.L8006A958:
/* 06B558 8006A958 8D460000 */  lw    $a2, ($t2)
/* 06B55C 8006A95C 00000000 */  nop   
/* 06B560 8006A960 18C00015 */  blez  $a2, .L8006A9B8
/* 06B564 8006A964 00001825 */   move  $v1, $zero
/* 06B568 8006A968 24050005 */  li    $a1, 5
.L8006A96C:
/* 06B56C 8006A96C 8D0C0000 */  lw    $t4, ($t0)
/* 06B570 8006A970 00000000 */  nop   
/* 06B574 8006A974 01831021 */  addu  $v0, $t4, $v1
/* 06B578 8006A978 80580001 */  lb    $t8, 1($v0)
/* 06B57C 8006A97C 00000000 */  nop   
/* 06B580 8006A980 14B80008 */  bne   $a1, $t8, .L8006A9A4
/* 06B584 8006A984 00000000 */   nop   
/* 06B588 8006A988 8C8F0000 */  lw    $t7, ($a0)
/* 06B58C 8006A98C 804D0000 */  lb    $t5, ($v0)
/* 06B590 8006A990 3C068012 */  lui   $a2, %hi(gNumberOfLevelHeaders) # $a2, 0x8012
/* 06B594 8006A994 01EDC821 */  addu  $t9, $t7, $t5
/* 06B598 8006A998 A3310000 */  sb    $s1, ($t9)
/* 06B59C 8006A99C 8CC61170 */  lw    $a2, %lo(gNumberOfLevelHeaders)($a2)
/* 06B5A0 8006A9A0 00000000 */  nop   
.L8006A9A4:
/* 06B5A4 8006A9A4 26310001 */  addiu $s1, $s1, 1
/* 06B5A8 8006A9A8 0226082A */  slt   $at, $s1, $a2
/* 06B5AC 8006A9AC 1420FFEF */  bnez  $at, .L8006A96C
/* 06B5B0 8006A9B0 24630006 */   addiu $v1, $v1, 6
/* 06B5B4 8006A9B4 00008825 */  move  $s1, $zero
.L8006A9B8:
/* 06B5B8 8006A9B8 8E640000 */  lw    $a0, ($s3)
/* 06B5BC 8006A9BC 0C01C450 */  jal   free_from_memory_pool
/* 06B5C0 8006A9C0 00000000 */   nop   
/* 06B5C4 8006A9C4 8FA40044 */  lw    $a0, 0x44($sp)
/* 06B5C8 8006A9C8 0C01C450 */  jal   free_from_memory_pool
/* 06B5CC 8006A9CC 00000000 */   nop   
/* 06B5D0 8006A9D0 0C01DB16 */  jal   load_asset_section_from_rom
/* 06B5D4 8006A9D4 24040018 */   li    $a0, 24
/* 06B5D8 8006A9D8 AE620000 */  sw    $v0, ($s3)
/* 06B5DC 8006A9DC 8C460000 */  lw    $a2, ($v0)
/* 06B5E0 8006A9E0 240BFFFF */  li    $t3, -1
/* 06B5E4 8006A9E4 11660005 */  beq   $t3, $a2, .L8006A9FC
/* 06B5E8 8006A9E8 00401825 */   move  $v1, $v0
.L8006A9EC:
/* 06B5EC 8006A9EC 8C4E0004 */  lw    $t6, 4($v0)
/* 06B5F0 8006A9F0 26310001 */  addiu $s1, $s1, 1
/* 06B5F4 8006A9F4 156EFFFD */  bne   $t3, $t6, .L8006A9EC
/* 06B5F8 8006A9F8 24420004 */   addiu $v0, $v0, 4
.L8006A9FC:
/* 06B5FC 8006A9FC 2631FFFF */  addiu $s1, $s1, -1
/* 06B600 8006AA00 00112080 */  sll   $a0, $s1, 2
/* 06B604 8006AA04 00646021 */  addu  $t4, $v1, $a0
/* 06B608 8006AA08 8D980000 */  lw    $t8, ($t4)
/* 06B60C 8006AA0C 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 06B610 8006AA10 03063823 */  subu  $a3, $t8, $a2
/* 06B614 8006AA14 AFA70050 */  sw    $a3, 0x50($sp)
/* 06B618 8006AA18 0C01C327 */  jal   allocate_from_main_pool_safe
/* 06B61C 8006AA1C 34A500FF */   ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 06B620 8006AA20 3C038012 */  lui   $v1, %hi(gLevelNames) # $v1, 0x8012
/* 06B624 8006AA24 2463116C */  addiu $v1, %lo(gLevelNames) # addiu $v1, $v1, 0x116c
/* 06B628 8006AA28 8FA40050 */  lw    $a0, 0x50($sp)
/* 06B62C 8006AA2C 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 06B630 8006AA30 AC620000 */  sw    $v0, ($v1)
/* 06B634 8006AA34 0C01C327 */  jal   allocate_from_main_pool_safe
/* 06B638 8006AA38 34A500FF */   ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 06B63C 8006AA3C 3C10800E */  lui   $s0, %hi(D_800DD310) # $s0, 0x800e
/* 06B640 8006AA40 2610D310 */  addiu $s0, %lo(D_800DD310) # addiu $s0, $s0, -0x2cf0
/* 06B644 8006AA44 8FA70050 */  lw    $a3, 0x50($sp)
/* 06B648 8006AA48 AE020000 */  sw    $v0, ($s0)
/* 06B64C 8006AA4C 24040019 */  li    $a0, 25
/* 06B650 8006AA50 00402825 */  move  $a1, $v0
/* 06B654 8006AA54 0C01DB9A */  jal   load_asset_to_address
/* 06B658 8006AA58 00003025 */   move  $a2, $zero
/* 06B65C 8006AA5C 3C038012 */  lui   $v1, %hi(gLevelNames) # $v1, 0x8012
/* 06B660 8006AA60 2463116C */  addiu $v1, %lo(gLevelNames) # addiu $v1, $v1, 0x116c
/* 06B664 8006AA64 1A200035 */  blez  $s1, .L8006AB3C
/* 06B668 8006AA68 00003825 */   move  $a3, $zero
/* 06B66C 8006AA6C 32250003 */  andi  $a1, $s1, 3
/* 06B670 8006AA70 10A0000E */  beqz  $a1, .L8006AAAC
/* 06B674 8006AA74 00A02025 */   move  $a0, $a1
/* 06B678 8006AA78 00001080 */  sll   $v0, $zero, 2
.L8006AA7C:
/* 06B67C 8006AA7C 8E6F0000 */  lw    $t7, ($s3)
/* 06B680 8006AA80 8E0E0000 */  lw    $t6, ($s0)
/* 06B684 8006AA84 01E26821 */  addu  $t5, $t7, $v0
/* 06B688 8006AA88 8DB90000 */  lw    $t9, ($t5)
/* 06B68C 8006AA8C 8C780000 */  lw    $t8, ($v1)
/* 06B690 8006AA90 24E70001 */  addiu $a3, $a3, 1
/* 06B694 8006AA94 032E6021 */  addu  $t4, $t9, $t6
/* 06B698 8006AA98 03027821 */  addu  $t7, $t8, $v0
/* 06B69C 8006AA9C ADEC0000 */  sw    $t4, ($t7)
/* 06B6A0 8006AAA0 1487FFF6 */  bne   $a0, $a3, .L8006AA7C
/* 06B6A4 8006AAA4 24420004 */   addiu $v0, $v0, 4
/* 06B6A8 8006AAA8 10F10024 */  beq   $a3, $s1, .L8006AB3C
.L8006AAAC:
/* 06B6AC 8006AAAC 00071080 */   sll   $v0, $a3, 2
/* 06B6B0 8006AAB0 00112080 */  sll   $a0, $s1, 2
.L8006AAB4:
/* 06B6B4 8006AAB4 8E6D0000 */  lw    $t5, ($s3)
/* 06B6B8 8006AAB8 8E180000 */  lw    $t8, ($s0)
/* 06B6BC 8006AABC 01A2C821 */  addu  $t9, $t5, $v0
/* 06B6C0 8006AAC0 8F2E0000 */  lw    $t6, ($t9)
/* 06B6C4 8006AAC4 8C6F0000 */  lw    $t7, ($v1)
/* 06B6C8 8006AAC8 01D86021 */  addu  $t4, $t6, $t8
/* 06B6CC 8006AACC 01E26821 */  addu  $t5, $t7, $v0
/* 06B6D0 8006AAD0 ADAC0000 */  sw    $t4, ($t5)
/* 06B6D4 8006AAD4 8E790000 */  lw    $t9, ($s3)
/* 06B6D8 8006AAD8 8C6D0000 */  lw    $t5, ($v1)
/* 06B6DC 8006AADC 03227021 */  addu  $t6, $t9, $v0
/* 06B6E0 8006AAE0 8DD80004 */  lw    $t8, 4($t6)
/* 06B6E4 8006AAE4 8E0F0000 */  lw    $t7, ($s0)
/* 06B6E8 8006AAE8 01A2C821 */  addu  $t9, $t5, $v0
/* 06B6EC 8006AAEC 030F6021 */  addu  $t4, $t8, $t7
/* 06B6F0 8006AAF0 AF2C0004 */  sw    $t4, 4($t9)
/* 06B6F4 8006AAF4 8E6E0000 */  lw    $t6, ($s3)
/* 06B6F8 8006AAF8 8C790000 */  lw    $t9, ($v1)
/* 06B6FC 8006AAFC 01C2C021 */  addu  $t8, $t6, $v0
/* 06B700 8006AB00 8F0F0008 */  lw    $t7, 8($t8)
/* 06B704 8006AB04 8E0D0000 */  lw    $t5, ($s0)
/* 06B708 8006AB08 03227021 */  addu  $t6, $t9, $v0
/* 06B70C 8006AB0C 01ED6021 */  addu  $t4, $t7, $t5
/* 06B710 8006AB10 ADCC0008 */  sw    $t4, 8($t6)
/* 06B714 8006AB14 8E780000 */  lw    $t8, ($s3)
/* 06B718 8006AB18 8C6E0000 */  lw    $t6, ($v1)
/* 06B71C 8006AB1C 03027821 */  addu  $t7, $t8, $v0
/* 06B720 8006AB20 8DED000C */  lw    $t5, 0xc($t7)
/* 06B724 8006AB24 8E190000 */  lw    $t9, ($s0)
/* 06B728 8006AB28 01C2C021 */  addu  $t8, $t6, $v0
/* 06B72C 8006AB2C 24420010 */  addiu $v0, $v0, 0x10
/* 06B730 8006AB30 01B96021 */  addu  $t4, $t5, $t9
/* 06B734 8006AB34 1444FFDF */  bne   $v0, $a0, .L8006AAB4
/* 06B738 8006AB38 AF0C000C */   sw    $t4, 0xc($t8)
.L8006AB3C:
/* 06B73C 8006AB3C 8E640000 */  lw    $a0, ($s3)
/* 06B740 8006AB40 0C01C450 */  jal   free_from_memory_pool
/* 06B744 8006AB44 00000000 */   nop   
/* 06B748 8006AB48 3C04800E */  lui   $a0, %hi(gFunc80068158Length) # $a0, 0x800e
/* 06B74C 8006AB4C 8C84D324 */  lw    $a0, %lo(gFunc80068158Length)($a0)
/* 06B750 8006AB50 00001825 */  move  $v1, $zero
/* 06B754 8006AB54 18800009 */  blez  $a0, .L8006AB7C
/* 06B758 8006AB58 00001025 */   move  $v0, $zero
/* 06B75C 8006AB5C 3C058007 */  lui   $a1, %hi(func_80068158) # $a1, 0x8007
/* 06B760 8006AB60 24A58158 */  addiu $a1, %lo(func_80068158) # addiu $a1, $a1, -0x7ea8
.L8006AB64:
/* 06B764 8006AB64 00A27821 */  addu  $t7, $a1, $v0
/* 06B768 8006AB68 91ED0000 */  lbu   $t5, ($t7)
/* 06B76C 8006AB6C 24420001 */  addiu $v0, $v0, 1
/* 06B770 8006AB70 0044082A */  slt   $at, $v0, $a0
/* 06B774 8006AB74 1420FFFB */  bnez  $at, .L8006AB64
/* 06B778 8006AB78 006D1821 */   addu  $v1, $v1, $t5
.L8006AB7C:
/* 06B77C 8006AB7C 3C19800E */  lui   $t9, %hi(gFunc80068158Checksum) # $t9, 0x800e
/* 06B780 8006AB80 8F39D320 */  lw    $t9, %lo(gFunc80068158Checksum)($t9)
/* 06B784 8006AB84 00000000 */  nop   
/* 06B788 8006AB88 10790004 */  beq   $v1, $t9, .L8006AB9C
/* 06B78C 8006AB8C 8FBF0024 */   lw    $ra, 0x24($sp)
/* 06B790 8006AB90 0C01A9A8 */  jal   disable_button_mask
/* 06B794 8006AB94 00000000 */   nop   
/* 06B798 8006AB98 8FBF0024 */  lw    $ra, 0x24($sp)
.L8006AB9C:
/* 06B79C 8006AB9C 8FB00014 */  lw    $s0, 0x14($sp)
/* 06B7A0 8006ABA0 8FB10018 */  lw    $s1, 0x18($sp)
/* 06B7A4 8006ABA4 8FB2001C */  lw    $s2, 0x1c($sp)
/* 06B7A8 8006ABA8 8FB30020 */  lw    $s3, 0x20($sp)
/* 06B7AC 8006ABAC 03E00008 */  jr    $ra
/* 06B7B0 8006ABB0 27BD0058 */   addiu $sp, $sp, 0x58
