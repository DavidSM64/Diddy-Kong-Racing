/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065130 */

#include "types.h"
#include "macros.h"

/************ .rodata ************/

// In __timeToSamplesNoRound
const DoubleLiteral D_800E6EC0 = { 1000000.0 };

/*********************************/

GLOBAL_ASM("asm/non_matchings/unknown_065D30/alSynNew.s")
GLOBAL_ASM("asm/non_matchings/unknown_065D30/alAudioFrame.s")
GLOBAL_ASM("asm/non_matchings/unknown_065D30/__allocParam.s")
GLOBAL_ASM("asm/non_matchings/unknown_065D30/__freeParam.s")
GLOBAL_ASM("asm/non_matchings/unknown_065D30/__collectPVoices.s")
GLOBAL_ASM("asm/non_matchings/unknown_065D30/__freePVoices.s")
GLOBAL_ASM("asm/non_matchings/unknown_065D30/__timeToSamplesNoRound.s")
GLOBAL_ASM("asm/non_matchings/unknown_065D30/__timeToSamples.s")
GLOBAL_ASM("asm/non_matchings/unknown_065D30/__nextSampleTime.s")
