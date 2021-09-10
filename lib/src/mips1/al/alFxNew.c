/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80064950 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "audio_internal.h"

/*
 * WARNING: THE FOLLOWING CONSTANT MUST BE KEPT IN SYNC
 * WITH SCALING IN MICROCODE!!!
 */
#define	SCALE 16384

/*
 * the following arrays contain default parameters for
 * a few hopefully useful effects.
 */
#define ms *(((s32)((f32)44.1))&~0x7)

s32 SMALLROOM_PARAMS[26] = {
    /* sections	   length */
          3,        100 ms,
                                      /*       chorus  chorus   filter
       input  output  fbcoef  ffcoef   gain     rate   depth     coef  */
           0,   54 ms,  9830,  -9830,      0,      0,      0,      0,
       19 ms,   38 ms,  3276,  -3276, 0x3fff,      0,      0,      0,
           0,   60 ms,  5000,      0,      0,      0,      0, 0x5000
};

s32 BIGROOM_PARAMS[34] = {
    /* sections	   length */
          4,        100 ms,
                                      /*       chorus  chorus   filter
       input  output  fbcoef  ffcoef   gain     rate   depth     coef  */
           0,   66 ms,  9830,  -9830,      0,      0,      0,      0,
       22 ms,   54 ms,  3276,  -3276, 0x3fff,      0,      0,      0,
       66 ms,   91 ms,  3276,  -3276, 0x3fff,      0,      0,      0,
           0,   94 ms,  8000,      0,      0,      0,      0, 0x5000
};

s32 ECHO_PARAMS[10] = {
    /* sections	   length */
          1,       200 ms,
                                      /*       chorus  chorus   filter
       input  output  fbcoef  ffcoef   gain     rate   depth     coef   */
           0,  179 ms, 12000,      0, 0x7fff,      0,      0,      0
};

s32 CHORUS_PARAMS[10] = {
    /* sections	   length */
          1,        20 ms,
                                      /*       chorus  chorus   filter
       input  output  fbcoef  ffcoef   gain     rate   depth     coef   */
	  0,   5 ms, 0x4000,      0,  0x7fff,   7600,   700,      0
};

s32 FLANGE_PARAMS[10] = {
    /* sections	   length */
          1,        20 ms,
                                      /*       chorus  chorus   filter
       input  output  fbcoef  ffcoef   gain     rate   depth     coef   */
	   0,   5 ms,      0, 0x5fff, 0x7fff,    380,   500,      0
};

s32 NULL_PARAMS[10] = {
    0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

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

GLOBAL_ASM("lib/asm/non_matchings/alFxNew/alFxNew.s")

void alEnvmixerNew(ALEnvMixer *e, s32 arg1) {
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

void alLoadNew(ALLoadFilter *arg0, s32 (*arg1)(s32*), s32 arg2) {
    alFilterNew(arg0, &alLoadPull, &alLoadParam, 0);
    arg0->state = alHeapDBAlloc(0, 0, arg2, 1, 0x20);
    arg0->lstate = alHeapDBAlloc(0, 0, arg2, 1, 0x20);
    arg0->dma = arg1(&arg0->dmaState);
    arg0->lastsam = 0;
    arg0->first = 1;
    arg0->memin = 0;
}

void alResampleNew(ALResampler *r, ALHeap *hp) {
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

void alAuxBusNew(ALAuxBus *m, void *sources, s32 maxSources) {
    alFilterNew(m, &alAuxBusPull, &alAuxBusParam, 6);
    m->sourceCount = 0;
    m->maxSources = maxSources;
    m->sources = sources;
}

void alMainBusNew(ALMainBus *m, void *sources, s32 maxSources) {
    alFilterNew(m, &alMainBusPull, &alMainBusParam, 7);
    m->sourceCount = 0;
    m->maxSources = maxSources;
    m->sources = sources;
}

void alSaveNew(ALSave *f) {
    alFilterNew(f, &alSavePull, &alSaveParam, AL_SAVE);
    f->dramout = 0;
    f->first = 1;
}
