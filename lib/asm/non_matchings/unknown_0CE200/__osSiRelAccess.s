glabel __osSiRelAccess
/* 0CE294 800CD694 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CE298 800CD698 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0CE29C 800CD69C 3C048013 */  lui   $a0, %hi(D_8012CE28) # $a0, 0x8013
/* 0CE2A0 800CD6A0 2484CE28 */  addiu $a0, %lo(D_8012CE28) # addiu $a0, $a0, -0x31d8
/* 0CE2A4 800CD6A4 00002825 */  move  $a1, $zero
/* 0CE2A8 800CD6A8 0C03238C */  jal   osSendMesg
/* 0CE2AC 800CD6AC 00003025 */   move  $a2, $zero
/* 0CE2B0 800CD6B0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CE2B4 800CD6B4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0CE2B8 800CD6B8 03E00008 */  jr    $ra
/* 0CE2BC 800CD6BC 00000000 */   nop   

