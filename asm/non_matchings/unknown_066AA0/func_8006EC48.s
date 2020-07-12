glabel func_8006EC48
/* 06F848 8006EC48 3C0E8012 */  lui   $t6, %hi(D_801234EC) # $t6, 0x8012
/* 06F84C 8006EC4C 8DCE34EC */  lw    $t6, %lo(D_801234EC)($t6)
/* 06F850 8006EC50 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 06F854 8006EC54 AFBF0014 */  sw    $ra, 0x14($sp)
/* 06F858 8006EC58 15C00010 */  bnez  $t6, .L8006EC9C
/* 06F85C 8006EC5C AFA40018 */   sw    $a0, 0x18($sp)
/* 06F860 8006EC60 0C0270B4 */  jal   is_in_tracks_mode
/* 06F864 8006EC64 00000000 */   nop   
/* 06F868 8006EC68 1440000C */  bnez  $v0, .L8006EC9C
/* 06F86C 8006EC6C 2401F3FF */   li    $at, -3073
/* 06F870 8006EC70 3C02800E */  lui   $v0, %hi(D_800DD37C) # $v0, 0x800e
/* 06F874 8006EC74 2442D37C */  addiu $v0, %lo(D_800DD37C) # addiu $v0, $v0, -0x2c84
/* 06F878 8006EC78 8C4F0000 */  lw    $t7, ($v0)
/* 06F87C 8006EC7C 8FA90018 */  lw    $t1, 0x18($sp)
/* 06F880 8006EC80 01E1C024 */  and   $t8, $t7, $at
/* 06F884 8006EC84 312A0003 */  andi  $t2, $t1, 3
/* 06F888 8006EC88 000A5A80 */  sll   $t3, $t2, 0xa
/* 06F88C 8006EC8C 37080040 */  ori   $t0, $t8, 0x40
/* 06F890 8006EC90 AC580000 */  sw    $t8, ($v0)
/* 06F894 8006EC94 010B6025 */  or    $t4, $t0, $t3
/* 06F898 8006EC98 AC4C0000 */  sw    $t4, ($v0)
.L8006EC9C:
/* 06F89C 8006EC9C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 06F8A0 8006ECA0 27BD0018 */  addiu $sp, $sp, 0x18
/* 06F8A4 8006ECA4 03E00008 */  jr    $ra
/* 06F8A8 8006ECA8 00000000 */   nop   

