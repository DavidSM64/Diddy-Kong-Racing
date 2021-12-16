/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1E70 */

#include "libultra_internal.h"
#include "viint.h"

void *osViGetCurrentFramebuffer(void) {
    register u32 saveMask;
    void *framep;

    saveMask = __osDisableInt();
    framep = __osViCurr->framep;
    __osRestoreInt(saveMask);
    return framep;
}
