/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C8820 */

#include "libultra_internal.h"
#include "types.h"

extern OSThread __osThreadTail;
void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 msgCount) {
    mq->mtqueue = (OSThread *)&__osThreadTail;
    mq->fullqueue = (OSThread *)&__osThreadTail;
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = msgCount;
    mq->msg = msg;
}
