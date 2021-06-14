/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4580 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel __osSetFpcCsr
/* 0D5180 800D4580 4442F800 */  cfc1  $v0, $31
/* 0D5184 800D4584 44C4F800 */  ctc1  $a0, $31
/* 0D5188 800D4588 03E00008 */  jr    $ra
/* 0D518C 800D458C 00000000 */   nop   
