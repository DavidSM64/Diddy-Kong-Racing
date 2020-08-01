/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C8F80 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

//GLOBAL_ASM("lib/asm/non_matchings/unknown_0C9B80/osPiStartDma.s")

extern OSDevMgr D_800E3740; //__osPiDevMgr;

s32 osPiStartDma(OSIoMesg *mb, s32 priority, s32 direction, u32 devAddr, void *dramAddr, u32 size, OSMesgQueue *mq)
{
    register s32 ret;
    if (!D_800E3740.active)
        return -1;
    if (direction == OS_READ)
        mb->hdr.type = 11;
    else
        mb->hdr.type = 12;
    mb->hdr.pri = priority;
    mb->hdr.retQueue = mq;
    mb->dramAddr = dramAddr;
    mb->devAddr = devAddr;
    mb->size = size;
    mb->piHandle = NULL;
    if (priority == OS_MESG_PRI_HIGH)
    {
        ret = osJamMesg(osPiGetCmdQueue(), (OSMesg)mb, OS_MESG_NOBLOCK);
    }
    else
    {
        ret = osSendMesg(osPiGetCmdQueue(), (OSMesg)mb, OS_MESG_NOBLOCK);
    }
    return ret;
}