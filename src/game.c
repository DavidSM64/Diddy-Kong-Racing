#include "game.h"

#include "asset_enums.h"
#include "asset_loading.h"
#include "audio.h"
#include "audio_spatial.h"
#include "audiosfx.h"
#include "camera.h"
#include "common.h"
#include "joypad.h"
#include "lights.h"
#include "macros.h"
#include "memory.h"
#include "menu.h"
#include "objects.h"
#include "racer.h"
#include "rcp_dkr.h"
#include "save_data.h"
#include "set_rsp_segment.h"
#include "structs.h"
#include "textures_sprites.h"
#include "thread3_main.h"
#include "tracks.h"
#include "types.h"
#include "video.h"
#include "weather.h"

/************ .data ************/

char *gTempLevelNames = NULL;
s8 gCurrentDefaultVehicle = -1;
u8 gTwoPlayerAdvRace = FALSE;
s32 gIsInRace = 0;

// Updated automatically from calc_func_checksums.py
s32 gViewportFuncChecksum = ViewportFuncChecksum;
s32 gViewportFuncLength = 0x154;
s16 gLevelPropertyStackPos = 0;
s16 D_800DD32C = 0;
s8 D_800DD330 = 0;

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
s32 gRaceTypeCountTable[16];
AIBehaviourTable *gAIBehaviourTable;
s16 gLevelPropertyStack[5 * 4]; // Stores level info for cutscenes. 5 sets of four properties.

/******************************/

/**
 * Allocates memory for gGlobalLevelTable, then populates it with relevant data from every level header.
 * The level headers are streamed from ROM.
 * Additionally loads other globally accessed information, like level names, then runs a checksum compare, for good
 * measure.
 */
void level_global_init(void) {
    s32 i;
    s32 size;
    UNUSED s32 pad;
    s32 checksumCount;
    u8 *header;
    s32 j;
    header = mempool_alloc_safe(sizeof(LevelHeader), COLOUR_TAG_YELLOW);
    gTempAssetTable = (s32 *) asset_table_load(ASSET_LEVEL_HEADERS_TABLE);
    i = 0;
    while (i < 16) {
        gRaceTypeCountTable[i++] = 0;
    }
    gNumberOfLevelHeaders = 0;
    while (gTempAssetTable[gNumberOfLevelHeaders] != -1) {
        gNumberOfLevelHeaders++;
    }
    gNumberOfLevelHeaders--;
    gGlobalLevelTable = mempool_alloc_safe(gNumberOfLevelHeaders * sizeof(LevelGlobalData), COLOUR_TAG_YELLOW);
    gCurrentLevelHeader = (LevelHeader *) header;
    gNumberOfWorlds = -1;
    for (i = 0; i < gNumberOfLevelHeaders; i++) {
        asset_load(ASSET_LEVEL_HEADERS, (u32) gCurrentLevelHeader, gTempAssetTable[i], sizeof(LevelHeader));
        if (gNumberOfWorlds < gCurrentLevelHeader->world) {
            gNumberOfWorlds = gCurrentLevelHeader->world;
        }
        if ((gCurrentLevelHeader->race_type >= 0) && (gCurrentLevelHeader->race_type < 16)) {
            gRaceTypeCountTable[gCurrentLevelHeader->race_type]++;
        }
        gGlobalLevelTable[i].world = gCurrentLevelHeader->world;
        gGlobalLevelTable[i].raceType = gCurrentLevelHeader->race_type;
        gGlobalLevelTable[i].vehicles = ((u16) gCurrentLevelHeader->available_vehicles) << 4;
        gGlobalLevelTable[i].vehicles |= gCurrentLevelHeader->vehicle & 0xF;
        gGlobalLevelTable[i].unk3 = 1;
        gGlobalLevelTable[i].unk4 = gCurrentLevelHeader->unkB0;
    }
    gNumberOfWorlds++;
    D_80121178 = mempool_alloc_safe(gNumberOfWorlds, COLOUR_TAG_YELLOW);
    for (i = 0; i < gNumberOfWorlds; i++) {
        D_80121178[i] = -1;
    }
    for (i = 0; i < gNumberOfLevelHeaders; i++) {
        if (gGlobalLevelTable[i].raceType == 5) {
            D_80121178[gGlobalLevelTable[i].world] = i;
        }
    }
    mempool_free(gTempAssetTable);
    mempool_free(header);
    gTempAssetTable = (s32 *) asset_table_load(ASSET_LEVEL_NAMES_TABLE);
    for (i = 0; gTempAssetTable[i] != (-1); i++) {}
    i--;
    size = gTempAssetTable[i] - gTempAssetTable[0];
    gLevelNames = mempool_alloc_safe(i * sizeof(s32), COLOUR_TAG_YELLOW);
    gTempLevelNames = mempool_alloc_safe(size, COLOUR_TAG_YELLOW);
    asset_load(ASSET_LEVEL_NAMES, (u32) gTempLevelNames, 0, size);
    for (size = 0; size < i; size++) {
        gLevelNames[size] = (char *) &gTempLevelNames[gTempAssetTable[size]];
    }
    mempool_free(gTempAssetTable);
    // Antipiracy measure
#ifdef ANTI_TAMPER
    checksumCount = 0;
    for (j = 0; j < gViewportFuncLength; j++) {
        checksumCount += ((u8 *) (&viewport_rsp_set))[j];
    }
    if (checksumCount != gViewportFuncChecksum) {
        drm_disable_input();
    }
#endif
}

