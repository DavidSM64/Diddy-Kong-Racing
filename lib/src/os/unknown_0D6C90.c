/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D6090 */

#include "macros.h"
#include "libultra_internal.h"
#include "viint.h"

struct __osThreadTail
{
    OSThread *next;
    OSPri priority;
} __osThreadTail;

struct __osThreadTail __osThreadTail = {0, -1};
OSThread *__osRunQueue = &__osThreadTail.next;
OSThread *__osActiveQueue = &__osThreadTail.next;

extern OSThread *__osRunningThread = NULL;
extern OSThread *D_800E4894 = NULL; // __osFaultedThread

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/__osViSwapContext.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/__osSpGetStatus.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/__osSpSetPc.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/__osSpRawStartDma.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/__osSpDeviceBusy.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/__osResetGlobalIntMask.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/osEPiRawWriteIo.s")
