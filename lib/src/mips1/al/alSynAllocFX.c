/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065860 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

#ifdef NON_EQUIVALENT
// This is very close to matching.
ALFxRef *alSynAllocFX(ALSynth *s, s16 bus, ALSynConfig *c, ALHeap *hp)
{
    alFxNew(s->auxBus[bus].fx, c, bus, hp);
    alFxParam(s->auxBus[bus].fx, AL_FILTER_SET_SOURCE,
                  &s->auxBus[bus]);
    alMainBusParam(s->mainBus, AL_FILTER_ADD_SOURCE, s->auxBus[bus].fx);

    return (ALFxRef)(&s->auxBus[bus].fx[0]);
}
#else
GLOBAL_ASM("lib/asm/non_matchings/alSynAllocFX/alSynAllocFX.s")
#endif
