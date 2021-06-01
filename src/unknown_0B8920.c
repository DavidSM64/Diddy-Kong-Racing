/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B7D20 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

#define OS_PIM_STACKSIZE	4096

extern u32 __osPiAccessQueueEnabled; //__osPiAccessQueueEnabled
extern OSDevMgr __osPiDevMgr;
extern u8 piThreadStack[OS_PIM_STACKSIZE];//piThreadStack
extern OSThread piThread; //piThread
extern OSMesgQueue piEventQueue; //piEventQueue
extern OSMesg piEventBuf[1]; //piEventBuf
extern OSMesgQueue piAccessQueue; //piAccessQueue
void __osDevMgrMain(void);

/************ .data ************/

s32* D_800E3040 = NULL;
s32* D_800E3044 = NULL;
s32* D_800E3048 = NULL;
s32* D_800E304C = NULL;

// Could be an array of pointers?
s32 D_800E3050[8] = {
    0, 0, 0, 0, 0, 0, 0, 0
};

s32* D_800E3070[2] = { NULL, NULL };
s32* D_800E3078[2] = { NULL, NULL };

// This could also be D_800E3080[2] + D_800E3088[2]
s32* D_800E3080[4] = { NULL, NULL, NULL, NULL };

/* Size: 0x10, might just be an array? */
typedef struct unk800E3090 {
    s16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
} unk800E3090;

unk800E3090 D_800E3090[4] = {
    { 0x4000, 0x0201, 0, 0, 0, 0, 0, 0, },
    { 0x4001, 0x0203, 0, 0, 0, 0, 0, 0, },
    { 0x4000, 0x0201, 0, 0, 0, 0, 0, 0, },
    { 0x4001, 0x0203, 0, 0, 0, 0, 0, 0, }
};

s32* D_800E30D0 = NULL;
s32* D_800E30D4 = NULL;

typedef struct{
    u8 unk00;
    u8 pad01[0x05];
    u8  unk06;
    u8  unk07;
    u32 unk08;  
} unk800DC918_04_0C; //copied from unknown_0255E0.c

typedef struct{
    u8 pad00[0x0C];
    unk800DC918_04_0C* unk0C;
    u8 pad0C[0x10];
    s16 unk20;
    u8 pad22[0x09];
    s8 unk2B;
    u8 pad2C[0x14];
    u8 unk40;
    u8 pad41[0x3];
} unk800DC918_04; //copied from unknown_0255E0.c

typedef struct{
    unk800DC918_04 * unk00;
    u8 pad04[0x8];
    u32 unk0C;
    u8 pad10[0xC];
}unk800E30D8;


unk800E30D8 *D_800E30D8 = NULL;
s32 D_800E30DC = 0;
s32 D_800E30E0 = 0;
s32 D_800E30E4 = 0;

s16 D_800E30E8[10] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 0
};

s16 D_800E30FC[10] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 0
};

s16 D_800E3110[26] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 0
};

s16 D_800E3144[26] = {
    0, 1, 1, 1, 2, 3, 4, 4, 4, 5, 
    3, 4, 4, 4, 5, 3, 4, 4, 4, 5, 
    6, 7, 7, 7, 8, 0
};

s32 *D_800E3178 = NULL;
s32 D_800E317C = 0;
s32 D_800E3180 = 0;
s32 *D_800E3184 = NULL;
s32 *D_800E3188 = NULL;
s32 D_800E318C = 0;
s32 *D_800E3190 = NULL;
s32 *D_800E3194 = NULL;
s32 D_800E3198 = 0;
s32 D_800E319C = 0;
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
s32 D_800E3684 = 0; // Unused?
s32 D_800E3688 = 0; // Unused?
s32 D_800E368C = 0; // Unused?

// Fast3D (F3DDKR) display list
u32 D_800E3690[] = {
    0xE7000000, 0x00000000, 
    0xBA001001, 0x00000000, 
    0xBA000E02, 0x00000000, 
    0xB9000002, 0x00000000, 
    0xB6000000, 0x00010001, 
    0xE7000000, 0x00000000, 
    0xB8000000, 0x00000000, 
    0xFC5616AC, 0x112CFE7F, 
    0xEF000C0F, 0x00504240, 
    0xFCFFFFFF, 0xFFFEFB7D, 
    0xEF000C0F, 0x00504240
};

