/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C9AF0 */

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

/* Hacky workaround. This is required because after alSynSetPriority, the linker seems to have added a bunch of nops. */
glabel __NOPS_NEEDED
/* 0CA6F0 800C9AF0 00000000 */  nop
/* 0CA6F4 800C9AF4 00000000 */  nop
/* 0CA6F8 800C9AF8 00000000 */  nop
/* 0CA6FC 800C9AFC 00000000 */  nop
/* 0CA700 800C9B00 00000000 */  nop
/* 0CA704 800C9B04 00000000 */  nop
/* 0CA708 800C9B08 00000000 */  nop
/* 0CA70C 800C9B0C 00000000 */  nop
/* 0CA710 800C9B10 00000000 */  nop
/* 0CA714 800C9B14 00000000 */  nop
/* 0CA718 800C9B18 00000000 */  nop
/* 0CA71C 800C9B1C 00000000 */  nop
/* 0CA720 800C9B20 00000000 */  nop
/* 0CA724 800C9B24 00000000 */  nop
/* 0CA728 800C9B28 00000000 */  nop
/* 0CA72C 800C9B2C 00000000 */  nop
