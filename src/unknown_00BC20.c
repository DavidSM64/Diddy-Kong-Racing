/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8000B020 */

#include "unknown_00BC20.h"
#include "memory.h"

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "asset_sections.h"
#include "asset_loading.h"
#include "thread0_epc.h"
#include "controller_pak.h"
#include "menu.h"
#include "unknown_06B2B0.h"
#include "unknown_043920.h"

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
    0.0f, -0.70711f, 0.70711f,
};

u16 D_800DC7A8[8] = {
    0x0001, 0x0002, 0x0003, 0x0004,
    0x0051, 0x0054, 0x0055, 0x0056,
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
    0x00E8, 0x0115, 0x0118, 0x0000,
};

s16 D_800DC820[16] = {
    0x0005, 0x0106, 0x0207, 0x0005,
    0x0106, 0x010B, 0x010B, 0x0207,
    0x000C, 0x020D, 0x0101, 0x0101,
    0x0101, 0x0101, 0x0101, 0x0000,
};
s8 D_800DC840[8] = { 9, 1, 2, 3, 4, 5, 7, 0 };

s8 D_800DC848 = 0;
s32 D_800DC84C[3] = { // Currently unknown, might be a different type.
    0xFF401000,
    0x1040FF00,
    0x10FF4000,
};
s32 D_800DC858 = 0;          // Currently unknown, might be a different type.
s32 D_800DC85C = 0x0028FFFF; // Currently unknown, might be a different type.

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
Object *D_8011AD40;
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
s32 *gAssetsObjectHeadersTable;
s32 gAssetsObjectHeadersTableLength;
s32 *gAssetsMiscSection;
s32 *gAssetsMiscTable;
s32 D_8011AD74;
Gfx *D_8011AD78[10];
s32 gAssetsMiscTableLength;
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
u8 (*D_8011AE4C)[8];  // Unknown number of entries.
s32 D_8011AE50;
s32 D_8011AE54;
Object **gObjPtrList; // Not sure about the number of elements
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
s16 *gAssetsLvlObjTranslationTable;
s32 gAssetsLvlObjTranslationTableLength;
s32 D_8011AEC0;
Object **gParticlePtrList;
s32 gParticleCount;
unknown8011AECC *D_8011AECC; // Array of structs, unknown number of members
s32 D_8011AED0;
s32 D_8011AED4;
s16 D_8011AED8;
u32 (*D_8011AEDC)[64]; // Not sure about the number of elements
s32 D_8011AEE0;
Object *(*gObjectStructArrayPtr)[8];
s32 *D_8011AEE8;
s32 *D_8011AEEC;
s32 gObjectCount;
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
s32 D_8011AFE8;
s16 D_8011AFEC;
s16 D_8011AFEE;
s32 D_8011AFF0;
unk800179D0 *D_8011AFF4;
s32 D_8011AFF8;
s32 D_8011AFFC;
s32 D_8011B000;
s32 D_8011B004;
s32 D_8011B008;
s32 D_8011B010[4];
Object *D_8011B020[10];
s32 D_8011B048[4];
s32 D_8011B058[4];
s32 D_8011B068[4];
s8 D_8011B078[3];
s8 D_8011B07B;
s32 D_8011B07C;
s32 D_8011B080[7];

extern s16 D_8011D5AC;

/******************************/

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B020.s")

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B290.s")
#else
extern s32 D_800DC754;
extern Object *D_800DC75C;
extern Object *D_800DC764;

s32 *get_misc_asset(s32 arg0);

