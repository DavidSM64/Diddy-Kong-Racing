glabel func_800C7850
/* 0C8450 800C7850 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C8454 800C7854 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C8458 800C7858 AFA5002C */  sw    $a1, 0x2c($sp)
/* 0C845C 800C785C 00A07025 */  move  $t6, $a1
/* 0C8460 800C7860 240F000A */  li    $t7, 10
/* 0C8464 800C7864 A7AF0018 */  sh    $t7, 0x18($sp)
/* 0C8468 800C7868 A7AE001C */  sh    $t6, 0x1c($sp)
/* 0C846C 800C786C 27A50018 */  addiu $a1, $sp, 0x18
/* 0C8470 800C7870 24840048 */  addiu $a0, $a0, 0x48
/* 0C8474 800C7874 0C03246B */  jal   func_800C91AC
/* 0C8478 800C7878 00003025 */   move  $a2, $zero
/* 0C847C 800C787C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C8480 800C7880 27BD0028 */  addiu $sp, $sp, 0x28
/* 0C8484 800C7884 03E00008 */  jr    $ra
/* 0C8488 800C7888 00000000 */   nop   

/* 0C848C 800C788C 00000000 */  nop   

