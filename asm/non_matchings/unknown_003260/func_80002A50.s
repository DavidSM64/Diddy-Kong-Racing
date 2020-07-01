glabel func_80002A50
/* 003650 80002A50 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 003654 80002A54 AFBF0014 */  sw    $ra, 0x14($sp)
/* 003658 80002A58 3C048011 */  lui   $a0, %hi(D_80115FB0) # $a0, 0x8011
/* 00365C 80002A5C 0C032268 */  jal   osStartThread
/* 003660 80002A60 24845FB0 */   addiu $a0, %lo(D_80115FB0) # addiu $a0, $a0, 0x5fb0
/* 003664 80002A64 8FBF0014 */  lw    $ra, 0x14($sp)
/* 003668 80002A68 27BD0018 */  addiu $sp, $sp, 0x18
/* 00366C 80002A6C 03E00008 */  jr    $ra
/* 003670 80002A70 00000000 */   nop   

