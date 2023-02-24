/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8006A6B0 */

#include "game.h"

#include <PR/os_cont.h>
#include <PR/gu.h>
#include <PR/os_time.h>
#include "memory.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "asset_enums.h"
#include "asset_loading.h"
#include "menu.h"
#include "video.h"
#include "set_rsp_segment.h"
#include "gzip.h"
#include "printf.h"
#include "thread0_epc.h"
#include "thread30_track_loading.h"
#include "weather.h"
#include "audio.h"
#include "objects.h"
#include "camera.h"
#include "save_data.h"
#include "unknown_078050.h"
#include "audiosfx.h"
#include "audiomgr.h"
#include "unknown_032760.h"
#include "textures_sprites.h"
#include "PR/os_internal.h"
#include "printf.h"
#include "fade_transition.h"
#include "borders.h"
#include "unknown_008C40.h"
#include "unknown_0255E0.h"
#include "game_text.h"
#include "game_ui.h"
#include "main.h"
#include "object_models.h"
#include "racer.h"
#include "particles.h"
#include "math_util.h"
#include "controller.h"

/************ .rodata ************/

UNUSED const char sLevelErrorString[] = "LOADLEVEL Error: Level out of range\n";
UNUSED const char sBossErrorString[] = "BossLev problem\n";
UNUSED const char sAITableErrorString[] = "AITABLE Error: Table out of range\n";
UNUSED const char sDebugVersionInfoString[] = "1.1605";
UNUSED const char sDebugBuildDateString[] = "02/10/97 16:03";
UNUSED const char sDebugUsernameString[] = "pmountain";

const char D_800E7134[] = "BBB\n"; // Functionally unused.
UNUSED const char sDebugCarString[] = "CAR";
UNUSED const char sDebugHovercraftString[] = "HOV";
UNUSED const char sDebugPlaneString[] = "PLN";
UNUSED const char sDebugVehicleSwapString[] = "Swapping\n";

/*********************************/

/************ .data ************/

char *D_800DD310 = NULL; // Currently unknown, might be a different type.
s8 gCurrentDefaultVehicle = -1;
u8 D_800DD318 = 0;
s32 gIsInRace = 0;

// Updated automatically from calc_func_checksums.py
s32 gFunc80068158Checksum = 0x585E;
s32 gFunc80068158Length = 0x154;

s16 D_800DD328 = 0;
s16 D_800DD32C = 0;

s8 D_800DD330 = 0;

UNUSED char *sDebugRomBuildInfo[6] = {
    NULL, NULL, NULL, // These could be a file boundary.
    (char *)sDebugVersionInfoString,
    (char *)sDebugBuildDateString,
    (char *)sDebugUsernameString
};

UNUSED char gBuildString[40] = "Version 7.7 29/09/97 15.00 L.Schuneman";

s8 sAntiPiracyTriggered = 0;
UNUSED s32 D_800DD378 = 1;
s32 gSaveDataFlags = 0;
s32 gScreenStatus = OSMESG_SWAP_BUFFER;
s32 sControllerStatus = 0;
UNUSED s32 D_800DD388 = 0;
s8 gSkipGfxTask = FALSE;
s8 D_800DD390 = 0;
s16 gLevelLoadTimer = 0;
s8 D_800DD398 = 0;
s8 D_800DD39C = 0;
s8 gDmemInvalid = FALSE;
UNUSED s32 D_800DD3A4 = 0;
UNUSED s32 D_800DD3A8 = 0;
UNUSED s32 D_800DD3AC = 0;
s32 gNumF3dCmdsPerPlayer[4] = { 4500, 7000, 11000, 11000 };
s32 gNumHudVertsPerPlayer[4] = { 300, 600, 850, 900 };
s32 gNumHudMatPerPlayer[4] = { 300, 400, 550, 600 };
s32 gNumHudTrisPerPlayer[4] = { 20, 30, 40, 50 };
s8 gDrawFrameTimer = 0;
FadeTransition D_800DD3F4 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_UNK2, FADE_COLOR_BLACK, 20, 0);
UNUSED FadeTransition D_800DD3FC = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_WHITE, 20, -1);
s32 sLogicUpdateRate = LOGIC_5FPS;
FadeTransition D_800DD408 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_WHITE, 30, -1);
UNUSED char *D_800DD410[3] = {
    (char *)sDebugCarString, (char *)sDebugHovercraftString, (char *)sDebugPlaneString
};
FadeTransition D_800DD41C = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 30, -1);
FadeTransition D_800DD424 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 260, -1);
/*******************************/

/************ .bss ************/

s32 *gTempAssetTable;
s32 gMapId;
LevelHeader *gCurrentLevelHeader;
char **gLevelNames;
s32 gNumberOfLevelHeaders;
s32 gNumberOfWorlds;

s8 *D_80121178;
unk8012117C *D_8012117C;

s32 D_80121180[16];

TempStruct5 *D_801211C0;
s16 D_801211C8[20];
Gfx *gDisplayLists[2];
Gfx *gCurrDisplayList;
UNUSED s32 D_801211FC;
MatrixS *gHudMatrices[2];
MatrixS *gGameCurrMatrix;
Vertex *gHudVertices[2];
Vertex *gGameCurrVertexList;
TriangleList *gHudTriangles[2];
TriangleList *gGameCurrTriList;
UNUSED s32 D_80121230[8];
s8 D_80121250[16]; //Settings4C
OSSched gMainSched; // 0x288 / 648 bytes
u64 gSchedStack[0x400];
s32 gSPTaskNum;
s32 sRenderContext;
s32 D_801234F0;
// Similar to gMapId, but is 0 if not currently playing a level (e.g. start menu).
s32 gPlayableMapId;
s32 D_801234F8;
s32 D_801234FC;
s32 D_80123500;
s32 D_80123504;
s32 D_80123508;
s32 D_8012350C;
Settings *gSettingsPtr;
s8 gIsLoading;
s8 gIsPaused;
s8 gPostRaceViewPort;
Vehicle gLevelDefaultVehicleID;
Vehicle D_8012351C; // Looks to be the current level's vehicle ID.
s32 sBootDelayTimer;
s8 D_80123524;
s8 D_80123525;
UNUSED s8 D_80123526; // Set to 0 then never used.
s32 gCurrNumF3dCmdsPerPlayer;
s32 gCurrNumHudMatPerPlayer;
s32 gCurrNumHudTrisPerPlayer;
s32 gCurrNumHudVertsPerPlayer;
OSScClient *gNMISched[3];
OSMesg gNMIOSMesg;
OSMesgQueue gNMIMesgQueue;
s32 gNMIMesgBuf[8];

/******************************/

void func_8006A6B0(void) {
    s32 i;
    s32 temp;
    UNUSED s32 pad;
    s32 checksumCount;
    u8 *header;
    s32 j;
    header = allocate_from_main_pool_safe(sizeof(LevelHeader), COLOUR_TAG_YELLOW);
    gTempAssetTable = (s32 *) load_asset_section_from_rom(ASSET_LEVEL_HEADERS_TABLE);
    i = 0;
    while (i < 16) {
        D_80121180[i++] = 0;
    }
    gNumberOfLevelHeaders = 0;
    while (gTempAssetTable[gNumberOfLevelHeaders] != -1) {
        gNumberOfLevelHeaders++;
    }
    gNumberOfLevelHeaders--;
    D_8012117C = allocate_from_main_pool_safe(gNumberOfLevelHeaders * sizeof(unk8012117C), COLOUR_TAG_YELLOW);
    gCurrentLevelHeader = (LevelHeader *) header;
    gNumberOfWorlds = -1;
    for (i = 0; i < gNumberOfLevelHeaders; i++) {
        load_asset_to_address(ASSET_LEVEL_HEADERS, (u32) gCurrentLevelHeader, gTempAssetTable[i], sizeof(LevelHeader));
        if (gNumberOfWorlds < gCurrentLevelHeader->world) {
            gNumberOfWorlds = gCurrentLevelHeader->world;
        }
        if ((gCurrentLevelHeader->race_type >= 0) && (gCurrentLevelHeader->race_type < 16)) {
            D_80121180[gCurrentLevelHeader->race_type]++;
        }
        D_8012117C[i].unk0 = gCurrentLevelHeader->world;
        D_8012117C[i].unk1 = gCurrentLevelHeader->race_type;
        D_8012117C[i].unk2 = ((u16) gCurrentLevelHeader->available_vehicles) << 4;
        D_8012117C[i].unk2 |= gCurrentLevelHeader->vehicle & 0xF;
        D_8012117C[i].unk3 = 1;
        D_8012117C[i].unk4 = gCurrentLevelHeader->unkB0;
    }
    gNumberOfWorlds++;
    D_80121178 = allocate_from_main_pool_safe(gNumberOfWorlds, COLOUR_TAG_YELLOW);
    for (i = 0; i < gNumberOfWorlds; i++) {
        D_80121178[i] = -1;
    }
    for (i = 0; i < gNumberOfLevelHeaders; i++) {
        if ((D_8012117C[i].unk1 == 5)) {
            D_80121178[D_8012117C[i].unk0] = i;
        }
    }
    free_from_memory_pool(gTempAssetTable);
    free_from_memory_pool(header);
    gTempAssetTable = (s32 *) load_asset_section_from_rom(ASSET_LEVEL_NAMES_TABLE);
    for (i = 0; gTempAssetTable[i] != (-1); i++){ }
    i--;
    temp = gTempAssetTable[0];
    temp = gTempAssetTable[i] - temp;
    gLevelNames = allocate_from_main_pool_safe(i * sizeof(s32), COLOUR_TAG_YELLOW);
    D_800DD310 = allocate_from_main_pool_safe(temp, COLOUR_TAG_YELLOW);
    load_asset_to_address(ASSET_LEVEL_NAMES, (u32) D_800DD310, 0, temp);
    for (temp = 0; temp < i; temp++) {
        gLevelNames[temp] = (char *) &D_800DD310[gTempAssetTable[temp]];
    }
    free_from_memory_pool(gTempAssetTable);
    // Antipiracy measure
    checksumCount = 0;
    for (j = 0; j < gFunc80068158Length; j++) {
        checksumCount += ((u8 *) (&func_80068158))[j];
    }
    if (checksumCount != gFunc80068158Checksum) {
        disable_button_mask();
    }
}