s8 D_800E36E8 = 0;

// Descending powers of 10
s32 D_800E36EC[9] = {
    1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10
}; 

s8 D_800E3710[48] = {
    4, 0, 0, 0, 1, 2, 0, 1, 0, 2, 1, 0, 2, 0, 4, 0, 
    0, 4, 1, -4, 1, 1, -4, 1, -2, 2, 1, -2, 1, -1, 4, 1, 
    -1, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

OSDevMgr __osPiDevMgr = { 0, NULL, NULL, NULL, NULL, NULL, NULL };

u8* D_800E3760 = NULL;
u8* D_800E3764 = NULL;
u8* gzip_inflate_input = NULL;
u8* gzip_inflate_output = NULL;

/*******************************/

/************ .rodata ************/

const char D_800E9160[] = "\nCouldn't find a block to pick wave details from.\nUsing block 0 as default.";
const char D_800E91AC[] = "\n\nBlock may be specified using 'P' on water group node.";
const char D_800E91E4[] = "\nError :: can not remove a wave swell object which doesn't exist !";
const char D_800E9228[] = "\nError :: more than eight swells overlap on column %d.";
const char D_800E9260[] = "\nError :: can not add another wave swell, reached limit of %d.";

const FloatLiteral D_800E92A0 = { 10000.0f };
const FloatLiteral D_800E92A4 = { -10000.0f };
const FloatLiteral D_800E92A8 = { 6.64f };
const FloatLiteral D_800E92AC = { 89128.961f };
const FloatLiteral D_800E92B0 = { 6.5333333f };
const FloatLiteral D_800E92B4 = { 89128.961f};
const FloatLiteral D_800E92B8 = { 6.64f };
const FloatLiteral D_800E92BC = { 89128.961f };
const FloatLiteral D_800E92C0 = { 6.5333333f };
const FloatLiteral D_800E92C4 = { 89128.961f };

// This is probably a file boundary.
const DoubleLiteral D_800E92C8 = { 0.0 };

// Jump table in func_800C01D8
const u32 D_800E92D0[] = {
    0x800C0310, 0x800C0320, 0x800C0370, 0x800C03C0, 
    0x800C03D0, 0x800C0420, 0x800C0470
};

// Jump table in func_800C0494
const u32 D_800E92EC[] = {
    0x800C056C, 0x800C0580, 0x800C0580, 0x800C0594, 
    0x800C0580, 0x800C0580, 0x800C05A8
};

const FloatLiteral D_800E9308 = { 1.4f };
const FloatLiteral D_800E930C = { 1.2f };

// Jump table in func_800C05C8
const u32 D_800E9310[] = {
    0x800C0680, 0x800C0694, 0x800C06A8, 0x800C06BC, 
    0x800C06D0, 0x800C06E4, 0x800C06F8
};

const FloatLiteral D_800E932C = { 1.2f };

// Jump table in func_800C38B4
const u32 D_800E9330[] = {
    0x800C3958, 0x800C3984, 0x800C3A30, 0x800C3AA8,
    0x800C3ADC, 0x800C3B00, 0x800C3B2C, 0x800C3B50,
    0x800C3B88, 0x800C3BA0
};

// This is probably a file boundary.
const DoubleLiteral D_800E9358 = { 0.0 };

// Jump table in func_800C45A4
const u32 D_800E9360[] = {
    0x800C4A88, 0x800C4A78, 0x800C4AD0, 0x800C4AE8, 
    0x800C4ADC, 0x800C4AE8, 0x800C4AE8, 0x800C4AE8, 
    0x800C4AE8, 0x800C4AE8, 0x800C4AE8, 0x800C4AE8, 
    0x800C4AE8, 0x800C4AE8, 0x800C4AE8, 0x800C4AE8, 
    0x800C4AE8, 0x800C4AE8, 0x800C4AE8, 0x800C4AE8, 
    0x800C4AE8, 0x800C4AE8, 0x800C4AE8, 0x800C4A6C
};


/*********************************/

/************ .bss ************/

extern s32 D_8012A0D8;
extern s32 D_8012A0DC;
extern s8 D_8012A788;
extern u8 D_8012A789;
extern u16 D_8012A7B6;
extern s32* D_8012A7C8;
extern s32 D_8012A7E0;

/* Size: 0x28 bytes */
typedef struct unk8012A7E8_24 {
    u8 unk00;
    u8 unk01;
    u8 pad02[0x1A];
    struct unk8012A7E8_24* unk1C;
} unk8012A7E8_24;

/* Size: 0x28 bytes */
typedef struct unk8012A7E8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s8 unk10;
    s8 unk11;
    s8 unk12;
    s8 unk13;
    s8 unk14;
    s8 unk15;
    s8 unk16;
    s8 unk17;
    s8 unk18;
    s8 unk19;
    s8 unk1A;
    s8 unk1B;
    s8 unk1C;
    s8 unk1D;
    u16 unk1E;
    s16 unk20;
    s16 unk22;
    unk8012A7E8_24 *unk24;
} unk8012A7E8;

