/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C0170 */

#include "types.h"
#include "macros.h"

/************ .data ************/

s32 D_800E31A0 = 0;
s32 D_800E31A4 = 0;
s32 D_800E31A8 = 0;
s32 D_800E31AC = 0;
s32 D_800E31B0 = 0;
s32 D_800E31B4 = 0;
s32 D_800E31B8 = 0;
s32 D_800E31BC = 0;
s32 D_800E31C0 = 0;
s32 D_800E31C4 = 0;
s32 D_800E31C8 = 0;
s32 D_800E31CC = 0;
s32 D_800E31D0[2] = { 0, 0 };

// Fast3D (F3DDKR) display list
u32 D_800E31D8[] = {
    0xE7000000, 0x00000000, 
    0xBA001402, 0x00000000, 
    0xBA001001, 0x00000000, 
    0xBA000E02, 0x00000000, 
    0xBA001102, 0x00000000, 
    0xBA001301, 0x00000000, 
    0xBA000C02, 0x00002000, 
    0xBA000903, 0x00000C00, 
    0xB9000002, 0x00000000, 
    0xB900031D, 0x00504340, 
    0xB8000000, 0x00000000
};

s16 D_800E3230[28] = {
    0xFE20, 0x0078, 0xFEC0, 0x0078, 0xFF60, 0x0078, 0x0000, 0x0078, 
    0x00A0, 0x0078, 0x0140, 0x0078, 0x01E0, 0x0078, 0xFE20, 0xFF88, 
    0xFEC0, 0xFF88, 0xFF60, 0xFF88, 0x0000, 0xFF88, 0x00A0, 0xFF88, 
    0x0140, 0xFF88, 0x01E0, 0xFF88
};

s16 D_800E3268[28] = {
    0xFF60, 0x0168, 0xFF60, 0x00F0, 0xFF60, 0x0078, 0xFF60, 0x0000, 
    0xFF60, 0xFF88, 0xFF60, 0xFF10, 0xFF60, 0xFF10, 0x00A0, 0x0168, 
    0x00A0, 0x00F0, 0x00A0, 0x0078, 0x00A0, 0x0000, 0x00A0, 0xFF88,
    0x00A0, 0xFF10, 0x00A0, 0xFF10
};

s8 D_800E32A0[12] = {
    0x00, 0x02, 0x04, 0x0E, 0x10, 0x12, 0x08, 0x0A,
    0x0C, 0x16, 0x18, 0x1A
};

s8 D_800E32AC[12] = {
    0x04, 0x06, 0x08, 0x12, 0x14, 0x16, 0x04, 0x06,
    0x08, 0x12, 0x14, 0x16
};

s8 D_800E32B8[24] = {
    0, 3, 1, 1, 3, 4, 1, 4, 
    2, 2, 4, 5, 6, 9, 7, 7, 
    9, 10, 7, 10, 8, 8, 10, 11
};

s8 D_800E32D0[12] = {
    -1, -1, 0, -1, -1, 0, 0, -1, -1, 0, -1, -1
};

s16 D_800E32DC[24] = {
    0xFCE0, 0x0078, 0xFE20, 0x0078, 0xFF60, 0x0078, 0x00A0, 0x0078, 
    0x01E0, 0x0078, 0x0320, 0x0078, 0xFCE0, 0xFF88, 0xFE20, 0xFF88, 
    0xFF60, 0xFF88, 0x00A0, 0xFF88, 0x01E0, 0xFF88, 0x0320, 0xFF88
};

s8 D_800E330C[12] = {
    0, 2, 4, 12, 14, 8, 10, 18, 20, 22, 0, 0
};

s8 D_800E3318[12] = {
    4, 6, 8, 16, 18, 4, 6, 14, 16, 18, 0, 0
};

s8 D_800E3324[20] = {
    0, 1, 3, 1, 3, 4, 1, 4, 2, 5, 7, 8, 5, 8, 6, 6, 8, 9, 0, 0
};

s8 D_800E3338[12] = {
    -1, -1, 0, -1, 0, 0, -1, 0, -1, -1, 0, 0
};

s16 D_800E3344[126] = {
    0xFF60, 0x00A0, 0xFF70, 0x00A0, 0xFF80, 0x00A0, 0xFF90, 0x00A0, 
    0xFFA0, 0x00A0, 0xFFB0, 0x00A0, 0xFFC0, 0x00A0, 0xFFD0, 0x00A0, 
    0xFFE0, 0x00A0, 0xFFF0, 0x00A0, 0x0000, 0x00A0, 0x0010, 0x00A0, 
    0x0020, 0x00A0, 0x0030, 0x00A0, 0x0040, 0x00A0, 0x0050, 0x00A0, 
    0x0060, 0x00A0, 0x0070, 0x00A0, 0x0080, 0x00A0, 0x0090, 0x00A0, 
    0x00A0, 0x00A0, 0xFF60, 0xFF38, 0xFF70, 0xFF60, 0xFF80, 0xFF74, 
    0xFF90, 0xFF7E, 0xFFA0, 0xFF74, 0xFFB0, 0xFF38, 0xFFC0, 0xFF10, 
    0xFFD0, 0xFEFC, 0xFFE0, 0xFEF2, 0xFFF0, 0xFEFC, 0x0000, 0xFF24, 
    0x0010, 0xFF2E, 0x0020, 0xFF38, 0x0030, 0xFF2E, 0x0040, 0xFF24, 
    0x0050, 0xFEFC, 0x0060, 0xFEF2, 0x0070, 0xFEFC, 0x0080, 0xFF24, 
    0x0090, 0xFF60, 0x00A0, 0xFF74, 0xFF60, 0xFEE8, 0xFF70, 0xFEE8, 
    0xFF80, 0xFEE8, 0xFF90, 0xFEE8, 0xFFA0, 0xFEE8, 0xFFB0, 0xFEE8, 
    0xFFC0, 0xFEE8, 0xFFD0, 0xFEE8, 0xFFE0, 0xFEE8, 0xFFF0, 0xFEE8, 
    0x0000, 0xFEE8, 0x0010, 0xFEE8, 0x0020, 0xFEE8, 0x0030, 0xFEE8, 
    0x0040, 0xFEE8, 0x0050, 0xFEE8, 0x0060, 0xFEE8, 0x0070, 0xFEE8, 
    0x0080, 0xFEE8, 0x0090, 0xFEE8, 0x00A0, 0xFEE8
};

