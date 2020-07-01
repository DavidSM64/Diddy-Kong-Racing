glabel func_8009C2E0
/* 09CEE0 8009C2E0 3C02800E */  lui   $v0, %hi(gActiveMagicCodes) # $v0, 0x800e
/* 09CEE4 8009C2E4 3C03800E */  lui   $v1, %hi(D_800DFD9C) # $v1, 0x800e
/* 09CEE8 8009C2E8 2463FD9C */  addiu $v1, %lo(D_800DFD9C) # addiu $v1, $v1, -0x264
/* 09CEEC 8009C2EC 2442FD98 */  addiu $v0, %lo(gActiveMagicCodes) # addiu $v0, $v0, -0x268
/* 09CEF0 8009C2F0 8C4E0000 */  lw    $t6, ($v0)
/* 09CEF4 8009C2F4 8C780000 */  lw    $t8, ($v1)
/* 09CEF8 8009C2F8 01C47825 */  or    $t7, $t6, $a0
/* 09CEFC 8009C2FC 0304C825 */  or    $t9, $t8, $a0
/* 09CF00 8009C300 AC4F0000 */  sw    $t7, ($v0)
/* 09CF04 8009C304 03E00008 */  jr    $ra
/* 09CF08 8009C308 AC790000 */   sw    $t9, ($v1)

