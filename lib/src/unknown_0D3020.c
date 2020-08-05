/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2470 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/func_800D2470.s")

#define PI_Q_BUF_LEN 1
extern u32 __osPiAccessQueueEnabled;//__osPiAccessQueueEnabled
extern OSMesg D_8012D1E0[PI_Q_BUF_LEN];//piAccessBuf
extern OSMesgQueue piAccessQueue; //__osPiAccessQueue
void __osPiCreateAccessQueue(void)
{

	__osPiAccessQueueEnabled = 1;
	osCreateMesgQueue(&piAccessQueue, D_8012D1E0, PI_Q_BUF_LEN);
	osSendMesg(&piAccessQueue, NULL, OS_MESG_NOBLOCK);
}

void __osPiGetAccess(void)
{
	OSMesg dummyMesg;
	if (!__osPiAccessQueueEnabled)
		__osPiCreateAccessQueue();
	osRecvMesg(&piAccessQueue, &dummyMesg, OS_MESG_BLOCK);
}

void __osPiRelAccess(void)
{
	osSendMesg(&piAccessQueue, NULL, OS_MESG_NOBLOCK);
}