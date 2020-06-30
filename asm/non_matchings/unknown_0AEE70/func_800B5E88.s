glabel func_800B5E88
/* 0B6A88 800B5E88 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0B6A8C 800B5E8C AFBF0014 */  sw    $ra, 0x14($sp)
/* 0B6A90 800B5E90 0C01EB9D */  jal   func_8007AE74
/* 0B6A94 800B5E94 00002025 */   move  $a0, $zero
/* 0B6A98 800B5E98 3C018012 */  lui   $at, %hi(D_80127CA0) # $at, 0x8012
/* 0B6A9C 800B5E9C AC227CA0 */  sw    $v0, %lo(D_80127CA0)($at)
/* 0B6AA0 800B5EA0 0C01EB9D */  jal   func_8007AE74
/* 0B6AA4 800B5EA4 24040001 */   li    $a0, 1
/* 0B6AA8 800B5EA8 3C018012 */  lui   $at, %hi(D_80127CA4) # $at, 0x8012
/* 0B6AAC 800B5EAC AC227CA4 */  sw    $v0, %lo(D_80127CA4)($at)
/* 0B6AB0 800B5EB0 0C01EB9D */  jal   func_8007AE74
/* 0B6AB4 800B5EB4 24040002 */   li    $a0, 2
/* 0B6AB8 800B5EB8 3C018012 */  lui   $at, %hi(D_80127CA8) # $at, 0x8012
/* 0B6ABC 800B5EBC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0B6AC0 800B5EC0 AC227CA8 */  sw    $v0, %lo(D_80127CA8)($at)
/* 0B6AC4 800B5EC4 3C0E8012 */  lui   $t6, %hi(D_80127CD8) # $t6, 0x8012
/* 0B6AC8 800B5EC8 25CE7CD8 */  addiu $t6, %lo(D_80127CD8) # addiu $t6, $t6, 0x7cd8
/* 0B6ACC 800B5ECC 3C018013 */  lui   $at, %hi(D_801285D8) # $at, 0x8013
/* 0B6AD0 800B5ED0 AC2E85D8 */  sw    $t6, %lo(D_801285D8)($at)
/* 0B6AD4 800B5ED4 03E00008 */  jr    $ra
/* 0B6AD8 800B5ED8 27BD0018 */   addiu $sp, $sp, 0x18

