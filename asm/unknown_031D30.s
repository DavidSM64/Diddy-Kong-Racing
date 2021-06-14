/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80031130 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

.section .text

.include "asm/unknown_031D30/func_80031130.s"
.include "asm/unknown_031D30/func_800314DC.s"
.include "asm/unknown_031D30/func_80031600.s"

.section .rodata

glabel D_800E5F60
.float -0.1

glabel D_800E5F64
.float -0.1

glabel D_800E5F68
.float 0.707

glabel D_800E5F6C
.float 0.45

glabel D_800E5F70
.float -0.1



