/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1EB0 */

#include "libultra_internal.h"
#include "viint.h"

void *osViGetNextFramebuffer(void) {
    register u32 saveMask;
    void *framep;

    saveMask = __osDisableInt();
    framep = __osViNext->framep;
    __osRestoreInt(saveMask);
    return framep;
}
