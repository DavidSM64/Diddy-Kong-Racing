/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800AE270 */

#include "types.h"
#include "macros.h"

/************ .data ************/

// I woundn't be suprised if most of these zeroes are really just null pointers.
s32 D_800E2CA0 = 0;
s32 D_800E2CA4 = 0;
s32 *D_800E2CA8 = NULL;
s32 D_800E2CAC = 0;
s32 D_800E2CB0 = 0;
s32 *D_800E2CB4 = NULL;
s32 D_800E2CB8 = 0;
s32 D_800E2CBC = 0;
s32 *D_800E2CC0 = NULL;
s32 D_800E2CC4 = 0;
s32 D_800E2CC8 = 0;
s32 *D_800E2CCC = NULL;
s32 D_800E2CD0 = 0;
s32 D_800E2CD4 = 0;
s32 *D_800E2CD8 = NULL;
s32 D_800E2CDC = 0;
s32 *D_800E2CE0 = NULL;
s32 *D_800E2CE4 = NULL;
s32 D_800E2CE8 = 0;
s32 *D_800E2CEC = NULL;
s32 *D_800E2CF0 = NULL;
s32 D_800E2CF4 = 0;
s32 *D_800E2CF8 = NULL;
s32 *D_800E2CFC = NULL;
s32 D_800E2D00[2] = { 0, 0 };

/* Size: 0x10 bytes, might just be an array? */
typedef struct unk800E2D08 {
    s16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
} unk800E2D08;

unk800E2D08 D_800E2D08[5] = {
    { 0x4000, 0x0102, 0x0100, 0x0000, 0x0000, 0x01E0, 0x0100, 0x01E0 },
    { 0x4000, 0x0203, 0x0100, 0x0000, 0x0100, 0x01E0, 0x01E0, 0x01E0 },
    { 0x4001, 0x0204, 0x0000, 0x0000, 0x0100, 0x0000, 0x0000, 0x01E0 },
    { 0x4002, 0x0305, 0x0100, 0x0000, 0x01E0, 0x0000, 0x01E0, 0x01E0 },
    { 0x4000, 0x0103, 0x0100, 0x0000, 0x0000, 0x01E0, 0x01E0, 0x01E0 }
};

// This might be a different struct/type
unk800E2D08 D_800E2D58[2] = {
    { 0x0000, 0x01FF, 0x01FF, 0x0000, 0x01FF, 0x01FF, 0x0000, 0x0000 },
    { 0x01FF, 0x0000, 0x0000, 0x01FF, 0x0000, 0x01FF, 0x01FF, 0x0000 }
};

/* Size: 0x40 bytes, might just be an array? */
typedef struct unk800E2D78 {
    s16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
    s16 unk10, unk12, unk14, unk16, unk18, unk1A, unk1C, unk1E;
    s16 unk20, unk22, unk24, unk26, unk28, unk2A, unk2C, unk2E;
    s16 unk30, unk32, unk34, unk36, unk38, unk3A, unk3C, unk3E;
} unk800E2D78;

unk800E2D78 D_800E2D78[2] = {
    {
        0x0000, 0x0105, 0x0000, 0x0000, 0x0080, 0x0000, 0x0080, 0x01FF, 
        0x0000, 0x0504, 0x0000, 0x0000, 0x0080, 0x01FF, 0x0000, 0x01FF, 
        0x0001, 0x0206, 0x0080, 0x0000, 0x0100, 0x0000, 0x0100, 0x01FF, 
        0x0001, 0x0605, 0x0080, 0x0000, 0x0100, 0x01FF, 0x0080, 0x01FF 
    },
    {
        0x0002, 0x0307, 0x0100, 0x0000, 0x0180, 0x0000, 0x0180, 0x01FF, 
        0x0002, 0x0706, 0x0100, 0x0000, 0x0180, 0x01FF, 0x0100, 0x01FF, 
        0x0003, 0x0004, 0x0180, 0x0000, 0x0200, 0x0000, 0x0200, 0x01FF, 
        0x0003, 0x0407, 0x0180, 0x0000, 0x0200, 0x01FF, 0x0180, 0x01FF
    },
};

/* Size: 0x18 bytes, might just be an array? */
typedef struct unk800E2DF8 {
    s16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
    s16 unk10, unk12, unk14, unk16;
} unk800E2DF8;

