glabel func_800011A8
/* 001DA8 800011A8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 001DAC 800011AC 308700FF */  andi  $a3, $a0, 0xff
/* 001DB0 800011B0 28E10010 */  slti  $at, $a3, 0x10
/* 001DB4 800011B4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 001DB8 800011B8 AFA40018 */  sw    $a0, 0x18($sp)
/* 001DBC 800011BC AFA5001C */  sw    $a1, 0x1c($sp)
/* 001DC0 800011C0 10200005 */  beqz  $at, .L800011D8
/* 001DC4 800011C4 30A600FF */   andi  $a2, $a1, 0xff
/* 001DC8 800011C8 3C04800E */  lui   $a0, %hi(D_800DC630) # $a0, 0x800e
/* 001DCC 800011CC 8C84C630 */  lw    $a0, %lo(D_800DC630)($a0)
/* 001DD0 800011D0 0C031E38 */  jal   func_800C78E0
/* 001DD4 800011D4 30E500FF */   andi  $a1, $a3, 0xff
.L800011D8:
/* 001DD8 800011D8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 001DDC 800011DC 27BD0018 */  addiu $sp, $sp, 0x18
/* 001DE0 800011E0 03E00008 */  jr    $ra
/* 001DE4 800011E4 00000000 */   nop   

