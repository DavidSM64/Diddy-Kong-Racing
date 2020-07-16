glabel func_800C69C4
/* 0C75C4 800C69C4 27BDFAC0 */  addiu $sp, $sp, -0x540
/* 0C75C8 800C69C8 AFB30028 */  sw    $s3, 0x28($sp)
/* 0C75CC 800C69CC 3C138013 */  lui   $s3, %hi(D_8012AAD4) # $s3, 0x8013
/* 0C75D0 800C69D0 8E73AAD4 */  lw    $s3, %lo(D_8012AAD4)($s3)
/* 0C75D4 800C69D4 AFB4002C */  sw    $s4, 0x2c($sp)
/* 0C75D8 800C69D8 AFB20024 */  sw    $s2, 0x24($sp)
/* 0C75DC 800C69DC 24080005 */  li    $t0, 5
/* 0C75E0 800C69E0 3C14800E */  lui   $s4, %hi(D_800E3768) # $s4, 0x800e
/* 0C75E4 800C69E4 3C128013 */  lui   $s2, %hi(D_8012AAD0) # $s2, 0x8013
/* 0C75E8 800C69E8 0268082B */  sltu  $at, $s3, $t0
/* 0C75EC 800C69EC AFBF0030 */  sw    $ra, 0x30($sp)
/* 0C75F0 800C69F0 AFB10020 */  sw    $s1, 0x20($sp)
/* 0C75F4 800C69F4 AFB0001C */  sw    $s0, 0x1c($sp)
/* 0C75F8 800C69F8 8E943768 */  lw    $s4, %lo(D_800E3768)($s4)
/* 0C75FC 800C69FC 10200008 */  beqz  $at, .L800C6A20
/* 0C7600 800C6A00 8E52AAD0 */   lw    $s2, %lo(D_8012AAD0)($s2)
.L800C6A04:
/* 0C7604 800C6A04 92820000 */  lbu   $v0, ($s4)
/* 0C7608 800C6A08 26940001 */  addiu $s4, $s4, 1
/* 0C760C 800C6A0C 02621004 */  sllv  $v0, $v0, $s3
/* 0C7610 800C6A10 26730008 */  addiu $s3, $s3, 8
/* 0C7614 800C6A14 0268082A */  slt   $at, $s3, $t0
/* 0C7618 800C6A18 1420FFFA */  bnez  $at, .L800C6A04
/* 0C761C 800C6A1C 02429025 */   or    $s2, $s2, $v0
.L800C6A20:
/* 0C7620 800C6A20 02689822 */  sub   $s3, $s3, $t0
/* 0C7624 800C6A24 3251001F */  andi  $s1, $s2, 0x1f
/* 0C7628 800C6A28 0268082B */  sltu  $at, $s3, $t0
/* 0C762C 800C6A2C 26310101 */  addiu $s1, $s1, 0x101
/* 0C7630 800C6A30 10200008 */  beqz  $at, .L800C6A54
/* 0C7634 800C6A34 01129006 */   srlv  $s2, $s2, $t0
.L800C6A38:
/* 0C7638 800C6A38 92820000 */  lbu   $v0, ($s4)
/* 0C763C 800C6A3C 26940001 */  addiu $s4, $s4, 1
/* 0C7640 800C6A40 02621004 */  sllv  $v0, $v0, $s3
/* 0C7644 800C6A44 26730008 */  addiu $s3, $s3, 8
/* 0C7648 800C6A48 0268082A */  slt   $at, $s3, $t0
/* 0C764C 800C6A4C 1420FFFA */  bnez  $at, .L800C6A38
/* 0C7650 800C6A50 02429025 */   or    $s2, $s2, $v0
.L800C6A54:
/* 0C7654 800C6A54 3250001F */  andi  $s0, $s2, 0x1f
/* 0C7658 800C6A58 01129006 */  srlv  $s2, $s2, $t0
/* 0C765C 800C6A5C 02689822 */  sub   $s3, $s3, $t0
/* 0C7660 800C6A60 24080004 */  li    $t0, 4
/* 0C7664 800C6A64 0268082B */  sltu  $at, $s3, $t0
/* 0C7668 800C6A68 10200008 */  beqz  $at, .L800C6A8C
/* 0C766C 800C6A6C 26100001 */   addiu $s0, $s0, 1
.L800C6A70:
/* 0C7670 800C6A70 92820000 */  lbu   $v0, ($s4)
/* 0C7674 800C6A74 26940001 */  addiu $s4, $s4, 1
/* 0C7678 800C6A78 02621004 */  sllv  $v0, $v0, $s3
/* 0C767C 800C6A7C 26730008 */  addiu $s3, $s3, 8
/* 0C7680 800C6A80 0268082A */  slt   $at, $s3, $t0
/* 0C7684 800C6A84 1420FFFA */  bnez  $at, .L800C6A70
/* 0C7688 800C6A88 02429025 */   or    $s2, $s2, $v0
.L800C6A8C:
/* 0C768C 800C6A8C 324A000F */  andi  $t2, $s2, 0xf
/* 0C7690 800C6A90 254A0004 */  addiu $t2, $t2, 4
/* 0C7694 800C6A94 3C19800F */  lui   $t9, %hi(gzip_border) # $t9, 0x800f
/* 0C7698 800C6A98 01129006 */  srlv  $s2, $s2, $t0
/* 0C769C 800C6A9C 02689822 */  sub   $s3, $s3, $t0
/* 0C76A0 800C6AA0 000A4825 */  or    $t1, $zero, $t2
/* 0C76A4 800C6AA4 273993C0 */  addiu $t9, %lo(gzip_border) # addiu $t9, $t9, -0x6c40
/* 0C76A8 800C6AA8 11400019 */  beqz  $t2, .L800C6B10
/* 0C76AC 800C6AAC 23AF0044 */   addi  $t7, $sp, 0x44
.L800C6AB0:
/* 0C76B0 800C6AB0 24080003 */  li    $t0, 3
/* 0C76B4 800C6AB4 0268082B */  sltu  $at, $s3, $t0
/* 0C76B8 800C6AB8 50200009 */  beql  $at, $zero, .L800C6AE0
/* 0C76BC 800C6ABC 93230000 */   lbu   $v1, ($t9)
.L800C6AC0:
/* 0C76C0 800C6AC0 92820000 */  lbu   $v0, ($s4)
/* 0C76C4 800C6AC4 26940001 */  addiu $s4, $s4, 1
/* 0C76C8 800C6AC8 02621004 */  sllv  $v0, $v0, $s3
/* 0C76CC 800C6ACC 26730008 */  addiu $s3, $s3, 8
/* 0C76D0 800C6AD0 0268082A */  slt   $at, $s3, $t0
/* 0C76D4 800C6AD4 1420FFFA */  bnez  $at, .L800C6AC0
/* 0C76D8 800C6AD8 02429025 */   or    $s2, $s2, $v0
/* 0C76DC 800C6ADC 93230000 */  lbu   $v1, ($t9)
.L800C6AE0:
/* 0C76E0 800C6AE0 32420007 */  andi  $v0, $s2, 7
/* 0C76E4 800C6AE4 254AFFFF */  addiu $t2, $t2, -1
/* 0C76E8 800C6AE8 00031880 */  sll   $v1, $v1, 2
/* 0C76EC 800C6AEC 006F1821 */  addu  $v1, $v1, $t7
/* 0C76F0 800C6AF0 AC620000 */  sw    $v0, ($v1)
/* 0C76F4 800C6AF4 01129006 */  srlv  $s2, $s2, $t0
/* 0C76F8 800C6AF8 02689822 */  sub   $s3, $s3, $t0
/* 0C76FC 800C6AFC 1540FFEC */  bnez  $t2, .L800C6AB0
/* 0C7700 800C6B00 27390001 */   addiu $t9, $t9, 1
/* 0C7704 800C6B04 2D210013 */  sltiu $at, $t1, 0x13
/* 0C7708 800C6B08 5020000A */  beql  $at, $zero, .L800C6B34
/* 0C770C 800C6B0C 240D0007 */   li    $t5, 7
.L800C6B10:
/* 0C7710 800C6B10 93230000 */  lbu   $v1, ($t9)
/* 0C7714 800C6B14 25290001 */  addiu $t1, $t1, 1
/* 0C7718 800C6B18 29210013 */  slti  $at, $t1, 0x13
/* 0C771C 800C6B1C 00031880 */  sll   $v1, $v1, 2
/* 0C7720 800C6B20 006F1821 */  addu  $v1, $v1, $t7
/* 0C7724 800C6B24 AC600000 */  sw    $zero, ($v1)
/* 0C7728 800C6B28 1420FFF9 */  bnez  $at, .L800C6B10
/* 0C772C 800C6B2C 27390001 */   addiu $t9, $t9, 1
/* 0C7730 800C6B30 240D0007 */  li    $t5, 7
.L800C6B34:
/* 0C7734 800C6B34 23A80034 */  addi  $t0, $sp, 0x34
/* 0C7738 800C6B38 23A90038 */  addi  $t1, $sp, 0x38
/* 0C773C 800C6B3C AFAD0038 */  sw    $t5, 0x38($sp)
/* 0C7740 800C6B40 23A40044 */  addi  $a0, $sp, 0x44
/* 0C7744 800C6B44 24050013 */  li    $a1, 19
/* 0C7748 800C6B48 24060013 */  li    $a2, 19
/* 0C774C 800C6B4C 24070000 */  li    $a3, 0
/* 0C7750 800C6B50 AFA00010 */  sw    $zero, 0x10($sp)
/* 0C7754 800C6B54 AFA80014 */  sw    $t0, 0x14($sp)
/* 0C7758 800C6B58 0C03189D */  jal   func_800C6274
/* 0C775C 800C6B5C AFA90018 */   sw    $t1, 0x18($sp)
/* 0C7760 800C6B60 23A90038 */  addi  $t1, $sp, 0x38
/* 0C7764 800C6B64 8D2D0000 */  lw    $t5, ($t1)
/* 0C7768 800C6B68 3C02800F */  lui   $v0, %hi(gzip_mask_bits) # $v0, 0x800f
/* 0C776C 800C6B6C 2442948C */  addiu $v0, %lo(gzip_mask_bits) # addiu $v0, $v0, -0x6b74
/* 0C7770 800C6B70 000D1840 */  sll   $v1, $t5, 1
/* 0C7774 800C6B74 23A80034 */  addi  $t0, $sp, 0x34
/* 0C7778 800C6B78 00431020 */  add   $v0, $v0, $v1
/* 0C777C 800C6B7C 8D0E0000 */  lw    $t6, ($t0)
/* 0C7780 800C6B80 0230C820 */  add   $t9, $s1, $s0
/* 0C7784 800C6B84 84580000 */  lh    $t8, ($v0)
/* 0C7788 800C6B88 23AF0044 */  addi  $t7, $sp, 0x44
/* 0C778C 800C6B8C 240A0000 */  li    $t2, 0
glabel func_800C6B90
/* 0C7790 800C6B90 1320005F */  beqz  $t9, .L800C6D10
/* 0C7794 800C6B94 026D082B */   sltu  $at, $s3, $t5
/* 0C7798 800C6B98 50200009 */  beql  $at, $zero, .L800C6BC0
/* 0C779C 800C6B9C 02581024 */   and   $v0, $s2, $t8
.L800C6BA0:
/* 0C77A0 800C6BA0 92820000 */  lbu   $v0, ($s4)
/* 0C77A4 800C6BA4 26940001 */  addiu $s4, $s4, 1
/* 0C77A8 800C6BA8 02621004 */  sllv  $v0, $v0, $s3
/* 0C77AC 800C6BAC 26730008 */  addiu $s3, $s3, 8
/* 0C77B0 800C6BB0 026D082A */  slt   $at, $s3, $t5
/* 0C77B4 800C6BB4 1420FFFA */  bnez  $at, .L800C6BA0
/* 0C77B8 800C6BB8 02429025 */   or    $s2, $s2, $v0
/* 0C77BC 800C6BBC 02581024 */  and   $v0, $s2, $t8
.L800C6BC0:
/* 0C77C0 800C6BC0 000210C0 */  sll   $v0, $v0, 3
/* 0C77C4 800C6BC4 01C24821 */  addu  $t1, $t6, $v0
/* 0C77C8 800C6BC8 95280004 */  lhu   $t0, 4($t1)
/* 0C77CC 800C6BCC 91220001 */  lbu   $v0, 1($t1)
/* 0C77D0 800C6BD0 29010010 */  slti  $at, $t0, 0x10
/* 0C77D4 800C6BD4 00529006 */  srlv  $s2, $s2, $v0
/* 0C77D8 800C6BD8 1420001C */  bnez  $at, .L800C6C4C
/* 0C77DC 800C6BDC 02629822 */   sub   $s3, $s3, $v0
/* 0C77E0 800C6BE0 24010010 */  li    $at, 16
/* 0C77E4 800C6BE4 1101001E */  beq   $t0, $at, .L800C6C60
/* 0C77E8 800C6BE8 24010011 */   li    $at, 17
/* 0C77EC 800C6BEC 51010033 */  beql  $t0, $at, .L800C6CBC
/* 0C77F0 800C6BF0 24080003 */   li    $t0, 3
/* 0C77F4 800C6BF4 24080007 */  li    $t0, 7
/* 0C77F8 800C6BF8 0268082B */  sltu  $at, $s3, $t0
/* 0C77FC 800C6BFC 50200009 */  beql  $at, $zero, .L800C6C24
/* 0C7800 800C6C00 3249007F */   andi  $t1, $s2, 0x7f
.L800C6C04:
/* 0C7804 800C6C04 92820000 */  lbu   $v0, ($s4)
/* 0C7808 800C6C08 26940001 */  addiu $s4, $s4, 1
/* 0C780C 800C6C0C 02621004 */  sllv  $v0, $v0, $s3
/* 0C7810 800C6C10 26730008 */  addiu $s3, $s3, 8
/* 0C7814 800C6C14 0268082A */  slt   $at, $s3, $t0
/* 0C7818 800C6C18 1420FFFA */  bnez  $at, .L800C6C04
/* 0C781C 800C6C1C 02429025 */   or    $s2, $s2, $v0
/* 0C7820 800C6C20 3249007F */  andi  $t1, $s2, 0x7f
.L800C6C24:
/* 0C7824 800C6C24 2529000B */  addiu $t1, $t1, 0xb
/* 0C7828 800C6C28 01129006 */  srlv  $s2, $s2, $t0
/* 0C782C 800C6C2C 02689822 */  sub   $s3, $s3, $t0
/* 0C7830 800C6C30 0329C823 */  subu  $t9, $t9, $t1
.L800C6C34:
/* 0C7834 800C6C34 2529FFFF */  addiu $t1, $t1, -1
/* 0C7838 800C6C38 ADE00000 */  sw    $zero, ($t7)
/* 0C783C 800C6C3C 1520FFFD */  bnez  $t1, .L800C6C34
/* 0C7840 800C6C40 25EF0004 */   addiu $t7, $t7, 4
/* 0C7844 800C6C44 08031AE4 */  j     func_800C6B90
/* 0C7848 800C6C48 240A0000 */   li    $t2, 0

