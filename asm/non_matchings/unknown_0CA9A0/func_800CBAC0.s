glabel func_800CBAC0
/* 0CC6C0 800CBAC0 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0CC6C4 800CBAC4 AFB3002C */  sw    $s3, 0x2c($sp)
/* 0CC6C8 800CBAC8 AFB50028 */  sw    $s5, 0x28($sp)
/* 0CC6CC 800CBACC 00137400 */  sll   $t6, $s3, 0x10
/* 0CC6D0 800CBAD0 0015C400 */  sll   $t8, $s5, 0x10
/* 0CC6D4 800CBAD4 0018AC03 */  sra   $s5, $t8, 0x10
/* 0CC6D8 800CBAD8 000E9C03 */  sra   $s3, $t6, 0x10
/* 0CC6DC 800CBADC 1A20001A */  blez  $s1, .L800CBB48
/* 0CC6E0 800CBAE0 AFBF0014 */   sw    $ra, 0x14($sp)
/* 0CC6E4 800CBAE4 8E590030 */  lw    $t9, 0x30($s2)
/* 0CC6E8 800CBAE8 8E440044 */  lw    $a0, 0x44($s2)
/* 0CC6EC 800CBAEC 02202825 */  move  $a1, $s1
/* 0CC6F0 800CBAF0 0320F809 */  jalr  $t9
/* 0CC6F4 800CBAF4 8E460034 */  lw    $a2, 0x34($s2)
/* 0CC6F8 800CBAF8 30460007 */  andi  $a2, $v0, 7
/* 0CC6FC 800CBAFC 02268821 */  addu  $s1, $s1, $a2
/* 0CC700 800CBB00 326EFFFF */  andi  $t6, $s3, 0xffff
/* 0CC704 800CBB04 3C010800 */  lui   $at, 0x800
/* 0CC708 800CBB08 01C17825 */  or    $t7, $t6, $at
/* 0CC70C 800CBB0C 32380007 */  andi  $t8, $s1, 7
/* 0CC710 800CBB10 02002025 */  move  $a0, $s0
/* 0CC714 800CBB14 0238C823 */  subu  $t9, $s1, $t8
/* 0CC718 800CBB18 272E0008 */  addiu $t6, $t9, 8
/* 0CC71C 800CBB1C AC8F0000 */  sw    $t7, ($a0)
/* 0CC720 800CBB20 26100008 */  addiu $s0, $s0, 8
/* 0CC724 800CBB24 31CFFFFF */  andi  $t7, $t6, 0xffff
/* 0CC728 800CBB28 02002825 */  move  $a1, $s0
/* 0CC72C 800CBB2C AC8F0004 */  sw    $t7, 4($a0)
/* 0CC730 800CBB30 0046C823 */  subu  $t9, $v0, $a2
/* 0CC734 800CBB34 3C180400 */  lui   $t8, 0x400
/* 0CC738 800CBB38 ACB80000 */  sw    $t8, ($a1)
/* 0CC73C 800CBB3C ACB90004 */  sw    $t9, 4($a1)
/* 0CC740 800CBB40 10000002 */  b     .L800CBB4C
/* 0CC744 800CBB44 26100008 */   addiu $s0, $s0, 8
.L800CBB48:
/* 0CC748 800CBB48 00003025 */  move  $a2, $zero
.L800CBB4C:
/* 0CC74C 800CBB4C 328E0002 */  andi  $t6, $s4, 2
/* 0CC750 800CBB50 11C00009 */  beqz  $t6, .L800CBB78
/* 0CC754 800CBB54 02001025 */   move  $v0, $s0
/* 0CC758 800CBB58 3C0F0F00 */  lui   $t7, 0xf00
/* 0CC75C 800CBB5C AC4F0000 */  sw    $t7, ($v0)
/* 0CC760 800CBB60 8E580018 */  lw    $t8, 0x18($s2)
/* 0CC764 800CBB64 3C011FFF */  lui   $at, (0x1FFFFFFF >> 16) # lui $at, 0x1fff
/* 0CC768 800CBB68 3421FFFF */  ori   $at, (0x1FFFFFFF & 0xFFFF) # ori $at, $at, 0xffff
/* 0CC76C 800CBB6C 0301C824 */  and   $t9, $t8, $at
/* 0CC770 800CBB70 AC590004 */  sw    $t9, 4($v0)
/* 0CC774 800CBB74 26100008 */  addiu $s0, $s0, 8
.L800CBB78:
/* 0CC778 800CBB78 02667021 */  addu  $t6, $s3, $a2
/* 0CC77C 800CBB7C 31CFFFFF */  andi  $t7, $t6, 0xffff
/* 0CC780 800CBB80 3C010800 */  lui   $at, 0x800
/* 0CC784 800CBB84 01E1C025 */  or    $t8, $t7, $at
/* 0CC788 800CBB88 02001825 */  move  $v1, $s0
/* 0CC78C 800CBB8C AC780000 */  sw    $t8, ($v1)
/* 0CC790 800CBB90 00167840 */  sll   $t7, $s6, 1
/* 0CC794 800CBB94 31F8FFFF */  andi  $t8, $t7, 0xffff
/* 0CC798 800CBB98 00157400 */  sll   $t6, $s5, 0x10
/* 0CC79C 800CBB9C 01D8C825 */  or    $t9, $t6, $t8
/* 0CC7A0 800CBBA0 328F00FF */  andi  $t7, $s4, 0xff
/* 0CC7A4 800CBBA4 26100008 */  addiu $s0, $s0, 8
/* 0CC7A8 800CBBA8 000F7400 */  sll   $t6, $t7, 0x10
/* 0CC7AC 800CBBAC 3C010100 */  lui   $at, 0x100
/* 0CC7B0 800CBBB0 AC790004 */  sw    $t9, 4($v1)
/* 0CC7B4 800CBBB4 01C1C025 */  or    $t8, $t6, $at
/* 0CC7B8 800CBBB8 02002025 */  move  $a0, $s0
/* 0CC7BC 800CBBBC AC980000 */  sw    $t8, ($a0)
/* 0CC7C0 800CBBC0 8E590014 */  lw    $t9, 0x14($s2)
/* 0CC7C4 800CBBC4 3C011FFF */  lui   $at, (0x1FFFFFFF >> 16) # lui $at, 0x1fff
/* 0CC7C8 800CBBC8 3421FFFF */  ori   $at, (0x1FFFFFFF & 0xFFFF) # ori $at, $at, 0xffff
/* 0CC7CC 800CBBCC 03217824 */  and   $t7, $t9, $at
/* 0CC7D0 800CBBD0 AC8F0004 */  sw    $t7, 4($a0)
/* 0CC7D4 800CBBD4 AE400040 */  sw    $zero, 0x40($s2)
/* 0CC7D8 800CBBD8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0CC7DC 800CBBDC 26100008 */  addiu $s0, $s0, 8
/* 0CC7E0 800CBBE0 02001025 */  move  $v0, $s0
/* 0CC7E4 800CBBE4 03E00008 */  jr    $ra
/* 0CC7E8 800CBBE8 27BD0018 */   addiu $sp, $sp, 0x18

