glabel func_800A47A0
/* 0A53A0 800A47A0 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 0A53A4 800A47A4 AFBE0038 */  sw    $fp, 0x38($sp)
/* 0A53A8 800A47A8 444EF800 */  cfc1  $t6, $31
/* 0A53AC 800A47AC 3C1E8012 */  lui   $fp, %hi(gCurrentHud) # $fp, 0x8012
/* 0A53B0 800A47B0 27DE6CDC */  addiu $fp, %lo(gCurrentHud) # addiu $fp, $fp, 0x6cdc
/* 0A53B4 800A47B4 AFB1001C */  sw    $s1, 0x1c($sp)
/* 0A53B8 800A47B8 8FD10000 */  lw    $s1, ($fp)
/* 0A53BC 800A47BC 35C10003 */  ori   $at, $t6, 3
/* 0A53C0 800A47C0 AFBF003C */  sw    $ra, 0x3c($sp)
/* 0A53C4 800A47C4 AFB70034 */  sw    $s7, 0x34($sp)
/* 0A53C8 800A47C8 AFB60030 */  sw    $s6, 0x30($sp)
/* 0A53CC 800A47CC AFB5002C */  sw    $s5, 0x2c($sp)
/* 0A53D0 800A47D0 AFB40028 */  sw    $s4, 0x28($sp)
/* 0A53D4 800A47D4 AFB30024 */  sw    $s3, 0x24($sp)
/* 0A53D8 800A47D8 AFB20020 */  sw    $s2, 0x20($sp)
/* 0A53DC 800A47DC AFB00018 */  sw    $s0, 0x18($sp)
/* 0A53E0 800A47E0 AFA5004C */  sw    $a1, 0x4c($sp)
/* 0A53E4 800A47E4 38210002 */  xori  $at, $at, 2
/* 0A53E8 800A47E8 44C1F800 */  ctc1  $at, $31
/* 0A53EC 800A47EC C62405D0 */  lwc1  $f4, 0x5d0($s1)
/* 0A53F0 800A47F0 3C128080 */  lui   $s2, (0x80808080 >> 16) # lui $s2, 0x8080
/* 0A53F4 800A47F4 460021A4 */  cvt.w.s $f6, $f4
/* 0A53F8 800A47F8 3C138012 */  lui   $s3, %hi(gHUDCurrDisplayList) # $s3, 0x8012
/* 0A53FC 800A47FC 440F3000 */  mfc1  $t7, $f6
/* 0A5400 800A4800 44CEF800 */  ctc1  $t6, $31
/* 0A5404 800A4804 448F4000 */  mtc1  $t7, $f8
/* 0A5408 800A4808 3C148012 */  lui   $s4, %hi(gHUDCurrMatrix) # $s4, 0x8012
/* 0A540C 800A480C 468042A0 */  cvt.s.w $f10, $f8
/* 0A5410 800A4810 3C158012 */  lui   $s5, %hi(gHUDCurrVertex) # $s5, 0x8012
/* 0A5414 800A4814 0080B025 */  move  $s6, $a0
/* 0A5418 800A4818 4459F800 */  cfc1  $t9, $31
/* 0A541C 800A481C E62A05D0 */  swc1  $f10, 0x5d0($s1)
/* 0A5420 800A4820 8FD80000 */  lw    $t8, ($fp)
/* 0A5424 800A4824 37210003 */  ori   $at, $t9, 3
/* 0A5428 800A4828 38210002 */  xori  $at, $at, 2
/* 0A542C 800A482C 44C1F800 */  ctc1  $at, $31
/* 0A5430 800A4830 C71005D0 */  lwc1  $f16, 0x5d0($t8)
/* 0A5434 800A4834 26B56D04 */  addiu $s5, %lo(gHUDCurrVertex) # addiu $s5, $s5, 0x6d04
/* 0A5438 800A4838 460084A4 */  cvt.w.s $f18, $f16
/* 0A543C 800A483C 26946D00 */  addiu $s4, %lo(gHUDCurrMatrix) # addiu $s4, $s4, 0x6d00
/* 0A5440 800A4840 44089000 */  mfc1  $t0, $f18
/* 0A5444 800A4844 44D9F800 */  ctc1  $t9, $31
/* 0A5448 800A4848 26736CFC */  addiu $s3, %lo(gHUDCurrDisplayList) # addiu $s3, $s3, 0x6cfc
/* 0A544C 800A484C 36528080 */  ori   $s2, (0x80808080 & 0xFFFF) # ori $s2, $s2, 0x8080
/* 0A5450 800A4850 00008025 */  move  $s0, $zero
/* 0A5454 800A4854 24170008 */  li    $s7, 8
/* 0A5458 800A4858 AFA80040 */  sw    $t0, 0x40($sp)
.L800A485C:
/* 0A545C 800A485C 82C90202 */  lb    $t1, 0x202($s6)
/* 0A5460 800A4860 8FD10000 */  lw    $s1, ($fp)
/* 0A5464 800A4864 0209082A */  slt   $at, $s0, $t1
/* 0A5468 800A4868 14200003 */  bnez  $at, .L800A4878
/* 0A546C 800A486C 02602025 */   move  $a0, $s3
/* 0A5470 800A4870 3C01800E */  lui   $at, %hi(D_800E2834) # $at, 0x800e
/* 0A5474 800A4874 AC322834 */  sw    $s2, %lo(D_800E2834)($at)
.L800A4878:
/* 0A5478 800A4878 02802825 */  move  $a1, $s4
/* 0A547C 800A487C 02A03025 */  move  $a2, $s5
/* 0A5480 800A4880 0C02A980 */  jal   func_800AA600
/* 0A5484 800A4884 262705C0 */   addiu $a3, $s1, 0x5c0
/* 0A5488 800A4888 8FD10000 */  lw    $s1, ($fp)
/* 0A548C 800A488C 26100001 */  addiu $s0, $s0, 1
/* 0A5490 800A4890 822A05DC */  lb    $t2, 0x5dc($s1)
/* 0A5494 800A4894 C62405D0 */  lwc1  $f4, 0x5d0($s1)
/* 0A5498 800A4898 448A3000 */  mtc1  $t2, $f6
/* 0A549C 800A489C 00000000 */  nop   
/* 0A54A0 800A48A0 46803220 */  cvt.s.w $f8, $f6
/* 0A54A4 800A48A4 46082281 */  sub.s $f10, $f4, $f8
/* 0A54A8 800A48A8 1617FFEC */  bne   $s0, $s7, .L800A485C
/* 0A54AC 800A48AC E62A05D0 */   swc1  $f10, 0x5d0($s1)
/* 0A54B0 800A48B0 82CB0202 */  lb    $t3, 0x202($s6)
/* 0A54B4 800A48B4 00000000 */  nop   
/* 0A54B8 800A48B8 16EB001D */  bne   $s7, $t3, .L800A4930
/* 0A54BC 800A48BC 8FA80040 */   lw    $t0, 0x40($sp)
/* 0A54C0 800A48C0 8FD10000 */  lw    $s1, ($fp)
/* 0A54C4 800A48C4 8FAC004C */  lw    $t4, 0x4c($sp)
/* 0A54C8 800A48C8 822205DB */  lb    $v0, 0x5db($s1)
/* 0A54CC 800A48CC 00000000 */  nop   
/* 0A54D0 800A48D0 2841001E */  slti  $at, $v0, 0x1e
/* 0A54D4 800A48D4 10200004 */  beqz  $at, .L800A48E8
/* 0A54D8 800A48D8 004C6821 */   addu  $t5, $v0, $t4
/* 0A54DC 800A48DC A22D05DB */  sb    $t5, 0x5db($s1)
/* 0A54E0 800A48E0 8FD10000 */  lw    $s1, ($fp)
/* 0A54E4 800A48E4 00000000 */  nop   
.L800A48E8:
/* 0A54E8 800A48E8 822E05DA */  lb    $t6, 0x5da($s1)
/* 0A54EC 800A48EC 00000000 */  nop   
/* 0A54F0 800A48F0 15C0000F */  bnez  $t6, .L800A4930
/* 0A54F4 800A48F4 8FA80040 */   lw    $t0, 0x40($sp)
/* 0A54F8 800A48F8 822F05DB */  lb    $t7, 0x5db($s1)
/* 0A54FC 800A48FC 3C058012 */  lui   $a1, %hi(gHUDVoiceSoundMask) # $a1, 0x8012
/* 0A5500 800A4900 29E1001E */  slti  $at, $t7, 0x1e
/* 0A5504 800A4904 14200009 */  bnez  $at, .L800A492C
/* 0A5508 800A4908 24A56D40 */   addiu $a1, %lo(gHUDVoiceSoundMask) # addiu $a1, $a1, 0x6d40
/* 0A550C 800A490C 24180001 */  li    $t8, 1
/* 0A5510 800A4910 A23805DA */  sb    $t8, 0x5da($s1)
/* 0A5514 800A4914 8CB90000 */  lw    $t9, ($a1)
/* 0A5518 800A4918 00000000 */  nop   
/* 0A551C 800A491C 17200004 */  bnez  $t9, .L800A4930
/* 0A5520 800A4920 8FA80040 */   lw    $t0, 0x40($sp)
/* 0A5524 800A4924 0C000741 */  jal   play_sound_global
/* 0A5528 800A4928 24040147 */   li    $a0, 327
.L800A492C:
/* 0A552C 800A492C 8FA80040 */  lw    $t0, 0x40($sp)
.L800A4930:
/* 0A5530 800A4930 8FC90000 */  lw    $t1, ($fp)
/* 0A5534 800A4934 44888000 */  mtc1  $t0, $f16
/* 0A5538 800A4938 240AFFFE */  li    $t2, -2
/* 0A553C 800A493C 468084A0 */  cvt.s.w $f18, $f16
/* 0A5540 800A4940 3C01800E */  lui   $at, %hi(D_800E2834) # $at, 0x800e
/* 0A5544 800A4944 E53205D0 */  swc1  $f18, 0x5d0($t1)
/* 0A5548 800A4948 8FBF003C */  lw    $ra, 0x3c($sp)
/* 0A554C 800A494C 8FBE0038 */  lw    $fp, 0x38($sp)
/* 0A5550 800A4950 8FB70034 */  lw    $s7, 0x34($sp)
/* 0A5554 800A4954 8FB60030 */  lw    $s6, 0x30($sp)
/* 0A5558 800A4958 8FB5002C */  lw    $s5, 0x2c($sp)
/* 0A555C 800A495C 8FB40028 */  lw    $s4, 0x28($sp)
/* 0A5560 800A4960 8FB30024 */  lw    $s3, 0x24($sp)
/* 0A5564 800A4964 8FB20020 */  lw    $s2, 0x20($sp)
/* 0A5568 800A4968 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0A556C 800A496C 8FB00018 */  lw    $s0, 0x18($sp)
/* 0A5570 800A4970 AC2A2834 */  sw    $t2, %lo(D_800E2834)($at)
/* 0A5574 800A4974 03E00008 */  jr    $ra
/* 0A5578 800A4978 27BD0048 */   addiu $sp, $sp, 0x48