UNUSED s16 func_8006ABB4(s32 arg0) {
    if (arg0 < 0) {
        return 0xE10;
    }
    if (arg0 >= gNumberOfLevelHeaders) {
        return 0xE10;
    }
    return D_8012117C[arg0].unk4;
}

UNUSED s32 func_8006AC00(s32 arg0, s8 arg1, s8 arg2) {
    if (arg0 < 0) {
        arg0 = 0;
    } else {
        arg0++;
    }
    if (arg1 != 0x40) {
        if (arg2 == -1) {
            for (; arg0 < gNumberOfLevelHeaders; arg0++) {
                if (arg1 == D_8012117C[arg0].unk1) {
                    return arg0;
                }
            }
        } else if (arg1 == -1) {
            for (; arg0 < gNumberOfLevelHeaders; arg0++) {
                if (arg2 == D_8012117C[arg0].unk0) {
                    return arg0;
                }
            }
        } else {
            for (; arg0 < gNumberOfLevelHeaders; arg0++) {
                if ((arg1 == D_8012117C[arg0].unk1) && (arg2 == D_8012117C[arg0].unk0)) {
                    return arg0;
                }
            }
        }
    } else {
        if (arg2 == -1) {
            for (; arg0 < gNumberOfLevelHeaders; arg0++) {
                if (D_8012117C[arg0].unk1 & 0x40) {
                    return arg0;
                }
            }
        } else {
            for (; arg0 < gNumberOfLevelHeaders; arg0++) {
                if ((D_8012117C[arg0].unk1 & 0x40) && (arg2 == D_8012117C[arg0].unk0)) {
                    return arg0;
                }
            }
        }
    }
    return -1;
}

UNUSED s32 func_8006AE2C(s32 arg0, s8 arg1, s8 arg2) {
    if(arg0 >= gNumberOfLevelHeaders){
        arg0 = gNumberOfLevelHeaders;
    }
    arg0--;
    if (arg1 != 0x40) {
        if (arg2 == -1) {
            for (; arg0 >= 0; arg0--) {
                if (arg1 == D_8012117C[arg0].unk1) {
                    return arg0;
                }
            }
        } else if (arg1 == -1) {
            for (; arg0 >= 0; arg0--) {
                if (arg2 == D_8012117C[arg0].unk0) {
                    return arg0;
                }
            }
        } else {
            for (; arg0 >= 0; arg0--) {
                if ((arg1 == D_8012117C[arg0].unk1) && (arg2 == D_8012117C[arg0].unk0)) {
                    return arg0;
                }
            }
        }
    } else {
        if (arg2 == -1) {
            for (; arg0 >= 0; arg0--) {
                if (D_8012117C[arg0].unk1 & 0x40) {
                    return arg0;
                }
            }
        } else {
            for (; arg0 >= 0; arg0--) {
                if ((D_8012117C[arg0].unk1 & 0x40) && (arg2 == D_8012117C[arg0].unk0)) {
                    return arg0;
                }
            }
        }
    }
    return -1;
}

UNUSED s32 func_8006B018(s8 arg0) {
    if ((arg0 >= 0) && (arg0 < 16)) {
        return D_80121180[arg0];
    }
    return 0;
}

UNUSED s32 func_8006B054(s8 arg0) {
    s32 out, i;
    out = 0;
    for (i = 0; i < gNumberOfLevelHeaders; i++) {
        if (arg0 == D_8012117C[i].unk0) {
            out++;
        }
    }
    return out;
}

Vehicle get_map_default_vehicle(s32 mapId) {
    if (mapId > 0 && mapId < gNumberOfLevelHeaders) {
        return D_8012117C[mapId].unk2 & 0xF;
    }
    return VEHICLE_CAR;
}

s32 get_map_available_vehicles(s32 mapId) {
    if (mapId > 0 && mapId < gNumberOfLevelHeaders) {
        s32 temp = D_8012117C[mapId].unk2;
        if (temp != 0) {
            return (temp >> 4) & 0xF;
        }
    }
    return 1;
}

s8 func_8006B14C(s32 mapId) {
    if (mapId >= 0 && mapId < gNumberOfLevelHeaders) {
        return D_8012117C[mapId].unk1;
    }
    return -1;
}

s8 func_8006B190(s32 mapId) {
    if (mapId >= 0 && mapId < gNumberOfLevelHeaders) {
        return D_8012117C[mapId].unk0;
    }
    return 0;
}

s32 get_hub_area_id(s32 worldId) {
    s8 *hubAreaIds;

    if (worldId < 0 || worldId >= gNumberOfWorlds) {
        worldId = 0;
    }
    hubAreaIds = (s8 *)get_misc_asset(MISC_ASSET_UNK1B); //hub_area_ids

    return hubAreaIds[worldId];
}

void get_number_of_levels_and_worlds(s32 *outLevelCount, s32 *outWorldCount) {
    *outLevelCount = gNumberOfLevelHeaders;
    *outWorldCount = gNumberOfWorlds;
}

/**
 * Returns true if the current event is a regular race or a boss race.
 * Returns false if it's a menu, challenge or hubworld.
*/
s32 check_if_in_race(void) {
    return gIsInRace;
}

