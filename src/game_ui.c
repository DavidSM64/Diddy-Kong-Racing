#include "game_ui.h"
#include "common.h"
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
#include "rcp_dkr.h"
#include "audiosfx.h"
#include "printf.h"
#include "audio_spatial.h"
#include "joypad.h"
#include "PRinternal/viint.h"

/************ .data ************/

// Unused?
UNUSED s32 D_800E1E60 = 0;

// Base positions of all onscreen hud elements
HudElement gHudElementBase[HUD_ELEMENT_COUNT] = {
    { 0, 0, 0, HUD_ASSET_0, 1.0f, 53.0f, 16.0f, 0.0f, 0, 0, 127, 0, 0},
    { 0, 0, 0, HUD_ASSET_3, 1.0f, 54.0f, 18.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_WEAPONS, 0.4f, -120.0f, -68.0f, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_6, 1.0f, 104.0f, 16.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_9, 1.0f, 93.0f, 31.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_4, 1.0f, 104.0f, 32.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_9, 1.0f, 114.0f, 31.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_BANANA_ANIM, 0.5f, -3.0f, 73.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_9, 1.0f, 182.0f, 22.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_9, 1.0f, 192.0f, 22.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_13, 1.0f, 239.0f, 16.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_9, 1.0f, 206.0f, 31.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_GO_BIG, 1.0f, 0.0f, 30.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_GET_READY, 1.0f, 0.0f, 30.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_FINISH, 1.0f, -200.0f, 30.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_MAP_DOT, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_CHEQUER_FLAG, 1.0f, -50.0f, 87.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_RETICLE, 2.0f, -50.0f, 87.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_18, 1.0f, 167.0f, 22.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_GOLD_BALLOON, 1.0f, -127.0f, 88.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_18, 1.0f, 52.0f, 27.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_9, 1.0f, 67.0f, 27.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_9, 1.0f, 77.0f, 27.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_9, 1.0f, 221.0f, 48.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_6, 1.0f, 188.0f, 48.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_10, 1.0f, 206.0f, 48.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_20, 0.4f, -105.0f, -98.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_BANANA_STATIC, 0.5f, -3.0f, 73.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_23, 1.0f, -8.0f, 97.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_LAP_FINAL, 1.0f, 0.0f, 30.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_LAP_LAP, 1.0f, 0.0f, 30.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_LAP_2, 1.0f, 0.0f, 30.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_2, 1.0f, 25.0f, 48.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_INDICATOR_TURN_90, 1.0f, -120.0f, 30.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_34, 0.4f, -105.0f, -98.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_WRONG, 1.0f, 0.0f, 30.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_WAY, 1.0f, 0.0f, 30.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_PRO_AM, 1.0f, 80.0f, -60.0f, 0.0f, 0, 0, 0, 0, 0}, // Unused
    { 0, 0, 0x6490, HUD_SPRITE_SPEEDOMETRE_ARROW, 0.5f, 122.0f, -71.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_47, 0.75f, 247.0f, 212.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_48, 1.0f, 234.0f, 196.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_49, 1.0f, 232.0f, 177.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_50, 1.0f, 240.0f, 159.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_51, 1.0f, 256.0f, 146.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_52, 1.0f, 275.0f, 143.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_53, 1.0f, 246.0f, 156.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_54, 0.7272f, 27.0f, 142.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_0, 1.0f, -200.0f, 70.0f, 0.0f, 0, 0, 129, 0, 0},
    { 0, 0, 0, HUD_ASSET_3, 1.0f, -175.0f, 72.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_WEAPON_NUMBER, 1.0f, -99.0f, -89.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_PORTRAIT, 0.76f, 43.0f, 20.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_66, 1.0f, 40.0f, 54.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_BANANA_ANIM, 0.375f, -117.0f, 46.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_28, 1.0f, 51.0f, 56.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_10, 1.0f, 60.0f, 57.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_ASSET_10, 1.0f, 69.0f, 57.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_PLACE_1, 1.0f, -160.0f, 5.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_PORTRAIT, 1.0f, 260.0f, 16.0f, 0.0f, 0, 0, 0, 0, 0},
    { 0, 0, 0, HUD_SPRITE_PLACE_ST, 1.0f, 160.0f, 5.0f, 0.0f, 0, 0, 0, 0, 0},
};

u16 D_800E25C4[96] = {
    0x0000, 0x0035, 0x0010, 0x0001, 0x0036, 0x0012, 0x0004, 0x00CB, 0x0013, 0x0005, 0x00D3, 0x0013, 0x0006, 0x00DC,
    0x0013, 0x0002, 0xFF88, 0xFFE1, 0x001B, 0x0021, 0x0016, 0x0008, 0x00D3, 0x0013, 0x0009, 0x00DC, 0x0013, 0x000B,
    0x00A7, 0x0013, 0x000E, 0x0000, 0x000A, 0x0010, 0x003B, 0x0023, 0x0011, 0x003B, 0x0023, 0x0007, 0x0021, 0x0016,
    0x001C, 0x001E, 0x002A, 0x0012, 0x00CA, 0x0013, 0x000D, 0x0000, 0x000A, 0x000C, 0x0000, 0x000A, 0x0023, 0x0000,
    0x000A, 0x0024, 0x0000, 0x000A, 0x001E, 0x0000, 0x000A, 0x001F, 0x0000, 0x000A, 0x001D, 0x0000, 0x000A, 0x002F,
    0xFF38, 0x0023, 0x0030, 0xFF51, 0x0025, 0x0031, 0xFF96, 0xFFD3, 0x0003, 0x00B4, 0x0013, 0x0032, 0x0107, 0x0011,
    0x0020, 0x00F7, 0x002D, 0x0033, 0x0103, 0x0031, 0x002E, 0x0022, 0x0047, 0xFFFF, 0xFFFF, 0xFFFF,
};

s16 D_800E2684[118] = {
    0x0000, 0x002D, 0x0010, 0x0087, 0x0004, 0x005E, 0x0013, 0x004E, 0x0005, 0x0066, 0x0013, 0x0056, 0x0006, 0x006F,
    0x0013, 0x005F, 0x0002, 0xFFD1, 0xFFDC, 0x0024, 0x001B, 0x0000, 0x0016, 0xFFE3, 0x0007, 0x0000, 0x0016, 0xFFE3,
    0x0008, 0x0061, 0x0013, 0x0044, 0x0009, 0x006A, 0x0013, 0x004D, 0x000B, 0x0037, 0x0013, 0x001A, 0x000C, 0x0000,
    0x000A, 0x0000, 0x000D, 0x0000, 0x000A, 0x0000, 0x000E, 0xFF60, 0x000A, 0xFF60, 0x0010, 0x0066, 0x0013, 0x0056,
    0x0011, 0x0066, 0x0013, 0x0056, 0x0012, 0x0058, 0x0013, 0x003B, 0x001C, 0xFFFD, 0x002A, 0xFFE0, 0x0020, 0x0012,
    0x002D, 0x0078, 0x001E, 0xFFEA, 0x000A, 0xFFEA, 0x001F, 0x000C, 0x000A, 0x0010, 0x001D, 0x0000, 0x000A, 0xFFD9,
    0x0023, 0x0000, 0x000A, 0x0000, 0x0024, 0x0000, 0x000A, 0x0000, 0x002F, 0xFF38, 0x0019, 0xFFD8, 0x0030, 0xFF51,
    0x001B, 0xFFF1, 0x0031, 0xFFDF, 0xFFCE, 0x0032, 0x0003, 0x0047, 0x0013, 0x0037, 0x0033, 0x003C, 0x0014, 0x003C,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
};

HudAudio gHudAudioData[2] = {
    { SOUND_CROWD, 0, 0, NULL, 0, 0, 0, 0, 0 },
    { SOUND_UNK_FF, 0, 0, NULL, 0, 0, 0, 0, 0 },
};

u8 gShowCourseDirections = TRUE;

u8 D_800E2794[4][4] = { { 1, 1, 1, 1 }, { 2, 2, 2, 2 }, { 2, 2, 2, 2 }, { 2, 2, 2, 2 } };

s8 gHudToggleSettings[4] = { 1, 1, 1, 1 };

s8 gPrevToggleSetting = 1;

u32 gHudLapColours[3] = {
    COLOUR_RGBA32(255, 40, 40, 254),
    COLOUR_RGBA32(40, 255, 40, 254),
    COLOUR_RGBA32(40, 40, 255, 254),
};

u8 gHudIndicatorTimer = 0;

ByteColour gHudMinimapColours[40] = {
    { 255, 160, 0 }, { 255, 255, 0 },   { 0, 128, 255 },   { 255, 255, 255 }, { 0, 175, 0 }, { 0, 255, 128 },
    { 255, 0, 0 },   { 255, 128, 190 }, { 128, 128, 128 }, { 0, 0, 255 },     { 0, 0, 0 },   { 0, 0, 0 },
    { 0, 0, 0 },     { 0, 0, 0 },       { 0, 0, 0 },       { 32, 0, 0 },      { 0, 0, 0 },   { 0, 0, 64 },
    { 0, 0, 0 },     { 0, 0, 0 },       { 0, 96, 0 },      { 0, 0, 0 },       { 0, 0, 0 },   { 128, 0, 0 },
    { 0, 0, 0 },     { 0, 0, 0 },       { 0, 64, 0 },      { 0, 0, 0 },       { 0, 32, 0 },  { 64, 0, 0 },
    { 0, 0, 0 },     { 64, 0, 64 },     { 0, 0, 0 },       { 0, 0, 96 },      { 0, 64, 0 },  { 0, 0, 0 },
    { 0, 128, 0 },   { 64, 0, 0 },      { 0, 0, 0 },       { 0, 0, 0 },
};

u32 gHudColour = COLOUR_RGBA32(255, 255, 255, 254);

#if REGION == REGION_JP
// ゴースト  -  Ghost
char D_800E42C8_E4EC8[] = { 0x80, 0x80, 0x80, 0x3B, 0x80, 0x5C, 0x80, 0x63, 0x00, 0x00 };

// セーブ  -  Save
char D_800E42D4_E4ED4[] = { 0x80, 0x5D, 0x80, 0x3B, 0x80, 0x8D };

// ふかのう - Impossible
char D_800E42DC_E4EDC[] = { 0x80, 0xD5, 0x80, 0xBF, 0x80, 0xD2, 0x80, 0xBC, 0x00, 0x00 };

char D_800E42E8_E4EE8[] = { 0x00, 0x00, 0x00, 0x00 };

// パック  -  Pak
char D_800E42EC_E4EEC[] = { 0x80, 0x90, 0x80, 0x4A, 0x80, 0x57 };

// フル  -  Full
char D_800E42F4_E4EF4[] = { 0x80, 0x6B, 0x80, 0x78, 0x00, 0x00 };

char D_800E42FC_E4EFC[] = { 0x00, 0x00, 0x00, 0x00 };

// パック  -  Pak
char D_800E4300_E4F00[] = { 0x80, 0x90, 0x80, 0x4A, 0x80, 0x57 };

// ふりょう  - Defective
char D_800E4308_E4F08[] = { 0x80, 0xD5, 0x80, 0xE1, 0x80, 0xB7, 0x80, 0xBC, 0x00, 0x00 };
#endif

UNUSED f32 sRecordVel = 0.0f; // Set to whatever the highest velocity recorded is, but never actually used.

// Unused?
s32 D_800E283C[] = { 0x06FFFFFF, 0x000FFFFF, 0x06000000, 0x0014FFFF };

/*******************************/

/************ .bss ************/

s8 gMinimapOpacity;
s8 gMinimapFade;
s8 gShowHUD;
s8 gMinimapXlu;

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
HudData *gCurrentHud;
HudData *gPlayerHud[MAXCONTROLLERS]; // One per active player
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
s32 gHudOffsetX; // Offset value to do the slide in animation.
s32 gHudBounceX; // Offset value to do the bounce when the hud slides in.
u16 gHudBounceTimer;
f32 gHudBounceMag;
u8 gHudRaceStart;
u8 D_80126D35;
u8 gHideRaceTimer;
u8 gNumActivePlayers;
u8 gWrongWayNagPrefix;
SoundMask *gRaceStartSoundMask;
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
u8 gHudAudioReset;
u8 gHudTimeTrialGhost;
s32 gHudVoiceTimer;
s32 gHudVoicePlayerID;
u16 gHudVoiceID;
DrawTexture gHudSprites[128];
s32 D_80127180;
Settings *gHudSettings;
u8 gHudSilverCoinRace;
u8 D_80127189;
u8 D_8012718A;
u8 gMinimapOpacityTarget;
s32 gStopwatchErrorX;
s32 gStopwatchErrorY;
LevelHeader_70 *D_80127194;
UNUSED s32 D_80127198[4];

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

    while (gAssetHudElementIds[gAssetHudElementIdsCount] != -1) {
        gAssetHudElementIdsCount++;
    }
    gAssetHudElements = mempool_alloc_safe(gAssetHudElementIdsCount * (sizeof(void *) + 1), COLOUR_TAG_BLUE);
    // Evil pointer shenanigans to store the timer in that last byte in the struct above.
    gAssetHudElementStaleCounter = (u8 *) ((gAssetHudElementIdsCount + (s32 *) gAssetHudElements));
    for (i = 0; i < gAssetHudElementIdsCount; i++) {
        gAssetHudElementStaleCounter[i] = 0;
        gAssetHudElements->entry[i] = NULL;
    }
    gAssetHudElements->entry[HUD_ELEMENT_UNK_01] =
        func_8007C12C(gAssetHudElementIds[HUD_ELEMENT_UNK_01] & 0x3FFF, 1); // ID: 86 - 0x56
    gAssetHudElements->entry[HUD_ELEMENT_UNK_17] =
        func_8007C12C(gAssetHudElementIds[HUD_ELEMENT_UNK_17] & 0x3FFF, 1); // ID: 291 - 0x123
    gAssetHudElements->entry[HUD_ELEMENT_UNK_08] =
        func_8007C12C(gAssetHudElementIds[HUD_ELEMENT_UNK_08] & 0x3FFF, 1); // ID: 156 - 0x9C
    gAssetHudElements->entry[HUD_ELEMENT_UNK_11] =
        func_8007C12C(gAssetHudElementIds[HUD_ELEMENT_UNK_11] & 0x3FFF, 1); // ID: 60 - 0x3C
    if (gNumActivePlayers != 3) {
        playerCount = gNumActivePlayers;
    } else {
        playerCount = 4; // Create four viewports if there are three players.
    }
    gPlayerHud[PLAYER_ONE] = mempool_alloc_safe(playerCount * sizeof(HudData), COLOUR_TAG_BLUE);
    gPlayerHud[PLAYER_TWO] = (HudData *) ((u8 *) gPlayerHud[PLAYER_ONE] + sizeof(HudData));
    gPlayerHud[PLAYER_THREE] = (HudData *) ((u8 *) gPlayerHud[PLAYER_TWO] + sizeof(HudData));
    gPlayerHud[PLAYER_FOUR] = (HudData *) ((u8 *) gPlayerHud[PLAYER_THREE] + sizeof(HudData));
    func_8009F034();
    D_80126D64 = 0;
    gWrongWayNagTimer = 0;
    D_80126D48 = 0;
    D_80126D66 = 4;
    D_80126D65 = 0;
    gStopwatchFaceID = 4;
    D_80126D69 = 1;
    D_80126D68 = 1;
    gHudAudioReset = FALSE;
    gHudVoiceID = 0;
    gHudVoiceTimer = 0;
    gRaceStartSoundMask = NULL;
    D_80126D44 = 0;
    gMinimapXlu = 0;
    D_80127194 = (LevelHeader_70 *) get_misc_asset(ASSET_MISC_58);
    func_8007F1E8(D_80127194);
    set_sound_channel_volume(0, 32767);
    set_sound_channel_volume(2, 32767);
    for (i = 0; i < 2; i++) {
        gHudAudioData[i].volume = 0;
        gHudAudioData[i].volumeRamp = 0;
        gHudAudioData[i].playerIndex = PLAYER_COMPUTER;
        if (gHudAudioData[i].soundMask) {
            sound_stop(gHudAudioData[i].soundMask);
        }
    }
}

