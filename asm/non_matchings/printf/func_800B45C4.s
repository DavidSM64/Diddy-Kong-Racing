glabel func_800B45C4
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