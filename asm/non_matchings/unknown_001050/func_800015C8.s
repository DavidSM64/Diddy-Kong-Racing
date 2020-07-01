glabel func_800015C8
/* 0021C8 800015C8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0021CC 800015CC 3C04800E */  lui   $a0, %hi(D_800DC630) # $a0, 0x800e
/* 0021D0 800015D0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0021D4 800015D4 8C84C630 */  lw    $a0, %lo(D_800DC630)($a0)
/* 0021D8 800015D8 0C031E94 */  jal   func_800C7A50
/* 0021DC 800015DC 00000000 */   nop   
/* 0021E0 800015E0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0021E4 800015E4 384E0001 */  xori  $t6, $v0, 1
/* 0021E8 800015E8 2DCE0001 */  sltiu $t6, $t6, 1
/* 0021EC 800015EC 31C200FF */  andi  $v0, $t6, 0xff
/* 0021F0 800015F0 03E00008 */  jr    $ra
/* 0021F4 800015F4 27BD0018 */   addiu $sp, $sp, 0x18

