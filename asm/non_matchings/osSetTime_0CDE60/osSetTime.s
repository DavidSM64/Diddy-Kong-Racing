glabel osSetTime
/* 0CDE60 800CD260 AFA40000 */  sw    $a0, ($sp)
/* 0CDE64 800CD264 8FAE0000 */  lw    $t6, ($sp)
/* 0CDE68 800CD268 AFA50004 */  sw    $a1, 4($sp)
/* 0CDE6C 800CD26C 3C018013 */  lui   $at, %hi(D_8012D220) # $at, 0x8013
/* 0CDE70 800CD270 8FAF0004 */  lw    $t7, 4($sp)
/* 0CDE74 800CD274 AC2ED220 */  sw    $t6, %lo(D_8012D220)($at)
/* 0CDE78 800CD278 3C018013 */  lui   $at, 0x8013
/* 0CDE7C 800CD27C 03E00008 */  jr    $ra
/* 0CDE80 800CD280 AC2FD224 */   sw    $t7, -0x2ddc($at)

/* 0CDE84 800CD284 00000000 */  nop   
/* 0CDE88 800CD288 00000000 */  nop   
/* 0CDE8C 800CD28C 00000000 */  nop   

