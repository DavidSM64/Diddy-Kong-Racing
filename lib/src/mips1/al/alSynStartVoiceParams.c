/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065BD0 */

#include "alSynStartVoiceParams.h"

s16 gStereoPanMode = STEREO;

void set_stereo_pan_mode(s32 panMode) {
    gStereoPanMode = panMode;
}

/* Unused. */
s16 get_stereo_pan_mode(void) {
    return gStereoPanMode;
}

s32 modify_panning(s32 pan) {
    switch(gStereoPanMode) {
        case STEREO:
            return pan;
        case HEADPHONES:
            pan = ((pan - 64) >> 1) + 64;
            return pan;
        case MONO:
        default: 
            return 64;
    }
}

void alSynStartVoiceParams(ALSynth *s, ALVoice *v, ALWaveTable *w, f32 pitch, s16 vol, ALPan pan, u8 fxmix, ALMicroTime t) {
    ALStartParamAlt *update;
    ALFilter *f;
    
    if (v->pvoice) {
        update = (ALStartParamAlt *)__allocParam();
        if (update != NULL) {
            update->delta  = s->paramSamples + v->pvoice->offset;
            update->next = 0;
            update->type = AL_FILTER_START_VOICE_ALT;
            update->unity  = v->unityPitch;
            update->pan = modify_panning(pan);
            update->volume = vol;
            update->fxMix = fxmix;
            update->pitch = pitch;
            update->samples = __timeToSamples(s, t);
            update->wave = w;
            f = v->pvoice->channelKnob;
            (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);
        }
    }
}
