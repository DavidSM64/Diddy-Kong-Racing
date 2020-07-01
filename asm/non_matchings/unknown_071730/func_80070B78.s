glabel func_80070B78
/* 071778 80070B78 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 07177C 80070B7C AFBF0014 */  sw    $ra, 0x14($sp)
/* 071780 80070B80 AFA40030 */  sw    $a0, 0x30($sp)
/* 071784 80070B84 0C01BD44 */  jal   func_8006F510
/* 071788 80070B88 AFA50034 */   sw    $a1, 0x34($sp)
/* 07178C 80070B8C 8FAF0034 */  lw    $t7, 0x34($sp)
/* 071790 80070B90 8FAE0030 */  lw    $t6, 0x30($sp)
/* 071794 80070B94 000FC080 */  sll   $t8, $t7, 2
/* 071798 80070B98 030FC021 */  addu  $t8, $t8, $t7
/* 07179C 80070B9C 0018C080 */  sll   $t8, $t8, 2
/* 0717A0 80070BA0 01D83821 */  addu  $a3, $t6, $t8
/* 0717A4 80070BA4 AFA20020 */  sw    $v0, 0x20($sp)
/* 0717A8 80070BA8 00E02025 */  move  $a0, $a3
/* 0717AC 80070BAC AFA70018 */  sw    $a3, 0x18($sp)
/* 0717B0 80070BB0 0C01C327 */  jal   func_80070C9C
/* 0717B4 80070BB4 2405FFFF */   li    $a1, -1
/* 0717B8 80070BB8 8FA50018 */  lw    $a1, 0x18($sp)
/* 0717BC 80070BBC 8FA60034 */  lw    $a2, 0x34($sp)
/* 0717C0 80070BC0 0C01C2F9 */  jal   func_80070BE4
/* 0717C4 80070BC4 00402025 */   move  $a0, $v0
/* 0717C8 80070BC8 8FA40020 */  lw    $a0, 0x20($sp)
/* 0717CC 80070BCC 0C01BD4F */  jal   func_8006F53C
/* 0717D0 80070BD0 AFA2001C */   sw    $v0, 0x1c($sp)
/* 0717D4 80070BD4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0717D8 80070BD8 8FA2001C */  lw    $v0, 0x1c($sp)
/* 0717DC 80070BDC 03E00008 */  jr    $ra
/* 0717E0 80070BE0 27BD0030 */   addiu $sp, $sp, 0x30

