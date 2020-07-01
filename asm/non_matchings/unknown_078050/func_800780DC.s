glabel func_800780DC
/* 078CDC 800780DC 8C830000 */  lw    $v1, ($a0)
/* 078CE0 800780E0 3C18800E */  lui   $t8, %hi(D_800DE4E0) # $t8, 0x800e
/* 078CE4 800780E4 246E0008 */  addiu $t6, $v1, 8
/* 078CE8 800780E8 AC8E0000 */  sw    $t6, ($a0)
/* 078CEC 800780EC 2718E4E0 */  addiu $t8, %lo(D_800DE4E0) # addiu $t8, $t8, -0x1b20
/* 078CF0 800780F0 3C0F0600 */  lui   $t7, 0x600
/* 078CF4 800780F4 AC6F0000 */  sw    $t7, ($v1)
/* 078CF8 800780F8 03E00008 */  jr    $ra
/* 078CFC 800780FC AC780004 */   sw    $t8, 4($v1)

