glabel osViGetCurrentFramebuffer
/* 0D2A70 800D1E70 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0D2A74 800D1E74 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D2A78 800D1E78 0C034958 */  jal   __osDisableInt
/* 0D2A7C 800D1E7C AFB00018 */   sw    $s0, 0x18($sp)
/* 0D2A80 800D1E80 3C0E800E */  lui   $t6, %hi(D_800E4870) # $t6, 0x800e
/* 0D2A84 800D1E84 8DCE4870 */  lw    $t6, %lo(D_800E4870)($t6)
/* 0D2A88 800D1E88 00408025 */  move  $s0, $v0
/* 0D2A8C 800D1E8C 02002025 */  move  $a0, $s0
/* 0D2A90 800D1E90 8DCF0004 */  lw    $t7, 4($t6)
/* 0D2A94 800D1E94 0C034960 */  jal   __osRestoreInt
/* 0D2A98 800D1E98 AFAF0020 */   sw    $t7, 0x20($sp)
/* 0D2A9C 800D1E9C 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D2AA0 800D1EA0 8FA20020 */  lw    $v0, 0x20($sp)
/* 0D2AA4 800D1EA4 8FB00018 */  lw    $s0, 0x18($sp)
/* 0D2AA8 800D1EA8 03E00008 */  jr    $ra
/* 0D2AAC 800D1EAC 27BD0028 */   addiu $sp, $sp, 0x28

