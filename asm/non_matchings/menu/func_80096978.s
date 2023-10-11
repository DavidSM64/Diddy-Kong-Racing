glabel func_80096978
/* 097578 80096978 27BDFF50 */  addiu $sp, $sp, -0xb0
/* 09757C 8009697C E7B4002C */  swc1  $f20, 0x2c($sp)
/* 097580 80096980 4485A000 */  mtc1  $a1, $f20
/* 097584 80096984 AFBF005C */  sw    $ra, 0x5c($sp)
/* 097588 80096988 AFBE0058 */  sw    $fp, 0x58($sp)
/* 09758C 8009698C AFB70054 */  sw    $s7, 0x54($sp)
/* 097590 80096990 AFB60050 */  sw    $s6, 0x50($sp)
/* 097594 80096994 AFB5004C */  sw    $s5, 0x4c($sp)
/* 097598 80096998 AFB40048 */  sw    $s4, 0x48($sp)
/* 09759C 8009699C AFB30044 */  sw    $s3, 0x44($sp)
/* 0975A0 800969A0 AFB20040 */  sw    $s2, 0x40($sp)
/* 0975A4 800969A4 AFB1003C */  sw    $s1, 0x3c($sp)
/* 0975A8 800969A8 AFB00038 */  sw    $s0, 0x38($sp)
/* 0975AC 800969AC E7B70030 */  swc1  $f23, 0x30($sp)
/* 0975B0 800969B0 E7B60034 */  swc1  $f22, 0x34($sp)
/* 0975B4 800969B4 E7B50028 */  swc1  $f21, 0x28($sp)
/* 0975B8 800969B8 0C01BAA4 */  jal   get_settings
/* 0975BC 800969BC AFA400B0 */   sw    $a0, 0xb0($sp)
/* 0975C0 800969C0 3C0E8000 */  lui   $t6, %hi(osTvType) # $t6, 0x8000
/* 0975C4 800969C4 8DCE0300 */  lw    $t6, %lo(osTvType)($t6)
/* 0975C8 800969C8 AFA20084 */  sw    $v0, 0x84($sp)
/* 0975CC 800969CC 15C00002 */  bnez  $t6, .L800969D8
/* 0975D0 800969D0 00001825 */   move  $v1, $zero
/* 0975D4 800969D4 2403000C */  li    $v1, 12
.L800969D8:
/* 0975D8 800969D8 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0975DC 800969DC 3C058012 */  lui   $a1, %hi(sMenuCurrHudMat) # $a1, 0x8012
/* 0975E0 800969E0 24A563A8 */  addiu $a1, %lo(sMenuCurrHudMat) # addiu $a1, $a1, 0x63a8
/* 0975E4 800969E4 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0975E8 800969E8 0C019FCB */  jal   set_ortho_matrix_view
/* 0975EC 800969EC AFA30098 */   sw    $v1, 0x98($sp)
/* 0975F0 800969F0 44800000 */  mtc1  $zero, $f0
/* 0975F4 800969F4 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 0975F8 800969F8 4600A03C */  c.lt.s $f20, $f0
/* 0975FC 800969FC 00000000 */  nop   
/* 097600 80096A00 45000002 */  bc1f  .L80096A0C
/* 097604 80096A04 00000000 */   nop   
/* 097608 80096A08 46000506 */  mov.s $f20, $f0
.L80096A0C:
/* 09760C 80096A0C 44810000 */  mtc1  $at, $f0
/* 097610 80096A10 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 097614 80096A14 4614003C */  c.lt.s $f0, $f20
/* 097618 80096A18 44812000 */  mtc1  $at, $f4
/* 09761C 80096A1C 45000002 */  bc1f  .L80096A28
/* 097620 80096A20 3C01437F */   li    $at, 0x437F0000 # 255.000000
/* 097624 80096A24 46000506 */  mov.s $f20, $f0
.L80096A28:
/* 097628 80096A28 46142181 */  sub.s $f6, $f4, $f20
/* 09762C 80096A2C 44814000 */  mtc1  $at, $f8
/* 097630 80096A30 3C10800E */  lui   $s0, %hi(sMenuGuiOpacity) # $s0, 0x800e
/* 097634 80096A34 46083282 */  mul.s $f10, $f6, $f8
/* 097638 80096A38 2610F764 */  addiu $s0, %lo(sMenuGuiOpacity) # addiu $s0, $s0, -0x89c
/* 09763C 80096A3C 24040002 */  li    $a0, 2
/* 097640 80096A40 444FF800 */  cfc1  $t7, $31
/* 097644 80096A44 00000000 */  nop   
/* 097648 80096A48 35E10003 */  ori   $at, $t7, 3
/* 09764C 80096A4C 38210002 */  xori  $at, $at, 2
/* 097650 80096A50 44C1F800 */  ctc1  $at, $31
/* 097654 80096A54 00000000 */  nop   
/* 097658 80096A58 46005424 */  cvt.w.s $f16, $f10
/* 09765C 80096A5C 44188000 */  mfc1  $t8, $f16
/* 097660 80096A60 44CFF800 */  ctc1  $t7, $31
/* 097664 80096A64 0C0310BB */  jal   set_text_font
/* 097668 80096A68 AE180000 */   sw    $t8, ($s0)
/* 09766C 80096A6C 00002025 */  move  $a0, $zero
/* 097670 80096A70 00002825 */  move  $a1, $zero
/* 097674 80096A74 00003025 */  move  $a2, $zero
/* 097678 80096A78 0C0310F3 */  jal   set_text_background_colour
/* 09767C 80096A7C 00003825 */   move  $a3, $zero
/* 097680 80096A80 8E190000 */  lw    $t9, ($s0)
/* 097684 80096A84 240400FF */  li    $a0, 255
/* 097688 80096A88 240500FF */  li    $a1, 255
/* 09768C 80096A8C 240600FF */  li    $a2, 255
/* 097690 80096A90 00003825 */  move  $a3, $zero
/* 097694 80096A94 0C0310E1 */  jal   set_text_colour
/* 097698 80096A98 AFB90010 */   sw    $t9, 0x10($sp)
/* 09769C 80096A9C 3C08800E */  lui   $t0, %hi(gMenuText) # $t0, 0x800e
/* 0976A0 80096AA0 8D08F4A0 */  lw    $t0, %lo(gMenuText)($t0)
/* 0976A4 80096AA4 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0976A8 80096AA8 2409000C */  li    $t1, 12
/* 0976AC 80096AAC 8D070084 */  lw    $a3, 0x84($t0)
/* 0976B0 80096AB0 AFA90010 */  sw    $t1, 0x10($sp)
/* 0976B4 80096AB4 248463A0 */  addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0976B8 80096AB8 24058000 */  li    $a1, -32768
/* 0976BC 80096ABC 0C031110 */  jal   draw_text
/* 0976C0 80096AC0 24060022 */   li    $a2, 34
/* 0976C4 80096AC4 240A00FF */  li    $t2, 255
/* 0976C8 80096AC8 AE0A0000 */  sw    $t2, ($s0)
/* 0976CC 80096ACC 3C02800E */  lui   $v0, %hi(gNumberOfActivePlayers) # $v0, 0x800e
/* 0976D0 80096AD0 8C42F4BC */  lw    $v0, %lo(gNumberOfActivePlayers)($v0)
/* 0976D4 80096AD4 240D00A0 */  li    $t5, 160
/* 0976D8 80096AD8 244BFFFF */  addiu $t3, $v0, -1
/* 0976DC 80096ADC 000B6140 */  sll   $t4, $t3, 5
/* 0976E0 80096AE0 01ACA823 */  subu  $s5, $t5, $t4
/* 0976E4 80096AE4 AFB500A4 */  sw    $s5, 0xa4($sp)
/* 0976E8 80096AE8 1840003A */  blez  $v0, .L80096BD4
/* 0976EC 80096AEC 0000B025 */   move  $s6, $zero
/* 0976F0 80096AF0 3C014370 */  li    $at, 0x43700000 # 240.000000
/* 0976F4 80096AF4 44819000 */  mtc1  $at, $f18
/* 0976F8 80096AF8 24190036 */  li    $t9, 54
/* 0976FC 80096AFC 46149102 */  mul.s $f4, $f18, $f20
/* 097700 80096B00 3C12800E */  lui   $s2, %hi(gRacerPortraits) # $s2, 0x800e
/* 097704 80096B04 8FB00084 */  lw    $s0, 0x84($sp)
/* 097708 80096B08 26520AF0 */  addiu $s2, %lo(gRacerPortraits) # addiu $s2, $s2, 0xaf0
/* 09770C 80096B0C 444FF800 */  cfc1  $t7, $31
/* 097710 80096B10 2413017F */  li    $s3, 383
/* 097714 80096B14 35E10003 */  ori   $at, $t7, 3
/* 097718 80096B18 38210002 */  xori  $at, $at, 2
/* 09771C 80096B1C 44C1F800 */  ctc1  $at, $31
/* 097720 80096B20 00000000 */  nop   
/* 097724 80096B24 460021A4 */  cvt.w.s $f6, $f4
/* 097728 80096B28 44183000 */  mfc1  $t8, $f6
/* 09772C 80096B2C 44CFF800 */  ctc1  $t7, $31
/* 097730 80096B30 03388823 */  subu  $s1, $t9, $t8
/* 097734 80096B34 00000000 */  nop   
.L80096B38:
/* 097738 80096B38 8208005A */  lb    $t0, 0x5a($s0)
/* 09773C 80096B3C 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 097740 80096B40 1500000E */  bnez  $t0, .L80096B7C
/* 097744 80096B44 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 097748 80096B48 3C028012 */  lui   $v0, %hi(gOptionBlinkTimer) # $v0, 0x8012
/* 09774C 80096B4C 8C4263BC */  lw    $v0, %lo(gOptionBlinkTimer)($v0)
/* 097750 80096B50 00000000 */  nop   
/* 097754 80096B54 28410020 */  slti  $at, $v0, 0x20
/* 097758 80096B58 10200005 */  beqz  $at, .L80096B70
/* 09775C 80096B5C 00025880 */   sll   $t3, $v0, 2
/* 097760 80096B60 00024880 */  sll   $t1, $v0, 2
/* 097764 80096B64 252A0080 */  addiu $t2, $t1, 0x80
/* 097768 80096B68 10000006 */  b     .L80096B84
/* 09776C 80096B6C AFAA00A0 */   sw    $t2, 0xa0($sp)
.L80096B70:
/* 097770 80096B70 026B6823 */  subu  $t5, $s3, $t3
/* 097774 80096B74 10000003 */  b     .L80096B84
/* 097778 80096B78 AFAD00A0 */   sw    $t5, 0xa0($sp)
.L80096B7C:
/* 09777C 80096B7C 240C00FF */  li    $t4, 255
/* 097780 80096B80 AFAC00A0 */  sw    $t4, 0xa0($sp)
.L80096B84:
/* 097784 80096B84 820E0059 */  lb    $t6, 0x59($s0)
/* 097788 80096B88 93A200A3 */  lbu   $v0, 0xa3($sp)
/* 09778C 80096B8C 000E7880 */  sll   $t7, $t6, 2
/* 097790 80096B90 024FC821 */  addu  $t9, $s2, $t7
/* 097794 80096B94 8F250000 */  lw    $a1, ($t9)
/* 097798 80096B98 241800FF */  li    $t8, 255
/* 09779C 80096B9C AFB8001C */  sw    $t8, 0x1c($sp)
/* 0977A0 80096BA0 26A6FFEC */  addiu $a2, $s5, -0x14
/* 0977A4 80096BA4 02203825 */  move  $a3, $s1
/* 0977A8 80096BA8 AFA20018 */  sw    $v0, 0x18($sp)
/* 0977AC 80096BAC AFA20014 */  sw    $v0, 0x14($sp)
/* 0977B0 80096BB0 0C01E2AE */  jal   render_textured_rectangle
/* 0977B4 80096BB4 AFA20010 */   sw    $v0, 0x10($sp)
/* 0977B8 80096BB8 3C08800E */  lui   $t0, %hi(gNumberOfActivePlayers) # $t0, 0x800e
/* 0977BC 80096BBC 8D08F4BC */  lw    $t0, %lo(gNumberOfActivePlayers)($t0)
/* 0977C0 80096BC0 26D60001 */  addiu $s6, $s6, 1
/* 0977C4 80096BC4 02C8082A */  slt   $at, $s6, $t0
/* 0977C8 80096BC8 26100018 */  addiu $s0, $s0, 0x18
/* 0977CC 80096BCC 1420FFDA */  bnez  $at, .L80096B38
/* 0977D0 80096BD0 26B50040 */   addiu $s5, $s5, 0x40
.L80096BD4:
/* 0977D4 80096BD4 3C0143A0 */  li    $at, 0x43A00000 # 320.000000
/* 0977D8 80096BD8 44814000 */  mtc1  $at, $f8
/* 0977DC 80096BDC 8FAB00A4 */  lw    $t3, 0xa4($sp)
/* 0977E0 80096BE0 46144282 */  mul.s $f10, $f8, $f20
/* 0977E4 80096BE4 00002025 */  move  $a0, $zero
/* 0977E8 80096BE8 4449F800 */  cfc1  $t1, $31
/* 0977EC 80096BEC 00000000 */  nop   
/* 0977F0 80096BF0 35210003 */  ori   $at, $t1, 3
/* 0977F4 80096BF4 38210002 */  xori  $at, $at, 2
/* 0977F8 80096BF8 44C1F800 */  ctc1  $at, $31
/* 0977FC 80096BFC 00000000 */  nop   
/* 097800 80096C00 46005424 */  cvt.w.s $f16, $f10
/* 097804 80096C04 440A8000 */  mfc1  $t2, $f16
/* 097808 80096C08 44C9F800 */  ctc1  $t1, $31
/* 09780C 80096C0C 014B6821 */  addu  $t5, $t2, $t3
/* 097810 80096C10 0C0310BB */  jal   set_text_font
/* 097814 80096C14 AFAD00A4 */   sw    $t5, 0xa4($sp)
/* 097818 80096C18 8FA30098 */  lw    $v1, 0x98($sp)
/* 09781C 80096C1C 8FA200A4 */  lw    $v0, 0xa4($sp)
/* 097820 80096C20 24630068 */  addiu $v1, $v1, 0x68
/* 097824 80096C24 3C0F800E */  lui   $t7, %hi(gRacePlacementsArray) # $t7, 0x800e
/* 097828 80096C28 3C014140 */  li    $at, 0x41400000 # 12.000000
/* 09782C 80096C2C 240C0068 */  li    $t4, 104
/* 097830 80096C30 25EF0BCC */  addiu $t7, %lo(gRacePlacementsArray) # addiu $t7, $t7, 0xbcc
/* 097834 80096C34 246E0004 */  addiu $t6, $v1, 4
/* 097838 80096C38 24790002 */  addiu $t9, $v1, 2
/* 09783C 80096C3C 241800FF */  li    $t8, 255
/* 097840 80096C40 3C13800E */  lui   $s3, %hi(gMenuImageStack) # $s3, 0x800e
/* 097844 80096C44 2448FFDE */  addiu $t0, $v0, -0x22
/* 097848 80096C48 2449FFE0 */  addiu $t1, $v0, -0x20
/* 09784C 80096C4C 4481A000 */  mtc1  $at, $f20
/* 097850 80096C50 AFAC00A8 */  sw    $t4, 0xa8($sp)
/* 097854 80096C54 AFA90064 */  sw    $t1, 0x64($sp)
/* 097858 80096C58 AFA80068 */  sw    $t0, 0x68($sp)
/* 09785C 80096C5C 2673F75C */  addiu $s3, %lo(gMenuImageStack) # addiu $s3, $s3, -0x8a4
/* 097860 80096C60 AFB80070 */  sw    $t8, 0x70($sp)
/* 097864 80096C64 AFB90074 */  sw    $t9, 0x74($sp)
/* 097868 80096C68 AFAE007C */  sw    $t6, 0x7c($sp)
/* 09786C 80096C6C AFAF0078 */  sw    $t7, 0x78($sp)
/* 097870 80096C70 AFA000A0 */  sw    $zero, 0xa0($sp)
/* 097874 80096C74 241E000A */  li    $fp, 10
/* 097878 80096C78 24170064 */  li    $s7, 100
.L80096C7C:
/* 09787C 80096C7C 8FB500A4 */  lw    $s5, 0xa4($sp)
/* 097880 80096C80 240A00FF */  li    $t2, 255
/* 097884 80096C84 AFAA0010 */  sw    $t2, 0x10($sp)
/* 097888 80096C88 00002025 */  move  $a0, $zero
/* 09788C 80096C8C 00002825 */  move  $a1, $zero
/* 097890 80096C90 00003025 */  move  $a2, $zero
/* 097894 80096C94 240700FF */  li    $a3, 255
/* 097898 80096C98 0C0310E1 */  jal   set_text_colour
/* 09789C 80096C9C 0000B025 */   move  $s6, $zero
/* 0978A0 80096CA0 8FAB0078 */  lw    $t3, 0x78($sp)
/* 0978A4 80096CA4 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0978A8 80096CA8 8FA50064 */  lw    $a1, 0x64($sp)
/* 0978AC 80096CAC 8FA6007C */  lw    $a2, 0x7c($sp)
/* 0978B0 80096CB0 240D000C */  li    $t5, 12
/* 0978B4 80096CB4 8D670000 */  lw    $a3, ($t3)
/* 0978B8 80096CB8 AFAD0010 */  sw    $t5, 0x10($sp)
/* 0978BC 80096CBC 0C031110 */  jal   draw_text
/* 0978C0 80096CC0 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 0978C4 80096CC4 240C00FF */  li    $t4, 255
/* 0978C8 80096CC8 AFAC0010 */  sw    $t4, 0x10($sp)
/* 0978CC 80096CCC 240400FF */  li    $a0, 255
/* 0978D0 80096CD0 240500FF */  li    $a1, 255
/* 0978D4 80096CD4 240600C0 */  li    $a2, 192
/* 0978D8 80096CD8 0C0310E1 */  jal   set_text_colour
/* 0978DC 80096CDC 24070060 */   li    $a3, 96
/* 0978E0 80096CE0 8FAE0078 */  lw    $t6, 0x78($sp)
/* 0978E4 80096CE4 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 0978E8 80096CE8 8FA50068 */  lw    $a1, 0x68($sp)
/* 0978EC 80096CEC 8FA60074 */  lw    $a2, 0x74($sp)
/* 0978F0 80096CF0 240F000C */  li    $t7, 12
/* 0978F4 80096CF4 8DC70000 */  lw    $a3, ($t6)
/* 0978F8 80096CF8 AFAF0010 */  sw    $t7, 0x10($sp)
/* 0978FC 80096CFC 0C031110 */  jal   draw_text
/* 097900 80096D00 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 097904 80096D04 3C048012 */  lui   $a0, %hi(sMenuCurrDisplayList) # $a0, 0x8012
/* 097908 80096D08 0C01ECF4 */  jal   reset_render_settings
/* 09790C 80096D0C 248463A0 */   addiu $a0, %lo(sMenuCurrDisplayList) # addiu $a0, $a0, 0x63a0
/* 097910 80096D10 0C01A142 */  jal   func_80068508
/* 097914 80096D14 24040001 */   li    $a0, 1
/* 097918 80096D18 0C01EFC7 */  jal   sprite_opaque
/* 09791C 80096D1C 00002025 */   move  $a0, $zero
/* 097920 80096D20 240200FF */  li    $v0, 255
/* 097924 80096D24 3C01800E */  lui   $at, %hi(sMenuGuiColourR) # $at, 0x800e
/* 097928 80096D28 8FB90070 */  lw    $t9, 0x70($sp)
/* 09792C 80096D2C A022F4A4 */  sb    $v0, %lo(sMenuGuiColourR)($at)
/* 097930 80096D30 3C01800E */  lui   $at, %hi(sMenuGuiColourG) # $at, 0x800e
/* 097934 80096D34 A039F4A8 */  sb    $t9, %lo(sMenuGuiColourG)($at)
/* 097938 80096D38 3C01800E */  lui   $at, %hi(sMenuGuiColourB) # $at, 0x800e
/* 09793C 80096D3C 3C18800E */  lui   $t8, %hi(gNumberOfActivePlayers) # $t8, 0x800e
/* 097940 80096D40 8F18F4BC */  lw    $t8, %lo(gNumberOfActivePlayers)($t8)
/* 097944 80096D44 A022F4AC */  sb    $v0, %lo(sMenuGuiColourB)($at)
/* 097948 80096D48 3C01800E */  lui   $at, %hi(D_800DF4B0) # $at, 0x800e
/* 09794C 80096D4C 1B00006E */  blez  $t8, .L80096F08
/* 097950 80096D50 A022F4B0 */   sb    $v0, %lo(D_800DF4B0)($at)
/* 097954 80096D54 8FAB00A8 */  lw    $t3, 0xa8($sp)
/* 097958 80096D58 240D0078 */  li    $t5, 120
/* 09795C 80096D5C 8FA900A0 */  lw    $t1, 0xa0($sp)
/* 097960 80096D60 01AB6023 */  subu  $t4, $t5, $t3
/* 097964 80096D64 448C9000 */  mtc1  $t4, $f18
/* 097968 80096D68 8FA80084 */  lw    $t0, 0x84($sp)
/* 09796C 80096D6C 00095040 */  sll   $t2, $t1, 1
/* 097970 80096D70 468095A0 */  cvt.s.w $f22, $f18
/* 097974 80096D74 010AA021 */  addu  $s4, $t0, $t2
.L80096D78:
/* 097978 80096D78 9691005C */  lhu   $s1, 0x5c($s4)
/* 09797C 80096D7C 240200FF */  li    $v0, 255
/* 097980 80096D80 2A2103E8 */  slti  $at, $s1, 0x3e8
/* 097984 80096D84 14200002 */  bnez  $at, .L80096D90
/* 097988 80096D88 26B8FF54 */   addiu $t8, $s5, -0xac
/* 09798C 80096D8C 241103E7 */  li    $s1, 999
.L80096D90:
/* 097990 80096D90 0237001A */  div   $zero, $s1, $s7
/* 097994 80096D94 8E790000 */  lw    $t9, ($s3)
/* 097998 80096D98 16E00002 */  bnez  $s7, .L80096DA4
/* 09799C 80096D9C 00000000 */   nop   
/* 0979A0 80096DA0 0007000D */  break 7
.L80096DA4:
/* 0979A4 80096DA4 2401FFFF */  li    $at, -1
/* 0979A8 80096DA8 16E10004 */  bne   $s7, $at, .L80096DBC
/* 0979AC 80096DAC 3C018000 */   lui   $at, 0x8000
/* 0979B0 80096DB0 16210002 */  bne   $s1, $at, .L80096DBC
/* 0979B4 80096DB4 00000000 */   nop   
/* 0979B8 80096DB8 0006000D */  break 6
.L80096DBC:
/* 0979BC 80096DBC E7360010 */  swc1  $f22, 0x10($t9)
/* 0979C0 80096DC0 00001012 */  mflo  $v0
/* 0979C4 80096DC4 00402825 */  move  $a1, $v0
/* 0979C8 80096DC8 00000000 */  nop   
/* 0979CC 80096DCC 00570019 */  multu $v0, $s7
/* 0979D0 80096DD0 00007012 */  mflo  $t6
/* 0979D4 80096DD4 022E8823 */  subu  $s1, $s1, $t6
/* 0979D8 80096DD8 00000000 */  nop   
/* 0979DC 80096DDC 023E001A */  div   $zero, $s1, $fp
/* 0979E0 80096DE0 17C00002 */  bnez  $fp, .L80096DEC
/* 0979E4 80096DE4 00000000 */   nop   
/* 0979E8 80096DE8 0007000D */  break 7
.L80096DEC:
/* 0979EC 80096DEC 2401FFFF */  li    $at, -1
/* 0979F0 80096DF0 17C10004 */  bne   $fp, $at, .L80096E04
/* 0979F4 80096DF4 3C018000 */   lui   $at, 0x8000
/* 0979F8 80096DF8 16210002 */  bne   $s1, $at, .L80096E04
/* 0979FC 80096DFC 00000000 */   nop   
/* 097A00 80096E00 0006000D */  break 6
.L80096E04:
/* 097A04 80096E04 00001812 */  mflo  $v1
/* 097A08 80096E08 00609025 */  move  $s2, $v1
/* 097A0C 80096E0C 00000000 */  nop   
/* 097A10 80096E10 007E0019 */  multu $v1, $fp
/* 097A14 80096E14 00007812 */  mflo  $t7
/* 097A18 80096E18 022F8823 */  subu  $s1, $s1, $t7
/* 097A1C 80096E1C 18A00019 */  blez  $a1, .L80096E84
/* 097A20 80096E20 00000000 */   nop   
/* 097A24 80096E24 44982000 */  mtc1  $t8, $f4
/* 097A28 80096E28 8E690000 */  lw    $t1, ($s3)
/* 097A2C 80096E2C 468021A0 */  cvt.s.w $f6, $f4
/* 097A30 80096E30 00002025 */  move  $a0, $zero
/* 097A34 80096E34 E526000C */  swc1  $f6, 0xc($t1)
/* 097A38 80096E38 8E680000 */  lw    $t0, ($s3)
/* 097A3C 80096E3C 0C027298 */  jal   func_8009CA60
/* 097A40 80096E40 A5050018 */   sh    $a1, 0x18($t0)
/* 097A44 80096E44 8E700000 */  lw    $s0, ($s3)
/* 097A48 80096E48 00002025 */  move  $a0, $zero
/* 097A4C 80096E4C C608000C */  lwc1  $f8, 0xc($s0)
/* 097A50 80096E50 00000000 */  nop   
/* 097A54 80096E54 46144280 */  add.s $f10, $f8, $f20
/* 097A58 80096E58 E60A000C */  swc1  $f10, 0xc($s0)
/* 097A5C 80096E5C 8E6A0000 */  lw    $t2, ($s3)
/* 097A60 80096E60 0C027298 */  jal   func_8009CA60
/* 097A64 80096E64 A5520018 */   sh    $s2, 0x18($t2)
/* 097A68 80096E68 8E700000 */  lw    $s0, ($s3)
/* 097A6C 80096E6C 00000000 */  nop   
/* 097A70 80096E70 C610000C */  lwc1  $f16, 0xc($s0)
/* 097A74 80096E74 00000000 */  nop   
/* 097A78 80096E78 46148480 */  add.s $f18, $f16, $f20
/* 097A7C 80096E7C 10000017 */  b     .L80096EDC
/* 097A80 80096E80 E612000C */   swc1  $f18, 0xc($s0)
.L80096E84:
/* 097A84 80096E84 1A400011 */  blez  $s2, .L80096ECC
/* 097A88 80096E88 26AEFF60 */   addiu $t6, $s5, -0xa0
/* 097A8C 80096E8C 26ADFF5A */  addiu $t5, $s5, -0xa6
/* 097A90 80096E90 448D2000 */  mtc1  $t5, $f4
/* 097A94 80096E94 8E6B0000 */  lw    $t3, ($s3)
/* 097A98 80096E98 468021A0 */  cvt.s.w $f6, $f4
/* 097A9C 80096E9C 00002025 */  move  $a0, $zero
/* 097AA0 80096EA0 E566000C */  swc1  $f6, 0xc($t3)
/* 097AA4 80096EA4 8E6C0000 */  lw    $t4, ($s3)
/* 097AA8 80096EA8 0C027298 */  jal   func_8009CA60
/* 097AAC 80096EAC A5920018 */   sh    $s2, 0x18($t4)
/* 097AB0 80096EB0 8E700000 */  lw    $s0, ($s3)
/* 097AB4 80096EB4 00000000 */  nop   
/* 097AB8 80096EB8 C608000C */  lwc1  $f8, 0xc($s0)
/* 097ABC 80096EBC 00000000 */  nop   
/* 097AC0 80096EC0 46144280 */  add.s $f10, $f8, $f20
/* 097AC4 80096EC4 10000005 */  b     .L80096EDC
/* 097AC8 80096EC8 E60A000C */   swc1  $f10, 0xc($s0)
.L80096ECC:
/* 097ACC 80096ECC 448E8000 */  mtc1  $t6, $f16
/* 097AD0 80096ED0 8E6F0000 */  lw    $t7, ($s3)
/* 097AD4 80096ED4 468084A0 */  cvt.s.w $f18, $f16
/* 097AD8 80096ED8 E5F2000C */  swc1  $f18, 0xc($t7)
.L80096EDC:
/* 097ADC 80096EDC 8E790000 */  lw    $t9, ($s3)
/* 097AE0 80096EE0 00002025 */  move  $a0, $zero
/* 097AE4 80096EE4 0C027298 */  jal   func_8009CA60
/* 097AE8 80096EE8 A7310018 */   sh    $s1, 0x18($t9)
/* 097AEC 80096EEC 3C18800E */  lui   $t8, %hi(gNumberOfActivePlayers) # $t8, 0x800e
/* 097AF0 80096EF0 8F18F4BC */  lw    $t8, %lo(gNumberOfActivePlayers)($t8)
/* 097AF4 80096EF4 26D60001 */  addiu $s6, $s6, 1
/* 097AF8 80096EF8 02D8082A */  slt   $at, $s6, $t8
/* 097AFC 80096EFC 26940018 */  addiu $s4, $s4, 0x18
/* 097B00 80096F00 1420FF9D */  bnez  $at, .L80096D78
/* 097B04 80096F04 26B50040 */   addiu $s5, $s5, 0x40
.L80096F08:
/* 097B08 80096F08 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 097B0C 80096F0C 8FAA007C */  lw    $t2, 0x7c($sp)
/* 097B10 80096F10 8FAB0074 */  lw    $t3, 0x74($sp)
/* 097B14 80096F14 25280011 */  addiu $t0, $t1, 0x11
/* 097B18 80096F18 254D0011 */  addiu $t5, $t2, 0x11
/* 097B1C 80096F1C 256C0011 */  addiu $t4, $t3, 0x11
/* 097B20 80096F20 AFAC0074 */  sw    $t4, 0x74($sp)
/* 097B24 80096F24 AFAD007C */  sw    $t5, 0x7c($sp)
/* 097B28 80096F28 AFA800A8 */  sw    $t0, 0xa8($sp)
/* 097B2C 80096F2C 0C01A142 */  jal   func_80068508
/* 097B30 80096F30 00002025 */   move  $a0, $zero
/* 097B34 80096F34 0C01EFC7 */  jal   sprite_opaque
/* 097B38 80096F38 24040001 */   li    $a0, 1
/* 097B3C 80096F3C 240E00FF */  li    $t6, 255
/* 097B40 80096F40 3C01800E */  lui   $at, %hi(sMenuGuiColourG) # $at, 0x800e
/* 097B44 80096F44 8FAF00A0 */  lw    $t7, 0xa0($sp)
/* 097B48 80096F48 A02EF4A8 */  sb    $t6, %lo(sMenuGuiColourG)($at)
/* 097B4C 80096F4C 8FB80078 */  lw    $t8, 0x78($sp)
/* 097B50 80096F50 8FA80070 */  lw    $t0, 0x70($sp)
/* 097B54 80096F54 3C01800E */  lui   $at, %hi(D_800DF4B0) # $at, 0x800e
/* 097B58 80096F58 A020F4B0 */  sb    $zero, %lo(D_800DF4B0)($at)
/* 097B5C 80096F5C 25F90001 */  addiu $t9, $t7, 1
/* 097B60 80096F60 2B210004 */  slti  $at, $t9, 4
/* 097B64 80096F64 27090004 */  addiu $t1, $t8, 4
/* 097B68 80096F68 250AFFC0 */  addiu $t2, $t0, -0x40
/* 097B6C 80096F6C AFAA0070 */  sw    $t2, 0x70($sp)
/* 097B70 80096F70 AFA90078 */  sw    $t1, 0x78($sp)
/* 097B74 80096F74 1420FF41 */  bnez  $at, .L80096C7C
/* 097B78 80096F78 AFB900A0 */   sw    $t9, 0xa0($sp)
/* 097B7C 80096F7C 3C0D8012 */  lui   $t5, %hi(gMenuOptionCount) # $t5, 0x8012
/* 097B80 80096F80 8DAD63E0 */  lw    $t5, %lo(gMenuOptionCount)($t5)
/* 097B84 80096F84 3C118012 */  lui   $s1, %hi(gResultOptionCount) # $s1, 0x8012
/* 097B88 80096F88 19A000B7 */  blez  $t5, .L80097268
/* 097B8C 80096F8C 26316C14 */   addiu $s1, %lo(gResultOptionCount) # addiu $s1, $s1, 0x6c14
/* 097B90 80096F90 8E2B0000 */  lw    $t3, ($s1)
/* 097B94 80096F94 24040007 */  li    $a0, 7
/* 097B98 80096F98 000B60C0 */  sll   $t4, $t3, 3
/* 097B9C 80096F9C 0C0315B4 */  jal   clear_dialogue_box_open_flag
/* 097BA0 80096FA0 AFAC00A8 */   sw    $t4, 0xa8($sp)
/* 097BA4 80096FA4 0C031525 */  jal   assign_dialogue_box_id
/* 097BA8 80096FA8 24040007 */   li    $a0, 7
/* 097BAC 80096FAC 8FA20098 */  lw    $v0, 0x98($sp)
/* 097BB0 80096FB0 8FAE00A8 */  lw    $t6, 0xa8($sp)
/* 097BB4 80096FB4 24040007 */  li    $a0, 7
/* 097BB8 80096FB8 01C27821 */  addu  $t7, $t6, $v0
/* 097BBC 80096FBC 25F800CC */  addiu $t8, $t7, 0xcc
/* 097BC0 80096FC0 004E3023 */  subu  $a2, $v0, $t6
/* 097BC4 80096FC4 24C600C4 */  addiu $a2, $a2, 0xc4
/* 097BC8 80096FC8 AFB80010 */  sw    $t8, 0x10($sp)
/* 097BCC 80096FCC 24050050 */  li    $a1, 80
/* 097BD0 80096FD0 0C0313B7 */  jal   set_current_dialogue_box_coords
/* 097BD4 80096FD4 240700F0 */   li    $a3, 240
/* 097BD8 80096FD8 24040007 */  li    $a0, 7
/* 097BDC 80096FDC 24050040 */  li    $a1, 64
/* 097BE0 80096FE0 24060040 */  li    $a2, 64
/* 097BE4 80096FE4 240700FF */  li    $a3, 255
/* 097BE8 80096FE8 0C0313EF */  jal   set_current_dialogue_background_colour
/* 097BEC 80096FEC AFA00010 */   sw    $zero, 0x10($sp)
/* 097BF0 80096FF0 24040007 */  li    $a0, 7
/* 097BF4 80096FF4 0C0313DF */  jal   set_dialogue_font
/* 097BF8 80096FF8 00002825 */   move  $a1, $zero
/* 097BFC 80096FFC 24040007 */  li    $a0, 7
/* 097C00 80097000 00002825 */  move  $a1, $zero
/* 097C04 80097004 00003025 */  move  $a2, $zero
/* 097C08 80097008 00003825 */  move  $a3, $zero
/* 097C0C 8009700C 0C031414 */  jal   set_current_text_background_colour
/* 097C10 80097010 AFA00010 */   sw    $zero, 0x10($sp)
/* 097C14 80097014 3C028012 */  lui   $v0, %hi(gOptionBlinkTimer) # $v0, 0x8012
/* 097C18 80097018 8C4263BC */  lw    $v0, %lo(gOptionBlinkTimer)($v0)
/* 097C1C 8009701C 3C10800E */  lui   $s0, %hi(gMenuSubOption) # $s0, 0x800e
/* 097C20 80097020 000248C0 */  sll   $t1, $v0, 3
/* 097C24 80097024 29210100 */  slti  $at, $t1, 0x100
/* 097C28 80097028 14200003 */  bnez  $at, .L80097038
/* 097C2C 8009702C 01201025 */   move  $v0, $t1
/* 097C30 80097030 240801FF */  li    $t0, 511
/* 097C34 80097034 01091023 */  subu  $v0, $t0, $t1
.L80097038:
/* 097C38 80097038 26100988 */  addiu $s0, %lo(gMenuSubOption) # addiu $s0, $s0, 0x988
/* 097C3C 8009703C 8E0A0000 */  lw    $t2, ($s0)
/* 097C40 80097040 8FB900A8 */  lw    $t9, 0xa8($sp)
/* 097C44 80097044 11400055 */  beqz  $t2, .L8009719C
/* 097C48 80097048 0000B025 */   move  $s6, $zero
/* 097C4C 8009704C 3C0B800E */  lui   $t3, %hi(gMenuText) # $t3, 0x800e
/* 097C50 80097050 8D6BF4A0 */  lw    $t3, %lo(gMenuText)($t3)
/* 097C54 80097054 272DFFE8 */  addiu $t5, $t9, -0x18
/* 097C58 80097058 AFAD00A8 */  sw    $t5, 0xa8($sp)
/* 097C5C 8009705C 8D670210 */  lw    $a3, 0x210($t3)
/* 097C60 80097060 240C0001 */  li    $t4, 1
/* 097C64 80097064 240E000C */  li    $t6, 12
/* 097C68 80097068 AFAE0014 */  sw    $t6, 0x14($sp)
/* 097C6C 8009706C AFAC0010 */  sw    $t4, 0x10($sp)
/* 097C70 80097070 AFA200A0 */  sw    $v0, 0xa0($sp)
/* 097C74 80097074 25A60008 */  addiu $a2, $t5, 8
/* 097C78 80097078 24040007 */  li    $a0, 7
/* 097C7C 8009707C 0C03145A */  jal   render_dialogue_text
/* 097C80 80097080 24058000 */   li    $a1, -32768
/* 097C84 80097084 8E0F0000 */  lw    $t7, ($s0)
/* 097C88 80097088 24010001 */  li    $at, 1
/* 097C8C 8009708C 15E1000C */  bne   $t7, $at, .L800970C0
/* 097C90 80097090 24040007 */   li    $a0, 7
/* 097C94 80097094 8FB800A0 */  lw    $t8, 0xa0($sp)
/* 097C98 80097098 240900FF */  li    $t1, 255
/* 097C9C 8009709C AFA90014 */  sw    $t1, 0x14($sp)
/* 097CA0 800970A0 24040007 */  li    $a0, 7
/* 097CA4 800970A4 240500FF */  li    $a1, 255
/* 097CA8 800970A8 240600FF */  li    $a2, 255
/* 097CAC 800970AC 240700FF */  li    $a3, 255
/* 097CB0 800970B0 0C031400 */  jal   set_current_text_colour
/* 097CB4 800970B4 AFB80010 */   sw    $t8, 0x10($sp)
/* 097CB8 800970B8 10000008 */  b     .L800970DC
/* 097CBC 800970BC 00000000 */   nop   
.L800970C0:
/* 097CC0 800970C0 240800FF */  li    $t0, 255
/* 097CC4 800970C4 AFA80014 */  sw    $t0, 0x14($sp)
/* 097CC8 800970C8 240500FF */  li    $a1, 255
/* 097CCC 800970CC 240600FF */  li    $a2, 255
/* 097CD0 800970D0 240700FF */  li    $a3, 255
/* 097CD4 800970D4 0C031400 */  jal   set_current_text_colour
/* 097CD8 800970D8 AFA00010 */   sw    $zero, 0x10($sp)
.L800970DC:
/* 097CDC 800970DC 3C0A800E */  lui   $t2, %hi(gMenuText) # $t2, 0x800e
/* 097CE0 800970E0 8D4AF4A0 */  lw    $t2, %lo(gMenuText)($t2)
/* 097CE4 800970E4 8FA600A8 */  lw    $a2, 0xa8($sp)
/* 097CE8 800970E8 8D470218 */  lw    $a3, 0x218($t2)
/* 097CEC 800970EC 24190001 */  li    $t9, 1
/* 097CF0 800970F0 240D000C */  li    $t5, 12
/* 097CF4 800970F4 AFAD0014 */  sw    $t5, 0x14($sp)
/* 097CF8 800970F8 AFB90010 */  sw    $t9, 0x10($sp)
/* 097CFC 800970FC 24040007 */  li    $a0, 7
/* 097D00 80097100 24058000 */  li    $a1, -32768
/* 097D04 80097104 0C03145A */  jal   render_dialogue_text
/* 097D08 80097108 24C6001A */   addiu $a2, $a2, 0x1a
/* 097D0C 8009710C 8E0B0000 */  lw    $t3, ($s0)
/* 097D10 80097110 24010002 */  li    $at, 2
/* 097D14 80097114 1561000C */  bne   $t3, $at, .L80097148
/* 097D18 80097118 24040007 */   li    $a0, 7
/* 097D1C 8009711C 8FAC00A0 */  lw    $t4, 0xa0($sp)
/* 097D20 80097120 240E00FF */  li    $t6, 255
/* 097D24 80097124 AFAE0014 */  sw    $t6, 0x14($sp)
/* 097D28 80097128 24040007 */  li    $a0, 7
/* 097D2C 8009712C 240500FF */  li    $a1, 255
/* 097D30 80097130 240600FF */  li    $a2, 255
/* 097D34 80097134 240700FF */  li    $a3, 255
/* 097D38 80097138 0C031400 */  jal   set_current_text_colour
/* 097D3C 8009713C AFAC0010 */   sw    $t4, 0x10($sp)
/* 097D40 80097140 10000008 */  b     .L80097164
/* 097D44 80097144 00000000 */   nop   
.L80097148:
/* 097D48 80097148 240F00FF */  li    $t7, 255
/* 097D4C 8009714C AFAF0014 */  sw    $t7, 0x14($sp)
/* 097D50 80097150 240500FF */  li    $a1, 255
/* 097D54 80097154 240600FF */  li    $a2, 255
/* 097D58 80097158 240700FF */  li    $a3, 255
/* 097D5C 8009715C 0C031400 */  jal   set_current_text_colour
/* 097D60 80097160 AFA00010 */   sw    $zero, 0x10($sp)
.L80097164:
/* 097D64 80097164 3C18800E */  lui   $t8, %hi(gMenuText) # $t8, 0x800e
/* 097D68 80097168 8F18F4A0 */  lw    $t8, %lo(gMenuText)($t8)
/* 097D6C 8009716C 8FA600A8 */  lw    $a2, 0xa8($sp)
/* 097D70 80097170 8F070154 */  lw    $a3, 0x154($t8)
/* 097D74 80097174 24090001 */  li    $t1, 1
/* 097D78 80097178 2408000C */  li    $t0, 12
/* 097D7C 8009717C AFA80014 */  sw    $t0, 0x14($sp)
/* 097D80 80097180 AFA90010 */  sw    $t1, 0x10($sp)
/* 097D84 80097184 24040007 */  li    $a0, 7
/* 097D88 80097188 24058000 */  li    $a1, -32768
/* 097D8C 8009718C 0C03145A */  jal   render_dialogue_text
/* 097D90 80097190 24C6002A */   addiu $a2, $a2, 0x2a
/* 097D94 80097194 10000032 */  b     .L80097260
/* 097D98 80097198 00000000 */   nop   
.L8009719C:
/* 097D9C 8009719C 8E390000 */  lw    $t9, ($s1)
/* 097DA0 800971A0 240A000C */  li    $t2, 12
/* 097DA4 800971A4 1B20002E */  blez  $t9, .L80097260
/* 097DA8 800971A8 AFAA00A8 */   sw    $t2, 0xa8($sp)
/* 097DAC 800971AC 3C108012 */  lui   $s0, %hi(gResultOptionText) # $s0, 0x8012
/* 097DB0 800971B0 3C128012 */  lui   $s2, %hi(gMenuOption) # $s2, 0x8012
/* 097DB4 800971B4 26526A68 */  addiu $s2, %lo(gMenuOption) # addiu $s2, $s2, 0x6a68
/* 097DB8 800971B8 26106BF0 */  addiu $s0, %lo(gResultOptionText) # addiu $s0, $s0, 0x6bf0
/* 097DBC 800971BC AFA200A0 */  sw    $v0, 0xa0($sp)
.L800971C0:
/* 097DC0 800971C0 8E4D0000 */  lw    $t5, ($s2)
/* 097DC4 800971C4 8FA200A0 */  lw    $v0, 0xa0($sp)
/* 097DC8 800971C8 16CD000C */  bne   $s6, $t5, .L800971FC
/* 097DCC 800971CC 24040007 */   li    $a0, 7
/* 097DD0 800971D0 240B00FF */  li    $t3, 255
/* 097DD4 800971D4 AFAB0014 */  sw    $t3, 0x14($sp)
/* 097DD8 800971D8 24040007 */  li    $a0, 7
/* 097DDC 800971DC 240500FF */  li    $a1, 255
/* 097DE0 800971E0 240600FF */  li    $a2, 255
/* 097DE4 800971E4 240700FF */  li    $a3, 255
/* 097DE8 800971E8 AFA20010 */  sw    $v0, 0x10($sp)
/* 097DEC 800971EC 0C031400 */  jal   set_current_text_colour
/* 097DF0 800971F0 AFA200A0 */   sw    $v0, 0xa0($sp)
/* 097DF4 800971F4 1000000A */  b     .L80097220
/* 097DF8 800971F8 8FA600A8 */   lw    $a2, 0xa8($sp)
.L800971FC:
/* 097DFC 800971FC 240C00FF */  li    $t4, 255
/* 097E00 80097200 AFAC0014 */  sw    $t4, 0x14($sp)
/* 097E04 80097204 240500FF */  li    $a1, 255
/* 097E08 80097208 240600FF */  li    $a2, 255
/* 097E0C 8009720C 240700FF */  li    $a3, 255
/* 097E10 80097210 AFA00010 */  sw    $zero, 0x10($sp)
/* 097E14 80097214 0C031400 */  jal   set_current_text_colour
/* 097E18 80097218 AFA200A0 */   sw    $v0, 0xa0($sp)
/* 097E1C 8009721C 8FA600A8 */  lw    $a2, 0xa8($sp)
.L80097220:
/* 097E20 80097220 8E070000 */  lw    $a3, ($s0)
/* 097E24 80097224 240E0001 */  li    $t6, 1
/* 097E28 80097228 240F000C */  li    $t7, 12
/* 097E2C 8009722C AFAF0014 */  sw    $t7, 0x14($sp)
/* 097E30 80097230 AFAE0010 */  sw    $t6, 0x10($sp)
/* 097E34 80097234 24040007 */  li    $a0, 7
/* 097E38 80097238 0C03145A */  jal   render_dialogue_text
/* 097E3C 8009723C 24050050 */   li    $a1, 80
/* 097E40 80097240 8E280000 */  lw    $t0, ($s1)
/* 097E44 80097244 8FB800A8 */  lw    $t8, 0xa8($sp)
/* 097E48 80097248 26D60001 */  addiu $s6, $s6, 1
/* 097E4C 8009724C 02C8082A */  slt   $at, $s6, $t0
/* 097E50 80097250 27090010 */  addiu $t1, $t8, 0x10
/* 097E54 80097254 26100004 */  addiu $s0, $s0, 4
/* 097E58 80097258 1420FFD9 */  bnez  $at, .L800971C0
/* 097E5C 8009725C AFA900A8 */   sw    $t1, 0xa8($sp)
.L80097260:
/* 097E60 80097260 0C03157D */  jal   open_dialogue_box
/* 097E64 80097264 24040007 */   li    $a0, 7
.L80097268:
/* 097E68 80097268 8FBF005C */  lw    $ra, 0x5c($sp)
/* 097E6C 8009726C C7B50028 */  lwc1  $f21, 0x28($sp)
/* 097E70 80097270 C7B4002C */  lwc1  $f20, 0x2c($sp)
/* 097E74 80097274 C7B70030 */  lwc1  $f23, 0x30($sp)
/* 097E78 80097278 C7B60034 */  lwc1  $f22, 0x34($sp)
/* 097E7C 8009727C 8FB00038 */  lw    $s0, 0x38($sp)
/* 097E80 80097280 8FB1003C */  lw    $s1, 0x3c($sp)
/* 097E84 80097284 8FB20040 */  lw    $s2, 0x40($sp)
/* 097E88 80097288 8FB30044 */  lw    $s3, 0x44($sp)
/* 097E8C 8009728C 8FB40048 */  lw    $s4, 0x48($sp)
/* 097E90 80097290 8FB5004C */  lw    $s5, 0x4c($sp)
/* 097E94 80097294 8FB60050 */  lw    $s6, 0x50($sp)
/* 097E98 80097298 8FB70054 */  lw    $s7, 0x54($sp)
/* 097E9C 8009729C 8FBE0058 */  lw    $fp, 0x58($sp)
/* 097EA0 800972A0 03E00008 */  jr    $ra
/* 097EA4 800972A4 27BD00B0 */   addiu $sp, $sp, 0xb0

