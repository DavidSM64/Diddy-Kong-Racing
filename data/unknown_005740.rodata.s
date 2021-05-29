.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E4BF0
.word 0x461C4000
.word 0x00000000

glabel D_800E4BF8
.word 0x3FD99999

glabel D_800E4BFC
.word 0x9999999A

glabel D_800E4C00
.word 0x461C4000
.word 0x00000000

glabel D_800E4C08
.word 0x3FA99999

glabel D_800E4C0C
.word 0x9999999A

glabel D_800E4C10
.word 0x3FEE6666

glabel D_800E4C14
.word 0x66666666

glabel D_800E4C18
.word 0x3FC0A3D7

glabel D_800E4C1C
.word 0x0A3D70A4

glabel D_800E4C20
.word 0x3FD33333

glabel D_800E4C24
.word 0x33333333

glabel D_800E4C28
.word 0x3F947AE1

glabel D_800E4C2C
.word 0x47AE147B

glabel D_800E4C30
.word 0x3F847AE1

glabel D_800E4C34
.word 0x47AE147B

glabel D_800E4C38
.word 0x3ECCCCCD
.word 0x00000000

glabel D_800E4C40
.word 0x3F747AE1

glabel D_800E4C44
.word 0x47AE147B

glabel D_800E4C48
.word 0xBFB99999

glabel D_800E4C4C
.word 0x9999999A

glabel D_800E4C50
.word 0x3FA99999

glabel D_800E4C54
.word 0x9999999A

glabel D_800E4C58
.word 0x3FEE6666

glabel D_800E4C5C
.word 0x66666666

glabel D_800E4C60
.word 0x3FD33333

glabel D_800E4C64
.word 0x33333333

glabel D_800E4C68
.word 0x401A36AE

glabel D_800E4C6C
.word 0x7D566CF4

glabel D_800E4C70
.word 0x40D1B574

glabel D_800E4C74
.word 0x461C4000

glabel D_800E4C78
.word 0x461C4000
.word 0x00000000

glabel D_800E4C80
.word 0x3FA99999

glabel D_800E4C84
.word 0x9999999A

glabel D_800E4C88
.word 0x3FEE6666

glabel D_800E4C8C
.word 0x66666666

glabel D_800E4C90
.word 0x401A36AE

glabel D_800E4C94
.word 0x7D566CF4

glabel D_800E4C98
.word 0x40D1B574
.word 0x00000000

glabel D_800E4CA0
.word 0x409B0CEF

glabel D_800E4CA4
.word 0xA82E87D3

glabel D_800E4CA8
.word 0x3FE99999

glabel D_800E4CAC
.word 0x9999999A

glabel D_800E4CB0
.word 0x3F4CCCCD
.word 0x00000000

glabel D_800E4CB8
.word 0xBFE99999

glabel D_800E4CBC
.word 0x9999999A

glabel D_800E4CC0
.word 0xBF4CCCCD

glabel D_800E4CC4
.word 0x4A095440

glabel D_800E4CC8
.word 0x3FA99999

glabel D_800E4CCC
.word 0x9999999A

glabel D_800E4CD0
.word 0x44BB8000

glabel D_800E4CD4
.word 0x3D4CCCCD

glabel D_800E4CD8
.word 0x3FA99999

glabel D_800E4CDC
.word 0x9999999A

glabel D_800E4CE0
.word 0x4A095440
.word 0x00000000

glabel D_800E4CE8
.word 0x3FE99999

glabel D_800E4CEC
.word 0x9999999A

glabel D_800E4CF0
.word 0x44BB8000

glabel D_800E4CF4
.word 0x3D4CCCCD

glabel D_800E4CF8
.word 0x3F50624D

glabel D_800E4CFC
.word 0xD2F1A9FC

.aligned_text "OUT OF AUDIO POINTS\n"
.aligned_text "amAudioLineAddVertex: Exceeded maximum number of lines (%d)\n"
.aligned_text "amAudioLineAddVertex: Exceeded maximum number of line vertices (%d)\n"
.aligned_text "amReverbLineAddVertex: Exceeded maximum number of lines (%d)\n"
.aligned_text "amReverbLineAddVertex: Exceeded maximum number of line vertices (%d)\n"
.aligned_text "Audio line definition error (less than 2 vertices on line %d)\n"
.aligned_text "Audio line definition error (line=%d, vertex=%d)\n"
.aligned_text "Reverb line definition error (less than 2 vertices on line %d)\n"
.aligned_text "Reverb line definition error (line=%d, vertex=%d)\n"

glabel D_800E4F10
.word 0xC7C35000

glabel D_800E4F14
.word 0x497423F0

glabel D_800E4F18
.word 0xC0F86A00

glabel D_800E4F1C
.word 0x00000000

glabel D_800E4F20
.word 0xC0F86A00

glabel D_800E4F24
.word 0x00000000
.word 0x00000000
.word 0x00000000

.aligned_text "Exceeded voice limit of %d (%d)\n"

.word 0x00000000
.word 0x00000000
.word 0x00000000
