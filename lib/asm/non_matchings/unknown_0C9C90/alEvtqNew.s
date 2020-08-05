glabel alEvtqNew
/* 0C9F5C 800C935C 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C9F60 800C9360 AFB30020 */  sw    $s3, 0x20($sp)
/* 0C9F64 800C9364 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0C9F68 800C9368 AFB00014 */  sw    $s0, 0x14($sp)
/* 0C9F6C 800C936C AFBF0024 */  sw    $ra, 0x24($sp)
/* 0C9F70 800C9370 AFB10018 */  sw    $s1, 0x18($sp)
/* 0C9F74 800C9374 00809025 */  move  $s2, $a0
/* 0C9F78 800C9378 00C09825 */  move  $s3, $a2
/* 0C9F7C 800C937C AC800010 */  sw    $zero, 0x10($a0)
/* 0C9F80 800C9380 AC800008 */  sw    $zero, 8($a0)
/* 0C9F84 800C9384 AC80000C */  sw    $zero, 0xc($a0)
/* 0C9F88 800C9388 AC800000 */  sw    $zero, ($a0)
/* 0C9F8C 800C938C AC800004 */  sw    $zero, 4($a0)
/* 0C9F90 800C9390 18C00008 */  blez  $a2, .L800C93B4
/* 0C9F94 800C9394 00008025 */   move  $s0, $zero
/* 0C9F98 800C9398 00A08825 */  move  $s1, $a1
.L800C939C:
/* 0C9F9C 800C939C 02202025 */  move  $a0, $s1
/* 0C9FA0 800C93A0 0C0321E4 */  jal   alLink
/* 0C9FA4 800C93A4 02402825 */   move  $a1, $s2
/* 0C9FA8 800C93A8 26100001 */  addiu $s0, $s0, 1
/* 0C9FAC 800C93AC 1613FFFB */  bne   $s0, $s3, .L800C939C
/* 0C9FB0 800C93B0 2631001C */   addiu $s1, $s1, 0x1c
.L800C93B4:
/* 0C9FB4 800C93B4 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0C9FB8 800C93B8 8FB00014 */  lw    $s0, 0x14($sp)
/* 0C9FBC 800C93BC 8FB10018 */  lw    $s1, 0x18($sp)
/* 0C9FC0 800C93C0 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0C9FC4 800C93C4 8FB30020 */  lw    $s3, 0x20($sp)
/* 0C9FC8 800C93C8 03E00008 */  jr    $ra
/* 0C9FCC 800C93CC 27BD0028 */   addiu $sp, $sp, 0x28

