glabel func_8002AD08
/* 02B908 8002AD08 3C028012 */  lui   $v0, %hi(D_8011D308) # $v0, 0x8012
/* 02B90C 8002AD0C 8042D308 */  lb    $v0, %lo(D_8011D308)($v0)
/* 02B910 8002AD10 10C00007 */  beqz  $a2, .L8002AD30
/* 02B914 8002AD14 00001825 */   move  $v1, $zero
/* 02B918 8002AD18 44800000 */  mtc1  $zero, $f0
/* 02B91C 8002AD1C 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 02B920 8002AD20 44812000 */  mtc1  $at, $f4
/* 02B924 8002AD24 E4C00000 */  swc1  $f0, ($a2)
/* 02B928 8002AD28 E4C00008 */  swc1  $f0, 8($a2)
/* 02B92C 8002AD2C E4C40004 */  swc1  $f4, 4($a2)
.L8002AD30:
/* 02B930 8002AD30 18400044 */  blez  $v0, .L8002AE44
/* 02B934 8002AD34 00002025 */   move  $a0, $zero
/* 02B938 8002AD38 30490003 */  andi  $t1, $v0, 3
/* 02B93C 8002AD3C 11200013 */  beqz  $t1, .L8002AD8C
/* 02B940 8002AD40 01203825 */   move  $a3, $t1
/* 02B944 8002AD44 3C0F8012 */  lui   $t7, %hi(D_8011D2B8) # $t7, 0x8012
/* 02B948 8002AD48 25EFD2B8 */  addiu $t7, %lo(D_8011D2B8) # addiu $t7, $t7, -0x2d48
/* 02B94C 8002AD4C 00007080 */  sll   $t6, $zero, 2
/* 02B950 8002AD50 01CF4021 */  addu  $t0, $t6, $t7
/* 02B954 8002AD54 240C000E */  li    $t4, 14
/* 02B958 8002AD58 240B000B */  li    $t3, 11
.L8002AD5C:
/* 02B95C 8002AD5C 8D180000 */  lw    $t8, ($t0)
/* 02B960 8002AD60 24630001 */  addiu $v1, $v1, 1
/* 02B964 8002AD64 830A0010 */  lb    $t2, 0x10($t8)
/* 02B968 8002AD68 00000000 */  nop   
/* 02B96C 8002AD6C 116A0003 */  beq   $t3, $t2, .L8002AD7C
/* 02B970 8002AD70 00000000 */   nop   
/* 02B974 8002AD74 158A0002 */  bne   $t4, $t2, .L8002AD80
/* 02B978 8002AD78 00000000 */   nop   
.L8002AD7C:
/* 02B97C 8002AD7C 24840001 */  addiu $a0, $a0, 1
.L8002AD80:
/* 02B980 8002AD80 14E3FFF6 */  bne   $a3, $v1, .L8002AD5C
/* 02B984 8002AD84 25080004 */   addiu $t0, $t0, 4
/* 02B988 8002AD88 1062002E */  beq   $v1, $v0, .L8002AE44
.L8002AD8C:
/* 02B98C 8002AD8C 3C0D8012 */   lui   $t5, %hi(D_8011D2B8) # $t5, 0x8012
/* 02B990 8002AD90 25ADD2B8 */  addiu $t5, %lo(D_8011D2B8) # addiu $t5, $t5, -0x2d48
/* 02B994 8002AD94 0002C880 */  sll   $t9, $v0, 2
/* 02B998 8002AD98 00037080 */  sll   $t6, $v1, 2
/* 02B99C 8002AD9C 01CD4021 */  addu  $t0, $t6, $t5
/* 02B9A0 8002ADA0 032D3821 */  addu  $a3, $t9, $t5
/* 02B9A4 8002ADA4 240B000B */  li    $t3, 11
/* 02B9A8 8002ADA8 240C000E */  li    $t4, 14
.L8002ADAC:
/* 02B9AC 8002ADAC 8D0F0000 */  lw    $t7, ($t0)
/* 02B9B0 8002ADB0 00000000 */  nop   
/* 02B9B4 8002ADB4 81EA0010 */  lb    $t2, 0x10($t7)
/* 02B9B8 8002ADB8 00000000 */  nop   
/* 02B9BC 8002ADBC 116A0003 */  beq   $t3, $t2, .L8002ADCC
/* 02B9C0 8002ADC0 00000000 */   nop   
/* 02B9C4 8002ADC4 158A0002 */  bne   $t4, $t2, .L8002ADD0
/* 02B9C8 8002ADC8 00000000 */   nop   
.L8002ADCC:
/* 02B9CC 8002ADCC 24840001 */  addiu $a0, $a0, 1
.L8002ADD0:
/* 02B9D0 8002ADD0 8D180004 */  lw    $t8, 4($t0)
/* 02B9D4 8002ADD4 00000000 */  nop   
/* 02B9D8 8002ADD8 830A0010 */  lb    $t2, 0x10($t8)
/* 02B9DC 8002ADDC 00000000 */  nop   
/* 02B9E0 8002ADE0 116A0003 */  beq   $t3, $t2, .L8002ADF0
/* 02B9E4 8002ADE4 00000000 */   nop   
/* 02B9E8 8002ADE8 158A0002 */  bne   $t4, $t2, .L8002ADF4
/* 02B9EC 8002ADEC 00000000 */   nop   
.L8002ADF0:
/* 02B9F0 8002ADF0 24840001 */  addiu $a0, $a0, 1
.L8002ADF4:
/* 02B9F4 8002ADF4 8D190008 */  lw    $t9, 8($t0)
/* 02B9F8 8002ADF8 00000000 */  nop   
/* 02B9FC 8002ADFC 83230010 */  lb    $v1, 0x10($t9)
/* 02BA00 8002AE00 00000000 */  nop   
/* 02BA04 8002AE04 11630003 */  beq   $t3, $v1, .L8002AE14
/* 02BA08 8002AE08 00000000 */   nop   
/* 02BA0C 8002AE0C 15830002 */  bne   $t4, $v1, .L8002AE18
/* 02BA10 8002AE10 00000000 */   nop   
.L8002AE14:
/* 02BA14 8002AE14 24840001 */  addiu $a0, $a0, 1
.L8002AE18:
/* 02BA18 8002AE18 8D0E000C */  lw    $t6, 0xc($t0)
/* 02BA1C 8002AE1C 25080010 */  addiu $t0, $t0, 0x10
/* 02BA20 8002AE20 81C30010 */  lb    $v1, 0x10($t6)
/* 02BA24 8002AE24 00000000 */  nop   
/* 02BA28 8002AE28 11630003 */  beq   $t3, $v1, .L8002AE38
/* 02BA2C 8002AE2C 00000000 */   nop   
/* 02BA30 8002AE30 15830002 */  bne   $t4, $v1, .L8002AE3C
/* 02BA34 8002AE34 00000000 */   nop   
.L8002AE38:
/* 02BA38 8002AE38 24840001 */  addiu $a0, $a0, 1
.L8002AE3C:
/* 02BA3C 8002AE3C 1507FFDB */  bne   $t0, $a3, .L8002ADAC
/* 02BA40 8002AE40 00000000 */   nop   
.L8002AE44:
/* 02BA44 8002AE44 240B000B */  li    $t3, 11
/* 02BA48 8002AE48 14800003 */  bnez  $a0, .L8002AE58
/* 02BA4C 8002AE4C 240C000E */   li    $t4, 14
/* 02BA50 8002AE50 03E00008 */  jr    $ra
/* 02BA54 8002AE54 00001025 */   move  $v0, $zero

