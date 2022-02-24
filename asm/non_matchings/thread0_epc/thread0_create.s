glabel thread0_create
/* 0B7B50 800B6F50 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0B7B54 800B6F54 3C0E8013 */  lui   $t6, %hi(D_801295E0) # $t6, 0x8013
/* 0B7B58 800B6F58 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0B7B5C 800B6F5C 25CE95E0 */  addiu $t6, %lo(D_801295E0) # addiu $t6, $t6, -0x6a20
/* 0B7B60 800B6F60 3C048013 */  lui   $a0, %hi(D_801295E0) # $a0, 0x8013
/* 0B7B64 800B6F64 3C06800B */  lui   $a2, %hi(thread0_Main) # $a2, 0x800b
/* 0B7B68 800B6F68 240F00FF */  li    $t7, 255
/* 0B7B6C 800B6F6C AFAF0014 */  sw    $t7, 0x14($sp)
/* 0B7B70 800B6F70 24C66FC4 */  addiu $a2, %lo(thread0_Main) # addiu $a2, $a2, 0x6fc4
/* 0B7B74 800B6F74 248495E0 */  addiu $a0, %lo(D_801295E0) # addiu $a0, $a0, -0x6a20
/* 0B7B78 800B6F78 AFAE0010 */  sw    $t6, 0x10($sp)
/* 0B7B7C 800B6F7C 00002825 */  move  $a1, $zero
/* 0B7B80 800B6F80 0C032214 */  jal   osCreateThread
/* 0B7B84 800B6F84 00003825 */   move  $a3, $zero
/* 0B7B88 800B6F88 3C048013 */  lui   $a0, %hi(D_801295E0) # $a0, 0x8013
/* 0B7B8C 800B6F8C 0C032268 */  jal   osStartThread
/* 0B7B90 800B6F90 248495E0 */   addiu $a0, %lo(D_801295E0) # addiu $a0, $a0, -0x6a20
/* 0B7B94 800B6F94 3C028013 */  lui   $v0, %hi(D_80129FB0) # $v0, 0x8013
/* 0B7B98 800B6F98 3C048013 */  lui   $a0, %hi(D_80129FBC) # $a0, 0x8013
/* 0B7B9C 800B6F9C 24849FBC */  addiu $a0, %lo(D_80129FBC) # addiu $a0, $a0, -0x6044
/* 0B7BA0 800B6FA0 24429FB0 */  addiu $v0, %lo(D_80129FB0) # addiu $v0, $v0, -0x6050
/* 0B7BA4 800B6FA4 2403FFFF */  li    $v1, -1
.L800B6FA8:
/* 0B7BA8 800B6FA8 24420004 */  addiu $v0, $v0, 4
/* 0B7BAC 800B6FAC 1444FFFE */  bne   $v0, $a0, .L800B6FA8
/* 0B7BB0 800B6FB0 AC43FFFC */   sw    $v1, -4($v0)
/* 0B7BB4 800B6FB4 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0B7BB8 800B6FB8 27BD0020 */  addiu $sp, $sp, 0x20
/* 0B7BBC 800B6FBC 03E00008 */  jr    $ra
/* 0B7BC0 800B6FC0 00000000 */   nop   

