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
#include "thread30.h"
#include "weather.h"
#include "audio.h"
#include "objects.h"
#include "camera.h"
#include "save_data.h"
#include "unknown_078050.h"
#include "unknown_003260.h"
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
s8 D_800DD314 = -1;
u8 D_800DD318 = 0;
s32 D_800DD31C = 0;

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
s32 D_800DD37C = 0;
s32 gScreenStatus = OSMESG_SWAP_BUFFER;
s32 sControllerStatus = 0;
UNUSED s32 D_800DD388 = 0;
s8 gSkipGfxTask = FALSE;
s8 D_800DD390 = 0;
s16 gLevelLoadTimer = 0;
s8 D_800DD398 = 0;
s8 D_800DD39C = 0;
s8 D_800DD3A0 = FALSE;
UNUSED s32 D_800DD3A4 = 0;
UNUSED s32 D_800DD3A8 = 0;
UNUSED s32 D_800DD3AC = 0;
s32 gNumF3dCmdsPerPlayer[4] = { 4500, 7000, 11000, 11000 };
s32 gNumHudVertsPerPlayer[4] = { 300, 600, 850, 900 };
s32 gNumHudMatPerPlayer[4] = { 300, 400, 550, 600 };
s32 gNumHudTrisPerPlayer[4] = { 20, 30, 40, 50 };
s8 gDrawFrameTimer = 0;
FadeTransition D_800DD3F4 = FADE_TRANSITION(128, FADE_COLOR_BLACK, 20, 0);
// Unused?
FadeTransition D_800DD3FC = FADE_TRANSITION(0, FADE_COLOR_WHITE, 20, -1);
s32 sLogicUpdateRate = LOGIC_5FPS;
FadeTransition D_800DD408 = FADE_TRANSITION(0, FADE_COLOR_WHITE, 30, -1);
// Unused?
// CAR / HOV / PLN - So this is vehicle type?
UNUSED char *D_800DD410[3] = {
    (char *)sDebugCarString, (char *)sDebugHovercraftString, (char *)sDebugPlaneString
};
FadeTransition D_800DD41C = FADE_TRANSITION(0, FADE_COLOR_BLACK, 30, -1);
FadeTransition D_800DD424 = FADE_TRANSITION(0, FADE_COLOR_BLACK, 260, -1);
/*******************************/

extern s32 gShowControllerPakMenu;

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
UNUSED u8 D_80121268[0x2000]; // 0x2000 / 8192 bytes Padding?
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

#ifdef NON_EQUIVALENT
// Only has regalloc issues.
void func_8006A6B0(void) {
  s32 i;
  s32 temp;
  s32 count;
  s32 checksumCount;
  u8 *sp44;
  UNUSED s32 temp2;

  sp44 = allocate_from_main_pool_safe(sizeof(LevelHeader), COLOUR_TAG_YELLOW);
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
  gCurrentLevelHeader = (LevelHeader *) sp44;
  gNumberOfWorlds = -1;
  for (i = 0; i < gNumberOfLevelHeaders; i++) {
    load_asset_to_address(ASSET_LEVEL_HEADERS, (s32) gCurrentLevelHeader, gTempAssetTable[i], sizeof(LevelHeader));
    if (gNumberOfWorlds < gCurrentLevelHeader->world) {
      gNumberOfWorlds = gCurrentLevelHeader->world;
    }
    if ((gCurrentLevelHeader->race_type >= 0) && (gCurrentLevelHeader->race_type < 16)) {
      D_80121180[gCurrentLevelHeader->race_type]++;
    }
    D_8012117C[i].unk0 = gCurrentLevelHeader->world;
    D_8012117C[i].unk1 = gCurrentLevelHeader->race_type;
    D_8012117C[i].unk2 = ((u16)gCurrentLevelHeader->available_vehicles) << 4;
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
    if ((D_8012117C[i].unk1 == 5) != 0) {
      D_80121178[D_8012117C[i].unk0] = i;
    }
  }
  free_from_memory_pool(gTempAssetTable);
  free_from_memory_pool(sp44);

  gTempAssetTable = (s32 *) load_asset_section_from_rom(ASSET_LEVEL_NAMES_TABLE);

  for (i = 0; gTempAssetTable[i] != (-1); i++){}
  i--;

  temp = gTempAssetTable[i];
  temp -= gTempAssetTable[0];

  gLevelNames = allocate_from_main_pool_safe(i * sizeof(s32), COLOUR_TAG_YELLOW);
  D_800DD310 = allocate_from_main_pool_safe(temp, COLOUR_TAG_YELLOW);
  load_asset_to_address(ASSET_LEVEL_NAMES, (u32) D_800DD310, 0, temp);
  for (count = 0; count < i; count++) {
    gLevelNames[count] = (char *) &D_800DD310[gTempAssetTable[count]];
  }
  free_from_memory_pool(gTempAssetTable);

  checksumCount = 0;
  for (i = 0; i < gFunc80068158Length; i++) {
    checksumCount += ((u8 *) (&func_80068158))[i];
  }
  if (checksumCount != gFunc80068158Checksum) {
    disable_button_mask();
  }
}
#else
GLOBAL_ASM("asm/non_matchings/game/func_8006A6B0.s")
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
GLOBAL_ASM("asm/non_matchings/game/func_8006AC00.s")