extern unk8012A7E8 (*D_8012A7E8)[1];
extern s32 D_8012A7F0;
extern s8 D_8012A7F4;
extern s32 D_8012AAD8;
extern u32 gzip_num_bits;
extern u32 gzip_bit_buffer;

/*****************************/

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
    if (D_800E3070[0] != NULL) {
        func_80071140(D_800E3070[0]);
        D_800E3070[0] = NULL;
    }
    if (D_800E3080[0] != NULL) {
        func_80071140(D_800E3080[0]);
        D_800E3080[0] = NULL;
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

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B9228.s")
#else

extern s32 D_800E30DC;
extern s32 D_8012A0E0;
extern s16* D_8012A1E8;

s32 func_800B9228(unk800DC918_04 * arg0){
    s32 v0 = 0;
    s32 retval = 0;
    s32 tmp;
    while(v0 < D_8012A0E0 && arg0 != D_800E30D8[v0].unk00){
        v0++;
    };
    if(D_800E30D4[D_800E30D8[v0].unk0C]){ 
        //load array address differently;
        retval = 1;
        *(D_8012A1E8 + (tmp = D_800E30DC)) = v0;
        D_800E30DC = tmp + 1;
    }
    return retval;
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B92F4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B97A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800B9C18.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BA288.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BA4B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BA8E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800BB2F4.s")

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

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C3C00.s")
#else

extern u32* D_8012A7E4;
void func_800C3C00(void){
    s32 i;
    D_8012A7E4 = func_80076C58(44);
    D_8012A7E0 = *(D_8012A7E4++);
    for(i = 0; i< D_8012A7E0; i++){
        D_8012A7E0[]
    }
}
#endif


void func_800C4164(s32 arg0) {
    D_8012A7F0 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4170.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C422C.s")
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C42EC.s")

void func_800C4384(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    (*D_8012A7E8)[0].unk14 = arg0;
    (*D_8012A7E8)[0].unk15 = arg1;
    (*D_8012A7E8)[0].unk16 = arg2;
    (*D_8012A7E8)[0].unk17 = arg3;
    (*D_8012A7E8)[0].unk1C = arg4;
}

void func_800C43CC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    (*D_8012A7E8)[0].unk18 = arg0;
    (*D_8012A7E8)[0].unk19 = arg1;
    (*D_8012A7E8)[0].unk1A = arg2;
    (*D_8012A7E8)[0].unk1B = arg3;
}

void func_800C45A4(s32, unk8012A7E8*, s32, s32, f32);

// Unused?
void func_800C4404(s32 arg0, s32 arg1, s32 arg2) {
    func_800C45A4(arg0, *D_8012A7E8, arg1, arg2, 1.0f);
}

// This function is OK
void func_800C4440(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    unk8012A7E8 *temp = &(*D_8012A7E8)[0];
    temp->unk0 = (arg1 == -0x8000) ? temp->unkC >> 1 : arg1;
    temp->unk2 = (arg2 == -0x8000) ? temp->unkE >> 1 : arg2;
    func_800C45A4(arg0, temp, arg3, arg4, 1.0f);
}

void func_800C44C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg1 >= 0) {
        if(arg1 < 8){
            unk8012A7E8 *temp = &D_8012A7E8[arg1];
            func_800C45A4(arg0, temp, arg2, arg3, 1.0f);
        }
    }
}

void func_800C4510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg1 >= 0 && arg1 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg1];
        temp->unk0 = (arg2 == -0x8000) ? temp->unkC >> 1 : arg2;
        temp->unk2 = (arg3 == -0x8000) ? temp->unkE >> 1 : arg3;
        func_800C45A4(arg0, temp, arg4, arg5, 1.0f);
    }
}