// hud_init_element
#pragma GLOBAL_ASM("asm/nonmatchings/game_ui/func_8009F034.s")

/**
 * Frees all elements in the hud, and the player hud, and flushes particles
 */
void free_hud(void) {
    s32 i;
    for (i = 0; i < gAssetHudElementIdsCount; i++) {
        if (gAssetHudElements->entry[i] != NULL) {
            if ((gAssetHudElementIds[i] & HUD_ELEMENT_TEXTURE) == HUD_ELEMENT_TEXTURE) {
                free_texture(gAssetHudElements->entry[i]);
            } else if (gAssetHudElementIds[i] & HUD_ELEMENT_SPRITE) {
                free_sprite((Sprite *) gAssetHudElements->entry[i]);
            } else if (gAssetHudElementIds[i] & HUD_ELEMENT_OBJECT) {
                free_object((Object *) gAssetHudElements->entry[i]);
            } else {
                free_3d_model((ObjectModel **) gAssetHudElements->entry[i]);
            }
            gAssetHudElements->entry[i] = NULL;
        }
    }
    mempool_free(*gPlayerHud);
    mempool_free(gAssetHudElementIds);
    gAssetHudElementIdsCount = 0;
    mempool_free(gAssetHudElements);
    gParticlePtrList_flush();
}

/**
 * Return whether the race has been started from the HUDs end.
 */
u8 race_starting(void) {
    return gHudRaceStart;
}

/**
 * The root function for all of the heads up display during an active event.
 * Branches off to its own function for each race type, but overridden completely in time trial.
 */
void render_hud(Gfx **dList, MatrixS **mtx, Vertex **vertexList, Object *obj, s32 updateRate) {
    s32 countdown;
    Object_Racer *racer;

    gHudCurrentViewport = get_current_viewport();
    if (D_8012718A) {
        obj = get_racer_object_by_port(1 - gHudCurrentViewport);
    }
    gHudLevelHeader = get_current_level_header();
    if (obj == NULL) {
        if (cutscene_id() == 10) {
            obj = get_racer_object_by_port(PLAYER_ONE);
        }
    }
    if (obj != NULL && !(gHudLevelHeader->unkBC & 2)) {
        if (get_game_mode() != GAMEMODE_MENU) {
            gHUDCurrDisplayList = *dList;
            gHUDCurrMatrix = *mtx;
            gHUDCurrVertex = *vertexList;
            D_80127180 = 0;
            if (gMinimapFade) {
                gMinimapOpacity += updateRate;
                if (gMinimapOpacity > gMinimapOpacityTarget) {
                    gMinimapOpacity = gMinimapOpacityTarget;
                }
            } else {
                gMinimapOpacity -= updateRate;
                if (gMinimapOpacity < 0) {
                    gMinimapOpacity = 0;
                }
            }
            if (gShowHUD == FALSE) {
                racer = (Object_Racer *) obj->unk64;
                if (D_8012718A) {
                    D_80126D10 = 1 - racer->playerIndex;
                } else {
                    D_80126D10 = racer->playerIndex;
                }
                gCurrentHud = gPlayerHud[gHudCurrentViewport];
                if (cutscene_id() != 10) {
                    if (gHUDNumPlayers == ONE_PLAYER) {
                        if (input_pressed(D_80126D10) & D_CBUTTONS && racer->raceFinished == FALSE &&
                            ((gHudLevelHeader->race_type == RACETYPE_DEFAULT) ||
                             gHudLevelHeader->race_type == RACETYPE_HORSESHOE_GULCH) &&
                            gHudRaceStart) {
                            gShowCourseDirections = 1 - gShowCourseDirections;
                            sound_play((SOUND_TING_HIGHER + gShowCourseDirections), NULL);
                            if (gShowCourseDirections) {
                                gHudIndicatorTimer = 120;
                            } else {
                                gHudIndicatorTimer = 0;
                            }
                        }
                    } else if (input_pressed(D_80126D10) & D_CBUTTONS && racer->raceFinished == FALSE &&
                               !(gHudLevelHeader->race_type & RACETYPE_CHALLENGE) && gHudRaceStart) {
                        if (D_800E2794[gHUDNumPlayers][racer->playerIndex] < PLAYER_FOUR) {
                            D_800E2794[gHUDNumPlayers][racer->playerIndex]++;
                        } else {
                            D_800E2794[gHUDNumPlayers][racer->playerIndex] = PLAYER_ONE;
                        }
                        sound_play((SOUND_TING_HIGHEST - (D_800E2794[gHUDNumPlayers][racer->playerIndex] == 0)), NULL);
                    }
                    if (input_pressed(D_80126D10) & R_CBUTTONS && racer->raceFinished == FALSE && gHudRaceStart &&
                        gMinimapOpacity == 0) {
                        gHudToggleSettings[gHUDNumPlayers] = 1 - gHudToggleSettings[gHUDNumPlayers];
                        if (gHudToggleSettings[gHUDNumPlayers] == 0) {
                            sound_play(SOUND_TING_LOW, NULL);
                        } else {
                            sound_play(SOUND_TING_HIGH, NULL);
                        }
                    }
                }
                if (gRaceStartShowHudStep == 0) {
                    if (gHudLevelHeader->race_type & RACETYPE_CHALLENGE ||
                        gHudLevelHeader->race_type == RACETYPE_DEFAULT ||
                        gHudLevelHeader->race_type == RACETYPE_HORSESHOE_GULCH ||
                        gHudLevelHeader->race_type == RACETYPE_BOSS) {
                        gHudAudioData[0].volume = 127;
                        gHudAudioData[1].volume = 127;
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
                rsp_init(&gHUDCurrDisplayList);
                rdp_init(&gHUDCurrDisplayList);
                tex_enable_modes(RENDER_ALL);
                tex_disable_modes(RENDER_Z_COMPARE);
                sprite_opaque(FALSE);
                if (check_if_showing_cutscene_camera() == FALSE && gHudRaceStart == FALSE &&
                    racer->playerIndex == PLAYER_ONE) {
                    if (D_80126D35 != 0) {
                        gHudBounceX = sins_f(gHudBounceTimer) * gHudBounceMag * 8.0f;
                        gHudBounceTimer += updateRate << 0xB;
                        if (gHudBounceTimer >= 0x8000) {
                            gHudBounceTimer -= 0x8000;
                            gHudBounceMag = gHudBounceMag / 2;
                            if (gHudBounceMag <= 0.125) {
                                gHudRaceStart = TRUE;
                                gHudOffsetX = 0;
                            }
                        }
                    } else {
                        if (gRaceStartShowHudStep == 1) {
                            sound_play(SOUND_WHOOSH1, NULL);
                            gRaceStartShowHudStep += 1;
                        }
                        gHudOffsetX -= updateRate * 13;
                        if (gHudOffsetX < 0) {
                            gHudOffsetX = 0;
                        }
                        if (gHudOffsetX == 0) {
                            D_80126D35 = 1;
                            sound_play(SOUND_EXPLOSION2, NULL);
                            gHudBounceX = 0;
                        }
                    }
                }
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                render_magnet_reticle(obj);
                set_ortho_matrix_view(&gHUDCurrDisplayList, &gHUDCurrMatrix);
                gDPSetEnvColor(gHUDCurrDisplayList++, 255, 255, 255, 0);
                countdown = get_race_countdown() >> 1;
                if (is_in_time_trial()) {
                    func_800A277C(countdown, obj, updateRate);
                } else {
                    if (cutscene_id() == 10) {
                        sprite_anim_off(TRUE);
                        render_balloon_count(racer);
                        sprite_anim_off(FALSE);
                    } else {
                        switch (get_current_level_race_type()) {
                            case RACETYPE_DEFAULT:
                            case RACETYPE_HORSESHOE_GULCH:
                                if (is_taj_challenge()) {
                                    render_hud_taj_race(countdown, obj, updateRate);
                                } else {
                                    render_hud_race(countdown, obj, updateRate);
                                }
                                break;
                            case RACETYPE_BOSS:
                                render_hud_race_boss(countdown, obj, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_BANANAS:
                                render_hud_banana_challenge(countdown, obj, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_BATTLE:
                                render_hud_battle(countdown, obj, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_EGGS:
                                render_hud_challenge_eggs(countdown, obj, updateRate);
                                break;
                            default:
                                render_hud_hubworld(obj, updateRate);
                                break;
                        }
                    }
                }
                if (racer->raceFinished == TRUE) {
                    sprite_anim_off(TRUE);
                    if (is_in_time_trial()) {
                        render_time_trial_finish(racer, updateRate);
                    } else if (get_viewport_count() == VIEWPORTS_COUNT_1_PLAYER && racer->finishPosition == 1) {
                        if (is_in_two_player_adventure()) {
                            if (get_current_level_race_type() == RACETYPE_BOSS) {
                                goto showFinishRace;
                            }
                            goto block_95;
                        }
                    showFinishRace:
                        render_race_finish_position(racer, updateRate);
                    } else {
                    block_95:
                        func_800A6254(racer, updateRate);
                    }
                    sprite_anim_off(FALSE);
                }
                gMinimapFade = FALSE;
                sprite_opaque(TRUE);
                if (D_80127180) {
                    gHudSprites[D_80127180].texture = NULL;
                    texrect_draw(&gHUDCurrDisplayList, gHudSprites, 0, 0, 255, 255, 255, 255);
                }
                *dList = gHUDCurrDisplayList;
                *mtx = gHUDCurrMatrix;
                *vertexList = gHUDCurrVertex;
                tex_enable_modes(RENDER_ALL);
            }
        }
    }
}

/**
 * Clear any sounds associated with the HUD then set the data to null.
 */
void hud_audio_init(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (gHudAudioData[i].soundMask) {
            sound_stop(gHudAudioData[i].soundMask);
            gHudAudioData[i].soundMask = NULL;
            gHudAudioData[i].volume = 0;
        }
    }
}

/**
 * Play delayed voice clips if there's one waiting.
 * Also play any background audio set by the HUD.
 * This includes the sound of the crowd at the beginning and end of a race.
 */
void hud_audio_update(s32 updateRate) {
    s32 temp;
    s32 i;

    if (gHudVoiceTimer > 0) {
        gHudVoiceTimer -= updateRate;
        if (gHudVoiceTimer <= 0) {
            gHudVoiceTimer = 0;
            if (gHUDVoiceSoundMask == NULL) {
                sound_play(gHudVoiceID, &gHUDVoiceSoundMask);
            }
        }
    }
    for (i = 0; i < 2; i++) {
        if (gHudAudioData[i].volume) {
            if (gHudAudioData[i].soundMask == NULL) {
                sound_play(gHudAudioData[i].soundID, (s32 *) &gHudAudioData[i].soundMask);
            }
            sound_volume_set_relative(gHudAudioData[i].soundID, gHudAudioData[i].soundMask, gHudAudioData[i].volume);
            if (gHudAudioData[i].volumeRamp > 0) {
                temp = gHudAudioData[i].volumeRamp * updateRate;
                if ((127 - temp) >= gHudAudioData[i].volume) {
                    gHudAudioData[i].volume += temp;
                } else {
                    gHudAudioData[i].volumeRamp = 0;
                    gHudAudioData[i].volume = 127;
                }
            } else if (gHudAudioData[i].volumeRamp < 0) {
                temp = gHudAudioData[i].volumeRamp * updateRate;
                if (-temp < gHudAudioData[i].volume) {
                    gHudAudioData[i].volume += temp;
                } else {
                    gHudAudioData[i].volumeRamp = 0;
                    gHudAudioData[i].volume = 0;
                }
            }
        } else {
            if (gHudAudioData[i].soundMask) {
                sound_stop(gHudAudioData[i].soundMask);
                gHudAudioData[i].soundMask = 0;
            }
        }
    }
    if (gHudAudioReset && gHudAudioData[0].volume == 0) {
        gHudAudioReset = FALSE;
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
void render_hud_race(s32 countdown, Object *obj, s32 updateRate) {
    Object_Racer *racer = &obj->unk64->racer;

    sprite_anim_off(TRUE);
    render_course_indicator_arrows(racer, updateRate);
    render_wrong_way_text(racer, updateRate);
    render_race_start(countdown, updateRate);

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
    sprite_anim_off(FALSE);
}

/**
 * Render the onscreen course arrows that show the player where to go.
 */
void render_course_indicator_arrows(Object_Racer *racer, s32 updateRate) {
    s32 timer;
    s32 type;
    HudElement *indicator;

    if (gShowCourseDirections) {
        timer = racer->indicator_timer;
        if (timer > 0) {
            type = racer->indicator_type;
            racer->indicator_timer = timer - updateRate;
            if (type) {
                indicator = (HudElement *) &gCurrentHud->entry[HUD_COURSE_ARROWS];
                switch (type) {
                    case INDICATOR_LEFT:
                        indicator->spriteID = HUD_SPRITE_INDICATOR_TURN_45;
                        indicator->rotation.y_rotation = 0;
                        break;
                    case INDICATOR_LEFT_SHARP:
                        indicator->spriteID = HUD_SPRITE_INDICATOR_TURN_90;
                        indicator->rotation.y_rotation = 0;
                        break;
                    case INDICATOR_LEFT_UTURN:
                        indicator->spriteID = HUD_SPRITE_INDICATOR_U;
                        indicator->rotation.y_rotation = 0;
                        break;
                    case INDICATOR_RIGHT:
                        indicator->spriteID = HUD_SPRITE_INDICATOR_TURN_45;
                        indicator->rotation.y_rotation = -0x8000;
                        break;
                    case INDICATOR_RIGHT_SHARP:
                        indicator->spriteID = HUD_SPRITE_INDICATOR_TURN_90;
                        indicator->rotation.y_rotation = -0x8000;
                        break;
                    case INDICATOR_RIGHT_UTURN:
                        indicator->spriteID = HUD_SPRITE_INDICATOR_U;
                        indicator->rotation.y_rotation = -0x8000;
                        break;
                    case INDICATOR_UP:
                        indicator->spriteID = HUD_SPRITE_INDICATOR_DOWN;
                        indicator->rotation.y_rotation = -0x8000;
                        indicator->rotation.x_rotation = -0x8000;
                        break;
                    case INDICATOR_DOWN:
                        indicator->spriteID = HUD_SPRITE_INDICATOR_DOWN;
                        indicator->rotation.y_rotation = 0;
                        break;
                    default: // INDICATOR_EXCLAMATION
                        indicator->spriteID = HUD_SPRITE_INDICATOR_EXCLAMATION;
                        indicator->rotation.y_rotation = 0;
                        break;
                }
                // Flip the arrow direction on adventure 2.
                if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS && racer->indicator_type < 30) {
                    indicator->rotation.y_rotation = (s16) (0x8000 - indicator->rotation.y_rotation);
                }
                if (gHUDNumPlayers == ONE_PLAYER && racer->raceFinished == FALSE && racer->indicator_type &&
                    gHudIndicatorTimer == 0) {
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, indicator);
                    indicator->pos.x = -indicator->pos.x;
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, indicator);
                    indicator->pos.x = -indicator->pos.x;
                    indicator->rotation.x_rotation = 0;
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                }
            }
        } else {
            racer->indicator_timer = 0;
        }
        if (gHudIndicatorTimer) {
            if (gHudIndicatorTimer & 0x20) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                indicator = &gCurrentHud->entry[HUD_COURSE_ARROWS];
                indicator->rotation.y_rotation = 0;
                indicator->rotation.x_rotation = 0;
                indicator->spriteID = HUD_SPRITE_INDICATOR_EXCLAMATION;
                if ((get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) && ((s32) racer->indicator_type < 30)) {
                    indicator->rotation.y_rotation = (s16) (0x8000 - indicator->rotation.y_rotation);
                }
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, indicator);
                indicator->pos.x = -indicator->pos.x;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, indicator);
                indicator->pos.x = -indicator->pos.x;
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
            if (updateRate < gHudIndicatorTimer) {
                gHudIndicatorTimer -= updateRate;
                return;
            }
            gHudIndicatorTimer = 0;
        }
    }
}

/*
 * Renders the HUD for the Smokey Castle challenge.
 * Shows each players portrait and their aquired treasure.
 */
void render_hud_banana_challenge(s32 countdown, Object *obj, s32 updateRate) {
    Object_Racer *racer;
    Object **racers;
    s32 numRacers;
    s32 i;

    racer = &obj->unk64->racer;
    racers = get_racer_objects(&numRacers);
    sprite_anim_off(TRUE);
    render_race_start(countdown, updateRate);
    switch (gNumActivePlayers) {
        case 1:
            for (i = 0; i < numRacers; i++) {
                racer = &racers[i]->unk64->racer;
                render_treasure_hud(racer);
                if (i == 1) {
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x += 55.0f;
                    gCurrentHud->entry[HUD_TREASURE_METRE].pos.x += 55.0f;
                }
                gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x += 55.0f;
                gCurrentHud->entry[HUD_TREASURE_METRE].pos.x += 55.0f;
            }
            if (1) {} // Fakematch
            gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x -= 275.0f;
            gCurrentHud->entry[HUD_TREASURE_METRE].pos.x -= 275.0f;
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
    sprite_anim_off(FALSE);
}

/**
 * The Egg Collector challenge mode displays the icons of each player and their score.
 */
void render_hud_challenge_eggs(s32 countdown, Object *obj, s32 updateRate) {
    Object_Racer *racer = &obj->unk64->racer;
    if (racer->raceFinished == FALSE) {
        sprite_anim_off(TRUE);
        render_race_start(countdown, updateRate);
        render_weapon_hud(obj, updateRate);
        if ((127 - (updateRate * 2)) >= gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].challengeEggs.alphaTimer) {
            gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].challengeEggs.alphaTimer += updateRate * 2;
        } else {
            gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].challengeEggs.alphaTimer = (gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].challengeEggs.alphaTimer + (updateRate * 2)) - 255;
        }
        // Skip rendering the portraits if in 2 player, it's done elsewhere.
        if (gNumActivePlayers != 2) {
            hud_draw_eggs(obj, updateRate);
        }
        sprite_anim_off(FALSE);
    }
}

