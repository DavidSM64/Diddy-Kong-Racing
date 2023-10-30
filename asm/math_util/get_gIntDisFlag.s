glabel get_gIntDisFlag
/* 070170 8006F570 3C02800E */  lui   $v0, %hi(gIntDisFlag) # $v0, 0x800e
/* 070174 8006F574 03E00008 */  jr    $ra
/* 070178 8006F578 9042D430 */   lbu   $v0, %lo(gIntDisFlag)($v0)
