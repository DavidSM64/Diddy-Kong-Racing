glabel func_800B263C
/* 0B323C 800B263C 8C820070 */  lw    $v0, 0x70($a0)
/* 0B3240 800B2640 00000000 */  nop   
/* 0B3244 800B2644 10400024 */  beqz  $v0, .L800B26D8
/* 0B3248 800B2648 00000000 */   nop   
/* 0B324C 800B264C 90430006 */  lbu   $v1, 6($v0)
/* 0B3250 800B2650 00000000 */  nop   
/* 0B3254 800B2654 10600020 */  beqz  $v1, .L800B26D8
/* 0B3258 800B2658 00000000 */   nop   
/* 0B325C 800B265C 908F0074 */  lbu   $t7, 0x74($a0)
/* 0B3260 800B2660 8C4E000C */  lw    $t6, 0xc($v0)
/* 0B3264 800B2664 000FC080 */  sll   $t8, $t7, 2
/* 0B3268 800B2668 01D8C821 */  addu  $t9, $t6, $t8
/* 0B326C 800B266C 8F280000 */  lw    $t0, ($t9)
/* 0B3270 800B2670 2469FFFF */  addiu $t1, $v1, -1
/* 0B3274 800B2674 14880018 */  bne   $a0, $t0, .L800B26D8
/* 0B3278 800B2678 00000000 */   nop   
/* 0B327C 800B267C A0490006 */  sb    $t1, 6($v0)
/* 0B3280 800B2680 90850074 */  lbu   $a1, 0x74($a0)
/* 0B3284 800B2684 312A00FF */  andi  $t2, $t1, 0xff
/* 0B3288 800B2688 00AA082A */  slt   $at, $a1, $t2
/* 0B328C 800B268C 10200012 */  beqz  $at, .L800B26D8
/* 0B3290 800B2690 00051880 */   sll   $v1, $a1, 2
.L800B2694:
/* 0B3294 800B2694 8C4B000C */  lw    $t3, 0xc($v0)
/* 0B3298 800B2698 00000000 */  nop   
/* 0B329C 800B269C 01633021 */  addu  $a2, $t3, $v1
/* 0B32A0 800B26A0 8CCC0004 */  lw    $t4, 4($a2)
/* 0B32A4 800B26A4 00000000 */  nop   
/* 0B32A8 800B26A8 ACCC0000 */  sw    $t4, ($a2)
/* 0B32AC 800B26AC 8C4D000C */  lw    $t5, 0xc($v0)
/* 0B32B0 800B26B0 00000000 */  nop   
/* 0B32B4 800B26B4 01A37821 */  addu  $t7, $t5, $v1
/* 0B32B8 800B26B8 8DE40000 */  lw    $a0, ($t7)
/* 0B32BC 800B26BC 24630004 */  addiu $v1, $v1, 4
/* 0B32C0 800B26C0 A0850074 */  sb    $a1, 0x74($a0)
/* 0B32C4 800B26C4 904E0006 */  lbu   $t6, 6($v0)
/* 0B32C8 800B26C8 24A50001 */  addiu $a1, $a1, 1
/* 0B32CC 800B26CC 00AE082A */  slt   $at, $a1, $t6
/* 0B32D0 800B26D0 1420FFF0 */  bnez  $at, .L800B2694
/* 0B32D4 800B26D4 00000000 */   nop   
.L800B26D8:
/* 0B32D8 800B26D8 03E00008 */  jr    $ra
/* 0B32DC 800B26DC 00000000 */   nop   

