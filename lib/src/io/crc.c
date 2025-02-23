/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800CD770 */

/**
 * File: crc.c
 * Description: Functions to compute Cyclic Redundancy Check for specific addresses and data.
 */
#include "PR/os_internal.h"
#include <ultra64.h>

#if BUILD_VERSION >= VERSION_J

#define ADDRESS_CRC_MESSAGE_LENGTH 10
#define ADDRESS_CRC_LENGTH 5
#define ADDRESS_CRC_GENERATOR 0x15
#define ADDRESS_CRC_MASK ((1 << ADDRESS_CRC_LENGTH) - 1)

/**
 * CRC-5 with the generating polynomial \f$ x^5 + x^4 + x^2 + 1 \f$, AKA 0x15 = 0b(1)1 0101.
 * It only works on the bits from 0x7FF = 11 11111111, i.e. 10 bits.
 *
 * Usually used as __osContAddressCrc(addr) | (addr << 5) to add the CRC to the end. The overall length of 10 + 5 bits
 * allows the address + CRC to fit into one s16.
 *
 * `addr` is the address of a block in the mempak, only valid up to 0x7FF.
 */
u8 __osContAddressCrc(u16 addr) {
    u32 temp = 0;
    u32 i = (1 << ADDRESS_CRC_MESSAGE_LENGTH);

    do {
        // temp is used as a shift register for the CRC
        temp <<= 1;

        if ((u32)addr & i) {
            if (temp & (1 << ADDRESS_CRC_LENGTH)) {
                // Same as temp++; temp ^= 0x15 since last bit always 0 after the shift
                temp ^= ADDRESS_CRC_GENERATOR - 1;
            } else {
                ++temp;
            }
        } else if (temp & (1 << ADDRESS_CRC_LENGTH)) {
            temp ^= ADDRESS_CRC_GENERATOR;
        }

        i >>= 1;
    } while (i != 0);

    // Acts like 5 bits of 0s are appended to addr
    i = ADDRESS_CRC_LENGTH;
    do {
        temp <<= 1;
        if (temp & (1 << ADDRESS_CRC_LENGTH)) {
            temp ^= ADDRESS_CRC_GENERATOR;
        }
    } while (--i != 0);

    // Discard the irrelevant bits above the actual remainder
    return temp & ADDRESS_CRC_MASK;
}

#define DATA_CRC_MESSAGE_BYTES 32
#define DATA_CRC_LENGTH 8
#define DATA_CRC_GENERATOR 0x85

/**
 * CRC-8 with generating polynomial \f$ x^8 + x^7 + x^2 + 1 \f$, AKA 0x85 = 0b(1) 1000 0101.
 * Expects exactly 0x20 = 32 bytes of data.
 */
u8 __osContDataCrc(u8* data) {
    u32 temp = 0;
    u32 i;
    u32 j;

    for (i = DATA_CRC_MESSAGE_BYTES; i; --i) {
        // Loop over each bit in the byte starting with most significant
        for (j = (1 << (DATA_CRC_LENGTH - 1)); j; j >>= 1) {
            temp <<= 1;

            if ((*data & j) != 0) {
                if ((temp & (1 << DATA_CRC_LENGTH)) != 0) {
                    // Same as ret++; ret ^= 0x85 since last bit always 0 after the shift
                    temp ^= DATA_CRC_GENERATOR - 1;
                } else {
                    ++temp;
                }
            } else if (temp & (1 << DATA_CRC_LENGTH)) {
                temp ^= DATA_CRC_GENERATOR;
            }
        }

        data++;
    }
    do {
        temp <<= 1;

        if (temp & (1 << DATA_CRC_LENGTH)) {
            temp ^= DATA_CRC_GENERATOR;
        }
    } while (++i < DATA_CRC_LENGTH);

    return temp;
}

#else

u8 __osContAddressCrc(u16 addr) {
    u8 temp = 0;
    u8 temp2;
    int i;
    
    for (i = 0; i < 16; i++) {
        temp2 = (temp & 0x10) ? 0x15 : 0;

        temp <<= 1;
        temp |= (u8)((addr & 0x400) ? 1 : 0);
        addr <<= 1;
        temp ^= temp2;
    }
    
    return temp & 0x1f;
}

u8 __osContDataCrc(u8 *data) {
    u8 temp = 0;
    u8 temp2;
    int i;
    int j;
    
    for (i = 0; i <= 32; i++) {
        for (j = 7; j > -1; j--) {
            temp2 = (temp & 0x80) ? 0x85 : 0;
            
            temp <<= 1;
            
            if (i == 32) {
                temp &= -1;
            } else {
                temp |= ((*data & (1 << j)) ? 1 : 0);
            }
            
            temp ^= temp2;
        }
        data++;
    }
    return temp;
}

#endif
