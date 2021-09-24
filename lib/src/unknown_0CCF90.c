/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CC390 */

#include "types.h"
#include "macros.h"
#include "ultra64.h"

GLOBAL_ASM("lib/asm/non_matchings/unknown_0CCF90/alMainBusParam.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CCF90/alMainBusPull.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CCF90/alSaveParam.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CCF90/alSavePull.s")

u64 osClockRate = OS_CLOCK_RATE;
u32 __osShutdown = 0;
u32 __OSGlobalIntMask = OS_IM_ALL;
s32 D_800E38B0 = 0; // 64DD flag? (Hints from SM64 code)

GLOBAL_ASM("lib/asm/non_matchings/unknown_0CCF90/osInitialize.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CCF90/osSetThreadPri.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CCF90/guPerspectiveF.s")
