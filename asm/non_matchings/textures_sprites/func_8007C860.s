glabel func_8007C860
/* 07D460 8007C860 04800006 */  bltz  $a0, .L8007C87C
/* 07D464 8007C864 3C0E8012 */   lui   $t6, %hi(gNumberOfLoadedTextures) # $t6, 0x8012
/* 07D468 8007C868 8DCE6330 */  lw    $t6, %lo(gNumberOfLoadedTextures)($t6)
/* 07D46C 8007C86C 3C0F8012 */  lui   $t7, %hi(gTextureCache) # $t7, 0x8012
/* 07D470 8007C870 008E082A */  slt   $at, $a0, $t6
/* 07D474 8007C874 14200003 */  bnez  $at, .L8007C884
/* 07D478 8007C878 00000000 */   nop   
.L8007C87C:
/* 07D47C 8007C87C 03E00008 */  jr    $ra
/* 07D480 8007C880 2402FFFF */   li    $v0, -1
.L8007C884:
/* 07D484 8007C884 8DEF6328 */  lw    $t7, %lo(gTextureCache)($t7)
/* 07D488 8007C888 0004C8C0 */  sll   $t9, $a0, 3
/* 07D48C 8007C88C 01F94021 */  addu  $t0, $t7, $t9
/* 07D490 8007C890 8D020000 */  lw    $v0, ($t0)
/* 07D494 8007C894 00000000 */  nop   
/* 07D498 8007C898 03E00008 */  jr    $ra
/* 07D49C 8007C89C 00000000 */   nop   