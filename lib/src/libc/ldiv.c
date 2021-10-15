/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D7470 */

#include "macros.h"
#include <stdlib.h>
#ifdef NON_MATCHING
//This needs to be compiled with mips3, which isn't yet supported
ldiv_t ldiv(long num, long denom)
{
    ldiv_t ret;

    ret.quot = num / denom;
    ret.rem = num - denom * ret.quot;
    if (ret.quot < 0 && ret.rem > 0)
    {
        ret.quot++;
        ret.rem -= denom;
    }

    return ret;
}

lldiv_t lldiv(long long num, long long denom)
{
    lldiv_t ret;

    ret.quot = num / denom;
    ret.rem = num - denom * ret.quot;
    if (ret.quot < 0 && ret.rem > 0)
    {
        ret.quot++;
        ret.rem -= denom;
    }

    return ret;
}
#else
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/lldiv.s")
GLOBAL_ASM("lib/asm/non_matchings/unknown_0D3020/ldiv.s")
#endif
