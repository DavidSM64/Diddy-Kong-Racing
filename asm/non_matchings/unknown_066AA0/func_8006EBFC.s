glabel func_8006EBFC
/* 06F7FC 8006EBFC 3C02800E */  lui   $v0, %hi(D_800DD37C) # $v0, 0x800e
/* 06F800 8006EC00 2442D37C */  addiu $v0, %lo(D_800DD37C) # addiu $v0, $v0, -0x2c84
/* 06F804 8006EC04 8C4E0000 */  lw    $t6, ($v0)
/* 06F808 8006EC08 00000000 */  nop   
/* 06F80C 8006EC0C 35CF0030 */  ori   $t7, $t6, 0x30
/* 06F810 8006EC10 03E00008 */  jr    $ra
/* 06F814 8006EC14 AC4F0000 */   sw    $t7, ($v0)

