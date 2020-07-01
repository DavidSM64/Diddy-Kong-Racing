glabel func_800D65B0
/* 0D71B0 800D65B0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0D71B4 800D65B4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D71B8 800D65B8 0C034958 */  jal   __osDisableInt
/* 0D71BC 800D65BC AFB00018 */   sw    $s0, 0x18($sp)
/* 0D71C0 800D65C0 3C0F800E */  lui   $t7, %hi(D_800E4890) # $t7, 0x800e
/* 0D71C4 800D65C4 8DEF4890 */  lw    $t7, %lo(D_800E4890)($t7)
/* 0D71C8 800D65C8 240E0002 */  li    $t6, 2
/* 0D71CC 800D65CC 3C04800E */  lui   $a0, %hi(D_800E4888) # $a0, 0x800e
/* 0D71D0 800D65D0 00408025 */  move  $s0, $v0
/* 0D71D4 800D65D4 24844888 */  addiu $a0, %lo(D_800E4888) # addiu $a0, $a0, 0x4888
/* 0D71D8 800D65D8 0C034CB3 */  jal   __osEnqueueAndYield
/* 0D71DC 800D65DC A5EE0010 */   sh    $t6, 0x10($t7)
/* 0D71E0 800D65E0 0C034960 */  jal   __osRestoreInt
/* 0D71E4 800D65E4 02002025 */   move  $a0, $s0
/* 0D71E8 800D65E8 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D71EC 800D65EC 8FB00018 */  lw    $s0, 0x18($sp)
/* 0D71F0 800D65F0 27BD0028 */  addiu $sp, $sp, 0x28
/* 0D71F4 800D65F4 03E00008 */  jr    $ra
/* 0D71F8 800D65F8 00000000 */   nop   

/* 0D71FC 800D65FC 00000000 */  nop   
