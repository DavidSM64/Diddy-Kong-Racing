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

/************ .rodata ************/

const FloatLiteral D_800E4BF0 = { 10000.0f };
const DoubleLiteral D_800E4BF8 = { 0.4 };
const FloatLiteral D_800E4C00 = { 10000.0f };
const DoubleLiteral D_800E4C08 = { 0.05 };
const DoubleLiteral D_800E4C10 = { 0.95 };
const DoubleLiteral D_800E4C18 = { 0.13 };
const DoubleLiteral D_800E4C20 = { 0.3 };
const DoubleLiteral D_800E4C28 = { 0.02 };
const DoubleLiteral D_800E4C30 = { 0.01 };
const FloatLiteral D_800E4C38 = { 0.4f };
const DoubleLiteral D_800E4C40 = { 0.005 };
const DoubleLiteral D_800E4C48 = { -0.1 };
const DoubleLiteral D_800E4C50 = { 0.05 };
const DoubleLiteral D_800E4C58 = { 0.95 };
const DoubleLiteral D_800E4C60 = { 0.3 };
const DoubleLiteral D_800E4C68 = { 6.5534 };
const FloatLiteral D_800E4C70 = { 6.5534f };
const FloatLiteral D_800E4C74 = { 10000.0f };
const FloatLiteral D_800E4C78 = { 10000.0f };
const DoubleLiteral D_800E4C80 = { 0.05 };
const DoubleLiteral D_800E4C88 = { 0.95 };
const DoubleLiteral D_800E4C90 = { 6.5534 };
const FloatLiteral D_800E4C98 = { 6.5534f };
const DoubleLiteral D_800E4CA0 = { 1731.23404 };
const DoubleLiteral D_800E4CA8 = { 0.8 };
const FloatLiteral D_800E4CB0 = { 0.8f };
const DoubleLiteral D_800E4CB8 = { -0.8 };
const FloatLiteral D_800E4CC0 = { -0.8f };
const FloatLiteral D_800E4CC4 = { 2250000.0f };
const DoubleLiteral D_800E4CC8 = { 0.05 };
const FloatLiteral D_800E4CD0 = { 1500.0f };
const FloatLiteral D_800E4CD4 = { 0.05f };
const DoubleLiteral D_800E4CD8 = { 0.05 };
const FloatLiteral D_800E4CE0 = { 2250000.0f };
const DoubleLiteral D_800E4CE8 = { 0.8 };
const FloatLiteral D_800E4CF0 = { 1500.0f };
const FloatLiteral D_800E4CF4 = { 0.05f };
const DoubleLiteral D_800E4CF8 = { 0.001 };

const char D_800E4D00[] = "OUT OF AUDIO POINTS\n";
const char D_800E4D18[] = "amAudioLineAddVertex: Exceeded maximum number of lines (%d)\n";
const char D_800E4D58[] = "amAudioLineAddVertex: Exceeded maximum number of line vertices (%d)\n";
const char D_800E4DA0[] = "amReverbLineAddVertex: Exceeded maximum number of lines (%d)\n";
const char D_800E4DE0[] = "amReverbLineAddVertex: Exceeded maximum number of line vertices (%d)\n";
const char D_800E4E28[] = "Audio line definition error (less than 2 vertices on line %d)\n";
const char D_800E4E68[] = "Audio line definition error (line=%d, vertex=%d)\n";
const char D_800E4E9C[] = "Reverb line definition error (less than 2 vertices on line %d)\n";
const char D_800E4EDC[] = "Reverb line definition error (line=%d, vertex=%d)\n";

const FloatLiteral D_800E4F10 = { -100000.0f };
const FloatLiteral D_800E4F14 = { 999999.0f };
const DoubleLiteral D_800E4F18 = { -100000.0 };
const DoubleLiteral D_800E4F20 = { -100000.0 };

const u32 filePadding[2] = { 0, 0 }; // unknown_005740 needs to be split.

const char D_800E4F30[] = "Exceeded voice limit of %d (%d)\n";

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

