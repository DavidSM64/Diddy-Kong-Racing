/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D6050 */

#include "macros.h"
#include "libultra_internal.h"
#include "viint.h"

GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/__osDpDeviceBusy.s")

__OSViContext *__osViGetCurrentContext(void){
    return __osViCurr;
}
