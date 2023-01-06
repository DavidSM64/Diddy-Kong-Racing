/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C6000 */

#include "types.h"
#include "libultra_internal.h"
#include "stacks.h"
#include "lib/src/os/piint.h"

extern OSMesgQueue __osPiAccessQueue;
extern u32 __osPiAccessQueueEnabled;
extern OSDevMgr __osPiDevMgr;

// bss variables
OSThread piThread;
u64 gPIMgrStack[0x20];
OSMesgQueue piEventQueue;
OSMesg piEventBuf[2];

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;
    if (!__osPiDevMgr.active) {
        osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
        osCreateMesgQueue(&piEventQueue, (OSMesg*)&piEventBuf, 1);
        if (!__osPiAccessQueueEnabled)
            __osPiCreateAccessQueue();
        osSetEventMesg(OS_EVENT_PI, &piEventQueue, (OSMesg)0x22222222);
        oldPri = -1;
        myPri = osGetThreadPri(NULL);
        if (myPri < pri) {
            oldPri = myPri;
            osSetThreadPri(NULL, pri);
        }
        savedMask = __osDisableInt();
        __osPiDevMgr.active = 1;
        __osPiDevMgr.thread = &piThread;
        __osPiDevMgr.cmdQueue = cmdQ;
        __osPiDevMgr.evtQueue = &piEventQueue;
        __osPiDevMgr.acsQueue = &__osPiAccessQueue;
        __osPiDevMgr.dma = osPiRawStartDma;
        __osPiDevMgr.edma = osEPiRawStartDma;

        osCreateThread(&piThread, 0, __osDevMgrMain, &__osPiDevMgr, &gPIMgrStack[0x20], pri);
        osStartThread(&piThread);
        __osRestoreInt(savedMask);
        if (oldPri != -1) {
            osSetThreadPri(NULL, oldPri);
        }
    }
}
