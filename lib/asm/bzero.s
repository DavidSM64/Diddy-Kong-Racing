/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D04E0 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel bzero /* Official name: _blkclr */
/* 0D10E0 800D04E0 28A1000C */  slti  $at, $a1, 0xc
/* 0D10E4 800D04E4 1420001D */  bnez  $at, .L800D055C
/* 0D10E8 800D04E8 00041823 */   negu  $v1, $a0
/* 0D10EC 800D04EC 30630003 */  andi  $v1, $v1, 3
/* 0D10F0 800D04F0 10600003 */  beqz  $v1, .L800D0500
/* 0D10F4 800D04F4 00A32823 */   subu  $a1, $a1, $v1
/* 0D10F8 800D04F8 A8800000 */  swl   $zero, ($a0)
/* 0D10FC 800D04FC 00832021 */  addu  $a0, $a0, $v1
.L800D0500:
/* 0D1100 800D0500 2401FFE0 */  li    $at, -32
/* 0D1104 800D0504 00A13824 */  and   $a3, $a1, $at
/* 0D1108 800D0508 10E0000C */  beqz  $a3, .L800D053C
/* 0D110C 800D050C 00A72823 */   subu  $a1, $a1, $a3
/* 0D1110 800D0510 00E43821 */  addu  $a3, $a3, $a0
.L800D0514:
/* 0D1114 800D0514 24840020 */  addiu $a0, $a0, 0x20
/* 0D1118 800D0518 AC80FFE0 */  sw    $zero, -0x20($a0)
/* 0D111C 800D051C AC80FFE4 */  sw    $zero, -0x1c($a0)
/* 0D1120 800D0520 AC80FFE8 */  sw    $zero, -0x18($a0)
/* 0D1124 800D0524 AC80FFEC */  sw    $zero, -0x14($a0)
/* 0D1128 800D0528 AC80FFF0 */  sw    $zero, -0x10($a0)
/* 0D112C 800D052C AC80FFF4 */  sw    $zero, -0xc($a0)
/* 0D1130 800D0530 AC80FFF8 */  sw    $zero, -8($a0)
/* 0D1134 800D0534 1487FFF7 */  bne   $a0, $a3, .L800D0514
/* 0D1138 800D0538 AC80FFFC */   sw    $zero, -4($a0)
.L800D053C:
/* 0D113C 800D053C 2401FFFC */  li    $at, -4
/* 0D1140 800D0540 00A13824 */  and   $a3, $a1, $at
/* 0D1144 800D0544 10E00005 */  beqz  $a3, .L800D055C
/* 0D1148 800D0548 00A72823 */   subu  $a1, $a1, $a3
/* 0D114C 800D054C 00E43821 */  addu  $a3, $a3, $a0
.L800D0550:
/* 0D1150 800D0550 24840004 */  addiu $a0, $a0, 4
/* 0D1154 800D0554 1487FFFE */  bne   $a0, $a3, .L800D0550
/* 0D1158 800D0558 AC80FFFC */   sw    $zero, -4($a0)
.L800D055C:
/* 0D115C 800D055C 18A00005 */  blez  $a1, .L800D0574
/* 0D1160 800D0560 00000000 */   nop   
/* 0D1164 800D0564 00A42821 */  addu  $a1, $a1, $a0
.L800D0568:
/* 0D1168 800D0568 24840001 */  addiu $a0, $a0, 1
/* 0D116C 800D056C 1485FFFE */  bne   $a0, $a1, .L800D0568
/* 0D1170 800D0570 A080FFFF */   sb    $zero, -1($a0)
.L800D0574:
/* 0D1174 800D0574 03E00008 */  jr    $ra
/* 0D1178 800D0578 00000000 */   nop   

/* 0D117C 800D057C 00000000 */  nop   

