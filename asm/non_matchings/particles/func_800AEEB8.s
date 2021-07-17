glabel func_800AEEB8
/* 0AFAB8 800AEEB8 240E0004 */  li    $t6, 4
/* 0AFABC 800AEEBC A48E0004 */  sh    $t6, 4($a0)
/* 0AFAC0 800AEEC0 8CAF0000 */  lw    $t7, ($a1)
/* 0AFAC4 800AEEC4 3C03800E */  lui   $v1, %hi(D_800E2E74) # $v1, 0x800e
/* 0AFAC8 800AEEC8 AC8F0008 */  sw    $t7, 8($a0)
/* 0AFACC 800AEECC 8CA20000 */  lw    $v0, ($a1)
/* 0AFAD0 800AEED0 24632E74 */  addiu $v1, %lo(D_800E2E74) # addiu $v1, $v1, 0x2e74
/* 0AFAD4 800AEED4 00003825 */  move  $a3, $zero
/* 0AFAD8 800AEED8 240800FF */  li    $t0, 255
.L800AEEDC:
/* 0AFADC 800AEEDC 84780000 */  lh    $t8, ($v1)
/* 0AFAE0 800AEEE0 24E70001 */  addiu $a3, $a3, 1
/* 0AFAE4 800AEEE4 A4580000 */  sh    $t8, ($v0)
/* 0AFAE8 800AEEE8 84790002 */  lh    $t9, 2($v1)
/* 0AFAEC 800AEEEC 00075400 */  sll   $t2, $a3, 0x10
/* 0AFAF0 800AEEF0 000A3C03 */  sra   $a3, $t2, 0x10
/* 0AFAF4 800AEEF4 28E10004 */  slti  $at, $a3, 4
/* 0AFAF8 800AEEF8 24630004 */  addiu $v1, $v1, 4
/* 0AFAFC 800AEEFC A4400004 */  sh    $zero, 4($v0)
/* 0AFB00 800AEF00 A0480006 */  sb    $t0, 6($v0)
/* 0AFB04 800AEF04 A0480007 */  sb    $t0, 7($v0)
/* 0AFB08 800AEF08 A0480008 */  sb    $t0, 8($v0)
/* 0AFB0C 800AEF0C A0480009 */  sb    $t0, 9($v0)
/* 0AFB10 800AEF10 2442000A */  addiu $v0, $v0, 0xa
/* 0AFB14 800AEF14 1420FFF1 */  bnez  $at, .L800AEEDC
/* 0AFB18 800AEF18 A459FFF8 */   sh    $t9, -8($v0)
/* 0AFB1C 800AEF1C ACA20000 */  sw    $v0, ($a1)
/* 0AFB20 800AEF20 240C0002 */  li    $t4, 2
/* 0AFB24 800AEF24 A48C0006 */  sh    $t4, 6($a0)
/* 0AFB28 800AEF28 8CCD0000 */  lw    $t5, ($a2)
/* 0AFB2C 800AEF2C 24070040 */  li    $a3, 64
/* 0AFB30 800AEF30 AC8D000C */  sw    $t5, 0xc($a0)
/* 0AFB34 800AEF34 8CC30000 */  lw    $v1, ($a2)
/* 0AFB38 800AEF38 24080003 */  li    $t0, 3
/* 0AFB3C 800AEF3C 24090001 */  li    $t1, 1
/* 0AFB40 800AEF40 240E0002 */  li    $t6, 2
/* 0AFB44 800AEF44 A0670000 */  sb    $a3, ($v1)
/* 0AFB48 800AEF48 A0680001 */  sb    $t0, 1($v1)
/* 0AFB4C 800AEF4C A4600004 */  sh    $zero, 4($v1)
/* 0AFB50 800AEF50 A0690002 */  sb    $t1, 2($v1)
/* 0AFB54 800AEF54 A460000A */  sh    $zero, 0xa($v1)
/* 0AFB58 800AEF58 A0600003 */  sb    $zero, 3($v1)
/* 0AFB5C 800AEF5C A460000C */  sh    $zero, 0xc($v1)
/* 0AFB60 800AEF60 A460000E */  sh    $zero, 0xe($v1)
/* 0AFB64 800AEF64 A0670010 */  sb    $a3, 0x10($v1)
/* 0AFB68 800AEF68 A0680011 */  sb    $t0, 0x11($v1)
/* 0AFB6C 800AEF6C A4600014 */  sh    $zero, 0x14($v1)
/* 0AFB70 800AEF70 A06E0012 */  sb    $t6, 0x12($v1)
/* 0AFB74 800AEF74 A0690013 */  sb    $t1, 0x13($v1)
/* 0AFB78 800AEF78 A460001E */  sh    $zero, 0x1e($v1)
/* 0AFB7C 800AEF7C 24630020 */  addiu $v1, $v1, 0x20
/* 0AFB80 800AEF80 03E00008 */  jr    $ra
/* 0AFB84 800AEF84 ACC30000 */   sw    $v1, ($a2)

