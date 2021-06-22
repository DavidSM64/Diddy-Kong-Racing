glabel func_8006ECFC
/* 06F8FC 8006ECFC 3C028012 */  lui   $v0, %hi(D_8012350C) # $v0, 0x8012
/* 06F900 8006ED00 2442350C */  addiu $v0, %lo(D_8012350C) # addiu $v0, $v0, 0x350c
/* 06F904 8006ED04 8C4E0000 */  lw    $t6, ($v0)
/* 06F908 8006ED08 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 06F90C 8006ED0C AFBF001C */  sw    $ra, 0x1c($sp)
/* 06F910 8006ED10 AFB10018 */  sw    $s1, 0x18($sp)
/* 06F914 8006ED14 AFB00014 */  sw    $s0, 0x14($sp)
/* 06F918 8006ED18 108E007D */  beq   $a0, $t6, .L8006EF10
/* 06F91C 8006ED1C 00802825 */   move  $a1, $a0
/* 06F920 8006ED20 AC440000 */  sw    $a0, ($v0)
/* 06F924 8006ED24 00002025 */  move  $a0, $zero
/* 06F928 8006ED28 0C01C42C */  jal   func_800710B0
/* 06F92C 8006ED2C AFA50048 */   sw    $a1, 0x48($sp)
/* 06F930 8006ED30 3C118012 */  lui   $s1, %hi(D_801211F0) # $s1, 0x8012
/* 06F934 8006ED34 263111F0 */  addiu $s1, %lo(D_801211F0) # addiu $s1, $s1, 0x11f0
/* 06F938 8006ED38 8E240000 */  lw    $a0, ($s1)
/* 06F93C 8006ED3C 0C01C450 */  jal   func_80071140
/* 06F940 8006ED40 00000000 */   nop   
/* 06F944 8006ED44 8E240004 */  lw    $a0, 4($s1)
/* 06F948 8006ED48 0C01C450 */  jal   func_80071140
/* 06F94C 8006ED4C 00000000 */   nop   
/* 06F950 8006ED50 8FA20048 */  lw    $v0, 0x48($sp)
/* 06F954 8006ED54 3C18800E */  lui   $t8, %hi(D_800DD3E0) # $t8, 0x800e
/* 06F958 8006ED58 2718D3E0 */  addiu $t8, %lo(D_800DD3E0) # addiu $t8, $t8, -0x2c20
/* 06F95C 8006ED5C 3C19800E */  lui   $t9, %hi(D_800DD3B0) # $t9, 0x800e
/* 06F960 8006ED60 00027880 */  sll   $t7, $v0, 2
/* 06F964 8006ED64 01F84021 */  addu  $t0, $t7, $t8
/* 06F968 8006ED68 2739D3B0 */  addiu $t9, %lo(D_800DD3B0) # addiu $t9, $t9, -0x2c50
/* 06F96C 8006ED6C 01F91821 */  addu  $v1, $t7, $t9
/* 06F970 8006ED70 3C0C800E */  lui   $t4, %hi(D_800DD3D0) # $t4, 0x800e
/* 06F974 8006ED74 3C0D800E */  lui   $t5, %hi(D_800DD3C0) # $t5, 0x800e
/* 06F978 8006ED78 8C780000 */  lw    $t8, ($v1)
/* 06F97C 8006ED7C 8D0E0000 */  lw    $t6, ($t0)
/* 06F980 8006ED80 25ADD3C0 */  addiu $t5, %lo(D_800DD3C0) # addiu $t5, $t5, -0x2c40
/* 06F984 8006ED84 258CD3D0 */  addiu $t4, %lo(D_800DD3D0) # addiu $t4, $t4, -0x2c30
/* 06F988 8006ED88 01EC3821 */  addu  $a3, $t7, $t4
/* 06F98C 8006ED8C 01ED4821 */  addu  $t1, $t7, $t5
/* 06F990 8006ED90 0018C8C0 */  sll   $t9, $t8, 3
/* 06F994 8006ED94 000E7900 */  sll   $t7, $t6, 4
/* 06F998 8006ED98 01F96021 */  addu  $t4, $t7, $t9
/* 06F99C 8006ED9C 8D2F0000 */  lw    $t7, ($t1)
/* 06F9A0 8006EDA0 8CED0000 */  lw    $t5, ($a3)
/* 06F9A4 8006EDA4 000FC880 */  sll   $t9, $t7, 2
/* 06F9A8 8006EDA8 032FC821 */  addu  $t9, $t9, $t7
/* 06F9AC 8006EDAC 000D7180 */  sll   $t6, $t5, 6
/* 06F9B0 8006EDB0 018EC021 */  addu  $t8, $t4, $t6
/* 06F9B4 8006EDB4 0019C840 */  sll   $t9, $t9, 1
/* 06F9B8 8006EDB8 03198021 */  addu  $s0, $t8, $t9
/* 06F9BC 8006EDBC 8E250000 */  lw    $a1, ($s1)
/* 06F9C0 8006EDC0 3C06FF00 */  lui   $a2, (0xFF0000FF >> 16) # lui $a2, 0xff00
/* 06F9C4 8006EDC4 34C600FF */  ori   $a2, (0xFF0000FF & 0xFFFF) # ori $a2, $a2, 0xff
/* 06F9C8 8006EDC8 02002025 */  move  $a0, $s0
/* 06F9CC 8006EDCC AFA90020 */  sw    $t1, 0x20($sp)
/* 06F9D0 8006EDD0 AFA70028 */  sw    $a3, 0x28($sp)
/* 06F9D4 8006EDD4 AFA3002C */  sw    $v1, 0x2c($sp)
/* 06F9D8 8006EDD8 0C01C3BE */  jal   allocate_at_address_in_main_pool
/* 06F9DC 8006EDDC AFA80024 */   sw    $t0, 0x24($sp)
/* 06F9E0 8006EDE0 8E250004 */  lw    $a1, 4($s1)
/* 06F9E4 8006EDE4 3C06FFFF */  lui   $a2, (0xFFFF00FF >> 16) # lui $a2, 0xffff
/* 06F9E8 8006EDE8 AE220000 */  sw    $v0, ($s1)
/* 06F9EC 8006EDEC 34C600FF */  ori   $a2, (0xFFFF00FF & 0xFFFF) # ori $a2, $a2, 0xff
/* 06F9F0 8006EDF0 0C01C3BE */  jal   allocate_at_address_in_main_pool
/* 06F9F4 8006EDF4 02002025 */   move  $a0, $s0
/* 06F9F8 8006EDF8 8E300000 */  lw    $s0, ($s1)
/* 06F9FC 8006EDFC AE220004 */  sw    $v0, 4($s1)
/* 06FA00 8006EE00 12000003 */  beqz  $s0, .L8006EE10
/* 06FA04 8006EE04 00000000 */   nop   
/* 06FA08 8006EE08 14400012 */  bnez  $v0, .L8006EE54
/* 06FA0C 8006EE0C 00402825 */   move  $a1, $v0
.L8006EE10:
/* 06FA10 8006EE10 12000004 */  beqz  $s0, .L8006EE24
/* 06FA14 8006EE14 00000000 */   nop   
/* 06FA18 8006EE18 0C01C450 */  jal   func_80071140
/* 06FA1C 8006EE1C 02002025 */   move  $a0, $s0
/* 06FA20 8006EE20 AE200000 */  sw    $zero, ($s1)
.L8006EE24:
/* 06FA24 8006EE24 8E250004 */  lw    $a1, 4($s1)
/* 06FA28 8006EE28 00000000 */  nop   
/* 06FA2C 8006EE2C 10A00004 */  beqz  $a1, .L8006EE40
/* 06FA30 8006EE30 00000000 */   nop   
/* 06FA34 8006EE34 0C01C450 */  jal   func_80071140
/* 06FA38 8006EE38 00A02025 */   move  $a0, $a1
/* 06FA3C 8006EE3C AE200004 */  sw    $zero, 4($s1)
.L8006EE40:
/* 06FA40 8006EE40 0C01BBF7 */  jal   func_8006EFDC
/* 06FA44 8006EE44 00000000 */   nop   
/* 06FA48 8006EE48 8E300000 */  lw    $s0, ($s1)
/* 06FA4C 8006EE4C 8E250004 */  lw    $a1, 4($s1)
/* 06FA50 8006EE50 00000000 */  nop   
.L8006EE54:
/* 06FA54 8006EE54 8FAD002C */  lw    $t5, 0x2c($sp)
/* 06FA58 8006EE58 8FAE0028 */  lw    $t6, 0x28($sp)
/* 06FA5C 8006EE5C 8DA20000 */  lw    $v0, ($t5)
/* 06FA60 8006EE60 3C018012 */  lui   $at, %hi(D_80121200) # $at, 0x8012
/* 06FA64 8006EE64 000218C0 */  sll   $v1, $v0, 3
/* 06FA68 8006EE68 00706021 */  addu  $t4, $v1, $s0
/* 06FA6C 8006EE6C 3C0A8012 */  lui   $t2, %hi(D_80121200) # $t2, 0x8012
/* 06FA70 8006EE70 AC2C1200 */  sw    $t4, %lo(D_80121200)($at)
/* 06FA74 8006EE74 8DC60000 */  lw    $a2, ($t6)
/* 06FA78 8006EE78 254A1200 */  addiu $t2, %lo(D_80121200) # addiu $t2, $t2, 0x1200
/* 06FA7C 8006EE7C 8D4F0000 */  lw    $t7, ($t2)
/* 06FA80 8006EE80 00063980 */  sll   $a3, $a2, 6
/* 06FA84 8006EE84 8FB90024 */  lw    $t9, 0x24($sp)
/* 06FA88 8006EE88 3C018012 */  lui   $at, %hi(D_80121220) # $at, 0x8012
/* 06FA8C 8006EE8C 00EFC021 */  addu  $t8, $a3, $t7
/* 06FA90 8006EE90 3C0B8012 */  lui   $t3, %hi(D_80121220) # $t3, 0x8012
/* 06FA94 8006EE94 AC381220 */  sw    $t8, %lo(D_80121220)($at)
/* 06FA98 8006EE98 8F280000 */  lw    $t0, ($t9)
/* 06FA9C 8006EE9C 256B1220 */  addiu $t3, %lo(D_80121220) # addiu $t3, $t3, 0x1220
/* 06FAA0 8006EEA0 8D6D0000 */  lw    $t5, ($t3)
/* 06FAA4 8006EEA4 00084900 */  sll   $t1, $t0, 4
/* 06FAA8 8006EEA8 3C018012 */  lui   $at, %hi(D_80121210) # $at, 0x8012
/* 06FAAC 8006EEAC 012D6021 */  addu  $t4, $t1, $t5
/* 06FAB0 8006EEB0 AC2C1210 */  sw    $t4, %lo(D_80121210)($at)
/* 06FAB4 8006EEB4 3C018012 */  lui   $at, %hi(D_80121200+4) # $at, 0x8012
/* 06FAB8 8006EEB8 00657021 */  addu  $t6, $v1, $a1
/* 06FABC 8006EEBC AC2E1204 */  sw    $t6, %lo(D_80121200+4)($at)
/* 06FAC0 8006EEC0 8D4F0004 */  lw    $t7, 4($t2)
/* 06FAC4 8006EEC4 3C018012 */  lui   $at, %hi(D_80121220+4) # $at, 0x8012
/* 06FAC8 8006EEC8 00EFC021 */  addu  $t8, $a3, $t7
/* 06FACC 8006EECC AC381224 */  sw    $t8, %lo(D_80121220+4)($at)
/* 06FAD0 8006EED0 8D790004 */  lw    $t9, 4($t3)
/* 06FAD4 8006EED4 3C018012 */  lui   $at, %hi(D_80121210+4) # $at, 0x8012
/* 06FAD8 8006EED8 01396821 */  addu  $t5, $t1, $t9
/* 06FADC 8006EEDC AC2D1214 */  sw    $t5, %lo(D_80121210+4)($at)
/* 06FAE0 8006EEE0 3C018012 */  lui   $at, %hi(D_80123528) # $at, 0x8012
/* 06FAE4 8006EEE4 AC223528 */  sw    $v0, %lo(D_80123528)($at)
/* 06FAE8 8006EEE8 3C018012 */  lui   $at, %hi(D_8012352C) # $at, 0x8012
/* 06FAEC 8006EEEC AC26352C */  sw    $a2, %lo(D_8012352C)($at)
/* 06FAF0 8006EEF0 8FAC0020 */  lw    $t4, 0x20($sp)
/* 06FAF4 8006EEF4 3C018012 */  lui   $at, %hi(D_80123530) # $at, 0x8012
/* 06FAF8 8006EEF8 AC283530 */  sw    $t0, %lo(D_80123530)($at)
/* 06FAFC 8006EEFC 8D8E0000 */  lw    $t6, ($t4)
/* 06FB00 8006EF00 3C018012 */  lui   $at, %hi(D_80123534) # $at, 0x8012
/* 06FB04 8006EF04 24040002 */  li    $a0, 2
/* 06FB08 8006EF08 0C01C42C */  jal   func_800710B0
/* 06FB0C 8006EF0C AC2E3534 */   sw    $t6, %lo(D_80123534)($at)
.L8006EF10:
/* 06FB10 8006EF10 3C038012 */  lui   $v1, %hi(D_801234E8) # $v1, 0x8012
/* 06FB14 8006EF14 8C6334E8 */  lw    $v1, %lo(D_801234E8)($v1)
/* 06FB18 8006EF18 3C118012 */  lui   $s1, %hi(D_801211F0) # $s1, 0x8012
/* 06FB1C 8006EF1C 263111F0 */  addiu $s1, %lo(D_801211F0) # addiu $s1, $s1, 0x11f0
/* 06FB20 8006EF20 00037880 */  sll   $t7, $v1, 2
/* 06FB24 8006EF24 022FC021 */  addu  $t8, $s1, $t7
/* 06FB28 8006EF28 8F190000 */  lw    $t9, ($t8)
/* 06FB2C 8006EF2C 3C048012 */  lui   $a0, %hi(D_801211F8) # $a0, 0x8012
/* 06FB30 8006EF30 248411F8 */  addiu $a0, %lo(D_801211F8) # addiu $a0, $a0, 0x11f8
/* 06FB34 8006EF34 3C0D8012 */  lui   $t5, %hi(D_80121200) # $t5, 0x8012
/* 06FB38 8006EF38 01AF6821 */  addu  $t5, $t5, $t7
/* 06FB3C 8006EF3C AC990000 */  sw    $t9, ($a0)
/* 06FB40 8006EF40 8DAD1200 */  lw    $t5, %lo(D_80121200)($t5)
/* 06FB44 8006EF44 3C0C8012 */  lui   $t4, %hi(D_80121220) # $t4, 0x8012
/* 06FB48 8006EF48 3C018012 */  lui   $at, %hi(D_80121208) # $at, 0x8012
/* 06FB4C 8006EF4C 018F6021 */  addu  $t4, $t4, $t7
/* 06FB50 8006EF50 8D8C1220 */  lw    $t4, %lo(D_80121220)($t4)
/* 06FB54 8006EF54 3C0E8012 */  lui   $t6, %hi(D_80121210) # $t6, 0x8012
/* 06FB58 8006EF58 AC2D1208 */  sw    $t5, %lo(D_80121208)($at)
/* 06FB5C 8006EF5C 3C018012 */  lui   $at, %hi(D_80121228) # $at, 0x8012
/* 06FB60 8006EF60 01CF7021 */  addu  $t6, $t6, $t7
/* 06FB64 8006EF64 8DCE1210 */  lw    $t6, %lo(D_80121210)($t6)
/* 06FB68 8006EF68 AC2C1228 */  sw    $t4, %lo(D_80121228)($at)
/* 06FB6C 8006EF6C 3C018012 */  lui   $at, %hi(D_80121218) # $at, 0x8012
/* 06FB70 8006EF70 AC2E1218 */  sw    $t6, %lo(D_80121218)($at)
/* 06FB74 8006EF74 8C820000 */  lw    $v0, ($a0)
/* 06FB78 8006EF78 3C18E900 */  lui   $t8, 0xe900
/* 06FB7C 8006EF7C 244F0008 */  addiu $t7, $v0, 8
/* 06FB80 8006EF80 AC8F0000 */  sw    $t7, ($a0)
/* 06FB84 8006EF84 AC400004 */  sw    $zero, 4($v0)
/* 06FB88 8006EF88 AC580000 */  sw    $t8, ($v0)
/* 06FB8C 8006EF8C 8C820000 */  lw    $v0, ($a0)
/* 06FB90 8006EF90 3C0DB800 */  lui   $t5, 0xb800
/* 06FB94 8006EF94 24590008 */  addiu $t9, $v0, 8
/* 06FB98 8006EF98 AC990000 */  sw    $t9, ($a0)
/* 06FB9C 8006EF9C AC400004 */  sw    $zero, 4($v0)
/* 06FBA0 8006EFA0 AC4D0000 */  sw    $t5, ($v0)
/* 06FBA4 8006EFA4 8FBF001C */  lw    $ra, 0x1c($sp)
/* 06FBA8 8006EFA8 8FB10018 */  lw    $s1, 0x18($sp)
/* 06FBAC 8006EFAC 8FB00014 */  lw    $s0, 0x14($sp)
/* 06FBB0 8006EFB0 03E00008 */  jr    $ra
/* 06FBB4 8006EFB4 27BD0048 */   addiu $sp, $sp, 0x48

