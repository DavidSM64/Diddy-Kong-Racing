glabel func_8008A8F8
/* 08B4F8 8008A8F8 00857024 */  and   $t6, $a0, $a1
/* 08B4FC 8008A8FC 11C00008 */  beqz  $t6, .L8008A920
/* 08B500 8008A900 3C03800E */   lui   $v1, %hi(gActiveMagicCodes) # $v1, 0x800e
/* 08B504 8008A904 2463FD98 */  addiu $v1, %lo(gActiveMagicCodes) # addiu $v1, $v1, -0x268
/* 08B508 8008A908 8C620000 */  lw    $v0, ($v1)
/* 08B50C 8008A90C 00C0C027 */  not   $t8, $a2
/* 08B510 8008A910 00827824 */  and   $t7, $a0, $v0
/* 08B514 8008A914 11E00002 */  beqz  $t7, .L8008A920
/* 08B518 8008A918 0058C824 */   and   $t9, $v0, $t8
/* 08B51C 8008A91C AC790000 */  sw    $t9, ($v1)
.L8008A920:
/* 08B520 8008A920 03E00008 */  jr    $ra
/* 08B524 8008A924 00000000 */   nop   

