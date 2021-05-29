.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

# I am not sure if this is in the correct file. It is hard to tell without any glabels.

.aligned_text "Error: Model no. out of range on load. !!\n"
.aligned_text "TEXTURE ERROR!!\n%d,%d\n"
.aligned_text "Error: Model table overflow!!\n"
.aligned_text "WARNING :: createModelInstance called with NULL pointer\n"
.aligned_text "ModFreeModel : NULL mod_inst!!\n"
.aligned_text "MOD Error: Tryed to deallocate non-existent model!!\n"

.word 0x00000000
.word 0x00000000
