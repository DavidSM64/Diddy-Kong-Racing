/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80063BA0 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta); //unknown_0C9C90

void func_80063BA0(ALCSPlayer *seqp, u8 arg1, u8 arg2) {
    ALEvent evt;
    evt.type = 2;
    evt.msg.midi.ticks = 0;
    evt.msg.midi.status = arg1 | 0xB0;
    evt.msg.midi.byte1 = 8;
    evt.msg.midi.byte2 = arg2;
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
