glabel func_8003F0DC
/* 03FCDC 8003F0DC 3C028012 */  lui   $v0, %hi(D_8011D4DC) # $v0, 0x8012
/* 03FCE0 8003F0E0 2442D4DC */  addiu $v0, %lo(D_8011D4DC) # addiu $v0, $v0, -0x2b24
/* 03FCE4 8003F0E4 8C4E0000 */  lw    $t6, ($v0)
/* 03FCE8 8003F0E8 00000000 */  nop   
/* 03FCEC 8003F0EC 25CFFFFF */  addiu $t7, $t6, -1
/* 03FCF0 8003F0F0 03E00008 */  jr    $ra
/* 03FCF4 8003F0F4 AC4F0000 */   sw    $t7, ($v0)

