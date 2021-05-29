.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E94D0
.word 0x05550556
.word 0x0559055A
.word 0x05650566
.word 0x0569056A
.word 0x05950596
.word 0x0599059A
.word 0x05A505A6
.word 0x05A905AA
.word 0x06550656
.word 0x0659065A
.word 0x06650666
.word 0x0669066A
.word 0x06950696
.word 0x0699069A
.word 0x06A506A6
.word 0x06A906AA
.word 0x09550956
.word 0x0959095A
.word 0x09650966
.word 0x0969096A
.word 0x09950996
.word 0x0999099A
.word 0x09A509A6
.word 0x09A909AA
.word 0x0A550A56
.word 0x0A590A5A
.word 0x0A650A66
.word 0x0A690A6A
.word 0x0A950A96
.word 0x0A990A9A
.word 0x0AA50AA6
.word 0x0AA90AAA
