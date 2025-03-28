.include "macro.inc"

/* assembler directives */
.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */
.set gp=64     /* allow use of 64-bit general purpose registers */

.section .text, "ax"

leaf __osDisableInt
mfc0       $t0, $12
addiu      $at, $zero, -0x2
and        $t1, $t0, $at
mtc0       $t1, $12
andi       $v0, $t0, 0x1
nop
jr         $ra
nop
.end __osDisableInt

leaf __osRestoreInt
mfc0       $t0, $12
or         $t0, $t0, $a0
mtc0       $t0, $12
nop
nop
jr         $ra
 nop
.end __osRestoreInt
