/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8006A6B0 */

#include "unknown_06B2B0.h"

#include <PR/os_cont.h>
#include <PR/gu.h>
#include "memory.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "asset_sections.h"
#include "menu.h"
#include "video.h"
#include "lib/src/mips1/sc/sched.h"
#include "gzip.h"
#include "printf.h"
#include "thread0_epc.h"
#include "thread30.h"

/************ .rodata ************/

const char D_800E70B0[] = "LOADLEVEL Error: Level out of range\n";
const char D_800E70D8[] = "BossLev problem\n";
const char D_800E70EC[] = "AITABLE Error: Table out of range\n";
const char D_800E7110[] = "1.1605";
const char D_800E7118[] = "02/10/97 16:03";
const char D_800E7128[] = "pmountain";

const char D_800E7134[] = "BBB\n";
const char D_800E713C[] = "CAR";
const char D_800E7140[] = "HOV";
const char D_800E7144[] = "PLN";
const char D_800E7148[] = "Swapping\n";

/*********************************/

/************ .data ************/

s8 *D_800DD310 = NULL; // Currently unknown, might be a different type. 
s8  D_800DD314 = -1;
u8  D_800DD318 = 0;
s32 D_800DD31C = 0;

// Updated automatically from calc_func_checksums.py
s32 gFunc80068158Checksum = 0x585E;
s32 gFunc80068158Length = 0x154;

s16 D_800DD328 = 0;
s16 D_800DD32C = 0;

s8 D_800DD330 = 0;

// Unused
char *D_800DD334[6] = {
    NULL, NULL, NULL, // These could be a file boundary.
    D_800E7110, D_800E7118, D_800E7128
};

// Unused
char gBuildString[40] = "Version 7.7 29/09/97 15.00 L.Schuneman";

s8  D_800DD374 = 0;
s32 D_800DD378 = 1;
s32 D_800DD37C = 0;
s32 D_800DD380 = 0; // Currently unknown, might be a different type. 
s32 D_800DD384 = 0;
s32 D_800DD388 = 0; // Currently unknown, might be a different type. 
s8  D_800DD38C = 0;
s8  D_800DD390 = 0;
s16 D_800DD394 = 0;
s8  D_800DD398 = 0;
s8  D_800DD39C = 0; 
s8  D_800DD3A0 = 0;
s32 D_800DD3A4 = 0; // Currently unknown, might be a different type. 
s32 D_800DD3A8 = 0; // Currently unknown, might be a different type. 
s32 D_800DD3AC = 0; // Currently unknown, might be a different type. 
s32 gNumF3dCmdsPerPlayer[4]  = { 4500, 7000, 11000, 11000 };
s32 gNumHudVertsPerPlayer[4] = { 300, 600, 850, 900 };
s32 gNumHudMatPerPlayer[4]   = { 300, 400, 550, 600 };
s32 gNumHudTrisPerPlayer[4]  = { 20, 30, 40, 50 };

s8  D_800DD3F0 = 0;
s16 D_800DD3F4[8] = {
    -32768, 0, 20, 0,
    255, -1, 20, -1
};
s32 D_800DD404 = 12;

unknown800DD408 D_800DD408 = {
    0, 255, 255, 255, 30, 0xFFFF
};

// Unused?
char *D_800DD410[3] = {
    D_800E713C, D_800E7140, D_800E7144
};

// Not sure if this is an array or a struct.
s32 D_800DD41C[2] = { 
    0, 0x001EFFFF
};

s32 D_800DD424[2] = { 
    0, 0x0104FFFF
};

/*******************************/

extern s32 gShowControllerPakMenu;

/************ .bss ************/

s32 *gTempAssetTable;
s32 D_80121164;
LevelHeader *gCurrentLevelHeader;
u8 **D_8012116C;
s32 gNumberOfLevelHeaders;
s32 gNumberOfWorlds;

s8 *D_80121178;

/* Size: 6 bytes */
typedef struct unk8012117C {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s16 unk4;
} unk8012117C;
unk8012117C *D_8012117C;

s32 D_80121180[16];

s32 D_801211C0[2];
s16 D_801211C8[20];
Gfx *gDisplayLists[2];
Gfx *gCurrDisplayList;
s32 D_801211FC;
s32 *gHudMatrices[2];
s32 gCurrHudMat;
s32 *gHudVertices[2];
s32 gCurrHudVerts;
s32 *gHudTriangles[2];
s32 gCurrHudTris;
s32 D_80121230[8];
s8  D_80121250[16];
OSSched *D_80121260;
s32 D_80121268[2208]; //Padding
s32 D_801234E8;
s32 D_801234EC;
s32 D_801234F0;
s32 D_801234F4;
s32 D_801234F8;
s32 D_801234FC;
s32 D_80123500;
s32 D_80123504;
s32 D_80123508;
s32 D_8012350C;
Settings *gSettingsPtr;
s8  D_80123514;
s8  gIsPaused;
s8  D_80123516;
s32 D_80123518;
s32 D_8012351C;
s32 D_80123520;
s8  D_80123524;
s8  D_80123525;
s8  D_80123526;
s32 gCurrNumF3dCmdsPerPlayer;
s32 gCurrNumHudMatPerPlayer;
s32 gCurrNumHudTrisPerPlayer;
s32 gCurrNumHudVertsPerPlayer;
OSScClient *D_80123538[3];
OSMesg *D_80123544;
OSMesgQueue *D_80123548;
s32 D_8012354C;
s32 D_80123550[4];
s32 D_80123560[8];

/******************************/

extern s32 gVideoCurrFramebuffer;
extern s32 gVideoLastFramebuffer;
extern s32 gVideoLastDepthBuffer;

void func_8006F43C(void);

