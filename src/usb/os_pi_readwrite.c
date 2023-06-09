/* RAM_POS: 0x800d0de0 */

//#include "macros.h"
#include "libultra_internal.h"
#include "../../lib/src/os/piint.h"

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