/**
 * Position and render the portraits for the egg challenge HUD.
 */
void hud_draw_eggs(Object *racerObj, s32 updateRate) {
    Object **racers;
    s32 i;
    Object_Racer *racer;
    s32 numRacers;
    s32 finishedPlayers;
    Object_Racer *curRacer;
    s32 portraitX;
    s32 diffX;
    s32 portraitY;
    s32 diffY;

    racers = get_racer_objects(&numRacers);
    if (gNumActivePlayers == 2) {
        finishedPlayers = 0;
        for (i = 0; i < numRacers; i++) {
            curRacer = &racers[i]->unk64->racer;
            if (curRacer->playerIndex != PLAYER_COMPUTER && curRacer->raceFinished) {
                finishedPlayers++;
            }
        }
        if (finishedPlayers == 2) {
            return;
        }
    }
    if (racerObj != NULL) {
        racer = &racerObj->unk64->racer;
    } else {
        racer = &racers[0]->unk64->racer;
    }
    if (numRacers == 4) {
        sprite_anim_off(TRUE);
        portraitX = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
        portraitY = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
        diffX = (gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x - portraitX);
        diffY = (gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.y - portraitY);
        for (i = 0; i < 4; i++) {
            curRacer = &racers[i]->unk64->racer;
            if (gNumActivePlayers < 3 || racer->playerIndex == curRacer->playerIndex) {
                hud_eggs_portrait(curRacer, updateRate);
            }
            gHudColour = COLOUR_RGBA32(255, 255, 255, 254);
            if (gNumActivePlayers == 1) {
                gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x += 68.0f;
            } else if (gNumActivePlayers == 2) {
                gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x = portraitX;
                if (osTvType == OS_TV_TYPE_PAL) {
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y += 66.0;
                    gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.y += 66.0;
                } else {
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y += 55.0f;
                    gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.y += 55.0f;
                }
            }
            gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x + diffX;
        }
        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x = portraitX;
        gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x = portraitX + diffX;
        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = portraitY;
        gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.y = portraitY + diffY;
        sprite_anim_off(FALSE);
    }
}

/**
 * Render the character portrait and the number of eggs they have secured.
 * Skip the portrait in 3/4 player, unless player 4 is AI controlled.
 */
void hud_eggs_portrait(Object_Racer *racer, UNUSED s32 updateRate) {
    s32 i;
    UNUSED s32 pad;
    s32 alpha;
    s32 prevY;
    s32 i2;

    prevY = gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x;
    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].spriteID = racer->characterId + HUD_SPRITE_PORTRAIT;
    D_80126CD5 = TRUE;
    if (gNumActivePlayers < 3 || (gNumActivePlayers == 3 && racer->playerIndex == PLAYER_COMPUTER)) {
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT]);
    }
    if (gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].challengeEggs.alphaTimer < 0) {
        alpha = (gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].challengeEggs.alphaTimer * 2) + 256;
    } else {
        alpha = 255 - (gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].challengeEggs.alphaTimer * 2);
    }
    if (alpha > 254) {
        alpha = 254;
    }
    for (i = 0; i < racer->lap && i < HUD_EGG_TOTAL; i++) {
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON]);
        gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x += 12.0f;
    }
    gHudColour = alpha | COLOUR_RGBA32(255, 255, 255, 0);
    i2 = i;
    for (i = 0; i < racer->eggHudCounter && i2 < HUD_EGG_TOTAL; i++) {
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON]);
        i2++;
        gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x += 12.0f;
    }
    gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x = prevY;
    D_80126CD5 = FALSE;
}

/**
 * Render the HUD for the battle mode challenge.
 * Shows each players portrait and their remaining health.
 */
void render_hud_battle(s32 countdown, Object *obj, s32 updateRate) {
    Object **racerObjs;
    Object_Racer *racer;
    s32 numRacers;
    s32 racersFinished;
    s32 i;

    racer = (Object_Racer *) obj->unk64;
    if (gNumActivePlayers != 1 || racer->raceFinished == FALSE) {
        sprite_anim_off(TRUE);
        render_race_start(countdown, updateRate);
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
        sprite_anim_off(FALSE);
    }
}

#ifdef NON_MATCHING
// hud_render_lives
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

    sprite_anim_off(TRUE);
    if (numRacers == 4) {
        offset = 0;
        prevCurrHudUnk64C = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
        prevCurrHudUnk650 = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
        for (i = 0; i < 4; i++) {
            curRacer = &racers[i]->unk64->racer;
            temp = prevCurrHudUnk64C ^ 0;
            temp3 = temp - gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
            temp = temp3;
            temp2 = offset + prevCurrHudUnk650;
            temp4 = temp2 - gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
            temp2 = temp4;
            gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x += temp;
            gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y += temp2;
            gCurrentHud->entry[HUD_BATTLE_BANANA_ICON].pos.x += temp;
            gCurrentHud->entry[HUD_BATTLE_BANANA_ICON].pos.y -= temp2;
            gCurrentHud->entry[HUD_BATTLE_BANANA_X].pos.x += temp;
            gCurrentHud->entry[HUD_BATTLE_BANANA_X].pos.y += temp2;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.x += temp;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.y += temp2;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].pos.x += temp;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].pos.y += temp2;
            if (gNumActivePlayers < 3 || racer->playerIndex == curRacer->playerIndex) {
                hud_draw_lives(curRacer, updateRate);
            }
            if (gNumActivePlayers == 1) {
                prevCurrHudUnk64C += 68;
            } else if (gNumActivePlayers == 2) {
                if (osTvType == OS_TV_TYPE_PAL) {
                    offset += 66.0;
                } else {
                    offset += 55;
                }
            }
        }

        temp = prevCurrHudUnk64C;
        temp3 = temp - gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
        temp = temp3;
        temp2 = prevCurrHudUnk650;
        temp4 = temp2 - gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
        temp2 = temp4;
        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x += temp;
        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y += temp2;
        gCurrentHud->entry[HUD_BATTLE_BANANA_ICON].pos.x += temp;
        gCurrentHud->entry[HUD_BATTLE_BANANA_ICON].pos.y -= temp2;
        gCurrentHud->entry[HUD_BATTLE_BANANA_X].pos.x += temp;
        gCurrentHud->entry[HUD_BATTLE_BANANA_X].pos.y += temp2;
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.x += temp;
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.y += temp2;
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].pos.x += temp;
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].pos.y += temp2;
    }
    sprite_anim_off(FALSE);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_ui/func_800A1E48.s")
#endif

/**
 * Render the portrait and life counter in the battle mode.
 * In 3/4 player, skips the portrait for all human players. Player 4 has a portrait if it's AI.
 */
void hud_draw_lives(Object_Racer *racer, UNUSED s32 updateRate) {
    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].spriteID = racer->characterId + HUD_SPRITE_PORTRAIT;
    if (gNumActivePlayers < 3 || (gNumActivePlayers == 3 && racer->playerIndex == PLAYER_COMPUTER)) {
        D_80126CD5 = TRUE;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT]);
        D_80126CD5 = FALSE;
        rdp_init(&gHUDCurrDisplayList);
        reset_render_settings(&gHUDCurrDisplayList);
    }
    if (racer->bananas < 10) {
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].spriteOffset = racer->bananas;
        if (gNumActivePlayers == 2) {
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.x += 6.0f;
        }
    } else {
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].spriteOffset = racer->bananas / 10;
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].spriteOffset = racer->bananas % 10;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2]);
    }
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1]);
    if (gNumActivePlayers == 2 && racer->bananas < 10) {
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.x -= 6.0f;
    }
    if (gNumActivePlayers != 2) {
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BATTLE_BANANA_X]);
        sprite_opaque(TRUE);
        D_80126CD5 = TRUE;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BATTLE_BANANA_ICON]);
        D_80126CD5 = FALSE;
        sprite_opaque(FALSE);
    }
}

/**
 * When racing the boss, render the essentials, but skip the bananas.
 */
void render_hud_race_boss(s32 countdown, Object *obj, s32 updateRate) {
    LevelHeader *level;
    Object_Racer *racer = (Object_Racer *) obj->unk64;

    sprite_anim_off(TRUE);
    render_wrong_way_text(racer, updateRate);
    render_race_start(countdown, updateRate);
    render_race_time(racer, updateRate);
    render_weapon_hud(obj, updateRate);

    level = get_current_level_header();
    if (level->laps > 1) {
        render_lap_count(racer, updateRate);
    }

    render_speedometer(obj, updateRate);
    render_race_position(racer, updateRate);
    sprite_anim_off(FALSE);
}

/**
 * When racing Taj in the overworld, render most of the basic race hud.
 */
void render_hud_taj_race(s32 countdown, Object *obj, s32 updateRate) {
    Object_Racer *racer = (Object_Racer *) obj->unk64;

    sprite_anim_off(TRUE);
    render_wrong_way_text(racer, updateRate);
    render_lap_count(racer, updateRate);
    render_race_position(racer, updateRate);
    render_race_time(racer, updateRate);
    render_race_start(countdown, updateRate);
    render_speedometer(obj, updateRate);
    sprite_anim_off(FALSE);
}

/**
 * The hub world displays the player's balloon count.
 * In two player adventure, the icon of the character of the player sitting out is displayed.
 */
void render_hud_hubworld(Object *obj, s32 updateRate) {
    Object_Racer *racer;
    HudElement *portrait;

    if (get_viewport_count() == 0) {
        racer = (Object_Racer *) obj->unk64;
        sprite_anim_off(TRUE);
        render_balloon_count(racer);
        render_speedometer(obj, updateRate);
        if (is_in_two_player_adventure()) {
            portrait = (HudElement *) &gCurrentHud->entry[HUD_TWO_PLAYER_ADV_PORTRAIT];
            portrait->spriteID = (get_settings()->racers[1].character + HUD_SPRITE_PORTRAIT);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, portrait);
        }
        sprite_anim_off(FALSE);
    }
}

