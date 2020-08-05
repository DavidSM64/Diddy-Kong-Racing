glabel func_800C8560
/* 0C9160 800C8560 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C9164 800C8564 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C9168 800C8568 240E000D */  li    $t6, 13
/* 0C916C 800C856C AFA5001C */  sw    $a1, 0x1c($sp)
/* 0C9170 800C8570 A7AE0018 */  sh    $t6, 0x18($sp)
/* 0C9174 800C8574 27A50018 */  addiu $a1, $sp, 0x18
/* 0C9178 800C8578 24840048 */  addiu $a0, $a0, 0x48
/* 0C917C 800C857C 0C03246B */  jal   alEvtqPostEvent
/* 0C9180 800C8580 00003025 */   move  $a2, $zero
/* 0C9184 800C8584 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C9188 800C8588 27BD0028 */  addiu $sp, $sp, 0x28
/* 0C918C 800C858C 03E00008 */  jr    $ra
/* 0C9190 800C8590 00000000 */   nop   

/* 0C9194 800C8594 00000000 */  nop   
/* 0C9198 800C8598 00000000 */  nop   
/* 0C919C 800C859C 00000000 */  nop   

