/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8009ECF0 */

#include "game_ui.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "camera.h"
#include "game.h"
#include "audio.h"
#include "textures_sprites.h"
#include "racer.h"
#include "math_util.h"
#include "objects.h"
#include "game_text.h"
#include "object_models.h"
#include "tracks.h"
#include "rcp.h"
#include "audiosfx.h"
#include "printf.h"
#include "audio_spatial.h"
#include "controller.h"

/************ .data ************/

// Unused?
s32 D_800E1E60 = 0;

unk800E1E64 D_800E1E64[59] = {
    { 0, 0, 1.0f, 53.0f, 16.0f, 0, 127, 0 },
    { 0, 3, 1.0f, 54.0f, 18.0f, 0, 0, 0 },
    { 0, 1, 0.4f, -120.0f, -68.0f, 0, 0, 0 },
    { 0, 6, 1.0f, 104.0f, 16.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 93.0f, 31.0f, 0, 0, 0 },
    { 0, 4, 1.0f, 104.0f, 32.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 114.0f, 31.0f, 0, 0, 0 },
    { 0, 8, 0.5f, -3.0f, 73.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 182.0f, 22.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 192.0f, 22.0f, 0, 0, 0 },
    { 0, 13, 1.0f, 239.0f, 16.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 206.0f, 31.0f, 0, 0, 0 },
    { 0, 7, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 22, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 5, 1.0f, -200.0f, 30.0f, 0, 0, 0 },
    { 0, 14, 1.0f, 0.0f, 0.0f, 0, 0, 0 },
    { 0, 16, 1.0f, -50.0f, 87.0f, 0, 0, 0 },
    { 0, 17, 2.0f, -50.0f, 87.0f, 0, 0, 0 },
    { 0, 18, 1.0f, 167.0f, 22.0f, 0, 0, 0 },
    { 0, 19, 1.0f, -127.0f, 88.0f, 0, 0, 0 },
    { 0, 18, 1.0f, 52.0f, 27.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 67.0f, 27.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 77.0f, 27.0f, 0, 0, 0 },
    { 0, 9, 1.0f, 221.0f, 48.0f, 0, 0, 0 },
    { 0, 6, 1.0f, 188.0f, 48.0f, 0, 0, 0 },
    { 0, 10, 1.0f, 206.0f, 48.0f, 0, 0, 0 },
    { 0, 20, 0.4f, -105.0f, -98.0f, 0, 0, 0 },
    { 0, 21, 0.5f, -3.0f, 73.0f, 0, 0, 0 },
    { 0, 23, 1.0f, -8.0f, 97.0f, 0, 0, 0 },
    { 0, 24, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 25, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 26, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 2, 1.0f, 25.0f, 48.0f, 0, 0, 0 },
    { 0, 32, 1.0f, -120.0f, 30.0f, 0, 0, 0 },
    { 0, 34, 0.4f, -105.0f, -98.0f, 0, 0, 0 },
    { 0, 35, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 36, 1.0f, 0.0f, 30.0f, 0, 0, 0 },
    { 0, 40, 1.0f, 80.0f, -60.0f, 0, 0, 0 },
    { 0, 1687158830, 0.5f, 122.0f, -71.0f, 0, 0, 0 },
    { 0, 47, 0.75f, 247.0f, 212.0f, 0, 0, 0 },
    { 0, 48, 1.0f, 234.0f, 196.0f, 0, 0, 0 },
    { 0, 49, 1.0f, 232.0f, 177.0f, 0, 0, 0 },
    { 0, 50, 1.0f, 240.0f, 159.0f, 0, 0, 0 },
    { 0, 51, 1.0f, 256.0f, 146.0f, 0, 0, 0 },
    { 0, 52, 1.0f, 275.0f, 143.0f, 0, 0, 0 },
    { 0, 53, 1.0f, 246.0f, 156.0f, 0, 0, 0 },
    { 0, 54, 0.7272f, 27.0f, 142.0f, 0, 0, 0 },
    { 0, 0, 1.0f, -200.0f, 70.0f, 0, 129, 0 },
    { 0, 3, 1.0f, -175.0f, 72.0f, 0, 0, 0 },
    { 0, 55, 1.0f, -99.0f, -89.0f, 0, 0, 0 },
    { 0, 56, 0.76f, 43.0f, 20.0f, 0, 0, 0 },
    { 0, 66, 1.0f, 40.0f, 54.0f, 0, 0, 0 },
    { 0, 8, 0.375f, -117.0f, 46.0f, 0, 0, 0 },
    { 0, 28, 1.0f, 51.0f, 56.0f, 0, 0, 0 },
    { 0, 10, 1.0f, 60.0f, 57.0f, 0, 0, 0 },
    { 0, 10, 1.0f, 69.0f, 57.0f, 0, 0, 0 },
    { 0, 67, 1.0f, -160.0f, 5.0f, 0, 0, 0 },
    { 0, 56, 1.0f, 260.0f, 16.0f, 0, 0, 0 },
    { 0, 68, 1.0f, 160.0f, 5.0f, 0, 0, 0 },
};

u16 D_800E25C4[96] = {
    0x0000, 0x0035, 0x0010, 0x0001, 0x0036, 0x0012, 0x0004, 0x00CB,
    0x0013, 0x0005, 0x00D3, 0x0013, 0x0006, 0x00DC, 0x0013, 0x0002,
    0xFF88, 0xFFE1, 0x001B, 0x0021, 0x0016, 0x0008, 0x00D3, 0x0013,
    0x0009, 0x00DC, 0x0013, 0x000B, 0x00A7, 0x0013, 0x000E, 0x0000,
    0x000A, 0x0010, 0x003B, 0x0023, 0x0011, 0x003B, 0x0023, 0x0007,
    0x0021, 0x0016, 0x001C, 0x001E, 0x002A, 0x0012, 0x00CA, 0x0013,
    0x000D, 0x0000, 0x000A, 0x000C, 0x0000, 0x000A, 0x0023, 0x0000, 
    0x000A, 0x0024, 0x0000, 0x000A, 0x001E, 0x0000, 0x000A, 0x001F,
    0x0000, 0x000A, 0x001D, 0x0000, 0x000A, 0x002F, 0xFF38, 0x0023,
    0x0030, 0xFF51, 0x0025, 0x0031, 0xFF96, 0xFFD3, 0x0003, 0x00B4,
    0x0013, 0x0032, 0x0107, 0x0011, 0x0020, 0x00F7, 0x002D, 0x0033,
    0x0103, 0x0031, 0x002E, 0x0022, 0x0047, 0xFFFF, 0xFFFF, 0xFFFF,
};

u16 D_800E2684[118] = {
    0x0000, 0x002D, 0x0010, 0x0087, 0x0004, 0x005E, 0x0013, 0x004E,
    0x0005, 0x0066, 0x0013, 0x0056, 0x0006, 0x006F, 0x0013, 0x005F,
    0x0002, 0xFFD1, 0xFFDC, 0x0024, 0x001B, 0x0000, 0x0016, 0xFFE3,
    0x0007, 0x0000, 0x0016, 0xFFE3, 0x0008, 0x0061, 0x0013, 0x0044,
    0x0009, 0x006A, 0x0013, 0x004D, 0x000B, 0x0037, 0x0013, 0x001A,
    0x000C, 0x0000, 0x000A, 0x0000, 0x000D, 0x0000, 0x000A, 0x0000,
    0x000E, 0xFF60, 0x000A, 0xFF60, 0x0010, 0x0066, 0x0013, 0x0056,
    0x0011, 0x0066, 0x0013, 0x0056, 0x0012, 0x0058, 0x0013, 0x003B,
    0x001C, 0xFFFD, 0x002A, 0xFFE0, 0x0020, 0x0012, 0x002D, 0x0078,
    0x001E, 0xFFEA, 0x000A, 0xFFEA, 0x001F, 0x000C, 0x000A, 0x0010,
    0x001D, 0x0000, 0x000A, 0xFFD9, 0x0023, 0x0000, 0x000A, 0x0000,
    0x0024, 0x0000, 0x000A, 0x0000, 0x002F, 0xFF38, 0x0019, 0xFFD8,
    0x0030, 0xFF51, 0x001B, 0xFFF1, 0x0031, 0xFFDF, 0xFFCE, 0x0032,
    0x0003, 0x0047, 0x0013, 0x0037, 0x0033, 0x003C, 0x0014, 0x003C,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
};

unk800E2770 D_800E2770[2] = {
    { 0x00FD, 0, 0, NULL, 0, 0, 0, 0, 0 },
    { 0x00FF, 0, 0, NULL, 0, 0, 0, 0, 0 },
};

u8 gShowCourseDirections = TRUE;

u8 D_800E2794[4][4] = {
    {1, 1, 1, 1}, 
    {2, 2, 2, 2}, 
    {2, 2, 2, 2}, 
    {2, 2, 2, 2}
};

s8 gHudToggleSettings[4] = {
    1, 1, 1, 1
};

s8 D_800E27A8 = 1;

u32 D_800E27AC[3] = {
    COLOUR_RGBA32(255, 40, 40, 254),
    COLOUR_RGBA32(40, 255, 40, 254),
    COLOUR_RGBA32(40, 40, 255, 254),
};

u8 D_800E27B8 = 0;

ByteColour gHudMinimapColours[40] = {
 { 255, 160, 0 }, 
 { 255, 255, 0 }, 
 { 0, 128, 255 }, 
 { 255, 255, 255 }, 
 { 0, 175, 0 }, 
 { 0, 255, 128 }, 
 { 255, 0, 0 }, 
 { 255, 128, 190 },
 { 128, 128, 128 }, 
 { 0, 0, 255 }, 
 { 0, 0, 0 }, 
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 32, 0, 0 },
 { 0, 0, 0 },
 { 0, 0, 64 },
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 0, 96, 0 },
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 128, 0, 0 },
 { 0, 0, 0 },
 { 0, 0, 0 },
 { 0, 64, 0 },
 { 0, 0, 0 },
 { 0, 32, 0 },
 { 64, 0, 0 },
 { 0, 0, 0 },
 { 64, 0, 64 }, 
 { 0, 0, 0 }, 
 { 0, 0, 96 }, 
 { 0, 64, 0 }, 
 { 0, 0, 0 }, 
 { 0, 128, 0 }, 
 { 64, 0, 0 }, 
 { 0, 0, 0 }, 
 { 0, 0, 0 },
};

u32 gHudColour = COLOUR_RGBA32(255, 255, 255, 254);

f32 D_800E2838 = 0.0f;

// Unused?
s32 D_800E283C[5] = {
    0x06FFFFFF, 0x000FFFFF, 0x06000000, 0x0014FFFF, 0x00000000
};

/*******************************/

/************ .bss ************/

s8 D_80126CD0;
s8 D_80126CD1;
s8 gShowHUD;
s8 D_80126CD3;

/**
 * gRaceStartShowHudStep counts up from 0->5 on race start, and is used to
 * coordinate when certain hud actions & audio clips play/happen:
 *   - set to 0 on loading of new race
 *   - 0->1 when camera shutter open animation occurs
 *   - 1->2 when hud slides into screen with "whoosh" sound
 *   - 2->3 on the "Get Ready!" voice play
 *   - 3->4 on the "Go" voice and text
 *   - 4->5 on the "Go" sliding off screen
 *   - stays 5 until the next race starts
*/
s8 gRaceStartShowHudStep;

s8 D_80126CD5;
u8 *gAssetHudElementStaleCounter;
unk80126CDC *gCurrentHud;
unk80126CDC *gPlayerHud[MAXCONTROLLERS]; //One per active player
s16 *gAssetHudElementIds;
HudElements *gAssetHudElements;
s32 gAssetHudElementIdsCount;
Gfx *gHUDCurrDisplayList;
MatrixS *gHUDCurrMatrix;
Vertex *gHUDCurrVertex;
s32 gHudCurrentViewport;
s32 gHUDNumPlayers;
s32 D_80126D10;
s32 D_80126D14;
s32 D_80126D18;
s32 gMinimapDotOffsetX;
s32 gMinimapDotOffsetY;
s32 D_80126D24;
s32 D_80126D28;
u16 D_80126D2C;
f32 D_80126D30;
u8 D_80126D34;
u8 D_80126D35;
u8 gHideRaceTimer;
u8 gNumActivePlayers;
u8 gWrongWayNagPrefix;
SoundMask *D_80126D3C;
s32 gHUDVoiceSoundMask;
s32 D_80126D44;
s16 D_80126D48;
s32 D_80126D4C;
s32 D_80126D50;
u8 gMinimapRed;
u8 gMinimapGreen;
u8 gMinimapBlue;
s32 gMinimapScreenX;
s32 gMinimapScreenY;
LevelHeader *gHudLevelHeader;
u8 D_80126D64;
u8 D_80126D65;
u8 D_80126D66;
u8 gStopwatchFaceID;
u8 D_80126D68;
s8 D_80126D69;
s32 gWrongWayNagTimer;
u8 D_80126D70;
u8 D_80126D71;
s32 gTimeTrialVoiceDelay;
s32 D_80126D78;
u16 gTimeTrialVoiceID;
DrawTexture gHudSprites[128];
s32 D_80127180;
Settings *gHudSettings;
u8 gHudSilverCoinRace;
u8 D_80127189;
u8 D_8012718A;
u8 D_8012718B;
s32 D_8012718C;
s32 D_80127190;
LevelHeader_70 *D_80127194;
s32 D_80127198[6];

// Not sure why this ended up here, and not in rcp.c along with the rest of the task data.
u8 gGfxTaskYieldData[OS_YIELD_DATA_SIZE];

/******************************/

