glabel get_random_number_from_range
/* 07054C 8006F94C 3C08800E */  lui   $t0, %hi(gCurrentRNGSeed) # $t0, 0x800e
/* 070550 8006F950 8D08D434 */  lw    $t0, %lo(gCurrentRNGSeed)($t0)
/* 070554 8006F954 3C01800E */  lui   $at, %hi(gCurrentRNGSeed) # $at, 0x800e
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
/* 070588 8006F988 AC28D434 */  sw    $t0, %lo(gCurrentRNGSeed)($at)
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
