glabel alCSeqSetLoc
/* 0C86A0 800C7AA0 8C8E0004 */  lw    $t6, 4($a0)
/* 0C86A4 800C7AA4 00803025 */  move  $a2, $a0
/* 0C86A8 800C7AA8 00804025 */  move  $t0, $a0
/* 0C86AC 800C7AAC ACAE0000 */  sw    $t6, ($a1)
/* 0C86B0 800C7AB0 8C8F000C */  lw    $t7, 0xc($a0)
/* 0C86B4 800C7AB4 00001025 */  move  $v0, $zero
/* 0C86B8 800C7AB8 00A01825 */  move  $v1, $a1
/* 0C86BC 800C7ABC ACAF0004 */  sw    $t7, 4($a1)
/* 0C86C0 800C7AC0 8C980010 */  lw    $t8, 0x10($a0)
/* 0C86C4 800C7AC4 24040010 */  li    $a0, 16
/* 0C86C8 800C7AC8 00A03825 */  move  $a3, $a1
/* 0C86CC 800C7ACC ACB80008 */  sw    $t8, 8($a1)
.L800C7AD0:
/* 0C86D0 800C7AD0 8CD90018 */  lw    $t9, 0x18($a2)
/* 0C86D4 800C7AD4 24420002 */  addiu $v0, $v0, 2
/* 0C86D8 800C7AD8 24630008 */  addiu $v1, $v1, 8
/* 0C86DC 800C7ADC AC790004 */  sw    $t9, 4($v1)
/* 0C86E0 800C7AE0 8CC90058 */  lw    $t1, 0x58($a2)
/* 0C86E4 800C7AE4 24C60008 */  addiu $a2, $a2, 8
/* 0C86E8 800C7AE8 24E70002 */  addiu $a3, $a3, 2
/* 0C86EC 800C7AEC AC690044 */  sw    $t1, 0x44($v1)
/* 0C86F0 800C7AF0 910A0098 */  lbu   $t2, 0x98($t0)
/* 0C86F4 800C7AF4 25080002 */  addiu $t0, $t0, 2
/* 0C86F8 800C7AF8 A0EA008A */  sb    $t2, 0x8a($a3)
/* 0C86FC 800C7AFC 910B00A6 */  lbu   $t3, 0xa6($t0)
/* 0C8700 800C7B00 A0EB009A */  sb    $t3, 0x9a($a3)
/* 0C8704 800C7B04 8CCC00B0 */  lw    $t4, 0xb0($a2)
/* 0C8708 800C7B08 AC6C00A4 */  sw    $t4, 0xa4($v1)
/* 0C870C 800C7B0C 8CCD0014 */  lw    $t5, 0x14($a2)
/* 0C8710 800C7B10 AC6D0008 */  sw    $t5, 8($v1)
/* 0C8714 800C7B14 8CCE0054 */  lw    $t6, 0x54($a2)
/* 0C8718 800C7B18 AC6E0048 */  sw    $t6, 0x48($v1)
/* 0C871C 800C7B1C 910F0097 */  lbu   $t7, 0x97($t0)
/* 0C8720 800C7B20 A0EF008B */  sb    $t7, 0x8b($a3)
/* 0C8724 800C7B24 911800A7 */  lbu   $t8, 0xa7($t0)
/* 0C8728 800C7B28 A0F8009B */  sb    $t8, 0x9b($a3)
/* 0C872C 800C7B2C 8CD900B4 */  lw    $t9, 0xb4($a2)
/* 0C8730 800C7B30 1444FFE7 */  bne   $v0, $a0, .L800C7AD0
/* 0C8734 800C7B34 AC7900A8 */   sw    $t9, 0xa8($v1)
/* 0C8738 800C7B38 03E00008 */  jr    $ra
/* 0C873C 800C7B3C 00000000 */   nop   
