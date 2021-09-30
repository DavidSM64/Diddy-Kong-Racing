/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C8600 */

#include "libultra_internal.h"

extern s32 osViClock;
s32 osAiSetFrequency(u32 frequency) {
    register u32 dacRate;
    register u8 bitRate;
    register float f;
    
    f = osViClock / (float)frequency + .5f;
    dacRate = f;
    
    if (dacRate < AI_MIN_DAC_RATE)
        return -1;
    
    bitRate = (dacRate / 66);
    
    if (bitRate > AI_MAX_BIT_RATE)
        bitRate = AI_MAX_BIT_RATE;

    IO_WRITE(AI_DACRATE_REG, dacRate - 1);
    IO_WRITE(AI_BITRATE_REG, bitRate - 1);
    IO_WRITE(AI_CONTROL_REG, AI_CONTROL_DMA_ON);
    
    return osViClock / (s32)dacRate;
}
