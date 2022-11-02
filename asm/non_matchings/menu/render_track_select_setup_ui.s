.late_rodata
glabel D_800E84F0
.float 1.2

.text
glabel render_track_select_setup_ui
/* 091B30 80090F30 27BDFF68 */  addiu $sp, $sp, -0x98
/* 091B34 80090F34 AFBF0054 */  sw    $ra, 0x54($sp)
/* 091B38 80090F38 AFBE0050 */  sw    $fp, 0x50($sp)
/* 091B3C 80090F3C AFB7004C */  sw    $s7, 0x4c($sp)
/* 091B40 80090F40 AFB60048 */  sw    $s6, 0x48($sp)
/* 091B44 80090F44 AFB50044 */  sw    $s5, 0x44($sp)
/* 091B48 80090F48 AFB40040 */  sw    $s4, 0x40($sp)
/* 091B4C 80090F4C AFB3003C */  sw    $s3, 0x3c($sp)
/* 091B50 80090F50 AFB20038 */  sw    $s2, 0x38($sp)
/* 091B54 80090F54 AFB10034 */  sw    $s1, 0x34($sp)
/* 091B58 80090F58 AFB00030 */  sw    $s0, 0x30($sp)
/* 091B5C 80090F5C AFA40098 */  sw    $a0, 0x98($sp)
/* 091B60 80090F60 AFA00080 */  sw    $zero, 0x80($sp)
/* 091B64 80090F64 AFA00078 */  sw    $zero, 0x78($sp)
/* 091B68 80090F68 0C01BAA4 */  jal   get_settings
/* 091B6C 80090F6C AFA00074 */   sw    $zero, 0x74($sp)
/* 091B70 80090F70 3C108000 */  lui   $s0, %hi(osTvType) # $s0, 0x8000
/* 091B74 80090F74 26100300 */  addiu $s0, %lo(osTvType) # addiu $s0, $s0, 0x300
/* 091B78 80090F78 8E0E0000 */  lw    $t6, ($s0)
/* 091B7C 80090F7C AFA20070 */  sw    $v0, 0x70($sp)
/* 091B80 80090F80 15C00003 */  bnez  $t6, .L80090F90
/* 091B84 80090F84 3C18800E */   lui   $t8, %hi(gNumberOfActivePlayers) # $t8, 0x800e
/* 091B88 80090F88 240F000C */  li    $t7, 12
/* 091B8C 80090F8C AFAF0080 */  sw    $t7, 0x80($sp)
.L80090F90:
/* 091B90 80090F90 8F18F4BC */  lw    $t8, %lo(gNumberOfActivePlayers)($t8)
/* 091B94 80090F94 24010002 */  li    $at, 2
/* 091B98 80090F98 1701000D */  bne   $t8, $at, .L80090FD0
/* 091B9C 80090F9C 00002025 */   move  $a0, $zero
/* 091BA0 80090FA0 3C198012 */  lui   $t9, %hi(D_801269C8) # $t9, 0x8012
/* 091BA4 80090FA4 8F3969C8 */  lw    $t9, %lo(D_801269C8)($t9)
/* 091BA8 80090FA8 3C088012 */  lui   $t0, %hi(D_801263E0) # $t0, 0x8012
/* 091BAC 80090FAC 2B210004 */  slti  $at, $t9, 4
/* 091BB0 80090FB0 10200007 */  beqz  $at, .L80090FD0
/* 091BB4 80090FB4 00000000 */   nop   
/* 091BB8 80090FB8 8D0863E0 */  lw    $t0, %lo(D_801263E0)($t0)
/* 091BBC 80090FBC 24090001 */  li    $t1, 1
/* 091BC0 80090FC0 29010002 */  slti  $at, $t0, 2
/* 091BC4 80090FC4 14200002 */  bnez  $at, .L80090FD0
/* 091BC8 80090FC8 00000000 */   nop   
/* 091BCC 80090FCC AFA90074 */  sw    $t1, 0x74($sp)
.L80090FD0:
/* 091BD0 80090FD0 0C019A25 */  jal   func_80066894
/* 091BD4 80090FD4 24050001 */   li    $a1, 1
/* 091BD8 80090FD8 0C026F57 */  jal   func_8009BD5C
/* 091BDC 80090FDC 00000000 */   nop   
/* 091BE0 80090FE0 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 091BE4 80090FE4 3C058012 */  lui   $a1, %hi(sMenuCurrHudMat) # $a1, 0x8012
/* 091BE8 80090FE8 24A563A8 */  addiu $a1, %lo(sMenuCurrHudMat) # addiu $a1, $a1, 0x63a8
/* 091BEC 80090FEC 0C019FCB */  jal   func_80067F2C
/* 091BF0 80090FF0 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 091BF4 80090FF4 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 091BF8 80090FF8 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 091BFC 80090FFC 3C03800E */  lui   $v1, %hi(gMenuImageStack) # $v1, 0x800e
/* 091C00 80091000 04410029 */  bgez  $v0, .L800910A8
/* 091C04 80091004 2463F75C */   addiu $v1, %lo(gMenuImageStack) # addiu $v1, $v1, -0x8a4
/* 091C08 80091008 3C028012 */  lui   $v0, %hi(gSelectedTrackX) # $v0, 0x8012
/* 091C0C 8009100C 8C4269F4 */  lw    $v0, %lo(gSelectedTrackX)($v0)
/* 091C10 80091010 24010004 */  li    $at, 4
/* 091C14 80091014 14410004 */  bne   $v0, $at, .L80091028
/* 091C18 80091018 24010005 */   li    $at, 5
/* 091C1C 8009101C 1000000A */  b     .L80091048
/* 091C20 80091020 24040006 */   li    $a0, 6
/* 091C24 80091024 24010005 */  li    $at, 5
.L80091028:
/* 091C28 80091028 14410005 */  bne   $v0, $at, .L80091040
/* 091C2C 8009102C 240B0004 */   li    $t3, 4
/* 091C30 80091030 240A0005 */  li    $t2, 5
/* 091C34 80091034 AFAA0084 */  sw    $t2, 0x84($sp)
/* 091C38 80091038 10000003 */  b     .L80091048
/* 091C3C 8009103C 24040005 */   li    $a0, 5
.L80091040:
/* 091C40 80091040 AFAB0084 */  sw    $t3, 0x84($sp)
/* 091C44 80091044 24040004 */  li    $a0, 4
.L80091048:
/* 091C48 80091048 8C6C0000 */  lw    $t4, ($v1)
/* 091C4C 8009104C 44800000 */  mtc1  $zero, $f0
/* 091C50 80091050 00041140 */  sll   $v0, $a0, 5
/* 091C54 80091054 01826821 */  addu  $t5, $t4, $v0
/* 091C58 80091058 E5A0000C */  swc1  $f0, 0xc($t5)
/* 091C5C 8009105C 8C6E0000 */  lw    $t6, ($v1)
/* 091C60 80091060 3C01800F */  lui   $at, %hi(D_800E84F0) # $at, 0x800f
/* 091C64 80091064 01C27821 */  addu  $t7, $t6, $v0
/* 091C68 80091068 E5E00010 */  swc1  $f0, 0x10($t7)
/* 091C6C 8009106C 8E180000 */  lw    $t8, ($s0)
/* 091C70 80091070 00000000 */  nop   
/* 091C74 80091074 17000004 */  bnez  $t8, .L80091088
/* 091C78 80091078 00000000 */   nop   
/* 091C7C 8009107C C42484F0 */  lwc1  $f4, %lo(D_800E84F0)($at)
/* 091C80 80091080 3C01800E */  lui   $at, %hi(D_800DF454) # $at, 0x800e
/* 091C84 80091084 E424F454 */  swc1  $f4, %lo(D_800DF454)($at)
.L80091088:
/* 091C88 80091088 0C027298 */  jal   func_8009CA60
/* 091C8C 8009108C 00000000 */   nop   
/* 091C90 80091090 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 091C94 80091094 44813000 */  mtc1  $at, $f6
/* 091C98 80091098 3C02800E */  lui   $v0, %hi(gMenuDelay) # $v0, 0x800e
/* 091C9C 8009109C 3C01800E */  lui   $at, %hi(D_800DF454) # $at, 0x800e
/* 091CA0 800910A0 8C42F47C */  lw    $v0, %lo(gMenuDelay)($v0)
/* 091CA4 800910A4 E426F454 */  swc1  $f6, %lo(D_800DF454)($at)
.L800910A8:
/* 091CA8 800910A8 2841FFEA */  slti  $at, $v0, -0x16
/* 091CAC 800910AC 1420042A */  bnez  $at, .L80092158
/* 091CB0 800910B0 2841001F */   slti  $at, $v0, 0x1f
/* 091CB4 800910B4 10200428 */  beqz  $at, .L80092158
/* 091CB8 800910B8 3C04800E */   lui   $a0, %hi(gTrackIdForPreview) # $a0, 0x800e
/* 091CBC 800910BC 04410006 */  bgez  $v0, .L800910D8
/* 091CC0 800910C0 3C1E800E */   lui   $fp, %hi(sMenuGuiOpacity) # $fp, 0x800e
/* 091CC4 800910C4 0002C900 */  sll   $t9, $v0, 4
/* 091CC8 800910C8 272800FF */  addiu $t0, $t9, 0xff
/* 091CCC 800910CC 27DEF764 */  addiu $fp, %lo(sMenuGuiOpacity) # addiu $fp, $fp, -0x89c
/* 091CD0 800910D0 10000005 */  b     .L800910E8
/* 091CD4 800910D4 AFC80000 */   sw    $t0, ($fp)
.L800910D8:
/* 091CD8 800910D8 3C1E800E */  lui   $fp, %hi(sMenuGuiOpacity) # $fp, 0x800e
/* 091CDC 800910DC 27DEF764 */  addiu $fp, %lo(sMenuGuiOpacity) # addiu $fp, $fp, -0x89c
/* 091CE0 800910E0 240900FF */  li    $t1, 255
/* 091CE4 800910E4 AFC90000 */  sw    $t1, ($fp)
.L800910E8:
/* 091CE8 800910E8 8FCA0000 */  lw    $t2, ($fp)
/* 091CEC 800910EC 00000000 */  nop   
/* 091CF0 800910F0 05410002 */  bgez  $t2, .L800910FC
/* 091CF4 800910F4 00000000 */   nop   
/* 091CF8 800910F8 AFC00000 */  sw    $zero, ($fp)
.L800910FC:
/* 091CFC 800910FC 8C84F4C4 */  lw    $a0, %lo(gTrackIdForPreview)($a0)
/* 091D00 80091100 0C01AC3E */  jal   func_8006B0F8
/* 091D04 80091104 00000000 */   nop   
/* 091D08 80091108 3C04800E */  lui   $a0, %hi(gTrackIdForPreview) # $a0, 0x800e
/* 091D0C 8009110C 8C84F4C4 */  lw    $a0, %lo(gTrackIdForPreview)($a0)
/* 091D10 80091110 0C01AF77 */  jal   get_level_name
/* 091D14 80091114 AFA2007C */   sw    $v0, 0x7c($sp)
/* 091D18 80091118 00408025 */  move  $s0, $v0
/* 091D1C 8009111C 0C0310BB */  jal   set_text_font
/* 091D20 80091120 24040002 */   li    $a0, 2
/* 091D24 80091124 8FCB0000 */  lw    $t3, ($fp)
/* 091D28 80091128 240400C0 */  li    $a0, 192
/* 091D2C 8009112C 240500C0 */  li    $a1, 192
/* 091D30 80091130 240600FF */  li    $a2, 255
/* 091D34 80091134 00003825 */  move  $a3, $zero
/* 091D38 80091138 0C0310E1 */  jal   set_text_colour
/* 091D3C 8009113C AFAB0010 */   sw    $t3, 0x10($sp)
/* 091D40 80091140 00002025 */  move  $a0, $zero
/* 091D44 80091144 00002825 */  move  $a1, $zero
/* 091D48 80091148 00003025 */  move  $a2, $zero
/* 091D4C 8009114C 0C0310F3 */  jal   set_text_background_colour
/* 091D50 80091150 00003825 */   move  $a3, $zero
/* 091D54 80091154 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 091D58 80091158 240C000C */  li    $t4, 12
/* 091D5C 8009115C AFAC0010 */  sw    $t4, 0x10($sp)
/* 091D60 80091160 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 091D64 80091164 24058000 */  li    $a1, -32768
/* 091D68 80091168 2406002B */  li    $a2, 43
/* 091D6C 8009116C 0C031110 */  jal   draw_text
/* 091D70 80091170 02003825 */   move  $a3, $s0
/* 091D74 80091174 3C068012 */  lui   $a2, %hi(gOptionBlinkTimer) # $a2, 0x8012
/* 091D78 80091178 8CC663BC */  lw    $a2, %lo(gOptionBlinkTimer)($a2)
/* 091D7C 8009117C 24040007 */  li    $a0, 7
/* 091D80 80091180 000668C0 */  sll   $t5, $a2, 3
/* 091D84 80091184 29A10100 */  slti  $at, $t5, 0x100
/* 091D88 80091188 14200003 */  bnez  $at, .L80091198
/* 091D8C 8009118C 01A03025 */   move  $a2, $t5
/* 091D90 80091190 240E01FF */  li    $t6, 511
/* 091D94 80091194 01CD3023 */  subu  $a2, $t6, $t5
.L80091198:
/* 091D98 80091198 8FCF0000 */  lw    $t7, ($fp)
/* 091D9C 8009119C 240500FF */  li    $a1, 255
/* 091DA0 800911A0 00003825 */  move  $a3, $zero
/* 091DA4 800911A4 AFA60084 */  sw    $a2, 0x84($sp)
/* 091DA8 800911A8 0C0313EF */  jal   set_current_dialogue_background_colour
/* 091DAC 800911AC AFAF0010 */   sw    $t7, 0x10($sp)
/* 091DB0 800911B0 3C028012 */  lui   $v0, %hi(D_801263E0) # $v0, 0x8012
/* 091DB4 800911B4 8C4263E0 */  lw    $v0, %lo(D_801263E0)($v0)
/* 091DB8 800911B8 2401FFFF */  li    $at, -1
/* 091DBC 800911BC 1041000A */  beq   $v0, $at, .L800911E8
/* 091DC0 800911C0 24010002 */   li    $at, 2
/* 091DC4 800911C4 14410073 */  bne   $v0, $at, .L80091394
/* 091DC8 800911C8 3C188012 */   lui   $t8, %hi(D_801269C8) # $t8, 0x8012
/* 091DCC 800911CC 8F1869C8 */  lw    $t8, %lo(D_801269C8)($t8)
/* 091DD0 800911D0 24010004 */  li    $at, 4
/* 091DD4 800911D4 1701006F */  bne   $t8, $at, .L80091394
/* 091DD8 800911D8 00000000 */   nop   
/* 091DDC 800911DC 0C027B18 */  jal   is_adventure_two_unlocked
/* 091DE0 800911E0 00000000 */   nop   
/* 091DE4 800911E4 1040006B */  beqz  $v0, .L80091394
.L800911E8:
/* 091DE8 800911E8 3C19800E */   lui   $t9, %hi(gMenuText) # $t9, 0x800e
/* 091DEC 800911EC 8F39F4A0 */  lw    $t9, %lo(gMenuText)($t9)
/* 091DF0 800911F0 00002825 */  move  $a1, $zero
/* 091DF4 800911F4 8F240248 */  lw    $a0, 0x248($t9)
/* 091DF8 800911F8 0C031368 */  jal   func_800C4DA0
/* 091DFC 800911FC 00003025 */   move  $a2, $zero
/* 091E00 80091200 3C08800E */  lui   $t0, %hi(gMenuText) # $t0, 0x800e
/* 091E04 80091204 8D08F4A0 */  lw    $t0, %lo(gMenuText)($t0)
/* 091E08 80091208 0040A025 */  move  $s4, $v0
/* 091E0C 8009120C 8D04024C */  lw    $a0, 0x24c($t0)
/* 091E10 80091210 00002825 */  move  $a1, $zero
/* 091E14 80091214 0C031368 */  jal   func_800C4DA0
/* 091E18 80091218 00003025 */   move  $a2, $zero
/* 091E1C 8009121C 0282082A */  slt   $at, $s4, $v0
/* 091E20 80091220 10200002 */  beqz  $at, .L8009122C
/* 091E24 80091224 3C10800E */   lui   $s0, %hi(D_800E0700) # $s0, 0x800e
/* 091E28 80091228 0040A025 */  move  $s4, $v0
.L8009122C:
/* 091E2C 8009122C 26100700 */  addiu $s0, %lo(D_800E0700) # addiu $s0, $s0, 0x700
/* 091E30 80091230 86020004 */  lh    $v0, 4($s0)
/* 091E34 80091234 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 091E38 80091238 0282082A */  slt   $at, $s4, $v0
/* 091E3C 8009123C 10200003 */  beqz  $at, .L8009124C
/* 091E40 80091240 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 091E44 80091244 10000002 */  b     .L80091250
/* 091E48 80091248 0040A025 */   move  $s4, $v0
.L8009124C:
/* 091E4C 8009124C 2694000C */  addiu $s4, $s4, 0xc
.L80091250:
/* 091E50 80091250 8FCE0000 */  lw    $t6, ($fp)
/* 091E54 80091254 3C01B0E0 */  lui   $at, (0xB0E0C000 >> 16) # lui $at, 0xb0e0
/* 091E58 80091258 3C188012 */  lui   $t8, %hi(D_80126550) # $t8, 0x8012
/* 091E5C 8009125C 8F18665C */  lw    $t8, %lo(D_80126550 + 0x10C)($t8)
/* 091E60 80091260 86090002 */  lh    $t1, 2($s0)
/* 091E64 80091264 860B0006 */  lh    $t3, 6($s0)
/* 091E68 80091268 860C0008 */  lh    $t4, 8($s0)
/* 091E6C 8009126C 860D000A */  lh    $t5, 0xa($s0)
/* 091E70 80091270 3421C000 */  ori   $at, (0xB0E0C000 & 0xFFFF) # ori $at, $at, 0xc000
/* 091E74 80091274 00142843 */  sra   $a1, $s4, 1
/* 091E78 80091278 240A0078 */  li    $t2, 120
/* 091E7C 8009127C 01C17821 */  addu  $t7, $t6, $at
/* 091E80 80091280 AFAF001C */  sw    $t7, 0x1c($sp)
/* 091E84 80091284 00052823 */  negu  $a1, $a1
/* 091E88 80091288 02803825 */  move  $a3, $s4
/* 091E8C 8009128C AFB80020 */  sw    $t8, 0x20($sp)
/* 091E90 80091290 01493023 */  subu  $a2, $t2, $t1
/* 091E94 80091294 AFAB0010 */  sw    $t3, 0x10($sp)
/* 091E98 80091298 AFAC0014 */  sw    $t4, 0x14($sp)
/* 091E9C 8009129C 0C020160 */  jal   func_80080580
/* 091EA0 800912A0 AFAD0018 */   sw    $t5, 0x18($sp)
/* 091EA4 800912A4 0C02039B */  jal   func_80080E6C
/* 091EA8 800912A8 00000000 */   nop   
/* 091EAC 800912AC 0C0310BB */  jal   set_text_font
/* 091EB0 800912B0 00002025 */   move  $a0, $zero
/* 091EB4 800912B4 8619000E */  lh    $t9, 0xe($s0)
/* 091EB8 800912B8 86080002 */  lh    $t0, 2($s0)
/* 091EBC 800912BC 8FA90080 */  lw    $t1, 0x80($sp)
/* 091EC0 800912C0 03285021 */  addu  $t2, $t9, $t0
/* 091EC4 800912C4 3C16800E */  lui   $s6, %hi(D_800E0418) # $s6, 0x800e
/* 091EC8 800912C8 0149B821 */  addu  $s7, $t2, $t1
/* 091ECC 800912CC 26F70001 */  addiu $s7, $s7, 1
/* 091ED0 800912D0 26D60418 */  addiu $s6, %lo(D_800E0418) # addiu $s6, $s6, 0x418
/* 091ED4 800912D4 0000A025 */  move  $s4, $zero
/* 091ED8 800912D8 00008825 */  move  $s1, $zero
/* 091EDC 800912DC 241200A1 */  li    $s2, 161
.L800912E0:
/* 091EE0 800912E0 00009825 */  move  $s3, $zero
/* 091EE4 800912E4 02E08025 */  move  $s0, $s7
.L800912E8:
/* 091EE8 800912E8 1660000B */  bnez  $s3, .L80091318
/* 091EEC 800912EC 240400FF */   li    $a0, 255
/* 091EF0 800912F0 8FCB0000 */  lw    $t3, ($fp)
/* 091EF4 800912F4 00002025 */  move  $a0, $zero
/* 091EF8 800912F8 000B6043 */  sra   $t4, $t3, 1
/* 091EFC 800912FC AFAC0010 */  sw    $t4, 0x10($sp)
/* 091F00 80091300 00002825 */  move  $a1, $zero
/* 091F04 80091304 00003025 */  move  $a2, $zero
/* 091F08 80091308 0C0310E1 */  jal   set_text_colour
/* 091F0C 8009130C 240700FF */   li    $a3, 255
/* 091F10 80091310 1000000C */  b     .L80091344
/* 091F14 80091314 00000000 */   nop   
.L80091318:
/* 091F18 80091318 8ECD0000 */  lw    $t5, ($s6)
/* 091F1C 8009131C 0000A825 */  move  $s5, $zero
/* 091F20 80091320 168D0003 */  bne   $s4, $t5, .L80091330
/* 091F24 80091324 240500FF */   li    $a1, 255
/* 091F28 80091328 8FB50084 */  lw    $s5, 0x84($sp)
/* 091F2C 8009132C 00000000 */  nop   
.L80091330:
/* 091F30 80091330 8FCE0000 */  lw    $t6, ($fp)
/* 091F34 80091334 240600FF */  li    $a2, 255
/* 091F38 80091338 02A03825 */  move  $a3, $s5
/* 091F3C 8009133C 0C0310E1 */  jal   set_text_colour
/* 091F40 80091340 AFAE0010 */   sw    $t6, 0x10($sp)
.L80091344:
/* 091F44 80091344 3C0F800E */  lui   $t7, %hi(gMenuText) # $t7, 0x800e
/* 091F48 80091348 8DEFF4A0 */  lw    $t7, %lo(gMenuText)($t7)
/* 091F4C 8009134C 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 091F50 80091350 01F1C021 */  addu  $t8, $t7, $s1
/* 091F54 80091354 8F070248 */  lw    $a3, 0x248($t8)
/* 091F58 80091358 2419000C */  li    $t9, 12
/* 091F5C 8009135C AFB90010 */  sw    $t9, 0x10($sp)
/* 091F60 80091360 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 091F64 80091364 02532823 */  subu  $a1, $s2, $s3
/* 091F68 80091368 0C031110 */  jal   draw_text
/* 091F6C 8009136C 02003025 */   move  $a2, $s0
/* 091F70 80091370 26730002 */  addiu $s3, $s3, 2
/* 091F74 80091374 24010004 */  li    $at, 4
/* 091F78 80091378 1661FFDB */  bne   $s3, $at, .L800912E8
/* 091F7C 8009137C 2610FFFE */   addiu $s0, $s0, -2
/* 091F80 80091380 26940001 */  addiu $s4, $s4, 1
/* 091F84 80091384 24010002 */  li    $at, 2
/* 091F88 80091388 26310004 */  addiu $s1, $s1, 4
/* 091F8C 8009138C 1681FFD4 */  bne   $s4, $at, .L800912E0
/* 091F90 80091390 26F70010 */   addiu $s7, $s7, 0x10
.L80091394:
/* 091F94 80091394 3C088012 */  lui   $t0, %hi(D_801269C8) # $t0, 0x8012
/* 091F98 80091398 8D0869C8 */  lw    $t0, %lo(D_801269C8)($t0)
/* 091F9C 8009139C 00000000 */  nop   
/* 091FA0 800913A0 29010004 */  slti  $at, $t0, 4
/* 091FA4 800913A4 102002D8 */  beqz  $at, .L80091F08
/* 091FA8 800913A8 00000000 */   nop   
/* 091FAC 800913AC 0C0310BB */  jal   set_text_font
/* 091FB0 800913B0 00002025 */   move  $a0, $zero
/* 091FB4 800913B4 8FCA0000 */  lw    $t2, ($fp)
/* 091FB8 800913B8 240400FF */  li    $a0, 255
/* 091FBC 800913BC 24050040 */  li    $a1, 64
/* 091FC0 800913C0 24060040 */  li    $a2, 64
/* 091FC4 800913C4 24070060 */  li    $a3, 96
/* 091FC8 800913C8 0C0310E1 */  jal   set_text_colour
/* 091FCC 800913CC AFAA0010 */   sw    $t2, 0x10($sp)
/* 091FD0 800913D0 3C09800E */  lui   $t1, %hi(gMenuText) # $t1, 0x800e
/* 091FD4 800913D4 8D29F4A0 */  lw    $t1, %lo(gMenuText)($t1)
/* 091FD8 800913D8 8FB00080 */  lw    $s0, 0x80($sp)
/* 091FDC 800913DC 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 091FE0 800913E0 240B0008 */  li    $t3, 8
/* 091FE4 800913E4 8D270024 */  lw    $a3, 0x24($t1)
/* 091FE8 800913E8 26100048 */  addiu $s0, $s0, 0x48
/* 091FEC 800913EC 02003025 */  move  $a2, $s0
/* 091FF0 800913F0 AFAB0010 */  sw    $t3, 0x10($sp)
/* 091FF4 800913F4 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 091FF8 800913F8 0C031110 */  jal   draw_text
/* 091FFC 800913FC 24050038 */   li    $a1, 56
/* 092000 80091400 3C0C800E */  lui   $t4, %hi(gMenuText) # $t4, 0x800e
/* 092004 80091404 8D8CF4A0 */  lw    $t4, %lo(gMenuText)($t4)
/* 092008 80091408 8FB20080 */  lw    $s2, 0x80($sp)
/* 09200C 8009140C 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 092010 80091410 240D0008 */  li    $t5, 8
/* 092014 80091414 8D870028 */  lw    $a3, 0x28($t4)
/* 092018 80091418 2652005C */  addiu $s2, $s2, 0x5c
/* 09201C 8009141C 02403025 */  move  $a2, $s2
/* 092020 80091420 AFAD0010 */  sw    $t5, 0x10($sp)
/* 092024 80091424 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 092028 80091428 0C031110 */  jal   draw_text
/* 09202C 8009142C 24050038 */   li    $a1, 56
/* 092030 80091430 8FCE0000 */  lw    $t6, ($fp)
/* 092034 80091434 240400FF */  li    $a0, 255
/* 092038 80091438 24050080 */  li    $a1, 128
/* 09203C 8009143C 240600FF */  li    $a2, 255
/* 092040 80091440 24070060 */  li    $a3, 96
/* 092044 80091444 0C0310E1 */  jal   set_text_colour
/* 092048 80091448 AFAE0010 */   sw    $t6, 0x10($sp)
/* 09204C 8009144C 3C188012 */  lui   $t8, %hi(gPlayerSelectVehicle) # $t8, 0x8012
/* 092050 80091450 831869C0 */  lb    $t8, %lo(gPlayerSelectVehicle)($t8)
/* 092054 80091454 8FAF0070 */  lw    $t7, 0x70($sp)
/* 092058 80091458 3C09800E */  lui   $t1, %hi(gTrackIdForPreview) # $t1, 0x800e
/* 09205C 8009145C 0018C880 */  sll   $t9, $t8, 2
/* 092060 80091460 8D29F4C4 */  lw    $t1, %lo(gTrackIdForPreview)($t1)
/* 092064 80091464 01F94021 */  addu  $t0, $t7, $t9
/* 092068 80091468 8D0A0030 */  lw    $t2, 0x30($t0)
/* 09206C 8009146C 00095840 */  sll   $t3, $t1, 1
/* 092070 80091470 014B6021 */  addu  $t4, $t2, $t3
/* 092074 80091474 27B10078 */  addiu $s1, $sp, 0x78
/* 092078 80091478 95840000 */  lhu   $a0, ($t4)
/* 09207C 8009147C 02202825 */  move  $a1, $s1
/* 092080 80091480 0C025DBE */  jal   decompress_filename_string
/* 092084 80091484 24060003 */   li    $a2, 3
/* 092088 80091488 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 09208C 8009148C 240D000C */  li    $t5, 12
/* 092090 80091490 AFAD0010 */  sw    $t5, 0x10($sp)
/* 092094 80091494 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 092098 80091498 240500FA */  li    $a1, 250
/* 09209C 8009149C 02003025 */  move  $a2, $s0
/* 0920A0 800914A0 0C031110 */  jal   draw_text
/* 0920A4 800914A4 02203825 */   move  $a3, $s1
/* 0920A8 800914A8 3C188012 */  lui   $t8, %hi(gPlayerSelectVehicle) # $t8, 0x8012
/* 0920AC 800914AC 831869C0 */  lb    $t8, %lo(gPlayerSelectVehicle)($t8)
/* 0920B0 800914B0 8FAE0070 */  lw    $t6, 0x70($sp)
/* 0920B4 800914B4 3C09800E */  lui   $t1, %hi(gTrackIdForPreview) # $t1, 0x800e
/* 0920B8 800914B8 00187880 */  sll   $t7, $t8, 2
/* 0920BC 800914BC 8D29F4C4 */  lw    $t1, %lo(gTrackIdForPreview)($t1)
/* 0920C0 800914C0 01CFC821 */  addu  $t9, $t6, $t7
/* 0920C4 800914C4 8F280018 */  lw    $t0, 0x18($t9)
/* 0920C8 800914C8 00095040 */  sll   $t2, $t1, 1
/* 0920CC 800914CC 010A5821 */  addu  $t3, $t0, $t2
/* 0920D0 800914D0 95640000 */  lhu   $a0, ($t3)
/* 0920D4 800914D4 02202825 */  move  $a1, $s1
/* 0920D8 800914D8 0C025DBE */  jal   decompress_filename_string
/* 0920DC 800914DC 24060003 */   li    $a2, 3
/* 0920E0 800914E0 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0920E4 800914E4 240C000C */  li    $t4, 12
/* 0920E8 800914E8 AFAC0010 */  sw    $t4, 0x10($sp)
/* 0920EC 800914EC 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0920F0 800914F0 240500FA */  li    $a1, 250
/* 0920F4 800914F4 02403025 */  move  $a2, $s2
/* 0920F8 800914F8 0C031110 */  jal   draw_text
/* 0920FC 800914FC 02203825 */   move  $a3, $s1
/* 092100 80091500 3C188012 */  lui   $t8, %hi(gPlayerSelectVehicle) # $t8, 0x8012
/* 092104 80091504 831869C0 */  lb    $t8, %lo(gPlayerSelectVehicle)($t8)
/* 092108 80091508 8FAD0070 */  lw    $t5, 0x70($sp)
/* 09210C 8009150C 3C09800E */  lui   $t1, %hi(gTrackIdForPreview) # $t1, 0x800e
/* 092110 80091510 00187080 */  sll   $t6, $t8, 2
/* 092114 80091514 8D29F4C4 */  lw    $t1, %lo(gTrackIdForPreview)($t1)
/* 092118 80091518 01AE7821 */  addu  $t7, $t5, $t6
/* 09211C 8009151C 8DF9003C */  lw    $t9, 0x3c($t7)
/* 092120 80091520 00094040 */  sll   $t0, $t1, 1
/* 092124 80091524 03285021 */  addu  $t2, $t9, $t0
/* 092128 80091528 95440000 */  lhu   $a0, ($t2)
/* 09212C 8009152C 240B00FF */  li    $t3, 255
/* 092130 80091530 240C00FF */  li    $t4, 255
/* 092134 80091534 AFAC0014 */  sw    $t4, 0x14($sp)
/* 092138 80091538 AFAB0010 */  sw    $t3, 0x10($sp)
/* 09213C 8009153C AFA00018 */  sw    $zero, 0x18($sp)
/* 092140 80091540 24050016 */  li    $a1, 22
/* 092144 80091544 24060035 */  li    $a2, 53
/* 092148 80091548 0C020600 */  jal   show_timestamp
/* 09214C 8009154C 24070080 */   li    $a3, 128
/* 092150 80091550 3C0D8012 */  lui   $t5, %hi(gPlayerSelectVehicle) # $t5, 0x8012
/* 092154 80091554 81AD69C0 */  lb    $t5, %lo(gPlayerSelectVehicle)($t5)
/* 092158 80091558 8FB80070 */  lw    $t8, 0x70($sp)
/* 09215C 8009155C 3C19800E */  lui   $t9, %hi(gTrackIdForPreview) # $t9, 0x800e
/* 092160 80091560 000D7080 */  sll   $t6, $t5, 2
/* 092164 80091564 8F39F4C4 */  lw    $t9, %lo(gTrackIdForPreview)($t9)
/* 092168 80091568 030E7821 */  addu  $t7, $t8, $t6
/* 09216C 8009156C 8DE90024 */  lw    $t1, 0x24($t7)
/* 092170 80091570 00194040 */  sll   $t0, $t9, 1
/* 092174 80091574 01285021 */  addu  $t2, $t1, $t0
/* 092178 80091578 95440000 */  lhu   $a0, ($t2)
/* 09217C 8009157C 240B00C0 */  li    $t3, 192
/* 092180 80091580 240C00FF */  li    $t4, 255
/* 092184 80091584 AFAC0014 */  sw    $t4, 0x14($sp)
/* 092188 80091588 AFAB0010 */  sw    $t3, 0x10($sp)
/* 09218C 8009158C AFA00018 */  sw    $zero, 0x18($sp)
/* 092190 80091590 24050016 */  li    $a1, 22
/* 092194 80091594 24060021 */  li    $a2, 33
/* 092198 80091598 0C020600 */  jal   show_timestamp
/* 09219C 8009159C 240700FF */   li    $a3, 255
/* 0921A0 800915A0 3C0D8012 */  lui   $t5, %hi(D_801263E0) # $t5, 0x8012
/* 0921A4 800915A4 8DAD63E0 */  lw    $t5, %lo(D_801263E0)($t5)
/* 0921A8 800915A8 2401FFFF */  li    $at, -1
/* 0921AC 800915AC 11A10256 */  beq   $t5, $at, .L80091F08
/* 0921B0 800915B0 3C02800E */   lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 0921B4 800915B4 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 0921B8 800915B8 24010001 */  li    $at, 1
/* 0921BC 800915BC 14410062 */  bne   $v0, $at, .L80091748
/* 0921C0 800915C0 24040007 */   li    $a0, 7
/* 0921C4 800915C4 8FB80080 */  lw    $t8, 0x80($sp)
/* 0921C8 800915C8 24050086 */  li    $a1, 134
/* 0921CC 800915CC 270E0089 */  addiu $t6, $t8, 0x89
/* 0921D0 800915D0 AFAE0010 */  sw    $t6, 0x10($sp)
/* 0921D4 800915D4 240700BA */  li    $a3, 186
/* 0921D8 800915D8 0C0313B7 */  jal   set_current_dialogue_box_coords
/* 0921DC 800915DC 27060070 */   addiu $a2, $t8, 0x70
/* 0921E0 800915E0 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0921E4 800915E4 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0921E8 800915E8 00002825 */  move  $a1, $zero
/* 0921EC 800915EC 00003025 */  move  $a2, $zero
/* 0921F0 800915F0 0C0316D6 */  jal   render_dialogue_box
/* 0921F4 800915F4 24070007 */   li    $a3, 7
/* 0921F8 800915F8 3C0F8012 */  lui   $t7, %hi(D_801263E0) # $t7, 0x8012
/* 0921FC 800915FC 8DEF63E0 */  lw    $t7, %lo(D_801263E0)($t7)
/* 092200 80091600 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 092204 80091604 1DE00013 */  bgtz  $t7, .L80091654
/* 092208 80091608 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 09220C 8009160C 8FA70080 */  lw    $a3, 0x80($sp)
/* 092210 80091610 8FCA0000 */  lw    $t2, ($fp)
/* 092214 80091614 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 092218 80091618 3C05800E */  lui   $a1, %hi(gRaceSelectionVehicleTitleTexture) # $a1, 0x800e
/* 09221C 8009161C 241900FF */  li    $t9, 255
/* 092220 80091620 240900FF */  li    $t1, 255
/* 092224 80091624 240800FF */  li    $t0, 255
/* 092228 80091628 AFA80018 */  sw    $t0, 0x18($sp)
/* 09222C 8009162C AFA90014 */  sw    $t1, 0x14($sp)
/* 092230 80091630 AFB90010 */  sw    $t9, 0x10($sp)
/* 092234 80091634 24A505B4 */  addiu $a1, %lo(gRaceSelectionVehicleTitleTexture) # addiu $a1, $a1, 0x5b4
/* 092238 80091638 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 09223C 8009163C 24060088 */  li    $a2, 136
/* 092240 80091640 24E70072 */  addiu $a3, $a3, 0x72
/* 092244 80091644 0C01E2AE */  jal   render_textured_rectangle
/* 092248 80091648 AFAA001C */   sw    $t2, 0x1c($sp)
/* 09224C 8009164C 1000003A */  b     .L80091738
/* 092250 80091650 00000000 */   nop   
.L80091654:
/* 092254 80091654 8FA70080 */  lw    $a3, 0x80($sp)
/* 092258 80091658 8FD80000 */  lw    $t8, ($fp)
/* 09225C 8009165C 3C05800E */  lui   $a1, %hi(gRaceSelectionTTTitleTexture) # $a1, 0x800e
/* 092260 80091660 240B00FF */  li    $t3, 255
/* 092264 80091664 240C00FF */  li    $t4, 255
/* 092268 80091668 240D00FF */  li    $t5, 255
/* 09226C 8009166C AFAD0018 */  sw    $t5, 0x18($sp)
/* 092270 80091670 AFAC0014 */  sw    $t4, 0x14($sp)
/* 092274 80091674 AFAB0010 */  sw    $t3, 0x10($sp)
/* 092278 80091678 24A505C4 */  addiu $a1, %lo(gRaceSelectionTTTitleTexture) # addiu $a1, $a1, 0x5c4
/* 09227C 8009167C 24060088 */  li    $a2, 136
/* 092280 80091680 0000A825 */  move  $s5, $zero
/* 092284 80091684 24E70072 */  addiu $a3, $a3, 0x72
/* 092288 80091688 0C01E2AE */  jal   render_textured_rectangle
/* 09228C 8009168C AFB8001C */   sw    $t8, 0x1c($sp)
/* 092290 80091690 8FB70080 */  lw    $s7, 0x80($sp)
/* 092294 80091694 3C10800E */  lui   $s0, %hi(D_800E0648) # $s0, 0x800e
/* 092298 80091698 26100648 */  addiu $s0, %lo(D_800E0648) # addiu $s0, $s0, 0x648
/* 09229C 8009169C 26F70097 */  addiu $s7, $s7, 0x97
.L800916A0:
/* 0922A0 800916A0 3C0E800E */  lui   $t6, %hi(D_800E0414) # $t6, 0x800e
/* 0922A4 800916A4 8DCE0414 */  lw    $t6, %lo(D_800E0414)($t6)
/* 0922A8 800916A8 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0922AC 800916AC 16AE0011 */  bne   $s5, $t6, .L800916F4
/* 0922B0 800916B0 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0922B4 800916B4 8FC80000 */  lw    $t0, ($fp)
/* 0922B8 800916B8 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0922BC 800916BC 8E050004 */  lw    $a1, 4($s0)
/* 0922C0 800916C0 240F00FF */  li    $t7, 255
/* 0922C4 800916C4 241900FF */  li    $t9, 255
/* 0922C8 800916C8 240900FF */  li    $t1, 255
/* 0922CC 800916CC AFA90018 */  sw    $t1, 0x18($sp)
/* 0922D0 800916D0 AFB90014 */  sw    $t9, 0x14($sp)
/* 0922D4 800916D4 AFAF0010 */  sw    $t7, 0x10($sp)
/* 0922D8 800916D8 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0922DC 800916DC 24060068 */  li    $a2, 104
/* 0922E0 800916E0 02E03825 */  move  $a3, $s7
/* 0922E4 800916E4 0C01E2AE */  jal   render_textured_rectangle
/* 0922E8 800916E8 AFA8001C */   sw    $t0, 0x1c($sp)
/* 0922EC 800916EC 1000000E */  b     .L80091728
/* 0922F0 800916F0 26B50001 */   addiu $s5, $s5, 1
.L800916F4:
/* 0922F4 800916F4 8FCD0000 */  lw    $t5, ($fp)
/* 0922F8 800916F8 8E050008 */  lw    $a1, 8($s0)
/* 0922FC 800916FC 240A00FF */  li    $t2, 255
/* 092300 80091700 240B00FF */  li    $t3, 255
/* 092304 80091704 240C00FF */  li    $t4, 255
/* 092308 80091708 AFAC0018 */  sw    $t4, 0x18($sp)
/* 09230C 8009170C AFAB0014 */  sw    $t3, 0x14($sp)
/* 092310 80091710 AFAA0010 */  sw    $t2, 0x10($sp)
/* 092314 80091714 24060068 */  li    $a2, 104
/* 092318 80091718 02E03825 */  move  $a3, $s7
/* 09231C 8009171C 0C01E2AE */  jal   render_textured_rectangle
/* 092320 80091720 AFAD001C */   sw    $t5, 0x1c($sp)
/* 092324 80091724 26B50001 */  addiu $s5, $s5, 1
.L80091728:
/* 092328 80091728 24010002 */  li    $at, 2
/* 09232C 8009172C 2610000C */  addiu $s0, $s0, 0xc
/* 092330 80091730 16A1FFDB */  bne   $s5, $at, .L800916A0
/* 092334 80091734 26F70018 */   addiu $s7, $s7, 0x18
.L80091738:
/* 092338 80091738 3C02800E */  lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 09233C 8009173C 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 092340 80091740 1000004B */  b     .L80091870
/* 092344 80091744 28410002 */   slti  $at, $v0, 2
.L80091748:
/* 092348 80091748 8FB80074 */  lw    $t8, 0x74($sp)
/* 09234C 8009174C 244EFFFF */  addiu $t6, $v0, -1
/* 092350 80091750 17000047 */  bnez  $t8, .L80091870
/* 092354 80091754 28410002 */   slti  $at, $v0, 2
/* 092358 80091758 01C20019 */  multu $t6, $v0
/* 09235C 8009175C 3C19800E */  lui   $t9, %hi(D_800E0688) # $t9, 0x800e
/* 092360 80091760 27390688 */  addiu $t9, %lo(D_800E0688) # addiu $t9, $t9, 0x688
/* 092364 80091764 3C11800E */  lui   $s1, %hi(D_800E0660) # $s1, 0x800e
/* 092368 80091768 3C128012 */  lui   $s2, %hi(D_801269C4) # $s2, 0x8012
/* 09236C 8009176C 0040B825 */  move  $s7, $v0
/* 092370 80091770 265269C4 */  addiu $s2, %lo(D_801269C4) # addiu $s2, $s2, 0x69c4
/* 092374 80091774 26310660 */  addiu $s1, %lo(D_800E0660) # addiu $s1, $s1, 0x660
/* 092378 80091778 0000A825 */  move  $s5, $zero
/* 09237C 8009177C 00009812 */  mflo  $s3
/* 092380 80091780 00137840 */  sll   $t7, $s3, 1
/* 092384 80091784 18400039 */  blez  $v0, .L8009186C
/* 092388 80091788 01F98021 */   addu  $s0, $t7, $t9
.L8009178C:
/* 09238C 8009178C 3C02800E */  lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 092390 80091790 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 092394 80091794 24010001 */  li    $at, 1
/* 092398 80091798 14410004 */  bne   $v0, $at, .L800917AC
/* 09239C 8009179C 3C098012 */   lui   $t1, %hi(D_801263E0) # $t1, 0x8012
/* 0923A0 800917A0 8D2963E0 */  lw    $t1, %lo(D_801263E0)($t1)
/* 0923A4 800917A4 00000000 */  nop   
/* 0923A8 800917A8 12A90007 */  beq   $s5, $t1, .L800917C8
.L800917AC:
/* 0923AC 800917AC 28410002 */   slti  $at, $v0, 2
/* 0923B0 800917B0 14200016 */  bnez  $at, .L8009180C
/* 0923B4 800917B4 02554021 */   addu  $t0, $s2, $s5
/* 0923B8 800917B8 810A0000 */  lb    $t2, ($t0)
/* 0923BC 800917BC 00000000 */  nop   
/* 0923C0 800917C0 15400012 */  bnez  $t2, .L8009180C
/* 0923C4 800917C4 00000000 */   nop   
.L800917C8:
/* 0923C8 800917C8 860B0002 */  lh    $t3, 2($s0)
/* 0923CC 800917CC 8FAC0080 */  lw    $t4, 0x80($sp)
/* 0923D0 800917D0 86020000 */  lh    $v0, ($s0)
/* 0923D4 800917D4 016C1821 */  addu  $v1, $t3, $t4
/* 0923D8 800917D8 246D0017 */  addiu $t5, $v1, 0x17
/* 0923DC 800917DC AFAD0010 */  sw    $t5, 0x10($sp)
/* 0923E0 800917E0 2466FFFE */  addiu $a2, $v1, -2
/* 0923E4 800917E4 24040007 */  li    $a0, 7
/* 0923E8 800917E8 2445FFFE */  addiu $a1, $v0, -2
/* 0923EC 800917EC 0C0313B7 */  jal   set_current_dialogue_box_coords
/* 0923F0 800917F0 24470032 */   addiu $a3, $v0, 0x32
/* 0923F4 800917F4 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0923F8 800917F8 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0923FC 800917FC 00002825 */  move  $a1, $zero
/* 092400 80091800 00003025 */  move  $a2, $zero
/* 092404 80091804 0C0316D6 */  jal   render_dialogue_box
/* 092408 80091808 24070007 */   li    $a3, 7
.L8009180C:
/* 09240C 8009180C 86180002 */  lh    $t8, 2($s0)
/* 092410 80091810 8FAE0080 */  lw    $t6, 0x80($sp)
/* 092414 80091814 8FC80000 */  lw    $t0, ($fp)
/* 092418 80091818 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 09241C 8009181C 8E250000 */  lw    $a1, ($s1)
/* 092420 80091820 86060000 */  lh    $a2, ($s0)
/* 092424 80091824 240F00FF */  li    $t7, 255
/* 092428 80091828 241900FF */  li    $t9, 255
/* 09242C 8009182C 240900FF */  li    $t1, 255
/* 092430 80091830 AFA90018 */  sw    $t1, 0x18($sp)
/* 092434 80091834 AFB90014 */  sw    $t9, 0x14($sp)
/* 092438 80091838 AFAF0010 */  sw    $t7, 0x10($sp)
/* 09243C 8009183C 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 092440 80091840 030E3821 */  addu  $a3, $t8, $t6
/* 092444 80091844 0C01E2AE */  jal   render_textured_rectangle
/* 092448 80091848 AFA8001C */   sw    $t0, 0x1c($sp)
/* 09244C 8009184C 26B50001 */  addiu $s5, $s5, 1
/* 092450 80091850 02B7082A */  slt   $at, $s5, $s7
/* 092454 80091854 26310004 */  addiu $s1, $s1, 4
/* 092458 80091858 1420FFCC */  bnez  $at, .L8009178C
/* 09245C 8009185C 26100004 */   addiu $s0, $s0, 4
/* 092460 80091860 3C02800E */  lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 092464 80091864 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 092468 80091868 00000000 */  nop   
.L8009186C:
/* 09246C 8009186C 28410002 */  slti  $at, $v0, 2
.L80091870:
/* 092470 80091870 10200005 */  beqz  $at, .L80091888
/* 092474 80091874 3C0A8012 */   lui   $t2, %hi(D_801263E0) # $t2, 0x8012
/* 092478 80091878 8D4A63E0 */  lw    $t2, %lo(D_801263E0)($t2)
/* 09247C 8009187C 00000000 */  nop   
/* 092480 80091880 1540006A */  bnez  $t2, .L80091A2C
/* 092484 80091884 8FB00080 */   lw    $s0, 0x80($sp)
.L80091888:
/* 092488 80091888 8FAB0074 */  lw    $t3, 0x74($sp)
/* 09248C 8009188C 244CFFFF */  addiu $t4, $v0, -1
/* 092490 80091890 15600066 */  bnez  $t3, .L80091A2C
/* 092494 80091894 8FB00080 */   lw    $s0, 0x80($sp)
/* 092498 80091898 01820019 */  multu $t4, $v0
/* 09249C 8009189C 8FB70080 */  lw    $s7, 0x80($sp)
/* 0924A0 800918A0 0000A825 */  move  $s5, $zero
/* 0924A4 800918A4 24160003 */  li    $s6, 3
/* 0924A8 800918A8 26F7008B */  addiu $s7, $s7, 0x8b
/* 0924AC 800918AC 00009812 */  mflo  $s3
/* 0924B0 800918B0 00136843 */  sra   $t5, $s3, 1
/* 0924B4 800918B4 01A09825 */  move  $s3, $t5
/* 0924B8 800918B8 8FAF007C */  lw    $t7, 0x7c($sp)
.L800918BC:
/* 0924BC 800918BC 24180001 */  li    $t8, 1
/* 0924C0 800918C0 02B87004 */  sllv  $t6, $t8, $s5
/* 0924C4 800918C4 01CFC824 */  and   $t9, $t6, $t7
/* 0924C8 800918C8 13200054 */  beqz  $t9, .L80091A1C
/* 0924CC 800918CC 00000000 */   nop   
/* 0924D0 800918D0 18400051 */  blez  $v0, .L80091A18
/* 0924D4 800918D4 0000A025 */   move  $s4, $zero
/* 0924D8 800918D8 00154880 */  sll   $t1, $s5, 2
/* 0924DC 800918DC 01354823 */  subu  $t1, $t1, $s5
/* 0924E0 800918E0 3C0A800E */  lui   $t2, %hi(gRaceSelectionImages) # $t2, 0x800e
/* 0924E4 800918E4 3C0C800E */  lui   $t4, %hi(D_800E06B0) # $t4, 0x800e
/* 0924E8 800918E8 258C06B0 */  addiu $t4, %lo(D_800E06B0) # addiu $t4, $t4, 0x6b0
/* 0924EC 800918EC 254A0624 */  addiu $t2, %lo(gRaceSelectionImages) # addiu $t2, $t2, 0x624
/* 0924F0 800918F0 00094080 */  sll   $t0, $t1, 2
/* 0924F4 800918F4 3C118012 */  lui   $s1, %hi(gPlayerSelectVehicle) # $s1, 0x8012
/* 0924F8 800918F8 00135840 */  sll   $t3, $s3, 1
/* 0924FC 800918FC 016C8021 */  addu  $s0, $t3, $t4
/* 092500 80091900 263169C0 */  addiu $s1, %lo(gPlayerSelectVehicle) # addiu $s1, $s1, 0x69c0
/* 092504 80091904 010A9021 */  addu  $s2, $t0, $t2
.L80091908:
/* 092508 80091908 822D0000 */  lb    $t5, ($s1)
/* 09250C 8009190C 8FA90070 */  lw    $t1, 0x70($sp)
/* 092510 80091910 16AD0011 */  bne   $s5, $t5, .L80091958
/* 092514 80091914 3C0A800E */   lui   $t2, %hi(gTrackIdForPreview) # $t2, 0x800e
/* 092518 80091918 8FD90000 */  lw    $t9, ($fp)
/* 09251C 8009191C 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 092520 80091920 8E450004 */  lw    $a1, 4($s2)
/* 092524 80091924 86060000 */  lh    $a2, ($s0)
/* 092528 80091928 241800FF */  li    $t8, 255
/* 09252C 8009192C 240E00FF */  li    $t6, 255
/* 092530 80091930 240F00FF */  li    $t7, 255
/* 092534 80091934 AFAF0018 */  sw    $t7, 0x18($sp)
/* 092538 80091938 AFAE0014 */  sw    $t6, 0x14($sp)
/* 09253C 8009193C AFB80010 */  sw    $t8, 0x10($sp)
/* 092540 80091940 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 092544 80091944 02E03825 */  move  $a3, $s7
/* 092548 80091948 0C01E2AE */  jal   render_textured_rectangle
/* 09254C 8009194C AFB9001C */   sw    $t9, 0x1c($sp)
/* 092550 80091950 1000002A */  b     .L800919FC
/* 092554 80091954 00000000 */   nop   
.L80091958:
/* 092558 80091958 8D4AF4C4 */  lw    $t2, %lo(gTrackIdForPreview)($t2)
/* 09255C 8009195C 8D280004 */  lw    $t0, 4($t1)
/* 092560 80091960 000A5880 */  sll   $t3, $t2, 2
/* 092564 80091964 010B6021 */  addu  $t4, $t0, $t3
/* 092568 80091968 8D8D0000 */  lw    $t5, ($t4)
/* 09256C 8009196C 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 092570 80091970 31B80002 */  andi  $t8, $t5, 2
/* 092574 80091974 13000011 */  beqz  $t8, .L800919BC
/* 092578 80091978 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 09257C 8009197C 8FC90000 */  lw    $t1, ($fp)
/* 092580 80091980 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 092584 80091984 8E450008 */  lw    $a1, 8($s2)
/* 092588 80091988 86060000 */  lh    $a2, ($s0)
/* 09258C 8009198C 240E00FF */  li    $t6, 255
/* 092590 80091990 240F00FF */  li    $t7, 255
/* 092594 80091994 241900FF */  li    $t9, 255
/* 092598 80091998 AFB90018 */  sw    $t9, 0x18($sp)
/* 09259C 8009199C AFAF0014 */  sw    $t7, 0x14($sp)
/* 0925A0 800919A0 AFAE0010 */  sw    $t6, 0x10($sp)
/* 0925A4 800919A4 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0925A8 800919A8 02E03825 */  move  $a3, $s7
/* 0925AC 800919AC 0C01E2AE */  jal   render_textured_rectangle
/* 0925B0 800919B0 AFA9001C */   sw    $t1, 0x1c($sp)
/* 0925B4 800919B4 10000011 */  b     .L800919FC
/* 0925B8 800919B8 00000000 */   nop   
.L800919BC:
/* 0925BC 800919BC 8FCC0000 */  lw    $t4, ($fp)
/* 0925C0 800919C0 8E450008 */  lw    $a1, 8($s2)
/* 0925C4 800919C4 86060000 */  lh    $a2, ($s0)
/* 0925C8 800919C8 240A00FF */  li    $t2, 255
/* 0925CC 800919CC 240800FF */  li    $t0, 255
/* 0925D0 800919D0 240B00FF */  li    $t3, 255
/* 0925D4 800919D4 AFAB0018 */  sw    $t3, 0x18($sp)
/* 0925D8 800919D8 AFA80014 */  sw    $t0, 0x14($sp)
/* 0925DC 800919DC AFAA0010 */  sw    $t2, 0x10($sp)
/* 0925E0 800919E0 02E03825 */  move  $a3, $s7
/* 0925E4 800919E4 05810003 */  bgez  $t4, .L800919F4
/* 0925E8 800919E8 000C6843 */   sra   $t5, $t4, 1
/* 0925EC 800919EC 25810001 */  addiu $at, $t4, 1
/* 0925F0 800919F0 00016843 */  sra   $t5, $at, 1
.L800919F4:
/* 0925F4 800919F4 0C01E2AE */  jal   render_textured_rectangle
/* 0925F8 800919F8 AFAD001C */   sw    $t5, 0x1c($sp)
.L800919FC:
/* 0925FC 800919FC 3C02800E */  lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 092600 80091A00 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 092604 80091A04 26940001 */  addiu $s4, $s4, 1
/* 092608 80091A08 0282082A */  slt   $at, $s4, $v0
/* 09260C 80091A0C 26310001 */  addiu $s1, $s1, 1
/* 092610 80091A10 1420FFBD */  bnez  $at, .L80091908
/* 092614 80091A14 26100002 */   addiu $s0, $s0, 2
.L80091A18:
/* 092618 80091A18 26F70018 */  addiu $s7, $s7, 0x18
.L80091A1C:
/* 09261C 80091A1C 26B50001 */  addiu $s5, $s5, 1
/* 092620 80091A20 16B6FFA6 */  bne   $s5, $s6, .L800918BC
/* 092624 80091A24 8FAF007C */   lw    $t7, 0x7c($sp)
/* 092628 80091A28 8FB00080 */  lw    $s0, 0x80($sp)
.L80091A2C:
/* 09262C 80091A2C 3C038012 */  lui   $v1, %hi(gPlayerSelectVehicle) # $v1, 0x8012
/* 092630 80091A30 806369C0 */  lb    $v1, %lo(gPlayerSelectVehicle)($v1)
/* 092634 80091A34 24010002 */  li    $at, 2
/* 092638 80091A38 2610008B */  addiu $s0, $s0, 0x8b
/* 09263C 80091A3C 24160003 */  li    $s6, 3
/* 092640 80091A40 14610002 */  bne   $v1, $at, .L80091A4C
/* 092644 80091A44 0200B825 */   move  $s7, $s0
/* 092648 80091A48 26170002 */  addiu $s7, $s0, 2
.L80091A4C:
/* 09264C 80091A4C 24010001 */  li    $at, 1
/* 092650 80091A50 14410035 */  bne   $v0, $at, .L80091B28
/* 092654 80091A54 3C188012 */   lui   $t8, %hi(D_801263E0) # $t8, 0x8012
/* 092658 80091A58 8F1863E0 */  lw    $t8, %lo(D_801263E0)($t8)
/* 09265C 80091A5C 00000000 */  nop   
/* 092660 80091A60 17000019 */  bnez  $t8, .L80091AC8
/* 092664 80091A64 00000000 */   nop   
/* 092668 80091A68 00760019 */  multu $v1, $s6
/* 09266C 80091A6C 3C11800E */  lui   $s1, %hi(gRaceSelectionImages) # $s1, 0x800e
/* 092670 80091A70 26310624 */  addiu $s1, %lo(gRaceSelectionImages) # addiu $s1, $s1, 0x624
/* 092674 80091A74 8FCB0000 */  lw    $t3, ($fp)
/* 092678 80091A78 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 09267C 80091A7C 240900FF */  li    $t1, 255
/* 092680 80091A80 240A00FF */  li    $t2, 255
/* 092684 80091A84 240800FF */  li    $t0, 255
/* 092688 80091A88 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 09268C 80091A8C 24060095 */  li    $a2, 149
/* 092690 80091A90 02E03825 */  move  $a3, $s7
/* 092694 80091A94 00007012 */  mflo  $t6
/* 092698 80091A98 000E7880 */  sll   $t7, $t6, 2
/* 09269C 80091A9C 022FC821 */  addu  $t9, $s1, $t7
/* 0926A0 80091AA0 8F250000 */  lw    $a1, ($t9)
/* 0926A4 80091AA4 AFA80018 */  sw    $t0, 0x18($sp)
/* 0926A8 80091AA8 AFAA0014 */  sw    $t2, 0x14($sp)
/* 0926AC 80091AAC AFA90010 */  sw    $t1, 0x10($sp)
/* 0926B0 80091AB0 0C01E2AE */  jal   render_textured_rectangle
/* 0926B4 80091AB4 AFAB001C */   sw    $t3, 0x1c($sp)
/* 0926B8 80091AB8 3C02800E */  lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 0926BC 80091ABC 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 0926C0 80091AC0 10000019 */  b     .L80091B28
/* 0926C4 80091AC4 00000000 */   nop   
.L80091AC8:
/* 0926C8 80091AC8 3C0C800E */  lui   $t4, %hi(D_800E0414) # $t4, 0x800e
/* 0926CC 80091ACC 8D8C0414 */  lw    $t4, %lo(D_800E0414)($t4)
/* 0926D0 80091AD0 3C05800E */  lui   $a1, %hi(D_800E0648) # $a1, 0x800e
/* 0926D4 80091AD4 01960019 */  multu $t4, $s6
/* 0926D8 80091AD8 8FC90000 */  lw    $t1, ($fp)
/* 0926DC 80091ADC 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0926E0 80091AE0 240E00FF */  li    $t6, 255
/* 0926E4 80091AE4 240F00FF */  li    $t7, 255
/* 0926E8 80091AE8 241900FF */  li    $t9, 255
/* 0926EC 80091AEC AFB90018 */  sw    $t9, 0x18($sp)
/* 0926F0 80091AF0 AFAF0014 */  sw    $t7, 0x14($sp)
/* 0926F4 80091AF4 AFAE0010 */  sw    $t6, 0x10($sp)
/* 0926F8 80091AF8 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0926FC 80091AFC 24060095 */  li    $a2, 149
/* 092700 80091B00 02003825 */  move  $a3, $s0
/* 092704 80091B04 00006812 */  mflo  $t5
/* 092708 80091B08 000DC080 */  sll   $t8, $t5, 2
/* 09270C 80091B0C 00B82821 */  addu  $a1, $a1, $t8
/* 092710 80091B10 8CA50648 */  lw    $a1, %lo(D_800E0648)($a1)
/* 092714 80091B14 0C01E2AE */  jal   render_textured_rectangle
/* 092718 80091B18 AFA9001C */   sw    $t1, 0x1c($sp)
/* 09271C 80091B1C 3C02800E */  lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 092720 80091B20 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 092724 80091B24 00000000 */  nop   
.L80091B28:
/* 092728 80091B28 3C11800E */  lui   $s1, %hi(gRaceSelectionImages) # $s1, 0x800e
/* 09272C 80091B2C 24010002 */  li    $at, 2
/* 092730 80091B30 14410031 */  bne   $v0, $at, .L80091BF8
/* 092734 80091B34 26310624 */   addiu $s1, %lo(gRaceSelectionImages) # addiu $s1, $s1, 0x624
/* 092738 80091B38 8FAA0074 */  lw    $t2, 0x74($sp)
/* 09273C 80091B3C 3C088012 */  lui   $t0, %hi(gPlayerSelectVehicle) # $t0, 0x8012
/* 092740 80091B40 1540002D */  bnez  $t2, .L80091BF8
/* 092744 80091B44 00000000 */   nop   
/* 092748 80091B48 810869C0 */  lb    $t0, %lo(gPlayerSelectVehicle)($t0)
/* 09274C 80091B4C 8FD90000 */  lw    $t9, ($fp)
/* 092750 80091B50 01160019 */  multu $t0, $s6
/* 092754 80091B54 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 092758 80091B58 02E03825 */  move  $a3, $s7
/* 09275C 80091B5C 241800FF */  li    $t8, 255
/* 092760 80091B60 240E00FF */  li    $t6, 255
/* 092764 80091B64 240F00FF */  li    $t7, 255
/* 092768 80091B68 0200B825 */  move  $s7, $s0
/* 09276C 80091B6C 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 092770 80091B70 2406004F */  li    $a2, 79
/* 092774 80091B74 00005812 */  mflo  $t3
/* 092778 80091B78 000B6080 */  sll   $t4, $t3, 2
/* 09277C 80091B7C 022C6821 */  addu  $t5, $s1, $t4
/* 092780 80091B80 8DA50000 */  lw    $a1, ($t5)
/* 092784 80091B84 AFAF0018 */  sw    $t7, 0x18($sp)
/* 092788 80091B88 AFAE0014 */  sw    $t6, 0x14($sp)
/* 09278C 80091B8C AFB80010 */  sw    $t8, 0x10($sp)
/* 092790 80091B90 0C01E2AE */  jal   render_textured_rectangle
/* 092794 80091B94 AFB9001C */   sw    $t9, 0x1c($sp)
/* 092798 80091B98 3C028012 */  lui   $v0, %hi(gPlayerSelectVehicle+1) # $v0, 0x8012
/* 09279C 80091B9C 804269C1 */  lb    $v0, %lo(gPlayerSelectVehicle+1)($v0)
/* 0927A0 80091BA0 24010002 */  li    $at, 2
/* 0927A4 80091BA4 14410002 */  bne   $v0, $at, .L80091BB0
/* 0927A8 80091BA8 00000000 */   nop   
/* 0927AC 80091BAC 26170002 */  addiu $s7, $s0, 2
.L80091BB0:
/* 0927B0 80091BB0 00560019 */  multu $v0, $s6
/* 0927B4 80091BB4 8FD80000 */  lw    $t8, ($fp)
/* 0927B8 80091BB8 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0927BC 80091BBC 240B00FF */  li    $t3, 255
/* 0927C0 80091BC0 240C00FF */  li    $t4, 255
/* 0927C4 80091BC4 240D00FF */  li    $t5, 255
/* 0927C8 80091BC8 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0927CC 80091BCC 240600B0 */  li    $a2, 176
/* 0927D0 80091BD0 02E03825 */  move  $a3, $s7
/* 0927D4 80091BD4 00004812 */  mflo  $t1
/* 0927D8 80091BD8 00095080 */  sll   $t2, $t1, 2
/* 0927DC 80091BDC 022A4021 */  addu  $t0, $s1, $t2
/* 0927E0 80091BE0 8D050000 */  lw    $a1, ($t0)
/* 0927E4 80091BE4 AFAD0018 */  sw    $t5, 0x18($sp)
/* 0927E8 80091BE8 AFAC0014 */  sw    $t4, 0x14($sp)
/* 0927EC 80091BEC AFAB0010 */  sw    $t3, 0x10($sp)
/* 0927F0 80091BF0 0C01E2AE */  jal   render_textured_rectangle
/* 0927F4 80091BF4 AFB8001C */   sw    $t8, 0x1c($sp)
.L80091BF8:
/* 0927F8 80091BF8 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0927FC 80091BFC 0C01ECF4 */  jal   func_8007B3D0
/* 092800 80091C00 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 092804 80091C04 3C0E800E */  lui   $t6, %hi(gNumberOfActivePlayers) # $t6, 0x800e
/* 092808 80091C08 8DCEF4BC */  lw    $t6, %lo(gNumberOfActivePlayers)($t6)
/* 09280C 80091C0C 8FAF0074 */  lw    $t7, 0x74($sp)
/* 092810 80091C10 29C10003 */  slti  $at, $t6, 3
/* 092814 80091C14 10200022 */  beqz  $at, .L80091CA0
/* 092818 80091C18 8FAC0074 */   lw    $t4, 0x74($sp)
/* 09281C 80091C1C 15E0001F */  bnez  $t7, .L80091C9C
/* 092820 80091C20 3C02800E */   lui   $v0, %hi(gMenuImageStack) # $v0, 0x800e
/* 092824 80091C24 2442F75C */  addiu $v0, %lo(gMenuImageStack) # addiu $v0, $v0, -0x8a4
/* 092828 80091C28 3C01C250 */  li    $at, 0xC2500000 # -52.000000
/* 09282C 80091C2C 44814000 */  mtc1  $at, $f8
/* 092830 80091C30 8C590000 */  lw    $t9, ($v0)
/* 092834 80091C34 3C09800E */  lui   $t1, %hi(gNumberOfActivePlayers) # $t1, 0x800e
/* 092838 80091C38 E72800F0 */  swc1  $f8, 0xf0($t9)
/* 09283C 80091C3C 8D29F4BC */  lw    $t1, %lo(gNumberOfActivePlayers)($t1)
/* 092840 80091C40 24010001 */  li    $at, 1
/* 092844 80091C44 15210009 */  bne   $t1, $at, .L80091C6C
/* 092848 80091C48 24040007 */   li    $a0, 7
/* 09284C 80091C4C 3C0141A8 */  li    $at, 0x41A80000 # 21.000000
/* 092850 80091C50 44815000 */  mtc1  $at, $f10
/* 092854 80091C54 8C4A0000 */  lw    $t2, ($v0)
/* 092858 80091C58 24040007 */  li    $a0, 7
/* 09285C 80091C5C 0C027298 */  jal   func_8009CA60
/* 092860 80091C60 E54A00EC */   swc1  $f10, 0xec($t2)
/* 092864 80091C64 1000000E */  b     .L80091CA0
/* 092868 80091C68 8FAC0074 */   lw    $t4, 0x74($sp)
.L80091C6C:
/* 09286C 80091C6C 3C01C240 */  li    $at, 0xC2400000 # -48.000000
/* 092870 80091C70 44818000 */  mtc1  $at, $f16
/* 092874 80091C74 8C480000 */  lw    $t0, ($v0)
/* 092878 80091C78 0C027298 */  jal   func_8009CA60
/* 09287C 80091C7C E51000EC */   swc1  $f16, 0xec($t0)
/* 092880 80091C80 3C014240 */  li    $at, 0x42400000 # 48.000000
/* 092884 80091C84 3C0B800E */  lui   $t3, %hi(gMenuImageStack) # $t3, 0x800e
/* 092888 80091C88 8D6BF75C */  lw    $t3, %lo(gMenuImageStack)($t3)
/* 09288C 80091C8C 44819000 */  mtc1  $at, $f18
/* 092890 80091C90 24040007 */  li    $a0, 7
/* 092894 80091C94 0C027298 */  jal   func_8009CA60
/* 092898 80091C98 E57200EC */   swc1  $f18, 0xec($t3)
.L80091C9C:
/* 09289C 80091C9C 8FAC0074 */  lw    $t4, 0x74($sp)
.L80091CA0:
/* 0928A0 80091CA0 3C0D800E */  lui   $t5, %hi(gMenuText) # $t5, 0x800e
/* 0928A4 80091CA4 11800098 */  beqz  $t4, .L80091F08
/* 0928A8 80091CA8 00000000 */   nop   
/* 0928AC 80091CAC 8DADF4A0 */  lw    $t5, %lo(gMenuText)($t5)
/* 0928B0 80091CB0 00002825 */  move  $a1, $zero
/* 0928B4 80091CB4 8DA40220 */  lw    $a0, 0x220($t5)
/* 0928B8 80091CB8 0C031368 */  jal   func_800C4DA0
/* 0928BC 80091CBC 00003025 */   move  $a2, $zero
/* 0928C0 80091CC0 3C12800E */  lui   $s2, %hi(gTwoPlayerRacerCountMenu) # $s2, 0x800e
/* 0928C4 80091CC4 265206E4 */  addiu $s2, %lo(gTwoPlayerRacerCountMenu) # addiu $s2, $s2, 0x6e4
/* 0928C8 80091CC8 86430004 */  lh    $v1, 4($s2)
/* 0928CC 80091CCC 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0928D0 80091CD0 2478FFF4 */  addiu $t8, $v1, -0xc
/* 0928D4 80091CD4 0302082A */  slt   $at, $t8, $v0
/* 0928D8 80091CD8 10200003 */  beqz  $at, .L80091CE8
/* 0928DC 80091CDC 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0928E0 80091CE0 10000002 */  b     .L80091CEC
/* 0928E4 80091CE4 2454000C */   addiu $s4, $v0, 0xc
.L80091CE8:
/* 0928E8 80091CE8 0060A025 */  move  $s4, $v1
.L80091CEC:
/* 0928EC 80091CEC 3C0B8012 */  lui   $t3, %hi(D_80126550) # $t3, 0x8012
/* 0928F0 80091CF0 8D6B665C */  lw    $t3, %lo(D_80126550 + 0x10C)($t3)
/* 0928F4 80091CF4 864E0002 */  lh    $t6, 2($s2)
/* 0928F8 80091CF8 86590006 */  lh    $t9, 6($s2)
/* 0928FC 80091CFC 86490008 */  lh    $t1, 8($s2)
/* 092900 80091D00 864A000A */  lh    $t2, 0xa($s2)
/* 092904 80091D04 3C08B0E0 */  lui   $t0, (0xB0E0C0FF >> 16) # lui $t0, 0xb0e0
/* 092908 80091D08 3508C0FF */  ori   $t0, (0xB0E0C0FF & 0xFFFF) # ori $t0, $t0, 0xc0ff
/* 09290C 80091D0C 00142843 */  sra   $a1, $s4, 1
/* 092910 80091D10 240F0078 */  li    $t7, 120
/* 092914 80091D14 00052823 */  negu  $a1, $a1
/* 092918 80091D18 AFA8001C */  sw    $t0, 0x1c($sp)
/* 09291C 80091D1C 02803825 */  move  $a3, $s4
/* 092920 80091D20 AFAB0020 */  sw    $t3, 0x20($sp)
/* 092924 80091D24 01EE3023 */  subu  $a2, $t7, $t6
/* 092928 80091D28 AFB90010 */  sw    $t9, 0x10($sp)
/* 09292C 80091D2C AFA90014 */  sw    $t1, 0x14($sp)
/* 092930 80091D30 0C020160 */  jal   func_80080580
/* 092934 80091D34 AFAA0018 */   sw    $t2, 0x18($sp)
/* 092938 80091D38 0C02039B */  jal   func_80080E6C
/* 09293C 80091D3C 00000000 */   nop   
/* 092940 80091D40 0C0310BB */  jal   set_text_font
/* 092944 80091D44 00002025 */   move  $a0, $zero
/* 092948 80091D48 240C0080 */  li    $t4, 128
/* 09294C 80091D4C AFAC0010 */  sw    $t4, 0x10($sp)
/* 092950 80091D50 00002025 */  move  $a0, $zero
/* 092954 80091D54 00002825 */  move  $a1, $zero
/* 092958 80091D58 00003025 */  move  $a2, $zero
/* 09295C 80091D5C 0C0310E1 */  jal   set_text_colour
/* 092960 80091D60 240700FF */   li    $a3, 255
/* 092964 80091D64 864F000E */  lh    $t7, 0xe($s2)
/* 092968 80091D68 864E0002 */  lh    $t6, 2($s2)
/* 09296C 80091D6C 3C0A800E */  lui   $t2, %hi(gMenuText) # $t2, 0x800e
/* 092970 80091D70 8D4AF4A0 */  lw    $t2, %lo(gMenuText)($t2)
/* 092974 80091D74 864D000C */  lh    $t5, 0xc($s2)
/* 092978 80091D78 86580000 */  lh    $t8, ($s2)
/* 09297C 80091D7C 8FA90080 */  lw    $t1, 0x80($sp)
/* 092980 80091D80 01EEC821 */  addu  $t9, $t7, $t6
/* 092984 80091D84 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 092988 80091D88 2408000C */  li    $t0, 12
/* 09298C 80091D8C 8D470220 */  lw    $a3, 0x220($t2)
/* 092990 80091D90 01B82821 */  addu  $a1, $t5, $t8
/* 092994 80091D94 03293021 */  addu  $a2, $t9, $t1
/* 092998 80091D98 24C60001 */  addiu $a2, $a2, 1
/* 09299C 80091D9C 24A50001 */  addiu $a1, $a1, 1
/* 0929A0 80091DA0 AFA80010 */  sw    $t0, 0x10($sp)
/* 0929A4 80091DA4 0C031110 */  jal   draw_text
/* 0929A8 80091DA8 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0929AC 80091DAC 240B00FF */  li    $t3, 255
/* 0929B0 80091DB0 AFAB0010 */  sw    $t3, 0x10($sp)
/* 0929B4 80091DB4 240400FF */  li    $a0, 255
/* 0929B8 80091DB8 240500FF */  li    $a1, 255
/* 0929BC 80091DBC 240600FF */  li    $a2, 255
/* 0929C0 80091DC0 0C0310E1 */  jal   set_text_colour
/* 0929C4 80091DC4 00003825 */   move  $a3, $zero
/* 0929C8 80091DC8 8658000E */  lh    $t8, 0xe($s2)
/* 0929CC 80091DCC 864F0002 */  lh    $t7, 2($s2)
/* 0929D0 80091DD0 3C09800E */  lui   $t1, %hi(gMenuText) # $t1, 0x800e
/* 0929D4 80091DD4 8D29F4A0 */  lw    $t1, %lo(gMenuText)($t1)
/* 0929D8 80091DD8 864C000C */  lh    $t4, 0xc($s2)
/* 0929DC 80091DDC 864D0000 */  lh    $t5, ($s2)
/* 0929E0 80091DE0 8FB90080 */  lw    $t9, 0x80($sp)
/* 0929E4 80091DE4 030F7021 */  addu  $t6, $t8, $t7
/* 0929E8 80091DE8 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0929EC 80091DEC 240A000C */  li    $t2, 12
/* 0929F0 80091DF0 8D270220 */  lw    $a3, 0x220($t1)
/* 0929F4 80091DF4 018D2821 */  addu  $a1, $t4, $t5
/* 0929F8 80091DF8 01D93021 */  addu  $a2, $t6, $t9
/* 0929FC 80091DFC 24C6FFFF */  addiu $a2, $a2, -1
/* 092A00 80091E00 24A5FFFF */  addiu $a1, $a1, -1
/* 092A04 80091E04 AFAA0010 */  sw    $t2, 0x10($sp)
/* 092A08 80091E08 0C031110 */  jal   draw_text
/* 092A0C 80091E0C 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 092A10 80091E10 0C01A142 */  jal   func_80068508
/* 092A14 80091E14 24040001 */   li    $a0, 1
/* 092A18 80091E18 0C01EFC7 */  jal   func_8007BF1C
/* 092A1C 80091E1C 00002025 */   move  $a0, $zero
/* 092A20 80091E20 3C15800E */  lui   $s5, %hi(gMultiplayerSelectedNumberOfRacers) # $s5, 0x800e
/* 092A24 80091E24 3C11800E */  lui   $s1, %hi(sMenuGuiColourB) # $s1, 0x800e
/* 092A28 80091E28 3C10800E */  lui   $s0, %hi(sMenuGuiColourG) # $s0, 0x800e
/* 092A2C 80091E2C 2610F4A8 */  addiu $s0, %lo(sMenuGuiColourG) # addiu $s0, $s0, -0xb58
/* 092A30 80091E30 2631F4AC */  addiu $s1, %lo(sMenuGuiColourB) # addiu $s1, $s1, -0xb54
/* 092A34 80091E34 26B50410 */  addiu $s5, %lo(gMultiplayerSelectedNumberOfRacers) # addiu $s5, $s5, 0x410
/* 092A38 80091E38 0000A025 */  move  $s4, $zero
/* 092A3C 80091E3C 241300FF */  li    $s3, 255
.L80091E40:
/* 092A40 80091E40 8EA80000 */  lw    $t0, ($s5)
/* 092A44 80091E44 3C0B8012 */  lui   $t3, %hi(D_801263E0) # $t3, 0x8012
/* 092A48 80091E48 1688000D */  bne   $s4, $t0, .L80091E80
/* 092A4C 80091E4C 00141040 */   sll   $v0, $s4, 1
/* 092A50 80091E50 8D6B63E0 */  lw    $t3, %lo(D_801263E0)($t3)
/* 092A54 80091E54 8FAC0084 */  lw    $t4, 0x84($sp)
/* 092A58 80091E58 29610003 */  slti  $at, $t3, 3
/* 092A5C 80091E5C 10200005 */  beqz  $at, .L80091E74
/* 092A60 80091E60 240D00FF */   li    $t5, 255
/* 092A64 80091E64 01AC1023 */  subu  $v0, $t5, $t4
/* 092A68 80091E68 A2020000 */  sb    $v0, ($s0)
/* 092A6C 80091E6C 10000003 */  b     .L80091E7C
/* 092A70 80091E70 A2220000 */   sb    $v0, ($s1)
.L80091E74:
/* 092A74 80091E74 A2000000 */  sb    $zero, ($s0)
/* 092A78 80091E78 A2200000 */  sb    $zero, ($s1)
.L80091E7C:
/* 092A7C 80091E7C 00141040 */  sll   $v0, $s4, 1
.L80091E80:
/* 092A80 80091E80 0002C040 */  sll   $t8, $v0, 1
/* 092A84 80091E84 02581821 */  addu  $v1, $s2, $t8
/* 092A88 80091E88 846F0010 */  lh    $t7, 0x10($v1)
/* 092A8C 80091E8C 864E0000 */  lh    $t6, ($s2)
/* 092A90 80091E90 3C05800E */  lui   $a1, %hi(gMenuImageStack) # $a1, 0x800e
/* 092A94 80091E94 01EEC821 */  addu  $t9, $t7, $t6
/* 092A98 80091E98 2729FF60 */  addiu $t1, $t9, -0xa0
/* 092A9C 80091E9C 44892000 */  mtc1  $t1, $f4
/* 092AA0 80091EA0 24A5F75C */  addiu $a1, %lo(gMenuImageStack) # addiu $a1, $a1, -0x8a4
/* 092AA4 80091EA4 468021A0 */  cvt.s.w $f6, $f4
/* 092AA8 80091EA8 8CAA0000 */  lw    $t2, ($a1)
/* 092AAC 80091EAC 244E0002 */  addiu $t6, $v0, 2
/* 092AB0 80091EB0 E546000C */  swc1  $f6, 0xc($t2)
/* 092AB4 80091EB4 84680012 */  lh    $t0, 0x12($v1)
/* 092AB8 80091EB8 864D0002 */  lh    $t5, 2($s2)
/* 092ABC 80091EBC 00085823 */  negu  $t3, $t0
/* 092AC0 80091EC0 016D6023 */  subu  $t4, $t3, $t5
/* 092AC4 80091EC4 25980078 */  addiu $t8, $t4, 0x78
/* 092AC8 80091EC8 44984000 */  mtc1  $t8, $f8
/* 092ACC 80091ECC 8CAF0000 */  lw    $t7, ($a1)
/* 092AD0 80091ED0 468042A0 */  cvt.s.w $f10, $f8
/* 092AD4 80091ED4 00002025 */  move  $a0, $zero
/* 092AD8 80091ED8 E5EA0010 */  swc1  $f10, 0x10($t7)
/* 092ADC 80091EDC 8CB90000 */  lw    $t9, ($a1)
/* 092AE0 80091EE0 0C027298 */  jal   func_8009CA60
/* 092AE4 80091EE4 A72E0018 */   sh    $t6, 0x18($t9)
/* 092AE8 80091EE8 26940001 */  addiu $s4, $s4, 1
/* 092AEC 80091EEC A2130000 */  sb    $s3, ($s0)
/* 092AF0 80091EF0 1696FFD3 */  bne   $s4, $s6, .L80091E40
/* 092AF4 80091EF4 A2330000 */   sb    $s3, ($s1)
/* 092AF8 80091EF8 0C01EFC7 */  jal   func_8007BF1C
/* 092AFC 80091EFC 24040001 */   li    $a0, 1
/* 092B00 80091F00 0C01A142 */  jal   func_80068508
/* 092B04 80091F04 00002025 */   move  $a0, $zero
.L80091F08:
/* 092B08 80091F08 3C098012 */  lui   $t1, %hi(D_801269C8) # $t1, 0x8012
/* 092B0C 80091F0C 8D2969C8 */  lw    $t1, %lo(D_801269C8)($t1)
/* 092B10 80091F10 24160003 */  li    $s6, 3
/* 092B14 80091F14 29210004 */  slti  $at, $t1, 4
/* 092B18 80091F18 1020003D */  beqz  $at, .L80092010
/* 092B1C 80091F1C 00000000 */   nop   
/* 092B20 80091F20 0C01EFC7 */  jal   func_8007BF1C
/* 092B24 80091F24 00002025 */   move  $a0, $zero
/* 092B28 80091F28 3C0A800E */  lui   $t2, %hi(gIsInAdventureTwo) # $t2, 0x800e
/* 092B2C 80091F2C 8D4AF494 */  lw    $t2, %lo(gIsInAdventureTwo)($t2)
/* 092B30 80091F30 2415000B */  li    $s5, 11
/* 092B34 80091F34 11400002 */  beqz  $t2, .L80091F40
/* 092B38 80091F38 3C014228 */   li    $at, 0x42280000 # 42.000000
/* 092B3C 80091F3C 2415000C */  li    $s5, 12
.L80091F40:
/* 092B40 80091F40 3C08800E */  lui   $t0, %hi(gMenuImageStack) # $t0, 0x800e
/* 092B44 80091F44 8D08F75C */  lw    $t0, %lo(gMenuImageStack)($t0)
/* 092B48 80091F48 44818000 */  mtc1  $at, $f16
/* 092B4C 80091F4C 00158140 */  sll   $s0, $s5, 5
/* 092B50 80091F50 01105821 */  addu  $t3, $t0, $s0
/* 092B54 80091F54 E5700010 */  swc1  $f16, 0x10($t3)
/* 092B58 80091F58 8FAD0070 */  lw    $t5, 0x70($sp)
/* 092B5C 80091F5C 3C18800E */  lui   $t8, %hi(gTrackIdForPreview) # $t8, 0x800e
/* 092B60 80091F60 8F18F4C4 */  lw    $t8, %lo(gTrackIdForPreview)($t8)
/* 092B64 80091F64 8DAC0004 */  lw    $t4, 4($t5)
/* 092B68 80091F68 00187880 */  sll   $t7, $t8, 2
/* 092B6C 80091F6C 018F7021 */  addu  $t6, $t4, $t7
/* 092B70 80091F70 8DD90000 */  lw    $t9, ($t6)
/* 092B74 80091F74 00000000 */  nop   
/* 092B78 80091F78 33290002 */  andi  $t1, $t9, 2
/* 092B7C 80091F7C 15200004 */  bnez  $t1, .L80091F90
/* 092B80 80091F80 00000000 */   nop   
/* 092B84 80091F84 0C027B18 */  jal   is_adventure_two_unlocked
/* 092B88 80091F88 00000000 */   nop   
/* 092B8C 80091F8C 10400008 */  beqz  $v0, .L80091FB0
.L80091F90:
/* 092B90 80091F90 3C0A800E */   lui   $t2, %hi(gMenuImageStack) # $t2, 0x800e
/* 092B94 80091F94 8D4AF75C */  lw    $t2, %lo(gMenuImageStack)($t2)
/* 092B98 80091F98 3C01C300 */  li    $at, 0xC3000000 # -128.000000
/* 092B9C 80091F9C 44819000 */  mtc1  $at, $f18
/* 092BA0 80091FA0 01504021 */  addu  $t0, $t2, $s0
/* 092BA4 80091FA4 02A02025 */  move  $a0, $s5
/* 092BA8 80091FA8 0C027298 */  jal   func_8009CA60
/* 092BAC 80091FAC E512000C */   swc1  $f18, 0xc($t0)
.L80091FB0:
/* 092BB0 80091FB0 8FAB0070 */  lw    $t3, 0x70($sp)
/* 092BB4 80091FB4 3C18800E */  lui   $t8, %hi(gTrackIdForPreview) # $t8, 0x800e
/* 092BB8 80091FB8 8F18F4C4 */  lw    $t8, %lo(gTrackIdForPreview)($t8)
/* 092BBC 80091FBC 8D6D0004 */  lw    $t5, 4($t3)
/* 092BC0 80091FC0 00186080 */  sll   $t4, $t8, 2
/* 092BC4 80091FC4 01AC7821 */  addu  $t7, $t5, $t4
/* 092BC8 80091FC8 8DEE0000 */  lw    $t6, ($t7)
/* 092BCC 80091FCC 00000000 */  nop   
/* 092BD0 80091FD0 31D90004 */  andi  $t9, $t6, 4
/* 092BD4 80091FD4 17200004 */  bnez  $t9, .L80091FE8
/* 092BD8 80091FD8 00000000 */   nop   
/* 092BDC 80091FDC 0C027B18 */  jal   is_adventure_two_unlocked
/* 092BE0 80091FE0 00000000 */   nop   
/* 092BE4 80091FE4 10400008 */  beqz  $v0, .L80092008
.L80091FE8:
/* 092BE8 80091FE8 3C09800E */   lui   $t1, %hi(gMenuImageStack) # $t1, 0x800e
/* 092BEC 80091FEC 8D29F75C */  lw    $t1, %lo(gMenuImageStack)($t1)
/* 092BF0 80091FF0 3C0142F0 */  li    $at, 0x42F00000 # 120.000000
/* 092BF4 80091FF4 44812000 */  mtc1  $at, $f4
/* 092BF8 80091FF8 01305021 */  addu  $t2, $t1, $s0
/* 092BFC 80091FFC 02A02025 */  move  $a0, $s5
/* 092C00 80092000 0C027298 */  jal   func_8009CA60
/* 092C04 80092004 E544000C */   swc1  $f4, 0xc($t2)
.L80092008:
/* 092C08 80092008 0C01EFC7 */  jal   func_8007BF1C
/* 092C0C 8009200C 24040001 */   li    $a0, 1
.L80092010:
/* 092C10 80092010 3C08800E */  lui   $t0, %hi(gNumberOfActivePlayers) # $t0, 0x800e
/* 092C14 80092014 8D08F4BC */  lw    $t0, %lo(gNumberOfActivePlayers)($t0)
/* 092C18 80092018 24010001 */  li    $at, 1
/* 092C1C 8009201C 1501001C */  bne   $t0, $at, .L80092090
/* 092C20 80092020 3C0B8012 */   lui   $t3, %hi(D_801263E0) # $t3, 0x8012
/* 092C24 80092024 8D6B63E0 */  lw    $t3, %lo(D_801263E0)($t3)
/* 092C28 80092028 3C04800E */  lui   $a0, %hi(gTrackIdForPreview) # $a0, 0x800e
/* 092C2C 8009202C 05600018 */  bltz  $t3, .L80092090
/* 092C30 80092030 00000000 */   nop   
/* 092C34 80092034 8C84F4C4 */  lw    $a0, %lo(gTrackIdForPreview)($a0)
/* 092C38 80092038 0C024AF8 */  jal   func_80092BE0
/* 092C3C 8009203C 00000000 */   nop   
/* 092C40 80092040 04400013 */  bltz  $v0, .L80092090
/* 092C44 80092044 3C048012 */   lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 092C48 80092048 8FA70080 */  lw    $a3, 0x80($sp)
/* 092C4C 8009204C 8FCF0000 */  lw    $t7, ($fp)
/* 092C50 80092050 3C05800E */  lui   $a1, %hi(gRaceSelectionTTTexture) # $a1, 0x800e
/* 092C54 80092054 241800FF */  li    $t8, 255
/* 092C58 80092058 240D00FF */  li    $t5, 255
/* 092C5C 8009205C 240C00FF */  li    $t4, 255
/* 092C60 80092060 AFAC0018 */  sw    $t4, 0x18($sp)
/* 092C64 80092064 AFAD0014 */  sw    $t5, 0x14($sp)
/* 092C68 80092068 AFB80010 */  sw    $t8, 0x10($sp)
/* 092C6C 8009206C 24A50614 */  addiu $a1, %lo(gRaceSelectionTTTexture) # addiu $a1, $a1, 0x614
/* 092C70 80092070 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 092C74 80092074 240600CC */  li    $a2, 204
/* 092C78 80092078 24E7007A */  addiu $a3, $a3, 0x7a
/* 092C7C 8009207C 0C01E2AE */  jal   render_textured_rectangle
/* 092C80 80092080 AFAF001C */   sw    $t7, 0x1c($sp)
/* 092C84 80092084 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 092C88 80092088 0C01ECF4 */  jal   func_8007B3D0
/* 092C8C 8009208C 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
.L80092090:
/* 092C90 80092090 3C0E8012 */  lui   $t6, %hi(D_801269C8) # $t6, 0x8012
/* 092C94 80092094 8DCE69C8 */  lw    $t6, %lo(D_801269C8)($t6)
/* 092C98 80092098 24010005 */  li    $at, 5
/* 092C9C 8009209C 11C1002C */  beq   $t6, $at, .L80092150
/* 092CA0 800920A0 3C028012 */   lui   $v0, %hi(D_801263E0) # $v0, 0x8012
/* 092CA4 800920A4 8C4263E0 */  lw    $v0, %lo(D_801263E0)($v0)
/* 092CA8 800920A8 24010002 */  li    $at, 2
/* 092CAC 800920AC 14410005 */  bne   $v0, $at, .L800920C4
/* 092CB0 800920B0 00000000 */   nop   
/* 092CB4 800920B4 8FB90074 */  lw    $t9, 0x74($sp)
/* 092CB8 800920B8 00000000 */  nop   
/* 092CBC 800920BC 13200009 */  beqz  $t9, .L800920E4
/* 092CC0 800920C0 00000000 */   nop   
.L800920C4:
/* 092CC4 800920C4 16C20005 */  bne   $s6, $v0, .L800920DC
/* 092CC8 800920C8 24010004 */   li    $at, 4
/* 092CCC 800920CC 8FA90074 */  lw    $t1, 0x74($sp)
/* 092CD0 800920D0 00000000 */  nop   
/* 092CD4 800920D4 15200003 */  bnez  $t1, .L800920E4
/* 092CD8 800920D8 00000000 */   nop   
.L800920DC:
/* 092CDC 800920DC 1441001D */  bne   $v0, $at, .L80092154
/* 092CE0 800920E0 240C00FF */   li    $t4, 255
.L800920E4:
/* 092CE4 800920E4 0C0310BB */  jal   set_text_font
/* 092CE8 800920E8 24040002 */   li    $a0, 2
/* 092CEC 800920EC 8FCA0000 */  lw    $t2, ($fp)
/* 092CF0 800920F0 240400FF */  li    $a0, 255
/* 092CF4 800920F4 240500FF */  li    $a1, 255
/* 092CF8 800920F8 240600FF */  li    $a2, 255
/* 092CFC 800920FC 00003825 */  move  $a3, $zero
/* 092D00 80092100 0C0310E1 */  jal   set_text_colour
/* 092D04 80092104 AFAA0010 */   sw    $t2, 0x10($sp)
/* 092D08 80092108 3C088012 */  lui   $t0, %hi(D_801269C8) # $t0, 0x8012
/* 092D0C 8009210C 8D0869C8 */  lw    $t0, %lo(D_801269C8)($t0)
/* 092D10 80092110 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 092D14 80092114 29010004 */  slti  $at, $t0, 4
/* 092D18 80092118 14200005 */  bnez  $at, .L80092130
/* 092D1C 8009211C 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 092D20 80092120 8FAB0080 */  lw    $t3, 0x80($sp)
/* 092D24 80092124 00000000 */  nop   
/* 092D28 80092128 25780018 */  addiu $t8, $t3, 0x18
/* 092D2C 8009212C AFB80080 */  sw    $t8, 0x80($sp)
.L80092130:
/* 092D30 80092130 8FA60080 */  lw    $a2, 0x80($sp)
/* 092D34 80092134 3C07800F */  lui   $a3, %hi(D_800E823C) # $a3, 0x800f
/* 092D38 80092138 240D000C */  li    $t5, 12
/* 092D3C 8009213C AFAD0010 */  sw    $t5, 0x10($sp)
/* 092D40 80092140 24E7823C */  addiu $a3, %lo(D_800E823C) # addiu $a3, $a3, -0x7dc4
/* 092D44 80092144 240500A0 */  li    $a1, 160
/* 092D48 80092148 0C031110 */  jal   draw_text
/* 092D4C 8009214C 24C600AC */   addiu $a2, $a2, 0xac
.L80092150:
/* 092D50 80092150 240C00FF */  li    $t4, 255
.L80092154:
/* 092D54 80092154 AFCC0000 */  sw    $t4, ($fp)
.L80092158:
/* 092D58 80092158 8FBF0054 */  lw    $ra, 0x54($sp)
/* 092D5C 8009215C 8FB00030 */  lw    $s0, 0x30($sp)
/* 092D60 80092160 8FB10034 */  lw    $s1, 0x34($sp)
/* 092D64 80092164 8FB20038 */  lw    $s2, 0x38($sp)
/* 092D68 80092168 8FB3003C */  lw    $s3, 0x3c($sp)
/* 092D6C 8009216C 8FB40040 */  lw    $s4, 0x40($sp)
/* 092D70 80092170 8FB50044 */  lw    $s5, 0x44($sp)
/* 092D74 80092174 8FB60048 */  lw    $s6, 0x48($sp)
/* 092D78 80092178 8FB7004C */  lw    $s7, 0x4c($sp)
/* 092D7C 8009217C 8FBE0050 */  lw    $fp, 0x50($sp)
/* 092D80 80092180 03E00008 */  jr    $ra
/* 092D84 80092184 27BD0098 */   addiu $sp, $sp, 0x98