UNUSED s16 func_8006ABB4(s32 levelID) {
    if (levelID < 0) {
        return 0xE10;
    }
    if (levelID >= gNumberOfLevelHeaders) {
        return 0xE10;
    }
    return gGlobalLevelTable[levelID].unk4;
}

/**
 * Iterates through the level property table and attempts to find a level ID that matches the properties you want.
 * Iterates Forwards.
 */
UNUSED s32 search_level_properties_forwards(s32 levelID, s8 raceType, s8 worldID) {
    if (levelID < 0) {
        levelID = 0;
    } else {
        levelID++;
    }
    if (raceType != RACETYPE_CHALLENGE) {
        if (worldID == -1) {
            for (; levelID < gNumberOfLevelHeaders; levelID++) {
                if (raceType == gGlobalLevelTable[levelID].raceType) {
                    return levelID;
                }
            }
        } else if (raceType == -1) {
            for (; levelID < gNumberOfLevelHeaders; levelID++) {
                if (worldID == gGlobalLevelTable[levelID].world) {
                    return levelID;
                }
            }
        } else {
            for (; levelID < gNumberOfLevelHeaders; levelID++) {
                if ((raceType == gGlobalLevelTable[levelID].raceType) &&
                    (worldID == gGlobalLevelTable[levelID].world)) {
                    return levelID;
                }
            }
        }
    } else {
        if (worldID == -1) {
            for (; levelID < gNumberOfLevelHeaders; levelID++) {
                if (gGlobalLevelTable[levelID].raceType & RACETYPE_CHALLENGE) {
                    return levelID;
                }
            }
        } else {
            for (; levelID < gNumberOfLevelHeaders; levelID++) {
                if ((gGlobalLevelTable[levelID].raceType & RACETYPE_CHALLENGE) &&
                    (worldID == gGlobalLevelTable[levelID].world)) {
                    return levelID;
                }
            }
        }
    }
    return -1;
}

/**
 * Iterates through the level property table and attempts to find a level ID that matches the properties you want.
 * Iterates Backwards.
 */
UNUSED s32 search_level_properties_backwards(s32 levelID, s8 raceType, s8 worldID) {
    if (levelID >= gNumberOfLevelHeaders) {
        levelID = gNumberOfLevelHeaders;
    }
    levelID--;
    if (raceType != RACETYPE_CHALLENGE) {
        if (worldID == -1) {
            for (; levelID >= 0; levelID--) {
                if (raceType == gGlobalLevelTable[levelID].raceType) {
                    return levelID;
                }
            }
        } else if (raceType == -1) {
            for (; levelID >= 0; levelID--) {
                if (worldID == gGlobalLevelTable[levelID].world) {
                    return levelID;
                }
            }
        } else {
            for (; levelID >= 0; levelID--) {
                if ((raceType == gGlobalLevelTable[levelID].raceType) &&
                    (worldID == gGlobalLevelTable[levelID].world)) {
                    return levelID;
                }
            }
        }
    } else {
        if (worldID == -1) {
            for (; levelID >= 0; levelID--) {
                if (gGlobalLevelTable[levelID].raceType & RACETYPE_CHALLENGE) {
                    return levelID;
                }
            }
        } else {
            for (; levelID >= 0; levelID--) {
                if ((gGlobalLevelTable[levelID].raceType & RACETYPE_CHALLENGE) &&
                    (worldID == gGlobalLevelTable[levelID].world)) {
                    return levelID;
                }
            }
        }
    }
    return -1;
}

