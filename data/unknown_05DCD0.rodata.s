.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E6A30
.word 0x3FD33333

glabel D_800E6A34
.word 0x33333333

glabel D_800E6A38
.word 0xBFB99999

glabel D_800E6A3C
.word 0x9999999A

glabel D_800E6A40
.word 0x3FB99999

glabel D_800E6A44
.word 0x9999999A

glabel D_800E6A48
.word 0x4085E000

glabel D_800E6A4C
.word 0x00000000

glabel D_800E6A50
.word 0x3FD33333

glabel D_800E6A54
.word 0x33333333

glabel D_800E6A58
.word 0xBFD33333

glabel D_800E6A5C
.word 0x33333333

glabel D_800E6A60
.word 0x3FD147AE

glabel D_800E6A64
.word 0x147AE148

glabel D_800E6A68
.word 0x3FDCCCCC

glabel D_800E6A6C
.word 0xCCCCCCCD

glabel D_800E6A70
.word 0x8005DBEC
.word 0x8005DC10
.word 0x8005DC48
.word 0x8005DC64
.word 0x8005DCBC
.word 0x8005DCE8

glabel D_800E6A88
.word 0xBFB99999

glabel D_800E6A8C
.word 0x9999999A

glabel D_800E6A90
.word 0x3FB99999

glabel D_800E6A94
.word 0x9999999A

glabel D_800E6A98
.word 0x4085E000

glabel D_800E6A9C
.word 0x00000000
