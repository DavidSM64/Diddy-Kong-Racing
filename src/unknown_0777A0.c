/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80072250 */

#include "types.h"
#include "macros.h"

extern s32 *D_80124200;
extern s32 D_80124218;
extern s32 D_80124220;
extern s32 D_80124238;
extern s32 D_80124278;
extern s32 *D_80124290;

// These are both defined in the generated dkr.ld file.
extern u8 __ASSETS_LUT_START, __ASSETS_LUT_END; // __ASSETS_LUT_START = 0xECB60, _END = 0xECC30

void osCreateMesgQueue(s32*, s32*, s32);
void osCreatePiManager(s32, s32*, s32*, s32);
void *func_80070C9C(s32, s32);
s32 func_80071478(s32*);
void dmacopy(u32 romOffset, u8 *ramAddress, s32 numBytes);
    
void func_80076BA0(void) {
    u32 size;
    osCreateMesgQueue(&D_80124278, &D_80124238, 0x10);
    osCreateMesgQueue(&D_80124220, &D_80124218, 1);
    osCreatePiManager(0x96, &D_80124278, &D_80124238, 0x10);
    size = &__ASSETS_LUT_END - &__ASSETS_LUT_START;
    D_80124290 = (s32*)func_80070C9C(size, 0x7F7F7FFF);
    func_80071478(D_80124290);
    dmacopy(&__ASSETS_LUT_START, D_80124290, size);
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_072E50/func_80076C58.s")
#else
    
// This function is OK
s32 *func_80076C58(u32 arg0) {
    s32 *temp;
    s32 *temp2;
    s32 size;
    s32 start;
    if (D_80124290[0] < arg0) {
        return NULL;
    }
    arg0++;
    temp = arg0 + D_80124290;
    start = *temp;
    size = *(temp + 1) - start;
    temp2 = (s32*)func_80070C9C(size, 0x7F7F7FFF);
    if (temp2 == NULL) {
        return NULL;
    }
    dmacopy(start + &__ASSETS_LUT_END, temp2, size);
    return temp2;
}

// Unused?
// This has regalloc & stack issues.
u8 *func_80076CF0(u32 arg0, s32 arg1) {
    s32 size;
    s32 sp2C;
    s32 start;
    s32 *temp;
    u8 *temp_a1;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_a0;

    if (D_80124290[0] < arg0) {
        return NULL;
    }
    
    arg0++;
    temp = arg0 + D_80124290;
    start = *temp;
    size = *(temp + 1) - start;
    
    temp_v0_2 = (u8*)func_80070C9C(8, 0xFFFFFFFF);
    temp_a0 = start + &__ASSETS_LUT_END;
    
    dmacopy(temp_a0, temp_v0_2, 8);
    sp2C = byteswap32(temp_v0_2) + arg1;
    func_80071140(temp_v0_2);
    temp_v0_3 = (u8*)func_80070C9C(sp2C + arg1, 0x7F7F7FFF);
    
    if (temp_v0_3 == NULL) {
        return NULL;
    }
    temp_a1 = (temp_v0_3 + sp2C) - size;
    dmacopy(temp_a0, temp_a1, size);
    func_800C6218(temp_a1, temp_v0_3);
    return temp_v0_3;
}

// Unused?
// This function is OK
s32 func_80076DFC(u32 arg0, s32 *arg1) {
    s32 start;
    s32 size;
    u8 *temp;
    if (D_80124290[0] < arg0) {
        return 0;
    }
    arg0++;
    temp = arg0 + D_80124290;
    start = *temp;
    size = *(temp + 1) - start;
    dmacopy(start + &__ASSETS_LUT_END, arg1, size);
    return size;
}
#endif

s32 func_80076E68(u32 arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 *temp;
    s32 temp2;
    
    if (arg3 == 0 || D_80124290[0] < arg0) {
        return 0;
    }
    
    arg0++;
    temp = arg0 + D_80124290;
    temp2 = *temp + arg2;
    dmacopy(temp2 + &__ASSETS_LUT_END, arg1, arg3);
    return arg3;
}

u8 *func_80076EE8(u32 arg0, s32 arg1) {
    s32 *temp;
    s32 temp2;
    s32 temp3;
    if (D_80124290[0] < arg0) {
        return NULL;
    }
    arg0++;
    temp = arg0 + D_80124290;
    temp3 = *temp + arg1;
    return temp3 + &__ASSETS_LUT_END;
}

s32 func_80076F30(u32 arg0) {
    s32 *temp;

    if (D_80124290[0] < arg0) {
        return 0;
    }
    arg0++;
    temp = arg0 + D_80124290;
    return *(temp + 1) - *temp;
}

#define MAX_TRANSFER_SIZE 0x5000 // Why did they pick 20 KB as the transfer limit?

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
