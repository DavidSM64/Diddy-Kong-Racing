glabel intmask_restore /* Official name: enableInterrupts */
/* 07013C 8006F53C 3C08800E */  lui   $t0, %hi(gIntDisFlag) # $t0, 0x800e
/* 070140 8006F540 8108D430 */  lb    $t0, %lo(gIntDisFlag)($t0)
/* 070144 8006F544 11000005 */  beqz  $t0, .L8006F55C # Identical to __osRestoreInt below this line
/* 070148 8006F548 40086000 */   mfc0  $t0, $12 # C0_SR - Status Register
/* 07014C 8006F54C 01044025 */  or    $t0, $t0, $a0
/* 070150 8006F550 40886000 */  mtc0  $t0, $12
/* 070154 8006F554 00000000 */  nop   
/* 070158 8006F558 00000000 */  nop   
.L8006F55C:
/* 07015C 8006F55C 03E00008 */  jr    $ra
/* 070160 8006F560 00000000 */   nop   

