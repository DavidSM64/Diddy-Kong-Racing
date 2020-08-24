glabel func_8008B358
/* 08BF58 8008B358 27BDFFC0 */  addiu $sp, $sp, -0x40
/* 08BF5C 8008B35C AFB70034 */  sw    $s7, 0x34($sp)
/* 08BF60 8008B360 AFB5002C */  sw    $s5, 0x2c($sp)
/* 08BF64 8008B364 AFB40028 */  sw    $s4, 0x28($sp)
/* 08BF68 8008B368 AFB30024 */  sw    $s3, 0x24($sp)
/* 08BF6C 8008B36C AFB20020 */  sw    $s2, 0x20($sp)
/* 08BF70 8008B370 AFB00018 */  sw    $s0, 0x18($sp)
/* 08BF74 8008B374 AFBE0038 */  sw    $fp, 0x38($sp)
/* 08BF78 8008B378 AFB60030 */  sw    $s6, 0x30($sp)
/* 08BF7C 8008B37C AFB1001C */  sw    $s1, 0x1c($sp)
/* 08BF80 8008B380 3C108012 */  lui   $s0, %hi(players_character_array) # $s0, 0x8012
/* 08BF84 8008B384 3C128012 */  lui   $s2, %hi(D_801263D4) # $s2, 0x8012
/* 08BF88 8008B388 3C138012 */  lui   $s3, %hi(D_801263C0) # $s3, 0x8012
/* 08BF8C 8008B38C 3C14800E */  lui   $s4, %hi(D_800DF4BC) # $s4, 0x800e
/* 08BF90 8008B390 3C158012 */  lui   $s5, %hi(D_801267D8) # $s5, 0x8012
/* 08BF94 8008B394 3C178012 */  lui   $s7, %hi(D_801263CC) # $s7, 0x8012
/* 08BF98 8008B398 AFBF003C */  sw    $ra, 0x3c($sp)
/* 08BF9C 8008B39C 26F763CC */  addiu $s7, %lo(D_801263CC) # addiu $s7, $s7, 0x63cc
/* 08BFA0 8008B3A0 26B567D8 */  addiu $s5, %lo(D_801267D8) # addiu $s5, $s5, 0x67d8
/* 08BFA4 8008B3A4 2694F4BC */  addiu $s4, %lo(D_800DF4BC) # addiu $s4, $s4, -0xb44
/* 08BFA8 8008B3A8 267363C0 */  addiu $s3, %lo(D_801263C0) # addiu $s3, $s3, 0x63c0
/* 08BFAC 8008B3AC 265263D4 */  addiu $s2, %lo(D_801263D4) # addiu $s2, $s2, 0x63d4
/* 08BFB0 8008B3B0 261063E8 */  addiu $s0, %lo(players_character_array) # addiu $s0, $s0, 0x63e8
/* 08BFB4 8008B3B4 00008825 */  move  $s1, $zero
/* 08BFB8 8008B3B8 24160001 */  li    $s6, 1
/* 08BFBC 8008B3BC 241E000E */  li    $fp, 14
.L8008B3C0:
/* 08BFC0 8008B3C0 824E0000 */  lb    $t6, ($s2)
/* 08BFC4 8008B3C4 00117880 */  sll   $t7, $s1, 2
/* 08BFC8 8008B3C8 15C0002F */  bnez  $t6, .L8008B488
/* 08BFCC 8008B3CC 02AFC021 */   addu  $t8, $s5, $t7
/* 08BFD0 8008B3D0 8F190000 */  lw    $t9, ($t8)
/* 08BFD4 8008B3D4 2406FFFF */  li    $a2, -1
/* 08BFD8 8008B3D8 33289000 */  andi  $t0, $t9, 0x9000
/* 08BFDC 8008B3DC 1100002A */  beqz  $t0, .L8008B488
/* 08BFE0 8008B3E0 02113821 */   addu  $a3, $s0, $s1
.L8008B3E4:
/* 08BFE4 8008B3E4 3C098012 */  lui   $t1, %hi(D_801263D4) # $t1, 0x8012
/* 08BFE8 8008B3E8 252963D4 */  addiu $t1, %lo(D_801263D4) # addiu $t1, $t1, 0x63d4
/* 08BFEC 8008B3EC 24C60001 */  addiu $a2, $a2, 1
/* 08BFF0 8008B3F0 02C02025 */  move  $a0, $s6
/* 08BFF4 8008B3F4 00091821 */  addu  $v1, $zero, $t1
/* 08BFF8 8008B3F8 00001025 */  move  $v0, $zero
.L8008B3FC:
/* 08BFFC 8008B3FC 806A0000 */  lb    $t2, ($v1)
/* 08C000 8008B400 02025821 */  addu  $t3, $s0, $v0
/* 08C004 8008B404 11400006 */  beqz  $t2, .L8008B420
/* 08C008 8008B408 00000000 */   nop   
/* 08C00C 8008B40C 816C0000 */  lb    $t4, ($t3)
/* 08C010 8008B410 00000000 */  nop   
/* 08C014 8008B414 14CC0002 */  bne   $a2, $t4, .L8008B420
/* 08C018 8008B418 00000000 */   nop   
/* 08C01C 8008B41C 00002025 */  move  $a0, $zero
.L8008B420:
/* 08C020 8008B420 24420001 */  addiu $v0, $v0, 1
/* 08C024 8008B424 28410004 */  slti  $at, $v0, 4
/* 08C028 8008B428 10200003 */  beqz  $at, .L8008B438
/* 08C02C 8008B42C 24630001 */   addiu $v1, $v1, 1
/* 08C030 8008B430 1480FFF2 */  bnez  $a0, .L8008B3FC
/* 08C034 8008B434 00000000 */   nop   
.L8008B438:
/* 08C038 8008B438 1080FFEA */  beqz  $a0, .L8008B3E4
/* 08C03C 8008B43C 00000000 */   nop   
/* 08C040 8008B440 A0E60000 */  sb    $a2, ($a3)
/* 08C044 8008B444 80F80000 */  lb    $t8, ($a3)
/* 08C048 8008B448 8E8D0000 */  lw    $t5, ($s4)
/* 08C04C 8008B44C 031E0019 */  multu $t8, $fp
/* 08C050 8008B450 8EEF0000 */  lw    $t7, ($s7)
/* 08C054 8008B454 25AE0001 */  addiu $t6, $t5, 1
/* 08C058 8008B458 A2560000 */  sb    $s6, ($s2)
/* 08C05C 8008B45C AE8E0000 */  sw    $t6, ($s4)
/* 08C060 8008B460 240A0014 */  li    $t2, 20
/* 08C064 8008B464 240400EF */  li    $a0, 239
/* 08C068 8008B468 00002825 */  move  $a1, $zero
/* 08C06C 8008B46C 0000C812 */  mflo  $t9
/* 08C070 8008B470 01F94021 */  addu  $t0, $t7, $t9
/* 08C074 8008B474 8509000C */  lh    $t1, 0xc($t0)
/* 08C078 8008B478 A6600002 */  sh    $zero, 2($s3)
/* 08C07C 8008B47C A26A0001 */  sb    $t2, 1($s3)
/* 08C080 8008B480 0C000741 */  jal   func_80001D04
/* 08C084 8008B484 A2690000 */   sb    $t1, ($s3)
.L8008B488:
/* 08C088 8008B488 26310001 */  addiu $s1, $s1, 1
/* 08C08C 8008B48C 24010004 */  li    $at, 4
/* 08C090 8008B490 1621FFCB */  bne   $s1, $at, .L8008B3C0
/* 08C094 8008B494 26520001 */   addiu $s2, $s2, 1
/* 08C098 8008B498 8FBF003C */  lw    $ra, 0x3c($sp)
/* 08C09C 8008B49C 8FB00018 */  lw    $s0, 0x18($sp)
/* 08C0A0 8008B4A0 8FB1001C */  lw    $s1, 0x1c($sp)
/* 08C0A4 8008B4A4 8FB20020 */  lw    $s2, 0x20($sp)
/* 08C0A8 8008B4A8 8FB30024 */  lw    $s3, 0x24($sp)
/* 08C0AC 8008B4AC 8FB40028 */  lw    $s4, 0x28($sp)
/* 08C0B0 8008B4B0 8FB5002C */  lw    $s5, 0x2c($sp)
/* 08C0B4 8008B4B4 8FB60030 */  lw    $s6, 0x30($sp)
/* 08C0B8 8008B4B8 8FB70034 */  lw    $s7, 0x34($sp)
/* 08C0BC 8008B4BC 8FBE0038 */  lw    $fp, 0x38($sp)
/* 08C0C0 8008B4C0 03E00008 */  jr    $ra
/* 08C0C4 8008B4C4 27BD0040 */   addiu $sp, $sp, 0x40

