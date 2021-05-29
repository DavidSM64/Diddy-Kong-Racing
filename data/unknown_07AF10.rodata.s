.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.aligned_text "320 by 240 Point sampled, Non interlaced.\n"
.aligned_text "320 by 240 Anti-aliased, Non interlaced.\n"
.aligned_text "640 by 240 Point sampled, Non interlaced.\n"
.aligned_text "640 by 240 Anti-aliased, Non interlaced.\n"
.aligned_text "640 by 480 Point sampled, Interlaced.\n"
.aligned_text "640 by 480 Anti-aliased, Interlaced.\n"
.aligned_text "640 by 480 Point sampled, Interlaced, De-flickered.\n"
.aligned_text "640 by 480 Anti-aliased, Interlaced, De-flickered.\n"

glabel D_800E7AFC
.word 0x3F9B26CA

glabel D_800E7B00
.word 0x3F8CCCCD

glabel D_800E7B04
.word 0x3FAAAAAB

glabel D_800E7B08
.word 0x3FAAAAAB

glabel D_800E7B0C
.word 0x8007A5AC
.word 0x8007A5D0
.word 0x8007A658
.word 0x8007A6C0
.word 0x8007A728
.word 0x8007A750
.word 0x8007A778
.word 0x8007A7A0
.word 0x00000000
