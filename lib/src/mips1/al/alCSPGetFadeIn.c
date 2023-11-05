/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80063C00 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

u8 alCSPGetFadeIn(ALCSPlayer *seqp, u8 chan) {
    return ((ALChanState_Custom*)seqp->chanState)[chan].fade;
}
