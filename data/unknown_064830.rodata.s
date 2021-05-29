.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.word 0x80063FE8
.word 0x8006401C
.word 0x8006407C
.word 0x80064050
.word 0x800640A8
.word 0x800640D4
.word 0x80064144
.word 0x800641C4

glabel D_800E6E90
.word 0x4105221B

glabel D_800E6E94
.word 0x3D3FB61B
.word 0x00000000
.word 0x00000000

.word 0x80064AD8
.word 0x80064AE4
.word 0x80064AFC
.word 0x80064B08
.word 0x80064AF0
.word 0x80064B14

glabel D_800E6EB8
.word 0x4105221B

glabel D_800E6EBC
.word 0x3D3FB61B
