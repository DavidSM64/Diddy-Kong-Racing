glabel func_80031CAC
/* 0328AC 80031CAC 3C03800E */  lui   $v1, %hi(gNumActiveLights) # $v1, 0x800e
/* 0328B0 80031CB0 2463C95C */  addiu $v1, %lo(gNumActiveLights) # addiu $v1, $v1, -0x36a4
/* 0328B4 80031CB4 3C0E800E */  lui   $t6, %hi(gMaxLights) # $t6, 0x800e
/* 0328B8 80031CB8 8DCEC958 */  lw    $t6, %lo(gMaxLights)($t6)
/* 0328BC 80031CBC 8C620000 */  lw    $v0, ($v1)
/* 0328C0 80031CC0 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0328C4 80031CC4 004E082A */  slt   $at, $v0, $t6
/* 0328C8 80031CC8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0328CC 80031CCC 102000AA */  beqz  $at, .L80031F78
/* 0328D0 80031CD0 00003025 */   move  $a2, $zero
/* 0328D4 80031CD4 3C0F800E */  lui   $t7, %hi(gActiveLights) # $t7, 0x800e
/* 0328D8 80031CD8 8DEFC950 */  lw    $t7, %lo(gActiveLights)($t7)
/* 0328DC 80031CDC 0002C080 */  sll   $t8, $v0, 2
/* 0328E0 80031CE0 01F8C821 */  addu  $t9, $t7, $t8
/* 0328E4 80031CE4 8F260000 */  lw    $a2, ($t9)
/* 0328E8 80031CE8 24490001 */  addiu $t1, $v0, 1
/* 0328EC 80031CEC AC690000 */  sw    $t1, ($v1)
/* 0328F0 80031CF0 90AA0008 */  lbu   $t2, 8($a1)
/* 0328F4 80031CF4 00000000 */  nop   
/* 0328F8 80031CF8 314B00F0 */  andi  $t3, $t2, 0xf0
/* 0328FC 80031CFC 000B6103 */  sra   $t4, $t3, 4
/* 032900 80031D00 A0CC0000 */  sb    $t4, ($a2)
/* 032904 80031D04 90AD0008 */  lbu   $t5, 8($a1)
/* 032908 80031D08 240B0001 */  li    $t3, 1
/* 03290C 80031D0C 31AE000F */  andi  $t6, $t5, 0xf
/* 032910 80031D10 A0CE0003 */  sb    $t6, 3($a2)
/* 032914 80031D14 90AF0009 */  lbu   $t7, 9($a1)
/* 032918 80031D18 00000000 */  nop   
/* 03291C 80031D1C 31F800E0 */  andi  $t8, $t7, 0xe0
/* 032920 80031D20 0018C943 */  sra   $t9, $t8, 5
/* 032924 80031D24 A0D90001 */  sb    $t9, 1($a2)
/* 032928 80031D28 90A90009 */  lbu   $t1, 9($a1)
/* 03292C 80031D2C A0CB0004 */  sb    $t3, 4($a2)
/* 032930 80031D30 312A001F */  andi  $t2, $t1, 0x1f
/* 032934 80031D34 A0CA0002 */  sb    $t2, 2($a2)
/* 032938 80031D38 ACC0000C */  sw    $zero, 0xc($a2)
/* 03293C 80031D3C A4C00006 */  sh    $zero, 6($a2)
/* 032940 80031D40 A4C00008 */  sh    $zero, 8($a2)
/* 032944 80031D44 1080000A */  beqz  $a0, .L80031D70
/* 032948 80031D48 A4C0000A */   sh    $zero, 0xa($a2)
/* 03294C 80031D4C C484000C */  lwc1  $f4, 0xc($a0)
/* 032950 80031D50 00000000 */  nop   
/* 032954 80031D54 E4C40010 */  swc1  $f4, 0x10($a2)
/* 032958 80031D58 C4860010 */  lwc1  $f6, 0x10($a0)
/* 03295C 80031D5C 00000000 */  nop   
/* 032960 80031D60 E4C60014 */  swc1  $f6, 0x14($a2)
/* 032964 80031D64 C4880014 */  lwc1  $f8, 0x14($a0)
/* 032968 80031D68 10000013 */  b     .L80031DB8
/* 03296C 80031D6C E4C80018 */   swc1  $f8, 0x18($a2)
.L80031D70:
/* 032970 80031D70 84AC0002 */  lh    $t4, 2($a1)
/* 032974 80031D74 00000000 */  nop   
/* 032978 80031D78 448C5000 */  mtc1  $t4, $f10
/* 03297C 80031D7C 00000000 */  nop   
/* 032980 80031D80 46805420 */  cvt.s.w $f16, $f10
/* 032984 80031D84 E4D00010 */  swc1  $f16, 0x10($a2)
/* 032988 80031D88 84AD0004 */  lh    $t5, 4($a1)
/* 03298C 80031D8C 00000000 */  nop   
/* 032990 80031D90 448D9000 */  mtc1  $t5, $f18
/* 032994 80031D94 00000000 */  nop   
/* 032998 80031D98 46809120 */  cvt.s.w $f4, $f18
/* 03299C 80031D9C E4C40014 */  swc1  $f4, 0x14($a2)
/* 0329A0 80031DA0 84AE0006 */  lh    $t6, 6($a1)
/* 0329A4 80031DA4 00000000 */  nop   
/* 0329A8 80031DA8 448E3000 */  mtc1  $t6, $f6
/* 0329AC 80031DAC 00000000 */  nop   
/* 0329B0 80031DB0 46803220 */  cvt.s.w $f8, $f6
/* 0329B4 80031DB4 E4C80018 */  swc1  $f8, 0x18($a2)
.L80031DB8:
/* 0329B8 80031DB8 90AF000A */  lbu   $t7, 0xa($a1)
/* 0329BC 80031DBC ACC0002C */  sw    $zero, 0x2c($a2)
/* 0329C0 80031DC0 000FC400 */  sll   $t8, $t7, 0x10
/* 0329C4 80031DC4 ACD8001C */  sw    $t8, 0x1c($a2)
/* 0329C8 80031DC8 A4C0003C */  sh    $zero, 0x3c($a2)
/* 0329CC 80031DCC 90B9000B */  lbu   $t9, 0xb($a1)
/* 0329D0 80031DD0 ACC00030 */  sw    $zero, 0x30($a2)
/* 0329D4 80031DD4 00194C00 */  sll   $t1, $t9, 0x10
/* 0329D8 80031DD8 ACC90020 */  sw    $t1, 0x20($a2)
/* 0329DC 80031DDC A4C0003E */  sh    $zero, 0x3e($a2)
/* 0329E0 80031DE0 90AA000C */  lbu   $t2, 0xc($a1)
/* 0329E4 80031DE4 ACC00034 */  sw    $zero, 0x34($a2)
/* 0329E8 80031DE8 000A5C00 */  sll   $t3, $t2, 0x10
/* 0329EC 80031DEC ACCB0024 */  sw    $t3, 0x24($a2)
/* 0329F0 80031DF0 A4C00040 */  sh    $zero, 0x40($a2)
/* 0329F4 80031DF4 90AC000D */  lbu   $t4, 0xd($a1)
/* 0329F8 80031DF8 ACC00038 */  sw    $zero, 0x38($a2)
/* 0329FC 80031DFC 000C6C00 */  sll   $t5, $t4, 0x10
/* 032A00 80031E00 ACCD0028 */  sw    $t5, 0x28($a2)
/* 032A04 80031E04 A4C00042 */  sh    $zero, 0x42($a2)
/* 032A08 80031E08 ACC00044 */  sw    $zero, 0x44($a2)
/* 032A0C 80031E0C 90AE001C */  lbu   $t6, 0x1c($a1)
/* 032A10 80031E10 00000000 */  nop   
/* 032A14 80031E14 29C10007 */  slti  $at, $t6, 7
/* 032A18 80031E18 10200020 */  beqz  $at, .L80031E9C
/* 032A1C 80031E1C 00000000 */   nop   
/* 032A20 80031E20 AFA50024 */  sw    $a1, 0x24($sp)
/* 032A24 80031E24 0C01AF6C */  jal   get_current_level_header
/* 032A28 80031E28 AFA60018 */   sw    $a2, 0x18($sp)
/* 032A2C 80031E2C 8FA50024 */  lw    $a1, 0x24($sp)
/* 032A30 80031E30 8FA60018 */  lw    $a2, 0x18($sp)
/* 032A34 80031E34 90AF001C */  lbu   $t7, 0x1c($a1)
/* 032A38 80031E38 2401FFFF */  li    $at, -1
/* 032A3C 80031E3C 000FC080 */  sll   $t8, $t7, 2
/* 032A40 80031E40 0058C821 */  addu  $t9, $v0, $t8
/* 032A44 80031E44 8F280074 */  lw    $t0, 0x74($t9)
/* 032A48 80031E48 00001825 */  move  $v1, $zero
/* 032A4C 80031E4C 11010013 */  beq   $t0, $at, .L80031E9C
/* 032A50 80031E50 250A0014 */   addiu $t2, $t0, 0x14
/* 032A54 80031E54 ACC80044 */  sw    $t0, 0x44($a2)
/* 032A58 80031E58 8D090000 */  lw    $t1, ($t0)
/* 032A5C 80031E5C A4C0004A */  sh    $zero, 0x4a($a2)
/* 032A60 80031E60 3124FFFF */  andi  $a0, $t1, 0xffff
/* 032A64 80031E64 A4C0004C */  sh    $zero, 0x4c($a2)
/* 032A68 80031E68 A4C0004E */  sh    $zero, 0x4e($a2)
/* 032A6C 80031E6C ACCA0044 */  sw    $t2, 0x44($a2)
/* 032A70 80031E70 1880000A */  blez  $a0, .L80031E9C
/* 032A74 80031E74 A4C90048 */   sh    $t1, 0x48($a2)
/* 032A78 80031E78 01401025 */  move  $v0, $t2
.L80031E7C:
/* 032A7C 80031E7C 94CB004E */  lhu   $t3, 0x4e($a2)
/* 032A80 80031E80 8C4C0004 */  lw    $t4, 4($v0)
/* 032A84 80031E84 24630001 */  addiu $v1, $v1, 1
/* 032A88 80031E88 0064082A */  slt   $at, $v1, $a0
/* 032A8C 80031E8C 016C6821 */  addu  $t5, $t3, $t4
/* 032A90 80031E90 A4CD004E */  sh    $t5, 0x4e($a2)
/* 032A94 80031E94 1420FFF9 */  bnez  $at, .L80031E7C
/* 032A98 80031E98 24420008 */   addiu $v0, $v0, 8
.L80031E9C:
/* 032A9C 80031E9C 84AE000E */  lh    $t6, 0xe($a1)
/* 032AA0 80031EA0 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 032AA4 80031EA4 448E5000 */  mtc1  $t6, $f10
/* 032AA8 80031EA8 340BFFFF */  li    $t3, 65535
/* 032AAC 80031EAC 46805420 */  cvt.s.w $f16, $f10
/* 032AB0 80031EB0 00C02025 */  move  $a0, $a2
/* 032AB4 80031EB4 E4D0005C */  swc1  $f16, 0x5c($a2)
/* 032AB8 80031EB8 84AF0010 */  lh    $t7, 0x10($a1)
/* 032ABC 80031EBC C4C0005C */  lwc1  $f0, 0x5c($a2)
/* 032AC0 80031EC0 448F9000 */  mtc1  $t7, $f18
/* 032AC4 80031EC4 44818000 */  mtc1  $at, $f16
/* 032AC8 80031EC8 46809120 */  cvt.s.w $f4, $f18
/* 032ACC 80031ECC 340FFFFF */  li    $t7, 65535
/* 032AD0 80031ED0 46008483 */  div.s $f18, $f16, $f0
/* 032AD4 80031ED4 E4C40060 */  swc1  $f4, 0x60($a2)
/* 032AD8 80031ED8 84B80012 */  lh    $t8, 0x12($a1)
/* 032ADC 80031EDC 46000282 */  mul.s $f10, $f0, $f0
/* 032AE0 80031EE0 44983000 */  mtc1  $t8, $f6
/* 032AE4 80031EE4 24180001 */  li    $t8, 1
/* 032AE8 80031EE8 E4CA0068 */  swc1  $f10, 0x68($a2)
/* 032AEC 80031EEC 46803220 */  cvt.s.w $f8, $f6
/* 032AF0 80031EF0 E4D2006C */  swc1  $f18, 0x6c($a2)
/* 032AF4 80031EF4 E4C80064 */  swc1  $f8, 0x64($a2)
/* 032AF8 80031EF8 84B90014 */  lh    $t9, 0x14($a1)
/* 032AFC 80031EFC 00000000 */  nop   
/* 032B00 80031F00 A4D90070 */  sh    $t9, 0x70($a2)
/* 032B04 80031F04 84A90018 */  lh    $t1, 0x18($a1)
/* 032B08 80031F08 00000000 */  nop   
/* 032B0C 80031F0C A4C90074 */  sh    $t1, 0x74($a2)
/* 032B10 80031F10 84AA0018 */  lh    $t2, 0x18($a1)
/* 032B14 80031F14 00000000 */  nop   
/* 032B18 80031F18 11400003 */  beqz  $t2, .L80031F28
/* 032B1C 80031F1C 00000000 */   nop   
/* 032B20 80031F20 10000002 */  b     .L80031F2C
/* 032B24 80031F24 A4CB0078 */   sh    $t3, 0x78($a2)
.L80031F28:
/* 032B28 80031F28 A4C00078 */  sh    $zero, 0x78($a2)
.L80031F2C:
/* 032B2C 80031F2C 84AC0016 */  lh    $t4, 0x16($a1)
/* 032B30 80031F30 00000000 */  nop   
/* 032B34 80031F34 A4CC0072 */  sh    $t4, 0x72($a2)
/* 032B38 80031F38 84AD001A */  lh    $t5, 0x1a($a1)
/* 032B3C 80031F3C 00000000 */  nop   
/* 032B40 80031F40 A4CD0076 */  sh    $t5, 0x76($a2)
/* 032B44 80031F44 84AE001A */  lh    $t6, 0x1a($a1)
/* 032B48 80031F48 00002825 */  move  $a1, $zero
/* 032B4C 80031F4C 11C00004 */  beqz  $t6, .L80031F60
/* 032B50 80031F50 00000000 */   nop   
/* 032B54 80031F54 A4CF007A */  sh    $t7, 0x7a($a2)
/* 032B58 80031F58 10000002 */  b     .L80031F64
/* 032B5C 80031F5C A4C0007A */   sh    $zero, 0x7a($a2)
.L80031F60:
/* 032B60 80031F60 A4C0007A */  sh    $zero, 0x7a($a2)
.L80031F64:
/* 032B64 80031F64 A0D80005 */  sb    $t8, 5($a2)
/* 032B68 80031F68 0C00C909 */  jal   func_80032424
/* 032B6C 80031F6C AFA60018 */   sw    $a2, 0x18($sp)
/* 032B70 80031F70 8FA60018 */  lw    $a2, 0x18($sp)
/* 032B74 80031F74 00000000 */  nop   
.L80031F78:
/* 032B78 80031F78 8FBF0014 */  lw    $ra, 0x14($sp)
/* 032B7C 80031F7C 27BD0020 */  addiu $sp, $sp, 0x20
/* 032B80 80031F80 03E00008 */  jr    $ra
/* 032B84 80031F84 00C01025 */   move  $v0, $a2

