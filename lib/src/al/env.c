/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CA0D0 */

/*====================================================================
 * envmixer.c
 *
 * Copyright 1993, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/

#include "types.h"
#include "macros.h"
#include "audio_internal.h"
#include "audio_assert.h"

// TODO: these come from headers
#ident "$Revision: 1.17 $"

#ifdef AUD_PROFILE
extern u32 cnt_index, env_num, env_cnt, env_max, env_min, lastCnt[];
extern u32 rate_num, rate_cnt, rate_max, rate_min;
extern u32 vol_num, vol_cnt, vol_max, vol_min;
#endif

#define EQPOWER_LENGTH 128
static s16 eqpower[ EQPOWER_LENGTH ] = {
    32767,  32764,  32757,  32744,  32727,  32704,
    32677,  32644,  32607,  32564,  32517,  32464,
    32407,  32344,  32277,  32205,  32127,  32045,
    31958,  31866,  31770,  31668,  31561,  31450,
    31334,  31213,  31087,  30957,  30822,  30682,
    30537,  30388,  30234,  30075,  29912,  29744,
    29572,  29395,  29214,  29028,  28838,  28643,
    28444,  28241,  28033,  27821,  27605,  27385,
    27160,  26931,  26698,  26461,  26220,  25975,
    25726,  25473,  25216,  24956,  24691,  24423,
    24151,  23875,  23596,  23313,  23026,  22736,
    22442,  22145,  21845,  21541,  21234,  20924,
    20610,  20294,  19974,  19651,  19325,  18997,
    18665,  18331,  17993,  17653,  17310,  16965,
    16617,  16266,  15913,  15558,  15200,  14840,
    14477,  14113,  13746,  13377,  13006,  12633,
    12258,  11881,  11503,  11122,  10740,  10357,
    9971,   9584,   9196,   8806,   8415,   8023,
    7630,   7235,   6839,   6442,   6044,   5646,
    5246,   4845,   4444,   4042,   3640,   3237,
    2833,   2429,   2025,   1620,   1216,    810,
    405,      0
};

extern	f64	__pow(f64, f64);

/*
 * prototypes for private enveloper functions
 */
static  Acmd *_pullSubFrame(void *filter, s16 *inp, s16 *outp, s32 outCount,
                            s32 sampleOffset, Acmd *p) ;
static  s16 _getRate(f64 vol, f64 tgt, s32 count, u16* ratel);

static f32 _getVol(f32 ivol, s32 samples, s16 ratem, u16 ratel);
extern u32 osVirtualToPhysical(void *);

/***********************************************************************
 * Enveloper filter public interfaces
 ***********************************************************************/
