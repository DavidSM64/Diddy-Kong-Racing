/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4790 */

#include "macros.h"
#include "libultra_internal.h"
#include "piint.h"
#include "config.h"

s32 osPiRawReadIo(u32 devAddr, u32 *data) {
    register u32 stat;
    WAIT_ON_IOBUSY(stat);
    *data = IO_READ((u32)osRomBase | devAddr);
    return 0;
}

#ifdef ENABLE_USB

// These are needed for the USB library to work.

s32 osPiRawWriteIo(u32 devAddr, u32 data) {
    register u32 stat;
    WAIT_ON_IOBUSY(stat);
    IO_WRITE((u32)osRomBase | devAddr, data);
    return 0;
}

s32 osPiReadIo(u32 devAddr, u32* data) {
    register s32 ret;

    __osPiGetAccess();
    ret = osPiRawReadIo(devAddr, data);
    __osPiRelAccess();

    return ret;
}

s32 osPiWriteIo(u32 devAddr, u32 data) {
    register s32 ret;

    __osPiGetAccess();
    ret = osPiRawWriteIo(devAddr, data);
    __osPiRelAccess();

    return ret;
}

#endif
