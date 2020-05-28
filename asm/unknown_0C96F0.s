.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C8AF0
/* 0C96F0 800C8AF0 27BDFFC8 */  addiu $sp, $sp, -0x38
/* 0C96F4 800C8AF4 AFBF0024 */  sw    $ra, 0x24($sp)
/* 0C96F8 800C8AF8 AFA40038 */  sw    $a0, 0x38($sp)
/* 0C96FC 800C8AFC AFB20020 */  sw    $s2, 0x20($sp)
/* 0C9700 800C8B00 AFB1001C */  sw    $s1, 0x1c($sp)
/* 0C9704 800C8B04 0C034958 */  jal   __osDisableInt
/* 0C9708 800C8B08 AFB00018 */   sw    $s0, 0x18($sp)
/* 0C970C 800C8B0C 8FAE0038 */  lw    $t6, 0x38($sp)
/* 0C9710 800C8B10 00408025 */  move  $s0, $v0
/* 0C9714 800C8B14 15C00003 */  bnez  $t6, .L800C8B24
/* 0C9718 800C8B18 00000000 */   nop   
/* 0C971C 800C8B1C 10000003 */  b     .L800C8B2C
/* 0C9720 800C8B20 24110004 */   li    $s1, 4
.L800C8B24:
/* 0C9724 800C8B24 8FAF0038 */  lw    $t7, 0x38($sp)
/* 0C9728 800C8B28 95F10010 */  lhu   $s1, 0x10($t7)
.L800C8B2C:
/* 0C972C 800C8B2C 02209025 */  move  $s2, $s1
/* 0C9730 800C8B30 24010002 */  li    $at, 2
/* 0C9734 800C8B34 1241000F */  beq   $s2, $at, .L800C8B74
/* 0C9738 800C8B38 24010004 */   li    $at, 4
/* 0C973C 800C8B3C 12410005 */  beq   $s2, $at, .L800C8B54
/* 0C9740 800C8B40 24010008 */   li    $at, 8
/* 0C9744 800C8B44 1241000B */  beq   $s2, $at, .L800C8B74
/* 0C9748 800C8B48 00000000 */   nop   
/* 0C974C 800C8B4C 10000010 */  b     .L800C8B90
/* 0C9750 800C8B50 00000000 */   nop   
.L800C8B54:
/* 0C9754 800C8B54 3C19800E */  lui   $t9, %hi(D_800E4890) # $t9, 0x800e
/* 0C9758 800C8B58 8F394890 */  lw    $t9, %lo(D_800E4890)($t9)
/* 0C975C 800C8B5C 24180001 */  li    $t8, 1
/* 0C9760 800C8B60 00002025 */  move  $a0, $zero
/* 0C9764 800C8B64 0C034CB3 */  jal   __osEnqueueAndYield
/* 0C9768 800C8B68 A7380010 */   sh    $t8, 0x10($t9)
/* 0C976C 800C8B6C 10000008 */  b     .L800C8B90
/* 0C9770 800C8B70 00000000 */   nop   
.L800C8B74:
/* 0C9774 800C8B74 8FA90038 */  lw    $t1, 0x38($sp)
/* 0C9778 800C8B78 24080001 */  li    $t0, 1
/* 0C977C 800C8B7C A5280010 */  sh    $t0, 0x10($t1)
/* 0C9780 800C8B80 8FAA0038 */  lw    $t2, 0x38($sp)
/* 0C9784 800C8B84 8D440008 */  lw    $a0, 8($t2)
/* 0C9788 800C8B88 0C034B1C */  jal   func_800D2C70
/* 0C978C 800C8B8C 01402825 */   move  $a1, $t2
.L800C8B90:
/* 0C9790 800C8B90 0C034960 */  jal   __osRestoreInt
/* 0C9794 800C8B94 02002025 */   move  $a0, $s0
/* 0C9798 800C8B98 8FBF0024 */  lw    $ra, 0x24($sp)
/* 0C979C 800C8B9C 8FB00018 */  lw    $s0, 0x18($sp)
/* 0C97A0 800C8BA0 8FB1001C */  lw    $s1, 0x1c($sp)
/* 0C97A4 800C8BA4 8FB20020 */  lw    $s2, 0x20($sp)
/* 0C97A8 800C8BA8 03E00008 */  jr    $ra
/* 0C97AC 800C8BAC 27BD0038 */   addiu $sp, $sp, 0x38

