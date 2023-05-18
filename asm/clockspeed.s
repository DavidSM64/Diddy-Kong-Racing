/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065D40 */

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64

.include "macros.inc"


.section .text, "ax"

# Returns 0 if the ROM is being played on console.
# Returns 1 if the ROM is being played on emulator with good settings.
# Returns 2 or higher if the ROM is being played on emulator with bad settings.
.global get_clockspeed
.balign 32
get_clockspeed:
    mfc0 $v1, $9
    nop
    mfc0 $v0, $9
    nop
    subu $v0, $v0, $v1
    jr $ra
    srl $v0, $v0, 1
	
.global get_cachemiss
.balign 32
get_cachemiss:
	nop
	nop
    mfc0 $v1, $9
    nop
    mfc0 $v0, $9
    nop
    subu $v0, $v0, $v1
    jr $ra
    srl $v0, $v0, 1
