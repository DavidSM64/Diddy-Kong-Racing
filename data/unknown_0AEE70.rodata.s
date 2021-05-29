.include "macros.inc"

.macro .aligned_text ascii
    .asciz "\ascii"
    .balign 4
.endm

.section .rodata

.aligned_text "\nMaximum limit of %d lens flare switches, per level, has been exceeded."

.word 0x00000000
.word 0x00000000

.aligned_text "\n\nUnknown trigger type in initParticleTrigger %d, Max %d.\n\n"
.aligned_text "\n\nUnknown particle type in initParticleTrigger %d, Max %d.\n\n"
.aligned_text "\n\nUnknown trigger type in initParticleTrigger %d, Max %d.\n\n"
.aligned_text "Sprite Particle buffer is full.\n"
.aligned_text "Triangle Particle buffer is full.\n"
.aligned_text "Rectangle Particle buffer is full.\n"
.aligned_text "Line Particle buffer is full.\n"
.aligned_text "Point Particle buffer is full.\n"
.aligned_text "\n\nCan't allocate space for unknown particle type."
.aligned_text "\n\nParticle has been freed twice, this is Super Safe, Honest!\n"
.aligned_text "\n\nSprite Particle Buffer is empty.\n\n"
.aligned_text "\n\nTriangle Particle Buffer is empty.\n\n"
.aligned_text "\n\nRectangle Particle Buffer is empty.\n\n"
.aligned_text "\n\nLine Particle buffer is empty.\n\n"
.aligned_text "\n\nPoint Particle buffer is empty.\n\n"
.aligned_text "\n\nCan't deallocate space for unknown particle type.\n\n"
.aligned_text "\nError :: trigger %x has no reference to point %x"
.aligned_text "\nError :: particle %x is not indexed correctly in trigger list %x (%d >> %p)"

.word 0x00000000

glabel D_800E8B98
.word 0x3EEFFFFF

glabel D_800E8B9C
.word 0xFFE97B64

glabel D_800E8BA0
.word 0x3EEFFFFF

glabel D_800E8BA4
.word 0xFFE97B64

glabel D_800E8BA8
.word 0x3EEFFFFF

glabel D_800E8BAC
.word 0xFFE97B64

glabel D_800E8BB0
.word 0x3EEFFFFF

glabel D_800E8BB4
.word 0xFFE97B64

glabel D_800E8BB8
.word 0x3EEFFFFF

glabel D_800E8BBC
.word 0xFFE97B64

glabel D_800E8BC0
.word 0x3EEFFFFF

glabel D_800E8BC4
.word 0xFFE97B64

glabel D_800E8BC8
.word 0x3EEFFFFF

glabel D_800E8BCC
.word 0xFFE97B64

glabel D_800E8BD0
.word 0x3EEFFFFF

glabel D_800E8BD4
.word 0xFFE97B64

glabel D_800E8BD8
.word 0x3DCCCCCD

.word 0x800B2250
.word 0x800B20E0
.word 0x800B2138
.word 0x800B2190
.word 0x800B21E8

glabel D_800E8BF0
.word 0x3DCCCCCD

glabel D_800E8BF4
.word 0x3C23D70A
.word 0x00000000
.word 0x00000000

glabel D_800E8C00
.aligned_text "0123456789abcdefghijklmnopqrstuvwxyz"

glabel D_800E8C28
.aligned_text "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

glabel D_800E8C50
.word 0x00000000

glabel D_800E8C54
.aligned_text "(null)"

glabel D_800E8C5C
.aligned_text "(nil)"

.aligned_text "*** diPrintf Error *** ---> Out of string space. (Print less text!)\n"

