glabel func_8006D8A4
/* 06E4A4 8006D8A4 240E002C */  li    $t6, 44
/* 06E4A8 8006D8A8 3C01800E */  lui   $at, %hi(D_800DD390) # $at, 0x800e
/* 06E4AC 8006D8AC 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 06E4B0 8006D8B0 A02ED390 */  sb    $t6, %lo(D_800DD390)($at)
/* 06E4B4 8006D8B4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 06E4B8 8006D8B8 3C018012 */  lui   $at, %hi(D_80123515) # $at, 0x8012
/* 06E4BC 8006D8BC 0C025179 */  jal   func_800945E4
/* 06E4C0 8006D8C0 A0203515 */   sb    $zero, %lo(D_80123515)($at)
/* 06E4C4 8006D8C4 3C04800E */  lui   $a0, %hi(D_800DD408) # $a0, 0x800e
/* 06E4C8 8006D8C8 0C030076 */  jal   func_800C01D8
/* 06E4CC 8006D8CC 2484D408 */   addiu $a0, %lo(D_800DD408) # addiu $a0, $a0, -0x2bf8
/* 06E4D0 8006D8D0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 06E4D4 8006D8D4 27BD0018 */  addiu $sp, $sp, 0x18
/* 06E4D8 8006D8D8 03E00008 */  jr    $ra
/* 06E4DC 8006D8DC 00000000 */   nop   

