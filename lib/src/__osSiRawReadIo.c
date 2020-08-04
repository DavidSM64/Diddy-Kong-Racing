/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4590 */

#include "types.h"
//#include "macros.h"

#define	PHYS_TO_K1(x)	((u32)(x)|0xA0000000)	/* physical to kseg1 */
#define	IO_READ(addr)		(*(vu32 *)PHYS_TO_K1(addr))

//GLOBAL_ASM("lib/asm/non_matchings/unknown_0D5190/__osSiRawReadIo.s")

s32 __osSiRawReadIo(u32 devAddr, u32 *data)
{
    if (__osSiDeviceBusy())
        return -1;
    *data = IO_READ(devAddr);
    return 0;
}
