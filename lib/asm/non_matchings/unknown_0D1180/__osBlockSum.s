glabel __osBlockSum
/* 0D1988 800D0D88 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 0D198C 800D0D8C AFA40040 */  sw    $a0, 0x40($sp)
/* 0D1990 800D0D90 AFA7004C */  sw    $a3, 0x4c($sp)
/* 0D1994 800D0D94 93AE004F */  lbu   $t6, 0x4f($sp)
/* 0D1998 800D0D98 8FAF0040 */  lw    $t7, 0x40($sp)
/* 0D199C 800D0D9C AFBF0014 */  sw    $ra, 0x14($sp)
/* 0D19A0 800D0DA0 AFA50044 */  sw    $a1, 0x44($sp)
/* 0D19A4 800D0DA4 AFA60048 */  sw    $a2, 0x48($sp)
/* 0D19A8 800D0DA8 AFA00038 */  sw    $zero, 0x38($sp)
/* 0D19AC 800D0DAC A1EE0065 */  sb    $t6, 0x65($t7)
/* 0D19B0 800D0DB0 0C0357F7 */  jal   __osPfsSelectBank
/* 0D19B4 800D0DB4 8FA40040 */   lw    $a0, 0x40($sp)
/* 0D19B8 800D0DB8 AFA20038 */  sw    $v0, 0x38($sp)
/* 0D19BC 800D0DBC 8FB80038 */  lw    $t8, 0x38($sp)
/* 0D19C0 800D0DC0 13000003 */  beqz  $t8, .L800D0DD0
/* 0D19C4 800D0DC4 00000000 */   nop   
/* 0D19C8 800D0DC8 10000027 */  b     .L800D0E68
/* 0D19CC 800D0DCC 03001025 */   move  $v0, $t8
.L800D0DD0:
/* 0D19D0 800D0DD0 AFA0003C */  sw    $zero, 0x3c($sp)
.L800D0DD4:
/* 0D19D4 800D0DD4 93A80047 */  lbu   $t0, 0x47($sp)
/* 0D19D8 800D0DD8 8FB90040 */  lw    $t9, 0x40($sp)
/* 0D19DC 800D0DDC 8FAA003C */  lw    $t2, 0x3c($sp)
/* 0D19E0 800D0DE0 000848C0 */  sll   $t1, $t0, 3
/* 0D19E4 800D0DE4 27A70018 */  addiu $a3, $sp, 0x18
/* 0D19E8 800D0DE8 8F240004 */  lw    $a0, 4($t9)
/* 0D19EC 800D0DEC 8F250008 */  lw    $a1, 8($t9)
/* 0D19F0 800D0DF0 0C033728 */  jal   __osContRamRead
/* 0D19F4 800D0DF4 012A3021 */   addu  $a2, $t1, $t2
/* 0D19F8 800D0DF8 AFA20038 */  sw    $v0, 0x38($sp)
/* 0D19FC 800D0DFC 8FAB0038 */  lw    $t3, 0x38($sp)
/* 0D1A00 800D0E00 11600007 */  beqz  $t3, .L800D0E20
/* 0D1A04 800D0E04 00000000 */   nop   
/* 0D1A08 800D0E08 8FAC0040 */  lw    $t4, 0x40($sp)
/* 0D1A0C 800D0E0C A1800065 */  sb    $zero, 0x65($t4)
/* 0D1A10 800D0E10 0C0357F7 */  jal   __osPfsSelectBank
/* 0D1A14 800D0E14 8FA40040 */   lw    $a0, 0x40($sp)
/* 0D1A18 800D0E18 10000013 */  b     .L800D0E68
/* 0D1A1C 800D0E1C 8FA20038 */   lw    $v0, 0x38($sp)
.L800D0E20:
/* 0D1A20 800D0E20 27A40018 */  addiu $a0, $sp, 0x18
/* 0D1A24 800D0E24 0C0354BC */  jal   __osSumcalc
/* 0D1A28 800D0E28 24050020 */   li    $a1, 32
/* 0D1A2C 800D0E2C 8FAD0048 */  lw    $t5, 0x48($sp)
/* 0D1A30 800D0E30 95AE0000 */  lhu   $t6, ($t5)
/* 0D1A34 800D0E34 004E7821 */  addu  $t7, $v0, $t6
/* 0D1A38 800D0E38 A5AF0000 */  sh    $t7, ($t5)
/* 0D1A3C 800D0E3C 8FB8003C */  lw    $t8, 0x3c($sp)
/* 0D1A40 800D0E40 27190001 */  addiu $t9, $t8, 1
/* 0D1A44 800D0E44 2B210008 */  slti  $at, $t9, 8
/* 0D1A48 800D0E48 1420FFE2 */  bnez  $at, .L800D0DD4
/* 0D1A4C 800D0E4C AFB9003C */   sw    $t9, 0x3c($sp)
/* 0D1A50 800D0E50 8FA80040 */  lw    $t0, 0x40($sp)
/* 0D1A54 800D0E54 A1000065 */  sb    $zero, 0x65($t0)
/* 0D1A58 800D0E58 0C0357F7 */  jal   __osPfsSelectBank
/* 0D1A5C 800D0E5C 8FA40040 */   lw    $a0, 0x40($sp)
/* 0D1A60 800D0E60 AFA20038 */  sw    $v0, 0x38($sp)
/* 0D1A64 800D0E64 8FA20038 */  lw    $v0, 0x38($sp)
.L800D0E68:
/* 0D1A68 800D0E68 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0D1A6C 800D0E6C 27BD0040 */  addiu $sp, $sp, 0x40
/* 0D1A70 800D0E70 03E00008 */  jr    $ra
/* 0D1A74 800D0E74 00000000 */   nop   

/* 0D1A78 800D0E78 00000000 */  nop   
/* 0D1A7C 800D0E7C 00000000 */  nop   

