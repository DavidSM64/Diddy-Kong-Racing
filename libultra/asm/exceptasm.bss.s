/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8012D240 */

.include "macro.inc"

/* assembler directives */
.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */
.set gp=64     /* allow use of 64-bit general purpose registers */

.section .bss

glabel __osThreadSave
.space 0x1B0