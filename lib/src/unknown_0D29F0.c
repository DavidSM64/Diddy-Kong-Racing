/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1DF0 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

typedef struct
{
    /* 0x0 */ f32 factor;
    /* 0x4 */ u16 offset;
    /* 0x8 */ u32 scale;
} __OSViScale;

typedef struct
{
    /* 0x0 */ u16 state;
    /* 0x2 */ u16 retraceCount;
    /* 0x4 */ void *framep;
    /* 0x8 */ OSViMode *modep;
    /* 0xC */ u32 control;
    /* 0x10 */ OSMesgQueue *msgq;
    /* 0x14 */ OSMesg msg;
    /* 0x18 */ __OSViScale x;
    /* 0x24 */ __OSViScale y;
} __OSViContext;

extern OSTime __osCurrentTime;//__osCurrentTime
extern u32 __osBaseCounter; //__osBaseCounter
extern __OSViContext *__osViCurr;
extern __OSViContext *__osViNext;

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/func_800D1DF0.s")

void *osViGetCurrentFramebuffer(void){
    register u32 saveMask;
    void *framep;

    saveMask = __osDisableInt();
    framep = __osViCurr->framep;
    __osRestoreInt(saveMask);
    return framep;
}

void *osViGetNextFramebuffer(void){
    register u32 saveMask;
    void *framep;

    saveMask = __osDisableInt();
    framep = __osViNext->framep;
    __osRestoreInt(saveMask);
    return framep;
}

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
