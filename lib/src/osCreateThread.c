/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C8850 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "PR/R4300.h"

//GLOBAL_ASM("lib/asm/non_matchings/osCreateThread_0C9450/osCreateThread.s")

extern OSThread *D_800E488C; //__osActiveQueue;
void D_800D35A0(void); //__osCleanupThread

void osCreateThread(OSThread *t, OSId id, void (*entry)(void *), void *arg, void *sp, OSPri p)
{
    register u32 saveMask;
    OSIntMask mask;
    t->id = id;
    t->priority = p;
    t->next = NULL;
    t->queue = NULL;
    t->context.pc = (u32)entry;
    t->context.a0 = (u64)arg;
    t->context.sp = (u64)sp - 16;
    t->context.ra = (u64)D_800D35A0;
    mask = OS_IM_ALL;
    t->context.sr = SR_IMASK | SR_EXL | SR_IE;
    t->context.rcp = (mask & RCP_IMASK) >> RCP_IMASKSHIFT;
    t->context.fpcsr = (u32)(FPCSR_FS | FPCSR_EV);
    t->fp = 0;
    t->state = OS_STATE_STOPPED;
    t->flags = 0;
    saveMask = __osDisableInt();
    t->tlnext = D_800E488C;
    D_800E488C = t;
    __osRestoreInt(saveMask);
}