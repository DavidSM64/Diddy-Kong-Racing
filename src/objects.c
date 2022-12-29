/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8000B020 */

#include "objects.h"
#include "memory.h"

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "level_object_entries.h"
#include "asset_enums.h"
#include "asset_loading.h"
#include "thread0_epc.h"
#include "save_data.h"
#include "menu.h"
#include "game.h"
#include "racer.h"
#include "particles.h"
#include "printf.h"
#include "unknown_0255E0.h"
#include "math_util.h"
#include "camera.h"
#include "waves.h"
#include "object_functions.h"
#include "object_models.h"
#include "unknown_032760.h"
#include "game_ui.h"
#include "unknown_008C40.h"
#include "main.h"

#define MAX_CHECKPOINTS 60
#define OBJECT_POOL_SIZE 0x15800
#define OBJECT_SLOT_COUNT 512

/************ .data ************/

unknown800DC6F0 D_800DC6F0 = { { -128 }, 0x1E, 0x0F };
unknown800DC6F0 D_800DC6F8 = { { 3 }, 0x1E, 0x0F };

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
u8 gHasGhostToSave = 0;
s32 D_800DC734 = 0; // Currently unknown, might be a different type.
u8 D_800DC738 = 0;
s8 D_800DC73C = 0;
s8 D_800DC740 = 0;
s8 D_800DC744 = 0;
s8 D_800DC748 = 0;
s32 D_800DC74C[2] = {0, 0}; // Have a feeling these are both the same array.
s32 D_800DC754[2] = {0, 0};
Object *D_800DC75C = NULL; // Currently unknown, might be a different type.
s32 D_800DC760 = 9; // Currently unknown, might be a different type.
Object *D_800DC764 = NULL; // Currently unknown, might be a different type.
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

// A table of which vehicles to use for boss races.
// https://www.youtube.com/watch?v=WQJAtns_rMk
s16 gBossVehicles[16] = {
    0x0005, 0x0106, 0x0207, 0x0005,
    0x0106, 0x010B, 0x010B, 0x0207,
    0x000C, 0x020D, 0x0101, 0x0101,
    0x0101, 0x0101, 0x0101, 0x0000,
};
s8 D_800DC840[8] = { 9, 1, 2, 3, 4, 5, 7, 0 };

