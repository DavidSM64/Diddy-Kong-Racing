.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.aligned_text "Region = %d	 loc = %x	 size = %x\t"
.aligned_text "FREE"
.aligned_text "ALLOCATED"
.aligned_text "ALLOCATED,FIXED"
.aligned_text "\n"
.aligned_text "\n"
.aligned_text "Region number = %d\t"
.aligned_text "maxSlots = %d\t"
.aligned_text "slotsUsed = %d\t"
.aligned_text "loc = %x\t"
.aligned_text "size = %x\n"
.aligned_text "\n"

glabel D_800E7630
.aligned_text "DKRACING-ADV"

glabel D_800E7640
.aligned_text "DKRACING-ADV"

glabel D_800E7650
.aligned_text "DKRACING-TIMES"
.aligned_text "DKRACING-TIMES"

glabel D_800E7670
.aligned_text "DKRACING-ADV"

glabel D_800E7680
.aligned_text "DKRACING-ADV"

glabel D_800E7690
.aligned_text "DKRACING-TIMES"

glabel D_800E76A0
.aligned_text "DKRACING-TIMES"

.aligned_text "WARNING : No Eprom\n"
.aligned_text "WARNING : No Eprom\n"
.aligned_text "WARNING : No Eprom\n"
.aligned_text "WARNING : No Eprom\n"
.aligned_text "WARNING : No Eprom\n"
.aligned_text "WARNING : No Eprom\n"
.aligned_text "WARNING : No Eprom\n"

glabel D_800E773C
.aligned_text "DKRACING-GHOSTS"

glabel D_800E774C
.word 0x00000000

.aligned_text "warning: corrupt ghost\n"

glabel D_800E7768
.aligned_text "DKRACING-GHOSTS"

glabel D_800E7778
.word 0x00000000

glabel D_800E777C
.aligned_text "DKRACING-GHOSTS"

glabel D_800E778C
.word 0x00000000

glabel D_800E7790
.aligned_text "DKRACING-GHOSTS"

glabel D_800E77A0
.word 0x00000000

glabel D_800E77A4
.aligned_text "DKRACING-GHOSTS"

glabel D_800E77B4
.word 0x00000000

glabel D_800E77B8
.aligned_text "DKRACING-GHOSTS"

glabel D_800E77C8
.word 0x00000000

glabel D_800E77CC
.aligned_text "DKRACING-GHOSTS"

glabel D_800E77DC
.word 0x00000000

glabel D_800E77E0
.word 0x3FB99999

glabel D_800E77E4
.word 0x9999999A

glabel D_800E77E8
.word 0x400CCCCC

glabel D_800E77EC
.word 0xCCCCCCCD

glabel D_800E77F0
.word 0x407EA000

glabel D_800E77F4
.word 0x00000000
.word 0x00000000
.word 0x00000000
