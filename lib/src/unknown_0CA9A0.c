/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CA0B0 */

#include "types.h"
#include "macros.h"

/************ .rodata ************/

const char D_800E9560[] = "samples >= 0";
const char D_800E9570[] = "env.c";
const char D_800E9578[] = "samples <= AL_MAX_RSP_SAMPLES";
const char D_800E9598[] = "env.c";
const char D_800E95A0[] = "source";
const char D_800E95A8[] = "env.c";

// Jump table in alEnvMixerPull
const u32 D_800E95B0[] = {
    0x800CA870, 0x800CA8C4, 0x800CA8C4, 0x800CA8C4, 
    0x800CA8C4, 0x800CA8C4, 0x800CA8C4, 0x800CA8C4, 
    0x800CA8C4, 0x800CA8C4, 0x800CA8C4, 0x800CA460, 
    0x800CA460, 0x800CA22C, 0x800CA7A8, 0x800CA828, 
    0x800CA460
};

const DoubleLiteral D_800E95F8 = { 65535.0 };

// Jump table in alResampleParam
const u32 D_800E9600[] = {
    0x800CC0C0, 0x800CC150, 0x800CC150, 0x800CC0C8, 
    0x800CC150, 0x800CC150, 0x800CC134, 0x800CC144, 
    0x800CC104
};

const DoubleLiteral D_800E9628 = { 1.99996 };
const FloatLiteral D_800E9630 = { 1.99996f };

/*********************************/

GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alFilterNew.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alEnvMixerPull.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alEnvmixerParam.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/func_800CAC5C.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/func_800CB2D4.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/func_800CB498.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alLoadParam.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/D_800CB714.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/func_800CBAC0.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alLoadPull.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alResampleParam.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CA9A0/alResamplePull.s")
