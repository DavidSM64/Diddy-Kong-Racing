glabel osViSetMode
/* 0D28A0 800D1CA0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0D28A4 800D1CA4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D28A8 800D1CA8 AFA40028 */  sw    $a0, 0x28($sp)
/* 0D28AC 800D1CAC 0C034958 */  jal   __osDisableInt
/* 0D28B0 800D1CB0 AFB00018 */   sw    $s0, 0x18($sp)
/* 0D28B4 800D1CB4 3C0F800E */  lui   $t7, %hi(__osViNext) # $t7, 0x800e
/* 0D28B8 800D1CB8 8DEF4874 */  lw    $t7, %lo(__osViNext)($t7)
/* 0D28BC 800D1CBC 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0D28C0 800D1CC0 3C19800E */  lui   $t9, %hi(__osViNext) # $t9, 0x800e
/* 0D28C4 800D1CC4 24180001 */  li    $t8, 1
/* 0D28C8 800D1CC8 ADEE0008 */  sw    $t6, 8($t7)
/* 0D28CC 800D1CCC 8F394874 */  lw    $t9, %lo(__osViNext)($t9)
/* 0D28D0 800D1CD0 3C08800E */  lui   $t0, %hi(__osViNext) # $t0, 0x800e
/* 0D28D4 800D1CD4 00408025 */  move  $s0, $v0
/* 0D28D8 800D1CD8 A7380000 */  sh    $t8, ($t9)
/* 0D28DC 800D1CDC 8D084874 */  lw    $t0, %lo(__osViNext)($t0)
/* 0D28E0 800D1CE0 02002025 */  move  $a0, $s0
/* 0D28E4 800D1CE4 8D090008 */  lw    $t1, 8($t0)
/* 0D28E8 800D1CE8 8D2A0004 */  lw    $t2, 4($t1)
/* 0D28EC 800D1CEC 0C034960 */  jal   __osRestoreInt
/* 0D28F0 800D1CF0 AD0A000C */   sw    $t2, 0xc($t0)
/* 0D28F4 800D1CF4 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D28F8 800D1CF8 8FB00018 */  lw    $s0, 0x18($sp)
/* 0D28FC 800D1CFC 27BD0028 */  addiu $sp, $sp, 0x28
/* 0D2900 800D1D00 03E00008 */  jr    $ra
/* 0D2904 800D1D04 00000000 */   nop   

/* 0D2908 800D1D08 00000000 */  nop   
/* 0D290C 800D1D0C 00000000 */  nop   

