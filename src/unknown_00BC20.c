/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8000B020 */

#include "unknown_00BC20.h"
#include "memory.h"

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "fast3d.h"
#include "asset_sections.h"

/************ .data ************/

unknown800DC6F0 D_800DC6F0 = { -128, 0x1E, 0x0F };
unknown800DC6F0 D_800DC6F8 = { 3, 0x1E, 0x0F };

s32 D_800DC700 = 0;
s32 D_800DC704 = 0; // Currently unknown, might be a different type.
s16 D_800DC708 = 0;
s32 D_800DC70C = 0; // Currently unknown, might be a different type.
s16 D_800DC710 = 1;
s32 D_800DC714 = 0; // Currently unknown, might be a different type.
s32 D_800DC718 = 0;
s8 D_800DC71C = 0;
s32 D_800DC720 = 0; // Currently unknown, might be a different type.
s16 D_800DC724 = 0x2A30;
s16 D_800DC728 = -1;
s16 D_800DC72C = 0;
u8 D_800DC730 = 0;
s32 D_800DC734 = 0; // Currently unknown, might be a different type.
u8 D_800DC738 = 0;
s8 D_800DC73C = 0;
s8 D_800DC740 = 0;
s8 D_800DC744 = 0;
s8 D_800DC748 = 0;
s32 D_800DC74C = 0; // Currently unknown, might be a different type.
s32 D_800DC750 = 0; // Currently unknown, might be a different type.
s32 D_800DC754 = 0; // Currently unknown, might be a different type.
s32 D_800DC758 = 0; // Currently unknown, might be a different type.
s32 D_800DC75C = 0; // Currently unknown, might be a different type.
s32 D_800DC760 = 9; // Currently unknown, might be a different type.
s32 D_800DC764 = 0; // Currently unknown, might be a different type.
s32 D_800DC768 = 0; // Currently unknown, might be a different type.

f32 D_800DC76C[15] = { 
    1.0f, 0.70711f, 0.70711f, 1.0f, 
    0.0f, 0.70711f, -0.70711f, 0.0f,
    -1.0f, -0.70711f, -0.70711f, -1.0f,
    0.0f, -0.70711f, 0.70711f
};

u16 D_800DC7A8[8] = { 
    0x0001, 0x0002, 0x0003, 0x0004, 
    0x0051, 0x0054, 0x0055, 0x0056
};

s16 D_800DC7B8[52] = {
    0x00ED, 0x00FF, 0x0037, 0x0038, 
    0x0039, 0x003A, 0x0057, 0x0058, 
    0x0059, 0x005A, 0x00F3, 0x00FD,
    0x0042, 0x0043, 0x0044, 0x0045,
    0x005B, 0x005C, 0x005D, 0x005E,
    0x00F4, 0x0101, 0x0001, 0x0002,
    0x0003, 0x0004, 0x0051, 0x0054,
    0x0055, 0x0056, 0x00ED, 0x00FF,
    0x0001, 0x0002, 0x0003, 0x0004,
    0x0051, 0x0054, 0x0055, 0x0056,
    0x00ED, 0x00FF, 0x00D9, 0x00DF,
    0x00E0, 0x0105, 0x008A, 0x00DA,
    0x00E8, 0x0115, 0x0118, 0x0000
};

s16 D_800DC820[16] = {
    0x0005, 0x0106, 0x0207, 0x0005,
    0x0106, 0x010B, 0x010B, 0x0207,
    0x000C, 0x020D, 0x0101, 0x0101,
    0x0101, 0x0101, 0x0101, 0x0000
};

s8 D_800DC840[8] = { 9, 1, 2, 3, 4, 5, 7, 0 };

s8 D_800DC848 = 0;
s32 D_800DC84C[3] = {         // Currently unknown, might be a different type.
    0xFF401000, 0x1040FF00, 0x10FF4000
};
s32 D_800DC858 = 0;           // Currently unknown, might be a different type.
s32 D_800DC85C = 0x0028FFFF;  // Currently unknown, might be a different type.

u8 D_800DC860 = 0x80;
u16 D_800DC864 = 0x0028;

/*******************************/

/************ .rodata ************/

const char D_800E4F60[] = "Objects out of ram(1) !!\n";
const char D_800E4F7C[] = "Door numbering error %d!!\n";
const char D_800E4F98[] = "objGetScope: Unknown scope for object %d\n";
const char D_800E4FC4[] = "ObjList (Part) Overflow %d!!!\n";
const char D_800E4FE4[] = "ObjSetupObject(1) Memory fail!!\n";
const char D_800E5008[] = "ObjSetupObject(2) Memory fail!!\n";
const char D_800E502C[] = "ObjSetupObject(5) Memory fail!!\n";
const char D_800E5050[] = "ObjSetupObject(6) Memory fail!!\n";
const char D_800E5074[] = "ObjSetupObject(3) Memory fail!!\n";
const char D_800E5098[] = "ObjList Overflow %d!!!\n";
const char D_800E50B0[] = "ObjSetupObject(4) Memory fail!!\n";
const char D_800E50D4[] = "Error: Multiple checkpoint no: %d !!\n";
const char D_800E50FC[] = "ERROR Channel %d\n";
const char D_800E5110[] = "RO error %d!!\n";
const char D_800E5120[] = "ARGHHHHHHHHH\n";

/*********************************/

/************ .bss ************/

// Currently defined in unknown_005740. Might need to be defined here.
extern s16 D_8011AC20[128];

