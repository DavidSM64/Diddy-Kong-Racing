glabel render_file_select_menu
/* 08D974 8008CD74 27BDFF78 */  addiu $sp, $sp, -0x88
/* 08D978 8008CD78 3C0E8000 */  lui   $t6, %hi(osTvType) # $t6, 0x8000
/* 08D97C 8008CD7C 8DCE0300 */  lw    $t6, %lo(osTvType)($t6)
/* 08D980 8008CD80 AFBF0054 */  sw    $ra, 0x54($sp)
/* 08D984 8008CD84 AFB70050 */  sw    $s7, 0x50($sp)
/* 08D988 8008CD88 AFB6004C */  sw    $s6, 0x4c($sp)
/* 08D98C 8008CD8C AFB50048 */  sw    $s5, 0x48($sp)
/* 08D990 8008CD90 AFB40044 */  sw    $s4, 0x44($sp)
/* 08D994 8008CD94 AFB30040 */  sw    $s3, 0x40($sp)
/* 08D998 8008CD98 AFB2003C */  sw    $s2, 0x3c($sp)
/* 08D99C 8008CD9C AFB10038 */  sw    $s1, 0x38($sp)
/* 08D9A0 8008CDA0 AFB00034 */  sw    $s0, 0x34($sp)
/* 08D9A4 8008CDA4 15C00003 */  bnez  $t6, .L8008CDB4
/* 08D9A8 8008CDA8 AFA40088 */   sw    $a0, 0x88($sp)
/* 08D9AC 8008CDAC 10000002 */  b     .L8008CDB8
/* 08D9B0 8008CDB0 2416000C */   li    $s6, 12
.L8008CDB4:
/* 08D9B4 8008CDB4 0000B025 */  move  $s6, $zero
.L8008CDB8:
/* 08D9B8 8008CDB8 0C026F57 */  jal   func_8009BD5C
/* 08D9BC 8008CDBC 00000000 */   nop   
/* 08D9C0 8008CDC0 3C178012 */  lui   $s7, %hi(D_801263A0) # $s7, 0x8012
/* 08D9C4 8008CDC4 26F763A0 */  addiu $s7, %lo(D_801263A0) # addiu $s7, $s7, 0x63a0
/* 08D9C8 8008CDC8 3C058012 */  lui   $a1, %hi(D_801263A8) # $a1, 0x8012
/* 08D9CC 8008CDCC 24A563A8 */  addiu $a1, %lo(D_801263A8) # addiu $a1, $a1, 0x63a8
/* 08D9D0 8008CDD0 0C019FCB */  jal   func_80067F2C
/* 08D9D4 8008CDD4 02E02025 */   move  $a0, $s7
/* 08D9D8 8008CDD8 3C118012 */  lui   $s1, %hi(gSavefileInfo) # $s1, 0x8012
/* 08D9DC 8008CDDC 3C10800E */  lui   $s0, %hi(D_800E03CC) # $s0, 0x800e
/* 08D9E0 8008CDE0 3C158012 */  lui   $s5, %hi(D_80126550) # $s5, 0x8012
/* 08D9E4 8008CDE4 3C13B0E0 */  lui   $s3, (0xB0E0C0FF >> 16) # lui $s3, 0xb0e0
/* 08D9E8 8008CDE8 3C12800E */  lui   $s2, %hi(gIsInAdventureTwo) # $s2, 0x800e
/* 08D9EC 8008CDEC 2652F494 */  addiu $s2, %lo(gIsInAdventureTwo) # addiu $s2, $s2, -0xb6c
/* 08D9F0 8008CDF0 3673C0FF */  ori   $s3, (0xB0E0C0FF & 0xFFFF) # ori $s3, $s3, 0xc0ff
/* 08D9F4 8008CDF4 26B56550 */  addiu $s5, %lo(D_80126550) # addiu $s5, $s5, 0x6550
/* 08D9F8 8008CDF8 261003CC */  addiu $s0, %lo(D_800E03CC) # addiu $s0, $s0, 0x3cc
/* 08D9FC 8008CDFC 263164A0 */  addiu $s1, %lo(gSavefileInfo) # addiu $s1, $s1, 0x64a0
/* 08DA00 8008CE00 24140078 */  li    $s4, 120
.L8008CE04:
/* 08DA04 8008CE04 8E4F0000 */  lw    $t7, ($s2)
/* 08DA08 8008CE08 92380000 */  lbu   $t8, ($s1)
/* 08DA0C 8008CE0C 00002025 */  move  $a0, $zero
/* 08DA10 8008CE10 11F80005 */  beq   $t7, $t8, .L8008CE28
/* 08DA14 8008CE14 00000000 */   nop   
/* 08DA18 8008CE18 92390001 */  lbu   $t9, 1($s1)
/* 08DA1C 8008CE1C 3C026A90 */  lui   $v0, (0x6A9073FF >> 16) # lui $v0, 0x6a90
/* 08DA20 8008CE20 17200003 */  bnez  $t9, .L8008CE30
/* 08DA24 8008CE24 344273FF */   ori   $v0, (0x6A9073FF & 0xFFFF) # ori $v0, $v0, 0x73ff
.L8008CE28:
/* 08DA28 8008CE28 10000001 */  b     .L8008CE30
/* 08DA2C 8008CE2C 02601025 */   move  $v0, $s3
.L8008CE30:
/* 08DA30 8008CE30 86050000 */  lh    $a1, ($s0)
/* 08DA34 8008CE34 86080002 */  lh    $t0, 2($s0)
/* 08DA38 8008CE38 86090006 */  lh    $t1, 6($s0)
/* 08DA3C 8008CE3C 860A0008 */  lh    $t2, 8($s0)
/* 08DA40 8008CE40 860B000A */  lh    $t3, 0xa($s0)
/* 08DA44 8008CE44 8EAC010C */  lw    $t4, 0x10c($s5)
/* 08DA48 8008CE48 86070004 */  lh    $a3, 4($s0)
/* 08DA4C 8008CE4C AFA2001C */  sw    $v0, 0x1c($sp)
/* 08DA50 8008CE50 24A5FF60 */  addiu $a1, $a1, -0xa0
/* 08DA54 8008CE54 02883023 */  subu  $a2, $s4, $t0
/* 08DA58 8008CE58 AFA90010 */  sw    $t1, 0x10($sp)
/* 08DA5C 8008CE5C AFAA0014 */  sw    $t2, 0x14($sp)
/* 08DA60 8008CE60 AFAB0018 */  sw    $t3, 0x18($sp)
/* 08DA64 8008CE64 0C020160 */  jal   func_80080580
/* 08DA68 8008CE68 AFAC0020 */   sw    $t4, 0x20($sp)
/* 08DA6C 8008CE6C 3C0D800E */  lui   $t5, %hi(D_800E03FC) # $t5, 0x800e
/* 08DA70 8008CE70 25AD03FC */  addiu $t5, %lo(D_800E03FC) # addiu $t5, $t5, 0x3fc
/* 08DA74 8008CE74 26100010 */  addiu $s0, $s0, 0x10
/* 08DA78 8008CE78 020D082B */  sltu  $at, $s0, $t5
/* 08DA7C 8008CE7C 1420FFE1 */  bnez  $at, .L8008CE04
/* 08DA80 8008CE80 2631000C */   addiu $s1, $s1, 0xc
/* 08DA84 8008CE84 0C0202F2 */  jal   func_80080BC8
/* 08DA88 8008CE88 02E02025 */   move  $a0, $s7
/* 08DA8C 8008CE8C 3C0E8012 */  lui   $t6, %hi(D_801263D8) # $t6, 0x8012
/* 08DA90 8008CE90 8DCE63D8 */  lw    $t6, %lo(D_801263D8)($t6)
/* 08DA94 8008CE94 00000000 */  nop   
/* 08DA98 8008CE98 15C00097 */  bnez  $t6, .L8008D0F8
/* 08DA9C 8008CE9C 00000000 */   nop   
/* 08DAA0 8008CEA0 0C0310BB */  jal   set_text_font
/* 08DAA4 8008CEA4 24040002 */   li    $a0, 2
/* 08DAA8 8008CEA8 00002025 */  move  $a0, $zero
/* 08DAAC 8008CEAC 00002825 */  move  $a1, $zero
/* 08DAB0 8008CEB0 00003025 */  move  $a2, $zero
/* 08DAB4 8008CEB4 0C0310F3 */  jal   set_text_background_color
/* 08DAB8 8008CEB8 00003825 */   move  $a3, $zero
/* 08DABC 8008CEBC 3C118012 */  lui   $s1, %hi(gSavefileInfo) # $s1, 0x8012
/* 08DAC0 8008CEC0 3C10800E */  lui   $s0, %hi(D_800E03CC) # $s0, 0x800e
/* 08DAC4 8008CEC4 3C14800E */  lui   $s4, %hi(D_800E03FC) # $s4, 0x800e
/* 08DAC8 8008CEC8 3C13800E */  lui   $s3, %hi(gMenuImageStack) # $s3, 0x800e
/* 08DACC 8008CECC 2673F75C */  addiu $s3, %lo(gMenuImageStack) # addiu $s3, $s3, -0x8a4
/* 08DAD0 8008CED0 269403FC */  addiu $s4, %lo(D_800E03FC) # addiu $s4, $s4, 0x3fc
/* 08DAD4 8008CED4 261003CC */  addiu $s0, %lo(D_800E03CC) # addiu $s0, $s0, 0x3cc
/* 08DAD8 8008CED8 263164A0 */  addiu $s1, %lo(gSavefileInfo) # addiu $s1, $s1, 0x64a0
/* 08DADC 8008CEDC 2415000A */  li    $s5, 10
.L8008CEE0:
/* 08DAE0 8008CEE0 922F0001 */  lbu   $t7, 1($s1)
/* 08DAE4 8008CEE4 240400FF */  li    $a0, 255
/* 08DAE8 8008CEE8 11E0006B */  beqz  $t7, .L8008D098
/* 08DAEC 8008CEEC 240500FF */   li    $a1, 255
/* 08DAF0 8008CEF0 00002025 */  move  $a0, $zero
/* 08DAF4 8008CEF4 0C01EFC7 */  jal   func_8007BF1C
/* 08DAF8 8008CEF8 2412000B */   li    $s2, 11
/* 08DAFC 8008CEFC 92380000 */  lbu   $t8, ($s1)
/* 08DB00 8008CF00 00003825 */  move  $a3, $zero
/* 08DB04 8008CF04 13000002 */  beqz  $t8, .L8008CF10
/* 08DB08 8008CF08 240B0080 */   li    $t3, 128
/* 08DB0C 8008CF0C 2412000C */  li    $s2, 12
.L8008CF10:
/* 08DB10 8008CF10 86990004 */  lh    $t9, 4($s4)
/* 08DB14 8008CF14 86080000 */  lh    $t0, ($s0)
/* 08DB18 8008CF18 86890006 */  lh    $t1, 6($s4)
/* 08DB1C 8008CF1C 860A0002 */  lh    $t2, 2($s0)
/* 08DB20 8008CF20 02402025 */  move  $a0, $s2
/* 08DB24 8008CF24 AFA00010 */  sw    $zero, 0x10($sp)
/* 08DB28 8008CF28 AFA00014 */  sw    $zero, 0x14($sp)
/* 08DB2C 8008CF2C AFAB0018 */  sw    $t3, 0x18($sp)
/* 08DB30 8008CF30 03282821 */  addu  $a1, $t9, $t0
/* 08DB34 8008CF34 0C02330A */  jal   render_menu_image
/* 08DB38 8008CF38 012A3021 */   addu  $a2, $t1, $t2
/* 08DB3C 8008CF3C 0C01A142 */  jal   func_80068508
/* 08DB40 8008CF40 24040001 */   li    $a0, 1
/* 08DB44 8008CF44 962C0002 */  lhu   $t4, 2($s1)
/* 08DB48 8008CF48 8E6E0000 */  lw    $t6, ($s3)
/* 08DB4C 8008CF4C 0195001A */  div   $zero, $t4, $s5
/* 08DB50 8008CF50 24090080 */  li    $t1, 128
/* 08DB54 8008CF54 16A00002 */  bnez  $s5, .L8008CF60
/* 08DB58 8008CF58 00000000 */   nop   
/* 08DB5C 8008CF5C 0007000D */  break 7
.L8008CF60:
/* 08DB60 8008CF60 2401FFFF */  li    $at, -1
/* 08DB64 8008CF64 16A10004 */  bne   $s5, $at, .L8008CF78
/* 08DB68 8008CF68 3C018000 */   lui   $at, 0x8000
/* 08DB6C 8008CF6C 15810002 */  bne   $t4, $at, .L8008CF78
/* 08DB70 8008CF70 00000000 */   nop   
/* 08DB74 8008CF74 0006000D */  break 6
.L8008CF78:
/* 08DB78 8008CF78 00002025 */  move  $a0, $zero
/* 08DB7C 8008CF7C 00003825 */  move  $a3, $zero
/* 08DB80 8008CF80 00006812 */  mflo  $t5
/* 08DB84 8008CF84 A5CD0018 */  sh    $t5, 0x18($t6)
/* 08DB88 8008CF88 86180000 */  lh    $t8, ($s0)
/* 08DB8C 8008CF8C 868F000C */  lh    $t7, 0xc($s4)
/* 08DB90 8008CF90 86080002 */  lh    $t0, 2($s0)
/* 08DB94 8008CF94 8699000E */  lh    $t9, 0xe($s4)
/* 08DB98 8008CF98 01F82821 */  addu  $a1, $t7, $t8
/* 08DB9C 8008CF9C 24A5FFFA */  addiu $a1, $a1, -6
/* 08DBA0 8008CFA0 AFA90018 */  sw    $t1, 0x18($sp)
/* 08DBA4 8008CFA4 AFA00014 */  sw    $zero, 0x14($sp)
/* 08DBA8 8008CFA8 AFA00010 */  sw    $zero, 0x10($sp)
/* 08DBAC 8008CFAC 0C02330A */  jal   render_menu_image
/* 08DBB0 8008CFB0 03283021 */   addu  $a2, $t9, $t0
/* 08DBB4 8008CFB4 962A0002 */  lhu   $t2, 2($s1)
/* 08DBB8 8008CFB8 8E6C0000 */  lw    $t4, ($s3)
/* 08DBBC 8008CFBC 0155001A */  div   $zero, $t2, $s5
/* 08DBC0 8008CFC0 24190080 */  li    $t9, 128
/* 08DBC4 8008CFC4 16A00002 */  bnez  $s5, .L8008CFD0
/* 08DBC8 8008CFC8 00000000 */   nop   
/* 08DBCC 8008CFCC 0007000D */  break 7
.L8008CFD0:
/* 08DBD0 8008CFD0 2401FFFF */  li    $at, -1
/* 08DBD4 8008CFD4 16A10004 */  bne   $s5, $at, .L8008CFE8
/* 08DBD8 8008CFD8 3C018000 */   lui   $at, 0x8000
/* 08DBDC 8008CFDC 15410002 */  bne   $t2, $at, .L8008CFE8
/* 08DBE0 8008CFE0 00000000 */   nop   
/* 08DBE4 8008CFE4 0006000D */  break 6
.L8008CFE8:
/* 08DBE8 8008CFE8 00002025 */  move  $a0, $zero
/* 08DBEC 8008CFEC 00003825 */  move  $a3, $zero
/* 08DBF0 8008CFF0 00005810 */  mfhi  $t3
/* 08DBF4 8008CFF4 A58B0018 */  sh    $t3, 0x18($t4)
/* 08DBF8 8008CFF8 860E0000 */  lh    $t6, ($s0)
/* 08DBFC 8008CFFC 868D000C */  lh    $t5, 0xc($s4)
/* 08DC00 8008D000 86180002 */  lh    $t8, 2($s0)
/* 08DC04 8008D004 868F000E */  lh    $t7, 0xe($s4)
/* 08DC08 8008D008 01AE2821 */  addu  $a1, $t5, $t6
/* 08DC0C 8008D00C 24A50006 */  addiu $a1, $a1, 6
/* 08DC10 8008D010 AFB90018 */  sw    $t9, 0x18($sp)
/* 08DC14 8008D014 AFA00014 */  sw    $zero, 0x14($sp)
/* 08DC18 8008D018 AFA00010 */  sw    $zero, 0x10($sp)
/* 08DC1C 8008D01C 0C02330A */  jal   render_menu_image
/* 08DC20 8008D020 01F83021 */   addu  $a2, $t7, $t8
/* 08DC24 8008D024 0C01A142 */  jal   func_80068508
/* 08DC28 8008D028 00002025 */   move  $a0, $zero
/* 08DC2C 8008D02C 24020040 */  li    $v0, 64
/* 08DC30 8008D030 3C01800E */  lui   $at, %hi(sMenuGuiColourG) # $at, 0x800e
/* 08DC34 8008D034 A022F4A8 */  sb    $v0, %lo(sMenuGuiColourG)($at)
/* 08DC38 8008D038 3C01800E */  lui   $at, %hi(sMenuGuiColourB) # $at, 0x800e
/* 08DC3C 8008D03C A022F4AC */  sb    $v0, %lo(sMenuGuiColourB)($at)
/* 08DC40 8008D040 860B0002 */  lh    $t3, 2($s0)
/* 08DC44 8008D044 868A0012 */  lh    $t2, 0x12($s4)
/* 08DC48 8008D048 86090000 */  lh    $t1, ($s0)
/* 08DC4C 8008D04C 86880010 */  lh    $t0, 0x10($s4)
/* 08DC50 8008D050 240C0080 */  li    $t4, 128
/* 08DC54 8008D054 AFAC0018 */  sw    $t4, 0x18($sp)
/* 08DC58 8008D058 02A02025 */  move  $a0, $s5
/* 08DC5C 8008D05C 00003825 */  move  $a3, $zero
/* 08DC60 8008D060 AFA00010 */  sw    $zero, 0x10($sp)
/* 08DC64 8008D064 AFA00014 */  sw    $zero, 0x14($sp)
/* 08DC68 8008D068 014B3021 */  addu  $a2, $t2, $t3
/* 08DC6C 8008D06C 0C02330A */  jal   render_menu_image
/* 08DC70 8008D070 01092821 */   addu  $a1, $t0, $t1
/* 08DC74 8008D074 240200FF */  li    $v0, 255
/* 08DC78 8008D078 3C01800E */  lui   $at, %hi(sMenuGuiColourG) # $at, 0x800e
/* 08DC7C 8008D07C A022F4A8 */  sb    $v0, %lo(sMenuGuiColourG)($at)
/* 08DC80 8008D080 3C01800E */  lui   $at, %hi(sMenuGuiColourB) # $at, 0x800e
/* 08DC84 8008D084 A022F4AC */  sb    $v0, %lo(sMenuGuiColourB)($at)
/* 08DC88 8008D088 0C01EFC7 */  jal   func_8007BF1C
/* 08DC8C 8008D08C 24040001 */   li    $a0, 1
/* 08DC90 8008D090 10000014 */  b     .L8008D0E4
/* 08DC94 8008D094 00000000 */   nop   
.L8008D098:
/* 08DC98 8008D098 240D00FF */  li    $t5, 255
/* 08DC9C 8008D09C AFAD0010 */  sw    $t5, 0x10($sp)
/* 08DCA0 8008D0A0 240600FF */  li    $a2, 255
/* 08DCA4 8008D0A4 0C0310E1 */  jal   set_text_color
/* 08DCA8 8008D0A8 24070040 */   li    $a3, 64
/* 08DCAC 8008D0AC 3C09800E */  lui   $t1, %hi(gMenuText) # $t1, 0x800e
/* 08DCB0 8008D0B0 8D29F4A0 */  lw    $t1, %lo(gMenuText)($t1)
/* 08DCB4 8008D0B4 8698000A */  lh    $t8, 0xa($s4)
/* 08DCB8 8008D0B8 86190002 */  lh    $t9, 2($s0)
/* 08DCBC 8008D0BC 868E0008 */  lh    $t6, 8($s4)
/* 08DCC0 8008D0C0 860F0000 */  lh    $t7, ($s0)
/* 08DCC4 8008D0C4 240A000C */  li    $t2, 12
/* 08DCC8 8008D0C8 8D27012C */  lw    $a3, 0x12c($t1)
/* 08DCCC 8008D0CC 03194021 */  addu  $t0, $t8, $t9
/* 08DCD0 8008D0D0 01163021 */  addu  $a2, $t0, $s6
/* 08DCD4 8008D0D4 AFAA0010 */  sw    $t2, 0x10($sp)
/* 08DCD8 8008D0D8 02E02025 */  move  $a0, $s7
/* 08DCDC 8008D0DC 0C031110 */  jal   draw_text
/* 08DCE0 8008D0E0 01CF2821 */   addu  $a1, $t6, $t7
.L8008D0E4:
/* 08DCE4 8008D0E4 3C0B800E */  lui   $t3, %hi(D_800E03FC) # $t3, 0x800e
/* 08DCE8 8008D0E8 256B03FC */  addiu $t3, %lo(D_800E03FC) # addiu $t3, $t3, 0x3fc
/* 08DCEC 8008D0EC 26100010 */  addiu $s0, $s0, 0x10
/* 08DCF0 8008D0F0 160BFF7B */  bne   $s0, $t3, .L8008CEE0
/* 08DCF4 8008D0F4 2631000C */   addiu $s1, $s1, 0xc
.L8008D0F8:
/* 08DCF8 8008D0F8 3C028012 */  lui   $v0, %hi(D_801263BC) # $v0, 0x8012
/* 08DCFC 8008D0FC 8C4263BC */  lw    $v0, %lo(D_801263BC)($v0)
/* 08DD00 8008D100 3C14800E */  lui   $s4, %hi(D_800E03FC) # $s4, 0x800e
/* 08DD04 8008D104 000260C0 */  sll   $t4, $v0, 3
/* 08DD08 8008D108 29810100 */  slti  $at, $t4, 0x100
/* 08DD0C 8008D10C 269403FC */  addiu $s4, %lo(D_800E03FC) # addiu $s4, $s4, 0x3fc
/* 08DD10 8008D110 14200003 */  bnez  $at, .L8008D120
/* 08DD14 8008D114 01801025 */   move  $v0, $t4
/* 08DD18 8008D118 240D01FF */  li    $t5, 511
/* 08DD1C 8008D11C 01AC1023 */  subu  $v0, $t5, $t4
.L8008D120:
/* 08DD20 8008D120 00002025 */  move  $a0, $zero
/* 08DD24 8008D124 0C0310BB */  jal   set_text_font
/* 08DD28 8008D128 AFA2007C */   sw    $v0, 0x7c($sp)
/* 08DD2C 8008D12C 00002025 */  move  $a0, $zero
/* 08DD30 8008D130 00002825 */  move  $a1, $zero
/* 08DD34 8008D134 00003025 */  move  $a2, $zero
/* 08DD38 8008D138 0C0310F3 */  jal   set_text_background_color
/* 08DD3C 8008D13C 00003825 */   move  $a3, $zero
/* 08DD40 8008D140 240E00FF */  li    $t6, 255
/* 08DD44 8008D144 AFAE0010 */  sw    $t6, 0x10($sp)
/* 08DD48 8008D148 240400FF */  li    $a0, 255
/* 08DD4C 8008D14C 240500FF */  li    $a1, 255
/* 08DD50 8008D150 240600FF */  li    $a2, 255
/* 08DD54 8008D154 0C0310E1 */  jal   set_text_color
/* 08DD58 8008D158 00003825 */   move  $a3, $zero
/* 08DD5C 8008D15C 00009825 */  move  $s3, $zero
/* 08DD60 8008D160 27B50064 */  addiu $s5, $sp, 0x64
.L8008D164:
/* 08DD64 8008D164 3C0F8012 */  lui   $t7, %hi(D_80126484) # $t7, 0x8012
/* 08DD68 8008D168 8DEF6484 */  lw    $t7, %lo(D_80126484)($t7)
/* 08DD6C 8008D16C 00009025 */  move  $s2, $zero
/* 08DD70 8008D170 11E00014 */  beqz  $t7, .L8008D1C4
/* 08DD74 8008D174 3C088012 */   lui   $t0, %hi(D_80126488) # $t0, 0x8012
/* 08DD78 8008D178 3C028012 */  lui   $v0, %hi(D_80126494) # $v0, 0x8012
/* 08DD7C 8008D17C 8C426494 */  lw    $v0, %lo(D_80126494)($v0)
/* 08DD80 8008D180 3C188012 */  lui   $t8, %hi(D_8012648C) # $t8, 0x8012
/* 08DD84 8008D184 14400007 */  bnez  $v0, .L8008D1A4
/* 08DD88 8008D188 00000000 */   nop   
/* 08DD8C 8008D18C 8F18648C */  lw    $t8, %lo(D_8012648C)($t8)
/* 08DD90 8008D190 00000000 */  nop   
/* 08DD94 8008D194 16780003 */  bne   $s3, $t8, .L8008D1A4
/* 08DD98 8008D198 00000000 */   nop   
/* 08DD9C 8008D19C 1000001C */  b     .L8008D210
/* 08DDA0 8008D1A0 24120001 */   li    $s2, 1
.L8008D1A4:
/* 08DDA4 8008D1A4 1840001A */  blez  $v0, .L8008D210
/* 08DDA8 8008D1A8 3C198012 */   lui   $t9, %hi(D_80126490) # $t9, 0x8012
/* 08DDAC 8008D1AC 8F396490 */  lw    $t9, %lo(D_80126490)($t9)
/* 08DDB0 8008D1B0 00000000 */  nop   
/* 08DDB4 8008D1B4 16790016 */  bne   $s3, $t9, .L8008D210
/* 08DDB8 8008D1B8 00000000 */   nop   
/* 08DDBC 8008D1BC 10000014 */  b     .L8008D210
/* 08DDC0 8008D1C0 24120001 */   li    $s2, 1
.L8008D1C4:
/* 08DDC4 8008D1C4 8D086488 */  lw    $t0, %lo(D_80126488)($t0)
/* 08DDC8 8008D1C8 3C098012 */  lui   $t1, %hi(D_8012648C) # $t1, 0x8012
/* 08DDCC 8008D1CC 11000007 */  beqz  $t0, .L8008D1EC
/* 08DDD0 8008D1D0 3C0A8012 */   lui   $t2, %hi(D_801263E0) # $t2, 0x8012
/* 08DDD4 8008D1D4 8D29648C */  lw    $t1, %lo(D_8012648C)($t1)
/* 08DDD8 8008D1D8 00000000 */  nop   
/* 08DDDC 8008D1DC 1669000C */  bne   $s3, $t1, .L8008D210
/* 08DDE0 8008D1E0 00000000 */   nop   
/* 08DDE4 8008D1E4 1000000A */  b     .L8008D210
/* 08DDE8 8008D1E8 24120001 */   li    $s2, 1
.L8008D1EC:
/* 08DDEC 8008D1EC 8D4A63E0 */  lw    $t2, %lo(D_801263E0)($t2)
/* 08DDF0 8008D1F0 3C0B800E */  lui   $t3, %hi(gSaveFileIndex) # $t3, 0x800e
/* 08DDF4 8008D1F4 15400006 */  bnez  $t2, .L8008D210
/* 08DDF8 8008D1F8 00000000 */   nop   
/* 08DDFC 8008D1FC 8D6BF4CC */  lw    $t3, %lo(gSaveFileIndex)($t3)
/* 08DE00 8008D200 00000000 */  nop   
/* 08DE04 8008D204 166B0002 */  bne   $s3, $t3, .L8008D210
/* 08DE08 8008D208 00000000 */   nop   
/* 08DE0C 8008D20C 24120001 */  li    $s2, 1
.L8008D210:
/* 08DE10 8008D210 12400018 */  beqz  $s2, .L8008D274
/* 08DE14 8008D214 02E02025 */   move  $a0, $s7
/* 08DE18 8008D218 3C0D800E */  lui   $t5, %hi(D_800E03CC) # $t5, 0x800e
/* 08DE1C 8008D21C 25AD03CC */  addiu $t5, %lo(D_800E03CC) # addiu $t5, $t5, 0x3cc
/* 08DE20 8008D220 00136100 */  sll   $t4, $s3, 4
/* 08DE24 8008D224 018D8021 */  addu  $s0, $t4, $t5
/* 08DE28 8008D228 8FA2007C */  lw    $v0, 0x7c($sp)
/* 08DE2C 8008D22C 2401FF00 */  li    $at, -256
/* 08DE30 8008D230 00414025 */  or    $t0, $v0, $at
/* 08DE34 8008D234 860E0002 */  lh    $t6, 2($s0)
/* 08DE38 8008D238 860F0006 */  lh    $t7, 6($s0)
/* 08DE3C 8008D23C 86180008 */  lh    $t8, 8($s0)
/* 08DE40 8008D240 8619000A */  lh    $t9, 0xa($s0)
/* 08DE44 8008D244 86050000 */  lh    $a1, ($s0)
/* 08DE48 8008D248 86070004 */  lh    $a3, 4($s0)
/* 08DE4C 8008D24C 01001025 */  move  $v0, $t0
/* 08DE50 8008D250 AFA8001C */  sw    $t0, 0x1c($sp)
/* 08DE54 8008D254 AFA80020 */  sw    $t0, 0x20($sp)
/* 08DE58 8008D258 AFA80024 */  sw    $t0, 0x24($sp)
/* 08DE5C 8008D25C AFA80028 */  sw    $t0, 0x28($sp)
/* 08DE60 8008D260 01D63021 */  addu  $a2, $t6, $s6
/* 08DE64 8008D264 AFAF0010 */  sw    $t7, 0x10($sp)
/* 08DE68 8008D268 AFB80014 */  sw    $t8, 0x14($sp)
/* 08DE6C 8008D26C 0C0203A4 */  jal   func_80080E90
/* 08DE70 8008D270 AFB90018 */   sw    $t9, 0x18($sp)
.L8008D274:
/* 08DE74 8008D274 3C098012 */  lui   $t1, %hi(D_80126CC0) # $t1, 0x8012
/* 08DE78 8008D278 8D296CC0 */  lw    $t1, %lo(D_80126CC0)($t1)
/* 08DE7C 8008D27C 3C0A800E */  lui   $t2, %hi(gSaveFileIndex) # $t2, 0x800e
/* 08DE80 8008D280 11200004 */  beqz  $t1, .L8008D294
/* 08DE84 8008D284 00135880 */   sll   $t3, $s3, 2
/* 08DE88 8008D288 8D4AF4CC */  lw    $t2, %lo(gSaveFileIndex)($t2)
/* 08DE8C 8008D28C 00000000 */  nop   
/* 08DE90 8008D290 126A0021 */  beq   $s3, $t2, .L8008D318
.L8008D294:
/* 08DE94 8008D294 01735823 */   subu  $t3, $t3, $s3
/* 08DE98 8008D298 3C0C8012 */  lui   $t4, %hi(gSavefileInfo) # $t4, 0x8012
/* 08DE9C 8008D29C 258C64A0 */  addiu $t4, %lo(gSavefileInfo) # addiu $t4, $t4, 0x64a0
/* 08DEA0 8008D2A0 000B5880 */  sll   $t3, $t3, 2
/* 08DEA4 8008D2A4 016C8821 */  addu  $s1, $t3, $t4
/* 08DEA8 8008D2A8 26240004 */  addiu $a0, $s1, 4
/* 08DEAC 8008D2AC 0C025DF4 */  jal   trim_filename_string
/* 08DEB0 8008D2B0 02A02825 */   move  $a1, $s5
/* 08DEB4 8008D2B4 922D0001 */  lbu   $t5, 1($s1)
/* 08DEB8 8008D2B8 00137080 */  sll   $t6, $s3, 2
/* 08DEBC 8008D2BC 15A00005 */  bnez  $t5, .L8008D2D4
/* 08DEC0 8008D2C0 3C04800E */   lui   $a0, %hi(gFilenames) # $a0, 0x800e
/* 08DEC4 8008D2C4 008E2021 */  addu  $a0, $a0, $t6
/* 08DEC8 8008D2C8 8C8403B0 */  lw    $a0, %lo(gFilenames)($a0)
/* 08DECC 8008D2CC 0C025DF4 */  jal   trim_filename_string
/* 08DED0 8008D2D0 02A02825 */   move  $a1, $s5
.L8008D2D4:
/* 08DED4 8008D2D4 12A00010 */  beqz  $s5, .L8008D318
/* 08DED8 8008D2D8 02E02025 */   move  $a0, $s7
/* 08DEDC 8008D2DC 3C18800E */  lui   $t8, %hi(D_800E03CC) # $t8, 0x800e
/* 08DEE0 8008D2E0 271803CC */  addiu $t8, %lo(D_800E03CC) # addiu $t8, $t8, 0x3cc
/* 08DEE4 8008D2E4 00137900 */  sll   $t7, $s3, 4
/* 08DEE8 8008D2E8 01F88021 */  addu  $s0, $t7, $t8
/* 08DEEC 8008D2EC 860A0002 */  lh    $t2, 2($s0)
/* 08DEF0 8008D2F0 86890002 */  lh    $t1, 2($s4)
/* 08DEF4 8008D2F4 86080000 */  lh    $t0, ($s0)
/* 08DEF8 8008D2F8 86990000 */  lh    $t9, ($s4)
/* 08DEFC 8008D2FC 240C000C */  li    $t4, 12
/* 08DF00 8008D300 012A5821 */  addu  $t3, $t1, $t2
/* 08DF04 8008D304 01763021 */  addu  $a2, $t3, $s6
/* 08DF08 8008D308 AFAC0010 */  sw    $t4, 0x10($sp)
/* 08DF0C 8008D30C 02A03825 */  move  $a3, $s5
/* 08DF10 8008D310 0C031110 */  jal   draw_text
/* 08DF14 8008D314 03282821 */   addu  $a1, $t9, $t0
.L8008D318:
/* 08DF18 8008D318 26730001 */  addiu $s3, $s3, 1
/* 08DF1C 8008D31C 24010003 */  li    $at, 3
/* 08DF20 8008D320 1661FF90 */  bne   $s3, $at, .L8008D164
/* 08DF24 8008D324 00000000 */   nop   
/* 08DF28 8008D328 0C0310BB */  jal   set_text_font
/* 08DF2C 8008D32C 24040002 */   li    $a0, 2
/* 08DF30 8008D330 240D0080 */  li    $t5, 128
/* 08DF34 8008D334 AFAD0010 */  sw    $t5, 0x10($sp)
/* 08DF38 8008D338 00002025 */  move  $a0, $zero
/* 08DF3C 8008D33C 00002825 */  move  $a1, $zero
/* 08DF40 8008D340 00003025 */  move  $a2, $zero
/* 08DF44 8008D344 0C0310E1 */  jal   set_text_color
/* 08DF48 8008D348 240700FF */   li    $a3, 255
/* 08DF4C 8008D34C 3C0E800E */  lui   $t6, %hi(gMenuText) # $t6, 0x800e
/* 08DF50 8008D350 8DCEF4A0 */  lw    $t6, %lo(gMenuText)($t6)
/* 08DF54 8008D354 240F0004 */  li    $t7, 4
/* 08DF58 8008D358 8DC70130 */  lw    $a3, 0x130($t6)
/* 08DF5C 8008D35C AFAF0010 */  sw    $t7, 0x10($sp)
/* 08DF60 8008D360 02E02025 */  move  $a0, $s7
/* 08DF64 8008D364 240500A1 */  li    $a1, 161
/* 08DF68 8008D368 0C031110 */  jal   draw_text
/* 08DF6C 8008D36C 24060013 */   li    $a2, 19
/* 08DF70 8008D370 241800FF */  li    $t8, 255
/* 08DF74 8008D374 AFB80010 */  sw    $t8, 0x10($sp)
/* 08DF78 8008D378 240400FF */  li    $a0, 255
/* 08DF7C 8008D37C 240500FF */  li    $a1, 255
/* 08DF80 8008D380 240600FF */  li    $a2, 255
/* 08DF84 8008D384 0C0310E1 */  jal   set_text_color
/* 08DF88 8008D388 00003825 */   move  $a3, $zero
/* 08DF8C 8008D38C 3C19800E */  lui   $t9, %hi(gMenuText) # $t9, 0x800e
/* 08DF90 8008D390 8F39F4A0 */  lw    $t9, %lo(gMenuText)($t9)
/* 08DF94 8008D394 24080004 */  li    $t0, 4
/* 08DF98 8008D398 8F270130 */  lw    $a3, 0x130($t9)
/* 08DF9C 8008D39C AFA80010 */  sw    $t0, 0x10($sp)
/* 08DFA0 8008D3A0 02E02025 */  move  $a0, $s7
/* 08DFA4 8008D3A4 240500A0 */  li    $a1, 160
/* 08DFA8 8008D3A8 0C031110 */  jal   draw_text
/* 08DFAC 8008D3AC 24060010 */   li    $a2, 16
/* 08DFB0 8008D3B0 240900FF */  li    $t1, 255
/* 08DFB4 8008D3B4 AFA90010 */  sw    $t1, 0x10($sp)
/* 08DFB8 8008D3B8 240400FF */  li    $a0, 255
/* 08DFBC 8008D3BC 240500FF */  li    $a1, 255
/* 08DFC0 8008D3C0 240600FF */  li    $a2, 255
/* 08DFC4 8008D3C4 0C0310E1 */  jal   set_text_color
/* 08DFC8 8008D3C8 00003825 */   move  $a3, $zero
/* 08DFCC 8008D3CC 3C0A8012 */  lui   $t2, %hi(D_80126484) # $t2, 0x8012
/* 08DFD0 8008D3D0 8D4A6484 */  lw    $t2, %lo(D_80126484)($t2)
/* 08DFD4 8008D3D4 26D600BB */  addiu $s6, $s6, 0xbb
/* 08DFD8 8008D3D8 1140002B */  beqz  $t2, .L8008D488
/* 08DFDC 8008D3DC 3C188012 */   lui   $t8, %hi(D_80126488) # $t8, 0x8012
/* 08DFE0 8008D3E0 3C028012 */  lui   $v0, %hi(D_80126494) # $v0, 0x8012
/* 08DFE4 8008D3E4 8C426494 */  lw    $v0, %lo(D_80126494)($v0)
/* 08DFE8 8008D3E8 24010001 */  li    $at, 1
/* 08DFEC 8008D3EC 1440000E */  bnez  $v0, .L8008D428
/* 08DFF0 8008D3F0 00000000 */   nop   
/* 08DFF4 8008D3F4 0C0310BB */  jal   set_text_font
/* 08DFF8 8008D3F8 00002025 */   move  $a0, $zero
/* 08DFFC 8008D3FC 3C0B800E */  lui   $t3, %hi(gMenuText) # $t3, 0x800e
/* 08E000 8008D400 8D6BF4A0 */  lw    $t3, %lo(gMenuText)($t3)
/* 08E004 8008D404 240C000C */  li    $t4, 12
/* 08E008 8008D408 8D670134 */  lw    $a3, 0x134($t3)
/* 08E00C 8008D40C AFAC0010 */  sw    $t4, 0x10($sp)
/* 08E010 8008D410 02E02025 */  move  $a0, $s7
/* 08E014 8008D414 240500A0 */  li    $a1, 160
/* 08E018 8008D418 0C031110 */  jal   draw_text
/* 08E01C 8008D41C 02C03025 */   move  $a2, $s6
/* 08E020 8008D420 1000006B */  b     .L8008D5D0
/* 08E024 8008D424 8FBF0054 */   lw    $ra, 0x54($sp)
.L8008D428:
/* 08E028 8008D428 1441000E */  bne   $v0, $at, .L8008D464
/* 08E02C 8008D42C 02E02025 */   move  $a0, $s7
/* 08E030 8008D430 0C0310BB */  jal   set_text_font
/* 08E034 8008D434 00002025 */   move  $a0, $zero
/* 08E038 8008D438 3C0D800E */  lui   $t5, %hi(gMenuText) # $t5, 0x800e
/* 08E03C 8008D43C 8DADF4A0 */  lw    $t5, %lo(gMenuText)($t5)
/* 08E040 8008D440 240E000C */  li    $t6, 12
/* 08E044 8008D444 8DA70138 */  lw    $a3, 0x138($t5)
/* 08E048 8008D448 AFAE0010 */  sw    $t6, 0x10($sp)
/* 08E04C 8008D44C 02E02025 */  move  $a0, $s7
/* 08E050 8008D450 240500A0 */  li    $a1, 160
/* 08E054 8008D454 0C031110 */  jal   draw_text
/* 08E058 8008D458 02C03025 */   move  $a2, $s6
/* 08E05C 8008D45C 1000005C */  b     .L8008D5D0
/* 08E060 8008D460 8FBF0054 */   lw    $ra, 0x54($sp)
.L8008D464:
/* 08E064 8008D464 3C07800F */  lui   $a3, %hi(D_800E8234) # $a3, 0x800f
/* 08E068 8008D468 240F000C */  li    $t7, 12
/* 08E06C 8008D46C AFAF0010 */  sw    $t7, 0x10($sp)
/* 08E070 8008D470 24E78234 */  addiu $a3, %lo(D_800E8234) # addiu $a3, $a3, -0x7dcc
/* 08E074 8008D474 240500A0 */  li    $a1, 160
/* 08E078 8008D478 0C031110 */  jal   draw_text
/* 08E07C 8008D47C 02C03025 */   move  $a2, $s6
/* 08E080 8008D480 10000053 */  b     .L8008D5D0
/* 08E084 8008D484 8FBF0054 */   lw    $ra, 0x54($sp)
.L8008D488:
/* 08E088 8008D488 8F186488 */  lw    $t8, %lo(D_80126488)($t8)
/* 08E08C 8008D48C 3C198012 */  lui   $t9, %hi(D_80126494) # $t9, 0x8012
/* 08E090 8008D490 1300001A */  beqz  $t8, .L8008D4FC
/* 08E094 8008D494 3C0B8012 */   lui   $t3, %hi(D_80126CC0) # $t3, 0x8012
/* 08E098 8008D498 8F396494 */  lw    $t9, %lo(D_80126494)($t9)
/* 08E09C 8008D49C 02E02025 */  move  $a0, $s7
/* 08E0A0 8008D4A0 1720000E */  bnez  $t9, .L8008D4DC
/* 08E0A4 8008D4A4 240500A0 */   li    $a1, 160
/* 08E0A8 8008D4A8 0C0310BB */  jal   set_text_font
/* 08E0AC 8008D4AC 00002025 */   move  $a0, $zero
/* 08E0B0 8008D4B0 3C08800E */  lui   $t0, %hi(gMenuText) # $t0, 0x800e
/* 08E0B4 8008D4B4 8D08F4A0 */  lw    $t0, %lo(gMenuText)($t0)
/* 08E0B8 8008D4B8 2409000C */  li    $t1, 12
/* 08E0BC 8008D4BC 8D07013C */  lw    $a3, 0x13c($t0)
/* 08E0C0 8008D4C0 AFA90010 */  sw    $t1, 0x10($sp)
/* 08E0C4 8008D4C4 02E02025 */  move  $a0, $s7
/* 08E0C8 8008D4C8 240500A0 */  li    $a1, 160
/* 08E0CC 8008D4CC 0C031110 */  jal   draw_text
/* 08E0D0 8008D4D0 02C03025 */   move  $a2, $s6
/* 08E0D4 8008D4D4 1000003E */  b     .L8008D5D0
/* 08E0D8 8008D4D8 8FBF0054 */   lw    $ra, 0x54($sp)
.L8008D4DC:
/* 08E0DC 8008D4DC 3C07800F */  lui   $a3, %hi(D_800E8238) # $a3, 0x800f
/* 08E0E0 8008D4E0 240A000C */  li    $t2, 12
/* 08E0E4 8008D4E4 AFAA0010 */  sw    $t2, 0x10($sp)
/* 08E0E8 8008D4E8 24E78238 */  addiu $a3, %lo(D_800E8238) # addiu $a3, $a3, -0x7dc8
/* 08E0EC 8008D4EC 0C031110 */  jal   draw_text
/* 08E0F0 8008D4F0 02C03025 */   move  $a2, $s6
/* 08E0F4 8008D4F4 10000036 */  b     .L8008D5D0
/* 08E0F8 8008D4F8 8FBF0054 */   lw    $ra, 0x54($sp)
.L8008D4FC:
/* 08E0FC 8008D4FC 8D6B6CC0 */  lw    $t3, %lo(D_80126CC0)($t3)
/* 08E100 8008D500 3C0C8012 */  lui   $t4, %hi(D_801263E0) # $t4, 0x8012
/* 08E104 8008D504 15600032 */  bnez  $t3, .L8008D5D0
/* 08E108 8008D508 8FBF0054 */   lw    $ra, 0x54($sp)
/* 08E10C 8008D50C 8D8C63E0 */  lw    $t4, %lo(D_801263E0)($t4)
/* 08E110 8008D510 24010001 */  li    $at, 1
/* 08E114 8008D514 15810007 */  bne   $t4, $at, .L8008D534
/* 08E118 8008D518 240400FF */   li    $a0, 255
/* 08E11C 8008D51C 8FA7007C */  lw    $a3, 0x7c($sp)
/* 08E120 8008D520 240D00FF */  li    $t5, 255
/* 08E124 8008D524 AFAD0010 */  sw    $t5, 0x10($sp)
/* 08E128 8008D528 240500FF */  li    $a1, 255
/* 08E12C 8008D52C 0C0310E1 */  jal   set_text_color
/* 08E130 8008D530 240600FF */   li    $a2, 255
.L8008D534:
/* 08E134 8008D534 3C0E800E */  lui   $t6, %hi(gMenuText) # $t6, 0x800e
/* 08E138 8008D538 8DCEF4A0 */  lw    $t6, %lo(gMenuText)($t6)
/* 08E13C 8008D53C 240F000C */  li    $t7, 12
/* 08E140 8008D540 8DC70140 */  lw    $a3, 0x140($t6)
/* 08E144 8008D544 AFAF0010 */  sw    $t7, 0x10($sp)
/* 08E148 8008D548 02E02025 */  move  $a0, $s7
/* 08E14C 8008D54C 2405005A */  li    $a1, 90
/* 08E150 8008D550 0C031110 */  jal   draw_text
/* 08E154 8008D554 02C03025 */   move  $a2, $s6
/* 08E158 8008D558 3C188012 */  lui   $t8, %hi(D_801263E0) # $t8, 0x8012
/* 08E15C 8008D55C 8F1863E0 */  lw    $t8, %lo(D_801263E0)($t8)
/* 08E160 8008D560 24010002 */  li    $at, 2
/* 08E164 8008D564 1701000A */  bne   $t8, $at, .L8008D590
/* 08E168 8008D568 240400FF */   li    $a0, 255
/* 08E16C 8008D56C 8FA7007C */  lw    $a3, 0x7c($sp)
/* 08E170 8008D570 241900FF */  li    $t9, 255
/* 08E174 8008D574 AFB90010 */  sw    $t9, 0x10($sp)
/* 08E178 8008D578 240400FF */  li    $a0, 255
/* 08E17C 8008D57C 240500FF */  li    $a1, 255
/* 08E180 8008D580 0C0310E1 */  jal   set_text_color
/* 08E184 8008D584 240600FF */   li    $a2, 255
/* 08E188 8008D588 10000007 */  b     .L8008D5A8
/* 08E18C 8008D58C 00000000 */   nop   
.L8008D590:
/* 08E190 8008D590 240800FF */  li    $t0, 255
/* 08E194 8008D594 AFA80010 */  sw    $t0, 0x10($sp)
/* 08E198 8008D598 240500FF */  li    $a1, 255
/* 08E19C 8008D59C 240600FF */  li    $a2, 255
/* 08E1A0 8008D5A0 0C0310E1 */  jal   set_text_color
/* 08E1A4 8008D5A4 00003825 */   move  $a3, $zero
.L8008D5A8:
/* 08E1A8 8008D5A8 3C09800E */  lui   $t1, %hi(gMenuText) # $t1, 0x800e
/* 08E1AC 8008D5AC 8D29F4A0 */  lw    $t1, %lo(gMenuText)($t1)
/* 08E1B0 8008D5B0 240A000C */  li    $t2, 12
/* 08E1B4 8008D5B4 8D270144 */  lw    $a3, 0x144($t1)
/* 08E1B8 8008D5B8 AFAA0010 */  sw    $t2, 0x10($sp)
/* 08E1BC 8008D5BC 02E02025 */  move  $a0, $s7
/* 08E1C0 8008D5C0 240500E6 */  li    $a1, 230
/* 08E1C4 8008D5C4 0C031110 */  jal   draw_text
/* 08E1C8 8008D5C8 02C03025 */   move  $a2, $s6
/* 08E1CC 8008D5CC 8FBF0054 */  lw    $ra, 0x54($sp)
.L8008D5D0:
/* 08E1D0 8008D5D0 8FB00034 */  lw    $s0, 0x34($sp)
/* 08E1D4 8008D5D4 8FB10038 */  lw    $s1, 0x38($sp)
/* 08E1D8 8008D5D8 8FB2003C */  lw    $s2, 0x3c($sp)
/* 08E1DC 8008D5DC 8FB30040 */  lw    $s3, 0x40($sp)
/* 08E1E0 8008D5E0 8FB40044 */  lw    $s4, 0x44($sp)
/* 08E1E4 8008D5E4 8FB50048 */  lw    $s5, 0x48($sp)
/* 08E1E8 8008D5E8 8FB6004C */  lw    $s6, 0x4c($sp)
/* 08E1EC 8008D5EC 8FB70050 */  lw    $s7, 0x50($sp)
/* 08E1F0 8008D5F0 03E00008 */  jr    $ra
/* 08E1F4 8008D5F4 27BD0088 */   addiu $sp, $sp, 0x88

