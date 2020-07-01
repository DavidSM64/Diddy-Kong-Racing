glabel MenuCautionInit
/* 08CFB4 8008C3B4 240E003C */  li    $t6, 60
/* 08CFB8 8008C3B8 3C018012 */  lui   $at, %hi(D_801263C4) # $at, 0x8012
/* 08CFBC 8008C3BC 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 08CFC0 8008C3C0 AC2E63C4 */  sw    $t6, %lo(D_801263C4)($at)
/* 08CFC4 8008C3C4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 08CFC8 8008C3C8 3C01800E */  lui   $at, %hi(D_800DF47C) # $at, 0x800e
/* 08CFCC 8008C3CC AC20F47C */  sw    $zero, %lo(D_800DF47C)($at)
/* 08CFD0 8008C3D0 0C03105C */  jal   func_800C4170
/* 08CFD4 8008C3D4 24040002 */   li    $a0, 2
/* 08CFD8 8008C3D8 3C04800E */  lui   $a0, %hi(D_800DF77C) # $a0, 0x800e
/* 08CFDC 8008C3DC 0C030076 */  jal   func_800C01D8
/* 08CFE0 8008C3E0 2484F77C */   addiu $a0, %lo(D_800DF77C) # addiu $a0, $a0, -0x884
/* 08CFE4 8008C3E4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 08CFE8 8008C3E8 240F0001 */  li    $t7, 1
/* 08CFEC 8008C3EC 3C01800E */  lui   $at, %hi(D_800DF498) # $at, 0x800e
/* 08CFF0 8008C3F0 AC2FF498 */  sw    $t7, %lo(D_800DF498)($at)
/* 08CFF4 8008C3F4 03E00008 */  jr    $ra
/* 08CFF8 8008C3F8 27BD0018 */   addiu $sp, $sp, 0x18