s8 D_8011AD20[2];
s8 D_8011AD22[2];
s8 D_8011AD24[2];
s8 D_8011AD26[2];
f32 D_8011AD28;
s32 D_8011AD2C;
f32 D_8011AD30;
s32 D_8011AD34;
s32 D_8011AD38;
s8 D_8011AD3C;
s8 D_8011AD3D;
s8 D_8011AD3E;
Player *D_8011AD40;
s8 D_8011AD44;
s8 D_8011AD45;
s16 D_8011AD46;
s16 D_8011AD48;
s16 D_8011AD4A;
s16 D_8011AD4C;
s16 D_8011AD4E;
s8 D_8011AD50;
s8 D_8011AD51;
s8 D_8011AD52;
s8 D_8011AD53;
s32 D_8011AD54;
s32 *D_8011AD58;
s32 D_8011AD5C;
s32 D_8011AD60;
s32 *D_8011AD64;
s32 D_8011AD68;
s32 *D_8011AD6C;
s32 *D_8011AD70;
s32 D_8011AD74;
Gfx *D_8011AD78[10];
s32 D_8011ADA0;
s16 D_8011ADA4;
f32 D_8011ADA8;
s32 D_8011ADAC;
s32 D_8011ADB0;
s32 D_8011ADB4;
s32 D_8011ADB8;
s32 D_8011ADBC;
s32 D_8011ADC0;
u8 D_8011ADC4;
u8 D_8011ADC5;
s32 D_8011ADC8;
s8 (*D_8011ADCC)[8];
f32 D_8011ADD0;
s8 D_8011ADD4;
s8 D_8011ADD5;
s32 D_8011ADD8[10];
s8 D_8011AE00;
s8 D_8011AE01;
s8 D_8011AE02;
s8 D_8011AE03;
u32 *D_8011AE08[16];
s32 (*D_8011AE48)[8]; // Unknown number of entries.
u8 (*D_8011AE4C)[8]; // Unknown number of entries.
s32 D_8011AE50;
s32 D_8011AE54;
Player **objPtrList; // Not sure about the number of elements
s32 objCount;
s32 D_8011AE60;
s32 D_8011AE64;
s32 *D_8011AE68;
s32 *D_8011AE6C;
s32 D_8011AE70;
s32 *D_8011AE74;
s16 D_8011AE78;
s16 D_8011AE7A;
s16 D_8011AE7C;
s8 D_8011AE7E;
s16 D_8011AE80;
s16 D_8011AE82;
s32 D_8011AE84;
s32 D_8011AE88;
u32 D_8011AE8C;
u32 D_8011AE90;
u32 D_8011AE94;
s32 D_8011AE98[2];
s32 D_8011AEA0;
s32 D_8011AEA4;
s32 D_8011AEA8[2];
s32 D_8011AEB0[2];
s16 *D_8011AEB8;
s32 D_8011AEBC;
s32 D_8011AEC0;
Player **particlePtrList;
s32 particleCount;

/* Size: 0x3C bytes */
typedef struct unknown8011AECC {
    u8 unk00[0x3A];
    s8 unk3A;
    s8 unk3B;
} unknown8011AECC;
unknown8011AECC* D_8011AECC; // Array of structs, unknown number of members
s32 D_8011AED0;
s32 D_8011AED4;
s16 D_8011AED8;
u32 (*D_8011AEDC)[64]; // Not sure about the number of elements
s32 D_8011AEE0;
Player *(*playerStructArray_Ptr)[8];
s32 *D_8011AEE8;
s32 *D_8011AEEC;
s32 playerCount;
u8 gTimeTrialEnabled;
u8 D_8011AEF5;
u8 D_8011AEF6;
u8 D_8011AEF7;
s32 D_8011AEF8;
s32 D_8011AEFC;
s32 D_8011AF00;
u32 (*D_8011AF04)[64]; // Not sure about the number of elements
s32 D_8011AF08[2];
s32 D_8011AF10[2];
s32 D_8011AF18[5];
s32 D_8011AF2C;
s32 D_8011AF30[12];
s32 D_8011AF60[2];
s32 D_8011AF68[32];

/* Size: 0x40 bytes */
typedef struct unk800179D0 {
    s32 unk0;
    u32* unk04;
    u32* unk08;
    f32 unk0C[12];
    u32 unk3C;
} unk800179D0;

/* Unknown Size */
typedef struct unk800179D0_2 {
    s32 unk04; 
} unk800179D0_2;

s32 D_8011AFE8;
s16 D_8011AFEC;
s16 D_8011AFEE;
s32 D_8011AFF0;
unk800179D0* D_8011AFF4; 
s32 D_8011AFF8;
s32 D_8011AFFC;
s32 D_8011B000;
s32 D_8011B004;
s32 D_8011B008;
s32 D_8011B010[4];
u32* D_8011B020[10];
s32 D_8011B048[4];
s32 D_8011B058[4];
s32 D_8011B068[4];
s8 D_8011B078[3];
s8 D_8011B07B;
s32 D_8011B07C;
s32 D_8011B080[7];

extern s16 D_8011D5AC;

/******************************/

extern s32 osTvType;

void func_8000C460(void);

void *new_sub_memory_pool(s32, u32);
void *allocate_from_main_pool_safe(s32, u32);
s32 *load_asset_section_from_rom(s32);
void particlePtrList_addObject(Player *);
void particlePtrList_flush(void);
void func_8001D258(f32, f32, s32, s32, s32);

extern void func_800245B4(s16);


GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B020.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B290.s")
#else 

extern s32 D_800DC754;
extern Player* D_800DC75C;
extern Player* D_800DC764;

s32 *func_8001E29C(s32 arg0);

