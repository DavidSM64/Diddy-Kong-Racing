glabel func_800BA8E4
/* 0BB4E4 800BA8E4 27BDFEE0 */  addiu $sp, $sp, -0x120
/* 0BB4E8 800BA8E8 24010001 */  li    $at, 1
/* 0BB4EC 800BA8EC AFBF005C */  sw    $ra, 0x5c($sp)
/* 0BB4F0 800BA8F0 AFBE0058 */  sw    $fp, 0x58($sp)
/* 0BB4F4 800BA8F4 AFB70054 */  sw    $s7, 0x54($sp)
/* 0BB4F8 800BA8F8 AFB60050 */  sw    $s6, 0x50($sp)
/* 0BB4FC 800BA8FC AFB5004C */  sw    $s5, 0x4c($sp)
/* 0BB500 800BA900 AFB40048 */  sw    $s4, 0x48($sp)
/* 0BB504 800BA904 AFB30044 */  sw    $s3, 0x44($sp)
/* 0BB508 800BA908 AFB20040 */  sw    $s2, 0x40($sp)
/* 0BB50C 800BA90C AFB1003C */  sw    $s1, 0x3c($sp)
/* 0BB510 800BA910 AFB00038 */  sw    $s0, 0x38($sp)
/* 0BB514 800BA914 E7B90030 */  swc1  $f25, 0x30($sp)
/* 0BB518 800BA918 E7B80034 */  swc1  $f24, 0x34($sp)
/* 0BB51C 800BA91C E7B70028 */  swc1  $f23, 0x28($sp)
/* 0BB520 800BA920 E7B6002C */  swc1  $f22, 0x2c($sp)
/* 0BB524 800BA924 E7B50020 */  swc1  $f21, 0x20($sp)
/* 0BB528 800BA928 E7B40024 */  swc1  $f20, 0x24($sp)
/* 0BB52C 800BA92C AFA40120 */  sw    $a0, 0x120($sp)
/* 0BB530 800BA930 14C10006 */  bne   $a2, $at, .L800BA94C
/* 0BB534 800BA934 AFA50124 */   sw    $a1, 0x124($sp)
/* 0BB538 800BA938 3C0E8013 */  lui   $t6, %hi(D_8012A078) # $t6, 0x8013
/* 0BB53C 800BA93C 8DCEA078 */  lw    $t6, %lo(D_8012A078)($t6)
/* 0BB540 800BA940 24010002 */  li    $at, 2
/* 0BB544 800BA944 11C10003 */  beq   $t6, $at, .L800BA954
/* 0BB548 800BA948 240F0002 */   li    $t7, 2
.L800BA94C:
/* 0BB54C 800BA94C 10000002 */  b     .L800BA958
/* 0BB550 800BA950 AFA00128 */   sw    $zero, 0x128($sp)
.L800BA954:
/* 0BB554 800BA954 AFAF0128 */  sw    $t7, 0x128($sp)
.L800BA958:
/* 0BB558 800BA958 3C18800E */  lui   $t8, %hi(D_800E30DC) # $t8, 0x800e
/* 0BB55C 800BA95C 8F1830DC */  lw    $t8, %lo(D_800E30DC)($t8)
/* 0BB560 800BA960 3C118013 */  lui   $s1, %hi(D_80129FC0) # $s1, 0x8013
/* 0BB564 800BA964 1B00024F */  blez  $t8, .L800BB2A4
/* 0BB568 800BA968 26319FC0 */   addiu $s1, %lo(D_80129FC0) # addiu $s1, $s1, -0x6040
/* 0BB56C 800BA96C 8FB90120 */  lw    $t9, 0x120($sp)
/* 0BB570 800BA970 8FAF0124 */  lw    $t7, 0x124($sp)
/* 0BB574 800BA974 8F2E0000 */  lw    $t6, ($t9)
/* 0BB578 800BA978 3C018013 */  lui   $at, %hi(D_80129FC4) # $at, 0x8013
/* 0BB57C 800BA97C AE2E0000 */  sw    $t6, ($s1)
/* 0BB580 800BA980 8DF80000 */  lw    $t8, ($t7)
/* 0BB584 800BA984 AFA000DC */  sw    $zero, 0xdc($sp)
/* 0BB588 800BA988 02202025 */  move  $a0, $s1
/* 0BB58C 800BA98C 0C01ECF4 */  jal   reset_render_settings
/* 0BB590 800BA990 AC389FC4 */   sw    $t8, %lo(D_80129FC4)($at)
/* 0BB594 800BA994 8E270000 */  lw    $a3, ($s1)
/* 0BB598 800BA998 3C1F8013 */  lui   $ra, %hi(D_80129FC8) # $ra, 0x8013
/* 0BB59C 800BA99C 24F90008 */  addiu $t9, $a3, 8
/* 0BB5A0 800BA9A0 AE390000 */  sw    $t9, ($s1)
/* 0BB5A4 800BA9A4 3C0EB700 */  lui   $t6, 0xb700
/* 0BB5A8 800BA9A8 240F0001 */  li    $t7, 1
/* 0BB5AC 800BA9AC 27FF9FC8 */  addiu $ra, %lo(D_80129FC8) # addiu $ra, $ra, -0x6038
/* 0BB5B0 800BA9B0 ACEF0004 */  sw    $t7, 4($a3)
/* 0BB5B4 800BA9B4 ACEE0000 */  sw    $t6, ($a3)
/* 0BB5B8 800BA9B8 8FF8004C */  lw    $t8, 0x4c($ra)
/* 0BB5BC 800BA9BC 3C190001 */  lui   $t9, 1
/* 0BB5C0 800BA9C0 1300006F */  beqz  $t8, .L800BAB80
/* 0BB5C4 800BA9C4 3C0F8013 */   lui   $t7, %hi(gWaveBatch) # $t7, 0x8013
/* 0BB5C8 800BA9C8 8E270000 */  lw    $a3, ($s1)
/* 0BB5CC 800BA9CC 3C0EB600 */  lui   $t6, 0xb600
/* 0BB5D0 800BA9D0 24F90008 */  addiu $t9, $a3, 8
/* 0BB5D4 800BA9D4 AE390000 */  sw    $t9, ($s1)
/* 0BB5D8 800BA9D8 3C0F0001 */  lui   $t7, 1
/* 0BB5DC 800BA9DC 3C058013 */  lui   $a1, %hi(D_8012A09C) # $a1, 0x8013
/* 0BB5E0 800BA9E0 ACEF0004 */  sw    $t7, 4($a3)
/* 0BB5E4 800BA9E4 ACEE0000 */  sw    $t6, ($a3)
/* 0BB5E8 800BA9E8 8CA5A09C */  lw    $a1, %lo(D_8012A09C)($a1)
/* 0BB5EC 800BA9EC 3C04800E */  lui   $a0, %hi(D_800E30D0) # $a0, 0x800e
/* 0BB5F0 800BA9F0 8C8430D0 */  lw    $a0, %lo(D_800E30D0)($a0)
/* 0BB5F4 800BA9F4 0005C200 */  sll   $t8, $a1, 8
/* 0BB5F8 800BA9F8 0C01ED1B */  jal   set_animated_texture_header
/* 0BB5FC 800BA9FC 03002825 */   move  $a1, $t8
/* 0BB600 800BAA00 3C198013 */  lui   $t9, %hi(gWaveBatch) # $t9, 0x8013
/* 0BB604 800BAA04 8F39A07C */  lw    $t9, %lo(gWaveBatch)($t9)
/* 0BB608 800BAA08 3C048013 */  lui   $a0, %hi(gWaveTexture) # $a0, 0x8013
/* 0BB60C 800BAA0C 93250007 */  lbu   $a1, 7($t9)
/* 0BB610 800BAA10 8C84A080 */  lw    $a0, %lo(gWaveTexture)($a0)
/* 0BB614 800BAA14 00057380 */  sll   $t6, $a1, 0xe
/* 0BB618 800BAA18 00408025 */  move  $s0, $v0
/* 0BB61C 800BAA1C 0C01ED1B */  jal   set_animated_texture_header
/* 0BB620 800BAA20 01C02825 */   move  $a1, $t6
/* 0BB624 800BAA24 00409025 */  move  $s2, $v0
/* 0BB628 800BAA28 02002025 */  move  $a0, $s0
/* 0BB62C 800BAA2C 0C02E92E */  jal   func_800BA4B8
/* 0BB630 800BAA30 24050001 */   li    $a1, 1
/* 0BB634 800BAA34 02402025 */  move  $a0, $s2
/* 0BB638 800BAA38 0C02E92E */  jal   func_800BA4B8
/* 0BB63C 800BAA3C 00002825 */   move  $a1, $zero
/* 0BB640 800BAA40 8E270000 */  lw    $a3, ($s1)
/* 0BB644 800BAA44 3C18FC22 */  lui   $t8, (0xFC2266AC >> 16) # lui $t8, 0xfc22
/* 0BB648 800BAA48 24EF0008 */  addiu $t7, $a3, 8
/* 0BB64C 800BAA4C AE2F0000 */  sw    $t7, ($s1)
/* 0BB650 800BAA50 3C191010 */  lui   $t9, (0x1010923F >> 16) # lui $t9, 0x1010
/* 0BB654 800BAA54 3739923F */  ori   $t9, (0x1010923F & 0xFFFF) # ori $t9, $t9, 0x923f
/* 0BB658 800BAA58 371866AC */  ori   $t8, (0xFC2266AC & 0xFFFF) # ori $t8, $t8, 0x66ac
/* 0BB65C 800BAA5C ACF80000 */  sw    $t8, ($a3)
/* 0BB660 800BAA60 ACF90004 */  sw    $t9, 4($a3)
/* 0BB664 800BAA64 920E0002 */  lbu   $t6, 2($s0)
/* 0BB668 800BAA68 3C1F8013 */  lui   $ra, %hi(D_80129FC8) # $ra, 0x8013
/* 0BB66C 800BAA6C 31CF000F */  andi  $t7, $t6, 0xf
/* 0BB670 800BAA70 15E00010 */  bnez  $t7, .L800BAAB4
/* 0BB674 800BAA74 27FF9FC8 */   addiu $ra, %lo(D_80129FC8) # addiu $ra, $ra, -0x6038
/* 0BB678 800BAA78 0C019884 */  jal   get_viewport_count
/* 0BB67C 800BAA7C 00000000 */   nop   
/* 0BB680 800BAA80 3C1F8013 */  lui   $ra, %hi(D_80129FC8) # $ra, 0x8013
/* 0BB684 800BAA84 1C40000B */  bgtz  $v0, .L800BAAB4
/* 0BB688 800BAA88 27FF9FC8 */   addiu $ra, %lo(D_80129FC8) # addiu $ra, $ra, -0x6038
/* 0BB68C 800BAA8C 8E270000 */  lw    $a3, ($s1)
/* 0BB690 800BAA90 3C19EF18 */  lui   $t9, (0xEF182C0F >> 16) # lui $t9, 0xef18
/* 0BB694 800BAA94 3C0E0010 */  lui   $t6, (0x001045D8 >> 16) # lui $t6, 0x10
/* 0BB698 800BAA98 24F80008 */  addiu $t8, $a3, 8
/* 0BB69C 800BAA9C AE380000 */  sw    $t8, ($s1)
/* 0BB6A0 800BAAA0 35CE45D8 */  ori   $t6, (0x001045D8 & 0xFFFF) # ori $t6, $t6, 0x45d8
/* 0BB6A4 800BAAA4 37392C0F */  ori   $t9, (0xEF182C0F & 0xFFFF) # ori $t9, $t9, 0x2c0f
/* 0BB6A8 800BAAA8 ACF90000 */  sw    $t9, ($a3)
/* 0BB6AC 800BAAAC 1000000A */  b     .L800BAAD8
/* 0BB6B0 800BAAB0 ACEE0004 */   sw    $t6, 4($a3)
.L800BAAB4:
/* 0BB6B4 800BAAB4 8E270000 */  lw    $a3, ($s1)
/* 0BB6B8 800BAAB8 3C18EF18 */  lui   $t8, (0xEF182C0F >> 16) # lui $t8, 0xef18
/* 0BB6BC 800BAABC 24EF0008 */  addiu $t7, $a3, 8
/* 0BB6C0 800BAAC0 AE2F0000 */  sw    $t7, ($s1)
/* 0BB6C4 800BAAC4 3C190011 */  lui   $t9, (0x00112078 >> 16) # lui $t9, 0x11
/* 0BB6C8 800BAAC8 37392078 */  ori   $t9, (0x00112078 & 0xFFFF) # ori $t9, $t9, 0x2078
/* 0BB6CC 800BAACC 37182C0F */  ori   $t8, (0xEF182C0F & 0xFFFF) # ori $t8, $t8, 0x2c0f
/* 0BB6D0 800BAAD0 ACF80000 */  sw    $t8, ($a3)
/* 0BB6D4 800BAAD4 ACF90004 */  sw    $t9, 4($a3)
.L800BAAD8:
/* 0BB6D8 800BAAD8 8E270000 */  lw    $a3, ($s1)
/* 0BB6DC 800BAADC 2403FF00 */  li    $v1, -256
/* 0BB6E0 800BAAE0 24EE0008 */  addiu $t6, $a3, 8
/* 0BB6E4 800BAAE4 AE2E0000 */  sw    $t6, ($s1)
/* 0BB6E8 800BAAE8 3C09800E */  lui   $t1, %hi(D_800E3180) # $t1, 0x800e
/* 0BB6EC 800BAAEC 3C0FFA00 */  lui   $t7, 0xfa00
/* 0BB6F0 800BAAF0 25293180 */  addiu $t1, %lo(D_800E3180) # addiu $t1, $t1, 0x3180
/* 0BB6F4 800BAAF4 ACEF0000 */  sw    $t7, ($a3)
/* 0BB6F8 800BAAF8 ACE30004 */  sw    $v1, 4($a3)
/* 0BB6FC 800BAAFC 8D380000 */  lw    $t8, ($t1)
/* 0BB700 800BAB00 00000000 */  nop   
/* 0BB704 800BAB04 13000016 */  beqz  $t8, .L800BAB60
/* 0BB708 800BAB08 00000000 */   nop   
/* 0BB70C 800BAB0C 8E270000 */  lw    $a3, ($s1)
/* 0BB710 800BAB10 3C0EFB00 */  lui   $t6, 0xfb00
/* 0BB714 800BAB14 24F90008 */  addiu $t9, $a3, 8
/* 0BB718 800BAB18 AE390000 */  sw    $t9, ($s1)
/* 0BB71C 800BAB1C ACEE0000 */  sw    $t6, ($a3)
/* 0BB720 800BAB20 8D220000 */  lw    $v0, ($t1)
/* 0BB724 800BAB24 3C128000 */  lui   $s2, 0x8000
/* 0BB728 800BAB28 90580010 */  lbu   $t8, 0x10($v0)
/* 0BB72C 800BAB2C 904F0011 */  lbu   $t7, 0x11($v0)
/* 0BB730 800BAB30 0018CE00 */  sll   $t9, $t8, 0x18
/* 0BB734 800BAB34 000FC400 */  sll   $t8, $t7, 0x10
/* 0BB738 800BAB38 03387025 */  or    $t6, $t9, $t8
/* 0BB73C 800BAB3C 90590012 */  lbu   $t9, 0x12($v0)
/* 0BB740 800BAB40 00000000 */  nop   
/* 0BB744 800BAB44 0019C200 */  sll   $t8, $t9, 8
/* 0BB748 800BAB48 01D87825 */  or    $t7, $t6, $t8
/* 0BB74C 800BAB4C 904E0013 */  lbu   $t6, 0x13($v0)
/* 0BB750 800BAB50 00000000 */  nop   
/* 0BB754 800BAB54 01EEC025 */  or    $t8, $t7, $t6
/* 0BB758 800BAB58 10000061 */  b     .L800BACE0
/* 0BB75C 800BAB5C ACF80004 */   sw    $t8, 4($a3)
.L800BAB60:
/* 0BB760 800BAB60 8E270000 */  lw    $a3, ($s1)
/* 0BB764 800BAB64 3C0FFB00 */  lui   $t7, 0xfb00
/* 0BB768 800BAB68 24F90008 */  addiu $t9, $a3, 8
/* 0BB76C 800BAB6C AE390000 */  sw    $t9, ($s1)
/* 0BB770 800BAB70 ACE30004 */  sw    $v1, 4($a3)
/* 0BB774 800BAB74 ACEF0000 */  sw    $t7, ($a3)
/* 0BB778 800BAB78 10000059 */  b     .L800BACE0
/* 0BB77C 800BAB7C 3C128000 */   lui   $s2, 0x8000
.L800BAB80:
/* 0BB780 800BAB80 8E270000 */  lw    $a3, ($s1)
/* 0BB784 800BAB84 3C18B700 */  lui   $t8, 0xb700
/* 0BB788 800BAB88 24EE0008 */  addiu $t6, $a3, 8
/* 0BB78C 800BAB8C AE2E0000 */  sw    $t6, ($s1)
/* 0BB790 800BAB90 ACF90004 */  sw    $t9, 4($a3)
/* 0BB794 800BAB94 ACF80000 */  sw    $t8, ($a3)
/* 0BB798 800BAB98 8DEFA07C */  lw    $t7, %lo(gWaveBatch)($t7)
/* 0BB79C 800BAB9C 3C048013 */  lui   $a0, %hi(gWaveTexture) # $a0, 0x8013
/* 0BB7A0 800BABA0 91E50007 */  lbu   $a1, 7($t7)
/* 0BB7A4 800BABA4 8C84A080 */  lw    $a0, %lo(gWaveTexture)($a0)
/* 0BB7A8 800BABA8 00057380 */  sll   $t6, $a1, 0xe
/* 0BB7AC 800BABAC 0C01ED1B */  jal   set_animated_texture_header
/* 0BB7B0 800BABB0 01C02825 */   move  $a1, $t6
/* 0BB7B4 800BABB4 8E270000 */  lw    $a3, ($s1)
/* 0BB7B8 800BABB8 3C010700 */  lui   $at, 0x700
/* 0BB7BC 800BABBC 24F80008 */  addiu $t8, $a3, 8
/* 0BB7C0 800BABC0 AE380000 */  sw    $t8, ($s1)
/* 0BB7C4 800BABC4 8444000A */  lh    $a0, 0xa($v0)
/* 0BB7C8 800BABC8 3C128000 */  lui   $s2, 0x8000
/* 0BB7CC 800BABCC 309900FF */  andi  $t9, $a0, 0xff
/* 0BB7D0 800BABD0 00197C00 */  sll   $t7, $t9, 0x10
/* 0BB7D4 800BABD4 0004C0C0 */  sll   $t8, $a0, 3
/* 0BB7D8 800BABD8 3319FFFF */  andi  $t9, $t8, 0xffff
/* 0BB7DC 800BABDC 01E17025 */  or    $t6, $t7, $at
/* 0BB7E0 800BABE0 01D97825 */  or    $t7, $t6, $t9
/* 0BB7E4 800BABE4 ACEF0000 */  sw    $t7, ($a3)
/* 0BB7E8 800BABE8 8C58000C */  lw    $t8, 0xc($v0)
/* 0BB7EC 800BABEC 3C0FFC56 */  lui   $t7, (0xFC567E04 >> 16) # lui $t7, 0xfc56
/* 0BB7F0 800BABF0 03127021 */  addu  $t6, $t8, $s2
/* 0BB7F4 800BABF4 ACEE0004 */  sw    $t6, 4($a3)
/* 0BB7F8 800BABF8 8E270000 */  lw    $a3, ($s1)
/* 0BB7FC 800BABFC 3C181FFC */  lui   $t8, (0x1FFCF7F8 >> 16) # lui $t8, 0x1ffc
/* 0BB800 800BAC00 24F90008 */  addiu $t9, $a3, 8
/* 0BB804 800BAC04 AE390000 */  sw    $t9, ($s1)
/* 0BB808 800BAC08 3718F7F8 */  ori   $t8, (0x1FFCF7F8 & 0xFFFF) # ori $t8, $t8, 0xf7f8
/* 0BB80C 800BAC0C 35EF7E04 */  ori   $t7, (0xFC567E04 & 0xFFFF) # ori $t7, $t7, 0x7e04
/* 0BB810 800BAC10 ACEF0000 */  sw    $t7, ($a3)
/* 0BB814 800BAC14 ACF80004 */  sw    $t8, 4($a3)
/* 0BB818 800BAC18 8E270000 */  lw    $a3, ($s1)
/* 0BB81C 800BAC1C 3C0FC811 */  lui   $t7, (0xC8112078 >> 16) # lui $t7, 0xc811
/* 0BB820 800BAC20 24EE0008 */  addiu $t6, $a3, 8
/* 0BB824 800BAC24 AE2E0000 */  sw    $t6, ($s1)
/* 0BB828 800BAC28 3C19EF18 */  lui   $t9, (0xEF182C0F >> 16) # lui $t9, 0xef18
/* 0BB82C 800BAC2C 37392C0F */  ori   $t9, (0xEF182C0F & 0xFFFF) # ori $t9, $t9, 0x2c0f
/* 0BB830 800BAC30 35EF2078 */  ori   $t7, (0xC8112078 & 0xFFFF) # ori $t7, $t7, 0x2078
/* 0BB834 800BAC34 ACEF0004 */  sw    $t7, 4($a3)
/* 0BB838 800BAC38 ACF90000 */  sw    $t9, ($a3)
/* 0BB83C 800BAC3C 8E270000 */  lw    $a3, ($s1)
/* 0BB840 800BAC40 3C09800E */  lui   $t1, %hi(D_800E3180) # $t1, 0x800e
/* 0BB844 800BAC44 24F80008 */  addiu $t8, $a3, 8
/* 0BB848 800BAC48 AE380000 */  sw    $t8, ($s1)
/* 0BB84C 800BAC4C 2419FFFF */  li    $t9, -1
/* 0BB850 800BAC50 3C0EFA00 */  lui   $t6, 0xfa00
/* 0BB854 800BAC54 25293180 */  addiu $t1, %lo(D_800E3180) # addiu $t1, $t1, 0x3180
/* 0BB858 800BAC58 ACEE0000 */  sw    $t6, ($a3)
/* 0BB85C 800BAC5C ACF90004 */  sw    $t9, 4($a3)
/* 0BB860 800BAC60 8D2F0000 */  lw    $t7, ($t1)
/* 0BB864 800BAC64 3C1F8013 */  lui   $ra, %hi(D_80129FC8) # $ra, 0x8013
/* 0BB868 800BAC68 11E00016 */  beqz  $t7, .L800BACC4
/* 0BB86C 800BAC6C 27FF9FC8 */   addiu $ra, %lo(D_80129FC8) # addiu $ra, $ra, -0x6038
/* 0BB870 800BAC70 8E270000 */  lw    $a3, ($s1)
/* 0BB874 800BAC74 3C0EFB00 */  lui   $t6, 0xfb00
/* 0BB878 800BAC78 24F80008 */  addiu $t8, $a3, 8
/* 0BB87C 800BAC7C AE380000 */  sw    $t8, ($s1)
/* 0BB880 800BAC80 ACEE0000 */  sw    $t6, ($a3)
/* 0BB884 800BAC84 8D220000 */  lw    $v0, ($t1)
/* 0BB888 800BAC88 00000000 */  nop   
/* 0BB88C 800BAC8C 904F0010 */  lbu   $t7, 0x10($v0)
/* 0BB890 800BAC90 90590011 */  lbu   $t9, 0x11($v0)
/* 0BB894 800BAC94 000FC600 */  sll   $t8, $t7, 0x18
/* 0BB898 800BAC98 00197C00 */  sll   $t7, $t9, 0x10
/* 0BB89C 800BAC9C 030F7025 */  or    $t6, $t8, $t7
/* 0BB8A0 800BACA0 90580012 */  lbu   $t8, 0x12($v0)
/* 0BB8A4 800BACA4 00000000 */  nop   
/* 0BB8A8 800BACA8 00187A00 */  sll   $t7, $t8, 8
/* 0BB8AC 800BACAC 01CFC825 */  or    $t9, $t6, $t7
/* 0BB8B0 800BACB0 904E0013 */  lbu   $t6, 0x13($v0)
/* 0BB8B4 800BACB4 00000000 */  nop   
/* 0BB8B8 800BACB8 032E7825 */  or    $t7, $t9, $t6
/* 0BB8BC 800BACBC 10000008 */  b     .L800BACE0
/* 0BB8C0 800BACC0 ACEF0004 */   sw    $t7, 4($a3)
.L800BACC4:
/* 0BB8C4 800BACC4 8E270000 */  lw    $a3, ($s1)
/* 0BB8C8 800BACC8 2403FF00 */  li    $v1, -256
/* 0BB8CC 800BACCC 24F80008 */  addiu $t8, $a3, 8
/* 0BB8D0 800BACD0 AE380000 */  sw    $t8, ($s1)
/* 0BB8D4 800BACD4 3C19FB00 */  lui   $t9, 0xfb00
/* 0BB8D8 800BACD8 ACF90000 */  sw    $t9, ($a3)
/* 0BB8DC 800BACDC ACE30004 */  sw    $v1, 4($a3)
.L800BACE0:
/* 0BB8E0 800BACE0 8FEE0028 */  lw    $t6, 0x28($ra)
/* 0BB8E4 800BACE4 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 0BB8E8 800BACE8 11C00007 */  beqz  $t6, .L800BAD08
/* 0BB8EC 800BACEC 3C0F800E */   lui   $t7, %hi(D_800E30DC) # $t7, 0x800e
/* 0BB8F0 800BACF0 3C013F00 */  li    $at, 0x3F000000 # 0.500000
/* 0BB8F4 800BACF4 4481A000 */  mtc1  $at, $f20
/* 0BB8F8 800BACF8 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 0BB8FC 800BACFC 4481C000 */  mtc1  $at, $f24
/* 0BB900 800BAD00 10000005 */  b     .L800BAD18
/* 0BB904 800BAD04 E7B400EC */   swc1  $f20, 0xec($sp)
.L800BAD08:
/* 0BB908 800BAD08 4481C000 */  mtc1  $at, $f24
/* 0BB90C 800BAD0C 3C013F00 */  li    $at, 0x3F000000 # 0.500000
/* 0BB910 800BAD10 4481A000 */  mtc1  $at, $f20
/* 0BB914 800BAD14 E7B800EC */  swc1  $f24, 0xec($sp)
.L800BAD18:
/* 0BB918 800BAD18 8DEF30DC */  lw    $t7, %lo(D_800E30DC)($t7)
/* 0BB91C 800BAD1C A7A000E8 */  sh    $zero, 0xe8($sp)
/* 0BB920 800BAD20 A7A000E6 */  sh    $zero, 0xe6($sp)
/* 0BB924 800BAD24 19E00146 */  blez  $t7, .L800BB240
/* 0BB928 800BAD28 A7A000E4 */   sh    $zero, 0xe4($sp)
/* 0BB92C 800BAD2C 8FB800DC */  lw    $t8, 0xdc($sp)
/* 0BB930 800BAD30 3C0E8013 */  lui   $t6, %hi(D_8012A1E8) # $t6, 0x8013
/* 0BB934 800BAD34 25CEA1E8 */  addiu $t6, %lo(D_8012A1E8) # addiu $t6, $t6, -0x5e18
/* 0BB938 800BAD38 0018C840 */  sll   $t9, $t8, 1
/* 0BB93C 800BAD3C 032E8021 */  addu  $s0, $t9, $t6
/* 0BB940 800BAD40 3C17800E */  lui   $s7, %hi(D_800E3080) # $s7, 0x800e
/* 0BB944 800BAD44 3C15800E */  lui   $s5, %hi(D_800E3070) # $s5, 0x800e
/* 0BB948 800BAD48 3C138013 */  lui   $s3, %hi(D_8012A018) # $s3, 0x8013
/* 0BB94C 800BAD4C 4480B000 */  mtc1  $zero, $f22
/* 0BB950 800BAD50 2673A018 */  addiu $s3, %lo(D_8012A018) # addiu $s3, $s3, -0x5fe8
/* 0BB954 800BAD54 26B53070 */  addiu $s5, %lo(D_800E3070) # addiu $s5, $s5, 0x3070
/* 0BB958 800BAD58 26F73080 */  addiu $s7, %lo(D_800E3080) # addiu $s7, $s7, 0x3080
/* 0BB95C 800BAD5C AFB00074 */  sw    $s0, 0x74($sp)
/* 0BB960 800BAD60 2416000A */  li    $s6, 10
/* 0BB964 800BAD64 3C140400 */  lui   $s4, 0x400
.L800BAD68:
/* 0BB968 800BAD68 8FEF004C */  lw    $t7, 0x4c($ra)
/* 0BB96C 800BAD6C 8FB00074 */  lw    $s0, 0x74($sp)
/* 0BB970 800BAD70 11E00008 */  beqz  $t7, .L800BAD94
/* 0BB974 800BAD74 00000000 */   nop   
/* 0BB978 800BAD78 86040000 */  lh    $a0, ($s0)
/* 0BB97C 800BAD7C 8FA50128 */  lw    $a1, 0x128($sp)
/* 0BB980 800BAD80 0C02E4BD */  jal   func_800B92F4
/* 0BB984 800BAD84 00000000 */   nop   
/* 0BB988 800BAD88 3C1F8013 */  lui   $ra, %hi(D_80129FC8) # $ra, 0x8013
/* 0BB98C 800BAD8C 10000007 */  b     .L800BADAC
/* 0BB990 800BAD90 27FF9FC8 */   addiu $ra, %lo(D_80129FC8) # addiu $ra, $ra, -0x6038
.L800BAD94:
/* 0BB994 800BAD94 86040000 */  lh    $a0, ($s0)
/* 0BB998 800BAD98 8FA50128 */  lw    $a1, 0x128($sp)
/* 0BB99C 800BAD9C 0C02E5EA */  jal   func_800B97A8
/* 0BB9A0 800BADA0 00000000 */   nop   
/* 0BB9A4 800BADA4 3C1F8013 */  lui   $ra, %hi(D_80129FC8) # $ra, 0x8013
/* 0BB9A8 800BADA8 27FF9FC8 */  addiu $ra, %lo(D_80129FC8) # addiu $ra, $ra, -0x6038
.L800BADAC:
/* 0BB9AC 800BADAC 86180000 */  lh    $t8, ($s0)
/* 0BB9B0 800BADB0 3C0E800E */  lui   $t6, %hi(D_800E30D8) # $t6, 0x800e
/* 0BB9B4 800BADB4 0018C8C0 */  sll   $t9, $t8, 3
/* 0BB9B8 800BADB8 8DCE30D8 */  lw    $t6, %lo(D_800E30D8)($t6)
/* 0BB9BC 800BADBC 0338C823 */  subu  $t9, $t9, $t8
/* 0BB9C0 800BADC0 0019C880 */  sll   $t9, $t9, 2
/* 0BB9C4 800BADC4 032E1021 */  addu  $v0, $t9, $t6
/* 0BB9C8 800BADC8 844F0004 */  lh    $t7, 4($v0)
/* 0BB9CC 800BADCC 3C0E800E */  lui   $t6, %hi(D_800E30D4) # $t6, 0x800e
/* 0BB9D0 800BADD0 448F2000 */  mtc1  $t7, $f4
/* 0BB9D4 800BADD4 8DCE30D4 */  lw    $t6, %lo(D_800E30D4)($t6)
/* 0BB9D8 800BADD8 468021A0 */  cvt.s.w $f6, $f4
/* 0BB9DC 800BADDC 3C058013 */  lui   $a1, %hi(D_80129FC4) # $a1, 0x8013
/* 0BB9E0 800BADE0 24A59FC4 */  addiu $a1, %lo(D_80129FC4) # addiu $a1, $a1, -0x603c
/* 0BB9E4 800BADE4 E7A600F0 */  swc1  $f6, 0xf0($sp)
/* 0BB9E8 800BADE8 84580006 */  lh    $t8, 6($v0)
/* 0BB9EC 800BADEC 02202025 */  move  $a0, $s1
/* 0BB9F0 800BADF0 44984000 */  mtc1  $t8, $f8
/* 0BB9F4 800BADF4 27A600E4 */  addiu $a2, $sp, 0xe4
/* 0BB9F8 800BADF8 468042A0 */  cvt.s.w $f10, $f8
/* 0BB9FC 800BADFC E7AA00F4 */  swc1  $f10, 0xf4($sp)
/* 0BBA00 800BAE00 84590008 */  lh    $t9, 8($v0)
/* 0BBA04 800BAE04 00000000 */  nop   
/* 0BBA08 800BAE08 44998000 */  mtc1  $t9, $f16
/* 0BBA0C 800BAE0C 00000000 */  nop   
/* 0BBA10 800BAE10 468084A0 */  cvt.s.w $f18, $f16
/* 0BBA14 800BAE14 E7B200F8 */  swc1  $f18, 0xf8($sp)
/* 0BBA18 800BAE18 8C4F000C */  lw    $t7, 0xc($v0)
/* 0BBA1C 800BAE1C 00000000 */  nop   
/* 0BBA20 800BAE20 000FC080 */  sll   $t8, $t7, 2
/* 0BBA24 800BAE24 01D8C821 */  addu  $t9, $t6, $t8
/* 0BBA28 800BAE28 8F2F0000 */  lw    $t7, ($t9)
/* 0BBA2C 800BAE2C 8FEE0028 */  lw    $t6, 0x28($ra)
/* 0BBA30 800BAE30 AFAF0104 */  sw    $t7, 0x104($sp)
/* 0BBA34 800BAE34 11C000A4 */  beqz  $t6, .L800BB0C8
/* 0BBA38 800BAE38 00000000 */   nop   
/* 0BBA3C 800BAE3C AFA0011C */  sw    $zero, 0x11c($sp)
/* 0BBA40 800BAE40 AFA200E0 */  sw    $v0, 0xe0($sp)
/* 0BBA44 800BAE44 AFB00074 */  sw    $s0, 0x74($sp)
.L800BAE48:
/* 0BBA48 800BAE48 8FA200E0 */  lw    $v0, 0xe0($sp)
/* 0BBA4C 800BAE4C 0000F025 */  move  $fp, $zero
/* 0BBA50 800BAE50 84580004 */  lh    $t8, 4($v0)
/* 0BBA54 800BAE54 00000000 */  nop   
/* 0BBA58 800BAE58 44982000 */  mtc1  $t8, $f4
/* 0BBA5C 800BAE5C 00000000 */  nop   
/* 0BBA60 800BAE60 468021A0 */  cvt.s.w $f6, $f4
/* 0BBA64 800BAE64 E7A600F0 */  swc1  $f6, 0xf0($sp)
.L800BAE68:
/* 0BBA68 800BAE68 3C058013 */  lui   $a1, %hi(D_80129FC4) # $a1, 0x8013
/* 0BBA6C 800BAE6C 4407C000 */  mfc1  $a3, $f24
/* 0BBA70 800BAE70 24A59FC4 */  addiu $a1, %lo(D_80129FC4) # addiu $a1, $a1, -0x603c
/* 0BBA74 800BAE74 02202025 */  move  $a0, $s1
/* 0BBA78 800BAE78 27A600E4 */  addiu $a2, $sp, 0xe4
/* 0BBA7C 800BAE7C 0C01A521 */  jal   camera_push_model_mtx
/* 0BBA80 800BAE80 E7B60010 */   swc1  $f22, 0x10($sp)
/* 0BBA84 800BAE84 8FA50104 */  lw    $a1, 0x104($sp)
/* 0BBA88 800BAE88 3C1F8013 */  lui   $ra, %hi(D_80129FC8) # $ra, 0x8013
/* 0BBA8C 800BAE8C 30B900FF */  andi  $t9, $a1, 0xff
/* 0BBA90 800BAE90 1320004B */  beqz  $t9, .L800BAFC0
/* 0BBA94 800BAE94 27FF9FC8 */   addiu $ra, %lo(D_80129FC8) # addiu $ra, $ra, -0x6038
/* 0BBA98 800BAE98 8FE60000 */  lw    $a2, ($ra)
/* 0BBA9C 800BAE9C 272FFFFF */  addiu $t7, $t9, -1
/* 0BBAA0 800BAEA0 24C30001 */  addiu $v1, $a2, 1
/* 0BBAA4 800BAEA4 01E30019 */  multu $t7, $v1
/* 0BBAA8 800BAEA8 00031040 */  sll   $v0, $v1, 1
/* 0BBAAC 800BAEAC 0002C8C0 */  sll   $t9, $v0, 3
/* 0BBAB0 800BAEB0 03226021 */  addu  $t4, $t9, $v0
/* 0BBAB4 800BAEB4 244BFFFF */  addiu $t3, $v0, -1
/* 0BBAB8 800BAEB8 000BC0C0 */  sll   $t8, $t3, 3
/* 0BBABC 800BAEBC 000C7840 */  sll   $t7, $t4, 1
/* 0BBAC0 800BAEC0 25EC0008 */  addiu $t4, $t7, 8
/* 0BBAC4 800BAEC4 03005825 */  move  $t3, $t8
/* 0BBAC8 800BAEC8 00062040 */  sll   $a0, $a2, 1
/* 0BBACC 800BAECC 2498FFFF */  addiu $t8, $a0, -1
/* 0BBAD0 800BAED0 0018C900 */  sll   $t9, $t8, 4
/* 0BBAD4 800BAED4 00007012 */  mflo  $t6
/* 0BBAD8 800BAED8 372F0001 */  ori   $t7, $t9, 1
/* 0BBADC 800BAEDC 3C010500 */  lui   $at, 0x500
/* 0BBAE0 800BAEE0 01C30019 */  multu $t6, $v1
/* 0BBAE4 800BAEE4 318EFFFF */  andi  $t6, $t4, 0xffff
/* 0BBAE8 800BAEE8 01C06025 */  move  $t4, $t6
/* 0BBAEC 800BAEEC 31EE00FF */  andi  $t6, $t7, 0xff
/* 0BBAF0 800BAEF0 000EC400 */  sll   $t8, $t6, 0x10
/* 0BBAF4 800BAEF4 00047900 */  sll   $t7, $a0, 4
/* 0BBAF8 800BAEF8 31EEFFFF */  andi  $t6, $t7, 0xffff
/* 0BBAFC 800BAEFC 0301C825 */  or    $t9, $t8, $at
/* 0BBB00 800BAF00 032E6825 */  or    $t5, $t9, $t6
/* 0BBB04 800BAF04 00008025 */  move  $s0, $zero
/* 0BBB08 800BAF08 00004012 */  mflo  $t0
/* 0BBB0C 800BAF0C 18C00052 */  blez  $a2, .L800BB058
/* 0BBB10 800BAF10 00000000 */   nop   
.L800BAF14:
/* 0BBB14 800BAF14 01160019 */  multu $t0, $s6
/* 0BBB18 800BAF18 8E780000 */  lw    $t8, ($s3)
/* 0BBB1C 800BAF1C 8FAF0128 */  lw    $t7, 0x128($sp)
/* 0BBB20 800BAF20 8E270000 */  lw    $a3, ($s1)
/* 0BBB24 800BAF24 030F2021 */  addu  $a0, $t8, $t7
/* 0BBB28 800BAF28 0004C880 */  sll   $t9, $a0, 2
/* 0BBB2C 800BAF2C 02B97021 */  addu  $t6, $s5, $t9
/* 0BBB30 800BAF30 8DD80000 */  lw    $t8, ($t6)
/* 0BBB34 800BAF34 02F9C821 */  addu  $t9, $s7, $t9
/* 0BBB38 800BAF38 8F2E0000 */  lw    $t6, ($t9)
/* 0BBB3C 800BAF3C 00007812 */  mflo  $t7
/* 0BBB40 800BAF40 030F4821 */  addu  $t1, $t8, $t7
/* 0BBB44 800BAF44 0006C040 */  sll   $t8, $a2, 1
/* 0BBB48 800BAF48 02180019 */  multu $s0, $t8
/* 0BBB4C 800BAF4C 01322821 */  addu  $a1, $t1, $s2
/* 0BBB50 800BAF50 24F80008 */  addiu $t8, $a3, 8
/* 0BBB54 800BAF54 AE380000 */  sw    $t8, ($s1)
/* 0BBB58 800BAF58 ACE50004 */  sw    $a1, 4($a3)
/* 0BBB5C 800BAF5C 26100001 */  addiu $s0, $s0, 1
/* 0BBB60 800BAF60 00007812 */  mflo  $t7
/* 0BBB64 800BAF64 000FC900 */  sll   $t9, $t7, 4
/* 0BBB68 800BAF68 30AF0006 */  andi  $t7, $a1, 6
/* 0BBB6C 800BAF6C 01D95021 */  addu  $t2, $t6, $t9
/* 0BBB70 800BAF70 016F7025 */  or    $t6, $t3, $t7
/* 0BBB74 800BAF74 31D900FF */  andi  $t9, $t6, 0xff
/* 0BBB78 800BAF78 0019C400 */  sll   $t8, $t9, 0x10
/* 0BBB7C 800BAF7C 03147825 */  or    $t7, $t8, $s4
/* 0BBB80 800BAF80 01EC7025 */  or    $t6, $t7, $t4
/* 0BBB84 800BAF84 ACEE0000 */  sw    $t6, ($a3)
/* 0BBB88 800BAF88 8E270000 */  lw    $a3, ($s1)
/* 0BBB8C 800BAF8C 0152C021 */  addu  $t8, $t2, $s2
/* 0BBB90 800BAF90 24F90008 */  addiu $t9, $a3, 8
/* 0BBB94 800BAF94 AE390000 */  sw    $t9, ($s1)
/* 0BBB98 800BAF98 ACF80004 */  sw    $t8, 4($a3)
/* 0BBB9C 800BAF9C ACED0000 */  sw    $t5, ($a3)
/* 0BBBA0 800BAFA0 8FE60000 */  lw    $a2, ($ra)
/* 0BBBA4 800BAFA4 00000000 */  nop   
/* 0BBBA8 800BAFA8 0206082A */  slt   $at, $s0, $a2
/* 0BBBAC 800BAFAC 01064021 */  addu  $t0, $t0, $a2
/* 0BBBB0 800BAFB0 1420FFD8 */  bnez  $at, .L800BAF14
/* 0BBBB4 800BAFB4 25080001 */   addiu $t0, $t0, 1
/* 0BBBB8 800BAFB8 10000027 */  b     .L800BB058
/* 0BBBBC 800BAFBC 00000000 */   nop   
.L800BAFC0:
/* 0BBBC0 800BAFC0 8E6E0000 */  lw    $t6, ($s3)
/* 0BBBC4 800BAFC4 24050028 */  li    $a1, 40
/* 0BBBC8 800BAFC8 01C50019 */  multu $t6, $a1
/* 0BBBCC 800BAFCC 8E270000 */  lw    $a3, ($s1)
/* 0BBBD0 800BAFD0 3C048013 */  lui   $a0, %hi(D_8012A028) # $a0, 0x8013
/* 0BBBD4 800BAFD4 2484A028 */  addiu $a0, %lo(D_8012A028) # addiu $a0, $a0, -0x5fd8
/* 0BBBD8 800BAFD8 24EF0008 */  addiu $t7, $a3, 8
/* 0BBBDC 800BAFDC AE2F0000 */  sw    $t7, ($s1)
/* 0BBBE0 800BAFE0 0000C812 */  mflo  $t9
/* 0BBBE4 800BAFE4 0099C021 */  addu  $t8, $a0, $t9
/* 0BBBE8 800BAFE8 03127821 */  addu  $t7, $t8, $s2
/* 0BBBEC 800BAFEC 31EE0006 */  andi  $t6, $t7, 6
/* 0BBBF0 800BAFF0 35D90018 */  ori   $t9, $t6, 0x18
/* 0BBBF4 800BAFF4 333800FF */  andi  $t8, $t9, 0xff
/* 0BBBF8 800BAFF8 00187C00 */  sll   $t7, $t8, 0x10
/* 0BBBFC 800BAFFC 01F47025 */  or    $t6, $t7, $s4
/* 0BBC00 800BB000 35D90050 */  ori   $t9, $t6, 0x50
/* 0BBC04 800BB004 ACF90000 */  sw    $t9, ($a3)
/* 0BBC08 800BB008 8E780000 */  lw    $t8, ($s3)
/* 0BBC0C 800BB00C 00000000 */  nop   
/* 0BBC10 800BB010 03050019 */  multu $t8, $a1
/* 0BBC14 800BB014 00007812 */  mflo  $t7
/* 0BBC18 800BB018 008F7021 */  addu  $t6, $a0, $t7
/* 0BBC1C 800BB01C 01D2C821 */  addu  $t9, $t6, $s2
/* 0BBC20 800BB020 ACF90004 */  sw    $t9, 4($a3)
/* 0BBC24 800BB024 8E270000 */  lw    $a3, ($s1)
/* 0BBC28 800BB028 3C0F0511 */  lui   $t7, (0x05110020 >> 16) # lui $t7, 0x511
/* 0BBC2C 800BB02C 24F80008 */  addiu $t8, $a3, 8
/* 0BBC30 800BB030 AE380000 */  sw    $t8, ($s1)
/* 0BBC34 800BB034 35EF0020 */  ori   $t7, (0x05110020 & 0xFFFF) # ori $t7, $t7, 0x20
/* 0BBC38 800BB038 ACEF0000 */  sw    $t7, ($a3)
/* 0BBC3C 800BB03C 8E790000 */  lw    $t9, ($s3)
/* 0BBC40 800BB040 3C0E800E */  lui   $t6, %hi(D_800E3090) # $t6, 0x800e
/* 0BBC44 800BB044 0019C140 */  sll   $t8, $t9, 5
/* 0BBC48 800BB048 03127821 */  addu  $t7, $t8, $s2
/* 0BBC4C 800BB04C 25CE3090 */  addiu $t6, %lo(D_800E3090) # addiu $t6, $t6, 0x3090
/* 0BBC50 800BB050 01EEC821 */  addu  $t9, $t7, $t6
/* 0BBC54 800BB054 ACF90004 */  sw    $t9, 4($a3)
.L800BB058:
/* 0BBC58 800BB058 0C01A690 */  jal   apply_matrix_from_stack
/* 0BBC5C 800BB05C 02202025 */   move  $a0, $s1
/* 0BBC60 800BB060 3C018013 */  lui   $at, %hi(D_8012A0A0) # $at, 0x8013
/* 0BBC64 800BB064 C42AA0A0 */  lwc1  $f10, %lo(D_8012A0A0)($at)
/* 0BBC68 800BB068 8FB80104 */  lw    $t8, 0x104($sp)
/* 0BBC6C 800BB06C 46145402 */  mul.s $f16, $f10, $f20
/* 0BBC70 800BB070 C7A800F0 */  lwc1  $f8, 0xf0($sp)
/* 0BBC74 800BB074 27DE0001 */  addiu $fp, $fp, 1
/* 0BBC78 800BB078 24030002 */  li    $v1, 2
/* 0BBC7C 800BB07C 46104480 */  add.s $f18, $f8, $f16
/* 0BBC80 800BB080 3C1F8013 */  lui   $ra, %hi(D_80129FC8) # $ra, 0x8013
/* 0BBC84 800BB084 00187A03 */  sra   $t7, $t8, 8
/* 0BBC88 800BB088 27FF9FC8 */  addiu $ra, %lo(D_80129FC8) # addiu $ra, $ra, -0x6038
/* 0BBC8C 800BB08C AFAF0104 */  sw    $t7, 0x104($sp)
/* 0BBC90 800BB090 17C3FF75 */  bne   $fp, $v1, .L800BAE68
/* 0BBC94 800BB094 E7B200F0 */   swc1  $f18, 0xf0($sp)
/* 0BBC98 800BB098 3C018013 */  lui   $at, %hi(D_8012A0A4) # $at, 0x8013
/* 0BBC9C 800BB09C C426A0A4 */  lwc1  $f6, %lo(D_8012A0A4)($at)
/* 0BBCA0 800BB0A0 8FA2011C */  lw    $v0, 0x11c($sp)
/* 0BBCA4 800BB0A4 46143282 */  mul.s $f10, $f6, $f20
/* 0BBCA8 800BB0A8 C7A400F8 */  lwc1  $f4, 0xf8($sp)
/* 0BBCAC 800BB0AC 24420001 */  addiu $v0, $v0, 1
/* 0BBCB0 800BB0B0 AFA2011C */  sw    $v0, 0x11c($sp)
/* 0BBCB4 800BB0B4 460A2200 */  add.s $f8, $f4, $f10
/* 0BBCB8 800BB0B8 1443FF63 */  bne   $v0, $v1, .L800BAE48
/* 0BBCBC 800BB0BC E7A800F8 */   swc1  $f8, 0xf8($sp)
/* 0BBCC0 800BB0C0 10000056 */  b     .L800BB21C
/* 0BBCC4 800BB0C4 8FAE00DC */   lw    $t6, 0xdc($sp)
.L800BB0C8:
/* 0BBCC8 800BB0C8 AFB00074 */  sw    $s0, 0x74($sp)
/* 0BBCCC 800BB0CC 4407C000 */  mfc1  $a3, $f24
/* 0BBCD0 800BB0D0 00008025 */  move  $s0, $zero
/* 0BBCD4 800BB0D4 0C01A521 */  jal   camera_push_model_mtx
/* 0BBCD8 800BB0D8 E7B60010 */   swc1  $f22, 0x10($sp)
/* 0BBCDC 800BB0DC 3C1F8013 */  lui   $ra, %hi(D_80129FC8) # $ra, 0x8013
/* 0BBCE0 800BB0E0 8FAE0104 */  lw    $t6, 0x104($sp)
/* 0BBCE4 800BB0E4 27FF9FC8 */  addiu $ra, %lo(D_80129FC8) # addiu $ra, $ra, -0x6038
/* 0BBCE8 800BB0E8 8FE60000 */  lw    $a2, ($ra)
/* 0BBCEC 800BB0EC 31D900FF */  andi  $t9, $t6, 0xff
/* 0BBCF0 800BB0F0 2738FFFF */  addiu $t8, $t9, -1
/* 0BBCF4 800BB0F4 24C30001 */  addiu $v1, $a2, 1
/* 0BBCF8 800BB0F8 03030019 */  multu $t8, $v1
/* 0BBCFC 800BB0FC 00031040 */  sll   $v0, $v1, 1
/* 0BBD00 800BB100 0002C8C0 */  sll   $t9, $v0, 3
/* 0BBD04 800BB104 03226021 */  addu  $t4, $t9, $v0
/* 0BBD08 800BB108 244BFFFF */  addiu $t3, $v0, -1
/* 0BBD0C 800BB10C 000B70C0 */  sll   $t6, $t3, 3
/* 0BBD10 800BB110 000CC040 */  sll   $t8, $t4, 1
/* 0BBD14 800BB114 270C0008 */  addiu $t4, $t8, 8
/* 0BBD18 800BB118 01C05825 */  move  $t3, $t6
/* 0BBD1C 800BB11C 00062040 */  sll   $a0, $a2, 1
/* 0BBD20 800BB120 248EFFFF */  addiu $t6, $a0, -1
/* 0BBD24 800BB124 000EC900 */  sll   $t9, $t6, 4
/* 0BBD28 800BB128 00007812 */  mflo  $t7
/* 0BBD2C 800BB12C 37380001 */  ori   $t8, $t9, 1
/* 0BBD30 800BB130 3C010500 */  lui   $at, 0x500
/* 0BBD34 800BB134 01E30019 */  multu $t7, $v1
/* 0BBD38 800BB138 318FFFFF */  andi  $t7, $t4, 0xffff
/* 0BBD3C 800BB13C 01E06025 */  move  $t4, $t7
/* 0BBD40 800BB140 330F00FF */  andi  $t7, $t8, 0xff
/* 0BBD44 800BB144 000F7400 */  sll   $t6, $t7, 0x10
/* 0BBD48 800BB148 0004C100 */  sll   $t8, $a0, 4
/* 0BBD4C 800BB14C 330FFFFF */  andi  $t7, $t8, 0xffff
/* 0BBD50 800BB150 01C1C825 */  or    $t9, $t6, $at
/* 0BBD54 800BB154 00004012 */  mflo  $t0
/* 0BBD58 800BB158 18C0002B */  blez  $a2, .L800BB208
/* 0BBD5C 800BB15C 00000000 */   nop   
/* 0BBD60 800BB160 8FBE0128 */  lw    $fp, 0x128($sp)
/* 0BBD64 800BB164 032F6825 */  or    $t5, $t9, $t7
.L800BB168:
/* 0BBD68 800BB168 01160019 */  multu $t0, $s6
/* 0BBD6C 800BB16C 8E6E0000 */  lw    $t6, ($s3)
/* 0BBD70 800BB170 8E270000 */  lw    $a3, ($s1)
/* 0BBD74 800BB174 01DE2021 */  addu  $a0, $t6, $fp
/* 0BBD78 800BB178 0004C080 */  sll   $t8, $a0, 2
/* 0BBD7C 800BB17C 02B8C821 */  addu  $t9, $s5, $t8
/* 0BBD80 800BB180 8F2F0000 */  lw    $t7, ($t9)
/* 0BBD84 800BB184 02F8C021 */  addu  $t8, $s7, $t8
/* 0BBD88 800BB188 8F190000 */  lw    $t9, ($t8)
/* 0BBD8C 800BB18C 00007012 */  mflo  $t6
/* 0BBD90 800BB190 01EE4821 */  addu  $t1, $t7, $t6
/* 0BBD94 800BB194 00067840 */  sll   $t7, $a2, 1
/* 0BBD98 800BB198 020F0019 */  multu $s0, $t7
/* 0BBD9C 800BB19C 01322821 */  addu  $a1, $t1, $s2
/* 0BBDA0 800BB1A0 24EF0008 */  addiu $t7, $a3, 8
/* 0BBDA4 800BB1A4 AE2F0000 */  sw    $t7, ($s1)
/* 0BBDA8 800BB1A8 ACE50004 */  sw    $a1, 4($a3)
/* 0BBDAC 800BB1AC 26100001 */  addiu $s0, $s0, 1
/* 0BBDB0 800BB1B0 00007012 */  mflo  $t6
/* 0BBDB4 800BB1B4 000EC100 */  sll   $t8, $t6, 4
/* 0BBDB8 800BB1B8 30AE0006 */  andi  $t6, $a1, 6
/* 0BBDBC 800BB1BC 03385021 */  addu  $t2, $t9, $t8
/* 0BBDC0 800BB1C0 016EC825 */  or    $t9, $t3, $t6
/* 0BBDC4 800BB1C4 333800FF */  andi  $t8, $t9, 0xff
/* 0BBDC8 800BB1C8 00187C00 */  sll   $t7, $t8, 0x10
/* 0BBDCC 800BB1CC 01F47025 */  or    $t6, $t7, $s4
/* 0BBDD0 800BB1D0 01CCC825 */  or    $t9, $t6, $t4
/* 0BBDD4 800BB1D4 ACF90000 */  sw    $t9, ($a3)
/* 0BBDD8 800BB1D8 8E270000 */  lw    $a3, ($s1)
/* 0BBDDC 800BB1DC 01527821 */  addu  $t7, $t2, $s2
/* 0BBDE0 800BB1E0 24F80008 */  addiu $t8, $a3, 8
/* 0BBDE4 800BB1E4 AE380000 */  sw    $t8, ($s1)
/* 0BBDE8 800BB1E8 ACEF0004 */  sw    $t7, 4($a3)
/* 0BBDEC 800BB1EC ACED0000 */  sw    $t5, ($a3)
/* 0BBDF0 800BB1F0 8FE60000 */  lw    $a2, ($ra)
/* 0BBDF4 800BB1F4 00000000 */  nop   
/* 0BBDF8 800BB1F8 0206082A */  slt   $at, $s0, $a2
/* 0BBDFC 800BB1FC 01064021 */  addu  $t0, $t0, $a2
/* 0BBE00 800BB200 1420FFD9 */  bnez  $at, .L800BB168
/* 0BBE04 800BB204 25080001 */   addiu $t0, $t0, 1
.L800BB208:
/* 0BBE08 800BB208 0C01A690 */  jal   apply_matrix_from_stack
/* 0BBE0C 800BB20C 02202025 */   move  $a0, $s1
/* 0BBE10 800BB210 3C1F8013 */  lui   $ra, %hi(D_80129FC8) # $ra, 0x8013
/* 0BBE14 800BB214 27FF9FC8 */  addiu $ra, %lo(D_80129FC8) # addiu $ra, $ra, -0x6038
/* 0BBE18 800BB218 8FAE00DC */  lw    $t6, 0xdc($sp)
.L800BB21C:
/* 0BBE1C 800BB21C 8FB80074 */  lw    $t8, 0x74($sp)
/* 0BBE20 800BB220 25D90001 */  addiu $t9, $t6, 1
/* 0BBE24 800BB224 3C0E800E */  lui   $t6, %hi(D_800E30DC) # $t6, 0x800e
/* 0BBE28 800BB228 8DCE30DC */  lw    $t6, %lo(D_800E30DC)($t6)
/* 0BBE2C 800BB22C 270F0002 */  addiu $t7, $t8, 2
/* 0BBE30 800BB230 032E082A */  slt   $at, $t9, $t6
/* 0BBE34 800BB234 AFAF0074 */  sw    $t7, 0x74($sp)
/* 0BBE38 800BB238 1420FECB */  bnez  $at, .L800BAD68
/* 0BBE3C 800BB23C AFB900DC */   sw    $t9, 0xdc($sp)
.L800BB240:
/* 0BBE40 800BB240 8FF8004C */  lw    $t8, 0x4c($ra)
/* 0BBE44 800BB244 3C19B700 */  lui   $t9, 0xb700
/* 0BBE48 800BB248 1300000E */  beqz  $t8, .L800BB284
/* 0BBE4C 800BB24C 00000000 */   nop   
/* 0BBE50 800BB250 8E270000 */  lw    $a3, ($s1)
/* 0BBE54 800BB254 3C0E0001 */  lui   $t6, 1
/* 0BBE58 800BB258 24EF0008 */  addiu $t7, $a3, 8
/* 0BBE5C 800BB25C AE2F0000 */  sw    $t7, ($s1)
/* 0BBE60 800BB260 ACEE0004 */  sw    $t6, 4($a3)
/* 0BBE64 800BB264 ACF90000 */  sw    $t9, ($a3)
/* 0BBE68 800BB268 8E270000 */  lw    $a3, ($s1)
/* 0BBE6C 800BB26C 2419FFFF */  li    $t9, -1
/* 0BBE70 800BB270 24F80008 */  addiu $t8, $a3, 8
/* 0BBE74 800BB274 AE380000 */  sw    $t8, ($s1)
/* 0BBE78 800BB278 3C0FFA00 */  lui   $t7, 0xfa00
/* 0BBE7C 800BB27C ACEF0000 */  sw    $t7, ($a3)
/* 0BBE80 800BB280 ACF90004 */  sw    $t9, 4($a3)
.L800BB284:
/* 0BBE84 800BB284 8E2E0000 */  lw    $t6, ($s1)
/* 0BBE88 800BB288 8FB80120 */  lw    $t8, 0x120($sp)
/* 0BBE8C 800BB28C 3C0F8013 */  lui   $t7, %hi(D_80129FC4) # $t7, 0x8013
/* 0BBE90 800BB290 AF0E0000 */  sw    $t6, ($t8)
/* 0BBE94 800BB294 8FB90124 */  lw    $t9, 0x124($sp)
/* 0BBE98 800BB298 8DEF9FC4 */  lw    $t7, %lo(D_80129FC4)($t7)
/* 0BBE9C 800BB29C 00000000 */  nop   
/* 0BBEA0 800BB2A0 AF2F0000 */  sw    $t7, ($t9)
.L800BB2A4:
/* 0BBEA4 800BB2A4 8FBF005C */  lw    $ra, 0x5c($sp)
/* 0BBEA8 800BB2A8 3C01800E */  lui   $at, %hi(D_800E30DC) # $at, 0x800e
/* 0BBEAC 800BB2AC C7B50020 */  lwc1  $f21, 0x20($sp)
/* 0BBEB0 800BB2B0 C7B40024 */  lwc1  $f20, 0x24($sp)
/* 0BBEB4 800BB2B4 C7B70028 */  lwc1  $f23, 0x28($sp)
/* 0BBEB8 800BB2B8 C7B6002C */  lwc1  $f22, 0x2c($sp)
/* 0BBEBC 800BB2BC C7B90030 */  lwc1  $f25, 0x30($sp)
/* 0BBEC0 800BB2C0 C7B80034 */  lwc1  $f24, 0x34($sp)
/* 0BBEC4 800BB2C4 8FB00038 */  lw    $s0, 0x38($sp)
/* 0BBEC8 800BB2C8 8FB1003C */  lw    $s1, 0x3c($sp)
/* 0BBECC 800BB2CC 8FB20040 */  lw    $s2, 0x40($sp)
/* 0BBED0 800BB2D0 8FB30044 */  lw    $s3, 0x44($sp)
/* 0BBED4 800BB2D4 8FB40048 */  lw    $s4, 0x48($sp)
/* 0BBED8 800BB2D8 8FB5004C */  lw    $s5, 0x4c($sp)
/* 0BBEDC 800BB2DC 8FB60050 */  lw    $s6, 0x50($sp)
/* 0BBEE0 800BB2E0 8FB70054 */  lw    $s7, 0x54($sp)
/* 0BBEE4 800BB2E4 8FBE0058 */  lw    $fp, 0x58($sp)
/* 0BBEE8 800BB2E8 AC2030DC */  sw    $zero, %lo(D_800E30DC)($at)
/* 0BBEEC 800BB2EC 03E00008 */  jr    $ra
/* 0BBEF0 800BB2F0 27BD0120 */   addiu $sp, $sp, 0x120

