glabel func_800D5FDC
/* 0D6BDC 800D5FDC 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 0D6BE0 800D5FE0 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D6BE4 800D5FE4 AFA40048 */  sw    $a0, 0x48($sp)
/* 0D6BE8 800D5FE8 AFA00020 */  sw    $zero, 0x20($sp)
/* 0D6BEC 800D5FEC AFA00024 */  sw    $zero, 0x24($sp)
.L800D5FF0:
/* 0D6BF0 800D5FF0 8FAE0048 */  lw    $t6, 0x48($sp)
/* 0D6BF4 800D5FF4 8FB80024 */  lw    $t8, 0x24($sp)
/* 0D6BF8 800D5FF8 91CF0065 */  lbu   $t7, 0x65($t6)
/* 0D6BFC 800D5FFC 03B8C821 */  addu  $t9, $sp, $t8
/* 0D6C00 800D6000 A32F0028 */  sb    $t7, 0x28($t9)
/* 0D6C04 800D6004 8FA80024 */  lw    $t0, 0x24($sp)
/* 0D6C08 800D6008 25090001 */  addiu $t1, $t0, 1
/* 0D6C0C 800D600C 29210020 */  slti  $at, $t1, 0x20
/* 0D6C10 800D6010 1420FFF7 */  bnez  $at, .L800D5FF0
/* 0D6C14 800D6014 AFA90024 */   sw    $t1, 0x24($sp)
/* 0D6C18 800D6018 8FAA0048 */  lw    $t2, 0x48($sp)
/* 0D6C1C 800D601C 24060400 */  li    $a2, 1024
/* 0D6C20 800D6020 27A70028 */  addiu $a3, $sp, 0x28
/* 0D6C24 800D6024 8D440004 */  lw    $a0, 4($t2)
/* 0D6C28 800D6028 8D450008 */  lw    $a1, 8($t2)
/* 0D6C2C 800D602C 0C03363C */  jal   func_800CD8F0
/* 0D6C30 800D6030 AFA00010 */   sw    $zero, 0x10($sp)
/* 0D6C34 800D6034 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D6C38 800D6038 AFA20020 */  sw    $v0, 0x20($sp)
/* 0D6C3C 800D603C 8FA20020 */  lw    $v0, 0x20($sp)
/* 0D6C40 800D6040 03E00008 */  jr    $ra
/* 0D6C44 800D6044 27BD0048 */   addiu $sp, $sp, 0x48

/* 0D6C48 800D6048 00000000 */  nop   
/* 0D6C4C 800D604C 00000000 */  nop   
