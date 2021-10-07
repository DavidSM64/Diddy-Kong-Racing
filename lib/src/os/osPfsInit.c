/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CED20 */

#include "macros.h"
#include "libultra_internal.h"
#include "controller.h"
#include "siint.h"

s32 osPfsInit(OSMesgQueue *queue, OSPfs *pfs, int channel) {
    s32 ret;
    ret = 0;
    __osSiGetAccess();
    ret = __osPfsGetStatus(queue, channel);
    __osSiRelAccess();
    if (ret != 0)
        return ret;

    pfs->queue = queue;
    pfs->channel = channel;
    pfs->status = 0;
    //pfs->activebank = -1; //Single difference between this an libreultra
    ERRCK(__osGetId(pfs));

    ret = osPfsChecker(pfs);
    pfs->status |= PFS_INITIALIZED;
    return ret;
}

#if 1
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CF330/__osPfsGetStatus.s")
#else
s32 osPfsIsPlug(OSMesgQueue *queue, u8 *pattern)
{
    s32 ret;
    OSMesg dummy;
    u8 bitpattern;
    OSContStatus data[MAXCONTROLLERS];
    int channel;
    u8 bits;
    int crc_error_cnt;
    ret = 0;
    bits = 0;
    crc_error_cnt = 3;
    __osSiGetAccess();
    while (TRUE)
    {
        __osPfsRequestData(CONT_CMD_REQUEST_STATUS);
        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
        __osPfsGetInitData(&bitpattern, data);
        for (channel = 0; channel < __osMaxControllers; channel++)
        {
            if ((data[channel].status & CONT_ADDR_CRC_ER) == 0)
            {
                crc_error_cnt--;
                break;
            }
        }
        if (__osMaxControllers == channel)
            crc_error_cnt = 0;
        if (crc_error_cnt < 1)
        {
            for (channel = 0; channel < __osMaxControllers; channel++)
            {
                if (data[channel].errno == 0 && (data[channel].status & CONT_CARD_ON) != 0)
                    bits |= 1 << channel;
            }
            __osSiRelAccess();
            *pattern = bits;
            return ret;
        }
    }
}
#endif
