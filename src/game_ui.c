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

UNUSED s32 D_800E1E60 = 0;

// clang-format off
// Base positions of all onscreen hud elements
HudElement gHudElementBase[HUD_ELEMENT_COUNT] = {
    { { { { 0, 0, 0 } } }, HUD_ASSET_0, 1.0f, { { { 53.0f, 16.0f, 0.0f } } }, 0, { { 0, 127, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_3, 1.0f, { { { 54.0f, 18.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_WEAPONS, 0.4f, { { { -120.0f, -68.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_6, 1.0f, { { { 104.0f, 16.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_NUMBERS, 1.0f, { { { 93.0f, 31.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_4, 1.0f, { { { 104.0f, 32.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_NUMBERS, 1.0f, { { { 114.0f, 31.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_BANANA_ANIM, 0.5f, { { { -3.0f, 73.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_NUMBERS, 1.0f, { { { 182.0f, 22.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_NUMBERS, 1.0f, { { { 192.0f, 22.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_13, 1.0f, { { { 239.0f, 16.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_NUMBERS, 1.0f, { { { 206.0f, 31.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_GO_BIG, 1.0f, { { { 0.0f, 30.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_GET_READY, 1.0f, { { { 0.0f, 30.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_FINISH, 1.0f, { { { -200.0f, 30.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_MAP_DOT, 1.0f, { { { 0.0f, 0.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_CHEQUER_FLAG, 1.0f, { { { -50.0f, 87.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_RETICLE, 2.0f, { { { -50.0f, 87.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_18, 1.0f, { { { 167.0f, 22.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_GOLD_BALLOON, 1.0f, { { { -127.0f, 88.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_18, 1.0f, { { { 52.0f, 27.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_NUMBERS, 1.0f, { { { 67.0f, 27.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_NUMBERS, 1.0f, { { { 77.0f, 27.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_NUMBERS, 1.0f, { { { 221.0f, 48.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_6, 1.0f, { { { 188.0f, 48.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_NUMBERS_SMALL, 1.0f, { { { 206.0f, 48.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_20, 0.4f, { { { -105.0f, -98.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_BANANA_STATIC, 0.5f, { { { -3.0f, 73.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_23, 1.0f, { { { -8.0f, 97.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_LAP_FINAL, 1.0f, { { { 0.0f, 30.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_LAP_LAP, 1.0f, { { { 0.0f, 30.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_LAP_2, 1.0f, { { { 0.0f, 30.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_2, 1.0f, { { { 25.0f, 48.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_INDICATOR_TURN_90, 1.0f, { { { -120.0f, 30.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_34, 0.4f, { { { -105.0f, -98.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_WRONG, 1.0f, { { { 0.0f, 30.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_WAY, 1.0f, { { { 0.0f, 30.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_PRO_AM, 1.0f, { { { 80.0f, -60.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } }, // Unused
    { { { { 0, 0, 0x6490 } } }, HUD_SPRITE_SPEEDOMETRE_ARROW, 0.5f, { { { 122.0f, -71.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_47, 0.75f, { { { 247.0f, 212.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_48, 1.0f, { { { 234.0f, 196.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_49, 1.0f, { { { 232.0f, 177.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_50, 1.0f, { { { 240.0f, 159.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_51, 1.0f, { { { 256.0f, 146.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_52, 1.0f, { { { 275.0f, 143.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_53, 1.0f, { { { 246.0f, 156.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_54, 0.7272f, { { { 27.0f, 142.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_0, 1.0f, { { { -200.0f, 70.0f, 0.0f } } }, 0, { { 0, 129, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_3, 1.0f, { { { -175.0f, 72.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_WEAPON_NUMBER, 1.0f, { { { -99.0f, -89.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_PORTRAIT, 0.76f, { { { 43.0f, 20.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_66, 1.0f, { { { 40.0f, 54.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_BANANA_ANIM, 0.375f, { { { -117.0f, 46.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_28, 1.0f, { { { 51.0f, 56.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_NUMBERS_SMALL, 1.0f, { { { 60.0f, 57.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_ASSET_NUMBERS_SMALL, 1.0f, { { { 69.0f, 57.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_PLACE_1, 1.0f, { { { -160.0f, 5.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_PORTRAIT, 1.0f, { { { 260.0f, 16.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
    { { { { 0, 0, 0 } } }, HUD_SPRITE_PLACE_ST, 1.0f, { { { 160.0f, 5.0f, 0.0f } } }, 0, { { 0, 0, 0, 0 } } },
};
// clang-format on

HudPresets2P gHudPresets2P[] = {
    { HUD_RACE_POSITION, 53, 16 },
    { HUD_RACE_POSITION_END, 54, 18 },
    { HUD_LAP_COUNT_CURRENT, 203, 19 },
    { HUD_LAP_COUNT_SEPERATOR, 211, 19 },
    { HUD_LAP_COUNT_TOTAL, 220, 19 },
    { HUD_WEAPON_DISPLAY, -120, -31 },
    { HUD_BANANA_COUNT_ICON_STATIC, 33, 22 },
    { HUD_BANANA_COUNT_NUMBER_1, 211, 19 },
    { HUD_BANANA_COUNT_NUMBER_2, 220, 19 },
    { HUD_RACE_TIME_NUMBER, 167, 19 },
    { HUD_RACE_END_FINISH, 0, 10 },
    { HUD_LAP_COUNT_FLAG, 59, 35 },
    { HUD_MAGNET_RETICLE, 59, 35 },
    { HUD_BANANA_COUNT_ICON_SPIN, 33, 22 },
    { HUD_BANANA_COUNT_SPARKLE, 30, 42 },
    { HUD_BANANA_COUNT_X, 202, 19 },
    { HUD_RACE_START_READY, 0, 10 },
    { HUD_RACE_START_GO, 0, 10 },
    { HUD_WRONGWAY_1, 0, 10 },
    { HUD_WRONGWAY_2, 0, 10 },
    { HUD_LAP_TEXT_LAP, 0, 10 },
    { HUD_LAP_TEXT_TWO, 0, 10 },
    { HUD_LAP_TEXT_FINAL, 0, 10 },
    { HUD_CHALLENGE_FINISH_POS_1, -200, 35 },
    { HUD_CHALLENGE_FINISH_POS_2, -175, 37 },
    { HUD_WEAPON_QUANTITY, -106, -45 },
    { HUD_LAP_COUNT_LABEL, 180, 19 },
    { HUD_CHALLENGE_PORTRAIT, 263, 17 },
    { HUD_TREASURE_METRE, 247, 45 },
    { HUD_EGG_CHALLENGE_ICON, 259, 49 },
    { HUD_SILVER_COIN_TALLY, 34, 71 },
    { -1, -1, -1 },
};

HudPresets4P gHudPresets4P[] = {
    { HUD_RACE_POSITION, 45, 16, 135 },
    { HUD_LAP_COUNT_CURRENT, 94, 19, 78 },
    { HUD_LAP_COUNT_SEPERATOR, 102, 19, 86 },
    { HUD_LAP_COUNT_TOTAL, 111, 19, 95 },
    { HUD_WEAPON_DISPLAY, -47, -36, 36 },
    { HUD_BANANA_COUNT_ICON_STATIC, 0, 22, -29 },
    { HUD_BANANA_COUNT_ICON_SPIN, 0, 22, -29 },
    { HUD_BANANA_COUNT_NUMBER_1, 97, 19, 68 },
    { HUD_BANANA_COUNT_NUMBER_2, 106, 19, 77 },
    { HUD_RACE_TIME_NUMBER, 55, 19, 26 },
    { HUD_RACE_START_GO, 0, 10, 0 },
    { HUD_RACE_START_READY, 0, 10, 0 },
    { HUD_RACE_END_FINISH, -160, 10, -160 },
    { HUD_LAP_COUNT_FLAG, 102, 19, 86 },
    { HUD_MAGNET_RETICLE, 102, 19, 86 },
    { HUD_BANANA_COUNT_X, 88, 19, 59 },
    { HUD_BANANA_COUNT_SPARKLE, -3, 42, -32 },
    { HUD_TREASURE_METRE, 18, 45, 120 },
    { HUD_LAP_TEXT_LAP, -22, 10, -22 },
    { HUD_LAP_TEXT_TWO, 12, 10, 16 },
    { HUD_LAP_TEXT_FINAL, 0, 10, -39 },
    { HUD_WRONGWAY_1, 0, 10, 0 },
    { HUD_WRONGWAY_2, 0, 10, 0 },
    { HUD_CHALLENGE_FINISH_POS_1, -200, 25, -40 },
    { HUD_CHALLENGE_FINISH_POS_2, -175, 27, -15 },
    { HUD_WEAPON_QUANTITY, -33, -50, 50 },
    { HUD_LAP_COUNT_LABEL, 71, 19, 55 },
    { HUD_EGG_CHALLENGE_ICON, 60, 20, 60 },
    { -1, -1, -1, -1 },
};

// Rare likely just used an s16 array for the above data, but we can make it match with a nicer looking struct.
// Small side effect is this padding is required to maintain matching.
UNUSED s32 gPresetPadding = 0;

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
char gHudTimeTrialJp_Ghost[] = { 0x80, 0x80, 0x80, 0x3B, 0x80, 0x5C, 0x80, 0x63, 0x00, 0x00 };

// セーブ  -  Save
char gHudTimeTrialJp_Save[] = { 0x80, 0x5D, 0x80, 0x3B, 0x80, 0x8D };

// ふかのう - Impossible
char gHudTimeTrialJp_Impossible[] = { 0x80, 0xD5, 0x80, 0xBF, 0x80, 0xD2, 0x80, 0xBC, 0x00, 0x00 };

char gHudTimeTrialJp_FullBlank[] = { 0x00, 0x00, 0x00, 0x00 };

// パック  -  Pak
char gHudTimeTrialJp_FullPak[] = { 0x80, 0x90, 0x80, 0x4A, 0x80, 0x57 };

// フル  -  Full
char gHudTimeTrialJp_Full[] = { 0x80, 0x6B, 0x80, 0x78, 0x00, 0x00 };

char gHudTimeTrialJp_DamagedBlank[] = { 0x00, 0x00, 0x00, 0x00 };

// パック  -  Pak
char gHudTimeTrialJp_DamagedPak[] = { 0x80, 0x90, 0x80, 0x4A, 0x80, 0x57 };

// ふりょう  - Defective
char gHudTimeTrialJp_Defective[] = { 0x80, 0xD5, 0x80, 0xE1, 0x80, 0xB7, 0x80, 0xBC, 0x00, 0x00 };
#endif

UNUSED f32 sRecordVel = 0.0f; // Set to whatever the highest velocity recorded is, but never actually used.

UNUSED s32 D_800E283C[] = { 0x06FFFFFF, 0x000FFFFF, 0x06000000, 0x0014FFFF };

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

s8 gHudPALScale;
u8 *gAssetHudElementStaleCounter;
HudData *gCurrentHud;
HudData *gPlayerHud[MAXCONTROLLERS]; // One per active player
s16 *gAssetHudElementIds;
HudElements *gAssetHudElements;
s32 gAssetHudElementIdsCount;
Gfx *gHudDL;
Mtx *gHudMtx;
Vertex *gHudVtx;
s32 gHudCurrentViewport;
s32 gHUDNumPlayers;
s32 gHudController;
s32 D_80126D14;
s32 D_80126D18;
s32 gMinimapDotOffsetX;
s32 gMinimapDotOffsetY;
s32 gHudOffsetX; // Offset value to do the slide in animation.
s32 gHudBounceX; // Offset value to do the bounce when the hud slides in.
u16 gHudBounceTimer;
f32 gHudBounceMag;
u8 gHudRaceStart;
u8 gHudSlide;
u8 gHideRaceTimer;
u8 gNumActivePlayers;
u8 gWrongWayNagPrefix;
AudioPoint *gRaceStartSoundMask;
SoundHandle gHUDVoiceSoundMask;
SoundHandle gHudBalloonSoundMask;
u16 gHudTTSoundID;
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
u8 gStopwatchAnimID;
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
u8 gAdventurePlayerFinish;
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
void hud_init(UNUSED s32 viewportCount) {
    s32 i;
    s32 playerCount;

    gHUDNumPlayers = cam_get_viewport_layout();
    gNumActivePlayers = cam_set_layout(gHUDNumPlayers);
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
        tex_load_sprite(gAssetHudElementIds[HUD_ELEMENT_UNK_01] & 0x3FFF, 1); // ID: 86 - 0x56
    gAssetHudElements->entry[HUD_ELEMENT_UNK_17] =
        tex_load_sprite(gAssetHudElementIds[HUD_ELEMENT_UNK_17] & 0x3FFF, 1); // ID: 291 - 0x123
    gAssetHudElements->entry[HUD_ELEMENT_UNK_08] =
        tex_load_sprite(gAssetHudElementIds[HUD_ELEMENT_UNK_08] & 0x3FFF, 1); // ID: 156 - 0x9C
    gAssetHudElements->entry[HUD_ELEMENT_UNK_11] =
        tex_load_sprite(gAssetHudElementIds[HUD_ELEMENT_UNK_11] & 0x3FFF, 1); // ID: 60 - 0x3C
    if (gNumActivePlayers != 3) {
        playerCount = gNumActivePlayers;
    } else {
        playerCount = 4; // Create four viewports if there are three players.
    }
    gPlayerHud[PLAYER_ONE] = mempool_alloc_safe(playerCount * sizeof(HudData), COLOUR_TAG_BLUE);
    gPlayerHud[PLAYER_TWO] = (HudData *) ((u8 *) gPlayerHud[PLAYER_ONE] + sizeof(HudData));
    gPlayerHud[PLAYER_THREE] = (HudData *) ((u8 *) gPlayerHud[PLAYER_TWO] + sizeof(HudData));
    gPlayerHud[PLAYER_FOUR] = (HudData *) ((u8 *) gPlayerHud[PLAYER_THREE] + sizeof(HudData));
    hud_init_element();
    D_80126D64 = 0;
    gWrongWayNagTimer = 0;
    gHudTTSoundID = SOUND_NONE;
    D_80126D66 = 4;
    D_80126D65 = 0;
    gStopwatchAnimID = 4;
    D_80126D69 = 1;
    D_80126D68 = 1;
    gHudAudioReset = FALSE;
    gHudVoiceID = 0;
    gHudVoiceTimer = 0;
    gRaceStartSoundMask = NULL;
    gHudBalloonSoundMask = NULL;
    gMinimapXlu = 0;
    D_80127194 = (LevelHeader_70 *) get_misc_asset(ASSET_MISC_58);
    func_8007F1E8(D_80127194);
    sndp_set_group_volume(0, AL_SNDP_GROUP_VOLUME_MAX);
    sndp_set_group_volume(2, AL_SNDP_GROUP_VOLUME_MAX);
    for (i = 0; i < 2; i++) {
        gHudAudioData[i].volume = 0;
        gHudAudioData[i].volumeRamp = 0;
        gHudAudioData[i].playerIndex = PLAYER_COMPUTER;
        if (gHudAudioData[i].soundMask) {
            sndp_stop(gHudAudioData[i].soundMask);
        }
    }
}

/**
 * Done on race start, set all the hud elements to their default values.
 * Numerous override cases for different game modes and multiplayer.
 */
void hud_init_element(void) {
    s32 i;
    s32 j;
    s32 activePlayers;
    HudElement *hudElement;
    HudPresets4P *preset4P;
    HudPresets2P *preset2P;
    s32 k;
    s32 temp;

    temp = get_current_level_race_type();
    if (temp == RACETYPE_UNK1 || temp == RACETYPE_HUBWORLD) {
        gHudOffsetX = 0;
        gHudRaceStart = TRUE;
    } else {
        if (gHUDNumPlayers < 2) {
            gHudOffsetX = SCREEN_WIDTH;
            gHudBounceMag = 2.0f;
        } else {
            gHudOffsetX = SCREEN_WIDTH - SCREEN_HEIGHT_HALF;
            gHudBounceMag = 2.0f;
        }
        gHudRaceStart = FALSE;
    }
    gHudBounceTimer = 0;
    gRaceStartShowHudStep = 0;
    gHideRaceTimer = 0;
    gWrongWayNagPrefix = 0;
    gHudSlide = 0;
    gMinimapOpacity = 0;
#if VERSION == VERSION_80
    gMinimapOpacityTarget = osTvType == OS_TV_TYPE_PAL ? 61 : 51;
#else
    gMinimapOpacityTarget = osTvType == OS_TV_TYPE_PAL ? 60 : 50;
#endif
    gMinimapFade = 0;
    gShowHUD = FALSE;
    gHudPALScale = FALSE;
    gAdventurePlayerFinish = FALSE;
    D_80126D4C = -100;
    D_80126D50 = rand_range(120, 360);
    D_8012718A = func_8000E158();
    gStopwatchErrorX = 55;
    gStopwatchErrorY = 179;
    if (osTvType == OS_TV_TYPE_PAL) {
        gStopwatchErrorY += 30;
        gStopwatchErrorX -= 4;
    }
    gHudTimeTrialGhost = timetrial_ghost_staff() == NULL ? FALSE : TRUE;
    activePlayers = gNumActivePlayers != 3 ? gNumActivePlayers : 4;
    for (j = 0; j < activePlayers; j++) {
        gCurrentHud = gPlayerHud[j];
        for (k = 0; k < ARRAY_COUNT(gHudElementBase); k++) {
            gCurrentHud->entry[k].pos.x = gHudElementBase[k].pos.x;
            gCurrentHud->entry[k].pos.y = gHudElementBase[k].pos.y;
            gCurrentHud->entry[k].pos.z = gHudElementBase[k].pos.z;
            gCurrentHud->entry[k].scale = gHudElementBase[k].scale;
            gCurrentHud->entry[k].rotation.z = gHudElementBase[k].rotation.z;
            gCurrentHud->entry[k].rotation.y = gHudElementBase[k].rotation.y;
            gCurrentHud->entry[k].rotation.x = gHudElementBase[k].rotation.x;
            gCurrentHud->entry[k].spriteID = gHudElementBase[k].spriteID;
            gCurrentHud->entry[k].spriteOffset = gHudElementBase[k].spriteOffset;
            gCurrentHud->entry[k].timer.minutes = gHudElementBase[k].timer.minutes;
            gCurrentHud->entry[k].timer.seconds = gHudElementBase[k].timer.seconds;
            gCurrentHud->entry[k].timer.hundredths = gHudElementBase[k].timer.hundredths;
            gCurrentHud->entry[k].timer.unk1D = gHudElementBase[k].timer.unk1D;
        }
        gCurrentHud->entry[HUD_SILVER_COIN_TALLY].silverCoinTally.offsetY = 5;
        if (gHUDNumPlayers == TWO_PLAYERS) {
            for (preset2P = gHudPresets2P; preset2P->assetID != -1; preset2P++) {
                gCurrentHud->entry[preset2P->assetID].pos.x = preset2P->x;
                if ((gAssetHudElementIds[gCurrentHud->entry[preset2P->assetID].spriteID] & ASSET_MASK_TEXTURE) ==
                    ASSET_MASK_TEXTURE) {
                    if (j == PLAYER_ONE) { // Top viewport
                        gCurrentHud->entry[preset2P->assetID].pos.y = preset2P->y;
                    } else { // Bottom viewport
                        gCurrentHud->entry[preset2P->assetID].pos.y = preset2P->y + 108;
                    }
                } else if (j == PLAYER_ONE) { // Top viewport
                    gCurrentHud->entry[preset2P->assetID].pos.y = preset2P->y + 60;
                } else { // Bottom viewport
                    gCurrentHud->entry[preset2P->assetID].pos.y = preset2P->y - 48;
                }
            }
            gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x = 263.0f;
            gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = 17.0f;
            gCurrentHud->entry[HUD_TREASURE_METRE].pos.x = 247.0f;
            gCurrentHud->entry[HUD_TREASURE_METRE].pos.y = 45.0f;
            gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x = 259.0f;
            gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.y = 49.0f;
            gCurrentHud->entry[HUD_BATTLE_BANANA_ICON].pos.x = 103.0f;
            gCurrentHud->entry[HUD_BATTLE_BANANA_ICON].pos.y = 49.0f;
            gCurrentHud->entry[HUD_BATTLE_BANANA_X].pos.x = 264.0f;
            gCurrentHud->entry[HUD_BATTLE_BANANA_X].pos.y = 50.0f;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.x = 265.0f;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.y = 51.0f;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].pos.x = 274.0f;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].pos.y = 51.0f;
            gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = 17.0f;
            gCurrentHud->entry[HUD_SILVER_COIN_TALLY].silverCoinTally.offsetY = 3;
        } else if (gHUDNumPlayers == THREE_PLAYERS || gHUDNumPlayers == FOUR_PLAYERS) {
            for (preset4P = gHudPresets4P; preset4P->assetID != -1; preset4P++) {
                if ((gAssetHudElementIds[gCurrentHud->entry[preset4P->assetID].spriteID] & ASSET_MASK_TEXTURE) ==
                    ASSET_MASK_TEXTURE) {
                    if (j == PLAYER_ONE || j == PLAYER_THREE) { // Left viewports
                        gCurrentHud->entry[preset4P->assetID].pos.x = preset4P->xLeft;
                    } else { // Right viewports
                        gCurrentHud->entry[preset4P->assetID].pos.x = preset4P->xRight + 160;
                    }
                    if (j == PLAYER_ONE || j == PLAYER_TWO) { // Top viewports
                        gCurrentHud->entry[preset4P->assetID].pos.y = preset4P->y;
                    } else { // Bottom viewports
                        gCurrentHud->entry[preset4P->assetID].pos.y = preset4P->y + 108;
                    }
                } else {
                    if (j == PLAYER_ONE || j == PLAYER_THREE) { // Left viewports
                        gCurrentHud->entry[preset4P->assetID].pos.x = preset4P->xLeft - 80;
                    } else { // Right viewports
                        gCurrentHud->entry[preset4P->assetID].pos.x = preset4P->xRight + 80;
                    }
                    if (j == PLAYER_ONE || j == PLAYER_TWO) { // Top viewports
                        gCurrentHud->entry[preset4P->assetID].pos.y = preset4P->y + 60;
                    } else { // Bottom viewports
                        gCurrentHud->entry[preset4P->assetID].pos.y = preset4P->y - 48;
                    }
                }
            }
        }
        if (gHUDNumPlayers != ONE_PLAYER) {
            for (i = 0; i < HUD_ELEMENT_COUNT; i++) {
                if (gCurrentHud->entry[i].spriteID == HUD_ASSET_NUMBERS) {
                    gCurrentHud->entry[i].spriteID = HUD_ASSET_NUMBERS_SMALL;
                } else if (gCurrentHud->entry[i].spriteID == HUD_ASSET_4) {
                    gCurrentHud->entry[i].spriteID = HUD_ASSET_15;
                } else if (gCurrentHud->entry[i].spriteID == HUD_ASSET_SEPERATOR) {
                    gCurrentHud->entry[i].spriteID = HUD_ASSET_SEPERATOR_SMALL;
                } else if (gCurrentHud->entry[i].spriteID == HUD_ASSET_18) {
                    gCurrentHud->entry[i].spriteID = HUD_ASSET_28;
                } else if (gCurrentHud->entry[i].spriteID == HUD_ASSET_54) {
                    gCurrentHud->entry[i].scale *= 0.6;
                } else if (i != HUD_RACE_POSITION && i != HUD_RACE_POSITION_END && i != HUD_WEAPON_DISPLAY &&
                           i != HUD_PRO_AM_LOGO && i != HUD_CHALLENGE_FINISH_POS_1 && i != HUD_CHALLENGE_FINISH_POS_2 &&
                           i != HUD_LAP_COUNT_LABEL && i != HUD_CHALLENGE_PORTRAIT && i != HUD_EGG_CHALLENGE_ICON &&
                           ((i < HUD_BATTLE_BANANA_ICON || i > HUD_BATTLE_BANANA_COUNT_2) ||
                            i == HUD_BANANA_COUNT_SPARKLE || i == HUD_BANANA_COUNT_NUMBER_2)) {
                    gCurrentHud->entry[i].scale *= 0.75;
                }
            }
        }
        if (gHUDNumPlayers >= THREE_PLAYERS) {
            gCurrentHud->entry[HUD_LAP_TEXT_LAP].scale = 1.0f;
            gCurrentHud->entry[HUD_LAP_TEXT_TWO].scale = 1.0f;
            gCurrentHud->entry[HUD_LAP_TEXT_FINAL].scale = 1.0f;
            gCurrentHud->entry[HUD_RACE_START_GO].scale = 1.0f;
            gCurrentHud->entry[HUD_RACE_START_READY].scale = 1.0f;
            gCurrentHud->entry[HUD_WRONGWAY_1].scale = 1.0f;
            gCurrentHud->entry[HUD_WRONGWAY_2].scale = 1.0f;
            gCurrentHud->entry[HUD_RACE_END_FINISH].scale = 1.0f;
            gCurrentHud->entry[HUD_LAP_TEXT_LAP].spriteID = HUD_SPRITE_LAP_LAP_SMALL;
            gCurrentHud->entry[HUD_LAP_TEXT_TWO].spriteID = HUD_SPRITE_LAP_2_SMALL;
            gCurrentHud->entry[HUD_LAP_TEXT_FINAL].spriteID = HUD_SPRITE_LAP_FINAL_SMALL;
            gCurrentHud->entry[HUD_RACE_START_GO].spriteID = HUD_SPRITE_GO_SMALL;
            gCurrentHud->entry[HUD_RACE_START_READY].spriteID = HUD_SPRITE_GET_READY_SMALL;
            gCurrentHud->entry[HUD_WRONGWAY_1].spriteID = HUD_SPRITE_WRONG_SMALL;
            gCurrentHud->entry[HUD_WRONGWAY_2].spriteID = HUD_SPRITE_WAY_SMALL;
            gCurrentHud->entry[HUD_RACE_END_FINISH].spriteID = HUD_SPRITE_FINISH_SMALL;
        } else {
            gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.prevLevel = 1;
            // while weaponDisplay is not correct union "type" we need the value to be set to be a s8 instead of u8
            gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].weaponDisplay.prevLevel = 1;
        }
        if (is_in_time_trial()) {
            gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].pos.x += -25.0f;
            gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1].pos.x += -25.0f;
            gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_2].pos.x += -25.0f;
            gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].pos.x += -25.0f;
            gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].pos.x += -25.0f;
            gCurrentHud->entry[HUD_BANANA_COUNT_X].pos.x += -25.0f;
            gCurrentHud->entry[HUD_LAP_COUNT_CURRENT].pos.x += -58.0f;
            gCurrentHud->entry[HUD_LAP_COUNT_SEPERATOR].pos.x += -58.0f;
            gCurrentHud->entry[HUD_LAP_COUNT_TOTAL].pos.x += -58.0f;
            gCurrentHud->entry[HUD_LAP_COUNT_LABEL].pos.x += -58.0f;
            gCurrentHud->entry[HUD_LAP_COUNT_FLAG].pos.x += -58.0f;
        }
        switch (get_current_level_race_type()) {
            case RACETYPE_BOSS:
                gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].pos.x += -120.0f;
                gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1].pos.x += -120.0f;
                gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_2].pos.x += -120.0f;
                gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].pos.x += -120.0f;
                gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].pos.x += -120.0f;
                gCurrentHud->entry[HUD_BANANA_COUNT_X].pos.x += -120.0f;
                gCurrentHud->entry[HUD_LAP_COUNT_LABEL].pos.x += 28.0f;
                gCurrentHud->entry[HUD_LAP_COUNT_CURRENT].pos.x += 28.0f;
                gCurrentHud->entry[HUD_LAP_COUNT_SEPERATOR].pos.x += 28.0f;
                gCurrentHud->entry[HUD_LAP_COUNT_TOTAL].pos.x += 28.0f;
                gCurrentHud->entry[HUD_LAP_COUNT_FLAG].pos.x += 28.0f;
                break;
            case RACETYPE_CHALLENGE_BANANAS:
                if (osTvType == OS_TV_TYPE_PAL) {
                    gCurrentHud->entry[HUD_TREASURE_METRE].pos.y -= 4.0f;
                }
                if (gNumActivePlayers >= FOUR_PLAYERS) {
                    temp = (j == PLAYER_ONE) || (j == PLAYER_THREE) ? 15 : -10;
                } else {
                    temp = gNumActivePlayers == TWO_PLAYERS ? -10 : 0;
                }
                gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC].pos.x += temp;
                gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].pos.x += temp;
                gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1].pos.x += temp;
                gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_2].pos.x += temp;
                gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE].pos.x += temp;
                gCurrentHud->entry[HUD_BANANA_COUNT_X].pos.x += temp;
                break;
        }
        if (is_taj_challenge()) {
            gCurrentHud->entry[HUD_LAP_COUNT_LABEL].pos.x += 28.0f;
            gCurrentHud->entry[HUD_LAP_COUNT_CURRENT].pos.x += 28.0f;
            gCurrentHud->entry[HUD_LAP_COUNT_SEPERATOR].pos.x += 28.0f;
            gCurrentHud->entry[HUD_LAP_COUNT_TOTAL].pos.x += 28.0f;
            gCurrentHud->entry[HUD_LAP_COUNT_FLAG].pos.x += 28.0f;
        }
        if (osTvType == OS_TV_TYPE_PAL) {
            for (k = 0; (k < HUD_ELEMENT_COUNT) ^ 0; k++) {
                i = k;
                gCurrentHud->entry[k].pos.y *= 1.2;
                gCurrentHud->entry[k].pos.x -= 4.0f;
                if ((gAssetHudElementIds[gCurrentHud->entry[k].spriteID] & ASSET_MASK_TEXTURE) == ASSET_MASK_TEXTURE) {
                    gCurrentHud->entry[i].pos.y -= 10.0f;
                }
            }

            for (k = HUD_SPEEDOMETRE_0; k < HUD_SILVER_COIN_TALLY; k++) {
                gCurrentHud->entry[k].pos.y += 10.0f;
            }
        }
        gCurrentHud->entry[HUD_BALLOON_COUNT_ICON].scale = 1.0f;
        gCurrentHud->entry[HUD_BALLOON_COUNT_X].spriteID = HUD_ASSET_18;
        gCurrentHud->entry[HUD_BALLOON_COUNT_NUMBER_1].spriteID = 9;
        gCurrentHud->entry[HUD_BALLOON_COUNT_NUMBER_2].spriteID = 9;
    }
    if (get_current_level_race_type() & RACETYPE_CHALLENGE) {
        gPrevToggleSetting = gHudToggleSettings[1];
        gHudToggleSettings[1] = 0;
    } else {
        gHudToggleSettings[1] = gPrevToggleSetting;
    }
}

/**
 * Frees all elements in the hud, and the player hud, and flushes particles
 */
void hud_free(void) {
    s32 i;
    for (i = 0; i < gAssetHudElementIdsCount; i++) {
        if (gAssetHudElements->entry[i] != NULL) {
            if ((gAssetHudElementIds[i] & ASSET_MASK_TEXTURE) == ASSET_MASK_TEXTURE) {
                tex_free(gAssetHudElements->entry[i]);
            } else if (gAssetHudElementIds[i] & ASSET_MASK_SPRITE) {
                sprite_free((Sprite *) gAssetHudElements->entry[i]);
            } else if (gAssetHudElementIds[i] & ASSET_MASK_OBJECT) {
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
 * Root function for the HUD updating and rendering for individual players.
 * The player can toggle specific overrides and settings for displays based on their current game modes.
 */
void hud_render_player(Gfx **dList, Mtx **mtx, Vertex **vertexList, Object *obj, s32 updateRate) {
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
            gHudDL = *dList;
            gHudMtx = *mtx;
            gHudVtx = *vertexList;
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
                racer = &obj->unk64->racer;
                if (D_8012718A) {
                    gHudController = 1 - racer->playerIndex;
                } else {
                    gHudController = racer->playerIndex;
                }
                gCurrentHud = gPlayerHud[gHudCurrentViewport];
                if (cutscene_id() != 10) {
                    if (gHUDNumPlayers == ONE_PLAYER) {
                        if (input_pressed(gHudController) & D_CBUTTONS && racer->raceFinished == FALSE &&
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
                    } else if (input_pressed(gHudController) & D_CBUTTONS && racer->raceFinished == FALSE &&
                               !(gHudLevelHeader->race_type & RACETYPE_CHALLENGE) && gHudRaceStart) {
                        if (D_800E2794[gHUDNumPlayers][racer->playerIndex] < 3) {
                            D_800E2794[gHUDNumPlayers][racer->playerIndex]++;
                        } else {
                            D_800E2794[gHUDNumPlayers][racer->playerIndex] = 0;
                        }
                        sound_play((SOUND_TING_HIGHEST - (D_800E2794[gHUDNumPlayers][racer->playerIndex] == 0)), NULL);
                    }
                    if (input_pressed(gHudController) & R_CBUTTONS && racer->raceFinished == FALSE && gHudRaceStart &&
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
                        sndp_set_active_sound_limit(12);
                    } else {
                        start_level_music(1.0f);
                    }
                    gRaceStartShowHudStep += 1;
                }
                gDPPipeSync(gHudDL++);
                rsp_init(&gHudDL);
                rdp_init(&gHudDL);
                tex_enable_modes(RENDER_ALL);
                tex_disable_modes(RENDER_Z_COMPARE);
                sprite_opaque(FALSE);
                if (check_if_showing_cutscene_camera() == FALSE && gHudRaceStart == FALSE &&
                    racer->playerIndex == PLAYER_ONE) {
                    if (gHudSlide) {
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
                            gHudSlide = TRUE;
                            sound_play(SOUND_EXPLOSION2, NULL);
                            gHudBounceX = 0;
                        }
                    }
                }
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
                hud_magnet_reticle(obj);
                mtx_ortho(&gHudDL, &gHudMtx);
                gDPSetEnvColor(gHudDL++, 255, 255, 255, 0);
                countdown = get_race_countdown() >> 1;
                if (is_in_time_trial()) {
                    hud_main_time_trial(countdown, obj, updateRate);
                } else {
                    if (cutscene_id() == 10) {
                        sprite_anim_off(TRUE);
                        hud_balloons(racer);
                        sprite_anim_off(FALSE);
                    } else {
                        switch (get_current_level_race_type()) {
                            case RACETYPE_DEFAULT:
                            case RACETYPE_HORSESHOE_GULCH:
                                if (is_taj_challenge()) {
                                    hud_main_taj(countdown, obj, updateRate);
                                } else {
                                    hud_main_race(countdown, obj, updateRate);
                                }
                                break;
                            case RACETYPE_BOSS:
                                hud_main_boss(countdown, obj, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_BANANAS:
                                hud_main_treasure(countdown, obj, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_BATTLE:
                                hud_main_battle(countdown, obj, updateRate);
                                break;
                            case RACETYPE_CHALLENGE_EGGS:
                                hud_main_eggs(countdown, obj, updateRate);
                                break;
                            default:
                                hud_main_hub(obj, updateRate);
                                break;
                        }
                    }
                }
                if (racer->raceFinished == TRUE) {
                    sprite_anim_off(TRUE);
                    if (is_in_time_trial()) {
                        hud_time_trial_finish(racer, updateRate);
                    } else if (cam_get_viewport_layout() == VIEWPORT_LAYOUT_1_PLAYER && racer->finishPosition == 1) {
                        if (is_in_two_player_adventure()) {
                            if (get_current_level_race_type() == RACETYPE_BOSS) {
                                goto showFinishRace;
                            }
                            goto block_95;
                        }
                    showFinishRace:
                        hud_race_finish_1player(racer, updateRate);
                    } else {
                    block_95:
                        hud_race_finish_multiplayer(racer, updateRate);
                    }
                    sprite_anim_off(FALSE);
                }
                gMinimapFade = FALSE;
                sprite_opaque(TRUE);
                if (D_80127180) {
                    gHudSprites[D_80127180].texture = NULL;
                    texrect_draw(&gHudDL, gHudSprites, 0, 0, 255, 255, 255, 255);
                }
                *dList = gHudDL;
                *mtx = gHudMtx;
                *vertexList = gHudVtx;
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
            sndp_stop(gHudAudioData[i].soundMask);
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
                sound_play(gHudAudioData[i].soundID, &gHudAudioData[i].soundMask);
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
                sndp_stop(gHudAudioData[i].soundMask);
                gHudAudioData[i].soundMask = 0;
            }
        }
    }
    if (gHudAudioReset && gHudAudioData[0].volume == 0) {
        gHudAudioReset = FALSE;
        if (gNumActivePlayers == 1) {
            sndp_set_active_sound_limit(8);
        } else if (gNumActivePlayers == 2) {
            sndp_set_active_sound_limit(12);
        } else {
            sndp_set_active_sound_limit(16);
        }
    }
}

/**
 * In a race, render all of the race related HUD.
 */
void hud_main_race(s32 countdown, Object *obj, s32 updateRate) {
    Object_Racer *racer = &obj->unk64->racer;

    sprite_anim_off(TRUE);
    hud_course_arrows(racer, updateRate);
    hud_wrong_way(racer, updateRate);
    hud_race_start(countdown, updateRate);

    if (gHudLevelHeader->race_type == RACETYPE_DEFAULT) {
        hud_lap_count(racer, updateRate);
    }

    hud_bananas(racer, updateRate);
    hud_race_time(racer, updateRate);
    hud_race_position(racer, updateRate);
    hud_speedometre(obj, updateRate);

    if (gHudSilverCoinRace && racer->raceFinished == FALSE) {
        hud_silver_coins(racer, updateRate);
    }

    hud_weapon(obj, updateRate);
    sprite_anim_off(FALSE);
}

/**
 * Render the onscreen course arrows that show the player where to go.
 */
void hud_course_arrows(Object_Racer *racer, s32 updateRate) {
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
                    gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 160);
                    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, indicator);
                    indicator->pos.x = -indicator->pos.x;
                    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, indicator);
                    indicator->pos.x = -indicator->pos.x;
                    indicator->rotation.x_rotation = 0;
                    gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
                }
            }
        } else {
            racer->indicator_timer = 0;
        }
        if (gHudIndicatorTimer) {
            if (gHudIndicatorTimer & 0x20) {
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 160);
                indicator = &gCurrentHud->entry[HUD_COURSE_ARROWS];
                indicator->rotation.y_rotation = 0;
                indicator->rotation.x_rotation = 0;
                indicator->spriteID = HUD_SPRITE_INDICATOR_EXCLAMATION;
                if ((get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) && ((s32) racer->indicator_type < 30)) {
                    indicator->rotation.y_rotation = (s16) (0x8000 - indicator->rotation.y_rotation);
                }
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, indicator);
                indicator->pos.x = -indicator->pos.x;
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, indicator);
                indicator->pos.x = -indicator->pos.x;
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
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
void hud_main_treasure(s32 countdown, Object *obj, s32 updateRate) {
    Object_Racer *racer;
    Object **racers;
    s32 numRacers;
    s32 i;

    racer = &obj->unk64->racer;
    racers = get_racer_objects(&numRacers);
    sprite_anim_off(TRUE);
    hud_race_start(countdown, updateRate);
    switch (gNumActivePlayers) {
        case 1:
            for (i = 0; i < numRacers; i++) {
                racer = &racers[i]->unk64->racer;
                hud_treasure(racer);
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
            hud_treasure(racer);
            break;
    }
    racer = &obj->unk64->racer;
    rendermode_reset(&gHudDL);
    hud_bananas(racer, updateRate);
    hud_weapon(obj, updateRate);
    sprite_anim_off(FALSE);
}

/**
 * The Egg Collector challenge mode displays the icons of each player and their score.
 */
void hud_main_eggs(s32 countdown, Object *obj, s32 updateRate) {
    Object_Racer *racer = &obj->unk64->racer;
    if (racer->raceFinished == FALSE) {
        sprite_anim_off(TRUE);
        hud_race_start(countdown, updateRate);
        hud_weapon(obj, updateRate);
        if ((127 - (updateRate * 2)) >= gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].challengeEggs.alphaTimer) {
            gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].challengeEggs.alphaTimer += updateRate * 2;
        } else {
            gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].challengeEggs.alphaTimer =
                (gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].challengeEggs.alphaTimer + (updateRate * 2)) - 255;
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
    if (numRacers == MAXCONTROLLERS) {
        sprite_anim_off(TRUE);
        portraitX = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
        portraitY = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
        diffX = (gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x - portraitX);
        diffY = (gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.y - portraitY);
        for (i = 0; i < MAXCONTROLLERS; i++) {
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
    gHudPALScale = TRUE;
    if (gNumActivePlayers < 3 || (gNumActivePlayers == 3 && racer->playerIndex == PLAYER_COMPUTER)) {
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT]);
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
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON]);
        gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x += 12.0f;
    }
    gHudColour = alpha | COLOUR_RGBA32(255, 255, 255, 0);
    i2 = i;
    for (i = 0; i < racer->eggHudCounter && i2 < HUD_EGG_TOTAL; i++) {
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON]);
        i2++;
        gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x += 12.0f;
    }
    gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x = prevY;
    gHudPALScale = FALSE;
}

/**
 * Render the HUD for the battle mode challenge.
 * Shows each players portrait and their remaining health.
 */
void hud_main_battle(s32 countdown, Object *obj, s32 updateRate) {
    Object **racerObjs;
    Object_Racer *racer;
    s32 numRacers;
    s32 racersFinished;
    s32 i;

    racer = &obj->unk64->racer;
    if (gNumActivePlayers != 1 || racer->raceFinished == FALSE) {
        sprite_anim_off(TRUE);
        hud_race_start(countdown, updateRate);
        hud_weapon(obj, updateRate);
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
                hud_bananas(racer, updateRate);
                break;
        }
        sprite_anim_off(FALSE);
    }
}

void func_800A1E48(Object *racerObj, s32 updateRate) {
    s32 pad0;
    s32 i;
    Object_Racer *racer;
    s32 numRacers;
    Object **racers;
    s32 prevChallengerPortraitX;
    s32 prevChallengerPortraitY;
    Object_Racer *curRacer;
    s32 offsetX;
    s32 offsetY;
    s32 tempX;
    s32 tempY;

    racers = get_racer_objects(&numRacers);
    if (racerObj != NULL) {
        racer = &racerObj->unk64->racer;
    } else {
        racer = &racers[PLAYER_ONE]->unk64->racer;
    }

    sprite_anim_off(TRUE);
    if (numRacers == 4) {
        offsetX = 0;
        offsetY = 0;
        prevChallengerPortraitX = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
        prevChallengerPortraitY = gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
        for (i = 0; i < 4; i++) {
            curRacer = &racers[i]->unk64->racer;
            tempX = (offsetX + prevChallengerPortraitX) - gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
            tempY = (offsetY + prevChallengerPortraitY) - gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
            gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x += tempX;
            gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y += tempY;
            gCurrentHud->entry[HUD_BATTLE_BANANA_ICON].pos.x += tempX;
            gCurrentHud->entry[HUD_BATTLE_BANANA_ICON].pos.y -= tempY;
            gCurrentHud->entry[HUD_BATTLE_BANANA_X].pos.x += tempX;
            gCurrentHud->entry[HUD_BATTLE_BANANA_X].pos.y += tempY;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.x += tempX;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.y += tempY;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].pos.x += tempX;
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].pos.y += tempY;
            if (gNumActivePlayers < 3 || racer->playerIndex == curRacer->playerIndex) {
                hud_lives_render(curRacer, updateRate);
            }
            if (gNumActivePlayers == 1) {
                offsetX += 68;
            } else if (gNumActivePlayers == 2) {
                if (osTvType == OS_TV_TYPE_PAL) {
                    offsetY += 66.0;
                } else {
                    offsetY += 55;
                }
            }
        }

        tempX = prevChallengerPortraitX - gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x;
        tempY = prevChallengerPortraitY - gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x += tempX;
        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y += tempY;
        gCurrentHud->entry[HUD_BATTLE_BANANA_ICON].pos.x += tempX;
        gCurrentHud->entry[HUD_BATTLE_BANANA_ICON].pos.y -= tempY;
        gCurrentHud->entry[HUD_BATTLE_BANANA_X].pos.x += tempX;
        gCurrentHud->entry[HUD_BATTLE_BANANA_X].pos.y += tempY;
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.x += tempX;
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.y += tempY;
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].pos.x += tempX;
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].pos.y += tempY;
    }

    sprite_anim_off(FALSE);
}

/**
 * Render the portrait and life counter in the battle mode.
 * In 3/4 player, skips the portrait for all human players. Player 4 has a portrait if it's AI.
 */
void hud_lives_render(Object_Racer *racer, UNUSED s32 updateRate) {
    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].spriteID = racer->characterId + HUD_SPRITE_PORTRAIT;
    if (gNumActivePlayers < 3 || (gNumActivePlayers == 3 && racer->playerIndex == PLAYER_COMPUTER)) {
        gHudPALScale = TRUE;
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT]);
        gHudPALScale = FALSE;
        rdp_init(&gHudDL);
        rendermode_reset(&gHudDL);
    }
    if (racer->bananas < 10) {
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].spriteOffset = racer->bananas;
        if (gNumActivePlayers == 2) {
            gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.x += 6.0f;
        }
    } else {
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].spriteOffset = racer->bananas / 10;
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2].spriteOffset = racer->bananas % 10;
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_2]);
    }
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1]);
    if (gNumActivePlayers == 2 && racer->bananas < 10) {
        gCurrentHud->entry[HUD_BATTLE_BANANA_COUNT_1].pos.x -= 6.0f;
    }
    if (gNumActivePlayers != 2) {
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BATTLE_BANANA_X]);
        sprite_opaque(TRUE);
        gHudPALScale = TRUE;
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BATTLE_BANANA_ICON]);
        gHudPALScale = FALSE;
        sprite_opaque(FALSE);
    }
}

/**
 * When racing the boss, render the essentials, but skip the bananas.
 */
void hud_main_boss(s32 countdown, Object *obj, s32 updateRate) {
    LevelHeader *level;
    Object_Racer *racer = &obj->unk64->racer;

    sprite_anim_off(TRUE);
    hud_wrong_way(racer, updateRate);
    hud_race_start(countdown, updateRate);
    hud_race_time(racer, updateRate);
    hud_weapon(obj, updateRate);

    level = get_current_level_header();
    if (level->laps > 1) {
        hud_lap_count(racer, updateRate);
    }

    hud_speedometre(obj, updateRate);
    hud_race_position(racer, updateRate);
    sprite_anim_off(FALSE);
}

/**
 * When racing Taj in the overworld, render most of the basic race hud.
 */
void hud_main_taj(s32 countdown, Object *obj, s32 updateRate) {
    Object_Racer *racer = &obj->unk64->racer;

    sprite_anim_off(TRUE);
    hud_wrong_way(racer, updateRate);
    hud_lap_count(racer, updateRate);
    hud_race_position(racer, updateRate);
    hud_race_time(racer, updateRate);
    hud_race_start(countdown, updateRate);
    hud_speedometre(obj, updateRate);
    sprite_anim_off(FALSE);
}

/**
 * The hub world displays the player's balloon count.
 * In two player adventure, the icon of the character of the player sitting out is displayed.
 */
void hud_main_hub(Object *obj, s32 updateRate) {
    Object_Racer *racer;
    HudElement *portrait;

    if (cam_get_viewport_layout() == PLAYER_ONE) {
        racer = &obj->unk64->racer;
        sprite_anim_off(TRUE);
        hud_balloons(racer);
        hud_speedometre(obj, updateRate);
        if (is_in_two_player_adventure()) {
            portrait = (HudElement *) &gCurrentHud->entry[HUD_TWO_PLAYER_ADV_PORTRAIT];
            portrait->spriteID = (get_settings()->racers[1].character + HUD_SPRITE_PORTRAIT);
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, portrait);
        }
        sprite_anim_off(FALSE);
    }
}

void hud_main_time_trial(s32 arg0, Object *playerRacerObj, s32 updateRate) {
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
    UNUSED s32 pad;
    UNUSED s32 pad2;
    s32 temp_t6;
    f32 animcationFraction;
    f32 posX;
    f32 posY;
    f32 posZ;
    u16 soundID;

    curRacer = &playerRacerObj->unk64->racer;
    stopwatchTimer = 0;
    if (gAssetHudElements->entry[HUD_BALLOON_COUNT_X] == NULL) {
        ttSWBody.objectID = gAssetHudElementIds[HUD_BALLOON_COUNT_X] & 0xFFFF;
        ttSWBody.size = sizeof(LevelObjectEntryCommon);
        ttSWBody.x = 0;
        ttSWBody.y = 0;
        ttSWBody.z = 0;
        gAssetHudElements->entry[HUD_BALLOON_COUNT_X] = spawn_object(&ttSWBody, 0);
        gCurrentHud->entry[HUD_STOPWATCH_HANDS].rotation.y_rotation = -0x8000;
        if (gAssetHudElements->entry[HUD_BALLOON_COUNT_X] != NULL) {
            ((Object *) gAssetHudElements->entry[HUD_BALLOON_COUNT_X])->segment.animFrame = 0;
        }
    }

    if (gAssetHudElements->entry[HUD_STOPWATCH] == NULL) {
        ttSWArms.objectID = gAssetHudElementIds[HUD_STOPWATCH] & 0xFFFF;
        ttSWArms.size = sizeof(LevelObjectEntryCommon);
        ttSWArms.x = 0;
        ttSWArms.y = 0;
        ttSWArms.z = 0;
        gAssetHudElements->entry[HUD_STOPWATCH] = spawn_object(&ttSWArms, 0);
        gCurrentHud->entry[HUD_STOPWATCH].rotation.y_rotation = -0x8000;
    }

    ttSWBodyObject = gAssetHudElements->entry[HUD_BALLOON_COUNT_X];
    if (ttSWBodyObject == NULL) {
        return;
    }

    ttSWBodyObject->segment.object.animationID = gStopwatchAnimID;
    obj68 = ttSWBodyObject->unk68[0];
    obj68->objModel->texOffsetUpdateRate = updateRate;
    if (gStopwatchAnimID != 0xFF) {
        if (gStopwatchAnimID == 4 && (get_race_countdown() || !music_is_playing())) {
            ttSWBodyObject->segment.animFrame = 16;
        } else if (gStopwatchAnimID == 4) {
            animcationFraction = music_animation_fraction();
            temp_t6 = (obj68->objModel->animations[gStopwatchAnimID].animLength - 1) << 4;
            if (animcationFraction == -1.0) {
                ttSWBodyObject->segment.animFrame = 0.0;
            } else if (animcationFraction > 0.5) {
                animcationFraction -= 0.5;
                animcationFraction *= 2.0;
                ttSWBodyObject->segment.animFrame = temp_t6 - (animcationFraction * temp_t6);
            } else {
                animcationFraction *= 2;
                ttSWBodyObject->segment.animFrame = temp_t6 * animcationFraction;
            }
        } else if (is_game_paused() == FALSE) {
            if (D_80126D69 < 0) {
                if (ttSWBodyObject->segment.animFrame > -(updateRate * D_80126D69)) {
                    ttSWBodyObject->segment.animFrame += (updateRate * D_80126D69);
                } else {
                    ttSWBodyObject->segment.animFrame = 1;
                    D_80126D69 = -D_80126D69;
                }
            } else {
                ttSWBodyObject->segment.animFrame += (updateRate * D_80126D69);
                temp_lo = (obj68->objModel->animations[gStopwatchAnimID].animLength - 1) << 4;
                if (ttSWBodyObject->segment.animFrame >= temp_lo) {
                    if (D_80126D68 != 0) {
                        D_80126D69 = -D_80126D69;
                        ttSWBodyObject->segment.animFrame = temp_lo - 1;
                    } else {
                        ttSWBodyObject->segment.animFrame = 0;
                        if (curRacer->wrongWayCounter == 0 && curRacer->raceFinished == FALSE) {
                            hud_stopwatch_face(4, 0, 4, 1, 1);
                        }
                    }
                }
            }
        }
        obj_animate(ttSWBodyObject);
    }

    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_STOPWATCH_HANDS]);

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
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_STOPWATCH]);
    }

    stopwatchTimer = (((stopwatchTimer / 60) + 30) % 60);
    gCurrentHud->entry[HUD_STOPWATCH].rotation.z_rotation = stopwatchTimer * 0x444;
    gCurrentHud->entry[HUD_STOPWATCH].pos.y = gCurrentHud->entry[HUD_STOPWATCH_HANDS].pos.y + 28.0f;
    if (get_contpak_error() <= 0) {
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_STOPWATCH]);
    }

    obj68->animUpdateTimer = 0;
    sprite_anim_off(TRUE);
    hud_course_arrows(curRacer, updateRate);
    if (curRacer->raceFinished == FALSE) {
        spB8 = gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.y;
        for (i = 0; i < curRacer->countLap && i < gHudLevelHeader->laps; i++) {
            get_timestamp_from_frames(curRacer->lap_times[i], &spB4, &spB0, &spAC);
            gHudColour = gHudLapColours[i];
            hud_timer_render(gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x, spB8, spB4, spB0, spAC, 1);
            gHudColour = COLOUR_RGBA32(255, 255, 255, 254);
            spB8 += 12;
            gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
            gCurrentHud->entry[HUD_TIME_TRIAL_LAP_NUMBER].spriteOffset = i + 1;
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx,
                               (HudElement *) &gCurrentHud->entry[HUD_TIME_TRIAL_LAP_NUMBER]);
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx,
                               (HudElement *) &gCurrentHud->entry[HUD_TIME_TRIAL_LAP_TEXT]);
            gCurrentHud->entry[HUD_TIME_TRIAL_LAP_NUMBER].pos.y += 12.0f;
            gCurrentHud->entry[HUD_TIME_TRIAL_LAP_TEXT].pos.y += 12.0f;
        }

        gCurrentHud->entry[HUD_TIME_TRIAL_LAP_NUMBER].pos.y -= i * 0xC;
        gCurrentHud->entry[HUD_TIME_TRIAL_LAP_TEXT].pos.y -= i * 0xC;
        if ((curRacer->boost_sound & BOOST_SOUND_UNK4) && (D_80126D4C <= 0)) {
            hud_stopwatch_face(7, 3, 0, 4, 0);
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
                soundID = rand_range(0, D_80126D64 + 2) + SOUND_VOICE_TT_OH_NO;
                while (soundID == gHudTTSoundID) {
                    soundID = rand_range(0, D_80126D64 + 2) + SOUND_VOICE_TT_OH_NO;
                }
                gHudTTSoundID = soundID;
                sound_play(soundID, &gHUDVoiceSoundMask);
                D_80126D64 = 1;
            }
        }
    }

    if ((curRacer->lap > 0) && (curRacer->lap < gHudLevelHeader->laps) && (curRacer->lap_times[curRacer->lap] < 20) &&
        (gHUDVoiceSoundMask == 0) && (curRacer->vehicleID <= VEHICLE_PLANE)) {
        gHudSettings = get_settings();
        if (curRacer->lap_times[curRacer->lap - 1] <
            gHudSettings->flapTimesPtr[curRacer->vehicleID][get_current_map_id()]) {
            stopwatchTimer = curRacer->lap_times[curRacer->lap - 1];
            for (i = 0; i < curRacer->lap - 1; i++) {
                if (stopwatchTimer >= curRacer->lap_times[i]) {
                    stopwatchTimer = 0;
                }
            }
            if (stopwatchTimer != 0) {
                sound_play(SOUND_VOICE_TT_LAP_RECORD, &gHUDVoiceSoundMask);
            }
        }
    }

    if (timetrial_valid_player_ghost()) {
        ttSWBodyObject = timetrial_player_ghost();
        if (ttSWBodyObject != NULL) {
            if (get_race_countdown() == 0 && curRacer->raceFinished == FALSE) {
                posX = ttSWBodyObject->segment.trans.x_position - playerRacerObj->segment.trans.x_position;
                posY = ttSWBodyObject->segment.trans.y_position - playerRacerObj->segment.trans.y_position;
                posZ = ttSWBodyObject->segment.trans.z_position - playerRacerObj->segment.trans.z_position;
                if ((sqrtf((posX * posX) + (posY * posY) + (posZ * posZ)) < 600.0f) && (gHUDVoiceSoundMask == 0) &&
                    (D_80126D50 == 0)) {
                    soundID = SOUND_VOICE_TT_GO_FOR_IT + rand_range(0, 2);
                    while (soundID == gHudTTSoundID) {
                        soundID = SOUND_VOICE_TT_GO_FOR_IT + rand_range(0, 2);
                    }
                    gHudTTSoundID = soundID;
                    sound_play(soundID, &gHUDVoiceSoundMask);
                    D_80126D50 = rand_range(120, 1200);
                }
                D_80126D50 -= updateRate;
                if (D_80126D50 < 0) {
                    D_80126D50 = 0;
                }
            }
        }
    }

    if (curRacer->lap_times[curRacer->lap] < 30 && curRacer->lap != 0) {
        hud_stopwatch_face(5, 1, 2, 2, 0);
    } else if (curRacer->boostTimer > 0) {
        hud_stopwatch_face(6, 2, 3, 2, 0);
    } else if (curRacer->wrongWayCounter > 120) {
        hud_stopwatch_face(6, 3, 1, 4, 0);
    }

    hud_lap_count(curRacer, updateRate);
    hud_race_time(curRacer, updateRate);
    hud_bananas(curRacer, updateRate);
    hud_wrong_way(curRacer, updateRate);
    hud_race_start(arg0, updateRate);
    hud_speedometre(playerRacerObj, updateRate);
    if (get_contpak_error() > 0) {
        // has to be defined here to match
        char *SWMessage[3];

#if REGION == REGION_JP
        switch (get_contpak_error()) {
            // Print "ゴースト セーブ ふかのう" - "Ghost Save Impossible"
            case CONTPAK_ERROR_UNKNOWN:
                SWMessage[2] = gHudTimeTrialJp_Ghost;
                SWMessage[1] = gHudTimeTrialJp_Save;
                SWMessage[0] = gHudTimeTrialJp_Impossible;
                break;
            // Print "{blank} パック フル " - "{blank} Pak Full"
            case CONTPAK_ERROR_FULL:
                SWMessage[2] = *(s32 *) gHudTimeTrialJp_FullBlank;
                SWMessage[1] = gHudTimeTrialJp_FullPak;
                SWMessage[0] = gHudTimeTrialJp_Full;
                break;
            // Print "{blank} パック ふりょう" - "{blank} Pak Defective"
            case CONTPAK_ERROR_DAMAGED:
                SWMessage[2] = *(s32 *) gHudTimeTrialJp_DamagedBlank;
                SWMessage[1] = gHudTimeTrialJp_DamagedPak;
                SWMessage[0] = gHudTimeTrialJp_Defective;
                break;
            default:
                SWMessage[2] = NULL;
                SWMessage[1] = NULL;
                SWMessage[0] = NULL;
                break;
        }
#else
        switch (get_contpak_error()) {
            // Print "CAN'T SAVE GOST"
            case CONTPAK_ERROR_UNKNOWN:
                SWMessage[2] = "CAN'T";
                SWMessage[1] = "SAVE";
                SWMessage[0] = "GHOST";
                break;
            // Print "CONTROLLER PAK FULL"
            case CONTPAK_ERROR_FULL:
                SWMessage[2] = " CONTROLLER";
                SWMessage[1] = "PAK";
                SWMessage[0] = "FULL";
                break;
            // Print "CONTROLLER PAK DAMAGED"
            case CONTPAK_ERROR_DAMAGED:
                SWMessage[2] = " CONTROLLER";
                SWMessage[1] = "PAK";
                SWMessage[0] = "DAMAGED";
                break;
#if VERSION >= VERSION_79
            default:
                SWMessage[2] = NULL;
                SWMessage[1] = NULL;
                SWMessage[0] = NULL;
                break;
#endif
        }
#endif

        set_kerning(TRUE);
        set_text_font(ASSET_FONTS_FUNFONT);
        // Draw text shadow.
        set_text_colour(0, 0, 0, 255, 255);
        draw_text(&gHudDL, gStopwatchErrorX + gHudOffsetX + gHudBounceX + 1, gStopwatchErrorY + 1, SWMessage[2],
                  ALIGN_MIDDLE_CENTER);
        draw_text(&gHudDL, gStopwatchErrorX + gHudOffsetX + gHudBounceX + 1, gStopwatchErrorY + 15, SWMessage[1],
                  ALIGN_MIDDLE_CENTER);
        draw_text(&gHudDL, gStopwatchErrorX + gHudOffsetX + gHudBounceX + 1, gStopwatchErrorY + 29, SWMessage[0],
                  ALIGN_MIDDLE_CENTER);
        // Draw actual text.
        set_text_colour(D_80127194->rgba.r, D_80127194->rgba.g, D_80127194->rgba.b, 128, D_80127194->rgba.a);
        draw_text(&gHudDL, gStopwatchErrorX + gHudOffsetX + gHudBounceX, gStopwatchErrorY, SWMessage[2],
                  ALIGN_MIDDLE_CENTER);
        draw_text(&gHudDL, gStopwatchErrorX + gHudOffsetX + gHudBounceX, gStopwatchErrorY + 14, SWMessage[1],
                  ALIGN_MIDDLE_CENTER);
        draw_text(&gHudDL, gStopwatchErrorX + gHudOffsetX + gHudBounceX, gStopwatchErrorY + 28, SWMessage[0],
                  ALIGN_MIDDLE_CENTER);
        update_colour_cycle(D_80127194, updateRate);
        set_kerning(FALSE);
    }

    sprite_anim_off(FALSE);
}

void hud_stopwatch_face(u8 arg0, u8 arg1, u8 animID, u8 arg3, u8 arg4) {
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
            gStopwatchAnimID = animID;
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
void hud_speedometre(Object *obj, UNUSED s32 updateRate) {
    f32 vel;
    Object_Racer *racer;
    s32 opacity;

    if (gNumActivePlayers == 1) {
        if (!check_if_showing_cutscene_camera()) {
            racer = &obj->unk64->racer;
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
                //!@bug: Planes and hovercraft use drift_direction for something else, applying this unintentionally.
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
                    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_SPEEDOMETRE_BG]);
                    rendermode_reset(&gHudDL);
                    sprite_opaque(TRUE);
                    gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, opacity);
                    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_SPEEDOMETRE_ARROW]);
                    sprite_opaque(FALSE);
                    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_SPEEDOMETRE_0]);
                    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_SPEEDOMETRE_30]);
                    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_SPEEDOMETRE_60]);
                    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_SPEEDOMETRE_90]);
                    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_SPEEDOMETRE_120]);
                    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_SPEEDOMETRE_150]);
                }
            }
        }
    }
}

/**
 * Call the functions that render the "Get Ready" and "GO!" as well as their countdowns to control fade.
 * This function will also call to begin the background music for 1 and 2 player. 3 and 4 are treated with silence.
 */
void hud_race_start(s32 countdown, s32 updateRate) {
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
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, (countdown * 255) / 40);
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_RACE_START_READY]);
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
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
                randomRacer = racerGroup[rand_range(1, numRacerObjects) - 1];
                racer = &randomRacer->unk64->racer;
                if (racer->vehicleID == VEHICLE_CAR) {
                    if (rand_range(0, 100) >= 96) {
                        frequency = 1.25 - ((rand_range(0, 7) * 0.5) / 7.0);
                        audspat_play_sound_direct(
                            76, randomRacer->segment.trans.x_position, randomRacer->segment.trans.y_position,
                            randomRacer->segment.trans.z_position, AUDIO_POINT_FLAG_ONE_TIME_TRIGGER,
                            ((rand_range(0, 7) * 63) / 7) + 24, frequency * 100.0f, &gRaceStartSoundMask);
                    }
                }
            }
        } else if (gCurrentHud->entry[HUD_RACE_START_GO].pos.x > -200.0f) {
            gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 160);
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, (HudElement *) &gCurrentHud->entry[HUD_RACE_START_GO]);
            gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
            gCurrentHud->entry[HUD_RACE_START_GO].raceStartGo.musicStartTimer[gHudCurrentViewport] += updateRate;
            if (gCurrentHud->entry[HUD_RACE_START_GO].raceStartGo.musicStartTimer[gHudCurrentViewport] >= 60) {
                if (gRaceStartShowHudStep == 4) {
                    // Mute background music in 3/4 player.
                    if (cam_get_viewport_layout() > TWO_PLAYERS) {
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
void hud_bananas(Object_Racer *racer, s32 updateRate) {
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
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BANANA_COUNT_X]);
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
            enable_pal_viewport_height_adjust(TRUE);
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BANANA_COUNT_ICON_STATIC]);
            enable_pal_viewport_height_adjust(FALSE);
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
                enable_pal_viewport_height_adjust(TRUE);
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BANANA_COUNT_SPARKLE]);
                enable_pal_viewport_height_adjust(FALSE);
            }
        } else {
            gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].spriteOffset = prevSprite + 128;
            sprite_anim_off(FALSE);
            sprite_opaque(TRUE);
            enable_pal_viewport_height_adjust(TRUE);
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN]);
            sprite_opaque(FALSE);
            enable_pal_viewport_height_adjust(FALSE);
            sprite_anim_off(TRUE);
            gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].spriteOffset -= 128;
        }
        temp_lo = bananas / 10;
        if (temp_lo) {
            gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1].spriteOffset = temp_lo;
            gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_2].spriteOffset = bananas % 10;
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_2]);
        } else {
            gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1].spriteOffset = bananas % 10;
        }
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BANANA_COUNT_NUMBER_1]);
        gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
    }
}

/**
 * Renders the icons and secured treasure in Smokey's castle.
 * In 4 player, all icons are skipped and in 3 player, player 4's icon is shown on their quadrant.
 */
void hud_treasure(Object_Racer *racer) {
    s32 i;
    s32 prevY;

    prevY = gCurrentHud->entry[HUD_TREASURE_METRE].pos.y;
    if (gNumActivePlayers < 3 || (gNumActivePlayers == 3 && racer->playerIndex == PLAYER_COMPUTER)) {
        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].spriteID = racer->characterId + HUD_SPRITE_PORTRAIT;
        gHudPALScale = TRUE;
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT]);
        gHudPALScale = FALSE;
    }
    for (i = 0; i < 10; i++) {
        if (i >= racer->lap) {
            gHudColour = COLOUR_RGBA32(128, 128, 128, 128);
        }
        gHudPALScale = TRUE;
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_TREASURE_METRE]);
        gHudPALScale = FALSE;
        gCurrentHud->entry[HUD_TREASURE_METRE].pos.y -= 3.0f;
    }
    gCurrentHud->entry[HUD_TREASURE_METRE].pos.y = prevY;
    gHudColour = COLOUR_RGBA32(255, 255, 255, 254);
    gHudPALScale = FALSE;
}

/**
 * Render the silver coin counter on the side of the screen.
 * When the 8th coin is collected, wait half a second then play an encouraging voice clip from T.T.
 */
void hud_silver_coins(Object_Racer *racer, s32 updateRate) {
    s32 i;
    s32 prevY;

    gCurrentHud->entry[HUD_SILVER_COIN_TALLY].pos.y =
        (s32) gCurrentHud->entry[HUD_SILVER_COIN_TALLY].pos.y; // Rounds float down to it's int value.
    prevY = gCurrentHud->entry[HUD_SILVER_COIN_TALLY].pos.y;
    for (i = 0; i < 8; i++) {
        if (i >= racer->silverCoinCount) {
            gHudColour = COLOUR_RGBA32(128, 128, 128, 128);
        }
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_SILVER_COIN_TALLY]);
        gCurrentHud->entry[HUD_SILVER_COIN_TALLY].pos.y -=
            gCurrentHud->entry[HUD_SILVER_COIN_TALLY].silverCoinTally.offsetY;
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
 * Plays the race finish fanfare and displays what position you finished in the middle of the screen.
 * Uses a 3 step process to play the sounds, display the position, then slide it offscreen.
 */
void hud_race_finish_1player(Object_Racer *racer, s32 updateRate) {
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
        gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 210);
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, position1);
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, position2);
        gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
    }
}

UNUSED void func_800A4C34(UNUSED s32 countdown, UNUSED Object_Racer *racer, UNUSED s32 updateRate) {
}

/**
 * Render the current race position of the racer.
 * Scales up and down when the position changes.
 */
void hud_race_position(Object_Racer *racer, s32 updateRate) {
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
            place = settings->racers[gHudController].starting_position;
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
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_RACE_POSITION_END]);
    }
    scale = (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter + 129);
    scale *= 128.0f;
    scale = sins_f(scale);
    placeIndex = place - 1;
    gCurrentHud->entry[HUD_RACE_POSITION].scale =
        (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.baseScale / 127.0f) + (1.0 + (0.5 * scale));
    prevPos = gCurrentHud->entry[HUD_RACE_POSITION].pos.x;
    gCurrentHud->entry[HUD_RACE_POSITION].pos.x -= (24.0f * gCurrentHud->entry[HUD_RACE_POSITION].scale);
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_RACE_POSITION]);
    gCurrentHud->entry[HUD_RACE_POSITION].pos.x = prevPos;
    if (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.active) {
        if (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter < 127 - (updateRate * 16)) {
            gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter += (updateRate * 16);
        } else {
            gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter = 127;
        }
    }
    if (placeIndex != gCurrentHud->entry[HUD_RACE_POSITION].spriteOffset) {
        if (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.active &&
            gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter > 0) {
            gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter =
                -gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter;
        } else {
            gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter = -127;
            gCurrentHud->entry[HUD_RACE_POSITION].racePosition.active = TRUE;
        }
    }
    gCurrentHud->entry[HUD_RACE_POSITION].spriteOffset = placeIndex;
    if (gCurrentHud->entry[HUD_RACE_POSITION].racePosition.active &&
        gCurrentHud->entry[HUD_RACE_POSITION].racePosition.scaleCounter == 127) {
        gCurrentHud->entry[HUD_RACE_POSITION].racePosition.active = FALSE;
    }
}

/**
 * Displays the current lap number onscreen.
 * Also displays the "Lap 2" and "Final Lap" messages when the line is crossed.
 * In multiplayer, shows a cut down display, if the display setting is set to show laps.
 */
void hud_lap_count(Object_Racer *racer, s32 updateRate) {
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
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_LAP_COUNT_FLAG]);
        }
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_LAP_COUNT_LABEL]);
        if (racer->countLap >= gHudLevelHeader->laps - 1) {
            gCurrentHud->entry[HUD_LAP_COUNT_CURRENT].spriteOffset = gHudLevelHeader->laps;
        } else {
            gCurrentHud->entry[HUD_LAP_COUNT_CURRENT].spriteOffset = racer->countLap + 1;
        }
        gCurrentHud->entry[HUD_LAP_COUNT_TOTAL].spriteOffset = gHudLevelHeader->laps;
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_LAP_COUNT_CURRENT]);
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_LAP_COUNT_SEPERATOR]);
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_LAP_COUNT_TOTAL]);
    }
    if (gHUDNumPlayers == TWO_PLAYERS) {
        sprite_opaque(TRUE);
    }
    if (is_game_paused() == FALSE) {
        if (racer->lap_times[racer->lap] < 30 && gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.status == LAPTEXT_IDLE &&
            racer->raceFinished == FALSE) {
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
                    if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x <
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos - (updateRate * 13)) {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x += updateRate * 13;
                    } else {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x =
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos;
                    }
                    if (gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x >
                        gCurrentHud->entry[HUD_LAP_TEXT_TWO].lapText.targetPos + (updateRate * 13)) {
                        gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x -= updateRate * 13;
                    } else {
                        gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x =
                            gCurrentHud->entry[HUD_LAP_TEXT_TWO].lapText.targetPos;
                    }
                    if (racer->lap_times[racer->lap] >= 60) {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.direction = LAPTEXT_IN;
                        sound_play(SOUND_WHOOSH1, NULL);
                    }
                    if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x ==
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos &&
                        gCurrentHud->entry[HUD_LAP_TEXT_TWO].pos.x ==
                            gCurrentHud->entry[HUD_LAP_TEXT_TWO].lapText.targetPos &&
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
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 160);
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_LAP_TEXT_TWO]);
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx,
                                   &gCurrentHud->entry[HUD_LAP_TEXT_LAP]); // lap
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
            } else if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.status == LAPTEXT_UNK3) {
                if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.direction == LAPTEXT_IN) {
                    if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x >
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos + (updateRate * 13)) {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x -= updateRate * 13;
                    } else {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x =
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos;
                    }
                    if (gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x <
                        gCurrentHud->entry[HUD_LAP_TEXT_FINAL].lapText.targetPos - (updateRate * 13)) {
                        gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x += updateRate * 13;
                    } else {
                        gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x =
                            gCurrentHud->entry[HUD_LAP_TEXT_FINAL].lapText.targetPos;
                    }
                    if (racer->lap_times[racer->lap] >= 60) {
                        gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.direction = LAPTEXT_OUT;
                        sound_play(SOUND_WHOOSH1, NULL);
                    }
                    if (gCurrentHud->entry[HUD_LAP_TEXT_LAP].pos.x ==
                            gCurrentHud->entry[HUD_LAP_TEXT_LAP].lapText.targetPos &&
                        gCurrentHud->entry[HUD_LAP_TEXT_FINAL].pos.x ==
                            gCurrentHud->entry[HUD_LAP_TEXT_FINAL].lapText.targetPos &&
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

                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 160);
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_LAP_TEXT_FINAL]);
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_LAP_TEXT_LAP]);
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
            }
        }
    }
    sprite_opaque(FALSE);
}

/**
 * Players going the wrong way will be nagged by T.T to turn around.
 * This function plays the audio, and makes the text fly in.
 */
void hud_wrong_way(Object_Racer *obj, s32 updateRate) {
    f32 textMoveSpeed;
    f32 textPosTarget;

    if (gHUDNumPlayers == TWO_PLAYERS) {
        sprite_opaque(TRUE);
    }
    if (obj->wrongWayCounter > 120 &&
        (gHUDNumPlayers ||
         gCurrentHud->entry[HUD_WRONGWAY_1].pos.x == gCurrentHud->entry[HUD_WRONGWAY_1].lapText.targetPos) &&
        !is_game_paused()) {
        if ((gWrongWayNagPrefix || gWrongWayNagTimer == 0) && gHUDVoiceSoundMask == NULL) {
            // 20% chance that T.T decides not to precede his nagging with "No no no!"
            if (gWrongWayNagPrefix || rand_range(1, 10) >= 8) {
                gWrongWayNagPrefix = FALSE;
                sound_play(SOUND_VOICE_TT_WRONG_WAY, &gHUDVoiceSoundMask);
                gWrongWayNagTimer = rand_range(1, 480) + 120;
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
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 160);
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_WRONGWAY_1]);
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_WRONGWAY_2]);
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
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
void hud_finish_position(Object_Racer *racer) {
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

    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1]);
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_2]);
    if (!(get_current_level_race_type() & RACETYPE_CHALLENGE_BATTLE) && is_in_two_player_adventure() == FALSE) {
        get_racer_objects(&racerCount);
        if (gNumActivePlayers >= 2 &&
            (is_in_two_player_adventure() == FALSE || is_postrace_viewport_active() == FALSE)) {
            set_text_font(FONT_COLOURFUL);
            if (racerCount != racer->finishPosition) {
                set_text_colour(255, 255, 255, 0, 255);
                draw_text(&gHudDL, gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x - FINISH_TEXT_OFFSET,
                          gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y, "RACE", ALIGN_TOP_LEFT);
                hud_timer_render(gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x + FINISH_TIME_OFFSET,
                                 gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y,
                                 gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.minutes,
                                 gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.seconds,
                                 gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.hundredths, 1);
                draw_text(&gHudDL, gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x - FINISH_TEXT_OFFSET,
                          gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.y, "LAP", ALIGN_TOP_LEFT);
                hud_timer_render(gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x + FINISH_TIME_OFFSET,
                                 gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.y,
                                 gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.minutes,
                                 gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.seconds,
                                 gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.hundredths, 1);
            } else {
                draw_text(&gHudDL, gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x - 35,
                          gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y, DID_NOT_FINISH, ALIGN_TOP_LEFT);
            }
        }
    }
}

void hud_race_finish_multiplayer(Object_Racer *racer, s32 updateRate) {
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
    if (is_in_two_player_adventure() && is_postrace_viewport_active() && gAdventurePlayerFinish == FALSE) {
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
        gAdventurePlayerFinish = TRUE;
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
                temp_v0_4 = 0;
                for (updateRate = 0; temp_v0_4 < curLevelHeader->laps; updateRate++, temp_v0_4++) {
                    totalRaceTime += racer->lap_times[updateRate];
                    if (racer->lap_times[updateRate] < fastestLapTime) {
                        fastestLapTime = racer->lap_times[updateRate];
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
            temp_v0_4 = (updateRate * 13);
            if (gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].pos.x <
                (gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.targetPos - temp_v0_4) + 160) {
                var_v1 = temp_v0_4;
                var_a2 = FALSE;
            } else {
                var_v1 = (gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.targetPos + 160) -
                         gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].pos.x;
            }
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].pos.x += var_v1;
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_2].pos.x += var_v1;
            if (gNumActivePlayers != 1) {
                if (gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x >
                    (gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.unk1D + temp_v0_4 + 160)) {
                    var_v1 = temp_v0_4;
                    var_a2 = FALSE;
                } else {
                    var_v1 = gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x -
                             (gCurrentHud->entry[HUD_RACE_TIME_NUMBER].timer.unk1D + 160);
                }
                gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x -= var_v1;
                var_v1 = temp_v0_4;
                if (gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x <
                    (gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.unk1D - var_v1) + 160) {
                    var_a2 = FALSE;
                } else {
                    var_v1 = (gCurrentHud->entry[HUD_LAP_TIME_TEXT].timer.unk1D + 160) -
                             gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x;
                }
                gCurrentHud->entry[HUD_LAP_TIME_TEXT].pos.x += var_v1;
            }
            if (var_a2) {
                gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.status = 2;
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
                        hud_time_trial_message(&racer->playerIndex);
                    }
                }
            }
            hud_finish_position(racer);
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
            hud_finish_position(racer);
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
            hud_finish_position(racer);
            break;
        case 4:
            if (racer->playerIndex == gHudAudioData[0].playerIndex) {
                gHudAudioData[0].volumeRamp = -1;
            }
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.status = 5;
            gCurrentHud->entry[HUD_CHALLENGE_FINISH_POS_1].raceFinishPos.textOutTimer = 0;
            hud_finish_position(racer);
            break;
        default:
            hud_finish_position(racer);
            break;
    }
}

/**
 * Play the normal race finish message, unless you beat your time record,
 * then T.T will say "Race Record" instead.
 */
void hud_time_trial_message(s16 *playerID) {
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
void hud_time_trial_finish(Object_Racer *racer, s32 updateRate) {
    UNUSED s32 temp;

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
            temp = (updateRate * 13); // Fakematch
            if (gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x <
                gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos - (updateRate * 13)) {
                gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x += updateRate * 13;
            } else {
                gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x =
                    gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos;
                gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.status = TIMETRIAL_FINISH_SHOW;
                gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.fadeTimer = -120;
                if (gHUDVoiceSoundMask == NULL && gHudTimeTrialGhost == FALSE) {
                    hud_time_trial_message(&racer->playerIndex);
                }
            }
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_RACE_END_FINISH]);
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
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_RACE_END_FINISH]);
            break;
        case TIMETRIAL_FINISH_OUT:
            gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x -= updateRate * 13;
            if (gCurrentHud->entry[HUD_RACE_END_FINISH].pos.x <
                gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.targetPos) {
                gCurrentHud->entry[HUD_RACE_END_FINISH].finishText.status = TIMETRIAL_FINISH_IDLE;
            }
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_RACE_END_FINISH]);
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
 * Has a case for when in the balloon cutscene, where it will visually increase the count by one.
 */
void hud_balloons(UNUSED Object_Racer *racer) {
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
        gCurrentHud->entry[HUD_BALLOON_COUNT_ICON].spriteID =
            HUD_SPRITE_BALLOON_DIAMOND; // Use the adventure two balloon sprite.
    }
    if (cutscene_id() == 10 && get_balloon_cutscene_timer() < balloonTickTimer) {
        balloonCount = *settings->balloonsPtr - 1;
    } else {
        balloonCount = *settings->balloonsPtr;
        if (cutscene_id() == 10) {
            if (get_balloon_cutscene_timer() < balloonTickTimer + 8 && gHudBalloonSoundMask == NULL) {
                sound_play(SOUND_HUD_LAP_TICK, &gHudBalloonSoundMask);
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
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BALLOON_COUNT_NUMBER_2]);
    } else {
        gCurrentHud->entry[HUD_BALLOON_COUNT_NUMBER_1].spriteOffset = balloonCount % 10;
    }
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BALLOON_COUNT_NUMBER_1]);
    enable_pal_viewport_height_adjust(TRUE);
    if (osTvType == OS_TV_TYPE_PAL) {
        sprite_opaque(TRUE);
    }
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BALLOON_COUNT_ICON]);
    sprite_opaque(FALSE);
    enable_pal_viewport_height_adjust(FALSE);
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_BALLOON_COUNT_X]);
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
void hud_weapon(Object *obj, s32 updateRate) {
    Object_Racer *racer;
    s32 temp_a0;

    racer = &obj->unk64->racer;
    if (racer->raceFinished == FALSE) {
        enable_pal_viewport_height_adjust(TRUE);
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
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].rotation.z_rotation =
                    gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation * 0x1000;
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale =
                    (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation * 0.04687) + 0.25;
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
                        0.18 *
                        sins_f(((f32) gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.scale * 682.6583 * 4.0));
                }
            }
            if (gHUDNumPlayers > ONE_PLAYER) {
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale *= 0.75;
            }
            if (gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale != 1.0) {
                sprite_opaque(TRUE);
            }
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_WEAPON_DISPLAY]);
            sprite_opaque(FALSE);
            if (racer->balloon_quantity > 3) {
                gCurrentHud->entry[HUD_WEAPON_QUANTITY].weaponDisplay.hideTimer = -128;
            }
            if (racer->balloon_quantity < 3) {
                gCurrentHud->entry[HUD_WEAPON_QUANTITY].weaponDisplay.hideTimer -= updateRate;
            }
            if (racer->balloon_quantity >= 3 ||
                ((((gCurrentHud->entry[HUD_WEAPON_QUANTITY].weaponDisplay.hideTimer + 128) % 32) < 20) &&
                 racer->balloon_quantity != 1)) {
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 160);
                gCurrentHud->entry[HUD_WEAPON_QUANTITY].spriteOffset = racer->balloon_quantity - 1;
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_WEAPON_QUANTITY]);
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
            }
        } else {
            if (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation > 0) {
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].rotation.z_rotation =
                    gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation * 0x1000;
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale =
                    (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation * 0.04687) + 0.25;
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation -= updateRate;
                gCurrentHud->entry[HUD_WEAPON_DISPLAY].spriteOffset = temp_a0;
                if (gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation < 0) {
                    gCurrentHud->entry[HUD_WEAPON_DISPLAY].weaponDisplay.rotation = 0;
                }
                if (gHUDNumPlayers != ONE_PLAYER) {
                    gCurrentHud->entry[HUD_WEAPON_DISPLAY].scale /= 2;
                }
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_WEAPON_DISPLAY]);
            }
        }
        gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
        enable_pal_viewport_height_adjust(FALSE);
    }
}

/**
 * If currently using a magnet, render a reticle over the racer that's being targeted.
 */
void hud_magnet_reticle(Object *racerObj) {
    Sprite *entry;
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
        viewport_main(&gHudDL, &gHudMtx);
        mtx_world_origin(&gHudDL, &gHudMtx);
        render_sprite_billboard(&gHudDL, &gHudMtx, &gHudVtx, (Object *) hud, entry, RENDER_Z_UPDATE);
    }
}

/**
 * Render the lap time on the top right.
 * When the player begins a new lap, start flashing the previous lap time below instead.
 */
void hud_race_time(Object_Racer *racer, s32 updateRate) {
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
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_RACE_TIME_LABEL]);
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
                hundredths =
                    gCurrentHud->entry[HUD_RACE_TIME_LABEL].raceTimeLabel.hundredths + ((hundredths / 10) * 10);
                gCurrentHud->entry[HUD_RACE_TIME_LABEL].raceTimeLabel.hundredths++;
                if (gCurrentHud->entry[HUD_RACE_TIME_LABEL].raceTimeLabel.hundredths >= 10) {
                    gCurrentHud->entry[HUD_RACE_TIME_LABEL].raceTimeLabel.hundredths = 0;
                }
            }

            if (gNumActivePlayers == 1) {
                hud_timer_render(gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x,
                                 gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y, minutes, seconds, hundredths, FALSE);
            } else {
                hud_timer_render(gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.x,
                                 gCurrentHud->entry[HUD_RACE_TIME_NUMBER].pos.y, minutes, seconds, hundredths, TRUE);
            }
            gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, 255);
        }
    }
}

