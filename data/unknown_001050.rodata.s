.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.aligned_text "amSndPlay: Illegal sound effects table index\n"
.aligned_text "amSndPlayDirect: Somebody tried to play illegal sound %d\n"
.aligned_text "Invalid midi sequence index\n"

glabel D_800E49DC
.float 60000000.0

glabel D_800E49E0
.float 46875.0

glabel D_800E49E4
.float 46875.0

glabel D_800E49E8
.float 120000.0

glabel D_800E49EC
.float 60000000.0