#ifdef NON_MATCHING
// render_hud_time_trial
// https://decomp.me/scratch/BWqz9
// Draws Time Trial HUD. Also handles music/audio?
void func_800A277C(s32 arg0, Object *playerRacerObj, s32 updateRate) {
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
        ttSWBody.size = sizeof(LevelObjectEntryCommon);
        ttSWBody.x = 0;
        ttSWBody.y = 0;
        ttSWBody.z = 0;
        gAssetHudElements->entry[20] = spawn_object(&ttSWBody, 0);
        gCurrentHud->entry[HUD_STOPWATCH_HANDS].rotation.y_rotation = -0x8000;
        if (gAssetHudElements->entry[20] != NULL) {
            ((Object *) gAssetHudElements->entry[20])->segment.animFrame = 0;
        }
    }
    if (gAssetHudElements->entry[34] == 0) {
        ttSWArms.objectID = gAssetHudElementIds[34] & 0xFFFF;
        ttSWArms.size = sizeof(LevelObjectEntryCommon);
        ttSWArms.x = 0;
        ttSWArms.y = 0;
        ttSWArms.z = 0;
        gAssetHudElements->entry[34] = spawn_object(&ttSWArms, 0);
        gCurrentHud->entry[HUD_STOPWATCH].rotation.y_rotation = -0x8000;
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
                            if (curRacer->wrongWayCounter == 0 && curRacer->raceFinished == 0) {
                                set_stopwatch_face(4, 0, 4, 1, 1);
                            }
                        }
                    }
                }
            }
            obj_animate(ttSWBodyObject);
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_STOPWATCH_HANDS]);

        for (i = 0; curRacer->lap >= i && i < 5; i++) {
            stopwatchTimer += curRacer->lap_times[i];
        }

        if (osTvType == OS_TV_TYPE_PAL) {
            stopwatchTimer = (f32) stopwatchTimer * 1.2;
        }
        if (normalise_time(36000) < stopwatchTimer) {
            stopwatchTimer = normalise_time(36000);
        }
        gCurrentHud->entry[HUD_STOPWATCH].rotation.z_rotation = ((stopwatchTimer * 0x444) + 0x7FF8);
        if (get_contpak_error() <= 0) {
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_STOPWATCH]);
        }
        gCurrentHud->entry[HUD_STOPWATCH].rotation.z_rotation = ((((stopwatchTimer / 60) + 30) % 60) * 0x444);
        gCurrentHud->entry[HUD_STOPWATCH].pos.y = gCurrentHud->entry[HUD_STOPWATCH_HANDS].pos.y + 28.0f;
        if (get_contpak_error() <= 0) {
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_STOPWATCH]);
        }
        obj68->animUpdateTimer = 0;
        sprite_anim_off(TRUE);
        render_course_indicator_arrows(curRacer, updateRate);
        if (!curRacer->raceFinished) {
            spB8 = gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.y;
            for (i = 0; i < curRacer->countLap && i < gHudLevelHeader->laps; i++) {
                // FAKEMATCH
                get_timestamp_from_frames(curRacer->lap_times[i] & 0xFFFFFFFFFFFFFFFF, &spB4, &spB0, &spAC);
                gHudColour = gHudLapColours[i];
                render_timer(gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x, spB8, spB4, spB0, spAC, 1);
                gHudColour = COLOUR_RGBA32(255, 255, 255, 254);
                spB8 += 12;
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                gCurrentHud->entry[HUD_TIME_TRIAL_LAP_NUMBER].spriteOffset = i + 1;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                              (HudElement *) &gCurrentHud->entry[HUD_TIME_TRIAL_LAP_NUMBER]);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                              (HudElement *) &gCurrentHud->entry[HUD_TIME_TRIAL_LAP_TEXT]);
                gCurrentHud->entry[HUD_TIME_TRIAL_LAP_NUMBER].pos.y += 12.0f;
                gCurrentHud->entry[HUD_TIME_TRIAL_LAP_TEXT].pos.y += 12.0f;
            }
            if (1) {} // FAKEMATCH
            posX = ((i * 4) - i) * 4;
            gCurrentHud->entry[HUD_TIME_TRIAL_LAP_NUMBER].pos.y -= posX;
            gCurrentHud->entry[HUD_TIME_TRIAL_LAP_TEXT].pos.y -= posX;
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
        if ((curRacer->lap > 0) && (curRacer->lap < gHudLevelHeader->laps) &&
            (curRacer->lap_times[curRacer->lap] < 20) && (gHUDVoiceSoundMask == 0) &&
            (curRacer->vehicleID <= VEHICLE_PLANE)) {
            gHudSettings = get_settings();
            if (curRacer->lap_times[curRacer->lap - 1] <
                gHudSettings->flapTimesPtr[curRacer->vehicleID][get_current_map_id()]) {
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
        if (timetrial_valid_player_ghost()) {
            ttSWBodyObject = timetrial_player_ghost();
            if (ttSWBodyObject != NULL) {
                if ((get_race_countdown() == 0) && (curRacer->raceFinished == 0)) {
                    posY = ttSWBodyObject->segment.trans.y_position - playerRacerObj->segment.trans.y_position;
                    posX = ttSWBodyObject->segment.trans.x_position - playerRacerObj->segment.trans.x_position;
                    posZ = ttSWBodyObject->segment.trans.z_position - playerRacerObj->segment.trans.z_position;
                    if ((sqrtf(posX * posX + (posY * posY) + (posZ * posZ)) < 600.0f) && (gHUDVoiceSoundMask == 0) &&
                        (D_80126D50 == 0)) {
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
        } else if (curRacer->wrongWayCounter > 120) {
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
                case CONTPAK_ERROR_UNKNOWN:
                    SWMessage[0] = "CAN'T";
                    SWMessage[1] = "SAVE";
                    SWMessage[2] = "GHOST";
                    break;
                case CONTPAK_ERROR_FULL:
                    SWMessage[0] = " CONTROLLER";
                    SWMessage[1] = "PAK";
                    SWMessage[2] = "FULL";
                    break;
                case CONTPAK_ERROR_DAMAGED:
                    SWMessage[0] = " CONTROLLER";
                    SWMessage[1] = "PAK";
                    SWMessage[2] = "DAMAGED";
                    break;
            }
            set_kerning(1);
            set_text_font(ASSET_FONTS_FUNFONT);
            // Draw text shadow.
            set_text_colour(0, 0, 0, 255, 255);
            draw_text(&gHUDCurrDisplayList, gStopwatchErrorX + gHudOffsetX + gHudBounceX + 1, gStopwatchErrorY + 1,
                      SWMessage[0], ALIGN_MIDDLE_CENTER);
            draw_text(&gHUDCurrDisplayList, gStopwatchErrorX + gHudOffsetX + gHudBounceX + 1, gStopwatchErrorY + 15,
                      SWMessage[1], ALIGN_MIDDLE_CENTER);
            draw_text(&gHUDCurrDisplayList, gStopwatchErrorX + gHudOffsetX + gHudBounceX + 1, gStopwatchErrorY + 29,
                      SWMessage[2], ALIGN_MIDDLE_CENTER);
            // Draw actual text.
            set_text_colour(D_80127194->red, D_80127194->green, D_80127194->blue, 128, D_80127194->alpha);
            draw_text(&gHUDCurrDisplayList, gStopwatchErrorX + gHudOffsetX + gHudBounceX, gStopwatchErrorY,
                      SWMessage[0], ALIGN_MIDDLE_CENTER);
            draw_text(&gHUDCurrDisplayList, gStopwatchErrorX + gHudOffsetX + gHudBounceX, gStopwatchErrorY + 14,
                      SWMessage[1], ALIGN_MIDDLE_CENTER);
            draw_text(&gHUDCurrDisplayList, gStopwatchErrorX + gHudOffsetX + gHudBounceX, gStopwatchErrorY + 28,
                      SWMessage[2], ALIGN_MIDDLE_CENTER);
            update_colour_cycle(D_80127194, updateRate);
            set_kerning(0);
        }
        sprite_anim_off(FALSE);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_ui/func_800A277C.s")
#endif

void set_stopwatch_face(u8 arg0, u8 arg1, u8 faceID, u8 arg3, u8 arg4) {
    s32 var_a3;
    s32 i;
    UNUSED u8 *temp_v0_2;
    Object_68 **unk68;
    Object *hud20;

    if (is_in_time_trial()) {
        hud20 = gAssetHudElements->entry[HUD_ELEMENT_UNK_14];
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

/**
 * Reset the angle of the speedometre's needle to the starting position.
 */
void hud_speedometre_reset(void) {
    gCurrentHud->entry[HUD_SPEEDOMETRE_ARROW].rotation.z_rotation = 0x6490;
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
                    vel = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                                (obj->segment.y_velocity * obj->segment.y_velocity) +
                                (obj->segment.z_velocity * obj->segment.z_velocity));
                } else {
                    vel = sqrtf((obj->segment.x_velocity * obj->segment.x_velocity) +
                                (obj->segment.z_velocity * obj->segment.z_velocity));
                }
                if (sRecordVel < vel) {
                    sRecordVel = vel;
                }
                vel *= 4.0f;
                if (racer->drift_direction != 0) {
                    vel += 7.0f; //!@Bug: Planes and hovercraft use drift_direction for something else, applying this
                                 //! unintentionally.
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
                    if (vel < gCurrentHud->entry[HUD_SPEEDOMETRE_ARROW].rotation.z_rotation) {
                        gCurrentHud->entry[HUD_SPEEDOMETRE_ARROW].rotation.z_rotation +=
                            ((vel - gCurrentHud->entry[HUD_SPEEDOMETRE_ARROW].rotation.z_rotation) / 2);
                    } else {
                        gCurrentHud->entry[HUD_SPEEDOMETRE_ARROW].rotation.z_rotation +=
                            ((vel - gCurrentHud->entry[HUD_SPEEDOMETRE_ARROW].rotation.z_rotation) / 8);
                    }
                }
                if (gHudToggleSettings[gHUDNumPlayers] == 0) {
                    if (gMinimapXlu & 2) {
                        opacity = 255.0f - ((gMinimapOpacity * 255.0f) / gMinimapOpacityTarget);
                    } else {
                        opacity = 255;
                    }
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_SPEEDOMETRE_BG]);
                    reset_render_settings(&gHUDCurrDisplayList);
                    sprite_opaque(TRUE);
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, opacity);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                                  &gCurrentHud->entry[HUD_SPEEDOMETRE_ARROW]);
                    sprite_opaque(FALSE);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                                  &gCurrentHud->entry[HUD_SPEEDOMETRE_0]);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                                  &gCurrentHud->entry[HUD_SPEEDOMETRE_30]);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                                  &gCurrentHud->entry[HUD_SPEEDOMETRE_60]);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                                  &gCurrentHud->entry[HUD_SPEEDOMETRE_90]);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                                  &gCurrentHud->entry[HUD_SPEEDOMETRE_120]);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                                  &gCurrentHud->entry[HUD_SPEEDOMETRE_150]);
                }
            }
        }
    }
}

/**
 * Call the functions that render the "Get Ready" and "GO!" as well as their countdowns to control fade.
 * This function will also call to begin the background music for 1 and 2 player. 3 and 4 are treated with silence.
 */
void render_race_start(s32 countdown, s32 updateRate) {

    if (!is_game_paused()) {
        if (countdown == 0 && gHudAudioData[0].playerIndex == PLAYER_COMPUTER) {
            gHudAudioData[0].volumeRamp = -1;
            gHudAudioData[1].volumeRamp = -1;
        }
        if (gHUDNumPlayers == TWO_PLAYERS) {
            sprite_opaque(TRUE);
        }
        if (countdown > 0) {
            if (gHudRaceStart) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, (countdown * 255) / 40);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_RACE_START_READY]);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                if (gRaceStartShowHudStep == 2) {
                    sound_play(SOUND_VOICE_TT_GET_READY, &gHUDVoiceSoundMask);
                    gRaceStartShowHudStep++;
                }
            }
            // Make engine revving sounds of random pitches while the race is waiting to begin.
            if (gRaceStartSoundMask == NULL && func_80023568() == 0) {
                f32 frequency;
                UNUSED s32 pad;
                Object **racerGroup;
                Object *randomRacer;
                Object_Racer *racer;
                s32 numRacerObjects;
                racerGroup = get_racer_objects(&numRacerObjects);
                randomRacer = racerGroup[get_random_number_from_range(1, numRacerObjects) - 1];
                racer = (Object_Racer *) randomRacer->unk64;
                if (racer->vehicleID == VEHICLE_CAR) {
                    if (get_random_number_from_range(0, 100) >= 96) {
                        frequency = 1.25 - ((get_random_number_from_range(0, 7) * 0.5) / 7.0);
                        func_800095E8(76, randomRacer->segment.trans.x_position, randomRacer->segment.trans.y_position,
                                      randomRacer->segment.trans.z_position, 4,
                                      ((get_random_number_from_range(0, 7) * 63) / 7) + 24, frequency * 100.0f,
                                      &gRaceStartSoundMask);
                    }
                }
            }
        } else if (gCurrentHud->entry[HUD_RACE_START_GO].pos.x > -200.0f) {
            gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                          (HudElement *) &gCurrentHud->entry[HUD_RACE_START_GO]);
            gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            gCurrentHud->entry[HUD_RACE_START_GO].raceStartGo.musicStartTimer[gHudCurrentViewport] += updateRate;
            if (gCurrentHud->entry[HUD_RACE_START_GO].raceStartGo.musicStartTimer[gHudCurrentViewport] >= 60) {
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
                gCurrentHud->entry[HUD_RACE_START_GO].pos.x -= (updateRate * 8);
            }
            if (gRaceStartShowHudStep == 3) {
                sound_play(SOUND_VOICE_TT_GO, &gHUDVoiceSoundMask);
                if (timetrial_ghost_staff() && timetrial_staff_unbeaten() == FALSE) {
                    hud_sound_play_delayed(SOUND_VOICE_TT_BEAT_MY_TIME, 1.7f, PLAYER_ONE);
                    set_delayed_text(ASSET_GAME_TEXT_82, 1.7f); // Now try and beat my time!
                }
                gHudAudioReset = TRUE;
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
    u8 prevSprite;
    if (racer->playerIndex == PLAYER_COMPUTER ||
        (((gHUDNumPlayers < TWO_PLAYERS || D_800E2794[gHUDNumPlayers][racer->playerIndex] == 2 ||
           gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BANANAS ||
           gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BATTLE) &&
          racer->raceFinished == FALSE) &&
         (gHUDNumPlayers < TWO_PLAYERS || racer->lap < 1 || racer->lap_times[racer->lap] >= 180 ||
          gHudLevelHeader->race_type & RACETYPE_CHALLENGE))) {
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BANANA_COUNT_X]);
        bananas = racer->bananas;
        prevSprite = gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].spriteOffset;
        if (gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].bananaCountIconSpin.spinCounter == 0 &&
            gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].bananaCountIconSpin.visualCounter != racer->bananas) {
            gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].bananaCountIconSpin.spinCounter = 2;
            gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].bananaCountIconSpin.visualCounter = racer->bananas;
        } else if (gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].bananaCountIconSpin.spinCounter) {
            gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].scale = 2.0f;
            prevSprite += updateRate * 13;
            if (prevSprite < (gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].spriteOffset & 0xFF)) {
                gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].bananaCountIconSpin.spinCounter--;
                if (gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].bananaCountIconSpin.spinCounter == 0) {
                    gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].bananaCountSparkle.sparkleCounter = 1;
                    gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].bananaCountSparkle.sparkleTimer = 6;
                    prevSprite = 0;
                    gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].spriteOffset = 1;
                }
            }
        }
        if (prevSprite == 0) {
            sprite_opaque(TRUE);
            set_viewport_tv_type(OS_TV_TYPE_NTSC);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC]);
            set_viewport_tv_type(OS_TV_TYPE_PAL);
            sprite_opaque(FALSE);
            gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].spriteOffset = prevSprite;
            if (gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].bananaCountSparkle.sparkleCounter) {
                gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].bananaCountSparkle.sparkleTimer -= updateRate;
                if (gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].bananaCountSparkle.sparkleTimer < 0) {
                    gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].bananaCountSparkle.sparkleTimer = 6;
                    if (gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].spriteOffset == 6) {
                        gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].spriteOffset = 0;
                        gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].bananaCountSparkle.sparkleCounter--;
                    } else {
                        gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].spriteOffset++;
                    }
                }
                set_viewport_tv_type(OS_TV_TYPE_NTSC);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE]);
                set_viewport_tv_type(OS_TV_TYPE_PAL);
            }
        } else {
            gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].spriteOffset = prevSprite + 128;
            sprite_anim_off(FALSE);
            sprite_opaque(TRUE);
            set_viewport_tv_type(OS_TV_TYPE_NTSC);
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN]);
            sprite_opaque(FALSE);
            set_viewport_tv_type(OS_TV_TYPE_PAL);
            sprite_anim_off(TRUE);
            gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].spriteOffset -= 128;
        }
        temp_lo = bananas / 10;
        if (temp_lo) {
            gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1].spriteOffset = temp_lo;
            gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_2].spriteOffset = bananas % 10;
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_2]);
        } else {
            gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1].spriteOffset = bananas % 10;
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1]);
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    }
}

/**
 * Renders the icons and secured treasure in Smokey's castle.
 * In 4 player, all icons are skipped and in 3 player, player 4's icon is shown on their quadrant.
 */
