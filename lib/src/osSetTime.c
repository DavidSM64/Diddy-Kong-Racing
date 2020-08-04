/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CD260 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

//GLOBAL_ASM("lib/asm/non_matchings/osSetTime_0CDE60/osSetTime.s")

void osSetTime(OSTime time){
    __osCurrentTime = time;
}