/**
 * Load basic hud assets and allocate HUD data for each player.
 * Set up the global hud elements and reset global vars.
*/
void init_hud(UNUSED s32 viewportCount) {
    s32 i;
    s32 playerCount;

    gHUDNumPlayers = get_viewport_count();
    gNumActivePlayers = set_active_viewports_and_max(gHUDNumPlayers);
    gHudSettings = get_settings();
    gHudSilverCoinRace = check_if_silver_coin_race();
    gAssetHudElementIds = (s16 *) load_asset_section_from_rom(ASSET_HUD_ELEMENT_IDS); 
    gAssetHudElementIdsCount = 0;
    
    while(gAssetHudElementIds[gAssetHudElementIdsCount] != -1) {
        gAssetHudElementIdsCount++;
    }
    gAssetHudElements = allocate_from_main_pool_safe(gAssetHudElementIdsCount * (sizeof(void *) + 1), COLOUR_TAG_BLUE);
    // Evil pointer shenanigans to store the timer in that last byte in the struct above.
    gAssetHudElementStaleCounter = (u8 *) ((gAssetHudElementIdsCount + (s32 *) gAssetHudElements));
    for(i = 0; i < gAssetHudElementIdsCount; i++) {
        gAssetHudElementStaleCounter[i] = 0;
        gAssetHudElements->entry[i] = NULL;
    }
    gAssetHudElements->entry[HUD_ELEMENT_UNK_01] = func_8007C12C(gAssetHudElementIds[HUD_ELEMENT_UNK_01] & 0x3FFF, 1); //ID: 86 - 0x56
    gAssetHudElements->entry[HUD_ELEMENT_UNK_17] = func_8007C12C(gAssetHudElementIds[HUD_ELEMENT_UNK_17] & 0x3FFF, 1); //ID: 291 - 0x123
    gAssetHudElements->entry[HUD_ELEMENT_UNK_08] = func_8007C12C(gAssetHudElementIds[HUD_ELEMENT_UNK_08] & 0x3FFF, 1); //ID: 156 - 0x9C
    gAssetHudElements->entry[HUD_ELEMENT_UNK_11] = func_8007C12C(gAssetHudElementIds[HUD_ELEMENT_UNK_11] & 0x3FFF, 1); //ID: 60 - 0x3C
    if (gNumActivePlayers != 3) {
        playerCount = gNumActivePlayers;
    } else {
        playerCount = 4; // Create four viewports if there are three players.
    }
    gPlayerHud[PLAYER_ONE] = allocate_from_main_pool_safe(playerCount * sizeof(unk80126CDC), COLOUR_TAG_BLUE);
    gPlayerHud[PLAYER_TWO] = (unk80126CDC *) ((u8 *) gPlayerHud[PLAYER_ONE] + sizeof(unk80126CDC));
    gPlayerHud[PLAYER_THREE] = (unk80126CDC *) ((u8 *) gPlayerHud[PLAYER_TWO] + sizeof(unk80126CDC));
    gPlayerHud[PLAYER_FOUR] = (unk80126CDC *) ((u8 *) gPlayerHud[PLAYER_THREE] + sizeof(unk80126CDC));
    func_8009F034();
    D_80126D64 = 0;
    gWrongWayNagTimer = 0;
    D_80126D48 = 0;
    D_80126D66 = 4;
    D_80126D65 = 0;
    gStopwatchFaceID = 4;
    D_80126D69 = 1;
    D_80126D68 = 1;
    D_80126D70 = 0;
    gTimeTrialVoiceID = 0;
    gTimeTrialVoiceDelay = 0;
    D_80126D3C = NULL;
    D_80126D44 = 0;
    D_80126CD3 = 0;
    D_80127194 = (LevelHeader_70 *) get_misc_asset(ASSET_MISC_58);
    func_8007F1E8(D_80127194);
    set_sound_channel_volume(0, 32767);
    set_sound_channel_volume(2, 32767);
    for(i = 0; i < 2; i++){
        D_800E2770[i].volume = 0;
        D_800E2770[i].unk3 = 0;
        D_800E2770[i].playerIndex = PLAYER_COMPUTER;
        if (D_800E2770[i].soundMask) {
            func_8000488C(D_800E2770[i].soundMask);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_8009F034.s")

/**
 * Free's all elements in the hud, and the player hud, and flushes particles
 */
void free_hud(void) {
    s32 i;
    for (i = 0; i < gAssetHudElementIdsCount; i++) {
        if (gAssetHudElements->entry[i] != NULL) {
            if ((gAssetHudElementIds[i] & 0xC000) == 0xC000) {
                free_texture(gAssetHudElements->entry[i]);
            } else if (gAssetHudElementIds[i] & 0x8000) {
                free_sprite((Sprite *) gAssetHudElements->entry[i]);
            } else if (gAssetHudElementIds[i] & 0x4000) {
                free_object((Object *) gAssetHudElements->entry[i]);
            } else {
                free_3d_model((ObjectModel **) gAssetHudElements->entry[i]);
            }
            gAssetHudElements->entry[i] = 0;
        }
    }
    free_from_memory_pool(*gPlayerHud);
    free_from_memory_pool(gAssetHudElementIds);
    gAssetHudElementIdsCount = 0;
    free_from_memory_pool(gAssetHudElements);
    gParticlePtrList_flush();
}

u8 func_800A0190(void) {
    return D_80126D34;
}

/**
 * The root function for all of the heads up display during an active event.
 * Branches off to its own function for each race type, but overridden completely in time trial.
*/
void render_hud(Gfx **dList, MatrixS **mtx, Vertex **vertexList, Object *arg3, s32 updateRate) {
    s32 sp2C;
    Object_Racer *racer;

    gHudCurrentViewport = get_current_viewport();
    if (D_8012718A) {
        arg3 = get_racer_object_by_port(1 - gHudCurrentViewport);
    }
    gHudLevelHeader = get_current_level_header();
    if (arg3 == NULL) {
        if (get_cutscene_id() == 10) {
            arg3 = get_racer_object_by_port(PLAYER_ONE);
        }
    }
    if (arg3 != NULL && !(gHudLevelHeader->unkBC & 2)) {
        if (get_game_mode() != GAMEMODE_MENU) {
            gHUDCurrDisplayList = *dList;
            gHUDCurrMatrix = *mtx;
            gHUDCurrVertex = *vertexList;
            D_80127180 = 0;
            if (D_80126CD1 != 0) {
                D_80126CD0 += updateRate;
                if (D_8012718B < D_80126CD0) {
                    D_80126CD0 = D_8012718B;
                }
            } else {
                D_80126CD0 -= updateRate;
                if (D_80126CD0 < 0) {
                    D_80126CD0 = 0;
                }
            }
            if (gShowHUD == 0) {
                racer = (Object_Racer *) arg3->unk64;
                if (D_8012718A) {
                    D_80126D10 = 1 - racer->playerIndex;
                } else {
                    D_80126D10 = racer->playerIndex;
                }
                gCurrentHud = gPlayerHud[gHudCurrentViewport];
                if (get_cutscene_id() != 10) {
                    if (gHUDNumPlayers == ONE_PLAYER) {
                        if (get_buttons_pressed_from_player(D_80126D10) & D_CBUTTONS && racer->raceFinished == FALSE && ((gHudLevelHeader->race_type == RACETYPE_DEFAULT) || gHudLevelHeader->race_type == RACETYPE_HORSESHOE_GULCH) && D_80126D34) {
                            gShowCourseDirections = 1 - gShowCourseDirections;
                            sound_play((SOUND_TING_HIGHER + gShowCourseDirections), NULL);
                            if (gShowCourseDirections) {
                                D_800E27B8 = 0x78;
                            } else {
                                D_800E27B8 = 0;
                            }
                        }
                    } else if (get_buttons_pressed_from_player(D_80126D10) & D_CBUTTONS && racer->raceFinished == FALSE && !(gHudLevelHeader->race_type & RACETYPE_CHALLENGE) && D_80126D34) {
                        if (D_800E2794[gHUDNumPlayers][racer->playerIndex] < PLAYER_FOUR) {
                             D_800E2794[gHUDNumPlayers][racer->playerIndex]++;
                        } else {
                             D_800E2794[gHUDNumPlayers][racer->playerIndex] = PLAYER_ONE;
                        }
                        sound_play((SOUND_TING_HIGHEST - (D_800E2794[gHUDNumPlayers][racer->playerIndex] == 0)), NULL);
                    }
                    if (get_buttons_pressed_from_player(D_80126D10) & R_CBUTTONS && racer->raceFinished == FALSE && D_80126D34 && D_80126CD0 == 0) {
                        gHudToggleSettings[gHUDNumPlayers] = 1 - gHudToggleSettings[gHUDNumPlayers];
                        if (gHudToggleSettings[gHUDNumPlayers] == 0) {
                            sound_play(SOUND_TING_LOW, NULL);
                        } else {
                            sound_play(SOUND_TING_HIGH, NULL);
                        }
                    }
                }
                if (gRaceStartShowHudStep == 0) {
                    if (gHudLevelHeader->race_type & RACETYPE_CHALLENGE || gHudLevelHeader->race_type == RACETYPE_DEFAULT || gHudLevelHeader->race_type == RACETYPE_HORSESHOE_GULCH || gHudLevelHeader->race_type == RACETYPE_BOSS) {
                        D_800E2770[0].volume = 127;
                        D_800E2770[1].volume = 127;
                        music_stop();
                        music_channel_reset_all();
                        music_play(SEQUENCE_RACE_START_FANFARE);
                        set_sound_channel_count(12);
                    } else {
                        start_level_music(1.0f);
                    }
                    gRaceStartShowHudStep += 1;
                }
                gDPPipeSync(gHUDCurrDisplayList++);
                init_rsp(&gHUDCurrDisplayList);
                init_rdp_and_framebuffer(&gHUDCurrDisplayList);
                tex_enable_modes(RENDER_ALL);
                tex_disable_modes(RENDER_Z_COMPARE);
                sprite_opaque(FALSE);
                if (check_if_showing_cutscene_camera() == FALSE && D_80126D34 == FALSE && racer->playerIndex == PLAYER_ONE) {
                    if (D_80126D35 != 0) {
                        D_80126D28 = sins_f(D_80126D2C) * D_80126D30 * 8.0f;
                        D_80126D2C += updateRate << 0xB;
                        if (D_80126D2C >= 0x8000) {
                            D_80126D2C -= 0x8000;
                            D_80126D30 = D_80126D30 / 2;
                            if (D_80126D30 <= 0.125) {
                                D_80126D34 = TRUE;
                                D_80126D24 = 0;
                            }
                        }
                    } else {
                        if (gRaceStartShowHudStep == 1) {
                            sound_play(SOUND_WHOOSH1, NULL);
                            gRaceStartShowHudStep += 1;
                        }
                        D_80126D24 -= updateRate * 13;
                        if (D_80126D24 < 0) {
                            D_80126D24 = 0;
                        }
                        if (D_80126D24 == 0) {
                            D_80126D35 = 1;
                            sound_play(SOUND_EXPLOSION2, NULL);
                            D_80126D28 = 0;
                        }
                    }
                }
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                render_magnet_reticle(arg3);
                set_ortho_matrix_view(&gHUDCurrDisplayList, &gHUDCurrMatrix);
                gDPSetEnvColor(gHUDCurrDisplayList++, 255, 255, 255, 0);
                sp2C = get_race_countdown() >> 1;
                if (is_in_time_trial()) {
                    func_800A277C(sp2C, arg3, updateRate);
                } else {
                    if (get_cutscene_id() == 10) {
                        func_80068508(TRUE);
                        render_balloon_count(racer);
                        func_80068508(FALSE);
                    } else {
                        switch (get_current_level_race_type()) {
                            case RACETYPE_DEFAULT:
                            case RACETYPE_HORSESHOE_GULCH:
                                if (is_taj_challenge()) {
                                    render_hud_taj_race(sp2C, arg3, updateRate);
                                } else {
                                    render_hud_race(sp2C, arg3, updateRate);
                                }
                                break;
                            case RACETYPE_BOSS:
                                render_hud_race_boss(sp2C, arg3, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_BANANAS:
                                render_hud_banana_challenge(sp2C, arg3, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_BATTLE:
                                render_hud_battle(sp2C, arg3, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_EGGS:
                                render_hud_challenge_eggs(sp2C, arg3, updateRate);
                                break;
                            default:
                                render_hud_hubworld(arg3, updateRate);
                                break;
                        }
                    }
                }
                if (racer->raceFinished == TRUE) {
                    func_80068508(TRUE);
                    if (is_in_time_trial()) {
                        render_time_trial_finish(racer, updateRate);
                    } else if (get_viewport_count() == VIEWPORTS_COUNT_1_PLAYER && racer->unk1AC == 1) {
                        if (is_in_two_player_adventure()) {
                            if (get_current_level_race_type() == RACETYPE_BOSS) {
                                goto showFinish;
                            }
                            goto block_95;
                        }
showFinish:
                        render_race_finish_position(racer, updateRate);
                    } else {
block_95:
                        func_800A6254(racer, updateRate);
                    }
                    func_80068508(FALSE);
                }
                D_80126CD1 = 0;
                sprite_opaque(TRUE);
                if (D_80127180) {
                    gHudSprites[D_80127180].texture = NULL;
                    render_textured_rectangle(&gHUDCurrDisplayList, gHudSprites, 0, 0, 255, 255, 255, 255);
                }
                *dList = gHUDCurrDisplayList;
                *mtx = gHUDCurrMatrix;
                *vertexList = gHUDCurrVertex;
                tex_enable_modes(RENDER_ALL);
            }
        }
    }
}

void func_800A0B74(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (D_800E2770[i].soundMask) {
            func_8000488C(D_800E2770[i].soundMask);
            D_800E2770[i].soundMask = NULL;
            D_800E2770[i].volume = 0;
        }
    }
}

void func_800A0BD4(s32 updateRate) {
    s32 temp;
    s32 i;

    if (gTimeTrialVoiceDelay > 0) {
        gTimeTrialVoiceDelay -= updateRate;
        if (gTimeTrialVoiceDelay <= 0) {
            gTimeTrialVoiceDelay = 0;
            if (gHUDVoiceSoundMask == NULL) {
                sound_play(gTimeTrialVoiceID, &gHUDVoiceSoundMask);
            }
        }
    }
    for(i = 0; i < 2; i++) {
        if (D_800E2770[i].volume) {
            if (D_800E2770[i].soundMask == NULL) {
                sound_play(D_800E2770[i].soundID, (s32 *) &D_800E2770[i].soundMask);
            }
            sound_volume_set_relative(D_800E2770[i].soundID, D_800E2770[i].soundMask, D_800E2770[i].volume);
            if (D_800E2770[i].unk3 > 0) {
                temp = D_800E2770[i].unk3 * updateRate;
                if ((127 - temp) >= D_800E2770[i].volume) {
                    D_800E2770[i].volume += temp;
                } else {
                    D_800E2770[i].unk3 = 0;
                    D_800E2770[i].volume = 0x7F;
                }
            } else if (D_800E2770[i].unk3 < 0) {
                temp = D_800E2770[i].unk3 * updateRate;
                if (-temp < D_800E2770[i].volume) {
                    D_800E2770[i].volume += temp;
                } else {
                    D_800E2770[i].unk3 = 0;
                    D_800E2770[i].volume = 0;
                }
            }
        } else {
            if (D_800E2770[i].soundMask) {
                func_8000488C(D_800E2770[i].soundMask);
                D_800E2770[i].soundMask = 0;
            }
        }
    }
    if ((D_80126D70 != 0) && (D_800E2770[0].volume == 0)) {
        D_80126D70 = 0;
        if (gNumActivePlayers == 1) {
            set_sound_channel_count(8);
        } else if (gNumActivePlayers == 2) {
            set_sound_channel_count(12);
        } else {
            set_sound_channel_count(16);
        }
    }
}

/**
 * In a race, render all of the race related HUD.
*/
void render_hud_race(s32 arg0, Object *obj, s32 updateRate) {
    Object_Racer *racer = &obj->unk64->racer;

    func_80068508(TRUE);
    render_course_indicator_arrows(racer, updateRate);
    render_wrong_way_text(racer, updateRate);
    render_race_start(arg0, updateRate);

    if (gHudLevelHeader->race_type == RACETYPE_DEFAULT) {
        render_lap_count(racer, updateRate);
    }

    render_racer_bananas(racer, updateRate);
    render_race_time(racer, updateRate);
    render_race_position(racer, updateRate);
    render_speedometer(obj, updateRate);

    if (gHudSilverCoinRace && racer->raceFinished == FALSE) {
        render_silver_coin_counter(racer, updateRate);
    }

    render_weapon_hud(obj, updateRate);
    func_80068508(FALSE);
}

/**
 * Render the onscreen course arrows that show the player where to go.
*/
void render_course_indicator_arrows(Object_Racer *racer, s32 updateRate) {
    s32 timer;
    s32 type;
    IndicatorArrow *indicator;

    if (gShowCourseDirections) {
        timer = racer->indicator_timer;
        if (timer > 0) {
            type = racer->indicator_type;
            racer->indicator_timer = timer - updateRate;
            if (type) {
                indicator = (IndicatorArrow *) &gCurrentHud->courseIndicator;
                switch (type) {
                case INDICATOR_LEFT:
                    indicator->textureID = 33;
                    indicator->unk0 = 0;
                    break;
                case INDICATOR_LEFT_SHARP:
                    indicator->textureID = 32;
                    indicator->unk0 = 0;
                    break;
                case INDICATOR_LEFT_UTURN:
                    indicator->textureID = 31;
                    indicator->unk0 = 0;
                    break;
                case INDICATOR_RIGHT:
                    indicator->textureID = 33;
                    indicator->unk0 = -0x8000;
                    break;
                case INDICATOR_RIGHT_SHARP:
                    indicator->textureID = 32;
                    indicator->unk0 = -0x8000;
                    break;
                case INDICATOR_RIGHT_UTURN:
                    indicator->textureID = 31;
                    indicator->unk0 = -0x8000;
                    break;
                case INDICATOR_UP:
                    indicator->textureID = 30;
                    indicator->unk0 = -0x8000;
                    indicator->unk2 = -0x8000;
                    break;
                case INDICATOR_DOWN:
                    indicator->textureID = 30;
                    indicator->unk0 = 0;
                    break;
                default: // INDICATOR_EXCLAMATION
                    indicator->textureID = 29;
                    indicator->unk0 = 0;
                    break;
                }
                // Flip the arrow direction on adventure 2.
                if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS && racer->indicator_type < 30) {
                    indicator->unk0 = (s16) (0x8000 - indicator->unk0);
                }
                if (gHUDNumPlayers == ONE_PLAYER && racer->raceFinished == FALSE && racer->indicator_type && D_800E27B8 == 0) {
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) indicator);
                    indicator->unkC = -indicator->unkC;
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) indicator);
                    indicator->unkC = -indicator->unkC;
                    indicator->unk2 = 0;
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                }
            }
        } else {
            racer->indicator_timer = 0;
        }
        if (D_800E27B8) {
            if (D_800E27B8 & 0x20) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                indicator = (IndicatorArrow *) &gCurrentHud->courseIndicator;
                indicator->unk0 = 0;
                indicator->unk2 = 0;
                indicator->textureID = 29;
                if ((get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) && ((s32) racer->indicator_type < 30)) {
                    indicator->unk0 = (s16) (0x8000 - indicator->unk0);
                }
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) indicator);
                indicator->unkC = (f32) -indicator->unkC;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) indicator);
                indicator->unkC = (f32) -indicator->unkC;
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
            if (updateRate < D_800E27B8) {
                D_800E27B8 -= updateRate;
                return;
            }
            D_800E27B8 = 0;
        }
    }
}

/*
 * Renders the HUD for the Smokey Castle challenge.
 * Shows each players portrait and their aquired treasure.
*/
void render_hud_banana_challenge(s32 arg0, Object *obj, s32 updateRate) {
    Object_Racer *racer;
    Object **racers;
    s32 numRacers;
    s32 i;

    racer = &obj->unk64->racer;
    racers = get_racer_objects(&numRacers);
    func_80068508(TRUE);
    render_race_start(arg0, updateRate);
    switch (gNumActivePlayers) {
    case 1:
        for (i = 0; i < numRacers; i++) {
            racer = &racers[i]->unk64->racer;
            render_treasure_hud(racer);
            if (i == 1) {
                gCurrentHud->unk64C += 55.0f;
                gCurrentHud->unk40C += 55.0f;
            }
            gCurrentHud->unk64C += 55.0f;
            gCurrentHud->unk40C += 55.0f;
        }
        if (1) {} // Fakematch
        gCurrentHud->unk64C -= 275.0f;
        gCurrentHud->unk40C -= 275.0f;
        break;
    case 3:
    case 4:
        render_treasure_hud(racer);
        break;
    }
    racer = &obj->unk64->racer;
    reset_render_settings(&gHUDCurrDisplayList);
    render_racer_bananas(racer, updateRate);
    render_weapon_hud(obj, updateRate);
    func_80068508(FALSE);
}

/**
 * The Egg Collector challenge mode displays the icons of each player and their score.
*/
void render_hud_challenge_eggs(s32 arg0, Object *obj, s32 updateRate) {
    Object_Racer *racer = &obj->unk64->racer;
    if (racer->raceFinished == FALSE) {
        func_80068508(TRUE);
        render_race_start(arg0, updateRate);
        render_weapon_hud(obj, updateRate);
        if ((127 - (updateRate * 2)) >= gCurrentHud->unk67A) {
            gCurrentHud->unk67A += updateRate * 2;
        } else {
            gCurrentHud->unk67A = (gCurrentHud->unk67A + (updateRate * 2)) - 255;
        }
        if (gNumActivePlayers != 2) {
            func_800A14F0(obj, updateRate);
        }
        func_80068508(FALSE);
    }
}