/**
 * Loads and sets up the level header, then loads and sets of the level geometry.
 * Sets weather, fog and active cutscenes where applicable.
*/
void load_level(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId) {
    s8 *someAsset;
    s32 i;
    s32 size;
    s32 var_s0;
    s32 wizpig;
    s32 numPlayers;
    s32 prevLevelID;
    Settings *settings;
    s32 offset;

    func_80072708();
    if (cutsceneId == -1) {
        cutsceneId = 0;
    }
    if (numberOfPlayers == ZERO_PLAYERS) {
        numPlayers = 1;
        numberOfPlayers = ONE_PLAYER;
    } else {
        numPlayers = 0;
    }
    
    if (numberOfPlayers == ONE_PLAYER) {
        set_sound_channel_count(8);
    } else if (numberOfPlayers == TWO_PLAYERS) {
        set_sound_channel_count(12);
    } else {
        set_sound_channel_count(16);
    }
    settings = get_settings();
    gTempAssetTable = (s32 *) load_asset_section_from_rom(ASSET_LEVEL_HEADERS_TABLE);

    for (i = 0; gTempAssetTable[i] != -1; i++) { }
    i--;
    if (levelId >= i) {
        levelId = ASSET_LEVEL_CENTRALAREAHUB;
    }

    offset = gTempAssetTable[levelId];
    size = gTempAssetTable[levelId + 1] - offset;
    gCurrentLevelHeader = (LevelHeader *) allocate_from_main_pool_safe(size, COLOUR_TAG_YELLOW);
    load_asset_to_address(ASSET_LEVEL_HEADERS, (u32) gCurrentLevelHeader, offset, size);
    D_800DD330 = 0;
    prevLevelID = levelId;
    if (gCurrentLevelHeader->race_type == RACETYPE_DEFAULT) {
        func_8006C2E4();
    }
    if (func_8006C2F0() == 0) {
        if (D_800DD32C == 0) {
            if (gCurrentLevelHeader->race_type == RACETYPE_BOSS) {
                var_s0 = settings->courseFlagsPtr[levelId];
                wizpig = FALSE;
                if (gCurrentLevelHeader->world == WORLD_CENTRAL_AREA || gCurrentLevelHeader->world == WORLD_FUTURE_FUN_LAND) {
                    wizpig = TRUE;
                }
                if (!(var_s0 & 1) || wizpig) {
                    func_8006C1AC(levelId, entranceId, vehicleId, cutsceneId);
                    if (settings->bosses & (1 << settings->worldId)) {
                        cutsceneId = 7;
                    } else {
                        cutsceneId = 3;
                    }
                    if (wizpig) {
                        cutsceneId = 0;
                        if (var_s0 & 1) {
                            D_800DD330 = 2;
                        }
                    }
                    someAsset = (s8 *) get_misc_asset(MISC_ASSET_UNK43);
                    for (var_s0 = 0; levelId != someAsset[var_s0]; var_s0 += 2) { }
                    levelId = someAsset[var_s0 + 1];
                    entranceId = cutsceneId;
                    if (cutsceneId) {} // Fakematch
                }
            }
            if (gCurrentLevelHeader->race_type == RACETYPE_HUBWORLD) {
                if (gCurrentLevelHeader->world > WORLD_CENTRAL_AREA && gCurrentLevelHeader->world < WORLD_FUTURE_FUN_LAND) {
                    var_s0 = gCurrentLevelHeader->world;
                    if (settings->keys & (1 << var_s0) && !(settings->cutsceneFlags & (0x4000 << (var_s0 + 31)))) {
                        // Trigger World Key unlocking Challenge Door cutscene.
                        func_8006C1AC(levelId, entranceId, vehicleId, cutsceneId);
                        settings->cutsceneFlags |= 0x4000 << (var_s0 + 31);
                        someAsset = (s8 *) get_misc_asset(MISC_ASSET_UNK44);
                        levelId = someAsset[var_s0 - 1];
                        entranceId = 0;
                        cutsceneId = 5;
                    }
                }
            }
            if (gCurrentLevelHeader->race_type == RACETYPE_HUBWORLD && gCurrentLevelHeader->world == WORLD_CENTRAL_AREA && !(settings->cutsceneFlags & 0x2000) && settings->wizpigAmulet >= 4) {
                // Trigger wizpig face cutscene
                func_8006C1AC(levelId, entranceId, vehicleId, cutsceneId);
                entranceId = 0;
                cutsceneId = 0;
                settings->cutsceneFlags |= 0x2000;
                levelId = ((s8 *) get_misc_asset(MISC_ASSET_UNK44))[4];
            }
        }
    }
    D_800DD32C = 0;
    if (prevLevelID != levelId) {
        free_from_memory_pool(gCurrentLevelHeader);
        offset = gTempAssetTable[levelId];
        size = gTempAssetTable[levelId + 1] - offset;
        gCurrentLevelHeader = allocate_from_main_pool_safe(size, COLOUR_TAG_YELLOW);
        load_asset_to_address(ASSET_LEVEL_HEADERS, (u32) gCurrentLevelHeader, offset, size);
    }
    free_from_memory_pool(gTempAssetTable);
    func_8006BFC8((s8 *) &gCurrentLevelHeader->unk20);
    func_8000CBC0();
    gMapId = levelId;
    for (var_s0 = 0; var_s0 < 7; var_s0++) {
        if ((s32) gCurrentLevelHeader->unk74[var_s0] != -1) {
            gCurrentLevelHeader->unk74[var_s0] = (s8 *) get_misc_asset((s32) gCurrentLevelHeader->unk74[var_s0]);
            func_8007F1E8((unk8007F1E8 *) gCurrentLevelHeader->unk74[var_s0]);
        }
    }

    if (cutsceneId == 0x64) {
        if (get_trophy_race_world_id() != 0) {
            if (gCurrentLevelHeader->race_type == RACETYPE_DEFAULT) {
                cutsceneId = CUTSCENE_NONE;
            }
        } else if (is_in_tracks_mode() == 1) {
            if (gCurrentLevelHeader->race_type == RACETYPE_DEFAULT) {
                cutsceneId = CUTSCENE_NONE;
            }
        }
    }
    if (gCurrentLevelHeader->race_type == RACETYPE_DEFAULT || gCurrentLevelHeader->race_type == RACETYPE_BOSS) {
        gIsInRace = TRUE;
    } else {
        gIsInRace = FALSE;
    }
    if (numPlayers && gCurrentLevelHeader->race_type != RACETYPE_CUTSCENE_2) {
        gCurrentLevelHeader->race_type = RACETYPE_CUTSCENE_1;
    }
    set_music_player_voice_limit(gCurrentLevelHeader->voiceLimit);
    func_80000CBC();
    func_80031BB8(0x20);
    var_s0 = VEHICLE_CAR;
    if (vehicleId >= VEHICLE_CAR && vehicleId < NUMBER_OF_PLAYER_VEHICLES) {
        var_s0 = gCurrentLevelHeader->unk4F[vehicleId];
    }
    set_taj_challenge_type(var_s0);
    var_s0 = settings->worldId;
    if (gCurrentLevelHeader->world != -1) {
        settings->worldId = gCurrentLevelHeader->world;
    }
    settings->courseId = levelId;
    if (var_s0 == 0 && settings->worldId > 0) {
        gCurrentDefaultVehicle = get_level_default_vehicle();
    }
    if (settings->worldId == 0 && var_s0 > 0 && gCurrentDefaultVehicle != -1) {
        vehicleId = gCurrentDefaultVehicle;
    }
    func_8006DB20(vehicleId);
    if (gCurrentLevelHeader->race_type == RACETYPE_HUBWORLD) {
        if (settings->worldId - 1 >= 0) {
            var_s0 = 8 << (settings->worldId + 31);
            if (settings->worldId == 5) {
                if (settings->balloonsPtr[0] >= 47) {
                    if (settings->ttAmulet >= 4) {
                        if ((settings->cutsceneFlags & var_s0) == 0) {
                            settings->cutsceneFlags |= var_s0;
                            cutsceneId = 5;
                        }
                    }
                }
            } else {
                if (settings->balloonsPtr[settings->worldId] >= 4) {
                    if (!(settings->cutsceneFlags & var_s0)) {
                        settings->cutsceneFlags |= var_s0;
                        cutsceneId = 5;
                    }
                }
                var_s0 <<= 5;
                if (settings->balloonsPtr[settings->worldId] >= 8) {
                    if (!(settings->cutsceneFlags & var_s0)) {
                        settings->cutsceneFlags |= var_s0;
                        cutsceneId = 5;
                    }
                }
            }
        }
    }

    var_s0 = settings->courseFlagsPtr[levelId];
    if (numberOfPlayers != ONE_PLAYER && gCurrentLevelHeader->race_type == RACETYPE_DEFAULT) {
        cutsceneId = 0x64;
    }
    if ((gCurrentLevelHeader->race_type == RACETYPE_DEFAULT || gCurrentLevelHeader->race_type & RACETYPE_CHALLENGE) && is_in_two_player_adventure()) {
        D_800DD318 = 1;
        cutsceneId = 0x64;
    } else {
        D_800DD318 = 0;

    }
    if (gCurrentLevelHeader->race_type == RACETYPE_DEFAULT && numPlayers == 0 && is_time_trial_enabled()) {
        cutsceneId = 0x64;
    }
    func_8001E450(cutsceneId);
    func_800249F0(gCurrentLevelHeader->geometry, gCurrentLevelHeader->skybox, numberOfPlayers, vehicleId, entranceId, gCurrentLevelHeader->collectables, gCurrentLevelHeader->unkBA);
    if (gCurrentLevelHeader->fogNear == 0 && gCurrentLevelHeader->fogFar == 0 && gCurrentLevelHeader->fogR == 0 && gCurrentLevelHeader->fogG == 0 && gCurrentLevelHeader->fogB == 0) {
        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            func_800307BC(var_s0);
        }
    } else {
        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            func_80030664(var_s0, gCurrentLevelHeader->fogNear, gCurrentLevelHeader->fogFar, (u8) gCurrentLevelHeader->fogR, gCurrentLevelHeader->fogG, gCurrentLevelHeader->fogB);
        }
    }
    settings = get_settings();
    if (gCurrentLevelHeader->world != -1) {
        settings->worldId = gCurrentLevelHeader->world;
    }
    settings->courseId = levelId;
    if (gCurrentLevelHeader->weatherEnable > 0) {
        func_800AB4A8(gCurrentLevelHeader->weatherType, gCurrentLevelHeader->weatherEnable, gCurrentLevelHeader->weatherVelX << 8, gCurrentLevelHeader->weatherVelY << 8, gCurrentLevelHeader->weatherVelZ << 8, gCurrentLevelHeader->weatherIntensity * 257, gCurrentLevelHeader->weatherOpacity * 257);
        setWeatherLimits(-1, -0x200);
    }
    if (gCurrentLevelHeader->unk49 == -1) {
        gCurrentLevelHeader->unkA4 = load_texture((s32) gCurrentLevelHeader->unkA4);
        gCurrentLevelHeader->unkA8 = 0;
        gCurrentLevelHeader->unkAA = 0;
    }
    if ((s32) gCurrentLevelHeader->pulseLightData != -1) {
        gCurrentLevelHeader->pulseLightData = (PulsatingLightData *) get_misc_asset((s32) gCurrentLevelHeader->pulseLightData);
        init_pulsating_light_data(gCurrentLevelHeader->pulseLightData);
    }
    update_camera_fov(gCurrentLevelHeader->cameraFOV);
    set_background_prim_colour(gCurrentLevelHeader->bgColorRed, gCurrentLevelHeader->bgColorGreen, gCurrentLevelHeader->bgColorBlue);
    reset_video_delta_time();
    func_8007AB24(gCurrentLevelHeader->unk4[numberOfPlayers]);
}

void func_8006BD10(f32 arg0) {
    if (gCurrentLevelHeader->music != 0) {
        func_800012E8();
        play_music(gCurrentLevelHeader->music);
        func_800014BC(arg0);
        func_80001074(gCurrentLevelHeader->instruments);
    }
}

s32 func_8006BD88(void) {
    return gMapId;
}

/**
 * Return the race type ID of the current level.
 * Official name: levelGetType
 */
u8 get_current_level_race_type(void) {
    return gCurrentLevelHeader->race_type;
}

/**
 * Return the header data of the current level.
 */
LevelHeader *get_current_level_header(void) {
    return gCurrentLevelHeader;
}

/**
 * Returns the amount of level headers there are in the game.
 * Goes unused.
 */
UNUSED u8 get_total_level_header_count(void) {
    return gNumberOfLevelHeaders - 1;
}

/**
 * Returns the name of the level from the passed ID
 */
char *get_level_name(s32 levelId) {
    char *levelName;
    u8 numberOfNullPointers = 0;

    if (levelId < 0 || levelId >= gNumberOfLevelHeaders) {
        return NULL;
    }

    levelName = gLevelNames[levelId];
    switch (get_language()) {
        case LANGUAGE_GERMAN:
            while (numberOfNullPointers < 1) {
                if (*(levelName++) == 0) {
                    numberOfNullPointers++;
                }
            }
            break;
        case LANGUAGE_FRENCH:
            while (numberOfNullPointers < 2) {
                if (*(levelName++) == 0) {
                    numberOfNullPointers++;
                }
            }
            break;
        case LANGUAGE_JAPANESE:
            while (numberOfNullPointers < 3) {
                if (*(levelName++) == 0) {
                    numberOfNullPointers++;
                }
            }
            break;
    }
    return levelName;
}

