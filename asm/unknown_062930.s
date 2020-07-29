/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80061D30 */

.include "globals.inc"
.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

.include "asm/unknown_062930/func_80061D30.s"
