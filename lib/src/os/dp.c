/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D6050 */

#include "macros.h"
#include "libultra_internal.h"

int __osDpDeviceBusy(void) {
    register u32 stat;
    stat = IO_READ(DPC_STATUS_REG);
    if (stat & DPC_STATUS_DMA_BUSY)
        return 1;
    return 0;
}