s8 D_800E3440[92] = {
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 
    0x0E, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x0E, 
    0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1A, 0x1C, 
    0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x1A, 0x1C, 
    0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x00, 0x02, 
    0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x54, 0x56, 
    0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x0E, 0x10, 
    0x12, 0x14, 0x16, 0x18, 0x1A, 0x62, 0x64, 0x66, 
    0x68, 0x6A, 0x6C, 0x6E, 0x1A, 0x1C, 0x1E, 0x20, 
    0x22, 0x24, 0x26, 0x28, 0x6E, 0x70, 0x72, 0x74, 
    0x76, 0x78, 0x7A, 0x7C
};

s8 D_800E349C[92] = {
    0x2A, 0x2C, 0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 
    0x54, 0x56, 0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 
    0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x42, 0x44, 0x62, 
    0x64, 0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x44, 0x46, 
    0x48, 0x4A, 0x4C, 0x4E, 0x50, 0x52, 0x6E, 0x70, 
    0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x54, 0x56, 
    0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x54, 0x56, 
    0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x62, 0x64, 
    0x66, 0x68, 0x6A, 0x6C, 0x6E, 0x62, 0x64, 0x66, 
    0x68, 0x6A, 0x6C, 0x6E, 0x6E, 0x70, 0x72, 0x74, 
    0x76, 0x78, 0x7A, 0x7C, 0x6E, 0x70, 0x72, 0x74, 
    0x76, 0x78, 0x7A, 0x7C
};

s8 D_800E34F8[92] = {
    0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, 
    0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, 0, 0, 
    0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

s8 D_800E3554[244] = {
    0, 8, 9, 0, 9, 1, 1, 9, 10, 1, 10, 2, 2, 10, 11, 2, 
    11, 3, 3, 11, 12, 3, 12, 4, 4, 12, 13, 4, 13, 5, 5, 13, 
    14, 5, 14, 6, 6, 14, 15, 6, 15, 7, 0, 7, 8, 0, 8, 1, 
    1, 8, 9, 1, 9, 2, 2, 9, 10, 2, 10, 3, 3, 10, 11, 3, 
    11, 4, 4, 11, 12, 4, 12, 5, 5, 12, 13, 5, 13, 6, 0, 8, 
    9, 0, 9, 1, 1, 9, 10, 1, 10, 2, 2, 10, 11, 2, 11, 3, 
    3, 11, 12, 3, 12, 4, 4, 12, 13, 4, 13, 5, 5, 13, 14, 5, 
    14, 6, 6, 14, 15, 6, 15, 7, 0, 8, 9, 0, 9, 1, 1, 9, 
    10, 1, 10, 2, 2, 10, 11, 2, 11, 3, 3, 11, 12, 3, 12, 4, 
    4, 12, 13, 4, 13, 5, 5, 13, 14, 5, 14, 6, 6, 14, 15, 6, 
    15, 7, 0, 7, 8, 0, 8, 1, 1, 8, 9, 1, 9, 2, 2, 9, 
    10, 2, 10, 3, 3, 10, 11, 3, 11, 4, 4, 11, 12, 4, 12, 5, 
    5, 12, 13, 5, 13, 6, 0, 8, 9, 0, 9, 1, 1, 9, 10, 1, 
    10, 2, 2, 10, 11, 2, 11, 3, 3, 11, 12, 3, 12, 4, 4, 12, 
    13, 4, 13, 5, 5, 13, 14, 5, 14, 6, 6, 14, 15, 6, 15, 7, 
    0, 0, 0, 0
};

// Fast3D (F3DDKR) display list
u32 D_800E3648[] = {
    0xE7000000, 0x00000000, 
    0xB6000000, 0x00010000, 
    0xFCFFFFFF, 0xFFFE793C, 
    0xEF080C0F, 0x00504340, 
    0xB8000000, 0x00000000
};

s8 D_800E3670 = 0;
s16 D_800E3674 = 0;
s32 D_800E3678 = 0;
s32 D_800E367C = 0;
s32 D_800E3680 = 1;

/*******************************/

/************ .bss ************/

extern s8 D_8012A788;
extern u8 D_8012A789;
extern u16 D_8012A7B6;
extern s32* D_8012A7C8;

/*****************************/

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

s32 func_800C3400(void) {
    s32 result = 0;
    if (D_800E3670 != 0) {
        if (D_8012A789 != 0) {
            result = 1;
            if (D_8012A788 != 0) {
                result = 2;
            }
        }
    }
    return result;
}


GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3440.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3564.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C38B4.s")
