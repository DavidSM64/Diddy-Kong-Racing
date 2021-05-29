.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.word 0x3F91DF46
.word 0x9D353918
.word 0x00000000
.word 0x00000000
.word 0x800D2A70
.word 0x800D2964
.word 0x800D29A4
.word 0x800D2A90
.word 0x800D2A90
.word 0x800D29E0
.word 0x800D2A28
.word 0x00000000
.word 0x00141818
.word 0x1C1C1C1C
.word 0x20202020
.word 0x20202020
.word 0x00040808
.word 0x0C0C0C0C
.word 0x10101010
.word 0x10101010
.word 0x800D3168
.word 0x800D3130
.word 0x800D3110
.word 0x800D2F74
.word 0x800D2F20
.word 0x800D30B4
.word 0x800D2EE8
.word 0x800D2EF4
.word 0x800D2F00
.word 0x00000000
.word 0x00000000
.word 0x00000000
