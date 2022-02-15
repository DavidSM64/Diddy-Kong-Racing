/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CE050 */

#include "types.h"
#include "macros.h"
#include "unknown_0CEC50.h"

//Takes a char pointer, the string to populate it with, and the length of that string.
//Example: 
//func_800CE050(&gameName, "DKRACING-ADV", strlen("DKRACING-ADV"));
GLOBAL_ASM("lib/asm/non_matchings/unknown_0CEC50/func_800CE050.s")
