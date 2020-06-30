glabel func_800B4A08
/* 0B5608 800B4A08 3C01800E */  lui   $at, 0x800e
/* 0B560C 800B4A0C 03E00008 */  jr    $ra
/* 0B5610 800B4A10 AC242EF0 */   sw    $a0, 0x2ef0($at)

/* 0B5614 800B4A14 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0B5618 800B4A18 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B561C 800B4A1C AFA60028 */  sw    $a2, 0x28($sp)
/* 0B5620 800B4A20 AFA50024 */  sw    $a1, 0x24($sp)
/* 0B5624 800B4A24 AFA7002C */  sw    $a3, 0x2c($sp)
/* 0B5628 800B4A28 0C02D290 */  jal   func_800B4A40
/* 0B562C 800B4A2C 27A60028 */   addiu $a2, $sp, 0x28
/* 0B5630 800B4A30 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0B5634 800B4A34 27BD0020 */  addiu $sp, $sp, 0x20
/* 0B5638 800B4A38 03E00008 */  jr    $ra
/* 0B563C 800B4A3C 00000000 */   nop   

