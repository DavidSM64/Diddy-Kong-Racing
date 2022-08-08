/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065900 */

#include "alSynStartVoiceParams.h"

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

Acmd *alAuxBusPull(void *filter, s16 *outp, s32 outCount, s32 sampleOffset, Acmd *p) {
    Acmd     *ptr = p;
    ALAuxBus *m = (ALAuxBus *)filter;
    ALFilter **sources = m->sources;
    s32         i;
    aClearBuffer(ptr++, AL_AUX_L_OUT, outCount<<1);
    aClearBuffer(ptr++, AL_AUX_R_OUT, outCount<<1);

    for (i = 0; i < m->sourceCount; i++) {
        ptr = (sources[i]->handler)(sources[i], outp, outCount, sampleOffset, ptr);
    }
    
    return ptr;
}

s32 alAuxBusParam(void *filter, s32 paramID, void *param) {
    ALAuxBus     *m = (ALAuxBus *) filter;
    ALFilter    **sources = m->sources;
    s32 i;
    
    switch (paramID) {
        case AL_FILTER_ADD_SOURCE:
            sources[m->sourceCount++] = (ALFilter *) param;
            break;
        case 0x11:
            for (i = 0; i < m->sourceCount; i++) {
                if ((ALFilter *) param == sources[i]) {
                    m->sourceCount--;
                    sources[i] = sources[m->sourceCount];
                }
            }
            break;
    }

    return 0;
    
}

void func_80065A80(ALSynth *arg0, PVoice *arg1, s16 arg2) {
    if (arg2 != arg1->unkDC) {
        alAuxBusParam(&arg0->auxBus[arg1->unkDC], 17, &arg1->envmixer);
        alAuxBusParam(&arg0->auxBus[arg2], 2, &arg1->envmixer);
        arg1->unkDC = arg2;
    }
}
