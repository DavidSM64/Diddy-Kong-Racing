glabel func_8009ECF0
/* 09F8F0 8009ECF0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 09F8F4 8009ECF4 AFBF0024 */  sw    $ra, 0x24($sp)
/* 09F8F8 8009ECF8 AFB20020 */  sw    $s2, 0x20($sp)
/* 09F8FC 8009ECFC AFB1001C */  sw    $s1, 0x1c($sp)
/* 09F900 8009ED00 AFB00018 */  sw    $s0, 0x18($sp)
/* 09F904 8009ED04 0C019884 */  jal   get_viewport_count
/* 09F908 8009ED08 AFA40028 */   sw    $a0, 0x28($sp)
/* 09F90C 8009ED0C 3C038012 */  lui   $v1, %hi(D_80126D0C) # $v1, 0x8012
/* 09F910 8009ED10 24636D0C */  addiu $v1, %lo(D_80126D0C) # addiu $v1, $v1, 0x6d0c
/* 09F914 8009ED14 AC620000 */  sw    $v0, ($v1)
/* 09F918 8009ED18 0C01994B */  jal   set_active_viewports_and_object_stack_cap
/* 09F91C 8009ED1C 00402025 */   move  $a0, $v0
/* 09F920 8009ED20 3C018012 */  lui   $at, %hi(D_80126D37) # $at, 0x8012
/* 09F924 8009ED24 0C01BAA4 */  jal   get_settings
/* 09F928 8009ED28 A0226D37 */   sb    $v0, %lo(D_80126D37)($at)
/* 09F92C 8009ED2C 3C018012 */  lui   $at, %hi(D_80127184) # $at, 0x8012
/* 09F930 8009ED30 0C003877 */  jal   check_if_silver_coin_race
/* 09F934 8009ED34 AC227184 */   sw    $v0, %lo(D_80127184)($at)
/* 09F938 8009ED38 3C018012 */  lui   $at, %hi(D_80127188) # $at, 0x8012
/* 09F93C 8009ED3C A0227188 */  sb    $v0, %lo(D_80127188)($at)
/* 09F940 8009ED40 0C01DB16 */  jal   load_asset_section_from_rom
/* 09F944 8009ED44 24040011 */   li    $a0, 17
/* 09F948 8009ED48 3C068012 */  lui   $a2, %hi(D_80126CF8) # $a2, 0x8012
/* 09F94C 8009ED4C 3C118012 */  lui   $s1, %hi(D_80126CF0) # $s1, 0x8012
/* 09F950 8009ED50 26316CF0 */  addiu $s1, %lo(D_80126CF0) # addiu $s1, $s1, 0x6cf0
/* 09F954 8009ED54 24C66CF8 */  addiu $a2, %lo(D_80126CF8) # addiu $a2, $a2, 0x6cf8
/* 09F958 8009ED58 00007040 */  sll   $t6, $zero, 1
/* 09F95C 8009ED5C AE220000 */  sw    $v0, ($s1)
/* 09F960 8009ED60 ACC00000 */  sw    $zero, ($a2)
/* 09F964 8009ED64 004E7821 */  addu  $t7, $v0, $t6
/* 09F968 8009ED68 85F80000 */  lh    $t8, ($t7)
/* 09F96C 8009ED6C 2412FFFF */  li    $s2, -1
/* 09F970 8009ED70 00401825 */  move  $v1, $v0
/* 09F974 8009ED74 12580009 */  beq   $s2, $t8, .L8009ED9C
/* 09F978 8009ED78 00008025 */   move  $s0, $zero
/* 09F97C 8009ED7C 26190001 */  addiu $t9, $s0, 1
.L8009ED80:
/* 09F980 8009ED80 00194040 */  sll   $t0, $t9, 1
/* 09F984 8009ED84 00684821 */  addu  $t1, $v1, $t0
/* 09F988 8009ED88 ACD90000 */  sw    $t9, ($a2)
/* 09F98C 8009ED8C 852A0000 */  lh    $t2, ($t1)
/* 09F990 8009ED90 03208025 */  move  $s0, $t9
/* 09F994 8009ED94 164AFFFA */  bne   $s2, $t2, .L8009ED80
/* 09F998 8009ED98 26190001 */   addiu $t9, $s0, 1
.L8009ED9C:
/* 09F99C 8009ED9C 00102080 */  sll   $a0, $s0, 2
/* 09F9A0 8009EDA0 00902021 */  addu  $a0, $a0, $s0
/* 09F9A4 8009EDA4 0C01C327 */  jal   allocate_from_main_pool_safe
/* 09F9A8 8009EDA8 3405FFFF */   li    $a1, 65535
/* 09F9AC 8009EDAC 3C068012 */  lui   $a2, %hi(D_80126CF8) # $a2, 0x8012
/* 09F9B0 8009EDB0 24C66CF8 */  addiu $a2, %lo(D_80126CF8) # addiu $a2, $a2, 0x6cf8
/* 09F9B4 8009EDB4 8CD00000 */  lw    $s0, ($a2)
/* 09F9B8 8009EDB8 3C048012 */  lui   $a0, %hi(D_80126CD8) # $a0, 0x8012
/* 09F9BC 8009EDBC 3C078012 */  lui   $a3, %hi(D_80126CF4) # $a3, 0x8012
/* 09F9C0 8009EDC0 00105880 */  sll   $t3, $s0, 2
/* 09F9C4 8009EDC4 24E76CF4 */  addiu $a3, %lo(D_80126CF4) # addiu $a3, $a3, 0x6cf4
/* 09F9C8 8009EDC8 24846CD8 */  addiu $a0, %lo(D_80126CD8) # addiu $a0, $a0, 0x6cd8
/* 09F9CC 8009EDCC 01626821 */  addu  $t5, $t3, $v0
/* 09F9D0 8009EDD0 ACE20000 */  sw    $v0, ($a3)
/* 09F9D4 8009EDD4 AC8D0000 */  sw    $t5, ($a0)
/* 09F9D8 8009EDD8 1A00000F */  blez  $s0, .L8009EE18
/* 09F9DC 8009EDDC 00001825 */   move  $v1, $zero
/* 09F9E0 8009EDE0 00001025 */  move  $v0, $zero
.L8009EDE4:
/* 09F9E4 8009EDE4 8C8E0000 */  lw    $t6, ($a0)
/* 09F9E8 8009EDE8 00000000 */  nop   
/* 09F9EC 8009EDEC 01C37821 */  addu  $t7, $t6, $v1
/* 09F9F0 8009EDF0 A1E00000 */  sb    $zero, ($t7)
/* 09F9F4 8009EDF4 8CF80000 */  lw    $t8, ($a3)
/* 09F9F8 8009EDF8 24630001 */  addiu $v1, $v1, 1
/* 09F9FC 8009EDFC 0302C821 */  addu  $t9, $t8, $v0
/* 09FA00 8009EE00 AF200000 */  sw    $zero, ($t9)
/* 09FA04 8009EE04 8CC80000 */  lw    $t0, ($a2)
/* 09FA08 8009EE08 24420004 */  addiu $v0, $v0, 4
/* 09FA0C 8009EE0C 0068082A */  slt   $at, $v1, $t0
/* 09FA10 8009EE10 1420FFF4 */  bnez  $at, .L8009EDE4
/* 09FA14 8009EE14 00000000 */   nop   
.L8009EE18:
/* 09FA18 8009EE18 8E290000 */  lw    $t1, ($s1)
/* 09FA1C 8009EE1C 24050001 */  li    $a1, 1
/* 09FA20 8009EE20 85240002 */  lh    $a0, 2($t1)
/* 09FA24 8009EE24 00000000 */  nop   
/* 09FA28 8009EE28 308A3FFF */  andi  $t2, $a0, 0x3fff
/* 09FA2C 8009EE2C 0C01F04B */  jal   func_8007C12C
/* 09FA30 8009EE30 01402025 */   move  $a0, $t2
/* 09FA34 8009EE34 3C078012 */  lui   $a3, %hi(D_80126CF4) # $a3, 0x8012
/* 09FA38 8009EE38 24E76CF4 */  addiu $a3, %lo(D_80126CF4) # addiu $a3, $a3, 0x6cf4
/* 09FA3C 8009EE3C 8CEB0000 */  lw    $t3, ($a3)
/* 09FA40 8009EE40 24050001 */  li    $a1, 1
/* 09FA44 8009EE44 AD620004 */  sw    $v0, 4($t3)
/* 09FA48 8009EE48 8E2C0000 */  lw    $t4, ($s1)
/* 09FA4C 8009EE4C 00000000 */  nop   
/* 09FA50 8009EE50 8584002E */  lh    $a0, 0x2e($t4)
/* 09FA54 8009EE54 00000000 */  nop   
/* 09FA58 8009EE58 308D3FFF */  andi  $t5, $a0, 0x3fff
/* 09FA5C 8009EE5C 0C01F04B */  jal   func_8007C12C
/* 09FA60 8009EE60 01A02025 */   move  $a0, $t5
/* 09FA64 8009EE64 3C078012 */  lui   $a3, %hi(D_80126CF4) # $a3, 0x8012
/* 09FA68 8009EE68 24E76CF4 */  addiu $a3, %lo(D_80126CF4) # addiu $a3, $a3, 0x6cf4
/* 09FA6C 8009EE6C 8CEE0000 */  lw    $t6, ($a3)
/* 09FA70 8009EE70 24050001 */  li    $a1, 1
/* 09FA74 8009EE74 ADC2005C */  sw    $v0, 0x5c($t6)
/* 09FA78 8009EE78 8E2F0000 */  lw    $t7, ($s1)
/* 09FA7C 8009EE7C 00000000 */  nop   
/* 09FA80 8009EE80 85E40010 */  lh    $a0, 0x10($t7)
/* 09FA84 8009EE84 00000000 */  nop   
/* 09FA88 8009EE88 30983FFF */  andi  $t8, $a0, 0x3fff
/* 09FA8C 8009EE8C 0C01F04B */  jal   func_8007C12C
/* 09FA90 8009EE90 03002025 */   move  $a0, $t8
/* 09FA94 8009EE94 3C078012 */  lui   $a3, %hi(D_80126CF4) # $a3, 0x8012
/* 09FA98 8009EE98 24E76CF4 */  addiu $a3, %lo(D_80126CF4) # addiu $a3, $a3, 0x6cf4
/* 09FA9C 8009EE9C 8CF90000 */  lw    $t9, ($a3)
/* 09FAA0 8009EEA0 24050001 */  li    $a1, 1
/* 09FAA4 8009EEA4 AF220020 */  sw    $v0, 0x20($t9)
/* 09FAA8 8009EEA8 8E280000 */  lw    $t0, ($s1)
/* 09FAAC 8009EEAC 00000000 */  nop   
/* 09FAB0 8009EEB0 85040022 */  lh    $a0, 0x22($t0)
/* 09FAB4 8009EEB4 00000000 */  nop   
/* 09FAB8 8009EEB8 30893FFF */  andi  $t1, $a0, 0x3fff
/* 09FABC 8009EEBC 0C01F04B */  jal   func_8007C12C
/* 09FAC0 8009EEC0 01202025 */   move  $a0, $t1
/* 09FAC4 8009EEC4 3C078012 */  lui   $a3, %hi(D_80126CF4) # $a3, 0x8012
/* 09FAC8 8009EEC8 24E76CF4 */  addiu $a3, %lo(D_80126CF4) # addiu $a3, $a3, 0x6cf4
/* 09FACC 8009EECC 8CEA0000 */  lw    $t2, ($a3)
/* 09FAD0 8009EED0 3C038012 */  lui   $v1, %hi(D_80126D37) # $v1, 0x8012
/* 09FAD4 8009EED4 AD420044 */  sw    $v0, 0x44($t2)
/* 09FAD8 8009EED8 90636D37 */  lbu   $v1, %lo(D_80126D37)($v1)
/* 09FADC 8009EEDC 24010003 */  li    $at, 3
/* 09FAE0 8009EEE0 10610003 */  beq   $v1, $at, .L8009EEF0
/* 09FAE4 8009EEE4 3405FFFF */   li    $a1, 65535
/* 09FAE8 8009EEE8 10000002 */  b     .L8009EEF4
/* 09FAEC 8009EEEC 00601025 */   move  $v0, $v1
.L8009EEF0:
/* 09FAF0 8009EEF0 24020004 */  li    $v0, 4
.L8009EEF4:
/* 09FAF4 8009EEF4 00022100 */  sll   $a0, $v0, 4
/* 09FAF8 8009EEF8 00822023 */  subu  $a0, $a0, $v0
/* 09FAFC 8009EEFC 00042080 */  sll   $a0, $a0, 2
/* 09FB00 8009EF00 00822023 */  subu  $a0, $a0, $v0
/* 09FB04 8009EF04 0C01C327 */  jal   allocate_from_main_pool_safe
/* 09FB08 8009EF08 00042140 */   sll   $a0, $a0, 5
/* 09FB0C 8009EF0C 3C038012 */  lui   $v1, %hi(D_80126CE0) # $v1, 0x8012
/* 09FB10 8009EF10 24636CE0 */  addiu $v1, %lo(D_80126CE0) # addiu $v1, $v1, 0x6ce0
/* 09FB14 8009EF14 244C0760 */  addiu $t4, $v0, 0x760
/* 09FB18 8009EF18 258E0760 */  addiu $t6, $t4, 0x760
/* 09FB1C 8009EF1C 25D80760 */  addiu $t8, $t6, 0x760
/* 09FB20 8009EF20 AC620000 */  sw    $v0, ($v1)
/* 09FB24 8009EF24 AC6C0004 */  sw    $t4, 4($v1)
/* 09FB28 8009EF28 AC6E0008 */  sw    $t6, 8($v1)
/* 09FB2C 8009EF2C 0C027C0D */  jal   func_8009F034
/* 09FB30 8009EF30 AC78000C */   sw    $t8, 0xc($v1)
/* 09FB34 8009EF34 3C018012 */  lui   $at, %hi(D_80126D64) # $at, 0x8012
/* 09FB38 8009EF38 A0206D64 */  sb    $zero, %lo(D_80126D64)($at)
/* 09FB3C 8009EF3C 3C018012 */  lui   $at, %hi(gWrongWayNagTimer) # $at, 0x8012
/* 09FB40 8009EF40 AC206D6C */  sw    $zero, %lo(gWrongWayNagTimer)($at)
/* 09FB44 8009EF44 3C018012 */  lui   $at, %hi(D_80126D48) # $at, 0x8012
/* 09FB48 8009EF48 A4206D48 */  sh    $zero, %lo(D_80126D48)($at)
/* 09FB4C 8009EF4C 24020004 */  li    $v0, 4
/* 09FB50 8009EF50 3C018012 */  lui   $at, %hi(D_80126D66) # $at, 0x8012
/* 09FB54 8009EF54 A0226D66 */  sb    $v0, %lo(D_80126D66)($at)
/* 09FB58 8009EF58 3C018012 */  lui   $at, %hi(D_80126D65) # $at, 0x8012
/* 09FB5C 8009EF5C A0206D65 */  sb    $zero, %lo(D_80126D65)($at)
/* 09FB60 8009EF60 3C018012 */  lui   $at, %hi(D_80126D67) # $at, 0x8012
/* 09FB64 8009EF64 A0226D67 */  sb    $v0, %lo(D_80126D67)($at)
/* 09FB68 8009EF68 3C018012 */  lui   $at, %hi(D_80126D69) # $at, 0x8012
/* 09FB6C 8009EF6C 24190001 */  li    $t9, 1
/* 09FB70 8009EF70 A0396D69 */  sb    $t9, %lo(D_80126D69)($at)
/* 09FB74 8009EF74 3C018012 */  lui   $at, %hi(D_80126D68) # $at, 0x8012
/* 09FB78 8009EF78 24080001 */  li    $t0, 1
/* 09FB7C 8009EF7C A0286D68 */  sb    $t0, %lo(D_80126D68)($at)
/* 09FB80 8009EF80 3C018012 */  lui   $at, %hi(D_80126D70) # $at, 0x8012
/* 09FB84 8009EF84 A0206D70 */  sb    $zero, %lo(D_80126D70)($at)
/* 09FB88 8009EF88 3C018012 */  lui   $at, %hi(D_80126D7C) # $at, 0x8012
/* 09FB8C 8009EF8C A4206D7C */  sh    $zero, %lo(D_80126D7C)($at)
/* 09FB90 8009EF90 3C018012 */  lui   $at, %hi(D_80126D74) # $at, 0x8012
/* 09FB94 8009EF94 AC206D74 */  sw    $zero, %lo(D_80126D74)($at)
/* 09FB98 8009EF98 3C018012 */  lui   $at, %hi(D_80126D3C) # $at, 0x8012
/* 09FB9C 8009EF9C AC206D3C */  sw    $zero, %lo(D_80126D3C)($at)
/* 09FBA0 8009EFA0 3C018012 */  lui   $at, %hi(D_80126D44) # $at, 0x8012
/* 09FBA4 8009EFA4 AC206D44 */  sw    $zero, %lo(D_80126D44)($at)
/* 09FBA8 8009EFA8 3C018012 */  lui   $at, %hi(D_80126CD3) # $at, 0x8012
/* 09FBAC 8009EFAC A0206CD3 */  sb    $zero, %lo(D_80126CD3)($at)
/* 09FBB0 8009EFB0 0C0078A7 */  jal   get_misc_asset
/* 09FBB4 8009EFB4 2404003A */   li    $a0, 58
/* 09FBB8 8009EFB8 3C038012 */  lui   $v1, %hi(D_80127194) # $v1, 0x8012
/* 09FBBC 8009EFBC 24637194 */  addiu $v1, %lo(D_80127194) # addiu $v1, $v1, 0x7194
/* 09FBC0 8009EFC0 AC620000 */  sw    $v0, ($v1)
/* 09FBC4 8009EFC4 0C01FC7A */  jal   func_8007F1E8
/* 09FBC8 8009EFC8 00402025 */   move  $a0, $v0
/* 09FBCC 8009EFCC 00002025 */  move  $a0, $zero
/* 09FBD0 8009EFD0 0C001298 */  jal   func_80004A60
/* 09FBD4 8009EFD4 24057FFF */   li    $a1, 32767
/* 09FBD8 8009EFD8 24040002 */  li    $a0, 2
/* 09FBDC 8009EFDC 0C001298 */  jal   func_80004A60
/* 09FBE0 8009EFE0 24057FFF */   li    $a1, 32767
/* 09FBE4 8009EFE4 3C10800E */  lui   $s0, %hi(D_800E2770) # $s0, 0x800e
/* 09FBE8 8009EFE8 3C11800E */  lui   $s1, %hi(D_800E2790) # $s1, 0x800e
/* 09FBEC 8009EFEC 26312790 */  addiu $s1, %lo(D_800E2790) # addiu $s1, $s1, 0x2790
/* 09FBF0 8009EFF0 26102770 */  addiu $s0, %lo(D_800E2770) # addiu $s0, $s0, 0x2770
.L8009EFF4:
/* 09FBF4 8009EFF4 8E040004 */  lw    $a0, 4($s0)
/* 09FBF8 8009EFF8 A2000002 */  sb    $zero, 2($s0)
/* 09FBFC 8009EFFC A2000003 */  sb    $zero, 3($s0)
/* 09FC00 8009F000 10800003 */  beqz  $a0, .L8009F010
/* 09FC04 8009F004 A212000C */   sb    $s2, 0xc($s0)
/* 09FC08 8009F008 0C001223 */  jal   func_8000488C
/* 09FC0C 8009F00C 00000000 */   nop   
.L8009F010:
/* 09FC10 8009F010 26100010 */  addiu $s0, $s0, 0x10
/* 09FC14 8009F014 1611FFF7 */  bne   $s0, $s1, .L8009EFF4
/* 09FC18 8009F018 00000000 */   nop   
/* 09FC1C 8009F01C 8FBF0024 */  lw    $ra, 0x24($sp)
/* 09FC20 8009F020 8FB00018 */  lw    $s0, 0x18($sp)
/* 09FC24 8009F024 8FB1001C */  lw    $s1, 0x1c($sp)
/* 09FC28 8009F028 8FB20020 */  lw    $s2, 0x20($sp)
/* 09FC2C 8009F02C 03E00008 */  jr    $ra
/* 09FC30 8009F030 27BD0028 */   addiu $sp, $sp, 0x28

