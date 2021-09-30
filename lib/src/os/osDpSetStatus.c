/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CD250 */

#include "libultra_internal.h"

void osDpSetStatus(u32 data) {
    IO_WRITE(DPC_STATUS_REG, data);
}
