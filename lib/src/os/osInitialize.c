/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CC5A0 */

#include "types.h"
#include "macros.h"
#include "ultra64.h"

u64 osClockRate = OS_CLOCK_RATE;
u32 __osShutdown = 0;
u32 __OSGlobalIntMask = OS_IM_ALL;
s32 D_800E38B0 = 0; // 64DD flag? (Hints from SM64 code)

GLOBAL_ASM("lib/asm/non_matchings/unknown_0CCF90/osInitialize.s")
