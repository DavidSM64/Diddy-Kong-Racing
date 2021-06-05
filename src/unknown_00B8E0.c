/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8000ACE0 */

#include "types.h"
#include "macros.h"

/************ .rodata ************/

const char D_800E4F30[] = "Exceeded voice limit of %d (%d)\n";

/*********************************/

GLOBAL_ASM("asm/non_matchings/unknown_005740/__initFromBank.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__setInstChanState.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__resetPerfChanState.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__initChanState.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__seqpStopOsc.s")

/* Unknown Size */
typedef struct unk8000B010 {
    u8 unk00[0x70];
    s8 unk70;
} unk8000B010;

void func_8000B010(unk8000B010 *arg0, s8 arg1) {
    arg0->unk70 = arg1;
}

