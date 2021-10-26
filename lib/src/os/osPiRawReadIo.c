/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4790 */

#include "macros.h"
#include "libultra_internal.h"
#include "piint.h"

s32 osPiRawReadIo(u32 devAddr, u32 *data) {
    register u32 stat;
    WAIT_ON_IOBUSY(stat);
    *data = IO_READ((u32)osRomBase | devAddr);
    return 0;
}
