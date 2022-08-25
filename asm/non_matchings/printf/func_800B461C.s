glabel func_800B461C
/* 0B521C 800B461C 8C8E0000 */  lw    $t6, ($a0)
/* 0B5220 800B4620 3C08800E */  lui   $t0, %hi(gParticleBehavioursAssetTable) # $t0, 0x800e
/* 0B5224 800B4624 25C3FFFF */  addiu $v1, $t6, -1
/* 0B5228 800B4628 04610009 */  bgez  $v1, .L800B4650
/* 0B522C 800B462C AC830000 */   sw    $v1, ($a0)
/* 0B5230 800B4630 3C02800E */  lui   $v0, %hi(gParticleBehavioursAssetTableCount) # $v0, 0x800e
/* 0B5234 800B4634 24422CF4 */  addiu $v0, %lo(gParticleBehavioursAssetTableCount) # addiu $v0, $v0, 0x2cf4
.L800B4638:
/* 0B5238 800B4638 8C580000 */  lw    $t8, ($v0)
/* 0B523C 800B463C 00000000 */  nop   
/* 0B5240 800B4640 0078C821 */  addu  $t9, $v1, $t8
/* 0B5244 800B4644 AC990000 */  sw    $t9, ($a0)
/* 0B5248 800B4648 0720FFFB */  bltz  $t9, .L800B4638
/* 0B524C 800B464C 03201825 */   move  $v1, $t9
.L800B4650:
/* 0B5250 800B4650 8D082CFC */  lw    $t0, %lo(gParticleBehavioursAssetTable)($t0)
/* 0B5254 800B4654 00034880 */  sll   $t1, $v1, 2
/* 0B5258 800B4658 01095021 */  addu  $t2, $t0, $t1
/* 0B525C 800B465C 8D420000 */  lw    $v0, ($t2)
/* 0B5260 800B4660 03E00008 */  jr    $ra
/* 0B5264 800B4664 00000000 */   nop   