/**
 * Return the number of tracks that aren't challenge maps.
 */
UNUSED s32 leveltable_non_challenge_count(s8 raceType) {
    if (raceType >= RACETYPE_DEFAULT && raceType < 16) {
        return gRaceTypeCountTable[raceType];
    }
    return 0;
}

/**
 * Returns the number of levels that belong to one hub world.
 */
UNUSED s32 leveltable_world_level_count(s8 worldID) {
    s32 out, i;
    out = 0;
    for (i = 0; i < gNumberOfLevelHeaders; i++) {
        if (worldID == gGlobalLevelTable[i].world) {
            out++;
        }
    }
    return out;
}

/**
 * Returns the default vehicle from the set map ID.
 */
Vehicle leveltable_vehicle_default(s32 mapId) {
    if (mapId > 0 && mapId < gNumberOfLevelHeaders) {
        return gGlobalLevelTable[mapId].vehicles & 0xF;
    }
    return VEHICLE_CAR;
}

/**
 * Returns the available vehicles from the set map ID.
 */
s32 leveltable_vehicle_usable(s32 mapId) {
    if (mapId > 0 && mapId < gNumberOfLevelHeaders) {
        s32 temp = gGlobalLevelTable[mapId].vehicles;
        if (temp != 0) {
            return (temp >> 4) & 0xF;
        }
    }
    return (1 << VEHICLE_CAR);
}

/**
 * Returns the race type from the set map ID.
 */
s8 leveltable_type(s32 mapId) {
    if (mapId >= 0 && mapId < gNumberOfLevelHeaders) {
        return gGlobalLevelTable[mapId].raceType;
    }
    return -1;
}

/**
 * Returns the world ID from the set map ID.
 */
s8 leveltable_world(s32 mapId) {
    if (mapId >= 0 && mapId < gNumberOfLevelHeaders) {
        return gGlobalLevelTable[mapId].world;
    }
    return 0;
}

/**
 * Returns the ID of the current hub world. Example: Dino Domain.
 */
s32 level_world_id(s32 worldId) {
    s8 *hubAreaIds;

    if (worldId < 0 || worldId >= gNumberOfWorlds) {
        worldId = 0;
    }
    hubAreaIds = (s8 *) get_misc_asset(ASSET_MISC_HUB_AREA_IDS);

    return hubAreaIds[worldId];
}

/**
 * Writes the level and hub count to the two arguments passed through.
 */
void level_count(s32 *outLevelCount, s32 *outWorldCount) {
    *outLevelCount = gNumberOfLevelHeaders;
    *outWorldCount = gNumberOfWorlds;
}

/**
 * Returns true if the current event is a regular race or a boss race.
 * Returns false if it's a menu, challenge or hubworld.
 */
s32 level_is_race(void) {
    return gIsInRace;
}

/**
 * Loads and sets up the level header, then loads and sets of the level geometry.
 * Sets weather, fog and active cutscenes where applicable.
 * Official Name: levelInit
 */