s8 D_800DC848 = 0;
u32 D_800DC84C[3] = {
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

UNUSED const char sObjectOutofMemString[] = "Objects out of ram(1) !!\n";
UNUSED const char sDoorNumberErrorString[] = "Door numbering error %d!!\n";
UNUSED const char sObjectScopeErrorString[] = "objGetScope: Unknown scope for object %d\n";
UNUSED const char sObjectListDataOverflowString[] = "ObjList (Part) Overflow %d!!!\n";
UNUSED const char sObjectSetupError1String[] = "ObjSetupObject(1) Memory fail!!\n";
UNUSED const char sObjectSetupError2String[] = "ObjSetupObject(2) Memory fail!!\n";
UNUSED const char sObjectSetupError5String[] = "ObjSetupObject(5) Memory fail!!\n";
UNUSED const char sObjectSetupError6String[] = "ObjSetupObject(6) Memory fail!!\n";
UNUSED const char sObjectSetupError3String[] = "ObjSetupObject(3) Memory fail!!\n";
UNUSED const char sObjectListOverflowString[] = "ObjList Overflow %d!!!\n";
UNUSED const char sObjectSetupError4String[] = "ObjSetupObject(4) Memory fail!!\n";
UNUSED const char sDuplicateCheckpointString[] = "Error: Multiple checkpoint no: %d !!\n";
UNUSED const char sErrorChannelString[] = "ERROR Channel %d\n";
UNUSED const char sReadOutErrorString[] = "RO error %d!!\n";
UNUSED const char sPureAnguishString[] = "ARGHHHHHHHHH\n";
extern f32 D_800E5644;

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
Object *D_8011AD34;
s32 D_8011AD38; //D_8011AD38 is ultimately set by func_80074B34, and is almost definitely SIDeviceStatus
s8 D_8011AD3C;
s8 D_8011AD3D;
s8 D_8011AD3E;
Object *D_8011AD40;
s8 D_8011AD44;
s8 gOverworldVehicle;
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
s32 gRaceStartCountdown;
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
s8 gIsNonCarRacers;
s8 gIsSilverCoinRace;
Object *D_8011AE08[16];
s32 (*D_8011AE48)[8]; // Unknown number of entries.
u8 (*D_8011AE4C)[8];  // Unknown number of entries.
s32 D_8011AE50;
TextureHeader *D_8011AE54;
Object **gObjPtrList; // Not sure about the number of elements
s32 objCount;
s32 D_8011AE60;
s32 D_8011AE64;
Object *gObjectMemoryPool;
s32 *D_8011AE6C;
s32 D_8011AE70;
Object **D_8011AE74;
s16 D_8011AE78;
s16 D_8011AE7A;
s16 D_8011AE7C;
s8 D_8011AE7E;
s16 gTTGhostTimeToBeat;
s16 D_8011AE82;
s16 gMapDefaultVehicle; // Vehicle enum
s32 D_8011AE88;
Gfx *gObjectCurrDisplayList;
MatrixS *gObjectCurrMatrix;
Vertex *gObjectCurrVertexList;
u8 *D_8011AE98[2];
s32 D_8011AEA0[2];
s32 D_8011AEA8[2];
s32 D_8011AEB0[2];
s16 *gAssetsLvlObjTranslationTable;
s32 gAssetsLvlObjTranslationTableLength;
s32 D_8011AEC0;
Object **gParticlePtrList;
s32 gParticleCount;
CheckpointNode *gTrackCheckpoints; // Array of structs, unknown number of members
s32 gNumberOfCheckpoints;
s32 D_8011AED4;
s16 D_8011AED8;
u32 (*D_8011AEDC)[64]; // Not sure about the number of elements
s32 D_8011AEE0;
Object *(*gRacers)[8];
// Similar to gRacers, but sorts the pointer by the players' current position in the race.
Object **gRacersByPosition;
// Similar to gRacers, but sorts the pointer by controller ports 1-4, then CPUs.
Object **gRacersByPort;
s32 gNumRacers;
u8 gTimeTrialEnabled;
u8 D_8011AEF5;
u8 D_8011AEF6;
s8 D_8011AEF7;
s32 D_8011AEF8;
s32 D_8011AEFC;
s8 D_8011AF00;
Object *(*D_8011AF04)[64]; // Not sure about the number of elements
s32 D_8011AF08[2];
s32 D_8011AF10[2];
f32 D_8011AF18[4];
s32 D_8011AF28;
s32 D_8011AF2C;
s32 D_8011AF30;
s32 D_8011AF34;
s32 D_8011AF38[10];
s32 D_8011AF60[2];
s32 D_8011AF68[32];
VertexPosition D_8011AFE8;
s16 D_8011AFEE;
s32 D_8011AFF0;
unk800179D0 *D_8011AFF4;
s32 D_8011AFF8;
s32 D_8011AFFC;
s32 D_8011B000;
s32 D_8011B004;
s32 D_8011B008;
u8 D_8011B010[16];
Object *D_8011B020[10];
s32 D_8011B048[4];
s32 D_8011B058[4];
s32 D_8011B068[4];
u8 D_8011B078[3];
u8 D_8011B07B[1];
s32 D_8011B080[7];

extern s16 D_8011D5AC;

/******************************/

GLOBAL_ASM("asm/non_matchings/objects/func_8000B020.s")

struct TempStruct9 {
    u8 pad[0x78];
    Sprite* unk78;
    TextureHeader* unk7C;
};

void func_8000B290(void) {
    Sprite *temp_a0_2;
    TextureHeader *temp_a0_3;
    s32 temp_a0;
    struct TempStruct9 *var_s0;
    u32 i;

    temp_a0 = D_800DC754[0];
    if (temp_a0 != 0) {
        free_from_memory_pool((void* ) temp_a0);
        D_800DC754[0] = 0;
        D_800DC754[1] = 0;
        D_800DC74C[0] = 0;
        D_800DC74C[1] = 0;
    }
    var_s0 = (struct TempStruct9 *) get_misc_asset(0x14);
    for (i = 0; i < 10; i++) {
        temp_a0_2 = var_s0[i].unk78;
        if (temp_a0_2 != 0) {
            free_sprite(temp_a0_2);
            var_s0[i].unk78 = 0;
        }
        temp_a0_3 = var_s0[i].unk7C;
        if (temp_a0_3 != 0) {
            free_texture(temp_a0_3);
            var_s0[i].unk7C = 0;
        }
    }
    if (D_800DC75C)
        gParticlePtrList_addObject(D_800DC75C);
    D_800DC75C = NULL;

    if (D_800DC764)
        gParticlePtrList_addObject(D_800DC764);
    D_800DC764 = NULL;
    gParticlePtrList_flush();
}

GLOBAL_ASM("asm/non_matchings/objects/func_8000B38C.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8000B750.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8000BADC.s")

Object *func_8000BF44(s32 arg0) {
    if (arg0 == -1) {
        arg0 = D_800DC760;
    }
    if (arg0 < 0 || arg0 >= 10) {
        return NULL;
    }
    return D_8011B020[arg0];
}

void allocate_object_pools(void) {
    s32 i;

    func_8001D258(0.67f, 0.33f, 0, -0x2000, 0);
    gObjectMemoryPool = (Object *) new_sub_memory_pool(OBJECT_POOL_SIZE, OBJECT_SLOT_COUNT);
    gParticlePtrList = (Object **) allocate_from_main_pool_safe(sizeof(uintptr_t) * 200, COLOUR_TAG_BLUE);
    D_8011AE6C = (s32 *) allocate_from_main_pool_safe(0x50, COLOUR_TAG_BLUE);
    D_8011AE74 = (Object **) allocate_from_main_pool_safe(0x200, COLOUR_TAG_BLUE);
    gTrackCheckpoints = (CheckpointNode *) allocate_from_main_pool_safe(sizeof(CheckpointNode) * MAX_CHECKPOINTS, COLOUR_TAG_BLUE);
    D_8011AEDC = allocate_from_main_pool_safe(0x50, COLOUR_TAG_BLUE);
    gRacers = allocate_from_main_pool_safe(sizeof(uintptr_t) * 10, COLOUR_TAG_BLUE);
    gRacersByPort = (Object **) allocate_from_main_pool_safe(sizeof(uintptr_t) * 10, COLOUR_TAG_BLUE);
    gRacersByPosition = (Object **) allocate_from_main_pool_safe(sizeof(uintptr_t) * 10, COLOUR_TAG_BLUE);
    D_8011AF04 = allocate_from_main_pool_safe(0x200, COLOUR_TAG_BLUE);
    D_8011ADCC = allocate_from_main_pool_safe(8, COLOUR_TAG_BLUE);
    D_8011AFF4 = (unk800179D0 *) allocate_from_main_pool_safe(0x400, COLOUR_TAG_BLUE);
    gAssetsLvlObjTranslationTable = (s16 *) load_asset_section_from_rom(ASSET_LEVEL_OBJECT_TRANSLATION_TABLE);
    gAssetsLvlObjTranslationTableLength = (get_size_of_asset_section(ASSET_LEVEL_OBJECT_TRANSLATION_TABLE) >> 1) - 1;
    while (gAssetsLvlObjTranslationTable[gAssetsLvlObjTranslationTableLength] == 0) {
        gAssetsLvlObjTranslationTableLength--;
    }
    D_8011AD58 = (s32 *) allocate_from_main_pool_safe(0x800, COLOUR_TAG_BLUE);
    gAssetsObjectHeadersTable = (s32 *) load_asset_section_from_rom(ASSET_OBJECT_HEADERS_TABLE);
    gAssetsObjectHeadersTableLength = 0;
    while (-1 != gAssetsObjectHeadersTable[gAssetsObjectHeadersTableLength]) {
        gAssetsObjectHeadersTableLength++;
    }
    gAssetsObjectHeadersTableLength--;
    D_8011AE48 = allocate_from_main_pool_safe(gAssetsObjectHeadersTableLength * 4, COLOUR_TAG_WHITE);
    D_8011AE4C = allocate_from_main_pool_safe(gAssetsObjectHeadersTableLength, COLOUR_TAG_WHITE);

    for (i = 0; i < gAssetsObjectHeadersTableLength; i++) {
        (*D_8011AE4C)[i] = 0;
    }

    gAssetsMiscSection = (s32 *) load_asset_section_from_rom(ASSET_MISC);
    gAssetsMiscTable = (s32 *) load_asset_section_from_rom(ASSET_MISC_TABLE);
    gAssetsMiscTableLength = 0;
    while (-1 != gAssetsMiscTable[gAssetsMiscTableLength]) {
        gAssetsMiscTableLength++;
    }

    decrypt_magic_codes(&gAssetsMiscSection[gAssetsMiscTable[65]], (gAssetsMiscTable[66] - gAssetsMiscTable[65]) * 4);
    gObjPtrList = (Object **) allocate_from_main_pool_safe(sizeof(uintptr_t) * OBJECT_SLOT_COUNT, COLOUR_TAG_BLUE);
    D_8011ADC4 = 0;
    gTimeTrialEnabled = 0;
    D_8011AEF5 = 0;
    D_8011ADA8 = 2.0f;
    func_8000C460();
}

#ifdef NON_EQUIVALENT
// Decrypts cheats
void decrypt_magic_codes(s32 *data, s32 length) {
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
#else
GLOBAL_ASM("asm/non_matchings/objects/decrypt_magic_codes.s")
#endif

void func_8000C460(void) {
    s32 i;

    D_8011AD26[0] = 1;
    D_8011AD5C = 0;
    D_8011AD60 = 0;
    gParticleCount = 0;
    D_8011AE70 = 0;
    gNumberOfCheckpoints = 0;
    D_8011AED4 = 0;
    gNumRacers = 0;
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
    free_from_memory_pool((void *) D_8011AEB0[0]);
    free_from_memory_pool((void *) D_8011AEB0[1]);
}

GLOBAL_ASM("asm/non_matchings/objects/func_8000C718.s")

void func_8000C844(s32 arg0) {
    if ((*D_8011AE4C)[arg0] != 0) {
        (*D_8011AE4C)[arg0]--;
        if ((*D_8011AE4C)[arg0] == 0) {
            free_from_memory_pool((void *) (*D_8011AE48)[arg0]);
        }
    }
}

/**
 * Converts the passed value into an accurate countdown value based on the systems region.
 * Since PAL runs at 50Hz, it therefore will reduce the timer to 5/6 to match, keeping
 * it consistent with non PAL timers, running 60Hz.
 */
s32 normalise_time(s32 timer) {
    if (osTvType != TV_TYPE_PAL || timer < 0) {
        return timer;
    } else {
        return (timer * 5) / 6;
    }
}

GLOBAL_ASM("asm/non_matchings/objects/func_8000C8F8.s")

// Reset all values of D_8011AE08 to NULL
void func_8000CBC0(void) {
    s32 i; //Required to be one line to match
    for (i = 0; i < ARRAY_COUNT(D_8011AE08); i++) { D_8011AE08[i] = NULL; }
}

// Set the object value for the given index if it's not already set
void func_8000CBF0(Object *obj, s32 index) {
    if (D_8011AE08[index] == NULL) {
        D_8011AE08[index] = obj;
    } else {
        if(D_8011AE08[index]){}
    }
}

// Set the next available value in D_8011AE08, and return it's index value. -1 if it's not set.
s32 func_8000CC20(Object *obj) {
    s32 i;
    s32 NextFreeIndex;

    NextFreeIndex = -1;
    for (i = 0; i < ARRAY_COUNT(D_8011AE08); i++) {
        if (D_8011AE08[i] == NULL) {
            NextFreeIndex = i;
            i = ARRAY_COUNT(D_8011AE08); // Why not just break?
        }
    }
    if (NextFreeIndex != -1) {
        D_8011AE08[NextFreeIndex] = obj;
    }
    return NextFreeIndex;
}

// Has a jump table
GLOBAL_ASM("asm/non_matchings/objects/func_8000CC7C.s")

u32 func_8000E0B0(void) {
    // D_8011AD38 is likely an SIDeviceStatus value, but not 100% sure yet.
    switch (D_8011AD38) {
        case 1: //NO_CONTROLLER_PAK
            return -1;
        case 7: //RUMBLE_PAK
            return 0;
        case 2: //CONTROLLER_PAK_INCONSISTENT
        case 3: //CONTROLLER_PAK_WITH_BAD_ID
            return 3;
        case 4: //CONTROLLER_PAK_FULL
        case 6: //CONTROLLER_PAK_UNK6
            return 2;
        case 0: //CONTROLLER_PAK_GOOD
        case 5: //CONTROLLER_PAK_CHANGED
        case 8: //CONTROLLER_PAK_UNK8
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

/**
 * Return true if there exist players piloting planes or hovercraft.
 * Used to determine whether to use certain zippers.
 */
s8 find_non_car_racers(void) {
    return gIsNonCarRacers;
}

/**
 * Return true if the silver coin race mode is active.
 * Used to determine whether to spawn silver coins.
 */
s8 check_if_silver_coin_race() {
    return gIsSilverCoinRace;
}

void func_8000E1EC(Object *obj, s32 vehicleID) {
    D_8011AD40 = obj;
    D_8011AD44 = 4;
    gOverworldVehicle = vehicleID;
    D_8011AD46 = obj->segment.trans.x_position;
    D_8011AD48 = obj->segment.trans.y_position;
    D_8011AD4A = obj->segment.trans.z_position;
    D_8011AD4C = obj->segment.trans.y_rotation;
    gParticlePtrList_addObject(obj);
    gNumRacers = 0;
}

void func_8000E2B4(void) {
    Object *player;
    LevelObjectEntry8000E2B4 sp2C;
    Settings *settings;
    Object_Racer *player_64;
    s16 object_id;

    if (!D_8011AD44) {
        return;
    }
    D_8011AD44--;
    if (D_8011AD44) {
        return;
    }
    settings = get_settings();
    sp2C.unkE = 0;
    sp2C.common.size = 0x10;
    if (gOverworldVehicle < 5) {
        object_id = ((s16 *) D_800DC7A8)[settings->racers[0].character + gOverworldVehicle * 10];
    } else {
        object_id = D_800DC7B8[gOverworldVehicle + 37];
    }
    set_level_default_vehicle(gOverworldVehicle);
    sp2C.common.size = sp2C.common.size | ((s32) (object_id & 0x100) >> 1);
    sp2C.unkA = 0;
    sp2C.unk8 = 0;
    sp2C.common.objectID = object_id;
    sp2C.common.x = D_8011AD46;
    sp2C.common.y = D_8011AD48;
    sp2C.common.z = D_8011AD4A;
    sp2C.unkC = D_8011AD4C;
    func_800521B8(1);
    player = spawn_object(&sp2C, 0x11);
    gNumRacers = 1;
    (*gRacers)[0] = player;
    gRacersByPort[0] = player;
    *gRacersByPosition = player;
    player_64 = &player->unk64->racer;
    player_64->unk1D6 = gOverworldVehicle;
    player_64->unk1D7 = gOverworldVehicle;
    player_64->unk2 = 0;
    player_64->characterId = (s8) settings->racers[0].character;
    player_64->playerIndex = 0;
    player_64->unk118 = 0;
    if (get_filtered_cheats() & CHEAT_BIG_CHARACTERS) {
        player->segment.trans.scale *= 1.4f;
    }
    if (get_filtered_cheats() & CHEAT_SMALL_CHARACTERS) {
        player->segment.trans.scale *= 0.714f;
    }
    player->segment.unk3C_a.level_entry = NULL;
    player->segment.trans.y_rotation = D_8011AD4C;
    player->segment.trans.y_position = D_8011AD48;
}

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

void func_8000E4E8(s32 index) {
    s32 *temp_v0;
    s32 i;
    u8 *temp_a1;

    temp_v0 = (s32 *) D_8011AEB0[index];
    temp_v0[0] = D_8011AEA0[index];
    temp_v0[3] = 0;
    temp_v0[2] = 0;
    temp_v0[1] = 0;
    temp_a1 = &D_8011AE98[index][D_8011AEA0[index]]; 
    
    // The backslash here is needed to match. And no, a for loop doesn't match.
    i = 0; \
    while(i < 16) {
        temp_a1[i] = 0;
        i++;
    }
}

s32 func_8000E558(Object *arg0){
    s32 temp_v0;
    s32 new_var, new_var2;
    if (arg0->segment.unk3C_a.level_entry == NULL) {
        return TRUE;
    }
    temp_v0 = (s32) arg0->segment.unk3C_a.level_entry;
    new_var2 = (s32) D_8011AE98[0];
    if ((temp_v0 >= new_var2) && (((D_8011AEA0[0] * 8) + new_var2) >= temp_v0)) {
        return FALSE;
    }
    new_var = (s32) D_8011AE98[1];
    // Why even bother with this check?
    if (temp_v0 >= new_var && temp_v0 <= ((D_8011AEA0[1] * 8) + new_var)) {
        return TRUE;
    }
    return TRUE;
}

GLOBAL_ASM("asm/non_matchings/objects/func_8000E5EC.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8000E79C.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8000E898.s")

/**
 * Returns the object at the current offset by ID.
*/
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
    arg0->segment.trans.unk6 |= 0x8000;
    func_800245B4(arg0->segment.unk2C.half.upper | 0xC000);
    gObjPtrList[objCount++] = arg0;
    if (1) {}  // Fakematch
    D_8011AE64++;
}

GLOBAL_ASM("asm/non_matchings/objects/spawn_object.s")

void func_8000F648(Object *obj, s32 count, s32 objType) {
    s32 i;
    if (objType == 0) { // 3D model
        for (i = 0; i < count; i++) {
            if (obj->unk68[i] != NULL) {
                func_8005FF40((ObjectModel **) (s32) obj->unk68[i]);
            }
        } 
    } else if (objType == 4) {
        for (i = 0; i < count; i++) {
            if (obj->unk68[i] != NULL) {
                free_texture((TextureHeader *) (s32) obj->unk68[i]);
            }
        } 
    } else { // Sprite
        for (i = 0; i < count; i++) {
            if (obj->unk68[i] != NULL) {
                free_sprite((Sprite *) (s32) obj->unk68[i]);
            }
        }
    }
}

void func_8000F758(Object *obj) {
    s32 i;
    for(i = 0; i < obj->segment.header->unk5A; i++) {
        obj->unk70[i] = func_80031F88(obj, &obj->segment.header->unk24[i]);
    }
}

GLOBAL_ASM("asm/non_matchings/objects/func_8000F7EC.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8000F99C.s")

s32 func_8000FAC4(Object *obj, Object_6C *arg1) {
    ObjHeaderParticleEntry *particleDataEntry;
    s32 i;

    obj->unk6C = arg1;
    particleDataEntry = obj->segment.header->objectParticles;
    for(i = 0; i < obj->segment.header->unk57; i++) {
        if ((particleDataEntry[i].upper & 0xFFFF0000) == 0xFFFF0000) {
            func_800AF1E0((Object *) &obj->unk6C[i], (particleDataEntry[i].upper >> 8) & 0xFF, particleDataEntry[i].upper & 0xFF);
        } else {
            func_800AF29C((Object *) &obj->unk6C[i],
                (particleDataEntry[i].upper >> 0x18) & 0xFF,
                (particleDataEntry[i].upper >> 0x10) & 0xFF,
                particleDataEntry[i].upper & 0xFFFF,
                (particleDataEntry[i].lower >> 0x10) & 0xFFFF,
                particleDataEntry[i].lower & 0xFFFF
            );
        }
    }
    return ((obj->segment.header->unk57 << 5) + 3) & ~3;
}

s32 func_8000FBCC(Object *arg0, Object_60 *arg1) {
    s32 var_v0;
    ObjectHeader *objHeader;

    arg0->unk50 = (Object_50*) arg1;
    arg1->unk4 = NULL;
    objHeader = ((ObjectSegment*) arg0)->header;
    if (objHeader->unk32) {
        arg1->unk4 = (s32 *) load_texture((s32) ((ObjectHeader *) objHeader)->unk34);
        objHeader = ((ObjectSegment*)arg0)->header;
    }
    ((Object_50*) arg1)->unk0 = (f32) objHeader->unk4;
    ((Object_50*) arg1)->unk8 = -1;
    D_8011AE50 = (s32) ((Object_60*)arg1)->unk4;
    var_v0 = 16;
    if ((((ObjectSegment*) arg0)->header->unk32) && (arg1->unk4 == NULL)) {
        return 0;
    }
    return var_v0;
}

s32 func_8000FC6C(struct_8000FC6C_3 *arg0, struct_8000FC6C *arg1) {
    arg0->unk58 = arg1;
    arg1->unk0 = arg0->unk40->unk8;
    arg1->unkC = 0;
    arg1->unkE = arg0->unk40->unk0 >> 8;
    arg1->unk4 = NULL;
    if (arg0->unk40->unk36) {
        arg1->unk4 = load_texture(arg0->unk40->unk38);
    }
    arg1->unk8 = -1;
    D_8011AE54 = arg1->unk4;
    if (arg0->unk40->unk36 && arg1->unk4 == NULL) {
        return 0;
    }
    return 20;
}

s32 func_8000FD20(unk8000FD20 *arg0, unk8000FD20_2 *arg1) {
    arg0->unk4C = arg1;
    arg1->unk13 = 0xFF;
    return 40;
}

s32 func_8000FD34(unk8000FD34 *arg0, unk_80016BC4_2 *arg1) {
    arg0->unk5C = arg1;
    func_80016BC4(arg0);
    return 268;
}

GLOBAL_ASM("asm/non_matchings/objects/func_8000FD54.s")

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

/*
 * Clears all existing particles from the object list
 */
void gParticlePtrList_flush(void) {
    s32 j, i, search_indx;
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
            if (search_indx < D_8011AE7C) {
                D_8011AE7C--;
            }
            objCount--;
            if (0) {} // Fakematch
            for (j = search_indx; j < objCount; j++) {
                gObjPtrList[j] = gObjPtrList[j + 1];
            }
        }
        func_800101AC(searchObj, 0);
    }
    gParticleCount = 0;
}

GLOBAL_ASM("asm/non_matchings/objects/func_800101AC.s")
GLOBAL_ASM("asm/non_matchings/objects/func_80010994.s")

#ifdef NON_EQUIVALENT
void func_80011134(Object *arg0, s32 arg1) {
    s32 sp5C;
    ObjectModel *temp_s3;
    TriangleBatchInfo *temp_s4;
    TriangleBatchInfo *var_s0;
    TextureHeader *var_t5;
    s16 temp_s5;
    s32 var_s1;
    u8 temp_v0;

    temp_s3 = arg0->unk68[arg0->segment.unk38.byte.unk3A]->objModel;
    temp_s5 = temp_s3->unk50;
    temp_s4 = temp_s3->batches;
    for (var_s1 = 0; temp_s5 > 0 && var_s1 < temp_s3->numberOfBatches; var_s1++) {
        var_s0 = &temp_s4[var_s1];
        if (var_s0->flags & 0x10000) { //Texture is animated
            temp_v0 = var_s0->textureIndex;
            if (temp_v0 != 0xFF) {
                var_t5 = temp_s3->textures[temp_v0].texture;
                sp5C = var_s0->unk7 << 6;
                func_8007EF80(var_t5, temp_s4[var_s1].flags, &sp5C, arg1);
                var_s0->unk7 = sp5C >> 6;
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/objects/func_80011134.s")
#endif

GLOBAL_ASM("asm/non_matchings/objects/func_80011264.s")

void func_80011390(void) {
    D_8011ADAC = 0;
}

s32 func_8001139C() {
    return D_8011ADB0;
}

/**
 * Return the timer countdown before the race starts.
 * There exists another variable in racer.c with exactly the same purpose.
 * This does not get used anywhere else.
 */
s32 get_race_start_timer() {
    return gRaceStartCountdown;
}

// Unused function, purpose currently unknown.
UNUSED s32 func_800113BC() {
    return D_8011ADBC;
}

GLOBAL_ASM("asm/non_matchings/objects/func_800113CC.s")

s32 func_80011560(void) { //! @bug The developers probably intended this to be a void function.
    D_800DC848 = 1;
    // No return value!
}

s32 func_80011570(Object *obj, f32 xPos, f32 yPos, f32 zPos) {
    UNUSED f32 unused;
    f32 test1, test2, test3, test4, test5, test6;
    f32 newXPos;
    f32 newYPos;
    f32 newZPos;
    LevelModel *levelModel;
    LevelModelSegmentBoundingBox *box;
    s32 var_a0;
    s32 var_v1;
    s32 intXPos, intYPos, intZPos;

    levelModel = get_current_level_model();
    newXPos = obj->segment.trans.x_position + xPos;
    newYPos = obj->segment.trans.y_position + yPos;
    newZPos = obj->segment.trans.z_position + zPos;
    if (levelModel == NULL) {
        D_800DC848 = 0;
        return 0;
    }
    var_v1 = 0;
    test1 = (levelModel->unk3E + 1000.0f);
    if (newXPos > test1) {
        var_v1 = 1;
    }
    test2 = (levelModel->unk3C - 1000.0f);
    if (obj->segment.trans.x_position < test2) {
        var_v1 = 1;
    }
    if (1) { } if (1) { } if (1) { }
    test3 = (levelModel->unk42 + 3000.0f);
    if (obj->segment.trans.y_position > test3) {
        var_v1 = 1;
    }
    test4 = (levelModel->unk40 - 500.00);
    if (obj->segment.trans.y_position < test4) {
        var_v1 = 1;
    }
    test5 = (levelModel->unk46 + 1000.0f);
    if (obj->segment.trans.z_position > test5) {
        var_v1 = 1;
    }
    test6 = (levelModel->unk44 - 1000.0f);
    if (obj->segment.trans.z_position < test6) {
        var_v1 = 1;
    }
    if (D_800DC848 != 0) {
        var_v1 = 0;
    }
    
    D_800DC848 = 0;
    if (var_v1 != 0) {
        obj->segment.unk2C.half.lower = -1;
        return 1;
    }

    obj->segment.trans.x_position = newXPos;
    obj->segment.trans.y_position = newYPos;
    obj->segment.trans.z_position = newZPos;
    box = func_8002A2DC(obj->segment.unk2C.half.lower);

    //For some reason the XYZ positions are converted into integers for the next section
    intXPos = newXPos, intYPos = newYPos, intZPos = newZPos;
    
    if (box == NULL) {
        obj->segment.unk2C.half.lower = get_level_segment_index_from_position(intXPos, intYPos, intZPos);
        return 0;
    } else {
        var_a0 = 0;
        if ((box->x2 < intXPos) || (intXPos < box->x1)) {
            var_a0 = 1;
        }
        if ((box->y2 < intYPos) || (intYPos < box->y1)) {
            var_a0 = 1;
        }
        if ((box->z2 < intZPos) || (intZPos < box->z1)) {
            var_a0 = 1;
        }
        if (var_a0 != 0) {
            var_v1 = get_level_segment_index_from_position(intXPos, intYPos, intZPos);
            if (var_v1 != -1) {
                obj->segment.unk2C.half.lower = var_v1;
            }
        }
    }
    return 0;
}

void func_80011960(Object *obj, Vertex *verts, u32 numVertices, Triangle *triangles, u32 numTriangles, TextureHeader *tex, u32 flags, u32 texOffset, f32 arg8) {
    s32 hasTexture = FALSE;
    func_80069484(&gObjectCurrDisplayList, &gObjectCurrMatrix, &obj->segment.trans, arg8, 0.0f);
    gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
    if (tex != NULL) {
        hasTexture = TRUE;
    }
    load_and_set_texture(&gObjectCurrDisplayList, (TextureHeader* ) tex, flags, texOffset);
    gSPVertexDKR(gObjectCurrDisplayList++, OS_K0_TO_PHYSICAL(verts), numVertices, 0);
    gSPPolygon(gObjectCurrDisplayList++, OS_K0_TO_PHYSICAL(triangles), numTriangles, hasTexture);
    func_80069A40(&gObjectCurrDisplayList);
}


#ifdef NON_EQUIVALENT
//f32 D_800E5550 = 0.01f;
void func_80011AD0(Object *this) {
    f32 tmp_f0;
    s32 offset;
    switch (this->behaviorId) {
        case 47:
            //L80011B10
            if (this->unk7C.word >= 0) {
                func_80011960(this, this->unk64->obj80011AD0.unk20, 4, this->unk64,
                                2, this->unk64->obj80011AD0.unk24, 11, 0, 1.0f);
            }
            break;

        case 61:
            //L80011B58
            offset = (this->unk64->obj80011AD0.unkFC * 6);
            offset *= 5;
            offset *= 2;
            offset += 128;
            func_80011960(this, offset, 6, this->unk64, 8, this->unk64->obj80011AD0.unkF8, 10, 0, 1.0f);
            break;

        case 3: //L80011BB4
            tmp_f0 = this->segment.unk3C_a.level_entry->unk80011AD0.unkD;
            offset = (this->unk64->obj80011AD0.unkFC * 6);
            offset *= 5;
            offset *= 2;
            offset += 128;
            func_80011960(this, offset, 6, this->unk64, 8, this->unk64->obj80011AD0.unkF8, 26, 0, tmp_f0 * 0.01f);
            break;

        case 89: //L80011C38
            if ((this->unk78 != 0) && (this->unk64->obj80011AD0.unk70 > 0 || this->unk64->obj80011AD0.unk74 > 0.0f)) {
                func_800135B8(this);
            }
            break;
    } //L80011C88
}
#else
GLOBAL_ASM("asm/non_matchings/objects/func_80011AD0.s")
#endif

/**
 * Render an object as a billboard.
 * A few tweaks are made depending on the behaviour ID of the object.
 * A few exceptions will not call to render a billboarded sprite.
 */
void render_3d_billboard(Object *obj) {
    s32 intensity;
    s32 flags;
    s32 alpha;
    s32 hasPrimCol;
    s32 hasEnvCol;
    ObjectTransformExt sp60;
    Object *var_a0;
    unk80068514_arg4* sp58;
#ifdef PUPPYPRINT_DEBUG
    u32 first = osGetCount();
    u32 first3 = 0;
#endif

    intensity = 255;
    hasPrimCol = FALSE;
    hasEnvCol = FALSE;
    flags = obj->segment.trans.unk6 | 0x100 | 0x8;
    if (obj->unk54 != NULL) {
        hasPrimCol = TRUE;
        hasEnvCol = TRUE;
        intensity = obj->unk54->unk0 * 255.0f;
    }

    if (obj->behaviorId == BHV_BOMB_EXPLOSION) {
        //!@bug Never true, because the type is u8.
        if (obj->segment.unk38.byte.unk39 > 255) {
            obj->segment.unk38.byte.unk39 = obj->unk7C.word & 0xFF;
        } else {
            obj->segment.unk38.byte.unk39 = (obj->segment.unk38.byte.unk39 * (obj->unk7C.word & 0xFF)) >> 8;
        }
    }
    
    alpha = obj->segment.unk38.byte.unk39;
    if (alpha > 255) {
        alpha = 255;
    }

    // If the behavior is a wizpig ghost, then halve it's transparency.
    if (obj->behaviorId == BHV_WIZPIG_GHOSTS) {
        alpha >>= 1;
    }
    
    if (alpha < 255) {
        flags |= RENDER_SEMI_TRANSPARENT;
        hasPrimCol = TRUE;
    }
    if ((obj->behaviorId == 5) && (obj->segment.trans.scale == 6.0f)) {
        gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, (intensity * 3) >> 2, intensity, intensity >> 1, alpha);
        hasPrimCol = TRUE;
    } else if (obj->behaviorId == BHV_WIZPIG_GHOSTS) {  // If the behavior is a wizpig ghost
        gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 150, 230, 255, alpha);
        hasPrimCol = TRUE;
    } else if (hasPrimCol || alpha < 255) {
        gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, intensity, intensity, intensity, alpha);
    } else {
        gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    }
    if (hasEnvCol) {
        gDPSetEnvColor(gObjectCurrDisplayList++, obj->unk54->unk4, obj->unk54->unk5, obj->unk54->unk6, obj->unk54->unk7);
    } else if (obj->behaviorId == BHV_LAVA_SPURT) {
        hasEnvCol = TRUE;
        gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 0, 255);
    } else {
        gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
    }
    sp58 = (unk80068514_arg4 *) obj->unk68[obj->segment.unk38.byte.unk3A];
    var_a0 = NULL;
    if (obj->behaviorId == BHV_FIREBALL_OCTOWEAPON_2) {
        var_a0 = (Object *) obj->trans78;
        if (obj->unk7C.word > 0) {
            var_a0 = obj;
        }
    }
    
    // 5 = OilSlick, SmokeCloud, Bomb, BubbleWeapon
    if(var_a0 != NULL || !(obj->behaviorId != BHV_WEAPON || obj->unk64->weapon.weaponID != WEAOON_BUBBLE_TRAP)) {
        sp60.trans.z_rotation = 0;
        sp60.trans.x_rotation = 0;
        sp60.trans.y_rotation = 0;
        sp60.trans.scale = obj->segment.trans.scale;
        sp60.trans.x_position = 0.0f;
        sp60.trans.z_position = 0.0f;
        sp60.trans.y_position = 12.0f;
        sp60.unk18 = obj->segment.animFrame;
        sp60.unk1A = 32;
        if (var_a0 == NULL) {
            var_a0 = (Object *) obj->unk64->weapon.target;
            if (var_a0 == NULL) {
                var_a0 = obj;
            }
        }
        func_800138A8(var_a0, sp58, &sp60, 0x106);
    } else {
#ifdef PUPPYPRINT_DEBUG
    first3 = osGetCount();
#endif
        render_sprite_billboard(&gObjectCurrDisplayList, &gObjectCurrMatrix, (Vertex **) &gObjectCurrVertexList, obj, sp58, flags);
#ifdef PUPPYPRINT_DEBUG
    first3 = osGetCount() - first3;
#endif
    }
    if (hasPrimCol) {
        gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    }
    if (hasEnvCol) {
        gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
    }
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.timers[PP_BILLBOARD], osGetCount() - first);
    profiler_offset(gPuppyTimers.timers[PP_BILLBOARD], first3);
#endif
}