void func_8006BEFC(void) {
    frontCleanupMultiSelect();
    set_background_prim_colour(0, 0, 0);
    free_from_memory_pool(gCurrentLevelHeader);
    func_800049D8();
    func_80001844();
    func_800018E0();
    func_800012E8();
    func_80031B60();
    func_8002C7D4();
    func_80008174();
    adjust_audio_volume(VOLUME_NORMAL);
    if (gCurrentLevelHeader->weatherEnable > 0) {
        free_weather_memory();
    }
    //! @bug this will never be true because unk49 is signed.
    if (gCurrentLevelHeader->unk49 == 0xFF) {
        free_texture(gCurrentLevelHeader->unkA4);
    }
}

void func_8006BFC8(s8 *arg0) {
    s32 temp;
    UNUSED s32 temp2;
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

    if (is_in_adventure_two()) {
        phi_s0 += 5;
    }

    phi_s0 = arg0[phi_s0];

    // Check if CHEAT_ULTIMATE_AI is active
    // This check works because a << 6 will but a 1 in the sign bit making it negative
    if ((get_filtered_cheats() << 6) < 0) {
        phi_s0 = 9;
    }
    if (get_render_context() == DRAW_MENU) {
        phi_s0 = 5;
    }
    gTempAssetTable = (s32 *) load_asset_section_from_rom(ASSET_UNKNOWN_0_TABLE);
    phi_v1 = 0;
    while (-1 != (s32) gTempAssetTable[phi_v1]) {
        phi_v1++;
    }
    phi_v1--;
    if (phi_s0 >= phi_v1) {
        phi_s0 = 0;
    }
    temp2 = gTempAssetTable[phi_s0];
    temp = gTempAssetTable[phi_s0 + 1] - temp2;
    D_801211C0 = allocate_from_main_pool_safe(temp, COLOUR_TAG_YELLOW);
    load_asset_to_address(ASSET_UNKNOWN_0, (u32) D_801211C0, temp2, temp);
    free_from_memory_pool(gTempAssetTable);
}

void frontCleanupMultiSelect(void) {
    free_from_memory_pool(D_801211C0);
}

TempStruct5 *func_8006C18C(void) {
    return D_801211C0;
}

s8 func_8006C19C(void) {
    return D_800DD318;
}

// Push a stack onto D_801211C8
void func_8006C1AC(s32 levelId, s32 entranceId, Vehicle vehicleId, s32 cutsceneId) {
    D_801211C8[D_800DD328++] = levelId;
    D_801211C8[D_800DD328++] = entranceId;
    D_801211C8[D_800DD328++] = vehicleId;
    D_801211C8[D_800DD328++] = cutsceneId;
}

// Pop a stack from D_801211C8
void func_8006C22C(s32 *levelId, s32 *entranceId, s32 *vehicleId, s32 *cutsceneId) {
    s16 temp_v1;

    D_800DD328--;
    *cutsceneId = D_801211C8[D_800DD328];
    D_800DD328--;
    temp_v1 = D_801211C8[D_800DD328];
    D_800DD328--;
    *entranceId = D_801211C8[D_800DD328];
    D_800DD328--;
    *levelId = D_801211C8[D_800DD328];

    if (temp_v1 != -1) {
        *vehicleId = temp_v1;
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

/**
 * Main looping function for the main thread.
 */
void thread3_main(UNUSED void *unused) {
    init_game();
    gSaveDataFlags = handle_save_data_and_read_controller(gSaveDataFlags, 0);
    sBootDelayTimer = 0;
    sRenderContext = DRAW_INTRO;
    while (1) {
        if (is_reset_pressed()) {
            func_80072708();
            audioStopThread();
            stop_thread30();
            __osSpSetStatus(SP_SET_HALT | SP_CLR_INTR_BREAK | SP_CLR_YIELD | SP_CLR_YIELDED | SP_CLR_TASKDONE | SP_CLR_RSPSIGNAL
                            | SP_CLR_CPUSIGNAL | SP_CLR_SIG5 | SP_CLR_SIG6 | SP_CLR_SIG7);
            osDpSetStatus(DPC_SET_XBUS_DMEM_DMA | DPC_CLR_FREEZE | DPC_CLR_FLUSH | DPC_CLR_TMEM_CTR | DPC_CLR_PIPE_CTR
                            | DPC_CLR_CMD_CTR | DPC_CLR_CMD_CTR);
            while (1); // Infinite loop
        }
        main_game_loop();
        thread3_verify_stack();
    }
}

/**
 * Setup all of the necessary pieces required for the game to function.
 * This includes the memory pool. controllers, video, audio, core assets and more.
 */
void init_game(void) {
    s32 viMode;

    init_main_memory_pool();
    rzipInit(); // Initialise gzip decompression related things
    sAntiPiracyTriggered = TRUE;
    if (check_imem_validity()) {
        sAntiPiracyTriggered = FALSE;
    }
    gIsLoading = FALSE;
    gLevelDefaultVehicleID = VEHICLE_CAR;

    if (osTvType == TV_TYPE_PAL) {
        viMode = OS_VI_PAL_LPN1;
    } else if (osTvType == TV_TYPE_NTSC) {
        viMode = OS_VI_NTSC_LPN1;
    } else if (osTvType == TV_TYPE_MPAL) {
        viMode = OS_VI_MPAL_LPN1;
    }

    osCreateScheduler(&gMainSched, &gSchedStack[0x400], /*priority*/ 13, viMode, 1);
    gDmemInvalid = FALSE;
    if (check_dmem_validity() == FALSE) {
        gDmemInvalid = TRUE;
    }
    init_video(VIDEO_MODE_LOWRES_LPN, &gMainSched);
    init_PI_mesg_queue();
    setup_gfx_mesg_queues(&gMainSched);
    audio_init(&gMainSched);
    func_80008040(); // Should be very similar to func_8005F850
    sControllerStatus = init_controllers();
    texInitTextures(); // Should be very similar to func_8005F850
    func_8005F850(); // Matched
    allocate_object_pools();
    diPrintfInit();
    func_800598D0();
    init_particle_assets();
    func_800AB1F0();
    calc_and_alloc_heap_for_settings();
    default_alloc_heap_for_hud();
    load_fonts();
    init_controller_paks();
    func_80081218();
    create_and_start_thread30();
    osCreateMesgQueue(&gNMIMesgQueue, &gNMIOSMesg, 1);
    osScAddClient(&gMainSched, (OSScClient*) gNMISched, &gNMIMesgQueue, OS_SC_ID_PRENMI);
    gNMIMesgBuf[0] = 0;
    D_80123504 = 0;
    D_80123508 = 0;
    gSPTaskNum = 0;

    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);

    osSetTime(0);
}

/**
 * The main gameplay loop.
 * Contains all game logic, audio and graphics processing.
 */
void main_game_loop(void) {
    s32 debugLoopCounter;
    s32 framebufferSize;
    s32 tempLogicUpdateRate, tempLogicUpdateRateMax;

    osSetTime(0);

    if (gScreenStatus == MESG_SKIP_BUFFER_SWAP) {
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        set_rsp_segment(&gCurrDisplayList, 0, 0);
        set_rsp_segment(&gCurrDisplayList, 1, (s32) gVideoCurrFramebuffer);
        set_rsp_segment(&gCurrDisplayList, 2, (s32) gVideoLastDepthBuffer);
        set_rsp_segment(&gCurrDisplayList, 4, (s32) gVideoCurrFramebuffer - 0x500);
    }
    if (gDrawFrameTimer == 0) {
        setup_ostask_xbus(gDisplayLists[gSPTaskNum], gCurrDisplayList, 0);
        gSPTaskNum += 1;
        gSPTaskNum &= 1;
    }
    if (gDrawFrameTimer) {
        gDrawFrameTimer--;
    }

    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gGameCurrMatrix = gHudMatrices[gSPTaskNum];
    gGameCurrVertexList = gHudVertices[gSPTaskNum];
    gGameCurrTriList = gHudTriangles[gSPTaskNum];

    set_rsp_segment(&gCurrDisplayList, 0, 0);
    set_rsp_segment(&gCurrDisplayList, 1, (s32) gVideoLastFramebuffer);
    set_rsp_segment(&gCurrDisplayList, 2, (s32) gVideoLastDepthBuffer);
    set_rsp_segment(&gCurrDisplayList, 4, (s32) gVideoLastFramebuffer - 0x500);
    init_rsp(&gCurrDisplayList);
    init_rdp_and_framebuffer(&gCurrDisplayList);
    render_background(&gCurrDisplayList, (Matrix *) &gGameCurrMatrix, TRUE); 
    gSaveDataFlags = handle_save_data_and_read_controller(gSaveDataFlags, sLogicUpdateRate);
    if (get_lockup_status()) {
        render_epc_lock_up_display();
        sRenderContext = DRAW_CRASH_SCREEN;
    }
    if (gDmemInvalid) {
        debugLoopCounter = 0;
        while (debugLoopCounter != 10000000) {
            debugLoopCounter++;
        }
        if (debugLoopCounter > 20000000) { // This shouldn't ever be true?
            render_printf(D_800E7134 /* "BBB\n" */);
        }
    }

    switch (sRenderContext) {
        case DRAW_INTRO: // Pre-boot screen
            pre_intro_loop();
            break;
        case DRAW_MENU: // In a menu
            func_8006DCF8(sLogicUpdateRate);
            break;
        case DRAW_GAME: // In game (Controlling a character)
            ingame_logic_loop(sLogicUpdateRate);
            break;
        case DRAW_CRASH_SCREEN: // EPC (lockup display)
            lockup_screen_loop(sLogicUpdateRate);
            break;
    }

    // This is a good spot to place custom text if you want it to overlay it over ALL the
    // menus & gameplay.

    handle_music_fade(sLogicUpdateRate);
    print_debug_strings(&gCurrDisplayList);
    render_dialogue_boxes(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList);
    close_dialogue_box(4);
    assign_dialogue_box_id(4);
    // handle_transitions will perform the logic of transitions and return the transition ID.
    if (handle_transitions(sLogicUpdateRate)) {
        render_fade_transition(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList);
    }
    if ((sBootDelayTimer >= 8) && (is_controller_missing())) {
        print_missing_controller_text(&gCurrDisplayList, sLogicUpdateRate);
    }

    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);

    copy_viewports_to_stack();
    if (gDrawFrameTimer != 1) {
        if (gSkipGfxTask == FALSE) {
            gScreenStatus = wait_for_gfx_task();
        }
    } else {
        gDrawFrameTimer = 0;
    }
    gSkipGfxTask = FALSE;
    clear_free_queue();
    if (!gIsPaused) {
        disable_cutscene_camera();
    }
    if (gDrawFrameTimer == 2) {
        framebufferSize = SCREEN_WIDTH * SCREEN_HEIGHT * 2;
        if (osTvType == TV_TYPE_PAL) {
            framebufferSize = (s32)((SCREEN_WIDTH * SCREEN_HEIGHT * 2) * 1.1f);
        }
        dmacopy_doubleword(gVideoLastFramebuffer, gVideoCurrFramebuffer, (s32) gVideoCurrFramebuffer + framebufferSize);
    }
    // tempLogicUpdateRate will be set to a value 2 or higher, based on the framerate.
    // the mul factor is hardcapped at 6, which happens at 10FPS. The mul factor
    // affects frameskipping, to maintain consistent game speed, through the (many)
    // dropped frames in DKR.
    tempLogicUpdateRate = swap_framebuffer_when_ready(gScreenStatus);
    sLogicUpdateRate = tempLogicUpdateRate;
    tempLogicUpdateRateMax = LOGIC_10FPS;
    if (tempLogicUpdateRate > tempLogicUpdateRateMax) {
        sLogicUpdateRate = tempLogicUpdateRateMax;
    }
}

