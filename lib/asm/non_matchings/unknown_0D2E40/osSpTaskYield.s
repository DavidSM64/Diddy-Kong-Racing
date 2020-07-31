glabel osSpTaskYield
/* 0D2E40 800D2240 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0D2E44 800D2244 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0D2E48 800D2248 0C033490 */  jal   __osSpSetStatus
/* 0D2E4C 800D224C 24040400 */   li    $a0, 1024
/* 0D2E50 800D2250 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0D2E54 800D2254 27BD0018 */  addiu $sp, $sp, 0x18
/* 0D2E58 800D2258 03E00008 */  jr    $ra
/* 0D2E5C 800D225C 00000000 */   nop   

