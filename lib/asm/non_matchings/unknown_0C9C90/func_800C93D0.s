glabel func_800C93D0
/* 0C9FD0 800C93D0 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C9FD4 800C93D4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C9FD8 800C93D8 00803025 */  move  $a2, $a0
/* 0C9FDC 800C93DC AFA60018 */  sw    $a2, 0x18($sp)
/* 0C9FE0 800C93E0 24040001 */  li    $a0, 1
/* 0C9FE4 800C93E4 0C03268C */  jal   func_800C9A30
/* 0C9FE8 800C93E8 AFA5001C */   sw    $a1, 0x1c($sp)
/* 0C9FEC 800C93EC 8FA60018 */  lw    $a2, 0x18($sp)
/* 0C9FF0 800C93F0 8FA5001C */  lw    $a1, 0x1c($sp)
/* 0C9FF4 800C93F4 00402025 */  move  $a0, $v0
/* 0C9FF8 800C93F8 8CCE0020 */  lw    $t6, 0x20($a2)
/* 0C9FFC 800C93FC ACAE0010 */  sw    $t6, 0x10($a1)
/* 0CA000 800C9400 8CCF0000 */  lw    $t7, ($a2)
/* 0CA004 800C9404 ACAF0000 */  sw    $t7, ($a1)
/* 0CA008 800C9408 0C03268C */  jal   func_800C9A30
/* 0CA00C 800C940C ACC50000 */   sw    $a1, ($a2)
/* 0CA010 800C9410 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CA014 800C9414 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CA018 800C9418 03E00008 */  jr    $ra
/* 0CA01C 800C941C 00000000 */   nop   

