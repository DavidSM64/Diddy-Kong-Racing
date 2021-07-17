glabel func_800AEE14
/* 0AFA14 800AEE14 240E0003 */  li    $t6, 3
/* 0AFA18 800AEE18 A48E0004 */  sh    $t6, 4($a0)
/* 0AFA1C 800AEE1C 8CAF0000 */  lw    $t7, ($a1)
/* 0AFA20 800AEE20 3C03800E */  lui   $v1, %hi(D_800E2E68) # $v1, 0x800e
/* 0AFA24 800AEE24 AC8F0008 */  sw    $t7, 8($a0)
/* 0AFA28 800AEE28 8CA20000 */  lw    $v0, ($a1)
/* 0AFA2C 800AEE2C 24632E68 */  addiu $v1, %lo(D_800E2E68) # addiu $v1, $v1, 0x2e68
/* 0AFA30 800AEE30 00003825 */  move  $a3, $zero
/* 0AFA34 800AEE34 240800FF */  li    $t0, 255
.L800AEE38:
/* 0AFA38 800AEE38 84780000 */  lh    $t8, ($v1)
/* 0AFA3C 800AEE3C 24E70001 */  addiu $a3, $a3, 1
/* 0AFA40 800AEE40 A4580000 */  sh    $t8, ($v0)
/* 0AFA44 800AEE44 84790002 */  lh    $t9, 2($v1)
/* 0AFA48 800AEE48 00074C00 */  sll   $t1, $a3, 0x10
/* 0AFA4C 800AEE4C 00093C03 */  sra   $a3, $t1, 0x10
/* 0AFA50 800AEE50 28E10003 */  slti  $at, $a3, 3
/* 0AFA54 800AEE54 24630004 */  addiu $v1, $v1, 4
/* 0AFA58 800AEE58 A4400004 */  sh    $zero, 4($v0)
/* 0AFA5C 800AEE5C A0480006 */  sb    $t0, 6($v0)
/* 0AFA60 800AEE60 A0480007 */  sb    $t0, 7($v0)
/* 0AFA64 800AEE64 A0480008 */  sb    $t0, 8($v0)
/* 0AFA68 800AEE68 A0480009 */  sb    $t0, 9($v0)
/* 0AFA6C 800AEE6C 2442000A */  addiu $v0, $v0, 0xa
/* 0AFA70 800AEE70 1420FFF1 */  bnez  $at, .L800AEE38
/* 0AFA74 800AEE74 A459FFF8 */   sh    $t9, -8($v0)
/* 0AFA78 800AEE78 ACA20000 */  sw    $v0, ($a1)
/* 0AFA7C 800AEE7C 240B0001 */  li    $t3, 1
/* 0AFA80 800AEE80 A48B0006 */  sh    $t3, 6($a0)
/* 0AFA84 800AEE84 8CCC0000 */  lw    $t4, ($a2)
/* 0AFA88 800AEE88 240D0040 */  li    $t5, 64
/* 0AFA8C 800AEE8C AC8C000C */  sw    $t4, 0xc($a0)
/* 0AFA90 800AEE90 8CC30000 */  lw    $v1, ($a2)
/* 0AFA94 800AEE94 240E0002 */  li    $t6, 2
/* 0AFA98 800AEE98 240F0001 */  li    $t7, 1
/* 0AFA9C 800AEE9C A06D0000 */  sb    $t5, ($v1)
/* 0AFAA0 800AEEA0 A06E0001 */  sb    $t6, 1($v1)
/* 0AFAA4 800AEEA4 A06F0002 */  sb    $t7, 2($v1)
/* 0AFAA8 800AEEA8 A0600003 */  sb    $zero, 3($v1)
/* 0AFAAC 800AEEAC 24630010 */  addiu $v1, $v1, 0x10
/* 0AFAB0 800AEEB0 03E00008 */  jr    $ra
/* 0AFAB4 800AEEB4 ACC30000 */   sw    $v1, ($a2)

