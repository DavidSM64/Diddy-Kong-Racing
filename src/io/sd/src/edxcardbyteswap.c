/* RAM_POS: auto if (defined(ENABLE_IO) && defined(ENABLE_LIBCART)) */

#include "../cart.h"
#include "cartint.h"
#include "edx.h"

int edx_card_byteswap(int flag)
{
    __cart_acs_get();
    __cart_wr(EDX_SYS_CFG_REG, flag ?
        (EDX_CFG_SDRAM_ON|EDX_CFG_BYTESWAP) : (EDX_CFG_SDRAM_ON)
    );
    __cart_acs_rel();
    return 0;
}
