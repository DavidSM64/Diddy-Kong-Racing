glabel func_800AAFD0
/* 0ABBD0 800AAFD0 27BDFF98 */  addiu $sp, $sp, -0x68
/* 0ABBD4 800AAFD4 AFBF003C */  sw    $ra, 0x3c($sp)
/* 0ABBD8 800AAFD8 AFBE0038 */  sw    $fp, 0x38($sp)
/* 0ABBDC 800AAFDC AFB70034 */  sw    $s7, 0x34($sp)
/* 0ABBE0 800AAFE0 AFB60030 */  sw    $s6, 0x30($sp)
/* 0ABBE4 800AAFE4 AFB5002C */  sw    $s5, 0x2c($sp)
/* 0ABBE8 800AAFE8 AFB40028 */  sw    $s4, 0x28($sp)
/* 0ABBEC 800AAFEC AFB30024 */  sw    $s3, 0x24($sp)
/* 0ABBF0 800AAFF0 AFB20020 */  sw    $s2, 0x20($sp)
/* 0ABBF4 800AAFF4 AFB1001C */  sw    $s1, 0x1c($sp)
/* 0ABBF8 800AAFF8 AFB00018 */  sw    $s0, 0x18($sp)
/* 0ABBFC 800AAFFC 84850028 */  lh    $a1, 0x28($a0)
/* 0ABC00 800AB000 00809825 */  move  $s3, $a0
/* 0ABC04 800AB004 18A00057 */  blez  $a1, .L800AB164
/* 0ABC08 800AB008 0000B825 */   move  $s7, $zero
/* 0ABC0C 800AB00C 3C128012 */  lui   $s2, %hi(gHUDCurrDisplayList) # $s2, 0x8012
/* 0ABC10 800AB010 26526CFC */  addiu $s2, %lo(gHUDCurrDisplayList) # addiu $s2, $s2, 0x6cfc
/* 0ABC14 800AB014 0000F025 */  move  $fp, $zero
.L800AB018:
/* 0ABC18 800AB018 8E6E0038 */  lw    $t6, 0x38($s3)
/* 0ABC1C 800AB01C 24160001 */  li    $s6, 1
/* 0ABC20 800AB020 01DE1021 */  addu  $v0, $t6, $fp
/* 0ABC24 800AB024 8C470008 */  lw    $a3, 8($v0)
/* 0ABC28 800AB028 240100FF */  li    $at, 255
/* 0ABC2C 800AB02C 30EF0100 */  andi  $t7, $a3, 0x100
/* 0ABC30 800AB030 15E00048 */  bnez  $t7, .L800AB154
/* 0ABC34 800AB034 00000000 */   nop   
/* 0ABC38 800AB038 84430002 */  lh    $v1, 2($v0)
/* 0ABC3C 800AB03C 84440004 */  lh    $a0, 4($v0)
/* 0ABC40 800AB040 00035880 */  sll   $t3, $v1, 2
/* 0ABC44 800AB044 8458000E */  lh    $t8, 0xe($v0)
/* 0ABC48 800AB048 84590010 */  lh    $t9, 0x10($v0)
/* 0ABC4C 800AB04C 8E6A0004 */  lw    $t2, 4($s3)
/* 0ABC50 800AB050 8E6C0008 */  lw    $t4, 8($s3)
/* 0ABC54 800AB054 90450000 */  lbu   $a1, ($v0)
/* 0ABC58 800AB058 01635821 */  addu  $t3, $t3, $v1
/* 0ABC5C 800AB05C 000B5840 */  sll   $t3, $t3, 1
/* 0ABC60 800AB060 00046900 */  sll   $t5, $a0, 4
/* 0ABC64 800AB064 03038023 */  subu  $s0, $t8, $v1
/* 0ABC68 800AB068 0324A023 */  subu  $s4, $t9, $a0
/* 0ABC6C 800AB06C 014BA821 */  addu  $s5, $t2, $t3
/* 0ABC70 800AB070 14A10003 */  bne   $a1, $at, .L800AB080
/* 0ABC74 800AB074 018D4021 */   addu  $t0, $t4, $t5
/* 0ABC78 800AB078 10000006 */  b     .L800AB094
/* 0ABC7C 800AB07C 00008825 */   move  $s1, $zero
.L800AB080:
/* 0ABC80 800AB080 8E6E0000 */  lw    $t6, ($s3)
/* 0ABC84 800AB084 000578C0 */  sll   $t7, $a1, 3
/* 0ABC88 800AB088 01CFC021 */  addu  $t8, $t6, $t7
/* 0ABC8C 800AB08C 8F110000 */  lw    $s1, ($t8)
/* 0ABC90 800AB090 00000000 */  nop   
.L800AB094:
/* 0ABC94 800AB094 2401FFFD */  li    $at, -3
/* 0ABC98 800AB098 00E13024 */  and   $a2, $a3, $at
/* 0ABC9C 800AB09C 02402025 */  move  $a0, $s2
/* 0ABCA0 800AB0A0 02202825 */  move  $a1, $s1
/* 0ABCA4 800AB0A4 0C01ED32 */  jal   func_8007B4C8
/* 0ABCA8 800AB0A8 AFA80044 */   sw    $t0, 0x44($sp)
/* 0ABCAC 800AB0AC 8E430000 */  lw    $v1, ($s2)
/* 0ABCB0 800AB0B0 3C098000 */  lui   $t1, 0x8000
/* 0ABCB4 800AB0B4 02A92021 */  addu  $a0, $s5, $t1
/* 0ABCB8 800AB0B8 260AFFFF */  addiu $t2, $s0, -1
/* 0ABCBC 800AB0BC 24790008 */  addiu $t9, $v1, 8
/* 0ABCC0 800AB0C0 AE590000 */  sw    $t9, ($s2)
/* 0ABCC4 800AB0C4 000A58C0 */  sll   $t3, $t2, 3
/* 0ABCC8 800AB0C8 308C0006 */  andi  $t4, $a0, 6
/* 0ABCCC 800AB0CC 016C6825 */  or    $t5, $t3, $t4
/* 0ABCD0 800AB0D0 0010C8C0 */  sll   $t9, $s0, 3
/* 0ABCD4 800AB0D4 03305021 */  addu  $t2, $t9, $s0
/* 0ABCD8 800AB0D8 000A5840 */  sll   $t3, $t2, 1
/* 0ABCDC 800AB0DC 31AE00FF */  andi  $t6, $t5, 0xff
/* 0ABCE0 800AB0E0 000E7C00 */  sll   $t7, $t6, 0x10
/* 0ABCE4 800AB0E4 256C0008 */  addiu $t4, $t3, 8
/* 0ABCE8 800AB0E8 3C010400 */  lui   $at, 0x400
/* 0ABCEC 800AB0EC 8FA80044 */  lw    $t0, 0x44($sp)
/* 0ABCF0 800AB0F0 01E1C025 */  or    $t8, $t7, $at
/* 0ABCF4 800AB0F4 318DFFFF */  andi  $t5, $t4, 0xffff
/* 0ABCF8 800AB0F8 030D7025 */  or    $t6, $t8, $t5
/* 0ABCFC 800AB0FC AC6E0000 */  sw    $t6, ($v1)
/* 0ABD00 800AB100 16200002 */  bnez  $s1, .L800AB10C
/* 0ABD04 800AB104 AC640004 */   sw    $a0, 4($v1)
/* 0ABD08 800AB108 0000B025 */  move  $s6, $zero
.L800AB10C:
/* 0ABD0C 800AB10C 2699FFFF */  addiu $t9, $s4, -1
/* 0ABD10 800AB110 8E430000 */  lw    $v1, ($s2)
/* 0ABD14 800AB114 00195100 */  sll   $t2, $t9, 4
/* 0ABD18 800AB118 01565825 */  or    $t3, $t2, $s6
/* 0ABD1C 800AB11C 316C00FF */  andi  $t4, $t3, 0xff
/* 0ABD20 800AB120 246F0008 */  addiu $t7, $v1, 8
/* 0ABD24 800AB124 AE4F0000 */  sw    $t7, ($s2)
/* 0ABD28 800AB128 000CC400 */  sll   $t8, $t4, 0x10
/* 0ABD2C 800AB12C 3C010500 */  lui   $at, 0x500
/* 0ABD30 800AB130 00147100 */  sll   $t6, $s4, 4
/* 0ABD34 800AB134 31CFFFFF */  andi  $t7, $t6, 0xffff
/* 0ABD38 800AB138 03016825 */  or    $t5, $t8, $at
/* 0ABD3C 800AB13C 01AFC825 */  or    $t9, $t5, $t7
/* 0ABD40 800AB140 01095021 */  addu  $t2, $t0, $t1
/* 0ABD44 800AB144 AC6A0004 */  sw    $t2, 4($v1)
/* 0ABD48 800AB148 AC790000 */  sw    $t9, ($v1)
/* 0ABD4C 800AB14C 86650028 */  lh    $a1, 0x28($s3)
/* 0ABD50 800AB150 00000000 */  nop   
.L800AB154:
/* 0ABD54 800AB154 26F70001 */  addiu $s7, $s7, 1
/* 0ABD58 800AB158 02E5082A */  slt   $at, $s7, $a1
/* 0ABD5C 800AB15C 1420FFAE */  bnez  $at, .L800AB018
/* 0ABD60 800AB160 27DE000C */   addiu $fp, $fp, 0xc
.L800AB164:
/* 0ABD64 800AB164 8FBF003C */  lw    $ra, 0x3c($sp)
/* 0ABD68 800AB168 8FB00018 */  lw    $s0, 0x18($sp)
/* 0ABD6C 800AB16C 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0ABD70 800AB170 8FB20020 */  lw    $s2, 0x20($sp)
/* 0ABD74 800AB174 8FB30024 */  lw    $s3, 0x24($sp)
/* 0ABD78 800AB178 8FB40028 */  lw    $s4, 0x28($sp)
/* 0ABD7C 800AB17C 8FB5002C */  lw    $s5, 0x2c($sp)
/* 0ABD80 800AB180 8FB60030 */  lw    $s6, 0x30($sp)
/* 0ABD84 800AB184 8FB70034 */  lw    $s7, 0x34($sp)
/* 0ABD88 800AB188 8FBE0038 */  lw    $fp, 0x38($sp)
/* 0ABD8C 800AB18C 03E00008 */  jr    $ra
/* 0ABD90 800AB190 27BD0068 */   addiu $sp, $sp, 0x68