// Has a jump table
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C45A4.s")

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C4DA0.s")

void func_800C4EDC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 > 0 && arg0 < 8) {
        // How is temp supposed to be setup for all of these functions? This is driving me nuts.
        unk8012A7E8 *temp = &D_8012A7E8[arg0]; // Issue with temp
        temp->unk0 = 0;
        temp->unk2 = 0;
        if (arg1 < arg3) {
            temp->unk4 = (s16) arg1;
            temp->unk8 = (s16) arg3;
        } else {
            temp->unk8 = (s16) arg1;
            temp->unk4 = (s16) arg3;
        }
        if (arg2 < arg4) {
            temp->unk6 = (s16) arg2;
            temp->unkA = (s16) arg4;
        } else {
            temp->unkA = (s16) arg2;
            temp->unk6 = (s16) arg4;
        }
        temp->unkC = (temp->unk8 - temp->unk4) + 1;
        temp->unkE = (temp->unkA - temp->unk6) + 1;
    }
}

void func_800C4F7C(s32 arg0, s32 arg1) {
    if (arg0 >= 0 && arg0 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg0];
        if (arg1 < D_8012A7E0) {
            temp->unk1D = arg1;
        }
    }
}


void func_800C4FBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 > 0 && arg0 < 8) {
        unk8012A7E8 *temp = &D_8012A7E8[arg0];
        temp->unk10 = arg1;
        temp->unk11 = arg2;
        temp->unk12 = arg3;
        temp->unk13 = arg4;
    }
}

void func_800C5000(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &D_8012A7E8[arg0];
    temp->unk14 = arg1;
    temp->unk15 = arg2;
    temp->unk16 = arg3;
    temp->unk17 = arg4;
    temp->unk1C = arg5;
}

void func_800C5050(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &D_8012A7E8[arg0]; // Issue with temp
    temp->unk18 = arg1;
    temp->unk19 = arg2;
    temp->unk1A = arg3;
    temp->unk1B = arg4;
}

// Unused?
void func_800C5094(s32 arg0, s32 arg1, s32 arg2) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &D_8012A7E8[arg0]; // Issue with temp
    temp->unk20 += arg1;
    temp->unk22 += arg2;
}

// Unused?
void func_800C50D8(s32 arg0) {
    unk8012A7E8 *temp;
    if (arg0 <= 0 || arg0 >= 8) {
        return;
    }
    temp = &D_8012A7E8[arg0]; // Issue with temp
    temp->unk20 = 0;
    temp->unk22 = 0;
}

// Unused?
// This function is OK
void func_800C510C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_800C5168(arg0, (*D_8012A7E8)[arg0].unk0, (*D_8012A7E8)[arg0].unk2, arg1, arg2, arg3);
}


GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5168.s")
#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5494.s")
#else
void func_800C5494(s32 arg0){
    unk8012A7E8 *tmp2 = &(*D_8012A7E8)[arg0];
    unk8012A7E8_24 *tmp = tmp2->unk24;
    if(tmp == NULL)
        return;
    
    while(tmp){
        tmp->unk01 = 255;
        tmp = tmp->unk1C;
    }
    tmp2->unk24 = NULL;
}

void func_800C54E8(s32 arg0, s16* arg1, u16 arg2, u16 arg3){
    s16 t4;
    s16 a3 = arg3;
    if(arg1 == 0 || (*D_8012A7E8)[arg0].unk19 == 255)
        return;
    t4 = arg1[6];
    switch(arg3){
        case 4: //L800C55E4;
            arg1[6] = 0;
            arg1[7] = 0;
            return;
        case 1: //L800C554C;
            a3 = arg3*1;
            break;
        case 2: //L800C5564;
        default: //L800C5564;
            break;
        
    }
    arg1[6] += arg2;
    arg1[7] += a3;
}
#endif


void func_800C55F4(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E |= 0x8000;
}

void func_800C5620(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E &= 0x7FFF;
}

// Unused?
void func_800C564C(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E |= 0x0001;
}

// Unused?
void func_800C5678(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E &= 0xFFFE;
}

// Unused?
void func_800C56A4(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E |= 0x4000;
}

void func_800C56D0(s32 arg0) {
    (*D_8012A7E8)[arg0].unk1E &= 0xBFFF;
}

