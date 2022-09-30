.late_rodata
glabel jpt_800E71D8
.word L8006DF70, L8006E00C, L8006E054, L8006E0E0, L8006DEE8, L8006E0E0, L8006E0E0, L8006E0E0, L8006E0E0, L8006E0E0, L8006E0E0, L8006E0E0, L8006E0E0, L8006DF00

.text
glabel func_8006DCF8
/* 06E8F8 8006DCF8 3C018012 */  lui   $at, %hi(gIsPaused) # $at, 0x8012
/* 06E8FC 8006DCFC 3C0E8012 */  lui   $t6, %hi(gIsLoading) # $t6, 0x8012
/* 06E900 8006DD00 81CE3514 */  lb    $t6, %lo(gIsLoading)($t6)
/* 06E904 8006DD04 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 06E908 8006DD08 A0203515 */  sb    $zero, %lo(gIsPaused)($at)
/* 06E90C 8006DD0C 3C018012 */  lui   $at, %hi(D_80123516) # $at, 0x8012
/* 06E910 8006DD10 AFBF0024 */  sw    $ra, 0x24($sp)
/* 06E914 8006DD14 AFB00020 */  sw    $s0, 0x20($sp)
/* 06E918 8006DD18 AFA40030 */  sw    $a0, 0x30($sp)
/* 06E91C 8006DD1C 15C00008 */  bnez  $t6, .L8006DD40
/* 06E920 8006DD20 A0203516 */   sb    $zero, %lo(D_80123516)($at)
/* 06E924 8006DD24 3C0F8012 */  lui   $t7, %hi(D_801234F0) # $t7, 0x8012
/* 06E928 8006DD28 8DEF34F0 */  lw    $t7, %lo(D_801234F0)($t7)
/* 06E92C 8006DD2C 00000000 */  nop   
/* 06E930 8006DD30 11E00004 */  beqz  $t7, .L8006DD44
/* 06E934 8006DD34 8FB80030 */   lw    $t8, 0x30($sp)
/* 06E938 8006DD38 0C01B716 */  jal   func_8006DC58
/* 06E93C 8006DD3C 00000000 */   nop   
.L8006DD40:
/* 06E940 8006DD40 8FB80030 */  lw    $t8, 0x30($sp)
.L8006DD44:
/* 06E944 8006DD44 3C108012 */  lui   $s0, %hi(gCurrDisplayList) # $s0, 0x8012
/* 06E948 8006DD48 261011F8 */  addiu $s0, %lo(gCurrDisplayList) # addiu $s0, $s0, 0x11f8
/* 06E94C 8006DD4C 3C058012 */  lui   $a1, %hi(gCurrHudMat) # $a1, 0x8012
/* 06E950 8006DD50 3C068012 */  lui   $a2, %hi(gCurrHudVerts) # $a2, 0x8012
/* 06E954 8006DD54 3C078012 */  lui   $a3, %hi(gCurrHudTris) # $a3, 0x8012
/* 06E958 8006DD58 24E71228 */  addiu $a3, %lo(gCurrHudTris) # addiu $a3, $a3, 0x1228
/* 06E95C 8006DD5C 24C61218 */  addiu $a2, %lo(gCurrHudVerts) # addiu $a2, $a2, 0x1218
/* 06E960 8006DD60 24A51208 */  addiu $a1, %lo(gCurrHudMat) # addiu $a1, $a1, 0x1208
/* 06E964 8006DD64 02002025 */  move  $a0, $s0
/* 06E968 8006DD68 0C020569 */  jal   menu_loop
/* 06E96C 8006DD6C AFB80010 */   sw    $t8, 0x10($sp)
/* 06E970 8006DD70 24190001 */  li    $t9, 1
/* 06E974 8006DD74 3C018012 */  lui   $at, %hi(D_801234F0) # $at, 0x8012
/* 06E978 8006DD78 AC3934F0 */  sw    $t9, %lo(D_801234F0)($at)
/* 06E97C 8006DD7C 2401FFFE */  li    $at, -2
/* 06E980 8006DD80 14410004 */  bne   $v0, $at, .L8006DD94
/* 06E984 8006DD84 AFA2002C */   sw    $v0, 0x2c($sp)
/* 06E988 8006DD88 3C018012 */  lui   $at, %hi(D_801234F0) # $at, 0x8012
/* 06E98C 8006DD8C 10000152 */  b     .L8006E2D8
/* 06E990 8006DD90 AC2034F0 */   sw    $zero, %lo(D_801234F0)($at)
.L8006DD94:
/* 06E994 8006DD94 2403FFFF */  li    $v1, -1
/* 06E998 8006DD98 1043003D */  beq   $v0, $v1, .L8006DE90
/* 06E99C 8006DD9C 304C0200 */   andi  $t4, $v0, 0x200
/* 06E9A0 8006DDA0 1180003B */  beqz  $t4, .L8006DE90
/* 06E9A4 8006DDA4 00000000 */   nop   
/* 06E9A8 8006DDA8 0C01B6F9 */  jal   func_8006DBE4
/* 06E9AC 8006DDAC 00000000 */   nop   
/* 06E9B0 8006DDB0 3C0D8012 */  lui   $t5, %hi(gSPTaskNum) # $t5, 0x8012
/* 06E9B4 8006DDB4 8DAD34E8 */  lw    $t5, %lo(gSPTaskNum)($t5)
/* 06E9B8 8006DDB8 3C0F8012 */  lui   $t7, %hi(gDisplayLists) # $t7, 0x8012
/* 06E9BC 8006DDBC 000D7080 */  sll   $t6, $t5, 2
/* 06E9C0 8006DDC0 01EE7821 */  addu  $t7, $t7, $t6
/* 06E9C4 8006DDC4 8DEF11F0 */  lw    $t7, %lo(gDisplayLists)($t7)
/* 06E9C8 8006DDC8 3C19E900 */  lui   $t9, 0xe900
/* 06E9CC 8006DDCC AE0F0000 */  sw    $t7, ($s0)
/* 06E9D0 8006DDD0 25F80008 */  addiu $t8, $t7, 8
/* 06E9D4 8006DDD4 AE180000 */  sw    $t8, ($s0)
/* 06E9D8 8006DDD8 ADE00004 */  sw    $zero, 4($t7)
/* 06E9DC 8006DDDC ADF90000 */  sw    $t9, ($t7)
/* 06E9E0 8006DDE0 8E020000 */  lw    $v0, ($s0)
/* 06E9E4 8006DDE4 3C0DB800 */  lui   $t5, 0xb800
/* 06E9E8 8006DDE8 244C0008 */  addiu $t4, $v0, 8
/* 06E9EC 8006DDEC AE0C0000 */  sw    $t4, ($s0)
/* 06E9F0 8006DDF0 AC400004 */  sw    $zero, 4($v0)
/* 06E9F4 8006DDF4 AC4D0000 */  sw    $t5, ($v0)
/* 06E9F8 8006DDF8 8FAE002C */  lw    $t6, 0x2c($sp)
/* 06E9FC 8006DDFC 3C088012 */  lui   $t0, %hi(D_801234F4) # $t0, 0x8012
/* 06EA00 8006DE00 250834F4 */  addiu $t0, %lo(D_801234F4) # addiu $t0, $t0, 0x34f4
/* 06EA04 8006DE04 31C4007F */  andi  $a0, $t6, 0x7f
/* 06EA08 8006DE08 0C01AC2B */  jal   func_8006B0AC
/* 06EA0C 8006DE0C AD040000 */   sw    $a0, ($t0)
/* 06EA10 8006DE10 3C098012 */  lui   $t1, %hi(D_80123504) # $t1, 0x8012
/* 06EA14 8006DE14 3C0A8012 */  lui   $t2, %hi(gLevelDefaultVehicleID) # $t2, 0x8012
/* 06EA18 8006DE18 3C0B8012 */  lui   $t3, %hi(D_80123508) # $t3, 0x8012
/* 06EA1C 8006DE1C 256B3508 */  addiu $t3, %lo(D_80123508) # addiu $t3, $t3, 0x3508
/* 06EA20 8006DE20 254A3518 */  addiu $t2, %lo(gLevelDefaultVehicleID) # addiu $t2, $t2, 0x3518
/* 06EA24 8006DE24 25293504 */  addiu $t1, %lo(D_80123504) # addiu $t1, $t1, 0x3504
/* 06EA28 8006DE28 24180064 */  li    $t8, 100
/* 06EA2C 8006DE2C AD420000 */  sw    $v0, ($t2)
/* 06EA30 8006DE30 AD200000 */  sw    $zero, ($t1)
/* 06EA34 8006DE34 AD780000 */  sw    $t8, ($t3)
/* 06EA38 8006DE38 3C018012 */  lui   $at, %hi(sRenderContext) # $at, 0x8012
/* 06EA3C 8006DE3C AC2034EC */  sw    $zero, %lo(sRenderContext)($at)
/* 06EA40 8006DE40 3C018012 */  lui   $at, %hi(gIsPaused) # $at, 0x8012
/* 06EA44 8006DE44 A0203515 */  sb    $zero, %lo(gIsPaused)($at)
/* 06EA48 8006DE48 3C018012 */  lui   $at, %hi(D_80123516) # $at, 0x8012
/* 06EA4C 8006DE4C A0203516 */  sb    $zero, %lo(D_80123516)($at)
/* 06EA50 8006DE50 3C038012 */  lui   $v1, %hi(D_80123500) # $v1, 0x8012
/* 06EA54 8006DE54 3C088012 */  lui   $t0, %hi(D_801234F4) # $t0, 0x8012
/* 06EA58 8006DE58 250834F4 */  addiu $t0, %lo(D_801234F4) # addiu $t0, $t0, 0x34f4
/* 06EA5C 8006DE5C 24633500 */  addiu $v1, %lo(D_80123500) # addiu $v1, $v1, 0x3500
/* 06EA60 8006DE60 8C650000 */  lw    $a1, ($v1)
/* 06EA64 8006DE64 8D040000 */  lw    $a0, ($t0)
/* 06EA68 8006DE68 8D470000 */  lw    $a3, ($t2)
/* 06EA6C 8006DE6C 8D260000 */  lw    $a2, ($t1)
/* 06EA70 8006DE70 0C01B2D6 */  jal   load_level_2
/* 06EA74 8006DE74 00000000 */   nop   
/* 06EA78 8006DE78 0C027068 */  jal   get_save_file_index
/* 06EA7C 8006DE7C 00000000 */   nop   
/* 06EA80 8006DE80 0C01BB12 */  jal   func_8006EC48
/* 06EA84 8006DE84 00402025 */   move  $a0, $v0
/* 06EA88 8006DE88 10000114 */  b     .L8006E2DC
/* 06EA8C 8006DE8C 8FBF0024 */   lw    $ra, 0x24($sp)
.L8006DE90:
/* 06EA90 8006DE90 10430099 */  beq   $v0, $v1, .L8006E0F8
/* 06EA94 8006DE94 30590100 */   andi  $t9, $v0, 0x100
/* 06EA98 8006DE98 13200098 */  beqz  $t9, .L8006E0FC
/* 06EA9C 8006DE9C 304C0080 */   andi  $t4, $v0, 0x80
/* 06EAA0 8006DEA0 0C01B305 */  jal   func_8006CC14
/* 06EAA4 8006DEA4 00000000 */   nop   
/* 06EAA8 8006DEA8 8FAC002C */  lw    $t4, 0x2c($sp)
/* 06EAAC 8006DEAC 3C018012 */  lui   $at, %hi(gIsPaused) # $at, 0x8012
/* 06EAB0 8006DEB0 A0203515 */  sb    $zero, %lo(gIsPaused)($at)
/* 06EAB4 8006DEB4 3C018012 */  lui   $at, %hi(D_80123516) # $at, 0x8012
/* 06EAB8 8006DEB8 318D007F */  andi  $t5, $t4, 0x7f
/* 06EABC 8006DEBC A0203516 */  sb    $zero, %lo(D_80123516)($at)
/* 06EAC0 8006DEC0 25AEFFFF */  addiu $t6, $t5, -1
/* 06EAC4 8006DEC4 2DC1000E */  sltiu $at, $t6, 0xe
/* 06EAC8 8006DEC8 10200085 */  beqz  $at, .L8006E0E0
/* 06EACC 8006DECC 000E7080 */   sll   $t6, $t6, 2
/* 06EAD0 8006DED0 3C01800E */  lui   $at, %hi(jpt_800E71D8) # $at, 0x800e
/* 06EAD4 8006DED4 002E0821 */  addu  $at, $at, $t6
/* 06EAD8 8006DED8 8C2E71D8 */  lw    $t6, %lo(jpt_800E71D8)($at)
/* 06EADC 8006DEDC 00000000 */  nop   
/* 06EAE0 8006DEE0 01C00008 */  jr    $t6
/* 06EAE4 8006DEE4 00000000 */   nop   
glabel L8006DEE8
/* 06EAE8 8006DEE8 2404000F */  li    $a0, 15
/* 06EAEC 8006DEEC 2405FFFF */  li    $a1, -1
/* 06EAF0 8006DEF0 0C01B68A */  jal   load_menu_with_level_background
/* 06EAF4 8006DEF4 24060001 */   li    $a2, 1
/* 06EAF8 8006DEF8 100000F8 */  b     .L8006E2DC
/* 06EAFC 8006DEFC 8FBF0024 */   lw    $ra, 0x24($sp)
glabel L8006DF00
/* 06EB00 8006DF00 3C088012 */  lui   $t0, %hi(D_801234F4) # $t0, 0x8012
/* 06EB04 8006DF04 3C098012 */  lui   $t1, %hi(D_80123504) # $t1, 0x8012
/* 06EB08 8006DF08 3C0B8012 */  lui   $t3, %hi(D_80123508) # $t3, 0x8012
/* 06EB0C 8006DF0C 256B3508 */  addiu $t3, %lo(D_80123508) # addiu $t3, $t3, 0x3508
/* 06EB10 8006DF10 25293504 */  addiu $t1, %lo(D_80123504) # addiu $t1, $t1, 0x3504
/* 06EB14 8006DF14 250834F4 */  addiu $t0, %lo(D_801234F4) # addiu $t0, $t0, 0x34f4
/* 06EB18 8006DF18 240F0064 */  li    $t7, 100
/* 06EB1C 8006DF1C AD000000 */  sw    $zero, ($t0)
/* 06EB20 8006DF20 AD200000 */  sw    $zero, ($t1)
/* 06EB24 8006DF24 AD6F0000 */  sw    $t7, ($t3)
/* 06EB28 8006DF28 3C018012 */  lui   $at, %hi(sRenderContext) # $at, 0x8012
/* 06EB2C 8006DF2C AC2034EC */  sw    $zero, %lo(sRenderContext)($at)
/* 06EB30 8006DF30 3C038012 */  lui   $v1, %hi(D_80123500) # $v1, 0x8012
/* 06EB34 8006DF34 3C0A8012 */  lui   $t2, %hi(gLevelDefaultVehicleID) # $t2, 0x8012
/* 06EB38 8006DF38 254A3518 */  addiu $t2, %lo(gLevelDefaultVehicleID) # addiu $t2, $t2, 0x3518
/* 06EB3C 8006DF3C 24633500 */  addiu $v1, %lo(D_80123500) # addiu $v1, $v1, 0x3500
/* 06EB40 8006DF40 8C650000 */  lw    $a1, ($v1)
/* 06EB44 8006DF44 8D470000 */  lw    $a3, ($t2)
/* 06EB48 8006DF48 8D260000 */  lw    $a2, ($t1)
/* 06EB4C 8006DF4C 8D040000 */  lw    $a0, ($t0)
/* 06EB50 8006DF50 0C01B2D6 */  jal   load_level_2
/* 06EB54 8006DF54 00000000 */   nop   
/* 06EB58 8006DF58 0C027068 */  jal   get_save_file_index
/* 06EB5C 8006DF5C 00000000 */   nop   
/* 06EB60 8006DF60 0C01BB12 */  jal   func_8006EC48
/* 06EB64 8006DF64 00402025 */   move  $a0, $v0
/* 06EB68 8006DF68 100000DC */  b     .L8006E2DC
/* 06EB6C 8006DF6C 8FBF0024 */   lw    $ra, 0x24($sp)
glabel L8006DF70
/* 06EB70 8006DF70 3C058012 */  lui   $a1, %hi(D_80121250) # $a1, 0x8012
/* 06EB74 8006DF74 24A51250 */  addiu $a1, %lo(D_80121250) # addiu $a1, $a1, 0x1250
/* 06EB78 8006DF78 80B80000 */  lb    $t8, ($a1)
/* 06EB7C 8006DF7C 3C088012 */  lui   $t0, %hi(D_801234F4) # $t0, 0x8012
/* 06EB80 8006DF80 3C098012 */  lui   $t1, %hi(D_80123504) # $t1, 0x8012
/* 06EB84 8006DF84 3C0B8012 */  lui   $t3, %hi(D_80123508) # $t3, 0x8012
/* 06EB88 8006DF88 256B3508 */  addiu $t3, %lo(D_80123508) # addiu $t3, $t3, 0x3508
/* 06EB8C 8006DF8C 25293504 */  addiu $t1, %lo(D_80123504) # addiu $t1, $t1, 0x3504
/* 06EB90 8006DF90 250834F4 */  addiu $t0, %lo(D_801234F4) # addiu $t0, $t0, 0x34f4
/* 06EB94 8006DF94 24190064 */  li    $t9, 100
/* 06EB98 8006DF98 AD200000 */  sw    $zero, ($t1)
/* 06EB9C 8006DF9C AD790000 */  sw    $t9, ($t3)
/* 06EBA0 8006DFA0 3C018012 */  lui   $at, %hi(sRenderContext) # $at, 0x8012
/* 06EBA4 8006DFA4 AD180000 */  sw    $t8, ($t0)
/* 06EBA8 8006DFA8 AC2034EC */  sw    $zero, %lo(sRenderContext)($at)
/* 06EBAC 8006DFAC 80A2000F */  lb    $v0, 0xf($a1)
/* 06EBB0 8006DFB0 80A30001 */  lb    $v1, 1($a1)
/* 06EBB4 8006DFB4 04400002 */  bltz  $v0, .L8006DFC0
/* 06EBB8 8006DFB8 3C0A8012 */   lui   $t2, %hi(gLevelDefaultVehicleID) # $t2, 0x8012
/* 06EBBC 8006DFBC AD220000 */  sw    $v0, ($t1)
.L8006DFC0:
/* 06EBC0 8006DFC0 00A36021 */  addu  $t4, $a1, $v1
/* 06EBC4 8006DFC4 81820008 */  lb    $v0, 8($t4)
/* 06EBC8 8006DFC8 3C038012 */  lui   $v1, %hi(D_80123500) # $v1, 0x8012
/* 06EBCC 8006DFCC 04400002 */  bltz  $v0, .L8006DFD8
/* 06EBD0 8006DFD0 24633500 */   addiu $v1, %lo(D_80123500) # addiu $v1, $v1, 0x3500
/* 06EBD4 8006DFD4 AD620000 */  sw    $v0, ($t3)
.L8006DFD8:
/* 06EBD8 8006DFD8 254A3518 */  addiu $t2, %lo(gLevelDefaultVehicleID) # addiu $t2, $t2, 0x3518
/* 06EBDC 8006DFDC 8D470000 */  lw    $a3, ($t2)
/* 06EBE0 8006DFE0 8D040000 */  lw    $a0, ($t0)
/* 06EBE4 8006DFE4 8C650000 */  lw    $a1, ($v1)
/* 06EBE8 8006DFE8 8D260000 */  lw    $a2, ($t1)
/* 06EBEC 8006DFEC 0C01B2D6 */  jal   load_level_2
/* 06EBF0 8006DFF0 00000000 */   nop   
/* 06EBF4 8006DFF4 0C027068 */  jal   get_save_file_index
/* 06EBF8 8006DFF8 00000000 */   nop   
/* 06EBFC 8006DFFC 0C01BB12 */  jal   func_8006EC48
/* 06EC00 8006E000 00402025 */   move  $a0, $v0
/* 06EC04 8006E004 100000B5 */  b     .L8006E2DC
/* 06EC08 8006E008 8FBF0024 */   lw    $ra, 0x24($sp)
glabel L8006E00C
/* 06EC0C 8006E00C 3C018012 */  lui   $at, %hi(sRenderContext) # $at, 0x8012
/* 06EC10 8006E010 AC2034EC */  sw    $zero, %lo(sRenderContext)($at)
/* 06EC14 8006E014 3C038012 */  lui   $v1, %hi(D_80123500) # $v1, 0x8012
/* 06EC18 8006E018 3C088012 */  lui   $t0, %hi(D_801234F4) # $t0, 0x8012
/* 06EC1C 8006E01C 3C098012 */  lui   $t1, %hi(D_80123504) # $t1, 0x8012
/* 06EC20 8006E020 3C0A8012 */  lui   $t2, %hi(gLevelDefaultVehicleID) # $t2, 0x8012
/* 06EC24 8006E024 254A3518 */  addiu $t2, %lo(gLevelDefaultVehicleID) # addiu $t2, $t2, 0x3518
/* 06EC28 8006E028 25293504 */  addiu $t1, %lo(D_80123504) # addiu $t1, $t1, 0x3504
/* 06EC2C 8006E02C 250834F4 */  addiu $t0, %lo(D_801234F4) # addiu $t0, $t0, 0x34f4
/* 06EC30 8006E030 24633500 */  addiu $v1, %lo(D_80123500) # addiu $v1, $v1, 0x3500
/* 06EC34 8006E034 8C650000 */  lw    $a1, ($v1)
/* 06EC38 8006E038 8D040000 */  lw    $a0, ($t0)
/* 06EC3C 8006E03C 8D260000 */  lw    $a2, ($t1)
/* 06EC40 8006E040 8D470000 */  lw    $a3, ($t2)
/* 06EC44 8006E044 0C01B2D6 */  jal   load_level_2
/* 06EC48 8006E048 00000000 */   nop   
/* 06EC4C 8006E04C 100000A3 */  b     .L8006E2DC
/* 06EC50 8006E050 8FBF0024 */   lw    $ra, 0x24($sp)
glabel L8006E054
/* 06EC54 8006E054 3C058012 */  lui   $a1, %hi(D_80121250) # $a1, 0x8012
/* 06EC58 8006E058 3C018012 */  lui   $at, %hi(sRenderContext) # $at, 0x8012
/* 06EC5C 8006E05C 24A51250 */  addiu $a1, %lo(D_80121250) # addiu $a1, $a1, 0x1250
/* 06EC60 8006E060 AC2034EC */  sw    $zero, %lo(sRenderContext)($at)
/* 06EC64 8006E064 80AF0001 */  lb    $t7, 1($a1)
/* 06EC68 8006E068 80A40000 */  lb    $a0, ($a1)
/* 06EC6C 8006E06C 00AFC021 */  addu  $t8, $a1, $t7
/* 06EC70 8006E070 80AE000F */  lb    $t6, 0xf($a1)
/* 06EC74 8006E074 83190008 */  lb    $t9, 8($t8)
/* 06EC78 8006E078 3C088012 */  lui   $t0, %hi(D_801234F4) # $t0, 0x8012
/* 06EC7C 8006E07C 3C098012 */  lui   $t1, %hi(D_80123504) # $t1, 0x8012
/* 06EC80 8006E080 3C0B8012 */  lui   $t3, %hi(D_80123508) # $t3, 0x8012
/* 06EC84 8006E084 256B3508 */  addiu $t3, %lo(D_80123508) # addiu $t3, $t3, 0x3508
/* 06EC88 8006E088 25293504 */  addiu $t1, %lo(D_80123504) # addiu $t1, $t1, 0x3504
/* 06EC8C 8006E08C 250834F4 */  addiu $t0, %lo(D_801234F4) # addiu $t0, $t0, 0x34f4
/* 06EC90 8006E090 AD040000 */  sw    $a0, ($t0)
/* 06EC94 8006E094 AD2E0000 */  sw    $t6, ($t1)
/* 06EC98 8006E098 0C01AC2B */  jal   func_8006B0AC
/* 06EC9C 8006E09C AD790000 */   sw    $t9, ($t3)
/* 06ECA0 8006E0A0 3C038012 */  lui   $v1, %hi(D_80123500) # $v1, 0x8012
/* 06ECA4 8006E0A4 3C088012 */  lui   $t0, %hi(D_801234F4) # $t0, 0x8012
/* 06ECA8 8006E0A8 3C098012 */  lui   $t1, %hi(D_80123504) # $t1, 0x8012
/* 06ECAC 8006E0AC 25293504 */  addiu $t1, %lo(D_80123504) # addiu $t1, $t1, 0x3504
/* 06ECB0 8006E0B0 250834F4 */  addiu $t0, %lo(D_801234F4) # addiu $t0, $t0, 0x34f4
/* 06ECB4 8006E0B4 24633500 */  addiu $v1, %lo(D_80123500) # addiu $v1, $v1, 0x3500
/* 06ECB8 8006E0B8 3C0A8012 */  lui   $t2, %hi(gLevelDefaultVehicleID) # $t2, 0x8012
/* 06ECBC 8006E0BC 254A3518 */  addiu $t2, %lo(gLevelDefaultVehicleID) # addiu $t2, $t2, 0x3518
/* 06ECC0 8006E0C0 8C650000 */  lw    $a1, ($v1)
/* 06ECC4 8006E0C4 8D040000 */  lw    $a0, ($t0)
/* 06ECC8 8006E0C8 8D260000 */  lw    $a2, ($t1)
/* 06ECCC 8006E0CC AD420000 */  sw    $v0, ($t2)
/* 06ECD0 8006E0D0 0C01B2D6 */  jal   load_level_2
/* 06ECD4 8006E0D4 00403825 */   move  $a3, $v0
/* 06ECD8 8006E0D8 10000080 */  b     .L8006E2DC
/* 06ECDC 8006E0DC 8FBF0024 */   lw    $ra, 0x24($sp)
.L8006E0E0:
glabel L8006E0E0
/* 06ECE0 8006E0E0 00002025 */  move  $a0, $zero
/* 06ECE4 8006E0E4 2405FFFF */  li    $a1, -1
/* 06ECE8 8006E0E8 0C01B68A */  jal   load_menu_with_level_background
/* 06ECEC 8006E0EC 00003025 */   move  $a2, $zero
/* 06ECF0 8006E0F0 1000007A */  b     .L8006E2DC
/* 06ECF4 8006E0F4 8FBF0024 */   lw    $ra, 0x24($sp)
.L8006E0F8:
/* 06ECF8 8006E0F8 304C0080 */  andi  $t4, $v0, 0x80
.L8006E0FC:
/* 06ECFC 8006E0FC 11800047 */  beqz  $t4, .L8006E21C
/* 06ED00 8006E100 00000000 */   nop   
/* 06ED04 8006E104 10430045 */  beq   $v0, $v1, .L8006E21C
/* 06ED08 8006E108 00000000 */   nop   
/* 06ED0C 8006E10C 0C01B6F9 */  jal   func_8006DBE4
/* 06ED10 8006E110 00000000 */   nop   
/* 06ED14 8006E114 3C0D8012 */  lui   $t5, %hi(gSPTaskNum) # $t5, 0x8012
/* 06ED18 8006E118 8DAD34E8 */  lw    $t5, %lo(gSPTaskNum)($t5)
/* 06ED1C 8006E11C 3C0F8012 */  lui   $t7, %hi(gDisplayLists) # $t7, 0x8012
/* 06ED20 8006E120 000D7080 */  sll   $t6, $t5, 2
/* 06ED24 8006E124 01EE7821 */  addu  $t7, $t7, $t6
/* 06ED28 8006E128 8DEF11F0 */  lw    $t7, %lo(gDisplayLists)($t7)
/* 06ED2C 8006E12C 8FAA002C */  lw    $t2, 0x2c($sp)
/* 06ED30 8006E130 AE0F0000 */  sw    $t7, ($s0)
/* 06ED34 8006E134 25F80008 */  addiu $t8, $t7, 8
/* 06ED38 8006E138 AE180000 */  sw    $t8, ($s0)
/* 06ED3C 8006E13C 3C19E900 */  lui   $t9, 0xe900
/* 06ED40 8006E140 ADF90000 */  sw    $t9, ($t7)
/* 06ED44 8006E144 ADE00004 */  sw    $zero, 4($t7)
/* 06ED48 8006E148 8E020000 */  lw    $v0, ($s0)
/* 06ED4C 8006E14C 3C058012 */  lui   $a1, %hi(D_80121250) # $a1, 0x8012
/* 06ED50 8006E150 244C0008 */  addiu $t4, $v0, 8
/* 06ED54 8006E154 AE0C0000 */  sw    $t4, ($s0)
/* 06ED58 8006E158 3C088012 */  lui   $t0, %hi(D_801234F4) # $t0, 0x8012
/* 06ED5C 8006E15C 3C0DB800 */  lui   $t5, 0xb800
/* 06ED60 8006E160 250834F4 */  addiu $t0, %lo(D_801234F4) # addiu $t0, $t0, 0x34f4
/* 06ED64 8006E164 24A51250 */  addiu $a1, %lo(D_80121250) # addiu $a1, $a1, 0x1250
/* 06ED68 8006E168 AC4D0000 */  sw    $t5, ($v0)
/* 06ED6C 8006E16C AC400004 */  sw    $zero, 4($v0)
/* 06ED70 8006E170 8D0F0000 */  lw    $t7, ($t0)
/* 06ED74 8006E174 314E007F */  andi  $t6, $t2, 0x7f
/* 06ED78 8006E178 A0AE0001 */  sb    $t6, 1($a1)
/* 06ED7C 8006E17C 00AE1821 */  addu  $v1, $a1, $t6
/* 06ED80 8006E180 A0AF0000 */  sb    $t7, ($a1)
/* 06ED84 8006E184 80780002 */  lb    $t8, 2($v1)
/* 06ED88 8006E188 80790004 */  lb    $t9, 4($v1)
/* 06ED8C 8006E18C 3C098012 */  lui   $t1, %hi(D_80123504) # $t1, 0x8012
/* 06ED90 8006E190 25293504 */  addiu $t1, %lo(D_80123504) # addiu $t1, $t1, 0x3504
/* 06ED94 8006E194 3C018012 */  lui   $at, %hi(sRenderContext) # $at, 0x8012
/* 06ED98 8006E198 AD180000 */  sw    $t8, ($t0)
/* 06ED9C 8006E19C AD390000 */  sw    $t9, ($t1)
/* 06EDA0 8006E1A0 AC2034EC */  sw    $zero, %lo(sRenderContext)($at)
/* 06EDA4 8006E1A4 806C000C */  lb    $t4, 0xc($v1)
/* 06EDA8 8006E1A8 3C0B8012 */  lui   $t3, %hi(D_80123508) # $t3, 0x8012
/* 06EDAC 8006E1AC 256B3508 */  addiu $t3, %lo(D_80123508) # addiu $t3, $t3, 0x3508
/* 06EDB0 8006E1B0 00002025 */  move  $a0, $zero
/* 06EDB4 8006E1B4 0C027094 */  jal   get_player_selected_vehicle
/* 06EDB8 8006E1B8 AD6C0000 */   sw    $t4, ($t3)
/* 06EDBC 8006E1BC 3C108012 */  lui   $s0, %hi(gSettingsPtr) # $s0, 0x8012
/* 06EDC0 8006E1C0 26103510 */  addiu $s0, %lo(gSettingsPtr) # addiu $s0, $s0, 0x3510
/* 06EDC4 8006E1C4 8E0D0000 */  lw    $t5, ($s0)
/* 06EDC8 8006E1C8 3C088012 */  lui   $t0, %hi(D_801234F4) # $t0, 0x8012
/* 06EDCC 8006E1CC 91AE004A */  lbu   $t6, 0x4a($t5)
/* 06EDD0 8006E1D0 3C098012 */  lui   $t1, %hi(D_80123504) # $t1, 0x8012
/* 06EDD4 8006E1D4 25293504 */  addiu $t1, %lo(D_80123504) # addiu $t1, $t1, 0x3504
/* 06EDD8 8006E1D8 250834F4 */  addiu $t0, %lo(D_801234F4) # addiu $t0, $t0, 0x34f4
/* 06EDDC 8006E1DC 3C038012 */  lui   $v1, %hi(D_80123500) # $v1, 0x8012
/* 06EDE0 8006E1E0 24633500 */  addiu $v1, %lo(D_80123500) # addiu $v1, $v1, 0x3500
/* 06EDE4 8006E1E4 8D040000 */  lw    $a0, ($t0)
/* 06EDE8 8006E1E8 8D260000 */  lw    $a2, ($t1)
/* 06EDEC 8006E1EC 25C5FFFF */  addiu $a1, $t6, -1
/* 06EDF0 8006E1F0 AC650000 */  sw    $a1, ($v1)
/* 06EDF4 8006E1F4 0C01B2D6 */  jal   load_level_2
/* 06EDF8 8006E1F8 00403825 */   move  $a3, $v0
/* 06EDFC 8006E1FC 3C188012 */  lui   $t8, %hi(D_8012351C) # $t8, 0x8012
/* 06EE00 8006E200 8F18351C */  lw    $t8, %lo(D_8012351C)($t8)
/* 06EE04 8006E204 3C0A8012 */  lui   $t2, %hi(gLevelDefaultVehicleID) # $t2, 0x8012
/* 06EE08 8006E208 3C018012 */  lui   $at, %hi(D_801234FC) # $at, 0x8012
/* 06EE0C 8006E20C 254A3518 */  addiu $t2, %lo(gLevelDefaultVehicleID) # addiu $t2, $t2, 0x3518
/* 06EE10 8006E210 AC2034FC */  sw    $zero, %lo(D_801234FC)($at)
/* 06EE14 8006E214 10000030 */  b     .L8006E2D8
/* 06EE18 8006E218 AD580000 */   sw    $t8, ($t2)
.L8006E21C:
/* 06EE1C 8006E21C 1840002F */  blez  $v0, .L8006E2DC
/* 06EE20 8006E220 8FBF0024 */   lw    $ra, 0x24($sp)
/* 06EE24 8006E224 0C01B6F9 */  jal   func_8006DBE4
/* 06EE28 8006E228 00000000 */   nop   
/* 06EE2C 8006E22C 3C198012 */  lui   $t9, %hi(gSPTaskNum) # $t9, 0x8012
/* 06EE30 8006E230 8F3934E8 */  lw    $t9, %lo(gSPTaskNum)($t9)
/* 06EE34 8006E234 3C0D8012 */  lui   $t5, %hi(gDisplayLists) # $t5, 0x8012
/* 06EE38 8006E238 00196080 */  sll   $t4, $t9, 2
/* 06EE3C 8006E23C 01AC6821 */  addu  $t5, $t5, $t4
/* 06EE40 8006E240 8DAD11F0 */  lw    $t5, %lo(gDisplayLists)($t5)
/* 06EE44 8006E244 3C0FE900 */  lui   $t7, 0xe900
/* 06EE48 8006E248 AE0D0000 */  sw    $t5, ($s0)
/* 06EE4C 8006E24C 25AE0008 */  addiu $t6, $t5, 8
/* 06EE50 8006E250 AE0E0000 */  sw    $t6, ($s0)
/* 06EE54 8006E254 ADA00004 */  sw    $zero, 4($t5)
/* 06EE58 8006E258 ADAF0000 */  sw    $t7, ($t5)
/* 06EE5C 8006E25C 8E020000 */  lw    $v0, ($s0)
/* 06EE60 8006E260 3C19B800 */  lui   $t9, 0xb800
/* 06EE64 8006E264 24580008 */  addiu $t8, $v0, 8
/* 06EE68 8006E268 AE180000 */  sw    $t8, ($s0)
/* 06EE6C 8006E26C AC400004 */  sw    $zero, 4($v0)
/* 06EE70 8006E270 AC590000 */  sw    $t9, ($v0)
/* 06EE74 8006E274 3C0A8012 */  lui   $t2, %hi(gLevelDefaultVehicleID) # $t2, 0x8012
/* 06EE78 8006E278 3C018012 */  lui   $at, %hi(sRenderContext) # $at, 0x8012
/* 06EE7C 8006E27C 254A3518 */  addiu $t2, %lo(gLevelDefaultVehicleID) # addiu $t2, $t2, 0x3518
/* 06EE80 8006E280 AC2034EC */  sw    $zero, %lo(sRenderContext)($at)
/* 06EE84 8006E284 8D460000 */  lw    $a2, ($t2)
/* 06EE88 8006E288 8FA4002C */  lw    $a0, 0x2c($sp)
/* 06EE8C 8006E28C 0C01B2B9 */  jal   func_8006CAE4
/* 06EE90 8006E290 2405FFFF */   li    $a1, -1
/* 06EE94 8006E294 3C108012 */  lui   $s0, %hi(gSettingsPtr) # $s0, 0x8012
/* 06EE98 8006E298 26103510 */  addiu $s0, %lo(gSettingsPtr) # addiu $s0, $s0, 0x3510
/* 06EE9C 8006E29C 8E0C0000 */  lw    $t4, ($s0)
/* 06EEA0 8006E2A0 00000000 */  nop   
/* 06EEA4 8006E2A4 918D004B */  lbu   $t5, 0x4b($t4)
/* 06EEA8 8006E2A8 00000000 */  nop   
/* 06EEAC 8006E2AC 11A0000B */  beqz  $t5, .L8006E2DC
/* 06EEB0 8006E2B0 8FBF0024 */   lw    $ra, 0x24($sp)
/* 06EEB4 8006E2B4 0C0270B4 */  jal   is_in_tracks_mode
/* 06EEB8 8006E2B8 00000000 */   nop   
/* 06EEBC 8006E2BC 14400007 */  bnez  $v0, .L8006E2DC
/* 06EEC0 8006E2C0 8FBF0024 */   lw    $ra, 0x24($sp)
/* 06EEC4 8006E2C4 0C0002CA */  jal   func_80000B28
/* 06EEC8 8006E2C8 00000000 */   nop   
/* 06EECC 8006E2CC 8E0E0000 */  lw    $t6, ($s0)
/* 06EED0 8006E2D0 00000000 */  nop   
/* 06EED4 8006E2D4 A1C0004B */  sb    $zero, 0x4b($t6)
.L8006E2D8:
/* 06EED8 8006E2D8 8FBF0024 */  lw    $ra, 0x24($sp)
.L8006E2DC:
/* 06EEDC 8006E2DC 8FB00020 */  lw    $s0, 0x20($sp)
/* 06EEE0 8006E2E0 03E00008 */  jr    $ra
/* 06EEE4 8006E2E4 27BD0030 */   addiu $sp, $sp, 0x30

