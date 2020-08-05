glabel func_800C85A0
/* 0C91A0 800C85A0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C91A4 800C85A4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C91A8 800C85A8 240E000F */  li    $t6, 15
/* 0C91AC 800C85AC A7AE0018 */  sh    $t6, 0x18($sp)
/* 0C91B0 800C85B0 27A50018 */  addiu $a1, $sp, 0x18
/* 0C91B4 800C85B4 24840048 */  addiu $a0, $a0, 0x48
/* 0C91B8 800C85B8 0C03246B */  jal   alEvtqPostEvent
/* 0C91BC 800C85BC 00003025 */   move  $a2, $zero
/* 0C91C0 800C85C0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0C91C4 800C85C4 27BD0028 */  addiu $sp, $sp, 0x28
/* 0C91C8 800C85C8 03E00008 */  jr    $ra
/* 0C91CC 800C85CC 00000000 */   nop   

