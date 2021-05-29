.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E7C90
.aligned_text "SCREEN: No out of range!!\n"

.word 0x00000000
