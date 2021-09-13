/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CD600 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"
#include "../src/memory.h"

s32 D_800E38D0 = 0;

// Ok, so I completely gave up on the rest of these bss variables.
// This is probably not the right place for them, but we can always 
// fix that later. ¯\_(ツ)_/¯

s32 D_8012CE20[2];
s32 D_8012CE28[6];
s32 __osEepPifRam[15];     
s32 D_8012CE7C;     
s32 viThread[172];    
s32 viEventQueue[6];   
s32 viEventBuf[6]; 
s32 viRetraceMsg[6];
s32 viCounterMsg[6];
s32 D_8012D190[4];     
s32 D_8012D1A0[16];     
s32 D_8012D1E0[2];     
s32 piAccessQueue[6];  
OSTimer D_8012D200;
s32 __osCurrentTime;
s32 D_8012D224;     
s32 __osBaseCounter;
s32 D_8012D22C;     
s32 D_8012D230[4];     
s32 D_8012D240[108];     
MemoryPoolSlot *gMainMemoryPool;    

GLOBAL_ASM("lib/asm/non_matchings/unknown_0CE200/__osSiCreateAccessQueue.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CE200/__osSiGetAccess.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CE200/__osSiRelAccess.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CE200/__osSiRawStartDma.s")
