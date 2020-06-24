# common macros

.macro glabel label
    .global \label
    \label:
.endm
