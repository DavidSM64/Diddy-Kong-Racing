/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1DF0 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

extern OSTime __osCurrentTime;//__osCurrentTime
extern u32 __osBaseCounter; //__osBaseCounter

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/func_800D1DF0.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/osViGetCurrentFramebuffer.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/osViGetNextFramebuffer.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/_VirtualToPhysicalTask.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/osSpTaskLoad.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/osSpTaskStartGo.s")

OSTime osGetTime()
{
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