.word 0x800B4BA4
.word 0x800B4BC8
.word 0x800B4BC8
.word 0x800B4BBC
.word 0x800B4BC8
.word 0x800B4BC8
.word 0x800B4BC8
.word 0x800B4BC8
.word 0x800B4BC8
.word 0x800B4BC8
.word 0x800B4BC8
.word 0x800B4BAC
.word 0x800B4BC8
.word 0x800B4BB4
.word 0x800B4BC8
.word 0x800B4BC8
.word 0x800B4BC4
.word 0x800B4DB0
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DB8
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4D90
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4D98
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC4
.word 0x800B4DC0
.word 0x800B52C4
.word 0x800B5E0C
.word 0x800B5794
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B4F84
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5AC4
.word 0x800B4E38
.word 0x800B52C4
.word 0x800B57A4
.word 0x800B5794
.word 0x800B5E0C
.word 0x800B4E38
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5D78
.word 0x800B4F64
.word 0x800B5C8C
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B5B48
.word 0x800B5E0C
.word 0x800B4F44
.word 0x800B5E0C
.word 0x800B5E0C
.word 0x800B4FA4
.word 0x800B6658
.word 0x800B6740
.word 0x800B6614
.word 0x800B6634
.word 0x800B66CC

.word 0x00000000

.aligned_text "\nAssertion failed: '%s' in file %s, line %d\n"
.aligned_text "\nAssertion failed: '%s' in file %s, line %d\n"
.aligned_text ">fault< "

glabel D_800E8EDC
.aligned_text "CORE"

glabel D_800E8EE4
.word 0x00000000

glabel D_800E8EE8
.aligned_text "CORE"

glabel D_800E8EF0
.word 0x00000000

glabel D_800E8EF4
.aligned_text "CORE"

glabel D_800E8EFC
.word 0x00000000

.aligned_text "setup"
.aligned_text "control"
.aligned_text "print"

# EPC (Error program counter?) Lockup display strings, see: https://tcrf.net/Diddy_Kong_Racing#Crash_Debugger
glabel D_800E8F18
.aligned_text " epc\t\t0x%08x\n"

glabel D_800E8F28
.aligned_text " cause\t\tmmAlloc(%d,0x%8x)\n"

glabel D_800E8F44
.aligned_text " object\t\t"

glabel D_800E8F50
.aligned_text "%s %d "

glabel D_800E8F58
.aligned_text "\n"

glabel D_800E8F5C
.aligned_text "\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

glabel D_800E8F6C
.aligned_text " Fault in thread %d\n"

glabel D_800E8F84
.aligned_text " epc\t\t0x%08x\n"

glabel D_800E8F94
.aligned_text " cause\t\t0x%08x\n"

glabel D_800E8FA4
.aligned_text " sr\t\t0x%08x\n"

glabel D_800E8FB4
.aligned_text " badvaddr\t0x%08x\n"

glabel D_800E8FC8
.aligned_text " object\t\t"

glabel D_800E8FD4
.aligned_text "%s %d "

glabel D_800E8FDC
.aligned_text "\n"

glabel D_800E8FE0
.aligned_text " at 0x%08x v0 0x%08x v1 0x%08x\n"

glabel D_800E9000
.aligned_text " a0 0x%08x a1 0x%08x a2 0x%08x\n"

glabel D_800E9020
.aligned_text " a3 0x%08x t0 0x%08x t1 0x%08x\n"

glabel D_800E9040
.aligned_text " t2 0x%08x t3 0x%08x t4 0x%08x\n"

glabel D_800E9060
.aligned_text " t5 0x%08x t6 0x%08x t7 0x%08x\n"

glabel D_800E9080
.aligned_text " s0 0x%08x s1 0x%08x s2 0x%08x\n"

glabel D_800E90A0
.aligned_text " s3 0x%08x s4 0x%08x s5 0x%08x\n"

glabel D_800E90C0
.aligned_text " s6 0x%08x s7 0x%08x t8 0x%08x\n"

glabel D_800E90E0
.aligned_text " t9 0x%08x gp 0x%08x sp 0x%08x\n"

glabel D_800E9100
.aligned_text " s8 0x%08x ra 0x%08x\n\n"
glabel D_800E9118
.aligned_text "   %08x %08x %08x\n"

glabel D_800E912C
.aligned_text "  "

glabel D_800E9130
.aligned_text "%04x "

glabel D_800E9138
.aligned_text "\n"

### End of EPC lockup strings ###

.word 0x800B7898
.word 0x800B7C18
.word 0x800B7C18
.word 0x800B7C18
.word 0x800B7C70
.word 0x800B7CE4

.word 0x00000000
.word 0x00000000
.word 0x00000000
