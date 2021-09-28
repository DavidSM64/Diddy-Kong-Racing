/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2240 */

#include "libultra_internal.h"

void osSpTaskYield(void) {
    __osSpSetStatus(SPSTATUS_SET_SIGNAL0);
}
