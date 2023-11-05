/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80063BA0 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

void alCSPSetFadeIn(ALSeqPlayer *seqp, u8 chan, ALPan pan) {
    ALEvent       evt;

    evt.type            = AL_SEQP_MIDI_EVT;
    evt.msg.midi.ticks  = 0;
    evt.msg.midi.status = AL_MIDI_ControlChange | chan;
    evt.msg.midi.byte1  = AL_SEQP_PROG_EVT;
    evt.msg.midi.byte2  = pan;

    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
