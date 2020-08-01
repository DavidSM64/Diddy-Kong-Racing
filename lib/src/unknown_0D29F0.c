/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1DF0 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

extern OSTime D_8012D220;//__osCurrentTime
extern u32 D_8012D228; //__osBaseCounter

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/func_800D1DF0.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/func_800D1E70.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/func_800D1EB0.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/_VirtualToPhysicalTask.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/osSpTaskLoad.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/osSpTaskStartGo.s")
//GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/osGetTime.s")

OSTime osGetTime()
{
    u32 tmptime;
    u32 elapseCount;
    OSTime currentCount;
    register u32 saveMask;
    saveMask = __osDisableInt();
    tmptime = osGetCount();
    elapseCount = tmptime - D_8012D228;
    currentCount = D_8012D220;
    __osRestoreInt(saveMask);
    return currentCount + elapseCount;
}
