/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80063C30 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "audio_internal.h"

extern s32 alAuxBusPull;
extern s32 alAuxBusParam;
extern s32 alEnvMixerPull;
extern s32 alEnvmixerParam;
extern s32 alLoadParam;
extern s32 alLoadPull;
extern s32 alResampleParam;
extern s32 alResamplePull;
extern s32 alMainBusParam;
extern s32 alMainBusPull;
extern s32 alSaveParam;
extern s32 alSavePull;

GLOBAL_ASM("asm/non_matchings/unknown_064830/alFxPull.s")

s32 alFxParam(void* filter, s32 paramID, void* param) {
    if (paramID == 1) {
        ((ALFilter *)filter)->source = param;
    }
    return 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_064830/alFxParamHdl.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/_loadOutputBuffer.s")
GLOBAL_ASM("asm/non_matchings/unknown_064830/_loadBuffer.s")
//GLOBAL_ASM("asm/non_matchings/unknown_064830/_saveBuffer.s")

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

#define	SCALE 16384

void init_lpfilter(ALLowPass *lp)
{
    s32		i, temp;
    s16		fc;
    f64		ffc, fcoef;

    temp = lp->fc * SCALE;
    fc = temp >> 15;
    lp->fgain = SCALE - fc;

    lp->first = 1;
    for (i=0; i<8; i++)
	lp->fcvec.fccoef[i] = 0;
    
    lp->fcvec.fccoef[i++] = fc;
    fcoef = ffc = (f64)fc/SCALE;

    for (; i<16; i++){
	fcoef *= ffc;
	lp->fcvec.fccoef[i] = (s16)(fcoef * SCALE);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_064830/alFxNew.s")

void alEnvmixerNew(ALEnvMixer* e, s32 arg1) {
    alFilterNew(e, &alEnvMixerPull, &alEnvmixerParam, 4);
    e->state = alHeapDBAlloc(0, 0, arg1, 1, 0x50);
    e->first = 1;
    e->motion = AL_STOPPED;
    e->volume = 1;
    e->ltgt = 1;
    e->rtgt = 1;
    e->cvolL = 1;
    e->cvolR = 1;
    e->dryamt = 0;
    e->wetamt = 0;
    e->lratm = 1;
    e->lratl = 0;
    e->delta = 0;
    e->segEnd = 0;
    e->pan = 0;
    e->ctrlList = 0;
    e->ctrlTail = 0;
    e->sources = 0;
}

void alLoadNew(ALLoadFilter* arg0, s32 (*arg1)(s32*), s32 arg2) {
    alFilterNew(arg0, &alLoadPull, &alLoadParam, 0);
    arg0->state = alHeapDBAlloc(0, 0, arg2, 1, 0x20);
    arg0->lstate = alHeapDBAlloc(0, 0, arg2, 1, 0x20);
    arg0->dma = arg1(&arg0->dmaState);
    arg0->lastsam = 0;
    arg0->first = 1;
    arg0->memin = 0;
}

void alResampleNew(ALResampler* r, ALHeap* hp) {
    alFilterNew(r, &alResamplePull, &alResampleParam, 1);
    r->state = alHeapDBAlloc(0, 0, hp, 1, 0x20);
    r->first = 1;
    r->motion = AL_STOPPED;
    r->upitch = 0;
    r->ctrlList = 0;
    r->ctrlTail = 0;
    r->delta = 0.0f;
    r->ratio = 1.0f;
}

void alAuxBusNew(ALAuxBus* m, void* sources, s32 maxSources) {
    alFilterNew(m, &alAuxBusPull, &alAuxBusParam, 6);
    m->sourceCount = 0;
    m->maxSources = maxSources;
    m->sources = sources;
}

void alMainBusNew(ALMainBus* m, void* sources, s32 maxSources) {
    alFilterNew(m, &alMainBusPull, &alMainBusParam, 7);
    m->sourceCount = 0;
    m->maxSources = maxSources;
    m->sources = sources;
}

void alSaveNew(ALSave* f) {
    alFilterNew(f, &alSavePull, &alSaveParam, AL_SAVE);
    f->dramout = 0;
    f->first = 1;
}
