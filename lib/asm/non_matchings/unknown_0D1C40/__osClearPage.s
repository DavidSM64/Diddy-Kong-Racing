glabel __osClearPage
/* 0D2328 800D1728 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0D232C 800D172C AFA40028 */  sw    $a0, 0x28($sp)
/* 0D2330 800D1730 AFA70034 */  sw    $a3, 0x34($sp)
/* 0D2334 800D1734 93AE0037 */  lbu   $t6, 0x37($sp)
/* 0D2338 800D1738 8FAF0028 */  lw    $t7, 0x28($sp)
/* 0D233C 800D173C AFBF001C */  sw    $ra, 0x1c($sp)
/* 0D2340 800D1740 AFA5002C */  sw    $a1, 0x2c($sp)
/* 0D2344 800D1744 AFA60030 */  sw    $a2, 0x30($sp)
/* 0D2348 800D1748 AFA00020 */  sw    $zero, 0x20($sp)
/* 0D234C 800D174C A1EE0065 */  sb    $t6, 0x65($t7)
/* 0D2350 800D1750 0C0357F7 */  jal   __osPfsSelectBank
/* 0D2354 800D1754 8FA40028 */   lw    $a0, 0x28($sp)
/* 0D2358 800D1758 AFA20020 */  sw    $v0, 0x20($sp)
/* 0D235C 800D175C 8FB80020 */  lw    $t8, 0x20($sp)
/* 0D2360 800D1760 13000003 */  beqz  $t8, .L800D1770
/* 0D2364 800D1764 00000000 */   nop   
/* 0D2368 800D1768 1000001B */  b     .L800D17D8
/* 0D236C 800D176C 03001025 */   move  $v0, $t8
.L800D1770:
/* 0D2370 800D1770 AFA00024 */  sw    $zero, 0x24($sp)
.L800D1774:
/* 0D2374 800D1774 8FB90028 */  lw    $t9, 0x28($sp)
/* 0D2378 800D1778 8FA8002C */  lw    $t0, 0x2c($sp)
/* 0D237C 800D177C 8FAA0024 */  lw    $t2, 0x24($sp)
/* 0D2380 800D1780 8F240004 */  lw    $a0, 4($t9)
/* 0D2384 800D1784 8F250008 */  lw    $a1, 8($t9)
/* 0D2388 800D1788 000848C0 */  sll   $t1, $t0, 3
/* 0D238C 800D178C AFA00010 */  sw    $zero, 0x10($sp)
/* 0D2390 800D1790 8FA70030 */  lw    $a3, 0x30($sp)
/* 0D2394 800D1794 0C03363C */  jal   __osContRamWrite
/* 0D2398 800D1798 012A3021 */   addu  $a2, $t1, $t2
/* 0D239C 800D179C AFA20020 */  sw    $v0, 0x20($sp)
/* 0D23A0 800D17A0 8FAB0020 */  lw    $t3, 0x20($sp)
/* 0D23A4 800D17A4 15600006 */  bnez  $t3, .L800D17C0
/* 0D23A8 800D17A8 00000000 */   nop   
/* 0D23AC 800D17AC 8FAC0024 */  lw    $t4, 0x24($sp)
/* 0D23B0 800D17B0 258D0001 */  addiu $t5, $t4, 1
/* 0D23B4 800D17B4 29A10008 */  slti  $at, $t5, 8
/* 0D23B8 800D17B8 1420FFEE */  bnez  $at, .L800D1774
/* 0D23BC 800D17BC AFAD0024 */   sw    $t5, 0x24($sp)
.L800D17C0:
/* 0D23C0 800D17C0 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0D23C4 800D17C4 A1C00065 */  sb    $zero, 0x65($t6)
/* 0D23C8 800D17C8 0C0357F7 */  jal   __osPfsSelectBank
/* 0D23CC 800D17CC 8FA40028 */   lw    $a0, 0x28($sp)
/* 0D23D0 800D17D0 AFA20020 */  sw    $v0, 0x20($sp)
/* 0D23D4 800D17D4 8FA20020 */  lw    $v0, 0x20($sp)
.L800D17D8:
/* 0D23D8 800D17D8 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0D23DC 800D17DC 27BD0028 */  addiu $sp, $sp, 0x28
/* 0D23E0 800D17E0 03E00008 */  jr    $ra
/* 0D23E4 800D17E4 00000000 */   nop   

/* 0D23E8 800D17E8 00000000 */  nop   
/* 0D23EC 800D17EC 00000000 */  nop   

