/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80063C30 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "audio_internal.h"
#include "initfx.h"

// TODO: these come from headers
#ident "$Revision: 1.49 $"
#ident "$Revision: 1.17 $"

#define RANGE 2.0
extern ALGlobals *alGlobals;

#ifdef AUD_PROFILE
extern u32 cnt_index, reverb_num, reverb_cnt, reverb_max, reverb_min, lastCnt[];
extern u32 load_num, load_cnt, load_max, load_min, save_num, save_cnt, save_max, save_min;
#endif

/*
 * macros
 */
#define SWAP(in, out)	\
{			\
     s16 t = out;	\
     out = in;		\
     in = t;		\
}



Acmd *_loadOutputBuffer(ALFx *r, ALDelay *d, s32 buff, s32 incount, Acmd *p);
Acmd *_loadBuffer(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p);
Acmd *_saveBuffer(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p);
Acmd *_filterBuffer(ALLowPass *lp, s32 buff, s32 count, Acmd *p);
f32  _doModFunc(ALDelay *d, s32 count);

u8 D_800DCEB0 = 1;
static s32 L_INC[] = { L0_INC, L1_INC, L2_INC };

/***********************************************************************
 * Reverb filter public interfaces
 ***********************************************************************/
Acmd *alFxPull(void *filter, s16 *outp, s32 outCount, s32 sampleOffset,
                     Acmd *p) 
{
    Acmd        *ptr = p;
    ALFx	*r = (ALFx *)filter;
    ALFilter    *source = r->filter.source;
    s16		i, buff1, buff2, input, output;
    s16		*in_ptr, *out_ptr, *prev_out_ptr = 0;
    ALDelay	*d;

#ifdef AUD_PROFILE
    lastCnt[++cnt_index] = osGetCount();
#endif
    
#ifdef _DEBUG
    assert(source);
#endif

    /*
     * pull channels going into this effect first
     */
    ptr = (*source->handler)(source, outp, outCount, sampleOffset, p);

    //Added by Rare Devs
    if (D_800DCEB0 == 0) {
        return ptr;
    }

    input  = AL_AUX_L_OUT;
    output = AL_AUX_R_OUT;
    buff1  = AL_TEMP_0;
    buff2  = AL_TEMP_1;
    
    aSetBuffer(ptr++, 0, 0, 0, outCount<<1);  /* set the buffer size */
    aMix(ptr++, 0, 0xda83, AL_AUX_L_OUT, input); /* .707L = L - .293L */
    aMix(ptr++, 0, 0x5a82, AL_AUX_R_OUT, input); /* mix the AuxL and AuxR into the AuxL */
    /* and write the mixed value to the delay line at r->input */
    ptr = _saveBuffer(r, r->input, input, outCount, ptr);

    aClearBuffer(ptr++, output, outCount<<1); /* clear the AL_AUX_R_OUT */

    for (i = 0; i < r->section_count; i++) {
	d  = &r->delay[i];  /* get the ALDelay structure */
	in_ptr  = &r->input[-d->input];
	out_ptr = &r->input[-d->output];
	
	if (in_ptr == prev_out_ptr) {
	    SWAP(buff1, buff2);
	} else {  /* load data at in_ptr into buff1 */
	    ptr = _loadBuffer(r, in_ptr, buff1, outCount, ptr);
	}
	ptr = _loadOutputBuffer(r, d, buff2, outCount, ptr);

	if (d->ffcoef) {
	    aMix(ptr++, 0, (u16)d->ffcoef, buff1, buff2);
	    if (!d->rs && !d->lp) {
		ptr = _saveBuffer(r, out_ptr, buff2, outCount, ptr);
	    }
	}
	
	if (d->fbcoef) {
	    aMix(ptr++, 0, (u16)d->fbcoef, buff2, buff1);
	    ptr = _saveBuffer(r, in_ptr, buff1, outCount, ptr);
	}

	if (d->lp)
	    ptr = _filterBuffer(d->lp, buff2, outCount, ptr);

	if (!d->rs)
	    ptr = _saveBuffer(r, out_ptr, buff2, outCount, ptr);
	
	if (d->gain)
	    aMix(ptr++, 0, (u16)d->gain, buff2, output);
	
	prev_out_ptr = &r->input[d->output];
    }

    /*
     * bump the master delay line input pointer
     * modulo the length
     */
    r->input += outCount;
    if (r->input > &r->base[r->length])
	r->input -= r->length;

    /*
     * output already in AL_AUX_R_OUT
     *      just copy to AL_AUX_L_OUT
     */
    aDMEMMove(ptr++, output, AL_AUX_L_OUT, outCount<<1);

#ifdef AUD_PROFILE
    PROFILE_AUD(reverb_num, reverb_cnt, reverb_max, reverb_min);
#endif
    return ptr;
}

s32 alFxParam(void *filter, s32 paramID, void *param) {
    if (paramID == 1) {
        ((ALFilter *)filter)->source = param;
    }
    return 0;
}

GLOBAL_ASM("lib/asm/non_matchings/reverb/alFxParamHdl.s")
GLOBAL_ASM("lib/asm/non_matchings/reverb/_loadOutputBuffer.s")

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

GLOBAL_ASM("lib/asm/non_matchings/reverb/_doModFunc.s")

void func_8006492C(u8 arg0) {
    D_800DCEB0 = arg0;
}

u8 func_8006493C() {
    return D_800DCEB0;
}