// Unused?
GLOBAL_ASM("asm/non_matchings/game/func_8006AE2C.s")

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

s32 func_8006B240(void) {
    return D_800DD31C;
}

// This isn't matching, but there shouldn't be any issues (hopefully).
#ifdef NON_EQUIVALENT

void load_level(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId) {
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
        set_sound_channel_count(8);
    } else if (numberOfPlayers == TWO_PLAYERS) {
        set_sound_channel_count(12);
    } else {
        set_sound_channel_count(16);
    }

    settings = get_settings();
    gTempAssetTable = load_asset_section_from_rom(ASSET_LEVEL_HEADERS_TABLE);
    maxLevelCount = 0;
    while (gTempAssetTable[maxLevelCount] != -1) {
        maxLevelCount++;
    }
    maxLevelCount--;
    if (levelId >= maxLevelCount) {
        levelId = ASSET_LEVEL_CENTRALAREAHUB;
    }
    offset = gTempAssetTable[levelId];
    size = gTempAssetTable[levelId + 1] - offset;
    gCurrentLevelHeader = (LevelHeader *)allocate_from_main_pool_safe(size, COLOUR_TAG_YELLOW);
    load_asset_to_address(ASSET_LEVEL_HEADERS, gCurrentLevelHeader, offset, size);
    D_800DD330 = 0;
    sp44 = levelId;
    if (gCurrentLevelHeader->race_type == RACETYPE_DEFAULT) {
        func_8006C2E4();
    }
    if (func_8006C2F0() == 0) {
        if (D_800DD32C == 0) {
            if (gCurrentLevelHeader->race_type == RACETYPE_BOSS) {
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
                    someAsset = get_misc_asset(MISC_ASSET_UNK43);
                    phi_s0 = 0;
                    while (levelId != someAsset[phi_s0 + 1]) {
                        phi_s0++;
                    }
                    levelId = someAsset[phi_s0 + 1];
                    entranceId = cutsceneId;
                }
            }
            if (gCurrentLevelHeader->race_type == RACETYPE_HUBWORLD) {
                s32 curWorld = gCurrentLevelHeader->world;
                if (curWorld > 0 && curWorld < 5) {
                    if (settings->keys & (1 << curWorld)) {
                        s32 temp_v0_5 = 0x4000 << (curWorld + 0x1F);
                        if (!(settings->cutsceneFlags & temp_v0_5)) {
                            // Trigger World Key unlocking Challenge Door cutscene.
                            func_8006C1AC(levelId, entranceId, vehicleId, cutsceneId);
                            settings->cutsceneFlags |= temp_v0_5;
                            levelId = get_misc_asset(MISC_ASSET_UNK44)[curWorld - 1];
                            entranceId = 0;
                            cutsceneId = 5;
                        }
                    }
                }
            }
            if (gCurrentLevelHeader->race_type == RACETYPE_HUBWORLD && gCurrentLevelHeader->world == 0 && !(settings->cutsceneFlags & CUTSCENE_WIZPIG_FACE) && settings->wizpigAmulet >= 4) {
                // Trigger wizpig face cutscene
                s32 savedEntranceId = entranceId;
                s32 savedCutsceneId = cutsceneId;
                cutsceneId = 0;
                entranceId = 0;
                func_8006C1AC(levelId, savedEntranceId, vehicleId, savedCutsceneId);
                settings->cutsceneFlags |= CUTSCENE_WIZPIG_FACE;
                levelId = get_misc_asset(MISC_ASSET_UNK44)[1];
            }
        }
    }
    D_800DD32C = 0;
    if (sp44 != levelId) {
        free_from_memory_pool(gCurrentLevelHeader);
        offset = gTempAssetTable[levelId];
        size = gTempAssetTable[levelId + 1] - offset;
        gCurrentLevelHeader = allocate_from_main_pool_safe(size, COLOUR_TAG_YELLOW);
        load_asset_to_address(ASSET_LEVEL_HEADERS, gCurrentLevelHeader, offset, size);
    }
    free_from_memory_pool(gTempAssetTable);
    func_8006BFC8(&gCurrentLevelHeader->unk20);
    func_8000CBC0();
    gMapId = levelId;
    for (i = 0; i < 7; i++) {
        if ((s32)gCurrentLevelHeader->unk74[i] != -1) {
            gCurrentLevelHeader->unk74[i] = get_misc_asset((s32)gCurrentLevelHeader->unk74[i]);
            func_8007F1E8(gCurrentLevelHeader->unk74[i]);
        }
    }
    if (cutsceneId == 0x64) {
        if (get_trophy_race_world_id() != 0 && gCurrentLevelHeader->race_type == RACETYPE_DEFAULT) {
            cutsceneId = 0;
        } else if (is_in_tracks_mode() == 1 && gCurrentLevelHeader->race_type == RACETYPE_DEFAULT) {
            cutsceneId = 0;
        }
    }
    if (gCurrentLevelHeader->race_type == RACETYPE_DEFAULT || gCurrentLevelHeader->race_type == RACETYPE_BOSS) {
        D_800DD31C = 1;
    } else {
        D_800DD31C = 0;
    }
    if (noPlayers && gCurrentLevelHeader->race_type != RACETYPE_CUTSCENE_2) {
        gCurrentLevelHeader->race_type = RACETYPE_CUTSCENE_1;
    }
    set_music_player_voice_limit(gCurrentLevelHeader->voiceLimit);
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
        D_800DD314 = get_level_default_vehicle();
    }
    if (settings->worldId == 0 && temp > 0 && D_800DD314 != -1) {
        vehicleId = D_800DD314;
    }
    func_8006DB20(vehicleId);
    if (gCurrentLevelHeader->race_type == RACETYPE_HUBWORLD) {
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
    if (numberOfPlayers != ONE_PLAYER && gCurrentLevelHeader->race_type == RACETYPE_DEFAULT) {
        cutsceneId = 0x64;
    }
    if ((gCurrentLevelHeader->race_type == RACETYPE_DEFAULT || (gCurrentLevelHeader->race_type & RACETYPE_CHALLENGE)) && is_in_two_player_adventure()) {
        D_800DD318 = 1;
        cutsceneId = 0x64;
    } else {
        D_800DD318 = 0;
    }
    if (gCurrentLevelHeader->race_type == RACETYPE_DEFAULT && !noPlayers && is_time_trial_enabled()) {
        cutsceneId = 0x64;
    }
    func_8001E450(cutsceneId);
    func_800249F0(gCurrentLevelHeader->geometry, gCurrentLevelHeader->skybox, numberOfPlayers, vehicleId, entranceId, gCurrentLevelHeader->collectables, gCurrentLevelHeader->unkBA);
    if (gCurrentLevelHeader->fogNear == 0 && gCurrentLevelHeader->fogFar == 0 && gCurrentLevelHeader->fogR == 0 && gCurrentLevelHeader->fogG == 0 && gCurrentLevelHeader->fogB == 0) {
        for (i = 0; i < 4; i++) {
            func_800307BC(i);
        }
    } else {
        for (i = 0; i < 4; i++) {
            func_80030664(i, gCurrentLevelHeader->fogNear, gCurrentLevelHeader->fogFar, (u8)gCurrentLevelHeader->fogR, gCurrentLevelHeader->fogG, gCurrentLevelHeader->fogB);
        }
    }
    settings = get_settings();
    if (gCurrentLevelHeader->world != -1) {
        settings->worldId = gCurrentLevelHeader->world;
    }
    settings->courseId = levelId;
    if (gCurrentLevelHeader->weatherEnable > 0) {
        func_800AB4A8(
            gCurrentLevelHeader->weatherType,
            gCurrentLevelHeader->weatherEnable,
            gCurrentLevelHeader->weatherVelX << 8,
            gCurrentLevelHeader->weatherVelY << 8,
            gCurrentLevelHeader->weatherVelZ << 8,
            gCurrentLevelHeader->weatherIntensity * 0x101,
            gCurrentLevelHeader->weatherOpacity * 0x101);
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
    set_background_prim_colour(gCurrentLevelHeader->bgColorRed, gCurrentLevelHeader->bgColorGreen, gCurrentLevelHeader->bgColorBlue);
    reset_video_delta_time();
    func_8007AB24(gCurrentLevelHeader->unk4[numberOfPlayers]);
}
#else
GLOBAL_ASM("asm/non_matchings/game/load_level.s")
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
    return gMapId;
}

