glabel func_800C73BC
/* 0C7FBC 800C73BC 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C7FC0 800C73C0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C7FC4 800C73C4 3C048013 */  lui   $a0, %hi(D_8012AAF0) # $a0, 0x8013
/* 0C7FC8 800C73C8 0C0322BC */  jal   func_800C8AF0
/* 0C7FCC 800C73CC 2484AAF0 */   addiu $a0, %lo(D_8012AAF0) # addiu $a0, $a0, -0x5510
/* 0C7FD0 800C73D0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C7FD4 800C73D4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0C7FD8 800C73D8 03E00008 */  jr    $ra
/* 0C7FDC 800C73DC 00000000 */   nop   

