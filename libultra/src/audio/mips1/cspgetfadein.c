#include <libaudio.h>

u8 alCSPGetFadeIn(ALCSPlayer *seqp, u8 chan) {
    return ((ALChanState_Custom*)seqp->chanState)[chan].fade;
}
