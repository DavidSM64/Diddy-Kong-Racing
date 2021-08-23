glabel init_particle_assets
/* 0AF130 800AE530 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0AF134 800AE534 AFBF002C */  sw    $ra, 0x2c($sp)
/* 0AF138 800AE538 AFB50028 */  sw    $s5, 0x28($sp)
/* 0AF13C 800AE53C AFB40024 */  sw    $s4, 0x24($sp)
/* 0AF140 800AE540 AFB30020 */  sw    $s3, 0x20($sp)
/* 0AF144 800AE544 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0AF148 800AE548 AFB10018 */  sw    $s1, 0x18($sp)
/* 0AF14C 800AE54C 0C02B924 */  jal   func_800AE490
/* 0AF150 800AE550 AFB00014 */   sw    $s0, 0x14($sp)
/* 0AF154 800AE554 0C01DB16 */  jal   load_asset_section_from_rom
/* 0AF158 800AE558 24040028 */   li    $a0, 40
/* 0AF15C 800AE55C 3C05800E */  lui   $a1, %hi(gParticlesAssetTableCount) # $a1, 0x800e
/* 0AF160 800AE560 2406FFFF */  li    $a2, -1
/* 0AF164 800AE564 3C12800E */  lui   $s2, %hi(gParticlesAssetTable) # $s2, 0x800e
/* 0AF168 800AE568 26522CF0 */  addiu $s2, %lo(gParticlesAssetTable) # addiu $s2, $s2, 0x2cf0
/* 0AF16C 800AE56C 24A52CE8 */  addiu $a1, %lo(gParticlesAssetTableCount) # addiu $a1, $a1, 0x2ce8
/* 0AF170 800AE570 00067080 */  sll   $t6, $a2, 2
/* 0AF174 800AE574 AE420000 */  sw    $v0, ($s2)
/* 0AF178 800AE578 ACA60000 */  sw    $a2, ($a1)
/* 0AF17C 800AE57C 004E7821 */  addu  $t7, $v0, $t6
/* 0AF180 800AE580 8DF80004 */  lw    $t8, 4($t7)
/* 0AF184 800AE584 00C01825 */  move  $v1, $a2
/* 0AF188 800AE588 10D80009 */  beq   $a2, $t8, .L800AE5B0
/* 0AF18C 800AE58C 00402025 */   move  $a0, $v0
/* 0AF190 800AE590 24790001 */  addiu $t9, $v1, 1
.L800AE594:
/* 0AF194 800AE594 00194080 */  sll   $t0, $t9, 2
/* 0AF198 800AE598 00884821 */  addu  $t1, $a0, $t0
/* 0AF19C 800AE59C ACB90000 */  sw    $t9, ($a1)
/* 0AF1A0 800AE5A0 8D2A0004 */  lw    $t2, 4($t1)
/* 0AF1A4 800AE5A4 03201825 */  move  $v1, $t9
/* 0AF1A8 800AE5A8 14CAFFFA */  bne   $a2, $t2, .L800AE594
/* 0AF1AC 800AE5AC 24790001 */   addiu $t9, $v1, 1
.L800AE5B0:
/* 0AF1B0 800AE5B0 0C01DB16 */  jal   load_asset_section_from_rom
/* 0AF1B4 800AE5B4 24040029 */   li    $a0, 41
/* 0AF1B8 800AE5B8 3C05800E */  lui   $a1, %hi(gParticlesAssetTableCount) # $a1, 0x800e
/* 0AF1BC 800AE5BC 24A52CE8 */  addiu $a1, %lo(gParticlesAssetTableCount) # addiu $a1, $a1, 0x2ce8
/* 0AF1C0 800AE5C0 8CAB0000 */  lw    $t3, ($a1)
/* 0AF1C4 800AE5C4 3C03800E */  lui   $v1, %hi(gParticlesAssets) # $v1, 0x800e
/* 0AF1C8 800AE5C8 24632CEC */  addiu $v1, %lo(gParticlesAssets) # addiu $v1, $v1, 0x2cec
/* 0AF1CC 800AE5CC AC620000 */  sw    $v0, ($v1)
/* 0AF1D0 800AE5D0 1960000F */  blez  $t3, .L800AE610
/* 0AF1D4 800AE5D4 00008825 */   move  $s1, $zero
/* 0AF1D8 800AE5D8 00008025 */  move  $s0, $zero
.L800AE5DC:
/* 0AF1DC 800AE5DC 8E4C0000 */  lw    $t4, ($s2)
/* 0AF1E0 800AE5E0 8C6E0000 */  lw    $t6, ($v1)
/* 0AF1E4 800AE5E4 01901021 */  addu  $v0, $t4, $s0
/* 0AF1E8 800AE5E8 8C4D0000 */  lw    $t5, ($v0)
/* 0AF1EC 800AE5EC 26310001 */  addiu $s1, $s1, 1
/* 0AF1F0 800AE5F0 01AE7821 */  addu  $t7, $t5, $t6
/* 0AF1F4 800AE5F4 AC4F0000 */  sw    $t7, ($v0)
/* 0AF1F8 800AE5F8 8CB80000 */  lw    $t8, ($a1)
/* 0AF1FC 800AE5FC 26100004 */  addiu $s0, $s0, 4
/* 0AF200 800AE600 0238082A */  slt   $at, $s1, $t8
/* 0AF204 800AE604 1420FFF5 */  bnez  $at, .L800AE5DC
/* 0AF208 800AE608 00000000 */   nop   
/* 0AF20C 800AE60C 00008825 */  move  $s1, $zero
.L800AE610:
/* 0AF210 800AE610 0C01DB16 */  jal   load_asset_section_from_rom
/* 0AF214 800AE614 2404002A */   li    $a0, 42
/* 0AF218 800AE618 2406FFFF */  li    $a2, -1
/* 0AF21C 800AE61C 3C12800E */  lui   $s2, %hi(gParticleBehaviorsAssetTableCount) # $s2, 0x800e
/* 0AF220 800AE620 3C13800E */  lui   $s3, %hi(gParticleBehaviorsAssetTable) # $s3, 0x800e
/* 0AF224 800AE624 26732CFC */  addiu $s3, %lo(gParticleBehaviorsAssetTable) # addiu $s3, $s3, 0x2cfc
/* 0AF228 800AE628 26522CF4 */  addiu $s2, %lo(gParticleBehaviorsAssetTableCount) # addiu $s2, $s2, 0x2cf4
/* 0AF22C 800AE62C 0006C880 */  sll   $t9, $a2, 2
/* 0AF230 800AE630 AE620000 */  sw    $v0, ($s3)
/* 0AF234 800AE634 AE460000 */  sw    $a2, ($s2)
/* 0AF238 800AE638 00594021 */  addu  $t0, $v0, $t9
/* 0AF23C 800AE63C 8D090004 */  lw    $t1, 4($t0)
/* 0AF240 800AE640 00C01825 */  move  $v1, $a2
/* 0AF244 800AE644 10C90009 */  beq   $a2, $t1, .L800AE66C
/* 0AF248 800AE648 00402025 */   move  $a0, $v0
/* 0AF24C 800AE64C 246A0001 */  addiu $t2, $v1, 1
.L800AE650:
/* 0AF250 800AE650 000A5880 */  sll   $t3, $t2, 2
/* 0AF254 800AE654 008B6021 */  addu  $t4, $a0, $t3
/* 0AF258 800AE658 AE4A0000 */  sw    $t2, ($s2)
/* 0AF25C 800AE65C 8D8D0004 */  lw    $t5, 4($t4)
/* 0AF260 800AE660 01401825 */  move  $v1, $t2
/* 0AF264 800AE664 14CDFFFA */  bne   $a2, $t5, .L800AE650
/* 0AF268 800AE668 246A0001 */   addiu $t2, $v1, 1
.L800AE66C:
/* 0AF26C 800AE66C 0C01DB16 */  jal   load_asset_section_from_rom
/* 0AF270 800AE670 2404002B */   li    $a0, 43
/* 0AF274 800AE674 8E4E0000 */  lw    $t6, ($s2)
/* 0AF278 800AE678 3C15800E */  lui   $s5, %hi(gParticleBehaviorsAssets) # $s5, 0x800e
/* 0AF27C 800AE67C 26B52CF8 */  addiu $s5, %lo(gParticleBehaviorsAssets) # addiu $s5, $s5, 0x2cf8
/* 0AF280 800AE680 19C00020 */  blez  $t6, .L800AE704
/* 0AF284 800AE684 AEA20000 */   sw    $v0, ($s5)
/* 0AF288 800AE688 00008025 */  move  $s0, $zero
/* 0AF28C 800AE68C 2414FFFF */  li    $s4, -1
.L800AE690:
/* 0AF290 800AE690 8E6F0000 */  lw    $t7, ($s3)
/* 0AF294 800AE694 8EB90000 */  lw    $t9, ($s5)
/* 0AF298 800AE698 01F01021 */  addu  $v0, $t7, $s0
/* 0AF29C 800AE69C 8C580000 */  lw    $t8, ($v0)
/* 0AF2A0 800AE6A0 00000000 */  nop   
/* 0AF2A4 800AE6A4 03194021 */  addu  $t0, $t8, $t9
/* 0AF2A8 800AE6A8 AC480000 */  sw    $t0, ($v0)
/* 0AF2AC 800AE6AC 8E690000 */  lw    $t1, ($s3)
/* 0AF2B0 800AE6B0 00000000 */  nop   
/* 0AF2B4 800AE6B4 01305021 */  addu  $t2, $t1, $s0
/* 0AF2B8 800AE6B8 8D4B0000 */  lw    $t3, ($t2)
/* 0AF2BC 800AE6BC 00000000 */  nop   
/* 0AF2C0 800AE6C0 8D63009C */  lw    $v1, 0x9c($t3)
/* 0AF2C4 800AE6C4 00000000 */  nop   
/* 0AF2C8 800AE6C8 12830009 */  beq   $s4, $v1, .L800AE6F0
/* 0AF2CC 800AE6CC 00000000 */   nop   
/* 0AF2D0 800AE6D0 0C0078A7 */  jal   get_misc_asset
/* 0AF2D4 800AE6D4 00602025 */   move  $a0, $v1
/* 0AF2D8 800AE6D8 8E6C0000 */  lw    $t4, ($s3)
/* 0AF2DC 800AE6DC 00000000 */  nop   
/* 0AF2E0 800AE6E0 01906821 */  addu  $t5, $t4, $s0
/* 0AF2E4 800AE6E4 8DAE0000 */  lw    $t6, ($t5)
/* 0AF2E8 800AE6E8 00000000 */  nop   
/* 0AF2EC 800AE6EC ADC2009C */  sw    $v0, 0x9c($t6)
.L800AE6F0:
/* 0AF2F0 800AE6F0 8E4F0000 */  lw    $t7, ($s2)
/* 0AF2F4 800AE6F4 26310001 */  addiu $s1, $s1, 1
/* 0AF2F8 800AE6F8 022F082A */  slt   $at, $s1, $t7
/* 0AF2FC 800AE6FC 1420FFE4 */  bnez  $at, .L800AE690
/* 0AF300 800AE700 26100004 */   addiu $s0, $s0, 4
.L800AE704:
/* 0AF304 800AE704 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0AF308 800AE708 8FB00014 */  lw    $s0, 0x14($sp)
/* 0AF30C 800AE70C 8FB10018 */  lw    $s1, 0x18($sp)
/* 0AF310 800AE710 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0AF314 800AE714 8FB30020 */  lw    $s3, 0x20($sp)
/* 0AF318 800AE718 8FB40024 */  lw    $s4, 0x24($sp)
/* 0AF31C 800AE71C 8FB50028 */  lw    $s5, 0x28($sp)
/* 0AF320 800AE720 03E00008 */  jr    $ra
/* 0AF324 800AE724 27BD0030 */   addiu $sp, $sp, 0x30

