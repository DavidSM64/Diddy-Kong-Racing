glabel func_800B4488
/* 0B5088 800B4488 3C03800E */  lui   $v1, %hi(gParticlesAssetTableCount) # $v1, 0x800e
/* 0B508C 800B448C 8C632CE8 */  lw    $v1, %lo(gParticlesAssetTableCount)($v1)
/* 0B5090 800B4490 3C0E800E */  lui   $t6, %hi(gParticlesAssetTable) # $t6, 0x800e
/* 0B5094 800B4494 0083082A */  slt   $at, $a0, $v1
/* 0B5098 800B4498 10200007 */  beqz  $at, .L800B44B8
/* 0B509C 800B449C 3C19800E */   lui   $t9, %hi(gParticlesAssetTable) # $t9, 0x800e
/* 0B50A0 800B44A0 8DCE2CF0 */  lw    $t6, %lo(gParticlesAssetTable)($t6)
/* 0B50A4 800B44A4 00047880 */  sll   $t7, $a0, 2
/* 0B50A8 800B44A8 01CFC021 */  addu  $t8, $t6, $t7
/* 0B50AC 800B44AC 8F020000 */  lw    $v0, ($t8)
/* 0B50B0 800B44B0 03E00008 */  jr    $ra
/* 0B50B4 800B44B4 00000000 */   nop   

.L800B44B8:
/* 0B50B8 800B44B8 8F392CF0 */  lw    $t9, %lo(gParticlesAssetTable)($t9)
/* 0B50BC 800B44BC 00034080 */  sll   $t0, $v1, 2
/* 0B50C0 800B44C0 03284821 */  addu  $t1, $t9, $t0
/* 0B50C4 800B44C4 8D22FFFC */  lw    $v0, -4($t1)
/* 0B50C8 800B44C8 00000000 */  nop   
/* 0B50CC 800B44CC 03E00008 */  jr    $ra
/* 0B50D0 800B44D0 00000000 */   nop   