GLOBAL_ASM("asm/non_matchings/objects/render_3d_model.s")

void func_80012C30(void) {
    D_8011ADA4 = 0;
}

void func_80012C3C(Gfx **dlist) {
    s32 i;
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
        gSPBranchList(D_8011AD78[D_8011ADA4] - 1, *dlist);
        D_8011ADA4++;
    }
}

void func_80012D5C(Gfx **dlist, MatrixS **mtx, Vertex **verts, Object *object) {
    f32 scale;
    if (object->segment.trans.unk6 & 0x5000)
        return;
    func_800B76B8(2, object->unk4A);
    gObjectCurrDisplayList = *dlist;
    gObjectCurrMatrix = *mtx;
    gObjectCurrVertexList = *verts;
    scale = object->segment.trans.scale;
    render_object(object);
    object->segment.trans.scale = scale;
    *dlist = gObjectCurrDisplayList;
    *mtx = gObjectCurrMatrix;
    *verts = gObjectCurrVertexList;
    func_800B76B8(2, -1);
}

void func_80012E28(Object *this) {
    UNUSED s32 unused1;
    Object_Racer *sp_20;
    f32 tmp_f2;
    f32 sp_1c;
    f32 tmp_f0;
    f32 temp;

    if (this->behaviorId == BHV_RACER) {

        sp_20 = &this->unk64->racer;
        this->segment.trans.y_rotation += sp_20->y_rotation_offset;
        this->segment.trans.x_rotation += sp_20->x_rotation_offset;
        this->segment.trans.z_rotation += sp_20->z_rotation_offset;
        sp_1c = 0.0f;
        if (sp_20->unk1D7 < 5) {

            sp_1c = coss_f(sp_20->z_rotation_offset);
            tmp_f2 = sp_1c;
            tmp_f0 = coss_f(sp_20->x_rotation_offset - sp_20->unk166) * tmp_f2;

            tmp_f0 = (tmp_f0 < 0.0f) ? 0.0f : tmp_f0 * tmp_f0;

            temp = (1.0f - tmp_f0) * 24.0f + sp_20->unkD0;
            if(0){}
            sp_1c = temp;
        }
        this->segment.trans.y_position = this->segment.trans.y_position + sp_1c;
        D_8011ADD0 = sp_1c;
    }
}

