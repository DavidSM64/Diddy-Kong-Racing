glabel __setInstChanState
/* 00B998 8000AD98 00061080 */  sll   $v0, $a2, 2
/* 00B99C 8000AD9C 8C8E0060 */  lw    $t6, 0x60($a0)
/* 00B9A0 8000ADA0 00461021 */  addu  $v0, $v0, $a2
/* 00B9A4 8000ADA4 00021080 */  sll   $v0, $v0, 2
/* 00B9A8 8000ADA8 01C27821 */  addu  $t7, $t6, $v0
/* 00B9AC 8000ADAC ADE50000 */  sw    $a1, ($t7)
/* 00B9B0 8000ADB0 8C990060 */  lw    $t9, 0x60($a0)
/* 00B9B4 8000ADB4 90B80001 */  lbu   $t8, 1($a1)
/* 00B9B8 8000ADB8 03224021 */  addu  $t0, $t9, $v0
/* 00B9BC 8000ADBC A1180007 */  sb    $t8, 7($t0)
/* 00B9C0 8000ADC0 8C8A0060 */  lw    $t2, 0x60($a0)
/* 00B9C4 8000ADC4 90A90000 */  lbu   $t1, ($a1)
/* 00B9C8 8000ADC8 01425821 */  addu  $t3, $t2, $v0
/* 00B9CC 8000ADCC A1690009 */  sb    $t1, 9($t3)
/* 00B9D0 8000ADD0 8C8D0060 */  lw    $t5, 0x60($a0)
/* 00B9D4 8000ADD4 90AC0002 */  lbu   $t4, 2($a1)
/* 00B9D8 8000ADD8 01A27021 */  addu  $t6, $t5, $v0
/* 00B9DC 8000ADDC A1CC0008 */  sb    $t4, 8($t6)
/* 00B9E0 8000ADE0 8C990060 */  lw    $t9, 0x60($a0)
/* 00B9E4 8000ADE4 84AF000C */  lh    $t7, 0xc($a1)
/* 00B9E8 8000ADE8 0322C021 */  addu  $t8, $t9, $v0
/* 00B9EC 8000ADEC 03E00008 */  jr    $ra
/* 00B9F0 8000ADF0 A70F0004 */   sh    $t7, 4($t8)

