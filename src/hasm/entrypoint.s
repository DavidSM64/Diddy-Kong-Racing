.include "macro.inc"

/* assembler directives */
.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */
.set gp=64     /* allow use of 64-bit general purpose registers */

.section .bss

glabel entrypointThreadStack
.space 0x1000

.section .text, "ax"

leaf entrypoint
lui        $t0, %hi(__BSS_SECTION_START)
lui        $t1, %hi(__BSS_SECTION_SIZE)
addiu      $t0, $t0, %lo(__BSS_SECTION_START)
ori        $t1, $t1, %lo(__BSS_SECTION_SIZE)
.L80000410:
addi       $t1, $t1, -0x8
sw         $zero, 0x0($t0)
sw         $zero, 0x4($t0)
bnez       $t1, .L80000410
 addi      $t0, $t0, 0x8
lui        $t2, %hi(mainproc)
lui        $sp, %hi(entrypointThreadStack + 0x1000)
addiu      $t2, $t2, %lo(mainproc)
jr         $t2
 addiu     $sp, $sp, %lo(entrypointThreadStack + 0x1000)
nop
nop
nop
nop
nop
nop
.end entrypoint
