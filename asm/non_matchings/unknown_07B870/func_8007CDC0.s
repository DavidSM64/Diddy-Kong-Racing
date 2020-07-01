glabel func_8007CDC0
/* 07D9C0 8007CDC0 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 07D9C4 8007CDC4 AFBF002C */  sw    $ra, 0x2c($sp)
/* 07D9C8 8007CDC8 AFBE0028 */  sw    $fp, 0x28($sp)
/* 07D9CC 8007CDCC AFB70024 */  sw    $s7, 0x24($sp)
/* 07D9D0 8007CDD0 AFB60020 */  sw    $s6, 0x20($sp)
/* 07D9D4 8007CDD4 AFB5001C */  sw    $s5, 0x1c($sp)
/* 07D9D8 8007CDD8 AFB40018 */  sw    $s4, 0x18($sp)
/* 07D9DC 8007CDDC AFB30014 */  sw    $s3, 0x14($sp)
/* 07D9E0 8007CDE0 AFB20010 */  sw    $s2, 0x10($sp)
/* 07D9E4 8007CDE4 AFB1000C */  sw    $s1, 0xc($sp)
/* 07D9E8 8007CDE8 AFB00008 */  sw    $s0, 8($sp)
/* 07D9EC 8007CDEC 848E0004 */  lh    $t6, 4($a0)
/* 07D9F0 8007CDF0 00863821 */  addu  $a3, $a0, $a2
/* 07D9F4 8007CDF4 AFAE0034 */  sw    $t6, 0x34($sp)
/* 07D9F8 8007CDF8 848F0006 */  lh    $t7, 6($a0)
/* 07D9FC 8007CDFC 3C098012 */  lui   $t1, %hi(D_80126364) # $t1, 0x8012
/* 07DA00 8007CE00 AFAF0030 */  sw    $t7, 0x30($sp)
/* 07DA04 8007CE04 90F2000C */  lbu   $s2, 0xc($a3)
/* 07DA08 8007CE08 90FE000D */  lbu   $fp, 0xd($a3)
/* 07DA0C 8007CE0C 3C028012 */  lui   $v0, %hi(D_80126360) # $v0, 0x8012
/* 07DA10 8007CE10 3C038012 */  lui   $v1, %hi(D_80126368) # $v1, 0x8012
/* 07DA14 8007CE14 8D296364 */  lw    $t1, %lo(D_80126364)($t1)
/* 07DA18 8007CE18 8C426360 */  lw    $v0, %lo(D_80126360)($v0)
/* 07DA1C 8007CE1C 8C636368 */  lw    $v1, %lo(D_80126368)($v1)
/* 07DA20 8007CE20 025E082A */  slt   $at, $s2, $fp
/* 07DA24 8007CE24 1020000A */  beqz  $at, .L8007CE50
/* 07DA28 8007CE28 00005025 */   move  $t2, $zero
/* 07DA2C 8007CE2C 8CB80008 */  lw    $t8, 8($a1)
/* 07DA30 8007CE30 0012C880 */  sll   $t9, $s2, 2
/* 07DA34 8007CE34 03197021 */  addu  $t6, $t8, $t9
/* 07DA38 8007CE38 8DC40000 */  lw    $a0, ($t6)
/* 07DA3C 8007CE3C 00000000 */  nop   
/* 07DA40 8007CE40 84980006 */  lh    $t8, 6($a0)
/* 07DA44 8007CE44 00000000 */  nop   
/* 07DA48 8007CE48 3319003B */  andi  $t9, $t8, 0x3b
/* 07DA4C 8007CE4C A4B90006 */  sh    $t9, 6($a1)
.L8007CE50:
/* 07DA50 8007CE50 025E082A */  slt   $at, $s2, $fp
/* 07DA54 8007CE54 1020008C */  beqz  $at, .L8007D088
/* 07DA58 8007CE58 00006825 */   move  $t5, $zero
/* 07DA5C 8007CE5C AFA50044 */  sw    $a1, 0x44($sp)
/* 07DA60 8007CE60 240500FF */  li    $a1, 255
/* 07DA64 8007CE64 00129880 */  sll   $s3, $s2, 2
/* 07DA68 8007CE68 3C1F0700 */  lui   $ra, 0x700
/* 07DA6C 8007CE6C 24170040 */  li    $s7, 64
/* 07DA70 8007CE70 24150001 */  li    $s5, 1
/* 07DA74 8007CE74 3C148000 */  lui   $s4, 0x8000
/* 07DA78 8007CE78 8FAE0044 */  lw    $t6, 0x44($sp)
.L8007CE7C:
/* 07DA7C 8007CE7C 0040B025 */  move  $s6, $v0
/* 07DA80 8007CE80 8DCF0008 */  lw    $t7, 8($t6)
/* 07DA84 8007CE84 8FAE0034 */  lw    $t6, 0x34($sp)
/* 07DA88 8007CE88 01F3C021 */  addu  $t8, $t7, $s3
/* 07DA8C 8007CE8C 8F040000 */  lw    $a0, ($t8)
/* 07DA90 8007CE90 8FAF0030 */  lw    $t7, 0x30($sp)
/* 07DA94 8007CE94 90900000 */  lbu   $s0, ($a0)
/* 07DA98 8007CE98 90910001 */  lbu   $s1, 1($a0)
/* 07DA9C 8007CE9C 80990003 */  lb    $t9, 3($a0)
/* 07DAA0 8007CEA0 80980004 */  lb    $t8, 4($a0)
/* 07DAA4 8007CEA4 032E4023 */  subu  $t0, $t9, $t6
/* 07DAA8 8007CEA8 01F83023 */  subu  $a2, $t7, $t8
/* 07DAAC 8007CEAC 01105821 */  addu  $t3, $t0, $s0
/* 07DAB0 8007CEB0 24C7FFFF */  addiu $a3, $a2, -1
/* 07DAB4 8007CEB4 256BFFFF */  addiu $t3, $t3, -1
/* 07DAB8 8007CEB8 00D16023 */  subu  $t4, $a2, $s1
/* 07DABC 8007CEBC A4480000 */  sh    $t0, ($v0)
/* 07DAC0 8007CEC0 A4470002 */  sh    $a3, 2($v0)
/* 07DAC4 8007CEC4 A4400004 */  sh    $zero, 4($v0)
/* 07DAC8 8007CEC8 A0450006 */  sb    $a1, 6($v0)
/* 07DACC 8007CECC A0450007 */  sb    $a1, 7($v0)
/* 07DAD0 8007CED0 A0450008 */  sb    $a1, 8($v0)
/* 07DAD4 8007CED4 A0450009 */  sb    $a1, 9($v0)
/* 07DAD8 8007CED8 A44B000A */  sh    $t3, 0xa($v0)
/* 07DADC 8007CEDC A447000C */  sh    $a3, 0xc($v0)
/* 07DAE0 8007CEE0 A440000E */  sh    $zero, 0xe($v0)
/* 07DAE4 8007CEE4 A0450010 */  sb    $a1, 0x10($v0)
/* 07DAE8 8007CEE8 A0450011 */  sb    $a1, 0x11($v0)
/* 07DAEC 8007CEEC A0450012 */  sb    $a1, 0x12($v0)
/* 07DAF0 8007CEF0 A0450013 */  sb    $a1, 0x13($v0)
/* 07DAF4 8007CEF4 A44B0014 */  sh    $t3, 0x14($v0)
/* 07DAF8 8007CEF8 A44C0016 */  sh    $t4, 0x16($v0)
/* 07DAFC 8007CEFC A4400018 */  sh    $zero, 0x18($v0)
/* 07DB00 8007CF00 A045001A */  sb    $a1, 0x1a($v0)
/* 07DB04 8007CF04 A045001B */  sb    $a1, 0x1b($v0)
/* 07DB08 8007CF08 A045001C */  sb    $a1, 0x1c($v0)
/* 07DB0C 8007CF0C A045001D */  sb    $a1, 0x1d($v0)
/* 07DB10 8007CF10 A448001E */  sh    $t0, 0x1e($v0)
/* 07DB14 8007CF14 A44C0020 */  sh    $t4, 0x20($v0)
/* 07DB18 8007CF18 A4400022 */  sh    $zero, 0x22($v0)
/* 07DB1C 8007CF1C A0450024 */  sb    $a1, 0x24($v0)
/* 07DB20 8007CF20 A0450025 */  sb    $a1, 0x25($v0)
/* 07DB24 8007CF24 A0450026 */  sb    $a1, 0x26($v0)
/* 07DB28 8007CF28 A0450027 */  sb    $a1, 0x27($v0)
/* 07DB2C 8007CF2C 8487000A */  lh    $a3, 0xa($a0)
/* 07DB30 8007CF30 01203025 */  move  $a2, $t1
/* 07DB34 8007CF34 30F900FF */  andi  $t9, $a3, 0xff
/* 07DB38 8007CF38 00197400 */  sll   $t6, $t9, 0x10
/* 07DB3C 8007CF3C 0007C0C0 */  sll   $t8, $a3, 3
/* 07DB40 8007CF40 3319FFFF */  andi  $t9, $t8, 0xffff
/* 07DB44 8007CF44 01DF7825 */  or    $t7, $t6, $ra
/* 07DB48 8007CF48 01F97025 */  or    $t6, $t7, $t9
/* 07DB4C 8007CF4C ACCE0000 */  sw    $t6, ($a2)
/* 07DB50 8007CF50 8C98000C */  lw    $t8, 0xc($a0)
/* 07DB54 8007CF54 24420028 */  addiu $v0, $v0, 0x28
/* 07DB58 8007CF58 03147821 */  addu  $t7, $t8, $s4
/* 07DB5C 8007CF5C ACCF0004 */  sw    $t7, 4($a2)
/* 07DB60 8007CF60 15A0001A */  bnez  $t5, .L8007CFCC
/* 07DB64 8007CF64 25290008 */   addiu $t1, $t1, 8
/* 07DB68 8007CF68 03D24023 */  subu  $t0, $fp, $s2
/* 07DB6C 8007CF6C 29010006 */  slti  $at, $t0, 6
/* 07DB70 8007CF70 14200002 */  bnez  $at, .L8007CF7C
/* 07DB74 8007CF74 01203025 */   move  $a2, $t1
/* 07DB78 8007CF78 24080005 */  li    $t0, 5
.L8007CF7C:
/* 07DB7C 8007CF7C 00082080 */  sll   $a0, $t0, 2
/* 07DB80 8007CF80 2499FFFF */  addiu $t9, $a0, -1
/* 07DB84 8007CF84 02D43821 */  addu  $a3, $s6, $s4
/* 07DB88 8007CF88 30F80006 */  andi  $t8, $a3, 6
/* 07DB8C 8007CF8C 001970C0 */  sll   $t6, $t9, 3
/* 07DB90 8007CF90 01D87825 */  or    $t7, $t6, $t8
/* 07DB94 8007CF94 35F90001 */  ori   $t9, $t7, 1
/* 07DB98 8007CF98 332E00FF */  andi  $t6, $t9, 0xff
/* 07DB9C 8007CF9C 000EC400 */  sll   $t8, $t6, 0x10
/* 07DBA0 8007CFA0 0004C8C0 */  sll   $t9, $a0, 3
/* 07DBA4 8007CFA4 3C010400 */  lui   $at, 0x400
/* 07DBA8 8007CFA8 03017825 */  or    $t7, $t8, $at
/* 07DBAC 8007CFAC 03247021 */  addu  $t6, $t9, $a0
/* 07DBB0 8007CFB0 000EC040 */  sll   $t8, $t6, 1
/* 07DBB4 8007CFB4 27190008 */  addiu $t9, $t8, 8
/* 07DBB8 8007CFB8 332EFFFF */  andi  $t6, $t9, 0xffff
/* 07DBBC 8007CFBC 01EEC025 */  or    $t8, $t7, $t6
/* 07DBC0 8007CFC0 ACD80000 */  sw    $t8, ($a2)
/* 07DBC4 8007CFC4 ACC70004 */  sw    $a3, 4($a2)
/* 07DBC8 8007CFC8 25290008 */  addiu $t1, $t1, 8
.L8007CFCC:
/* 07DBCC 8007CFCC 3C190511 */  lui   $t9, (0x05110020 >> 16) # lui $t9, 0x511
/* 07DBD0 8007CFD0 37390020 */  ori   $t9, (0x05110020 & 0xFFFF) # ori $t9, $t9, 0x20
/* 07DBD4 8007CFD4 01202025 */  move  $a0, $t1
/* 07DBD8 8007CFD8 AC990000 */  sw    $t9, ($a0)
/* 07DBDC 8007CFDC 00747821 */  addu  $t7, $v1, $s4
/* 07DBE0 8007CFE0 AC8F0004 */  sw    $t7, 4($a0)
/* 07DBE4 8007CFE4 2606FFFF */  addiu $a2, $s0, -1
/* 07DBE8 8007CFE8 2627FFFF */  addiu $a3, $s1, -1
/* 07DBEC 8007CFEC 25480003 */  addiu $t0, $t2, 3
/* 07DBF0 8007CFF0 254B0001 */  addiu $t3, $t2, 1
/* 07DBF4 8007CFF4 0006C140 */  sll   $t8, $a2, 5
/* 07DBF8 8007CFF8 0007C940 */  sll   $t9, $a3, 5
/* 07DBFC 8007CFFC 25AD0001 */  addiu $t5, $t5, 1
/* 07DC00 8007D000 254E0002 */  addiu $t6, $t2, 2
/* 07DC04 8007D004 25440004 */  addiu $a0, $t2, 4
/* 07DC08 8007D008 29A10005 */  slti  $at, $t5, 5
/* 07DC0C 8007D00C 25290008 */  addiu $t1, $t1, 8
/* 07DC10 8007D010 A0770000 */  sb    $s7, ($v1)
/* 07DC14 8007D014 A0680001 */  sb    $t0, 1($v1)
/* 07DC18 8007D018 A06E0002 */  sb    $t6, 2($v1)
/* 07DC1C 8007D01C A06B0003 */  sb    $t3, 3($v1)
/* 07DC20 8007D020 A4780004 */  sh    $t8, 4($v1)
/* 07DC24 8007D024 A4790006 */  sh    $t9, 6($v1)
/* 07DC28 8007D028 A4780008 */  sh    $t8, 8($v1)
/* 07DC2C 8007D02C A460000A */  sh    $zero, 0xa($v1)
/* 07DC30 8007D030 A475000C */  sh    $s5, 0xc($v1)
/* 07DC34 8007D034 A460000E */  sh    $zero, 0xe($v1)
/* 07DC38 8007D038 A0770010 */  sb    $s7, 0x10($v1)
/* 07DC3C 8007D03C A0640011 */  sb    $a0, 0x11($v1)
/* 07DC40 8007D040 A0680012 */  sb    $t0, 0x12($v1)
/* 07DC44 8007D044 A06B0013 */  sb    $t3, 0x13($v1)
/* 07DC48 8007D048 A4750014 */  sh    $s5, 0x14($v1)
/* 07DC4C 8007D04C A4790016 */  sh    $t9, 0x16($v1)
/* 07DC50 8007D050 A4780018 */  sh    $t8, 0x18($v1)
/* 07DC54 8007D054 A479001A */  sh    $t9, 0x1a($v1)
/* 07DC58 8007D058 A475001C */  sh    $s5, 0x1c($v1)
/* 07DC5C 8007D05C A460001E */  sh    $zero, 0x1e($v1)
/* 07DC60 8007D060 24630020 */  addiu $v1, $v1, 0x20
/* 07DC64 8007D064 00805025 */  move  $t2, $a0
/* 07DC68 8007D068 26520001 */  addiu $s2, $s2, 1
/* 07DC6C 8007D06C 14200003 */  bnez  $at, .L8007D07C
/* 07DC70 8007D070 26730004 */   addiu $s3, $s3, 4
/* 07DC74 8007D074 00006825 */  move  $t5, $zero
/* 07DC78 8007D078 00005025 */  move  $t2, $zero
.L8007D07C:
/* 07DC7C 8007D07C 025E082A */  slt   $at, $s2, $fp
/* 07DC80 8007D080 1420FF7E */  bnez  $at, .L8007CE7C
/* 07DC84 8007D084 8FAE0044 */   lw    $t6, 0x44($sp)
.L8007D088:
/* 07DC88 8007D088 01202025 */  move  $a0, $t1
/* 07DC8C 8007D08C 3C0FE700 */  lui   $t7, 0xe700
/* 07DC90 8007D090 AC8F0000 */  sw    $t7, ($a0)
/* 07DC94 8007D094 AC800004 */  sw    $zero, 4($a0)
/* 07DC98 8007D098 25250008 */  addiu $a1, $t1, 8
/* 07DC9C 8007D09C 3C0EB800 */  lui   $t6, 0xb800
/* 07DCA0 8007D0A0 ACAE0000 */  sw    $t6, ($a1)
/* 07DCA4 8007D0A4 ACA00004 */  sw    $zero, 4($a1)
/* 07DCA8 8007D0A8 24A90008 */  addiu $t1, $a1, 8
/* 07DCAC 8007D0AC 3C018012 */  lui   $at, %hi(D_80126364) # $at, 0x8012
/* 07DCB0 8007D0B0 AC296364 */  sw    $t1, %lo(D_80126364)($at)
/* 07DCB4 8007D0B4 3C018012 */  lui   $at, %hi(D_80126360) # $at, 0x8012
/* 07DCB8 8007D0B8 8FBF002C */  lw    $ra, 0x2c($sp)
/* 07DCBC 8007D0BC AC226360 */  sw    $v0, %lo(D_80126360)($at)
/* 07DCC0 8007D0C0 3C018012 */  lui   $at, %hi(D_80126368) # $at, 0x8012
/* 07DCC4 8007D0C4 8FBE0028 */  lw    $fp, 0x28($sp)
/* 07DCC8 8007D0C8 8FB70024 */  lw    $s7, 0x24($sp)
/* 07DCCC 8007D0CC 8FB60020 */  lw    $s6, 0x20($sp)
/* 07DCD0 8007D0D0 8FB5001C */  lw    $s5, 0x1c($sp)
/* 07DCD4 8007D0D4 8FB40018 */  lw    $s4, 0x18($sp)
/* 07DCD8 8007D0D8 8FB30014 */  lw    $s3, 0x14($sp)
/* 07DCDC 8007D0DC 8FB20010 */  lw    $s2, 0x10($sp)
/* 07DCE0 8007D0E0 8FB1000C */  lw    $s1, 0xc($sp)
/* 07DCE4 8007D0E4 8FB00008 */  lw    $s0, 8($sp)
/* 07DCE8 8007D0E8 AC236368 */  sw    $v1, %lo(D_80126368)($at)
/* 07DCEC 8007D0EC 03E00008 */  jr    $ra
/* 07DCF0 8007D0F0 27BD0040 */   addiu $sp, $sp, 0x40

