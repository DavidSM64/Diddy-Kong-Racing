/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C8E20 */

#include "types.h"
#include "macros.h"
#include "PR/rcp.h"

u32 osAiGetLength(void) {
    return IO_READ(AI_LEN_REG);
}
