/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D63FC */

#include "libultra_internal.h"

s32 __osSpSetPc(u32 data) {
    register u32 stat = IO_READ(SP_STATUS_REG);
    if (!(stat & SP_STATUS_HALT))
        return -1;
    else {
        IO_WRITE(SP_PC_REG, data);
    }
    return 0;
}
