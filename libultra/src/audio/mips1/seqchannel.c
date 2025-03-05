#include <libaudio.h>

void alSeqChOff(ALSeqPlayer *seqp, u8 chan) {
    ALEvent evt;

    evt.type = AL_SEQP_MIDI_EVT;
    evt.msg.midi.ticks  = 0;
    evt.msg.midi.status = AL_MIDI_ControlChange;
    evt.msg.midi.byte1  = AL_MIDI_UNK_6A;
    evt.msg.midi.byte2  = chan;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}

void alSeqChOn(ALSeqPlayer *seqp, u8 chan) {
    ALEvent evt;

    evt.type = AL_SEQP_MIDI_EVT;
    evt.msg.midi.ticks  = 0;
    evt.msg.midi.status = AL_MIDI_ControlChange;
    evt.msg.midi.byte1  = AL_MIDI_UNK_6C;
    evt.msg.midi.byte2  = chan;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
