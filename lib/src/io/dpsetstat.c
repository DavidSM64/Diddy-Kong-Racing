/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CD250 */

#include "PR/os_internal.h"
#include "PR/rcp.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

void osDpSetStatus(u32 data) {
    IO_WRITE(DPC_STATUS_REG, data);
}
