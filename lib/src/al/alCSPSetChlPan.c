/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C78E0 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

void alCSPSetChlPan(ALCSPlayer *seqp, u8 chan, ALPan pan) {
    ALEvent       evt;

    evt.type            = AL_SEQP_MIDI_EVT;
    evt.msg.midi.ticks  = 0;
    evt.msg.midi.status = AL_MIDI_ControlChange | chan;
    evt.msg.midi.byte1  = AL_MIDI_PAN_CTRL;
    evt.msg.midi.byte2  = pan;
                    
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
