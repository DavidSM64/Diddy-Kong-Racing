/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80076BA0 */

#include "unknown_0777A0.h"
#include "memory.h"

//#include "assets.h"
#include "types.h"
#include "macros.h"
#include "ultra64.h"

/************ .bss ************/

OSIoMesg D_80124200;
OSMesg D_80124218;
OSMesgQueue D_80124220;
OSMesg D_80124238;
s32 D_80124240[14];
OSMesgQueue D_80124278;
s32 *gAssetsLookupTable;

/*******************************/

// These are both defined in the generated dkr.ld file.
extern u8 __ASSETS_LUT_START, __ASSETS_LUT_END; // __ASSETS_LUT_START = 0xECB60, _END = 0xECC30

void *allocate_from_main_pool_safe(s32, s32);
s32 func_80071478(s32*);
void dmacopy(u32 romOffset, u8 *ramAddress, s32 numBytes);
    
void func_80076BA0(void) {
    u32 assetTableSize;
    osCreateMesgQueue(&D_80124278, &D_80124238, 16);
    osCreateMesgQueue(&D_80124220, &D_80124218, 1);
    osCreatePiManager(150, &D_80124278, &D_80124238, 16);
    assetTableSize = &__ASSETS_LUT_END - &__ASSETS_LUT_START;
    gAssetsLookupTable = (s32*)allocate_from_main_pool_safe(assetTableSize, COLOR_TAG_GRAY);
    func_80071478(gAssetsLookupTable);
    dmacopy(&__ASSETS_LUT_START, gAssetsLookupTable, assetTableSize);
}
    
/**
 * Returns the memory address containing an asset section loaded from ROM.
 */
s32 *load_asset_section_from_rom(u32 assetIndex) {
    s32 *index;
    s32 *out;
    s32 size;
    s32 start;
    if (gAssetsLookupTable[0] < assetIndex) {
        return NULL;
    }
    assetIndex++;
    index = assetIndex + gAssetsLookupTable;
    start = *index;
    size = *(index + 1) - start;
    out = (s32*)allocate_from_main_pool_safe(size, COLOR_TAG_GRAY);
    if (out == NULL) {
        return NULL;
    }
    dmacopy(start + &__ASSETS_LUT_END, out, size);
    return out;
}

#ifdef NON_MATCHING
// This has regalloc & stack issues.
u8 *func_80076CF0(u32 assetIndex, s32 arg1) {
    s32 size;
    s32 sp2C;
    s32 start;
    s32 *index;
    u8 *temp_a1;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_a0;

    if (gAssetsLookupTable[0] < assetIndex) {
        return NULL;
    }
    
    assetIndex++;
    index = assetIndex + gAssetsLookupTable;
    start = *index;
    size = *(index + 1) - start;
    
    temp_v0_2 = (u8*)allocate_from_main_pool_safe(8, COLOR_TAG_WHITE);
    temp_a0 = start + &__ASSETS_LUT_END;
    
    dmacopy(temp_a0, temp_v0_2, 8);
    sp2C = byteswap32(temp_v0_2) + arg1;
    free_from_memory_pool(temp_v0_2);
    temp_v0_3 = (u8*)allocate_from_main_pool_safe(sp2C + arg1, COLOR_TAG_GRAY);
    
    if (temp_v0_3 == NULL) {
        return NULL;
    }
    temp_a1 = (temp_v0_3 + sp2C) - size;
    dmacopy(temp_a0, temp_a1, size);
    func_800C6218(temp_a1, temp_v0_3);
    return temp_v0_3;
}
#else
GLOBAL_ASM("asm/non_matchings/controller_pak/load_asset_section_from_rom.s")
#endif

/**
 * Unused.
 * Loads an asset section to a specific memory address.
 * Returns the size of asset section.
 */
s32 load_asset_section_from_rom_to_address(u32 assetIndex, s32 *address) {
    s32 start;
    s32 size;
    s32 *index;
    if (gAssetsLookupTable[0] < assetIndex) {
        return 0;
    }
    assetIndex++;
    index = assetIndex + gAssetsLookupTable;
    start = *index;
    size = *(index + 1) - start;
    dmacopy(start + &__ASSETS_LUT_END, address, size);
    return size;
}

/**
 * Loads part of an asset section to a specific memory address.
 * Returns the size argument.
 */
s32 load_asset_to_address(u32 assetIndex, s32 *address, s32 assetOffset, s32 size) {
    s32 *index;
    s32 start;
    
    if (size == 0 || gAssetsLookupTable[0] < assetIndex) {
        return 0;
    }
    
    assetIndex++;
    index = assetIndex + gAssetsLookupTable;
    start = *index + assetOffset;
    dmacopy(start + &__ASSETS_LUT_END, address, size);
    return size;
}

/**
 * Returns a rom offset of an asset given its asset section and a local offset.
 */
u8 *get_rom_offset_of_asset(u32 assetIndex, s32 assetOffset) {
    s32 *index;
    s32 start;
    
    if (gAssetsLookupTable[0] < assetIndex) {
        return NULL;
    }
    
    assetIndex++;
    index = assetIndex + gAssetsLookupTable;
    start = *index + assetOffset;
    return start + &__ASSETS_LUT_END;
}

/**
 * Returns the size of an asset section.
 */
s32 get_size_of_asset_section(u32 assetIndex) {
    s32 *index;

    if (gAssetsLookupTable[0] < assetIndex) {
        return 0;
    }
    
    assetIndex++;
    index = assetIndex + gAssetsLookupTable;
    return *(index + 1) - *index;
}

#define MAX_TRANSFER_SIZE 0x5000

/**
 * Copies data from the game cartridge to a ram address.
 */
void dmacopy(u32 romOffset, u8 *ramAddress, s32 numBytes) {
    s32 sp4C;
    s32 numBytesToDMA;

    osInvalDCache(ramAddress, numBytes);
    numBytesToDMA = MAX_TRANSFER_SIZE;
    while(numBytes > 0) {
        if (numBytes < numBytesToDMA) {
            numBytesToDMA = numBytes;
        }
        osPiStartDma(&D_80124200, 0, 0, romOffset, ramAddress, numBytesToDMA, &D_80124220);
        osRecvMesg(&D_80124220, &sp4C, 1);
        numBytes -= numBytesToDMA;
        romOffset += numBytesToDMA;
        ramAddress += numBytesToDMA;
    }
}
