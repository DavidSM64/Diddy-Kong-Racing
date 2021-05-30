.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E9560
.aligned_text "samples >= 0"

glabel D_800E9570
.aligned_text "env.c"

glabel D_800E9578
.aligned_text "samples <= AL_MAX_RSP_SAMPLES"

glabel D_800E9598
.aligned_text "env.c"

glabel D_800E95A0
.aligned_text "source"

glabel D_800E95A8
.aligned_text "env.c"

glabel D_800E95B0
.word 0x800CA870
.word 0x800CA8C4
.word 0x800CA8C4
.word 0x800CA8C4
.word 0x800CA8C4
.word 0x800CA8C4
.word 0x800CA8C4
.word 0x800CA8C4
.word 0x800CA8C4
.word 0x800CA8C4
.word 0x800CA8C4
.word 0x800CA460
.word 0x800CA460
.word 0x800CA22C
.word 0x800CA7A8
.word 0x800CA828
.word 0x800CA460

.word 0x00000000

glabel D_800E95F8
.word 0x40EFFFE0

glabel D_800E95FC
.word 0x00000000

glabel D_800E9600
.word 0x800CC0C0
.word 0x800CC150
.word 0x800CC150
.word 0x800CC0C8
.word 0x800CC150
.word 0x800CC150
.word 0x800CC134
.word 0x800CC144
.word 0x800CC104
.word 0x00000000

glabel D_800E9628
.word 0x3FFFFFD6
.word 0x0E94EE39
.word 0x3FFFFEB0
.word 0x00000000
.word 0x00000000
.word 0x00000000
