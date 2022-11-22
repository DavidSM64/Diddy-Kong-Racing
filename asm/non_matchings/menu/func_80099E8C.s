.late_rodata
glabel D_800E8570
.float 0.075

.text
glabel func_80099E8C
/* 09AA8C 80099E8C 27BDFF10 */  addiu $sp, $sp, -0xf0
/* 09AA90 80099E90 AFB70054 */  sw    $s7, 0x54($sp)
/* 09AA94 80099E94 3C178012 */  lui   $s7, %hi(sMenuCurrDisplayList) # $s7, 0x8012
/* 09AA98 80099E98 26F763A0 */  addiu $s7, %lo(sMenuCurrDisplayList) # addiu $s7, $s7, 0x63a0
/* 09AA9C 80099E9C AFBF005C */  sw    $ra, 0x5c($sp)
/* 09AAA0 80099EA0 AFA400F0 */  sw    $a0, 0xf0($sp)
/* 09AAA4 80099EA4 3C058012 */  lui   $a1, %hi(sMenuCurrHudMat) # $a1, 0x8012
/* 09AAA8 80099EA8 AFBE0058 */  sw    $fp, 0x58($sp)
/* 09AAAC 80099EAC AFB60050 */  sw    $s6, 0x50($sp)
/* 09AAB0 80099EB0 AFB5004C */  sw    $s5, 0x4c($sp)
/* 09AAB4 80099EB4 AFB40048 */  sw    $s4, 0x48($sp)
/* 09AAB8 80099EB8 AFB30044 */  sw    $s3, 0x44($sp)
/* 09AABC 80099EBC AFB20040 */  sw    $s2, 0x40($sp)
/* 09AAC0 80099EC0 AFB1003C */  sw    $s1, 0x3c($sp)
/* 09AAC4 80099EC4 AFB00038 */  sw    $s0, 0x38($sp)
/* 09AAC8 80099EC8 24A563A8 */  addiu $a1, %lo(sMenuCurrHudMat) # addiu $a1, $a1, 0x63a8
/* 09AACC 80099ECC 0C019FCB */  jal   func_80067F2C
/* 09AAD0 80099ED0 02E02025 */   move  $a0, $s7
/* 09AAD4 80099ED4 3C0E8000 */  lui   $t6, %hi(osTvType) # $t6, 0x8000
/* 09AAD8 80099ED8 8DCE0300 */  lw    $t6, %lo(osTvType)($t6)
/* 09AADC 80099EDC 3C188012 */  lui   $t8, %hi(gOpacityDecayTimer) # $t8, 0x8012
/* 09AAE0 80099EE0 15C00004 */  bnez  $t6, .L80099EF4
/* 09AAE4 80099EE4 24040002 */   li    $a0, 2
/* 09AAE8 80099EE8 240F000C */  li    $t7, 12
/* 09AAEC 80099EEC 10000002 */  b     .L80099EF8
/* 09AAF0 80099EF0 AFAF00D0 */   sw    $t7, 0xd0($sp)
.L80099EF4:
/* 09AAF4 80099EF4 AFA000D0 */  sw    $zero, 0xd0($sp)
.L80099EF8:
/* 09AAF8 80099EF8 8F1863D8 */  lw    $t8, %lo(gOpacityDecayTimer)($t8)
/* 09AAFC 80099EFC 0C0310BB */  jal   set_text_font
/* 09AB00 80099F00 AFB800E4 */   sw    $t8, 0xe4($sp)
/* 09AB04 80099F04 00002025 */  move  $a0, $zero
/* 09AB08 80099F08 00002825 */  move  $a1, $zero
/* 09AB0C 80099F0C 00003025 */  move  $a2, $zero
/* 09AB10 80099F10 0C0310F3 */  jal   set_text_background_colour
/* 09AB14 80099F14 00003825 */   move  $a3, $zero
/* 09AB18 80099F18 24190080 */  li    $t9, 128
/* 09AB1C 80099F1C AFB90010 */  sw    $t9, 0x10($sp)
/* 09AB20 80099F20 00002025 */  move  $a0, $zero
/* 09AB24 80099F24 00002825 */  move  $a1, $zero
/* 09AB28 80099F28 00003025 */  move  $a2, $zero
/* 09AB2C 80099F2C 0C0310E1 */  jal   set_text_colour
/* 09AB30 80099F30 240700FF */   li    $a3, 255
/* 09AB34 80099F34 3C09800E */  lui   $t1, %hi(gMenuText) # $t1, 0x800e
/* 09AB38 80099F38 8D29F4A0 */  lw    $t1, %lo(gMenuText)($t1)
/* 09AB3C 80099F3C 240A000C */  li    $t2, 12
/* 09AB40 80099F40 8D270148 */  lw    $a3, 0x148($t1)
/* 09AB44 80099F44 AFAA0010 */  sw    $t2, 0x10($sp)
/* 09AB48 80099F48 02E02025 */  move  $a0, $s7
/* 09AB4C 80099F4C 240500A1 */  li    $a1, 161
/* 09AB50 80099F50 0C031110 */  jal   draw_text
/* 09AB54 80099F54 24060023 */   li    $a2, 35
/* 09AB58 80099F58 240B00FF */  li    $t3, 255
/* 09AB5C 80099F5C AFAB0010 */  sw    $t3, 0x10($sp)
/* 09AB60 80099F60 240400FF */  li    $a0, 255
/* 09AB64 80099F64 240500FF */  li    $a1, 255
/* 09AB68 80099F68 240600FF */  li    $a2, 255
/* 09AB6C 80099F6C 0C0310E1 */  jal   set_text_colour
/* 09AB70 80099F70 00003825 */   move  $a3, $zero
/* 09AB74 80099F74 3C0C800E */  lui   $t4, %hi(gMenuText) # $t4, 0x800e
/* 09AB78 80099F78 8D8CF4A0 */  lw    $t4, %lo(gMenuText)($t4)
/* 09AB7C 80099F7C 240D000C */  li    $t5, 12
/* 09AB80 80099F80 8D870148 */  lw    $a3, 0x148($t4)
/* 09AB84 80099F84 AFAD0010 */  sw    $t5, 0x10($sp)
/* 09AB88 80099F88 02E02025 */  move  $a0, $s7
/* 09AB8C 80099F8C 240500A0 */  li    $a1, 160
/* 09AB90 80099F90 0C031110 */  jal   draw_text
/* 09AB94 80099F94 24060020 */   li    $a2, 32
/* 09AB98 80099F98 3C0E8012 */  lui   $t6, %hi(D_801264D4) # $t6, 0x8012
/* 09AB9C 80099F9C 8DCE64D4 */  lw    $t6, %lo(D_801264D4)($t6)
/* 09ABA0 80099FA0 24120038 */  li    $s2, 56
/* 09ABA4 80099FA4 1DC00014 */  bgtz  $t6, .L80099FF8
/* 09ABA8 80099FA8 24090003 */   li    $t1, 3
/* 09ABAC 80099FAC 240F00FF */  li    $t7, 255
/* 09ABB0 80099FB0 AFAF0010 */  sw    $t7, 0x10($sp)
/* 09ABB4 80099FB4 240400FF */  li    $a0, 255
/* 09ABB8 80099FB8 240500FF */  li    $a1, 255
/* 09ABBC 80099FBC 240600FF */  li    $a2, 255
/* 09ABC0 80099FC0 0C0310E1 */  jal   set_text_colour
/* 09ABC4 80099FC4 00003825 */   move  $a3, $zero
/* 09ABC8 80099FC8 3C18800E */  lui   $t8, %hi(gMenuText) # $t8, 0x800e
/* 09ABCC 80099FCC 8F18F4A0 */  lw    $t8, %lo(gMenuText)($t8)
/* 09ABD0 80099FD0 8FA600D0 */  lw    $a2, 0xd0($sp)
/* 09ABD4 80099FD4 2419000C */  li    $t9, 12
/* 09ABD8 80099FD8 8F07014C */  lw    $a3, 0x14c($t8)
/* 09ABDC 80099FDC AFB90010 */  sw    $t9, 0x10($sp)
/* 09ABE0 80099FE0 02E02025 */  move  $a0, $s7
/* 09ABE4 80099FE4 240500A0 */  li    $a1, 160
/* 09ABE8 80099FE8 0C031110 */  jal   draw_text
/* 09ABEC 80099FEC 24C60078 */   addiu $a2, $a2, 0x78
/* 09ABF0 80099FF0 100001ED */  b     .L8009A7A8
/* 09ABF4 80099FF4 8FBF005C */   lw    $ra, 0x5c($sp)
.L80099FF8:
/* 09ABF8 80099FF8 3C028012 */  lui   $v0, %hi(gOptionBlinkTimer) # $v0, 0x8012
/* 09ABFC 80099FFC 8C4263BC */  lw    $v0, %lo(gOptionBlinkTimer)($v0)
/* 09AC00 8009A000 AFA900E8 */  sw    $t1, 0xe8($sp)
/* 09AC04 8009A004 000250C0 */  sll   $t2, $v0, 3
/* 09AC08 8009A008 29410100 */  slti  $at, $t2, 0x100
/* 09AC0C 8009A00C 14200003 */  bnez  $at, .L8009A01C
/* 09AC10 8009A010 01401025 */   move  $v0, $t2
/* 09AC14 8009A014 240B01FF */  li    $t3, 511
/* 09AC18 8009A018 016A1023 */  subu  $v0, $t3, $t2
.L8009A01C:
/* 09AC1C 8009A01C 2401FF00 */  li    $at, -256
/* 09AC20 8009A020 00416025 */  or    $t4, $v0, $at
/* 09AC24 8009A024 AFAC00D8 */  sw    $t4, 0xd8($sp)
/* 09AC28 8009A028 0C0310BB */  jal   set_text_font
/* 09AC2C 8009A02C 24040001 */   li    $a0, 1
/* 09AC30 8009A030 3C0D8012 */  lui   $t5, %hi(D_801264D4) # $t5, 0x8012
/* 09AC34 8009A034 8FA200E4 */  lw    $v0, 0xe4($sp)
/* 09AC38 8009A038 8DAD64D4 */  lw    $t5, %lo(D_801264D4)($t5)
/* 09AC3C 8009A03C 3C0E8012 */  lui   $t6, %hi(D_80126508) # $t6, 0x8012
/* 09AC40 8009A040 004D082A */  slt   $at, $v0, $t5
/* 09AC44 8009A044 1020012B */  beqz  $at, .L8009A4F4
/* 09AC48 8009A048 25CE6508 */   addiu $t6, %lo(D_80126508) # addiu $t6, $t6, 0x6508
/* 09AC4C 8009A04C 240D0028 */  li    $t5, 40
/* 09AC50 8009A050 448D2000 */  mtc1  $t5, $f4
/* 09AC54 8009A054 3C0F8012 */  lui   $t7, %hi(D_80126510) # $t7, 0x8012
/* 09AC58 8009A058 468021A0 */  cvt.s.w $f6, $f4
/* 09AC5C 8009A05C 3C198012 */  lui   $t9, %hi(D_80126518) # $t9, 0x8012
/* 09AC60 8009A060 3C0B8012 */  lui   $t3, %hi(D_80126520) # $t3, 0x8012
/* 09AC64 8009A064 256B6520 */  addiu $t3, %lo(D_80126520) # addiu $t3, $t3, 0x6520
/* 09AC68 8009A068 27396518 */  addiu $t9, %lo(D_80126518) # addiu $t9, $t9, 0x6518
/* 09AC6C 8009A06C 25EF6510 */  addiu $t7, %lo(D_80126510) # addiu $t7, $t7, 0x6510
/* 09AC70 8009A070 00025040 */  sll   $t2, $v0, 1
/* 09AC74 8009A074 014B6021 */  addu  $t4, $t2, $t3
/* 09AC78 8009A078 004FC021 */  addu  $t8, $v0, $t7
/* 09AC7C 8009A07C 00594821 */  addu  $t1, $v0, $t9
/* 09AC80 8009A080 3C15800E */  lui   $s5, %hi(D_800E1E20) # $s5, 0x800e
/* 09AC84 8009A084 3C11800E */  lui   $s1, %hi(D_800E1754) # $s1, 0x800e
/* 09AC88 8009A088 26311754 */  addiu $s1, %lo(D_800E1754) # addiu $s1, $s1, 0x1754
/* 09AC8C 8009A08C 26B51E20 */  addiu $s5, %lo(D_800E1E20) # addiu $s5, $s5, 0x1e20
/* 09AC90 8009A090 AFA90070 */  sw    $t1, 0x70($sp)
/* 09AC94 8009A094 AFB80074 */  sw    $t8, 0x74($sp)
/* 09AC98 8009A098 AFAC006C */  sw    $t4, 0x6c($sp)
/* 09AC9C 8009A09C E7A60068 */  swc1  $f6, 0x68($sp)
/* 09ACA0 8009A0A0 004EF021 */  addu  $fp, $v0, $t6
/* 09ACA4 8009A0A4 24160004 */  li    $s6, 4
/* 09ACA8 8009A0A8 2414003F */  li    $s4, 63
/* 09ACAC 8009A0AC 27B30088 */  addiu $s3, $sp, 0x88
.L8009A0B0:
/* 09ACB0 8009A0B0 93C40000 */  lbu   $a0, ($fp)
/* 09ACB4 8009A0B4 0C01AC64 */  jal   func_8006B190
/* 09ACB8 8009A0B8 00000000 */   nop   
/* 09ACBC 8009A0BC 2443FFFF */  addiu $v1, $v0, -1
/* 09ACC0 8009A0C0 04600004 */  bltz  $v1, .L8009A0D4
/* 09ACC4 8009A0C4 00604025 */   move  $t0, $v1
/* 09ACC8 8009A0C8 28610005 */  slti  $at, $v1, 5
/* 09ACCC 8009A0CC 14200002 */  bnez  $at, .L8009A0D8
/* 09ACD0 8009A0D0 00000000 */   nop   
.L8009A0D4:
/* 09ACD4 8009A0D4 00004025 */  move  $t0, $zero
.L8009A0D8:
/* 09ACD8 8009A0D8 93C40000 */  lbu   $a0, ($fp)
/* 09ACDC 8009A0DC 0C01AF77 */  jal   get_level_name
/* 09ACE0 8009A0E0 AFA800EC */   sw    $t0, 0xec($sp)
/* 09ACE4 8009A0E4 904E0000 */  lbu   $t6, ($v0)
/* 09ACE8 8009A0E8 8FA800EC */  lw    $t0, 0xec($sp)
/* 09ACEC 8009A0EC 11C00013 */  beqz  $t6, .L8009A13C
/* 09ACF0 8009A0F0 00008025 */   move  $s0, $zero
/* 09ACF4 8009A0F4 90450000 */  lbu   $a1, ($v0)
/* 09ACF8 8009A0F8 02602021 */  addu  $a0, $s3, $zero
/* 09ACFC 8009A0FC 00403021 */  addu  $a2, $v0, $zero
/* 09AD00 8009A100 30A300FF */  andi  $v1, $a1, 0xff
.L8009A104:
/* 09AD04 8009A104 28610061 */  slti  $at, $v1, 0x61
/* 09AD08 8009A108 14200005 */  bnez  $at, .L8009A120
/* 09AD0C 8009A10C A0850000 */   sb    $a1, ($a0)
/* 09AD10 8009A110 2861007B */  slti  $at, $v1, 0x7b
/* 09AD14 8009A114 10200002 */  beqz  $at, .L8009A120
/* 09AD18 8009A118 386F0020 */   xori  $t7, $v1, 0x20
/* 09AD1C 8009A11C A08F0000 */  sb    $t7, ($a0)
.L8009A120:
/* 09AD20 8009A120 90C50001 */  lbu   $a1, 1($a2)
/* 09AD24 8009A124 26100001 */  addiu $s0, $s0, 1
/* 09AD28 8009A128 24840001 */  addiu $a0, $a0, 1
/* 09AD2C 8009A12C 10A00003 */  beqz  $a1, .L8009A13C
/* 09AD30 8009A130 24C60001 */   addiu $a2, $a2, 1
/* 09AD34 8009A134 1614FFF3 */  bne   $s0, $s4, .L8009A104
/* 09AD38 8009A138 30A300FF */   andi  $v1, $a1, 0xff
.L8009A13C:
/* 09AD3C 8009A13C 44924000 */  mtc1  $s2, $f8
/* 09AD40 8009A140 0270C021 */  addu  $t8, $s3, $s0
/* 09AD44 8009A144 A3000000 */  sb    $zero, ($t8)
/* 09AD48 8009A148 3C013F40 */  li    $at, 0x3F400000 # 0.750000
/* 09AD4C 8009A14C 46804220 */  cvt.s.w $f8, $f8
/* 09AD50 8009A150 44815000 */  mtc1  $at, $f10
/* 09AD54 8009A154 3C013F50 */  li    $at, 0x3F500000 # 0.812500
/* 09AD58 8009A158 0008C880 */  sll   $t9, $t0, 2
/* 09AD5C 8009A15C 3C05800E */  lui   $a1, %hi(D_800E16F4) # $a1, 0x800e
/* 09AD60 8009A160 44818000 */  mtc1  $at, $f16
/* 09AD64 8009A164 00B92821 */  addu  $a1, $a1, $t9
/* 09AD68 8009A168 8CA516F4 */  lw    $a1, %lo(D_800E16F4)($a1)
/* 09AD6C 8009A16C 44074000 */  mfc1  $a3, $f8
/* 09AD70 8009A170 8FA60068 */  lw    $a2, 0x68($sp)
/* 09AD74 8009A174 2409FFFF */  li    $t1, -1
/* 09AD78 8009A178 AFA90018 */  sw    $t1, 0x18($sp)
/* 09AD7C 8009A17C AFA0001C */  sw    $zero, 0x1c($sp)
/* 09AD80 8009A180 00008025 */  move  $s0, $zero
/* 09AD84 8009A184 02E02025 */  move  $a0, $s7
/* 09AD88 8009A188 E7AA0010 */  swc1  $f10, 0x10($sp)
/* 09AD8C 8009A18C 0C01E340 */  jal   render_texture_rectangle_scaled
/* 09AD90 8009A190 E7B00014 */   swc1  $f16, 0x14($sp)
/* 09AD94 8009A194 240A0034 */  li    $t2, 52
/* 09AD98 8009A198 240B0020 */  li    $t3, 32
/* 09AD9C 8009A19C 240C0050 */  li    $t4, 80
/* 09ADA0 8009A1A0 240D00B0 */  li    $t5, 176
/* 09ADA4 8009A1A4 240E0080 */  li    $t6, 128
/* 09ADA8 8009A1A8 AFAE0028 */  sw    $t6, 0x28($sp)
/* 09ADAC 8009A1AC AFAD0024 */  sw    $t5, 0x24($sp)
/* 09ADB0 8009A1B0 AFAC0020 */  sw    $t4, 0x20($sp)
/* 09ADB4 8009A1B4 AFAB001C */  sw    $t3, 0x1c($sp)
/* 09ADB8 8009A1B8 AFAA0010 */  sw    $t2, 0x10($sp)
/* 09ADBC 8009A1BC 02E02025 */  move  $a0, $s7
/* 09ADC0 8009A1C0 24050028 */  li    $a1, 40
/* 09ADC4 8009A1C4 02403025 */  move  $a2, $s2
/* 09ADC8 8009A1C8 240700F0 */  li    $a3, 240
/* 09ADCC 8009A1CC AFB60014 */  sw    $s6, 0x14($sp)
/* 09ADD0 8009A1D0 0C0203A4 */  jal   func_80080E90
/* 09ADD4 8009A1D4 AFB60018 */   sw    $s6, 0x18($sp)
/* 09ADD8 8009A1D8 3C188012 */  lui   $t8, %hi(D_80126498) # $t8, 0x8012
/* 09ADDC 8009A1DC 8F186498 */  lw    $t8, %lo(D_80126498)($t8)
/* 09ADE0 8009A1E0 8FAF00E4 */  lw    $t7, 0xe4($sp)
/* 09ADE4 8009A1E4 8FA200D8 */  lw    $v0, 0xd8($sp)
/* 09ADE8 8009A1E8 15F8000D */  bne   $t7, $t8, .L8009A220
/* 09ADEC 8009A1EC 02E02025 */   move  $a0, $s7
/* 09ADF0 8009A1F0 24190034 */  li    $t9, 52
/* 09ADF4 8009A1F4 AFB90010 */  sw    $t9, 0x10($sp)
/* 09ADF8 8009A1F8 24050028 */  li    $a1, 40
/* 09ADFC 8009A1FC 02403025 */  move  $a2, $s2
/* 09AE00 8009A200 240700F0 */  li    $a3, 240
/* 09AE04 8009A204 AFB60014 */  sw    $s6, 0x14($sp)
/* 09AE08 8009A208 AFB60018 */  sw    $s6, 0x18($sp)
/* 09AE0C 8009A20C AFA2001C */  sw    $v0, 0x1c($sp)
/* 09AE10 8009A210 AFA20020 */  sw    $v0, 0x20($sp)
/* 09AE14 8009A214 AFA20024 */  sw    $v0, 0x24($sp)
/* 09AE18 8009A218 0C0203A4 */  jal   func_80080E90
/* 09AE1C 8009A21C AFA20028 */   sw    $v0, 0x28($sp)
.L8009A220:
/* 09AE20 8009A220 240900FF */  li    $t1, 255
/* 09AE24 8009A224 AFA90010 */  sw    $t1, 0x10($sp)
/* 09AE28 8009A228 00002025 */  move  $a0, $zero
/* 09AE2C 8009A22C 00002825 */  move  $a1, $zero
/* 09AE30 8009A230 00003025 */  move  $a2, $zero
/* 09AE34 8009A234 0C0310E1 */  jal   set_text_colour
/* 09AE38 8009A238 240700FF */   li    $a3, 255
/* 09AE3C 8009A23C 00105040 */  sll   $t2, $s0, 1
.L8009A240:
/* 09AE40 8009A240 02AA1021 */  addu  $v0, $s5, $t2
/* 09AE44 8009A244 804B0000 */  lb    $t3, ($v0)
/* 09AE48 8009A248 804D0001 */  lb    $t5, 1($v0)
/* 09AE4C 8009A24C 862C0000 */  lh    $t4, ($s1)
/* 09AE50 8009A250 862F0002 */  lh    $t7, 2($s1)
/* 09AE54 8009A254 2418000C */  li    $t8, 12
/* 09AE58 8009A258 01B27021 */  addu  $t6, $t5, $s2
/* 09AE5C 8009A25C 016C2821 */  addu  $a1, $t3, $t4
/* 09AE60 8009A260 24A50028 */  addiu $a1, $a1, 0x28
/* 09AE64 8009A264 AFB80010 */  sw    $t8, 0x10($sp)
/* 09AE68 8009A268 02E02025 */  move  $a0, $s7
/* 09AE6C 8009A26C 02603825 */  move  $a3, $s3
/* 09AE70 8009A270 0C031110 */  jal   draw_text
/* 09AE74 8009A274 01CF3021 */   addu  $a2, $t6, $t7
/* 09AE78 8009A278 26100001 */  addiu $s0, $s0, 1
/* 09AE7C 8009A27C 1616FFF0 */  bne   $s0, $s6, .L8009A240
/* 09AE80 8009A280 00105040 */   sll   $t2, $s0, 1
/* 09AE84 8009A284 241900FF */  li    $t9, 255
/* 09AE88 8009A288 AFB90010 */  sw    $t9, 0x10($sp)
/* 09AE8C 8009A28C 240400C8 */  li    $a0, 200
/* 09AE90 8009A290 240500E4 */  li    $a1, 228
/* 09AE94 8009A294 24060050 */  li    $a2, 80
/* 09AE98 8009A298 0C0310E1 */  jal   set_text_colour
/* 09AE9C 8009A29C 240700FF */   li    $a3, 255
/* 09AEA0 8009A2A0 86250000 */  lh    $a1, ($s1)
/* 09AEA4 8009A2A4 86290002 */  lh    $t1, 2($s1)
/* 09AEA8 8009A2A8 240A000C */  li    $t2, 12
/* 09AEAC 8009A2AC AFAA0010 */  sw    $t2, 0x10($sp)
/* 09AEB0 8009A2B0 02E02025 */  move  $a0, $s7
/* 09AEB4 8009A2B4 02603825 */  move  $a3, $s3
/* 09AEB8 8009A2B8 24A50028 */  addiu $a1, $a1, 0x28
/* 09AEBC 8009A2BC 0C031110 */  jal   draw_text
/* 09AEC0 8009A2C0 01323021 */   addu  $a2, $t1, $s2
/* 09AEC4 8009A2C4 8FAB0074 */  lw    $t3, 0x74($sp)
/* 09AEC8 8009A2C8 3C05800E */  lui   $a1, %hi(D_800E0AF0) # $a1, 0x800e
/* 09AECC 8009A2CC 916C0000 */  lbu   $t4, ($t3)
/* 09AED0 8009A2D0 86260004 */  lh    $a2, 4($s1)
/* 09AED4 8009A2D4 000C6880 */  sll   $t5, $t4, 2
/* 09AED8 8009A2D8 862E0006 */  lh    $t6, 6($s1)
/* 09AEDC 8009A2DC 00AD2821 */  addu  $a1, $a1, $t5
/* 09AEE0 8009A2E0 8CA50AF0 */  lw    $a1, %lo(D_800E0AF0)($a1)
/* 09AEE4 8009A2E4 240F00FF */  li    $t7, 255
/* 09AEE8 8009A2E8 241800FF */  li    $t8, 255
/* 09AEEC 8009A2EC 241900FF */  li    $t9, 255
/* 09AEF0 8009A2F0 240900FF */  li    $t1, 255
/* 09AEF4 8009A2F4 AFA9001C */  sw    $t1, 0x1c($sp)
/* 09AEF8 8009A2F8 AFB90018 */  sw    $t9, 0x18($sp)
/* 09AEFC 8009A2FC AFB80014 */  sw    $t8, 0x14($sp)
/* 09AF00 8009A300 AFAF0010 */  sw    $t7, 0x10($sp)
/* 09AF04 8009A304 02E02025 */  move  $a0, $s7
/* 09AF08 8009A308 24C60028 */  addiu $a2, $a2, 0x28
/* 09AF0C 8009A30C 0C01E2AE */  jal   render_textured_rectangle
/* 09AF10 8009A310 01D23821 */   addu  $a3, $t6, $s2
/* 09AF14 8009A314 8FAA0070 */  lw    $t2, 0x70($sp)
/* 09AF18 8009A318 24010001 */  li    $at, 1
/* 09AF1C 8009A31C 91420000 */  lbu   $v0, ($t2)
/* 09AF20 8009A320 02E02025 */  move  $a0, $s7
/* 09AF24 8009A324 10410007 */  beq   $v0, $at, .L8009A344
/* 09AF28 8009A328 240FFFFF */   li    $t7, -1
/* 09AF2C 8009A32C 24010002 */  li    $at, 2
/* 09AF30 8009A330 10410007 */  beq   $v0, $at, .L8009A350
/* 09AF34 8009A334 3C05800E */   lui   $a1, %hi(gRaceSelectionPlaneTex) # $a1, 0x800e
/* 09AF38 8009A338 3C05800E */  lui   $a1, %hi(gRaceSelectionCarTex) # $a1, 0x800e
/* 09AF3C 8009A33C 10000005 */  b     .L8009A354
/* 09AF40 8009A340 24A5045C */   addiu $a1, %lo(gRaceSelectionCarTex) # addiu $a1, $a1, 0x45c
.L8009A344:
/* 09AF44 8009A344 3C05800E */  lui   $a1, %hi(gRaceSelectionHoverTex) # $a1, 0x800e
/* 09AF48 8009A348 10000002 */  b     .L8009A354
/* 09AF4C 8009A34C 24A50474 */   addiu $a1, %lo(gRaceSelectionHoverTex) # addiu $a1, $a1, 0x474
.L8009A350:
/* 09AF50 8009A350 24A5048C */  addiu $a1, %lo(gRaceSelectionPlaneTex) # addiu $a1, $a1, 0x48c
.L8009A354:
/* 09AF54 8009A354 862B0008 */  lh    $t3, 8($s1)
/* 09AF58 8009A358 862D000A */  lh    $t5, 0xa($s1)
/* 09AF5C 8009A35C 256C0028 */  addiu $t4, $t3, 0x28
/* 09AF60 8009A360 01B27021 */  addu  $t6, $t5, $s2
/* 09AF64 8009A364 448E2000 */  mtc1  $t6, $f4
/* 09AF68 8009A368 448C9000 */  mtc1  $t4, $f18
/* 09AF6C 8009A36C 46802120 */  cvt.s.w $f4, $f4
/* 09AF70 8009A370 3C013F20 */  li    $at, 0x3F200000 # 0.625000
/* 09AF74 8009A374 44810000 */  mtc1  $at, $f0
/* 09AF78 8009A378 468094A0 */  cvt.s.w $f18, $f18
/* 09AF7C 8009A37C 44072000 */  mfc1  $a3, $f4
/* 09AF80 8009A380 AFAF0018 */  sw    $t7, 0x18($sp)
/* 09AF84 8009A384 44069000 */  mfc1  $a2, $f18
/* 09AF88 8009A388 AFA0001C */  sw    $zero, 0x1c($sp)
/* 09AF8C 8009A38C E7A00010 */  swc1  $f0, 0x10($sp)
/* 09AF90 8009A390 0C01E340 */  jal   render_texture_rectangle_scaled
/* 09AF94 8009A394 E7A00014 */   swc1  $f0, 0x14($sp)
/* 09AF98 8009A398 0C01ECF4 */  jal   reset_render_settings
/* 09AF9C 8009A39C 02E02025 */   move  $a0, $s7
/* 09AFA0 8009A3A0 8638000C */  lh    $t8, 0xc($s1)
/* 09AFA4 8009A3A4 3C02800E */  lui   $v0, %hi(gMenuImageStack) # $v0, 0x800e
/* 09AFA8 8009A3A8 2719FF88 */  addiu $t9, $t8, -0x78
/* 09AFAC 8009A3AC 44993000 */  mtc1  $t9, $f6
/* 09AFB0 8009A3B0 2442F75C */  addiu $v0, %lo(gMenuImageStack) # addiu $v0, $v0, -0x8a4
/* 09AFB4 8009A3B4 46803220 */  cvt.s.w $f8, $f6
/* 09AFB8 8009A3B8 8C490000 */  lw    $t1, ($v0)
/* 09AFBC 8009A3BC 3C01800F */  lui   $at, %hi(D_800E8570) # $at, 0x800f
/* 09AFC0 8009A3C0 E52800EC */  swc1  $f8, 0xec($t1)
/* 09AFC4 8009A3C4 862A000E */  lh    $t2, 0xe($s1)
/* 09AFC8 8009A3C8 8FAD00D0 */  lw    $t5, 0xd0($sp)
/* 09AFCC 8009A3CC 000A5823 */  negu  $t3, $t2
/* 09AFD0 8009A3D0 01726023 */  subu  $t4, $t3, $s2
/* 09AFD4 8009A3D4 018D7021 */  addu  $t6, $t4, $t5
/* 09AFD8 8009A3D8 25CF0078 */  addiu $t7, $t6, 0x78
/* 09AFDC 8009A3DC 448F5000 */  mtc1  $t7, $f10
/* 09AFE0 8009A3E0 8C580000 */  lw    $t8, ($v0)
/* 09AFE4 8009A3E4 46805420 */  cvt.s.w $f16, $f10
/* 09AFE8 8009A3E8 24040007 */  li    $a0, 7
/* 09AFEC 8009A3EC E71000F0 */  swc1  $f16, 0xf0($t8)
/* 09AFF0 8009A3F0 8C590000 */  lw    $t9, ($v0)
/* 09AFF4 8009A3F4 C4328570 */  lwc1  $f18, %lo(D_800E8570)($at)
/* 09AFF8 8009A3F8 0C027298 */  jal   func_8009CA60
/* 09AFFC 8009A3FC E73200E8 */   swc1  $f18, 0xe8($t9)
/* 09B000 8009A400 24090080 */  li    $t1, 128
/* 09B004 8009A404 3C01800E */  lui   $at, %hi(sMenuGuiOpacity) # $at, 0x800e
/* 09B008 8009A408 AC29F764 */  sw    $t1, %lo(sMenuGuiOpacity)($at)
/* 09B00C 8009A40C 862B0012 */  lh    $t3, 0x12($s1)
/* 09B010 8009A410 8FAA006C */  lw    $t2, 0x6c($sp)
/* 09B014 8009A414 8FAE00D0 */  lw    $t6, 0xd0($sp)
/* 09B018 8009A418 000B6023 */  negu  $t4, $t3
/* 09B01C 8009A41C 95440000 */  lhu   $a0, ($t2)
/* 09B020 8009A420 86250010 */  lh    $a1, 0x10($s1)
/* 09B024 8009A424 01926823 */  subu  $t5, $t4, $s2
/* 09B028 8009A428 01AE3021 */  addu  $a2, $t5, $t6
/* 09B02C 8009A42C 24C60077 */  addiu $a2, $a2, 0x77
/* 09B030 8009A430 AFA00018 */  sw    $zero, 0x18($sp)
/* 09B034 8009A434 AFA00014 */  sw    $zero, 0x14($sp)
/* 09B038 8009A438 AFA00010 */  sw    $zero, 0x10($sp)
/* 09B03C 8009A43C 00003825 */  move  $a3, $zero
/* 09B040 8009A440 0C020600 */  jal   show_timestamp
/* 09B044 8009A444 24A5FF89 */   addiu $a1, $a1, -0x77
/* 09B048 8009A448 240F00FF */  li    $t7, 255
/* 09B04C 8009A44C 3C01800E */  lui   $at, %hi(sMenuGuiOpacity) # $at, 0x800e
/* 09B050 8009A450 AC2FF764 */  sw    $t7, %lo(sMenuGuiOpacity)($at)
/* 09B054 8009A454 86390012 */  lh    $t9, 0x12($s1)
/* 09B058 8009A458 8FB8006C */  lw    $t8, 0x6c($sp)
/* 09B05C 8009A45C 8FAB00D0 */  lw    $t3, 0xd0($sp)
/* 09B060 8009A460 00194823 */  negu  $t1, $t9
/* 09B064 8009A464 97040000 */  lhu   $a0, ($t8)
/* 09B068 8009A468 86250010 */  lh    $a1, 0x10($s1)
/* 09B06C 8009A46C 01325023 */  subu  $t2, $t1, $s2
/* 09B070 8009A470 240C00C0 */  li    $t4, 192
/* 09B074 8009A474 240D00FF */  li    $t5, 255
/* 09B078 8009A478 014B3021 */  addu  $a2, $t2, $t3
/* 09B07C 8009A47C 24C60079 */  addiu $a2, $a2, 0x79
/* 09B080 8009A480 AFAD0014 */  sw    $t5, 0x14($sp)
/* 09B084 8009A484 AFAC0010 */  sw    $t4, 0x10($sp)
/* 09B088 8009A488 AFA00018 */  sw    $zero, 0x18($sp)
/* 09B08C 8009A48C 240700FF */  li    $a3, 255
/* 09B090 8009A490 0C020600 */  jal   show_timestamp
/* 09B094 8009A494 24A5FF87 */   addiu $a1, $a1, -0x79
/* 09B098 8009A498 8FB80074 */  lw    $t8, 0x74($sp)
/* 09B09C 8009A49C 8FAE00E4 */  lw    $t6, 0xe4($sp)
/* 09B0A0 8009A4A0 27190001 */  addiu $t9, $t8, 1
/* 09B0A4 8009A4A4 3C188012 */  lui   $t8, %hi(D_801264D4) # $t8, 0x8012
/* 09B0A8 8009A4A8 8FA90070 */  lw    $t1, 0x70($sp)
/* 09B0AC 8009A4AC 8FAB006C */  lw    $t3, 0x6c($sp)
/* 09B0B0 8009A4B0 8FAD00E8 */  lw    $t5, 0xe8($sp)
/* 09B0B4 8009A4B4 8F1864D4 */  lw    $t8, %lo(D_801264D4)($t8)
/* 09B0B8 8009A4B8 25CF0001 */  addiu $t7, $t6, 1
/* 09B0BC 8009A4BC 252A0001 */  addiu $t2, $t1, 1
/* 09B0C0 8009A4C0 256C0002 */  addiu $t4, $t3, 2
/* 09B0C4 8009A4C4 25AEFFFF */  addiu $t6, $t5, -1
/* 09B0C8 8009A4C8 01F8082A */  slt   $at, $t7, $t8
/* 09B0CC 8009A4CC AFAC006C */  sw    $t4, 0x6c($sp)
/* 09B0D0 8009A4D0 AFAA0070 */  sw    $t2, 0x70($sp)
/* 09B0D4 8009A4D4 AFAF00E4 */  sw    $t7, 0xe4($sp)
/* 09B0D8 8009A4D8 AFB90074 */  sw    $t9, 0x74($sp)
/* 09B0DC 8009A4DC 27DE0001 */  addiu $fp, $fp, 1
/* 09B0E0 8009A4E0 AFAE00E8 */  sw    $t6, 0xe8($sp)
/* 09B0E4 8009A4E4 10200003 */  beqz  $at, .L8009A4F4
/* 09B0E8 8009A4E8 26520036 */   addiu $s2, $s2, 0x36
/* 09B0EC 8009A4EC 1DC0FEF0 */  bgtz  $t6, .L8009A0B0
/* 09B0F0 8009A4F0 00000000 */   nop   
.L8009A4F4:
/* 09B0F4 8009A4F4 3C108012 */  lui   $s0, %hi(D_801263E0) # $s0, 0x8012
/* 09B0F8 8009A4F8 8FB900D8 */  lw    $t9, 0xd8($sp)
/* 09B0FC 8009A4FC 261063E0 */  addiu $s0, %lo(D_801263E0) # addiu $s0, $s0, 0x63e0
/* 09B100 8009A500 8E0A0000 */  lw    $t2, ($s0)
/* 09B104 8009A504 332900FF */  andi  $t1, $t9, 0xff
/* 09B108 8009A508 19400063 */  blez  $t2, .L8009A698
/* 09B10C 8009A50C AFA900D8 */   sw    $t1, 0xd8($sp)
/* 09B110 8009A510 0C0315B4 */  jal   func_800C56D0
/* 09B114 8009A514 24040007 */   li    $a0, 7
/* 09B118 8009A518 0C031525 */  jal   assign_dialogue_box_id
/* 09B11C 8009A51C 24040007 */   li    $a0, 7
/* 09B120 8009A520 240B008A */  li    $t3, 138
/* 09B124 8009A524 AFAB0010 */  sw    $t3, 0x10($sp)
/* 09B128 8009A528 24040007 */  li    $a0, 7
/* 09B12C 8009A52C 24050068 */  li    $a1, 104
/* 09B130 8009A530 24060066 */  li    $a2, 102
/* 09B134 8009A534 0C0313B7 */  jal   set_current_dialogue_box_coords
/* 09B138 8009A538 240700D8 */   li    $a3, 216
/* 09B13C 8009A53C 240C00C0 */  li    $t4, 192
/* 09B140 8009A540 AFAC0010 */  sw    $t4, 0x10($sp)
/* 09B144 8009A544 24040007 */  li    $a0, 7
/* 09B148 8009A548 00002825 */  move  $a1, $zero
/* 09B14C 8009A54C 00003025 */  move  $a2, $zero
/* 09B150 8009A550 0C0313EF */  jal   set_current_dialogue_background_colour
/* 09B154 8009A554 00003825 */   move  $a3, $zero
/* 09B158 8009A558 24040007 */  li    $a0, 7
/* 09B15C 8009A55C 0C0313DF */  jal   set_dialogue_font
/* 09B160 8009A560 00002825 */   move  $a1, $zero
/* 09B164 8009A564 24040007 */  li    $a0, 7
/* 09B168 8009A568 00002825 */  move  $a1, $zero
/* 09B16C 8009A56C 00003025 */  move  $a2, $zero
/* 09B170 8009A570 00003825 */  move  $a3, $zero
/* 09B174 8009A574 0C031414 */  jal   set_current_text_background_colour
/* 09B178 8009A578 AFA00010 */   sw    $zero, 0x10($sp)
/* 09B17C 8009A57C 8E0D0000 */  lw    $t5, ($s0)
/* 09B180 8009A580 24010001 */  li    $at, 1
/* 09B184 8009A584 15A1000C */  bne   $t5, $at, .L8009A5B8
/* 09B188 8009A588 24040007 */   li    $a0, 7
/* 09B18C 8009A58C 8FAF00D8 */  lw    $t7, 0xd8($sp)
/* 09B190 8009A590 241800FF */  li    $t8, 255
/* 09B194 8009A594 AFB80014 */  sw    $t8, 0x14($sp)
/* 09B198 8009A598 24040007 */  li    $a0, 7
/* 09B19C 8009A59C 240500FF */  li    $a1, 255
/* 09B1A0 8009A5A0 240600FF */  li    $a2, 255
/* 09B1A4 8009A5A4 240700FF */  li    $a3, 255
/* 09B1A8 8009A5A8 0C031400 */  jal   set_current_text_colour
/* 09B1AC 8009A5AC AFAF0010 */   sw    $t7, 0x10($sp)
/* 09B1B0 8009A5B0 10000008 */  b     .L8009A5D4
/* 09B1B4 8009A5B4 00000000 */   nop   
.L8009A5B8:
/* 09B1B8 8009A5B8 240E00FF */  li    $t6, 255
/* 09B1BC 8009A5BC AFAE0014 */  sw    $t6, 0x14($sp)
/* 09B1C0 8009A5C0 240500FF */  li    $a1, 255
/* 09B1C4 8009A5C4 240600FF */  li    $a2, 255
/* 09B1C8 8009A5C8 240700FF */  li    $a3, 255
/* 09B1CC 8009A5CC 0C031400 */  jal   set_current_text_colour
/* 09B1D0 8009A5D0 AFA00010 */   sw    $zero, 0x10($sp)
.L8009A5D4:
/* 09B1D4 8009A5D4 3C19800E */  lui   $t9, %hi(gMenuText) # $t9, 0x800e
/* 09B1D8 8009A5D8 8F39F4A0 */  lw    $t9, %lo(gMenuText)($t9)
/* 09B1DC 8009A5DC 24090001 */  li    $t1, 1
/* 09B1E0 8009A5E0 8F270150 */  lw    $a3, 0x150($t9)
/* 09B1E4 8009A5E4 240A000C */  li    $t2, 12
/* 09B1E8 8009A5E8 AFAA0014 */  sw    $t2, 0x14($sp)
/* 09B1EC 8009A5EC AFA90010 */  sw    $t1, 0x10($sp)
/* 09B1F0 8009A5F0 24040007 */  li    $a0, 7
/* 09B1F4 8009A5F4 24058000 */  li    $a1, -32768
/* 09B1F8 8009A5F8 0C03145A */  jal   render_dialogue_text
/* 09B1FC 8009A5FC 2406000C */   li    $a2, 12
/* 09B200 8009A600 8E0B0000 */  lw    $t3, ($s0)
/* 09B204 8009A604 24010002 */  li    $at, 2
/* 09B208 8009A608 1561000C */  bne   $t3, $at, .L8009A63C
/* 09B20C 8009A60C 24040007 */   li    $a0, 7
/* 09B210 8009A610 8FAC00D8 */  lw    $t4, 0xd8($sp)
/* 09B214 8009A614 240D00FF */  li    $t5, 255
/* 09B218 8009A618 AFAD0014 */  sw    $t5, 0x14($sp)
/* 09B21C 8009A61C 24040007 */  li    $a0, 7
/* 09B220 8009A620 240500FF */  li    $a1, 255
/* 09B224 8009A624 240600FF */  li    $a2, 255
/* 09B228 8009A628 240700FF */  li    $a3, 255
/* 09B22C 8009A62C 0C031400 */  jal   set_current_text_colour
/* 09B230 8009A630 AFAC0010 */   sw    $t4, 0x10($sp)
/* 09B234 8009A634 10000008 */  b     .L8009A658
/* 09B238 8009A638 00000000 */   nop   
.L8009A63C:
/* 09B23C 8009A63C 240F00FF */  li    $t7, 255
/* 09B240 8009A640 AFAF0014 */  sw    $t7, 0x14($sp)
/* 09B244 8009A644 240500FF */  li    $a1, 255
/* 09B248 8009A648 240600FF */  li    $a2, 255
/* 09B24C 8009A64C 240700FF */  li    $a3, 255
/* 09B250 8009A650 0C031400 */  jal   set_current_text_colour
/* 09B254 8009A654 AFA00010 */   sw    $zero, 0x10($sp)
.L8009A658:
/* 09B258 8009A658 3C18800E */  lui   $t8, %hi(gMenuText) # $t8, 0x800e
/* 09B25C 8009A65C 8F18F4A0 */  lw    $t8, %lo(gMenuText)($t8)
/* 09B260 8009A660 240E0001 */  li    $t6, 1
/* 09B264 8009A664 8F070154 */  lw    $a3, 0x154($t8)
/* 09B268 8009A668 2419000C */  li    $t9, 12
/* 09B26C 8009A66C AFB90014 */  sw    $t9, 0x14($sp)
/* 09B270 8009A670 AFAE0010 */  sw    $t6, 0x10($sp)
/* 09B274 8009A674 24040007 */  li    $a0, 7
/* 09B278 8009A678 24058000 */  li    $a1, -32768
/* 09B27C 8009A67C 0C03145A */  jal   render_dialogue_text
/* 09B280 8009A680 2406001C */   li    $a2, 28
/* 09B284 8009A684 02E02025 */  move  $a0, $s7
/* 09B288 8009A688 00002825 */  move  $a1, $zero
/* 09B28C 8009A68C 00003025 */  move  $a2, $zero
/* 09B290 8009A690 0C0316D6 */  jal   render_dialogue_box
/* 09B294 8009A694 24070007 */   li    $a3, 7
.L8009A698:
/* 09B298 8009A698 3C098012 */  lui   $t1, %hi(gOptionBlinkTimer) # $t1, 0x8012
/* 09B29C 8009A69C 8D2963BC */  lw    $t1, %lo(gOptionBlinkTimer)($t1)
/* 09B2A0 8009A6A0 3C028012 */  lui   $v0, %hi(gOpacityDecayTimer) # $v0, 0x8012
/* 09B2A4 8009A6A4 312A0010 */  andi  $t2, $t1, 0x10
/* 09B2A8 8009A6A8 1140003E */  beqz  $t2, .L8009A7A4
/* 09B2AC 8009A6AC 3C0B8012 */   lui   $t3, %hi(D_801264D4) # $t3, 0x8012
/* 09B2B0 8009A6B0 8C4263D8 */  lw    $v0, %lo(gOpacityDecayTimer)($v0)
/* 09B2B4 8009A6B4 8D6B64D4 */  lw    $t3, %lo(D_801264D4)($t3)
/* 09B2B8 8009A6B8 244C0003 */  addiu $t4, $v0, 3
/* 09B2BC 8009A6BC 018B082A */  slt   $at, $t4, $t3
/* 09B2C0 8009A6C0 1020001C */  beqz  $at, .L8009A734
/* 09B2C4 8009A6C4 3C10800E */   lui   $s0, %hi(gMenuSelectionArrowDown) # $s0, 0x800e
/* 09B2C8 8009A6C8 2610043C */  addiu $s0, %lo(gMenuSelectionArrowDown) # addiu $s0, $s0, 0x43c
/* 09B2CC 8009A6CC 240D0080 */  li    $t5, 128
/* 09B2D0 8009A6D0 AFAD001C */  sw    $t5, 0x1c($sp)
/* 09B2D4 8009A6D4 02002825 */  move  $a1, $s0
/* 09B2D8 8009A6D8 02E02025 */  move  $a0, $s7
/* 09B2DC 8009A6DC 240600A1 */  li    $a2, 161
/* 09B2E0 8009A6E0 26470003 */  addiu $a3, $s2, 3
/* 09B2E4 8009A6E4 AFA00010 */  sw    $zero, 0x10($sp)
/* 09B2E8 8009A6E8 AFA00014 */  sw    $zero, 0x14($sp)
/* 09B2EC 8009A6EC 0C01E2AE */  jal   render_textured_rectangle
/* 09B2F0 8009A6F0 AFA00018 */   sw    $zero, 0x18($sp)
/* 09B2F4 8009A6F4 240F00FF */  li    $t7, 255
/* 09B2F8 8009A6F8 241800FF */  li    $t8, 255
/* 09B2FC 8009A6FC 240E00FF */  li    $t6, 255
/* 09B300 8009A700 241900FF */  li    $t9, 255
/* 09B304 8009A704 AFB9001C */  sw    $t9, 0x1c($sp)
/* 09B308 8009A708 AFAE0018 */  sw    $t6, 0x18($sp)
/* 09B30C 8009A70C AFB80014 */  sw    $t8, 0x14($sp)
/* 09B310 8009A710 AFAF0010 */  sw    $t7, 0x10($sp)
/* 09B314 8009A714 02E02025 */  move  $a0, $s7
/* 09B318 8009A718 02002825 */  move  $a1, $s0
/* 09B31C 8009A71C 2406009F */  li    $a2, 159
/* 09B320 8009A720 0C01E2AE */  jal   render_textured_rectangle
/* 09B324 8009A724 26470001 */   addiu $a3, $s2, 1
/* 09B328 8009A728 3C028012 */  lui   $v0, %hi(gOpacityDecayTimer) # $v0, 0x8012
/* 09B32C 8009A72C 8C4263D8 */  lw    $v0, %lo(gOpacityDecayTimer)($v0)
/* 09B330 8009A730 00000000 */  nop   
.L8009A734:
/* 09B334 8009A734 18400019 */  blez  $v0, .L8009A79C
/* 09B338 8009A738 3C10800E */   lui   $s0, %hi(gMenuSelectionArrowUp) # $s0, 0x800e
/* 09B33C 8009A73C 2610041C */  addiu $s0, %lo(gMenuSelectionArrowUp) # addiu $s0, $s0, 0x41c
/* 09B340 8009A740 24090080 */  li    $t1, 128
/* 09B344 8009A744 AFA9001C */  sw    $t1, 0x1c($sp)
/* 09B348 8009A748 02002825 */  move  $a1, $s0
/* 09B34C 8009A74C 02E02025 */  move  $a0, $s7
/* 09B350 8009A750 240600A1 */  li    $a2, 161
/* 09B354 8009A754 24070036 */  li    $a3, 54
/* 09B358 8009A758 AFA00010 */  sw    $zero, 0x10($sp)
/* 09B35C 8009A75C AFA00014 */  sw    $zero, 0x14($sp)
/* 09B360 8009A760 0C01E2AE */  jal   render_textured_rectangle
/* 09B364 8009A764 AFA00018 */   sw    $zero, 0x18($sp)
/* 09B368 8009A768 240A00FF */  li    $t2, 255
/* 09B36C 8009A76C 240B00FF */  li    $t3, 255
/* 09B370 8009A770 240C00FF */  li    $t4, 255
/* 09B374 8009A774 240D00FF */  li    $t5, 255
/* 09B378 8009A778 AFAD001C */  sw    $t5, 0x1c($sp)
/* 09B37C 8009A77C AFAC0018 */  sw    $t4, 0x18($sp)
/* 09B380 8009A780 AFAB0014 */  sw    $t3, 0x14($sp)
/* 09B384 8009A784 AFAA0010 */  sw    $t2, 0x10($sp)
/* 09B388 8009A788 02E02025 */  move  $a0, $s7
/* 09B38C 8009A78C 02002825 */  move  $a1, $s0
/* 09B390 8009A790 2406009F */  li    $a2, 159
/* 09B394 8009A794 0C01E2AE */  jal   render_textured_rectangle
/* 09B398 8009A798 24070034 */   li    $a3, 52
.L8009A79C:
/* 09B39C 8009A79C 0C01ECF4 */  jal   reset_render_settings
/* 09B3A0 8009A7A0 02E02025 */   move  $a0, $s7
.L8009A7A4:
/* 09B3A4 8009A7A4 8FBF005C */  lw    $ra, 0x5c($sp)
.L8009A7A8:
/* 09B3A8 8009A7A8 8FB00038 */  lw    $s0, 0x38($sp)
/* 09B3AC 8009A7AC 8FB1003C */  lw    $s1, 0x3c($sp)
/* 09B3B0 8009A7B0 8FB20040 */  lw    $s2, 0x40($sp)
/* 09B3B4 8009A7B4 8FB30044 */  lw    $s3, 0x44($sp)
/* 09B3B8 8009A7B8 8FB40048 */  lw    $s4, 0x48($sp)
/* 09B3BC 8009A7BC 8FB5004C */  lw    $s5, 0x4c($sp)
/* 09B3C0 8009A7C0 8FB60050 */  lw    $s6, 0x50($sp)
/* 09B3C4 8009A7C4 8FB70054 */  lw    $s7, 0x54($sp)
/* 09B3C8 8009A7C8 8FBE0058 */  lw    $fp, 0x58($sp)
/* 09B3CC 8009A7CC 03E00008 */  jr    $ra
/* 09B3D0 8009A7D0 27BD00F0 */   addiu $sp, $sp, 0xf0

