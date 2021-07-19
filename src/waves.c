/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800B7D20 */

#include "types.h"
#include "macros.h"
#include "libultra_internal.h"

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

/*******************************/

/************ .rodata ************/

const char D_800E9160[] = "\nCouldn't find a block to pick wave details from.\nUsing block 0 as default.";
const char D_800E91AC[] = "\n\nBlock may be specified using 'P' on water group node.";
const char D_800E91E4[] = "\nError :: can not remove a wave swell object which doesn't exist !";
const char D_800E9228[] = "\nError :: more than eight swells overlap on column %d.";
const char D_800E9260[] = "\nError :: can not add another wave swell, reached limit of %d.";

/*********************************/

/************ .bss ************/

s32 D_80129FC0;
s32 D_80129FC4;
s32 D_80129FC8;
s32 D_80129FCC;
s32 D_80129FD0[4];
s32 D_80129FE0[2];
s32 D_80129FE8;
s32 D_80129FF0[6];
s32 D_8012A008;
s32 D_8012A00C;
s32 D_8012A010;
s32 D_8012A014;
s32 D_8012A018;
s32 D_8012A01C;
s32 D_8012A020[2];
s32 D_8012A028[20];
s32 D_8012A078;
s32 D_8012A07C;
s32 D_8012A080;
s32 D_8012A084;
s32 D_8012A088;
s32 D_8012A08C;
s32 D_8012A090;
s32 D_8012A094;
s32 D_8012A098;
s32 D_8012A09C;
s32 D_8012A0A0;
s32 D_8012A0A4;
s32 D_8012A0A8;
s32 D_8012A0AC;
s32 D_8012A0B0;
s32 D_8012A0B4;
s32 D_8012A0B8;
s32 D_8012A0BC;
s32 D_8012A0C0;
s32 D_8012A0C4;
s32 D_8012A0C8;
s32 D_8012A0CC;
s32 D_8012A0D0;
s32 D_8012A0D4;
s32 D_8012A0D8;
s32 D_8012A0DC;
s32 D_8012A0E0;
s32 D_8012A0E8[64];
s16 D_8012A1E8[512];
s32 D_8012A5E8[3];
s32 D_8012A5F4;
s32 D_8012A5F8;
s32 D_8012A5FC;
s32 D_8012A600[72];
s32 D_8012A720;
s32 D_8012A724;
s32 D_8012A728[2];

/*****************************/

u8* allocate_from_main_pool_safe(s32 arg0, s32 arg1);
void free_from_memory_pool(s32* arg0);
void free_texture(s32* arg0);
void func_800C5494(s32 arg0);
void func_800C5620(s32 arg0);

void func_800B7D20(void) {
    if (D_800E3040 != NULL) {
        free_from_memory_pool(D_800E3040);
        D_800E3040 = NULL;
    }
    if (D_800E3044 != NULL) {
        free_from_memory_pool(D_800E3044);
        D_800E3044 = NULL;
    }
    if (D_800E3048 != NULL) {
        free_from_memory_pool(D_800E3048);
        D_800E3048 = NULL;
    }
    if (D_800E304C != NULL) {
        free_from_memory_pool(D_800E304C);
        D_800E304C = NULL;
    }
    if (D_800E3070[0] != NULL) {
        free_from_memory_pool(D_800E3070[0]);
        D_800E3070[0] = NULL;
    }
    if (D_800E3080[0] != NULL) {
        free_from_memory_pool(D_800E3080[0]);
        D_800E3080[0] = NULL;
    }
    if (D_800E30D0 != NULL) {
        free_texture(D_800E30D0);
        D_800E30D0 = NULL;
    }
    if (D_800E30D4 != NULL) {
        free_from_memory_pool(D_800E30D4);
        D_800E30D4 = NULL;
    }
    if (D_800E30D8 != NULL) {
        free_from_memory_pool(D_800E30D8);
        D_800E30D8 = NULL;
    }
    if (D_800E3178 != NULL) {
        free_from_memory_pool(D_800E3178);
        D_800E3178 = NULL;
    }
    D_800E3190 = NULL;
    D_800E3194 = NULL;
    D_800E3184 = NULL;
    D_800E3188 = NULL;
}

GLOBAL_ASM("asm/non_matchings/waves/func_800B7EB4.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800B8134.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800B82B4.s")

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

GLOBAL_ASM("asm/non_matchings/waves/func_800B8C04.s")

s32 func_800B9228(unk800DC918_04 * arg0){
    s32 v0 = 0;
    s32 result = 0;
    while(v0 < D_8012A0E0 && arg0 != D_800E30D8[v0].unk00){
        v0++;
    };
    if(D_800E30D4[D_800E30D8[v0].unk0C]){ 
        result = 1;
        D_8012A1E8[D_800E30DC++] = v0;
    }
    return result;
}

GLOBAL_ASM("asm/non_matchings/waves/func_800B92F4.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800B97A8.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800B9C18.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BA288.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BA4B8.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BA8E4.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BB2F4.s")

void func_800BBE08(void);
void func_800BBF78(s32 arg0);

void func_800BBDDC(s32 arg0) {
    func_800BBE08();
    func_800BBF78(arg0);
}

GLOBAL_ASM("asm/non_matchings/waves/func_800BBE08.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BBF78.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BC6C8.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BCC70.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BDC80.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BE654.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BEEB4.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BEFC4.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BF3E4.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BF524.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BF634.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BFE98.s")
GLOBAL_ASM("asm/non_matchings/waves/func_800BFFDC.s")