void func_800A14F0(Object *racerObj, s32 updateRate) {
    Object **racers;
    s32 i;
    Object_Racer *racer;
    s32 numRacers;
    s32 numOfFinishedPlayers;
    Object_Racer *curRacer;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;

    racers = get_racer_objects(&numRacers);
    if (gNumActivePlayers == 2) {
        numOfFinishedPlayers = 0;
        for(i = 0; i < numRacers; i++) {
            curRacer = &racers[i]->unk64->racer;
            if(curRacer->playerIndex != -1 && curRacer->raceFinished) {
                numOfFinishedPlayers++;
            }
        }
        if (numOfFinishedPlayers == 2) {
            return;
        }
    }
    if (racerObj != NULL) {
        racer = &racerObj->unk64->racer;
    } else {
        racer = &racers[0]->unk64->racer;
    }
    if (numRacers == 4) {
        func_80068508(TRUE);
        sp44 = (s32) gCurrentHud->unk64C;
        sp3C = (s32) gCurrentHud->unk650;
        sp40 = (s32) (gCurrentHud->unk66C - sp44);
        sp38 = (s32) (gCurrentHud->unk670 - sp3C);
        for(i = 0; i < 4; i++) {
            curRacer = &racers[i]->unk64->racer;
            if (((s32) gNumActivePlayers < 3) || (racer->playerIndex == curRacer->playerIndex)) {
                func_800A19A4(curRacer, updateRate);
            }
            gHudColour = -2;
            if (gNumActivePlayers == 1) {
                gCurrentHud->unk64C += 68.0f;
            } else if (gNumActivePlayers == 2) {
                gCurrentHud->unk64C = sp44;
                if (osTvType == 0) {
                    gCurrentHud->unk650 = (f32) ((f64) gCurrentHud->unk650 + 66.0);
                    gCurrentHud->unk670 = (f32) ((f64) gCurrentHud->unk670 + 66.0);
                } else {
                    gCurrentHud->unk650 += 55.0f;
                    gCurrentHud->unk670 += 55.0f;
                }
            }
            gCurrentHud->unk66C = gCurrentHud->unk64C + sp40;
        }
        gCurrentHud->unk64C = sp44;
        gCurrentHud->unk66C = sp44 + sp40;
        gCurrentHud->unk650 = sp3C;
        gCurrentHud->unk670 = sp3C + sp38;
        func_80068508(FALSE);
    }
}


void func_800A19A4(Object_Racer *racer, UNUSED s32 updateRate) {
    s32 i;
    UNUSED s32 pad;
    s32 sp44;
    s32 sp40;
    s32 i2;

    sp40 = (s32) gCurrentHud->unk66C;
    gCurrentHud->unk646 = racer->characterId + 56;
    D_80126CD5 = 1;
    if (((s32) gNumActivePlayers < 3) || ((gNumActivePlayers == 3) && (racer->playerIndex == -1))) {
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk640);
    }
    if (gCurrentHud->unk67A < 0) {
        sp44 = (gCurrentHud->unk67A * 2) + 256;
    } else {
        sp44 = 255 - (gCurrentHud->unk67A * 2);
    }
    if (sp44 > 254) {
        sp44 = 254;
    }
    for (i = 0; (i < racer->lap) && (i < 3); i++) {
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk660);
        gCurrentHud->unk66C += 12.0f;
    }
    gHudColour = sp44 | ~0xFF;
    i2 = i;
    for (i = 0; (i < racer->eggHudCounter) && (i2 < 3); i++) {
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk660);
        i2++;
        gCurrentHud->unk66C += 12.0f;
    }
    gCurrentHud->unk66C = (f32) sp40;
    D_80126CD5 = 0;
}

/**
 * Render the HUD for the battle mode challenge.
 * Shows each players portrait and their remaining health.
*/
void render_hud_battle(s32 arg0, Object *obj, s32 updateRate) {
    Object **racerObjs;
    Object_Racer *racer;
    s32 numRacers;
    s32 racersFinished;
    s32 i;

    racer = (Object_Racer *) obj->unk64;
    if (gNumActivePlayers != 1 || racer->raceFinished == FALSE) {
        func_80068508(TRUE);
        render_race_start(arg0, updateRate);
        render_weapon_hud(obj, updateRate);
        racerObjs = get_racer_objects(&numRacers);
        switch (gNumActivePlayers) {
            case 1:
                func_800A1E48(obj, updateRate);
                break;
            case 2:
                racersFinished = 0;
                for (i = 0; i < numRacers; i++) {
                    racer = &racerObjs[i]->unk64->racer;
                    if (racer->playerIndex != PLAYER_COMPUTER && racer->raceFinished) {
                        racersFinished++;
                    }
                }
                if (racersFinished == 2) {
                    return;
                }
                break;
            default:
                render_racer_bananas(racer, updateRate);
                break;
        }
        func_80068508(FALSE);
    }
}

#ifdef NON_EQUIVALENT
void func_800A1E48(Object *racerObj, s32 updateRate) {
    f32 temp;
    s32 i;
    Object_Racer *racer;
    s32 numRacers;
    Object **racers;
    s32 prevCurrHudUnk64C;
    s32 prevCurrHudUnk650;
    f32 temp2;
    Object_Racer *curRacer;
    s32 offset;
    s32 temp3;
    s32 temp4;
    
    racers = get_racer_objects(&numRacers);
    if (racerObj != NULL) {
        racer = &racerObj->unk64->racer;
    } else {
        racer = &racers[PLAYER_ONE]->unk64->racer;
    }

    func_80068508(TRUE);
    if (numRacers == 4) {
        offset = 0;
        prevCurrHudUnk64C = gCurrentHud->unk64C;
        prevCurrHudUnk650 = gCurrentHud->unk650;
        for (i = 0; i < 4; i++) {
            curRacer = &racers[i]->unk64->racer;
            temp = prevCurrHudUnk64C ^ 0;
            temp3 = temp - gCurrentHud->unk64C;
            temp = temp3;
            temp2 = offset + prevCurrHudUnk650;
            temp4 = temp2 - gCurrentHud->unk650;
            temp2 = temp4;
            gCurrentHud->unk64C += temp;
            gCurrentHud->unk650 += temp2;
            gCurrentHud->unk68C += temp;
            gCurrentHud->unk690 -= temp2;
            gCurrentHud->unk6AC += temp;
            gCurrentHud->unk6B0 += temp2;
            gCurrentHud->unk6CC += temp;
            gCurrentHud->unk6D0 += temp2;
            gCurrentHud->unk6EC += temp;
            gCurrentHud->unk6F0 += temp2;
            if (gNumActivePlayers < 3 || racer->playerIndex == curRacer->playerIndex) {
                func_800A22F4(curRacer, updateRate);
            }
            if (gNumActivePlayers == 1) {
                prevCurrHudUnk64C += 68;
            } else if (gNumActivePlayers == 2) {
                if (osTvType == TV_TYPE_PAL) {
                    offset += 66.0;
                } else {
                    offset += 55;
                }
            }
        }

        temp = prevCurrHudUnk64C;
        temp3 = temp - gCurrentHud->unk64C;
        temp = temp3;
        temp2 = prevCurrHudUnk650;
        temp4 = temp2 - gCurrentHud->unk650;
        temp2 = temp4;
        gCurrentHud->unk64C += temp;
        gCurrentHud->unk650 += temp2;
        gCurrentHud->unk68C += temp;
        gCurrentHud->unk690 -= temp2;
        gCurrentHud->unk6AC += temp;
        gCurrentHud->unk6B0 += temp2;
        gCurrentHud->unk6CC += temp;
        gCurrentHud->unk6D0 += temp2;
        gCurrentHud->unk6EC += temp;
        gCurrentHud->unk6F0 += temp2;
    }
    func_80068508(FALSE);
}
#else
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A1E48.s")
#endif

void func_800A22F4(Object_Racer *racer, UNUSED s32 updateRate) {
    gCurrentHud->unk646 = racer->characterId + 56;
    if (gNumActivePlayers < 3 || (gNumActivePlayers == 3 && racer->playerIndex == PLAYER_COMPUTER)) {
        D_80126CD5 = TRUE;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk640);
        D_80126CD5 = FALSE;
        init_rdp_and_framebuffer(&gHUDCurrDisplayList);
        reset_render_settings(&gHUDCurrDisplayList);
    }
    if (racer->bananas < 10) {
        gCurrentHud->unk6D8 = racer->bananas;
        if (gNumActivePlayers == 2) {
            gCurrentHud->unk6CC += 6.0f;
        }
    } else {
        gCurrentHud->unk6D8 = racer->bananas / 10;
        gCurrentHud->unk6F8 = racer->bananas % 10;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk6E0);
    }
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk6C0);
    if (gNumActivePlayers == 2 && racer->bananas < 10) {
        gCurrentHud->unk6CC -= 6.0f;
    }
    if (gNumActivePlayers != 2) {
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk6A0);
        sprite_opaque(TRUE);
        D_80126CD5 = TRUE;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk680);
        D_80126CD5 = FALSE;
        sprite_opaque(FALSE);
    }
}

/**
 * When racing the boss, render the essentials, but skip the bananas.
*/
void render_hud_race_boss(s32 arg0, Object *obj, s32 updateRate) {
    LevelHeader *level;
    Object_Racer *racer = (Object_Racer *) obj->unk64;

    func_80068508(TRUE);
    render_wrong_way_text(racer, updateRate);
    render_race_start(arg0, updateRate);
    render_race_time(racer, updateRate);
    render_weapon_hud(obj, updateRate);

    level = get_current_level_header();
    if (level->laps > 1) {
        render_lap_count(racer, updateRate);
    }

    render_speedometer(obj, updateRate);
    render_race_position(racer, updateRate);
    func_80068508(FALSE);
}

/**
 * When racing Taj in the overworld, render most of the basic race hud.
*/
void render_hud_taj_race(s32 arg0, Object *obj, s32 updateRate) {
    Object_Racer *racer = (Object_Racer *) obj->unk64;

    func_80068508(TRUE);
    render_wrong_way_text(racer, updateRate);
    render_lap_count(racer, updateRate);
    render_race_position(racer, updateRate);
    render_race_time(racer, updateRate);
    render_race_start(arg0, updateRate);
    render_speedometer(obj, updateRate);
    func_80068508(FALSE);
}

/**
 * The hub world displays the player's balloon count.
 * In two player adventure, the icon of the character of the player sitting out is displayed.
*/
void render_hud_hubworld(Object *obj, s32 updateRate) {
    Object_Racer *racer;
    unk80126CDC *temp_a3;

    if (get_viewport_count() == 0) {
        racer = (Object_Racer *) obj->unk64;
        func_80068508(TRUE);
        render_balloon_count(racer);
        render_speedometer(obj, updateRate);
        if (is_in_two_player_adventure()) {
            temp_a3 = (unk80126CDC *) &gCurrentHud->unk720;
            temp_a3->unk6 = (get_settings()->racers[1].character + 0x38);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) temp_a3);
        }
        func_80068508(FALSE);
    }
}

