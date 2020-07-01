glabel func_8007A2D0
/* 07AED0 8007A2D0 00057880 */  sll   $t7, $a1, 2
/* 07AED4 8007A2D4 8C830000 */  lw    $v1, ($a0)
/* 07AED8 8007A2D8 31F8FFFF */  andi  $t8, $t7, 0xffff
/* 07AEDC 8007A2DC 0018CA00 */  sll   $t9, $t8, 8
/* 07AEE0 8007A2E0 3C01BC00 */  lui   $at, 0xbc00
/* 07AEE4 8007A2E4 03214025 */  or    $t0, $t9, $at
/* 07AEE8 8007A2E8 3C018000 */  lui   $at, 0x8000
/* 07AEEC 8007A2EC 246E0008 */  addiu $t6, $v1, 8
/* 07AEF0 8007A2F0 AC8E0000 */  sw    $t6, ($a0)
/* 07AEF4 8007A2F4 00C15021 */  addu  $t2, $a2, $at
/* 07AEF8 8007A2F8 35090006 */  ori   $t1, $t0, 6
/* 07AEFC 8007A2FC AC690000 */  sw    $t1, ($v1)
/* 07AF00 8007A300 03E00008 */  jr    $ra
/* 07AF04 8007A304 AC6A0004 */   sw    $t2, 4($v1)

/* 07AF08 8007A308 00000000 */  nop   
/* 07AF0C 8007A30C 00000000 */  nop   