void level_load(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId) {
    s8 *someAsset;
    s32 i;
    s32 size;
    s32 var_s0;
    s32 wizpig;
    s32 numPlayers;
    s32 prevLevelID;
    Settings *settings;
    s32 offset;

    rumble_kill();
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
        sndp_set_active_sound_limit(8);
    } else if (numberOfPlayers == TWO_PLAYERS) {
        sndp_set_active_sound_limit(12);
    } else {
        sndp_set_active_sound_limit(16);
    }
    settings = get_settings();
    gTempAssetTable = (s32 *) asset_table_load(ASSET_LEVEL_HEADERS_TABLE);

    for (i = 0; gTempAssetTable[i] != -1; i++) {}
    i--;
    if (levelId >= i) {
        stubbed_printf("LOADLEVEL Error: Level out of range\n");
        levelId = ASSET_LEVEL_CENTRALAREAHUB;
    }

    offset = gTempAssetTable[levelId];
    size = gTempAssetTable[levelId + 1] - offset;
    gCurrentLevelHeader = (LevelHeader *) mempool_alloc_safe(size, COLOUR_TAG_YELLOW);
    asset_load(ASSET_LEVEL_HEADERS, (u32) gCurrentLevelHeader, offset, size);
    D_800DD330 = 0;
    prevLevelID = levelId;
    if (gCurrentLevelHeader->race_type == RACETYPE_DEFAULT) {
        level_properties_reset();
    }
    if (level_properties_get() == 0 && D_800DD32C == 0) {
        if (gCurrentLevelHeader->race_type == RACETYPE_BOSS) {
            var_s0 = settings->courseFlagsPtr[levelId];
            wizpig = FALSE;
            if (gCurrentLevelHeader->world == WORLD_CENTRAL_AREA ||
                gCurrentLevelHeader->world == WORLD_FUTURE_FUN_LAND) {
                wizpig = TRUE;
            }
            if (!(var_s0 & 1) || wizpig) {
                level_properties_push(levelId, entranceId, vehicleId, cutsceneId);
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
                someAsset = (s8 *) get_misc_asset(ASSET_MISC_67);
                for (var_s0 = 0; levelId != someAsset[var_s0]; var_s0 += 2) {}
                levelId = someAsset[var_s0 + 1];
                entranceId = cutsceneId;
                if (cutsceneId == CUTSCENE_NONE) {
                    stubbed_printf("BossLev problem\n");
                }
            }
        }
        if (gCurrentLevelHeader->race_type == RACETYPE_HUBWORLD) {
            if (gCurrentLevelHeader->world > WORLD_CENTRAL_AREA && gCurrentLevelHeader->world < WORLD_FUTURE_FUN_LAND) {
                var_s0 = gCurrentLevelHeader->world;
                if (settings->keys & (1 << var_s0) &&
                    !(settings->cutsceneFlags & (CUTSCENE_DINO_DOMAIN_KEY << (var_s0 + 31)))) {
                    // Trigger World Key unlocking Challenge Door cutscene.
                    level_properties_push(levelId, entranceId, vehicleId, cutsceneId);
                    settings->cutsceneFlags |= CUTSCENE_DINO_DOMAIN_KEY << (var_s0 + 31);
                    someAsset = (s8 *) get_misc_asset(ASSET_MISC_68);
                    levelId = someAsset[var_s0 - 1];
                    entranceId = 0;
                    cutsceneId = CUTSCENE_ID_UNK_5;
                }
            }
        }
        if (gCurrentLevelHeader->race_type == RACETYPE_HUBWORLD && gCurrentLevelHeader->world == WORLD_CENTRAL_AREA &&
            !(settings->cutsceneFlags & CUTSCENE_WIZPIG_FACE) && settings->wizpigAmulet >= 4) {
            // Trigger wizpig face cutscene
            level_properties_push(levelId, entranceId, vehicleId, cutsceneId);
            entranceId = 0;
            cutsceneId = CUTSCENE_NONE;
            settings->cutsceneFlags |= CUTSCENE_WIZPIG_FACE;
            levelId = ((s8 *) get_misc_asset(ASSET_MISC_68))[4];
        }
    }
    D_800DD32C = 0;
    if (prevLevelID != levelId) {
        mempool_free(gCurrentLevelHeader);
        offset = gTempAssetTable[levelId];
        size = gTempAssetTable[levelId + 1] - offset;
        gCurrentLevelHeader = mempool_alloc_safe(size, COLOUR_TAG_YELLOW);
        asset_load(ASSET_LEVEL_HEADERS, (u32) gCurrentLevelHeader, offset, size);
    }
    mempool_free(gTempAssetTable);
    aitable_init((s8 *) &gCurrentLevelHeader->AILevelTable);
    func_8000CBC0();
    gMapId = levelId;
    for (var_s0 = 0; var_s0 < 7; var_s0++) {
        if ((s32) gCurrentLevelHeader->unk74[var_s0] != -1) {
            gCurrentLevelHeader->unk74[var_s0] =
                (LevelHeader_70 *) get_misc_asset((s32) gCurrentLevelHeader->unk74[var_s0]);
            func_8007F1E8((LevelHeader_70 *) gCurrentLevelHeader->unk74[var_s0]);
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
    music_voicelimit_set(gCurrentLevelHeader->voiceLimit);
    music_volume_reset();
    lights_init(32);
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
    if (var_s0 == WORLD_CENTRAL_AREA && settings->worldId > 0) {
        gCurrentDefaultVehicle = get_level_default_vehicle();
    }
    if (settings->worldId == WORLD_CENTRAL_AREA && var_s0 > 0 && gCurrentDefaultVehicle != -1) {
        vehicleId = gCurrentDefaultVehicle;
    }
    set_vehicle_id_for_menu(vehicleId);
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

    var_s0 = settings->courseFlagsPtr[levelId]; // Redundant
    if (numberOfPlayers != ONE_PLAYER && gCurrentLevelHeader->race_type == RACETYPE_DEFAULT) {
        cutsceneId = CUTSCENE_ID_UNK_64;
    }
    if ((gCurrentLevelHeader->race_type == RACETYPE_DEFAULT || gCurrentLevelHeader->race_type & RACETYPE_CHALLENGE) &&
        is_in_two_player_adventure()) {
        gTwoPlayerAdvRace = TRUE;
        cutsceneId = CUTSCENE_ID_UNK_64;
    } else {
        gTwoPlayerAdvRace = FALSE;
    }
    if (gCurrentLevelHeader->race_type == RACETYPE_DEFAULT && numPlayers == 0 && is_time_trial_enabled()) {
        cutsceneId = CUTSCENE_ID_UNK_64;
    }
    cutscene_id_set(cutsceneId);
    init_track(gCurrentLevelHeader->geometry, gCurrentLevelHeader->skybox, numberOfPlayers, vehicleId, entranceId,
               gCurrentLevelHeader->collectables, gCurrentLevelHeader->unkBA);
    if (gCurrentLevelHeader->fogNear == 0 && gCurrentLevelHeader->fogFar == 0 && gCurrentLevelHeader->fogR == 0 &&
        gCurrentLevelHeader->fogG == 0 && gCurrentLevelHeader->fogB == 0) {
        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            reset_fog(var_s0);
        }
    } else {
        for (var_s0 = 0; var_s0 < 4; var_s0++) {
            set_fog(var_s0, gCurrentLevelHeader->fogNear, gCurrentLevelHeader->fogFar, (u8) gCurrentLevelHeader->fogR,
                    gCurrentLevelHeader->fogG, gCurrentLevelHeader->fogB);
        }
    }
    settings = get_settings();
    if (gCurrentLevelHeader->world != -1) {
        settings->worldId = gCurrentLevelHeader->world;
    }
    settings->courseId = levelId;
    if (gCurrentLevelHeader->weatherEnable > 0) {
        weather_reset(gCurrentLevelHeader->weatherType, gCurrentLevelHeader->weatherEnable,
                      gCurrentLevelHeader->weatherVelX << 8, gCurrentLevelHeader->weatherVelY << 8,
                      gCurrentLevelHeader->weatherVelZ << 8, gCurrentLevelHeader->weatherIntensity * 257,
                      gCurrentLevelHeader->weatherOpacity * 257);
        weather_clip_planes(-1, -512);
    }
    if (gCurrentLevelHeader->skyDome == -1) {
        gCurrentLevelHeader->unkA4 = load_texture((s32) gCurrentLevelHeader->unkA4);
        gCurrentLevelHeader->unkA8 = 0;
        gCurrentLevelHeader->unkAA = 0;
    }
    if ((s32) gCurrentLevelHeader->pulseLightData != -1) {
        gCurrentLevelHeader->pulseLightData =
            (PulsatingLightData *) get_misc_asset((s32) gCurrentLevelHeader->pulseLightData);
        init_pulsating_light_data(gCurrentLevelHeader->pulseLightData);
    }
    cam_set_fov(gCurrentLevelHeader->cameraFOV);
    bgdraw_primcolour(gCurrentLevelHeader->bgColorRed, gCurrentLevelHeader->bgColorGreen,
                      gCurrentLevelHeader->bgColorBlue);
    video_delta_reset();
    func_8007AB24(gCurrentLevelHeader->unk4[numberOfPlayers]);
}

