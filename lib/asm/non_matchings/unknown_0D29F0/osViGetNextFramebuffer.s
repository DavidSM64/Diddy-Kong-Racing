glabel osViGetNextFramebuffer
/* 0D2AB0 800D1EB0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0D2AB4 800D1EB4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D2AB8 800D1EB8 0C034958 */  jal   __osDisableInt
/* 0D2ABC 800D1EBC AFB00018 */   sw    $s0, 0x18($sp)
/* 0D2AC0 800D1EC0 3C0E800E */  lui   $t6, %hi(__osViNext) # $t6, 0x800e
/* 0D2AC4 800D1EC4 8DCE4874 */  lw    $t6, %lo(__osViNext)($t6)
/* 0D2AC8 800D1EC8 00408025 */  move  $s0, $v0
/* 0D2ACC 800D1ECC 02002025 */  move  $a0, $s0
/* 0D2AD0 800D1ED0 8DCF0004 */  lw    $t7, 4($t6)
/* 0D2AD4 800D1ED4 0C034960 */  jal   __osRestoreInt
/* 0D2AD8 800D1ED8 AFAF0020 */   sw    $t7, 0x20($sp)
/* 0D2ADC 800D1EDC 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D2AE0 800D1EE0 8FA20020 */  lw    $v0, 0x20($sp)
/* 0D2AE4 800D1EE4 8FB00018 */  lw    $s0, 0x18($sp)
/* 0D2AE8 800D1EE8 03E00008 */  jr    $ra
/* 0D2AEC 800D1EEC 27BD0028 */   addiu $sp, $sp, 0x28

