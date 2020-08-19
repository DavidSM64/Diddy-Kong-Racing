glabel func_8000418C
/* 004D8C 8000418C 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 004D90 80004190 AFBF0014 */  sw    $ra, 0x14($sp)
/* 004D94 80004194 8C8E0008 */  lw    $t6, 8($a0)
/* 004D98 80004198 00803825 */  move  $a3, $a0
/* 004D9C 8000419C 8DCF0004 */  lw    $t7, 4($t6)
/* 004DA0 800041A0 00000000 */  nop   
/* 004DA4 800041A4 81E40005 */  lb    $a0, 5($t7)
/* 004DA8 800041A8 0C032678 */  jal   alCents2Ratio
/* 004DAC 800041AC AFA70030 */   sw    $a3, 0x30($sp)
/* 004DB0 800041B0 8FA70030 */  lw    $a3, 0x30($sp)
/* 004DB4 800041B4 3C04800E */  lui   $a0, %hi(gAlSndPlayer) # $a0, 0x800e
/* 004DB8 800041B8 C4E4002C */  lwc1  $f4, 0x2c($a3)
/* 004DBC 800041BC 8C84C6BC */  lw    $a0, %lo(gAlSndPlayer)($a0)
/* 004DC0 800041C0 46040182 */  mul.s $f6, $f0, $f4
/* 004DC4 800041C4 24180010 */  li    $t8, 16
/* 004DC8 800041C8 A7B80020 */  sh    $t8, 0x20($sp)
/* 004DCC 800041CC 27A50020 */  addiu $a1, $sp, 0x20
/* 004DD0 800041D0 E7A6001C */  swc1  $f6, 0x1c($sp)
/* 004DD4 800041D4 8FB9001C */  lw    $t9, 0x1c($sp)
/* 004DD8 800041D8 34068235 */  li    $a2, 33333
/* 004DDC 800041DC AFA70024 */  sw    $a3, 0x24($sp)
/* 004DE0 800041E0 24840014 */  addiu $a0, $a0, 0x14
/* 004DE4 800041E4 0C03246B */  jal   alEvtqPostEvent
/* 004DE8 800041E8 AFB90028 */   sw    $t9, 0x28($sp)
/* 004DEC 800041EC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 004DF0 800041F0 27BD0030 */  addiu $sp, $sp, 0x30
/* 004DF4 800041F4 03E00008 */  jr    $ra
/* 004DF8 800041F8 00000000 */   nop   

