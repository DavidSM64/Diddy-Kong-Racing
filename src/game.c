/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8006A6B0 */

#include "game.h"

#include <PR/os_cont.h>
#include <PR/gu.h>
#include <PR/gbi.h>
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
#include "string.h"
#include "stdarg.h"
#include "math_util.h"
#include "controller.h"

/************ .rodata ************/

/*********************************/

/************ .data ************/

char *gTempLevelNames = NULL;
s8 gCurrentDefaultVehicle = -1;
u8 D_800DD318 = FALSE;
s32 gIsInRace = 0;

// Updated automatically from calc_func_checksums.py
s32 gFunc80068158Checksum = 0x585E;
s32 gFunc80068158Length = 0x154;

s16 gLevelPropertyStackPos = 0;
s16 D_800DD32C = 0;

s8 D_800DD330 = 0;

s8 sAntiPiracyTriggered = 0;
s32 gSaveDataFlags = 0; //Official Name: load_save_flags
s32 sControllerStatus = 0;
s8 gSkipGfxTask = FALSE;
s8 D_800DD390 = 0;
s16 gLevelLoadTimer = 0;
s8 D_800DD398 = 0;
s8 D_800DD39C = 0;
s8 gDmemInvalid = FALSE;
s32 gNumF3dCmdsPerPlayer[4] = { 4500, 7000, 11000, 11000 };
s32 gNumHudVertsPerPlayer[4] = { 300, 600, 850, 900 };
s32 gNumHudMatPerPlayer[4] = { 300, 400, 550, 600 };
s32 gNumHudTrisPerPlayer[4] = { 20, 30, 40, 50 };
s8 gDrawFrameTimer = 0;
FadeTransition D_800DD3F4 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_UNK2, FADE_COLOR_BLACK, 20, 0);
s32 sLogicUpdateRate = LOGIC_5FPS;
FadeTransition D_800DD408 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_WHITE, 30, -1);
FadeTransition gLevelFadeOutTransition = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 30, -1);
FadeTransition D_800DD424 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 260, -1);
s32 gNumGfxTasksAtScheduler = 0;
/*******************************/

/************ .bss ************/

s32 *gTempAssetTable;
s32 gMapId;
LevelHeader *gCurrentLevelHeader;
char **gLevelNames;
s32 gNumberOfLevelHeaders;
s32 gNumberOfWorlds;

s8 *D_80121178;
LevelGlobalData *gGlobalLevelTable;

s32 D_80121180[16];

TempStruct5 *D_801211C0;
s16 gLevelPropertyStack[5 * 4]; // Stores level info for cutscenes. 5 sets of four properties.
Gfx *gDisplayLists[2];
Gfx *gCurrDisplayList;
MatrixS *gMatrixHeap[2];
MatrixS *gGameCurrMatrix;
Vertex *gVertexHeap[2];
Vertex *gGameCurrVertexList;
TriangleList *gTriangleHeap[2];
TriangleList *gGameCurrTriList;
s8 D_80121250[16]; //Settings4C
OSSched gMainSched; // 0x288 / 648 bytes
u64 gSchedStack[THREAD5_STACK / sizeof(u64)];
s32 gSPTaskNum;
s32 sRenderContext;
s32 D_801234F0; // I don't think this is ever not 1
// Similar to gMapId, but is 0 if not currently playing a level (e.g. start menu).
s32 gPlayableMapId;
s32 D_801234F8;
s32 D_801234FC;
s32 D_80123500;
s32 D_80123504;
s32 D_80123508;
s32 gPrevPlayerCount;
Settings *gSettingsPtr;
s8 gIsLoading;
s8 gIsPaused;
s8 gPostRaceViewPort;
Vehicle gLevelDefaultVehicleID;
Vehicle D_8012351C; // Looks to be the current level's vehicle ID.
s32 sBootDelayTimer;
s8 D_80123524;
s8 gNextMap;
s32 gCurrNumF3dCmdsPerPlayer;
s32 gCurrNumHudMatPerPlayer;
s32 gCurrNumHudTrisPerPlayer;
s32 gCurrNumHudVertsPerPlayer;
OSScClient *gNMISched[3];
OSMesg gGameMesgBuf[3];
OSMesgQueue gGameMesgQueue;
s32 gNMIMesgBuf; //Official Name: resetPressed
s32 D_80123568[6]; // BSS Padding

/******************************/

/**
 * Allocates memory for gGlobalLevelTable, then populates it with relevant data from every level header.
 * The level headers are streamed from ROM.
 * Additionally loads other globally accessed information, like level names, then runs a checksum compare, for good measure.
*/
void init_level_globals(void) {
    s32 i;
    s32 size;
    u8 *header;
#ifndef NO_ANTIPIRACY
    s32 checksumCount;
    s32 j;
#endif
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
    gGlobalLevelTable = allocate_from_main_pool_safe(gNumberOfLevelHeaders * sizeof(LevelGlobalData), COLOUR_TAG_YELLOW);
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
        gGlobalLevelTable[i].world = gCurrentLevelHeader->world;
        gGlobalLevelTable[i].raceType = gCurrentLevelHeader->race_type;
        gGlobalLevelTable[i].vehicles = ((u16) gCurrentLevelHeader->available_vehicles) << 4;
        gGlobalLevelTable[i].vehicles |= gCurrentLevelHeader->vehicle & 0xF;
        gGlobalLevelTable[i].unk3 = 1;
        gGlobalLevelTable[i].unk4 = gCurrentLevelHeader->unkB0;
    }
    gNumberOfWorlds++;
    D_80121178 = allocate_from_main_pool_safe(gNumberOfWorlds, COLOUR_TAG_YELLOW);
    for (i = 0; i < gNumberOfWorlds; i++) {
        D_80121178[i] = -1;
    }
    for (i = 0; i < gNumberOfLevelHeaders; i++) {
        if ((gGlobalLevelTable[i].raceType == 5)) {
            D_80121178[gGlobalLevelTable[i].world] = i;
        }
    }
    free_from_memory_pool(gTempAssetTable);
    free_from_memory_pool(header);
    gTempAssetTable = (s32 *) load_asset_section_from_rom(ASSET_LEVEL_NAMES_TABLE);
    for (i = 0; gTempAssetTable[i] != (-1); i++) { }
    i--;
    size = gTempAssetTable[i] - gTempAssetTable[0];
    gLevelNames = allocate_from_main_pool_safe(i * sizeof(s32), COLOUR_TAG_YELLOW);
    gTempLevelNames = allocate_from_main_pool_safe(size, COLOUR_TAG_YELLOW);
    load_asset_to_address(ASSET_LEVEL_NAMES, (u32) gTempLevelNames, 0, size);
    for (size = 0; size < i; size++) {
        gLevelNames[size] = (char *) &gTempLevelNames[gTempAssetTable[size]];
    }
    free_from_memory_pool(gTempAssetTable);
    // Antipiracy measure
