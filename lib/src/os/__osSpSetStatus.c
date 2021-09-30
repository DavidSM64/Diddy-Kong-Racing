/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CD240 */

#include "types.h"
#include "macros.h"
#include "PR/rcp.h"

void __osSpSetStatus(u32 status) {
    IO_WRITE(SP_STATUS_REG, status);
}
