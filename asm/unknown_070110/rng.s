glabel set_rng_seed
/* 07050C 8006F90C 3C01800E */  lui   $at, %hi(D_800DD434)
/* 070510 8006F910 03E00008 */  jr    $ra
/* 070514 8006F914 AC24D434 */   sw    $a0, %lo(D_800DD434)($at)

glabel save_rng_seed
/* 070518 8006F918 3C04800E */  lui   $a0, %hi(D_800DD434)
/* 07051C 8006F91C 8C84D434 */  lw    $a0, %lo(D_800DD434)($a0)
/* 070520 8006F920 3C01800E */  lui   $at, %hi(D_800DD438)
/* 070524 8006F924 03E00008 */  jr    $ra
/* 070528 8006F928 AC24D438 */   sw    $a0, %lo(D_800DD438)($at)

glabel load_rng_seed
/* 07052C 8006F92C 3C04800E */  lui   $a0, %hi(D_800DD438)
/* 070530 8006F930 8C84D438 */  lw    $a0, %lo(D_800DD438)($a0)
/* 070534 8006F934 3C01800E */  lui   $at, %hi(D_800DD434)
/* 070538 8006F938 03E00008 */  jr    $ra
/* 07053C 8006F93C AC24D434 */   sw    $a0, %lo(D_800DD434)($at)

glabel get_rng_seed
/* 070540 8006F940 3C02800E */  lui   $v0, %hi(D_800DD434)
/* 070544 8006F944 03E00008 */  jr    $ra
/* 070548 8006F948 8C42D434 */   lw    $v0, %lo(D_800DD434)($v0)

/*
 * func_8006F94C(start, end) = Gets a random number within a range. 
 * Start is inclusive, end is exclusive; also changes the RNG seed.
 * 
 *  func_8006F94C(0, 5) will return a number from 0 to 4.
 *  func_8006F94C(20, 30) will return a number from 20 to 29.
*/
glabel func_8006F94C
/* 07054C 8006F94C 3C08800E */  lui   $t0, %hi(D_800DD434) # $t0, 0x800e
/* 070550 8006F950 8D08D434 */  lw    $t0, %lo(D_800DD434)($t0)
/* 070554 8006F954 3C01800E */  lui   $at, %hi(D_800DD434) # $at, 0x800e
/* 070558 8006F958 00A42822 */  sub   $a1, $a1, $a0
/* 07055C 8006F95C 00084FFC */  dsll32 $t1, $t0, 0x1f
/* 070560 8006F960 000857F8 */  dsll  $t2, $t0, 0x1f
/* 070564 8006F964 00094FFA */  dsrl  $t1, $t1, 0x1f
/* 070568 8006F968 000A503E */  dsrl32 $t2, $t2, 0
/* 07056C 8006F96C 00085B3C */  dsll32 $t3, $t0, 0xc
/* 070570 8006F970 012A4825 */  or    $t1, $t1, $t2
/* 070574 8006F974 000B583E */  dsrl32 $t3, $t3, 0
/* 070578 8006F978 012B4826 */  xor   $t1, $t1, $t3
/* 07057C 8006F97C 00095D3A */  dsrl  $t3, $t1, 0x14
/* 070580 8006F980 316B0FFF */  andi  $t3, $t3, 0xfff
/* 070584 8006F984 01694026 */  xor   $t0, $t3, $t1
/* 070588 8006F988 AC28D434 */  sw    $t0, %lo(D_800DD434)($at)
/* 07058C 8006F98C 20A50001 */  addi  $a1, $a1, 1
/* 070590 8006F990 01044023 */  subu  $t0, $t0, $a0
/* 070594 8006F994 0105001B */  divu  $zero, $t0, $a1
/* 070598 8006F998 00004012 */  mflo  $t0
/* 07059C 8006F99C 00001010 */  mfhi  $v0
/* 0705A0 8006F9A0 00441020 */  add   $v0, $v0, $a0
/* 0705A4 8006F9A4 14A00002 */  bnez  $a1, .L8006F9B0
/* 0705A8 8006F9A8 00000000 */   nop   
/* 0705AC 8006F9AC 0007000D */  break 7
.L8006F9B0:
/* 0705B0 8006F9B0 03E00008 */  jr    $ra
/* 0705B4 8006F9B4 00000000 */   nop   
