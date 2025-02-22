/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2240 */

#include "PR/os_internal.h"
#include "PR/rcp.h"

void osSpTaskYield(void) {
    __osSpSetStatus(SP_SET_YIELD);
}
