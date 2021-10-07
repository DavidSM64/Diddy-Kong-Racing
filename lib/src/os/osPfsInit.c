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

//I would think this should be in it's own file, but it only works here
s32 __osPfsGetStatus(OSMesgQueue *queue, int channel) {
    s32 ret;
    OSMesg dummy;
    u8 pattern;
    OSContStatus data[MAXCONTROLLERS];
	
	ret = 0;
    __osPfsRequestData(0);
    
	ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    
	ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    
	__osPfsGetInitData(&pattern, data);

    if (data[channel].status & CONT_CARD_ON && data[channel].status & CONT_CARD_PULL) {
        return PFS_ERR_NEW_PACK;
    }
    
	if (data[channel].errno || !(data[channel].status & CONT_CARD_ON)) {
        return PFS_ERR_NOPACK;
    }
    
	if (data[channel].status & CONT_ADDR_CRC_ER) {
        return PFS_ERR_CONTRFAIL;
    }

    return ret;
}
