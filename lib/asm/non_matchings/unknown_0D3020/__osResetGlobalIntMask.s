glabel __osResetGlobalIntMask
/* 0D7100 800D6500 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0D7104 800D6504 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D7108 800D6508 AFA40028 */  sw    $a0, 0x28($sp)
/* 0D710C 800D650C 0C034958 */  jal   __osDisableInt
/* 0D7110 800D6510 AFB00018 */   sw    $s0, 0x18($sp)
/* 0D7114 800D6514 8FAF0028 */  lw    $t7, 0x28($sp)
/* 0D7118 800D6518 3C0E800E */  lui   $t6, %hi(__OSGlobalIntMask) # $t6, 0x800e
/* 0D711C 800D651C 8DCE38AC */  lw    $t6, %lo(__OSGlobalIntMask)($t6)
/* 0D7120 800D6520 2401FBFE */  li    $at, -1026
/* 0D7124 800D6524 01E1C024 */  and   $t8, $t7, $at
/* 0D7128 800D6528 0300C827 */  not   $t9, $t8
/* 0D712C 800D652C 00408025 */  move  $s0, $v0
/* 0D7130 800D6530 3C01800E */  lui   $at, %hi(__OSGlobalIntMask) # $at, 0x800e
/* 0D7134 800D6534 01D94024 */  and   $t0, $t6, $t9
/* 0D7138 800D6538 AC2838AC */  sw    $t0, %lo(__OSGlobalIntMask)($at)
/* 0D713C 800D653C 0C034960 */  jal   __osRestoreInt
/* 0D7140 800D6540 02002025 */   move  $a0, $s0
/* 0D7144 800D6544 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D7148 800D6548 8FB00018 */  lw    $s0, 0x18($sp)
/* 0D714C 800D654C 27BD0028 */  addiu $sp, $sp, 0x28
/* 0D7150 800D6550 03E00008 */  jr    $ra
/* 0D7154 800D6554 00000000 */   nop   

/* 0D7158 800D6558 00000000 */  nop   
/* 0D715C 800D655C 00000000 */  nop   
