glabel sinf
/* 0D5820 800D4C20 E7AC0000 */  swc1  $f12, ($sp)
/* 0D5824 800D4C24 8FA20000 */  lw    $v0, ($sp)
/* 0D5828 800D4C28 C7A40000 */  lwc1  $f4, ($sp)
/* 0D582C 800D4C2C 00021D83 */  sra   $v1, $v0, 0x16
/* 0D5830 800D4C30 306E01FF */  andi  $t6, $v1, 0x1ff
/* 0D5834 800D4C34 29C100FF */  slti  $at, $t6, 0xff
/* 0D5838 800D4C38 10200019 */  beqz  $at, .L800D4CA0
/* 0D583C 800D4C3C 01C01825 */   move  $v1, $t6
/* 0D5840 800D4C40 29C100E6 */  slti  $at, $t6, 0xe6
/* 0D5844 800D4C44 14200014 */  bnez  $at, .L800D4C98
/* 0D5848 800D4C48 460020A1 */   cvt.d.s $f2, $f4
/* 0D584C 800D4C4C 46221302 */  mul.d $f12, $f2, $f2
/* 0D5850 800D4C50 3C03800F */  lui   $v1, %hi(P_sinf) # $v1, 0x800f
/* 0D5854 800D4C54 24639810 */  addiu $v1, %lo(P_sinf) # addiu $v1, $v1, -0x67f0
/* 0D5858 800D4C58 D4660020 */  ldc1  $f6, 0x20($v1)
/* 0D585C 800D4C5C D46A0018 */  ldc1  $f10, 0x18($v1)
/* 0D5860 800D4C60 D4640010 */  ldc1  $f4, 0x10($v1)
/* 0D5864 800D4C64 462C3202 */  mul.d $f8, $f6, $f12
/* 0D5868 800D4C68 462A4400 */  add.d $f16, $f8, $f10
/* 0D586C 800D4C6C D46A0008 */  ldc1  $f10, 8($v1)
/* 0D5870 800D4C70 462C8482 */  mul.d $f18, $f16, $f12
/* 0D5874 800D4C74 46249180 */  add.d $f6, $f18, $f4
/* 0D5878 800D4C78 462C3202 */  mul.d $f8, $f6, $f12
/* 0D587C 800D4C7C 46285380 */  add.d $f14, $f10, $f8
/* 0D5880 800D4C80 462C1402 */  mul.d $f16, $f2, $f12
/* 0D5884 800D4C84 00000000 */  nop   
/* 0D5888 800D4C88 462E8482 */  mul.d $f18, $f16, $f14
/* 0D588C 800D4C8C 46229100 */  add.d $f4, $f18, $f2
/* 0D5890 800D4C90 03E00008 */  jr    $ra
/* 0D5894 800D4C94 46202020 */   cvt.s.d $f0, $f4

.L800D4C98:
/* 0D5898 800D4C98 03E00008 */  jr    $ra
/* 0D589C 800D4C9C C7A00000 */   lwc1  $f0, ($sp)

