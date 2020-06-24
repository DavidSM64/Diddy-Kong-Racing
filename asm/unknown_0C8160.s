.include "globals.inc"
.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel func_800C7560
/* 0C8160 800C7560 24030010 */  li    $v1, 16
/* 0C8164 800C7564 30AE000F */  andi  $t6, $a1, 0xf
/* 0C8168 800C7568 006E1023 */  subu  $v0, $v1, $t6
/* 0C816C 800C756C 10620003 */  beq   $v1, $v0, .L800C757C
/* 0C8170 800C7570 00A27821 */   addu  $t7, $a1, $v0
/* 0C8174 800C7574 10000002 */  b     .L800C7580
/* 0C8178 800C7578 AC8F0000 */   sw    $t7, ($a0)
.L800C757C:
/* 0C817C 800C757C AC850000 */  sw    $a1, ($a0)
.L800C7580:
/* 0C8180 800C7580 8C980000 */  lw    $t8, ($a0)
/* 0C8184 800C7584 AC860008 */  sw    $a2, 8($a0)
/* 0C8188 800C7588 AC80000C */  sw    $zero, 0xc($a0)
/* 0C818C 800C758C 03E00008 */  jr    $ra
/* 0C8190 800C7590 AC980004 */   sw    $t8, 4($a0)

/* 0C8194 800C7594 00000000 */  nop   
/* 0C8198 800C7598 00000000 */  nop   
/* 0C819C 800C759C 00000000 */  nop   
