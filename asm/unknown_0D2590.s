.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800D1990
/* 0D2590 800D1990 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 0D2594 800D1994 AFB00020 */  sw    $s0, 0x20($sp)
/* 0D2598 800D1998 3C10800E */  lui   $s0, %hi(D_800E38E0) # $s0, 0x800e
/* 0D259C 800D199C 261038E0 */  addiu $s0, %lo(D_800E38E0) # addiu $s0, $s0, 0x38e0
/* 0D25A0 800D19A0 8E0E0000 */  lw    $t6, ($s0)
/* 0D25A4 800D19A4 AFBF0024 */  sw    $ra, 0x24($sp)
/* 0D25A8 800D19A8 AFA40030 */  sw    $a0, 0x30($sp)
/* 0D25AC 800D19AC 55C00052 */  bnezl $t6, .L800D1AF8
/* 0D25B0 800D19B0 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0D25B4 800D19B4 0C0353B0 */  jal   func_800D4EC0
/* 0D25B8 800D19B8 00000000 */   nop   
/* 0D25BC 800D19BC 3C048013 */  lui   $a0, %hi(D_8012D130) # $a0, 0x8013
/* 0D25C0 800D19C0 3C058013 */  lui   $a1, %hi(D_8012D148) # $a1, 0x8013
/* 0D25C4 800D19C4 24A5D148 */  addiu $a1, %lo(D_8012D148) # addiu $a1, $a1, -0x2eb8
/* 0D25C8 800D19C8 2484D130 */  addiu $a0, %lo(D_8012D130) # addiu $a0, $a0, -0x2ed0
/* 0D25CC 800D19CC 0C032208 */  jal   osCreateMesgQueue
/* 0D25D0 800D19D0 24060005 */   li    $a2, 5
/* 0D25D4 800D19D4 3C068013 */  lui   $a2, %hi(D_8012D160) # $a2, 0x8013
/* 0D25D8 800D19D8 3C078013 */  lui   $a3, %hi(D_8012D178) # $a3, 0x8013
/* 0D25DC 800D19DC 24E7D178 */  addiu $a3, %lo(D_8012D178) # addiu $a3, $a3, -0x2e88
/* 0D25E0 800D19E0 24C6D160 */  addiu $a2, %lo(D_8012D160) # addiu $a2, $a2, -0x2ea0
/* 0D25E4 800D19E4 240F000D */  li    $t7, 13
/* 0D25E8 800D19E8 2418000E */  li    $t8, 14
/* 0D25EC 800D19EC 3C058013 */  lui   $a1, %hi(D_8012D130) # $a1, 0x8013
/* 0D25F0 800D19F0 A4CF0000 */  sh    $t7, ($a2)
/* 0D25F4 800D19F4 A0C00002 */  sb    $zero, 2($a2)
/* 0D25F8 800D19F8 ACC00004 */  sw    $zero, 4($a2)
/* 0D25FC 800D19FC A4F80000 */  sh    $t8, ($a3)
/* 0D2600 800D1A00 A0E00002 */  sb    $zero, 2($a3)
/* 0D2604 800D1A04 ACE00004 */  sw    $zero, 4($a3)
/* 0D2608 800D1A08 24A5D130 */  addiu $a1, %lo(D_8012D130) # addiu $a1, $a1, -0x2ed0
/* 0D260C 800D1A0C 0C0332EC */  jal   osSetEventMsg
/* 0D2610 800D1A10 24040007 */   li    $a0, 7
/* 0D2614 800D1A14 3C078013 */  lui   $a3, 0x8013
/* 0D2618 800D1A18 3C058013 */  lui   $a1, %hi(D_8012D130) # $a1, 0x8013
/* 0D261C 800D1A1C 24E6D178 */  addiu $a2, $a3, -0x2e88
/* 0D2620 800D1A20 24A5D130 */  addiu $a1, %lo(D_8012D130) # addiu $a1, $a1, -0x2ed0
/* 0D2624 800D1A24 0C0332EC */  jal   osSetEventMsg
/* 0D2628 800D1A28 24040003 */   li    $a0, 3
/* 0D262C 800D1A2C 2419FFFF */  li    $t9, -1
/* 0D2630 800D1A30 AFB90028 */  sw    $t9, 0x28($sp)
/* 0D2634 800D1A34 0C034950 */  jal   func_800D2540
/* 0D2638 800D1A38 00002025 */   move  $a0, $zero
/* 0D263C 800D1A3C 8FA80030 */  lw    $t0, 0x30($sp)
/* 0D2640 800D1A40 00002025 */  move  $a0, $zero
/* 0D2644 800D1A44 0048082A */  slt   $at, $v0, $t0
/* 0D2648 800D1A48 10200003 */  beqz  $at, .L800D1A58
/* 0D264C 800D1A4C 01002825 */   move  $a1, $t0
/* 0D2650 800D1A50 0C033210 */  jal   func_800CC840
/* 0D2654 800D1A54 AFA20028 */   sw    $v0, 0x28($sp)
.L800D1A58:
/* 0D2658 800D1A58 0C034958 */  jal   __osDisableInt
/* 0D265C 800D1A5C 00000000 */   nop   
/* 0D2660 800D1A60 8FAB0030 */  lw    $t3, 0x30($sp)
/* 0D2664 800D1A64 3C038013 */  lui   $v1, %hi(D_8012D130) # $v1, 0x8013
/* 0D2668 800D1A68 3C048013 */  lui   $a0, %hi(D_8012CE80) # $a0, 0x8013
/* 0D266C 800D1A6C 3C0A8013 */  lui   $t2, %hi(D_8012D130) # $t2, 0x8013
/* 0D2670 800D1A70 2484CE80 */  addiu $a0, %lo(D_8012CE80) # addiu $a0, $a0, -0x3180
/* 0D2674 800D1A74 2463D130 */  addiu $v1, %lo(D_8012D130) # addiu $v1, $v1, -0x2ed0
/* 0D2678 800D1A78 24090001 */  li    $t1, 1
/* 0D267C 800D1A7C 254AD130 */  addiu $t2, %lo(D_8012D130) # addiu $t2, $t2, -0x2ed0
/* 0D2680 800D1A80 3C06800D */  lui   $a2, %hi(D_800D1B08) # $a2, 0x800d
/* 0D2684 800D1A84 AFA2002C */  sw    $v0, 0x2c($sp)
/* 0D2688 800D1A88 AE090000 */  sw    $t1, ($s0)
/* 0D268C 800D1A8C AE040004 */  sw    $a0, 4($s0)
/* 0D2690 800D1A90 AE030008 */  sw    $v1, 8($s0)
/* 0D2694 800D1A94 AE03000C */  sw    $v1, 0xc($s0)
/* 0D2698 800D1A98 AE000010 */  sw    $zero, 0x10($s0)
/* 0D269C 800D1A9C AE000014 */  sw    $zero, 0x14($s0)
/* 0D26A0 800D1AA0 AE000018 */  sw    $zero, 0x18($s0)
/* 0D26A4 800D1AA4 24C61B08 */  addiu $a2, %lo(D_800D1B08) # addiu $a2, $a2, 0x1b08
/* 0D26A8 800D1AA8 AFAA0010 */  sw    $t2, 0x10($sp)
/* 0D26AC 800D1AAC 00002825 */  move  $a1, $zero
/* 0D26B0 800D1AB0 02003825 */  move  $a3, $s0
/* 0D26B4 800D1AB4 0C032214 */  jal   osCreateThread
/* 0D26B8 800D1AB8 AFAB0014 */   sw    $t3, 0x14($sp)
/* 0D26BC 800D1ABC 0C034AC4 */  jal   func_800D2B10
/* 0D26C0 800D1AC0 00000000 */   nop   
/* 0D26C4 800D1AC4 3C048013 */  lui   $a0, %hi(D_8012CE80) # $a0, 0x8013
/* 0D26C8 800D1AC8 0C032268 */  jal   osStartThread
/* 0D26CC 800D1ACC 2484CE80 */   addiu $a0, %lo(D_8012CE80) # addiu $a0, $a0, -0x3180
/* 0D26D0 800D1AD0 0C034960 */  jal   __osRestoreInt
/* 0D26D4 800D1AD4 8FA4002C */   lw    $a0, 0x2c($sp)
/* 0D26D8 800D1AD8 8FAC0028 */  lw    $t4, 0x28($sp)
/* 0D26DC 800D1ADC 2401FFFF */  li    $at, -1
/* 0D26E0 800D1AE0 00002025 */  move  $a0, $zero
/* 0D26E4 800D1AE4 51810004 */  beql  $t4, $at, .L800D1AF8
/* 0D26E8 800D1AE8 8FBF0024 */   lw    $ra, 0x24($sp)
/* 0D26EC 800D1AEC 0C033210 */  jal   func_800CC840
/* 0D26F0 800D1AF0 01802825 */   move  $a1, $t4
/* 0D26F4 800D1AF4 8FBF0024 */  lw    $ra, 0x24($sp)
.L800D1AF8:
/* 0D26F8 800D1AF8 8FB00020 */  lw    $s0, 0x20($sp)
/* 0D26FC 800D1AFC 27BD0030 */  addiu $sp, $sp, 0x30
/* 0D2700 800D1B00 03E00008 */  jr    $ra
/* 0D2704 800D1B04 00000000 */   nop   

