.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800D17F0
/* 0D23F0 800D17F0 18A0001F */  blez  $a1, .L800D1870
/* 0D23F4 800D17F4 00000000 */   nop   
/* 0D23F8 800D17F8 240B2000 */  li    $t3, 8192
/* 0D23FC 800D17FC 00AB082B */  sltu  $at, $a1, $t3
/* 0D2400 800D1800 1020001D */  beqz  $at, .L800D1878
/* 0D2404 800D1804 00000000 */   nop   
/* 0D2408 800D1808 00804025 */  move  $t0, $a0
/* 0D240C 800D180C 00854821 */  addu  $t1, $a0, $a1
/* 0D2410 800D1810 0109082B */  sltu  $at, $t0, $t1
/* 0D2414 800D1814 10200016 */  beqz  $at, .L800D1870
/* 0D2418 800D1818 00000000 */   nop   
/* 0D241C 800D181C 310A000F */  andi  $t2, $t0, 0xf
/* 0D2420 800D1820 11400007 */  beqz  $t2, .L800D1840
/* 0D2424 800D1824 2529FFF0 */   addiu $t1, $t1, -0x10
/* 0D2428 800D1828 010A4023 */  subu  $t0, $t0, $t2
/* 0D242C 800D182C BD150000 */  cache 0x15, ($t0)
/* 0D2430 800D1830 0109082B */  sltu  $at, $t0, $t1
/* 0D2434 800D1834 1020000E */  beqz  $at, .L800D1870
/* 0D2438 800D1838 00000000 */   nop   
/* 0D243C 800D183C 25080010 */  addiu $t0, $t0, 0x10
.L800D1840:
/* 0D2440 800D1840 312A000F */  andi  $t2, $t1, 0xf
/* 0D2444 800D1844 11400006 */  beqz  $t2, .L800D1860
/* 0D2448 800D1848 00000000 */   nop   
/* 0D244C 800D184C 012A4823 */  subu  $t1, $t1, $t2
/* 0D2450 800D1850 BD350010 */  cache 0x15, 0x10($t1)
/* 0D2454 800D1854 0128082B */  sltu  $at, $t1, $t0
/* 0D2458 800D1858 14200005 */  bnez  $at, .L800D1870
/* 0D245C 800D185C 00000000 */   nop   
.L800D1860:
/* 0D2460 800D1860 BD110000 */  cache 0x11, ($t0)
/* 0D2464 800D1864 0109082B */  sltu  $at, $t0, $t1
/* 0D2468 800D1868 1420FFFD */  bnez  $at, .L800D1860
/* 0D246C 800D186C 25080010 */   addiu $t0, $t0, 0x10
.L800D1870:
/* 0D2470 800D1870 03E00008 */  jr    $ra
/* 0D2474 800D1874 00000000 */   nop   

.L800D1878:
/* 0D2478 800D1878 3C088000 */  lui   $t0, %hi(D_80000010) # $t0, 0x8000
/* 0D247C 800D187C 010B4821 */  addu  $t1, $t0, $t3
/* 0D2480 800D1880 2529FFF0 */  addiu $t1, $t1, -0x10
.L800D1884:
/* 0D2484 800D1884 BD010000 */  cache 1, ($t0)
/* 0D2488 800D1888 0109082B */  sltu  $at, $t0, $t1
/* 0D248C 800D188C 1420FFFD */  bnez  $at, .L800D1884
/* 0D2490 800D1890 25080010 */   addiu $t0, %lo(D_80000010) # addiu $t0, $t0, 0x10
/* 0D2494 800D1894 03E00008 */  jr    $ra
/* 0D2498 800D1898 00000000 */   nop   

/* 0D249C 800D189C 00000000 */  nop   