void render_treasure_hud(Object_Racer *racer) {
    s32 i;
    s32 prevY;

    prevY = gCurrentHud->entry[HUD_TREASURE_METRE].pos.y;
    if (gNumActivePlayers < 3 || (gNumActivePlayers == 3 && racer->playerIndex == PLAYER_COMPUTER)) {
        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].spriteID = racer->characterId + HUD_SPRITE_PORTRAIT;
        D_80126CD5 = TRUE;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT]);
        D_80126CD5 = FALSE;
    }
    for (i = 0; i < 10; i++) {
        if (i >= racer->lap) {
            gHudColour = COLOUR_RGBA32(128, 128, 128, 128);
        }
        D_80126CD5 = TRUE;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_TREASURE_METRE]);
        D_80126CD5 = FALSE;
        gCurrentHud->entry[HUD_TREASURE_METRE].pos.y -= 3.0f;
    }
    gCurrentHud->entry[HUD_TREASURE_METRE].pos.y = prevY;
    gHudColour = COLOUR_RGBA32(255, 255, 255, 254);
    D_80126CD5 = FALSE;
}

/**
 * Render the silver coin counter on the side of the screen.
 * When the 8th coin is collected, wait half a second then play an encouraging voice clip from T.T.
 */
void render_silver_coin_counter(Object_Racer *racer, s32 updateRate) {
    s32 i;
    s32 prevY;

    gCurrentHud->entry[HUD_SILVER_COIN_TALLY].pos.y = (s32) gCurrentHud->entry[HUD_SILVER_COIN_TALLY].pos.y; // Rounds float down to it's int value.
    prevY = gCurrentHud->entry[HUD_SILVER_COIN_TALLY].pos.y;
    for (i = 0; i < 8; i++) {
        if (i >= racer->silverCoinCount) {
            gHudColour = COLOUR_RGBA32(128, 128, 128, 128);
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_SILVER_COIN_TALLY]);
        gCurrentHud->entry[HUD_SILVER_COIN_TALLY].pos.y -= gCurrentHud->entry[HUD_SILVER_COIN_TALLY].silverCoinTally.offsetY;
    }
    if (racer->silverCoinCount == 8) {
        if (gCurrentHud->entry[HUD_SILVER_COIN_TALLY].silverCoinTally.soundTimer < 30) {
            gCurrentHud->entry[HUD_SILVER_COIN_TALLY].silverCoinTally.soundTimer += updateRate;
        }
        if (gCurrentHud->entry[HUD_SILVER_COIN_TALLY].silverCoinTally.soundPlayed == FALSE) {
            if (gCurrentHud->entry[HUD_SILVER_COIN_TALLY].silverCoinTally.soundTimer >= 30) {
                gCurrentHud->entry[HUD_SILVER_COIN_TALLY].silverCoinTally.soundPlayed = TRUE;
                if (gHUDVoiceSoundMask == NULL) {
                    sound_play(SOUND_VOICE_TT_GO_FOR_IT, &gHUDVoiceSoundMask);
                }
            }
        }
    }
    gCurrentHud->entry[HUD_SILVER_COIN_TALLY].pos.y = prevY;
    gHudColour = COLOUR_RGBA32(255, 255, 255, 254);
}

/**
 * Plays the race finish fanfare and displays what position you finished
 * in the middle of the screen.
 * Uses a 3 step process to play the sounds, display the position, then slide it offscreen.
 */
void render_race_finish_position(Object_Racer *racer, s32 updateRate) {
    HudElement *position1;
    HudElement *position2;
    s8 drawPosition;

    position1 = &gCurrentHud->entry[HUD_RACE_FINISH_POS_1];
    position2 = &gCurrentHud->entry[HUD_RACE_FINISH_POS_2];
    drawPosition = FALSE;
    switch (position1->raceFinishPos.status) {
        case HUD_RACEFINISH_MUTE:
            music_voicelimit_set(24);
            music_play(SEQUENCE_FIRST_PLACE);
            sound_play(SOUND_WHOOSH1, NULL);
            sound_play(SOUND_VOICE_TT_FINISH, &gHUDVoiceSoundMask);
            gHudAudioData[0].volume = 127;
            gHudAudioData[0].volumeRamp = 0;
            gHudAudioData[0].playerIndex = racer->playerIndex;
            position1->raceFinishPos.status = HUD_RACEFINISH_TEXT_IN;
            break;
        case HUD_RACEFINISH_TEXT_IN:
            position1->pos.x += updateRate * 13;
            if (position1->pos.x > -23.0f) {
                position1->pos.x = -23.0f;
            }
            position2->pos.x -= updateRate * 13;
            if (position2->pos.x < 22.0f) {
                position2->pos.x = 22.0f;
            }
            drawPosition = TRUE;
            if (position2->pos.x == 22.0f) {
                position1->raceFinishPos.textOutTimer += updateRate;
                if (position1->raceFinishPos.textOutTimer >= 120) {
                    position1->raceFinishPos.textOutTimer = -120;
                    position1->raceFinishPos.textOutTicks++;
                }
                if (position1->raceFinishPos.textOutTicks == 2) {
                    position1->raceFinishPos.status = HUD_RACEFINISH_TEXT_OUT;
                    sound_play(SOUND_WHOOSH1, NULL);
                    if (gHudAudioData[0].playerIndex == racer->playerIndex) {
                        gHudAudioData[0].volumeRamp = -1;
                    }
                }
            }
            break;
        case HUD_RACEFINISH_TEXT_OUT:
            position1->pos.x += updateRate * 13;
            position2->pos.x += updateRate * 13;
            drawPosition = TRUE;
            if (position1->pos.x > 200.0f) {
                position1->raceFinishPos.status = HUD_RACEFINISH_IDLE;
            }
            break;
        case HUD_RACEFINISH_IDLE:
            position1->raceFinishPos.status = HUD_RACEFINISH_IDLE;
            break;
    }
    if (drawPosition) {
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 210);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, position1);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, position2);
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
    }
}

UNUSED void func_800A4C34(UNUSED s32 countdown, UNUSED Object_Racer *racer, UNUSED s32 updateRate) {
}

/**
 * Render the current race position of the racer.
 * Scales up and down when the position changes.
 */
void render_race_position(Object_Racer *racer, s32 updateRate) {
    s32 place;
    f32 prevPos;
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
            gCurrentHud->entry[HUD_RACE_POSITION].spriteOffset = place;
            place++;
        }
    }
    if (gHUDNumPlayers < 2) {
        // P1 and P2 have different endings to P3 onward, so offset the sprite ID based on current position.
        if (place < 4) {
            gCurrentHud->entry[HUD_RACE_POSITION_END].spriteOffset = place - 1;
        } else {
            gCurrentHud->entry[HUD_RACE_POSITION_END].spriteOffset = 3;
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_RACE_POSITION_END]);
    }
    scale = (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter + 129);
    scale *= 128.0f;
    scale = sins_f(scale);
    placeIndex = place - 1;
    gCurrentHud->entry[HUD_RACE_POSITION].scale = (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.baseScale / 127.0f) + (1.0 + (0.5 * scale));
    prevPos = gCurrentHud->entry[HUD_RACE_POSITION].pos.x;
    gCurrentHud->entry[HUD_RACE_POSITION].pos.x -= (24.0f * gCurrentHud->entry[HUD_RACE_POSITION].scale);
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_RACE_POSITION]);
    gCurrentHud->entry[HUD_RACE_POSITION].pos.x = prevPos;
    if (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.active) {
        if (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter < 127 - (updateRate * 16)) {
            gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter += (updateRate * 16);
        } else {
            gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter = 127;
        }
    }
    if (placeIndex != gCurrentHud->entry[HUD_RACE_POSITION].spriteOffset) {
        if (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.active && gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter > 0) {
            gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter = -gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter;
        } else {
            gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter = -127;
            gCurrentHud->entry[HUD_RACE_POSITION].racePosition.active = TRUE;
        }
    }
    gCurrentHud->entry[HUD_RACE_POSITION].spriteOffset = placeIndex;
    if (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.active && gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter == 127) {
        gCurrentHud->entry[HUD_RACE_POSITION].racePosition.active = FALSE;
    }
}

/**
 * Displays the current lap number onscreen.
 * Also displays the "Lap 2" and "Final Lap" messages when the line is crossed.
 * In multiplayer, shows a cut down display, if the display setting is set to show laps.
 */
void render_lap_count(Object_Racer *racer, s32 updateRate) {
    if (racer->raceFinished == FALSE &&
        (gHUDNumPlayers <= ONE_PLAYER || racer->lap <= 0 || racer->lap_times[racer->lap] >= 180) &&
        (gHUDNumPlayers <= ONE_PLAYER || D_800E2794[gHUDNumPlayers][racer->playerIndex] == 3)) {
        if (gHudLevelHeader->laps == (0, racer->countLap + 1) && gHUDNumPlayers < THREE_PLAYERS) {
            gCurrentHud->entry[HUD_LAP_COUNT_FLAG].lapCountFlag.visualCounter += updateRate;
            if (gCurrentHud->entry[HUD_LAP_COUNT_FLAG].lapCountFlag.visualCounter > 6) {
                gCurrentHud->entry[HUD_LAP_COUNT_FLAG].spriteOffset++;
                gCurrentHud->entry[HUD_LAP_COUNT_FLAG].lapCountFlag.visualCounter -= 6;
                if (gCurrentHud->entry[HUD_LAP_COUNT_FLAG].spriteOffset > 4) {
                    gCurrentHud->entry[HUD_LAP_COUNT_FLAG].spriteOffset = 0;
                }
            }
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_LAP_COUNT_FLAG]);
        }
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_LAP_COUNT_LABEL]);
        if (racer->countLap >= gHudLevelHeader->laps - 1) {
            gCurrentHud->entry[HUD_LAP_COUNT_CURRENT].spriteOffset = gHudLevelHeader->laps;
        } else {
            gCurrentHud->entry[HUD_LAP_COUNT_CURRENT].spriteOffset = racer->countLap + 1;
        }
        gCurrentHud->entry[HUD_LAP_COUNT_TOTAL].spriteOffset = gHudLevelHeader->laps;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_LAP_COUNT_CURRENT]);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_LAP_COUNT_SEPERATOR]);
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_LAP_COUNT_TOTAL]);
    }
    if (gHUDNumPlayers == TWO_PLAYERS) {
        sprite_opaque(TRUE);
    }
    if (is_game_paused() == FALSE) {
        if (racer->lap_times[racer->lap] < 30 && gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.status == LAPTEXT_IDLE && racer->raceFinished == FALSE) {
            if (racer->lap == 1 && gHudLevelHeader->laps >= 3) {
                gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.status = LAPTEXT_UNK2;
                gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.direction = LAPTEXT_OUT;
                gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.soundPlayed = FALSE;
                sound_play(SOUND_WHOOSH1, NULL);
                switch (gHUDNumPlayers) {
                    case ONE_PLAYER:
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos = -21;
                        gCurrentHud->entry[HUD_LAP_TEXT_TWO].lapText.targetPos = 32;
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x = -200.0f;
                        gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x = 211.0f;
                        break;
                    case TWO_PLAYERS:
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos = -16;
                        gCurrentHud->entry[HUD_LAP_TEXT_TWO].lapText.targetPos = 27;
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x = -200.0f;
                        gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x = 211.0f;
                        break;
                    default:
                        if (racer->playerIndex != PLAYER_ONE && racer->playerIndex != PLAYER_THREE) {
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos = 60;
                            gCurrentHud->entry[HUD_LAP_TEXT_TWO].lapText.targetPos = 91;
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x = -70.0f;
                            gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x = 221.0f;
                        } else {
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos = -90;
                            gCurrentHud->entry[HUD_LAP_TEXT_TWO].lapText.targetPos = -59;
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x = -220.0f;
                            gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x = 71.0f;
                        }
                        break;
                }
            } else if (gHudLevelHeader->laps == (0, racer->lap + 1) && racer->lap != 0) {
                gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.status = LAPTEXT_UNK3;
                gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.direction = LAPTEXT_IN;
                gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.soundPlayed = FALSE;
                sound_play(SOUND_WHOOSH1, NULL);
                switch (gHUDNumPlayers) {
                    case ONE_PLAYER:
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos = 51;
                        gCurrentHud->entry[HUD_LAP_TEXT_FINAL].lapText.targetPos = -41;
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x = 210.0f;
                        gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x = -200.0f;
                        break;
                    case TWO_PLAYERS:
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos = 41;
                        gCurrentHud->entry[HUD_LAP_TEXT_FINAL].lapText.targetPos = -31;
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x = 210.0f;
                        gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x = -200.0f;
                        break;
                    default:
                        if (racer->playerIndex != PLAYER_ONE && racer->playerIndex != PLAYER_THREE) {
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos = 100;
                            gCurrentHud->entry[HUD_LAP_TEXT_FINAL].lapText.targetPos = 50;
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x = 100.0f;
                            gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x = -50.0f;
                        } else {
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos = -50;
                            gCurrentHud->entry[HUD_LAP_TEXT_FINAL].lapText.targetPos = -100;
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x = 50.0f;
                            gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x = -200.0f;
                        }
                        break;
                }
            }
        }
        if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.status != LAPTEXT_IDLE) {
            if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.status == LAPTEXT_UNK2) {
                if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.direction == LAPTEXT_OUT) {
                    if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x < gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos - (updateRate * 13)) {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x += updateRate * 13;
                    } else {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x = gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos;
                    }
                    if (gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x > gCurrentHud->entry[HUD_LAP_TEXT_TWO].lapText.targetPos + (updateRate * 13)) {
                        gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x -= updateRate * 13;
                    } else {
                        gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x = gCurrentHud->entry[HUD_LAP_TEXT_TWO].lapText.targetPos;
                    }
                    if (racer->lap_times[racer->lap] >= 60) {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.direction = LAPTEXT_IN;
                        sound_play(SOUND_WHOOSH1, NULL);
                    }
                    if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x == gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos &&
                        gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x == gCurrentHud->entry[HUD_LAP_TEXT_TWO].lapText.targetPos &&
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.soundPlayed == FALSE) {
                        if (gHUDVoiceSoundMask == NULL) {
                            sound_play(SOUND_VOICE_TT_LAP2, &gHUDVoiceSoundMask);
                        }
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.soundPlayed = TRUE;
                    }
                } else if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.direction == LAPTEXT_IN) {
                    gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x -= updateRate * 13;
                    gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x += updateRate * 13;
                    if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x < -200.0f) {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.status = LAPTEXT_IDLE;
                    }
                }
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_LAP_TEXT_TWO]);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_LAP_TEXT_LAP]); // lap
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            } else if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.status == LAPTEXT_UNK3) {
                if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.direction == LAPTEXT_IN) {
                    if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x > gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos + (updateRate * 13)) {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x -= updateRate * 13;
                    } else {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x = gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos;
                    }
                    if (gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x < gCurrentHud->entry[HUD_LAP_TEXT_FINAL].lapText.targetPos - (updateRate * 13)) {
                        gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x += updateRate * 13;
                    } else {
                        gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x = gCurrentHud->entry[HUD_LAP_TEXT_FINAL].lapText.targetPos;
                    }
                    if (racer->lap_times[racer->lap] >= 60) {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.direction = LAPTEXT_OUT;
                        sound_play(SOUND_WHOOSH1, NULL);
                    }
                    if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x == gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos &&
                        gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x == gCurrentHud->entry[HUD_LAP_TEXT_FINAL].lapText.targetPos &&
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.soundPlayed == FALSE) {
                        if (gHUDVoiceSoundMask == NULL) {
                            sound_play(SOUND_VOICE_TT_FINAL_LAP, &gHUDVoiceSoundMask);
                        }
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.soundPlayed = TRUE;
                    }
                } else if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.direction == LAPTEXT_OUT) {
                    gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x += updateRate * 13;
                    gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x -= updateRate * 13;
                    if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x > 200.0f) {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.status = LAPTEXT_IDLE;
                    }
                }

                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_LAP_TEXT_FINAL]);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_LAP_TEXT_LAP]);
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
    if (obj->wrongWayCounter > 120 && (gHUDNumPlayers || gCurrentHud->entry[HUD_WRONGWAY_1].pos.x == gCurrentHud->entry[HUD_WRONGWAY_1].lapText.targetPos) &&
        !is_game_paused()) {
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
    if (gCurrentHud->entry[HUD_WRONGWAY_1].lapText.status != WRONGWAY_HIDE) {
        if (gCurrentHud->entry[HUD_WRONGWAY_1].lapText.status == WRONGWAY_SHOW) {
            if (gCurrentHud->entry[HUD_WRONGWAY_1].lapText.direction == WRONGWAY_IN) {
                textMoveSpeed = updateRate * 13;
                gCurrentHud->entry[HUD_WRONGWAY_1].pos.x += textMoveSpeed;
                textPosTarget = gCurrentHud->entry[HUD_WRONGWAY_1].lapText.targetPos;
                if (gCurrentHud->entry[HUD_WRONGWAY_1].pos.x > textPosTarget) {
                    gCurrentHud->entry[HUD_WRONGWAY_1].pos.x = textPosTarget;
                }
                gCurrentHud->entry[HUD_WRONGWAY_2].pos.x -= textMoveSpeed;
                textPosTarget = gCurrentHud->entry[HUD_WRONGWAY_2].lapText.targetPos;
                if (gCurrentHud->entry[HUD_WRONGWAY_2].pos.x < textPosTarget) {
                    gCurrentHud->entry[HUD_WRONGWAY_2].pos.x = textPosTarget;
                }
                if (obj->wrongWayCounter <= 90) {
                    gCurrentHud->entry[HUD_WRONGWAY_1].lapText.direction = WRONGWAY_OUT;
                    sound_play(SOUND_WHOOSH1, NULL);
                }
            } else if (gCurrentHud->entry[HUD_WRONGWAY_1].lapText.direction == WRONGWAY_OUT) {
                textMoveSpeed = updateRate * 13;
                gCurrentHud->entry[HUD_WRONGWAY_1].pos.x -= textMoveSpeed;
                gCurrentHud->entry[HUD_WRONGWAY_2].pos.x += textMoveSpeed;
                if (gCurrentHud->entry[HUD_WRONGWAY_1].pos.x < -200.0f) {
                    gCurrentHud->entry[HUD_WRONGWAY_1].lapText.status = WRONGWAY_HIDE;
                }
            }
            if (!is_game_paused()) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_WRONGWAY_1]);
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_WRONGWAY_2]);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        }
    } else if (obj->wrongWayCounter > 120) {
        gCurrentHud->entry[HUD_WRONGWAY_1].lapText.status = WRONGWAY_SHOW;
        gCurrentHud->entry[HUD_WRONGWAY_1].lapText.direction = WRONGWAY_IN;
        gCurrentHud->entry[HUD_WRONGWAY_1].lapText.targetPos = -31;
        gCurrentHud->entry[HUD_WRONGWAY_2].lapText.targetPos = 52;
        gCurrentHud->entry[HUD_WRONGWAY_1].lapText.soundPlayed = FALSE;
        if (gHUDNumPlayers == TWO_PLAYERS) {
            gCurrentHud->entry[HUD_WRONGWAY_1].lapText.targetPos = -21;
            gCurrentHud->entry[HUD_WRONGWAY_2].lapText.targetPos = 42;
        } else if (gHUDNumPlayers > TWO_PLAYERS) {
            if (obj->playerIndex == PLAYER_ONE || obj->playerIndex == PLAYER_THREE) {
                gCurrentHud->entry[HUD_WRONGWAY_1].lapText.targetPos = -100;
                gCurrentHud->entry[HUD_WRONGWAY_2].lapText.targetPos = -55;
            } else {
                gCurrentHud->entry[HUD_WRONGWAY_1].lapText.targetPos = 59;
                gCurrentHud->entry[HUD_WRONGWAY_2].lapText.targetPos = 104;
            }
        }
        gCurrentHud->entry[HUD_WRONGWAY_2].pos.x = gCurrentHud->entry[HUD_WRONGWAY_2].lapText.targetPos + 200;
        gCurrentHud->entry[HUD_WRONGWAY_1].pos.x = gCurrentHud->entry[HUD_WRONGWAY_2].lapText.targetPos - 200;
        sound_play(SOUND_WHOOSH1, NULL);
    }
    sprite_opaque(FALSE);
}

