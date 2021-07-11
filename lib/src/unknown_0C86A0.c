/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C7AA0 */

#include "types.h"
#include "macros.h"
#include "audio_internal.h"

GLOBAL_ASM("lib/asm/non_matchings/unknown_0C86A0/alCSeqSetLoc.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C86A0/alCSeqGetLoc.s")

GLOBAL_ASM("lib/asm/non_matchings/unknown_0C86A0/__getTrackByte.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C86A0/__readVarLen.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C86A0/__alCSeqGetTrackEvent.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C86A0/alCSeqNew.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C86A0/alCSeqNewMarker.s")

s32 alCSeqGetTicks(ALCSeq *seq)
{
    return seq->lastTicks; 
}

GLOBAL_ASM("lib/asm/non_matchings/unknown_0C86A0/alCSeqSecToTicks.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C86A0/alCSeqTicksToSec.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0C86A0/__alCSeqNextDelta.s")
