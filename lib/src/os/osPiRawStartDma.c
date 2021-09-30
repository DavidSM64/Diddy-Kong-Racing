/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D25a0 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "PR/rcp.h"

s32 osPiRawStartDma(s32 direction, u32 devAddr, void *dramAddr, u32 size) {
    register int status;
    status = IO_READ(PI_STATUS_REG);
    while (status & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY | PI_STATUS_ERROR)) {
        status = IO_READ(PI_STATUS_REG);
    }

    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dramAddr));
    IO_WRITE(PI_CART_ADDR_REG, K1_TO_PHYS(osRomBase | devAddr));

    switch (direction) {
        case OS_READ:
            IO_WRITE(PI_WR_LEN_REG, size - 1);
            break;
        case OS_WRITE:
            IO_WRITE(PI_RD_LEN_REG, size - 1);
            break;
        default:
            return -1;
            break;
    }
    return 0;
}