/**
 * Render race result for multiplayer races or battles after that player has finished.
 * Displays the finish position, and in races, will display the race time.
 */
void hud_draw_finish_misc(Object_Racer *racer) {
    s32 racerCount;
#if VERSION == VERSION_80
    static char sDidNotFinish[] = "DID NOT FINISH";
#define DID_NOT_FINISH &sDidNotFinish
#define FINISH_TEXT_OFFSET 40
#define FINISH_TIME_OFFSET 0
#elif VERSION == VERSION_79
    static char sDidNotFinish[] = { 0x80, 0xEB, 0x80, 0xB9, 0x80, 0xD1, 0x80, 0xB9,
                                    0x80, 0xF3, 0x80, 0xC5, 0x80, 0xC9, 0x80, 0x34 };
#define DID_NOT_FINISH &sDidNotFinish
#define FINISH_TEXT_OFFSET 48
#define FINISH_TIME_OFFSET 2
#else
#define DID_NOT_FINISH "DID NOT FINISH"
#define FINISH_TEXT_OFFSET 40
#define FINISH_TIME_OFFSET 0
#endif

    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1]);
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_2]);
    if (!(get_current_level_race_type() & RACETYPE_CHALLENGE_BATTLE) && (!is_in_two_player_adventure())) {
        get_racer_objects(&racerCount);
        if (gNumActivePlayers >= 2 &&
            (is_in_two_player_adventure() == FALSE || is_postrace_viewport_active() == FALSE)) {
            set_text_font(FONT_COLOURFUL);
            if (racerCount != racer->finishPosition) {
                set_text_colour(255, 255, 255, 0, 255);
                draw_text(&gHUDCurrDisplayList, gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x - FINISH_TEXT_OFFSET,
                          gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y, "RACE", ALIGN_TOP_LEFT);
                render_timer(gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x + FINISH_TIME_OFFSET, gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y,
                             gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.minutes, gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.seconds,
                             gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.hundredths, 1);
                draw_text(&gHUDCurrDisplayList, gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x - FINISH_TEXT_OFFSET,
                          gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.y, "LAP", ALIGN_TOP_LEFT);
                render_timer(gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x + FINISH_TIME_OFFSET, gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.y,
                             gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.minutes, gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.seconds,
                             gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.hundredths, 1);
            } else {
                draw_text(&gHUDCurrDisplayList, gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x - 35, gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y,
                          DID_NOT_FINISH, ALIGN_TOP_LEFT);
            }
        }
    }
}

#ifdef NON_MATCHING
// hud_render_finish
void func_800A6254(Object_Racer *racer, s32 updateRate) {
    UNUSED s32 *var_a0;
    UNUSED s32 var_t0;
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
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].pos.y -= 108.0f;
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_2].pos.y -= 108.0f;
            gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y -= 108.0f;
            gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.y -= 108.0f;
        }
        gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].pos.y += 35.0f;
        gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_2].pos.y += 35.0f;
        gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y += 35.0f;
        gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.y += 35.0f;
        gHudAudioData[0].playerIndex = racer->playerIndex;
        D_80127189 = 1;
    }

    switch (gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.status) {
        case 0:
            if (!(raceType & RACETYPE_CHALLENGE_BATTLE)) {
                gHudAudioData[0].volume = 127;
                gHudAudioData[0].volumeRamp = 0;
                gHudAudioData[0].playerIndex = racer->playerIndex;
                sound_play(SOUND_WHOOSH1, NULL);
            }
            switch (gHUDNumPlayers) {
                case 0:
                case 1:
                    gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.targetPos = -20;
                    gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.unk1D = -15;
                    gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.unk1D = -15;
                    break;
                default:
                    if (racer->playerIndex == PLAYER_ONE || racer->playerIndex == PLAYER_THREE) {
                        gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.targetPos = -90;
                        gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.unk1D = -85;
                        gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.unk1D = -85;
                    } else {
                        gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.targetPos = 55;
                        gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.unk1D = 60;
                        gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.unk1D = 60;
                    }
                    break;
            }
            if (osTvType == OS_TV_TYPE_PAL) {
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.targetPos -= 4;
                gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.unk1D -= 4;
                gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.unk1D -= 4;
            }
            if (racer->finishPosition < 4) {
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_2].spriteOffset = racer->finishPosition - 1;
            } else {
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_2].spriteOffset = 3;
            }
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].spriteOffset = racer->finishPosition - 1;
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.status = 1;
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
                    if (osTvType == OS_TV_TYPE_PAL) {
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
                    gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x = var_f12;
                    gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y = var_f0;
                    gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x = var_f14;
                    gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.y = var_f2;
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
                    if (osTvType == OS_TV_TYPE_PAL) {
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
                    gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x = var_f12;
                    gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y = var_f0;
                    gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x = var_f14;
                    gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.y = var_f2;
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
                gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.minutes = minutes;
                gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.seconds = seconds;
                gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.hundredths = hundredths;
                get_timestamp_from_frames(totalRaceTime, &minutes, &seconds, &hundredths);
                gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.minutes = minutes;
                gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.seconds = seconds;
                gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.hundredths = hundredths;
            }
            break;
        case 1:
            var_a2 = TRUE;
            if (gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].pos.x <
                (gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.targetPos - (updateRate * 13)) + 160) {
                var_v1 = (updateRate * 13);
                var_a2 = FALSE;
            } else {
                var_v1 = (gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.targetPos + 160) - gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].pos.x;
            }
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].pos.x += var_v1;
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_2].pos.x += var_v1;
            if (gNumActivePlayers != 1) {
                if ((gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.unk1D + (updateRate * 13) + 160) < gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x) {
                    var_a2 = FALSE;
                } else {
                    var_v1 = gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x - (gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.unk1D + 160);
                }
                gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x -= var_v1;
                if (gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x < (gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.unk1D - var_v1) + 160) {
                    var_a2 = FALSE;
                } else {
                    var_v1 = (gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.unk1D + 160) - gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x;
                }
                gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x += var_v1;
            }
            temp_v0_4 = 2; // fakematch?
            if (var_a2) {
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.status = temp_v0_4; // fakematch? Why not just set directly to 2?
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.textOutTimer = -120;
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.textOutTicks = 0;
                if (gHUDVoiceSoundMask == NULL) {
                    if (raceType == RACETYPE_CHALLENGE_BATTLE) {
                        switch (racer->finishPosition) {
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
                    } else if (timetrial_ghost_staff() == NULL) {
                        play_time_trial_end_message(&racer->playerIndex);
                    }
                }
            }
            hud_draw_finish_misc(racer);
            break;
        case 2:
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.textOutTimer += updateRate;

            if (gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.textOutTimer >= 120) {
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.textOutTimer = -120;
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.textOutTicks++;
            }
            if (gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.textOutTicks == 2) {
                if (gNumActivePlayers == 1 || is_in_two_player_adventure()) {
                    gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.status = 3;
                    sound_play(SOUND_WHOOSH1, NULL);
                } else {
                    gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.status = 4;
                }
            }
            hud_draw_finish_misc(racer);
            break;
        case 3:
            if (raceType == RACETYPE_CHALLENGE_BATTLE) {
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.status = 4;
            } else {
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].pos.x -= (updateRate * 13);
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_2].pos.x -= (updateRate * 13);
                if (gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].pos.x < -200.0f) {
                    gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.status = 4;
                }
                gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x += (updateRate * 13);
                gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x += (updateRate * 13);
            }
            hud_draw_finish_misc(racer);
            break;
        case 4:
            if (racer->playerIndex == gHudAudioData[0].playerIndex) {
                gHudAudioData[0].volumeRamp = -1;
            }
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.status = 5;
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.textOutTimer = 0;
            hud_draw_finish_misc(racer);
            break;
        default:
            hud_draw_finish_misc(racer);
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_ui/func_800A6254.s")
#endif

/**
 * Play the normal race finish message, unless you beat your time record,
 * then T.T will say "Race Record" instead.
 */
void play_time_trial_end_message(s16 *playerID) {
    Settings *settings = get_settings();

    if (playerID != NULL) {
#if VERSION >= VERSION_79
        if (settings->racers[*playerID].best_times & 0x80 && (get_current_level_race_type() == RACETYPE_DEFAULT)) {
#else
        if (settings->racers[*playerID].best_times & 0x80) {
#endif

            sound_play(SOUND_VOICE_TT_RACE_RECORD, &gHUDVoiceSoundMask);
        } else {
            sound_play(SOUND_VOICE_TT_FINISH, &gHUDVoiceSoundMask);
        }
    }
}

/**
 * Render the finishing overlay after a time trial.
 * Has measures for multiplayer, depsite time trial being a single player exclusive mode.
 */
void render_time_trial_finish(Object_Racer *racer, s32 updateRate) {
    s32 temp;

    switch (gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.status) {
        case TIMETRIAL_FINISH_INIT:
            gHudAudioData[0].volume = 127;
            gHudAudioData[0].volumeRamp = 0;
            gHudAudioData[0].playerIndex = racer->playerIndex;
            sound_play(SOUND_WHOOSH1, NULL);
            if (gHUDNumPlayers == 0 || gHUDNumPlayers == 1) {
                gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x = -200.0f;
                gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos = 0;
            } else {
                if (racer->playerIndex == PLAYER_ONE || racer->playerIndex == PLAYER_THREE) {
                    gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos = -80;
                    gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x = -200.0f;
                } else {
                    gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos = 80;
                    gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x = -40.0f;
                }
            }
            gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.status = TIMETRIAL_FINISH_IN;
            break;
        case TIMETRIAL_FINISH_IN:
            temp = (updateRate * 13);
            if (gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x < gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos - (updateRate * 13)) {
                gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x += updateRate * 13;
            } else {
                gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x = gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos;
                gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.status = TIMETRIAL_FINISH_SHOW;
                gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.fadeTimer = -120;
                if (gHUDVoiceSoundMask == NULL && gHudTimeTrialGhost == FALSE) {
                    play_time_trial_end_message(&racer->playerIndex);
                }
            }
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_RACE_END_FINISH]);
            break;
        case TIMETRIAL_FINISH_SHOW:
            gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.fadeTimer += updateRate;
            if (gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.fadeTimer >= 120) {
                gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.status = TIMETRIAL_FINISH_OUT;
                if (gHUDNumPlayers == PLAYER_ONE || gHUDNumPlayers == PLAYER_TWO) {
                    gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos = 56;
                } else {
                    if (racer->playerIndex == PLAYER_ONE || racer->playerIndex == PLAYER_THREE) {
                        gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos = 56;
                    } else {
                        gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos = -40;
                    }
                }
                sound_play(SOUND_WHOOSH1, NULL);
            }
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_RACE_END_FINISH]);
            break;
        case TIMETRIAL_FINISH_OUT:
            gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x -= updateRate * 13;
            if (gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x < gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos) {
                gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.status = TIMETRIAL_FINISH_IDLE;
            }
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_RACE_END_FINISH]);
            break;
        case TIMETRIAL_FINISH_IDLE:
            gHudAudioData[0].volumeRamp = -1;
            gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.status = TIMETRIAL_FINISH_IDLE_2;
            gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.fadeTimer = 0;
            break;
        default:
            break;
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
    if (osTvType == OS_TV_TYPE_PAL) {
        balloonTickTimer = 646;
    } else {
        balloonTickTimer = 840;
    }
    if (settings->cutsceneFlags & CUTSCENE_ADVENTURE_TWO) {
        gCurrentHud->entry[HUD_BALLOON_COUNT_ICON].spriteID = HUD_SPRITE_BALLOON_DIAMOND; // Use the adventure two balloon sprite.
    }
    if (cutscene_id() == 10 && get_balloon_cutscene_timer() < balloonTickTimer) {
        balloonCount = *settings->balloonsPtr - 1;
    } else {
        balloonCount = *settings->balloonsPtr;
        if (cutscene_id() == 10) {
            if (get_balloon_cutscene_timer() < balloonTickTimer + 8 && D_80126D44 == NULL) {
                sound_play(SOUND_HUD_LAP_TICK, &D_80126D44);
            }
        }
    }
    if (balloonCount < 0) {
        balloonCount = 0;
    }
    div = balloonCount / 10;
    if (div != 0) {
        gCurrentHud->entry[HUD_BALLOON_COUNT_NUMBER_1].spriteOffset = div;
        gCurrentHud->entry[HUD_BALLOON_COUNT_NUMBER_2].spriteOffset = balloonCount % 10;
        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BALLOON_COUNT_NUMBER_2]);
    } else {
        gCurrentHud->entry[HUD_BALLOON_COUNT_NUMBER_1].spriteOffset = balloonCount % 10;
    }
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BALLOON_COUNT_NUMBER_1]);
    set_viewport_tv_type(OS_TV_TYPE_NTSC);
    if (osTvType == OS_TV_TYPE_PAL) {
        sprite_opaque(TRUE);
    }
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BALLOON_COUNT_ICON]);
    sprite_opaque(FALSE);
    set_viewport_tv_type(OS_TV_TYPE_PAL);
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_BALLOON_COUNT_X]);
}

