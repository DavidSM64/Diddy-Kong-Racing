/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2470 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/func_800D2470.s")

#define PI_Q_BUF_LEN 1
extern u32 D_800E4800;//__osPiAccessQueueEnabled
extern OSMesg D_8012D1E0[PI_Q_BUF_LEN];//piAccessBuf
extern OSMesgQueue D_8012D1E8; //__osPiAccessQueue
void __osPiCreateAccessQueue(void)
{

	D_800E4800 = 1;
	osCreateMesgQueue(&D_8012D1E8, D_8012D1E0, PI_Q_BUF_LEN);
	osSendMesg(&D_8012D1E8, NULL, OS_MESG_NOBLOCK);
}

void __osPiGetAccess(void)
{
	OSMesg dummyMesg;
	if (!D_800E4800)
		__osPiCreateAccessQueue();
	osRecvMesg(&D_8012D1E8, &dummyMesg, OS_MESG_BLOCK);
}

void __osPiRelAccess(void)
{
	osSendMesg(&D_8012D1E8, NULL, OS_MESG_NOBLOCK);
}