#ifdef NON_MATCHING
// render_hud_time_trial
// https://decomp.me/scratch/BWqz9
// Draws Time Trial HUD. Also handles music/audio?
void func_800A277C(s32 arg0, Object* playerRacerObj, s32 updateRate) {
    s32 i;
    s32 spB8;
    s32 spB4;
    s32 spB0;
    s32 spAC;
    s32 stopwatchTimer;
    s32 temp_lo;
    Object_Racer *curRacer;
    Object *ttSWBodyObject;
    Object_68 *obj68;
    LevelObjectEntryCommon ttSWBody;
    LevelObjectEntryCommon ttSWArms;
    UNUSED s32 temp_a0_2;
    s32 temp_t6;
    u16 stopwatchEndSoundID;
    s32 recordTime;
    u16 newLapSoundID;
    f32 posX;
    f32 posY;
    f32 posZ;
    UNUSED f32 new_var;
    char *SWMessage[3];
    
    curRacer = &playerRacerObj->unk64->racer;
    stopwatchTimer = 0;
    if (gAssetHudElements->entry[20] == NULL) {
        ttSWBody.objectID = gAssetHudElementIds[20] & 0xFFFF;
        ttSWBody.size = 8;
        ttSWBody.x = 0;
        ttSWBody.y = 0;
        ttSWBody.z = 0;
        gAssetHudElements->entry[20] = spawn_object(&ttSWBody, 0);
        gCurrentHud->unk340 = -0x8000;
        if (gAssetHudElements->entry[20] != NULL) {
             ((Object *) gAssetHudElements->entry[20])->segment.animFrame = 0;
        }
    }
    if (gAssetHudElements->entry[34] == 0) {
        ttSWArms.objectID = gAssetHudElementIds[34] & 0xFFFF;
        ttSWArms.size = 8;
        ttSWArms.x = 0;
        ttSWArms.y = 0;
        ttSWArms.z = 0;
        gAssetHudElements->entry[34] = spawn_object(&ttSWArms, 0);
        gCurrentHud->unk440 = -0x8000;
    }
    ttSWBodyObject = gAssetHudElements->entry[20];
    if (ttSWBodyObject != NULL) {
        ttSWBodyObject->segment.object.animationID = gStopwatchFaceID;
        obj68 = (Object_68 *) ttSWBodyObject->unk68[0];
        obj68->objModel->unk52 = updateRate;
        if (gStopwatchFaceID != 0xFF) {
            if ((gStopwatchFaceID == 4) && ((get_race_countdown()) || (!music_is_playing()))) {
                ttSWBodyObject->segment.animFrame = 16;
            } else if (gStopwatchFaceID == 4) {
                posX = music_animation_fraction();
                temp_t6 = (obj68->objModel->animations[gStopwatchFaceID].unk4 - 1) << 4;
                if (posX == -1.0) {
                    ttSWBodyObject->segment.animFrame = 0.0;
                } else if (posX > 0.5) {
                    ttSWBodyObject->segment.animFrame = (temp_t6 - ((f32) (2.0 * (f32) (posX - 0.5)) * temp_t6));
                } else {
                    new_var = posX;
                    ttSWBodyObject->segment.animFrame = temp_t6 * (posX * 2);
                }
            } else if (!is_game_paused()) {
                if (D_80126D69 < 0) {
                    if (-(updateRate * D_80126D69) < ttSWBodyObject->segment.animFrame) {
                        ttSWBodyObject->segment.animFrame += (updateRate * D_80126D69);
                    } else {
                        ttSWBodyObject->segment.animFrame = 1;
                        D_80126D69 = -D_80126D69;
                    }
                } else {
                    ttSWBodyObject->segment.animFrame += (updateRate * D_80126D69);
                    temp_lo = (obj68->objModel->animations[gStopwatchFaceID].unk4 - 1) << 4;
                    if (ttSWBodyObject->segment.animFrame >= temp_lo) {
                        if (D_80126D68 != 0) {
                            D_80126D69 = -D_80126D69;
                            ttSWBodyObject->segment.animFrame = temp_lo - 1;
                        } else {
                            ttSWBodyObject->segment.animFrame = 0;
                            if (curRacer->unk1FC == 0 && curRacer->raceFinished == 0) {
                                set_stopwatch_face(4, 0, 4, 1, 1);
                            }
                        }
                    }
                }
            }
            object_animate(ttSWBodyObject);
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC** ) &gCurrentHud->unk340);
        
        for(i = 0; curRacer->lap >= i && i < 5; i++) { 
            stopwatchTimer += curRacer->lap_times[i];
        }
        
        if (osTvType == TV_TYPE_PAL) {
            stopwatchTimer = (f32) stopwatchTimer * 1.2;
        }
        if (normalise_time(36000) < stopwatchTimer) {
            stopwatchTimer = normalise_time(36000);
        }
        gCurrentHud->unk444 = ((stopwatchTimer * 0x444) + 0x7FF8);
        if (get_contpak_error() <= 0) {
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) &gCurrentHud->unk440);
        }
        gCurrentHud->unk444 = ((((stopwatchTimer / 60) + 30) % 60) * 0x444);
        gCurrentHud->unk450 = gCurrentHud->unk350 + 28.0f;
        if (get_contpak_error() <= 0) {
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) &gCurrentHud->unk440);
        }
        obj68->unk20 = 0;
        func_80068508(TRUE);
        render_course_indicator_arrows(curRacer, updateRate);
        if (!curRacer->raceFinished) {
            spB8 = gCurrentHud->unk2F0;
            for (i = 0; i < curRacer->countLap && i < gHudLevelHeader->laps; i++) {
                 // FAKEMATCH
                get_timestamp_from_frames(curRacer->lap_times[i] & 0xFFFFFFFFFFFFFFFF, &spB4, &spB0, &spAC);
                gHudColour = D_800E27AC[i];
                render_timer(gCurrentHud->unk2EC, spB8, spB4, spB0, spAC, 1);
                gHudColour = COLOUR_RGBA32(255, 255, 255, 254);
                spB8 += 12;
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                gCurrentHud->unk338 = i + 1;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) &gCurrentHud->unk320);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) &gCurrentHud->unk300);
                gCurrentHud->unk330 += 12.0f;
                gCurrentHud->unk310 += 12.0f;
            }
            if (1) {} // FAKEMATCH
            posX = ((i * 4) - i) * 4;
            gCurrentHud->unk330 -= posX;
            gCurrentHud->unk310 -= posX;
            if ((curRacer->boost_sound & BOOST_SOUND_UNK4) && (D_80126D4C <= 0)) {
                set_stopwatch_face(7, 3, 0, 4, 0);
                D_80126D4C = 60;
                curRacer->boost_sound &= ~BOOST_SOUND_UNK4;
            }
            if (D_80126D4C > 0) {
                D_80126D4C -= updateRate;
                if (D_80126D4C < 0) {
                    D_80126D4C = 0;
                }
            }
            if ((D_80126D4C == 0) && (!curRacer->raceFinished)) {
                D_80126D4C = -100;
                if (gHUDVoiceSoundMask == 0) {
                    stopwatchEndSoundID = get_random_number_from_range(0, D_80126D64 + 2) + SOUND_VOICE_TT_OH_NO;
                    while (D_80126D48 == stopwatchEndSoundID) {
                        stopwatchEndSoundID = get_random_number_from_range(0, D_80126D64 + 2) + SOUND_VOICE_TT_OH_NO;
                    }
                    D_80126D48 = (u16) stopwatchEndSoundID;
                    sound_play(stopwatchEndSoundID, &gHUDVoiceSoundMask);
                    D_80126D64 = 1;
                }
            }
        }
        if ((curRacer->lap > 0) && (curRacer->lap < gHudLevelHeader->laps) && (curRacer->lap_times[curRacer->lap] < 20) && (gHUDVoiceSoundMask == 0) && (curRacer->vehicleID <= VEHICLE_PLANE)) {
            gHudSettings = get_settings();
            if (curRacer->lap_times[curRacer->lap - 1] < gHudSettings->flapTimesPtr[curRacer->vehicleID][get_current_map_id()]) {
                recordTime = curRacer->lap_times[curRacer->lap - 1];
                for (i = 0; i < curRacer->lap - 1; i++) {
                    if (recordTime >= curRacer->lap_times[i]) {
                        recordTime = 0;
                    }
                }
                if (recordTime) {
                    sound_play(SOUND_VOICE_TT_LAP_RECORD, &gHUDVoiceSoundMask);
                }
            }
        }
        if (func_8001B288()) {
            ttSWBodyObject = func_8001B2E0();
            if (ttSWBodyObject != NULL) {
                if ((get_race_countdown() == 0) && (curRacer->raceFinished == 0)) {
                    posY = ttSWBodyObject->segment.trans.y_position - playerRacerObj->segment.trans.y_position;
                    posX = ttSWBodyObject->segment.trans.x_position - playerRacerObj->segment.trans.x_position;
                    posZ = ttSWBodyObject->segment.trans.z_position - playerRacerObj->segment.trans.z_position;
                    if ((sqrtf(posX * posX + (posY * posY) + (posZ * posZ)) < 600.0f) && (gHUDVoiceSoundMask == 0) && (D_80126D50 == 0)) {
                        newLapSoundID = (get_random_number_from_range(0, 2) + SOUND_VOICE_TT_GO_FOR_IT);
                        while (D_80126D48 == newLapSoundID) {
                            newLapSoundID = (get_random_number_from_range(0, 2) + SOUND_VOICE_TT_GO_FOR_IT);
                        }
                        D_80126D48 = newLapSoundID;
                        sound_play(newLapSoundID, &gHUDVoiceSoundMask);
                        D_80126D50 = get_random_number_from_range(120, 1200);
                    }
                    D_80126D50 -= updateRate;
                    if (D_80126D50 < 0) {
                        D_80126D50 = 0;
                    }
                }
            }
        }
        if ((curRacer->lap_times[curRacer->lap] < 30) && (curRacer->lap != 0)) {
            set_stopwatch_face(5, 1, 2, 2, 0);
        } else if (curRacer->boostTimer > 0) {
            set_stopwatch_face(6, 2, 3, 2, 0);
        } else if (curRacer->unk1FC > 120) {
            set_stopwatch_face(6, 3, 1, 4, 0);
        }
        render_lap_count(curRacer, updateRate);
        render_race_time(curRacer, updateRate);
        render_racer_bananas(curRacer, updateRate);
        render_wrong_way_text(curRacer, updateRate);
        render_race_start(arg0, updateRate);
        render_speedometer(playerRacerObj, updateRate);
        if (get_contpak_error() > 0) {
            switch (get_contpak_error()) {
                case 1:
                    SWMessage[0] = "CAN'T";
                    SWMessage[1] = "SAVE";
                    SWMessage[2] = "GHOST";
                    break;
                case 2:
                    SWMessage[0] = " CONTROLLER";
                    SWMessage[1] = "PAK";
                    SWMessage[2] = "FULL";
                    break;
                case 3:
                    SWMessage[0] = " CONTROLLER";
                    SWMessage[1] = "PAK";
                    SWMessage[2] = "DAMAGED";
                    break;
            }
            set_kerning(1);
            set_text_font(ASSET_FONTS_FUNFONT);
            // Draw text shadow.
            set_text_colour(0, 0, 0, 255, 255);
            draw_text(&gHUDCurrDisplayList, D_8012718C + D_80126D24 + D_80126D28 + 1, D_80127190 + 1, SWMessage[0], ALIGN_MIDDLE_CENTER);
            draw_text(&gHUDCurrDisplayList, D_8012718C + D_80126D24 + D_80126D28 + 1, D_80127190 + 15, SWMessage[1], ALIGN_MIDDLE_CENTER);
            draw_text(&gHUDCurrDisplayList, D_8012718C + D_80126D24 + D_80126D28 + 1, D_80127190 + 29, SWMessage[2], ALIGN_MIDDLE_CENTER);
            // Draw actual text.
            set_text_colour(D_80127194->red, D_80127194->green, D_80127194->blue, 128, D_80127194->alpha);
            draw_text(&gHUDCurrDisplayList, D_8012718C + D_80126D24 + D_80126D28, D_80127190, SWMessage[0], ALIGN_MIDDLE_CENTER);
            draw_text(&gHUDCurrDisplayList, D_8012718C + D_80126D24 + D_80126D28, D_80127190 + 14, SWMessage[1], ALIGN_MIDDLE_CENTER);
            draw_text(&gHUDCurrDisplayList, D_8012718C + D_80126D24 + D_80126D28, D_80127190 + 28, SWMessage[2], ALIGN_MIDDLE_CENTER);
            update_colour_cycle(D_80127194, updateRate);
            set_kerning(0);
        }
        func_80068508(FALSE);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A277C.s")
#endif

void set_stopwatch_face(u8 arg0, u8 arg1, u8 faceID, u8 arg3, u8 arg4) {
    s32 var_a3;
    s32 i;
    UNUSED u8 *temp_v0_2;
    Object_68 **unk68;
    Object *hud20;

    if (is_in_time_trial()) {
        hud20 = gAssetHudElements->entry[20];
        if (hud20 != NULL) {
            unk68 = (Object_68 **) hud20->unk68[0];
            var_a3 = unk68[0]->unk28;
            
            for (i = 0; i < var_a3; i++) {
                if (D_80126D66 == unk68[0]->unk38[i].unk0[0]) {
                    unk68[0]->unk38[i].unk0[0] = arg0;
                    if (arg0 == 4) {
                        unk68[0]->unk38[i].unk8 |= (0x800000 | 0x10000);
                        unk68[0]->unk50 = 1;
                    } else {
                        unk68[0]->unk38[i].unk8 &= ~(0x800000 | 0x10000);
                        unk68[0]->unk50 = 0;
                    }
                    var_a3 = unk68[0]->unk28;
                } else if (D_80126D65 == unk68[0]->unk38[i].unk0[0]) {
                    unk68[0]->unk38[i].unk0[0] = arg1;
                    var_a3 = unk68[0]->unk28;
                }                
            }
            D_80126D66 = arg0;
            D_80126D65 = arg1;
            gStopwatchFaceID = faceID;
            D_80126D69 = arg3;
            D_80126D68 = arg4;
        }
    }
}

void func_800A3870(void) {
    gCurrentHud->unk4C4 = 0x6490;
}

/**
 * When enabled, displays speed of the player in the bottom right corner, replacing the minimap.
 * Speed is calculated by normalising racer velocity. then scaling the angle of the needle with that number.
*/
void render_speedometer(Object *obj, UNUSED s32 updateRate) {
    f32 vel;
    Object_Racer *racer;
    s32 opacity;

    if (gNumActivePlayers == 1) {
        if (!check_if_showing_cutscene_camera()) {
            racer = (Object_Racer *) obj->unk64;
            if (racer->raceFinished == FALSE) {
                if (racer->vehicleID == VEHICLE_PLANE) {
                    vel = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.y_velocity * obj->segment.y_velocity) + (obj->segment.z_velocity * obj->segment.z_velocity));
                } else {
                    vel = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) + (obj->segment.z_velocity * obj->segment.z_velocity));
                }
                if (D_800E2838 < vel) {
                    D_800E2838 = vel;
                }
                vel *= 4.0f;
                if (racer->drift_direction != 0) {
                    vel += 7.0f;
                }
                if (vel > 100.0f) {
                    vel = 100.0f;
                }
                if (racer->velocity > 0.0f) {
                    vel = 0.0f;
                }
                vel = 100.0f - vel;
                vel *= 300.0f;
                if (vel > 25744.0f) {
                    vel = 25744.0f;
                }
                if (!is_game_paused()) {
                    if (vel < gCurrentHud->unk4C4) {
                        gCurrentHud->unk4C4 += ((vel - gCurrentHud->unk4C4) / 2);
                    } else {
                        gCurrentHud->unk4C4 += ((vel - gCurrentHud->unk4C4) / 8);
                    }
                }
                if (gHudToggleSettings[gHUDNumPlayers] == 0) {
                    if (D_80126CD3 & 2) {
                        opacity = 255.0f - ((D_80126CD0 * 255.0f) / D_8012718B);
                    } else {
                        opacity = 255;
                    }
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk5A0);
                    reset_render_settings(&gHUDCurrDisplayList);
                    sprite_opaque(TRUE);
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, opacity);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk4C0);
                    sprite_opaque(FALSE);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk4E0);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk500);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk520);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk540);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk560);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk580);
                }
            }
        }
    }
}


/**
 * Call the functions that render the "Get Ready" and "GO!" as well as their countdowns to control fade.
 * This function will also call to begin the background music for 1 and 2 player. 3 and 4 are treated with silence.
*/
void render_race_start(s32 arg0, s32 updateRate) {

    if (!is_game_paused()) {
        if (arg0 == 0 && D_800E2770[0].playerIndex == PLAYER_COMPUTER) {
            D_800E2770[0].unk3 = -1;
            D_800E2770[1].unk3 = -1;
        }
        if (gHUDNumPlayers == TWO_PLAYERS) {
            sprite_opaque(TRUE);
        }
        if (arg0 > 0) {
            if (D_80126D34) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, (arg0 * 255) / 40);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk1A0);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                if (gRaceStartShowHudStep == 2) {
                    sound_play(SOUND_VOICE_TT_GET_READY, &gHUDVoiceSoundMask);
                    gRaceStartShowHudStep++;
                }
            }
            if (D_80126D3C == NULL && func_80023568() == 0) {
                f32 sp4C;
                UNUSED s32 pad;
                Object** racerGroup;
                Object* randomRacer;
                Object_Racer* racer;
                s32 numRacerObjects;
                racerGroup = get_racer_objects(&numRacerObjects);
                randomRacer = racerGroup[get_random_number_from_range(1, numRacerObjects) - 1];
                racer = (Object_Racer*)randomRacer->unk64;
                if (racer->vehicleID == VEHICLE_CAR) {
                    if (get_random_number_from_range(0, 100) >= 96) {
                        sp4C = 1.25 - ((get_random_number_from_range(0, 7) * 0.5) / 7.0);
                        func_800095E8(76, randomRacer->segment.trans.x_position, randomRacer->segment.trans.y_position, randomRacer->segment.trans.z_position, 4, ((get_random_number_from_range(0, 7) * 63) / 7) + 24, sp4C * 100.0f, &D_80126D3C);
                    }
                }
            }
        } else if (gCurrentHud->unk18C > -200.0f) {
            gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk180);
            gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            gCurrentHud->unk19A[gHudCurrentViewport] += updateRate;
            if (gCurrentHud->unk19A[gHudCurrentViewport] >= 60) {
                if (gRaceStartShowHudStep == 4) {
                    // Mute background music in 3/4 player.
                    if (get_viewport_count() > TWO_PLAYERS) {
                        music_play(SEQUENCE_NONE);
                    } else {
                        start_level_music(1.0f);
                    }
                    sound_play(SOUND_WHOOSH1, NULL);
                    gRaceStartShowHudStep++;
                }
                gCurrentHud->unk18C -= (updateRate * 8);
            }
            if (gRaceStartShowHudStep == 3) {
                sound_play(SOUND_VOICE_TT_GO, &gHUDVoiceSoundMask);
                if (get_time_trial_ghost() && unbeaten_staff_time() == FALSE) {
                    set_time_trial_start_voice(SOUND_VOICE_TT_BEAT_MY_TIME, 1.7f, 0);
                    set_delayed_text(ASSET_GAME_TEXT_82, 1.7f); // Now try and beat my time!
                }
                D_80126D70 = 1;
                gRaceStartShowHudStep++;
            }
        }
        sprite_opaque(FALSE);
    }
}

/**
 * Renders the banana counter on screen.
 * When a banana is collected, render sparkles and animate the banana. for a brief moment.
*/
void render_racer_bananas(Object_Racer *racer, s32 updateRate) {
    s32 bananas;
    UNUSED s16 pad;
    s32 temp_lo;
    u8 var_v1;
    if(racer->playerIndex == PLAYER_COMPUTER || (((gHUDNumPlayers < TWO_PLAYERS || D_800E2794[gHUDNumPlayers][racer->playerIndex] == PLAYER_THREE || gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BANANAS || gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BATTLE) && racer->raceFinished == FALSE) && (gHUDNumPlayers < TWO_PLAYERS || (racer->lap < 1) || racer->lap_times[racer->lap] >= 180 || gHudLevelHeader->race_type & RACETYPE_CHALLENGE))) {
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk240);
        bananas = racer->bananas;
        var_v1 = gCurrentHud->unkF8;
        if ((gCurrentHud->unkFA == 0) && (gCurrentHud->unkFB != racer->bananas)) {
            gCurrentHud->unkFA = 2;
            gCurrentHud->unkFB = racer->bananas;
        } else if (gCurrentHud->unkFA) {
            gCurrentHud->unk388 = 2.0f;
            var_v1 += updateRate * 13;
            if (var_v1 < (gCurrentHud->unkF8 & 0xFF)) {
                gCurrentHud->unkFA--;
                if (gCurrentHud->unkFA == 0) {
                    gCurrentHud->unk39B = 1;
                    gCurrentHud->unk39A = 6;
                    var_v1 = 0;
                    gCurrentHud->unk398 = 1;
                }
            }
        }
        if (var_v1 == 0) {
            sprite_opaque(TRUE);
            set_viewport_tv_type(TV_TYPE_NTSC);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk360);
            set_viewport_tv_type(TV_TYPE_PAL);
            sprite_opaque(FALSE);
            gCurrentHud->unkF8 = var_v1;
            if (gCurrentHud->unk39B) {
                gCurrentHud->unk39A -= updateRate;
                if (gCurrentHud->unk39A < 0) {
                    gCurrentHud->unk39A = 6;
                    if (gCurrentHud->unk398 == 6) {
                        gCurrentHud->unk398 = 0;
                        gCurrentHud->unk39B--;
                    } else {
                        gCurrentHud->unk398++;
                    }
                }
                set_viewport_tv_type(TV_TYPE_NTSC);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk380);
                set_viewport_tv_type(TV_TYPE_PAL);
            }
        } else {
            gCurrentHud->unkF8 = var_v1 + 128;
            func_80068508(FALSE);
            sprite_opaque(TRUE);
            set_viewport_tv_type(TV_TYPE_NTSC);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unkE0);
            sprite_opaque(FALSE);
            set_viewport_tv_type(TV_TYPE_PAL);
            func_80068508(TRUE);
            gCurrentHud->unkF8 -= 128;
        }
        temp_lo = bananas / 10;
        if (temp_lo) {
            gCurrentHud->unk118 = temp_lo;
            gCurrentHud->unk138 = bananas % 10;
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk120);
        } else {
            gCurrentHud->unk118 = bananas % 10;
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk100);
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    }
}

/**
 * Renders the icons and secured treasure in Smokey's castle.
 * In 4 player, all icons are skipped and in 3 player, player 4's icon is shown on their quadrant.
*/
void render_treasure_hud(Object_Racer *racer) {
    s32 i;
    s32 sp48;

    sp48 = gCurrentHud->unk410;
    if (gNumActivePlayers < 3 || (gNumActivePlayers == 3 && racer->playerIndex == PLAYER_COMPUTER)) {
        gCurrentHud->unk646 = racer->characterId + 56;
        D_80126CD5 = TRUE;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk640);
        D_80126CD5 = FALSE;
    }
    for (i = 0; i < 10; i++) {
        if (i >= racer->lap) {
            gHudColour = COLOUR_RGBA32(128, 128, 128, 128);
        }
        D_80126CD5 = TRUE;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk400);
        D_80126CD5 = FALSE;
        gCurrentHud->unk410 -= 3.0f;
    }
    gCurrentHud->unk410 = sp48;
    gHudColour = COLOUR_RGBA32(255, 255, 255, 254);
    D_80126CD5 = FALSE;
}