glabel D_800D1B08
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
/* 0D2734 800D1B34 0C035820 */  jal   func_800D6080
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
/* 0D2760 800D1B60 3C128013 */  lui   $s2, %hi(D_8012D228) # $s2, 0x8013
/* 0D2764 800D1B64 3C118013 */  lui   $s1, %hi(D_8012D220) # $s1, 0x8013
/* 0D2768 800D1B68 2631D220 */  addiu $s1, %lo(D_8012D220) # addiu $s1, $s1, -0x2de0
/* 0D276C 800D1B6C 2652D228 */  addiu $s2, %lo(D_8012D228) # addiu $s2, $s2, -0x2dd8
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
/* 0D27AC 800D1BAC 0C035824 */  jal   func_800D6090
/* 0D27B0 800D1BB0 00000000 */   nop   
/* 0D27B4 800D1BB4 3C038013 */  lui   $v1, %hi(D_8012FFFF) # $v1, 0x8013
/* 0D27B8 800D1BB8 9463D190 */  lhu   $v1, %lo(D_8012D190)($v1)
/* 0D27BC 800D1BBC 3C018013 */  lui   $at, %hi(D_8012D190) # $at, 0x8013
/* 0D27C0 800D1BC0 2463FFFF */  addiu $v1, %lo(D_8012FFFF) # addiu $v1, $v1, -1
/* 0D27C4 800D1BC4 306FFFFF */  andi  $t7, $v1, 0xffff
/* 0D27C8 800D1BC8 15E0000E */  bnez  $t7, .L800D1C04
/* 0D27CC 800D1BCC A42FD190 */   sh    $t7, %lo(D_8012D190)($at)
/* 0D27D0 800D1BD0 0C035820 */  jal   func_800D6080
/* 0D27D4 800D1BD4 00000000 */   nop   
/* 0D27D8 800D1BD8 8C580010 */  lw    $t8, 0x10($v0)
/* 0D27DC 800D1BDC 00408025 */  move  $s0, $v0
/* 0D27E0 800D1BE0 00003025 */  move  $a2, $zero
/* 0D27E4 800D1BE4 53000005 */  beql  $t8, $zero, .L800D1BFC
/* 0D27E8 800D1BE8 96030002 */   lhu   $v1, 2($s0)
/* 0D27EC 800D1BEC 8C440010 */  lw    $a0, 0x10($v0)
/* 0D27F0 800D1BF0 0C03238C */  jal   func_800C8E30
/* 0D27F4 800D1BF4 8C450014 */   lw    $a1, 0x14($v0)
/* 0D27F8 800D1BF8 96030002 */  lhu   $v1, 2($s0)
.L800D1BFC:
/* 0D27FC 800D1BFC 3C018013 */  lui   $at, %hi(D_8012D190) # $at, 0x8013
/* 0D2800 800D1C00 A423D190 */  sh    $v1, %lo(D_8012D190)($at)
.L800D1C04:
/* 0D2804 800D1C04 8E790000 */  lw    $t9, ($s3)
/* 0D2808 800D1C08 8E500000 */  lw    $s0, ($s2)
/* 0D280C 800D1C0C 27280001 */  addiu $t0, $t9, 1
/* 0D2810 800D1C10 0C031E34 */  jal   func_800C78D0
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
/* 0D2848 800D1C48 0C0353D3 */  jal   func_800D4F4C
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
