/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8009ECF0 */

#include "types.h"
#include "macros.h"
#include "structs.h"

typedef struct {
    u8 unk0[0x4C4];
    u16 unk4C4;
} unk80126CDC;

typedef struct {
    u8 unk0[0x4C];
    s8 unk4C;
} unk80126D60;

typedef struct {
    s16 unk0;
    s16 unk2;
} unk80127BF8;

extern u32 osTvType;

/************ .data ************/

// Unused?
s32 D_800E1E60 = 0;

typedef struct unk800E1E64 {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
} unk800E1E64;

unk800E1E64 D_800E1E64[59] = {
    { 0, 0, 1.0f, 53.0f, 16.0f, 0, 127, 0 },
    { 0, 3, 1.0f, 54.0f, 18.0f, 0, 0, 0 },
    { 0, 1, 0.4f, -120.0f, -68.0f, 0, 0, 0 },
    { 0, 6, 1.0f, 104.0f, 16.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 93.0f, 31.0f, 0, 0, 0 },
    { 0, 4, 1.0f, 104.0f, 32.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 114.0f, 31.0f, 0, 0, 0 },
    { 0, 8, 0.5f, -3.0f, 73.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 182.0f, 22.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 192.0f, 22.0f, 0, 0, 0 },
    { 0, 13, 1.0f, 239.0f, 16.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 206.0f, 31.0f, 0, 0, 0 },
    { 0, 7, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 22, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 5, 1.0f, -200.0f, 30.0f, 0, 0, 0 },
    { 0, 14, 1.0f, 0.0f, 0.0f, 0, 0, 0 },
    { 0, 16, 1.0f, -50.0f, 87.0f, 0, 0, 0 },
    { 0, 17, 2.0f, -50.0f, 87.0f, 0, 0, 0 },
    { 0, 18, 1.0f, 167.0f, 22.0f, 0, 0, 0 },
    { 0, 19, 1.0f, -127.0f, 88.0f, 0, 0, 0 },
    { 0, 18, 1.0f, 52.0f, 27.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 67.0f, 27.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 77.0f, 27.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 221.0f, 48.0f, 0, 0, 0 },
    { 0, 6, 1.0f, 188.0f, 48.0f, 0, 0, 0 },
    { 0, 10, 1.0f, 206.0f, 48.0f, 0, 0, 0 },
    { 0, 20, 0.4f, -105.0f, -98.0f, 0, 0, 0 },
    { 0, 21, 0.5f, -3.0f, 73.0f, 0, 0, 0 },
    { 0, 23, 1.0f, -8.0f, 97.0f, 0, 0, 0 },
    { 0, 24, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 25, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 26, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 2, 1.0f, 25.0f, 48.0f, 0, 0, 0 },
    { 0, 32, 1.0f, -120.0f, 30.0f, 0, 0, 0 },
    { 0, 34, 0.4f, -105.0f, -98.0f, 0, 0, 0 },
    { 0, 35, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 36, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 40, 1.0f, 80.0f, -60.0f, 0, 0, 0 },
    { 0, 1687158830, 0.5f, 122.0f, -71.0f, 0, 0, 0 },
    { 0, 47, 0.75f, 247.0f, 212.0f, 0, 0, 0 },
    { 0, 48, 1.0f, 234.0f, 196.0f, 0, 0, 0 },
    { 0, 49, 1.0f, 232.0f, 177.0f, 0, 0, 0 },
    { 0, 50, 1.0f, 240.0f, 159.0f, 0, 0, 0 },
    { 0, 51, 1.0f, 256.0f, 146.0f, 0, 0, 0 },
    { 0, 52, 1.0f, 275.0f, 143.0f, 0, 0, 0 },
    { 0, 53, 1.0f, 246.0f, 156.0f, 0, 0, 0 },
    { 0, 54, 0.7272f, 27.0f, 142.0f, 0, 0, 0 },
    { 0, 0, 1.0f, -200.0f, 70.0f, 0, 129, 0 },
    { 0, 3, 1.0f, -175.0f, 72.0f, 0, 0, 0 },
    { 0, 55, 1.0f, -99.0f, -89.0f, 0, 0, 0 },
    { 0, 56, 0.76f, 43.0f, 20.0f, 0, 0, 0 },
    { 0, 66, 1.0f, 40.0f, 54.0f, 0, 0, 0 },
    { 0, 8, 0.375f, -117.0f, 46.0f, 0, 0, 0 },
    { 0, 28, 1.0f, 51.0f, 56.0f, 0, 0, 0 },
    { 0, 10, 1.0f, 60.0f, 57.0f, 0, 0, 0 },
    { 0, 10, 1.0f, 69.0f, 57.0f, 0, 0, 0 },
    { 0, 67, 1.0f, -160.0f, 5.0f, 0, 0, 0 },
    { 0, 56, 1.0f, 260.0f, 16.0f, 0, 0, 0 },
    { 0, 68, 1.0f, 160.0f, 5.0f, 0, 0, 0 },
};

