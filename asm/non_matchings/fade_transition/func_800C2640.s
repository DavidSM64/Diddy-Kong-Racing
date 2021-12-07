glabel func_800C2640
/* 0C3240 800C2640 AFA40000 */  sw    $a0, ($sp)
/* 0C3244 800C2644 3C048013 */  lui   $a0, %hi(gLastFadeGreen) # $a0, 0x8013
/* 0C3248 800C2648 3C038013 */  lui   $v1, %hi(gLastFadeRed) # $v1, 0x8013
/* 0C324C 800C264C 3C058013 */  lui   $a1, %hi(gLastFadeBlue) # $a1, 0x8013
/* 0C3250 800C2650 24A5A740 */  addiu $a1, %lo(gLastFadeBlue) # addiu $a1, $a1, -0x58c0
/* 0C3254 800C2654 2463A738 */  addiu $v1, %lo(gLastFadeRed) # addiu $v1, $v1, -0x58c8
/* 0C3258 800C2658 2484A73C */  addiu $a0, %lo(gLastFadeGreen) # addiu $a0, $a0, -0x58c4
/* 0C325C 800C265C 8C6E0000 */  lw    $t6, ($v1)
/* 0C3260 800C2660 8C980000 */  lw    $t8, ($a0)
/* 0C3264 800C2664 8CA80000 */  lw    $t0, ($a1)
/* 0C3268 800C2668 000E7C00 */  sll   $t7, $t6, 0x10
/* 0C326C 800C266C 0018CC00 */  sll   $t9, $t8, 0x10
/* 0C3270 800C2670 00084C00 */  sll   $t1, $t0, 0x10
/* 0C3274 800C2674 AC6F0000 */  sw    $t7, ($v1)
/* 0C3278 800C2678 AC990000 */  sw    $t9, ($a0)
/* 0C327C 800C267C ACA90000 */  sw    $t1, ($a1)
/* 0C3280 800C2680 240A00FF */  li    $t2, 255
/* 0C3284 800C2684 3C018013 */  lui   $at, %hi(gCurFadeAlpha) # $at, 0x8013
/* 0C3288 800C2688 A02AA737 */  sb    $t2, %lo(gCurFadeAlpha)($at)
/* 0C328C 800C268C 3C01437F */  li    $at, 0x437F0000 # 255.000000
/* 0C3290 800C2690 44812000 */  mtc1  $at, $f4
/* 0C3294 800C2694 3C018013 */  lui   $at, %hi(sTransitionOpacity) # $at, 0x8013
/* 0C3298 800C2698 44803000 */  mtc1  $zero, $f6
/* 0C329C 800C269C E424A750 */  swc1  $f4, %lo(sTransitionOpacity)($at)
/* 0C32A0 800C26A0 3C018013 */  lui   $at, %hi(D_8012A754) # $at, 0x8013
/* 0C32A4 800C26A4 3C0B8013 */  lui   $t3, %hi(gCurFadeRed) # $t3, 0x8013
/* 0C32A8 800C26A8 916BA734 */  lbu   $t3, %lo(gCurFadeRed)($t3)
/* 0C32AC 800C26AC E426A754 */  swc1  $f6, %lo(D_8012A754)($at)
/* 0C32B0 800C26B0 8C6D0000 */  lw    $t5, ($v1)
/* 0C32B4 800C26B4 3C02800E */  lui   $v0, %hi(sTransitionFadeTimer) # $v0, 0x800e
/* 0C32B8 800C26B8 944231B0 */  lhu   $v0, %lo(sTransitionFadeTimer)($v0)
/* 0C32BC 800C26BC 000B6400 */  sll   $t4, $t3, 0x10
/* 0C32C0 800C26C0 018D7023 */  subu  $t6, $t4, $t5
/* 0C32C4 800C26C4 01C2001A */  div   $zero, $t6, $v0
/* 0C32C8 800C26C8 3C188013 */  lui   $t8, %hi(gCurFadeGreen) # $t8, 0x8013
/* 0C32CC 800C26CC 14400002 */  bnez  $v0, .L800C26D8
/* 0C32D0 800C26D0 00000000 */   nop   
/* 0C32D4 800C26D4 0007000D */  break 7
.L800C26D8:
/* 0C32D8 800C26D8 2401FFFF */  li    $at, -1
/* 0C32DC 800C26DC 14410004 */  bne   $v0, $at, .L800C26F0
/* 0C32E0 800C26E0 3C018000 */   lui   $at, 0x8000
/* 0C32E4 800C26E4 15C10002 */  bne   $t6, $at, .L800C26F0
/* 0C32E8 800C26E8 00000000 */   nop   
/* 0C32EC 800C26EC 0006000D */  break 6
.L800C26F0:
/* 0C32F0 800C26F0 3C018013 */  lui   $at, %hi(D_8012A744) # $at, 0x8013
/* 0C32F4 800C26F4 9318A735 */  lbu   $t8, %lo(gCurFadeGreen)($t8)
/* 0C32F8 800C26F8 3C0B8013 */  lui   $t3, %hi(gCurFadeBlue) # $t3, 0x8013
/* 0C32FC 800C26FC 0018CC00 */  sll   $t9, $t8, 0x10
/* 0C3300 800C2700 916BA736 */  lbu   $t3, %lo(gCurFadeBlue)($t3)
/* 0C3304 800C2704 24180001 */  li    $t8, 1
/* 0C3308 800C2708 000B6400 */  sll   $t4, $t3, 0x10
/* 0C330C 800C270C 00007812 */  mflo  $t7
/* 0C3310 800C2710 AC2FA744 */  sw    $t7, %lo(D_8012A744)($at)
/* 0C3314 800C2714 8C880000 */  lw    $t0, ($a0)
/* 0C3318 800C2718 00000000 */  nop   
/* 0C331C 800C271C 03284823 */  subu  $t1, $t9, $t0
/* 0C3320 800C2720 0122001A */  div   $zero, $t1, $v0
/* 0C3324 800C2724 14400002 */  bnez  $v0, .L800C2730
/* 0C3328 800C2728 00000000 */   nop   
/* 0C332C 800C272C 0007000D */  break 7
.L800C2730:
/* 0C3330 800C2730 2401FFFF */  li    $at, -1
/* 0C3334 800C2734 14410004 */  bne   $v0, $at, .L800C2748
/* 0C3338 800C2738 3C018000 */   lui   $at, 0x8000
/* 0C333C 800C273C 15210002 */  bne   $t1, $at, .L800C2748
/* 0C3340 800C2740 00000000 */   nop   
/* 0C3344 800C2744 0006000D */  break 6
.L800C2748:
/* 0C3348 800C2748 3C018013 */  lui   $at, %hi(D_8012A748) # $at, 0x8013
/* 0C334C 800C274C 00005012 */  mflo  $t2
/* 0C3350 800C2750 AC2AA748 */  sw    $t2, %lo(D_8012A748)($at)
/* 0C3354 800C2754 8CAD0000 */  lw    $t5, ($a1)
/* 0C3358 800C2758 00000000 */  nop   
/* 0C335C 800C275C 018D7023 */  subu  $t6, $t4, $t5
/* 0C3360 800C2760 01C2001A */  div   $zero, $t6, $v0
/* 0C3364 800C2764 14400002 */  bnez  $v0, .L800C2770
/* 0C3368 800C2768 00000000 */   nop   
/* 0C336C 800C276C 0007000D */  break 7
.L800C2770:
/* 0C3370 800C2770 2401FFFF */  li    $at, -1
/* 0C3374 800C2774 14410004 */  bne   $v0, $at, .L800C2788
/* 0C3378 800C2778 3C018000 */   lui   $at, 0x8000
/* 0C337C 800C277C 15C10002 */  bne   $t6, $at, .L800C2788
/* 0C3380 800C2780 00000000 */   nop   
/* 0C3384 800C2784 0006000D */  break 6
.L800C2788:
/* 0C3388 800C2788 3C018013 */  lui   $at, %hi(D_8012A74C) # $at, 0x8013
/* 0C338C 800C278C 00007812 */  mflo  $t7
/* 0C3390 800C2790 AC2FA74C */  sw    $t7, %lo(D_8012A74C)($at)
/* 0C3394 800C2794 3C01800E */  lui   $at, %hi(sTransitionStatus) # $at, 0x800e
/* 0C3398 800C2798 03E00008 */  jr    $ra
/* 0C339C 800C279C AC3831AC */   sw    $t8, %lo(sTransitionStatus)($at)

