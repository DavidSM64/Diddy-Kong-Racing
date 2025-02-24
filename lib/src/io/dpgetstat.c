/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D18D0 */

#include "PR/os_internal.h"
#include "PR/rcp.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

u32 osDpGetStatus(void) {
    return IO_READ(DPC_STATUS_REG);
}
