glabel alClose
/* 0C93B4 800C87B4 3C0E800E */  lui   $t6, %hi(alGlobals) # $t6, 0x800e
/* 0C93B8 800C87B8 8DCE3780 */  lw    $t6, %lo(alGlobals)($t6)
/* 0C93BC 800C87BC 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C93C0 800C87C0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C93C4 800C87C4 51C00006 */  beql  $t6, $zero, .L800C87E0
/* 0C93C8 800C87C8 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0C93CC 800C87CC 0C034B18 */  jal   alSynDelete
/* 0C93D0 800C87D0 00000000 */   nop   
/* 0C93D4 800C87D4 3C01800E */  lui   $at, %hi(alGlobals) # $at, 0x800e
/* 0C93D8 800C87D8 AC203780 */  sw    $zero, %lo(alGlobals)($at)
/* 0C93DC 800C87DC 8FBF0014 */  lw    $ra, 0x14($sp)
.L800C87E0:
/* 0C93E0 800C87E0 27BD0018 */  addiu $sp, $sp, 0x18
/* 0C93E4 800C87E4 03E00008 */  jr    $ra
/* 0C93E8 800C87E8 00000000 */   nop   

