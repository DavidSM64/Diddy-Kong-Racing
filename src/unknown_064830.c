/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80063C30 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "audio_internal.h"

/************ .data ************/

s8 D_800DCEB0 = 1;
s32 D_800DCEB4 = 0x10; // Currently unknown, might be a different type.
s32 D_800DCEB8 = 0x10; // Currently unknown, might be a different type.
s32 D_800DCEBC = 0x20; // Currently unknown, might be a different type.

/*******************************/

GLOBAL_ASM("asm/non_matchings/unknown_064830/alFxPull.s")

s32 alFxParam(void* filter, s32 paramID, void* param) {
    if (paramID == 1) {
        ((ALFilter *)filter)->source = param;
    }
    return 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_064830/alFxParamHdl.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/_loadOutputBuffer.s")

/* 
 * This routine is for loading data from the delay line buff. If the
 * address of curr_ptr < r->base, it will force it to be within r->base
 * space, If the load goes past the end of r->base it will wrap around.
 * Cause count bytes of data at curr_ptr (within the delay line) to be
 * loaded into buff. (Buff is a dmem buffer)
 */
Acmd *_loadBuffer(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p)
{
    Acmd    *ptr = p;
    s32     after_end, before_end;
    s16     *updated_ptr, *delay_end;

#ifdef AUD_PROFILE
    lastCnt[++cnt_index] = osGetCount();
#endif

    delay_end = &r->base[r->length];

#ifdef _DEBUG
    if(curr_ptr > delay_end)
        __osError(ERR_ALMODDELAYOVERFLOW, 1, delay_end - curr_ptr);
#endif

    if (curr_ptr < r->base)
    curr_ptr += r->length;
    updated_ptr = curr_ptr + count;
    
    if (updated_ptr > delay_end) {
        after_end = updated_ptr - delay_end;
        before_end = delay_end - curr_ptr;
        
        aSetBuffer(ptr++, 0, buff, 0, before_end<<1);
        aLoadBuffer(ptr++, osVirtualToPhysical(curr_ptr));
        aSetBuffer(ptr++, 0, buff+(before_end<<1), 0, after_end<<1);
        aLoadBuffer(ptr++, osVirtualToPhysical(r->base));
    } else {
        aSetBuffer(ptr++, 0, buff, 0, count<<1);
        aLoadBuffer(ptr++, osVirtualToPhysical(curr_ptr));
    }

    aSetBuffer(ptr++, 0, 0, 0, count<<1);

#ifdef AUD_PROFILE
    PROFILE_AUD(load_num, load_cnt, load_max, load_min);
#endif
    return ptr;

}

/*
 * This routine is for writing data to the delay line buff. If the
 * address of curr_ptr < r->base, it will force it to be within r->base
 * space. If the write goes past the end of r->base, it will wrap around
 * Cause count bytes of data at buff to be written to delay line, curr_ptr.
 */
Acmd *_saveBuffer(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p)
{
    Acmd    *ptr = p;
    s32     after_end, before_end;
    s16     *updated_ptr, *delay_end;

#ifdef AUD_PROFILE
    lastCnt[++cnt_index] = osGetCount();
#endif

    delay_end = &r->base[r->length];
    if (curr_ptr < r->base)      /* probably just security */
        curr_ptr += r->length;   /* shouldn't occur */
    updated_ptr = curr_ptr + count;

    if (updated_ptr > delay_end) { /* if the data wraps past end of r->base */
        after_end = updated_ptr - delay_end;
        before_end = delay_end - curr_ptr;

        aSetBuffer(ptr++, 0, 0, buff, before_end<<1);
        aSaveBuffer(ptr++, osVirtualToPhysical(curr_ptr));
        aSetBuffer(ptr++, 0, 0, buff+(before_end<<1), after_end<<1);
        aSaveBuffer(ptr++, osVirtualToPhysical(r->base));
        aSetBuffer(ptr++, 0, 0, 0, count<<1);
    } else {
        aSetBuffer(ptr++, 0, 0, buff, count<<1);
        aSaveBuffer(ptr++, osVirtualToPhysical(curr_ptr));
    }

#ifdef AUD_PROFILE
    PROFILE_AUD(save_num, save_cnt, save_max, save_min);
#endif
    return ptr;

}

Acmd *_filterBuffer(ALLowPass *lp, s32 buff, s32 count, Acmd *p)
{
    Acmd	*ptr = p;

    aSetBuffer(ptr++, 0, buff, buff, count<<1);
    aLoadADPCM(ptr++, 32, osVirtualToPhysical(lp->fcvec.fccoef));
    aPoleFilter(ptr++, lp->first, lp->fgain, osVirtualToPhysical(lp->fstate));
    lp->first = 0;

    return ptr;
}

GLOBAL_ASM("asm/non_matchings/unknown_064830/_doModFunc.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/func_8006492C.s")