/**
 * Unused function that plays whichever T.T voice line is passed through.
 * Only if the game is currently running and no voice line is already playing.
 */
UNUSED void hud_sound_play(u16 soundId) {
    if (gHUDVoiceSoundMask == NULL && !(is_game_paused())) {
        sound_play(soundId, &gHUDVoiceSoundMask);
    }
}

/**
 * Set the sound ID and delay (in seconds) of the voice clip that will be played.
 */
void hud_sound_play_delayed(u16 soundID, f32 delay, s32 playerIndex) {
    if (gHudVoiceTimer == 0) {
        gHudVoiceID = soundID;
        gHudVoiceTimer = delay * 60.0f;
        gHudVoicePlayerID = playerIndex;
    }
}

/**
 * Stop the queued voice clip from playing from the HUD.
 */
void hud_sound_stop(u16 soundID, s32 playerIndex) {
    if (soundID == gHudVoiceID && gHudVoicePlayerID == playerIndex) {
        gHudVoiceTimer = 0;
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
        set_viewport_tv_type(OS_TV_TYPE_NTSC);
        temp_a0 = (racer->balloon_type * 3) + (racer->balloon_level);
        if (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.prevLevel != racer->balloon_level) {
            if (racer->balloon_level == 0) {
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.scale = 120;
            } else if (gNumActivePlayers == 1) {
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.scale = 0;
            } else {
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.scale = 120;
            }
            gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.prevLevel = racer->balloon_level;
        }
        if (racer->balloon_quantity > 0) {
            if (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation < 16 && racer->unk170 == 0) {
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].rotation.z_rotation = gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation * 0x1000;
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale = (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation * 0.04687) + 0.25;
            } else {
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].rotation.z_rotation = 0;
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale = 1.0f;
            }
            gCurrentHud->entry[HUD_WEAPON_DISPLAY].spriteOffset = temp_a0;
            gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation += updateRate;
            if (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation > 16) {
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation = 16;
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.scale += updateRate;
                if (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.scale > 120) {
                    gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.scale = 120;
                } else if (gHUDNumPlayers == ONE_PLAYER) {
                    gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale +=
                        0.18 * sins_f(((f32) gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.scale * 682.6583 * 4.0));
                }
            }
            if (gHUDNumPlayers > ONE_PLAYER) {
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale *= 0.75;
            }
            if (gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale != 1.0) {
                sprite_opaque(TRUE);
            }
            func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_WEAPON_DISPLAY]);
            sprite_opaque(FALSE);
            if (racer->balloon_quantity > 3) {
                gCurrentHud->entry[HUD_WEAPON_QUANTITY].weaponDisplay.numberFlickerTimer = -128;
            }
            if (racer->balloon_quantity < 3) {
                gCurrentHud->entry[HUD_WEAPON_QUANTITY].weaponDisplay.numberFlickerTimer -= updateRate;
            }
            if (racer->balloon_quantity >= 3 ||
                ((((gCurrentHud->entry[HUD_WEAPON_QUANTITY].weaponDisplay.numberFlickerTimer + 128) % 32) < 20) && racer->balloon_quantity != 1)) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 160);
                gCurrentHud->entry[HUD_WEAPON_QUANTITY].spriteOffset = racer->balloon_quantity - 1;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_WEAPON_QUANTITY]);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
            }
        } else {
            if (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation > 0) {
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].rotation.z_rotation = gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation * 0x1000;
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale = (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation * 0.04687) + 0.25;
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation -= updateRate;
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].spriteOffset = temp_a0;
                if (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation < 0) {
                    gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation = 0;
                }
                if (gHUDNumPlayers != ONE_PLAYER) {
                    gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale /= 2;
                }
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_WEAPON_DISPLAY]);
            }
        }
        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        set_viewport_tv_type(OS_TV_TYPE_PAL);
    }
}

/**
 * If currently using a magnet, render a reticle over the racer that's being targeted.
 */
void render_magnet_reticle(Object *racerObj) {
    unk80068514_arg4 *entry;
    HudElement *hud;
    Object_Racer *racer;

    if (entry) {} // Fakematch
    racer = &racerObj->unk64->racer;
    if (racer->magnetTargetObj != NULL && get_current_viewport() == racer->playerIndex) {
        hud = &gCurrentHud->entry[HUD_MAGNET_RETICLE];
        hud->pos.x = racer->magnetTargetObj->segment.trans.x_position;
        hud->pos.y = racer->magnetTargetObj->segment.trans.y_position;
        hud->pos.z = racer->magnetTargetObj->segment.trans.z_position;
        entry = gAssetHudElements->entry[hud->spriteID];
        if (entry == NULL) {
            return;
        }
        gAssetHudElementStaleCounter[hud->spriteID] = 0;
        func_80066CDC(&gHUDCurrDisplayList, &gHUDCurrMatrix);
        matrix_world_origin(&gHUDCurrDisplayList, &gHUDCurrMatrix);
        render_sprite_billboard(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (Object *) hud, entry,
                                RENDER_Z_UPDATE);
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

    if (!(gHUDNumPlayers != ONE_PLAYER && D_800E2794[gHUDNumPlayers][racer->playerIndex] != 1) ||
        (gHUDNumPlayers > ONE_PLAYER && racer->lap > 0 && racer->lap_times[racer->lap] < 180)) {
        if (racer->raceFinished == FALSE) {
            timerHideCounter = gCurrentHud->entry[HUD_RACE_TIME_LABEL].raceTimeLabel.hideTimer + 127;
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
                gCurrentHud->entry[HUD_RACE_TIME_LABEL].raceTimeLabel.hideTimer = -127;
                timerHideCounter = 0;
            }
            if (gHUDNumPlayers == ONE_PLAYER) {
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_RACE_TIME_LABEL]);
            }
            if (normalise_time(36000) < stopwatchTimer) {
                stopwatchTimer = normalise_time(36000);
            }
            get_timestamp_from_frames(stopwatchTimer, &minutes, &seconds, &hundredths);
            if (countingDown || (normalise_time(36000) == stopwatchTimer)) {
                if ((timerHideCounter > updateRate)) {
                    timerHideCounter -= updateRate;
                } else {
                    timerHideCounter = 0;
                }
                gCurrentHud->entry[HUD_RACE_TIME_LABEL].raceTimeLabel.hideTimer = timerHideCounter - 127;
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
                // This section seems to do nothing of consequense.
                hundredths = gCurrentHud->entry[HUD_RACE_TIME_LABEL].raceTimeLabel.hundredths + ((hundredths / 10) * 10);
                gCurrentHud->entry[HUD_RACE_TIME_LABEL].raceTimeLabel.hundredths++;
                if (gCurrentHud->entry[HUD_RACE_TIME_LABEL].raceTimeLabel.hundredths >= 10) {
                    gCurrentHud->entry[HUD_RACE_TIME_LABEL].raceTimeLabel.hundredths = 0;
                }
            }

            if (gNumActivePlayers == 1) {
                render_timer(gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x, gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y, minutes, seconds, hundredths,
                             FALSE);
            } else {
                render_timer(gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x, gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y, minutes, seconds, hundredths,
                             TRUE);
            }
            gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, 255);
        }
    }
}

/**
 * Render a time in minutes, seconds and hundredths of a second.
 */
