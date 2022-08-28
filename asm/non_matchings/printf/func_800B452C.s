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