/**
 * Render a time in minutes, seconds and hundredths of a second.
 * Supports a smaller font for multiplayer.
 */
void hud_timer_render(s32 x, s32 y, s32 minutes, s32 seconds, s32 hundredths, s32 smallFont) {
    UNUSED s32 pad;
    HudElementBase entry;
    s32 offset1;
    s32 offset2;
    s32 offset3;
    s32 offsetY;
    s32 numbers;
    s32 seperator;

    entry.x = x;
    entry.y = y;
    entry.z_rotation = 0;
    entry.x_rotation = 0;
    entry.y_rotation = 0;
    entry.scale = 1.0f;
    entry.z = 0.0f;
    if (!smallFont) { // The below offsets are applied after drawing their respective elements.
        offset1 = 11; // Offset for the first number
        offset2 = 10; // Offset for the second number
        offset3 = 10; // Offset for the seperator
        offsetY = 2;  // Offset used for the seperator.
        numbers = HUD_ASSET_NUMBERS;
        seperator = HUD_ASSET_SEPERATOR; // :
    } else {
        offset1 = 10;
        offset2 = 8;
        offset3 = 7;
        offsetY = 0; // Small font is the same height
        numbers = HUD_ASSET_NUMBERS_SMALL;
        seperator = HUD_ASSET_SEPERATOR_SMALL; // :
    }
    entry.spriteID = numbers;
    entry.spriteOffset = minutes / 10;
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, (HudElement *) &entry);
    entry.x += offset1;
    entry.spriteOffset = minutes % 10;
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, (HudElement *) &entry);
    entry.spriteOffset = 0;
    entry.x += offset2;
    entry.y += offsetY;
    entry.spriteID = seperator;
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, (HudElement *) &entry);
    entry.spriteID = numbers;
    entry.x += offset3;
    entry.y -= offsetY;
    entry.spriteOffset = seconds / 10;
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, (HudElement *) &entry);
    entry.x += offset1;
    entry.spriteOffset = seconds % 10;
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, (HudElement *) &entry);
    entry.spriteOffset = 0;
    entry.x += offset2;
    entry.y += offsetY;
    entry.spriteID = seperator;
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, (HudElement *) &entry);
    entry.spriteID = numbers;
    entry.x += offset3;
    entry.y -= offsetY;
    entry.spriteOffset = hundredths / 10;
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, (HudElement *) &entry);
    entry.x += offset1;
    entry.spriteOffset = hundredths % 10;
    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, (HudElement *) &entry);
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
    model->minimapSpriteIndex = (s32) tex_load_sprite(model->minimapSpriteIndex, 1);
}