void func_800014BC(f32 arg0);
s8 *get_misc_asset(s32 arg0);
s32 func_8006A624(s8 arg0);
void func_8006F870(Matrix, s32*);
s16 get_level_segment_index_from_position(f32, f32, f32);    
void func_8006A50C(void);
void func_800665E8(s32 arg0);
void load_level_2(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8006C164(void);
void func_8000E194(void);
f32 sqrtf(f32);
void osSetTime(u64);
void func_8001D5E0(f32 arg0, f32 arg1, f32 arg2);
void func_800705F8(s32, f32, f32, f32);
void func_8006ECFC(s32 arg0);
void load_level_3(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800813C0();
void func_80004A60(s32, s32);
void render(void);
void func_8006C3E0(void);
Settings *get_settings(void);
s32 is_in_tracks_mode(void);
s32 *load_asset_section_from_rom(s32);
void load_asset_to_address(u32, s32*, s32, s32);
void func_8006C1AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8006C2E4(void);
s16 func_8006C2F0(void);
void func_8006DB20(s32 arg0);
void func_80072708(void);
void update_camera_fov(f32);
void func_8006BFC8(s8 *arg0);
void func_80068158(Gfx**, s32, s32, s32, s32);
s32 get_trophy_race_world_id(void);
void func_8006DCF8(s32 arg0);
void func_8006EC48(s32 arg0);
void calc_and_alloc_heap_for_settings(void);
void reset_character_id_slots(void);
void func_8006EFDC(void);

#ifdef NON_MATCHING

void func_8006A6B0(void) {
    s32 i, count, checksumCount;
    s32 temp;
    u8 *sp44;
    sp44 = allocate_from_main_pool_safe(sizeof(LevelHeader), COLOR_TAG_YELLOW);
    gTempAssetTable = load_asset_section_from_rom(ASSET_LEVEL_HEADERS_TABLE);
    for(i = 0; i < 16; i++) {
        D_80121180[i] = 0;
    }
    gNumberOfLevelHeaders = 0;
    while (gTempAssetTable[gNumberOfLevelHeaders] != -1) {
        gNumberOfLevelHeaders++;
    }
    gNumberOfLevelHeaders--;
    D_8012117C = allocate_from_main_pool_safe(gNumberOfLevelHeaders * sizeof(unk8012117C), COLOR_TAG_YELLOW);
    gNumberOfWorlds = -1;
    gCurrentLevelHeader = sp44;
    for (i = 0; i < gNumberOfLevelHeaders; i++) {
        load_asset_to_address(ASSET_LEVEL_HEADERS, gCurrentLevelHeader, gTempAssetTable[i], sizeof(LevelHeader));
        if (gNumberOfWorlds < gCurrentLevelHeader->world) {
            gNumberOfWorlds = gCurrentLevelHeader->world;
        }
        if (gCurrentLevelHeader->race_type >= 0 && gCurrentLevelHeader->race_type < 16) {
            D_80121180[gCurrentLevelHeader->race_type]++;
        }
        D_8012117C[i].unk0 = gCurrentLevelHeader->world;
        D_8012117C[i].unk1 = gCurrentLevelHeader->race_type;
        D_8012117C[i].unk2 = gCurrentLevelHeader->available_vehicles << 4;
        D_8012117C[i].unk2 |= gCurrentLevelHeader->vehicle & 0xF;
        D_8012117C[i].unk3 = 1;
        D_8012117C[i].unk4 = gCurrentLevelHeader->unkB0;
    }
    gNumberOfWorlds++;
    D_80121178 = allocate_from_main_pool_safe(gNumberOfWorlds, COLOR_TAG_YELLOW);
    for (i = 0; i < gNumberOfWorlds; i++) {
        D_80121178[i] = -1;
    }
    for (i = 0; i < gNumberOfLevelHeaders; i++) {
        if (D_8012117C[i].unk1 == 5) {
            D_80121178[D_8012117C[i].unk0] = i;
        }
    }
    free_from_memory_pool(gTempAssetTable);
    free_from_memory_pool(sp44);
    
    gTempAssetTable = load_asset_section_from_rom(ASSET_LEVEL_NAMES_TABLE);
    count = 0;
    while (gTempAssetTable[count] != -1) {
        count++;
    }
    count--;
    temp = gTempAssetTable[count] - gTempAssetTable[0];
    // Minor issue here.
    D_8012116C = allocate_from_main_pool_safe(count * sizeof(s32), COLOR_TAG_YELLOW);
    D_800DD310 = allocate_from_main_pool_safe(temp, COLOR_TAG_YELLOW);
    load_asset_to_address(ASSET_LEVEL_NAMES, D_800DD310, 0, temp);
    for(i = 0; i < count; i++) {
        D_8012116C[i] = &D_800DD310[gTempAssetTable[i]];
    }
    free_from_memory_pool(gTempAssetTable);
    
    // Anti-piracy/Anti-tamper check.
    checksumCount = 0;
    for(i = 0; i < gFunc80068158Length; i++) {
        checksumCount += ((u8*)&func_80068158)[i];
    }
    if (checksumCount != gFunc80068158Checksum) {
        // Disables button inputs in some parts of the game if the checksum doesn't match.
        disable_button_mask();
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_06B2B0/func_8006A6B0.s")
#endif

// Unused.
s16 func_8006ABB4(s32 arg0) {
    if (arg0 < 0) {
        return 0xE10;
    }
    if (arg0 >= gNumberOfLevelHeaders) {
        return 0xE10;
    }
    return D_8012117C[arg0].unk4;
}

// Unused?
GLOBAL_ASM("asm/non_matchings/unknown_06B2B0/func_8006AC00.s")

// Unused?
GLOBAL_ASM("asm/non_matchings/unknown_06B2B0/func_8006AE2C.s")

// Unused.
s32 func_8006B018(s8 arg0) {
    if ((arg0 >= 0) && (arg0 < 16)) {
        return D_80121180[arg0];
    }
    return 0;
}

// Unused.
s32 func_8006B054(s8 arg0) {
    s32 out, i;
    out = 0;
    for(i = 0; i < gNumberOfLevelHeaders; i++) {
        if (arg0 == D_8012117C[i].unk0) {
            out++;
        }
    }
    return out;
}

s32 func_8006B0AC(s32 arg0) {
    if (arg0 > 0 && arg0 < gNumberOfLevelHeaders) {
        return D_8012117C[arg0].unk2 & 0xF;
    }
    return 0;
}

s32 func_8006B0F8(s32 arg0) {
    if (arg0 > 0 && arg0 < gNumberOfLevelHeaders) {
        s32 temp = D_8012117C[arg0].unk2;
        if(temp != 0) {
            return (temp >> 4) & 0xF;
        }
    }
    return 1;
}

s8 func_8006B14C(s32 arg0) {
    if (arg0 >= 0 && arg0 < gNumberOfLevelHeaders) {
        return D_8012117C[arg0].unk1;
    }
    return -1;
}

s8 func_8006B190(s32 arg0) {
    if (arg0 >= 0 && arg0 < gNumberOfLevelHeaders) {
        return D_8012117C[arg0].unk0;
    }
    return 0;
}

s32 func_8006B1D4(s32 arg0) {
    s8 *temp;
    
    if (arg0 < 0 || arg0 >= gNumberOfWorlds) {
        arg0 = 0;
    }
    temp = get_misc_asset(0x1B);
    
    return temp[arg0];
}

void get_number_of_levels_and_worlds(s32 *outLevelCount, s32 *outWorldCount) {
    *outLevelCount = gNumberOfLevelHeaders;
    *outWorldCount = gNumberOfWorlds;
}

s32 func_8006B240(void) {
    return D_800DD31C;
}

// This isn't matching, but there shouldn't be any issues (hopefully).
#ifdef NON_MATCHING

void load_level(s32 levelId, s32 numberOfPlayers, s32 entranceId, s32 vehicleId, s32 cutsceneId) {
    s32 maxLevelCount;
    s32 sp44;
    s32 noPlayers;
    s32 phi_s0;
    s32 vehicle;
    s32 i;
    s32 size;
    s32 offset;
    s32 temp;
    s32 phi_v1_2;
    s32 phi_v0_2;
    s8 *someAsset;
    Settings *settings;
    
    func_80072708();
    if (cutsceneId == -1) {
        cutsceneId = 0;
    }
    if (numberOfPlayers == ZERO_PLAYERS) {
        noPlayers = TRUE;
        numberOfPlayers = ONE_PLAYER;
    } else {
        noPlayers = FALSE;
    }
    if (numberOfPlayers == ONE_PLAYER) {
        func_8000318C(8);
    } else if (numberOfPlayers == TWO_PLAYERS) {
        func_8000318C(12);
    } else {
        func_8000318C(16);
    }
    
    settings = get_settings();
    gTempAssetTable = load_asset_section_from_rom(ASSET_LEVEL_HEADERS_TABLE);
    maxLevelCount = 0;
    while (gTempAssetTable[maxLevelCount] != -1) {
        maxLevelCount++;
    }
    maxLevelCount--;
    if (levelId >= maxLevelCount) {
        levelId = 0;
    }
    offset = gTempAssetTable[levelId];
    size = gTempAssetTable[levelId + 1] - offset;
    gCurrentLevelHeader = (LevelHeader*)allocate_from_main_pool_safe(size, COLOR_TAG_YELLOW);
    load_asset_to_address(ASSET_LEVEL_HEADERS, gCurrentLevelHeader, offset, size);
    D_800DD330 = 0;
    sp44 = levelId;
    if (gCurrentLevelHeader->race_type == RACE_TYPE_DEFAULT) {
        func_8006C2E4();
    }
    if (func_8006C2F0() == 0) {
        if (D_800DD32C == 0) {
            if (gCurrentLevelHeader->race_type == RACE_TYPE_BOSS) {
                phi_v1_2 = settings->courseFlagsPtr[levelId];
                phi_v0_2 = FALSE;
                if (gCurrentLevelHeader->world == 0 || gCurrentLevelHeader->world == 5) {
                    phi_v0_2 = TRUE;
                }
                if (!(phi_v1_2 & 1) || phi_v0_2) {
                    func_8006C1AC(levelId, entranceId, vehicleId, cutsceneId);
                    if (settings->bosses & (1 << settings->worldId)) {
                        cutsceneId = 7;
                    } else {
                        cutsceneId = 3;
                    }
                    if (phi_v0_2) {
                        cutsceneId = 0;
                        if (phi_v1_2 & 1) {
                            D_800DD330 = (u8)2;
                        }
                    }
                    someAsset = get_misc_asset(0x43);
                    phi_s0 = 0;
                    while(levelId != someAsset[phi_s0 + 1]) {
                        phi_s0++;
                    }
                    levelId = someAsset[phi_s0 + 1];
                    entranceId = cutsceneId;
                }
                
            }
            if (gCurrentLevelHeader->race_type == RACE_TYPE_HUB_AREA) {
                s32 curWorld = gCurrentLevelHeader->world;
                if (curWorld > 0 && curWorld < 5) {
                    if (settings->keys & (1 << curWorld)) {
                        s32 temp_v0_5 = 0x4000 << (curWorld + 0x1F);
                        if (!(settings->cutsceneFlags & temp_v0_5)) {
                            // Trigger World Key unlocking Challenge Door cutscene.
                            func_8006C1AC(levelId, entranceId, vehicleId, cutsceneId);
                            settings->cutsceneFlags |= temp_v0_5;
                            levelId = get_misc_asset(0x44)[curWorld-1];
                            entranceId = 0;
                            cutsceneId = 5;
                        }
                    }
                }
            }
            if (gCurrentLevelHeader->race_type == RACE_TYPE_HUB_AREA && gCurrentLevelHeader->world == 0 && !(settings->cutsceneFlags & 0x2000) && settings->wizpigAmulet >= 4) {
                // Trigger wizpig face cutscene
                s32 savedEntranceId = entranceId;
                s32 savedCutsceneId = cutsceneId;
                cutsceneId = 0;
                entranceId = 0;
                func_8006C1AC(levelId, savedEntranceId, vehicleId, savedCutsceneId);
                settings->cutsceneFlags |= 0x2000;
                levelId = get_misc_asset(0x44)[1];
            }
        }
    }
    D_800DD32C = 0;
    if (sp44 != levelId) {
        free_from_memory_pool(gCurrentLevelHeader);
        offset = gTempAssetTable[levelId];
        size = gTempAssetTable[levelId + 1] - offset;
        gCurrentLevelHeader = allocate_from_main_pool_safe(size, COLOR_TAG_YELLOW);
        load_asset_to_address(ASSET_LEVEL_HEADERS, gCurrentLevelHeader, offset, size);
    }
    free_from_memory_pool(gTempAssetTable);
    func_8006BFC8(&gCurrentLevelHeader->unk20);
    func_8000CBC0();
    D_80121164 = levelId;
    for (i = 0; i < 7; i++) {
        if ((s32)gCurrentLevelHeader->unk74[i] != -1) {
            gCurrentLevelHeader->unk74[i] = get_misc_asset((s32)gCurrentLevelHeader->unk74[i]);
            func_8007F1E8(gCurrentLevelHeader->unk74[i]);
        }
    }
    if (cutsceneId == 0x64) {
        if(get_trophy_race_world_id() != 0 && gCurrentLevelHeader->race_type == RACE_TYPE_DEFAULT) {
            cutsceneId = 0;
        } else if(is_in_tracks_mode() == 1 && gCurrentLevelHeader->race_type == RACE_TYPE_DEFAULT) {
            cutsceneId = 0;
        }
    }
    if (gCurrentLevelHeader->race_type == RACE_TYPE_DEFAULT || gCurrentLevelHeader->race_type == RACE_TYPE_BOSS) {
        D_800DD31C = 1;
    } else {
        D_800DD31C = 0;
    }
    if (noPlayers && gCurrentLevelHeader->race_type != RACE_TYPE_CUTSCENE_2) {
        gCurrentLevelHeader->race_type = RACE_TYPE_CUTSCENE_1;
    }
    func_80000BE0(gCurrentLevelHeader->unkB3);
    func_80000CBC();
    func_80031BB8(0x20);
    vehicle = VEHICLE_CAR;
    if (vehicleId >= VEHICLE_CAR && vehicleId < NUMBER_OF_VEHICLE_TYPES) {
        vehicle = gCurrentLevelHeader->unk4F[vehicleId];
    }
    func_80017E74(vehicle);
    temp = settings->worldId;
    if (gCurrentLevelHeader->world != -1) {
        settings->worldId = gCurrentLevelHeader->world;
    }
    settings->courseId = levelId;
    if (temp == 0 && settings->worldId > 0) {
        D_800DD314 = func_8006DB2C();
    }
    if (settings->worldId == 0 && temp > 0 && D_800DD314 != -1) {
        vehicleId = D_800DD314;
    }
    func_8006DB20(vehicleId);
    if (gCurrentLevelHeader->race_type == RACE_TYPE_HUB_AREA) {
        if (settings->worldId > 0) {
            s32 temp_s0_5 = 8 << (settings->worldId + 31);
            if (settings->worldId == 5) {
                if (settings->balloonsPtr[0] >= 47) {
                    if (settings->ttAmulet >= 4) {
                        if ((settings->cutsceneFlags & temp_s0_5) == 0) {
                            settings->cutsceneFlags |= temp_s0_5;
                            cutsceneId = 5;
                        }
                    }
                }
            } else {
                if (settings->balloonsPtr[settings->worldId] >= 4) {
                    if ((settings->cutsceneFlags & temp_s0_5) == 0) {
                        settings->cutsceneFlags |= temp_s0_5;
                        cutsceneId = 5;
                    }
                }
                if (settings->balloonsPtr[settings->worldId] >= 8) {
                    s32 temp3 = temp_s0_5 << 5;
                    if (!(settings->cutsceneFlags & temp3)) {
                        settings->cutsceneFlags |= temp3;
                        cutsceneId = 5;
                    }
                }
            }
        }
    }
    if (numberOfPlayers != ONE_PLAYER && gCurrentLevelHeader->race_type == RACE_TYPE_DEFAULT) {
        cutsceneId = 0x64;
    }
    if ((gCurrentLevelHeader->race_type == RACE_TYPE_DEFAULT || (gCurrentLevelHeader->race_type & RACE_TYPE_CHALLENGE)) && is_in_two_player_adventure()) {
        D_800DD318 = 1;
        cutsceneId = 0x64;
    } else {
        D_800DD318 = 0;
    }
    if (gCurrentLevelHeader->race_type == RACE_TYPE_DEFAULT && !noPlayers && is_time_trial_enabled()) {
        cutsceneId = 0x64;
    }
    func_8001E450(cutsceneId);
    func_800249F0(gCurrentLevelHeader->geometry, gCurrentLevelHeader->skybox, numberOfPlayers, vehicleId, entranceId, gCurrentLevelHeader->collectables, gCurrentLevelHeader->unkBA);
    if (gCurrentLevelHeader->unk3A == 0 && gCurrentLevelHeader->unk3C == 0 && gCurrentLevelHeader->fogR == 0 && gCurrentLevelHeader->fogG == 0 && gCurrentLevelHeader->fogB == 0) {
        for(i = 0; i < 4; i++) {
            func_800307BC(i);
        }
    } else {
        for(i = 0; i < 4; i++) {
            func_80030664(i, gCurrentLevelHeader->unk3A, gCurrentLevelHeader->unk3C, (u8)gCurrentLevelHeader->fogR, gCurrentLevelHeader->fogG, gCurrentLevelHeader->fogB);
        }
    }
    settings = get_settings();
    if (gCurrentLevelHeader->world != -1) {
        settings->worldId = gCurrentLevelHeader->world;
    }
    settings->courseId = levelId;
    if (gCurrentLevelHeader->weather_enable > 0) {
        func_800AB4A8(
            gCurrentLevelHeader->unk92, 
            gCurrentLevelHeader->weather_enable, 
            gCurrentLevelHeader->unk96 << 8, 
            gCurrentLevelHeader->unk98 << 8, 
            gCurrentLevelHeader->unk9A << 8, 
            gCurrentLevelHeader->unk94 * 0x101, 
            gCurrentLevelHeader->unk95 * 0x101
        );
        func_800AB308(-1, -0x200);
    }
    if (gCurrentLevelHeader->unk49 == -1) {
        gCurrentLevelHeader->unkA4 = load_texture(gCurrentLevelHeader->unkA4);
        gCurrentLevelHeader->unkA8 = (u16)0;
        gCurrentLevelHeader->unkAA = (u16)0;
    }
    if ((s32)gCurrentLevelHeader->pulseLightData != -1) { 
        // Only used in spaceport alpha for some pulsating lights.
        gCurrentLevelHeader->pulseLightData = get_misc_asset((s32)gCurrentLevelHeader->pulseLightData);
        init_pulsating_light_data(gCurrentLevelHeader->pulseLightData);
    }
    update_camera_fov(gCurrentLevelHeader->cameraFOV);
    func_80077B34(gCurrentLevelHeader->bgColorRed, gCurrentLevelHeader->bgColorGreen, gCurrentLevelHeader->bgColorBlue);
    func_8007A974();
    func_8007AB24(gCurrentLevelHeader->unk4[numberOfPlayers]);
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_06B2B0/load_level.s")
#endif

void func_8006BD10(f32 arg0) {
    if (gCurrentLevelHeader->music != 0) {
        func_800012E8();
        play_music(gCurrentLevelHeader->music);
        func_800014BC(arg0);
        func_80001074(gCurrentLevelHeader->instruments);
    }
}

s32 func_8006BD88(void) {
    return D_80121164;
}

u8 get_current_level_race_type(void) {
    return gCurrentLevelHeader->race_type;
}

LevelHeader *get_current_level_header(void) {
    return gCurrentLevelHeader;
}

/* Unused? */
u8 func_8006BDC0(void) {
    return gNumberOfLevelHeaders - 1;
}

u8 *func_8006BDDC(s32 arg0) {
    u8 *text;
    u8 numberOfNullPointers = 0;
    
    if(arg0 < 0 || arg0 >= gNumberOfLevelHeaders) {
        return NULL;
    }
    
    text = D_8012116C[arg0];
    switch(get_language()) {
        case GERMAN:
            while(numberOfNullPointers < 1) {
                if(*(text++) == 0) {
                    numberOfNullPointers++;
                }
            }
            break;
        case FRENCH:
            while(numberOfNullPointers < 2) {
                if(*(text++) == 0) {
                    numberOfNullPointers++;
                }
            }
            break;
        case JAPANESE:
            while(numberOfNullPointers < 3) {
                if(*(text++) == 0) {
                    numberOfNullPointers++;
                }
            }
            break;
    }
    return text;
}

void func_8006BEFC(void) {
    func_8006C164();
    func_80077B34(0, 0, 0);
    free_from_memory_pool(gCurrentLevelHeader);
    func_800049D8();
    func_80001844();
    func_800018E0();
    func_800012E8();
    func_80031B60();
    func_8002C7D4();
    func_80008174();
    func_80000968(0);
    if (gCurrentLevelHeader->weather_enable > 0) {
        func_800AB35C();
    }
    if (gCurrentLevelHeader->unk49 == 0xFF) {
       free_texture(gCurrentLevelHeader->unkA4);
    }
}

void func_8006BFC8(s8 *arg0) {
    s32 temp, temp2;
    s16 phi_v1;
    s8 phi_s0;
    Settings *settings;
    
    phi_s0 = 0;
    if (!is_in_tracks_mode()) {
        settings = get_settings();
        temp = settings->courseFlagsPtr[settings->courseId];
        if (temp & 2) {
            phi_s0 = 1;
        }
        if (temp & 4) {
            phi_s0 = 2;
        }
    } else {
        phi_s0 = 3;
    }
    
    if (get_trophy_race_world_id() != 0) {
        phi_s0 = 4;
    }
    
    if(is_in_adventure_two()){
        phi_s0 += 5;
    }
    
    phi_s0 = arg0[phi_s0];
    
    if ((get_filtered_cheats() << 6) < 0) {
        phi_s0 = 9;
    }
    if (func_8006DA0C() == 1) {
        phi_s0 = 5;
    }
    gTempAssetTable = load_asset_section_from_rom(ASSET_UNKNOWN_0_TABLE);
    phi_v1 = 0;
    while (-1 != (s32)gTempAssetTable[phi_v1]) {
        phi_v1++;
    }
    phi_v1--;
    if (phi_s0 >= phi_v1) {
        phi_s0 = 0;
    }
    temp2 = gTempAssetTable[phi_s0];
    temp = gTempAssetTable[phi_s0 + 1] - temp2;
    D_801211C0[0] = allocate_from_main_pool_safe(temp, COLOR_TAG_YELLOW);
    load_asset_to_address(ASSET_UNKNOWN_0, D_801211C0[0], temp2, temp);
    free_from_memory_pool(gTempAssetTable);
}

void func_8006C164(void) {
    free_from_memory_pool(D_801211C0[0]);
}

s32 func_8006C18C(void) {
    return D_801211C0[0];
}

s8 func_8006C19C(void) {
    return D_800DD318;
}

void func_8006C1AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_801211C8[D_800DD328++] = arg0;
    D_801211C8[D_800DD328++] = arg1;
    D_801211C8[D_800DD328++] = arg2;
    D_801211C8[D_800DD328++] = arg3;
}

void func_8006C22C(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s16 temp_v1;
    
    D_800DD328--;
    *arg3 = D_801211C8[D_800DD328];
    D_800DD328--;
    temp_v1 = D_801211C8[D_800DD328];
    D_800DD328--;
    *arg1 = D_801211C8[D_800DD328];
    D_800DD328--;
    *arg0 = D_801211C8[D_800DD328];
    
    if (temp_v1 != -1) {
        *arg2 = temp_v1;
    }
    
    D_800DD32C = 1;
}


void func_8006C2E4(void) {
    D_800DD328 = 0;
}

s16 func_8006C2F0(void) {
    return D_800DD328;
}

s32 func_8006C300(void) {
    if (D_800DD330 >= 2) {
        D_800DD330 = 1;
        return 0;
    } else {
        return D_800DD330;
    }
}

void thread3_main(s32 arg0) {
    func_8006C3E0();
    D_800DD37C = func_8006A1C4(D_800DD37C, 0);
    D_80123520 = 0;
    D_801234EC = -1;
    while(1) {
        if (func_8006EAC0() != 0) {
            func_80072708();
            audioStopThread();
            stop_thread30();
            __osSpSetStatus(0xAAAA82);
            func_800CD250(0x1D6);
            while(1); // Infinite loop
        }
        render();
        func_80065E30();
    }
}

void func_8006C3E0(void) {
    s32 mode;

    init_main_memory_pool();
    func_800C6170();
    D_800DD374 = TRUE;
    if (func_8006F4EC() != 0) {
        D_800DD374 = FALSE;
    }
    D_80123514 = FALSE;
    D_80123518 = 0;
    
    if (osTvType == TV_TYPE_PAL) {
        mode = 14;
    } else if (osTvType == TV_TYPE_NTSC) {
        mode = 0;
    } else if (osTvType == TV_TYPE_MPAL) {
        mode = 28;
    }
    
    osCreateScheduler(&D_80121260, &D_801234E8, /*priority*/ 13, (u8) mode, 1);
    D_800DD3A0 = 0;
    if (func_8006EFB8() == 0) {
        D_800DD3A0 = 1;
    }
    init_video(1, &D_80121260);
    func_80076BA0();
    func_80078100(&D_80121260);
    audio_init(&D_80121260);
    func_80008040();
    D_800DD384 = func_8006A10C();
    func_8007AC70();
    func_8005F850();
    func_8000BF8C();
    func_800B5E88();
    func_800598D0();
    init_particle_assets();
    func_800AB1F0();
    calc_and_alloc_heap_for_settings();
    func_8006EFDC();
    load_fonts();
    func_80075B18();
    func_80081218();
    create_and_start_thread30();
    osCreateMesgQueue(&D_80123548, &D_80123544, 1);
    osScAddClient(&D_80121260, &D_80123538, &D_80123548, 3);
    D_80123560[0] = 0;
    D_80123504 = 0;
    D_80123508 = 0;
    D_801234E8 = 0;
    
    gCurrDisplayList = gDisplayLists[D_801234E8];
    gDPFullSync(gCurrDisplayList++)
    gSPEndDisplayList(gCurrDisplayList++)
    
    osSetTime(0);
}

void func_8006CCF0(s32 arg0);

void render(void) {
    s32 phi_v0;
    s32 phi_v0_2;
    s32 temp, temp2;
    
    osSetTime(0);
    
    if (D_800DD380 == 8) {
        gCurrDisplayList = gDisplayLists[D_801234E8];
        set_rsp_segment(&gCurrDisplayList, 0, 0);
        set_rsp_segment(&gCurrDisplayList, 1, gVideoCurrFramebuffer);
        set_rsp_segment(&gCurrDisplayList, 2, gVideoLastDepthBuffer);
        set_rsp_segment(&gCurrDisplayList, 4, gVideoCurrFramebuffer - 0x500);
    }
    if (D_800DD3F0 == 0) {
        setupOSTasks(gDisplayLists[D_801234E8], gCurrDisplayList, 0);
        D_801234E8 += 1;
        D_801234E8 &= 1;
    }
    if (D_800DD3F0 != 0) {
        D_800DD3F0 -= 1;
    }
    
    gCurrDisplayList = gDisplayLists[D_801234E8];
    gCurrHudMat = gHudMatrices[D_801234E8];
    gCurrHudVerts = gHudVertices[D_801234E8];
    gCurrHudTris = gHudTriangles[D_801234E8];
    
    set_rsp_segment(&gCurrDisplayList, 0, 0);
    set_rsp_segment(&gCurrDisplayList, 1, gVideoLastFramebuffer);
    set_rsp_segment(&gCurrDisplayList, 2, gVideoLastDepthBuffer);
    set_rsp_segment(&gCurrDisplayList, 4, gVideoLastFramebuffer - 0x500);
    func_800780DC(&gCurrDisplayList);
    func_80078054(&gCurrDisplayList);
    render_background(&gCurrDisplayList, &gCurrHudMat, 1);
    D_800DD37C = func_8006A1C4(D_800DD37C, D_800DD404);
    if (func_800B76DC() != 0) {
        render_epc_lock_up_display();
        D_801234EC = 5;
    }
    if (D_800DD3A0 != 0) {
        phi_v0 = 0;
        while(phi_v0 != 10000000) {
            phi_v0 += 1;
        }
        if (phi_v0 >= 20000001) { // This shouldn't ever be true?
            render_printf(D_800E7134 /* "BBB\n" */);
        }
    }
    
    switch(D_801234EC) {
        case -1: // Pre-boot screen
            func_8006F43C();
            break;
        case 1: // In a menu
            func_8006DCF8(D_800DD404);
            break;
        case 0: // In game (Controlling a character)
            func_8006CCF0(D_800DD404);
            break;
        case 5: // EPC (lockup display)
            func_800B77D4(D_800DD404);
            break;
    }
    
    // This is a good spot to place custom text if you want it to overlay it over ALL the 
    // menus & gameplay.
    
    func_80000D00((u8)D_800DD404);
    func_800B5F78(&gCurrDisplayList);
    func_800C56FC(&gCurrDisplayList, &gCurrHudMat, &gCurrHudVerts);
    func_800C5620(4);
    func_800C5494(4);
    if (func_800C0494(D_800DD404) != 0) {
        render_fade_transition(&gCurrDisplayList, &gCurrHudMat, &gCurrHudVerts);
    }
    if ((D_80123520 >= 8) && (func_8006F4C8() != 0)) {
        func_800829F8(&gCurrDisplayList, D_800DD404);
    }
    
    gDPFullSync(gCurrDisplayList++)
    gSPEndDisplayList(gCurrDisplayList++)
    
    func_80066610();
    if (D_800DD3F0 != 1) {
        if (D_800DD38C == 0) {
            D_800DD380 = func_80077A54();
        }
    } else {
        D_800DD3F0 = 0;
    }
    D_800DD38C = 0;
    clear_free_queue();
    if (!gIsPaused) {
        func_80066520();
    }
    if (D_800DD3F0 == 2) {
        phi_v0_2 = 320 * 240 * 2;
        if (osTvType == TV_TYPE_PAL) {
            phi_v0_2 = (s32)((320 * 240 * 2) * 1.1);
        }
        func_80070B04(gVideoLastFramebuffer, gVideoCurrFramebuffer, gVideoCurrFramebuffer + phi_v0_2);
    }
    
    temp = func_8007A98C(D_800DD380);
    D_800DD404 = temp;
    temp2 = 6;
    if (temp > temp2) {
        D_800DD404 = temp2;
    }
}

void func_8006CAE4(s32 arg0, s32 arg1, s32 arg2) {
    D_80123500 = arg0 - 1;
    if (arg1 == -1) {
        D_801234F4 = get_track_id_to_load();
    } else {
        D_801234F4 = arg1;
    }
    load_level_2(D_801234F4, D_80123500, D_80123504, arg2);
}

/**
 * Calls load_level() with the same arguments except for the cutsceneId, 
 * which is the value at D_80123508. Also does some other stuff.
 * Needs a better name!
 */
void load_level_2(s32 levelId, s32 numberOfPlayers, s32 entranceId, s32 vehicleId) {
    func_8006ECFC(numberOfPlayers);
    set_free_queue_state(0);
    func_80065EA0();
    func_800C3048();
    load_level(levelId, numberOfPlayers, entranceId, vehicleId, D_80123508);
    func_8009ECF0(get_viewport_count());
    func_800AE728(8, 0x10, 0x96, 0x64, 0x32, 0);
    func_8001BF20();
    osSetTime(0);
    set_free_queue_state(2);
    func_80072298(1);
}

void func_8006CC14(void) {
    set_free_queue_state(0);
    if (D_800DD38C == 0) {
        if (D_800DD3F0 != 1) {
            func_80077A54();
        }
        D_800DD38C = 1;
    }
    func_8006BEFC();
    func_800C01D8(&D_800DD3F4);
    func_800AE270();
    func_800A003C();
    func_800C30CC();
    gCurrDisplayList = gDisplayLists[D_801234E8];
    gDPFullSync(gCurrDisplayList++)
    gSPEndDisplayList(gCurrDisplayList++)
    set_free_queue_state(2);
}

#ifdef NON_MATCHING

void func_8006EC48(s32 arg0);
void func_8006F398(void);
void func_8006F42C(void);
void func_8006D8F0(s32 arg0);
void load_menu_with_level_background(s32 menuId, s32 levelId, s32 cutsceneId);

// Almost matching except for a couple minor issues.
void func_8006CCF0(s32 arg0) {
    s32 i, buttonHeldInputs, sp40, sp3C, buttonPressedInputs, phi_v1_2;
    
    sp40 = 0;
    buttonHeldInputs = 0;
    buttonPressedInputs = 0;
    
    for (i = 0; i < func_8009C3D8(); i++) {
        buttonHeldInputs |= get_buttons_held_from_player(i);
        buttonPressedInputs |= get_buttons_pressed_from_player(i);
    }
    if (D_800DD374) {
        buttonPressedInputs |= START_BUTTON;
    }
    if (!gIsPaused) {
        func_80010994(arg0);
        if (func_80066510() == 0 || func_8001139C()) {
            if ((buttonPressedInputs & START_BUTTON) && (func_8006C2F0() == 0) && (D_800DD390 == 0) 
                && (D_801234EC == 0) && (D_80123516 == 0) && (D_800DD394 == 0) && (D_800DD398 == 0)) {
                buttonPressedInputs = 0;
                gIsPaused = TRUE;
                func_80093A40();
            }
        }
    } else {
        func_80028FA0(1);
    }
    D_800DD398 -= arg0;
    if (D_800DD398 < 0) {
        D_800DD398 = 0;
    }
    if (D_80123516 != 0) {
        gIsPaused = FALSE;
    }
    gParticlePtrList_flush();
    func_8001BF20();
    func_80024D54(&gCurrDisplayList, &gCurrHudMat, &gCurrHudVerts, &gCurrHudTris, arg0);
    if (D_801234EC == 0) {
        // Ignore the user's L/R/Z buttons.
        buttonHeldInputs &= ~(L_TRIG | R_TRIG | Z_TRIG);
    }
    if (D_80123516 != 0) {
        i = func_80095728(&gCurrDisplayList, &gCurrHudMat, &gCurrHudVerts, arg0);
        switch (i - 1) {
            case 1:
                buttonHeldInputs |= (L_TRIG | Z_TRIG);
                break;
            case 0:
                D_80123516 = 0;
                func_8006D8F0(-1);
                break;
            case 3:
                func_8006C2E4();
                D_800DD390 = 0;
                buttonHeldInputs |= (L_TRIG | R_TRIG);
                break;
            // Issue with the below cases.
            case 4:
                sp40 = 1;
                buttonHeldInputs |= L_TRIG;
                break;
            case 7:
                sp40 = 2;
                buttonHeldInputs |= L_TRIG;
                break;
            case 8:
                sp40 = 3;
                buttonHeldInputs |= L_TRIG;
                break;
            case 9:
                sp40 = 4;
                buttonHeldInputs |= L_TRIG;
                break;
            case 10:
                sp40 = 5;
                buttonHeldInputs |= L_TRIG;
                break;
            case 11:
                sp40 = 6;
                buttonHeldInputs |= L_TRIG;
                break;
            case 12:
                sp40 = 7;
                buttonHeldInputs |= L_TRIG;
                break;
        }
    }
    func_800C3440(arg0);
    i = func_800C3400();
    if (i != 0) {
        if (i == 2) {
            gIsPaused = TRUE;
        }
        if (func_800C3400() != 2) {
            gIsPaused = FALSE;
            n_alSeqpDelete();
        }
    }
    if (gIsPaused) {
        i = func_80094170(&gCurrDisplayList, arg0);
        switch (i - 1) {
        case 0:
            gIsPaused = FALSE;
            break;
        case 1:
            func_80001050();
            func_800C314C();
            if (func_80023568() != 0 && is_in_two_player_adventure()) {
                func_8006F398();
            }
            buttonHeldInputs |= (L_TRIG | R_TRIG);
            break;
        case 2:
            func_80001050();
            func_800C314C();
            if (func_80023568() != 0 && is_in_two_player_adventure()) {
                func_8006F398();
            }
            buttonHeldInputs |= L_TRIG;
            break;
        case 4:
            sp40 = 1;
            func_800C314C();
            buttonHeldInputs |= L_TRIG;
            break;
        case 11:
            sp40 = 6;
            func_800C314C();
            buttonHeldInputs |= L_TRIG;
            break;
        case 5:
            gIsPaused = FALSE;
            break;
        case 6:
            func_80022E18(1);
            gIsPaused = FALSE;
            break;
        case 3:
            D_800DD390 = 0;
            func_80001050();
            func_800C314C();
            func_8006C2E4();
            buttonHeldInputs |= (L_TRIG | R_TRIG);
            break;
        }
    }
    func_80078054(&gCurrDisplayList);
    render_borders_for_multiplayer(&gCurrDisplayList);
    func_800A8474(&gCurrDisplayList, &gCurrHudMat, &gCurrHudVerts, arg0);
    func_80077268(&gCurrDisplayList);
    if (D_800DD39C != 0) {
        if (func_800214C4() != 0) {
            D_801234F4 = 0x23;
            D_801234F8 = 1;
            D_80123504 = 0;
            D_800DD39C = 0;
        }
    }
    phi_v1_2 = FALSE;
    if (D_800DD390 != 0) {
        D_800DD390 -= arg0;
        if (D_800DD390 <= 0) {
            D_800DD390 = 0;
            func_8006C1AC(0, 0, 0, 0);
            func_8006C1AC(0x2B, 0, -1, 0xA);
            phi_v1_2 = TRUE;
        }
    }
    if (D_800DD394 > 0) {
        D_800DD394 -= arg0;
        if (D_800DD394 <= 0) {
            buttonHeldInputs = L_TRIG;
            switch(D_80123524) {
                case 1:
                    buttonHeldInputs = (L_TRIG | Z_TRIG);
                    break;
                case 2:
                    sp40 = 3;
                    sp3C = 1;
                    func_80098208();
                    D_801234FC = 2;
                    break;
                case 3:
                    D_800DD39C = 1;
                    // fall-through
                case 4:
                    D_801234F8 = 1;
                    D_801234F4 = D_80123525;
                    D_80123504 = 0;
                    D_80123508 = 0;
                    buttonHeldInputs = 0;
                    break;
            }
            D_80123524 = 0;
            D_800DD394 = 0;
        }
    }
    if (phi_v1_2) {
        if (func_8006C2F0() != 0) {
            func_8006C22C(&D_801234F4, &D_80123504, &i, &D_80123508);
            func_8006F42C();
            if (D_801234F4 < 0) {
                if (D_801234F4 == -1 || D_801234F4 == -10) {
                    if (D_801234F4 == -10 && is_in_two_player_adventure()) {
                        func_8006F398();
                    }
                    buttonHeldInputs |= L_TRIG;
                    D_801234FC = 2;
                } else {
                    buttonHeldInputs = 0;
                    D_801234FC = 1;
                    sp40 = 8;
                }
            } else {
                D_801234FC = 0;
                D_801234F8 = 1;
                buttonHeldInputs = 0;
            }
        }
    } else {
        sp3C = func_8006C300();
        if (func_8006C2F0() != 0) {
            if (D_800DD394 == 0) {
                // Minor issue here.
                if ((func_800214C4() != 0) || ((buttonPressedInputs & A_BUTTON) && (sp3C != 0))) {
                    if (sp3C != 0) {
                        func_80000B28();
                    }
                    func_8006F42C();
                    func_8006C22C(&D_801234F4, &D_80123504, &i, &D_80123508);
                    if (D_801234F4 < 0) {
                        if (D_801234F4 == -1 || D_801234F4 == -10) {
                            if (D_801234F4 == -10 && is_in_two_player_adventure()) {
                                func_8006F398();
                            }
                            buttonHeldInputs |= L_TRIG;
                            D_801234FC = 2;
                        } else {
                            buttonHeldInputs = 0;
                            D_801234FC = 1;
                            sp40 = 8;
                        }
                    } else {
                        D_801234F8 = 1;
                    }
                }
            }
        }
    }
    if (((buttonHeldInputs & L_TRIG) && (D_801234EC == 0)) || (D_801234FC != 0)) {
        gIsPaused = FALSE;
        D_800DD394 = 0;
        D_80123516 = 0;
        func_8006CC14();
        func_8006EC48(get_save_file_index());
        if (sp40 != 0) {
            D_80123514 = FALSE;
            switch (sp40) {
                case 1:
                    // Go to track select menu from "Select Track" option in tracks menu.
                    load_menu_with_level_background(MENU_TRACK_SELECT, -1, 1);
                    break;
                case 2:
                    load_menu_with_level_background(MENU_RESULTS, 0x22, 0);
                    break;
                case 3:
                    load_menu_with_level_background(MENU_TROPHY_RACE_ROUND, 0x22, 0);
                    break;
                case 4:
                    load_menu_with_level_background(MENU_TROPHY_RACE_RANKINGS, 0x22, 0);
                    break;
                case 5:
                    // Trophy race related?
                    load_menu_with_level_background(MENU_UNUSED_22, 0x22, 0);
                    break;
                case 6: 
                    // Go to character select menu from "Select Character" option in tracks menu.
                    i = 0;
                    if (is_drumstick_unlocked() != 0) {
                        i ^= 1;
                    }
                    if (is_tt_unlocked() != 0) {
                        i ^= 3;
                    }
                    func_8008AEB4(1, 0);
                    load_menu_with_level_background(MENU_CHARACTER_SELECT, 0x16, i);
                    break;
                case 7:
                    D_80123514 = TRUE;
                    load_menu_with_level_background(MENU_UNKNOWN_23, -1, 0);
                    D_80123514 = FALSE;
                    break;
                case 8:
                    load_menu_with_level_background(MENU_CREDITS, -1, 0);
                    break;
            }
        } else if (D_801234FC == 1) {
            if (D_80121250[2] == -1) {
                load_menu_with_level_background(MENU_UNUSED_8, -1, 0);
            } else {
                D_80123514 = TRUE;
                load_menu_with_level_background(MENU_UNKNOWN_5, -1, -1);
            }
        } else if (!(buttonHeldInputs & R_TRIG)) {
            if (!(buttonHeldInputs & Z_TRIG)) {
                D_801234F4 = D_80121250[0];
                D_80123504 = D_80121250[15];
                D_80123508 = D_80121250[D_80121250[1] + 8];
                D_80123518 = func_8006B0AC(D_801234F4);
                if (D_80123508 < 0) {
                    D_80123508 = 0x64;
                }
            }
            load_level_2(D_801234F4, D_80123500, D_80123504, D_80123518);
        } else {
            func_8006EC48(get_save_file_index());
            load_menu_with_level_background(MENU_TITLE, -1, 0);
        }
        D_801234FC = 0;
    }
    if (D_801234F8 != 0) {
        D_80123516 = 0;
        func_8006CC14();
        load_level_2(D_801234F4, D_80123500, D_80123504, D_80123518);
        func_8006EC48(get_save_file_index());
        D_801234F8 = 0;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_06B2B0/func_8006CCF0.s")
#endif

void func_8006D8A4(void) {
    D_800DD390 = 0x2C;
    gIsPaused = 0;
    n_alSeqpDelete();
    func_800C01D8(&D_800DD408);
}

void func_8006D8E0(s32 arg0) {
    D_80123516 = arg0 + 1;
}

void func_8006D8F0(s32 arg0) {
    s32 temp;
    if (D_801234EC != 4) {
        D_801234F4 = D_80121250[0];
        D_80123504 = 0;
        D_80123508 = 0x64;
        temp = D_80121250[1];
        if (D_80121250[15] >= 0) {
            D_80123504 = D_80121250[15];
        }
        if (D_80121250[temp + 8] >= 0) {
            D_80123508 = D_80121250[temp + 8];
        }
        D_801234F8 = 1;
    }
}

void func_8006D968(s8 *arg0) {
    s32 i;
    if (D_801234EC != 4) {
        D_80121250[0] = D_801234F4;
        for(i = 0; i < 2; i++) {
            D_80121250[i + 2] = arg0[i + 8];
            D_80121250[i + 4] = arg0[i + 10];
            D_80121250[i + 6] = arg0[i + 12];
            D_80121250[i + 8] = arg0[i + 14];
            D_80121250[i + 10] = arg0[i + 18];
            D_80121250[i + 12] = arg0[i + 20];
        }
        D_80121250[14] = arg0[22];
        D_80121250[15] = arg0[23];
        D_801234FC = 1;
    }
}

s32 func_8006DA0C(void) {
    return D_801234EC;
}

/* Unused? */
void func_8006DA1C(s32 arg0) {
    D_801234EC = arg0;
}

void load_menu_with_level_background(s32 menuId, s32 levelId, s32 cutsceneId) {
    func_8006ECFC(0);
    D_801234EC = 1;
    D_801234F0 = 1;
    func_80004A60(0, 0x7FFF);
    func_80004A60(1, 0x7FFF);
    func_80004A60(2, 0x7FFF);
    func_80065EA0();
    
    if (!D_80123514) {
        D_80123514 = FALSE;
        if (levelId < 0) {
            D_80123514 = TRUE;
        } else {
            load_level_3(levelId, -1, 0, 2, cutsceneId);
        }
    }
    if (menuId == MENU_UNUSED_2 || menuId == MENU_LOGOS || menuId == MENU_TITLE) {
        func_800813C0();
    }
    menu_init(menuId);
    D_80123504 = 0;
}

void func_8006DB14(s32 arg0) {
    D_80123518 = arg0;
}

void func_8006DB20(s32 arg0) {
    D_8012351C = arg0;
}

s32 func_8006DB2C(void) {
    return D_80123518;
}

/**
 * Calls load_level() with the same arguments, but also does some other stuff.
 * Needs a better name!
 */
void load_level_3(s32 levelId, s32 numberOfPlayers, s32 entranceId, s32 vehicleId, s32 cutsceneId) {
    set_free_queue_state(0);
    func_80065EA0();
    func_800C3048();
    load_level(levelId, numberOfPlayers, entranceId, vehicleId, cutsceneId);
    func_8009ECF0(get_viewport_count());
    func_800AE728(4, 4, 0x6E, 0x30, 0x20, 0);
    func_8001BF20();
    osSetTime(0);
    set_free_queue_state(2);
}

void func_8006DBE4(void) {
    if (!D_80123514) {
        D_80123514 = TRUE;
        set_free_queue_state(0);
        func_8006BEFC();
        func_800C01D8(&D_800DD3F4);
        func_800AE270();
        func_800A003C();
        func_800C30CC();
        set_free_queue_state(2);
    }
    D_80123514 = FALSE;
}

void func_8006DC58(s32 arg0) {
    if (get_thread30_level_id_to_load() == 0) {
        func_80010994(arg0);
        gParticlePtrList_flush();
        func_8001BF20();
        func_80024D54(&gCurrDisplayList, &gCurrHudMat, &gCurrHudVerts, &gCurrHudTris, arg0);
        func_800C3440(arg0);
        func_80078054(&gCurrDisplayList);
        render_borders_for_multiplayer(&gCurrDisplayList);
        func_80077268(&gCurrDisplayList);
    }
}

#ifdef NON_MATCHING
// Minor & regalloc issues.
void func_8006DCF8(s32 arg0) {
    s32 menuLoopResult, temp, temp2, tempResult;
    
    gIsPaused = FALSE;
    D_80123516 = 0;
    if (!D_80123514 && D_801234F0) {
        func_8006DC58(arg0);
    }
    menuLoopResult = menu_loop(&gCurrDisplayList, &gCurrHudMat, &gCurrHudVerts, &gCurrHudTris, arg0);
    D_801234F0 = TRUE;
    if (menuLoopResult == -2) {
        D_801234F0 = FALSE;
        return;
    }
    if ((menuLoopResult != -1) && (menuLoopResult & 0x200)) {
        func_8006DBE4();
        gCurrDisplayList = gDisplayLists[D_801234E8];
        gDPFullSync(gCurrDisplayList++)
        gSPEndDisplayList(gCurrDisplayList++)
        D_801234F4 = menuLoopResult & 0x7F;
        D_80123518 = func_8006B0AC(D_801234F4);
        D_80123504 = 0;
        D_80123508 = 0x64;
        D_801234EC = 0;
        gIsPaused = FALSE;
        D_80123516 = 0;
        load_level_2(D_801234F4, D_80123500, D_80123504, D_80123518);
        func_8006EC48(get_save_file_index());
        return;
    }
    if ((menuLoopResult != -1) && (menuLoopResult & 0x100)) {
        func_8006CC14();
        gIsPaused = FALSE;
        D_80123516 = 0;
        switch (menuLoopResult & 0x7F) {
            case 5:
                load_menu_with_level_background(MENU_TRACK_SELECT, -1, 1);
                break;
            case 14:
                D_801234F4 = 0;
                D_80123504 = 0;
                D_80123508 = 0x64;
                D_801234EC = 0;
                load_level_2(D_801234F4, D_80123500, D_80123504, D_80123518);
                func_8006EC48(get_save_file_index());
                break;
            case 1:
                D_80123504 = 0;
                D_80123508 = 0x64;
                D_801234F4 = D_80121250[0];
                D_801234EC = 0;
                // Minor issue with these 2 if statements
                temp2 = D_80121250[D_80121250[1] + 8];
                temp = D_80121250[15];
                if (temp >= 0) {
                    D_80123504 = temp;
                }
                if (temp2 >= 0) {
                    D_80123508 = temp2;
                }
                load_level_2(D_801234F4, D_80123500, D_80123504, D_80123518);
                func_8006EC48(get_save_file_index());
                break;
            case 2:
                D_801234EC = 0;
                load_level_2(D_801234F4, D_80123500, D_80123504, D_80123518);
                break;
            case 3:
                D_801234EC = 0;
                D_801234F4 = D_80121250[0];
                D_80123504 = D_80121250[15];
                D_80123508 = D_80121250[D_80121250[1] + 8];
                D_80123518 = func_8006B0AC(D_801234F4);
                load_level_2(D_801234F4, D_80123500, D_80123504, D_80123518);
                break;
            default:
                load_menu_with_level_background(MENU_TITLE, -1, 0);
                break;
        }
        return;
    }
    if ((menuLoopResult & 0x80) && (menuLoopResult != -1)) {
        func_8006DBE4();
        // Minor issue here.
        gCurrDisplayList = gDisplayLists[D_801234E8];
        gDPFullSync(gCurrDisplayList++)
        gSPEndDisplayList(gCurrDisplayList++)
        temp = menuLoopResult & 0x7F;
        D_80121250[1] = temp;
        D_80121250[0] = D_801234F4;
        D_801234F4 = D_80121250[temp + 2];
        D_80123504 = D_80121250[temp + 4];
        D_801234EC = 0;
        D_80123508 = D_80121250[temp + 12];
        temp = get_player_selected_vehicle(0);
        D_80123500 = gSettingsPtr->gObjectCount - 1;
        load_level_2(D_801234F4, D_80123500, D_80123504, temp);
        D_801234FC = 0;
        D_80123518 = D_8012351C;
        return;
    }
    if (menuLoopResult > 0) {
        func_8006DBE4();
        gCurrDisplayList = gDisplayLists[D_801234E8];
        gDPFullSync(gCurrDisplayList++)
        gSPEndDisplayList(gCurrDisplayList++)
        D_801234EC = 0;
        func_8006CAE4(menuLoopResult, -1, D_80123518);
        if (gSettingsPtr->newGame && !is_in_tracks_mode()) {
            func_80000B28();
            gSettingsPtr->newGame = FALSE;
        }
    }
}

#else
GLOBAL_ASM("asm/non_matchings/unknown_06B2B0/func_8006DCF8.s")
#endif

void load_level_for_menu(s32 levelId, s32 numberOfPlayers, s32 cutsceneId) {
    if (!D_80123514) {
        func_8006DBE4();
        if (get_thread30_level_id_to_load() == 0) {
            gCurrDisplayList = gDisplayLists[D_801234E8];
            gDPFullSync(gCurrDisplayList++)
            gSPEndDisplayList(gCurrDisplayList++)
        }
    }
    if (levelId != -1) {
        load_level_3(levelId, numberOfPlayers, 0, 2, cutsceneId);
        D_80123514 = FALSE;
        return;
    }
    D_80123514 = TRUE;
}

void calc_and_alloc_heap_for_settings(void) {
    s32 dataSize;
    u32 sizes[15];
    s32 numWorlds, numLevels;
    
    func_8006A6B0();
    reset_character_id_slots();
    get_number_of_levels_and_worlds(&numLevels, &numWorlds);
    sizes[0] = sizeof(Settings);
    sizes[1] = sizes[0] + (numLevels * 4); // balloonsPtr
    sizes[2] = sizes[1] + (numWorlds * 2); // flapInitialsPtr[0]
    dataSize = (numLevels * 2);
    sizes[3] = sizes[2] + dataSize; // flapInitialsPtr[1]
    sizes[4] = sizes[3] + dataSize; // flapInitialsPtr[2]
    sizes[5] = sizes[4] + dataSize; // flapTimesPtr[0]
    sizes[6] = sizes[5] + dataSize; // flapTimesPtr[1]
    sizes[7] = sizes[6] + dataSize; // flapTimesPtr[2]
    sizes[8] = sizes[7] + dataSize; // courseInitialsPtr[0]
    sizes[9] = sizes[8] + dataSize; // courseInitialsPtr[1]
    sizes[10] = sizes[9] + dataSize; // courseInitialsPtr[2]
    sizes[11] = sizes[10] + dataSize; // courseTimesPtr[0]
    sizes[12] = sizes[11] + dataSize; // courseTimesPtr[1]
    sizes[13] = sizes[12] + dataSize; // courseTimesPtr[2]
    sizes[14] = sizes[13] + dataSize; // total size
    
    gSettingsPtr = allocate_from_main_pool_safe(sizes[14], COLOR_TAG_WHITE);
    gSettingsPtr->courseFlagsPtr = (u8*)gSettingsPtr + sizes[0];
    gSettingsPtr->balloonsPtr = (u8*)gSettingsPtr + sizes[1];
    gSettingsPtr->tajFlags = 0;
    gSettingsPtr->flapInitialsPtr[0] = (u8*)gSettingsPtr + sizes[2];
    gSettingsPtr->flapInitialsPtr[1] = (u8*)gSettingsPtr + sizes[3];
    gSettingsPtr->flapInitialsPtr[2] = (u8*)gSettingsPtr + sizes[4];
    gSettingsPtr->flapTimesPtr[0] = (u8*)gSettingsPtr + sizes[5];
    gSettingsPtr->flapTimesPtr[1] = (u8*)gSettingsPtr + sizes[6];
    gSettingsPtr->flapTimesPtr[2] = (u8*)gSettingsPtr + sizes[7];
    gSettingsPtr->courseInitialsPtr[0] = (u8*)gSettingsPtr + sizes[8];
    gSettingsPtr->courseInitialsPtr[1] = (u8*)gSettingsPtr + sizes[9];
    gSettingsPtr->courseInitialsPtr[2] = (u8*)gSettingsPtr + sizes[10];
    gSettingsPtr->courseTimesPtr[0] = (u8*)gSettingsPtr + sizes[11];
    gSettingsPtr->courseTimesPtr[1] = (u8*)gSettingsPtr + sizes[12];
    gSettingsPtr->courseTimesPtr[2] = (u8*)gSettingsPtr + sizes[13];
    gSettingsPtr->unk4C = &D_80121250;
    D_800DD37C = 263;
}

void func_8006E5BC(void) {
    s32 i, j;
    gSettingsPtr->gObjectCount = get_number_of_active_players();
    for (i = 0; i < 8; i++) {
        gSettingsPtr->racers[i].best_times = 0;
        gSettingsPtr->racers[i].character = get_character_id_from_slot(i);
        if (gSettingsPtr->gObjectCount >= 2) {
            gSettingsPtr->racers[i].starting_position = i;
        } else if (is_in_two_player_adventure()) {
            gSettingsPtr->racers[i].starting_position = 5 - i;
        } else {
            gSettingsPtr->racers[i].starting_position = 7 - i;
        }
        gSettingsPtr->racers[i].unk7 = 0;
        for(j = 0; j < 4; j++) {
            gSettingsPtr->racers[i].placements[j] = 0;
        }
        gSettingsPtr->racers[i].course_time = 0;
        for(j = 0; j < 3; j++) {
            gSettingsPtr->racers[i].lap_times[j] = 0;
        }
    }
    gSettingsPtr->timeTrialRacer = 0;
    gSettingsPtr->unk115[0] = 0;
    gSettingsPtr->unk115[1] = 0;
    gSettingsPtr->display_times = 0;
    gSettingsPtr->worldId = 0;
    gSettingsPtr->courseId = 0;
}

void func_8006E770(Settings *settings, s32 arg1) {
    s32 i, j;
    s32 numWorlds, numLevels;
    s32 index;
    u16 *temp_v0;
    
    get_number_of_levels_and_worlds(&numLevels, &numWorlds);
    temp_v0 = (u16*)get_misc_asset(0x17);
    for (i = 0; i < 3; i++) { // 3 = number of save files?
        for(j = 0; j < numLevels; j++) {
            index = (j * 12) + (i * 4);
            if (arg1 & 1) {
                settings->flapInitialsPtr[i][j] = temp_v0[index + 3];
                settings->flapTimesPtr[i][j] = temp_v0[index + 2];
            }
            if (arg1 & 2) {
                settings->courseInitialsPtr[i][j] = temp_v0[index + 1];
                settings->courseTimesPtr[i][j] = temp_v0[index];
            }
        }
    }
}

void func_8006E994(Settings *settings) {
    s32 i;
    s32 sp20;
    s32 sp1C;

    get_number_of_levels_and_worlds(&sp1C, &sp20);
    settings->newGame = 1;
    
    for (i = 0; i < sp20; i++) {
        settings->balloonsPtr[i] = 0;
    }
    for(i = 0; i < sp1C; i++) {
        settings->courseFlagsPtr[i] = 0;
    }
    
    settings->keys = 0;
    settings->unkA = 0;
    settings->bosses = 0;
    settings->trophies = 0;
    settings->cutsceneFlags = 0;
    settings->tajFlags = 0;
    settings->ttAmulet = 0;
    settings->wizpigAmulet = 0;
}

// Unused?
void func_8006EA58(void) {
    func_8006E770(gSettingsPtr, 3);
    func_8006E994(gSettingsPtr);
}

Settings *get_settings(void) {
    return gSettingsPtr;
}

/**
 * Returns the value in gIsPaused.
 */
s8 is_game_paused(void) {
    return gIsPaused;
}

s8 func_8006EAB0(void) {
    return D_80123516;
}

s32 func_8006EAC0(void) {
    if (D_80123560[0] == 0) {
        D_80123560[0] = (s32) ((osRecvMesg(&D_80123548, NULL, 0) + 1) != 0);
    }
    return D_80123560[0];
}

s32 func_8006EB14(void) {
    return D_801234F4;
}

/* Unused? */
void func_8006EB24(void) {
    D_800DD37C |= 0x01;
}

/* Unused? */
void func_8006EB40(void) {
    D_800DD37C |= 0x02;
}

void func_8006EB5C(void) {
    D_800DD37C |= 0x03;
}

void func_8006EB78(s32 arg0) {
    D_800DD37C &= -0x301;
    D_800DD37C |= (0x04 | ((arg0 & 3) << 8));
}

void func_8006EBA8(void) {
    D_800DD37C |= 0x08;
}

void func_8006EBC4(void) {
    D_800DD37C |= 0x10;
}

void func_8006EBE0(void) {
    D_800DD37C |= 0x20;
}

void func_8006EBFC(void) {
    D_800DD37C |= 0x30;
}

void func_8006EC18(s32 arg0) {
    D_800DD37C &= -0xC01;
    D_800DD37C |= (0x40 | ((arg0 & 3) << 0xA));
}

void func_8006EC48(s32 arg0) {
    if (D_801234EC == 0 && !is_in_tracks_mode()) {
        D_800DD37C &= -0xC01;
        D_800DD37C |= (0x40 | ((arg0 & 3) << 0xA));
    }
}

void func_8006ECAC(s32 arg0) {
    D_800DD37C = ((arg0 & 0x03) << 10) | 0x80;
}

/* Unused? */
void func_8006ECC4(void) {
    D_800DD37C |= 0x100;
}

void func_8006ECE0(void) {
    D_800DD37C |= 0x200;
}

GLOBAL_ASM("asm/non_matchings/unknown_06B2B0/func_8006ECFC.s")

s32 func_8006EFB8(void) {
    // Have to use literal here for this function to match.
    if (*((s32*)0xA4000000) != -1) {
        return 0;
    }
    return 1;
}

#ifdef NON_MATCHING

// Not close to matching, but should be the same functionality-wise.
void func_8006EFDC(void) {
    s32 size1, size2, size3, size4, totalSize;

    D_8012350C = 3;
    
    size1 = (gNumF3dCmdsPerPlayer[3] * sizeof(Gwords));
    size2 = (gNumHudMatPerPlayer[3] * sizeof(Mtx));
    size3 = (gNumHudVertsPerPlayer[3] * sizeof(Vertex));
    size4 = (gNumHudTrisPerPlayer[3] * sizeof(Triangle));
    totalSize = size1 + size2 + size3 + size4;
    
    gDisplayLists[0] = (u8*)allocate_from_main_pool_safe(totalSize, COLOR_TAG_RED);
    gHudMatrices[0] = (u8*)gDisplayLists[0] + size1;
    gHudVertices[0] = (u8*)gHudMatrices[0] + size2;
    gHudTriangles[0] = (u8*)gHudVertices[0] + size3;
    
    gDisplayLists[1] = (u8*)allocate_from_main_pool_safe(totalSize, COLOR_TAG_YELLOW);
    gHudMatrices[1] = (u8*)gDisplayLists[1] + size1;
    gHudVertices[1] = (u8*)gHudMatrices[1] + size2;
    gHudTriangles[1] = (u8*)gHudVertices[1] + size3;
    
    gCurrNumF3dCmdsPerPlayer = gNumF3dCmdsPerPlayer[3];
    gCurrNumHudMatPerPlayer = gNumHudMatPerPlayer[3];
    gCurrNumHudTrisPerPlayer = gNumHudTrisPerPlayer[3];
    gCurrNumHudVertsPerPlayer = gNumHudVertsPerPlayer[3];
}
#else
GLOBAL_ASM("asm/non_matchings/unknown_06B2B0/func_8006EFDC.s")
#endif

void func_8006F140(s32 arg0) {
    if (D_800DD394 == 0) {
        D_800DD394 = 0x28;
        D_80123524 = 0;
        D_80123526 = 0;
        if (arg0 == 1) {
            func_800C01D8(&D_800DD41C);
        }
        if (arg0 == 3) {
            D_800DD394 = 0x11A;
            func_800C01D8(&D_800DD424);
        }
        if (arg0 == 4) {
            D_800DD394 = 0x168;
            func_800C01D8(&D_800DD424);
        }
        if (arg0 == 0) {
            D_800DD394 = 2;
        }
    }
}

// Unused?
void func_8006F20C(void) {
    if (D_800DD394 == 0) {
        func_800C01D8(&D_800DD41C);
        D_800DD394 = 0x28;
        D_80123524 = 1;
    }
}

void func_8006F254(void) {
    if (D_800DD394 == 0) {
        func_800C01D8(&D_800DD41C);
        D_800DD394 = 0x28;
        D_80123524 = 2;
    }
}

void func_8006F29C(void) {
    if (D_800DD394 == 0) {
        if ((gSettingsPtr->trophies & 0xFF) == 0xFF && !(gSettingsPtr->cutsceneFlags & 1) && gSettingsPtr->bosses & 1) {
            gSettingsPtr->cutsceneFlags |= 1;
            func_800C01D8(&D_800DD41C);
            D_800DD394 = 0x28;
            D_80123525 = 0x2D;
            D_80123524 = 3;
        }
    }
}

void func_8006F338(s32 arg0) {
    if (D_800DD394 == 0) {
        D_80123525 = arg0;
        func_800C01D8(&D_800DD41C);
        D_800DD394 = 0x28;
        D_80123524 = 4;
    }
}

void func_8006F388(u8 arg0) {
    D_800DD398 = arg0;
}

void func_8006F398(void) {
    s32 i;
    u8 temp;
    u8 *first_racer_data;
    u8 *second_racer_data;

    func_8006A50C();
    func_8000E194();
    
    first_racer_data = (u8*)(gSettingsPtr->racers);
    second_racer_data = (u8*)(gSettingsPtr->racers + 1);
    
    for(i = 0; i < sizeof(Racer); i++) {
        temp = first_racer_data[i];
        first_racer_data[i] = second_racer_data[i];
        second_racer_data[i] = temp;
    }
}

void func_8006F42C(void) {
    D_800DD3F0 = 2;
}

void func_8006F43C(void) {
    s32 i;
    s32 buttonInputs = 0;
    
    for(i = 0; i < MAXCONTROLLERS; i++) {
        buttonInputs |= get_buttons_held_from_player(i);
    }
    if (buttonInputs & START_BUTTON) {
        gShowControllerPakMenu = TRUE;
    }
    D_80123520++;
    if (D_80123520 >= 8) {
        load_menu_with_level_background(MENU_BOOT, 0x27, 2);
    }
}

s32 func_8006F4C8(void) {
    if (D_800DD384 == -1) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_8006F4EC(void) {
    // Have to use a literal here for the function to match.
    if (*((s32*)0xA4001000) != 0x17D7) {
        return 0;
    }
    return 1;
}
