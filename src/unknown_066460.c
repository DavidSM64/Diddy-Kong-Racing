/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065860 */

#include "unknown_066460.h"

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

#if 1
    GLOBAL_ASM("asm/non_matchings/unknown_066460/alSynAllocFX.s")
#else
ALFxRef *alSynAllocFX(ALSynth *s, s16 bus, ALSynConfig *c, ALHeap *hp)
{
    alFxNew(&s->auxBus[bus].fx[0], c, hp);
    alFxParam(&s->auxBus[bus].fx[0], AL_FILTER_SET_SOURCE,
                  &s->auxBus[bus]);
    alMainBusParam(s->mainBus, AL_FILTER_ADD_SOURCE,&s->auxBus[bus].fx[0]);

    return (ALFxRef)(&s->auxBus[bus].fx[0]);
}
#endif