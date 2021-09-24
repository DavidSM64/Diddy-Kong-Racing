/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C79E0 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

void alCSPSetTempo(ALCSPlayer *seqp, s32 tempo) {
    ALEvent       evt;
    
    evt.type             = AL_SEQP_META_EVT;
    evt.msg.tempo.status = AL_MIDI_Meta;
    evt.msg.tempo.type   = AL_MIDI_META_TEMPO;
    evt.msg.tempo.byte1  = (tempo & 0xff0000)>>16;
    evt.msg.tempo.byte2  = (tempo & 0xff00)>>8;
    evt.msg.tempo.byte3  = tempo & 0xff;
    
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
