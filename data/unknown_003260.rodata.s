.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.aligned_text "audio manager: RCP audio interface bug caused DMA from bad address - move audiomgr.c in the makelist!\n"
.aligned_text "audio: ai out of samples\n"
.aligned_text "OH DEAR - No audio DMA buffers left\n"
.aligned_text "Dma not done\n"

.word 0x00000000

.aligned_text "Bad soundState: voices =%d, states free =%d, states busy =%d, type %d data %x\n"
.aligned_text "playing a playing sound\n"
.aligned_text "Nonsense sndp event\n"
.aligned_text "Sound state allocate failed - sndId %d\n"
.aligned_text "Don't worry - game should cope OK\n"
.aligned_text "WARNING: Attempt to stop NULL sound aborted\n"

.word 0x800035C4
.word 0x80003A0C
.word 0x80004090
.word 0x80003B2C
.word 0x80004090
.word 0x80004090
.word 0x80004090
.word 0x80003C8C
.word 0x80004090
.word 0x80004090
.word 0x80004090
.word 0x80004090
.word 0x80004090
.word 0x80004090
.word 0x80004090
.word 0x80003BA4
