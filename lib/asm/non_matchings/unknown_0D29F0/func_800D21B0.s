glabel func_800D21B0
/* 0D2DB0 800D21B0 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0D2DB4 800D21B4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D2DB8 800D21B8 0C034958 */  jal   __osDisableInt
/* 0D2DBC 800D21BC AFB00018 */   sw    $s0, 0x18($sp)
/* 0D2DC0 800D21C0 0C031E34 */  jal   func_800C78D0
/* 0D2DC4 800D21C4 00408025 */   move  $s0, $v0
/* 0D2DC8 800D21C8 AFA20034 */  sw    $v0, 0x34($sp)
/* 0D2DCC 800D21CC 3C0F8013 */  lui   $t7, %hi(D_8012D228) # $t7, 0x8013
/* 0D2DD0 800D21D0 8DEFD228 */  lw    $t7, %lo(D_8012D228)($t7)
/* 0D2DD4 800D21D4 8FAE0034 */  lw    $t6, 0x34($sp)
/* 0D2DD8 800D21D8 3C088013 */  lui   $t0, %hi(D_8012D220) # $t0, 0x8013
/* 0D2DDC 800D21DC 3C098013 */  lui   $t1, %hi(D_8012D224) # $t1, 0x8013
/* 0D2DE0 800D21E0 8D29D224 */  lw    $t1, %lo(D_8012D224)($t1)
/* 0D2DE4 800D21E4 8D08D220 */  lw    $t0, %lo(D_8012D220)($t0)
/* 0D2DE8 800D21E8 01CFC023 */  subu  $t8, $t6, $t7
/* 0D2DEC 800D21EC AFB80030 */  sw    $t8, 0x30($sp)
/* 0D2DF0 800D21F0 02002025 */  move  $a0, $s0
/* 0D2DF4 800D21F4 AFA9002C */  sw    $t1, 0x2c($sp)
/* 0D2DF8 800D21F8 0C034960 */  jal   __osRestoreInt
/* 0D2DFC 800D21FC AFA80028 */   sw    $t0, 0x28($sp)
/* 0D2E00 800D2200 8FB90030 */  lw    $t9, 0x30($sp)
/* 0D2E04 800D2204 8FAD002C */  lw    $t5, 0x2c($sp)
/* 0D2E08 800D2208 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D2E0C 800D220C 03205825 */  move  $t3, $t9
/* 0D2E10 800D2210 016D1821 */  addu  $v1, $t3, $t5
/* 0D2E14 800D2214 8FAC0028 */  lw    $t4, 0x28($sp)
/* 0D2E18 800D2218 240A0000 */  li    $t2, 0
/* 0D2E1C 800D221C 006D082B */  sltu  $at, $v1, $t5
/* 0D2E20 800D2220 002A1021 */  addu  $v0, $at, $t2
/* 0D2E24 800D2224 8FB00018 */  lw    $s0, 0x18($sp)
/* 0D2E28 800D2228 27BD0038 */  addiu $sp, $sp, 0x38
/* 0D2E2C 800D222C 03E00008 */  jr    $ra
/* 0D2E30 800D2230 004C1021 */   addu  $v0, $v0, $t4

/* 0D2E34 800D2234 00000000 */  nop   
/* 0D2E38 800D2238 00000000 */  nop   
/* 0D2E3C 800D223C 00000000 */  nop   

