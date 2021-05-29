.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.aligned_text "Camera Error: Illegal mode!\n"
.aligned_text "Camera Error: Illegal player no!\n"
.aligned_text "cameraPushSprMtx: model stack overflow!!\n"
.aligned_text "\nCam do 2D sprite called with NULL pointer!"
.aligned_text "CamDo2DSprite FrameNo Overflow !!!\n"
.aligned_text "cameraPushModelMtx: model stack overflow!!\n"
.aligned_text "camPushModelMtx: bsp stack overflow!!\n"
.aligned_text "camPopModelMtx: model stack negative overflow!!\n"
.aligned_text "camPopModelMtx: bsp stack negative overflow!!\n"

glabel D_800E7078
.aligned_text "%x."

glabel D_800E707C
.aligned_text "%x  "

glabel D_800E7084
.aligned_text "\n"

glabel D_800E7088
.aligned_text "\n"

glabel D_800E708C
.aligned_text "%f  "

glabel D_800E7094
.aligned_text "\n"

glabel D_800E7098
.aligned_text "\n"

glabel D_800E709C
.word 0x466A6000

glabel D_800E70A0
.word 0x466A6000

glabel D_800E70A4
.word 0x466A6000
.word 0x00000000
.word 0x00000000

.aligned_text "LOADLEVEL Error: Level out of range\n"
.aligned_text "BossLev problem\n"
.aligned_text "AITABLE Error: Table out of range\n"
.aligned_text "1.1605"
.aligned_text "02/10/97 16:03"
.aligned_text "pmountain"

glabel D_800E7134
.aligned_text "BBB\n"

.aligned_text "CAR"
.aligned_text "HOV"
.aligned_text "PLN"
.aligned_text "Swapping\n"

.word 0x8006CF68
.word 0x8006CF5C
.word 0x8006D024
.word 0x8006CF80
.word 0x8006CF9C
.word 0x8006D024
.word 0x8006D024
.word 0x8006CFB0
.word 0x8006CFC4
.word 0x8006CFD8
.word 0x8006CFEC
.word 0x8006D000
.word 0x8006D014
.word 0x8006D0B8
.word 0x8006D0C4
.word 0x8006D108
.word 0x8006D19C
.word 0x8006D14C
.word 0x8006D17C
.word 0x8006D188
.word 0x8006D1C0
.word 0x8006D1C0
.word 0x8006D1C0
.word 0x8006D1C0
.word 0x8006D164
.word 0x8006D5FC
.word 0x8006D614
.word 0x8006D62C
.word 0x8006D644
.word 0x8006D65C
.word 0x8006D674
.word 0x8006D6D4
.word 0x8006D6F4
.word 0x8006DF70
.word 0x8006E00C
.word 0x8006E054
.word 0x8006E0E0
.word 0x8006DEE8
.word 0x8006E0E0
.word 0x8006E0E0
.word 0x8006E0E0
.word 0x8006E0E0
.word 0x8006E0E0
.word 0x8006E0E0
.word 0x8006E0E0
.word 0x8006E0E0
.word 0x8006DF00
