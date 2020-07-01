glabel func_800403A8
/* 040FA8 800403A8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 040FAC 800403AC AFBF0014 */  sw    $ra, 0x14($sp)
/* 040FB0 800403B0 AFA40018 */  sw    $a0, 0x18($sp)
/* 040FB4 800403B4 0C00C72B */  jal   func_80031CAC
/* 040FB8 800403B8 AFA60020 */   sw    $a2, 0x20($sp)
/* 040FBC 800403BC 8FAE0018 */  lw    $t6, 0x18($sp)
/* 040FC0 800403C0 00000000 */  nop   
/* 040FC4 800403C4 ADC20064 */  sw    $v0, 0x64($t6)
/* 040FC8 800403C8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 040FCC 800403CC 27BD0018 */  addiu $sp, $sp, 0x18
/* 040FD0 800403D0 03E00008 */  jr    $ra
/* 040FD4 800403D4 00000000 */   nop   

