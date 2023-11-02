glabel func_800ACA20
/* 0AD620 800ACA20 27BDFF10 */  addiu $sp, $sp, -0xf0
/* 0AD624 800ACA24 AFB60050 */  sw    $s6, 0x50($sp)
/* 0AD628 800ACA28 3C16800E */  lui   $s6, %hi(D_800E2A80) # $s6, 0x800e
/* 0AD62C 800ACA2C 26D62A80 */  addiu $s6, %lo(D_800E2A80) # addiu $s6, $s6, 0x2a80
/* 0AD630 800ACA30 8ECF0000 */  lw    $t7, ($s6)
/* 0AD634 800ACA34 AFB70054 */  sw    $s7, 0x54($sp)
/* 0AD638 800ACA38 AFB5004C */  sw    $s5, 0x4c($sp)
/* 0AD63C 800ACA3C AFB1003C */  sw    $s1, 0x3c($sp)
/* 0AD640 800ACA40 AFB00038 */  sw    $s0, 0x38($sp)
/* 0AD644 800ACA44 00E08025 */  move  $s0, $a3
/* 0AD648 800ACA48 00808825 */  move  $s1, $a0
/* 0AD64C 800ACA4C 00A0A825 */  move  $s5, $a1
/* 0AD650 800ACA50 00C0B825 */  move  $s7, $a2
/* 0AD654 800ACA54 AFBF005C */  sw    $ra, 0x5c($sp)
/* 0AD658 800ACA58 AFBE0058 */  sw    $fp, 0x58($sp)
/* 0AD65C 800ACA5C AFB40048 */  sw    $s4, 0x48($sp)
/* 0AD660 800ACA60 AFB30044 */  sw    $s3, 0x44($sp)
/* 0AD664 800ACA64 AFB20040 */  sw    $s2, 0x40($sp)
/* 0AD668 800ACA68 E7B90030 */  swc1  $f25, 0x30($sp)
/* 0AD66C 800ACA6C E7B80034 */  swc1  $f24, 0x34($sp)
/* 0AD670 800ACA70 E7B70028 */  swc1  $f23, 0x28($sp)
/* 0AD674 800ACA74 E7B6002C */  swc1  $f22, 0x2c($sp)
/* 0AD678 800ACA78 E7B50020 */  swc1  $f21, 0x20($sp)
/* 0AD67C 800ACA7C 11E00126 */  beqz  $t7, .L800ACF18
/* 0AD680 800ACA80 E7B40024 */   swc1  $f20, 0x24($sp)
/* 0AD684 800ACA84 3C19800E */  lui   $t9, %hi(D_800E2A84) # $t9, 0x800e
/* 0AD688 800ACA88 8F392A84 */  lw    $t9, %lo(D_800E2A84)($t9)
/* 0AD68C 800ACA8C 00000000 */  nop   
/* 0AD690 800ACA90 17200122 */  bnez  $t9, .L800ACF1C
/* 0AD694 800ACA94 8FBF005C */   lw    $ra, 0x5c($sp)
/* 0AD698 800ACA98 0C019884 */  jal   get_viewport_count
/* 0AD69C 800ACA9C 00000000 */   nop   
/* 0AD6A0 800ACAA0 1440011D */  bnez  $v0, .L800ACF18
/* 0AD6A4 800ACAA4 3C01BF80 */   li    $at, 0xBF800000 # -1.000000
/* 0AD6A8 800ACAA8 8ECE0000 */  lw    $t6, ($s6)
/* 0AD6AC 800ACAAC 4480A000 */  mtc1  $zero, $f20
/* 0AD6B0 800ACAB0 8DCB003C */  lw    $t3, 0x3c($t6)
/* 0AD6B4 800ACAB4 44815000 */  mtc1  $at, $f10
/* 0AD6B8 800ACAB8 E7B400D8 */  swc1  $f20, 0xd8($sp)
/* 0AD6BC 800ACABC E7B400DC */  swc1  $f20, 0xdc($sp)
/* 0AD6C0 800ACAC0 AFAB0098 */  sw    $t3, 0x98($sp)
/* 0AD6C4 800ACAC4 0C01A769 */  jal   get_projection_matrix_f32
/* 0AD6C8 800ACAC8 E7AA00E0 */   swc1  $f10, 0xe0($sp)
/* 0AD6CC 800ACACC 27A500D8 */  addiu $a1, $sp, 0xd8
/* 0AD6D0 800ACAD0 00A03025 */  move  $a2, $a1
/* 0AD6D4 800ACAD4 0C01BDBB */  jal   f32_matrix_dot
/* 0AD6D8 800ACAD8 00402025 */   move  $a0, $v0
/* 0AD6DC 800ACADC 3C1E8012 */  lui   $fp, %hi(D_80127C30) # $fp, 0x8012
/* 0AD6E0 800ACAE0 27DE7C30 */  addiu $fp, %lo(D_80127C30) # addiu $fp, $fp, 0x7c30
/* 0AD6E4 800ACAE4 C7C60000 */  lwc1  $f6, ($fp)
/* 0AD6E8 800ACAE8 C7A400D8 */  lwc1  $f4, 0xd8($sp)
/* 0AD6EC 800ACAEC C7CA0004 */  lwc1  $f10, 4($fp)
/* 0AD6F0 800ACAF0 46043202 */  mul.s $f8, $f6, $f4
/* 0AD6F4 800ACAF4 C7A600DC */  lwc1  $f6, 0xdc($sp)
/* 0AD6F8 800ACAF8 02202025 */  move  $a0, $s1
/* 0AD6FC 800ACAFC 02A02825 */  move  $a1, $s5
/* 0AD700 800ACB00 46065102 */  mul.s $f4, $f10, $f6
/* 0AD704 800ACB04 C7A600E0 */  lwc1  $f6, 0xe0($sp)
/* 0AD708 800ACB08 46044280 */  add.s $f10, $f8, $f4
/* 0AD70C 800ACB0C C7C80008 */  lwc1  $f8, 8($fp)
/* 0AD710 800ACB10 00000000 */  nop   
/* 0AD714 800ACB14 46083102 */  mul.s $f4, $f6, $f8
/* 0AD718 800ACB18 460A2480 */  add.s $f18, $f4, $f10
/* 0AD71C 800ACB1C 4612A03C */  c.lt.s $f20, $f18
/* 0AD720 800ACB20 00000000 */  nop   
/* 0AD724 800ACB24 450000FD */  bc1f  .L800ACF1C
/* 0AD728 800ACB28 8FBF005C */   lw    $ra, 0x5c($sp)
/* 0AD72C 800ACB2C 0C019B37 */  jal   func_80066CDC
/* 0AD730 800ACB30 E7B200C8 */   swc1  $f18, 0xc8($sp)
/* 0AD734 800ACB34 02202025 */  move  $a0, $s1
/* 0AD738 800ACB38 0C01A102 */  jal   matrix_world_origin
/* 0AD73C 800ACB3C 02A02825 */   move  $a1, $s5
/* 0AD740 800ACB40 3C014000 */  li    $at, 0x40000000 # 2.000000
/* 0AD744 800ACB44 4481C000 */  mtc1  $at, $f24
/* 0AD748 800ACB48 3C014380 */  li    $at, 0x43800000 # 256.000000
/* 0AD74C 800ACB4C 44813000 */  mtc1  $at, $f6
/* 0AD750 800ACB50 C7CC0000 */  lwc1  $f12, ($fp)
/* 0AD754 800ACB54 C604000C */  lwc1  $f4, 0xc($s0)
/* 0AD758 800ACB58 46066202 */  mul.s $f8, $f12, $f6
/* 0AD75C 800ACB5C 44813000 */  mtc1  $at, $f6
/* 0AD760 800ACB60 C7CE0004 */  lwc1  $f14, 4($fp)
/* 0AD764 800ACB64 C7C20008 */  lwc1  $f2, 8($fp)
/* 0AD768 800ACB68 46044280 */  add.s $f10, $f8, $f4
/* 0AD76C 800ACB6C C7B200C8 */  lwc1  $f18, 0xc8($sp)
/* 0AD770 800ACB70 46067202 */  mul.s $f8, $f14, $f6
/* 0AD774 800ACB74 E7AA00CC */  swc1  $f10, 0xcc($sp)
/* 0AD778 800ACB78 C6040010 */  lwc1  $f4, 0x10($s0)
/* 0AD77C 800ACB7C 44813000 */  mtc1  $at, $f6
/* 0AD780 800ACB80 46044280 */  add.s $f10, $f8, $f4
/* 0AD784 800ACB84 00009025 */  move  $s2, $zero
/* 0AD788 800ACB88 46061202 */  mul.s $f8, $f2, $f6
/* 0AD78C 800ACB8C E7AA00D0 */  swc1  $f10, 0xd0($sp)
/* 0AD790 800ACB90 C6040014 */  lwc1  $f4, 0x14($s0)
/* 0AD794 800ACB94 C7A600D8 */  lwc1  $f6, 0xd8($sp)
/* 0AD798 800ACB98 46129502 */  mul.s $f20, $f18, $f18
/* 0AD79C 800ACB9C 46044280 */  add.s $f10, $f8, $f4
/* 0AD7A0 800ACBA0 A7A000A4 */  sh    $zero, 0xa4($sp)
/* 0AD7A4 800ACBA4 E7AA00D4 */  swc1  $f10, 0xd4($sp)
/* 0AD7A8 800ACBA8 4614A582 */  mul.s $f22, $f20, $f20
/* 0AD7AC 800ACBAC C7AA00DC */  lwc1  $f10, 0xdc($sp)
/* 0AD7B0 800ACBB0 A7A000A6 */  sh    $zero, 0xa6($sp)
/* 0AD7B4 800ACBB4 A7A000A8 */  sh    $zero, 0xa8($sp)
/* 0AD7B8 800ACBB8 4612C402 */  mul.s $f16, $f24, $f18
/* 0AD7BC 800ACBBC 3C14FA00 */  lui   $s4, 0xfa00
/* 0AD7C0 800ACBC0 27B300A4 */  addiu $s3, $sp, 0xa4
/* 0AD7C4 800ACBC4 24020001 */  li    $v0, 1
/* 0AD7C8 800ACBC8 46068202 */  mul.s $f8, $f16, $f6
/* 0AD7CC 800ACBCC 460C4101 */  sub.s $f4, $f8, $f12
/* 0AD7D0 800ACBD0 460A8182 */  mul.s $f6, $f16, $f10
/* 0AD7D4 800ACBD4 E7A400D8 */  swc1  $f4, 0xd8($sp)
/* 0AD7D8 800ACBD8 C7A400E0 */  lwc1  $f4, 0xe0($sp)
/* 0AD7DC 800ACBDC 00000000 */  nop   
/* 0AD7E0 800ACBE0 46048282 */  mul.s $f10, $f16, $f4
/* 0AD7E4 800ACBE4 460E3201 */  sub.s $f8, $f6, $f14
/* 0AD7E8 800ACBE8 E7A800DC */  swc1  $f8, 0xdc($sp)
/* 0AD7EC 800ACBEC 46025181 */  sub.s $f6, $f10, $f2
/* 0AD7F0 800ACBF0 E7A600E0 */  swc1  $f6, 0xe0($sp)
.L800ACBF4:
/* 0AD7F4 800ACBF4 16400004 */  bnez  $s2, .L800ACC08
/* 0AD7F8 800ACBF8 3C108012 */   lui   $s0, %hi(D_80127C2C) # $s0, 0x8012
/* 0AD7FC 800ACBFC 8E107C2C */  lw    $s0, %lo(D_80127C2C)($s0)
/* 0AD800 800ACC00 10000009 */  b     .L800ACC28
/* 0AD804 800ACC04 00000000 */   nop   
.L800ACC08:
/* 0AD808 800ACC08 16420005 */  bne   $s2, $v0, .L800ACC20
/* 0AD80C 800ACC0C 3C108012 */   lui   $s0, %hi(D_80127C28) # $s0, 0x8012
/* 0AD810 800ACC10 3C108012 */  lui   $s0, %hi(D_80127C24) # $s0, 0x8012
/* 0AD814 800ACC14 8E107C24 */  lw    $s0, %lo(D_80127C24)($s0)
/* 0AD818 800ACC18 10000003 */  b     .L800ACC28
/* 0AD81C 800ACC1C 00000000 */   nop   
.L800ACC20:
/* 0AD820 800ACC20 8E107C28 */  lw    $s0, %lo(D_80127C28)($s0)
/* 0AD824 800ACC24 00000000 */  nop   
.L800ACC28:
/* 0AD828 800ACC28 12000058 */  beqz  $s0, .L800ACD8C
/* 0AD82C 800ACC2C 00000000 */   nop   
/* 0AD830 800ACC30 8E0D0000 */  lw    $t5, ($s0)
/* 0AD834 800ACC34 00000000 */  nop   
/* 0AD838 800ACC38 19A00054 */  blez  $t5, .L800ACD8C
/* 0AD83C 800ACC3C 00000000 */   nop   
.L800ACC40:
/* 0AD840 800ACC40 C7A800CC */  lwc1  $f8, 0xcc($sp)
/* 0AD844 800ACC44 C7A400D0 */  lwc1  $f4, 0xd0($sp)
/* 0AD848 800ACC48 C7AA00D4 */  lwc1  $f10, 0xd4($sp)
/* 0AD84C 800ACC4C E7A800B0 */  swc1  $f8, 0xb0($sp)
/* 0AD850 800ACC50 E7A400B4 */  swc1  $f4, 0xb4($sp)
/* 0AD854 800ACC54 12400016 */  beqz  $s2, .L800ACCB0
/* 0AD858 800ACC58 E7AA00B8 */   swc1  $f10, 0xb8($sp)
/* 0AD85C 800ACC5C C606000C */  lwc1  $f6, 0xc($s0)
/* 0AD860 800ACC60 E7A80060 */  swc1  $f8, 0x60($sp)
/* 0AD864 800ACC64 C7A800D8 */  lwc1  $f8, 0xd8($sp)
/* 0AD868 800ACC68 00000000 */  nop   
/* 0AD86C 800ACC6C 46083182 */  mul.s $f6, $f6, $f8
/* 0AD870 800ACC70 C7A80060 */  lwc1  $f8, 0x60($sp)
/* 0AD874 800ACC74 00000000 */  nop   
/* 0AD878 800ACC78 46064200 */  add.s $f8, $f8, $f6
/* 0AD87C 800ACC7C E7A800B0 */  swc1  $f8, 0xb0($sp)
/* 0AD880 800ACC80 C606000C */  lwc1  $f6, 0xc($s0)
/* 0AD884 800ACC84 C7A800DC */  lwc1  $f8, 0xdc($sp)
/* 0AD888 800ACC88 00000000 */  nop   
/* 0AD88C 800ACC8C 46083182 */  mul.s $f6, $f6, $f8
/* 0AD890 800ACC90 46062200 */  add.s $f8, $f4, $f6
/* 0AD894 800ACC94 C7A600E0 */  lwc1  $f6, 0xe0($sp)
/* 0AD898 800ACC98 E7A800B4 */  swc1  $f8, 0xb4($sp)
/* 0AD89C 800ACC9C C604000C */  lwc1  $f4, 0xc($s0)
/* 0AD8A0 800ACCA0 00000000 */  nop   
/* 0AD8A4 800ACCA4 46062202 */  mul.s $f8, $f4, $f6
/* 0AD8A8 800ACCA8 46085100 */  add.s $f4, $f10, $f8
/* 0AD8AC 800ACCAC E7A400B8 */  swc1  $f4, 0xb8($sp)
.L800ACCB0:
/* 0AD8B0 800ACCB0 C6060008 */  lwc1  $f6, 8($s0)
/* 0AD8B4 800ACCB4 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0AD8B8 800ACCB8 46143282 */  mul.s $f10, $f6, $f20
/* 0AD8BC 800ACCBC E7AA00AC */  swc1  $f10, 0xac($sp)
/* 0AD8C0 800ACCC0 8E220000 */  lw    $v0, ($s1)
/* 0AD8C4 800ACCC4 00000000 */  nop   
/* 0AD8C8 800ACCC8 24580008 */  addiu $t8, $v0, 8
/* 0AD8CC 800ACCCC AE380000 */  sw    $t8, ($s1)
/* 0AD8D0 800ACCD0 AC540000 */  sw    $s4, ($v0)
/* 0AD8D4 800ACCD4 920B0005 */  lbu   $t3, 5($s0)
/* 0AD8D8 800ACCD8 920F0004 */  lbu   $t7, 4($s0)
/* 0AD8DC 800ACCDC 000B6C00 */  sll   $t5, $t3, 0x10
/* 0AD8E0 800ACCE0 000FCE00 */  sll   $t9, $t7, 0x18
/* 0AD8E4 800ACCE4 032DC025 */  or    $t8, $t9, $t5
/* 0AD8E8 800ACCE8 92190007 */  lbu   $t9, 7($s0)
/* 0AD8EC 800ACCEC 920F0006 */  lbu   $t7, 6($s0)
/* 0AD8F0 800ACCF0 44994000 */  mtc1  $t9, $f8
/* 0AD8F4 800ACCF4 000F7200 */  sll   $t6, $t7, 8
/* 0AD8F8 800ACCF8 030E5825 */  or    $t3, $t8, $t6
/* 0AD8FC 800ACCFC 07210004 */  bgez  $t9, .L800ACD10
/* 0AD900 800ACD00 46804120 */   cvt.s.w $f4, $f8
/* 0AD904 800ACD04 44813000 */  mtc1  $at, $f6
/* 0AD908 800ACD08 00000000 */  nop   
/* 0AD90C 800ACD0C 46062100 */  add.s $f4, $f4, $f6
.L800ACD10:
/* 0AD910 800ACD10 46162282 */  mul.s $f10, $f4, $f22
/* 0AD914 800ACD14 02202025 */  move  $a0, $s1
/* 0AD918 800ACD18 02A02825 */  move  $a1, $s5
/* 0AD91C 800ACD1C 02E03025 */  move  $a2, $s7
/* 0AD920 800ACD20 444DF800 */  cfc1  $t5, $31
/* 0AD924 800ACD24 02603825 */  move  $a3, $s3
/* 0AD928 800ACD28 35A10003 */  ori   $at, $t5, 3
/* 0AD92C 800ACD2C 38210002 */  xori  $at, $at, 2
/* 0AD930 800ACD30 44C1F800 */  ctc1  $at, $31
/* 0AD934 800ACD34 00000000 */  nop   
/* 0AD938 800ACD38 46005224 */  cvt.w.s $f8, $f10
/* 0AD93C 800ACD3C 440C4000 */  mfc1  $t4, $f8
/* 0AD940 800ACD40 44CDF800 */  ctc1  $t5, $31
/* 0AD944 800ACD44 318F00FF */  andi  $t7, $t4, 0xff
/* 0AD948 800ACD48 016FC025 */  or    $t8, $t3, $t7
/* 0AD94C 800ACD4C AC580004 */  sw    $t8, 4($v0)
/* 0AD950 800ACD50 8ECE0000 */  lw    $t6, ($s6)
/* 0AD954 800ACD54 8E0D0000 */  lw    $t5, ($s0)
/* 0AD958 800ACD58 8DD90068 */  lw    $t9, 0x68($t6)
/* 0AD95C 800ACD5C 000D6080 */  sll   $t4, $t5, 2
/* 0AD960 800ACD60 032C5821 */  addu  $t3, $t9, $t4
/* 0AD964 800ACD64 8D6F0000 */  lw    $t7, ($t3)
/* 0AD968 800ACD68 24180104 */  li    $t8, 260
/* 0AD96C 800ACD6C AFB80014 */  sw    $t8, 0x14($sp)
/* 0AD970 800ACD70 0C01A145 */  jal   render_sprite_billboard
/* 0AD974 800ACD74 AFAF0010 */   sw    $t7, 0x10($sp)
/* 0AD978 800ACD78 8E0E0010 */  lw    $t6, 0x10($s0)
/* 0AD97C 800ACD7C 26100010 */  addiu $s0, $s0, 0x10
/* 0AD980 800ACD80 1DC0FFAF */  bgtz  $t6, .L800ACC40
/* 0AD984 800ACD84 00000000 */   nop   
/* 0AD988 800ACD88 24020001 */  li    $v0, 1
.L800ACD8C:
/* 0AD98C 800ACD8C 16420019 */  bne   $s2, $v0, .L800ACDF4
/* 0AD990 800ACD90 24010003 */   li    $at, 3
/* 0AD994 800ACD94 C7CC0000 */  lwc1  $f12, ($fp)
/* 0AD998 800ACD98 C7A600D8 */  lwc1  $f6, 0xd8($sp)
/* 0AD99C 800ACD9C C7CE0004 */  lwc1  $f14, 4($fp)
/* 0AD9A0 800ACDA0 460C3102 */  mul.s $f4, $f6, $f12
/* 0AD9A4 800ACDA4 C7AA00DC */  lwc1  $f10, 0xdc($sp)
/* 0AD9A8 800ACDA8 C7C20008 */  lwc1  $f2, 8($fp)
/* 0AD9AC 800ACDAC E7A60060 */  swc1  $f6, 0x60($sp)
/* 0AD9B0 800ACDB0 460E5202 */  mul.s $f8, $f10, $f14
/* 0AD9B4 800ACDB4 46082100 */  add.s $f4, $f4, $f8
/* 0AD9B8 800ACDB8 C7A800E0 */  lwc1  $f8, 0xe0($sp)
/* 0AD9BC 800ACDBC 00000000 */  nop   
/* 0AD9C0 800ACDC0 46081182 */  mul.s $f6, $f2, $f8
/* 0AD9C4 800ACDC4 46043180 */  add.s $f6, $f6, $f4
/* 0AD9C8 800ACDC8 46183002 */  mul.s $f0, $f6, $f24
/* 0AD9CC 800ACDCC C7A60060 */  lwc1  $f6, 0x60($sp)
/* 0AD9D0 800ACDD0 460C0102 */  mul.s $f4, $f0, $f12
/* 0AD9D4 800ACDD4 46062101 */  sub.s $f4, $f4, $f6
/* 0AD9D8 800ACDD8 460E0182 */  mul.s $f6, $f0, $f14
/* 0AD9DC 800ACDDC E7A400D8 */  swc1  $f4, 0xd8($sp)
/* 0AD9E0 800ACDE0 460A3101 */  sub.s $f4, $f6, $f10
/* 0AD9E4 800ACDE4 46020182 */  mul.s $f6, $f0, $f2
/* 0AD9E8 800ACDE8 E7A400DC */  swc1  $f4, 0xdc($sp)
/* 0AD9EC 800ACDEC 46083281 */  sub.s $f10, $f6, $f8
/* 0AD9F0 800ACDF0 E7AA00E0 */  swc1  $f10, 0xe0($sp)
.L800ACDF4:
/* 0AD9F4 800ACDF4 26520001 */  addiu $s2, $s2, 1
/* 0AD9F8 800ACDF8 1641FF7E */  bne   $s2, $at, .L800ACBF4
/* 0AD9FC 800ACDFC 00000000 */   nop   
/* 0ADA00 800ACE00 0C01E948 */  jal   get_video_width_and_height_as_s32
/* 0ADA04 800ACE04 00000000 */   nop   
/* 0ADA08 800ACE08 8E230000 */  lw    $v1, ($s1)
/* 0ADA0C 800ACE0C 8FAA0098 */  lw    $t2, 0x98($sp)
/* 0ADA10 800ACE10 00602025 */  move  $a0, $v1
/* 0ADA14 800ACE14 3C0C800E */  lui   $t4, %hi(D_800E2928) # $t4, 0x800e
/* 0ADA18 800ACE18 258C2928 */  addiu $t4, %lo(D_800E2928) # addiu $t4, $t4, 0x2928
/* 0ADA1C 800ACE1C 3C190600 */  lui   $t9, 0x600
/* 0ADA20 800ACE20 24630008 */  addiu $v1, $v1, 8
/* 0ADA24 800ACE24 00024403 */  sra   $t0, $v0, 0x10
/* 0ADA28 800ACE28 AC990000 */  sw    $t9, ($a0)
/* 0ADA2C 800ACE2C AC8C0004 */  sw    $t4, 4($a0)
/* 0ADA30 800ACE30 00602825 */  move  $a1, $v1
/* 0ADA34 800ACE34 310DFFFF */  andi  $t5, $t0, 0xffff
/* 0ADA38 800ACE38 ACB40000 */  sw    $s4, ($a1)
/* 0ADA3C 800ACE3C 01A04025 */  move  $t0, $t5
/* 0ADA40 800ACE40 914D0011 */  lbu   $t5, 0x11($t2)
/* 0ADA44 800ACE44 914F0010 */  lbu   $t7, 0x10($t2)
/* 0ADA48 800ACE48 000DCC00 */  sll   $t9, $t5, 0x10
/* 0ADA4C 800ACE4C 000FC600 */  sll   $t8, $t7, 0x18
/* 0ADA50 800ACE50 03196025 */  or    $t4, $t8, $t9
/* 0ADA54 800ACE54 91580013 */  lbu   $t8, 0x13($t2)
/* 0ADA58 800ACE58 914F0012 */  lbu   $t7, 0x12($t2)
/* 0ADA5C 800ACE5C 44982000 */  mtc1  $t8, $f4
/* 0ADA60 800ACE60 000F7200 */  sll   $t6, $t7, 8
/* 0ADA64 800ACE64 3049FFFF */  andi  $t1, $v0, 0xffff
/* 0ADA68 800ACE68 018E6825 */  or    $t5, $t4, $t6
/* 0ADA6C 800ACE6C 24630008 */  addiu $v1, $v1, 8
/* 0ADA70 800ACE70 07010005 */  bgez  $t8, .L800ACE88
/* 0ADA74 800ACE74 468021A0 */   cvt.s.w $f6, $f4
/* 0ADA78 800ACE78 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0ADA7C 800ACE7C 44814000 */  mtc1  $at, $f8
/* 0ADA80 800ACE80 00000000 */  nop   
/* 0ADA84 800ACE84 46083180 */  add.s $f6, $f6, $f8
.L800ACE88:
/* 0ADA88 800ACE88 46163282 */  mul.s $f10, $f6, $f22
/* 0ADA8C 800ACE8C 00603025 */  move  $a2, $v1
/* 0ADA90 800ACE90 3C0EFCFF */  lui   $t6, (0xFCFFFFFF >> 16) # lui $t6, 0xfcff
/* 0ADA94 800ACE94 3C18FFFD */  lui   $t8, (0xFFFDF6FB >> 16) # lui $t8, 0xfffd
/* 0ADA98 800ACE98 4459F800 */  cfc1  $t9, $31
/* 0ADA9C 800ACE9C 3718F6FB */  ori   $t8, (0xFFFDF6FB & 0xFFFF) # ori $t8, $t8, 0xf6fb
/* 0ADAA0 800ACEA0 37210003 */  ori   $at, $t9, 3
/* 0ADAA4 800ACEA4 38210002 */  xori  $at, $at, 2
/* 0ADAA8 800ACEA8 44C1F800 */  ctc1  $at, $31
/* 0ADAAC 800ACEAC 35CEFFFF */  ori   $t6, (0xFCFFFFFF & 0xFFFF) # ori $t6, $t6, 0xffff
/* 0ADAB0 800ACEB0 46005124 */  cvt.w.s $f4, $f10
/* 0ADAB4 800ACEB4 24670008 */  addiu $a3, $v1, 8
/* 0ADAB8 800ACEB8 440B2000 */  mfc1  $t3, $f4
/* 0ADABC 800ACEBC 44D9F800 */  ctc1  $t9, $31
/* 0ADAC0 800ACEC0 316F00FF */  andi  $t7, $t3, 0xff
/* 0ADAC4 800ACEC4 01AF6025 */  or    $t4, $t5, $t7
/* 0ADAC8 800ACEC8 ACAC0004 */  sw    $t4, 4($a1)
/* 0ADACC 800ACECC 313903FF */  andi  $t9, $t1, 0x3ff
/* 0ADAD0 800ACED0 ACD80004 */  sw    $t8, 4($a2)
/* 0ADAD4 800ACED4 ACCE0000 */  sw    $t6, ($a2)
/* 0ADAD8 800ACED8 00195B80 */  sll   $t3, $t9, 0xe
/* 0ADADC 800ACEDC 310F03FF */  andi  $t7, $t0, 0x3ff
/* 0ADAE0 800ACEE0 3C01F600 */  lui   $at, 0xf600
/* 0ADAE4 800ACEE4 01616825 */  or    $t5, $t3, $at
/* 0ADAE8 800ACEE8 000F6080 */  sll   $t4, $t7, 2
/* 0ADAEC 800ACEEC 01AC7025 */  or    $t6, $t5, $t4
/* 0ADAF0 800ACEF0 24E20008 */  addiu $v0, $a3, 8
/* 0ADAF4 800ACEF4 ACEE0000 */  sw    $t6, ($a3)
/* 0ADAF8 800ACEF8 ACE00004 */  sw    $zero, 4($a3)
/* 0ADAFC 800ACEFC 3C18E700 */  lui   $t8, 0xe700
/* 0ADB00 800ACF00 AC580000 */  sw    $t8, ($v0)
/* 0ADB04 800ACF04 AC400004 */  sw    $zero, 4($v0)
/* 0ADB08 800ACF08 24430008 */  addiu $v1, $v0, 8
/* 0ADB0C 800ACF0C AE230000 */  sw    $v1, ($s1)
/* 0ADB10 800ACF10 0C01ECF4 */  jal   reset_render_settings
/* 0ADB14 800ACF14 02202025 */   move  $a0, $s1
.L800ACF18:
/* 0ADB18 800ACF18 8FBF005C */  lw    $ra, 0x5c($sp)
.L800ACF1C:
/* 0ADB1C 800ACF1C C7B50020 */  lwc1  $f21, 0x20($sp)
/* 0ADB20 800ACF20 C7B40024 */  lwc1  $f20, 0x24($sp)
/* 0ADB24 800ACF24 C7B70028 */  lwc1  $f23, 0x28($sp)
/* 0ADB28 800ACF28 C7B6002C */  lwc1  $f22, 0x2c($sp)
/* 0ADB2C 800ACF2C C7B90030 */  lwc1  $f25, 0x30($sp)
/* 0ADB30 800ACF30 C7B80034 */  lwc1  $f24, 0x34($sp)
/* 0ADB34 800ACF34 8FB00038 */  lw    $s0, 0x38($sp)
/* 0ADB38 800ACF38 8FB1003C */  lw    $s1, 0x3c($sp)
/* 0ADB3C 800ACF3C 8FB20040 */  lw    $s2, 0x40($sp)
/* 0ADB40 800ACF40 8FB30044 */  lw    $s3, 0x44($sp)
/* 0ADB44 800ACF44 8FB40048 */  lw    $s4, 0x48($sp)
/* 0ADB48 800ACF48 8FB5004C */  lw    $s5, 0x4c($sp)
/* 0ADB4C 800ACF4C 8FB60050 */  lw    $s6, 0x50($sp)
/* 0ADB50 800ACF50 8FB70054 */  lw    $s7, 0x54($sp)
/* 0ADB54 800ACF54 8FBE0058 */  lw    $fp, 0x58($sp)
/* 0ADB58 800ACF58 03E00008 */  jr    $ra
/* 0ADB5C 800ACF5C 27BD00F0 */   addiu $sp, $sp, 0xf0

