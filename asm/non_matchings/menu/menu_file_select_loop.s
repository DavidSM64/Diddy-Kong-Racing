glabel menu_file_select_loop
/* 08EA70 8008DE70 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 08EA74 8008DE74 AFBF0024 */  sw    $ra, 0x24($sp)
/* 08EA78 8008DE78 0C01BAA4 */  jal   get_settings
/* 08EA7C 8008DE7C AFA40048 */   sw    $a0, 0x48($sp)
/* 08EA80 8008DE80 8FA40048 */  lw    $a0, 0x48($sp)
/* 08EA84 8008DE84 0C02305A */  jal   func_8008C168
/* 08EA88 8008DE88 AFA20038 */   sw    $v0, 0x38($sp)
/* 08EA8C 8008DE8C 3C028012 */  lui   $v0, %hi(D_801263D8) # $v0, 0x8012
/* 08EA90 8008DE90 8C4263D8 */  lw    $v0, %lo(D_801263D8)($v0)
/* 08EA94 8008DE94 3C018012 */  lui   $at, %hi(D_801263D8) # $at, 0x8012
/* 08EA98 8008DE98 10400037 */  beqz  $v0, .L8008DF78
/* 08EA9C 8008DE9C 244E0001 */   addiu $t6, $v0, 1
/* 08EAA0 8008DEA0 AC2E63D8 */  sw    $t6, %lo(D_801263D8)($at)
/* 08EAA4 8008DEA4 3C0F8012 */  lui   $t7, %hi(D_801263D8) # $t7, 0x8012
/* 08EAA8 8008DEA8 8DEF63D8 */  lw    $t7, %lo(D_801263D8)($t7)
/* 08EAAC 8008DEAC 00004025 */  move  $t0, $zero
/* 08EAB0 8008DEB0 29E10003 */  slti  $at, $t7, 3
/* 08EAB4 8008DEB4 14200030 */  bnez  $at, .L8008DF78
/* 08EAB8 8008DEB8 3C028012 */   lui   $v0, %hi(gSavefileInfo) # $v0, 0x8012
/* 08EABC 8008DEBC 3C078012 */  lui   $a3, %hi(D_80126530) # $a3, 0x8012
/* 08EAC0 8008DEC0 24E76530 */  addiu $a3, %lo(D_80126530) # addiu $a3, $a3, 0x6530
/* 08EAC4 8008DEC4 244264A0 */  addiu $v0, %lo(gSavefileInfo) # addiu $v0, $v0, 0x64a0
.L8008DEC8:
/* 08EAC8 8008DEC8 8CE30000 */  lw    $v1, ($a3)
/* 08EACC 8008DECC A0400000 */  sb    $zero, ($v0)
/* 08EAD0 8008DED0 9078004B */  lbu   $t8, 0x4b($v1)
/* 08EAD4 8008DED4 240C004B */  li    $t4, 75
/* 08EAD8 8008DED8 1300000A */  beqz  $t8, .L8008DF04
/* 08EADC 8008DEDC 24190001 */   li    $t9, 1
/* 08EAE0 8008DEE0 24190044 */  li    $t9, 68
/* 08EAE4 8008DEE4 240D0052 */  li    $t5, 82
/* 08EAE8 8008DEE8 A0400001 */  sb    $zero, 1($v0)
/* 08EAEC 8008DEEC A4400002 */  sh    $zero, 2($v0)
/* 08EAF0 8008DEF0 A0590004 */  sb    $t9, 4($v0)
/* 08EAF4 8008DEF4 A04C0005 */  sb    $t4, 5($v0)
/* 08EAF8 8008DEF8 A04D0006 */  sb    $t5, 6($v0)
/* 08EAFC 8008DEFC 10000016 */  b     .L8008DF58
/* 08EB00 8008DF00 A0400007 */   sb    $zero, 7($v0)
.L8008DF04:
/* 08EB04 8008DF04 8C6E0010 */  lw    $t6, 0x10($v1)
/* 08EB08 8008DF08 24450004 */  addiu $a1, $v0, 4
/* 08EB0C 8008DF0C 31CF0004 */  andi  $t7, $t6, 4
/* 08EB10 8008DF10 11E00002 */  beqz  $t7, .L8008DF1C
/* 08EB14 8008DF14 24180001 */   li    $t8, 1
/* 08EB18 8008DF18 A0580000 */  sb    $t8, ($v0)
.L8008DF1C:
/* 08EB1C 8008DF1C A0590001 */  sb    $t9, 1($v0)
/* 08EB20 8008DF20 8C6C0000 */  lw    $t4, ($v1)
/* 08EB24 8008DF24 24060003 */  li    $a2, 3
/* 08EB28 8008DF28 858D0000 */  lh    $t5, ($t4)
/* 08EB2C 8008DF2C 00000000 */  nop   
/* 08EB30 8008DF30 A44D0002 */  sh    $t5, 2($v0)
/* 08EB34 8008DF34 8C640050 */  lw    $a0, 0x50($v1)
/* 08EB38 8008DF38 AFA80044 */  sw    $t0, 0x44($sp)
/* 08EB3C 8008DF3C AFA7002C */  sw    $a3, 0x2c($sp)
/* 08EB40 8008DF40 0C025DBE */  jal   decompress_filename_string
/* 08EB44 8008DF44 AFA20030 */   sw    $v0, 0x30($sp)
/* 08EB48 8008DF48 8FA20030 */  lw    $v0, 0x30($sp)
/* 08EB4C 8008DF4C 8FA7002C */  lw    $a3, 0x2c($sp)
/* 08EB50 8008DF50 8FA80044 */  lw    $t0, 0x44($sp)
/* 08EB54 8008DF54 00000000 */  nop   
.L8008DF58:
/* 08EB58 8008DF58 25080001 */  addiu $t0, $t0, 1
/* 08EB5C 8008DF5C 24010003 */  li    $at, 3
/* 08EB60 8008DF60 2442000C */  addiu $v0, $v0, 0xc
/* 08EB64 8008DF64 1501FFD8 */  bne   $t0, $at, .L8008DEC8
/* 08EB68 8008DF68 24E70004 */   addiu $a3, $a3, 4
/* 08EB6C 8008DF6C 3C018012 */  lui   $at, %hi(D_801263D8) # $at, 0x8012
/* 08EB70 8008DF70 AC2063D8 */  sw    $zero, %lo(D_801263D8)($at)
/* 08EB74 8008DF74 AFA80044 */  sw    $t0, 0x44($sp)
.L8008DF78:
/* 08EB78 8008DF78 3C038012 */  lui   $v1, %hi(D_801263BC) # $v1, 0x8012
/* 08EB7C 8008DF7C 246363BC */  addiu $v1, %lo(D_801263BC) # addiu $v1, $v1, 0x63bc
/* 08EB80 8008DF80 8FA50048 */  lw    $a1, 0x48($sp)
/* 08EB84 8008DF84 8C6E0000 */  lw    $t6, ($v1)
/* 08EB88 8008DF88 3C06800E */  lui   $a2, %hi(gMenuDelay) # $a2, 0x800e
/* 08EB8C 8008DF8C 24C6F47C */  addiu $a2, %lo(gMenuDelay) # addiu $a2, $a2, -0xb84
/* 08EB90 8008DF90 8CC20000 */  lw    $v0, ($a2)
/* 08EB94 8008DF94 01C57821 */  addu  $t7, $t6, $a1
/* 08EB98 8008DF98 8FA80044 */  lw    $t0, 0x44($sp)
/* 08EB9C 8008DF9C 31F8003F */  andi  $t8, $t7, 0x3f
/* 08EBA0 8008DFA0 10400009 */  beqz  $v0, .L8008DFC8
/* 08EBA4 8008DFA4 AC780000 */   sw    $t8, ($v1)
/* 08EBA8 8008DFA8 18400005 */  blez  $v0, .L8008DFC0
/* 08EBAC 8008DFAC 00456023 */   subu  $t4, $v0, $a1
/* 08EBB0 8008DFB0 0045C821 */  addu  $t9, $v0, $a1
/* 08EBB4 8008DFB4 ACD90000 */  sw    $t9, ($a2)
/* 08EBB8 8008DFB8 10000003 */  b     .L8008DFC8
/* 08EBBC 8008DFBC 03201025 */   move  $v0, $t9
.L8008DFC0:
/* 08EBC0 8008DFC0 ACCC0000 */  sw    $t4, ($a2)
/* 08EBC4 8008DFC4 01801025 */  move  $v0, $t4
.L8008DFC8:
/* 08EBC8 8008DFC8 2841FFEC */  slti  $at, $v0, -0x14
/* 08EBCC 8008DFCC 1420000A */  bnez  $at, .L8008DFF8
/* 08EBD0 8008DFD0 28410015 */   slti  $at, $v0, 0x15
/* 08EBD4 8008DFD4 10200008 */  beqz  $at, .L8008DFF8
/* 08EBD8 8008DFD8 00A02025 */   move  $a0, $a1
/* 08EBDC 8008DFDC 0C02335D */  jal   render_file_select_menu
/* 08EBE0 8008DFE0 AFA80044 */   sw    $t0, 0x44($sp)
/* 08EBE4 8008DFE4 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 08EBE8 8008DFE8 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 08EBEC 8008DFEC 8FA80044 */  lw    $t0, 0x44($sp)
/* 08EBF0 8008DFF0 8FA50048 */  lw    $a1, 0x48($sp)
/* 08EBF4 8008DFF4 00000000 */  nop   
.L8008DFF8:
/* 08EBF8 8008DFF8 144000A4 */  bnez  $v0, .L8008E28C
/* 08EBFC 8008DFFC 3C0D8012 */   lui   $t5, %hi(D_801263D8) # $t5, 0x8012
/* 08EC00 8008E000 8DAD63D8 */  lw    $t5, %lo(D_801263D8)($t5)
/* 08EC04 8008E004 3C0E8012 */  lui   $t6, %hi(D_80126484) # $t6, 0x8012
/* 08EC08 8008E008 15A000A0 */  bnez  $t5, .L8008E28C
/* 08EC0C 8008E00C 00000000 */   nop   
/* 08EC10 8008E010 8DCE6484 */  lw    $t6, %lo(D_80126484)($t6)
/* 08EC14 8008E014 3C0F8012 */  lui   $t7, %hi(D_80126488) # $t7, 0x8012
/* 08EC18 8008E018 11C00005 */  beqz  $t6, .L8008E030
/* 08EC1C 8008E01C 00000000 */   nop   
/* 08EC20 8008E020 0C02362F */  jal   func_8008D8BC
/* 08EC24 8008E024 00A02025 */   move  $a0, $a1
/* 08EC28 8008E028 10000098 */  b     .L8008E28C
/* 08EC2C 8008E02C 00000000 */   nop   
.L8008E030:
/* 08EC30 8008E030 8DEF6488 */  lw    $t7, %lo(D_80126488)($t7)
/* 08EC34 8008E034 3C188012 */  lui   $t8, %hi(D_80126CC0) # $t8, 0x8012
/* 08EC38 8008E038 11E00005 */  beqz  $t7, .L8008E050
/* 08EC3C 8008E03C 00000000 */   nop   
/* 08EC40 8008E040 0C02371F */  jal   func_8008DC7C
/* 08EC44 8008E044 00A02025 */   move  $a0, $a1
/* 08EC48 8008E048 10000090 */  b     .L8008E28C
/* 08EC4C 8008E04C 00000000 */   nop   
.L8008E050:
/* 08EC50 8008E050 8F186CC0 */  lw    $t8, %lo(D_80126CC0)($t8)
/* 08EC54 8008E054 00002025 */  move  $a0, $zero
/* 08EC58 8008E058 13000048 */  beqz  $t8, .L8008E17C
/* 08EC5C 8008E05C 00000000 */   nop   
/* 08EC60 8008E060 0C01A955 */  jal   get_buttons_pressed_from_player
/* 08EC64 8008E064 AFA80044 */   sw    $t0, 0x44($sp)
/* 08EC68 8008E068 8FA80044 */  lw    $t0, 0x44($sp)
/* 08EC6C 8008E06C 30594000 */  andi  $t9, $v0, 0x4000
/* 08EC70 8008E070 13200016 */  beqz  $t9, .L8008E0CC
/* 08EC74 8008E074 3C0C800E */   lui   $t4, %hi(D_800E0FA0) # $t4, 0x800e
/* 08EC78 8008E078 8D8C0FA0 */  lw    $t4, %lo(D_800E0FA0)($t4)
/* 08EC7C 8008E07C 00086880 */  sll   $t5, $t0, 2
/* 08EC80 8008E080 15800012 */  bnez  $t4, .L8008E0CC
/* 08EC84 8008E084 01A86823 */   subu  $t5, $t5, $t0
/* 08EC88 8008E088 3C0E8012 */  lui   $t6, %hi(gSavefileInfo) # $t6, 0x8012
/* 08EC8C 8008E08C 25CE64A0 */  addiu $t6, %lo(gSavefileInfo) # addiu $t6, $t6, 0x64a0
/* 08EC90 8008E090 000D6880 */  sll   $t5, $t5, 2
/* 08EC94 8008E094 01AE1021 */  addu  $v0, $t5, $t6
/* 08EC98 8008E098 0C02607A */  jal   func_800981E8
/* 08EC9C 8008E09C AFA20030 */   sw    $v0, 0x30($sp)
/* 08ECA0 8008E0A0 8FA20030 */  lw    $v0, 0x30($sp)
/* 08ECA4 8008E0A4 3C018012 */  lui   $at, %hi(D_80126CC0) # $at, 0x8012
/* 08ECA8 8008E0A8 AC206CC0 */  sw    $zero, %lo(D_80126CC0)($at)
/* 08ECAC 8008E0AC 240F0044 */  li    $t7, 68
/* 08ECB0 8008E0B0 2418004B */  li    $t8, 75
/* 08ECB4 8008E0B4 24190052 */  li    $t9, 82
/* 08ECB8 8008E0B8 A04F0004 */  sb    $t7, 4($v0)
/* 08ECBC 8008E0BC A0580005 */  sb    $t8, 5($v0)
/* 08ECC0 8008E0C0 A0590006 */  sb    $t9, 6($v0)
/* 08ECC4 8008E0C4 10000071 */  b     .L8008E28C
/* 08ECC8 8008E0C8 A0400007 */   sb    $zero, 7($v0)
.L8008E0CC:
/* 08ECCC 8008E0CC 8FA40048 */  lw    $a0, 0x48($sp)
/* 08ECD0 8008E0D0 0C025F44 */  jal   func_80097D10
/* 08ECD4 8008E0D4 00000000 */   nop   
/* 08ECD8 8008E0D8 1040006C */  beqz  $v0, .L8008E28C
/* 08ECDC 8008E0DC 00000000 */   nop   
/* 08ECE0 8008E0E0 0C02607A */  jal   func_800981E8
/* 08ECE4 8008E0E4 00000000 */   nop   
/* 08ECE8 8008E0E8 3C0C800E */  lui   $t4, %hi(gSaveFileIndex) # $t4, 0x800e
/* 08ECEC 8008E0EC 8D8CF4CC */  lw    $t4, %lo(gSaveFileIndex)($t4)
/* 08ECF0 8008E0F0 3C0E8012 */  lui   $t6, %hi(gSavefileInfo) # $t6, 0x8012
/* 08ECF4 8008E0F4 000C6880 */  sll   $t5, $t4, 2
/* 08ECF8 8008E0F8 01AC6823 */  subu  $t5, $t5, $t4
/* 08ECFC 8008E0FC 3C018012 */  lui   $at, %hi(D_80126CC0) # $at, 0x8012
/* 08ED00 8008E100 000D6880 */  sll   $t5, $t5, 2
/* 08ED04 8008E104 25CE64A0 */  addiu $t6, %lo(gSavefileInfo) # addiu $t6, $t6, 0x64a0
/* 08ED08 8008E108 AC206CC0 */  sw    $zero, %lo(D_80126CC0)($at)
/* 08ED0C 8008E10C 01AE1021 */  addu  $v0, $t5, $t6
/* 08ED10 8008E110 A0400000 */  sb    $zero, ($v0)
/* 08ED14 8008E114 3C0F800E */  lui   $t7, %hi(gIsInAdventureTwo) # $t7, 0x800e
/* 08ED18 8008E118 8DEFF494 */  lw    $t7, %lo(gIsInAdventureTwo)($t7)
/* 08ED1C 8008E11C 24190001 */  li    $t9, 1
/* 08ED20 8008E120 11E00003 */  beqz  $t7, .L8008E130
/* 08ED24 8008E124 24440004 */   addiu $a0, $v0, 4
/* 08ED28 8008E128 24180001 */  li    $t8, 1
/* 08ED2C 8008E12C A0580000 */  sb    $t8, ($v0)
.L8008E130:
/* 08ED30 8008E130 A0590001 */  sb    $t9, 1($v0)
/* 08ED34 8008E134 A4400002 */  sh    $zero, 2($v0)
/* 08ED38 8008E138 0C025DD1 */  jal   compress_filename_string
/* 08ED3C 8008E13C 24050003 */   li    $a1, 3
/* 08ED40 8008E140 8FAC0038 */  lw    $t4, 0x38($sp)
/* 08ED44 8008E144 3C04800E */  lui   $a0, %hi(gSaveFileIndex) # $a0, 0x800e
/* 08ED48 8008E148 AD820050 */  sw    $v0, 0x50($t4)
/* 08ED4C 8008E14C 8C84F4CC */  lw    $a0, %lo(gSaveFileIndex)($a0)
/* 08ED50 8008E150 0C01BADE */  jal   func_8006EB78
/* 08ED54 8008E154 00000000 */   nop   
/* 08ED58 8008E158 0C000326 */  jal   set_music_fade_timer
/* 08ED5C 8008E15C 2404FF80 */   li    $a0, -128
/* 08ED60 8008E160 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeIn) # $a0, 0x800e
/* 08ED64 8008E164 0C030076 */  jal   func_800C01D8
/* 08ED68 8008E168 2484F774 */   addiu $a0, %lo(sMenuTransitionFadeIn) # addiu $a0, $a0, -0x88c
/* 08ED6C 8008E16C 240D0001 */  li    $t5, 1
/* 08ED70 8008E170 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08ED74 8008E174 10000045 */  b     .L8008E28C
/* 08ED78 8008E178 AC2DF47C */   sw    $t5, %lo(gMenuDelay)($at)
.L8008E17C:
/* 08ED7C 8008E17C 0C02357E */  jal   func_8008D5F8
/* 08ED80 8008E180 00A02025 */   move  $a0, $a1
/* 08ED84 8008E184 10400041 */  beqz  $v0, .L8008E28C
/* 08ED88 8008E188 AFA20040 */   sw    $v0, 0x40($sp)
/* 08ED8C 8008E18C 18400036 */  blez  $v0, .L8008E268
/* 08ED90 8008E190 3C09800E */   lui   $t1, %hi(gSaveFileIndex) # $t1, 0x800e
/* 08ED94 8008E194 8D29F4CC */  lw    $t1, %lo(gSaveFileIndex)($t1)
/* 08ED98 8008E198 3C0F8012 */  lui   $t7, %hi(gSavefileInfo) # $t7, 0x8012
/* 08ED9C 8008E19C 00097080 */  sll   $t6, $t1, 2
/* 08EDA0 8008E1A0 01C97023 */  subu  $t6, $t6, $t1
/* 08EDA4 8008E1A4 000E7080 */  sll   $t6, $t6, 2
/* 08EDA8 8008E1A8 25EF64A0 */  addiu $t7, %lo(gSavefileInfo) # addiu $t7, $t7, 0x64a0
/* 08EDAC 8008E1AC 01CF1021 */  addu  $v0, $t6, $t7
/* 08EDB0 8008E1B0 90580001 */  lbu   $t8, 1($v0)
/* 08EDB4 8008E1B4 3C0B800E */  lui   $t3, %hi(D_800E0FB0) # $t3, 0x800e
/* 08EDB8 8008E1B8 1300000C */  beqz  $t8, .L8008E1EC
/* 08EDBC 8008E1BC 256B0FB0 */   addiu $t3, %lo(D_800E0FB0) # addiu $t3, $t3, 0xfb0
/* 08EDC0 8008E1C0 240400EF */  li    $a0, 239
/* 08EDC4 8008E1C4 0C000741 */  jal   func_80001D04
/* 08EDC8 8008E1C8 00002825 */   move  $a1, $zero
/* 08EDCC 8008E1CC 3C04800E */  lui   $a0, %hi(gSaveFileIndex) # $a0, 0x800e
/* 08EDD0 8008E1D0 8C84F4CC */  lw    $a0, %lo(gSaveFileIndex)($a0)
/* 08EDD4 8008E1D4 0C01BADE */  jal   func_8006EB78
/* 08EDD8 8008E1D8 00000000 */   nop   
/* 08EDDC 8008E1DC 0C000326 */  jal   set_music_fade_timer
/* 08EDE0 8008E1E0 2404FF80 */   li    $a0, -128
/* 08EDE4 8008E1E4 10000021 */  b     .L8008E26C
/* 08EDE8 8008E1E8 8FB80040 */   lw    $t8, 0x40($sp)
.L8008E1EC:
/* 08EDEC 8008E1EC 24190001 */  li    $t9, 1
/* 08EDF0 8008E1F0 3C018012 */  lui   $at, %hi(D_80126CC0) # $at, 0x8012
/* 08EDF4 8008E1F4 AC396CC0 */  sw    $t9, %lo(D_80126CC0)($at)
/* 08EDF8 8008E1F8 AD600000 */  sw    $zero, ($t3)
/* 08EDFC 8008E1FC 3C0C8000 */  lui   $t4, %hi(osTvType) # $t4, 0x8000
/* 08EE00 8008E200 8D8C0300 */  lw    $t4, %lo(osTvType)($t4)
/* 08EE04 8008E204 00004025 */  move  $t0, $zero
/* 08EE08 8008E208 15800002 */  bnez  $t4, .L8008E214
/* 08EE0C 8008E20C 3C0A800E */   lui   $t2, %hi(D_800E03FC) # $t2, 0x800e
/* 08EE10 8008E210 2408000C */  li    $t0, 12
.L8008E214:
/* 08EE14 8008E214 3C0E800E */  lui   $t6, %hi(D_800E03CC) # $t6, 0x800e
/* 08EE18 8008E218 25CE03CC */  addiu $t6, %lo(D_800E03CC) # addiu $t6, $t6, 0x3cc
/* 08EE1C 8008E21C 00096900 */  sll   $t5, $t1, 4
/* 08EE20 8008E220 254A03FC */  addiu $t2, %lo(D_800E03FC) # addiu $t2, $t2, 0x3fc
/* 08EE24 8008E224 01AE1821 */  addu  $v1, $t5, $t6
/* 08EE28 8008E228 84780000 */  lh    $t8, ($v1)
/* 08EE2C 8008E22C 854F0000 */  lh    $t7, ($t2)
/* 08EE30 8008E230 846C0002 */  lh    $t4, 2($v1)
/* 08EE34 8008E234 85590002 */  lh    $t9, 2($t2)
/* 08EE38 8008E238 01F82821 */  addu  $a1, $t7, $t8
/* 08EE3C 8008E23C 240F0003 */  li    $t7, 3
/* 08EE40 8008E240 244E0004 */  addiu $t6, $v0, 4
/* 08EE44 8008E244 032C6821 */  addu  $t5, $t9, $t4
/* 08EE48 8008E248 01A83021 */  addu  $a2, $t5, $t0
/* 08EE4C 8008E24C AFAE0014 */  sw    $t6, 0x14($sp)
/* 08EE50 8008E250 AFAF0018 */  sw    $t7, 0x18($sp)
/* 08EE54 8008E254 250400BB */  addiu $a0, $t0, 0xbb
/* 08EE58 8008E258 00003825 */  move  $a3, $zero
/* 08EE5C 8008E25C 0C025E1D */  jal   func_80097874
/* 08EE60 8008E260 AFAB0010 */   sw    $t3, 0x10($sp)
/* 08EE64 8008E264 AFA00040 */  sw    $zero, 0x40($sp)
.L8008E268:
/* 08EE68 8008E268 8FB80040 */  lw    $t8, 0x40($sp)
.L8008E26C:
/* 08EE6C 8008E26C 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeIn) # $a0, 0x800e
/* 08EE70 8008E270 13000006 */  beqz  $t8, .L8008E28C
/* 08EE74 8008E274 00000000 */   nop   
/* 08EE78 8008E278 0C030076 */  jal   func_800C01D8
/* 08EE7C 8008E27C 2484F774 */   addiu $a0, %lo(sMenuTransitionFadeIn) # addiu $a0, $a0, -0x88c
/* 08EE80 8008E280 8FB90040 */  lw    $t9, 0x40($sp)
/* 08EE84 8008E284 3C01800E */  lui   $at, %hi(gMenuDelay) # $at, 0x800e
/* 08EE88 8008E288 AC39F47C */  sw    $t9, %lo(gMenuDelay)($at)
.L8008E28C:
/* 08EE8C 8008E28C 3C06800E */  lui   $a2, %hi(gMenuDelay) # $a2, 0x800e
/* 08EE90 8008E290 24C6F47C */  addiu $a2, %lo(gMenuDelay) # addiu $a2, $a2, -0xb84
/* 08EE94 8008E294 8CC20000 */  lw    $v0, ($a2)
/* 08EE98 8008E298 00000000 */  nop   
/* 08EE9C 8008E29C 28410024 */  slti  $at, $v0, 0x24
/* 08EEA0 8008E2A0 14200054 */  bnez  $at, .L8008E3F4
/* 08EEA4 8008E2A4 3C06800E */   lui   $a2, %hi(gActiveMagicCodes) # $a2, 0x800e
/* 08EEA8 8008E2A8 24C6FD98 */  addiu $a2, %lo(gActiveMagicCodes) # addiu $a2, $a2, -0x268
/* 08EEAC 8008E2AC 8CC30000 */  lw    $v1, ($a2)
/* 08EEB0 8008E2B0 3C04FBFF */  lui   $a0, (0xFBFFFFFF >> 16) # lui $a0, 0xfbff
/* 08EEB4 8008E2B4 00036140 */  sll   $t4, $v1, 5
/* 08EEB8 8008E2B8 0581000F */  bgez  $t4, .L8008E2F8
/* 08EEBC 8008E2BC 3484FFFF */   ori   $a0, (0xFBFFFFFF & 0xFFFF) # ori $a0, $a0, 0xffff
/* 08EEC0 8008E2C0 3C05800E */  lui   $a1, %hi(gUnlockedMagicCodes) # $a1, 0x800e
/* 08EEC4 8008E2C4 24A5FD9C */  addiu $a1, %lo(gUnlockedMagicCodes) # addiu $a1, $a1, -0x264
/* 08EEC8 8008E2C8 8CAE0000 */  lw    $t6, ($a1)
/* 08EECC 8008E2CC 8FB80038 */  lw    $t8, 0x38($sp)
/* 08EED0 8008E2D0 00646824 */  and   $t5, $v1, $a0
/* 08EED4 8008E2D4 01C47824 */  and   $t7, $t6, $a0
/* 08EED8 8008E2D8 ACCD0000 */  sw    $t5, ($a2)
/* 08EEDC 8008E2DC ACAF0000 */  sw    $t7, ($a1)
/* 08EEE0 8008E2E0 8F020000 */  lw    $v0, ($t8)
/* 08EEE4 8008E2E4 00000000 */  nop   
/* 08EEE8 8008E2E8 84590000 */  lh    $t9, ($v0)
/* 08EEEC 8008E2EC 00000000 */  nop   
/* 08EEF0 8008E2F0 272C0001 */  addiu $t4, $t9, 1
/* 08EEF4 8008E2F4 A44C0000 */  sh    $t4, ($v0)
.L8008E2F8:
/* 08EEF8 8008E2F8 3C0D800E */  lui   $t5, %hi(gNumberOfActivePlayers) # $t5, 0x800e
/* 08EEFC 8008E2FC 8DADF4BC */  lw    $t5, %lo(gNumberOfActivePlayers)($t5)
/* 08EF00 8008E300 3C02800E */  lui   $v0, %hi(gIsInTwoPlayerAdventure) # $v0, 0x800e
/* 08EF04 8008E304 39AE0002 */  xori  $t6, $t5, 2
/* 08EF08 8008E308 2442F4C0 */  addiu $v0, %lo(gIsInTwoPlayerAdventure) # addiu $v0, $v0, -0xb40
/* 08EF0C 8008E30C 2DCE0001 */  sltiu $t6, $t6, 1
/* 08EF10 8008E310 11C00003 */  beqz  $t6, .L8008E320
/* 08EF14 8008E314 AC4E0000 */   sw    $t6, ($v0)
/* 08EF18 8008E318 0C00386E */  jal   func_8000E1B8
/* 08EF1C 8008E31C 00000000 */   nop   
.L8008E320:
/* 08EF20 8008E320 24180001 */  li    $t8, 1
/* 08EF24 8008E324 3C01800E */  lui   $at, %hi(gNumberOfActivePlayers) # $at, 0x800e
/* 08EF28 8008E328 AC38F4BC */  sw    $t8, %lo(gNumberOfActivePlayers)($at)
/* 08EF2C 8008E32C 3C01800E */  lui   $at, %hi(D_800E0FAC) # $at, 0x800e
/* 08EF30 8008E330 24190001 */  li    $t9, 1
/* 08EF34 8008E334 0C02390A */  jal   func_8008E428
/* 08EF38 8008E338 AC390FAC */   sw    $t9, %lo(D_800E0FAC)($at)
/* 08EF3C 8008E33C 0C0002CA */  jal   func_80000B28
/* 08EF40 8008E340 00000000 */   nop   
/* 08EF44 8008E344 0C01B96F */  jal   func_8006E5BC
/* 08EF48 8008E348 00000000 */   nop   
/* 08EF4C 8008E34C 8FA20038 */  lw    $v0, 0x38($sp)
/* 08EF50 8008E350 3C01800E */  lui   $at, %hi(gTrophyRaceWorldId) # $at, 0x800e
/* 08EF54 8008E354 AC200FE8 */  sw    $zero, %lo(gTrophyRaceWorldId)($at)
/* 08EF58 8008E358 904C004B */  lbu   $t4, 0x4b($v0)
/* 08EF5C 8008E35C 3C0D800E */  lui   $t5, %hi(gIsInAdventureTwo) # $t5, 0x800e
/* 08EF60 8008E360 11800017 */  beqz  $t4, .L8008E3C0
/* 08EF64 8008E364 00000000 */   nop   
/* 08EF68 8008E368 8DADF494 */  lw    $t5, %lo(gIsInAdventureTwo)($t5)
/* 08EF6C 8008E36C 00000000 */  nop   
/* 08EF70 8008E370 11A00005 */  beqz  $t5, .L8008E388
/* 08EF74 8008E374 00000000 */   nop   
/* 08EF78 8008E378 8C4E0010 */  lw    $t6, 0x10($v0)
/* 08EF7C 8008E37C 00000000 */  nop   
/* 08EF80 8008E380 35CF0004 */  ori   $t7, $t6, 4
/* 08EF84 8008E384 AC4F0010 */  sw    $t7, 0x10($v0)
.L8008E388:
/* 08EF88 8008E388 0C0078A7 */  jal   get_misc_asset
/* 08EF8C 8008E38C 24040019 */   li    $a0, 25
/* 08EF90 8008E390 3C06800E */  lui   $a2, %hi(gNumberOfActivePlayers) # $a2, 0x800e
/* 08EF94 8008E394 8CC6F4BC */  lw    $a2, %lo(gNumberOfActivePlayers)($a2)
/* 08EF98 8008E398 00402025 */  move  $a0, $v0
/* 08EF9C 8008E39C 00002825 */  move  $a1, $zero
/* 08EFA0 8008E3A0 00003825 */  move  $a3, $zero
/* 08EFA4 8008E3A4 AFA00010 */  sw    $zero, 0x10($sp)
/* 08EFA8 8008E3A8 0C026AF6 */  jal   func_8009ABD8
/* 08EFAC 8008E3AC AFA00014 */   sw    $zero, 0x14($sp)
/* 08EFB0 8008E3B0 0C0204F4 */  jal   menu_init
/* 08EFB4 8008E3B4 24040017 */   li    $a0, 23
/* 08EFB8 8008E3B8 10000017 */  b     .L8008E418
/* 08EFBC 8008E3BC 00001025 */   move  $v0, $zero
.L8008E3C0:
/* 08EFC0 8008E3C0 8C580010 */  lw    $t8, 0x10($v0)
/* 08EFC4 8008E3C4 3C01800E */  lui   $at, %hi(gIsInAdventureTwo) # $at, 0x800e
/* 08EFC8 8008E3C8 33190004 */  andi  $t9, $t8, 4
/* 08EFCC 8008E3CC 13200005 */  beqz  $t9, .L8008E3E4
/* 08EFD0 8008E3D0 3C02800E */   lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 08EFD4 8008E3D4 240C0001 */  li    $t4, 1
/* 08EFD8 8008E3D8 3C01800E */  lui   $at, %hi(gIsInAdventureTwo) # $at, 0x800e
/* 08EFDC 8008E3DC 10000002 */  b     .L8008E3E8
/* 08EFE0 8008E3E0 AC2CF494 */   sw    $t4, %lo(gIsInAdventureTwo)($at)
.L8008E3E4:
/* 08EFE4 8008E3E4 AC20F494 */  sw    $zero, %lo(gIsInAdventureTwo)($at)
.L8008E3E8:
/* 08EFE8 8008E3E8 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 08EFEC 8008E3EC 1000000B */  b     .L8008E41C
/* 08EFF0 8008E3F0 8FBF0024 */   lw    $ra, 0x24($sp)
.L8008E3F4:
/* 08EFF4 8008E3F4 2841FFDD */  slti  $at, $v0, -0x23
/* 08EFF8 8008E3F8 10200007 */  beqz  $at, .L8008E418
/* 08EFFC 8008E3FC 00001025 */   move  $v0, $zero
/* 08F000 8008E400 0C02390A */  jal   func_8008E428
/* 08F004 8008E404 00000000 */   nop   
/* 08F008 8008E408 0C0204F4 */  jal   menu_init
/* 08F00C 8008E40C 24040013 */   li    $a0, 19
/* 08F010 8008E410 10000001 */  b     .L8008E418
/* 08F014 8008E414 00001025 */   move  $v0, $zero
.L8008E418:
/* 08F018 8008E418 8FBF0024 */  lw    $ra, 0x24($sp)
.L8008E41C:
/* 08F01C 8008E41C 27BD0048 */  addiu $sp, $sp, 0x48
/* 08F020 8008E420 03E00008 */  jr    $ra
/* 08F024 8008E424 00000000 */   nop   