void func_80012F30(Object *obj) {
    if (obj->behaviorId == BHV_RACER) {
        Object_Racer *racer = &obj->unk64->racer;
        obj->segment.trans.y_rotation -= racer->y_rotation_offset;
        obj->segment.trans.x_rotation -= racer->x_rotation_offset;
        obj->segment.trans.z_rotation -= racer->z_rotation_offset;
        obj->segment.trans.y_position -= D_8011ADD0;
    }
}

GLOBAL_ASM("asm/non_matchings/objects/func_80012F94.s")

void render_object(Object *this) {
    func_80012F94(this);
    if (this->segment.trans.unk6 & 0x8000) {
        func_800B3740(this, &gObjectCurrDisplayList, &gObjectCurrMatrix, &gObjectCurrVertexList, 0x8000);
    } else {
        if (this->segment.header->modelType == OBJECT_MODEL_TYPE_3D_MODEL)
            render_3d_model(this);
        else if (this->segment.header->modelType == OBJECT_MODEL_TYPE_SPRITE_BILLBOARD)
            render_3d_billboard(this);
        else if (this->segment.header->modelType == OBJECT_MODEL_TYPE_UNKNOWN4)
            func_80011AD0(this);
    }
    func_80013548(this);
}

void func_80013548(Object *obj) {
    if (!(obj->segment.trans.unk6 & 0x8000) && obj->segment.header->behaviorId == BHV_RACER) {
        obj->segment.trans.x_position -= obj->unk64->racer.carBobX;
        obj->segment.trans.y_position -= obj->unk64->racer.carBobY;
        obj->segment.trans.z_position -= obj->unk64->racer.carBobZ;
    }
}

GLOBAL_ASM("asm/non_matchings/objects/func_800135B8.s")
GLOBAL_ASM("asm/non_matchings/objects/func_800138A8.s")

/**
 * Get the racer object data, and fetch set visual shield properties based on that racer.
 * Afterwards, render the graphics with opacity scaling with the fadetimer.
 */
