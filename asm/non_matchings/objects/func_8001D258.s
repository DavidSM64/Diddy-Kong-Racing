glabel func_8001D258
/* 01DE58 8001D258 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 01DE5C 8001D25C AFA60028 */  sw    $a2, 0x28($sp)
/* 01DE60 8001D260 AFA7002C */  sw    $a3, 0x2c($sp)
/* 01DE64 8001D264 87AE002E */  lh    $t6, 0x2e($sp)
/* 01DE68 8001D268 87AF0032 */  lh    $t7, 0x32($sp)
/* 01DE6C 8001D26C 87A7002A */  lh    $a3, 0x2a($sp)
/* 01DE70 8001D270 AFBF001C */  sw    $ra, 0x1c($sp)
/* 01DE74 8001D274 44067000 */  mfc1  $a2, $f14
/* 01DE78 8001D278 3C048012 */  lui   $a0, %hi(D_8011AF30) # $a0, 0x8012
/* 01DE7C 8001D27C 44056000 */  mfc1  $a1, $f12
/* 01DE80 8001D280 2484AF30 */  addiu $a0, %lo(D_8011AF30) # addiu $a0, $a0, -0x50d0
/* 01DE84 8001D284 AFAE0010 */  sw    $t6, 0x10($sp)
/* 01DE88 8001D288 0C00752D */  jal   func_8001D4B4
/* 01DE8C 8001D28C AFAF0014 */   sw    $t7, 0x14($sp)
/* 01DE90 8001D290 8FBF001C */  lw    $ra, 0x1c($sp)
/* 01DE94 8001D294 27BD0020 */  addiu $sp, $sp, 0x20
/* 01DE98 8001D298 03E00008 */  jr    $ra
/* 01DE9C 8001D29C 00000000 */   nop   
