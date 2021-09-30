/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4590 */

#include "types.h"
#include "siint.h"
#include "PR/rcp.h"

s32 __osSiRawReadIo(u32 devAddr, u32 *data) {
    if (__osSiDeviceBusy()) {
        return -1;
    }

    *data = IO_READ(devAddr);

    return 0;
}