/**
 * Return the race type ID of the current level.
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
    func_8006C164();
    set_background_prim_colour(0, 0, 0);
    free_from_memory_pool(gCurrentLevelHeader);
    func_800049D8();
    func_80001844();
    func_800018E0();
    func_800012E8();
    func_80031B60();
    func_8002C7D4();
    func_80008174();
    func_80000968(0);
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

void func_8006C164(void) {
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
    D_800DD37C = func_8006A1C4(D_800DD37C, 0);
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

s32 gAntiAliasing = TRUE;

/**
 * Setup all of the necessary pieces required for the game to function.
 * This includes the memory pool. controllers, video, audio, core assets and more.
 */
void init_game(void) {
    s32 mode;
    s32 i;

    init_main_memory_pool();
    func_800C6170(); // Initialise gzip decompression related things
#ifndef NO_ANTIPIRACY
    sAntiPiracyTriggered = TRUE;
    if (check_imem_validity()) {
        sAntiPiracyTriggered = FALSE;
    }
#endif
    gIsLoading = FALSE;
    gLevelDefaultVehicleID = VEHICLE_CAR;

    if (osTvType == TV_TYPE_PAL) {
        mode = 14;
    } else if (osTvType == TV_TYPE_NTSC) {
        mode = 0;
    } else if (osTvType == TV_TYPE_MPAL) {
        mode = 28;
    }

    osCreateScheduler(&gMainSched, &gSPTaskNum, /*priority*/ 13, (u8) mode, 1);
    D_800DD3A0 = FALSE;
    if (!func_8006EFB8()) {
        D_800DD3A0 = TRUE;
    }
    init_video(VIDEO_MODE_LOWRES_LPN, &gMainSched);
    init_PI_mesg_queue();
    setup_gfx_mesg_queues(&gMainSched);
    audio_init(&gMainSched);
    func_80008040(); // Should be very similar to func_8005F850
    sControllerStatus = init_controllers();
    func_8007AC70(); // Should be very similar to func_8005F850
    func_8005F850(); // Matched
    func_8000BF8C();
    func_800B5E88();
    func_800598D0();
    init_particle_assets();
    func_800AB1F0();
    calc_and_alloc_heap_for_settings();
    func_8006EFDC();
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

#ifdef FIFO_UCODE
s8 suCodeSwitch = 0;
#endif

u32 sPrevTime = 0;
u32 sDeltaTime = 0;
s32 sTotalTime = 0;

/**
 * The main gameplay loop.
 * Contains all game logic, audio and graphics processing.
 */
void main_game_loop(void) {
    s32 debugLoopCounter;
    s32 framebufferSize;
    s32 tempLogicUpdateRate, tempLogicUpdateRateMax;
#ifdef PUPPYPRINT_DEBUG
    u32 first = osGetCount();
    u32 first2;
    u32 first3;
    s32 i;
    if (get_buttons_held_from_player(0) & U_JPAD && get_buttons_pressed_from_player(0) & L_TRIG) {
        gProfilerOn ^= 1;
    }
    profiler_reset_values();
#endif

    /*if (get_buttons_pressed_from_player(0) & R_JPAD) {
        if (gScreenWidth == 304) {
            gScreenWidth = 360;
            change_vi(&gGlobalVI, 360, 224);
        } else if (gScreenWidth == 360) {
            gScreenWidth = 408;
            change_vi(&gGlobalVI, 408, 224);
        } else {
            gScreenWidth = 304;
            change_vi(&gGlobalVI, 304, 224);
        }
    }*/

    if (gScreenStatus == MESG_SKIP_BUFFER_SWAP) {
        gCurrDisplayList = gDisplayLists[gSPTaskNum];
        set_rsp_segment(&gCurrDisplayList, 0, 0);
        set_rsp_segment(&gCurrDisplayList, 1, (s32)gVideoCurrFramebuffer);
        set_rsp_segment(&gCurrDisplayList, 2, gVideoLastDepthBuffer);
        set_rsp_segment(&gCurrDisplayList, 4, (s32)gVideoCurrFramebuffer - 0x500);
    }
    if (gDrawFrameTimer == 0) {
#ifndef FIFO_UCODE
        setup_ostask_xbus(gDisplayLists[gSPTaskNum], gCurrDisplayList, 0);
#else
    #ifdef PUPPYPRINT_DEBUG
        if (get_buttons_pressed_from_player(PLAYER_ONE) & D_JPAD) {
            gAntiAliasing ^= 1;
        }
        if (suCodeSwitch == FALSE && IO_READ(DPC_BUFBUSY_REG) + IO_READ(DPC_CLOCK_REG) + IO_READ(DPC_TMEM_REG)) {
    #endif
            setup_ostask_fifo(gDisplayLists[gSPTaskNum], gCurrDisplayList, 0);
    #ifdef PUPPYPRINT_DEBUG
        } else {
            setup_ostask_xbus(gDisplayLists[gSPTaskNum], gCurrDisplayList, 0);
        }
    #endif
#endif
        gSPTaskNum += 1;
        gSPTaskNum &= 1;
    }
    if (gDrawFrameTimer) {
        gDrawFrameTimer--;
    }

    sDeltaTime = osGetTime() - sPrevTime;
    sPrevTime = osGetTime();
    sTotalTime += OS_CYCLES_TO_USEC(sDeltaTime);
    sTotalTime -= 16666;
    sLogicUpdateRate = LOGIC_60FPS;
    while (sTotalTime > 16666) {
        sTotalTime -= 16666;
        sLogicUpdateRate++;
        if (sLogicUpdateRate == 4) {
            sTotalTime = 0;
        }
    }

    gCurrDisplayList = gDisplayLists[gSPTaskNum];
    gGameCurrMatrix = gHudMatrices[gSPTaskNum];
    gGameCurrVertexList = gHudVertices[gSPTaskNum];
    gGameCurrTriList = gHudTriangles[gSPTaskNum];

    set_rsp_segment(&gCurrDisplayList, 0, 0);
    set_rsp_segment(&gCurrDisplayList, 1, gVideoLastFramebuffer);
    set_rsp_segment(&gCurrDisplayList, 2, gVideoLastDepthBuffer);
    set_rsp_segment(&gCurrDisplayList, 4, gVideoLastFramebuffer - 0x500);
#ifdef PUPPYPRINT_DEBUG
    first2 = osGetCount();
#endif
    init_rsp(&gCurrDisplayList);
    init_rdp_and_framebuffer(&gCurrDisplayList);
    render_background(&gCurrDisplayList, (Matrix *) &gGameCurrMatrix, TRUE); 
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.timers[PP_BACKGROUND], osGetCount() - first2);
    first2 = osGetCount();
#endif
    D_800DD37C = func_8006A1C4(D_800DD37C, sLogicUpdateRate);
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.timers[PP_PAD], osGetCount() - first2);
#endif
    if (get_lockup_status()) {
        render_epc_lock_up_display();
        sRenderContext = DRAW_CRASH_SCREEN;
    }
    if (D_800DD3A0) {
        debugLoopCounter = 0;
        while (debugLoopCounter != 10000000) {
            debugLoopCounter += 1;
        }
        if (debugLoopCounter >= 20000001) { // This shouldn't ever be true?
            render_printf(D_800E7134 /* "BBB\n" */);
        }
    }
    switch (sRenderContext) {
        case DRAW_INTRO: // Pre-boot screen
#ifdef PUPPYPRINT_DEBUG
            first2 = osGetCount();
            first3 = gPuppyTimers.timers[PP_BACKGROUND][perfIteration];
#endif
            pre_intro_loop();
#ifdef PUPPYPRINT_DEBUG
            profiler_add(gPuppyTimers.timers[PP_MENU], osGetCount() - first2);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_SCENE][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_LIGHT][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_ENVMAP][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_TEXT][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_WAVES][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_PARTICLES][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_VOID][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_BACKGROUND][perfIteration] - first3);
