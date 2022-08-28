glabel func_800B4578
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

