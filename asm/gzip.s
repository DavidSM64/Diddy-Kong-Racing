/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C68C0 */

.include "globals.inc"
.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

.include "asm/gzip/gzip_inflate_block.s"
.include "asm/gzip/gzip_inflate_dynamic.s"
.include "asm/gzip/gzip_inflate_fixed.s"
.include "asm/gzip/gzip_inflate_stored.s"
.include "asm/gzip/gzip_inflate_codes.s"
