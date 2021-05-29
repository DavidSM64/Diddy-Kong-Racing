.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E6ED0
.aligned_text "WARNING: Stack overflow/underflow!!!\n"

.word 0x00000000
.word 0x00000000
