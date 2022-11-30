glabel func_800C15D4
/* 0C21D4 800C15D4 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0C21D8 800C15D8 AFBF0034 */  sw    $ra, 0x34($sp)
/* 0C21DC 800C15DC AFA40038 */  sw    $a0, 0x38($sp)
/* 0C21E0 800C15E0 3C05FFFF */  lui   $a1, (0xFFFF00FF >> 16) # lui $a1, 0xffff
/* 0C21E4 800C15E4 AFB50030 */  sw    $s5, 0x30($sp)
/* 0C21E8 800C15E8 AFB4002C */  sw    $s4, 0x2c($sp)
/* 0C21EC 800C15EC AFB30028 */  sw    $s3, 0x28($sp)
/* 0C21F0 800C15F0 AFB20024 */  sw    $s2, 0x24($sp)
/* 0C21F4 800C15F4 AFB10020 */  sw    $s1, 0x20($sp)
/* 0C21F8 800C15F8 AFB0001C */  sw    $s0, 0x1c($sp)
/* 0C21FC 800C15FC E7B50010 */  swc1  $f21, 0x10($sp)
/* 0C2200 800C1600 E7B40014 */  swc1  $f20, 0x14($sp)
/* 0C2204 800C1604 34A500FF */  ori   $a1, (0xFFFF00FF & 0xFFFF) # ori $a1, $a1, 0xff
/* 0C2208 800C1608 0C01C327 */  jal   allocate_from_main_pool_safe
/* 0C220C 800C160C 24040DA0 */   li    $a0, 3488
/* 0C2210 800C1610 3C04800E */  lui   $a0, %hi(sTransitionVtx) # $a0, 0x800e
/* 0C2214 800C1614 3C05800E */  lui   $a1, %hi(sTransitionTris) # $a1, 0x800e
/* 0C2218 800C1618 244F02D0 */  addiu $t7, $v0, 0x2d0
/* 0C221C 800C161C 24A531C8 */  addiu $a1, %lo(sTransitionTris) # addiu $a1, $a1, 0x31c8
/* 0C2220 800C1620 248431C0 */  addiu $a0, %lo(sTransitionVtx) # addiu $a0, $a0, 0x31c0
/* 0C2224 800C1624 25F902D0 */  addiu $t9, $t7, 0x2d0
/* 0C2228 800C1628 272D0400 */  addiu $t5, $t9, 0x400
/* 0C222C 800C162C AC820000 */  sw    $v0, ($a0)
/* 0C2230 800C1630 AC8F0004 */  sw    $t7, 4($a0)
/* 0C2234 800C1634 ACB90000 */  sw    $t9, ($a1)
/* 0C2238 800C1638 ACAD0004 */  sw    $t5, 4($a1)
/* 0C223C 800C163C 3C058013 */  lui   $a1, %hi(gCurFadeGreen) # $a1, 0x8013
/* 0C2240 800C1640 3C048013 */  lui   $a0, %hi(gCurFadeRed) # $a0, 0x8013
/* 0C2244 800C1644 3C03800E */  lui   $v1, %hi(sTransitionVtx) # $v1, 0x800e
/* 0C2248 800C1648 3C0A800E */  lui   $t2, %hi(sTransitionTris) # $t2, 0x800e
/* 0C224C 800C164C 3C068013 */  lui   $a2, %hi(gCurFadeBlue) # $a2, 0x8013
/* 0C2250 800C1650 24C6A736 */  addiu $a2, %lo(gCurFadeBlue) # addiu $a2, $a2, -0x58ca
/* 0C2254 800C1654 254A31C8 */  addiu $t2, %lo(sTransitionTris) # addiu $t2, $t2, 0x31c8
/* 0C2258 800C1658 246331C0 */  addiu $v1, %lo(sTransitionVtx) # addiu $v1, $v1, 0x31c0
/* 0C225C 800C165C 2484A734 */  addiu $a0, %lo(gCurFadeRed) # addiu $a0, $a0, -0x58cc
/* 0C2260 800C1660 24A5A735 */  addiu $a1, %lo(gCurFadeGreen) # addiu $a1, $a1, -0x58cb
/* 0C2264 800C1664 240902D0 */  li    $t1, 720
/* 0C2268 800C1668 240800FF */  li    $t0, 255
/* 0C226C 800C166C 00001025 */  move  $v0, $zero
.L800C1670:
/* 0C2270 800C1670 8C6F0000 */  lw    $t7, ($v1)
/* 0C2274 800C1674 908E0000 */  lbu   $t6, ($a0)
/* 0C2278 800C1678 01E2C021 */  addu  $t8, $t7, $v0
/* 0C227C 800C167C A30E0006 */  sb    $t6, 6($t8)
/* 0C2280 800C1680 8C6C0000 */  lw    $t4, ($v1)
/* 0C2284 800C1684 90B90000 */  lbu   $t9, ($a1)
/* 0C2288 800C1688 01826821 */  addu  $t5, $t4, $v0
/* 0C228C 800C168C A1B90007 */  sb    $t9, 7($t5)
/* 0C2290 800C1690 8C6E0000 */  lw    $t6, ($v1)
/* 0C2294 800C1694 90CF0000 */  lbu   $t7, ($a2)
/* 0C2298 800C1698 01C2C021 */  addu  $t8, $t6, $v0
/* 0C229C 800C169C A30F0008 */  sb    $t7, 8($t8)
/* 0C22A0 800C16A0 8C6C0000 */  lw    $t4, ($v1)
/* 0C22A4 800C16A4 00000000 */  nop   
/* 0C22A8 800C16A8 0182C821 */  addu  $t9, $t4, $v0
/* 0C22AC 800C16AC A3280009 */  sb    $t0, 9($t9)
/* 0C22B0 800C16B0 8C6E0000 */  lw    $t6, ($v1)
/* 0C22B4 800C16B4 908D0000 */  lbu   $t5, ($a0)
/* 0C22B8 800C16B8 01C27821 */  addu  $t7, $t6, $v0
/* 0C22BC 800C16BC A1ED0010 */  sb    $t5, 0x10($t7)
/* 0C22C0 800C16C0 8C6C0000 */  lw    $t4, ($v1)
/* 0C22C4 800C16C4 90B80000 */  lbu   $t8, ($a1)
/* 0C22C8 800C16C8 0182C821 */  addu  $t9, $t4, $v0
/* 0C22CC 800C16CC A3380011 */  sb    $t8, 0x11($t9)
/* 0C22D0 800C16D0 8C6D0000 */  lw    $t5, ($v1)
/* 0C22D4 800C16D4 90CE0000 */  lbu   $t6, ($a2)
/* 0C22D8 800C16D8 01A27821 */  addu  $t7, $t5, $v0
/* 0C22DC 800C16DC A1EE0012 */  sb    $t6, 0x12($t7)
/* 0C22E0 800C16E0 8C6C0000 */  lw    $t4, ($v1)
/* 0C22E4 800C16E4 00000000 */  nop   
/* 0C22E8 800C16E8 0182C021 */  addu  $t8, $t4, $v0
/* 0C22EC 800C16EC A3080013 */  sb    $t0, 0x13($t8)
/* 0C22F0 800C16F0 8C6D0000 */  lw    $t5, ($v1)
/* 0C22F4 800C16F4 90990000 */  lbu   $t9, ($a0)
/* 0C22F8 800C16F8 01A27021 */  addu  $t6, $t5, $v0
/* 0C22FC 800C16FC A1D9001A */  sb    $t9, 0x1a($t6)
/* 0C2300 800C1700 8C6C0000 */  lw    $t4, ($v1)
/* 0C2304 800C1704 90AF0000 */  lbu   $t7, ($a1)
/* 0C2308 800C1708 0182C021 */  addu  $t8, $t4, $v0
/* 0C230C 800C170C A30F001B */  sb    $t7, 0x1b($t8)
/* 0C2310 800C1710 8C790000 */  lw    $t9, ($v1)
/* 0C2314 800C1714 90CD0000 */  lbu   $t5, ($a2)
/* 0C2318 800C1718 03227021 */  addu  $t6, $t9, $v0
/* 0C231C 800C171C A1CD001C */  sb    $t5, 0x1c($t6)
/* 0C2320 800C1720 8C6C0000 */  lw    $t4, ($v1)
/* 0C2324 800C1724 00000000 */  nop   
/* 0C2328 800C1728 01827821 */  addu  $t7, $t4, $v0
/* 0C232C 800C172C A1E8001D */  sb    $t0, 0x1d($t7)
/* 0C2330 800C1730 8C790000 */  lw    $t9, ($v1)
/* 0C2334 800C1734 90980000 */  lbu   $t8, ($a0)
/* 0C2338 800C1738 03226821 */  addu  $t5, $t9, $v0
/* 0C233C 800C173C A1B80024 */  sb    $t8, 0x24($t5)
/* 0C2340 800C1740 8C6C0000 */  lw    $t4, ($v1)
/* 0C2344 800C1744 90AE0000 */  lbu   $t6, ($a1)
/* 0C2348 800C1748 01827821 */  addu  $t7, $t4, $v0
/* 0C234C 800C174C A1EE0025 */  sb    $t6, 0x25($t7)
/* 0C2350 800C1750 8C780000 */  lw    $t8, ($v1)
/* 0C2354 800C1754 90D90000 */  lbu   $t9, ($a2)
/* 0C2358 800C1758 03026821 */  addu  $t5, $t8, $v0
/* 0C235C 800C175C A1B90026 */  sb    $t9, 0x26($t5)
/* 0C2360 800C1760 8C6C0000 */  lw    $t4, ($v1)
/* 0C2364 800C1764 00000000 */  nop   
/* 0C2368 800C1768 01827021 */  addu  $t6, $t4, $v0
/* 0C236C 800C176C 24420028 */  addiu $v0, $v0, 0x28
/* 0C2370 800C1770 1449FFBF */  bne   $v0, $t1, .L800C1670
/* 0C2374 800C1774 A1C80027 */   sb    $t0, 0x27($t6)
/* 0C2378 800C1778 24630004 */  addiu $v1, $v1, 4
/* 0C237C 800C177C 006A082B */  sltu  $at, $v1, $t2
/* 0C2380 800C1780 1420FFBB */  bnez  $at, .L800C1670
/* 0C2384 800C1784 00001025 */   move  $v0, $zero
/* 0C2388 800C1788 3C03800E */  lui   $v1, %hi(sTransitionVtx) # $v1, 0x800e
/* 0C238C 800C178C 3C0A800E */  lui   $t2, %hi(sTransitionTris) # $t2, 0x800e
/* 0C2390 800C1790 254A31C8 */  addiu $t2, %lo(sTransitionTris) # addiu $t2, $t2, 0x31c8
/* 0C2394 800C1794 246331C0 */  addiu $v1, %lo(sTransitionVtx) # addiu $v1, $v1, 0x31c0
/* 0C2398 800C1798 24090009 */  li    $t1, 9
/* 0C239C 800C179C 2408000A */  li    $t0, 10
.L800C17A0:
/* 0C23A0 800C17A0 8C6F0000 */  lw    $t7, ($v1)
/* 0C23A4 800C17A4 24070001 */  li    $a3, 1
/* 0C23A8 800C17A8 A1E000C7 */  sb    $zero, 0xc7($t7)
/* 0C23AC 800C17AC 8C780000 */  lw    $t8, ($v1)
/* 0C23B0 800C17B0 00000000 */  nop   
/* 0C23B4 800C17B4 A300022F */  sb    $zero, 0x22f($t8)
.L800C17B8:
/* 0C23B8 800C17B8 0007C840 */  sll   $t9, $a3, 1
/* 0C23BC 800C17BC 03280019 */  multu $t9, $t0
/* 0C23C0 800C17C0 24F80001 */  addiu $t8, $a3, 1
/* 0C23C4 800C17C4 0018C840 */  sll   $t9, $t8, 1
/* 0C23C8 800C17C8 24F80002 */  addiu $t8, $a3, 2
/* 0C23CC 800C17CC 8C6D0000 */  lw    $t5, ($v1)
/* 0C23D0 800C17D0 00001012 */  mflo  $v0
/* 0C23D4 800C17D4 01A26021 */  addu  $t4, $t5, $v0
/* 0C23D8 800C17D8 A18000C7 */  sb    $zero, 0xc7($t4)
/* 0C23DC 800C17DC 03280019 */  multu $t9, $t0
/* 0C23E0 800C17E0 0018C840 */  sll   $t9, $t8, 1
/* 0C23E4 800C17E4 8C6E0000 */  lw    $t6, ($v1)
/* 0C23E8 800C17E8 24F80003 */  addiu $t8, $a3, 3
/* 0C23EC 800C17EC 01C27821 */  addu  $t7, $t6, $v0
/* 0C23F0 800C17F0 A1E0022F */  sb    $zero, 0x22f($t7)
/* 0C23F4 800C17F4 8C6D0000 */  lw    $t5, ($v1)
/* 0C23F8 800C17F8 24E70004 */  addiu $a3, $a3, 4
/* 0C23FC 800C17FC 00002012 */  mflo  $a0
/* 0C2400 800C1800 01A46021 */  addu  $t4, $t5, $a0
/* 0C2404 800C1804 A18000C7 */  sb    $zero, 0xc7($t4)
/* 0C2408 800C1808 03280019 */  multu $t9, $t0
/* 0C240C 800C180C 8C6E0000 */  lw    $t6, ($v1)
/* 0C2410 800C1810 0018C840 */  sll   $t9, $t8, 1
/* 0C2414 800C1814 01C47821 */  addu  $t7, $t6, $a0
/* 0C2418 800C1818 A1E0022F */  sb    $zero, 0x22f($t7)
/* 0C241C 800C181C 8C6D0000 */  lw    $t5, ($v1)
/* 0C2420 800C1820 00002812 */  mflo  $a1
/* 0C2424 800C1824 01A56021 */  addu  $t4, $t5, $a1
/* 0C2428 800C1828 A18000C7 */  sb    $zero, 0xc7($t4)
/* 0C242C 800C182C 03280019 */  multu $t9, $t0
/* 0C2430 800C1830 8C6E0000 */  lw    $t6, ($v1)
/* 0C2434 800C1834 00000000 */  nop   
/* 0C2438 800C1838 01C57821 */  addu  $t7, $t6, $a1
/* 0C243C 800C183C A1E0022F */  sb    $zero, 0x22f($t7)
/* 0C2440 800C1840 8C6D0000 */  lw    $t5, ($v1)
/* 0C2444 800C1844 00003012 */  mflo  $a2
/* 0C2448 800C1848 01A66021 */  addu  $t4, $t5, $a2
/* 0C244C 800C184C A18000C7 */  sb    $zero, 0xc7($t4)
/* 0C2450 800C1850 8C6E0000 */  lw    $t6, ($v1)
/* 0C2454 800C1854 00000000 */  nop   
/* 0C2458 800C1858 01C67821 */  addu  $t7, $t6, $a2
/* 0C245C 800C185C 14E9FFD6 */  bne   $a3, $t1, .L800C17B8
/* 0C2460 800C1860 A1E0022F */   sb    $zero, 0x22f($t7)
/* 0C2464 800C1864 24630004 */  addiu $v1, $v1, 4
/* 0C2468 800C1868 006A082B */  sltu  $at, $v1, $t2
/* 0C246C 800C186C 1420FFCC */  bnez  $at, .L800C17A0
/* 0C2470 800C1870 00000000 */   nop   
/* 0C2474 800C1874 3C014370 */  li    $at, 0x43700000 # 240.000000
/* 0C2478 800C1878 3C12800E */  lui   $s2, %hi(sTransitionTris) # $s2, 0x800e
/* 0C247C 800C187C 4481A000 */  mtc1  $at, $f20
/* 0C2480 800C1880 0000A825 */  move  $s5, $zero
/* 0C2484 800C1884 265231C8 */  addiu $s2, %lo(sTransitionTris) # addiu $s2, $s2, 0x31c8
/* 0C2488 800C1888 0000A025 */  move  $s4, $zero
/* 0C248C 800C188C 2410FFF0 */  li    $s0, -16
.L800C1890:
/* 0C2490 800C1890 00159C00 */  sll   $s3, $s5, 0x10
/* 0C2494 800C1894 0013C403 */  sra   $t8, $s3, 0x10
/* 0C2498 800C1898 00182400 */  sll   $a0, $t8, 0x10
/* 0C249C 800C189C 0004CC03 */  sra   $t9, $a0, 0x10
/* 0C24A0 800C18A0 03202025 */  move  $a0, $t9
/* 0C24A4 800C18A4 0C01C1F1 */  jal   sins_f
/* 0C24A8 800C18A8 03009825 */   move  $s3, $t8
/* 0C24AC 800C18AC 46140102 */  mul.s $f4, $f0, $f20
/* 0C24B0 800C18B0 00132400 */  sll   $a0, $s3, 0x10
/* 0C24B4 800C18B4 00047C03 */  sra   $t7, $a0, 0x10
/* 0C24B8 800C18B8 01E02025 */  move  $a0, $t7
/* 0C24BC 800C18BC 444DF800 */  cfc1  $t5, $31
/* 0C24C0 800C18C0 00000000 */  nop   
/* 0C24C4 800C18C4 35A10003 */  ori   $at, $t5, 3
/* 0C24C8 800C18C8 38210002 */  xori  $at, $at, 2
/* 0C24CC 800C18CC 44C1F800 */  ctc1  $at, $31
/* 0C24D0 800C18D0 00000000 */  nop   
/* 0C24D4 800C18D4 460021A4 */  cvt.w.s $f6, $f4
/* 0C24D8 800C18D8 44113000 */  mfc1  $s1, $f6
/* 0C24DC 800C18DC 44CDF800 */  ctc1  $t5, $31
/* 0C24E0 800C18E0 00116400 */  sll   $t4, $s1, 0x10
/* 0C24E4 800C18E4 0C01C1FE */  jal   coss_f
/* 0C24E8 800C18E8 000C8C03 */   sra   $s1, $t4, 0x10
/* 0C24EC 800C18EC 3C014334 */  li    $at, 0x43340000 # 180.000000
/* 0C24F0 800C18F0 44814000 */  mtc1  $at, $f8
/* 0C24F4 800C18F4 00141840 */  sll   $v1, $s4, 1
/* 0C24F8 800C18F8 46080282 */  mul.s $f10, $f0, $f8
/* 0C24FC 800C18FC 0003C080 */  sll   $t8, $v1, 2
/* 0C2500 800C1900 0303C021 */  addu  $t8, $t8, $v1
/* 0C2504 800C1904 3C02800E */  lui   $v0, %hi(sTransitionVtx) # $v0, 0x800e
/* 0C2508 800C1908 4459F800 */  cfc1  $t9, $31
/* 0C250C 800C190C 244231C0 */  addiu $v0, %lo(sTransitionVtx) # addiu $v0, $v0, 0x31c0
/* 0C2510 800C1910 37210003 */  ori   $at, $t9, 3
/* 0C2514 800C1914 38210002 */  xori  $at, $at, 2
/* 0C2518 800C1918 44C1F800 */  ctc1  $at, $31
/* 0C251C 800C191C 00181840 */  sll   $v1, $t8, 1
/* 0C2520 800C1920 46005424 */  cvt.w.s $f16, $f10
/* 0C2524 800C1924 00112823 */  negu  $a1, $s1
/* 0C2528 800C1928 44048000 */  mfc1  $a0, $f16
/* 0C252C 800C192C 44D9F800 */  ctc1  $t9, $31
/* 0C2530 800C1930 00046C00 */  sll   $t5, $a0, 0x10
/* 0C2534 800C1934 000D2403 */  sra   $a0, $t5, 0x10
.L800C1938:
/* 0C2538 800C1938 8C4E0000 */  lw    $t6, ($v0)
/* 0C253C 800C193C 24420004 */  addiu $v0, $v0, 4
/* 0C2540 800C1940 01C37821 */  addu  $t7, $t6, $v1
/* 0C2544 800C1944 A5F10000 */  sh    $s1, ($t7)
/* 0C2548 800C1948 8C58FFFC */  lw    $t8, -4($v0)
/* 0C254C 800C194C 00000000 */  nop   
/* 0C2550 800C1950 0303C821 */  addu  $t9, $t8, $v1
/* 0C2554 800C1954 A7240002 */  sh    $a0, 2($t9)
/* 0C2558 800C1958 8C4DFFFC */  lw    $t5, -4($v0)
/* 0C255C 800C195C 00000000 */  nop   
/* 0C2560 800C1960 01A36021 */  addu  $t4, $t5, $v1
/* 0C2564 800C1964 A5900004 */  sh    $s0, 4($t4)
/* 0C2568 800C1968 8C4EFFFC */  lw    $t6, -4($v0)
/* 0C256C 800C196C 00000000 */  nop   
/* 0C2570 800C1970 01C37821 */  addu  $t7, $t6, $v1
/* 0C2574 800C1974 A5F0000E */  sh    $s0, 0xe($t7)
/* 0C2578 800C1978 8C58FFFC */  lw    $t8, -4($v0)
/* 0C257C 800C197C 00000000 */  nop   
/* 0C2580 800C1980 0303C821 */  addu  $t9, $t8, $v1
/* 0C2584 800C1984 A73000B8 */  sh    $s0, 0xb8($t9)
/* 0C2588 800C1988 8C4DFFFC */  lw    $t5, -4($v0)
/* 0C258C 800C198C 00000000 */  nop   
/* 0C2590 800C1990 01A36021 */  addu  $t4, $t5, $v1
/* 0C2594 800C1994 A59000C2 */  sh    $s0, 0xc2($t4)
/* 0C2598 800C1998 8C4EFFFC */  lw    $t6, -4($v0)
/* 0C259C 800C199C 00000000 */  nop   
/* 0C25A0 800C19A0 01C37821 */  addu  $t7, $t6, $v1
/* 0C25A4 800C19A4 A5E50168 */  sh    $a1, 0x168($t7)
/* 0C25A8 800C19A8 8C58FFFC */  lw    $t8, -4($v0)
/* 0C25AC 800C19AC 00000000 */  nop   
/* 0C25B0 800C19B0 0303C821 */  addu  $t9, $t8, $v1
/* 0C25B4 800C19B4 A724016A */  sh    $a0, 0x16a($t9)
/* 0C25B8 800C19B8 8C4DFFFC */  lw    $t5, -4($v0)
/* 0C25BC 800C19BC 00000000 */  nop   
/* 0C25C0 800C19C0 01A36021 */  addu  $t4, $t5, $v1
/* 0C25C4 800C19C4 A590016C */  sh    $s0, 0x16c($t4)
/* 0C25C8 800C19C8 8C4EFFFC */  lw    $t6, -4($v0)
/* 0C25CC 800C19CC 00000000 */  nop   
/* 0C25D0 800C19D0 01C37821 */  addu  $t7, $t6, $v1
/* 0C25D4 800C19D4 A5F00176 */  sh    $s0, 0x176($t7)
/* 0C25D8 800C19D8 8C58FFFC */  lw    $t8, -4($v0)
/* 0C25DC 800C19DC 00000000 */  nop   
/* 0C25E0 800C19E0 0303C821 */  addu  $t9, $t8, $v1
/* 0C25E4 800C19E4 A7300220 */  sh    $s0, 0x220($t9)
/* 0C25E8 800C19E8 8C4DFFFC */  lw    $t5, -4($v0)
/* 0C25EC 800C19EC 00000000 */  nop   
/* 0C25F0 800C19F0 01A36021 */  addu  $t4, $t5, $v1
/* 0C25F4 800C19F4 1452FFD0 */  bne   $v0, $s2, .L800C1938
/* 0C25F8 800C19F8 A590022A */   sh    $s0, 0x22a($t4)
/* 0C25FC 800C19FC 26940001 */  addiu $s4, $s4, 1
/* 0C2600 800C1A00 2A810009 */  slti  $at, $s4, 9
/* 0C2604 800C1A04 1420FFA2 */  bnez  $at, .L800C1890
/* 0C2608 800C1A08 26B51000 */   addiu $s5, $s5, 0x1000
/* 0C260C 800C1A0C 8FAE0038 */  lw    $t6, 0x38($sp)
/* 0C2610 800C1A10 3C03800E */  lui   $v1, %hi(sTransitionTris) # $v1, 0x800e
/* 0C2614 800C1A14 91CF0000 */  lbu   $t7, ($t6)
/* 0C2618 800C1A18 246331C8 */  addiu $v1, %lo(sTransitionTris) # addiu $v1, $v1, 0x31c8
/* 0C261C 800C1A1C 31F80080 */  andi  $t8, $t7, 0x80
/* 0C2620 800C1A20 1300001D */  beqz  $t8, .L800C1A98
/* 0C2624 800C1A24 3C06800E */   lui   $a2, %hi(sTransitionTaskNum) # $a2, 0x800e
/* 0C2628 800C1A28 3C014334 */  li    $at, 0x43340000 # 180.000000
/* 0C262C 800C1A2C 3C19800E */  lui   $t9, %hi(sTransitionFadeTimer) # $t9, 0x800e
/* 0C2630 800C1A30 44801000 */  mtc1  $zero, $f2
/* 0C2634 800C1A34 973931B0 */  lhu   $t9, %lo(sTransitionFadeTimer)($t9)
/* 0C2638 800C1A38 44816000 */  mtc1  $at, $f12
/* 0C263C 800C1A3C 3C018013 */  lui   $at, %hi(D_8012A758) # $at, 0x8013
/* 0C2640 800C1A40 44999000 */  mtc1  $t9, $f18
/* 0C2644 800C1A44 E422A758 */  swc1  $f2, %lo(D_8012A758)($at)
/* 0C2648 800C1A48 3C018013 */  lui   $at, %hi(D_8012A75C) # $at, 0x8013
/* 0C264C 800C1A4C E422A75C */  swc1  $f2, %lo(D_8012A75C)($at)
/* 0C2650 800C1A50 07210005 */  bgez  $t9, .L800C1A68
/* 0C2654 800C1A54 46809020 */   cvt.s.w $f0, $f18
/* 0C2658 800C1A58 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0C265C 800C1A5C 44812000 */  mtc1  $at, $f4
/* 0C2660 800C1A60 00000000 */  nop   
/* 0C2664 800C1A64 46040000 */  add.s $f0, $f0, $f4
.L800C1A68:
/* 0C2668 800C1A68 00000000 */  nop   
/* 0C266C 800C1A6C 4600A183 */  div.s $f6, $f20, $f0
/* 0C2670 800C1A70 3C018013 */  lui   $at, %hi(D_8012A760) # $at, 0x8013
/* 0C2674 800C1A74 46006203 */  div.s $f8, $f12, $f0
/* 0C2678 800C1A78 E426A760 */  swc1  $f6, %lo(D_8012A760)($at)
/* 0C267C 800C1A7C 3C018013 */  lui   $at, %hi(D_8012A764) # $at, 0x8013
/* 0C2680 800C1A80 E428A764 */  swc1  $f8, %lo(D_8012A764)($at)
/* 0C2684 800C1A84 3C018013 */  lui   $at, %hi(D_8012A768) # $at, 0x8013
/* 0C2688 800C1A88 E434A768 */  swc1  $f20, %lo(D_8012A768)($at)
/* 0C268C 800C1A8C 3C018013 */  lui   $at, %hi(D_8012A76C) # $at, 0x8013
/* 0C2690 800C1A90 1000001E */  b     .L800C1B0C
/* 0C2694 800C1A94 E42CA76C */   swc1  $f12, %lo(D_8012A76C)($at)
.L800C1A98:
/* 0C2698 800C1A98 3C014334 */  li    $at, 0x43340000 # 180.000000
/* 0C269C 800C1A9C 3C0D800E */  lui   $t5, %hi(sTransitionFadeTimer) # $t5, 0x800e
/* 0C26A0 800C1AA0 44816000 */  mtc1  $at, $f12
/* 0C26A4 800C1AA4 95AD31B0 */  lhu   $t5, %lo(sTransitionFadeTimer)($t5)
/* 0C26A8 800C1AA8 3C018013 */  lui   $at, %hi(D_8012A758) # $at, 0x8013
/* 0C26AC 800C1AAC 448D5000 */  mtc1  $t5, $f10
/* 0C26B0 800C1AB0 E434A758 */  swc1  $f20, %lo(D_8012A758)($at)
/* 0C26B4 800C1AB4 44801000 */  mtc1  $zero, $f2
/* 0C26B8 800C1AB8 3C018013 */  lui   $at, %hi(D_8012A75C) # $at, 0x8013
/* 0C26BC 800C1ABC E42CA75C */  swc1  $f12, %lo(D_8012A75C)($at)
/* 0C26C0 800C1AC0 05A10005 */  bgez  $t5, .L800C1AD8
/* 0C26C4 800C1AC4 46805020 */   cvt.s.w $f0, $f10
/* 0C26C8 800C1AC8 3C014F80 */  li    $at, 0x4F800000 # 4294967296.000000
/* 0C26CC 800C1ACC 44818000 */  mtc1  $at, $f16
/* 0C26D0 800C1AD0 00000000 */  nop   
/* 0C26D4 800C1AD4 46100000 */  add.s $f0, $f0, $f16
.L800C1AD8:
/* 0C26D8 800C1AD8 4600A487 */  neg.s $f18, $f20
/* 0C26DC 800C1ADC 00000000 */  nop   
/* 0C26E0 800C1AE0 46009103 */  div.s $f4, $f18, $f0
/* 0C26E4 800C1AE4 46006187 */  neg.s $f6, $f12
/* 0C26E8 800C1AE8 3C018013 */  lui   $at, %hi(D_8012A760) # $at, 0x8013
/* 0C26EC 800C1AEC 46003203 */  div.s $f8, $f6, $f0
/* 0C26F0 800C1AF0 E424A760 */  swc1  $f4, %lo(D_8012A760)($at)
/* 0C26F4 800C1AF4 3C018013 */  lui   $at, %hi(D_8012A764) # $at, 0x8013
/* 0C26F8 800C1AF8 E428A764 */  swc1  $f8, %lo(D_8012A764)($at)
/* 0C26FC 800C1AFC 3C018013 */  lui   $at, %hi(D_8012A768) # $at, 0x8013
/* 0C2700 800C1B00 E422A768 */  swc1  $f2, %lo(D_8012A768)($at)
/* 0C2704 800C1B04 3C018013 */  lui   $at, %hi(D_8012A76C) # $at, 0x8013
/* 0C2708 800C1B08 E422A76C */  swc1  $f2, %lo(D_8012A76C)($at)
.L800C1B0C:
/* 0C270C 800C1B0C 24C631D0 */  addiu $a2, %lo(sTransitionTaskNum) # addiu $a2, $a2, 0x31d0
/* 0C2710 800C1B10 24050400 */  li    $a1, 1024
/* 0C2714 800C1B14 24040040 */  li    $a0, 64
/* 0C2718 800C1B18 00001025 */  move  $v0, $zero
.L800C1B1C:
/* 0C271C 800C1B1C 8C6C0000 */  lw    $t4, ($v1)
/* 0C2720 800C1B20 00000000 */  nop   
/* 0C2724 800C1B24 01827021 */  addu  $t6, $t4, $v0
/* 0C2728 800C1B28 A1C40000 */  sb    $a0, ($t6)
/* 0C272C 800C1B2C 8C6F0000 */  lw    $t7, ($v1)
/* 0C2730 800C1B30 00000000 */  nop   
/* 0C2734 800C1B34 01E2C021 */  addu  $t8, $t7, $v0
/* 0C2738 800C1B38 A7000004 */  sh    $zero, 4($t8)
/* 0C273C 800C1B3C 8C790000 */  lw    $t9, ($v1)
/* 0C2740 800C1B40 00000000 */  nop   
/* 0C2744 800C1B44 03226821 */  addu  $t5, $t9, $v0
/* 0C2748 800C1B48 A5A00006 */  sh    $zero, 6($t5)
/* 0C274C 800C1B4C 8C6C0000 */  lw    $t4, ($v1)
/* 0C2750 800C1B50 00000000 */  nop   
/* 0C2754 800C1B54 01827021 */  addu  $t6, $t4, $v0
/* 0C2758 800C1B58 A5C00008 */  sh    $zero, 8($t6)
/* 0C275C 800C1B5C 8C6F0000 */  lw    $t7, ($v1)
/* 0C2760 800C1B60 00000000 */  nop   
/* 0C2764 800C1B64 01E2C021 */  addu  $t8, $t7, $v0
/* 0C2768 800C1B68 A700000A */  sh    $zero, 0xa($t8)
/* 0C276C 800C1B6C 8C790000 */  lw    $t9, ($v1)
/* 0C2770 800C1B70 00000000 */  nop   
/* 0C2774 800C1B74 03226821 */  addu  $t5, $t9, $v0
/* 0C2778 800C1B78 A5A0000C */  sh    $zero, 0xc($t5)
/* 0C277C 800C1B7C 8C6C0000 */  lw    $t4, ($v1)
/* 0C2780 800C1B80 00000000 */  nop   
/* 0C2784 800C1B84 01827021 */  addu  $t6, $t4, $v0
/* 0C2788 800C1B88 A5C0000E */  sh    $zero, 0xe($t6)
/* 0C278C 800C1B8C 8C6F0000 */  lw    $t7, ($v1)
/* 0C2790 800C1B90 00000000 */  nop   
/* 0C2794 800C1B94 01E2C021 */  addu  $t8, $t7, $v0
/* 0C2798 800C1B98 A3040010 */  sb    $a0, 0x10($t8)
/* 0C279C 800C1B9C 8C790000 */  lw    $t9, ($v1)
/* 0C27A0 800C1BA0 00000000 */  nop   
/* 0C27A4 800C1BA4 03226821 */  addu  $t5, $t9, $v0
/* 0C27A8 800C1BA8 A5A00014 */  sh    $zero, 0x14($t5)
/* 0C27AC 800C1BAC 8C6C0000 */  lw    $t4, ($v1)
/* 0C27B0 800C1BB0 00000000 */  nop   
/* 0C27B4 800C1BB4 01827021 */  addu  $t6, $t4, $v0
/* 0C27B8 800C1BB8 A5C00016 */  sh    $zero, 0x16($t6)
/* 0C27BC 800C1BBC 8C6F0000 */  lw    $t7, ($v1)
/* 0C27C0 800C1BC0 00000000 */  nop   
/* 0C27C4 800C1BC4 01E2C021 */  addu  $t8, $t7, $v0
/* 0C27C8 800C1BC8 A7000018 */  sh    $zero, 0x18($t8)
/* 0C27CC 800C1BCC 8C790000 */  lw    $t9, ($v1)
/* 0C27D0 800C1BD0 00000000 */  nop   
/* 0C27D4 800C1BD4 03226821 */  addu  $t5, $t9, $v0
/* 0C27D8 800C1BD8 A5A0001A */  sh    $zero, 0x1a($t5)
/* 0C27DC 800C1BDC 8C6C0000 */  lw    $t4, ($v1)
/* 0C27E0 800C1BE0 00000000 */  nop   
/* 0C27E4 800C1BE4 01827021 */  addu  $t6, $t4, $v0
/* 0C27E8 800C1BE8 A5C0001C */  sh    $zero, 0x1c($t6)
/* 0C27EC 800C1BEC 8C6F0000 */  lw    $t7, ($v1)
/* 0C27F0 800C1BF0 00000000 */  nop   
/* 0C27F4 800C1BF4 01E2C021 */  addu  $t8, $t7, $v0
/* 0C27F8 800C1BF8 A700001E */  sh    $zero, 0x1e($t8)
/* 0C27FC 800C1BFC 8C790000 */  lw    $t9, ($v1)
/* 0C2800 800C1C00 00000000 */  nop   
/* 0C2804 800C1C04 03226821 */  addu  $t5, $t9, $v0
/* 0C2808 800C1C08 A1A40020 */  sb    $a0, 0x20($t5)
/* 0C280C 800C1C0C 8C6C0000 */  lw    $t4, ($v1)
/* 0C2810 800C1C10 00000000 */  nop   
/* 0C2814 800C1C14 01827021 */  addu  $t6, $t4, $v0
/* 0C2818 800C1C18 A5C00024 */  sh    $zero, 0x24($t6)
/* 0C281C 800C1C1C 8C6F0000 */  lw    $t7, ($v1)
/* 0C2820 800C1C20 00000000 */  nop   
/* 0C2824 800C1C24 01E2C021 */  addu  $t8, $t7, $v0
/* 0C2828 800C1C28 A7000026 */  sh    $zero, 0x26($t8)
/* 0C282C 800C1C2C 8C790000 */  lw    $t9, ($v1)
/* 0C2830 800C1C30 00000000 */  nop   
/* 0C2834 800C1C34 03226821 */  addu  $t5, $t9, $v0
/* 0C2838 800C1C38 A5A00028 */  sh    $zero, 0x28($t5)
/* 0C283C 800C1C3C 8C6C0000 */  lw    $t4, ($v1)
/* 0C2840 800C1C40 00000000 */  nop   
/* 0C2844 800C1C44 01827021 */  addu  $t6, $t4, $v0
/* 0C2848 800C1C48 A5C0002A */  sh    $zero, 0x2a($t6)
/* 0C284C 800C1C4C 8C6F0000 */  lw    $t7, ($v1)
/* 0C2850 800C1C50 00000000 */  nop   
/* 0C2854 800C1C54 01E2C021 */  addu  $t8, $t7, $v0
/* 0C2858 800C1C58 A700002C */  sh    $zero, 0x2c($t8)
/* 0C285C 800C1C5C 8C790000 */  lw    $t9, ($v1)
/* 0C2860 800C1C60 00000000 */  nop   
/* 0C2864 800C1C64 03226821 */  addu  $t5, $t9, $v0
/* 0C2868 800C1C68 A5A0002E */  sh    $zero, 0x2e($t5)
/* 0C286C 800C1C6C 8C6C0000 */  lw    $t4, ($v1)
/* 0C2870 800C1C70 00000000 */  nop   
/* 0C2874 800C1C74 01827021 */  addu  $t6, $t4, $v0
/* 0C2878 800C1C78 A1C40030 */  sb    $a0, 0x30($t6)
/* 0C287C 800C1C7C 8C6F0000 */  lw    $t7, ($v1)
/* 0C2880 800C1C80 00000000 */  nop   
/* 0C2884 800C1C84 01E2C021 */  addu  $t8, $t7, $v0
/* 0C2888 800C1C88 A7000034 */  sh    $zero, 0x34($t8)
/* 0C288C 800C1C8C 8C790000 */  lw    $t9, ($v1)
/* 0C2890 800C1C90 00000000 */  nop   
/* 0C2894 800C1C94 03226821 */  addu  $t5, $t9, $v0
/* 0C2898 800C1C98 A5A00036 */  sh    $zero, 0x36($t5)
/* 0C289C 800C1C9C 8C6C0000 */  lw    $t4, ($v1)
/* 0C28A0 800C1CA0 00000000 */  nop   
/* 0C28A4 800C1CA4 01827021 */  addu  $t6, $t4, $v0
/* 0C28A8 800C1CA8 A5C00038 */  sh    $zero, 0x38($t6)
/* 0C28AC 800C1CAC 8C6F0000 */  lw    $t7, ($v1)
/* 0C28B0 800C1CB0 00000000 */  nop   
/* 0C28B4 800C1CB4 01E2C021 */  addu  $t8, $t7, $v0
/* 0C28B8 800C1CB8 A700003A */  sh    $zero, 0x3a($t8)
/* 0C28BC 800C1CBC 8C790000 */  lw    $t9, ($v1)
/* 0C28C0 800C1CC0 00000000 */  nop   
/* 0C28C4 800C1CC4 03226821 */  addu  $t5, $t9, $v0
/* 0C28C8 800C1CC8 A5A0003C */  sh    $zero, 0x3c($t5)
/* 0C28CC 800C1CCC 8C6C0000 */  lw    $t4, ($v1)
/* 0C28D0 800C1CD0 00000000 */  nop   
/* 0C28D4 800C1CD4 01827021 */  addu  $t6, $t4, $v0
/* 0C28D8 800C1CD8 24420040 */  addiu $v0, $v0, 0x40
/* 0C28DC 800C1CDC 1445FF8F */  bne   $v0, $a1, .L800C1B1C
/* 0C28E0 800C1CE0 A5C0003E */   sh    $zero, 0x3e($t6)
/* 0C28E4 800C1CE4 24630004 */  addiu $v1, $v1, 4
/* 0C28E8 800C1CE8 0066082B */  sltu  $at, $v1, $a2
/* 0C28EC 800C1CEC 1420FF8B */  bnez  $at, .L800C1B1C
/* 0C28F0 800C1CF0 00001025 */   move  $v0, $zero
/* 0C28F4 800C1CF4 3C0A800E */  lui   $t2, %hi(sTransitionTaskNum) # $t2, 0x800e
/* 0C28F8 800C1CF8 254A31D0 */  addiu $t2, %lo(sTransitionTaskNum) # addiu $t2, $t2, 0x31d0
/* 0C28FC 800C1CFC 0000A025 */  move  $s4, $zero
/* 0C2900 800C1D00 240B0008 */  li    $t3, 8
/* 0C2904 800C1D04 00142040 */  sll   $a0, $s4, 1
.L800C1D08:
/* 0C2908 800C1D08 3C02800E */  lui   $v0, %hi(sTransitionTris) # $v0, 0x800e
/* 0C290C 800C1D0C 244231C8 */  addiu $v0, %lo(sTransitionTris) # addiu $v0, $v0, 0x31c8
/* 0C2910 800C1D10 00041900 */  sll   $v1, $a0, 4
/* 0C2914 800C1D14 24860001 */  addiu $a2, $a0, 1
/* 0C2918 800C1D18 24850003 */  addiu $a1, $a0, 3
/* 0C291C 800C1D1C 24880002 */  addiu $t0, $a0, 2
.L800C1D20:
/* 0C2920 800C1D20 8C4F0000 */  lw    $t7, ($v0)
/* 0C2924 800C1D24 24420004 */  addiu $v0, $v0, 4
/* 0C2928 800C1D28 01E3C021 */  addu  $t8, $t7, $v1
/* 0C292C 800C1D2C A3040001 */  sb    $a0, 1($t8)
/* 0C2930 800C1D30 8C59FFFC */  lw    $t9, -4($v0)
/* 0C2934 800C1D34 00000000 */  nop   
/* 0C2938 800C1D38 03236821 */  addu  $t5, $t9, $v1
/* 0C293C 800C1D3C A1A60002 */  sb    $a2, 2($t5)
/* 0C2940 800C1D40 8C4CFFFC */  lw    $t4, -4($v0)
/* 0C2944 800C1D44 00000000 */  nop   
/* 0C2948 800C1D48 01837021 */  addu  $t6, $t4, $v1
/* 0C294C 800C1D4C A1C50003 */  sb    $a1, 3($t6)
/* 0C2950 800C1D50 8C4FFFFC */  lw    $t7, -4($v0)
/* 0C2954 800C1D54 00000000 */  nop   
/* 0C2958 800C1D58 01E3C021 */  addu  $t8, $t7, $v1
/* 0C295C 800C1D5C A3040011 */  sb    $a0, 0x11($t8)
/* 0C2960 800C1D60 8C59FFFC */  lw    $t9, -4($v0)
/* 0C2964 800C1D64 00000000 */  nop   
/* 0C2968 800C1D68 03236821 */  addu  $t5, $t9, $v1
/* 0C296C 800C1D6C A1A50012 */  sb    $a1, 0x12($t5)
/* 0C2970 800C1D70 8C4CFFFC */  lw    $t4, -4($v0)
/* 0C2974 800C1D74 00000000 */  nop   
/* 0C2978 800C1D78 01837021 */  addu  $t6, $t4, $v1
/* 0C297C 800C1D7C A1C80013 */  sb    $t0, 0x13($t6)
/* 0C2980 800C1D80 8C4FFFFC */  lw    $t7, -4($v0)
/* 0C2984 800C1D84 00000000 */  nop   
/* 0C2988 800C1D88 01E3C021 */  addu  $t8, $t7, $v1
/* 0C298C 800C1D8C A3040101 */  sb    $a0, 0x101($t8)
/* 0C2990 800C1D90 8C59FFFC */  lw    $t9, -4($v0)
/* 0C2994 800C1D94 00000000 */  nop   
/* 0C2998 800C1D98 03236821 */  addu  $t5, $t9, $v1
/* 0C299C 800C1D9C A1A60102 */  sb    $a2, 0x102($t5)
/* 0C29A0 800C1DA0 8C4CFFFC */  lw    $t4, -4($v0)
/* 0C29A4 800C1DA4 00000000 */  nop   
/* 0C29A8 800C1DA8 01837021 */  addu  $t6, $t4, $v1
/* 0C29AC 800C1DAC A1C50103 */  sb    $a1, 0x103($t6)
/* 0C29B0 800C1DB0 8C4FFFFC */  lw    $t7, -4($v0)
/* 0C29B4 800C1DB4 00000000 */  nop   
/* 0C29B8 800C1DB8 01E3C021 */  addu  $t8, $t7, $v1
/* 0C29BC 800C1DBC A3040111 */  sb    $a0, 0x111($t8)
/* 0C29C0 800C1DC0 8C59FFFC */  lw    $t9, -4($v0)
/* 0C29C4 800C1DC4 00000000 */  nop   
/* 0C29C8 800C1DC8 03236821 */  addu  $t5, $t9, $v1
/* 0C29CC 800C1DCC A1A50112 */  sb    $a1, 0x112($t5)
/* 0C29D0 800C1DD0 8C4CFFFC */  lw    $t4, -4($v0)
/* 0C29D4 800C1DD4 00000000 */  nop   
/* 0C29D8 800C1DD8 01837021 */  addu  $t6, $t4, $v1
/* 0C29DC 800C1DDC A1C80113 */  sb    $t0, 0x113($t6)
/* 0C29E0 800C1DE0 8C4FFFFC */  lw    $t7, -4($v0)
/* 0C29E4 800C1DE4 00000000 */  nop   
/* 0C29E8 800C1DE8 01E3C021 */  addu  $t8, $t7, $v1
/* 0C29EC 800C1DEC A3040201 */  sb    $a0, 0x201($t8)
/* 0C29F0 800C1DF0 8C59FFFC */  lw    $t9, -4($v0)
/* 0C29F4 800C1DF4 00000000 */  nop   
/* 0C29F8 800C1DF8 03236821 */  addu  $t5, $t9, $v1
/* 0C29FC 800C1DFC A1A60202 */  sb    $a2, 0x202($t5)
/* 0C2A00 800C1E00 8C4CFFFC */  lw    $t4, -4($v0)
/* 0C2A04 800C1E04 00000000 */  nop   
/* 0C2A08 800C1E08 01837021 */  addu  $t6, $t4, $v1
/* 0C2A0C 800C1E0C A1C50203 */  sb    $a1, 0x203($t6)
/* 0C2A10 800C1E10 8C4FFFFC */  lw    $t7, -4($v0)
/* 0C2A14 800C1E14 00000000 */  nop   
/* 0C2A18 800C1E18 01E3C021 */  addu  $t8, $t7, $v1
/* 0C2A1C 800C1E1C A3040211 */  sb    $a0, 0x211($t8)
/* 0C2A20 800C1E20 8C59FFFC */  lw    $t9, -4($v0)
/* 0C2A24 800C1E24 00000000 */  nop   
/* 0C2A28 800C1E28 03236821 */  addu  $t5, $t9, $v1
/* 0C2A2C 800C1E2C A1A50212 */  sb    $a1, 0x212($t5)
/* 0C2A30 800C1E30 8C4CFFFC */  lw    $t4, -4($v0)
/* 0C2A34 800C1E34 00000000 */  nop   
/* 0C2A38 800C1E38 01837021 */  addu  $t6, $t4, $v1
/* 0C2A3C 800C1E3C A1C80213 */  sb    $t0, 0x213($t6)
/* 0C2A40 800C1E40 8C4FFFFC */  lw    $t7, -4($v0)
/* 0C2A44 800C1E44 00000000 */  nop   
/* 0C2A48 800C1E48 01E3C021 */  addu  $t8, $t7, $v1
/* 0C2A4C 800C1E4C A3040301 */  sb    $a0, 0x301($t8)
/* 0C2A50 800C1E50 8C59FFFC */  lw    $t9, -4($v0)
/* 0C2A54 800C1E54 00000000 */  nop   
/* 0C2A58 800C1E58 03236821 */  addu  $t5, $t9, $v1
/* 0C2A5C 800C1E5C A1A60302 */  sb    $a2, 0x302($t5)
/* 0C2A60 800C1E60 8C4CFFFC */  lw    $t4, -4($v0)
/* 0C2A64 800C1E64 00000000 */  nop   
/* 0C2A68 800C1E68 01837021 */  addu  $t6, $t4, $v1
/* 0C2A6C 800C1E6C A1C50303 */  sb    $a1, 0x303($t6)
/* 0C2A70 800C1E70 8C4FFFFC */  lw    $t7, -4($v0)
/* 0C2A74 800C1E74 00000000 */  nop   
/* 0C2A78 800C1E78 01E3C021 */  addu  $t8, $t7, $v1
/* 0C2A7C 800C1E7C A3040311 */  sb    $a0, 0x311($t8)
/* 0C2A80 800C1E80 8C59FFFC */  lw    $t9, -4($v0)
/* 0C2A84 800C1E84 00000000 */  nop   
/* 0C2A88 800C1E88 03236821 */  addu  $t5, $t9, $v1
/* 0C2A8C 800C1E8C A1A50312 */  sb    $a1, 0x312($t5)
/* 0C2A90 800C1E90 8C4CFFFC */  lw    $t4, -4($v0)
/* 0C2A94 800C1E94 00000000 */  nop   
/* 0C2A98 800C1E98 01837021 */  addu  $t6, $t4, $v1
/* 0C2A9C 800C1E9C 144AFFA0 */  bne   $v0, $t2, .L800C1D20
/* 0C2AA0 800C1EA0 A1C80313 */   sb    $t0, 0x313($t6)
/* 0C2AA4 800C1EA4 26940001 */  addiu $s4, $s4, 1
/* 0C2AA8 800C1EA8 168BFF97 */  bne   $s4, $t3, .L800C1D08
/* 0C2AAC 800C1EAC 00142040 */   sll   $a0, $s4, 1
/* 0C2AB0 800C1EB0 8FBF0034 */  lw    $ra, 0x34($sp)
/* 0C2AB4 800C1EB4 240F0001 */  li    $t7, 1
/* 0C2AB8 800C1EB8 3C01800E */  lui   $at, %hi(sTransitionStatus) # $at, 0x800e
/* 0C2ABC 800C1EBC C7B50010 */  lwc1  $f21, 0x10($sp)
/* 0C2AC0 800C1EC0 C7B40014 */  lwc1  $f20, 0x14($sp)
/* 0C2AC4 800C1EC4 8FB0001C */  lw    $s0, 0x1c($sp)
/* 0C2AC8 800C1EC8 8FB10020 */  lw    $s1, 0x20($sp)
/* 0C2ACC 800C1ECC 8FB20024 */  lw    $s2, 0x24($sp)
/* 0C2AD0 800C1ED0 8FB30028 */  lw    $s3, 0x28($sp)
/* 0C2AD4 800C1ED4 8FB4002C */  lw    $s4, 0x2c($sp)
/* 0C2AD8 800C1ED8 8FB50030 */  lw    $s5, 0x30($sp)
/* 0C2ADC 800C1EDC AC2F31AC */  sw    $t7, %lo(sTransitionStatus)($at)
/* 0C2AE0 800C1EE0 03E00008 */  jr    $ra
/* 0C2AE4 800C1EE4 27BD0038 */   addiu $sp, $sp, 0x38

