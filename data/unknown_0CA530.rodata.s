.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E94B0
.word 0x412E8480
.word 0x00000000
.word 0x412E8480
.word 0x00000000

glabel D_800E94C0
.word 0x3F8012EF

glabel D_800E94C4
.word 0x3F7FDA28
.word 0x00000000
.word 0x00000000
