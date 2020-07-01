glabel func_80002A74
/* 003674 80002A74 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 003678 80002A78 AFBF0014 */  sw    $ra, 0x14($sp)
/* 00367C 80002A7C 3C048011 */  lui   $a0, %hi(D_80115FB0) # $a0, 0x8011
/* 003680 80002A80 0C0322BC */  jal   func_800C8AF0
/* 003684 80002A84 24845FB0 */   addiu $a0, %lo(D_80115FB0) # addiu $a0, $a0, 0x5fb0
/* 003688 80002A88 8FBF0014 */  lw    $ra, 0x14($sp)
/* 00368C 80002A8C 27BD0018 */  addiu $sp, $sp, 0x18
/* 003690 80002A90 03E00008 */  jr    $ra
/* 003694 80002A94 00000000 */   nop   

