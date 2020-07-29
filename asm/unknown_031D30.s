/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80031130 */

.include "globals.inc"
.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

.include "asm/unknown_031D30/func_80031130.s"
.include "asm/unknown_031D30/func_800314DC.s"
.include "asm/unknown_031D30/func_80031600.s"