/**
 * Returns the hud settings value for the mumber of active players.
 * For player 1, it's switching between the minimap and speedometre.
 * For 2 players, it's for toggling the minimap
 * For 3 players, it's for toggling between the minimap and a spectator cam in viewport 4.
 * For 4 players, it's for toggling the minimap.
 */
s8 hud_setting(void) {
    return gHudToggleSettings[gHUDNumPlayers];
}

/**
 * Renders HUD elements concerning all players.
 * This includes the minimap and score counters for challenge modes.
 */
void hud_render_general(Gfx **dList, Mtx **mtx, Vertex **vtx, s32 updateRate) {
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
    UNUSED s32 pad0[2];
    s32 temp_s1_2;
    s32 var_a0_5;
    s32 spF4;
    s32 spF0;
    s32 tempVar1;
    s32 temp_s1_3;
    s32 spE4;
    s32 spE0;
    UNUSED s32 pad1;
    Object *temp_v0_8;
    s32 tempVar2;
    s32 sp144;
    s32 racerCount;
    UNUSED s32 pad2;
    Camera *someObjSeg;
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
                if ((gAssetHudElementIds[i] & ASSET_MASK_TEXTURE) == ASSET_MASK_TEXTURE) {
                    tex_free((TextureHeader *) gAssetHudElements->entry[i]);
                } else if (gAssetHudElementIds[i] & ASSET_MASK_SPRITE) {
                    sprite_free((Sprite *) gAssetHudElements->entry[i]);
                } else if (gAssetHudElementIds[i] & ASSET_MASK_OBJECT) {
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
    gHudDL = *dList;
    gHudMtx = *mtx;
    gHudVtx = *vtx;
    if (gHudLevelHeader->race_type == RACETYPE_CHALLENGE_EGGS) {
        if (gNumActivePlayers == 2 && gHudToggleSettings[gHUDNumPlayers] == 0) {
            hud_draw_eggs(NULL, updateRate);
            rendermode_reset(&gHudDL);
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
            mtx_ortho(&gHudDL, &gHudMtx);
            func_800A1E48(0, updateRate);
            sprite_anim_off(FALSE);
            rendermode_reset(&gHudDL);
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
                    mtx_ortho(&gHudDL, &gHudMtx);
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
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].spriteID =
                        curRacerObj->characterId + HUD_SPRITE_PORTRAIT;
                    if (osTvType == OS_TV_TYPE_PAL) {
                        gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x -= 4.0f;
                        gCurrentHud->entry[HUD_EGG_CHALLENGE_ICON].pos.x -= 4.0f;
                    }
                    gHudPALScale = TRUE;
                    hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT]);
                    gHudPALScale = FALSE;
                    if (gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].bananaCountIconSpin.visualCounter == 0 &&
                        curRacerObj->bananas == 10) {
                        gCurrentHud->entry[HUD_BANANA_COUNT_ICON_SPIN].bananaCountIconSpin.visualCounter =
                            curRacerObj->bananas;
                    }
                    hud_bananas(curRacerObj, updateRate);
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
                    rendermode_reset(&gHudDL);
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
                someRacer = &racerGroup[sp144]->unk64->racer;
                hud_treasure(someRacer);
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
                    gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y =
                        (s32) gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y;
                    gCurrentHud->entry[HUD_TREASURE_METRE].pos.y = (s32) gCurrentHud->entry[HUD_TREASURE_METRE].pos.y;
                }
                hud_treasure(tempVar4);
                gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.x = temp_s0_3;
                gCurrentHud->entry[HUD_CHALLENGE_PORTRAIT].pos.y = temp_s1_3;
                gCurrentHud->entry[HUD_TREASURE_METRE].pos.x = temp_f16;
                gCurrentHud->entry[HUD_TREASURE_METRE].pos.y = temp_f6;
            }
        }
    }
    if (D_80127180 != 0) {
        gHudSprites[D_80127180].texture = NULL;
        texrect_draw(&gHudDL, gHudSprites, 0, 0, 255, 255, 255, 255);
    }
    *dList = gHudDL;
    *mtx = gHudMtx;
    *vtx = gHudVtx;
    if ((gHudLevelHeader->unkBC & 1)) {
        return;
    }

    sp113 = TRUE;
    for (i = 0; i < objectCount; i++) {
        someRacer = &objectGroup[i]->unk64->racer;
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
    }

    rendermode_reset(&gHudDL);
    mtx_ortho(&gHudDL, &gHudMtx);
    lvlMdl = get_current_level_model();
    if (lvlMdl == NULL) {
        return;
    }
    someObjSeg = cam_get_active_camera();
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
        gDPSetPrimColor(gHudDL++, 0, 0, 255, 255, 255, mapOpacity);
    } else {
        gDPSetPrimColor(gHudDL++, 0, 0, gMinimapRed, gMinimapGreen, gMinimapBlue, mapOpacity);
    }
    render_ortho_triangle_image(&gHudDL, &gHudMtx, &gHudVtx, (ObjectSegment *) &hudElem, minimap, 0);
    sp11C = (lvlMdl->upperXBounds - lvlMdl->lowerXBounds) / (f32) (lvlMdl->upperZBounds - lvlMdl->lowerZBounds);
    sp118 = coss_f((lvlMdl->minimapRotation * 0xFFFF) / 360);
    sp114 = sins_f((lvlMdl->minimapRotation * 0xFFFF) / 360);
    if (is_in_time_trial() && timetrial_valid_player_ghost()) {
        temp_v0_8 = timetrial_player_ghost();
        if (temp_v0_8 != NULL) {
            minimap_marker_pos(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114, sp118,
                               sp11C);
            gCurrentHud->entry[HUD_MINIMAP_MARKER].spriteID = HUD_SPRITE_MAP_DOT;
            gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation = 0;
            gCurrentHud->entry[HUD_MINIMAP_MARKER].scale = 1.0f;
            tempVar1 = (opacity * (f32) temp_v0_8->segment.object.opacity) * (1.0 / 128.0);
            gDPSetPrimColor(gHudDL++, 0, 0, 60, 60, 60, tempVar1);
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_MINIMAP_MARKER]);
        }
    }
    temp_v0_8 = timetrial_ghost_staff();
    if (temp_v0_8 != NULL) {
        minimap_marker_pos(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114, sp118,
                           sp11C);
        gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation = 0;
        tempVar1 = (opacity * (f32) temp_v0_8->segment.object.opacity) * (1.0 / 128.0);
        gDPSetPrimColor(gHudDL++, 0, 0, gHudMinimapColours[8].red, gHudMinimapColours[8].green,
                        gHudMinimapColours[8].blue, tempVar1);
        gCurrentHud->entry[HUD_MINIMAP_MARKER].scale = 1.0f;
        gCurrentHud->entry[HUD_MINIMAP_MARKER].spriteID = HUD_SPRITE_MAP_DOT;
        hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_MINIMAP_MARKER]);
    }
    // Draw Taj's minimap icon.
    if (gHudLevelHeader->race_type == RACETYPE_HUBWORLD) {
        temp_v0_8 = find_taj_object();
        if (temp_v0_8 != NULL) {
            gCurrentHud->entry[HUD_MINIMAP_MARKER].spriteID = HUD_SPRITE_MAP_DOT;
            minimap_marker_pos(temp_v0_8->segment.trans.x_position, temp_v0_8->segment.trans.z_position, sp114, sp118,
                               sp11C);
            gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation = 0;
            gDPSetPrimColor(gHudDL++, 0, 0, 255, 0, 255, opacity);
            gCurrentHud->entry[HUD_MINIMAP_MARKER].scale = 1.0f;
            hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_MINIMAP_MARKER]);
        }
    }
    // Draw racer minimap icons.
    // Non AI players get an arrow instead of a blob that rotates.
    for (i = objectCount - 1; i >= 0; i--) {
        temp_v0_8 = objectGroup[i];
        someRacer = &objectGroup[i]->unk64->racer;
        if (someRacer != NULL) {
            minimap_marker_pos(objectGroup[i]->segment.trans.x_position, objectGroup[i]->segment.trans.z_position,
                               sp114, sp118, sp11C);
            if (someRacer->playerIndex != PLAYER_COMPUTER) {
                gCurrentHud->entry[HUD_MINIMAP_MARKER].pos.y -= 1.0f;
                gCurrentHud->entry[HUD_MINIMAP_MARKER].spriteID = HUD_SPRITE_MAP_ARROW;
                gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation =
                    (objectGroup[i]->segment.trans.rotation.y_rotation - ((lvlMdl->minimapRotation * 0xFFFF) / 360)) &
                    0xFFFF;

                if (get_filtered_cheats() & CHEAT_MIRRORED_TRACKS) {
                    gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation =
                        0xFFFF - gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation;
                }
                sprite_opaque(TRUE);
            } else {
                gCurrentHud->entry[HUD_MINIMAP_MARKER].rotation.z_rotation = 0;
                gCurrentHud->entry[HUD_MINIMAP_MARKER].spriteID = HUD_SPRITE_MAP_DOT;
            }
            if (is_taj_challenge() && someRacer->vehicleID == VEHICLE_CARPET) {
                gDPSetPrimColor(gHudDL++, 0, 0, 255, 0, 255, opacity);
            } else {
                gDPSetPrimColor(gHudDL++, 0, 0, gHudMinimapColours[someRacer->characterId].red,
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
                hud_element_render(&gHudDL, &gHudMtx, &gHudVtx, &gCurrentHud->entry[HUD_MINIMAP_MARKER]);
            }
            sprite_opaque(FALSE);
        }
    }
    gDPPipeSync(gHudDL++);
    sprite_anim_off(FALSE);
    sprite_opaque(TRUE);
    *dList = gHudDL;
    *mtx = gHudMtx;
    *vtx = gHudVtx;
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
        gCurrentHud->entry[HUD_MINIMAP_MARKER].pos.x =
            (gMinimapScreenX - ((scaledX * angleCos) + (scaledY * angleSin))) + lvlMdl->minimapOffsetXAdv2 -
            gMinimapDotOffsetX;
        gCurrentHud->entry[HUD_MINIMAP_MARKER].pos.y = (lvlMdl->minimapOffsetYAdv2 + gMinimapScreenY) -
                                                       ((scaledX * angleSin) - (scaledY * angleCos)) +
                                                       gMinimapDotOffsetY;
        return;
    }
    // Final x position on minimap
    gCurrentHud->entry[HUD_MINIMAP_MARKER].pos.x = gMinimapScreenX + ((scaledX * angleCos) + (scaledY * angleSin)) +
                                                   (f32) lvlMdl->minimapOffsetXAdv1 - gMinimapDotOffsetX;
    // Final y position on minimap
    gCurrentHud->entry[HUD_MINIMAP_MARKER].pos.y = (lvlMdl->minimapOffsetYAdv1 + gMinimapScreenY) -
                                                   ((scaledX * angleSin) - (scaledY * angleCos)) + gMinimapDotOffsetY;
}