void func_8006CAE4(s32 arg0, s32 arg1, Vehicle vehicle) {
    D_80123500 = arg0 - 1;
    if (arg1 == -1) {
        gPlayableMapId = get_track_id_to_load();
    } else {
        gPlayableMapId = arg1;
    }
    load_level_2(gPlayableMapId, D_80123500, D_80123504, vehicle);
}

/**
 * Calls load_level() with the same arguments except for the cutsceneId,
 * which is the value at D_80123508. Also does some other stuff.
 * Needs a better name!
 */
void load_level_2(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId) {
    calc_and_alloc_heap_for_hud(numberOfPlayers);
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

// Guessing this is the "unload everything ready for level swap" function.
void func_8006CC14(void) {
    set_free_queue_state(0);
    if (gSkipGfxTask == FALSE) {
        if (gDrawFrameTimer != 1) {
            wait_for_gfx_task();
        }
        gSkipGfxTask = TRUE;
    }
    func_8006BEFC();
    transition_begin(&D_800DD3F4);
    func_800AE270();
    func_800A003C();
    func_800C30CC();
    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);
    set_free_queue_state(2);
}

/**
 * The main behaviour function involving all of the ingame stuff.
 * Involves the updating of all objects and setting up the render scene.
*/
void ingame_logic_loop(s32 updateRate) {
    s32 buttonPressedInputs, buttonHeldInputs, i, sp40, sp3C;

    sp40 = 0;
    buttonHeldInputs = 0;
    buttonPressedInputs = 0;

    // Get input data for all 4 players.
    for (i = 0; i < get_active_player_count(); i++) {
        buttonHeldInputs |= get_buttons_held_from_player(i);
        buttonPressedInputs |= get_buttons_pressed_from_player(i);
    }
    // Spam the start button, making the game unplayable because it's constantly paused.
    if (sAntiPiracyTriggered) {
        buttonPressedInputs |= START_BUTTON;
    }
    // Update all objects
    if (!gIsPaused) {
        func_80010994(updateRate);
        if (check_if_showing_cutscene_camera() == 0 || func_8001139C()) {
            if ((buttonPressedInputs & START_BUTTON) && (func_8006C2F0() == 0) && (D_800DD390 == 0)
                && (sRenderContext == DRAW_GAME) && (gPostRaceViewPort == NULL) && (gLevelLoadTimer == 0) && (D_800DD398 == 0)) {
                buttonPressedInputs = 0;
                gIsPaused = TRUE;
                func_80093A40();
            }
        }
    } else {
        func_80028FA0(1);
    }
    D_800DD398 -= updateRate;
    if (D_800DD398 < 0) {
        D_800DD398 = 0;
    }
    if (gPostRaceViewPort) {
        gIsPaused = FALSE;
    }
    gParticlePtrList_flush();
    func_8001BF20();
    render_scene(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
    if (sRenderContext == DRAW_GAME) {
        // Ignore the user's L/R/Z buttons.
        buttonHeldInputs &= ~(L_TRIG | R_TRIG | Z_TRIG);
    }
    if (gPostRaceViewPort) {
        i = func_80095728(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, updateRate); 
        switch (i) {
            case 2:
                buttonHeldInputs |= (L_TRIG | Z_TRIG);
                break;
            case 1:
                gPostRaceViewPort = NULL;
                func_8006D8F0(-1);
                break;
            case 4:
                func_8006C2E4(); 
                D_800DD390 = 0;
                buttonHeldInputs |= (L_TRIG | R_TRIG);
                break;
            case 5:
                buttonHeldInputs |= L_TRIG,
                sp40 = 1;
                break;
            case 8:
                buttonHeldInputs |= L_TRIG,
                sp40 = 2;
                break;
            case 9:
                buttonHeldInputs |= L_TRIG,
                sp40 = 3;
                break;
            case 10:
                buttonHeldInputs |= L_TRIG,
                sp40 = 4;
                break;
            case 11:
                buttonHeldInputs |= L_TRIG,
                sp40 = 5;
                break;
            case 12:
                buttonHeldInputs |= L_TRIG,
                sp40 = 6;
                break;
            case 13:
                buttonHeldInputs |= L_TRIG,
                sp40 = 7;
                break;
        }
    }
    func_800C3440(updateRate);
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
        i = render_pause_menu(&gCurrDisplayList, updateRate);
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
                buttonHeldInputs |= (L_TRIG | Z_TRIG);
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
    init_rdp_and_framebuffer(&gCurrDisplayList);
    render_borders_for_multiplayer(&gCurrDisplayList);
    render_minimap_and_misc_hud(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, updateRate);
    render_second_multiplayer_borders(&gCurrDisplayList);
    if (D_800DD39C != 0) {
        if (func_800214C4() != 0) {
            gPlayableMapId = ASSET_LEVEL_FUTUREFUNLANDHUB;
            D_801234F8 = 1;
            D_80123504 = 0;
            D_800DD39C = 0;
        }
    }
    sp3C = FALSE;
    if (D_800DD390 != 0) {
        D_800DD390 -= updateRate;
        if (D_800DD390 <= 0) {
            D_800DD390 = 0;
            func_8006C1AC(ASSET_LEVEL_CENTRALAREAHUB, 0, VEHICLE_CAR, 0);
            func_8006C1AC(ASSET_LEVEL_WIZPIGAMULETSEQUENCE, 0, -1, 0xA);
            sp3C = TRUE;
        }
    }
    if (gLevelLoadTimer > 0) {
        gLevelLoadTimer -= updateRate;
        if (gLevelLoadTimer <= 0) {
            buttonHeldInputs = L_TRIG;
            sp3C = TRUE;
            switch (D_80123524) {
                case 1:
                    buttonHeldInputs = (L_TRIG | Z_TRIG);
                    break;
                case 2:
                    sp40 = 3;
                    func_80098208();
                    D_801234FC = 2;
                    break;
                case 3:
                    D_800DD39C = 1;
                    // fall-through
                case 4:
                    D_801234F8 = 1;
                    gPlayableMapId = D_80123525;
                    D_80123504 = 0;
                    D_80123508 = 0;
                    buttonHeldInputs = 0;
                    break;
            }
            D_80123524 = 0;
            gLevelLoadTimer = 0;
        }
    }
    if (sp3C) {
        if (func_8006C2F0() != 0) {
            func_8006C22C(&gPlayableMapId, &D_80123504, &i, &D_80123508);
            func_8006F42C();
            if (gPlayableMapId < 0) {
                if (gPlayableMapId == (s32)SPECIAL_MAP_ID_NO_LEVEL || gPlayableMapId == (s32)SPECIAL_MAP_ID_UNK_NEG10) {
                    if (gPlayableMapId == (s32)SPECIAL_MAP_ID_UNK_NEG10 && is_in_two_player_adventure()) {
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
        if (func_8006C2F0()) {
            if (gLevelLoadTimer == 0) {
                i = func_800214C4();
                if ((i != 0) || ((buttonPressedInputs & A_BUTTON) && (sp3C != 0))) {
                    if (sp3C != 0) {
                        func_80000B28();
                    }
                    func_8006F42C();
                    func_8006C22C(&gPlayableMapId, &D_80123504, &i, &D_80123508);
                    if (gPlayableMapId < 0) {
                        if (gPlayableMapId == -1 || gPlayableMapId == -10) {
                            if (gPlayableMapId == -10 && is_in_two_player_adventure()) {
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
    if (((buttonHeldInputs & L_TRIG) && (sRenderContext == DRAW_GAME)) || (D_801234FC != 0)) {
        gIsPaused = FALSE;
        gLevelLoadTimer = 0;
        gPostRaceViewPort = NULL;
        func_8006CC14();
        safe_mark_write_save_file(get_save_file_index());
        if (sp40 != 0) {
            gIsLoading = FALSE;
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
                    if (is_drumstick_unlocked()) {
                        i ^= 1;
                    }
                    if (is_tt_unlocked()) {
                        i ^= 3;
                    }
                    func_8008AEB4(1, 0);
                    load_menu_with_level_background(MENU_CHARACTER_SELECT, 0x16, i);
                    break;
                case 7:
                    gIsLoading = TRUE;
                    load_menu_with_level_background(MENU_UNKNOWN_23, -1, 0);
                    gIsLoading = FALSE;
                    break;
                case 8:
                    load_menu_with_level_background(MENU_CREDITS, -1, 0);
                    break;
            }
        } else if (D_801234FC == 1) {
            if (D_80121250[2] == -1) {
                load_menu_with_level_background(MENU_UNUSED_8, -1, 0);
            } else {
                gIsLoading = TRUE;
                load_menu_with_level_background(MENU_TRACK_SELECT_ADVENTURE, -1, -1);
            }
        } else if (!(buttonHeldInputs & R_TRIG)) {
            if (!(buttonHeldInputs & Z_TRIG)) {
                gPlayableMapId = D_80121250[0];
                D_80123504 = D_80121250[15];
                D_80123508 = D_80121250[D_80121250[1] + 8];
                gLevelDefaultVehicleID = get_map_default_vehicle(gPlayableMapId);
                if (D_80123508 < 0) {
                    D_80123508 = 0x64;
                }
            }
            load_level_2(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
        } else {
            safe_mark_write_save_file(get_save_file_index());
            load_menu_with_level_background(MENU_TITLE, -1, 0);
        }
        D_801234FC = 0;
    }
    if (D_801234F8 != 0) {
        gPostRaceViewPort = NULL;
        func_8006CC14();
        load_level_2(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
        safe_mark_write_save_file(get_save_file_index());
        D_801234F8 = 0;
    }
}

void func_8006D8A4(void) {
    D_800DD390 = 0x2C;
    gIsPaused = 0;
    n_alSeqpDelete();
    transition_begin(&D_800DD408);
}

void func_8006D8E0(s32 arg0) {
    gPostRaceViewPort = arg0 + 1;
}

void func_8006D8F0(UNUSED s32 arg0) {
    s32 temp;
    if (sRenderContext != DRAW_UNK_04) {
        gPlayableMapId = D_80121250[0];
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
    if (sRenderContext != DRAW_UNK_04) {
        D_80121250[0] = gPlayableMapId;
        for (i = 0; i < 2; i++) {
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

/**
 * Gets the render context from outside this file
 */
RenderContext get_render_context(void) {
    return sRenderContext;
}

/**
 *  Unused function used to set the render context from outside this file
 */
UNUSED void set_render_context(s32 changeTo) {
    sRenderContext = changeTo;
}

void load_menu_with_level_background(s32 menuId, s32 levelId, s32 cutsceneId) {
    calc_and_alloc_heap_for_hud(0);
    sRenderContext = DRAW_MENU;
    D_801234F0 = 1;
    set_sound_channel_volume(0, 32767);
    set_sound_channel_volume(1, 32767);
    set_sound_channel_volume(2, 32767);
    func_80065EA0();

    if (!gIsLoading) {
        gIsLoading = FALSE;
        if (levelId < 0) {
            gIsLoading = TRUE;
        } else {
            load_level_3(levelId, -1, 0, VEHICLE_PLANE, cutsceneId);
        }
    }
    if (menuId == MENU_UNUSED_2 || menuId == MENU_LOGOS || menuId == MENU_TITLE) {
        func_800813C0();
    }
    menu_init(menuId);
    D_80123504 = 0;
}

/**
 * Set the default vehicle option from the current loaded level.
 */
void set_level_default_vehicle(Vehicle vehicleID) {
    gLevelDefaultVehicleID = vehicleID;
}

void func_8006DB20(Vehicle vehicleId) {
    D_8012351C = vehicleId;
}

/**
 * Get the default vehicle option, set by a loaded level.
 */
Vehicle get_level_default_vehicle(void) {
    return gLevelDefaultVehicleID;
}

/**
 * Calls load_level() with the same arguments, but also does some other stuff.
 * Needs a better name!
 */
void load_level_3(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId) {
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
    if (!gIsLoading) {
        gIsLoading = TRUE;
        set_free_queue_state(0);
        func_8006BEFC();
        transition_begin(&D_800DD3F4);
        func_800AE270();
        func_800A003C();
        func_800C30CC();
        set_free_queue_state(2);
    }
    gIsLoading = FALSE;
}

void func_8006DC58(s32 updateRate) {
    if (get_thread30_level_id_to_load() == 0) {
        func_80010994(updateRate);
        gParticlePtrList_flush();
        func_8001BF20();
        render_scene(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
        func_800C3440(updateRate);
        init_rdp_and_framebuffer(&gCurrDisplayList);
        render_borders_for_multiplayer(&gCurrDisplayList);
        render_second_multiplayer_borders(&gCurrDisplayList);
    }
}

#ifdef NON_EQUIVALENT
// Minor & regalloc issues.
void func_8006DCF8(s32 updateRate) {
    s32 menuLoopResult, temp, temp2, tempResult;

    gIsPaused = FALSE;
    gPostRaceViewPort = NULL;
    if (!gIsLoading && D_801234F0) {
        func_8006DC58(updateRate);
    }
    menuLoopResult = menu_loop(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
    D_801234F0 = TRUE;
    if (menuLoopResult == -2) {
        D_801234F0 = FALSE;
        return;
    }
    if ((menuLoopResult != -1) && (menuLoopResult & 0x200)) {
        func_8006DBE4();
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        gDPFullSync(gCurrDisplayList++);
        gSPEndDisplayList(gCurrDisplayList++);
        gPlayableMapId = menuLoopResult & 0x7F;
        gLevelDefaultVehicleID = get_map_default_vehicle(gPlayableMapId);
        D_80123504 = 0;
        D_80123508 = 0x64;
        sRenderContext = DRAW_GAME;
        gIsPaused = FALSE;
        gPostRaceViewPort = NULL;
        load_level_2(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
        safe_mark_write_save_file(get_save_file_index());
        return;
    }
    if ((menuLoopResult != -1) && (menuLoopResult & 0x100)) {
        func_8006CC14();
        gIsPaused = FALSE;
        gPostRaceViewPort = NULL;
        switch (menuLoopResult & 0x7F) {
            case 5:
                load_menu_with_level_background(MENU_TRACK_SELECT, -1, 1);
                break;
            case 14:
                gPlayableMapId = ASSET_LEVEL_CENTRALAREAHUB;
                D_80123504 = 0;
                D_80123508 = 0x64;
                sRenderContext = DRAW_GAME;
                load_level_2(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
                safe_mark_write_save_file(get_save_file_index());
                break;
            case 1:
                D_80123504 = 0;
                D_80123508 = 0x64;
                gPlayableMapId = D_80121250[0];
                sRenderContext = DRAW_GAME;
                // Minor issue with these 2 if statements
                temp2 = D_80121250[D_80121250[1] + 8];
                temp = D_80121250[15];
                if (temp >= 0) {
                    D_80123504 = temp;
                }
                if (temp2 >= 0) {
                    D_80123508 = temp2;
                }
                load_level_2(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
                safe_mark_write_save_file(get_save_file_index());
                break;
            case 2:
                sRenderContext = DRAW_GAME;
                load_level_2(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
                break;
            case 3:
                sRenderContext = DRAW_GAME;
                gPlayableMapId = D_80121250[0];
                D_80123504 = D_80121250[15];
                D_80123508 = D_80121250[D_80121250[1] + 8];
                gLevelDefaultVehicleID = get_map_default_vehicle(gPlayableMapId);
                load_level_2(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
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
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        gDPFullSync(gCurrDisplayList++);
        gSPEndDisplayList(gCurrDisplayList++);
        temp = menuLoopResult & 0x7F;
        D_80121250[1] = temp;
        D_80121250[0] = gPlayableMapId;
        gPlayableMapId = D_80121250[temp + 2];
        D_80123504 = D_80121250[temp + 4];
        sRenderContext = DRAW_GAME;
        D_80123508 = D_80121250[temp + 12];
        temp = get_player_selected_vehicle(0);
        D_80123500 = gSettingsPtr->gNumRacers - 1;
        load_level_2(gPlayableMapId, D_80123500, D_80123504, temp);
        D_801234FC = 0;
        gLevelDefaultVehicleID = D_8012351C;
        return;
    }
    if (menuLoopResult > 0) {
        func_8006DBE4();
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        gDPFullSync(gCurrDisplayList++);
        gSPEndDisplayList(gCurrDisplayList++);
        sRenderContext = DRAW_GAME;
        func_8006CAE4(menuLoopResult, -1, gLevelDefaultVehicleID);
        if (gSettingsPtr->newGame && !is_in_tracks_mode()) {
            func_80000B28();
            gSettingsPtr->newGame = FALSE;
        }
    }
}

#else
GLOBAL_ASM("asm/non_matchings/game/func_8006DCF8.s")
#endif

void load_level_for_menu(s32 levelId, s32 numberOfPlayers, s32 cutsceneId) {
    if (!gIsLoading) {
        func_8006DBE4();
        if (get_thread30_level_id_to_load() == 0) {
            gCurrDisplayList = gDisplayLists[gSPTaskNum];
            gDPFullSync(gCurrDisplayList++);
            gSPEndDisplayList(gCurrDisplayList++);
        }
    }
    if (levelId != (s32) SPECIAL_MAP_ID_NO_LEVEL) {
        //!@bug: Forcing the plane here makes all AI use plane paths. This can be seen most evidently in the Ancient Lake demo.
        load_level_3(levelId, numberOfPlayers, 0, VEHICLE_PLANE, cutsceneId);
        gIsLoading = FALSE;
        return;
    }
    gIsLoading = TRUE;
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
    sizes[3] = sizes[2] + dataSize;   // flapInitialsPtr[1]
    sizes[4] = sizes[3] + dataSize;   // flapInitialsPtr[2]
    sizes[5] = sizes[4] + dataSize;   // flapTimesPtr[0]
    sizes[6] = sizes[5] + dataSize;   // flapTimesPtr[1]
    sizes[7] = sizes[6] + dataSize;   // flapTimesPtr[2]
    sizes[8] = sizes[7] + dataSize;   // courseInitialsPtr[0]
    sizes[9] = sizes[8] + dataSize;   // courseInitialsPtr[1]
    sizes[10] = sizes[9] + dataSize;  // courseInitialsPtr[2]
    sizes[11] = sizes[10] + dataSize; // courseTimesPtr[0]
    sizes[12] = sizes[11] + dataSize; // courseTimesPtr[1]
    sizes[13] = sizes[12] + dataSize; // courseTimesPtr[2]
    sizes[14] = sizes[13] + dataSize; // total size

    gSettingsPtr = allocate_from_main_pool_safe(sizes[14], COLOUR_TAG_WHITE);
    gSettingsPtr->courseFlagsPtr = (s32 *)((u8 *)gSettingsPtr + sizes[0]);
    gSettingsPtr->balloonsPtr = (s16 *)((u8 *)gSettingsPtr + sizes[1]);
    gSettingsPtr->tajFlags = 0;
    gSettingsPtr->flapInitialsPtr[0] = (u16 *)((u8 *)gSettingsPtr + sizes[2]);
    gSettingsPtr->flapInitialsPtr[1] = (u16 *)((u8 *)gSettingsPtr + sizes[3]);
    gSettingsPtr->flapInitialsPtr[2] = (u16 *)((u8 *)gSettingsPtr + sizes[4]);
    gSettingsPtr->flapTimesPtr[0] = (u16 *)((u8 *)gSettingsPtr + sizes[5]);
    gSettingsPtr->flapTimesPtr[1] = (u16 *)((u8 *)gSettingsPtr + sizes[6]);
    gSettingsPtr->flapTimesPtr[2] = (u16 *)((u8 *)gSettingsPtr + sizes[7]);
    gSettingsPtr->courseInitialsPtr[0] = (u16 *)((u8 *)gSettingsPtr + sizes[8]);
    gSettingsPtr->courseInitialsPtr[1] = (u16 *)((u8 *)gSettingsPtr + sizes[9]);
    gSettingsPtr->courseInitialsPtr[2] = (u16 *)((u8 *)gSettingsPtr + sizes[10]);
    gSettingsPtr->courseTimesPtr[0] = (u16 *)((u8 *)gSettingsPtr + sizes[11]);
    gSettingsPtr->courseTimesPtr[1] = (u16 *)((u8 *)gSettingsPtr + sizes[12]);
    gSettingsPtr->courseTimesPtr[2] = (u16 *)((u8 *)gSettingsPtr + sizes[13]);
    gSettingsPtr->unk4C = (Settings4C *) &D_80121250;
    gSaveDataFlags = // Set bits 0/1/2/8 and wipe out all others
        SAVE_DATA_FLAG_READ_FLAP_TIMES |
        SAVE_DATA_FLAG_READ_COURSE_TIMES |
        SAVE_DATA_FLAG_READ_SAVE_DATA |
        SAVE_DATA_FLAG_READ_EEPROM_SETTINGS;
}

void func_8006E5BC(void) {
    s32 i, j;
    gSettingsPtr->gNumRacers = get_number_of_active_players();
    for (i = 0; i < 8; i++) {
        gSettingsPtr->racers[i].best_times = 0;
        gSettingsPtr->racers[i].character = get_character_id_from_slot(i);
        if (gSettingsPtr->gNumRacers >= 2) {
            gSettingsPtr->racers[i].starting_position = i;
        } else if (is_in_two_player_adventure()) {
            gSettingsPtr->racers[i].starting_position = 5 - i;
        } else {
            gSettingsPtr->racers[i].starting_position = 7 - i;
        }
        gSettingsPtr->racers[i].unk7 = 0;
        for (j = 0; j < 4; j++) {
            gSettingsPtr->racers[i].placements[j] = 0;
        }
        gSettingsPtr->racers[i].course_time = 0;
        for (j = 0; j < 3; j++) {
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
    temp_v0 = (u16 *)get_misc_asset(MISC_ASSET_UNK17);
    for (i = 0; i < NUMBER_OF_SAVE_FILES; i++) {
        for (j = 0; j < numLevels; j++) {
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
    settings->newGame = TRUE;

    for (i = 0; i < sp20; i++) {
        settings->balloonsPtr[i] = 0;
    }
    for (i = 0; i < sp1C; i++) {
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

UNUSED void func_8006EA58(void) {
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

/**
 * Returns the status of the post-race shrunken viewport.
*/
s8 is_postrace_viewport_active(void) {
    return gPostRaceViewPort;
}

/**
 * Sets and returns (nonzero) the message set when pressing the reset button.
 * Official name: mainResetPressed
 */
s32 is_reset_pressed(void) {
    if (gNMIMesgBuf[0] == 0) {
        gNMIMesgBuf[0] = (s32)((osRecvMesg(&gNMIMesgQueue, NULL, OS_MESG_NOBLOCK) + 1) != 0);
    }
    return gNMIMesgBuf[0];
}

s32 func_8006EB14(void) {
    return gPlayableMapId;
}

/**
 * Marks a flag to read flap times from the eeprom
 */
UNUSED void mark_to_read_flap_times(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_READ_FLAP_TIMES;
}

/**
 * Marks a flag to read course times from the eeprom
 */
UNUSED void mark_to_read_course_times(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_READ_COURSE_TIMES;
}

/**
 * Marks a flag to read both flap times and course times from the eeprom
 */
void mark_to_read_flap_and_course_times(void) {
    gSaveDataFlags |= (SAVE_DATA_FLAG_READ_FLAP_TIMES | SAVE_DATA_FLAG_READ_COURSE_TIMES);
}

/**
 * Marks a flag to read the save file from the passed index from flash.
 */
void mark_read_save_file(s32 saveFileIndex) {
    //Wipe out bits 8 and 9
    gSaveDataFlags &= ~(SAVE_DATA_FLAG_READ_EEPROM_SETTINGS | SAVE_DATA_FLAG_WRITE_EEPROM_SETTINGS);
    //Place saveFileIndex at bits 8 and 9 and set bit 2
    gSaveDataFlags |= (SAVE_DATA_FLAG_READ_SAVE_DATA | ((saveFileIndex & SAVE_DATA_FLAG_INDEX_VALUE) << 8));
}

/**
 * Marks a flag to read all save file data from flash.
 */
void mark_read_all_save_files(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_READ_ALL_SAVE_DATA; //Set bit 3
}

/**
 * Marks a flag to write flap times to the eeprom
 */
void mark_to_write_flap_times(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_WRITE_FLAP_TIMES;
}

/**
 * Marks a flag to write course times to the eeprom
 */
void mark_to_write_course_times(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_WRITE_COURSE_TIMES;
}

/**
 * Marks a flag to write both flap times and course times to the eeprom
 */
void mark_to_write_flap_and_course_times(void) {
    gSaveDataFlags |= (SAVE_DATA_FLAG_WRITE_FLAP_TIMES | SAVE_DATA_FLAG_WRITE_COURSE_TIMES);
}

/**
 * Forcefully marks a flag to write a save file to flash.
 */
void force_mark_write_save_file(s32 saveFileIndex) {
    gSaveDataFlags &= ~SAVE_DATA_FLAG_WRITE_SAVE_FILE_NUMBER_BITS; //Wipe out bits 10 and 11
    gSaveDataFlags |= (SAVE_DATA_FLAG_WRITE_SAVE_DATA | ((saveFileIndex & 3) << 10)); //Set bit 6 and place saveFileIndex into bits 10 and 11
}

/**
 * Marks a flag to write a save file to flash as long as we're not in tracks mode, and we're in the draw game render context.
 * This should prevent save data from being overwritten outside of Adventure Mode.
 */
void safe_mark_write_save_file(s32 saveFileIndex) {
    if (sRenderContext == DRAW_GAME && !is_in_tracks_mode()) {
        gSaveDataFlags &= ~SAVE_DATA_FLAG_WRITE_SAVE_FILE_NUMBER_BITS; //Wipe out bits 10 and 11
        gSaveDataFlags |= (SAVE_DATA_FLAG_WRITE_SAVE_DATA | ((saveFileIndex & 3) << 10));; //Set bit 6 and place saveFileIndex into bits 10 and 11
    }
}

/**
 * Marks a flag to erase a save file from flash later
 */
void mark_save_file_to_erase(s32 saveFileIndex) {
    //Set bit 7 and and place saveFileIndex into bits 10 and 11 while wiping everything else
    gSaveDataFlags = SAVE_DATA_FLAG_ERASE_SAVE_DATA | ((saveFileIndex & 3) << 10);
}

/**
 * Marks a flag to read eeprom settings from flash later
 * @bug: Because this is the same bit used for reading save files,
 *       it will change the save file number to read from
 */
UNUSED void mark_read_eeprom_settings(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_READ_EEPROM_SETTINGS; // Set bit 8
}

/**
 * Marks a flag to write eeprom settings to flash later
 * @bug: Because this is the same bit used for reading save files,
 *       it will change the save file number to read from
 */
void mark_write_eeprom_settings(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_WRITE_EEPROM_SETTINGS; // Set bit 9
}

/**
 * Allocates an amount of memory for the number of players passed in.
 */
void calc_and_alloc_heap_for_hud(s32 numberOfPlayers) {
    s32 newVar;
    s32 totalSize;

    if (numberOfPlayers != D_8012350C) {
        newVar = numberOfPlayers;
        D_8012350C = newVar;
        set_free_queue_state(0);
        free_from_memory_pool(gDisplayLists[0]);
        free_from_memory_pool(gDisplayLists[1]);
        totalSize =
            ((gNumF3dCmdsPerPlayer[newVar] * sizeof(Gwords)))
            + ((gNumHudMatPerPlayer[newVar] * sizeof(Matrix)))
            + ((gNumHudVertsPerPlayer[newVar] * sizeof(Vertex)))
            + ((gNumHudTrisPerPlayer[newVar] * sizeof(Triangle)));
        gDisplayLists[0] = (Gfx *) allocate_at_address_in_main_pool(totalSize, (u8 *) gDisplayLists[0], COLOUR_TAG_RED);
        gDisplayLists[1] = (Gfx *) allocate_at_address_in_main_pool(totalSize, (u8 *) gDisplayLists[1], COLOUR_TAG_YELLOW);
        if ((gDisplayLists[0] == NULL) || gDisplayLists[1] == NULL) {
            if (gDisplayLists[0] != NULL) {
                free_from_memory_pool(gDisplayLists[0]);
                gDisplayLists[0] = NULL;
            }
            if (gDisplayLists[1] != NULL) {
                free_from_memory_pool(gDisplayLists[1]);
                gDisplayLists[1] = NULL;
            }
            default_alloc_heap_for_hud();
        }
        gHudMatrices[0] = (MatrixS *)((u8 *) gDisplayLists[0] + ((gNumF3dCmdsPerPlayer[newVar] * sizeof(Gwords))));
        gHudTriangles[0] = (TriangleList *)((u8 *) gHudMatrices[0] + ((gNumHudMatPerPlayer[newVar] * sizeof(Matrix))));
        gHudVertices[0] = (Vertex *)((u8 *) gHudTriangles[0] + ((gNumHudTrisPerPlayer[newVar] * sizeof(Triangle))));
        gHudMatrices[1] = (MatrixS *)((u8 *) gDisplayLists[1] + ((gNumF3dCmdsPerPlayer[newVar] * sizeof(Gwords))));
        gHudTriangles[1] = (TriangleList *)((u8 *) gHudMatrices[1] + ((gNumHudMatPerPlayer[newVar] * sizeof(Matrix))));
        gHudVertices[1] = (Vertex *)((u8 *) gHudTriangles[1] + ((gNumHudTrisPerPlayer[newVar] * sizeof(Triangle))));
        gCurrNumF3dCmdsPerPlayer = gNumF3dCmdsPerPlayer[newVar];
        gCurrNumHudMatPerPlayer = gNumHudMatPerPlayer[newVar];
        gCurrNumHudTrisPerPlayer = gNumHudTrisPerPlayer[newVar];
        gCurrNumHudVertsPerPlayer = gNumHudVertsPerPlayer[newVar];
        set_free_queue_state(2);
    }
    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gGameCurrMatrix = gHudMatrices[gSPTaskNum];
    gGameCurrTriList = gHudTriangles[gSPTaskNum];
    gGameCurrVertexList = gHudVertices[gSPTaskNum];

    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);
}

/**
 * Returns FALSE if dmem doesn't begin with a -1. This is checked on every main game loop iteration.
 */
s32 check_dmem_validity(void) {
    if (IO_READ(SP_DMEM_START) != -1U) {
        return FALSE;
    }
    return TRUE;
}

/**
 * Defaults allocations for 4 players
 */
void default_alloc_heap_for_hud(void) {
    s32 numberOfPlayers;
    s32 totalSize;

    numberOfPlayers = FOUR_PLAYERS;
    D_8012350C = numberOfPlayers;
    totalSize = (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords))
        + (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix))
        + (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex))
        + (gNumHudTrisPerPlayer[numberOfPlayers] * sizeof(Triangle));

    gDisplayLists[0] = (Gfx *)allocate_from_main_pool_safe(totalSize, COLOUR_TAG_RED);
    gHudMatrices[0] = (MatrixS *)((u8 *)gDisplayLists[0] + (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords)));
    gHudVertices[0] = (Vertex *)((u8 *)gHudMatrices[0] + (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix)));
    gHudTriangles[0] = (TriangleList *)((u8 *)gHudVertices[0] + (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex)));

    gDisplayLists[1] = (Gfx *)allocate_from_main_pool_safe(totalSize, COLOUR_TAG_YELLOW);
    gHudMatrices[1] = (MatrixS *)((u8 *)gDisplayLists[1] + (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords)));
    gHudVertices[1] = (Vertex *)((u8 *)gHudMatrices[1] + (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix)));
    gHudTriangles[1] = (TriangleList *)((u8 *)gHudVertices[1] + (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex)));

    gCurrNumF3dCmdsPerPlayer = gNumF3dCmdsPerPlayer[numberOfPlayers];
    gCurrNumHudMatPerPlayer = gNumHudMatPerPlayer[numberOfPlayers];
    gCurrNumHudTrisPerPlayer = gNumHudTrisPerPlayer[numberOfPlayers];
    gCurrNumHudVertsPerPlayer = gNumHudVertsPerPlayer[numberOfPlayers];
}

void func_8006F140(s32 arg0) {
    if (gLevelLoadTimer == 0) {
        gLevelLoadTimer = 40;
        D_80123524 = 0;
        D_80123526 = 0;
        if (arg0 == 1) {
            transition_begin(&D_800DD41C);
        }
        if (arg0 == 3) {
            gLevelLoadTimer = 282;
            transition_begin(&D_800DD424);
        }
        if (arg0 == 4) {
            gLevelLoadTimer = 360;
            transition_begin(&D_800DD424);
        }
        if (arg0 == 0) {
            gLevelLoadTimer = 2;
        }
    }
}

UNUSED void func_8006F20C(void) {
    if (gLevelLoadTimer == 0) {
        transition_begin(&D_800DD41C);
        gLevelLoadTimer = 40;
        D_80123524 = 1;
    }
}

void func_8006F254(void) {
    if (gLevelLoadTimer == 0) {
        transition_begin(&D_800DD41C);
        gLevelLoadTimer = 40;
        D_80123524 = 2;
    }
}

void func_8006F29C(void) {
    if (gLevelLoadTimer == 0) {
        if ((gSettingsPtr->trophies & 0xFF) == 0xFF && !(gSettingsPtr->cutsceneFlags & CUTSCENE_LIGHTHOUSE_ROCKET) && gSettingsPtr->bosses & 1) {
            gSettingsPtr->cutsceneFlags |= CUTSCENE_LIGHTHOUSE_ROCKET;
            transition_begin(&D_800DD41C);
            gLevelLoadTimer = 40;
            D_80123525 = 0x2D;
            D_80123524 = 3;
        }
    }
}

void func_8006F338(s32 arg0) {
    if (gLevelLoadTimer == 0) {
        D_80123525 = arg0;
        transition_begin(&D_800DD41C);
        gLevelLoadTimer = 40;
        D_80123524 = 4;
    }
}

void func_8006F388(u8 time) {
    D_800DD398 = time;
}

void func_8006F398(void) {
    s32 i;
    u8 temp;
    u8 *first_racer_data;
    u8 *second_racer_data;

    swap_player_1_and_2_ids();
    func_8000E194();

    first_racer_data = (u8 *)(gSettingsPtr->racers);
    second_racer_data = (u8 *)(gSettingsPtr->racers + 1);

    for (i = 0; i < (s32)sizeof(Racer); i++) {
        temp = first_racer_data[i];
        first_racer_data[i] = second_racer_data[i];
        second_racer_data[i] = temp;
    }
}

void func_8006F42C(void) {
    gDrawFrameTimer = 2;
}

/**
 * Give the player 8 frames to enter the CPak menu with start, then load the intro sequence.
 */
void pre_intro_loop(void) {
    s32 i;
    s32 buttonInputs = 0;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        buttonInputs |= get_buttons_held_from_player(i);
    }
    if (buttonInputs & START_BUTTON) {
        gShowControllerPakMenu = TRUE;
    }
    sBootDelayTimer++;
    if (sBootDelayTimer >= 8) {
        load_menu_with_level_background(MENU_BOOT, 0x27, 2);
    }
}

/**
 * Returns TRUE if the game doesn't detect any controllers.
 * Official name: mainDemoOnly
 */
s32 is_controller_missing(void) {
    if (sControllerStatus == CONTROLLER_MISSING) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * Ran on boot, will make sure the CIC chip (CIC6103) is to spec. Will return true if it's all good, otherwise it returns false.
 * The intention of this function, is an attempt to check that the cartridge is a legitimate copy.
 * A false read, meaning you're caught running an illegitimate copy, will force the game to pause when you enter the world.
 */
s32 check_imem_validity(void) {
    if (IO_READ(SP_IMEM_START) != 0x17D7) {
        return FALSE;
    }
    return TRUE;
}
