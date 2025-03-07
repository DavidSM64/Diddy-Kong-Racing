.include "macro.inc"

/* assembler directives */
.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */
.set gp=64     /* allow use of 64-bit general purpose registers */

.section .text, "ax"

leaf __osGetSR
mfc0       $v0, $12 /* C0_SR */
jr         $ra
 nop
nop
.end __osGetSR
