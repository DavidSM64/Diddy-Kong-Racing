glabel func_800AF134
/* 0AFD34 800AF134 3C0E800E */  lui   $t6, %hi(gParticlesAssetTableCount) # $t6, 0x800e
/* 0AFD38 800AF138 8DCE2CE8 */  lw    $t6, %lo(gParticlesAssetTableCount)($t6)
/* 0AFD3C 800AF13C 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0AFD40 800AF140 00CE082A */  slt   $at, $a2, $t6
/* 0AFD44 800AF144 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0AFD48 800AF148 14200002 */  bnez  $at, .L800AF154
/* 0AFD4C 800AF14C AFA7002C */   sw    $a3, 0x2c($sp)
/* 0AFD50 800AF150 00003025 */  move  $a2, $zero
.L800AF154:
/* 0AFD54 800AF154 3C0F800E */  lui   $t7, %hi(gParticleBehaviorsAssetTableCount) # $t7, 0x800e
/* 0AFD58 800AF158 8DEF2CF4 */  lw    $t7, %lo(gParticleBehaviorsAssetTableCount)($t7)
/* 0AFD5C 800AF15C 3C18800E */  lui   $t8, %hi(gParticleBehaviorsAssetTable) # $t8, 0x800e
/* 0AFD60 800AF160 00AF082A */  slt   $at, $a1, $t7
/* 0AFD64 800AF164 14200002 */  bnez  $at, .L800AF170
/* 0AFD68 800AF168 00000000 */   nop   
/* 0AFD6C 800AF16C 00002825 */  move  $a1, $zero
.L800AF170:
/* 0AFD70 800AF170 8F182CFC */  lw    $t8, %lo(gParticleBehaviorsAssetTable)($t8)
/* 0AFD74 800AF174 0005C880 */  sll   $t9, $a1, 2
/* 0AFD78 800AF178 84890008 */  lh    $t1, 8($a0)
/* 0AFD7C 800AF17C 03194021 */  addu  $t0, $t8, $t9
/* 0AFD80 800AF180 8D020000 */  lw    $v0, ($t0)
/* 0AFD84 800AF184 14C90005 */  bne   $a2, $t1, .L800AF19C
/* 0AFD88 800AF188 00000000 */   nop   
/* 0AFD8C 800AF18C 8C8A0000 */  lw    $t2, ($a0)
/* 0AFD90 800AF190 00000000 */  nop   
/* 0AFD94 800AF194 104A000F */  beq   $v0, $t2, .L800AF1D4
/* 0AFD98 800AF198 8FBF001C */   lw    $ra, 0x1c($sp)
.L800AF19C:
/* 0AFD9C 800AF19C AFA40020 */  sw    $a0, 0x20($sp)
/* 0AFDA0 800AF1A0 AFA50024 */  sw    $a1, 0x24($sp)
/* 0AFDA4 800AF1A4 0C02C898 */  jal   func_800B2260
/* 0AFDA8 800AF1A8 AFA60028 */   sw    $a2, 0x28($sp)
/* 0AFDAC 800AF1AC 87AB0032 */  lh    $t3, 0x32($sp)
/* 0AFDB0 800AF1B0 87AC0036 */  lh    $t4, 0x36($sp)
/* 0AFDB4 800AF1B4 8FA40020 */  lw    $a0, 0x20($sp)
/* 0AFDB8 800AF1B8 8FA50024 */  lw    $a1, 0x24($sp)
/* 0AFDBC 800AF1BC 8FA60028 */  lw    $a2, 0x28($sp)
/* 0AFDC0 800AF1C0 87A7002E */  lh    $a3, 0x2e($sp)
/* 0AFDC4 800AF1C4 AFAB0010 */  sw    $t3, 0x10($sp)
/* 0AFDC8 800AF1C8 0C02BCA7 */  jal   func_800AF29C
/* 0AFDCC 800AF1CC AFAC0014 */   sw    $t4, 0x14($sp)
/* 0AFDD0 800AF1D0 8FBF001C */  lw    $ra, 0x1c($sp)
.L800AF1D4:
/* 0AFDD4 800AF1D4 27BD0020 */  addiu $sp, $sp, 0x20
/* 0AFDD8 800AF1D8 03E00008 */  jr    $ra
/* 0AFDDC 800AF1DC 00000000 */   nop   

