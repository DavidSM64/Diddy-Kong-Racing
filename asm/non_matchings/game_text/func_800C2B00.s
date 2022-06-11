glabel func_800C2B00
/* 0C3700 800C2B00 27BDFFB8 */  addiu $sp, $sp, -0x48
/* 0C3704 800C2B04 AFBF0044 */  sw    $ra, 0x44($sp)
/* 0C3708 800C2B08 AFBE0040 */  sw    $fp, 0x40($sp)
/* 0C370C 800C2B0C AFB7003C */  sw    $s7, 0x3c($sp)
/* 0C3710 800C2B10 AFB60038 */  sw    $s6, 0x38($sp)
/* 0C3714 800C2B14 AFB50034 */  sw    $s5, 0x34($sp)
/* 0C3718 800C2B18 AFB40030 */  sw    $s4, 0x30($sp)
/* 0C371C 800C2B1C AFB3002C */  sw    $s3, 0x2c($sp)
/* 0C3720 800C2B20 AFB20028 */  sw    $s2, 0x28($sp)
/* 0C3724 800C2B24 AFB10024 */  sw    $s1, 0x24($sp)
/* 0C3728 800C2B28 AFB00020 */  sw    $s0, 0x20($sp)
/* 0C372C 800C2B2C 0C031525 */  jal   assign_dialogue_box_id
/* 0C3730 800C2B30 24040006 */   li    $a0, 6
/* 0C3734 800C2B34 3C118013 */  lui   $s1, %hi(sDialogueYPos2) # $s1, 0x8013
/* 0C3738 800C2B38 2631A7B4 */  addiu $s1, %lo(sDialogueYPos2) # addiu $s1, $s1, -0x584c
/* 0C373C 800C2B3C 3C108013 */  lui   $s0, %hi(sDialogueYPos1) # $s0, 0x8013
/* 0C3740 800C2B40 3C158013 */  lui   $s5, %hi(sDialogueXPos1) # $s5, 0x8013
/* 0C3744 800C2B44 3C168013 */  lui   $s6, %hi(sDialogueXPos2) # $s6, 0x8013
/* 0C3748 800C2B48 862E0000 */  lh    $t6, ($s1)
/* 0C374C 800C2B4C 26D6A7B2 */  addiu $s6, %lo(sDialogueXPos2) # addiu $s6, $s6, -0x584e
/* 0C3750 800C2B50 26B5A7AE */  addiu $s5, %lo(sDialogueXPos1) # addiu $s5, $s5, -0x5852
/* 0C3754 800C2B54 2610A7B0 */  addiu $s0, %lo(sDialogueYPos1) # addiu $s0, $s0, -0x5850
/* 0C3758 800C2B58 86060000 */  lh    $a2, ($s0)
/* 0C375C 800C2B5C 86A50000 */  lh    $a1, ($s5)
/* 0C3760 800C2B60 86C70000 */  lh    $a3, ($s6)
/* 0C3764 800C2B64 24040006 */  li    $a0, 6
/* 0C3768 800C2B68 0C0313B7 */  jal   set_current_dialogue_box_coords
/* 0C376C 800C2B6C AFAE0010 */   sw    $t6, 0x10($sp)
/* 0C3770 800C2B70 3C178013 */  lui   $s7, %hi(sDialogueAlpha) # $s7, 0x8013
/* 0C3774 800C2B74 26F7A7A8 */  addiu $s7, %lo(sDialogueAlpha) # addiu $s7, $s7, -0x5858
/* 0C3778 800C2B78 86EF0000 */  lh    $t7, ($s7)
/* 0C377C 800C2B7C 24040006 */  li    $a0, 6
/* 0C3780 800C2B80 000FC080 */  sll   $t8, $t7, 2
/* 0C3784 800C2B84 030FC021 */  addu  $t8, $t8, $t7
/* 0C3788 800C2B88 0018C140 */  sll   $t8, $t8, 5
/* 0C378C 800C2B8C 0018CA03 */  sra   $t9, $t8, 8
/* 0C3790 800C2B90 AFB90010 */  sw    $t9, 0x10($sp)
/* 0C3794 800C2B94 24050040 */  li    $a1, 64
/* 0C3798 800C2B98 24060060 */  li    $a2, 96
/* 0C379C 800C2B9C 0C0313EF */  jal   set_current_dialogue_background_colour
/* 0C37A0 800C2BA0 24070060 */   li    $a3, 96
/* 0C37A4 800C2BA4 24040006 */  li    $a0, 6
/* 0C37A8 800C2BA8 00002825 */  move  $a1, $zero
/* 0C37AC 800C2BAC 00003025 */  move  $a2, $zero
/* 0C37B0 800C2BB0 00003825 */  move  $a3, $zero
/* 0C37B4 800C2BB4 0C031414 */  jal   set_current_text_background_colour
/* 0C37B8 800C2BB8 AFA00010 */   sw    $zero, 0x10($sp)
/* 0C37BC 800C2BBC 3C1E8013 */  lui   $fp, %hi(D_8012A7B8) # $fp, 0x8013
/* 0C37C0 800C2BC0 27DEA7B8 */  addiu $fp, %lo(D_8012A7B8) # addiu $fp, $fp, -0x5848
/* 0C37C4 800C2BC4 87C20000 */  lh    $v0, ($fp)
/* 0C37C8 800C2BC8 86280000 */  lh    $t0, ($s1)
/* 0C37CC 800C2BCC 86090000 */  lh    $t1, ($s0)
/* 0C37D0 800C2BD0 00025880 */  sll   $t3, $v0, 2
/* 0C37D4 800C2BD4 01625823 */  subu  $t3, $t3, $v0
/* 0C37D8 800C2BD8 000B5880 */  sll   $t3, $t3, 2
/* 0C37DC 800C2BDC 01095023 */  subu  $t2, $t0, $t1
/* 0C37E0 800C2BE0 014B6023 */  subu  $t4, $t2, $t3
/* 0C37E4 800C2BE4 00026840 */  sll   $t5, $v0, 1
/* 0C37E8 800C2BE8 018D9823 */  subu  $s3, $t4, $t5
/* 0C37EC 800C2BEC 26730002 */  addiu $s3, $s3, 2
/* 0C37F0 800C2BF0 00137043 */  sra   $t6, $s3, 1
/* 0C37F4 800C2BF4 01C09825 */  move  $s3, $t6
/* 0C37F8 800C2BF8 1840004E */  blez  $v0, .L800C2D34
/* 0C37FC 800C2BFC 0000A025 */   move  $s4, $zero
/* 0C3800 800C2C00 3C128013 */  lui   $s2, %hi(D_8012A7C0) # $s2, 0x8013
/* 0C3804 800C2C04 2652A7C0 */  addiu $s2, %lo(D_8012A7C0) # addiu $s2, $s2, -0x5840
.L800C2C08:
/* 0C3808 800C2C08 8E4F0000 */  lw    $t7, ($s2)
/* 0C380C 800C2C0C 24040006 */  li    $a0, 6
/* 0C3810 800C2C10 91E50005 */  lbu   $a1, 5($t7)
/* 0C3814 800C2C14 0C0313DF */  jal   set_dialogue_font
/* 0C3818 800C2C18 00000000 */   nop   
/* 0C381C 800C2C1C 8E420000 */  lw    $v0, ($s2)
/* 0C3820 800C2C20 24010004 */  li    $at, 4
/* 0C3824 800C2C24 90500006 */  lbu   $s0, 6($v0)
/* 0C3828 800C2C28 240B00FF */  li    $t3, 255
/* 0C382C 800C2C2C 16010009 */  bne   $s0, $at, .L800C2C54
/* 0C3830 800C2C30 24010001 */   li    $at, 1
/* 0C3834 800C2C34 86D80000 */  lh    $t8, ($s6)
/* 0C3838 800C2C38 86B90000 */  lh    $t9, ($s5)
/* 0C383C 800C2C3C 00000000 */  nop   
/* 0C3840 800C2C40 03198823 */  subu  $s1, $t8, $t9
/* 0C3844 800C2C44 00114043 */  sra   $t0, $s1, 1
/* 0C3848 800C2C48 1000000A */  b     .L800C2C74
/* 0C384C 800C2C4C 01008825 */   move  $s1, $t0
/* 0C3850 800C2C50 24010001 */  li    $at, 1
.L800C2C54:
/* 0C3854 800C2C54 16010007 */  bne   $s0, $at, .L800C2C74
/* 0C3858 800C2C58 24110008 */   li    $s1, 8
/* 0C385C 800C2C5C 86C90000 */  lh    $t1, ($s6)
/* 0C3860 800C2C60 86AA0000 */  lh    $t2, ($s5)
/* 0C3864 800C2C64 00000000 */  nop   
/* 0C3868 800C2C68 012A8823 */  subu  $s1, $t1, $t2
/* 0C386C 800C2C6C 10000001 */  b     .L800C2C74
/* 0C3870 800C2C70 2631FFF8 */   addiu $s1, $s1, -8
.L800C2C74:
/* 0C3874 800C2C74 90450001 */  lbu   $a1, 1($v0)
/* 0C3878 800C2C78 90460002 */  lbu   $a2, 2($v0)
/* 0C387C 800C2C7C 90470003 */  lbu   $a3, 3($v0)
/* 0C3880 800C2C80 AFAB0010 */  sw    $t3, 0x10($sp)
/* 0C3884 800C2C84 904C0004 */  lbu   $t4, 4($v0)
/* 0C3888 800C2C88 86ED0000 */  lh    $t5, ($s7)
/* 0C388C 800C2C8C 24040006 */  li    $a0, 6
/* 0C3890 800C2C90 018D0019 */  multu $t4, $t5
/* 0C3894 800C2C94 00007012 */  mflo  $t6
/* 0C3898 800C2C98 000E7A03 */  sra   $t7, $t6, 8
/* 0C389C 800C2C9C 0C031400 */  jal   set_current_text_colour
/* 0C38A0 800C2CA0 AFAF0014 */   sw    $t7, 0x14($sp)
/* 0C38A4 800C2CA4 8E470000 */  lw    $a3, ($s2)
/* 0C38A8 800C2CA8 24180001 */  li    $t8, 1
/* 0C38AC 800C2CAC AFB80010 */  sw    $t8, 0x10($sp)
/* 0C38B0 800C2CB0 24040006 */  li    $a0, 6
/* 0C38B4 800C2CB4 02202825 */  move  $a1, $s1
/* 0C38B8 800C2CB8 02603025 */  move  $a2, $s3
/* 0C38BC 800C2CBC AFB00014 */  sw    $s0, 0x14($sp)
/* 0C38C0 800C2CC0 0C03145A */  jal   render_dialogue_text
/* 0C38C4 800C2CC4 24E70008 */   addiu $a3, $a3, 8
/* 0C38C8 800C2CC8 86E80000 */  lh    $t0, ($s7)
/* 0C38CC 800C2CCC 241900FF */  li    $t9, 255
/* 0C38D0 800C2CD0 00084A00 */  sll   $t1, $t0, 8
/* 0C38D4 800C2CD4 01284823 */  subu  $t1, $t1, $t0
/* 0C38D8 800C2CD8 00095203 */  sra   $t2, $t1, 8
/* 0C38DC 800C2CDC AFAA0014 */  sw    $t2, 0x14($sp)
/* 0C38E0 800C2CE0 AFB90010 */  sw    $t9, 0x10($sp)
/* 0C38E4 800C2CE4 24040006 */  li    $a0, 6
/* 0C38E8 800C2CE8 00002825 */  move  $a1, $zero
/* 0C38EC 800C2CEC 00003025 */  move  $a2, $zero
/* 0C38F0 800C2CF0 0C031400 */  jal   set_current_text_colour
/* 0C38F4 800C2CF4 00003825 */   move  $a3, $zero
/* 0C38F8 800C2CF8 8E470000 */  lw    $a3, ($s2)
/* 0C38FC 800C2CFC 240B0001 */  li    $t3, 1
/* 0C3900 800C2D00 AFAB0010 */  sw    $t3, 0x10($sp)
/* 0C3904 800C2D04 24040006 */  li    $a0, 6
/* 0C3908 800C2D08 26250001 */  addiu $a1, $s1, 1
/* 0C390C 800C2D0C 26660001 */  addiu $a2, $s3, 1
/* 0C3910 800C2D10 AFB00014 */  sw    $s0, 0x14($sp)
/* 0C3914 800C2D14 0C03145A */  jal   render_dialogue_text
/* 0C3918 800C2D18 24E70008 */   addiu $a3, $a3, 8
/* 0C391C 800C2D1C 87CC0000 */  lh    $t4, ($fp)
/* 0C3920 800C2D20 26940001 */  addiu $s4, $s4, 1
/* 0C3924 800C2D24 028C082A */  slt   $at, $s4, $t4
/* 0C3928 800C2D28 26520004 */  addiu $s2, $s2, 4
/* 0C392C 800C2D2C 1420FFB6 */  bnez  $at, .L800C2C08
/* 0C3930 800C2D30 2673000E */   addiu $s3, $s3, 0xe
.L800C2D34:
/* 0C3934 800C2D34 0C03157D */  jal   open_dialogue_box
/* 0C3938 800C2D38 24040006 */   li    $a0, 6
/* 0C393C 800C2D3C 8FBF0044 */  lw    $ra, 0x44($sp)
/* 0C3940 800C2D40 8FB00020 */  lw    $s0, 0x20($sp)
/* 0C3944 800C2D44 8FB10024 */  lw    $s1, 0x24($sp)
/* 0C3948 800C2D48 8FB20028 */  lw    $s2, 0x28($sp)
/* 0C394C 800C2D4C 8FB3002C */  lw    $s3, 0x2c($sp)
/* 0C3950 800C2D50 8FB40030 */  lw    $s4, 0x30($sp)
/* 0C3954 800C2D54 8FB50034 */  lw    $s5, 0x34($sp)
/* 0C3958 800C2D58 8FB60038 */  lw    $s6, 0x38($sp)
/* 0C395C 800C2D5C 8FB7003C */  lw    $s7, 0x3c($sp)
/* 0C3960 800C2D60 8FBE0040 */  lw    $fp, 0x40($sp)
/* 0C3964 800C2D64 03E00008 */  jr    $ra
/* 0C3968 800C2D68 27BD0048 */   addiu $sp, $sp, 0x48