void render_timer(s32 x, s32 y, s32 minutes, s32 seconds, s32 hundredths, s32 smallFont) {
    UNUSED s32 pad;
    HudElementBase entry2;
    s32 unk14;
    s32 unk10;
    s32 unkC;
    s32 unk8;
    s32 var_s4;
    s32 unk0;

    entry2.x = x;
    entry2.y = y;
    entry2.z_rotation = 0;
    entry2.x_rotation = 0;
    entry2.y_rotation = 0;
    entry2.scale = 1.0f;
    entry2.z = 0.0f;
    if (!smallFont) {
        unk14 = 11;
        unk10 = 10;
        unkC = 10;
        unk8 = 2;
        var_s4 = HUD_ASSET_9;
        unk0 = HUD_ASSET_11;
    } else {
        unk14 = 10;
        unk10 = 8;
        unkC = 7;
        unk8 = 0;
        var_s4 = HUD_ASSET_10;
        unk0 = HUD_ASSET_12;
    }
    entry2.spriteID = var_s4;
    entry2.spriteOffset = minutes / 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (HudElement *) &entry2);
    entry2.x += unk14;
    entry2.spriteOffset = minutes % 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (HudElement *) &entry2);
    entry2.spriteOffset = 0;
    entry2.x += unk10;
    entry2.y += unk8;
    entry2.spriteID = unk0;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (HudElement *) &entry2);
    entry2.spriteID = var_s4;
    entry2.x += unkC;
    entry2.y -= unk8;
    entry2.spriteOffset = seconds / 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (HudElement *) &entry2);
    entry2.x += unk14;
    entry2.spriteOffset = seconds % 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (HudElement *) &entry2);
    entry2.spriteOffset = 0;
    entry2.x += unk10;
    entry2.y += unk8;
    entry2.spriteID = unk0;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (HudElement *) &entry2);
    entry2.spriteID = var_s4;
    entry2.x += unkC;
    entry2.y -= unk8;
    entry2.spriteOffset = hundredths / 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (HudElement *) &entry2);
    entry2.x += unk14;
    entry2.spriteOffset = hundredths % 10;
    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, (HudElement *) &entry2);
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
    HudElement hudElem;
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
    s32 position2;
    s32 temp_f16;
    s32 temp_f6;
    s32 temp_s3;
    s32 temp;
    UNUSED s32 pad3[4];

    hud_audio_update(updateRate);

    gAssetHudElementStaleCounter[HUD_ELEMENT_UNK_01] = 0;
    gAssetHudElementStaleCounter[HUD_ELEMENT_UNK_17] = 0;
    gAssetHudElementStaleCounter[HUD_ELEMENT_UNK_08] = 0;
    gAssetHudElementStaleCounter[HUD_ELEMENT_UNK_11] = 0;
    D_80127180 = 0;

    if (gMinimapXlu & 2) {
        mapOpacity = 255.0f - ((gMinimapOpacity * 255.0f) / gMinimapOpacityTarget);
    } else {
        mapOpacity = 255;
    }

    for (i = 0; i < gAssetHudElementIdsCount; i++) {
        if (gAssetHudElements->entry[i] && i != 40) {
            if (++gAssetHudElementStaleCounter[i] > 60) {
                if ((gAssetHudElementIds[i] & HUD_ELEMENT_TEXTURE) == HUD_ELEMENT_TEXTURE) {
                    free_texture((TextureHeader *) gAssetHudElements->entry[i]);
                } else if (gAssetHudElementIds[i] & HUD_ELEMENT_SPRITE) {
                    free_sprite((Sprite *) gAssetHudElements->entry[i]);
                } else if (gAssetHudElementIds[i] & HUD_ELEMENT_OBJECT) {
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
            hud_draw_eggs(NULL, updateRate);
            reset_render_settings(&gHUDCurrDisplayList);
        } else {
            // Render player 4's egg challenge portrait if they are AI controlled.
            if (gNumActivePlayers == 3) {
                tempVar4 = NULL;
                for (tempVar2 = 0; tempVar2 < objectCount; tempVar2++) {
                    if (objectGroup[tempVar2]->unk64->racer.playerIndex == PLAYER_COMPUTER) {
                        tempVar4 = &objectGroup[tempVar2]->unk64->racer;
                    }
                }
                if (tempVar4 != NULL) {
                    position2 = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
                    temp_s1 = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
                    spF4 = gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x;
                    spF0 = gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.y;
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x = 225.0f;
                    gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x = 221.0f;
                    gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.y = 197.0f;
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = 165.0f;
                    if (osTvType == OS_TV_TYPE_PAL) {
                        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x -= 4.0f;
                        gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x -= 4.0f;
                        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y *= 1.1;
                        gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.y *= 1.1;
                    }
                    hud_eggs_portrait(tempVar4, updateRate);
                    gHudColour = COLOUR_RGBA32(255, 255, 255, 254);
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x = position2;
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = temp_s1;
                    gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x = spF4;
                    gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.y = spF0;
                }
            }
        }
    } else if (gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BATTLE) {
        // Show life counter and icons in 2 player.
        if (gNumActivePlayers == 2 && gHudToggleSettings[gHUDNumPlayers] == 0) {
            sprite_anim_off(TRUE);
            sprite_opaque(FALSE);
            set_ortho_matrix_view(&gHUDCurrDisplayList, &gHUDCurrMatrix);
            func_800A1E48(0, updateRate);
            sprite_anim_off(FALSE);
            reset_render_settings(&gHUDCurrDisplayList);
            sprite_opaque(TRUE);
        } else {
            // In 3/4 player, just show the life counter.
            if (gNumActivePlayers == 3) {
                curRacerObj = NULL;
                for (tempVar2 = 0; tempVar2 < objectCount; tempVar2++) {
                    if (objectGroup[tempVar2]->unk64->racer.playerIndex == PLAYER_COMPUTER) {
                        curRacerObj = &objectGroup[tempVar2]->unk64->racer;
                    }
                }
                if (curRacerObj != NULL) {
                    gCurrentHud = gPlayerHud[PLAYER_FOUR];
                    spE4 = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
                    spE0 = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
                    sprite_opaque(FALSE);
                    set_ortho_matrix_view(&gHUDCurrDisplayList, &gHUDCurrMatrix);
                    sprite_anim_off(TRUE);
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x = 225.0f;
                    if (osTvType == OS_TV_TYPE_PAL) {
                        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = 181.5f;
                    } else {
                        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = 165.0f;
                    }
                    if (osTvType == OS_TV_TYPE_PAL) {
                        var_a0_5 = (66.0f - gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].pos.x) - 4.0f;
                        temp = -114.0f - gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].pos.y;
                    } else {
                        var_a0_5 = 66.0f - gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].pos.x;
                        temp = -100.0f - gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].pos.y;
                    }
                    gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].pos.x += var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].pos.y += temp;
                    gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].pos.x += var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].pos.y += temp;
                    gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].pos.x += var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].pos.y += temp;
                    gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1].pos.x += var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1].pos.y -= temp + 1;
                    gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_2].pos.x += var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_2].pos.y -= temp + 1;
                    gCurrentHud->entry[HUD_BANANA_COUNT_X].pos.x += var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_X].pos.y -= temp;
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].spriteID = curRacerObj->characterId + HUD_SPRITE_PORTRAIT;
                    if (osTvType == OS_TV_TYPE_PAL) {
                        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x -= 4.0f;
                        gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x -= 4.0f;
                    }
                    D_80126CD5 = TRUE;
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                                  &gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT]);
                    D_80126CD5 = FALSE;
                    if (gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].bananaCountIconSpin.visualCounter == 0 && curRacerObj->bananas == 10) {
                        gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].bananaCountIconSpin.visualCounter = curRacerObj->bananas;
                    }
                    render_racer_bananas(curRacerObj, updateRate);
                    gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].pos.x -= var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].pos.y -= temp;
                    gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].pos.x -= var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].pos.y -= temp;
                    gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].pos.x -= var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].pos.y -= temp;
                    gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1].pos.x -= var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1].pos.y += temp + 1;
                    gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_2].pos.x -= var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_2].pos.y += temp + 1;
                    gCurrentHud->entry[HUD_BANANA_COUNT_X].pos.x -= var_a0_5;
                    gCurrentHud->entry[HUD_BANANA_COUNT_X].pos.y += temp;
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x = spE4;
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = spE0;
                    sprite_opaque(TRUE);
                    reset_render_settings(&gHUDCurrDisplayList);
                    sprite_anim_off(FALSE);
                }
            }
        }
    } else if (gHudLevelHeader->race_type == RACETYPE_CHALLENGE_BANANAS) {
        if (gNumActivePlayers == 2 && gHudToggleSettings[gHUDNumPlayers] == 0) {
            temp_s0_2 = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
            temp_s1_2 = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
            temp_s3 = gCurrentHud->entry[HUD_TREASURE_METRE].pos.x;
            spBC = gCurrentHud->entry[HUD_TREASURE_METRE].pos.y;
            racerGroup = get_racer_objects(&racerCount);
            for (sp144 = 0; sp144 < racerCount; sp144++) {
                someRacer = (Object_Racer *) racerGroup[sp144]->unk64;
                render_treasure_hud(someRacer);
                if (osTvType == OS_TV_TYPE_PAL) {
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y += 66.0;
                    gCurrentHud->entry[HUD_TREASURE_METRE].pos.y += 66.0;
                } else {
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y += 55.0f;
                    gCurrentHud->entry[HUD_TREASURE_METRE].pos.y += 55.0f;
                }
            }
            gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x = temp_s0_2;
            gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = temp_s1_2;
            gCurrentHud->entry[HUD_TREASURE_METRE].pos.x = temp_s3;
            gCurrentHud->entry[HUD_TREASURE_METRE].pos.y = spBC;
        } else if (gNumActivePlayers == 3) {
            tempVar4 = NULL;
            for (tempVar2 = 0; tempVar2 < objectCount; tempVar2++) {
                if (objectGroup[tempVar2]->unk64->racer.playerIndex == PLAYER_COMPUTER) {
                    tempVar4 = &objectGroup[tempVar2]->unk64->racer;
                }
            }
            if (tempVar4 != NULL) {
                temp_s0_3 = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
                temp_s1_3 = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
                temp_f16 = gCurrentHud->entry[HUD_TREASURE_METRE].pos.x;
                temp_f6 = gCurrentHud->entry[HUD_TREASURE_METRE].pos.y;
                gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x = 225.0f;
                gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = 165.0f;
                gCurrentHud->entry[HUD_TREASURE_METRE].pos.x = 209.0f;
                gCurrentHud->entry[HUD_TREASURE_METRE].pos.y = 193.0f;
                if (osTvType == OS_TV_TYPE_PAL) {
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x -= 4.0f;
                    gCurrentHud->entry[HUD_TREASURE_METRE].pos.x -= 4.0f;
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y *= 1.1;
                    gCurrentHud->entry[HUD_TREASURE_METRE].pos.y *= 1.1;
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = (s32) gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
                    gCurrentHud->entry[HUD_TREASURE_METRE].pos.y = (s32) gCurrentHud->entry[HUD_TREASURE_METRE].pos.y;
                }
                render_treasure_hud(tempVar4);
                gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x = temp_s0_3;
                gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = temp_s1_3;
                gCurrentHud->entry[HUD_TREASURE_METRE].pos.x = temp_f16;
                gCurrentHud->entry[HUD_TREASURE_METRE].pos.y = temp_f6;
            }
        }
    }
    if (D_80127180 != 0) {
        gHudSprites[D_80127180].texture = NULL;
        texrect_draw(&gHUDCurrDisplayList, gHudSprites, 0, 0, 255, 255, 255, 255);
    }
    *dList = gHUDCurrDisplayList;
    *mtx = gHUDCurrMatrix;
    *vtx = gHUDCurrVertex;
    if (!(gHudLevelHeader->unkBC & 1)) {
        sp113 = TRUE;
        for (i = 0; i < objectCount; i++) {
            someRacer = (Object_Racer *) objectGroup[i]->unk64;
            if (someRacer != NULL && someRacer->playerIndex != PLAYER_COMPUTER && someRacer->raceFinished == FALSE) {
                sp113 = FALSE;
            }
        }
        if ((gHUDNumPlayers == THREE_PLAYERS && is_postrace_viewport_active()) || check_if_showing_cutscene_camera() ||
            sp113) {
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
            sprite_anim_off(TRUE);
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
                        gMinimapScreenY = -gMinimapDotOffsetY / 2;
                    } else {
                        gMinimapScreenX = (gMinimapDotOffsetX / 2) + 72;
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
            if (osTvType == OS_TV_TYPE_PAL) {
                gMinimapScreenY *= 1.2;
            }
            sprite_opaque(FALSE);
            hudElem.pos.x = gMinimapScreenX + gHudOffsetX + gHudBounceX;
            hudElem.pos.y = gMinimapScreenY;
            if (osTvType == OS_TV_TYPE_PAL) {
                hudElem.pos.x -= 4.0f;
            }
            hudElem.rotation.z_rotation = -someObjSeg->trans.rotation.z_rotation;
            hudElem.rotation.x_rotation = 0;
            if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                hudElem.rotation.y_rotation = -0x8000;
                hudElem.pos.x -= gMinimapDotOffsetX;
            } else {
                hudElem.rotation.y_rotation = 0;
            }
            hudElem.spriteOffset = 0;
            hudElem.pos.z = 0.0f;
            hudElem.scale = 1.0f;
            opacity = mapOpacity;
            if (mapOpacity > 160) {
                mapOpacity = 160;
            }
            if (gNumActivePlayers == 3) {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 255, 255, mapOpacity);
            } else {
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, gMinimapRed, gMinimapGreen, gMinimapBlue, mapOpacity);
            }
            render_ortho_triangle_image(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                                        (ObjectSegment *) &hudElem, minimap, 0);
            sp11C = (lvlMdl->upperXBounds - lvlMdl->lowerXBounds) / (f32) (lvlMdl->upperZBounds - lvlMdl->lowerZBounds);
            sp118 = coss_f((lvlMdl->minimapRotation * 0xFFFF) / 360);
            sp114 = sins_f((lvlMdl->minimapRotation * 0xFFFF) / 360);
            if (is_in_time_trial() && timetrial_valid_player_ghost()) {
                temp_v0_8 = timetrial_player_ghost();
                if (temp_v0_8 != NULL) {
                    minimap_marker_pos(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114,
                                       sp118, sp11C);
                    gCurrentHud->entry[HUD_MINIMAP_MARKER].spriteID = HUD_SPRITE_MAP_DOT;
                    gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation = 0;
                    gCurrentHud->entry[HUD_MINIMAP_MARKER].scale = 1.0f;
                    tempVar1 = (opacity * (f32) temp_v0_8->segment.object.opacity) * (1.0 / 128.0);
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 60, 60, 60, tempVar1);
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_MINIMAP_MARKER]);
                }
            }
            temp_v0_8 = timetrial_ghost_staff();
            if (temp_v0_8 != NULL) {
                minimap_marker_pos(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114,
                                   sp118, sp11C);
                gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation = 0;
                tempVar1 = (opacity * (f32) temp_v0_8->segment.object.opacity) * (1.0 / 128.0);
                gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, gHudMinimapColours[8].red, gHudMinimapColours[8].green,
                                gHudMinimapColours[8].blue, tempVar1);
                gCurrentHud->entry[HUD_MINIMAP_MARKER].scale = 1.0f;
                gCurrentHud->entry[HUD_MINIMAP_MARKER].spriteID = HUD_SPRITE_MAP_DOT;
                func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_MINIMAP_MARKER]);
            }
            // Draw Taj's minimap icon.
            if (gHudLevelHeader->race_type == RACETYPE_HUBWORLD) {
                temp_v0_8 = find_taj_object();
                if (temp_v0_8 != NULL) {
                    gCurrentHud->entry[HUD_MINIMAP_MARKER].spriteID = HUD_SPRITE_MAP_DOT;
                    minimap_marker_pos(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114,
                                       sp118, sp11C);
                    gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation = 0;
                    gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 0, 255, opacity);
                    gCurrentHud->entry[HUD_MINIMAP_MARKER].scale = 1.0f;
                    func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex, &gCurrentHud->entry[HUD_MINIMAP_MARKER]);
                }
            }
            // Draw racer minimap icons.
            // Non AI players get an arrow instead of a blob that rotates.
            for (i = objectCount - 1; i >= 0; i--) {
                temp_v0_8 = objectGroup[i];
                someRacer = (Object_Racer *) objectGroup[i]->unk64;
                if (someRacer != NULL) {
                    minimap_marker_pos(objectGroup[i]->segment.trans.x_position,
                                       objectGroup[i]->segment.trans.z_position, sp114, sp118, sp11C);
                    if (someRacer->playerIndex != PLAYER_COMPUTER) {
                        gCurrentHud->entry[HUD_MINIMAP_MARKER].pos.y -= 1.0f;
                        gCurrentHud->entry[HUD_MINIMAP_MARKER].spriteID = HUD_SPRITE_MAP_ARROW;
                        gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation = (objectGroup[i]->segment.trans.rotation.y_rotation -
                                                                 ((lvlMdl->minimapRotation * 0xFFFF) / 360)) &
                                                                0xFFFF;

                        if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                            gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation = 0xFFFF - gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation;
                        }
                        sprite_opaque(TRUE);
                    } else {
                        gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation = 0;
                        gCurrentHud->entry[HUD_MINIMAP_MARKER].spriteID = HUD_SPRITE_MAP_DOT;
                    }
                    if (is_taj_challenge() && someRacer->vehicleID == VEHICLE_CARPET) {
                        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, 255, 0, 255, opacity);
                    } else {
                        gDPSetPrimColor(gHUDCurrDisplayList++, 0, 0, gHudMinimapColours[someRacer->characterId].red,
                                        gHudMinimapColours[someRacer->characterId].green,
                                        gHudMinimapColours[someRacer->characterId].blue, opacity);
                    }
                    if (!(get_current_level_race_type() & RACETYPE_CHALLENGE) || (!someRacer->raceFinished)) {
                        if (osTvType == OS_TV_TYPE_PAL) {
                            gCurrentHud->entry[HUD_MINIMAP_MARKER].pos.x -= 4.0f;
                        }
                        if (get_current_level_race_type() == RACETYPE_CHALLENGE_BATTLE) {
                            switch (someRacer->elevation) {
                                case ELEVATION_LOW:
                                    gCurrentHud->entry[HUD_MINIMAP_MARKER].scale = 0.8f;
                                    break;
                                case ELEVATION_NORMAL:
                                    gCurrentHud->entry[HUD_MINIMAP_MARKER].scale = 1.0f;
                                    break;
                                case ELEVATION_HIGH:
                                case ELEVATION_HIGHEST:
                                    gCurrentHud->entry[HUD_MINIMAP_MARKER].scale = 1.2f;
                                    break;
                            }
                        } else {
                            gCurrentHud->entry[HUD_MINIMAP_MARKER].scale = 1.0f;
                        }
                        func_800AA600(&gHUDCurrDisplayList, &gHUDCurrMatrix, &gHUDCurrVertex,
                                      &gCurrentHud->entry[HUD_MINIMAP_MARKER]);
                    }
                    sprite_opaque(FALSE);
                }
            }
            gDPPipeSync(gHUDCurrDisplayList++);
            sprite_anim_off(FALSE);
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
    LevelModel *lvlMdl;
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
        gCurrentHud->entry[HUD_MINIMAP_MARKER].pos.x = (gMinimapScreenX - ((scaledX * angleCos) + (scaledY * angleSin))) +
                                       lvlMdl->minimapOffsetXAdv2 - gMinimapDotOffsetX;
        gCurrentHud->entry[HUD_MINIMAP_MARKER].pos.y = (lvlMdl->minimapOffsetYAdv2 + gMinimapScreenY) -
                                       ((scaledX * angleSin) - (scaledY * angleCos)) + gMinimapDotOffsetY;
        return;
    }
    // Final x position on minimap
    gCurrentHud->entry[HUD_MINIMAP_MARKER].pos.x = gMinimapScreenX + ((scaledX * angleCos) + (scaledY * angleSin)) +
                                   (f32) lvlMdl->minimapOffsetXAdv1 - gMinimapDotOffsetX;
    // Final y position on minimap
    gCurrentHud->entry[HUD_MINIMAP_MARKER].pos.y = (lvlMdl->minimapOffsetYAdv1 + gMinimapScreenY) -
                                   ((scaledX * angleSin) - (scaledY * angleCos)) + gMinimapDotOffsetY;
}

// hud_draw_element
#pragma GLOBAL_ASM("asm/nonmatchings/game_ui/func_800AA600.s")

/**
 * Renders a 3D model onscreen.
 * Used in conjunction with the HUD.
 */
void hud_draw_model(ObjectModel *objModel) {
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

/**
 * Begin fading the minimap which will slowly set it to whatever the opacity target is.
 * Fades in or out based on what the setting is.
 */
void minimap_fade(s32 setting) {
    gMinimapFade = TRUE;
    gMinimapXlu = setting;
}

/**
 * Snaps the minimap opacity to the target level.
 * Fades in or out based on what the setting is.
 */
void minimap_opacity_set(s32 setting) {
    gMinimapOpacity = gMinimapOpacityTarget;
    gMinimapXlu = setting;
}

/**
 * Sets the race start HUD procedure to the first step.
 */
UNUSED void hud_reset_race_start(void) {
    gRaceStartShowHudStep = 0;
}

/**
 * Sets the visibility of the hud, hiding almost everything, leaving only the minimap.
 */
void hud_visibility(u8 setting) {
    gShowHUD = 1 - setting;
}
