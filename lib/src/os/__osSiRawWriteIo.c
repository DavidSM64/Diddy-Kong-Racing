/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D45E0 */

#include "types.h"
#include "siint.h"
#include "PR/rcp.h"

s32 __osSiRawWriteIo(u32 devAddr, u32 data) {
    if (__osSiDeviceBusy()) {
        return -1;
    }

    IO_WRITE(devAddr, data);

    return 0;
}
