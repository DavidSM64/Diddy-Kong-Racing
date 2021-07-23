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

/* Size: 0x4C bytes */
typedef struct unk80065A80_arg0_34 {
    u8 pad0[0x4C];
} unk80065A80_arg0_34;

/* Unknown size */
typedef struct unk80065A80_arg0 {
    u8 pad0[0x34];
    unk80065A80_arg0_34 *unk34;
} unk80065A80_arg0;

/* Unknown size */
typedef struct unk80065A80_arg1 {
    u8 pad0[0x8C];
    s32 unk8C;
    u8 pad90[0x4C];
    u8 unkDC;
} unk80065A80_arg1;

void func_80065A80(unk80065A80_arg0 *arg0, unk80065A80_arg1 *arg1, s16 arg2) {
    if (arg2 != arg1->unkDC) {
        alAuxBusParam(&arg0->unk34[arg1->unkDC], 0x11, &arg1->unk8C);
        alAuxBusParam(&arg0->unk34[arg2], 2, &arg1->unk8C);
        arg1->unkDC = arg2;
    }
}
