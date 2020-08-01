glabel func_800CD0A4
/* 0CDCA4 800CD0A4 3C0F8013 */  lui   $t7, %hi(__osMaxControllers) # $t7, 0x8013
/* 0CDCA8 800CD0A8 91EFCD91 */  lbu   $t7, %lo(__osMaxControllers)($t7)
/* 0CDCAC 800CD0AC 3C0E8013 */  lui   $t6, %hi(D_8012CD50) # $t6, 0x8013
/* 0CDCB0 800CD0B0 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0CDCB4 800CD0B4 25CECD50 */  addiu $t6, %lo(D_8012CD50) # addiu $t6, $t6, -0x32b0
/* 0CDCB8 800CD0B8 AFAE000C */  sw    $t6, 0xc($sp)
/* 0CDCBC 800CD0BC 19E00021 */  blez  $t7, .L800CD144
/* 0CDCC0 800CD0C0 AFA00000 */   sw    $zero, ($sp)
.L800CD0C4:
/* 0CDCC4 800CD0C4 8FB9000C */  lw    $t9, 0xc($sp)
/* 0CDCC8 800CD0C8 27B80004 */  addiu $t8, $sp, 4
/* 0CDCCC 800CD0CC 8B210000 */  lwl   $at, ($t9)
/* 0CDCD0 800CD0D0 9B210003 */  lwr   $at, 3($t9)
/* 0CDCD4 800CD0D4 AF010000 */  sw    $at, ($t8)
/* 0CDCD8 800CD0D8 8B290004 */  lwl   $t1, 4($t9)
/* 0CDCDC 800CD0DC 9B290007 */  lwr   $t1, 7($t9)
/* 0CDCE0 800CD0E0 AF090004 */  sw    $t1, 4($t8)
/* 0CDCE4 800CD0E4 93AA0006 */  lbu   $t2, 6($sp)
/* 0CDCE8 800CD0E8 314B00C0 */  andi  $t3, $t2, 0xc0
/* 0CDCEC 800CD0EC 000B6103 */  sra   $t4, $t3, 4
/* 0CDCF0 800CD0F0 A08C0004 */  sb    $t4, 4($a0)
/* 0CDCF4 800CD0F4 908D0004 */  lbu   $t5, 4($a0)
/* 0CDCF8 800CD0F8 15A00007 */  bnez  $t5, .L800CD118
/* 0CDCFC 800CD0FC 00000000 */   nop   
/* 0CDD00 800CD100 97AE0008 */  lhu   $t6, 8($sp)
/* 0CDD04 800CD104 A48E0000 */  sh    $t6, ($a0)
/* 0CDD08 800CD108 83AF000A */  lb    $t7, 0xa($sp)
/* 0CDD0C 800CD10C A08F0002 */  sb    $t7, 2($a0)
/* 0CDD10 800CD110 83A8000B */  lb    $t0, 0xb($sp)
/* 0CDD14 800CD114 A0880003 */  sb    $t0, 3($a0)
.L800CD118:
/* 0CDD18 800CD118 8FB80000 */  lw    $t8, ($sp)
/* 0CDD1C 800CD11C 3C0B8013 */  lui   $t3, %hi(__osMaxControllers) # $t3, 0x8013
/* 0CDD20 800CD120 916BCD91 */  lbu   $t3, %lo(__osMaxControllers)($t3)
/* 0CDD24 800CD124 8FA9000C */  lw    $t1, 0xc($sp)
/* 0CDD28 800CD128 27190001 */  addiu $t9, $t8, 1
/* 0CDD2C 800CD12C 032B082A */  slt   $at, $t9, $t3
/* 0CDD30 800CD130 252A0008 */  addiu $t2, $t1, 8
/* 0CDD34 800CD134 AFAA000C */  sw    $t2, 0xc($sp)
/* 0CDD38 800CD138 AFB90000 */  sw    $t9, ($sp)
/* 0CDD3C 800CD13C 1420FFE1 */  bnez  $at, .L800CD0C4
/* 0CDD40 800CD140 24840006 */   addiu $a0, $a0, 6
.L800CD144:
/* 0CDD44 800CD144 03E00008 */  jr    $ra
/* 0CDD48 800CD148 27BD0010 */   addiu $sp, $sp, 0x10

