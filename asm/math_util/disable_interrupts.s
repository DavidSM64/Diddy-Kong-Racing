glabel disable_interrupts /* Official name: disableInterrupts */
/* 070110 8006F510 3C08800E */  lui   $t0, %hi(gIntDisFlag) # $t0, 0x800e
/* 070114 8006F514 8108D430 */  lb    $t0, %lo(gIntDisFlag)($t0)
/* 070118 8006F518 11000006 */  beqz  $t0, .L8006F534
/* 07011C 8006F51C 40086000 */  mfc0  $t0, $12 # C0_SR - Status Register
/* 070120 8006F520 2401FFFE */  li    $at, -2
/* 070124 8006F524 01014824 */  and   $t1, $t0, $at
/* 070128 8006F528 40896000 */  mtc0  $t1, $12
/* 07012C 8006F52C 31020001 */  andi  $v0, $t0, 1
/* 070130 8006F530 00000000 */  nop   
.L8006F534:
/* 070134 8006F534 03E00008 */  jr    $ra
/* 070138 8006F538 00000000 */   nop   