/**
 * Renders a HUD element onscreen.
 * Loads the asset if it does not yet exist, and refreshes the stale counter to keep it loaded.
 * Since hud elements can be all sorts of things, the function checks what asset type it is, before
 * deciding to draw a texture rectangle, ortho tris, or a 3D model entirely.
 */
void hud_element_render(Gfx **dList, Mtx **mtx, Vertex **vtxList, HudElement *hud) {
    ObjectModel **objModels;
    TextureHeader *textureHeader2;
    TextureHeader *textureHeader;
    Camera *camera;
    LevelObjectEntry_Hud objEntry;
    UNUSED s32 pad1;
    Object *tempObject;
    HudDrawTexture sp88;
    UNUSED s32 pad2[3];
    HudDrawTexture sp70;
    s32 alpha;
    u32 colour;
    s32 spriteID;
    HudDrawTexture sp58;
    UNUSED s32 pad3;
    HudDrawTexture sp48;
    Sprite *sprite;
    UNUSED s32 pad4[2];
    s32 spriteElementId;

    spriteID = hud->spriteID;
    spriteElementId = gAssetHudElementIds[spriteID];
    if ((spriteElementId & ASSET_MASK_TEXTURE) == ASSET_MASK_TEXTURE) {
        objEntry.offsetY = -gMinimapOpacity;
    } else {
        objEntry.offsetY = gMinimapOpacity;
    }

    if (gAssetHudElements->entry[spriteID] == NULL) {
        if ((spriteElementId & ASSET_MASK_TEXTURE) == ASSET_MASK_TEXTURE) {
            gAssetHudElements->entry[hud->spriteID] = load_texture(spriteElementId & 0x3FFF);
        } else if (spriteElementId & ASSET_MASK_SPRITE) {
            gAssetHudElements->entry[hud->spriteID] = tex_load_sprite(spriteElementId & 0x3FFF, 1);
        } else if (spriteElementId & ASSET_MASK_OBJECT) {
            objEntry.common.objectID = spriteElementId & 0xFF;
            objEntry.common.size = ((gAssetHudElementIds[hud->spriteID] & 0x100) >> 1) | sizeof(LevelObjectEntryCommon);
            objEntry.common.x = 0;
            objEntry.common.y = 0;
            objEntry.common.z = 0;
            gAssetHudElements->entry[hud->spriteID] = spawn_object((LevelObjectEntryCommon *) &objEntry, 0);
        } else {
            gAssetHudElements->entry[hud->spriteID] = object_model_init(spriteElementId, 0);
        }

        spriteID = hud->spriteID;
        if (gAssetHudElements->entry[spriteID] == NULL) {
            return;
        }
    }

    gAssetHudElementStaleCounter[spriteID] = 0;

    gHudDL = *dList;
    gHudMtx = *mtx;
    gHudVtx = *vtxList;
    spriteID = hud->spriteID;
    if (spriteID != HUD_SPEEDOMETRE_30) {
        if (spriteID != HUD_RACE_END_FINISH && spriteID != HUD_BANANA_COUNT_ICON_STATIC &&
            (spriteID < HUD_CHALLENGE_FINISH_POS_1 || spriteID >= HUD_BATTLE_BANANA_COUNT_1) &&
            spriteID != HUD_SILVER_COIN_TALLY && gMinimapXlu & 1) {
            hud->pos.y += objEntry.offsetY;
        }
        hud->pos.x += gHudOffsetX + gHudBounceX;
    }
    spriteID = hud->spriteID;
    if ((gAssetHudElementIds[spriteID] & ASSET_MASK_TEXTURE) == ASSET_MASK_TEXTURE) {
        if (spriteID >= HUD_CHALLENGE_FINISH_POS_1 && spriteID < HUD_BATTLE_BANANA_COUNT_1) {
            if (osTvType == OS_TV_TYPE_PAL) {
                hud->pos.y -= 8.0f;
            }

            if (gMinimapXlu & 2) {
                alpha = 255.0f - ((gMinimapOpacity * 255.0f) / gMinimapOpacityTarget);
            } else {
                alpha = 255;
            }
            spriteID = hud->spriteID;
            textureHeader = gAssetHudElements->entry[spriteID];
            textureHeader = (TextureHeader *) (((u8 *) textureHeader) + hud->spriteOffset * textureHeader->textureSize);
            sp88.drawTexture.texture = textureHeader;
            sp88.drawTexture.xOffset = hud->pos.x;
            sp88.drawTexture.yOffset = hud->pos.y;
            sp88.unk8 = 0;
            if (osTvType == OS_TV_TYPE_PAL) {
                if (hud->spriteID == HUD_BATTLE_BANANA_X) {
                    if (alpha == 255) {
                        colour = COLOUR_RGBA32(255, 255, 255, 254);
                    } else {
                        colour = COLOUR_RGBA32(255, 255, 255, alpha);
                    }
                    sp88.drawTexture.xOffset = 0;
                    sp88.drawTexture.yOffset = 0;
                    texrect_draw_scaled(&gHudDL, &sp88.drawTexture, hud->pos.x, hud->pos.y, 1.0f, 1.1f, colour,
                                        TEXRECT_POINT);
                } else {
                    texrect_draw(&gHudDL, &sp88.drawTexture, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
                }
            } else {
                texrect_draw(&gHudDL, &sp88.drawTexture, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
            }
            if (osTvType == OS_TV_TYPE_PAL) {
                hud->pos.y += 8.0f;
            }
        } else if (gHudPALScale && osTvType == OS_TV_TYPE_PAL) {
            textureHeader = gAssetHudElements->entry[spriteID];
            textureHeader = (TextureHeader *) (((u8 *) textureHeader) + hud->spriteOffset * textureHeader->textureSize);
            sp70.drawTexture.texture = textureHeader;
            sp70.drawTexture.xOffset = 0;
            sp70.drawTexture.yOffset = 0;
            sp70.unk8 = 0;
            texrect_draw_scaled(&gHudDL, &sp70.drawTexture, hud->pos.x, hud->pos.y, hud->scale, hud->scale * 1.1,
                                gHudColour, TEXRECT_POINT);
        } else if (hud->scale == 1.0) {
            textureHeader2 = gAssetHudElements->entry[spriteID];
            textureHeader2 =
                (TextureHeader *) (((u8 *) textureHeader2) + hud->spriteOffset * textureHeader2->textureSize);
            if (gHudColour == COLOUR_RGBA32(255, 255, 255, 254)) {
                gHudSprites[D_80127180].texture = textureHeader2;
                gHudSprites[D_80127180].xOffset = hud->pos.x;
                gHudSprites[D_80127180].yOffset = hud->pos.y;
                D_80127180++;
            } else {
                sp58.drawTexture.texture = textureHeader2;
                sp58.drawTexture.xOffset = hud->pos.x;
                sp58.drawTexture.yOffset = hud->pos.y;
                sp58.unk8 = 0;
                texrect_draw(&gHudDL, &sp58.drawTexture, 0, 0, (gHudColour >> 24) & 0xFF, (gHudColour >> 16) & 0xFF,
                             (gHudColour >> 8) & 0xFF, gHudColour & 0xFF);
                rendermode_reset(&gHudDL);
            }
        } else {
            textureHeader = gAssetHudElements->entry[spriteID];
            textureHeader = (TextureHeader *) (((u8 *) textureHeader) + hud->spriteOffset * textureHeader->textureSize);
            sp48.drawTexture.texture = textureHeader;
            sp48.drawTexture.xOffset = 0;
            sp48.drawTexture.yOffset = 0;
            sp48.unk8 = 0;
            texrect_draw_scaled(&gHudDL, &sp48.drawTexture, hud->pos.x, hud->pos.y, hud->scale, hud->scale, gHudColour,
                                TEXRECT_POINT);
            rendermode_reset(&gHudDL);
        }
    } else if (gAssetHudElementIds[spriteID] & ASSET_MASK_SPRITE) {
        camera = cam_get_active_camera();
        sprite = gAssetHudElements->entry[hud->spriteID];
        hud->rotation.z -= camera->trans.rotation.z;
        render_ortho_triangle_image(&gHudDL, &gHudMtx, &gHudVtx, (ObjectSegment *) hud, sprite, 0);
        hud->rotation.z += camera->trans.rotation.z;
    } else if (gAssetHudElementIds[spriteID] & ASSET_MASK_OBJECT) {
        tempObject = gAssetHudElements->entry[spriteID];
        tempObject->segment.trans.rotation.x = hud->rotation.x;
        tempObject->segment.trans.rotation.y = hud->rotation.y;
        tempObject->segment.trans.rotation.z = hud->rotation.z;
        tempObject->segment.trans.x_position = hud->pos.x;
        tempObject->segment.trans.y_position = hud->pos.y;
        tempObject->segment.trans.z_position = hud->pos.z;
        tempObject->segment.trans.scale = hud->scale;
        tempObject->segment.object.modelIndex = 0;
        tempObject->segment.object.opacity = 0xFF;
        render_object(&gHudDL, &gHudMtx, &gHudVtx, tempObject);
    } else {
        mtx_cam_push(&gHudDL, &gHudMtx, (ObjectTransform *) hud, 1.0f, 0.0f);
        if (0) {}
        objModels = gAssetHudElements->entry[hud->spriteID];
        hud_draw_model(*objModels);
        mtx_pop(&gHudDL);
    }
    spriteID = hud->spriteID;
    if (spriteID != HUD_SPRITE_PRO_AM) {
        if (spriteID != HUD_SPRITE_MAP_DOT && spriteID != HUD_SPRITE_MAP_ARROW &&
            (spriteID < HUD_ASSET_47 || spriteID >= HUD_ASSET_54) && spriteID != HUD_SPRITE_SPEEDOMETRE_ARROW &&
            gMinimapXlu & 1) {
            hud->pos.y -= objEntry.offsetY;
        }
        hud->pos.x -= gHudOffsetX + gHudBounceX;
    }
    *dList = gHudDL;
    *mtx = gHudMtx;
    *vtxList = gHudVtx;
}

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
            material_set_no_tex_offset(&gHudDL, texPtr, flags & ~RENDER_Z_COMPARE);
            gSPVertexDKR(gHudDL++, OS_K0_TO_PHYSICAL(verts), numVerts, 0);
            if (texPtr == NULL) {
                textureEnabled = TRIN_DISABLE_TEXTURE;
            }
            gSPPolygon(gHudDL++, OS_K0_TO_PHYSICAL(tris), numTris, textureEnabled);
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
