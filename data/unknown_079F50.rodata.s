.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.aligned_text "(Audio task)"
.aligned_text "(Game task)"
.aligned_text "(DI task)\n"
.aligned_text "(DI benchmark test)\n"
.aligned_text "(Unknown task type %d)\n"
.aligned_text "\nRCP TASK INFO\n"
.aligned_text "-------------\n"
.aligned_text "\ttype\t\t= %u\n"
.aligned_text "\tflags\t\t= %u\n"
.aligned_text "\tucode_boot\t\t= %p\n"
.aligned_text "\tucode_boot_size\t\t= %u\n"
.aligned_text "\tucode\t\t= %p\n"
.aligned_text "\tucode_size\t\t= %u\n"
.aligned_text "\tucode_data\t\t= %p\n"
.aligned_text "\tucode_data_size\t\t= %u\n"
.aligned_text "\toutput_buff\t\t= %p\n"
.aligned_text "\toutput_buff_size\t\t= %u\n"
.aligned_text "\tdata_ptr\t\t= %p\n"
.aligned_text "\tdata_size\t\t= %u\n"

glabel D_800E796C
.word 0x48E4E1C0

glabel D_800E7970
.word 0x8007A2A4
.word 0x8007A248
.word 0x8007A1BC
.word 0x8007A2A4
.word 0x8007A2A4
.word 0x8007A248
.word 0x8007A248
.word 0x00000000
