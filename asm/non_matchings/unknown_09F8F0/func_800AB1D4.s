glabel func_800AB1D4
/* 0ABDD4 800AB1D4 240F0001 */  li    $t7, 1
/* 0ABDD8 800AB1D8 01E4C023 */  subu  $t8, $t7, $a0
/* 0ABDDC 800AB1DC 3C018012 */  lui   $at, %hi(D_80126CD2) # $at, 0x8012
/* 0ABDE0 800AB1E0 AFA40000 */  sw    $a0, ($sp)
/* 0ABDE4 800AB1E4 03E00008 */  jr    $ra
/* 0ABDE8 800AB1E8 A0386CD2 */   sb    $t8, %lo(D_80126CD2)($at)

/* 0ABDEC 800AB1EC 00000000 */  nop   