#endif
            break;
        case DRAW_MENU: // In a menu
#ifdef PUPPYPRINT_DEBUG
            first2 = osGetCount();
            first3 = gPuppyTimers.timers[PP_BACKGROUND][perfIteration];
#endif
            func_8006DCF8(sLogicUpdateRate);
#ifdef PUPPYPRINT_DEBUG
            profiler_add(gPuppyTimers.timers[PP_MENU], osGetCount() - first2);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_OBJECTS][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_SCENE][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_LIGHT][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_ENVMAP][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_TEXT][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_WAVES][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_PARTICLES][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_VOID][perfIteration]);
            profiler_offset(gPuppyTimers.timers[PP_MENU], gPuppyTimers.timers[PP_BACKGROUND][perfIteration] - first3);
#endif
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
#ifdef PUPPYPRINT_DEBUG
    first2 = osGetCount();
#endif
    print_debug_strings(&gCurrDisplayList);
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.timers[PP_TEXT], osGetCount() - first2);
    first2 = osGetCount();
    first3 = gPuppyTimers.timers[PP_TEXT][perfIteration];
#endif
    render_dialogue_boxes(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList);
    close_dialogue_box(4);
    assign_dialogue_box_id(4);
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.timers[PP_DIALOGUE], osGetCount() - first2);
    profiler_offset(gPuppyTimers.timers[PP_DIALOGUE], gPuppyTimers.timers[PP_TEXT][perfIteration] - first3);
    first2 = osGetCount();
