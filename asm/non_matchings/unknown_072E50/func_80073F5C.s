glabel func_80073F5C
/* 074B5C 80073F5C 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 074B60 80073F60 AFBF001C */  sw    $ra, 0x1c($sp)
/* 074B64 80073F64 AFA40038 */  sw    $a0, 0x38($sp)
/* 074B68 80073F68 0C01CF13 */  jal   func_80073C4C
/* 074B6C 80073F6C AFA5003C */   sw    $a1, 0x3c($sp)
/* 074B70 80073F70 AFA20024 */  sw    $v0, 0x24($sp)
/* 074B74 80073F74 00402025 */  move  $a0, $v0
/* 074B78 80073F78 0C01C327 */  jal   allocate_from_main_pool_safe
/* 074B7C 80073F7C 2405FFFF */   li    $a1, -1
/* 074B80 80073F80 3C0E4741 */  lui   $t6, (0x47414D44 >> 16) # lui $t6, 0x4741
/* 074B84 80073F84 AFA2002C */  sw    $v0, 0x2c($sp)
/* 074B88 80073F88 35CE4D44 */  ori   $t6, (0x47414D44 & 0xFFFF) # ori $t6, $t6, 0x4d44
/* 074B8C 80073F8C AC4E0000 */  sw    $t6, ($v0)
/* 074B90 80073F90 8FA4003C */  lw    $a0, 0x3c($sp)
/* 074B94 80073F94 0C01CCBA */  jal   func_800732E8
/* 074B98 80073F98 24450004 */   addiu $a1, $v0, 4
/* 074B9C 80073F9C 8FA40038 */  lw    $a0, 0x38($sp)
/* 074BA0 80073FA0 24050003 */  li    $a1, 3
/* 074BA4 80073FA4 0C01CF17 */  jal   func_80073C5C
/* 074BA8 80073FA8 27A60030 */   addiu $a2, $sp, 0x30
/* 074BAC 80073FAC 1440000C */  bnez  $v0, .L80073FE0
/* 074BB0 80073FB0 00401825 */   move  $v1, $v0
/* 074BB4 80073FB4 8FAF002C */  lw    $t7, 0x2c($sp)
/* 074BB8 80073FB8 8FB80024 */  lw    $t8, 0x24($sp)
/* 074BBC 80073FBC 8FA40038 */  lw    $a0, 0x38($sp)
/* 074BC0 80073FC0 3C06800E */  lui   $a2, %hi(D_800E7680) # $a2, 0x800e
/* 074BC4 80073FC4 24C67680 */  addiu $a2, %lo(D_800E7680) # addiu $a2, $a2, 0x7680
/* 074BC8 80073FC8 2405FFFF */  li    $a1, -1
/* 074BCC 80073FCC 27A70030 */  addiu $a3, $sp, 0x30
/* 074BD0 80073FD0 AFAF0010 */  sw    $t7, 0x10($sp)
/* 074BD4 80073FD4 0C01D9B5 */  jal   func_800766D4
/* 074BD8 80073FD8 AFB80014 */   sw    $t8, 0x14($sp)
/* 074BDC 80073FDC 00401825 */  move  $v1, $v0
.L80073FE0:
/* 074BE0 80073FE0 8FA4002C */  lw    $a0, 0x2c($sp)
/* 074BE4 80073FE4 0C01C450 */  jal   func_80071140
/* 074BE8 80073FE8 AFA30028 */   sw    $v1, 0x28($sp)
/* 074BEC 80073FEC 8FA30028 */  lw    $v1, 0x28($sp)
/* 074BF0 80073FF0 8FBF001C */  lw    $ra, 0x1c($sp)
/* 074BF4 80073FF4 10600006 */  beqz  $v1, .L80074010
/* 074BF8 80073FF8 00601025 */   move  $v0, $v1
/* 074BFC 80073FFC 8FB90038 */  lw    $t9, 0x38($sp)
/* 074C00 80074000 00000000 */  nop   
/* 074C04 80074004 00194780 */  sll   $t0, $t9, 0x1e
/* 074C08 80074008 00681825 */  or    $v1, $v1, $t0
/* 074C0C 8007400C 00601025 */  move  $v0, $v1
.L80074010:
/* 074C10 80074010 03E00008 */  jr    $ra
/* 074C14 80074014 27BD0038 */   addiu $sp, $sp, 0x38

