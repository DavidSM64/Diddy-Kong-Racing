glabel func_80063BA0
/* 0647A0 80063BA0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0647A4 80063BA4 AFA60030 */  sw    $a2, 0x30($sp)
/* 0647A8 80063BA8 93B90033 */  lbu   $t9, 0x33($sp)
/* 0647AC 80063BAC 00A03825 */  move  $a3, $a1
/* 0647B0 80063BB0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0647B4 80063BB4 AFA40028 */  sw    $a0, 0x28($sp)
/* 0647B8 80063BB8 AFA5002C */  sw    $a1, 0x2c($sp)
/* 0647BC 80063BBC 240E0002 */  li    $t6, 2
/* 0647C0 80063BC0 34EF00B0 */  ori   $t7, $a3, 0xb0
/* 0647C4 80063BC4 24180008 */  li    $t8, 8
/* 0647C8 80063BC8 A7AE0018 */  sh    $t6, 0x18($sp)
/* 0647CC 80063BCC AFA0001C */  sw    $zero, 0x1c($sp)
/* 0647D0 80063BD0 A3AF0020 */  sb    $t7, 0x20($sp)
/* 0647D4 80063BD4 A3B80021 */  sb    $t8, 0x21($sp)
/* 0647D8 80063BD8 27A50018 */  addiu $a1, $sp, 0x18
/* 0647DC 80063BDC 24840048 */  addiu $a0, $a0, 0x48
/* 0647E0 80063BE0 00003025 */  move  $a2, $zero
/* 0647E4 80063BE4 0C03246B */  jal   func_800C91AC
/* 0647E8 80063BE8 A3B90022 */   sb    $t9, 0x22($sp)
/* 0647EC 80063BEC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0647F0 80063BF0 27BD0028 */  addiu $sp, $sp, 0x28
/* 0647F4 80063BF4 03E00008 */  jr    $ra
/* 0647F8 80063BF8 00000000 */   nop   

/* 0647FC 80063BFC 00000000 */  nop   

