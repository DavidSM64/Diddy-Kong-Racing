glabel render_fade_waves
/* 0C2FF8 800C23F8 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0C2FFC 800C23FC AFBF001C */  sw    $ra, 0x1c($sp)
/* 0C3000 800C2400 AFB00018 */  sw    $s0, 0x18($sp)
/* 0C3004 800C2404 AFA40020 */  sw    $a0, 0x20($sp)
/* 0C3008 800C2408 AFA50024 */  sw    $a1, 0x24($sp)
/* 0C300C 800C240C 0C01ECF4 */  jal   func_8007B3D0
/* 0C3010 800C2410 AFA60028 */   sw    $a2, 0x28($sp)
/* 0C3014 800C2414 3C03800E */  lui   $v1, %hi(sTransitionTaskNum) # $v1, 0x800e
/* 0C3018 800C2418 8FAE0020 */  lw    $t6, 0x20($sp)
/* 0C301C 800C241C 8C6331D0 */  lw    $v1, %lo(sTransitionTaskNum)($v1)
/* 0C3020 800C2420 8DC20000 */  lw    $v0, ($t6)
/* 0C3024 800C2424 00037880 */  sll   $t7, $v1, 2
/* 0C3028 800C2428 3C06800E */  lui   $a2, %hi(sTransitionVtx) # $a2, 0x800e
/* 0C302C 800C242C 3C07800E */  lui   $a3, %hi(sTransitionTris) # $a3, 0x800e
/* 0C3030 800C2430 00CF3021 */  addu  $a2, $a2, $t7
/* 0C3034 800C2434 00EF3821 */  addu  $a3, $a3, $t7
/* 0C3038 800C2438 00402025 */  move  $a0, $v0
/* 0C303C 800C243C 8CC631C0 */  lw    $a2, %lo(sTransitionVtx)($a2)
/* 0C3040 800C2440 8CE731C8 */  lw    $a3, %lo(sTransitionTris)($a3)
/* 0C3044 800C2444 3C19800E */  lui   $t9, %hi(dTransitionShapeSettings) # $t9, 0x800e
/* 0C3048 800C2448 27393648 */  addiu $t9, %lo(dTransitionShapeSettings) # addiu $t9, $t9, 0x3648
/* 0C304C 800C244C 3C180600 */  lui   $t8, 0x600
/* 0C3050 800C2450 3C1005D0 */  lui   $s0, (0x05D000E0 >> 16) # lui $s0, 0x5d0
/* 0C3054 800C2454 3C0D05B0 */  lui   $t5, (0x05B000C0 >> 16) # lui $t5, 0x5b0
/* 0C3058 800C2458 AC980000 */  sw    $t8, ($a0)
/* 0C305C 800C245C AC990004 */  sw    $t9, 4($a0)
/* 0C3060 800C2460 35AD00C0 */  ori   $t5, (0x05B000C0 & 0xFFFF) # ori $t5, $t5, 0xc0
/* 0C3064 800C2464 361000E0 */  ori   $s0, (0x05D000E0 & 0xFFFF) # ori $s0, $s0, 0xe0
/* 0C3068 800C2468 00004025 */  move  $t0, $zero
/* 0C306C 800C246C 241F0006 */  li    $ra, 6
/* 0C3070 800C2470 240C0004 */  li    $t4, 4
/* 0C3074 800C2474 240B0001 */  li    $t3, 1
/* 0C3078 800C2478 3C0A0400 */  lui   $t2, 0x400
/* 0C307C 800C247C 3C098000 */  lui   $t1, 0x8000
/* 0C3080 800C2480 24420008 */  addiu $v0, $v0, 8
.L800C2484:
/* 0C3084 800C2484 110B0003 */  beq   $t0, $t3, .L800C2494
/* 0C3088 800C2488 00401825 */   move  $v1, $v0
/* 0C308C 800C248C 150C0013 */  bne   $t0, $t4, .L800C24DC
/* 0C3090 800C2490 00C92021 */   addu  $a0, $a2, $t1
.L800C2494:
/* 0C3094 800C2494 00C92021 */  addu  $a0, $a2, $t1
/* 0C3098 800C2498 308E0006 */  andi  $t6, $a0, 6
/* 0C309C 800C249C 35CF0068 */  ori   $t7, $t6, 0x68
/* 0C30A0 800C24A0 31F800FF */  andi  $t8, $t7, 0xff
/* 0C30A4 800C24A4 0018CC00 */  sll   $t9, $t8, 0x10
/* 0C30A8 800C24A8 032A7025 */  or    $t6, $t9, $t2
/* 0C30AC 800C24AC 24420008 */  addiu $v0, $v0, 8
/* 0C30B0 800C24B0 35CF0104 */  ori   $t7, $t6, 0x104
/* 0C30B4 800C24B4 00402825 */  move  $a1, $v0
/* 0C30B8 800C24B8 AC6F0000 */  sw    $t7, ($v1)
/* 0C30BC 800C24BC AC640004 */  sw    $a0, 4($v1)
/* 0C30C0 800C24C0 00E9C021 */  addu  $t8, $a3, $t1
/* 0C30C4 800C24C4 ACB80004 */  sw    $t8, 4($a1)
/* 0C30C8 800C24C8 ACAD0000 */  sw    $t5, ($a1)
/* 0C30CC 800C24CC 24420008 */  addiu $v0, $v0, 8
/* 0C30D0 800C24D0 24C6008C */  addiu $a2, $a2, 0x8c
/* 0C30D4 800C24D4 10000012 */  b     .L800C2520
/* 0C30D8 800C24D8 24E700C0 */   addiu $a3, $a3, 0xc0
.L800C24DC:
/* 0C30DC 800C24DC 30990006 */  andi  $t9, $a0, 6
/* 0C30E0 800C24E0 372E0078 */  ori   $t6, $t9, 0x78
/* 0C30E4 800C24E4 31CF00FF */  andi  $t7, $t6, 0xff
/* 0C30E8 800C24E8 000FC400 */  sll   $t8, $t7, 0x10
/* 0C30EC 800C24EC 00401825 */  move  $v1, $v0
/* 0C30F0 800C24F0 24420008 */  addiu $v0, $v0, 8
/* 0C30F4 800C24F4 030AC825 */  or    $t9, $t8, $t2
/* 0C30F8 800C24F8 372E0128 */  ori   $t6, $t9, 0x128
/* 0C30FC 800C24FC 00402825 */  move  $a1, $v0
/* 0C3100 800C2500 AC6E0000 */  sw    $t6, ($v1)
/* 0C3104 800C2504 AC640004 */  sw    $a0, 4($v1)
/* 0C3108 800C2508 00E97821 */  addu  $t7, $a3, $t1
/* 0C310C 800C250C ACAF0004 */  sw    $t7, 4($a1)
/* 0C3110 800C2510 ACB00000 */  sw    $s0, ($a1)
/* 0C3114 800C2514 24420008 */  addiu $v0, $v0, 8
/* 0C3118 800C2518 24C600A0 */  addiu $a2, $a2, 0xa0
/* 0C311C 800C251C 24E700E0 */  addiu $a3, $a3, 0xe0
.L800C2520:
/* 0C3120 800C2520 25080001 */  addiu $t0, $t0, 1
/* 0C3124 800C2524 151FFFD7 */  bne   $t0, $ra, .L800C2484
/* 0C3128 800C2528 00000000 */   nop   
/* 0C312C 800C252C 8FA40020 */  lw    $a0, 0x20($sp)
/* 0C3130 800C2530 0C01ECF4 */  jal   func_8007B3D0
/* 0C3134 800C2534 AC820000 */   sw    $v0, ($a0)
/* 0C3138 800C2538 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0C313C 800C253C 8FB00018 */  lw    $s0, 0x18($sp)
/* 0C3140 800C2540 03E00008 */  jr    $ra
/* 0C3144 800C2544 27BD0020 */   addiu $sp, $sp, 0x20

