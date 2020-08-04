/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D46B0 */

.include "globals.inc"
.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel osInvalICache
/* 0D52B0 800D46B0 18A00011 */  blez  $a1, .L800D46F8
/* 0D52B4 800D46B4 00000000 */   nop   
/* 0D52B8 800D46B8 240B4000 */  li    $t3, 16384
/* 0D52BC 800D46BC 00AB082B */  sltu  $at, $a1, $t3
/* 0D52C0 800D46C0 1020000F */  beqz  $at, .L800D4700
/* 0D52C4 800D46C4 00000000 */   nop   
/* 0D52C8 800D46C8 00804025 */  move  $t0, $a0
/* 0D52CC 800D46CC 00854821 */  addu  $t1, $a0, $a1
/* 0D52D0 800D46D0 0109082B */  sltu  $at, $t0, $t1
/* 0D52D4 800D46D4 10200008 */  beqz  $at, .L800D46F8
/* 0D52D8 800D46D8 00000000 */   nop   
/* 0D52DC 800D46DC 310A001F */  andi  $t2, $t0, 0x1f
/* 0D52E0 800D46E0 2529FFE0 */  addiu $t1, $t1, -0x20
/* 0D52E4 800D46E4 010A4023 */  subu  $t0, $t0, $t2
.L800D46E8:
/* 0D52E8 800D46E8 BD100000 */  cache 0x10, ($t0)
/* 0D52EC 800D46EC 0109082B */  sltu  $at, $t0, $t1
/* 0D52F0 800D46F0 1420FFFD */  bnez  $at, .L800D46E8
/* 0D52F4 800D46F4 25080020 */   addiu $t0, $t0, 0x20
.L800D46F8:
/* 0D52F8 800D46F8 03E00008 */  jr    $ra
/* 0D52FC 800D46FC 00000000 */   nop   

.L800D4700:
/* 0D5300 800D4700 3C088000 */  lui   $t0, %hi(D_80000020) # $t0, 0x8000
/* 0D5304 800D4704 010B4821 */  addu  $t1, $t0, $t3
/* 0D5308 800D4708 2529FFE0 */  addiu $t1, $t1, -0x20
.L800D470C:
/* 0D530C 800D470C BD000000 */  cache 0, ($t0)
/* 0D5310 800D4710 0109082B */  sltu  $at, $t0, $t1
/* 0D5314 800D4714 1420FFFD */  bnez  $at, .L800D470C
/* 0D5318 800D4718 25080020 */   addiu $t0, %lo(D_80000020) # addiu $t0, $t0, 0x20
/* 0D531C 800D471C 03E00008 */  jr    $ra
/* 0D5320 800D4720 00000000 */   nop   

/* 0D5324 800D4724 00000000 */  nop   
/* 0D5328 800D4728 00000000 */  nop   
/* 0D532C 800D472C 00000000 */  nop   
