glabel func_800A22F4
/* 0A2EF4 800A22F4 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0A2EF8 800A22F8 AFB00018 */  sw    $s0, 0x18($sp)
/* 0A2EFC 800A22FC 3C108012 */  lui   $s0, %hi(D_80126CDC) # $s0, 0x8012
/* 0A2F00 800A2300 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0A2F04 800A2304 AFA40020 */  sw    $a0, 0x20($sp)
/* 0A2F08 800A2308 AFA50024 */  sw    $a1, 0x24($sp)
/* 0A2F0C 800A230C 808F0003 */  lb    $t7, 3($a0)
/* 0A2F10 800A2310 26106CDC */  addiu $s0, %lo(D_80126CDC) # addiu $s0, $s0, 0x6cdc
/* 0A2F14 800A2314 8E190000 */  lw    $t9, ($s0)
/* 0A2F18 800A2318 25F80038 */  addiu $t8, $t7, 0x38
/* 0A2F1C 800A231C 3C038012 */  lui   $v1, %hi(D_80126D37) # $v1, 0x8012
/* 0A2F20 800A2320 A7380646 */  sh    $t8, 0x646($t9)
/* 0A2F24 800A2324 90636D37 */  lbu   $v1, %lo(D_80126D37)($v1)
/* 0A2F28 800A2328 00807025 */  move  $t6, $a0
/* 0A2F2C 800A232C 28610003 */  slti  $at, $v1, 3
/* 0A2F30 800A2330 14200009 */  bnez  $at, .L800A2358
/* 0A2F34 800A2334 24010003 */   li    $at, 3
/* 0A2F38 800A2338 1461001C */  bne   $v1, $at, .L800A23AC
/* 0A2F3C 800A233C 8FAB0020 */   lw    $t3, 0x20($sp)
/* 0A2F40 800A2340 8FA80020 */  lw    $t0, 0x20($sp)
/* 0A2F44 800A2344 2401FFFF */  li    $at, -1
/* 0A2F48 800A2348 85090000 */  lh    $t1, ($t0)
/* 0A2F4C 800A234C 00000000 */  nop   
/* 0A2F50 800A2350 15210016 */  bne   $t1, $at, .L800A23AC
/* 0A2F54 800A2354 8FAB0020 */   lw    $t3, 0x20($sp)
.L800A2358:
/* 0A2F58 800A2358 240A0001 */  li    $t2, 1
/* 0A2F5C 800A235C 3C018012 */  lui   $at, %hi(D_80126CD5) # $at, 0x8012
/* 0A2F60 800A2360 A02A6CD5 */  sb    $t2, %lo(D_80126CD5)($at)
/* 0A2F64 800A2364 8E070000 */  lw    $a3, ($s0)
/* 0A2F68 800A2368 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A2F6C 800A236C 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A2F70 800A2370 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A2F74 800A2374 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A2F78 800A2378 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A2F7C 800A237C 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A2F80 800A2380 0C02A980 */  jal   func_800AA600
/* 0A2F84 800A2384 24E70640 */   addiu $a3, $a3, 0x640
/* 0A2F88 800A2388 3C018012 */  lui   $at, %hi(D_80126CD5) # $at, 0x8012
/* 0A2F8C 800A238C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A2F90 800A2390 A0206CD5 */  sb    $zero, %lo(D_80126CD5)($at)
/* 0A2F94 800A2394 0C01E015 */  jal   init_rdp_and_framebuffer
/* 0A2F98 800A2398 24846CFC */   addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A2F9C 800A239C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A2FA0 800A23A0 0C01ECF4 */  jal   func_8007B3D0
/* 0A2FA4 800A23A4 24846CFC */   addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A2FA8 800A23A8 8FAB0020 */  lw    $t3, 0x20($sp)
.L800A23AC:
/* 0A2FAC 800A23AC 2403000A */  li    $v1, 10
/* 0A2FB0 800A23B0 81620185 */  lb    $v0, 0x185($t3)
/* 0A2FB4 800A23B4 00000000 */  nop   
/* 0A2FB8 800A23B8 2841000A */  slti  $at, $v0, 0xa
/* 0A2FBC 800A23BC 10200010 */  beqz  $at, .L800A2400
/* 0A2FC0 800A23C0 00000000 */   nop   
/* 0A2FC4 800A23C4 8E0C0000 */  lw    $t4, ($s0)
/* 0A2FC8 800A23C8 3C0D8012 */  lui   $t5, %hi(D_80126D37) # $t5, 0x8012
/* 0A2FCC 800A23CC A58206D8 */  sh    $v0, 0x6d8($t4)
/* 0A2FD0 800A23D0 91AD6D37 */  lbu   $t5, %lo(D_80126D37)($t5)
/* 0A2FD4 800A23D4 24010002 */  li    $at, 2
/* 0A2FD8 800A23D8 15A1002F */  bne   $t5, $at, .L800A2498
/* 0A2FDC 800A23DC 00000000 */   nop   
/* 0A2FE0 800A23E0 8E020000 */  lw    $v0, ($s0)
/* 0A2FE4 800A23E4 3C0140C0 */  li    $at, 0x40C00000 # 6.000000
/* 0A2FE8 800A23E8 44813000 */  mtc1  $at, $f6
/* 0A2FEC 800A23EC C44406CC */  lwc1  $f4, 0x6cc($v0)
/* 0A2FF0 800A23F0 00000000 */  nop   
/* 0A2FF4 800A23F4 46062200 */  add.s $f8, $f4, $f6
/* 0A2FF8 800A23F8 10000027 */  b     .L800A2498
/* 0A2FFC 800A23FC E44806CC */   swc1  $f8, 0x6cc($v0)
.L800A2400:
/* 0A3000 800A2400 0043001A */  div   $zero, $v0, $v1
/* 0A3004 800A2404 8E0F0000 */  lw    $t7, ($s0)
/* 0A3008 800A2408 14600002 */  bnez  $v1, .L800A2414
/* 0A300C 800A240C 00000000 */   nop   
/* 0A3010 800A2410 0007000D */  break 7
.L800A2414:
/* 0A3014 800A2414 2401FFFF */  li    $at, -1
/* 0A3018 800A2418 14610004 */  bne   $v1, $at, .L800A242C
/* 0A301C 800A241C 3C018000 */   lui   $at, 0x8000
/* 0A3020 800A2420 14410002 */  bne   $v0, $at, .L800A242C
/* 0A3024 800A2424 00000000 */   nop   
/* 0A3028 800A2428 0006000D */  break 6
.L800A242C:
/* 0A302C 800A242C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A3030 800A2430 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A3034 800A2434 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A3038 800A2438 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A303C 800A243C 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A3040 800A2440 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A3044 800A2444 00007012 */  mflo  $t6
/* 0A3048 800A2448 A5EE06D8 */  sh    $t6, 0x6d8($t7)
/* 0A304C 800A244C 8FB80020 */  lw    $t8, 0x20($sp)
/* 0A3050 800A2450 8E090000 */  lw    $t1, ($s0)
/* 0A3054 800A2454 83190185 */  lb    $t9, 0x185($t8)
/* 0A3058 800A2458 00000000 */  nop   
/* 0A305C 800A245C 0323001A */  div   $zero, $t9, $v1
/* 0A3060 800A2460 14600002 */  bnez  $v1, .L800A246C
/* 0A3064 800A2464 00000000 */   nop   
/* 0A3068 800A2468 0007000D */  break 7
.L800A246C:
/* 0A306C 800A246C 2401FFFF */  li    $at, -1
/* 0A3070 800A2470 14610004 */  bne   $v1, $at, .L800A2484
/* 0A3074 800A2474 3C018000 */   lui   $at, 0x8000
/* 0A3078 800A2478 17210002 */  bne   $t9, $at, .L800A2484
/* 0A307C 800A247C 00000000 */   nop   
/* 0A3080 800A2480 0006000D */  break 6
.L800A2484:
/* 0A3084 800A2484 00004010 */  mfhi  $t0
/* 0A3088 800A2488 A52806F8 */  sh    $t0, 0x6f8($t1)
/* 0A308C 800A248C 8E070000 */  lw    $a3, ($s0)
/* 0A3090 800A2490 0C02A980 */  jal   func_800AA600
/* 0A3094 800A2494 24E706E0 */   addiu $a3, $a3, 0x6e0
.L800A2498:
/* 0A3098 800A2498 8E070000 */  lw    $a3, ($s0)
/* 0A309C 800A249C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A30A0 800A24A0 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A30A4 800A24A4 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A30A8 800A24A8 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A30AC 800A24AC 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A30B0 800A24B0 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A30B4 800A24B4 0C02A980 */  jal   func_800AA600
/* 0A30B8 800A24B8 24E706C0 */   addiu $a3, $a3, 0x6c0
/* 0A30BC 800A24BC 3C038012 */  lui   $v1, %hi(D_80126D37) # $v1, 0x8012
/* 0A30C0 800A24C0 90636D37 */  lbu   $v1, %lo(D_80126D37)($v1)
/* 0A30C4 800A24C4 24040002 */  li    $a0, 2
/* 0A30C8 800A24C8 14830011 */  bne   $a0, $v1, .L800A2510
/* 0A30CC 800A24CC 3C058012 */   lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A30D0 800A24D0 8FAA0020 */  lw    $t2, 0x20($sp)
/* 0A30D4 800A24D4 00000000 */  nop   
/* 0A30D8 800A24D8 814B0185 */  lb    $t3, 0x185($t2)
/* 0A30DC 800A24DC 00000000 */  nop   
/* 0A30E0 800A24E0 2961000A */  slti  $at, $t3, 0xa
/* 0A30E4 800A24E4 1020000A */  beqz  $at, .L800A2510
/* 0A30E8 800A24E8 00000000 */   nop   
/* 0A30EC 800A24EC 8E020000 */  lw    $v0, ($s0)
/* 0A30F0 800A24F0 3C0140C0 */  li    $at, 0x40C00000 # 6.000000
/* 0A30F4 800A24F4 44818000 */  mtc1  $at, $f16
/* 0A30F8 800A24F8 C44A06CC */  lwc1  $f10, 0x6cc($v0)
/* 0A30FC 800A24FC 3C038012 */  lui   $v1, %hi(D_80126D37) # $v1, 0x8012
/* 0A3100 800A2500 46105481 */  sub.s $f18, $f10, $f16
/* 0A3104 800A2504 E45206CC */  swc1  $f18, 0x6cc($v0)
/* 0A3108 800A2508 90636D37 */  lbu   $v1, %lo(D_80126D37)($v1)
/* 0A310C 800A250C 00000000 */  nop   
.L800A2510:
/* 0A3110 800A2510 1083001A */  beq   $a0, $v1, .L800A257C
/* 0A3114 800A2514 24A56D00 */   addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A3118 800A2518 8E070000 */  lw    $a3, ($s0)
/* 0A311C 800A251C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A3120 800A2520 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A3124 800A2524 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A3128 800A2528 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A312C 800A252C 0C02A980 */  jal   func_800AA600
/* 0A3130 800A2530 24E706A0 */   addiu $a3, $a3, 0x6a0
/* 0A3134 800A2534 0C01EFC7 */  jal   func_8007BF1C
/* 0A3138 800A2538 24040001 */   li    $a0, 1
/* 0A313C 800A253C 240C0001 */  li    $t4, 1
/* 0A3140 800A2540 3C018012 */  lui   $at, %hi(D_80126CD5) # $at, 0x8012
/* 0A3144 800A2544 A02C6CD5 */  sb    $t4, %lo(D_80126CD5)($at)
/* 0A3148 800A2548 8E070000 */  lw    $a3, ($s0)
/* 0A314C 800A254C 3C048012 */  lui   $a0, %hi(gHUDCurrDisplayList) # $a0, 0x8012
/* 0A3150 800A2550 3C058012 */  lui   $a1, %hi(D_80126D00) # $a1, 0x8012
/* 0A3154 800A2554 3C068012 */  lui   $a2, %hi(D_80126D04) # $a2, 0x8012
/* 0A3158 800A2558 24C66D04 */  addiu $a2, %lo(D_80126D04) # addiu $a2, $a2, 0x6d04
/* 0A315C 800A255C 24A56D00 */  addiu $a1, %lo(D_80126D00) # addiu $a1, $a1, 0x6d00
/* 0A3160 800A2560 24846CFC */  addiu $a0, %lo(gHUDCurrDisplayList) # addiu $a0, $a0, 0x6cfc
/* 0A3164 800A2564 0C02A980 */  jal   func_800AA600
/* 0A3168 800A2568 24E70680 */   addiu $a3, $a3, 0x680
/* 0A316C 800A256C 3C018012 */  lui   $at, %hi(D_80126CD5) # $at, 0x8012
/* 0A3170 800A2570 A0206CD5 */  sb    $zero, %lo(D_80126CD5)($at)
/* 0A3174 800A2574 0C01EFC7 */  jal   func_8007BF1C
/* 0A3178 800A2578 00002025 */   move  $a0, $zero
.L800A257C:
/* 0A317C 800A257C 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0A3180 800A2580 8FB00018 */  lw    $s0, 0x18($sp)
/* 0A3184 800A2584 03E00008 */  jr    $ra
/* 0A3188 800A2588 27BD0020 */   addiu $sp, $sp, 0x20

