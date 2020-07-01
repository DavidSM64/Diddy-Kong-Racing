glabel func_8008E4B0
/* 08F0B0 8008E4B0 3C028012 */  lui   $v0, %hi(D_80126550) # $v0, 0x8012
/* 08F0B4 8008E4B4 24426550 */  addiu $v0, %lo(D_80126550) # addiu $v0, $v0, 0x6550
/* 08F0B8 8008E4B8 8C4E00F4 */  lw    $t6, 0xf4($v0)
/* 08F0BC 8008E4BC 3C01800E */  lui   $at, %hi(D_800E041C) # $at, 0x800e
/* 08F0C0 8008E4C0 AC2E041C */  sw    $t6, %lo(D_800E041C)($at)
/* 08F0C4 8008E4C4 8C4F00F0 */  lw    $t7, 0xf0($v0)
/* 08F0C8 8008E4C8 3C01800E */  lui   $at, %hi(D_800E042C) # $at, 0x800e
/* 08F0CC 8008E4CC AC2F042C */  sw    $t7, %lo(D_800E042C)($at)
/* 08F0D0 8008E4D0 8C5800FC */  lw    $t8, 0xfc($v0)
/* 08F0D4 8008E4D4 3C01800E */  lui   $at, %hi(D_800E043C) # $at, 0x800e
/* 08F0D8 8008E4D8 AC38043C */  sw    $t8, %lo(D_800E043C)($at)
/* 08F0DC 8008E4DC 8C5900F8 */  lw    $t9, 0xf8($v0)
/* 08F0E0 8008E4E0 3C01800E */  lui   $at, 0x800e
/* 08F0E4 8008E4E4 03E00008 */  jr    $ra
/* 08F0E8 8008E4E8 AC39044C */   sw    $t9, 0x44c($at)

