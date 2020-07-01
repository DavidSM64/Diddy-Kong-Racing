glabel func_8008CC28
/* 08D828 8008CC28 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 08D82C 8008CC2C 3C0A800E */  lui   $t2, %hi(D_800DF4AC) # $t2, 0x800e
/* 08D830 8008CC30 254AF4AC */  addiu $t2, %lo(D_800DF4AC) # addiu $t2, $t2, -0xb54
/* 08D834 8008CC34 91580000 */  lbu   $t8, ($t2)
/* 08D838 8008CC38 3C08800E */  lui   $t0, %hi(D_800DF4A4) # $t0, 0x800e
/* 08D83C 8008CC3C 3C0B800E */  lui   $t3, %hi(D_800DF764) # $t3, 0x800e
/* 08D840 8008CC40 256BF764 */  addiu $t3, %lo(D_800DF764) # addiu $t3, $t3, -0x89c
/* 08D844 8008CC44 2508F4A4 */  addiu $t0, %lo(D_800DF4A4) # addiu $t0, $t0, -0xb5c
/* 08D848 8008CC48 AFB80024 */  sw    $t8, 0x24($sp)
/* 08D84C 8008CC4C 910E0000 */  lbu   $t6, ($t0)
/* 08D850 8008CC50 8D790000 */  lw    $t9, ($t3)
/* 08D854 8008CC54 3C09800E */  lui   $t1, %hi(D_800DF4A8) # $t1, 0x800e
/* 08D858 8008CC58 24B8FF61 */  addiu $t8, $a1, -0x9f
/* 08D85C 8008CC5C 44982000 */  mtc1  $t8, $f4
/* 08D860 8008CC60 2529F4A8 */  addiu $t1, %lo(D_800DF4A8) # addiu $t1, $t1, -0xb58
/* 08D864 8008CC64 3C03800E */  lui   $v1, %hi(D_800DF75C) # $v1, 0x800e
/* 08D868 8008CC68 912F0000 */  lbu   $t7, ($t1)
/* 08D86C 8008CC6C 8FAC0040 */  lw    $t4, 0x40($sp)
/* 08D870 8008CC70 2463F75C */  addiu $v1, %lo(D_800DF75C) # addiu $v1, $v1, -0x8a4
/* 08D874 8008CC74 AFAE002C */  sw    $t6, 0x2c($sp)
/* 08D878 8008CC78 AFB90020 */  sw    $t9, 0x20($sp)
/* 08D87C 8008CC7C 468021A0 */  cvt.s.w $f6, $f4
/* 08D880 8008CC80 8FAD0044 */  lw    $t5, 0x44($sp)
/* 08D884 8008CC84 8FAE0048 */  lw    $t6, 0x48($sp)
/* 08D888 8008CC88 8C790000 */  lw    $t9, ($v1)
/* 08D88C 8008CC8C 00041140 */  sll   $v0, $a0, 5
/* 08D890 8008CC90 A12C0000 */  sb    $t4, ($t1)
/* 08D894 8008CC94 AFBF0014 */  sw    $ra, 0x14($sp)
/* 08D898 8008CC98 AFA50034 */  sw    $a1, 0x34($sp)
/* 08D89C 8008CC9C AFA60038 */  sw    $a2, 0x38($sp)
/* 08D8A0 8008CCA0 A1070000 */  sb    $a3, ($t0)
/* 08D8A4 8008CCA4 AFAF0028 */  sw    $t7, 0x28($sp)
/* 08D8A8 8008CCA8 A14D0000 */  sb    $t5, ($t2)
/* 08D8AC 8008CCAC AD6E0000 */  sw    $t6, ($t3)
/* 08D8B0 8008CCB0 03226021 */  addu  $t4, $t9, $v0
/* 08D8B4 8008CCB4 E586000C */  swc1  $f6, 0xc($t4)
/* 08D8B8 8008CCB8 8FAD0038 */  lw    $t5, 0x38($sp)
/* 08D8BC 8008CCBC 240E0077 */  li    $t6, 119
/* 08D8C0 8008CCC0 01CD7823 */  subu  $t7, $t6, $t5
/* 08D8C4 8008CCC4 448F4000 */  mtc1  $t7, $f8
/* 08D8C8 8008CCC8 8C780000 */  lw    $t8, ($v1)
/* 08D8CC 8008CCCC 468042A0 */  cvt.s.w $f10, $f8
/* 08D8D0 8008CCD0 0302C821 */  addu  $t9, $t8, $v0
/* 08D8D4 8008CCD4 E72A0010 */  swc1  $f10, 0x10($t9)
/* 08D8D8 8008CCD8 AFA40030 */  sw    $a0, 0x30($sp)
/* 08D8DC 8008CCDC 0C027298 */  jal   func_8009CA60
/* 08D8E0 8008CCE0 AFA2001C */   sw    $v0, 0x1c($sp)
/* 08D8E4 8008CCE4 8FAC002C */  lw    $t4, 0x2c($sp)
/* 08D8E8 8008CCE8 3C01800E */  lui   $at, %hi(D_800DF4A4) # $at, 0x800e
/* 08D8EC 8008CCEC 8FAE0028 */  lw    $t6, 0x28($sp)
/* 08D8F0 8008CCF0 A02CF4A4 */  sb    $t4, %lo(D_800DF4A4)($at)
/* 08D8F4 8008CCF4 3C01800E */  lui   $at, %hi(D_800DF4A8) # $at, 0x800e
/* 08D8F8 8008CCF8 8FAD0024 */  lw    $t5, 0x24($sp)
/* 08D8FC 8008CCFC 8FB80034 */  lw    $t8, 0x34($sp)
/* 08D900 8008CD00 A02EF4A8 */  sb    $t6, %lo(D_800DF4A8)($at)
/* 08D904 8008CD04 3C01800E */  lui   $at, %hi(D_800DF4AC) # $at, 0x800e
/* 08D908 8008CD08 8FAF0020 */  lw    $t7, 0x20($sp)
/* 08D90C 8008CD0C A02DF4AC */  sb    $t5, %lo(D_800DF4AC)($at)
/* 08D910 8008CD10 2719FF5F */  addiu $t9, $t8, -0xa1
/* 08D914 8008CD14 44998000 */  mtc1  $t9, $f16
/* 08D918 8008CD18 3C03800E */  lui   $v1, %hi(D_800DF75C) # $v1, 0x800e
/* 08D91C 8008CD1C 3C01800E */  lui   $at, %hi(D_800DF764) # $at, 0x800e
/* 08D920 8008CD20 2463F75C */  addiu $v1, %lo(D_800DF75C) # addiu $v1, $v1, -0x8a4
/* 08D924 8008CD24 AC2FF764 */  sw    $t7, %lo(D_800DF764)($at)
/* 08D928 8008CD28 468084A0 */  cvt.s.w $f18, $f16
/* 08D92C 8008CD2C 8FA2001C */  lw    $v0, 0x1c($sp)
/* 08D930 8008CD30 8C6C0000 */  lw    $t4, ($v1)
/* 08D934 8008CD34 8FA40030 */  lw    $a0, 0x30($sp)
/* 08D938 8008CD38 01827021 */  addu  $t6, $t4, $v0
/* 08D93C 8008CD3C E5D2000C */  swc1  $f18, 0xc($t6)
/* 08D940 8008CD40 8FAD0038 */  lw    $t5, 0x38($sp)
/* 08D944 8008CD44 240F0079 */  li    $t7, 121
/* 08D948 8008CD48 01EDC023 */  subu  $t8, $t7, $t5
/* 08D94C 8008CD4C 44982000 */  mtc1  $t8, $f4
/* 08D950 8008CD50 8C790000 */  lw    $t9, ($v1)
/* 08D954 8008CD54 468021A0 */  cvt.s.w $f6, $f4
/* 08D958 8008CD58 03226021 */  addu  $t4, $t9, $v0
/* 08D95C 8008CD5C 0C027298 */  jal   func_8009CA60
/* 08D960 8008CD60 E5860010 */   swc1  $f6, 0x10($t4)
/* 08D964 8008CD64 8FBF0014 */  lw    $ra, 0x14($sp)
/* 08D968 8008CD68 27BD0030 */  addiu $sp, $sp, 0x30
/* 08D96C 8008CD6C 03E00008 */  jr    $ra
/* 08D970 8008CD70 00000000 */   nop   