unk800E2DF8 D_800E2DF8[2] = {
    {
        0x0000, 0x0000, 0x01FF, 0x0000, 0x01FF, 0x01FF, 0x0000, 0x0000, 
        0x01FF, 0x0000, 0x01FF, 0x01FF
    },
    {
        0x0000, 0x0000, 0x01FF, 0x0000, 0x01FF, 0x01FF, 0x0000, 0x0000, 
        0x01FF, 0x0000, 0x01FF, 0x01FF
    },
};

f32 D_800E2E28[9] = {
    0.0f, 0.0f, 0.1, 0.2f, 0.3f, 0.45f, 0.525f, 0.6f, 0.8f
};

s32 D_800E2E4C = 0;
s32 D_800E2E50 = 0;
s32 D_800E2E54 = 0;
s32 D_800E2E58 = 0;
s32 D_800E2E5C = 0;
s32 *D_800E2E60 = NULL;
s32  D_800E2E64 = 0;

s16 D_800E2E68[6] = {
    0, 8, 7, -4, -7, -4
};

s16 D_800E2E74[8] = {
    -6, 6, 6, 6, 6, -6, -6, -6
};

s32 D_800E2E84[16] = {
    0x00000000, 0xC00840FF, 0xFF6008FF, 0x404040FF, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x1070FFFF, 0x00000000, 0x00000000
};

s32 D_800E2EC4[10] = {
    0x404040FF, 0x404040FF, 0x002D00FF, 0x002D00FF, 
    0x403C0AFF, 0x403C0AFF, 0x4040FFFF, 0x4040FFFF, 
    0x404040FF, 0x404040FF
};

s32 D_800E2EEC = 0x100;
s32 D_800E2EF0 = 0;

u8 D_800E2EF4[196] = {
    0x02, 0x04, 0x06, 0x08, 0x0A, 0x0F, 0x11, 0x15, 0x17, 0x1F, 0x21, 0x27, 0x29, 0x2B, 0x2D, 0x2F, 
    0x31, 0x33, 0x35, 0x38, 0x3A, 0x3F, 0x41, 0x43, 0x45, 0x48, 0x4A, 0x4B, 0x4D, 0x50, 0x52, 0x56, 
    0x58, 0x5B, 0x5D, 0x62, 0x64, 0x68, 0x6A, 0x6F, 0x71, 0x76, 0x78, 0x7D, 0x7F, 0x84, 0x86, 0x8B, 
    0x8D, 0x92, 0x94, 0x96, 0x98, 0x9A, 0x9D, 0xA2, 0xA5, 0xA9, 0xAB, 0xB0, 0xB3, 0xB8, 0x00, 0x01, 
    0x00, 0x09, 0x0B, 0x11, 0x13, 0x19, 0x1B, 0x21, 0x23, 0x29, 0x2B, 0x31, 0x33, 0x38, 0x3A, 0x41, 
    0x43, 0x49, 0x4B, 0x4C, 0x4E, 0x53, 0x55, 0x5B, 0x5D, 0x62, 0x64, 0x6B, 0x6D, 0x73, 0x75, 0x7B, 
    0x7D, 0x83, 0x85, 0x8B, 0x8D, 0x93, 0x95, 0x9B, 0x9D, 0xA3, 0xA5, 0xAA, 0xAC, 0xB2, 0xB4, 0xBC, 
    0xBE, 0xC4, 0xC6, 0xCC, 0xCE, 0xD3, 0xD5, 0xD7, 0xD9, 0xDC, 0xDE, 0xE0, 0xE2, 0xE7, 0xE9, 0xEF, 
    0x00, 0x01, 0x03, 0x08, 0x09, 0x0F, 0x11, 0x16, 0x18, 0x1D, 0x1F, 0x24, 0x26, 0x28, 0x2A, 0x2F, 
    0x31, 0x36, 0x38, 0x39, 0x3B, 0x3D, 0x3F, 0x43, 0x45, 0x46, 0x48, 0x4F, 0x51, 0x56, 0x58, 0x5D, 
    0x5F, 0x64, 0x66, 0x6B, 0x6C, 0x70, 0x72, 0x77, 0x79, 0x7C, 0x7E, 0x82, 0x84, 0x89, 0x8B, 0x92, 
    0x94, 0x99, 0x9B, 0xA0, 0xA2, 0xA6, 0xA8, 0xAB, 0xAD, 0xAE, 0xB0, 0xB3, 0xB5, 0xB9, 0xB5, 0xB9, 
    0x00, 0x00, 0x00, 0x00
};

