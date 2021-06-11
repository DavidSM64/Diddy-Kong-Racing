/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80000400 */

.include "globals.inc"
.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

.section .text

glabel entrypoint
/* 001000 80000400 3C08800F */  lui   $t0, %hi(gBssSectionStart) # $t0, 0x800f
/* 001004 80000404 3C090004 */  lui   $t1, %hi(__BSS_SECTION_SIZE) # lui $t1, 4
/* 001008 80000408 2508BF60 */  addiu $t0, %lo(gBssSectionStart) # addiu $t0, $t0, -0x40a0
/* 00100C 8000040C 35291490 */  ori   $t1, %lo(__BSS_SECTION_SIZE) # ori $t1, $t1, 0x1490
.L80000410:
/* 001010 80000410 2129FFF8 */  addi  $t1, $t1, -8
/* 001014 80000414 AD000000 */  sw    $zero, ($t0)
/* 001018 80000418 AD000004 */  sw    $zero, 4($t0)
/* 00101C 8000041C 1520FFFC */  bnez  $t1, .L80000410
/* 001020 80000420 21080008 */   addi  $t0, $t0, 8
/* 001024 80000424 3C0A8006 */  lui   $t2, %hi(func_80065D40) # $t2, 0x8006
/* 001028 80000428 3C1D8012 */  lui   $sp, %hi(D_80120AC0) # $sp, 0x8012
/* 00102C 8000042C 254A5D40 */  addiu $t2, %lo(func_80065D40) # addiu $t2, $t2, 0x5d40
/* 001030 80000430 01400008 */  jr    $t2
/* 001034 80000434 27BD0AC0 */   addiu $sp, %lo(D_80120AC0) # addiu $sp, $sp, 0xac0
/* 001038 80000438 00000000 */  nop   
/* 00103C 8000043C 00000000 */  nop   
/* 001040 80000440 00000000 */  nop   
/* 001044 80000444 00000000 */  nop   
/* 001048 80000448 00000000 */  nop   
/* 00104C 8000044C 00000000 */  nop   