#ifndef NO_ANTIPIRACY
    checksumCount = 0;
    for (j = 0; j < gFunc80068158Length; j++) {
        checksumCount += ((u8 *) (&func_80068158))[j];
    }
    if (checksumCount != gFunc80068158Checksum) {
        disable_button_mask();
    }
#endif
}

/**
 * Returns the default vehicle from the set map ID.
*/
Vehicle get_map_default_vehicle(s32 mapId) {
    if (mapId > 0 && mapId < gNumberOfLevelHeaders) {
        return gGlobalLevelTable[mapId].vehicles & 0xF;
    }
    return VEHICLE_CAR;
}

/**
 * Returns the available vehicles from the set map ID.
*/
s32 get_map_available_vehicles(s32 mapId) {
    if (mapId > 0 && mapId < gNumberOfLevelHeaders) {
        s32 temp = gGlobalLevelTable[mapId].vehicles;
        if (temp != 0) {
            return (temp >> 4) & 0xF;
        }
    }
    return VEHICLE_HOVERCRAFT;
}

/**
 * Returns the race type from the set map ID.
*/
s8 get_map_race_type(s32 mapId) {
    if (mapId >= 0 && mapId < gNumberOfLevelHeaders) {
        return gGlobalLevelTable[mapId].raceType;
    }
    return -1;
}

/**
 * Returns the world ID from the set map ID.
*/
s8 get_map_world_id(s32 mapId) {
    if (mapId >= 0 && mapId < gNumberOfLevelHeaders) {
        return gGlobalLevelTable[mapId].world;
    }
    return 0;
}

/**
 * Returns the ID of the current hub world. Example: Dino Domain.
*/
s32 get_hub_area_id(s32 worldId) {
    s8 *hubAreaIds;

    if (worldId < 0 || worldId >= gNumberOfWorlds) {
        worldId = 0;
    }
    hubAreaIds = (s8 *)get_misc_asset(MISC_ASSET_UNK1B); //hub_area_ids

    return hubAreaIds[worldId];
}

