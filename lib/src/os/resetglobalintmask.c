/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D6500 */

#include "PR/os_internal.h"

extern OSIntMask __OSGlobalIntMask;	/* global interrupt mask */

void __osResetGlobalIntMask(OSHWIntr mask) {
    register u32 saveMask = __osDisableInt();

    __OSGlobalIntMask &= ~(mask & ~OS_IM_RCP);

    __osRestoreInt(saveMask);
}
