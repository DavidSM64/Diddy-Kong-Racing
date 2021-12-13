/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1990 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "viint.h"
#include "osint.h"

extern OSTime __osCurrentTime;
extern u32 __osBaseCounter;
extern u32 __osViIntrCount;

OSDevMgr __osViDevMgr = {0};

#define OS_VIM_STACKSIZE 4096
u8 viThreadStack[2960]; // Should be OS_VIM_STACKSIZE?

s32 gThread30Stack;

extern OSThread viThread;
extern OSMesgQueue viEventQueue;
extern OSMesg viEventBuf[5];
extern OSIoMesg viRetraceMsg;
extern OSIoMesg viCounterMsg;

void viMgrMain(void *arg);

void osCreateViManager(OSPri pri) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;
    if (__osViDevMgr.active == 0) {
        __osTimerServicesInit();
        osCreateMesgQueue(&viEventQueue, viEventBuf, 5);
        viRetraceMsg.hdr.type = OS_MESG_TYPE_VRETRACE;
        viRetraceMsg.hdr.pri = OS_MESG_PRI_NORMAL;
        viRetraceMsg.hdr.retQueue = NULL;
        viCounterMsg.hdr.type = OS_MESG_TYPE_COUNTER;
        viCounterMsg.hdr.pri = OS_MESG_PRI_NORMAL;
        viCounterMsg.hdr.retQueue = NULL;
        osSetEventMesg(OS_EVENT_VI, &viEventQueue, &viRetraceMsg);
        osSetEventMesg(OS_EVENT_COUNTER, &viEventQueue, &viCounterMsg);
        oldPri = -1;
        myPri = osGetThreadPri(NULL);
        if (myPri < pri) {
            oldPri = myPri;
            osSetThreadPri(NULL, pri);
        }
        savedMask = __osDisableInt();
        __osViDevMgr.active = 1;
        __osViDevMgr.thread = &viThread;
        __osViDevMgr.cmdQueue = &viEventQueue;
        __osViDevMgr.evtQueue = &viEventQueue;
        __osViDevMgr.acsQueue = NULL;
        __osViDevMgr.dma = NULL;
        __osViDevMgr.edma = NULL;
        osCreateThread(&viThread, 0, viMgrMain, &__osViDevMgr, &viThreadStack[OS_VIM_STACKSIZE], pri);
        __osViInit();
        osStartThread(&viThread);
        __osRestoreInt(savedMask);
        if (oldPri != -1) {
            osSetThreadPri(0, oldPri);
        }
    }
}

#ifdef NON_MATCHING
void __osTimerInterrupt(void);
//Fails due to how retrace is declared. Not sure how to fix it.
void viMgrMain(void *arg) {
    __OSViContext *vc;
    OSDevMgr *dm;
    OSIoMesg *mesg;
    static u16 retrace;
    s32 first;
    u32 count;

    mesg = NULL;
    first = FALSE;
    vc = __osViGetCurrentContext();
    retrace = vc->retraceCount;

    if (retrace == 0)
        retrace = 1;

    dm = (OSDevMgr *)arg;

    while (TRUE) {
        osRecvMesg(dm->evtQueue, (OSMesg *)&mesg, OS_MESG_BLOCK);
        switch (mesg->hdr.type) {
            case OS_MESG_TYPE_VRETRACE:
                __osViSwapContext();
                retrace--;
                if (retrace == 0) {
                    vc = __osViGetCurrentContext();
                    if (vc->msgq != NULL) {
                        osSendMesg(vc->msgq, vc->msg, OS_MESG_NOBLOCK);
                    }
                    retrace = vc->retraceCount;
                }
                __osViIntrCount++;
                if (first) {
                    count = osGetCount();
                    __osCurrentTime = count;
                    first = FALSE;
                }
                count = __osBaseCounter;
                __osBaseCounter = osGetCount();
                count = __osBaseCounter - count;
                __osCurrentTime = __osCurrentTime + count;
                break;

            case OS_MESG_TYPE_COUNTER:
                __osTimerInterrupt();
                break;
        }
    }
}
#else
GLOBAL_ASM("lib/asm/non_matchings/osViMgr_0D2590/viMgrMain.s")
#endif
