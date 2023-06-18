/* RAM_POS: auto if (defined(ENABLE_IO) && defined(ENABLE_LIBCART)) */

#include "../cart.h"
#include "cartint.h"

int cart_card_byteswap(int flag)
{
    static int (*const card_byteswap[CART_MAX])(int flag) =
    {
        ci_card_byteswap,
        edx_card_byteswap,
        ed_card_byteswap,
        sc_card_byteswap,
    };
    if (cart_type < 0) return -1;
    return card_byteswap[cart_type](flag);
}