void render_racer_shield(Gfx **dList, MatrixS **mtx, Vertex **vtxList, Object *obj) {
    struct Object_Racer* racer;
    Object_68 *gfxData;
    ObjectModel *mdl;
    struct RacerShieldGfx* shield;
    s32 shieldType;
    s32 var_a1;
    s32 var_a2;
    f32 scale;
    f32 shear;

    racer = (Object_Racer *) obj->unk64;
    if (racer->shieldTimer > 0 && D_800DC75C != NULL) {
        gObjectCurrDisplayList = *dList;
        gObjectCurrMatrix = *mtx;
        gObjectCurrVertexList = *vtxList;
        var_a2 = racer->unk2;
        if (var_a2 > 10) {
            var_a2 = 0;
        }
        var_a1 = racer->unk1D6;
        if (var_a1 > 2) {
            var_a1 = 0;
        }
        shield = ((struct RacerShieldGfx *) get_misc_asset(MISC_ASSET_SHIELD_DATA));
        var_a1 =  (var_a1 * 10) + var_a2;
        shield = shield + var_a1;
        D_800DC75C->segment.trans.x_position = shield->x_position;
        D_800DC75C->segment.trans.y_position = shield->y_position;
        D_800DC75C->segment.trans.z_position = shield->z_position;
        D_800DC75C->segment.trans.y_position += shield->y_offset * sins_f(D_8011B010[var_a2] * 0x200);
        shear = (coss_f(D_8011B010[var_a2] * 0x400) * 0.05f) + 0.95f;
        D_800DC75C->segment.trans.scale = shield->scale * shear;
        shear = shear * shield->turnSpeed;
        D_800DC75C->segment.trans.y_rotation = D_8011B010[var_a2] * 0x800;
        D_800DC75C->segment.trans.x_rotation = 0x800;
        D_800DC75C->segment.trans.z_rotation = 0;
        shieldType = racer->shieldType;
        if (shieldType != SHIELD_NONE) {
            shieldType--;
        }
        if (shieldType > SHIELD_LEVEL3 - 1) {
            shieldType = SHIELD_LEVEL3 - 1;
        }
        scale = ((f32) shieldType * 0.1f) + 1.0f;
        D_800DC75C->segment.trans.scale *= scale;
        shear *= scale;
        gfxData = D_800DC75C->unk68[shieldType];
        mdl = gfxData->objModel;
        D_800DC75C->unk44 = (Vertex *) gfxData->unk4[gfxData->unk1F];
        gDPSetEnvColor(gObjectCurrDisplayList++, 255, 255, 255, 0);
        if (racer->shieldTimer < 64) {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, racer->shieldTimer * 4);
        } else {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
        func_80068FA8(&gObjectCurrDisplayList, &gObjectCurrMatrix, D_800DC75C, obj, shear);
        func_800143A8(mdl, D_800DC75C, 0, 4, 0);
        gDkrInsertMatrix(gObjectCurrDisplayList++, 0, G_MTX_DKR_INDEX_0);
        if (racer->shieldTimer < 64) {
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
        *dList = gObjectCurrDisplayList;
        *mtx = gObjectCurrMatrix;
        *vtxList = gObjectCurrVertexList;
    }
}

/**
 * Get the racer object data, and fetch set visual magnet properties based on that racer.
 * Afterwards, render the graphics with opacity set by the properties.
 */
void render_racer_magnet(Gfx **dList, MatrixS **mtx, Vertex **vtxList, Object *obj) {
    Object_Racer *racer;
    Object_68 *gfxData;
    ObjectModel *mdl;
    f32* magnet;
    s32 var_a0;
    s32 var_t0;
    s32 opacity;
    f32 shear;
    UNUSED s32 pad;

    racer = (Object_Racer *) obj->unk64;
    var_t0 = racer->unk2 * 4;
    if (D_8011B07B[var_t0]) {
        if (D_800DC764 != NULL) {
            gObjectCurrDisplayList = *dList;
            gObjectCurrMatrix = *mtx;
            gObjectCurrVertexList = *vtxList;
            magnet = (f32 *) get_misc_asset(MISC_ASSET_MAGNET_DATA);
            var_a0 = racer->unk1D6;
            if (var_a0 < 0 || var_a0 > 2) {
                var_a0 = 0;
            }
            magnet = &magnet[var_a0 * 5];
            var_t0 = racer->unk2;
            if (var_t0 > 10) {
                var_t0 = 0;
            }
            D_800DC764->segment.trans.x_position = magnet[0];
            D_800DC764->segment.trans.y_position = magnet[1];
            D_800DC764->segment.trans.z_position = magnet[2];
            magnet += 3;
            shear = (coss_f((D_8011B078[(var_t0 * 4) + 1] * 0x400)) * 0.02f) + 0.98f;
            D_800DC764->segment.trans.scale = magnet[0] * shear;
            magnet += 1;
            shear = magnet[0] * shear;
            D_800DC764->segment.trans.y_rotation = D_8011B078[(var_t0 * 4) + 2] * 0x1000;
            D_800DC764->segment.trans.x_rotation = 0;
            D_800DC764->segment.trans.z_rotation = 0;
            gfxData = *D_800DC764->unk68;
            mdl = gfxData->objModel;
            D_800DC764->unk44 = (Vertex *) gfxData->unk4[gfxData->unk1F];
            opacity = (((D_8011B078[(var_t0 * 4) + 1] * 8) & 0x7F) + 0x80);
            func_8007F594(&gObjectCurrDisplayList, 2, 0xFFFFFF00 | opacity, D_800DC84C[racer->unk184]);
            func_80068FA8(&gObjectCurrDisplayList, &gObjectCurrMatrix, D_800DC764, obj, shear);
            D_800DC720 = TRUE;
            func_800143A8(mdl, D_800DC764, 0, 4, 0);
            D_800DC720 = FALSE;
            gDkrInsertMatrix(gObjectCurrDisplayList++, 0, G_MTX_DKR_INDEX_0);
            gDPSetPrimColor(gObjectCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            reset_render_settings(&gObjectCurrDisplayList);
            *dList = gObjectCurrDisplayList;
            *mtx = gObjectCurrMatrix;
            *vtxList = gObjectCurrVertexList;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/objects/func_80014090.s")

void func_800142B8(void) {
    s32 i = D_8011AE60;
    s32 j;
    Object *currObj;
    Object_68 *curr_68;

    for (; i < objCount; i++) {
        currObj = gObjPtrList[i];
        if ((currObj->segment.trans.unk6 & 0x8000) == 0 && currObj->segment.header->modelType == OBJECT_MODEL_TYPE_3D_MODEL) {
            for (j = 0; j < currObj->segment.header->numberOfModelIds; j++) {
                curr_68 = currObj->unk68[j];
                if (curr_68 != NULL && curr_68->unk20 > 0) {
                    curr_68->unk20 &= 0x03;
                    curr_68->unk20--;
                }
            }
        }
    }
}

GLOBAL_ASM("asm/non_matchings/objects/func_800143A8.s")
GLOBAL_ASM("asm/non_matchings/objects/func_80014814.s")
GLOBAL_ASM("asm/non_matchings/objects/func_80014B50.s")
GLOBAL_ASM("asm/non_matchings/objects/func_80015348.s")
GLOBAL_ASM("asm/non_matchings/objects/func_800155B8.s")
GLOBAL_ASM("asm/non_matchings/objects/func_800159C8.s")
GLOBAL_ASM("asm/non_matchings/objects/func_80016500.s")
GLOBAL_ASM("asm/non_matchings/objects/func_80016748.s")

void func_80016BC4(unk8000FD34 *arg0) {
    s32 var_s0;
    s32 var_s1;
    s32 *temp_v0;
    s8 var_v1;

    arg0->unk5C->unk104 = 0;
    func_8001709C();
    func_8001709C(arg0);
    var_s1 = 0;
    var_v1 = arg0->unk40->unk55;
    var_s0 = 0;
    if (var_v1 > 0) {
        do {
            temp_v0 = (s32 *) *(arg0->unk68 + var_s0);
            if (temp_v0 != NULL) {
                func_8006017C(*temp_v0);
                var_v1 = arg0->unk40->unk55;
            }
            var_s1 += 1;
            var_s0 += 1;
        } while (var_s1 < var_v1);
    }
}

GLOBAL_ASM("asm/non_matchings/objects/func_80016C68.s")
GLOBAL_ASM("asm/non_matchings/objects/func_80016DE8.s")

void func_8001709C(Object *obj) {
    ObjectTransform sp78;
    s32 i;
    f32 inverseScale;
    Matrix *sp6C;
    Matrix sp2C;
    Object_5C *obj5C;
    
    obj5C = obj->unk5C;
    obj5C->unk104 = (obj5C->unk104 + 1) & 1; 
    sp6C = (Matrix *) &obj5C->_matrices[obj5C->unk104 << 1];
    sp78.y_rotation = -obj->segment.trans.y_rotation;
    sp78.x_rotation = -obj->segment.trans.x_rotation;
    sp78.z_rotation = -obj->segment.trans.z_rotation;
    sp78.scale = 1.0f;
    sp78.x_position = -obj->segment.trans.x_position;
    sp78.y_position = -obj->segment.trans.y_position;
    sp78.z_position = -obj->segment.trans.z_position;
    object_transform_to_matrix_2((float (*)[4]) sp6C, (ObjectTransform* ) &sp78);
    inverseScale = 1.0f / obj->segment.trans.scale;
    i = 0;
    while (i < 16) {
        ((f32 *) sp2C)[i] = 0.0f;
        i++;
    }
    sp2C[0][0] = inverseScale;
    sp2C[1][1] = inverseScale;
    sp2C[2][2] = inverseScale;
    sp2C[3][3] = 1.0f;
    f32_matrix_mult(sp6C, &sp2C, sp6C);
    sp78.y_rotation = obj->segment.trans.y_rotation;
    sp78.x_rotation = obj->segment.trans.x_rotation;
    sp78.z_rotation = obj->segment.trans.z_rotation;
    sp78.scale = 1.0f / inverseScale;
    sp78.x_position = obj->segment.trans.x_position;
    sp78.y_position = obj->segment.trans.y_position;
    sp78.z_position = obj->segment.trans.z_position;
    object_transform_to_matrix(obj5C->_matrices[(obj5C->unk104 + 2) << 1], (ObjectTransform* ) &sp78);
    obj5C->unk100 = NULL;
}

GLOBAL_ASM("asm/non_matchings/objects/func_80017248.s")

unk800179D0 *func_8001790C(u32 *arg0, u32 *arg1) {
    unk800179D0 *entry;
    s16 i;

    for(i = 0; i < 16; i++) {
        entry = &D_8011AFF4[i];
        if (entry->unk0 != 0 && entry->unk04 == arg0 && entry->unk08 == arg1) {
            entry->unk0 = 0;
            return entry;
        }
    }
    return NULL;
}

unk800179D0 *func_80017978(s32 arg0, s32 arg1) {
    unk800179D0 *entry;
    s16 i;

    for(i = 0; i < 16; i++) {
        entry = &D_8011AFF4[i];
        if (entry->unk0 == 0) {
            entry->unk04 = (u32 *) arg0;
            entry->unk08 = (u32 *) arg1;
            entry->unk0 = 2;
            return entry;
        }
    }
    return NULL;
}

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

GLOBAL_ASM("asm/non_matchings/objects/func_80017A18.s")

void func_80017E74(s32 arg0) {
    D_8011AED8 = arg0;
    D_8011ADAC = 0;
}

s16 func_80017E88(void) {
    return D_8011AED8;
}

GLOBAL_ASM("asm/non_matchings/objects/func_80017E98.s")
GLOBAL_ASM("asm/non_matchings/objects/func_800185E4.s")

/**
 * Search and return Taj's overworld object.
 * Used for drawing his minimap position.
*/
Object *find_taj_object(void) {
    s32 i;
    Object *current_obj;
    for (i = D_8011AE60; i < objCount; i++) {
        current_obj = gObjPtrList[i];
        if (!(current_obj->segment.trans.unk6 & 0x8000) && (current_obj->behaviorId == 62)) {
            return current_obj;
        }
    }
    return NULL;
}

GLOBAL_ASM("asm/non_matchings/objects/func_80018CE0.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001955C.s")
GLOBAL_ASM("asm/non_matchings/objects/func_80019808.s")

s8 func_8001A7D8(unk8001A7D8_arg0 *arg0) {
    Object_Racer *racer;

    racer = (Object_Racer *) gRacersByPosition[0]->unk64;
    if (racer->playerIndex == PLAYER_COMPUTER) {
        return 0;
    }
    D_8011ADC4 = 0;
    if (!(arg0->unk4[arg0->unk49] & 2)) {
        if (D_8011AEF5 == 0) {
            D_8011ADC4 = 1;
            arg0->unk4[arg0->unk49] |= 2;
        }
    } else if (gIsSilverCoinRace && racer->silverCoinCount >= 8 && D_8011AEF5 == 0) {
        D_8011ADC4 = 1;
            arg0->unk4[arg0->unk49] |= 4;
    }
    return D_8011ADC4;
}

void func_8001A8D4(s32 arg0) {
    D_8011AD4E = 0x12C;
    D_8011AD50 = 0;
    D_8011AD52 = arg0;
}

GLOBAL_ASM("asm/non_matchings/objects/func_8001A8F4.s")

s16 func_8001AE44() {
    return D_8011AD4E;
}

s32 func_8001AE54() {
    return D_8011ADC8;
}

GLOBAL_ASM("asm/non_matchings/objects/func_8001AE64.s")

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

Object *func_8001B2E0(void) {
    return D_8011AD34;
}

/**
Pretty sure this determines whether or not you're eligible to race TT ghost in track select
when TT is on. It looks like it checks some ghost data makes sure you've got a ghost for that level
with the default vehicle,
Returns 0 if TT ghost was loaded successfully.
*/
s32 func_8001B2F0(s32 mapId) {
    TTGhostTable *ghostTable;
    TTGhostTable *prevGhostTable;
    s32 ret;
    TTGhostTable *nextGhostTable;

    gMapDefaultVehicle = get_map_default_vehicle(mapId);
    ghostTable = (TTGhostTable *) load_asset_section_from_rom(ASSET_TTGHOSTS_TABLE);

    nextGhostTable = ghostTable;
    do {
        prevGhostTable = nextGhostTable;
        if ((prevGhostTable->mapId == mapId) && (prevGhostTable->defaultVehicleId == gMapDefaultVehicle)) {
            break;
        }
        nextGhostTable++;
    } while (prevGhostTable->mapId != 0xFF);

    ret = 1;

    if (prevGhostTable->mapId != 0xFF) {
        ret = load_tt_ghost(nextGhostTable->ghostOffset, nextGhostTable[1].ghostOffset - nextGhostTable->ghostOffset, &gTTGhostTimeToBeat);
    }

    free_from_memory_pool(ghostTable);
    return ret;
}

s32 func_8001B3AC(s32 arg0) {
    return arg0 == D_800DC718;
}

GLOBAL_ASM("asm/non_matchings/objects/func_8001B3C4.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001B4FC.s")

Object *func_8001B640(void) {
    return (Object *) D_800DC718;
}

s32 func_8001B650(void) {
    return D_800DC738 == 0;
}

s32 func_8001B668(s32 arg0) {
    s16 sp2E;
    s16 sp2C;
    s32 temp_v0;
    s32 mapId;

    mapId = func_800599A8();
    if ((func_8006BD88() != mapId) || (D_800DC728 != D_8011AE82)) {
        temp_v0 = func_800599B8(arg0, func_8006BD88(), D_8011AE82, &sp2E, &sp2C);
        if (temp_v0 == 0) {
            D_800DC728 = D_8011AE82;
            D_800DC72C = sp2E;
            D_800DC724 = sp2C;
        }
        return temp_v0;
    }
    return func_800599B8(arg0, func_8006BD88(), D_8011AE82, NULL, NULL);
}

s32 func_8001B738(s32 controllerIndex) {
    return func_80059B7C(controllerIndex, func_800599A8(), D_800DC728, D_800DC72C, D_800DC724);
}

u8 has_ghost_to_save() {
    return gHasGhostToSave;
}

void func_8001B790(void) {
    D_8011D5AC = -1;
    gHasGhostToSave = 0;
}

Object *func_8001B7A8(Object *racer, s32 position, f32 *distance) {
    UNUSED s32 temp;
    Object *tempRacer;
    position = (racer->obj.obj8001B7A8.unk112 - position) - 1;
    if (position < 0 || position >= gNumRacers) {
        return NULL;
    }
    tempRacer = gRacersByPosition[position];
    if (tempRacer == NULL) {
        return NULL;
    }
    *distance = func_8001B834((Object_Racer *) racer, (Object_Racer *) tempRacer->unk64);
    return tempRacer;
}

f32 func_8001B834(Object_Racer *racer1, Object_Racer *racer2) {
    Object_Racer *temp_racer;
    f32 var_f2;
    s32 r1_ccp;
    UNUSED s32 temp_lo;
    s32 var_v1;
    s32 checkpointID;

    if (gNumberOfCheckpoints <= 0) {
        return 0.0f;
    }
    var_f2 = 0.0f;
    var_v1 = FALSE;
    if (racer2->courseCheckpoint < racer1->courseCheckpoint) {
        temp_racer = racer1;
        racer1 = racer2;
        racer2 = temp_racer;
        var_v1 = TRUE;
    }
    checkpointID = racer1->checkpoint;
    for (r1_ccp = racer1->courseCheckpoint; r1_ccp < racer2->courseCheckpoint; r1_ccp++) {
        var_f2 += gTrackCheckpoints[checkpointID++].distance;
        if (checkpointID == gNumberOfCheckpoints) {
            checkpointID = 0;
        }
    }
    checkpointID = racer1->checkpoint - 1;
    if (checkpointID < 0) {
        checkpointID = gNumberOfCheckpoints - 1;
    }
    var_f2 += (gTrackCheckpoints[checkpointID].distance * racer1->checkpoint_distance);
    checkpointID = racer2->checkpoint - 1;
    if (checkpointID < 0) {
        checkpointID = gNumberOfCheckpoints - 1;
    }
    var_f2 -= (gTrackCheckpoints[checkpointID].distance * racer2->checkpoint_distance);
    if (var_v1) {
        var_f2 = -var_f2;
    }
    return var_f2;
}

UNUSED f32 func_8001B974(Object_Racer* racer) {
    f32 distLeft;
    s32 checkpointID;

    if (gNumberOfCheckpoints <= 0) {
        return 0.0f;
    }
    distLeft = 0.0f;
    for (checkpointID = racer->checkpoint; checkpointID < gNumberOfCheckpoints; checkpointID++) {
        distLeft += gTrackCheckpoints[checkpointID].distance;
    }
    checkpointID = racer->checkpoint - 1;
    if (checkpointID < 0) {
        checkpointID = gNumberOfCheckpoints - 1;
    }
    distLeft += (gTrackCheckpoints[checkpointID].distance * racer->checkpoint_distance);
    return distLeft;
}

/**
 * Returns a pointer to a specific checkpoint.
*/
CheckpointNode *get_checkpoint_node(s32 checkpointID) {
    return &gTrackCheckpoints[checkpointID];
}

/**
 * Takes the position along the checkpoint path, and finds the next applicable node.
 * If an alternative path is available, use that node instead.
*/
CheckpointNode *find_next_checkpoint_node(s32 splinePos, s32 arg1) {
    CheckpointNode *checkpointNode = &gTrackCheckpoints[splinePos];
    if (arg1 != 0 && checkpointNode->altRouteID != -1) {
        checkpointNode = &gTrackCheckpoints[checkpointNode->altRouteID];
    }
    return checkpointNode;
}

/**
 * Returns the number of active checkpoints in the current level.
*/
s32 get_checkpoint_count(void) {
    return gNumberOfCheckpoints;
}

/**
 * Returns the group of racer objects.
*/
Object **get_racer_objects(s32 *numRacers) {
    *numRacers = gNumRacers;
    return *gRacers;
}

/**
 * Returns the group of racer objects, ordered by player index.
*/
Object **get_racer_objects_by_port(s32 *numRacers) {
    *numRacers = gNumRacers;
    return gRacersByPort;
}

/**
 * Returns the group of racer objects, ordered by current race position.
*/
Object **get_racer_objects_by_position(s32 *numRacers) {
    *numRacers = gNumRacers;
    return gRacersByPosition;
}

Object *get_racer_object(s32 index) {
    if (gNumRacers == 0) {
        return NULL;
    }
    if (index < 0 || index >= gNumRacers) {
        return NULL;
    }
    return (*gRacers)[index];
}

Object *get_racer_object_by_port(s32 index) {
    if (gNumRacers == 0) {
        return NULL;
    }
    if (index < 0 || index >= gNumRacers) {
        return NULL;
    }
    return gRacersByPort[index];
}

/**
 * Unused function that would've iterated through all active checkpoints to render their visual nodes.
 * The function it calls is completely stubbed out.
*/
UNUSED void debug_render_checkpoints(Gfx **dlist, MatrixS **mtx, Vertex **vtx) {
    s32 i;

    load_and_set_texture_no_offset(dlist, NULL, RENDER_Z_COMPARE);
    if (gNumberOfCheckpoints > 3) {
        for (i = 0; i < gNumberOfCheckpoints; i++) {
            // Ground path
            debug_render_checkpoint_node(i, 0, dlist, mtx, vtx);
        }
        for (i = 0; i < gNumberOfCheckpoints; i++){
            // Air path
            debug_render_checkpoint_node(i, 1, dlist, mtx, vtx);
        }
    }
}

/**
 * Would've rendered an individual checkpoint node. On https://noclip.website, with dev objects enabled, you can see a visual representation of
 * what these checkpoints would've looked like ingame.
*/
UNUSED void debug_render_checkpoint_node(UNUSED s32 checkpointID, UNUSED s32 pathID, UNUSED Gfx **dList, UNUSED MatrixS **mtx, UNUSED Vertex **vtx) {
}

GLOBAL_ASM("asm/non_matchings/objects/func_8001BC54.s")

u32 func_8001BD94(s32 arg0) {
    if (arg0 < 0 || arg0 >= D_8011AEE0) {
        return 0;
    }
    return D_8011AEDC[0][arg0];
}

GLOBAL_ASM("asm/non_matchings/objects/func_8001BDD4.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001BF20.s")

s16 func_8001C418(f32 yPos) {
    s16 i = 0;
    s16 out = 0;
    for(; i < 4; i++) {
        if ((D_8011AF18[i] != -20000.0f) && (D_8011AF18[i] < yPos)) {
            out = i;
        }
    }
    return out;
}

s32 func_8001C48C(Object *obj) {
    s32 i;
    for(i = 0; i < 128; i++) {
        if ((*D_8011AF04)[i] == 0) {
            (*D_8011AF04)[i] = obj;
            return i;
        }
    }
    return -1;
}

s32 func_8001C524(f32 xDiff, f32 yDiff, f32 zDiff, s32 someFlag) {
    UNUSED f32 pad[6];
    s32 sp64;
    f32 x;
    f32 len;
    f32 z;
    f32 y;
    f32 dist;
    s32 var_a0;
    s32 numSteps;
    s32 result;
    ObjectSegment *segment;
    LevelObjectEntry_TTDoor *levelObj;

    if (someFlag) {
        sp64 = func_8001C418(yDiff);
    }
    dist = D_800E5644;
    result = 0xFF;
    for (numSteps = 0; numSteps != 128; numSteps++) {
        segment = (ObjectSegment*) (*D_8011AF04)[numSteps];
        if (segment) {
            levelObj = &((segment->unk3C_a.level_entry)->ttDoor);
            var_a0 = 1;
            if (someFlag && (sp64 != levelObj->unkE)) {
                var_a0 = 0;
            }
            if ((someFlag == 2) && (levelObj->unk8 != 3)) {
                var_a0 = 0;
            }
            if (var_a0) {
                x = segment->trans.x_position - xDiff;
                y = segment->trans.y_position - yDiff;
                z = segment->trans.z_position - zDiff;
                len = ((x * x) + (y * y) + (z * z));
                if (len < dist * dist) {
                    dist = sqrtf(len);
                    result = numSteps;
                }
            }
        }
    }
    return result;
}

GLOBAL_ASM("asm/non_matchings/objects/func_8001C6C4.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001CC48.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001CD28.s")

void func_8001D1AC(void) {
    D_8011AF10[0] = 1;
}

void func_8001D1BC(s32 arg0) {
    if (arg0 != D_8011AF08[0]) {
        D_8011AF08[1] = D_8011AF08[0];
        D_8011AF08[0] = arg0;
    }
}

Object *func_8001D1E4(s32 *arg0) {
    *arg0 = D_8011AF08[1];
    return D_8011AF04[0][D_8011AF08[1]];
}

Object *func_8001D214(s32 arg0) {
    if (arg0 >= 0 && arg0 < 0x80) {
        return D_8011AF04[0][arg0];
    }
    return 0;
}

UNUSED void func_8001D23C(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {
}

void func_8001D258(f32 arg0, f32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    func_8001D4B4(&D_8011AF30, arg0, arg1, arg2, arg3, arg4);
}

GLOBAL_ASM("asm/non_matchings/objects/func_8001D2A0.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001D4B4.s")

void set_and_normalize_D_8011AFE8(f32 x, f32 y, f32 z) {
    f32 vecLength = sqrtf((x * x) + (y * y) + (z * z));
    f32 normalizedLength;
    if (vecLength != 0.0f) {
        normalizedLength = -8192.0f / vecLength;
        x *= normalizedLength;
        y *= normalizedLength;
        z *= normalizedLength;
    }
    D_8011AFE8.x = x;
    D_8011AFE8.y = y;
    D_8011AFE8.z = z;
}

void calc_dyn_light_and_env_map_for_object(ObjectModel *model, Object *object, s32 arg2, f32 arg3) {
    s16 environmentMappingEnabled;
    s32 dynamicLightingEnabled;
    s16 i;
#ifdef PUPPYPRINT_DEBUG
    u32 first =  osGetCount();
#endif

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
        if (object->segment.header->unk71 != 0) {
            // Dynamic lighting for some objects? (Intro diddy, Taj, T.T., Bosses)
            calc_dynamic_lighting_for_object_1(object, model, arg2, object, arg3, 1.0f);
        } else {
            // Dynamic lighting for other objects? (Racers, Rare logo, Wizpig face, etc.)
            calc_dynamic_lighting_for_object_2(object, model, arg2, arg3);
        }
    }
#ifdef PUPPYPRINT_DEBUG
        profiler_add(gPuppyTimers.timers[PP_LIGHT], osGetCount() - first);
        first = osGetCount();
#endif
    if (environmentMappingEnabled) {
        // Calculates environment mapping for the object
        calc_env_mapping_for_object(model, object->segment.trans.z_rotation, object->segment.trans.x_rotation, object->segment.trans.y_rotation);
#ifdef PUPPYPRINT_DEBUG
        profiler_add(gPuppyTimers.timers[PP_ENVMAP], osGetCount() - first);
#endif
    }
}

GLOBAL_ASM("asm/non_matchings/objects/calc_dynamic_lighting_for_object_1.s")
GLOBAL_ASM("asm/non_matchings/objects/calc_env_mapping_for_object.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001E13C.s")

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
        && !(current_obj->segment.trans.unk6 & 0x8000)
        && current_obj->behaviorId == BHV_RAMP_SWITCH
        && current_obj->action == arg0) {
            *arg1 = current_obj->segment.trans.x_position;
            *arg2 = current_obj->segment.trans.y_position;
            *arg3 = current_obj->segment.trans.z_position;
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
        if (get_render_context() == DRAW_MENU) {
            func_8006F42C();
        }
    }
}

// Unused?
s32 func_8001E4B4(void) {
    return D_8011AE60;
}

GLOBAL_ASM("asm/non_matchings/objects/func_8001E4C4.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001E6EC.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001E89C.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001E93C.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001EE74.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001EFA4.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8001F23C.s")

s8 func_8001F3B8(void) {
    return D_8011ADD4;
}

void func_8001F3C8(s32 arg0) {
    if (arg0 != D_8011ADD4) {
        D_8011AE78 = 0;
    }
    D_8011ADD4 = arg0;
}

s32 func_8001F3EC(s32 arg0){
    s32 i;
    s32 count;
    if (D_8011AE78 == 0) {
        return -1;
    }

    count = 0;
    for (i = 0; i < D_8011AE78; i++) {
        if (D_8011AE74[i]->unk7C.word == arg0){
            count++;
        }
    }

    return count;
}

void func_8001F450(void) {
    D_8011AD53 = 1;
}

GLOBAL_ASM("asm/non_matchings/objects/func_8001F460.s")

s32 func_800210CC(s8 arg0) {
    if (arg0 >= D_8011AD3D) {
        D_8011AD3D = arg0;
        return 1;
    }
    return 0;
}

GLOBAL_ASM("asm/non_matchings/objects/func_80021104.s")
GLOBAL_ASM("asm/non_matchings/objects/func_8002125C.s")

void func_80021400(s32 arg0) {
    s32 i;
    arg0 &= 0xFF; //?


    for (i = 0; i < D_8011AE78 && (arg0 != (D_8011AE74[i]->unk7C.word & 0xFF)); i++) {}

    if (i < D_8011AE78) {
        if (D_8011AE74[i]->unk64 != NULL) {
            if (D_8011AE74[i]->unk64->obj80021400_64.obj64->unk2A < 0) {
                D_8011AE74[i]->unk64->obj80021400_64.obj64->unk2A = 1;
            }
        }
    }
}

s8 func_800214C4(void) {
    return D_8011AD22[1 - D_8011AD20[1]];
}

s8 func_800214E4(Object *obj, s32 updateRate) {
    s16 temp_v1;
    s32 i;
    Object_AnimatedObject *animObj;

    animObj = (Object_AnimatedObject *) obj->unk64;
    if (animObj->unk3A != 0) {
        obj->segment.trans.unk6 |= 0x4000;
    }
    if (animObj->unk36 == -1) {
        return animObj->unk3A;
    }
    if (animObj->unk36 >= 0) {
        animObj->unk36 -= updateRate;
    }
    if (animObj->unk36 == -1) {
        animObj->unk36 = -2;
    }
    if (animObj->unk36 <= 0) {
        obj->segment.trans.unk6 |= 0x4000;
        i = 0;
        if (D_8011AE78 > 0) {
            temp_v1 = animObj->unk28;
            if (temp_v1 != (s32) (*D_8011AE74)->unk7C.word) {
loop_11:
                i++;
                if (i < D_8011AE78) {
                    if (temp_v1 != (s32) D_8011AE74[i]->unk7C.word) {
                        goto loop_11;
                    }
                }
            }
        }
        func_8001EFA4(D_8011AE74[i], (Object_Animation *) obj);
        return 1;
    }
    return 0;
}

GLOBAL_ASM("asm/non_matchings/objects/func_80021600.s")

f32 catmull_rom_interpolation(f32 *arg0, s32 arg1, f32 arg2) {
    f32 ret;
    f32 temp3, temp2, temp;
    
    temp =  (-0.5f * arg0[arg1])    + ( 1.5f * arg0[arg1 + 1]) + (-1.5f * arg0[arg1 + 2]) + ( 0.5f * arg0[arg1 + 3]);
    temp2 = ( 1.0f * arg0[arg1])    + (-2.5f * arg0[arg1 + 1]) + ( 2.0f * arg0[arg1 + 2]) + (-0.5f * arg0[arg1 + 3]);
    temp3 = (arg0[arg1 + 2] * 0.5f)+ ( 0.0f * arg0[arg1 + 1]) + (-0.5f * arg0[arg1])     + ( 0.0f * arg0[arg1 + 3]);
    
    ret = (1.0f * arg0[arg1 + 1]);
    ret = (((((temp * arg2) + temp2) * arg2) + temp3) * arg2) + ret;
    
    return ret;
}

/**
 * Interpolates x along a spline and returns the resultant progress along the spline.
*/
f32 cubic_spline_interpolation(f32 *data, s32 index, f32 x, f32 *derivative) {
    f32 ret;
    f32 temp3, temp2, temp;
    
    temp =  (-0.5f * data[index])    + ( 1.5f * data[index + 1]) + (-1.5f * data[index + 2]) + ( 0.5f * data[index + 3]);
    temp2 = ( 1.0f * data[index])    + (-2.5f * data[index + 1]) + ( 2.0f * data[index + 2]) + (-0.5f * data[index + 3]);
    temp3 = (data[index + 2] * 0.5f) + ( 0.0f * data[index + 1]) + (-0.5f * data[index])     + ( 0.0f * data[index + 3]);
    
    ret = (1.0f * data[index + 1]);
    *derivative = (((temp * 3 * x) + (2 * temp2)) * x) + temp3;
    ret = (((((temp * x) + temp2) * x) + temp3) * x) + ret;
    
    return ret;
}

GLOBAL_ASM("asm/non_matchings/objects/func_8002277C.s")

f32 lerp(f32 *arg0, u32 arg1, f32 arg2) {
    f32 result = arg0[arg1 + 1] + ((arg0[arg1 + 2] - arg0[arg1 + 1]) * arg2);
    return result;
}

f32 func_800228B0(f32 *arg0, u32 arg1, f32 arg2, f32 *arg3) {
    f32 new_var2;
    f32 temp_f12;
    f32 new_var;
    f32 temp_f2;
    new_var = arg0[arg1 + 2] - arg0[arg1 + 1];
    temp_f2 = new_var * arg2;
    temp_f12 = arg0[arg1 + 1];
    new_var2 = temp_f12 + temp_f2;
    *arg3 = arg0[arg1 + 2] - arg0[arg1 + 1];
    return new_var2;
}

UNUSED void func_800228DC(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {
}

void func_800228EC(s32 arg0) {
    Object_Racer *object_64;

    D_8011AEF7 = 3;
    object_64 = &get_racer_object(0)->unk64->racer;
    object_64->courseCheckpoint = 0;
    object_64->checkpoint = 0;
    object_64->lap = 0;
    object_64->unk1BA = 0;
    func_80017E74(arg0);
    func_8006F388(10);
}

GLOBAL_ASM("asm/non_matchings/objects/func_80022948.s")

void func_80022CFC(s32 arg0, f32 x, f32 y, f32 z) {
    s32 index;
    unk80022CFC_1 *obj;
    Settings *settings = get_settings();

    for (index = 0; index < objCount; index += 1) {
        obj = ((unk80022CFC_1*) gObjPtrList[index]);
        if (obj->unk48 == 0x4D) {
            if (obj->unk3C != NULL) {
                if (obj->unk3C->unkA > 0) {
                    if ((settings->tajFlags != 0) && (settings->tajFlags & (1 << (obj->unk3C->unkA + 2)))) {
                        obj->unkC = x;
                        obj->unk10 = y + 10.0f;
                        obj->unk14 = z;
                        obj->unk2E = arg0;
                        obj->unk78 = 0;
                        obj->unk39 = 0;
                    }
                }
            }
        }
    }
}

GLOBAL_ASM("asm/non_matchings/objects/func_80022E18.s")
GLOBAL_ASM("asm/non_matchings/objects/func_800230D0.s")

s8 func_8002341C(void) {
    return D_8011AEF6;
}

Object *func_8002342C(f32 x, f32 z) {
    Object *tempObj;
    Object *bestObj;
    f32 diffX;
    f32 diffZ;
    f32 distance;
    f32 bestDist;
    s32 i;

    bestDist = 0.0f;
    i = 0;
    bestObj = NULL;
    if (objCount > 0) {
        do {
            tempObj = gObjPtrList[i];
            if (!(tempObj->segment.trans.unk6 & 0x8000) && tempObj->behaviorId == BHV_UNK_57) {
                diffX = tempObj->segment.trans.x_position - x;
                diffZ = tempObj->segment.trans.z_position - z;
                tempObj = gObjPtrList[i]; // fakematch
                distance = ((diffX * diffX) + (diffZ * diffZ));
                if (bestDist < distance * distance) {
                    bestDist = sqrtf(distance);
                    bestObj = tempObj;
                }
            }
            i += 1;
        } while (i < objCount);
    }
    return bestObj;
}


s32 func_80023568(void) {
    if (D_8011AD3C != 0) {
        return D_8011AD24[1] + 1;
    } else if (get_current_level_race_type() == RACETYPE_BOSS) {
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

GLOBAL_ASM("asm/non_matchings/objects/func_800235DC.s")

void run_object_init_func(Object *obj, void *entry, s32 arg2) {
    obj->behaviorId = obj->segment.header->behaviorId;
    switch (obj->behaviorId) {
        case BHV_RACER:
            obj_init_racer(obj, (LevelObjectEntry_CharacterFlag *) entry);
            break;
        case BHV_SCENERY:
            obj_init_scenery(obj, (LevelObjectEntry_Scenery*) entry);
            break;
        case BHV_FISH:
            obj_init_fish(obj, (LevelObjectEntry_Fish *) entry);
            break;
        case BHV_ANIMATOR:
            obj_init_animator(obj, (LevelObjectEntry_Animator *) entry, arg2);
            break;
        case BHV_SMOKE:
            obj_init_smoke(obj, (LevelObjectEntry_Smoke *) entry);
            break;
        case BHV_UNK_19:
            obj_init_unknown25(obj, (LevelObjectEntry_Unknown25 *) entry);
            break;
        case BHV_BOMB_EXPLOSION:
            obj_init_bombexplosion(obj, (LevelObjectEntry_BombExplosion *) entry);
            break;
        case BHV_EXIT:
            obj_init_exit(obj, (LevelObjectEntry_Exit *) entry);
            break;
        case BHV_AUDIO:
            obj_init_audio(obj, (LevelObjectEntry_Audio *) entry);
            break;
        case BHV_AUDIO_LINE:
        case BHV_AUDIO_LINE_2:
            obj_init_audioline(obj, (LevelObjectEntry_AudioLine *) entry);
            break;
        case BHV_AUDIO_REVERB:
            obj_init_audioreverb(obj, (LevelObjectEntry_AudioReverb *) entry);
            break;
        case BHV_CAMERA_CONTROL:
            obj_init_cameracontrol(obj, (LevelObjectEntry_CameraControl *) entry);
            break;
        case BHV_SETUP_POINT:
            obj_init_setuppoint(obj, (LevelObjectEntry_SetupPoint *) entry);
            break;
        case BHV_DINO_WHALE:
            obj_init_dino_whale(obj, (LevelObjectEntry_Dino_Whale *) entry);
            break;
        case BHV_CHECKPOINT:
            obj_init_checkpoint(obj, (LevelObjectEntry_Checkpoint *) entry, arg2);
            break;
        case BHV_MODECHANGE:
            obj_init_modechange(obj, (LevelObjectEntry_ModeChange *) entry);
            break;
        case BHV_BONUS:
            obj_init_bonus(obj, (LevelObjectEntry_Bonus *) entry);
            break;
        case BHV_DOOR:
            obj_init_door(obj, (LevelObjectEntry_Door *) entry);
            break;
        case BHV_TT_DOOR:
            obj_init_ttdoor(obj, (LevelObjectEntry_TTDoor *) entry);
            break;
        case BHV_FOG_CHANGER:
            obj_init_fogchanger(obj, (LevelObjectEntry_FogChanger *) entry);
            break;
        case BHV_AINODE:
            obj_init_ainode(obj, (LevelObjectEntry_AiNode *) entry);
            break;
        case BHV_WEAPON_BALLOON:
            obj_init_weaponballoon(obj, (LevelObjectEntry_WeaponBalloon *) entry);
            break;
        case BHV_BALLOON_POP:
            obj_init_wballoonpop(obj, (LevelObjectEntry_WBalloonPop *) entry);
            break;
        case BHV_WEAPON:
        case BHV_WEAPON_2:
            obj_init_weapon(obj, (LevelObjectEntry_Weapon *) entry);
            break;
        case BHV_SKY_CONTROL:
            obj_init_skycontrol(obj, (LevelObjectEntry_SkyControl *) entry);
            break;
        case BHV_TORCH_MIST:
            obj_init_torch_mist(obj, (LevelObjectEntry_Torch_Mist *) entry);
            break;
        case BHV_TEXTURE_SCROLL:
            obj_init_texscroll(obj, (LevelObjectEntry_TexScroll *) entry, arg2);
            break;
        case BHV_STOPWATCH_MAN:
            obj_init_stopwatchman(obj, (LevelObjectEntry_StopWatchMan *) entry);
            break;
        case BHV_BANANA:
            obj_init_banana(obj, (LevelObjectEntry_Banana *) entry);
            break;
        case BHV_LIGHT_RGBA:
            obj_init_rgbalight(obj, (LevelObjectEntry_RgbaLight *) entry, arg2);
            break;
        case BHV_BUOY_PIRATE_SHIP:
            obj_init_buoy_pirateship(obj, (LevelObjectEntry_Buoy_PirateShip *) entry, arg2);
            break;
        case BHV_LOG:
            obj_init_log(obj, (LevelObjectEntry_Log *) entry, arg2);
            break;
        case BHV_WEATHER:
            obj_init_weather(obj, (LevelObjectEntry_Weather *) entry);
            break;
        case BHV_BRIDGE_WHALE_RAMP:
            obj_init_bridge_whaleramp(obj, (LevelObjectEntry_Bridge_WhaleRamp *) entry);
            break;
        case BHV_RAMP_SWITCH:
            obj_init_rampswitch(obj, (LevelObjectEntry_RampSwitch *) entry);
            break;
        case BHV_SEA_MONSTER:
            obj_init_seamonster(obj, (LevelObjectEntry_SeaMonster *) entry);
            break;
        case BHV_LENS_FLARE:
            obj_init_lensflare(obj, (LevelObjectEntry_LensFlare *) entry);
            break;
        case BHV_LENS_FLARE_SWITCH:
            obj_init_lensflareswitch(obj, (LevelObjectEntry_LensFlareSwitch *) entry);
            break;
        case BHV_COLLECT_EGG:
            obj_init_collectegg(obj, (LevelObjectEntry_CollectEgg *) entry);
            break;
        case BHV_EGG_CREATOR:
            obj_init_eggcreator(obj, (LevelObjectEntry_EggCreator *) entry);
            break;
        case BHV_CHARACTER_FLAG:
            obj_init_characterflag(obj, (LevelObjectEntry_CharacterFlag *) entry);
            break;
        case BHV_ANIMATION:
            obj_init_animation(obj, (LevelObjectEntry_Animation *) entry);
            break;
        case BHV_INFO_POINT:
            obj_init_infopoint(obj, (LevelObjectEntry_InfoPoint *) entry);
            break;
        case BHV_TRIGGER:
            obj_init_trigger(obj, (LevelObjectEntry_Trigger *) entry);
            break;
        case BHV_ZIPPER_WATER:
        case BHV_ZIPPER_AIR:
            obj_init_airzippers_waterzippers(obj, (LevelObjectEntry_AirZippers_WaterZippers *) entry);
            break;
        case BHV_UNK_3A:
            obj_init_unknown58(obj, (LevelObjectEntry_Unknown58 *) entry);
            break;
        case BHV_WAVE_GENERATOR:
            obj_init_wavegenerator(obj, (LevelObjectEntry_WaveGenerator *) entry, arg2);
            break;
        case BHV_BUTTERFLY:
            obj_init_butterfly(obj, (LevelObjectEntry_Butterfly *) entry);
            break;
        case BHV_PARK_WARDEN:
            obj_init_parkwarden(obj, (LevelObjectEntry_Parkwarden *) entry);
            break;
        case BHV_WORLD_KEY:
            obj_init_worldkey(obj, (LevelObjectEntry_WorldKey *) entry);
            break;
        case BHV_BANANA_SPAWNER:
            obj_init_bananacreator(obj, (LevelObjectEntry_BananaCreator *) entry);
            break;
        case BHV_TREASURE_SUCKER:
            obj_init_treasuresucker(obj, (LevelObjectEntry_TreasureSucker *) entry);
            break;
        case BHV_LAVA_SPURT:
            obj_init_lavaspurt(obj, (LevelObjectEntry_LavaSpurt *) entry);
            break;
        case BHV_POS_ARROW:
            obj_init_posarrow(obj, (LevelObjectEntry_PosArrow *) entry);
            break;
        case BHV_HIT_TESTER:
        case BHV_HIT_TESTER_3:
            obj_init_hittester(obj, (LevelObjectEntry_HitTester *) entry);
            break;
        case BHV_HIT_TESTER_2:
        case BHV_DYNAMIC_LIGHT_OBJECT_2:
        case BHV_HIT_TESTER_4:
            obj_init_dynamic_lighting_object(obj, (LevelObjectEntry_DynamicLightingObject *) entry);
            break;
        case BHV_SNOWBALL:
        case BHV_SNOWBALL_3:
            obj_init_unknown96(obj, (LevelObjectEntry_Unknown96 *) entry);
            break;
        case BHV_SNOWBALL_2:
        case BHV_SNOWBALL_4:
            obj_init_snowball(obj, (LevelObjectEntry_Snowball *) entry);
            break;
        case BHV_MIDI_FADE:
            obj_init_midifade(obj, (LevelObjectEntry_MidiFade *) entry);
            break;
        case BHV_MIDI_FADE_POINT:
            obj_init_midifadepoint(obj, (LevelObjectEntry_MidiFadePoint *) entry);
            break;
        case BHV_MIDI_CHANNEL_SET:
            obj_init_midichset(obj, (LevelObjectEntry_Midichset *) entry);
            break;
        case BHV_EFFECT_BOX:
            obj_init_effectbox(obj, (LevelObjectEntry_EffectBox *) entry);
            break;
        case BHV_TROPHY_CABINET:
            obj_init_trophycab(obj, (LevelObjectEntry_TrophyCab *) entry);
            break;
        case BHV_BUBBLER:
            obj_init_bubbler(obj, (LevelObjectEntry_Bubbler *) entry);
            break;
        case BHV_FLY_COIN:
            obj_init_flycoin(obj, (LevelObjectEntry_FlyCoin *) entry);
            break;
        case BHV_GOLDEN_BALLOON:
            obj_init_goldenballoon(obj, (LevelObjectEntry_GoldenBalloon *) entry);
            break;
        case BHV_LASER_BOLT:
            obj_init_laserbolt(obj, (LevelObjectEntry_Laserbolt *) entry);
            break;
        case BHV_LASER_GUN:
            obj_init_lasergun(obj, (LevelObjectEntry_Lasergun *) entry);
            break;
        case BHV_ZIPPER_GROUND:
            obj_init_groundzipper(obj, (LevelObjectEntry_GroundZipper *) entry);
            break;
        case BHV_OVERRIDE_POS:
            obj_init_overridepos(obj, (LevelObjectEntry_OverridePos *) entry);
            break;
        case BHV_WIZPIG_SHIP:
            obj_init_wizpigship(obj, (LevelObjectEntry_WizpigShip *) entry);
            break;
        case BHV_BOOST:
            obj_init_boost(obj, (LevelObjectEntry_Boost *) entry);
            break;
        case BHV_SILVER_COIN:
            obj_init_silvercoin(obj, (LevelObjectEntry_SilverCoin *) entry);
            break;
        case BHV_WARDEN_SMOKE:
            obj_init_wardensmoke(obj, (LevelObjectEntry_WardenSmoke *) entry);
            break;
        case BHV_UNK_5E:
            obj_init_unknown94(obj, (LevelObjectEntry_Unknown94 *) entry, arg2);
            break;
        case BHV_TELEPORT:
            obj_init_teleport(obj, (LevelObjectEntry_Teleport *) entry);
            break;
        case BHV_ROCKET_SIGNPOST:
        case BHV_ROCKET_SIGNPOST_2:
            obj_init_lighthouse_rocketsignpost(obj, (LevelObjectEntry_Lighthouse_RocketSignpost *) entry);
            break;
        case BHV_RANGE_TRIGGER:
            obj_init_rangetrigger(obj, (LevelObjectEntry_RangeTrigger *) entry);
            break;
        case BHV_FIREBALL_OCTOWEAPON:
        case BHV_FIREBALL_OCTOWEAPON_2:
            obj_init_fireball_octoweapon(obj, (LevelObjectEntry_Fireball_Octoweapon *) entry);
            break;
        case BHV_FROG:
            obj_init_frog(obj, (LevelObjectEntry_Frog *) entry);
            break;
        case BHV_SILVER_COIN_2:
            obj_init_silvercoin_adv2(obj, (LevelObjectEntry_SilverCoinAdv2 *) entry);
            break;
        case BHV_LEVEL_NAME:
            obj_init_levelname(obj, (LevelObjectEntry_LevelName *) entry);
            break;
    }
}

s32 func_80023E30(s32 arg0) {
  s32 value = 0;
  switch (arg0 - 1){
    case 0x00:
      value = 0x1F;
      break;
    case 0x01:
      value = 0x13;
      break;
    case 0x04:
      value = 0x16;
      break;
    case 0x0B:
      value = 0x1B;
      break;
    case 0x0D:
    case 0x6E:
      value = 0x30;
      break;
    case 0x10:
    case 0x4C:
      value = 0x12;
      break;
    case 0x45:
    case 0x47:
    case 0x5F:
    case 0x60:
      value = 0x3B;
      break;
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x67:
      value = 0x3A;
      break;
    case 0x17:
      value = 0x04;
      break;
    case 0x1E:
      value = 0x1B;
      break;
    case 0x1F:
    case 0x3F:
    case 0x57:
    case 0x6D:
      value = 0x12;
      break;
    case 0x42:
      value = 0x30;
      break;
    case 0x25:
      value = 0x39;
      break;
    case 0x26:
      value = 0x12;
      break;
    case 0x27:
      value = 0x09;
      break;
    case 0x2C:
      value = 0x12;
      break;
    case 0x2F:
      value = 0x09;
      break;
    case 0x3E:
      value = 0x09;
      break;
    case 0x31:
    case 0x37:
    case 0x4F:
    case 0x53:
    case 0x55:
    case 0x72:
      value = 0x0B;
      break;
    case 0x35:
      value = 0x0B;
      break;
    case 0x49:
    case 0x5E:
    case 0x62:
    case 0x63:
      value = 0x31;
      break;
    case 0x5A:
      value = 0x01;
      break;
    case 0x50:
      value = 0x0A;
      break;
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
      value = 0x10;
      break;
    case 0x51:
      value = 0x12;
      break;
    case 0x30:
    case 0x32:
    case 0x3C:
      value = 0x02;
      break;
    case 0x3D:
      value = 0x1B;
      break;
    case 0x6C:
      value = 0x0B;
      break;
    case 0x71:
      value = 0x01;
      break;
  }
  return value;
}

void run_object_loop_func(Object *obj, s32 updateRate) {
#ifdef PUPPYPRINT_DEBUG
    u32 first = osGetTime();
#endif
    func_800B76B8(1, obj->unk4A);
    switch (obj->behaviorId) {
        case BHV_SCENERY:
            obj_loop_scenery(obj, updateRate);
            break;
        case BHV_FISH:
            obj_loop_fish(obj, updateRate);
            break;
        case BHV_ANIMATOR:
            obj_loop_animator(obj, updateRate);
            break;
        case BHV_SMOKE:
            obj_loop_smoke(obj, updateRate);
            break;
        case BHV_UNK_19:
            obj_loop_unknown25(obj, updateRate);
            break;
        case BHV_BOMB_EXPLOSION:
            obj_loop_bombexplosion(obj, updateRate);
            break;
        case BHV_EXIT:
            obj_loop_exit(obj, updateRate);
            break;
        case BHV_CAMERA_CONTROL:
            obj_loop_cameracontrol(obj, updateRate);
            break;
        case BHV_SETUP_POINT:
            obj_loop_setuppoint(obj, updateRate);
            break;
        case BHV_DINO_WHALE:
            obj_loop_dino_whale(obj, updateRate);
            break;
        case BHV_CHECKPOINT:
            obj_loop_checkpoint(obj, updateRate);
            break;
        case BHV_MODECHANGE:
            obj_loop_modechange(obj, updateRate);
            break;
        case BHV_BONUS:
            obj_loop_bonus(obj, updateRate);
            break;
        case BHV_DOOR:
            obj_loop_door(obj, updateRate);
            break;
        case BHV_FOG_CHANGER:
            obj_loop_fogchanger(obj);
            break;
        case BHV_AINODE:
            obj_loop_ainode(obj, updateRate);
            break;
        case BHV_WEAPON_BALLOON:
            obj_loop_weaponballoon(obj, updateRate);
            break;
        case BHV_BALLOON_POP:
            obj_loop_wballoonpop(obj, updateRate);
            break;
        case BHV_WEAPON:
        case BHV_WEAPON_2:
            obj_loop_weapon(obj, updateRate);
            break;
        case BHV_SKY_CONTROL:
            obj_loop_skycontrol(obj, updateRate);
            break;
        case BHV_TORCH_MIST:
            obj_loop_torch_mist(obj, updateRate);
            break;
        case BHV_TEXTURE_SCROLL:
            obj_loop_texscroll(obj, updateRate);
            break;
        case BHV_STOPWATCH_MAN:
            obj_loop_stopwatchman(obj, updateRate);
            break;
        case BHV_BANANA:
            obj_loop_banana(obj, updateRate);
            break;
        case BHV_BUOY_PIRATE_SHIP:
            obj_loop_buoy_pirateship(obj, updateRate);
            break;
        case BHV_LOG:
            obj_loop_log(obj, updateRate);
            break;
        case BHV_WEATHER:
            obj_loop_weather(obj, updateRate);
            break;
        case BHV_BRIDGE_WHALE_RAMP:
            obj_loop_bridge_whaleramp(obj, updateRate);
            break;
        case BHV_RAMP_SWITCH:
            obj_loop_rampswitch(obj, updateRate);
            break;
        case BHV_SEA_MONSTER:
            obj_loop_seamonster(obj, updateRate);
            break;
        case BHV_COLLECT_EGG:
            obj_loop_collectegg(obj, updateRate);
            break;
        case BHV_EGG_CREATOR:
            obj_loop_eggcreator(obj, updateRate);
            break;
        case BHV_CHARACTER_FLAG:
            obj_loop_characterflag(obj, updateRate);
            break;
        case BHV_ANIMATED_OBJECT:
        case BHV_ANIMATED_OBJECT_2:
        case BHV_ANIMATED_OBJECT_3:
        case BHV_ANIMATED_OBJECT_4:
            obj_loop_animobject(obj, updateRate);
            break;
        case BHV_WIZPIG_GHOSTS:
            obj_loop_wizghosts(obj, updateRate);
            break;
        case BHV_CAMERA_ANIMATION:
            obj_loop_animcamera(obj, updateRate);
            break;
        case BHV_INFO_POINT:
            obj_loop_infopoint(obj, updateRate);
            break;
        case BHV_CAR_ANIMATION:
            obj_loop_animcar(obj, updateRate);
            break;
        case BHV_CHARACTER_SELECT:
            obj_loop_char_select(obj, updateRate);
            break;
        case BHV_TRIGGER:
            obj_loop_trigger(obj, updateRate);
            break;
        case BHV_VEHICLE_ANIMATION:
            obj_loop_vehicleanim(obj, updateRate);
            break;
        case BHV_ZIPPER_WATER:
        case BHV_ZIPPER_AIR:
            obj_loop_airzippers_waterzippers(obj, updateRate);
            break;
        case BHV_UNK_3A:
            obj_loop_unknown58(obj, updateRate);
            break;
        case BHV_WAVE_POWER:
            obj_loop_wavepower(obj);
            break;
        case BHV_BUTTERFLY:
            obj_loop_butterfly(obj, updateRate);
            break;
        case BHV_PARK_WARDEN:
            obj_loop_parkwarden(obj, updateRate);
            break;
        case BHV_WORLD_KEY:
            obj_loop_worldkey(obj, updateRate); //arg1=speed
            break;
        case BHV_BANANA_SPAWNER:
            obj_loop_bananacreator(obj, updateRate);
            break;
        case BHV_TREASURE_SUCKER:
            obj_loop_treasuresucker(obj, updateRate);
            break;
        case BHV_LAVA_SPURT:
            obj_loop_lavaspurt(obj, updateRate);
            break;
        case BHV_POS_ARROW:
            obj_loop_posarrow(obj, updateRate);
            break;
        case BHV_HIT_TESTER:
        case BHV_HIT_TESTER_2:
        case BHV_HIT_TESTER_3:
        case BHV_HIT_TESTER_4:
            obj_loop_hittester(obj, updateRate);
            break;
        case BHV_SNOWBALL:
        case BHV_SNOWBALL_2:
        case BHV_SNOWBALL_3:
        case BHV_SNOWBALL_4:
            obj_loop_snowball(obj, updateRate);
            break;
        case BHV_EFFECT_BOX:
            obj_loop_effectbox(obj, updateRate);
            break;
        case BHV_TROPHY_CABINET:
            obj_loop_trophycab(obj, updateRate);
            break;
        case BHV_BUBBLER:
            obj_loop_bubbler(obj, updateRate);
            break;
        case BHV_FLY_COIN:
            obj_loop_flycoin(obj, updateRate);
            break;
        case BHV_GOLDEN_BALLOON:
            obj_loop_goldenballoon(obj, updateRate);
            break;
        case BHV_LASER_BOLT:
            obj_loop_laserbolt(obj, updateRate);
            break;
        case BHV_LASER_GUN:
            obj_loop_lasergun(obj, updateRate);
            break;
        case BHV_PARK_WARDEN_2:
            obj_loop_gbparkwarden(obj, updateRate);
            break;
        case BHV_ZIPPER_GROUND:
            obj_loop_groundzipper(obj, updateRate);
            break;
        case BHV_WIZPIG_SHIP:
            obj_loop_wizpigship(obj, updateRate);
            break;
        case BHV_SILVER_COIN:
        case BHV_SILVER_COIN_2:
            obj_loop_silvercoin(obj, updateRate);
            break;
        case BHV_WARDEN_SMOKE:
            obj_loop_wardensmoke(obj, updateRate);
            break;
        case BHV_UNK_5E:
            obj_loop_unknown94(obj, updateRate);
            break;
        case BHV_TELEPORT:
            obj_loop_teleport(obj, updateRate);
            break;
        case BHV_RANGE_TRIGGER:
            obj_loop_rangetrigger(obj, updateRate);
            break;
        case BHV_ROCKET_SIGNPOST_2:
            obj_loop_rocketsignpost(obj, updateRate);
            break;
        case BHV_FIREBALL_OCTOWEAPON:
        case BHV_FIREBALL_OCTOWEAPON_2:
            obj_loop_fireball_octoweapon(obj, updateRate);
            break;
        case BHV_FROG:
            obj_loop_frog(obj, updateRate);
            break;
        case BHV_TT_DOOR:
            obj_loop_ttdoor(obj, updateRate);
            break;
        case BHV_DOOR_OPENER:
            obj_loop_dooropener(obj, updateRate);
            break;
        case BHV_PIG_ROCKETEER:
            obj_loop_pigrocketeer(obj, updateRate);
            break;
        case BHV_LEVEL_NAME:
            obj_loop_levelname(obj, updateRate);
            break;
    }
    func_800B76B8(1, -1);
#ifdef PUPPYPRINT_DEBUG
    profiler_add_obj(obj->behaviorId, osGetTime() - first);
#endif
}

UNUSED void func_8002458C(UNUSED s32 arg0) {
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