void func_8000B290() {

    if (D_800DC754) {
        free_from_memory_pool();
    }
    get_misc_asset(20);
    /*{
        if(D_800DC754->unk7a)
            free_sprite();
        D_800DC754->unk7a = 0;

        if(D_800DC754->unk7C)
            free_texture();
        D_800DC754->unk7C = 0;
    }*/
    if (D_800DC75C)
        gParticlePtrList_addObject(D_800DC75C);
    D_800DC75C = NULL;

    if (D_800DC764)
        gParticlePtrList_addObject(D_800DC764);
    D_800DC764 = NULL;

    gParticlePtrList_flush();
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B38C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000B750.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000BADC.s")

Object *func_8000BF44(s32 arg0) {
    if (arg0 == -1) {
        arg0 = D_800DC760;
    }
    if (arg0 < 0 || arg0 >= 10) {
        return NULL;
    }
    return D_8011B020[arg0];
}

void func_8000BF8C(void) {
    s32 i;

    func_8001D258(0.67f, 0.33f, 0, -0x2000, 0);
    D_8011AE68 = (s32 *)new_sub_memory_pool(0x15800, 0x200);
    gParticlePtrList = (Object **)allocate_from_main_pool_safe(0x320, COLOR_TAG_BLUE);
    D_8011AE6C = (s32 *)allocate_from_main_pool_safe(0x50, COLOR_TAG_BLUE);
    D_8011AE74 = (s32 *)allocate_from_main_pool_safe(0x200, COLOR_TAG_BLUE);
    D_8011AECC = (unknown8011AECC *)allocate_from_main_pool_safe(0xE10, COLOR_TAG_BLUE);
    D_8011AEDC = (u32 *)allocate_from_main_pool_safe(0x50, COLOR_TAG_BLUE);
    gObjectStructArrayPtr = (Object *)allocate_from_main_pool_safe(0x28, COLOR_TAG_BLUE);
    D_8011AEEC = (s32 *)allocate_from_main_pool_safe(0x28, COLOR_TAG_BLUE);
    D_8011AEE8 = (s32 *)allocate_from_main_pool_safe(0x28, COLOR_TAG_BLUE);
    D_8011AF04 = (u32 *)allocate_from_main_pool_safe(0x200, COLOR_TAG_BLUE);
    D_8011ADCC = (s8 *)allocate_from_main_pool_safe(8, COLOR_TAG_BLUE);
    D_8011AFF4 = (unk800179D0 *)allocate_from_main_pool_safe(0x400, COLOR_TAG_BLUE);
    gAssetsLvlObjTranslationTable = (s16 *)load_asset_section_from_rom(ASSET_LEVEL_OBJECT_TRANSLATION_TABLE);
    gAssetsLvlObjTranslationTableLength = (get_size_of_asset_section(ASSET_LEVEL_OBJECT_TRANSLATION_TABLE) >> 1) - 1;
    while (gAssetsLvlObjTranslationTable[gAssetsLvlObjTranslationTableLength] == 0) {
        gAssetsLvlObjTranslationTableLength--;
    }
    D_8011AD58 = (s32 *)allocate_from_main_pool_safe(0x800, COLOR_TAG_BLUE);
    gAssetsObjectHeadersTable = load_asset_section_from_rom(ASSET_OBJECT_HEADERS_TABLE);
    gAssetsObjectHeadersTableLength = 0;
    while (-1 != gAssetsObjectHeadersTable[gAssetsObjectHeadersTableLength]) {
        gAssetsObjectHeadersTableLength++;
    }
    gAssetsObjectHeadersTableLength--;
    D_8011AE48 = (s32 *)allocate_from_main_pool_safe(gAssetsObjectHeadersTableLength * 4, COLOR_TAG_WHITE);
    D_8011AE4C = (u8 *)allocate_from_main_pool_safe(gAssetsObjectHeadersTableLength, COLOR_TAG_WHITE);

    for (i = 0; i < gAssetsObjectHeadersTableLength; i++) {
        (*D_8011AE4C)[i] = 0;
    }

    gAssetsMiscSection = load_asset_section_from_rom(ASSET_MISC);
    gAssetsMiscTable = load_asset_section_from_rom(ASSET_MISC_TABLE);
    gAssetsMiscTableLength = 0;
    while (-1 != gAssetsMiscTable[gAssetsMiscTableLength]) {
        gAssetsMiscTableLength++;
    }

    decrypt_magic_codes(&gAssetsMiscSection[gAssetsMiscTable[65]], (gAssetsMiscTable[66] - gAssetsMiscTable[65]) * 4);
    gObjPtrList = (Object **)allocate_from_main_pool_safe(0x800, COLOR_TAG_BLUE);
    D_8011ADC4 = 0;
    gTimeTrialEnabled = 0;
    D_8011AEF5 = 0;
    D_8011ADA8 = 2.0f;
    func_8000C460();
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/decrypt_magic_codes.s")
#else
// Decrypts cheats
void decrypt_magic_codes(u8 *data, s32 length) {
    u8 sp3;
    u8 sp2;
    u8 sp1;
    u8 sp0;
    //s32 numWords;
    s32 i;

    //numWords = length / 4;

    for (i = 0; i < length; i++) {
        sp0 = ((data[i + 3] & 0xC0) >> 6) | (data[i + 0] & 0xC0) | ((data[i + 1] & 0xC0) >> 2) | ((data[i + 2] & 0xC0) >> 4);
        sp1 = ((data[i + 3] & 0x30) >> 4) | ((data[i + 0] & 0x30) << 2) | (data[i + 1] & 0x30) | ((data[i + 2] & 0x30) >> 2);
        sp2 = ((data[i + 3] & 0xC) >> 2) | ((data[i + 0] & 0xC) << 4) | ((data[i + 1] & 0xC) << 2) | (data[i + 2] & 0xC);
        sp3 = (data[i + 3] & 3) | (data[i + 0] << 6) | ((data[i + 1] & 3) << 4) | ((data[i + 2] & 3) << 2);
        data[i + 0] = ((sp0 & 0x55) << 1) | ((sp0 & 0xAA) >> 1);
        data[i + 1] = ((sp1 & 0x55) << 1) | ((sp1 & 0xAA) >> 1);
        data[i + 2] = ((sp2 & 0x55) << 1) | ((sp2 & 0xAA) >> 1);
        data[i + 3] = ((sp3 & 0x55) << 1) | ((sp3 & 0xAA) >> 1);
    }
}
#endif

void func_8000C460(void) {
    s32 i;

    D_8011AD26[0] = 1;
    D_8011AD5C = 0;
    D_8011AD60 = 0;
    gParticleCount = 0;
    D_8011AE70 = 0;
    D_8011AED0 = 0;
    D_8011AED4 = 0;
    gObjectCount = 0;
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
    free_tt_ghost_data();
    D_800DC748 = 0;
    if (D_800DC71C != 0) {
        func_80072298(1);
    }
    D_800DC71C = 0;
    if (D_800DC744 && is_in_two_player_adventure()) {
        D_800DC744 = 0;
        func_8006F398();
    }
    gParticlePtrList_flush();
    len = objCount;
    for (i = 0; i < len; i++) {
        func_800101AC(gObjPtrList[i], 1);
    }
    gParticleCount = 0;
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
    } else {
        return (arg0 * 5) / 6;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000C8F8.s")

void func_8000CBC0(void) {
    s32 i = 0;
    while (i < 16) { // For some odd reason, using a for loop here makes this not match.
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
    for (i = 0; i < 0x10; i++) {
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
    switch (D_8011AD38) {
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
    } else {
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

void func_8000E1EC(Object *object, s32 arg1) {
    D_8011AD40 = object;
    D_8011AD44 = 4;
    D_8011AD45 = arg1;
    D_8011AD46 = object->x_position;
    D_8011AD48 = object->y_position;
    D_8011AD4A = object->z_position;
    D_8011AD4C = object->y_rotation;
    gParticlePtrList_addObject(object);
    gObjectCount = 0;
}

#ifdef NON_MATCHING
typedef struct LevelObjectEntry8000E2B4 {
    LevelObjectEntryCommon common;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} LevelObjectEntry8000E2B4;

void func_8000E2B4(void) {
    LevelObjectEntry8000E2B4 sp2C;
    Settings *settings;
    Object *player;
    Object_64 *player_64;
    s16 object_id;

    if (D_8011AD44 == 0) {
        return;
    }
    D_8011AD44 = (s8) (D_8011AD44 - 1);
    if (D_8011AD44 != 0) {
        return;
    }
    settings = get_settings();
    sp2C.unkE = 0;
    sp2C.common.size = 0x10;
    if (D_8011AD45 < 5) {
        object_id = ((s16*)D_800DC7A8)[settings->racers[0].character + D_8011AD45 * 10];
    } else {
        object_id = D_800DC7B8[D_8011AD45 + 37];
    }
    func_8006DB14(D_8011AD45);
    sp2C.common.size = sp2C.common.size | ((s32) (object_id & 0x100) >> 1);
    sp2C.unkA = 0;
    sp2C.unk8 = 0;
    sp2C.common.object_id = (s8) object_id;
    sp2C.common.x = D_8011AD46;
    sp2C.common.y = D_8011AD48;
    sp2C.common.z = D_8011AD4A;
    sp2C.unkC = D_8011AD4C;
    func_800521B8(1);
    player = func_8000EA54(&sp2C, 0x11);
    gObjectCount = 1;
    (*gObjectStructArrayPtr)[0] = (s32) player;
    *D_8011AEEC = (s32) player;
    *D_8011AEE8 = (s32) player;
    player_64 = player->unk64;
    player_64->unk1D6 = (s8) D_8011AD45;
    player_64->unk0_a.unk0_b.unk2 = (u8)0;
    player_64->unk1D7 = (s8) D_8011AD45;
    player_64->unk0_a.unk0_b.unk0 = (u16)0;
    player_64->unk118 = 0;
    player_64->unk0_a.unk0_b.unk3 = (s8) settings->racers[0].character;
    if (get_filtered_cheats() & CHEAT_BIG_CHARACTERS) {
        player->scale *= 1.4f;
    }
    if (get_filtered_cheats() & CHEAT_SMALL_CHARACTERS) {
        player->scale *= 0.714f;
    }
    player->unk3C_a.unk3C = 0;
    player->y_rotation = D_8011AD4C;
    player->y_position = D_8011AD48;
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E2B4.s")
#endif

/**
 * Enables or Disables time trial mode.
 */
void set_time_trial_enabled(s32 arg0) {
    gTimeTrialEnabled = arg0;
}

/**
 * Returns the value in gTimeTrialEnabled.
 */
u8 is_time_trial_enabled() {
    return gTimeTrialEnabled;
}

u8 func_8000E4D8(void) {
    return D_8011AEF5;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E4E8.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E558.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E5EC.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E79C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000E898.s")

Object *get_object(s32 index) {
    if (index < 0 || index >= objCount) {
        return 0;
    }
    return gObjPtrList[index];
}

Object **func_8000E988(s32 *arg0, s32 *cnt) {
    *arg0 = D_8011AE60;
    *cnt = objCount;
    return gObjPtrList;
}

// Unused?
s32 getObjectCount(void) {
    return objCount;
}

// Unused?
s32 func_8000E9C0(void) {
    return D_8011AE64;
}

void func_8000E9D0(Object *arg0) {
    arg0->unk6 |= 0x8000;
    func_800245B4(arg0->unk2C | 0xC000);
    gObjPtrList[objCount++] = arg0;
    if (1);
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

s32 func_8000FD20(unk8000FD20 *arg0, unk8000FD20_2 *arg1) {
    arg0->unk4C = arg1;
    arg1->unk13 = 0xFF;
    return 0x28;
}

s32 func_8000FD34(unk8000FD34 *arg0, s32 arg1) {
    arg0->unk5C = arg1;
    func_80016BC4();
    return 0x10C;
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8000FD54.s")

void gParticlePtrList_addObject(Object *object) {
    func_800245B4(object->unk4A | 0x8000);
    gParticlePtrList[gParticleCount] = object;
    gParticleCount++;
}

s32 func_80010018(void) {
    return gAssetsLvlObjTranslationTableLength;
}

s32 func_80010028(s32 arg0) {
    return (gAssetsLvlObjTranslationTable[arg0] < gAssetsObjectHeadersTableLength);
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/gParticlePtrList_flush.s")
#else
//bad regalloc; swap s2 = s3
/*removes objects in particleList from gObjPtrList and frees*/
void gParticlePtrList_flush(void) {
    s32 j, i, search_indx, tmp;
    Object *searchObj;

    D_8011AE88 = 0;
    for (i = 0; i < gParticleCount; i++) {
        search_indx = -1;
        searchObj = gParticlePtrList[i];

        for (j = 0; j < objCount; j++) {
            if (searchObj == gObjPtrList[j])
                search_indx = j;
        }

        //if object found
        if (search_indx != -1) {
            tmp = D_8011AE7C;
            if (search_indx < D_8011AE7C)
                D_8011AE7C = tmp - 1;

            objCount--;
            for (j = search_indx; j < objCount; j++) {
                gObjPtrList[j] = gObjPtrList[j + 1];
            }
        }
        func_800101AC(searchObj, 0);
    }
    gParticleCount = 0;
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

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011960.s")
#else
void func_80011960(Object *arg0, s32 arg2, u32 arg3, Object_64 *arg4,
                    u32 arg5, u32 arg6, u32 arg7, u32 arg8, f32 arg9) {
}
#endif

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80011AD0.s")
#else
extern f32 D_800E5550;
void func_80011AD0(Object *this) {
    f32 tmp_f0;
    u32 offset;
    switch (this->unk48) {
        case 47:
            //L80011B10
            if (this->unk7C.word < 0)
                break;
            func_80011960(this, this->unk64->unk20, 4, this->unk64,
                            2, this->unk64->unk24, 11, 0, 1.0f);
            break;

        case 61:
            //L80011B58
            offset = (this->unk64->unkFC * 6);
            offset *= 5;
            offset = offset * 2 + 0x80;
            func_80011960(this, offset, 6, this->unk64, 8, this->unk64->unkF8, 10, 0, 1.0f);
            break;

        case 3: //L80011BB4
            tmp_f0 = (f32)this->unk3C->unkD;
            if (this->unk3C->unkD < 0) {
                tmp_f0 += 4294967296.0f;
            }
            offset = (this->unk64->unkFC * 6);
            offset *= 5;
            offset = offset * 2 + 0x80;
            func_80011960(this, offset, 6, this->unk64, 8, this->unk64->unkF8, 26, 0, tmp_f0 * D_800E5550);
            break;

        case 89: //L80011C38
            if (this->unk78 == 0)
                break;
            if (this->unk64->unk70 > 0 || 0.0f < this->unk64->unk74) {
                func_800135B8(this);
            }
            break;
        default:
            break;
    } //L80011C88
}
#endif

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/render_3d_billboard.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/render_3d_model.s")

void func_80012C30(void) {
    D_8011ADA4 = 0;
}

void func_80012C3C(Gfx **dlist) {
    s32 i;
    Gfx *tmp;
    for (i = 0; i < D_8011ADA4; i++) {
        gSPDisplayList((*dlist)++, D_8011AD78[i]);
    }
}

void func_80012C98(Gfx **dlist) {
    if (D_8011ADA4 < 9) {
        gSPNoOp((*dlist)++); // Placeholder instruction?
        D_8011AD78[D_8011ADA4] = *dlist;
    }
}

void func_80012CE8(Gfx **dlist) {
    if (D_8011ADA4 < 9) {
        gSPEndDisplayList((*dlist)++);
        gSPBranchList(D_8011AD78[D_8011ADA4] - 1, (u32)*dlist);
        D_8011ADA4++;
    }
}

void func_80012D5C(u32 *arg0, u32 *arg1, u32 *arg2, Object *object) {
    f32 scale;
    u32 tmp2;
    u32 tmp3;
    if (object->unk6 & 0x5000)
        return;
    func_800B76B8(2, object->unk4A);
    D_8011AE8C = *arg0;
    D_8011AE90 = *arg1;
    D_8011AE94 = *arg2;
    scale = object->scale;
    render_object(object);
    object->scale = scale;
    *arg0 = D_8011AE8C;
    *arg1 = D_8011AE90;
    *arg2 = D_8011AE94;
    func_800B76B8(2, -1);
}

#if 1
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012E28.s")
#else
void func_80012E28(Object *this) {
    s32 unused1;
    Object_64 *sp_20;
    f32 tmp_f2;
    f32 sp_1c;
    f32 tmp_f0;

    if (this->unk48 == 1) {

        sp_20 = this->unk64;
        this->y_rotation += sp_20->unk160;
        this->x_rotation += sp_20->unk162;
        this->z_rotation += sp_20->unk164;
        sp_1c = 0.0f;
        if (sp_20->unk1D7 < 5) {

            sp_1c = func_800707F8(sp_20->unk164);
            tmp_f2 = sp_1c;
            tmp_f0 = func_800707F8(sp_20->unk162 - sp_20->unk166) * tmp_f2;

            //bad regalloc of 0.0f
            tmp_f0 = (tmp_f0 < 0.0f) ? 0.0f : tmp_f0 * tmp_f0;

            sp_1c = (1.0f - tmp_f0) * 24.0f + sp_20->unkD0;
        }
        //L80012F0C
        this->y_position = this->y_position + sp_1c;
        D_8011ADD0 = sp_1c;
    }
    //L80012F20
}
#endif

void func_80012F30(Object *arg0) {
    if (arg0->unk48 == 1) {
        Object_64 *object_64 = arg0->unk64;
        arg0->y_rotation -= object_64->unk160;
        arg0->x_rotation -= object_64->unk162;
        arg0->z_rotation -= object_64->unk164;
        arg0->y_position -= D_8011ADD0;
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80012F94.s")

void render_object(Object *this) {
    func_80012F94(this);
    if (this->unk6 & 0x8000) {
        func_800B3740(this, &D_8011AE8C, &D_8011AE90, &D_8011AE94, 32768);
    } else {
        if (this->descriptor_ptr->unk53 == 0)
            render_3d_model(this);
        else if (this->descriptor_ptr->unk53 == 1)
            render_3d_billboard(this);
        else if (this->descriptor_ptr->unk53 == 4)
            func_80011AD0(this);
    }
    func_80013548(this);
}

void func_80013548(Object *arg0) {
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

void func_800142B8(void) {
    s32 i = D_8011AE60;
    s32 j;
    Object *currObj;
    Object_68 *curr_68;

    for (; i < objCount; i++) {
        currObj = gObjPtrList[i];
        if ((currObj->unk6 & 0x8000) == 0 && currObj->descriptor_ptr->unk53 == 0) {
            for (j = 0; j < currObj->descriptor_ptr->unk55; j++) {
                curr_68 = currObj->unk68[j];
                if (curr_68 != NULL && curr_68->unk20 > 0) {
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
    while (i < 16) {
        unk800179D0 *temp = &D_8011AFF4[i];
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

Object *func_80018C6C(void) {
    s32 i;
    Object *current_obj;
    for (i = D_8011AE60; i < objCount; i++) {
        current_obj = gObjPtrList[i];
        if (!(current_obj->unk6 & 0x8000) && (current_obj->unk48 == 62))
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

s32 func_8001B738(s32 arg0) {
    return func_80059B7C(arg0, func_800599A8(), D_800DC728, D_800DC72C, D_800DC724);
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

Object **get_object_struct_array(s32 *cnt) {
    *cnt = gObjectCount;
    return *gObjectStructArrayPtr;
}

s32 *func_8001BA90(s32 *arg0) {
    *arg0 = gObjectCount;
    return D_8011AEEC;
}

s32 *func_8001BAAC(s32 *arg0) {
    *arg0 = gObjectCount;
    return D_8011AEE8;
}

Object *get_object_struct(s32 indx) {
    if (gObjectCount == 0) {
        return NULL;
    }
    if (indx < 0 || indx >= gObjectCount) {
        return NULL;
    }
    return (*gObjectStructArrayPtr)[indx];
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

void calc_dyn_light_and_env_map_for_object(ObjectModel *model, Object *object, s32 arg2, f32 arg3) {
    s16 environmentMappingEnabled;
    s32 dynamicLightingEnabled;
    s16 i;

    dynamicLightingEnabled = 0;
    environmentMappingEnabled = 0;

    for (i = 0; i < model->numberOfBatches; i++) {
        if (model->batches[i].unk6 != 0xFF) {
            dynamicLightingEnabled = -1; // This is a bit weird, but I guess it works.
        }
        if (model->batches[i].flags & 0x8000) {
            environmentMappingEnabled = -1;
        }
    }

    if (dynamicLightingEnabled) {
        // Calculates dynamic lighting for the object
        if (object->descriptor_ptr->unk71 != 0) {
            // Dynamic lighting for some objects? (Intro diddy, Taj, T.T., Bosses)
            calc_dynamic_lighting_for_object_1(object, model, arg2, object, arg3, 1.0f);
        } else {
            // Dynamic lighting for other objects? (Racers, Rare logo, Wizpig face, etc.)
            calc_dynamic_lighting_for_object_2(object, model, arg2, arg3);
        }
    }

    if (environmentMappingEnabled) {
        // Calculates environment mapping for the object
        calc_env_mapping_for_object(model, object->z_rotation, object->x_rotation, object->y_rotation);
    }
}

GLOBAL_ASM("asm/non_matchings/unknown_00BC20/calc_dynamic_lighting_for_object_1.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/calc_env_mapping_for_object.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8001E13C.s")

/**
 * Returns a pointer to the asset in the misc. section. If index is out of range, then this
 * function just returns the pointer to gAssetsMiscSection.
 */
s32 *get_misc_asset(s32 index) {
    if (index < 0 || index >= gAssetsMiscTableLength) {
        return gAssetsMiscSection;
    }
    return (s32 *)&gAssetsMiscSection[gAssetsMiscTable[index]];
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

void func_8001E36C(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 i;
    Object *current_obj;
    *arg1 = -32000.0f;
    *arg2 = -32000.0f;
    *arg3 = -32000.0f;
    for (i = 0; i < objCount; i++) {
        current_obj = gObjPtrList[i];

        if (current_obj != NULL
        && (current_obj->unk6 & 0x8000) == 0
        && current_obj->unk48 == 39
        && current_obj->unk78 == arg0) {
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
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/catmull_rom_interpolation.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002263C.s")
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_8002277C.s")

f32 lerp(f32 *arg0, u32 arg1, f32 arg2) {
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
    Object_64 *object_64;

    D_8011AEF7 = 3;
    object_64 = get_object_struct(0)->unk64;
    object_64->unk190 = 0;
    object_64->unk192 = 0;
    object_64->unk193 = 0;
    object_64->unk1BA = 0;
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
Object *func_8002342C(f32 x, f32 z) {
    Object *retval = NULL;
    s32 i;
    Object *currObj = NULL;
    f32 x;
    f32 z;
    f32 dist;
    f32 max = 0.0f;

    for (i = 0; i < objCount; i++) {
        currObj = gObjPtrList[i];
        if ((currObj->unk6 & 0x8000) == 0 && currObj->unk48 == 87) {
            x = currObj->x_position - x;
            z = currObj->z_position - z;
            dist = sqrtf(x * x + z * z);

            if (max < dist) {
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

void func_800238BC(Object *arg0, void *arg1) {
    arg0->unk48 = arg0->descriptor_ptr->unk54;
    switch (arg0->unk48 - 1) {
        case 0x00:
            func_8004DAB0(arg0, arg1);
            break;
        case 0x01:
            func_80033CC0(arg0, arg1);
            break;
        case 0x02:
            func_80036C30(arg0, arg1);
            break;
        case 0x03:
            func_800376E0(arg0, arg1);
            break;
        case 0x05:
            func_800389AC(arg0, arg1);
            break;
        case 0x18:
            func_80038A6C(arg0, arg1);
            break;
        case 0x15:
            func_80038B74(arg0, arg1);
            break;
        case 0x06:
            func_80038E3C(arg0, arg1);
            break;
        case 0x07:
            func_8003FD68(arg0, arg1);
            break;
        case 0x08:
        case 0x12:
            func_8003FEF4(arg0, arg1);
            break;
        case 0x1A:
            func_8004001C(arg0, arg1);
            break;
        case 0x09:
            func_80039160(arg0, arg1);
            break;
        case 0x0A:
            func_80039190(arg0, arg1);
            break;
        case 0x0B:
            func_800391C8(arg0, arg1);
            break;
        case 0x0C:
            func_8003ACBC(arg0, arg1);
            break;
        case 0x1D:
            func_8003AD34(arg0, arg1);
            break;
        case 0x28:
            func_8003B058(arg0, arg1);
            break;
        case 0x0D:
            func_8003B7CC(arg0, arg1);
            break;
        case 0x6E:
            func_8003C1E0(arg0, arg1);
            break;
        case 0x0E:
            func_8003CF18(arg0, arg1);
            break;
        case 0x0F:
            func_8003CFE0(arg0, arg1);
            break;
        case 0x10:
            func_8003DFCC(arg0, arg1);
            break;
        case 0x16:
            func_8003E5B0(arg0, arg1);
            break;
        case 0x04:
        case 0x11:
            func_8003E5C8(arg0, arg1);
            break;
        case 0x19:
            func_8003CF58(arg0, arg1);
            break;
        case 0x1B:
            func_80034AF0(arg0, arg1);
            break;
        case 0x1C:
            func_800400A4(arg0, arg1);
            break;
        case 0x1E:
            func_80036194(arg0, arg1);
            break;
        case 0x1F:
            func_8003D534(arg0, arg1);
            break;
        case 0x20:
            func_800403A8(arg0, arg1);
            break;
        case 0x23:
            func_800403D8(arg0, arg1);
            break;
        case 0x42:
            func_8004049C(arg0, arg1);
            break;
        case 0x24:
            func_80040800(arg0, arg1);
            break;
        case 0x25:
            func_8003C9EC(arg0, arg1);
            break;
        case 0x26:
            func_8003CE64(arg0, arg1);
            break;
        case 0x27:
            func_8003CF00(arg0, arg1);
            break;
        case 0x2A:
            func_8004092C(arg0, arg1);
            break;
        case 0x2B:
            func_8004094C(arg0, arg1);
            break;
        case 0x2C:
            func_8003522C(arg0, arg1);
            break;
        case 0x2D:
            func_80035640(arg0, arg1);
            break;
        case 0x2E:
            func_80035EF8(arg0, arg1);
            break;
        case 0x30:
            func_80037A18(arg0, arg1);
            break;
        case 0x33:
            func_80038854(arg0, arg1);
            break;
        case 0x36:
            func_8003C644(arg0, arg1);
            break;
        case 0x38:
        case 0x5C:
            func_8003588C(arg0, arg1);
            break;
        case 0x39:
            func_80035E20(arg0, arg1);
            break;
        case 0x3A:
            func_800409A4(arg0, arg1);
            break;
        case 0x3C:
            func_800409C8(arg0, arg1);
            break;
        case 0x3D:
            func_800392B8(arg0, arg1);
            break;
        case 0x3F:
            func_8003DE74(arg0, arg1);
            break;
        case 0x40:
            func_8003D3EC(arg0, arg1);
            break;
        case 0x41:
            func_8003D038(arg0, arg1);
            break;
        case 0x43:
            func_80037578(arg0, arg1);
            break;
        case 0x44:
            func_80037624(arg0, arg1);
            break;
        case 0x45:
        case 0x66:
            func_8003818C(arg0, arg1);
            break;
        case 0x47:
        case 0x5E:
        case 0x67:
            func_800381E0(arg0, arg1);
            break;
        case 0x5F:
        case 0x64:
            func_80038214(arg0, arg1);
            break;
        case 0x60:
        case 0x65:
            func_80038248(arg0, arg1);
            break;
        case 0x46:
            func_80041A90(arg0, arg1);
            break;
        case 0x6F:
            func_80041E80(arg0, arg1);
            break;
        case 0x75:
            func_80042014(arg0, arg1);
            break;
        case 0x48:
            func_80034B68(arg0, arg1);
            break;
        case 0x49:
            func_80034E70(arg0, arg1);
            break;
        case 0x4A:
            func_8004203C(arg0, arg1);
            break;
        case 0x4B:
            func_8003D2AC(arg0, arg1);
            break;
        case 0x4C:
            func_8003B368(arg0, arg1);
            break;
        case 0x4D:
            func_80034844(arg0, arg1);
            break;
        case 0x4E:
            func_80034530(arg0, arg1);
            break;
        case 0x51:
            func_80035AE8(arg0, arg1);
            break;
        case 0x52:
            func_80037D54(arg0, arg1);
            break;
        case 0x53:
            func_80037D6C(arg0, arg1);
            break;
        case 0x58:
            func_8004210C(arg0, arg1);
            break;
        case 0x57:
            func_8003DC5C(arg0, arg1);
            break;
        case 0x59:
            func_80038AC8(arg0, arg1);
            break;
        case 0x5D:
            func_80042150(arg0, arg1);
            break;
        case 0x61:
            func_80038D58(arg0, arg1);
            break;
        case 0x62:
        case 0x63:
            func_8003572C(arg0, arg1);
            break;
        case 0x68:
            func_8004216C(arg0, arg1);
            break;
        case 0x6B:
        case 0x73:
            func_80033F44(arg0, arg1);
            break;
        case 0x6C:
            func_80042210(arg0, arg1);
            break;
        case 0x6D:
            func_8003DBA0(arg0, arg1);
            break;
        case 0x74:
            func_80042A1C(arg0, arg1);
            break;
    }
}

#ifdef NON_MATCHING
s32 func_80023E30(s32 arg0) {
    switch (arg0 - 1) {
        case 0x00:
            return 0x1F;
        case 0x01:
            return 0x13;
        case 0x04:
            return 0x16;
        case 0x0B:
            return 0x1B;
        case 0x0D:
        case 0x6E:
            return 0x30;
        case 0x10:
        case 0x4C:
            return 0x12;
        case 0x45:
        case 0x47:
        case 0x5F:
        case 0x60:
            return 0x3B;
        case 0x64:
        case 0x65:
        case 0x66:
        case 0x67:
            return 0x3A;
        case 0x17:
            return 0x04;
        case 0x1E:
            return 0x1B;
        case 0x1F:
        case 0x3F:
        case 0x57:
        case 0x6D:
            return 0x12;
        case 0x42:
            return 0x30;
        case 0x25:
            return 0x39;
        case 0x26:
            return 0x12;
        case 0x27:
            return 0x09;
        case 0x2C:
            return 0x12;
        case 0x2F:
            return 0x09;
        case 0x3E:
            return 0x09;
        case 0x31:
        case 0x37:
        case 0x4F:
        case 0x53:
        case 0x55:
        case 0x72:
            return 0x0B;
        case 0x35:
            return 0x0B;
        case 0x49:
        case 0x5E:
        case 0x62:
        case 0x63:
            return 0x31;
        case 0x5A:
            return 0x01;
        case 0x50:
            return 0x0A;
        case 0x06:
        case 0x0C:
        case 0x11:
        case 0x19:
        case 0x1D:
        case 0x23:
        case 0x28:
        case 0x33:
        case 0x36:
        case 0x38:
        case 0x43:
        case 0x4D:
        case 0x4E:
        case 0x5C:
        case 0x61:
        case 0x6B:
        case 0x73:
            return 0x10;
        case 0x51:
            return 0x12;
        case 0x30:
        case 0x32:
        case 0x3C:
            return 0x02;
        case 0x3D:
            return 0x1B;
        case 0x6C:
            return 0x0B;
        case 0x71:
            return 0x01;
        default:
            return 0x00;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_00BC20/func_80023E30.s")
#endif

void run_object_loop_func(Object *obj, s32 arg1) {
    func_800B76B8(1, obj->unk4A);
    switch (obj->unk48) {
        case 2:
            func_80033DD0(obj, arg1);
            break;
        case 3:
            func_800370D4(obj, arg1);
            break;
        case 4:
            func_800377E4(obj, arg1);
            break;
        case 6:
            func_800389B8(obj, arg1);
            break;
        case 25:
            func_80038A78(obj, arg1);
            break;
        case 22:
            func_80038BF4(obj, arg1);
            break;
        case 7:
            func_80038F58(obj, arg1);
            break;
        case 10:
            func_80039184(obj, arg1);
            break;
        case 11:
            func_800391BC(obj, arg1);
            break;
        case 12:
            func_800391FC(obj, arg1);
            break;
        case 13:
            func_8003AD28(obj, arg1);
            break;
        case 30:
            func_8003AE50(obj, arg1);
            break;
        case 41:
            func_8003B174(obj, arg1);
            break;
        case 14:
            func_8003B988(obj, arg1);
            break;
        case 15:
            func_80030A74(obj);
            break;
        case 16:
            func_8003D02C(obj, arg1);
            break;
        case 17:
            func_8003E140(obj, arg1);
            break;
        case 23:
            func_8003E5BC(obj, arg1);
            break;
        case 5:
        case 18:
            func_8003E630(obj, arg1);
            break;
        case 26:
            func_8003CF98(obj, arg1);
            break;
        case 28:
            func_80034B4C(obj, arg1);
            break;
        case 29:
            func_80040148(obj, arg1);
            break;
        case 31:
            func_800361E0(obj, arg1);
            break;
        case 32:
            func_8003D5A0(obj, arg1);
            break;
        case 36:
            func_80040448(obj, arg1);
            break;
        case 67:
            func_80040570(obj, arg1);
            break;
        case 37:
            func_80040820(obj, arg1);
            break;
        case 38:
            func_8003CA68(obj, arg1);
            break;
        case 39:
            func_8003CEA0(obj, arg1);
            break;
        case 40:
            func_8003CF0C(obj, arg1);
            break;
        case 45:
            func_80035260(obj, arg1);
            break;
        case 46:
            func_8003564C(obj, arg1);
            break;
        case 47:
            func_80035F6C(obj, arg1);
            break;
        case 50:
        case 81:
        case 85:
        case 86:
            func_80037CE8(obj, arg1);
            break;
        case 119:
            func_80042CD0(obj, arg1);
            break;
        case 51:
            func_80038710(obj, arg1);
            break;
        case 52:
            func_800388D4(obj, arg1);
            break;
        case 53:
            func_800387CC(obj, arg1);
            break;
        case 54:
            func_8003833C(obj, arg1);
            break;
        case 55:
            func_8003C7A4(obj, arg1);
            break;
        case 56:
            func_800380F8(obj, arg1);
            break;
        case 57:
        case 93:
            func_8003596C(obj, arg1);
            break;
        case 58:
            func_80035E34(obj, arg1);
            break;
        case 60:
            func_800BFFDC(obj);
            break;
        case 61:
            func_80040C54(obj, arg1);
            break;
        case 62:
            func_80039330(obj, arg1);
            break;
        case 64:
            obj_loop_world_key(obj, arg1); //arg1=speed
            break;
        case 65:
            func_8003D3FC(obj, arg1);
            break;
        case 66:
            func_8003D058(obj, arg1);
            break;
        case 68:
            func_80037594(obj, arg1);
            break;
        case 69:
            func_8003763C(obj, arg1);
            break;
        case 70:
        case 72:
        case 103:
        case 104:
            func_800381C0(obj, arg1);
            break;
        case 96:
        case 97:
        case 101:
        case 102:
            func_8003827C(obj, arg1);
            break;
        case 73:
            func_80034B74(obj, arg1);
            break;
        case 74:
            func_80034E9C(obj, arg1);
            break;
        case 75:
            func_80042090(obj, arg1);
            break;
        case 76:
            func_8003D2B8(obj, arg1);
            break;
        case 77:
            func_8003B4BC(obj, arg1);
            break;
        case 78:
            func_80034860(obj, arg1);
            break;
        case 79:
            func_800345A0(obj, arg1);
            break;
        case 80:
            func_8003ACA0(obj, arg1);
            break;
        case 82:
            func_80035C50(obj, arg1);
            break;
        case 84:
            func_80037D78(obj, arg1);
            break;
        case 88:
        case 110:
            func_8003DD14(obj, arg1);
            break;
        case 90:
            func_80038AD4(obj, arg1);
            break;
        case 94:
            func_80042160(obj, arg1);
            break;
        case 98:
            func_80038DC4(obj, arg1);
            break;
        case 105:
            func_80042178(obj, arg1);
            break;
        case 100:
            func_800357D4(obj, arg1);
            break;
        case 108:
        case 116:
            func_80033F60(obj, arg1);
            break;
        case 109:
            func_800422F0(obj, arg1);
            break;
        case 111:
            func_8003C2E4(obj, arg1);
            break;
        case 113:
            func_80037D08(obj, arg1);
            break;
        case 115:
            func_80042998(obj, arg1);
            break;
        case 117:
            func_80042A90(obj, arg1);
            break;
    }
    func_800B76B8(1, -1);
}

// Unused
void func_8002458C(s32 arg0) {
}

s16 *func_80024594(s32 *arg0, s32 *arg1) {
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
