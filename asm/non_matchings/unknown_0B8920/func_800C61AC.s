glabel func_800C61AC
/* 0C6DAC 800C61AC 908E0001 */  lbu   $t6, 1($a0)
/* 0C6DB0 800C61B0 90830000 */  lbu   $v1, ($a0)
/* 0C6DB4 800C61B4 90980002 */  lbu   $t8, 2($a0)
/* 0C6DB8 800C61B8 90880003 */  lbu   $t0, 3($a0)
/* 0C6DBC 800C61BC 000E7A00 */  sll   $t7, $t6, 8
/* 0C6DC0 800C61C0 006F1825 */  or    $v1, $v1, $t7
/* 0C6DC4 800C61C4 0018CC00 */  sll   $t9, $t8, 0x10
/* 0C6DC8 800C61C8 00791825 */  or    $v1, $v1, $t9
/* 0C6DCC 800C61CC 00084E00 */  sll   $t1, $t0, 0x18
/* 0C6DD0 800C61D0 24840003 */  addiu $a0, $a0, 3
/* 0C6DD4 800C61D4 03E00008 */  jr    $ra
/* 0C6DD8 800C61D8 00691025 */   or    $v0, $v1, $t1

