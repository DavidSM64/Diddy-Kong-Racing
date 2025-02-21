/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C6000 */

#include "types.h"
#include "libultra_internal.h"
#include "stacks.h"
#include "lib/src/os/piint.h"
#include "macros.h"

static OSThread piThread ALIGNED(0x8);
static STACK(piThreadStack, OS_PIM_STACKSIZE) ALIGNED(0x10);

static OSMesgQueue piEventQueue ALIGNED(0x8);
static OSMesg piEventBuf[1];

OSDevMgr __osPiDevMgr = { 0 };

#ifndef RAREDIFFS
OSPiHandle* __osPiTable = NULL;
#if BUILD_VERSION >= VERSION_J
OSPiHandle __Dom1SpeedParam ALIGNED(0x8);
OSPiHandle __Dom2SpeedParam ALIGNED(0x8);
OSPiHandle* __osCurrentHandle[2] ALIGNED(0x8) = { &__Dom1SpeedParam, &__Dom2SpeedParam };
#else
extern OSPiHandle CartRomHandle;
extern OSPiHandle LeoDiskHandle;
OSPiHandle* __osCurrentHandle[2] ALIGNED(0x8) = { &CartRomHandle, &LeoDiskHandle };
#endif
#endif

void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQ, OSMesg* cmdBuf, s32 cmdMsgCnt) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

#ifdef _DEBUG
    if ((pri < OS_PRIORITY_IDLE) || (pri > OS_PRIORITY_MAX)) {
        __osError(ERR_OSCREATEPIMANAGER, 1, pri);
        return;
    }
#endif

    if (__osPiDevMgr.active) {
        return;
    }
    osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
    osCreateMesgQueue(&piEventQueue, (OSMesg*)piEventBuf, 1);

    if (!__osPiAccessQueueEnabled) {
        __osPiCreateAccessQueue();
    }

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
    __osPiDevMgr.dma = __osPiRawStartDma;
    __osPiDevMgr.edma = __osEPiRawStartDma;
    osCreateThread(&piThread, 0, __osDevMgrMain, &__osPiDevMgr, STACK_START(piThreadStack), pri);
    osStartThread(&piThread);
    __osRestoreInt(savedMask);

    if (oldPri != -1) {
        osSetThreadPri(NULL, oldPri);
    }
}
