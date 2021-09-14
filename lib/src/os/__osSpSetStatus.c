/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CD240 */

#include "__osSpSetStatus.h"
#include "types.h"
#include "macros.h"
#include "hardware.h"

void __osSpSetStatus(u32 status) {
    HW_REG(SP_STATUS_REG, u32) = status;
}
