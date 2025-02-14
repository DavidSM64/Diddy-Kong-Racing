/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B7D10 */

.section .text

.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

glabel stack_pointer
jr    $ra
 move  $v0, $sp
 