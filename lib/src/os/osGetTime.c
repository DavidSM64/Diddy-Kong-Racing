/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D21B0 */

#include "libultra_internal.h"

extern OSTime __osCurrentTime;
extern u32 __osBaseCounter;

OSTime osGetTime() {
    u32 tmptime;
    u32 elapseCount;
    OSTime currentCount;
    register u32 saveMask;
    saveMask = __osDisableInt();
    tmptime = osGetCount();
    elapseCount = tmptime - __osBaseCounter;
    currentCount = __osCurrentTime;
    __osRestoreInt(saveMask);
    return currentCount + elapseCount;
}
