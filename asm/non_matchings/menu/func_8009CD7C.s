glabel func_8009CD7C
/* 09D97C 8009CD7C 27BDFF90 */  addiu $sp, $sp, -0x70
/* 09D980 8009CD80 3C0F800E */  lui   $t7, %hi(sMenuGuiOpacity) # $t7, 0x800e
/* 09D984 8009CD84 8DEFF764 */  lw    $t7, %lo(sMenuGuiOpacity)($t7)
/* 09D988 8009CD88 AFB5002C */  sw    $s5, 0x2c($sp)
/* 09D98C 8009CD8C 240E0009 */  li    $t6, 9
/* 09D990 8009CD90 240100FF */  li    $at, 255
/* 09D994 8009CD94 0080A825 */  move  $s5, $a0
/* 09D998 8009CD98 AFBF003C */  sw    $ra, 0x3c($sp)
/* 09D99C 8009CD9C AFBE0038 */  sw    $fp, 0x38($sp)
/* 09D9A0 8009CDA0 AFB70034 */  sw    $s7, 0x34($sp)
/* 09D9A4 8009CDA4 AFB60030 */  sw    $s6, 0x30($sp)
/* 09D9A8 8009CDA8 AFB40028 */  sw    $s4, 0x28($sp)
/* 09D9AC 8009CDAC AFB30024 */  sw    $s3, 0x24($sp)
/* 09D9B0 8009CDB0 AFB20020 */  sw    $s2, 0x20($sp)
/* 09D9B4 8009CDB4 AFB1001C */  sw    $s1, 0x1c($sp)
/* 09D9B8 8009CDB8 AFB00018 */  sw    $s0, 0x18($sp)
/* 09D9BC 8009CDBC 11E10003 */  beq   $t7, $at, .L8009CDCC
/* 09D9C0 8009CDC0 AFAE005C */   sw    $t6, 0x5c($sp)
/* 09D9C4 8009CDC4 2418000D */  li    $t8, 13
/* 09D9C8 8009CDC8 AFB8005C */  sw    $t8, 0x5c($sp)
.L8009CDCC:
/* 09D9CC 8009CDCC 86A60028 */  lh    $a2, 0x28($s5)
/* 09D9D0 8009CDD0 0000B025 */  move  $s6, $zero
/* 09D9D4 8009CDD4 18C00058 */  blez  $a2, .L8009CF38
/* 09D9D8 8009CDD8 0000B825 */   move  $s7, $zero
/* 09D9DC 8009CDDC 3C118012 */  lui   $s1, %hi(sMenuCurrDisplayList) # $s1, 0x8012
/* 09D9E0 8009CDE0 263163A0 */  addiu $s1, %lo(sMenuCurrDisplayList) # addiu $s1, $s1, 0x63a0
.L8009CDE4:
/* 09D9E4 8009CDE4 8EB90038 */  lw    $t9, 0x38($s5)
/* 09D9E8 8009CDE8 2401FFFF */  li    $at, -1
/* 09D9EC 8009CDEC 03371021 */  addu  $v0, $t9, $s7
/* 09D9F0 8009CDF0 8C4A0008 */  lw    $t2, 8($v0)
/* 09D9F4 8009CDF4 00000000 */  nop   
/* 09D9F8 8009CDF8 314B0100 */  andi  $t3, $t2, 0x100
/* 09D9FC 8009CDFC 1560004A */  bnez  $t3, .L8009CF28
/* 09DA00 8009CE00 00000000 */   nop   
/* 09DA04 8009CE04 84430002 */  lh    $v1, 2($v0)
/* 09DA08 8009CE08 84440004 */  lh    $a0, 4($v0)
/* 09DA0C 8009CE0C 00037880 */  sll   $t7, $v1, 2
/* 09DA10 8009CE10 844C000E */  lh    $t4, 0xe($v0)
/* 09DA14 8009CE14 844D0010 */  lh    $t5, 0x10($v0)
/* 09DA18 8009CE18 8EAE0004 */  lw    $t6, 4($s5)
/* 09DA1C 8009CE1C 8EB80008 */  lw    $t8, 8($s5)
/* 09DA20 8009CE20 90450000 */  lbu   $a1, ($v0)
/* 09DA24 8009CE24 01E37821 */  addu  $t7, $t7, $v1
/* 09DA28 8009CE28 000F7840 */  sll   $t7, $t7, 1
/* 09DA2C 8009CE2C 0004C900 */  sll   $t9, $a0, 4
/* 09DA30 8009CE30 01838023 */  subu  $s0, $t4, $v1
/* 09DA34 8009CE34 01A49023 */  subu  $s2, $t5, $a0
/* 09DA38 8009CE38 01CFF021 */  addu  $fp, $t6, $t7
/* 09DA3C 8009CE3C 14A10005 */  bne   $a1, $at, .L8009CE54
/* 09DA40 8009CE40 03194021 */   addu  $t0, $t8, $t9
/* 09DA44 8009CE44 00009825 */  move  $s3, $zero
/* 09DA48 8009CE48 0000A025 */  move  $s4, $zero
/* 09DA4C 8009CE4C 10000009 */  b     .L8009CE74
/* 09DA50 8009CE50 00003825 */   move  $a3, $zero
.L8009CE54:
/* 09DA54 8009CE54 8EAA0000 */  lw    $t2, ($s5)
/* 09DA58 8009CE58 90470007 */  lbu   $a3, 7($v0)
/* 09DA5C 8009CE5C 000558C0 */  sll   $t3, $a1, 3
/* 09DA60 8009CE60 014B6021 */  addu  $t4, $t2, $t3
/* 09DA64 8009CE64 00076B80 */  sll   $t5, $a3, 0xe
/* 09DA68 8009CE68 8D930000 */  lw    $s3, ($t4)
/* 09DA6C 8009CE6C 24140001 */  li    $s4, 1
/* 09DA70 8009CE70 01A03825 */  move  $a3, $t5
.L8009CE74:
/* 09DA74 8009CE74 8FA6005C */  lw    $a2, 0x5c($sp)
/* 09DA78 8009CE78 02202025 */  move  $a0, $s1
/* 09DA7C 8009CE7C 02602825 */  move  $a1, $s3
/* 09DA80 8009CE80 0C01ED3A */  jal   func_8007B4E8
/* 09DA84 8009CE84 AFA80044 */   sw    $t0, 0x44($sp)
/* 09DA88 8009CE88 8E220000 */  lw    $v0, ($s1)
/* 09DA8C 8009CE8C 3C098000 */  lui   $t1, 0x8000
/* 09DA90 8009CE90 03C92021 */  addu  $a0, $fp, $t1
/* 09DA94 8009CE94 260FFFFF */  addiu $t7, $s0, -1
/* 09DA98 8009CE98 244E0008 */  addiu $t6, $v0, 8
/* 09DA9C 8009CE9C AE2E0000 */  sw    $t6, ($s1)
/* 09DAA0 8009CEA0 000FC0C0 */  sll   $t8, $t7, 3
/* 09DAA4 8009CEA4 30990006 */  andi  $t9, $a0, 6
/* 09DAA8 8009CEA8 03195025 */  or    $t2, $t8, $t9
/* 09DAAC 8009CEAC 001070C0 */  sll   $t6, $s0, 3
/* 09DAB0 8009CEB0 01D07821 */  addu  $t7, $t6, $s0
/* 09DAB4 8009CEB4 000FC040 */  sll   $t8, $t7, 1
/* 09DAB8 8009CEB8 314B00FF */  andi  $t3, $t2, 0xff
/* 09DABC 8009CEBC 000B6400 */  sll   $t4, $t3, 0x10
/* 09DAC0 8009CEC0 27190008 */  addiu $t9, $t8, 8
/* 09DAC4 8009CEC4 3C010400 */  lui   $at, 0x400
/* 09DAC8 8009CEC8 8FA80044 */  lw    $t0, 0x44($sp)
/* 09DACC 8009CECC 01816825 */  or    $t5, $t4, $at
/* 09DAD0 8009CED0 332AFFFF */  andi  $t2, $t9, 0xffff
/* 09DAD4 8009CED4 01AA5825 */  or    $t3, $t5, $t2
/* 09DAD8 8009CED8 264EFFFF */  addiu $t6, $s2, -1
/* 09DADC 8009CEDC AC4B0000 */  sw    $t3, ($v0)
/* 09DAE0 8009CEE0 AC440004 */  sw    $a0, 4($v0)
/* 09DAE4 8009CEE4 8E220000 */  lw    $v0, ($s1)
/* 09DAE8 8009CEE8 000E7900 */  sll   $t7, $t6, 4
/* 09DAEC 8009CEEC 01F4C025 */  or    $t8, $t7, $s4
/* 09DAF0 8009CEF0 331900FF */  andi  $t9, $t8, 0xff
/* 09DAF4 8009CEF4 244C0008 */  addiu $t4, $v0, 8
/* 09DAF8 8009CEF8 AE2C0000 */  sw    $t4, ($s1)
/* 09DAFC 8009CEFC 00196C00 */  sll   $t5, $t9, 0x10
/* 09DB00 8009CF00 00125900 */  sll   $t3, $s2, 4
/* 09DB04 8009CF04 3C010500 */  lui   $at, 0x500
/* 09DB08 8009CF08 01A15025 */  or    $t2, $t5, $at
/* 09DB0C 8009CF0C 316CFFFF */  andi  $t4, $t3, 0xffff
/* 09DB10 8009CF10 014C7025 */  or    $t6, $t2, $t4
/* 09DB14 8009CF14 01097821 */  addu  $t7, $t0, $t1
/* 09DB18 8009CF18 AC4F0004 */  sw    $t7, 4($v0)
/* 09DB1C 8009CF1C AC4E0000 */  sw    $t6, ($v0)
/* 09DB20 8009CF20 86A60028 */  lh    $a2, 0x28($s5)
/* 09DB24 8009CF24 00000000 */  nop   
.L8009CF28:
/* 09DB28 8009CF28 26D60001 */  addiu $s6, $s6, 1
/* 09DB2C 8009CF2C 02C6082A */  slt   $at, $s6, $a2
/* 09DB30 8009CF30 1420FFAC */  bnez  $at, .L8009CDE4
/* 09DB34 8009CF34 26F7000C */   addiu $s7, $s7, 0xc
.L8009CF38:
/* 09DB38 8009CF38 8FBF003C */  lw    $ra, 0x3c($sp)
/* 09DB3C 8009CF3C 8FB00018 */  lw    $s0, 0x18($sp)
/* 09DB40 8009CF40 8FB1001C */  lw    $s1, 0x1c($sp)
/* 09DB44 8009CF44 8FB20020 */  lw    $s2, 0x20($sp)
/* 09DB48 8009CF48 8FB30024 */  lw    $s3, 0x24($sp)
/* 09DB4C 8009CF4C 8FB40028 */  lw    $s4, 0x28($sp)
/* 09DB50 8009CF50 8FB5002C */  lw    $s5, 0x2c($sp)
/* 09DB54 8009CF54 8FB60030 */  lw    $s6, 0x30($sp)
/* 09DB58 8009CF58 8FB70034 */  lw    $s7, 0x34($sp)
/* 09DB5C 8009CF5C 8FBE0038 */  lw    $fp, 0x38($sp)
/* 09DB60 8009CF60 03E00008 */  jr    $ra
/* 09DB64 8009CF64 27BD0070 */   addiu $sp, $sp, 0x70

