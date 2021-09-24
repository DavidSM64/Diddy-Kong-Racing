/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2240 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

void osSpTaskYield(void) {
    __osSpSetStatus(SPSTATUS_SET_SIGNAL0);
}

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D2E40/osViSetSpecialFeatures.s")
