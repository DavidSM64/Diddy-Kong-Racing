glabel alCSeqGetLoc
/* 0C8740 800C7B40 8CAE0000 */  lw    $t6, ($a1)
/* 0C8744 800C7B44 00801825 */  move  $v1, $a0
/* 0C8748 800C7B48 00803825 */  move  $a3, $a0
/* 0C874C 800C7B4C AC8E0004 */  sw    $t6, 4($a0)
/* 0C8750 800C7B50 8CAF0004 */  lw    $t7, 4($a1)
/* 0C8754 800C7B54 00001025 */  move  $v0, $zero
/* 0C8758 800C7B58 00A03025 */  move  $a2, $a1
/* 0C875C 800C7B5C AC8F000C */  sw    $t7, 0xc($a0)
/* 0C8760 800C7B60 8CB80008 */  lw    $t8, 8($a1)
/* 0C8764 800C7B64 00A04025 */  move  $t0, $a1
/* 0C8768 800C7B68 AC980010 */  sw    $t8, 0x10($a0)
/* 0C876C 800C7B6C 24040010 */  li    $a0, 16
.L800C7B70:
/* 0C8770 800C7B70 8CD9000C */  lw    $t9, 0xc($a2)
/* 0C8774 800C7B74 24420002 */  addiu $v0, $v0, 2
/* 0C8778 800C7B78 24630008 */  addiu $v1, $v1, 8
/* 0C877C 800C7B7C AC790010 */  sw    $t9, 0x10($v1)
/* 0C8780 800C7B80 8CC9004C */  lw    $t1, 0x4c($a2)
/* 0C8784 800C7B84 24C60008 */  addiu $a2, $a2, 8
/* 0C8788 800C7B88 24E70002 */  addiu $a3, $a3, 2
/* 0C878C 800C7B8C AC690050 */  sw    $t1, 0x50($v1)
/* 0C8790 800C7B90 910A008C */  lbu   $t2, 0x8c($t0)
/* 0C8794 800C7B94 25080002 */  addiu $t0, $t0, 2
/* 0C8798 800C7B98 A0EA0096 */  sb    $t2, 0x96($a3)
/* 0C879C 800C7B9C 910B009A */  lbu   $t3, 0x9a($t0)
/* 0C87A0 800C7BA0 A0EB00A6 */  sb    $t3, 0xa6($a3)
/* 0C87A4 800C7BA4 8CCC00A4 */  lw    $t4, 0xa4($a2)
/* 0C87A8 800C7BA8 AC6C00B0 */  sw    $t4, 0xb0($v1)
/* 0C87AC 800C7BAC 8CCD0008 */  lw    $t5, 8($a2)
/* 0C87B0 800C7BB0 AC6D0014 */  sw    $t5, 0x14($v1)
/* 0C87B4 800C7BB4 8CCE0048 */  lw    $t6, 0x48($a2)
/* 0C87B8 800C7BB8 AC6E0054 */  sw    $t6, 0x54($v1)
/* 0C87BC 800C7BBC 910F008B */  lbu   $t7, 0x8b($t0)
/* 0C87C0 800C7BC0 A0EF0097 */  sb    $t7, 0x97($a3)
/* 0C87C4 800C7BC4 9118009B */  lbu   $t8, 0x9b($t0)
/* 0C87C8 800C7BC8 A0F800A7 */  sb    $t8, 0xa7($a3)
/* 0C87CC 800C7BCC 8CD900A8 */  lw    $t9, 0xa8($a2)
/* 0C87D0 800C7BD0 1444FFE7 */  bne   $v0, $a0, .L800C7B70
/* 0C87D4 800C7BD4 AC7900B4 */   sw    $t9, 0xb4($v1)
/* 0C87D8 800C7BD8 03E00008 */  jr    $ra
/* 0C87DC 800C7BDC 00000000 */   nop   
