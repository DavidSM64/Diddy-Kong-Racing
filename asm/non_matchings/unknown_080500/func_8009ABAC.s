glabel func_8009ABAC
/* 09B7AC 8009ABAC 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 09B7B0 8009ABB0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 09B7B4 8009ABB4 3C04800E */  lui   $a0, %hi(D_800E1708) # $a0, 0x800e
/* 09B7B8 8009ABB8 0C02712A */  jal   func_8009C4A8
/* 09B7BC 8009ABBC 24841708 */   addiu $a0, %lo(D_800E1708) # addiu $a0, $a0, 0x1708
/* 09B7C0 8009ABC0 0C03108B */  jal   func_800C422C
/* 09B7C4 8009ABC4 24040002 */   li    $a0, 2
/* 09B7C8 8009ABC8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 09B7CC 8009ABCC 27BD0018 */  addiu $sp, $sp, 0x18
/* 09B7D0 8009ABD0 03E00008 */  jr    $ra
/* 09B7D4 8009ABD4 00000000 */   nop   

