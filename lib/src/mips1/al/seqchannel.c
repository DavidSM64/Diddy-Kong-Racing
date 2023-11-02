/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80063AF0 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

void alSeqChOff(ALSeqPlayer *seqp, u8 chan) {
    ALEvent evt;

    evt.type = AL_SEQP_MIDI_EVT;
    evt.msg.midi.ticks  = 0;
    evt.msg.midi.status = AL_MIDI_ControlChange;
    evt.msg.midi.byte1  = 0x6A;
    evt.msg.midi.byte2  = chan;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}

void alSeqChOn(ALSeqPlayer *seqp, u8 chan) {
    ALEvent evt;

    evt.type = AL_SEQP_MIDI_EVT;
    evt.msg.midi.ticks  = 0;
    evt.msg.midi.status = AL_MIDI_ControlChange;
    evt.msg.midi.byte1  = 0x6C;
    evt.msg.midi.byte2  = chan;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
