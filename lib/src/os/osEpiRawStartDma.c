/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2680 */

#include "libultra_internal.h"
#include "PR/rcp.h"

s32 osEPiRawStartDma(OSPiHandle *pihandle, s32 dir, u32 cart_addr, void *dram_addr, u32 size) {
    register int status;

    status = IO_READ(PI_STATUS_REG);

    while (status & PI_STATUS_ERROR) {
        status = IO_READ(PI_STATUS_REG);
    }

    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dram_addr));
    IO_WRITE(PI_CART_ADDR_REG, K1_TO_PHYS(pihandle->baseAddress | cart_addr));

    switch (dir) {
        case OS_READ:
            IO_WRITE(PI_WR_LEN_REG, size - 1);
            break;
        case OS_WRITE:
            IO_WRITE(PI_RD_LEN_REG, size - 1);
            break;
        default:
            return -1;
    }

    return 0;
}
