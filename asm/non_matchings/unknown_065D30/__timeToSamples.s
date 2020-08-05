glabel __timeToSamples
/* 0663C4 800657C4 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0663C8 800657C8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0663CC 800657CC 0C0195D5 */  jal   __timeToSamplesNoRound
/* 0663D0 800657D0 00000000 */   nop   
/* 0663D4 800657D4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0663D8 800657D8 2401FFF0 */  li    $at, -16
/* 0663DC 800657DC 00417024 */  and   $t6, $v0, $at
/* 0663E0 800657E0 01C01025 */  move  $v0, $t6
/* 0663E4 800657E4 03E00008 */  jr    $ra
/* 0663E8 800657E8 27BD0018 */   addiu $sp, $sp, 0x18

