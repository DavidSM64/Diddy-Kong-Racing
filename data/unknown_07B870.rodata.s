.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.aligned_text "Error: Texture no %x out of range on load. !!\n"
.aligned_text "TEX Error: Palette memory overflow!!\n"
.aligned_text "TEX Error: TexTab overflow!!\n"
.aligned_text "texFreeTexture: NULL tex!!\n"
.aligned_text "TEX Error: Tryed to deallocate non-existent texture!!\n"
.aligned_text "SRPBUF overflow!!\n"
.aligned_text "Error: Sprite table overflow!!\n"
.aligned_text "texFreeSprite: NULL sprite!!\n"
.aligned_text "TEXSPR Error: Tryed to deallocate non-existent sprite!!\n"

.word 0x00000000
