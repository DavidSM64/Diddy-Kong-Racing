glabel func_800C4318
/* 0C4F18 800C4318 3C0F8013 */  lui   $t7, %hi(gNumberOfFonts) # $t7, 0x8013
/* 0C4F1C 800C431C 8DEFA7E0 */  lw    $t7, %lo(gNumberOfFonts)($t7)
/* 0C4F20 800C4320 AFA50004 */  sw    $a1, 4($sp)
/* 0C4F24 800C4324 008F082A */  slt   $at, $a0, $t7
/* 0C4F28 800C4328 10200014 */  beqz  $at, .L800C437C
/* 0C4F2C 800C432C 30AE00FF */   andi  $t6, $a1, 0xff
/* 0C4F30 800C4330 3C198013 */  lui   $t9, %hi(gFonts) # $t9, 0x8013
/* 0C4F34 800C4334 8F39A7E4 */  lw    $t9, %lo(gFonts)($t9)
/* 0C4F38 800C4338 0004C280 */  sll   $t8, $a0, 0xa
/* 0C4F3C 800C433C 03191821 */  addu  $v1, $t8, $t9
/* 0C4F40 800C4340 90680028 */  lbu   $t0, 0x28($v1)
/* 0C4F44 800C4344 25C5FFE0 */  addiu $a1, $t6, -0x20
/* 0C4F48 800C4348 1100000C */  beqz  $t0, .L800C437C
/* 0C4F4C 800C434C 30A900FF */   andi  $t1, $a1, 0xff
/* 0C4F50 800C4350 000950C0 */  sll   $t2, $t1, 3
/* 0C4F54 800C4354 006A5821 */  addu  $t3, $v1, $t2
/* 0C4F58 800C4358 91640100 */  lbu   $a0, 0x100($t3)
/* 0C4F5C 800C435C 240100FF */  li    $at, 255
/* 0C4F60 800C4360 10810006 */  beq   $a0, $at, .L800C437C
/* 0C4F64 800C4364 00001025 */   move  $v0, $zero
/* 0C4F68 800C4368 00046080 */  sll   $t4, $a0, 2
/* 0C4F6C 800C436C 006C6821 */  addu  $t5, $v1, $t4
/* 0C4F70 800C4370 8DA20080 */  lw    $v0, 0x80($t5)
/* 0C4F74 800C4374 03E00008 */  jr    $ra
/* 0C4F78 800C4378 00000000 */   nop   
.L800C437C:
/* 0C4F7C 800C437C 03E00008 */  jr    $ra
/* 0C4F80 800C4380 00000000 */   nop   

