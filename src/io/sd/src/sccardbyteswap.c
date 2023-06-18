/* RAM_POS: auto if (defined(ENABLE_IO) && defined(ENABLE_LIBCART)) */

#include "../cart.h"
#include "cartint.h"
#include "sc.h"

int sc_card_byteswap(int flag)
{
    __cart_acs_get();
    __sc_sync();
    __cart_wr(SC_DATA1_REG, flag ? SC_SD_BYTESWAP_ON : SC_SD_BYTESWAP_OFF);
    __cart_wr(SC_COMMAND_REG, SC_SD_OP);
    if (__sc_sync()) CART_ABORT();
    __cart_acs_rel();
    return 0;
}