/**
 * Render the silver coin counter on the side of the screen.
 * When the 8th coin is collected, wait a second then play an encouraging voice clip from T.T.
*/
void render_silver_coin_counter(Object_Racer *racer, s32 updateRate) {
    s32 i;
    s32 prevUnk5D0;

    gCurrentHud->unk5D0 = (s32) gCurrentHud->unk5D0; //Rounds float down to it's int value.
    prevUnk5D0 = gCurrentHud->unk5D0;
    for(i = 0; i < 8; i++) {
        if (i >= racer->silverCoinCount) {
            gHudColour = COLOUR_RGBA32(128, 128, 128, 128);
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk5C0);
        gCurrentHud->unk5D0 -= gCurrentHud->unk5DC;
    }
    if (racer->silverCoinCount == 8) {
        if (gCurrentHud->unk5DB < 30) {
            gCurrentHud->unk5DB += updateRate;
        }
        if (gCurrentHud->unk5DA == 0) {
            if (gCurrentHud->unk5DB >= 30) {
                gCurrentHud->unk5DA = 1;
                if (gHUDVoiceSoundMask == NULL) {
                    sound_play(SOUND_VOICE_TT_GO_FOR_IT, &gHUDVoiceSoundMask);
                }
            }
        }
    }
    gCurrentHud->unk5D0 = prevUnk5D0;
    gHudColour = COLOUR_RGBA32(255, 255, 255, 254);
}

/**
 * Plays the race finish fanfare and displays what position you finished
 * in the middle of the screen.
 * Uses a 3 step process to play the sounds, display the position, then slide it offscreen.
*/
void render_race_finish_position(Object_Racer *racer, s32 updateRate) {
    unk800A497C *temp_a3;
    unk800A497C *temp_s0;
    s8 drawPosition;

    temp_a3 = (unk800A497C *) &gCurrentHud->unk700;
    temp_s0 = (unk800A497C *) &gCurrentHud->unk740;
    //temp_s0 = &gCurrentHud->unk740;
    drawPosition = FALSE;
    switch (temp_a3->unk1A) {
        case 0:
            music_voicelimit_set(24);
            music_play(SEQUENCE_FIRST_PLACE);
            sound_play(SOUND_WHOOSH1, NULL);
            sound_play(SOUND_VOICE_TT_FINISH, &gHUDVoiceSoundMask);
            D_800E2770->volume = 127;
            D_800E2770->unk3 = 0;
            D_800E2770->playerIndex = racer->playerIndex;
            temp_a3->unk1A = 1;
            break;
        case 1:
            temp_a3->unkC += updateRate * 13;
            if (temp_a3->unkC > -23.0f) {
                temp_a3->unkC = -23.0f;
            }
            temp_s0->unkC -= updateRate * 13;
            if (temp_s0->unkC < 22.0f) {
                temp_s0->unkC = 22.0f;
            }
            drawPosition = TRUE;
            if (temp_s0->unkC == 22.0f) {
                temp_a3->unk1B += updateRate;
                if (temp_a3->unk1B >= 120) {
                    temp_a3->unk1B = -120;
                    temp_a3->unk1C = temp_a3->unk1C + 1;
                }
                if (temp_a3->unk1C == 2) {
                    temp_a3->unk1A = 2;
                    sound_play(SOUND_WHOOSH1, NULL);
                    if (D_800E2770->playerIndex == racer->playerIndex) {
                        D_800E2770->unk3 = -1;
                    }
                }
            }
            break;
        case 2:
            temp_a3->unkC += updateRate * 13;
            temp_s0->unkC += updateRate * 13;
            drawPosition = TRUE;
            if (temp_a3->unkC > 200.0f) {
                temp_a3->unk1A = 3;
            }
            break;
        case 3:
            temp_a3->unk1A = 3;
            break;
    }
    if (drawPosition) {
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 210);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) temp_a3);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC **) temp_s0);
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    }
}


UNUSED void func_800A4C34(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {}

/**
 * Render the current race position of the racer.
 * Scales up and down when the position changes.
*/
void render_race_position(Object_Racer *racer, s32 updateRate) {
    s32 place;
    f32 prevCurrHudUnkC;
    f32 scale;
    s32 placeIndex;
    Settings *settings;

    if (racer->raceFinished) {
        return;
    }
    place = racer->racePosition;
    if (get_race_countdown()) {
        if (get_current_level_race_type() == RACETYPE_BOSS || is_taj_challenge()) {
            place = 2;
        } else {
            settings = get_settings();
            place = settings->racers[D_80126D10].starting_position;
            gCurrentHud->unk18 = place;
            place++;
        }
    }
    if (gHUDNumPlayers < 2) {
        if (place < 4) {
            gCurrentHud->unk38 = place - 1;
        } else {
            gCurrentHud->unk38 = 3;
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk20);
    }
    scale = (gCurrentHud->unk1B + 129);
    scale *= 128.0f;
    scale = sins_f(scale);
    placeIndex = place - 1;
    gCurrentHud->unk8 = (gCurrentHud->unk1C / 127.0f) + (1.0 + (0.5 * scale));
    prevCurrHudUnkC = gCurrentHud->unkC;
    gCurrentHud->unkC -= (24.0f * gCurrentHud->unk8);
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk0);
    gCurrentHud->unkC = prevCurrHudUnkC;
    if (gCurrentHud->unk1A) {
        if (gCurrentHud->unk1B < 127 - (updateRate * 16)) {
            gCurrentHud->unk1B += (updateRate * 16);
        } else {
            gCurrentHud->unk1B = 127;
        }
    }
    if (placeIndex != gCurrentHud->unk18) {
        if (gCurrentHud->unk1A && gCurrentHud->unk1B > 0) {
            gCurrentHud->unk1B = -gCurrentHud->unk1B;
        } else {
            gCurrentHud->unk1B = -127;
            gCurrentHud->unk1A = 1;
        }
    }
    gCurrentHud->unk18 = placeIndex;
    if (gCurrentHud->unk1A && gCurrentHud->unk1B == 127) {
        gCurrentHud->unk1A = 0;
    }
}


/**
 * Displays the current lap number onscreen.
 * Also displays the "Lap 2" and "Final Lap" messages when the line is crossed.
 * In multiplayer, shows a cut down display, if the display setting is set to show laps.
*/
void render_lap_count(Object_Racer *racer, s32 updateRate) {
    if (racer->raceFinished == FALSE && (gHUDNumPlayers <= ONE_PLAYER || racer->lap <= 0 || racer->lap_times[racer->lap] >= 180) 
            && (gHUDNumPlayers <= ONE_PLAYER || D_800E2794[gHUDNumPlayers][racer->playerIndex] == 3)) {
        if (gHudLevelHeader->laps == (0, racer->countLap + 1) && gHUDNumPlayers < THREE_PLAYERS) {
            gCurrentHud->unk21A += updateRate;
            if (gCurrentHud->unk21A > 6) {
                gCurrentHud->unk218++;
                gCurrentHud->unk21A -= 6;
                if (gCurrentHud->unk218 > 4) {
                    gCurrentHud->unk218 = 0;
                }
            }
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk200);
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk60);
        if (racer->countLap >= gHudLevelHeader->laps - 1) {
            gCurrentHud->unk98 = gHudLevelHeader->laps;
        } else {
            gCurrentHud->unk98 = racer->countLap + 1;
        }
        gCurrentHud->unkD8 = gHudLevelHeader->laps;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk80);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unkA0);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unkC0);
    }
    if (gHUDNumPlayers == TWO_PLAYERS) {
        sprite_opaque(TRUE);
    }
    if (is_game_paused() == FALSE) {
        if (racer->lap_times[racer->lap] < 30 && gCurrentHud->unk3DA == 0 && racer->raceFinished == FALSE) {
            if ((racer->lap == 1) && gHudLevelHeader->laps >= 3) {
                gCurrentHud->unk3DA = 2;
                gCurrentHud->unk3DB = 1;
                gCurrentHud->unk3DD = 0;
                sound_play(SOUND_WHOOSH1, NULL);
                switch (gHUDNumPlayers) {
                case ONE_PLAYER:
                    gCurrentHud->unk3DC = -21;
                    gCurrentHud->unk3FC = 32;
                    gCurrentHud->unk3CC = -200.0f;
                    gCurrentHud->unk3EC = 211.0f;
                    break;
                case TWO_PLAYERS:
                    gCurrentHud->unk3DC = -16;
                    gCurrentHud->unk3FC = 27;
                    gCurrentHud->unk3CC = -200.0f;
                    gCurrentHud->unk3EC = 211.0f;
                    break;
                default:
                    if (racer->playerIndex != PLAYER_ONE && racer->playerIndex != PLAYER_THREE) {
                        gCurrentHud->unk3DC = 60;
                        gCurrentHud->unk3FC = 91;
                        gCurrentHud->unk3CC = -70.0f;
                        gCurrentHud->unk3EC = 221.0f;
                    } else {
                        gCurrentHud->unk3DC = -90;
                        gCurrentHud->unk3FC = -59;
                        gCurrentHud->unk3CC = -220.0f;
                        gCurrentHud->unk3EC = 71.0f;
                    }
                    break;
                }
            } else if (gHudLevelHeader->laps == (0, racer->lap + 1) && racer->lap != 0) {
                gCurrentHud->unk3DA = 3;
                gCurrentHud->unk3DB = -1;
                gCurrentHud->unk3DD = 0;
                sound_play(SOUND_WHOOSH1, NULL);
                switch (gHUDNumPlayers) {
                case ONE_PLAYER:
                    gCurrentHud->unk3DC = 51;
                    gCurrentHud->unk3BC = -41;
                    gCurrentHud->unk3CC = 210.0f;
                    gCurrentHud->unk3AC = -200.0f;
                    break;
                case TWO_PLAYERS:
                    gCurrentHud->unk3DC = 41;
                    gCurrentHud->unk3BC = -31;
                    gCurrentHud->unk3CC = 210.0f;
                    gCurrentHud->unk3AC = -200.0f;
                    break;
                default:
                    if (racer->playerIndex != PLAYER_ONE && racer->playerIndex != PLAYER_THREE) {
                        gCurrentHud->unk3DC = 100;
                        gCurrentHud->unk3BC = 50;
                        gCurrentHud->unk3CC = 100.0f;
                        gCurrentHud->unk3AC = -50.0f;
                    } else {
                        gCurrentHud->unk3DC = -50;
                        gCurrentHud->unk3BC = -100;
                        gCurrentHud->unk3CC = 50.0f;
                        gCurrentHud->unk3AC = -200.0f;
                    }
                    break;
                }
            }
        }
        if (gCurrentHud->unk3DA != 0) {
            if (gCurrentHud->unk3DA == 2) {
                if (gCurrentHud->unk3DB == 1) {
                    if (gCurrentHud->unk3CC < gCurrentHud->unk3DC - (updateRate * 13)) {
                        gCurrentHud->unk3CC = gCurrentHud->unk3CC + (updateRate * 13);
                    } else {
                        gCurrentHud->unk3CC = gCurrentHud->unk3DC;
                    }
                    if (gCurrentHud->unk3EC > gCurrentHud->unk3FC + (updateRate * 13)) {
                        gCurrentHud->unk3EC = gCurrentHud->unk3EC - (updateRate * 13);
                    } else {
                        gCurrentHud->unk3EC = gCurrentHud->unk3FC;
                    }
                    if (racer->lap_times[racer->lap] >= 60) {
                        gCurrentHud->unk3DB = -1;
                        sound_play(SOUND_WHOOSH1, NULL);
                    }
                    if (gCurrentHud->unk3CC == ((0, gCurrentHud))->unk3DC && gCurrentHud->unk3EC == ((0, gCurrentHud))->unk3FC && gCurrentHud->unk3DD == 0) {
                        if (gHUDVoiceSoundMask == NULL) {
                            sound_play(SOUND_VOICE_TT_LAP2, &gHUDVoiceSoundMask);
                        }
                        gCurrentHud->unk3DD = 1;
                    }
                } else if (gCurrentHud->unk3DB == -1) {
                    gCurrentHud->unk3CC = gCurrentHud->unk3CC - (updateRate * 13);
                    gCurrentHud->unk3EC = gCurrentHud->unk3EC + (updateRate * 13);
                    if (gCurrentHud->unk3CC < -200.0f) {
                        gCurrentHud->unk3DA = 0;
                    }
                }
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk3E0);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk3C0);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            } else if (gCurrentHud->unk3DA == 3) {
                if (gCurrentHud->unk3DB == -1) {
                    if (gCurrentHud->unk3CC > gCurrentHud->unk3DC + (updateRate * 13)) {
                        gCurrentHud->unk3CC = gCurrentHud->unk3CC - (updateRate * 13);
                    } else {
                        gCurrentHud->unk3CC = gCurrentHud->unk3DC;
                    }
                    if (gCurrentHud->unk3AC < gCurrentHud->unk3BC - (updateRate * 13)) {
                        gCurrentHud->unk3AC = gCurrentHud->unk3AC + (updateRate * 13);
                    } else {
                        gCurrentHud->unk3AC = gCurrentHud->unk3BC;
                    }
                    if (racer->lap_times[racer->lap] >= 60) {
                        gCurrentHud->unk3DB = 1;
                        sound_play(SOUND_WHOOSH1, NULL);
                    }
                    if (gCurrentHud->unk3CC == ((0, gCurrentHud))->unk3DC && gCurrentHud->unk3AC == ((0, gCurrentHud))->unk3BC && gCurrentHud->unk3DD == 0) {
                        if (gHUDVoiceSoundMask == NULL) {
                            sound_play(SOUND_VOICE_TT_FINAL_LAP, &gHUDVoiceSoundMask);
                        }
                        gCurrentHud->unk3DD = 1;
                    }
                } else if (gCurrentHud->unk3DB == 1) {
                    gCurrentHud->unk3CC = gCurrentHud->unk3CC + (updateRate * 13);
                    gCurrentHud->unk3AC = gCurrentHud->unk3AC - (updateRate * 13);
                    if (gCurrentHud->unk3CC > 200.0f) {
                        gCurrentHud->unk3DA = 0;
                    }
                }
                
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk3A0);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk3C0);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        }
    }
    sprite_opaque(FALSE);
}

/**
 * Players going the wrong way will be nagged by T.T to turn around.
 * This function plays the audio, and makes the text fly in.
*/
void render_wrong_way_text(Object_Racer *obj, s32 updateRate) { 
    f32 textMoveSpeed;
    f32 textPosTarget;

    if (gHUDNumPlayers == TWO_PLAYERS) {
        sprite_opaque(TRUE);
    }
    if (obj->unk1FC > 120 && (gHUDNumPlayers || gCurrentHud->unk46C == gCurrentHud->unk47A[2]) && !is_game_paused()) {
        if ((gWrongWayNagPrefix || gWrongWayNagTimer == 0) && gHUDVoiceSoundMask == NULL) {
            // 20% chance that T.T decides not to precede his nagging with "No no no!"
            if (gWrongWayNagPrefix || get_random_number_from_range(1, 10) >= 8) {
                gWrongWayNagPrefix = FALSE;
                sound_play(SOUND_VOICE_TT_WRONG_WAY, &gHUDVoiceSoundMask);
                gWrongWayNagTimer = get_random_number_from_range(1, 480) + 120;
            } else {
                gWrongWayNagPrefix = TRUE;
                sound_play(SOUND_VOICE_TT_NONONO, &gHUDVoiceSoundMask);
            }
        }
        gWrongWayNagTimer -= updateRate;
        if (gWrongWayNagTimer < 0) {
            gWrongWayNagTimer = 0;
        }
    }
    if (gCurrentHud->unk47A[0]) {
        if (gCurrentHud->unk47A[0] == 1) {
            if (gCurrentHud->unk47A[1] == 1) {
                textMoveSpeed = updateRate * 13;
                gCurrentHud->unk46C += textMoveSpeed;
                textPosTarget = gCurrentHud->unk47A[2];
                if (gCurrentHud->unk46C > textPosTarget) {
                    gCurrentHud->unk46C = textPosTarget;
                }
                gCurrentHud->unk48C -= textMoveSpeed;
                textPosTarget = gCurrentHud->unk49C;
                if (gCurrentHud->unk48C < textPosTarget) {
                    gCurrentHud->unk48C = textPosTarget;
                }
                if (obj->unk1FC <= 90) {
                    gCurrentHud->unk47A[1] = -1;
                    sound_play(SOUND_WHOOSH1, NULL);
                }
            } else if (gCurrentHud->unk47A[1] == -1) {
                textMoveSpeed = updateRate * 13;
                gCurrentHud->unk46C -= textMoveSpeed;
                gCurrentHud->unk48C += textMoveSpeed;
                if (gCurrentHud->unk46C < -200.0f) {
                    gCurrentHud->unk47A[0] = 0;
                }
            }
            if (!is_game_paused()) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk460);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk480);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        }
    } else if (obj->unk1FC > 120) {
        gCurrentHud->unk47A[0] = 1;
        gCurrentHud->unk47A[1] = 1;
        gCurrentHud->unk47A[2] = -31;
        gCurrentHud->unk49C = 52;
        gCurrentHud->unk47A[3] = 0;
        if (gHUDNumPlayers == TWO_PLAYERS) {
            gCurrentHud->unk47A[2] = -21;
            gCurrentHud->unk49C = 42;
        } else  if (gHUDNumPlayers > TWO_PLAYERS) {
            if (obj->playerIndex == PLAYER_ONE || obj->playerIndex == PLAYER_THREE) {
                gCurrentHud->unk47A[2] = -100;
                gCurrentHud->unk49C = -55;
            } else {
                gCurrentHud->unk47A[2] = 59;
                gCurrentHud->unk49C = 104;
            }
        }
        gCurrentHud->unk48C = gCurrentHud->unk49C + 200;
        gCurrentHud->unk46C =  gCurrentHud->unk49C - 200;
        sound_play(SOUND_WHOOSH1, NULL);
    }
    sprite_opaque(FALSE);
}