/**
 * If the level's music ID is nonzero, set the current background music.
 */
void level_music_start(f32 tempo) {
    if (gCurrentLevelHeader->music != SEQUENCE_NONE) {
        music_channel_reset_all();
        music_play(gCurrentLevelHeader->music);
        music_tempo_set_relative(tempo);
        music_dynamic_set(gCurrentLevelHeader->instruments);
    }
}

/**
 * Return the current map ID.
 */
s32 level_id(void) {
    return gMapId;
}

/**
 * Return the race type ID of the current level.
 * Official name: levelGetType
 */
u8 level_type(void) {
    return gCurrentLevelHeader->race_type;
}

/**
 * Return the header data of the current level.
 * Official Name: levelGetLevel
 */
LevelHeader *level_header(void) {
    return gCurrentLevelHeader;
}

/**
 * Returns the amount of level headers there are in the game.
 */
UNUSED u8 level_header_count(void) {
    return gNumberOfLevelHeaders - 1;
}

/**
 * Returns the name of the level from the passed ID
 */
char *level_name(s32 levelId) {
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

/**
 * Call multiple functions to stop and free audio, then free track, weather and wave data.
 */
void level_free(void) {
    aitable_free();
    bgdraw_primcolour(0, 0, 0);
    mempool_free(gCurrentLevelHeader);
    sndp_stop_all_looped();
    music_stop();
    music_jingle_stop();
    music_channel_reset_all();
    lights_free();
    free_track();
    audspat_reset();
    sound_volume_change(VOLUME_NORMAL);
    if (gCurrentLevelHeader->weatherEnable > 0) {
        weather_free();
    }
    //! @bug this will never be true because skyDome is signed.
    if (gCurrentLevelHeader->skyDome == 0xFF) {
        tex_free(gCurrentLevelHeader->unkA4);
    }
}

/**
 * Set the skill level of the AI.
 * Apply offsets based on game mode.
 */
void aitable_init(s8 *aiLevelTable) {
    s32 temp;
    UNUSED s32 temp2;
    s16 tableIndexCount;
    s8 aiLevel;
    Settings *settings;

    aiLevel = 0;
    if (is_in_tracks_mode() == FALSE) {
        settings = get_settings();
        temp = settings->courseFlagsPtr[settings->courseId];
        if (temp & 2) {
            aiLevel = 1;
        }
        if (temp & 4) {
            aiLevel = 2;
        }
    } else {
        aiLevel = 3;
    }
    if (get_trophy_race_world_id()) {
        aiLevel = 4;
    }
    if (is_in_adventure_two()) {
        aiLevel += 5;
    }
    aiLevel = aiLevelTable[aiLevel];
    if (get_filtered_cheats() & CHEAT_ULTIMATE_AI) {
        aiLevel = 9;
    }
    if (get_game_mode() == GAMEMODE_MENU) {
        aiLevel = 5;
    }
    gTempAssetTable = (s32 *) asset_table_load(ASSET_AI_BEHAVIOUR_TABLE);
    tableIndexCount = 0;
    while (-1 != (s32) gTempAssetTable[tableIndexCount]) {
        tableIndexCount++;
    }
    tableIndexCount--;
    if (aiLevel >= tableIndexCount) {
        stubbed_printf("AITABLE Error: Table out of range\n");
        aiLevel = 0;
    }
    temp2 = gTempAssetTable[aiLevel];
    temp = gTempAssetTable[aiLevel + 1] - temp2;
    gAIBehaviourTable = mempool_alloc_safe(temp, COLOUR_TAG_YELLOW);
    asset_load(ASSET_AI_BEHAVIOUR, (u32) gAIBehaviourTable, temp2, temp);
    mempool_free(gTempAssetTable);
}

/**
 * Frees the AI behaviour table from memory.
 */
void aitable_free(void) {
    mempool_free(gAIBehaviourTable);
}

/**
 * Return the behaviour value table for AI racers.
 */
AIBehaviourTable *aitable_get(void) {
    return gAIBehaviourTable;
}

/**
 * Return whether it is a standard race with two players in adventure mode.
 */
s8 race_is_adventure_2P(void) {
    return gTwoPlayerAdvRace;
}

/**
 * Pushes the current level data onto a stack.
 * Used for preserving certain properties when viewing cutscenes, where this information would otherwise be lost.
 */
void level_properties_push(s32 levelId, s32 entranceId, Vehicle vehicleId, s32 cutsceneId) {
    gLevelPropertyStack[gLevelPropertyStackPos++] = levelId;
    gLevelPropertyStack[gLevelPropertyStackPos++] = entranceId;
    gLevelPropertyStack[gLevelPropertyStackPos++] = vehicleId;
    gLevelPropertyStack[gLevelPropertyStackPos++] = cutsceneId;
}

/**
 * Reads the level data from the stack, then pops it.
 * Used after cutscenes to properly restore the previous level status.
 */
void level_properties_pop(s32 *levelId, s32 *entranceId, s32 *vehicleId, s32 *cutsceneId) {
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
void level_properties_reset(void) {
    gLevelPropertyStackPos = 0;
}

/**
 * Returns the position of the level property stack.
 * Should always return a multiple of 4.
 */
s16 level_properties_get(void) {
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