#endif
    // handle_transitions will perform the logic of transitions and return the transition ID.
    if (handle_transitions(sLogicUpdateRate)) {
        render_fade_transition(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList);
    }
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.timers[PP_TRANSITION], osGetCount() - first2);
#endif
    if ((sBootDelayTimer >= 8) && (is_controller_missing())) {
        print_missing_controller_text(&gCurrDisplayList, sLogicUpdateRate);
    }

#ifdef PUPPYPRINT_DEBUG
    first2 = osGetCount();
    first3 = gPuppyTimers.timers[PP_TEXT][perfIteration];
    if (gProfilerOn) {
        render_profiler();
        count_triangles((u8*) gDisplayLists[gSPTaskNum], (u8*) gCurrDisplayList);
    }
    profiler_add(gPuppyTimers.timers[PP_PROFILER], osGetCount() - first2);
    profiler_offset(gPuppyTimers.timers[PP_PROFILER], gPuppyTimers.timers[PP_TEXT][perfIteration] - first3);
#endif

    gDPFullSync(gCurrDisplayList++);
    gSPEndDisplayList(gCurrDisplayList++);

    func_80066610();
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.timers[PP_LOGIC], osGetCount() - first);
    for (i = 1; i < PP_THREAD0; i++) {
        profiler_offset(gPuppyTimers.timers[PP_LOGIC], gPuppyTimers.timers[i][perfIteration]);
    }
