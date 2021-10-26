/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D52C0 */

#include "libultra_internal.h"
#include "siint.h"

int __osSiDeviceBusy() {
    register u32 stat = IO_READ(SI_STATUS_REG);
    if (stat & (SI_STATUS_DMA_BUSY | SI_STATUS_RD_BUSY))
        return 1;
    return 0;
}
