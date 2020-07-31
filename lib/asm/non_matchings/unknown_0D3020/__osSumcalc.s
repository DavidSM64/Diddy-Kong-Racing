glabel __osSumcalc
/* 0D5EF0 800D52F0 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0D5EF4 800D52F4 AFA00008 */  sw    $zero, 8($sp)
/* 0D5EF8 800D52F8 AFA40004 */  sw    $a0, 4($sp)
/* 0D5EFC 800D52FC 18A00010 */  blez  $a1, .L800D5340
/* 0D5F00 800D5300 AFA0000C */   sw    $zero, 0xc($sp)
.L800D5304:
/* 0D5F04 800D5304 8FAF0004 */  lw    $t7, 4($sp)
/* 0D5F08 800D5308 8FAE0008 */  lw    $t6, 8($sp)
/* 0D5F0C 800D530C 8FAB000C */  lw    $t3, 0xc($sp)
/* 0D5F10 800D5310 91F80000 */  lbu   $t8, ($t7)
/* 0D5F14 800D5314 25E80001 */  addiu $t0, $t7, 1
/* 0D5F18 800D5318 256C0001 */  addiu $t4, $t3, 1
/* 0D5F1C 800D531C 01D8C821 */  addu  $t9, $t6, $t8
/* 0D5F20 800D5320 AFB90008 */  sw    $t9, 8($sp)
/* 0D5F24 800D5324 8FA90008 */  lw    $t1, 8($sp)
/* 0D5F28 800D5328 0185082A */  slt   $at, $t4, $a1
/* 0D5F2C 800D532C AFAC000C */  sw    $t4, 0xc($sp)
/* 0D5F30 800D5330 312AFFFF */  andi  $t2, $t1, 0xffff
/* 0D5F34 800D5334 AFA80004 */  sw    $t0, 4($sp)
/* 0D5F38 800D5338 1420FFF2 */  bnez  $at, .L800D5304
/* 0D5F3C 800D533C AFAA0008 */   sw    $t2, 8($sp)
.L800D5340:
/* 0D5F40 800D5340 97A2000A */  lhu   $v0, 0xa($sp)
/* 0D5F44 800D5344 03E00008 */  jr    $ra
/* 0D5F48 800D5348 27BD0010 */   addiu $sp, $sp, 0x10

