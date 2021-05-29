.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.aligned_text "\nCouldn't find a block to pick wave details from.\nUsing block 0 as default."
.aligned_text "\n\nBlock may be specified using 'P' on water group node."
.aligned_text "\nError :: can not remove a wave swell object which doesn't exist !"
.aligned_text "\nError :: more than eight swells overlap on column %d."
.aligned_text "\nError :: can not add another wave swell, reached limit of %d."

glabel D_800E92A0
.word 0x461C4000

glabel D_800E92A4
.word 0xC61C4000

glabel D_800E92A8
.word 0x40D47AE1

glabel D_800E92AC
.word 0x47AE147B

glabel D_800E92B0
.word 0x40D11111

glabel D_800E92B4
.word 0x47AE147B

glabel D_800E92B8
.word 0x40D47AE1

glabel D_800E92BC
.word 0x47AE147B

glabel D_800E92C0
.word 0x40D11111

glabel D_800E92C4
.word 0x47AE147B
.word 0x00000000
.word 0x00000000

glabel D_800E92D0
.word 0x800C0310
.word 0x800C0320
.word 0x800C0370
.word 0x800C03C0
.word 0x800C03D0
.word 0x800C0420
.word 0x800C0470

glabel D_800E92EC
.word 0x800C056C
.word 0x800C0580
.word 0x800C0580
.word 0x800C0594
.word 0x800C0580
.word 0x800C0580
.word 0x800C05A8

glabel D_800E9308
.word 0x3FB33333

glabel D_800E930C
.word 0x3F99999A

glabel D_800E9310
.word 0x800C0680
.word 0x800C0694
.word 0x800C06A8
.word 0x800C06BC
.word 0x800C06D0
.word 0x800C06E4
.word 0x800C06F8

glabel D_800E932C
.word 0x3F99999A

glabel D_800E9330
.word 0x800C3958
.word 0x800C3984
.word 0x800C3A30
.word 0x800C3AA8
.word 0x800C3ADC
.word 0x800C3B00
.word 0x800C3B2C
.word 0x800C3B50
.word 0x800C3B88
.word 0x800C3BA0
.word 0x00000000
.word 0x00000000

glabel D_800E9360
.word 0x800C4A88
.word 0x800C4A78
.word 0x800C4AD0
.word 0x800C4AE8
.word 0x800C4ADC
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4AE8
.word 0x800C4A6C
