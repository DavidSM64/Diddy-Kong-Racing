/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80076BA0 */

#include "asset_loading.h"

//#include "assets.h"
#include "macros.h"
#include "ultra64.h"

/************ .bss ************/

OSIoMesg gAssetsDmaIoMesg;
OSMesg gDmaMesg;
OSMesgQueue gDmaMesgQueue;
OSMesg gPIMesgBuf[16];
OSMesgQueue gPIMesgQueue;
u32 *gAssetsLookupTable;

/*******************************/

// These are both defined in the generated dkr.ld file.
extern u8 __ASSETS_LUT_START[], __ASSETS_LUT_END[]; // __ASSETS_LUT_START = 0xECB60, _END = 0xECC30

/**
 * Set up the peripheral interface message queues and scheduling.
 * This will send messages when DMA reads are finished.
 * After, allocate space and load the asset table into RAM.
*/
void init_PI_mesg_queue(void) {
    u32 assetTableSize;
    osCreateMesgQueue(&gPIMesgQueue, gPIMesgBuf, ARRAY_COUNT(gPIMesgBuf));
    osCreateMesgQueue(&gDmaMesgQueue, &gDmaMesg, 1);
    osCreatePiManager((OSPri) 150, &gPIMesgQueue, gPIMesgBuf, ARRAY_COUNT(gPIMesgBuf));
    assetTableSize = __ASSETS_LUT_END - __ASSETS_LUT_START;
    gAssetsLookupTable = (u32 *) allocate_from_main_pool_safe(assetTableSize, COLOUR_TAG_GREY);
    func_80071478((u8 *) gAssetsLookupTable);
    dmacopy((u32) __ASSETS_LUT_START, (u32) gAssetsLookupTable, (s32) assetTableSize);
}

/**
 * Returns the memory address containing an asset section loaded from ROM.
 */
u32 *load_asset_section_from_rom(u32 assetIndex) {
    u32 *index;
    u32 *out;
    s32 size;
    u32 start;
    if (gAssetsLookupTable[0] < assetIndex) {
        return 0;
    }
    assetIndex++;
    index = assetIndex + gAssetsLookupTable;
    start = *index;
    size = *(index + 1) - start;
    out = (u32 *) allocate_from_main_pool_safe(size, COLOUR_TAG_GREY);
    if (out == 0) {
        return 0;
    }
    dmacopy((u32) (start + __ASSETS_LUT_END), (u32)out, size);
    return out;
}

/**
 * Loads part of an asset section to a specific memory address.
 * Returns the size argument.
 */
s32 load_asset_to_address(u32 assetIndex, u32 address, s32 assetOffset, s32 size) {
    u32 *index;
    s32 start;

    if (size == 0 || gAssetsLookupTable[0] < assetIndex) {
        return 0;
    }

    assetIndex++;
    index = assetIndex + gAssetsLookupTable;
    start = *index + assetOffset;
    dmacopy((u32) (start + __ASSETS_LUT_END), address, size);
    return size;
}

/**
 * Returns a rom offset of an asset given its asset section and a local offset.
 */
u8 *get_rom_offset_of_asset(u32 assetIndex, u32 assetOffset) {
    u32 *index;
    u32 start;

    if (gAssetsLookupTable[0] < assetIndex) {
        return NULL;
    }

    assetIndex++;
    index = assetIndex + gAssetsLookupTable;
    start = *index + assetOffset;
    return start + __ASSETS_LUT_END;
}

/**
 * Returns the size of an asset section.
 */
s32 get_size_of_asset_section(u32 assetIndex) {
    u32 *index;

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
void dmacopy(u32 romOffset, u32 ramAddress, s32 numBytes) {
    OSMesg dmaMesg;
    s32 numBytesToDMA;

    osInvalDCache((u32 *) ramAddress, numBytes);
    numBytesToDMA = MAX_TRANSFER_SIZE;
    while (numBytes > 0) {
        if (numBytes < numBytesToDMA) {
            numBytesToDMA = numBytes;
        }
        osPiStartDma(&gAssetsDmaIoMesg, OS_MESG_PRI_NORMAL, OS_READ, romOffset, (u32 *) ramAddress, numBytesToDMA, &gDmaMesgQueue);
        osRecvMesg(&gDmaMesgQueue, &dmaMesg, 1);
        numBytes -= numBytesToDMA;
        romOffset += numBytesToDMA;
        ramAddress += numBytesToDMA;
    }
}
