.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E6AB0
.word 0x3FD33333

glabel D_800E6AB4
.word 0x33333333

glabel D_800E6AB8
.word 0xBFD33333

glabel D_800E6ABC
.word 0x33333333

glabel D_800E6AC0
.word 0x3FD99999

glabel D_800E6AC4
.word 0x9999999A

glabel D_800E6AC8
.word 0x3FDCCCCC

glabel D_800E6ACC
.word 0xCCCCCCCD

glabel D_800E6AD0
.word 0x8005EE9C
.word 0x8005EEC0
.word 0x8005EEF8
.word 0x8005EF14
.word 0x8005EF6C
.word 0x8005EF98

glabel D_800E6AE8
.word 0xBFB99999

glabel D_800E6AEC
.word 0x9999999A

glabel D_800E6AF0
.word 0x3FB99999

glabel D_800E6AF4
.word 0x9999999A
.word 0x00000000
.word 0x00000000

glabel D_800E6B00
.word 0x3FD33333

glabel D_800E6B04
.word 0x33333333

glabel D_800E6B08
.word 0xBFD33333

glabel D_800E6B0C
.word 0x33333333

glabel D_800E6B10
.word 0x3FD99999

glabel D_800E6B14
.word 0x9999999A
.word 0x00000000
.word 0x00000000
