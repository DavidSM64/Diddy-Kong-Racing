glabel func_800B44D4
/* 0B50D4 800B44D4 8C8E0000 */  lw    $t6, ($a0)
/* 0B50D8 800B44D8 3C05800E */  lui   $a1, %hi(gParticlesAssetTableCount) # $a1, 0x800e
/* 0B50DC 800B44DC 25C30001 */  addiu $v1, $t6, 1
/* 0B50E0 800B44E0 24A52CE8 */  addiu $a1, %lo(gParticlesAssetTableCount) # addiu $a1, $a1, 0x2ce8
/* 0B50E4 800B44E4 AC830000 */  sw    $v1, ($a0)
/* 0B50E8 800B44E8 8CA20000 */  lw    $v0, ($a1)
/* 0B50EC 800B44EC 3C19800E */  lui   $t9, %hi(gParticlesAssetTable) # $t9, 0x800e
/* 0B50F0 800B44F0 0062082A */  slt   $at, $v1, $v0
/* 0B50F4 800B44F4 14200007 */  bnez  $at, .L800B4514
/* 0B50F8 800B44F8 0062C023 */   subu  $t8, $v1, $v0
.L800B44FC:
/* 0B50FC 800B44FC AC980000 */  sw    $t8, ($a0)
/* 0B5100 800B4500 8CA20000 */  lw    $v0, ($a1)
/* 0B5104 800B4504 03001825 */  move  $v1, $t8
/* 0B5108 800B4508 0302082A */  slt   $at, $t8, $v0
/* 0B510C 800B450C 1020FFFB */  beqz  $at, .L800B44FC
/* 0B5110 800B4510 0062C023 */   subu  $t8, $v1, $v0
.L800B4514:
/* 0B5114 800B4514 8F392CF0 */  lw    $t9, %lo(gParticlesAssetTable)($t9)
/* 0B5118 800B4518 00034080 */  sll   $t0, $v1, 2
/* 0B511C 800B451C 03284821 */  addu  $t1, $t9, $t0
/* 0B5120 800B4520 8D220000 */  lw    $v0, ($t1)
/* 0B5124 800B4524 03E00008 */  jr    $ra
/* 0B5128 800B4528 00000000 */   nop   