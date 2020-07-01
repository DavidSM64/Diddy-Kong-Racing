glabel func_80075AEC
/* 0766EC 80075AEC 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0766F0 80075AF0 AFA40018 */  sw    $a0, 0x18($sp)
/* 0766F4 80075AF4 3C048012 */  lui   $a0, %hi(D_80124010) # $a0, 0x8012
/* 0766F8 80075AF8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0766FC 80075AFC 8C844010 */  lw    $a0, %lo(D_80124010)($a0)
/* 076700 80075B00 0C0333F8 */  jal   func_800CCFE0
/* 076704 80075B04 00000000 */   nop   
/* 076708 80075B08 8FBF0014 */  lw    $ra, 0x14($sp)
/* 07670C 80075B0C 27BD0018 */  addiu $sp, $sp, 0x18
/* 076710 80075B10 03E00008 */  jr    $ra
/* 076714 80075B14 00001025 */   move  $v0, $zero

