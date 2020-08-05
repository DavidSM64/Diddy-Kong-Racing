/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C85A0 */

#include "libultra_internal.h"
#include "types.h"
#include "macros.h"

GLOBAL_ASM("lib/asm/non_matchings/unknown_0C91A0/func_800C85A0.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C91A0/func_800C85D0.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C91A0/func_800C8600.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C91A0/alUnlink.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C91A0/alLink.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C91A0/func_800C87B4.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C91A0/func_800C87EC.s")

extern OSThread __osThreadTail;
void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 msgCount)
{
    mq->mtqueue = (OSThread *)&__osThreadTail;
    mq->fullqueue = (OSThread *)&__osThreadTail;
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = msgCount;
    mq->msg = msg;
}