#endif
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
#ifdef PUPPYPRINT_DEBUG
    calculate_and_update_fps();
    puppyprint_calculate_average_times();
    perfIteration++;
    if (perfIteration == NUM_PERF_ITERATIONS - 1)
        perfIteration = 0;
#endif
    if (gDrawFrameTimer == 2) {
        framebufferSize = SCREEN_WIDTH * SCREEN_HEIGHT * 2;
        if (osTvType == TV_TYPE_PAL) {
            framebufferSize = (s32)((SCREEN_WIDTH * SCREEN_HEIGHT * 2) * 1.1f);
        }
        dmacopy_doubleword(gVideoLastFramebuffer, (s32)gVideoCurrFramebuffer, (s32)gVideoCurrFramebuffer + framebufferSize);
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
#ifdef PUPPYPRINT_DEBUG
    u32 first = osGetCount();
    u32 first2;
#endif
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
#ifdef PUPPYPRINT_DEBUG
    sPrevLoadTime = OS_CYCLES_TO_USEC(osGetCount() - first);
    sPrevLoadTimer = 150;
#endif
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
    func_800C01D8(&D_800DD3F4);
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
#ifdef PUPPYPRINT_DEBUG
    u32 first;
    u32 first3;
#endif

    sp40 = 0;
    buttonHeldInputs = 0;
    buttonPressedInputs = 0;

    // Get input data for all 4 players.
    for (i = 0; i < get_active_player_count(); i++) {
        buttonHeldInputs |= get_buttons_held_from_player(i);
        buttonPressedInputs |= get_buttons_pressed_from_player(i);
    }
#ifndef NO_ANTIPIRACY
    // Spam the start button, making the game unplayable because it's constantly paused.
    if (sAntiPiracyTriggered) {
        buttonPressedInputs |= START_BUTTON;
    }
#endif
    // Update all objects
    if (!gIsPaused) {
#ifdef PUPPYPRINT_DEBUG
    first = osGetCount();
    first3 = gPuppyTimers.timers[PP_WAVES][perfIteration];
#endif
        func_80010994(updateRate);
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.timers[PP_OBJECTS], osGetCount() - first);
    profiler_offset(gPuppyTimers.timers[PP_OBJECTS], gPuppyTimers.timers[PP_RACER][perfIteration]);
    profiler_offset(gPuppyTimers.timers[PP_OBJECTS], gPuppyTimers.timers[PP_WAVES][perfIteration] - first3);
#endif
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
    
#ifdef PUPPYPRINT_DEBUG
    first = osGetCount();
    first3 = gPuppyTimers.timers[PP_TEXT][perfIteration];
#endif
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
    //render_borders_for_multiplayer(&gCurrDisplayList);
    func_800A8474(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, updateRate);
    //render_second_multiplayer_borders(&gCurrDisplayList);
#ifdef PUPPYPRINT_DEBUG
    profiler_add(gPuppyTimers.timers[PP_HUD], osGetCount() - first);
    profiler_offset(gPuppyTimers.timers[PP_HUD], gPuppyTimers.timers[PP_TEXT][perfIteration] - first3);
#endif
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
        func_8006EC48(get_save_file_index());
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
            func_8006EC48(get_save_file_index());
            load_menu_with_level_background(MENU_TITLE, -1, 0);
        }
        D_801234FC = 0;
    }
    if (D_801234F8 != 0) {
        gPostRaceViewPort = NULL;
        func_8006CC14();
        load_level_2(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
        func_8006EC48(get_save_file_index());
        D_801234F8 = 0;
    }
}

