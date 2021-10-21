/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D2B10 */

#include "libultra_internal.h"
#include "viint.h"
#include "video.h"

extern OSViMode	osViModeNtscLan1;
extern OSViMode	osViModePalLan1;
extern OSViMode	osViModeMpalLan1;
extern __OSViContext vi[2];
extern __OSViContext *__osViCurr;
extern __OSViContext *__osViNext;
extern s32 osViClock;

void __osViInit(void) {
	bzero(vi, sizeof(vi));
	__osViCurr = &vi[0];
	__osViNext = &vi[1];
	__osViNext->retraceCount = 1;
	__osViCurr->retraceCount = 1;
	if (osTvType == OS_TV_TYPE_PAL) {
		__osViNext->modep = &osViModePalLan1;
        osViClock = VI_PAL_CLOCK;
	} else if (osTvType == OS_TV_TYPE_MPAL) {
		__osViNext->modep = &osViModeMpalLan1;
        osViClock = VI_MPAL_CLOCK;
	} else {
		__osViNext->modep = &osViModeNtscLan1;
        osViClock = VI_NTSC_CLOCK;
	}
	__osViNext->state = VI_STATE_BLACK;
	__osViNext->control = __osViNext->modep->comRegs.ctrl;
	while (IO_READ(VI_CURRENT_REG) > 10); //wait for vsync?
	IO_WRITE(VI_CONTROL_REG, 0); //pixel size blank (no data, no sync)
	__osViSwapContext();
}
