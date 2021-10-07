/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1DF0 */

#include "libultra_internal.h"
#include "viint.h"

__OSViContext vi[2] = {0};
__OSViContext *__osViCurr = &vi[0];
__OSViContext *__osViNext = &vi[1];

//TODO: This should be defined above osInitialize
#define OS_TASK_YIELDED 0x0001
#define OS_TASK_DP_WAIT	0x0002
s32 osViClock = VI_NTSC_CLOCK;

OSYieldResult osSpTaskYielded(OSTask *tp) {
    u32 status;
    OSYieldResult result;
    status = __osSpGetStatus();
    if (status & SP_STATUS_YIELDED)
        result = OS_TASK_YIELDED;
    else
        result = 0;
    if (status & SP_STATUS_YIELD) {
        tp->t.flags |= result;
        tp->t.flags &= ~(OS_TASK_DP_WAIT);
    }
    return result;
}

void *osViGetCurrentFramebuffer(void){
    register u32 saveMask;
    void *framep;

    saveMask = __osDisableInt();
    framep = __osViCurr->framep;
    __osRestoreInt(saveMask);
    return framep;
}

void *osViGetNextFramebuffer(void){
    register u32 saveMask;
    void *framep;

    saveMask = __osDisableInt();
    framep = __osViNext->framep;
    __osRestoreInt(saveMask);
    return framep;
}

#define _osVirtualToPhysical(ptr)               \
    if (ptr != NULL) {                          \
        ptr = (void *)osVirtualToPhysical(ptr); \
    }

extern OSTask tmp_task;
OSTask *_VirtualToPhysicalTask(OSTask *intp) {
    OSTask *tp;
    tp = &tmp_task;
    bcopy(intp, tp, sizeof(OSTask));

    _osVirtualToPhysical(tp->t.ucode);
    _osVirtualToPhysical(tp->t.ucode_data);
    _osVirtualToPhysical(tp->t.dram_stack);
    _osVirtualToPhysical(tp->t.output_buff);
    _osVirtualToPhysical(tp->t.output_buff_size);
    _osVirtualToPhysical(tp->t.data_ptr);
    _osVirtualToPhysical(tp->t.yield_data_ptr);
    return tp;
}

void osSpTaskLoad(OSTask *intp) {
    OSTask *tp;
    tp = _VirtualToPhysicalTask(intp);
    if (tp->t.flags & OS_TASK_YIELDED) {
        tp->t.ucode_data = tp->t.yield_data_ptr;
        tp->t.ucode_data_size = tp->t.yield_data_size;
        intp->t.flags &= ~OS_TASK_YIELDED;
    }

    osWritebackDCache(tp, sizeof(OSTask));
    __osSpSetStatus(SP_CLR_YIELD | SP_CLR_YIELDED | SP_CLR_TASKDONE | SP_SET_INTR_BREAK);
    while (__osSpSetPc(SP_IMEM_START) == -1)
        ;

    while (__osSpRawStartDma(1, (SP_IMEM_START - sizeof(*tp)), tp,
                             sizeof(OSTask)) == -1)
        ;

    while (__osSpDeviceBusy())
        ;

    while (__osSpRawStartDma(1, SP_IMEM_START, tp->t.ucode_boot,
                             tp->t.ucode_boot_size) == -1)
        ;
}

void osSpTaskStartGo(OSTask *tp) {
    while (__osSpDeviceBusy());

    __osSpSetStatus(SP_SET_INTR_BREAK | SP_CLR_SSTEP | SP_CLR_BROKE | SP_CLR_HALT);
}
