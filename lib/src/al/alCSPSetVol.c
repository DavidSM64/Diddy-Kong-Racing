/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C7850 */

#include "audio_internal.h"

void alCSPSetVol(ALCSPlayer *seqp, s16 vol) {
    ALEvent       evt;

    evt.type            = AL_SEQP_VOL_EVT;
    evt.msg.spvol.vol   = vol;
    
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}
