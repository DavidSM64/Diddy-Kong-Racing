/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D64D0 */

#include "libultra_internal.h"

int __osSpDeviceBusy() {
    register u32 stat = IO_READ(SP_STATUS_REG);
    if (stat & (SP_STATUS_DMA_BUSY | SP_STATUS_DMA_FULL | SP_STATUS_IO_FULL))
        return 1;
    return 0;
}
