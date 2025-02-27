/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C9AF0 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

/* params.s - All libultra games have this padding */
.space 0x40
