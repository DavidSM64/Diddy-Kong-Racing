/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D1DF0 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "os/osVirtualToPhysical.h"

typedef struct
{
    /* 0x0 */ f32 factor;
    /* 0x4 */ u16 offset;
    /* 0x8 */ u32 scale;
} __OSViScale;

typedef struct
{
    /* 0x0 */ u16 state;
    /* 0x2 */ u16 retraceCount;
    /* 0x4 */ void *framep;
    /* 0x8 */ OSViMode *modep;
    /* 0xC */ u32 control;
    /* 0x10 */ OSMesgQueue *msgq;
    /* 0x14 */ OSMesg msg;
    /* 0x18 */ __OSViScale x;
    /* 0x24 */ __OSViScale y;
} __OSViContext;

__OSViContext vi[2] = {0};

__OSViContext *__osViCurr = &vi[0];
__OSViContext *__osViNext = &vi[1];

//TODO: This should be defined above osInitialize
#define VI_NTSC_CLOCK 48681812
s32 osViClock = VI_NTSC_CLOCK;

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D29F0/osSpTaskYielded.s")

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


//TODO Split into sptask.c and seperate header

#define OS_TASK_YIELDED			0x0001

#define SP_CLR_HALT		0x00001	    /* Bit  0: clear halt */
#define SP_CLR_BROKE		0x00004	    /* Bit  2: clear broke */
#define SP_CLR_SSTEP		0x00020	    /* Bit  5: clear sstep */
#define SP_SET_INTR_BREAK	0x00100	    /* Bit  8: set intr on break */
#define SP_CLR_SIG0		0x00200	    /* Bit  9: clear signal 0 */
#define SP_CLR_SIG1		0x00800	    /* Bit 11: clear signal 1 */
#define SP_CLR_SIG2		0x02000	    /* Bit 11: clear signal 1 */



#define SP_CLR_YIELD		SP_CLR_SIG0
#define SP_CLR_YIELDED		SP_CLR_SIG1
#define SP_CLR_TASKDONE		SP_CLR_SIG2

#define SP_IMEM_START		0x04001000	/* read/write */

#define _osVirtualToPhysical(ptr)               \
	if (ptr != NULL)                            \
	{                                           \
		ptr = (void *)osVirtualToPhysical(ptr); \
	}

extern OSTask D_8012D1A0;
OSTask *_VirtualToPhysicalTask(OSTask *intp)
{
	OSTask *tp;
	tp = &D_8012D1A0;
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

void osSpTaskLoad(OSTask *intp){

	OSTask *tp;
	tp = _VirtualToPhysicalTask(intp);
	if (tp->t.flags & OS_TASK_YIELDED)
	{
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