.L8002AE58:
/* 02BA58 8002AE58 2407FFFF */  li    $a3, -1
/* 02BA5C 8002AE5C 18400084 */  blez  $v0, .L8002B070
/* 02BA60 8002AE60 00001825 */   move  $v1, $zero
/* 02BA64 8002AE64 30480001 */  andi  $t0, $v0, 1
/* 02BA68 8002AE68 11000022 */  beqz  $t0, .L8002AEF4
/* 02BA6C 8002AE6C 3C0D8012 */   lui   $t5, %hi(D_8011D2B8) # $t5, 0x8012
/* 02BA70 8002AE70 8DADD2B8 */  lw    $t5, %lo(D_8011D2B8)($t5)
/* 02BA74 8002AE74 3C014039 */  li    $at, 0x40390000 # 2.890625
/* 02BA78 8002AE78 81A30010 */  lb    $v1, 0x10($t5)
/* 02BA7C 8002AE7C 3C0F8012 */  lui   $t7, %hi(D_8011D2B8) # $t7, 0x8012
/* 02BA80 8002AE80 11630003 */  beq   $t3, $v1, .L8002AE90
/* 02BA84 8002AE84 00000000 */   nop   
/* 02BA88 8002AE88 15830019 */  bne   $t4, $v1, .L8002AEF0
/* 02BA8C 8002AE8C 24030001 */   li    $v1, 1
.L8002AE90:
/* 02BA90 8002AE90 8DEFD2B8 */  lw    $t7, %lo(D_8011D2B8)($t7)
/* 02BA94 8002AE94 44811800 */  mtc1  $at, $f3
/* 02BA98 8002AE98 C5E80000 */  lwc1  $f8, ($t7)
/* 02BA9C 8002AE9C 44801000 */  mtc1  $zero, $f2
/* 02BAA0 8002AEA0 460042A1 */  cvt.d.s $f10, $f8
/* 02BAA4 8002AEA4 46225400 */  add.d $f16, $f10, $f2
/* 02BAA8 8002AEA8 3C013FE0 */  li    $at, 0x3FE00000 # 1.750000
/* 02BAAC 8002AEAC 460061A1 */  cvt.d.s $f6, $f12
/* 02BAB0 8002AEB0 4630303C */  c.lt.d $f6, $f16
/* 02BAB4 8002AEB4 00000000 */  nop   
/* 02BAB8 8002AEB8 4500000D */  bc1f  .L8002AEF0
/* 02BABC 8002AEBC 24030001 */   li    $v1, 1
/* 02BAC0 8002AEC0 C5E40008 */  lwc1  $f4, 8($t7)
/* 02BAC4 8002AEC4 44819800 */  mtc1  $at, $f19
/* 02BAC8 8002AEC8 44809000 */  mtc1  $zero, $f18
/* 02BACC 8002AECC 46002221 */  cvt.d.s $f8, $f4
/* 02BAD0 8002AED0 4628903C */  c.lt.d $f18, $f8
/* 02BAD4 8002AED4 24010001 */  li    $at, 1
/* 02BAD8 8002AED8 45010003 */  bc1t  .L8002AEE8
/* 02BADC 8002AEDC 00000000 */   nop   
/* 02BAE0 8002AEE0 14810003 */  bne   $a0, $at, .L8002AEF0
/* 02BAE4 8002AEE4 24030001 */   li    $v1, 1
.L8002AEE8:
/* 02BAE8 8002AEE8 00003825 */  move  $a3, $zero
/* 02BAEC 8002AEEC 24030001 */  li    $v1, 1
.L8002AEF0:
/* 02BAF0 8002AEF0 1062005F */  beq   $v1, $v0, .L8002B070
.L8002AEF4:
/* 02BAF4 8002AEF4 3C014039 */   li    $at, 0x40390000 # 2.890625
/* 02BAF8 8002AEF8 44811800 */  mtc1  $at, $f3
/* 02BAFC 8002AEFC 3C014034 */  li    $at, 0x40340000 # 2.812500
/* 02BB00 8002AF00 3C198012 */  lui   $t9, %hi(D_8011D2B8) # $t9, 0x8012
/* 02BB04 8002AF04 2739D2B8 */  addiu $t9, %lo(D_8011D2B8) # addiu $t9, $t9, -0x2d48
/* 02BB08 8002AF08 0003C080 */  sll   $t8, $v1, 2
/* 02BB0C 8002AF0C 44817800 */  mtc1  $at, $f15
/* 02BB10 8002AF10 44801000 */  mtc1  $zero, $f2
/* 02BB14 8002AF14 44807000 */  mtc1  $zero, $f14
/* 02BB18 8002AF18 03194021 */  addu  $t0, $t8, $t9
.L8002AF1C:
/* 02BB1C 8002AF1C 8D090000 */  lw    $t1, ($t0)
/* 02BB20 8002AF20 00000000 */  nop   
/* 02BB24 8002AF24 812A0010 */  lb    $t2, 0x10($t1)
/* 02BB28 8002AF28 00000000 */  nop   
/* 02BB2C 8002AF2C 116A0003 */  beq   $t3, $t2, .L8002AF3C
/* 02BB30 8002AF30 00000000 */   nop   
/* 02BB34 8002AF34 158A0016 */  bne   $t4, $t2, .L8002AF90
/* 02BB38 8002AF38 00000000 */   nop   
.L8002AF3C:
/* 02BB3C 8002AF3C C5260000 */  lwc1  $f6, ($t1)
/* 02BB40 8002AF40 460062A1 */  cvt.d.s $f10, $f12
/* 02BB44 8002AF44 46003421 */  cvt.d.s $f16, $f6
/* 02BB48 8002AF48 46228100 */  add.d $f4, $f16, $f2
/* 02BB4C 8002AF4C 3C013FE0 */  li    $at, 0x3FE00000 # 1.750000
/* 02BB50 8002AF50 4624503C */  c.lt.d $f10, $f4
/* 02BB54 8002AF54 00000000 */  nop   
/* 02BB58 8002AF58 4500001A */  bc1f  .L8002AFC4
/* 02BB5C 8002AF5C 00000000 */   nop   
/* 02BB60 8002AF60 C5280008 */  lwc1  $f8, 8($t1)
/* 02BB64 8002AF64 44819800 */  mtc1  $at, $f19
/* 02BB68 8002AF68 44809000 */  mtc1  $zero, $f18
/* 02BB6C 8002AF6C 460041A1 */  cvt.d.s $f6, $f8
/* 02BB70 8002AF70 4626903C */  c.lt.d $f18, $f6
/* 02BB74 8002AF74 24010001 */  li    $at, 1
/* 02BB78 8002AF78 45010003 */  bc1t  .L8002AF88
/* 02BB7C 8002AF7C 00000000 */   nop   
/* 02BB80 8002AF80 14810010 */  bne   $a0, $at, .L8002AFC4
/* 02BB84 8002AF84 00000000 */   nop   
.L8002AF88:
/* 02BB88 8002AF88 1000000E */  b     .L8002AFC4
/* 02BB8C 8002AF8C 00603825 */   move  $a3, $v1
.L8002AF90:
/* 02BB90 8002AF90 04E0000C */  bltz  $a3, .L8002AFC4
/* 02BB94 8002AF94 28810002 */   slti  $at, $a0, 2
/* 02BB98 8002AF98 1420000A */  bnez  $at, .L8002AFC4
/* 02BB9C 8002AF9C 00000000 */   nop   
/* 02BBA0 8002AFA0 C52A0000 */  lwc1  $f10, ($t1)
/* 02BBA4 8002AFA4 46006421 */  cvt.d.s $f16, $f12
/* 02BBA8 8002AFA8 46005121 */  cvt.d.s $f4, $f10
/* 02BBAC 8002AFAC 462E2201 */  sub.d $f8, $f4, $f14
/* 02BBB0 8002AFB0 4628803C */  c.lt.d $f16, $f8
/* 02BBB4 8002AFB4 00000000 */  nop   
/* 02BBB8 8002AFB8 45000002 */  bc1f  .L8002AFC4
/* 02BBBC 8002AFBC 00000000 */   nop   
/* 02BBC0 8002AFC0 2407FFFF */  li    $a3, -1
.L8002AFC4:
/* 02BBC4 8002AFC4 8D090004 */  lw    $t1, 4($t0)
/* 02BBC8 8002AFC8 00000000 */  nop   
/* 02BBCC 8002AFCC 812A0010 */  lb    $t2, 0x10($t1)
/* 02BBD0 8002AFD0 C5200000 */  lwc1  $f0, ($t1)
/* 02BBD4 8002AFD4 116A0003 */  beq   $t3, $t2, .L8002AFE4
/* 02BBD8 8002AFD8 00000000 */   nop   
/* 02BBDC 8002AFDC 158A0015 */  bne   $t4, $t2, .L8002B034
/* 02BBE0 8002AFE0 00000000 */   nop   
.L8002AFE4:
/* 02BBE4 8002AFE4 460001A1 */  cvt.d.s $f6, $f0
/* 02BBE8 8002AFE8 46223280 */  add.d $f10, $f6, $f2
/* 02BBEC 8002AFEC 3C013FE0 */  li    $at, 0x3FE00000 # 1.750000
/* 02BBF0 8002AFF0 460064A1 */  cvt.d.s $f18, $f12
/* 02BBF4 8002AFF4 462A903C */  c.lt.d $f18, $f10
/* 02BBF8 8002AFF8 00000000 */  nop   
/* 02BBFC 8002AFFC 45000019 */  bc1f  .L8002B064
/* 02BC00 8002B000 00000000 */   nop   
/* 02BC04 8002B004 C5300008 */  lwc1  $f16, 8($t1)
/* 02BC08 8002B008 44812800 */  mtc1  $at, $f5
/* 02BC0C 8002B00C 44802000 */  mtc1  $zero, $f4
/* 02BC10 8002B010 46008221 */  cvt.d.s $f8, $f16
/* 02BC14 8002B014 4628203C */  c.lt.d $f4, $f8
/* 02BC18 8002B018 24010001 */  li    $at, 1
/* 02BC1C 8002B01C 45010003 */  bc1t  .L8002B02C
/* 02BC20 8002B020 00000000 */   nop   
/* 02BC24 8002B024 1481000F */  bne   $a0, $at, .L8002B064
/* 02BC28 8002B028 00000000 */   nop   
.L8002B02C:
/* 02BC2C 8002B02C 1000000D */  b     .L8002B064
/* 02BC30 8002B030 24670001 */   addiu $a3, $v1, 1
.L8002B034:
/* 02BC34 8002B034 04E0000B */  bltz  $a3, .L8002B064
/* 02BC38 8002B038 28810002 */   slti  $at, $a0, 2
/* 02BC3C 8002B03C 14200009 */  bnez  $at, .L8002B064
/* 02BC40 8002B040 00000000 */   nop   
/* 02BC44 8002B044 460004A1 */  cvt.d.s $f18, $f0
/* 02BC48 8002B048 462E9281 */  sub.d $f10, $f18, $f14
/* 02BC4C 8002B04C 460061A1 */  cvt.d.s $f6, $f12
/* 02BC50 8002B050 462A303C */  c.lt.d $f6, $f10
/* 02BC54 8002B054 00000000 */  nop   
/* 02BC58 8002B058 45000002 */  bc1f  .L8002B064
/* 02BC5C 8002B05C 00000000 */   nop   
/* 02BC60 8002B060 2407FFFF */  li    $a3, -1
.L8002B064:
/* 02BC64 8002B064 24630002 */  addiu $v1, $v1, 2
/* 02BC68 8002B068 1462FFAC */  bne   $v1, $v0, .L8002AF1C
/* 02BC6C 8002B06C 25080008 */   addiu $t0, $t0, 8
.L8002B070:
/* 02BC70 8002B070 04E10003 */  bgez  $a3, .L8002B080
/* 02BC74 8002B074 00077080 */   sll   $t6, $a3, 2
/* 02BC78 8002B078 03E00008 */  jr    $ra
/* 02BC7C 8002B07C 00001025 */   move  $v0, $zero

