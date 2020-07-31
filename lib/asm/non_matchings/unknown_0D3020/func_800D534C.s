glabel func_800D534C
/* 0D5F4C 800D534C 27BDFFF8 */  addiu $sp, $sp, -8
/* 0D5F50 800D5350 A7A00006 */  sh    $zero, 6($sp)
/* 0D5F54 800D5354 A4C00000 */  sh    $zero, ($a2)
/* 0D5F58 800D5358 94CE0000 */  lhu   $t6, ($a2)
/* 0D5F5C 800D535C A4AE0000 */  sh    $t6, ($a1)
/* 0D5F60 800D5360 AFA00000 */  sw    $zero, ($sp)
.L800D5364:
/* 0D5F64 800D5364 8FAF0000 */  lw    $t7, ($sp)
/* 0D5F68 800D5368 008FC021 */  addu  $t8, $a0, $t7
/* 0D5F6C 800D536C 97190000 */  lhu   $t9, ($t8)
/* 0D5F70 800D5370 A7B90006 */  sh    $t9, 6($sp)
/* 0D5F74 800D5374 94A80000 */  lhu   $t0, ($a1)
/* 0D5F78 800D5378 01194821 */  addu  $t1, $t0, $t9
/* 0D5F7C 800D537C A4A90000 */  sh    $t1, ($a1)
/* 0D5F80 800D5380 97AB0006 */  lhu   $t3, 6($sp)
/* 0D5F84 800D5384 94CA0000 */  lhu   $t2, ($a2)
/* 0D5F88 800D5388 01606027 */  not   $t4, $t3
/* 0D5F8C 800D538C 014C6821 */  addu  $t5, $t2, $t4
/* 0D5F90 800D5390 A4CD0000 */  sh    $t5, ($a2)
/* 0D5F94 800D5394 8FAE0000 */  lw    $t6, ($sp)
/* 0D5F98 800D5398 25CF0002 */  addiu $t7, $t6, 2
/* 0D5F9C 800D539C 2DE1001C */  sltiu $at, $t7, 0x1c
/* 0D5FA0 800D53A0 1420FFF0 */  bnez  $at, .L800D5364
/* 0D5FA4 800D53A4 AFAF0000 */   sw    $t7, ($sp)
/* 0D5FA8 800D53A8 00001025 */  move  $v0, $zero
/* 0D5FAC 800D53AC 03E00008 */  jr    $ra
/* 0D5FB0 800D53B0 27BD0008 */   addiu $sp, $sp, 8

