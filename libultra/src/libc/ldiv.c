#include "os_version.h"
#include "stdlib.h"
#include "ultra64.h"

// TODO: these come from headers
#ident "$Revision: 1.34 $"
#ident "$Revision: 1.5 $"

ldiv_t ldiv(long num, long denom) {
    ldiv_t ret;

    ret.quot = num / denom;
    ret.rem = num - denom * ret.quot;

    if (ret.quot < 0 && ret.rem > 0) {
        ret.quot += 1;
        ret.rem -= denom;
    }

    return ret;
}

lldiv_t lldiv(long long num, long long denom) {
    lldiv_t ret;

    ret.quot = num / denom;
    ret.rem = num - denom * ret.quot;

    if (ret.quot < 0 && ret.rem > 0) {
        ret.quot += 1;
        ret.rem -= denom;
    }

    return ret;
}


#ifdef __GNUC__
u64 __lshrdi3(u64 u, unsigned int b) {
    return u >> b;
}

u64 __ashldi3(u64 u, unsigned int b) {
    return u << b;
}

s64 __ashrdi3(s64 u, unsigned int b) {
    return u >> b;
}
#endif