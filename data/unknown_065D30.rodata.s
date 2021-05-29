.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E6EC0
.word 0x412E8480

glabel D_800E6EC4
.word 0x00000000
.word 0x00000000
.word 0x00000000