void func_800A5F18(Object_Racer *racer) {
    s32 sp24;

    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk5E0);
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk600);
    if (!(get_current_level_race_type() & RACETYPE_CHALLENGE_BATTLE) && (is_in_two_player_adventure() == 0)) {
        get_racer_objects(&sp24);
        if (gNumActivePlayers >= 2 && (is_in_two_player_adventure() == FALSE || is_postrace_viewport_active() == FALSE)) {
            set_text_font(FONT_COLOURFUL);
            if (sp24 != racer->unk1AC) {
                set_text_colour(255, 255, 255, 0, 255);
                draw_text(&gHUDCurrDisplayList, gCurrentHud->unk16C - 40.0f, gCurrentHud->unk170, "RACE", ALIGN_TOP_LEFT);
                render_timer(gCurrentHud->unk16C, gCurrentHud->unk170, gCurrentHud->unk17A, gCurrentHud->unk17B, gCurrentHud->unk17C, 1);
                draw_text(&gHUDCurrDisplayList, gCurrentHud->unk2EC - 40.0f, gCurrentHud->unk2F0, "LAP", ALIGN_TOP_LEFT);
                render_timer(gCurrentHud->unk2EC, gCurrentHud->unk2F0, gCurrentHud->unk2FA, gCurrentHud->unk2FB, gCurrentHud->unk2FC, 1);
            } else {
                draw_text(&gHUDCurrDisplayList, gCurrentHud->unk16C - 35.0f, gCurrentHud->unk170, "DID NOT FINISH", ALIGN_TOP_LEFT);
            }
        }
    }
}

#ifdef NON_EQUIVALENT
void func_800A6254(Object_Racer *racer, s32 updateRate) {
    s32 *var_a0;
    s32 var_t0;
    s32 var_a2;
    s32 var_v1;
    s32 raceType;
    f32 var_f0;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    s32 totalRaceTime;
    s32 fastestLapTime;
    s32 minutes;
    s32 seconds;
    s32 hundredths;
    LevelHeader *curLevelHeader;
    s32 temp_v0_4;
    
    raceType = get_current_level_race_type();
    if (is_in_two_player_adventure() && is_postrace_viewport_active() && D_80127189 == 0) {
        if (func_8000E184()) {
            gCurrentHud->unk5F0 -= 108.0f;
            gCurrentHud->unk610 -= 108.0f;
            gCurrentHud->unk170 -= 108.0f;
            gCurrentHud->unk2F0 -= 108.0f;
        }
        gCurrentHud->unk5F0 += 35.0f;
        gCurrentHud->unk610 += 35.0f;
        gCurrentHud->unk170 += 35.0f;
        gCurrentHud->unk2F0 += 35.0f;
        D_800E2770[0].playerIndex = racer->playerIndex;
        D_80127189 = 1;
    }
    
    switch (gCurrentHud->unk5FA) {
        case 0:
            if (!(raceType & RACETYPE_CHALLENGE_BATTLE)) {
                D_800E2770[0].volume = 127;
                D_800E2770[0].unk3 = 0;
                D_800E2770[0].playerIndex = racer->playerIndex;
                sound_play(SOUND_WHOOSH1, NULL);
            }
            switch (gHUDNumPlayers) {
                case 0:
                case 1:
                    gCurrentHud->unk5FD = -20;
                    gCurrentHud->unk17D = -15;
                    gCurrentHud->unk2FD = -15;
                    break;
                default:
                    if (racer->playerIndex == PLAYER_ONE || racer->playerIndex == PLAYER_THREE) {
                        gCurrentHud->unk5FD = -90;
                        gCurrentHud->unk17D = -85;
                        gCurrentHud->unk2FD = -85;
                    } else {
                        gCurrentHud->unk5FD = 55;
                        gCurrentHud->unk17D = 60;
                        gCurrentHud->unk2FD = 60;
                    }
                    break;
            }
            if (osTvType == TV_TYPE_PAL) {
                gCurrentHud->unk5FD -= 4;
                gCurrentHud->unk17D -= 4;
                gCurrentHud->unk2FD -= 4;
            }
            if (racer->unk1AC < 4) {
                gCurrentHud->unk618 = racer->unk1AC - 1;
            } else {
                gCurrentHud->unk618 = 3;
            }
            gCurrentHud->unk5F8 = racer->unk1AC - 1;
            gCurrentHud->unk5FA = 1;
            switch (gNumActivePlayers) {
                case 2:
                    var_f12 = 360.0f;
                    var_f14 = -40.0f;
                    if (racer->playerIndex == PLAYER_ONE) {
                        var_f0 = 75.0f;
                        var_f2 = 90.0f;
                    } else {
                        var_f0 = 183.0f;
                        var_f2 = 198.0f;
                    }
                    if (osTvType == TV_TYPE_PAL) {
                        var_f0 *= 1.1;
                        var_f2 *= 1.1;
                        var_f12 -= 4.0f;
                        var_f14 -= 4.0f;
                        var_f0 = (s32) var_f0;
                        var_f2 = (s32) var_f2;
                        if (racer->playerIndex == 0) {
                            var_f0 -= 9.0f;
                            var_f2 -= 9.0f;
                        }
                    }
                    gCurrentHud->unk16C = var_f12;
                    gCurrentHud->unk170 = var_f0;
                    gCurrentHud->unk2EC = var_f14;
                    gCurrentHud->unk2F0 = var_f2;
                    break;
                case 3:
                case 4:
                    if (racer->playerIndex < 2) {
                        var_f0 = 75.0f;
                        var_f2 = 90.0f;
                    } else {
                        var_f0 = 183.0f;
                        var_f2 = 198.0f;
                    }
                    if (racer->playerIndex == PLAYER_ONE || racer->playerIndex == PLAYER_THREE) {
                        var_f12 = 70.0f;
                        var_f14 = -230.0f;
                    } else {
                        var_f12 = 230.0f;
                        var_f14 = -70.0f;
                    }
                    if (osTvType == TV_TYPE_PAL) {
                        var_f0 *= 1.1;
                        var_f2 *= 1.1;
                        var_f12 -= 4.0f;
                        var_f14 -= 4.0f;
                        var_f0 = (s32) var_f0;
                        var_f2 = (s32) var_f2;
                        if (racer->playerIndex < 2) {
                            var_f0 -= 9.0f;
                            var_f2 -= 9.0f;
                        }
                    }
                    gCurrentHud->unk16C = var_f12;
                    gCurrentHud->unk170 = var_f0;
                    gCurrentHud->unk2EC = var_f14;
                    gCurrentHud->unk2F0 = var_f2;
                    break;
            }
            if (gNumActivePlayers != 1) {
                curLevelHeader = get_current_level_header();
                totalRaceTime = 0;
                fastestLapTime = racer->lap_times[0];
                for (var_v1 = 0; var_v1 < (var_a2 = curLevelHeader->laps); var_v1++) {
                    totalRaceTime += racer->lap_times[var_v1];
                    if (racer->lap_times[var_v1] < fastestLapTime) {
                        fastestLapTime = racer->lap_times[var_v1];
                    }
                }
                get_timestamp_from_frames(fastestLapTime, &minutes, &seconds, &hundredths);
                gCurrentHud->unk2FA = minutes;
                gCurrentHud->unk2FB = seconds;
                gCurrentHud->unk2FC = hundredths;
                get_timestamp_from_frames(totalRaceTime, &minutes, &seconds, &hundredths);
                gCurrentHud->unk17A = minutes;
                gCurrentHud->unk17B = seconds;
                gCurrentHud->unk17C = hundredths;
            }
            break;
        case 1:
            var_a2 = TRUE;
            if (gCurrentHud->unk5EC < (gCurrentHud->unk5FD - (updateRate * 13)) + 160) {
                var_v1 = (updateRate * 13);
                var_a2 = FALSE;
            } else {
                var_v1 = (gCurrentHud->unk5FD + 160) - gCurrentHud->unk5EC;
            }
            gCurrentHud->unk5EC += var_v1;
            gCurrentHud->unk60C += var_v1;
            if (gNumActivePlayers != 1) {
                if ((gCurrentHud->unk17D + (updateRate * 13) + 160) < gCurrentHud->unk16C) {
                    var_a2 = FALSE;
                } else {
                    var_v1 = gCurrentHud->unk16C - (gCurrentHud->unk17D + 160);
                }
                gCurrentHud->unk16C -= var_v1;
                if (gCurrentHud->unk2EC < (gCurrentHud->unk2FD - var_v1) + 160) {
                    var_a2 = FALSE;
                } else { 
                    var_v1 = (gCurrentHud->unk2FD + 160) - gCurrentHud->unk2EC;
                }
                gCurrentHud->unk2EC += var_v1;
            }
            temp_v0_4 = 2; //fakematch?
            if (var_a2) {
                gCurrentHud->unk5FA = temp_v0_4; //fakematch? Why not just set directly to 2?
                gCurrentHud->unk5FB = -120;
                gCurrentHud->unk5FC = 0;
                if (gHUDVoiceSoundMask == NULL) {
                    if (raceType == RACETYPE_CHALLENGE_BATTLE) {
                        switch (racer->unk1AC) {
                            case 1:
                            case 2:
                                sound_play(SOUND_UNK_146, &gHUDVoiceSoundMask);
                                break;
                            case 3:
                                sound_play(SOUND_VOICE_TT_TOO_BAD, &gHUDVoiceSoundMask);
                                break;
                            default:
                                sound_play(SOUND_VOICE_TT_UNLUCKY, &gHUDVoiceSoundMask);
                                break;
                        }
                    } else if (get_time_trial_ghost() == NULL) {
                        play_time_trial_end_message(&racer->playerIndex);
                    }
                }
            }
            func_800A5F18(racer);
            break;
        case 2:
            gCurrentHud->unk5FB += updateRate;
            
            if (gCurrentHud->unk5FB >= 120) {
                gCurrentHud->unk5FB = -120;
                gCurrentHud->unk5FC++;
            }
            if (gCurrentHud->unk5FC == 2) {
                if (gNumActivePlayers == 1 || is_in_two_player_adventure()) {
                    gCurrentHud->unk5FA = 3;
                    sound_play(SOUND_WHOOSH1, NULL);
                } else {
                    gCurrentHud->unk5FA = 4;
                }
            }
            func_800A5F18(racer);
            break;
        case 3:
            if (raceType == RACETYPE_CHALLENGE_BATTLE) {
                gCurrentHud->unk5FA = 4;
            } else {
                gCurrentHud->unk5EC -= (updateRate * 13);
                gCurrentHud->unk60C -= (updateRate * 13);
                if (gCurrentHud->unk5EC < -200.0f) {
                    gCurrentHud->unk5FA = 4;
                }
                gCurrentHud->unk16C += (updateRate * 13);
                gCurrentHud->unk2EC += (updateRate * 13);
            }
            func_800A5F18(racer);
            break;
        case 4:
            if (racer->playerIndex == D_800E2770[0].playerIndex) {
                D_800E2770[0].unk3 = -1;
            }
            gCurrentHud->unk5FA = 5;
            gCurrentHud->unk5FB = 0;
            func_800A5F18(racer);
            break;
        default:
            func_800A5F18(racer);
            break;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/game_ui/func_800A6254.s")
#endif

/**
 * Play the normal race finish message, unless you beat your time record,
 * then T.T will say "Race Record" instead.
*/
void play_time_trial_end_message(s16 *playerID) {
    Settings *settings = get_settings();

    if (playerID != NULL) {
        if (settings->racers[*playerID].best_times & 0x80) {
            sound_play(SOUND_VOICE_TT_RACE_RECORD, &gHUDVoiceSoundMask);
        } else {
            sound_play(SOUND_VOICE_TT_FINISH, &gHUDVoiceSoundMask);
        }
    }
}

/**
 * Render the finishing overlay after a time trial.
*/
void render_time_trial_finish(Object_Racer *racer, s32 updateRate) {
    s32 temp;
    
    switch (gCurrentHud->unk1DA) {
    case 0:
        D_800E2770->volume = 127;
        D_800E2770->unk3 = 0;
        D_800E2770->playerIndex = (s8) racer->playerIndex;
        sound_play(SOUND_WHOOSH1, NULL);
        if (gHUDNumPlayers == 0 || gHUDNumPlayers == 1) {
            gCurrentHud->unk1CC = -200.0f;
            gCurrentHud->unk1DD = 0;
        } else {
            if ((racer->playerIndex == 0) || (racer->playerIndex == 2)) {
                gCurrentHud->unk1DD = -80;
                gCurrentHud->unk1CC = -200.0f;
            } else {
                gCurrentHud->unk1DD = 80;
                gCurrentHud->unk1CC = -40.0f;
            }
        }
        gCurrentHud->unk1DA = 1;
        return;
    case 1:
        temp = (updateRate * 13);
        if (gCurrentHud->unk1CC < gCurrentHud->unk1DD - temp) {
            gCurrentHud->unk1CC += temp;
        } else {
            gCurrentHud->unk1CC = gCurrentHud->unk1DD;
            gCurrentHud->unk1DA = 2;
            gCurrentHud->unk1DB = -120;
            if (gHUDVoiceSoundMask == NULL && D_80126D71 == 0) {
                play_time_trial_end_message(&racer->playerIndex);
            }
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk1C0);
        return;
    case 2:
        gCurrentHud->unk1DB += updateRate;
        if (gCurrentHud->unk1DB >= 120) {
            gCurrentHud->unk1DA = 3;
            if ((gHUDNumPlayers == 0) || (gHUDNumPlayers == 1)) {
                gCurrentHud->unk1DD = 56;
            } else {
                if ((racer->playerIndex == 0) || (racer->playerIndex == 2)) {
                    gCurrentHud->unk1DD = 56;
                } else {
                    gCurrentHud->unk1DD = -40;
                }
            }
            sound_play(SOUND_WHOOSH1, NULL);
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk1C0);
        return;
    case 3:
        gCurrentHud->unk1CC -= updateRate * 13;
        if (gCurrentHud->unk1CC < gCurrentHud->unk1DD) {
            gCurrentHud->unk1DA = 4;
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk1C0);
        return;
    case 4:
        D_800E2770->unk3 = -1;
        gCurrentHud->unk1DA = 5;
        gCurrentHud->unk1DB = 0;
        return;
    default:
        return;
    }
}

/**
 * Render the icon, and the number of collectable balloons onscreen.
*/
void render_balloon_count(UNUSED Object_Racer *racer) {
    s32 balloonCount;
    s32 div;
    UNUSED s32 pad;
    u32 balloonTickTimer;
    Settings *settings;

    settings = get_settings();
    if (osTvType == TV_TYPE_PAL) {
        balloonTickTimer = 646;
    } else {
        balloonTickTimer = 840;
    }
    if (settings->cutsceneFlags & CUTSCENE_ADVENTURE_TWO) {
        gCurrentHud->unk266 = 69; // Use the adventure two balloon sprite.
    }
    if (get_cutscene_id() == 10 && get_balloon_cutscene_timer() < balloonTickTimer) {
        balloonCount = *settings->balloonsPtr - 1;
    } else {
        balloonCount = *settings->balloonsPtr;
        if (get_cutscene_id() == 10) {
            if (get_balloon_cutscene_timer() < balloonTickTimer + 8 && D_80126D44 == 0) {
                sound_play(SOUND_HUD_LAP_TICK, &D_80126D44);
            }
        }
    }
    if (balloonCount < 0) {
        balloonCount = 0;
    }
    div = balloonCount / 10;
    if (div != 0) {
        gCurrentHud->unk2B8 = div;
        gCurrentHud->unk2D8 = balloonCount % 10;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk2C0);
    } else {
        gCurrentHud->unk2B8 = balloonCount % 10;
    }
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk2A0);
    set_viewport_tv_type(TV_TYPE_NTSC);
    if (osTvType == TV_TYPE_PAL) {
        sprite_opaque(TRUE);
    }
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk260);
    sprite_opaque(FALSE);
    set_viewport_tv_type(TV_TYPE_PAL);
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk280);
}


/**
 * Unused function that plays whichever T.T voice line is passed through.
 * Only if the game is currently running and no voice line is already playing.
*/
UNUSED void play_hud_voice_line(u16 soundId) {
    if (gHUDVoiceSoundMask == NULL && !(is_game_paused())) {
        sound_play(soundId, &gHUDVoiceSoundMask);
    }
}

/**
 * Set the sound ID and delay (in seconds) of the voice clip that will be played
 * after the time trial run starts.
*/
void set_time_trial_start_voice(u16 soundID, f32 delay, s32 arg2) {
    if (gTimeTrialVoiceDelay == 0) {
        gTimeTrialVoiceID = soundID;
        gTimeTrialVoiceDelay = delay * 60.0f;
        D_80126D78 = arg2;
    }
}

void func_800A74EC(u16 soundID, s32 arg1) {
    if (soundID == gTimeTrialVoiceID && D_80126D78 == arg1) {
        gTimeTrialVoiceDelay = 0;
    }
}

