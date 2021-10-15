/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800D18D0 */

#include "types.h"
#include "libultra_internal.h"

u32 osDpGetStatus(){
    return IO_READ(DPC_STATUS_REG);
}
