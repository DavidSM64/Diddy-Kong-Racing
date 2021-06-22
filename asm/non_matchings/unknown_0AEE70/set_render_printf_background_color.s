glabel set_render_printf_background_color
/* 0B6EB4 800B62B4 3C028013 */  lui   $v0, %hi(D_801285D8) # $v0, 0x8013
/* 0B6EB8 800B62B8 244285D8 */  addiu $v0, %lo(D_801285D8) # addiu $v0, $v0, -0x7a28
/* 0B6EBC 800B62BC 8C490000 */  lw    $t1, ($v0)
/* 0B6EC0 800B62C0 AFA40000 */  sw    $a0, ($sp)
/* 0B6EC4 800B62C4 AFA50004 */  sw    $a1, 4($sp)
/* 0B6EC8 800B62C8 AFA60008 */  sw    $a2, 8($sp)
/* 0B6ECC 800B62CC AFA7000C */  sw    $a3, 0xc($sp)
/* 0B6ED0 800B62D0 24080085 */  li    $t0, 133
/* 0B6ED4 800B62D4 A1280000 */  sb    $t0, ($t1)
/* 0B6ED8 800B62D8 8C4A0000 */  lw    $t2, ($v0)
/* 0B6EDC 800B62DC 00A07825 */  move  $t7, $a1
/* 0B6EE0 800B62E0 254B0001 */  addiu $t3, $t2, 1
/* 0B6EE4 800B62E4 AC4B0000 */  sw    $t3, ($v0)
/* 0B6EE8 800B62E8 A1640000 */  sb    $a0, ($t3)
/* 0B6EEC 800B62EC 8C4D0000 */  lw    $t5, ($v0)
/* 0B6EF0 800B62F0 01E02825 */  move  $a1, $t7
/* 0B6EF4 800B62F4 25AE0001 */  addiu $t6, $t5, 1
/* 0B6EF8 800B62F8 00C0C025 */  move  $t8, $a2
/* 0B6EFC 800B62FC AC4E0000 */  sw    $t6, ($v0)
/* 0B6F00 800B6300 03003025 */  move  $a2, $t8
/* 0B6F04 800B6304 A1C50000 */  sb    $a1, ($t6)
/* 0B6F08 800B6308 8C580000 */  lw    $t8, ($v0)
/* 0B6F0C 800B630C 00E0C825 */  move  $t9, $a3
/* 0B6F10 800B6310 03203825 */  move  $a3, $t9
/* 0B6F14 800B6314 27190001 */  addiu $t9, $t8, 1
/* 0B6F18 800B6318 AC590000 */  sw    $t9, ($v0)
/* 0B6F1C 800B631C A3260000 */  sb    $a2, ($t9)
/* 0B6F20 800B6320 8C490000 */  lw    $t1, ($v0)
/* 0B6F24 800B6324 00000000 */  nop   
/* 0B6F28 800B6328 252A0001 */  addiu $t2, $t1, 1
/* 0B6F2C 800B632C AC4A0000 */  sw    $t2, ($v0)
/* 0B6F30 800B6330 A1470000 */  sb    $a3, ($t2)
/* 0B6F34 800B6334 8C4C0000 */  lw    $t4, ($v0)
/* 0B6F38 800B6338 00000000 */  nop   
/* 0B6F3C 800B633C 258D0001 */  addiu $t5, $t4, 1
/* 0B6F40 800B6340 AC4D0000 */  sw    $t5, ($v0)
/* 0B6F44 800B6344 A1A00000 */  sb    $zero, ($t5)
/* 0B6F48 800B6348 8C4F0000 */  lw    $t7, ($v0)
/* 0B6F4C 800B634C 00000000 */  nop   
/* 0B6F50 800B6350 25F80001 */  addiu $t8, $t7, 1
/* 0B6F54 800B6354 03E00008 */  jr    $ra
/* 0B6F58 800B6358 AC580000 */   sw    $t8, ($v0)

