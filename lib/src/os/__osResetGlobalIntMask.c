/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D6500 */

#include "libultra_internal.h"

extern u32 __OSGlobalIntMask;

void __osResetGlobalIntMask(OSHWIntr interrupt) {
    register u32 saveMask = __osDisableInt();

    //not sure about these constants, SR_IBIT3 is external level 3 INT0, which I think corresponds to the rcp
    //os.h has several masks defined that end in 401 but non that are just 401
    __OSGlobalIntMask &= ~(interrupt & ~(SR_IBIT3 | SR_IE));

    __osRestoreInt(saveMask);
}
