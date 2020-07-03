/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80065F10 */

#include "types.h"
#include "macros.h"

extern s32 D_800DD434;
extern s32 D_800DD438;

GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006F510.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006F53C.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006F564.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006F5E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006F64C.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006F6EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006F768.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006F870.s")

void set_rng_seed(s32 arg0) {
    D_800DD434 = arg0;
}

void save_rng_seed(s32 arg0) {
    arg0 = D_800DD434;
    D_800DD438 = arg0;
}

void load_rng_seed(s32 arg0) {
    arg0 = D_800DD438;
    D_800DD434 = arg0;
}

s32 get_rng_seed(void) {
    return D_800DD434;
}

GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006F94C.s")



GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006F9B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006FB60.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006FC30.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006FE04.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006FE30.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8006FE74.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_80070130.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_800701E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_80070320.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_800703D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_80070490.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_800704F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_800705F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_80070638.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8007066C.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_800706BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_800706C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_80070750.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_800707C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_800707F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_8007082C.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_80070890.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_80070A2C.s")
GLOBAL_ASM("asm/non_matchings/unknown_070110/func_80070B04.s")
