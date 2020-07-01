glabel func_8007A4C0
/* 07B0C0 8007A4C0 3C018012 */  lui   $at, 0x8012
/* 07B0C4 8007A4C4 03E00008 */  jr    $ra
/* 07B0C8 8007A4C8 AC2462CC */   sw    $a0, 0x62cc($at)

/* 07B0CC 8007A4CC 3C028012 */  lui   $v0, %hi(D_801262CC) # $v0, 0x8012
/* 07B0D0 8007A4D0 8C4262CC */  lw    $v0, %lo(D_801262CC)($v0)
/* 07B0D4 8007A4D4 03E00008 */  jr    $ra
/* 07B0D8 8007A4D8 00000000 */   nop   

/* 07B0DC 8007A4DC 3C0E8012 */  lui   $t6, %hi(D_801262CC) # $t6, 0x8012
/* 07B0E0 8007A4E0 8DCE62CC */  lw    $t6, %lo(D_801262CC)($t6)
/* 07B0E4 8007A4E4 3C19800E */  lui   $t9, %hi(D_800DE77C) # $t9, 0x800e
/* 07B0E8 8007A4E8 31CF0007 */  andi  $t7, $t6, 7
/* 07B0EC 8007A4EC 000FC0C0 */  sll   $t8, $t7, 3
/* 07B0F0 8007A4F0 2739E77C */  addiu $t9, %lo(D_800DE77C) # addiu $t9, $t9, -0x1884
/* 07B0F4 8007A4F4 03191821 */  addu  $v1, $t8, $t9
/* 07B0F8 8007A4F8 8C680000 */  lw    $t0, ($v1)
/* 07B0FC 8007A4FC 00041080 */  sll   $v0, $a0, 2
/* 07B100 8007A500 3C018012 */  lui   $at, 0x8012
/* 07B104 8007A504 00220821 */  addu  $at, $at, $v0
/* 07B108 8007A508 AC2862B0 */  sw    $t0, 0x62b0($at)
/* 07B10C 8007A50C 8C690004 */  lw    $t1, 4($v1)
/* 07B110 8007A510 3C018012 */  lui   $at, 0x8012
/* 07B114 8007A514 00220821 */  addu  $at, $at, $v0
/* 07B118 8007A518 03E00008 */  jr    $ra
/* 07B11C 8007A51C AC2962B8 */   sw    $t1, 0x62b8($at)

