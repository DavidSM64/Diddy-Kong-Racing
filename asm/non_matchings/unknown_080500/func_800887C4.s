glabel func_800887C4
/* 0893C4 800887C4 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0893C8 800887C8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0893CC 800887CC 3C04800E */  lui   $a0, %hi(D_800DF7C4) # $a0, 0x800e
/* 0893D0 800887D0 0C02712A */  jal   func_8009C4A8
/* 0893D4 800887D4 2484F7C4 */   addiu $a0, %lo(D_800DF7C4) # addiu $a0, $a0, -0x83c
/* 0893D8 800887D8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0893DC 800887DC 27BD0018 */  addiu $sp, $sp, 0x18
/* 0893E0 800887E0 03E00008 */  jr    $ra
/* 0893E4 800887E4 00000000 */   nop   

