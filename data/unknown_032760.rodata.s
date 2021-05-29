.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E5FA0
.aligned_text "Illegal door no!!!\n"

glabel D_800E5FB4
.aligned_text "Illegal door no!!!\n"

glabel D_800E5FC8
.aligned_text "Illegal door no!!!\n"

.word 0x00000000

glabel D_800E5FE0
.word 0x3FF33333

glabel D_800E5FE4
.word 0x33333333

glabel D_800E5FE8
.word 0x3FB99999

glabel D_800E5FEC
.word 0x9999999A

glabel D_800E5FF0
.word 0x3FECCCCC

glabel D_800E5FF4
.word 0xCCCCCCCD

glabel D_800E5FF8
.word 0x3FF33333

glabel D_800E5FFC
.word 0x33333333

glabel D_800E6000
.word 0x3E4CCCCD

glabel D_800E6004
.word 0x3F1CAC08

glabel D_800E6008
.word 0x3F0D4FDF
.word 0x00000000

glabel D_800E6010
.word 0x3FF33333

glabel D_800E6014
.word 0x33333333

glabel D_800E6018
.word 0x3FEF5C28

glabel D_800E601C
.word 0xF5C28F5C

glabel D_800E6020
.word 0x3FEE6666

glabel D_800E6024
.word 0x66666666

glabel D_800E6028
.word 0x3FF33333

glabel D_800E602C
.word 0x33333333

glabel D_800E6030
.word 0x4072C000

glabel D_800E6034
.word 0x00000000

glabel D_800E6038
.word 0x3FA99999

glabel D_800E603C
.word 0x9999999A

glabel D_800E6040
.word 0x3FA99999

glabel D_800E6044
.word 0x9999999A

glabel D_800E6048
.word 0x3C23D70A
.word 0x00000000

glabel D_800E6050
.word 0x3FF33333

glabel D_800E6054
.word 0x33333333

glabel D_800E6058
.word 0x3FF33333

glabel D_800E605C
.word 0x33333333

glabel D_800E6060
.word 0x3FF33333

glabel D_800E6064
.word 0x33333333

glabel D_800E6068
.word 0x4072C000

glabel D_800E606C
.word 0x00000000
.word 0x80039758
.word 0x80039758
.word 0x80039758
.word 0x80039758
.word 0x80039768
.word 0x80039768
.word 0x80039758
.word 0x80039768
.word 0x80039768
.word 0x80039758
.word 0x80039758
.word 0x80039768
.word 0x80039768
.word 0x80039768
.word 0x80039758
.word 0x80039768
.word 0x80039768
.word 0x80039768
.word 0x80039768
.word 0x80039758
.word 0x80039758
.word 0x800397BC
.word 0x80039978
.word 0x80039AE0
.word 0x80039BB8
.word 0x80039DC4
.word 0x80039ED8
.word 0x80039FDC
.word 0x80039FDC
.word 0x8003A5AC
.word 0x8003A0CC
.word 0x8003A1E8
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A268
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A3FC
.word 0x8003A4F4
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A5AC
.word 0x8003A574
.word 0x00000000

glabel D_800E6140
.word 0x40534000

glabel D_800E6144
.word 0x00000000

glabel D_800E6148
.word 0x3DCCCCCD
.word 0x00000000

glabel D_800E6150
.word 0x3FF19999

glabel D_800E6154
.word 0x9999999A

glabel D_800E6158
.word 0x40019999

glabel D_800E615C
.word 0x9999999A

glabel D_800E6160
.word 0x3FF33333

glabel D_800E6164
.word 0x33333333

glabel D_800E6168
.word 0x3FF33333

glabel D_800E616C
.word 0x33333333

glabel D_800E6170
.word 0x40604000

glabel D_800E6174
.word 0x00000000

glabel D_800E6178
.word 0x3FF33333

glabel D_800E617C
.word 0x33333333

glabel D_800E6180
.word 0x4745C100
.word 0x00000000

glabel D_800E6188
.word 0x3FF33333

glabel D_800E618C
.word 0x33333333

glabel D_800E6190
.word 0x3FF33333

glabel D_800E6194
.word 0x33333333

glabel D_800E6198
.word 0x3FEE6666

glabel D_800E619C
.word 0x66666666

glabel D_800E61A0
.word 0xC61C4000
.word 0x00000000

glabel D_800E61A8
.word 0x3F50624D

glabel D_800E61AC
.word 0xD2F1A9FC

glabel D_800E61B0
.word 0x3A83126F
.word 0x00000000

glabel D_800E61B8
.word 0x3FB99999

glabel D_800E61BC
.word 0x9999999A

.word 0x8003E66C
.word 0x8003E66C
.word 0x8003E67C
.word 0x8003E67C
.word 0x8003E684
.word 0x8003E684
.word 0x8003E684
.word 0x8003E684
.word 0x8003E684
.word 0x8003E684
.word 0x8003E67C
.word 0x8003E67C

glabel D_800E61F0
.word 0x3FF33333

glabel D_800E61F4
.word 0x33333333

glabel D_800E61F8
.word 0x40C38800

glabel D_800E61FC
.word 0x00000000

glabel D_800E6200
.word 0x3FF33333

glabel D_800E6204
.word 0x33333333

glabel D_800E6208
.word 0xC61C4000

glabel D_800E620C
.word 0x3F19999A

glabel D_800E6210
.word 0x3F19999A

glabel D_800E6214
.word 0x3D99999A

glabel D_800E6218
.word 0x3C23D70A

glabel D_800E621C
.word 0x3DCCCCCD

glabel D_800E6220
.word 0x3FCCCCCD

glabel D_800E6224
.word 0x3FCCCCCD
.word 0x80040D30
.word 0x80040E54
.word 0x80040E54
.word 0x800411E4
.word 0x8004153C

glabel D_800E623C
.word 0x46AFC800

glabel D_800E6240
.word 0x3F99999A

glabel D_800E6244
.word 0x3FCCCCCD

glabel D_800E6248
.word 0x3FCCCCCD
.word 0x00000000

glabel D_800E6250
.word 0x3FF33333

glabel D_800E6254
.word 0x33333333
.word 0x80042378
.word 0x800426B8
.word 0x80042898
.word 0x800428E8
.word 0x8004292C

glabel D_800E626C
.word 0x3FAB851F

glabel D_800E6270
.word 0x3D4CCCCD

glabel D_800E6274
.word 0x3E19999A

glabel D_800E6278
.word 0x3E19999A
.word 0x00000000
