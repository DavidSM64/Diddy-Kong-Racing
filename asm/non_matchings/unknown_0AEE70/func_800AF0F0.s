glabel func_800AF0F0
/* 0AFCF0 800AF0F0 8C820044 */  lw    $v0, 0x44($a0)
/* 0AFCF4 800AF0F4 00000000 */  nop   
/* 0AFCF8 800AF0F8 8C460000 */  lw    $a2, ($v0)
/* 0AFCFC 800AF0FC 8C43000C */  lw    $v1, 0xc($v0)
/* 0AFD00 800AF100 90C50000 */  lbu   $a1, ($a2)
/* 0AFD04 800AF104 90C70001 */  lbu   $a3, 1($a2)
/* 0AFD08 800AF108 24A5FFFF */  addiu $a1, $a1, -1
/* 0AFD0C 800AF10C 0005C140 */  sll   $t8, $a1, 5
/* 0AFD10 800AF110 24E7FFFF */  addiu $a3, $a3, -1
/* 0AFD14 800AF114 00074940 */  sll   $t1, $a3, 5
/* 0AFD18 800AF118 A4690006 */  sh    $t1, 6($v1)
/* 0AFD1C 800AF11C A4780008 */  sh    $t8, 8($v1)
/* 0AFD20 800AF120 A4780016 */  sh    $t8, 0x16($v1)
/* 0AFD24 800AF124 A4780018 */  sh    $t8, 0x18($v1)
/* 0AFD28 800AF128 A469001A */  sh    $t1, 0x1a($v1)
/* 0AFD2C 800AF12C 03E00008 */  jr    $ra
/* 0AFD30 800AF130 A478001C */   sh    $t8, 0x1c($v1)

