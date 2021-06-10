glabel viMgrMain
/* 0D2708 800D1B08 27BDFFB0 */  addiu $sp, $sp, -0x50
/* 0D270C 800D1B0C AFBF0034 */  sw    $ra, 0x34($sp)
/* 0D2710 800D1B10 AFB70030 */  sw    $s7, 0x30($sp)
/* 0D2714 800D1B14 0080B825 */  move  $s7, $a0
/* 0D2718 800D1B18 AFB6002C */  sw    $s6, 0x2c($sp)
/* 0D271C 800D1B1C AFB50028 */  sw    $s5, 0x28($sp)
/* 0D2720 800D1B20 AFB40024 */  sw    $s4, 0x24($sp)
/* 0D2724 800D1B24 AFB30020 */  sw    $s3, 0x20($sp)
/* 0D2728 800D1B28 AFB2001C */  sw    $s2, 0x1c($sp)
/* 0D272C 800D1B2C AFB10018 */  sw    $s1, 0x18($sp)
/* 0D2730 800D1B30 AFB00014 */  sw    $s0, 0x14($sp)
/* 0D2734 800D1B34 0C035820 */  jal   __osViGetCurrentContext
/* 0D2738 800D1B38 AFA00044 */   sw    $zero, 0x44($sp)
/* 0D273C 800D1B3C 94430002 */  lhu   $v1, 2($v0)
/* 0D2740 800D1B40 3C018013 */  lui   $at, %hi(D_8012D190) # $at, 0x8013
/* 0D2744 800D1B44 2416000E */  li    $s6, 14
/* 0D2748 800D1B48 14600004 */  bnez  $v1, .L800D1B5C
/* 0D274C 800D1B4C A423D190 */   sh    $v1, %lo(D_8012D190)($at)
/* 0D2750 800D1B50 24030001 */  li    $v1, 1
/* 0D2754 800D1B54 3C018013 */  lui   $at, %hi(D_8012D190) # $at, 0x8013
/* 0D2758 800D1B58 A423D190 */  sh    $v1, %lo(D_8012D190)($at)
.L800D1B5C:
/* 0D275C 800D1B5C 3C138013 */  lui   $s3, %hi(D_8012D22C) # $s3, 0x8013
/* 0D2760 800D1B60 3C128013 */  lui   $s2, %hi(__osBaseCounter) # $s2, 0x8013
/* 0D2764 800D1B64 3C118013 */  lui   $s1, %hi(__osCurrentTime) # $s1, 0x8013
/* 0D2768 800D1B68 2631D220 */  addiu $s1, %lo(__osCurrentTime) # addiu $s1, $s1, -0x2de0
/* 0D276C 800D1B6C 2652D228 */  addiu $s2, %lo(__osBaseCounter) # addiu $s2, $s2, -0x2dd8
/* 0D2770 800D1B70 2673D22C */  addiu $s3, %lo(D_8012D22C) # addiu $s3, $s3, -0x2dd4
/* 0D2774 800D1B74 2415000D */  li    $s5, 13
/* 0D2778 800D1B78 27B40044 */  addiu $s4, $sp, 0x44
.L800D1B7C:
/* 0D277C 800D1B7C 8EE4000C */  lw    $a0, 0xc($s7)
.L800D1B80:
/* 0D2780 800D1B80 02802825 */  move  $a1, $s4
/* 0D2784 800D1B84 0C0322EC */  jal   osRecvMesg
/* 0D2788 800D1B88 24060001 */   li    $a2, 1
/* 0D278C 800D1B8C 8FAE0044 */  lw    $t6, 0x44($sp)
/* 0D2790 800D1B90 95C30000 */  lhu   $v1, ($t6)
/* 0D2794 800D1B94 10750005 */  beq   $v1, $s5, .L800D1BAC
/* 0D2798 800D1B98 00000000 */   nop   
/* 0D279C 800D1B9C 1076002A */  beq   $v1, $s6, .L800D1C48
/* 0D27A0 800D1BA0 00000000 */   nop   
/* 0D27A4 800D1BA4 1000FFF6 */  b     .L800D1B80
/* 0D27A8 800D1BA8 8EE4000C */   lw    $a0, 0xc($s7)
.L800D1BAC:
/* 0D27AC 800D1BAC 0C035824 */  jal   __osViSwapContext
/* 0D27B0 800D1BB0 00000000 */   nop   
/* 0D27B4 800D1BB4 3C038013 */  lui   $v1, %hi(D_8012D190) # $v1, 0x8013
/* 0D27B8 800D1BB8 9463D190 */  lhu   $v1, %lo(D_8012D190)($v1)
/* 0D27BC 800D1BBC 3C018013 */  lui   $at, %hi(D_8012D190) # $at, 0x8013
/* 0D27C0 800D1BC0 2463FFFF */  addiu $v1, $v1, -1
/* 0D27C4 800D1BC4 306FFFFF */  andi  $t7, $v1, 0xffff
/* 0D27C8 800D1BC8 15E0000E */  bnez  $t7, .L800D1C04
/* 0D27CC 800D1BCC A42FD190 */   sh    $t7, %lo(D_8012D190)($at)
/* 0D27D0 800D1BD0 0C035820 */  jal   __osViGetCurrentContext
/* 0D27D4 800D1BD4 00000000 */   nop   
/* 0D27D8 800D1BD8 8C580010 */  lw    $t8, 0x10($v0)
/* 0D27DC 800D1BDC 00408025 */  move  $s0, $v0
/* 0D27E0 800D1BE0 00003025 */  move  $a2, $zero
/* 0D27E4 800D1BE4 53000005 */  beql  $t8, $zero, .L800D1BFC
/* 0D27E8 800D1BE8 96030002 */   lhu   $v1, 2($s0)
/* 0D27EC 800D1BEC 8C440010 */  lw    $a0, 0x10($v0)
/* 0D27F0 800D1BF0 0C03238C */  jal   osSendMesg
/* 0D27F4 800D1BF4 8C450014 */   lw    $a1, 0x14($v0)
/* 0D27F8 800D1BF8 96030002 */  lhu   $v1, 2($s0)
.L800D1BFC:
/* 0D27FC 800D1BFC 3C018013 */  lui   $at, %hi(D_8012D190) # $at, 0x8013
/* 0D2800 800D1C00 A423D190 */  sh    $v1, %lo(D_8012D190)($at)
.L800D1C04:
/* 0D2804 800D1C04 8E790000 */  lw    $t9, ($s3)
/* 0D2808 800D1C08 8E500000 */  lw    $s0, ($s2)
/* 0D280C 800D1C0C 27280001 */  addiu $t0, $t9, 1
/* 0D2810 800D1C10 0C031E34 */  jal   osGetCount
/* 0D2814 800D1C14 AE680000 */   sw    $t0, ($s3)
/* 0D2818 800D1C18 8E2D0004 */  lw    $t5, 4($s1)
/* 0D281C 800D1C1C 00508023 */  subu  $s0, $v0, $s0
/* 0D2820 800D1C20 8E2C0000 */  lw    $t4, ($s1)
/* 0D2824 800D1C24 020D7821 */  addu  $t7, $s0, $t5
/* 0D2828 800D1C28 240A0000 */  li    $t2, 0
/* 0D282C 800D1C2C 01ED082B */  sltu  $at, $t7, $t5
/* 0D2830 800D1C30 002A7021 */  addu  $t6, $at, $t2
/* 0D2834 800D1C34 01CC7021 */  addu  $t6, $t6, $t4
/* 0D2838 800D1C38 AE420000 */  sw    $v0, ($s2)
/* 0D283C 800D1C3C AE2E0000 */  sw    $t6, ($s1)
/* 0D2840 800D1C40 1000FFCE */  b     .L800D1B7C
/* 0D2844 800D1C44 AE2F0004 */   sw    $t7, 4($s1)
.L800D1C48:
/* 0D2848 800D1C48 0C0353D3 */  jal   __osTimerInterrupt
/* 0D284C 800D1C4C 00000000 */   nop   
/* 0D2850 800D1C50 1000FFCB */  b     .L800D1B80
/* 0D2854 800D1C54 8EE4000C */   lw    $a0, 0xc($s7)
/* 0D2858 800D1C58 00000000 */  nop   
/* 0D285C 800D1C5C 00000000 */  nop   
/* 0D2860 800D1C60 00000000 */  nop   
/* 0D2864 800D1C64 00000000 */  nop   
/* 0D2868 800D1C68 00000000 */  nop   
/* 0D286C 800D1C6C 00000000 */  nop   
/* 0D2870 800D1C70 8FBF0034 */  lw    $ra, 0x34($sp)
/* 0D2874 800D1C74 8FB00014 */  lw    $s0, 0x14($sp)
/* 0D2878 800D1C78 8FB10018 */  lw    $s1, 0x18($sp)
/* 0D287C 800D1C7C 8FB2001C */  lw    $s2, 0x1c($sp)
/* 0D2880 800D1C80 8FB30020 */  lw    $s3, 0x20($sp)
/* 0D2884 800D1C84 8FB40024 */  lw    $s4, 0x24($sp)
/* 0D2888 800D1C88 8FB50028 */  lw    $s5, 0x28($sp)
/* 0D288C 800D1C8C 8FB6002C */  lw    $s6, 0x2c($sp)
/* 0D2890 800D1C90 8FB70030 */  lw    $s7, 0x30($sp)
/* 0D2894 800D1C94 03E00008 */  jr    $ra
/* 0D2898 800D1C98 27BD0050 */   addiu $sp, $sp, 0x50

/* 0D289C 800D1C9C 00000000 */  nop   