Acmd *alEnvmixerPull(void *filter, UNUSED s16 *outp, s32 outCount, s32 sampleOffset,
                     Acmd *p) 
{
    Acmd        *ptr = p;
    ALEnvMixer	*e = (ALEnvMixer *)filter;
    s16         inp;
    s32         lastOffset;
    s32         thisOffset = sampleOffset;
    s32         samples;
    s16         loutp = 0;
    s32         fVol;
    ALParam     *thisParam;
    
#ifdef AUD_PROFILE
    lastCnt[++cnt_index] = osGetCount();
#endif

    /*
     * Force the input to be the resampler output
     */
    inp = AL_RESAMPLER_OUT;

    while (e->ctrlList != 0) {
            
        lastOffset = thisOffset;
        thisOffset = e->ctrlList->delta;
        samples    = thisOffset - lastOffset;
        if (samples > outCount)
            break;
        
#ifdef _DEBUG
        assert(samples >= 0);
        assert(samples <= AL_MAX_RSP_SAMPLES);
#else
        // Something must have gone wrong when compiling this file, and the asserts got left in.
        if (samples >= 0) {} 
        else { assert_stub("samples >= 0", "env.c", 104); }
        if (samples <= AL_MAX_RSP_SAMPLES) {} 
        else { assert_stub("samples <= AL_MAX_RSP_SAMPLES", "env.c", 105); }
#endif

        
        switch (e->ctrlList->type) {
          case (AL_FILTER_START_VOICE_ALT):
              {                  
                  ALStartParamAlt *param = (ALStartParamAlt *)e->ctrlList;
                  ALFilter     *f = (ALFilter *) e;
                  s32 tmp;
                  
                  if (param->unity) {
                      (*e->filter.setParam)(&e->filter,
                                            AL_FILTER_SET_UNITY_PITCH, 0);
                  }
                  
                  (*e->filter.setParam)(&e->filter, AL_FILTER_SET_WAVETABLE,
                                        param->wave);
                  (*e->filter.setParam)(&e->filter, AL_FILTER_START, 0);

                  e->first  = 1;

                  e->delta  = 0;
                  e->segEnd = param->samples;

                  tmp = ((s32)param->volume + (s32)param->volume) / 2; //Diff
                  e->volume = (s16) tmp;
                  e->pan    = param->pan;
                  e->dryamt = eqpower[param->fxMix];
                  e->wetamt = eqpower[EQPOWER_LENGTH - param->fxMix - 1];
                  
                  if (param->samples) {
                      e->cvolL  = 1;
                      e->cvolR  = 1;
                  } else {
                      /*
                       * Attack time is zero. Simply set the
                       * volume. We don't want an attack segment.
                       */
                      e->cvolL = (e->volume * eqpower[e->pan]) >> 15;
                      e->cvolR = (e->volume *
                                  eqpower[EQPOWER_LENGTH - e->pan - 1]) >> 15;
                  }

                  if (f->source) {
                      union {
                          f32 f;
                          s32 i;
                      } data;                    
                      data.f = param->pitch;
                      (*f->source->setParam)(f->source, AL_FILTER_SET_PITCH,
                                            (void *)data.i);
                  }
                  
              }
              
              break;
                
          case (AL_FILTER_SET_FXAMT):
          case (AL_FILTER_SET_PAN):
          case (AL_FILTER_SET_VOLUME):
	      ptr = _pullSubFrame(e, &inp, &loutp, samples, sampleOffset, ptr);
          e->delta += samples; //Diff
              if (e->delta >= e->segEnd){
                  /*
                   * We should have reached our target, calculate
                   * target in case e->segEnd was 0
                   */
                  e->ltgt = (e->volume * eqpower[e->pan]) >> 15;
                  e->rtgt = (e->volume *
                             eqpower[EQPOWER_LENGTH - e->pan - 1]) >> 15;
                  e->delta = e->segEnd;   /* To prevent overflow */
                  e->cvolL = e->ltgt;
                  e->cvolR = e->rtgt;
              } else {
                  /* 
                   * Estimate the current volume
                   */
                  e->cvolL = _getVol(e->cvolL, e->delta, e->lratm, e->lratl);
                  e->cvolR = _getVol(e->cvolR, e->delta, e->rratm, e->rratl);
              }
    
              /*
               * We can't have volume of zero, because the envelope
               * would never go anywhere from there
               */
              if( e->cvolL == 0 ) e->cvolL = 1;
              if( e->cvolR == 0 ) e->cvolR = 1;

              if (e->ctrlList->type == AL_FILTER_SET_PAN)

                  /*
                   * This should result in a change to the current
                   * segment rate and target
                   */
                  e->pan = (s16) e->ctrlList->data.i;

              if (e->ctrlList->type == AL_FILTER_SET_VOLUME){

                  /*
                   * Switching to a new segment
                   */
                  e->delta = 0;
                
                  /*
                   * Map volume non-linearly to give something close to
                   * loudness
                   */
                  fVol = (e->ctrlList->data.i);
                  fVol = (fVol+fVol)/2; //Diff
                  e->volume = (s16) fVol;
                
                  e->segEnd = e->ctrlList->moredata.i;

              }
            
              if (e->ctrlList->type == AL_FILTER_SET_FXAMT){
                  e->dryamt = eqpower[e->ctrlList->data.i];
                  e->wetamt = eqpower[EQPOWER_LENGTH - e->ctrlList->data.i - 1];
              }
            
              /*
               * Force a volume update
               */
              e->first = 1;
              break;

          case (AL_FILTER_START_VOICE):
              {
                  ALStartParam *p = (ALStartParam *)e->ctrlList;
                  
                  /*
                   * Changing to PLAYING (since the previous state was
                   * persumable STOPPED, we'll just bump the output
                   * pointer rather than pull a subframe of zeros).
                   */
                  if (p->unity) {
                      (*e->filter.setParam)(&e->filter,
                                            AL_FILTER_SET_UNITY_PITCH, 0);
                  }
                  
                  (*e->filter.setParam)(&e->filter, AL_FILTER_SET_WAVETABLE,
                                        p->wave);
                  (*e->filter.setParam)(&e->filter, AL_FILTER_START, 0);
              }
              break;
              
          case (AL_FILTER_STOP_VOICE):
              {
                  /*
                   * Changing to STOPPED and reset the filter
                   */
		  ptr = _pullSubFrame(e, &inp, &loutp, samples, sampleOffset, ptr);
		  (*e->filter.setParam)(&e->filter, AL_FILTER_RESET, 0);
              }
              break;

          case (AL_FILTER_FREE_VOICE):
              {                  
                  ALSynth *drvr = &alGlobals->drvr;
                  ALFreeParam *param = (ALFreeParam *)e->ctrlList;
                  param->pvoice->offset = 0;
                  __freePVoices(drvr, (PVoice *)param->pvoice);
              }
              break;
              
          default:
              /*
               * Pull the reuired number of samples and then pass the message
               * on down the chain
               */
	      ptr = _pullSubFrame(e, &inp, &loutp, samples, sampleOffset, ptr);
          e->delta += samples; //Diff
              (*e->filter.setParam)(&e->filter, e->ctrlList->type,
                                    (void *) e->ctrlList->data.i);
              break;
        }
        loutp  += (samples<<1);
        outCount -= samples;

        /*
         * put the param record back on the free list
         */
        thisParam = e->ctrlList;
        e->ctrlList = e->ctrlList->next;
        if (e->ctrlList == 0)
            e->ctrlTail = 0;
        
        __freeParam(thisParam);
        
    }

    //Diff
    if (e->motion == 1) {
        ptr = _pullSubFrame(e, &inp, &loutp, outCount, sampleOffset, ptr);
        e->delta += outCount; //Diff
    }    

    /*
     * Prevent overflow in e->delta
     */
    
    if (e->delta > e->segEnd)
        e->delta = e->segEnd;

#ifdef AUD_PROFILE
    PROFILE_AUD(env_num, env_cnt, env_max, env_min);
#endif
    return ptr;
}