/**
 * Renders the icon in the bottom left of the current weapon.
 * The icon will spin and grow as it appears, then spins and shrinks as it disappears.
*/
void render_weapon_hud(Object *obj, s32 updateRate) {
    Object_Racer *racer;
    s32 temp_a0;

    racer = (Object_Racer *) obj->unk64;
    if (racer->raceFinished == FALSE) {
        set_viewport_tv_type(TV_TYPE_NTSC);
        temp_a0 = (racer->balloon_type * 3) + (racer->balloon_level);
        if (gCurrentHud->unk5D != racer->balloon_level) {
            if (racer->balloon_level == 0) {
                gCurrentHud->unk5C = 120;
            } else if (gNumActivePlayers == 1) {
                gCurrentHud->unk5C = 0;
            } else {
                gCurrentHud->unk5C = 120;
            }
            gCurrentHud->unk5D = racer->balloon_level;
        }
        if (racer->balloon_quantity > 0) {
            if (gCurrentHud->unk5B < 16 && racer->unk170 == 0) {
                gCurrentHud->unk44 = gCurrentHud->unk5B << 12;
                gCurrentHud->unk48 = (gCurrentHud->unk5B * 0.04687) + 0.25;
            } else {
                gCurrentHud->unk44 = 0;
                gCurrentHud->unk48 = 1.0f;
            }
            gCurrentHud->unk58 = temp_a0;
            gCurrentHud->unk5B += updateRate;
            if (gCurrentHud->unk5B > 16) {
                gCurrentHud->unk5B = 16;
                gCurrentHud->unk5C += updateRate;
                if (gCurrentHud->unk5C > 120) {
                    gCurrentHud->unk5C = 120;
                } else if (gHUDNumPlayers == ONE_PLAYER) {
                    gCurrentHud->unk48 += 0.18 * sins_f(((f32) gCurrentHud->unk5C * 682.6583 * 4.0));
                }
            }
            if (gHUDNumPlayers > ONE_PLAYER) {
                gCurrentHud->unk48 *= 0.75;
            }
            if (gCurrentHud->unk48 != 1.0) {
                sprite_opaque(TRUE);
            }
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk40);
            sprite_opaque(FALSE);
            if (racer->balloon_quantity > 3) {
                gCurrentHud->unk63A = -128;
            }
            if (racer->balloon_quantity < 3) {
                gCurrentHud->unk63A -= updateRate;
            }
            if (racer->balloon_quantity >= 3 || ((((gCurrentHud->unk63A + 128) % 32) < 20) && racer->balloon_quantity != 1)) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                gCurrentHud->unk638 = racer->balloon_quantity - 1;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk620);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        } else {
            if (gCurrentHud->unk5B > 0) {
                gCurrentHud->unk44 = gCurrentHud->unk5B << 12;
                gCurrentHud->unk48 = (gCurrentHud->unk5B * 0.04687) + 0.25;
                gCurrentHud->unk5B -= updateRate;
                gCurrentHud->unk58 = temp_a0;
                if (gCurrentHud->unk5B < 0) {
                    gCurrentHud->unk5B = 0;
                }
                if (gHUDNumPlayers != ONE_PLAYER) {
                    gCurrentHud->unk48 /= 2;
                }
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk40);
            }
        }
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        set_viewport_tv_type(TV_TYPE_PAL);
    }
}

/**
 * If currently using a magnet, render a reticle over the racer that's being targeted.
*/
void render_magnet_reticle(Object *racerObj) {
    unk80068514_arg4 *entry;
    unk80126CDC *hud;
    Object_Racer *racer;
    s32 hudElementIndex;

    if(entry){} // Fakematch
    racer = &racerObj->unk64->racer;
    if (racer->magnetTargetObj != NULL && get_current_viewport() == racer->playerIndex) {
        hud = gCurrentHud;
        hud->unk22C = racer->magnetTargetObj->segment.trans.x_position;
        hud->unk230 = racer->magnetTargetObj->segment.trans.y_position;
        hud->unk234 = racer->magnetTargetObj->segment.trans.z_position;
        hudElementIndex = hud->unk226;
        entry = gAssetHudElements->entry[hudElementIndex];
        if (entry == NULL) {
            return;
        }
        gAssetHudElementStaleCounter[hudElementIndex] = 0;
        hud = (unk80126CDC *) &hud->unk220;
        func_80066CDC(&gHUDCurrDisplayList, &gHUDCurrMatrix);
        matrix_world_origin(&gHUDCurrDisplayList, &gHUDCurrMatrix);
        render_sprite_billboard(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (Object *) hud, entry, RENDER_Z_UPDATE);
    }
}

/**
 * Render the lap time on the top right.
 * When the player begins a new lap, start flashing the previous lap time below instead.
*/
void render_race_time(Object_Racer *racer, s32 updateRate) {
    s32 i;
    s32 stopwatchTimer;
    s32 minutes;
    s32 seconds;
    s32 hundredths;
    s32 countingDown;
    s32 timerHideCounter;

    if (!(gHUDNumPlayers != ONE_PLAYER && D_800E2794[gHUDNumPlayers][racer->playerIndex] != 1) || (gHUDNumPlayers > ONE_PLAYER && racer->lap > 0 && racer->lap_times[racer->lap] < 180)) {
        if (racer->raceFinished == FALSE) {
            timerHideCounter = gCurrentHud->unk15A + 127;
            if (racer->lap > 0 && racer->lap_times[racer->lap] < 180 && racer->lap < gHudLevelHeader->laps) {
                stopwatchTimer = racer->lap_times[racer->lap - 1];
                countingDown = TRUE;
                if (timerHideCounter == 0) {
                    timerHideCounter = 180;
                }
            } else {
                stopwatchTimer = 0;
                for (i = 0; i <= racer->countLap && i < gHudLevelHeader->laps; i++) {
                    stopwatchTimer += racer->lap_times[i];
                }
                countingDown = stopwatchTimer == 0 || racer->raceFinished || is_game_paused();
                gCurrentHud->unk15A = -127;
                timerHideCounter = 0;
            }
            if (gHUDNumPlayers == ONE_PLAYER) {
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk140);
            }
            if (normalise_time(36000) < stopwatchTimer) {
                stopwatchTimer = normalise_time(36000);
            }
            get_timestamp_from_frames(stopwatchTimer, &minutes, &seconds, &hundredths);
            if (countingDown || (normalise_time(36000) == stopwatchTimer)) {
                if((timerHideCounter > updateRate)) {
                    timerHideCounter -= updateRate;
                } else {
                    timerHideCounter = 0;
                }
                gCurrentHud->unk15A = timerHideCounter - 127;
                if ((timerHideCounter % 30) > 20) {
                    gHideRaceTimer = TRUE;
                    return;
                } else {
                    if (gHideRaceTimer) {
                        if (gHUDNumPlayers == ONE_PLAYER) {
                            sound_play(SOUND_HUD_LAP_TICK, NULL);
                        }
                        gHideRaceTimer = FALSE;
                    }
                }
            } else {
                hundredths = gCurrentHud->unk15B + ((hundredths / 10) * 10);
                gCurrentHud->unk15B = gCurrentHud->unk15B + 1;
                if (gCurrentHud->unk15B >= 10) {
                    gCurrentHud->unk15B = 0;
                }
            }
            
            if (gNumActivePlayers == 1) {
                render_timer(gCurrentHud->unk16C, gCurrentHud->unk170, minutes, seconds, hundredths, 0);
            } else {
                render_timer(gCurrentHud->unk16C, gCurrentHud->unk170, minutes, seconds, hundredths, 1);
            }
            gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
    }
}

/**
 * Render a time in minutes, seconds and hundredths of a second.
*/
void render_timer(s32 arg0, s32 arg1, s32 minutes, s32 seconds, s32 hundredths, s32 someBool) {
    UNUSED s32 pad;
    unk80126CDC_entry entry2;
    s32 unk14;
    s32 unk10;
    s32 unkC;
    s32 unk8;
    s32 var_s4;
    s32 unk0;

    entry2.unkC = arg0;
    entry2.unk10 = arg1;
    entry2.unk4 = 0;
    entry2.unk2 = 0;
    entry2.unk0 = 0;
    entry2.unk8 = 1.0f;
    entry2.unk14 = 0.0f;
    if (!someBool) {
        unk14 = 11;
        unk10 = 10;
        unkC = 10;
        unk8 = 2;
        var_s4 = 9;
        unk0 = 11;
    } else {
        unk14 = 10;
        unk10 = 8;
        unkC = 7;
        unk8 = 0;
        var_s4 = 10;
        unk0 = 12;
    }
    entry2.unk6 = var_s4;
    entry2.unk18 = minutes / 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC** ) &entry2);
    entry2.unkC += unk14;
    entry2.unk18 = minutes % 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC** ) &entry2);
    entry2.unk18 = 0;
    entry2.unkC += unk10;
    entry2.unk10 += unk8;
    entry2.unk6 = unk0;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC** ) &entry2);
    entry2.unk6 = var_s4;
    entry2.unkC += unkC;
    entry2.unk10 -= unk8;
    entry2.unk18 = seconds / 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC** ) &entry2);
    entry2.unkC += unk14;
    entry2.unk18 = seconds % 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC** ) &entry2);
    entry2.unk18 = 0;
    entry2.unkC += unk10;
    entry2.unk10 += unk8;
    entry2.unk6 = (s16) unk0;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC** ) &entry2);
    entry2.unk6 = var_s4;
    entry2.unkC += unkC;
    entry2.unk10 -= unk8;
    entry2.unk18 = hundredths / 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC** ) &entry2);
    entry2.unkC += unk14;
    entry2.unk18 = hundredths % 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (unk80126CDC** ) &entry2);
}


/**
 * Loads the minimap sprite from the level data, then sets the global colours for the minimap.
*/
void minimap_init(LevelModel *model) {
    s32 sp2C;
    gMinimapRed = (model->minimapColor >> 16) & 0xFF;
    gMinimapGreen = (model->minimapColor >> 8) & 0xFF;
    gMinimapBlue = model->minimapColor & 0xFF;
    load_sprite_info(model->minimapSpriteIndex, &gMinimapDotOffsetX, &gMinimapDotOffsetY, &sp2C, &sp2C, &sp2C);
    func_8007CA68(model->minimapSpriteIndex, 0, &D_80126D14, &D_80126D18, &sp2C);
    model->minimapSpriteIndex = (s32) func_8007C12C(model->minimapSpriteIndex, 1);
}

/**
 * Returns the hud settings value for the mumber of active players.
 * For player 1, it's switching between the minimap and speedometre.
 * For 2 players, it's for toggling the minimap
 * For 3 players, it's for toggling between the minimap and a spectator cam in viewport 4.
 * For 4 players, it's for toggling the minimap.
*/
s8 get_hud_setting(void) {
    return gHudToggleSettings[gHUDNumPlayers];
}

