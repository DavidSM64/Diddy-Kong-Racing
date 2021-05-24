/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80004B40 */

#include "types.h"
#include "macros.h"

/************ .data ************/

s8 D_800DC6D0 = 1; // Currently unknown, might be a u8.
s32 D_800DC6D4 = 0; // Currently unknown, might be a different type.
s32 D_800DC6D8 = 1; // Currently unknown, might be a different type.
s32 D_800DC6DC = 0; // Currently unknown, might be a different type.
s32 D_800DC6E0 = 0; // Currently unknown, might be a different type.

/*******************************/

/************ .bss ************/

extern s8 D_8011AC18;

/*******************************/

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80004B40.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800050D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80005254.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80005D08.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800063EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006AC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006BFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80006FC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80007FA4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008040.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008140.s")

void func_80008168(void) {
    D_8011AC18 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008174.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80008438.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800090C0.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800092A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009558.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800095E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800096D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800096F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000974C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800098A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009968.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_800099EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009AB4.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009B7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_80009D6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A2E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/func_8000A414.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__mapVoice.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__unmapVoice.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__lookupVoice.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__lookupSoundQuick.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__vsVol.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__vsDelta.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__vsPan.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__seqpReleaseVoice.s")
GLOBAL_ASM("asm/non_matchings/unknown_005740/__voiceNeedsNoteKill.s")
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