u16 D_800E25C4[96] = {
    0x0000, 0x0035, 0x0010, 0x0001, 0x0036, 0x0012, 0x0004, 0x00CB, 
    0x0013, 0x0005, 0x00D3, 0x0013, 0x0006, 0x00DC, 0x0013, 0x0002, 
    0xFF88, 0xFFE1, 0x001B, 0x0021, 0x0016, 0x0008, 0x00D3, 0x0013, 
    0x0009, 0x00DC, 0x0013, 0x000B, 0x00A7, 0x0013, 0x000E, 0x0000, 
    0x000A, 0x0010, 0x003B, 0x0023, 0x0011, 0x003B, 0x0023, 0x0007, 
    0x0021, 0x0016, 0x001C, 0x001E, 0x002A, 0x0012, 0x00CA, 0x0013, 
    0x000D, 0x0000, 0x000A, 0x000C, 0x0000, 0x000A, 0x0023, 0x0000, 
    0x000A, 0x0024, 0x0000, 0x000A, 0x001E, 0x0000, 0x000A, 0x001F, 
    0x0000, 0x000A, 0x001D, 0x0000, 0x000A, 0x002F, 0xFF38, 0x0023, 
    0x0030, 0xFF51, 0x0025, 0x0031, 0xFF96, 0xFFD3, 0x0003, 0x00B4, 
    0x0013, 0x0032, 0x0107, 0x0011, 0x0020, 0x00F7, 0x002D, 0x0033, 
    0x0103, 0x0031, 0x002E, 0x0022, 0x0047, 0xFFFF, 0xFFFF, 0xFFFF
};

u16 D_800E2684[118] = {
    0x0000, 0x002D, 0x0010, 0x0087, 0x0004, 0x005E, 0x0013, 0x004E, 
    0x0005, 0x0066, 0x0013, 0x0056, 0x0006, 0x006F, 0x0013, 0x005F, 
    0x0002, 0xFFD1, 0xFFDC, 0x0024, 0x001B, 0x0000, 0x0016, 0xFFE3, 
    0x0007, 0x0000, 0x0016, 0xFFE3, 0x0008, 0x0061, 0x0013, 0x0044, 
    0x0009, 0x006A, 0x0013, 0x004D, 0x000B, 0x0037, 0x0013, 0x001A, 
    0x000C, 0x0000, 0x000A, 0x0000, 0x000D, 0x0000, 0x000A, 0x0000, 
    0x000E, 0xFF60, 0x000A, 0xFF60, 0x0010, 0x0066, 0x0013, 0x0056, 
    0x0011, 0x0066, 0x0013, 0x0056, 0x0012, 0x0058, 0x0013, 0x003B, 
    0x001C, 0xFFFD, 0x002A, 0xFFE0, 0x0020, 0x0012, 0x002D, 0x0078, 
    0x001E, 0xFFEA, 0x000A, 0xFFEA, 0x001F, 0x000C, 0x000A, 0x0010, 
    0x001D, 0x0000, 0x000A, 0xFFD9, 0x0023, 0x0000, 0x000A, 0x0000, 
    0x0024, 0x0000, 0x000A, 0x0000, 0x002F, 0xFF38, 0x0019, 0xFFD8, 
    0x0030, 0xFF51, 0x001B, 0xFFF1, 0x0031, 0xFFDF, 0xFFCE, 0x0032, 
    0x0003, 0x0047, 0x0013, 0x0037, 0x0033, 0x003C, 0x0014, 0x003C, 
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000
};