glabel osRecvMesg
/* 0C97B0 800C8BB0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0C97B4 800C8BB4 AFBF001C */  sw    $ra, 0x1c($sp)
/* 0C97B8 800C8BB8 AFA40028 */  sw    $a0, 0x28($sp)
/* 0C97BC 800C8BBC AFA5002C */  sw    $a1, 0x2c($sp)
/* 0C97C0 800C8BC0 AFA60030 */  sw    $a2, 0x30($sp)
/* 0C97C4 800C8BC4 AFB10018 */  sw    $s1, 0x18($sp)
/* 0C97C8 800C8BC8 0C034958 */  jal   __osDisableInt
/* 0C97CC 800C8BCC AFB00014 */   sw    $s0, 0x14($sp)
/* 0C97D0 800C8BD0 8FAE0028 */  lw    $t6, 0x28($sp)
/* 0C97D4 800C8BD4 00408025 */  move  $s0, $v0
/* 0C97D8 800C8BD8 8DCF0008 */  lw    $t7, 8($t6)
/* 0C97DC 800C8BDC 15E00012 */  bnez  $t7, .L800C8C28
/* 0C97E0 800C8BE0 00000000 */   nop   
.L800C8BE4:
/* 0C97E4 800C8BE4 8FB80030 */  lw    $t8, 0x30($sp)
/* 0C97E8 800C8BE8 17000005 */  bnez  $t8, .L800C8C00
/* 0C97EC 800C8BEC 00000000 */   nop   
/* 0C97F0 800C8BF0 0C034960 */  jal   __osRestoreInt
/* 0C97F4 800C8BF4 02002025 */   move  $a0, $s0
/* 0C97F8 800C8BF8 10000036 */  b     .L800C8CD4
/* 0C97FC 800C8BFC 2402FFFF */   li    $v0, -1
.L800C8C00:
/* 0C9800 800C8C00 3C08800E */  lui   $t0, %hi(D_800E4890) # $t0, 0x800e
/* 0C9804 800C8C04 8D084890 */  lw    $t0, %lo(D_800E4890)($t0)
/* 0C9808 800C8C08 24190008 */  li    $t9, 8
/* 0C980C 800C8C0C A5190010 */  sh    $t9, 0x10($t0)
/* 0C9810 800C8C10 0C034CB3 */  jal   __osEnqueueAndYield
/* 0C9814 800C8C14 8FA40028 */   lw    $a0, 0x28($sp)
/* 0C9818 800C8C18 8FA90028 */  lw    $t1, 0x28($sp)
/* 0C981C 800C8C1C 8D2A0008 */  lw    $t2, 8($t1)
/* 0C9820 800C8C20 1140FFF0 */  beqz  $t2, .L800C8BE4
/* 0C9824 800C8C24 00000000 */   nop   
.L800C8C28:
/* 0C9828 800C8C28 8FAB002C */  lw    $t3, 0x2c($sp)
/* 0C982C 800C8C2C 11600008 */  beqz  $t3, .L800C8C50
/* 0C9830 800C8C30 00000000 */   nop   
/* 0C9834 800C8C34 8FAC0028 */  lw    $t4, 0x28($sp)
/* 0C9838 800C8C38 8D8E000C */  lw    $t6, 0xc($t4)
/* 0C983C 800C8C3C 8D8D0014 */  lw    $t5, 0x14($t4)
/* 0C9840 800C8C40 000E7880 */  sll   $t7, $t6, 2
/* 0C9844 800C8C44 01AFC021 */  addu  $t8, $t5, $t7
/* 0C9848 800C8C48 8F190000 */  lw    $t9, ($t8)
/* 0C984C 800C8C4C AD790000 */  sw    $t9, ($t3)
.L800C8C50:
/* 0C9850 800C8C50 8FA80028 */  lw    $t0, 0x28($sp)
/* 0C9854 800C8C54 8D09000C */  lw    $t1, 0xc($t0)
/* 0C9858 800C8C58 8D0C0010 */  lw    $t4, 0x10($t0)
/* 0C985C 800C8C5C 252A0001 */  addiu $t2, $t1, 1
/* 0C9860 800C8C60 014C001A */  div   $zero, $t2, $t4
/* 0C9864 800C8C64 00007010 */  mfhi  $t6
/* 0C9868 800C8C68 AD0E000C */  sw    $t6, 0xc($t0)
/* 0C986C 800C8C6C 8FAD0028 */  lw    $t5, 0x28($sp)
/* 0C9870 800C8C70 15800002 */  bnez  $t4, .L800C8C7C
/* 0C9874 800C8C74 00000000 */   nop   
/* 0C9878 800C8C78 0007000D */  break 7
.L800C8C7C:
/* 0C987C 800C8C7C 2401FFFF */  li    $at, -1
/* 0C9880 800C8C80 15810004 */  bne   $t4, $at, .L800C8C94
/* 0C9884 800C8C84 3C018000 */   lui   $at, 0x8000
/* 0C9888 800C8C88 15410002 */  bne   $t2, $at, .L800C8C94
/* 0C988C 800C8C8C 00000000 */   nop   
/* 0C9890 800C8C90 0006000D */  break 6
.L800C8C94:
/* 0C9894 800C8C94 8DAF0008 */  lw    $t7, 8($t5)
/* 0C9898 800C8C98 25F8FFFF */  addiu $t8, $t7, -1
/* 0C989C 800C8C9C ADB80008 */  sw    $t8, 8($t5)
/* 0C98A0 800C8CA0 8FB90028 */  lw    $t9, 0x28($sp)
/* 0C98A4 800C8CA4 8F2B0004 */  lw    $t3, 4($t9)
/* 0C98A8 800C8CA8 8D690000 */  lw    $t1, ($t3)
/* 0C98AC 800C8CAC 11200006 */  beqz  $t1, .L800C8CC8
/* 0C98B0 800C8CB0 00000000 */   nop   
/* 0C98B4 800C8CB4 0C034D05 */  jal   __osPopThread
/* 0C98B8 800C8CB8 27240004 */   addiu $a0, $t9, 4
/* 0C98BC 800C8CBC 00408825 */  move  $s1, $v0
/* 0C98C0 800C8CC0 0C032268 */  jal   osStartThread
/* 0C98C4 800C8CC4 02202025 */   move  $a0, $s1
.L800C8CC8:
/* 0C98C8 800C8CC8 0C034960 */  jal   __osRestoreInt
/* 0C98CC 800C8CCC 02002025 */   move  $a0, $s0
/* 0C98D0 800C8CD0 00001025 */  move  $v0, $zero
.L800C8CD4:
/* 0C98D4 800C8CD4 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0C98D8 800C8CD8 8FB00014 */  lw    $s0, 0x14($sp)
/* 0C98DC 800C8CDC 8FB10018 */  lw    $s1, 0x18($sp)
/* 0C98E0 800C8CE0 03E00008 */  jr    $ra
/* 0C98E4 800C8CE4 27BD0028 */   addiu $sp, $sp, 0x28

/* 0C98E8 800C8CE8 00000000 */  nop   
/* 0C98EC 800C8CEC 00000000 */  nop   
