/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D4EC0 */

#include "macros.h"
#include "libultra_internal.h"

extern OSTimer __osBaseTimer;
OSTimer *__osTimerList = &__osBaseTimer;

extern OSTime __osCurrentTime;
extern u32 __osBaseCounter;
extern u32 __osViIntrCount;
extern u32 __osTimerCounter;


OSTime __osInsertTimer(OSTimer *t);

#ifdef NON_EQUIVALENT
//Seems to be a mismatch based on where __osCurrentTime is defined.
//Scratch proving that: https://decomp.me/scratch/OB3iP
void __osTimerServicesInit(void) {
    __osCurrentTime = 0;
    __osBaseCounter = 0;
    __osViIntrCount = 0;
    __osTimerList->prev = __osTimerList;
    __osTimerList->next = __osTimerList->prev;
    __osTimerList->remaining = 0;
    __osTimerList->interval = __osTimerList->remaining;
    __osTimerList->mq = NULL;
    __osTimerList->msg = 0;
}
#else
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/__osTimerServicesInit.s")
#endif

void __osSetTimerIntr(OSTime tim);
void __osSetCompare(u32);

void __osTimerInterrupt(void) {
    OSTimer *t;
    u32 count;
    u32 elapsed_cycles;

    if (__osTimerList->next == __osTimerList)
        return;
    while (1) {
        t = __osTimerList->next;
        if (t == __osTimerList){
            __osSetCompare(0);
            __osTimerCounter = 0;
            break;
        }
        count = osGetCount();
        elapsed_cycles = count - __osTimerCounter;
        __osTimerCounter = count;
        if (elapsed_cycles < t->remaining){
            t->remaining -= elapsed_cycles;
            __osSetTimerIntr(t->remaining);
            return;
        } else {
            t->prev->next = t->next;
            t->next->prev = t->prev;
            t->next = NULL;
            t->prev = NULL;
            if (t->mq != NULL){
                osSendMesg(t->mq, t->msg, OS_MESG_NOBLOCK);
            }
            if (t->interval != 0){
                t->remaining = t->interval;
                __osInsertTimer(t);
            }
        }
    }
}

void __osSetTimerIntr(OSTime tim) {
    OSTime NewTime;
    u32 savedMask;
    savedMask = __osDisableInt();
    __osTimerCounter = osGetCount();
    NewTime = tim + __osTimerCounter;
    __osSetCompare(NewTime);
    __osRestoreInt(savedMask);
}

OSTime __osInsertTimer(OSTimer *t) {
    OSTimer *timep;
    OSTime tim;
    u32 savedMask;
    savedMask = __osDisableInt();
    for (timep = __osTimerList->next, tim = t->remaining;
         timep != __osTimerList && tim > timep->remaining;
         tim -= timep->remaining, timep = timep->next) {
        ;
    }
    t->remaining = tim;
    if (timep != __osTimerList)
        timep->remaining -= tim;
    t->next = timep;
    t->prev = timep->prev;
    timep->prev->next = t;
    timep->prev = t;
    __osRestoreInt(savedMask);
    return tim;
}
