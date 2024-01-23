/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007F900 */

#include "menu.h"
#include "memory.h"
#include "fade_transition.h"

#include <PR/os_cont.h>
#include "asset_enums.h"
#include "types.h"
#include "macros.h"
#include "structs.h"
#include "f3ddkr.h"
#include "video.h"
#include "audio.h"
#include "camera.h"
#include "font.h"
#include "game_text.h"
#include "object_models.h"
#include "printf.h"
#include "textures_sprites.h"
#include "thread30_track_loading.h"
#include "objects.h"
#include "game.h"
#include "rcp.h"
#include "save_data.h"
#include "object_functions.h"
#include "audiosfx.h"
#include "racer.h"
#include "tracks.h"
#include "lib/src/mips1/al/alSynStartVoiceParams.h"
#include "controller.h"

/**
 * @file Contains all the code used for every menu in the game.
 */

/************ .bss ************/

// The bss section needs to stay above the data section!
// Otherwise the bss variables will get reordered, which is bad.

char D_80126390[4]; // course initials
char D_80126394[4]; // flap initials
s32 gSaveGhostDelayCounter;
s32 gPreviousMenuID;
Gfx *sMenuCurrDisplayList;
char **gTTSaveGhostPakErrorText;
MatrixS *sMenuCurrHudMat;
Vertex *sMenuCurrHudVerts;
TriangleList *sMenuCurrHudTris;
unk801263C0 gMenuSelectedCharacter;
unk801263C0 D_801263B8;
s32 gOptionBlinkTimer;
unk801263C0 gMenuCurrentCharacter;

s32 gIgnorePlayerInputTime;  // A set amount of time to ignore player input.
UNUSED s32 sUnused_801263C8; // Set to 0 in menu_init, and never again.
CharacterSelectData (
    *gCurrCharacterSelectData)[10]; // Some sort of character list? Cares if T.T. and Drumstick are unlocked

s32 D_801263D0;                         // Compared for equality to gTrackIdForPreview
s8 gActivePlayersArray[MAXCONTROLLERS]; // Boolean value for each controller if it's active with a player.
s32 gOpacityDecayTimer;
s8 D_801263DC[MAXCONTROLLERS];
s32 gMenuOptionCount;
s32 D_801263E4;
s8 gPlayersCharacterArray[8]; // -1 = Non active player, or character id if >= 0
s8 gCharacterIdSlots[8];
s32 D_801263F8[8];
u8 D_80126418[8];
u8 D_80126420[8];
u8 D_80126428[8];
u8 D_80126430[8]; // Contains the order of racer indices that tell you what place they are in.
s8 D_80126438[16];

// Eeeprom save data bits stored at address 0xF
// bit 0      = Adventure Two is Unlocked
// bit 1      = Used to set the CHEAT_CONTROL_DRUMSTICK magic code flag. Drumstick is unlocked flag?
// bits 2-3   = Current language value
// bits 4-23  = Used to set the CHEAT_CONTROL_TT magic code flag. Could be tracks where TT has been beat?
// bit 24     = Unknown, but it's set as a default high bit.
// bit 25     = Seems to be a flag for whether subtitles are enabled or not.
// bits 26-55 = Unknown, but it could be a set of flags for unlocked tracks
// bits 56-63 = Checksum bits. These are calculated from the previous bits,
//              and validated using calculate_eeprom_settings_checksum.
//              If the checksum fails, the settings are reset to just
//              bits 24/25 being high.
u64 sEepromSettings;

f32 sBootScreenTimer;
s8 gControllersXAxisDelay[4];
s8 gControllersYAxisDelay[4];
s8 gControllersXAxisDirection[4]; // X axis (-1 = left, 1 = right) for controller
MenuElement *gGameSelectElements;
s8 gControllersYAxisDirection[4]; // Y axis (-1 = down, 1 = up) for controller
s8 gControllersXAxis[4];
s8 gControllersYAxis[4];
s32 sUnused_80126470; // Set to 0 in the magic codes menu and 0xD000 elsewhere, otherwise unused.
s32 gTrackSelectViewPortHalfX;
s32 gTrackSelectViewPortHalfY;
s32 gTrackSelectViewPortX;
s32 gTrackSelectViewportY;
s32 D_80126484;
s32 D_80126488;
s32 gSaveFileIndex3;
s32 gSaveFileIndex2;
s32 D_80126494;
s32 D_80126498;
s32 D_8012649C;

SavefileInfo gSavefileInfo[4];

s32 D_801264D0;
s32 D_801264D4; // Count of elements in some arrays?  D_80126540, D_80126508, D_80126510, D_80126518, D_80126520?
s8 gDialogueSubmenu;
u8 D_801264DC[4]; // gGhostLevelIDs?
s8 D_801264E0;
s8 D_801264E1;

s8 sCurrentMenuID;
u8 D_801264E4[4]; // gGhostSomethings?
s32 D_801264E8;
u8 D_801264EC[4]; // gGhostVehicleIds?
s32 D_801264F0[2];
u16 D_801264F8[6]; // gGhostChecksums?
s8 sDialogueOptionMax;
u8 D_80126508[6];
s8 gDialogueOptionYOffset;
u8 D_80126510[6];
s8 gDialogueItemSelection;
u8 D_80126518[6];
u16 D_80126520[6];
Settings *gSavefileData[4];
u8 D_80126540[8];
s32 gMultiplayerSelectedNumberOfRacersCopy; // Saved version gMultiplayerSelectedNumberOfRacers?
void *gMenuObjects[128]; // lookup table? Contains Textures, Objects, and Sprites. Need to change name and type.
u8 D_80126750[128];      // Seems to be a boolean for "This texture exists" for the above array.
s32 D_801267D0;
s32 D_801267D4;
s32 D_801267D8[5]; // Buttons pressed per player plus an extra?
s8 *D_801267EC;
s32 D_801267F0[5];
s8 *D_80126804;
s32 D_80126808[MAXCONTROLLERS]; // Soundmask values
s16 D_80126818[5];
s32 D_80126824;
UNUSED s8 sUnused_80126828; // Set to 0 in menu_init, and never used again.
s32 D_8012682C;
s16 D_80126830[5];
s16 D_8012683A;
s32 D_8012683C;
s32 D_80126840;
s32 D_80126844;
s32 D_80126848;
s32 D_8012684C;
s32 *D_80126850; // Never set, but it's read? Is it part of a larger struct being set?
s32 D_80126854;
s32 D_80126858;
s32 D_8012685C;
s32 D_80126860;
s32 gTitleDemoIndex;
s16 gTitleDemoTimer;
s32 gTitleRevealTimer;
f32 gTitleAudioCounter;
s8 *sTitleScreenDemoIds; // Misc Asset 66 - title_screen_demo_ids.bin - 12 or 13 values.
unk80126878 D_80126878[8];
f32 D_801268D8;
s32 D_801268DC;
s32 D_801268E0;
s32 D_801268E4;
s16 D_801268E8[4][6]; // Track Select values?
s16 gFFLUnlocked;
UNUSED s32 D_8012691C;
UNUSED s32 D_80126920;
s32 D_80126924;
s32 D_80126928;
s32 D_8012692C;
TrackRenderDetails gTrackSelectRenderDetails[9];
s8 gPlayerSelectVehicle[4]; // Unknown number of entries.
s8 D_801269C4[4];
s32 D_801269C8;
s32 D_801269CC;
char *gAudioOutputStrings[3];
f32 gTrackSelectX;
char *gMusicTestString;
f32 gTrackSelectY;
f32 D_801269E8;
f32 D_801269EC;
char *D_801269F0;
s32 gSelectedTrackX;
s32 gSelectedTrackY;
s32 *D_801269FC;
s32 D_80126A00;
SaveFileData *D_80126A04;
s32 D_80126A08;
SaveFileData *D_80126A0C;
s32 D_80126A10;
s32 D_80126A14;
s32 D_80126A18;
s32 D_80126A1C;
s32 sControllerPakNotesFree[MAXCONTROLLERS]; // Looks to be an array for number notes free in each controller memory pak
u8 sControllerPakIssueNotFound[MAXCONTROLLERS];   // Flag to see if there's no known issues for the given controller pak
u8 sControllerPakFatalErrorFound[MAXCONTROLLERS]; // Flag to see if there's a fatal error for the given controller pak
u8 sControllerPakNoFreeSpace[MAXCONTROLLERS];     // Flag to see if there's no free space for the given controller pak
u8 sControllerPakBadData[MAXCONTROLLERS];         // Flag to see if there's bad data for the given controller pak
char *gMenuOptionText[8];                         // Menu Text
u8 sControllerPakDataPresent[MAXCONTROLLERS]; // Flag to see if there's data present for the given controller pak? Not
                                              // sure
char *D_80126A64;
s32 gMenuOption; // sCurrentControllerIndex?
s32 D_80126A6C;
char **gDeviceStatusStrings;
s32 D_80126A74;
s32 D_80126A78;
s32 D_80126A7C;
unk80126A80 *D_80126A80[4];
s32 D_80126A90;
s32 D_80126A94;
s32 D_80126A98;
s32 D_80126A9C;
char *D_80126AA0[16];                           // Text to render
u8 *sCurrentControllerPakAllFileNames[16];      // Every file name on the controller pak
u8 *sCurrentControllerPakAllFileExtensions[16]; // Every file extension on the controller pak
u8 sCurrentControllerPakAllFileTypes[16];       // File type of all files on controller pak
u32 sCurrentControllerPakAllFileSizes[16];      // File size of all files on controller pak
u32 sCurrentControllerPakFreeSpace;             // Space available in current controller pak
s32 sControllerPakMenuNumberOfRows;             // 8 if PAL, 7 if not
TextureHeader *D_80126BB8;
TextureHeader *D_80126BBC;
s32 D_80126BC0;
s32 D_80126BC4;
PakError sControllerPakError; // 0 = no error, 1 = fatal error, 2 = no free space, 3 = bad data
s32 D_80126BCC;
s32 D_80126BD0;
s32 D_80126BD4;
s32 D_80126BD8;
f32 D_80126BDC;
s32 D_80126BE0;
s32 D_80126BE4;
s32 D_80126BE8;
f32 D_80126BEC;
char *gResultOptionText[8];
s32 D_80126C10;
s32 gResultOptionCount;
s32 gBootMenuTimer;
char **D_80126C1C;
s32 gBootMenuPhase;
s32 D_80126C24;
s8 D_80126C28;
unk80080BC8 (*D_80126C2C)[2];
u16 (*gCheatsAssetData)[30]; // Cheat table.
s32 D_80126C34;
s32 gNumberOfCheats;
s32 D_80126C3C;
s16 gCheatInputCurrentRow;
s16 gCheatInputCurrentColumn;
s16 gCheatInputStringLength;
s16 gOptionsMenuItemIndex;
s32 D_80126C48;
s16 D_80126C4C;
f32 D_80126C50;
unk80126C54 D_80126C54;
char D_80126C58[20];
s32 *D_80126C6C;
s32 gNumOnscreenMagicCodes;
char *D_80126C74; // gFileName?
s32 D_80126C78;
s32 D_80126C7C;
s16 D_80126C80[32];
s32 D_80126CC0;

/******************************/

/************ .data ************/

// A boolean, set to TRUE if player has entered trophy race through adventure mode.
s8 gInAdvModeTrophyRace = FALSE;

// Height scale of the wooden frames in the track select menu.
f32 gTrackSelectWoodFrameHeightScale = 1.0f;

s32 gResetTitleScale = 1;

s32 gTitleScreenCurrentOption = 0; // 0 = "Start", 1 = "Options"

// Currently selected index for all menus.
s32 gMenuCurIndex = 0;

s32 unused_800DF464 = 4;
s32 unused_800DF468 = 0;

// Used as a short delay before printing the missing controller text.
s32 gMissingControllerDelay = 0;

s32 gCurrentMenuId = 0;
s32 unused_800DF474 = 0;

// A boolean, set to TRUE when a track is loaded using gTrackIdToLoad.
s32 gTrackSpecifiedWithTrackIdToLoad = 0;

s32 gMenuDelay = 0;
s32 gNumberOfReadyPlayers = 0;
s32 D_800DF484 = 0;
s32 gTitleScreenLoaded = 0;
s32 unused_800DF48C = 0;
s32 unused_800DF490 = 0;
s32 gIsInAdventureTwo = 0;
s32 gPlayerHasSeenCautionMenu = 0;
s32 *gMenuTextLangTable = NULL;

char **gMenuText = NULL;

u8 sMenuGuiColourR = 0xFF;
u8 sMenuGuiColourG = 0xFF;
u8 sMenuGuiColourB = 0xFF;
u8 sMenuGuiColourBlendFactor = 0;

// Flags for menu/HUD sprites. Used in func_8009CA60()
// Seems like it doesn't matter what you set it as?
s32 gMenuSpriteFlags = 0;

s32 gIsInTracksMode = 1;
s32 gNumberOfActivePlayers = 1;
s32 gIsInTwoPlayerAdventure = 0;
s32 gTrackIdForPreview = ASSET_LEVEL_CENTRALAREAHUB;
s32 gTrackSelectRow = 0; // 1 = Dino Domain, 2 = Sherbet Island, etc.
s32 gSaveFileIndex = 0;
s32 unused_800DF4D0 = 0;
s32 gTrackIdToLoad = 0;
s8 unused_800DF4D8 = 1;
s8 gNextTajChallengeMenu = FALSE;
s8 gNeedToCloseDialogueBox = FALSE;

// Array of booleans, set to TRUE when you are done talking to an NPC.
// This has (atleast) 5 elements, not 4!
s8 gDoneTalkingToNPC[5] = {
    FALSE, // Taj
    FALSE, // Unused?
    FALSE, // T.T.
    FALSE, // Taj Challenge
    FALSE  // Trophy Cabinet
};

s8 gDialogueOptionTangible = FALSE;

s32 unused_800DF4F0[] = { 0x4000, 0x8000, 0x1000, 0x2000, 0x8000, 0x10, 0x400, 0x00 };

unk800DF510 sMenuImageProperties[18] = {
    { 0, 0, 0, 0x00, 1.0f, 0.0f, 0.0f, -32.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x01, 1.0f, 0.0f, 0.0f, -32.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x02, 1.0f, 0.0f, 0.0f, -32.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x03, 1.0f, 0.0f, 0.0f, -32.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x05, 0.215f, 0.0f, 0.0f, -500.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x06, 0.215f, 0.0f, 0.0f, -500.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x07, 0.215f, 0.0f, 0.0f, -500.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x04, 0.125f, 0.0f, -40.0f, -500.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x5B, 0.75f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x5C, 0.75f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x42, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x40, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x41, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x4C, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x4D, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x4E, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x4F, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x5D, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0 } },
};

s16 *gAssetsMenuElementIds[1] = { NULL };
s16 gMenuElementIdCount = 0;
s16 gMenuObjectsCount = 0;
unk800DF510 *gMenuImageStack = NULL;

s32 sMenuMusicVolume = 0x7F;
s32 sMenuGuiOpacity = 0xFF;
s32 unused_800DF768 = 1;

FadeTransition sMenuTransitionFadeInFast = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 10, -1);
FadeTransition sMenuTransitionFadeIn = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 18, -1);
FadeTransition sMenuTransitionFadeOut = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_OUT, FADE_COLOR_BLACK, 18, 0);
UNUSED FadeTransition sMenuTransitionFadeInWhite =
    FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_WHITE, 18, -1);
UNUSED FadeTransition sMenuTransitionFadeOutWhite =
    FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_OUT, FADE_COLOR_WHITE, 18, 0);

s32 gTrophyRankingsState = 4;
MenuElement *gTrophyRankingsMenuElements = NULL;
s32 gDrawElementsRegionYOffset = 0;
s32 gDrawElementsYOffset = 0;

char *gTitleMenuStrings[3] = { 0, 0, 0 };

// Version text shown on the title screen? See 1:15 in https://www.youtube.com/watch?v=OHSCLcA74ao.
char gVersionDisplayText[20] = "VERSION XXXXXXXX";

// "Diddy Kong Racing" logo texture indices
s16 sGameTitleTileTextures[12] = { TEXTURE_TITLE_SEGMENT_01, TEXTURE_TITLE_SEGMENT_02, TEXTURE_TITLE_SEGMENT_03,
                                   TEXTURE_TITLE_SEGMENT_04, TEXTURE_TITLE_SEGMENT_05, TEXTURE_TITLE_SEGMENT_06,
                                   TEXTURE_TITLE_SEGMENT_07, TEXTURE_TITLE_SEGMENT_08, TEXTURE_TITLE_SEGMENT_09,
                                   TEXTURE_TITLE_SEGMENT_10, TEXTURE_TITLE_SEGMENT_11, -1 };

DrawTexture sGameTitleTileOffsets[12] = { { NULL, -75, -32 }, { NULL, -60, -32 }, { NULL, -45, -32 },
                                          { NULL, -30, -32 }, { NULL, -15, -32 }, { NULL, 0, -32 },
                                          { NULL, 15, -32 },  { NULL, 30, -32 },  { NULL, 45, -32 },
                                          { NULL, 60, -32 },  { NULL, 75, -32 },  { NULL, 0, 0 } };

// Title screen cinematic text
unk800DF83C gTitleCinematicText[10] = {
    { "TIMBER", 14.0f, 14.5f, 16.5f, 17.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF,
      SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "BUMPER", 19.0f, 19.5f, 21.5f, 22.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF,
      SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "CONKER", 24.0f, 24.5f, 26.5f, 27.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF,
      SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "TIPTUP", 29.0f, 29.5f, 31.5f, 32.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF,
      SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "DRUMSTICK", 35.0f, 35.5f, 37.5f, 38.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF,
      SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "PIPSY", 40.0f, 40.5f, 42.5f, 43.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF,
      SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "BANJO", 45.0f, 45.5f, 47.5f, 48.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF,
      SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "KRUNCH", 50.0f, 50.5f, 52.5f, 53.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF,
      SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "WIZPIG", 57.5f, 58.0f, 60.0f, 60.5f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF,
      SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "DIDDY", 63.5f, 64.0f, 66.0f, 66.5f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF,
      SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f }
};

// Number of active colours used in the title screen cinematic.
s32 gTitleCinematicTextColourCount = 0;

// Colours used for the Character Names during the title screen cinematic
MenuColour gTitleCinematicTextColours[4] = {
    { 255, 255, 0, 255, 204 }, // Yellow
    { 0, 255, 0, 255, 153 },   // Green
    { 0, 255, 255, 255, 102 }, // Cyan
    { 0, 0, 255, 255, 51 }     // Blue
};

UNUSED u8 unused_800DFA10[4] = { 0, 0, 15, 120 };

char *gOptionMenuStrings[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };

s16 gOptionMenuTextures[8] = { 0x3D, 0x3C, 0x3F, 0x3E, 0x44, -1, -1, 0 };

unk800DFA3C gAudioMenuStrings[8] = {
    { 160, 80, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 0, 12, NULL },  { 160, 104, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 0, 12, NULL },
    { 160, 144, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 0, 12, NULL }, { 160, 192, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 0, 12, NULL },
    { 161, 35, 0, 0, 0, 0xFF, 0x80, 2, 0, 12, NULL },        { 160, 32, 0xFF, 0x80, 0xFF, 0, 0xFF, 2, 0, 12, NULL },
    { 160, 188, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 0, 12, NULL }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL },
};

// Current song index used in the music test (from JUKEBOX magic code)
s32 gMusicTestSongIndex = 0;

s32 gSfxVolumeSliderValue = 256;   // Value from 0 to 256
s32 gMusicVolumeSliderValue = 256; // Value from 0 to 256

StereoPanMode gAudioOutputType = STEREO;

// This is used for RGBA colors for the save options Controller Pak BG.
u32 gContPakSaveBgColours[MAXCONTROLLERS] = {
    COLOUR_RGBA32(64, 64, 255, 255),  // Blue for controller 1
    COLOUR_RGBA32(255, 64, 64, 255),  // Red for controller 2
    COLOUR_RGBA32(255, 208, 64, 255), // Yellow for controller 3
    COLOUR_RGBA32(64, 255, 64, 255)   // Green for controller 4
};

SIDeviceStatus D_800DFADC = CONTROLLER_PAK_GOOD;
s32 gControllerIndex = 0;

// Strings related to the controller pak.
char *gContPakNotPresentStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakCorruptDataRepairStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakDamagedStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakFullStrings[5] = { 0, 0, 0, 0, 0 };
char *gContPakDiffContStrings[7] = { 0, 0, 0, 0, 0, 0, 0 };
char *gContPakNoRoomForGhostsStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakCorruptDataStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakRumbleDetectedStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakSwitchToRumbleStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakNeed2ndAdvStrings[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

// Associated with SIDeviceStatus enum values.
char **gContPakStrings[11] = { NULL,
                               gContPakNotPresentStrings,
                               gContPakCorruptDataRepairStrings,
                               gContPakDamagedStrings,
                               gContPakFullStrings,
                               gContPakDiffContStrings,
                               gContPakNoRoomForGhostsStrings,
                               gContPakRumbleDetectedStrings,
                               gContPakSwitchToRumbleStrings,
                               gContPakCorruptDataStrings,
                               gContPakNeed2ndAdvStrings };

s32 unused_800DFC08 = 0;
s32 unused_800DFC0C = 0xFFFF;

/*** Icons in the save options menu. ***/
DrawTexture gDrawTexN64Icon[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gDrawTexTTIcon[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gDrawTexGhostIcon[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gDrawTexFileIcon[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gDrawTexContPakIcon[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gDrawTexTrashIcon[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };

u8 unused_800DFC70[8] = { 0x40, 0x40, 0x04, 0x04, 0xFF, 0, 0, 0 };

s16 gSaveMenuObjectIndices[26] = { 0x0024, 0x0025, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x003D,
                                   0x003F, 0x003E, 0x003C, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048,
                                   0x0049, 0x004A, 0x004B, 0x0040, 0x0041, 0x0002, 0xFFFF, 0x0000 };

s16 gSaveMenuImageIndices[4] = { 0x000B, 0x000C, 0x0002, 0xFFFF };

MenuElement gControllerPakMenuElement[7] = {
    { 161, 32, 161, 33, 161, 32, 0, 0, 0, 255, 128, ASSET_FONTS_BIGFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 160, 30, 160, 30, 160, 30, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 160, 112, 160, 112, 160, 112, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 160, 128, 160, 128, 160, 128, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 160, 192, 160, 192, 160, 192, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 160, 208, 160, 208, 160, 208, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ASSET_FONTS_FUNFONT, 0, 0, { NULL }, { { 0, 0, 0, 0 } } },
};

s32 gShowControllerPakMenu = FALSE;

s32 gActiveMagicCodes = 0;
s32 gUnlockedMagicCodes = 0;

char *gMagicCodeMenuStrings[5] = { 0, 0, 0, 0, 0 };

u8 gCharacterVolumes[10][2] = {
    { 0x0F, 0x64 }, { 0x0C, 0x07 }, { 0x09, 0x64 }, { 0x0A, 0x64 }, { 0x08, 0x64 },
    { 0x0B, 0x64 }, { 0x0D, 0x64 }, { 0x0E, 0x64 }, { 0x05, 0x64 }, { 0x04, 0x64 },
};

s16 gCharSelectObjectIndices[2] = { -1, 0 };
s16 gCharSelectImageIndices[2] = { -1, 0 };

// Not sure what this is
// Used for gCurrCharacterSelectData when Neither T.T. Nor Drumstick are unlocked
// CharacterSelectData

#define NONE 0xFF
#define KRUNCH 0
#define DIDDY 1
#define BUMPER 2
#define BANJO 3
#define CONKER 4
#define TIPTUP 5
#define PIPSY 6
#define TIMBER 7
#define DRUMSTICK 8
#define TICTOC_8 8 // T.T's unlocked but Drumstick is not
#define TICTOC_9 9 // Everyone unlocked.

/**
 * Diddy Kong Racing's character select menu refers to these arrays below to know how
 * to handle some certain things. This includes which direction selects which index, which voice ID
 * they use, and which audio voices the BGM uses. It has a different table for each possible combination
 * of which characters are available to select. This system is far from conventional.
 * Unfortunately, because each entry is explicitly 14 bytes, it means a struct would not match, because
 * a struct would align itself to 16 bytes, creating an extra 2 bytes of padding inbetween.
 *
 * The layout shows which character is in each cardinal direction. Presumably so it knows
 * where to place extra cursors when a new player joins.
 * Frankly, this is a comically overcomplicated method.
 */

// Default character select screen with the initial 8 characters.
/*    Name         Up                  Down                Left                                Right Voice ID */
CharacterSelectData gCharacterSelectBytesDefault[] = {
    /*Krunch*/ { { NONE, NONE }, { CONKER, NONE }, { NONE, NONE, NONE, NONE }, { DIDDY, BUMPER, BANJO, NONE }, 0x0000 },
    /*Diddy*/ { { NONE, NONE }, { TIPTUP, NONE }, { KRUNCH, NONE, NONE, NONE }, { BUMPER, BANJO, NONE, NONE }, 0x0009 },
    /*Bumper*/ { { NONE, NONE }, { PIPSY, NONE }, { DIDDY, KRUNCH, NONE, NONE }, { BANJO, NONE, NONE, NONE }, 0x0001 },
    /*Banjo*/ { { NONE, NONE }, { TIMBER, NONE }, { BUMPER, DIDDY, KRUNCH, NONE }, { NONE, NONE, NONE, NONE }, 0x0005 },
    /*Conker*/
    { { KRUNCH, NONE }, { NONE, NONE }, { NONE, NONE, NONE, NONE }, { TIPTUP, PIPSY, TIMBER, NONE }, 0x0003 },
    /*Tiptup*/ { { DIDDY, NONE }, { NONE, NONE }, { CONKER, NONE, NONE, NONE }, { PIPSY, TIMBER, NONE, NONE }, 0x0002 },
    /*Pipsy*/
    { { BUMPER, NONE }, { NONE, NONE }, { TIPTUP, CONKER, NONE, NONE }, { TIMBER, NONE, NONE, NONE }, 0x0007 },
    /*Timber*/ { { BANJO, NONE }, { NONE, NONE }, { PIPSY, TIPTUP, CONKER, NONE }, { NONE, NONE, NONE, NONE }, 0x0004 }
};

// Drumstick is unlocked, but T.T is not.
/*    Name            Up                     Down                Left                                  Right Voice ID */
CharacterSelectData gCharacterSelectBytesDrumStick[] = {
    /*Krunch*/ {
        { NONE, NONE }, { CONKER, NONE }, { NONE, NONE, NONE, NONE }, { DIDDY, DRUMSTICK, BUMPER, BANJO }, 0x0000 },
    /*Diddy*/
    { { NONE, NONE }, { CONKER, TIPTUP }, { KRUNCH, NONE, NONE, NONE }, { DRUMSTICK, BUMPER, BANJO, NONE }, 0x0009 },
    /*Bumper*/
    { { NONE, NONE }, { PIPSY, TIMBER }, { DRUMSTICK, DIDDY, KRUNCH, NONE }, { BANJO, NONE, NONE, NONE }, 0x0001 },
    /*Banjo*/
    { { NONE, NONE }, { TIMBER, NONE }, { BUMPER, DRUMSTICK, DIDDY, KRUNCH }, { NONE, NONE, NONE, NONE }, 0x0005 },
    /*Conker*/
    { { KRUNCH, DIDDY }, { NONE, NONE }, { NONE, NONE, NONE, NONE }, { TIPTUP, PIPSY, TIMBER, NONE }, 0x0003 },
    /*Tiptup*/
    { { DIDDY, DRUMSTICK }, { NONE, NONE }, { CONKER, NONE, NONE, NONE }, { PIPSY, TIMBER, NONE, NONE }, 0x0002 },
    /*Pipsy*/
    { { DRUMSTICK, BUMPER }, { NONE, NONE }, { TIPTUP, CONKER, NONE, NONE }, { TIMBER, NONE, NONE, NONE }, 0x0007 },
    /*Timber*/
    { { BUMPER, BANJO }, { NONE, NONE }, { PIPSY, TIPTUP, CONKER, NONE }, { NONE, NONE, NONE, NONE }, 0x0004 },
    /*Drumstick*/
    { { NONE, NONE }, { TIPTUP, PIPSY }, { DIDDY, KRUNCH, NONE, NONE }, { BUMPER, BANJO, NONE, NONE }, 0x0006 }
};

// Under the unlikely chance you have T.T unlocked, but not Drumstick.
/*    Name         Up                 Down                  Left                                 Right Voice ID */
CharacterSelectData gCharacterSelectBytesTT[] = {
    /*Krunch*/ { { NONE, NONE }, { CONKER, NONE }, { NONE, NONE, NONE, NONE }, { DIDDY, BUMPER, BANJO, NONE }, 0x0000 },
    /*Diddy*/
    { { NONE, NONE }, { TIPTUP, TICTOC_8 }, { KRUNCH, NONE, NONE, NONE }, { BUMPER, BANJO, NONE, NONE }, 0x0009 },
    /*Bumper*/
    { { NONE, NONE }, { TICTOC_8, PIPSY }, { DIDDY, KRUNCH, NONE, NONE }, { BANJO, NONE, NONE, NONE }, 0x0001 },
    /*Banjo*/
    { { NONE, NONE }, { PIPSY, TIMBER }, { BUMPER, DIDDY, KRUNCH, NONE }, { NONE, NONE, NONE, NONE }, 0x0005 },
    /*Conker*/
    { { KRUNCH, NONE }, { NONE, NONE }, { NONE, NONE, NONE, NONE }, { TIPTUP, TICTOC_8, PIPSY, TIMBER }, 0x0003 },
    /*Tiptup*/
    { { KRUNCH, DIDDY }, { NONE, NONE }, { CONKER, NONE, NONE, NONE }, { TICTOC_8, PIPSY, TIMBER, NONE }, 0x0002 },
    /*Pipsy*/
    { { BUMPER, BANJO }, { NONE, NONE }, { TICTOC_8, TIPTUP, CONKER, NONE }, { TIMBER, NONE, NONE, NONE }, 0x0007 },
    /*Timber*/
    { { BANJO, NONE }, { NONE, NONE }, { PIPSY, TICTOC_8, TIPTUP, CONKER }, { NONE, NONE, NONE, NONE }, 0x0004 },
    /*T.T*/ { { DIDDY, BUMPER }, { NONE, NONE }, { TIPTUP, CONKER, NONE, NONE }, { PIPSY, TIMBER, NONE, NONE }, 0x0008 }
};

// With everyone unlocked.
/*    Name            Up                   Down                Left                                 Right Voice ID */
CharacterSelectData gCharacterSelectBytesComplete[] = {
    /*Krunch*/ {
        { NONE, NONE }, { CONKER, NONE }, { NONE, NONE, NONE, NONE }, { DIDDY, DRUMSTICK, BUMPER, BANJO }, 0x0000 },
    /*Diddy*/
    { { NONE, NONE }, { TIPTUP, NONE }, { KRUNCH, NONE, NONE, NONE }, { DRUMSTICK, BUMPER, BANJO, NONE }, 0x0009 },
    /*Bumper*/
    { { NONE, NONE }, { PIPSY, NONE }, { DRUMSTICK, DIDDY, KRUNCH, NONE }, { BANJO, NONE, NONE, NONE }, 0x0001 },
    /*Banjo*/
    { { NONE, NONE }, { TIMBER, NONE }, { BUMPER, DRUMSTICK, DIDDY, KRUNCH }, { NONE, NONE, NONE, NONE }, 0x0005 },
    /*Conker*/
    { { KRUNCH, NONE }, { NONE, NONE }, { NONE, NONE, NONE, NONE }, { TIPTUP, TICTOC_9, PIPSY, TIMBER }, 0x0003 },
    /*Tiptup*/
    { { DIDDY, NONE }, { NONE, NONE }, { CONKER, NONE, NONE, NONE }, { TICTOC_9, PIPSY, TIMBER, NONE }, 0x0002 },
    /*Pipsy*/
    { { BUMPER, NONE }, { NONE, NONE }, { TICTOC_9, TIPTUP, CONKER, NONE }, { TIMBER, NONE, NONE, NONE }, 0x0007 },
    /*Timber*/
    { { BANJO, NONE }, { NONE, NONE }, { PIPSY, TICTOC_9, TIPTUP, CONKER }, { NONE, NONE, NONE, NONE }, 0x0004 },
    /*Drumstick*/
    { { NONE, NONE }, { TICTOC_9, NONE }, { DIDDY, KRUNCH, NONE, NONE }, { BUMPER, BANJO, NONE, NONE }, 0x0006 },
    /*T.T*/
    { { DRUMSTICK, NONE }, { TIPTUP, NONE }, { TIPTUP, CONKER, NONE, NONE }, { PIPSY, TIMBER, NONE, NONE }, 0x0008 }
    //!@bug T.T's down input selects Tiptup. It should be set to NONE.
};

s32 unused_800DFFCC = 0;

// Set from func_8008AEB4()
// Is either 0, 1, or 2. However it is never set to 2?
// Set to 0 upon entering the Character Select menu normally.
// Set to 1 upon entering the Char Select from the
//   "Select Character" option on the "Pause Options" screen in a race.
s32 gEnteredCharSelectFrom = 0;

// Set from func_8008AEB4()
// Set to the value *arg1 when arg0 is 2, but that never happens.
// Not read from anywhere, so I'd consider this to be unused.
s32 unused_800DFFD4 = -1;

MenuElement gCautionMenuTextElements[14] = {
    { SCREEN_WIDTH_HALF + 1,
      35,
      SCREEN_WIDTH_HALF + 1,
      35,
      SCREEN_WIDTH_HALF + 1,
      35,
      0,
      0,
      0,
      255,
      128,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      32,
      SCREEN_WIDTH_HALF,
      32,
      SCREEN_WIDTH_HALF,
      32,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      72,
      SCREEN_WIDTH_HALF,
      68,
      SCREEN_WIDTH_HALF,
      72,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      86,
      SCREEN_WIDTH_HALF,
      82,
      SCREEN_WIDTH_HALF,
      86,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      100,
      SCREEN_WIDTH_HALF,
      96,
      SCREEN_WIDTH_HALF,
      100,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      114,
      SCREEN_WIDTH_HALF,
      110,
      SCREEN_WIDTH_HALF,
      114,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      128,
      SCREEN_WIDTH_HALF,
      124,
      SCREEN_WIDTH_HALF,
      128,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      142,
      SCREEN_WIDTH_HALF,
      138,
      SCREEN_WIDTH_HALF,
      142,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      156,
      SCREEN_WIDTH_HALF,
      152,
      SCREEN_WIDTH_HALF,
      156,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      156,
      SCREEN_WIDTH_HALF,
      166,
      SCREEN_WIDTH_HALF,
      156,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      186,
      SCREEN_WIDTH_HALF,
      180,
      SCREEN_WIDTH_HALF,
      186,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      200,
      SCREEN_WIDTH_HALF,
      194,
      SCREEN_WIDTH_HALF,
      200,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      200,
      SCREEN_WIDTH_HALF,
      208,
      SCREEN_WIDTH_HALF,
      200,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { NULL }, { { 0, 0, 0, 0 } } },
};

MenuElement gGameSelectTextElemsNoAdv2[7] = {
    { SCREEN_WIDTH_HALF + 1,
      35,
      SCREEN_WIDTH_HALF + 1,
      35,
      SCREEN_WIDTH_HALF + 1,
      35,
      0,
      0,
      0,
      255,
      128,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      32,
      SCREEN_WIDTH_HALF,
      32,
      SCREEN_WIDTH_HALF,
      32,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { -96, 39, -96, 39, -96, 39, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT, 0, 7, { NULL }, { { 192, 44, 4, 4 } } },
    { SCREEN_WIDTH_HALF,
      104,
      SCREEN_WIDTH_HALF,
      104,
      SCREEN_WIDTH_HALF,
      104,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { -96, -9, -96, -9, -96, -9, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT, 0, 7, { NULL }, { { 192, 44, 4, 4 } } },
    { SCREEN_WIDTH_HALF,
      152,
      SCREEN_WIDTH_HALF,
      152,
      SCREEN_WIDTH_HALF,
      152,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { NULL }, { { 0, 0, 0, 0 } } },
};

MenuElement gGameSelectTextElemsWithAdv2[9] = {
    { SCREEN_WIDTH_HALF + 1,
      35,
      SCREEN_WIDTH_HALF + 1,
      35,
      SCREEN_WIDTH_HALF + 1,
      35,
      0,
      0,
      0,
      255,
      128,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { SCREEN_WIDTH_HALF,
      32,
      SCREEN_WIDTH_HALF,
      32,
      SCREEN_WIDTH_HALF,
      32,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { -112,
      55,
      -112,
      55,
      -112,
      55,
      176,
      224,
      192,
      255,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      7,
      { NULL },
      { { 224, 44, 4, 4 } } },
    { SCREEN_WIDTH_HALF,
      88,
      SCREEN_WIDTH_HALF,
      88,
      SCREEN_WIDTH_HALF,
      88,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { -112, 7, -112, 7, -112, 7, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT, 0, 7, { NULL }, { { 224, 44, 4, 4 } } },
    { SCREEN_WIDTH_HALF,
      136,
      SCREEN_WIDTH_HALF,
      136,
      SCREEN_WIDTH_HALF,
      136,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { -112,
      -41,
      -112,
      -41,
      -112,
      -41,
      176,
      224,
      192,
      255,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      7,
      { NULL },
      { { 224, 44, 4, 4 } } },
    { SCREEN_WIDTH_HALF,
      184,
      SCREEN_WIDTH_HALF,
      184,
      SCREEN_WIDTH_HALF,
      184,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { NULL },
      { { 0, 0, 0, 0 } } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { NULL }, { { 0, 0, 0, 0 } } },
};

s16 gFileSelectObjectIndices[6] = { 0x00, 0x43, 0x40, 0x41, 0x42, -1 };

s16 gFileSelectImageIndices[6] = { 0x00, 0x0B, 0x0C, 0x0A, -1, 0 };

char *gFilenames[3] = { NULL, NULL, NULL };

u16 unused_800E03BC[8] = {
    0x004C, 0x0070, 0x00F4, 0x0070, 0x004C, 0x00D0, 0x00F4, 0x00D0,
};

ButtonElement gFileSelectButtons[3] = {
    { 24, 81, 88, 64, 4, 4, GPACK_RGBA5551(64, 16, 0, 0), GPACK_RGBA5551(255, 255, 0, 0) },  // File A
    { 116, 81, 88, 64, 4, 4, GPACK_RGBA5551(64, 16, 0, 0), GPACK_RGBA5551(255, 255, 0, 0) }, // File B
    { 208, 81, 88, 64, 4, 4, GPACK_RGBA5551(64, 16, 0, 0), GPACK_RGBA5551(255, 255, 0, 0) }, // File C
};

s16 gFileSelectElementPos[10] = {
    44, 54, // game name
    21, 25, // Balloon icon
    44, 27, // New Text
    63, 25, // Balloon count
    45, 25  // Balloon count x
};

// Either 0 (2 racers), 1 (4 racers), or 2 (6 racers)
s32 gMultiplayerSelectedNumberOfRacers = 0;

// Highlighted option index for time trial in tracks mode.
//   0 = Time Trial off
//   1 = Time Trial on
s32 gTracksMenuTimeTrialHighlightIndex = 0;

// Highlighted option index for adventure 1 or 2 in tracks mode.
//   0 = Adventure 1 (Normal)
//   1 = Adventure 2 (Mirrored)
s32 gTracksMenuAdventureHighlightIndex = 0;

DrawTexture gMenuSelectionArrowUp[2] = { { NULL, -12, -8 }, { NULL, 0, 0 } };
DrawTexture gMenuSelectionArrowLeft[2] = { { NULL, -8, -12 }, { NULL, 0, 0 } };
DrawTexture gMenuSelectionArrowDown[2] = { { NULL, -12, -8 }, { NULL, 0, 0 } };
DrawTexture gMenuSelectionArrowRight[2] = { { NULL, -8, -12 }, { NULL, 0, 0 } };

DrawTexture gRaceSelectionCarTex[3] = { { NULL, 0, 0 }, { NULL, 0, 32 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionHoverTex[3] = { { NULL, 0, 0 }, { NULL, 0, 32 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionPlaneTex[3] = { { NULL, 0, 0 }, { NULL, 0, 32 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionTTOn[3] = { { NULL, 0, 0 }, { NULL, 0, 32 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionTTOff[3] = { { NULL, 0, 0 }, { NULL, 0, 32 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionCarOptHighlight[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionCarOpt[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionHoverOptHighlight[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionHoverOpt[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionPlaneOptHighlight[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionPlaneOpt[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionTTOnOptHighlight[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionTTOffOptHighlight[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionTTOnOpt[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionTTOffOpt[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionPlayer1Texture[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionPlayer2Texture[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionPlayer3Texture[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionPlayer4Texture[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionVehicleTitleTexture[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionTTTitleTexture[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E05D4[4] = { { NULL, 0, -48 }, { NULL, 0, -16 }, { NULL, 0, 16 }, { NULL, 0, 0 } };
DrawTexture D_800E05F4[4] = { { NULL, 0, -48 }, { NULL, 0, -16 }, { NULL, 0, 16 }, { NULL, 0, 0 } };
DrawTexture gRaceSelectionTTTexture[2] = { { NULL, -16, -16 }, { NULL, 0, 0 } };

DrawTexture *gRaceSelectionImages[9] = {
    gRaceSelectionCarTex,   gRaceSelectionCarOptHighlight,   gRaceSelectionCarOpt,
    gRaceSelectionHoverTex, gRaceSelectionHoverOptHighlight, gRaceSelectionHoverOpt,
    gRaceSelectionPlaneTex, gRaceSelectionPlaneOptHighlight, gRaceSelectionPlaneOpt

};

DrawTexture *gTrackSelectTTImage[6] = { gRaceSelectionTTOff, gRaceSelectionTTOffOptHighlight, gRaceSelectionTTOffOpt,
                                        gRaceSelectionTTOn,  gRaceSelectionTTOnOptHighlight,  gRaceSelectionTTOnOpt };

DrawTexture *gTrackSelectPlayerImage[6] = { gRaceSelectionPlayer1Texture,      gRaceSelectionPlayer2Texture,
                                            gRaceSelectionPlayer3Texture,      gRaceSelectionPlayer4Texture,
                                            gRaceSelectionVehicleTitleTexture, gRaceSelectionTTTitleTexture };

DrawTexture *gMenuSelectionArrows[4] = { gMenuSelectionArrowUp, gMenuSelectionArrowLeft, gMenuSelectionArrowDown,
                                         gMenuSelectionArrowRight };

// X/Y offsets for the "Player" icon
s16 gTracksMenuPlayerNamePositions[20] = {
    // X, Y
    0x44, 0x72,                                     // 1 player
    0x44, 0x72, 0xCC, 0x72,                         // 2 players
    0x21, 0x72, 0x88, 0x72, 0xEF, 0x72,             // 3 players
    0x21, 0x72, 0x66, 0x72, 0xAA, 0x72, 0xEF, 0x72, // 4 players
};

// X offsets for "Car", "Hover", and "Plane" choices in track select.
s16 gTracksMenuVehicleNamePositions[10] = {
    0x68,                  // 1 player
    0x21, 0xFB,            // 2 players
    0x27, 0x8E, 0xF5,      // 3 players
    0x27, 0x6C, 0xB0, 0xF5 // 4 players
};

// Paired X / Y Offsets. X Is First, Y is Second. For NTSC.
s16 gTracksMenuArrowPositionsNTSC[8] = {
    0x0000, 0xFFC2, 0x0055, 0x0000, 0x0000, 0x003E, 0xFFAB, 0x0000,
};

// Paired X / Y Offsets. X Is First, Y is Second. For PAL.
s16 gTracksMenuArrowPositionsPAL[8] = {
    0x0000, 0xFFB6, 0x0055, 0x0000, 0x0000, 0x004A, 0xFFAB, 0x0000,
};

ButtonTextElement gTwoPlayerRacerCountMenu = {
    SCREEN_WIDTH_HALF - 80, 140, 160, 64, 4, 4, { 80, 20, 58, 40, 80, 40, 102, 40 }
};

// Adventure 1/2 button in the track select menu.
// Note: The first element (.x) is not actually used.
ButtonElement gTracksMenuAdventureButton = { 80, 152, 160, 40, 4, 4, 80, 14 };

// Often access like D_800E0710[i * 3 + 1].
// Texture indices for the backgrounds in the Track Select
// Seems like the 3rd number of a group of 3 is not used for anything?
s16 gTracksMenuBgTextureIndices[15] = {
    0x0E, 0x0F, 0x00, // Dino domain
    0x10, 0x11, 0x20, // Sherbet Island
    0x12, 0x13, 0x00, // Snowflake Mountain
    0x14, 0x15, 0x20, // Dragon Forest
    0x16, 0x17, 0x20  // Future Fun Land
};

TextureHeader *gTracksMenuBgTextures[10] = {
    NULL, NULL, // Dino domain
    NULL, NULL, // Sherbet Island
    NULL, NULL, // Snowflake Mountain
    NULL, NULL, // Dragon Forest
    NULL, NULL  // Future Fun Land
};

// ID for T.Ts voice lines for each track id.
// T.T. will say nothing for tracks with -1
s16 gTTVoiceLines[53] = { -1,
                          -1,
                          SOUND_VOICE_TT_DRAGON_FOREST,
                          SOUND_VOICE_TT_FOSSIL_CANYON,
                          SOUND_VOICE_TT_PIRATE_LAGOON,
                          SOUND_VOICE_TT_ANCIENT_LAKE,
                          SOUND_VOICE_TT_WALRUS_COVE,
                          SOUND_VOICE_TT_HOT_TOP_VOLCANO,
                          SOUND_VOICE_TT_WHALE_BAY,
                          SOUND_VOICE_TT_SNOWBALL_VALLEY,
                          SOUND_VOICE_TT_CRESCENT_ISLAND,
                          SOUND_VOICE_TT_FIRE_MOUNTAIN,
                          SOUND_VOICE_TT_DINO_DOMAIN,
                          SOUND_VOICE_TT_EVERFROST_PEAK,
                          SOUND_VOICE_TT_SHERBET_ISLAND,
                          SOUND_VOICE_TT_SPACEPORT_ALPHA,
                          -1,
                          SOUND_VOICE_TT_SPACEDUST_VALLEY,
                          SOUND_VOICE_TT_GREENWOOD_VILLAGE,
                          SOUND_VOICE_TT_BOULDER_CANYON,
                          SOUND_VOICE_TT_WINDMILL_PLAINS,
                          -1,
                          -1,
                          -1,
                          SOUND_VOICE_TT_SNOWFLAKE_MOUNTAIN,
                          SOUND_VOICE_TT_SMOKEY_CASTLE,
                          SOUND_VOICE_TT_DARKWATER_BEACH,
                          SOUND_VOICE_TT_ICICLE_PYRAMID,
                          SOUND_VOICE_TT_FROSTY_VILLAGE,
                          SOUND_VOICE_TT_JUNGLE_FALLS,
                          SOUND_VOICE_TT_TREASURE_CAVES,
                          SOUND_VOICE_TT_HAUNTED_WOODS,
                          SOUND_VOICE_TT_DARKMOON_CAVERNS,
                          SOUND_VOICE_TT_STAR_CITY,
                          SOUND_VOICE_TT_TROPHY_RACE,
                          SOUND_VOICE_TT_FUTURE_FUN_LAND,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1 };

s16 gTrackSelectObjectIndices[14] = {
    0x05, 0x06, 0x07, 0x3D, 0x3C, 0x3F, 0x3E, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, -1
};

s16 gTrackSelectImageIndices[4] = { 0x04, 0x05, 0x06, -1 };

s16 gTrackSelectPreviewObjectIndices[36] = { 0x0004, 0x0000, 0x0001, 0x0002, 0x0003, 0x0018, 0x0019, 0x001A, 0x001B,
                                             0x001C, 0x001D, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A,
                                             0x002B, 0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0023, 0x002C, 0x002D,
                                             0x002E, 0x002F, 0x0030, 0x0031, 0x0040, 0x0041, 0x0043, 0x005E, 0xFFFF };

s16 gTrackSelectPreviewImageIndices[8] = { 0x07, 0x00, 0x01, 0x02, 0x03, 0x0B, 0x0C, -1 };

// Not a struct, since the entries can *technically* be either 4 or 5 bytes. But it is always 5 in the final game.
/*
    Offset 0: u8 index;
    Offset 1: u8 indexInto800E0730;
    Offset 2: u8 alpha;
    Offset 3: u8 alpha2;
    Offset 4: u8 texCoordUFactor;
*/
u8 gTrackSelectBgData[295] = {
    0,  0, 255, 255, 0,  1,  1, 255, 255, 0,  2,  0, 255, 255, 0,  3,   1, 255, 255, 0,  4,  0, 255, 255, 0,
    5,  1, 255, 255, 0,  6,  0, 255, 255, 0,  6,  2, 0,   64,  0,  7,   1, 255, 255, 0,  7,  3, 64,  128, 0,
    8,  0, 255, 255, 0,  8,  2, 128, 192, 32, 9,  1, 255, 255, 0,  9,   3, 192, 255, 32, 10, 2, 255, 255, 0,
    11, 3, 255, 255, 0,  12, 2, 255, 255, 32, 13, 3, 255, 255, 32, 14,  2, 255, 255, 0,  14, 4, 0,   64,  0,
    15, 3, 255, 255, 0,  15, 5, 64,  128, 0,  16, 2, 255, 255, 32, 16,  4, 128, 192, 0,  17, 3, 255, 255, 32,
    17, 5, 192, 255, 0,  18, 4, 255, 255, 0,  19, 5, 255, 255, 0,  20,  4, 255, 255, 0,  21, 5, 255, 255, 0,
    22, 4, 255, 255, 0,  22, 6, 0,   64,  0,  23, 5, 255, 255, 0,  23,  7, 64,  128, 0,  24, 4, 255, 255, 0,
    24, 6, 128, 192, 32, 25, 5, 255, 255, 0,  25, 7, 192, 255, 32, 26,  6, 255, 255, 0,  27, 7, 255, 255, 0,
    28, 6, 255, 255, 32, 29, 7, 255, 255, 32, 30, 6, 255, 255, 0,  30,  8, 0,   64,  0,  31, 7, 255, 255, 0,
    31, 9, 64,  128, 0,  32, 6, 255, 255, 32, 32, 8, 128, 192, 32, 33,  7, 255, 255, 32, 33, 9, 192, 255, 32,
    34, 8, 255, 255, 0,  35, 9, 255, 255, 0,  36, 8, 255, 255, 32, 37,  9, 255, 255, 32, 38, 8, 255, 255, 0,
    39, 9, 255, 255, 0,  40, 8, 255, 255, 32, 41, 9, 255, 255, 32, 255, 0, 0,   0,   0
};
Vertex *gTrackSelectBgVertices[2] = { NULL, NULL };
Triangle *gTrackSelectBgTriangles[2] = { NULL, NULL };
char *gQMarkPtr = "?";

// Boolean. Set to TRUE once in the Track Select menu, then
//   set to FALSE when leaving the menu.
// This is effectively unused, since it is only read from the
//   unused function func_8008E790()
s32 gIsInTracksMenu = FALSE;

s32 gTrackNameVoiceDelay = 0;
s32 gMenuOptionCap = 0;
s32 gMenuSubOption = 0;

// Index of the last player who paused.
s32 gLastPlayerWhoPaused = 0;

ColourRGBA gPlayerPauseBgColour[4] = {
    { { { 64, 64, 255, 160 } } },  // Blue for player 1
    { { { 255, 64, 64, 160 } } },  // Red for player 2
    { { { 208, 192, 32, 176 } } }, // Yellow for player 3
    { { { 32, 192, 64, 176 } } },  // Green for player 4
};

ColourRGBA gPlayerPauseOptionsTextColour[4] = {
    { { { 0, 255, 0, 128 } } }, // Green for Player 1
    { { { 0, 255, 0, 96 } } },  // Green for Player 2
    { { { 0, 0, 255, 96 } } },  // Blue for Player 3
    { { { 0, 0, 255, 128 } } }, // Blue for Player 4
};

// BAD CONTROLLER PAK / If you wish to change / Controller Pak or Rumble Pak, / please do so now.
char *sBadControllerPakMenuText[5] = { 0, 0, 0, 0, 0 };

// CONTROLLER PAK FULL / If you wish to change / Controller Pak or Rumble Pak, / please do so now.
char *sControllerPakFullMenuText[5] = { 0, 0, 0, 0, 0 };

// NO CONTROLLER PAK / If you wish to change / Controller Pak or Rumble Pak, / please do so now.
char *sNoControllerPakMenuText[5] = { 0, 0, 0, 0, 0 };

// CORRUPT DATA / If you wish to change / Controller Pak or Rumble Pak, / please do so now.
char *sCorruptDataMenuText[3] = { 0, 0, 0 }; // This should be 5 in size? This is unclear still.

char *D_800E09F8[3] = { 0, 0, 0 };

// If you wish to use / the Controller Pak / insert it now!
char *sInsertControllerPakMenuText[3] = { 0, 0, 0 };

s16 D_800E0A10[2] = { 0x0000, 0x0000 };

// If you wish to use / the Rumble Pak / insert it now!
char *sInsertRumblePakMenuText[4] = { 0, 0, 0, 0 };

s16 gRaceResultsObjectIndices[14] = { 0x0005, 0x003B, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036,
                                      0x0039, 0x0037, 0x0038, 0x003A, 0x0000, 0x0001, 0xFFFF };

s16 gRaceResultsImageIndices[8] = { 0x0004, 0x0000, 0x0001, 0xFFFF, 0x0300, 0x0000, 0x0012, 0xFFFF };

DrawTexture gMenuPortraitKrunch[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gMenuPortraitDiddy[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gMenuPortraitDrumstick[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gMenuPortraitBumper[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gMenuPortraitBanjo[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gMenuPortraitConker[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gMenuPortraitTiptup[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gMenuPortraitTT[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gMenuPortraitPipsy[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture gMenuPortraitTimber[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };

DrawTexture *gRacerPortraits[10] = { gMenuPortraitKrunch, gMenuPortraitDiddy, gMenuPortraitDrumstick,
                                     gMenuPortraitBumper, gMenuPortraitBanjo, gMenuPortraitConker,
                                     gMenuPortraitTiptup, gMenuPortraitTT,    gMenuPortraitPipsy,
                                     gMenuPortraitTimber };

s16 unused_800E0B18[74] = { 0x0140, 0x017C, 0x01B8, 0x01F4, 0x0230, 0x026C, 0x02A8, 0x02E4, 0x01E0, 0x0000, 0x0018,
                            0x0039, 0x005A, 0x007B, 0x009C, 0x00BD, 0x00DE, 0x00FF, 0x00A0, 0x0000, 0x0140, 0x01B8,
                            0x0230, 0x02A8, 0x01E0, 0x0000, 0x0018, 0x0065, 0x00B3, 0x0100, 0x00A0, 0x0000, 0x0140,
                            0x01F4, 0x02A8, 0x01E0, 0x0028, 0x008C, 0x00F0, 0x00A0, 0x01E0, 0x00C0, 0x00A0, 0x00C0,
                            0xFF60, 0x00C0, 0xFF80, 0xFFEC, 0xFFE4, 0xFFE6, 0x0050, 0xFFF8, 0xFFE4, 0xFFF4, 0xFFE4,
                            0x0006, 0xFFE4, 0x0018, 0x0050, 0x0008, 0x0000, 0x0078, 0x0000, 0x003C, 0x0000, 0x001E,
                            0x0000, 0x0384, 0x0000, 0x001E, 0x0000, 0x001E, 0x0000, 0x0384 };

char gFirstPlace[4] = "1ST";
char gSecondPlace[4] = "2ND";
char gThirdPlace[4] = "3RD";
char gFourthPlace[4] = "4TH";
char gFifthPlace[4] = "5TH";
char gSixthPlace[4] = "6TH";
char gSeventhPlace[4] = "7TH";
char gEighthPlace[4] = "8TH";

char *gRacePlacementsArray[8] = { gFirstPlace, gSecondPlace, gThirdPlace,   gFourthPlace,
                                  gFifthPlace, gSixthPlace,  gSeventhPlace, gEighthPlace };

MenuElement gRaceResultsMenuElements[8] = {
    { 352,
      172,
      32,
      172,
      -288,
      172,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 452, 166, 132, 166, -188, 166, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 560, 184, 240, 184, -80, 184, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 452, 180, 132, 180, -188, 180, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { NULL }, { { 0, 0, 0, 0 } } },
    { 452, 198, 132, 198, -188, 198, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { NULL }, { { 0, 0, 0, 0 } } },
    { 452, 216, 132, 216, -188, 216, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { NULL }, { { 0, 0, 0, 0 } } },
    { 560, 200, 240, 200, -80, 200, 128, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { NULL }, { { 0, 0, 0, 0 } } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { NULL }, { { 0, 0, 0, 0 } } },
};

MenuElement gRaceOrderMenuElements[11] = {
    { 575,
      172,
      255,
      172,
      -65,
      172,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 542,
      172,
      222,
      172,
      -98,
      172,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 509,
      172,
      189,
      172,
      -131,
      172,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 476,
      172,
      156,
      172,
      -164,
      172,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 443,
      172,
      123,
      172,
      -197,
      172,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 410,
      172,
      90,
      172,
      -230,
      172,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 377,
      172,
      57,
      172,
      -263,
      172,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 344,
      172,
      24,
      172,
      -296,
      166,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 481, 166, 161, 166, -159, 166, 0, 0, 0, 255, 128, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 479, 164, 159, 164, -161, 164, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { NULL }, { { 0, 0, 0, 0 } } },

};

MenuElement gRecordTimesMenuElements[9] = {
    { 481, 174, 161, 174, -159, 174, 0, 0, 0, 255, 128, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 479, 172, 159, 172, -161, 172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 368, 192, 48, 192, -272, 192, 255, 64, 64, 96, 255, ASSET_FONTS_FUNFONT, 8, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 506, 187, 186, 187, -134, 187, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { NULL }, { { 0, 0, 0, 0 } } },
    { 578,
      192,
      258,
      192,
      -62,
      192,
      255,
      128,
      255,
      96,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { &D_80126390 },
      { { 0, 0, 0, 0 } } },
    { 368, 212, 48, 212, -272, 212, 255, 64, 64, 96, 255, ASSET_FONTS_FUNFONT, 8, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 506, 207, 186, 207, -134, 207, 128, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { NULL }, { { 0, 0, 0, 0 } } },
    { 578,
      212,
      258,
      212,
      -62,
      212,
      255,
      128,
      255,
      96,
      255,
      ASSET_FONTS_FUNFONT,
      12,
      0,
      { &D_80126394 },
      { { 0, 0, 0, 0 } } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { NULL }, { { 0, 0, 0, 0 } } },
};

// Valid characters for name input. Must be u8, not char.
// The length of the array must be a power of two.
u8 gFileNameValidChars[32] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.?    ";

char gCurFilenameCharBeingDrawn = '\0';
s32 gEnterInitalsY = 192;
s32 gFilenameX = 160;
s32 gFilenameY = 120;
s32 gFilenameFont = ASSET_FONTS_BIGFONT;
s32 gCurrentFilenameChars = 0;
s32 D_800E0FA4 = 0;
char gCheckAdvEnterInitials[4] = "DKR"; // Default file name?
s32 D_800E0FAC = 0;
s32 gIndexOfCurInputCharacter = 0;

s16 gAdvTrackInitObjectIndices[18] = { 0x0004, 0x0000, 0x0001, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D,
                                       0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0023, 0x0030, 0x005E, -1 };

s16 gAdvTrackInitImageIndices[6] = { 7, 0, 1, 2, 3, -1 };

s32 gRankingPlayerCount = 8; // Number of racers in trophy race? (1 to 8)
s32 gTrophyRaceWorldId = 0;
s32 gTrophyRaceRound = 0; // Rounds 1 - 4 (as 0 - 3)
s32 gPrevTrophyRaceRound = 0;

u32 unused_800E0FF4[4] = { 0x01FFFFFF, 0x0012FFFF, 0x81FFFFFF, 0x00120000 };

// Number of points to award in trophy race for each place.
s32 gTrophyRacePointsArray[8] = { 9, 7, 5, 3, 1, 0, 0, 0 };

s16 gTrophyRankingsObjectIndices[14] = { 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
                                         0x39, 0x3A, 0x3B, 0x00, 0x01, -1,   0x00 };

s16 gTrophyRaceImageIndices[3] = { 0, 1, -1 };

MenuElement gTrophyRankingsTitle[] = {
    { 320 + 160 + 1,
      35,
      (320 / 2) + 1,
      35,
      -159,
      35,
      0,
      0,
      0,
      255,
      128,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { 0 },
      { { 0, 0, 0, 0 } } },
    { 320 + 160,
      32,
      (320 / 2),
      32,
      -160,
      32,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_BIGFONT,
      12,
      0,
      { 0 },
      { { 0, 0, 0, 0 } } },
};
MenuElement gTrophyRankingsRacers[] = {
    { 64,
      -192,
      64,
      48,
      64,
      288,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 32,
      -192,
      32,
      48,
      32,
      288,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      0,
      { gFirstPlace },
      { { 0, 0, 0, 0 } } },
    { 130,
      -172,
      130,
      68,
      130,
      308,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      4,
      2,
      { &gTrophyRacePointsArray[0] },
      { { 0, 0, 0, 0 } } },
    { 64,
      -150,
      64,
      90,
      64,
      330,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 32,
      -150,
      32,
      90,
      32,
      330,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      0,
      { gSecondPlace },
      { { 0, 0, 0, 0 } } },
    { 130,
      -130,
      130,
      110,
      130,
      350,
      255,
      192,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      4,
      2,
      { &gTrophyRacePointsArray[1] },
      { { 0, 0, 0, 0 } } },
    { 64,
      -108,
      64,
      132,
      64,
      372,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 32,
      -108,
      32,
      132,
      32,
      372,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      0,
      { gThirdPlace },
      { { 0, 0, 0, 0 } } },
    { 130,
      -88,
      130,
      152,
      130,
      392,
      255,
      128,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      4,
      2,
      { &gTrophyRacePointsArray[2] },
      { { 0, 0, 0, 0 } } },
    { 64,
      -66,
      64,
      174,
      64,
      414,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 32,
      -66,
      32,
      174,
      32,
      414,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      0,
      { gFourthPlace },
      { { 0, 0, 0, 0 } } },
    { 130,
      -46,
      130,
      194,
      130,
      434,
      255,
      64,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      4,
      2,
      { &gTrophyRacePointsArray[3] },
      { { 0, 0, 0, 0 } } },
    { 220,
      288,
      220,
      48,
      220,
      -192,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 188,
      288,
      188,
      48,
      188,
      -192,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      0,
      { gFifthPlace },
      { { 0, 0, 0, 0 } } },
    { 286,
      308,
      286,
      68,
      286,
      -172,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      4,
      2,
      { &gTrophyRacePointsArray[4] },
      { { 0, 0, 0, 0 } } },
    { 220,
      330,
      220,
      90,
      220,
      -160,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 188,
      330,
      188,
      90,
      188,
      -150,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      0,
      { gSixthPlace },
      { { 0, 0, 0, 0 } } },
    { 286,
      350,
      286,
      110,
      286,
      -130,
      255,
      192,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      4,
      2,
      { &gTrophyRacePointsArray[5] },
      { { 0, 0, 0, 0 } } },
    { 220,
      372,
      220,
      132,
      220,
      -108,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 188,
      372,
      188,
      132,
      188,
      -108,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      0,
      { gSeventhPlace },
      { { 0, 0, 0, 0 } } },
    { 286,
      392,
      286,
      152,
      286,
      -88,
      255,
      128,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      4,
      2,
      { &gTrophyRacePointsArray[6] },
      { { 0, 0, 0, 0 } } },
    { 220,
      414,
      220,
      174,
      220,
      -66,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      3,
      { &gMenuPortraitKrunch },
      { { 0, 0, 0, 0 } } },
    { 188,
      414,
      188,
      174,
      188,
      -66,
      255,
      255,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      0,
      0,
      { gEighthPlace },
      { { 0, 0, 0, 0 } } },
    { 286,
      434,
      286,
      194,
      286,
      -46,
      255,
      64,
      255,
      0,
      255,
      ASSET_FONTS_FUNFONT,
      4,
      2,
      { &gTrophyRacePointsArray[7] },
      { { 0, 0, 0, 0 } } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ASSET_FONTS_FUNFONT, 0, 0, { 0 }, { { 0, 0, 0, 0 } } }
};
s16 gTrophyRankingsRawIconPositions[138] = {
    0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x00DC, 0x00BC,
    0x011E, 0x00DC, 0x00BC, 0x011E, 0x00DC, 0x00BC, 0x011E, 0x00DC, 0x00BC, 0x011E, 0x0030, 0x0030, 0x0044, 0x005A,
    0x005A, 0x006E, 0x0084, 0x0084, 0x0098, 0x00AE, 0x00AE, 0x00C2, 0x0030, 0x0030, 0x0044, 0x005A, 0x005A, 0x006E,
    0x0084, 0x0084, 0x0098, 0x00AE, 0x00AE, 0x00C2, 0x0038, 0x0038, 0x0040, 0x006A, 0x006A, 0x0072, 0x009C, 0x009C,
    0x00A4, 0x00CE, 0x00CE, 0x00D6, 0x0038, 0x0038, 0x0040, 0x006A, 0x006A, 0x0072, 0x009C, 0x009C, 0x00A4, 0x00CE,
    0x00CE, 0x00D6, 0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x00DC, 0x00BC, 0x011E,
    0x00DC, 0x00BC, 0x011E, 0x00DC, 0x00BC, 0x011E, 0x0034, 0x0034, 0x0048, 0x006F, 0x006F, 0x0083, 0x00AA, 0x00AA,
    0x00BE, 0x0034, 0x0034, 0x0048, 0x006F, 0x006F, 0x0083, 0x00AA, 0x00AA, 0x00BE, 0x004C, 0x004C, 0x0054, 0x007E,
    0x007E, 0x0086, 0x00B0, 0x00B0, 0x00B8, 0x004C, 0x004C, 0x0054, 0x007E, 0x007E, 0x0086, 0x00B0, 0x00B0, 0x00B8,
    0x008C, 0x006C, 0x00CE, 0x008C, 0x006C, 0x00CE, 0x008C, 0x006C, 0x00CE, 0x008C, 0x006C, 0x00CE
};

s16 *gTrophyRankingsIconPositions[32] = { NULL,
                                          NULL,
                                          NULL,
                                          NULL,
                                          &gTrophyRankingsRawIconPositions[126],
                                          &gTrophyRankingsRawIconPositions[90],
                                          &gTrophyRankingsRawIconPositions[126],
                                          &gTrophyRankingsRawIconPositions[24],
                                          NULL,
                                          NULL,
                                          &gTrophyRankingsRawIconPositions[72],
                                          &gTrophyRankingsRawIconPositions[90],
                                          NULL,
                                          NULL,
                                          &gTrophyRankingsRawIconPositions[0],
                                          &gTrophyRankingsRawIconPositions[24],
                                          NULL,
                                          NULL,
                                          NULL,
                                          NULL,
                                          &gTrophyRankingsRawIconPositions[126],
                                          &gTrophyRankingsRawIconPositions[108],
                                          &gTrophyRankingsRawIconPositions[126],
                                          &gTrophyRankingsRawIconPositions[48],
                                          NULL,
                                          NULL,
                                          &gTrophyRankingsRawIconPositions[72],
                                          &gTrophyRankingsRawIconPositions[108],
                                          NULL,
                                          NULL,
                                          &gTrophyRankingsRawIconPositions[0],
                                          &gTrophyRankingsRawIconPositions[48] };

// DrawTextures for Dino Domain ghost background.
DrawTexture gDrawTexDinoDomainGhostBg[] = { { NULL, 0, 0 },    { NULL, 64, 0 },   { NULL, 128, 0 }, { NULL, 192, 0 },
                                            { NULL, 256, 0 },  { NULL, 0, 32 },   { NULL, 64, 32 }, { NULL, 128, 32 },
                                            { NULL, 192, 32 }, { NULL, 256, 32 }, { NULL, 0, 0 } };

// DrawTextures for Sherbet Island ghost background.
DrawTexture gDrawTexSherbetIslandGhostBg[] = { { NULL, 0, 0 },    { NULL, 64, 0 },   { NULL, 128, 0 },
                                               { NULL, 192, 0 },  { NULL, 256, 0 },  { NULL, 0, 32 },
                                               { NULL, 64, 32 },  { NULL, 128, 32 }, { NULL, 192, 32 },
                                               { NULL, 256, 32 }, { NULL, 0, 0 } };

// DrawTextures for Snowflake Mountain ghost background.
DrawTexture gDrawTexSnowflakeMountainGhostBg[] = { { NULL, 0, 0 },    { NULL, 64, 0 },   { NULL, 128, 0 },
                                                   { NULL, 192, 0 },  { NULL, 256, 0 },  { NULL, 0, 32 },
                                                   { NULL, 64, 32 },  { NULL, 128, 32 }, { NULL, 192, 32 },
                                                   { NULL, 256, 32 }, { NULL, 0, 0 } };

// DrawTextures for Dragon Forest ghost background.
DrawTexture gDrawTexDragonForestGhostBg[] = { { NULL, 0, 0 },    { NULL, 64, 0 },   { NULL, 128, 0 }, { NULL, 192, 0 },
                                              { NULL, 256, 0 },  { NULL, 0, 32 },   { NULL, 64, 32 }, { NULL, 128, 32 },
                                              { NULL, 192, 32 }, { NULL, 256, 32 }, { NULL, 0, 0 } };

// DrawTextures for Future Fun Land ghost background.
DrawTexture gDrawTexFutureFunLandGhostBg[] = { { NULL, 0, 0 },    { NULL, 64, 0 },   { NULL, 128, 0 },
                                               { NULL, 192, 0 },  { NULL, 256, 0 },  { NULL, 0, 32 },
                                               { NULL, 64, 32 },  { NULL, 128, 32 }, { NULL, 192, 32 },
                                               { NULL, 256, 32 }, { NULL, 0, 0 } };

DrawTexture *gDrawTexWorldBgs[5] = {
    gDrawTexDinoDomainGhostBg,        // Dino Domain
    gDrawTexSherbetIslandGhostBg,     // Sherbet Island
    gDrawTexSnowflakeMountainGhostBg, // Snowflake Mountain
    gDrawTexDragonForestGhostBg,      // Dragon Forest
    gDrawTexFutureFunLandGhostBg      // Future Fun Land
};

s16 gGhostDataObjectIndices[34] = { 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
                                    0x1A, 0x1B, 0x1C, 0x1D, 0x32, 0x33, 0x34, 0x36, 0x35, 0x37, 0x38, 0x39,
                                    0x3A, 0x3B, 0x00, 0x01, 0x04, 0x3D, 0x3C, 0x3F, 0x3E, -1 };

s16 gGhostDataImageIndices[4] = { 0, 1, 7, -1 };

s16 gGhostDataElementPositions[10] = { 0x78, 0x12, 0x08, 0x06, 0xC0, 0x06, 0xD4, 0x1A, 0x78, 0x22 };

s16 gIntroCinematicObjectIndices[12] = { 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, -1, 0 };

Gfx dCreditsFade[11] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsSPEndDisplayList(),
};

s16 gCreditsObjectIndices[12] = {
    0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, -1, 0
};

s16 gCreditsImageIndices[2] = { -1, 0 };

#define CREDITS_END (0x1000)
#define CREDITS_NEW_TITLE(seconds) (0x2000 | ((s16) (seconds * 60.0)))
#define CREDITS_CONTINUE_TITLE(seconds) (0x3000 | ((s16) (seconds * 60.0)))
#define CREDITS_NEXT_LEVEL (0x4000)
#define CREDITS_DEV_TIMES(seconds) (0x6000 | ((s16) (seconds * 60.0)))

// Number of seconds for each section in the credits.
#define CREDITS_DEFAULT_TITLE_TIME 2.75
#define CREDITS_MAGIC_CODE_TIME 4.5
#define CREDITS_DEV_TIMES_TIME 8.334

// Data used to control the credits.
s16 gCreditsControlData[] = {
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    0, // "CREDITS"
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    1,
    2, // "Software Director", "R.Harrison"
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    3,
    4,
    5,
    6,
    CREDITS_NEXT_LEVEL,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    7,
    8,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    9,
    10,
    11,
    12,
    CREDITS_CONTINUE_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    13,
    14,
    15,
    CREDITS_NEXT_LEVEL,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    16,
    17,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    18,
    19,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    20,
    CREDITS_NEXT_LEVEL,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    21,
    22,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    23,
    24,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    25,
    26,
    CREDITS_NEXT_LEVEL,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    27,
    28,
    29,
    30,
    31,
    CREDITS_CONTINUE_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    32,
    33,
    34,
    35,
    CREDITS_CONTINUE_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    36,
    37,
    38,
    CREDITS_NEXT_LEVEL,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    39,
    40,
    41,
    42,
    43,
    CREDITS_CONTINUE_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    44,
    45,
    46,
    CREDITS_CONTINUE_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    47,
    48,
    49,
    CREDITS_NEXT_LEVEL,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    50,
    51,
    52,
    53,
    54,
    CREDITS_CONTINUE_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    55,
    56,
    57,
    58,
    CREDITS_CONTINUE_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    59,
    60,
    61,
    62,
    CREDITS_NEXT_LEVEL,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    63,
    64,
    65,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    66,
    67,
    68,
    69,
    70,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    71,
    72,
    73,
    CREDITS_NEXT_LEVEL,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    74,
    75, // "Special Thanks To", "J.HOCHBERG"
    CREDITS_CONTINUE_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    76, // "H.LINCOLN"
    CREDITS_CONTINUE_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    77, // "M.ARAKAWA"
    CREDITS_NEXT_LEVEL,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    78,
    79,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    80,
    81,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    82,
    83,
    CREDITS_NEXT_LEVEL,
    CREDITS_NEW_TITLE(CREDITS_DEFAULT_TITLE_TIME),
    84, // "THE END"
    CREDITS_NEW_TITLE(CREDITS_MAGIC_CODE_TIME),
    85,
    86, // Magic Code Description, Magic Code
    CREDITS_NEXT_LEVEL,
    CREDITS_END, // Set to CREDITS_DEV_TIMES(CREDITS_DEV_TIMES_TIME) if you've beaten wizpig 2.
    0,
    1,
    2,
    3,
    CREDITS_NEXT_LEVEL,
    CREDITS_DEV_TIMES(CREDITS_DEV_TIMES_TIME),
    4,
    5,
    6,
    7,
    CREDITS_NEXT_LEVEL,
    CREDITS_DEV_TIMES(CREDITS_DEV_TIMES_TIME),
    8,
    9,
    10,
    11,
    CREDITS_NEXT_LEVEL,
    CREDITS_DEV_TIMES(CREDITS_DEV_TIMES_TIME),
    12,
    13,
    14,
    15,
    CREDITS_NEXT_LEVEL,
    CREDITS_DEV_TIMES(CREDITS_DEV_TIMES_TIME),
    16,
    17,
    18,
    19,
    CREDITS_NEXT_LEVEL,
    CREDITS_END
};

// List of amazing people.
char *gCreditsArray[87] = { "CREDITS",
                            "Software Director",
                            "R.Harrison",
                            "Software Engineers",
                            "P.Mountain",
                            "J.Pegg",
                            "R.Gale",
                            "Art Director",
                            "K.Bayliss",
                            "3D Artists",
                            "L.Musgrave",
                            "K.Rabbette",
                            "D.Smith",
                            "J.Christensen",
                            "B.Smyth",
                            "P.Cunningham",
                            "Music",
                            "D.Wise",
                            "Sound Effects",
                            "G.Norgate",
                            "ALSO",
                            "Additional Design",
                            "M.Wakeley",
                            "Documentation",
                            "L.Loveday",
                            "Liason",
                            "E.Hochberg",
                            "Character Voices",
                            "K.Bayliss",
                            "J.Christensen",
                            "E.Fischer",
                            "K.Rabbette",
                            "L.Ray",
                            "L.Schuneman",
                            "C.Seavor",
                            "D.Smith",
                            "J.Stamper",
                            "K.Stamper",
                            "C.Sutherland",
                            "Rare Quality Assurance",
                            "H.Ward",
                            "G.Richards",
                            "S.Farmer",
                            "J.Williams",
                            "D.Wong",
                            "G.Jones",
                            "M.Penny",
                            "S.Brand",
                            "S.Malpass",
                            "A.Wilson",
                            "NOA Thanks To",
                            "M.Fukuda",
                            "K.Lobb",
                            "M.Kelbaugh",
                            "A.Williams",
                            "R.Johnson",
                            "M.Forrest",
                            "P.Sandhop",
                            "H.Sterchi",
                            "T.Hertzog",
                            "D.Bridgham",
                            "G.Richardson",
                            "B.Smith",
                            "NOA Thanks To",
                            "NOA Tree House",
                            "NOA Tree Branch",
                            "NCL Thank You's",
                            "K.Terasaki",
                            "M.Goto",
                            "H.Yamada",
                            "Mario Club",
                            "NOE Thank You's",
                            "J.Kraft",
                            "J.Bardakoff",
                            "Special Thanks To",
                            "J.Hochberg",
                            "H.Lincoln",
                            "M.Arakawa",
                            "Game Director",
                            "L.Schuneman",
                            "Producer",
                            "C.Stamper",
                            "Executive Producer",
                            "T.Stamper",
                            NULL,
                            NULL,
                            NULL };

// Developer's best times for each track
char *gCreditsBestTimesArray[20] = {
    /***** Dino Domain *****/ "0:53:43", "1:21:55", "0:54:13", "1:22:48",
    /** Snowflake Mountain */ "1:04:11", "1:13:51", "1:25:01", "0:55:05",
    /**** Sherbet Island ***/ "1:37:63", "1:56:60", "0:57:81", "1:28:01",
    /**** Dragon Forest ****/ "1:51:15", "1:31:80", "2:03:16", "0:58:25",
    /*** Future Fun Land ***/ "2:00:38", "2:05:68", "1:52:96", "1:55:00"
};

char *gCreditsLastMessageArray[5] = {
    "THE END?", "TO BE CONTINUED ...", // Appears after beating the first wizpig race.
    "THE END",                         // Appears after beating the second wizpig race.
    "NO CHEAT", "THIS TIME.",          // Appears if you use the "WHODIDTHIS" cheat.
};

// Cheats that are shown in the credits.
s32 gCheatsInCreditsArray[21] = { CHEAT_BIG_CHARACTERS,
                                  CHEAT_SMALL_CHARACTERS,
                                  CHEAT_MUSIC_MENU,
                                  CHEAT_START_WITH_10_BANANAS,
                                  CHEAT_HORN_CHEAT,
                                  CHEAT_DISPLAY_CREDITS,
                                  CHEAT_DISABLE_WEAPONS,
                                  CHEAT_DISABLE_BANANAS,
                                  CHEAT_BANANAS_REDUCE_SPEED,
                                  CHEAT_NO_LIMIT_TO_BANANAS,
                                  CHEAT_ALL_BALLOONS_ARE_RED,
                                  CHEAT_ALL_BALLOONS_ARE_GREEN,
                                  CHEAT_ALL_BALLOONS_ARE_BLUE,
                                  CHEAT_ALL_BALLOONS_ARE_YELLOW,
                                  CHEAT_ALL_BALLOONS_ARE_RAINBOW,
                                  CHEAT_MAXIMUM_POWER_UP,
                                  CHEAT_TURN_OFF_ZIPPERS,
                                  CHEAT_SELECT_SAME_PLAYER,
                                  CHEAT_FOUR_WHEEL_DRIVER,
                                  CHEAT_TWO_PLAYER_ADVENTURE,
                                  CHEAT_ULTIMATE_AI };
#define NUMBER_CHEATS_IN_CREDITS sizeof(gCheatsInCreditsArray) / sizeof(s32)

s32 gViewingCreditsFromCheat = FALSE; // Set to 1 if viewing credits from "WHODIDTHIS" cheat

MenuElement gCreditsMenuElements[9] = {
    { 480, 104, 160, 104, -160, 104, 255, 0, 255, 48, 255, ASSET_FONTS_FUNFONT, 4, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, { { 0, 0, 0, 0 } } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { NULL }, { { 0, 0, 0, 0 } } },
};

Gfx dMenuHudSettings[] = {
    gsDPPipeSync(),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_FOG),
    gsSPEndDisplayList(),
};

UNUSED Gfx dMenuHudDrawModes[][2] = {
    {
        gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
        gsDPSetOtherMode(DKR_OMH_1CYC_BILERP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    },
    {
        gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
        gsDPSetOtherMode(DKR_OMH_1CYC_POINT_NOPERSP, DKR_OML_COMMON | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    }
};

// Triangle indices for the wood panels used in multiple menus.
s8 gWoodPanelsIndices[32] = { 0,  1,  2,  0,  2,  3,  4,  5,  6,  4,  6,  7,  8,  9,  10, 8,
                              10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 0,  0 };

// UV coordinate indices the wood panels.
u8 gWoodPanelTexCoords[5][12] = { { 0, 0, 3, 0, 2, 1, 0, 0, 2, 1, 1, 1 },
                                  { 2, 1, 3, 0, 3, 3, 2, 1, 3, 3, 2, 2 },
                                  { 1, 2, 2, 2, 3, 3, 1, 2, 3, 3, 0, 3 },
                                  { 0, 0, 1, 1, 1, 2, 0, 0, 1, 2, 0, 3 },
                                  { 1, 1, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2 } };

// Position offsets for the wood panels.
u16 gWoodPanelVertCoords[10][4] = { { 0, 0, 256, 0 },         { 511, 255, 1, 255 },   { 511, 255, 256, 0 },
                                    { 256, -256, 511, -255 }, { 1, -255, 511, -255 }, { 256, -256, 0, -256 },
                                    { 0, 0, 1, 255 },         { 1, -255, 0, -256 },   { 1, 255, 511, 255 },
                                    { 511, -255, 1, -255 } };

// Colour filter, used for the shadows on the side of the panels.
s16 gWoodPanelVertColours[5][4] = {
    { 216, 216, 216, 256 }, // Colour for top part of the panel
    { 176, 176, 176, 256 }, // Colour for right part of the panel
    { 96, 96, 96, 256 },    // Colour for bottom part of the panel
    { 136, 136, 136, 256 }, // Colour for left part of the panel
    { 256, 256, 256, 256 }  // Colour for the center of the panel
};

s32 *gWoodPanelVertices[2] = { NULL, NULL };

s32 *gWoodPanelTriangles[2] = { NULL, NULL };

s32 D_800E1DB4 = 0;
s32 gWoodPanelCount = 0;
s32 gWoodPanelAllocCount = 0;

// U tex scale for wood panels (32 is 1.0x)
s32 gWoodPanelTexScaleU = 32;
// V tex scale for wood panels (32 is 1.0x)
s32 gWoodPanelTexScaleV = 32;

// Related to the file select wood panel highlight.
s16 D_800E1DC8[16] = { 1, 1, -1, 1, -1, 1, -1, -1, 1, -1, -1, -1, 1, 1, 1, -1 };

// Fade transition from the logo screen to the title screen.
FadeTransition gFadeLogoToTitleScreen = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 120, -1);

char gRareCopyrightString[24] = "(C) COPYRIGHT RARE 1997";

// Fade transition between levels in the title screen demo.
FadeTransition gFadeTitleScreenDemo = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 52, -1);

// Used in func_800853D0(). Used for controller pak adventure saves.
// So the first save in the pak would be (ADV.A), second save (ADV.B), etc.
char *gConPakAdvSavePrefix = " (ADV.";

/*******************************/

/************ .rodata ************/

const char D_800E8208[] = "OK?";
const char D_800E820C[] = "~";
const char D_800E8210[] = "DEL";
const char D_800E8214[] = "OK";
const char gROMChecksum[] = "ROM checksum %08X,%d\n"; // Used with the "DODGYROMMER" cheat.
const char D_800E8230[] = "OK?";
const char D_800E8234[] = "OK?";
const char D_800E8238[] = "OK?";
const char D_800E823C[] = "OK?";
const char D_800E8240[] = "OK?";
const char D_800E8244[] = "SP";
const char D_800E8248[] = "DEL";
const char D_800E824C[] = "OK";
const char D_800E8250[] = "loadFrontEndItem() - Item no %d out of range 0-%d\n";

/*********************************/

#ifdef NON_EQUIVALENT

// Should be functionally equivalent
void load_menu_text(s32 language) {
    s32 start, langIndex, i, j;

    if (gMenuTextLangTable == NULL) {
        gMenuTextLangTable = load_asset_section_from_rom(ASSET_MENU_TEXT_TABLE);
    }

    switch (language) {
        case LANGUAGE_JAPANESE:
            langIndex = 4;
            break;
        case LANGUAGE_GERMAN:
            langIndex = 3;
            break;
        case LANGUAGE_FRENCH:
            langIndex = 2;
            break;
        default: // English
            langIndex = 1;
            break;
    }

    start = gMenuTextLangTable[langIndex];
    if (gMenuText != NULL) {
        load_asset_to_address(ASSET_MENU_TEXT, gMenuText, start, gMenuTextLangTable[langIndex + 1] - start);
        // Fill up the lookup table with proper RAM addresses
        for (i = 0; i < gMenuTextLangTable[0]; i++) {
            if ((s32) gMenuText[i] == -1) {
                gMenuText[i] = NULL;
            } else {
                gMenuText[i] = &((u8 *) gMenuText)[(s32) gMenuText[i]];
            }
        }
        gAudioOutputStrings[0] = gMenuText[ASSET_MENU_TEXT_STEREO];                             // "STEREO"
        gAudioOutputStrings[1] = gMenuText[ASSET_MENU_TEXT_MONO];                               // "MONO"
        gAudioOutputStrings[2] = gMenuText[ASSET_MENU_TEXT_HEADPHONES];                         // "HEADPHONES"
        gAudioMenuStrings[1].unkC = gMenuText[ASSET_MENU_TEXT_SFXVOLUME];                       // "SFX VOLUME"
        gAudioMenuStrings[2].unkC = gMenuText[ASSET_MENU_TEXT_MUSICVOLUME];                     // "MUSIC VOLUME"
        gAudioMenuStrings[3].unkC = gMenuText[ASSET_MENU_TEXT_RETURN];                          // "RETURN"
        gAudioMenuStrings[4].unkC = gMenuText[ASSET_MENU_TEXT_AUDIOOPTIONS];                    // "AUDIO OPTIONS"
        gAudioMenuStrings[5].unkC = gMenuText[ASSET_MENU_TEXT_AUDIOOPTIONS];                    // "AUDIO OPTIONS"
        gMusicTestString = gMenuText[ASSET_MENU_TEXT_MUSICTEST];                                // "MUSIC TEST 00"
        gMagicCodeMenuStrings[0] = gMenuText[ASSET_MENU_TEXT_ENTERCODE];                        // "ENTER CODE"
        gMagicCodeMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_CLEARALLCODES];                    // "CLEAR ALL CODES"
        gMagicCodeMenuStrings[2] = gMenuText[ASSET_MENU_TEXT_CODELIST];                         // "CODE LIST"
        gMagicCodeMenuStrings[3] = gMenuText[ASSET_MENU_TEXT_RETURN];                           // "RETURN"
        gRaceResultsMenuElements[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_LAPTIMES];    // "LAP TIMES"
        gRaceResultsMenuElements[2].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_OVERALLTIME]; // "OVERALL TIME"
        gRaceOrderMenuElements[8].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_RACEORDER];     // "RACE ORDER"
        gRaceOrderMenuElements[9].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_RACEORDER];     // "RACE ORDER"
        gRecordTimesMenuElements[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_RECORDTIMES]; // "RECORD TIMES"
        gRecordTimesMenuElements[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_RECORDTIMES]; // "RECORD TIMES"
        gRecordTimesMenuElements[2].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_BESTTIME];    // "BEST TIME"
        gRecordTimesMenuElements[5].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_BESTLAP];     // "BEST LAP"
        gOptionMenuStrings[0] = gMenuText[ASSET_MENU_TEXT_LANGUAGE];                            // "ENGLISH"
        if (sEepromSettings & 0x2000000) {
            gOptionMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_SUBTITLESON]; // "SUBTITLES ON"
        } else {
            gOptionMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_SUBTITLESOFF]; // "SUBTITLES OFF"
        }
        gOptionMenuStrings[2] = gMenuText[ASSET_MENU_TEXT_AUDIOOPTIONS];             // "AUDIO OPTIONS"
        gOptionMenuStrings[3] = gMenuText[ASSET_MENU_TEXT_SAVEOPTIONS];              // "SAVE OPTIONS"
        gOptionMenuStrings[4] = gMenuText[ASSET_MENU_TEXT_MAGICCODES];               // "MAGIC CODES"
        gOptionMenuStrings[5] = gMenuText[ASSET_MENU_TEXT_RETURN];                   // "RETURN"
        gFilenames[0] = gMenuText[ASSET_MENU_TEXT_GAMEA];                            // "GAME A"
        gFilenames[1] = gMenuText[ASSET_MENU_TEXT_GAMEB];                            // "GAME B"
        gFilenames[2] = gMenuText[ASSET_MENU_TEXT_GAMEC];                            // "GAME C"
        gContPakNotPresentStrings[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];          // "CONTROLLER PAK ~"
        gContPakNotPresentStrings[1] = gMenuText[ASSET_MENU_TEXT_CONTPAKNOTPRESENT]; // "IS NOT PRESENT."
        gContPakNotPresentStrings[3] = gMenuText[ASSET_MENU_TEXT_CANCEL];            // "CANCEL"
        gContPakCorruptDataRepairStrings[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];   // "CONTROLLER PAK ~"
        gContPakCorruptDataRepairStrings[1] =
            gMenuText[ASSET_MENU_TEXT_CONTPAKHASCORRUPTDATA_0]; // "CONTAINS CORRUPT DATA."
        gContPakCorruptDataRepairStrings[3] = gMenuText[ASSET_MENU_TEXT_CONTPAKHASCORRUPTDATA_1]; // "ATTEMPT TO REPAIR"
        gContPakCorruptDataRepairStrings[4] = gMenuText[ASSET_MENU_TEXT_CANCEL];                  // "CANCEL"
        gContPakDamagedStrings[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];                          // "CONTROLLER PAK ~"
        gContPakDamagedStrings[1] = gMenuText[ASSET_MENU_TEXT_CONTPAKISDAMAGED_0];  // "IRREPARABLY DAMAGED."
        gContPakDamagedStrings[3] = gMenuText[ASSET_MENU_TEXT_CONTPAKISDAMAGED_1];  // "REFORMAT PAK"
        gContPakDamagedStrings[4] = gMenuText[ASSET_MENU_TEXT_CANCEL];              // "CANCEL"
        gContPakFullStrings[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];               // "CONTROLLER PAK ~"
        gContPakFullStrings[1] = gMenuText[ASSET_MENU_TEXT_CONTPAKISFULL];          // "FULL."
        gContPakFullStrings[3] = gMenuText[ASSET_MENU_TEXT_CONTINUE];               // "CONTINUE"
        gContPakDiffContStrings[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];           // "CONTROLLER PAK ~"
        gContPakDiffContStrings[1] = gMenuText[ASSET_MENU_TEXT_CONTPAKDIFFERENT_0]; // "DIFFERENT CONTROLLER"
        gContPakDiffContStrings[2] = gMenuText[ASSET_MENU_TEXT_CONTPAKDIFFERENT_1]; // "PAK IS INSERTED."
        gContPakDiffContStrings[4] = gMenuText[ASSET_MENU_TEXT_CANCEL];             // "CANCEL"
        gContPakNoRoomForGhostsStrings[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];    // "CONTROLLER PAK ~"
        gContPakNoRoomForGhostsStrings[1] = gMenuText[ASSET_MENU_TEXT_CANNOTSTOREANYMOREGHOSTS_0]; // "CANNOT STORE ANY"
        gContPakNoRoomForGhostsStrings[2] = gMenuText[ASSET_MENU_TEXT_CANNOTSTOREANYMOREGHOSTS_1]; // "MORE GHOSTS."
        gContPakNoRoomForGhostsStrings[4] = gMenuText[ASSET_MENU_TEXT_CONTINUE];                   // "CONTINUE"
        gContPakCorruptDataStrings[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];                       // "CONTROLLER PAK ~"
        gContPakCorruptDataStrings[1] = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_0];                  // "CORRUPT DATA."
        gContPakCorruptDataStrings[3] = gMenuText[ASSET_MENU_TEXT_TRYAGAIN];                       // "TRY AGAIN"
        gContPakCorruptDataStrings[4] = gMenuText[ASSET_MENU_TEXT_CANCEL];                         // "CANCEL"
        gContPakRumbleDetectedStrings[0] = gMenuText[ASSET_MENU_TEXT_RUMBLEPAKDETECTED_0]; // "Rumble Pak Detected"
        gContPakRumbleDetectedStrings[1] =
            gMenuText[ASSET_MENU_TEXT_RUMBLEPAKDETECTED_1]; // "Insert any Controller Paks"
        gContPakRumbleDetectedStrings[2] = gMenuText[ASSET_MENU_TEXT_RUMBLEPAKDETECTED_2]; // "you wish to use now!"
        gContPakRumbleDetectedStrings[4] = gMenuText[ASSET_MENU_TEXT_CONTINUE];            // "CONTINUE"
        gContPakSwitchToRumbleStrings[0] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_0];      // "If you wish to use any"
        gContPakSwitchToRumbleStrings[1] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_1];      // "Rumble Paks then please"
        gContPakSwitchToRumbleStrings[2] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_2];      // "insert them now."
        gContPakSwitchToRumbleStrings[4] = gMenuText[ASSET_MENU_TEXT_CONTINUE];            // "CONTINUE"
        gContPakNeed2ndAdvStrings[0] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_0];       // "SORRY, BUT YOU"
        gContPakNeed2ndAdvStrings[1] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_1];       // "CAN'T LOAD GAMES"
        gContPakNeed2ndAdvStrings[2] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_2];       // "FOR THE SECOND"
        gContPakNeed2ndAdvStrings[3] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_3];       // "ADVENTURE UNTIL"
        gContPakNeed2ndAdvStrings[4] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_4];       // "YOU HAVE COMPLETED"
        gContPakNeed2ndAdvStrings[5] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_5];       // "THE FIRST."
        gContPakNeed2ndAdvStrings[7] = gMenuText[ASSET_MENU_TEXT_CONTINUE];                // "CONTINUE"
        gTitleMenuStrings[0] = gMenuText[ASSET_MENU_TEXT_START];                           // "START"
        gTitleMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_OPTIONS];                         // "OPTIONS"
        gGameSelectTextElemsNoAdv2[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_GAMESELECT];     // "GAME SELECT"
        gGameSelectTextElemsNoAdv2[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_GAMESELECT];     // "GAME SELECT"
        gGameSelectTextElemsNoAdv2[3].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_ADVENTURE];      // "ADVENTURE"
        gGameSelectTextElemsNoAdv2[5].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_TRACKS];         // "TRACKS"
        gGameSelectTextElemsWithAdv2[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_GAMESELECT];   // "GAME SELECT"
        gGameSelectTextElemsWithAdv2[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_GAMESELECT];   // "GAME SELECT"
        gGameSelectTextElemsWithAdv2[3].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_ADVENTURE];    // "ADVENTURE"
        gGameSelectTextElemsWithAdv2[5].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_ADVENTURETWO]; // "ADVENTURE TWO"
        gGameSelectTextElemsWithAdv2[7].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_TRACKS];       // "TRACKS"
        sBadControllerPakMenuText[0] = gMenuText[ASSET_MENU_TEXT_BADCONTPAK];   // "BAD CONTROLLER PAK"
        sControllerPakFullMenuText[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKFULL]; // "CONTROLLER PAK FULL"
        sNoControllerPakMenuText[0] = gMenuText[ASSET_MENU_TEXT_NOCONTPAK];     // 'NO CONTROLLER PAK"
        sCorruptDataMenuText[4] = NULL;
        sCorruptDataMenuText[5] = NULL;
        sCorruptDataMenuText[0] = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_0]; // "CORRUPT DATA."
        // Three messages
        //"If you wish to change" / "Controller Pak or Rumble Pak," / "please do so now."
        for (i = 0; i < 2; i++) {
            sBadControllerPakMenuText[i + 1] = gMenuText[177 + i];
            sControllerPakFullMenuText[i + 1] = gMenuText[177 + i];
            sNoControllerPakMenuText[i + 1] = gMenuText[177 + i];
            sCorruptDataMenuText[i + 1] = gMenuText[177 + i];
        }
        j = 0;
        while (sCorruptDataMenuText[j] != NULL) {
            j++;
        }
        sCorruptDataMenuText[j] = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_1];                 // "TRY AGAIN!"
        sInsertControllerPakMenuText[0] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_3];        // "If you wish to use"
        sInsertControllerPakMenuText[1] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_4];        // "the Controller Pak"
        sInsertControllerPakMenuText[2] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_6];        // "insert it now!"
        sInsertRumblePakMenuText[0] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_3];            // "If you wish to use"
        sInsertRumblePakMenuText[1] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_5];            // "the Rumble Pak"
        sInsertRumblePakMenuText[2] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_6];            // "insert it now!"
        gCautionMenuTextElements[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION]; // "CAUTION"
        gCautionMenuTextElements[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION]; // "CAUTION"
        for (i = 2; i < 13; i++) {
            // Caution message lines starting from gMenuText[166]
            gCautionMenuTextElements[i].unk14_a.asciiText = gMenuText[166 + (i - 2)];
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/load_menu_text.s")
#endif

void func_8007FF88(void) {
    if (gWoodPanelTriangles[0] != NULL) {
        free_from_memory_pool(gWoodPanelTriangles[0]);
        gWoodPanelTriangles[0] = NULL;
    }
    gWoodPanelTriangles[1] = NULL;
    D_80126C2C = NULL;
    gWoodPanelVertices[0] = NULL;
    gWoodPanelVertices[1] = NULL;
    gWoodPanelCount = 0;
    gWoodPanelAllocCount = 0;
}

GLOBAL_ASM("asm/non_matchings/menu/func_8007FFEC.s")

void func_80080518(f32 arg0, f32 arg1) {
    gWoodPanelTexScaleU = (s32) (arg0 * 32.0f);
    gWoodPanelTexScaleV = (s32) (arg1 * 32.0f);
}

// https://decomp.me/scratch/W0adv
#ifdef NON_EQUIVALENT
void func_80080580(Gfx **dlist, s32 startX, s32 startY, s32 width, s32 height, s32 borderWidth, s32 borderHeight,
                   s32 colour, TextureHeader *tex) {
    s32 uVals[4];
    s32 vVals[4];
    Vertex *verts;
    Triangle *tris;
    s32 j;
    s32 i;
    s32 texEnabled;

    //((unk80080BC8*)((u8*)D_80126C2C[gWoodPanelCount] + (D_800E1DB4 * 4)))->texture = tex;
    ((unk80080BC8 *) ((u8 *) D_80126C2C + (gWoodPanelCount << 5) + (D_800E1DB4 * 4)))->texture = tex;
    //(&(*D_80126C2C)[gWoodPanelCount] + (D_800E1DB4 * 4))->texture = tex;
    // D_80126C2C[gWoodPanelCount][D_800E1DB4].texture = tex;
    if (tex != NULL) {
        uVals[0] = 0;
        vVals[0] = 0;
        uVals[1] = gWoodPanelTexScaleU * borderWidth;
        uVals[2] = (width - borderWidth) * gWoodPanelTexScaleU;
        uVals[3] = gWoodPanelTexScaleU * width;
        vVals[1] = gWoodPanelTexScaleV * borderHeight;
        vVals[2] = (height - borderHeight) * gWoodPanelTexScaleV;
        vVals[3] = gWoodPanelTexScaleV * height;
        tris = ((unk80080BC8 *) ((u8 *) D_80126C2C + (gWoodPanelCount << 5) + (D_800E1DB4 * 4)))->triangles;
        for (i = 0; i < 5; i++) {
            tris[i * 2].uv0.u = uVals[gWoodPanelTexCoords[i][0]];
            tris[i * 2].uv0.v = vVals[gWoodPanelTexCoords[i][1]];
            tris[i * 2].uv1.u = uVals[gWoodPanelTexCoords[i][2]];
            tris[i * 2].uv1.v = vVals[gWoodPanelTexCoords[i][3]];
            tris[i * 2].uv2.u = uVals[gWoodPanelTexCoords[i][4]];
            tris[i * 2].uv2.v = vVals[gWoodPanelTexCoords[i][5]];
            tris[i * 2 + 1].uv0.u = uVals[gWoodPanelTexCoords[i][6]];
            tris[i * 2 + 1].uv0.v = vVals[gWoodPanelTexCoords[i][7]];
            tris[i * 2 + 1].uv1.u = uVals[gWoodPanelTexCoords[i][8]];
            tris[i * 2 + 1].uv1.v = vVals[gWoodPanelTexCoords[i][9]];
            tris[i * 2 + 1].uv2.u = uVals[gWoodPanelTexCoords[i][10]];
            tris[i * 2 + 1].uv2.v = vVals[gWoodPanelTexCoords[i][11]];
        }
    }
    verts = ((unk80080BC8 *) ((u8 *) D_80126C2C + (gWoodPanelCount << 5) + (D_800E1DB4 * 4)))->vertices;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 4; j++) {
            verts[j].x = startX;
            verts[j].y = startY;
            verts[j].x += (gWoodPanelVertCoords[j][0] * width);
            verts[j].x += (gWoodPanelVertCoords[j][1] * borderWidth);
            verts[j].y += (gWoodPanelVertCoords[j][2] * height);
            verts[j].y += (gWoodPanelVertCoords[j][3] * borderHeight);
            verts[j].z = 0;
            verts[j].r = (s32) (gWoodPanelVertColours[i][0] * ((colour >> 24) & 0xFF)) >> 8;
            verts[j].g = (s32) (gWoodPanelVertColours[i][1] * ((colour >> 16) & 0xFF)) >> 8;
            verts[j].b = (s32) (gWoodPanelVertColours[i][2] * ((colour >> 8) & 0xFF)) >> 8;
            verts[j].a = (s32) (gWoodPanelVertColours[i][3] * (colour & 0xFF)) >> 8;
        }
    }
    if (dlist != NULL) {
        ((unk80080BC8 *) ((u8 *) D_80126C2C + (gWoodPanelCount << 5) + (D_800E1DB4 * 4)))->unk18 = 1;
        gSPDisplayList((*dlist)++, &dMenuHudSettings);
        if (tex != NULL) {
            texEnabled = TRUE;
            gDkrDmaDisplayList((*dlist)++, OS_K0_TO_PHYSICAL(&dMenuHudSettings[8]), 2);
            gDkrDmaDisplayList((*dlist)++, OS_K0_TO_PHYSICAL(tex->cmd), tex->numberOfCommands);
        } else {
            texEnabled = FALSE;
            gDkrDmaDisplayList((*dlist)++, OS_K0_TO_PHYSICAL(&dMenuHudSettings[6]), 2);
        }
        gDPPipeSync((*dlist)++);
        /*
        temp_v0_6 = *dlist;
        *dlist = temp_v0_6 + 8;
        temp_v0_6->words.w0 = (((((*(D_80126C2C + (gWoodPanelCount << 5) + (D_800E1DB4 * 4)) + 0x80000000) & 6) | 0x98)
        & 0xFF) << 0x10) | 0x04000000 | 0x170; temp_v0_6->words.w1 = *(D_80126C2C + (gWoodPanelCount << 5) + (D_800E1DB4
        * 4)) + 0x80000000;
        */
        gSPVertexDKR((*dlist)++,
                     OS_K0_TO_PHYSICAL(((unk80080BC8 *) ((u8 *) D_80126C2C + (i * 32) + (D_800E1DB4 * 4)))->vertices),
                     20, 0);
        /*
        temp_v0_7 = *dlist;
        *dlist = temp_v0_7 + 8;
        temp_v0_7->words.w0 = (((texEnabled | 0x90) & 0xFF) << 0x10) | 0x05000000 | 0xA0;
        temp_v0_7->words.w1 = (D_80126C2C + (gWoodPanelCount << 5) + (D_800E1DB4 * 4))->unk8 + 0x80000000;
        */
        gSPPolygon((*dlist)++,
                   OS_K0_TO_PHYSICAL(((unk80080BC8 *) ((u8 *) D_80126C2C + (i * 32) + (D_800E1DB4 * 4)))->triangles),
                   10, texEnabled);
        reset_render_settings(dlist);
    } else {
        ((unk80080BC8 *) ((u8 *) D_80126C2C + (gWoodPanelCount * 32) + (D_800E1DB4 * 4)))->unk18 = 0;
    }
    gWoodPanelCount++;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80080580.s")
#endif

// https://decomp.me/scratch/lS3f5
#ifdef NON_EQUIVALENT
void func_80080BC8(Gfx **dlist) {
    s16 temp_a1;
    s32 i;
    s32 var_t0;
    TextureHeader *tex;
    TextureHeader *lastTex;

    gSPDisplayList((*dlist)++, &dMenuHudSettings);
    var_t0 = -1;
    lastTex = NULL;

    for (i = 0; i < gWoodPanelCount; i++) {
        //((unk80080BC8*)((u8*)D_80126C2C + (i << 5) + (D_800E1DB4 * 4)))->texture
        if (!D_80126C2C[i][D_800E1DB4].unk18) {
            tex = D_80126C2C[i][D_800E1DB4].texture;
            if (tex != NULL) {
                if (var_t0 != 1) {
                    var_t0 = 1;
                    gDkrDmaDisplayList((*dlist)++, OS_K0_TO_PHYSICAL(&dMenuHudSettings[8]), 2);
                }
                if (lastTex != tex) {
                    gDkrDmaDisplayList((*dlist)++, OS_K0_TO_PHYSICAL(tex->cmd), tex->numberOfCommands);
                    lastTex = tex;
                }
            } else if (var_t0 != 0) {
                var_t0 = 0;
                gDkrDmaDisplayList((*dlist)++, OS_K0_TO_PHYSICAL(&dMenuHudSettings[6]), 2);
            }
            gDPPipeSync((*dlist)++);
            gSPVertexDKR((*dlist)++, OS_K0_TO_PHYSICAL((&D_80126C2C[i][D_800E1DB4])->vertices), 20, 0);
            gSPPolygon((*dlist)++, OS_K0_TO_PHYSICAL((&D_80126C2C[i][D_800E1DB4])->triangles), 10, 0);
        }
    }
    gWoodPanelCount = 0;
    D_800E1DB4 = 1 - D_800E1DB4;
    reset_render_settings(dlist);
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80080BC8.s")
#endif

void func_80080E6C(void) {
    gWoodPanelCount = 0;
    D_800E1DB4 = (s32) (1 - D_800E1DB4);
}

// https://decomp.me/scratch/IZ1Gq
GLOBAL_ASM("asm/non_matchings/menu/func_80080E90.s")

// init_save_data
#ifdef NON_EQUIVALENT
// Should be functionally equivalent.
void func_80081218(void) {
    s32 numLevels; // sp34
    s32 numWorlds; // sp30
    s32 i;
    s32 sp28;
    s32 sp20;

    get_number_of_levels_and_worlds(&numLevels, &numWorlds);
    sp20 = ((numLevels * 4) + (numWorlds * 2) + 0x11B) & ~3;
    sp28 = numLevels * 4;
    gSavefileData[0] = allocate_from_main_pool_safe(sp20 * 4, COLOUR_TAG_WHITE);
    gSavefileData[0] = gSavefileData[0];
    gSavefileData[0]->courseFlagsPtr = (u8 *) gSavefileData[0] + sizeof(Settings);
    gSavefileData[0]->balloonsPtr = (u8 *) gSavefileData[0]->courseFlagsPtr + sp28;
    gSavefileData[1] = (u8 *) gSavefileData[0] + sp20;
    gSavefileData[1]->courseFlagsPtr = (u8 *) gSavefileData[1] + sizeof(Settings);
    gSavefileData[1]->balloonsPtr = (u8 *) gSavefileData[1]->courseFlagsPtr + sp28;
    gSavefileData[2] = (u8 *) gSavefileData[1] + sp20;
    gSavefileData[2]->courseFlagsPtr = (u8 *) gSavefileData[2] + sizeof(Settings);
    gSavefileData[2]->balloonsPtr = (u8 *) gSavefileData[2]->courseFlagsPtr + sp28;
    gSavefileData[3] = (u8 *) gSavefileData[2] + sp20;
    gSavefileData[3]->courseFlagsPtr = (u8 *) gSavefileData[3] + sizeof(Settings);
    gSavefileData[3]->balloonsPtr = (u8 *) gSavefileData[3]->courseFlagsPtr + sp28;
    gCheatsAssetData = get_misc_asset(ASSET_MISC_MAGIC_CODES);
    gNumberOfCheats = (s32) (*gCheatsAssetData);
    gMenuText = allocate_from_main_pool_safe(1024 * sizeof(char *), COLOUR_TAG_WHITE);
    load_menu_text(LANGUAGE_ENGLISH);
    for (i = 0; i < 128; i++) {
        gMenuObjects[i] = NULL;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80081218.s")
#endif

/**
 * Sets the title reveal timer to zero when the menu boots, meaning it may not automatically appear.
 */
void reset_title_logo_scale(void) {
    gResetTitleScale = TRUE;
}

/**
 * Core function for initialising all menu elements.
 * Gets the current menu ID, then runs the init function of the respective menu element.
 */
void menu_init(u32 menuId) {
    s32 i;

    gCurrentMenuId = menuId;
    reset_controller_sticks();
    gIgnorePlayerInputTime = 1;
    gOptionBlinkTimer = 0;
    sUnused_801263C8 = 0;
    sUnused_80126828 = 0;

    // clang-format off
    // Needs to be one line
    for (i = 0; i < ARRAY_COUNT(D_80126808); i++) { D_80126808[i] = 0; }
    // clang-format on

    music_stop();
    switch (gCurrentMenuId) {
        case MENU_LOGOS:
            menu_logos_screen_init();
            break;
        case MENU_TITLE:
            menu_title_screen_init();
            break;
        case MENU_OPTIONS:
            menu_options_init();
            break;
        case MENU_AUDIO_OPTIONS:
            menu_audio_options_init();
            break;
        case MENU_SAVE_OPTIONS:
            menu_save_options_init();
            break;
        case MENU_MAGIC_CODES:
            menu_magic_codes_init();
            break;
        case MENU_MAGIC_CODES_LIST:
            menu_magic_codes_list_init();
            break;
        case MENU_CHARACTER_SELECT:
            menu_character_select_init();
            break;
        case MENU_GAME_SELECT:
            menu_game_select_init();
            break;
        case MENU_FILE_SELECT:
            menu_file_select_init();
            break;
        case MENU_TRACK_SELECT:
            menu_track_select_init();
            break;
        case MENU_TRACK_SELECT_ADVENTURE:
            menu_adventure_track_init();
            break;
        case MENU_RESULTS:
            menu_results_init();
            break;
        case MENU_TROPHY_RACE_ROUND:
            menu_trophy_race_round_init();
            break;
        case MENU_TROPHY_RACE_RANKINGS:
            menu_trophy_race_rankings_init();
            break;
        case MENU_NEWGAME_CINEMATIC:
            menu_cinematic_init();
            break;
        case MENU_GHOST_DATA:
            menu_ghost_data_init();
            break;
        case MENU_CREDITS:
            menu_credits_init();
            break;
        case MENU_BOOT:
            menu_boot_init();
            break;
        case MENU_CAUTION:
            menu_caution_init();
            break;
    }
    sUnused_80126470 = 0xD000;
}

/**
 * Runs every frame. Calls the loop function of the current menu id
 */
s32 menu_loop(Gfx **currDisplayList, MatrixS **currHudMat, Vertex **currHudVerts, TriangleList **currHudTris,
              s32 updateRate) {
    s32 ret;

    sMenuCurrDisplayList = *currDisplayList;
    sMenuCurrHudMat = *currHudMat;
    sMenuCurrHudVerts = *currHudVerts;
    sMenuCurrHudTris = *currHudTris;

    update_controller_sticks();
    switch (gCurrentMenuId) {
        case MENU_LOGOS:
            ret = menu_logo_screen_loop(updateRate);
            break;
        case MENU_TITLE:
            ret = menu_title_screen_loop(updateRate);
            break;
        case MENU_OPTIONS:
            ret = menu_options_loop(updateRate);
            break;
        case MENU_AUDIO_OPTIONS:
            ret = menu_audio_options_loop(updateRate);
            break;
        case MENU_SAVE_OPTIONS:
            ret = menu_save_options_loop(updateRate);
            break;
        case MENU_MAGIC_CODES:
            ret = menu_magic_codes_loop(updateRate);
            break;
        case MENU_MAGIC_CODES_LIST:
            ret = menu_magic_codes_list_loop(updateRate);
            break;
        case MENU_CHARACTER_SELECT:
            ret = menu_character_select_loop(updateRate);
            break;
        case MENU_FILE_SELECT:
            ret = menu_file_select_loop(updateRate);
            break;
        case MENU_GAME_SELECT:
            ret = menu_game_select_loop(updateRate);
            break;
        case MENU_TRACK_SELECT:
            ret = menu_track_select_loop(updateRate);
            break;
        case MENU_TRACK_SELECT_ADVENTURE:
            ret = menu_adventure_track_loop(updateRate);
            break;
        case MENU_RESULTS:
            ret = menu_results_loop(updateRate);
            break;
        case MENU_TROPHY_RACE_ROUND:
            ret = menu_trophy_race_round_loop(updateRate);
            break;
        case MENU_TROPHY_RACE_RANKINGS:
            ret = menu_trophy_race_rankings_loop(updateRate);
            break;
        case MENU_NEWGAME_CINEMATIC:
            ret = menu_cinematic_loop(updateRate);
            break;
        case MENU_GHOST_DATA:
            ret = menu_ghost_data_loop(updateRate);
            break;
        case MENU_CREDITS:
            ret = menu_credits_loop(updateRate);
            break;
        case MENU_BOOT:
            ret = menu_boot_loop(updateRate);
            break;
        case MENU_CAUTION:
            ret = menu_caution_loop(updateRate);
            break;
    }
    *currDisplayList = sMenuCurrDisplayList;
    *currHudMat = sMenuCurrHudMat;
    *currHudVerts = sMenuCurrHudVerts;
    *currHudTris = sMenuCurrHudTris;
    return ret;
}

void show_timestamp(s32 frameCount, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 fontID) {
    s32 minutes;
    s32 seconds;
    s32 hundredths;
    s32 xOffset1;
    s32 imageIndex2;
    s32 imageIndex;
    s32 xOffset2;
    s32 xOffset3;

    sMenuGuiColourR = red;
    sMenuGuiColourG = green;
    sMenuGuiColourB = blue;
    if (fontID == ASSET_FONTS_FUNFONT) {
        gMenuImageStack[0].unk10 = yPos;
        gMenuImageStack[1].unk10 = yPos - 2;
        imageIndex = 0;
        imageIndex2 = 1;
        xPos -= 39;
        xOffset1 = 12;
        xOffset2 = 11;
        xOffset3 = 10;
    } else {
        gMenuImageStack[2].unk10 = yPos;
        gMenuImageStack[3].unk10 = yPos - 1;
        imageIndex = 2;
        imageIndex2 = 3;
        xPos -= 28;
        xOffset1 = 9;
        xOffset2 = 9;
        xOffset3 = 5;
    }
    get_timestamp_from_frames(frameCount, &minutes, &seconds, &hundredths);
    func_80068508(TRUE);
    sprite_opaque(FALSE);

    gMenuImageStack[imageIndex].unk18 = minutes / 10;
    gMenuImageStack[imageIndex].unkC = xPos;
    func_8009CA60(imageIndex);

    xPos += xOffset1;
    gMenuImageStack[imageIndex].unk18 = minutes % 10;
    gMenuImageStack[imageIndex].unkC = xPos;
    func_8009CA60(imageIndex);

    xPos += xOffset2;
    gMenuImageStack[imageIndex2].unkC = xPos;
    func_8009CA60(imageIndex2);

    xPos += xOffset3;
    gMenuImageStack[imageIndex].unk18 = seconds / 10;
    gMenuImageStack[imageIndex].unkC = xPos;
    func_8009CA60(imageIndex);

    xPos += xOffset1;
    gMenuImageStack[imageIndex].unk18 = seconds % 10;
    gMenuImageStack[imageIndex].unkC = xPos;
    func_8009CA60(imageIndex);

    xPos += xOffset2;
    gMenuImageStack[imageIndex2].unkC = xPos;
    func_8009CA60(imageIndex2);

    xPos += xOffset3;
    gMenuImageStack[imageIndex].unk18 = hundredths / 10;
    gMenuImageStack[imageIndex].unkC = xPos;
    func_8009CA60(imageIndex);

    xPos += xOffset1;
    gMenuImageStack[imageIndex].unk18 = hundredths % 10;
    gMenuImageStack[imageIndex].unkC = xPos;
    func_8009CA60(imageIndex);

    func_80068508(FALSE);
    sprite_opaque(TRUE);
    sMenuGuiColourR = (u8) 255;
    sMenuGuiColourG = (u8) 255;
    sMenuGuiColourB = (u8) 255;
}

void func_80081C04(s32 number, s32 x, s32 y, s32 r, s32 g, s32 b, s32 a, UNUSED s32 font, s32 alignment) {
    s32 strLen;
    s32 powerOfTen;
    s32 i;
    s32 hasProcessedDigit;
    s32 curDigit;
    UNUSED s32 pad[2];
    u8 digits[10];

    strLen = 0;
    powerOfTen = 1000000000;
    hasProcessedDigit = FALSE;

    while (powerOfTen >= 10) {
        if (number >= powerOfTen) {
            curDigit = number / powerOfTen;
            number -= curDigit * powerOfTen;
            digits[strLen++] = curDigit;
            hasProcessedDigit = TRUE;
        } else if (hasProcessedDigit) {
            digits[strLen++] = 0;
        }
        powerOfTen /= 10;
    }

    digits[strLen++] = number;
    if (alignment & HORZ_ALIGN_CENTER) {
        x -= strLen * 12;
        x += 6;
    } else if (alignment & HORZ_ALIGN_RIGHT) {
        x -= (strLen * 11) >> 1;
    } else {
        x += 6;
    }
    if (alignment & VERT_ALIGN_MIDDLE) {
        y += 7;
    } else if (alignment & 0x10) {
        y -= 7;
    }
    sMenuGuiColourR = r;
    sMenuGuiColourG = g;
    sMenuGuiColourB = b;
    sMenuGuiOpacity = a;
    sprite_opaque(0);
    func_80068508(TRUE);
    if (powerOfTen && number) {} // Fakematch
    gMenuImageStack[0].unk10 = y;
    for (i = 0; i < strLen; i++) {
        gMenuImageStack[0].unkC = x;
        gMenuImageStack[0].unk18 = digits[i];
        func_8009CA60(0);
        x += 12;
    }
    sprite_opaque(1);
    func_80068508(FALSE);
    sMenuGuiColourR = 255;
    sMenuGuiColourG = 255;
    sMenuGuiColourB = 255;
    sMenuGuiOpacity = 255;
}

void func_80081E54(MenuElement *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    gTrophyRankingsMenuElements = arg0;
    gTrophyRankingsState = 0;
    D_80126858 = arg1 * 60.0f;
    D_8012685C = arg2 * 60.0f;
    D_80126860 = arg3 * 60.0f;
    D_80126854 = 0;
    gDrawElementsRegionYOffset = arg4;
    gDrawElementsYOffset = arg5;
    if (D_80126858 > 0) {
        sound_play(SOUND_WHOOSH1, NULL);
    }
}

s32 func_80081F4C(s32 updateRate) {
    f32 scale;
    s32 ret;
    s32 i;
    s32 buttonsPressedAllPlayers;

    ret = 1;
    scale = -1.0f;
    buttonsPressedAllPlayers = 0;
    if (gTrophyRankingsState != 4) {
        if (gIgnorePlayerInputTime == 0) {
            for (i = 0; i < gNumberOfActivePlayers; i++) {
                buttonsPressedAllPlayers |= get_buttons_pressed_from_player(i);
            }
        }
        D_80126854 += updateRate;
        do {
            switch (gTrophyRankingsState) {
                case 0:
                    if (buttonsPressedAllPlayers & (A_BUTTON | START_BUTTON)) {
                        D_80126854 = 0;
                        gTrophyRankingsState = 1;
                        buttonsPressedAllPlayers = 0;
                    } else {
                        if (D_80126854 >= D_80126858) {
                            D_80126854 -= D_80126858;
                            gTrophyRankingsState = 1;
                        } else {
                            scale = (f32) D_80126854 / (f32) D_80126858;
                        }
                    }
                    break;
                case 1:
                    if (D_8012685C < 0) {
                        D_80126854 = 0;
                    }
                    if (buttonsPressedAllPlayers & (A_BUTTON | START_BUTTON)) {
                        D_80126854 = 0;
                        gTrophyRankingsState = 2;
                        buttonsPressedAllPlayers = 0;
                        if (D_80126860 > D_80126854) {
                            sound_play(SOUND_WHOOSH1, NULL);
                        }
                    } else {
                        if (D_80126854 >= D_8012685C) {
                            D_80126854 -= D_8012685C;
                            gTrophyRankingsState = 2;
                            if (D_80126854 < D_80126860) {
                                sound_play(SOUND_WHOOSH1, NULL);
                            }
                        } else {
                            scale = (f32) D_80126854 / (f32) D_8012685C;
                        }
                    }
                    break;
                case 2:
                    if ((buttonsPressedAllPlayers & (A_BUTTON | START_BUTTON)) || (D_80126854 >= D_80126860)) {
                        gTrophyRankingsState = 4;
                    } else {
                        scale = (f32) D_80126854 / (f32) D_80126860;
                    }
                    break;
            }
        } while (scale < 0.0f && gTrophyRankingsState != 4);

        if (gTrophyRankingsState != 4) {
            draw_menu_elements(gTrophyRankingsState, gTrophyRankingsMenuElements, scale);
            ret = 0;
        }
    }
    return ret;
}

void draw_menu_elements(s32 flags, MenuElement *elems, f32 scale) {
    s32 shouldResetRenderSettings;
    s32 xPos, yPos;

    shouldResetRenderSettings = FALSE;
    if (flags == 4) {
        return;
    }

    set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    while (elems->unk14_a.element != NULL) {
        if ((elems->unk14_a.element != &D_80126850)) {                      // fakematch
            if (flags == ((elems->unk14_a.element != (&D_80126850)) * 0)) { // fakematch
                xPos = ((s32) ((elems->center - elems->left) * scale)) + elems->left;
                yPos = ((s32) ((elems->middle - elems->top) * scale)) + elems->top;
            } else if ((flags == 1)) {
                xPos = elems->center;
                yPos = elems->middle;
            } else {
                xPos = ((s32) ((elems->right - elems->center) * scale)) + elems->center;
                yPos = ((s32) ((elems->bottom - elems->middle) * scale)) + elems->middle;
            }
            switch (elems->elementType) {
                case 0: // ascii text
                    set_text_background_colour(
                        elems->details.background.backgroundRed, elems->details.background.backgroundGreen,
                        elems->details.background.backgroundBlue, elems->details.background.backgroundAlpha);
                    set_text_colour(elems->filterRed, elems->filterGreen, elems->filterBlue, elems->filterBlendFactor,
                                    elems->opacity);
                    set_text_font(elems->textFont);
                    draw_text(&sMenuCurrDisplayList, xPos, yPos + gDrawElementsRegionYOffset, elems->unk14_a.asciiText,
                              elems->textAlignFlags);
                    break;
                case 1:
                    if (shouldResetRenderSettings) {
                        shouldResetRenderSettings = FALSE;
                        reset_render_settings(&sMenuCurrDisplayList);
                    }
                    sMenuGuiOpacity = elems->opacity;
                    show_timestamp(*elems->unk14_a.numberU16, xPos - 160, (-yPos - gDrawElementsYOffset) + 120,
                                   elems->filterRed, elems->filterGreen, elems->filterBlue, elems->textFont);
                    break;
                case 2: // Number
                    if (shouldResetRenderSettings) {
                        shouldResetRenderSettings = FALSE;
                        reset_render_settings(&sMenuCurrDisplayList);
                    }
                    func_80081C04(*elems->unk14_a.number, xPos - 160, (-yPos - gDrawElementsYOffset) + 120,
                                  elems->filterRed, elems->filterGreen, elems->filterBlue, elems->opacity,
                                  elems->textFont, elems->textAlignFlags);
                    break;
                case 3:
                    render_textured_rectangle(&sMenuCurrDisplayList, elems->unk14_a.drawTexture, xPos,
                                              yPos + gDrawElementsRegionYOffset, elems->filterRed, elems->filterGreen,
                                              elems->filterBlue, elems->opacity);
                    shouldResetRenderSettings = TRUE;
                    break;
                case 4:
                    render_texture_rectangle_scaled(
                        &sMenuCurrDisplayList, elems->unk14_a.element, xPos, yPos + gDrawElementsRegionYOffset,
                        elems->details.texture.width / 256.0f, elems->details.texture.height / 256.0f,
                        (elems->filterRed << 24) | (elems->filterGreen << 16) | (elems->filterBlue << 8) |
                            elems->opacity,
                        elems->textAlignFlags);
                    shouldResetRenderSettings = TRUE;
                    break;
                case 5:
                    if (shouldResetRenderSettings) {
                        shouldResetRenderSettings = FALSE;
                        reset_render_settings(&sMenuCurrDisplayList);
                    }
                    func_80068508(TRUE);
                    sprite_opaque(FALSE);
                    gMenuImageStack[elems->unk14_a.value].unkC = xPos - 160;
                    gMenuImageStack[elems->unk14_a.value].unk10 = (-yPos - gDrawElementsYOffset) + 120;
                    gMenuImageStack[elems->unk14_a.value].unk18 = elems->textFont;
                    gMenuImageStack[elems->unk14_a.value].unk4 = elems->details.background.backgroundRed;
                    gMenuImageStack[elems->unk14_a.value].unk2 = elems->details.background.backgroundGreen;
                    gMenuImageStack[elems->unk14_a.value].unk0 = elems->details.background.backgroundBlue;
                    gMenuImageStack[elems->unk14_a.value].unk8 = elems->details.background.backgroundAlpha / 256.0f;
                    sMenuGuiColourR = elems->filterRed;
                    sMenuGuiColourG = elems->filterGreen;
                    sMenuGuiColourB = elems->filterBlue;
                    sMenuGuiColourBlendFactor = elems->filterBlendFactor;
                    sMenuGuiOpacity = elems->opacity;
                    func_8009CA60(elems->unk14_a.value);
                    func_80068508(FALSE);
                    sprite_opaque(TRUE);
                    break;
                case 6:
                    func_80080E90(&sMenuCurrDisplayList, xPos, yPos + gDrawElementsYOffset,
                                  elems->details.texture.width, elems->details.texture.height,
                                  elems->details.texture.borderWidth, elems->details.texture.borderHeight,
                                  elems->filterRed, elems->filterGreen, elems->filterBlue, elems->opacity);
                    break;
                case 7: // Texture
                    func_80080580(&sMenuCurrDisplayList, xPos, yPos + gDrawElementsYOffset,
                                  elems->details.texture.width, elems->details.texture.height,
                                  elems->details.texture.borderWidth, elems->details.texture.borderHeight,
                                  (elems->filterRed << 24) | (elems->filterGreen << 16) | (elems->filterBlue << 8) |
                                      elems->opacity,
                                  elems->unk14_a.element);
                    break;
            }
        }
        elems++; // Go onto the next element.
    }
    if (shouldResetRenderSettings) {
        reset_render_settings(&sMenuCurrDisplayList);
    }
    sMenuGuiColourR = 255;
    sMenuGuiColourG = 255;
    sMenuGuiColourB = 255;
    sMenuGuiColourBlendFactor = 0;
    sMenuGuiOpacity = 255;
}

void func_800828B8(void) {
    s32 i;
    s32 numWorlds;
    s32 numLevels;
    Settings *settings;

    settings = get_settings();
    get_number_of_levels_and_worlds(&numLevels, &numWorlds);

    for (i = 0; i < numLevels; i++) {
        settings->courseFlagsPtr[i] = RACE_UNATTEMPTED;
        for (numWorlds = 0; numWorlds < NUMBER_OF_SAVE_FILES; numWorlds++) {
            settings->courseFlagsPtr[i] |= gSavefileData[numWorlds]->courseFlagsPtr[i];
        }
    }

    settings->trophies = 0;
    settings->keys = 0;
    settings->bosses = 0;
    settings->cutsceneFlags = 0;
    for (i = 0; i < NUMBER_OF_SAVE_FILES; i++) {
        settings->trophies |= gSavefileData[i]->trophies;
        settings->keys |= gSavefileData[i]->keys;
        settings->bosses |= gSavefileData[i]->bosses;
        settings->cutsceneFlags |= gSavefileData[i]->cutsceneFlags;
    }
}

void print_missing_controller_text(Gfx **dl, s32 updateRate) {
    s32 posY;

    gMissingControllerDelay += updateRate;

    if (gMissingControllerDelay & 0x10) {
        load_menu_text(get_language());
        set_text_font(ASSET_FONTS_FUNFONT);
        set_text_colour(255, 255, 255, 0, 0xFF);
        set_text_background_colour(0, 0, 0, 0);
        posY = 208;
        if (osTvType == TV_TYPE_PAL) {
            posY = 234;
        }
        draw_text(dl, POS_CENTRED, posY, gMenuText[ASSET_MENU_TEXT_CONTROLLERNOTCONNECTED], ALIGN_MIDDLE_CENTER);
    }
}

/**
 * Initialises the viewport and background settings for the screen with the rotating N64 and Rareware Logo.
 * It then sets a 16 second timer that will count down.
 */
void menu_logos_screen_init(void) {
    gMenuDelay = 0;
    sBootScreenTimer = 16.0f;
    set_background_fill_colour(0, 0, 0);
    if (osTvType == TV_TYPE_PAL) {
        viewport_menu_set(0, 0, 38, SCREEN_WIDTH, SCREEN_HEIGHT - 16);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT_PAL);
    } else {
        viewport_menu_set(0, 0, 40, SCREEN_WIDTH, SCREEN_HEIGHT - 44);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    copy_viewports_to_stack(); // Init viewports
    camEnableUserView(0, 1);
}

/**
 * Handler of everything that happens in the space of those 16 seconds.
 */
s32 menu_logo_screen_loop(s32 updateRate) {
    s32 opacity;
    s32 yOffset;
    s32 yOffsetShadow;

    if (osTvType == TV_TYPE_PAL) {
        yOffset = 26;
        if (sBootScreenTimer < 2.6f && gMenuDelay == 0) {
            transition_begin(&gFadeLogoToTitleScreen);
            gMenuDelay = 1;
        }
        sBootScreenTimer -= updateRate / 50.0f;
    } else {
        yOffset = 0;
        if (sBootScreenTimer < 2.17f && gMenuDelay == 0) {
            transition_begin(&gFadeLogoToTitleScreen);
            gMenuDelay = 1;
        }
        sBootScreenTimer -= updateRate / 60.0f;
    }
    if (sBootScreenTimer <= 0.0f) {
        camDisableUserView(0, FALSE);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, VIEWPORT_AUTO, VIEWPORT_AUTO);
        init_title_screen_variables();
        menu_init(MENU_TITLE);
    }
    // This uses doubles instead of floats for precision in the counting.
    if (sBootScreenTimer < 8.5) {
        set_text_font(ASSET_FONTS_SMALLFONT);
        set_text_background_colour(0, 0, 0, 0);
        if ((sBootScreenTimer < 8.0) && (sBootScreenTimer >= 7.5)) {
            opacity = (8.0 - sBootScreenTimer) * 510.0;
        } else {
            if ((sBootScreenTimer < 7.5) && (sBootScreenTimer >= 7.0)) {
                opacity = (sBootScreenTimer - 7.0) * 510.0;
            } else {
                opacity = 0;
            }
        }
        if (opacity != 0) {
            set_text_colour(255, 255, 0, 255, opacity);
            draw_text(&sMenuCurrDisplayList, 159, yOffset + 212, gRareCopyrightString, ALIGN_MIDDLE_CENTER);
            draw_text(&sMenuCurrDisplayList, 161, yOffset + 212, gRareCopyrightString, ALIGN_MIDDLE_CENTER);
            draw_text(&sMenuCurrDisplayList, POS_CENTRED, yOffset + 211, gRareCopyrightString, ALIGN_MIDDLE_CENTER);
            draw_text(&sMenuCurrDisplayList, POS_CENTRED, yOffset + 213, gRareCopyrightString, ALIGN_MIDDLE_CENTER);
        }
        yOffsetShadow = yOffset + 212;
        if (sBootScreenTimer > 8.0) {
            opacity = (8.5 - sBootScreenTimer) * 510.0;
        } else {
            opacity = 0xFF;
        }
        set_text_colour(0xFF, 0xFF, 0xFF, 0xFF, opacity);
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, yOffsetShadow, gRareCopyrightString, ALIGN_MIDDLE_CENTER);
    }
    return MENU_RESULT_CONTINUE;
}

/**
 * Sets some things needed after the title screen from the save buffer.
 */
void init_title_screen_variables(void) {
    if (sEepromSettings & 2) {
        set_magic_code_flags(CHEAT_CONTROL_DRUMSTICK);
    }
    if ((sEepromSettings & 0xFFFFF0) == 0xFFFFF0) {
        set_magic_code_flags(CHEAT_CONTROL_TT);
    }
    if (sEepromSettings & 1) {
        gIsInAdventureTwo = TRUE;
    } else {
        gIsInAdventureTwo = FALSE;
    }
    if ((sEepromSettings & 0x2000000) == 0) {
        set_subtitles(0);
    }
    load_menu_text(get_language());
}

#ifdef NON_MATCHING
void func_80083098(f32 arg0) {
    f32 temp;
    f32 temp2;
    s32 didUpdate;
    s32 xPos;
    s32 yPos;
    s32 i;
    unk800DF83C *introCharData;
    char *text;
    s32 j;

    didUpdate = FALSE;
    xPos = 0;
    yPos = 0;
    text = NULL;
    if (D_801268E0 < 10) {
        introCharData = &gTitleCinematicText[D_801268E0];
        D_801268D8 += arg0;
        set_text_font(ASSET_FONTS_BIGFONT);
        set_text_background_colour(0, 0, 0, 0);
        i = 0;
        while (i < gTitleCinematicTextColourCount) {
            // set_text_colour(gTitleCinematicTextColours[D_80126878[i].colourIndex].red,
            // gTitleCinematicTextColours[D_80126878[i].colourIndex].green,
            // gTitleCinematicTextColours[D_80126878[i].colourIndex].blue,
            // gTitleCinematicTextColours[D_80126878[i].colourIndex].alpha,
            // gTitleCinematicTextColours[D_80126878[i].colourIndex].opacity);
            j = D_80126878[i].colourIndex; // This seems super fake, but I can't do any better.
            set_text_colour(gTitleCinematicTextColours[j].red, gTitleCinematicTextColours[j].green,
                            gTitleCinematicTextColours[j].blue, gTitleCinematicTextColours[j].alpha,
                            gTitleCinematicTextColours[j].opacity);
            draw_text(&sMenuCurrDisplayList, D_80126878[i].x, D_80126878[i].y, D_80126878[i].text, ALIGN_MIDDLE_CENTER);
            D_80126878[i].colourIndex++;
            if (D_80126878[i].colourIndex >= 4) {
                j = i;
                gTitleCinematicTextColourCount--;
                while (j < gTitleCinematicTextColourCount) {
                    D_80126878[j].text = D_80126878[j + 1].text;
                    D_80126878[j].x = D_80126878[j + 1].x;
                    D_80126878[j].y = D_80126878[j + 1].y;
                    D_80126878[j].colourIndex = D_80126878[j + 1].colourIndex;
                    j++;
                }
            } else {
                i++;
            }
        }
        if (introCharData->unk4 <= D_801268D8) {
            if (D_801268D8 < introCharData->unk8) {
                temp = (D_801268D8 - introCharData->unk4);
                temp2 = (introCharData->unk8 - introCharData->unk4);
                xPos = (introCharData->unk14 + (((introCharData->unk1C - introCharData->unk14) * temp) / temp2));
                yPos = (introCharData->unk18 + (((introCharData->unk20 - introCharData->unk18) * temp) / temp2));
                text = introCharData->unk0;
                didUpdate = TRUE;
            } else if (D_801268D8 <= introCharData->unkC) {
                xPos = introCharData->unk1C;
                yPos = introCharData->unk20;
                text = introCharData->unk0;
                didUpdate = TRUE;
            } else if (D_801268D8 < introCharData->unk10) {
                temp = (D_801268D8 - introCharData->unkC);
                temp2 = (introCharData->unk10 - introCharData->unkC);
                xPos = (introCharData->unk1C + (((introCharData->unk24 - introCharData->unk1C) * temp) / temp2));
                yPos = (introCharData->unk20 + (((introCharData->unk28 - introCharData->unk20) * temp) / temp2));
                text = introCharData->unk0;
                didUpdate = TRUE;
            } else {
                if (!gTitleCinematicTextColours[0].red) {} // Fake
                D_801268E0++;
            }
        }
        if (didUpdate) {
            if (gTitleCinematicTextColourCount < 4) {
                D_80126878[gTitleCinematicTextColourCount].colourIndex = 0;
                D_80126878[gTitleCinematicTextColourCount].text = text;
                D_80126878[gTitleCinematicTextColourCount].x = xPos;
                D_80126878[gTitleCinematicTextColourCount].y = yPos;
                gTitleCinematicTextColourCount++;
            }
            set_text_colour(255, 255, 255, 0, 255);
            draw_text(&sMenuCurrDisplayList, xPos, yPos, text, ALIGN_MIDDLE_CENTER);
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80083098.s")
#endif

/**
 * Initialise the title screen menu.
 * Load the title textures and reset player allocation.
 * Set the current level and demo.
 */
void menu_title_screen_init(void) {
    s32 i;
    s32 numberOfPlayers;

    gTitleScreenLoaded = 1;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    reset_character_id_slots();
    gSaveFileIndex = 0;
    gTitleScreenCurrentOption = 0;
    gNumberOfActivePlayers = 4;
    initialise_player_ids();
    music_play(SEQUENCE_NONE2);
    sMenuMusicVolume = music_volume();
    if (gResetTitleScale) {
        gTitleRevealTimer = 0;
        gResetTitleScale = FALSE;
    } else {
        gTitleRevealTimer = 1;
    }
    gTitleAudioCounter = 0;
    gMenuOptionCount = 0;
    func_8009C674(sGameTitleTileTextures);
    for (i = 0; i < 11; i++) {
        sGameTitleTileOffsets[i].texture = gMenuObjects[sGameTitleTileTextures[i]];
    }
    music_voicelimit_set(27);
    func_800660C0();
    set_text_font(ASSET_FONTS_FUNFONT);
    load_font(ASSET_FONTS_BIGFONT);
    sound_volume_reset(FALSE);
    set_time_trial_enabled(FALSE);
    gTitleDemoIndex = 0;
    sTitleScreenDemoIds = (s8 *) get_misc_asset(ASSET_MISC_TITLE_SCREEN_DEMO_IDS);
    numberOfPlayers = sTitleScreenDemoIds[DEMO_PLAYER_COUNT];
    gTitleDemoTimer = 0;
    if (numberOfPlayers == -2) {
        numberOfPlayers = 0;
        gTitleDemoTimer = 600;
    }
    load_level_for_menu(sTitleScreenDemoIds[DEMO_LEVEL_ID], numberOfPlayers, sTitleScreenDemoIds[DEMO_CUTSCENE_ID]);
    D_801268D8 = 0;
    D_801268E0 = 0;
    D_801268DC = 0;
    gTitleCinematicTextColourCount = 0;
    gOpacityDecayTimer = 0;
    gIsInTracksMode = FALSE;
}

/**
 * Scale and render the game title on the screen based on the reveal timer.
 * Also render the selection options.
 */
void render_title_screen(UNUSED s32 updateRate, f32 updateRateF) {
    UNUSED u32 foo[2];
    s32 alpha;
    f32 scale;
    s32 i;
    s32 posY;

    if (gTitleRevealTimer) {
        set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
        scale = (f32) gTitleRevealTimer * 0.03125f;
        sMenuGuiOpacity = (gTitleRevealTimer * 8) - 1;
        func_80068508(FALSE);
        if (scale != 1.0f) {
            render_texture_rectangle_scaled(&sMenuCurrDisplayList, sGameTitleTileOffsets, SCREEN_WIDTH_FLOAT_HALF,
                                            52.0f, scale, scale, 0xFFFFFFFE, TEXRECT_POINT);
        } else {
            render_textured_rectangle(&sMenuCurrDisplayList, sGameTitleTileOffsets, SCREEN_WIDTH_HALF, 52, 255, 255,
                                      255, 255);
        }
        if (!is_controller_missing()) {
            i = 0;
            posY = (osTvType == TV_TYPE_PAL) ? SCREEN_HEIGHT - 22 : SCREEN_HEIGHT - 48;
            set_text_font(ASSET_FONTS_FUNFONT);
            set_text_background_colour(0, 0, 0, 0);
            while (gTitleMenuStrings[i] != NULL) {
                if (i == gTitleScreenCurrentOption) {
                    alpha = (gOptionBlinkTimer & 0x1F) * 16;
                    if (alpha > 255) {
                        alpha = 511 - alpha;
                    }
                } else {
                    alpha = 0;
                }
                set_text_colour(255, 255, 255, alpha, sMenuGuiOpacity);
                draw_text(&sMenuCurrDisplayList, POS_CENTRED, posY, gTitleMenuStrings[i], ALIGN_MIDDLE_CENTER);
                posY += 16;
                i++;
            }
        }
    } else {
        if (sTitleScreenDemoIds[gTitleDemoIndex] == sTitleScreenDemoIds[0]) {
            func_80083098(updateRateF);
        }
    }
}

/**
 * Handle the countdown when the title screen starts to show the logo coming in.
 * Fade music to make voice clips more audible.
 */
s32 menu_title_screen_loop(s32 updateRate) {
    UNUSED s32 temp_v0_5;
    s32 sp28;
    s8 *demo;
    s32 contrIndex;
    f32 updateRateF;
    ObjectSegment *sp18;
    s8 playerCount;

    sp18 = get_active_camera_segment();
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    func_8008E4EC();
    if (osTvType == TV_TYPE_PAL) {
        updateRateF = (f32) updateRate / 50.0f;
    } else {
        updateRateF = (f32) updateRate / 60.0f;
    }
    if (gMenuDelay < 20) {
        render_title_screen(updateRate, updateRateF);
    }
    if (gMenuDelay) {
        gMenuDelay += updateRate;
    }
    if (sTitleScreenDemoIds[gTitleDemoIndex] == sTitleScreenDemoIds[0]) {
        gOpacityDecayTimer += updateRate;
    }
    sp28 = 0;
    if (gTitleDemoTimer > 0) {
        gTitleDemoTimer -= updateRate;
        if (gTitleDemoTimer < 60 && gTitleDemoTimer + updateRate >= 60) {
            music_fade(-768);
            sp28 = 0;
            transition_begin(&gFadeTitleScreenDemo);
        }
        if (gTitleDemoTimer <= 0) {
            sp28 = 1;
        }
    } else {
        gTitleDemoTimer = 0;
    }
    if (gMenuDelay == 0 && (func_800214C4() || sp28)) {
        if (gTitleDemoTimer) {} // Fakematch
        gTitleDemoIndex += DEMO_INDEX_SIZE;
        demo = &sTitleScreenDemoIds[gTitleDemoIndex];
        if (demo[0] == -1) {
            gTitleDemoIndex = 0;
            demo = &sTitleScreenDemoIds[gTitleDemoIndex];
        }
        if (gTitleRevealTimer == 0) {
            gTitleRevealTimer = 1;
        }
        playerCount = demo[DEMO_PLAYER_COUNT];
        gTitleDemoTimer = 0;
        if (playerCount == -2) {
            playerCount = 0;
            gTitleDemoTimer = 1500;
        }
        load_level_for_menu(demo[DEMO_LEVEL_ID], playerCount, demo[DEMO_CUTSCENE_ID]);
        if (sTitleScreenDemoIds[gTitleDemoIndex] == sTitleScreenDemoIds[DEMO_LEVEL_ID]) {
            D_801268D8 = 0.0f;
            D_801268E0 = 0;
            D_801268DC = 0;
            gTitleCinematicTextColourCount = 0;
            gOpacityDecayTimer = 0;
        }
    }
    if (gTitleRevealTimer) {
        if (gTitleRevealTimer < 32) {
            if (gTitleRevealTimer == 1) {
                sound_play(SOUND_WHOOSH1, 0);
            }
            gTitleRevealTimer += updateRate;
            if (gTitleRevealTimer >= 32) {
                gTitleRevealTimer = 32;
                sp18->object.distanceToCamera = 8.0f;
                sound_play(SOUND_EXPLOSION, 0);
            }
        } else {
            if (gTitleAudioCounter < 6.0f) {
                gTitleAudioCounter += updateRateF;
                if (gTitleAudioCounter > 0.67f && gMenuOptionCount == 0) {
                    sound_play(SOUND_VOICE_TT_DIDDY_KONG_RACING, 0);
                    gMenuOptionCount = 1;
                } else if ((gTitleAudioCounter > 2.83f) && (gMenuOptionCount == 1)) {
                    sound_play(SOUND_VOICE_TT_PRESS_START, 0);
                    gMenuOptionCount = 2;
                }
            }
        }
    }
    if (gTitleAudioCounter > 0.0f) {
        if (gTitleAudioCounter < 0.5f) {
            music_volume_set((s32) ((f32) sMenuMusicVolume * (1.0f - gTitleAudioCounter)));
        } else if (gTitleAudioCounter < 4.5f) {
            music_volume_set(((s32) sMenuMusicVolume >> 1));
        } else if (gTitleAudioCounter < 5.0f) {
            music_volume_set((s32) ((f32) sMenuMusicVolume * (gTitleAudioCounter - 4.0f)));
        } else {
            music_volume_set(*((s8 *) &sMenuMusicVolume + 3));
        }
    }
    if (gTitleRevealTimer == 0) {
        if (D_801267D8[4] & (A_BUTTON | START_BUTTON)) {
            gTitleRevealTimer = 1;
        }
    } else if ((gMenuDelay == 0) && !is_controller_missing()) {
        s32 temp0 = gTitleScreenCurrentOption;
        // D_80126830[4] = +1 when going up, and -1 when going down.
        if ((D_80126830[4] < 0) && (gTitleScreenCurrentOption < 1)) {
            gTitleScreenCurrentOption++;
        }
        if ((D_80126830[4] > 0) && (gTitleScreenCurrentOption > 0)) {
            gTitleScreenCurrentOption--;
        }
        if (temp0 != gTitleScreenCurrentOption) {
            sound_play(SOUND_MENU_PICK2, (s32 *) (0 * contrIndex)); // TODO: The `* contrIndex` here is a fake match.
        }
        if (D_801267D8[4] & (A_BUTTON | START_BUTTON)) {
            for (contrIndex = 3; contrIndex > 0 && !(D_801267D8[contrIndex] & (A_BUTTON | START_BUTTON));
                 contrIndex--) {}
            set_active_player_index(contrIndex);
            gMenuDelay = 1;
            transition_begin(&sMenuTransitionFadeIn);
            enable_new_screen_transitions();
            sound_play(SOUND_SELECT2, 0);
        }
    }
    if (gMenuDelay > 30) {
        title_screen_exit();
        disable_new_screen_transitions();
        if (gTitleScreenCurrentOption == 0) {
            sp28 = 0;
            if (is_drumstick_unlocked()) {
                sp28 = 1;
            }
            if (is_tt_unlocked()) {
                sp28 ^= 3;
            }
            load_level_for_menu(ASSET_LEVEL_CHARACTERSELECT, -1, sp28);
            func_8008AEB4(0, NULL);
            menu_init(MENU_CHARACTER_SELECT);
            return MENU_RESULT_CONTINUE;
        }
        gMenuCurIndex = 0;
        load_level_for_menu(ASSET_LEVEL_OPTIONSBACKGROUND, -1, 0);
        menu_init(MENU_OPTIONS);
        return MENU_RESULT_CONTINUE;
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}

/**
 * Unloads the title screen logo and sets all audio back to default.
 */
void title_screen_exit(void) {
    func_8009C4A8(sGameTitleTileTextures);
    music_voicelimit_set(16);
    func_800660D0();
    unload_font(ASSET_FONTS_BIGFONT);
    sound_volume_reset(TRUE);
}

/**
 * Initialise the root options menu.
 * Loads required fonts and sets the background music.
 */
void menu_options_init(void) {
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    transition_begin(&sMenuTransitionFadeOut);
    load_font(ASSET_FONTS_BIGFONT);
    set_text_font(ASSET_FONTS_BIGFONT);
    music_voicelimit_set(24);
    music_play(SEQUENCE_MAIN_MENU);
    music_change_off();
}

// Draws options menu screen
void render_options_menu_ui(UNUSED s32 updateRate) {
    s32 optionMenuTextIndex;
    s32 alpha;
    s32 yPos;

    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_background_colour(0, 0, 0, 0);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, gMenuText[ASSET_MENU_TEXT_OPTIONS],
              ALIGN_MIDDLE_CENTER); // OPTIONS
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, gMenuText[ASSET_MENU_TEXT_OPTIONS],
              ALIGN_MIDDLE_CENTER); // OPTIONS

    optionMenuTextIndex = 0;
    yPos = 76;

    set_text_font(ASSET_FONTS_FUNFONT);

    while (gOptionMenuStrings[optionMenuTextIndex] != NULL) {
        if (optionMenuTextIndex == gMenuCurIndex) {
            alpha = gOptionBlinkTimer * 8;
            if (gOptionBlinkTimer >= 32) {
                alpha = 511 - alpha;
            }
        } else {
            alpha = 0;
        }
        set_text_colour(255, 255, 255, alpha, 255);
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, yPos, gOptionMenuStrings[optionMenuTextIndex],
                  ALIGN_MIDDLE_CENTER);

        optionMenuTextIndex++;
        yPos += 28;
    }
}

/**
 * Draw the text list and accept input for going to specific option menus.
 */
s32 menu_options_loop(s32 updateRate) {
    s32 buttonsPressed;
    s32 i;
    UNUSED s32 pad0;
    s32 analogueX;
    s32 analogueY;
    UNUSED s32 pad1[4];

    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }

    if (gMenuDelay > -20 && gMenuDelay < 35) {
        render_options_menu_ui(updateRate);
    }
    buttonsPressed = 0;
    analogueX = 0;
    analogueY = 0;
    if (gIgnorePlayerInputTime == 0 && gMenuDelay == 0) {
        s8 *xAxisPtr;
        s8 *yAxisPtr;
        for (i = 0, xAxisPtr = gControllersXAxisDirection, yAxisPtr = gControllersYAxisDirection; i < MAXCONTROLLERS;
             i++) {
            buttonsPressed |= get_buttons_pressed_from_player(i);
            analogueX += *(xAxisPtr++);
            analogueY += *(yAxisPtr++);
        }
    }
    if ((buttonsPressed & B_BUTTON) || ((buttonsPressed & (A_BUTTON | START_BUTTON)) && gMenuCurIndex == 5)) {
        // Leave the option menu
        music_fade(-128);
        gMenuDelay = -1;
        transition_begin(&sMenuTransitionFadeIn);
        sound_play(SOUND_MENU_BACK3, NULL);
    } else if ((buttonsPressed & (A_BUTTON | START_BUTTON)) && gMenuCurIndex >= 2) {
        // Go to a sub-menu
        gMenuDelay = 31;
        sound_play(SOUND_SELECT2, NULL);

    } else if (gMenuCurIndex == 0 && analogueX != 0) {
        switch ((u64) get_language()) {
            case LANGUAGE_ENGLISH:
                set_language(LANGUAGE_FRENCH);
                break;
            default:
                set_language(LANGUAGE_ENGLISH);
                break;
        }
        sound_play(SOUND_MENU_PICK2, NULL);
    } else if (gMenuCurIndex == 1 && analogueX != 0) {
        if (sEepromSettings & 0x2000000) {
            // 0x2000000 SUBTITLES ENABLED?
            sound_play(SOUND_MENU_PICK2, NULL);
            unset_eeprom_settings_value(0x2000000);
            set_subtitles(0);
            gOptionMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_SUBTITLESOFF];
        } else {
            sound_play(SOUND_MENU_PICK2, NULL);
            set_eeprom_settings_value(0x2000000);
            set_subtitles(1);
            gOptionMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_SUBTITLESON];
        }
    } else {
        s32 prev_D_800DF460 = gMenuCurIndex;
        if (analogueY < 0) {
            gMenuCurIndex++;
            if (gMenuCurIndex >= 6) {
                gMenuCurIndex = 5;
            }
        }
        if (analogueY > 0) {
            gMenuCurIndex--;
            if (gMenuCurIndex < 0) {
                gMenuCurIndex = 0;
            }
        }
        if (prev_D_800DF460 != gMenuCurIndex) {
            sound_play(SOUND_MENU_PICK2, NULL);
        }
    }
    if (gMenuDelay > 30) {
        // Change screen to a sub-menu
        if (gMenuCurIndex == 2) {
            unload_big_font_1();
            menu_init(MENU_AUDIO_OPTIONS);
            return MENU_RESULT_CONTINUE;
        }
        if (gMenuCurIndex == 3) {
            unload_big_font_1();
            menu_init(MENU_SAVE_OPTIONS);
            return MENU_RESULT_CONTINUE;
        }
        unload_big_font_1();
        menu_init(MENU_MAGIC_CODES);
        return MENU_RESULT_CONTINUE;
    }
    if (gMenuDelay < -30) {
        // Change screen back to the title screen.
        music_change_on();
        unload_big_font_1();
        menu_init(MENU_TITLE);
        return MENU_RESULT_CONTINUE;
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}

/**
 * Explicitly says to unload the ASSET_FONTS_BIGFONT type.
 */
void unload_big_font_1(void) {
    unload_font(ASSET_FONTS_BIGFONT);
}

/**
 * Initialise the audio options menu.
 * Loads necessary textures and fonts.
 * Gets global audio volume and checks if the jukebox cheat is active to set the lower Y bounds.
 */
void menu_audio_options_init(void) {
    gOptionsMenuItemIndex = 0;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    D_801269FC = NULL;
    gOpacityDecayTimer = -1;
    func_8009C674(gOptionMenuTextures);
    allocate_menu_images(&gOptionMenuTextures[6]);
    assign_menu_arrow_textures();
    transition_begin(&sMenuTransitionFadeOut);
    func_8007FFEC(2);
    gMusicVolumeSliderValue = music_volume_config();
    gSfxVolumeSliderValue = get_sfx_volume_slider();
    if (gActiveMagicCodes & CHEAT_MUSIC_MENU) { // Check if "JUKEBOX" cheat is active
        gAudioMenuStrings[6].unkC = gMusicTestString;
        gAudioMenuStrings[3].unk2 = 212;
        music_voicelimit_set(32);
        gMenuOptionCount = 5;
    } else {
        gAudioMenuStrings[6].unkC = NULL;
        gAudioMenuStrings[3].unk2 = 192;
        gMenuOptionCount = 4;
    }
    load_font(ASSET_FONTS_BIGFONT);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80084854.s")

s32 menu_audio_options_loop(s32 updateRate) {
    s32 i;
    u32 buttonsPressed;
    s32 contX;
    s32 contY;
    s32 contXAxis;
    s32 sp30;

    sp30 = 0;
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }
    if (gMenuDelay > -20 && gMenuDelay < 20) {
        func_80084854();
    }
    if (gIgnorePlayerInputTime == 0) {
        contX = 0;
        contY = 0;
        if (gMenuDelay == 0) {
            buttonsPressed = 0;
            contXAxis = 0;
            for (i = 0; i < 4; i++) {
                buttonsPressed |= get_buttons_pressed_from_player(i);
                contXAxis += clamp_joystick_x_axis(i);
                contX += gControllersXAxisDirection[i];
                contY += gControllersYAxisDirection[i];
            }
            if (contXAxis < 0) {
                contXAxis += 24;
                if (contXAxis > 0) {
                    contXAxis = 0;
                }
            } else {
                contXAxis -= 24;
                if (contXAxis < 0) {
                    contXAxis = 0;
                }
            }
            contXAxis >>= 2;
            if (((buttonsPressed & (A_BUTTON | START_BUTTON)) && (gMenuOptionCount == gOptionsMenuItemIndex + 1)) ||
                (buttonsPressed & B_BUTTON)) {
                gMenuDelay = -1;
                transition_begin(&sMenuTransitionFadeIn);
                if (gOpacityDecayTimer >= 0) {
                    music_fade(-128);
                }
                sp30 = 3;
            } else if (contY < 0 && gOptionsMenuItemIndex < (gMenuOptionCount - 1)) {
                gOptionsMenuItemIndex++;
                sp30 = 1;
            } else if (contY > 0 && gOptionsMenuItemIndex > 0) {
                gOptionsMenuItemIndex--;
                sp30 = 1;
            } else if (gOptionsMenuItemIndex == 0 && contX != 0) {
                if (contX < 0) {
                    gAudioOutputType--;
                } else {
                    gAudioOutputType++;
                }
                if (gAudioOutputType < 0) {
                    gAudioOutputType = HEADPHONES;
                }
                if (gAudioOutputType >= 3) {
                    gAudioOutputType = STEREO;
                }
                set_stereo_pan_mode(gAudioOutputType);
                sp30 = 1;
            } else if (contXAxis && (gOptionsMenuItemIndex == 1 || gOptionsMenuItemIndex == 2)) {
                if (gOptionsMenuItemIndex == 1) {
                    gSfxVolumeSliderValue += contXAxis;
                    if (gSfxVolumeSliderValue < 0) {
                        gSfxVolumeSliderValue = 0;
                    } else if (gSfxVolumeSliderValue > 256) {
                        gSfxVolumeSliderValue = 256;
                    }
                    set_sfx_volume_slider(gSfxVolumeSliderValue);
                } else if (gOptionsMenuItemIndex == 2) {
                    gMusicVolumeSliderValue += contXAxis;
                    if (gMusicVolumeSliderValue < 0) {
                        gMusicVolumeSliderValue = 0;
                    } else if (gMusicVolumeSliderValue > 256) {
                        gMusicVolumeSliderValue = 256;
                    }
                    music_volume_config_set(gMusicVolumeSliderValue);
                    if (!music_is_playing()) {
                        if (gOpacityDecayTimer >= 0) {
                            music_change_on();
                            music_play(gMusicTestSongIndex);
                        } else {
                            music_change_on();
                            music_voicelimit_set(24);
                            music_play(SEQUENCE_MAIN_MENU);
                            music_change_off();
                        }
                    }
                }
            } else if (gMenuOptionCount >= 5 && gOptionsMenuItemIndex == 3) {
                if (contX < 0 && gMusicTestSongIndex > 0) {
                    gMusicTestSongIndex--;
                    sp30 = 1;
                } else if (contX > 0) {
                    if (gMusicTestSongIndex < (music_sequence_count() - 1)) {
                        gMusicTestSongIndex++;
                        sp30 = 1;
                    }
                }
                if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                    music_change_on();
                    music_voicelimit_set(24);
                    music_play(gMusicTestSongIndex);
                    gOpacityDecayTimer = gMusicTestSongIndex;
                }
            }
            if (gOptionsMenuItemIndex == 1) {
                if (D_801269FC == NULL) {
                    sound_play(SOUND_VOICE_DIDDY_POSITIVE5, (s32 *) &D_801269FC);
                }
            } else if (D_801269FC != NULL) {
                func_8000488C((u8 *) D_801269FC);
            }
            if (sp30 == 3) {
                sound_play(SOUND_MENU_BACK3, NULL);
            } else if (sp30 == 2) {
                sound_play(SOUND_SELECT2, NULL);
            } else if (sp30 == 1) {
                sound_play(SOUND_MENU_PICK2, NULL);
            }
        }
    }
    if (gMenuDelay < -30) {
        func_800851FC();
        menu_init(MENU_OPTIONS);
        return 0;
    }
    gIgnorePlayerInputTime = 0;
    return 0;
}

void func_800851FC(void) {
    if (D_801269FC != NULL) {
        func_8000488C(D_801269FC);
    }
    if (gOpacityDecayTimer >= 0) {
        music_voicelimit_set(24);
        music_play(SEQUENCE_MAIN_MENU);
        music_fade(0x100);
        music_change_off();
    }
    func_8009C4A8(gOptionMenuTextures);
    unload_font(ASSET_FONTS_BIGFONT);
}

void menu_save_options_init(void) {
    D_80126A6C = 1;
    D_80126A10 = 0;
    D_80126A18 = 1;
    D_80126A1C = 1;
    gOptionsMenuItemIndex = 0;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    gMenuOptionCount = 1;
    gOpacityDecayTimer = 0;
    D_80126A64 = (char *) allocate_from_main_pool_safe(0x800, COLOUR_TAG_WHITE);
    D_80126A0C = (SaveFileData *) allocate_from_main_pool_safe(0xA00, COLOUR_TAG_WHITE);
    D_80126A04 = &D_80126A0C[80];
    D_80126A08 = 0;
    D_80126BD4 = 0;
    D_80126BDC = 0.0f;
    D_80126A00 = 0;
    D_80126BE4 = 0;
    D_80126BEC = 0.0f;
    func_8009C674(gSaveMenuObjectIndices);
    allocate_menu_images(gSaveMenuImageIndices);
    func_8007FFEC(0xA);
    load_font(ASSET_FONTS_BIGFONT);
    gDrawTexN64Icon[0].texture = gMenuObjects[TEXTURE_ICON_SAVE_N64];
    gDrawTexTTIcon[0].texture = gMenuObjects[TEXTURE_ICON_SAVE_TT];
    gDrawTexGhostIcon[0].texture = gMenuObjects[TEXTURE_ICON_SAVE_GHOSTS];
    gDrawTexFileIcon[0].texture = gMenuObjects[TEXTURE_ICON_SAVE_FILECABINET];
    gDrawTexContPakIcon[0].texture = gMenuObjects[TEXTURE_ICON_SAVE_CPAK];
    gDrawTexTrashIcon[0].texture = gMenuObjects[TEXTURE_ICON_SAVE_BIN];
    assign_menu_arrow_textures();
    mark_read_all_save_files();
    transition_begin(&sMenuTransitionFadeOut);
}

void func_800853D0(SaveFileData *arg0, s32 x, s32 y) {
    s32 i;
    s32 sp78;
    s32 sp74;
    s32 sp70;
    s32 colour;
    DrawTexture *drawTexture;
    char *text2;
    char *text;
    char buffer[16];
    TextureHeader *texture;
    s32 temp;

    sp70 = 11;
    switch (arg0->saveFileType) {
        case SAVE_FILE_TYPE_UNK1:
            drawTexture = gDrawTexN64Icon;
            texture = gMenuObjects[TEXTURE_SURFACE_BUTTON_WOOD];
            colour = COLOUR_RGBA32(176, 224, 192, 255);
            if (!gSavefileData[arg0->controllerIndex]->newGame) {
                decompress_filename_string(gSavefileData[arg0->controllerIndex]->filename, buffer, 3);
                trim_filename_string(buffer, buffer);
                text2 = buffer;
                sp78 = *gSavefileData[arg0->controllerIndex]->balloonsPtr / 10;
                sp74 = *gSavefileData[arg0->controllerIndex]->balloonsPtr - (sp78 * 10);
                // Is Adventure Two?
                if (gSavefileData[arg0->controllerIndex]->cutsceneFlags & 4) {
                    sp70 = 12;
                }
            } else {
                text2 = gFilenames[arg0->controllerIndex];
            }
            text = gMenuText[ASSET_MENU_TEXT_GAMEPAK];
            break;
        case SAVE_FILE_TYPE_UNK2:
            drawTexture = gDrawTexTTIcon;
            texture = gMenuObjects[TEXTURE_SURFACE_BUTTON_WOOD];
            colour = COLOUR_RGBA32(176, 224, 192, 255);
            text2 = gMenuText[ASSET_MENU_TEXT_TIMES];
            text = gMenuText[ASSET_MENU_TEXT_GAMEPAK];
            break;
        case SAVE_FILE_TYPE_GAME_DATA:
            drawTexture = gDrawTexN64Icon;
            texture = gMenuObjects[TEXTURE_UNK_44];
            colour = gContPakSaveBgColours[arg0->controllerIndex];
            text2 = buffer;
            decompress_filename_string(arg0->compressedFilename, buffer, 3);
            // char *gConPakAdvSavePrefix = " (ADV.";
            for (i = 0; gConPakAdvSavePrefix[i] != '\0'; i++) {
                buffer[i + 3] = gConPakAdvSavePrefix[i];
            }
            buffer[i + 3] = arg0->saveFileExt[0];
            buffer[i + 4] = ')';
            buffer[i + 5] = '\0';
            text = gMenuText[86 + arg0->controllerIndex];
            sp78 = arg0->unk2 / 10;
            sp74 = arg0->unk2 % 10;
            if (arg0->unk3 != 0) {
                sp70 = 12;
            }
            break;
        case SAVE_FILE_TYPE_TIME_DATA:
            drawTexture = gDrawTexTTIcon;
            texture = gMenuObjects[TEXTURE_UNK_44];
            colour = gContPakSaveBgColours[arg0->controllerIndex];
            text2 = arg0->saveFileExt;
            text = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + arg0->controllerIndex];
            break;
        case SAVE_FILE_TYPE_GHOST_DATA:
            drawTexture = gDrawTexGhostIcon;
            texture = gMenuObjects[TEXTURE_UNK_44];
            colour = gContPakSaveBgColours[arg0->controllerIndex];
            text2 = gMenuText[ASSET_MENU_TEXT_GHOSTS];
            text = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + arg0->controllerIndex];
            break;
        case SAVE_FILE_TYPE_UNKNOWN:
            drawTexture = gDrawTexFileIcon;
            texture = gMenuObjects[TEXTURE_UNK_44];
            colour = gContPakSaveBgColours[arg0->controllerIndex];
            text2 = arg0->saveFileExt;
            text = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + arg0->controllerIndex];
            break;
        case SAVE_FILE_TYPE_UNK8:
            drawTexture = gDrawTexContPakIcon;
            texture = gMenuObjects[TEXTURE_UNK_44];
            colour = gContPakSaveBgColours[arg0->controllerIndex];
            text2 = gMenuText[ASSET_MENU_TEXT_EMPTYSLOT];
            text = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + arg0->controllerIndex];
            break;
        case SAVE_FILE_TYPE_UNK9:
            drawTexture = gDrawTexGhostIcon;
            texture = gMenuObjects[TEXTURE_UNK_45];
            colour = -1;
            text2 = gMenuText[ASSET_MENU_TEXT_VIEWGHOSTS];
            text = NULL;
            break;
        case SAVE_FILE_TYPE_UNKA:
            drawTexture = gDrawTexN64Icon;
            text2 = gMenuText[ASSET_MENU_TEXT_GAMEPAKBONUSES];
            texture = gMenuObjects[TEXTURE_SURFACE_BUTTON_WOOD];
            colour = COLOUR_RGBA32(176, 224, 192, 255);
            text = gMenuText[ASSET_MENU_TEXT_GAMEPAK];
            break;
        default:
            drawTexture = gDrawTexTrashIcon;
            texture = gMenuObjects[TEXTURE_UNK_45];
            colour = COLOUR_RGBA32(128, 128, 128, 255);
            text2 = gMenuText[ASSET_MENU_TEXT_ERASE];
            text = NULL;
            break;
    }
    func_80080580(&sMenuCurrDisplayList, x - 160, 120 - y, 160, 64, 4, 4, colour, texture);
    if (osTvType == TV_TYPE_PAL) {
        y += 12;
    }
    if (arg0->saveFileType == SAVE_FILE_TYPE_GAME_DATA ||
        (arg0->saveFileType == SAVE_FILE_TYPE_UNK1 && gSavefileData[arg0->controllerIndex]->newGame == FALSE)) {
        if (osTvType == TV_TYPE_PAL) {
            i = 134;
        } else {
            i = 120;
        }
        func_80068508(TRUE);
        temp = (i - y);
        gMenuImageStack[2].unk10 = temp - 49;
        gMenuImageStack[sp70].unk10 = temp - 24;
        sprite_opaque(0);
        gMenuImageStack[2].unkC = x - 133;
        gMenuImageStack[2].unk18 = sp78;
        func_8009CA60(2);
        gMenuImageStack[2].unkC = x - 125;
        gMenuImageStack[2].unk18 = sp74;
        func_8009CA60(2);
        sprite_opaque(1);
        gMenuImageStack[sp70].unkC = x - 128;
        func_8009CA60(sp70);
        func_80068508(FALSE);
    }
    if (drawTexture != NULL) {
        render_textured_rectangle(&sMenuCurrDisplayList, drawTexture, x + 60, y + 6, 255, 255, 255, 255);
    }
    if (text != NULL) {
        set_text_font(0);
        set_text_colour(0, 0, 0, 255, 128);
        draw_text(&sMenuCurrDisplayList, x + 81, y + 1, text, ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 64, 255, 64, 255);
        draw_text(&sMenuCurrDisplayList, x + 79, y - 1, text, ALIGN_MIDDLE_CENTER);
    }
    if (text2 != NULL) {
        set_text_font(1);
        set_text_colour(0, 0, 0, 255, 160);
        draw_text(&sMenuCurrDisplayList, x + 80, y + 48, text2, ALIGN_TOP_CENTER);
        set_text_colour(255, 255, 255, 255, 255);
        draw_text(&sMenuCurrDisplayList, x + 79, y + 47, text2, ALIGN_TOP_CENTER);
    }
}

void func_80085B9C(UNUSED s32 updateRate) {
    s32 videoWidth;
    s32 temp;
    s32 sp5C;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 drawTexturedRectangle;
    s32 drawPleaseWait;
    s32 drawOk;
    s32 drawDialogueBox;

    videoWidth = GET_VIDEO_WIDTH(get_video_width_and_height_as_s32());
    var_s3 = FALSE;
    drawTexturedRectangle = FALSE;
    drawPleaseWait = FALSE;
    drawOk = FALSE;
    drawDialogueBox = FALSE;
    switch (gMenuOptionCount & 7) {
        case 0:
            break;
        case 1:
        case 2:
            drawPleaseWait = TRUE;
            break;
        case 3:
        case 4:
            var_s3 = TRUE;
            break;
        case 5:
            var_s3 = TRUE;
            drawTexturedRectangle = TRUE;
            break;
        case 6:
            var_s3 = TRUE;
            drawTexturedRectangle = TRUE;
            drawOk = TRUE;
            break;
        case 7:
            var_s3 = TRUE;
            drawTexturedRectangle = TRUE;
            drawPleaseWait = TRUE;
            break;
    }
    if (gMenuOptionCount & 8) {
        drawDialogueBox = TRUE;
    }
    set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    set_text_background_colour(0, 0, 0, 0);
    set_text_font(2);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, gMenuText[ASSET_MENU_TEXT_SAVEOPTIONS],
              ALIGN_MIDDLE_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, gMenuText[ASSET_MENU_TEXT_SAVEOPTIONS],
              ALIGN_MIDDLE_CENTER);

    if (drawTexturedRectangle) {
        temp = (osTvType == TV_TYPE_PAL) ? SCREEN_HEIGHT_HALF_PAL : SCREEN_HEIGHT_HALF;
        temp += ((s32) (gOptionBlinkTimer & 0x1F) >> 1);

        for (var_s2 = 0; var_s2 < 2; var_s2 += 1, temp += 16) {
            render_textured_rectangle(&sMenuCurrDisplayList, gMenuSelectionArrowDown, SCREEN_WIDTH_HALF, temp, 255, 255,
                                      255, 255);
        }
    }

    if (var_s3) {
        var_s2 = (s32) D_80126BDC;
        temp = var_s2;
        sp5C = 80 - (s32) ((D_80126BDC - var_s2) * 164.0f);
        var_s1 = sp5C;
        while (var_s1 < videoWidth && temp < D_80126A08) {
            func_800853D0(&D_80126A0C[temp], var_s1, 64);
            var_s1 += 164;
            temp++;
        }
        temp = var_s2;
        var_s1 = sp5C;
        while ((var_s1 > 0) && (temp > 0)) {
            temp--;
            var_s1 -= 164;
            func_800853D0(&D_80126A0C[temp], var_s1, 64);
        }
    }

    if (drawTexturedRectangle) {
        var_s2 = (s32) D_80126BEC;
        temp = var_s2;
        sp5C = 80 - (s32) ((D_80126BEC - (f32) var_s2) * 164.0f);
        var_s1 = sp5C;
        while (var_s1 < videoWidth && temp < D_80126A00) {
            func_800853D0(&D_80126A04[temp], var_s1, 144);
            var_s1 += 164;
            temp++;
        }
        temp = var_s2;
        var_s1 = sp5C;
        while (var_s1 > 0 && temp > 0) {
            temp--;
            var_s1 -= 164;
            func_800853D0(&D_80126A04[temp], var_s1, 144);
        }
    }

    set_text_font(2);
    set_text_colour(255, 255, 255, 0, 255);
    if (drawOk) {
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 128, (char *) D_800E8208, ALIGN_MIDDLE_CENTER); // "OK?"
    }
    if (drawPleaseWait) {
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 128, gMenuText[ASSET_MENU_TEXT_PLEASEWAIT],
                  ALIGN_MIDDLE_CENTER);
    }
    if (drawDialogueBox) {
        render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 7);
    }
    func_80080E6C();
}

SIDeviceStatus func_800860A8(s32 controllerIndex, s32 *arg1, SaveFileData *arg2, s32 *arg3, s32 fileSize,
                             UNUSED s32 arg5) {
    SIDeviceStatus ret = CONTROLLER_PAK_GOOD;

    if (*arg1 != 0) {
        ret = get_free_space(controllerIndex, &arg2[*arg3].fileSize, &sControllerPakNotesFree[controllerIndex]);
        if (ret == CONTROLLER_PAK_GOOD) {
            if (((s32) arg2[*arg3].fileSize >= fileSize) && (sControllerPakNotesFree[controllerIndex] > 0)) {
                arg2[*arg3].saveFileType = SAVE_FILE_TYPE_UNK8;
                arg2[*arg3].controllerIndex = controllerIndex;
                (*arg3)++;
            }
        } else {
            SIDeviceStatus status = ret & 0xFF; // The upper bytes could be controllerIndex, so focus on the status
            if ((*arg1 < 0) && status == CONTROLLER_PAK_RUMBLE_PAK_FOUND) {
                *arg1 = 0;
                ret = CONTROLLER_PAK_GOOD;
            } else if (status != CONTROLLER_PAK_WITH_BAD_ID && status != CONTROLLER_PAK_INCONSISTENT &&
                       status != CONTROLLER_PAK_BAD_DATA) {
                ret = CONTROLLER_PAK_GOOD;
            }
        }
    }

    return ret;
}

void func_800861C8(SaveFileData *arg0, s32 *arg1) {
    s32 i;
    for (i = 0; i < NUMBER_OF_SAVE_FILES; i++) {
        if (gSavefileData[i]->newGame) {
            arg0[*arg1].saveFileType = SAVE_FILE_TYPE_UNK1;
            arg0[*arg1].unk1 = 0;
            arg0[*arg1].unk2 = 0;
            arg0[*arg1].controllerIndex = i;
            arg0[*arg1].fileSize = get_game_data_file_size();
            (*arg1)++;
        }
    }
}

SIDeviceStatus func_800862C4(void) {
    s32 numAttempts;
    s32 i;
    s32 fileIndex;
    SIDeviceStatus result;
    SIDeviceStatus temp;
    char *fileNames[16];
    char *fileExts[16];
    u8 fileTypes[16];
    Settings *settings;
    u32 fileSizes[16];
    char *temp_D_80126A64;

    settings = gSavefileData[3];
    D_80126A08 = 0;
    D_80126BD4 = 0;
    D_80126BDC = 0.0f;
    for (i = 0; i < NUMBER_OF_SAVE_FILES; i++) {
        if (!gSavefileData[i]->newGame) {
            D_80126A0C[D_80126A08].saveFileType = SAVE_FILE_TYPE_UNK1;
            D_80126A0C[D_80126A08].unk1 = 1;
            D_80126A0C[D_80126A08].unk2 = gSavefileData[i]->balloonsPtr[0];
            D_80126A0C[D_80126A08].controllerIndex = i;
            D_80126A0C[D_80126A08].fileSize = get_game_data_file_size();
            D_80126A08++;
        }
    }

    D_80126A0C[D_80126A08].saveFileType = SAVE_FILE_TYPE_UNK2;
    D_80126A0C[D_80126A08].unk1 = 1;
    D_80126A0C[D_80126A08++].fileSize = get_time_data_file_size();
    D_80126A0C[D_80126A08++].saveFileType = SAVE_FILE_TYPE_UNKA;
    temp_D_80126A64 = D_80126A64;
    do {
        numAttempts = 1;
        if (D_80126A18 != 0) {
            D_80126A14 = 0;

            do {
                result = get_controller_pak_file_list(0, 16, fileNames, fileExts, fileSizes, fileTypes);
                temp = result & 0xFF; // strip the controller index from the result to just get the SI Device Status
                numAttempts++;
            } while ((temp == CONTROLLER_PAK_CHANGED) && (numAttempts < 3));

            if (result == CONTROLLER_PAK_GOOD) {
                for (fileIndex = 0; fileIndex < 16; fileIndex++) {
                    if ((fileTypes[fileIndex] >= SAVE_FILE_TYPE_GAME_DATA) &&
                        (fileTypes[fileIndex] <= SAVE_FILE_TYPE_UNKNOWN)) {
                        (*sControllerPakNotesFree)--;
                        D_80126A0C[D_80126A08].saveFileType = fileTypes[fileIndex];
                        D_80126A0C[D_80126A08].controllerIndex = 0;
                        D_80126A0C[D_80126A08].saveFileNumber = fileIndex;
                        D_80126A0C[D_80126A08].fileSize = fileSizes[fileIndex];
                        if (fileTypes[fileIndex] == SAVE_FILE_TYPE_GAME_DATA) {
                            if (read_game_data_from_controller_pak(0, fileExts[fileIndex], settings) ==
                                CONTROLLER_PAK_GOOD) {
                                D_80126A0C[D_80126A08].saveFileExt = temp_D_80126A64;
                                temp_D_80126A64[0] = *fileExts[fileIndex];
                                temp_D_80126A64[1] = 0;
                                temp_D_80126A64 += 2;
                                D_80126A0C[D_80126A08].unk2 = *settings->balloonsPtr;
                                D_80126A0C[D_80126A08].unk3 =
                                    (settings->cutsceneFlags & 4) != 0; // Is in Adventure Two?
                                D_80126A0C[D_80126A08].compressedFilename = settings->filename;
                            } else {
                                D_80126A08--;
                            }
                        } else {
                            temp = 0;
                            if ((fileTypes[fileIndex] == SAVE_FILE_TYPE_UNKNOWN) ||
                                (fileTypes[fileIndex] == SAVE_FILE_TYPE_TIME_DATA)) {
                                if (fileTypes[fileIndex] == SAVE_FILE_TYPE_TIME_DATA) {
                                    temp = CONTROLLER_PAK_BAD_DATA;
                                }
                                D_80126A0C[D_80126A08].saveFileExt = temp_D_80126A64;
                                while (fileNames[fileIndex][temp] != '\0') {
                                    *temp_D_80126A64 = fileNames[fileIndex][temp];
                                    temp++;
                                    temp_D_80126A64++;
                                }

                                if ((fileExts[fileIndex] != NULL) && (fileExts[fileIndex][0] != '\0')) {
                                    *temp_D_80126A64 = '.';
                                    temp_D_80126A64++;
                                    temp = 0;
                                    while (fileExts[fileIndex][temp] != '\0') {
                                        *temp_D_80126A64 = fileExts[fileIndex][temp];
                                        temp_D_80126A64++;
                                        temp++;
                                    }
                                }
                                *temp_D_80126A64 = 0;
                                temp_D_80126A64++;
                            }
                        }
                        D_80126A08++;
                    }
                }
                packDirectoryFree();
            } else if (temp == CONTROLLER_PAK_RUMBLE_PAK_FOUND) {
                D_80126A14 = 1;
                if (D_80126A18 < 0) {
                    result = CONTROLLER_PAK_GOOD;
                }
                if (D_80126A6C != 0) {
                    D_80126A10 = 1;
                    D_80126A6C = 0;
                }
            } else if (temp == CONTROLLER_PAK_NOT_FOUND) {
                result = CONTROLLER_PAK_GOOD;
            } else if (D_80126A18 < 0 && temp == CONTROLLER_PAK_CHANGED) {
                numAttempts = 0;
            }
        }
    } while (numAttempts == 0);
    return result;
}

SIDeviceStatus func_800867D4(void) {
    SIDeviceStatus ret = CONTROLLER_PAK_GOOD;

    D_80126A00 = 0;

    switch (D_80126A0C[D_80126BD4].saveFileType) {
        case SAVE_FILE_TYPE_UNK1:
            mark_read_save_file(D_80126A0C[D_80126BD4].controllerIndex);
            func_800861C8(D_80126A04, &D_80126A00);
            ret = func_800860A8(0, &D_80126A18, D_80126A04, &D_80126A00, get_game_data_file_size(), -1);
            break;
        case SAVE_FILE_TYPE_UNK2:
            ret = func_800860A8(0, &D_80126A18, D_80126A04, &D_80126A00, get_time_data_file_size(), -1);
            break;
        case SAVE_FILE_TYPE_GAME_DATA:
            func_800861C8(D_80126A04, &D_80126A00);
            ret = func_800860A8(1, &D_80126A1C, D_80126A04, &D_80126A00, get_game_data_file_size(),
                                D_80126A0C[D_80126BD4].controllerIndex);
            break;
        case SAVE_FILE_TYPE_TIME_DATA:
            D_80126A04[D_80126A00++].saveFileType = SAVE_FILE_TYPE_UNK2;
            ret = func_800860A8(1, &D_80126A1C, D_80126A04, &D_80126A00, get_time_data_file_size(),
                                D_80126A0C[D_80126BD4].controllerIndex);
            break;
        case SAVE_FILE_TYPE_GHOST_DATA:
            D_80126A04[D_80126A00++].saveFileType = SAVE_FILE_TYPE_UNK9;
            ret = func_800860A8(1, &D_80126A1C, D_80126A04, &D_80126A00, get_ghost_data_file_size(),
                                D_80126A0C[D_80126BD4].controllerIndex);
            break;
    }

    D_80126A04[D_80126A00++].saveFileType = SAVE_FILE_TYPE_UNK7;

    return ret;
}

void func_80086A48(s32 arg0) {
    f32 temp, temp2;
    f32 temp3, temp4;
    temp = D_80126BD4;
    temp2 = D_80126BE4;
    while (arg0 > 0) {
        if (D_80126A08 > 0) {
            temp3 = temp - D_80126BDC;
            D_80126BDC += (0.1f * temp3);
        }
        if (gMenuOptionCount > 0 && D_80126A00 > 0) {
            temp4 = temp2 - D_80126BEC;
            D_80126BEC += (0.1f * temp4);
        }
        arg0--;
    }
}

SIDeviceStatus func_80086AFC(void) {
    s32 i;
    SIDeviceStatus ret;
    UNUSED s32 pad[2];
    char fileExt[PFS_FILE_EXT_LEN];
    Settings *settings;

    settings = get_settings();
    switch (D_80126A0C[D_80126BD4].saveFileType) {
        case SAVE_FILE_TYPE_UNK1:
            switch (D_80126A04[D_80126BE4].saveFileType) {
                case SAVE_FILE_TYPE_UNK1:
                    force_mark_write_save_file(D_80126A04[D_80126BE4].controllerIndex);
                    gSavefileData[D_80126A04[D_80126BE4].controllerIndex]->cutsceneFlags = settings->cutsceneFlags;
                    gSavefileData[D_80126A04[D_80126BE4].controllerIndex]->newGame = FALSE;
                    *gSavefileData[D_80126A04[D_80126BE4].controllerIndex]->balloonsPtr = *settings->balloonsPtr;
                    gSavefileData[D_80126A04[D_80126BE4].controllerIndex]->filename = settings->filename;
                    break;
                case SAVE_FILE_TYPE_UNK8:
                    ret = write_game_data_to_controller_pak(D_80126A04[D_80126BE4].controllerIndex, settings);
                    break;
                case SAVE_FILE_TYPE_UNK7:
                    mark_save_file_to_erase(D_80126A0C[D_80126BD4].controllerIndex);
                    gSavefileData[D_80126A0C[D_80126BD4].controllerIndex]->newGame = TRUE;
                    break;
            }
            break;
        case SAVE_FILE_TYPE_UNK2:
            if (D_80126A04[D_80126BE4].saveFileType != SAVE_FILE_TYPE_UNK7) {
                if (D_80126A04[D_80126BE4].saveFileType == SAVE_FILE_TYPE_UNK8) {
                    ret = write_time_data_to_controller_pak(D_80126A04[D_80126BE4].controllerIndex, settings);
                }
            } else {
                clear_lap_records(settings, 3);
                mark_to_write_flap_and_course_times();
                unset_eeprom_settings_value(
                    0xFFFFF0); // Reset most eeprom save data, but keep Adventure 2, and Drumstick.
            }
            break;
        case SAVE_FILE_TYPE_GAME_DATA:
            switch (D_80126A04[D_80126BE4].saveFileType) {
                case SAVE_FILE_TYPE_UNK1:
                    ret = read_game_data_from_controller_pak(D_80126A0C[D_80126BD4].controllerIndex,
                                                             D_80126A0C[D_80126BD4].saveFileExt, settings);
                    if (settings->cutsceneFlags & 4 && !is_adventure_two_unlocked()) {
                        ret = CONTROLLER_PAK_NEED_SECOND_ADVENTURE;
                    }
                    if (ret == CONTROLLER_PAK_GOOD) {
                        force_mark_write_save_file(D_80126A04[D_80126BE4].controllerIndex);
                        gSavefileData[D_80126A04[D_80126BE4].controllerIndex]->cutsceneFlags = settings->cutsceneFlags;
                        gSavefileData[D_80126A04[D_80126BE4].controllerIndex]->newGame = 0;
                        *gSavefileData[D_80126A04[D_80126BE4].controllerIndex]->balloonsPtr = *settings->balloonsPtr;
                        gSavefileData[D_80126A04[D_80126BE4].controllerIndex]->filename = settings->filename;
                    }
                    break;
                case SAVE_FILE_TYPE_UNK8:
                    ret = read_game_data_from_controller_pak(D_80126A0C[D_80126BD4].controllerIndex,
                                                             D_80126A0C[D_80126BD4].saveFileExt, gSavefileData[3]);
                    if (ret == CONTROLLER_PAK_GOOD) {
                        ret =
                            write_game_data_to_controller_pak(D_80126A04[D_80126BE4].controllerIndex, gSavefileData[3]);
                    }
                    break;
                case SAVE_FILE_TYPE_UNK7:
                    ret = delete_file(D_80126A0C[D_80126BD4].controllerIndex, D_80126A0C[D_80126BD4].saveFileNumber);
                    break;
            }
            break;
        case SAVE_FILE_TYPE_TIME_DATA:
            for (i = 0; D_80126A0C[D_80126BD4].saveFileExt[i] != '\0'; i++) {}
            if (i > 0) {
                fileExt[0] = D_80126A0C[D_80126BD4].saveFileExt[i - 1];
            } else {
                fileExt[0] = 'A';
            }
            fileExt[1] = '\0';
            switch (D_80126A04[D_80126BE4].saveFileType) {
                case SAVE_FILE_TYPE_UNK2:
                    ret = read_time_data_from_controller_pak(D_80126A0C[D_80126BD4].controllerIndex, fileExt, settings);
                    break;
                case SAVE_FILE_TYPE_UNK8:
                    ret = read_time_data_from_controller_pak(D_80126A0C[D_80126BD4].controllerIndex, fileExt, settings);
                    if (ret == CONTROLLER_PAK_GOOD) {
                        ret = write_time_data_to_controller_pak(D_80126A04[D_80126BE4].controllerIndex, settings);
                    }
                    mark_to_read_flap_and_course_times();
                    break;
                case SAVE_FILE_TYPE_UNK7:
                    ret = delete_file(D_80126A0C[D_80126BD4].controllerIndex, D_80126A0C[D_80126BD4].saveFileNumber);
                    break;
            }
            break;
        case SAVE_FILE_TYPE_GHOST_DATA:
            if (D_80126A04[D_80126BE4].saveFileType != SAVE_FILE_TYPE_UNK7) {
                if (D_80126A04[D_80126BE4].saveFileType != SAVE_FILE_TYPE_UNK8) {
                    if (D_80126A04[D_80126BE4].saveFileType == SAVE_FILE_TYPE_UNK9) {
                        gMenuDelay = 1;
                        D_801264D0 = D_80126A0C[D_80126BD4].controllerIndex;
                    }
                } else {
                    ret = copy_controller_pak_data(D_80126A0C[D_80126BD4].controllerIndex,
                                                   D_80126A0C[D_80126BD4].saveFileNumber,
                                                   D_80126A04[D_80126BE4].controllerIndex);
                }
            } else {
                ret = delete_file(D_80126A0C[D_80126BD4].controllerIndex, D_80126A0C[D_80126BD4].saveFileNumber);
            }
            break;
        case SAVE_FILE_TYPE_UNKNOWN:
            if (D_80126A04[D_80126BE4].saveFileType == SAVE_FILE_TYPE_UNK7) {
                ret = delete_file(D_80126A0C[D_80126BD4].controllerIndex, D_80126A0C[D_80126BD4].saveFileNumber);
            }
            break;
        case SAVE_FILE_TYPE_UNKA:
            if (D_80126A04[D_80126BE4].saveFileType == SAVE_FILE_TYPE_UNK7) {
                unset_eeprom_settings_value(
                    0xFFFFF3); // Reset most eeprom save data including Adventure Two unlock and Drumstick unlock.
                gActiveMagicCodes &= ~(CHEAT_CONTROL_TT | CHEAT_CONTROL_DRUMSTICK);
                gUnlockedMagicCodes &= ~(CHEAT_CONTROL_TT | CHEAT_CONTROL_DRUMSTICK);
            }
            break;
        default:
            ret = CONTROLLER_PAK_GOOD;
            break;
    }
    return ret;
}

void func_800871D8(SIDeviceStatus deviceStatus) {
    s32 i;
    s32 j;
    s32 k;
    s32 y;
    char *text;

    gControllerIndex = (deviceStatus >> 30) & 3; // Gets the controller index from the device status.
    deviceStatus &= 0x3FFFFFFF;                  // Removes the controller index from the device status value.
    gDeviceStatusStrings = gContPakStrings[deviceStatus];
    D_800DFADC = deviceStatus;
    D_80126A74 = 0;

    for (k = 0; gDeviceStatusStrings[k] != NULL; k++) {}
    k++;
    for (; gDeviceStatusStrings[k] != NULL; D_80126A74++, k++) {}

    D_80126A78 = D_80126A74 - 1;

    assign_dialogue_box_id(7);
    set_current_dialogue_box_coords(7, 40, SCREEN_HEIGHT_HALF - (((k * 16) + 44) >> 1), 280,
                                    (((k * 16) + 44) >> 1) + SCREEN_HEIGHT_HALF);
    set_current_dialogue_background_colour(7, 0, 0, 0, 160);
    set_current_text_background_colour(7, 0, 0, 0, 0);
    set_dialogue_font(7, 2);
    set_current_text_colour(7, 255, 255, 255, 0, 255);
    text = gMenuText[ASSET_MENU_TEXT_PAKERROR];
    if (gDeviceStatusStrings == gContPakRumbleDetectedStrings ||
        gDeviceStatusStrings == gContPakSwitchToRumbleStrings) {
        text = gMenuText[ASSET_MENU_TEXT_CAUTION];
    } else if (gDeviceStatusStrings == gContPakNeed2ndAdvStrings) {
        text = gMenuText[ASSET_MENU_TEXT_GAMEERROR];
    }
    render_dialogue_text(7, POS_CENTRED, 20, text, 1, ALIGN_MIDDLE_CENTER);
    y = 52;
    i = 0;
    set_dialogue_font(7, ASSET_FONTS_FUNFONT);
    for (; gDeviceStatusStrings[i] != NULL; i++, y += 16) {
        render_dialogue_text(7, POS_CENTRED, y, gDeviceStatusStrings[i], gControllerIndex + 1, ALIGN_MIDDLE_CENTER);
    }
    i++;
    y += 16;
    for (j = 0; gDeviceStatusStrings[i] != NULL; i++, j++, y += 16) {
        D_80126A80[j] = render_dialogue_text(7, POS_CENTRED, y, gDeviceStatusStrings[i], 1, ALIGN_MIDDLE_CENTER);
    }
    gMenuOptionCount |= 8;
}

s32 func_800874D0(s32 buttonsPressed, s32 arg1) {
    s32 ret;

    ret = 0;
    if (buttonsPressed & B_BUTTON) {
        gMenuOptionCount = 0;
        if (D_80126A10 != D_80126A14) {
            func_800871D8(CONTROLLER_PAK_SWITCH_TO_RUMBLE);
        } else {
            sound_play(SOUND_MENU_BACK3, NULL);
            ret = -1;
        }
    } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        sound_play(SOUND_SELECT2, NULL);
        gMenuOptionCount = 4;
    } else if ((arg1 < 0) && (D_80126BD4 > 0)) {
        sound_play(SOUND_MENU_PICK2, NULL);
        D_80126BD4--;
    } else if ((arg1 > 0) && (D_80126BD4 < (D_80126A08 - 1))) {
        sound_play(SOUND_MENU_PICK2, NULL);
        D_80126BD4++;
    }
    return ret;
}

s32 func_800875E4(s32 buttonsPressed, s32 arg1) {
    if (buttonsPressed & B_BUTTON) {
        sound_play(SOUND_MENU_BACK3, NULL);
        gMenuOptionCount = 3;
    } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        sound_play(SOUND_SELECT2, NULL);
        gMenuOptionCount = 6;
    } else if ((arg1 < 0) && (D_80126BE4 > 0)) {
        sound_play(SOUND_MENU_PICK2, NULL);
        D_80126BE4--;
    } else if ((arg1 > 0) && (D_80126BE4 < D_80126A00 - 1)) {
        sound_play(SOUND_MENU_PICK2, NULL);
        D_80126BE4++;
    }

    return 0;
}

s32 func_800876CC(s32 buttonsPressed, UNUSED s32 arg1) {
    if (buttonsPressed & B_BUTTON) {
        sound_play(SOUND_MENU_BACK3, NULL);
        gMenuOptionCount = 5;
    } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        sound_play(SOUND_SELECT2, NULL);
        gMenuOptionCount = 7;
        gOpacityDecayTimer = 0;
    }

    return 0;
}

s32 func_80087734(s32 buttonsPressed, s32 yAxis) {
    UNUSED s32 pad[2];
    s32 sp1C;
    s32 i;
    s32 temp;

    temp = gOptionBlinkTimer * 8;
    if (temp > 255) {
        temp = 511 - temp;
    }
    sp1C = (gMenuOptionCount & 7);
    for (i = 0; i < D_80126A74; i++) {
        if (i == D_80126A78) {
            D_80126A80[i]->unk13 = temp;
        } else {
            D_80126A80[i]->unk13 = 0;
        }
    }
    if (buttonsPressed & B_BUTTON ||
        (buttonsPressed & (START_BUTTON | A_BUTTON) && (u32) D_80126A74 == (u32) (D_80126A78 + 1))) {
        sound_play(SOUND_MENU_BACK3, NULL);
        gMenuOptionCount &= ~8;
        switch (sp1C) {
            case 0:
                if (!(buttonsPressed & (START_BUTTON | A_BUTTON))) {
                    gOpacityDecayTimer = 6;
                    gMenuOptionCount = 1;
                }
                break;
            case 2:
                switch (D_800DFADC) {
                    case CONTROLLER_PAK_CHANGED:
                        gOpacityDecayTimer = 5;
                        gMenuOptionCount = 1;
                        break;
                    case CONTROLLER_PAK_NOT_FOUND:
                    case CONTROLLER_PAK_INCONSISTENT:
                    case CONTROLLER_PAK_WITH_BAD_ID:
                    case CONTROLLER_PAK_BAD_DATA:
                        D_80126A18 = 0;
                        break;
                    case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
                        D_80126A18 = -1;
                        break;
                    default:
                        D_80126A18 = 1;
                        break;
                }
                break;
            case 4:
                switch (D_800DFADC) {
                    case CONTROLLER_PAK_NOT_FOUND:
                    case CONTROLLER_PAK_CHANGED:
                        gOpacityDecayTimer = 5;
                        gMenuOptionCount = 1;
                        break;
                    case CONTROLLER_PAK_INCONSISTENT:
                    case CONTROLLER_PAK_WITH_BAD_ID:
                    case CONTROLLER_PAK_BAD_DATA:
                        D_80126A1C = 0;
                        break;
                    case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
                        D_80126A1C = -1;
                        break;
                    default:
                        D_80126A1C = 1;
                        break;
                }
                break;
            case 7:
                switch (D_800DFADC) {
                    case CONTROLLER_PAK_NOT_FOUND:
                    case CONTROLLER_PAK_INCONSISTENT:
                    case CONTROLLER_PAK_WITH_BAD_ID:
                    case CONTROLLER_PAK_CHANGED:
                    case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
                        gOpacityDecayTimer = 5;
                        gMenuOptionCount = 1;
                        break;
                    case CONTROLLER_PAK_BAD_DATA:
                    case CONTROLLER_PAK_NEED_SECOND_ADVENTURE:
                        gMenuOptionCount = 4;
                        break;
                }
                break;
        }
    } else if (buttonsPressed & (START_BUTTON | A_BUTTON)) {
        sound_play(SOUND_SELECT2, NULL);
        gMenuOptionCount &= ~8;
        switch (D_800DFADC) {
            case CONTROLLER_PAK_WITH_BAD_ID:
                reformat_controller_pak(gControllerIndex);
                if (sp1C == 4) {
                    D_80126A1C = 0;
                } else if (sp1C == 7) {
                    D_80126A18 = 0;
                }
                break;
            case CONTROLLER_PAK_INCONSISTENT:
            case CONTROLLER_PAK_BAD_DATA:
                repair_controller_pak(gControllerIndex);
                if (sp1C == 4) {
                    D_80126A1C = 1;
                } else if (sp1C == 2) {
                    D_80126A18 = 1;
                }
                break;
            case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
                if (sp1C == 4) {
                    D_80126A1C = -1;
                } else {
                    D_80126A18 = -1;
                }
                break;
        }
    } else if (yAxis < 0 && D_80126A78 < (D_80126A74 - 1)) {
        sound_play(SOUND_MENU_PICK2, NULL);
        D_80126A78++;
    } else if (yAxis > 0 && D_80126A78 > 0) {
        sound_play(SOUND_MENU_PICK2, NULL);
        D_80126A78--;
    }
    return 0;
}

s32 menu_save_options_loop(s32 updateRate) {
    SIDeviceStatus result;
    s32 buttonsPressed;
    s32 i;
    s32 yAxis;
    s32 xAxis;

    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }
    if ((gMenuOptionCount & 7) >= 2) {
        func_80086A48(updateRate);
    }
    if (gMenuDelay > -20 && gMenuDelay < 20) {
        func_80085B9C(updateRate);
    }
    if (gMenuDelay != 0) {
        if (gMenuDelay >= 31) {
            func_80087EB8();
            menu_init(MENU_GHOST_DATA);
        } else if (gMenuDelay < -30) {
            func_80087EB8();
            menu_init(MENU_OPTIONS);
        }
        return 0;
    }
    buttonsPressed = 0;
    xAxis = 0;
    yAxis = 0;
    if (gIgnorePlayerInputTime == 0) {
        for (i = 0; i < 4; i++) {
            xAxis += gControllersXAxisDirection[i];
            yAxis += gControllersYAxisDirection[i];
            buttonsPressed |= get_buttons_pressed_from_player(i);
        }
    }
    if (gMenuOptionCount & 8) {
        gMenuDelay = func_80087734(buttonsPressed, yAxis);
    } else {
        switch (gMenuOptionCount) {
            case 0:
                gMenuDelay = -1;
                break;
            case 1:
                gOpacityDecayTimer++;
                if (gOpacityDecayTimer >= 11) {
                    gMenuOptionCount = 2;
                }
                break;
            case 2:
                D_80126BD4 = 0;
                D_80126BDC = 0.0f;
                result = func_800862C4();
                if (result != 0) {
                    func_800871D8(result);
                } else {
                    gMenuOptionCount = 3;
                }
                break;
            case 3:
                gMenuDelay = func_800874D0(buttonsPressed, xAxis);
                break;
            case 4:
                D_80126BE4 = 0;
                D_80126BEC = 0.0f;
                result = func_800867D4();
                if (result != CONTROLLER_PAK_GOOD) {
                    func_800871D8(result);
                } else {
                    gMenuOptionCount = 5;
                }
                break;
            case 5:
                gMenuDelay = func_800875E4(buttonsPressed, xAxis);
                break;
            case 6:
                gMenuDelay = func_800876CC(buttonsPressed, xAxis);
                break;
            case 7:
                gOpacityDecayTimer++;
                if (gOpacityDecayTimer >= 4) {
                    result = func_80086AFC();
                    if (result != CONTROLLER_PAK_GOOD) {
                        func_800871D8(result);
                    } else {
                        gOpacityDecayTimer = 6;
                        gMenuOptionCount = 1;
                    }
                }
                break;
        }
        if (gMenuDelay != 0) {
            transition_begin(&sMenuTransitionFadeIn);
        }
    }
    gIgnorePlayerInputTime = 0;

    return MENU_RESULT_CONTINUE;
}

void func_80087EB8(void) {
    unload_font(ASSET_FONTS_BIGFONT);
    func_8007FF88();
    func_8009C4A8(gSaveMenuObjectIndices);
    assign_dialogue_box_id(7);
    free_from_memory_pool((void *) D_80126A0C);
    free_from_memory_pool((void *) D_80126A64);
}

#ifdef NON_EQUIVALENT
// Nearly complete
SIDeviceStatus func_80087F14(s32 *controllerIndex, s32 arg1) {
    s32 ret;
    s32 j = 0;
    s32 k = 0;
    s32 i = 0;
    s32 controllerIndexVal;
    s32 pakStatusSuccess;
    s32 pakStatusError3;
    s32 pakStatusError9;
    s32 bytesFree;
    s32 notesFree;
    s32 pakStatusErrorNoFreeSpace;
    s32 pakStatus;

    pakStatusSuccess = 0;
    pakStatusError3 = 0;
    pakStatusError9 = 0;
    pakStatusErrorNoFreeSpace = 0;
    // Is this really <= 0?
    for (i = 0; i <= 0; i++) {
        // sControllerPakIssueNotFound[i] = 0;
        sControllerPakFatalErrorFound[i] = 0;
        sControllerPakNoFreeSpace[i] = 0;
        sControllerPakBadData[i] = 0;
        ret = get_free_space(i, &bytesFree, &notesFree);
        pakStatus = ret & 0xFF; // Upper 2 bits are controller index
        if (ret == CONTROLLER_PAK_GOOD) {
            sControllerPakIssueNotFound[i] = 1;
            if (bytesFree == 0 || notesFree == 0) {
                sControllerPakNoFreeSpace[i] = 1;
                if (sControllerPakDataPresent[i] == 0) {
                    pakStatusErrorNoFreeSpace++;
                }
            }
            pakStatusSuccess++;
        } else {
            sControllerPakIssueNotFound[i] = 0;
            // Bad data
            if (pakStatus == CONTROLLER_PAK_BAD_DATA) {
                sControllerPakBadData[i] = 1;
                pakStatusError9++;
            }
            // Error inconsistent
            if (pakStatus == CONTROLLER_PAK_INCONSISTENT) {
                // Repair file system
                repair_controller_pak(i);
            }
            // fatal error
            if (pakStatus == CONTROLLER_PAK_WITH_BAD_ID) {
                sControllerPakFatalErrorFound[i] = 1;
                pakStatusError3++;
            }
        }
    }
    if ((pakStatusSuccess == 0) || (pakStatusError3 != 0) || (pakStatusErrorNoFreeSpace != 0) ||
        (pakStatusError9 != 0)) {
        return CONTROLLER_PAK_NOT_FOUND; // Return unsuccessfully?
    }

    controllerIndexVal = *controllerIndex;
    if (controllerIndexVal < 0) {
        i = controllerIndexVal;
        do {
            controllerIndexVal++;
            i++;
            if (controllerIndexVal > 0) {
                controllerIndexVal--;
                i--;
            }
        } while (sControllerPakIssueNotFound[i] == 0);
    } else if (sControllerPakIssueNotFound[*controllerIndex] == 0 || arg1 > 0) {
        i = controllerIndexVal;
        do {
            controllerIndexVal++;
            i++;
            if (controllerIndexVal > 0) {
                controllerIndexVal--;
                i--;
            }
        } while (sControllerPakIssueNotFound[i] == 0);
    } else if (arg1 < 0) {
        i = controllerIndexVal;
        do {
            controllerIndexVal--;
            i--;
            if (controllerIndexVal < 0) {
                ;
                controllerIndexVal++;
                i++;
            }
        } while (sControllerPakIssueNotFound[i] == 0);
    }

    *controllerIndex = controllerIndexVal;
    ret = get_controller_pak_file_list(controllerIndexVal, 16, &sCurrentControllerPakAllFileNames,
                                       &sCurrentControllerPakAllFileExtensions, &sCurrentControllerPakAllFileSizes,
                                       &sCurrentControllerPakAllFileTypes);

    if (ret == CONTROLLER_PAK_GOOD) {
        i = 0;
        j = 0;
        do {
            sCurrentControllerPakAllFileSizes[i] = sCurrentControllerPakAllFileSizes[i] / 256;
            if (sCurrentControllerPakAllFileNames[i] != 0) {
                k = 0;
                for (; sCurrentControllerPakAllFileNames[i][k] != 0; j++, k++) {
                    D_80126AA0[i][j] = sCurrentControllerPakAllFileNames[i][k];
                }

                if ((sCurrentControllerPakAllFileExtensions[i] != 0) &&
                    (*sCurrentControllerPakAllFileExtensions[i] != 0)) {
                    D_80126AA0[i][j] = '.';
                    j++;
                    k = 0;
                    for (; sCurrentControllerPakAllFileExtensions[i][k] != 0; j++, k++) {
                        D_80126AA0[i][j] = sCurrentControllerPakAllFileExtensions[i][k];
                    }
                }
            }
            if (j == 0) {
                D_80126AA0[i][j] = '-';
                j++;
            }
            i++;
            D_80126AA0[i - 1][j] = 0;
        } while (&D_80126AA0 != &sCurrentControllerPakAllFileNames);

        packDirectoryFree();                                                     // Free D_800DE440 from memory
        get_free_space(*controllerIndex, &sCurrentControllerPakFreeSpace, NULL); // Get Available Space in Controller
                                                                                 // Pak
        sCurrentControllerPakFreeSpace = sCurrentControllerPakFreeSpace / 256;   // Bytes
        ret = pakStatus;                                                         // Really?
    }

    return ret;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80087F14.s")
#endif

/**
 * Sets and returns an error code if any controller paks have an error.
 * Current implementation only checks the first controller pak.
 * 0 = No Error
 * 1 = Fatal Error
 * 2 = No Free Space
 * 3 = Corrupt Data
 */
PakError check_for_controller_pak_errors(void) {
    s32 errorFound;
    s32 i;

    errorFound = 0;
    sControllerPakError = PAK_ERROR_NONE;

    // This has been hard limited to just the first controller pak, but can easily be modified to check the rest with i
    // <= MAXCONTROLLERS
    for (i = 0; i <= 0 && errorFound == 0; i++) {
        if (sControllerPakFatalErrorFound[i] != 0) {
            gControllerPakMenuElement[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_PAKERROR]; // PAK ERROR
            gControllerPakMenuElement[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_PAKERROR]; // PAK ERROR
            gControllerPakMenuElement[2].unk14_a.asciiText =
                gMenuText[ASSET_MENU_TEXT_CONTPAK1 + i]; // CONTROLLER PAK 1 / 2 / 3 / 4
            gControllerPakMenuElement[3].unk14_a.asciiText =
                gMenuText[ASSET_MENU_TEXT_CONTPAKISDAMAGED_0]; // IRREPARABLY DAMAGED.
            gControllerPakMenuElement[4].unk14_a.asciiText =
                gMenuText[ASSET_MENU_TEXT_TURNOFFN64_0]; // Switch off the N64
            gControllerPakMenuElement[5].unk14_a.asciiText =
                gMenuText[ASSET_MENU_TEXT_TURNOFFN64_1]; // and remove the controller pak.
            sControllerPakError = PAK_ERROR_FATAL;
            errorFound = 1;
        } else if ((sControllerPakNoFreeSpace[i] != 0) && (sControllerPakDataPresent[i] == 0)) {
            gControllerPakMenuElement[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION]; // CAUTION
            gControllerPakMenuElement[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION]; // CAUTION
            gControllerPakMenuElement[2].unk14_a.asciiText =
                gMenuText[ASSET_MENU_TEXT_CONTPAK1 + i]; // CONTROLLER PAK 1 / 2 / 3 / 4
            gControllerPakMenuElement[3].unk14_a.asciiText =
                gMenuText[ASSET_MENU_TEXT_CONTPAKFULL];                                           // CONTROLLER PAK FULL
            gControllerPakMenuElement[4].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CONTINUE]; // CONTINUE
            gControllerPakMenuElement[5].unk14_a.asciiText = NULL;
            sControllerPakDataPresent[i] = 1;
            sControllerPakError = PAK_ERROR_FULL;
            errorFound = 1;
        } else if (sControllerPakBadData[i] != 0) {
            gControllerPakMenuElement[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION]; // CAUTION
            gControllerPakMenuElement[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION]; // CAUTION
            gControllerPakMenuElement[2].unk14_a.asciiText =
                gMenuText[ASSET_MENU_TEXT_CONTPAK1 + i]; // CONTROLLER PAK 1 / 2 / 3 / 4
            gControllerPakMenuElement[3].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_0]; // CORRUPT DATA.
            gControllerPakMenuElement[4].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_1]; // TRY AGAIN!
            gControllerPakMenuElement[5].unk14_a.asciiText = NULL;
            sControllerPakError = PAK_ERROR_CORRUPT;
            errorFound = 1;
        }
    }

    return sControllerPakError;
}

/**
 * Initialise boot screen menu.
 * Load the title textures into RAM.
 */
void menu_boot_init(void) {
    s32 i;

    transition_begin(&sMenuTransitionFadeOut);
    set_background_prim_colour(0, 0, 0);
    func_8009C674(sGameTitleTileTextures);

    // Sets up the 11 texture pointers for the "Diddy Kong Racing" logo.
    for (i = 0; i < 11; i++) {
        sGameTitleTileOffsets[i].texture = gMenuObjects[sGameTitleTileTextures[i]];
    }

    // Reset variables for menu_boot_loop()
    gBootMenuPhase = 0;
    gBootMenuTimer = 0;
}

s32 menu_boot_loop(s32 updateRate) {
    s32 out;
    s32 temp;
    s32 y;

    out = 0;

    y = SCREEN_HEIGHT_HALF;
    if (osTvType == TV_TYPE_PAL) {
        y = SCREEN_HEIGHT_HALF_PAL;
    }

    temp = y;

    switch (gBootMenuPhase) {
        case 0:
            if (gBootMenuTimer < 32) {
                gBootMenuTimer += updateRate;
                if (gBootMenuTimer >= 33) {
                    gBootMenuTimer = 32;
                }
            } else {
                func_800887E8();
                gBootMenuPhase = 1;
            }
            break;
        case 1:
            if (gBootMenuTimer < 140) {
                gBootMenuTimer += updateRate;
                if (gBootMenuTimer >= 141) {
                    gBootMenuTimer = 140;
                }
            } else {
                func_800887C4();
                gBootMenuPhase = 2;
            }
            if (gBootMenuTimer >= 129) {
                temp = 300;
            }
            break;
        case 2:
            if (gMenuDelay && check_fadeout_transition() == 0) {
                transition_begin(&sMenuTransitionFadeInFast);
            }
            temp = 300;
            out = menu_controller_pak_loop(updateRate);
            break;
    }

    if (temp < 300) {
        render_textured_rectangle(&sMenuCurrDisplayList, sGameTitleTileOffsets, SCREEN_WIDTH_HALF, temp, 255, 255, 255,
                                  255);
        reset_render_settings(&sMenuCurrDisplayList);
    }

    return out;
}

void func_800887C4(void) {
    func_8009C4A8((s16 *) sGameTitleTileTextures);
}

void func_800887E8(void) {
    s32 i;

    // Starting point
    D_80126AA0[0] = allocate_from_main_pool_safe(0x200, COLOUR_TAG_WHITE);

    // Fills in the table.
    for (i = 1; i < 16; i++) {
        D_80126AA0[i] = (char *) (((u32) D_80126AA0[0]) + (i * 0x20));
    }

    for (i = 0; i < 1; i++) {
        sControllerPakDataPresent[i] = 0;
    }

    D_80126C10 = 0;
    gMenuOptionCount = 0;
    gOptionBlinkTimer = 0;
    gMenuOption = -1;
    load_menu_text(get_language());
    if (func_80087F14(&gMenuOption, 0) == CONTROLLER_PAK_GOOD) {
        gMenuDelay = 0;
    } else if (check_for_controller_pak_errors() == PAK_ERROR_NONE) {
        gMenuDelay = 20;
    }
    if (sControllerPakError == PAK_ERROR_NONE && !gShowControllerPakMenu) {
        gMenuDelay = 20;
    }
    gMenuCurIndex = 0;
    gOpacityDecayTimer = 0;
    func_8009C6D4(63);
    assign_menu_arrow_textures();
    if (osTvType == TV_TYPE_PAL) {
        sControllerPakMenuNumberOfRows = 8;
    } else {
        sControllerPakMenuNumberOfRows = 7;
    }
    load_font(ASSET_FONTS_BIGFONT);
}

// Visual Aid : https://i.imgur.com/7T2Scdr.png
void render_controller_pak_ui(UNUSED s32 updateRate) {
    s32 alpha;
    s32 i;
    char *noteText;
    char *fileNameText;
    char *pagesText;
    s32 numberOfPages;
    s32 yPos = 0;

    set_text_background_colour(0, 0, 0, 0);
    alpha = gOptionBlinkTimer << 3;
    if (alpha >= 256) {
        alpha = 511 - alpha;
    }
    if (sControllerPakError != PAK_ERROR_NONE) {
        draw_menu_elements(1, gControllerPakMenuElement, 1.0f);
    } else if (gShowControllerPakMenu != 0) {
        set_text_font(ASSET_FONTS_BIGFONT);
        set_text_colour(0, 0, 0, 255, 128);
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 33, gMenuText[ASSET_MENU_TEXT_CONTPAK],
                  ALIGN_MIDDLE_CENTER); // CONTROLLER PAK - Drop Shadow
        set_text_colour(255, 255, 255, 0, 255);
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 30, gMenuText[ASSET_MENU_TEXT_CONTPAK],
                  ALIGN_MIDDLE_CENTER); // CONTROLLER PAK - Main Text

        yPos += 48;

        assign_dialogue_box_id(6);
        set_current_dialogue_box_coords(6, 58, yPos, 262, yPos + 30);

        if (gMenuCurIndex == -1) {
            set_current_dialogue_background_colour(6, 255, 255, 255, (alpha >> 1) + 128);
        } else {
            set_current_dialogue_background_colour(6, 96, 192, 92, 224);
        }

        set_dialogue_font(6, ASSET_FONTS_FUNFONT);
        set_current_text_colour(6, 255, 255, 255, 0, 255);
        set_current_text_background_colour(6, 0, 0, 0, 0);
        render_dialogue_text(6, POS_CENTRED, 2, gMenuText[86 + gMenuOption], 1,
                             HORZ_ALIGN_CENTER); // ASSET_MENU_TEXT_CONTPAK1 - CONTROLLER PAK 1 / 2 / 3 / 4
        render_dialogue_text(6, POS_CENTRED, 16, gMenuText[ASSET_MENU_TEXT_FREEPAGESX], sCurrentControllerPakFreeSpace,
                             HORZ_ALIGN_CENTER); // FREE PAGES: ~
        render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 6);

        yPos += 34; // To 82

        set_dialogue_font(6, ASSET_FONTS_SMALLFONT);
        set_current_text_background_colour(6, 0, 0, 0, 0);
        for (i = -1; i < sControllerPakMenuNumberOfRows; i++) {
            assign_dialogue_box_id(6);
            set_current_dialogue_box_coords(6, 28, yPos, 292, yPos + 14);
            if (i < 0) {
                // Red background for table header
                set_current_dialogue_background_colour(6, 224, 48, 48, 224);
                set_current_text_colour(6, 224, 224, 48, 255, 255);
                noteText = gMenuText[ASSET_MENU_TEXT_NOTE];         // NOTE
                fileNameText = gMenuText[ASSET_MENU_TEXT_FILENAME]; // FILENAME
                pagesText = gMenuText[ASSET_MENU_TEXT_PAGES];       // PAGES
                numberOfPages = 1;
            } else {
                if (gMenuCurIndex == (i + gOpacityDecayTimer)) {
                    // White background for currently selected row
                    set_current_dialogue_background_colour(6, 255, 255, 255, (alpha >> 1) + 128);
                } else {
                    // Yellow background for all other rows
                    set_current_dialogue_background_colour(6, 224, 224, 48, 224);
                }
                set_current_text_colour(6, 16, 16, 160, 255, 255);
                noteText = (char *) &D_800E820C;  //~
                pagesText = (char *) &D_800E820C; //~
                fileNameText = D_80126AA0[gOpacityDecayTimer + i];
                numberOfPages = sCurrentControllerPakAllFileSizes[gOpacityDecayTimer + i];
            }
            render_dialogue_text(6, 26, 2, noteText, gOpacityDecayTimer + i + 1, HORZ_ALIGN_CENTER);
            render_dialogue_text(6, 56, 2, fileNameText, 1, HORZ_ALIGN_LEFT);
            render_dialogue_text(6, 240, 2, pagesText, numberOfPages, HORZ_ALIGN_CENTER);
            render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 6);
            yPos += 16;
        }
        if (gOpacityDecayTimer < (16 - sControllerPakMenuNumberOfRows)) {
            if ((gOptionBlinkTimer & 8) != 0) {
                render_textured_rectangle(&sMenuCurrDisplayList, gMenuSelectionArrowDown, SCREEN_WIDTH_HALF, yPos + 8,
                                          255, 255, 255, 255);
                reset_render_settings(&sMenuCurrDisplayList);
            }
        } else {
            set_text_font(ASSET_FONTS_FUNFONT);
            if (gMenuCurIndex == 16) {
                set_text_colour(255, 255, 255, alpha, 255);
            } else {
                set_text_colour(255, 255, 255, 0, 255);
            }
            draw_text(&sMenuCurrDisplayList, POS_CENTRED, yPos, gMenuText[ASSET_MENU_TEXT_EXIT],
                      ALIGN_TOP_CENTER); // EXIT
        }
        if ((gMenuOptionCount != 0) && (D_80126C10 == 0)) {
            if (osTvType == TV_TYPE_PAL) {
                yPos = 134;
            } else {
                yPos = SCREEN_HEIGHT_HALF;
            }
            assign_dialogue_box_id(6);
            set_dialogue_font(6, ASSET_FONTS_FUNFONT);
            set_current_dialogue_box_coords(6, 76, yPos - 28, 244, yPos + 28);
            set_current_dialogue_background_colour(6, 0, 0, 0, 160);

            yPos = 4;
            for (i = 0; i <= 2; i++) {
                if (i == 0) {
                    set_current_text_colour(6, 255, 0, 255, 64, 255);
                } else if (i == gMenuOptionCount) {
                    set_current_text_colour(6, 255, 255, 255, alpha, 255);
                } else {
                    set_current_text_colour(6, 255, 255, 255, 0, 255);
                }

                // Render these three lines in this order
                // ASSET_MENU_TEXT_DELETENOTEX  - DELETE NOTE ~ ?
                // ASSET_MENU_TEXT_DELETE       - DELETE
                // ASSET_MENU_TEXT_CANCELDELETE - CANCEL
                render_dialogue_text(6, POS_CENTRED, yPos, gMenuText[ASSET_MENU_TEXT_DELETENOTEX + i],
                                     gMenuCurIndex + 1, HORZ_ALIGN_CENTER);

                if (i != 0) {
                    yPos += 16;
                } else {
                    yPos += 20;
                }
            }
            render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 6);
        }
        // Deleting File
        if (D_80126C10 != 0) {
            set_text_colour(255, 255, 255, 0, 255);
            set_text_font(ASSET_FONTS_BIGFONT);
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 128, gMenuText[ASSET_MENU_TEXT_PLEASEWAIT],
                      ALIGN_MIDDLE_CENTER);
        }
    }
}

s32 menu_controller_pak_loop(s32 updateRate) {
    s32 i;
    s32 pressedButtons;
    s32 xStick;
    s32 yStick;
    s32 playMoveSound = FALSE;
    s32 playCancelSound = FALSE;
    s32 playSelectedSound = FALSE;
    UNUSED s32 pad;
    s32 temp_v1_2;

    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay < 20) {
        render_controller_pak_ui(updateRate);
    }
    if (gMenuDelay == 0) {
        pressedButtons = 0;
        xStick = 0;
        yStick = 0;
        for (i = 0; i < MAXCONTROLLERS; i++) {
            pressedButtons |= get_buttons_pressed_from_player(i);
            xStick += gControllersXAxisDirection[i];
            yStick += gControllersYAxisDirection[i];
        }
        if (sControllerPakError != PAK_ERROR_NONE) {
            if ((sControllerPakError != PAK_ERROR_FATAL) && (pressedButtons & (A_BUTTON | START_BUTTON))) {
                sound_play(SOUND_SELECT2, NULL);
                if (func_80087F14(&gMenuOption, 0) == CONTROLLER_PAK_GOOD) {
                    sControllerPakError = PAK_ERROR_NONE;
                } else if (check_for_controller_pak_errors() == PAK_ERROR_NONE) {
                    gShowControllerPakMenu = 0;
                }
                if ((sControllerPakError == PAK_ERROR_NONE) && (gShowControllerPakMenu == 0)) {
                    playCancelSound = TRUE;
                    gMenuDelay = 1;
                    transition_begin(&sMenuTransitionFadeIn);
                }
            }
        } else {
            if (gMenuOptionCount != 0) {
                if (D_80126C10 != 0) {
                    D_80126C10--;
                    if (D_80126C10 == 0) {
                        if (delete_file(gMenuOption, gMenuCurIndex) != CONTROLLER_PAK_GOOD) {
                            // Failed to delete the file
                            playCancelSound = TRUE;
                            gMenuDelay = 1;
                            transition_begin(&sMenuTransitionFadeIn);
                        } else {
                            // File deleted successfully
                            playSelectedSound = TRUE;
                            if (func_80087F14(&gMenuOption, xStick) != CONTROLLER_PAK_GOOD) {
                                playCancelSound = TRUE;
                                gMenuDelay = 1;
                                transition_begin(&sMenuTransitionFadeIn);
                            }
                        }
                        gMenuOptionCount = 0;
                    }
                } else if (pressedButtons & B_BUTTON) {
                    playCancelSound = TRUE;
                    gMenuOptionCount = 0;
                } else if (pressedButtons & (A_BUTTON | START_BUTTON)) {
                    if (gMenuOptionCount == 1) {
                        D_80126C10 = 3;
                    } else {
                        playCancelSound = TRUE;
                        gMenuOptionCount = 0;
                    }
                } else if (yStick > 0 && gMenuOptionCount >= 2) {
                    gMenuOptionCount = 1;
                    playMoveSound = TRUE;
                } else if (yStick < 0 && gMenuOptionCount < 2) {
                    gMenuOptionCount = 2;
                    playMoveSound = TRUE;
                }
            } else if ((pressedButtons & B_BUTTON) ||
                       (gMenuCurIndex == 16 && (pressedButtons & (A_BUTTON | START_BUTTON)))) {
                playCancelSound = 1;
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
            } else {
                // gMenuCurIndex = selected menu index?
                switch (gMenuCurIndex) {
                    case -1:
                        if (yStick < 0) {
                            if (!xStick) {} // Fakematch
                            gMenuCurIndex = 0;
                            playMoveSound = TRUE;
                        }
                        break;
                    case 16:
                        if (yStick > 0) {
                            gMenuCurIndex = 15;
                            playMoveSound = TRUE;
                        }
                        break;
                    default:
                        if (pressedButtons & (A_BUTTON | START_BUTTON)) {
                            // Check if the selected menu item is a file or blank
                            if ((sCurrentControllerPakAllFileTypes[gMenuCurIndex] >= SAVE_FILE_TYPE_GAME_DATA) &&
                                (sCurrentControllerPakAllFileTypes[gMenuCurIndex] <= SAVE_FILE_TYPE_UNKNOWN)) {
                                D_80126C10 = 0;
                                gMenuOptionCount = 2;
                                playSelectedSound = TRUE;
                            } else {
                                // If it's not, just play the "back" sound
                                playCancelSound = TRUE;
                            }
                        } else {
                            if (yStick > 0) {
                                gMenuCurIndex--;
                                if (gMenuCurIndex < 0) {
                                    gMenuCurIndex = 0;
                                } else {
                                    playMoveSound = TRUE;
                                }
                            } else if (yStick < 0) {
                                gMenuCurIndex++;
                                playMoveSound = TRUE;
                            }
                        }
                        if (gMenuCurIndex >= (gOpacityDecayTimer + sControllerPakMenuNumberOfRows)) {
                            gOpacityDecayTimer = (gMenuCurIndex - sControllerPakMenuNumberOfRows) + 1;
                        }
                        if (gMenuCurIndex < gOpacityDecayTimer) {
                            gOpacityDecayTimer = gMenuCurIndex;
                        }
                        temp_v1_2 = 16 - sControllerPakMenuNumberOfRows;
                        if (temp_v1_2 < gOpacityDecayTimer) {
                            gOpacityDecayTimer = temp_v1_2;
                        }
                        if (gOpacityDecayTimer < 0) {
                            gOpacityDecayTimer = 0;
                        }
                        break;
                }
            }
        }
        if (playCancelSound) {
            // Menu Cancel Sound
            sound_play(SOUND_MENU_BACK3, NULL);
        } else if (playSelectedSound) {
            // Menu Item Selected Sound
            sound_play(SOUND_SELECT2, NULL);
        } else if (playMoveSound) {
            // Menu Moving Sound
            sound_play(SOUND_MENU_PICK2, NULL);
        }
    } else {
        gMenuDelay += updateRate;
        if (gMenuDelay >= 36) {

            func_800895A4();
            menu_init(MENU_LOGOS);
            load_level_for_menu(ASSET_LEVEL_FRONTEND, -1, 0);
        }
    }
    return 0;
}

void func_800895A4(void) {
    func_8009C508(0x3F);
    free_from_memory_pool(D_80126AA0[0]);
    unload_font(ASSET_FONTS_BIGFONT);
}

void menu_magic_codes_init(void) {
    gCheatInputCurrentRow = 0;
    gCheatInputCurrentColumn = 0;
    gOptionsMenuItemIndex = 0;
    gCheatInputStringLength = 0;
    sUnused_80126470 = 0;
    D_80126C4C = -1;
    D_80126C58[0] = '\0';
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    gOpacityDecayTimer = 0;
    gMenuOptionCount = 0;
    transition_begin(&sMenuTransitionFadeOut);
    set_current_dialogue_box_coords(7, 50, 50, 270, 132);
    set_current_dialogue_background_colour(7, 0, 0, 0, 128);
    assign_dialogue_box_id(7);
    load_font(ASSET_FONTS_BIGFONT);
}

void render_magic_codes_ui(UNUSED s32 updateRate) {
    u16 *cheatData;
    s32 i, j;
    s32 alpha2, alpha, green;
    s32 xPos, yPos;
    char displayChar[2];
    s32 temp;
    UNUSED s32 pad[2];

    set_text_background_colour(0, 0, 0, 0);
    render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 7);
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, gMenuText[ASSET_MENU_TEXT_MAGICCODES],
              ALIGN_MIDDLE_CENTER); // "MAGIC CODES"
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, gMenuText[ASSET_MENU_TEXT_MAGICCODES],
              ALIGN_MIDDLE_CENTER); // "MAGIC CODES"
    temp = 'A';
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_colour(255, 255, 255, 0, 255);
    // Draw the input table
    for (i = 0, yPos = 60; i < 4; i++, yPos += 22) {
        for (j = 0, xPos = 64; j < 7; j++, xPos += 32) {
            if (gOptionsMenuItemIndex == 5 && j == gCheatInputCurrentColumn && i == gCheatInputCurrentRow) {
                alpha2 = gOptionBlinkTimer * 8;
                if (alpha2 >= 256) {
                    alpha2 = 511 - alpha2;
                }
                alpha2 >>= 1;
                alpha2 += 128;
                set_text_colour(128, 255, 192, alpha2, 255);
            }
            if (temp <= 'Z') {
                displayChar[0] = temp;
                displayChar[1] = '\0';
                draw_text(&sMenuCurrDisplayList, xPos, yPos, displayChar, ALIGN_MIDDLE_CENTER); // Draw the character
            } else if (j == 5) {
                draw_text(&sMenuCurrDisplayList, xPos, yPos, (char *) &D_800E8210 /* "DEL" */, ALIGN_MIDDLE_CENTER);
            } else {
                draw_text(&sMenuCurrDisplayList, xPos, yPos, (char *) &D_800E8214 /* "OK" */, ALIGN_MIDDLE_CENTER);
            }
            if ((5 == gOptionsMenuItemIndex) && (j == gCheatInputCurrentColumn) && (i == gCheatInputCurrentRow)) {
                set_text_colour(255, 255, 255, 0, 255);
            }
            temp = (temp + 1) & 0xFF;
        }
    }

    alpha2 = gOptionBlinkTimer * 8;
    if (alpha2 >= 256) {
        alpha2 = 511 - alpha2;
    }

    set_text_font(ASSET_FONTS_FUNFONT);
    i = 0;
    temp = 164;
    yPos = 16;
    if (osTvType == TV_TYPE_PAL) {
        yPos = 24;
    }

    while (gMagicCodeMenuStrings[i] != NULL) {
        alpha = 0;
        if (i == gOptionsMenuItemIndex && gMenuOptionCount == 0) {
            alpha = alpha2;
        }
        set_text_colour(255, 255, 255, alpha, 255);
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, temp, gMagicCodeMenuStrings[i], ALIGN_MIDDLE_CENTER);
        i++;
        temp += yPos;
    }
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_colour(255, 255, 128, 128, 255);
    set_text_background_colour(0, 0, 128, 128);
    if (gOptionsMenuItemIndex == 4) {
        if (D_80126C4C == -1) {
            draw_text(&sMenuCurrDisplayList, POS_CENTRED, 144, gMenuText[ASSET_MENU_TEXT_BADCODE],
                      ALIGN_MIDDLE_CENTER); //"Sorry, the code was incorrect"
        } else {
            // Draw cheat code name.
            cheatData = (*gCheatsAssetData) + 1;
            draw_text(&sMenuCurrDisplayList, POS_CENTRED, 144,
                      &((char *) (*gCheatsAssetData))[cheatData[D_80126C4C + 1]], ALIGN_MIDDLE_CENTER);
        }
    } else if (5 == gOptionsMenuItemIndex) {
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, 144, D_80126C58, ALIGN_MIDDLE_CENTER);
    } else if (gOptionsMenuItemIndex == 6) {
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, 144, gMenuText[ASSET_MENU_TEXT_ALLCODESDELETED],
                  ALIGN_MIDDLE_CENTER); //"All cheats have been deleted"
    }
    if (gMenuOptionCount != 0) {
        if (osTvType == TV_TYPE_PAL) {
            temp = SCREEN_HEIGHT_HALF + 14;
        } else {
            temp = SCREEN_HEIGHT_HALF;
        }
        assign_dialogue_box_id(6);
        set_dialogue_font(6, ASSET_FONTS_FUNFONT);
        set_current_dialogue_box_coords(6, 76, temp - 28, 244, temp + 28);
        set_current_dialogue_background_colour(6, 0, 0, 0, 160);
        temp = 4;
        for (i = 0; i < 3; i++) {
            green = 0xFF;
            alpha = 0;
            if (i == 0) {
                green = 0;
                alpha = 64;
            } else if (i == gMenuOptionCount) {
                alpha = alpha2;
            }
            set_current_text_colour(6, 255, green, 255, alpha, 255);
            // gMenuText[148] = "CLEAR ALL CODES?", [149] = "OK", [150] = "CANCEL"
            render_dialogue_text(6, POS_CENTRED, temp, gMenuText[148 + i], 1, HORZ_ALIGN_CENTER);

            if (i != 0) {
                temp += 16;
            } else {
                temp += 20;
            }
        }
        render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 6);
    }
    if (get_filtered_cheats() & CHEAT_ROM_CHECKSUM) {
        calculate_and_display_rom_checksum();
    }
}

s32 menu_magic_codes_loop(s32 updateRate) {
    s32 i;
    s32 buttonsPressed;
    s32 xDir;
    s32 yDir;
    s32 someBool;
    s32 someBool2;
    s32 foundCheat;
    s32 menuDelay;
    s32 playBackSound;
    s32 playSelectSound;
    s32 playPickSound;
    s32 prevValue;
    char *cheatCodeText;
    u16 *cheatDataEntries;

    someBool = FALSE;
    someBool2 = FALSE;
    menuDelay = 0;
    foundCheat = FALSE;
    playBackSound = FALSE;
    playSelectSound = FALSE;
    playPickSound = FALSE;
    if (gOpacityDecayTimer != 0) {
        gOpacityDecayTimer -= updateRate;
        if (gOpacityDecayTimer < 0) {
            gOpacityDecayTimer = 0;
        }
    }
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay > -20 && gMenuDelay < 20) {
        foundCheat = 0;
        render_magic_codes_ui(updateRate);
    }
    buttonsPressed = 0;
    xDir = 0;
    yDir = 0;
    if (gIgnorePlayerInputTime == 0 && gMenuDelay == 0) {
        for (i = 0; i < MAXCONTROLLERS; i++) {
            buttonsPressed |= get_buttons_pressed_from_player(i);
            xDir += gControllersXAxisDirection[i];
            yDir += gControllersYAxisDirection[i];
        }
    }
    if (gOptionsMenuItemIndex == 4) {
        if (gOpacityDecayTimer == 0 || buttonsPressed & (A_BUTTON | START_BUTTON)) {
            gOptionsMenuItemIndex = 0;
        }
    } else if (gOptionsMenuItemIndex == 5) {
        prevValue = ((gCheatInputCurrentColumn & 0xF) * 16) | gCheatInputCurrentRow;
        if (xDir < 0) {
            gCheatInputCurrentColumn--;
            if (gCheatInputCurrentColumn < 0) {
                gCheatInputCurrentColumn = 6;
            }
        }
        if (xDir > 0) {
            gCheatInputCurrentColumn++;
            if (gCheatInputCurrentColumn >= 7) {
                gCheatInputCurrentColumn = 0;
            }
        }
        if (yDir < 0) {
            gCheatInputCurrentRow++;
            if (gCheatInputCurrentRow >= 4) {
                gCheatInputCurrentRow = 0;
            }
        }
        if (yDir > 0) {
            gCheatInputCurrentRow--;
            if (gCheatInputCurrentRow < 0) {
                gCheatInputCurrentRow = 3;
            }
        }
        if ((((gCheatInputCurrentColumn & 0xF) * 16) | gCheatInputCurrentRow) != prevValue) {
            playPickSound = TRUE;
        }
        if (buttonsPressed & A_BUTTON) {
            if (gCheatInputCurrentRow == 3 && gCheatInputCurrentColumn == 5) {
                someBool = TRUE;
            } else if (gCheatInputCurrentRow == 3 && gCheatInputCurrentColumn == 6) {
                someBool2 = TRUE;
            } else if (gCheatInputStringLength <= 18) {
                playSelectSound = TRUE;
                D_80126C58[gCheatInputStringLength] =
                    (gCheatInputCurrentRow * 7) + gCheatInputCurrentColumn + 'A'; // Convert to upper case?
                gCheatInputStringLength++;
                D_80126C58[gCheatInputStringLength] = '\0';
            }
        }
        if (buttonsPressed & B_BUTTON) {
            if (gCheatInputStringLength > 0) {
                someBool = TRUE;
            } else {
                gOptionsMenuItemIndex = 0;
            }
        }
        if (buttonsPressed & START_BUTTON) {
            someBool2 = TRUE;
        }
        if (someBool) {
            sound_play(SOUND_BOUNCE, NULL);
            if (gCheatInputStringLength > 0) {
                gCheatInputStringLength--;
                D_80126C58[gCheatInputStringLength] = '\0';
            }
        }
        if (someBool2) {
            playSelectSound = TRUE;
            if (gCheatInputStringLength == 0) {
                gOptionsMenuItemIndex = 0;
            } else {
                cheatDataEntries = &(*gCheatsAssetData)[1];
                D_80126C4C = 0; // Index into the gCheatsAssetData cheatsTable
                while ((D_80126C4C < (gNumberOfCheats * 2)) && !foundCheat) {
                    foundCheat = TRUE;
                    cheatCodeText = ((char *) (*gCheatsAssetData)) + cheatDataEntries[D_80126C4C];
                    // D_80126C58 = char *gPlayerEnteredCode; (Or something like that)
                    i = -1;
                    do {
                        i++;
                        if (cheatCodeText[i] != D_80126C58[i]) {
                            foundCheat = FALSE;
                        }
                        if (!foundCheat) {
                            do {
                            } while (0); // Fakematch
                            break;
                        }
                    } while (cheatCodeText[i] != '\0' && D_80126C58[i] != '\0');
                    if (foundCheat) {
                        continue;
                    }
                    D_80126C4C += 2;
                }
                if (!foundCheat) {
                    D_80126C4C = -1;
                } else {
                    gUnlockedMagicCodes |= 1 << (D_80126C4C >> 1);
                    gActiveMagicCodes |= 1 << (D_80126C4C >> 1);
                }
                gOptionsMenuItemIndex = 4;
                gOpacityDecayTimer = 240;
            }
        }
    } else if (gOptionsMenuItemIndex == 6) {
        if (gOpacityDecayTimer == 0 || buttonsPressed & (A_BUTTON | START_BUTTON)) {
            gOptionsMenuItemIndex = 1;
        }
    } else if (gMenuOptionCount != 0) {
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            if (gMenuOptionCount == 1) {
                gActiveMagicCodes = 0;
                gOptionsMenuItemIndex = 6;
                playSelectSound = TRUE;
                gUnlockedMagicCodes &= 3;
                gOpacityDecayTimer = 0xF0;
            } else {
                playBackSound = TRUE;
            }
            gMenuOptionCount = 0;
        } else if (buttonsPressed & B_BUTTON) {
            playBackSound = TRUE;
            gMenuOptionCount = 0;
        } else if (yDir < 0 && gMenuOptionCount == 1) {
            playPickSound = TRUE;
            gMenuOptionCount = 2;
        } else if (yDir > 0 && gMenuOptionCount == 2) {
            playPickSound = TRUE;
            gMenuOptionCount = 1;
        }
    } else {
        prevValue = gOptionsMenuItemIndex;
        if (yDir < 0) {
            gOptionsMenuItemIndex += 1;
            if (gOptionsMenuItemIndex >= 4) {
                gOptionsMenuItemIndex = 3;
            }
        }
        if (yDir > 0) {
            gOptionsMenuItemIndex -= 1;
            if (gOptionsMenuItemIndex < 0) {
                gOptionsMenuItemIndex = 0;
            }
        }
        if (prevValue != gOptionsMenuItemIndex) {
            playPickSound = TRUE;
        }
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            playSelectSound = TRUE;
            if (gOptionsMenuItemIndex == 3) {
                menuDelay = -1;
            } else if (gOptionsMenuItemIndex == 0) {
                gCheatInputCurrentRow = 0;
                gCheatInputCurrentColumn = 0;
                gCheatInputStringLength = 0;
                D_80126C58[0] = '\0';
                gOptionsMenuItemIndex = 5;
            } else if (gOptionsMenuItemIndex == 1) {
                gMenuOptionCount = 2;
            } else if (gOptionsMenuItemIndex == 2) {
                menuDelay = 1;
            }
        }
        if (buttonsPressed & (B_BUTTON)) {
            menuDelay = -1;
        }
        if (menuDelay != 0) {
            if (menuDelay < 0) {
                playBackSound = TRUE;
            }
            gMenuDelay = menuDelay;
            transition_begin(&sMenuTransitionFadeIn);
        }
    }
    if (playBackSound) {
        sound_play(SOUND_MENU_BACK3, NULL);
    } else if (playSelectSound) {
        sound_play(SOUND_SELECT2, NULL);
    } else if (playPickSound) {
        sound_play(SOUND_MENU_PICK2, NULL);
    }

    gIgnorePlayerInputTime = 0;
    if (gMenuDelay < -30 || gMenuDelay > 30) {
        unload_big_font_2();
        if (gMenuDelay < 0) {
            if (gActiveMagicCodes & CHEAT_DISPLAY_CREDITS) {
                music_change_on();
                gViewingCreditsFromCheat = TRUE;
                menu_init(MENU_CREDITS);
                gActiveMagicCodes &= ~CHEAT_DISPLAY_CREDITS;
            } else {
                menu_init(MENU_OPTIONS);
            }
        } else {
            menu_init(MENU_MAGIC_CODES_LIST);
        }
    }
    return MENU_RESULT_CONTINUE;
}

/**
 * Explicitly says to unload the ASSET_FONTS_BIGFONT type.
 */
void unload_big_font_2(void) {
    unload_font(ASSET_FONTS_BIGFONT);
}

/**
 * Initialise the magic list menu.
 * Sets the max list height based on region, and loads the arrows for scrolling.
 */
void menu_magic_codes_list_init(void) {
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    gMenuOptionCount = 0;
    gOptionsMenuItemIndex = 0;
    load_font(ASSET_FONTS_BIGFONT);
    func_8009C6D4(63);
    assign_menu_arrow_textures();
    transition_begin(&sMenuTransitionFadeOut);
    if (osTvType == TV_TYPE_PAL) {
        gNumOnscreenMagicCodes = 11;
    } else {
        gNumOnscreenMagicCodes = 10;
    }
}

void render_magic_codes_list_menu_text(UNUSED s32 updateRate) {
    s32 i;
    s32 alpha;
    s32 yPos;
    s32 numOfUnlockedCheats;
    s32 code;
    u16 *cheatData;

    set_text_background_colour(0, 0, 0, 0);
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, gMenuText[ASSET_MENU_TEXT_MAGICCODESLIST],
              ALIGN_MIDDLE_CENTER); // MAGIC CODES LIST
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, gMenuText[ASSET_MENU_TEXT_MAGICCODESLIST],
              ALIGN_MIDDLE_CENTER); // MAGIC CODES LIST

    for (i = 0, code = 1, numOfUnlockedCheats = 0; i < 32; i++, code <<= 1) {
        if (code & gUnlockedMagicCodes) {
            D_80126C80[numOfUnlockedCheats] = i;
            numOfUnlockedCheats += 1;
        }
    }
    yPos = 54;
    alpha = gOptionBlinkTimer * 8;
    if (alpha >= 256) {
        alpha = 511 - alpha;
    }
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_colour(255, 255, 255, 0, 255);
    for (i = gMenuOptionCount, cheatData = (*gCheatsAssetData) + 1;
         (i < gMenuOptionCount + gNumOnscreenMagicCodes) && (i < numOfUnlockedCheats); i++, yPos += 16) {
        if (i == gOptionsMenuItemIndex) {
            set_text_colour(255, 255, 255, alpha, 255);
        }
        draw_text(&sMenuCurrDisplayList, 48, yPos, (char *) (*gCheatsAssetData) + cheatData[(D_80126C80[i] << 1) + 1],
                  ALIGN_TOP_LEFT);
        if ((1 << D_80126C80[i]) & gActiveMagicCodes) {
            draw_text(&sMenuCurrDisplayList, 256, yPos, gMenuText[ASSET_MENU_TEXT_ON], ALIGN_TOP_LEFT); // ON
        } else {
            draw_text(&sMenuCurrDisplayList, 256, yPos, gMenuText[ASSET_MENU_TEXT_OFF], ALIGN_TOP_LEFT); // OFF
        }
        if (i == gOptionsMenuItemIndex) {
            set_text_colour(255, 255, 255, 0, 255);
        }
    }
    if (i < gMenuOptionCount + gNumOnscreenMagicCodes) {
        if (numOfUnlockedCheats == gOptionsMenuItemIndex) {
            set_text_colour(255, 255, 255, alpha, 255);
        }
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, yPos, gMenuText[ASSET_MENU_TEXT_RETURN],
                  ALIGN_TOP_CENTER); // RETURN
        return;
    }
    if (gOptionBlinkTimer & 8) {
        render_textured_rectangle(&sMenuCurrDisplayList, gMenuSelectionArrowDown, SCREEN_WIDTH_HALF, yPos + 8, 255, 255,
                                  255, 255);
    }
}

void func_8008A8F8(s32 arg0, s32 arg1, s32 arg2) {
    if ((arg0 & arg1) && (arg0 & gActiveMagicCodes)) {
        gActiveMagicCodes &= ~arg2;
    }
}

s32 menu_magic_codes_list_loop(s32 updateRate) {
    s32 previousMenuItemIndex;
    s32 xAxis;
    s32 yAxis;
    s32 delay;
    s32 buttonsPressed;
    s32 i;
    s32 numUnlockedCodes;
    s32 code;

    delay = 0;
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay > -20 && gMenuDelay < 20) {
        render_magic_codes_list_menu_text(updateRate);
    }

    buttonsPressed = 0;
    xAxis = 0;
    yAxis = 0;
    if (gIgnorePlayerInputTime == 0 && gMenuDelay == 0) {
        for (i = 0; i < MAXCONTROLLERS; i++) {
            buttonsPressed |= get_buttons_pressed_from_player(i);
            xAxis += gControllersXAxisDirection[i];
            yAxis += gControllersYAxisDirection[i];
        }
    }

    for (i = 0, code = 1, numUnlockedCodes = 0; i < MAX_CHEATS; i++) {
        if (code & gUnlockedMagicCodes) {
            D_80126C80[numUnlockedCodes] = i;
            numUnlockedCodes++;
        }
        code <<= 1;
    }

    if (((xAxis < 0) || (xAxis > 0)) && (numUnlockedCodes != gOptionsMenuItemIndex)) {
        sound_play(SOUND_SELECT2, NULL);
        code = 1 << D_80126C80[gOptionsMenuItemIndex];
        gActiveMagicCodes ^= code;                         // Toggle active cheats?
        func_8008A8F8(code, 0x10, CHEAT_SMALL_CHARACTERS); // func_8008A8F8() = Clear flags?
        func_8008A8F8(code, 0x20, CHEAT_BIG_CHARACTERS);
        func_8008A8F8(code, 0x1000,
                      (CHEAT_NO_LIMIT_TO_BANANAS | CHEAT_BANANAS_REDUCE_SPEED | CHEAT_START_WITH_10_BANANAS));
        func_8008A8F8(code, 0x6080, CHEAT_DISABLE_BANANAS);
        func_8008A8F8(code, 0x800,
                      (CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_BLUE |
                       CHEAT_ALL_BALLOONS_ARE_YELLOW | CHEAT_ALL_BALLOONS_ARE_RAINBOW | CHEAT_MAXIMUM_POWER_UP));
        func_8008A8F8(code, 0x1F8000, CHEAT_DISABLE_WEAPONS);
        func_8008A8F8(code, 0x8000,
                      (CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_BLUE | CHEAT_ALL_BALLOONS_ARE_YELLOW |
                       CHEAT_ALL_BALLOONS_ARE_RAINBOW));
        func_8008A8F8(code, 0x10000,
                      (CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_BLUE | CHEAT_ALL_BALLOONS_ARE_YELLOW |
                       CHEAT_ALL_BALLOONS_ARE_RAINBOW));
        func_8008A8F8(code, 0x20000,
                      (CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_YELLOW |
                       CHEAT_ALL_BALLOONS_ARE_RAINBOW));
        func_8008A8F8(code, 0x40000,
                      (CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_BLUE |
                       CHEAT_ALL_BALLOONS_ARE_RAINBOW));
        func_8008A8F8(code, 0x80000,
                      (CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_BLUE |
                       CHEAT_ALL_BALLOONS_ARE_YELLOW));
    }

    previousMenuItemIndex = gOptionsMenuItemIndex;

    if (yAxis < 0) {
        gOptionsMenuItemIndex++;
        if (numUnlockedCodes < gOptionsMenuItemIndex) {
            gOptionsMenuItemIndex = numUnlockedCodes;
        }
    }
    if (yAxis > 0) {
        gOptionsMenuItemIndex--;
        if (gOptionsMenuItemIndex < 0) {
            gOptionsMenuItemIndex = 0;
        }
    }

    if (gOptionsMenuItemIndex < gMenuOptionCount) {
        gMenuOptionCount = gOptionsMenuItemIndex;
    } else if (gOptionsMenuItemIndex >= (gMenuOptionCount + gNumOnscreenMagicCodes)) {
        gMenuOptionCount = (gOptionsMenuItemIndex - gNumOnscreenMagicCodes) + 1;
    }

    if (gOptionsMenuItemIndex != previousMenuItemIndex) {
        sound_play(SOUND_MENU_PICK2, NULL);
    }

    if ((buttonsPressed & (A_BUTTON | START_BUTTON)) && (numUnlockedCodes == gOptionsMenuItemIndex)) {
        delay = -1;
    }
    if (buttonsPressed & B_BUTTON) {
        delay = -1;
    }
    if (delay != 0) {
        gMenuDelay = delay;
        transition_begin(&sMenuTransitionFadeIn);
        sound_play(SOUND_MENU_BACK3, NULL);
    }
    if (gMenuDelay < -30) {
        func_8008AD1C();
        menu_init(MENU_MAGIC_CODES);
        return MENU_RESULT_CONTINUE;
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}

void func_8008AD1C(void) {
    func_8009C508(0x3F);
    unload_font(ASSET_FONTS_BIGFONT);
}

void calculate_and_display_rom_checksum(void) {
    static u32 cksum = 0;
    static u32 calculated = 0;
    s32 blockOffs;
    s32 size;
    s32 numBytes, numLeft;
    s32 i;
    u8 *tempBuffer;

    if (!calculated) {
        numBytes = 0x1000;
        size = 0x5000;
        blockOffs = 0x1000;
        numLeft = (s32) &__ROM_END;
        numLeft -= 0x1000;
        tempBuffer = allocate_from_main_pool_safe(size, COLOUR_TAG_BLACK);

        while (numLeft != 0) {
            numBytes = numLeft;
            if (numBytes > size) {
                numBytes = size;
            }
            dmacopy(blockOffs, (u32) tempBuffer, numBytes);
            numLeft -= numBytes;

            for (i = 0; i < numBytes; i++) {
                cksum += tempBuffer[i];
            }
            blockOffs += numBytes;
        }

        free_from_memory_pool(tempBuffer);
        calculated = TRUE;
    }

    set_render_printf_background_colour(0, 0, 0, 128);
    set_render_printf_position(32, 136);
    numLeft = (s32) &__ROM_END;
    render_printf(gROMChecksum, cksum, numLeft); // gROMChecksum = "ROM checksum %08X,%d\n"
}

// These vars have to be defined after calculate_and_display_rom_checksum since that function has a static var in it.

s32 D_800E1E1C = 0;

s8 D_800E1E20[8] = { 0, -1, 1, 0, 0, 1, -1, 0 };

s8 D_800E1E28 = 0;

// TT Game Status textures, think these are potentially multi-part images.
s16 D_800E1E2C[10] = { 0x4C, 0x4D, 0x4E, 0x4F, 0x5B, 0x5C, 0x00, 0x42, -1, 0 };

// TT game status textures. And these maybe just standalone ones.
s16 D_800E1E40[10] = { 0x0D, 0x0E, 0x0F, 0x10, 0x08, 0x09, 0x00, 0x0A, -1, 0 };

void func_8008AEB4(s32 arg0, s32 *arg1) {
    switch (arg0) {
        default:
            gEnteredCharSelectFrom = 0;
            return;
        case 1:
        case 3:
            gEnteredCharSelectFrom = 1;
            return;
        case 2:
            gEnteredCharSelectFrom = 2;
            unused_800DFFD4 = *arg1;
            return;
    }
}

/**
 * Sets the player who controls the menus.
 * 0 = controller 1, 1 = controller 2, 2 = controller 3, 3 = controller 4
 */
void set_active_player_index(s32 controllerIndex) {
    s32 i;

    gNumberOfActivePlayers = 1;

    for (i = 0; i < ARRAY_COUNT(gPlayersCharacterArray); i++) {
        gPlayersCharacterArray[i] = (i == controllerIndex) ? 1 : -1;
    }

    for (i = 0; i < ARRAY_COUNT(gActivePlayersArray); i++) {
        gActivePlayersArray[i] = (i == controllerIndex) ? TRUE : FALSE;
    }
}

/**
 * Initialises the character select menu. Checks which characters are available and sets the vars used for selection.
 * Sets up sound channels with the background music based on which characters are selected.
 */
void menu_character_select_init(void) {
    s32 breakTheLoop;
    s32 i;
    u8 *channelVolumes;

    breakTheLoop = FALSE;
    initialise_player_ids();
    if (is_drumstick_unlocked()) {
        if (is_tt_unlocked()) {
            gCurrCharacterSelectData = (CharacterSelectData(*)[10]) & gCharacterSelectBytesComplete;
        } else {
            gCurrCharacterSelectData = (CharacterSelectData(*)[10]) & gCharacterSelectBytesDrumStick;
        }
    } else if (is_tt_unlocked()) {
        gCurrCharacterSelectData = (CharacterSelectData(*)[10]) & gCharacterSelectBytesTT;
    } else {
        gCurrCharacterSelectData = (CharacterSelectData(*)[10]) & gCharacterSelectBytesDefault;
    }
    for (i = 0; i < ARRAY_COUNT(D_801263DC); i++) {
        D_801263DC[i] = 0;
    }
    gNumberOfReadyPlayers = 0;
    gMenuDelay = 0;
    gOptionBlinkTimer = 0;
    D_800DF484 = 0;
    for (i = 0; i < ARRAY_COUNT(gActivePlayersArray) && !breakTheLoop; i++) {
        if (gActivePlayersArray[i] != 0) {
            breakTheLoop = TRUE;
            gMenuCurrentCharacter.channelIndex = (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID;
            gMenuCurrentCharacter.unk2 = 0x7F;
            gMenuCurrentCharacter.unk1 = 1;
        }
    }
    gMenuSelectedCharacter.channelIndex = -1;
    gMenuSelectedCharacter.unk2 = 0;
    gMenuSelectedCharacter.unk1 = 0;
    D_801263B8.channelIndex = -1;
    D_801263B8.unk2 = 0;
    D_801263B8.unk1 = 0;
    music_play(SEQUENCE_CHOOSE_YOUR_RACER);
    for (i = 0; i < NUM_CHARACTERS; i++) {
        channelVolumes = gCharacterVolumes[i];
        if (i != gMenuCurrentCharacter.channelIndex) {
            music_channel_off(channelVolumes[0]);
            music_channel_off(channelVolumes[1]);
        }
    }
    music_channel_off(6);
    music_change_off();
    func_8009C674(gCharSelectObjectIndices);
    allocate_menu_images(gCharSelectImageIndices);
    transition_begin(&sMenuTransitionFadeOut);
    load_font(ASSET_FONTS_BIGFONT);
}

/**
 * Draws the "Player Select" and "OK?" text in the character select menu.
 */
void draw_character_select_text(UNUSED s32 arg0) {
    s32 yPos;
    if (gMenuDelay >= -0x16 && gMenuDelay < 0x17) {
        set_text_font(ASSET_FONTS_BIGFONT);
        set_text_background_colour(0, 0, 0, 0);
        set_text_colour(0, 0, 0, 255, 128);
        // Draw "Player Select" text drop shadow
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, gMenuText[ASSET_MENU_TEXT_PLAYERSELECT],
                  ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 255, 255, 0, 255);
        // Draw "Player Select" text
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, gMenuText[ASSET_MENU_TEXT_PLAYERSELECT],
                  ALIGN_MIDDLE_CENTER);
        if (gNumberOfReadyPlayers == gNumberOfActivePlayers && gNumberOfActivePlayers > 0) {
            yPos = 208;
            if (osTvType == TV_TYPE_PAL) {
                yPos = 234;
            }
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yPos, (char *) D_800E8230 /* "OK?" */,
                      ALIGN_MIDDLE_CENTER);
        }
        reset_render_settings(&sMenuCurrDisplayList);
        update_camera_fov(40.0f);
    }
}

void func_8008B358(void) {
    s32 i;
    s32 j;
    s32 var_a0;
    s32 var_a2;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        if (!gActivePlayersArray[i]) {
            var_a2 = -1;
            if (D_801267D8[i] & (A_BUTTON | START_BUTTON)) {
                do {
                    var_a2++;
                    var_a0 = TRUE;
                    for (j = 0; (j < ARRAY_COUNT(gActivePlayersArray)) && (var_a0); j++) {
                        if (gActivePlayersArray[j] && var_a2 == gPlayersCharacterArray[j]) {
                            var_a0 = FALSE;
                        }
                    }
                } while (!var_a0);
                gPlayersCharacterArray[i] = var_a2;
                gActivePlayersArray[i] = TRUE;
                gNumberOfActivePlayers++;
                gMenuCurrentCharacter.channelIndex = (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID;
                gMenuCurrentCharacter.unk2 = 0;
                gMenuCurrentCharacter.unk1 = 20;
                sound_play(SOUND_SELECT2, NULL);
            }
        }
    }
}

void func_8008B4C8(void) {
    s32 i;
    s32 characterSelected;
    s32 buttonsPressedAllPlayers;

    buttonsPressedAllPlayers = 0;
    for (i = 0; i < ARRAY_COUNT(gActivePlayersArray); i++) {
        if (gActivePlayersArray[i]) {
            buttonsPressedAllPlayers |= D_801267D8[i];
        }
    }

    if (buttonsPressedAllPlayers & (A_BUTTON | START_BUTTON)) {
        // Character Selected
        gMenuDelay = 1;
        mark_read_all_save_files();
        transition_begin(&sMenuTransitionFadeIn);
        characterSelected = -1;
        //!@bug: This loop condition is doing a bitwise & instead of a boolean &&
        for (i = 0; (i < MAXCONTROLLERS) & (characterSelected < 0); i++) {
            if (D_801267D8[i] & (A_BUTTON | START_BUTTON)) {
                characterSelected = i;
            }
        }
        if (D_80126808[characterSelected] != 0) {
            func_8000488C(D_80126808[characterSelected]);
        }
        sound_play(((*gCurrCharacterSelectData)[gPlayersCharacterArray[characterSelected]].voiceID +
                    SOUND_VOICE_CHARACTER_SELECTED),
                   &D_80126808[characterSelected]);
        if ((gNumberOfActivePlayers > 2) ||
            ((gNumberOfActivePlayers > 1) && !(gActiveMagicCodes & CHEAT_TWO_PLAYER_ADVENTURE)) ||
            (gEnteredCharSelectFrom == 1)) {
            music_fade(-128);
        }
    } else {
        // Character Deselected
        for (i = 0; i < ARRAY_COUNT(gActivePlayersArray); i++) {
            if (gActivePlayersArray[i] && D_801263DC[i] != 0) {
                if (D_801267D8[i] & B_BUTTON) {
                    D_801263DC[i] = 0;
                    gNumberOfReadyPlayers--;
                    if (D_80126808[i] != 0) {
                        func_8000488C(D_80126808[i]);
                    }
                    sound_play(((*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID +
                                SOUND_VOICE_CHARACTER_DESELECTED),
                               &D_80126808[i]);
                }
            }
        }
    }
}

void func_8008B758(s8 *activePlayers) {
    CharacterSelectData *charSelectData;
    s32 found;
    s32 i;
    s32 j;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        if (activePlayers[i] != 0) {
            if (D_801263DC[i] != 0) {
                if (D_801267D8[i] & B_BUTTON) {
                    D_801263DC[i] = 0;
                    gNumberOfReadyPlayers -= 1;
                    if (D_80126808[i] != 0) {
                        func_8000488C(D_80126808[i]);
                    }
                    sound_play(((*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID +
                                SOUND_VOICE_CHARACTER_DESELECTED),
                               &D_80126808[i]);
                }
            } else {
                if (D_801267D8[i] & B_BUTTON) {
                    gNumberOfActivePlayers--;
                    gActivePlayersArray[i] = 0;
                    if (gNumberOfActivePlayers > 0) {
                        if (gMenuSelectedCharacter.channelIndex ==
                            (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID) {
                            if (gMenuCurrentCharacter.unk1 <= 0) {
                                for (found = FALSE, j = 0; j < ARRAY_COUNT(gActivePlayersArray) && !found; j++) {
                                    if (gActivePlayersArray[j]) {
                                        found = TRUE;
                                        gMenuCurrentCharacter.channelIndex =
                                            (*gCurrCharacterSelectData)[gPlayersCharacterArray[j]].voiceID;
                                        gMenuCurrentCharacter.unk2 = 0;
                                        gMenuCurrentCharacter.unk1 = 20;
                                    }
                                }
                            }
                        }
                    }
                    gPlayersCharacterArray[i] = -1;
                    if (gNumberOfActivePlayers <= 0) {
                        gMenuDelay = -1;
                        transition_begin(&sMenuTransitionFadeIn);
                    }
                } else if (D_801267D8[i] & (A_BUTTON | START_BUTTON)) {
                    D_801263DC[i] = 1;
                    gNumberOfReadyPlayers++;
                    if (D_80126808[i] != 0) {
                        func_8000488C(D_80126808[i]);
                    }
                    sound_play(
                        ((*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID + SOUND_VOICE_CHARACTER_SELECT),
                        &D_80126808[i]);
                } else {
                    charSelectData = (*gCurrCharacterSelectData) + gPlayersCharacterArray[i];
                    if (D_80126830[i] > 0) {
                        func_8008BFE8(i, charSelectData->upInput, ARRAY_COUNT(charSelectData->upInput),
                                      SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    } else if (D_80126830[i] < 0) {
                        func_8008BFE8(i, charSelectData->downInput, ARRAY_COUNT(charSelectData->downInput),
                                      SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    } else if (D_80126818[i] < 0) {
                        func_8008BFE8(i, charSelectData->rightInput, ARRAY_COUNT(charSelectData->rightInput),
                                      SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    } else if (D_80126818[i] > 0) {
                        func_8008BFE8(i, charSelectData->leftInput, ARRAY_COUNT(charSelectData->leftInput),
                                      SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    }
                    if (charSelectData->voiceID != (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID) {
                        gMenuCurrentCharacter.channelIndex =
                            (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID;
                        gMenuCurrentCharacter.unk2 = 0;
                        gMenuCurrentCharacter.unk1 = 20;
                    }
                }
            }
        }
    }
}

void randomise_ai_racer_slots(s32 arg0) {
    s32 foundIt;
    s32 i, j;
    s32 numCharacters;

    numCharacters = 7;
    if (is_drumstick_unlocked()) {
        numCharacters++;
    }
    if (is_tt_unlocked()) {
        numCharacters++;
    }

    if (arg0 < 8) {
        foundIt = FALSE;
        for (i = 0; i < arg0 && !foundIt; i++) {
            if (gCharacterIdSlots[i] == 9) { // I think 9 is the character id for Diddy Kong?
                foundIt = TRUE;
            }
        }
        if (!foundIt) {
            gCharacterIdSlots[arg0] = 9;
            arg0++;
        }
    }

    for (i = arg0; i < 8; i++) {
        do {
            gCharacterIdSlots[i] = (*gCurrCharacterSelectData)[get_random_number_from_range(0, numCharacters)].voiceID;
            for (j = 0, foundIt = FALSE; j < i; j++) {
                if (gCharacterIdSlots[j] == gCharacterIdSlots[i]) {
                    foundIt = TRUE;
                }
            }
        } while (foundIt);
    }
}

s32 menu_character_select_loop(s32 updateRate) {
    s32 i;
    s32 phi_a0;
    s32 phi_t3;
    s8 activePlayers[4];
    s32 j;

    draw_character_select_text(updateRate);
    func_8008C168(updateRate);
    func_8008E4EC();

    for (i = 0; i < ARRAY_COUNT(D_801263DC); i++) {
        if (D_801263DC[i] == 1) {
            D_801263DC[i] = 2;
        }
    }
    gIgnorePlayerInputTime = 0;
    if (gMenuDelay == 0) {
        // clang-format off
        // THIS MUST BE ON ONE LINE!
        for (i = 0; i < ARRAY_COUNT(gActivePlayersArray); i++) { activePlayers[i] = gActivePlayersArray[i]; }
        // clang-format on
        func_8008B358();
        if (gNumberOfReadyPlayers == gNumberOfActivePlayers) {
            func_8008B4C8(); // Cancel/Confirm selected character?
        } else {
            func_8008B758(activePlayers); // Move and select characters?
        }
        return 0; // This return needs to be here.
    } else if (gMenuDelay > 0) {
        gMenuDelay += updateRate;
        if (gMenuDelay >= 31) {
            phi_t3 = 0;
            if (gEnteredCharSelectFrom == 0) {
                phi_t3++;
                if (gActiveMagicCodes & CHEAT_TWO_PLAYER_ADVENTURE) {
                    phi_t3++;
                }
            }
            func_8008C128();

            phi_a0 = 0;
            for (j = 0; j < ARRAY_COUNT(gActivePlayersArray); j++) {
                if (gActivePlayersArray[j]) {
                    gCharacterIdSlots[phi_a0] = (*gCurrCharacterSelectData)[gPlayersCharacterArray[j]].voiceID;
                    phi_a0++;
                }
            }

            randomise_ai_racer_slots(phi_a0);
            assign_player_ids(gActivePlayersArray);

            gIsInTracksMode = 1;
            if (phi_t3 >= gNumberOfActivePlayers) {
                music_change_off();
                load_level_for_menu(ASSET_LEVEL_OPTIONSBACKGROUND, -1, 0);
                if (gNumberOfActivePlayers == 1 && !gPlayerHasSeenCautionMenu) {
                    menu_init(MENU_CAUTION);
                } else {
                    menu_init(MENU_GAME_SELECT);
                }
            } else {
                music_change_on();
                func_800828B8();
                init_racer_headers();
                menu_init(MENU_TRACK_SELECT);
            }
        }
    } else if (gMenuDelay < 0) {
        gMenuDelay -= updateRate;
        if (gMenuDelay < -30) {
            music_change_on();
            func_8008C128();
            gNumberOfActivePlayers = 1;
            menu_init(MENU_TITLE);
        }
    }
    return MENU_RESULT_CONTINUE;
}

void func_8008BFE8(s32 arg0, s8 *arg1, s32 arg2, u16 menuPickSoundId, u16 menuPickFailedSoundId) {
    s32 sameCharSelected;
    s32 j;
    s32 i;

    j = 0;
    sameCharSelected = TRUE;
    while (sameCharSelected && j < arg2 && arg1[j] != -1) {
        sameCharSelected = FALSE;
        // Run this block if the DOUBLEVISION cheat isn't active.
        if (!(get_filtered_cheats() & CHEAT_SELECT_SAME_PLAYER)) {
            for (i = 0; i < MAXCONTROLLERS && !sameCharSelected; i++) {
                if (i != arg0 && gPlayersCharacterArray[i] == arg1[j]) {
                    sameCharSelected = TRUE;
                }
            }
            if (sameCharSelected) {
                j++;
            }
        }
    }
    if (!sameCharSelected) {
        gPlayersCharacterArray[arg0] = arg1[j];
        // menuPickSoundId seems to always be passed SOUND_MENU_PICK3?
        sound_play(menuPickSoundId, NULL);
    } else {
        // menuPickFailedSoundId seems to always be passed SOUND_HORN_DRUMSTICK?
        sound_play(menuPickFailedSoundId, NULL);
    }
}

void func_8008C128(void) {
    func_8009C4A8(gCharSelectObjectIndices);
    set_free_queue_state(0);
    unload_font(ASSET_FONTS_BIGFONT);
    set_free_queue_state(2);
    gEnteredCharSelectFrom = 0;
}

void func_8008C168(s32 updateRate) {
    if (gMenuCurrentCharacter.unk1 > 0) {
        gMenuCurrentCharacter.unk1 = gMenuCurrentCharacter.unk1 - updateRate;
        if (gMenuCurrentCharacter.unk1 <= 0) {
            if (D_801263B8.channelIndex >= 0) {
                music_channel_off(gCharacterVolumes[D_801263B8.channelIndex][0]);
                music_channel_off(gCharacterVolumes[0][D_801263B8.channelIndex * 2 + 1]);
            }
            D_801263B8.channelIndex = gMenuSelectedCharacter.channelIndex;
            if (gMenuSelectedCharacter.channelIndex >= 0) {
                D_801263B8.unk2 = gMenuSelectedCharacter.unk2;
            }
            gMenuSelectedCharacter.channelIndex = gMenuCurrentCharacter.channelIndex;
            if (gMenuSelectedCharacter.channelIndex >= 0) {
                gMenuSelectedCharacter.unk2 = gMenuCurrentCharacter.unk2;
                music_channel_on(gCharacterVolumes[gMenuSelectedCharacter.channelIndex][0]);
                music_channel_on(gCharacterVolumes[0][gMenuSelectedCharacter.channelIndex * 2 + 1]);
            }
        }
    }
    if (gMenuSelectedCharacter.channelIndex >= 0) {
        gMenuSelectedCharacter.unk2 += updateRate * 4;
        if (gMenuSelectedCharacter.unk2 > 127) {
            gMenuSelectedCharacter.unk2 = 127;
        }
        music_channel_fade_set(gCharacterVolumes[gMenuSelectedCharacter.channelIndex][0], gMenuSelectedCharacter.unk2);
        music_channel_fade_set(gCharacterVolumes[0][gMenuSelectedCharacter.channelIndex * 2 + 1],
                               gMenuSelectedCharacter.unk3);
    }
    if (D_801263B8.channelIndex >= 0) {
        D_801263B8.unk2 -= updateRate * 4;
        if (D_801263B8.channelIndex != gMenuSelectedCharacter.channelIndex) {
            if (D_801263B8.unk2 < 0) {
                music_channel_off(gCharacterVolumes[D_801263B8.channelIndex][0]);
                music_channel_off(gCharacterVolumes[0][D_801263B8.channelIndex * 2 + 1]);
            } else {
                music_channel_fade_set(gCharacterVolumes[D_801263B8.channelIndex][0], D_801263B8.unk2);
                music_channel_fade_set(gCharacterVolumes[0][D_801263B8.channelIndex * 2 + 1], D_801263B8.unk3);
            }
        }
        if (D_801263B8.unk2 < 0) {
            D_801263B8.channelIndex = -1;
        }
    }
}

/**
 * Initialises the timer and transition for the controller pak warning screen.
 * Only seen once per game session, as set by gPlayerHasSeenCautionMenu.
 */
void menu_caution_init(void) {
    gIgnorePlayerInputTime = 60;
    gMenuDelay = 0;
    load_font(ASSET_FONTS_BIGFONT);
    transition_begin(&sMenuTransitionFadeOut);
    gPlayerHasSeenCautionMenu = 1;
}

/**
 * Loops through the display of the caution screen.
 * Blocks player input for one second.
 */
s32 menu_caution_loop(s32 updateRate) {
    if (gMenuDelay) {
        gMenuDelay += updateRate;
    } else if (gIgnorePlayerInputTime <= 0 &&
               (get_buttons_pressed_from_player(PLAYER_ONE) & (A_BUTTON | B_BUTTON | START_BUTTON))) {
        sound_play(SOUND_SELECT2, NULL);
        gMenuDelay = 1;
        transition_begin(&sMenuTransitionFadeIn);
    }
    if (gMenuDelay < 20) {
        draw_menu_elements(1, gCautionMenuTextElements, 1.0f);
    }
    if (gMenuDelay > 30) {
        unload_big_font_3();
        menu_init(MENU_GAME_SELECT);
    }
    if (gIgnorePlayerInputTime > 0) {
        gIgnorePlayerInputTime -= updateRate;
    }
    return MENU_RESULT_CONTINUE;
}

/**
 * Explicitly says to unload the ASSET_FONTS_BIGFONT type.
 */
void unload_big_font_3(void) {
    unload_font(ASSET_FONTS_BIGFONT);
}

/**
 * Initialises the selection menu that contains the options for adventure one, two and tracks mode.
 * Loads all save file data to determine whether to show adventure two.
 */
void menu_game_select_init(void) {
    s32 i;

    gMenuDelay = 0;
    gOptionBlinkTimer = 0;
    gMenuCurIndex = 0;
    gMenuOptionCount = 2;
    transition_begin(&sMenuTransitionFadeOut);
    mark_read_all_save_files();
    set_ghost_none();
    gOpacityDecayTimer = 1;
    func_8009C6D4(0x43);
    func_8007FFEC(3);
    load_font(ASSET_FONTS_BIGFONT);
    music_play(SEQUENCE_CHOOSE_YOUR_RACER);

    for (i = 0; i < NUM_CHARACTERS; i++) {
        if (i != gMenuSelectedCharacter.channelIndex) {
            music_channel_off(gCharacterVolumes[i][0]);
            music_channel_off(gCharacterVolumes[i][1]);
        }
    }

    music_channel_off(6);
    music_change_off();
    if (is_adventure_two_unlocked()) {
        gGameSelectElements = gGameSelectTextElemsWithAdv2;
        gMenuOptionCount = 2;
    } else {
        gGameSelectElements = gGameSelectTextElemsNoAdv2;
        gMenuOptionCount = 1;
    }

    for (i = 0; i <= gMenuOptionCount; i++) {
        // Fakematch? What's the (i ^ 0)?
        gGameSelectElements[((i ^ 0) * 2) + 2].unk14_a.texture = gMenuObjects[TEXTURE_SURFACE_BUTTON_WOOD];
    }
}

void func_8008C698(UNUSED s32 updateRate) {
    s32 i;
    s32 filterBlendFactor;
    s32 fade;

    if (gMenuDelay >= -21 && gMenuDelay < 22) {
        fade = gOptionBlinkTimer * 8;
        fade = fade;
        if (fade >= 0x100) {
            fade = 0x1FF - fade;
        }
        set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);

        for (i = 0; i <= gMenuOptionCount; i++) {
            filterBlendFactor = 0;
            if (i == gMenuCurIndex) {
                filterBlendFactor = fade;
            }
            // Fakematch? What's the (i ^ 0)?
            gGameSelectElements[((i ^ 0) * 2) + 3].filterBlendFactor = filterBlendFactor;
        }

        if (osTvType == TV_TYPE_PAL) {
            gDrawElementsRegionYOffset = 12;
            gDrawElementsYOffset = 0;
        } else {
            gDrawElementsRegionYOffset = 0;
            gDrawElementsYOffset = 0;
        }

        draw_menu_elements(1, gGameSelectElements, 1.0f);
        func_80080BC8(&sMenuCurrDisplayList);
    }
}

s32 menu_game_select_loop(s32 updateRate) {
    s32 playerInputs;
    s32 playerYDir;
    s32 charSelectScene;

    func_8008C168(updateRate);

    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;

    if (gOpacityDecayTimer) {
        gOpacityDecayTimer++;
        if (gOpacityDecayTimer >= 3) {
            func_800828B8();
            gOpacityDecayTimer = 0;
        }
    }
    if (gMenuDelay != 0) {
        if (gMenuDelay < 0) {
            gMenuDelay -= updateRate;
        } else {
            gMenuDelay += updateRate;
        }
    }
    if (gMenuDelay > 30) {
        func_8008CACC();
        if (gMenuCurIndex == gMenuOptionCount) {
            music_change_on();
            gIsInTracksMode = TRUE;
            init_racer_headers();
            load_level_for_menu((s32) SPECIAL_MAP_ID_NO_LEVEL, -1, 0);
            menu_init(MENU_TRACK_SELECT);
        } else {
            gIsInAdventureTwo = gMenuCurIndex;
            gIsInTracksMode = FALSE;
            gPlayerSelectVehicle[PLAYER_ONE] = VEHICLE_CAR;
            set_level_default_vehicle(VEHICLE_CAR);
            menu_init(MENU_FILE_SELECT);
        }
        return MENU_RESULT_CONTINUE;
    } else if (gMenuDelay < -30) {
        func_8008CACC();
        charSelectScene = 0;
        if (is_drumstick_unlocked()) {
            charSelectScene = 1;
        }
        if (is_tt_unlocked()) {
            charSelectScene ^= 3;
        }
        load_level_for_menu(ASSET_LEVEL_CHARACTERSELECT, -1, charSelectScene);
        func_8008AEB4(0, 0);
        menu_init(MENU_CHARACTER_SELECT);
        return MENU_RESULT_CONTINUE;
    } else {
        func_8008C698(updateRate);
        if ((gMenuDelay == 0) && (gOpacityDecayTimer == 0)) {
            playerInputs = get_buttons_pressed_from_player(PLAYER_ONE);
            playerYDir = gControllersYAxisDirection[0];
            playerInputs = playerInputs;
            if (gNumberOfActivePlayers == 2) {
                playerInputs |= get_buttons_pressed_from_player(1);
                playerYDir += gControllersYAxisDirection[1];
            }
            if (playerInputs & (A_BUTTON | START_BUTTON)) {
                if (gMenuCurIndex == gMenuOptionCount) {
                    music_fade(-0x80);
                }
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = 1;
                sound_play(SOUND_SELECT2, NULL);
            } else if (playerInputs & B_BUTTON) {
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = -1;
            } else {
                if (playerYDir < 0) {
                    if (gMenuCurIndex < gMenuOptionCount) {
                        gMenuCurIndex++;
                        sound_play(SOUND_MENU_PICK2, NULL);
                    }
                }
                if (playerYDir > 0) {
                    if (gMenuCurIndex > 0) {
                        gMenuCurIndex--;
                        sound_play(SOUND_MENU_PICK2, NULL);
                    }
                }
            }
        }
        gIgnorePlayerInputTime = 0;
        return MENU_RESULT_CONTINUE;
    }
}

void func_8008CACC(void) {
    unload_font(ASSET_FONTS_BIGFONT);
    func_8007FF88();
    func_8009C508(0x43);
}

/**
 * Initialises the file selection menu. Loads the relevant textures for the menu.
 * Sets the audio channels to match the selected character.
 */
void menu_file_select_init(void) {
    s32 i;
    UNUSED s32 numLevels;
    UNUSED s32 numWorlds;

    get_number_of_levels_and_worlds(&numLevels, &numWorlds); // Unused
    func_8009C674(gFileSelectObjectIndices);
    allocate_menu_images(gFileSelectImageIndices);
    func_8007FFEC(6);
    mark_read_all_save_files();
    gOpacityDecayTimer = 1;
    gSaveFileIndex = 0;
    gMenuDelay = 0;
    gMenuOptionCount = 0;
    gOptionBlinkTimer = 0;
    D_80126484 = FALSE;
    D_80126488 = FALSE;
    D_80126CC0 = FALSE;
    transition_begin(&sMenuTransitionFadeOut);
    load_font(ASSET_FONTS_BIGFONT);
    music_play(SEQUENCE_CHOOSE_YOUR_RACER);
    for (i = 0; i < NUM_CHARACTERS; i++) {
        if (i != gMenuSelectedCharacter.channelIndex) {
            music_channel_off(gCharacterVolumes[i][0]);
            music_channel_off(gCharacterVolumes[i][1]);
        }
    }
    music_channel_off(6);
    music_change_off();
}

/**
 * Sets the colour properties of the selected image index in the menu texture stack, then renders it on screen.
 * Rendering it twice using different colour settings, it casts a shadow.
 */
void render_menu_image(s32 imageID, s32 xOffset, s32 yOffset, s32 red, s32 green, s32 blue, s32 opacity) {
    s32 tempRed = sMenuGuiColourR;
    s32 tempGreen = sMenuGuiColourG;
    s32 tempBlue = sMenuGuiColourB;
    s32 tempOpacity = sMenuGuiOpacity;
    // This first section is the shadow
    sMenuGuiColourR = red;
    sMenuGuiColourG = green;
    sMenuGuiColourB = blue;
    sMenuGuiOpacity = opacity;
    gMenuImageStack[imageID].unkC = xOffset - 159;
    gMenuImageStack[imageID].unk10 = 119 - yOffset;
    func_8009CA60(imageID);
    // And this then draws it again, with colour
    sMenuGuiColourR = tempRed;
    sMenuGuiColourG = tempGreen;
    sMenuGuiColourB = tempBlue;
    sMenuGuiOpacity = tempOpacity;
    gMenuImageStack[imageID].unkC = xOffset - 161;
    gMenuImageStack[imageID].unk10 = 121 - yOffset;
    func_8009CA60(imageID);
}

void render_file_select_menu(UNUSED s32 updateRate) {
    s32 yPos;
    s32 var_s2;
    s32 temp;
    u32 colour;
    s32 i;
    UNUSED s32 pad[3];
    char trimmedFilename[4];

    if (osTvType == TV_TYPE_PAL) {
        yPos = 12;
    } else {
        yPos = 0;
    }

    func_8009BD5C();
    set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    for (i = 0; i < NUMBER_OF_SAVE_FILES; i++) {
        if (gSavefileInfo[i].isAdventure2 == gIsInAdventureTwo || gSavefileInfo[i].isStarted == 0) {
            colour = COLOUR_RGBA32(176, 224, 192, 255);
        } else {
            colour = COLOUR_RGBA32(106, 144, 115, 255);
        }
        func_80080580(NULL, gFileSelectButtons[i].x - SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF - gFileSelectButtons[i].y,
                      gFileSelectButtons[i].width, gFileSelectButtons[i].height, gFileSelectButtons[i].borderWidth,
                      gFileSelectButtons[i].borderHeight, colour, gMenuObjects[TEXTURE_SURFACE_BUTTON_WOOD]);
    }
    func_80080BC8(&sMenuCurrDisplayList);
    if (gOpacityDecayTimer == 0) {
        set_text_font(ASSET_FONTS_BIGFONT);
        set_text_background_colour(0, 0, 0, 0);
        for (i = 0; i < NUMBER_OF_SAVE_FILES; i++) {
            if (gSavefileInfo[i].isStarted) {
                sprite_opaque(FALSE);
                var_s2 = 11;
                if (gSavefileInfo[i].isAdventure2) {
                    var_s2 = 12;
                }
                render_menu_image(var_s2, gFileSelectButtons[i].x + gFileSelectElementPos[2],
                                  gFileSelectButtons[i].y + gFileSelectElementPos[3], 0, 0, 0, 128);
                func_80068508(TRUE);
                gMenuImageStack->unk18 = gSavefileInfo[i].balloonCount / 10;
                render_menu_image(0, gFileSelectButtons[i].x + gFileSelectElementPos[6] - 6,
                                  gFileSelectButtons[i].y + gFileSelectElementPos[7], 0, 0, 0, 128);
                gMenuImageStack->unk18 = gSavefileInfo[i].balloonCount % 10;
                render_menu_image(0, gFileSelectButtons[i].x + gFileSelectElementPos[6] + 6,
                                  gFileSelectButtons[i].y + gFileSelectElementPos[7], 0, 0, 0, 128);
                func_80068508(FALSE);
                sMenuGuiColourG = 64;
                sMenuGuiColourB = 64;
                render_menu_image(10, gFileSelectButtons[i].x + gFileSelectElementPos[8],
                                  gFileSelectButtons[i].y + gFileSelectElementPos[9], 0, 0, 0, 128);
                sMenuGuiColourG = 255;
                sMenuGuiColourB = 255;
                sprite_opaque(TRUE);
            } else {
                set_text_colour(255, 255, 255, 64, 255);
                draw_text(&sMenuCurrDisplayList, gFileSelectButtons[i].x + gFileSelectElementPos[4],
                          gFileSelectButtons[i].y + gFileSelectElementPos[5] + yPos, gMenuText[ASSET_MENU_TEXT_NEW],
                          ALIGN_MIDDLE_CENTER);
            }
        }
    }
    temp = gOptionBlinkTimer * 8;
    if (temp >= 256) {
        temp = 511 - temp;
    }
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_background_colour(0, 0, 0, 0);
    set_text_colour(255, 255, 255, 0, 255);
    for (i = 0; i < NUMBER_OF_SAVE_FILES; i++) {
        var_s2 = FALSE;
        if (D_80126484 != FALSE) {
            if (D_80126494 == 0 && i == gSaveFileIndex3) {
                var_s2 = TRUE;
            } else if (D_80126494 > 0 && i == gSaveFileIndex2) {
                var_s2 = TRUE;
            }
        } else if (D_80126488 != FALSE) {
            if (i == gSaveFileIndex3) {
                var_s2 = TRUE;
            }
        } else if (gMenuOptionCount == 0 && i == gSaveFileIndex) {
            var_s2 = TRUE;
        }
        if (var_s2) {
            colour = temp | ~0xFF;
            func_80080E90(&sMenuCurrDisplayList, gFileSelectButtons[i].x, gFileSelectButtons[i].y + yPos,
                          gFileSelectButtons[i].width, gFileSelectButtons[i].height, gFileSelectButtons[i].borderWidth,
                          gFileSelectButtons[i].borderHeight, colour, colour, colour, colour);
        }
        if (!D_80126CC0 || i != gSaveFileIndex) {
            trim_filename_string(gSavefileInfo[i].name, trimmedFilename);
            if (!gSavefileInfo[i].isStarted) {
                trim_filename_string(gFilenames[i], trimmedFilename);
            }
            if (trimmedFilename) {
                draw_text(&sMenuCurrDisplayList, gFileSelectButtons[i].x + gFileSelectElementPos[0],
                          gFileSelectButtons[i].y + gFileSelectElementPos[1] + yPos, trimmedFilename,
                          ALIGN_MIDDLE_CENTER);
            }
        }
    }
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 19, gMenuText[ASSET_MENU_TEXT_GAMESELECT],
              ALIGN_TOP_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 16, gMenuText[ASSET_MENU_TEXT_GAMESELECT], ALIGN_TOP_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    yPos += 187;
    if (D_80126484) {
        if (D_80126494 == 0) {
            set_text_font(ASSET_FONTS_FUNFONT);
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yPos, gMenuText[ASSET_MENU_TEXT_GAMETOCOPY],
                      ALIGN_MIDDLE_CENTER);
        } else if (D_80126494 == 1) {
            set_text_font(ASSET_FONTS_FUNFONT);
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yPos, gMenuText[ASSET_MENU_TEXT_GAMETOCOPYTO],
                      ALIGN_MIDDLE_CENTER);
        } else {
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yPos, (char *) &D_800E8234 /* "OK?" */,
                      ALIGN_MIDDLE_CENTER);
        }
    } else if (D_80126488) {
        if (D_80126494 == 0) {
            set_text_font(ASSET_FONTS_FUNFONT);
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yPos, gMenuText[ASSET_MENU_TEXT_GAMETOERASE],
                      ALIGN_MIDDLE_CENTER);
        } else {
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yPos, (char *) &D_800E8238 /* "OK?" */,
                      ALIGN_MIDDLE_CENTER);
        }
    } else if (!D_80126CC0) {
        if (gMenuOptionCount == 1) {
            set_text_colour(255, 255, 255, temp, 255);
        }
        draw_text(&sMenuCurrDisplayList, 90, yPos, gMenuText[ASSET_MENU_TEXT_COPY], ALIGN_MIDDLE_CENTER);
        if (gMenuOptionCount == 2) {
            set_text_colour(255, 255, 255, temp, 255);
        } else {
            set_text_colour(255, 255, 255, 0, 255);
        }
        draw_text(&sMenuCurrDisplayList, 230, yPos, gMenuText[ASSET_MENU_TEXT_ERASE], ALIGN_MIDDLE_CENTER);
    }
}

s32 func_8008D5F8(UNUSED s32 updateRate) {
    u32 buttonsPressed;
    s32 xAxisDirection;
    s32 yAxisDirection;
    s32 temp_a0;
    u32 buttonsPressedPlayer2;

    buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE);
    xAxisDirection = gControllersXAxisDirection[PLAYER_ONE];
    yAxisDirection = gControllersYAxisDirection[PLAYER_ONE];
    if (gNumberOfActivePlayers == 2) {
        buttonsPressedPlayer2 = get_buttons_pressed_from_player(PLAYER_TWO);
        buttonsPressed |= buttonsPressedPlayer2;
        xAxisDirection += gControllersXAxisDirection[PLAYER_TWO];
        yAxisDirection += gControllersYAxisDirection[PLAYER_TWO];
    }
    if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        switch (gMenuOptionCount) {
            case 0:
                if (gSavefileInfo[gSaveFileIndex].isStarted) {
                    if (gIsInAdventureTwo != gSavefileInfo[gSaveFileIndex].isAdventure2) {
                        sound_play(SOUND_HORN_DRUMSTICK, NULL);
                        break;
                    }
                }
                sound_play(SOUND_SELECT2, NULL);
                return 1;
            case 1:
                sound_play(SOUND_SELECT2, NULL);
                gSaveFileIndex3 = gSaveFileIndex;
                D_80126484 = TRUE;
                D_80126494 = 0;
                return 0;
            case 2:
                sound_play(SOUND_SELECT2, NULL);
                gSaveFileIndex3 = gSaveFileIndex;
                D_80126488 = TRUE;
                D_80126494 = 0;
                return 0;
        }
    } else if (buttonsPressed & CONT_B) {
        return -1;
    }

    temp_a0 = (gMenuOptionCount << 8) | gSaveFileIndex;
    if (gMenuOptionCount == 0) {
        // Left
        if ((xAxisDirection < 0) && (gSaveFileIndex > 0)) {
            gSaveFileIndex--;
        }
        // Right
        if ((xAxisDirection > 0) && (gSaveFileIndex < 2)) {
            gSaveFileIndex++;
        }
        // Down
        if (yAxisDirection < 0) {
            if (gSaveFileIndex >= 2) {
                gMenuOptionCount = 2;
            } else {
                gMenuOptionCount = 1;
            }
        }
    } else {
        // Left
        if ((xAxisDirection < 0) && (gMenuOptionCount == 2)) {
            gMenuOptionCount = 1;
        }
        // Right
        if ((xAxisDirection > 0) && (gMenuOptionCount == 1)) {
            gMenuOptionCount = 2;
        }
        // Up
        if (yAxisDirection > 0) {
            if ((gMenuOptionCount == 1) && (gSaveFileIndex >= 2)) {
                gSaveFileIndex = 0;
            }
            if ((gMenuOptionCount == 2) && (gSaveFileIndex <= 0)) {
                gSaveFileIndex = 2;
            }
            gMenuOptionCount = 0;
        }
    }
    if (temp_a0 != ((gMenuOptionCount << 8) | gSaveFileIndex)) {
        sound_play(SOUND_MENU_PICK2, NULL);
    }
    return 0;
}

void func_8008D8BC(UNUSED s32 updateRate) {
    s32 prevValue;
    u32 buttonsPressed;
    s32 xAxisDirection;
    s32 i;
    Settings *settings;
    u32 buttonsPressedPlayerTwo;

    settings = get_settings();
    buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE);
    xAxisDirection = gControllersXAxisDirection[PLAYER_ONE];
    if (gNumberOfActivePlayers == 2) {
        buttonsPressedPlayerTwo = get_buttons_pressed_from_player(PLAYER_TWO);
        buttonsPressed |= buttonsPressedPlayerTwo;
        xAxisDirection += gControllersXAxisDirection[PLAYER_TWO];
    }
    if (D_80126494 == 0) {
        if (buttonsPressed & (B_BUTTON)) {
            sound_play(SOUND_MENU_BACK3, NULL);
            D_80126484 = FALSE;
            return;
        }
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            if (gSavefileInfo[gSaveFileIndex3].isStarted) {
                sound_play(SOUND_SELECT2, NULL);
                mark_read_save_file(gSaveFileIndex3);
                gSaveFileIndex2 = gSaveFileIndex3;
                D_80126494 = 1;
                return;
            }
            sound_play(SOUND_MENU_BACK3, NULL);
            return;
        }
        prevValue = gSaveFileIndex3;
        if ((xAxisDirection < 0) && (gSaveFileIndex3 > 0)) {
            gSaveFileIndex3--;
        }
        if ((xAxisDirection > 0) && (gSaveFileIndex3 < 2)) {
            gSaveFileIndex3++;
        }
        if (prevValue != gSaveFileIndex3) {
            sound_play(SOUND_MENU_PICK2, NULL);
        }
    } else if (D_80126494 == 1) {
        if (buttonsPressed & B_BUTTON) {
            sound_play(SOUND_MENU_BACK3, NULL);
            gSaveFileIndex3 = gSaveFileIndex2;
            D_80126494 = 0;
            return;
        }
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            if (!gSavefileInfo[gSaveFileIndex2].isStarted) {
                sound_play(SOUND_SELECT2, NULL);
                D_80126494 = 2;
                return;
            }
            sound_play(SOUND_MENU_BACK3, NULL);
            return;
        }
        prevValue = gSaveFileIndex2;
        if (xAxisDirection < 0 && gSaveFileIndex2 > 0) {
            gSaveFileIndex2--;
        }
        if (xAxisDirection > 0 && gSaveFileIndex2 < 2) {
            gSaveFileIndex2++;
        }
        if (prevValue != gSaveFileIndex2) {
            sound_play(SOUND_MENU_PICK2, NULL);
        }
    } else {
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            sound_play(SOUND_SELECT2, NULL);
            force_mark_write_save_file(gSaveFileIndex2);
            gSavefileInfo[gSaveFileIndex2].isAdventure2 = FALSE;
            gSavefileInfo[gSaveFileIndex2].isStarted = TRUE;
            gSavefileInfo[gSaveFileIndex2].balloonCount = *settings->balloonsPtr;
            if (settings->cutsceneFlags & CUTSCENE_ADVENTURE_TWO) {
                gSavefileInfo[gSaveFileIndex2].isAdventure2 = TRUE;
            }
            for (i = 0; gSavefileInfo[gSaveFileIndex3].name[i] != '\0'; i++) {
                gSavefileInfo[gSaveFileIndex2].name[i] = gSavefileInfo[gSaveFileIndex3].name[i];
            }
            gSavefileInfo[gSaveFileIndex2].name[i] = '\0';
            gSaveFileIndex = gSaveFileIndex2;
            gMenuOptionCount = 0;
            D_80126484 = FALSE;
        } else if (buttonsPressed & B_BUTTON) {
            sound_play(SOUND_MENU_BACK3, NULL);
            D_80126494 = 1;
        }
    }
}

void func_8008DC7C(UNUSED s32 updateRate) {
    s32 buttonsPressed;
    s32 controllerXAxisDirection;
    s32 temp;

    buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE);
    controllerXAxisDirection = gControllersXAxisDirection[0];

    if (gNumberOfActivePlayers == 2) {
        buttonsPressed |= get_buttons_pressed_from_player(PLAYER_TWO);
        controllerXAxisDirection += gControllersXAxisDirection[1];
    }

    if (D_80126494 == 0) {
        if (buttonsPressed & B_BUTTON) {
            sound_play(SOUND_MENU_BACK3, NULL);
            D_80126488 = FALSE;
            return;
        } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            if (gSavefileInfo[gSaveFileIndex3].isStarted != 0) {
                sound_play(SOUND_SELECT2, NULL);
                D_80126494 = 1;
                return;
            }
            sound_play(SOUND_MENU_BACK3, NULL);
            return;
        }

        temp = gSaveFileIndex3;

        // Left
        if (controllerXAxisDirection < 0) {
            if (gSaveFileIndex3 > 0) {
                gSaveFileIndex3--;
            }
        }

        // Right
        if (controllerXAxisDirection > 0) {
            if (gSaveFileIndex3 < 2) {
                gSaveFileIndex3++;
            }
        }

        if (gSaveFileIndex3 != temp) {
            sound_play(SOUND_MENU_PICK2, NULL);
        }
    } else {
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            sound_play(SOUND_SELECT2, NULL);
            mark_save_file_to_erase(gSaveFileIndex3);
            gSavefileInfo[gSaveFileIndex3].isAdventure2 = 0;
            gSavefileInfo[gSaveFileIndex3].isStarted = 0;
            gSavefileInfo[gSaveFileIndex3].balloonCount = 0;
            gSavefileInfo[gSaveFileIndex3].name[0] = 'D';
            gSavefileInfo[gSaveFileIndex3].name[1] = 'K';
            gSavefileInfo[gSaveFileIndex3].name[2] = 'R';
            gSavefileInfo[gSaveFileIndex3].name[3] = '\0';
            gSaveFileIndex = gSaveFileIndex3;
            gMenuOptionCount = 0;
            D_80126488 = FALSE;
        } else if (buttonsPressed & B_BUTTON) {
            sound_play(SOUND_MENU_BACK3, NULL);
            D_80126494 = 0;
        }
    }
}

s32 menu_file_select_loop(s32 updateRate) {
    s32 i;
    s32 currentMenuDelay;
    u32 buttonsPressed;
    Settings *settings;

    settings = get_settings();
    func_8008C168(updateRate);
    if (gOpacityDecayTimer) {
        gOpacityDecayTimer++;

        if (gOpacityDecayTimer >= 3) {
            for (i = 0; i < NUMBER_OF_SAVE_FILES; i++) {
                gSavefileInfo[i].isAdventure2 = 0;
                if (gSavefileData[i]->newGame) {
                    gSavefileInfo[i].isStarted = 0;
                    gSavefileInfo[i].balloonCount = 0;
                    gSavefileInfo[i].name[0] = 'D';
                    gSavefileInfo[i].name[1] = 'K';
                    gSavefileInfo[i].name[2] = 'R';
                    gSavefileInfo[i].name[3] = '\0';
                } else {
                    if (gSavefileData[i]->cutsceneFlags & CUTSCENE_ADVENTURE_TWO) {
                        gSavefileInfo[i].isAdventure2 = TRUE;
                    }
                    gSavefileInfo[i].isStarted = TRUE;
                    gSavefileInfo[i].balloonCount = *gSavefileData[i]->balloonsPtr;
                    decompress_filename_string(gSavefileData[i]->filename, gSavefileInfo[i].name, 3);
                }
            }
            gOpacityDecayTimer = 0;
        }
    }
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3f;
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }
    if ((gMenuDelay >= -20) && (gMenuDelay <= 20)) {
        render_file_select_menu(updateRate);
    }
    if ((gMenuDelay == 0) && (gOpacityDecayTimer == 0)) {
        if (D_80126484 != FALSE) {
            func_8008D8BC(updateRate);
        } else if (D_80126488 != FALSE) {
            func_8008DC7C(updateRate);
        } else if (D_80126CC0) {
            buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE);
            if ((buttonsPressed & B_BUTTON) && (gCurrentFilenameChars == 0)) {
                unload_big_font_4();
                D_80126CC0 = FALSE;
                gSavefileInfo[i].name[0] = 'D';
                gSavefileInfo[i].name[1] = 'K';
                gSavefileInfo[i].name[2] = 'R';
                gSavefileInfo[i].name[3] = '\0';
            } else if (menu_enter_filename_loop(updateRate) != 0) {
                unload_big_font_4();
                D_80126CC0 = FALSE;
                gSavefileInfo[gSaveFileIndex].isAdventure2 = 0;
                if (gIsInAdventureTwo != 0) {
                    gSavefileInfo[gSaveFileIndex].isAdventure2 = 1;
                }
                gSavefileInfo[gSaveFileIndex].isStarted = 1;
                gSavefileInfo[gSaveFileIndex].balloonCount = 0;
                settings->filename = compress_filename_string(gSavefileInfo[gSaveFileIndex].name, 3);
                mark_read_save_file(gSaveFileIndex);
                music_fade(-128);
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = 1;
            }
        } else {
            currentMenuDelay = func_8008D5F8(updateRate);
            if (currentMenuDelay != 0) {
                if (currentMenuDelay > 0) {
                    if (gSavefileInfo[gSaveFileIndex].isStarted != 0) {
                        sound_play(SOUND_SELECT2, NULL);
                        mark_read_save_file(gSaveFileIndex);
                        music_fade(-128);
                    } else {
                        D_80126CC0 = TRUE;
                        gIndexOfCurInputCharacter = 0;
                        i = 0;
                        if (osTvType == TV_TYPE_PAL) {
                            i = 12;
                        }
                        func_80097874(i + 187, gFileSelectButtons[gSaveFileIndex].x + gFileSelectElementPos[0],
                                      gFileSelectButtons[gSaveFileIndex].y + gFileSelectElementPos[1] + i, 0,
                                      &gIndexOfCurInputCharacter, gSavefileInfo[gSaveFileIndex].name, 3);
                        currentMenuDelay = 0;
                    }
                }
                if (currentMenuDelay != 0) {
                    transition_begin(&sMenuTransitionFadeIn);
                    gMenuDelay = currentMenuDelay;
                }
            }
        }
    }
    if (gMenuDelay > 35) {
        if (gActiveMagicCodes & CHEAT_FREE_BALLOON) {
            gActiveMagicCodes &= ~CHEAT_FREE_BALLOON;
            gUnlockedMagicCodes &= ~CHEAT_FREE_BALLOON;
            (*settings->balloonsPtr)++;
        }
        gIsInTwoPlayerAdventure = (gNumberOfActivePlayers == 2);
        if (gIsInTwoPlayerAdventure) {
            fontUseFont();
        }
        gNumberOfActivePlayers = 1;
        D_800E0FAC = 1;
        func_8008E428();
        music_change_on();
        init_racer_headers();
        gTrophyRaceWorldId = 0;
        if (settings->newGame) {
            if (gIsInAdventureTwo) {
                settings->cutsceneFlags |= CUTSCENE_ADVENTURE_TWO;
            }
            func_8009ABD8((s8 *) get_misc_asset(ASSET_MISC_25), 0, gNumberOfActivePlayers, 0, 0, NULL);
            menu_init(MENU_NEWGAME_CINEMATIC);
            return MENU_RESULT_CONTINUE;
        }
        if (settings->cutsceneFlags & CUTSCENE_ADVENTURE_TWO) {
            gIsInAdventureTwo = TRUE;
        } else {
            gIsInAdventureTwo = FALSE;
        }
        return gNumberOfActivePlayers;
    }
    if (gMenuDelay < -35) {
        func_8008E428();
        menu_init(MENU_GAME_SELECT);
        return MENU_RESULT_CONTINUE;
    } else {
        return MENU_RESULT_CONTINUE;
    }
}

void func_8008E428(void) {
    func_8009C4A8(gFileSelectObjectIndices);
    func_8007FF88();
    unload_font(ASSET_FONTS_BIGFONT);
}

/**
 * Set the texture IDs of the vehicle ID elements.
 */
void assign_vehicle_icon_textures(void) {
    gRaceSelectionCarTex[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_CAR_TOP];
    gRaceSelectionCarTex[1].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_CAR_BOTTOM];
    gRaceSelectionHoverTex[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_HOVERCRAFT_TOP];
    gRaceSelectionHoverTex[1].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_HOVERCRAFT_BOTTOM];
    gRaceSelectionPlaneTex[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_PLANE_TOP];
    gRaceSelectionPlaneTex[1].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_PLANE_BOTTOM];
}

/**
 * Set the texture IDs of the menu arrow elements.
 */
void assign_menu_arrow_textures(void) {
    gMenuSelectionArrowUp[0].texture = gMenuObjects[TEXTURE_ICON_ARROW_UP];
    gMenuSelectionArrowLeft[0].texture = gMenuObjects[TEXTURE_ICON_ARROW_LEFT];
    gMenuSelectionArrowDown[0].texture = gMenuObjects[TEXTURE_ICON_ARROW_DOWN];
    gMenuSelectionArrowRight[0].texture = gMenuObjects[TEXTURE_ICON_ARROW_RIGHT];
}

void func_8008E4EC(void) {
    s32 i;
    s32 buttonsPressed[ARRAY_COUNT(D_80126818)];

    if (gIgnorePlayerInputTime == 0) {
        for (i = 0; i < ARRAY_COUNT(D_80126818); i++) {
            buttonsPressed[i] = 0;
            D_80126818[i] = 0;
            D_80126830[i] = 0;
        }
        for (i = 0; i < MAXCONTROLLERS; i++) {
            buttonsPressed[i] = get_buttons_held_from_player(i);
            D_80126818[i] = gControllersXAxisDirection[i];
            D_80126830[i] = gControllersYAxisDirection[i];
            if (i < gNumberOfActivePlayers) {
                buttonsPressed[ARRAY_COUNT(D_80126818) - 1] |= buttonsPressed[i];
                D_80126818[ARRAY_COUNT(D_80126818) - 1] += gControllersXAxisDirection[i];
                D_80126830[ARRAY_COUNT(D_80126818) - 1] += gControllersYAxisDirection[i];
            }
        }
        for (i = 0; i < ARRAY_COUNT(D_80126818); i++) {
            D_801267D8[i] = buttonsPressed[i] & ~D_801267F0[i];
            D_801267F0[i] = buttonsPressed[i];
        }
        return;
    }
    for (i = 0; i < ARRAY_COUNT(D_80126818); i++) {
        D_801267F0[i] = (START_BUTTON | B_BUTTON | A_BUTTON);
        D_801267D8[i] = 0;
        D_80126818[i] = 0;
        D_80126830[i] = 0;
    }
}

UNUSED s32 func_8008E790(void) {
    return gIsInTracksMenu;
}

#ifdef NON_EQUIVALENT
void menu_track_select_init(void) {
    s32 levelCount;
    s32 worldCount;
    Settings *settings;
    TextureHeader **var_s0;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 var_a0;
    s8 **trackMenuIds;
    s16 *var_s2;
    s32 videoWidthAndHeight;
    s32 temp_v0_6;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 idx2;
    s32 idx;
    s32 var_v0;
    s16 var_t4;

    load_font(ASSET_FONTS_BIGFONT);
    settings = get_settings();
    get_number_of_levels_and_worlds(&levelCount, &worldCount);
    trackMenuIds = (s8 **) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    if (gTitleScreenLoaded != 0) {
        D_801269C8 = 0;
        D_801269CC = 0;
        gTracksMenuTimeTrialHighlightIndex = 0;
        gTracksMenuAdventureHighlightIndex = 0;
        gTitleScreenLoaded = 0;
    }
    videoWidthAndHeight = get_video_width_and_height_as_s32();
    gTrackSelectViewPortX = GET_VIDEO_WIDTH(videoWidthAndHeight);
    gTrackSelectViewportY = GET_VIDEO_HEIGHT(videoWidthAndHeight);
    gTrackSelectViewPortHalfX = gTrackSelectViewPortX >> 1;
    gTrackSelectViewPortHalfY = gTrackSelectViewportY >> 1;
    gTrackSelectX = (f32) D_801269C8 * 320.0f;
    gTrackSelectY = (f32) D_801269CC * (f32) -gTrackSelectViewportY;
    gSelectedTrackX = -1;
    gSelectedTrackY = -1;
    D_801263D0 = -1;
    gOpacityDecayTimer = 32;
    gOptionBlinkTimer = 0;
    D_801267D0 = -1;
    func_8008F00C(0);
    transition_begin(&sMenuTransitionFadeOut);
    enable_new_screen_transitions();
    set_background_fill_colour(50, 105, 223);
    for (var_a1 = 0; var_a1 != 5; var_a1++) {
        temp_a0 = gTracksMenuBgTextureIndices[(var_a1 * 3)];
        var_s0 = (TextureHeader **) gTracksMenuBgTextures[var_a1];
        if (temp_a0 != -1) {
            func_8009C6D4(temp_a0);
            var_s0[0] = gMenuObjects[gTracksMenuBgTextureIndices[(var_a1 * 3)]];
        } else {
            var_s0[0] = NULL;
        }
        temp_a0_2 = gTracksMenuBgTextureIndices[(var_a1 * 3) + 1];
        if (temp_a0_2 != -1) {
            func_8009C6D4(temp_a0_2);
            var_s0[1] = (TextureHeader *) gMenuObjects[gTracksMenuBgTextureIndices[(var_a1 * 3)]];
        } else {
            var_s0[1] = NULL;
        }
    }
    gTrackSelectBgTriangles[0] = (Triangle *) allocate_from_main_pool_safe(2880, COLOUR_TAG_YELLOW);
    gTrackSelectBgTriangles[1] = (s32) (&gTrackSelectBgTriangles[0][40]); // 640 bytes forward
    gTrackSelectBgVertices[0] = (s32) (&gTrackSelectBgTriangles[1][80]);  // 1280 bytes forward
    // gTrackSelectBgVertices[1] = (s32) (&gTrackSelectBgVertices[0][80]); //800 bytes past gTrackSelectBgVertices
    var_a0 = -160;
    var_v0 = 0;
    for (var_v0 = 0; var_v0 < 80; var_v0++) {
        gTrackSelectBgVertices[var_v0]->x = var_a0;
        var_a0 = -var_a0;
        gTrackSelectBgVertices[var_v0]->z = -1024;
        gTrackSelectBgVertices[var_v0]->r = 0xFF;
        gTrackSelectBgVertices[var_v0]->g = 0xFF;
        gTrackSelectBgVertices[var_v0]->b = 0xFF;
    }
    for (var_v0 = 0; var_v0 < 40; var_v0++) {
        gTrackSelectBgTriangles[var_v0]->flags = 0x40; // 0x40 = Draw backface
        gTrackSelectBgTriangles[var_v0]->vi0 = 0;
        gTrackSelectBgTriangles[var_v0]->vi1 = 2;
        gTrackSelectBgTriangles[var_v0]->vi2 = 1;
    }
    D_80126924 = 0;
    set_background_draw_function(func_8008F618);
    viewport_menu_set(0, 80, gTrackSelectViewPortHalfY - (gTrackSelectViewPortHalfY >> 1), SCREEN_HEIGHT,
                      (gTrackSelectViewPortHalfY >> 1) + gTrackSelectViewPortHalfY);
    copy_viewports_to_stack();
    camEnableUserView(0, 0);
    gIsInTracksMenu = TRUE;
    func_8009C674(gTrackSelectObjectIndices);
    allocate_menu_images(gTrackSelectImageIndices);
    assign_menu_arrow_textures();

    D_800E05D4[0].texture = gMenuObjects[TEXTURE_UNK_08];
    D_800E05D4[1].texture = gMenuObjects[TEXTURE_UNK_09];
    D_800E05D4[2].texture = gMenuObjects[TEXTURE_UNK_0A];
    D_800E05F4[0].texture = gMenuObjects[TEXTURE_UNK_0B];
    D_800E05F4[1].texture = gMenuObjects[TEXTURE_UNK_0C];
    D_800E05F4[2].texture = gMenuObjects[TEXTURE_UNK_0D];

    for (idx = 0; idx < 4; idx++) {
        var_s2 = D_801268E8[idx];
        for (idx2 = 0; idx2 < 6; idx2++) {
            *var_s2 = -1;
            if (idx2 == 0) {
                if (idx < 4) {
                    *var_s2 = trackMenuIds[idx][idx2];
                }
            } else if (idx2 < 4) {
                if ((trackMenuIds[idx][idx2] != -1) && (settings->courseFlagsPtr[trackMenuIds[idx][idx2]] & 1)) {
                    *var_s2 = trackMenuIds[idx][idx2];
                }
            } else if (idx2 == 4) {
                var_a1_2 = 0;
                // This is almost definitely wrong.
                for (var_a0_2 = 0; var_a0_2 < 2; var_a0_2++) {
                    if ((trackMenuIds[idx][var_a0_2] != -1) &&
                        ((settings->courseFlagsPtr[trackMenuIds[idx][var_a0_2]] & 6) == 6)) {
                        var_a1_2++;
                    }
                }
                if ((var_a1_2 == 4) && (idx != 4)) {
                    temp_v0_6 = 130 << idx;
                    if (temp_v0_6 != (settings->bosses & temp_v0_6)) {
                        var_a1_2 = 0;
                    }
                }
                if (var_a1_2 == 4) {
                    *var_s2 = trackMenuIds[idx][idx2];
                }
            } else if ((idx2 == 5) && (settings->keys & (1 << idx))) {
                *var_s2 = trackMenuIds[idx][idx2];
            }
            if (is_adventure_two_unlocked()) {
                *var_s2 = trackMenuIds[idx][idx2];
            }
        }
    }
    gTrackIdForPreview = D_801268E8[D_801269CC][D_801269C8];
    gTrackSelectRow = D_801269CC + 1;
    if (gTrackIdForPreview == (s16) -1) {
        D_801263D0 = D_801268E8[0];
        load_level_for_menu(D_801263D0, -1, 1);
        gTrackSelectRow = 1;
        gSelectedTrackX = 0;
        gSelectedTrackY = 0;
    }
    assign_dialogue_box_id(7);
    func_8007FFEC(2);
    D_80126840 = 0;
    D_80126848 = 0;
    sMenuMusicVolume = 0;
    music_voicelimit_set(24);
    music_voicelimit_change_off();
    music_play(SEQUENCE_MAIN_MENU);
    music_volume_set(sMenuMusicVolume);
    music_change_off();
    set_gIntDisFlag(TRUE); // Set an interrupt?
    gIsInAdventureTwo = gTracksMenuAdventureHighlightIndex;
    gMultiplayerSelectedNumberOfRacersCopy = gMultiplayerSelectedNumberOfRacers;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_track_select_init.s")
#endif

void func_8008F00C(s32 arg0) {
    Vehicle vehicle;
    s32 i;
    s32 temp;

    if ((D_801267D0 != -1) && (D_801267D0 != 0) && (D_801267D0 == 1)) {
        func_8009C4A8(gTrackSelectPreviewObjectIndices);
    }

    D_801267D0 = arg0;
    temp = D_801267D0;

    if ((temp >= 0) && (temp < 2)) {
        switch (D_801267D0) {
            case 0:
                D_801269E8 = gTrackSelectX;
                D_801269EC = gTrackSelectY;
                break;
            case 1:
                vehicle = get_map_default_vehicle(gTrackIdForPreview);
                for (i = 0; i < gNumberOfActivePlayers; i++) {
                    D_801269C4[i] = 0;
                    gPlayerSelectVehicle[i] = vehicle;
                }
                gNumberOfReadyPlayers = 0;
                gTrackNameVoiceDelay = 1;
                func_8009C674(gTrackSelectPreviewObjectIndices);
                allocate_menu_images(gTrackSelectPreviewImageIndices);
                assign_vehicle_icon_textures();
                gRaceSelectionTTOn[0].texture = gMenuObjects[TEXTURE_ICON_TIMETRIAL_ON_TOP];
                gRaceSelectionTTOn[1].texture = gMenuObjects[TEXTURE_ICON_TIMETRIAL_ON_BOTTOM];
                gRaceSelectionTTOff[0].texture = gMenuObjects[TEXTURE_ICON_TIMETRIAL_OFF_TOP];
                gRaceSelectionTTOff[1].texture = gMenuObjects[TEXTURE_ICON_TIMETRIAL_OFF_BOTTOM];
                gRaceSelectionCarOptHighlight[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_CAR_HIGHLIGHT];
                gRaceSelectionCarOpt[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_CAR];
                gRaceSelectionHoverOptHighlight[0].texture =
                    gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT_HIGHLIGHT];
                gRaceSelectionHoverOpt[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT];
                gRaceSelectionPlaneOptHighlight[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_PLANE_HIGHLIGHT];
                gRaceSelectionPlaneOpt[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_PLANE];
                gRaceSelectionTTOnOptHighlight[0].texture = gMenuObjects[TEXTURE_ICON_TIMETRIAL_OPT_ON];
                gRaceSelectionTTOffOptHighlight[0].texture = gMenuObjects[TEXTURE_ICON_TIMETRIAL_OPT_ON_HIGHLIGHT];
                gRaceSelectionTTOnOpt[0].texture = gMenuObjects[TEXTURE_ICON_TIMETRIAL_OPT_OFF];
                gRaceSelectionTTOffOpt[0].texture = gMenuObjects[TEXTURE_ICON_TIMETRIAL_OPT_OFF_HIGHLIGHT];
                gRaceSelectionPlayer1Texture[0].texture = gMenuObjects[TEXTURE_ICON_PLAYER_1];
                gRaceSelectionPlayer2Texture[0].texture = gMenuObjects[TEXTURE_ICON_PLAYER_2];
                gRaceSelectionPlayer3Texture[0].texture = gMenuObjects[TEXTURE_ICON_PLAYER_3];
                gRaceSelectionPlayer4Texture[0].texture = gMenuObjects[TEXTURE_ICON_PLAYER_4];
                gRaceSelectionVehicleTitleTexture[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_TITLE];
                gRaceSelectionTTTitleTexture[0].texture = gMenuObjects[TEXTURE_ICON_TT_TITLE];
                gRaceSelectionTTTexture[0].texture = gMenuObjects[TEXTURE_ICON_TT_HEAD];
                break;
        }
    }
    gMenuDelay = 0;
}

s32 menu_track_select_loop(s32 updateRate) {
    s32 cutsceneId;
    Settings *settings;

    settings = get_settings();
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (get_thread30_level_id_to_load() == 0 && gMenuDelay != 0) {
        if (gMenuDelay < 0) {
            gMenuDelay -= updateRate;
        } else {
            gMenuDelay += updateRate;
        }
    }
    func_8008E4EC();

    gSPClearGeometryMode(sMenuCurrDisplayList++, G_CULL_FRONT);

    switch (D_801267D0) {
        case 0:
            func_8008FF1C(updateRate);
            func_800904E8(updateRate);
            func_80090918(updateRate);
            break;
        case 1:
            func_80090ED8(updateRate);
            render_track_select_setup_ui(updateRate);
            func_80092188(updateRate);
            break;
    }

    if (sMenuMusicVolume < 0) {
        music_volume_set(0);
    } else {
        sMenuMusicVolume += updateRate * 2;
        if (sMenuMusicVolume >= 81) {
            sMenuMusicVolume = 80;
        }
        music_volume_set((u8) sMenuMusicVolume);
    }
    if (D_801267D0 < 0) {
        func_8008F534();
        gTrackSpecifiedWithTrackIdToLoad = 0;
        if (gNumberOfActivePlayers >= 3 ||
            (gNumberOfActivePlayers == 2 && !(gActiveMagicCodes & CHEAT_TWO_PLAYER_ADVENTURE))) {
            cutsceneId = 0;
            if (is_drumstick_unlocked()) {
                cutsceneId = 1;
            }
            if (is_tt_unlocked()) {
                cutsceneId ^= 3;
            }
            load_level_for_menu(ASSET_LEVEL_CHARACTERSELECT, -1, cutsceneId);
            func_8008AEB4(0, NULL);
            menu_init(MENU_CHARACTER_SELECT);
            return MENU_RESULT_CONTINUE;
        }
        load_level_for_menu(ASSET_LEVEL_OPTIONSBACKGROUND, -1, 0);
        menu_init(MENU_GAME_SELECT);
        return MENU_RESULT_CONTINUE;
    }
    if (D_801267D0 >= 2) {
        func_8008F534();
        if (gMultiplayerSelectedNumberOfRacersCopy != gMultiplayerSelectedNumberOfRacers) {
            for (cutsceneId = 0; cutsceneId < 8; cutsceneId++) {
                settings->racers[cutsceneId].starting_position = cutsceneId;
            }
        }
        if (D_801269C8 != 4) {
            gTrackSpecifiedWithTrackIdToLoad = 1;
            return gNumberOfActivePlayers;
        }
        gTrophyRaceWorldId = D_801269CC + 1;
        gInAdvModeTrophyRace = 0;
        gTrophyRaceRound = 0;
        menu_init(MENU_TROPHY_RACE_ROUND);
        return MENU_RESULT_CONTINUE;
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}

void func_8008F534(void) {
    s32 i;

    camDisableUserView(0, FALSE);
    func_8009C4A8(gTrackSelectObjectIndices);
    set_free_queue_state(0);
    free_from_memory_pool(gTrackSelectBgTriangles[0]);
    set_free_queue_state(2);
    for (i = 0; i < 15; i += 3) {
        if (gTracksMenuBgTextureIndices[i] != -1) {
            func_8009C508(gTracksMenuBgTextureIndices[i]);
        }
        if (gTracksMenuBgTextureIndices[i + 1] != -1) {
            func_8009C508(gTracksMenuBgTextureIndices[i + 1]);
        }
    }
    unload_font(ASSET_FONTS_BIGFONT);
    func_8007FF88();
    music_change_on();
    music_voicelimit_change_on();
    music_stop();
    set_gIntDisFlag(FALSE);
}

#ifdef NON_EQUIVALENT
s32 func_8008F618(Gfx **dlist, MatrixS **mtx) {
    s32 sp7C;
    u8 *data;
    s32 texU;
    s32 texV;
    UNUSED s32 pad1;
    s32 yPos;
    s32 flags;
    s32 hasTexture;
    UNUSED s32 pad2;
    s32 numVertices;
    s32 index;
    s32 prevAlpha;
    s32 prevIndex;
    s32 temp;
    s32 temp2;
    Vertex *vertices;
    Triangle *triangles;
    TextureHeader *bgTexture;
    s32 prevAlpha2;
    s32 curIndex;

    numVertices = 0;
    camDisableUserView(0, TRUE);
    camera_init_tracks_menu(dlist, mtx);
    set_ortho_matrix_view(dlist, mtx);
    reset_render_settings(dlist);
    gDPPipeSync((*dlist)++);
    sp7C = gTrackSelectX;
    temp2 = -gTrackSelectY;
    temp = temp2 / (gTrackSelectViewportY >> 3);
    if (temp >= 42) {
        return 1;
    }
    temp2 -= (temp * (gTrackSelectViewportY >> 3));
    yPos = gTrackSelectViewPortHalfY + temp2;
    gDPSetPrimColor((*dlist)++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor((*dlist)++, 255, 255, 255, 0);
    vertices = (&gTrackSelectBgVertices)[D_80126924];
    triangles = (&gTrackSelectBgTriangles)[D_80126924];
    for (index = 0; gTrackSelectBgData[index] < temp; index += 5) {}

    data = &gTrackSelectBgData[index];
    while ((yPos >= -gTrackSelectViewPortHalfY) && (data[0] < 42) && (numVertices < 64)) {
        bgTexture = gTracksMenuBgTextures[data[1]];
        vertices[0].y = yPos;
        vertices[1].y = yPos;
        vertices[0].a = data[2];
        vertices[1].a = data[2];
        prevIndex = data[0];
        prevAlpha = data[2];
        vertices[2].y = yPos - (gTrackSelectViewportY >> 3);
        vertices[2].a = data[3];
        vertices[3].y = (gTrackSelectViewPortHalfY + temp2) - (gTrackSelectViewportY >> 3);
        vertices[3].a = data[3];
        prevAlpha2 = data[3];
        data += 4;
        if (bgTexture != 0) {
            texU = (((bgTexture->width - 1) & sp7C) << 5) + (data[0] << 5);
            data++;
            texV = bgTexture->height << 5;
        }
        triangles[0].uv0.u = texU;
        triangles[0].uv0.v = 0;
        triangles[0].uv1.u = texU;
        triangles[0].uv1.v = texV;
        triangles[0].uv2.u = texU + 0x2800;
        triangles[0].uv2.v = 0;
        triangles[1].uv0.u = texU + 0x2800;
        triangles[1].uv0.v = 0;
        triangles[1].uv1.u = texU;
        triangles[1].uv1.v = texV;
        triangles[1].uv2.u = texU + 0x2800;
        triangles[1].uv2.v = texV;

        triangles += 2;
        vertices += 4;

        if (bgTexture != 0) {
            hasTexture = 1;
        } else {
            hasTexture = 0;
        }

        // If both alphas are 255, then don't set the transparency flags.
        if ((prevAlpha + prevAlpha2) == 255 + 255) {
            flags = 0;
        } else {
            flags = RENDER_VTX_ALPHA | RENDER_Z_UPDATE;
        }

        load_and_set_texture(dlist, bgTexture, flags, 0);
        gSPVertexDKR((*dlist)++, OS_PHYSICAL_TO_K0(vertices), 4, 0);
        gSPPolygon((*dlist)++, OS_PHYSICAL_TO_K0(triangles), 2, hasTexture);
        curIndex = data[0];
        if (prevIndex != curIndex) {
            yPos -= (gTrackSelectViewportY >> 3);
        }
        numVertices += 4;
    }
    camEnableUserView(0, 1);
    return 0;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_8008F618.s")
#endif

void render_track_select(s32 x, s32 y, char *hubName, char *trackName, s32 rectOpacity, s32 imageId, s32 copyViewPort,
                         DrawTexture *arg7, s32 arg8) {
    s32 xTemp;
    s32 yTemp;
    s32 opacity;
    s32 i;
    s32 sp6C;
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;
    f32 sp58;
    f32 sp54;
    s16 *offsets;
    s32 temp;

    sp6C = 0;
    xTemp = x + 160;
    yTemp = gTrackSelectViewPortHalfY - y;
    if (osTvType == TV_TYPE_PAL) {
        sp6C = 12;
    }
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_background_colour(0, 0, 0, 0);
    if (gMenuDelay > 0) {
        opacity = 255 - (gMenuDelay * 16);
        if (opacity < 0) {
            opacity = 0;
        }
    } else {
        opacity = 255;
    }
    if (hubName != D_801269F0) {
        temp = (s32) get_level_name(get_hub_area_id(3));
        if ((s32) hubName == temp) {
            set_kerning(TRUE);
        }
        set_text_colour(0, 0, 0, 255, opacity / 2);
        draw_text(&sMenuCurrDisplayList, 161, (yTemp - sp6C) - 85, hubName, ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 255, 255, 0, opacity);
        draw_text(&sMenuCurrDisplayList, 160, (yTemp - sp6C) - 88, hubName, ALIGN_MIDDLE_CENTER);
        D_801269F0 = hubName;
        set_kerning(0);
    }
    set_text_colour(255, 255, 255, 0, opacity);
    draw_text(&sMenuCurrDisplayList, xTemp, sp6C + yTemp + 88, trackName, ALIGN_MIDDLE_CENTER);
    if (rectOpacity > 0) {
        if (((yTemp - (gTrackSelectViewportY >> 2)) < gTrackSelectViewportY) &&
            (((gTrackSelectViewportY >> 2) + yTemp) > 0)) {
            sp58 = 1.25f;
            sp54 = 1.25f;
            if (osTvType == TV_TYPE_PAL) {
                sp54 *= 1.1;
            }
            temp = xTemp - 80;
            if (copyViewPort) {
                copy_viewport_frame_size_to_coords(0, &x1, &y1, &x2, &y2);
                temp = x1;
                sp58 = (x2 - temp) / 128.0f;
                sp54 = (y2 - y1) / 96.0f;
            } else {
                x2 = xTemp + 80;
            }
            x1 = temp;
            if (temp < SCREEN_WIDTH && xTemp > 0) {
                render_texture_rectangle_scaled(&sMenuCurrDisplayList, arg7, xTemp, yTemp, sp58, sp54,
                                                (rectOpacity & 0xFF) | ~0xFF, 0x1000);
            }
            if (xTemp < SCREEN_WIDTH && x2 > 0) {
                render_texture_rectangle_scaled(&sMenuCurrDisplayList, arg7, xTemp, yTemp, sp58, sp54,
                                                (rectOpacity & 0xFF) | ~0xFF, 0);
            }
            reset_render_settings(&sMenuCurrDisplayList);
        }
    }
    gMenuImageStack[imageId].unkC = x;
    gMenuImageStack[imageId].unk10 = y;
    if (osTvType == TV_TYPE_PAL) {
        gTrackSelectWoodFrameHeightScale = 1.2f;
        offsets = gTracksMenuArrowPositionsPAL;
    } else {
        offsets = gTracksMenuArrowPositionsNTSC;
    }
    func_8009CA60(imageId);
    gTrackSelectWoodFrameHeightScale = 1.0f;
    for (i = 0; i < 4; i++) {
        if ((1 << i) & arg8) {
            render_textured_rectangle(&sMenuCurrDisplayList, gMenuSelectionArrows[i], offsets[(i << 1)] + xTemp + 1,
                                      offsets[(i << 1) + 1] + yTemp + 1, 0, 0, 0, 128);
            render_textured_rectangle(&sMenuCurrDisplayList, gMenuSelectionArrows[i], offsets[(i << 1)] + xTemp - 1,
                                      offsets[(i << 1) + 1] + yTemp - 1, 255, 255, 255, 255);
        }
    }
    reset_render_settings(&sMenuCurrDisplayList);
}

#ifdef NON_MATCHING
void func_8008FF1C(UNUSED s32 updateRate) {
    s32 i; // sp7C
    UNUSED s16 **temp2;
    char *hubName;
    UNUSED s32 temp4;
    s32 trackSelectX;
    UNUSED s32 pad4;
    s32 temp;
    s32 maxTrackY;
    s8 *trackMenuIds;
    Settings *settings; // sp58
    TrackRenderDetails *cur;
    s32 trackX;
    s32 trackY;
    s32 j;
    s32 startIndex;

    settings = get_settings();
    trackMenuIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    if (gMenuDelay > -23 && gMenuDelay < 23) {
        if (gFFLUnlocked == -1) {
            maxTrackY = 3;
        } else {
            maxTrackY = 4;
        }
        trackSelectX = (gTrackSelectX / 320);
        temp = (gTrackSelectY / -gTrackSelectViewportY);
        trackY = temp - 1;
        startIndex = -1;
        for (i = startIndex, cur = gTrackSelectRenderDetails; i < 2; i++) {
            for (j = startIndex; j < 2; j++) {
                trackX = trackSelectX + j;
                if ((trackY < 0) || (maxTrackY < trackY) || (trackX < 0) || (trackX >= 6)) {
                    cur->visible = 0;
                } else {
                    cur->visible = 1;
                    hubName = get_level_name(get_hub_area_id(trackY + 1));
                    cur->hubName = hubName;
                    // Problem is here.
                    if (D_801268E8[trackY][trackX] != -1) {
                        cur->trackName = get_level_name(trackMenuIds[(trackY * 6) + trackX]);
                        if (trackX == 4) {
                            if (((settings->trophies >> (trackY * 2)) & 3) == 3) {
                                cur->visible = 2;
                            }
                        } else if ((settings->courseFlagsPtr[trackMenuIds[(trackY * 6) + trackX]] & 2)) {
                            cur->visible = 2;
                        }
                    } else {
                        cur->trackName = (char *) gQMarkPtr;
                    }
                    cur->xOff = ((trackX * 320) - gTrackSelectX);
                    if (1) {} // Fakematch
                    cur->yOff = ((-trackY * gTrackSelectViewportY) - gTrackSelectY);
                    cur->opacity = 0xFF;
                    if ((trackX == gSelectedTrackX) && (trackY == gSelectedTrackY)) {
                        cur->copyViewPort = (cur->copyViewPort & 0xFF) | 0x80;
                        if (gOpacityDecayTimer < 32) {
                            cur->opacity = gOpacityDecayTimer * 8;
                        }
                    } else {
                        cur->copyViewPort = cur->copyViewPort & 0xFF7F;
                    }
                    cur->copyViewPort = cur->copyViewPort & 0xFF80;
                    if (gMenuDelay == 0) {
                        if (trackY > 0) {
                            cur->copyViewPort =
                                (((cur->copyViewPort & 0xFF) | 1) & 0x7F) | (cur->copyViewPort & 0xFF80);
                        }
                        if (trackX < 5) {
                            cur->copyViewPort =
                                (((cur->copyViewPort & 0xFF) | 2) & 0x7F) | (cur->copyViewPort & 0xFF80);
                        }
                        if (trackY < maxTrackY) {
                            cur->copyViewPort =
                                (((cur->copyViewPort & 0xFF) | 4) & 0x7F) | (cur->copyViewPort & 0xFF80);
                        }
                        if (trackX > 0) {
                            cur->copyViewPort =
                                (((cur->copyViewPort & 0xFF) | 8) & 0x7F) | (cur->copyViewPort & 0xFF80);
                        }
                        if (trackX == 4 && trackY == 4) {
                            cur->copyViewPort =
                                ((cur->copyViewPort & 0xFF & 0xFF) & 0x7D) | (cur->copyViewPort & 0xFF80);
                        }
                        if (trackX == 5 && trackY == 3) {
                            cur->copyViewPort =
                                ((cur->copyViewPort & 0xFF & 0xFF) & 0x7B) | (cur->copyViewPort & 0xFF80);
                        }
                    }
                    if (trackX == 4) {
                        cur->border = 6;
                    } else if (trackX == 5) {
                        cur->border = 5;
                    } else {
                        cur->border = 4;
                    }
                }
                cur++;
            }
            trackY++;
        }
        camDisableUserView(0, TRUE);
        func_8009BD5C();
        set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
        reset_render_settings(&sMenuCurrDisplayList);
        gDPPipeSync(sMenuCurrDisplayList++);
        D_80126928 = 64;
        D_8012692C = 32;
        D_801269F0 = NULL;
        for (i = 0; i < ARRAY_COUNT(gTrackSelectRenderDetails); i++) {
            if (gTrackSelectRenderDetails[i].visible != 0) {
                render_track_select(gTrackSelectRenderDetails[i].xOff, gTrackSelectRenderDetails[i].yOff,
                                    gTrackSelectRenderDetails[i].hubName, gTrackSelectRenderDetails[i].trackName,
                                    gTrackSelectRenderDetails[i].opacity, gTrackSelectRenderDetails[i].border,
                                    ((u32) gTrackSelectRenderDetails[i].viewPort) >> 0xF,
                                    (gTrackSelectRenderDetails[i].visible == 1) ? D_800E05D4 : D_800E05F4,
                                    gTrackSelectRenderDetails[i].copyViewPort & 0x7F);
            }
        }
        D_80126924 = 1 - D_80126924;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_8008FF1C.s")
#endif

void func_800904E8(s32 updateRate) {
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;
    s32 i;

    tick_thread30();
    for (i = 0; i < updateRate; i++) {
        gTrackSelectX += (D_801269E8 - gTrackSelectX) * 0.1;
        gTrackSelectY += (D_801269EC - gTrackSelectY) * 0.1;
    }
    if (gOpacityDecayTimer == 32 && get_thread30_level_id_to_load() == 0) {
        if (gTrackIdForPreview == D_801263D0) {
            gSelectedTrackX = D_801269C8;
            gSelectedTrackY = D_801269CC;
        } else if (gTrackIdForPreview != D_801263D0 && gTrackIdForPreview != -1 &&
                   set_level_to_load_in_background(gTrackIdForPreview, 1)) {
            D_801263D0 = gTrackIdForPreview;
            gSelectedTrackX = D_801269C8;
            gSelectedTrackY = D_801269CC;
            set_level_default_vehicle(get_map_default_vehicle(gTrackIdForPreview));
        }
    }
    x1 = ((gSelectedTrackX * SCREEN_WIDTH) - gTrackSelectX) + SCREEN_WIDTH_FLOAT_HALF - 80.0f;
    x2 = x1 + SCREEN_WIDTH_HALF;
    y1 = gTrackSelectViewPortHalfY - ((gSelectedTrackY * -gTrackSelectViewportY) - gTrackSelectY) -
         (gTrackSelectViewportY >> 2);
    y2 = y1 + gTrackSelectViewPortHalfY;
    viewport_menu_set(0, x1, y1, x2, y2);
    copy_viewport_background_size_to_coords(0, &x1, &y1, &x2, &y2);
    camEnableUserView(0, 0);
}

void func_80090918(s32 updateRate) {
    UNUSED s32 pad1[2];
    s32 var_t1;
    UNUSED s32 pad2[2];
    s32 var_a1;
    s32 var_t0;
    s32 var_t2;
    s32 sp24;
    s32 var_t3;
    s32 var_a2;

    sp24 = gMenuDelay;
    if (gMenuDelay > 0) {
        if ((D_801269E8 - gTrackSelectX > 4.0f) || (D_801269E8 - gTrackSelectX < -4.0f) ||
            ((D_801269EC - gTrackSelectY > 4.0f)) || (D_801269EC - gTrackSelectY < -4.0f)) {
            gMenuDelay = 1;
        } else if (D_800E1E1C) {
            sound_play(SOUND_SELECT2, NULL);
            D_800E1E1C = 0;
        }
        var_t1 = gMenuDelay - 1;
        if (var_t1 > 20) {
            var_t1 = 20;
        }
        var_t2 = 160;
        var_t0 = gTrackSelectViewPortHalfY;
        if (var_t1 < 20) {
            var_t2 += (D_801269E8 - gTrackSelectX);
            var_t0 -= (D_801269EC - gTrackSelectY);
        }
        var_t3 = (((var_t1 + 20) * gTrackSelectViewPortHalfY) / 40) + var_t0;
        var_a2 = var_t0 - (((var_t1 + 20) * gTrackSelectViewPortHalfY) / 40);
        viewport_menu_set(0, (var_t2 - (var_t1 * 4)) - 80, var_a2, (var_t1 * 4) + var_t2 + 80, var_t3);
        gMenuImageStack[4].unk8 = (f32) (sMenuImageProperties[4].unk8 * (1.0f + ((f32) var_t1 / 20.0f)));
        gMenuImageStack[6].unk8 = (f32) (sMenuImageProperties[6].unk8 * (1.0f + ((f32) var_t1 / 20.0f)));
        gMenuImageStack[5].unk8 = (f32) (sMenuImageProperties[5].unk8 * (1.0f + ((f32) var_t1 / 20.0f)));
    }
    camEnableUserView(0, 0);
    if (get_thread30_level_id_to_load() == 0) {
        if (gMenuDelay < 0) {
            sMenuMusicVolume -= updateRate * 4;
        }
        if (gSelectedTrackX == D_801269C8 && gSelectedTrackY == D_801269CC) {
            gOpacityDecayTimer -= updateRate;
            if (gOpacityDecayTimer < 0) {
                gOpacityDecayTimer = 0;
            }
        } else {
            gOpacityDecayTimer = gOpacityDecayTimer + updateRate;
            if (gOpacityDecayTimer > 32) {
                gOpacityDecayTimer = 32;
            }
        }
        if (gMenuDelay < -22) {
            set_background_draw_function(NULL);
            gIsInTracksMenu = FALSE;
        }
        if (gMenuDelay > 30) {
            if ((is_adventure_two_unlocked()) && (D_801269C8 != 5)) {
                gMenuOptionCount = -1;
            } else {
                gMenuOptionCount = 0;
            }
            func_8008F00C(1);
        } else if (gMenuDelay < -30) {
            disable_new_screen_transitions();
            camDisableUserView(0, FALSE);
            func_8008F00C(-1);
        }
    }
    if (sp24 == 0) {
        var_a1 = (gFFLUnlocked == -1) ? 3 : 4;
        if (D_801267D8[4] & (A_BUTTON | START_BUTTON)) {
            if (gTrackIdForPreview != (s32) -1) {
                gMenuDelay = 1;
                gTrackIdToLoad = gTrackIdForPreview;
                D_800E1E1C = 1;
            } else {
                sound_play(SOUND_UNK_6A, NULL);
            }
        } else if (D_801267D8[4] & B_BUTTON) {
            disable_new_screen_transitions();
            transition_begin(&sMenuTransitionFadeIn);
            enable_new_screen_transitions();
            gMenuDelay = -1;
        } else {
            s32 prevValue = D_801269C8;
            s32 prevValue2 = D_801269CC;
            if ((D_80126818[4] < 0) && (D_801269C8 > 0)) {
                D_801269C8--;
            }
            if ((D_80126818[4] > 0) && (D_801269C8 < 5)) {
                D_801269C8++;
            }
            if ((D_801269CC == 4) && (D_801269C8 == 5)) {
                D_801269C8 = 4;
            }
            if (D_80126818[4] == 0) {
                if ((D_80126830[4] < 0) && (D_801269CC < var_a1)) {
                    D_801269CC++;
                }
                if ((D_80126830[4] > 0) && (D_801269CC > 0)) {
                    D_801269CC--;
                }
                if ((D_801269C8 == 5) && (D_801269CC == 4)) {
                    D_801269CC = 3;
                }
            }
            if ((prevValue != D_801269C8) || (D_801269CC != prevValue2)) {
                sound_play(SOUND_MENU_PICK2, NULL);
                gTrackIdForPreview = D_801268E8[D_801269CC][D_801269C8];
                gTrackSelectRow = D_801269CC + 1;
                D_801269E8 = (D_801269C8 * 320);
                D_801269EC = -(D_801269CC * gTrackSelectViewportY);
            }
        }
    }
}

void func_80090ED8(UNUSED s32 updateRate) {
    if (gMenuOptionCount == 1 && gTracksMenuTimeTrialHighlightIndex == 0 && D_80126840 == 0) {
        sound_play(SOUND_VOICE_TT_SNORE, &D_80126840);
    }
}

void render_track_select_setup_ui(UNUSED s32 updateRate) {
    // Had to mess around with shifting the local variables, so they all probably need to be renamed.
    s32 k;
    s32 y;
    s32 temp2;
    s32 temp;
    s32 sp84;
    s32 regionOffset;          // sp80
    s32 availableVehicleFlags; // sp7C
    union {
        char buffer[4];
        s32 word;
    } filename; // sp78
    s32 sp74;
    Settings *settings; // sp70
    s32 i;
    s32 j;

    regionOffset = 0;
    filename.word = 0; // Set all 4 bytes as '\0'?
    sp74 = FALSE;
    settings = get_settings();
    if (osTvType == TV_TYPE_PAL) {
        regionOffset = 12;
    }
    if (gNumberOfActivePlayers == 2 && D_801269C8 < 4 && gMenuOptionCount >= 2) {
        sp74 = TRUE;
    }
    camDisableUserView(0, TRUE);
    func_8009BD5C();
    set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (gMenuDelay < 0) {
        if (gSelectedTrackX == 4) {
            sp84 = 6;
        } else if ((gSelectedTrackX == 5)) {
            sp84 = 5;
        } else {
            sp84 = 4;
        }
        gMenuImageStack[sp84].unkC = 0.0f;
        gMenuImageStack[sp84].unk10 = 0.0f;
        if (osTvType == TV_TYPE_PAL) {
            gTrackSelectWoodFrameHeightScale = 1.2f;
        }
        func_8009CA60(sp84);
        gTrackSelectWoodFrameHeightScale = 1.0f;
    }
    if (gMenuDelay >= -22 && gMenuDelay <= 30) {
        sMenuGuiOpacity = (gMenuDelay < 0) ? 255 + (gMenuDelay * 16) : 255;
        if (sMenuGuiOpacity < 0) {
            sMenuGuiOpacity = 0;
        }
        availableVehicleFlags = get_map_available_vehicles(gTrackIdForPreview);
        i = get_level_name(gTrackIdForPreview);
        set_text_font(ASSET_FONTS_BIGFONT);
        set_text_colour(192, 192, 255, 0, sMenuGuiOpacity);
        set_text_background_colour(0, 0, 0, 0);
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, 43, (char *) i, ALIGN_MIDDLE_CENTER); // Draw track name?
        sp84 = gOptionBlinkTimer * 8;
        if (sp84 >= 256) {
            sp84 = 511 - sp84;
        }
        set_current_dialogue_background_colour(7, 255, sp84, 0, sMenuGuiOpacity);
        if (gMenuOptionCount == -1 || (gMenuOptionCount == 2 && D_801269C8 == 4 && is_adventure_two_unlocked())) {
            temp2 = get_text_width(gMenuText[ASSET_MENU_TEXT_ADVENTURE2], 0, 0); // "ADVENTURE"
            k = get_text_width(gMenuText[ASSET_MENU_TEXT_ADVENTURETWO2], 0, 0);  // "ADVENTURE TWO"
            if (temp2 < k) {
                temp2 = k;
            }
            if (temp2 < gTracksMenuAdventureButton.width) {
                temp2 = gTracksMenuAdventureButton.width;
            } else {
                temp2 += 12;
            }
            func_80080580(&sMenuCurrDisplayList, -(temp2 >> 1), SCREEN_HEIGHT_HALF - gTracksMenuAdventureButton.y,
                          temp2, gTracksMenuAdventureButton.height, gTracksMenuAdventureButton.borderWidth,
                          gTracksMenuAdventureButton.borderHeight, sMenuGuiOpacity + COLOUR_RGBA32(176, 224, 192, 0),
                          gMenuObjects[67]);
            func_80080E6C();
            set_text_font(ASSET_FONTS_FUNFONT);
            for (temp = 0, temp2 = 0,
                y = gTracksMenuAdventureButton.colourMax + gTracksMenuAdventureButton.y + regionOffset + 1;
                 temp2 < 2; temp2++, temp++, y += 16) {
                for (j = 0, i = y; j < 4; j += 2, i -= 2) {
                    if (j == 0) {
                        set_text_colour(0, 0, 0, 255, sMenuGuiOpacity >> 1);
                    } else {
                        k = 0;
                        if (temp2 == gTracksMenuAdventureHighlightIndex) {
                            k = sp84;
                        }
                        set_text_colour(255, 255, 255, k, sMenuGuiOpacity);
                    }
                    // gMenuText[146] = "ADVENTURE", gMenuText[147] = "ADVENTURE TWO"
                    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1 - j, i,
                              gMenuText[ASSET_MENU_TEXT_ADVENTURE2 + temp], ALIGN_MIDDLE_CENTER);
                }
            }
        }
        if (D_801269C8 < 4) {
            set_text_font(ASSET_FONTS_FUNFONT);
            set_text_colour(255, 64, 64, 96, sMenuGuiOpacity);
            draw_text(&sMenuCurrDisplayList, 56, 72 + regionOffset, gMenuText[ASSET_MENU_TEXT_BESTTIME],
                      ALIGN_MIDDLE_LEFT); // "BEST TIME"
            draw_text(&sMenuCurrDisplayList, 56, 92 + regionOffset, gMenuText[ASSET_MENU_TEXT_BESTLAP],
                      ALIGN_MIDDLE_LEFT); // "BEST LAP"
            set_text_colour(255, 128, 255, 96, sMenuGuiOpacity);
            decompress_filename_string(settings->courseInitialsPtr[gPlayerSelectVehicle[0]][gTrackIdForPreview],
                                       filename.buffer, 3);
            draw_text(&sMenuCurrDisplayList, 250, regionOffset + 72, filename.buffer, ALIGN_MIDDLE_CENTER);
            decompress_filename_string(settings->flapInitialsPtr[gPlayerSelectVehicle[0]][gTrackIdForPreview],
                                       filename.buffer, 3);
            draw_text(&sMenuCurrDisplayList, 250, regionOffset + 92, filename.buffer, ALIGN_MIDDLE_CENTER);
            show_timestamp(settings->courseTimesPtr[gPlayerSelectVehicle[PLAYER_ONE]][gTrackIdForPreview], 22, 53, 128,
                           255, 255, FONT_COLOURFUL);
            show_timestamp(settings->flapTimesPtr[gPlayerSelectVehicle[PLAYER_ONE]][gTrackIdForPreview], 22, 33, 255,
                           192, 255, FONT_COLOURFUL);
            if (gMenuOptionCount != -1) {
                if (gNumberOfActivePlayers == 1) {
                    set_current_dialogue_box_coords(7, 134, regionOffset + 112, 186, regionOffset + 137);
                    render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 7);
                    if (gMenuOptionCount <= 0) {
                        render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionVehicleTitleTexture, 136,
                                                  regionOffset + 114, 255, 255, 255, sMenuGuiOpacity);
                    } else {
                        render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionTTTitleTexture, 136,
                                                  regionOffset + 114, 255, 255, 255, sMenuGuiOpacity);
                        for (k = 0, y = regionOffset + 151; k < 2; k++, y += 24) {
                            if (k == gTracksMenuTimeTrialHighlightIndex) {
                                render_textured_rectangle(&sMenuCurrDisplayList, gTrackSelectTTImage[k * 3 + 1], 104, y,
                                                          255, 255, 255, sMenuGuiOpacity);
                            } else {
                                render_textured_rectangle(&sMenuCurrDisplayList, gTrackSelectTTImage[k * 3 + 2], 104, y,
                                                          255, 255, 255, sMenuGuiOpacity);
                            }
                        }
                    }
                } else if (!sp74) {
                    // Probably fake
                    y = gNumberOfActivePlayers;
                    j = ((y - 1) * y);
                    for (k = 0; (k < y) ^ 0; k++) {
                        if ((gNumberOfActivePlayers == 1 && k == gMenuOptionCount) ||
                            (gNumberOfActivePlayers > 1 && D_801269C4[k] == 0)) {
                            set_current_dialogue_box_coords(7, gTracksMenuPlayerNamePositions[j] - 2,
                                                            gTracksMenuPlayerNamePositions[j + 1] + regionOffset - 2,
                                                            gTracksMenuPlayerNamePositions[j] + 50,
                                                            gTracksMenuPlayerNamePositions[j + 1] + regionOffset + 23);
                            render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 7);
                        }
                        render_textured_rectangle(
                            &sMenuCurrDisplayList, gTrackSelectPlayerImage[k], gTracksMenuPlayerNamePositions[j],
                            gTracksMenuPlayerNamePositions[j + 1] + regionOffset, 255, 255, 255, sMenuGuiOpacity);
                        j += 2;
                    }
                }
                if ((gNumberOfActivePlayers > 1 || gMenuOptionCount == 0) && !sp74) {
                    // Draws "Car", "Hover", "Plane" text choice images.
                    j = ((gNumberOfActivePlayers - 1) * gNumberOfActivePlayers) >> 1;
                    for (k = 0, y = regionOffset + 139; k < 3; k++) {
                        if ((1 << k) & availableVehicleFlags) {
                            for (temp2 = 0; temp2 < gNumberOfActivePlayers; temp2++) {
                                if (k == gPlayerSelectVehicle[temp2]) {
                                    // Highlighted
                                    render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[(k * 3) + 1],
                                                              gTracksMenuVehicleNamePositions[j + temp2], y, 255, 255,
                                                              255, sMenuGuiOpacity);
                                } else if (settings->courseFlagsPtr[gTrackIdForPreview] & 2) {
                                    // Not highlighted
                                    render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[(k * 3) + 2],
                                                              gTracksMenuVehicleNamePositions[j + temp2], y, 255, 255,
                                                              255, sMenuGuiOpacity);
                                } else {
                                    // Not available (Ghosted out)
                                    render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[(k * 3) + 2],
                                                              gTracksMenuVehicleNamePositions[j + temp2], y, 255, 255,
                                                              255, (sMenuGuiOpacity / 2));
                                }
                            }
                            y += 24;
                        }
                    }
                }
                y = regionOffset + 139;
                if (gPlayerSelectVehicle[PLAYER_ONE] == 2) {
                    y += 2;
                }
                if (gNumberOfActivePlayers == 1) {
                    if (gMenuOptionCount == 0) {
                        // Draw vehicle image for one player
                        render_textured_rectangle(&sMenuCurrDisplayList,
                                                  gRaceSelectionImages[gPlayerSelectVehicle[PLAYER_ONE] * 3], 149, y,
                                                  255, 255, 255, sMenuGuiOpacity);
                    } else {
                        // Draw T.T. image for one player
                        render_textured_rectangle(&sMenuCurrDisplayList,
                                                  gTrackSelectTTImage[gTracksMenuTimeTrialHighlightIndex * 3], 149,
                                                  regionOffset + 139, 255, 255, 255, sMenuGuiOpacity);
                    }
                }
                if (gNumberOfActivePlayers == 2 && !sp74) {
                    // Draw vehicle image for first player
                    render_textured_rectangle(&sMenuCurrDisplayList,
                                              gRaceSelectionImages[gPlayerSelectVehicle[PLAYER_ONE] * 3], 79, y, 255,
                                              255, 255, sMenuGuiOpacity);
                    y = regionOffset + 139;
                    if (gPlayerSelectVehicle[PLAYER_TWO] == 2) {
                        y += 2;
                    }
                    // Draw vehicle image for second player
                    render_textured_rectangle(&sMenuCurrDisplayList,
                                              gRaceSelectionImages[gPlayerSelectVehicle[PLAYER_TWO] * 3], 176, y, 255,
                                              255, 255, sMenuGuiOpacity);
                }
                reset_render_settings(&sMenuCurrDisplayList);
                if (gNumberOfActivePlayers <= 2 && !sp74) {
                    // Draw border around vehicle images
                    gMenuImageStack[7].unk10 = -52.0f;
                    if (gNumberOfActivePlayers == 1) {
                        gMenuImageStack[7].unkC = 21.0f;
                        func_8009CA60(7);
                    } else {
                        gMenuImageStack[7].unkC = -48.0f;
                        func_8009CA60(7);
                        gMenuImageStack[7].unkC = 48.0f;
                        func_8009CA60(7);
                    }
                }
                if (sp74) {
                    temp2 = get_text_width(gMenuText[ASSET_MENU_TEXT_NUMBEROFRACERS], 0, 0); // "NUMBER OF RACERS"
                    if ((gTwoPlayerRacerCountMenu.width - 12) < temp2) {
                        temp2 = temp2 + 12;
                    } else {
                        temp2 = gTwoPlayerRacerCountMenu.width;
                    }
                    func_80080580(&sMenuCurrDisplayList, -(temp2 >> 1), 120 - gTwoPlayerRacerCountMenu.y, temp2,
                                  gTwoPlayerRacerCountMenu.height, gTwoPlayerRacerCountMenu.borderWidth,
                                  gTwoPlayerRacerCountMenu.borderHeight, COLOUR_RGBA32(176, 224, 192, 255),
                                  gMenuObjects[67]);
                    func_80080E6C();
                    set_text_font(ASSET_FONTS_FUNFONT);
                    set_text_colour(0, 0, 0, 255, 128);
                    draw_text(&sMenuCurrDisplayList,
                              gTwoPlayerRacerCountMenu.textPos[0] + gTwoPlayerRacerCountMenu.x + 1,
                              gTwoPlayerRacerCountMenu.textPos[1] + gTwoPlayerRacerCountMenu.y + regionOffset + 1,
                              gMenuText[ASSET_MENU_TEXT_NUMBEROFRACERS], ALIGN_MIDDLE_CENTER);
                    set_text_colour(255, 255, 255, 0, 255);
                    draw_text(&sMenuCurrDisplayList,
                              (gTwoPlayerRacerCountMenu.textPos[0] + gTwoPlayerRacerCountMenu.x) - 1,
                              (gTwoPlayerRacerCountMenu.textPos[1] + gTwoPlayerRacerCountMenu.y + regionOffset) - 1,
                              gMenuText[ASSET_MENU_TEXT_NUMBEROFRACERS], ALIGN_MIDDLE_CENTER);
                    func_80068508(TRUE);
                    sprite_opaque(FALSE);

                    for (temp2 = 0; temp2 < 3; temp2++) {
                        if (temp2 == gMultiplayerSelectedNumberOfRacers) {
                            if (gMenuOptionCount < 3) {
                                sMenuGuiColourG = 255 - sp84;
                                sMenuGuiColourB = 255 - sp84;
                            } else {
                                sMenuGuiColourG = 0;
                                sMenuGuiColourB = 0;
                            }
                        }
                        gMenuImageStack->unkC =
                            (gTwoPlayerRacerCountMenu.textPos[(temp2 << 1) + 2] + gTwoPlayerRacerCountMenu.x) - 160;
                        gMenuImageStack->unk10 =
                            (-gTwoPlayerRacerCountMenu.textPos[(temp2 << 1) + 2 + 1] - gTwoPlayerRacerCountMenu.y) +
                            120;
                        gMenuImageStack->unk18 = (temp2 << 1) + 2;
                        func_8009CA60(0);
                        sMenuGuiColourG = 255;
                        sMenuGuiColourB = 255;
                    }
                    sprite_opaque(TRUE);
                    func_80068508(FALSE);
                }
            }
        }
        if (D_801269C8 < 4) {
            sprite_opaque(FALSE);
            k = 11;
            if (gIsInAdventureTwo) {
                k = 12;
            }
            gMenuImageStack[k].unk10 = 42.0f;
            if ((settings->courseFlagsPtr[gTrackIdForPreview] & 2) || (is_adventure_two_unlocked())) {
                gMenuImageStack[k].unkC = -128.0f;
                func_8009CA60(k);
            }
            if ((settings->courseFlagsPtr[gTrackIdForPreview] & 4) || (is_adventure_two_unlocked())) {
                gMenuImageStack[k].unkC = 120.0f;
                func_8009CA60(k);
            }
            sprite_opaque(TRUE);
        }
        if (gNumberOfActivePlayers == 1 && gMenuOptionCount >= 0 && func_80092BE0(gTrackIdForPreview) >= 0) {
            render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionTTTexture, 204, regionOffset + 122, 255, 255,
                                      255, sMenuGuiOpacity);
            reset_render_settings(&sMenuCurrDisplayList);
        }
        if (D_801269C8 != 5) {
            if ((gMenuOptionCount == 2 && !sp74) || (gMenuOptionCount == 3 && sp74) || gMenuOptionCount == 4) {
                set_text_font(ASSET_FONTS_BIGFONT);
                set_text_colour(255, 255, 255, 0, sMenuGuiOpacity);
                if (D_801269C8 >= 4) {
                    regionOffset += 24;
                }
                draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, regionOffset + 172, (char *) D_800E823C /* "OK?" */,
                          ALIGN_MIDDLE_CENTER);
            }
        }
        sMenuGuiOpacity = 255;
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_80092188.s")

s32 func_80092BE0(s32 mapId) {
    s8 *trackIdArray;
    s32 index;
    s32 temp;

    trackIdArray = (s8 *) get_misc_asset(ASSET_MISC_MAIN_TRACKS_IDS);

    index = 0;
    temp = -1;
    if (trackIdArray[0] != -1) {
        while (temp < 0) {
            if (mapId == (s32) trackIdArray[index]) {
                temp = index;
            }
            index++;
            if (trackIdArray[index] == -1) {
                break;
            }
        }
    }

    if (temp >= 0) {
        u64 temp2 = 0x10 << temp;
        if ((temp2 & sEepromSettings) == 0) {
            temp = -1;
        }
    }

    return temp;
}

/**
 * Load and initialise the track setup gui for use when entering a track in adventure mode.
 */
void menu_adventure_track_init(void) {
    Settings *settings;
    s32 result;
    s32 mapId;
    s16 ttVoiceLine;

    settings = get_settings();
    gTrackIdForPreview = ASSET_LEVEL_CENTRALAREAHUB;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    mapId = settings->unk4C->unk2;
    gPlayerSelectVehicle[PLAYER_ONE] = get_map_default_vehicle(mapId);
    result = get_map_race_type(mapId);
    if ((result == 5) || (result == 8) || (!(result & 0x40) && (!(settings->courseFlagsPtr[mapId] & RACE_CLEARED)))) {
        ttVoiceLine = gTTVoiceLines[mapId];
        if (ttVoiceLine != -1) {
            sound_play_delayed(ttVoiceLine, NULL, 1.0f);
        }
        gMenuOptionCount = -1;
    } else {
        ttVoiceLine = gTTVoiceLines[mapId];
        if (ttVoiceLine != -1) {
            sound_play_delayed(ttVoiceLine, NULL, 0.5f);
        }
        music_voicelimit_set(24);
        music_play(SEQUENCE_MAIN_MENU);
        music_change_off();
        gMenuOptionCount = 0;
        func_8009C674(gAdvTrackInitObjectIndices);
        allocate_menu_images(gAdvTrackInitImageIndices);
        assign_vehicle_icon_textures();
        gRaceSelectionCarOptHighlight[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_CAR_HIGHLIGHT];
        gRaceSelectionCarOpt[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_CAR];
        gRaceSelectionHoverOptHighlight[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT_HIGHLIGHT];
        gRaceSelectionHoverOpt[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT];
        gRaceSelectionPlaneOptHighlight[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_PLANE_HIGHLIGHT];
        gRaceSelectionPlaneOpt[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_SELECT_PLANE];
        gRaceSelectionVehicleTitleTexture[0].texture = gMenuObjects[TEXTURE_ICON_VEHICLE_TITLE];
        gRaceSelectionTTTexture[0].texture = gMenuObjects[TEXTURE_ICON_TT_HEAD];

        transition_begin(&sMenuTransitionFadeOut);
        gOptionBlinkTimer = 0;
        gMenuDelay = 0;
        gTrackNameVoiceDelay = 30;
        load_font(ASSET_FONTS_BIGFONT);
        load_level_for_menu(mapId, -1, 1);
    }
    assign_dialogue_box_id(7);
    if (get_map_race_type(mapId) & 0x40) {
        set_current_text(get_map_world_id(mapId) + 59);
    }
}

/**
 * Render the setup gui when in a track preview in adventure mode.
 * This includes the vehicle selection and if time trial is enabled, the best times.
 */
void render_adventure_track_setup(UNUSED s32 arg0, s32 arg1, s32 arg2) {
    s32 alpha;
    s32 y;
    s32 greenAmount;
    s32 i;
    s32 savedY;
    s32 yOffset;
    s32 mask;
    s32 sp58;
    char *filename;
    Settings *settings;
    char *levelName;

    filename = NULL;
    settings = get_settings();
    yOffset = 0;
    if (osTvType == TV_TYPE_PAL) {
        yOffset = 12;
    }
    sp58 = ((Settings4C *) ((u8 *) settings->unk4C + gTrackIdForPreview))->unk2;
    gSPClearGeometryMode(sMenuCurrDisplayList++, G_CULL_FRONT);
    func_8009BD5C();
    set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (gMenuDelay >= -20) {
        if (gMenuDelay <= 20) {
            mask = get_map_available_vehicles(sp58);
            levelName = get_level_name(sp58);
            set_text_font(FONT_LARGE);
            set_text_background_colour(0, 0, 0, 0);
            set_text_colour(0, 0, 0, 255, 128);
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 46, levelName, ALIGN_MIDDLE_CENTER);
            set_text_colour(255, 255, 255, 0, 255);
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 43, levelName, ALIGN_MIDDLE_CENTER);
            if (!(get_map_race_type(sp58) & 0x40)) {
                if (arg2 == 0) {
                    if (is_time_trial_enabled()) {
                        if (func_80092BE0(sp58) >= 0) {
                            render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionTTTexture,
                                                      SCREEN_HEIGHT - 36, yOffset + 122, 255, 255, 255,
                                                      sMenuGuiOpacity);
                        }
                        set_text_font(0);
                        set_text_colour(255, 64, 64, 96, 255);
                        draw_text(&sMenuCurrDisplayList, 88, yOffset + 72, gMenuText[ASSET_MENU_TEXT_BESTTIME],
                                  ALIGN_MIDDLE_CENTER);
                        draw_text(&sMenuCurrDisplayList, 88, yOffset + 92, gMenuText[ASSET_MENU_TEXT_BESTLAP],
                                  ALIGN_MIDDLE_CENTER);
                        set_text_colour(255, 128, 255, 96, 255);
                        decompress_filename_string(settings->courseInitialsPtr[gPlayerSelectVehicle[0]][sp58],
                                                   (char *) &filename, 3);
                        draw_text(&sMenuCurrDisplayList, 258, yOffset + 72, (char *) &filename, ALIGN_MIDDLE_CENTER);
                        decompress_filename_string(settings->flapInitialsPtr[gPlayerSelectVehicle[0]][sp58],
                                                   (char *) &filename, 3);
                        draw_text(&sMenuCurrDisplayList, 258, yOffset + 92, (char *) &filename, ALIGN_MIDDLE_CENTER);
                        show_timestamp(
                            settings
                                ->courseTimesPtr[gPlayerSelectVehicle[0]]
                                                [((Settings4C *) ((u8 *) settings->unk4C + gTrackIdForPreview))->unk2],
                            26, 53, 128, 255, 255, 0);
                        show_timestamp(
                            settings
                                ->flapTimesPtr[gPlayerSelectVehicle[0]]
                                              [((Settings4C *) ((u8 *) settings->unk4C + gTrackIdForPreview))->unk2],
                            26, 33, 255, 192, 255, 0);
                    }
                    greenAmount = gOptionBlinkTimer * 8;
                    if (greenAmount > 255) {
                        greenAmount = 511 - greenAmount;
                    }
                    set_current_dialogue_background_colour(7, 255, greenAmount, 0, 255);
                    set_current_dialogue_box_coords(7, 134, yOffset + 112, 186, yOffset + 137);
                    render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 7);
                    render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionVehicleTitleTexture, 136,
                                              yOffset + 114, 255, 255, 255, 255);

                    y = yOffset + 139;
                    savedY = y;

                    for (i = 0; i < 3; i++) {
                        alpha = (arg1 < 2 && get_map_default_vehicle(sp58) != (Vehicle) i) ? 128 : 255;
                        if ((1 << i) & mask) {
                            if (i == gPlayerSelectVehicle[0]) {
                                render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[i * 3 + 1], 104,
                                                          y, 255, 255, 255, 255);
                            } else {
                                render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[i * 3 + 2], 104,
                                                          y, 255, 255, 255, alpha);
                            }
                            y += 24;
                        }
                    }
                    y = savedY;
                    if (gPlayerSelectVehicle[0] == 2) {
                        y += 2;
                    }
                    render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[gPlayerSelectVehicle[0] * 3],
                                              149, y, 255, 255, 255, 255);
                    reset_render_settings(&sMenuCurrDisplayList);
                    gMenuImageStack[7].unkC = 21.0f;
                    gMenuImageStack[7].unk10 = -52.0f;
                    func_8009CA60(7);
                    if (gMenuOptionCount != 0) {
                        set_text_font(FONT_LARGE);
                        set_text_background_colour(0, 0, 0, 0);
                        set_text_colour(255, 255, 255, 0, 255);
                        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yOffset + 172, (char *) D_800E8240,
                                  ALIGN_MIDDLE_CENTER);
                    }
                } else {
                    set_text_font(FONT_LARGE);
                    set_text_background_colour(0, 0, 0, 0);
                    set_text_colour(255, 255, 255, 0, 255);
                    y = yOffset + 0xB0;
                    if (get_language() == LANGUAGE_FRENCH) {
                        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, y, gMenuText[13], ALIGN_MIDDLE_CENTER);
                        y += 32;
                    }
                    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, y, gMenuText[11], ALIGN_MIDDLE_CENTER);
                    y += 32;
                    if (get_language() != LANGUAGE_FRENCH) {
                        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, y, gMenuText[13], ALIGN_MIDDLE_CENTER);
                    }
                }
            }
        }
    }
}

/**
 * Process the logic for the track setup selection after entering a door in adventure mode.
 * This also includes drawing all the gui.
 */
s32 menu_adventure_track_loop(s32 updateRate) {
    s32 vehicle;
    s32 sp30;
    s32 vehicle2;
    s32 sp28;
    s32 mapId;
    s32 sp20;
    s32 sp1C;
    Settings *settings;

    if (gMenuOptionCount < 0) {
        return gTrackIdForPreview | 0x80;
    }
    settings = get_settings();
    mapId = ((Settings4C *) ((u8 *) settings->unk4C + gTrackIdForPreview))->unk2;
    sp28 = FALSE;
    sp1C = 0;
    if (settings->courseFlagsPtr[mapId] & RACE_CLEARED) {
        sp1C = 1;
    }
    if (settings->courseFlagsPtr[mapId] & RACE_CLEARED_SILVER_COINS) {
        sp1C = 2;
    }
    if (get_map_race_type(mapId) & RACETYPE_CHALLENGE) {
        sp28 = TRUE;
    }
    sp20 = FALSE;
    if (!is_time_trial_enabled()) {
        if (sp1C == 1) {
            if (settings->worldId == WORLD_FUTURE_FUN_LAND || (settings->bosses & (1 << settings->worldId))) {
                sp20 = TRUE;
            }
        }
    }
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    render_adventure_track_setup(updateRate, sp1C, sp20);
    if (sp1C < 2) {
        gPlayerSelectVehicle[PLAYER_ONE] = get_map_default_vehicle(mapId);
    }
    vehicle = gPlayerSelectVehicle[PLAYER_ONE];
    sp30 = get_map_available_vehicles(mapId);
    vehicle2 = vehicle;
    func_8008E4EC();
    if (gMenuDelay == 0) {
        if ((gMenuOptionCount != 0) || sp20 || sp28) {
            if (D_801267D8[0] & (A_BUTTON | START_BUTTON)) {
                if (sp28) {
                    set_current_text(0x2710);
                }
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
                sound_play(SOUND_SELECT2, NULL);
            } else if (D_801267D8[0] & B_BUTTON) {
                sound_play(SOUND_MENU_BACK3, NULL);
                if (sp20 || sp28) {
                    if (sp28) {
                        set_current_text(0x2710);
                    }
                    transition_begin(&sMenuTransitionFadeIn);
                    gMenuDelay = -1;
                } else {
                    gMenuOptionCount = 0;
                }
            }
        } else {
            if (D_801267D8[0] & B_BUTTON) {
                sound_play(SOUND_MENU_BACK3, NULL);
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = -1;
            } else if (D_801267D8[0] & (A_BUTTON | START_BUTTON)) {
                gMenuOptionCount = 1;
                sound_play(SOUND_CAR_REV2, NULL);
            } else if (sp1C >= 2) {
                if (D_80126830[0] > 0) {
                    do {
                        vehicle--;
                    } while (!((1 << vehicle) & sp30) && (vehicle >= 0));
                }
                if (D_80126830[0] < 0) {
                    do {
                        vehicle++;
                    } while (!((1 << vehicle) & sp30) && (vehicle < 3));
                }
                if ((vehicle < 0) || (vehicle >= 3)) {
                    vehicle = vehicle2;
                }
                if (vehicle != vehicle2) {
                    sound_play(SOUND_MENU_PICK2, NULL);
                    gPlayerSelectVehicle[PLAYER_ONE] = vehicle;
                }
            }
        }
    } else {
        if (gMenuDelay < 0) {
            gMenuDelay = gMenuDelay - updateRate;
        } else {
            gMenuDelay = gMenuDelay + updateRate;
        }
        if ((gMenuDelay >= 31) || (gMenuDelay < -30)) {
            func_80093A0C();
            if (gMenuDelay > 0) {
                return gTrackIdForPreview | 0x80;
            }
            return 0x103;
        }
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}

void func_80093A0C(void) {
    func_8009C4A8((s16 *) &gAdvTrackInitObjectIndices);
    unload_font(ASSET_FONTS_BIGFONT);
    music_change_on();
}

// Pause Menu
void func_80093A40(void) {
    s32 raceType;
    s32 i;
    Settings *settings;

    func_80072298(0);
    settings = get_settings();
    gLastPlayerWhoPaused = -1;

    for (i = 0; ((get_active_player_count() > i) && (gLastPlayerWhoPaused < 0)); i++) {
        if (get_buttons_held_from_player(i) & START_BUTTON) {
            gLastPlayerWhoPaused = i;
        }
    }
    if (gLastPlayerWhoPaused < 0) {
        gLastPlayerWhoPaused = 0;
    }
    gMenuOptionText[0] = gMenuText[ASSET_MENU_TEXT_CONTINUE];
    gMenuOptionCap = 1;
    if (gTrophyRaceWorldId == 0) {
        raceType = get_map_race_type(settings->courseId);
        if ((settings->worldId == WORLD_CENTRAL_AREA) && (is_taj_challenge() != 0)) {
            gMenuOptionText[1] = gMenuText[ASSET_MENU_TEXT_ABANDONCHALLENGE];
            gMenuOptionCap = 2;
        } else if ((settings->worldId > WORLD_CENTRAL_AREA) && (raceType != RACETYPE_BOSS)) {
            if (raceType & RACETYPE_CHALLENGE) {
                gMenuOptionText[1] = gMenuText[ASSET_MENU_TEXT_RESTARTCHALLENGE];
                gMenuOptionText[2] = (!gIsInTracksMode) ? gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY]
                                                        : gMenuText[ASSET_MENU_TEXT_SELECTTRACK];
                gMenuOptionCap = 3;
            } else if (raceType == RACETYPE_DEFAULT) {
                gMenuOptionText[1] = gMenuText[ASSET_MENU_TEXT_RESTARTRACE];
                gMenuOptionText[2] = (!gIsInTracksMode) ? gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY]
                                                        : gMenuText[ASSET_MENU_TEXT_SELECTTRACK];
                gMenuOptionCap = 3;
            }
        } else if ((!gIsInTracksMode) && (raceType == RACETYPE_BOSS)) {
            gMenuOptionText[1] = gMenuText[ASSET_MENU_TEXT_RESTARTRACE];
            gMenuOptionText[2] = gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY];
            gMenuOptionCap = 3;
        }
        if ((gIsInTracksMode == TRUE) && (gNumberOfActivePlayers == 1)) {
            gMenuOptionText[gMenuOptionCap++] = gMenuText[ASSET_MENU_TEXT_SELECTCHARACTER];
        }
        gMenuOptionText[gMenuOptionCap++] = gMenuText[ASSET_MENU_TEXT_QUITGAME];
    } else {
        gMenuOptionText[gMenuOptionCap++] = gMenuText[ASSET_MENU_TEXT_QUITTROPHYRACE];
    }
    gMenuOption = 0;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    gIgnorePlayerInputTime = 1;
    gMenuSubOption = 0;
    reset_controller_sticks();
}

void func_80093D40(UNUSED s32 updateRate) {
    ColourRGBA *colour;
    s32 halfTemp;
    s32 halfX;
    s32 x;
    s32 temp;
    s32 textWidth;
    s32 i;
    s32 y;
    s32 alpha;

    for (i = 0, x = SCREEN_WIDTH_HALF; i < gMenuOptionCap; i++) {
        textWidth = get_text_width(gMenuOptionText[i], 0, 0) + 8;
        if (x < textWidth) {
            x = textWidth;
        }
    }
    temp = (gMenuOptionCap * 16) + 28;
    if (osTvType == TV_TYPE_PAL) {
        y = SCREEN_HEIGHT_HALF_PAL;
    } else {
        y = SCREEN_HEIGHT_HALF;
    }
    clear_dialogue_box_open_flag(7);
    assign_dialogue_box_id(7);
    halfTemp = temp >> 1;
    halfX = x >> 1;
    set_current_dialogue_box_coords(7, SCREEN_WIDTH_HALF - halfX, y - halfTemp, halfX + 160, halfTemp + y);
    colour = &gPlayerPauseBgColour[get_player_id(gLastPlayerWhoPaused)];
    set_current_dialogue_background_colour(7, colour->r, colour->g, colour->b, colour->a);
    set_dialogue_font(7, ASSET_FONTS_FUNFONT);
    set_current_text_background_colour(7, 128, 128, 255, 0);
    colour = &gPlayerPauseOptionsTextColour[get_player_id(gLastPlayerWhoPaused)];
    set_current_text_colour(7, colour->r, colour->g, colour->b, colour->a, 255);
    alpha = gOptionBlinkTimer * 8;
    if (alpha > 255) {
        alpha = 511 - alpha;
    }
    if (gMenuSubOption != 0) {
        i = halfTemp - 26;
        if (gTrophyRaceWorldId != 0) {
            render_dialogue_text(7, POS_CENTRED, i + 8, gMenuText[ASSET_MENU_TEXT_QUITTROPHYRACETITLE], 1,
                                 ALIGN_MIDDLE_CENTER);
        } else {
            render_dialogue_text(7, POS_CENTRED, i + 8, gMenuText[ASSET_MENU_TEXT_QUITGAMETITLE], 1,
                                 ALIGN_MIDDLE_CENTER);
        }
        if (gMenuSubOption == 1) {
            set_current_text_colour(7, 255, 255, 255, alpha, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, POS_CENTRED, i + 28, gMenuText[ASSET_MENU_TEXT_OK], 1, ALIGN_MIDDLE_CENTER);
        if (gMenuSubOption == 2) {
            set_current_text_colour(7, 255, 255, 255, alpha, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, POS_CENTRED, i + 44, gMenuText[ASSET_MENU_TEXT_CANCEL], 1, ALIGN_MIDDLE_CENTER);
    } else {
        i = gLastPlayerWhoPaused + 1; // Fakematch. Seems to fix stuff?
        render_dialogue_text(7, POS_CENTRED, 12, gMenuText[ASSET_MENU_TEXT_PAUSEOPTIONS], gLastPlayerWhoPaused + 1,
                             ALIGN_MIDDLE_CENTER);
        for (i = 0, y = 32; i < gMenuOptionCap; i++, y += 16) {
            if (i == gMenuOption) {
                set_current_text_colour(7, 255, 255, 255, alpha, 255);
            } else {
                set_current_text_colour(7, 255, 255, 255, 0, 255);
            }
            render_dialogue_text(7, POS_CENTRED, y, gMenuOptionText[i], 1, ALIGN_MIDDLE_CENTER);
        }
    }
    open_dialogue_box(7);
}

/**
 * Show the available options when the player pauses the game.
 * Returns a different behaviour value depending on what's selected,
 * making the main game loop do different things.
 */
s32 render_pause_menu(UNUSED Gfx **dl, s32 updateRate) {
    s8 temp;
    s32 playerId;
    s32 buttonsPressed;

    if (gMenuOptionCap == 0) {
        sound_volume_change(VOLUME_NORMAL);
        return 0;
    }

    sound_volume_change(VOLUME_LOWER);
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    update_controller_sticks();

    buttonsPressed = 0;
    if (gIgnorePlayerInputTime == 0) {
        buttonsPressed = get_buttons_pressed_from_player(gLastPlayerWhoPaused);
    }

    if (gMenuDelay == 0) {
        if (gMenuSubOption != 0) {
            if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                sound_play(SOUND_SELECT2, NULL);
                if (gMenuSubOption == 1) {
                    gMenuDelay = 1;
                } else {
                    gMenuSubOption = 0;
                }
            } else if (buttonsPressed & B_BUTTON) {
                sound_play(SOUND_SELECT2, NULL);
                gMenuSubOption = 0;
            } else {
                temp = gMenuSubOption;
                playerId = gLastPlayerWhoPaused;
                if (gControllersYAxisDirection[playerId] != 0) {
                    gMenuSubOption = 3 - gMenuSubOption;
                }
                if (temp != gMenuSubOption) {
                    sound_play(SOUND_MENU_PICK2, NULL);
                }
            }
        } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            sound_play(SOUND_SELECT2, NULL);
            if ((gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_QUITGAME]) ||
                ((gTrophyRaceWorldId != 0) &&
                 (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_QUITTROPHYRACE]))) {
                gMenuSubOption = 2;
            } else {
                gMenuDelay = 1;
            }
        } else {
            temp = gMenuOption;
            playerId = gLastPlayerWhoPaused;
            buttonsPressed = gControllersYAxisDirection[playerId];
            if (buttonsPressed < 0) {
                gMenuOption++;
            }
            if (buttonsPressed > 0) {
                gMenuOption--;
            }
            if (gMenuOption < 0) {
                gMenuOption = gMenuOptionCap - 1;
            }
            if (gMenuOption >= gMenuOptionCap) {
                gMenuOption = 0;
            }
            if (temp != gMenuOption) {
                sound_play(SOUND_MENU_PICK2, NULL);
            }
        }
    } else {
        gMenuDelay++;
        if (gMenuDelay >= 4) {
            n_alSynRemovePlayer();
            if (gMenuSubOption == 1) {
                if (gTrophyRaceWorldId != 0) {
                    gTrophyRaceWorldId = 0;
                    if (gIsInTracksMode == 0) {
                        return 3;
                    }
                    return 5;
                }
                return 4;
            }
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_CONTINUE]) {
                sound_volume_change(VOLUME_NORMAL);
                return 1;
            }
            if ((gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_RESTARTRACE]) ||
                (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_RESTARTCHALLENGE])) {
                if ((gIsInTracksMode == 0) && (gTTVoiceLines[get_ingame_map_id()] != -1)) {
                    sound_play_delayed(gTTVoiceLines[get_ingame_map_id()], NULL, 1.0f);
                }
                return 2;
            }
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY]) {
                return 3;
            }
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_SELECTTRACK]) {
                return 5;
            }
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_SELECTCHARACTER]) {
                return 12;
            }
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_ABANDONCHALLENGE]) {
                sound_volume_change(VOLUME_NORMAL);
                return 7;
            }
            return 1;
        }
    }

    func_80093D40(updateRate);
    gIgnorePlayerInputTime = 0;
    return 0;
}

void n_alSynRemovePlayer(void) {
    func_80072298(1);
    close_dialogue_box(7);
    assign_dialogue_box_id(7);
    gMenuOptionCap = 0;
}

void n_alSeqpDelete(void) {
    n_alSynRemovePlayer();
}

/**
 * Set the racer portrait element textures for their respective characters.
 */
void assign_racer_portrait_textures(void) {
    gMenuPortraitKrunch[0].texture = gMenuObjects[TEXTURE_ICON_PORTRAIT_KRUNCH];
    gMenuPortraitDiddy[0].texture = gMenuObjects[TEXTURE_ICON_PORTRAIT_DIDDY];
    gMenuPortraitDrumstick[0].texture = gMenuObjects[TEXTURE_ICON_PORTRAIT_DRUMSTICK];
    gMenuPortraitBanjo[0].texture = gMenuObjects[TEXTURE_ICON_PORTRAIT_BANJO];
    gMenuPortraitBumper[0].texture = gMenuObjects[TEXTURE_ICON_PORTRAIT_BUMPER];
    gMenuPortraitConker[0].texture = gMenuObjects[TEXTURE_ICON_PORTRAIT_CONKER];
    gMenuPortraitTiptup[0].texture = gMenuObjects[TEXTURE_ICON_PORTRAIT_TIPTUP];
    gMenuPortraitTT[0].texture = gMenuObjects[TEXTURE_ICON_PORTRAIT_TT];
    gMenuPortraitPipsy[0].texture = gMenuObjects[TEXTURE_ICON_PORTRAIT_PIPSY];
    gMenuPortraitTimber[0].texture = gMenuObjects[TEXTURE_ICON_PORTRAIT_TIMBER];
}

void func_80094688(s32 arg0, s32 arg1) {
    s16 *var_v1;
    LevelHeader *header;

    func_80072298(0);
    header = get_current_level_header();
    D_80126C28 = arg0;
    if (is_in_two_player_adventure()) {
        set_scene_viewport_num(VIEWPORTS_COUNT_1_PLAYER);
    }
    D_80126A90 = FALSE;
    if (gNumberOfActivePlayers == 1 && gTrophyRaceWorldId == 0) {
        if (is_in_tracks_mode() == TRUE) {
            gResultOptionText[0] = gMenuText[ASSET_MENU_TEXT_TRYAGAIN];
            gResultOptionText[1] = gMenuText[ASSET_MENU_TEXT_SELECTTRACK];
            gResultOptionText[2] = gMenuText[ASSET_MENU_TEXT_SELECTCHARACTER];
            gResultOptionCount = 3;
            D_80126A90 = TRUE;
        } else {
            if (arg0 == 0) {
                gResultOptionText[0] = gMenuText[ASSET_MENU_TEXT_TRYAGAIN];
                gResultOptionCount = 1;
            } else {
                gResultOptionCount = 0;
            }
            gResultOptionText[gResultOptionCount] = gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY];
            gResultOptionCount++;
        }
        gResultOptionText[gResultOptionCount] = gMenuText[ASSET_MENU_TEXT_QUIT];
        gResultOptionCount++;
        gMenuOptionCount = 0;
    } else {
        gMenuOptionCount = 7;
    }
    D_80126CC0 = FALSE;
    gOptionBlinkTimer = 0;
    gOpacityDecayTimer = 0;
    gMenuDelay = 0;
    gMenuCurIndex = 0;
    gMenuOption = 0;
    gIgnorePlayerInputTime = 1;
    D_80126C54.unk0_s32 = -1;
    gMenuSubOption = 0;
    D_80126C1C = NULL;
    D_80126A98 = 0;
    if (header->race_type & RACETYPE_CHALLENGE) {
        gIgnorePlayerInputTime = normalise_time(240); // 4 seconds
    }
    if (D_80126C28) {
        gMenuOptionCount = 8;
        gMenuDelay = 100;
    }
    if (get_game_mode() != GAMEMODE_INGAME) {
        gMenuOptionCount = 7;
    }
    reset_controller_sticks();
    func_8006D8E0(arg0);
    gTrackSelectViewPortX = get_video_width_and_height_as_s32();
    gTrackSelectViewportY = GET_VIDEO_HEIGHT(gTrackSelectViewPortX) & 0xFFFF;
    gTrackSelectViewPortX = GET_VIDEO_WIDTH(gTrackSelectViewPortX);
    gTrackSelectViewPortHalfX = gTrackSelectViewPortX >> 1;
    gTrackSelectViewPortHalfY = gTrackSelectViewportY >> 1;
    if ((gNumberOfActivePlayers == 1) && (gTrophyRaceWorldId == 0)) {
        D_80126C54.unk0_s32 = 0;
        arg1 = (s8) header->world - 1;
        var_v1 = &gTracksMenuBgTextureIndices[arg1 * 3];
        if (var_v1[0] != -1) {
            func_8009C6D4(var_v1[0]);
            D_80126BB8 = gMenuObjects[var_v1[0]];
        } else {
            D_80126BB8 = 0;
        }
        if (var_v1[1] != -1) {
            func_8009C6D4(var_v1[1]);
            D_80126BBC = gMenuObjects[var_v1[1]];
        } else {
            D_80126BBC = 0;
        }
        D_80126BC0 = var_v1[2];
        if (get_game_mode() == GAMEMODE_INGAME) {
            func_80078170(D_80126BB8, D_80126BBC, D_80126BC0);
        }
        camEnableUserView(0, 1);
        viewport_menu_set(0, 0, 0, gTrackSelectViewPortX, gTrackSelectViewportY);
    }
    sound_volume_change(VOLUME_LOWER_AMBIENT);
}

void func_80094A5C(void) {
    UNUSED s32 pad[2];
    Settings *settings;
    s16 temp_a0;
    s32 i;
    s32 j;

    if (D_80126C54.unk0_s32 >= 0) {
        if (D_80126C54.unk0_s32 < 10) {
            D_80126C54.unk0_s32++;
            return;
        }
        temp_a0 = D_800E0A10[D_80126C54.unk0_s32];
        if (temp_a0 == -1) {
            allocate_menu_images(gRaceResultsImageIndices);
            assign_racer_portrait_textures();
            settings = get_settings();
            gRaceResultsMenuElements->unk14_a.element =
                gRacerPortraits[settings->racers[settings->timeTrialRacer].character];
            if (!is_time_trial_enabled()) {
                for (i = 0; i < 8; i++) {
                    for (j = 0; j < 8; j++) {
                        if (i == settings->racers[j].starting_position) {
                            gRaceOrderMenuElements[7 - i].unk14_a.element =
                                gRacerPortraits[settings->racers[j].character];
                        }
                    }
                }
                if (is_in_two_player_adventure()) {
                    for (i = 0; i < 6; i++) {
                        gRaceOrderMenuElements[i + 1].unk14_a.element = gRaceOrderMenuElements[i + 2].unk14_a.element;
                    }
                    gRaceOrderMenuElements[7].unk14_a.element = &D_80126850;
                    gRaceOrderMenuElements[0].unk14_a.element = &D_80126850;
                }
            }
            D_80126C54.unk0_s32 = -1;
            return;
        }
        func_8009C6D4(temp_a0);
        D_80126C54.unk0_s32++;
    }
}

void func_80094C14(s32 updateRate) {
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    D_80126A94 += updateRate;
    if (gOpacityDecayTimer >= 0) {
        gOpacityDecayTimer += updateRate;
        switch (gMenuCurIndex) {
            case 0:
                if (normalise_time(240) < gOpacityDecayTimer) {
                    music_fade(-256);
                    gMenuCurIndex = 1;
                }
                break;
            case 1:
                if (normalise_time(300) < gOpacityDecayTimer) {
                    music_voicelimit_set(24);
                    music_play(SEQUENCE_MAIN_MENU);
                    music_fade(256);
                }
                break;
        }
        if (normalise_time(300) < gOpacityDecayTimer) {
            gOpacityDecayTimer = -1;
        }
    }
}

#ifdef NON_MATCHING
void func_80094D28(UNUSED s32 updateRate) {
    s32 y;
    s32 textAlpha;
    s32 viewportULX;
    s32 viewportLRY;
    s32 viewportULY;
    Settings *settings;
    s32 j;
    s32 i;
    s32 sp3C;
    s32 temp;

    settings = get_settings();
    if (gNumberOfActivePlayers == 1) {
        set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    }
    camDisableUserView(0, TRUE);
    textAlpha = gOptionBlinkTimer * 8;
    if (textAlpha > 255) {
        textAlpha = 511 - textAlpha;
    }
    switch (gMenuOptionCount) {
        case 1:
            temp = D_80126A94;
            if (temp > 60) {
                temp = 60;
            }
            viewportULY = ((gTrackSelectViewPortHalfY - ((gTrackSelectViewPortHalfY * 4) / 5)) * temp) / 60;
            viewportLRY =
                gTrackSelectViewportY - (((gTrackSelectViewPortHalfY - (gTrackSelectViewPortHalfY / 5)) * temp) / 60);
            viewportULX = (temp * 80) / 60;
            viewport_menu_set(0, viewportULX, viewportULY, SCREEN_WIDTH - viewportULX, viewportLRY);
            gMenuImageStack[4].unkC = 0.0f;
            gMenuImageStack[4].unk10 = gTrackSelectViewPortHalfY - ((viewportULY + viewportLRY) >> 1);
            gMenuImageStack[4].unk8 = sMenuImageProperties[4].unk8 * (2.0f - (temp / 60.0f));
            break;
        case 2:
            for (i = 0; i < 3; i++) {
                if (settings->display_times && settings->racers[0].best_times & (1 << i)) {
                    gRaceResultsMenuElements[i + 3].filterGreen = 192 - ((textAlpha * 3) >> 2);
                    gRaceResultsMenuElements[i + 3].filterBlue = 255 - textAlpha;
                } else {
                    gRaceResultsMenuElements[i + 3].filterGreen = 192;
                    gRaceResultsMenuElements[i + 3].filterBlue = 255;
                }
            }
            if (settings->display_times && settings->racers[0].best_times & (1 << 7)) {
                gRaceResultsMenuElements[6].filterRed = (textAlpha >> 1) + 128;
                gRaceResultsMenuElements[6].filterGreen = 255 - textAlpha;
                gRaceResultsMenuElements[6].filterBlue = 255 - textAlpha;
            } else {
                gRaceResultsMenuElements[6].filterRed = 128;
                gRaceResultsMenuElements[6].filterGreen = 255;
                gRaceResultsMenuElements[6].filterBlue = 255;
            }
            break;
        case 3:
            for (j = 0; j < 8; j++) {
                i = j;
                sp3C = 255;
                if (is_in_two_player_adventure()) {
                    i = j - 1;
                    if (i == settings->racers[1].starting_position) {
                        sp3C = (textAlpha >> 1) + 128;
                    }
                }
                if (i == settings->racers[0].starting_position) {
                    sp3C = (textAlpha >> 1) + 128;
                }
                if (y) {} // Fake
                gRaceOrderMenuElements[7 - j].filterRed = sp3C;
                gRaceOrderMenuElements[7 - j].filterGreen = sp3C;
                gRaceOrderMenuElements[7 - j].filterBlue = sp3C;
            }
            break;
        case 5:
            if (settings->display_times && settings->racers[0].best_times & (s8) ~(1 << 7)) {
                gRecordTimesMenuElements[6].filterRed = 255;
                gRecordTimesMenuElements[6].filterGreen = 192 - ((textAlpha * 3) >> 2);
                gRecordTimesMenuElements[6].filterBlue = 255 - textAlpha;
            } else {
                gRecordTimesMenuElements[6].filterRed = 255;
                gRecordTimesMenuElements[6].filterGreen = 192;
                gRecordTimesMenuElements[6].filterBlue = 255;
            }
            if (settings->display_times && settings->racers[0].best_times & (1 << 7)) {
                gRecordTimesMenuElements[3].filterRed = (textAlpha >> 1) + 128;
                gRecordTimesMenuElements[3].filterGreen = 255 - textAlpha;
                gRecordTimesMenuElements[3].filterBlue = 255 - textAlpha;
            } else {
                gRecordTimesMenuElements[3].filterRed = 128;
                gRecordTimesMenuElements[3].filterGreen = 255;
                gRecordTimesMenuElements[3].filterBlue = 255;
            }
            break;
        case 6:
            clear_dialogue_box_open_flag(7);
            assign_dialogue_box_id(7);
            set_dialogue_font(7, FONT_COLOURFUL);
            set_current_text_background_colour(7, 0, 0, 0, 0);

            if (D_80126A98 != 0) {
                temp = 1;
            } else if (D_80126C1C != NULL) {
                temp = D_80126C24;
            } else {
                temp = gResultOptionCount;
            }
            if (temp >= 5) {
                viewportULX = 2;
                viewportLRY = 13;
            } else {
                viewportULX = 0;
                viewportLRY = 16;
            }
            viewportULY = ((temp * viewportLRY) + 1) >> 1;
            temp = 192;
            if (osTvType == TV_TYPE_PAL) {
                temp = 218;
            }
            set_current_dialogue_box_coords(7, 0, temp - viewportULY - viewportULX - 4, SCREEN_WIDTH,
                                            temp + viewportULY + viewportULX + 4);
            set_current_dialogue_background_colour(7, 64, 64, 255, 0);
            set_current_text_colour(7, 255, 0, 255, 64, 255);
            if (D_80126A98 != 0) {
                render_dialogue_text(7, POS_CENTRED, 12, gMenuText[ASSET_MENU_TEXT_PLEASEWAIT], 1, ALIGN_MIDDLE_CENTER);
            } else if (D_80126C1C != NULL) {
                for (y = 12, temp = 0; temp < D_80126C24; temp++, y += viewportLRY) {
                    render_dialogue_text(7, POS_CENTRED, y, D_80126C1C[temp], 1, ALIGN_MIDDLE_CENTER);
                }
            } else {
                if (y && y) {} // fake
                viewportULY -= 24;
                if (gMenuSubOption != 0) {
                    render_dialogue_text(7, POS_CENTRED, viewportULY + 8, gMenuText[ASSET_MENU_TEXT_QUITGAMETITLE], 1,
                                         ALIGN_MIDDLE_CENTER);
                    temp = 0;
                    if (gMenuSubOption == 1) {
                        temp = textAlpha;
                    }
                    set_current_text_colour(7, 255, 255, 255, temp, 255);
                    render_dialogue_text(7, POS_CENTRED, viewportULY + 26, gMenuText[ASSET_MENU_TEXT_OK], 1,
                                         ALIGN_MIDDLE_CENTER);
                    temp = 0;
                    if (gMenuSubOption == 2) {
                        temp = textAlpha;
                    }
                    set_current_text_colour(7, 255, 255, 255, temp, 255);
                    render_dialogue_text(7, POS_CENTRED, viewportULY + 42, gMenuText[ASSET_MENU_TEXT_CANCEL], 1,
                                         ALIGN_MIDDLE_CENTER);
                } else {
                    for (y = 12, temp = 0; temp < gResultOptionCount; temp++, y += viewportLRY) {
                        if (temp == gMenuOption) {
                            set_current_text_colour(7, 255, 255, 255, textAlpha, 255);
                        } else {
                            set_current_text_colour(7, 255, 255, 255, 0, 255);
                        }
                        render_dialogue_text(7, SCREEN_WIDTH_HALF, y, gResultOptionText[temp], 1, ALIGN_MIDDLE_CENTER);
                    }
                }
            }
            open_dialogue_box(7);
            break;
    }
    if (get_game_mode() == GAMEMODE_INGAME && gNumberOfActivePlayers == 1) {
        if (gTrophyRaceWorldId == 0) {
            camEnableUserView(0, TRUE);
            if (osTvType == TV_TYPE_PAL) {
                gTrackSelectWoodFrameHeightScale = 1.2f;
            }
            if (gMenuOptionCount > 0) {
                func_8009CA60(4);
            }
            gTrackSelectWoodFrameHeightScale = 1.0f;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80094D28.s")
#endif

void func_80095624(SIDeviceStatus status) {
    // status may contain controllerIndex in it's upper bits
    // so grab the lower bits for the SIDeviceStatus

    // clang-format off
    switch (status & 0xFF) {
        case CONTROLLER_PAK_NOT_FOUND:
        case CONTROLLER_PAK_CHANGED: /*Required to match*/ \
            D_80126C1C = sNoControllerPakMenuText;
            break;
        case CONTROLLER_PAK_FULL:
        case CONTROLLER_PAK_NO_ROOM_FOR_GHOSTS: /*Required to match*/ \
            D_80126C1C = sControllerPakFullMenuText;
            break;
        case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
            // If you wish to use / the Controller Pak / insert it now!
            D_80126C1C = sInsertControllerPakMenuText;
            break;
        case CONTROLLER_PAK_SWITCH_TO_RUMBLE:
            // If you wish to use / the Rumble Pak / insert it now!
            D_80126C1C = sInsertRumblePakMenuText;
            break;
        case CONTROLLER_PAK_BAD_DATA:
            D_80126C1C = sCorruptDataMenuText;
            break;
        default:
            D_80126C1C = sBadControllerPakMenuText;
            break;
    }
    // clang-format on

    for (D_80126C24 = 0; D_80126C1C[D_80126C24] != 0; D_80126C24++) {}
}

s32 func_80095728(Gfx **dlist, MatrixS **matrices, Vertex **vertices, s32 updateRate) {
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 i;
    s32 ret;
    s32 buttonsPressed;
    s32 prevMenuOption;
    s32 sp38;
    s32 sp34;
    s32 numPlayers;
    Settings *settings;
    Racer *racer;
    char *temp_v1_14;

    sp54 = 0;
    sp50 = 0;
    sp4C = 0;
    ret = 0;
    sMenuCurrDisplayList = *dlist;
    sMenuCurrHudMat = *matrices;
    sMenuCurrHudVerts = *vertices;
    settings = get_settings();
    if (osTvType == TV_TYPE_PAL) {
        sp38 = 26;
        sp34 = 12;
    } else {
        sp38 = 0;
        sp34 = 0;
    }
    numPlayers = gNumberOfActivePlayers;
    if (is_in_two_player_adventure()) {
        numPlayers = 2;
    }
    if (D_80126A90) {
        if (has_ghost_to_save()) {
            gResultOptionText[gResultOptionCount - 1] = gMenuText[ASSET_MENU_TEXT_SAVEGHOST];
            gResultOptionText[gResultOptionCount] = gMenuText[ASSET_MENU_TEXT_QUIT];
            gResultOptionCount++;
        }
        D_80126A90 = FALSE;
    }
    func_80094A5C();
    func_80094C14(updateRate);
    if (gMenuDelay < 20 && D_80126C28 == 0) {
        if (D_80126C54.unk0_s32 < 0) {
            func_80094D28(updateRate);
        }
    } else {
        func_80078170(NULL, NULL, 0);
    }
    update_controller_sticks();
    buttonsPressed = 0;
    if (gIgnorePlayerInputTime == FALSE && D_80126C54.unk0_s32 < 0) {
        for (i = 0; i < numPlayers; i++) {
            buttonsPressed |= get_buttons_pressed_from_player(i);
        }
    }
    switch (gMenuOptionCount) {
        case 0:
            if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                gMenuOptionCount = 1;
                D_80126A94 = 0;
            }
            break;
        case 1:
            if (D_80126A94 > 60 || buttonsPressed & (A_BUTTON | START_BUTTON)) {
                viewport_menu_set(0, 80, gTrackSelectViewPortHalfY - ((gTrackSelectViewPortHalfY * 4) / 5),
                                  SCREEN_HEIGHT, (gTrackSelectViewPortHalfY / 5) + gTrackSelectViewPortHalfY);
                gMenuImageStack[4].unkC = 0.0f;
                gMenuImageStack[4].unk10 = 36.0f;
                gMenuImageStack[4].unk8 = sMenuImageProperties[4].unk8;
                if (get_map_race_type(settings->courseId) & RACETYPE_CHALLENGE) {
                    gMenuOptionCount = 6;
                } else if (!settings->display_times) {
                    func_80081E54(gRaceOrderMenuElements, 0.5f, 15.0f, 0.5f, sp38, sp34);
                    gMenuOptionCount = 3;
                } else {
                    racer = &settings->racers[settings->timeTrialRacer];
                    gRaceResultsMenuElements[3].unk14_a.numberU16 = &racer->lap_times[0];
                    gRaceResultsMenuElements[4].unk14_a.numberU16 = &racer->lap_times[1];
                    gRaceResultsMenuElements[5].unk14_a.numberU16 = &racer->lap_times[2];
                    gRaceResultsMenuElements[6].unk14_a.numberU16 = &racer->course_time;
                    func_80081E54(gRaceResultsMenuElements, 0.5f, 15.0f, 0.5f, sp38, sp34);
                    gMenuOptionCount = 2;
                }
            }
            break;
        case 2:
            if (func_80081F4C(updateRate) != 0) {
                if (gTrophyRaceWorldId != 0) {
                    music_fade(-128);
                    transition_begin(&sMenuTransitionFadeIn);
                    gMenuOptionCount = 8;
                } else if (settings->display_times) {
                    gRecordTimesMenuElements[3].unk14_a.numberU16 =
                        &settings->courseTimesPtr[*gPlayerSelectVehicle][settings->courseId];
                    gRecordTimesMenuElements[6].unk14_a.numberU16 =
                        &settings->flapTimesPtr[*gPlayerSelectVehicle][settings->courseId];
                    decompress_filename_string(settings->courseInitialsPtr[*gPlayerSelectVehicle][settings->courseId],
                                               D_80126390, 3);
                    decompress_filename_string(settings->flapInitialsPtr[*gPlayerSelectVehicle][settings->courseId],
                                               D_80126394, 3);
                    if (settings->racers[0].best_times != 0) {
                        gMenuOptionCount = 4;
                        if ((gIsInTracksMode == 0) && (D_800E0FAC)) {
                            decompress_filename_string(settings->filename, gCheckAdvEnterInitials, 3);
                            D_800E0FAC = 0;
                        }
                        func_80097874(sp38 + 196, 160, sp38 + 120, 2, &D_800E0FA4, gCheckAdvEnterInitials, 3);
                    } else {
                        func_80081E54(gRecordTimesMenuElements, 0.5f, 15.0f, 0.5f, sp38, sp34);
                        gMenuOptionCount = 5;
                    }
                } else {
                    gMenuOptionCount = 3;
                    func_80081E54(gRaceOrderMenuElements, 0.5f, 15.0f, 0.5f, sp38, sp34);
                }
            }
            break;
        case 3:
            if (func_80081F4C(updateRate) != 0) {
                gMenuOptionCount = 6;
            }
            break;
        case 4:
            if (menu_enter_filename_loop(updateRate) != 0) {
                if (settings->racers[0].best_times & 0x7F) {
                    settings->flapInitialsPtr[*gPlayerSelectVehicle][settings->courseId] =
                        compress_filename_string(gCheckAdvEnterInitials, 3);
                    decompress_filename_string(settings->flapInitialsPtr[*gPlayerSelectVehicle][settings->courseId],
                                               D_80126394, 3);
                }
                if (settings->racers[0].best_times & 0x80) {
                    settings->courseInitialsPtr[*gPlayerSelectVehicle][settings->courseId] =
                        compress_filename_string(gCheckAdvEnterInitials, 3);
                    decompress_filename_string(settings->courseInitialsPtr[*gPlayerSelectVehicle][settings->courseId],
                                               D_80126390, 3);
                }
                func_80081E54(gRecordTimesMenuElements, 0.5f, 15.0f, 0.5f, sp38, sp34);
                gMenuOptionCount = 5;
            }
            break;
        case 5:
            if (func_80081F4C(updateRate) != 0) {
                gMenuOptionCount = 6;
            }
            break;
        case 6:
            if (D_80126A98 != 0) {
                D_80126A98++;
                if (D_80126A98 >= 5) {
                    sound_volume_change(3);
                    sp54 = func_8001B738(0);
                    if ((sp54 & 0xFF) == 5) {
                        sp54 = func_8001B738(0);
                    }
                    sound_volume_change(2);
                    if (sp54 != 0) {
                        func_80095624(sp54);
                        sp54 = 1;
                    } else {
                        if (D_80126C1C == sInsertControllerPakMenuText) {
                            func_80095624(CONTROLLER_PAK_SWITCH_TO_RUMBLE);
                        } else {
                            D_80126C1C = NULL;
                        }
                        gResultOptionText[gMenuOption] = gMenuText[28];
                        gMenuOption = 0;
                        gResultOptionCount -= 1;
                    }
                    D_80126A98 = 0;
                }
            } else if (D_80126C1C != NULL) {
                if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                    sp50 = 1;
                    if (D_80126C1C == sInsertControllerPakMenuText) {
                        D_80126A98 = 1;
                    } else {
                        D_80126C1C = NULL;
                    }
                } else if (buttonsPressed & B_BUTTON) {
                    D_80126C1C = NULL;
                    sp54 = 1;
                }
            } else {
                if (gMenuSubOption != 0) {
                    if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                        if (gMenuSubOption == 1) {
                            sp50 = 1;
                            music_fade(-128);
                            transition_begin(&sMenuTransitionFadeIn);
                            gMenuOptionCount = 8;
                        } else {
                            sp54 = 1;
                            gMenuSubOption = 0;
                        }
                    } else {
                        prevMenuOption = gMenuSubOption;
                        if (buttonsPressed & B_BUTTON) {
                            sp54 = 1;
                            gMenuSubOption = 0;
                        } else {
                            for (i = 0; i < numPlayers; i++) {
                                if ((gControllersYAxisDirection[i] > 0) && (gMenuSubOption == 2)) {
                                    gMenuSubOption = 1;
                                }
                                if ((gControllersYAxisDirection[i] < 0) && (gMenuSubOption == 1)) {
                                    gMenuSubOption = 2;
                                }
                            }
                            if (prevMenuOption != gMenuSubOption) {
                                sp4C = 1;
                            }
                        }
                    }
                } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                    sp50 = 1;
                    temp_v1_14 = gResultOptionText[gMenuOption];
                    if (temp_v1_14 == gMenuText[ASSET_MENU_TEXT_SAVEGHOST]) {
                        D_80126A98 = 1;
                    } else if (temp_v1_14 == gMenuText[ASSET_MENU_TEXT_QUIT]) {
                        gMenuSubOption = 2;
                    } else {
                        music_fade(-128);
                        transition_begin(&sMenuTransitionFadeIn);
                        gMenuOptionCount = 8;
                    }
                } else {
                    prevMenuOption = gMenuOption;
                    for (i = 0; i < numPlayers; i++) {
                        if (gControllersYAxisDirection[i] < 0) {
                            if (gMenuOption < (gResultOptionCount - 1)) {
                                gMenuOption++;
                            }
                        }
                        if (gControllersYAxisDirection[i] > 0) {
                            if (gMenuOption > 0) {
                                gMenuOption--;
                            }
                        }
                    }
                    if (prevMenuOption != gMenuOption) {
                        sp4C = 1;
                    }
                }
            }
            if (sp54 != 0) {
                sound_play(SOUND_MENU_BACK3, NULL);
            } else if (sp50 != 0) {
                sound_play(SOUND_SELECT2, NULL);
            } else if (sp4C != 0) {
                sound_play(SOUND_MENU_PICK2, NULL);
            }
            break;
        case 7:
            if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                music_fade(-128);
                transition_begin(&sMenuTransitionFadeIn);
                gMenuOptionCount = 8;
            }
            break;
        case 8:
            gMenuDelay += updateRate;
            if (gMenuDelay > 30) {
                if (settings->display_times) {
                    if (settings->racers[0].best_times & 0x7F) {
                        mark_to_write_flap_times();
                    }
                    if (settings->racers[0].best_times & 0x80) {
                        mark_to_write_course_times();
                    }
                }
                camDisableUserView(0, FALSE);
                func_80096790();
                close_dialogue_box(7);
                assign_dialogue_box_id(7);
                if (D_80126C28 >= 2) {
                    if (D_80126C28 == 9) {
                        func_8009ABD8((s8 *) get_misc_asset(ASSET_MISC_25), D_80126C28, 0x10E, 0, 0, NULL);
                    } else {
                        func_8009ABD8((s8 *) get_misc_asset(ASSET_MISC_25), D_80126C28, 0x101, 0, 0, NULL);
                    }
                    ret = 13;
                } else if ((gTrophyRaceWorldId != 0)) {
                    ret = 10;
                } else if ((gNumberOfActivePlayers >= 2)) {
                    ret = 8;
                } else {
                    temp_v1_14 = gResultOptionText[gMenuOption];
                    if (temp_v1_14 == gMenuText[ASSET_MENU_TEXT_TRYAGAIN]) {
                        if (!gIsInTracksMode && gTTVoiceLines[get_ingame_map_id()] != -1) {
                            sound_play_delayed(gTTVoiceLines[get_ingame_map_id()], NULL, 1.0f);
                        }
                        ret = 2;
                    } else if (temp_v1_14 == gMenuText[ASSET_MENU_TEXT_SELECTTRACK]) {
                        ret = 5;
                    } else if (temp_v1_14 == gMenuText[ASSET_MENU_TEXT_SELECTCHARACTER]) {
                        ret = 12;
                    } else if (temp_v1_14 == gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY]) {
                        ret = 1;
                    } else {
                        ret = 4;
                    }
                }
            }
            break;
    }
    if (gIgnorePlayerInputTime > 0) {
        gIgnorePlayerInputTime -= updateRate;
        if (gIgnorePlayerInputTime < 0) {
            gIgnorePlayerInputTime = 0;
        }
    }
    *dlist = sMenuCurrDisplayList;
    *matrices = sMenuCurrHudMat;
    *vertices = sMenuCurrHudVerts;
    return ret;
}

void func_80096790(void) {
    s32 temp;
    s8 *temp2;

    temp2 = (s8 *) get_current_level_header();
    func_8009C4A8(gRaceResultsObjectIndices);
    temp = *temp2 - 1;

    if (D_80126BB8) {
        func_8009C508(gTracksMenuBgTextureIndices[temp * 3]);
    }
    D_80126BB8 = 0;

    if (D_80126BBC) {
        func_8009C508(gTracksMenuBgTextureIndices[(temp * 3) + 1]);
    }
    D_80126BBC = 0;

    unload_big_font_4();
    sound_volume_change(VOLUME_NORMAL);
}

/**
 * Initialise the race results menu.
 * Set the text for the options and set the order of the racer portraits based on finishing position.
 */
void menu_results_init(void) {
    Settings *settings;
    u16 *placements;
    s32 i;
    s8 startPos;

    settings = get_settings();
    gResultOptionText[0] = gMenuText[ASSET_MENU_TEXT_SELECTTRACK];
    gResultOptionText[1] = gMenuText[ASSET_MENU_TEXT_TRYAGAIN];
    gResultOptionText[2] = gMenuText[ASSET_MENU_TEXT_QUIT];
    gResultOptionCount = 3;

    for (i = 0; i < gNumberOfActivePlayers; i++) {
        startPos = settings->racers[i].starting_position;
        if (startPos < 4) {
            placements = settings->racers[i].placements;
            placements[startPos]++;
        }
    }

    gMenuOptionCount = -1;
    gOptionBlinkTimer = 0;
    gOpacityDecayTimer = 0;
    gMenuDelay = 0;
    gMenuOption = 0;
    gIgnorePlayerInputTime = 1;
    gMenuSubOption = 0;
    func_8009C674(gRaceResultsObjectIndices);
    allocate_menu_images(gRaceResultsImageIndices);
    assign_racer_portrait_textures();
    load_font(ASSET_FONTS_BIGFONT);
    transition_begin(&sMenuTransitionFadeOut);
    music_voicelimit_set(24);
    music_play(SEQUENCE_MAIN_MENU);
    music_fade(128);
}

void func_80096978(UNUSED s32 updateRate, f32 opacity) {
    s32 x2;
    s32 y2;
    s32 spA4;
    s32 spA0;
    s32 time;
    s32 sp98;
    s32 hundredths;
    s32 tens;
    UNUSED s32 pad;
    s32 i;
    Settings *settings;

    settings = get_settings();
    sp98 = 0;
    if (osTvType == TV_TYPE_PAL) {
        sp98 = 12;
    }
    set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (opacity < 0.0f) {
        opacity = 0.0f;
    }
    if (opacity > 1.0f) {
        opacity = 1.0f;
    }
    sMenuGuiOpacity = (1 - opacity) * 255;
    set_text_font(2);
    set_text_background_colour(0, 0, 0, 0);
    set_text_colour(255, 255, 255, 0, sMenuGuiOpacity);
    draw_text(&sMenuCurrDisplayList, POS_CENTRED, 34, gMenuText[ASSET_MENU_TEXT_RANKINGS], ALIGN_MIDDLE_CENTER);
    sMenuGuiOpacity = 255;
    spA4 = 160 - ((gNumberOfActivePlayers - 1) << 5);
    x2 = spA4;

    for (i = 0; i < gNumberOfActivePlayers; i++) {
        if (settings->racers[i].starting_position == 0) {
            if (gOptionBlinkTimer < 32) {
                spA0 = (gOptionBlinkTimer * 4) + 128;
            } else {
                spA0 = 0x17F - (gOptionBlinkTimer * 4);
            }
        } else {
            spA0 = 255;
        }
        render_textured_rectangle(&sMenuCurrDisplayList, gRacerPortraits[settings->racers[i].character], x2 - 20,
                                  54 - (s32) (240 * opacity), spA0, spA0, spA0, 255);
        x2 += 64;
    }

    spA4 = spA4 + (s32) (320 * opacity); // Cannot use += here?
    set_text_font(ASSET_FONTS_FUNFONT);
    y2 = 0x68;
    for (spA0 = 0; spA0 < 4; spA0++) {
        time = spA4;
        set_text_colour(0, 0, 0, 255, 255);
        draw_text(&sMenuCurrDisplayList, time - 32, y2 + sp98 + 4, gRacePlacementsArray[spA0], ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 255, 192, 96, 255);
        draw_text(&sMenuCurrDisplayList, time - 34, y2 + sp98 + 2, gRacePlacementsArray[spA0], ALIGN_MIDDLE_CENTER);
        reset_render_settings(&sMenuCurrDisplayList);
        func_80068508(TRUE);
        sprite_opaque(FALSE);
        sMenuGuiColourR = 255;
        sMenuGuiColourG = 255 - 64 * spA0;
        sMenuGuiColourB = 255;
        sMenuGuiColourBlendFactor = 255;
        x2 = spA4;
        for (i = 0; i < gNumberOfActivePlayers; i++, x2 += 64) {
            time = settings->racers[i].placements[spA0]; // Is this local var name correct?
            if (time > 999) {
                time = 999;
            }
            hundredths = time / 100;
            time -= (hundredths * 100);
            tens = time / 10;
            time -= tens * 10;

            // I'm 99% sure these need to be gMenuImageStack[0]
            // Changing it to gMenuImageStack[spA0] or gMenuImageStack[i] makes the score worse.
            gMenuImageStack[0].unk10 = (SCREEN_HEIGHT_HALF - y2);
            if (hundredths > 0) {
                gMenuImageStack[0].unkC = (x2 - 172);
                gMenuImageStack[0].unk18 = hundredths;
                func_8009CA60(0);
                gMenuImageStack[0].unkC += 12.0f;
                gMenuImageStack[0].unk18 = tens;
                func_8009CA60(0);
                gMenuImageStack[0].unkC += 12.0f;
            } else if (tens > 0) {
                gMenuImageStack[0].unkC = (x2 - 166);
                gMenuImageStack[0].unk18 = tens;
                func_8009CA60(0);
                gMenuImageStack[0].unkC += 12.0f;
            } else {
                gMenuImageStack[0].unkC = (x2 - 160);
            }
            gMenuImageStack[0].unk18 = time;
            func_8009CA60(0);
        }
        y2 = y2 + 17;
        func_80068508(FALSE);
        sprite_opaque(TRUE);
        sMenuGuiColourG = 255;
        sMenuGuiColourBlendFactor = 0;
    }
    if (gMenuOptionCount > 0) {
        y2 = gResultOptionCount * 8;
        clear_dialogue_box_open_flag(7);
        assign_dialogue_box_id(7);
        set_current_dialogue_box_coords(7, 80, (sp98 - y2) + 196, 240, y2 + sp98 + 204);
        set_current_dialogue_background_colour(7, 64, 64, 255, 0);
        set_dialogue_font(7, 0);
        set_current_text_background_colour(7, 0, 0, 0, 0);
        spA0 = gOptionBlinkTimer * 8;
        if (spA0 > 255) {
            spA0 = 511 - spA0;
        }
        if (gMenuSubOption != 0) {
            y2 -= 24;
            render_dialogue_text(7, POS_CENTRED, y2 + 8, gMenuText[ASSET_MENU_TEXT_QUITGAMETITLE], 1,
                                 ALIGN_MIDDLE_CENTER);
            if (gMenuSubOption == 1) {
                set_current_text_colour(7, 255, 255, 255, spA0, 255);
            } else {
                set_current_text_colour(7, 255, 255, 255, 0, 255);
            }
            render_dialogue_text(7, POS_CENTRED, y2 + 0x1A, gMenuText[ASSET_MENU_TEXT_OK], 1, ALIGN_MIDDLE_CENTER);
            if (gMenuSubOption == 2) {
                set_current_text_colour(7, 255, 255, 255, spA0, 255);
            } else {
                set_current_text_colour(7, 255, 255, 255, 0, 255);
            }
            render_dialogue_text(7, POS_CENTRED, y2 + 0x2A, gMenuText[ASSET_MENU_TEXT_CANCEL], 1, ALIGN_MIDDLE_CENTER);
        } else {

            for (i = 0, y2 = 12; i < gResultOptionCount;) {
                if (i == gMenuOption) {
                    set_current_text_colour(7, 255, 255, 255, spA0, 255);
                } else {
                    set_current_text_colour(7, 255, 255, 255, 0, 255);
                }
                render_dialogue_text(7, 80, y2, gResultOptionText[i], 1, ALIGN_MIDDLE_CENTER);
                i++;
                y2 += 16;
            }
        }
        open_dialogue_box(7);
    }
}

s32 menu_results_loop(s32 updateRate) {
    s32 playBackSound;
    s32 playSelectSound;
    s32 playPickSound;
    s32 prevOption;

    playBackSound = FALSE;
    playSelectSound = FALSE;
    playPickSound = FALSE;
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    func_8008E4EC();
    if (gMenuOptionCount <= 0) {
        gOpacityDecayTimer += updateRate;
        if (gOpacityDecayTimer >= 60) {
            gMenuOptionCount = 1;
        } else if (gMenuOptionCount < 0 && gOpacityDecayTimer > 20) {
            gMenuOptionCount = 0;
            sound_play(SOUND_WHOOSH1, NULL);
        }
    }
    if (gMenuDelay < 20) {
        if (gMenuOptionCount <= 0) {
            if (gOpacityDecayTimer >= 20) {
                func_80096978(updateRate, 1.0f - ((f32) (gOpacityDecayTimer - 20) / 40.0f));
            }
        } else {
            func_80096978(updateRate, 0.0f);
        }
    }
    if (gMenuDelay == 0) {
        if (gMenuOptionCount == 0) {
            if (D_801267D8[4] & (A_BUTTON | START_BUTTON)) {
                gMenuOptionCount = 1;
            }
        } else if (gMenuSubOption != 0) {
            if (D_801267D8[4] & (A_BUTTON | START_BUTTON)) {
                if (gMenuSubOption == 1) {
                    playSelectSound = TRUE;
                    music_fade(-128);
                    transition_begin(&sMenuTransitionFadeIn);
                    gMenuDelay = 1;
                } else {
                    playBackSound = TRUE;
                    gMenuSubOption = 0;
                }
            } else if (D_801267D8[4] & B_BUTTON) {
                playBackSound = TRUE;
                gMenuSubOption = 0;
            } else {
                prevOption = gMenuSubOption;
                if (D_80126830[4] > 0 && gMenuSubOption == 2) {
                    gMenuSubOption = 1;
                }
                if (D_80126830[4] < 0 && gMenuSubOption == 1) {
                    gMenuSubOption = 2;
                }
                if (prevOption != gMenuSubOption) {
                    playPickSound = TRUE;
                }
            }
        } else if (D_801267D8[4] & (A_BUTTON | START_BUTTON)) {
            playSelectSound = TRUE;
            if (gResultOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_QUIT]) {
                gMenuSubOption = 2;
            } else {
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
                music_fade(-128);
            }
        } else {
            prevOption = gMenuOption;
            if (D_80126830[4] < 0 && gMenuOption < (gResultOptionCount - 1)) {
                gMenuOption++;
            }
            if (D_80126830[4] > 0 && gMenuOption > 0) {
                gMenuOption--;
            }
            if (prevOption != gMenuOption) {
                playPickSound = TRUE;
            }
        }
        if (playBackSound) {
            sound_play(SOUND_MENU_BACK3, NULL);
        } else if (playSelectSound) {
            sound_play(SOUND_SELECT2, NULL);
        } else if (playPickSound) {
            sound_play(SOUND_MENU_PICK2, NULL);
        }

    } else {
        gMenuDelay += updateRate;
        if (gMenuDelay > 30) {
            func_800976CC();
            close_dialogue_box(7);
            assign_dialogue_box_id(7);
            if (gResultOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_TRYAGAIN]) {
                return (0x100 | 0x2); // This gets parsed in menu_logic_loop as a flag and an ID from the bottom 7 bits.
            }
            if (gResultOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_SELECTTRACK]) {
                load_level_for_menu(SPECIAL_MAP_ID_NO_LEVEL, -1, 0);
                menu_init(MENU_TRACK_SELECT);
                return 0;
            }
            return (0x100 | 0x4);
        }
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}

void func_800976CC(void) {
    func_8009C4A8(gRaceResultsObjectIndices);
    unload_font(ASSET_FONTS_BIGFONT);
}

/**
 * Takes in a compressed filename integer, and decompresses it to a string.
 * Each character takes up 5 bits, so up to 6 chars can fit in the integer.
 */
void decompress_filename_string(u32 compressedFilename, char *output, s32 length) {
    s32 index;
    output[length] = '\0'; // Set null terminator at the end
    for (index = length - 1; index >= 0;) {
        index--;
        output[index + 1] = gFileNameValidChars[compressedFilename & (sizeof(gFileNameValidChars) - 1)];
        compressedFilename /= sizeof(gFileNameValidChars); // compressedFilename >>= 5;
    }
}

/**
 * Takes in a string, and compresses it into an integer.
 * Each character takes up 5 bits, so up to 6 chars can fit in the integer.
 */
s32 compress_filename_string(char *filename, s32 length) {
    s32 i;
    u32 output;
    u8 processingChars;
    u8 currentChar;
    s32 charIndex;

    output = 0;
    processingChars = 1;

    for (i = 0; i < length; i++) {
        if (filename[i] == '\0') {
            processingChars = 0;
        }

        if (!processingChars) {
            currentChar = ' ';
            charIndex = 0;
        } else {
            currentChar = filename[i];
            charIndex = 0;
        }

        while (currentChar != gFileNameValidChars[charIndex]) {
            charIndex++;
            if (charIndex >= (s32) (sizeof(gFileNameValidChars) - 1)) {
                break;
            }
        }

        output *= sizeof(gFileNameValidChars); // output <<= 5;
        output |= charIndex & (sizeof(gFileNameValidChars) - 1);
    }

    return output;
}

void trim_filename_string(char *input, char *output) {
    s32 some_ptr;
    u32 zxChar;
    char *ptr_to_input;
    char new_var;
    s32 another_ptr;
    char *one_more_ptr;

    some_ptr = 0;
    if (*input != 0) {
        new_var = input[some_ptr];
        ptr_to_input = input;
        zxChar = new_var;
        do {
            another_ptr = some_ptr;
            if ((zxChar & 0xFFFFFFFF) == ' ') {
                zxChar = ptr_to_input[1];
                some_ptr++;
                ptr_to_input++;
                while ((zxChar & 0xFFFFFFFF) == ' ') {
                    some_ptr++;
                    zxChar = *(++ptr_to_input);
                }
                if ((zxChar != 0) && (another_ptr < some_ptr)) {
                    one_more_ptr = another_ptr + input;
                    do {
                        *(output++) = *(one_more_ptr++);
                    } while (++another_ptr < some_ptr);
                    zxChar = *ptr_to_input;
                }
            } else {
                *output = zxChar;
                zxChar = ptr_to_input[1];
                output++;
                some_ptr++;
                ptr_to_input++;
            }
        } while (zxChar != 0);
    }
    *output = '\0';
}

void func_80097874(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, char *fileName, s32 fileNameLength) {
    gEnterInitalsY = arg0;
    gFilenameX = arg1;
    gFilenameY = arg2;
    gFilenameFont = arg3;
    D_80126C6C = arg4;
    D_80126C74 = fileName;
    D_80126C78 = fileNameLength;
    gCurrentFilenameChars = 0;
    D_80126C50 = (f32) *D_80126C6C;
    D_80126C48 = FALSE;
    D_80126C3C = 0;
    D_80126C34 = 0;
    load_font(ASSET_FONTS_BIGFONT);
}

/**
 * Draw menu for "Enter your initials" when starting a new game.
 * The text entry is a horizontal list of characters you scroll through.
 * Visual Aid: https://imgur.com/llVwdTy
 */
void render_enter_filename_ui(UNUSED s32 updateRate) {
    s32 xIncrement;
    s32 charIndexIncrement;
    s32 xStart;
    s32 charIndex;
    s32 x;
    s32 i;
    s32 startCharacterIndex;
    s32 y;
    char *trimmedTextPtr;
    char trimmedTextBuffer[4];

    startCharacterIndex = D_80126C50;
    xStart = SCREEN_WIDTH_HALF - (s32) ((D_80126C50 - (f32) startCharacterIndex) * 40);
    set_text_background_colour(0, 0, 0, 0);
    set_text_font(ASSET_FONTS_FUNFONT);

    // Draw "Enter Initials" shadow
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 2, gEnterInitalsY - 22,
              gMenuText[ASSET_MENU_TEXT_ENTERINITIALS], ALIGN_MIDDLE_CENTER);

    // Draw "Enter Initials" text
    set_text_colour(255, 128, 255, 96, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, gEnterInitalsY - 24, gMenuText[ASSET_MENU_TEXT_ENTERINITIALS],
              ALIGN_MIDDLE_CENTER);

    y = gEnterInitalsY;

    // Doesn't match with a for loop.
    i = 0;
    while (i < 2) {
        x = xStart;
        charIndex = startCharacterIndex;
        if (i != 0) {
            x = xStart - 40;
            charIndex = startCharacterIndex - 1;
            xIncrement = -40;
            charIndexIncrement = -1;
        } else {
            xIncrement = 40;
            charIndexIncrement = 1;
        }
        while (((x >= -15) && (x < 336))) {
            if (charIndex < 0) {
                charIndex = 30;
            }
            if (charIndex > 30) {
                charIndex = 0;
            }
            if (charIndex == *D_80126C6C) {
                set_text_colour(255, 255, 255, 0, 255);
            } else {
                set_text_colour(0, 0, 0, 128, 255);
            }
            if (charIndex < 28) {
                set_text_font(ASSET_FONTS_BIGFONT);
                gCurFilenameCharBeingDrawn = gFileNameValidChars[charIndex];
                draw_text(&sMenuCurrDisplayList, x, y, &gCurFilenameCharBeingDrawn, ALIGN_MIDDLE_CENTER);
            } else {
                set_text_font(ASSET_FONTS_FUNFONT);
                if (charIndex == 28) {
                    draw_text(&sMenuCurrDisplayList, x, y, (char *) &D_800E8244 /* "SP" */, ALIGN_MIDDLE_CENTER);
                } else if (charIndex == 29) {
                    draw_text(&sMenuCurrDisplayList, x, y, (char *) &D_800E8248 /* "DEL" */, ALIGN_MIDDLE_CENTER);
                } else {
                    draw_text(&sMenuCurrDisplayList, x, y, (char *) &D_800E824C /* "OK" */, ALIGN_MIDDLE_CENTER);
                }
            }
            x += xIncrement;
            charIndex += charIndexIncrement;
        }
        i++;
    }
    trimmedTextPtr = trimmedTextBuffer;
    trim_filename_string(D_80126C74, trimmedTextPtr);

    if (trimmedTextPtr != NULL) {
        set_text_font(gFilenameFont);
        set_text_colour(0, 0, 0, 255, 128);
        draw_text(&sMenuCurrDisplayList, gFilenameX + 1, gFilenameY + 3, trimmedTextBuffer, ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 255, 255, 0, 255);
        draw_text(&sMenuCurrDisplayList, gFilenameX, gFilenameY, trimmedTextBuffer, ALIGN_MIDDLE_CENTER);
    }
}

s32 menu_enter_filename_loop(s32 updateRate) {
    s32 var_v0_2;
    f32 temp_f20;
    u32 buttonsPressed;
    f32 var_f12;
    f32 var_f14;
    f32 var_f18;
    s32 *temp_a1;
    s32 var_v1;
    s32 joytickXAxis;

    buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE);
    joytickXAxis = clamp_joystick_x_axis(PLAYER_ONE);
    if ((joytickXAxis > -35) && (joytickXAxis < 35)) {
        joytickXAxis = 0;
    }
    if (joytickXAxis < 0) {
        if (D_80126C3C >= 0) {
            D_80126C34 = 0;
            D_80126C3C = -1;
        }
        D_80126C34 += updateRate;
        if (updateRate != D_80126C34) {
            if (D_80126C34 < 28) {
                joytickXAxis = 0;
            } else {
                D_80126C34 -= 6;
            }
        }
    } else if (joytickXAxis > 0) {
        if (D_80126C3C <= 0) {
            D_80126C34 = 0;
            D_80126C3C = 1;
        }
        D_80126C34 += updateRate;
        if (updateRate != D_80126C34) {
            if (D_80126C34 < 28) {
                joytickXAxis = 0;
            } else {
                D_80126C34 -= 6;
            }
        }
    } else {
        D_80126C34 = 0;
        D_80126C3C = 0;
    }
    temp_a1 = D_80126C6C;
    temp_f20 = (f32) *temp_a1;
    for (var_v1 = 0; var_v1 < updateRate; var_v1++) {
        if (D_80126C50 <= temp_f20) {
            var_f12 = temp_f20 - D_80126C50;
            var_f14 = temp_f20 - (D_80126C50 + 31.0f);
        } else {
            var_f12 = (temp_f20 + 31.0f) - D_80126C50;
            var_f14 = temp_f20 - D_80126C50;
        }
        if ((var_f12 * var_f12) < (var_f14 * var_f14)) {
            var_f18 = var_f12;
        } else {
            var_f18 = var_f14;
        }
        D_80126C50 += var_f18 * 0.1f;
        if (D_80126C50 >= 31.0f) {
            do {
                D_80126C50 -= 31.0f;
            } while (D_80126C50 >= 31.0f);
        }
        if (D_80126C50 < 0.0f) {
            do {
                D_80126C50 += 31.0f;
            } while (D_80126C50 < 0.0f);
        }
    }
    if (gCurrentFilenameChars < D_80126C78) {
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            if (*temp_a1 < 29) {
                D_80126C74[gCurrentFilenameChars] = gFileNameValidChars[*temp_a1];
                gCurrentFilenameChars++;
                D_80126C74[gCurrentFilenameChars] = '\0';
                sound_play(SOUND_SELECT2, NULL);
                if (gCurrentFilenameChars >= D_80126C78) {
                    *D_80126C6C = 30;
                }
            } else if (*temp_a1 == 29) {
                if (gCurrentFilenameChars > 0) {
                    gCurrentFilenameChars--;
                    D_80126C74[gCurrentFilenameChars] = '\0';
                }
                sound_play(SOUND_MENU_BACK3, NULL);
            } else {
                if ((gCurrentFilenameChars != 0) || (D_80126C74[0] == '\0')) {
                    for (var_v1 = gCurrentFilenameChars; var_v1 < D_80126C78; var_v1++) {
                        D_80126C74[var_v1] = 32;
                    }
                }
                D_80126C74[D_80126C78] = '\0';
                sound_play(SOUND_SELECT2, NULL);
                D_80126C48 = TRUE;
            }
        } else if (buttonsPressed & B_BUTTON) {
            if (gCurrentFilenameChars > 0) {
                gCurrentFilenameChars--;
            }
            D_80126C74[gCurrentFilenameChars] = '\0';
            sound_play(SOUND_MENU_BACK3, NULL);
        } else {
            var_v0_2 = *temp_a1;
            if (joytickXAxis < 0) {
                var_v0_2--;
            }
            if (joytickXAxis > 0) {
                var_v0_2++;
            }
            if (var_v0_2 < 0) {
                var_v0_2 = 30;
            }
            if (var_v0_2 >= 31) {
                var_v0_2 = 0;
            }
            if (var_v0_2 != *temp_a1) {
                sound_play(SOUND_MENU_PICK2, NULL);
                *D_80126C6C = var_v0_2;
            }
        }
    } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        sound_play(SOUND_SELECT2, NULL);
        D_80126C48 = TRUE;
    } else if (buttonsPressed & B_BUTTON) {
        gCurrentFilenameChars--;
        D_80126C74[gCurrentFilenameChars] = '\0';
        sound_play(SOUND_MENU_BACK3, NULL);
    }
    render_enter_filename_ui(updateRate);
    return D_80126C48;
}

/**
 * Explicitly says to unload the ASSET_FONTS_BIGFONT type.
 */
void unload_big_font_4(void) {
    unload_font(ASSET_FONTS_BIGFONT);
}

// Gets triggered when entering trophy race in adventure mode.
void func_80098208(void) {
    Settings *settings = get_settings();
    gTrophyRaceWorldId = settings->worldId;
    gTrophyRaceRound = 0;
    settings->unk4C->unk0 = settings->courseId;
    settings->unk4C->unkF = 0;
    settings->unk4C->unk1 = 0;
    gInAdvModeTrophyRace = 1;
    set_time_trial_enabled(0);
}

/**
 * Initialise the trophy race intro.
 * Finds which level should be next, then loads it for the preview.
 */
void menu_trophy_race_round_init(void) {
    s32 i;
    s32 index;
    Settings *settings;
    s8 *levelIds;

    settings = get_settings();
    levelIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS); // Returns level ids array.

    if (gTrophyRaceRound == 0) {
        for (index = 0; index < 8; index++) {
            settings->racers[index].trophy_points = 0;
        }
    }

    // Is this a fakematch? I can't tell.
    do {
        index = levelIds[((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound];
        if (index != -1) {
            continue;
        }
        index = (index + 1) & 3;
    } while (index == -1);

    for (i = 0; i < gNumberOfActivePlayers; i++) {
        gPlayerSelectVehicle[i] = get_map_default_vehicle(index);
    }

    set_level_default_vehicle(get_map_default_vehicle(index));
    load_level_for_menu(index, -1, 1);

    gMenuDelay = 0;
    gTrackNameVoiceDelay = 10;
    load_font(ASSET_FONTS_BIGFONT);
    music_voicelimit_set(24);
    music_play(SEQUENCE_MAIN_MENU);
    music_fade(256);
}

/**
 * Draws the trophy race intro text
 * Ex. (DINO DOMAIN / TROPHY RACE / ROUND ONE / ANCIENT LAKE)
 */
void draw_trophy_race_text(UNUSED s32 updateRate) {
    s32 yPos;
    char *worldName;
    char *levelName;
    s8 *levelIds;

    levelIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    if (osTvType == TV_TYPE_PAL) {
        yPos = 18;
    } else {
        yPos = 0;
    }

    worldName = get_level_name(get_hub_area_id(gTrophyRaceWorldId));
    levelName = get_level_name(levelIds[((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound]);
    set_text_background_colour(0, 0, 0, 0);
    set_text_font(ASSET_FONTS_BIGFONT);
    // Text Shadows first
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, (char *) worldName, ALIGN_MIDDLE_CENTER);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 67, gMenuText[ASSET_MENU_TEXT_TROPHYRACE],
              ALIGN_MIDDLE_CENTER); // TROPHY RACE
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, (char *) worldName, ALIGN_MIDDLE_CENTER);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 64, gMenuText[ASSET_MENU_TEXT_TROPHYRACE],
              ALIGN_MIDDLE_CENTER); // TROPHY RACE
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yPos + 176,
              gMenuText[ASSET_MENU_TEXT_ROUNDONE + gTrophyRaceRound],
              ALIGN_MIDDLE_CENTER); // ROUND ONE / ROUND TWO / ROUND THREE / ROUND FOUR
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yPos + 208, (char *) levelName, ALIGN_MIDDLE_CENTER);
}

s32 menu_trophy_race_round_loop(s32 updateRate) {
    s8 *trackMenuIds;
    s16 ttVoiceLine;
    s32 temp;

    trackMenuIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS); // tracks_menu_ids
    if (gTrackNameVoiceDelay != 0) {
        gTrackNameVoiceDelay -= updateRate;
        if (gTrackNameVoiceDelay <= 0) {
            // This is mostly likely supposed to be a multi dimensional array
            temp = trackMenuIds[(((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound)];
            ttVoiceLine = gTTVoiceLines[temp];
            if (ttVoiceLine != -1) {
                sound_play(ttVoiceLine, NULL);
            }
            gTrackNameVoiceDelay = 0;
        }
    }
    if (gMenuDelay != 0) {
        gMenuDelay += updateRate;
    }
    if (gMenuDelay < 22) {
        draw_trophy_race_text(updateRate);
    }
    if ((gIgnorePlayerInputTime == 0) && (gMenuDelay == 0)) {
        func_8008E4EC();
        if ((D_801267D8[4] & (A_BUTTON | START_BUTTON)) != 0) {
            transition_begin(&sMenuTransitionFadeIn);
            gMenuDelay = 1;
            music_fade(-128);
        }
    }
    if (gMenuDelay >= 31) {
        unload_big_font_5();
        gTrackIdToLoad = trackMenuIds[(((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound)];
        gTrackSpecifiedWithTrackIdToLoad = 1;
        return gNumberOfActivePlayers;
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}

/**
 * Explicitly says to unload the ASSET_FONTS_BIGFONT type.
 */
void unload_big_font_5(void) {
    unload_font(ASSET_FONTS_BIGFONT);
}

// https://decomp.me/scratch/MvASs
#ifdef NON_MATCHING
void func_80098774(s32 isRankings) {
    Settings *settings;
    s16 **iconPositions;
    s16 *yPositions;
    s16 *xPositions;
    s32 yOffset;
    s32 menuElemIndex;
    UNUSED s32 arrIndex;
    s32 racerIndex;
    s32 temp;
    s32 greenAmount;
    UNUSED s32 index;
    char *titleText;
    UNUSED MenuElement *elem;

    settings = get_settings();
    titleText = (isRankings) ? gMenuText[ASSET_MENU_TEXT_RANKINGS] : gMenuText[ASSET_MENU_TEXT_RACEORDER];
    gTrophyRankingsTitle[0].unk14_a.asciiText = titleText;
    gTrophyRankingsTitle[1].unk14_a.asciiText = titleText;
    racerIndex = (gRankingPlayerCount - 1);
    racerIndex <<= 1;
    yOffset = 240;
    if (osTvType == TV_TYPE_PAL) {
        racerIndex += 16;
        yOffset = 264;
    }
    iconPositions = gTrophyRankingsIconPositions;
    xPositions = gTrophyRankingsIconPositions[racerIndex++];
    yPositions = iconPositions[racerIndex];
    menuElemIndex = 2;
    if (xPositions != NULL && yPositions != NULL) {
        for (racerIndex = 0; racerIndex < gRankingPlayerCount; racerIndex++) {
            for (temp = 0; temp < 3; temp++) {
                gTrophyRankingsTitle[menuElemIndex + temp].left = *xPositions;
                gTrophyRankingsTitle[menuElemIndex + temp].center = *xPositions;
                gTrophyRankingsTitle[menuElemIndex + temp].right = *xPositions;
                xPositions++;
                if ((gRankingPlayerCount >= 5) && (racerIndex >= (gRankingPlayerCount >> 1))) {
                    gTrophyRankingsTitle[menuElemIndex + temp].top = *yPositions - yOffset;
                    gTrophyRankingsTitle[menuElemIndex + temp].middle = *yPositions;
                    gTrophyRankingsTitle[menuElemIndex + temp].bottom = *yPositions + yOffset;
                    yPositions++;
                } else {
                    gTrophyRankingsTitle[menuElemIndex + temp].top = *yPositions + yOffset;
                    gTrophyRankingsTitle[menuElemIndex + temp].middle = *yPositions;
                    gTrophyRankingsTitle[menuElemIndex + temp].bottom = *yPositions - yOffset;
                    yPositions++;
                }
            }

            // Regalloc issue here.
            temp = gRankingPlayerCount & 3;
            if (temp) {
                greenAmount = racerIndex;
                if (racerIndex >= 3) {
                    greenAmount = racerIndex - 3;
                }
            } else {
                greenAmount = racerIndex & 3;
            }
            temp = 255 - (greenAmount << 6);

            gTrophyRankingsTitle[menuElemIndex + 2].filterGreen = temp;
            if (isRankings) {
                gTrophyRankingsTitle[menuElemIndex].unk14_a.drawTexture =
                    gRacerPortraits[settings->racers[D_80126430[racerIndex]].character];
                gTrophyRankingsTitle[menuElemIndex + 2].unk14_a.element = &settings->racers[D_80126430[racerIndex]];
            } else {
                gTrophyRankingsTitle[menuElemIndex].unk14_a.drawTexture =
                    gRacerPortraits[settings->racers[D_80126428[racerIndex]].character];
                gTrophyRankingsTitle[menuElemIndex + 2].unk14_a.number = &gTrophyRacePointsArray[racerIndex];
            }
            menuElemIndex += 3;
        }
    }
    gTrophyRankingsTitle[menuElemIndex].unk14_a.asciiText = NULL;
}

#else
GLOBAL_ASM("asm/non_matchings/menu/func_80098774.s")
#endif

/**
 * Initialise trophy race points screen.
 * Sets the order of the racer portraits based on points position.
 */
void menu_trophy_race_rankings_init(void) {
    UNUSED s32 pad0;
    UNUSED s32 pad1;
    UNUSED s32 pad2;
    s32 i;
    s32 j;
    s32 tempForSwap;
    s32 sp48[4];
    UNUSED s32 pad3;
    Settings *settings;
    s8 *trackMenuIds;

    settings = get_settings();
    trackMenuIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    gMenuOptionCount = 0;
    gMenuDelay = 0;
    gOptionBlinkTimer = 0;
    gOpacityDecayTimer = 0;
    reset_controller_sticks();
    func_8009C674(gTrophyRankingsObjectIndices);
    allocate_menu_images(gTrophyRaceImageIndices);
    gPrevTrophyRaceRound = gTrophyRaceRound;
    do {
        if (++gTrophyRaceRound >= 4) {
            break;
        }
    } while ((trackMenuIds[((gTrophyRaceWorldId - 1) * 6) + (gTrophyRaceRound)] == -1));

    if (gTrophyRaceRound < 4) {
        gResultOptionText[0] = gMenuText[ASSET_MENU_TEXT_CONTINUE];
        gResultOptionText[1] = gMenuText[ASSET_MENU_TEXT_QUITTROPHYRACE];
        gResultOptionCount = 3;
    } else {
        gResultOptionText[0] = gMenuText[ASSET_MENU_TEXT_TROPHYCEREMONY];
        gResultOptionCount = 1;
    }
    gMenuOption = 0;
    assign_racer_portrait_textures();

    if (gNumberOfActivePlayers > 2) {
        gRankingPlayerCount = gNumberOfActivePlayers;
    } else if ((gNumberOfActivePlayers == 2) || (is_in_two_player_adventure())) {
        gRankingPlayerCount = get_multiplayer_racer_count();
    } else {
        gRankingPlayerCount = 8;
    }
    for (i = 0; i < gRankingPlayerCount; i++) {
        for (j = 0; j < gRankingPlayerCount; j++) {
            if (i == settings->racers[j].starting_position) {
                D_80126428[i] = j;
                if (j < gNumberOfActivePlayers) {
                    D_80126418[i] = TRUE;
                } else {
                    D_80126418[i] = FALSE;
                }
            }
        }
    }
    for (i = 0; i < gRankingPlayerCount; i++) {
        D_801263F8[i] = gTrophyRacePointsArray[settings->racers[i].starting_position];
    }
    for (i = 0; i < gRankingPlayerCount; i++) {
        D_80126430[i] = i;
        sp48[i] = settings->racers[i].trophy_points + D_801263F8[i];
    }

    for (i = gRankingPlayerCount - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (sp48[j] < sp48[j + 1]) {
                tempForSwap = sp48[j];
                sp48[j] = sp48[j + 1];
                sp48[j + 1] = tempForSwap;
                tempForSwap = D_80126430[j];
                D_80126430[j] = D_80126430[j + 1];
                D_80126430[j + 1] = tempForSwap;
            }
        }
    }

    if (is_in_two_player_adventure()) {
        j = 2;
    } else {
        j = gNumberOfActivePlayers;
    }
    for (i = 0; i < gRankingPlayerCount; i++) {
        if (D_80126430[i] < j) {
            D_80126420[i] = 1;
        } else {
            D_80126420[i] = 0;
        }
    }
    load_font(ASSET_FONTS_BIGFONT);
    music_voicelimit_set(24);
    music_play(SEQUENCE_MAIN_MENU);
    music_fade(256);
    func_80098774(0);
    func_80081E54(gTrophyRankingsTitle, 0.5f, 20.0f, 0.5f, 0, 0);
}

void func_80098EBC(s32 updateRate) {
    s32 test;
    s32 new_var2;
    s32 fade;
    s32 i;
    UNUSED MenuElement *test2;

    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    test = gOptionBlinkTimer * 8;
    if (test > 255) {
        test = 511 - test;
    }
    for (i = 0; i < gRankingPlayerCount; i++) {
        fade = 255;
        if (gNumberOfActivePlayers <= 2 &&
            ((gMenuOptionCount == 0 && D_80126418[i]) || (gMenuOptionCount != 0 && D_80126420[i]))) {
            fade = (test >> 1) + 128;
        }
        gTrophyRankingsRacers[i * 3].filterRed = fade;
        gTrophyRankingsRacers[i * 3].filterGreen = fade;
        gTrophyRankingsRacers[i * 3].filterBlue = fade;
    }
    new_var2 = gMenuOptionCount;
    if (new_var2 == 2 || new_var2 == 3) {
        draw_menu_elements(1, gTrophyRankingsTitle, 1.0f);
    }
}

s32 menu_trophy_race_rankings_loop(s32 updateRate) {
    s32 i;
    s32 temp6;
    s32 buttonsPressed;
    s32 temp1;
    s32 ret;
    s8 *miscAsset31;
    s32 sp34;
    s16 temp5;
    s16 temp7;
    Settings *settings;
    s32 temp0;

    ret = MENU_RESULT_CONTINUE;
    settings = get_settings();
    if ((gMenuDelay > -20) && (gMenuDelay < 20)) {
        func_80098EBC(updateRate);
    }
    update_controller_sticks();
    switch (gMenuOptionCount) { // gMenuOptionCount = current Trophy Race Rankings state?
        case 0:
            if (func_80081F4C(updateRate) != 0) {
                gMenuOptionCount = 1;
                func_80098774(1);
                func_80081E54(gTrophyRankingsTitle, 0.5f, 0.0f, 0.0f, 0, 0);
            }
            break;
        case 1:
            if (func_80081F4C(updateRate) != 0) {
                gMenuOptionCount = 2;
                draw_menu_elements(1, gTrophyRankingsTitle, 1.0f);
            }
            break;
        case 2:
            gOpacityDecayTimer += updateRate;
            if (gOpacityDecayTimer > 10) {
                gOpacityDecayTimer -= 10;
                temp5 = 0;
                for (i = 0; i < gRankingPlayerCount; i++) {
                    if (D_801263F8[i] > 0) {
                        D_801263F8[i]--;
                        temp5 = 1;
                        settings->racers[i].trophy_points++;
                    }
                }
                if (temp5) {
                    sound_play(SOUND_TING_HIGH, NULL);
                }
            }

            buttonsPressed = 0;
            temp1 = gMenuOption;
            for (i = 0; i < gNumberOfActivePlayers; i++) {
                buttonsPressed |= get_buttons_pressed_from_player(i);
                if (gControllersYAxisDirection[i] < 0) {
                    gMenuOption++;
                }
                if (gControllersYAxisDirection[i] > 0) {
                    gMenuOption--;
                }
            }
            if (gMenuOption < 0) {
                gMenuOption = 0;
            }
            if (gMenuOption >= gResultOptionCount) {
                gMenuOption = gResultOptionCount - 1;
            }
            if (temp1 != gMenuOption) {
                sound_play(SOUND_MENU_PICK2, NULL);
            }
            if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                music_fade(-128);
                transition_begin(&sMenuTransitionFadeIn);
                gMenuOptionCount = 3;
                for (i = 0; i < gRankingPlayerCount; i++) {
                    settings->racers[i].trophy_points += D_801263F8[i];
                }
            }
            break;
        case 3:
            gMenuDelay += updateRate;
            if (gMenuDelay >= 31) {
                func_80099600();
                close_dialogue_box(7);
                assign_dialogue_box_id(7);
                if (gTrophyRaceRound < 4) {
                    menu_init(MENU_TROPHY_RACE_ROUND);
                } else {
                    for (temp6 = 0, i = 0; i < gRankingPlayerCount; i++) {
                        if (D_80126420[i] != 0) {
                            temp7 = settings->racers[D_80126430[i]].character;
                            if (temp6 == 0) {
                                sp34 = i;
                                D_80126438[temp6++] = temp7;
                                continue;
                            }
                            if (settings->racers[D_80126430[i]].trophy_points ==
                                settings->racers[D_80126430[sp34]].trophy_points) {
                                D_80126438[temp6++] = temp7;
                            }
                        }
                    }

                    if (gNumberOfActivePlayers == 1 && !is_in_two_player_adventure()) {
                        temp6 = 0;
                    }
                    D_80126438[temp6] = -1;
                    if (gIsInTracksMode == 1) {
                        if (sp34 >= 3) {
                            menu_init(MENU_TRACK_SELECT);
                        } else {
                            ret = MENU_RESULT_FLAGS_100 | MENU_RESULT_TRACKS_MODE;
                        }
                    } else {
                        ret = MENU_RESULT_RETURN_TO_GAME;
                        settings->courseId = get_hub_area_id(settings->worldId);
                        if (gInAdvModeTrophyRace != 0) {
                            gInAdvModeTrophyRace = 0;
                            ret = settings->courseId | MENU_RESULT_FLAGS_200;
                            if (sp34 < 3) {
                                temp0 = settings->worldId - 1;
                                temp0 <<= 1;
                                temp1 = ((3 - sp34) & 3);
                                temp6 = (settings->trophies >> temp0) & 3;
                                if (temp6 < temp1) {
                                    settings->trophies &= ~(3 << temp0);
                                    settings->trophies |= (temp1 << temp0);
                                    safe_mark_write_save_file(get_save_file_index());
                                }
                            }
                        }
                    }
                    if (sp34 < 3) {
                        miscAsset31 = (s8 *) get_misc_asset(ASSET_MISC_31);
                        temp0 = ((gTrophyRaceWorldId * 3) + sp34) - 3;
                        func_8009ABD8(miscAsset31, temp0, ret, 0, 0, D_80126438);
                        ret = MENU_RESULT_CONTINUE;
                        menu_init(MENU_NEWGAME_CINEMATIC);
                    }
                    gTrophyRaceWorldId = 0;
                }
            }
            break;
    }
    gIgnorePlayerInputTime = 0;
    return ret;
}

void func_80099600(void) {
    func_8009C4A8(gTrophyRankingsObjectIndices);
    unload_font(ASSET_FONTS_BIGFONT);
}

s32 get_trophy_race_world_id(void) {
    return gTrophyRaceWorldId;
}

void func_8009963C(void) {
    u8 *mainTrackIds;
    s32 i;
    s32 j;
    u16 sp44[4];
    u16 swap;
    u16 swapByte;
    UNUSED s32 pad;

    D_801264D4 = 0;
    mainTrackIds = (u8 *) get_misc_asset(ASSET_MISC_MAIN_TRACKS_IDS);

    for (i = 0; i < 6; i++) {
        if (D_801264DC[i] != 0xFF) {
            for (j = 0; mainTrackIds[j] != 0xFF && mainTrackIds[j] != D_801264DC[i]; j++) {}
            if (mainTrackIds[j] != 0xFF) {
                D_80126540[D_801264D4] = i;
                sp44[D_801264D4] = (j * 8) + D_801264EC[i];
                D_801264D4++;
            }
        }
    }

    for (i = D_801264D4 - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (sp44[j + 1] < sp44[j]) {
                swap = sp44[j];
                sp44[j] = sp44[j + 1];
                sp44[j + 1] = swap;
                swapByte = D_80126540[j];
                D_80126540[j] = D_80126540[j + 1];
                D_80126540[j + 1] = swapByte;
            }
        }
    }

    for (i = 0; i < D_801264D4; i++) {
        D_80126508[i] = D_801264DC[D_80126540[i]];
        D_80126510[i] = D_801264E4[D_80126540[i]];
        D_80126518[i] = D_801264EC[D_80126540[i]];
        D_80126520[i] = D_801264F8[D_80126540[i]];
    }
}

s32 func_800998E0(s32 arg0) {
    s32 temp_s0;
    s32 result;
    s32 i;

    result = 0;
    if (arg0 >= 0 && arg0 < D_801264D4) {
        sound_play(SOUND_SELECT2, NULL);
        temp_s0 = D_80126540[arg0];
        result = func_800753D8(D_801264D0, temp_s0);
        if (result == 0) {
            D_801264DC[temp_s0] = 0xFF;
            D_801264D4--;
            for (i = arg0; i < D_801264D4; i++) {
                D_80126540[i] = D_80126540[i + 1];
                D_80126508[i] = D_80126508[i + 1];
                D_80126510[i] = D_80126510[i + 1];
                D_80126518[i] = D_80126518[i + 1];
                D_80126520[i] = D_80126520[i + 1];
            }
            for (i = 0; i < D_801264D4; i++) {
                if (temp_s0 < D_80126540[i]) {
                    D_80126540[i]--;
                }
            }
        }
    }
    return result;
}

#ifdef NON_EQUIVALENT

// Should be functionally equivalent
void menu_ghost_data_init(void) {
    s32 i;
    SIDeviceStatus pakStatus;

    pakStatus = func_800756D4(D_801264D0, &D_801264DC, &D_801264EC, &D_801264E4, &D_801264F8);
    if (pakStatus == CONTROLLER_PAK_GOOD) {
        func_8009963C();
    }
    func_8009C674(&gGhostDataObjectIndices);
    allocate_menu_images(&gGhostDataImageIndices);
    load_font(ASSET_FONTS_BIGFONT);
    gDrawTexDinoDomainGhostBg[0].texture = gMenuObjects[TEXTURE_BACKGROUND_DINO_DOMAIN_TOP];
    gDrawTexDinoDomainGhostBg[5].texture = gMenuObjects[TEXTURE_BACKGROUND_DINO_DOMAIN_BOTTOM];
    gDrawTexSherbetIslandGhostBg[0].texture = gMenuObjects[TEXTURE_BACKGROUND_SHERBERT_ISLAND_TOP];
    gDrawTexSherbetIslandGhostBg[5].texture = gMenuObjects[TEXTURE_BACKGROUND_SHERBERT_ISLAND_BOTTOM];
    gDrawTexSnowflakeMountainGhostBg[0].texture = gMenuObjects[TEXTURE_BACKGROUND_SNOWFLAKE_MOUNTAIN_TOP];
    gDrawTexSnowflakeMountainGhostBg[5].texture = gMenuObjects[TEXTURE_BACKGROUND_SNOWFLAKE_MOUNTAIN_BOTTOM];
    gDrawTexDragonForestGhostBg[0].texture = gMenuObjects[TEXTURE_BACKGROUND_DRAGON_FOREST_TOP];
    gDrawTexDragonForestGhostBg[5].texture = gMenuObjects[TEXTURE_BACKGROUND_DRAGON_FOREST_BOTTOM];
    gDrawTexFutureFunLandGhostBg[0].texture = gMenuObjects[TEXTURE_BACKGROUND_FUTURE_FUN_LAND_TOP];
    gDrawTexFutureFunLandGhostBg[5].texture = gMenuObjects[TEXTURE_BACKGROUND_FUTURE_FUN_LAND_BOTTOM];
    for (i = 0; i < 4; i++) {
        gDrawTexDinoDomainGhostBg[i + 1].texture = gDrawTexDinoDomainGhostBg[0].texture;
        gDrawTexDinoDomainGhostBg[i + 6].texture = gDrawTexDinoDomainGhostBg[5].texture;
        if (i & 1 == 1) {
            gDrawTexSherbetIslandGhostBg[i + 1].texture = gDrawTexSherbetIslandGhostBg[0].texture;
            gDrawTexSherbetIslandGhostBg[i + 6].texture = gDrawTexSherbetIslandGhostBg[5].texture;
        } else {
            gDrawTexSherbetIslandGhostBg[i + 1].texture = gDrawTexSherbetIslandGhostBg[5].texture;
            gDrawTexSherbetIslandGhostBg[i + 6].texture = gDrawTexSherbetIslandGhostBg[0].texture;
        }
        gDrawTexSnowflakeMountainGhostBg[i + 1].texture = gDrawTexSnowflakeMountainGhostBg[0].texture;
        gDrawTexSnowflakeMountainGhostBg[i + 6].texture = gDrawTexSnowflakeMountainGhostBg[5].texture;
        gDrawTexDragonForestGhostBg[i + 1].texture = gDrawTexDragonForestGhostBg[0].texture;
        gDrawTexDragonForestGhostBg[i + 6].texture = gDrawTexDragonForestGhostBg[5].texture;
        if (i & 1 == 1) {
            gDrawTexFutureFunLandGhostBg[i + 1].texture = gDrawTexFutureFunLandGhostBg[0].texture;
            gDrawTexFutureFunLandGhostBg[i + 6].texture = gDrawTexFutureFunLandGhostBg[5].texture;
        } else {
            gDrawTexFutureFunLandGhostBg[i + 1].texture = gDrawTexFutureFunLandGhostBg[5].texture;
            gDrawTexFutureFunLandGhostBg[i + 6].texture = gDrawTexFutureFunLandGhostBg[0].texture;
        }
    }
    assign_vehicle_icon_textures();
    assign_racer_portrait_textures();
    assign_menu_arrow_textures();
    gOptionBlinkTimer = 0;
    gMenuOptionCount = 0;
    gOpacityDecayTimer = 0;
    gMenuDelay = 0;
    D_80126498 = 0;
    if (pakStatus == CONTROLLER_PAK_GOOD) {
        transition_begin(&sMenuTransitionFadeOut);
        return;
    }
    gMenuDelay = 30;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_ghost_data_init.s")
#endif

void func_80099E8C(UNUSED s32 updateRate) {
    s32 currentWorldId;
    s32 spE8;
    s32 spE4;
    s32 i;
    s32 y;
    s32 colourIntensity;
    s32 x;
    s32 heightAdjust;
    DrawTexture *vehicleSelectTex;
    char *levelName;
    char textBuffer[64];

    set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (osTvType == TV_TYPE_PAL) {
        heightAdjust = 12;
    } else {
        heightAdjust = 0;
    }
    spE4 = gOpacityDecayTimer;
    set_text_font(FONT_LARGE);
    set_text_background_colour(0, 0, 0, 0);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, gMenuText[ASSET_MENU_TEXT_GHOSTDATA],
              ALIGN_MIDDLE_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, gMenuText[ASSET_MENU_TEXT_GHOSTDATA], ALIGN_MIDDLE_CENTER);
    y = 56;
    if (D_801264D4 <= 0) {
        set_text_colour(255, 255, 255, 0, 255);
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, heightAdjust + SCREEN_HEIGHT_HALF,
                  gMenuText[ASSET_MENU_TEXT_NOGHOSTSSAVED], ALIGN_MIDDLE_CENTER);
        return;
    }
    spE8 = 3;
    colourIntensity = gOptionBlinkTimer * 8;
    if (colourIntensity > 255) {
        colourIntensity = 511 - colourIntensity;
    }
    colourIntensity |= ~0xFF;
    set_text_font(FONT_SMALL);
    x = 40;
    while (spE4 < D_801264D4 && spE8 > 0) {
        if (gGhostDataElementPositions[0]) {} // Fakematch

        currentWorldId = get_map_world_id(D_80126508[spE4]) - 1;
        if (currentWorldId < 0 || currentWorldId >= 5) {
            currentWorldId = 0;
        }
        levelName = get_level_name(D_80126508[spE4]);
        for (i = 0; (levelName[i] != '\0') && (i < 63); i++) {
            textBuffer[i] = levelName[i];
            if ((textBuffer[i] >= 'a') && (textBuffer[i] <= 'z')) {
                textBuffer[i] ^= 0x20; // Force uppercase.
            }
        }
        textBuffer[i] = '\0'; // Set NULL terminator
        render_texture_rectangle_scaled(&sMenuCurrDisplayList, gDrawTexWorldBgs[currentWorldId], x, y, 0.75f, 0.8125f,
                                        COLOUR_RGBA32(255, 255, 255, 255), 0);
        func_80080E90(&sMenuCurrDisplayList, 40, y, 240, 52, 4, 4, 32, 80, 176, 128);
        if (spE4 == D_80126498) {
            func_80080E90(&sMenuCurrDisplayList, 40, y, 240, 52, 4, 4, colourIntensity, colourIntensity,
                          colourIntensity, colourIntensity);
        }
        set_text_colour(0, 0, 0, 255, 255);
        for (i = 0; i < 4; i++) {
            draw_text(&sMenuCurrDisplayList, gGhostDataElementPositions[0] + 40 + D_800E1E20[(i << 1)],
                      y + gGhostDataElementPositions[1] + D_800E1E20[(i << 1) + 1], textBuffer, ALIGN_MIDDLE_CENTER);
        }
        set_text_colour(200, 228, 80, 255, 255);
        draw_text(&sMenuCurrDisplayList, gGhostDataElementPositions[0] + 40, gGhostDataElementPositions[1] + y,
                  textBuffer, ALIGN_MIDDLE_CENTER);
        render_textured_rectangle(&sMenuCurrDisplayList, gRacerPortraits[D_80126510[spE4]],
                                  gGhostDataElementPositions[2] + 40, gGhostDataElementPositions[3] + y, 255, 255, 255,
                                  255);
        switch (D_80126518[spE4]) {
            case 1:
                vehicleSelectTex = gRaceSelectionHoverTex;
                break;
            case 2:
                vehicleSelectTex = gRaceSelectionPlaneTex;
                break;
            default:
                vehicleSelectTex = gRaceSelectionCarTex;
                break;
        }
        render_texture_rectangle_scaled(&sMenuCurrDisplayList, vehicleSelectTex, (gGhostDataElementPositions[4] + 40),
                                        (gGhostDataElementPositions[5] + y), 0.625f, 0.625f,
                                        COLOUR_RGBA32(255, 255, 255, 255), 0);
        reset_render_settings(&sMenuCurrDisplayList);
        gMenuImageStack[7].unkC = (gGhostDataElementPositions[6] - SCREEN_HEIGHT_HALF);
        gMenuImageStack[7].unk10 = ((-gGhostDataElementPositions[7] - y) + heightAdjust + SCREEN_HEIGHT_HALF);
        gMenuImageStack[7].unk8 = 0.075f;
        func_8009CA60(7);
        sMenuGuiOpacity = 128;
        // Timestamp Shadow gets drawn first
        show_timestamp(D_80126520[spE4], gGhostDataElementPositions[8] - (SCREEN_HEIGHT_HALF - 1),
                       (-gGhostDataElementPositions[9] - y) + heightAdjust + (SCREEN_HEIGHT_HALF - 1), 0, 0, 0,
                       FONT_COLOURFUL);
        sMenuGuiOpacity = 255;
        show_timestamp(D_80126520[spE4], gGhostDataElementPositions[8] - (SCREEN_HEIGHT_HALF + 1),
                       (-gGhostDataElementPositions[9] - y) + heightAdjust + (SCREEN_HEIGHT_HALF + 1), 255, 192, 255,
                       FONT_COLOURFUL);
        spE4++;
        spE8--;
        y += 54;
    }
    colourIntensity &= 0xFF;
    if (gMenuOptionCount > 0) {
        clear_dialogue_box_open_flag(7);
        assign_dialogue_box_id(7);
        set_current_dialogue_box_coords(7, 104, 102, 216, 138);
        set_current_dialogue_background_colour(7, 0, 0, 0, 192);
        set_dialogue_font(7, 0);
        set_current_text_background_colour(7, 0, 0, 0, 0);
        if (gMenuOptionCount == 1) {
            set_current_text_colour(7, 255, 255, 255, colourIntensity, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, POS_CENTRED, 12, gMenuText[ASSET_MENU_TEXT_ERASEGHOST], 1, ALIGN_MIDDLE_CENTER);
        if (gMenuOptionCount == 2) {
            set_current_text_colour(7, 255, 255, 255, colourIntensity, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, POS_CENTRED, 28, gMenuText[ASSET_MENU_TEXT_CANCEL], 1, ALIGN_MIDDLE_CENTER);
        render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 7);
    }
    if (gOptionBlinkTimer & 0x10) {
        if ((gOpacityDecayTimer + 3) < D_801264D4) {
            render_textured_rectangle(&sMenuCurrDisplayList, gMenuSelectionArrowDown, SCREEN_WIDTH_HALF + 1, y + 3, 0,
                                      0, 0, 128);
            render_textured_rectangle(&sMenuCurrDisplayList, gMenuSelectionArrowDown, SCREEN_WIDTH_HALF - 1, y + 1, 255,
                                      255, 255, 255);
        }
        if (gOpacityDecayTimer > 0) {
            render_textured_rectangle(&sMenuCurrDisplayList, gMenuSelectionArrowUp, SCREEN_WIDTH_HALF + 1, 54, 0, 0, 0,
                                      128);
            render_textured_rectangle(&sMenuCurrDisplayList, gMenuSelectionArrowUp, SCREEN_WIDTH_HALF - 1, 52, 255, 255,
                                      255, 255);
        }
        reset_render_settings(&sMenuCurrDisplayList);
    }
}

s32 menu_ghost_data_loop(s32 updateRate) {
    s32 i;
    s32 pressedButtons;
    s32 xStick;
    s32 yStick;
    s32 temp;
    UNUSED s32 unused;

    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;

    if ((gMenuDelay > -20) && (gMenuDelay < 20)) {
        func_80099E8C(updateRate);
    }

    pressedButtons = 0;
    if (gMenuDelay) {
        if (gMenuDelay < 0) {
            gMenuDelay -= updateRate;
        } else {
            gMenuDelay += updateRate;
        }
    }

    xStick = 0;
    yStick = 0;
    if (!gIgnorePlayerInputTime && gMenuDelay == 0) {
        for (i = 0; i < MAXCONTROLLERS; i++) {
            pressedButtons |= get_buttons_pressed_from_player(i);
            xStick += gControllersXAxisDirection[i];
            yStick += gControllersYAxisDirection[i];
        }
    }

    switch (gMenuOptionCount) {
        case 0:
            if ((pressedButtons & (START_BUTTON | A_BUTTON)) && (D_801264D4 > 0)) {
                gMenuOptionCount = 2;
                sound_play(SOUND_SELECT2, NULL);
            } else if ((pressedButtons & B_BUTTON) ||
                       ((pressedButtons & (START_BUTTON | A_BUTTON)) && (D_801264D4 == 0))) {
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
                sound_play(SOUND_MENU_BACK3, NULL);
            } else {
                temp = D_80126498;
                if (yStick < 0 && D_80126498 < (D_801264D4 - 1)) {
                    D_80126498++;
                    if (D_80126498 >= gOpacityDecayTimer + 3) {
                        gOpacityDecayTimer = D_80126498 - 2;
                    }
                }
                if (yStick > 0 && D_80126498 > 0) {
                    D_80126498--;
                    if (D_80126498 < gOpacityDecayTimer) {
                        gOpacityDecayTimer = D_80126498;
                    }
                }
                if (temp != D_80126498) {
                    sound_play(SOUND_MENU_PICK2, NULL);
                }
            }
            break;
        case 1:
            if (pressedButtons & B_BUTTON) {
                gMenuOptionCount = 0;
                sound_play(SOUND_MENU_BACK3, NULL);
            } else {
                if (pressedButtons & (START_BUTTON | A_BUTTON)) {
                    if (func_800998E0(D_80126498) == 0) {
                        if (D_80126498 >= D_801264D4) {
                            D_80126498 = D_801264D4 - 1;
                        }
                        if (D_80126498 < 0) {
                            D_80126498 = 0;
                        }
                        if (D_80126498 < gOpacityDecayTimer) {
                            gOpacityDecayTimer = D_80126498;
                        }
                        sound_play(SOUND_SELECT2, NULL);
                    } else {
                        gMenuDelay = 1;
                        transition_begin(&sMenuTransitionFadeIn);
                        sound_play(SOUND_MENU_BACK3, NULL);
                    }
                    gMenuOptionCount = 0;
                } else if (yStick < 0) {
                    gMenuOptionCount = 2;
                    sound_play(SOUND_MENU_PICK2, NULL);
                }
            }
            break;
        case 2:
            if (pressedButtons & (START_BUTTON | A_BUTTON | B_BUTTON)) {
                gMenuOptionCount = 0;
                sound_play(SOUND_MENU_BACK3, NULL);
            } else if (yStick > 0) {
                gMenuOptionCount = 1;
                sound_play(SOUND_MENU_PICK2, NULL);
            }
            break;
    }

    gIgnorePlayerInputTime = FALSE;
    if (gMenuDelay > 30) {
        func_8009ABAC();
        menu_init(MENU_SAVE_OPTIONS);
    }
    return MENU_RESULT_CONTINUE;
}

void func_8009ABAC(void) {
    func_8009C4A8(gGhostDataObjectIndices);
    unload_font(ASSET_FONTS_BIGFONT);
}

void func_8009ABD8(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s8 *arg5) {
    s32 phi_v1;

    phi_v1 = 0;
    while (phi_v1 < arg1) {
        phi_v1++;
        while (-1 != *arg0) {
            arg0 += 3;
        }
        arg0++;
    }

    if (phi_v1 == 0 && (s8 *) get_misc_asset(ASSET_MISC_25) == arg0) {
        D_8012684C = TRUE;
    } else {
        D_8012684C = FALSE;
    }

    D_801267EC = arg0;
    D_80126824 = arg2;
    D_8012683C = arg3;
    D_80126844 = arg4;
    D_80126804 = arg5;
}

void menu_cinematic_init(void) {
    if (D_80126804 != NULL) {
        func_8009C674(gIntroCinematicObjectIndices);
        assign_racer_portrait_textures();
    }
    load_level_for_menu(D_801267EC[0], D_801267EC[1], D_801267EC[2]);
    gMenuDelay = 0;
    gMenuOptionCount = 0;
}

s32 menu_cinematic_loop(UNUSED s32 updateRate) {
    s32 i;
    s32 buttonsPressed;

    buttonsPressed = 0;
    if (gIgnorePlayerInputTime == 0) {
        for (i = 0; i < gNumberOfActivePlayers; i++) {
            buttonsPressed |= get_buttons_pressed_from_player(i);
        }
    }
    if (func_800214C4() != 0) {
        D_801267EC += 3;
        if (D_801267EC[0] >= 0) {
            load_level_for_menu(D_801267EC[0], D_801267EC[1], D_801267EC[2]);
        } else {
            if (D_8012684C) {
                music_change_off();
            }
            func_8009AF18();
            return D_80126824;
        }
    }
    if ((D_8012683C != 0) && (buttonsPressed & (A_BUTTON | START_BUTTON))) {
        func_8009AF18();
        return D_8012683C;
    }
    if ((D_80126844 != 0) && (buttonsPressed & B_BUTTON)) {
        func_8009AF18();
        return D_80126844;
    }
    if (D_80126804 != NULL) {
        for (i = 0; D_80126804[i] != -1; i++) {
            render_textured_rectangle(&sMenuCurrDisplayList, gRacerPortraits[D_80126804[i]], 24, 16 + (44 * i), 255,
                                      255, 255, 255);
        }
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}

void func_8009AF18(void) {
    if (D_80126804 != NULL) {
        func_8009C4A8(gIntroCinematicObjectIndices);
    }
}

/**
 * Initialise credits sequence.
 * Sets the ending text depending on when the credits were called.
 */
void menu_credits_init(void) {
    s32 cheat;
    s32 cheatIndex;
    u16 *cheatOffsets;
    Settings *settings;

    settings = get_settings();
    gMenuDelay = 0;
    D_80126BC4 = 0;
    D_80126BCC = 0;
    gMenuOptionCount = 0;
    gOpacityDecayTimer = 40;
    gMenuCurIndex = 0;
    D_80126BD0 = 0;
    D_80126BD8 = 0;
    D_80126BE0 = 0;
    set_background_fill_colour(0, 0, 0);
    if (osTvType == TV_TYPE_PAL) {
        viewport_menu_set(0, 0, 38, SCREEN_WIDTH, 224);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT_PAL);
    } else {
        viewport_menu_set(0, 0, 40, SCREEN_WIDTH, 196);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    copy_viewports_to_stack();
    camEnableUserView(0, 1);
    func_8009C674(gCreditsObjectIndices);
    allocate_menu_images(gCreditsImageIndices);
    assign_racer_portrait_textures();
    load_font(ASSET_FONTS_BIGFONT);
    music_voicelimit_set(24);
    gCreditsControlData[130] = CREDITS_END; // DONT show developer times
    if (gViewingCreditsFromCheat) {
        music_play(SEQUENCE_DARKMOON_CAVERNS);
        gCreditsArray[84] = gCreditsLastMessageArray[2]; // "THE END"
        gCreditsArray[85] = gCreditsLastMessageArray[3]; // "NO CHEAT"
        gCreditsArray[86] = gCreditsLastMessageArray[4]; // "THIS TIME."
        gViewingCreditsFromCheat = FALSE;
    } else {
        if (settings->bosses & 0x20) {
            music_play(SEQUENCE_CRESCENT_ISLAND);
            gCreditsArray[84] = gCreditsLastMessageArray[1];                      // "TO BE CONTINUED ..."
            gCreditsControlData[130] = CREDITS_DEV_TIMES(CREDITS_DEV_TIMES_TIME); // Show developer times.
            D_80126BCC = 9;
        } else {
            music_play(SEQUENCE_DARKMOON_CAVERNS);
            gCreditsArray[84] = gCreditsLastMessageArray[0]; // "THE END?"
        }

        cheat = gCheatsInCreditsArray[get_random_number_from_range(0, NUMBER_CHEATS_IN_CREDITS - 1)];
        cheatIndex = -1;
        while (cheat != 0) {
            cheat >>= 1;
            cheatIndex++;
        }

        // The first u16 of gCheatsAssetData is the total number of cheats.
        // After that is the offsets to the cheat strings.
        cheatOffsets = *gCheatsAssetData + 1;
        gCreditsArray[85] = (char *) (*gCheatsAssetData) + (cheatOffsets)[(cheatIndex << 1) + 1]; // Cheat name
        gCreditsArray[86] = (char *) (*gCheatsAssetData) + (cheatOffsets)[(cheatIndex << 1)];     // Cheat code
    }
    music_change_off();
    enable_new_screen_transitions();
    set_gIntDisFlag(TRUE);
}

/**
 * Render a fading rectangle over the screen during the credits to serve as a transition between levels.
 */
void render_credits_fade(s32 x1, s32 y1, s32 x2, s32 y2, s32 a) {
    if (a > 255) {
        a = 255;
    }
    if (a < 0) {
        a = 0;
    }

    gSPDisplayList(sMenuCurrDisplayList++, dCreditsFade);
    gDPSetPrimColor(sMenuCurrDisplayList++, 0, 0, 0, 0, 0, a);
    gDPSetCombineMode(sMenuCurrDisplayList++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPFillRectangle(sMenuCurrDisplayList++, x1, y1, x1 + x2, y1 + y2);
    gDPPipeSync(sMenuCurrDisplayList++);
    gDPSetPrimColor(sMenuCurrDisplayList++, 0, 0, 255, 255, 255, 255);

    reset_render_settings(&sMenuCurrDisplayList);
}

GLOBAL_ASM("asm/non_matchings/menu/menu_credits_loop.s")

void func_8009BCF0(void) {
    music_voicelimit_set(18);
    disable_new_screen_transitions();
    camDisableUserView(0, FALSE);
    set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, VIEWPORT_AUTO, VIEWPORT_AUTO);
    func_8009C4A8(gCreditsObjectIndices);
    unload_font(ASSET_FONTS_BIGFONT);
    set_gIntDisFlag(FALSE);
}

void func_8009BD5C(void) {
    unk80069D20 *temp_v0;
    s16 sp2A;
    s16 sp28;
    s16 sp26;
    f32 sp20;
    f32 sp1C;
    f32 sp18;

    set_active_viewports_and_max(0);
    set_active_camera(0);

    temp_v0 = (unk80069D20 *) get_active_camera_segment();

    sp2A = temp_v0->unk0;
    sp28 = temp_v0->unk2;
    sp26 = temp_v0->unk4;
    sp20 = temp_v0->unkC;
    sp1C = temp_v0->unk10;
    sp18 = temp_v0->unk14;
    temp_v0->unk4 = 0;
    temp_v0->unk2 = 0;
    temp_v0->unk0 = 0x8000;
    temp_v0->unkC = -32.0f;
    temp_v0->unk10 = -32.0f;
    temp_v0->unk14 = -32.0f;

    update_envmap_position(0, 0, -1);
    func_80066CDC(&sMenuCurrDisplayList, &sMenuCurrHudMat);

    temp_v0->unk0 = sp2A;
    temp_v0->unk2 = sp28;
    temp_v0->unk4 = sp26;
    temp_v0->unkC = sp20;
    temp_v0->unk10 = sp1C;
    temp_v0->unk14 = sp18;
}

void func_8009BE54() {
}

/**
 * Reset all menu related joystick inputs for each player.
 */
void reset_controller_sticks(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        gControllersXAxisDirection[i] = 0;
        gControllersYAxisDirection[i] = 0;
        gControllersXAxisDelay[i] = 0;
        gControllersYAxisDelay[i] = 0;
        gControllersXAxis[i] = 0;
        gControllersYAxis[i] = 0;
    }
}

#define STICK_DEADZONE 35
#define STICK_DELAY_AMOUNT 15

/**
 * Reads the stick inputs, then with the aid of a maximum range and a deadzone, writes it to the menu inputs.
 * Stick input delay is not time corrected, meaning holding the stick is slower at lower framerates.
 */
void update_controller_sticks(void) {
    s32 XClamp, YClamp;
    s32 i;
    for (i = 0; i < 4; i++) {
        XClamp = clamp_joystick_x_axis(i);
        YClamp = clamp_joystick_y_axis(i);
        gControllersXAxisDirection[i] = 0;
        gControllersYAxisDirection[i] = 0;

        if (XClamp < -STICK_DEADZONE && gControllersXAxis[i] >= -STICK_DEADZONE) {
            gControllersXAxisDirection[i] = -1;
            gControllersXAxisDelay[i] = 0;
        }
        if (XClamp > STICK_DEADZONE && gControllersXAxis[i] <= STICK_DEADZONE) {
            gControllersXAxisDirection[i] = 1;
            gControllersXAxisDelay[i] = 0;
        }
        if (YClamp < -STICK_DEADZONE && gControllersYAxis[i] >= -STICK_DEADZONE) {
            gControllersYAxisDirection[i] = -1;
            gControllersYAxisDelay[i] = 0;
        }
        if (YClamp > STICK_DEADZONE && gControllersYAxis[i] <= STICK_DEADZONE) {
            gControllersYAxisDirection[i] = 1;
            gControllersYAxisDelay[i] = 0;
        }

        gControllersYAxis[i] = YClamp;
        if (gControllersYAxis[i] < -STICK_DEADZONE) {
            gControllersYAxisDelay[i]++; //!@Delta
        } else if (gControllersYAxis[i] > STICK_DEADZONE) {
            gControllersYAxisDelay[i]++; //!@Delta
        } else {
            gControllersYAxisDelay[i] = 0;
        }

        if (gControllersYAxisDelay[i] > STICK_DELAY_AMOUNT) {
            gControllersYAxis[i] = 0;
            gControllersYAxisDelay[i] = 0;
        }

        gControllersXAxis[i] = XClamp;
        if (gControllersXAxis[i] < -STICK_DEADZONE) {
            gControllersXAxisDelay[i]++; //!@Delta
        } else if (gControllersXAxis[i] > STICK_DEADZONE) {
            gControllersXAxisDelay[i]++; //!@Delta
        } else {
            gControllersXAxisDelay[i] = 0;
        }

        if (gControllersXAxisDelay[i] > STICK_DELAY_AMOUNT) {
            gControllersXAxis[i] = 0;
            gControllersXAxisDelay[i] = 0;
        }
    }
}

/**
 * Reset the character id number slots to the default.
 */
void reset_character_id_slots(void) {
    s32 i;
    gTrackSelectRow = 1; // 1 = Dino Domain
    for (i = 0; i < 8; i++) {
        gCharacterIdSlots[i] = i;
    }
}

/**
 * Returns the value from gSaveFileIndex
 */
s32 get_save_file_index(void) {
    return gSaveFileIndex;
}

/**
 * Returns the track id that should be loaded. The value depends
 * on if whether you are playing in adventure or tracks mode.
 */
s32 get_track_id_to_load(void) {
    Settings *settings = get_settings();
    if (!gIsInTracksMode && gTrackSpecifiedWithTrackIdToLoad == 0) {
        if (settings->newGame) {
            return 0;
        } else {
            return settings->courseId;
        }
    }
    gTrackSpecifiedWithTrackIdToLoad = 0;
    return gTrackIdToLoad;
}

/**
 * Gets the character id from a slot index. Slot should be a value within [0,7]
 */
s8 get_character_id_from_slot(s32 slot) {
    return gCharacterIdSlots[slot];
}

/**
 * Unused duplicate of get_character_id_from_slot()
 */
s8 get_character_id_from_slot_unused(s32 slot) {
    return gCharacterIdSlots[slot];
}

/**
 * Gets the selected vehicle index for a player.
 * 0 = Car, 1 = Hovercraft, 2 = Plane
 */
s8 get_player_selected_vehicle(s32 playerNum) {
    return gPlayerSelectVehicle[playerNum];
}

/**
 * Sets the selected vehicle index for a player.
 * 0 = Car, 1 = Hovercraft, 2 = Plane
 */
void set_player_selected_vehicle(s32 playerNum, s32 index) {
    gPlayerSelectVehicle[playerNum] = index;
}

s8 *func_8009C274(void) {
    return D_801263DC;
}

/**
 * Returns the character Id from a controller index.
 */
s8 get_player_character(s32 controllerIndex) {
    if (controllerIndex < 0 || controllerIndex >= 4) {
        return -1;
    }
    if (!gActivePlayersArray[controllerIndex]) {
        return -1;
    }
    return gPlayersCharacterArray[controllerIndex];
}

/**
 * Sets the value of gIsInTracksMode, which determines if the player is in tracks mode or not.
 */
void enable_tracks_mode(s32 boolean) {
    gIsInTracksMode = boolean;
}

/**
 * Returns if the player is playing in the tracks mode instead of adventure.
 */
s32 is_in_tracks_mode(void) {
    return gIsInTracksMode;
}

/**
 * Sets the active & unlocked magic code flags.
 */
void set_magic_code_flags(s32 flags) {
    gActiveMagicCodes |= flags;
    gUnlockedMagicCodes |= flags;
}

#define CHEATS_ALLOWED_IN_ADVENTURE_AND_TIME_TRIAL                                                                   \
    (CHEAT_CONTROL_TT | CHEAT_CONTROL_DRUMSTICK | CHEAT_BIG_CHARACTERS | CHEAT_SMALL_CHARACTERS | CHEAT_HORN_CHEAT | \
     CHEAT_SELECT_SAME_PLAYER | CHEAT_TWO_PLAYER_ADVENTURE | CHEAT_ULTIMATE_AI | CHEAT_EPC_LOCK_UP_DISPLAY |         \
     CHEAT_ROM_CHECKSUM)

// Remember that ~ means NOT. So the challenge maps only allow cheats NOT included here.
#define CHEATS_ALLOWED_IN_CHALLENGES                                                                             \
    ~(CHEAT_START_WITH_10_BANANAS | CHEAT_DISABLE_BANANAS | CHEAT_DISABLE_WEAPONS | CHEAT_ALL_BALLOONS_ARE_RED | \
      CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_BLUE | CHEAT_ALL_BALLOONS_ARE_YELLOW |               \
      CHEAT_ALL_BALLOONS_ARE_RAINBOW)

/**
 * Filters active cheats based on different conditions. Also enables mirroring for Adventure 2.
 */
s32 get_filtered_cheats(void) {
    s32 cheats = gActiveMagicCodes;
    if (!gIsInTracksMode || is_time_trial_enabled()) {
        cheats &= CHEATS_ALLOWED_IN_ADVENTURE_AND_TIME_TRIAL;
    }
    if (!check_if_in_race()) {
        cheats &= ~CHEAT_MIRRORED_TRACKS; // Disable mirroring
    }
    if (get_map_race_type(get_settings()->courseId) & 0x40) {
        cheats &= CHEATS_ALLOWED_IN_CHALLENGES;
    }
    if (gIsInAdventureTwo && check_if_in_race()) {
        cheats |= CHEAT_MIRRORED_TRACKS; // Enable mirroring
    }
    return cheats;
}

/**
 * Returns the value in gNumberOfActivePlayers.
 */
s32 get_number_of_active_players(void) {
    return gNumberOfActivePlayers;
}

/**
 * Returns the number of active players.
 * However, it will explicitly return 2 players if you're on a track in 2 player adventure mode,
 * as it would otherwise return 1.
 */
s32 get_active_player_count(void) {
    unk8006BDB0 *temp = (unk8006BDB0 *) get_current_level_header();
    if (gIsInTwoPlayerAdventure && !gIsInTracksMode) {
        if (temp->unk4C == 0 || (temp->unk4C & 0x40) != 0) {
            return 2;
        }
    }
    return gNumberOfActivePlayers;
}

/**
 * Returns the number of racers for a multiplayer match.
 */
s32 get_multiplayer_racer_count(void) {
    if (!gIsInTracksMode) {
        return 6; // Two player adventure is fixed at 6 racers
    }
    if (gTrophyRaceWorldId) {
        return 6; // Trophy race is fixed at 6 racers
    }
    // gMultiplayerSelectedNumberOfRacers is either 0 (2 racers), 1 (4 racers), or 2 (6 racers)
    return (gMultiplayerSelectedNumberOfRacers + 1) << 1; // Doesn't match with multiply.
}

Settings **get_all_save_files_ptr(void) {
    return (Settings **) gSavefileData;
}

UNUSED void func_8009C49C(void) {
    gTitleScreenLoaded = 0;
}

void func_8009C4A8(s16 *arg0) {
    s32 index = 0;
    while (arg0[index] != -1) {
        func_8009C508(arg0[index++]);
    }
}

void func_8009C508(s32 arg0) {
    if (D_80126750[arg0] != 0) {
        if (gMenuObjects[arg0] != 0) {
            if ((((*gAssetsMenuElementIds)[arg0] & 0xC000) == 0xC000) && (gMenuObjects[arg0] != 0)) {
                set_free_queue_state(0);
                free_texture(gMenuObjects[arg0]);
                set_free_queue_state(2);
            } else {
                if ((*gAssetsMenuElementIds)[arg0] & 0x8000) {
                    free_sprite((Sprite *) (u32) gMenuObjects[arg0]);
                } else {
                    if ((*gAssetsMenuElementIds)[arg0] & 0x4000) {
                        free_object((Object *) (u32) gMenuObjects[arg0]);
                    } else {
                        free_3d_model((ObjectModel **) (u32) gMenuObjects[arg0]);
                    }
                }
            }
        }
        gMenuObjects[arg0] = 0;
        D_80126750[arg0] = 0;
        gMenuObjectsCount--;
        gParticlePtrList_flush();
    }
    if (gMenuObjectsCount == 0) {
        if (gMenuImageStack != NULL) {
            free_from_memory_pool(gMenuImageStack);
            gMenuImageStack = NULL;
        }
        if (*gAssetsMenuElementIds != NULL) {
            free_from_memory_pool(*gAssetsMenuElementIds);
            *gAssetsMenuElementIds = NULL;
            gMenuElementIdCount = (u16) 0;
        }
    }
}

void func_8009C674(s16 *textureIndex) {
    s32 index = 0;
    while (textureIndex[index] != -1) {
        func_8009C6D4(textureIndex[index++]);
    }
}

void func_8009C6D4(s32 arg0) {
    s32 i;
    LevelObjectEntryCommon entry;

    if (*gAssetsMenuElementIds == NULL) {
        *gAssetsMenuElementIds = (s16 *) load_asset_section_from_rom(ASSET_MENU_ELEMENT_IDS);
        for (gMenuElementIdCount = 0; (*gAssetsMenuElementIds)[gMenuElementIdCount] != -1; gMenuElementIdCount++) {}
        gMenuObjectsCount = 0;
        for (i = 0; i < gMenuElementIdCount; i++) {
            D_80126750[i] = FALSE;
        }
    }
    if (!D_80126750[arg0]) {
        i = (*gAssetsMenuElementIds)[arg0];

        if (((!arg0) && (!arg0)) && (!arg0)) {} // Fakematch

        if ((i & 0xC000) == 0xC000) {
            gMenuObjects[arg0] = (TextureHeader *) load_texture(i & 0x3FFF);
        } else if (i & 0x8000) {
            gMenuObjects[arg0] = (TextureHeader *) func_8007C12C(i & 0x3FFF, 0);
        } else if (i & 0x4000) {
            if (gMenuElementIdCount) {} // Fakematch
            entry.objectID = i & 0xFFFF;
            entry.size = 8;
            entry.x = 0;
            entry.y = 0;
            entry.z = 0;
            gMenuObjects[arg0] = (TextureHeader *) spawn_object(&entry, 0);
        } else {
            gMenuObjects[arg0] = (TextureHeader *) object_model_init(i & 0x3FFF, 0);
        }

        D_80126750[arg0] = TRUE;
        gMenuObjectsCount++;
    }
}

void allocate_menu_images(s16 *imageSet) {
    s32 index = 0;
    while (imageSet[index] != -1) {
        allocate_and_set_menu_image_properties(imageSet[index++]);
    }
}

void allocate_and_set_menu_image_properties(s32 imageID) {
    if (gMenuImageStack == NULL) {
        gMenuImageStack = allocate_from_main_pool_safe(sizeof(unk800DF510) * 18, COLOUR_TAG_RED);
    }

    gMenuImageStack[imageID].unk0 = sMenuImageProperties[imageID].unk0;
    gMenuImageStack[imageID].unk2 = sMenuImageProperties[imageID].unk2;
    gMenuImageStack[imageID].unk4 = sMenuImageProperties[imageID].unk4;
    gMenuImageStack[imageID].unk6 = sMenuImageProperties[imageID].unk6;
    gMenuImageStack[imageID].unkC = sMenuImageProperties[imageID].unkC;
    gMenuImageStack[imageID].unk10 = sMenuImageProperties[imageID].unk10;
    gMenuImageStack[imageID].unk14 = sMenuImageProperties[imageID].unk14;
    gMenuImageStack[imageID].unk8 = sMenuImageProperties[imageID].unk8;
    gMenuImageStack[imageID].unk18 = sMenuImageProperties[imageID].unk18;
    gMenuImageStack[imageID].unk1A = get_random_number_from_range(0, 0xFFFF);
    gMenuImageStack[imageID].unk1B = get_random_number_from_range(0, 0xFFFF);
    gMenuImageStack[imageID].unk1C = get_random_number_from_range(0, 0xFFFF);
    gMenuImageStack[imageID].unk1D = sMenuImageProperties[imageID].unk1D;
}

void func_8009CA58(void) {
}

void func_8009CA60(s32 stackIndex) {
    Object *new_var;
    unk8009CA602 *new_var2;
    Sprite *sprite;
    ObjectModel **temp;

    if (gMenuObjects[gMenuImageStack[stackIndex].unk6] != 0) {
        if (((*gAssetsMenuElementIds)[gMenuImageStack[stackIndex].unk6] & 0xC000) != 0xC000) {
            if ((*gAssetsMenuElementIds)[gMenuImageStack[stackIndex].unk6] & 0x4000) {
                if (0) {} // Fakematch
                new_var = (Object *) gMenuObjects[gMenuImageStack[stackIndex].unk6];
                new_var2 = (unk8009CA602 *) &gMenuImageStack[stackIndex];
                new_var->segment.trans.y_rotation = new_var2->trans.y_rotation;
                new_var->segment.trans.x_rotation = new_var2->trans.x_rotation;
                new_var->segment.trans.z_rotation = new_var2->trans.z_rotation;
                new_var->segment.trans.x_position = new_var2->trans.x_position;
                new_var->segment.trans.y_position = new_var2->trans.y_position;
                new_var->segment.trans.z_position = new_var2->trans.z_position;
                new_var->segment.trans.scale = new_var2->trans.scale;
                if (unused_800DF468 == 0) {
                    new_var->segment.animFrame = new_var2->unk1D;
                    new_var->segment.object.modelIndex = new_var2->unk18;
                }
                new_var->segment.object.opacity = sMenuGuiOpacity;
                render_object(&sMenuCurrDisplayList, &sMenuCurrHudMat, &sMenuCurrHudVerts, new_var);
            } else {
                if ((*gAssetsMenuElementIds)[gMenuImageStack[stackIndex].unk6] & 0x8000) {
                    sprite = (Sprite *) gMenuObjects[gMenuImageStack[stackIndex].unk6];
                    gDPSetPrimColor(sMenuCurrDisplayList++, 0, 0, sMenuGuiColourR, sMenuGuiColourG, sMenuGuiColourB,
                                    sMenuGuiOpacity);
                    gDPSetEnvColor(sMenuCurrDisplayList++, 255, 255, 255, 0);
                    render_ortho_triangle_image(&sMenuCurrDisplayList, &sMenuCurrHudMat, &sMenuCurrHudVerts,
                                                (ObjectSegment *) (&gMenuImageStack[stackIndex]), sprite,
                                                gMenuSpriteFlags);
                    gDPSetPrimColor(sMenuCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                } else {
                    if (sMenuGuiOpacity < 255) {
                        gDPSetPrimColor(sMenuCurrDisplayList++, 0, 0, 255, 255, 255, sMenuGuiOpacity);
                    } else {
                        gDPSetPrimColor(sMenuCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                    };
                    gDPSetEnvColor(sMenuCurrDisplayList++, 255, 255, 255, 0);
                    camera_push_model_mtx(&sMenuCurrDisplayList, &sMenuCurrHudMat,
                                          (ObjectTransform *) (&gMenuImageStack[stackIndex]),
                                          gTrackSelectWoodFrameHeightScale, 0);
                    temp = ((ObjectModel **) gMenuObjects[gMenuImageStack[stackIndex].unk6]);
                    render_track_selection_viewport_border(*temp);
                    apply_matrix_from_stack(&sMenuCurrDisplayList);
                    if (sMenuGuiOpacity < 255) {
                        gDPSetPrimColor(sMenuCurrDisplayList++, 0, 0, 255, 255, 255, 255);
                    }
                }
            }
        }
    }
}

/**
 * Render the border around the centre viewport in the track selection menu.
 * Comes in wood, iron and gold colours.
 */
void render_track_selection_viewport_border(ObjectModel *objMdl) {
    UNUSED s32 pad1[4];
    s32 flags;
    UNUSED s32 pad2[4];
    TextureHeader *tex;
    Triangle *tris;
    s32 triOffset;
    s32 vertOffset;
    Vertex *verts;
    s32 numVerts;
    s32 numTris;
    s32 texOffset;
    s32 texEnabled;
    s32 i;

    flags = RENDER_FOG_ACTIVE | RENDER_ANTI_ALIASING;
    if (sMenuGuiOpacity != 255) {
        flags = RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_ANTI_ALIASING;
    }
    for (i = 0; i < objMdl->numberOfBatches; i++) {
        if (!(objMdl->batches[i].flags & RENDER_Z_UPDATE)) {
            vertOffset = objMdl->batches[i].verticesOffset;
            triOffset = objMdl->batches[i].facesOffset;
            numVerts = objMdl->batches[i + 1].verticesOffset - vertOffset;
            numTris = objMdl->batches[i + 1].facesOffset - triOffset;
            verts = &objMdl->vertices[vertOffset];
            tris = &objMdl->triangles[triOffset];
            //!@bug Never true, since textureIndex is unsigned. This should've been either `== (u8)-1` or `== 0xFF`.
            if (objMdl->batches[i].textureIndex == -1) {
                tex = NULL;
                texEnabled = FALSE;
                texOffset = 0;
            } else {
                tex = objMdl->textures[objMdl->batches[i].textureIndex].texture;
                texEnabled = TRUE;
                texOffset = objMdl->batches[i].unk7 << 14;
            }
            load_and_set_texture(&sMenuCurrDisplayList, tex, flags, texOffset);

            gSPVertexDKR(sMenuCurrDisplayList++, OS_PHYSICAL_TO_K0(verts), numVerts, 0);
            gSPPolygon(sMenuCurrDisplayList++, OS_PHYSICAL_TO_K0(tris), numTris, texEnabled);
        }
    }
}

void func_8009CF68(s32 arg0) {
    if (gDoneTalkingToNPC[arg0] == 0) {
        if (arg0 != 3) {
            sCurrentMenuID = 0;
            gDialogueSubmenu = 0;
        }
        gNeedToCloseDialogueBox = TRUE;
        gDoneTalkingToNPC[arg0] = 1;
    }
}

/**
 * If the call to close dialogue has been made, this will begin hiding it.
 * It then also resets the menus stick inputs.
 */
void try_close_dialogue_box(void) {
    if (gNeedToCloseDialogueBox) {
        gNeedToCloseDialogueBox = FALSE;
        close_dialogue_box(1);
        reset_controller_sticks();
    }
}

/**
 * Top level function for controlling dialogue with NPC's.
 * Returning nonzero will trigger those NPC's to stop dialogue.
 */
s32 npc_dialogue_loop(u32 dialogueOption) {
    s32 result;

    gDoneTalkingToNPC[dialogueOption] = 0;
    if ((func_800C3400() != 0) && (dialogueOption != DIALOGUE_CHALLENGE)) {
        return 0;
    }
    if (gNeedToCloseDialogueBox) {
        return 0;
    }
    if (dialogueOption != DIALOGUE_CHALLENGE) {
        set_pause_lockout_timer(1);
    }
    result = 0;
    update_controller_sticks();
    assign_dialogue_box_id(1);
    open_dialogue_box(1);
    set_current_dialogue_background_colour(1, 0, 0, 0, 128);
    func_8001F450();
    switch (dialogueOption) {
        case DIALOGUE_TAJ:
            result = taj_menu_loop(); // Taj menu
            break;
        case DIALOGUE_TT:
            result = tt_menu_loop(); // T.T. menu
            break;
        case DIALOGUE_CHALLENGE:
            result = dialogue_challenge_loop(); // Taj challenge completed/failed menu
            break;
        case DIALOGUE_TROPHY:
            result = trophy_race_cabinet_menu_loop(); // Trophy race cabinet menu
            break;
        case DIALOGUE_RACERESULT:
            result = dialogue_race_defeat();
            break;
    }
    return result;
}

/**
 * Each dialogue option runs this. If the condition is true, it makes the text partially whiter.
 * Otherwise, it stays as normal, or fades out, depending on whether the option is accessable.
 */
void set_option_text_colour(s32 condition) {
    if (condition == FALSE) {
        set_current_text_colour(1, 0, 0, 0x7F, 0x5A, 0xFF); // Normal
        if (gDialogueOptionTangible != FALSE) {
            set_current_text_colour(1, 0, 0, 0x7F, 0x5A, 0x78); // Locked
        }
    } else {
        set_current_text_colour(1, 0xCF, 0xCF, 0xCF, 0x5A, 0xFF); // Selected Option
    }
    gDialogueOptionTangible = (u8) FALSE;
}

/**
 * Render a line of text at a given Y position, and pass through the text ID and option ID.
 */
void render_dialogue_option(char *text, s32 yOffset, s32 optionID) {
    set_option_text_colour(gDialogueSubmenu == sDialogueOptionMax);
    if (gDialogueSubmenu == sDialogueOptionMax) {
        gDialogueItemSelection = optionID;
    }
    render_dialogue_text(1, POS_CENTRED, gDialogueOptionYOffset, text, 1, HORZ_ALIGN_CENTER);
    gDialogueOptionYOffset = (s8) (gDialogueOptionYOffset + yOffset);
    sDialogueOptionMax = (s8) (sDialogueOptionMax + 1);
}

/**
 * Sets dialogue option when the joystick is moved.
 * Will wrap around if it goes out of bounds.
 */
void handle_menu_joystick_input(void) {
    if (gControllersYAxisDirection[0] < 0) {
        gDialogueSubmenu = gDialogueSubmenu + 1;
        sound_play(SOUND_MENU_PICK, NULL);
    } else if (gControllersYAxisDirection[0] > 0) {
        gDialogueSubmenu = gDialogueSubmenu - 1;
        sound_play(SOUND_MENU_PICK, NULL);
    }

    if (gDialogueSubmenu < 0) {
        gDialogueSubmenu = sDialogueOptionMax - 1;
    }

    if (gDialogueSubmenu >= sDialogueOptionMax) {
        gDialogueSubmenu = 0;
    }
}

void func_8009D324(void) {
    unused_800DF4D8 = 0;
}

/**
 * Sets the variable controlling which Taj Challenge dialogue is to be used.
 */
void set_next_taj_challenge_menu(s32 arg0) {
    gNextTajChallengeMenu = arg0;
}

/**
 * Sets the menu ID to the second passed number if it's equal to the first.
 */
void set_menu_id_if_option_equal(s32 IDToCheck, s32 IDToSet) {
    if (sCurrentMenuID == IDToCheck) {
        sCurrentMenuID = IDToSet;
    }
}

/**
 * Handles all of the rendering and logic of Taj's dialogue menu.
 */
s32 taj_menu_loop(void) {
    s32 sp2C;
    s32 buttonsPressed;
    Settings *settings;

    settings = get_settings();
    if (gNextTajChallengeMenu && sCurrentMenuID == 0) {
        sCurrentMenuID = -gNextTajChallengeMenu;
    }
    if (sCurrentMenuID == 0) {
        sCurrentMenuID = 1;
    }
    if ((sCurrentMenuID > 0) && (sCurrentMenuID < 4)) {
        set_current_dialogue_box_coords(1, 24, 16, 184, 124);
        set_dialogue_font(1, ASSET_FONTS_FUNFONT);
    }
    sp2C = 0;
    buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE);
    sDialogueOptionMax = 0;

    switch (sCurrentMenuID) {
        case 2:
        case 0x62:
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_VEHICLESELECT], 1,
                                 HORZ_ALIGN_CENTER); // VEHICLE SELECT
            gDialogueOptionYOffset = 30;
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_CAR], 20, 0);        // CAR
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_HOVERCRAFT], 20, 1); // HOVERCRAFT
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_PLANE], 20, 2);      // PLANE
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_MAINMENU], 20, 3);   // MAIN MENU
            break;
        case 3:
        case 0x63:
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_CHALLENGESELECT], 1,
                                 HORZ_ALIGN_CENTER); // CHALLENGE SELECT
            gDialogueOptionYOffset = 30;
            if (settings->tajFlags & TAJ_FLAGS_CAR_CHAL_UNLOCKED) {
                gDialogueOptionTangible = settings->tajFlags & TAJ_FLAGS_CAR_CHAL_COMPLETED;
                render_dialogue_option(gMenuText[ASSET_MENU_TEXT_CARCHALLENGE], 20, 0); // CAR CHALLENGE
            }
            if (settings->tajFlags & TAJ_FLAGS_HOVER_CHAL_UNLOCKED) {
                gDialogueOptionTangible = settings->tajFlags & TAJ_FLAGS_HOVER_CHAL_COMPLETED;
                render_dialogue_option(gMenuText[ASSET_MENU_TEXT_HOVERCHALLENGE], 20, 1); // HOVER CHALLENGE
            }
            if (settings->tajFlags & TAJ_FLAGS_PLANE_CHAL_UNLOCKED) {
                gDialogueOptionTangible = settings->tajFlags & TAJ_FLAGS_PLANE_CHAL_COMPLETED;
                render_dialogue_option(gMenuText[ASSET_MENU_TEXT_PLANECHALLENGE], 20, 2); // PLANE CHALLENGE
            }
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_MAINMENU], 20, 3); // MAIN MENU
            break;
    }

    switch (sCurrentMenuID) {
        case 0:
            // Hello Friend!
            // If you wish to change your vehicle, then summon me with your horn.
            // Either stop on the pad or beep when I am close to you!
            // Press A To Continue
            set_current_text(ASSET_GAME_TEXT_7);
            sCurrentMenuID = 1;
            unused_800DF4D8 = 1;
            break;
        case 1:
            gNextTajChallengeMenu = 0;
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_OPTIONS], 1,
                                 HORZ_ALIGN_CENTER); // OPTIONS
            gDialogueOptionYOffset = 30;
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_CHANGEVEHICLE], 20, 0); // CHANGE VEHICLE
            if (settings->tajFlags & TAJ_FLAGS_UNLOCKED_A_CHALLENGE) {
                render_dialogue_option(gMenuText[ASSET_MENU_TEXT_CHALLENGES], 20, 1); // CHALLENGES
            }
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_RETURN], 20, 2); // RETURN
            handle_menu_joystick_input();
            if (buttonsPressed & B_BUTTON) {
                sp2C = 3;
                sound_play(SOUND_MENU_BACK3, NULL);
            } else if (buttonsPressed & A_BUTTON) {
                sound_play(SOUND_SELECT2, NULL);
                switch (gDialogueItemSelection) {
                    case 1:
                        sCurrentMenuID = 3;
                        gDialogueSubmenu = 0;
                        play_taj_voice_clip(SOUND_VOICE_TAJ_CHALLENGE_MENU, TRUE);
                        break;
                    case 2:
                        sp2C = 3;
                        break;
                    case 0:
                        sCurrentMenuID = 2;
                        gDialogueSubmenu = 0;
                        play_taj_voice_clip(SOUND_VOICE_TAJ_SELECT_VEHICLE, TRUE);
                        break;
                }
            }
            break;
        case 2:
            handle_menu_joystick_input();
            if (buttonsPressed & B_BUTTON) {
                sound_play(SOUND_MENU_BACK3, NULL);
                play_taj_voice_clip(SOUND_VOICE_TAJ_MENUBACK, TRUE);
                sCurrentMenuID = 1;
                gDialogueSubmenu = 0;
            } else if (buttonsPressed & A_BUTTON) {
                if (gDialogueItemSelection != 3) {
                    sp2C = gDialogueItemSelection | 0x80;
                    sCurrentMenuID = 0x62;
                } else {
                    sCurrentMenuID = 1;
                    gDialogueSubmenu = 0;
                    play_taj_voice_clip(SOUND_VOICE_TAJ_MENUBACK, TRUE);
                }
            }
            break;
        case 3:
            handle_menu_joystick_input();
            if ((buttonsPressed & B_BUTTON) || ((buttonsPressed & A_BUTTON) && (gDialogueItemSelection == 3))) {
                sound_play(SOUND_MENU_BACK3, NULL);
                play_taj_voice_clip(SOUND_VOICE_TAJ_MENUBACK2, TRUE);
                sCurrentMenuID = 1;
                gDialogueSubmenu = 3;
            } else if (buttonsPressed & A_BUTTON) {
                sp2C = gDialogueItemSelection | 0x40;
                sound_play(SOUND_SELECT2, NULL);
                sCurrentMenuID = 0x63;
            }
            break;
        case -3: // Plane Challenge - To Test your flying skills you must race me around the Island!!
        case -2: // Hover Challenge - To Test your driving skills you must race me around the Island!!
        case -1: // Car Challenge - To Test your driving skills you must race me around the Island!!
            set_current_text(ASSET_GAME_TEXT_8 - sCurrentMenuID); // 9, 10, 11
            sCurrentMenuID = 4;
            break;
        case -4:
            set_current_text(ASSET_GAME_TEXT_17); // MY SKILLS ARE GREATER! - Better luck next time. - TRY AGAIN.
            gNextTajChallengeMenu = 0;
            sCurrentMenuID = 1;
            gDialogueSubmenu = 3;
            break;
        case -5:
            set_current_text(ASSET_GAME_TEXT_21); // Well Done! - You are a skilled racer.
            gNextTajChallengeMenu = 0;
            sCurrentMenuID = 7;
            gDialogueSubmenu = 0;
            break;
        case -8: // Well done! - Take this as a reward. - That was my last challenge. You have done well.
        case -7: // Well done! - Take this as a reward. - I'll See You Later.
        case -6: // Well done! - Take this as a reward. - I'll See You Later.
            set_current_text(ASSET_GAME_TEXT_12 - sCurrentMenuID); // 18, 19, 20
            sCurrentMenuID = 6;
            gDialogueSubmenu = 0;
            break;
        case 4:
            sp2C = (gNextTajChallengeMenu - 1) | 0x40;
            sCurrentMenuID = 5;
            close_dialogue_box(1);
            break;
        case 5:
            gNextTajChallengeMenu = 0;
            close_dialogue_box(1);
            break;
        case 6:
        case 7:
            sp2C = 4;
            if (sCurrentMenuID == 7) {
                sp2C = 3;
            }
            gNeedToCloseDialogueBox = FALSE;
            close_dialogue_box(1);
            gNextTajChallengeMenu = 0;
            sCurrentMenuID = 0;
            break;
    }
    return sp2C;
}

/**
 * Shows the dialogue options after you finish an unbeaten race in P2 or lower.
 */
s32 dialogue_race_defeat(void) {
    s32 state;
    s32 playerInput;

    set_current_dialogue_box_coords(1, 24, 16, 184, 135);
    set_dialogue_font(1, ASSET_FONTS_FUNFONT);
    state = 0;
    playerInput = get_buttons_pressed_from_player(PLAYER_ONE);
    sDialogueOptionMax = 0;
    gNextTajChallengeMenu = 0;
    render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_LOSETOTAJ_0], 1,
                         HORZ_ALIGN_CENTER); // BETTER LUCK
    render_dialogue_text(1, POS_CENTRED, 20, gMenuText[ASSET_MENU_TEXT_LOSETOTAJ_1], 1,
                         HORZ_ALIGN_CENTER); // NEXT TIME!
    gDialogueOptionYOffset = 50;
    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_TRYAGAIN], 20, 0); // TRY AGAIN
    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_EXIT], 20, 1);     // EXIT
    handle_menu_joystick_input();
    if (playerInput & A_BUTTON) {
        sound_play(SOUND_SELECT2, NULL);
        switch (gDialogueItemSelection) {
            case 0:
                state = 1;
                break;
            case 1:
                state = 2;
                break;
        }
    }
    return state;
}

/**
 * Main function for TT dialogue.
 * Handles the controls for navigating the main options, selecting time trial and viewing the game status.
 * Also has unused functions to handle pak swapping as well as displaying the messages about them.
 */
s32 tt_menu_loop(void) {
    s32 currentOption;
    s32 buttonsPressed;
    s32 i;
    s32 yPos1;
    u8 result;
    Settings *settings;

    settings = get_settings();

    if (is_in_two_player_adventure()) {
        settings->cutsceneFlags |= CUTSCENE_TT_HELP;
    }
    if (!(settings->cutsceneFlags & CUTSCENE_TT_HELP)) {
        sCurrentMenuID = TT_MENU_INTRODUCTION;
    }
    if ((sCurrentMenuID != TT_MENU_GAME_STATUS) && (sCurrentMenuID != TT_MENU_INTRODUCTION)) {
        currentOption = 120;
        if (has_ghost_to_save()) {
            currentOption = 136;
        }
        set_current_dialogue_box_coords(1, 24, 16, 192, currentOption);
    } else {
        set_current_dialogue_box_coords(1, 24, 16, 184, 220);
    }
    set_dialogue_font(1, ASSET_FONTS_FUNFONT);
    currentOption = 0;
    buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE) << 0;
    sDialogueOptionMax = 0;
    gDialogueOptionYOffset = 32;
    switch (sCurrentMenuID) {
        case TT_MENU_ROOT:
        case TT_MENU_EXIT:
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_OPTIONS], 1,
                                 HORZ_ALIGN_CENTER);                          // OPTIONS
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_STATUS], 20, 3); // STATUS
            if (!is_in_two_player_adventure()) {
                if (is_time_trial_enabled()) {
                    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_TIMETRIALON], 20, 0); // TIME TRIAL ON
                } else {
                    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_TIMETRIALOFF], 20, 0); // TIME TRIAL OFF
                }
                if (has_ghost_to_save()) {
                    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_SAVEGHOST], 20, 1); // SAVE GHOST
                }
            }
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_RETURN], 20, 2); // RETURN
            handle_menu_joystick_input();
            if (gDialogueItemSelection == 0) {
                if (gControllersXAxisDirection[0] > 0) {
                    if (!is_time_trial_enabled()) {
                        play_tt_voice_clip(SOUND_VOICE_TT_TIME_TRIAL_ON, TRUE);
                    }
                    set_time_trial_enabled(TRUE);
                } else if (gControllersXAxisDirection[0] < 0) {
                    if (is_time_trial_enabled() == 1) {
                        play_tt_voice_clip(SOUND_VOICE_TT_TIME_TRIAL_OFF, TRUE);
                    }
                    set_time_trial_enabled(FALSE);
                }
            }
            if ((buttonsPressed & A_BUTTON) && (sCurrentMenuID != TT_MENU_EXIT)) {
                if (gPreviousMenuID && !gPreviousMenuID && !gPreviousMenuID) {} // Fakematch
                switch (gDialogueItemSelection) {
                    case 1:
                        sound_play(SOUND_SELECT2, NULL);
                        gSaveGhostDelayCounter = 0;
                        gPreviousMenuID = TT_MENU_ROOT;
                        sCurrentMenuID = TT_MENU_SAVE_GHOST;
                        break;
                    case 3:
                        sound_play(SOUND_SELECT2, NULL);
                        play_tt_voice_clip(SOUND_VOICE_TT_GAME_STATUS, TRUE);
                        func_8009C674(D_800E1E2C);
                        allocate_menu_images(D_800E1E40);
                        D_800E1E28 = 1;
                        sCurrentMenuID = TT_MENU_GAME_STATUS;
                        break;
                }
                currentOption = gDialogueItemSelection + 1;
            } else if (buttonsPressed & B_BUTTON) {
                sound_play(SOUND_MENU_BACK3, NULL);
                currentOption = 3;
            }
            if (sCurrentMenuID == TT_MENU_GAME_STATUS) {
                currentOption = 0;
            }
            if (currentOption == 3) {
                sCurrentMenuID = TT_MENU_EXIT;
            }
            if (sCurrentMenuID == TT_MENU_EXIT) {
                currentOption = 3;
            }
            break;
        case TT_MENU_CONT_PAK_ERROR_1:
            i = 0;
            while (gTTSaveGhostPakErrorText[i] != NULL) {
                i++;
            }
            yPos1 = 58;
            if (i > 0) {
                i--;
                yPos1 -= (i << 2 << 1); // Might be fake?
                i = 0;
                while (gTTSaveGhostPakErrorText[i] != NULL) {
                    render_dialogue_text(1, POS_CENTRED, yPos1, gTTSaveGhostPakErrorText[i], 1, HORZ_ALIGN_CENTER);
                    yPos1 += 16;
                    i++;
                }
            }
            if (buttonsPressed & (A_BUTTON | B_BUTTON)) {
                sCurrentMenuID = TT_MENU_ROOT;
            }
            break;
        case TT_MENU_GAME_STATUS:
            if (buttonsPressed & (A_BUTTON | B_BUTTON)) {
                sCurrentMenuID = TT_MENU_ROOT;
                D_800E1E28 = 0;
                func_8009C4A8(D_800E1E2C);
                play_tt_voice_clip(SOUND_VOICE_TT_OKAY, TRUE);
            }
            break;
        case TT_MENU_INTRODUCTION: {
            /*
                0: HI, I'M TT.
                1:
                2: YOU CAN ASK ME
                3: ABOUT YOUR GAME
                4: STATUS OR SELECT
                5: MY TIME TRIAL MODE
                6: TO PRACTICE A
                7: LEVEL.
                8:
                9: I CAN ALSO SAVE
                10: YOUR BEST GHOSTS
                11: {NULL TO END THE CHAT}
            */
            // TT Has 12 different intro text lines. This will render them one by one until it hits the NULL line.
            i = ASSET_MENU_TEXT_TTINTRO_0;
            while (gMenuText[i] != NULL) {
                render_dialogue_text(1, POS_CENTRED, 6 + ((i - 52) * 16), gMenuText[i], 1, HORZ_ALIGN_CENTER);
                i++;
            }
            if (buttonsPressed & (A_BUTTON | B_BUTTON)) {
                settings->cutsceneFlags |= CUTSCENE_TT_HELP;
                sCurrentMenuID = TT_MENU_ROOT;
            }
        } break;
        case TT_MENU_INSERT_CONT_PAK:
            render_dialogue_text(1, POS_CENTRED, 34, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_3], 1,
                                 HORZ_ALIGN_CENTER); // If you wish to use
            render_dialogue_text(1, POS_CENTRED, 50, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_4], 1,
                                 HORZ_ALIGN_CENTER); // the Controller Pak
            render_dialogue_text(1, POS_CENTRED, 66, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_6], 1,
                                 HORZ_ALIGN_CENTER); // insert it now!
            if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                sound_play(SOUND_SELECT2, NULL);
                gSaveGhostDelayCounter = 0;
                gPreviousMenuID = TT_MENU_INSERT_RUMBLE_PAK;
                sCurrentMenuID = TT_MENU_SAVE_GHOST;
            } else if (buttonsPressed & B_BUTTON) {
                sound_play(SOUND_MENU_BACK3, NULL);
                sCurrentMenuID = TT_MENU_ROOT;
            }
            break;
        case TT_MENU_INSERT_RUMBLE_PAK:
            render_dialogue_text(1, POS_CENTRED, 34, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_3], 1,
                                 HORZ_ALIGN_CENTER); // If you wish to use
            render_dialogue_text(1, POS_CENTRED, 50, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_5], 1,
                                 HORZ_ALIGN_CENTER); // the Rumble Pak
            render_dialogue_text(1, POS_CENTRED, 66, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_6], 1,
                                 HORZ_ALIGN_CENTER); // insert it now!
            if (buttonsPressed & (A_BUTTON | B_BUTTON | START_BUTTON)) {
                sCurrentMenuID = TT_MENU_ROOT;
            }
            break;
        case TT_MENU_SAVE_GHOST:
            render_dialogue_text(1, POS_CENTRED, 50, gMenuText[ASSET_MENU_TEXT_PLEASEWAIT], 1,
                                 HORZ_ALIGN_CENTER); // PLEASE WAIT
            gSaveGhostDelayCounter++;
            if (gSaveGhostDelayCounter >= 5) {
                result = func_8001B738(0);
                if (result == CONTROLLER_PAK_CHANGED) {
                    result = func_8001B738(0);
                }
                switch (result) {
                    case CONTROLLER_PAK_GOOD:
                        sCurrentMenuID = gPreviousMenuID;
                        break;
                    case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
                        sCurrentMenuID = TT_MENU_INSERT_CONT_PAK;
                        break;
                    case CONTROLLER_PAK_NOT_FOUND:
                        // NO CONTROLLER PAK
                        // If you wish to change / Controller Pak or Rumble Pak, / please do so now.
                        gTTSaveGhostPakErrorText = sNoControllerPakMenuText;
                        sCurrentMenuID = TT_MENU_CONT_PAK_ERROR_1;
                        break;
                    case CONTROLLER_PAK_FULL:
                    case CONTROLLER_PAK_NO_ROOM_FOR_GHOSTS:
                        // CONTROLLER PAK FULL
                        // If you wish to change / Controller Pak or Rumble Pak, / please do so now.
                        gTTSaveGhostPakErrorText = sControllerPakFullMenuText;
                        sCurrentMenuID = TT_MENU_CONT_PAK_ERROR_1;
                        break;
                    case CONTROLLER_PAK_BAD_DATA:
                        // CORRUPT DATA.
                        // If you wish to change / Controller Pak or Rumble Pak, / please do so now.
                        // TRY AGAIN!
                        gTTSaveGhostPakErrorText = sCorruptDataMenuText;
                        sCurrentMenuID = TT_MENU_CONT_PAK_ERROR_1;
                        break;
                    case CONTROLLER_PAK_INCONSISTENT:
                    case CONTROLLER_PAK_WITH_BAD_ID:
                    case CONTROLLER_PAK_CHANGED:
                    case CONTROLLER_PAK_SWITCH_TO_RUMBLE:
                    default:
                        // BAD CONTROLLER PAK
                        // If you wish to change / Controller Pak or Rumble Pak, / please do so now.
                        gTTSaveGhostPakErrorText = sBadControllerPakMenuText;
                        sCurrentMenuID = TT_MENU_CONT_PAK_ERROR_1;
                        break;
                }
            }
            break;
    }
    if ((sCurrentMenuID == TT_MENU_CONT_PAK_ERROR_1) || (sCurrentMenuID == TT_MENU_CONT_PAK_ERROR_2) ||
        (sCurrentMenuID == TT_MENU_CONT_PAK_ERROR_3)) {
        render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_PAKERROR], 1, HORZ_ALIGN_CENTER); // PAK ERROR
    }

    return currentOption;
}

void func_8009E3D0(void) {
    s32 numBalloonsTensDigit;
    s32 y;
    s32 i;
    s32 x;
    s32 numOfItem;
    Settings *settings;
    s32 flag;
    s16 tempX;

    if (D_800E1E28 == 1) {
        D_800E1E28++;
        return;
    }
    settings = get_settings();
    func_80068508(TRUE);
    if (osTvType == TV_TYPE_PAL) {
        y = 10;
    } else {
        y = 20;
    }
    numOfItem = 8;
    if (settings->cutsceneFlags & 4) {
        numOfItem = 9;
    }
    tempX = -74;
    gMenuImageStack[numOfItem].unkC = tempX;
    gMenuImageStack[numOfItem].unk10 = (65 - y);
    func_8009CA60(numOfItem);
    sprite_opaque(0);
    tempX = -29;
    gMenuImageStack[0].unkC = tempX;
    gMenuImageStack[0].unk10 = (98 - y);
    gMenuImageStack[0].unkC -= 6.0f;

    flag = (settings->balloonsPtr[0] / 10); // settings->balloonsPtr[0] is the total balloon count.
    numBalloonsTensDigit = flag;
    if (numBalloonsTensDigit != 0) {
        gMenuImageStack[0].unk18 = numBalloonsTensDigit;
        func_8009CA60(0);
        gMenuImageStack[0].unkC += 12.0f;
    }
    gMenuImageStack[0].unk18 = (settings->balloonsPtr[0] % 10);
    func_8009CA60(0);
    tempX = -49;
    gMenuImageStack[10].unkC = tempX;
    gMenuImageStack[10].unk10 = (98 - y);
    func_8009CA60(10);
    sprite_opaque(1);
    y += 50;
    tempX = -89;
    gMenuImageStack[15].unkC = tempX;
    gMenuImageStack[15].unk10 = (95 - y);
    gMenuImageStack[15].unk18 = settings->wizpigAmulet;
    func_8009CA60(15);
    tempX = -29;
    gMenuImageStack[16].unkC = tempX;
    gMenuImageStack[16].unk10 = (95 - y);
    gMenuImageStack[16].unk18 = settings->ttAmulet;
    func_8009CA60(16);

    for (flag = 3, numOfItem = 0, i = 0; i < 16; flag <<= 2, i++) {
        if (flag == (settings->trophies & flag)) {
            numOfItem++;
        }
    }
    y += 50;
    for (x = 20, i = 0; i < 4; i++, x += 30) {
        gMenuImageStack[13].unkC = (x - 124);
        gMenuImageStack[13].unk10 = (95 - y);
        if (i < numOfItem) {
            gMenuImageStack[13].unk18 = 1;
        } else {
            gMenuImageStack[13].unk18 = 0;
        }
        func_8009CA60(13);
    }
    for (flag = 1, i = 0, numOfItem = 0; i < 16; flag <<= 1, i++) {
        if (flag == (settings->keys & flag)) {
            numOfItem++;
        }
    }
    y += 45;
    for (x = 20, i = 0; i < 4; i++, x += 30) {
        gMenuImageStack[14].unkC = (x - 124);
        gMenuImageStack[14].unk10 = (95 - (y));
        if (i < numOfItem) {
            gMenuImageStack[14].unk18 = 1;
        } else {
            gMenuImageStack[14].unk18 = 0;
        }
        func_8009CA60(14);
    }
    func_80068508(FALSE);
}

/**
 * Dialogue menu for the trophy cabinets in each world hub.
 */
s32 trophy_race_cabinet_menu_loop(void) {
    s32 currentOption;
    s32 buttonsPressed;

    set_current_dialogue_box_coords(1, 24, 16, 184, SCREEN_HEIGHT_HALF);
    set_dialogue_font(1, ASSET_FONTS_FUNFONT);
    currentOption = 0;
    buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE);
    render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_TROPHYRACE], 1, HORZ_ALIGN_CENTER); // TROPHY RACE
    if (gControllersYAxisDirection[0] < 0) {
        gDialogueSubmenu++;
    } else if (gControllersYAxisDirection[0] > 0) {
        gDialogueSubmenu--;
    }
    if (gDialogueSubmenu < 0) {
        gDialogueSubmenu = 0;
    }
    if (gDialogueSubmenu > 1) {
        gDialogueSubmenu = 1;
    }
    set_option_text_colour(gDialogueSubmenu == 0);
    render_dialogue_text(1, POS_CENTRED, 30, gMenuText[ASSET_MENU_TEXT_ENTERTROPHYRACE], 1,
                         HORZ_ALIGN_CENTER); // ENTER TROPHY RACE
    set_option_text_colour(gDialogueSubmenu == 1);
    render_dialogue_text(1, POS_CENTRED, 50, gMenuText[ASSET_MENU_TEXT_EXIT], 1, HORZ_ALIGN_CENTER); // EXIT
    if (buttonsPressed & A_BUTTON) {
        currentOption = gDialogueSubmenu + 1;
    }
    if (buttonsPressed & B_BUTTON) {
        currentOption = 2;
    }
    return currentOption;
}

/**
 * Blank function called when a dialogue box is opened.
 */
void dialogue_open_stub(void) {
}

/**
 * Blank function called when a dialogue box is closed.
 */
void dialogue_close_stub(void) {
}

/**
 * Renders a textbox with a displaylist.
 * Return value goes completely unused.
 */
f32 func_8009E9B0(UNUSED DialogueBoxBackground *textbox, Gfx **dlist, MatrixS **mat, Vertex **verts) {
    sMenuCurrDisplayList = *dlist;
    sMenuCurrHudMat = *mat;
    sMenuCurrHudVerts = *verts;
    set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (D_800E1E28 != 0 && sCurrentMenuID == 4) {
        func_8009E3D0();
    }
    *dlist = sMenuCurrDisplayList;
    *mat = sMenuCurrHudMat;
    *verts = sMenuCurrHudVerts;
    return TRUE;
}

u64 *get_eeprom_settings_pointer(void) {
    return &sEepromSettings;
}

s32 set_eeprom_settings_value(u64 valueToSet) {
    sEepromSettings |= valueToSet;
    mark_write_eeprom_settings();
    return TRUE;
}

s32 unset_eeprom_settings_value(u64 valueToUnset) {
    sEepromSettings &= ~valueToUnset;
    mark_write_eeprom_settings();
    return TRUE;
}

u64 get_eeprom_settings(void) {
    return sEepromSettings;
}

/**
 * Returns the current language being used by the game.
 * 0 = English, 1 = German, 2 = French, 3 = Japanese
 * Official Name: frontGetLanguage
 */
s32 get_language(void) {
    s32 language = LANGUAGE_ENGLISH;
    switch (sEepromSettings & 0xC) {
        case 4:
            language = LANGUAGE_GERMAN;
            break;
        case 8:
            language = LANGUAGE_FRENCH;
            break;
        case 12:
            language = LANGUAGE_JAPANESE;
            break;
    }
    return language;
}

/**
 * Sets the language used by the game. Even though German is not selectable in the US version, it is
 * still fully intact. Japanese is not properly implemented in the US 1.0 version of the game. If you
 * tried to switch to it, all you would see is the word "Japanese" used everywhere as a placeholder.
 */
void set_language(s32 language) {
    u64 langFlag = 0; // English

    switch (language) {
        case LANGUAGE_GERMAN:
            langFlag = 4;
            break;
        case LANGUAGE_FRENCH:
            langFlag = 8;
            break;
        case LANGUAGE_JAPANESE:
            langFlag = 12;
            break;
    }

    sEepromSettings &= ~0xC;     // Set bits 3 and 4 low first
    sEepromSettings |= langFlag; // Then set them according to the selected lang

    load_menu_text(language);
    mark_write_eeprom_settings();
}

/**
 * Returns TRUE if the player has adventure two unlocked.
 */
s32 is_adventure_two_unlocked(void) {
    return sEepromSettings & 1;
}

/**
 * Returns 1 if the player is in adventure 2
 */
s32 is_in_adventure_two(void) {
    return gIsInAdventureTwo;
}

/**
 * Returns 1 if the player is in the two player adventure mode.
 * This will automatically return 0 while in tracks mode.
 */
s32 is_in_two_player_adventure(void) {
    if (is_in_tracks_mode()) {
        return FALSE;
    }
    return gIsInTwoPlayerAdventure;
}

/**
 * Returns 1 if T.T. is avaliable to use, or 0 if not.
 */
s32 is_tt_unlocked(void) {
    return gActiveMagicCodes & CHEAT_CONTROL_TT;
}

/**
 * Returns 1 if Drumstick is avaliable to use, or 0 if not.
 */
s32 is_drumstick_unlocked(void) {
    return gActiveMagicCodes & CHEAT_CONTROL_DRUMSTICK;
}
