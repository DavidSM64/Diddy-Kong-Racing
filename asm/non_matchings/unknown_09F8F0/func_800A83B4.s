glabel func_800A83B4
/* 0A8FB4 800A83B4 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0A8FB8 800A83B8 AFBF0024 */  sw    $ra, 0x24($sp)
/* 0A8FBC 800A83BC AFB00020 */  sw    $s0, 0x20($sp)
/* 0A8FC0 800A83C0 8C8E0038 */  lw    $t6, 0x38($a0)
/* 0A8FC4 800A83C4 3C018012 */  lui   $at, %hi(D_80126D54) # $at, 0x8012
/* 0A8FC8 800A83C8 000EC402 */  srl   $t8, $t6, 0x10
/* 0A8FCC 800A83CC A0386D54 */  sb    $t8, %lo(D_80126D54)($at)
/* 0A8FD0 800A83D0 8C990038 */  lw    $t9, 0x38($a0)
/* 0A8FD4 800A83D4 3C018012 */  lui   $at, %hi(D_80126D55) # $at, 0x8012
/* 0A8FD8 800A83D8 00194A02 */  srl   $t1, $t9, 8
/* 0A8FDC 800A83DC A0296D55 */  sb    $t1, %lo(D_80126D55)($at)
/* 0A8FE0 800A83E0 8C8B0038 */  lw    $t3, 0x38($a0)
/* 0A8FE4 800A83E4 3C018012 */  lui   $at, %hi(D_80126D56) # $at, 0x8012
/* 0A8FE8 800A83E8 00808025 */  move  $s0, $a0
/* 0A8FEC 800A83EC A02B6D56 */  sb    $t3, %lo(D_80126D56)($at)
/* 0A8FF0 800A83F0 8C840020 */  lw    $a0, 0x20($a0)
/* 0A8FF4 800A83F4 27A7002C */  addiu $a3, $sp, 0x2c
/* 0A8FF8 800A83F8 3C058012 */  lui   $a1, %hi(D_80126D1C) # $a1, 0x8012
/* 0A8FFC 800A83FC 3C068012 */  lui   $a2, %hi(D_80126D20) # $a2, 0x8012
/* 0A9000 800A8400 24C66D20 */  addiu $a2, %lo(D_80126D20) # addiu $a2, $a2, 0x6d20
/* 0A9004 800A8404 24A56D1C */  addiu $a1, %lo(D_80126D1C) # addiu $a1, $a1, 0x6d1c
/* 0A9008 800A8408 AFA70010 */  sw    $a3, 0x10($sp)
/* 0A900C 800A840C 0C01F238 */  jal   func_8007C8E0
/* 0A9010 800A8410 AFA70014 */   sw    $a3, 0x14($sp)
/* 0A9014 800A8414 8E040020 */  lw    $a0, 0x20($s0)
/* 0A9018 800A8418 3C068012 */  lui   $a2, %hi(D_80126D14) # $a2, 0x8012
/* 0A901C 800A841C 3C078012 */  lui   $a3, %hi(D_80126D18) # $a3, 0x8012
/* 0A9020 800A8420 27AC002C */  addiu $t4, $sp, 0x2c
/* 0A9024 800A8424 AFAC0010 */  sw    $t4, 0x10($sp)
/* 0A9028 800A8428 24E76D18 */  addiu $a3, %lo(D_80126D18) # addiu $a3, $a3, 0x6d18
/* 0A902C 800A842C 24C66D14 */  addiu $a2, %lo(D_80126D14) # addiu $a2, $a2, 0x6d14
/* 0A9030 800A8430 0C01F29A */  jal   func_8007CA68
/* 0A9034 800A8434 00002825 */   move  $a1, $zero
/* 0A9038 800A8438 8E040020 */  lw    $a0, 0x20($s0)
/* 0A903C 800A843C 0C01F04B */  jal   func_8007C12C
/* 0A9040 800A8440 24050001 */   li    $a1, 1
/* 0A9044 800A8444 AE020020 */  sw    $v0, 0x20($s0)
/* 0A9048 800A8448 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0A904C 800A844C 8FB00020 */  lw    $s0, 0x20($sp)
/* 0A9050 800A8450 03E00008 */  jr    $ra
/* 0A9054 800A8454 27BD0030 */   addiu $sp, $sp, 0x30

