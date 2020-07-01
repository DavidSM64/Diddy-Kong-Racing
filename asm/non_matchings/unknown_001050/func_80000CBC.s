glabel func_80000CBC
/* 0018BC 80000CBC 3C018011 */  lui   $at, %hi(D_80115D38) # $at, 0x8011
/* 0018C0 80000CC0 AC205D38 */  sw    $zero, %lo(D_80115D38)($at)
/* 0018C4 80000CC4 3C018011 */  lui   $at, %hi(D_80115D3C) # $at, 0x8011
/* 0018C8 80000CC8 AC205D3C */  sw    $zero, %lo(D_80115D3C)($at)
/* 0018CC 80000CCC 3C013F80 */  li    $at, 0x3F800000 # 1.000000
/* 0018D0 80000CD0 44812000 */  mtc1  $at, $f4
/* 0018D4 80000CD4 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0018D8 80000CD8 3C04800E */  lui   $a0, %hi(D_800DC638) # $a0, 0x800e
/* 0018DC 80000CDC AFBF0014 */  sw    $ra, 0x14($sp)
/* 0018E0 80000CE0 3C01800E */  lui   $at, %hi(D_800DC650) # $at, 0x800e
/* 0018E4 80000CE4 9084C638 */  lbu   $a0, %lo(D_800DC638)($a0)
/* 0018E8 80000CE8 0C000664 */  jal   func_80001990
/* 0018EC 80000CEC E424C650 */   swc1  $f4, %lo(D_800DC650)($at)
/* 0018F0 80000CF0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0018F4 80000CF4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0018F8 80000CF8 03E00008 */  jr    $ra
/* 0018FC 80000CFC 00000000 */   nop   

