glabel load_menu_text
/* 080500 8007F900 3C09800E */  lui   $t1, %hi(gMenuTextLangTable) # $t1, 0x800e
/* 080504 8007F904 2529F49C */  addiu $t1, %lo(gMenuTextLangTable) # addiu $t1, $t1, -0xb64
/* 080508 8007F908 8D230000 */  lw    $v1, ($t1)
/* 08050C 8007F90C 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 080510 8007F910 AFBF0014 */  sw    $ra, 0x14($sp)
/* 080514 8007F914 14600009 */  bnez  $v1, .L8007F93C
/* 080518 8007F918 00802825 */   move  $a1, $a0
/* 08051C 8007F91C 24040009 */  li    $a0, 9
/* 080520 8007F920 0C01DB16 */  jal   load_asset_section_from_rom
/* 080524 8007F924 AFA50018 */   sw    $a1, 0x18($sp)
/* 080528 8007F928 3C09800E */  lui   $t1, %hi(gMenuTextLangTable) # $t1, 0x800e
/* 08052C 8007F92C 2529F49C */  addiu $t1, %lo(gMenuTextLangTable) # addiu $t1, $t1, -0xb64
/* 080530 8007F930 8FA50018 */  lw    $a1, 0x18($sp)
/* 080534 8007F934 AD220000 */  sw    $v0, ($t1)
/* 080538 8007F938 00401825 */  move  $v1, $v0
.L8007F93C:
/* 08053C 8007F93C 24010001 */  li    $at, 1
/* 080540 8007F940 10A1000B */  beq   $a1, $at, .L8007F970
/* 080544 8007F944 3C08800E */   lui   $t0, %hi(gMenuText) # $t0, 0x800e
/* 080548 8007F948 24010002 */  li    $at, 2
/* 08054C 8007F94C 10A1000A */  beq   $a1, $at, .L8007F978
/* 080550 8007F950 24060002 */   li    $a2, 2
/* 080554 8007F954 24010003 */  li    $at, 3
/* 080558 8007F958 10A10003 */  beq   $a1, $at, .L8007F968
/* 08055C 8007F95C 00000000 */   nop   
/* 080560 8007F960 10000005 */  b     .L8007F978
/* 080564 8007F964 24060001 */   li    $a2, 1
.L8007F968:
/* 080568 8007F968 10000003 */  b     .L8007F978
/* 08056C 8007F96C 24060004 */   li    $a2, 4
.L8007F970:
/* 080570 8007F970 10000001 */  b     .L8007F978
/* 080574 8007F974 24060003 */   li    $a2, 3
.L8007F978:
/* 080578 8007F978 00067080 */  sll   $t6, $a2, 2
/* 08057C 8007F97C 006E1021 */  addu  $v0, $v1, $t6
/* 080580 8007F980 2508F4A0 */  addiu $t0, %lo(gMenuText) # addiu $t0, $t0, -0xb60
/* 080584 8007F984 8C470004 */  lw    $a3, 4($v0)
/* 080588 8007F988 8C460000 */  lw    $a2, ($v0)
/* 08058C 8007F98C 8D050000 */  lw    $a1, ($t0)
/* 080590 8007F990 00E63823 */  subu  $a3, $a3, $a2
/* 080594 8007F994 10A00179 */  beqz  $a1, .L8007FF7C
/* 080598 8007F998 8FBF0014 */   lw    $ra, 0x14($sp)
/* 08059C 8007F99C 0C01DB9A */  jal   load_asset_to_address
/* 0805A0 8007F9A0 24040008 */   li    $a0, 8
/* 0805A4 8007F9A4 3C09800E */  lui   $t1, %hi(gMenuTextLangTable) # $t1, 0x800e
/* 0805A8 8007F9A8 2529F49C */  addiu $t1, %lo(gMenuTextLangTable) # addiu $t1, $t1, -0xb64
/* 0805AC 8007F9AC 8D2F0000 */  lw    $t7, ($t1)
/* 0805B0 8007F9B0 3C08800E */  lui   $t0, %hi(gMenuText) # $t0, 0x800e
/* 0805B4 8007F9B4 8DF80000 */  lw    $t8, ($t7)
/* 0805B8 8007F9B8 2508F4A0 */  addiu $t0, %lo(gMenuText) # addiu $t0, $t0, -0xb60
/* 0805BC 8007F9BC 1B000014 */  blez  $t8, .L8007FA10
/* 0805C0 8007F9C0 00003025 */   move  $a2, $zero
/* 0805C4 8007F9C4 00001825 */  move  $v1, $zero
/* 0805C8 8007F9C8 2407FFFF */  li    $a3, -1
.L8007F9CC:
/* 0805CC 8007F9CC 8D050000 */  lw    $a1, ($t0)
/* 0805D0 8007F9D0 00000000 */  nop   
/* 0805D4 8007F9D4 00A31021 */  addu  $v0, $a1, $v1
/* 0805D8 8007F9D8 8C440000 */  lw    $a0, ($v0)
/* 0805DC 8007F9DC 00000000 */  nop   
/* 0805E0 8007F9E0 14E40003 */  bne   $a3, $a0, .L8007F9F0
/* 0805E4 8007F9E4 0085C821 */   addu  $t9, $a0, $a1
/* 0805E8 8007F9E8 10000002 */  b     .L8007F9F4
/* 0805EC 8007F9EC AC400000 */   sw    $zero, ($v0)
.L8007F9F0:
/* 0805F0 8007F9F0 AC590000 */  sw    $t9, ($v0)
.L8007F9F4:
/* 0805F4 8007F9F4 8D2A0000 */  lw    $t2, ($t1)
/* 0805F8 8007F9F8 24C60001 */  addiu $a2, $a2, 1
/* 0805FC 8007F9FC 8D4B0000 */  lw    $t3, ($t2)
/* 080600 8007FA00 24630004 */  addiu $v1, $v1, 4
/* 080604 8007FA04 00CB082A */  slt   $at, $a2, $t3
/* 080608 8007FA08 1420FFF0 */  bnez  $at, .L8007F9CC
/* 08060C 8007FA0C 00000000 */   nop   
.L8007FA10:
/* 080610 8007FA10 8D040000 */  lw    $a0, ($t0)
/* 080614 8007FA14 3C058012 */  lui   $a1, %hi(gAudioOutputStrings) # $a1, 0x8012
/* 080618 8007FA18 8C8C0000 */  lw    $t4, ($a0)
/* 08061C 8007FA1C 24A569D0 */  addiu $a1, %lo(gAudioOutputStrings) # addiu $a1, $a1, 0x69d0
/* 080620 8007FA20 ACAC0000 */  sw    $t4, ($a1)
/* 080624 8007FA24 8C8D0004 */  lw    $t5, 4($a0)
/* 080628 8007FA28 3C02800E */  lui   $v0, %hi(gAudioMenuStrings) # $v0, 0x800e
/* 08062C 8007FA2C ACAD0004 */  sw    $t5, 4($a1)
/* 080630 8007FA30 8C8E0008 */  lw    $t6, 8($a0)
/* 080634 8007FA34 2442FA3C */  addiu $v0, %lo(gAudioMenuStrings) # addiu $v0, $v0, -0x5c4
/* 080638 8007FA38 ACAE0008 */  sw    $t6, 8($a1)
/* 08063C 8007FA3C 8C8F000C */  lw    $t7, 0xc($a0)
/* 080640 8007FA40 3C018012 */  lui   $at, %hi(gMusicTestString) # $at, 0x8012
/* 080644 8007FA44 AC4F001C */  sw    $t7, 0x1c($v0)
/* 080648 8007FA48 8C980010 */  lw    $t8, 0x10($a0)
/* 08064C 8007FA4C 3C03800E */  lui   $v1, %hi(gMagicCodeMenuStrings) # $v1, 0x800e
/* 080650 8007FA50 AC58002C */  sw    $t8, 0x2c($v0)
/* 080654 8007FA54 8C990014 */  lw    $t9, 0x14($a0)
/* 080658 8007FA58 2463FDA0 */  addiu $v1, %lo(gMagicCodeMenuStrings) # addiu $v1, $v1, -0x260
/* 08065C 8007FA5C AC59003C */  sw    $t9, 0x3c($v0)
/* 080660 8007FA60 8C8A0018 */  lw    $t2, 0x18($a0)
/* 080664 8007FA64 3C07800E */  lui   $a3, %hi(D_800E0BEC) # $a3, 0x800e
/* 080668 8007FA68 AC4A004C */  sw    $t2, 0x4c($v0)
/* 08066C 8007FA6C 8C8B0018 */  lw    $t3, 0x18($a0)
/* 080670 8007FA70 24E70BEC */  addiu $a3, %lo(D_800E0BEC) # addiu $a3, $a3, 0xbec
/* 080674 8007FA74 AC4B005C */  sw    $t3, 0x5c($v0)
/* 080678 8007FA78 8C8C001C */  lw    $t4, 0x1c($a0)
/* 08067C 8007FA7C 3C09800E */  lui   $t1, %hi(D_800E0CEC) # $t1, 0x800e
/* 080680 8007FA80 AC2C69E0 */  sw    $t4, %lo(gMusicTestString)($at)
/* 080684 8007FA84 8C8D0038 */  lw    $t5, 0x38($a0)
/* 080688 8007FA88 25290CEC */  addiu $t1, %lo(D_800E0CEC) # addiu $t1, $t1, 0xcec
/* 08068C 8007FA8C AC6D0000 */  sw    $t5, ($v1)
/* 080690 8007FA90 8C8E003C */  lw    $t6, 0x3c($a0)
/* 080694 8007FA94 3C06800E */  lui   $a2, %hi(D_800E0E4C) # $a2, 0x800e
/* 080698 8007FA98 AC6E0004 */  sw    $t6, 4($v1)
/* 08069C 8007FA9C 8C8F0040 */  lw    $t7, 0x40($a0)
/* 0806A0 8007FAA0 24C60E4C */  addiu $a2, %lo(D_800E0E4C) # addiu $a2, $a2, 0xe4c
/* 0806A4 8007FAA4 AC6F0008 */  sw    $t7, 8($v1)
/* 0806A8 8007FAA8 8C980014 */  lw    $t8, 0x14($a0)
/* 0806AC 8007FAAC 3C02800E */  lui   $v0, %hi(gOptionMenuStrings) # $v0, 0x800e
/* 0806B0 8007FAB0 AC78000C */  sw    $t8, 0xc($v1)
/* 0806B4 8007FAB4 8C990074 */  lw    $t9, 0x74($a0)
/* 0806B8 8007FAB8 2442FA10 */  addiu $v0, %lo(gOptionMenuStrings) # addiu $v0, $v0, -0x5f0
/* 0806BC 8007FABC ACF90034 */  sw    $t9, 0x34($a3)
/* 0806C0 8007FAC0 8C8A0078 */  lw    $t2, 0x78($a0)
/* 0806C4 8007FAC4 3C010200 */  lui   $at, 0x200
/* 0806C8 8007FAC8 ACEA0054 */  sw    $t2, 0x54($a3)
/* 0806CC 8007FACC 8C8B007C */  lw    $t3, 0x7c($a0)
/* 0806D0 8007FAD0 00000000 */  nop   
/* 0806D4 8007FAD4 AD2B0114 */  sw    $t3, 0x114($t1)
/* 0806D8 8007FAD8 8C8C007C */  lw    $t4, 0x7c($a0)
/* 0806DC 8007FADC 3C0B8012 */  lui   $t3, %hi(sEepromSettings+4) # $t3, 0x8012
/* 0806E0 8007FAE0 AD2C0134 */  sw    $t4, 0x134($t1)
/* 0806E4 8007FAE4 8C8D0080 */  lw    $t5, 0x80($a0)
/* 0806E8 8007FAE8 00000000 */  nop   
/* 0806EC 8007FAEC ACCD0014 */  sw    $t5, 0x14($a2)
/* 0806F0 8007FAF0 8C8E0080 */  lw    $t6, 0x80($a0)
/* 0806F4 8007FAF4 00000000 */  nop   
/* 0806F8 8007FAF8 ACCE0034 */  sw    $t6, 0x34($a2)
/* 0806FC 8007FAFC 8C8F0024 */  lw    $t7, 0x24($a0)
/* 080700 8007FB00 00000000 */  nop   
/* 080704 8007FB04 ACCF0054 */  sw    $t7, 0x54($a2)
/* 080708 8007FB08 8C980028 */  lw    $t8, 0x28($a0)
/* 08070C 8007FB0C 00000000 */  nop   
/* 080710 8007FB10 ACD800B4 */  sw    $t8, 0xb4($a2)
/* 080714 8007FB14 8C990088 */  lw    $t9, 0x88($a0)
/* 080718 8007FB18 00000000 */  nop   
/* 08071C 8007FB1C AC590000 */  sw    $t9, ($v0)
/* 080720 8007FB20 8D6B644C */  lw    $t3, %lo(sEepromSettings+4)($t3)
/* 080724 8007FB24 00000000 */  nop   
/* 080728 8007FB28 01616824 */  and   $t5, $t3, $at
/* 08072C 8007FB2C 11A00004 */  beqz  $t5, .L8007FB40
/* 080730 8007FB30 00000000 */   nop   
/* 080734 8007FB34 8C8E02D8 */  lw    $t6, 0x2d8($a0)
/* 080738 8007FB38 10000004 */  b     .L8007FB4C
/* 08073C 8007FB3C AC4E0004 */   sw    $t6, 4($v0)
.L8007FB40:
/* 080740 8007FB40 8C8F02DC */  lw    $t7, 0x2dc($a0)
/* 080744 8007FB44 00000000 */  nop   
/* 080748 8007FB48 AC4F0004 */  sw    $t7, 4($v0)
.L8007FB4C:
/* 08074C 8007FB4C 8C980018 */  lw    $t8, 0x18($a0)
/* 080750 8007FB50 3C06800E */  lui   $a2, %hi(gFilenames) # $a2, 0x800e
/* 080754 8007FB54 AC580008 */  sw    $t8, 8($v0)
/* 080758 8007FB58 8C990294 */  lw    $t9, 0x294($a0)
/* 08075C 8007FB5C 24C603B0 */  addiu $a2, %lo(gFilenames) # addiu $a2, $a2, 0x3b0
/* 080760 8007FB60 AC59000C */  sw    $t9, 0xc($v0)
/* 080764 8007FB64 8C8A0044 */  lw    $t2, 0x44($a0)
/* 080768 8007FB68 3C07800E */  lui   $a3, %hi(D_800DFAE4) # $a3, 0x800e
/* 08076C 8007FB6C AC4A0010 */  sw    $t2, 0x10($v0)
/* 080770 8007FB70 8C8B0014 */  lw    $t3, 0x14($a0)
/* 080774 8007FB74 24E7FAE4 */  addiu $a3, %lo(D_800DFAE4) # addiu $a3, $a3, -0x51c
/* 080778 8007FB78 AC4B0014 */  sw    $t3, 0x14($v0)
/* 08077C 8007FB7C 8C8C0120 */  lw    $t4, 0x120($a0)
/* 080780 8007FB80 3C03800E */  lui   $v1, %hi(D_800DFAFC) # $v1, 0x800e
/* 080784 8007FB84 ACCC0000 */  sw    $t4, ($a2)
/* 080788 8007FB88 8C8D0124 */  lw    $t5, 0x124($a0)
/* 08078C 8007FB8C 2463FAFC */  addiu $v1, %lo(D_800DFAFC) # addiu $v1, $v1, -0x504
/* 080790 8007FB90 ACCD0004 */  sw    $t5, 4($a2)
/* 080794 8007FB94 8C8E0128 */  lw    $t6, 0x128($a0)
/* 080798 8007FB98 3C05800E */  lui   $a1, %hi(D_800DFB14) # $a1, 0x800e
/* 08079C 8007FB9C ACCE0008 */  sw    $t6, 8($a2)
/* 0807A0 8007FBA0 8C8F0168 */  lw    $t7, 0x168($a0)
/* 0807A4 8007FBA4 24A5FB14 */  addiu $a1, %lo(D_800DFB14) # addiu $a1, $a1, -0x4ec
/* 0807A8 8007FBA8 ACEF0000 */  sw    $t7, ($a3)
/* 0807AC 8007FBAC 8C98016C */  lw    $t8, 0x16c($a0)
/* 0807B0 8007FBB0 3C08800E */  lui   $t0, %hi(D_800DFB2C) # $t0, 0x800e
/* 0807B4 8007FBB4 ACF80004 */  sw    $t8, 4($a3)
/* 0807B8 8007FBB8 8C990154 */  lw    $t9, 0x154($a0)
/* 0807BC 8007FBBC 2508FB2C */  addiu $t0, %lo(D_800DFB2C) # addiu $t0, $t0, -0x4d4
/* 0807C0 8007FBC0 ACF9000C */  sw    $t9, 0xc($a3)
/* 0807C4 8007FBC4 8C8A0168 */  lw    $t2, 0x168($a0)
/* 0807C8 8007FBC8 3C02800E */  lui   $v0, %hi(D_800DFB40) # $v0, 0x800e
/* 0807CC 8007FBCC AC6A0000 */  sw    $t2, ($v1)
/* 0807D0 8007FBD0 8C8B0174 */  lw    $t3, 0x174($a0)
/* 0807D4 8007FBD4 2442FB40 */  addiu $v0, %lo(D_800DFB40) # addiu $v0, $v0, -0x4c0
/* 0807D8 8007FBD8 AC6B0004 */  sw    $t3, 4($v1)
/* 0807DC 8007FBDC 8C8C0178 */  lw    $t4, 0x178($a0)
/* 0807E0 8007FBE0 3C06800E */  lui   $a2, %hi(D_800DFB8C) # $a2, 0x800e
/* 0807E4 8007FBE4 AC6C000C */  sw    $t4, 0xc($v1)
/* 0807E8 8007FBE8 8C8D0154 */  lw    $t5, 0x154($a0)
/* 0807EC 8007FBEC 24C6FB8C */  addiu $a2, %lo(D_800DFB8C) # addiu $a2, $a2, -0x474
/* 0807F0 8007FBF0 AC6D0010 */  sw    $t5, 0x10($v1)
/* 0807F4 8007FBF4 8C8E0168 */  lw    $t6, 0x168($a0)
/* 0807F8 8007FBF8 3C03800E */  lui   $v1, %hi(D_800DFB5C) # $v1, 0x800e
/* 0807FC 8007FBFC ACAE0000 */  sw    $t6, ($a1)
/* 080800 8007FC00 8C8F017C */  lw    $t7, 0x17c($a0)
/* 080804 8007FC04 2463FB5C */  addiu $v1, %lo(D_800DFB5C) # addiu $v1, $v1, -0x4a4
/* 080808 8007FC08 ACAF0004 */  sw    $t7, 4($a1)
/* 08080C 8007FC0C 8C980180 */  lw    $t8, 0x180($a0)
/* 080810 8007FC10 3C07800E */  lui   $a3, %hi(D_800DFBA4) # $a3, 0x800e
/* 080814 8007FC14 ACB8000C */  sw    $t8, 0xc($a1)
/* 080818 8007FC18 8C990154 */  lw    $t9, 0x154($a0)
/* 08081C 8007FC1C 24E7FBA4 */  addiu $a3, %lo(D_800DFBA4) # addiu $a3, $a3, -0x45c
/* 080820 8007FC20 ACB90010 */  sw    $t9, 0x10($a1)
/* 080824 8007FC24 8C8A0168 */  lw    $t2, 0x168($a0)
/* 080828 8007FC28 3C05800E */  lui   $a1, %hi(D_800DFB74) # $a1, 0x800e
/* 08082C 8007FC2C AD0A0000 */  sw    $t2, ($t0)
/* 080830 8007FC30 8C8B0184 */  lw    $t3, 0x184($a0)
/* 080834 8007FC34 24A5FB74 */  addiu $a1, %lo(D_800DFB74) # addiu $a1, $a1, -0x48c
/* 080838 8007FC38 AD0B0004 */  sw    $t3, 4($t0)
/* 08083C 8007FC3C 8C8C0188 */  lw    $t4, 0x188($a0)
/* 080840 8007FC40 3C01800E */  lui   $at, %hi(D_800E09B0) # $at, 0x800e
/* 080844 8007FC44 AD0C000C */  sw    $t4, 0xc($t0)
/* 080848 8007FC48 8C8D0168 */  lw    $t5, 0x168($a0)
/* 08084C 8007FC4C 3C09800E */  lui   $t1, %hi(D_800E09EC) # $t1, 0x800e
/* 080850 8007FC50 AC4D0000 */  sw    $t5, ($v0)
/* 080854 8007FC54 8C8E018C */  lw    $t6, 0x18c($a0)
/* 080858 8007FC58 252909EC */  addiu $t1, %lo(D_800E09EC) # addiu $t1, $t1, 0x9ec
/* 08085C 8007FC5C AC4E0004 */  sw    $t6, 4($v0)
/* 080860 8007FC60 8C8F0190 */  lw    $t7, 0x190($a0)
/* 080864 8007FC64 3C08800E */  lui   $t0, %hi(D_800E09F8) # $t0, 0x800e
/* 080868 8007FC68 AC4F0008 */  sw    $t7, 8($v0)
/* 08086C 8007FC6C 8C980154 */  lw    $t8, 0x154($a0)
/* 080870 8007FC70 250809F8 */  addiu $t0, %lo(D_800E09F8) # addiu $t0, $t0, 0x9f8
/* 080874 8007FC74 AC580010 */  sw    $t8, 0x10($v0)
/* 080878 8007FC78 8C990168 */  lw    $t9, 0x168($a0)
/* 08087C 8007FC7C 3C02800E */  lui   $v0, %hi(D_800DFBBC) # $v0, 0x800e
/* 080880 8007FC80 AC790000 */  sw    $t9, ($v1)
/* 080884 8007FC84 8C8A0198 */  lw    $t2, 0x198($a0)
/* 080888 8007FC88 2442FBBC */  addiu $v0, %lo(D_800DFBBC) # addiu $v0, $v0, -0x444
/* 08088C 8007FC8C AC6A0004 */  sw    $t2, 4($v1)
/* 080890 8007FC90 8C8B019C */  lw    $t3, 0x19c($a0)
/* 080894 8007FC94 00000000 */  nop   
/* 080898 8007FC98 AC6B0008 */  sw    $t3, 8($v1)
/* 08089C 8007FC9C 8C8C0188 */  lw    $t4, 0x188($a0)
/* 0808A0 8007FCA0 00000000 */  nop   
/* 0808A4 8007FCA4 AC6C0010 */  sw    $t4, 0x10($v1)
/* 0808A8 8007FCA8 8C8D0168 */  lw    $t5, 0x168($a0)
/* 0808AC 8007FCAC 3C03800E */  lui   $v1, %hi(gGameSelectTextElemsWithAdv2) # $v1, 0x800e
/* 0808B0 8007FCB0 ACAD0000 */  sw    $t5, ($a1)
/* 0808B4 8007FCB4 8C8E02E0 */  lw    $t6, 0x2e0($a0)
/* 0808B8 8007FCB8 24630278 */  addiu $v1, %lo(gGameSelectTextElemsWithAdv2) # addiu $v1, $v1, 0x278
/* 0808BC 8007FCBC ACAE0004 */  sw    $t6, 4($a1)
/* 0808C0 8007FCC0 8C8F005C */  lw    $t7, 0x5c($a0)
/* 0808C4 8007FCC4 00000000 */  nop   
/* 0808C8 8007FCC8 ACAF000C */  sw    $t7, 0xc($a1)
/* 0808CC 8007FCCC 8C980154 */  lw    $t8, 0x154($a0)
/* 0808D0 8007FCD0 00000000 */  nop   
/* 0808D4 8007FCD4 ACB80010 */  sw    $t8, 0x10($a1)
/* 0808D8 8007FCD8 8C990264 */  lw    $t9, 0x264($a0)
/* 0808DC 8007FCDC 3C05800E */  lui   $a1, %hi(gGameSelectTextElemsNoAdv2) # $a1, 0x800e
/* 0808E0 8007FCE0 ACD90000 */  sw    $t9, ($a2)
/* 0808E4 8007FCE4 8C8A0268 */  lw    $t2, 0x268($a0)
/* 0808E8 8007FCE8 24A50198 */  addiu $a1, %lo(gGameSelectTextElemsNoAdv2) # addiu $a1, $a1, 0x198
/* 0808EC 8007FCEC ACCA0004 */  sw    $t2, 4($a2)
/* 0808F0 8007FCF0 8C8B026C */  lw    $t3, 0x26c($a0)
/* 0808F4 8007FCF4 00000000 */  nop   
/* 0808F8 8007FCF8 ACCB0008 */  sw    $t3, 8($a2)
/* 0808FC 8007FCFC 8C8C0188 */  lw    $t4, 0x188($a0)
/* 080900 8007FD00 00000000 */  nop   
/* 080904 8007FD04 ACCC0010 */  sw    $t4, 0x10($a2)
/* 080908 8007FD08 8C8D0270 */  lw    $t5, 0x270($a0)
/* 08090C 8007FD0C 3C06800E */  lui   $a2, %hi(gTitleMenuStrings) # $a2, 0x800e
/* 080910 8007FD10 ACED0000 */  sw    $t5, ($a3)
/* 080914 8007FD14 8C8E0274 */  lw    $t6, 0x274($a0)
/* 080918 8007FD18 24C6F7A4 */  addiu $a2, %lo(gTitleMenuStrings) # addiu $a2, $a2, -0x85c
/* 08091C 8007FD1C ACEE0004 */  sw    $t6, 4($a3)
/* 080920 8007FD20 8C8F0278 */  lw    $t7, 0x278($a0)
/* 080924 8007FD24 00000000 */  nop   
/* 080928 8007FD28 ACEF0008 */  sw    $t7, 8($a3)
/* 08092C 8007FD2C 8C980188 */  lw    $t8, 0x188($a0)
/* 080930 8007FD30 00000000 */  nop   
/* 080934 8007FD34 ACF80010 */  sw    $t8, 0x10($a3)
/* 080938 8007FD38 8C9901A0 */  lw    $t9, 0x1a0($a0)
/* 08093C 8007FD3C 3C07800E */  lui   $a3, %hi(D_800E09D8) # $a3, 0x800e
/* 080940 8007FD40 AC590000 */  sw    $t9, ($v0)
/* 080944 8007FD44 8C8A01A4 */  lw    $t2, 0x1a4($a0)
/* 080948 8007FD48 24E709D8 */  addiu $a3, %lo(D_800E09D8) # addiu $a3, $a3, 0x9d8
/* 08094C 8007FD4C AC4A0004 */  sw    $t2, 4($v0)
/* 080950 8007FD50 8C8B01A8 */  lw    $t3, 0x1a8($a0)
/* 080954 8007FD54 00000000 */  nop   
/* 080958 8007FD58 AC4B0008 */  sw    $t3, 8($v0)
/* 08095C 8007FD5C 8C8C01AC */  lw    $t4, 0x1ac($a0)
/* 080960 8007FD60 00000000 */  nop   
/* 080964 8007FD64 AC4C000C */  sw    $t4, 0xc($v0)
/* 080968 8007FD68 8C8D01B0 */  lw    $t5, 0x1b0($a0)
/* 08096C 8007FD6C 00000000 */  nop   
/* 080970 8007FD70 AC4D0010 */  sw    $t5, 0x10($v0)
/* 080974 8007FD74 8C8E01B4 */  lw    $t6, 0x1b4($a0)
/* 080978 8007FD78 00000000 */  nop   
/* 08097C 8007FD7C AC4E0014 */  sw    $t6, 0x14($v0)
/* 080980 8007FD80 8C8F0188 */  lw    $t7, 0x188($a0)
/* 080984 8007FD84 00000000 */  nop   
/* 080988 8007FD88 AC4F001C */  sw    $t7, 0x1c($v0)
/* 08098C 8007FD8C 8C980224 */  lw    $t8, 0x224($a0)
/* 080990 8007FD90 00801025 */  move  $v0, $a0
/* 080994 8007FD94 ACD80000 */  sw    $t8, ($a2)
/* 080998 8007FD98 8C990090 */  lw    $t9, 0x90($a0)
/* 08099C 8007FD9C 00000000 */  nop   
/* 0809A0 8007FDA0 ACD90004 */  sw    $t9, 4($a2)
/* 0809A4 8007FDA4 8C8A0130 */  lw    $t2, 0x130($a0)
/* 0809A8 8007FDA8 3C06800E */  lui   $a2, %hi(D_800E09C4) # $a2, 0x800e
/* 0809AC 8007FDAC ACAA0014 */  sw    $t2, 0x14($a1)
/* 0809B0 8007FDB0 8C8B0130 */  lw    $t3, 0x130($a0)
/* 0809B4 8007FDB4 24C609C4 */  addiu $a2, %lo(D_800E09C4) # addiu $a2, $a2, 0x9c4
/* 0809B8 8007FDB8 ACAB0034 */  sw    $t3, 0x34($a1)
/* 0809BC 8007FDBC 8C8C0238 */  lw    $t4, 0x238($a0)
/* 0809C0 8007FDC0 00000000 */  nop   
/* 0809C4 8007FDC4 ACAC0074 */  sw    $t4, 0x74($a1)
/* 0809C8 8007FDC8 8C8D0240 */  lw    $t5, 0x240($a0)
/* 0809CC 8007FDCC 00000000 */  nop   
/* 0809D0 8007FDD0 ACAD00B4 */  sw    $t5, 0xb4($a1)
/* 0809D4 8007FDD4 8C8E0130 */  lw    $t6, 0x130($a0)
/* 0809D8 8007FDD8 3C05800E */  lui   $a1, %hi(D_800E09B0) # $a1, 0x800e
/* 0809DC 8007FDDC AC6E0014 */  sw    $t6, 0x14($v1)
/* 0809E0 8007FDE0 8C8F0130 */  lw    $t7, 0x130($a0)
/* 0809E4 8007FDE4 24A509B0 */  addiu $a1, %lo(D_800E09B0) # addiu $a1, $a1, 0x9b0
/* 0809E8 8007FDE8 AC6F0034 */  sw    $t7, 0x34($v1)
/* 0809EC 8007FDEC 8C980238 */  lw    $t8, 0x238($a0)
/* 0809F0 8007FDF0 00000000 */  nop   
/* 0809F4 8007FDF4 AC780074 */  sw    $t8, 0x74($v1)
/* 0809F8 8007FDF8 8C99023C */  lw    $t9, 0x23c($a0)
/* 0809FC 8007FDFC 00000000 */  nop   
/* 080A00 8007FE00 AC7900B4 */  sw    $t9, 0xb4($v1)
/* 080A04 8007FE04 8C8A0240 */  lw    $t2, 0x240($a0)
/* 080A08 8007FE08 00000000 */  nop   
/* 080A0C 8007FE0C AC6A00F4 */  sw    $t2, 0xf4($v1)
/* 080A10 8007FE10 8C8B0114 */  lw    $t3, 0x114($a0)
/* 080A14 8007FE14 3C03800E */  lui   $v1, %hi(D_800E09EC) # $v1, 0x800e
/* 080A18 8007FE18 AC2B09B0 */  sw    $t3, %lo(D_800E09B0)($at)
/* 080A1C 8007FE1C 8C8C0110 */  lw    $t4, 0x110($a0)
/* 080A20 8007FE20 3C01800E */  lui   $at, %hi(D_800E09C4) # $at, 0x800e
/* 080A24 8007FE24 AC2C09C4 */  sw    $t4, %lo(D_800E09C4)($at)
/* 080A28 8007FE28 8C8D010C */  lw    $t5, 0x10c($a0)
/* 080A2C 8007FE2C 3C01800E */  lui   $at, %hi(D_800E09D8) # $at, 0x800e
/* 080A30 8007FE30 AC2D09D8 */  sw    $t5, %lo(D_800E09D8)($at)
/* 080A34 8007FE34 8C8E02E0 */  lw    $t6, 0x2e0($a0)
/* 080A38 8007FE38 AD200010 */  sw    $zero, 0x10($t1)
/* 080A3C 8007FE3C AD200014 */  sw    $zero, 0x14($t1)
/* 080A40 8007FE40 246309EC */  addiu $v1, %lo(D_800E09EC) # addiu $v1, $v1, 0x9ec
/* 080A44 8007FE44 AD2E0000 */  sw    $t6, ($t1)
.L8007FE48:
/* 080A48 8007FE48 8C4F02C4 */  lw    $t7, 0x2c4($v0)
/* 080A4C 8007FE4C 24630004 */  addiu $v1, $v1, 4
/* 080A50 8007FE50 ACAF0004 */  sw    $t7, 4($a1)
/* 080A54 8007FE54 8C5802C4 */  lw    $t8, 0x2c4($v0)
/* 080A58 8007FE58 0068082B */  sltu  $at, $v1, $t0
/* 080A5C 8007FE5C ACD80004 */  sw    $t8, 4($a2)
/* 080A60 8007FE60 8C5902C4 */  lw    $t9, 0x2c4($v0)
/* 080A64 8007FE64 24A50004 */  addiu $a1, $a1, 4
/* 080A68 8007FE68 ACF90004 */  sw    $t9, 4($a3)
/* 080A6C 8007FE6C 8C4A02C4 */  lw    $t2, 0x2c4($v0)
/* 080A70 8007FE70 24420004 */  addiu $v0, $v0, 4
/* 080A74 8007FE74 24C60004 */  addiu $a2, $a2, 4
/* 080A78 8007FE78 24E70004 */  addiu $a3, $a3, 4
/* 080A7C 8007FE7C 1420FFF2 */  bnez  $at, .L8007FE48
/* 080A80 8007FE80 AC6A0000 */   sw    $t2, ($v1)
/* 080A84 8007FE84 8D2B0000 */  lw    $t3, ($t1)
/* 080A88 8007FE88 00003025 */  move  $a2, $zero
/* 080A8C 8007FE8C 11600007 */  beqz  $t3, .L8007FEAC
/* 080A90 8007FE90 3C02800E */   lui   $v0, %hi(D_800E0A04) # $v0, 0x800e
/* 080A94 8007FE94 3C03800E */  lui   $v1, %hi(D_800E09EC) # $v1, 0x800e
/* 080A98 8007FE98 246309EC */  addiu $v1, %lo(D_800E09EC) # addiu $v1, $v1, 0x9ec
.L8007FE9C:
/* 080A9C 8007FE9C 8C6C0004 */  lw    $t4, 4($v1)
/* 080AA0 8007FEA0 24C60001 */  addiu $a2, $a2, 1
/* 080AA4 8007FEA4 1580FFFD */  bnez  $t4, .L8007FE9C
/* 080AA8 8007FEA8 24630004 */   addiu $v1, $v1, 4
.L8007FEAC:
/* 080AAC 8007FEAC 8C8D02E4 */  lw    $t5, 0x2e4($a0)
/* 080AB0 8007FEB0 00067080 */  sll   $t6, $a2, 2
/* 080AB4 8007FEB4 012E7821 */  addu  $t7, $t1, $t6
/* 080AB8 8007FEB8 ADED0000 */  sw    $t5, ($t7)
/* 080ABC 8007FEBC 8C98027C */  lw    $t8, 0x27c($a0)
/* 080AC0 8007FEC0 24420A04 */  addiu $v0, %lo(D_800E0A04) # addiu $v0, $v0, 0xa04
/* 080AC4 8007FEC4 AC580000 */  sw    $t8, ($v0)
/* 080AC8 8007FEC8 8C990280 */  lw    $t9, 0x280($a0)
/* 080ACC 8007FECC 3C03800E */  lui   $v1, %hi(D_800E0A14) # $v1, 0x800e
/* 080AD0 8007FED0 AC590004 */  sw    $t9, 4($v0)
/* 080AD4 8007FED4 8C8A0288 */  lw    $t2, 0x288($a0)
/* 080AD8 8007FED8 24630A14 */  addiu $v1, %lo(D_800E0A14) # addiu $v1, $v1, 0xa14
/* 080ADC 8007FEDC AC4A0008 */  sw    $t2, 8($v0)
/* 080AE0 8007FEE0 8C8B027C */  lw    $t3, 0x27c($a0)
/* 080AE4 8007FEE4 3C05800E */  lui   $a1, %hi(gCautionMenuTextElements) # $a1, 0x800e
/* 080AE8 8007FEE8 AC6B0000 */  sw    $t3, ($v1)
/* 080AEC 8007FEEC 8C8C0284 */  lw    $t4, 0x284($a0)
/* 080AF0 8007FEF0 24A5FFD8 */  addiu $a1, %lo(gCautionMenuTextElements) # addiu $a1, $a1, -0x28
/* 080AF4 8007FEF4 AC6C0004 */  sw    $t4, 4($v1)
/* 080AF8 8007FEF8 8C8E0288 */  lw    $t6, 0x288($a0)
/* 080AFC 8007FEFC 3C01800E */  lui   $at, %hi(gCautionMenuTextElements+84) # $at, 0x800e
/* 080B00 8007FF00 AC6E0008 */  sw    $t6, 8($v1)
/* 080B04 8007FF04 8C8D0260 */  lw    $t5, 0x260($a0)
/* 080B08 8007FF08 2482000C */  addiu $v0, $a0, 0xc
/* 080B0C 8007FF0C ACAD0014 */  sw    $t5, 0x14($a1)
/* 080B10 8007FF10 8C8F0260 */  lw    $t7, 0x260($a0)
/* 080B14 8007FF14 3C03800E */  lui   $v1, %hi(gCautionMenuTextElements+96) # $v1, 0x800e
/* 080B18 8007FF18 ACAF0034 */  sw    $t7, 0x34($a1)
/* 080B1C 8007FF1C 8C980298 */  lw    $t8, 0x298($a0)
/* 080B20 8007FF20 24630038 */  addiu $v1, %lo(gCautionMenuTextElements+96) # addiu $v1, $v1, 0x38
/* 080B24 8007FF24 AC38002C */  sw    $t8, %lo(gCautionMenuTextElements+84)($at)
/* 080B28 8007FF28 8C99029C */  lw    $t9, 0x29c($a0)
/* 080B2C 8007FF2C 3C01800E */  lui   $at, %hi(gCautionMenuTextElements+116) # $at, 0x800e
/* 080B30 8007FF30 AC39004C */  sw    $t9, %lo(gCautionMenuTextElements+116)($at)
/* 080B34 8007FF34 8C8A02A0 */  lw    $t2, 0x2a0($a0)
/* 080B38 8007FF38 3C04800E */  lui   $a0, %hi(gCautionMenuTextElements+352) # $a0, 0x800e
/* 080B3C 8007FF3C 3C01800E */  lui   $at, %hi(gCautionMenuTextElements+148) # $at, 0x800e
/* 080B40 8007FF40 24840138 */  addiu $a0, %lo(gCautionMenuTextElements+352) # addiu $a0, $a0, 0x138
/* 080B44 8007FF44 AC2A006C */  sw    $t2, %lo(gCautionMenuTextElements+148)($at)
.L8007FF48:
/* 080B48 8007FF48 8C4B0298 */  lw    $t3, 0x298($v0)
/* 080B4C 8007FF4C 24630080 */  addiu $v1, $v1, 0x80
/* 080B50 8007FF50 AC6BFFD4 */  sw    $t3, -0x2c($v1)
/* 080B54 8007FF54 8C4C029C */  lw    $t4, 0x29c($v0)
/* 080B58 8007FF58 24420010 */  addiu $v0, $v0, 0x10
/* 080B5C 8007FF5C AC6CFFF4 */  sw    $t4, -0xc($v1)
/* 080B60 8007FF60 8C4E0290 */  lw    $t6, 0x290($v0)
/* 080B64 8007FF64 00000000 */  nop   
/* 080B68 8007FF68 AC6E0014 */  sw    $t6, 0x14($v1)
/* 080B6C 8007FF6C 8C4D0294 */  lw    $t5, 0x294($v0)
/* 080B70 8007FF70 1464FFF5 */  bne   $v1, $a0, .L8007FF48
/* 080B74 8007FF74 AC6D0034 */   sw    $t5, 0x34($v1)
/* 080B78 8007FF78 8FBF0014 */  lw    $ra, 0x14($sp)
.L8007FF7C:
/* 080B7C 8007FF7C 27BD0018 */  addiu $sp, $sp, 0x18
/* 080B80 8007FF80 03E00008 */  jr    $ra
/* 080B84 8007FF84 00000000 */   nop   