.L8002B080:
/* 02BC80 8002B080 3C0D8012 */  lui   $t5, %hi(D_8011D2B8) # $t5, 0x8012
/* 02BC84 8002B084 25ADD2B8 */  addiu $t5, %lo(D_8011D2B8) # addiu $t5, $t5, -0x2d48
/* 02BC88 8002B088 01CD1821 */  addu  $v1, $t6, $t5
/* 02BC8C 8002B08C 8C6F0000 */  lw    $t7, ($v1)
/* 02BC90 8002B090 00000000 */  nop   
/* 02BC94 8002B094 C5F00000 */  lwc1  $f16, ($t7)
/* 02BC98 8002B098 10C00010 */  beqz  $a2, .L8002B0DC
/* 02BC9C 8002B09C E4B00000 */   swc1  $f16, ($a1)
/* 02BCA0 8002B0A0 8C780000 */  lw    $t8, ($v1)
/* 02BCA4 8002B0A4 00000000 */  nop   
/* 02BCA8 8002B0A8 C7040004 */  lwc1  $f4, 4($t8)
/* 02BCAC 8002B0AC 00000000 */  nop   
/* 02BCB0 8002B0B0 E4C40000 */  swc1  $f4, ($a2)
/* 02BCB4 8002B0B4 8C790000 */  lw    $t9, ($v1)
/* 02BCB8 8002B0B8 00000000 */  nop   
/* 02BCBC 8002B0BC C7280008 */  lwc1  $f8, 8($t9)
/* 02BCC0 8002B0C0 00000000 */  nop   
/* 02BCC4 8002B0C4 E4C80004 */  swc1  $f8, 4($a2)
/* 02BCC8 8002B0C8 8C6E0000 */  lw    $t6, ($v1)
/* 02BCCC 8002B0CC 00000000 */  nop   
/* 02BCD0 8002B0D0 C5D2000C */  lwc1  $f18, 0xc($t6)
/* 02BCD4 8002B0D4 00000000 */  nop   
/* 02BCD8 8002B0D8 E4D20008 */  swc1  $f18, 8($a2)
.L8002B0DC:
/* 02BCDC 8002B0DC 8C6D0000 */  lw    $t5, ($v1)
/* 02BCE0 8002B0E0 00000000 */  nop   
/* 02BCE4 8002B0E4 81A20010 */  lb    $v0, 0x10($t5)
/* 02BCE8 8002B0E8 00000000 */  nop   
/* 02BCEC 8002B0EC 03E00008 */  jr    $ra
/* 02BCF0 8002B0F0 00000000 */   nop   

