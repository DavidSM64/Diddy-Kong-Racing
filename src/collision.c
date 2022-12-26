/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80031130 */

#include "collision.h"

#include "types.h"
#include "macros.h"

/*******************************/

// All handwritten assembly, below.

// Collision for a different segment
GLOBAL_ASM("asm/collision/func_80031130.s")
// Might be segment related.
GLOBAL_ASM("asm/collision/func_800314DC.s")
// Player collision for the current segment
GLOBAL_ASM("asm/collision/func_80031600.s")
