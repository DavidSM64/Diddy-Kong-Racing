#include "PR/os_internal.h"
#include <ultra64.h>

// A stack frame was added to hardware interrupt handlers in 2.0J
#if BUILD_VERSION >= VERSION_J

struct __osHwInt {
    s32 (*handler)(void);
    void* stackEnd;
};

extern struct __osHwInt __osHwIntTable[];

void __osSetHWIntrRoutine(OSHWIntr interrupt, s32 (*handler)(void), void* stackEnd) {
    register u32 saveMask = __osDisableInt();

    __osHwIntTable[interrupt].handler = handler;
    __osHwIntTable[interrupt].stackEnd = stackEnd;
    __osRestoreInt(saveMask);
}

#else

extern struct s32 (*__osHwIntTable[])(void);

void __osSetHWIntrRoutine(OSHWIntr interrupt, s32 (*handler)(void)) {
    register u32 saveMask = __osDisableInt();

    __osHwIntTable[interrupt] = handler;
    __osRestoreInt(saveMask);
}

#endif
