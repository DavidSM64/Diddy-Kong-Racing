glabel func_8006EB78
/* 06F778 8006EB78 3C02800E */  lui   $v0, %hi(D_800DD37C) # $v0, 0x800e
/* 06F77C 8006EB7C 2442D37C */  addiu $v0, %lo(D_800DD37C) # addiu $v0, $v0, -0x2c84
/* 06F780 8006EB80 8C4E0000 */  lw    $t6, ($v0)
/* 06F784 8006EB84 2401FCFF */  li    $at, -769
/* 06F788 8006EB88 30880003 */  andi  $t0, $a0, 3
/* 06F78C 8006EB8C 01C17824 */  and   $t7, $t6, $at
/* 06F790 8006EB90 35F90004 */  ori   $t9, $t7, 4
/* 06F794 8006EB94 00084A00 */  sll   $t1, $t0, 8
/* 06F798 8006EB98 AC4F0000 */  sw    $t7, ($v0)
/* 06F79C 8006EB9C 03295025 */  or    $t2, $t9, $t1
/* 06F7A0 8006EBA0 03E00008 */  jr    $ra
/* 06F7A4 8006EBA4 AC4A0000 */   sw    $t2, ($v0)

