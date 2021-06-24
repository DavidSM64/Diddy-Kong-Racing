/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800245F0 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

.include "asm/unknown_0251F0/func_800245F0.s"
.include "asm/unknown_0251F0/calc_dynamic_lighting_for_object_2.s"
