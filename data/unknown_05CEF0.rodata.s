.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E6A10
.word 0x3FD33333

glabel D_800E6A14
.word 0x33333333

glabel D_800E6A18
.word 0xBFB99999

glabel D_800E6A1C
.word 0x9999999A

glabel D_800E6A20
.word 0x3FB99999

glabel D_800E6A24
.word 0x9999999A

glabel D_800E6A28
.word 0x4085E000

glabel D_800E6A2C
.word 0x00000000