.L800C6C4C:
/* 0C784C 800C6C4C ADE80000 */  sw    $t0, ($t7)
/* 0C7850 800C6C50 25EF0004 */  addiu $t7, $t7, 4
/* 0C7854 800C6C54 2739FFFF */  addiu $t9, $t9, -1
/* 0C7858 800C6C58 08031AE4 */  j     func_800C6B90
/* 0C785C 800C6C5C 00085025 */   or    $t2, $zero, $t0

.L800C6C60:
/* 0C7860 800C6C60 24080002 */  li    $t0, 2
/* 0C7864 800C6C64 0268082B */  sltu  $at, $s3, $t0
/* 0C7868 800C6C68 50200009 */  beql  $at, $zero, .L800C6C90
/* 0C786C 800C6C6C 32490003 */   andi  $t1, $s2, 3
.L800C6C70:
/* 0C7870 800C6C70 92820000 */  lbu   $v0, ($s4)
/* 0C7874 800C6C74 26940001 */  addiu $s4, $s4, 1
/* 0C7878 800C6C78 02621004 */  sllv  $v0, $v0, $s3
/* 0C787C 800C6C7C 26730008 */  addiu $s3, $s3, 8
/* 0C7880 800C6C80 0268082A */  slt   $at, $s3, $t0
/* 0C7884 800C6C84 1420FFFA */  bnez  $at, .L800C6C70
/* 0C7888 800C6C88 02429025 */   or    $s2, $s2, $v0
/* 0C788C 800C6C8C 32490003 */  andi  $t1, $s2, 3
.L800C6C90:
/* 0C7890 800C6C90 21290003 */  addi  $t1, $t1, 3
/* 0C7894 800C6C94 01129006 */  srlv  $s2, $s2, $t0
/* 0C7898 800C6C98 02689822 */  sub   $s3, $s3, $t0
/* 0C789C 800C6C9C 0329C823 */  subu  $t9, $t9, $t1
.L800C6CA0:
/* 0C78A0 800C6CA0 2529FFFF */  addiu $t1, $t1, -1
/* 0C78A4 800C6CA4 ADEA0000 */  sw    $t2, ($t7)
/* 0C78A8 800C6CA8 1520FFFD */  bnez  $t1, .L800C6CA0
/* 0C78AC 800C6CAC 25EF0004 */   addiu $t7, $t7, 4
/* 0C78B0 800C6CB0 08031AE4 */  j     func_800C6B90
/* 0C78B4 800C6CB4 00000000 */   nop   

