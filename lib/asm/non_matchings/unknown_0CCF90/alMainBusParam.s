glabel alMainBusParam
/* 0CCF90 800CC390 24010002 */  li    $at, 2
/* 0CCF94 800CC394 14A10008 */  bne   $a1, $at, .L800CC3B8
/* 0CCF98 800CC398 8C82001C */   lw    $v0, 0x1c($a0)
/* 0CCF9C 800CC39C 8C8E0014 */  lw    $t6, 0x14($a0)
/* 0CCFA0 800CC3A0 000E7880 */  sll   $t7, $t6, 2
/* 0CCFA4 800CC3A4 004FC021 */  addu  $t8, $v0, $t7
/* 0CCFA8 800CC3A8 AF060000 */  sw    $a2, ($t8)
/* 0CCFAC 800CC3AC 8C990014 */  lw    $t9, 0x14($a0)
/* 0CCFB0 800CC3B0 27280001 */  addiu $t0, $t9, 1
/* 0CCFB4 800CC3B4 AC880014 */  sw    $t0, 0x14($a0)
.L800CC3B8:
/* 0CCFB8 800CC3B8 03E00008 */  jr    $ra
/* 0CCFBC 800CC3BC 00001025 */   move  $v0, $zero

