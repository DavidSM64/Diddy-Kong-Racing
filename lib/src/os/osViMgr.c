/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1990 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"


extern OSTime __osCurrentTime;
extern u32 __osBaseCounter;
extern u32 __osViIntrCount; //__osViIntrCount

OSDevMgr __osViDevMgr = {0};

#define OS_VIM_STACKSIZE 4096
u8 viThreadStack[2960]; // viThreadStack[OS_VIM_STACKSIZE];

s32 gThread30Stack;

extern OSThread viThread;
extern OSMesgQueue viEventQueue;
extern OSMesg viEventBuf[5]; //viEventBuf;
extern OSIoMesg viRetraceMsg; //viRetraceMsg
extern OSIoMesg viCounterMsg; //viCounterMsg

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
		osCreateThread(&viThread, 0, viMgrMain, &__osViDevMgr, &viThreadStack[OS_VIM_STACKSIZE], pri); //TODO give 0x8012C130 a proper symbol
		__osViInit();
		osStartThread(&viThread);
		__osRestoreInt(savedMask);
		if (oldPri != -1) {
			osSetThreadPri(0, oldPri);
		}
	}
}
GLOBAL_ASM("lib/asm/non_matchings/osViMgr_0D2590/viMgrMain.s")
