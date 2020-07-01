glabel func_8009EA78
/* 09F678 8009EA78 3C028012 */  lui   $v0, %hi(D_80126448) # $v0, 0x8012
/* 09F67C 8009EA7C 24426448 */  addiu $v0, %lo(D_80126448) # addiu $v0, $v0, 0x6448
/* 09F680 8009EA80 8C4E0000 */  lw    $t6, ($v0)
/* 09F684 8009EA84 8C4F0004 */  lw    $t7, 4($v0)
/* 09F688 8009EA88 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 09F68C 8009EA8C AFBF0014 */  sw    $ra, 0x14($sp)
/* 09F690 8009EA90 01C44025 */  or    $t0, $t6, $a0
/* 09F694 8009EA94 01E54825 */  or    $t1, $t7, $a1
/* 09F698 8009EA98 AFA40018 */  sw    $a0, 0x18($sp)
/* 09F69C 8009EA9C AFA5001C */  sw    $a1, 0x1c($sp)
/* 09F6A0 8009EAA0 AC490004 */  sw    $t1, 4($v0)
/* 09F6A4 8009EAA4 0C01BB38 */  jal   func_8006ECE0
/* 09F6A8 8009EAA8 AC480000 */   sw    $t0, ($v0)
/* 09F6AC 8009EAAC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 09F6B0 8009EAB0 27BD0018 */  addiu $sp, $sp, 0x18
/* 09F6B4 8009EAB4 03E00008 */  jr    $ra
/* 09F6B8 8009EAB8 24020001 */   li    $v0, 1

