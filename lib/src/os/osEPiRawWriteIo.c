/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D6560 */

#include "libultra_internal.h"
#include "piint.h"

s32 osEPiRawWriteIo(OSPiHandle *pihandle, u32 devAddr, u32 data) {
    register u32 stat = IO_READ(PI_STATUS_REG);

	while (stat & PI_STATUS_ERROR)
		stat = IO_READ(PI_STATUS_REG);

    IO_WRITE(pihandle->baseAddress | devAddr, data);
    return 0;
}
