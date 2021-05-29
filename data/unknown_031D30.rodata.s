.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E5F60
.word 0xBDCCCCCD

glabel D_800E5F64
.word 0xBDCCCCCD

glabel D_800E5F68
.word 0x3F34FDF4

glabel D_800E5F6C
.word 0x3EE66666

glabel D_800E5F70
.word 0xBDCCCCCD
.word 0x00000000
.word 0x00000000
.word 0x00000000
.word 0x80033A70
.word 0x80033AA4
.word 0x80033AE4
.word 0x80033B48
.word 0x80033BB4
.word 0x00000000
.word 0x00000000
.word 0x00000000
