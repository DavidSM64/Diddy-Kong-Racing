glabel menu_track_select_init
/* 08F3A0 8008E7A0 27BDFF80 */  addiu $sp, $sp, -0x80
/* 08F3A4 8008E7A4 AFBF0044 */  sw    $ra, 0x44($sp)
/* 08F3A8 8008E7A8 AFBE0040 */  sw    $fp, 0x40($sp)
/* 08F3AC 8008E7AC AFB7003C */  sw    $s7, 0x3c($sp)
/* 08F3B0 8008E7B0 AFB60038 */  sw    $s6, 0x38($sp)
/* 08F3B4 8008E7B4 AFB50034 */  sw    $s5, 0x34($sp)
/* 08F3B8 8008E7B8 AFB40030 */  sw    $s4, 0x30($sp)
/* 08F3BC 8008E7BC AFB3002C */  sw    $s3, 0x2c($sp)
/* 08F3C0 8008E7C0 AFB20028 */  sw    $s2, 0x28($sp)
/* 08F3C4 8008E7C4 AFB10024 */  sw    $s1, 0x24($sp)
/* 08F3C8 8008E7C8 AFB00020 */  sw    $s0, 0x20($sp)
/* 08F3CC 8008E7CC 0C03105C */  jal   load_font
/* 08F3D0 8008E7D0 24040002 */   li    $a0, 2
/* 08F3D4 8008E7D4 0C01BAA4 */  jal   get_settings
/* 08F3D8 8008E7D8 00000000 */   nop   
/* 08F3DC 8008E7DC 0040A025 */  move  $s4, $v0
/* 08F3E0 8008E7E0 27A4007C */  addiu $a0, $sp, 0x7c
/* 08F3E4 8008E7E4 0C01AC89 */  jal   get_number_of_levels_and_worlds
/* 08F3E8 8008E7E8 27A50078 */   addiu $a1, $sp, 0x78
/* 08F3EC 8008E7EC 0C0078A7 */  jal   get_misc_asset
/* 08F3F0 8008E7F0 2404001A */   li    $a0, 26
/* 08F3F4 8008E7F4 3C03800E */  lui   $v1, %hi(gTitleScreenLoaded) # $v1, 0x800e
/* 08F3F8 8008E7F8 2463F488 */  addiu $v1, %lo(gTitleScreenLoaded) # addiu $v1, $v1, -0xb78
/* 08F3FC 8008E7FC 8C6E0000 */  lw    $t6, ($v1)
/* 08F400 8008E800 0040B825 */  move  $s7, $v0
/* 08F404 8008E804 11C00009 */  beqz  $t6, .L8008E82C
/* 08F408 8008E808 3C018012 */   lui   $at, %hi(D_801269C8) # $at, 0x8012
/* 08F40C 8008E80C AC2069C8 */  sw    $zero, %lo(D_801269C8)($at)
/* 08F410 8008E810 3C018012 */  lui   $at, %hi(D_801269CC) # $at, 0x8012
/* 08F414 8008E814 AC2069CC */  sw    $zero, %lo(D_801269CC)($at)
/* 08F418 8008E818 3C01800E */  lui   $at, %hi(gTracksMenuTimeTrialHighlightIndex) # $at, 0x800e
/* 08F41C 8008E81C AC200414 */  sw    $zero, %lo(gTracksMenuTimeTrialHighlightIndex)($at)
/* 08F420 8008E820 3C01800E */  lui   $at, %hi(gTracksMenuAdventureHighlightIndex) # $at, 0x800e
/* 08F424 8008E824 AC200418 */  sw    $zero, %lo(gTracksMenuAdventureHighlightIndex)($at)
/* 08F428 8008E828 AC600000 */  sw    $zero, ($v1)
.L8008E82C:
/* 08F42C 8008E82C 0C01E948 */  jal   get_video_width_and_height_as_s32
/* 08F430 8008E830 00000000 */   nop   
/* 08F434 8008E834 3C068012 */  lui   $a2, %hi(gTrackSelectViewPortX) # $a2, 0x8012
/* 08F438 8008E838 24C6647C */  addiu $a2, %lo(gTrackSelectViewPortX) # addiu $a2, $a2, 0x647c
/* 08F43C 8008E83C 3C078012 */  lui   $a3, %hi(gTrackSelectViewportY) # $a3, 0x8012
/* 08F440 8008E840 00027C03 */  sra   $t7, $v0, 0x10
/* 08F444 8008E844 3059FFFF */  andi  $t9, $v0, 0xffff
/* 08F448 8008E848 24E76480 */  addiu $a3, %lo(gTrackSelectViewportY) # addiu $a3, $a3, 0x6480
/* 08F44C 8008E84C ACC20000 */  sw    $v0, ($a2)
/* 08F450 8008E850 31F8FFFF */  andi  $t8, $t7, 0xffff
/* 08F454 8008E854 ACF80000 */  sw    $t8, ($a3)
/* 08F458 8008E858 ACD90000 */  sw    $t9, ($a2)
/* 08F45C 8008E85C 00195043 */  sra   $t2, $t9, 1
/* 08F460 8008E860 3C018012 */  lui   $at, %hi(gTrackSelectViewPortHalfX) # $at, 0x8012
/* 08F464 8008E864 AC2A6474 */  sw    $t2, %lo(gTrackSelectViewPortHalfX)($at)
/* 08F468 8008E868 8CE50000 */  lw    $a1, ($a3)
/* 08F46C 8008E86C 3C1E8012 */  lui   $fp, %hi(gTrackSelectViewPortHalfY) # $fp, 0x8012
/* 08F470 8008E870 27DE6478 */  addiu $fp, %lo(gTrackSelectViewPortHalfY) # addiu $fp, $fp, 0x6478
/* 08F474 8008E874 00055843 */  sra   $t3, $a1, 1
/* 08F478 8008E878 AFCB0000 */  sw    $t3, ($fp)
/* 08F47C 8008E87C 3C0C8012 */  lui   $t4, %hi(D_801269C8) # $t4, 0x8012
/* 08F480 8008E880 8D8C69C8 */  lw    $t4, %lo(D_801269C8)($t4)
/* 08F484 8008E884 3C0D8012 */  lui   $t5, %hi(D_801269CC) # $t5, 0x8012
/* 08F488 8008E888 448C2000 */  mtc1  $t4, $f4
/* 08F48C 8008E88C 8DAD69CC */  lw    $t5, %lo(D_801269CC)($t5)
/* 08F490 8008E890 468021A0 */  cvt.s.w $f6, $f4
/* 08F494 8008E894 3C0143A0 */  li    $at, 0x43A00000 # 320.000000
/* 08F498 8008E898 44814000 */  mtc1  $at, $f8
/* 08F49C 8008E89C 00057023 */  negu  $t6, $a1
/* 08F4A0 8008E8A0 448E2000 */  mtc1  $t6, $f4
/* 08F4A4 8008E8A4 448D8000 */  mtc1  $t5, $f16
/* 08F4A8 8008E8A8 46083282 */  mul.s $f10, $f6, $f8
/* 08F4AC 8008E8AC 3C018012 */  lui   $at, %hi(gTrackSelectX) # $at, 0x8012
/* 08F4B0 8008E8B0 2415FFFF */  li    $s5, -1
/* 08F4B4 8008E8B4 240F0020 */  li    $t7, 32
/* 08F4B8 8008E8B8 468021A0 */  cvt.s.w $f6, $f4
/* 08F4BC 8008E8BC E42A69DC */  swc1  $f10, %lo(gTrackSelectX)($at)
/* 08F4C0 8008E8C0 3C018012 */  lui   $at, %hi(gTrackSelectY) # $at, 0x8012
/* 08F4C4 8008E8C4 468084A0 */  cvt.s.w $f18, $f16
/* 08F4C8 8008E8C8 00002025 */  move  $a0, $zero
/* 08F4CC 8008E8CC 46069202 */  mul.s $f8, $f18, $f6
/* 08F4D0 8008E8D0 E42869E4 */  swc1  $f8, %lo(gTrackSelectY)($at)
/* 08F4D4 8008E8D4 3C018012 */  lui   $at, %hi(gSelectedTrackX) # $at, 0x8012
/* 08F4D8 8008E8D8 AC3569F4 */  sw    $s5, %lo(gSelectedTrackX)($at)
/* 08F4DC 8008E8DC 3C018012 */  lui   $at, %hi(gSelectedTrackY) # $at, 0x8012
/* 08F4E0 8008E8E0 AC3569F8 */  sw    $s5, %lo(gSelectedTrackY)($at)
/* 08F4E4 8008E8E4 3C018012 */  lui   $at, %hi(D_801263D0) # $at, 0x8012
/* 08F4E8 8008E8E8 AC3563D0 */  sw    $s5, %lo(D_801263D0)($at)
/* 08F4EC 8008E8EC 3C018012 */  lui   $at, %hi(gOpacityDecayTimer) # $at, 0x8012
/* 08F4F0 8008E8F0 AC2F63D8 */  sw    $t7, %lo(gOpacityDecayTimer)($at)
/* 08F4F4 8008E8F4 3C018012 */  lui   $at, %hi(gOptionBlinkTimer) # $at, 0x8012
/* 08F4F8 8008E8F8 AC2063BC */  sw    $zero, %lo(gOptionBlinkTimer)($at)
/* 08F4FC 8008E8FC 3C018012 */  lui   $at, %hi(D_801267D0) # $at, 0x8012
/* 08F500 8008E900 0C023C03 */  jal   func_8008F00C
/* 08F504 8008E904 AC3567D0 */   sw    $s5, %lo(D_801267D0)($at)
/* 08F508 8008E908 3C04800E */  lui   $a0, %hi(sMenuTransitionFadeOut) # $a0, 0x800e
/* 08F50C 8008E90C 0C030076 */  jal   transition_begin
/* 08F510 8008E910 2484F77C */   addiu $a0, %lo(sMenuTransitionFadeOut) # addiu $a0, $a0, -0x884
/* 08F514 8008E914 0C03005C */  jal   enable_new_screen_transitions
/* 08F518 8008E918 00000000 */   nop   
/* 08F51C 8008E91C 24040032 */  li    $a0, 50
/* 08F520 8008E920 24050069 */  li    $a1, 105
/* 08F524 8008E924 0C01DED7 */  jal   set_background_fill_colour
/* 08F528 8008E928 240600DF */   li    $a2, 223
/* 08F52C 8008E92C 3C11800E */  lui   $s1, %hi(gTracksMenuBgTextureIndices) # $s1, 0x800e
/* 08F530 8008E930 3C168012 */  lui   $s6, %hi(gMenuObjects) # $s6, 0x8012
/* 08F534 8008E934 3C12800E */  lui   $s2, %hi(gTracksMenuBgTextures) # $s2, 0x800e
/* 08F538 8008E938 26520730 */  addiu $s2, %lo(gTracksMenuBgTextures) # addiu $s2, $s2, 0x730
/* 08F53C 8008E93C 26D66550 */  addiu $s6, %lo(gMenuObjects) # addiu $s6, $s6, 0x6550
/* 08F540 8008E940 26310710 */  addiu $s1, %lo(gTracksMenuBgTextureIndices) # addiu $s1, $s1, 0x710
/* 08F544 8008E944 00002825 */  move  $a1, $zero
.L8008E948:
/* 08F548 8008E948 86240000 */  lh    $a0, ($s1)
/* 08F54C 8008E94C 000570C0 */  sll   $t6, $a1, 3
/* 08F550 8008E950 12A4000C */  beq   $s5, $a0, .L8008E984
/* 08F554 8008E954 024E8021 */   addu  $s0, $s2, $t6
/* 08F558 8008E958 0C0271B5 */  jal   func_8009C6D4
/* 08F55C 8008E95C AFA50074 */   sw    $a1, 0x74($sp)
/* 08F560 8008E960 86290000 */  lh    $t1, ($s1)
/* 08F564 8008E964 8FA50074 */  lw    $a1, 0x74($sp)
/* 08F568 8008E968 00095080 */  sll   $t2, $t1, 2
/* 08F56C 8008E96C 02CA5821 */  addu  $t3, $s6, $t2
/* 08F570 8008E970 8D6C0000 */  lw    $t4, ($t3)
/* 08F574 8008E974 0005C8C0 */  sll   $t9, $a1, 3
/* 08F578 8008E978 02598021 */  addu  $s0, $s2, $t9
/* 08F57C 8008E97C 10000002 */  b     .L8008E988
/* 08F580 8008E980 AE0C0000 */   sw    $t4, ($s0)
.L8008E984:
/* 08F584 8008E984 AE000000 */  sw    $zero, ($s0)
.L8008E988:
/* 08F588 8008E988 86240002 */  lh    $a0, 2($s1)
/* 08F58C 8008E98C 00000000 */  nop   
/* 08F590 8008E990 12A4000A */  beq   $s5, $a0, .L8008E9BC
/* 08F594 8008E994 00000000 */   nop   
/* 08F598 8008E998 0C0271B5 */  jal   func_8009C6D4
/* 08F59C 8008E99C AFA50074 */   sw    $a1, 0x74($sp)
/* 08F5A0 8008E9A0 862F0002 */  lh    $t7, 2($s1)
/* 08F5A4 8008E9A4 8FA50074 */  lw    $a1, 0x74($sp)
/* 08F5A8 8008E9A8 000FC080 */  sll   $t8, $t7, 2
/* 08F5AC 8008E9AC 02D8C821 */  addu  $t9, $s6, $t8
/* 08F5B0 8008E9B0 8F290000 */  lw    $t1, ($t9)
/* 08F5B4 8008E9B4 10000002 */  b     .L8008E9C0
/* 08F5B8 8008E9B8 AE090004 */   sw    $t1, 4($s0)
.L8008E9BC:
/* 08F5BC 8008E9BC AE000004 */  sw    $zero, 4($s0)
.L8008E9C0:
/* 08F5C0 8008E9C0 24A50001 */  addiu $a1, $a1, 1
/* 08F5C4 8008E9C4 24010005 */  li    $at, 5
/* 08F5C8 8008E9C8 14A1FFDF */  bne   $a1, $at, .L8008E948
/* 08F5CC 8008E9CC 26310006 */   addiu $s1, $s1, 6
/* 08F5D0 8008E9D0 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 08F5D4 8008E9D4 34A500FF */  ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 08F5D8 8008E9D8 0C01C327 */  jal   allocate_from_main_pool_safe
/* 08F5DC 8008E9DC 24040B40 */   li    $a0, 2880
/* 08F5E0 8008E9E0 3C05800E */  lui   $a1, %hi(gTrackSelectBgTriangles) # $a1, 0x800e
/* 08F5E4 8008E9E4 24A50970 */  addiu $a1, %lo(gTrackSelectBgTriangles) # addiu $a1, $a1, 0x970
/* 08F5E8 8008E9E8 ACA20000 */  sw    $v0, ($a1)
/* 08F5EC 8008E9EC 244B0280 */  addiu $t3, $v0, 0x280
/* 08F5F0 8008E9F0 3C01800E */  lui   $at, %hi(gTrackSelectBgTriangles+4) # $at, 0x800e
/* 08F5F4 8008E9F4 AC2B0974 */  sw    $t3, %lo(gTrackSelectBgTriangles+4)($at)
/* 08F5F8 8008E9F8 8CAC0004 */  lw    $t4, 4($a1)
/* 08F5FC 8008E9FC 3C01800E */  lui   $at, %hi(gTrackSelectBgVertices+4) # $at, 0x800e
/* 08F600 8008EA00 258D0280 */  addiu $t5, $t4, 0x280
/* 08F604 8008EA04 AC2D0968 */  sw    $t5, %lo(gTrackSelectBgVertices)($at)
/* 08F608 8008EA08 3C0E800E */  lui   $t6, %hi(gTrackSelectBgVertices) # $t6, 0x800e
/* 08F60C 8008EA0C 8DCE0968 */  lw    $t6, %lo(gTrackSelectBgVertices)($t6)
/* 08F610 8008EA10 3C03800E */  lui   $v1, %hi(gTrackSelectBgVertices) # $v1, 0x800e
/* 08F614 8008EA14 3C08800E */  lui   $t0, %hi(gTrackSelectBgTriangles) # $t0, 0x800e
/* 08F618 8008EA18 25CF0320 */  addiu $t7, $t6, 0x320
/* 08F61C 8008EA1C AC2F096C */  sw    $t7, %lo(gTrackSelectBgVertices+4)($at)
/* 08F620 8008EA20 2404FF60 */  li    $a0, -160
/* 08F624 8008EA24 25080970 */  addiu $t0, %lo(gTrackSelectBgTriangles) # addiu $t0, $t0, 0x970
/* 08F628 8008EA28 24630968 */  addiu $v1, %lo(gTrackSelectBgVertices) # addiu $v1, $v1, 0x968
/* 08F62C 8008EA2C 240500FF */  li    $a1, 255
/* 08F630 8008EA30 24070320 */  li    $a3, 800
/* 08F634 8008EA34 2406FC00 */  li    $a2, -1024
/* 08F638 8008EA38 00001025 */  move  $v0, $zero
.L8008EA3C:
/* 08F63C 8008EA3C 8C780000 */  lw    $t8, ($v1)
/* 08F640 8008EA40 00000000 */  nop   
/* 08F644 8008EA44 0302C821 */  addu  $t9, $t8, $v0
/* 08F648 8008EA48 A7240000 */  sh    $a0, ($t9)
/* 08F64C 8008EA4C 8C690000 */  lw    $t1, ($v1)
/* 08F650 8008EA50 00042023 */  negu  $a0, $a0
/* 08F654 8008EA54 01225021 */  addu  $t2, $t1, $v0
/* 08F658 8008EA58 A5460004 */  sh    $a2, 4($t2)
/* 08F65C 8008EA5C 8C6B0000 */  lw    $t3, ($v1)
/* 08F660 8008EA60 00000000 */  nop   
/* 08F664 8008EA64 01626021 */  addu  $t4, $t3, $v0
/* 08F668 8008EA68 A1850006 */  sb    $a1, 6($t4)
/* 08F66C 8008EA6C 8C6D0000 */  lw    $t5, ($v1)
/* 08F670 8008EA70 00000000 */  nop   
/* 08F674 8008EA74 01A27021 */  addu  $t6, $t5, $v0
/* 08F678 8008EA78 A1C50007 */  sb    $a1, 7($t6)
/* 08F67C 8008EA7C 8C6F0000 */  lw    $t7, ($v1)
/* 08F680 8008EA80 00000000 */  nop   
/* 08F684 8008EA84 01E2C021 */  addu  $t8, $t7, $v0
/* 08F688 8008EA88 A3050008 */  sb    $a1, 8($t8)
/* 08F68C 8008EA8C 8C790000 */  lw    $t9, ($v1)
/* 08F690 8008EA90 00000000 */  nop   
/* 08F694 8008EA94 03224821 */  addu  $t1, $t9, $v0
/* 08F698 8008EA98 A524000A */  sh    $a0, 0xa($t1)
/* 08F69C 8008EA9C 8C6A0000 */  lw    $t2, ($v1)
/* 08F6A0 8008EAA0 00042023 */  negu  $a0, $a0
/* 08F6A4 8008EAA4 01425821 */  addu  $t3, $t2, $v0
/* 08F6A8 8008EAA8 A566000E */  sh    $a2, 0xe($t3)
/* 08F6AC 8008EAAC 8C6C0000 */  lw    $t4, ($v1)
/* 08F6B0 8008EAB0 00000000 */  nop   
/* 08F6B4 8008EAB4 01826821 */  addu  $t5, $t4, $v0
/* 08F6B8 8008EAB8 A1A50010 */  sb    $a1, 0x10($t5)
/* 08F6BC 8008EABC 8C6E0000 */  lw    $t6, ($v1)
/* 08F6C0 8008EAC0 00000000 */  nop   
/* 08F6C4 8008EAC4 01C27821 */  addu  $t7, $t6, $v0
/* 08F6C8 8008EAC8 A1E50011 */  sb    $a1, 0x11($t7)
/* 08F6CC 8008EACC 8C780000 */  lw    $t8, ($v1)
/* 08F6D0 8008EAD0 00000000 */  nop   
/* 08F6D4 8008EAD4 0302C821 */  addu  $t9, $t8, $v0
/* 08F6D8 8008EAD8 A3250012 */  sb    $a1, 0x12($t9)
/* 08F6DC 8008EADC 8C690000 */  lw    $t1, ($v1)
/* 08F6E0 8008EAE0 00000000 */  nop   
/* 08F6E4 8008EAE4 01225021 */  addu  $t2, $t1, $v0
/* 08F6E8 8008EAE8 A5440014 */  sh    $a0, 0x14($t2)
/* 08F6EC 8008EAEC 8C6B0000 */  lw    $t3, ($v1)
/* 08F6F0 8008EAF0 00042023 */  negu  $a0, $a0
/* 08F6F4 8008EAF4 01626021 */  addu  $t4, $t3, $v0
/* 08F6F8 8008EAF8 A5860018 */  sh    $a2, 0x18($t4)
/* 08F6FC 8008EAFC 8C6D0000 */  lw    $t5, ($v1)
/* 08F700 8008EB00 00000000 */  nop   
/* 08F704 8008EB04 01A27021 */  addu  $t6, $t5, $v0
/* 08F708 8008EB08 A1C5001A */  sb    $a1, 0x1a($t6)
/* 08F70C 8008EB0C 8C6F0000 */  lw    $t7, ($v1)
/* 08F710 8008EB10 00000000 */  nop   
/* 08F714 8008EB14 01E2C021 */  addu  $t8, $t7, $v0
/* 08F718 8008EB18 A305001B */  sb    $a1, 0x1b($t8)
/* 08F71C 8008EB1C 8C790000 */  lw    $t9, ($v1)
/* 08F720 8008EB20 00000000 */  nop   
/* 08F724 8008EB24 03224821 */  addu  $t1, $t9, $v0
/* 08F728 8008EB28 A125001C */  sb    $a1, 0x1c($t1)
/* 08F72C 8008EB2C 8C6A0000 */  lw    $t2, ($v1)
/* 08F730 8008EB30 00000000 */  nop   
/* 08F734 8008EB34 01425821 */  addu  $t3, $t2, $v0
/* 08F738 8008EB38 A564001E */  sh    $a0, 0x1e($t3)
/* 08F73C 8008EB3C 8C6C0000 */  lw    $t4, ($v1)
/* 08F740 8008EB40 00042023 */  negu  $a0, $a0
/* 08F744 8008EB44 01826821 */  addu  $t5, $t4, $v0
/* 08F748 8008EB48 A5A60022 */  sh    $a2, 0x22($t5)
/* 08F74C 8008EB4C 8C6E0000 */  lw    $t6, ($v1)
/* 08F750 8008EB50 00000000 */  nop   
/* 08F754 8008EB54 01C27821 */  addu  $t7, $t6, $v0
/* 08F758 8008EB58 A1E50024 */  sb    $a1, 0x24($t7)
/* 08F75C 8008EB5C 8C780000 */  lw    $t8, ($v1)
/* 08F760 8008EB60 00000000 */  nop   
/* 08F764 8008EB64 0302C821 */  addu  $t9, $t8, $v0
/* 08F768 8008EB68 A3250025 */  sb    $a1, 0x25($t9)
/* 08F76C 8008EB6C 8C690000 */  lw    $t1, ($v1)
/* 08F770 8008EB70 00000000 */  nop   
/* 08F774 8008EB74 01225021 */  addu  $t2, $t1, $v0
/* 08F778 8008EB78 24420028 */  addiu $v0, $v0, 0x28
/* 08F77C 8008EB7C 1447FFAF */  bne   $v0, $a3, .L8008EA3C
/* 08F780 8008EB80 A1450026 */   sb    $a1, 0x26($t2)
/* 08F784 8008EB84 24630004 */  addiu $v1, $v1, 4
/* 08F788 8008EB88 0068082B */  sltu  $at, $v1, $t0
/* 08F78C 8008EB8C 1420FFAB */  bnez  $at, .L8008EA3C
/* 08F790 8008EB90 00001025 */   move  $v0, $zero
/* 08F794 8008EB94 3C03800E */  lui   $v1, %hi(gTrackSelectBgTriangles) # $v1, 0x800e
/* 08F798 8008EB98 3C08800E */  lui   $t0, %hi(gQMarkPtr) # $t0, 0x800e
/* 08F79C 8008EB9C 25080978 */  addiu $t0, %lo(gQMarkPtr) # addiu $t0, $t0, 0x978
/* 08F7A0 8008EBA0 24630970 */  addiu $v1, %lo(gTrackSelectBgTriangles) # addiu $v1, $v1, 0x970
/* 08F7A4 8008EBA4 24070003 */  li    $a3, 3
/* 08F7A8 8008EBA8 24060001 */  li    $a2, 1
/* 08F7AC 8008EBAC 24050002 */  li    $a1, 2
/* 08F7B0 8008EBB0 24040040 */  li    $a0, 64
/* 08F7B4 8008EBB4 00001025 */  move  $v0, $zero
.L8008EBB8:
/* 08F7B8 8008EBB8 8C6B0000 */  lw    $t3, ($v1)
/* 08F7BC 8008EBBC 00000000 */  nop   
/* 08F7C0 8008EBC0 01626021 */  addu  $t4, $t3, $v0
/* 08F7C4 8008EBC4 A1840000 */  sb    $a0, ($t4)
/* 08F7C8 8008EBC8 8C6D0000 */  lw    $t5, ($v1)
/* 08F7CC 8008EBCC 00000000 */  nop   
/* 08F7D0 8008EBD0 01A27021 */  addu  $t6, $t5, $v0
/* 08F7D4 8008EBD4 A1C00001 */  sb    $zero, 1($t6)
/* 08F7D8 8008EBD8 8C6F0000 */  lw    $t7, ($v1)
/* 08F7DC 8008EBDC 00000000 */  nop   
/* 08F7E0 8008EBE0 01E2C021 */  addu  $t8, $t7, $v0
/* 08F7E4 8008EBE4 A3050002 */  sb    $a1, 2($t8)
/* 08F7E8 8008EBE8 8C790000 */  lw    $t9, ($v1)
/* 08F7EC 8008EBEC 00000000 */  nop   
/* 08F7F0 8008EBF0 03224821 */  addu  $t1, $t9, $v0
/* 08F7F4 8008EBF4 A1260003 */  sb    $a2, 3($t1)
/* 08F7F8 8008EBF8 8C6A0000 */  lw    $t2, ($v1)
/* 08F7FC 8008EBFC 24420010 */  addiu $v0, $v0, 0x10
/* 08F800 8008EC00 01425821 */  addu  $t3, $t2, $v0
/* 08F804 8008EC04 A1640000 */  sb    $a0, ($t3)
/* 08F808 8008EC08 8C6C0000 */  lw    $t4, ($v1)
/* 08F80C 8008EC0C 00000000 */  nop   
/* 08F810 8008EC10 01826821 */  addu  $t5, $t4, $v0
/* 08F814 8008EC14 A1A60001 */  sb    $a2, 1($t5)
/* 08F818 8008EC18 8C6E0000 */  lw    $t6, ($v1)
/* 08F81C 8008EC1C 00000000 */  nop   
/* 08F820 8008EC20 01C27821 */  addu  $t7, $t6, $v0
/* 08F824 8008EC24 A1E50002 */  sb    $a1, 2($t7)
/* 08F828 8008EC28 8C780000 */  lw    $t8, ($v1)
/* 08F82C 8008EC2C 00000000 */  nop   
/* 08F830 8008EC30 0302C821 */  addu  $t9, $t8, $v0
/* 08F834 8008EC34 24420010 */  addiu $v0, $v0, 0x10
/* 08F838 8008EC38 28410280 */  slti  $at, $v0, 0x280
/* 08F83C 8008EC3C 1420FFDE */  bnez  $at, .L8008EBB8
/* 08F840 8008EC40 A3270003 */   sb    $a3, 3($t9)
/* 08F844 8008EC44 24630004 */  addiu $v1, $v1, 4
/* 08F848 8008EC48 0068082B */  sltu  $at, $v1, $t0
/* 08F84C 8008EC4C 1420FFDA */  bnez  $at, .L8008EBB8
/* 08F850 8008EC50 00001025 */   move  $v0, $zero
/* 08F854 8008EC54 3C018012 */  lui   $at, %hi(D_80126924) # $at, 0x8012
/* 08F858 8008EC58 3C048009 */  lui   $a0, %hi(func_8008F618) # $a0, 0x8009
/* 08F85C 8008EC5C AC206924 */  sw    $zero, %lo(D_80126924)($at)
/* 08F860 8008EC60 0C01E2AB */  jal   set_background_draw_function
/* 08F864 8008EC64 2484F618 */   addiu $a0, %lo(func_8008F618) # addiu $a0, $a0, -0x9e8
/* 08F868 8008EC68 8FC20000 */  lw    $v0, ($fp)
/* 08F86C 8008EC6C 00002025 */  move  $a0, $zero
/* 08F870 8008EC70 00021843 */  sra   $v1, $v0, 1
/* 08F874 8008EC74 00624821 */  addu  $t1, $v1, $v0
/* 08F878 8008EC78 AFA90010 */  sw    $t1, 0x10($sp)
/* 08F87C 8008EC7C 24050050 */  li    $a1, 80
/* 08F880 8008EC80 240700F0 */  li    $a3, 240
/* 08F884 8008EC84 0C019A50 */  jal   viewport_menu_set
/* 08F888 8008EC88 00433023 */   subu  $a2, $v0, $v1
/* 08F88C 8008EC8C 0C019984 */  jal   copy_viewports_to_stack
/* 08F890 8008EC90 00000000 */   nop   
/* 08F894 8008EC94 00002025 */  move  $a0, $zero
/* 08F898 8008EC98 0C019A06 */  jal   camEnableUserView
/* 08F89C 8008EC9C 00002825 */   move  $a1, $zero
/* 08F8A0 8008ECA0 240A0001 */  li    $t2, 1
/* 08F8A4 8008ECA4 3C01800E */  lui   $at, %hi(gIsInTracksMenu) # $at, 0x800e
/* 08F8A8 8008ECA8 3C04800E */  lui   $a0, %hi(gTrackSelectObjectIndices) # $a0, 0x800e
/* 08F8AC 8008ECAC AC2A097C */  sw    $t2, %lo(gIsInTracksMenu)($at)
/* 08F8B0 8008ECB0 0C02719D */  jal   func_8009C674
/* 08F8B4 8008ECB4 248407C4 */   addiu $a0, %lo(gTrackSelectObjectIndices) # addiu $a0, $a0, 0x7c4
/* 08F8B8 8008ECB8 3C04800E */  lui   $a0, %hi(gTrackSelectImageIndices) # $a0, 0x800e
/* 08F8BC 8008ECBC 0C027229 */  jal   allocate_menu_images
/* 08F8C0 8008ECC0 248407E0 */   addiu $a0, %lo(gTrackSelectImageIndices) # addiu $a0, $a0, 0x7e0
/* 08F8C4 8008ECC4 0C02392C */  jal   assign_menu_arrow_textures
/* 08F8C8 8008ECC8 00000000 */   nop   
/* 08F8CC 8008ECCC 3C02800E */  lui   $v0, %hi(D_800E05D4) # $v0, 0x800e
/* 08F8D0 8008ECD0 3C03800E */  lui   $v1, %hi(D_800E05F4) # $v1, 0x800e
/* 08F8D4 8008ECD4 246305F4 */  addiu $v1, %lo(D_800E05F4) # addiu $v1, $v1, 0x5f4
/* 08F8D8 8008ECD8 244205D4 */  addiu $v0, %lo(D_800E05D4) # addiu $v0, $v0, 0x5d4
/* 08F8DC 8008ECDC 8ECB0020 */  lw    $t3, 0x20($s6)
/* 08F8E0 8008ECE0 8ECC0024 */  lw    $t4, 0x24($s6)
/* 08F8E4 8008ECE4 8ECD0028 */  lw    $t5, 0x28($s6)
/* 08F8E8 8008ECE8 8ECE002C */  lw    $t6, 0x2c($s6)
/* 08F8EC 8008ECEC 8ECF0030 */  lw    $t7, 0x30($s6)
/* 08F8F0 8008ECF0 8ED80034 */  lw    $t8, 0x34($s6)
/* 08F8F4 8008ECF4 3C198012 */  lui   $t9, %hi(D_801268E8) # $t9, 0x8012
/* 08F8F8 8008ECF8 273968E8 */  addiu $t9, %lo(D_801268E8) # addiu $t9, $t9, 0x68e8
/* 08F8FC 8008ECFC AFB90058 */  sw    $t9, 0x58($sp)
/* 08F900 8008ED00 24160004 */  li    $s6, 4
/* 08F904 8008ED04 00009825 */  move  $s3, $zero
/* 08F908 8008ED08 24100006 */  li    $s0, 6
/* 08F90C 8008ED0C AC4B0000 */  sw    $t3, ($v0)
/* 08F910 8008ED10 AC4C0008 */  sw    $t4, 8($v0)
/* 08F914 8008ED14 AC4D0010 */  sw    $t5, 0x10($v0)
/* 08F918 8008ED18 AC6E0000 */  sw    $t6, ($v1)
/* 08F91C 8008ED1C AC6F0008 */  sw    $t7, 8($v1)
/* 08F920 8008ED20 AC780010 */  sw    $t8, 0x10($v1)
.L8008ED24:
/* 08F924 8008ED24 8FB20058 */  lw    $s2, 0x58($sp)
/* 08F928 8008ED28 00008825 */  move  $s1, $zero
/* 08F92C 8008ED2C 267E0001 */  addiu $fp, $s3, 1
.L8008ED30:
/* 08F930 8008ED30 1620000B */  bnez  $s1, .L8008ED60
/* 08F934 8008ED34 A6550000 */   sh    $s5, ($s2)
/* 08F938 8008ED38 2A610004 */  slti  $at, $s3, 4
/* 08F93C 8008ED3C 10200009 */  beqz  $at, .L8008ED64
/* 08F940 8008ED40 2A210004 */   slti  $at, $s1, 4
/* 08F944 8008ED44 02700019 */  multu $s3, $s0
/* 08F948 8008ED48 00004812 */  mflo  $t1
/* 08F94C 8008ED4C 01315021 */  addu  $t2, $t1, $s1
/* 08F950 8008ED50 01575821 */  addu  $t3, $t2, $s7
/* 08F954 8008ED54 816C0000 */  lb    $t4, ($t3)
/* 08F958 8008ED58 1000004A */  b     .L8008EE84
/* 08F95C 8008ED5C A64C0000 */   sh    $t4, ($s2)
.L8008ED60:
/* 08F960 8008ED60 2A210004 */  slti  $at, $s1, 4
.L8008ED64:
/* 08F964 8008ED64 10200013 */  beqz  $at, .L8008EDB4
/* 08F968 8008ED68 00000000 */   nop   
/* 08F96C 8008ED6C 02700019 */  multu $s3, $s0
/* 08F970 8008ED70 00006812 */  mflo  $t5
/* 08F974 8008ED74 01B17021 */  addu  $t6, $t5, $s1
/* 08F978 8008ED78 01D77821 */  addu  $t7, $t6, $s7
/* 08F97C 8008ED7C 81E20000 */  lb    $v0, ($t7)
/* 08F980 8008ED80 00000000 */  nop   
/* 08F984 8008ED84 12A2003F */  beq   $s5, $v0, .L8008EE84
/* 08F988 8008ED88 00000000 */   nop   
/* 08F98C 8008ED8C 8E980004 */  lw    $t8, 4($s4)
/* 08F990 8008ED90 0002C880 */  sll   $t9, $v0, 2
/* 08F994 8008ED94 03194821 */  addu  $t1, $t8, $t9
/* 08F998 8008ED98 8D2A0000 */  lw    $t2, ($t1)
/* 08F99C 8008ED9C 00000000 */  nop   
/* 08F9A0 8008EDA0 314B0001 */  andi  $t3, $t2, 1
/* 08F9A4 8008EDA4 11600037 */  beqz  $t3, .L8008EE84
/* 08F9A8 8008EDA8 00000000 */   nop   
/* 08F9AC 8008EDAC 10000035 */  b     .L8008EE84
/* 08F9B0 8008EDB0 A6420000 */   sh    $v0, ($s2)
.L8008EDB4:
/* 08F9B4 8008EDB4 16360025 */  bne   $s1, $s6, .L8008EE4C
/* 08F9B8 8008EDB8 24010005 */   li    $at, 5
/* 08F9BC 8008EDBC 00133080 */  sll   $a2, $s3, 2
/* 08F9C0 8008EDC0 00D33023 */  subu  $a2, $a2, $s3
/* 08F9C4 8008EDC4 00063040 */  sll   $a2, $a2, 1
/* 08F9C8 8008EDC8 00D71021 */  addu  $v0, $a2, $s7
/* 08F9CC 8008EDCC 00002025 */  move  $a0, $zero
/* 08F9D0 8008EDD0 00002825 */  move  $a1, $zero
.L8008EDD4:
/* 08F9D4 8008EDD4 80430000 */  lb    $v1, ($v0)
/* 08F9D8 8008EDD8 24840001 */  addiu $a0, $a0, 1
/* 08F9DC 8008EDDC 12A3000A */  beq   $s5, $v1, .L8008EE08
/* 08F9E0 8008EDE0 28810004 */   slti  $at, $a0, 4
/* 08F9E4 8008EDE4 8E8C0004 */  lw    $t4, 4($s4)
/* 08F9E8 8008EDE8 00036880 */  sll   $t5, $v1, 2
/* 08F9EC 8008EDEC 018D7021 */  addu  $t6, $t4, $t5
/* 08F9F0 8008EDF0 8DCF0000 */  lw    $t7, ($t6)
/* 08F9F4 8008EDF4 00000000 */  nop   
/* 08F9F8 8008EDF8 31F80006 */  andi  $t8, $t7, 6
/* 08F9FC 8008EDFC 16180002 */  bne   $s0, $t8, .L8008EE08
/* 08FA00 8008EE00 00000000 */   nop   
/* 08FA04 8008EE04 24A50001 */  addiu $a1, $a1, 1
.L8008EE08:
/* 08FA08 8008EE08 1420FFF2 */  bnez  $at, .L8008EDD4
/* 08FA0C 8008EE0C 24420001 */   addiu $v0, $v0, 1
/* 08FA10 8008EE10 14B60009 */  bne   $a1, $s6, .L8008EE38
/* 08FA14 8008EE14 00D15821 */   addu  $t3, $a2, $s1
/* 08FA18 8008EE18 12760007 */  beq   $s3, $s6, .L8008EE38
/* 08FA1C 8008EE1C 24190082 */   li    $t9, 130
/* 08FA20 8008EE20 9689000C */  lhu   $t1, 0xc($s4)
/* 08FA24 8008EE24 02791004 */  sllv  $v0, $t9, $s3
/* 08FA28 8008EE28 01225024 */  and   $t2, $t1, $v0
/* 08FA2C 8008EE2C 104A0002 */  beq   $v0, $t2, .L8008EE38
/* 08FA30 8008EE30 00000000 */   nop   
/* 08FA34 8008EE34 00002825 */  move  $a1, $zero
.L8008EE38:
/* 08FA38 8008EE38 14B60012 */  bne   $a1, $s6, .L8008EE84
/* 08FA3C 8008EE3C 01776021 */   addu  $t4, $t3, $s7
/* 08FA40 8008EE40 818D0000 */  lb    $t5, ($t4)
/* 08FA44 8008EE44 1000000F */  b     .L8008EE84
/* 08FA48 8008EE48 A64D0000 */   sh    $t5, ($s2)
.L8008EE4C:
/* 08FA4C 8008EE4C 1621000D */  bne   $s1, $at, .L8008EE84
/* 08FA50 8008EE50 240F0001 */   li    $t7, 1
/* 08FA54 8008EE54 968E0008 */  lhu   $t6, 8($s4)
/* 08FA58 8008EE58 03CFC004 */  sllv  $t8, $t7, $fp
/* 08FA5C 8008EE5C 01D8C824 */  and   $t9, $t6, $t8
/* 08FA60 8008EE60 13200008 */  beqz  $t9, .L8008EE84
/* 08FA64 8008EE64 00000000 */   nop   
/* 08FA68 8008EE68 02700019 */  multu $s3, $s0
/* 08FA6C 8008EE6C 00004812 */  mflo  $t1
/* 08FA70 8008EE70 01315021 */  addu  $t2, $t1, $s1
/* 08FA74 8008EE74 01575821 */  addu  $t3, $t2, $s7
/* 08FA78 8008EE78 816C0000 */  lb    $t4, ($t3)
/* 08FA7C 8008EE7C 00000000 */  nop   
/* 08FA80 8008EE80 A64C0000 */  sh    $t4, ($s2)
.L8008EE84:
/* 08FA84 8008EE84 0C027B18 */  jal   is_adventure_two_unlocked
/* 08FA88 8008EE88 00000000 */   nop   
/* 08FA8C 8008EE8C 10400008 */  beqz  $v0, .L8008EEB0
/* 08FA90 8008EE90 00000000 */   nop   
/* 08FA94 8008EE94 02700019 */  multu $s3, $s0
/* 08FA98 8008EE98 00006812 */  mflo  $t5
/* 08FA9C 8008EE9C 01B17821 */  addu  $t7, $t5, $s1
/* 08FAA0 8008EEA0 01F77021 */  addu  $t6, $t7, $s7
/* 08FAA4 8008EEA4 81D80000 */  lb    $t8, ($t6)
/* 08FAA8 8008EEA8 00000000 */  nop   
/* 08FAAC 8008EEAC A6580000 */  sh    $t8, ($s2)
.L8008EEB0:
/* 08FAB0 8008EEB0 26310001 */  addiu $s1, $s1, 1
/* 08FAB4 8008EEB4 1630FF9E */  bne   $s1, $s0, .L8008ED30
/* 08FAB8 8008EEB8 26520002 */   addiu $s2, $s2, 2
/* 08FABC 8008EEBC 8FB90058 */  lw    $t9, 0x58($sp)
/* 08FAC0 8008EEC0 24010005 */  li    $at, 5
/* 08FAC4 8008EEC4 2729000C */  addiu $t1, $t9, 0xc
/* 08FAC8 8008EEC8 AFA90058 */  sw    $t1, 0x58($sp)
/* 08FACC 8008EECC 17C1FF95 */  bne   $fp, $at, .L8008ED24
/* 08FAD0 8008EED0 03C09825 */   move  $s3, $fp
/* 08FAD4 8008EED4 3C028012 */  lui   $v0, %hi(D_801269CC) # $v0, 0x8012
/* 08FAD8 8008EED8 8C4269CC */  lw    $v0, %lo(D_801269CC)($v0)
/* 08FADC 8008EEDC 3C0C8012 */  lui   $t4, %hi(D_801269C8) # $t4, 0x8012
/* 08FAE0 8008EEE0 00025080 */  sll   $t2, $v0, 2
/* 08FAE4 8008EEE4 8D8C69C8 */  lw    $t4, %lo(D_801269C8)($t4)
/* 08FAE8 8008EEE8 3C078012 */  lui   $a3, %hi(D_801268E8) # $a3, 0x8012
/* 08FAEC 8008EEEC 01425023 */  subu  $t2, $t2, $v0
/* 08FAF0 8008EEF0 24E768E8 */  addiu $a3, %lo(D_801268E8) # addiu $a3, $a3, 0x68e8
/* 08FAF4 8008EEF4 000A5080 */  sll   $t2, $t2, 2
/* 08FAF8 8008EEF8 00EA5821 */  addu  $t3, $a3, $t2
/* 08FAFC 8008EEFC 000C6840 */  sll   $t5, $t4, 1
/* 08FB00 8008EF00 016D7821 */  addu  $t7, $t3, $t5
/* 08FB04 8008EF04 85EE0000 */  lh    $t6, ($t7)
/* 08FB08 8008EF08 3C03800E */  lui   $v1, %hi(gTrackIdForPreview) # $v1, 0x800e
/* 08FB0C 8008EF0C 3C10800E */  lui   $s0, %hi(gTrackSelectRow) # $s0, 0x800e
/* 08FB10 8008EF10 2610F4C8 */  addiu $s0, %lo(gTrackSelectRow) # addiu $s0, $s0, -0xb38
/* 08FB14 8008EF14 2463F4C4 */  addiu $v1, %lo(gTrackIdForPreview) # addiu $v1, $v1, -0xb3c
/* 08FB18 8008EF18 24580001 */  addiu $t8, $v0, 1
/* 08FB1C 8008EF1C AE180000 */  sw    $t8, ($s0)
/* 08FB20 8008EF20 16AE000E */  bne   $s5, $t6, .L8008EF5C
/* 08FB24 8008EF24 AC6E0000 */   sw    $t6, ($v1)
/* 08FB28 8008EF28 84E40000 */  lh    $a0, ($a3)
/* 08FB2C 8008EF2C 3C028012 */  lui   $v0, %hi(D_801263D0) # $v0, 0x8012
/* 08FB30 8008EF30 244263D0 */  addiu $v0, %lo(D_801263D0) # addiu $v0, $v0, 0x63d0
/* 08FB34 8008EF34 2405FFFF */  li    $a1, -1
/* 08FB38 8008EF38 24060001 */  li    $a2, 1
/* 08FB3C 8008EF3C 0C01B8BA */  jal   load_level_for_menu
/* 08FB40 8008EF40 AC440000 */   sw    $a0, ($v0)
/* 08FB44 8008EF44 240A0001 */  li    $t2, 1
/* 08FB48 8008EF48 AE0A0000 */  sw    $t2, ($s0)
/* 08FB4C 8008EF4C 3C018012 */  lui   $at, %hi(gSelectedTrackX) # $at, 0x8012
/* 08FB50 8008EF50 AC2069F4 */  sw    $zero, %lo(gSelectedTrackX)($at)
/* 08FB54 8008EF54 3C018012 */  lui   $at, %hi(gSelectedTrackY) # $at, 0x8012
/* 08FB58 8008EF58 AC2069F8 */  sw    $zero, %lo(gSelectedTrackY)($at)
.L8008EF5C:
/* 08FB5C 8008EF5C 0C031525 */  jal   assign_dialogue_box_id
/* 08FB60 8008EF60 24040007 */   li    $a0, 7
/* 08FB64 8008EF64 0C01FFFB */  jal   func_8007FFEC
/* 08FB68 8008EF68 24040002 */   li    $a0, 2
/* 08FB6C 8008EF6C 3C018012 */  lui   $at, %hi(D_80126840) # $at, 0x8012
/* 08FB70 8008EF70 AC206840 */  sw    $zero, %lo(D_80126840)($at)
/* 08FB74 8008EF74 3C10800E */  lui   $s0, %hi(sMenuMusicVolume) # $s0, 0x800e
/* 08FB78 8008EF78 3C018012 */  lui   $at, %hi(D_80126848) # $at, 0x8012
/* 08FB7C 8008EF7C 2610F760 */  addiu $s0, %lo(sMenuMusicVolume) # addiu $s0, $s0, -0x8a0
/* 08FB80 8008EF80 AC206848 */  sw    $zero, %lo(D_80126848)($at)
/* 08FB84 8008EF84 AE000000 */  sw    $zero, ($s0)
/* 08FB88 8008EF88 0C0002F8 */  jal   music_voicelimit_set
/* 08FB8C 8008EF8C 24040018 */   li    $a0, 24
/* 08FB90 8008EF90 0C000307 */  jal   music_voicelimit_change_off
/* 08FB94 8008EF94 00000000 */   nop   
/* 08FB98 8008EF98 0C0002CD */  jal   music_play
/* 08FB9C 8008EF9C 24040018 */   li    $a0, 24
/* 08FBA0 8008EFA0 92040003 */  lbu   $a0, 3($s0)
/* 08FBA4 8008EFA4 0C000664 */  jal   music_volume_set
/* 08FBA8 8008EFA8 00000000 */   nop   
/* 08FBAC 8008EFAC 0C0002C6 */  jal   music_change_off
/* 08FBB0 8008EFB0 00000000 */   nop   
/* 08FBB4 8008EFB4 0C01BD59 */  jal   set_gIntDisFlag
/* 08FBB8 8008EFB8 24040001 */   li    $a0, 1
/* 08FBBC 8008EFBC 3C0C800E */  lui   $t4, %hi(gTracksMenuAdventureHighlightIndex) # $t4, 0x800e
/* 08FBC0 8008EFC0 8D8C0418 */  lw    $t4, %lo(gTracksMenuAdventureHighlightIndex)($t4)
/* 08FBC4 8008EFC4 3C01800E */  lui   $at, %hi(gIsInAdventureTwo) # $at, 0x800e
/* 08FBC8 8008EFC8 3C0B800E */  lui   $t3, %hi(gMultiplayerSelectedNumberOfRacers) # $t3, 0x800e
/* 08FBCC 8008EFCC 8D6B0410 */  lw    $t3, %lo(gMultiplayerSelectedNumberOfRacers)($t3)
/* 08FBD0 8008EFD0 8FBF0044 */  lw    $ra, 0x44($sp)
/* 08FBD4 8008EFD4 AC2CF494 */  sw    $t4, %lo(gIsInAdventureTwo)($at)
/* 08FBD8 8008EFD8 3C018012 */  lui   $at, %hi(gMultiplayerSelectedNumberOfRacersCopy) # $at, 0x8012
/* 08FBDC 8008EFDC 8FB00020 */  lw    $s0, 0x20($sp)
/* 08FBE0 8008EFE0 8FB10024 */  lw    $s1, 0x24($sp)
/* 08FBE4 8008EFE4 8FB20028 */  lw    $s2, 0x28($sp)
/* 08FBE8 8008EFE8 8FB3002C */  lw    $s3, 0x2c($sp)
/* 08FBEC 8008EFEC 8FB40030 */  lw    $s4, 0x30($sp)
/* 08FBF0 8008EFF0 8FB50034 */  lw    $s5, 0x34($sp)
/* 08FBF4 8008EFF4 8FB60038 */  lw    $s6, 0x38($sp)
/* 08FBF8 8008EFF8 8FB7003C */  lw    $s7, 0x3c($sp)
/* 08FBFC 8008EFFC 8FBE0040 */  lw    $fp, 0x40($sp)
/* 08FC00 8008F000 27BD0080 */  addiu $sp, $sp, 0x80
/* 08FC04 8008F004 03E00008 */  jr    $ra
/* 08FC08 8008F008 AC2B6548 */   sw    $t3, %lo(gMultiplayerSelectedNumberOfRacersCopy)($at)

