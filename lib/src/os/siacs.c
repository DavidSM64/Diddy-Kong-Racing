/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CD600 */

#include "libultra_internal.h"
#include "controller.h"
#include "src/memory.h"

u32 __osSiAccessQueueEnabled = 0;

// Ok, so I completely gave up on the rest of these bss variables.
// This is probably not the right place for them, but we can always 
// fix that later.
#define SI_Q_BUF_LEN 1
static OSMesg siAccessBuf[SI_Q_BUF_LEN];
OSMesgQueue __osSiAccessQueue;
OSPifRam __osEepPifRam;
OSThread viThread;
u64 gViMgrStack[0x20];
s32 viEventQueue[6];
s32 viEventBuf[6];
s32 viRetraceMsg[6];
s32 viCounterMsg[6];
u16 retrace; //Used in viMgrMain, but it's supposed to be static in that function
u16 D_8012D192;
s32 D_8012D194[2];
OSTask tmp_task; //Supposed to be statically declared in sptask.c
#define PI_Q_BUF_LEN 1
OSMesg piAccessBuf[PI_Q_BUF_LEN]; //Should be static, but this works for now
s32 __osPiAccessQueue[6];
OSTimer __osBaseTimer;
OSTime __osCurrentTime;
s32 __osBaseCounter;
s32 __osViIntrCount;
u32 __osTimerCounter;
u32 D_8012D234[2];
OSThread gInterruptedThread;
MemoryPoolSlot *gMainMemoryPool;

void __osSiCreateAccessQueue(void) {
	__osSiAccessQueueEnabled = 1;
	osCreateMesgQueue(&__osSiAccessQueue, siAccessBuf, SI_Q_BUF_LEN);
	osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}

void __osSiGetAccess(void) {
	OSMesg dummyMesg;
	if (!__osSiAccessQueueEnabled)
		__osSiCreateAccessQueue();
	osRecvMesg(&__osSiAccessQueue, &dummyMesg, OS_MESG_BLOCK);
}

void __osSiRelAccess(void) {
	osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