// This is probably not right.
u8 D_800E2770[32] = {
    0, 0xFD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

s8 D_800E2790 = 1;

s8 D_800E2794[16] = {
    1, 1, 1, 1, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2
};

s8 D_800E27A4[4] = {
    1, 1, 1, 1
};

s8 D_800E27A8 = 1;

s8 D_800E27AC[12] = {
    -1, 40, 40, -2, 
    40, -1, 40, -2,
    40, 40, -1, -2
};

s32 D_800E27B8 = 0;

u8 D_800E27BC[120] = {
    0xFF, 0xA0, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x80, 
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xAF, 0x00, 0x00, 
    0xFF, 0x80, 0xFF, 0x00, 0x00, 0xFF, 0x80, 0xBE, 
    0x80, 0x80, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x40, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x40, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

s32 D_800E2834 = -2;

f32 D_800E2838 = 0.0f;

// Unused?
s32 D_800E283C[5] = {
    0x06FFFFFF, 0x000FFFFF, 0x06000000, 0x0014FFFF, 
    0x00000000
};

// D_800E28D8 is also unk800E2850

/* Size: 0x2C Bytes */
typedef struct unk800E2850 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
} unk800E2850;

unk800E2850 D_800E2850[3] = {
    { 0,  0x40, 0, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 },
    { 0, 0x100, 1, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 },
    { 0,  0x08, 2, 0xFE000000, 0xFE000000, 0xFE000000, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 4, 4, 8, 8 }
};

s32 D_800E28D4 = 0;

unk800E2850 D_800E28D8 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Not sure about typing for the following.
s32 D_800E2904 = 0;
s32 D_800E2908 = 0;
s32 D_800E290C = 0;
s32 D_800E2910 = 0;
s32 D_800E2914[2] = { 0, 0 };
s32 D_800E291C = 0;
s32 D_800E2920[2] = { 0, 0 };

// Fast3D (F3DDKR) display list
u32 D_800E2928[] = {
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

/* Size: 0x10 Bytes */
typedef struct unk800E2980 {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    f32 unk8;
    f32 unkC;
} unk800E2980;

unk800E2980 D_800E2980[2] = {
    { 1, 0xFFFF, 0xC090, 3.0f, 0.0f },
    { 0,      0,      0, 0.0f, 0.0f }
};

unk800E2980 D_800E29A0[4] = {
    { 3, 0xFFFF, 0x0090, 0.75f,  -32.0f },
    { 2, 0x0050, 0xFF60,  0.8f,  -96.0f },
    { 2, 0x00FF, 0x0090, 0.75f, -192.0f },
    { 0,      0,      0,  0.0f,    0.0f }
};

unk800E2980 D_800E29E0[5] = {
    { 3, 0xFF80, 0x1490, 0.65f,  -64.0f },
    { 2, 0xFFFF, 0xFF90,  1.0f, -128.0f },
    { 3, 0xFFFF, 0x8090,  0.5f, -176.0f },
    { 3, 0xFF28, 0x2890, 0.75f, -224.0f },
    { 0,      0,      0,  0.0f,    0.0f }
};

unk800E2980 D_800E2A30[5] = {
    { 3, 0xFF80, 0xFF80,  0.5f,  -64.0f },
    { 1, 0xFFFF, 0xC090, 0.75f, -128.0f },
    { 2, 0xFF28, 0x0080,  0.6f, -176.0f },
    { 1, 0xFFC0, 0xFF90, 0.75f, -224.0f },
    { 0,      0,      0,  0.0f,    0.0f }
};

s32 D_800E2A80 = 0;
s32 D_800E2A84 = 1;
s32 D_800E2A88 = 0;
f32 D_800E2A8C = -200.0f;
f32 D_800E2A90 = 200.0f;
f32 D_800E2A94 = 200.0f;
f32 D_800E2A98 = 200.0f;
f32 D_800E2A9C = 200.0f;
f32 D_800E2AA0 = -200.0f;
f32 D_800E2AA4 = -200.0f;
f32 D_800E2AA8 = -200.0f;

s16 D_800E2AAC[80] = {
    0, 0, 0, -1, -1, 0, 0, 0, 
    -1, -1, 0, 0, 0, -1, -1, 0, 
    0, 0, -1, -1, 0, 0, 0, -1, 
    -1, 0, 0, 0, -1, -1, 0, 0, 
    0, -1, -1, 0, 0, 0, -1, -1, 
    0, 0, 0, -1, -1, 0, 0, 0, 
    -1, -1, 0, 0, 0, -1, -1, 0, 
    0, 0, -1, -1, 0, 0, 0, -1, 
    -1, 0, 0, 0, -1, -1, 0, 0, 
    0, -1, -1, 0, 0, 0, -1, -1
};

/* Size: 0x1C Bytes */
typedef struct unk800E2B4C {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
} unk800E2B4C;

unk800E2B4C D_800E2B4C[8] = {
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 },
    { 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0 }
};

/* Size: 0x18 Bytes */
typedef struct unk800E2C2C {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s32 unk8;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} unk800E2C2C;

unk800E2C2C D_800E2C2C[2] = {
    { 0, 0x400, 0x400, 0x000AFFC4, 0, 0x80FF, 0xFF80, 0x80FF, 0x8000 },
    { 0, 0x600, 0x600, 0x0020FF40, 0, 0xFFFF, 0xFF00, 0x80FF, 0xFF00 }
};

s32 D_800E2C5C = 0;
s32 D_800E2C60 = 0x00010000;
s32 D_800E2C64 = 0;
s32 D_800E2C68 = 0x00010000;
s32 D_800E2C6C = 0x00010000;
s32 D_800E2C70 = 0;
s32 D_800E2C74 = 0x00010000;
s32 D_800E2C78 = 0;
s32 D_800E2C7C = 0;
s32 D_800E2C80 = 0;
s32 D_800E2C84 = 0;
s32 D_800E2C88 = 0;
s32 D_800E2C8C = 0;
s32 D_800E2C90 = 0;
s32 D_800E2C94 = 0;

s16 D_800E2C98[4] = {
    0x40FF, 0xFFFF, 0x0005, 0x0002
};

/*******************************/

/************ .bss ************/

u8 D_80126CD0;
u8 D_80126CD1;
u8 D_80126CD2;
u8 D_80126CD3;
u8 D_80126CD4;
u8 D_80126CD5;
s32 D_80126CD8;
unk80126CDC* D_80126CDC;
s32 D_80126CE0;
s32 D_80126CE4;
s32 D_80126CE8;
s32 D_80126CEC;
s32 D_80126CF0;
s32 D_80126CF4;
s32 D_80126CF8;
s32 D_80126CFC;
s32 D_80126D00;
s32 D_80126D04;
s32 D_80126D08;
s32 D_80126D0C;
s32 D_80126D10;
s32 D_80126D14;
s32 D_80126D18;
s32 D_80126D1C;
s32 D_80126D20;
s32 D_80126D24;
s32 D_80126D28;
s32 D_80126D2C;
s32 D_80126D30;
u8 D_80126D34;
u8 D_80126D35;
u8 D_80126D36;
u8 D_80126D37;
s32 D_80126D38;
s32 D_80126D3C;
s32 D_80126D40;
s32 D_80126D44;
s32 D_80126D48;
s32 D_80126D4C;
s32 D_80126D50;
u8 D_80126D54;
u8 D_80126D55;
u8 D_80126D56;
s32 D_80126D58;
s32 D_80126D5C;
unk80126D60* D_80126D60;
u8 D_80126D64;
u8 D_80126D65;
u8 D_80126D66;
u8 D_80126D67;
u8 D_80126D68;
u8 D_80126D69;
s32 D_80126D6C;
u8 D_80126D70;
u8 D_80126D71;
s32 D_80126D74;
s32 D_80126D78;
u16 D_80126D7C;
s32 D_80126D80;
s32 D_80126D84;
s32 D_80126D88[254];
s32 D_80127180;
s32 D_80127184;
u8 D_80127188;
u8 D_80127189;
u8 D_8012718A;
u8 D_8012718B;
s32 D_8012718C;
s32 D_80127190;
s32 D_80127194;
s32 D_80127198[6];
s32 D_801271B0[640];
s32 D_80127BB0;
s32 D_80127BB4;
s32 D_80127BB8[16];
unk80127BF8 D_80127BF8;
s32 D_80127BFC;
s32 D_80127C00;
s32 D_80127C04;
s32 D_80127C08;
s32 D_80127C0C;
s32 D_80127C10;
s32 D_80127C14;
s32 D_80127C18;
s32 D_80127C1C;
s32 D_80127C20;
s32 D_80127C24;
s32 D_80127C28;
s32 D_80127C2C;
s32 D_80127C30[4];
s32 D_80127C40[16];

/******************************/

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_8009ECF0.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_8009F034.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A003C.s")

u8 func_800A0190(void) {
    return D_80126D34;
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A01A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A0B74.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A0BD4.s")

typedef struct {
    u8 unk0[0x64];
    s32* unk64;
} unk800A0DC0;

typedef struct {
    u8 unk0[0x1D8];
    s8 unk1D8;
} unk800A0DC0_2;

void func_800A0DC0(s32 arg0, unk800A0DC0* arg1, s32 arg2) {
    unk800A0DC0_2* temp = arg1->unk64;

    func_80068508(1);
    func_800A0EB4(temp, arg2);
    func_800A5A64(temp, arg2);
    func_800A3CE4(arg0, arg2);

    if (D_80126D60->unk4C == 0) {
        func_800A4F50(temp, arg2);
    }

    func_800A4154(temp, arg2);
    func_800A7B68(temp, arg2);
    func_800A4C44(temp, arg2);
    func_800A3884(arg1, arg2);

    if (D_80127188 != 0 && temp->unk1D8 == 0) {
        func_800A47A0(temp, arg2);
    }

    func_800A7520(arg1, arg2);
    func_80068508(0);
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A0EB4.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A1248.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A1428.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A14F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A19A4.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A1C04.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A1E48.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A22F4.s")

void func_800A258C(s32 arg0, unk800A0DC0* arg1, s32 arg2) {
    LevelHeader* level;
    unk800A0DC0_2* temp = arg1->unk64;

    func_80068508(1);
    func_800A5A64(temp, arg2);
    func_800A3CE4(arg0, arg2);
    func_800A7B68(temp, arg2);
    func_800A7520(arg1, arg2);

    level = get_current_level_header();
    if (level->laps > 1) {
        func_800A4F50(temp, arg2);
    }

    func_800A3884(arg1, arg2);
    func_800A4C44(temp, arg2);
    func_80068508(0);
}

void func_800A263C(s32 arg0, unk800A0DC0* arg1, s32 arg2) {
    unk800A0DC0_2* temp = arg1->unk64;

    func_80068508(1);
    func_800A5A64(temp, arg2);
    func_800A4F50(temp, arg2);
    func_800A4C44(temp, arg2);
    func_800A7B68(temp, arg2);
    func_800A3CE4(arg0, arg2);
    func_800A3884(arg1, arg2);
    func_80068508(0);
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A26C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A277C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A36CC.s")

void func_800A3870(void) {
    D_80126CDC->unk4C4 = 0x6490;
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A3884.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A3CE4.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A4154.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A45F0.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A47A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A497C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A4C44.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A4F50.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A5A64.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A5F18.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A6254.s")

void func_800A6DB4(s16* arg0) {
    Settings* settings = get_settings();

    if (arg0 != NULL) {
        if (settings->racers[*arg0].best_times & 0x80) {
            func_80001D04(0x145, &D_80126D40);
        } else {
            func_80001D04(0x102, &D_80126D40);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A6E30.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A718C.s")

void func_800A7484(u16 arg0, f32 arg1, s32 arg2) {
    if (D_80126D74 == 0) {
        D_80126D7C = arg0;
        D_80126D74 = arg1 * 60.0f;
        D_80126D78 = arg2;
    }
}

void func_800A74EC(u16 arg0, s32 arg1) {
    if (arg0 == D_80126D7C && D_80126D78 == arg1) {
        D_80126D74 = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A7520.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A7A60.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A7B68.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A7FBC.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A83B4.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A8458.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800A8474.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AA3EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AA600.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AAFD0.s")

void func_800AB194(s32 arg0) {
    D_80126CD1 = 1;
    D_80126CD3 = arg0;
}

void func_800AB1AC(s32 arg0) {
    D_80126CD0 = D_8012718B;
    D_80126CD3 = arg0;
}

/* Unused? */
void func_800AB1C8(void) {
    D_80126CD4 = 0;
}

/* Last function of file */
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AB1D4.s")
//void func_800AB1D4(s32 arg0) {
//    D_80126CD2 = arg0 - 1;
//}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AB1F0.s")

void func_800AB308(s16 arg0, s16 arg1) {
    if (D_80127BF8.unk2 < D_80127BF8.unk0) {
        D_80127BF8.unk0 = arg0;
        D_80127BF8.unk2 = arg1;
    } else {
        D_80127BF8.unk0 = arg1;
        D_80127BF8.unk2 = arg0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AB35C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AB4A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ABB34.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ABC5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ABE68.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AC0C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AC21C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AC5A4.s")

void func_800AC880(s32 arg0) {
    if (arg0 == D_800E2A80) {
        D_800E2A80 = 0;
        D_800E2A84 = 1;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AC8A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ACA20.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ACF60.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ACF98.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD030.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD144.s")

void func_800AD220(void) {
    if (D_800E2C2C[0].unkC != 0) {
        func_8007B2BC(D_800E2C2C[0].unkC);
        D_800E2C88 = 0;
    }

    if (D_800E2C2C[1].unkC != 0) {
        func_8007B2BC(D_800E2C2C[1].unkC);
        D_800E2C88 = 0;
    }

    if (D_800E2C8C != 0) {
        func_8007CCB0(D_800E2C8C);
        D_800E2C8C = 0;
    }

    if (D_800E2C94 != 0) {
        func_800096F8(D_800E2C94);
        D_800E2C94 = 0;
    }

    D_800E2C5C = 0;
}

void func_800AD2C4(s32 arg0, s32 arg1, f32 arg2) {
    D_800E2C78 = osTvType == 0 ? 50.0 * arg2 : 60.0 * arg2;
    D_800E2C68 = arg0;
    D_800E2C64 = (D_800E2C68 - D_800E2C60) / D_800E2C78;
    D_800E2C74 = arg1;
    D_800E2C70 = (D_800E2C74 - D_800E2C6C) / D_800E2C78;
}

GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD40C.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD4B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800AD658.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ADAB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ADBC8.s")
GLOBAL_ASM("asm/non_matchings/unknown_09F8F0/func_800ADCBC.s")
