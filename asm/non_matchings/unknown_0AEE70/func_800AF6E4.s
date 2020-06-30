glabel func_800AF6E4
/* 0B02E4 800AF6E4 8C8E006C */  lw    $t6, 0x6c($a0)
/* 0B02E8 800AF6E8 00057940 */  sll   $t7, $a1, 5
/* 0B02EC 800AF6EC 01CF1021 */  addu  $v0, $t6, $t7
/* 0B02F0 800AF6F0 84580004 */  lh    $t8, 4($v0)
/* 0B02F4 800AF6F4 00000000 */  nop   
/* 0B02F8 800AF6F8 33197FFF */  andi  $t9, $t8, 0x7fff
/* 0B02FC 800AF6FC A4590004 */  sh    $t9, 4($v0)
/* 0B0300 800AF700 8488001A */  lh    $t0, 0x1a($a0)
/* 0B0304 800AF704 00000000 */  nop   
/* 0B0308 800AF708 2509FFFF */  addiu $t1, $t0, -1
/* 0B030C 800AF70C 03E00008 */  jr    $ra
/* 0B0310 800AF710 A489001A */   sh    $t1, 0x1a($a0)

