glabel func_8009EABC
/* 09F6BC 8009EABC 3C028012 */  lui   $v0, %hi(D_80126448) # $v0, 0x8012
/* 09F6C0 8009EAC0 24426448 */  addiu $v0, %lo(D_80126448) # addiu $v0, $v0, 0x6448
/* 09F6C4 8009EAC4 8C4E0000 */  lw    $t6, ($v0)
/* 09F6C8 8009EAC8 8C4F0004 */  lw    $t7, 4($v0)
/* 09F6CC 8009EACC 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 09F6D0 8009EAD0 00804027 */  not   $t0, $a0
/* 09F6D4 8009EAD4 00A04827 */  not   $t1, $a1
/* 09F6D8 8009EAD8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 09F6DC 8009EADC 01C85024 */  and   $t2, $t6, $t0
/* 09F6E0 8009EAE0 01E95824 */  and   $t3, $t7, $t1
/* 09F6E4 8009EAE4 AFA40018 */  sw    $a0, 0x18($sp)
/* 09F6E8 8009EAE8 AFA5001C */  sw    $a1, 0x1c($sp)
/* 09F6EC 8009EAEC AC4B0004 */  sw    $t3, 4($v0)
/* 09F6F0 8009EAF0 0C01BB38 */  jal   func_8006ECE0
/* 09F6F4 8009EAF4 AC4A0000 */   sw    $t2, ($v0)
/* 09F6F8 8009EAF8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 09F6FC 8009EAFC 27BD0018 */  addiu $sp, $sp, 0x18
/* 09F700 8009EB00 03E00008 */  jr    $ra
/* 09F704 8009EB04 24020001 */   li    $v0, 1

