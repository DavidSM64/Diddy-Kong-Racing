glabel func_800B452C
/* 0B512C 800B452C 8C8E0000 */  lw    $t6, ($a0)
/* 0B5130 800B4530 3C08800E */  lui   $t0, %hi(gParticlesAssetTable) # $t0, 0x800e
/* 0B5134 800B4534 25C3FFFF */  addiu $v1, $t6, -1
/* 0B5138 800B4538 04610009 */  bgez  $v1, .L800B4560
/* 0B513C 800B453C AC830000 */   sw    $v1, ($a0)
/* 0B5140 800B4540 3C02800E */  lui   $v0, %hi(gParticlesAssetTableCount) # $v0, 0x800e
/* 0B5144 800B4544 24422CE8 */  addiu $v0, %lo(gParticlesAssetTableCount) # addiu $v0, $v0, 0x2ce8
.L800B4548:
/* 0B5148 800B4548 8C580000 */  lw    $t8, ($v0)
/* 0B514C 800B454C 00000000 */  nop   
/* 0B5150 800B4550 0078C821 */  addu  $t9, $v1, $t8
/* 0B5154 800B4554 AC990000 */  sw    $t9, ($a0)
/* 0B5158 800B4558 0720FFFB */  bltz  $t9, .L800B4548
/* 0B515C 800B455C 03201825 */   move  $v1, $t9
.L800B4560:
/* 0B5160 800B4560 8D082CF0 */  lw    $t0, %lo(gParticlesAssetTable)($t0)
/* 0B5164 800B4564 00034880 */  sll   $t1, $v1, 2
/* 0B5168 800B4568 01095021 */  addu  $t2, $t0, $t1
/* 0B516C 800B456C 8D420000 */  lw    $v0, ($t2)
/* 0B5170 800B4570 03E00008 */  jr    $ra
/* 0B5174 800B4574 00000000 */   nop   

/* 0B5178 800B4578 3C03800E */  lui   $v1, %hi(gParticleBehavioursAssetTableCount) # $v1, 0x800e
/* 0B517C 800B457C 8C632CF4 */  lw    $v1, %lo(gParticleBehavioursAssetTableCount)($v1)
/* 0B5180 800B4580 3C0E800E */  lui   $t6, %hi(gParticleBehavioursAssetTable) # $t6, 0x800e
/* 0B5184 800B4584 0083082A */  slt   $at, $a0, $v1
/* 0B5188 800B4588 10200007 */  beqz  $at, .L800B45A8
/* 0B518C 800B458C 3C19800E */   lui   $t9, %hi(gParticleBehavioursAssetTable) # $t9, 0x800e
/* 0B5190 800B4590 8DCE2CFC */  lw    $t6, %lo(gParticleBehavioursAssetTable)($t6)
/* 0B5194 800B4594 00047880 */  sll   $t7, $a0, 2
/* 0B5198 800B4598 01CFC021 */  addu  $t8, $t6, $t7
/* 0B519C 800B459C 8F020000 */  lw    $v0, ($t8)
/* 0B51A0 800B45A0 03E00008 */  jr    $ra
/* 0B51A4 800B45A4 00000000 */   nop   

.L800B45A8:
/* 0B51A8 800B45A8 8F392CFC */  lw    $t9, %lo(gParticleBehavioursAssetTable)($t9)
/* 0B51AC 800B45AC 00034080 */  sll   $t0, $v1, 2
/* 0B51B0 800B45B0 03284821 */  addu  $t1, $t9, $t0
/* 0B51B4 800B45B4 8D22FFFC */  lw    $v0, -4($t1)
/* 0B51B8 800B45B8 00000000 */  nop   
/* 0B51BC 800B45BC 03E00008 */  jr    $ra
/* 0B51C0 800B45C0 00000000 */   nop   

/* 0B51C4 800B45C4 8C8E0000 */  lw    $t6, ($a0)
/* 0B51C8 800B45C8 3C05800E */  lui   $a1, %hi(gParticleBehavioursAssetTableCount) # $a1, 0x800e
/* 0B51CC 800B45CC 25C30001 */  addiu $v1, $t6, 1
/* 0B51D0 800B45D0 24A52CF4 */  addiu $a1, %lo(gParticleBehavioursAssetTableCount) # addiu $a1, $a1, 0x2cf4
/* 0B51D4 800B45D4 AC830000 */  sw    $v1, ($a0)
/* 0B51D8 800B45D8 8CA20000 */  lw    $v0, ($a1)
/* 0B51DC 800B45DC 3C19800E */  lui   $t9, %hi(gParticleBehavioursAssetTable) # $t9, 0x800e
/* 0B51E0 800B45E0 0062082A */  slt   $at, $v1, $v0
/* 0B51E4 800B45E4 14200007 */  bnez  $at, .L800B4604
/* 0B51E8 800B45E8 0062C023 */   subu  $t8, $v1, $v0
.L800B45EC:
/* 0B51EC 800B45EC AC980000 */  sw    $t8, ($a0)
/* 0B51F0 800B45F0 8CA20000 */  lw    $v0, ($a1)
/* 0B51F4 800B45F4 03001825 */  move  $v1, $t8
/* 0B51F8 800B45F8 0302082A */  slt   $at, $t8, $v0
/* 0B51FC 800B45FC 1020FFFB */  beqz  $at, .L800B45EC
/* 0B5200 800B4600 0062C023 */   subu  $t8, $v1, $v0
.L800B4604:
/* 0B5204 800B4604 8F392CFC */  lw    $t9, %lo(gParticleBehavioursAssetTable)($t9)
/* 0B5208 800B4608 00034080 */  sll   $t0, $v1, 2
/* 0B520C 800B460C 03284821 */  addu  $t1, $t9, $t0
/* 0B5210 800B4610 8D220000 */  lw    $v0, ($t1)
/* 0B5214 800B4614 03E00008 */  jr    $ra
/* 0B5218 800B4618 00000000 */   nop  