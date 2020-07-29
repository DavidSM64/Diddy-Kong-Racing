/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065F10 */

.include "globals.inc"
.include "macros.inc"

.set noat      # allow manual use of $at
.set noreorder # dont insert nops after branches
.set gp=64     # 64-bit instructions are used

.include "asm/unknown_070110/func_8006F510.s"
.include "asm/unknown_070110/func_8006F53C.s"
.include "asm/unknown_070110/func_8006F564.s"
.include "asm/unknown_070110/func_8006F5E0.s"
.include "asm/unknown_070110/func_8006F64C.s"
.include "asm/unknown_070110/func_8006F6EC.s"
.include "asm/unknown_070110/func_8006F768.s"
.include "asm/unknown_070110/func_8006F870.s"
.include "asm/unknown_070110/rng.s"
.include "asm/unknown_070110/func_8006F9B8.s"
.include "asm/unknown_070110/func_8006FB60.s"
.include "asm/unknown_070110/func_8006FC30.s"
.include "asm/unknown_070110/func_8006FE04.s"
.include "asm/unknown_070110/func_8006FE30.s"
.include "asm/unknown_070110/func_8006FE74.s"
.include "asm/unknown_070110/func_80070130.s"
.include "asm/unknown_070110/func_800701E4.s"
.include "asm/unknown_070110/func_80070320.s"
.include "asm/unknown_070110/func_800703D8.s"
.include "asm/unknown_070110/func_80070490.s"
.include "asm/unknown_070110/func_800704F0.s"
.include "asm/unknown_070110/func_800705F8.s"
.include "asm/unknown_070110/func_80070638.s"
.include "asm/unknown_070110/func_8007066C.s"
.include "asm/unknown_070110/func_80070750.s"
.include "asm/unknown_070110/func_800707C4.s"
.include "asm/unknown_070110/func_800707F8.s"
.include "asm/unknown_070110/func_8007082C.s"
.include "asm/unknown_070110/func_80070890.s"
.include "asm/unknown_070110/func_80070A2C.s"
.include "asm/unknown_070110/func_80070B04.s"
