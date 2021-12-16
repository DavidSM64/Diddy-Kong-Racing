.late_rodata
glabel jpt_800E85E0
.word L8009DC60, L8009DEF0, L8009E37C, L8009E37C, L8009DFB0, L8009DFEC, L8009E098, L8009E194, L8009E23C, L8009E37C, L8009DC60
glabel jpt_800E860C
.word L8009E2D0, L8009E2F4, L8009E354, L8009E354, L8009E314, L8009E354, L8009E314, L8009E2E4, L8009E354, L8009E334

.text
glabel tt_menu_loop
/* 09E73C 8009DB3C 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 09E740 8009DB40 AFBF001C */  sw    $ra, 0x1c($sp)
/* 09E744 8009DB44 0C01BAA4 */  jal   get_settings
/* 09E748 8009DB48 00000000 */   nop   
/* 09E74C 8009DB4C 0C027B20 */  jal   is_in_two_player_adventure
/* 09E750 8009DB50 AFA20030 */   sw    $v0, 0x30($sp)
/* 09E754 8009DB54 10400007 */  beqz  $v0, .L8009DB74
/* 09E758 8009DB58 3C038012 */   lui   $v1, %hi(sCurrentMenuID) # $v1, 0x8012
/* 09E75C 8009DB5C 8FA20030 */  lw    $v0, 0x30($sp)
/* 09E760 8009DB60 00000000 */  nop   
/* 09E764 8009DB64 8C4E0010 */  lw    $t6, 0x10($v0)
/* 09E768 8009DB68 00000000 */  nop   
/* 09E76C 8009DB6C 35CF0002 */  ori   $t7, $t6, 2
/* 09E770 8009DB70 AC4F0010 */  sw    $t7, 0x10($v0)
.L8009DB74:
/* 09E774 8009DB74 8FA20030 */  lw    $v0, 0x30($sp)
/* 09E778 8009DB78 24090005 */  li    $t1, 5
/* 09E77C 8009DB7C 8C580010 */  lw    $t8, 0x10($v0)
/* 09E780 8009DB80 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09E784 8009DB84 33190002 */  andi  $t9, $t8, 2
/* 09E788 8009DB88 17200002 */  bnez  $t9, .L8009DB94
/* 09E78C 8009DB8C 24040001 */   li    $a0, 1
/* 09E790 8009DB90 A02964E2 */  sb    $t1, %lo(sCurrentMenuID)($at)
.L8009DB94:
/* 09E794 8009DB94 806364E2 */  lb    $v1, %lo(sCurrentMenuID)($v1)
/* 09E798 8009DB98 24010004 */  li    $at, 4
/* 09E79C 8009DB9C 10610012 */  beq   $v1, $at, .L8009DBE8
/* 09E7A0 8009DBA0 24050018 */   li    $a1, 24
/* 09E7A4 8009DBA4 24010005 */  li    $at, 5
/* 09E7A8 8009DBA8 1061000F */  beq   $v1, $at, .L8009DBE8
/* 09E7AC 8009DBAC 240A0078 */   li    $t2, 120
/* 09E7B0 8009DBB0 0C006DE0 */  jal   func_8001B780
/* 09E7B4 8009DBB4 AFAA0044 */   sw    $t2, 0x44($sp)
/* 09E7B8 8009DBB8 10400003 */  beqz  $v0, .L8009DBC8
/* 09E7BC 8009DBBC 24040001 */   li    $a0, 1
/* 09E7C0 8009DBC0 240B0088 */  li    $t3, 136
/* 09E7C4 8009DBC4 AFAB0044 */  sw    $t3, 0x44($sp)
.L8009DBC8:
/* 09E7C8 8009DBC8 8FAC0044 */  lw    $t4, 0x44($sp)
/* 09E7CC 8009DBCC 24050018 */  li    $a1, 24
/* 09E7D0 8009DBD0 24060010 */  li    $a2, 16
/* 09E7D4 8009DBD4 240700C0 */  li    $a3, 192
/* 09E7D8 8009DBD8 0C0313B7 */  jal   set_current_dialogue_box_coords
/* 09E7DC 8009DBDC AFAC0010 */   sw    $t4, 0x10($sp)
/* 09E7E0 8009DBE0 10000007 */  b     .L8009DC00
/* 09E7E4 8009DBE4 24040001 */   li    $a0, 1
.L8009DBE8:
/* 09E7E8 8009DBE8 240D00DC */  li    $t5, 220
/* 09E7EC 8009DBEC AFAD0010 */  sw    $t5, 0x10($sp)
/* 09E7F0 8009DBF0 24060010 */  li    $a2, 16
/* 09E7F4 8009DBF4 0C0313B7 */  jal   set_current_dialogue_box_coords
/* 09E7F8 8009DBF8 240700B8 */   li    $a3, 184
/* 09E7FC 8009DBFC 24040001 */  li    $a0, 1
.L8009DC00:
/* 09E800 8009DC00 0C0313DF */  jal   set_dialogue_font
/* 09E804 8009DC04 00002825 */   move  $a1, $zero
/* 09E808 8009DC08 AFA00044 */  sw    $zero, 0x44($sp)
/* 09E80C 8009DC0C 0C01A955 */  jal   get_buttons_pressed_from_player
/* 09E810 8009DC10 00002025 */   move  $a0, $zero
/* 09E814 8009DC14 3C018012 */  lui   $at, %hi(sDialogueOptionMax) # $at, 0x8012
/* 09E818 8009DC18 A0206504 */  sb    $zero, %lo(sDialogueOptionMax)($at)
/* 09E81C 8009DC1C 3C088012 */  lui   $t0, %hi(sCurrentMenuID) # $t0, 0x8012
/* 09E820 8009DC20 3C018012 */  lui   $at, %hi(gDialogOptionYOffset) # $at, 0x8012
/* 09E824 8009DC24 240E0020 */  li    $t6, 32
/* 09E828 8009DC28 250864E2 */  addiu $t0, %lo(sCurrentMenuID) # addiu $t0, $t0, 0x64e2
/* 09E82C 8009DC2C A02E650E */  sb    $t6, %lo(gDialogOptionYOffset)($at)
/* 09E830 8009DC30 81030000 */  lb    $v1, ($t0)
/* 09E834 8009DC34 00402025 */  move  $a0, $v0
/* 09E838 8009DC38 2C61000B */  sltiu $at, $v1, 0xb
/* 09E83C 8009DC3C 102001CF */  beqz  $at, .L8009E37C
/* 09E840 8009DC40 AFA20040 */   sw    $v0, 0x40($sp)
/* 09E844 8009DC44 00037880 */  sll   $t7, $v1, 2
/* 09E848 8009DC48 3C01800F */  lui   $at, %hi(jpt_800E85E0) # $at, 0x800f
/* 09E84C 8009DC4C 002F0821 */  addu  $at, $at, $t7
/* 09E850 8009DC50 8C2F85E0 */  lw    $t7, %lo(jpt_800E85E0)($at)
/* 09E854 8009DC54 00000000 */  nop   
/* 09E858 8009DC58 01E00008 */  jr    $t7
/* 09E85C 8009DC5C 00000000 */   nop   
glabel L8009DC60
/* 09E860 8009DC60 3C18800E */  lui   $t8, %hi(gMenuText) # $t8, 0x800e
/* 09E864 8009DC64 8F18F4A0 */  lw    $t8, %lo(gMenuText)($t8)
/* 09E868 8009DC68 24190001 */  li    $t9, 1
/* 09E86C 8009DC6C 8F070090 */  lw    $a3, 0x90($t8)
/* 09E870 8009DC70 24090004 */  li    $t1, 4
/* 09E874 8009DC74 AFA90014 */  sw    $t1, 0x14($sp)
/* 09E878 8009DC78 AFB90010 */  sw    $t9, 0x10($sp)
/* 09E87C 8009DC7C 24040001 */  li    $a0, 1
/* 09E880 8009DC80 24058000 */  li    $a1, -32768
/* 09E884 8009DC84 0C03145A */  jal   render_dialogue_text
/* 09E888 8009DC88 24060006 */   li    $a2, 6
/* 09E88C 8009DC8C 3C0A800E */  lui   $t2, %hi(gMenuText) # $t2, 0x800e
/* 09E890 8009DC90 8D4AF4A0 */  lw    $t2, %lo(gMenuText)($t2)
/* 09E894 8009DC94 24050014 */  li    $a1, 20
/* 09E898 8009DC98 8D44011C */  lw    $a0, 0x11c($t2)
/* 09E89C 8009DC9C 0C02746E */  jal   render_dialogue_option
/* 09E8A0 8009DCA0 24060003 */   li    $a2, 3
/* 09E8A4 8009DCA4 0C027B20 */  jal   is_in_two_player_adventure
/* 09E8A8 8009DCA8 00000000 */   nop   
/* 09E8AC 8009DCAC 1440001B */  bnez  $v0, .L8009DD1C
/* 09E8B0 8009DCB0 00000000 */   nop   
/* 09E8B4 8009DCB4 0C003932 */  jal   is_time_trial_enabled
/* 09E8B8 8009DCB8 00000000 */   nop   
/* 09E8BC 8009DCBC 10400009 */  beqz  $v0, .L8009DCE4
/* 09E8C0 8009DCC0 3C0C800E */   lui   $t4, %hi(gMenuText) # $t4, 0x800e
/* 09E8C4 8009DCC4 3C0B800E */  lui   $t3, %hi(gMenuText) # $t3, 0x800e
/* 09E8C8 8009DCC8 8D6BF4A0 */  lw    $t3, %lo(gMenuText)($t3)
/* 09E8CC 8009DCCC 24050014 */  li    $a1, 20
/* 09E8D0 8009DCD0 8D640104 */  lw    $a0, 0x104($t3)
/* 09E8D4 8009DCD4 0C02746E */  jal   render_dialogue_option
/* 09E8D8 8009DCD8 00003025 */   move  $a2, $zero
/* 09E8DC 8009DCDC 10000006 */  b     .L8009DCF8
/* 09E8E0 8009DCE0 00000000 */   nop   
.L8009DCE4:
/* 09E8E4 8009DCE4 8D8CF4A0 */  lw    $t4, %lo(gMenuText)($t4)
/* 09E8E8 8009DCE8 24050014 */  li    $a1, 20
/* 09E8EC 8009DCEC 8D840108 */  lw    $a0, 0x108($t4)
/* 09E8F0 8009DCF0 0C02746E */  jal   render_dialogue_option
/* 09E8F4 8009DCF4 00003025 */   move  $a2, $zero
.L8009DCF8:
/* 09E8F8 8009DCF8 0C006DE0 */  jal   func_8001B780
/* 09E8FC 8009DCFC 00000000 */   nop   
/* 09E900 8009DD00 10400006 */  beqz  $v0, .L8009DD1C
/* 09E904 8009DD04 3C0D800E */   lui   $t5, %hi(gMenuText) # $t5, 0x800e
/* 09E908 8009DD08 8DADF4A0 */  lw    $t5, %lo(gMenuText)($t5)
/* 09E90C 8009DD0C 24050014 */  li    $a1, 20
/* 09E910 8009DD10 8DA4006C */  lw    $a0, 0x6c($t5)
/* 09E914 8009DD14 0C02746E */  jal   render_dialogue_option
/* 09E918 8009DD18 24060001 */   li    $a2, 1
.L8009DD1C:
/* 09E91C 8009DD1C 3C0E800E */  lui   $t6, %hi(gMenuText) # $t6, 0x800e
/* 09E920 8009DD20 8DCEF4A0 */  lw    $t6, %lo(gMenuText)($t6)
/* 09E924 8009DD24 24050014 */  li    $a1, 20
/* 09E928 8009DD28 8DC40014 */  lw    $a0, 0x14($t6)
/* 09E92C 8009DD2C 0C02746E */  jal   render_dialogue_option
/* 09E930 8009DD30 24060002 */   li    $a2, 2
/* 09E934 8009DD34 0C02749B */  jal   handle_menu_joystick_input
/* 09E938 8009DD38 00000000 */   nop   
/* 09E93C 8009DD3C 3C0F8012 */  lui   $t7, %hi(D_80126516) # $t7, 0x8012
/* 09E940 8009DD40 81EF6516 */  lb    $t7, %lo(D_80126516)($t7)
/* 09E944 8009DD44 3C028012 */  lui   $v0, %hi(gControllersXAxisDirection) # $v0, 0x8012
/* 09E948 8009DD48 15E0001B */  bnez  $t7, .L8009DDB8
/* 09E94C 8009DD4C 8FB80040 */   lw    $t8, 0x40($sp)
/* 09E950 8009DD50 8042645C */  lb    $v0, %lo(gControllersXAxisDirection)($v0)
/* 09E954 8009DD54 00000000 */  nop   
/* 09E958 8009DD58 1840000B */  blez  $v0, .L8009DD88
/* 09E95C 8009DD5C 00000000 */   nop   
/* 09E960 8009DD60 0C003932 */  jal   is_time_trial_enabled
/* 09E964 8009DD64 00000000 */   nop   
/* 09E968 8009DD68 14400003 */  bnez  $v0, .L8009DD78
/* 09E96C 8009DD6C 24040231 */   li    $a0, 561
/* 09E970 8009DD70 0C00DAF3 */  jal   func_80036BCC
/* 09E974 8009DD74 24050001 */   li    $a1, 1
.L8009DD78:
/* 09E978 8009DD78 0C00392F */  jal   set_time_trial_enabled
/* 09E97C 8009DD7C 24040001 */   li    $a0, 1
/* 09E980 8009DD80 1000000D */  b     .L8009DDB8
/* 09E984 8009DD84 8FB80040 */   lw    $t8, 0x40($sp)
.L8009DD88:
/* 09E988 8009DD88 0441000B */  bgez  $v0, .L8009DDB8
/* 09E98C 8009DD8C 8FB80040 */   lw    $t8, 0x40($sp)
/* 09E990 8009DD90 0C003932 */  jal   is_time_trial_enabled
/* 09E994 8009DD94 00000000 */   nop   
/* 09E998 8009DD98 24010001 */  li    $at, 1
/* 09E99C 8009DD9C 14410003 */  bne   $v0, $at, .L8009DDAC
/* 09E9A0 8009DDA0 24040230 */   li    $a0, 560
/* 09E9A4 8009DDA4 0C00DAF3 */  jal   func_80036BCC
/* 09E9A8 8009DDA8 24050001 */   li    $a1, 1
.L8009DDAC:
/* 09E9AC 8009DDAC 0C00392F */  jal   set_time_trial_enabled
/* 09E9B0 8009DDB0 00002025 */   move  $a0, $zero
/* 09E9B4 8009DDB4 8FB80040 */  lw    $t8, 0x40($sp)
.L8009DDB8:
/* 09E9B8 8009DDB8 8FAE0040 */  lw    $t6, 0x40($sp)
/* 09E9BC 8009DDBC 33198000 */  andi  $t9, $t8, 0x8000
/* 09E9C0 8009DDC0 13200032 */  beqz  $t9, .L8009DE8C
/* 09E9C4 8009DDC4 3C098012 */   lui   $t1, %hi(sCurrentMenuID) # $t1, 0x8012
/* 09E9C8 8009DDC8 812964E2 */  lb    $t1, %lo(sCurrentMenuID)($t1)
/* 09E9CC 8009DDCC 2401000A */  li    $at, 10
/* 09E9D0 8009DDD0 1121002E */  beq   $t1, $at, .L8009DE8C
/* 09E9D4 8009DDD4 3C038012 */   lui   $v1, %hi(D_80126516) # $v1, 0x8012
/* 09E9D8 8009DDD8 80636516 */  lb    $v1, %lo(D_80126516)($v1)
/* 09E9DC 8009DDDC 24010001 */  li    $at, 1
/* 09E9E0 8009DDE0 10610006 */  beq   $v1, $at, .L8009DDFC
/* 09E9E4 8009DDE4 240400EF */   li    $a0, 239
/* 09E9E8 8009DDE8 24010003 */  li    $at, 3
/* 09E9EC 8009DDEC 10610011 */  beq   $v1, $at, .L8009DE34
/* 09E9F0 8009DDF0 240400EF */   li    $a0, 239
/* 09E9F4 8009DDF4 10000023 */  b     .L8009DE84
/* 09E9F8 8009DDF8 246D0001 */   addiu $t5, $v1, 1
.L8009DDFC:
/* 09E9FC 8009DDFC 0C000741 */  jal   func_80001D04
/* 09EA00 8009DE00 00002825 */   move  $a1, $zero
/* 09EA04 8009DE04 3C048012 */  lui   $a0, %hi(D_80126398) # $a0, 0x8012
/* 09EA08 8009DE08 24846398 */  addiu $a0, %lo(D_80126398) # addiu $a0, $a0, 0x6398
/* 09EA0C 8009DE0C AC800000 */  sw    $zero, ($a0)
/* 09EA10 8009DE10 3C018012 */  lui   $at, %hi(D_8012639C) # $at, 0x8012
/* 09EA14 8009DE14 AC20639C */  sw    $zero, %lo(D_8012639C)($at)
/* 09EA18 8009DE18 3C038012 */  lui   $v1, %hi(D_80126516) # $v1, 0x8012
/* 09EA1C 8009DE1C 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09EA20 8009DE20 240A0008 */  li    $t2, 8
/* 09EA24 8009DE24 80636516 */  lb    $v1, %lo(D_80126516)($v1)
/* 09EA28 8009DE28 10000015 */  b     .L8009DE80
/* 09EA2C 8009DE2C A02A64E2 */   sb    $t2, %lo(sCurrentMenuID)($at)
/* 09EA30 8009DE30 240400EF */  li    $a0, 239
.L8009DE34:
/* 09EA34 8009DE34 0C000741 */  jal   func_80001D04
/* 09EA38 8009DE38 00002825 */   move  $a1, $zero
/* 09EA3C 8009DE3C 2404022E */  li    $a0, 558
/* 09EA40 8009DE40 0C00DAF3 */  jal   func_80036BCC
/* 09EA44 8009DE44 24050001 */   li    $a1, 1
/* 09EA48 8009DE48 3C04800E */  lui   $a0, %hi(D_800E1E2C) # $a0, 0x800e
/* 09EA4C 8009DE4C 0C02719D */  jal   func_8009C674
/* 09EA50 8009DE50 24841E2C */   addiu $a0, %lo(D_800E1E2C) # addiu $a0, $a0, 0x1e2c
/* 09EA54 8009DE54 3C04800E */  lui   $a0, %hi(D_800E1E40) # $a0, 0x800e
/* 09EA58 8009DE58 0C027229 */  jal   allocate_menu_images
/* 09EA5C 8009DE5C 24841E40 */   addiu $a0, %lo(D_800E1E40) # addiu $a0, $a0, 0x1e40
/* 09EA60 8009DE60 240B0001 */  li    $t3, 1
/* 09EA64 8009DE64 3C01800E */  lui   $at, %hi(D_800E1E28) # $at, 0x800e
/* 09EA68 8009DE68 A02B1E28 */  sb    $t3, %lo(D_800E1E28)($at)
/* 09EA6C 8009DE6C 3C038012 */  lui   $v1, %hi(D_80126516) # $v1, 0x8012
/* 09EA70 8009DE70 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09EA74 8009DE74 240C0004 */  li    $t4, 4
/* 09EA78 8009DE78 80636516 */  lb    $v1, %lo(D_80126516)($v1)
/* 09EA7C 8009DE7C A02C64E2 */  sb    $t4, %lo(sCurrentMenuID)($at)
.L8009DE80:
/* 09EA80 8009DE80 246D0001 */  addiu $t5, $v1, 1
.L8009DE84:
/* 09EA84 8009DE84 10000008 */  b     .L8009DEA8
/* 09EA88 8009DE88 AFAD0044 */   sw    $t5, 0x44($sp)
.L8009DE8C:
/* 09EA8C 8009DE8C 31CF4000 */  andi  $t7, $t6, 0x4000
/* 09EA90 8009DE90 11E00005 */  beqz  $t7, .L8009DEA8
/* 09EA94 8009DE94 24040241 */   li    $a0, 577
/* 09EA98 8009DE98 0C000741 */  jal   func_80001D04
/* 09EA9C 8009DE9C 00002825 */   move  $a1, $zero
/* 09EAA0 8009DEA0 24180003 */  li    $t8, 3
/* 09EAA4 8009DEA4 AFB80044 */  sw    $t8, 0x44($sp)
.L8009DEA8:
/* 09EAA8 8009DEA8 3C038012 */  lui   $v1, %hi(sCurrentMenuID)
/* 09EAAC 8009DEAC 806364E2 */  lb    $v1, %lo(sCurrentMenuID)($v1)
/* 09EAB0 8009DEB0 24010004 */  li    $at, 4
/* 09EAB4 8009DEB4 14610002 */  bne   $v1, $at, .L8009DEC0
/* 09EAB8 8009DEB8 2409000A */   li    $t1, 10
/* 09EABC 8009DEBC AFA00044 */  sw    $zero, 0x44($sp)
.L8009DEC0:
/* 09EAC0 8009DEC0 8FB90044 */  lw    $t9, 0x44($sp)
/* 09EAC4 8009DEC4 24010003 */  li    $at, 3
/* 09EAC8 8009DEC8 17210004 */  bne   $t9, $at, .L8009DEDC
/* 09EACC 8009DECC 240A0003 */   li    $t2, 3
/* 09EAD0 8009DED0 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09EAD4 8009DED4 A02964E2 */  sb    $t1, %lo(sCurrentMenuID)($at)
/* 09EAD8 8009DED8 2403000A */  li    $v1, 10
.L8009DEDC:
/* 09EADC 8009DEDC 2401000A */  li    $at, 10
/* 09EAE0 8009DEE0 14610127 */  bne   $v1, $at, .L8009E380
/* 09EAE4 8009DEE4 24010001 */   li    $at, 1
/* 09EAE8 8009DEE8 10000124 */  b     .L8009E37C
/* 09EAEC 8009DEEC AFAA0044 */   sw    $t2, 0x44($sp)
glabel L8009DEF0
/* 09EAF0 8009DEF0 3C048012 */  lui   $a0, %hi(D_801263A4) # $a0, 0x8012
/* 09EAF4 8009DEF4 8C8463A4 */  lw    $a0, %lo(D_801263A4)($a0)
/* 09EAF8 8009DEF8 00001825 */  move  $v1, $zero
/* 09EAFC 8009DEFC 8C850000 */  lw    $a1, ($a0)
/* 09EB00 8009DF00 240E003A */  li    $t6, 58
/* 09EB04 8009DF04 10A00005 */  beqz  $a1, .L8009DF1C
/* 09EB08 8009DF08 00801025 */   move  $v0, $a0
.L8009DF0C:
/* 09EB0C 8009DF0C 8C4B0004 */  lw    $t3, 4($v0)
/* 09EB10 8009DF10 24630001 */  addiu $v1, $v1, 1
/* 09EB14 8009DF14 1560FFFD */  bnez  $t3, .L8009DF0C
/* 09EB18 8009DF18 24420004 */   addiu $v0, $v0, 4
.L8009DF1C:
/* 09EB1C 8009DF1C 1860001B */  blez  $v1, .L8009DF8C
/* 09EB20 8009DF20 246CFFFF */   addiu $t4, $v1, -1
/* 09EB24 8009DF24 000C68C0 */  sll   $t5, $t4, 3
/* 09EB28 8009DF28 10A00018 */  beqz  $a1, .L8009DF8C
/* 09EB2C 8009DF2C 01CD3023 */   subu  $a2, $t6, $t5
/* 09EB30 8009DF30 8C870000 */  lw    $a3, ($a0)
/* 09EB34 8009DF34 00001825 */  move  $v1, $zero
/* 09EB38 8009DF38 240F0001 */  li    $t7, 1
.L8009DF3C:
/* 09EB3C 8009DF3C 24180004 */  li    $t8, 4
/* 09EB40 8009DF40 AFB80014 */  sw    $t8, 0x14($sp)
/* 09EB44 8009DF44 AFAF0010 */  sw    $t7, 0x10($sp)
/* 09EB48 8009DF48 24040001 */  li    $a0, 1
/* 09EB4C 8009DF4C 24058000 */  li    $a1, -32768
/* 09EB50 8009DF50 AFA30024 */  sw    $v1, 0x24($sp)
/* 09EB54 8009DF54 0C03145A */  jal   render_dialogue_text
/* 09EB58 8009DF58 AFA60038 */   sw    $a2, 0x38($sp)
/* 09EB5C 8009DF5C 8FA30024 */  lw    $v1, 0x24($sp)
/* 09EB60 8009DF60 3C198012 */  lui   $t9, %hi(D_801263A4) # $t9, 0x8012
/* 09EB64 8009DF64 8F3963A4 */  lw    $t9, %lo(D_801263A4)($t9)
/* 09EB68 8009DF68 24630004 */  addiu $v1, $v1, 4
/* 09EB6C 8009DF6C 03234821 */  addu  $t1, $t9, $v1
/* 09EB70 8009DF70 8FA60038 */  lw    $a2, 0x38($sp)
/* 09EB74 8009DF74 8D270000 */  lw    $a3, ($t1)
/* 09EB78 8009DF78 24C60010 */  addiu $a2, $a2, 0x10
/* 09EB7C 8009DF7C 14E0FFEF */  bnez  $a3, .L8009DF3C
/* 09EB80 8009DF80 240F0001 */   li    $t7, 1
/* 09EB84 8009DF84 3C088012 */  lui   $t0, %hi(sCurrentMenuID) # $t0, 0x8012
/* 09EB88 8009DF88 250864E2 */  addiu $t0, %lo(sCurrentMenuID) # addiu $t0, $t0, 0x64e2
.L8009DF8C:
/* 09EB8C 8009DF8C 8FAA0040 */  lw    $t2, 0x40($sp)
/* 09EB90 8009DF90 3C038012 */  lui   $v1, %hi(sCurrentMenuID) # $v1, 0x8012
/* 09EB94 8009DF94 314BC000 */  andi  $t3, $t2, 0xc000
/* 09EB98 8009DF98 11600002 */  beqz  $t3, .L8009DFA4
/* 09EB9C 8009DF9C 00000000 */   nop   
/* 09EBA0 8009DFA0 A1000000 */  sb    $zero, ($t0)
.L8009DFA4:
/* 09EBA4 8009DFA4 806364E2 */  lb    $v1, %lo(sCurrentMenuID)($v1)
/* 09EBA8 8009DFA8 100000F5 */  b     .L8009E380
/* 09EBAC 8009DFAC 24010001 */   li    $at, 1
glabel L8009DFB0
/* 09EBB0 8009DFB0 308CC000 */  andi  $t4, $a0, 0xc000
/* 09EBB4 8009DFB4 118000F1 */  beqz  $t4, .L8009E37C
/* 09EBB8 8009DFB8 3C01800E */   lui   $at, %hi(D_800E1E28) # $at, 0x800e
/* 09EBBC 8009DFBC A1000000 */  sb    $zero, ($t0)
/* 09EBC0 8009DFC0 3C04800E */  lui   $a0, %hi(D_800E1E2C) # $a0, 0x800e
/* 09EBC4 8009DFC4 A0201E28 */  sb    $zero, %lo(D_800E1E28)($at)
/* 09EBC8 8009DFC8 0C02712A */  jal   func_8009C4A8
/* 09EBCC 8009DFCC 24841E2C */   addiu $a0, %lo(D_800E1E2C) # addiu $a0, $a0, 0x1e2c
/* 09EBD0 8009DFD0 2404022F */  li    $a0, 559
/* 09EBD4 8009DFD4 0C00DAF3 */  jal   func_80036BCC
/* 09EBD8 8009DFD8 24050001 */   li    $a1, 1
/* 09EBDC 8009DFDC 3C038012 */  lui   $v1, %hi(sCurrentMenuID) # $v1, 0x8012
/* 09EBE0 8009DFE0 806364E2 */  lb    $v1, %lo(sCurrentMenuID)($v1)
/* 09EBE4 8009DFE4 100000E6 */  b     .L8009E380
/* 09EBE8 8009DFE8 24010001 */   li    $at, 1
glabel L8009DFEC
/* 09EBEC 8009DFEC 3C02800E */  lui   $v0, %hi(gMenuText) # $v0, 0x800e
/* 09EBF0 8009DFF0 8C42F4A0 */  lw    $v0, %lo(gMenuText)($v0)
/* 09EBF4 8009DFF4 240300D0 */  li    $v1, 208
/* 09EBF8 8009DFF8 8C4E00D0 */  lw    $t6, 0xd0($v0)
/* 09EBFC 8009DFFC 00000000 */  nop   
/* 09EC00 8009E000 11C00019 */  beqz  $t6, .L8009E068
/* 09EC04 8009E004 8FA90040 */   lw    $t1, 0x40($sp)
/* 09EC08 8009E008 8C4700D0 */  lw    $a3, 0xd0($v0)
/* 09EC0C 8009E00C 24060006 */  li    $a2, 6
/* 09EC10 8009E010 240D0001 */  li    $t5, 1
.L8009E014:
/* 09EC14 8009E014 240F0004 */  li    $t7, 4
/* 09EC18 8009E018 AFAF0014 */  sw    $t7, 0x14($sp)
/* 09EC1C 8009E01C AFAD0010 */  sw    $t5, 0x10($sp)
/* 09EC20 8009E020 24040001 */  li    $a0, 1
/* 09EC24 8009E024 24058000 */  li    $a1, -32768
/* 09EC28 8009E028 AFA30024 */  sw    $v1, 0x24($sp)
/* 09EC2C 8009E02C 0C03145A */  jal   render_dialogue_text
/* 09EC30 8009E030 AFA60020 */   sw    $a2, 0x20($sp)
/* 09EC34 8009E034 8FA30024 */  lw    $v1, 0x24($sp)
/* 09EC38 8009E038 3C18800E */  lui   $t8, %hi(gMenuText) # $t8, 0x800e
/* 09EC3C 8009E03C 8F18F4A0 */  lw    $t8, %lo(gMenuText)($t8)
/* 09EC40 8009E040 24630004 */  addiu $v1, $v1, 4
/* 09EC44 8009E044 0303C821 */  addu  $t9, $t8, $v1
/* 09EC48 8009E048 8FA60020 */  lw    $a2, 0x20($sp)
/* 09EC4C 8009E04C 8F270000 */  lw    $a3, ($t9)
/* 09EC50 8009E050 24C60010 */  addiu $a2, $a2, 0x10
/* 09EC54 8009E054 14E0FFEF */  bnez  $a3, .L8009E014
/* 09EC58 8009E058 240D0001 */   li    $t5, 1
/* 09EC5C 8009E05C 3C088012 */  lui   $t0, %hi(sCurrentMenuID) # $t0, 0x8012
/* 09EC60 8009E060 250864E2 */  addiu $t0, %lo(sCurrentMenuID) # addiu $t0, $t0, 0x64e2
/* 09EC64 8009E064 8FA90040 */  lw    $t1, 0x40($sp)
.L8009E068:
/* 09EC68 8009E068 8FAB0030 */  lw    $t3, 0x30($sp)
/* 09EC6C 8009E06C 312AC000 */  andi  $t2, $t1, 0xc000
/* 09EC70 8009E070 11400006 */  beqz  $t2, .L8009E08C
/* 09EC74 8009E074 3C038012 */   lui   $v1, %hi(sCurrentMenuID) # $v1, 0x8012
/* 09EC78 8009E078 8D6C0010 */  lw    $t4, 0x10($t3)
/* 09EC7C 8009E07C 00000000 */  nop   
/* 09EC80 8009E080 358E0002 */  ori   $t6, $t4, 2
/* 09EC84 8009E084 AD6E0010 */  sw    $t6, 0x10($t3)
/* 09EC88 8009E088 A1000000 */  sb    $zero, ($t0)
.L8009E08C:
/* 09EC8C 8009E08C 806364E2 */  lb    $v1, %lo(sCurrentMenuID)($v1)
/* 09EC90 8009E090 100000BB */  b     .L8009E380
/* 09EC94 8009E094 24010001 */   li    $at, 1
glabel L8009E098
/* 09EC98 8009E098 3C0D800E */  lui   $t5, %hi(gMenuText) # $t5, 0x800e
/* 09EC9C 8009E09C 8DADF4A0 */  lw    $t5, %lo(gMenuText)($t5)
/* 09ECA0 8009E0A0 240F0001 */  li    $t7, 1
/* 09ECA4 8009E0A4 8DA7027C */  lw    $a3, 0x27c($t5)
/* 09ECA8 8009E0A8 24180004 */  li    $t8, 4
/* 09ECAC 8009E0AC AFB80014 */  sw    $t8, 0x14($sp)
/* 09ECB0 8009E0B0 AFAF0010 */  sw    $t7, 0x10($sp)
/* 09ECB4 8009E0B4 24040001 */  li    $a0, 1
/* 09ECB8 8009E0B8 24058000 */  li    $a1, -32768
/* 09ECBC 8009E0BC 0C03145A */  jal   render_dialogue_text
/* 09ECC0 8009E0C0 24060022 */   li    $a2, 34
/* 09ECC4 8009E0C4 3C19800E */  lui   $t9, %hi(gMenuText) # $t9, 0x800e
/* 09ECC8 8009E0C8 8F39F4A0 */  lw    $t9, %lo(gMenuText)($t9)
/* 09ECCC 8009E0CC 24090001 */  li    $t1, 1
/* 09ECD0 8009E0D0 8F270280 */  lw    $a3, 0x280($t9)
/* 09ECD4 8009E0D4 240A0004 */  li    $t2, 4
/* 09ECD8 8009E0D8 AFAA0014 */  sw    $t2, 0x14($sp)
/* 09ECDC 8009E0DC AFA90010 */  sw    $t1, 0x10($sp)
/* 09ECE0 8009E0E0 24040001 */  li    $a0, 1
/* 09ECE4 8009E0E4 24058000 */  li    $a1, -32768
/* 09ECE8 8009E0E8 0C03145A */  jal   render_dialogue_text
/* 09ECEC 8009E0EC 24060032 */   li    $a2, 50
/* 09ECF0 8009E0F0 3C0C800E */  lui   $t4, %hi(gMenuText) # $t4, 0x800e
/* 09ECF4 8009E0F4 8D8CF4A0 */  lw    $t4, %lo(gMenuText)($t4)
/* 09ECF8 8009E0F8 240E0001 */  li    $t6, 1
/* 09ECFC 8009E0FC 8D870288 */  lw    $a3, 0x288($t4)
/* 09ED00 8009E100 240B0004 */  li    $t3, 4
/* 09ED04 8009E104 AFAB0014 */  sw    $t3, 0x14($sp)
/* 09ED08 8009E108 AFAE0010 */  sw    $t6, 0x10($sp)
/* 09ED0C 8009E10C 24040001 */  li    $a0, 1
/* 09ED10 8009E110 24058000 */  li    $a1, -32768
/* 09ED14 8009E114 0C03145A */  jal   render_dialogue_text
/* 09ED18 8009E118 24060042 */   li    $a2, 66
/* 09ED1C 8009E11C 8FAD0040 */  lw    $t5, 0x40($sp)
/* 09ED20 8009E120 240400EF */  li    $a0, 239
/* 09ED24 8009E124 31AF9000 */  andi  $t7, $t5, 0x9000
/* 09ED28 8009E128 11E0000E */  beqz  $t7, .L8009E164
/* 09ED2C 8009E12C 8FA90040 */   lw    $t1, 0x40($sp)
/* 09ED30 8009E130 0C000741 */  jal   func_80001D04
/* 09ED34 8009E134 00002825 */   move  $a1, $zero
/* 09ED38 8009E138 3C048012 */  lui   $a0, %hi(D_80126398) # $a0, 0x8012
/* 09ED3C 8009E13C 24846398 */  addiu $a0, %lo(D_80126398) # addiu $a0, $a0, 0x6398
/* 09ED40 8009E140 AC800000 */  sw    $zero, ($a0)
/* 09ED44 8009E144 24180007 */  li    $t8, 7
/* 09ED48 8009E148 3C018012 */  lui   $at, %hi(D_8012639C) # $at, 0x8012
/* 09ED4C 8009E14C AC38639C */  sw    $t8, %lo(D_8012639C)($at)
/* 09ED50 8009E150 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09ED54 8009E154 24190008 */  li    $t9, 8
/* 09ED58 8009E158 1000000A */  b     .L8009E184
/* 09ED5C 8009E15C A03964E2 */   sb    $t9, %lo(sCurrentMenuID)($at)
/* 09ED60 8009E160 8FA90040 */  lw    $t1, 0x40($sp)
.L8009E164:
/* 09ED64 8009E164 00000000 */  nop   
/* 09ED68 8009E168 312A4000 */  andi  $t2, $t1, 0x4000
/* 09ED6C 8009E16C 11400005 */  beqz  $t2, .L8009E184
/* 09ED70 8009E170 24040241 */   li    $a0, 577
/* 09ED74 8009E174 0C000741 */  jal   func_80001D04
/* 09ED78 8009E178 00002825 */   move  $a1, $zero
/* 09ED7C 8009E17C 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09ED80 8009E180 A02064E2 */  sb    $zero, %lo(sCurrentMenuID)($at)
.L8009E184:
/* 09ED84 8009E184 3C038012 */  lui   $v1, %hi(sCurrentMenuID) # $v1, 0x8012
/* 09ED88 8009E188 806364E2 */  lb    $v1, %lo(sCurrentMenuID)($v1)
/* 09ED8C 8009E18C 1000007C */  b     .L8009E380
/* 09ED90 8009E190 24010001 */   li    $at, 1
glabel L8009E194
/* 09ED94 8009E194 3C0C800E */  lui   $t4, %hi(gMenuText) # $t4, 0x800e
/* 09ED98 8009E198 8D8CF4A0 */  lw    $t4, %lo(gMenuText)($t4)
/* 09ED9C 8009E19C 240E0001 */  li    $t6, 1
/* 09EDA0 8009E1A0 8D87027C */  lw    $a3, 0x27c($t4)
/* 09EDA4 8009E1A4 240B0004 */  li    $t3, 4
/* 09EDA8 8009E1A8 AFAB0014 */  sw    $t3, 0x14($sp)
/* 09EDAC 8009E1AC AFAE0010 */  sw    $t6, 0x10($sp)
/* 09EDB0 8009E1B0 24040001 */  li    $a0, 1
/* 09EDB4 8009E1B4 24058000 */  li    $a1, -32768
/* 09EDB8 8009E1B8 0C03145A */  jal   render_dialogue_text
/* 09EDBC 8009E1BC 24060022 */   li    $a2, 34
/* 09EDC0 8009E1C0 3C0D800E */  lui   $t5, %hi(gMenuText) # $t5, 0x800e
/* 09EDC4 8009E1C4 8DADF4A0 */  lw    $t5, %lo(gMenuText)($t5)
/* 09EDC8 8009E1C8 240F0001 */  li    $t7, 1
/* 09EDCC 8009E1CC 8DA70284 */  lw    $a3, 0x284($t5)
/* 09EDD0 8009E1D0 24180004 */  li    $t8, 4
/* 09EDD4 8009E1D4 AFB80014 */  sw    $t8, 0x14($sp)
/* 09EDD8 8009E1D8 AFAF0010 */  sw    $t7, 0x10($sp)
/* 09EDDC 8009E1DC 24040001 */  li    $a0, 1
/* 09EDE0 8009E1E0 24058000 */  li    $a1, -32768
/* 09EDE4 8009E1E4 0C03145A */  jal   render_dialogue_text
/* 09EDE8 8009E1E8 24060032 */   li    $a2, 50
/* 09EDEC 8009E1EC 3C19800E */  lui   $t9, %hi(gMenuText) # $t9, 0x800e
/* 09EDF0 8009E1F0 8F39F4A0 */  lw    $t9, %lo(gMenuText)($t9)
/* 09EDF4 8009E1F4 24090001 */  li    $t1, 1
/* 09EDF8 8009E1F8 8F270288 */  lw    $a3, 0x288($t9)
/* 09EDFC 8009E1FC 240A0004 */  li    $t2, 4
/* 09EE00 8009E200 AFAA0014 */  sw    $t2, 0x14($sp)
/* 09EE04 8009E204 AFA90010 */  sw    $t1, 0x10($sp)
/* 09EE08 8009E208 24040001 */  li    $a0, 1
/* 09EE0C 8009E20C 24058000 */  li    $a1, -32768
/* 09EE10 8009E210 0C03145A */  jal   render_dialogue_text
/* 09EE14 8009E214 24060042 */   li    $a2, 66
/* 09EE18 8009E218 8FAC0040 */  lw    $t4, 0x40($sp)
/* 09EE1C 8009E21C 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09EE20 8009E220 318ED000 */  andi  $t6, $t4, 0xd000
/* 09EE24 8009E224 11C00002 */  beqz  $t6, .L8009E230
/* 09EE28 8009E228 3C038012 */   lui   $v1, %hi(sCurrentMenuID) # $v1, 0x8012
/* 09EE2C 8009E22C A02064E2 */  sb    $zero, %lo(sCurrentMenuID)($at)
.L8009E230:
/* 09EE30 8009E230 806364E2 */  lb    $v1, %lo(sCurrentMenuID)($v1)
/* 09EE34 8009E234 10000052 */  b     .L8009E380
/* 09EE38 8009E238 24010001 */   li    $at, 1
glabel L8009E23C
/* 09EE3C 8009E23C 3C0B800E */  lui   $t3, %hi(gMenuText) # $t3, 0x800e
/* 09EE40 8009E240 8D6BF4A0 */  lw    $t3, %lo(gMenuText)($t3)
/* 09EE44 8009E244 240D0001 */  li    $t5, 1
/* 09EE48 8009E248 8D6701F0 */  lw    $a3, 0x1f0($t3)
/* 09EE4C 8009E24C 240F0004 */  li    $t7, 4
/* 09EE50 8009E250 AFAF0014 */  sw    $t7, 0x14($sp)
/* 09EE54 8009E254 AFAD0010 */  sw    $t5, 0x10($sp)
/* 09EE58 8009E258 24040001 */  li    $a0, 1
/* 09EE5C 8009E25C 24058000 */  li    $a1, -32768
/* 09EE60 8009E260 0C03145A */  jal   render_dialogue_text
/* 09EE64 8009E264 24060032 */   li    $a2, 50
/* 09EE68 8009E268 3C048012 */  lui   $a0, %hi(D_80126398) # $a0, 0x8012
/* 09EE6C 8009E26C 24846398 */  addiu $a0, %lo(D_80126398) # addiu $a0, $a0, 0x6398
/* 09EE70 8009E270 8C980000 */  lw    $t8, ($a0)
/* 09EE74 8009E274 00000000 */  nop   
/* 09EE78 8009E278 27190001 */  addiu $t9, $t8, 1
/* 09EE7C 8009E27C 2B210005 */  slti  $at, $t9, 5
/* 09EE80 8009E280 1420003B */  bnez  $at, .L8009E370
/* 09EE84 8009E284 AC990000 */   sw    $t9, ($a0)
/* 09EE88 8009E288 0C006DCE */  jal   func_8001B738
/* 09EE8C 8009E28C 00002025 */   move  $a0, $zero
/* 09EE90 8009E290 304300FF */  andi  $v1, $v0, 0xff
/* 09EE94 8009E294 24010005 */  li    $at, 5
/* 09EE98 8009E298 14610005 */  bne   $v1, $at, .L8009E2B0
/* 09EE9C 8009E29C 2C61000A */   sltiu $at, $v1, 0xa
/* 09EEA0 8009E2A0 0C006DCE */  jal   func_8001B738
/* 09EEA4 8009E2A4 00002025 */   move  $a0, $zero
/* 09EEA8 8009E2A8 304300FF */  andi  $v1, $v0, 0xff
/* 09EEAC 8009E2AC 2C61000A */  sltiu $at, $v1, 0xa
.L8009E2B0:
/* 09EEB0 8009E2B0 10200028 */  beqz  $at, .L8009E354
/* 09EEB4 8009E2B4 00035080 */   sll   $t2, $v1, 2
/* 09EEB8 8009E2B8 3C01800F */  lui   $at, %hi(jpt_800E860C) # $at, 0x800f
/* 09EEBC 8009E2BC 002A0821 */  addu  $at, $at, $t2
/* 09EEC0 8009E2C0 8C2A860C */  lw    $t2, %lo(jpt_800E860C)($at)
/* 09EEC4 8009E2C4 00000000 */  nop   
/* 09EEC8 8009E2C8 01400008 */  jr    $t2
/* 09EECC 8009E2CC 00000000 */   nop   
glabel L8009E2D0
/* 09EED0 8009E2D0 3C0C8012 */  lui   $t4, %hi(D_8012639C) # $t4, 0x8012
/* 09EED4 8009E2D4 8D8C639C */  lw    $t4, %lo(D_8012639C)($t4)
/* 09EED8 8009E2D8 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09EEDC 8009E2DC 10000024 */  b     .L8009E370
/* 09EEE0 8009E2E0 A02C64E2 */   sb    $t4, %lo(sCurrentMenuID)($at)
glabel L8009E2E4
/* 09EEE4 8009E2E4 240E0006 */  li    $t6, 6
/* 09EEE8 8009E2E8 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09EEEC 8009E2EC 10000020 */  b     .L8009E370
/* 09EEF0 8009E2F0 A02E64E2 */   sb    $t6, %lo(sCurrentMenuID)($at)
glabel L8009E2F4
/* 09EEF4 8009E2F4 3C0B800E */  lui   $t3, %hi(D_800E09D8) # $t3, 0x800e
/* 09EEF8 8009E2F8 256B09D8 */  addiu $t3, %lo(D_800E09D8) # addiu $t3, $t3, 0x9d8
/* 09EEFC 8009E2FC 3C018012 */  lui   $at, %hi(D_801263A4) # $at, 0x8012
/* 09EF00 8009E300 AC2B63A4 */  sw    $t3, %lo(D_801263A4)($at)
/* 09EF04 8009E304 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09EF08 8009E308 240D0001 */  li    $t5, 1
/* 09EF0C 8009E30C 10000018 */  b     .L8009E370
/* 09EF10 8009E310 A02D64E2 */   sb    $t5, %lo(sCurrentMenuID)($at)
glabel L8009E314
/* 09EF14 8009E314 3C0F800E */  lui   $t7, %hi(D_800E09C4) # $t7, 0x800e
/* 09EF18 8009E318 25EF09C4 */  addiu $t7, %lo(D_800E09C4) # addiu $t7, $t7, 0x9c4
/* 09EF1C 8009E31C 3C018012 */  lui   $at, %hi(D_801263A4) # $at, 0x8012
/* 09EF20 8009E320 AC2F63A4 */  sw    $t7, %lo(D_801263A4)($at)
/* 09EF24 8009E324 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09EF28 8009E328 24180001 */  li    $t8, 1
/* 09EF2C 8009E32C 10000010 */  b     .L8009E370
/* 09EF30 8009E330 A03864E2 */   sb    $t8, %lo(sCurrentMenuID)($at)
glabel L8009E334
/* 09EF34 8009E334 3C19800E */  lui   $t9, %hi(D_800E09EC) # $t9, 0x800e
/* 09EF38 8009E338 273909EC */  addiu $t9, %lo(D_800E09EC) # addiu $t9, $t9, 0x9ec
/* 09EF3C 8009E33C 3C018012 */  lui   $at, %hi(D_801263A4) # $at, 0x8012
/* 09EF40 8009E340 AC3963A4 */  sw    $t9, %lo(D_801263A4)($at)
/* 09EF44 8009E344 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09EF48 8009E348 24090001 */  li    $t1, 1
/* 09EF4C 8009E34C 10000008 */  b     .L8009E370
/* 09EF50 8009E350 A02964E2 */   sb    $t1, %lo(sCurrentMenuID)($at)
.L8009E354:
glabel L8009E354
/* 09EF54 8009E354 3C0A800E */  lui   $t2, %hi(D_800E09B0) # $t2, 0x800e
/* 09EF58 8009E358 254A09B0 */  addiu $t2, %lo(D_800E09B0) # addiu $t2, $t2, 0x9b0
/* 09EF5C 8009E35C 3C018012 */  lui   $at, %hi(D_801263A4) # $at, 0x8012
/* 09EF60 8009E360 AC2A63A4 */  sw    $t2, %lo(D_801263A4)($at)
/* 09EF64 8009E364 3C018012 */  lui   $at, %hi(sCurrentMenuID) # $at, 0x8012
/* 09EF68 8009E368 240C0001 */  li    $t4, 1
/* 09EF6C 8009E36C A02C64E2 */  sb    $t4, %lo(sCurrentMenuID)($at)
.L8009E370:
/* 09EF70 8009E370 3C038012 */  lui   $v1, %hi(sCurrentMenuID) # $v1, 0x8012
/* 09EF74 8009E374 806364E2 */  lb    $v1, %lo(sCurrentMenuID)($v1)
/* 09EF78 8009E378 00000000 */  nop   
.L8009E37C:
glabel L8009E37C
/* 09EF7C 8009E37C 24010001 */  li    $at, 1
.L8009E380:
/* 09EF80 8009E380 10610005 */  beq   $v1, $at, .L8009E398
/* 09EF84 8009E384 24040001 */   li    $a0, 1
/* 09EF88 8009E388 24010002 */  li    $at, 2
/* 09EF8C 8009E38C 10610002 */  beq   $v1, $at, .L8009E398
/* 09EF90 8009E390 24010003 */   li    $at, 3
/* 09EF94 8009E394 1461000A */  bne   $v1, $at, .L8009E3C0
.L8009E398:
/* 09EF98 8009E398 3C0E800E */   lui   $t6, %hi(gMenuText) # $t6, 0x800e
/* 09EF9C 8009E39C 8DCEF4A0 */  lw    $t6, %lo(gMenuText)($t6)
/* 09EFA0 8009E3A0 240B0001 */  li    $t3, 1
/* 09EFA4 8009E3A4 8DC70100 */  lw    $a3, 0x100($t6)
/* 09EFA8 8009E3A8 240D0004 */  li    $t5, 4
/* 09EFAC 8009E3AC AFAD0014 */  sw    $t5, 0x14($sp)
/* 09EFB0 8009E3B0 AFAB0010 */  sw    $t3, 0x10($sp)
/* 09EFB4 8009E3B4 24058000 */  li    $a1, -32768
/* 09EFB8 8009E3B8 0C03145A */  jal   render_dialogue_text
/* 09EFBC 8009E3BC 24060006 */   li    $a2, 6
.L8009E3C0:
/* 09EFC0 8009E3C0 8FBF001C */  lw    $ra, 0x1c($sp)
/* 09EFC4 8009E3C4 8FA20044 */  lw    $v0, 0x44($sp)
/* 09EFC8 8009E3C8 03E00008 */  jr    $ra
/* 09EFCC 8009E3CC 27BD0048 */   addiu $sp, $sp, 0x48

