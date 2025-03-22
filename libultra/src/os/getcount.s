.include "macro.inc"

/* assembler directives */
.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */
.set gp=64     /* allow use of 64-bit general purpose registers */

.section .text, "ax"

leaf osGetCount
mfc0       $v0, $9 /* C0_COUNT */
jr         $ra
nop
.end osGetCount