void func_8006D8A4(void) {
    D_800DD390 = 0x2C;
    gIsPaused = 0;
    n_alSeqpDelete();
    func_800C01D8(&D_800DD408);
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

s32 get_render_context(void) {
    return sRenderContext;
}

/* Unused function used to set the render context from outside this file */
UNUSED void set_render_context(s32 changeTo) {
    sRenderContext = changeTo;
}

void load_menu_with_level_background(s32 menuId, s32 levelId, s32 cutsceneId) {
    func_8006ECFC(0);
    sRenderContext = DRAW_MENU;
    D_801234F0 = 1;
    func_80004A60(0, 32767);
    func_80004A60(1, 32767);
    func_80004A60(2, 32767);
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
        func_800C01D8(&D_800DD3F4);
        func_800AE270();
        func_800A003C();
        func_800C30CC();
        set_free_queue_state(2);
    }
    gIsLoading = FALSE;
}

void func_8006DC58(s32 updateRate) {
    if (get_thread30_level_id_to_load() == 0) {
#ifdef PUPPYPRINT_DEBUG
        u32 first = osGetCount();
#endif
        func_80010994(updateRate);
#ifdef PUPPYPRINT_DEBUG
        profiler_add(gPuppyTimers.timers[PP_OBJECTS], osGetCount() - first);
        profiler_offset(gPuppyTimers.timers[PP_OBJECTS], gPuppyTimers.timers[PP_RACER][perfIteration]);
#endif
        gParticlePtrList_flush();
        func_8001BF20();
        render_scene(&gCurrDisplayList, &gGameCurrMatrix, &gGameCurrVertexList, &gGameCurrTriList, updateRate);
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
        load_level_2(gPlayableMapId, D_80123500, D_80123504, gLevelDefaultVehicleID);
        func_8006EC48(get_save_file_index());
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
                func_8006EC48(get_save_file_index());
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
                func_8006EC48(get_save_file_index());
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
    D_800DD37C = 263;
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
    for (i = 0; i < 3; i++) { // 3 = number of save files?
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

s8 func_8006EAB0(void) {
    return gPostRaceViewPort;
}

/**
 * Sets and returns (nonzero) the message set when pressing the reset button.
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

void func_8006EB78(s32 saveFileIndex) {
    D_800DD37C &= -0x301;
    D_800DD37C |= (0x04 | ((saveFileIndex & 3) << 8));
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

void func_8006EC48(s32 saveFileIndex) {
    if (sRenderContext == DRAW_GAME && !is_in_tracks_mode()) {
        D_800DD37C &= -0xC01;
        D_800DD37C |= (0x40 | ((saveFileIndex & 3) << 0xA));
    }
}

void func_8006ECAC(s32 arg0) {
    D_800DD37C = ((arg0 & 0x03) << 10) | 0x80;
}

/* Unused? */
void func_8006ECC4(void) {
    D_800DD37C |= 0x100;
}

//Always called after updating a value in sEepromSettings
void func_8006ECE0(void) {
    D_800DD37C |= 0x200;
}

GLOBAL_ASM("asm/non_matchings/game/func_8006ECFC.s")

s32 func_8006EFB8(void) {
    //Could be SP_DMEM_START / CACHERR_EE / SR_FR / M_K0 / LEO_STATUS_BUFFER_MANAGER_INTERRUPT
    if (IO_READ(SP_DMEM_START) != -1U) {
        return FALSE;
    }
    return TRUE;
}

#ifdef NON_EQUIVALENT

// Not close to matching, but should be the same functionality-wise.
void func_8006EFDC(void) {
    s32 size1, size2, size3, size4, totalSize;

    D_8012350C = 3;

    size1 = (gNumF3dCmdsPerPlayer[3] * sizeof(Gwords));
    size2 = (gNumHudMatPerPlayer[3] * sizeof(Matrix));
    size3 = (gNumHudVertsPerPlayer[3] * sizeof(Vertex));
    size4 = (gNumHudTrisPerPlayer[3] * sizeof(Triangle));
    totalSize = size1 + size2 + size3 + size4;

    gDisplayLists[0] = (u8 *)allocate_from_main_pool_safe(totalSize, COLOUR_TAG_RED);
    gHudMatrices[0] = (u8 *)gDisplayLists[0] + size1;
    gHudVertices[0] = (u8 *)gHudMatrices[0] + size2;
    gHudTriangles[0] = (u8 *)gHudVertices[0] + size3;

    gDisplayLists[1] = (u8 *)allocate_from_main_pool_safe(totalSize, COLOUR_TAG_YELLOW);
    gHudMatrices[1] = (u8 *)gDisplayLists[1] + size1;
    gHudVertices[1] = (u8 *)gHudMatrices[1] + size2;
    gHudTriangles[1] = (u8 *)gHudVertices[1] + size3;

    gCurrNumF3dCmdsPerPlayer = gNumF3dCmdsPerPlayer[3];
    gCurrNumHudMatPerPlayer = gNumHudMatPerPlayer[3];
    gCurrNumHudTrisPerPlayer = gNumHudTrisPerPlayer[3];
    gCurrNumHudVertsPerPlayer = gNumHudVertsPerPlayer[3];
}
#else
GLOBAL_ASM("asm/non_matchings/game/func_8006EFDC.s")
#endif

void func_8006F140(s32 arg0) {
    if (gLevelLoadTimer == 0) {
        gLevelLoadTimer = 40;
        D_80123524 = 0;
        D_80123526 = 0;
        if (arg0 == 1) {
            func_800C01D8(&D_800DD41C);
        }
        if (arg0 == 3) {
            gLevelLoadTimer = 282;
            func_800C01D8(&D_800DD424);
        }
        if (arg0 == 4) {
            gLevelLoadTimer = 360;
            func_800C01D8(&D_800DD424);
        }
        if (arg0 == 0) {
            gLevelLoadTimer = 2;
        }
    }
}

// Unused?
void func_8006F20C(void) {
    if (gLevelLoadTimer == 0) {
        func_800C01D8(&D_800DD41C);
        gLevelLoadTimer = 40;
        D_80123524 = 1;
    }
}

void func_8006F254(void) {
    if (gLevelLoadTimer == 0) {
        func_800C01D8(&D_800DD41C);
        gLevelLoadTimer = 40;
        D_80123524 = 2;
    }
}

void func_8006F29C(void) {
    if (gLevelLoadTimer == 0) {
        if ((gSettingsPtr->trophies & 0xFF) == 0xFF && !(gSettingsPtr->cutsceneFlags & CUTSCENE_LIGHTHOUSE_ROCKET) && gSettingsPtr->bosses & 1) {
            gSettingsPtr->cutsceneFlags |= CUTSCENE_LIGHTHOUSE_ROCKET;
            func_800C01D8(&D_800DD41C);
            gLevelLoadTimer = 40;
            D_80123525 = 0x2D;
            D_80123524 = 3;
        }
    }
}

void func_8006F338(s32 arg0) {
    if (gLevelLoadTimer == 0) {
        D_80123525 = arg0;
        func_800C01D8(&D_800DD41C);
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
    /*(SP_STATUS_HALT | SP_STATUS_BROKE | SP_STATUS_DMA_BUSY | SP_STATUS_IO_FULL | SP_STATUS_INTR_BREAK | SP_STATUS_YIELD |
    SP_STATUS_YIELDED | SP_STATUS_TASKDONE | SP_STATUS_TASKDONE | SP_STATUS_RSPSIGNAL | SP_STATUS_SIG5))*/
    if (IO_READ(SP_IMEM_START) != 0x17D7) {
        return FALSE;
    }
    return TRUE;
}
#endif