/**
 * Renders the minimap in all modes as well as a few other random pieces of HUD.
 * This function also handles the HUD in 3 or 4 player, instead of the normal dedicated functions it has.
*/
void render_minimap_and_misc_hud(Gfx **dList, MatrixS **mtx, Vertex **vtx, s32 updateRate) {
    Object_Racer *curRacerObj;
    LevelModel *lvlMdl;
    Sprite *minimap;
    Object **objectGroup;
    Object_Racer *tempVar4;
    Object_Racer *someRacer;
    s32 i;
    s32 objectCount;
    UNUSED s32 tempVar3;
    ObjectTransform_800A8474 objTrans;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    u8 sp113;
    s32 mapOpacity;
    s32 opacity;
    UNUSED s32 pad[2];
    s32 temp_s1_2;
    s32 var_a0_5;
    s32 spF4;
    s32 spF0;
    s32 tempVar1;
    s32 temp_s1_3;
    s32 spE4;
    s32 spE0;
    UNUSED s32 pad9;
    Object *temp_v0_8;
    s32 tempVar2;
    s32 sp144;
    s32 racerCount;
    UNUSED s32 pad2;
    ObjectSegment *someObjSeg;
    Object **racerGroup;
    s32 spBC;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s1;
    s32 temp_s0;
    s32 temp_f16;
    s32 temp_f6;
    s32 temp_s3;
    s32 temp;
    UNUSED s32 pad3[4];
    
    func_800A0BD4(updateRate);
    
    gAssetHudElementStaleCounter[HUD_ELEMENT_UNK_01] = 0;
    gAssetHudElementStaleCounter[HUD_ELEMENT_UNK_17] = 0;
    gAssetHudElementStaleCounter[HUD_ELEMENT_UNK_08] = 0;
    gAssetHudElementStaleCounter[HUD_ELEMENT_UNK_11] = 0;
    D_80127180 = 0;
    
    if (D_80126CD3 & 2) {
        mapOpacity = 255.0f - ((D_80126CD0 * 255.0f) / D_8012718B);
    } else {
        mapOpacity = 255;
    }
    
    for (i = 0; i < gAssetHudElementIdsCount; i++) {
        if (gAssetHudElements->entry[i] && i != 40) {
            if (++gAssetHudElementStaleCounter[i] > 60) {
                if ((gAssetHudElementIds[i] & (0x4000 | 0x8000)) == (0x4000 | 0x8000)) {
                    free_texture((TextureHeader *) gAssetHudElements->entry[i]);
                } else if (gAssetHudElementIds[i] & 0x8000) {
                    free_sprite((Sprite *) gAssetHudElements->entry[i]);
                } else if (gAssetHudElementIds[i] & 0x4000) {
                    free_object((Object *) gAssetHudElements->entry[i]);
                } else {
                    free_3d_model((ObjectModel **) gAssetHudElements->entry[i]);
                }
                gAssetHudElements->entry[i] = 0;
            }
        }
    }
    
    gHudLevelHeader = get_current_level_header();
    objectGroup = get_racer_objects_by_port(&objectCount);
    gHUDCurrDisplayList = *dList;
    gHUDCurrMatrix = *mtx;
    gHUDCurrVertex = *vtx;
    if (gHudLevelHeader->race_type == RACETYPE_CHALLENGE_EGGS) {
        if (gNumActivePlayers == 2 && gHudToggleSettings[gHUDNumPlayers] == 0) {
            func_800A14F0(NULL, updateRate);
            reset_render_settings(&gHUDCurrDisplayList);
        } else {
            if (gNumActivePlayers == 3) {
                tempVar4 = NULL;
                for(tempVar2 = 0; tempVar2 < objectCount; tempVar2++) {
                    if (objectGroup[tempVar2]->unk64->racer.playerIndex == PLAYER_COMPUTER) {
                        tempVar4 = &objectGroup[tempVar2]->unk64->racer;
                    }
                }
                if (tempVar4 != NULL) {
                    temp_s0 = gCurrentHud->unk64C;
                    temp_s1 = gCurrentHud->unk650;
                    spF4 = gCurrentHud->unk66C;
                    spF0 = gCurrentHud->unk670;
                    gCurrentHud->unk64C = 225.0f;
                    gCurrentHud->unk66C = 221.0f;
                    gCurrentHud->unk670 = 197.0f;
                    gCurrentHud->unk650 = 165.0f;
                    if (osTvType == TV_TYPE_PAL) {
                        gCurrentHud->unk64C -= 4.0f;
                        gCurrentHud->unk66C -= 4.0f;
                        gCurrentHud->unk650 *= 1.1;
                        gCurrentHud->unk670 *= 1.1;
                    }
                    func_800A19A4(tempVar4, updateRate);
                    gHudColour = COLOUR_RGBA32(255, 255, 255, 254);
                    gCurrentHud->unk64C = temp_s0;
                    gCurrentHud->unk650 = temp_s1;
                    gCurrentHud->unk66C = spF4;
                    gCurrentHud->unk670 = spF0;
                }
            }
        }
    } else if (gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BATTLE) {
        // Show life counter and icons in 2 player.
        if (gNumActivePlayers == 2 && gHudToggleSettings[gHUDNumPlayers] == 0) {
            func_80068508(TRUE);
            sprite_opaque(FALSE);
            set_ortho_matrix_view(&gHUDCurrDisplayList, &gHUDCurrMatrix);
            func_800A1E48(0, updateRate);
            func_80068508(FALSE);
            reset_render_settings(&gHUDCurrDisplayList);
            sprite_opaque(TRUE);
        } else {
            // In 3/4 player, just show the life counter.
            if (gNumActivePlayers == 3) {
                curRacerObj = NULL;
                for(tempVar2 = 0; tempVar2 < objectCount; tempVar2++) {
                    if (objectGroup[tempVar2]->unk64->racer.playerIndex == PLAYER_COMPUTER) { 
                        curRacerObj = &objectGroup[tempVar2]->unk64->racer;
                    }
                }
                if (curRacerObj != NULL) {
                    gCurrentHud = gPlayerHud[PLAYER_FOUR];
                    spE4 = gCurrentHud->unk64C;
                    spE0 = gCurrentHud->unk650;
                    sprite_opaque(FALSE);
                    set_ortho_matrix_view(&gHUDCurrDisplayList, &gHUDCurrMatrix);
                    func_80068508(TRUE);
                    gCurrentHud->unk64C = 225.0f;
                    if (osTvType == TV_TYPE_PAL) {
                        gCurrentHud->unk650 = 181.5f;
                    } else {
                        gCurrentHud->unk650 = 165.0f;
                    }
                    if (osTvType == TV_TYPE_PAL) {
                        var_a0_5 = (66.0f - gCurrentHud->unk36C) - 4.0f;
                        temp = -114.0f - gCurrentHud->unk370;
                    } else {
                        var_a0_5 = 66.0f - gCurrentHud->unk36C;
                        temp = -100.0f - gCurrentHud->unk370;
                    }
                    gCurrentHud->unk36C += var_a0_5;
                    gCurrentHud->unk370 += temp; 
                    gCurrentHud->unkEC += var_a0_5;
                    gCurrentHud->unkF0 += temp;
                    gCurrentHud->unk38C += var_a0_5;
                    gCurrentHud->unk390 += temp;
                    gCurrentHud->unk10C += var_a0_5;
                    gCurrentHud->unk110 -= temp + 1;
                    gCurrentHud->unk12C += var_a0_5;
                    gCurrentHud->unk130 -= temp + 1;
                    gCurrentHud->unk24C += var_a0_5;
                    gCurrentHud->unk250 -= temp;
                    gCurrentHud->unk646 = curRacerObj->characterId + 56;
                    if (osTvType == TV_TYPE_PAL) {
                        gCurrentHud->unk64C -= 4.0f;
                        gCurrentHud->unk66C -= 4.0f;
                    }
                    D_80126CD5 = TRUE;
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk640);
                    D_80126CD5 = FALSE;
                    if (gCurrentHud->unkFB == 0 && curRacerObj->bananas == 10) {
                        gCurrentHud->unkFB = curRacerObj->bananas;
                    }
                    render_racer_bananas(curRacerObj, updateRate);
                    gCurrentHud->unk36C -= var_a0_5;
                    gCurrentHud->unk370 -= temp;
                    gCurrentHud->unkEC -= var_a0_5;
                    gCurrentHud->unkF0 -= temp;
                    gCurrentHud->unk38C -= var_a0_5;
                    gCurrentHud->unk390 -= temp;
                    gCurrentHud->unk10C -= var_a0_5;
                    gCurrentHud->unk110 += temp + 1;
                    gCurrentHud->unk12C -= var_a0_5;
                    gCurrentHud->unk130 += temp + 1;
                    gCurrentHud->unk24C -= var_a0_5;
                    gCurrentHud->unk250 += temp;
                    gCurrentHud->unk64C = spE4;
                    gCurrentHud->unk650 = spE0;
                    sprite_opaque(TRUE);
                    reset_render_settings(&gHUDCurrDisplayList);
                    func_80068508(FALSE);
                }
            }
        }
    } else if (gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BANANAS) {
        if (gNumActivePlayers == 2 && gHudToggleSettings[gHUDNumPlayers] == 0) {
            temp_s0_2 = gCurrentHud->unk64C;
            temp_s1_2 = gCurrentHud->unk650;
            temp_s3 = gCurrentHud->unk40C;
            spBC = gCurrentHud->unk410;
            racerGroup = get_racer_objects(&racerCount);
            for (sp144 = 0; sp144 < racerCount; sp144++) {
                someRacer = (Object_Racer *) racerGroup[sp144]->unk64;
                render_treasure_hud(someRacer);
                if (osTvType == TV_TYPE_PAL) {
                    gCurrentHud->unk650 += 66.0;
                    gCurrentHud->unk410 += 66.0;
                } else {
                    gCurrentHud->unk650 += 55.0f;
                    gCurrentHud->unk410 += 55.0f;
                }
            }
            gCurrentHud->unk64C = temp_s0_2;
            gCurrentHud->unk650 = temp_s1_2;
            gCurrentHud->unk40C = temp_s3;
            gCurrentHud->unk410 = spBC;
        } else if (gNumActivePlayers == 3) {
            tempVar4 = NULL;
            for(tempVar2 = 0; tempVar2 < objectCount; tempVar2++) {
                if (objectGroup[tempVar2]->unk64->racer.playerIndex == PLAYER_COMPUTER) {
                    tempVar4 = &objectGroup[tempVar2]->unk64->racer;
                }
            }
            if (tempVar4 != NULL) {
                temp_s0_3 = gCurrentHud->unk64C;
                temp_s1_3 = gCurrentHud->unk650;
                temp_f16 = gCurrentHud->unk40C;
                temp_f6 = gCurrentHud->unk410;
                gCurrentHud->unk64C = 225.0f;
                gCurrentHud->unk650 = 165.0f;
                gCurrentHud->unk40C = 209.0f;
                gCurrentHud->unk410 = 193.0f;
                if (osTvType == TV_TYPE_PAL) {
                    gCurrentHud->unk64C -= 4.0f;
                    gCurrentHud->unk40C -= 4.0f;
                    gCurrentHud->unk650 *= 1.1;
                    gCurrentHud->unk410 *= 1.1;
                    gCurrentHud->unk650 = (s32) gCurrentHud->unk650;
                    gCurrentHud->unk410 = (s32) gCurrentHud->unk410;
                }
                render_treasure_hud(tempVar4);
                gCurrentHud->unk64C = temp_s0_3;
                gCurrentHud->unk650 = temp_s1_3;
                gCurrentHud->unk40C = temp_f16;
                gCurrentHud->unk410 = temp_f6;
            }
        }
    }
    if (D_80127180 != 0) {
        gHudSprites[D_80127180].texture = NULL;
        render_textured_rectangle(&gHUDCurrDisplayList, gHudSprites, 0, 0, 255, 255, 255, 255);
    }
    *dList = gHUDCurrDisplayList;
    *mtx = gHUDCurrMatrix;
    *vtx = gHUDCurrVertex;
    if (!(gHudLevelHeader->unkBC & 1)) {
        sp113 = TRUE;
        for(i = 0; i < objectCount; i++) {
            someRacer = (Object_Racer *) objectGroup[i]->unk64;
            if (someRacer != NULL && 
                someRacer->playerIndex != PLAYER_COMPUTER && 
                someRacer->raceFinished == FALSE) {
                sp113 = FALSE;
            }
        }
        if ((gHUDNumPlayers == THREE_PLAYERS && is_postrace_viewport_active()) || check_if_showing_cutscene_camera() || sp113) {
            goto test;
        } else if (gHudToggleSettings[gHUDNumPlayers] != 1) {
        test:
            return;
        } else {
            reset_render_settings(&gHUDCurrDisplayList);
            set_ortho_matrix_view(&gHUDCurrDisplayList, &gHUDCurrMatrix);
            lvlMdl = get_current_level_model();
            if (lvlMdl == NULL) {
                return;
            }
            someObjSeg = get_active_camera_segment();
            func_80068508(TRUE);
            minimap = (Sprite *) lvlMdl->minimapSpriteIndex;
            switch (gHUDNumPlayers) {
                case TWO_PLAYERS:
                    gMinimapScreenX = 135;
                    gMinimapScreenY = -gMinimapDotOffsetY / 2;
                    break;
                case THREE_PLAYERS:
                    if (get_current_level_race_type() == RACETYPE_CHALLENGE_EGGS || 
                        get_current_level_race_type() == RACETYPE_CHALLENGE_BATTLE || 
                        get_current_level_race_type() == RACETYPE_CHALLENGE_BANANAS) {
                        gMinimapScreenX = (gMinimapDotOffsetX / 2) - 8;
                        gMinimapScreenY =  -gMinimapDotOffsetY / 2;
                    } else {
                        gMinimapScreenX = ( gMinimapDotOffsetX / 2) + 72;
                        gMinimapScreenY = -60 - (gMinimapDotOffsetY / 2);
                    }
                    break;
                case FOUR_PLAYERS:
                    gMinimapScreenX = (gMinimapDotOffsetX / 2) - 8;
                    gMinimapScreenY = -gMinimapDotOffsetY / 2;
                    break;
                default:
                    gMinimapScreenX = 135;
                    gMinimapScreenY = -98;
                    break;
            }
            if (osTvType == TV_TYPE_PAL) {
                gMinimapScreenY *= 1.2;
            }
            sprite_opaque(FALSE);
            objTrans.trans.x_position = gMinimapScreenX + D_80126D24 + D_80126D28;
            objTrans.trans.y_position = gMinimapScreenY;
            if (osTvType == TV_TYPE_PAL) {
                objTrans.trans.x_position -= 4.0f;
            }
            objTrans.trans.z_rotation = -someObjSeg->trans.z_rotation;
            objTrans.trans.x_rotation = 0;
            if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                objTrans.trans.y_rotation = -0x8000;
                objTrans.trans.x_position -= gMinimapDotOffsetX;
            } else {
                objTrans.trans.y_rotation = 0;
            }
            objTrans.unk18 = 0;
            objTrans.trans.z_position = 0.0f;
            objTrans.trans.scale = 1.0f;
            opacity = mapOpacity;
            if (mapOpacity > 160) {
                mapOpacity = 160;
            }
            if (gNumActivePlayers == 3) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, mapOpacity);
            } else {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, gMinimapRed, gMinimapGreen, gMinimapBlue, mapOpacity);
            }
            render_ortho_triangle_image(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (ObjectSegment* ) &objTrans.trans, minimap, 0);
            sp11C = (lvlMdl->upperXBounds - lvlMdl->lowerXBounds) / (f32) (lvlMdl->upperZBounds - lvlMdl->lowerZBounds);
            sp118 = coss_f((lvlMdl->minimapRotation * 0xFFFF) / 360);
            sp114 = sins_f((lvlMdl->minimapRotation * 0xFFFF) / 360);
            if (is_in_time_trial() && func_8001B288()) {
                temp_v0_8 = func_8001B2E0();
                if (temp_v0_8 != NULL) {
                    minimap_marker_pos(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114, sp118, sp11C);
                    gCurrentHud->unk1E6 = 14;
                    gCurrentHud->unk1E4 = 0;
                    gCurrentHud->unk1E8 = 1.0f;
                    tempVar1 = (opacity * (f32) temp_v0_8->segment.object.opacity) * 0.0078125;
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 60, 60, 60, tempVar1);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk1E0);
                }
            }
            temp_v0_8 = get_time_trial_ghost();
            if (temp_v0_8 != NULL) {
                minimap_marker_pos(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114, sp118, sp11C);
                gCurrentHud->unk1E4 = 0;
                tempVar1 = (opacity * (f32) temp_v0_8->segment.object.opacity) * 0.0078125;
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, gHudMinimapColours[8].red, gHudMinimapColours[8].green, gHudMinimapColours[8].blue, tempVar1);
                gCurrentHud->unk1E8 = 1.0f;
                gCurrentHud->unk1E6 = 14;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk1E0);
            }
            // Draw Taj's minimap icon.
            if (gHudLevelHeader->race_type == RACETYPE_HUBWORLD) {
                temp_v0_8 = find_taj_object();
                if (temp_v0_8 != NULL) {
                    gCurrentHud->unk1E6 = 14;
                    minimap_marker_pos(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114, sp118, sp11C);
                    gCurrentHud->unk1E4 = 0;
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 0, 255, opacity);
                    gCurrentHud->unk1E8 = 1.0f;
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk1E0);
                }
            }
            // Draw racer minimap icons.
            // Non AI players get an arrow instead of a blob that rotates.
            for (i = objectCount - 1; i >= 0; i--) {
                temp_v0_8 = objectGroup[i];
                someRacer = (Object_Racer *) objectGroup[i]->unk64;
                if (someRacer != NULL) {
                    minimap_marker_pos(objectGroup[i]->segment.trans.x_position, objectGroup[i]->segment.trans.z_position, sp114, sp118, sp11C);
                    if (someRacer->playerIndex != PLAYER_COMPUTER) {
                        gCurrentHud->unk1F0 -= 1.0f;
                        gCurrentHud->unk1E6 = 27;
                        gCurrentHud->unk1E4 = (objectGroup[i]->segment.trans.y_rotation - ((lvlMdl->minimapRotation * 0xFFFF) / 360)) & 0xFFFF;
                        
                        if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                            gCurrentHud->unk1E4 = 0xFFFF - gCurrentHud->unk1E4;
                        }
                        sprite_opaque(TRUE);
                    } else {
                        gCurrentHud->unk1E4 = 0;
                        gCurrentHud->unk1E6 = 14;
                    }
                    if (is_taj_challenge() && someRacer->vehicleID == VEHICLE_CARPET) {
                        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 0, 255, opacity);
                    } else {
                        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, gHudMinimapColours[someRacer->characterId].red, gHudMinimapColours[someRacer->characterId].green, gHudMinimapColours[someRacer->characterId].blue, opacity);
                    }
                    if (!(get_current_level_race_type() & RACETYPE_CHALLENGE) || (!someRacer->raceFinished)) {
                        if (osTvType == TV_TYPE_PAL) {
                            gCurrentHud->unk1EC -= 4.0f;
                        }
                        if (get_current_level_race_type() == RACETYPE_CHALLENGE_BATTLE) {
                            switch (someRacer->unk212) {
                                case 0:
                                    gCurrentHud->unk1E8 = 0.8f;
                                    break;
                                case 1:
                                    gCurrentHud->unk1E8 = 1.0f;
                                    break;
                                case 2:
                                case 3:
                                    gCurrentHud->unk1E8 = 1.2f;
                                    break;
                            }
                        } else {
                            gCurrentHud->unk1E8 = 1.0f;
                        }
                        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->unk1E0);
                    }
                    sprite_opaque(FALSE);
                }
            }
            gDPPipeSync(gHUDCurrDisplayList++);
            func_80068508(FALSE);
            sprite_opaque(TRUE);
            *dList = gHUDCurrDisplayList;
            *mtx = gHUDCurrMatrix;
            *vtx = gHUDCurrVertex;
        }
    }
}

/**
 * Set the position of the minimap marker based on object position.
 * Some markers can rotate, so account for that, too.
*/
void minimap_marker_pos(f32 x, f32 z, f32 angleSin, f32 angleCos, f32 modelAspectRatio) {
    LevelModel* lvlMdl;
    UNUSED s32 pad24[2];
    f32 scaledX;
    f32 scaledY;
    s32 a;
    s32 b;
    
    lvlMdl = get_current_level_model();
    
    a = lvlMdl->upperXBounds - lvlMdl->lowerXBounds;
    b = lvlMdl->upperZBounds - lvlMdl->lowerZBounds;
    scaledX = (60.0f * modelAspectRatio * lvlMdl->minimapXScale * (x - lvlMdl->lowerXBounds)) / a;
    scaledY = (lvlMdl->minimapYScale * -60.0f * (z - lvlMdl->lowerZBounds)) / b;

    if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) { // Is adventure 2?
        gCurrentHud->unk1EC = (((f32) gMinimapScreenX - ((scaledX * angleCos) + (scaledY * angleSin))) + (f32) lvlMdl->minimapOffsetXAdv2) - (f32) gMinimapDotOffsetX;
        gCurrentHud->unk1F0 = ((f32) (lvlMdl->minimapOffsetYAdv2 + gMinimapScreenY) - ((scaledX * angleSin) - (scaledY * angleCos))) + (f32) gMinimapDotOffsetY;
        return;
    }
    // Final x position on minimap
    gCurrentHud->unk1EC = ((f32) gMinimapScreenX + ((scaledX * angleCos) + (scaledY * angleSin)) + (f32) lvlMdl->minimapOffsetXAdv1) - (f32) gMinimapDotOffsetX;
    // Final y position on minimap
    gCurrentHud->unk1F0 = ((f32) (lvlMdl->minimapOffsetYAdv1 + gMinimapScreenY) - ((scaledX * angleSin) - (scaledY * angleCos))) + (f32) gMinimapDotOffsetY;
}

GLOBAL_ASM("asm/non_matchings/game_ui/func_800AA600.s")

void func_800AAFD0(ObjectModel *objModel) {
    UNUSED s32 pad;
    TextureHeader *texPtr;
    s32 triOffset;
    s32 vertOffset;
    s32 numBatches;
    s32 numVerts;
    s32 numTris;
    Vertex *verts;
    Triangle *tris;
    s32 textureEnabled;
    s32 i;
    s32 texIndex;
    s32 flags;

    numBatches = objModel->numberOfBatches;
    
    for (i = 0; i < numBatches; i++) {
        flags = objModel->batches[i].flags;
        if (!(flags & RENDER_Z_UPDATE)) {
            vertOffset = objModel->batches[i].verticesOffset;
            triOffset = objModel->batches[i].facesOffset;
            numVerts = objModel->batches[i + 1].verticesOffset - vertOffset;
            numTris = objModel->batches[i + 1].facesOffset - triOffset;
            verts = &objModel->vertices[vertOffset];
            tris = &objModel->triangles[triOffset];
            texIndex = objModel->batches[i].textureIndex; // 0xFF = No Texture 
            textureEnabled = TRIN_ENABLE_TEXTURE;
            if (texIndex == 0xFF) {
                texPtr = NULL;
            } else {
                texPtr = objModel->textures[texIndex].texture;
            }
            load_and_set_texture_no_offset(&gHUDCurrDisplayList, texPtr, flags & ~RENDER_Z_COMPARE);
            gSPVertexDKR(gHUDCurrDisplayList++, OS_PHYSICAL_TO_K0(verts), numVerts, 0);
            if (texPtr == NULL) {
                textureEnabled = TRIN_DISABLE_TEXTURE;
            }
            gSPPolygon(gHUDCurrDisplayList++, OS_PHYSICAL_TO_K0(tris), numTris, textureEnabled);
            numBatches = objModel->numberOfBatches;
        }
    } 
}

void func_800AB194(s32 arg0) {
    D_80126CD1 = 1;
    D_80126CD3 = arg0;
}

void func_800AB1AC(s32 arg0) {
    D_80126CD0 = D_8012718B;
    D_80126CD3 = arg0;
}

/**
 * Sets the race start HUD procedure to the first step.
*/
UNUSED void reset_race_start_hud(void) {
    gRaceStartShowHudStep = 0;
}

/**
 * Sets the visibility of the hud, hiding almost everything, leaving only the minimap.
*/
void set_hud_visibility(u8 setting) {
    gShowHUD = 1 - setting;
}
