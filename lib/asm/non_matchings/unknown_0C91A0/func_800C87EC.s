glabel func_800C87EC
/* 0C93EC 800C87EC 3C02800E */  lui   $v0, %hi(D_800E3780) # $v0, 0x800e
/* 0C93F0 800C87F0 24423780 */  addiu $v0, %lo(D_800E3780) # addiu $v0, $v0, 0x3780
/* 0C93F4 800C87F4 8C4E0000 */  lw    $t6, ($v0)
/* 0C93F8 800C87F8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0C93FC 800C87FC AFBF0014 */  sw    $ra, 0x14($sp)
/* 0C9400 800C8800 55C00004 */  bnezl $t6, .L800C8814
/* 0C9404 800C8804 8FBF0014 */   lw    $ra, 0x14($sp)
/* 0C9408 800C8808 0C01944C */  jal   func_80065130
/* 0C940C 800C880C AC440000 */   sw    $a0, ($v0)
/* 0C9410 800C8810 8FBF0014 */  lw    $ra, 0x14($sp)
.L800C8814:
/* 0C9414 800C8814 27BD0018 */  addiu $sp, $sp, 0x18
/* 0C9418 800C8818 03E00008 */  jr    $ra
/* 0C941C 800C881C 00000000 */   nop   

