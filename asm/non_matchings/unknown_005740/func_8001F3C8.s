glabel func_8001F3C8
/* 01FFC8 8001F3C8 3C028012 */  lui   $v0, %hi(D_8011ADD4) # $v0, 0x8012
/* 01FFCC 8001F3CC 2442ADD4 */  addiu $v0, %lo(D_8011ADD4) # addiu $v0, $v0, -0x522c
/* 01FFD0 8001F3D0 804E0000 */  lb    $t6, ($v0)
/* 01FFD4 8001F3D4 3C018012 */  lui   $at, %hi(D_8011AE78) # $at, 0x8012
/* 01FFD8 8001F3D8 108E0002 */  beq   $a0, $t6, .L8001F3E4
/* 01FFDC 8001F3DC 00000000 */   nop   
/* 01FFE0 8001F3E0 A420AE78 */  sh    $zero, %lo(D_8011AE78)($at)
.L8001F3E4:
/* 01FFE4 8001F3E4 03E00008 */  jr    $ra
/* 01FFE8 8001F3E8 A0440000 */   sb    $a0, ($v0)

