glabel func_8007BF1C
/* 07CB1C 8007BF1C 3C01800E */  lui   $at, %hi(D_800DE7C4) # $at, 0x800e
/* 07CB20 8007BF20 AC24E7C4 */  sw    $a0, %lo(D_800DE7C4)($at)
/* 07CB24 8007BF24 3C018012 */  lui   $at, 0x8012
/* 07CB28 8007BF28 240E0001 */  li    $t6, 1
/* 07CB2C 8007BF2C 03E00008 */  jr    $ra
/* 07CB30 8007BF30 A42E6382 */   sh    $t6, 0x6382($at)

