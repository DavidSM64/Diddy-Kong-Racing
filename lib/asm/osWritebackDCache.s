/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4630 */

.include "globals.inc"
.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used


glabel osWritebackDCache
/* 0D5230 800D4630 18A00011 */  blez  $a1, .L800D4678
/* 0D5234 800D4634 00000000 */   nop   
/* 0D5238 800D4638 240B2000 */  li    $t3, 8192
/* 0D523C 800D463C 00AB082B */  sltu  $at, $a1, $t3
/* 0D5240 800D4640 1020000F */  beqz  $at, .L800D4680
/* 0D5244 800D4644 00000000 */   nop   
/* 0D5248 800D4648 00804025 */  move  $t0, $a0
/* 0D524C 800D464C 00854821 */  addu  $t1, $a0, $a1
/* 0D5250 800D4650 0109082B */  sltu  $at, $t0, $t1
/* 0D5254 800D4654 10200008 */  beqz  $at, .L800D4678
/* 0D5258 800D4658 00000000 */   nop   
/* 0D525C 800D465C 310A000F */  andi  $t2, $t0, 0xf
/* 0D5260 800D4660 2529FFF0 */  addiu $t1, $t1, -0x10
/* 0D5264 800D4664 010A4023 */  subu  $t0, $t0, $t2
.L800D4668:
/* 0D5268 800D4668 BD190000 */  cache 0x19, ($t0)
/* 0D526C 800D466C 0109082B */  sltu  $at, $t0, $t1
/* 0D5270 800D4670 1420FFFD */  bnez  $at, .L800D4668
/* 0D5274 800D4674 25080010 */   addiu $t0, $t0, 0x10
.L800D4678:
/* 0D5278 800D4678 03E00008 */  jr    $ra
/* 0D527C 800D467C 00000000 */   nop   

.L800D4680:
/* 0D5280 800D4680 3C088000 */  lui   $t0, %hi(D_80000010) # $t0, 0x8000
/* 0D5284 800D4684 010B4821 */  addu  $t1, $t0, $t3
/* 0D5288 800D4688 2529FFF0 */  addiu $t1, $t1, -0x10
.L800D468C:
/* 0D528C 800D468C BD010000 */  cache 1, ($t0)
/* 0D5290 800D4690 0109082B */  sltu  $at, $t0, $t1
/* 0D5294 800D4694 1420FFFD */  bnez  $at, .L800D468C
/* 0D5298 800D4698 25080010 */   addiu $t0, %lo(D_80000010) # addiu $t0, $t0, 0x10
/* 0D529C 800D469C 03E00008 */  jr    $ra
/* 0D52A0 800D46A0 00000000 */   nop   

/* 0D52A4 800D46A4 00000000 */  nop   
/* 0D52A8 800D46A8 00000000 */  nop   
/* 0D52AC 800D46AC 00000000 */  nop   
