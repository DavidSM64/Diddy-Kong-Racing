.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E6AA0
.word 0x3FD33333

glabel D_800E6AA4
.word 0x33333333

glabel D_800E6AA8
.word 0x4085E000

glabel D_800E6AAC
.word 0x00000000
