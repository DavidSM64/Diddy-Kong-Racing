/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C8E20 */

#include "PR/rcp.h"

/**
 * This function (osAiGetLength) returns the number of bytes remaining in the current DMA buffer.
 * Notes:
 * For hardware version 1.0, the audio DMA length register is only 15-bit long and thus supports 
 * a maximum transfer size of 32 Kbytes. In the final release, this register is extended to 
 * 18 bits to support a transfer of 256 Kbytes. 
 */
u32 osAiGetLength(void) {
    return IO_READ(AI_LEN_REG);
}
