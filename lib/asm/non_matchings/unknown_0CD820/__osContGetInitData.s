glabel __osContGetInitData
/* 0CDA18 800CCE18 3C0F8013 */  lui   $t7, %hi(__osMaxControllers) # $t7, 0x8013
/* 0CDA1C 800CCE1C 91EFCD91 */  lbu   $t7, %lo(__osMaxControllers)($t7)
/* 0CDA20 800CCE20 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CDA24 800CCE24 3C0E8013 */  lui   $t6, %hi(__osContPifRam) # $t6, 0x8013
/* 0CDA28 800CCE28 25CECD50 */  addiu $t6, %lo(__osContPifRam) # addiu $t6, $t6, -0x32b0
/* 0CDA2C 800CCE2C A3A00007 */  sb    $zero, 7($sp)
/* 0CDA30 800CCE30 AFAE0014 */  sw    $t6, 0x14($sp)
/* 0CDA34 800CCE34 19E00028 */  blez  $t7, .L800CCED8
/* 0CDA38 800CCE38 AFA00008 */   sw    $zero, 8($sp)
.L800CCE3C:
/* 0CDA3C 800CCE3C 8FB90014 */  lw    $t9, 0x14($sp)
/* 0CDA40 800CCE40 27B8000C */  addiu $t8, $sp, 0xc
/* 0CDA44 800CCE44 8B210000 */  lwl   $at, ($t9)
/* 0CDA48 800CCE48 9B210003 */  lwr   $at, 3($t9)
/* 0CDA4C 800CCE4C AF010000 */  sw    $at, ($t8)
/* 0CDA50 800CCE50 8B290004 */  lwl   $t1, 4($t9)
/* 0CDA54 800CCE54 9B290007 */  lwr   $t1, 7($t9)
/* 0CDA58 800CCE58 AF090004 */  sw    $t1, 4($t8)
/* 0CDA5C 800CCE5C 93AA000E */  lbu   $t2, 0xe($sp)
/* 0CDA60 800CCE60 314B00C0 */  andi  $t3, $t2, 0xc0
/* 0CDA64 800CCE64 000B6103 */  sra   $t4, $t3, 4
/* 0CDA68 800CCE68 A0AC0003 */  sb    $t4, 3($a1)
/* 0CDA6C 800CCE6C 90AD0003 */  lbu   $t5, 3($a1)
/* 0CDA70 800CCE70 15A0000E */  bnez  $t5, .L800CCEAC
/* 0CDA74 800CCE74 00000000 */   nop   
/* 0CDA78 800CCE78 93AE0011 */  lbu   $t6, 0x11($sp)
/* 0CDA7C 800CCE7C 93A80010 */  lbu   $t0, 0x10($sp)
/* 0CDA80 800CCE80 240B0001 */  li    $t3, 1
/* 0CDA84 800CCE84 000E7A00 */  sll   $t7, $t6, 8
/* 0CDA88 800CCE88 01E8C025 */  or    $t8, $t7, $t0
/* 0CDA8C 800CCE8C A4B80000 */  sh    $t8, ($a1)
/* 0CDA90 800CCE90 93B90012 */  lbu   $t9, 0x12($sp)
/* 0CDA94 800CCE94 A0B90002 */  sb    $t9, 2($a1)
/* 0CDA98 800CCE98 8FAA0008 */  lw    $t2, 8($sp)
/* 0CDA9C 800CCE9C 93A90007 */  lbu   $t1, 7($sp)
/* 0CDAA0 800CCEA0 014B6004 */  sllv  $t4, $t3, $t2
/* 0CDAA4 800CCEA4 012C6825 */  or    $t5, $t1, $t4
/* 0CDAA8 800CCEA8 A3AD0007 */  sb    $t5, 7($sp)
.L800CCEAC:
/* 0CDAAC 800CCEAC 8FAE0008 */  lw    $t6, 8($sp)
/* 0CDAB0 800CCEB0 3C198013 */  lui   $t9, %hi(__osMaxControllers) # $t9, 0x8013
/* 0CDAB4 800CCEB4 9339CD91 */  lbu   $t9, %lo(__osMaxControllers)($t9)
/* 0CDAB8 800CCEB8 8FA80014 */  lw    $t0, 0x14($sp)
/* 0CDABC 800CCEBC 25CF0001 */  addiu $t7, $t6, 1
/* 0CDAC0 800CCEC0 01F9082A */  slt   $at, $t7, $t9
/* 0CDAC4 800CCEC4 25180008 */  addiu $t8, $t0, 8
/* 0CDAC8 800CCEC8 AFB80014 */  sw    $t8, 0x14($sp)
/* 0CDACC 800CCECC AFAF0008 */  sw    $t7, 8($sp)
/* 0CDAD0 800CCED0 1420FFDA */  bnez  $at, .L800CCE3C
/* 0CDAD4 800CCED4 24A50004 */   addiu $a1, $a1, 4
.L800CCED8:
/* 0CDAD8 800CCED8 93AB0007 */  lbu   $t3, 7($sp)
/* 0CDADC 800CCEDC 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CDAE0 800CCEE0 03E00008 */  jr    $ra
/* 0CDAE4 800CCEE4 A08B0000 */   sb    $t3, ($a0)

