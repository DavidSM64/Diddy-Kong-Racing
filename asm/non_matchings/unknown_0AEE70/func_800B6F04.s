glabel func_800B6F04
/* 0B7B04 800B6F04 3C0E8012 */  lui   $t6, %hi(D_80127CBC) # $t6, 0x8012
/* 0B7B08 800B6F08 8DCE7CBC */  lw    $t6, %lo(D_80127CBC)($t6)
/* 0B7B0C 800B6F0C 3C028012 */  lui   $v0, %hi(D_80127CAE) # $v0, 0x8012
/* 0B7B10 800B6F10 3C018012 */  lui   $at, %hi(D_80127CAC) # $at, 0x8012
/* 0B7B14 800B6F14 24427CAE */  addiu $v0, %lo(D_80127CAE) # addiu $v0, $v0, 0x7cae
/* 0B7B18 800B6F18 A42E7CAC */  sh    $t6, %lo(D_80127CAC)($at)
/* 0B7B1C 800B6F1C 944F0000 */  lhu   $t7, ($v0)
/* 0B7B20 800B6F20 00000000 */  nop   
/* 0B7B24 800B6F24 25F8000B */  addiu $t8, $t7, 0xb
/* 0B7B28 800B6F28 03E00008 */  jr    $ra
/* 0B7B2C 800B6F2C A4580000 */   sh    $t8, ($v0)

/* 0B7B30 800B6F30 AFA40000 */  sw    $a0, ($sp)
/* 0B7B34 800B6F34 AFA50004 */  sw    $a1, 4($sp)
/* 0B7B38 800B6F38 03E00008 */  jr    $ra
/* 0B7B3C 800B6F3C AFA60008 */   sw    $a2, 8($sp)

