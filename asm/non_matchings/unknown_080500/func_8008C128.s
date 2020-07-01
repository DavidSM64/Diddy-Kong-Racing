glabel func_8008C128
/* 08CD28 8008C128 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 08CD2C 8008C12C AFBF0014 */  sw    $ra, 0x14($sp)
/* 08CD30 8008C130 3C04800E */  lui   $a0, %hi(D_800DFDC8) # $a0, 0x800e
/* 08CD34 8008C134 0C02712A */  jal   func_8009C4A8
/* 08CD38 8008C138 2484FDC8 */   addiu $a0, %lo(D_800DFDC8) # addiu $a0, $a0, -0x238
/* 08CD3C 8008C13C 0C01C42C */  jal   func_800710B0
/* 08CD40 8008C140 00002025 */   move  $a0, $zero
/* 08CD44 8008C144 0C03108B */  jal   func_800C422C
/* 08CD48 8008C148 24040002 */   li    $a0, 2
/* 08CD4C 8008C14C 0C01C42C */  jal   func_800710B0
/* 08CD50 8008C150 24040002 */   li    $a0, 2
/* 08CD54 8008C154 8FBF0014 */  lw    $ra, 0x14($sp)
/* 08CD58 8008C158 3C01800E */  lui   $at, %hi(D_800DFFD0) # $at, 0x800e
/* 08CD5C 8008C15C AC20FFD0 */  sw    $zero, %lo(D_800DFFD0)($at)
/* 08CD60 8008C160 03E00008 */  jr    $ra
/* 08CD64 8008C164 27BD0018 */   addiu $sp, $sp, 0x18

