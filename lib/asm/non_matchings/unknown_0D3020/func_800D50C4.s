glabel func_800D50C4
/* 0D5CC4 800D50C4 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0D5CC8 800D50C8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0D5CCC 800D50CC AFA40028 */  sw    $a0, 0x28($sp)
/* 0D5CD0 800D50D0 0C034958 */  jal   __osDisableInt
/* 0D5CD4 800D50D4 AFA5002C */   sw    $a1, 0x2c($sp)
/* 0D5CD8 800D50D8 0C031E34 */  jal   func_800C78D0
/* 0D5CDC 800D50DC AFA2001C */   sw    $v0, 0x1c($sp)
/* 0D5CE0 800D50E0 3C018013 */  lui   $at, %hi(D_8012D230) # $at, 0x8013
/* 0D5CE4 800D50E4 AC22D230 */  sw    $v0, %lo(D_8012D230)($at)
/* 0D5CE8 800D50E8 3C0E8013 */  lui   $t6, %hi(D_8012D230) # $t6, 0x8013
/* 0D5CEC 800D50EC 8DCED230 */  lw    $t6, %lo(D_8012D230)($t6)
/* 0D5CF0 800D50F0 8FA9002C */  lw    $t1, 0x2c($sp)
/* 0D5CF4 800D50F4 8FA80028 */  lw    $t0, 0x28($sp)
/* 0D5CF8 800D50F8 01C0C825 */  move  $t9, $t6
/* 0D5CFC 800D50FC 03295821 */  addu  $t3, $t9, $t1
/* 0D5D00 800D5100 24180000 */  li    $t8, 0
/* 0D5D04 800D5104 0169082B */  sltu  $at, $t3, $t1
/* 0D5D08 800D5108 00385021 */  addu  $t2, $at, $t8
/* 0D5D0C 800D510C 01485021 */  addu  $t2, $t2, $t0
/* 0D5D10 800D5110 AFAA0020 */  sw    $t2, 0x20($sp)
/* 0D5D14 800D5114 AFAB0024 */  sw    $t3, 0x24($sp)
/* 0D5D18 800D5118 0C035D18 */  jal   func_800D7460
/* 0D5D1C 800D511C 01602025 */   move  $a0, $t3
/* 0D5D20 800D5120 0C034960 */  jal   __osRestoreInt
/* 0D5D24 800D5124 8FA4001C */   lw    $a0, 0x1c($sp)
/* 0D5D28 800D5128 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0D5D2C 800D512C 27BD0028 */  addiu $sp, $sp, 0x28
/* 0D5D30 800D5130 03E00008 */  jr    $ra
/* 0D5D34 800D5134 00000000 */   nop   

