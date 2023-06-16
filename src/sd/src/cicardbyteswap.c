/* RAM_POS: auto */

#include <cart.h>
#include "cartint.h"
#include "ci.h"

int ci_card_byteswap(int flag)
{
    __cart_acs_get();
    __ci_sync();
    __cart_wr(CI_COMMAND_REG, flag ? CI_BYTESWAP_ON : CI_BYTESWAP_OFF);
    __ci_sync();
    __cart_acs_rel();
    return 0;
}
