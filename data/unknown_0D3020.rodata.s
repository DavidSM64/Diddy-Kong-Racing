.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E97C0
.word 0x3FF00000
.word 0x00000000
.word 0xBFC55554
.word 0xBC83656D
.word 0x3F8110ED
.word 0x3804C2A0
.word 0xBF29F6FF
.word 0xEEA56814
.word 0x3EC5DBDF
.word 0x0E314BFE

glabel D_800E97E8
.word 0x3FD45F30
.word 0x6DC9C883

glabel D_800E97F0
.word 0x400921FB
.word 0x50000000

glabel D_800E97F8
.word 0x3E6110B4
.word 0x611A6263
.word 0x00000000
.word 0x00000000
.word 0x00000000
.word 0x00000000

glabel D_800E9810
.word 0x3FF00000
.word 0x00000000
.word 0xBFC55554
.word 0xBC83656D
.word 0x3F8110ED
.word 0x3804C2A0
.word 0xBF29F6FF
.word 0xEEA56814
.word 0x3EC5DBDF
.word 0x0E314BFE
.word 0x3FD45F30
.word 0x6DC9C883

glabel D_800E9840
.word 0x400921FB
.word 0x50000000

glabel D_800E9848
.word 0x3E6110B4
.word 0x611A6263
.word 0x00000000
.word 0x00000000
.word 0x00000000
.word 0x00000000

glabel D_800E9860
.word 0x40240000
.word 0x00000000
.word 0x40590000
.word 0x00000000
.word 0x40C38800
.word 0x00000000
.word 0x4197D784
.word 0x00000000
.word 0x4341C379
.word 0x37E08000
.word 0x4693B8B5
.word 0xB5056E17
.word 0x4D384F03
.word 0xE93FF9F5
.word 0x5A827748
.word 0xF9301D32
.word 0x75154FDD
.word 0x7F73BF3C

glabel D_800E98A8
.aligned_text "NaN"

glabel D_800E98AC
.aligned_text "Inf"

glabel D_800E98B0
.word 0x30000000
.word 0x00000000

glabel D_800E98B8
.word 0x4197D784
.word 0x00000000

glabel D_800E98C0
.word 0x7F810000
.word 0x00000000
.word 0x00000000
.word 0x00000000