.L800D4CA0:
/* 0D58A0 800D4CA0 28610136 */  slti  $at, $v1, 0x136
/* 0D58A4 800D4CA4 10200044 */  beqz  $at, .L800D4DB8
/* 0D58A8 800D4CA8 C7A40000 */   lwc1  $f4, ($sp)
/* 0D58AC 800D4CAC C7A60000 */  lwc1  $f6, ($sp)
/* 0D58B0 800D4CB0 3C01800F */  lui   $at, %hi(rpi_sinf) # $at, 0x800f
/* 0D58B4 800D4CB4 D42A9838 */  ldc1  $f10, %lo(rpi_sinf)($at)
/* 0D58B8 800D4CB8 460030A1 */  cvt.d.s $f2, $f6
/* 0D58BC 800D4CBC 44804800 */  mtc1  $zero, $f9
/* 0D58C0 800D4CC0 462A1002 */  mul.d $f0, $f2, $f10
/* 0D58C4 800D4CC4 44804000 */  mtc1  $zero, $f8
/* 0D58C8 800D4CC8 3C013FE0 */  li    $at, 0x3FE00000 # 1.750000
/* 0D58CC 800D4CCC 4620403E */  c.le.d $f8, $f0
/* 0D58D0 800D4CD0 00000000 */  nop   
/* 0D58D4 800D4CD4 4502000B */  bc1fl .L800D4D04
/* 0D58D8 800D4CD8 44813800 */   mtc1  $at, $f7
/* 0D58DC 800D4CDC 3C013FE0 */  li    $at, 0x3FE00000 # 1.750000
/* 0D58E0 800D4CE0 44818800 */  mtc1  $at, $f17
/* 0D58E4 800D4CE4 44808000 */  mtc1  $zero, $f16
/* 0D58E8 800D4CE8 00000000 */  nop   
/* 0D58EC 800D4CEC 46300480 */  add.d $f18, $f0, $f16
/* 0D58F0 800D4CF0 4620910D */  trunc.w.d $f4, $f18
/* 0D58F4 800D4CF4 44022000 */  mfc1  $v0, $f4
/* 0D58F8 800D4CF8 10000009 */  b     .L800D4D20
/* 0D58FC 800D4CFC 44828000 */   mtc1  $v0, $f16
/* 0D5900 800D4D00 44813800 */  mtc1  $at, $f7
.L800D4D04:
/* 0D5904 800D4D04 44803000 */  mtc1  $zero, $f6
/* 0D5908 800D4D08 00000000 */  nop   
/* 0D590C 800D4D0C 46260281 */  sub.d $f10, $f0, $f6
/* 0D5910 800D4D10 4620520D */  trunc.w.d $f8, $f10
/* 0D5914 800D4D14 44024000 */  mfc1  $v0, $f8
/* 0D5918 800D4D18 00000000 */  nop   
/* 0D591C 800D4D1C 44828000 */  mtc1  $v0, $f16
.L800D4D20:
/* 0D5920 800D4D20 3C01800F */  lui   $at, %hi(pihi_sinf) # $at, 0x800f
/* 0D5924 800D4D24 D4329840 */  ldc1  $f18, %lo(pihi_sinf)($at)
/* 0D5928 800D4D28 46808021 */  cvt.d.w $f0, $f16
/* 0D592C 800D4D2C 3C01800F */  lui   $at, %hi(pilo_sinf) # $at, 0x800f
/* 0D5930 800D4D30 D4269848 */  ldc1  $f6, %lo(pilo_sinf)($at)
/* 0D5934 800D4D34 3C03800F */  lui   $v1, %hi(P_sinf) # $v1, 0x800f
/* 0D5938 800D4D38 24639810 */  addiu $v1, %lo(P_sinf) # addiu $v1, $v1, -0x67f0
/* 0D593C 800D4D3C 46320102 */  mul.d $f4, $f0, $f18
/* 0D5940 800D4D40 D4680020 */  ldc1  $f8, 0x20($v1)
/* 0D5944 800D4D44 D4720018 */  ldc1  $f18, 0x18($v1)
/* 0D5948 800D4D48 30590001 */  andi  $t9, $v0, 1
/* 0D594C 800D4D4C 46260282 */  mul.d $f10, $f0, $f6
/* 0D5950 800D4D50 46241081 */  sub.d $f2, $f2, $f4
/* 0D5954 800D4D54 462A1081 */  sub.d $f2, $f2, $f10
/* 0D5958 800D4D58 D46A0010 */  ldc1  $f10, 0x10($v1)
/* 0D595C 800D4D5C 46221302 */  mul.d $f12, $f2, $f2
/* 0D5960 800D4D60 00000000 */  nop   
/* 0D5964 800D4D64 462C4402 */  mul.d $f16, $f8, $f12
/* 0D5968 800D4D68 46328100 */  add.d $f4, $f16, $f18
/* 0D596C 800D4D6C D4720008 */  ldc1  $f18, 8($v1)
/* 0D5970 800D4D70 462C2182 */  mul.d $f6, $f4, $f12
/* 0D5974 800D4D74 462A3200 */  add.d $f8, $f6, $f10
/* 0D5978 800D4D78 462C4402 */  mul.d $f16, $f8, $f12
/* 0D597C 800D4D7C 17200007 */  bnez  $t9, .L800D4D9C
/* 0D5980 800D4D80 46309380 */   add.d $f14, $f18, $f16
/* 0D5984 800D4D84 462C1102 */  mul.d $f4, $f2, $f12
/* 0D5988 800D4D88 00000000 */  nop   
/* 0D598C 800D4D8C 462E2182 */  mul.d $f6, $f4, $f14
/* 0D5990 800D4D90 46223280 */  add.d $f10, $f6, $f2
/* 0D5994 800D4D94 03E00008 */  jr    $ra
/* 0D5998 800D4D98 46205020 */   cvt.s.d $f0, $f10

.L800D4D9C:
/* 0D599C 800D4D9C 462C1202 */  mul.d $f8, $f2, $f12
/* 0D59A0 800D4DA0 00000000 */  nop   
/* 0D59A4 800D4DA4 462E4482 */  mul.d $f18, $f8, $f14
/* 0D59A8 800D4DA8 46229400 */  add.d $f16, $f18, $f2
/* 0D59AC 800D4DAC 46208020 */  cvt.s.d $f0, $f16
/* 0D59B0 800D4DB0 03E00008 */  jr    $ra
/* 0D59B4 800D4DB4 46000007 */   neg.s $f0, $f0

.L800D4DB8:
/* 0D59B8 800D4DB8 46042032 */  c.eq.s $f4, $f4
/* 0D59BC 800D4DBC 3C01800F */  lui   $at, %hi(zero_sinf) # $at, 0x800f
/* 0D59C0 800D4DC0 45010004 */  bc1t  .L800D4DD4
/* 0D59C4 800D4DC4 00000000 */   nop   
/* 0D59C8 800D4DC8 3C01800F */  lui   $at, %hi(__libm_qnan_f) # $at, 0x800f
/* 0D59CC 800D4DCC 03E00008 */  jr    $ra
/* 0D59D0 800D4DD0 C42098C0 */   lwc1  $f0, %lo(__libm_qnan_f)($at)

.L800D4DD4:
/* 0D59D4 800D4DD4 C4209850 */  lwc1  $f0, %lo(zero_sinf)($at)
/* 0D59D8 800D4DD8 03E00008 */  jr    $ra
/* 0D59DC 800D4DDC 00000000 */   nop   

