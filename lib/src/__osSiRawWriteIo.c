/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D45E0 */

#include "types.h"

#define	PHYS_TO_K1(x)	((u32)(x)|0xA0000000)	/* physical to kseg1 */
#define	IO_WRITE(addr,data)	(*(vu32 *)PHYS_TO_K1(addr)=(u32)(data))

s32 __osSiRawWriteIo(u32 devAddr, u32 data)
{

    if (__osSiDeviceBusy())
        return -1;
    IO_WRITE(devAddr, data);
    return 0;
}