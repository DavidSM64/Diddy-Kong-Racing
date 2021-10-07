/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D63EC */

#include "libultra_internal.h"

u32 __osSpGetStatus() {
    return IO_READ(SP_STATUS_REG);
}
