glabel func_800C27A0
/* 0C33A0 800C27A0 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 0C33A4 800C27A4 AFB2000C */  sw    $s2, 0xc($sp)
/* 0C33A8 800C27A8 AFB00004 */  sw    $s0, 4($sp)
/* 0C33AC 800C27AC AFB10008 */  sw    $s1, 8($sp)
/* 0C33B0 800C27B0 3C108013 */  lui   $s0, %hi(gCurFadeBlue) # $s0, 0x8013
/* 0C33B4 800C27B4 3C12800E */  lui   $s2, %hi(sTransitionFlags) # $s2, 0x800e
/* 0C33B8 800C27B8 3C0D8013 */  lui   $t5, %hi(gCurFadeGreen) # $t5, 0x8013
/* 0C33BC 800C27BC 3C0C8013 */  lui   $t4, %hi(gCurFadeRed) # $t4, 0x8013
/* 0C33C0 800C27C0 3C0B8013 */  lui   $t3, %hi(D_8012A74C) # $t3, 0x8013
/* 0C33C4 800C27C4 3C0A8013 */  lui   $t2, %hi(gLastFadeBlue) # $t2, 0x8013
/* 0C33C8 800C27C8 3C098013 */  lui   $t1, %hi(D_8012A748) # $t1, 0x8013
/* 0C33CC 800C27CC 3C088013 */  lui   $t0, %hi(gLastFadeGreen) # $t0, 0x8013
/* 0C33D0 800C27D0 3C078013 */  lui   $a3, %hi(D_8012A744) # $a3, 0x8013
/* 0C33D4 800C27D4 3C068013 */  lui   $a2, %hi(gLastFadeRed) # $a2, 0x8013
/* 0C33D8 800C27D8 3C05800E */  lui   $a1, %hi(sTransitionFadeTimer) # $a1, 0x800e
/* 0C33DC 800C27DC 24A531B0 */  addiu $a1, %lo(sTransitionFadeTimer) # addiu $a1, $a1, 0x31b0
/* 0C33E0 800C27E0 24C6A738 */  addiu $a2, %lo(gLastFadeRed) # addiu $a2, $a2, -0x58c8
/* 0C33E4 800C27E4 24E7A744 */  addiu $a3, %lo(D_8012A744) # addiu $a3, $a3, -0x58bc
/* 0C33E8 800C27E8 2508A73C */  addiu $t0, %lo(gLastFadeGreen) # addiu $t0, $t0, -0x58c4
/* 0C33EC 800C27EC 2529A748 */  addiu $t1, %lo(D_8012A748) # addiu $t1, $t1, -0x58b8
/* 0C33F0 800C27F0 254AA740 */  addiu $t2, %lo(gLastFadeBlue) # addiu $t2, $t2, -0x58c0
/* 0C33F4 800C27F4 256BA74C */  addiu $t3, %lo(D_8012A74C) # addiu $t3, $t3, -0x58b4
/* 0C33F8 800C27F8 258CA734 */  addiu $t4, %lo(gCurFadeRed) # addiu $t4, $t4, -0x58cc
/* 0C33FC 800C27FC 25ADA735 */  addiu $t5, %lo(gCurFadeGreen) # addiu $t5, $t5, -0x58cb
/* 0C3400 800C2800 265231B4 */  addiu $s2, %lo(sTransitionFlags) # addiu $s2, $s2, 0x31b4
/* 0C3404 800C2804 2610A736 */  addiu $s0, %lo(gCurFadeBlue) # addiu $s0, $s0, -0x58ca
/* 0C3408 800C2808 3411FFFF */  li    $s1, 65535
/* 0C340C 800C280C 24020001 */  li    $v0, 1
.L800C2810:
/* 0C3410 800C2810 94A30000 */  lhu   $v1, ($a1)
/* 0C3414 800C2814 00000000 */  nop   
/* 0C3418 800C2818 18600024 */  blez  $v1, .L800C28AC
/* 0C341C 800C281C 00000000 */   nop   
/* 0C3420 800C2820 8CEF0000 */  lw    $t7, ($a3)
/* 0C3424 800C2824 8CCE0000 */  lw    $t6, ($a2)
/* 0C3428 800C2828 01E40019 */  multu $t7, $a0
/* 0C342C 800C282C 8D0F0000 */  lw    $t7, ($t0)
/* 0C3430 800C2830 0083082A */  slt   $at, $a0, $v1
/* 0C3434 800C2834 0000C012 */  mflo  $t8
/* 0C3438 800C2838 01D8C821 */  addu  $t9, $t6, $t8
/* 0C343C 800C283C 8D2E0000 */  lw    $t6, ($t1)
/* 0C3440 800C2840 ACD90000 */  sw    $t9, ($a2)
/* 0C3444 800C2844 01C40019 */  multu $t6, $a0
/* 0C3448 800C2848 8D4E0000 */  lw    $t6, ($t2)
/* 0C344C 800C284C 0000C012 */  mflo  $t8
/* 0C3450 800C2850 01F8C821 */  addu  $t9, $t7, $t8
/* 0C3454 800C2854 8D6F0000 */  lw    $t7, ($t3)
/* 0C3458 800C2858 AD190000 */  sw    $t9, ($t0)
/* 0C345C 800C285C 01E40019 */  multu $t7, $a0
/* 0C3460 800C2860 0000C012 */  mflo  $t8
/* 0C3464 800C2864 01D8C821 */  addu  $t9, $t6, $t8
/* 0C3468 800C2868 1420000D */  bnez  $at, .L800C28A0
/* 0C346C 800C286C AD590000 */   sw    $t9, ($t2)
/* 0C3470 800C2870 918F0000 */  lbu   $t7, ($t4)
/* 0C3474 800C2874 91B80000 */  lbu   $t8, ($t5)
/* 0C3478 800C2878 000F7400 */  sll   $t6, $t7, 0x10
/* 0C347C 800C287C 920F0000 */  lbu   $t7, ($s0)
/* 0C3480 800C2880 ACCE0000 */  sw    $t6, ($a2)
/* 0C3484 800C2884 0018CC00 */  sll   $t9, $t8, 0x10
/* 0C3488 800C2888 000F7400 */  sll   $t6, $t7, 0x10
/* 0C348C 800C288C AD190000 */  sw    $t9, ($t0)
/* 0C3490 800C2890 AD4E0000 */  sw    $t6, ($t2)
/* 0C3494 800C2894 00832023 */  subu  $a0, $a0, $v1
/* 0C3498 800C2898 1000000C */  b     .L800C28CC
/* 0C349C 800C289C A4A00000 */   sh    $zero, ($a1)
.L800C28A0:
/* 0C34A0 800C28A0 0064C023 */  subu  $t8, $v1, $a0
/* 0C34A4 800C28A4 10000009 */  b     .L800C28CC
/* 0C34A8 800C28A8 A4B80000 */   sh    $t8, ($a1)
.L800C28AC:
/* 0C34AC 800C28AC 96430000 */  lhu   $v1, ($s2)
/* 0C34B0 800C28B0 00000000 */  nop   
/* 0C34B4 800C28B4 12230005 */  beq   $s1, $v1, .L800C28CC
/* 0C34B8 800C28B8 0064C823 */   subu  $t9, $v1, $a0
/* 0C34BC 800C28BC 332FFFFF */  andi  $t7, $t9, 0xffff
/* 0C34C0 800C28C0 1DE00002 */  bgtz  $t7, .L800C28CC
/* 0C34C4 800C28C4 A6590000 */   sh    $t9, ($s2)
/* 0C34C8 800C28C8 A6400000 */  sh    $zero, ($s2)
.L800C28CC:
/* 0C34CC 800C28CC 1040FFD0 */  beqz  $v0, .L800C2810
/* 0C34D0 800C28D0 00000000 */   nop   
/* 0C34D4 800C28D4 8FB00004 */  lw    $s0, 4($sp)
/* 0C34D8 800C28D8 8FB10008 */  lw    $s1, 8($sp)
/* 0C34DC 800C28DC 8FB2000C */  lw    $s2, 0xc($sp)
/* 0C34E0 800C28E0 03E00008 */  jr    $ra
/* 0C34E4 800C28E4 27BD0010 */   addiu $sp, $sp, 0x10

