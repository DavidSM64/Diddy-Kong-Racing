.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E9550
.word 0x80000000
.word 0x00000000

glabel D_800E9558
.word 0x80000000
.word 0x00000000
