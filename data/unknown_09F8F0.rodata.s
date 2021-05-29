.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E8640
.aligned_text "CAN'T"

glabel D_800E8648
.aligned_text "SAVE"

glabel D_800E8650
.aligned_text "GHOST"

glabel D_800E8658
.aligned_text " CONTROLLER"

glabel D_800E8664
.aligned_text "PAK"

glabel D_800E8668
.aligned_text "FULL"

glabel D_800E8670
.aligned_text " CONTROLLER"

glabel D_800E867C
.aligned_text "PAK"

glabel D_800E8680
.aligned_text "DAMAGED"

glabel D_800E8688
.aligned_text "RACE"

glabel D_800E8690
.aligned_text "LAP"

glabel D_800E8694
.aligned_text "DID NOT FINISH"

.word 0x00000000

glabel D_800E86A8
.word 0x3FE33333

glabel D_800E86AC
.word 0x33333333
.word 0x3FF33333
.word 0x33333333

glabel D_800E86B8
.word 0x43838000

glabel D_800E86BC
.word 0x43818000

glabel D_800E86C0
.word 0x43848000
.word 0x00000000
.word 0x3FF33333
.word 0x33333333
.word 0x3FE33333
.word 0x33333333
.word 0x3FF33333
.word 0x33333333
.word 0x3FE33333
.word 0x33333333

glabel D_800E86E8
.word 0x3FF33333

glabel D_800E86EC
.word 0x33333333

glabel D_800E86F0
.word 0x3FE33333

glabel D_800E86F4
.word 0x33333333

glabel D_800E86F8
.word 0x800A0F28
.word 0x800A0F38
.word 0x800A0F48
.word 0x800A0F58
.word 0x800A0F6C
.word 0x800A0F80
.word 0x800A0F94
.word 0x800A0FAC

glabel D_800E8718
.word 0x43898000
.word 0x00000000

glabel D_800E8720
.word 0x40508000

glabel D_800E8724
.word 0x00000000

glabel D_800E8728
.word 0x40508000

glabel D_800E872C
.word 0x00000000

glabel D_800E8730
.word 0x40508000

glabel D_800E8734
.word 0x00000000

glabel D_800E8738
.word 0x3FF33333

glabel D_800E873C
.word 0x33333333

glabel D_800E8740
.word 0x46C92000

glabel D_800E8744
.word 0x800A63D8
.word 0x800A691C
.word 0x800A6BCC
.word 0x800A6CA4
.word 0x800A6D68

glabel D_800E8758
.word 0x3FF19999

glabel D_800E875C
.word 0x9999999A

glabel D_800E8760
.word 0x3FF19999

glabel D_800E8764
.word 0x9999999A

glabel D_800E8768
.word 0x800A6E70
.word 0x800A6F3C
.word 0x800A7014
.word 0x800A70D4
.word 0x800A7158
.word 0x00000000

glabel D_800E8780
.word 0x3FA7FF58

glabel D_800E8784
.word 0x3A53B8E5

glabel D_800E8788
.word 0x40855544

glabel D_800E878C
.word 0x32CA57A8

glabel D_800E8790
.word 0x3FC70A3D

glabel D_800E8794
.word 0x70A3D70A

glabel D_800E8798
.word 0x3FA7FF58

glabel D_800E879C
.word 0x3A53B8E5

glabel D_800E87A0
.word 0x3FF19999

glabel D_800E87A4
.word 0x9999999A

glabel D_800E87A8
.word 0x43358000
.word 0x00000000
.word 0x40508000
.word 0x00000000

glabel D_800E87B8
.word 0x40508000

glabel D_800E87BC
.word 0x00000000

glabel D_800E87C0
.word 0x3FF19999

glabel D_800E87C4
.word 0x9999999A

glabel D_800E87C8
.word 0x3FF33333

glabel D_800E87CC
.word 0x33333333

glabel D_800E87D0
.word 0x3F4CCCCD

glabel D_800E87D4
.word 0x3F99999A

glabel D_800E87D8
.word 0x3F8CCCCD
.word 0x00000000

glabel D_800E87E0
.word 0x3FF19999

glabel D_800E87E4
.word 0x9999999A
.word 0x00000000
.word 0x00000000