void func_8000B290(){

    if(D_800DC754){
        free_from_memory_pool();
    }
    func_8001E29C(20);
    /*{
        if(D_800DC754->unk7a)
            func_8007CCB0();
        D_800DC754->unk7a = 0;

        if(D_800DC754->unk7C)
            func_8007B2BC();
        D_800DC754->unk7C = 0;
    }*/
    if(D_800DC75C)
        particlePtrList_addObject(D_800DC75C);
    D_800DC75C = NULL;
    
    if(D_800DC764)
        particlePtrList_addObject(D_800DC764);
    D_800DC764 = NULL;

    particlePtrList_flush();
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B38C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B750.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000BADC.s")

u32* func_8000BF44(s32 arg0) {
    if (arg0 == -1) {
        arg0 = D_800DC760;
    }
    if (arg0 < 0 || arg0 >= 10) {
        return NULL;
    }
    return D_8011B020[arg0];
}

void func_8000C2D8(u8 *arg0, s32 length);

void func_8000BF8C(void) {
    s32 i;

    func_8001D258(0.67f, 0.33f, 0, -0x2000, 0);
    D_8011AE68 = (s32*)new_sub_memory_pool(0x15800, 0x200);
    particlePtrList = (Player **)allocate_from_main_pool_safe(0x320, COLOR_TAG_BLUE);
    D_8011AE6C = (s32*)allocate_from_main_pool_safe(0x50, COLOR_TAG_BLUE);
    D_8011AE74 = (s32*)allocate_from_main_pool_safe(0x200, COLOR_TAG_BLUE);
    D_8011AECC = (unknown8011AECC*)allocate_from_main_pool_safe(0xE10, COLOR_TAG_BLUE);
    D_8011AEDC = (s32*)allocate_from_main_pool_safe(0x50, COLOR_TAG_BLUE);
    playerStructArray_Ptr = (s32*)allocate_from_main_pool_safe(0x28, COLOR_TAG_BLUE);
    D_8011AEEC = (s32*)allocate_from_main_pool_safe(0x28, COLOR_TAG_BLUE);
    D_8011AEE8 = (s32*)allocate_from_main_pool_safe(0x28, COLOR_TAG_BLUE);
    D_8011AF04 = (s32*)allocate_from_main_pool_safe(0x200, COLOR_TAG_BLUE);
    D_8011ADCC = (s32*)allocate_from_main_pool_safe(8, COLOR_TAG_BLUE);
    D_8011AFF4 = (s32*)allocate_from_main_pool_safe(0x400, COLOR_TAG_BLUE);
    D_8011AEB8 = (s32*)load_asset_section_from_rom(ASSET_LEVEL_OBJECT_TRANSLATION_TABLE);
    D_8011AEBC = (get_size_of_asset_section(ASSET_LEVEL_OBJECT_TRANSLATION_TABLE) >> 1) - 1;
    while (D_8011AEB8[D_8011AEBC] == 0) {
        D_8011AEBC--;
    }
    D_8011AD58 = (s32*)allocate_from_main_pool_safe(0x800, COLOR_TAG_BLUE);
    D_8011AD64 = load_asset_section_from_rom(ASSET_OBJECT_HEADERS_TABLE);
    D_8011AD68 = 0;
    while (-1 != D_8011AD64[D_8011AD68]) {
        D_8011AD68++;
    }
    D_8011AD68--;
    D_8011AE48 = (s32*)allocate_from_main_pool_safe(D_8011AD68 << 2, COLOR_TAG_WHITE);
    D_8011AE4C = (s32*)allocate_from_main_pool_safe(D_8011AD68, COLOR_TAG_WHITE);
    
    for (i = 0; i < D_8011AD68; i++) {
        (*D_8011AE4C)[i] = 0;
    }
    
    D_8011AD6C = load_asset_section_from_rom(ASSET_MISC);
    D_8011AD70 = load_asset_section_from_rom(ASSET_MISC_TABLE);
    D_8011ADA0 = 0;
    while (-1 != D_8011AD70[D_8011ADA0]) {
        D_8011ADA0++;
    }
    func_8000C2D8(&D_8011AD6C[D_8011AD70[65]], (D_8011AD70[66] - D_8011AD70[65]) * 4);
    objPtrList = (Player**)allocate_from_main_pool_safe(0x800, COLOR_TAG_BLUE);
    D_8011ADC4 = 0;
    gTimeTrialEnabled = 0;
    D_8011AEF5 = 0;
    D_8011ADA8 = 2.0f;
    func_8000C460();
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C2D8.s")
#else
// Decrypts cheats
void func_8000C2D8(u8 *arg0, s32 length) {
    u8 sp3;
    u8 sp2;
    u8 sp1;
    u8 sp0;
    //s32 numWords;
    s32 i;

    //numWords = length / 4;
    
    for (i = 0; i < length; i++) {
        sp0 = ((arg0[i + 3] & 0xC0) >> 6) | (arg0[i + 0] & 0xC0) | ((arg0[i + 1] & 0xC0) >> 2) | ((arg0[i + 2] & 0xC0) >> 4);
        sp1 = ((arg0[i + 3] & 0x30) >> 4) | ((arg0[i + 0] & 0x30) << 2) | (arg0[i + 1] & 0x30) | ((arg0[i + 2] & 0x30) >> 2);
        sp2 = ((arg0[i + 3] & 0xC) >> 2) | ((arg0[i + 0] & 0xC) << 4) | ((arg0[i + 1] & 0xC) << 2) | (arg0[i + 2] & 0xC);
        sp3 = (arg0[i + 3] & 3) | (arg0[i + 0] << 6) | ((arg0[i + 1] & 3) << 4) | ((arg0[i + 2] & 3) << 2);
        arg0[i + 0] = ((sp0 & 0x55) << 1) | ((sp0 & 0xAA) >> 1);
        arg0[i + 1] = ((sp1 & 0x55) << 1) | ((sp1 & 0xAA) >> 1);
        arg0[i + 2] = ((sp2 & 0x55) << 1) | ((sp2 & 0xAA) >> 1);
        arg0[i + 3] = ((sp3 & 0x55) << 1) | ((sp3 & 0xAA) >> 1);
    }
}
#endif

void func_8000C460(void) {
    s32 i;
    
    D_8011AD26[0] = 1;
    D_8011AD5C = 0;
    D_8011AD60 = 0;
    particleCount = 0;
    D_8011AE70 = 0;
    D_8011AED0 = 0;
    D_8011AED4 = 0;
    playerCount = 0;
    D_8011AE78 = 0;
    D_8011AD20[1] = 0;
    D_8011AD22[0] = 0;
    D_8011AD22[1] = 0;
    
    for (i = 0; i < 0x80; i++) {
        (*D_8011AF04)[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        (*D_8011ADCC)[i] = 0;
    }
    for (i = 0; i < 0x10; i++) {
        D_8011AFF4[i].unk0 = 0;
    }
    
    D_8011AF08[0] = 0xFF;
    D_8011AF08[1] = 0xFF;
    objCount = 0;
    D_8011AE60 = 0;
    D_8011AE64 = 0;
    D_8011AE88 = 0;
    D_8011ADD4 = 0;
    D_8011AE7A = 0;
    D_8011AE7E = 1;
    D_8011AE7C = 0;
    D_8011AD44 = 0;
    D_8011AEF6 = 0;
    D_8011AEF7 = 0;
    D_8011AF60[0] = 0;
    D_8011AE00 = 0;
    D_8011AE01 = 1;
    D_8011AD53 = 0;
    D_8011ADD5 = 0;
}

void func_8000C604(void) {
    s32 i, len;
    func_80059B4C();
    D_800DC748 = 0;
    if (D_800DC71C != 0) {
        func_80072298(1);
    }
    D_800DC71C = 0;
    if (D_800DC744 && is_in_two_player_adventure()) {
        D_800DC744 = 0;
        func_8006F398();
    }
    particlePtrList_flush();
    len = objCount;
    for (i = 0; i < len; i++) {
        func_800101AC(objPtrList[i], 1);
    }
    particleCount = 0;
    objCount = 0;
    D_8011AE60 = 0;
    func_8000C460();
    free_from_memory_pool(D_8011AEB0[0]);
    free_from_memory_pool(D_8011AEB0[1]);
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C718.s")

void func_8000C844(s32 arg0) {
    if ((*D_8011AE4C)[arg0] != 0) {
        (*D_8011AE4C)[arg0]--;
        if ((*D_8011AE4C)[arg0] == 0) {
            free_from_memory_pool((*D_8011AE48)[arg0]);
        }
    }
}

s32 func_8000C8B4(s32 arg0) {
    if (osTvType != 0 || arg0 < 0) {
        return arg0;
    }
    else {
        return (arg0 * 5) / 6;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C8F8.s")

void func_8000CBC0(void) {
    s32 i = 0;
    while(i < 16){ // For some odd reason, using a for loop here makes this not match.
        D_8011AE08[i] = NULL;
        i++;
    }
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000CBF0.s")
#else
void func_8000CBF0(u32 *arg0, s32 arg1) {
    u32 **temp = &D_8011AE08[arg1];
    u32 *temp2;
    temp2 = *temp;
    if (temp2 != NULL) {
        return; // I can't get this second return to appear.
    }
    D_8011AE08[arg1] = arg0;
    return; 
}
#endif

s32 func_8000CC20(u32 *arg0) {
    s32 i;
    s32 phi_v1;

    phi_v1 = -1;
    for(i = 0; i < 0x10; i++){
        if (D_8011AE08[i] == 0) {
            phi_v1 = i;
            i = 0x10;
        }
    }
    if (phi_v1 != -1) {
        D_8011AE08[phi_v1] = arg0;
    }
    return phi_v1;
}

// Has a jump table
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000CC7C.s")

u32 func_8000E0B0(void) {
    switch(D_8011AD38) {
        case 1:
            return -1;
        case 7:
            return 0;
        case 2:
        case 3:
            return 3;
        case 4:
        case 6:
            return 2;
        case 0:
        case 5:
        case 8:
            return func_80059E20();
        default:
            return 0;
    }
}

void func_8000E128(void) {
    D_800DC708 = 0x8000;
}

s8 func_8000E138() {
    return D_8011AD20[0];
}

s8 func_8000E148() {
    return D_800DC71C;
}

s8 func_8000E158(void) {
    if (D_800DC740 != 0) {
        return D_800DC73C;
    }
    else {
        return 0;
    }
}

s8 func_8000E184() {
    return D_800DC748;
}

void func_8000E194(void) {
    D_800DC73C = 1 - D_800DC73C;
    D_800DC740 = 0;
}

void func_8000E1B8(void) {
    D_800DC73C = 0;
    D_800DC740 = 0;
}

s8 func_8000E1CC(void) {
    return D_8011AE02;
}

s8 func_8000E1DC() {
    return D_8011AE03;
}

void func_8000E1EC(Player *arg0, s32 arg1) {
    D_8011AD40 = arg0;
    D_8011AD44 = 4;
    D_8011AD45 = arg1;
    D_8011AD46 = arg0->x_position;
    D_8011AD48 = arg0->y_position;
    D_8011AD4A = arg0->z_position;
    D_8011AD4C = arg0->y_rotation;
    particlePtrList_addObject(arg0);
    playerCount = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E2B4.s")

void set_time_trial_enabled(s32 arg0) {
    gTimeTrialEnabled = arg0;
}

u8 is_time_trial_enabled() {
    return gTimeTrialEnabled;
}

u8 func_8000E4D8(void){
    return D_8011AEF5;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E4E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E558.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E5EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E79C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E898.s")


Player *getObject(s32 indx) {
    if (indx < 0 || indx >= objCount) {
        return 0;
    }
    return objPtrList[indx];
}

Player **func_8000E988(s32 *arg0, s32 *cnt) {
    *arg0 = D_8011AE60;
    *cnt = objCount;
    return objPtrList;
}

// Unused?
s32 getObjectCount(void) {
    return objCount;
}

// Unused?
s32 func_8000E9C0(void) {
    return D_8011AE64;
}

void func_8000E9D0(Player* arg0){
    arg0->unk6 |= 0x8000;
    func_800245B4(arg0->unk2C | 0xC000);
    objPtrList[objCount++] = arg0;
    if(1);
    D_8011AE64++;
}    

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000EA54.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000F648.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000F758.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000F7EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000F99C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000FAC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000FBCC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000FC6C.s")

/* Unknown Size */
typedef struct unk8000FD20_2 {
    u8 unk00[0x13];
    u8 unk13;
} unk8000FD20_2;

/* Unknown Size */
typedef struct unk8000FD20 {
    u8 unk00[0x4C];
    unk8000FD20_2* unk4C;
} unk8000FD20;

s32 func_8000FD20(unk8000FD20* arg0, unk8000FD20_2* arg1) {
    arg0->unk4C = arg1;
    arg1->unk13 = 0xFF;
    return 0x28;
}

/* Unknown Size. This might just be unk8000FD20. */
typedef struct unk8000FD34 {
    u8 unk00[0x5C];
    s32 unk5C;
} unk8000FD34;

s32 func_8000FD34(unk8000FD34 *arg0, s32 arg1) {
    arg0->unk5C = arg1;
    func_80016BC4();
    return 0x10C;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000FD54.s")


void particlePtrList_addObject(Player* arg0){
    func_800245B4(arg0->unk4A | 0x8000);
    particlePtrList[particleCount] = arg0;
    particleCount++;
}


s32 func_80010018(void){
    return D_8011AEBC;
}

s32 func_80010028(s32 arg0){
    return (D_8011AEB8[arg0] < D_8011AD68);
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/particlePtrList_flush.s")
#else
//bad regalloc; swap s2 = s3
/*removes objects in particleList from objPtrList and frees*/
void particlePtrList_flush(void){
    s32  j, i, search_indx, tmp;
    Player* searchObj;
    
    D_8011AE88 = 0;
    for (i = 0; i < particleCount; i++){
        search_indx = -1;
        searchObj = particlePtrList[i];
        
        for(j = 0; j < objCount; j++){
            if(searchObj == objPtrList[j])
                search_indx = j;
        }

        //if object found
        if(search_indx != -1){
            tmp = D_8011AE7C;
            if(search_indx < D_8011AE7C)
                D_8011AE7C = tmp-1; 
            
            objCount--;
            for(j = search_indx; j < objCount; j++){
                objPtrList[j] = objPtrList[j+1];
            }
        }
        func_800101AC(searchObj,0);
    }
    particleCount = 0;
}
#endif


GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800101AC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80010994.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011134.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011264.s")

void func_80011390(void) {
    D_8011ADAC = 0;
}

s32 func_8001139C() {
    return D_8011ADB0;
}

s32 func_800113AC() {
    return D_8011ADB8;
}

s32 func_800113BC() {
    return D_8011ADBC;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800113CC.s")

void func_80011560(void) {
    D_800DC848 = 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011570.s")
void func_80011960(Player*, s32, u32, Player_64*, u32, u32, u32, u32, f32);
#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011960.s")
#else
void func_80011960(Player* arg0, s32 arg2, u32 arg3, Player_64* arg4
                  , u32 arg5 , u32 arg6 , u32 arg7, u32 arg8, f32 arg9)
{


}
#endif

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011AD0.s")
#else
extern f32 D_800E5550;
void func_80011AD0(Player* this){
    f32 tmp_f0;
    u32 offset;
    switch(this->unk48){
        case 47:
            //L80011B10
            if(this->unk7C.word < 0)
                break;
            func_80011960( this, this->unk64->unk20, 4, this->unk64
                            , 2, this->unk64->unk24, 11, 0, 1.0f);
            break;

        case 61:
            //L80011B58
            offset = (this->unk64->unkFC*6);
            offset *= 5;
            offset = offset*2 + 0x80;
            func_80011960(this, offset, 6, this->unk64
                            , 8, this->unk64->unkF8, 10, 0, 1.0f);
            break;

        case 3://L80011BB4
            tmp_f0 = (f32) this->unk3C->unkD;
            if(this->unk3C->unkD < 0){
                tmp_f0 += 4294967296.0f;
            }
            offset = (this->unk64->unkFC*6);
            offset *= 5;
            offset = offset*2 + 0x80;
            func_80011960(this, offset, 6, this->unk64
                            , 8, this->unk64->unkF8, 26, 0, tmp_f0 * D_800E5550);
            break;

        case 89: //L80011C38
            if(this->unk78 == 0)
                break;
            if(this->unk64->unk70 > 0 || 0.0f < this->unk64->unk74){
                func_800135B8(this);
            }
            break;
        default:
            break;
    }//L80011C88
}
#endif

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011C94.s")
#else
void func_80011C94(Player* this){
}
#endif


#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800120C8.s")
#else

extern f32 D_8011AD30;

void func_800120C8(Player* this){
    u32 sp_b8;
    u32 sp_a8;
    u32 sp_a4;
    u32 sp_78;

    u32 *s0;
    f32 tmp_f_1;
    f32 *tmp_fp_s1;
    Player_64* tmp_s3;

    s0 = ((u32*) this->unk68)[this->unk3A];
    if(s0){
        /*
        sp_a8 = 0;
        sp_a4 = 0;
        sp_b8 = 255;
        sp_78 = *s0;

        if(this->unk54){
            tmp_f_1 = *((f32*) this->unk54) * 255.0f * D_8011AD30;
            sp_a8 = 1;
            sp_a4 = 1;
            sp_b8 = tmp_f_1;
        }
        

        tmp_fp_s1 = &D_8011AD30;
        if(this->unk48 == 1){
            tmp_s3 = this->unk64;
            func_80012E28(this);

        }else{
            tmp_s3 = NULL;
        }
        if(s0->unk20 < 0){
            this->s0->unk1f
        }
        //L800122Fc
        */
        //L800129A0
        {
            $t6 = this->unk3A;


            //f64 $f8;
            $f12 = (f32) $t9;
            $f8 = ( (f64) $f16) + (((f64) $f8)* 0.25f);
            $f4 = (((f32) $v0->unk2) - this->y_position);
            this->x_position = (f32) $f8;
            this->y_position = (f32) (((f64)$f18) + (((f64) $f4) * $f14));
            $sp_38 = this->z_position;
            $f8 = ( (f64) $f10) + (((f64) ($f12 - $f6)) * $f14);
            $s0->0x14 = (f32) $f8;
            if(this->descriptor_ptr->unk53 == 1){
                
                func_80068514( $s1, &D_8011AE90, &D_8011AE94, this, $t4, 266);
            }
        }
        //L80012AF8
        if($sp_9c != -1){
            if(this->descriptor_ptr->unk71){
                fast3d_cmd($v0++, 0xFA000000, 
                    ($v1->unk18 << 0x18) | ($v1->unk19 << 0x10) | ($v1->unk1a << 0x08) | ($sp_b4 & 0xff)); 
                    //G_SETPRIMCOLOR
                
                func_8007B43C();
            }
            //L80012B6C
            func_800143A8($sp_78, this, $sp_9c, 4, $sp_b0);
            if(this->descriptor_ptr->unk71){
                func_8007B54();
            } 
        }
        //L80012BA8
        if( $sp_a8 || this->descriptor_ptr->unk71){
            fast3d_cmd($v0++, 0xFA000000, 0xFFFFFFFF); //G_SETPRIMCOLOR
        }
        //L80012BE8
        if($sp_a4){
            fast3d_cmd($v0++, 0xFB000000, 0xFFFFFDA9); //G_SETENVCOLOR 
        }
        //L80012C0C
        func_80069A40($s1);
    }
    //L80012C14
    return;
}
#endif

void func_80012C30(void) {
    D_8011ADA4 = 0;
}

void func_80012C3C(Gfx** dlist){
    s32 i;
    Gfx *tmp;
    for(i = 0; i<D_8011ADA4; i++){
        fast3d_cmd((*dlist)++, 0x06000000, D_8011AD78[i]);
    }
}

void func_80012C98(Gfx **dlist) {
    if (D_8011ADA4 < 9) {
        fast3d_cmd((*dlist)++, 0x00000000, 0x00000000); // Fast3D NOP
        D_8011AD78[D_8011ADA4] = *dlist;
    }
}

void func_80012CE8(Gfx **dlist) {
    if (D_8011ADA4 < 9) {
        fast3d_cmd((*dlist)++, 0xB8000000, 0x00000000); // End display list
        fast3d_cmd(D_8011AD78[D_8011ADA4] - 1, 0x6010000, (u32)*dlist); // Jump to display list
        D_8011ADA4++;
    }
}

void func_8001348C(Player *);

func_80012D5C(u32 *arg0, u32 *arg1, u32 *arg2, Player * arg3){
    f32 scale;
    u32 tmp2;
    u32 tmp3;
    if(arg3->unk6 & 0x5000)
        return;
    
    func_800B76B8(2, arg3->unk4A);
    D_8011AE8C = *arg0;
    D_8011AE90 = *arg1;
    D_8011AE94 = *arg2;
    scale = arg3->scale;
    func_8001348C(arg3);
    arg3->scale = scale;
    *arg0 = D_8011AE8C;
    *arg1 = D_8011AE90;
    *arg2 = D_8011AE94;
    func_800B76B8(2, -1);

    
}

extern f32 func_800707F8(s16);
#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012E28.s")
#else
void func_80012E28(Player *this){
    s32         unused1;
    Player_64  *sp_20;
    f32         tmp_f2;
    f32         sp_1c;
    f32         tmp_f0;
    

    if(this->unk48 == 1){
        
        sp_20 = this->unk64;
        this->y_rotation += sp_20->unk160;
        this->x_rotation += sp_20->unk162;
        this->z_rotation += sp_20->unk164;
        sp_1c = 0.0f;
        if(sp_20->unk1D7 < 5) {
            
            sp_1c = func_800707F8(sp_20->unk164);
            tmp_f2 = sp_1c;
            tmp_f0 = func_800707F8(sp_20->unk162 - sp_20->unk166)*tmp_f2;
            
            //bad regalloc of 0.0f
            tmp_f0 = (tmp_f0 < 0.0f) ? 0.0f : tmp_f0*tmp_f0;
            
            sp_1c = (1.0f - tmp_f0)*24.0f + sp_20->unkD0;
        }
        //L80012F0C
        this->y_position = this->y_position + sp_1c;
        D_8011ADD0 = sp_1c;
    }
    //L80012F20
}
#endif


void func_80012F30(Player *arg0) {
    if (arg0->unk48 == 1) {
        Player_64 *player_64 = arg0->unk64;
        arg0->y_rotation -= player_64->unk160;
        arg0->x_rotation -= player_64->unk162;
        arg0->z_rotation -= player_64->unk164;
        arg0->y_position -= D_8011ADD0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012F94.s")




void func_80013548(Player *arg0);

void func_8001348C(Player *this){
    func_80012F94(this);
    if(this->unk6 & 0x8000){
        func_800B3740(this, &D_8011AE8C, &D_8011AE90, &D_8011AE94, 32768);
    }
    else{
        if(this->descriptor_ptr->unk53 == 0)
            func_800120C8(this);
        else if(this->descriptor_ptr->unk53 == 1)
            func_80011C94(this);
        else if(this->descriptor_ptr->unk53 == 4)
            func_80011AD0(this);
    }
    func_80013548(this);
}

void func_80013548(Player *arg0) {
    if ((arg0->unk6 & 0x8000) == 0 && arg0->descriptor_ptr->unk54 == 1) {
        arg0->x_position -= arg0->unk64->unk78;
        arg0->y_position -= arg0->unk64->unk7C;
        arg0->z_position -= arg0->unk64->unk80;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800135B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800138A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80013A0C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80013DCC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80014090.s")

void func_800142B8(void){
    s32 i =  D_8011AE60;
    s32 j;
    Player* currObj;
    Player_68 *curr_68;

    for(; i < objCount; i++){
        currObj = objPtrList[i];
        if( (currObj->unk6 & 0x8000) == 0  && currObj->descriptor_ptr->unk53 == 0){
            for(j=0; j<currObj->descriptor_ptr->unk55; j++){
                curr_68 = currObj->unk68[j];
                if( curr_68 != NULL && curr_68->unk20 > 0){
                    curr_68->unk20 = curr_68->unk20-- & 0x03;
                }
            }
        }
    }

}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800143A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80014814.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80014B50.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80015348.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800155B8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800159C8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80016500.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80016748.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80016BC4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80016C68.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80016DE8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001709C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80017248.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001790C.s")

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80017978.s")

u32 func_800179D0(void) {
    s16 i = 0;
    while(i < 16) {
        unk800179D0* temp = &D_8011AFF4[i]; 
        if (temp->unk0 != 0) {
            temp->unk0--;
        }
        i++;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80017A18.s")

void func_80017E74(s32 arg0) {
    D_8011AED8 = arg0;
    D_8011ADAC = 0;
}

s16 func_80017E88(void) {
    return D_8011AED8;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80017E98.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800185E4.s")

Player * func_80018C6C(void){
    s32 i;
    Player* current_obj;
    for(i=D_8011AE60; i < objCount; i++){
        current_obj = objPtrList[i];
        if(!(current_obj->unk6 & 0x8000) && (current_obj->unk48 == 62))
            return current_obj;
    }
    return NULL;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80018CE0.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001955C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80019808.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001A7D8.s")

void func_8001A8D4(s32 arg0) {
    D_8011AD4E = 0x12C;
    D_8011AD50 = 0;
    D_8011AD52 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001A8F4.s")

s16 func_8001AE44() {
    return D_8011AD4E;
}

s32 func_8001AE54() {
    return D_8011ADC8;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001AE64.s")

s32 func_8001B288(void) {
    if (func_800599A8() != func_8006BD88()) {
        return 0;
    } else {
        if (D_800DC728 != D_8011AE82) {
            return 0;
        } else {
            return 1;
        }
    }
}


s32 func_8001B2E0() {
    return D_8011AD34;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B2F0.s")

s32 func_8001B3AC(s32 arg0) {
    return arg0 == D_800DC718;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B3C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B4FC.s")

s32 func_8001B640() {
    return D_800DC718;
}

s32 func_8001B650(void) {
    return D_800DC738 == 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B668.s")

void func_8001B738(s32 arg0) {
    func_80059B7C(arg0, func_800599A8(), D_800DC728, D_800DC72C, D_800DC724);
}

u8 func_8001B780() {
    return D_800DC730;
}

void func_8001B790(void) {
    D_8011D5AC = -1;
    D_800DC730 = 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B7A8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B834.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001B974.s")

// Returns a pointer to some struct that is 0x3C bytes long.
unknown8011AECC *func_8001BA00(s32 arg0) {
    return &D_8011AECC[arg0];
}

unknown8011AECC *func_8001BA1C(s32 arg0, s32 arg1) {
    unknown8011AECC *val = &D_8011AECC[arg0];
    if (arg1 != 0 && val->unk3A != -1) {
       val = &D_8011AECC[val->unk3A];
    }
    return val;
}

s32 func_8001BA64() {
    return D_8011AED0;
}

Player **getPlayerStructArray(s32 *cnt) {
    *cnt = playerCount;
    return *playerStructArray_Ptr;
}

s32 *func_8001BA90(s32 *arg0) {
    *arg0 = playerCount;
    return D_8011AEEC;
}

s32 *func_8001BAAC(s32 *arg0) {
    *arg0 = playerCount;
    return D_8011AEE8;
}

Player *getPlayerStruct(s32 indx) {
    if (playerCount == 0) {
        return NULL;
    }
    if(indx < 0 || indx >= playerCount) {
        return NULL;
    }
    return (*playerStructArray_Ptr)[indx];
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001BB18.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001BB68.s")

void func_8001BC40(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001BC54.s")


u32 func_8001BD94(s32 arg0) {
    if (arg0 < 0 || arg0 >= D_8011AEE0) {
        return 0;
    }
    return D_8011AEDC[0][arg0];
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001BDD4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001BF20.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001C418.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001C48C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001C524.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001C6C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001CC48.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001CD28.s")

void func_8001D1AC(void) {
    D_8011AF10[0] = 1;
}

void func_8001D1BC(s32 arg0) {
    if (arg0 != D_8011AF08[0]) {
        D_8011AF08[1] = D_8011AF08[0];
        D_8011AF08[0] = arg0;
    }
}

u32 func_8001D1E4(s32 *arg0) {
    *arg0 = D_8011AF08[1];
    return D_8011AF04[0][D_8011AF08[1]];
}

u32 func_8001D214(s32 arg0) {
    if (arg0 >= 0 && arg0 < 0x80) {
        return D_8011AF04[0][arg0];
    }
    return 0;
}

void func_8001D23C(s32 arg0, s32 arg1, s32 arg2) {
    
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D258.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D2A0.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D4B4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D5E0.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D6E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001D80C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001DD54.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E13C.s")

s32 *func_8001E29C(s32 arg0) {
    if (arg0 < 0 || arg0 >= D_8011ADA0) {
        return D_8011AD6C;
    }
    return (s32*)&D_8011AD6C[D_8011AD70[arg0]];
}

s32 func_8001E2EC(s32 arg0) {
    if (arg0 >= 0 && arg0 < 8) {
        if (D_8011ADCC[0][arg0] > 0) {
            D_8011ADCC[0][arg0]--;
        }
        return D_8011ADCC[0][arg0];
    }
    return 0;
}

void func_8001E344(s32 arg0) {
    s32 temp = 8;
    if (arg0 >= 0 && arg0 < 8) {
        D_8011ADCC[0][arg0] = 8;
    }
}

void func_8001E36C(s32 arg0, f32* arg1, f32* arg2, f32* arg3){
    s32 i;
    Player* current_obj;
    *arg1 = -32000.0f;
    *arg2 = -32000.0f;
    *arg3 = -32000.0f;
    for(i=0; i<objCount; i++){
        current_obj = objPtrList[i];

        if( current_obj != NULL
        && (current_obj->unk6 & 0x8000) == 0 
        &&  current_obj->unk48 == 39
        &&  current_obj->unk78 == arg0
        ){
            *arg1 = current_obj->x_position;
            *arg2 = current_obj->y_position;
            *arg3 = current_obj->z_position;
        }
    }
}

s16 func_8001E440() {
    return D_8011AE7A;
}

void func_8001E450(s32 arg0) {
    D_8011AE7A = arg0;
}

void func_8001E45C(s32 arg0) {
    if (arg0 != D_8011AE7A) {
        D_8011AE7A = arg0;
        D_8011ADAC = 0;
        D_8011AE7E = (u8)1;
        if (func_8006DA0C() == 1) {
            func_8006F42C();
        }
    }
}

// Unused?
s32 func_8001E4B4(void) {
    return D_8011AE60;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E4C4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E6EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E89C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E93C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001EE74.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001EFA4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001F23C.s")

s8 func_8001F3B8(void) {
    return D_8011ADD4;
}

void func_8001F3C8(s32 arg0) {
    if (arg0 != D_8011ADD4) {
        D_8011AE78 = 0;
    }
    D_8011ADD4 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001F3EC.s")

void func_8001F450(void) {
    D_8011AD53 = 1;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001F460.s")

s32 func_800210CC(s8 arg0) {
    if (arg0 >= D_8011AD3D) {
        D_8011AD3D = arg0;
        return 1;
    }
    return 0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80021104.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002125C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80021400.s")

s8 func_800214C4(void) {
    return D_8011AD22[1 - D_8011AD20[1]];
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800214E4.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80021600.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022540.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002263C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002277C.s")

f32 func_80022888(f32 *arg0, u32 arg1, f32 arg2) {
    f32 result = arg0[arg1 + 1] + ((arg0[arg1 + 2] - arg0[arg1 + 1]) * arg2);
    return result;
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800228B0.s")
#else
f32 func_800228B0(f32 *arg0, u32 arg1, f32 arg2, f32 *arg3) {
    f32 temp_f12;
    f32 temp_f2;
    // regalloc issues
    temp_f2 = (arg0[arg1 + 2] - arg0[arg1 + 1]) * arg2;
    temp_f12 = arg0[arg1 + 1];
    *arg3 = arg0[arg1 + 2] - arg0[arg1 + 1];
    return temp_f12 + temp_f2;
}
#endif

// Unused?
void func_800228DC(s32 arg0, s32 arg1, s32 arg2) {

}

void func_800228EC(s32 arg0) {
    Player_64 *player_64;

    D_8011AEF7 = 3;
    player_64 = getPlayerStruct(0)->unk64;
    player_64->unk190 = 0;
    player_64->unk192 = 0;
    player_64->unk193 = 0;
    player_64->unk1BA = 0;
    func_80017E74(arg0);
    func_8006F388(10);
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022948.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022CFC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80022E18.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800230D0.s")

s8 func_8002341C(void) {
    return D_8011AEF6;
}
#if 1 
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002342C.s")
#else

extern f32 sqrtf(f32);

//bad regalloc
//finds furthest object (with some additional conditions)
Player* func_8002342C(f32 x, f32 z){
    Player* retval = NULL;
    s32 i;
    Player* currObj = NULL;
    f32 x;
    f32 z;
    f32 dist;
    f32 max = 0.0f;
    
    for(i=0; i<objCount; i++){
        currObj = objPtrList[i];
        if((currObj->unk6 & 0x8000) == 0 && currObj->unk48 == 87){
            x = currObj->x_position - x;
            z = currObj->z_position - z;
            dist = sqrtf(x*x + z*z);

            if(max < dist){
                max = dist;
                retval = currObj;
            }
        }
    }
    return retval;
}
#endif

s32 func_80023568(void) {
    if (D_8011AD3C != 0) {
        return D_8011AD24[1] + 1;
    } else if (get_current_level_race_type() == 8) {
        return D_8011AD24[1] + 1;
    }
    return 0;
}

s8 func_800235C0(void) {
    return D_8011ADD5;
}

void func_800235D0(s32 arg0) {
    D_8011ADD5 = arg0;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800235DC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_800238BC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80023E30.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80023F48.s")

s16* func_80024594(s32 *arg0, s32 *arg1) {
    *arg0 = D_800DC700;
    *arg1 = 0x80;
    return D_8011AC20;
}

void func_800245B4(s16 arg0) {
    D_8011AC20[D_800DC700++] = arg0;
    if (D_800DC700 >= 0x80) {
        D_800DC700 = 0;
    }
}

