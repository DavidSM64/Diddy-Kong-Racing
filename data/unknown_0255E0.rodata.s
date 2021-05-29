.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

glabel D_800E5DF0
.aligned_text "TT CAM"

.aligned_text "Solid Clipping x0=x1 Error!!!\n"
.aligned_text "TrackGetHeight() - Overflow!!!\n"

glabel D_800E5E38
.aligned_text "ERROR!! TrackMem overflow .. %d\n"

.word 0x00000000

glabel D_800E5E60
.word 0x406F4000

glabel D_800E5E64
.word 0x00000000

glabel D_800E5E68
.word 0xC072C000

glabel D_800E5E6C
.word 0x00000000

glabel D_800E5E70
.word 0x4072C000

glabel D_800E5E74
.word 0x00000000

glabel D_800E5E78
.word 0x4072C000

glabel D_800E5E7C
.word 0x00000000

glabel D_800E5E80
.word 0xC072C000

glabel D_800E5E84
.word 0x00000000

glabel D_800E5E88
.word 0xC072C000

glabel D_800E5E8C
.word 0x00000000

glabel D_800E5E90
.word 0xBFB99999

glabel D_800E5E94
.word 0x9999999A

glabel D_800E5E98
.word 0xBFB99999

glabel D_800E5E9C
.word 0x9999999A

glabel D_800E5EA0
.word 0x408F4000

glabel D_800E5EA4
.word 0x00000000

glabel D_800E5EA8
.word 0x408F4000

glabel D_800E5EAC
.word 0x00000000

glabel D_800E5EB0
.word 0x3FE99999

glabel D_800E5EB4
.word 0x9999999A

glabel D_800E5EB8
.word 0x406FE000

glabel D_800E5EBC
.word 0x00000000

glabel D_800E5EC0
.word 0x8002AB40
.word 0x8002AB40
.word 0x8002AB54
.word 0x8002AB40
.word 0x8002AB40
.word 0x8002AB54
.word 0x8002AB40
.word 0x8002AB54
.word 0x8002AB2C
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB58
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB40
.word 0x8002AB54
.word 0x8002AB40
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB58
.word 0x8002AB54
.word 0x8002AB54
.word 0x8002AB58
.word 0x8002AB40

glabel D_800E5F40
.word 0x3FC99999

glabel D_800E5F44
.word 0x9999999A

glabel D_800E5F48
.word 0x3FB33333

glabel D_800E5F4C
.word 0x3F36C8B4

glabel D_800E5F50
.word 0x3BA3D70A

glabel D_800E5F54
.word 0x3FB50481

glabel D_800E5F58
.word 0x3BA3D70A

glabel D_800E5F5C
.word 0x3F7D70A4
