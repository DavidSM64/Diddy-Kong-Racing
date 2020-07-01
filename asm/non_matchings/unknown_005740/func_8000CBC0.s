glabel func_8000CBC0
/* 00D7C0 8000CBC0 3C038012 */  lui   $v1, %hi(D_8011AE08) # $v1, 0x8012
/* 00D7C4 8000CBC4 3C028012 */  lui   $v0, %hi(D_8011AE48) # $v0, 0x8012
/* 00D7C8 8000CBC8 2442AE48 */  addiu $v0, %lo(D_8011AE48) # addiu $v0, $v0, -0x51b8
/* 00D7CC 8000CBCC 2463AE08 */  addiu $v1, %lo(D_8011AE08) # addiu $v1, $v1, -0x51f8
.L8000CBD0:
/* 00D7D0 8000CBD0 24630010 */  addiu $v1, $v1, 0x10
/* 00D7D4 8000CBD4 AC60FFF0 */  sw    $zero, -0x10($v1)
/* 00D7D8 8000CBD8 AC60FFF4 */  sw    $zero, -0xc($v1)
/* 00D7DC 8000CBDC AC60FFF8 */  sw    $zero, -8($v1)
/* 00D7E0 8000CBE0 1462FFFB */  bne   $v1, $v0, .L8000CBD0
/* 00D7E4 8000CBE4 AC60FFFC */   sw    $zero, -4($v1)
/* 00D7E8 8000CBE8 03E00008 */  jr    $ra
/* 00D7EC 8000CBEC 00000000 */   nop   

