glabel func_8007A080
/* 07AC80 8007A080 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 07AC84 8007A084 AFBF0014 */  sw    $ra, 0x14($sp)
/* 07AC88 8007A088 8C820274 */  lw    $v0, 0x274($a0)
/* 07AC8C 8007A08C 24010001 */  li    $at, 1
/* 07AC90 8007A090 8C4E0010 */  lw    $t6, 0x10($v0)
/* 07AC94 8007A094 00000000 */  nop   
/* 07AC98 8007A098 15C1000B */  bne   $t6, $at, .L8007A0C8
/* 07AC9C 8007A09C 8FBF0014 */   lw    $ra, 0x14($sp)
/* 07ACA0 8007A0A0 8C4F0004 */  lw    $t7, 4($v0)
/* 07ACA4 8007A0A4 00000000 */  nop   
/* 07ACA8 8007A0A8 35F80010 */  ori   $t8, $t7, 0x10
/* 07ACAC 8007A0AC 0C03486C */  jal   osGetTime
/* 07ACB0 8007A0B0 AC580004 */   sw    $t8, 4($v0)
/* 07ACB4 8007A0B4 3C018012 */  lui   $at, %hi(D_8012611C) # $at, 0x8012
/* 07ACB8 8007A0B8 AC226118 */  sw    $v0, %lo(D_80126118)($at)
/* 07ACBC 8007A0BC 0C034890 */  jal   osSpTaskYield
/* 07ACC0 8007A0C0 AC23611C */   sw    $v1, %lo(D_8012611C)($at)
/* 07ACC4 8007A0C4 8FBF0014 */  lw    $ra, 0x14($sp)
.L8007A0C8:
/* 07ACC8 8007A0C8 27BD0018 */  addiu $sp, $sp, 0x18
/* 07ACCC 8007A0CC 03E00008 */  jr    $ra
/* 07ACD0 8007A0D0 00000000 */   nop   

