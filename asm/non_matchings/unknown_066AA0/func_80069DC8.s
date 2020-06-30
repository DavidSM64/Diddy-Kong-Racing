glabel func_80069DC8
/* 06A9C8 80069DC8 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 06A9CC 80069DCC AFA60040 */  sw    $a2, 0x40($sp)
/* 06A9D0 80069DD0 AFBF0024 */  sw    $ra, 0x24($sp)
/* 06A9D4 80069DD4 8FA70040 */  lw    $a3, 0x40($sp)
/* 06A9D8 80069DD8 44067000 */  mfc1  $a2, $f14
/* 06A9DC 80069DDC 27AE0034 */  addiu $t6, $sp, 0x34
/* 06A9E0 80069DE0 27AF0030 */  addiu $t7, $sp, 0x30
/* 06A9E4 80069DE4 27B8002C */  addiu $t8, $sp, 0x2c
/* 06A9E8 80069DE8 3C048012 */  lui   $a0, %hi(D_80120F60) # $a0, 0x8012
/* 06A9EC 80069DEC 44056000 */  mfc1  $a1, $f12
/* 06A9F0 80069DF0 24840F60 */  addiu $a0, %lo(D_80120F60) # addiu $a0, $a0, 0xf60
/* 06A9F4 80069DF4 AFB80018 */  sw    $t8, 0x18($sp)
/* 06A9F8 80069DF8 AFAF0014 */  sw    $t7, 0x14($sp)
/* 06A9FC 80069DFC 0C01BD93 */  jal   func_8006F64C
/* 06AA00 80069E00 AFAE0010 */   sw    $t6, 0x10($sp)
/* 06AA04 80069E04 8FBF0024 */  lw    $ra, 0x24($sp)
/* 06AA08 80069E08 C7A0002C */  lwc1  $f0, 0x2c($sp)
/* 06AA0C 80069E0C 03E00008 */  jr    $ra
/* 06AA10 80069E10 27BD0038 */   addiu $sp, $sp, 0x38

