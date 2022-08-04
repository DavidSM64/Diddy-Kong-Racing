/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065B20 */

#include "alSynStartVoiceParams.h"

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

ALParam *__allocParam();

void alSynSetPan(ALSynth *synth, ALVoice *v, u8 pan) {
    ALParam  *update;
    ALFilter *f;

    if (v->pvoice) {
        update = __allocParam();

        if(update != NULL) {
            update->delta  = synth->paramSamples + v->pvoice->offset;
            update->type   = AL_FILTER_SET_PAN;
            update->data.i = modify_panning(pan);
            update->next   = 0;

            f = v->pvoice->channelKnob;
            (*f->setParam)(f, AL_FILTER_ADD_UPDATE, update);  
        }        
    }
}
