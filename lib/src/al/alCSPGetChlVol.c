/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C79A0 */

#include "audio_internal.h"

u8 alCSPGetChlVol(ALCSPlayer *seqp, u8 chan) {
    return seqp->chanState[chan].vol;
}
