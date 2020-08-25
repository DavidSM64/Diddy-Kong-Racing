glabel func_8003FEF4
/* 040AF4 8003FEF4 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 040AF8 8003FEF8 AFBF0044 */  sw    $ra, 0x44($sp)
/* 040AFC 8003FEFC AFB00040 */  sw    $s0, 0x40($sp)
/* 040B00 8003FF00 AFA40048 */  sw    $a0, 0x48($sp)
/* 040B04 8003FF04 8C820064 */  lw    $v0, 0x64($a0)
/* 040B08 8003FF08 90AF0008 */  lbu   $t7, 8($a1)
/* 040B0C 8003FF0C 00A08025 */  move  $s0, $a1
/* 040B10 8003FF10 A04F0000 */  sb    $t7, ($v0)
/* 040B14 8003FF14 94B8000A */  lhu   $t8, 0xa($a1)
/* 040B18 8003FF18 31E400FF */  andi  $a0, $t7, 0xff
/* 040B1C 8003FF1C A4580002 */  sh    $t8, 2($v0)
/* 040B20 8003FF20 90B9000C */  lbu   $t9, 0xc($a1)
/* 040B24 8003FF24 00000000 */  nop   
/* 040B28 8003FF28 A059000C */  sb    $t9, 0xc($v0)
/* 040B2C 8003FF2C 90A8000D */  lbu   $t0, 0xd($a1)
/* 040B30 8003FF30 AC400008 */  sw    $zero, 8($v0)
/* 040B34 8003FF34 A048000D */  sb    $t0, 0xd($v0)
/* 040B38 8003FF38 94A9000E */  lhu   $t1, 0xe($a1)
/* 040B3C 8003FF3C 00000000 */  nop   
/* 040B40 8003FF40 A4490004 */  sh    $t1, 4($v0)
/* 040B44 8003FF44 90AA0012 */  lbu   $t2, 0x12($a1)
/* 040B48 8003FF48 00000000 */  nop   
/* 040B4C 8003FF4C A04A0011 */  sb    $t2, 0x11($v0)
/* 040B50 8003FF50 90AB0011 */  lbu   $t3, 0x11($a1)
/* 040B54 8003FF54 00000000 */  nop   
/* 040B58 8003FF58 A04B0010 */  sb    $t3, 0x10($v0)
/* 040B5C 8003FF5C 90AC0009 */  lbu   $t4, 9($a1)
/* 040B60 8003FF60 00000000 */  nop   
/* 040B64 8003FF64 A04C000E */  sb    $t4, 0xe($v0)
/* 040B68 8003FF68 90AD0010 */  lbu   $t5, 0x10($a1)
/* 040B6C 8003FF6C 00000000 */  nop   
/* 040B70 8003FF70 A04D000F */  sb    $t5, 0xf($v0)
/* 040B74 8003FF74 90AE0013 */  lbu   $t6, 0x13($a1)
/* 040B78 8003FF78 3305FFFF */  andi  $a1, $t8, 0xffff
/* 040B7C 8003FF7C A04E0012 */  sb    $t6, 0x12($v0)
/* 040B80 8003FF80 86190006 */  lh    $t9, 6($s0)
/* 040B84 8003FF84 86180004 */  lh    $t8, 4($s0)
/* 040B88 8003FF88 44994000 */  mtc1  $t9, $f8
/* 040B8C 8003FF8C 860F0002 */  lh    $t7, 2($s0)
/* 040B90 8003FF90 468042A0 */  cvt.s.w $f10, $f8
/* 040B94 8003FF94 44983000 */  mtc1  $t8, $f6
/* 040B98 8003FF98 448F2000 */  mtc1  $t7, $f4
/* 040B9C 8003FF9C E7AA0010 */  swc1  $f10, 0x10($sp)
/* 040BA0 8003FFA0 9048000F */  lbu   $t0, 0xf($v0)
/* 040BA4 8003FFA4 468031A0 */  cvt.s.w $f6, $f6
/* 040BA8 8003FFA8 AFA80014 */  sw    $t0, 0x14($sp)
/* 040BAC 8003FFAC 9049000E */  lbu   $t1, 0xe($v0)
/* 040BB0 8003FFB0 46802120 */  cvt.s.w $f4, $f4
/* 040BB4 8003FFB4 AFA90018 */  sw    $t1, 0x18($sp)
/* 040BB8 8003FFB8 904A0010 */  lbu   $t2, 0x10($v0)
/* 040BBC 8003FFBC 44062000 */  mfc1  $a2, $f4
/* 040BC0 8003FFC0 AFAA001C */  sw    $t2, 0x1c($sp)
/* 040BC4 8003FFC4 904B0012 */  lbu   $t3, 0x12($v0)
/* 040BC8 8003FFC8 44073000 */  mfc1  $a3, $f6
/* 040BCC 8003FFCC AFAB0020 */  sw    $t3, 0x20($sp)
/* 040BD0 8003FFD0 944C0004 */  lhu   $t4, 4($v0)
/* 040BD4 8003FFD4 00000000 */  nop   
/* 040BD8 8003FFD8 AFAC0024 */  sw    $t4, 0x24($sp)
/* 040BDC 8003FFDC 904D0011 */  lbu   $t5, 0x11($v0)
/* 040BE0 8003FFE0 00000000 */  nop   
/* 040BE4 8003FFE4 AFAD0028 */  sw    $t5, 0x28($sp)
/* 040BE8 8003FFE8 904E000C */  lbu   $t6, 0xc($v0)
/* 040BEC 8003FFEC 00000000 */  nop   
/* 040BF0 8003FFF0 AFAE002C */  sw    $t6, 0x2c($sp)
/* 040BF4 8003FFF4 904F000D */  lbu   $t7, 0xd($v0)
/* 040BF8 8003FFF8 0C002629 */  jal   func_800098A4
/* 040BFC 8003FFFC AFAF0030 */   sw    $t7, 0x30($sp)
/* 040C00 80040000 8FA40048 */  lw    $a0, 0x48($sp)
/* 040C04 80040004 0C003FEE */  jal   particlePtrList_addObject
/* 040C08 80040008 00000000 */   nop   
/* 040C0C 8004000C 8FBF0044 */  lw    $ra, 0x44($sp)
/* 040C10 80040010 8FB00040 */  lw    $s0, 0x40($sp)
/* 040C14 80040014 03E00008 */  jr    $ra
/* 040C18 80040018 27BD0048 */   addiu $sp, $sp, 0x48

