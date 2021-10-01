glabel __osPackRequestData
/* 0CDAE8 800CCEE8 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0CDAEC 800CCEEC 308400FF */  andi  $a0, $a0, 0xff
/* 0CDAF0 800CCEF0 AFA00000 */  sw    $zero, ($sp)
.L800CCEF4:
/* 0CDAF4 800CCEF4 8FAE0000 */  lw    $t6, ($sp)
/* 0CDAF8 800CCEF8 8FB80000 */  lw    $t8, ($sp)
/* 0CDAFC 800CCEFC 3C018013 */  lui   $at, %hi(__osContPifRam) # $at, 0x8013
/* 0CDB00 800CCF00 000E7880 */  sll   $t7, $t6, 2
/* 0CDB04 800CCF04 002F0821 */  addu  $at, $at, $t7
/* 0CDB08 800CCF08 AC20CD50 */  sw    $zero, %lo(__osContPifRam)($at)
/* 0CDB0C 800CCF0C 27190001 */  addiu $t9, $t8, 1
/* 0CDB10 800CCF10 2B210010 */  slti  $at, $t9, 0x10
/* 0CDB14 800CCF14 1420FFF7 */  bnez  $at, .L800CCEF4
/* 0CDB18 800CCF18 AFB90000 */   sw    $t9, ($sp)
/* 0CDB1C 800CCF1C 3C198013 */  lui   $t9, %hi(__osMaxControllers) # $t9, 0x8013
/* 0CDB20 800CCF20 9339CD91 */  lbu   $t9, %lo(__osMaxControllers)($t9)
/* 0CDB24 800CCF24 3C098013 */  lui   $t1, %hi(__osContPifRam) # $t1, 0x8013
/* 0CDB28 800CCF28 24080001 */  li    $t0, 1
/* 0CDB2C 800CCF2C 3C018013 */  lui   $at, %hi(__osContPifRam) # $at, 0x8013
/* 0CDB30 800CCF30 2529CD50 */  addiu $t1, %lo(__osContPifRam) # addiu $t1, $t1, -0x32b0
/* 0CDB34 800CCF34 240A00FF */  li    $t2, 255
/* 0CDB38 800CCF38 240B0001 */  li    $t3, 1
/* 0CDB3C 800CCF3C 240C0003 */  li    $t4, 3
/* 0CDB40 800CCF40 240D00FF */  li    $t5, 255
/* 0CDB44 800CCF44 240E00FF */  li    $t6, 255
/* 0CDB48 800CCF48 240F00FF */  li    $t7, 255
/* 0CDB4C 800CCF4C 241800FF */  li    $t8, 255
/* 0CDB50 800CCF50 AC28CD8C */  sw    $t0, %lo(__osContPifRam+60)($at)
/* 0CDB54 800CCF54 AFA9000C */  sw    $t1, 0xc($sp)
/* 0CDB58 800CCF58 A3AA0004 */  sb    $t2, 4($sp)
/* 0CDB5C 800CCF5C A3AB0005 */  sb    $t3, 5($sp)
/* 0CDB60 800CCF60 A3AC0006 */  sb    $t4, 6($sp)
/* 0CDB64 800CCF64 A3A40007 */  sb    $a0, 7($sp)
/* 0CDB68 800CCF68 A3AD0008 */  sb    $t5, 8($sp)
/* 0CDB6C 800CCF6C A3AE0009 */  sb    $t6, 9($sp)
/* 0CDB70 800CCF70 A3AF000A */  sb    $t7, 0xa($sp)
/* 0CDB74 800CCF74 A3B8000B */  sb    $t8, 0xb($sp)
/* 0CDB78 800CCF78 1B200013 */  blez  $t9, .L800CCFC8
/* 0CDB7C 800CCF7C AFA00000 */   sw    $zero, ($sp)
.L800CCF80:
/* 0CDB80 800CCF80 27A90004 */  addiu $t1, $sp, 4
/* 0CDB84 800CCF84 8D210000 */  lw    $at, ($t1)
/* 0CDB88 800CCF88 8FA8000C */  lw    $t0, 0xc($sp)
/* 0CDB8C 800CCF8C 3C188013 */  lui   $t8, %hi(__osMaxControllers) # $t8, 0x8013
/* 0CDB90 800CCF90 A9010000 */  swl   $at, ($t0)
/* 0CDB94 800CCF94 B9010003 */  swr   $at, 3($t0)
/* 0CDB98 800CCF98 8D2B0004 */  lw    $t3, 4($t1)
/* 0CDB9C 800CCF9C A90B0004 */  swl   $t3, 4($t0)
/* 0CDBA0 800CCFA0 B90B0007 */  swr   $t3, 7($t0)
/* 0CDBA4 800CCFA4 8FAE0000 */  lw    $t6, ($sp)
/* 0CDBA8 800CCFA8 9318CD91 */  lbu   $t8, %lo(__osMaxControllers)($t8)
/* 0CDBAC 800CCFAC 8FAC000C */  lw    $t4, 0xc($sp)
/* 0CDBB0 800CCFB0 25CF0001 */  addiu $t7, $t6, 1
/* 0CDBB4 800CCFB4 01F8082A */  slt   $at, $t7, $t8
/* 0CDBB8 800CCFB8 258D0008 */  addiu $t5, $t4, 8
/* 0CDBBC 800CCFBC AFAF0000 */  sw    $t7, ($sp)
/* 0CDBC0 800CCFC0 1420FFEF */  bnez  $at, .L800CCF80
/* 0CDBC4 800CCFC4 AFAD000C */   sw    $t5, 0xc($sp)
.L800CCFC8:
/* 0CDBC8 800CCFC8 8FAA000C */  lw    $t2, 0xc($sp)
/* 0CDBCC 800CCFCC 241900FE */  li    $t9, 254
/* 0CDBD0 800CCFD0 27BD0010 */  addiu $sp, $sp, 0x10
/* 0CDBD4 800CCFD4 03E00008 */  jr    $ra
/* 0CDBD8 800CCFD8 A1590000 */   sb    $t9, ($t2)

/* 0CDBDC 800CCFDC 00000000 */  nop   
