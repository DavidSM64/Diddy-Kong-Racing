.rdata
glabel D_800E8640
.asciz "CAN'T"
.ascii "\0\0" # padding
glabel D_800E8648
.asciz "SAVE"
.ascii "\0\0\0" # padding
glabel D_800E8650
.asciz "GHOST"
.ascii "\0\0" # padding
glabel D_800E8658
.asciz " CONTROLLER"
glabel D_800E8664
.asciz "PAK"
glabel D_800E8668
.asciz "FULL"
.ascii "\0\0\0" # padding
glabel D_800E8670
.asciz " CONTROLLER"
glabel D_800E867C
.asciz "PAK"
glabel D_800E8680
.asciz "DAMAGED"

.late_rodata
glabel D_800E8738
.double 1.2

.text
glabel func_800A277C
/* 0A337C 800A277C 27BDFF40 */  addiu $sp, $sp, -0xc0
/* 0A3380 800A2780 AFB00020 */  sw    $s0, 0x20($sp)
/* 0A3384 800A2784 3C108012 */  lui   $s0, %hi(D_80126CF4) # $s0, 0x8012
/* 0A3388 800A2788 AFBF002C */  sw    $ra, 0x2c($sp)
/* 0A338C 800A278C AFB20028 */  sw    $s2, 0x28($sp)
/* 0A3390 800A2790 AFB10024 */  sw    $s1, 0x24($sp)
/* 0A3394 800A2794 AFA400C0 */  sw    $a0, 0xc0($sp)
/* 0A3398 800A2798 AFA500C4 */  sw    $a1, 0xc4($sp)
/* 0A339C 800A279C AFA600C8 */  sw    $a2, 0xc8($sp)
/* 0A33A0 800A27A0 8CAF0064 */  lw    $t7, 0x64($a1)
/* 0A33A4 800A27A4 26106CF4 */  addiu $s0, %lo(D_80126CF4) # addiu $s0, $s0, 0x6cf4
/* 0A33A8 800A27A8 8E030000 */  lw    $v1, ($s0)
/* 0A33AC 800A27AC AFAF00A0 */  sw    $t7, 0xa0($sp)
/* 0A33B0 800A27B0 8C780050 */  lw    $t8, 0x50($v1)
/* 0A33B4 800A27B4 00004825 */  move  $t1, $zero
/* 0A33B8 800A27B8 1700001E */  bnez  $t8, .L800A2834
/* 0A33BC 800A27BC 3C198012 */   lui   $t9, %hi(D_80126CF0) # $t9, 0x8012
/* 0A33C0 800A27C0 8F396CF0 */  lw    $t9, %lo(D_80126CF0)($t9)
/* 0A33C4 800A27C4 240C0008 */  li    $t4, 8
/* 0A33C8 800A27C8 872B0028 */  lh    $t3, 0x28($t9)
/* 0A33CC 800A27CC A3AC0091 */  sb    $t4, 0x91($sp)
/* 0A33D0 800A27D0 A7A00092 */  sh    $zero, 0x92($sp)
/* 0A33D4 800A27D4 A7A00094 */  sh    $zero, 0x94($sp)
/* 0A33D8 800A27D8 A7A00096 */  sh    $zero, 0x96($sp)
/* 0A33DC 800A27DC AFA900A8 */  sw    $t1, 0xa8($sp)
/* 0A33E0 800A27E0 27A40090 */  addiu $a0, $sp, 0x90
/* 0A33E4 800A27E4 00002825 */  move  $a1, $zero
/* 0A33E8 800A27E8 0C003A95 */  jal   spawn_object
/* 0A33EC 800A27EC A3AB0090 */   sb    $t3, 0x90($sp)
/* 0A33F0 800A27F0 8E0D0000 */  lw    $t5, ($s0)
/* 0A33F4 800A27F4 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A33F8 800A27F8 3C118012 */  lui   $s1, %hi(D_80126CDC) # $s1, 0x8012
/* 0A33FC 800A27FC 26316CDC */  addiu $s1, %lo(D_80126CDC) # addiu $s1, $s1, 0x6cdc
/* 0A3400 800A2800 ADA20050 */  sw    $v0, 0x50($t5)
/* 0A3404 800A2804 8E2F0000 */  lw    $t7, ($s1)
/* 0A3408 800A2808 240E8000 */  li    $t6, -32768
/* 0A340C 800A280C A5EE0340 */  sh    $t6, 0x340($t7)
/* 0A3410 800A2810 8E030000 */  lw    $v1, ($s0)
/* 0A3414 800A2814 00000000 */  nop   
/* 0A3418 800A2818 8C640050 */  lw    $a0, 0x50($v1)
/* 0A341C 800A281C 00000000 */  nop   
/* 0A3420 800A2820 10800004 */  beqz  $a0, .L800A2834
/* 0A3424 800A2824 00000000 */   nop   
/* 0A3428 800A2828 A4800018 */  sh    $zero, 0x18($a0)
/* 0A342C 800A282C 8E030000 */  lw    $v1, ($s0)
/* 0A3430 800A2830 00000000 */  nop   
.L800A2834:
/* 0A3434 800A2834 8C780088 */  lw    $t8, 0x88($v1)
/* 0A3438 800A2838 3C118012 */  lui   $s1, %hi(D_80126CDC) # $s1, 0x8012
/* 0A343C 800A283C 17000016 */  bnez  $t8, .L800A2898
/* 0A3440 800A2840 26316CDC */   addiu $s1, %lo(D_80126CDC) # addiu $s1, $s1, 0x6cdc
/* 0A3444 800A2844 3C198012 */  lui   $t9, %hi(D_80126CF0) # $t9, 0x8012
/* 0A3448 800A2848 8F396CF0 */  lw    $t9, %lo(D_80126CF0)($t9)
/* 0A344C 800A284C 240C0008 */  li    $t4, 8
/* 0A3450 800A2850 872B0044 */  lh    $t3, 0x44($t9)
/* 0A3454 800A2854 A3AC0089 */  sb    $t4, 0x89($sp)
/* 0A3458 800A2858 A7A0008A */  sh    $zero, 0x8a($sp)
/* 0A345C 800A285C A7A0008C */  sh    $zero, 0x8c($sp)
/* 0A3460 800A2860 A7A0008E */  sh    $zero, 0x8e($sp)
/* 0A3464 800A2864 AFA900A8 */  sw    $t1, 0xa8($sp)
/* 0A3468 800A2868 27A40088 */  addiu $a0, $sp, 0x88
/* 0A346C 800A286C 00002825 */  move  $a1, $zero
/* 0A3470 800A2870 0C003A95 */  jal   spawn_object
/* 0A3474 800A2874 A3AB0088 */   sb    $t3, 0x88($sp)
/* 0A3478 800A2878 8E0D0000 */  lw    $t5, ($s0)
/* 0A347C 800A287C 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A3480 800A2880 ADA20088 */  sw    $v0, 0x88($t5)
/* 0A3484 800A2884 8E2F0000 */  lw    $t7, ($s1)
/* 0A3488 800A2888 240E8000 */  li    $t6, -32768
/* 0A348C 800A288C A5EE0440 */  sh    $t6, 0x440($t7)
/* 0A3490 800A2890 8E030000 */  lw    $v1, ($s0)
/* 0A3494 800A2894 00000000 */  nop   
.L800A2898:
/* 0A3498 800A2898 8C700050 */  lw    $s0, 0x50($v1)
/* 0A349C 800A289C 3C128012 */  lui   $s2, %hi(D_80126D67) # $s2, 0x8012
/* 0A34A0 800A28A0 12000384 */  beqz  $s0, .L800A36B4
/* 0A34A4 800A28A4 26526D67 */   addiu $s2, %lo(D_80126D67) # addiu $s2, $s2, 0x6d67
/* 0A34A8 800A28A8 92580000 */  lbu   $t8, ($s2)
/* 0A34AC 800A28AC 8E190068 */  lw    $t9, 0x68($s0)
/* 0A34B0 800A28B0 A218003B */  sb    $t8, 0x3b($s0)
/* 0A34B4 800A28B4 8F2A0000 */  lw    $t2, ($t9)
/* 0A34B8 800A28B8 8FAB00C8 */  lw    $t3, 0xc8($sp)
/* 0A34BC 800A28BC AFAA0098 */  sw    $t2, 0x98($sp)
/* 0A34C0 800A28C0 8D4D0000 */  lw    $t5, ($t2)
/* 0A34C4 800A28C4 240100FF */  li    $at, 255
/* 0A34C8 800A28C8 A5AB0052 */  sh    $t3, 0x52($t5)
/* 0A34CC 800A28CC 92420000 */  lbu   $v0, ($s2)
/* 0A34D0 800A28D0 00000000 */  nop   
/* 0A34D4 800A28D4 104100A4 */  beq   $v0, $at, .L800A2B68
/* 0A34D8 800A28D8 24010004 */   li    $at, 4
/* 0A34DC 800A28DC 1441000D */  bne   $v0, $at, .L800A2914
/* 0A34E0 800A28E0 00000000 */   nop   
/* 0A34E4 800A28E4 0C0044E7 */  jal   func_8001139C
/* 0A34E8 800A28E8 AFA900A8 */   sw    $t1, 0xa8($sp)
/* 0A34EC 800A28EC 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A34F0 800A28F0 14400006 */  bnez  $v0, .L800A290C
/* 0A34F4 800A28F4 240E0010 */   li    $t6, 16
/* 0A34F8 800A28F8 0C000572 */  jal   music_is_playing
/* 0A34FC 800A28FC AFA900A8 */   sw    $t1, 0xa8($sp)
/* 0A3500 800A2900 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A3504 800A2904 14400003 */  bnez  $v0, .L800A2914
/* 0A3508 800A2908 240E0010 */   li    $t6, 16
.L800A290C:
/* 0A350C 800A290C 10000091 */  b     .L800A2B54
/* 0A3510 800A2910 A60E0018 */   sh    $t6, 0x18($s0)
.L800A2914:
/* 0A3514 800A2914 924F0000 */  lbu   $t7, ($s2)
/* 0A3518 800A2918 24010004 */  li    $at, 4
/* 0A351C 800A291C 15E10042 */  bne   $t7, $at, .L800A2A28
/* 0A3520 800A2920 00000000 */   nop   
/* 0A3524 800A2924 0C00057E */  jal   audio_get_chr_select_anim_frac
/* 0A3528 800A2928 AFA900A8 */   sw    $t1, 0xa8($sp)
/* 0A352C 800A292C 8FB80098 */  lw    $t8, 0x98($sp)
/* 0A3530 800A2930 924C0000 */  lbu   $t4, ($s2)
/* 0A3534 800A2934 8F190000 */  lw    $t9, ($t8)
/* 0A3538 800A2938 000C58C0 */  sll   $t3, $t4, 3
/* 0A353C 800A293C 8F2A0044 */  lw    $t2, 0x44($t9)
/* 0A3540 800A2940 3C01BFF0 */  li    $at, 0xBFF00000 # -1.875000
/* 0A3544 800A2944 014B6821 */  addu  $t5, $t2, $t3
/* 0A3548 800A2948 8DA20004 */  lw    $v0, 4($t5)
/* 0A354C 800A294C 44812800 */  mtc1  $at, $f5
/* 0A3550 800A2950 44802000 */  mtc1  $zero, $f4
/* 0A3554 800A2954 46000321 */  cvt.d.s $f12, $f0
/* 0A3558 800A2958 462C2032 */  c.eq.d $f4, $f12
/* 0A355C 800A295C 2442FFFF */  addiu $v0, $v0, -1
/* 0A3560 800A2960 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A3564 800A2964 00027100 */  sll   $t6, $v0, 4
/* 0A3568 800A2968 45000003 */  bc1f  .L800A2978
/* 0A356C 800A296C 01C01025 */   move  $v0, $t6
/* 0A3570 800A2970 10000078 */  b     .L800A2B54
/* 0A3574 800A2974 A6000018 */   sh    $zero, 0x18($s0)
.L800A2978:
/* 0A3578 800A2978 3C013FE0 */  li    $at, 0x3FE00000 # 1.750000
/* 0A357C 800A297C 44819800 */  mtc1  $at, $f19
/* 0A3580 800A2980 44809000 */  mtc1  $zero, $f18
/* 0A3584 800A2984 3C014000 */  li    $at, 0x40000000 # 2.000000
/* 0A3588 800A2988 462C903C */  c.lt.d $f18, $f12
/* 0A358C 800A298C 00000000 */  nop   
/* 0A3590 800A2990 45000015 */  bc1f  .L800A29E8
/* 0A3594 800A2994 00000000 */   nop   
/* 0A3598 800A2998 46326181 */  sub.d $f6, $f12, $f18
/* 0A359C 800A299C 44825000 */  mtc1  $v0, $f10
/* 0A35A0 800A29A0 462033A0 */  cvt.s.d $f14, $f6
/* 0A35A4 800A29A4 460070A1 */  cvt.d.s $f2, $f14
/* 0A35A8 800A29A8 46221200 */  add.d $f8, $f2, $f2
/* 0A35AC 800A29AC 46805420 */  cvt.s.w $f16, $f10
/* 0A35B0 800A29B0 462043A0 */  cvt.s.d $f14, $f8
/* 0A35B4 800A29B4 46107102 */  mul.s $f4, $f14, $f16
/* 0A35B8 800A29B8 46048181 */  sub.s $f6, $f16, $f4
/* 0A35BC 800A29BC 444FF800 */  cfc1  $t7, $31
/* 0A35C0 800A29C0 00000000 */  nop   
/* 0A35C4 800A29C4 35E10003 */  ori   $at, $t7, 3
/* 0A35C8 800A29C8 38210002 */  xori  $at, $at, 2
/* 0A35CC 800A29CC 44C1F800 */  ctc1  $at, $31
/* 0A35D0 800A29D0 00000000 */  nop   
/* 0A35D4 800A29D4 46003224 */  cvt.w.s $f8, $f6
/* 0A35D8 800A29D8 44184000 */  mfc1  $t8, $f8
/* 0A35DC 800A29DC 44CFF800 */  ctc1  $t7, $31
/* 0A35E0 800A29E0 1000005C */  b     .L800A2B54
/* 0A35E4 800A29E4 A6180018 */   sh    $t8, 0x18($s0)
.L800A29E8:
/* 0A35E8 800A29E8 44815000 */  mtc1  $at, $f10
/* 0A35EC 800A29EC 44822000 */  mtc1  $v0, $f4
/* 0A35F0 800A29F0 460A0382 */  mul.s $f14, $f0, $f10
/* 0A35F4 800A29F4 468021A0 */  cvt.s.w $f6, $f4
/* 0A35F8 800A29F8 460E3202 */  mul.s $f8, $f6, $f14
/* 0A35FC 800A29FC 4459F800 */  cfc1  $t9, $31
/* 0A3600 800A2A00 00000000 */  nop   
/* 0A3604 800A2A04 37210003 */  ori   $at, $t9, 3
/* 0A3608 800A2A08 38210002 */  xori  $at, $at, 2
/* 0A360C 800A2A0C 44C1F800 */  ctc1  $at, $31
/* 0A3610 800A2A10 00000000 */  nop   
/* 0A3614 800A2A14 460042A4 */  cvt.w.s $f10, $f8
/* 0A3618 800A2A18 440C5000 */  mfc1  $t4, $f10
/* 0A361C 800A2A1C 44D9F800 */  ctc1  $t9, $31
/* 0A3620 800A2A20 1000004C */  b     .L800A2B54
/* 0A3624 800A2A24 A60C0018 */   sh    $t4, 0x18($s0)
.L800A2A28:
/* 0A3628 800A2A28 0C01BAA8 */  jal   is_game_paused
/* 0A362C 800A2A2C AFA900A8 */   sw    $t1, 0xa8($sp)
/* 0A3630 800A2A30 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A3634 800A2A34 14400047 */  bnez  $v0, .L800A2B54
/* 0A3638 800A2A38 3C058012 */   lui   $a1, %hi(D_80126D69) # $a1, 0x8012
/* 0A363C 800A2A3C 24A56D69 */  addiu $a1, %lo(D_80126D69) # addiu $a1, $a1, 0x6d69
/* 0A3640 800A2A40 80A20000 */  lb    $v0, ($a1)
/* 0A3644 800A2A44 8FAC00C8 */  lw    $t4, 0xc8($sp)
/* 0A3648 800A2A48 04410012 */  bgez  $v0, .L800A2A94
/* 0A364C 800A2A4C 00000000 */   nop   
/* 0A3650 800A2A50 8FAA00C8 */  lw    $t2, 0xc8($sp)
/* 0A3654 800A2A54 86040018 */  lh    $a0, 0x18($s0)
/* 0A3658 800A2A58 01420019 */  multu $t2, $v0
/* 0A365C 800A2A5C 240E0001 */  li    $t6, 1
/* 0A3660 800A2A60 00001812 */  mflo  $v1
/* 0A3664 800A2A64 00035823 */  negu  $t3, $v1
/* 0A3668 800A2A68 0164082A */  slt   $at, $t3, $a0
/* 0A366C 800A2A6C 10200003 */  beqz  $at, .L800A2A7C
/* 0A3670 800A2A70 00836821 */   addu  $t5, $a0, $v1
/* 0A3674 800A2A74 10000037 */  b     .L800A2B54
/* 0A3678 800A2A78 A60D0018 */   sh    $t5, 0x18($s0)
.L800A2A7C:
/* 0A367C 800A2A7C A60E0018 */  sh    $t6, 0x18($s0)
/* 0A3680 800A2A80 80AF0000 */  lb    $t7, ($a1)
/* 0A3684 800A2A84 00000000 */  nop   
/* 0A3688 800A2A88 000FC023 */  negu  $t8, $t7
/* 0A368C 800A2A8C 10000031 */  b     .L800A2B54
/* 0A3690 800A2A90 A0B80000 */   sb    $t8, ($a1)
.L800A2A94:
/* 0A3694 800A2A94 01820019 */  multu $t4, $v0
/* 0A3698 800A2A98 86190018 */  lh    $t9, 0x18($s0)
/* 0A369C 800A2A9C 00005012 */  mflo  $t2
/* 0A36A0 800A2AA0 032A5821 */  addu  $t3, $t9, $t2
/* 0A36A4 800A2AA4 A60B0018 */  sh    $t3, 0x18($s0)
/* 0A36A8 800A2AA8 8FAD0098 */  lw    $t5, 0x98($sp)
/* 0A36AC 800A2AAC 92580000 */  lbu   $t8, ($s2)
/* 0A36B0 800A2AB0 8DAE0000 */  lw    $t6, ($t5)
/* 0A36B4 800A2AB4 001860C0 */  sll   $t4, $t8, 3
/* 0A36B8 800A2AB8 8DCF0044 */  lw    $t7, 0x44($t6)
/* 0A36BC 800A2ABC 860B0018 */  lh    $t3, 0x18($s0)
/* 0A36C0 800A2AC0 01ECC821 */  addu  $t9, $t7, $t4
/* 0A36C4 800A2AC4 8F230004 */  lw    $v1, 4($t9)
/* 0A36C8 800A2AC8 3C0D8012 */  lui   $t5, %hi(D_80126D68) # $t5, 0x8012
/* 0A36CC 800A2ACC 2463FFFF */  addiu $v1, $v1, -1
/* 0A36D0 800A2AD0 00035100 */  sll   $t2, $v1, 4
/* 0A36D4 800A2AD4 016A082A */  slt   $at, $t3, $t2
/* 0A36D8 800A2AD8 1420001F */  bnez  $at, .L800A2B58
/* 0A36DC 800A2ADC 02002025 */   move  $a0, $s0
/* 0A36E0 800A2AE0 91AD6D68 */  lbu   $t5, %lo(D_80126D68)($t5)
/* 0A36E4 800A2AE4 00000000 */  nop   
/* 0A36E8 800A2AE8 11A00007 */  beqz  $t5, .L800A2B08
/* 0A36EC 800A2AEC 00000000 */   nop   
/* 0A36F0 800A2AF0 80AE0000 */  lb    $t6, ($a1)
/* 0A36F4 800A2AF4 254FFFFF */  addiu $t7, $t2, -1
/* 0A36F8 800A2AF8 000EC023 */  negu  $t8, $t6
/* 0A36FC 800A2AFC A0B80000 */  sb    $t8, ($a1)
/* 0A3700 800A2B00 10000014 */  b     .L800A2B54
/* 0A3704 800A2B04 A60F0018 */   sh    $t7, 0x18($s0)
.L800A2B08:
/* 0A3708 800A2B08 A6000018 */  sh    $zero, 0x18($s0)
/* 0A370C 800A2B0C 8FAC00A0 */  lw    $t4, 0xa0($sp)
/* 0A3710 800A2B10 00000000 */  nop   
/* 0A3714 800A2B14 919901FC */  lbu   $t9, 0x1fc($t4)
/* 0A3718 800A2B18 00000000 */  nop   
/* 0A371C 800A2B1C 1720000E */  bnez  $t9, .L800A2B58
/* 0A3720 800A2B20 02002025 */   move  $a0, $s0
/* 0A3724 800A2B24 818A01D8 */  lb    $t2, 0x1d8($t4)
/* 0A3728 800A2B28 24040004 */  li    $a0, 4
/* 0A372C 800A2B2C 15400009 */  bnez  $t2, .L800A2B54
/* 0A3730 800A2B30 00002825 */   move  $a1, $zero
/* 0A3734 800A2B34 240B0001 */  li    $t3, 1
/* 0A3738 800A2B38 AFAB0010 */  sw    $t3, 0x10($sp)
/* 0A373C 800A2B3C 24060004 */  li    $a2, 4
/* 0A3740 800A2B40 24070001 */  li    $a3, 1
/* 0A3744 800A2B44 0C028DB3 */  jal   func_800A36CC
/* 0A3748 800A2B48 AFA900A8 */   sw    $t1, 0xa8($sp)
/* 0A374C 800A2B4C 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A3750 800A2B50 00000000 */  nop   
.L800A2B54:
/* 0A3754 800A2B54 02002025 */  move  $a0, $s0
.L800A2B58:
/* 0A3758 800A2B58 0C01874C */  jal   func_80061D30
/* 0A375C 800A2B5C AFA900A8 */   sw    $t1, 0xa8($sp)
/* 0A3760 800A2B60 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A3764 800A2B64 00000000 */  nop   
.L800A2B68:
/* 0A3768 800A2B68 8E270000 */  lw    $a3, ($s1)
/* 0A376C 800A2B6C 3C128012 */  lui   $s2, %hi(gHUDCurrDisplayList) # $s2, 0x8012
/* 0A3770 800A2B70 26526CFC */  addiu $s2, %lo(gHUDCurrDisplayList) # addiu $s2, $s2, 0x6cfc
/* 0A3774 800A2B74 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A3778 800A2B78 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A377C 800A2B7C 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A3780 800A2B80 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A3784 800A2B84 02402025 */  move  $a0, $s2
/* 0A3788 800A2B88 AFA900A8 */  sw    $t1, 0xa8($sp)
/* 0A378C 800A2B8C 0C02A980 */  jal   func_800AA600
/* 0A3790 800A2B90 24E70340 */   addiu $a3, $a3, 0x340
/* 0A3794 800A2B94 8FA500A0 */  lw    $a1, 0xa0($sp)
/* 0A3798 800A2B98 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A379C 800A2B9C 80A30193 */  lb    $v1, 0x193($a1)
/* 0A37A0 800A2BA0 00004025 */  move  $t0, $zero
/* 0A37A4 800A2BA4 0460000C */  bltz  $v1, .L800A2BD8
/* 0A37A8 800A2BA8 3C188000 */   lui   $t8, %hi(osTvType) # $t8, 0x8000
/* 0A37AC 800A2BAC 00086880 */  sll   $t5, $t0, 2
/* 0A37B0 800A2BB0 00AD8021 */  addu  $s0, $a1, $t5
/* 0A37B4 800A2BB4 24020005 */  li    $v0, 5
.L800A2BB8:
/* 0A37B8 800A2BB8 8E0E0128 */  lw    $t6, 0x128($s0)
/* 0A37BC 800A2BBC 25080001 */  addiu $t0, $t0, 1
/* 0A37C0 800A2BC0 0068082A */  slt   $at, $v1, $t0
/* 0A37C4 800A2BC4 26100004 */  addiu $s0, $s0, 4
/* 0A37C8 800A2BC8 14200003 */  bnez  $at, .L800A2BD8
/* 0A37CC 800A2BCC 012E4821 */   addu  $t1, $t1, $t6
/* 0A37D0 800A2BD0 1502FFF9 */  bne   $t0, $v0, .L800A2BB8
/* 0A37D4 800A2BD4 00000000 */   nop   
.L800A2BD8:
/* 0A37D8 800A2BD8 8F180300 */  lw    $t8, %lo(osTvType)($t8)
/* 0A37DC 800A2BDC 34048CA0 */  li    $a0, 36000
/* 0A37E0 800A2BE0 17000012 */  bnez  $t8, .L800A2C2C
/* 0A37E4 800A2BE4 00000000 */   nop   
/* 0A37E8 800A2BE8 44892000 */  mtc1  $t1, $f4
/* 0A37EC 800A2BEC 3C01800F */  lui   $at, %hi(D_800E8738 + 4) # $at, 0x800f
/* 0A37F0 800A2BF0 468021A0 */  cvt.s.w $f6, $f4
/* 0A37F4 800A2BF4 C42B8738 */  lwc1  $f11, %lo(D_800E8738)($at)
/* 0A37F8 800A2BF8 C42A873C */  lwc1  $f10, %lo(D_800E8738 + 4)($at)
/* 0A37FC 800A2BFC 46003221 */  cvt.d.s $f8, $f6
/* 0A3800 800A2C00 462A4102 */  mul.d $f4, $f8, $f10
/* 0A3804 800A2C04 444FF800 */  cfc1  $t7, $31
/* 0A3808 800A2C08 00000000 */  nop   
/* 0A380C 800A2C0C 35E10003 */  ori   $at, $t7, 3
/* 0A3810 800A2C10 38210002 */  xori  $at, $at, 2
/* 0A3814 800A2C14 44C1F800 */  ctc1  $at, $31
/* 0A3818 800A2C18 00000000 */  nop   
/* 0A381C 800A2C1C 462021A4 */  cvt.w.d $f6, $f4
/* 0A3820 800A2C20 44CFF800 */  ctc1  $t7, $31
/* 0A3824 800A2C24 44093000 */  mfc1  $t1, $f6
/* 0A3828 800A2C28 00000000 */  nop   
.L800A2C2C:
/* 0A382C 800A2C2C 0C00322D */  jal   normalise_time
/* 0A3830 800A2C30 AFA900A8 */   sw    $t1, 0xa8($sp)
/* 0A3834 800A2C34 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A3838 800A2C38 00000000 */  nop   
/* 0A383C 800A2C3C 0049082A */  slt   $at, $v0, $t1
/* 0A3840 800A2C40 10200005 */  beqz  $at, .L800A2C58
/* 0A3844 800A2C44 24100444 */   li    $s0, 1092
/* 0A3848 800A2C48 0C00322D */  jal   normalise_time
/* 0A384C 800A2C4C 34048CA0 */   li    $a0, 36000
/* 0A3850 800A2C50 00404825 */  move  $t1, $v0
/* 0A3854 800A2C54 24100444 */  li    $s0, 1092
.L800A2C58:
/* 0A3858 800A2C58 01300019 */  multu $t1, $s0
/* 0A385C 800A2C5C 8E2A0000 */  lw    $t2, ($s1)
/* 0A3860 800A2C60 0000C812 */  mflo  $t9
/* 0A3864 800A2C64 272C7FF8 */  addiu $t4, $t9, 0x7ff8
/* 0A3868 800A2C68 A54C0444 */  sh    $t4, 0x444($t2)
/* 0A386C 800A2C6C 0C00382C */  jal   func_8000E0B0
/* 0A3870 800A2C70 AFA900A8 */   sw    $t1, 0xa8($sp)
/* 0A3874 800A2C74 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A3878 800A2C78 1C40000D */  bgtz  $v0, .L800A2CB0
/* 0A387C 800A2C7C 2403003C */   li    $v1, 60
/* 0A3880 800A2C80 8E270000 */  lw    $a3, ($s1)
/* 0A3884 800A2C84 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A3888 800A2C88 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A388C 800A2C8C 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A3890 800A2C90 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A3894 800A2C94 02402025 */  move  $a0, $s2
/* 0A3898 800A2C98 AFA900A8 */  sw    $t1, 0xa8($sp)
/* 0A389C 800A2C9C 0C02A980 */  jal   func_800AA600
/* 0A38A0 800A2CA0 24E70440 */   addiu $a3, $a3, 0x440
/* 0A38A4 800A2CA4 8FA900A8 */  lw    $t1, 0xa8($sp)
/* 0A38A8 800A2CA8 00000000 */  nop   
/* 0A38AC 800A2CAC 2403003C */  li    $v1, 60
.L800A2CB0:
/* 0A38B0 800A2CB0 0123001A */  div   $zero, $t1, $v1
/* 0A38B4 800A2CB4 8E380000 */  lw    $t8, ($s1)
/* 0A38B8 800A2CB8 14600002 */  bnez  $v1, .L800A2CC4
/* 0A38BC 800A2CBC 00000000 */   nop   
/* 0A38C0 800A2CC0 0007000D */  break 7
.L800A2CC4:
/* 0A38C4 800A2CC4 2401FFFF */  li    $at, -1
/* 0A38C8 800A2CC8 14610004 */  bne   $v1, $at, .L800A2CDC
/* 0A38CC 800A2CCC 3C018000 */   lui   $at, 0x8000
/* 0A38D0 800A2CD0 15210002 */  bne   $t1, $at, .L800A2CDC
/* 0A38D4 800A2CD4 00000000 */   nop   
/* 0A38D8 800A2CD8 0006000D */  break 6
.L800A2CDC:
/* 0A38DC 800A2CDC 00005812 */  mflo  $t3
/* 0A38E0 800A2CE0 256D001E */  addiu $t5, $t3, 0x1e
/* 0A38E4 800A2CE4 00000000 */  nop   
/* 0A38E8 800A2CE8 01A3001A */  div   $zero, $t5, $v1
/* 0A38EC 800A2CEC 14600002 */  bnez  $v1, .L800A2CF8
/* 0A38F0 800A2CF0 00000000 */   nop   
/* 0A38F4 800A2CF4 0007000D */  break 7
.L800A2CF8:
/* 0A38F8 800A2CF8 2401FFFF */  li    $at, -1
/* 0A38FC 800A2CFC 14610004 */  bne   $v1, $at, .L800A2D10
/* 0A3900 800A2D00 3C018000 */   lui   $at, 0x8000
/* 0A3904 800A2D04 15A10002 */  bne   $t5, $at, .L800A2D10
/* 0A3908 800A2D08 00000000 */   nop   
/* 0A390C 800A2D0C 0006000D */  break 6
.L800A2D10:
/* 0A3910 800A2D10 3C0141E0 */  li    $at, 0x41E00000 # 28.000000
/* 0A3914 800A2D14 44815000 */  mtc1  $at, $f10
/* 0A3918 800A2D18 00004810 */  mfhi  $t1
/* 0A391C 800A2D1C 00000000 */  nop   
/* 0A3920 800A2D20 00000000 */  nop   
/* 0A3924 800A2D24 01300019 */  multu $t1, $s0
/* 0A3928 800A2D28 00007012 */  mflo  $t6
/* 0A392C 800A2D2C A70E0444 */  sh    $t6, 0x444($t8)
/* 0A3930 800A2D30 8E220000 */  lw    $v0, ($s1)
/* 0A3934 800A2D34 00000000 */  nop   
/* 0A3938 800A2D38 C4480350 */  lwc1  $f8, 0x350($v0)
/* 0A393C 800A2D3C 00000000 */  nop   
/* 0A3940 800A2D40 460A4100 */  add.s $f4, $f8, $f10
/* 0A3944 800A2D44 0C00382C */  jal   func_8000E0B0
/* 0A3948 800A2D48 E4440450 */   swc1  $f4, 0x450($v0)
/* 0A394C 800A2D4C 1C40000A */  bgtz  $v0, .L800A2D78
/* 0A3950 800A2D50 8FAF0098 */   lw    $t7, 0x98($sp)
/* 0A3954 800A2D54 8E270000 */  lw    $a3, ($s1)
/* 0A3958 800A2D58 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A395C 800A2D5C 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A3960 800A2D60 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A3964 800A2D64 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A3968 800A2D68 02402025 */  move  $a0, $s2
/* 0A396C 800A2D6C 0C02A980 */  jal   func_800AA600
/* 0A3970 800A2D70 24E70440 */   addiu $a3, $a3, 0x440
/* 0A3974 800A2D74 8FAF0098 */  lw    $t7, 0x98($sp)
.L800A2D78:
/* 0A3978 800A2D78 24040001 */  li    $a0, 1
/* 0A397C 800A2D7C 0C01A142 */  jal   func_80068508
/* 0A3980 800A2D80 A1E00020 */   sb    $zero, 0x20($t7)
/* 0A3984 800A2D84 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 0A3988 800A2D88 8FA500C8 */  lw    $a1, 0xc8($sp)
/* 0A398C 800A2D8C 0C0283AD */  jal   render_course_indicator_arrows
/* 0A3990 800A2D90 00000000 */   nop   
/* 0A3994 800A2D94 8FA900A0 */  lw    $t1, 0xa0($sp)
/* 0A3998 800A2D98 00000000 */  nop   
/* 0A399C 800A2D9C 813901D8 */  lb    $t9, 0x1d8($t1)
/* 0A39A0 800A2DA0 00000000 */  nop   
/* 0A39A4 800A2DA4 172000CC */  bnez  $t9, .L800A30D8
/* 0A39A8 800A2DA8 00000000 */   nop   
/* 0A39AC 800A2DAC 444AF800 */  cfc1  $t2, $31
/* 0A39B0 800A2DB0 8E2C0000 */  lw    $t4, ($s1)
/* 0A39B4 800A2DB4 35410003 */  ori   $at, $t2, 3
/* 0A39B8 800A2DB8 38210002 */  xori  $at, $at, 2
/* 0A39BC 800A2DBC 44C1F800 */  ctc1  $at, $31
/* 0A39C0 800A2DC0 C58602F0 */  lwc1  $f6, 0x2f0($t4)
/* 0A39C4 800A2DC4 00004025 */  move  $t0, $zero
/* 0A39C8 800A2DC8 46003224 */  cvt.w.s $f8, $f6
/* 0A39CC 800A2DCC 3C0E8012 */  lui   $t6, %hi(D_80126D60) # $t6, 0x8012
/* 0A39D0 800A2DD0 440B4000 */  mfc1  $t3, $f8
/* 0A39D4 800A2DD4 44CAF800 */  ctc1  $t2, $31
/* 0A39D8 800A2DD8 AFAB00B8 */  sw    $t3, 0xb8($sp)
/* 0A39DC 800A2DDC 812D0194 */  lb    $t5, 0x194($t1)
/* 0A39E0 800A2DE0 00000000 */  nop   
/* 0A39E4 800A2DE4 19A00067 */  blez  $t5, .L800A2F84
/* 0A39E8 800A2DE8 00086880 */   sll   $t5, $t0, 2
/* 0A39EC 800A2DEC 8DCE6D60 */  lw    $t6, %lo(D_80126D60)($t6)
/* 0A39F0 800A2DF0 00001080 */  sll   $v0, $zero, 2
/* 0A39F4 800A2DF4 81D8004B */  lb    $t8, 0x4b($t6)
/* 0A39F8 800A2DF8 01228021 */  addu  $s0, $t1, $v0
/* 0A39FC 800A2DFC 1B000060 */  blez  $t8, .L800A2F80
/* 0A3A00 800A2E00 3C0F800E */   lui   $t7, %hi(D_800E27AC) # $t7, 0x800e
/* 0A3A04 800A2E04 25EF27AC */  addiu $t7, %lo(D_800E27AC) # addiu $t7, $t7, 0x27ac
/* 0A3A08 800A2E08 004FC821 */  addu  $t9, $v0, $t7
/* 0A3A0C 800A2E0C AFB9003C */  sw    $t9, 0x3c($sp)
.L800A2E10:
/* 0A3A10 800A2E10 8E040128 */  lw    $a0, 0x128($s0)
/* 0A3A14 800A2E14 AFA800BC */  sw    $t0, 0xbc($sp)
/* 0A3A18 800A2E18 27A500B4 */  addiu $a1, $sp, 0xb4
/* 0A3A1C 800A2E1C 27A600B0 */  addiu $a2, $sp, 0xb0
/* 0A3A20 800A2E20 0C0165E4 */  jal   get_timestamp_from_frames
/* 0A3A24 800A2E24 27A700AC */   addiu $a3, $sp, 0xac
/* 0A3A28 800A2E28 8FAC003C */  lw    $t4, 0x3c($sp)
/* 0A3A2C 800A2E2C 3C01800E */  lui   $at, %hi(D_800E2834) # $at, 0x800e
/* 0A3A30 800A2E30 8D8A0000 */  lw    $t2, ($t4)
/* 0A3A34 800A2E34 444DF800 */  cfc1  $t5, $31
/* 0A3A38 800A2E38 AC2A2834 */  sw    $t2, %lo(D_800E2834)($at)
/* 0A3A3C 800A2E3C 8E2B0000 */  lw    $t3, ($s1)
/* 0A3A40 800A2E40 35A10003 */  ori   $at, $t5, 3
/* 0A3A44 800A2E44 38210002 */  xori  $at, $at, 2
/* 0A3A48 800A2E48 44C1F800 */  ctc1  $at, $31
/* 0A3A4C 800A2E4C C56A02EC */  lwc1  $f10, 0x2ec($t3)
/* 0A3A50 800A2E50 8FAE00AC */  lw    $t6, 0xac($sp)
/* 0A3A54 800A2E54 46005124 */  cvt.w.s $f4, $f10
/* 0A3A58 800A2E58 8FA500B8 */  lw    $a1, 0xb8($sp)
/* 0A3A5C 800A2E5C 44042000 */  mfc1  $a0, $f4
/* 0A3A60 800A2E60 8FA600B4 */  lw    $a2, 0xb4($sp)
/* 0A3A64 800A2E64 8FA700B0 */  lw    $a3, 0xb0($sp)
/* 0A3A68 800A2E68 24180001 */  li    $t8, 1
/* 0A3A6C 800A2E6C 44CDF800 */  ctc1  $t5, $31
/* 0A3A70 800A2E70 AFB80014 */  sw    $t8, 0x14($sp)
/* 0A3A74 800A2E74 0C029FEF */  jal   func_800A7FBC
/* 0A3A78 800A2E78 AFAE0010 */   sw    $t6, 0x10($sp)
/* 0A3A7C 800A2E7C 240FFFFE */  li    $t7, -2
/* 0A3A80 800A2E80 3C01800E */  lui   $at, %hi(D_800E2834) # $at, 0x800e
/* 0A3A84 800A2E84 AC2F2834 */  sw    $t7, %lo(D_800E2834)($at)
/* 0A3A88 800A2E88 8FB900B8 */  lw    $t9, 0xb8($sp)
/* 0A3A8C 800A2E8C 8E430000 */  lw    $v1, ($s2)
/* 0A3A90 800A2E90 272C000C */  addiu $t4, $t9, 0xc
/* 0A3A94 800A2E94 246A0008 */  addiu $t2, $v1, 8
/* 0A3A98 800A2E98 8FA800BC */  lw    $t0, 0xbc($sp)
/* 0A3A9C 800A2E9C AFAC00B8 */  sw    $t4, 0xb8($sp)
/* 0A3AA0 800A2EA0 AE4A0000 */  sw    $t2, ($s2)
/* 0A3AA4 800A2EA4 3C0BFA00 */  lui   $t3, 0xfa00
/* 0A3AA8 800A2EA8 240DFFFF */  li    $t5, -1
/* 0A3AAC 800A2EAC AC6D0004 */  sw    $t5, 4($v1)
/* 0A3AB0 800A2EB0 AC6B0000 */  sw    $t3, ($v1)
/* 0A3AB4 800A2EB4 8E2E0000 */  lw    $t6, ($s1)
/* 0A3AB8 800A2EB8 25090001 */  addiu $t1, $t0, 1
/* 0A3ABC 800A2EBC A5C90338 */  sh    $t1, 0x338($t6)
/* 0A3AC0 800A2EC0 8E270000 */  lw    $a3, ($s1)
/* 0A3AC4 800A2EC4 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A3AC8 800A2EC8 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A3ACC 800A2ECC 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A3AD0 800A2ED0 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A3AD4 800A2ED4 AFA90050 */  sw    $t1, 0x50($sp)
/* 0A3AD8 800A2ED8 02402025 */  move  $a0, $s2
/* 0A3ADC 800A2EDC 0C02A980 */  jal   func_800AA600
/* 0A3AE0 800A2EE0 24E70320 */   addiu $a3, $a3, 0x320
/* 0A3AE4 800A2EE4 8E270000 */  lw    $a3, ($s1)
/* 0A3AE8 800A2EE8 3C058012 */  lui   $a1, %hi(gHUDCurrMatrix) # $a1, 0x8012
/* 0A3AEC 800A2EEC 3C068012 */  lui   $a2, %hi(gHUDCurrVertex) # $a2, 0x8012
/* 0A3AF0 800A2EF0 24C66D04 */  addiu $a2, %lo(gHUDCurrVertex) # addiu $a2, $a2, 0x6d04
/* 0A3AF4 800A2EF4 24A56D00 */  addiu $a1, %lo(gHUDCurrMatrix) # addiu $a1, $a1, 0x6d00
/* 0A3AF8 800A2EF8 02402025 */  move  $a0, $s2
/* 0A3AFC 800A2EFC 0C02A980 */  jal   func_800AA600
/* 0A3B00 800A2F00 24E70300 */   addiu $a3, $a3, 0x300
/* 0A3B04 800A2F04 8E220000 */  lw    $v0, ($s1)
/* 0A3B08 800A2F08 3C014140 */  li    $at, 0x41400000 # 12.000000
/* 0A3B0C 800A2F0C 44810000 */  mtc1  $at, $f0
/* 0A3B10 800A2F10 C4460330 */  lwc1  $f6, 0x330($v0)
/* 0A3B14 800A2F14 26100004 */  addiu $s0, $s0, 4
/* 0A3B18 800A2F18 46003200 */  add.s $f8, $f6, $f0
/* 0A3B1C 800A2F1C 3C0A8012 */  lui   $t2, %hi(D_80126D60) # $t2, 0x8012
/* 0A3B20 800A2F20 E4480330 */  swc1  $f8, 0x330($v0)
/* 0A3B24 800A2F24 8E220000 */  lw    $v0, ($s1)
/* 0A3B28 800A2F28 00000000 */  nop   
/* 0A3B2C 800A2F2C C44A0310 */  lwc1  $f10, 0x310($v0)
/* 0A3B30 800A2F30 00000000 */  nop   
/* 0A3B34 800A2F34 46005100 */  add.s $f4, $f10, $f0
/* 0A3B38 800A2F38 E4440310 */  swc1  $f4, 0x310($v0)
/* 0A3B3C 800A2F3C 8FB8003C */  lw    $t8, 0x3c($sp)
/* 0A3B40 800A2F40 8FB900A0 */  lw    $t9, 0xa0($sp)
/* 0A3B44 800A2F44 270F0004 */  addiu $t7, $t8, 4
/* 0A3B48 800A2F48 AFAF003C */  sw    $t7, 0x3c($sp)
/* 0A3B4C 800A2F4C 8FA80050 */  lw    $t0, 0x50($sp)
/* 0A3B50 800A2F50 832C0194 */  lb    $t4, 0x194($t9)
/* 0A3B54 800A2F54 00000000 */  nop   
/* 0A3B58 800A2F58 010C082A */  slt   $at, $t0, $t4
/* 0A3B5C 800A2F5C 10200009 */  beqz  $at, .L800A2F84
/* 0A3B60 800A2F60 00086880 */   sll   $t5, $t0, 2
/* 0A3B64 800A2F64 8D4A6D60 */  lw    $t2, %lo(D_80126D60)($t2)
/* 0A3B68 800A2F68 00000000 */  nop   
/* 0A3B6C 800A2F6C 814B004B */  lb    $t3, 0x4b($t2)
/* 0A3B70 800A2F70 00000000 */  nop   
/* 0A3B74 800A2F74 010B082A */  slt   $at, $t0, $t3
/* 0A3B78 800A2F78 1420FFA5 */  bnez  $at, .L800A2E10
/* 0A3B7C 800A2F7C 00000000 */   nop   
.L800A2F80:
/* 0A3B80 800A2F80 00086880 */  sll   $t5, $t0, 2
.L800A2F84:
/* 0A3B84 800A2F84 01A86823 */  subu  $t5, $t5, $t0
/* 0A3B88 800A2F88 000D6880 */  sll   $t5, $t5, 2
/* 0A3B8C 800A2F8C 448D3000 */  mtc1  $t5, $f6
/* 0A3B90 800A2F90 8E220000 */  lw    $v0, ($s1)
/* 0A3B94 800A2F94 46803020 */  cvt.s.w $f0, $f6
/* 0A3B98 800A2F98 C4480330 */  lwc1  $f8, 0x330($v0)
/* 0A3B9C 800A2F9C 8FA900A0 */  lw    $t1, 0xa0($sp)
/* 0A3BA0 800A2FA0 46004281 */  sub.s $f10, $f8, $f0
/* 0A3BA4 800A2FA4 3C108012 */  lui   $s0, %hi(D_80126D4C) # $s0, 0x8012
/* 0A3BA8 800A2FA8 E44A0330 */  swc1  $f10, 0x330($v0)
/* 0A3BAC 800A2FAC 8E220000 */  lw    $v0, ($s1)
/* 0A3BB0 800A2FB0 26106D4C */  addiu $s0, %lo(D_80126D4C) # addiu $s0, $s0, 0x6d4c
/* 0A3BB4 800A2FB4 C4440310 */  lwc1  $f4, 0x310($v0)
/* 0A3BB8 800A2FB8 00000000 */  nop   
/* 0A3BBC 800A2FBC 46002181 */  sub.s $f6, $f4, $f0
/* 0A3BC0 800A2FC0 E4460310 */  swc1  $f6, 0x310($v0)
/* 0A3BC4 800A2FC4 912E01EF */  lbu   $t6, 0x1ef($t1)
/* 0A3BC8 800A2FC8 00000000 */  nop   
/* 0A3BCC 800A2FCC 31D80004 */  andi  $t8, $t6, 4
/* 0A3BD0 800A2FD0 13000010 */  beqz  $t8, .L800A3014
/* 0A3BD4 800A2FD4 00000000 */   nop   
/* 0A3BD8 800A2FD8 8E0F0000 */  lw    $t7, ($s0)
/* 0A3BDC 800A2FDC 24040007 */  li    $a0, 7
/* 0A3BE0 800A2FE0 1DE0000C */  bgtz  $t7, .L800A3014
/* 0A3BE4 800A2FE4 24050003 */   li    $a1, 3
/* 0A3BE8 800A2FE8 00003025 */  move  $a2, $zero
/* 0A3BEC 800A2FEC 24070004 */  li    $a3, 4
/* 0A3BF0 800A2FF0 0C028DB3 */  jal   func_800A36CC
/* 0A3BF4 800A2FF4 AFA00010 */   sw    $zero, 0x10($sp)
/* 0A3BF8 800A2FF8 8FA900A0 */  lw    $t1, 0xa0($sp)
/* 0A3BFC 800A2FFC 2419003C */  li    $t9, 60
/* 0A3C00 800A3000 AE190000 */  sw    $t9, ($s0)
/* 0A3C04 800A3004 912A01EF */  lbu   $t2, 0x1ef($t1)
/* 0A3C08 800A3008 00000000 */  nop   
/* 0A3C0C 800A300C 314BFFFB */  andi  $t3, $t2, 0xfffb
/* 0A3C10 800A3010 A12B01EF */  sb    $t3, 0x1ef($t1)
.L800A3014:
/* 0A3C14 800A3014 3C108012 */  lui   $s0, %hi(D_80126D4C) # $s0, 0x8012
/* 0A3C18 800A3018 26106D4C */  addiu $s0, %lo(D_80126D4C) # addiu $s0, $s0, 0x6d4c
/* 0A3C1C 800A301C 8E020000 */  lw    $v0, ($s0)
/* 0A3C20 800A3020 8FAD00C8 */  lw    $t5, 0xc8($sp)
/* 0A3C24 800A3024 18400006 */  blez  $v0, .L800A3040
/* 0A3C28 800A3028 004D7023 */   subu  $t6, $v0, $t5
/* 0A3C2C 800A302C AE0E0000 */  sw    $t6, ($s0)
/* 0A3C30 800A3030 05C10003 */  bgez  $t6, .L800A3040
/* 0A3C34 800A3034 01C01025 */   move  $v0, $t6
/* 0A3C38 800A3038 AE000000 */  sw    $zero, ($s0)
/* 0A3C3C 800A303C 00001025 */  move  $v0, $zero
.L800A3040:
/* 0A3C40 800A3040 14400025 */  bnez  $v0, .L800A30D8
/* 0A3C44 800A3044 00000000 */   nop   
/* 0A3C48 800A3048 813801D8 */  lb    $t8, 0x1d8($t1)
/* 0A3C4C 800A304C 240FFF9C */  li    $t7, -100
/* 0A3C50 800A3050 17000021 */  bnez  $t8, .L800A30D8
/* 0A3C54 800A3054 3C198012 */   lui   $t9, %hi(gHUDVoiceSoundMask) # $t9, 0x8012
/* 0A3C58 800A3058 AE0F0000 */  sw    $t7, ($s0)
/* 0A3C5C 800A305C 8F396D40 */  lw    $t9, %lo(gHUDVoiceSoundMask)($t9)
/* 0A3C60 800A3060 3C108012 */  lui   $s0, %hi(D_80126D64) # $s0, 0x8012
/* 0A3C64 800A3064 1720001C */  bnez  $t9, .L800A30D8
/* 0A3C68 800A3068 26106D64 */   addiu $s0, %lo(D_80126D64) # addiu $s0, $s0, 0x6d64
/* 0A3C6C 800A306C 92050000 */  lbu   $a1, ($s0)
/* 0A3C70 800A3070 00002025 */  move  $a0, $zero
/* 0A3C74 800A3074 0C01BE53 */  jal   get_random_number_from_range
/* 0A3C78 800A3078 24A50002 */   addiu $a1, $a1, 2
/* 0A3C7C 800A307C 3C118012 */  lui   $s1, %hi(D_80126D48) # $s1, 0x8012
/* 0A3C80 800A3080 26316D48 */  addiu $s1, %lo(D_80126D48) # addiu $s1, $s1, 0x6d48
/* 0A3C84 800A3084 962A0000 */  lhu   $t2, ($s1)
/* 0A3C88 800A3088 2443014B */  addiu $v1, $v0, 0x14b
/* 0A3C8C 800A308C 306BFFFF */  andi  $t3, $v1, 0xffff
/* 0A3C90 800A3090 154B000A */  bne   $t2, $t3, .L800A30BC
/* 0A3C94 800A3094 3064FFFF */   andi  $a0, $v1, 0xffff
.L800A3098:
/* 0A3C98 800A3098 92050000 */  lbu   $a1, ($s0)
/* 0A3C9C 800A309C 00002025 */  move  $a0, $zero
/* 0A3CA0 800A30A0 0C01BE53 */  jal   get_random_number_from_range
/* 0A3CA4 800A30A4 24A50002 */   addiu $a1, $a1, 2
/* 0A3CA8 800A30A8 962C0000 */  lhu   $t4, ($s1)
/* 0A3CAC 800A30AC 2443014B */  addiu $v1, $v0, 0x14b
/* 0A3CB0 800A30B0 306DFFFF */  andi  $t5, $v1, 0xffff
/* 0A3CB4 800A30B4 118DFFF8 */  beq   $t4, $t5, .L800A3098
/* 0A3CB8 800A30B8 3064FFFF */   andi  $a0, $v1, 0xffff
.L800A30BC:
/* 0A3CBC 800A30BC 3C058012 */  lui   $a1, %hi(gHUDVoiceSoundMask) # $a1, 0x8012
/* 0A3CC0 800A30C0 A6240000 */  sh    $a0, ($s1)
/* 0A3CC4 800A30C4 0C000741 */  jal   play_sound_global
/* 0A3CC8 800A30C8 24A56D40 */   addiu $a1, %lo(gHUDVoiceSoundMask) # addiu $a1, $a1, 0x6d40
/* 0A3CCC 800A30CC 240E0001 */  li    $t6, 1
/* 0A3CD0 800A30D0 8FA900A0 */  lw    $t1, 0xa0($sp)
/* 0A3CD4 800A30D4 A20E0000 */  sb    $t6, ($s0)
.L800A30D8:
/* 0A3CD8 800A30D8 81230193 */  lb    $v1, 0x193($t1)
/* 0A3CDC 800A30DC 3C118012 */  lui   $s1, %hi(D_80126D48) # $s1, 0x8012
/* 0A3CE0 800A30E0 18600041 */  blez  $v1, .L800A31E8
/* 0A3CE4 800A30E4 26316D48 */   addiu $s1, %lo(D_80126D48) # addiu $s1, $s1, 0x6d48
/* 0A3CE8 800A30E8 3C188012 */  lui   $t8, %hi(D_80126D60) # $t8, 0x8012
/* 0A3CEC 800A30EC 8F186D60 */  lw    $t8, %lo(D_80126D60)($t8)
/* 0A3CF0 800A30F0 0003C880 */  sll   $t9, $v1, 2
/* 0A3CF4 800A30F4 830F004B */  lb    $t7, 0x4b($t8)
/* 0A3CF8 800A30F8 01395021 */  addu  $t2, $t1, $t9
/* 0A3CFC 800A30FC 006F082A */  slt   $at, $v1, $t7
/* 0A3D00 800A3100 10200039 */  beqz  $at, .L800A31E8
/* 0A3D04 800A3104 00000000 */   nop   
/* 0A3D08 800A3108 8D4B0128 */  lw    $t3, 0x128($t2)
/* 0A3D0C 800A310C 3C0C8012 */  lui   $t4, %hi(gHUDVoiceSoundMask) # $t4, 0x8012
/* 0A3D10 800A3110 29610014 */  slti  $at, $t3, 0x14
/* 0A3D14 800A3114 10200034 */  beqz  $at, .L800A31E8
/* 0A3D18 800A3118 00000000 */   nop   
/* 0A3D1C 800A311C 8D8C6D40 */  lw    $t4, %lo(gHUDVoiceSoundMask)($t4)
/* 0A3D20 800A3120 00000000 */  nop   
/* 0A3D24 800A3124 15800030 */  bnez  $t4, .L800A31E8
/* 0A3D28 800A3128 00000000 */   nop   
/* 0A3D2C 800A312C 812D01D6 */  lb    $t5, 0x1d6($t1)
/* 0A3D30 800A3130 00000000 */  nop   
/* 0A3D34 800A3134 29A10003 */  slti  $at, $t5, 3
/* 0A3D38 800A3138 1020002B */  beqz  $at, .L800A31E8
/* 0A3D3C 800A313C 00000000 */   nop   
/* 0A3D40 800A3140 0C01BAA4 */  jal   get_settings
/* 0A3D44 800A3144 00000000 */   nop   
/* 0A3D48 800A3148 3C108012 */  lui   $s0, %hi(D_80127184) # $s0, 0x8012
/* 0A3D4C 800A314C 26107184 */  addiu $s0, %lo(D_80127184) # addiu $s0, $s0, 0x7184
/* 0A3D50 800A3150 0C01AF62 */  jal   func_8006BD88
/* 0A3D54 800A3154 AE020000 */   sw    $v0, ($s0)
/* 0A3D58 800A3158 8FAE00A0 */  lw    $t6, 0xa0($sp)
/* 0A3D5C 800A315C 8E190000 */  lw    $t9, ($s0)
/* 0A3D60 800A3160 81C30193 */  lb    $v1, 0x193($t6)
/* 0A3D64 800A3164 81CA01D6 */  lb    $t2, 0x1d6($t6)
/* 0A3D68 800A3168 0003C080 */  sll   $t8, $v1, 2
/* 0A3D6C 800A316C 000A5880 */  sll   $t3, $t2, 2
/* 0A3D70 800A3170 01D87821 */  addu  $t7, $t6, $t8
/* 0A3D74 800A3174 032B6021 */  addu  $t4, $t9, $t3
/* 0A3D78 800A3178 8D8D0024 */  lw    $t5, 0x24($t4)
/* 0A3D7C 800A317C 8DE40124 */  lw    $a0, 0x124($t7)
/* 0A3D80 800A3180 0002C040 */  sll   $t8, $v0, 1
/* 0A3D84 800A3184 01B87821 */  addu  $t7, $t5, $t8
/* 0A3D88 800A3188 95EA0000 */  lhu   $t2, ($t7)
/* 0A3D8C 800A318C 2465FFFF */  addiu $a1, $v1, -1
/* 0A3D90 800A3190 008A082A */  slt   $at, $a0, $t2
/* 0A3D94 800A3194 10200014 */  beqz  $at, .L800A31E8
/* 0A3D98 800A3198 00000000 */   nop   
/* 0A3D9C 800A319C 18A0000D */  blez  $a1, .L800A31D4
/* 0A3DA0 800A31A0 00804825 */   move  $t1, $a0
/* 0A3DA4 800A31A4 00001025 */  move  $v0, $zero
/* 0A3DA8 800A31A8 01C08025 */  move  $s0, $t6
/* 0A3DAC 800A31AC 00051880 */  sll   $v1, $a1, 2
.L800A31B0:
/* 0A3DB0 800A31B0 8E190128 */  lw    $t9, 0x128($s0)
/* 0A3DB4 800A31B4 24420004 */  addiu $v0, $v0, 4
/* 0A3DB8 800A31B8 0139082A */  slt   $at, $t1, $t9
/* 0A3DBC 800A31BC 14200003 */  bnez  $at, .L800A31CC
/* 0A3DC0 800A31C0 0043082A */   slt   $at, $v0, $v1
/* 0A3DC4 800A31C4 00004825 */  move  $t1, $zero
/* 0A3DC8 800A31C8 0043082A */  slt   $at, $v0, $v1
.L800A31CC:
/* 0A3DCC 800A31CC 1420FFF8 */  bnez  $at, .L800A31B0
/* 0A3DD0 800A31D0 26100004 */   addiu $s0, $s0, 4
.L800A31D4:
/* 0A3DD4 800A31D4 11200004 */  beqz  $t1, .L800A31E8
/* 0A3DD8 800A31D8 24040144 */   li    $a0, 324
/* 0A3DDC 800A31DC 3C058012 */  lui   $a1, %hi(gHUDVoiceSoundMask) # $a1, 0x8012
/* 0A3DE0 800A31E0 0C000741 */  jal   play_sound_global
/* 0A3DE4 800A31E4 24A56D40 */   addiu $a1, %lo(gHUDVoiceSoundMask) # addiu $a1, $a1, 0x6d40
.L800A31E8:
/* 0A3DE8 800A31E8 0C006CA2 */  jal   func_8001B288
/* 0A3DEC 800A31EC 00000000 */   nop   
/* 0A3DF0 800A31F0 1040004F */  beqz  $v0, .L800A3330
/* 0A3DF4 800A31F4 8FAA00A0 */   lw    $t2, 0xa0($sp)
/* 0A3DF8 800A31F8 0C006CB8 */  jal   func_8001B2E0
/* 0A3DFC 800A31FC 00000000 */   nop   
/* 0A3E00 800A3200 1040004A */  beqz  $v0, .L800A332C
/* 0A3E04 800A3204 00408025 */   move  $s0, $v0
/* 0A3E08 800A3208 0C0044E7 */  jal   func_8001139C
/* 0A3E0C 800A320C 00000000 */   nop   
/* 0A3E10 800A3210 14400047 */  bnez  $v0, .L800A3330
/* 0A3E14 800A3214 8FAA00A0 */   lw    $t2, 0xa0($sp)
/* 0A3E18 800A3218 8FAB00A0 */  lw    $t3, 0xa0($sp)
/* 0A3E1C 800A321C 8FAD00C4 */  lw    $t5, 0xc4($sp)
/* 0A3E20 800A3220 816C01D8 */  lb    $t4, 0x1d8($t3)
/* 0A3E24 800A3224 00000000 */  nop   
/* 0A3E28 800A3228 15800041 */  bnez  $t4, .L800A3330
/* 0A3E2C 800A322C 8FAA00A0 */   lw    $t2, 0xa0($sp)
/* 0A3E30 800A3230 C608000C */  lwc1  $f8, 0xc($s0)
/* 0A3E34 800A3234 C5AA000C */  lwc1  $f10, 0xc($t5)
/* 0A3E38 800A3238 C6040010 */  lwc1  $f4, 0x10($s0)
/* 0A3E3C 800A323C C5A60010 */  lwc1  $f6, 0x10($t5)
/* 0A3E40 800A3240 460A4001 */  sub.s $f0, $f8, $f10
/* 0A3E44 800A3244 C5AA0014 */  lwc1  $f10, 0x14($t5)
/* 0A3E48 800A3248 46062081 */  sub.s $f2, $f4, $f6
/* 0A3E4C 800A324C C6080014 */  lwc1  $f8, 0x14($s0)
/* 0A3E50 800A3250 46000102 */  mul.s $f4, $f0, $f0
/* 0A3E54 800A3254 460A4381 */  sub.s $f14, $f8, $f10
/* 0A3E58 800A3258 46021182 */  mul.s $f6, $f2, $f2
/* 0A3E5C 800A325C 00000000 */  nop   
/* 0A3E60 800A3260 460E7282 */  mul.s $f10, $f14, $f14
/* 0A3E64 800A3264 46062200 */  add.s $f8, $f4, $f6
/* 0A3E68 800A3268 0C0326B4 */  jal   sqrtf
/* 0A3E6C 800A326C 460A4300 */   add.s $f12, $f8, $f10
/* 0A3E70 800A3270 3C014416 */  li    $at, 0x44160000 # 600.000000
/* 0A3E74 800A3274 44812000 */  mtc1  $at, $f4
/* 0A3E78 800A3278 3C188012 */  lui   $t8, %hi(gHUDVoiceSoundMask) # $t8, 0x8012
/* 0A3E7C 800A327C 4604003C */  c.lt.s $f0, $f4
/* 0A3E80 800A3280 00000000 */  nop   
/* 0A3E84 800A3284 45000020 */  bc1f  .L800A3308
/* 0A3E88 800A3288 00000000 */   nop   
/* 0A3E8C 800A328C 8F186D40 */  lw    $t8, %lo(gHUDVoiceSoundMask)($t8)
/* 0A3E90 800A3290 3C108012 */  lui   $s0, %hi(D_80126D50) # $s0, 0x8012
/* 0A3E94 800A3294 1700001C */  bnez  $t8, .L800A3308
/* 0A3E98 800A3298 26106D50 */   addiu $s0, %lo(D_80126D50) # addiu $s0, $s0, 0x6d50
/* 0A3E9C 800A329C 8E0F0000 */  lw    $t7, ($s0)
/* 0A3EA0 800A32A0 00002025 */  move  $a0, $zero
/* 0A3EA4 800A32A4 15E00018 */  bnez  $t7, .L800A3308
/* 0A3EA8 800A32A8 00000000 */   nop   
/* 0A3EAC 800A32AC 0C01BE53 */  jal   get_random_number_from_range
/* 0A3EB0 800A32B0 24050002 */   li    $a1, 2
/* 0A3EB4 800A32B4 962A0000 */  lhu   $t2, ($s1)
/* 0A3EB8 800A32B8 24430147 */  addiu $v1, $v0, 0x147
/* 0A3EBC 800A32BC 306EFFFF */  andi  $t6, $v1, 0xffff
/* 0A3EC0 800A32C0 154E0009 */  bne   $t2, $t6, .L800A32E8
/* 0A3EC4 800A32C4 3064FFFF */   andi  $a0, $v1, 0xffff
.L800A32C8:
/* 0A3EC8 800A32C8 00002025 */  move  $a0, $zero
/* 0A3ECC 800A32CC 0C01BE53 */  jal   get_random_number_from_range
/* 0A3ED0 800A32D0 24050002 */   li    $a1, 2
/* 0A3ED4 800A32D4 96390000 */  lhu   $t9, ($s1)
/* 0A3ED8 800A32D8 24430147 */  addiu $v1, $v0, 0x147
/* 0A3EDC 800A32DC 306BFFFF */  andi  $t3, $v1, 0xffff
/* 0A3EE0 800A32E0 132BFFF9 */  beq   $t9, $t3, .L800A32C8
/* 0A3EE4 800A32E4 3064FFFF */   andi  $a0, $v1, 0xffff
.L800A32E8:
/* 0A3EE8 800A32E8 3C058012 */  lui   $a1, %hi(gHUDVoiceSoundMask) # $a1, 0x8012
/* 0A3EEC 800A32EC A6240000 */  sh    $a0, ($s1)
/* 0A3EF0 800A32F0 0C000741 */  jal   play_sound_global
/* 0A3EF4 800A32F4 24A56D40 */   addiu $a1, %lo(gHUDVoiceSoundMask) # addiu $a1, $a1, 0x6d40
/* 0A3EF8 800A32F8 24040078 */  li    $a0, 120
/* 0A3EFC 800A32FC 0C01BE53 */  jal   get_random_number_from_range
/* 0A3F00 800A3300 240504B0 */   li    $a1, 1200
/* 0A3F04 800A3304 AE020000 */  sw    $v0, ($s0)
.L800A3308:
/* 0A3F08 800A3308 3C108012 */  lui   $s0, %hi(D_80126D50) # $s0, 0x8012
/* 0A3F0C 800A330C 26106D50 */  addiu $s0, %lo(D_80126D50) # addiu $s0, $s0, 0x6d50
/* 0A3F10 800A3310 8E0C0000 */  lw    $t4, ($s0)
/* 0A3F14 800A3314 8FAD00C8 */  lw    $t5, 0xc8($sp)
/* 0A3F18 800A3318 00000000 */  nop   
/* 0A3F1C 800A331C 018DC023 */  subu  $t8, $t4, $t5
/* 0A3F20 800A3320 07010002 */  bgez  $t8, .L800A332C
/* 0A3F24 800A3324 AE180000 */   sw    $t8, ($s0)
/* 0A3F28 800A3328 AE000000 */  sw    $zero, ($s0)
.L800A332C:
/* 0A3F2C 800A332C 8FAA00A0 */  lw    $t2, 0xa0($sp)
.L800A3330:
/* 0A3F30 800A3330 8FAC00A0 */  lw    $t4, 0xa0($sp)
/* 0A3F34 800A3334 81430193 */  lb    $v1, 0x193($t2)
/* 0A3F38 800A3338 00000000 */  nop   
/* 0A3F3C 800A333C 00037080 */  sll   $t6, $v1, 2
/* 0A3F40 800A3340 014EC821 */  addu  $t9, $t2, $t6
/* 0A3F44 800A3344 8F2B0128 */  lw    $t3, 0x128($t9)
/* 0A3F48 800A3348 00000000 */  nop   
/* 0A3F4C 800A334C 2961001E */  slti  $at, $t3, 0x1e
/* 0A3F50 800A3350 1020000A */  beqz  $at, .L800A337C
/* 0A3F54 800A3354 00000000 */   nop   
/* 0A3F58 800A3358 10600008 */  beqz  $v1, .L800A337C
/* 0A3F5C 800A335C 24040005 */   li    $a0, 5
/* 0A3F60 800A3360 24050001 */  li    $a1, 1
/* 0A3F64 800A3364 24060002 */  li    $a2, 2
/* 0A3F68 800A3368 24070002 */  li    $a3, 2
/* 0A3F6C 800A336C 0C028DB3 */  jal   func_800A36CC
/* 0A3F70 800A3370 AFA00010 */   sw    $zero, 0x10($sp)
/* 0A3F74 800A3374 10000016 */  b     .L800A33D0
/* 0A3F78 800A3378 8FA400A0 */   lw    $a0, 0xa0($sp)
.L800A337C:
/* 0A3F7C 800A337C 818D01D3 */  lb    $t5, 0x1d3($t4)
/* 0A3F80 800A3380 8FB800A0 */  lw    $t8, 0xa0($sp)
/* 0A3F84 800A3384 19A00008 */  blez  $t5, .L800A33A8
/* 0A3F88 800A3388 24040006 */   li    $a0, 6
/* 0A3F8C 800A338C 24050002 */  li    $a1, 2
/* 0A3F90 800A3390 24060003 */  li    $a2, 3
/* 0A3F94 800A3394 24070002 */  li    $a3, 2
/* 0A3F98 800A3398 0C028DB3 */  jal   func_800A36CC
/* 0A3F9C 800A339C AFA00010 */   sw    $zero, 0x10($sp)
/* 0A3FA0 800A33A0 1000000B */  b     .L800A33D0
/* 0A3FA4 800A33A4 8FA400A0 */   lw    $a0, 0xa0($sp)
.L800A33A8:
/* 0A3FA8 800A33A8 930F01FC */  lbu   $t7, 0x1fc($t8)
/* 0A3FAC 800A33AC 24040006 */  li    $a0, 6
/* 0A3FB0 800A33B0 29E10079 */  slti  $at, $t7, 0x79
/* 0A3FB4 800A33B4 14200005 */  bnez  $at, .L800A33CC
/* 0A3FB8 800A33B8 24050003 */   li    $a1, 3
/* 0A3FBC 800A33BC 24060001 */  li    $a2, 1
/* 0A3FC0 800A33C0 24070004 */  li    $a3, 4
/* 0A3FC4 800A33C4 0C028DB3 */  jal   func_800A36CC
/* 0A3FC8 800A33C8 AFA00010 */   sw    $zero, 0x10($sp)
.L800A33CC:
/* 0A3FCC 800A33CC 8FA400A0 */  lw    $a0, 0xa0($sp)
.L800A33D0:
/* 0A3FD0 800A33D0 8FA500C8 */  lw    $a1, 0xc8($sp)
/* 0A3FD4 800A33D4 0C0293D4 */  jal   render_lap_count
/* 0A3FD8 800A33D8 00000000 */   nop   
/* 0A3FDC 800A33DC 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 0A3FE0 800A33E0 8FA500C8 */  lw    $a1, 0xc8($sp)
/* 0A3FE4 800A33E4 0C029EDA */  jal   render_race_time
/* 0A3FE8 800A33E8 00000000 */   nop   
/* 0A3FEC 800A33EC 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 0A3FF0 800A33F0 8FA500C8 */  lw    $a1, 0xc8($sp)
/* 0A3FF4 800A33F4 0C029055 */  jal   render_racer_bananas
/* 0A3FF8 800A33F8 00000000 */   nop   
/* 0A3FFC 800A33FC 8FA400A0 */  lw    $a0, 0xa0($sp)
/* 0A4000 800A3400 8FA500C8 */  lw    $a1, 0xc8($sp)
/* 0A4004 800A3404 0C029699 */  jal   render_wrong_way_text
/* 0A4008 800A3408 00000000 */   nop   
/* 0A400C 800A340C 8FA400C0 */  lw    $a0, 0xc0($sp)
/* 0A4010 800A3410 8FA500C8 */  lw    $a1, 0xc8($sp)
/* 0A4014 800A3414 0C028F39 */  jal   render_race_start
/* 0A4018 800A3418 00000000 */   nop   
/* 0A401C 800A341C 8FA400C4 */  lw    $a0, 0xc4($sp)
/* 0A4020 800A3420 8FA500C8 */  lw    $a1, 0xc8($sp)
/* 0A4024 800A3424 0C028E21 */  jal   render_speedometer
/* 0A4028 800A3428 00000000 */   nop   
/* 0A402C 800A342C 0C00382C */  jal   func_8000E0B0
/* 0A4030 800A3430 00000000 */   nop   
/* 0A4034 800A3434 1840009D */  blez  $v0, .L800A36AC
/* 0A4038 800A3438 00000000 */   nop   
/* 0A403C 800A343C 0C00382C */  jal   func_8000E0B0
/* 0A4040 800A3440 00000000 */   nop   
/* 0A4044 800A3444 24010001 */  li    $at, 1
/* 0A4048 800A3448 10410008 */  beq   $v0, $at, .L800A346C
/* 0A404C 800A344C 24010002 */   li    $at, 2
/* 0A4050 800A3450 10410010 */  beq   $v0, $at, .L800A3494
/* 0A4054 800A3454 3C0B800F */   lui   $t3, %hi(D_800E8658) # $t3, 0x800f
/* 0A4058 800A3458 24010003 */  li    $at, 3
/* 0A405C 800A345C 10410016 */  beq   $v0, $at, .L800A34B8
/* 0A4060 800A3460 3C18800F */   lui   $t8, %hi(D_800E8670) # $t8, 0x800f
/* 0A4064 800A3464 1000001C */  b     .L800A34D8
/* 0A4068 800A3468 00000000 */   nop   
.L800A346C:
/* 0A406C 800A346C 3C0A800F */  lui   $t2, %hi(D_800E8640) # $t2, 0x800f
/* 0A4070 800A3470 3C0E800F */  lui   $t6, %hi(D_800E8648) # $t6, 0x800f
/* 0A4074 800A3474 3C19800F */  lui   $t9, %hi(D_800E8650) # $t9, 0x800f
/* 0A4078 800A3478 254A8640 */  addiu $t2, %lo(D_800E8640) # addiu $t2, $t2, -0x79c0
/* 0A407C 800A347C 25CE8648 */  addiu $t6, %lo(D_800E8648) # addiu $t6, $t6, -0x79b8
/* 0A4080 800A3480 27398650 */  addiu $t9, %lo(D_800E8650) # addiu $t9, $t9, -0x79b0
/* 0A4084 800A3484 AFAA0060 */  sw    $t2, 0x60($sp)
/* 0A4088 800A3488 AFAE005C */  sw    $t6, 0x5c($sp)
/* 0A408C 800A348C 10000012 */  b     .L800A34D8
/* 0A4090 800A3490 AFB90058 */   sw    $t9, 0x58($sp)
.L800A3494:
/* 0A4094 800A3494 3C0C800F */  lui   $t4, %hi(D_800E8664) # $t4, 0x800f
/* 0A4098 800A3498 3C0D800F */  lui   $t5, %hi(D_800E8668) # $t5, 0x800f
/* 0A409C 800A349C 256B8658 */  addiu $t3, %lo(D_800E8658) # addiu $t3, $t3, -0x79a8
/* 0A40A0 800A34A0 258C8664 */  addiu $t4, %lo(D_800E8664) # addiu $t4, $t4, -0x799c
/* 0A40A4 800A34A4 25AD8668 */  addiu $t5, %lo(D_800E8668) # addiu $t5, $t5, -0x7998
/* 0A40A8 800A34A8 AFAB0060 */  sw    $t3, 0x60($sp)
/* 0A40AC 800A34AC AFAC005C */  sw    $t4, 0x5c($sp)
/* 0A40B0 800A34B0 10000009 */  b     .L800A34D8
/* 0A40B4 800A34B4 AFAD0058 */   sw    $t5, 0x58($sp)
.L800A34B8:
/* 0A40B8 800A34B8 3C0F800F */  lui   $t7, %hi(D_800E867C) # $t7, 0x800f
/* 0A40BC 800A34BC 3C0A800F */  lui   $t2, %hi(D_800E8680) # $t2, 0x800f
/* 0A40C0 800A34C0 27188670 */  addiu $t8, %lo(D_800E8670) # addiu $t8, $t8, -0x7990
/* 0A40C4 800A34C4 25EF867C */  addiu $t7, %lo(D_800E867C) # addiu $t7, $t7, -0x7984
/* 0A40C8 800A34C8 254A8680 */  addiu $t2, %lo(D_800E8680) # addiu $t2, $t2, -0x7980
/* 0A40CC 800A34CC AFB80060 */  sw    $t8, 0x60($sp)
/* 0A40D0 800A34D0 AFAF005C */  sw    $t7, 0x5c($sp)
/* 0A40D4 800A34D4 AFAA0058 */  sw    $t2, 0x58($sp)
.L800A34D8:
/* 0A40D8 800A34D8 0C031059 */  jal   set_kerning
/* 0A40DC 800A34DC 24040001 */   li    $a0, 1
/* 0A40E0 800A34E0 0C0310BB */  jal   set_text_font
/* 0A40E4 800A34E4 00002025 */   move  $a0, $zero
/* 0A40E8 800A34E8 240E00FF */  li    $t6, 255
/* 0A40EC 800A34EC AFAE0010 */  sw    $t6, 0x10($sp)
/* 0A40F0 800A34F0 00002025 */  move  $a0, $zero
/* 0A40F4 800A34F4 00002825 */  move  $a1, $zero
/* 0A40F8 800A34F8 00003025 */  move  $a2, $zero
/* 0A40FC 800A34FC 0C0310E1 */  jal   set_text_colour
/* 0A4100 800A3500 240700FF */   li    $a3, 255
/* 0A4104 800A3504 3C108012 */  lui   $s0, %hi(D_8012718C) # $s0, 0x8012
/* 0A4108 800A3508 3C118012 */  lui   $s1, %hi(D_80126D24) # $s1, 0x8012
/* 0A410C 800A350C 26316D24 */  addiu $s1, %lo(D_80126D24) # addiu $s1, $s1, 0x6d24
/* 0A4110 800A3510 2610718C */  addiu $s0, %lo(D_8012718C) # addiu $s0, $s0, 0x718c
/* 0A4114 800A3514 8E190000 */  lw    $t9, ($s0)
/* 0A4118 800A3518 8E2B0000 */  lw    $t3, ($s1)
/* 0A411C 800A351C 3C0D8012 */  lui   $t5, %hi(D_80126D28) # $t5, 0x8012
/* 0A4120 800A3520 8DAD6D28 */  lw    $t5, %lo(D_80126D28)($t5)
/* 0A4124 800A3524 3C068012 */  lui   $a2, %hi(D_80127190) # $a2, 0x8012
/* 0A4128 800A3528 8CC67190 */  lw    $a2, %lo(D_80127190)($a2)
/* 0A412C 800A352C 032B6021 */  addu  $t4, $t9, $t3
/* 0A4130 800A3530 8FA70060 */  lw    $a3, 0x60($sp)
/* 0A4134 800A3534 2418000C */  li    $t8, 12
/* 0A4138 800A3538 018D2821 */  addu  $a1, $t4, $t5
/* 0A413C 800A353C 24A50001 */  addiu $a1, $a1, 1
/* 0A4140 800A3540 AFB80010 */  sw    $t8, 0x10($sp)
/* 0A4144 800A3544 02402025 */  move  $a0, $s2
/* 0A4148 800A3548 0C031110 */  jal   draw_text
/* 0A414C 800A354C 24C60001 */   addiu $a2, $a2, 1
/* 0A4150 800A3550 8E0F0000 */  lw    $t7, ($s0)
/* 0A4154 800A3554 8E2A0000 */  lw    $t2, ($s1)
/* 0A4158 800A3558 3C198012 */  lui   $t9, %hi(D_80126D28) # $t9, 0x8012
/* 0A415C 800A355C 8F396D28 */  lw    $t9, %lo(D_80126D28)($t9)
/* 0A4160 800A3560 3C068012 */  lui   $a2, %hi(D_80127190) # $a2, 0x8012
/* 0A4164 800A3564 8CC67190 */  lw    $a2, %lo(D_80127190)($a2)
/* 0A4168 800A3568 01EA7021 */  addu  $t6, $t7, $t2
/* 0A416C 800A356C 8FA7005C */  lw    $a3, 0x5c($sp)
/* 0A4170 800A3570 240B000C */  li    $t3, 12
/* 0A4174 800A3574 01D92821 */  addu  $a1, $t6, $t9
/* 0A4178 800A3578 24A50001 */  addiu $a1, $a1, 1
/* 0A417C 800A357C AFAB0010 */  sw    $t3, 0x10($sp)
/* 0A4180 800A3580 02402025 */  move  $a0, $s2
/* 0A4184 800A3584 0C031110 */  jal   draw_text
/* 0A4188 800A3588 24C6000F */   addiu $a2, $a2, 0xf
/* 0A418C 800A358C 8E0C0000 */  lw    $t4, ($s0)
/* 0A4190 800A3590 8E2D0000 */  lw    $t5, ($s1)
/* 0A4194 800A3594 3C0F8012 */  lui   $t7, %hi(D_80126D28) # $t7, 0x8012
/* 0A4198 800A3598 8DEF6D28 */  lw    $t7, %lo(D_80126D28)($t7)
/* 0A419C 800A359C 3C068012 */  lui   $a2, %hi(D_80127190) # $a2, 0x8012
/* 0A41A0 800A35A0 8CC67190 */  lw    $a2, %lo(D_80127190)($a2)
/* 0A41A4 800A35A4 018DC021 */  addu  $t8, $t4, $t5
/* 0A41A8 800A35A8 8FA70058 */  lw    $a3, 0x58($sp)
/* 0A41AC 800A35AC 240A000C */  li    $t2, 12
/* 0A41B0 800A35B0 030F2821 */  addu  $a1, $t8, $t7
/* 0A41B4 800A35B4 24A50001 */  addiu $a1, $a1, 1
/* 0A41B8 800A35B8 AFAA0010 */  sw    $t2, 0x10($sp)
/* 0A41BC 800A35BC 02402025 */  move  $a0, $s2
/* 0A41C0 800A35C0 0C031110 */  jal   draw_text
/* 0A41C4 800A35C4 24C6001D */   addiu $a2, $a2, 0x1d
/* 0A41C8 800A35C8 3C028012 */  lui   $v0, %hi(D_80127194) # $v0, 0x8012
/* 0A41CC 800A35CC 8C427194 */  lw    $v0, %lo(D_80127194)($v0)
/* 0A41D0 800A35D0 24070080 */  li    $a3, 128
/* 0A41D4 800A35D4 904E0013 */  lbu   $t6, 0x13($v0)
/* 0A41D8 800A35D8 90440010 */  lbu   $a0, 0x10($v0)
/* 0A41DC 800A35DC 90450011 */  lbu   $a1, 0x11($v0)
/* 0A41E0 800A35E0 90460012 */  lbu   $a2, 0x12($v0)
/* 0A41E4 800A35E4 0C0310E1 */  jal   set_text_colour
/* 0A41E8 800A35E8 AFAE0010 */   sw    $t6, 0x10($sp)
/* 0A41EC 800A35EC 8E190000 */  lw    $t9, ($s0)
/* 0A41F0 800A35F0 8E2B0000 */  lw    $t3, ($s1)
/* 0A41F4 800A35F4 3C0D8012 */  lui   $t5, %hi(D_80126D28) # $t5, 0x8012
/* 0A41F8 800A35F8 8DAD6D28 */  lw    $t5, %lo(D_80126D28)($t5)
/* 0A41FC 800A35FC 3C068012 */  lui   $a2, %hi(D_80127190) # $a2, 0x8012
/* 0A4200 800A3600 8CC67190 */  lw    $a2, %lo(D_80127190)($a2)
/* 0A4204 800A3604 8FA70060 */  lw    $a3, 0x60($sp)
/* 0A4208 800A3608 2418000C */  li    $t8, 12
/* 0A420C 800A360C 032B6021 */  addu  $t4, $t9, $t3
/* 0A4210 800A3610 AFB80010 */  sw    $t8, 0x10($sp)
/* 0A4214 800A3614 02402025 */  move  $a0, $s2
/* 0A4218 800A3618 0C031110 */  jal   draw_text
/* 0A421C 800A361C 018D2821 */   addu  $a1, $t4, $t5
/* 0A4220 800A3620 8E0F0000 */  lw    $t7, ($s0)
/* 0A4224 800A3624 8E2A0000 */  lw    $t2, ($s1)
/* 0A4228 800A3628 3C198012 */  lui   $t9, %hi(D_80126D28) # $t9, 0x8012
/* 0A422C 800A362C 3C068012 */  lui   $a2, %hi(D_80127190) # $a2, 0x8012
/* 0A4230 800A3630 8CC67190 */  lw    $a2, %lo(D_80127190)($a2)
/* 0A4234 800A3634 8F396D28 */  lw    $t9, %lo(D_80126D28)($t9)
/* 0A4238 800A3638 8FA7005C */  lw    $a3, 0x5c($sp)
/* 0A423C 800A363C 240B000C */  li    $t3, 12
/* 0A4240 800A3640 01EA7021 */  addu  $t6, $t7, $t2
/* 0A4244 800A3644 AFAB0010 */  sw    $t3, 0x10($sp)
/* 0A4248 800A3648 02402025 */  move  $a0, $s2
/* 0A424C 800A364C 24C6000E */  addiu $a2, $a2, 0xe
/* 0A4250 800A3650 0C031110 */  jal   draw_text
/* 0A4254 800A3654 01D92821 */   addu  $a1, $t6, $t9
/* 0A4258 800A3658 8E0C0000 */  lw    $t4, ($s0)
/* 0A425C 800A365C 8E2D0000 */  lw    $t5, ($s1)
/* 0A4260 800A3660 3C0F8012 */  lui   $t7, %hi(D_80126D28) # $t7, 0x8012
/* 0A4264 800A3664 3C068012 */  lui   $a2, %hi(D_80127190) # $a2, 0x8012
/* 0A4268 800A3668 8CC67190 */  lw    $a2, %lo(D_80127190)($a2)
/* 0A426C 800A366C 8DEF6D28 */  lw    $t7, %lo(D_80126D28)($t7)
/* 0A4270 800A3670 8FA70058 */  lw    $a3, 0x58($sp)
/* 0A4274 800A3674 240A000C */  li    $t2, 12
/* 0A4278 800A3678 018DC021 */  addu  $t8, $t4, $t5
/* 0A427C 800A367C AFAA0010 */  sw    $t2, 0x10($sp)
/* 0A4280 800A3680 02402025 */  move  $a0, $s2
/* 0A4284 800A3684 24C6001C */  addiu $a2, $a2, 0x1c
/* 0A4288 800A3688 0C031110 */  jal   draw_text
/* 0A428C 800A368C 030F2821 */   addu  $a1, $t8, $t7
/* 0A4290 800A3690 3C048012 */  lui   $a0, %hi(D_80127194) # $a0, 0x8012
/* 0A4294 800A3694 8C847194 */  lw    $a0, %lo(D_80127194)($a0)
/* 0A4298 800A3698 8FA500C8 */  lw    $a1, 0xc8($sp)
/* 0A429C 800A369C 0C01FC93 */  jal   func_8007F24C
/* 0A42A0 800A36A0 00000000 */   nop   
/* 0A42A4 800A36A4 0C031059 */  jal   set_kerning
/* 0A42A8 800A36A8 00002025 */   move  $a0, $zero
.L800A36AC:
/* 0A42AC 800A36AC 0C01A142 */  jal   func_80068508
/* 0A42B0 800A36B0 00002025 */   move  $a0, $zero
.L800A36B4:
/* 0A42B4 800A36B4 8FBF002C */  lw    $ra, 0x2c($sp)
/* 0A42B8 800A36B8 8FB00020 */  lw    $s0, 0x20($sp)
/* 0A42BC 800A36BC 8FB10024 */  lw    $s1, 0x24($sp)
/* 0A42C0 800A36C0 8FB20028 */  lw    $s2, 0x28($sp)
/* 0A42C4 800A36C4 03E00008 */  jr    $ra
/* 0A42C8 800A36C8 27BD00C0 */   addiu $sp, $sp, 0xc0

