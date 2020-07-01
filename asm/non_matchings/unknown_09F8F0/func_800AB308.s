glabel func_800AB308
/* 0ABF08 800AB308 3C028012 */  lui   $v0, %hi(D_80127BF8) # $v0, 0x8012
/* 0ABF0C 800AB30C 24427BF8 */  addiu $v0, %lo(D_80127BF8) # addiu $v0, $v0, 0x7bf8
/* 0ABF10 800AB310 84480002 */  lh    $t0, 2($v0)
/* 0ABF14 800AB314 84490000 */  lh    $t1, ($v0)
/* 0ABF18 800AB318 00047400 */  sll   $t6, $a0, 0x10
/* 0ABF1C 800AB31C 0005C400 */  sll   $t8, $a1, 0x10
/* 0ABF20 800AB320 0018CC03 */  sra   $t9, $t8, 0x10
/* 0ABF24 800AB324 000E7C03 */  sra   $t7, $t6, 0x10
/* 0ABF28 800AB328 AFA40000 */  sw    $a0, ($sp)
/* 0ABF2C 800AB32C AFA50004 */  sw    $a1, 4($sp)
/* 0ABF30 800AB330 0109082A */  slt   $at, $t0, $t1
/* 0ABF34 800AB334 03202825 */  move  $a1, $t9
/* 0ABF38 800AB338 10200004 */  beqz  $at, .L800AB34C
/* 0ABF3C 800AB33C 01E02025 */   move  $a0, $t7
/* 0ABF40 800AB340 A44F0000 */  sh    $t7, ($v0)
/* 0ABF44 800AB344 03E00008 */  jr    $ra
/* 0ABF48 800AB348 A4590002 */   sh    $t9, 2($v0)

.L800AB34C:
/* 0ABF4C 800AB34C A4450000 */  sh    $a1, ($v0)
/* 0ABF50 800AB350 A4440002 */  sh    $a0, 2($v0)
/* 0ABF54 800AB354 03E00008 */  jr    $ra
/* 0ABF58 800AB358 00000000 */   nop   

