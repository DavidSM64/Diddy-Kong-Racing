/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1D80 */

#include "libultra_internal.h"
#include "viint.h"

void osViSetEvent(OSMesgQueue *mq, OSMesg m, u32 retraceCount) {
    register u32 saveMask;
    saveMask = __osDisableInt();
    __osViNext->msgq = mq;
    __osViNext->msg = m;
    __osViNext->retraceCount = retraceCount;
    __osRestoreInt(saveMask);
}
