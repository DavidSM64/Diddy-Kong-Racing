/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B7D20 */

#include "types.h"
#include "macros.h"

extern s32* D_800E3040;
extern s32* D_800E3044;
extern s32* D_800E3048;
extern s32* D_800E304C;
extern s32* D_800E3070;
extern s32* D_800E3080;
extern s32* D_800E30D0;
extern s32* D_800E30D4;
extern s32* D_800E30D8;
extern s32 D_800E30DC;
extern s32* D_800E3178;
extern s32* D_800E3184;
extern s32* D_800E3188;
extern s32* D_800E3190;
extern s32* D_800E3194;
extern s32 D_800E31A0;
extern s16 D_800E3674;
extern s32 D_800E3678;
extern s32 D_800E3680;
extern u8* D_800E3760;
extern u8* D_800E3764;
extern s32 D_800E3768;
extern s32 D_800E376C;
extern s32 D_8012A0D8;
extern s32 D_8012A0DC;
extern u16 D_8012A7B6;
extern s32* D_8012A7C8;
extern s32 D_8012A7F0;
extern s32 D_8012AAD8;
extern s32 D_8012AAD4;
extern s32 D_8012AAD0;

u8* func_80070C9C(s32 arg0, s32 arg1);
void func_80071140(s32* arg0);
void func_8007B2BC(s32* arg0);
void func_800C5494(s32 arg0);
void func_800C5620(s32 arg0);

void func_800B7D20(void) {
    if (D_800E3040 != NULL) {
        func_80071140(D_800E3040);
        D_800E3040 = NULL;
    }
    if (D_800E3044 != NULL) {
        func_80071140(D_800E3044);
        D_800E3044 = NULL;
    }
    if (D_800E3048 != NULL) {
        func_80071140(D_800E3048);
        D_800E3048 = NULL;
    }
    if (D_800E304C != NULL) {
        func_80071140(D_800E304C);
        D_800E304C = NULL;
    }
    if (D_800E3070 != NULL) {
        func_80071140(D_800E3070);
        D_800E3070 = NULL;
    }
    if (D_800E3080 != NULL) {
        func_80071140(D_800E3080);
        D_800E3080 = NULL;
    }
    if (D_800E30D0 != NULL) {
        func_8007B2BC(D_800E30D0);
        D_800E30D0 = NULL;
    }
    if (D_800E30D4 != NULL) {
        func_80071140(D_800E30D4);
        D_800E30D4 = NULL;
    }
    if (D_800E30D8 != NULL) {
        func_80071140(D_800E30D8);
        D_800E30D8 = NULL;
    }
    if (D_800E3178 != NULL) {
        func_80071140(D_800E3178);
        D_800E3178 = NULL;
    }
    D_800E3190 = NULL;
    D_800E3194 = NULL;
    D_800E3184 = NULL;
    D_800E3188 = NULL;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B7EB4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B8134.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B82B4.s")

void func_800B8B8C(void) {
    s32 temp_v0;
    s32 phi_v0;
    s32 i;
    
    D_800E30DC = 0;
    phi_v0 = 0;
    
    for(i = 0; i < D_8012A0D8 * D_8012A0DC; i++) {
        temp_v0 = phi_v0 + 1;
        D_800E30D4[i] = 0;
        phi_v0 = temp_v0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B8C04.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B9228.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B92F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B97A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B9C18.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BA288.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BA4B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BA8E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BB2F4.s")

//GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BBDDC.s")
void func_800BBE08(void);
void func_800BBF78(s32 arg0);

void func_800BBDDC(s32 arg0) {
    func_800BBE08();
    func_800BBF78(arg0);
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BBE08.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BBF78.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BC6C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BCC70.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BDC80.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BE654.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BEEB4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BEFC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BF3E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BF524.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BF634.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BFE98.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BFFDC.s")

void func_800C0170(void) {
    D_800E31A0 = 1;
}

void func_800C0180(void) {
    D_800E31A0 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C018C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C01D8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0494.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C05C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0724.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0780.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0834.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0A08.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C0B00.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C1130.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C13E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C14DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C15D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C1EE8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2274.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C23F8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2548.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2640.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C27A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C28E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C29F0.s")

void func_800C2AB4(void) {
    func_80071140(D_8012A7C8);
    D_8012A7B6 = (u16)0;
    func_800C5620(6);
    func_800C5494(6);
}


void func_800C2AF4(s32 arg0) {
    D_800E3680 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2B00.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2D6C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C2F1C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3048.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C30CC.s")

void func_800C3140(s32 arg0) {
    D_800E3674 = arg0;
}

void func_800C314C(void) {
    D_800E3678 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3158.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C31EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3400.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3440.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3564.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C38B4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3C00.s")

void func_800C4164(s32 arg0) {
    D_8012A7F0 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4170.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C422C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C42EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4384.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C43CC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4440.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C45A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4DA0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4EDC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4F7C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4FBC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5000.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5050.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5168.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5494.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C55F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5620.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C56D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C56FC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C580C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5AA0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5B58.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5F60.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C6000.s")

void func_800C6170(void) {
    D_800E3760 = func_80070C9C(0x2800, 0xFF);
    D_800E3764 = func_80070C9C(0x10, 0xFF);
}

// Returns the little-endian value from a byte array.
s32 byteswap32(u8* arg0) {
    s32 value;
    value = *arg0++;
    value |= (*arg0++ << 8);
    value |= (*arg0++ << 16);
    value |= (*arg0++ << 24);
    return value;
}

s32 func_800C61DC(s32 arg0, s32 arg1) {
    func_80076E68(arg0, D_800E3764, arg1, 8);
    return byteswap32(D_800E3764);
}

s32 func_800C68C0(void);

s32 func_800C6218(s32 arg0, s32 arg1) {
    // The compression header is 5 bytes. Maybe this is part of the decompression routine?
    D_800E3768 = (s32) (arg0 + 5); 
    D_800E376C = arg1;
    D_8012AAD4 = 0;
    D_8012AAD0 = 0;
    while(func_800C68C0() != 0) {} // Keep calling func_800C68C0() until it returns 0.
    return arg1;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C6274.s")

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C68C0.s")

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C69C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C6B90.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C6DDC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C6F34.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C7040.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C7090.s")