s32
alEnvmixerParam(void *filter, s32 paramID, void *param)
{
    ALFilter      *f = (ALFilter *) filter;
    ALEnvMixer	*e = (ALEnvMixer *) filter;
    
    switch (paramID) {

      case (AL_FILTER_ADD_UPDATE):
          if (e->ctrlTail) {
              e->ctrlTail->next = (ALParam *)param;
          } else {
              e->ctrlList = (ALParam *)param;
          }            
          e->ctrlTail = (ALParam *)param;
          
          break;
        
      case (AL_FILTER_RESET):
          e->first = 1;
          e->motion = AL_STOPPED;
          e->volume = 1;
          if (f->source)
              (*f->source->setParam)(f->source, AL_FILTER_RESET, param);
          break;

      case (AL_FILTER_START):
          e->motion = AL_PLAYING;
          if (f->source)
              (*f->source->setParam)(f->source, AL_FILTER_START, param);
          break;
            
      case (AL_FILTER_SET_SOURCE):
          f->source = (ALFilter *) param;
          break;

      default:
          if (f->source)
              (*f->source->setParam)(f->source, paramID, param);
    }
    return 0;
}

static
Acmd* _pullSubFrame(void *filter, s16 *inp, s16 *outp, s32 outCount,
                    s32 sampleOffset, Acmd *p) 
{
    Acmd        *ptr = p;
    ALEnvMixer	*e = (ALEnvMixer *)filter;
    ALFilter      *source= e->filter.source;

    /* filter must be playing and request non-zero output samples to pull. */
    if (!outCount) //Diff
        return ptr;

    /*
     * ask all filters upstream from us to build their command
     * lists.
     */
#ifdef _DEBUG
    assert(source);
#else
    // Something must have gone wrong when compiling this file, and the asserts got left in.
    if (source) {}
    else { assert_stub("source", "env.c", 373); }
#endif
    
    ptr = (*source->handler)(source, inp, outCount, sampleOffset, p);

    /*
     * construct our portion of the command list
     */
    aSetBuffer(ptr++, A_MAIN, *inp, AL_MAIN_L_OUT + *outp, outCount<<1);
    aSetBuffer(ptr++, A_AUX, AL_MAIN_R_OUT + *outp, AL_AUX_L_OUT + *outp,
	       AL_AUX_R_OUT + *outp);

    if (e->first){
	e->first = 0;

        /*
         * Calculate derived parameters
         */
        e->ltgt = (e->volume * eqpower[e->pan]) >> 15;
        e->lratm = _getRate((f64)e->cvolL, (f64)e->ltgt,
                            e->segEnd, &(e->lratl));
        e->rtgt = (e->volume *
                   eqpower[EQPOWER_LENGTH - e->pan - 1]) >> 15;
        e->rratm = _getRate((f64)e->cvolR, (f64)e->rtgt, e->segEnd,
                            &(e->rratl));

        aSetVolume(ptr++, A_LEFT | A_VOL, e->cvolL, 0, 0);
        aSetVolume(ptr++, A_RIGHT | A_VOL, e->cvolR, 0, 0);
	aSetVolume(ptr++, A_LEFT  | A_RATE, e->ltgt, e->lratm, e->lratl);
	aSetVolume(ptr++, A_RIGHT | A_RATE, e->rtgt, e->rratm, e->rratl);
	aSetVolume(ptr++, A_AUX, e->dryamt, 0, e->wetamt);
	aEnvMixer (ptr++, A_INIT | A_AUX, osVirtualToPhysical(e->state));
    }
    else
	aEnvMixer(ptr++, A_CONTINUE | A_AUX, osVirtualToPhysical(e->state));

    /*
     * bump the input buffer pointer
     */

    *inp += (outCount<<1);
    //e->delta += outCount; //Diff

    return ptr;
}

