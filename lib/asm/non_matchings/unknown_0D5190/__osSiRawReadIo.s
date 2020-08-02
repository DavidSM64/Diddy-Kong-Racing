glabel __osSiRawReadIo
/* 0D5190 800D4590 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0D5194 800D4594 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0D5198 800D4598 AFA40018 */  sw    $a0, 0x18($sp)
/* 0D519C 800D459C 0C0354B0 */  jal   __osSiDeviceBusy
/* 0D51A0 800D45A0 AFA5001C */   sw    $a1, 0x1c($sp)
/* 0D51A4 800D45A4 10400003 */  beqz  $v0, .L800D45B4
/* 0D51A8 800D45A8 00000000 */   nop   
/* 0D51AC 800D45AC 10000008 */  b     .L800D45D0
/* 0D51B0 800D45B0 2402FFFF */   li    $v0, -1
.L800D45B4:
/* 0D51B4 800D45B4 8FAE0018 */  lw    $t6, 0x18($sp)
/* 0D51B8 800D45B8 3C01A000 */  lui   $at, 0xa000
/* 0D51BC 800D45BC 8FB9001C */  lw    $t9, 0x1c($sp)
/* 0D51C0 800D45C0 01C17825 */  or    $t7, $t6, $at
/* 0D51C4 800D45C4 8DF80000 */  lw    $t8, ($t7)
/* 0D51C8 800D45C8 00001025 */  move  $v0, $zero
/* 0D51CC 800D45CC AF380000 */  sw    $t8, ($t9)
.L800D45D0:
/* 0D51D0 800D45D0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0D51D4 800D45D4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0D51D8 800D45D8 03E00008 */  jr    $ra
/* 0D51DC 800D45DC 00000000 */   nop   