/* 0C78B8 800C6CB8 24080003 */  li    $t0, 3
.L800C6CBC:
/* 0C78BC 800C6CBC 0268082B */  sltu  $at, $s3, $t0
/* 0C78C0 800C6CC0 50200009 */  beql  $at, $zero, .L800C6CE8
/* 0C78C4 800C6CC4 32490007 */   andi  $t1, $s2, 7
.L800C6CC8:
/* 0C78C8 800C6CC8 92820000 */  lbu   $v0, ($s4)
/* 0C78CC 800C6CCC 26940001 */  addiu $s4, $s4, 1
/* 0C78D0 800C6CD0 02621004 */  sllv  $v0, $v0, $s3
/* 0C78D4 800C6CD4 26730008 */  addiu $s3, $s3, 8
/* 0C78D8 800C6CD8 0268082A */  slt   $at, $s3, $t0
/* 0C78DC 800C6CDC 1420FFFA */  bnez  $at, .L800C6CC8
/* 0C78E0 800C6CE0 02429025 */   or    $s2, $s2, $v0
/* 0C78E4 800C6CE4 32490007 */  andi  $t1, $s2, 7
.L800C6CE8:
/* 0C78E8 800C6CE8 21290003 */  addi  $t1, $t1, 3
/* 0C78EC 800C6CEC 01129006 */  srlv  $s2, $s2, $t0
/* 0C78F0 800C6CF0 02689822 */  sub   $s3, $s3, $t0
/* 0C78F4 800C6CF4 0329C823 */  subu  $t9, $t9, $t1
.L800C6CF8:
/* 0C78F8 800C6CF8 2529FFFF */  addiu $t1, $t1, -1
/* 0C78FC 800C6CFC ADE00000 */  sw    $zero, ($t7)
/* 0C7900 800C6D00 1520FFFD */  bnez  $t1, .L800C6CF8
/* 0C7904 800C6D04 25EF0004 */   addiu $t7, $t7, 4
/* 0C7908 800C6D08 08031AE4 */  j     func_800C6B90
/* 0C790C 800C6D0C 240A0000 */   li    $t2, 0

