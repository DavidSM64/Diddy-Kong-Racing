glabel func_800976CC
/* 0982CC 800976CC 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0982D0 800976D0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0982D4 800976D4 3C04800E */  lui   $a0, %hi(D_800E0A24) # $a0, 0x800e
/* 0982D8 800976D8 0C02712A */  jal   func_8009C4A8
/* 0982DC 800976DC 24840A24 */   addiu $a0, %lo(D_800E0A24) # addiu $a0, $a0, 0xa24
/* 0982E0 800976E0 0C03108B */  jal   func_800C422C
/* 0982E4 800976E4 24040002 */   li    $a0, 2
/* 0982E8 800976E8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0982EC 800976EC 27BD0018 */  addiu $sp, $sp, 0x18
/* 0982F0 800976F0 03E00008 */  jr    $ra
/* 0982F4 800976F4 00000000 */   nop   