// Fast3D (F3DDKR) display list
u32 D_800E2FB8[] = {
    0xE7000000, 0x00000000, 
    0xBA001402, 0x00000000, 
    0xBA001001, 0x00000000, 
    0xBA000E02, 0x00000000, 
    0xBA001102, 0x00000000, 
    0xBA001301, 0x00000000, 
    0xBA000C02, 0x00002000, 
    0xBA000903, 0x00000C00, 
    0xB9000002, 0x00000000, 
    0xB900031D, 0x00504240, 
    0xFB000000, 0xFFFFFFFF, 
    0xFA000000, 0x00000000, 
    0xB8000000, 0x00000000
};

s32 D_800E3020 = -1;
s32 D_800E3024 = 0;
s32 D_800E3028 = 0;

s32 *D_800E302C[3] = {
    (s32*)0x800E8F00, (s32*)0x800E8F08, (s32*)0x800E8F10
};

/*******************************/

void func_800AE2D8(void);
void func_800AE374(void);
void func_800AE438(void);
void func_800AE490(void);

void func_800AE270(void) {
    func_800AE374();
    func_800AE438();
    func_800AE2D8();
}

void func_800AE2A0(void) {
    func_800AE374();
    func_800AE438();
    func_800AE490();
    func_800AE2D8();
}

void func_800AE2D8(void) {
    s32 phi_s1;
    s32 phi_s0;

    if (D_800E2E60 != NULL) {
        phi_s1 = 0;
        phi_s0 = 0;
        if (D_800E2E64 > 0) {
            do {
                func_8007CCB0(*(D_800E2E60 + phi_s1));
                phi_s0 += 1;
                phi_s1 += 1;
            } while (phi_s0 < D_800E2E64);
        }
        func_80071140(D_800E2E60);
        D_800E2E60 = 0;
    }
}

void func_800AE374(void) {
    if (D_800E2CA8 != NULL) {
        func_80071140(D_800E2CA8);
        D_800E2CA8 = NULL;
    }
    if (D_800E2CB4 != NULL) {
        func_80071140(D_800E2CB4);
        D_800E2CB4 = NULL;
    }
    if (D_800E2CC0 != NULL) {
        func_80071140(D_800E2CC0);
        D_800E2CC0 = NULL;
    }
    if (D_800E2CCC != NULL) {
        func_80071140(D_800E2CCC);
        D_800E2CCC = NULL;
    }
    if (D_800E2CD8 != NULL) {
        func_80071140(D_800E2CD8);
        D_800E2CD8 = NULL;
    }
}

void func_800AE438(void) {
    if (D_800E2CE0 != NULL) {
        func_80071140(D_800E2CE0);
        D_800E2CE0 = NULL;
    }
    if (D_800E2CE4 != NULL) {
        func_80071140(D_800E2CE4);
        D_800E2CE4 = NULL;
    }
}

void func_800AE490(void) {
    if (D_800E2CEC != NULL) {
        func_80071140(D_800E2CEC);
        D_800E2CEC = NULL;
    }
    if (D_800E2CF0 != NULL) {
        func_80071140(D_800E2CF0);
        D_800E2CF0 = NULL;
    }
    if (D_800E2CF8 != NULL) {
        func_80071140(D_800E2CF8);
        D_800E2CF8 = NULL;
    }
    if (D_800E2CFC != NULL) {
        func_80071140(D_800E2CFC);
        D_800E2CFC = NULL;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AE530.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AE728.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AEE14.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AEEB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AEF88.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF024.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF0A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF0F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF134.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF1E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF29C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF404.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF52C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF6E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AF714.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AFC3C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800AFE5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B0010.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B03C0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B0698.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B0BAC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B1130.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B1CB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B2040.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B2260.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B22FC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B263C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B26E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B2FBC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3140.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3240.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3358.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B34B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3564.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3740.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B3E64.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B4668.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B46BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B4940.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B4A08.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B4A40.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B5E88.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B5EDC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B5F78.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B62B4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B635C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B653C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B695C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B69FC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6E50.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6EE0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6F04.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6F40.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B6F50.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/D_800B6FC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B70D0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7144.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B71B0.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7460.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B76B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B76DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B77D4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7810.s")
GLOBAL_ASM("asm/non_matchings/unknown_0AEE70/func_800B7D10.s")