/**
 * Writes the level and hub count to the two arguments passed through.
*/
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
        cutsceneId = CUTSCENE_NONE;
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
        clear_level_property_stack();
    }
    if (get_level_property_stack_pos() == 0) {
        if (D_800DD32C == 0) {
            if (gCurrentLevelHeader->race_type == RACETYPE_BOSS) {
                var_s0 = settings->courseFlagsPtr[levelId];
                wizpig = FALSE;
                if (gCurrentLevelHeader->world == WORLD_CENTRAL_AREA || gCurrentLevelHeader->world == WORLD_FUTURE_FUN_LAND) {
                    wizpig = TRUE;
                }
                if (!(var_s0 & 1) || wizpig) {
                    push_level_property_stack(levelId, entranceId, vehicleId, cutsceneId);
                    if (settings->bosses & (1 << settings->worldId)) {
                        cutsceneId = CUTSCENE_ID_UNK_7;
                    } else {
                        cutsceneId = CUTSCENE_ID_UNK_3;
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
                }
            }
            if (gCurrentLevelHeader->race_type == RACETYPE_HUBWORLD) {
                if (gCurrentLevelHeader->world > WORLD_CENTRAL_AREA && gCurrentLevelHeader->world < WORLD_FUTURE_FUN_LAND) {
                    var_s0 = gCurrentLevelHeader->world;
                    if (settings->keys & (1 << var_s0) && !(settings->cutsceneFlags & (CUTSCENE_DINO_DOMAIN_KEY << (var_s0 + 31)))) {
                        // Trigger World Key unlocking Challenge Door cutscene.
                        push_level_property_stack(levelId, entranceId, vehicleId, cutsceneId);
                        settings->cutsceneFlags |= CUTSCENE_DINO_DOMAIN_KEY << (var_s0 + 31);
                        someAsset = (s8 *) get_misc_asset(MISC_ASSET_UNK44);
                        levelId = someAsset[var_s0 - 1];
                        entranceId = 0;
                        cutsceneId = CUTSCENE_ID_UNK_5;
                    }
                }
            }
            if (gCurrentLevelHeader->race_type == RACETYPE_HUBWORLD && gCurrentLevelHeader->world == WORLD_CENTRAL_AREA && 
                !(settings->cutsceneFlags & CUTSCENE_WIZPIG_FACE) && settings->wizpigAmulet >= 4) {
                // Trigger wizpig face cutscene
                push_level_property_stack(levelId, entranceId, vehicleId, cutsceneId);
                entranceId = 0;
                cutsceneId = CUTSCENE_NONE;
                settings->cutsceneFlags |= CUTSCENE_WIZPIG_FACE;
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

    if (cutsceneId == CUTSCENE_ID_UNK_64) {
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
                            cutsceneId = CUTSCENE_ID_UNK_5;
                        }
                    }
                }
            } else {
                if (settings->balloonsPtr[settings->worldId] >= 4) {
                    if (!(settings->cutsceneFlags & var_s0)) {
                        settings->cutsceneFlags |= var_s0;
                        cutsceneId = CUTSCENE_ID_UNK_5;
                    }
                }
                var_s0 <<= 5;
                if (settings->balloonsPtr[settings->worldId] >= 8) {
                    if (!(settings->cutsceneFlags & var_s0)) {
                        settings->cutsceneFlags |= var_s0;
                        cutsceneId = CUTSCENE_ID_UNK_5;
                    }
                }
            }
        }
    }

    var_s0 = settings->courseFlagsPtr[levelId];
    if (numberOfPlayers != ONE_PLAYER && gCurrentLevelHeader->race_type == RACETYPE_DEFAULT) {
        cutsceneId = CUTSCENE_ID_UNK_64;
    }
    if ((gCurrentLevelHeader->race_type == RACETYPE_DEFAULT || gCurrentLevelHeader->race_type & RACETYPE_CHALLENGE) && is_in_two_player_adventure()) {
        D_800DD318 = TRUE;
        cutsceneId = CUTSCENE_ID_UNK_64;
    } else {
        D_800DD318 = FALSE;

    }
    if (gCurrentLevelHeader->race_type == RACETYPE_DEFAULT && numPlayers == 0 && is_time_trial_enabled()) {
        cutsceneId = CUTSCENE_ID_UNK_64;
    }
    func_8001E450(cutsceneId);

    func_800249F0(gCurrentLevelHeader->geometry, gCurrentLevelHeader->skybox, numberOfPlayers, vehicleId, entranceId, gCurrentLevelHeader->collectables, gCurrentLevelHeader->unkBA);

    if (gCurrentLevelHeader->fogNear == 0 && gCurrentLevelHeader->fogFar == 0 && gCurrentLevelHeader->fogR == 0 && gCurrentLevelHeader->fogG == 0 && gCurrentLevelHeader->fogB == 0) {
        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            reset_fog(var_s0);
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
    s32 temp2;
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

    if (get_filtered_cheats() & CHEAT_ULTIMATE_AI) {
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

/**
 * Pushes the current level data onto a stack.
 * Used for preserving certain properties when viewing cutscenes, where this information would otherwise be lost.
*/
void push_level_property_stack(s32 levelId, s32 entranceId, Vehicle vehicleId, s32 cutsceneId) {
    gLevelPropertyStack[gLevelPropertyStackPos++] = levelId;
    gLevelPropertyStack[gLevelPropertyStackPos++] = entranceId;
    gLevelPropertyStack[gLevelPropertyStackPos++] = vehicleId;
    gLevelPropertyStack[gLevelPropertyStackPos++] = cutsceneId;
}

/**
 * Reads the level data from the stack, then pops it.
 * Used after cutscenes to properly restore the previous level status.
*/
void pop_level_property_stack(s32 *levelId, s32 *entranceId, s32 *vehicleId, s32 *cutsceneId) {
    s32 tempVehicleID;

    gLevelPropertyStackPos--;
    *cutsceneId = gLevelPropertyStack[gLevelPropertyStackPos--];
    tempVehicleID = gLevelPropertyStack[gLevelPropertyStackPos--];
    *entranceId = gLevelPropertyStack[gLevelPropertyStackPos--];
    *levelId = gLevelPropertyStack[gLevelPropertyStackPos];

    if (tempVehicleID != -1) {
        *vehicleId = tempVehicleID;
    }

    D_800DD32C = 1;
}

/**
 * Resets the position in the level propert stack, effectively clearing it.
*/
void clear_level_property_stack(void) {
    gLevelPropertyStackPos = 0;
}

/**
 * Returns the position of the level property stack.
 * Should always return a multiple of 4.
 */
s16 get_level_property_stack_pos(void) {
    return gLevelPropertyStackPos;
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
 * Official Name: mainThread
 */
void thread3_main(UNUSED void *unused) {
    OSMesg mesg;

    init_game();
    gSaveDataFlags = handle_save_data_and_read_controller(gSaveDataFlags, 0);
    sBootDelayTimer = 0;
    sRenderContext = DRAW_INTRO;

    while (1) {
        while (gNumGfxTasksAtScheduler < 2) {
            main_game_loop();
        }

        osRecvMesg(&gGameMesgQueue, &mesg, OS_MESG_BLOCK);

        switch ((s32) mesg) {
        case OS_SC_DONE_MSG:
            gNumGfxTasksAtScheduler--;
            break;

        case OS_SC_PRE_NMI_MSG:
            gNMIMesgBuf = TRUE;
            func_80072708();
            audioStopThread();
            stop_thread30();
            __osSpSetStatus(SP_SET_HALT | SP_CLR_INTR_BREAK | SP_CLR_YIELD | SP_CLR_YIELDED | SP_CLR_TASKDONE | SP_CLR_RSPSIGNAL
                    | SP_CLR_CPUSIGNAL | SP_CLR_SIG5 | SP_CLR_SIG6 | SP_CLR_SIG7);
            osDpSetStatus(DPC_SET_XBUS_DMEM_DMA | DPC_CLR_FREEZE | DPC_CLR_FLUSH | DPC_CLR_TMEM_CTR | DPC_CLR_PIPE_CTR
                    | DPC_CLR_CMD_CTR | DPC_CLR_CMD_CTR);
            while (1);
            break;
        }
    }
}

#ifndef FIFO_UCODE
u8 gDisableAA = TRUE;
#else
u8 gDisableAA = TRUE;
#endif
u8 gHideHUD = FALSE;
s8 gScreenMode = 0;
s8 gScreenPos[2] = {0, 0};

/**
 * Setup all of the necessary pieces required for the game to function.
 * This includes the memory pool. controllers, video, audio, core assets and more.
 * Official Name: mainInitGame
 */
void init_game(void) {
    s32 i;

    init_main_memory_pool();
    rzipInit(); // Initialise gzip decompression related things
#ifndef NO_ANTIPIRACY
    sAntiPiracyTriggered = TRUE;
    if (check_imem_validity()) {
        sAntiPiracyTriggered = FALSE;
    }
#endif
    gIsLoading = FALSE;
    gLevelDefaultVehicleID = VEHICLE_CAR;

    osCreateScheduler(&gMainSched, &gSchedStack[0x40], OS_SC_PRIORITY, (u8) 0, 1);
    init_video(VIDEO_MODE_LOWRES_LPN, &gMainSched);
    init_PI_mesg_queue();
    setup_gfx_mesg_queues(&gMainSched);
    audio_init(&gMainSched);
    func_80008040(); // Should be very similar to func_8005F850
    sControllerStatus = init_controllers();
    tex_init_textures();
    func_8005F850(); // Matched
    allocate_object_pools();
    diPrintfInit();
    func_800598D0();
    init_particle_assets();
    func_800AB1F0();
    calc_and_alloc_heap_for_settings();
    default_alloc_displaylist_heap();
    load_fonts();
    init_controller_paks();
    func_80081218();
    create_and_start_thread30();
    osCreateMesgQueue(&gGameMesgQueue, gGameMesgBuf, 3);
    osScAddClient(&gMainSched, (OSScClient*) gNMISched, &gGameMesgQueue, OS_SC_ID_VIDEO);
    gNMIMesgBuf = 0;
    D_80123504 = 0;
    D_80123508 = 0;
    gSPTaskNum = 0;

    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);
    get_platform();

    osSetTime(0);
}

#ifdef FIFO_UCODE
s8 suCodeSwitch = 0;
#endif

u32 sPrevTime = 0;
u32 sDeltaTime = 0;
s32 sTotalTime = 0;
u8 gOverrideAA = 0;
s32 gOverrideTimer = 0;

extern s32 gVideoSkipNextRate;

s32 calculate_updaterate(void) {
    static u32 prevtime = 0;
    static s32 remainder = 0;
    s32 total;
    s32 rate;

    u32 now = osGetCount();

    if (gVideoSkipNextRate) {
        rate = LOGIC_60FPS;
        remainder = 0;
        gVideoSkipNextRate = FALSE;
    } else {
        if (now > prevtime) {
            total = (u32) (now - prevtime) + remainder;
        } else {
            // Counter has reset since last time
            total = (0xffffffff - prevtime) + 1 + now + remainder;
        }

        if (total < (OS_CPU_COUNTER / 30)) { // 30-60 fps
            rate = LOGIC_60FPS;
        } else if (total < (OS_CPU_COUNTER / 20)) { // 20-30 fps
            rate = LOGIC_30FPS;
        } else if (total < (OS_CPU_COUNTER / 15)) {
            rate = LOGIC_20FPS;
        } else if (total < (OS_CPU_COUNTER / 12)) {
            rate = LOGIC_15FPS;
        } else if (total < (OS_CPU_COUNTER / 10)) {
            rate = LOGIC_12FPS;
        } else {
            rate = LOGIC_10FPS;
        }

        remainder = total - rate * (OS_CPU_COUNTER / 60);
    }

    prevtime = now;

    return rate;
}


/**
 * The main gameplay loop.
 * Contains all game logic, audio and graphics processing.
 */
void main_game_loop(void) {
    s32 framebufferSize;
    s32 tempLogicUpdateRate, tempLogicUpdateRateMax;
#ifdef PUPPYPRINT_DEBUG
    profiler_reset_values();
    profiler_snapshot(THREAD4_START);
#endif

    /*if (gVideoSkipNextRate) {
        sLogicUpdateRate = LOGIC_60FPS;
        sTotalTime = 0;
        sPrevTime = 0;
        gVideoSkipNextRate = FALSE;
    } else {
        sDeltaTime = osGetCount() - sPrevTime;
        sPrevTime = osGetCount();
        sTotalTime += OS_CYCLES_TO_USEC(sDeltaTime);
        sTotalTime -= 16666;
        sLogicUpdateRate = LOGIC_60FPS;
        while (sTotalTime > 16666) {
            sTotalTime -= 16666;
            sLogicUpdateRate++;
            if (sLogicUpdateRate == 4) {
                sTotalTime = 0;
            }
            if (sLogicUpdateRate > D_801262E4) {
                sLogicUpdateRate = D_801262E4;
            }

        }
    }*/

    sLogicUpdateRate = calculate_updaterate();

    if (!gDisableAA) {
        gOverrideTimer -= 40000;
        gOverrideTimer += MIN(OS_CYCLES_TO_USEC(sDeltaTime), 66666);
        if (gOverrideTimer <= -125000) {
            gOverrideTimer = -125000;
            if (gOverrideAA == TRUE) {
                gOverrideAA = FALSE;
                set_dither_filter();
            }
        }
        if (gOverrideTimer >= 125000) {
            gOverrideTimer = 125000;
            if (gOverrideAA == FALSE) {
                gOverrideAA = TRUE;
                set_dither_filter();
            }
        }
    }

    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gGameCurrMatrix = gMatrixHeap[gSPTaskNum];
    gGameCurrVertexList = gVertexHeap[gSPTaskNum];
    gGameCurrTriList = gTriangleHeap[gSPTaskNum];

    set_rsp_segment(&gCurrDisplayList, 0, 0);
    set_rsp_segment(&gCurrDisplayList, 1, (s32) gVideoLastFramebuffer);
    set_rsp_segment(&gCurrDisplayList, 2, (s32) gVideoLastDepthBuffer);
    set_rsp_segment(&gCurrDisplayList, 4, (s32) gVideoLastFramebuffer - 0x500);
    init_rsp(&gCurrDisplayList);
    init_rdp_and_framebuffer(&gCurrDisplayList);
    render_background(&gCurrDisplayList, (Matrix *) &gGameCurrMatrix, TRUE); 
    gSaveDataFlags = handle_save_data_and_read_controller(gSaveDataFlags, sLogicUpdateRate);
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

#ifdef PUPPYPRINT_DEBUG
    gPuppyPrint.mainTimerPoints[0][PP_PROFILER_DRAW] = osGetCount();
    if (gPuppyPrint.enabled) {
        render_profiler();
        count_triangles((u8*) gDisplayLists[gSPTaskNum], (u8*) gCurrDisplayList);
    }
    gPuppyPrint.mainTimerPoints[1][PP_PROFILER_DRAW] = osGetCount();
#endif
    profiler_snapshot(THREAD4_END);

    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);

    copy_viewports_to_stack();
    if (gDrawFrameTimer != 1) {
        if (gSkipGfxTask == FALSE) {
            wait_for_gfx_task();
        }
    } else {
        gDrawFrameTimer = 0;
    }
    gSkipGfxTask = FALSE;
    clear_free_queue();
    if (!gIsPaused) {
        disable_cutscene_camera();
    }
#ifdef PUPPYPRINT_DEBUG
    gPuppyPrint.mainTimerPoints[0][PP_PROFILER_CALC] = osGetCount();
    calculate_and_update_fps();
    puppyprint_calculate_average_times();
    perfIteration++;
    if (perfIteration == NUM_PERF_ITERATIONS - 1) {
        perfIteration = 0;
    }
    gPuppyPrint.mainTimerPoints[1][PP_PROFILER_CALC] = osGetCount();
#endif
    if (gDrawFrameTimer == 2) {
        framebufferSize = SCREEN_WIDTH * SCREEN_HEIGHT * 2;
        dmacopy_doubleword(gVideoLastFramebuffer, gVideoCurrFramebuffer, (s32) gVideoCurrFramebuffer + framebufferSize);
    }

    swap_framebuffer_when_ready();

    if (gDrawFrameTimer == 0) {
#ifndef FIFO_UCODE
        setup_ostask_xbus(gDisplayLists[gSPTaskNum], gCurrDisplayList, 0);
#else
    #ifdef PUPPYPRINT_DEBUG
        if (get_buttons_pressed_from_player(PLAYER_ONE) & D_JPAD) {
            gDisableAA ^= 1;
            set_dither_filter();
        }
    #endif
        if (suCodeSwitch == FALSE && IO_READ(DPC_BUFBUSY_REG) + IO_READ(DPC_CLOCK_REG) + IO_READ(DPC_TMEM_REG) && gExpansionPak) {
            setup_ostask_fifo(gDisplayLists[gSPTaskNum], gCurrDisplayList, 0);
        } else {
            setup_ostask_xbus(gDisplayLists[gSPTaskNum], gCurrDisplayList, 0);
        }
#endif
        gNumGfxTasksAtScheduler++;
        gSPTaskNum ^= 1;
    }
    if (gDrawFrameTimer) {
        gDrawFrameTimer--;
    }
}

void func_8006CAE4(s32 numPlayers, s32 trackID, Vehicle vehicle) {
    D_80123500 = numPlayers - 1;
    if (trackID == -1) {
        gPlayableMapId = get_track_id_to_load();
    } else {
        gPlayableMapId = trackID; // Unused, because arg1 is always -1.
    }
    load_level_game(gPlayableMapId, D_80123500, D_80123504, vehicle);
}

/**
 * Calls load_level() with the same arguments except for the cutsceneId,
 * which is the value at D_80123508. Also does some other stuff.
 * Used when ingame.
 */
void load_level_game(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId) {
    profiler_begin_timer();
    alloc_displaylist_heap(numberOfPlayers);
    set_free_queue_state(0);
    func_80065EA0();
    func_800C3048();
    load_level(levelId, numberOfPlayers, entranceId, vehicleId, D_80123508);
    func_8009ECF0(get_viewport_count());
    func_800AE728(8, 0x10, 0x96, 0x64, 0x32, 0);
    func_8001BF20();
    osSetTime(0);
    sPrevTime = 0;
    set_free_queue_state(2);
    func_80072298(1);
    puppyprint_log("Level [%s] loaded in %2.3fs.", get_level_name(levelId), OS_CYCLES_TO_USEC(osGetCount() - profiler_get_timer()) / 1000000.0f);
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
    
    if (get_buttons_pressed_from_player(0) & L_TRIG && !(get_buttons_held_from_player(0) & U_JPAD)) {
        s32 soundID;
        gHideHUD ^= 1;
        if (gHideHUD == 0) {
            soundID = SOUND_TING_HIGH;
        } else {
            soundID = SOUND_TING_LOW;
        }
        play_sound_global(soundID, NULL);
    }
#ifndef NO_ANTIPIRACY
    // Spam the start button, making the game unplayable because it's constantly paused.
    if (sAntiPiracyTriggered) {
        buttonPressedInputs |= START_BUTTON;
    }
#endif
    // Update all objects
    if (!gIsPaused) {
        func_80010994(updateRate);
        if (check_if_showing_cutscene_camera() == 0 || func_8001139C()) {
            if ((buttonPressedInputs & START_BUTTON) && (get_level_property_stack_pos() == 0) && (D_800DD390 == 0)
                && (sRenderContext == DRAW_GAME) && (gPostRaceViewPort == NULL) && (gLevelLoadTimer == 0) && (D_800DD398 == 0)) {
                buttonPressedInputs = 0;
                gIsPaused = TRUE;
                func_80093A40();
            }
        }
    } else {
        set_anti_aliasing(TRUE);
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
#ifdef PUPPYPRINT_DEBUG
    gPuppyPrint.mainTimerPoints[0][PP_LEVELGFX] = osGetCount();
#endif
    render_scene(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
#ifdef PUPPYPRINT_DEBUG
    gPuppyPrint.mainTimerPoints[1][PP_LEVELGFX] = osGetCount();
#endif
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
                clear_level_property_stack(); 
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
                clear_level_property_stack();
                buttonHeldInputs |= (L_TRIG | R_TRIG);
                break;
        }
    }
    init_rdp_and_framebuffer(&gCurrDisplayList);
    render_borders_for_multiplayer(&gCurrDisplayList);
    render_minimap_and_misc_hud(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, updateRate);
    //render_second_multiplayer_borders(&gCurrDisplayList);
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
            push_level_property_stack(ASSET_LEVEL_CENTRALAREAHUB, 0, VEHICLE_CAR, 0);
            push_level_property_stack(ASSET_LEVEL_WIZPIGAMULETSEQUENCE, 0, -1, 0xA);
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
                    gPlayableMapId = gNextMap;
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
        if (get_level_property_stack_pos() != 0) {
            pop_level_property_stack(&gPlayableMapId, &D_80123504, &i, &D_80123508);
            set_frame_blackout_timer();
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
        if (get_level_property_stack_pos()) {
            if (gLevelLoadTimer == 0) {
                i = func_800214C4();
                if ((i != 0) || ((buttonPressedInputs & A_BUTTON) && (sp3C != 0))) {
                    if (sp3C != 0) {
                        func_80000B28();
                    }
                    set_frame_blackout_timer();
                    pop_level_property_stack(&gPlayableMapId, &D_80123504, &i, &D_80123508);
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
            load_level_game(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
        } else {
            safe_mark_write_save_file(get_save_file_index());
            load_menu_with_level_background(MENU_TITLE, -1, 0);
        }
        D_801234FC = 0;
    }
    if (D_801234F8 != 0) {
        gPostRaceViewPort = NULL;
        func_8006CC14();
        load_level_game(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
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
 * Sets up and loads a level to be used in the background of the menu that's about to be set up.
 * Used for every kind of menu that's not ingame.
*/
void load_menu_with_level_background(s32 menuId, s32 levelId, s32 cutsceneId) {
    alloc_displaylist_heap(0);
    sRenderContext = DRAW_MENU;
    D_801234F0 = TRUE;
    set_sound_channel_volume(0, 32767);
    set_sound_channel_volume(1, 32767);
    set_sound_channel_volume(2, 32767);
    func_80065EA0();

    if (!gIsLoading) {
        gIsLoading = FALSE;
        if (levelId < 0) {
            gIsLoading = TRUE;
        } else {
            load_level_menu(levelId, -1, 0, VEHICLE_PLANE, cutsceneId);
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
 * Used for menus.
 */
void load_level_menu(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId) {
    profiler_begin_timer();
    set_free_queue_state(0);
    func_80065EA0();
    func_800C3048();
    load_level(levelId, numberOfPlayers, entranceId, vehicleId, cutsceneId);
    func_8009ECF0(get_viewport_count());
    func_800AE728(4, 4, 0x6E, 0x30, 0x20, 0);
    func_8001BF20();
    osSetTime(0);
    sPrevTime = 0;
    set_free_queue_state(2);
    puppyprint_log("Level (%s) (Menu) loaded in %2.3fs.", get_level_name(levelId), OS_CYCLES_TO_USEC(osGetCount() - profiler_get_timer()) / 1000000.0f);
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
#ifdef PUPPYPRINT_DEBUG
        gPuppyPrint.mainTimerPoints[0][PP_LEVELGFX] = osGetCount();
#endif
        render_scene(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
#ifdef PUPPYPRINT_DEBUG
        gPuppyPrint.mainTimerPoints[1][PP_LEVELGFX] = osGetCount();
#endif
        func_800C3440(updateRate);
        init_rdp_and_framebuffer(&gCurrDisplayList);
        //render_borders_for_multiplayer(&gCurrDisplayList);
        //render_second_multiplayer_borders(&gCurrDisplayList);
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
        load_level_game(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
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
                load_level_game(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
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
                load_level_game(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
                safe_mark_write_save_file(get_save_file_index());
                break;
            case 2:
                sRenderContext = DRAW_GAME;
                load_level_game(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
                break;
            case 3:
                sRenderContext = DRAW_GAME;
                gPlayableMapId = D_80121250[0];
                D_80123504 = D_80121250[15];
                D_80123508 = D_80121250[D_80121250[1] + 8];
                gLevelDefaultVehicleID = get_map_default_vehicle(gPlayableMapId);
                load_level_game(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
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
        load_level_game(gPlayableMapId, D_80123500, D_80123504, temp);
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
    Vehicle vehicleID = VEHICLE_PLANE;
    if (!gIsLoading) {
        func_8006DBE4();
        if (get_thread30_level_id_to_load() == 0) {
            gCurrDisplayList = gDisplayLists[gSPTaskNum];
            gDPFullSync(gCurrDisplayList++);
            gSPEndDisplayList(gCurrDisplayList++);
        }
    }
    if (levelId != (s32) SPECIAL_MAP_ID_NO_LEVEL) {
        switch (levelId) {
        case ASSET_LEVEL_TRICKYTOPS1:
            vehicleID = VEHICLE_TRICKY;
            break;
        case ASSET_LEVEL_BLUEY1:
            vehicleID = VEHICLE_BLUEY;
            break;
        case ASSET_LEVEL_BUBBLER1:
            vehicleID = VEHICLE_BUBBLER;
            break;
        case ASSET_LEVEL_SMOKEY1:
            vehicleID = VEHICLE_SMOKEY;
            break;
        case ASSET_LEVEL_WIZPIG1:
            vehicleID = VEHICLE_WIZPIG;
            break;
        case ASSET_LEVEL_CENTRALAREAHUB:
            vehicleID = VEHICLE_PLANE;
            break;
        default: 
            vehicleID = get_map_default_vehicle(levelId);
            if (vehicleID > VEHICLE_PLANE) {
                vehicleID = VEHICLE_PLANE;
            }
            break;
        }
        alloc_displaylist_heap(3);
        load_level_menu(levelId, numberOfPlayers, 0, vehicleID, cutsceneId);
        gIsLoading = FALSE;
        return;
    }
    gIsLoading = TRUE;
}

void calc_and_alloc_heap_for_settings(void) {
    s32 dataSize;
    u32 sizes[15];
    s32 numWorlds, numLevels;

    init_level_globals();
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
    for (i = 0; i < NUM_RACERS_1P; i++) {
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
    settings->cutsceneFlags = CUTSCENE_NONE;
    settings->tajFlags = 0;
    settings->ttAmulet = 0;
    settings->wizpigAmulet = 0;
}

/**
 * Return the global game settings.
 * This is where global game records and perferences are stored.
*/
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
    return gNMIMesgBuf;
}

/**
 * Returns the current map ID if ingame, since this var is only set ingame.
*/
s32 get_ingame_map_id(void) {
    return gPlayableMapId;
}

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
 * Official Name: mainSaveGame
 */
void force_mark_write_save_file(s32 saveFileIndex) {
    gSaveDataFlags &= ~SAVE_DATA_FLAG_WRITE_SAVE_FILE_NUMBER_BITS; //Wipe out bits 10 and 11
    gSaveDataFlags |= (SAVE_DATA_FLAG_WRITE_SAVE_DATA | ((saveFileIndex & 3) << 10)); //Set bit 6 and place saveFileIndex into bits 10 and 11
}

/**
 * Marks a flag to write a save file to flash as long as we're not in tracks mode, and we're in the draw game render context.
 * This should prevent save data from being overwritten outside of Adventure Mode.
 * Official Name: mainSaveGame2
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

//Always called after updating a value in sEepromSettings
void mark_write_eeprom_settings(void) {
    gSaveDataFlags |= SAVE_DATA_FLAG_WRITE_EEPROM_SETTINGS; // Set bit 9
}

/**
 * Allocates an amount of memory for the number of players passed in.
 */
void alloc_displaylist_heap(s32 numberOfPlayers) {
    s32 num;
    s32 totalSize;

    if (numberOfPlayers != gPrevPlayerCount) {
        gPrevPlayerCount = numberOfPlayers;
        num = numberOfPlayers;
        set_free_queue_state(0);
        free_from_memory_pool(gDisplayLists[0]);
        free_from_memory_pool(gDisplayLists[1]);
        totalSize =
            ((gNumF3dCmdsPerPlayer[num] * sizeof(Gwords)))
            + ((gNumHudMatPerPlayer[num] * sizeof(Matrix)))
            + ((gNumHudVertsPerPlayer[num] * sizeof(Vertex)))
            + ((gNumHudTrisPerPlayer[num] * sizeof(Triangle)));
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
            default_alloc_displaylist_heap();
        }
        gMatrixHeap[0] = (MatrixS *)((u8 *) gDisplayLists[0] + ((gNumF3dCmdsPerPlayer[num] * sizeof(Gwords))));
        gTriangleHeap[0] = (TriangleList *)((u8 *) gMatrixHeap[0] + ((gNumHudMatPerPlayer[num] * sizeof(Matrix))));
        gVertexHeap[0] = (Vertex *)((u8 *) gTriangleHeap[0] + ((gNumHudTrisPerPlayer[num] * sizeof(Triangle))));
        gMatrixHeap[1] = (MatrixS *)((u8 *) gDisplayLists[1] + ((gNumF3dCmdsPerPlayer[num] * sizeof(Gwords))));
        gTriangleHeap[1] = (TriangleList *)((u8 *) gMatrixHeap[1] + ((gNumHudMatPerPlayer[num] * sizeof(Matrix))));
        gVertexHeap[1] = (Vertex *)((u8 *) gTriangleHeap[1] + ((gNumHudTrisPerPlayer[num] * sizeof(Triangle))));
        gCurrNumF3dCmdsPerPlayer = gNumF3dCmdsPerPlayer[num];
        gCurrNumHudMatPerPlayer = gNumHudMatPerPlayer[num];
        gCurrNumHudTrisPerPlayer = gNumHudTrisPerPlayer[num];
        gCurrNumHudVertsPerPlayer = gNumHudVertsPerPlayer[num];
        set_free_queue_state(2);
    }
    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gGameCurrMatrix = gMatrixHeap[gSPTaskNum];
    gGameCurrTriList = gTriangleHeap[gSPTaskNum];
    gGameCurrVertexList = gVertexHeap[gSPTaskNum];

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
void default_alloc_displaylist_heap(void) {
    s32 numberOfPlayers;
    s32 totalSize;

    numberOfPlayers = FOUR_PLAYERS;
    gPrevPlayerCount = numberOfPlayers;
    totalSize = (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords))
        + (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix))
        + (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex))
        + (gNumHudTrisPerPlayer[numberOfPlayers] * sizeof(Triangle));

    gDisplayLists[0] = (Gfx *) allocate_from_main_pool_safe(totalSize, COLOUR_TAG_RED);
    gMatrixHeap[0] = (MatrixS *) ((u8 *) gDisplayLists[0] + (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords)));
    gVertexHeap[0] = (Vertex *) ((u8 *) gMatrixHeap[0] + (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix)));
    gTriangleHeap[0] = (TriangleList *) ((u8 *) gVertexHeap[0] + (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex)));

    gDisplayLists[1] = (Gfx *) allocate_from_main_pool_safe(totalSize, COLOUR_TAG_YELLOW);
    gMatrixHeap[1] = (MatrixS *) ((u8 *) gDisplayLists[1] + (gNumF3dCmdsPerPlayer[numberOfPlayers] * sizeof(Gwords)));
    gVertexHeap[1] = (Vertex *) ((u8 *) gMatrixHeap[1] + (gNumHudMatPerPlayer[numberOfPlayers] * sizeof(Matrix)));
    gTriangleHeap[1] = (TriangleList *) ((u8 *) gVertexHeap[1] + (gNumHudVertsPerPlayer[numberOfPlayers] * sizeof(Vertex)));

    gCurrNumF3dCmdsPerPlayer = gNumF3dCmdsPerPlayer[numberOfPlayers];
    gCurrNumHudMatPerPlayer = gNumHudMatPerPlayer[numberOfPlayers];
    gCurrNumHudTrisPerPlayer = gNumHudTrisPerPlayer[numberOfPlayers];
    gCurrNumHudVertsPerPlayer = gNumHudVertsPerPlayer[numberOfPlayers];
}

void func_8006F140(s32 arg0) {
    if (gLevelLoadTimer == 0) {
        gLevelLoadTimer = 40;
        D_80123524 = 0;
        if (arg0 == 1) { //FADE_BARNDOOR_HORIZONTAL?
            transition_begin(&gLevelFadeOutTransition);
        }
        if (arg0 == 3) { //FADE_CIRCLE?
            gLevelLoadTimer = 282;
            transition_begin(&D_800DD424);
        }
        if (arg0 == 4) { //FADE_WAVES?
            gLevelLoadTimer = 360;
            transition_begin(&D_800DD424);
        }
        if (arg0 == 0) { //FADE_FULLSCREEN?
            gLevelLoadTimer = 2;
        }
    }
}

void func_8006F254(void) {
    if (gLevelLoadTimer == 0) {
        transition_begin(&gLevelFadeOutTransition);
        gLevelLoadTimer = 40;
        D_80123524 = 2;
    }
}

/**
 * Check if all available trophy races and Wizpig 1 has been beaten, and if the cutscene has not yet played.
*/
void begin_lighthouse_rocket_cutscene(void) {
    if (gLevelLoadTimer == 0) {
        if ((gSettingsPtr->trophies & 0xFF) == 0xFF && !(gSettingsPtr->cutsceneFlags & CUTSCENE_LIGHTHOUSE_ROCKET) && gSettingsPtr->bosses & 1) {
            gSettingsPtr->cutsceneFlags |= CUTSCENE_LIGHTHOUSE_ROCKET;
            transition_begin(&gLevelFadeOutTransition);
            gLevelLoadTimer = 40;
            gNextMap = ASSET_LEVEL_ROCKETSEQUENCE;
            D_80123524 = 3;
        }
    }
}

/**
 * Begin a transition, then set the next level to the passed argument.
 * This is used only to warp to Future Fun Land from the hub area.
*/
void begin_level_teleport(s32 levelID) {
    if (gLevelLoadTimer == 0) {
        gNextMap = levelID;
        transition_begin(&gLevelFadeOutTransition);
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

/**
 * Sets the timer to delay drawing new frames.
 * When set to 2, the game will copy the previous framebuffer over to the next.
*/
void set_frame_blackout_timer(void) {
    gDrawFrameTimer = 2;
}

#if SKIP_INTRO == SKIP_TITLE
 #define BOOT_LVL MENU_TITLE
#elif SKIP_INTRO == SKIP_CHARACTER
 #define BOOT_LVL MENU_CHARACTER_SELECT
#elif SKIP_INTRO == SKIP_MENU
 #define BOOT_LVL MENU_GAME_SELECT
#else
 #define BOOT_LVL MENU_BOOT
#endif // SKIP_INTRO

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
#ifndef SKIP_INTRO
    sBootDelayTimer++;
#else
    sBootDelayTimer = 8;
#endif
    if (sBootDelayTimer >= 8) {
        load_menu_with_level_background(BOOT_LVL, 0x27, 2);
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

#ifndef NO_ANTIPIRACY
/**
 * Ran on boot, will make sure the CIC chip (CIC6103) is to spec. Will return true if it's all good, otherwise it returns false.
 * The intention of this function, is an attempt to check that the cartridge is a legitimate copy.
 * A false read, meaning you're caught running an illegitimate copy, will force the game to pause when you enter the world.
 */
s32 check_imem_validity(void) {
    if (IO_READ(SP_IMEM_START) != CIC_ID) {
        return FALSE;
    }
    return TRUE;
}
#endif