#define EXP_MASK  0x7f800000
#define MANT_MASK 0x807fffff

f64
_frexpf(f64 value, s32 *eptr)
{
    f64 absvalue;

    *eptr = 0;
    if (value == 0.0) /* nothing to do for zero */
        return (value);
    absvalue = (value > 0.0) ? value : -value;
    for ( ; absvalue >= 1.0; absvalue *= 0.5)
        ++*eptr;
    for ( ; absvalue < 0.5; absvalue += absvalue)
        --*eptr;
    return (value > 0.0 ? absvalue : -absvalue);
}

f64
_ldexpf(f64 in, s32 ex)
{
    s32 exp;
    
    if ( ex ) {
	exp = 1 << ex;
	in *= (f64)exp;
    }

    return ( in );
}

/*
    _getRate()  --  This function determines how to go from the
		    current volume level (vol) to the target
		    volume level (tgt) in some number of steps
		    (count).  Two values are returned that are
		    used as multipliers to incrementally scale
		    the volume.  Some tricky math is used and
		    is explained below.
		    RWW 28jun95
*/

static
s16 _getRate(f64 vol, f64 tgt, s32 count, u16* ratel)
{
    s16         s;    
    f64         a;
    
    if (count == 0){
        if (tgt >= vol){
            *ratel = 0xffff;
            return 0x7fff;
        }
        else{
            *ratel = 0;
            return -0x8000; //Diff
        }
    }

    a = (tgt - vol) / (f32)count;
    a *= 8;
    if (a < 0.0) {
        a -= 1.0;
    }
    s = (s16) a;
    *ratel = (s16)((0xffff * (a - (f32) s)));
    
    return (s16)a;
}

static
f32 _getVol(f32 ivol, s32 samples, s16 ratem, u16 ratel) {
    f32 r;
    r = ((ratem<<16) + (f32) ratel)/65536.0;
    ivol += (r * samples) / 8.0;
    return ivol;
}
