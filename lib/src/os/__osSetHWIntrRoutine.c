/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D47DC */

#include "libultra_internal.h"

extern s32 (*__osHwIntTable[])(void);

void __osSetHWIntrRoutine(OSHWIntr interrupt, s32 (*handler)(void)) {
    register u32 saveMask;
    saveMask = __osDisableInt();
    __osHwIntTable[interrupt] = handler;
    __osRestoreInt(saveMask);
}
