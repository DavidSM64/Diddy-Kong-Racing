.late_rodata
glabel D_800E6940
.double 0.45
glabel D_800E6948
.float -0.02
glabel D_800E694C
.float 1000000.0
glabel D_800E6950
.double 160000.0
glabel D_800E6958
.float 0.8
.word 0 # Padding
glabel D_800E6960
.double 160000.0
glabel jpt_800E6968
.word L8005AF80, L8005AFD8, L8005B004, L8005B030, L8005AFAC, L8005B05C, L8005B094, L8005B0CC, L8005B0CC, L8005B1B0, L8005B030, L8005B10C, L8005B144, L8005B17C
glabel D_800E69A0
.double 0.9
glabel D_800E69A8
.float 0.02
glabel D_800E69AC
.float -0.02
glabel D_800E69B0
.float 265.0
.word 0 # Padding
glabel D_800E69B8
.double 1500.0

.text
glabel func_8005A6F0
/* 05B2F0 8005A6F0 27BDFF60 */  addiu $sp, $sp, -0xa0
/* 05B2F4 8005A6F4 AFBF002C */  sw    $ra, 0x2c($sp)
/* 05B2F8 8005A6F8 AFB00028 */  sw    $s0, 0x28($sp)
/* 05B2FC 8005A6FC 240EFFFF */  li    $t6, -1
/* 05B300 8005A700 3C018012 */  lui   $at, %hi(gCurrentPlayerIndex) # $at, 0x8012
/* 05B304 8005A704 00A08025 */  move  $s0, $a1
/* 05B308 8005A708 AFA400A0 */  sw    $a0, 0xa0($sp)
/* 05B30C 8005A70C AFA600A8 */  sw    $a2, 0xa8($sp)
/* 05B310 8005A710 AFA700AC */  sw    $a3, 0xac($sp)
/* 05B314 8005A714 0C01B683 */  jal   get_render_context
/* 05B318 8005A718 AC2ED55C */   sw    $t6, %lo(gCurrentPlayerIndex)($at)
/* 05B31C 8005A71C 0C01AF6C */  jal   get_current_level_header
/* 05B320 8005A720 AFA20094 */   sw    $v0, 0x94($sp)
/* 05B324 8005A724 AFA20070 */  sw    $v0, 0x70($sp)
/* 05B328 8005A728 820301F6 */  lb    $v1, 0x1f6($s0)
/* 05B32C 8005A72C 3C198012 */  lui   $t9, %hi(gRaceStartTimer) # $t9, 0x8012
/* 05B330 8005A730 18600006 */  blez  $v1, .L8005A74C
/* 05B334 8005A734 00000000 */   nop   
/* 05B338 8005A738 8FAF00A8 */  lw    $t7, 0xa8($sp)
/* 05B33C 8005A73C 00000000 */  nop   
/* 05B340 8005A740 006FC023 */  subu  $t8, $v1, $t7
/* 05B344 8005A744 10000002 */  b     .L8005A750
/* 05B348 8005A748 A21801F6 */   sb    $t8, 0x1f6($s0)
.L8005A74C:
/* 05B34C 8005A74C A20001F6 */  sb    $zero, 0x1f6($s0)
.L8005A750:
/* 05B350 8005A750 8F39D540 */  lw    $t9, %lo(gRaceStartTimer)($t9)
/* 05B354 8005A754 00000000 */  nop   
/* 05B358 8005A758 13200005 */  beqz  $t9, .L8005A770
/* 05B35C 8005A75C 2404FFC4 */   li    $a0, -60
/* 05B360 8005A760 0C01BE53 */  jal   get_random_number_from_range
/* 05B364 8005A764 2405003C */   li    $a1, 60
/* 05B368 8005A768 244D0078 */  addiu $t5, $v0, 0x78
/* 05B36C 8005A76C A60D01C6 */  sh    $t5, 0x1c6($s0)
.L8005A770:
/* 05B370 8005A770 8602018C */  lh    $v0, 0x18c($s0)
/* 05B374 8005A774 00000000 */  nop   
/* 05B378 8005A778 18400006 */  blez  $v0, .L8005A794
/* 05B37C 8005A77C 00000000 */   nop   
/* 05B380 8005A780 8FAE00A8 */  lw    $t6, 0xa8($sp)
/* 05B384 8005A784 00000000 */  nop   
/* 05B388 8005A788 004E7823 */  subu  $t7, $v0, $t6
/* 05B38C 8005A78C 10000002 */  b     .L8005A798
/* 05B390 8005A790 A60F018C */   sh    $t7, 0x18c($s0)
.L8005A794:
/* 05B394 8005A794 A600018C */  sh    $zero, 0x18c($s0)
.L8005A798:
/* 05B398 8005A798 0C0078A7 */  jal   get_misc_asset
/* 05B39C 8005A79C 24040009 */   li    $a0, 9
/* 05B3A0 8005A7A0 3C038012 */  lui   $v1, %hi(gCurrentRacerMiscAssetPtr) # $v1, 0x8012
/* 05B3A4 8005A7A4 2463D564 */  addiu $v1, %lo(gCurrentRacerMiscAssetPtr) # addiu $v1, $v1, -0x2a9c
/* 05B3A8 8005A7A8 AC620000 */  sw    $v0, ($v1)
/* 05B3AC 8005A7AC 82190003 */  lb    $t9, 3($s0)
/* 05B3B0 8005A7B0 3C01800E */  lui   $at, %hi(D_800E6940 + 4) # $at, 0x800e
/* 05B3B4 8005A7B4 00196880 */  sll   $t5, $t9, 2
/* 05B3B8 8005A7B8 004D7021 */  addu  $t6, $v0, $t5
/* 05B3BC 8005A7BC C5C40000 */  lwc1  $f4, ($t6)
/* 05B3C0 8005A7C0 C4296940 */  lwc1  $f9, %lo(D_800E6940)($at)
/* 05B3C4 8005A7C4 C4286944 */  lwc1  $f8, %lo(D_800E6940 + 4)($at)
/* 05B3C8 8005A7C8 460021A1 */  cvt.d.s $f6, $f4
/* 05B3CC 8005A7CC 46283282 */  mul.d $f10, $f6, $f8
/* 05B3D0 8005A7D0 3C0C8012 */  lui   $t4, %hi(gCurrentRacerWeightStat) # $t4, 0x8012
/* 05B3D4 8005A7D4 258CD56C */  addiu $t4, %lo(gCurrentRacerWeightStat) # addiu $t4, $t4, -0x2a94
/* 05B3D8 8005A7D8 462054A0 */  cvt.s.d $f18, $f10
/* 05B3DC 8005A7DC E5920000 */  swc1  $f18, ($t4)
/* 05B3E0 8005A7E0 860F0204 */  lh    $t7, 0x204($s0)
/* 05B3E4 8005A7E4 00000000 */  nop   
/* 05B3E8 8005A7E8 19E00004 */  blez  $t7, .L8005A7FC
/* 05B3EC 8005A7EC 3C01800E */   lui   $at, %hi(D_800E6948) # $at, 0x800e
/* 05B3F0 8005A7F0 C4246948 */  lwc1  $f4, %lo(D_800E6948)($at)
/* 05B3F4 8005A7F4 00000000 */  nop   
/* 05B3F8 8005A7F8 E5840000 */  swc1  $f4, ($t4)
.L8005A7FC:
/* 05B3FC 8005A7FC 0C0078A7 */  jal   get_misc_asset
/* 05B400 8005A800 2404000A */   li    $a0, 10
/* 05B404 8005A804 3C038012 */  lui   $v1, %hi(gCurrentRacerMiscAssetPtr) # $v1, 0x8012
/* 05B408 8005A808 2463D564 */  addiu $v1, %lo(gCurrentRacerMiscAssetPtr) # addiu $v1, $v1, -0x2a9c
/* 05B40C 8005A80C AC620000 */  sw    $v0, ($v1)
/* 05B410 8005A810 82180003 */  lb    $t8, 3($s0)
/* 05B414 8005A814 3C018012 */  lui   $at, %hi(gCurrentRacerHandlingStat) # $at, 0x8012
/* 05B418 8005A818 00186880 */  sll   $t5, $t8, 2
/* 05B41C 8005A81C 004D7021 */  addu  $t6, $v0, $t5
/* 05B420 8005A820 C5C60000 */  lwc1  $f6, ($t6)
/* 05B424 8005A824 2404000B */  li    $a0, 11
/* 05B428 8005A828 0C0078A7 */  jal   get_misc_asset
/* 05B42C 8005A82C E426D570 */   swc1  $f6, %lo(gCurrentRacerHandlingStat)($at)
/* 05B430 8005A830 3C058012 */  lui   $a1, %hi(gCurrentRacerMiscAssetPtr) # $a1, 0x8012
/* 05B434 8005A834 24A5D564 */  addiu $a1, %lo(gCurrentRacerMiscAssetPtr) # addiu $a1, $a1, -0x2a9c
/* 05B438 8005A838 ACA20000 */  sw    $v0, ($a1)
/* 05B43C 8005A83C 82180003 */  lb    $t8, 3($s0)
/* 05B440 8005A840 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 05B444 8005A844 0018C880 */  sll   $t9, $t8, 2
/* 05B448 8005A848 00596821 */  addu  $t5, $v0, $t9
/* 05B44C 8005A84C C5A80000 */  lwc1  $f8, ($t5)
/* 05B450 8005A850 3C018012 */  lui   $at, %hi(D_8011D574) # $at, 0x8012
/* 05B454 8005A854 E428D574 */  swc1  $f8, %lo(D_8011D574)($at)
/* 05B458 8005A858 C48A000C */  lwc1  $f10, 0xc($a0)
/* 05B45C 8005A85C 00000000 */  nop   
/* 05B460 8005A860 E7AA008C */  swc1  $f10, 0x8c($sp)
/* 05B464 8005A864 C4920010 */  lwc1  $f18, 0x10($a0)
/* 05B468 8005A868 00000000 */  nop   
/* 05B46C 8005A86C E7B20088 */  swc1  $f18, 0x88($sp)
/* 05B470 8005A870 C4840014 */  lwc1  $f4, 0x14($a0)
/* 05B474 8005A874 00000000 */  nop   
/* 05B478 8005A878 E7A40084 */  swc1  $f4, 0x84($sp)
/* 05B47C 8005A87C 860301B2 */  lh    $v1, 0x1b2($s0)
/* 05B480 8005A880 00000000 */  nop   
/* 05B484 8005A884 1860000A */  blez  $v1, .L8005A8B0
/* 05B488 8005A888 00000000 */   nop   
/* 05B48C 8005A88C 8FAE00A8 */  lw    $t6, 0xa8($sp)
/* 05B490 8005A890 00000000 */  nop   
/* 05B494 8005A894 006EC023 */  subu  $t8, $v1, $t6
/* 05B498 8005A898 A61801B2 */  sh    $t8, 0x1b2($s0)
/* 05B49C 8005A89C 860F01B2 */  lh    $t7, 0x1b2($s0)
/* 05B4A0 8005A8A0 00000000 */  nop   
/* 05B4A4 8005A8A4 05E10002 */  bgez  $t7, .L8005A8B0
/* 05B4A8 8005A8A8 00000000 */   nop   
/* 05B4AC 8005A8AC A60001B2 */  sh    $zero, 0x1b2($s0)
.L8005A8B0:
/* 05B4B0 8005A8B0 821901E7 */  lb    $t9, 0x1e7($s0)
/* 05B4B4 8005A8B4 00000000 */  nop   
/* 05B4B8 8005A8B8 272D0001 */  addiu $t5, $t9, 1
/* 05B4BC 8005A8BC 0C008D07 */  jal   func_8002341C
/* 05B4C0 8005A8C0 A20D01E7 */   sb    $t5, 0x1e7($s0)
/* 05B4C4 8005A8C4 1440001A */  bnez  $v0, .L8005A930
/* 05B4C8 8005A8C8 240E001E */   li    $t6, 30
/* 05B4CC 8005A8CC 0C008D5A */  jal   func_80023568
/* 05B4D0 8005A8D0 00000000 */   nop   
/* 05B4D4 8005A8D4 14400016 */  bnez  $v0, .L8005A930
/* 05B4D8 8005A8D8 240E001E */   li    $t6, 30
/* 05B4DC 8005A8DC 820E01D6 */  lb    $t6, 0x1d6($s0)
/* 05B4E0 8005A8E0 24010004 */  li    $at, 4
/* 05B4E4 8005A8E4 11C10011 */  beq   $t6, $at, .L8005A92C
/* 05B4E8 8005A8E8 3C0142F0 */   li    $at, 0x42F00000 # 120.000000
/* 05B4EC 8005A8EC 44813000 */  mtc1  $at, $f6
/* 05B4F0 8005A8F0 3C018012 */  lui   $at, %hi(D_8011D544) # $at, 0x8012
/* 05B4F4 8005A8F4 C428D544 */  lwc1  $f8, %lo(D_8011D544)($at)
/* 05B4F8 8005A8F8 3C188012 */  lui   $t8, %hi(gRaceStartTimer) # $t8, 0x8012
/* 05B4FC 8005A8FC 4608303C */  c.lt.s $f6, $f8
/* 05B500 8005A900 00000000 */  nop   
/* 05B504 8005A904 4501000A */  bc1t  .L8005A930
/* 05B508 8005A908 240E001E */   li    $t6, 30
/* 05B50C 8005A90C 8F18D540 */  lw    $t8, %lo(gRaceStartTimer)($t8)
/* 05B510 8005A910 8FAF0070 */  lw    $t7, 0x70($sp)
/* 05B514 8005A914 17000006 */  bnez  $t8, .L8005A930
/* 05B518 8005A918 240E001E */   li    $t6, 30
/* 05B51C 8005A91C 81F9004C */  lb    $t9, 0x4c($t7)
/* 05B520 8005A920 00000000 */  nop   
/* 05B524 8005A924 332D0040 */  andi  $t5, $t9, 0x40
/* 05B528 8005A928 11A00002 */  beqz  $t5, .L8005A934
.L8005A92C:
/* 05B52C 8005A92C 240E001E */   li    $t6, 30
.L8005A930:
/* 05B530 8005A930 A20E0201 */  sb    $t6, 0x201($s0)
.L8005A934:
/* 05B534 8005A934 82180201 */  lb    $t8, 0x201($s0)
/* 05B538 8005A938 3C01800E */  lui   $at, %hi(D_800E694C) # $at, 0x800e
/* 05B53C 8005A93C C422694C */  lwc1  $f2, %lo(D_800E694C)($at)
/* 05B540 8005A940 1700007C */  bnez  $t8, .L8005AB34
/* 05B544 8005A944 27A40090 */   addiu $a0, $sp, 0x90
/* 05B548 8005A948 0C006E9D */  jal   get_object_struct_array
/* 05B54C 8005A94C E7A20078 */   swc1  $f2, 0x78($sp)
/* 05B550 8005A950 8FAF0090 */  lw    $t7, 0x90($sp)
/* 05B554 8005A954 C7A20078 */  lwc1  $f2, 0x78($sp)
/* 05B558 8005A958 00004025 */  move  $t0, $zero
/* 05B55C 8005A95C 00003825 */  move  $a3, $zero
/* 05B560 8005A960 19E00055 */  blez  $t7, .L8005AAB8
/* 05B564 8005A964 00005025 */   move  $t2, $zero
/* 05B568 8005A968 31E30003 */  andi  $v1, $t7, 3
/* 05B56C 8005A96C 10600018 */  beqz  $v1, .L8005A9D0
/* 05B570 8005A970 00604825 */   move  $t1, $v1
/* 05B574 8005A974 0000C880 */  sll   $t9, $zero, 2
/* 05B578 8005A978 00593021 */  addu  $a2, $v0, $t9
/* 05B57C 8005A97C 240B0001 */  li    $t3, 1
.L8005A980:
/* 05B580 8005A980 8CC40000 */  lw    $a0, ($a2)
/* 05B584 8005A984 254A0001 */  addiu $t2, $t2, 1
/* 05B588 8005A988 8C850064 */  lw    $a1, 0x64($a0)
/* 05B58C 8005A98C 00000000 */  nop   
/* 05B590 8005A990 84AD0000 */  lh    $t5, ($a1)
/* 05B594 8005A994 00000000 */  nop   
/* 05B598 8005A998 15A00002 */  bnez  $t5, .L8005A9A4
/* 05B59C 8005A99C 00000000 */   nop   
/* 05B5A0 8005A9A0 00803825 */  move  $a3, $a0
.L8005A9A4:
/* 05B5A4 8005A9A4 84AE0000 */  lh    $t6, ($a1)
/* 05B5A8 8005A9A8 00000000 */  nop   
/* 05B5AC 8005A9AC 156E0002 */  bne   $t3, $t6, .L8005A9B8
/* 05B5B0 8005A9B0 00000000 */   nop   
/* 05B5B4 8005A9B4 00804025 */  move  $t0, $a0
.L8005A9B8:
/* 05B5B8 8005A9B8 152AFFF1 */  bne   $t1, $t2, .L8005A980
/* 05B5BC 8005A9BC 24C60004 */   addiu $a2, $a2, 4
/* 05B5C0 8005A9C0 8FB80090 */  lw    $t8, 0x90($sp)
/* 05B5C4 8005A9C4 00000000 */  nop   
/* 05B5C8 8005A9C8 1158003B */  beq   $t2, $t8, .L8005AAB8
/* 05B5CC 8005A9CC 00000000 */   nop   
.L8005A9D0:
/* 05B5D0 8005A9D0 8FAF0090 */  lw    $t7, 0x90($sp)
/* 05B5D4 8005A9D4 000A6880 */  sll   $t5, $t2, 2
/* 05B5D8 8005A9D8 000FC880 */  sll   $t9, $t7, 2
/* 05B5DC 8005A9DC 03224821 */  addu  $t1, $t9, $v0
/* 05B5E0 8005A9E0 004D3021 */  addu  $a2, $v0, $t5
/* 05B5E4 8005A9E4 240B0001 */  li    $t3, 1
.L8005A9E8:
/* 05B5E8 8005A9E8 8CC40000 */  lw    $a0, ($a2)
/* 05B5EC 8005A9EC 00000000 */  nop   
/* 05B5F0 8005A9F0 8C850064 */  lw    $a1, 0x64($a0)
/* 05B5F4 8005A9F4 00000000 */  nop   
/* 05B5F8 8005A9F8 84AE0000 */  lh    $t6, ($a1)
/* 05B5FC 8005A9FC 00000000 */  nop   
/* 05B600 8005AA00 15C00002 */  bnez  $t6, .L8005AA0C
/* 05B604 8005AA04 00000000 */   nop   
/* 05B608 8005AA08 00803825 */  move  $a3, $a0
.L8005AA0C:
/* 05B60C 8005AA0C 84B80000 */  lh    $t8, ($a1)
/* 05B610 8005AA10 00000000 */  nop   
/* 05B614 8005AA14 15780002 */  bne   $t3, $t8, .L8005AA20
/* 05B618 8005AA18 00000000 */   nop   
/* 05B61C 8005AA1C 00804025 */  move  $t0, $a0
.L8005AA20:
/* 05B620 8005AA20 8CC50004 */  lw    $a1, 4($a2)
/* 05B624 8005AA24 00000000 */  nop   
/* 05B628 8005AA28 8CA30064 */  lw    $v1, 0x64($a1)
/* 05B62C 8005AA2C 00000000 */  nop   
/* 05B630 8005AA30 84640000 */  lh    $a0, ($v1)
/* 05B634 8005AA34 00000000 */  nop   
/* 05B638 8005AA38 14800002 */  bnez  $a0, .L8005AA44
/* 05B63C 8005AA3C 00000000 */   nop   
/* 05B640 8005AA40 00A03825 */  move  $a3, $a1
.L8005AA44:
/* 05B644 8005AA44 15640002 */  bne   $t3, $a0, .L8005AA50
/* 05B648 8005AA48 00000000 */   nop   
/* 05B64C 8005AA4C 00A04025 */  move  $t0, $a1
.L8005AA50:
/* 05B650 8005AA50 8CC50008 */  lw    $a1, 8($a2)
/* 05B654 8005AA54 00000000 */  nop   
/* 05B658 8005AA58 8CA30064 */  lw    $v1, 0x64($a1)
/* 05B65C 8005AA5C 00000000 */  nop   
/* 05B660 8005AA60 84640000 */  lh    $a0, ($v1)
/* 05B664 8005AA64 00000000 */  nop   
/* 05B668 8005AA68 14800002 */  bnez  $a0, .L8005AA74
/* 05B66C 8005AA6C 00000000 */   nop   
/* 05B670 8005AA70 00A03825 */  move  $a3, $a1
.L8005AA74:
/* 05B674 8005AA74 15640002 */  bne   $t3, $a0, .L8005AA80
/* 05B678 8005AA78 00000000 */   nop   
/* 05B67C 8005AA7C 00A04025 */  move  $t0, $a1
.L8005AA80:
/* 05B680 8005AA80 8CC5000C */  lw    $a1, 0xc($a2)
/* 05B684 8005AA84 24C60010 */  addiu $a2, $a2, 0x10
/* 05B688 8005AA88 8CA30064 */  lw    $v1, 0x64($a1)
/* 05B68C 8005AA8C 00000000 */  nop   
/* 05B690 8005AA90 84640000 */  lh    $a0, ($v1)
/* 05B694 8005AA94 00000000 */  nop   
/* 05B698 8005AA98 14800002 */  bnez  $a0, .L8005AAA4
/* 05B69C 8005AA9C 00000000 */   nop   
/* 05B6A0 8005AAA0 00A03825 */  move  $a3, $a1
.L8005AAA4:
/* 05B6A4 8005AAA4 15640002 */  bne   $t3, $a0, .L8005AAB0
/* 05B6A8 8005AAA8 00000000 */   nop   
/* 05B6AC 8005AAAC 00A04025 */  move  $t0, $a1
.L8005AAB0:
/* 05B6B0 8005AAB0 14C9FFCD */  bne   $a2, $t1, .L8005A9E8
/* 05B6B4 8005AAB4 00000000 */   nop   
.L8005AAB8:
/* 05B6B8 8005AAB8 10E0000B */  beqz  $a3, .L8005AAE8
/* 05B6BC 8005AABC 3C01800E */   lui   $at, %hi(D_800E6950 + 4) # $at, 0x800e
/* 05B6C0 8005AAC0 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 05B6C4 8005AAC4 C4EA000C */  lwc1  $f10, 0xc($a3)
/* 05B6C8 8005AAC8 C492000C */  lwc1  $f18, 0xc($a0)
/* 05B6CC 8005AACC C4E40014 */  lwc1  $f4, 0x14($a3)
/* 05B6D0 8005AAD0 46125081 */  sub.s $f2, $f10, $f18
/* 05B6D4 8005AAD4 C4860014 */  lwc1  $f6, 0x14($a0)
/* 05B6D8 8005AAD8 46021202 */  mul.s $f8, $f2, $f2
/* 05B6DC 8005AADC 46062001 */  sub.s $f0, $f4, $f6
/* 05B6E0 8005AAE0 46000282 */  mul.s $f10, $f0, $f0
/* 05B6E4 8005AAE4 460A4080 */  add.s $f2, $f8, $f10
.L8005AAE8:
/* 05B6E8 8005AAE8 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 05B6EC 8005AAEC 11000011 */  beqz  $t0, .L8005AB34
/* 05B6F0 8005AAF0 00000000 */   nop   
/* 05B6F4 8005AAF4 C4256950 */  lwc1  $f5, %lo(D_800E6950)($at)
/* 05B6F8 8005AAF8 C4246954 */  lwc1  $f4, %lo(D_800E6950 + 4)($at)
/* 05B6FC 8005AAFC 460014A1 */  cvt.d.s $f18, $f2
/* 05B700 8005AB00 4632203E */  c.le.d $f4, $f18
/* 05B704 8005AB04 00000000 */  nop   
/* 05B708 8005AB08 4500000A */  bc1f  .L8005AB34
/* 05B70C 8005AB0C 00000000 */   nop   
/* 05B710 8005AB10 C506000C */  lwc1  $f6, 0xc($t0)
/* 05B714 8005AB14 C488000C */  lwc1  $f8, 0xc($a0)
/* 05B718 8005AB18 C50A0014 */  lwc1  $f10, 0x14($t0)
/* 05B71C 8005AB1C 46083081 */  sub.s $f2, $f6, $f8
/* 05B720 8005AB20 C4920014 */  lwc1  $f18, 0x14($a0)
/* 05B724 8005AB24 46021102 */  mul.s $f4, $f2, $f2
/* 05B728 8005AB28 46125001 */  sub.s $f0, $f10, $f18
/* 05B72C 8005AB2C 46000182 */  mul.s $f6, $f0, $f0
/* 05B730 8005AB30 46062080 */  add.s $f2, $f4, $f6
.L8005AB34:
/* 05B734 8005AB34 86020204 */  lh    $v0, 0x204($s0)
/* 05B738 8005AB38 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 05B73C 8005AB3C 1840000A */  blez  $v0, .L8005AB68
/* 05B740 8005AB40 00000000 */   nop   
/* 05B744 8005AB44 8FA600A8 */  lw    $a2, 0xa8($sp)
/* 05B748 8005AB48 3C01800E */  lui   $at, %hi(D_800E6958) # $at, 0x800e
/* 05B74C 8005AB4C 00467823 */  subu  $t7, $v0, $a2
/* 05B750 8005AB50 A60F0204 */  sh    $t7, 0x204($s0)
/* 05B754 8005AB54 C42A6958 */  lwc1  $f10, %lo(D_800E6958)($at)
/* 05B758 8005AB58 C608002C */  lwc1  $f8, 0x2c($s0)
/* 05B75C 8005AB5C 00000000 */  nop   
/* 05B760 8005AB60 460A4482 */  mul.s $f18, $f8, $f10
/* 05B764 8005AB64 E612002C */  swc1  $f18, 0x2c($s0)
.L8005AB68:
/* 05B768 8005AB68 86020206 */  lh    $v0, 0x206($s0)
/* 05B76C 8005AB6C 8FA600A8 */  lw    $a2, 0xa8($sp)
/* 05B770 8005AB70 18400003 */  blez  $v0, .L8005AB80
/* 05B774 8005AB74 0046C823 */   subu  $t9, $v0, $a2
/* 05B778 8005AB78 A602018A */  sh    $v0, 0x18a($s0)
/* 05B77C 8005AB7C A6190206 */  sh    $t9, 0x206($s0)
.L8005AB80:
/* 05B780 8005AB80 82020201 */  lb    $v0, 0x201($s0)
/* 05B784 8005AB84 00000000 */  nop   
/* 05B788 8005AB88 1440000B */  bnez  $v0, .L8005ABB8
/* 05B78C 8005AB8C 3C01800E */   lui   $at, %hi(D_800E6960 + 4) # $at, 0x800e
/* 05B790 8005AB90 C4276960 */  lwc1  $f7, %lo(D_800E6960)($at)
/* 05B794 8005AB94 C4266964 */  lwc1  $f6, %lo(D_800E6960 + 4)($at)
/* 05B798 8005AB98 46001121 */  cvt.d.s $f4, $f2
/* 05B79C 8005AB9C 4626203C */  c.lt.d $f4, $f6
/* 05B7A0 8005ABA0 240D001E */  li    $t5, 30
/* 05B7A4 8005ABA4 45000004 */  bc1f  .L8005ABB8
/* 05B7A8 8005ABA8 00000000 */   nop   
/* 05B7AC 8005ABAC A20D0201 */  sb    $t5, 0x201($s0)
/* 05B7B0 8005ABB0 82020201 */  lb    $v0, 0x201($s0)
/* 05B7B4 8005ABB4 00000000 */  nop   
.L8005ABB8:
/* 05B7B8 8005ABB8 10400218 */  beqz  $v0, .L8005B41C
/* 05B7BC 8005ABBC 8FA700AC */   lw    $a3, 0xac($sp)
/* 05B7C0 8005ABC0 0C01105C */  jal   func_80044170
/* 05B7C4 8005ABC4 02002825 */   move  $a1, $s0
/* 05B7C8 8005ABC8 3C0E8012 */  lui   $t6, %hi(gCurrentRacerInput) # $t6, 0x8012
/* 05B7CC 8005ABCC 8DCED528 */  lw    $t6, %lo(gCurrentRacerInput)($t6)
/* 05B7D0 8005ABD0 3C0C8012 */  lui   $t4, %hi(gCurrentRacerWeightStat) # $t4, 0x8012
/* 05B7D4 8005ABD4 31D88000 */  andi  $t8, $t6, 0x8000
/* 05B7D8 8005ABD8 258CD56C */  addiu $t4, %lo(gCurrentRacerWeightStat) # addiu $t4, $t4, -0x2a94
/* 05B7DC 8005ABDC 17000003 */  bnez  $t8, .L8005ABEC
/* 05B7E0 8005ABE0 240B0001 */   li    $t3, 1
/* 05B7E4 8005ABE4 240F0001 */  li    $t7, 1
/* 05B7E8 8005ABE8 A20F020C */  sb    $t7, 0x20c($s0)
.L8005ABEC:
/* 05B7EC 8005ABEC 920201FE */  lbu   $v0, 0x1fe($s0)
/* 05B7F0 8005ABF0 24010003 */  li    $at, 3
/* 05B7F4 8005ABF4 14410011 */  bne   $v0, $at, .L8005AC3C
/* 05B7F8 8005ABF8 00000000 */   nop   
/* 05B7FC 8005ABFC 921901FF */  lbu   $t9, 0x1ff($s0)
/* 05B800 8005AC00 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 05B804 8005AC04 44994000 */  mtc1  $t9, $f8
/* 05B808 8005AC08 07210004 */  bgez  $t9, .L8005AC1C
/* 05B80C 8005AC0C 468042A0 */   cvt.s.w $f10, $f8
/* 05B810 8005AC10 44819000 */  mtc1  $at, $f18
/* 05B814 8005AC14 00000000 */  nop   
/* 05B818 8005AC18 46125280 */  add.s $f10, $f10, $f18
.L8005AC1C:
/* 05B81C 8005AC1C 3C014380 */  li    $at, 0x43800000 # 256.000000
/* 05B820 8005AC20 44812000 */  mtc1  $at, $f4
/* 05B824 8005AC24 C5880000 */  lwc1  $f8, ($t4)
/* 05B828 8005AC28 46045183 */  div.s $f6, $f10, $f4
/* 05B82C 8005AC2C 46064482 */  mul.s $f18, $f8, $f6
/* 05B830 8005AC30 E5920000 */  swc1  $f18, ($t4)
/* 05B834 8005AC34 920201FE */  lbu   $v0, 0x1fe($s0)
/* 05B838 8005AC38 00000000 */  nop   
.L8005AC3C:
/* 05B83C 8005AC3C 1562001E */  bne   $t3, $v0, .L8005ACB8
/* 05B840 8005AC40 24010002 */   li    $at, 2
/* 05B844 8005AC44 920D01FF */  lbu   $t5, 0x1ff($s0)
/* 05B848 8005AC48 C5800000 */  lwc1  $f0, ($t4)
/* 05B84C 8005AC4C 448D5000 */  mtc1  $t5, $f10
/* 05B850 8005AC50 05A10005 */  bgez  $t5, .L8005AC68
/* 05B854 8005AC54 46805120 */   cvt.s.w $f4, $f10
/* 05B858 8005AC58 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 05B85C 8005AC5C 44814000 */  mtc1  $at, $f8
/* 05B860 8005AC60 00000000 */  nop   
/* 05B864 8005AC64 46082100 */  add.s $f4, $f4, $f8
.L8005AC68:
/* 05B868 8005AC68 46040182 */  mul.s $f6, $f0, $f4
/* 05B86C 8005AC6C 3C014300 */  li    $at, 0x43000000 # 128.000000
/* 05B870 8005AC70 44819000 */  mtc1  $at, $f18
/* 05B874 8005AC74 3C018012 */  lui   $at, %hi(gCurrentStickY) # $at, 0x8012
/* 05B878 8005AC78 46123283 */  div.s $f10, $f6, $f18
/* 05B87C 8005AC7C 2418003C */  li    $t8, 60
/* 05B880 8005AC80 460A0201 */  sub.s $f8, $f0, $f10
/* 05B884 8005AC84 E5880000 */  swc1  $f8, ($t4)
/* 05B888 8005AC88 860E0204 */  lh    $t6, 0x204($s0)
/* 05B88C 8005AC8C 00000000 */  nop   
/* 05B890 8005AC90 19C00005 */  blez  $t6, .L8005ACA8
/* 05B894 8005AC94 00000000 */   nop   
/* 05B898 8005AC98 C5840000 */  lwc1  $f4, ($t4)
/* 05B89C 8005AC9C 00000000 */  nop   
/* 05B8A0 8005ACA0 46002187 */  neg.s $f6, $f4
/* 05B8A4 8005ACA4 E5860000 */  swc1  $f6, ($t4)
.L8005ACA8:
/* 05B8A8 8005ACA8 AC38D538 */  sw    $t8, %lo(gCurrentStickY)($at)
/* 05B8AC 8005ACAC 920201FE */  lbu   $v0, 0x1fe($s0)
/* 05B8B0 8005ACB0 00000000 */  nop   
/* 05B8B4 8005ACB4 24010002 */  li    $at, 2
.L8005ACB8:
/* 05B8B8 8005ACB8 1441002F */  bne   $v0, $at, .L8005AD78
/* 05B8BC 8005ACBC 00000000 */   nop   
/* 05B8C0 8005ACC0 920F01FF */  lbu   $t7, 0x1ff($s0)
/* 05B8C4 8005ACC4 00000000 */  nop   
/* 05B8C8 8005ACC8 000FCE00 */  sll   $t9, $t7, 0x18
/* 05B8CC 8005ACCC 0C01C1F1 */  jal   cosine_s
/* 05B8D0 8005ACD0 00192403 */   sra   $a0, $t9, 0x10
/* 05B8D4 8005ACD4 3C013FB0 */  li    $at, 0x3FB00000 # 1.375000
/* 05B8D8 8005ACD8 44817800 */  mtc1  $at, $f15
/* 05B8DC 8005ACDC 3C014080 */  li    $at, 0x40800000 # 4.000000
/* 05B8E0 8005ACE0 44814000 */  mtc1  $at, $f8
/* 05B8E4 8005ACE4 C6020084 */  lwc1  $f2, 0x84($s0)
/* 05B8E8 8005ACE8 46080102 */  mul.s $f4, $f0, $f8
/* 05B8EC 8005ACEC C7B200AC */  lwc1  $f18, 0xac($sp)
/* 05B8F0 8005ACF0 44807000 */  mtc1  $zero, $f14
/* 05B8F4 8005ACF4 920E01FF */  lbu   $t6, 0x1ff($s0)
/* 05B8F8 8005ACF8 46022181 */  sub.s $f6, $f4, $f2
/* 05B8FC 8005ACFC 000EC600 */  sll   $t8, $t6, 0x18
/* 05B900 8005AD00 46009321 */  cvt.d.s $f12, $f18
/* 05B904 8005AD04 460034A1 */  cvt.d.s $f18, $f6
/* 05B908 8005AD08 462E9202 */  mul.d $f8, $f18, $f14
/* 05B90C 8005AD0C 460012A1 */  cvt.d.s $f10, $f2
/* 05B910 8005AD10 00182403 */  sra   $a0, $t8, 0x10
/* 05B914 8005AD14 462C4102 */  mul.d $f4, $f8, $f12
/* 05B918 8005AD18 46245180 */  add.d $f6, $f10, $f4
/* 05B91C 8005AD1C 462034A0 */  cvt.s.d $f18, $f6
/* 05B920 8005AD20 E6120084 */  swc1  $f18, 0x84($s0)
/* 05B924 8005AD24 E7AC0044 */  swc1  $f12, 0x44($sp)
/* 05B928 8005AD28 0C01C1FE */  jal   sine_s
/* 05B92C 8005AD2C E7AD0040 */   swc1  $f13, 0x40($sp)
/* 05B930 8005AD30 3C013FB0 */  li    $at, 0x3FB00000 # 1.375000
/* 05B934 8005AD34 44817800 */  mtc1  $at, $f15
/* 05B938 8005AD38 3C014080 */  li    $at, 0x40800000 # 4.000000
/* 05B93C 8005AD3C 44815000 */  mtc1  $at, $f10
/* 05B940 8005AD40 C6020088 */  lwc1  $f2, 0x88($s0)
/* 05B944 8005AD44 460A0102 */  mul.s $f4, $f0, $f10
/* 05B948 8005AD48 44807000 */  mtc1  $zero, $f14
/* 05B94C 8005AD4C C7AD0040 */  lwc1  $f13, 0x40($sp)
/* 05B950 8005AD50 C7AC0044 */  lwc1  $f12, 0x44($sp)
/* 05B954 8005AD54 46022181 */  sub.s $f6, $f4, $f2
/* 05B958 8005AD58 460034A1 */  cvt.d.s $f18, $f6
/* 05B95C 8005AD5C 462E9282 */  mul.d $f10, $f18, $f14
/* 05B960 8005AD60 46001221 */  cvt.d.s $f8, $f2
/* 05B964 8005AD64 462C5102 */  mul.d $f4, $f10, $f12
/* 05B968 8005AD68 46244180 */  add.d $f6, $f8, $f4
/* 05B96C 8005AD6C 462034A0 */  cvt.s.d $f18, $f6
/* 05B970 8005AD70 10000015 */  b     .L8005ADC8
/* 05B974 8005AD74 E6120088 */   swc1  $f18, 0x88($s0)
.L8005AD78:
/* 05B978 8005AD78 C60A0084 */  lwc1  $f10, 0x84($s0)
/* 05B97C 8005AD7C 3C013FB0 */  li    $at, 0x3FB00000 # 1.375000
/* 05B980 8005AD80 44817800 */  mtc1  $at, $f15
/* 05B984 8005AD84 44807000 */  mtc1  $zero, $f14
/* 05B988 8005AD88 46005021 */  cvt.d.s $f0, $f10
/* 05B98C 8005AD8C 462E0102 */  mul.d $f4, $f0, $f14
/* 05B990 8005AD90 C7A800AC */  lwc1  $f8, 0xac($sp)
/* 05B994 8005AD94 00000000 */  nop   
/* 05B998 8005AD98 46004321 */  cvt.d.s $f12, $f8
/* 05B99C 8005AD9C C6080088 */  lwc1  $f8, 0x88($s0)
/* 05B9A0 8005ADA0 462C2182 */  mul.d $f6, $f4, $f12
/* 05B9A4 8005ADA4 460040A1 */  cvt.d.s $f2, $f8
/* 05B9A8 8005ADA8 462E1102 */  mul.d $f4, $f2, $f14
/* 05B9AC 8005ADAC 46260481 */  sub.d $f18, $f0, $f6
/* 05B9B0 8005ADB0 462C2182 */  mul.d $f6, $f4, $f12
/* 05B9B4 8005ADB4 462092A0 */  cvt.s.d $f10, $f18
/* 05B9B8 8005ADB8 E60A0084 */  swc1  $f10, 0x84($s0)
/* 05B9BC 8005ADBC 46261481 */  sub.d $f18, $f2, $f6
/* 05B9C0 8005ADC0 462092A0 */  cvt.s.d $f10, $f18
/* 05B9C4 8005ADC4 E60A0088 */  swc1  $f10, 0x88($s0)
.L8005ADC8:
/* 05B9C8 8005ADC8 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 05B9CC 8005ADCC 44814000 */  mtc1  $at, $f8
/* 05B9D0 8005ADD0 3C018012 */  lui   $at, %hi(gCurrentRacerHandlingStat) # $at, 0x8012
/* 05B9D4 8005ADD4 24040021 */  li    $a0, 33
/* 05B9D8 8005ADD8 0C0078A7 */  jal   get_misc_asset
/* 05B9DC 8005ADDC E428D570 */   swc1  $f8, %lo(gCurrentRacerHandlingStat)($at)
/* 05B9E0 8005ADE0 8FB900A0 */  lw    $t9, 0xa0($sp)
/* 05B9E4 8005ADE4 3C018012 */  lui   $at, %hi(gCurrentRacerMiscAssetPtr) # $at, 0x8012
/* 05B9E8 8005ADE8 AC22D564 */  sw    $v0, %lo(gCurrentRacerMiscAssetPtr)($at)
/* 05B9EC 8005ADEC 8F2D0040 */  lw    $t5, 0x40($t9)
/* 05B9F0 8005ADF0 00000000 */  nop   
/* 05B9F4 8005ADF4 91A4005D */  lbu   $a0, 0x5d($t5)
/* 05B9F8 8005ADF8 0C0078A7 */  jal   get_misc_asset
/* 05B9FC 8005ADFC 00000000 */   nop   
/* 05BA00 8005AE00 3C018012 */  lui   $at, %hi(D_8011D568) # $at, 0x8012
/* 05BA04 8005AE04 8FAE00A0 */  lw    $t6, 0xa0($sp)
/* 05BA08 8005AE08 AC22D568 */  sw    $v0, %lo(D_8011D568)($at)
/* 05BA0C 8005AE0C C5C40020 */  lwc1  $f4, 0x20($t6)
/* 05BA10 8005AE10 3C014010 */  li    $at, 0x40100000 # 2.250000
/* 05BA14 8005AE14 44819800 */  mtc1  $at, $f19
/* 05BA18 8005AE18 44809000 */  mtc1  $zero, $f18
/* 05BA1C 8005AE1C 460021A1 */  cvt.d.s $f6, $f4
/* 05BA20 8005AE20 4632303C */  c.lt.d $f6, $f18
/* 05BA24 8005AE24 240B0001 */  li    $t3, 1
/* 05BA28 8005AE28 4500000F */  bc1f  .L8005AE68
/* 05BA2C 8005AE2C 00000000 */   nop   
/* 05BA30 8005AE30 821801E2 */  lb    $t8, 0x1e2($s0)
/* 05BA34 8005AE34 00000000 */  nop   
/* 05BA38 8005AE38 2B010003 */  slti  $at, $t8, 3
/* 05BA3C 8005AE3C 10200009 */  beqz  $at, .L8005AE64
/* 05BA40 8005AE40 00000000 */   nop   
/* 05BA44 8005AE44 C60800C0 */  lwc1  $f8, 0xc0($s0)
/* 05BA48 8005AE48 44805800 */  mtc1  $zero, $f11
/* 05BA4C 8005AE4C 44805000 */  mtc1  $zero, $f10
/* 05BA50 8005AE50 46004121 */  cvt.d.s $f4, $f8
/* 05BA54 8005AE54 46245032 */  c.eq.d $f10, $f4
/* 05BA58 8005AE58 00000000 */  nop   
/* 05BA5C 8005AE5C 45010002 */  bc1t  .L8005AE68
/* 05BA60 8005AE60 00000000 */   nop   
.L8005AE64:
/* 05BA64 8005AE64 A20001F1 */  sb    $zero, 0x1f1($s0)
.L8005AE68:
/* 05BA68 8005AE68 820F0175 */  lb    $t7, 0x175($s0)
/* 05BA6C 8005AE6C 00000000 */  nop   
/* 05BA70 8005AE70 11E00006 */  beqz  $t7, .L8005AE8C
/* 05BA74 8005AE74 00000000 */   nop   
/* 05BA78 8005AE78 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 05BA7C 8005AE7C 8FA600A8 */  lw    $a2, 0xa8($sp)
/* 05BA80 8005AE80 0C015B8B */  jal   func_80056E2C
/* 05BA84 8005AE84 02002825 */   move  $a1, $s0
/* 05BA88 8005AE88 240B0001 */  li    $t3, 1
.L8005AE8C:
/* 05BA8C 8005AE8C 821901D6 */  lb    $t9, 0x1d6($s0)
/* 05BA90 8005AE90 00000000 */  nop   
/* 05BA94 8005AE94 11790008 */  beq   $t3, $t9, .L8005AEB8
/* 05BA98 8005AE98 8FAD00A0 */   lw    $t5, 0xa0($sp)
/* 05BA9C 8005AE9C 44803000 */  mtc1  $zero, $f6
/* 05BAA0 8005AEA0 A20001E5 */  sb    $zero, 0x1e5($s0)
/* 05BAA4 8005AEA4 3C018012 */  lui   $at, %hi(D_8011D5AE) # $at, 0x8012
/* 05BAA8 8005AEA8 E60600C0 */  swc1  $f6, 0xc0($s0)
/* 05BAAC 8005AEAC 1000000A */  b     .L8005AED8
/* 05BAB0 8005AEB0 A020D5AE */   sb    $zero, %lo(D_8011D5AE)($at)
/* 05BAB4 8005AEB4 8FAD00A0 */  lw    $t5, 0xa0($sp)
.L8005AEB8:
/* 05BAB8 8005AEB8 3C078012 */  lui   $a3, %hi(D_8011D5B0) # $a3, 0x8012
/* 05BABC 8005AEBC 85A4002E */  lh    $a0, 0x2e($t5)
/* 05BAC0 8005AEC0 8DA5000C */  lw    $a1, 0xc($t5)
/* 05BAC4 8005AEC4 8DA60014 */  lw    $a2, 0x14($t5)
/* 05BAC8 8005AEC8 0C00AC3D */  jal   func_8002B0F4
/* 05BACC 8005AECC 24E7D5B0 */   addiu $a3, %lo(D_8011D5B0) # addiu $a3, $a3, -0x2a50
/* 05BAD0 8005AED0 3C018012 */  lui   $at, %hi(D_8011D5AE) # $at, 0x8012
/* 05BAD4 8005AED4 A022D5AE */  sb    $v0, %lo(D_8011D5AE)($at)
.L8005AED8:
/* 05BAD8 8005AED8 0C00AB32 */  jal   func_8002ACC8
/* 05BADC 8005AEDC 00002025 */   move  $a0, $zero
/* 05BAE0 8005AEE0 8E0E0148 */  lw    $t6, 0x148($s0)
/* 05BAE4 8005AEE4 240B0001 */  li    $t3, 1
/* 05BAE8 8005AEE8 15C00009 */  bnez  $t6, .L8005AF10
/* 05BAEC 8005AEEC 3C088012 */   lui   $t0, %hi(gRaceStartTimer) # $t0, 0x8012
/* 05BAF0 8005AEF0 2508D540 */  addiu $t0, %lo(gRaceStartTimer) # addiu $t0, $t0, -0x2ac0
/* 05BAF4 8005AEF4 8D180000 */  lw    $t8, ($t0)
/* 05BAF8 8005AEF8 00000000 */  nop   
/* 05BAFC 8005AEFC 17000004 */  bnez  $t8, .L8005AF10
/* 05BB00 8005AF00 00000000 */   nop   
/* 05BB04 8005AF04 860F0204 */  lh    $t7, 0x204($s0)
/* 05BB08 8005AF08 00000000 */  nop   
/* 05BB0C 8005AF0C 19E0000E */  blez  $t7, .L8005AF48
.L8005AF10:
/* 05BB10 8005AF10 3C018012 */   lui   $at, %hi(gCurrentStickX) # $at, 0x8012
/* 05BB14 8005AF14 AC20D534 */  sw    $zero, %lo(gCurrentStickX)($at)
/* 05BB18 8005AF18 3C018012 */  lui   $at, %hi(gCurrentStickY) # $at, 0x8012
/* 05BB1C 8005AF1C 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BB20 8005AF20 AC20D538 */  sw    $zero, %lo(gCurrentStickY)($at)
/* 05BB24 8005AF24 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BB28 8005AF28 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BB2C 8005AF2C AC600000 */  sw    $zero, ($v1)
/* 05BB30 8005AF30 3C018012 */  lui   $at, %hi(gCurrentButtonsReleased) # $at, 0x8012
/* 05BB34 8005AF34 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BB38 8005AF38 3C088012 */  lui   $t0, %hi(gRaceStartTimer) # $t0, 0x8012
/* 05BB3C 8005AF3C AC20D530 */  sw    $zero, %lo(gCurrentButtonsReleased)($at)
/* 05BB40 8005AF40 2508D540 */  addiu $t0, %lo(gRaceStartTimer) # addiu $t0, $t0, -0x2ac0
/* 05BB44 8005AF44 AC400000 */  sw    $zero, ($v0)
.L8005AF48:
/* 05BB48 8005AF48 921901D6 */  lbu   $t9, 0x1d6($s0)
/* 05BB4C 8005AF4C 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BB50 8005AF50 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BB54 8005AF54 2F21000E */  sltiu $at, $t9, 0xe
/* 05BB58 8005AF58 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BB5C 8005AF5C 10200094 */  beqz  $at, .L8005B1B0
/* 05BB60 8005AF60 2442D52C */   addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BB64 8005AF64 0019C880 */  sll   $t9, $t9, 2
/* 05BB68 8005AF68 3C01800E */  lui   $at, %hi(jpt_800E6968) # $at, 0x800e
/* 05BB6C 8005AF6C 00390821 */  addu  $at, $at, $t9
/* 05BB70 8005AF70 8C396968 */  lw    $t9, %lo(jpt_800E6968)($at)
/* 05BB74 8005AF74 00000000 */  nop   
/* 05BB78 8005AF78 03200008 */  jr    $t9
/* 05BB7C 8005AF7C 00000000 */   nop   
glabel L8005AF80
/* 05BB80 8005AF80 8FA400A8 */  lw    $a0, 0xa8($sp)
/* 05BB84 8005AF84 8FA500AC */  lw    $a1, 0xac($sp)
/* 05BB88 8005AF88 8FA600A0 */  lw    $a2, 0xa0($sp)
/* 05BB8C 8005AF8C 0C013DFD */  jal   func_8004F7F4
/* 05BB90 8005AF90 02003825 */   move  $a3, $s0
/* 05BB94 8005AF94 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BB98 8005AF98 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BB9C 8005AF9C 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BBA0 8005AFA0 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BBA4 8005AFA4 10000082 */  b     .L8005B1B0
/* 05BBA8 8005AFA8 240B0001 */   li    $t3, 1
glabel L8005AFAC
/* 05BBAC 8005AFAC 8FA400A8 */  lw    $a0, 0xa8($sp)
/* 05BBB0 8005AFB0 8FA500AC */  lw    $a1, 0xac($sp)
/* 05BBB4 8005AFB4 8FA600A0 */  lw    $a2, 0xa0($sp)
/* 05BBB8 8005AFB8 0C013308 */  jal   func_8004CC20
/* 05BBBC 8005AFBC 02003825 */   move  $a3, $s0
/* 05BBC0 8005AFC0 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BBC4 8005AFC4 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BBC8 8005AFC8 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BBCC 8005AFCC 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BBD0 8005AFD0 10000077 */  b     .L8005B1B0
/* 05BBD4 8005AFD4 240B0001 */   li    $t3, 1
glabel L8005AFD8
/* 05BBD8 8005AFD8 8FA400A8 */  lw    $a0, 0xa8($sp)
/* 05BBDC 8005AFDC 8FA500AC */  lw    $a1, 0xac($sp)
/* 05BBE0 8005AFE0 8FA600A0 */  lw    $a2, 0xa0($sp)
/* 05BBE4 8005AFE4 0C011949 */  jal   func_80046524
/* 05BBE8 8005AFE8 02003825 */   move  $a3, $s0
/* 05BBEC 8005AFEC 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BBF0 8005AFF0 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BBF4 8005AFF4 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BBF8 8005AFF8 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BBFC 8005AFFC 1000006C */  b     .L8005B1B0
/* 05BC00 8005B000 240B0001 */   li    $t3, 1
glabel L8005B004
/* 05BC04 8005B004 8FA400A8 */  lw    $a0, 0xa8($sp)
/* 05BC08 8005B008 8FA500AC */  lw    $a1, 0xac($sp)
/* 05BC0C 8005B00C 8FA600A0 */  lw    $a2, 0xa0($sp)
/* 05BC10 8005B010 0C0125E5 */  jal   func_80049794
/* 05BC14 8005B014 02003825 */   move  $a3, $s0
/* 05BC18 8005B018 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BC1C 8005B01C 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BC20 8005B020 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BC24 8005B024 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BC28 8005B028 10000061 */  b     .L8005B1B0
/* 05BC2C 8005B02C 240B0001 */   li    $t3, 1
glabel L8005B030
/* 05BC30 8005B030 8FA400A8 */  lw    $a0, 0xa8($sp)
/* 05BC34 8005B034 8FA500AC */  lw    $a1, 0xac($sp)
/* 05BC38 8005B038 8FA600A0 */  lw    $a2, 0xa0($sp)
/* 05BC3C 8005B03C 0C013657 */  jal   func_8004D95C
/* 05BC40 8005B040 02003825 */   move  $a3, $s0
/* 05BC44 8005B044 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BC48 8005B048 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BC4C 8005B04C 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BC50 8005B050 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BC54 8005B054 10000056 */  b     .L8005B1B0
/* 05BC58 8005B058 240B0001 */   li    $t3, 1
glabel L8005B05C
/* 05BC5C 8005B05C 8FA400A8 */  lw    $a0, 0xa8($sp)
/* 05BC60 8005B060 8FA500AC */  lw    $a1, 0xac($sp)
/* 05BC64 8005B064 8FA600A0 */  lw    $a2, 0xa0($sp)
/* 05BC68 8005B068 02003825 */  move  $a3, $s0
/* 05BC6C 8005B06C AFA30010 */  sw    $v1, 0x10($sp)
/* 05BC70 8005B070 AFA20014 */  sw    $v0, 0x14($sp)
/* 05BC74 8005B074 0C0170D9 */  jal   func_8005C364
/* 05BC78 8005B078 AFA80018 */   sw    $t0, 0x18($sp)
/* 05BC7C 8005B07C 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BC80 8005B080 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BC84 8005B084 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BC88 8005B088 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BC8C 8005B08C 10000048 */  b     .L8005B1B0
/* 05BC90 8005B090 240B0001 */   li    $t3, 1
glabel L8005B094
/* 05BC94 8005B094 8FA400A8 */  lw    $a0, 0xa8($sp)
/* 05BC98 8005B098 8FA500AC */  lw    $a1, 0xac($sp)
/* 05BC9C 8005B09C 8FA600A0 */  lw    $a2, 0xa0($sp)
/* 05BCA0 8005B0A0 02003825 */  move  $a3, $s0
/* 05BCA4 8005B0A4 AFA30010 */  sw    $v1, 0x10($sp)
/* 05BCA8 8005B0A8 AFA20014 */  sw    $v0, 0x14($sp)
/* 05BCAC 8005B0AC 0C017434 */  jal   func_8005D0D0
/* 05BCB0 8005B0B0 AFA80018 */   sw    $t0, 0x18($sp)
/* 05BCB4 8005B0B4 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BCB8 8005B0B8 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BCBC 8005B0BC 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BCC0 8005B0C0 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BCC4 8005B0C4 1000003A */  b     .L8005B1B0
/* 05BCC8 8005B0C8 240B0001 */   li    $t3, 1
glabel L8005B0CC
/* 05BCCC 8005B0CC 3C0D8012 */  lui   $t5, %hi(gCurrentStickX) # $t5, 0x8012
/* 05BCD0 8005B0D0 25ADD534 */  addiu $t5, %lo(gCurrentStickX) # addiu $t5, $t5, -0x2acc
/* 05BCD4 8005B0D4 8FA400A8 */  lw    $a0, 0xa8($sp)
/* 05BCD8 8005B0D8 8FA500AC */  lw    $a1, 0xac($sp)
/* 05BCDC 8005B0DC 8FA600A0 */  lw    $a2, 0xa0($sp)
/* 05BCE0 8005B0E0 AFAD0014 */  sw    $t5, 0x14($sp)
/* 05BCE4 8005B0E4 02003825 */  move  $a3, $s0
/* 05BCE8 8005B0E8 AFA30010 */  sw    $v1, 0x10($sp)
/* 05BCEC 8005B0EC 0C017608 */  jal   func_8005D820
/* 05BCF0 8005B0F0 AFA80018 */   sw    $t0, 0x18($sp)
/* 05BCF4 8005B0F4 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BCF8 8005B0F8 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BCFC 8005B0FC 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BD00 8005B100 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BD04 8005B104 1000002A */  b     .L8005B1B0
/* 05BD08 8005B108 240B0001 */   li    $t3, 1
glabel L8005B10C
/* 05BD0C 8005B10C 8FA400A8 */  lw    $a0, 0xa8($sp)
/* 05BD10 8005B110 8FA500AC */  lw    $a1, 0xac($sp)
/* 05BD14 8005B114 8FA600A0 */  lw    $a2, 0xa0($sp)
/* 05BD18 8005B118 02003825 */  move  $a3, $s0
/* 05BD1C 8005B11C AFA30010 */  sw    $v1, 0x10($sp)
/* 05BD20 8005B120 AFA20014 */  sw    $v0, 0x14($sp)
/* 05BD24 8005B124 0C017930 */  jal   func_8005E4C0
/* 05BD28 8005B128 AFA80018 */   sw    $t0, 0x18($sp)
/* 05BD2C 8005B12C 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BD30 8005B130 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BD34 8005B134 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BD38 8005B138 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BD3C 8005B13C 1000001C */  b     .L8005B1B0
/* 05BD40 8005B140 240B0001 */   li    $t3, 1
glabel L8005B144
/* 05BD44 8005B144 8FA400A8 */  lw    $a0, 0xa8($sp)
/* 05BD48 8005B148 8FA500AC */  lw    $a1, 0xac($sp)
/* 05BD4C 8005B14C 8FA600A0 */  lw    $a2, 0xa0($sp)
/* 05BD50 8005B150 02003825 */  move  $a3, $s0
/* 05BD54 8005B154 AFA30010 */  sw    $v1, 0x10($sp)
/* 05BD58 8005B158 AFA20014 */  sw    $v0, 0x14($sp)
/* 05BD5C 8005B15C 0C017AA4 */  jal   func_8005EA90
/* 05BD60 8005B160 AFA80018 */   sw    $t0, 0x18($sp)
/* 05BD64 8005B164 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BD68 8005B168 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BD6C 8005B16C 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BD70 8005B170 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BD74 8005B174 1000000E */  b     .L8005B1B0
/* 05BD78 8005B178 240B0001 */   li    $t3, 1
glabel L8005B17C
/* 05BD7C 8005B17C 8FA400A8 */  lw    $a0, 0xa8($sp)
/* 05BD80 8005B180 8FA500AC */  lw    $a1, 0xac($sp)
/* 05BD84 8005B184 8FA600A0 */  lw    $a2, 0xa0($sp)
/* 05BD88 8005B188 02003825 */  move  $a3, $s0
/* 05BD8C 8005B18C AFA30010 */  sw    $v1, 0x10($sp)
/* 05BD90 8005B190 AFA20014 */  sw    $v0, 0x14($sp)
/* 05BD94 8005B194 0C017CC4 */  jal   func_8005F310
/* 05BD98 8005B198 AFA80018 */   sw    $t0, 0x18($sp)
/* 05BD9C 8005B19C 3C038012 */  lui   $v1, %hi(gCurrentRacerInput) # $v1, 0x8012
/* 05BDA0 8005B1A0 3C028012 */  lui   $v0, %hi(gCurrentButtonsPressed) # $v0, 0x8012
/* 05BDA4 8005B1A4 2442D52C */  addiu $v0, %lo(gCurrentButtonsPressed) # addiu $v0, $v0, -0x2ad4
/* 05BDA8 8005B1A8 2463D528 */  addiu $v1, %lo(gCurrentRacerInput) # addiu $v1, $v1, -0x2ad8
/* 05BDAC 8005B1AC 240B0001 */  li    $t3, 1
.L8005B1B0:
glabel L8005B1B0
/* 05BDB0 8005B1B0 8FAE0094 */  lw    $t6, 0x94($sp)
/* 05BDB4 8005B1B4 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 05BDB8 8005B1B8 11CB0006 */  beq   $t6, $t3, .L8005B1D4
/* 05BDBC 8005B1BC 00000000 */   nop   
/* 05BDC0 8005B1C0 8C450000 */  lw    $a1, ($v0)
/* 05BDC4 8005B1C4 8C660000 */  lw    $a2, ($v1)
/* 05BDC8 8005B1C8 8FA700A8 */  lw    $a3, 0xa8($sp)
/* 05BDCC 8005B1CC 0C001434 */  jal   func_800050D0
/* 05BDD0 8005B1D0 00000000 */   nop   
.L8005B1D4:
/* 05BDD4 8005B1D4 C61200A8 */  lwc1  $f18, 0xa8($s0)
/* 05BDD8 8005B1D8 C7A80084 */  lwc1  $f8, 0x84($sp)
/* 05BDDC 8005B1DC E7B20080 */  swc1  $f18, 0x80($sp)
/* 05BDE0 8005B1E0 82180192 */  lb    $t8, 0x192($s0)
/* 05BDE4 8005B1E4 8FA500A0 */  lw    $a1, 0xa0($sp)
/* 05BDE8 8005B1E8 AFB80090 */  sw    $t8, 0x90($sp)
/* 05BDEC 8005B1EC 82040192 */  lb    $a0, 0x192($s0)
/* 05BDF0 8005B1F0 8FA6008C */  lw    $a2, 0x8c($sp)
/* 05BDF4 8005B1F4 8FA70088 */  lw    $a3, 0x88($sp)
/* 05BDF8 8005B1F8 260F00A8 */  addiu $t7, $s0, 0xa8
/* 05BDFC 8005B1FC 261901C8 */  addiu $t9, $s0, 0x1c8
/* 05BE00 8005B200 AFB90018 */  sw    $t9, 0x18($sp)
/* 05BE04 8005B204 AFAF0014 */  sw    $t7, 0x14($sp)
/* 05BE08 8005B208 0C006179 */  jal   func_800185E4
/* 05BE0C 8005B20C E7A80010 */   swc1  $f8, 0x10($sp)
/* 05BE10 8005B210 2401FF9C */  li    $at, -100
/* 05BE14 8005B214 14410006 */  bne   $v0, $at, .L8005B230
/* 05BE18 8005B218 00405025 */   move  $t2, $v0
/* 05BE1C 8005B21C 02002025 */  move  $a0, $s0
/* 05BE20 8005B220 0C01709C */  jal   func_8005C270
/* 05BE24 8005B224 AFA2009C */   sw    $v0, 0x9c($sp)
/* 05BE28 8005B228 8FAA009C */  lw    $t2, 0x9c($sp)
/* 05BE2C 8005B22C 00000000 */  nop   
.L8005B230:
/* 05BE30 8005B230 82040192 */  lb    $a0, 0x192($s0)
/* 05BE34 8005B234 920501C8 */  lbu   $a1, 0x1c8($s0)
/* 05BE38 8005B238 0C006E87 */  jal   func_8001BA1C
/* 05BE3C 8005B23C AFAA009C */   sw    $t2, 0x9c($sp)
/* 05BE40 8005B240 820D01CA */  lb    $t5, 0x1ca($s0)
/* 05BE44 8005B244 8FAA009C */  lw    $t2, 0x9c($sp)
/* 05BE48 8005B248 004D7021 */  addu  $t6, $v0, $t5
/* 05BE4C 8005B24C 81D80036 */  lb    $t8, 0x36($t6)
/* 05BE50 8005B250 24010005 */  li    $at, 5
/* 05BE54 8005B254 17010007 */  bne   $t8, $at, .L8005B274
/* 05BE58 8005B258 00000000 */   nop   
/* 05BE5C 8005B25C 821901E5 */  lb    $t9, 0x1e5($s0)
/* 05BE60 8005B260 240F001E */  li    $t7, 30
/* 05BE64 8005B264 13200003 */  beqz  $t9, .L8005B274
/* 05BE68 8005B268 A20F0201 */   sb    $t7, 0x201($s0)
/* 05BE6C 8005B26C 240D0001 */  li    $t5, 1
/* 05BE70 8005B270 A20D01C8 */  sb    $t5, 0x1c8($s0)
.L8005B274:
/* 05BE74 8005B274 820E01CA */  lb    $t6, 0x1ca($s0)
/* 05BE78 8005B278 24010006 */  li    $at, 6
/* 05BE7C 8005B27C 004EC021 */  addu  $t8, $v0, $t6
/* 05BE80 8005B280 83030036 */  lb    $v1, 0x36($t8)
/* 05BE84 8005B284 8FAF0070 */  lw    $t7, 0x70($sp)
/* 05BE88 8005B288 14610009 */  bne   $v1, $at, .L8005B2B0
/* 05BE8C 8005B28C 24010004 */   li    $at, 4
/* 05BE90 8005B290 81F9004B */  lb    $t9, 0x4b($t7)
/* 05BE94 8005B294 820E01CA */  lb    $t6, 0x1ca($s0)
/* 05BE98 8005B298 272D0001 */  addiu $t5, $t9, 1
/* 05BE9C 8005B29C A20D0193 */  sb    $t5, 0x193($s0)
/* 05BEA0 8005B2A0 004EC021 */  addu  $t8, $v0, $t6
/* 05BEA4 8005B2A4 83030036 */  lb    $v1, 0x36($t8)
/* 05BEA8 8005B2A8 00000000 */  nop   
/* 05BEAC 8005B2AC 24010004 */  li    $at, 4
.L8005B2B0:
/* 05BEB0 8005B2B0 14610010 */  bne   $v1, $at, .L8005B2F4
/* 05BEB4 8005B2B4 00000000 */   nop   
/* 05BEB8 8005B2B8 C60A002C */  lwc1  $f10, 0x2c($s0)
/* 05BEBC 8005B2BC 3C01C010 */  li    $at, 0xC0100000 # -2.250000
/* 05BEC0 8005B2C0 44812800 */  mtc1  $at, $f5
/* 05BEC4 8005B2C4 44802000 */  mtc1  $zero, $f4
/* 05BEC8 8005B2C8 46005021 */  cvt.d.s $f0, $f10
/* 05BECC 8005B2CC 4624003C */  c.lt.d $f0, $f4
/* 05BED0 8005B2D0 3C01800E */  lui   $at, %hi(D_800E69A0 + 4) # $at, 0x800e
/* 05BED4 8005B2D4 45000007 */  bc1f  .L8005B2F4
/* 05BED8 8005B2D8 00000000 */   nop   
/* 05BEDC 8005B2DC C42769A0 */  lwc1  $f7, %lo(D_800E69A0)($at)
/* 05BEE0 8005B2E0 C42669A4 */  lwc1  $f6, %lo(D_800E69A0 + 4)($at)
/* 05BEE4 8005B2E4 00000000 */  nop   
/* 05BEE8 8005B2E8 46260482 */  mul.d $f18, $f0, $f6
/* 05BEEC 8005B2EC 46209220 */  cvt.s.d $f8, $f18
/* 05BEF0 8005B2F0 E608002C */  swc1  $f8, 0x2c($s0)
.L8005B2F4:
/* 05BEF4 8005B2F4 1540002C */  bnez  $t2, .L8005B3A8
/* 05BEF8 8005B2F8 00000000 */   nop   
/* 05BEFC 8005B2FC 820F01CA */  lb    $t7, 0x1ca($s0)
/* 05BF00 8005B300 24010002 */  li    $at, 2
/* 05BF04 8005B304 004FC821 */  addu  $t9, $v0, $t7
/* 05BF08 8005B308 832D0036 */  lb    $t5, 0x36($t9)
/* 05BF0C 8005B30C 240E0001 */  li    $t6, 1
/* 05BF10 8005B310 15A10002 */  bne   $t5, $at, .L8005B31C
/* 05BF14 8005B314 00000000 */   nop   
/* 05BF18 8005B318 A20E01C8 */  sb    $t6, 0x1c8($s0)
.L8005B31C:
/* 05BF1C 8005B31C 0C006E99 */  jal   func_8001BA64
/* 05BF20 8005B320 00000000 */   nop   
/* 05BF24 8005B324 82180192 */  lb    $t8, 0x192($s0)
/* 05BF28 8005B328 00000000 */  nop   
/* 05BF2C 8005B32C 270F0001 */  addiu $t7, $t8, 1
/* 05BF30 8005B330 A20F0192 */  sb    $t7, 0x192($s0)
/* 05BF34 8005B334 82190192 */  lb    $t9, 0x192($s0)
/* 05BF38 8005B338 00000000 */  nop   
/* 05BF3C 8005B33C 0322082A */  slt   $at, $t9, $v0
/* 05BF40 8005B340 1420000C */  bnez  $at, .L8005B374
/* 05BF44 8005B344 8FB80070 */   lw    $t8, 0x70($sp)
/* 05BF48 8005B348 860D0190 */  lh    $t5, 0x190($s0)
/* 05BF4C 8005B34C A2000192 */  sb    $zero, 0x192($s0)
/* 05BF50 8005B350 19A00008 */  blez  $t5, .L8005B374
/* 05BF54 8005B354 8FB80070 */   lw    $t8, 0x70($sp)
/* 05BF58 8005B358 82030193 */  lb    $v1, 0x193($s0)
/* 05BF5C 8005B35C 00000000 */  nop   
/* 05BF60 8005B360 28610078 */  slti  $at, $v1, 0x78
/* 05BF64 8005B364 10200002 */  beqz  $at, .L8005B370
/* 05BF68 8005B368 246E0001 */   addiu $t6, $v1, 1
/* 05BF6C 8005B36C A20E0193 */  sb    $t6, 0x193($s0)
.L8005B370:
/* 05BF70 8005B370 8FB80070 */  lw    $t8, 0x70($sp)
.L8005B374:
/* 05BF74 8005B374 86030190 */  lh    $v1, 0x190($s0)
/* 05BF78 8005B378 830F004B */  lb    $t7, 0x4b($t8)
/* 05BF7C 8005B37C 24182710 */  li    $t8, 10000
/* 05BF80 8005B380 25F90003 */  addiu $t9, $t7, 3
/* 05BF84 8005B384 03220019 */  multu $t9, $v0
/* 05BF88 8005B388 246E0001 */  addiu $t6, $v1, 1
/* 05BF8C 8005B38C 00006812 */  mflo  $t5
/* 05BF90 8005B390 006D082A */  slt   $at, $v1, $t5
/* 05BF94 8005B394 10200002 */  beqz  $at, .L8005B3A0
/* 05BF98 8005B398 00000000 */   nop   
/* 05BF9C 8005B39C A60E0190 */  sh    $t6, 0x190($s0)
.L8005B3A0:
/* 05BFA0 8005B3A0 1000000E */  b     .L8005B3DC
/* 05BFA4 8005B3A4 A61801A8 */   sh    $t8, 0x1a8($s0)
.L8005B3A8:
/* 05BFA8 8005B3A8 860F0000 */  lh    $t7, ($s0)
/* 05BFAC 8005B3AC 2401FFFF */  li    $at, -1
/* 05BFB0 8005B3B0 15E10009 */  bne   $t7, $at, .L8005B3D8
/* 05BFB4 8005B3B4 00000000 */   nop   
/* 05BFB8 8005B3B8 C7A00080 */  lwc1  $f0, 0x80($sp)
/* 05BFBC 8005B3BC C60A00A8 */  lwc1  $f10, 0xa8($s0)
/* 05BFC0 8005B3C0 00000000 */  nop   
/* 05BFC4 8005B3C4 460A003C */  c.lt.s $f0, $f10
/* 05BFC8 8005B3C8 00000000 */  nop   
/* 05BFCC 8005B3CC 45000002 */  bc1f  .L8005B3D8
/* 05BFD0 8005B3D0 00000000 */   nop   
/* 05BFD4 8005B3D4 E60000A8 */  swc1  $f0, 0xa8($s0)
.L8005B3D8:
/* 05BFD8 8005B3D8 A60A01A8 */  sh    $t2, 0x1a8($s0)
.L8005B3DC:
/* 05BFDC 8005B3DC 8FB900A0 */  lw    $t9, 0xa0($sp)
/* 05BFE0 8005B3E0 00000000 */  nop   
/* 05BFE4 8005B3E4 C724000C */  lwc1  $f4, 0xc($t9)
/* 05BFE8 8005B3E8 00000000 */  nop   
/* 05BFEC 8005B3EC E6040068 */  swc1  $f4, 0x68($s0)
/* 05BFF0 8005B3F0 8FAD00A0 */  lw    $t5, 0xa0($sp)
/* 05BFF4 8005B3F4 00000000 */  nop   
/* 05BFF8 8005B3F8 C5A60010 */  lwc1  $f6, 0x10($t5)
/* 05BFFC 8005B3FC 00000000 */  nop   
/* 05C000 8005B400 E606006C */  swc1  $f6, 0x6c($s0)
/* 05C004 8005B404 8FAE00A0 */  lw    $t6, 0xa0($sp)
/* 05C008 8005B408 00000000 */  nop   
/* 05C00C 8005B40C C5D20014 */  lwc1  $f18, 0x14($t6)
/* 05C010 8005B410 1000000F */  b     .L8005B450
/* 05C014 8005B414 E6120070 */   swc1  $f18, 0x70($s0)
/* 05C018 8005B418 8FA700AC */  lw    $a3, 0xac($sp)
.L8005B41C:
/* 05C01C 8005B41C 0C016E06 */  jal   func_8005B818
/* 05C020 8005B420 02002825 */   move  $a1, $s0
/* 05C024 8005B424 8FB80094 */  lw    $t8, 0x94($sp)
/* 05C028 8005B428 240B0001 */  li    $t3, 1
/* 05C02C 8005B42C 130B0008 */  beq   $t8, $t3, .L8005B450
/* 05C030 8005B430 3C058012 */   lui   $a1, %hi(gCurrentButtonsPressed) # $a1, 0x8012
/* 05C034 8005B434 3C068012 */  lui   $a2, %hi(gCurrentRacerInput) # $a2, 0x8012
/* 05C038 8005B438 8CC6D528 */  lw    $a2, %lo(gCurrentRacerInput)($a2)
/* 05C03C 8005B43C 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 05C040 8005B440 8CA5D52C */  lw    $a1, %lo(gCurrentButtonsPressed)($a1)
/* 05C044 8005B444 8FA700A8 */  lw    $a3, 0xa8($sp)
/* 05C048 8005B448 0C001434 */  jal   func_800050D0
/* 05C04C 8005B44C 00000000 */   nop   
.L8005B450:
/* 05C050 8005B450 C7A800AC */  lwc1  $f8, 0xac($sp)
/* 05C054 8005B454 820F0175 */  lb    $t7, 0x175($s0)
/* 05C058 8005B458 46004321 */  cvt.d.s $f12, $f8
/* 05C05C 8005B45C 15E0000C */  bnez  $t7, .L8005B490
/* 05C060 8005B460 8FB900A8 */   lw    $t9, 0xa8($sp)
/* 05C064 8005B464 8E040178 */  lw    $a0, 0x178($s0)
/* 05C068 8005B468 00000000 */  nop   
/* 05C06C 8005B46C 10800008 */  beqz  $a0, .L8005B490
/* 05C070 8005B470 8FB900A8 */   lw    $t9, 0xa8($sp)
/* 05C074 8005B474 E7AD0040 */  swc1  $f13, 0x40($sp)
/* 05C078 8005B478 0C001223 */  jal   func_8000488C
/* 05C07C 8005B47C E7AC0044 */   swc1  $f12, 0x44($sp)
/* 05C080 8005B480 C7AD0040 */  lwc1  $f13, 0x40($sp)
/* 05C084 8005B484 C7AC0044 */  lwc1  $f12, 0x44($sp)
/* 05C088 8005B488 AE000178 */  sw    $zero, 0x178($s0)
/* 05C08C 8005B48C 8FB900A8 */  lw    $t9, 0xa8($sp)
.L8005B490:
/* 05C090 8005B490 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 05C094 8005B494 8FA5008C */  lw    $a1, 0x8c($sp)
/* 05C098 8005B498 8FA60088 */  lw    $a2, 0x88($sp)
/* 05C09C 8005B49C 8FA70084 */  lw    $a3, 0x84($sp)
/* 05C0A0 8005B4A0 E7AD0040 */  swc1  $f13, 0x40($sp)
/* 05C0A4 8005B4A4 E7AC0044 */  swc1  $f12, 0x44($sp)
/* 05C0A8 8005B4A8 0C006338 */  jal   func_80018CE0
/* 05C0AC 8005B4AC AFB90010 */   sw    $t9, 0x10($sp)
/* 05C0B0 8005B4B0 82060188 */  lb    $a2, 0x188($s0)
/* 05C0B4 8005B4B4 C7AD0040 */  lwc1  $f13, 0x40($sp)
/* 05C0B8 8005B4B8 C7AC0044 */  lwc1  $f12, 0x44($sp)
/* 05C0BC 8005B4BC 18C00009 */  blez  $a2, .L8005B4E4
/* 05C0C0 8005B4C0 00000000 */   nop   
/* 05C0C4 8005B4C4 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 05C0C8 8005B4C8 02002825 */  move  $a1, $s0
/* 05C0CC 8005B4CC E7AD0040 */  swc1  $f13, 0x40($sp)
/* 05C0D0 8005B4D0 0C015DB8 */  jal   func_800576E0
/* 05C0D4 8005B4D4 E7AC0044 */   swc1  $f12, 0x44($sp)
/* 05C0D8 8005B4D8 C7AD0040 */  lwc1  $f13, 0x40($sp)
/* 05C0DC 8005B4DC C7AC0044 */  lwc1  $f12, 0x44($sp)
/* 05C0E0 8005B4E0 00000000 */  nop   
.L8005B4E4:
/* 05C0E4 8005B4E4 8E0D0148 */  lw    $t5, 0x148($s0)
/* 05C0E8 8005B4E8 44803000 */  mtc1  $zero, $f6
/* 05C0EC 8005B4EC 11A00005 */  beqz  $t5, .L8005B504
/* 05C0F0 8005B4F0 3C02800E */   lui   $v0, %hi(D_800DCB54) # $v0, 0x800e
/* 05C0F4 8005B4F4 44808000 */  mtc1  $zero, $f16
/* 05C0F8 8005B4F8 AE000148 */  sw    $zero, 0x148($s0)
/* 05C0FC 8005B4FC E610002C */  swc1  $f16, 0x2c($s0)
/* 05C100 8005B500 E6100030 */  swc1  $f16, 0x30($s0)
.L8005B504:
/* 05C104 8005B504 C60E0090 */  lwc1  $f14, 0x90($s0)
/* 05C108 8005B508 C600008C */  lwc1  $f0, 0x8c($s0)
/* 05C10C 8005B50C 44808000 */  mtc1  $zero, $f16
/* 05C110 8005B510 460E003E */  c.le.s $f0, $f14
/* 05C114 8005B514 3C01800E */  lui   $at, %hi(D_800E69AC) # $at, 0x800e
/* 05C118 8005B518 45000005 */  bc1f  .L8005B530
/* 05C11C 8005B51C 46007281 */   sub.s $f10, $f14, $f0
/* 05C120 8005B520 3C01800E */  lui   $at, %hi(D_800E69A8) # $at, 0x800e
/* 05C124 8005B524 C42269A8 */  lwc1  $f2, %lo(D_800E69A8)($at)
/* 05C128 8005B528 10000004 */  b     .L8005B53C
/* 05C12C 8005B52C 3C013FC0 */   li    $at, 0x3FC00000 # 1.500000
.L8005B530:
/* 05C130 8005B530 C42269AC */  lwc1  $f2, %lo(D_800E69AC)($at)
/* 05C134 8005B534 00000000 */  nop   
/* 05C138 8005B538 3C013FC0 */  li    $at, 0x3FC00000 # 1.500000
.L8005B53C:
/* 05C13C 8005B53C 44813800 */  mtc1  $at, $f7
/* 05C140 8005B540 46005121 */  cvt.d.s $f4, $f10
/* 05C144 8005B544 46262482 */  mul.d $f18, $f4, $f6
/* 05C148 8005B548 46001221 */  cvt.d.s $f8, $f2
/* 05C14C 8005B54C 460001A1 */  cvt.d.s $f6, $f0
/* 05C150 8005B550 4610103C */  c.lt.s $f2, $f16
/* 05C154 8005B554 46289280 */  add.d $f10, $f18, $f8
/* 05C158 8005B558 462C5102 */  mul.d $f4, $f10, $f12
/* 05C15C 8005B55C 46243480 */  add.d $f18, $f6, $f4
/* 05C160 8005B560 46209220 */  cvt.s.d $f8, $f18
/* 05C164 8005B564 45000007 */  bc1f  .L8005B584
/* 05C168 8005B568 E608008C */   swc1  $f8, 0x8c($s0)
/* 05C16C 8005B56C C60A008C */  lwc1  $f10, 0x8c($s0)
/* 05C170 8005B570 00000000 */  nop   
/* 05C174 8005B574 460E503E */  c.le.s $f10, $f14
/* 05C178 8005B578 00000000 */  nop   
/* 05C17C 8005B57C 4501000B */  bc1t  .L8005B5AC
/* 05C180 8005B580 3C013F80 */   lui   $at, 0x3f80
.L8005B584:
/* 05C184 8005B584 4602803C */  c.lt.s $f16, $f2
/* 05C188 8005B588 00000000 */  nop   
/* 05C18C 8005B58C 4500000A */  bc1f  .L8005B5B8
/* 05C190 8005B590 00000000 */   nop   
/* 05C194 8005B594 C606008C */  lwc1  $f6, 0x8c($s0)
/* 05C198 8005B598 00000000 */  nop   
/* 05C19C 8005B59C 4606703E */  c.le.s $f14, $f6
/* 05C1A0 8005B5A0 00000000 */  nop   
/* 05C1A4 8005B5A4 45000004 */  bc1f  .L8005B5B8
/* 05C1A8 8005B5A8 3C013F80 */   li    $at, 0x3F800000 # 1.000000
.L8005B5AC:
/* 05C1AC 8005B5AC 44812000 */  mtc1  $at, $f4
/* 05C1B0 8005B5B0 E60E008C */  swc1  $f14, 0x8c($s0)
/* 05C1B4 8005B5B4 E6040090 */  swc1  $f4, 0x90($s0)
.L8005B5B8:
/* 05C1B8 8005B5B8 8603016A */  lh    $v1, 0x16a($s0)
/* 05C1BC 8005B5BC 860E016C */  lh    $t6, 0x16c($s0)
/* 05C1C0 8005B5C0 8FAF00A8 */  lw    $t7, 0xa8($sp)
/* 05C1C4 8005B5C4 01C3C023 */  subu  $t8, $t6, $v1
/* 05C1C8 8005B5C8 030F0019 */  multu $t8, $t7
/* 05C1CC 8005B5CC 00005012 */  mflo  $t2
/* 05C1D0 8005B5D0 000AC8C3 */  sra   $t9, $t2, 3
/* 05C1D4 8005B5D4 2B210801 */  slti  $at, $t9, 0x801
/* 05C1D8 8005B5D8 14200002 */  bnez  $at, .L8005B5E4
/* 05C1DC 8005B5DC 03205025 */   move  $t2, $t9
/* 05C1E0 8005B5E0 240A0800 */  li    $t2, 2048
.L8005B5E4:
/* 05C1E4 8005B5E4 2941F800 */  slti  $at, $t2, -0x800
/* 05C1E8 8005B5E8 10200002 */  beqz  $at, .L8005B5F4
/* 05C1EC 8005B5EC 00000000 */   nop   
/* 05C1F0 8005B5F0 240AF800 */  li    $t2, -2048
.L8005B5F4:
/* 05C1F4 8005B5F4 8442CB54 */  lh    $v0, %lo(D_800DCB54)($v0)
/* 05C1F8 8005B5F8 006A7021 */  addu  $t6, $v1, $t2
/* 05C1FC 8005B5FC 10400003 */  beqz  $v0, .L8005B60C
/* 05C200 8005B600 00626821 */   addu  $t5, $v1, $v0
/* 05C204 8005B604 10000002 */  b     .L8005B610
/* 05C208 8005B608 A60D016A */   sh    $t5, 0x16a($s0)
.L8005B60C:
/* 05C20C 8005B60C A60E016A */  sh    $t6, 0x16a($s0)
.L8005B610:
/* 05C210 8005B610 8602018E */  lh    $v0, 0x18e($s0)
/* 05C214 8005B614 00000000 */  nop   
/* 05C218 8005B618 18400031 */  blez  $v0, .L8005B6E0
/* 05C21C 8005B61C 2841003D */   slti  $at, $v0, 0x3d
/* 05C220 8005B620 1420001E */  bnez  $at, .L8005B69C
/* 05C224 8005B624 00000000 */   nop   
/* 05C228 8005B628 8E04017C */  lw    $a0, 0x17c($s0)
/* 05C22C 8005B62C 00000000 */  nop   
/* 05C230 8005B630 1080000B */  beqz  $a0, .L8005B660
/* 05C234 8005B634 00000000 */   nop   
/* 05C238 8005B638 8FA200A0 */  lw    $v0, 0xa0($sp)
/* 05C23C 8005B63C 00000000 */  nop   
/* 05C240 8005B640 8C45000C */  lw    $a1, 0xc($v0)
/* 05C244 8005B644 8C460010 */  lw    $a2, 0x10($v0)
/* 05C248 8005B648 8C470014 */  lw    $a3, 0x14($v0)
/* 05C24C 8005B64C 0C0025B6 */  jal   update_spatial_audio_position
/* 05C250 8005B650 00000000 */   nop   
/* 05C254 8005B654 8602018E */  lh    $v0, 0x18e($s0)
/* 05C258 8005B658 10000019 */  b     .L8005B6C0
/* 05C25C 8005B65C 8FAE00A8 */   lw    $t6, 0xa8($sp)
.L8005B660:
/* 05C260 8005B660 8E180118 */  lw    $t8, 0x118($s0)
/* 05C264 8005B664 8FAF00A0 */  lw    $t7, 0xa0($sp)
/* 05C268 8005B668 13000014 */  beqz  $t8, .L8005B6BC
/* 05C26C 8005B66C 2404009F */   li    $a0, 159
/* 05C270 8005B670 8DE5000C */  lw    $a1, 0xc($t7)
/* 05C274 8005B674 8DE60010 */  lw    $a2, 0x10($t7)
/* 05C278 8005B678 8DE70014 */  lw    $a3, 0x14($t7)
/* 05C27C 8005B67C 24190001 */  li    $t9, 1
/* 05C280 8005B680 260D017C */  addiu $t5, $s0, 0x17c
/* 05C284 8005B684 AFAD0014 */  sw    $t5, 0x14($sp)
/* 05C288 8005B688 0C002556 */  jal   func_80009558
/* 05C28C 8005B68C AFB90010 */   sw    $t9, 0x10($sp)
/* 05C290 8005B690 8602018E */  lh    $v0, 0x18e($s0)
/* 05C294 8005B694 1000000A */  b     .L8005B6C0
/* 05C298 8005B698 8FAE00A8 */   lw    $t6, 0xa8($sp)
.L8005B69C:
/* 05C29C 8005B69C 8E04017C */  lw    $a0, 0x17c($s0)
/* 05C2A0 8005B6A0 00000000 */  nop   
/* 05C2A4 8005B6A4 10800006 */  beqz  $a0, .L8005B6C0
/* 05C2A8 8005B6A8 8FAE00A8 */   lw    $t6, 0xa8($sp)
/* 05C2AC 8005B6AC 0C0025BE */  jal   func_800096F8
/* 05C2B0 8005B6B0 00000000 */   nop   
/* 05C2B4 8005B6B4 8602018E */  lh    $v0, 0x18e($s0)
/* 05C2B8 8005B6B8 AE00017C */  sw    $zero, 0x17c($s0)
.L8005B6BC:
/* 05C2BC 8005B6BC 8FAE00A8 */  lw    $t6, 0xa8($sp)
.L8005B6C0:
/* 05C2C0 8005B6C0 00000000 */  nop   
/* 05C2C4 8005B6C4 004EC023 */  subu  $t8, $v0, $t6
/* 05C2C8 8005B6C8 A618018E */  sh    $t8, 0x18e($s0)
/* 05C2CC 8005B6CC 860F018E */  lh    $t7, 0x18e($s0)
/* 05C2D0 8005B6D0 00000000 */  nop   
/* 05C2D4 8005B6D4 1DE00002 */  bgtz  $t7, .L8005B6E0
/* 05C2D8 8005B6D8 00000000 */   nop   
/* 05C2DC 8005B6DC A2000189 */  sb    $zero, 0x189($s0)
.L8005B6E0:
/* 05C2E0 8005B6E0 8E040024 */  lw    $a0, 0x24($s0)
/* 05C2E4 8005B6E4 8FA200A0 */  lw    $v0, 0xa0($sp)
/* 05C2E8 8005B6E8 10800006 */  beqz  $a0, .L8005B704
/* 05C2EC 8005B6EC 00000000 */   nop   
/* 05C2F0 8005B6F0 8C45000C */  lw    $a1, 0xc($v0)
/* 05C2F4 8005B6F4 8C460010 */  lw    $a2, 0x10($v0)
/* 05C2F8 8005B6F8 8C470014 */  lw    $a3, 0x14($v0)
/* 05C2FC 8005B6FC 0C0025B6 */  jal   update_spatial_audio_position
/* 05C300 8005B700 00000000 */   nop   
.L8005B704:
/* 05C304 8005B704 3C018012 */  lui   $at, %hi(D_8011D584) # $at, 0x8012
/* 05C308 8005B708 A020D584 */  sb    $zero, %lo(D_8011D584)($at)
/* 05C30C 8005B70C 8E020150 */  lw    $v0, 0x150($s0)
/* 05C310 8005B710 3C198012 */  lui   $t9, %hi(gRaceStartTimer) # $t9, 0x8012
/* 05C314 8005B714 10400038 */  beqz  $v0, .L8005B7F8
/* 05C318 8005B718 00000000 */   nop   
/* 05C31C 8005B71C 8F39D540 */  lw    $t9, %lo(gRaceStartTimer)($t9)
/* 05C320 8005B720 8FAD00A0 */  lw    $t5, 0xa0($sp)
/* 05C324 8005B724 17200034 */  bnez  $t9, .L8005B7F8
/* 05C328 8005B728 00002025 */   move  $a0, $zero
/* 05C32C 8005B72C C5B2000C */  lwc1  $f18, 0xc($t5)
/* 05C330 8005B730 0C0078A7 */  jal   get_misc_asset
/* 05C334 8005B734 E452000C */   swc1  $f18, 0xc($v0)
/* 05C338 8005B738 820E0003 */  lb    $t6, 3($s0)
/* 05C33C 8005B73C 8FA300A0 */  lw    $v1, 0xa0($sp)
/* 05C340 8005B740 01C2C021 */  addu  $t8, $t6, $v0
/* 05C344 8005B744 830F0000 */  lb    $t7, ($t8)
/* 05C348 8005B748 C4660010 */  lwc1  $f6, 0x10($v1)
/* 05C34C 8005B74C 448F4000 */  mtc1  $t7, $f8
/* 05C350 8005B750 8E190150 */  lw    $t9, 0x150($s0)
/* 05C354 8005B754 468042A0 */  cvt.s.w $f10, $f8
/* 05C358 8005B758 3C01800E */  lui   $at, %hi(D_800E69B0) # $at, 0x800e
/* 05C35C 8005B75C 46065100 */  add.s $f4, $f10, $f6
/* 05C360 8005B760 E7240010 */  swc1  $f4, 0x10($t9)
/* 05C364 8005B764 8E0D0150 */  lw    $t5, 0x150($s0)
/* 05C368 8005B768 C4720014 */  lwc1  $f18, 0x14($v1)
/* 05C36C 8005B76C 00000000 */  nop   
/* 05C370 8005B770 E5B20014 */  swc1  $f18, 0x14($t5)
/* 05C374 8005B774 C42A69B0 */  lwc1  $f10, %lo(D_800E69B0)($at)
/* 05C378 8005B778 C4680030 */  lwc1  $f8, 0x30($v1)
/* 05C37C 8005B77C 8E0E0150 */  lw    $t6, 0x150($s0)
/* 05C380 8005B780 460A4183 */  div.s $f6, $f8, $f10
/* 05C384 8005B784 3C01800E */  lui   $at, %hi(D_800E69B8) # $at, 0x800e
/* 05C388 8005B788 E5C60008 */  swc1  $f6, 8($t6)
/* 05C38C 8005B78C C4640030 */  lwc1  $f4, 0x30($v1)
/* 05C390 8005B790 C42869BC */  lwc1  $f8, %lo(D_800E69B8 + 4)($at)
/* 05C394 8005B794 C42969B8 */  lwc1  $f9, %lo(D_800E69B8)($at)
/* 05C398 8005B798 460024A1 */  cvt.d.s $f18, $f4
/* 05C39C 8005B79C 4628903C */  c.lt.d $f18, $f8
/* 05C3A0 8005B7A0 3C013FF0 */  li    $at, 0x3FF00000 # 1.875000
/* 05C3A4 8005B7A4 45000007 */  bc1f  .L8005B7C4
/* 05C3A8 8005B7A8 00000000 */   nop   
/* 05C3AC 8005B7AC 8E020150 */  lw    $v0, 0x150($s0)
/* 05C3B0 8005B7B0 00000000 */  nop   
/* 05C3B4 8005B7B4 84580006 */  lh    $t8, 6($v0)
/* 05C3B8 8005B7B8 00000000 */  nop   
/* 05C3BC 8005B7BC 370F4000 */  ori   $t7, $t8, 0x4000
/* 05C3C0 8005B7C0 A44F0006 */  sh    $t7, 6($v0)
.L8005B7C4:
/* 05C3C4 8005B7C4 8E020150 */  lw    $v0, 0x150($s0)
/* 05C3C8 8005B7C8 44812800 */  mtc1  $at, $f5
/* 05C3CC 8005B7CC C44A0008 */  lwc1  $f10, 8($v0)
/* 05C3D0 8005B7D0 44802000 */  mtc1  $zero, $f4
/* 05C3D4 8005B7D4 460051A1 */  cvt.d.s $f6, $f10
/* 05C3D8 8005B7D8 4624303C */  c.lt.d $f6, $f4
/* 05C3DC 8005B7DC 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 05C3E0 8005B7E0 45000004 */  bc1f  .L8005B7F4
/* 05C3E4 8005B7E4 00000000 */   nop   
/* 05C3E8 8005B7E8 44819000 */  mtc1  $at, $f18
/* 05C3EC 8005B7EC 00000000 */  nop   
/* 05C3F0 8005B7F0 E4520008 */  swc1  $f18, 8($v0)
.L8005B7F4:
/* 05C3F4 8005B7F4 AE000150 */  sw    $zero, 0x150($s0)
.L8005B7F8:
/* 05C3F8 8005B7F8 241900FF */  li    $t9, 255
/* 05C3FC 8005B7FC A21901FE */  sb    $t9, 0x1fe($s0)
/* 05C400 8005B800 0C013DDF */  jal   func_8004F77C
/* 05C404 8005B804 02002025 */   move  $a0, $s0
/* 05C408 8005B808 8FBF002C */  lw    $ra, 0x2c($sp)
/* 05C40C 8005B80C 8FB00028 */  lw    $s0, 0x28($sp)
/* 05C410 8005B810 03E00008 */  jr    $ra
/* 05C414 8005B814 27BD00A0 */   addiu $sp, $sp, 0xa0

