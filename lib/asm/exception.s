/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2CB0 */

.include "globals.inc"
.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

.include "lib/asm/exception/__osExceptionPreamble.s"
.include "lib/asm/exception/__osException.s"
.include "lib/asm/exception/send_mesg.s"
.include "lib/asm/exception/__osEnqueueAndYield.s"
.include "lib/asm/exception/__osEnqueueThread.s"
.include "lib/asm/exception/__osPopThread.s"
.include "lib/asm/exception/__osDispatchThread.s"
.include "lib/asm/exception/D_800D35A0.s"