.L800C6D10:
/* 0C7910 800C6D10 3C01800E */  lui   $at, %hi(D_800E3768) # $at, 0x800e
/* 0C7914 800C6D14 AC343768 */  sw    $s4, %lo(D_800E3768)($at)
/* 0C7918 800C6D18 3C018013 */  lui   $at, %hi(D_8012AAD0) # $at, 0x8013
/* 0C791C 800C6D1C 24080009 */  li    $t0, 9
/* 0C7920 800C6D20 AC32AAD0 */  sw    $s2, %lo(D_8012AAD0)($at)
/* 0C7924 800C6D24 AFA80038 */  sw    $t0, 0x38($sp)
/* 0C7928 800C6D28 3C02800F */  lui   $v0, %hi(gzip_cplext) # $v0, 0x800f
/* 0C792C 800C6D2C 3C018013 */  lui   $at, %hi(D_8012AAD4) # $at, 0x8013
/* 0C7930 800C6D30 3C07800F */  lui   $a3, %hi(gzip_cplens) # $a3, 0x800f
/* 0C7934 800C6D34 24429412 */  addiu $v0, %lo(gzip_cplext) # addiu $v0, $v0, -0x6bee
/* 0C7938 800C6D38 23A30034 */  addi  $v1, $sp, 0x34
/* 0C793C 800C6D3C 23A80038 */  addi  $t0, $sp, 0x38
/* 0C7940 800C6D40 AC33AAD4 */  sw    $s3, %lo(D_8012AAD4)($at)
/* 0C7944 800C6D44 23A40044 */  addi  $a0, $sp, 0x44
/* 0C7948 800C6D48 00112825 */  or    $a1, $zero, $s1
/* 0C794C 800C6D4C 24060101 */  li    $a2, 257
/* 0C7950 800C6D50 24E793D4 */  addiu $a3, %lo(gzip_cplens) # addiu $a3, $a3, -0x6c2c
/* 0C7954 800C6D54 AFA20010 */  sw    $v0, 0x10($sp)
/* 0C7958 800C6D58 AFA30014 */  sw    $v1, 0x14($sp)
/* 0C795C 800C6D5C 0C03189D */  jal   func_800C6274
/* 0C7960 800C6D60 AFA80018 */   sw    $t0, 0x18($sp)
/* 0C7964 800C6D64 23A40044 */  addi  $a0, $sp, 0x44
/* 0C7968 800C6D68 00111080 */  sll   $v0, $s1, 2
/* 0C796C 800C6D6C 24080006 */  li    $t0, 6
/* 0C7970 800C6D70 00822021 */  addu  $a0, $a0, $v0
/* 0C7974 800C6D74 AFA80040 */  sw    $t0, 0x40($sp)
/* 0C7978 800C6D78 3C02800F */  lui   $v0, %hi(gzip_cpdext) # $v0, 0x800f
/* 0C797C 800C6D7C 3C07800F */  lui   $a3, %hi(gzip_cpdist) # $a3, 0x800f
/* 0C7980 800C6D80 2442946E */  addiu $v0, %lo(gzip_cpdext) # addiu $v0, $v0, -0x6b92
/* 0C7984 800C6D84 23A3003C */  addi  $v1, $sp, 0x3c
/* 0C7988 800C6D88 23A80040 */  addi  $t0, $sp, 0x40
/* 0C798C 800C6D8C 00102825 */  or    $a1, $zero, $s0
/* 0C7990 800C6D90 24060000 */  li    $a2, 0
/* 0C7994 800C6D94 24E79432 */  addiu $a3, %lo(gzip_cpdist) # addiu $a3, $a3, -0x6bce
/* 0C7998 800C6D98 AFA20010 */  sw    $v0, 0x10($sp)
/* 0C799C 800C6D9C AFA30014 */  sw    $v1, 0x14($sp)
/* 0C79A0 800C6DA0 0C03189D */  jal   func_800C6274
/* 0C79A4 800C6DA4 AFA80018 */   sw    $t0, 0x18($sp)
/* 0C79A8 800C6DA8 8FA40034 */  lw    $a0, 0x34($sp)
/* 0C79AC 800C6DAC 8FA5003C */  lw    $a1, 0x3c($sp)
/* 0C79B0 800C6DB0 8FA60038 */  lw    $a2, 0x38($sp)
/* 0C79B4 800C6DB4 0C031C10 */  jal   func_800C7040
/* 0C79B8 800C6DB8 8FA70040 */   lw    $a3, 0x40($sp)
/* 0C79BC 800C6DBC 8FBF0030 */  lw    $ra, 0x30($sp)
/* 0C79C0 800C6DC0 8FB4002C */  lw    $s4, 0x2c($sp)
/* 0C79C4 800C6DC4 8FB30028 */  lw    $s3, 0x28($sp)
/* 0C79C8 800C6DC8 8FB20024 */  lw    $s2, 0x24($sp)
/* 0C79CC 800C6DCC 8FB10020 */  lw    $s1, 0x20($sp)
/* 0C79D0 800C6DD0 8FB0001C */  lw    $s0, 0x1c($sp)
/* 0C79D4 800C6DD4 03E00008 */  jr    $ra
/* 0C79D8 800C6DD8 27BD0540 */   addiu $sp, $sp, 0x540

