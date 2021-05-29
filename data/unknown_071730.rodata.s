.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.aligned_text "*** mmAlloc: size = 0 ***\n"
.aligned_text "*** mm Error *** ---> No more slots available.\n"
.aligned_text "\n*** mm Error *** ---> No suitble block found for allocation.\n"
.aligned_text "*** mmAllocAtAddr: size = 0 ***\n"
.aligned_text "\n*** mm Error *** ---> No more slots available.\n"
.aligned_text "\n*** mm Error *** ---> Can't allocate memory at desired address.\n"
.aligned_text "\n*** mm Error *** ---> Can't free ram at this location: %x\n"
.aligned_text "\n*** mm Error *** ---> No match found for mmFree.\n"
.aligned_text "*** Slots still in use in region ***\n"
.aligned_text "\n*** mm Error *** ---> stbf stack too deep!\n"
.aligned_text "\n*** mm Error *** ---> Can't fix the specified block.\n"
.aligned_text "\n*** mm Error *** ---> Can't unfix the specified block.\n"
.aligned_text "Colour %x >> %d\n"
.aligned_text "Unable to record %d slots, colours overflowed table.\n"
.aligned_text "RED %d\n"
.aligned_text "GREEN %d\n"
.aligned_text "BLUE %d\n"
.aligned_text "YELLOW %d\n"
.aligned_text "MAGENTA %d\n"
.aligned_text "CYAN %d\n"
.aligned_text "WHITE %d\n"
.aligned_text "GREY %d\n"
.aligned_text "ORANGE %d\n\n"

glabel D_800E7528
.aligned_text "RED %d\n"
glabel D_800E7530
.aligned_text "GREEN %d\n"
glabel D_800E753C
.aligned_text "BLUE %d\n"
glabel D_800E7548
.aligned_text "YELLOW %d\n"
glabel D_800E7554
.aligned_text "MAGENTA %d\n"
glabel D_800E7560
.aligned_text "CYAN %d\n"
glabel D_800E756C
.aligned_text "WHITE %d\n"
glabel D_800E7578
.aligned_text "GREY %d\n"
glabel D_800E7584
.aligned_text "ORANGE %d\n\n"