void func_800C56FC(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    if (D_800E36E8 != 0) {
        D_8012A7F4--;
        if (D_8012A7F4 == 0) {
            func_8009E9A8();
            D_800E36E8 = 0;
        }
    }
    
    for(i = 1; i < 8; i++) {
        if ((*D_8012A7E8)[i].unk1E & 0x8000) {
            if ((*D_8012A7E8)[i].unk1E & 0x4000) {
                func_800C5B58(arg0, arg1, arg2, i);
            } else {
                func_800C5B58(arg0, 0, 0, i);
            }
        }
    }
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C580C.s")
#else

// sprintf like function, but only for decimal integers (%d).
void func_800C580C(char** outString, s32 number) {
    char digit;
    s32 i;
    s32 hasDigit; // boolean
    s32 div;
    
    // Check for a negative number
    if (number < 0) { 
        **outString = '-';
        number = -number;
        (*outString)++;
    }
    
    // Loop through digit places.
    for(i = 0; i < 9; i++){
        hasDigit = 0;
        digit = '0';
        if (number >= D_800E36EC[i]) {
            div = number / D_800E36EC[i];
            hasDigit = 1;
            digit = '0' + div;
            number -= div * D_800E36EC[i];
        }
        if (hasDigit) {
            **outString = digit;
            (*outString)++;
        }
    }

    // One's digit place
    **outString = '0' + number;
    (*outString)++;
}
#endif

//GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5AA0.s")
void func_800C5AA0(Gfx **dlist, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 temp_v0 = func_8007A520();
    if (arg3 >= 0 && arg1 < (temp_v0 & 0xFFFF) && arg4 >= 0 && arg2 < (temp_v0 >> 16)) {
        if (arg1 < 0) {
            arg1 = 0;
        }
        if (arg2 < 0) {
            arg2 = 0;
        }
        gDPFillRectangle((*dlist)++, arg1, arg2, arg3, arg4);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/func_800C5B58.s")

void func_800C580C(char**, s32);

void func_800C5F60(unsigned char *input, char *output, s32 number) {
    while (*input != '\0') {
        if ('~' == *input) { // ~ is equivalent to a %d.
            // output the number as part of the string
            func_800C580C(&output, number);
            input++;
        } else {
            *output = *input;
            input++;
            output++;
        }
    }
    *output = '\0'; // null terminator
}

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt)
{
	u32 savedMask;
	OSPri oldPri;
	OSPri myPri;
	if (!__osPiDevMgr.active)
	{
		osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
		osCreateMesgQueue(&piEventQueue, (OSMesg*)&piEventBuf, 1);
		if (!__osPiAccessQueueEnabled)
			__osPiCreateAccessQueue();
		osSetEventMesg(OS_EVENT_PI, &piEventQueue, (OSMesg)0x22222222);
		oldPri = -1;
		myPri = osGetThreadPri(NULL);
		if (myPri < pri)
		{
			oldPri = myPri;
			osSetThreadPri(NULL, pri);
		}
		savedMask = __osDisableInt();
		__osPiDevMgr.active = 1;
		__osPiDevMgr.thread = &piThread;
		__osPiDevMgr.cmdQueue = cmdQ;
		__osPiDevMgr.evtQueue = &piEventQueue;
		__osPiDevMgr.acsQueue = &piAccessQueue;
		__osPiDevMgr.dma = osPiRawStartDma;
        __osPiDevMgr.edma = osEPiRawStartDma;

		osCreateThread(&piThread, 0, __osDevMgrMain, &__osPiDevMgr, &piThreadStack[OS_PIM_STACKSIZE], pri);
		osStartThread(&piThread);
		__osRestoreInt(savedMask);
		if (oldPri != -1)
		{
			osSetThreadPri(NULL, oldPri);
		}
	}
}


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

s32 gzip_inflate_block(void);

u8* func_800C6218(u8* arg0, u8* arg1) {
    gzip_inflate_input = arg0 + 5; // The compression header is 5 bytes. 
    gzip_inflate_output = arg1;
    gzip_num_bits = 0;
    gzip_bit_buffer = 0;
    while(gzip_inflate_block() != 0) {} // Keep calling gzip_inflate_block() until it returns 0.
    return arg1;
}

GLOBAL_ASM("asm/non_matchings/unknown_0B8920/gzip_huft_build.s")
