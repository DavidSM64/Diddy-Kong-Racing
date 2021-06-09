/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x80077450 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

/************ .data ************/

s16 D_800DE490[16] = {
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

u8 D_800DE4B0 = 0;
u8 D_800DE4B4 = 0;
u8 D_800DE4B8 = 0;
s32 D_800DE4BC = 0x00010001;

u32 D_800DE4C0 = 0x40;
u32 D_800DE4C4 = 0;
u32 D_800DE4C8 = 0;
s32 D_800DE4CC = 0;

u32 D_800DE4D0 = 0;
s32 D_800DE4D4 = 0;
s32 D_800DE4D8 = 0;
s32 D_800DE4DC = 0;

// Fast3D (F3DDKR) display list
u32 D_800DE4E0[] = {
    0xB6000000, 0x001F3204,
    0xBB000000, 0x00000000,
    0xB7000000, 0x00000204,
    0xBC000404, 0x00000002,
    0xBC000C04, 0x00000002,
    0xBC001404, 0x0000FFFE,
    0xBC001C04, 0x0000FFFE,
    0xB8000000, 0x00000000
};

// Fast3D (F3DDKR) display list
u32 D_800DE520[] = {
    0xBA001402, 0x00000000,
    0xBA001701, 0x00800000,
    0xBA001001, 0x00000000,
    0xBA000E02, 0x00000000,
    0xBA001102, 0x00000000,
    0xBA001301, 0x00080000,
    0xBA000C02, 0x00002000,
    0xBA000903, 0x00000C00,
    0xFCFFFFFF, 0xFFFCF87C,
    0xBA000801, 0x00000000,
    0xB9000002, 0x00000000,
    0xB900031D, 0x0F0A4000,
    0xBA000602, 0x00000000,
    0xE7000000, 0x00000000,
    0xB8000000, 0x00000000
};

// Fast3D (F3DDKR) display list
u32 D_800DE598[] = {
    0xE7000000, 0x00000000,
    0xBA001001, 0x00000000,
    0xBA000E02, 0x00000000,
    0xB9000002, 0x00000000,
    0xB6000000, 0x00010001,
    0xE7000000, 0x00000000,
    0xFCFFFFFF, 0xFFFCF279,
    0xEF000C0F, 0x0F0A4000,
    0xB8000000, 0x00000000
};

// Fast3D (F3DDKR) display list
u32 D_800DE5E0[] = {
    0xE7000000, 0x00000000,
    0xBA001001, 0x00000000,
    0xBA000E02, 0x00000000,
    0xB9000002, 0x00000000,
    0xB6000000, 0x00010001,
    0xE7000000, 0x00000000,
    0xFCFFFFFF, 0xFFFDF6FB,
    0xEF000C0F, 0x0F0A4000,
    0xB8000000, 0x00000000
};

// Fast3D (F3DDKR) display list
u32 D_800DE628[] = {
    0xE7000000, 0x00000000,
    0xBA001001, 0x00000000,
    0xBA000E02, 0x00000000,
    0xB9000002, 0x00000000,
    0xB6000000, 0x00010001,
    0xE7000000, 0x00000000,
    0xFC119623, 0xFF2FFFFF,
    0xEF000C0F, 0x00504240,
    0xB8000000, 0x00000000
};

// Fast3D (F3DDKR) display list
u32 D_800DE670[] = {
    0xE7000000, 0x00000000,
    0xBA001001, 0x00000000,
    0xBA000E02, 0x00000000,
    0xB9000002, 0x00000000,
    0xB6000000, 0x00010001,
    0xE7000000, 0x00000000,
    0xB8000000, 0x00000000
};

// Fast3D (F3DDKR) display list
u32 D_800DE6A8[] = {
    0xFC119623, 0xFF2FFFFF,
    0xEF002C0F, 0x00552048,
    0xFC119623, 0xFF2FFFFF,
    0xEF002C0F, 0x0F0A4000,
    0xFC119623, 0xFF2FFFFF,
    0xEF000C0F, 0x00552048,
    0xFC119623, 0xFF2FFFFF,
    0xEF000C0F, 0x0F0A4000
};

// Fast3D (F3DDKR) display list
u32 D_800DE6E8[] = {
    0xFC119623, 0xFF2FFFFF,
    0xEF002C0F, 0x005041C8,
    0xFC119623, 0xFF2FFFFF,
    0xEF002C0F, 0x00504240,
    0xFC119623, 0xFF2FFFFF,
    0xEF000C0F, 0x005041C8,
    0xFC119623, 0xFF2FFFFF,
    0xEF000C0F, 0x00504240
};

/*******************************/

/************ .bss ************/

s32 D_801242A0[256];
s32 D_801246A0[1536];
OSMesgQueue  D_80125EA0;
OSMesg       D_80125EB8;
OSMesgQueue  D_80125EC0;
OSMesgQueue  D_80125ED8;
OSMesg       D_80125EF0;
s32          D_80125EF8[6];
OSMesg       D_80125F10;
s32          D_80125F18[6];
s8 D_80125F30;
s8 D_80125F31;
s8 D_80125F32;
s8 D_80125F33;
s8 D_80125F34;
s8 D_80125F35;
s8 D_80125F36;
s8 D_80125F37;
s32 D_80125F38;
s32 D_80125F3C;
s32 D_80125F40[56];
s32 D_80126020[56];
u32 D_80126100;

/*******************************/

GLOBAL_ASM("asm/non_matchings/unknown_078050/setupOSTasks.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077A54.s")

void func_80077B34(u8 arg0, u8 arg1, u8 arg2){
    D_800DE4B0 = arg0;
    D_800DE4B4 = arg1;
    D_800DE4B8 = arg2;
}

GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077B5C.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80077B9C.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078054.s")



#if 1
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_800780DC.s")
#else
typedef struct{
    u32 unk00;
    u32* unk04;
} struct_800780DC_a0;

void func_800780DC(struct_800780DC_a0** arg0){
    u32* tmp2= D_800DE4E0;
    struct_800780DC_a0* tmp = *arg0;
    

    *arg0 = *arg0 + 1;
    tmp->unk00 = 0x6000000;
    tmp->unk04 = tmp2;
}
#endif


void func_80078100(void){
    D_80126100 = func_8007957C();
    osCreateMesgQueue(&D_80125EA0, &D_80125EB8,1);
    osCreateMesgQueue(&D_80125EC0, &D_80125EF0,8);
    osCreateMesgQueue(&D_80125ED8, &D_80125F10,8);
    
}

void func_80078170(u32 arg0, u32 arg1, u32 arg2){
    D_800DE4C4 = arg0;
    D_800DE4C8 = arg1;
    D_800DE4C0 = arg2 << 2;
}


GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078190.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_800787FC.s")

void func_80078AAC(u32 arg0){
    D_800DE4D0 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078AB8.s")
GLOBAL_ASM("asm/non_matchings/unknown_078050/func_80078D00.s")
