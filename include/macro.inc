# common macros

# Assembly Macros

.set K0BASE, 0x80000000
.set K1BASE, 0xA0000000
.set K2BASE, 0xC0000000

.macro glabel label
    .global \label
    .type \label, @function
    \label:
.endm

.macro dlabel label
    .global \label
    .type \label, @object
    \label:
.endm

.macro jlabel label
    .global \label
    \label:
.endm

.macro .word32 x
    .word \x
.endm

.macro BANK_INDEX bank, index
	.half \bank
	.half \index
.endm

.macro move a, b
    addu \a, \b, $zero
.endm

.macro leaf label
    .global \label
    .type \label, @function
    \label:
    .ent    \label
.endm

# Used for alternative entries for Sin functions
.macro altleaf label
    .global \label
    .type \label, @function
    \label:
    .aent    \label
.endm
