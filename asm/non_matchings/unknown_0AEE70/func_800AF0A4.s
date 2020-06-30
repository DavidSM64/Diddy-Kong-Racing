glabel func_800AF0A4
/* 0AFCA4 800AF0A4 8C820044 */  lw    $v0, 0x44($a0)
/* 0AFCA8 800AF0A8 00000000 */  nop   
/* 0AFCAC 800AF0AC 8C460000 */  lw    $a2, ($v0)
/* 0AFCB0 800AF0B0 8C43000C */  lw    $v1, 0xc($v0)
/* 0AFCB4 800AF0B4 90C50000 */  lbu   $a1, ($a2)
/* 0AFCB8 800AF0B8 90C70001 */  lbu   $a3, 1($a2)
/* 0AFCBC 800AF0BC 24AEFFFF */  addiu $t6, $a1, -1
/* 0AFCC0 800AF0C0 000E7D40 */  sll   $t7, $t6, 0x15
/* 0AFCC4 800AF0C4 000FC403 */  sra   $t8, $t7, 0x10
/* 0AFCC8 800AF0C8 24E7FFFF */  addiu $a3, $a3, -1
/* 0AFCCC 800AF0CC 00074940 */  sll   $t1, $a3, 5
/* 0AFCD0 800AF0D0 00185043 */  sra   $t2, $t8, 1
/* 0AFCD4 800AF0D4 A46A0004 */  sh    $t2, 4($v1)
/* 0AFCD8 800AF0D8 A4600006 */  sh    $zero, 6($v1)
/* 0AFCDC 800AF0DC A4600008 */  sh    $zero, 8($v1)
/* 0AFCE0 800AF0E0 A469000A */  sh    $t1, 0xa($v1)
/* 0AFCE4 800AF0E4 A478000C */  sh    $t8, 0xc($v1)
/* 0AFCE8 800AF0E8 03E00008 */  jr    $ra
/* 0AFCEC 800AF0EC A469000E */   sh    $t1, 0xe($v1)

