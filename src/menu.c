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

DrawTexture *D_80126390;
DrawTexture *D_80126394;
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

s32 gIgnorePlayerInputTime; // A set amount of time to ignore player input.
UNUSED s32 sUnused_801263C8; // Set to 0 in menu_init, and never again.
CharacterSelectData (*gCurrCharacterSelectData)[10]; //Some sort of character list? Cares if T.T. and Drumstick are unlocked

s32 D_801263D0; //Compared for equality to gTrackIdForPreview
s8 gActivePlayersArray[MAXCONTROLLERS]; //Boolean value for each controller if it's active with a player.
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
u8 D_80126430[8]; //Contains the order of racer indices that tell you what place they are in.
s8 D_80126438[16];

//Eeeprom save data bits stored at address 0xF
//bit 0      = Adventure Two is Unlocked
//bit 1      = Used to set the CHEAT_CONTROL_DRUMSTICK magic code flag. Drumstick is unlocked flag?
//bits 2-3   = Current language value
//bits 4-23  = Used to set the CHEAT_CONTROL_TT magic code flag. Could be tracks where TT has been beat?
//bit 24     = Unknown, but it's set as a default high bit.
//bit 25     = Seems to be a flag for whether subtitles are enabled or not.
//bits 26-55 = Unknown, but it could be a set of flags for unlocked tracks
//bits 56-63 = Checksum bits. These are calculated from the previous bits,
//             and validated using calculate_eeprom_settings_checksum.
//             If the checksum fails, the settings are reset to just
//             bits 24/25 being high.
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
s32 D_801264D4;
s8 gDialogueSubmenu;
u8 *D_801264DC; //gGhostLevelIDs?
s8 D_801264E0;
s8 D_801264E1;

s8 sCurrentMenuID;
u8 *D_801264E4; //gGhostSomethings?
s32 D_801264E8;
u8 *D_801264EC; //gGhostVehicleIds?
s32 D_801264F0[2];
s16 *D_801264F8[3]; //gGhostChecksums?
s8 sDialogueOptionMax;
s32 D_80126508;
s16 D_8012650C;
s8 gDialogueOptionYOffset;
s32 D_80126510;
s16 D_80126514;
s8 gDialogueItemSelection;
s32 D_80126518;
s32 D_8012651C;
s32 D_80126520;
s32 D_80126524;
s32 D_80126528;
s32 D_8012652C;
Settings *gSavefileData[4];
s8 D_80126540;
s8 D_80126541;
s32 D_80126544;
s32 gMultiplayerSelectedNumberOfRacersCopy; // Saved version gMultiplayerSelectedNumberOfRacers?
TextureHeader *gMenuTextures[128];              // lookup table? TEXTURES
u8 D_80126750[128]; // Seems to be a boolean for "This texture exists" for the above array.
s32 D_801267D0;
s32 D_801267D4;
s32 D_801267D8[5]; //Buttons pressed per player plus an extra?
s8 *D_801267EC;
s32 D_801267F0[5];
s8 *D_80126804;
s32 D_80126808[MAXCONTROLLERS]; //Soundmask values
s16 D_80126818[2];
s32 D_8012681C;
s16 D_80126820;
s32 D_80126824;
UNUSED s8 sUnused_80126828; // Set to 0 in menu_init, and never used again.
s32 D_8012682C;
s16 D_80126830[4];
s16 D_80126838;
s16 D_8012683A;
s32 D_8012683C;
s32 D_80126840;
s32 D_80126844;
s32 D_80126848;
s32 D_8012684C;
s32 *D_80126850; //Never set, but it's read? Is it part of a larger struct being set?
s32 D_80126854;
s32 D_80126858;
s32 D_8012685C;
s32 D_80126860;
s32 gTitleDemoIndex;
s16 gTitleDemoTimer;
s32 gTitleRevealTimer;
f32 gTitleAudioCounter;
s8 *sTitleScreenDemoIds; //Misc Asset 66 - title_screen_demo_ids.bin - 12 or 13 values.
s32 D_80126878[24];
f32 D_801268D8;
s32 D_801268DC;
s32 D_801268E0;
s32 D_801268E4;
s16 D_801268E8[4][6]; //Track Select values?
s16 gFFLUnlocked;
UNUSED s32 D_8012691C;
UNUSED s32 D_80126920;
s32 D_80126924;
s32 D_80126928;
s32 D_8012692C;
TrackRenderDetails gTrackSelectRenderDetails[9];
s8 gPlayerSelectVehicle[4]; // Unknown number of entries.
u8 D_801269C4[4];
s32 D_801269C8;
s32 D_801269CC;
char *gAudioOutputStrings[3];
f32 gTrackSelectX;
char *gMusicTestString;
f32 gTrackSelectY;
f32 D_801269E8;
f32 D_801269EC;
s32 D_801269F0;
s32 gSelectedTrackX;
s32 gSelectedTrackY;
s32 *D_801269FC;
s32 D_80126A00;
unk800861C8 *D_80126A04; //Shares it's allocation with D_80126A0C
s32 D_80126A08;
unk800861C8 *D_80126A0C; //Allocated 2560 bytes in menu_save_options_init. Possibly an array of 2 large structs.
s32 D_80126A10;
s32 D_80126A14;
s32 D_80126A18;
s32 D_80126A1C;
s32 sControllerPakNotesFree[MAXCONTROLLERS]; // Looks to be an array for number notes free in each controller memory pak
u8 sControllerPakIssueNotFound[MAXCONTROLLERS]; //Flag to see if there's no known issues for the given controller pak
u8 sControllerPakFatalErrorFound[MAXCONTROLLERS]; //Flag to see if there's a fatal error for the given controller pak
u8 sControllerPakNoFreeSpace[MAXCONTROLLERS]; //Flag to see if there's no free space for the given controller pak
u8 sControllerPakBadData[MAXCONTROLLERS]; //Flag to see if there's bad data for the given controller pak
char *gMenuOptionText[8]; //Menu Text
u8 sControllerPakDataPresent[MAXCONTROLLERS]; //Flag to see if there's data present for the given controller pak? Not sure
u8 *D_80126A64;
s32 gMenuOption; //sCurrentControllerIndex?
s32 D_80126A6C;
s32 D_80126A70;
s32 D_80126A74;
s32 D_80126A78;
s32 D_80126A7C;
s32 D_80126A80[4];
s32 D_80126A90;
s32 D_80126A94;
s32 D_80126A98;
s32 D_80126A9C;
char *D_80126AA0[16]; //Text to render
u8 *sCurrentControllerPakAllFileNames[16]; //Every file name on the controller pak
u8 *sCurrentControllerPakAllFileExtensions[16]; //Every file extension on the controller pak
u8  sCurrentControllerPakAllFileTypes[16]; //File type of all files on controller pak
u32 sCurrentControllerPakAllFileSizes[16]; //File size of all files on controller pak
u32 sCurrentControllerPakFreeSpace; //Space available in current controller pak
s32 sControllerPakMenuNumberOfRows; //8 if PAL, 7 if not
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
u8 D_80126C58[20];
s32 *D_80126C6C;
s32 gNumOnscreenMagicCodes;
char *D_80126C74;
s32 D_80126C78;
s32 D_80126C7C;
s16 D_80126C80[32];
s32 D_80126CC0;

/******************************/

/************ .data ************/

s8 D_800DF450 = 0;
f32 D_800DF454 = 1.0f;
s32 gResetTitleScale = 1;
s32 gTitleScreenCurrentOption = 0; // 0 = "Start", 1 = "Options"
s32 D_800DF460 = 0; // Currently selected menu index? Reused in different menus.
s32 D_800DF464 = 4; // Currently unknown, might be a different type.
s32 D_800DF468 = 0;
s32 D_800DF46C = 0;
s32 gCurrentMenuId = 0; // Currently unknown, might be a different type.
s32 D_800DF474 = 0;     // Currently unknown, might be a different type.
s32 D_800DF478 = 0;     // Currently unknown, might be a different type.
s32 gMenuDelay = 0;
s32 gNumberOfReadyPlayers = 0;
s32 D_800DF484 = 0; // Currently unknown, might be a different type.
s32 D_800DF488 = 0;
s32 D_800DF48C = 0; // Currently unknown, might be a different type.
s32 D_800DF490 = 0; // Currently unknown, might be a different type.
s32 gIsInAdventureTwo = 0;
s32 gPlayerHasSeenCautionMenu = 0;
s32 *gMenuTextLangTable = NULL;

char **gMenuText = NULL;

u8 sMenuGuiColourR = 0xFF;
u8 sMenuGuiColourG = 0xFF;
u8 sMenuGuiColourB = 0xFF;

u8  D_800DF4B0              = 0;
s32 D_800DF4B4              = 0;
s32 gIsInTracksMode         = 1;
s32 gNumberOfActivePlayers  = 1;
s32 gIsInTwoPlayerAdventure = 0;
s32 gTrackIdForPreview    = ASSET_LEVEL_CENTRALAREAHUB;
s32 gTrackSelectRow         = 0; // 1 = Dino Domain, 2 = Sherbet Island, etc.
s32 gSaveFileIndex          = 0;
s32 D_800DF4D0              = 0; // Unused?
s32 gTrackIdToLoad          = 0;
s8 D_800DF4D8               = 1;
s8 gNextTajChallengeMenu    = FALSE;
s8 gNeedToCloseDialogueBox  = FALSE;

s8 D_800DF4E4[4] = {
    0, 0, 0, 0
};

s32 D_800DF4E8 = 0; // Currently unknown, might be a different type.
s8 gDialogueOptionTangible = FALSE;

// Unused?
s32 D_800DF4F0[] = {
    0x4000, 0x8000, 0x1000, 0x2000, 0x8000, 0x10, 0x400, 0x00
};

//MenuElement?
unk800DF510 sMenuImageProperties[18] = {
    { 0, 0, 0, 0x00,   1.0f, 0.0f,   0.0f,  -32.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x01,   1.0f, 0.0f,   0.0f,  -32.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x02,   1.0f, 0.0f,   0.0f,  -32.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x03,   1.0f, 0.0f,   0.0f,  -32.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x05, 0.215f, 0.0f,   0.0f, -500.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x06, 0.215f, 0.0f,   0.0f, -500.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x07, 0.215f, 0.0f,   0.0f, -500.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x04, 0.125f, 0.0f, -40.0f, -500.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x5B,  0.75f, 0.0f,   0.0f,    0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x5C,  0.75f, 0.0f,   0.0f,    0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x42,   1.0f, 0.0f,   0.0f,    0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x40,   1.0f, 0.0f,   0.0f,    0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x41,   1.0f, 0.0f,   0.0f,    0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x4C,   1.0f, 0.0f,   0.0f,    0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x4D,   1.0f, 0.0f,   0.0f,    0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x4E,   1.0f, 0.0f,   0.0f,    0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x4F,   1.0f, 0.0f,   0.0f,    0.0f, 0, 0, 0, 0, 0, { 0 } },
    { 0, 0, 0, 0x5D,   1.0f, 0.0f,   0.0f,    0.0f, 0, 0, 0, 0, 0, { 0 } },
};

s16 *gAssetsMenuElementIds[1] = { NULL }; // This is probably not correct.
s16 D_800DF754 = 0;
s16 D_800DF758 = 0;
unk800DF510 *gMenuImageStack = NULL;

s32 sMenuMusicVolume = 0x7F;
s32 sMenuGuiOpacity = 0xFF;
s32 D_800DF768 = 1;

FadeTransition sMenuTransitionFadeInFast = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 10, -1);
FadeTransition sMenuTransitionFadeIn = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 18, -1);
FadeTransition sMenuTransitionFadeOut = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_OUT, FADE_COLOR_BLACK, 18, 0);
UNUSED FadeTransition sMenuTransitionFadeInWhite = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_WHITE, 18, -1);
UNUSED FadeTransition sMenuTransitionFadeOutWhite = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_OUT, FADE_COLOR_WHITE, 18, 0);

s32 D_800DF794 = 4;
MenuElement *D_800DF798 = NULL;
s32 D_800DF79C = 0;

s32 D_800DF7A0 = 0;
char *gTitleMenuStrings[3] = { 0, 0, 0 };

// Version text shown on the title screen? See 1:15 in https://www.youtube.com/watch?v=OHSCLcA74ao.
char gVersionDisplayText[20] = "VERSION XXXXXXXX";

// "Diddy Kong Racing" logo texture indices?
s16 sGameTitleTileTextures[12] = {
    TEXTURE_TITLE_SEGMENT_01,
    TEXTURE_TITLE_SEGMENT_02,
    TEXTURE_TITLE_SEGMENT_03,
    TEXTURE_TITLE_SEGMENT_04,
    TEXTURE_TITLE_SEGMENT_05,
    TEXTURE_TITLE_SEGMENT_06,
    TEXTURE_TITLE_SEGMENT_07,
    TEXTURE_TITLE_SEGMENT_08,
    TEXTURE_TITLE_SEGMENT_09,
    TEXTURE_TITLE_SEGMENT_10,
    TEXTURE_TITLE_SEGMENT_11, 
    -1
};

DrawTexture sGameTitleTileOffsets[12] = {
    { NULL, -75, -32 },
    { NULL, -60, -32 },
    { NULL, -45, -32 },
    { NULL, -30, -32 },
    { NULL, -15, -32 },
    { NULL,   0, -32 },
    { NULL,  15, -32 },
    { NULL,  30, -32 },
    { NULL,  45, -32 },
    { NULL,  60, -32 },
    { NULL,  75, -32 },
    { NULL,   0,   0 }
};

// Title screen cinematic text
unk800DF83C D_800DF83C[10] = {
    { "TIMBER", 14.0f, 14.5f, 16.5f, 17.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "BUMPER", 19.0f, 19.5f, 21.5f, 22.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "CONKER", 24.0f, 24.5f, 26.5f, 27.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "TIPTUP", 29.0f, 29.5f, 31.5f, 32.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "DRUMSTICK", 35.0f, 35.5f, 37.5f, 38.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "PIPSY", 40.0f, 40.5f, 42.5f, 43.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "BANJO", 45.0f, 45.5f, 47.5f, 48.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "KRUNCH", 50.0f, 50.5f, 52.5f, 53.0f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "WIZPIG", 57.5f, 58.0f, 60.0f, 60.5f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f },
    { "DIDDY", 63.5f, 64.0f, 66.0f, 66.5f, -80.0f, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT_HALF, SCREEN_HEIGHT_FLOAT - 32.0f, SCREEN_WIDTH_FLOAT + 80.0f, SCREEN_HEIGHT_FLOAT - 32.0f }
};

s32 D_800DF9F4 = 0;

u16 D_800DF9F8[12] = {
    0xFFFF, 0x00FF, 0xCC00, 0xFF00, 0xFF99, 0x00FF, 0xFFFF, 0x6600, 0x00FF, 0xFF33, 0x0000, 0x0F78
};

char *gOptionMenuStrings[7] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

s16 gOptionMenuTextures[8] = {
    0x3D, 0x3C, 0x3F, 0x3E, 0x44, -1, -1, 0
};

unk800DFA3C gAudioMenuStrings[8] = {
    { 160,  80, 0xFF, 0xFF, 0xFF,    0, 0xFF, 0, 0, 12, NULL },
    { 160, 104, 0xFF, 0xFF, 0xFF,    0, 0xFF, 0, 0, 12, NULL },
    { 160, 144, 0xFF, 0xFF, 0xFF,    0, 0xFF, 0, 0, 12, NULL },
    { 160, 192, 0xFF, 0xFF, 0xFF,    0, 0xFF, 0, 0, 12, NULL },
    { 161,  35,    0,    0,    0, 0xFF, 0x80, 2, 0, 12, NULL },
    { 160,  32, 0xFF, 0x80, 0xFF,    0, 0xFF, 2, 0, 12, NULL },
    { 160, 188, 0xFF, 0xFF, 0xFF,    0, 0xFF, 0, 0, 12, NULL },
    {   0,   0,    0,    0,    0,    0,    0, 0, 0,  0, NULL },
};

s32 D_800DFABC = 0; // Currently unknown, might be a different type.

s32 gSfxVolumeSliderValue = 256;   // Value from 0 to 256
s32 gMusicVolumeSliderValue = 256; // Value from 0 to 256

s32 D_800DFAC8 = 0;

// Unsure about typing here.
u16 D_800DFACC[8] = {
    0x4040, 0xFFFF, 0xFF40, 0x40FF, 0xFFD0, 0x40FF, 0x40FF, 0x40FF
};

s32 D_800DFADC = 0; // Currently unknown, might be a different type.
s32 D_800DFAE0 = 0; // Currently unknown, might be a different type.

char *D_800DFAE4[6] = { 0, 0, 0, 0, 0, 0 };
char *D_800DFAFC[6] = { 0, 0, 0, 0, 0, 0 };
char *D_800DFB14[6] = { 0, 0, 0, 0, 0, 0 };
char *D_800DFB2C[5] = { 0, 0, 0, 0, 0 };
char *D_800DFB40[7] = { 0, 0, 0, 0, 0, 0, 0 };
char *D_800DFB5C[6] = { 0, 0, 0, 0, 0, 0 };
char *D_800DFB74[6] = { 0, 0, 0, 0, 0, 0 };
char *D_800DFB8C[6] = { 0, 0, 0, 0, 0, 0 };
char *D_800DFBA4[6] = { 0, 0, 0, 0, 0, 0 };
char *D_800DFBBC[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
s32 D_800DFBDC = 0;

// Unused?
char **D_800DFBE0[10] = {
    D_800DFAE4, D_800DFAFC, D_800DFB14, D_800DFB2C, D_800DFB40, D_800DFB5C, D_800DFB8C, D_800DFBA4, D_800DFB74, D_800DFBBC
};

s32 D_800DFC08 = 0;      // Currently unknown, might be a different type.
s32 D_800DFC0C = 0xFFFF; // Currently unknown, might be a different type.

DrawTexture D_800DFC10[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800DFC20[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800DFC30[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800DFC40[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800DFC50[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800DFC60[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };

// Unused?
u8 D_800DFC70[8] = { 0x40, 0x40, 0x04, 0x04, 0xFF, 0, 0, 0 };

s16 D_800DFC78[26] = {
    0x0024, 0x0025, 0x0018, 0x0019,
    0x001A, 0x001B, 0x001C, 0x001D,
    0x003D, 0x003F, 0x003E, 0x003C,
    0x0043, 0x0044, 0x0045, 0x0046,
    0x0047, 0x0048, 0x0049, 0x004A,
    0x004B, 0x0040, 0x0041, 0x0002,
    0xFFFF, 0x0000
};

//Image textures, likely for the below menu
s16 D_800DFCAC[4] = {
    0x000B, 0x000C, 0x0002, 0xFFFF
};

MenuElement gControllerPakMenuElement[7] = {
    { 161, 32,  161, 33,  161, 32,  0,   0,   0,   255, 128, ASSET_FONTS_BIGFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 160, 30,  160, 30,  160, 30,  255, 255, 255, 0,   255, ASSET_FONTS_BIGFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 160, 112, 160, 112, 160, 112, 255, 255, 255, 0,   255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 160, 128, 160, 128, 160, 128, 255, 255, 255, 0,   255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 160, 192, 160, 192, 160, 192, 255, 255, 255, 0,   255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 160, 208, 160, 208, 160, 208, 255, 255, 255, 0,   255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   ASSET_FONTS_FUNFONT, 0,  0, { NULL }, {{ 0, 0, 0, 0 }} },
};

s32 gShowControllerPakMenu = FALSE;

s32 gActiveMagicCodes = 0;
s32 gUnlockedMagicCodes = 0;

char *gMagicCodeMenuStrings[5] = { 0, 0, 0, 0, 0 };

u8 D_800DFDB4[10][2] = {
    { 0x0F, 0x64 },
    { 0x0C, 0x07 },
    { 0x09, 0x64 },
    { 0x0A, 0x64 },
    { 0x08, 0x64 },
    { 0x0B, 0x64 },
    { 0x0D, 0x64 },
    { 0x0E, 0x64 },
    { 0x05, 0x64 },
    { 0x04, 0x64 },
};

s16 D_800DFDC8[2] = { -1, 0 };
s16 D_800DFDCC[2] = { -1, 0 };

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
/*    Name         Up                  Down                Left                                Right                            Voice ID */
CharacterSelectData gCharacterSelectBytesDefault[] = {
    /*Krunch*/ { { NONE, NONE },     { CONKER, NONE },   { NONE, NONE, NONE, NONE },         { DIDDY, BUMPER, BANJO, NONE },     0x0000 },
    /*Diddy*/  { { NONE, NONE },     { TIPTUP, NONE },   { KRUNCH, NONE, NONE, NONE },       { BUMPER, BANJO, NONE, NONE },      0x0009 },
    /*Bumper*/ { { NONE, NONE },     { PIPSY, NONE },    { DIDDY, KRUNCH, NONE, NONE },      { BANJO, NONE, NONE, NONE },        0x0001 },
    /*Banjo*/  { { NONE, NONE },     { TIMBER, NONE },   { BUMPER, DIDDY, KRUNCH, NONE },    { NONE, NONE, NONE, NONE },         0x0005 },
    /*Conker*/ { { KRUNCH, NONE },   { NONE, NONE },     { NONE, NONE, NONE, NONE },         { TIPTUP, PIPSY, TIMBER, NONE },    0x0003 },
    /*Tiptup*/ { { DIDDY, NONE },    { NONE, NONE },     { CONKER, NONE, NONE, NONE },       { PIPSY, TIMBER, NONE, NONE },      0x0002 },
    /*Pipsy*/  { { BUMPER, NONE },   { NONE, NONE },     { TIPTUP, CONKER, NONE, NONE },     { TIMBER, NONE, NONE, NONE },       0x0007 },
    /*Timber*/ { { BANJO, NONE },    { NONE, NONE },     { PIPSY, TIPTUP, CONKER, NONE },    { NONE, NONE, NONE, NONE },         0x0004 }
};

// Drumstick is unlocked, but T.T is not.
/*    Name            Up                     Down                Left                                  Right                              Voice ID */
CharacterSelectData gCharacterSelectBytesDrumStick[] = {
    /*Krunch*/    { { NONE, NONE },        { CONKER, NONE },   { NONE, NONE, NONE, NONE },           { DIDDY, DRUMSTICK, BUMPER, BANJO }, 0x0000 },
    /*Diddy*/     { { NONE, NONE },        { CONKER, TIPTUP }, { KRUNCH, NONE, NONE, NONE },         { DRUMSTICK, BUMPER, BANJO, NONE },  0x0009 },
    /*Bumper*/    { { NONE, NONE },        { PIPSY, TIMBER },  { DRUMSTICK, DIDDY, KRUNCH, NONE },   { BANJO, NONE, NONE, NONE },         0x0001 },
    /*Banjo*/     { { NONE, NONE },        { TIMBER, NONE },   { BUMPER, DRUMSTICK, DIDDY, KRUNCH }, { NONE, NONE, NONE, NONE },          0x0005 },
    /*Conker*/    { { KRUNCH, DIDDY },     { NONE, NONE },     { NONE, NONE, NONE, NONE },           { TIPTUP, PIPSY, TIMBER, NONE },     0x0003 },
    /*Tiptup*/    { { DIDDY, DRUMSTICK },  { NONE, NONE },     { CONKER, NONE, NONE, NONE },         { PIPSY, TIMBER, NONE, NONE },       0x0002 },
    /*Pipsy*/     { { DRUMSTICK, BUMPER }, { NONE, NONE },     { TIPTUP, CONKER, NONE, NONE },       { TIMBER, NONE, NONE, NONE },        0x0007 },
    /*Timber*/    { { BUMPER, BANJO },     { NONE, NONE },     { PIPSY, TIPTUP, CONKER, NONE },      { NONE, NONE, NONE, NONE },          0x0004 },
    /*Drumstick*/ { { NONE, NONE },        { TIPTUP, PIPSY },  { DIDDY, KRUNCH, NONE, NONE },        { BUMPER, BANJO, NONE, NONE },       0x0006 }
};

// Under the unlikely chance you have T.T unlocked, but not Drumstick.
/*    Name         Up                 Down                  Left                                 Right                              Voice ID */
CharacterSelectData gCharacterSelectBytesTT[] = {
    /*Krunch*/ { { NONE, NONE },    { CONKER, NONE },     { NONE, NONE, NONE, NONE },          { DIDDY, BUMPER, BANJO, NONE },      0x0000 },
    /*Diddy*/  { { NONE, NONE },    { TIPTUP, TICTOC_8 }, { KRUNCH, NONE, NONE, NONE },        { BUMPER, BANJO, NONE, NONE },       0x0009 },
    /*Bumper*/ { { NONE, NONE },    { TICTOC_8, PIPSY },  { DIDDY, KRUNCH, NONE, NONE },       { BANJO, NONE, NONE, NONE },         0x0001 },
    /*Banjo*/  { { NONE, NONE },    { PIPSY, TIMBER },    { BUMPER, DIDDY, KRUNCH, NONE },     { NONE, NONE, NONE, NONE },          0x0005 },
    /*Conker*/ { { KRUNCH, NONE },  { NONE, NONE },       { NONE, NONE, NONE, NONE },          { TIPTUP, TICTOC_8, PIPSY, TIMBER }, 0x0003 },
    /*Tiptup*/ { { KRUNCH, DIDDY }, { NONE, NONE },       { CONKER, NONE, NONE, NONE },        { TICTOC_8, PIPSY, TIMBER, NONE },   0x0002 },
    /*Pipsy*/  { { BUMPER, BANJO }, { NONE, NONE },       { TICTOC_8, TIPTUP, CONKER, NONE },  { TIMBER, NONE, NONE, NONE },        0x0007 },
    /*Timber*/ { { BANJO, NONE },   { NONE, NONE },       { PIPSY, TICTOC_8, TIPTUP, CONKER }, { NONE, NONE, NONE, NONE },          0x0004 },
    /*T.T*/    { { DIDDY, BUMPER }, { NONE, NONE },       { TIPTUP, CONKER, NONE, NONE },      { PIPSY, TIMBER, NONE, NONE },       0x0008 }
};

// With everyone unlocked.
/*    Name            Up                   Down                Left                                 Right                              Voice ID */
CharacterSelectData gCharacterSelectBytesComplete[] = {
    /*Krunch*/    { { NONE, NONE },      { CONKER, NONE },   { NONE, NONE, NONE, NONE },           { DIDDY, DRUMSTICK, BUMPER, BANJO }, 0x0000 }, 
    /*Diddy*/     { { NONE, NONE },      { TIPTUP, NONE },   { KRUNCH, NONE, NONE, NONE },         { DRUMSTICK, BUMPER, BANJO, NONE },  0x0009 },
    /*Bumper*/    { { NONE, NONE },      { PIPSY, NONE },    { DRUMSTICK, DIDDY, KRUNCH, NONE },   { BANJO, NONE, NONE, NONE },         0x0001 },
    /*Banjo*/     { { NONE, NONE },      { TIMBER, NONE },   { BUMPER, DRUMSTICK, DIDDY, KRUNCH }, { NONE, NONE, NONE, NONE },          0x0005 },
    /*Conker*/    { { KRUNCH, NONE },    { NONE, NONE },     { NONE, NONE, NONE, NONE },           { TIPTUP, TICTOC_9, PIPSY, TIMBER }, 0x0003 },
    /*Tiptup*/    { { DIDDY, NONE },     { NONE, NONE },     { CONKER, NONE, NONE, NONE },         { TICTOC_9, PIPSY, TIMBER, NONE },   0x0002 },
    /*Pipsy*/     { { BUMPER, NONE },    { NONE, NONE },     { TICTOC_9, TIPTUP, CONKER, NONE },   { TIMBER, NONE, NONE, NONE },        0x0007 },
    /*Timber*/    { { BANJO, NONE },     { NONE, NONE },     { PIPSY, TICTOC_9, TIPTUP, CONKER },  { NONE, NONE, NONE, NONE },          0x0004 },
    /*Drumstick*/ { { NONE, NONE },      { TICTOC_9, NONE }, { DIDDY, KRUNCH, NONE, NONE },        { BUMPER, BANJO, NONE, NONE },       0x0006 },
    /*T.T*/       { { DRUMSTICK, NONE }, { TIPTUP, NONE },   { TIPTUP, CONKER, NONE, NONE },       { PIPSY, TIMBER, NONE, NONE },       0x0008 }
//!@bug T.T's down input selects Tiptup. It should be set to NONE.
};

s32 D_800DFFCC = 0; // Likely unused.
s32 D_800DFFD0 = 0;
s32 D_800DFFD4 = -1;

MenuElement gCautionMenuTextElements[14] = {
    { SCREEN_WIDTH_HALF + 1,  35, SCREEN_WIDTH_HALF + 1,  35, SCREEN_WIDTH_HALF + 1,  35,   0,   0,   0, 255, 128, ASSET_FONTS_BIGFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF,  32, SCREEN_WIDTH_HALF,  32, SCREEN_WIDTH_HALF,  32, 255, 255, 255,   0, 255, ASSET_FONTS_BIGFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF,  72, SCREEN_WIDTH_HALF,  68, SCREEN_WIDTH_HALF,  72, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF,  86, SCREEN_WIDTH_HALF,  82, SCREEN_WIDTH_HALF,  86, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF, 100, SCREEN_WIDTH_HALF,  96, SCREEN_WIDTH_HALF, 100, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF, 114, SCREEN_WIDTH_HALF, 110, SCREEN_WIDTH_HALF, 114, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF, 128, SCREEN_WIDTH_HALF, 124, SCREEN_WIDTH_HALF, 128, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF, 142, SCREEN_WIDTH_HALF, 138, SCREEN_WIDTH_HALF, 142, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF, 156, SCREEN_WIDTH_HALF, 152, SCREEN_WIDTH_HALF, 156, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF, 156, SCREEN_WIDTH_HALF, 166, SCREEN_WIDTH_HALF, 156, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF, 186, SCREEN_WIDTH_HALF, 180, SCREEN_WIDTH_HALF, 186, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF, 200, SCREEN_WIDTH_HALF, 194, SCREEN_WIDTH_HALF, 200, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF, 200, SCREEN_WIDTH_HALF, 208, SCREEN_WIDTH_HALF, 200, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,                   0,  0, 0, { NULL }, {{ 0, 0, 0, 0 }} },
};

MenuElement gGameSelectTextElemsNoAdv2[7] = {
    { SCREEN_WIDTH_HALF + 1,  35, SCREEN_WIDTH_HALF + 1,  35, SCREEN_WIDTH_HALF + 1,  35,   0,   0,   0, 255, 128, ASSET_FONTS_BIGFONT, 12, 0, { NULL },  {{ 0, 0, 0, 0 }} },
    { SCREEN_WIDTH_HALF,  32, SCREEN_WIDTH_HALF,  32, SCREEN_WIDTH_HALF,  32, 255, 255, 255,   0, 255, ASSET_FONTS_BIGFONT, 12, 0, { NULL },   {{ 0, 0, 0, 0 }} },
    { -96,  39, -96,  39, -96,  39, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT,  0, 7, { NULL }, {{ 192, 44, 4, 4 }} },
    { SCREEN_WIDTH_HALF, 104, SCREEN_WIDTH_HALF, 104, SCREEN_WIDTH_HALF, 104, 255, 255, 255,   0, 255, ASSET_FONTS_BIGFONT, 12, 0, { NULL },   {{ 0, 0, 0, 0 }} },
    { -96,  -9, -96,  -9, -96,  -9, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT,  0, 7, { NULL }, {{ 192, 44, 4, 4 }} },
    { SCREEN_WIDTH_HALF, 152, SCREEN_WIDTH_HALF, 152, SCREEN_WIDTH_HALF, 152, 255, 255, 255,   0, 255, ASSET_FONTS_BIGFONT, 12, 0, { NULL },   {{ 0, 0, 0, 0 }} },
    {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0,  0, 0, { NULL },   {{ 0, 0, 0, 0 }} },
};

MenuElement gGameSelectTextElemsWithAdv2[9] = {
    {  SCREEN_WIDTH_HALF + 1,  35,  SCREEN_WIDTH_HALF + 1,  35,  SCREEN_WIDTH_HALF + 1,  35,   0,   0,   0, 255, 128, ASSET_FONTS_BIGFONT, 12, 0, { NULL },  {{ 0, 0, 0, 0 }} },
    {  SCREEN_WIDTH_HALF,  32,  SCREEN_WIDTH_HALF,  32,  SCREEN_WIDTH_HALF,  32, 255, 255, 255,   0, 255, ASSET_FONTS_BIGFONT, 12, 0, { NULL },   {{ 0, 0, 0, 0 }} },
    { -112,  55, -112,  55, -112,  55, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT,  0, 7, { NULL }, {{ 224, 44, 4, 4 }} },
    {  SCREEN_WIDTH_HALF,  88,  SCREEN_WIDTH_HALF,  88,  SCREEN_WIDTH_HALF,  88, 255, 255, 255,   0, 255, ASSET_FONTS_BIGFONT, 12, 0, { NULL },   {{ 0, 0, 0, 0 }} },
    { -112,   7, -112,   7, -112,   7, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT,  0, 7, { NULL }, {{ 224, 44, 4, 4 }} },
    {  SCREEN_WIDTH_HALF, 136,  SCREEN_WIDTH_HALF, 136,  SCREEN_WIDTH_HALF, 136, 255, 255, 255,   0, 255, ASSET_FONTS_BIGFONT, 12, 0, { NULL },   {{ 0, 0, 0, 0 }} },
    { -112, -41, -112, -41, -112, -41, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT,  0, 7, { NULL }, {{ 224, 44, 4, 4 }} },
    {  SCREEN_WIDTH_HALF, 184,  SCREEN_WIDTH_HALF, 184,  SCREEN_WIDTH_HALF, 184, 255, 255, 255,   0, 255, ASSET_FONTS_BIGFONT, 12, 0, { NULL },   {{ 0, 0, 0, 0 }}},
    {    0,   0,    0,   0,    0,   0,   0,   0,   0,   0,   0, 0,  0, 0, { NULL },   {{ 0, 0, 0, 0 }} },
};

s16 D_800E0398[6] = {
    0x00, 0x43, 0x40, 0x41, 0x42, -1
};

s16 D_800E03A4[6] = {
    0x00, 0x0B, 0x0C, 0x0A, -1, 0
};

char *gFilenames[3] = {
    NULL, NULL, NULL
};

// Unused?
u16 D_800E03BC[8] = {
    0x004C,
    0x0070,
    0x00F4,
    0x0070,
    0x004C,
    0x00D0,
    0x00F4,
    0x00D0,
};

ButtonElement gFileSelectButtons[3] = {
    { 24, 81, 88, 64, 4, 4, GPACK_RGBA5551(64, 16, 0, 0), GPACK_RGBA5551(255, 255, 0, 0) }, // File A
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

s32 D_800E0414 = 0;
s32 D_800E0418 = 0;
DrawTexture gMenuSelectionArrowUp[2] = { { NULL, -12, -8 }, { NULL, 0, 0 }};
DrawTexture gMenuSelectionArrowLeft[2] = { { NULL, -8, -12 }, { NULL, 0, 0 }};
DrawTexture gMenuSelectionArrowDown[2] = { { NULL, -12, -8 }, { NULL, 0, 0 }};
DrawTexture gMenuSelectionArrowRight[2] = { { NULL, -8, -12 }, { NULL, 0, 0 }};

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
    gRaceSelectionCarTex, gRaceSelectionCarOptHighlight, gRaceSelectionCarOpt, gRaceSelectionHoverTex, gRaceSelectionHoverOptHighlight, gRaceSelectionHoverOpt, gRaceSelectionPlaneTex, gRaceSelectionPlaneOptHighlight, gRaceSelectionPlaneOpt

};

DrawTexture *D_800E0648[6] = {
    gRaceSelectionTTOff, gRaceSelectionTTOffOptHighlight, gRaceSelectionTTOffOpt, gRaceSelectionTTOn, gRaceSelectionTTOnOptHighlight, gRaceSelectionTTOnOpt
};

DrawTexture *D_800E0660[6] = {
    gRaceSelectionPlayer1Texture, gRaceSelectionPlayer2Texture, gRaceSelectionPlayer3Texture, gRaceSelectionPlayer4Texture, gRaceSelectionVehicleTitleTexture, gRaceSelectionTTTitleTexture
};

DrawTexture *gMenuSelectionArrows[4] = {
    gMenuSelectionArrowUp, gMenuSelectionArrowLeft, gMenuSelectionArrowDown, gMenuSelectionArrowRight
};

u16 D_800E0688[20] = {
    0x44, 0x72, 0x44, 0x72,
    0xCC, 0x72, 0x21, 0x72,
    0x88, 0x72, 0xEF, 0x72,
    0x21, 0x72, 0x66, 0x72,
    0xAA, 0x72, 0xEF, 0x72,
};

u16 D_800E06B0[10] = {
    0x68, 0x21, 0xFB, 0x27, 0x8E, 0xF5, 0x27, 0x6C, 0xB0, 0xF5
};

s16 D_800E06C4[8] = {
    0x0000, 0xFFC2, 0x0055, 0x0000,
    0x0000, 0x003E, 0xFFAB, 0x0000,
};

s16 D_800E06D4[8] = {
    0x0000, 0xFFB6, 0x0055, 0x0000,
    0x0000, 0x004A, 0xFFAB, 0x0000,
};

ButtonTextElement gTwoPlayerRacerCountMenu = {
    SCREEN_WIDTH_HALF - 80, 140, 160, 64, 4, 4, { 80, 20, 58, 40, 80, 40, 102, 40 }
};

ButtonElement D_800E0700 = {
    80, 152, 160, 40, 4, 4, 80, 14
};

// Often access like D_800E0710[i * 3 + 1]. Maybe it's s16[4][3]?
s16 D_800E0710[16] = {
    0x0E, 0x0F, 0x00, 0x10,
    0x11, 0x20, 0x12, 0x13,
    0x00, 0x14, 0x15, 0x20,
    0x16, 0x17, 0x20, 0x00
};

s16 D_800E0730[19] = {
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000
};

s16 D_800E0758[54] = {
    0xFFFF, 0xFFFF,
    0x0129, 0x011A, 0x0120, 0x0115,
    0x0126, 0x011D, 0x0130, 0x0121,
    0x0117, 0x0154, 0x0128, 0x0119,
    0x012C, 0x0123, 0xFFFF, 0x0122,
    0x011C, 0x0116, 0x0127, 0xFFFF,
    0xFFFF, 0xFFFF, 0x012D, 0x012E,
    0x0153, 0x012B, 0x011B, 0x011F,
    0x0124, 0x011E, 0x0118, 0x0125,
    0x012F, 0x012A, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0x0000
};

s16 D_800E07C4[14] = {
    0x05, 0x06, 0x07, 0x3D,
    0x3C, 0x3F, 0x3E, 0x08,
    0x09, 0x0A, 0x0B, 0x0C,
    0x0D, -1
};

s16 D_800E07E0[4] = {
    0x04, 0x05, 0x06, -1
};

s16 D_800E07E8[36] = {
    0x0004, 0x0000, 0x0001, 0x0002,
    0x0003, 0x0018, 0x0019, 0x001A,
    0x001B, 0x001C, 0x001D, 0x0024,
    0x0025, 0x0026, 0x0027, 0x0028,
    0x0029, 0x002A, 0x002B, 0x001E,
    0x001F, 0x0020, 0x0021, 0x0022,
    0x0023, 0x002C, 0x002D, 0x002E,
    0x002F, 0x0030, 0x0031, 0x0040,
    0x0041, 0x0043, 0x005E, 0xFFFF
};

s16 D_800E0830[8] = {
    0x07, 0x00, 0x01, 0x02,
    0x03, 0x0B, 0x0C, -1
};

s16 D_800E0840[148] = {
    0x0000, 0xFFFF, 0x0001, 0x01FF,
    0xFF00, 0x0200, 0xFFFF, 0x0003,
    0x01FF, 0xFF00, 0x0400, 0xFFFF,
    0x0005, 0x01FF, 0xFF00, 0x0600,
    0xFFFF, 0x0006, 0x0200, 0x4000,
    0x0701, 0xFFFF, 0x0007, 0x0340,
    0x8000, 0x0800, 0xFFFF, 0x0008,
    0x0280, 0xC020, 0x0901, 0xFFFF,
    0x0009, 0x03C0, 0xFF20, 0x0A02,
    0xFFFF, 0x000B, 0x03FF, 0xFF00,
    0x0C02, 0xFFFF, 0x200D, 0x03FF,
    0xFF20, 0x0E02, 0xFFFF, 0x000E,
    0x0400, 0x4000, 0x0F03, 0xFFFF,
    0x000F, 0x0540, 0x8000, 0x1002,
    0xFFFF, 0x2010, 0x0480, 0xC000,
    0x1103, 0xFFFF, 0x2011, 0x05C0,
    0xFF00, 0x1204, 0xFFFF, 0x0013,
    0x05FF, 0xFF00, 0x1404, 0xFFFF,
    0x0015, 0x05FF, 0xFF00, 0x1604,
    0xFFFF, 0x0016, 0x0600, 0x4000,
    0x1705, 0xFFFF, 0x0017, 0x0740,
    0x8000, 0x1804, 0xFFFF, 0x0018,
    0x0680, 0xC020, 0x1905, 0xFFFF,
    0x0019, 0x07C0, 0xFF20, 0x1A06,
    0xFFFF, 0x001B, 0x07FF, 0xFF00,
    0x1C06, 0xFFFF, 0x201D, 0x07FF,
    0xFF20, 0x1E06, 0xFFFF, 0x001E,
    0x0800, 0x4000, 0x1F07, 0xFFFF,
    0x001F, 0x0940, 0x8000, 0x2006,
    0xFFFF, 0x2020, 0x0880, 0xC020,
    0x2107, 0xFFFF, 0x2021, 0x09C0,
    0xFF20, 0x2208, 0xFFFF, 0x0023,
    0x09FF, 0xFF00, 0x2408, 0xFFFF,
    0x2025, 0x09FF, 0xFF20, 0x2608,
    0xFFFF, 0x0027, 0x09FF, 0xFF00,
    0x2808, 0xFFFF, 0x2029, 0x09FF,
    0xFF20, 0xFF00, 0x0000, 0x0000
};

Vertex *D_800E0968 = NULL;
s32 D_800E096C = 0;
unk800E0970 *D_800E0970 = NULL;
s32 D_800E0974 = 0;
char *gQMarkPtr = "?";
s32 D_800E097C = 0;
s32 gTrackNameVoiceDelay = 0;
s32 gMenuOptionCap = 0;
s32 gMenuSubOption = 0;
s32 D_800E098C = 0; //Player ID or controllerIndex maybe?

ColourRGBA D_800E0990[4] = {
    {{{  64,  64, 255, 160 }}},
    {{{ 255,  64,  64, 160 }}},
    {{{ 208, 192,  32, 176 }}},
    {{{  32, 192,  64, 176 }}},
};

ColourRGBA D_800E09A0[4] = {
    {{{   0, 255,   0, 128 }}},
    {{{   0, 255,   0,  96 }}},
    {{{   0,   0, 255,  96 }}},
    {{{   0,   0, 255, 128 }}},
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

s16 D_800E0A10[2] = {
    0x0000, 0x0000
};

//If you wish to use / the Rumble Pak / insert it now!
char *sInsertRumblePakMenuText[4] = { 0, 0, 0, 0 };

s16 D_800E0A24[14] = {
    0x0005, 0x003B, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0039, 0x0037, 0x0038, 0x003A, 0x0000, 0x0001, 0xFFFF
};

s16 D_800E0A40[8] = {
    0x0004, 0x0000, 0x0001, 0xFFFF, 0x0300, 0x0000, 0x0012, 0xFFFF
};

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

DrawTexture *gRacerPortraits[10] = {
    gMenuPortraitKrunch, gMenuPortraitDiddy, gMenuPortraitDrumstick, gMenuPortraitBumper,
    gMenuPortraitBanjo, gMenuPortraitConker, gMenuPortraitTiptup, gMenuPortraitTT,
    gMenuPortraitPipsy, gMenuPortraitTimber
};

s16 D_800E0B18[74] = {
    0x0140, 0x017C, 0x01B8, 0x01F4,
    0x0230, 0x026C, 0x02A8, 0x02E4,
    0x01E0, 0x0000, 0x0018, 0x0039,
    0x005A, 0x007B, 0x009C, 0x00BD,
    0x00DE, 0x00FF, 0x00A0, 0x0000,
    0x0140, 0x01B8, 0x0230, 0x02A8,
    0x01E0, 0x0000, 0x0018, 0x0065,
    0x00B3, 0x0100, 0x00A0, 0x0000,
    0x0140, 0x01F4, 0x02A8, 0x01E0,
    0x0028, 0x008C, 0x00F0, 0x00A0,
    0x01E0, 0x00C0, 0x00A0, 0x00C0,
    0xFF60, 0x00C0, 0xFF80, 0xFFEC,
    0xFFE4, 0xFFE6, 0x0050, 0xFFF8,
    0xFFE4, 0xFFF4, 0xFFE4, 0x0006,
    0xFFE4, 0x0018, 0x0050, 0x0008,
    0x0000, 0x0078, 0x0000, 0x003C,
    0x0000, 0x001E, 0x0000, 0x0384,
    0x0000, 0x001E, 0x0000, 0x001E,
    0x0000, 0x0384
};

char gFirstPlace[4]   = "1ST";
char gSecondPlace[4]  = "2ND";
char gThirdPlace[4]   = "3RD";
char gFourthPlace[4]  = "4TH";
char gFifthPlace[4]   = "5TH";
char gSixthPlace[4]   = "6TH";
char gSeventhPlace[4] = "7TH";
char gEighthPlace[4]  = "8TH";

char *gRacePlacementsArray[8] = {
    gFirstPlace, gSecondPlace, gThirdPlace, gFourthPlace,
    gFifthPlace, gSixthPlace, gSeventhPlace, gEighthPlace
};

MenuElement D_800E0BEC[8] = {
    { 352, 172,  32, 172, -288, 172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT,  0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
    { 452, 166, 132, 166, -188, 166, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, {      NULL   }, {{ 0, 0, 0, 0 }} },
    { 560, 184, 240, 184,  -80, 184, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, {      NULL   }, {{ 0, 0, 0, 0 }} },
    { 452, 180, 132, 180, -188, 180, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT,  0, 1, {      NULL   }, {{ 0, 0, 0, 0 }} },
    { 452, 198, 132, 198, -188, 198, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT,  0, 1, {      NULL   }, {{ 0, 0, 0, 0 }} },
    { 452, 216, 132, 216, -188, 216, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT,  0, 1, {      NULL   }, {{ 0, 0, 0, 0 }} },
    { 560, 200, 240, 200,  -80, 200, 128, 255, 255, 0, 255, ASSET_FONTS_FUNFONT,  0, 1, {      NULL   }, {{ 0, 0, 0, 0 }} },
    {   0,   0,   0,   0,    0,   0,   0,   0,   0, 0,   0, 0,  0, 0, {      NULL   }, {{ 0, 0, 0, 0 }} },
};

MenuElement D_800E0CEC[11] = {
    { 575, 172, 255, 172,  -65, 172, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT,  0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
    { 542, 172, 222, 172,  -98, 172, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT,  0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
    { 509, 172, 189, 172, -131, 172, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT,  0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
    { 476, 172, 156, 172, -164, 172, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT,  0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
    { 443, 172, 123, 172, -197, 172, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT,  0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
    { 410, 172,  90, 172, -230, 172, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT,  0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
    { 377, 172,  57, 172, -263, 172, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT,  0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
    { 344, 172,  24, 172, -296, 166, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT,  0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
    { 481, 166, 161, 166, -159, 166,   0,   0,   0, 255, 128, ASSET_FONTS_FUNFONT, 12, 0, {      NULL   }, {{ 0, 0, 0, 0 }} },
    { 479, 164, 159, 164, -161, 164, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, {      NULL   }, {{ 0, 0, 0, 0 }} },
    {   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0, 0,  0, 0, {      NULL   }, {{ 0, 0, 0, 0 }} },

};

MenuElement D_800E0E4C[9] = {
    { 481, 174, 161, 174, -159, 174,   0,   0,   0, 255, 128, ASSET_FONTS_FUNFONT, 12, 0, {       NULL  }, {{ 0, 0, 0, 0 }} },
    { 479, 172, 159, 172, -161, 172, 255, 255, 255,   0, 255, ASSET_FONTS_FUNFONT, 12, 0, {       NULL  }, {{ 0, 0, 0, 0 }} },
    { 368, 192,  48, 192, -272, 192, 255,  64,  64,  96, 255, ASSET_FONTS_FUNFONT,  8, 0, {       NULL  }, {{ 0, 0, 0, 0 }} },
    { 506, 187, 186, 187, -134, 187, 255, 192, 255,   0, 255, ASSET_FONTS_FUNFONT,  0, 1, {       NULL  }, {{ 0, 0, 0, 0 }} },
    { 578, 192, 258, 192,  -62, 192, 255, 128, 255,  96, 255, ASSET_FONTS_FUNFONT, 12, 0, { &D_80126390 }, {{ 0, 0, 0, 0 }} },
    { 368, 212,  48, 212, -272, 212, 255,  64,  64,  96, 255, ASSET_FONTS_FUNFONT,  8, 0, {       NULL  }, {{ 0, 0, 0, 0 }} },
    { 506, 207, 186, 207, -134, 207, 128, 255, 255,   0, 255, ASSET_FONTS_FUNFONT,  0, 1, {       NULL  }, {{ 0, 0, 0, 0 }} },
    { 578, 212, 258, 212,  -62, 212, 255, 128, 255,  96, 255, ASSET_FONTS_FUNFONT, 12, 0, { &D_80126394 }, {{ 0, 0, 0, 0 }} },
    {   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0, 0,  0, 0, {       NULL  }, {{ 0, 0, 0, 0 }} },
};

// Valid characters for name input. Must be u8, not char.
// The length of the array must be a power of two.
u8 gFileNameValidChars[32] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.?    ";

char D_800E0F8C = '\0';
s32 D_800E0F90 = 192;
s32 D_800E0F94 = 160;
s32 D_800E0F98 = 120;
s32 D_800E0F9C = ASSET_FONTS_BIGFONT;
s32 D_800E0FA0 = 0;
s32 D_800E0FA4 = 0;
char D_800E0FA8[4] = "DKR"; // Default file name?
s32 D_800E0FAC = 0;
s32 D_800E0FB0 = 0;

s16 D_800E0FB4[18] = {
    0x0004, 0x0000, 0x0001, 0x0018,
    0x0019, 0x001A, 0x001B, 0x001C,
    0x001D, 0x001E, 0x001F, 0x0020,
    0x0021, 0x0022, 0x0023, 0x0030,
    0x005E, -1
};

s16 D_800E0FD8[6] = {
    7, 0, 1, 2, 3, -1
};

s32 gRankingPlayerCount = 8; // Number of racers in trophy race? (1 to 8)
s32 gTrophyRaceWorldId = 0;
s32 gTrophyRaceRound = 0; // Rounds 1 - 4 (as 0 - 3)
s32 gPrevTrophyRaceRound = 0;

// Unused? Not sure what this is.
u32 D_800E0FF4[4] = {
    0x01FFFFFF, 0x0012FFFF, 0x81FFFFFF, 0x00120000
};

// Number of points to award in trophy race for each place.
s32 gTrophyRacePointsArray[8] = {
    9, 7, 5, 3, 1, 0, 0, 0
};

s16 D_800E1024[14] = {
    0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x00, 0x01, -1, 0x00
};

s16 D_800E1040[3] = {
    0, 1, -1
};

MenuElement D_800E1048[1][2] = { 
    {
        { SCREEN_WIDTH + 160 + 1, 35, SCREEN_WIDTH_HALF + 1, 35, -159, 35, 0, 0, 0, 255, 128, ASSET_FONTS_BIGFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} },
        { SCREEN_WIDTH + 160, 32, SCREEN_WIDTH_HALF, 32, -160, 32, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { NULL }, {{ 0, 0, 0, 0 }} }
    }
};

MenuElement D_800E1088[8][3] = {
    {
        { 64, -192, 64, 48, 64, 288, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
        { 32, -192, 32, 48, 32, 288, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gFirstPlace }, {{ 0, 0, 0, 0 }} },
        { 130, -172, 130, 68, 130, 308, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[0] }, {{ 0, 0, 0, 0 }} }
    },
    {
        { 64, -150, 64, 90, 64, 330, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
        { 32, -150, 32, 90, 32, 330, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gSecondPlace }, {{ 0, 0, 0, 0 }} },
        { 130, -130, 130, 110, 130, 350, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[1] }, {{ 0, 0, 0, 0 }} }
    },
    {
        { 64, -108, 64, 132, 64, 372, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
        { 32, -108, 32, 132, 32, 372, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gThirdPlace }, {{ 0, 0, 0, 0 }} },
        { 130, -88, 130, 152, 130, 392, 255, 128, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[2] }, {{ 0, 0, 0, 0 }} }
    },
    {
        { 64, -66, 64, 174, 64, 414, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
        { 32, -66, 32, 174, 32, 414, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gFourthPlace }, {{ 0, 0, 0, 0 }} },
        { 130, -46, 130, 194, 130, 434, 255, 64, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[3] }, {{ 0, 0, 0, 0 }} }
    },
    {
        { 220, 288, 220, 48, 220, -192, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
        { 188, 288, 188, 48, 188, -192, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gFifthPlace }, {{ 0, 0, 0, 0 }} },
        { 286, 308, 286, 68, 286, -172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[4] }, {{ 0, 0, 0, 0 }} }
    },
    {
        { 220, 330, 220, 90, 220, -160, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
        { 188, 330, 188, 90, 188, -150, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gSixthPlace }, {{ 0, 0, 0, 0 }} },
        { 286, 350, 286, 110, 286, -130, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[5] }, {{ 0, 0, 0, 0 }} }
    },
    {
        { 220, 372, 220, 132, 220, -108, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
        { 188, 372, 188, 132, 188, -108, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gSeventhPlace }, {{ 0, 0, 0, 0 }} },
        { 286, 392, 286, 152, 286, -88, 255, 128, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[6] }, {{ 0, 0, 0, 0 }} }
    },
    {
        { 220, 414, 220, 174, 220, -66, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, {{ 0, 0, 0, 0 }} },
        { 188, 414, 188, 174, 188, -66, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gEighthPlace }, {{ 0, 0, 0, 0 }} },
        { 286, 434, 286, 194, 286, -46, 255, 64, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[7] }, {{ 0, 0, 0, 0 }} }
    }
};
MenuElement D_800E1088_END = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ASSET_FONTS_FUNFONT, 0, 0, { NULL }, {{ 0, 0, 0, 0 }} };

s16 D_800E13A8[138] = {
    0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x0040, 0x0020,
    0x0082, 0x0040, 0x0020, 0x0082, 0x00DC, 0x00BC, 0x011E, 0x00DC,
    0x00BC, 0x011E, 0x00DC, 0x00BC, 0x011E, 0x00DC, 0x00BC, 0x011E,
    0x0030, 0x0030, 0x0044, 0x005A, 0x005A, 0x006E, 0x0084, 0x0084,
    0x0098, 0x00AE, 0x00AE, 0x00C2, 0x0030, 0x0030, 0x0044, 0x005A,
    0x005A, 0x006E, 0x0084, 0x0084, 0x0098, 0x00AE, 0x00AE, 0x00C2,
    0x0038, 0x0038, 0x0040, 0x006A, 0x006A, 0x0072, 0x009C, 0x009C,
    0x00A4, 0x00CE, 0x00CE, 0x00D6, 0x0038, 0x0038, 0x0040, 0x006A,
    0x006A, 0x0072, 0x009C, 0x009C, 0x00A4, 0x00CE, 0x00CE, 0x00D6,
    0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x0040, 0x0020,
    0x0082, 0x00DC, 0x00BC, 0x011E, 0x00DC, 0x00BC, 0x011E, 0x00DC,
    0x00BC, 0x011E, 0x0034, 0x0034, 0x0048, 0x006F, 0x006F, 0x0083,
    0x00AA, 0x00AA, 0x00BE, 0x0034, 0x0034, 0x0048, 0x006F, 0x006F,
    0x0083, 0x00AA, 0x00AA, 0x00BE, 0x004C, 0x004C, 0x0054, 0x007E,
    0x007E, 0x0086, 0x00B0, 0x00B0, 0x00B8, 0x004C, 0x004C, 0x0054,
    0x007E, 0x007E, 0x0086, 0x00B0, 0x00B0, 0x00B8, 0x008C, 0x006C,
    0x00CE, 0x008C, 0x006C, 0x00CE, 0x008C, 0x006C, 0x00CE, 0x008C,
    0x006C, 0x00CE
};

s16 *D_800E14BC[32] = {
    NULL, NULL, NULL, NULL,
    &D_800E13A8[126], &D_800E13A8[90], &D_800E13A8[126], &D_800E13A8[24],
    NULL, NULL , &D_800E13A8[72], &D_800E13A8[90],
    NULL, NULL, &D_800E13A8[0], &D_800E13A8[24],
    NULL, NULL, NULL, NULL,
    &D_800E13A8[126], &D_800E13A8[108], &D_800E13A8[126], &D_800E13A8[48],
    NULL, NULL, &D_800E13A8[72], &D_800E13A8[108],
    NULL, NULL, &D_800E13A8[0], &D_800E13A8[48]
};

unk800E153C D_800E153C[] = {
    { NULL, 0x00000000 },
    { NULL, 0x00400000 },
    { NULL, 0x00800000 },
    { NULL, 0x00C00000 },
    { NULL, 0x01000000 },
    { NULL, 0x00000020 },
    { NULL, 0x00400020 },
    { NULL, 0x00800020 },
    { NULL, 0x00C00020 },
    { NULL, 0x01000020 },
    { NULL, 0x00000000 },
};
unk800E153C D_800E1594[] = {
    { NULL, 0x00000000 },
    { NULL, 0x00400000 },
    { NULL, 0x00800000 },
    { NULL, 0x00C00000 },
    { NULL, 0x01000000 },
    { NULL, 0x00000020 },
    { NULL, 0x00400020 },
    { NULL, 0x00800020 },
    { NULL, 0x00C00020 },
    { NULL, 0x01000020 },
    { NULL, 0x00000000 },
};
unk800E153C D_800E15EC[] = {
    { NULL, 0x00000000 },
    { NULL, 0x00400000 },
    { NULL, 0x00800000 },
    { NULL, 0x00C00000 },
    { NULL, 0x01000000 },
    { NULL, 0x00000020 },
    { NULL, 0x00400020 },
    { NULL, 0x00800020 },
    { NULL, 0x00C00020 },
    { NULL, 0x01000020 },
    { NULL, 0x00000000 },
};
unk800E153C D_800E1644[] = {
    { NULL, 0x00000000 },
    { NULL, 0x00400000 },
    { NULL, 0x00800000 },
    { NULL, 0x00C00000 },
    { NULL, 0x01000000 },
    { NULL, 0x00000020 },
    { NULL, 0x00400020 },
    { NULL, 0x00800020 },
    { NULL, 0x00C00020 },
    { NULL, 0x01000020 },
    { NULL, 0x00000000 },
};
unk800E153C D_800E169C[] = {
    { NULL, 0x00000000 },
    { NULL, 0x00400000 },
    { NULL, 0x00800000 },
    { NULL, 0x00C00000 },
    { NULL, 0x01000000 },
    { NULL, 0x00000020 },
    { NULL, 0x00400020 },
    { NULL, 0x00800020 },
    { NULL, 0x00C00020 },
    { NULL, 0x01000020 },
    { NULL, 0x00000000 },
};

unk800E153C *D_800E16F4[5] = {
    D_800E153C, D_800E1594, D_800E15EC, D_800E1644, D_800E169C
};

s16 D_800E1708[34] = {
    0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
    0x32, 0x33, 0x34, 0x36, 0x35, 0x37, 0x38, 0x39,
    0x3A, 0x3B, 0x00, 0x01, 0x04, 0x3D, 0x3C, 0x3F,
    0x3E, -1
};

s16 D_800E174C[4] = {
    0, 1, 7, -1
};

s16 D_800E1754[10] = {
    0x78, 0x12, 0x08, 0x06, 0xC0, 0x06, 0xD4, 0x1A, 0x78, 0x22
};

s16 D_800E1768[12] = {
    0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, -1, 0
};

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

s16 D_800E17D8[12] = {
    0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, -1, 0
};

s16 D_800E17F0[2] = {
    -1, 0
};

s16 D_800E17F4[130] = {
    0x20A5, 0x0000, 0x20A5, 0x0001, 0x0002, 0x20A5, 0x0003, 0x0004,
    0x0005, 0x0006, 0x4000, 0x20A5, 0x0007, 0x0008, 0x20A5, 0x0009,
    0x000A, 0x000B, 0x000C, 0x30A5, 0x000D, 0x000E, 0x000F, 0x4000,
    0x20A5, 0x0010, 0x0011, 0x20A5, 0x0012, 0x0013, 0x20A5, 0x0014,
    0x4000, 0x20A5, 0x0015, 0x0016, 0x20A5, 0x0017, 0x0018, 0x20A5,
    0x0019, 0x001A, 0x4000, 0x20A5, 0x001B, 0x001C, 0x001D, 0x001E,
    0x001F, 0x30A5, 0x0020, 0x0021, 0x0022, 0x0023, 0x30A5, 0x0024,
    0x0025, 0x0026, 0x4000, 0x20A5, 0x0027, 0x0028, 0x0029, 0x002A,
    0x002B, 0x30A5, 0x002C, 0x002D, 0x002E, 0x30A5, 0x002F, 0x0030,
    0x0031, 0x4000, 0x20A5, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036,
    0x30A5, 0x0037, 0x0038, 0x0039, 0x003A, 0x30A5, 0x003B, 0x003C,
    0x003D, 0x003E, 0x4000, 0x20A5, 0x003F, 0x0040, 0x0041, 0x20A5,
    0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x20A5, 0x0047, 0x0048,
    0x0049, 0x4000, 0x20A5, 0x004A, 0x004B, 0x30A5, 0x004C, 0x30A5,
    0x004D, 0x4000, 0x20A5, 0x004E, 0x004F, 0x20A5, 0x0050, 0x0051,
    0x20A5, 0x0052, 0x0053, 0x4000, 0x20A5, 0x0054, 0x210E, 0x0055,
    0x0056, 0x4000
};

u16 D_800E18F8 = 0x1000;

// Unused?
u16 D_800E18FC[30] = {
    0x0001, 0x0002, 0x0003, 0x4000,
    0x61F4, 0x0004, 0x0005, 0x0006,
    0x0007, 0x4000, 0x61F4, 0x0008,
    0x0009, 0x000A, 0x000B, 0x4000,
    0x61F4, 0x000C, 0x000D, 0x000E,
    0x000F, 0x4000, 0x61F4, 0x0010,
    0x0011, 0x0012, 0x0013, 0x4000,
    0x1000, 0x0000
};

// List of amazing people.
char *gCreditsArray[87] = {
    "CREDITS",
    "Software Director", "R.Harrison",
    "Software Engineers", "P.Mountain", "J.Pegg", "R.Gale",
    "Art Director", "K.Bayliss",
    "3D Artists", "L.Musgrave", "K.Rabbette", "D.Smith", "J.Christensen", "B.Smyth", "P.Cunningham",
    "Music", "D.Wise",
    "Sound Effects", "G.Norgate",
    "ALSO",
    "Additional Design", "M.Wakeley",
    "Documentation", "L.Loveday", "Liason", "E.Hochberg",
    "Character Voices", "K.Bayliss", "J.Christensen", "E.Fischer", "K.Rabbette", "L.Ray",
        "L.Schuneman", "C.Seavor", "D.Smith", "J.Stamper", "K.Stamper", "C.Sutherland",
    "Rare Quality Assurance", "H.Ward", "G.Richards", "S.Farmer", "J.Williams", "D.Wong",
        "G.Jones", "M.Penny", "S.Brand", "S.Malpass", "A.Wilson",
    "NOA Thanks To", "M.Fukuda", "K.Lobb", "M.Kelbaugh", "A.Williams", "R.Johnson", "M.Forrest",
        "P.Sandhop", "H.Sterchi", "T.Hertzog", "D.Bridgham", "G.Richardson", "B.Smith",
    "NOA Thanks To", "NOA Tree House", "NOA Tree Branch",
    "NCL Thank You's", "K.Terasaki", "M.Goto", "H.Yamada", "Mario Club",
    "NOE Thank You's", "J.Kraft", "J.Bardakoff",
    "Special Thanks To", "J.Hochberg", "H.Lincoln", "M.Arakawa",
    "Game Director", "L.Schuneman",
    "Producer", "C.Stamper",
    "Executive Producer", "T.Stamper",
    NULL, NULL, NULL
};

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
s32 gCheatsInCreditsArray[21] = {
    CHEAT_BIG_CHARACTERS,
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
    CHEAT_ULTIMATE_AI
};
#define NUMBER_CHEATS_IN_CREDITS sizeof(gCheatsInCreditsArray) / sizeof(s32)

s32 gViewingCreditsFromCheat = FALSE; // Set to 1 if viewing credits from "WHODIDTHIS" cheat

MenuElement D_800E1B50[9] = {
    { 480, 104, 160, 104, -160, 104, 255,   0, 255, 48, 255, ASSET_FONTS_FUNFONT, 4, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255,  0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255,  0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255,  0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, ASSET_FONTS_BIGFONT, 4, 0, { NULL }, {{ 0, 0, 0, 0 }} },
    {   0,   0,   0,   0,    0,   0,   0,   0,   0,  0,   0, 0, 0, 0, { NULL }, {{ 0, 0, 0, 0 }} },
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

s8 D_800E1CD0[32] = {
    0, 1, 2, 0, 2, 3, 4, 5,
    6, 4, 6, 7, 8, 9, 10, 8,
    10, 11, 12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19, 0, 0
};

// UV coordinate indices
u8 D_800E1CF0[5][12] = {
    { 0, 0, 3, 0, 2, 1, 0, 0, 2, 1, 1, 1 }, 
    { 2, 1, 3, 0, 3, 3, 2, 1, 3, 3, 2, 2 }, 
    { 1, 2, 2, 2, 3, 3, 1, 2, 3, 3, 0, 3 }, 
    { 0, 0, 1, 1, 1, 2, 0, 0, 1, 2, 0, 3 }, 
    { 1, 1, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2 }
};

// Position offsets, why are there 10?
u16 D_800E1D2C[10][4] = {
    {   0,    0, 256,    0 },
    { 511,  255,   1,  255 },
    { 511,  255, 256,    0 },
    { 256, -256, 511, -255 },
    {   1, -255, 511, -255 },
    { 256, -256,   0, -256 },
    {   0,    0,   1,  255 },
    {   1, -255,   0, -256 },
    {   1,  255, 511,  255 },
    { 511, -255,   1, -255 }
};

// Colours
s16 D_800E1D7C[5][4] = {
    { 216, 216, 216, 256 },
    { 176, 176, 176, 256 },
    {  96,  96,  96, 256 },
    { 136, 136, 136, 256 },
    { 256, 256, 256, 256 }
};

s32 *D_800E1DA4[2] = {
    NULL, NULL
};

s32 *D_800E1DAC[2] = {
    NULL, NULL
};

s32 D_800E1DB4 = 0;
s32 D_800E1DB8 = 0;
s32 D_800E1DBC = 0;

s32 D_800E1DC0 = 32;
s32 D_800E1DC4 = 32;

s16 D_800E1DC8[16] = {
    1, 1, -1, 1, -1, 1, -1, -1, 1, -1, -1, -1, 1, 1, 1, -1
};

FadeTransition D_800E1DE8 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 120, -1);

char gRareCopyrightString[24] = "(C) COPYRIGHT RARE 1997";

FadeTransition D_800E1E08 = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 52, -1);

char *D_800E1E10 = " (ADV.";


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
            if ((s32)gMenuText[i] == -1) {
                gMenuText[i] = NULL;
            } else {
                gMenuText[i] = &((u8 *)gMenuText)[(s32)gMenuText[i]];
            }
        }
        gAudioOutputStrings[0] = gMenuText[ASSET_MENU_TEXT_STEREO];                                  // "STEREO"
        gAudioOutputStrings[1] = gMenuText[ASSET_MENU_TEXT_MONO];                                    // "MONO"
        gAudioOutputStrings[2] = gMenuText[ASSET_MENU_TEXT_HEADPHONES];                              // "HEADPHONES"
        gAudioMenuStrings[1].unkC = gMenuText[ASSET_MENU_TEXT_SFXVOLUME];                            // "SFX VOLUME"
        gAudioMenuStrings[2].unkC = gMenuText[ASSET_MENU_TEXT_MUSICVOLUME];                          // "MUSIC VOLUME"
        gAudioMenuStrings[3].unkC = gMenuText[ASSET_MENU_TEXT_RETURN];                               // "RETURN"
        gAudioMenuStrings[4].unkC = gMenuText[ASSET_MENU_TEXT_AUDIOOPTIONS];                         // "AUDIO OPTIONS"
        gAudioMenuStrings[5].unkC = gMenuText[ASSET_MENU_TEXT_AUDIOOPTIONS];                         // "AUDIO OPTIONS"
        gMusicTestString = gMenuText[ASSET_MENU_TEXT_MUSICTEST];                                     // "MUSIC TEST 00"
        gMagicCodeMenuStrings[0] = gMenuText[ASSET_MENU_TEXT_ENTERCODE];                             // "ENTER CODE"
        gMagicCodeMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_CLEARALLCODES];                         // "CLEAR ALL CODES"
        gMagicCodeMenuStrings[2] = gMenuText[ASSET_MENU_TEXT_CODELIST];                              // "CODE LIST"
        gMagicCodeMenuStrings[3] = gMenuText[ASSET_MENU_TEXT_RETURN];                                // "RETURN"
        D_800E0BEC[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_LAPTIMES];                       // "LAP TIMES"
        D_800E0BEC[2].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_OVERALLTIME];                    // "OVERALL TIME"
        D_800E0CEC[8].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_RACEORDER];                      // "RACE ORDER"
        D_800E0CEC[9].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_RACEORDER];                      // "RACE ORDER"
        D_800E0E4C[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_RECORDTIMES];                    // "RECORD TIMES"
        D_800E0E4C[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_RECORDTIMES];                    // "RECORD TIMES"
        D_800E0E4C[2].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_BESTTIME];                       // "BEST TIME"
        D_800E0E4C[5].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_BESTLAP];                        // "BEST LAP"
        gOptionMenuStrings[0] = gMenuText[ASSET_MENU_TEXT_LANGUAGE];                                 // "ENGLISH"
        if (sEepromSettings & 0x2000000) {
            gOptionMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_SUBTITLESON];                          // "SUBTITLES ON"
        } else {
            gOptionMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_SUBTITLESOFF];                         // "SUBTITLES OFF"
        }
        gOptionMenuStrings[2] = gMenuText[ASSET_MENU_TEXT_AUDIOOPTIONS];                             // "AUDIO OPTIONS"
        gOptionMenuStrings[3] = gMenuText[ASSET_MENU_TEXT_SAVEOPTIONS];                              // "SAVE OPTIONS"
        gOptionMenuStrings[4] = gMenuText[ASSET_MENU_TEXT_MAGICCODES];                               // "MAGIC CODES"
        gOptionMenuStrings[5] = gMenuText[ASSET_MENU_TEXT_RETURN];                                   // "RETURN"
        gFilenames[0] = gMenuText[ASSET_MENU_TEXT_GAMEA];                                            // "GAME A"
        gFilenames[1] = gMenuText[ASSET_MENU_TEXT_GAMEB];                                            // "GAME B"
        gFilenames[2] = gMenuText[ASSET_MENU_TEXT_GAMEC];                                            // "GAME C"
        D_800DFAE4[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];                                         // "CONTROLLER PAK ~"
        D_800DFAE4[1] = gMenuText[ASSET_MENU_TEXT_CONTPAKNOTPRESENT];                                // "IS NOT PRESENT."
        D_800DFAE4[3] = gMenuText[ASSET_MENU_TEXT_CANCEL];                                           // "CANCEL"
        D_800DFAFC[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];                                         // "CONTROLLER PAK ~"
        D_800DFAFC[1] = gMenuText[ASSET_MENU_TEXT_CONTPAKHASCORRUPTDATA_0];                          // "CONTAINS CORRUPT DATA."
        D_800DFAFC[3] = gMenuText[ASSET_MENU_TEXT_CONTPAKHASCORRUPTDATA_1];                          // "ATTEMPT TO REPAIR"
        D_800DFAFC[4] = gMenuText[ASSET_MENU_TEXT_CANCEL];                                           // "CANCEL"
        D_800DFB14[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];                                         // "CONTROLLER PAK ~"
        D_800DFB14[1] = gMenuText[ASSET_MENU_TEXT_CONTPAKISDAMAGED_0];                               // "IRREPARABLY DAMAGED."
        D_800DFB14[3] = gMenuText[ASSET_MENU_TEXT_CONTPAKISDAMAGED_1];                               // "REFORMAT PAK"
        D_800DFB14[4] = gMenuText[ASSET_MENU_TEXT_CANCEL];                                           // "CANCEL"
        D_800DFB2C[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];                                         // "CONTROLLER PAK ~"
        D_800DFB2C[1] = gMenuText[ASSET_MENU_TEXT_CONTPAKISFULL];                                    // "FULL."
        D_800DFB2C[3] = gMenuText[ASSET_MENU_TEXT_CONTINUE];                                         // "CONTINUE"
        D_800DFB40[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];                                         // "CONTROLLER PAK ~"
        D_800DFB40[1] = gMenuText[ASSET_MENU_TEXT_CONTPAKDIFFERENT_0];                               // "DIFFERENT CONTROLLER"
        D_800DFB40[2] = gMenuText[ASSET_MENU_TEXT_CONTPAKDIFFERENT_1];                               // "PAK IS INSERTED."
        D_800DFB40[4] = gMenuText[ASSET_MENU_TEXT_CANCEL];                                           // "CANCEL"
        D_800DFB5C[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];                                         // "CONTROLLER PAK ~"
        D_800DFB5C[1] = gMenuText[ASSET_MENU_TEXT_CANNOTSTOREANYMOREGHOSTS_0];                       // "CANNOT STORE ANY"
        D_800DFB5C[2] = gMenuText[ASSET_MENU_TEXT_CANNOTSTOREANYMOREGHOSTS_1];                       // "MORE GHOSTS."
        D_800DFB5C[4] = gMenuText[ASSET_MENU_TEXT_CONTINUE];                                         // "CONTINUE"
        D_800DFB74[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKX];                                         // "CONTROLLER PAK ~"
        D_800DFB74[1] = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_0];                                    // "CORRUPT DATA."
        D_800DFB74[3] = gMenuText[ASSET_MENU_TEXT_TRYAGAIN];                                         // "TRY AGAIN"
        D_800DFB74[4] = gMenuText[ASSET_MENU_TEXT_CANCEL];                                           // "CANCEL"
        D_800DFB8C[0] = gMenuText[ASSET_MENU_TEXT_RUMBLEPAKDETECTED_0];                              // "Rumble Pak Detected"
        D_800DFB8C[1] = gMenuText[ASSET_MENU_TEXT_RUMBLEPAKDETECTED_1];                              // "Insert any Controller Paks"
        D_800DFB8C[2] = gMenuText[ASSET_MENU_TEXT_RUMBLEPAKDETECTED_2];                              // "you wish to use now!"
        D_800DFB8C[4] = gMenuText[ASSET_MENU_TEXT_CONTINUE];                                         // "CONTINUE"
        D_800DFBA4[0] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_0];                                   // "If you wish to use any"
        D_800DFBA4[1] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_1];                                   // "Rumble Paks then please"
        D_800DFBA4[2] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_2];                                   // "insert them now."
        D_800DFBA4[4] = gMenuText[ASSET_MENU_TEXT_CONTINUE];                                         // "CONTINUE"
        D_800DFBBC[0] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_0];                                // "SORRY, BUT YOU"
        D_800DFBBC[1] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_1];                                // "CAN'T LOAD GAMES"
        D_800DFBBC[2] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_2];                                // "FOR THE SECOND"
        D_800DFBBC[3] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_3];                                // "ADVENTURE UNTIL"
        D_800DFBBC[4] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_4];                                // "YOU HAVE COMPLETED"
        D_800DFBBC[5] = gMenuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_5];                                // "THE FIRST."
        D_800DFBBC[7] = gMenuText[ASSET_MENU_TEXT_CONTINUE];                                         // "CONTINUE"
        gTitleMenuStrings[0] = gMenuText[ASSET_MENU_TEXT_START];                                     // "START"
        gTitleMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_OPTIONS];                                   // "OPTIONS"
        gGameSelectTextElemsNoAdv2[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_GAMESELECT];     // "GAME SELECT"
        gGameSelectTextElemsNoAdv2[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_GAMESELECT];     // "GAME SELECT"
        gGameSelectTextElemsNoAdv2[3].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_ADVENTURE];      // "ADVENTURE"
        gGameSelectTextElemsNoAdv2[5].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_TRACKS];         // "TRACKS"
        gGameSelectTextElemsWithAdv2[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_GAMESELECT];   // "GAME SELECT"
        gGameSelectTextElemsWithAdv2[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_GAMESELECT];   // "GAME SELECT"
        gGameSelectTextElemsWithAdv2[3].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_ADVENTURE];    // "ADVENTURE"
        gGameSelectTextElemsWithAdv2[5].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_ADVENTURETWO]; // "ADVENTURE TWO"
        gGameSelectTextElemsWithAdv2[7].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_TRACKS];       // "TRACKS"
        sBadControllerPakMenuText[0] = gMenuText[ASSET_MENU_TEXT_BADCONTPAK];                        // "BAD CONTROLLER PAK"
        sControllerPakFullMenuText[0] = gMenuText[ASSET_MENU_TEXT_CONTPAKFULL];                      // "CONTROLLER PAK FULL"
        sNoControllerPakMenuText[0] = gMenuText[ASSET_MENU_TEXT_NOCONTPAK];                          // 'NO CONTROLLER PAK"
        sCorruptDataMenuText[4] = NULL;
        sCorruptDataMenuText[5] = NULL;
        sCorruptDataMenuText[0] = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_0];                          // "CORRUPT DATA."
        //Three messages
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
        sCorruptDataMenuText[j] = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_1];                          // "TRY AGAIN!"
        sInsertControllerPakMenuText[0] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_3];                 // "If you wish to use"
        sInsertControllerPakMenuText[1] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_4];                 // "the Controller Pak"
        sInsertControllerPakMenuText[2] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_6];                 // "insert it now!"
        sInsertRumblePakMenuText[0] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_3];                     // "If you wish to use"
        sInsertRumblePakMenuText[1] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_5];                     // "the Rumble Pak"
        sInsertRumblePakMenuText[2] = gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_6];                     // "insert it now!"
        gCautionMenuTextElements[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION];          // "CAUTION"
        gCautionMenuTextElements[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION];          // "CAUTION"
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
    if (D_800E1DAC[0] != NULL) {
        free_from_memory_pool(D_800E1DAC[0]);
        D_800E1DAC[0] = NULL;
    }
    D_800E1DAC[1] = NULL;
    D_80126C2C = NULL;
    D_800E1DA4[0] = NULL;
    D_800E1DA4[1] = NULL;
    D_800E1DB8 = 0;
    D_800E1DBC = 0;
}

GLOBAL_ASM("asm/non_matchings/menu/func_8007FFEC.s")

void func_80080518(f32 arg0, f32 arg1) {
    D_800E1DC0 = (s32) (arg0 * 32.0f);
    D_800E1DC4 = (s32) (arg1 * 32.0f);
}

//https://decomp.me/scratch/W0adv
#ifdef NON_EQUIVALENT
void func_80080580(Gfx** dlist, s32 startX, s32 startY, s32 width, s32 height, s32 borderWidth, s32 borderHeight, s32 colour, TextureHeader *tex) {
    s32 uVals[4];
    s32 vVals[4];
    Vertex* verts;
    Triangle* tris;
    s32 j;
    s32 i;
    s32 texEnabled;

    //((unk80080BC8*)((u8*)D_80126C2C[D_800E1DB8] + (D_800E1DB4 * 4)))->texture = tex;
    ((unk80080BC8*)((u8*)D_80126C2C + (D_800E1DB8 << 5) + (D_800E1DB4 * 4)))->texture = tex;
    //(&(*D_80126C2C)[D_800E1DB8] + (D_800E1DB4 * 4))->texture = tex;
    //D_80126C2C[D_800E1DB8][D_800E1DB4].texture = tex;
    if (tex != NULL) {
        uVals[0] = 0;
        vVals[0] = 0;
        uVals[1] = D_800E1DC0 * borderWidth;
        uVals[2] = (width - borderWidth) * D_800E1DC0;
        uVals[3] = D_800E1DC0 * width;
        vVals[1] = D_800E1DC4 * borderHeight;
        vVals[2] = (height - borderHeight) * D_800E1DC4;
        vVals[3] = D_800E1DC4 * height;
        tris = ((unk80080BC8*)((u8*)D_80126C2C + (D_800E1DB8 << 5) + (D_800E1DB4 * 4)))->triangles;
        for (i = 0; i < 5; i++) {
            tris[i*2].uv0.u = uVals[D_800E1CF0[i][0]];
            tris[i*2].uv0.v = vVals[D_800E1CF0[i][1]];
            tris[i*2].uv1.u = uVals[D_800E1CF0[i][2]];
            tris[i*2].uv1.v = vVals[D_800E1CF0[i][3]];
            tris[i*2].uv2.u = uVals[D_800E1CF0[i][4]];
            tris[i*2].uv2.v = vVals[D_800E1CF0[i][5]];
            tris[i*2+1].uv0.u = uVals[D_800E1CF0[i][6]];
            tris[i*2+1].uv0.v = vVals[D_800E1CF0[i][7]];
            tris[i*2+1].uv1.u = uVals[D_800E1CF0[i][8]];
            tris[i*2+1].uv1.v = vVals[D_800E1CF0[i][9]];
            tris[i*2+1].uv2.u = uVals[D_800E1CF0[i][10]];
            tris[i*2+1].uv2.v = vVals[D_800E1CF0[i][11]];
        }
    }
    verts = ((unk80080BC8*)((u8*)D_80126C2C + (D_800E1DB8 << 5) + (D_800E1DB4 * 4)))->vertices;
    for (i = 0; i < 5; i++) {
        for(j = 0; j < 4; j++) {
            verts[j].x = startX;
            verts[j].y = startY;
            verts[j].x += (D_800E1D2C[j][0] * width);
            verts[j].x += (D_800E1D2C[j][1] * borderWidth);
            verts[j].y += (D_800E1D2C[j][2] * height);
            verts[j].y += (D_800E1D2C[j][3] * borderHeight);
            verts[j].z = 0;
            verts[j].r = (s32) (D_800E1D7C[i][0] * ((colour >> 24) & 0xFF)) >> 8;
            verts[j].g = (s32) (D_800E1D7C[i][1] * ((colour >> 16) & 0xFF)) >> 8;
            verts[j].b = (s32) (D_800E1D7C[i][2] * ((colour >> 8) & 0xFF)) >> 8;
            verts[j].a = (s32) (D_800E1D7C[i][3] * (colour & 0xFF)) >> 8;
        }
    }
    if (dlist != NULL) {
        ((unk80080BC8*)((u8*)D_80126C2C + (D_800E1DB8 << 5) + (D_800E1DB4 * 4)))->unk18 = 1;
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
        temp_v0_6->words.w0 = (((((*(D_80126C2C + (D_800E1DB8 << 5) + (D_800E1DB4 * 4)) + 0x80000000) & 6) | 0x98) & 0xFF) << 0x10) | 0x04000000 | 0x170;
        temp_v0_6->words.w1 = *(D_80126C2C + (D_800E1DB8 << 5) + (D_800E1DB4 * 4)) + 0x80000000;
        */
        gSPVertexDKR((*dlist)++, OS_K0_TO_PHYSICAL(((unk80080BC8*)((u8*)D_80126C2C + (i * 32) + (D_800E1DB4 * 4)))->vertices), 20, 0); 
        /* 
        temp_v0_7 = *dlist;
        *dlist = temp_v0_7 + 8;
        temp_v0_7->words.w0 = (((texEnabled | 0x90) & 0xFF) << 0x10) | 0x05000000 | 0xA0;
        temp_v0_7->words.w1 = (D_80126C2C + (D_800E1DB8 << 5) + (D_800E1DB4 * 4))->unk8 + 0x80000000;
        */
        gSPPolygon((*dlist)++, OS_K0_TO_PHYSICAL(((unk80080BC8*)((u8*)D_80126C2C + (i * 32) + (D_800E1DB4 * 4)))->triangles), 10, texEnabled);
        reset_render_settings(dlist);
    } else {
        ((unk80080BC8*)((u8*)D_80126C2C + (D_800E1DB8 * 32) + (D_800E1DB4 * 4)))->unk18 = 0;
    }
    D_800E1DB8++;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80080580.s")
#endif

//https://decomp.me/scratch/lS3f5
#ifdef NON_EQUIVALENT
void func_80080BC8(Gfx** dlist) {
    s16 temp_a1;
    s32 i;
    s32 var_t0;
    TextureHeader *tex;
    TextureHeader *lastTex;
    
    gSPDisplayList((*dlist)++, &dMenuHudSettings); 
    var_t0 = -1;
    lastTex = NULL;
    
    for (i = 0; i < D_800E1DB8; i++) {
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
    D_800E1DB8 = 0;
    D_800E1DB4 = 1 - D_800E1DB4;
    reset_render_settings(dlist);
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80080BC8.s")
#endif

void func_80080E6C(void) {
    D_800E1DB8 = 0;
    D_800E1DB4 = (s32)(1 - D_800E1DB4);
}

//https://decomp.me/scratch/IZ1Gq
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
    gSavefileData[0]->courseFlagsPtr = (u8 *)gSavefileData[0] + sizeof(Settings);
    gSavefileData[0]->balloonsPtr = (u8 *)gSavefileData[0]->courseFlagsPtr + sp28;
    gSavefileData[1] = (u8 *)gSavefileData[0] + sp20;
    gSavefileData[1]->courseFlagsPtr = (u8 *)gSavefileData[1] + sizeof(Settings);
    gSavefileData[1]->balloonsPtr = (u8 *)gSavefileData[1]->courseFlagsPtr + sp28;
    gSavefileData[2] = (u8 *)gSavefileData[1] + sp20;
    gSavefileData[2]->courseFlagsPtr = (u8 *)gSavefileData[2] + sizeof(Settings);
    gSavefileData[2]->balloonsPtr = (u8 *)gSavefileData[2]->courseFlagsPtr + sp28;
    gSavefileData[3] = (u8 *)gSavefileData[2] + sp20;
    gSavefileData[3]->courseFlagsPtr = (u8 *)gSavefileData[3] + sizeof(Settings);
    gSavefileData[3]->balloonsPtr = (u8 *)gSavefileData[3]->courseFlagsPtr + sp28;
    gCheatsAssetData = get_misc_asset(MISC_ASSET_UNK41);
    gNumberOfCheats = (s32)(*gCheatsAssetData);
    gMenuText = allocate_from_main_pool_safe(1024 * sizeof(char *), COLOUR_TAG_WHITE);
    load_menu_text(LANGUAGE_ENGLISH);
    for (i = 0; i < 128; i++) {
        gMenuTextures[i] = NULL;
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

    //Needs to be one line
    for (i = 0; i < ARRAY_COUNT(D_80126808); i++) { D_80126808[i] = 0; }
    func_80001844();
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
s32 menu_loop(Gfx **currDisplayList, MatrixS **currHudMat, Vertex **currHudVerts, TriangleList **currHudTris, s32 updateRate) {
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
    func_80068508(1);
    func_8007BF1C(FALSE);

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

    func_80068508(0);
    func_8007BF1C(TRUE);
    sMenuGuiColourR = (u8)255;
    sMenuGuiColourG = (u8)255;
    sMenuGuiColourB = (u8)255;
}

#ifdef NON_EQUIVALENT
//void func_80081C04(s32 num, s32 x, s32 y, u8 r, u8 g, u8 b, u8 a, u8 font, u8 alignment)
void func_80081C04(s32 num, s32 x, s32 y, u8 red, u8 green, u8 blue, u8 alpha, u8 font, u8 alignment) {
    u8 *sp38;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s3;
    s32 var_s4_2;
    s32 found;

    var_s3 = 0;
    var_s0 = 1000000000;
    found = FALSE;

    while (var_s0 >= 10) {
        if (num < var_s0) {
            found = TRUE;
            sp38[var_s3] = (num / var_s0);
            num %= var_s0;
        } else if (found) {
            sp38[var_s3] = 0;
        }
        var_s3++;
        var_s0 /= 10;
    }
    sp38[var_s3] = num;
    var_s3++;
    if (alignment & 4) {
        x -= var_s3 * 12;
        var_s4_2 = x + 6;
    }
    else if (alignment & 1) {
        var_s4_2 = x - ((var_s3 * 11) >> 1);
    } else {
        var_s4_2 = x + 6;
    }
    if (alignment & 8) {
        y += 7;
    } else if (alignment & 0x10) {
        y -= 7;
    }
    sMenuGuiColourR = red;
    sMenuGuiColourG = green;
    sMenuGuiColourB = blue;
    sMenuGuiOpacity = alpha;
    func_8007BF1C(0);
    func_80068508(1);
    gMenuImageStack->unk10 = y;
    for (var_s0_2 = 0; var_s0_2 < var_s3; var_s0_2++, var_s4_2 += 12) {
        gMenuImageStack->unkC = var_s4_2;
        gMenuImageStack->unk18 = sp38[var_s0_2];
        func_8009CA60(0);
    }
    func_8007BF1C(1);
    func_80068508(0);
    sMenuGuiColourR = 255;
    sMenuGuiColourG = 255;
    sMenuGuiColourB = 255;
    sMenuGuiOpacity = 255;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80081C04.s")
#endif

void func_80081E54(MenuElement *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    D_800DF798 = arg0;
    D_800DF794 = 0;
    D_80126858 = arg1 * 60.0f;
    D_8012685C = arg2 * 60.0f;
    D_80126860 = arg3 * 60.0f;
    D_80126854 = 0;
    D_800DF79C = arg4;
    D_800DF7A0 = arg5;
    if (D_80126858 > 0) {
        play_sound_global(SOUND_WHOOSH1, NULL);
    }
}

s32 func_80081F4C(s32 updateRate) {
    f32 var_f20;
    s32 ret;
    s32 i;
    s32 buttonsPressedAllPlayers;

    ret = 1;
    var_f20 = -1.0f;
    buttonsPressedAllPlayers = 0;
    if (D_800DF794 != 4) {
        if (gIgnorePlayerInputTime == 0) {
            for (i = 0; i < gNumberOfActivePlayers; i++) {
                buttonsPressedAllPlayers |= get_buttons_pressed_from_player(i);
            }
        }
        D_80126854 += updateRate;
        do {
            switch (D_800DF794) {
                case 0:
                    if (buttonsPressedAllPlayers & (A_BUTTON | START_BUTTON)) {
                        D_80126854 = 0;
                        D_800DF794 = 1;
                        buttonsPressedAllPlayers = 0;
                    } else {
                        if (D_80126854 >= D_80126858) {
                            D_80126854 -= D_80126858;
                            D_800DF794 = 1;
                        } else {
                            var_f20 = (f32) D_80126854 / (f32) D_80126858;
                        }
                    }
                    break;
                case 1:
                    if (D_8012685C < 0) {
                        D_80126854 = 0;
                    }
                    if (buttonsPressedAllPlayers & (A_BUTTON | START_BUTTON)) {
                        D_80126854 = 0;
                        D_800DF794 = 2;
                        buttonsPressedAllPlayers = 0;
                        if (D_80126860 > D_80126854) {
                            play_sound_global(SOUND_WHOOSH1, NULL);
                        }
                    } else {
                        if (D_80126854 >= D_8012685C) {
                            D_80126854 -= D_8012685C;
                            D_800DF794 = 2;
                            if (D_80126854 < D_80126860) {
                                play_sound_global(SOUND_WHOOSH1, NULL);
                            }
                        } else {
                            var_f20 = (f32) D_80126854 / (f32) D_8012685C;
                        }
                    }
                    break;
                case 2:
                    if ((buttonsPressedAllPlayers & (A_BUTTON | START_BUTTON)) || (D_80126854 >= D_80126860)) {
                        D_800DF794 = 4;
                    } else {
                        var_f20 = (f32) D_80126854 / (f32) D_80126860;
                    }
                    break;
            }
        } while ((var_f20 < 0.0f) && (D_800DF794 != 4));

        if (D_800DF794 != 4) {
            draw_menu_elements(D_800DF794, D_800DF798, var_f20);
            ret = 0;
        }
    }
    return ret;
}

#ifdef NON_EQUIVALENT

void draw_menu_elements(s32 arg0, MenuElement *elem, f32 arg2) {
    s32 s5;
    s32 tempX, tempY;
    s32 xPos, yPos;

    s5 = FALSE;
    if (arg0 != 4) {
        set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
        while (elem->unk14_a.element != NULL) {
            if (elem->unk14_a.element != &D_80126850) {
                if (arg0 == 0) {
                    tempX = elem->center - elem->left;
                    tempX *= arg2;
                    xPos = tempX + elem->left;
                    tempY = elem->middle - elem->top;
                    tempY *= arg2;
                    yPos = tempY + elem->top;
                } else if (arg0 == 1) {
                    xPos = elem->center;
                    yPos = elem->middle;
                } else {
                    tempX = elem->right - elem->center;
                    tempX *= arg2;
                    xPos = tempX + elem->center;
                    tempY = elem->bottom - elem->middle;
                    tempY *= arg2;
                    yPos = (tempY & 0xFFFFFFFFFFFFFFFFu) + elem->middle;
                }
                switch (elem->elementType) {
                    case 0: //ascii text
                        set_text_background_colour(
                            elem->details.background.backgroundRed, 
                            elem->details.background.backgroundGreen,
                            elem->details.background.backgroundBlue,
                            elem->details.background.backgroundAlpha);
                        set_text_colour(elem->filterRed, elem->filterGreen, elem->filterBlue, elem->filterAlpha, elem->opacity);
                        set_text_font(elem->textFont);
                        draw_text(&sMenuCurrDisplayList, xPos, yPos + D_800DF79C, elem->unk14_a.asciiText, elem->textAlignFlags);
                        break;
                    case 1:
                        if (s5) {
                            s5 = FALSE;
                            reset_render_settings(&sMenuCurrDisplayList);
                        }
                        sMenuGuiOpacity = elem->opacity;
                        show_timestamp(
                            *elem->unk14_a.numberU16,
                            xPos - 160,
                            (-yPos - D_800DF7A0) + 120,
                            elem->filterRed,
                            elem->filterGreen,
                            elem->filterBlue,
                            elem->textFont);
                        break;
                    case 2: //Number
                        if (s5) {
                            s5 = FALSE;
                            reset_render_settings(&sMenuCurrDisplayList);
                        }
                        func_80081C04(
                            *elem->unk14_a.number,
                            xPos - 160,
                            (-yPos - D_800DF7A0) + 120,
                            elem->filterRed,
                            elem->filterGreen,
                            elem->filterBlue,
                            elem->opacity,
                            elem->textFont,
                            elem->textAlignFlags);
                        break;
                    case 3:
                        render_textured_rectangle(
                            &sMenuCurrDisplayList,
                            elem->unk14_a.texture,
                            xPos,
                            yPos + D_800DF79C,
                            elem->filterRed,
                            elem->filterGreen,
                            elem->filterBlue,
                            elem->opacity);
                        s5 = TRUE;
                        break;
                    case 4:
                        render_texture_rectangle_scaled(
                            &sMenuCurrDisplayList,
                            elem->unk14_a.element,
                            xPos,
                            yPos + D_800DF79C,
                            elem->details.texture.width / 256.0f,
                            elem->details.texture.height / 256.0f,
                            (elem->filterRed << 24) | (elem->filterGreen << 16) | (elem->filterBlue << 8) | elem->opacity,
                            elem->textAlignFlags);
                        s5 = TRUE;
                        break;
                    case 5:
                        if (s5) {
                            s5 = FALSE;
                            reset_render_settings(&sMenuCurrDisplayList);
                        }
                        func_80068508(1);
                        func_8007BF1C(FALSE);
                        gMenuImageStack[elem->unk14_a.value].unkC = xPos - 160;
                        gMenuImageStack[elem->unk14_a.value].unk10 = (-yPos - D_800DF7A0) + 120;
                        gMenuImageStack[elem->unk14_a.value].unk18 = elem->textFont;
                        gMenuImageStack[elem->unk14_a.value].unk4 = elem->details.background.backgroundRed;
                        gMenuImageStack[elem->unk14_a.value].unk2 = elem->details.background.backgroundGreen;
                        gMenuImageStack[elem->unk14_a.value].unk0 = elem->details.background.backgroundBlue;
                        gMenuImageStack[elem->unk14_a.value].unk8 = elem->details.background.backgroundAlpha / 256.0f;
                        sMenuGuiColourR = elem->filterRed;
                        sMenuGuiColourG = elem->filterGreen;
                        sMenuGuiColourB = elem->filterBlue;
                        D_800DF4B0 = elem->filterAlpha;
                        sMenuGuiOpacity = elem->opacity;
                        func_8009CA60(elem->unk14_a.value);
                        func_80068508(0);
                        func_8007BF1C(TRUE);
                        break;
                    case 6:
                        func_80080E90(
                            &sMenuCurrDisplayList,
                            xPos,
                            yPos + D_800DF7A0,
                            elem->details.texture.width,
                            elem->details.texture.height,
                            elem->details.texture.borderWidth,
                            elem->details.texture.borderHeight,
                            elem->filterRed,
                            elem->filterGreen,
                            elem->filterBlue,
                            elem->opacity);
                        break;
                    case 7: //Texture
                        func_80080580(
                            &sMenuCurrDisplayList,
                            xPos,
                            yPos + D_800DF7A0,
                            elem->details.texture.width,
                            elem->details.texture.height,
                            elem->details.texture.borderWidth,
                            elem->details.texture.borderHeight,
                            (elem->filterRed << 24) | (elem->filterGreen << 16) | (elem->filterBlue << 8) | elem->opacity,
                            elem->unk14_a.element);
                        break;
                }
            }
            elem++; // Go onto the next element.
        }
        if (s5) {
            reset_render_settings(&sMenuCurrDisplayList);
        }
        sMenuGuiColourR = 0xFF;
        sMenuGuiColourG = 0xFF;
        sMenuGuiColourB = 0xFF;
        D_800DF4B0 = 0;
        sMenuGuiOpacity = 0xFF;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/draw_menu_elements.s")
#endif

void func_800828B8(void) {
    s32 i;
    s32 numWorlds;
    s32 numLevels;
    Settings *settings;

    settings = get_settings();
    get_number_of_levels_and_worlds(&numLevels, &numWorlds);

    for (i = 0; i < numLevels; i++) {
        settings->courseFlagsPtr[i] = 0;
        for (numWorlds = 0; numWorlds < 3; numWorlds++) {
            settings->courseFlagsPtr[i] |= gSavefileData[numWorlds]->courseFlagsPtr[i];
        }
    }

    settings->trophies = 0;
    settings->keys = 0;
    settings->bosses = 0;
    settings->cutsceneFlags = 0;
    for (i = 0; i < 3; i++) {
        settings->trophies |= gSavefileData[i]->trophies;
        settings->keys |= gSavefileData[i]->keys;
        settings->bosses |= gSavefileData[i]->bosses;
        settings->cutsceneFlags |= gSavefileData[i]->cutsceneFlags;
    }
}

void print_missing_controller_text(Gfx **dl, s32 updateRate) {
    s32 posY;

    D_800DF46C += updateRate;

    if (D_800DF46C & 0x10) {
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
        resize_viewport(0, 0, 38, SCREEN_WIDTH, SCREEN_HEIGHT - 16);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT + 44);
    } else {
        resize_viewport(0, 0, 40, SCREEN_WIDTH, SCREEN_HEIGHT - 44);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    copy_viewports_to_stack(); //Init viewports
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
            transition_begin(&D_800E1DE8);
            gMenuDelay = 1;
        }
        sBootScreenTimer -= updateRate / 50.0f;
    } else {
        yOffset = 0;
        if (sBootScreenTimer < 2.17f && gMenuDelay == 0) {
            transition_begin(&D_800E1DE8);
            gMenuDelay = 1;
        }
        sBootScreenTimer -= updateRate / 60.0f;
    }
    if (sBootScreenTimer <= 0.0f) {
        camDisableUserView(0, 0);
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

GLOBAL_ASM("asm/non_matchings/menu/func_80083098.s")

/**
 * Initialise the title screen menu.
 * Load the title textures and reset player allocation.
 * Set the current level and demo.
*/
void menu_title_screen_init(void) {
    s32 i;
    s32 numberOfPlayers;

    D_800DF488 = 1;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    reset_character_id_slots();
    gSaveFileIndex = 0;
    gTitleScreenCurrentOption = 0;
    gNumberOfActivePlayers = 4;
    initialise_player_ids();
    play_music(SEQUENCE_NONE2);
    sMenuMusicVolume = musicGetRelativeVolume();
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
        sGameTitleTileOffsets[i].texture = gMenuTextures[sGameTitleTileTextures[i]];
    }
    set_music_player_voice_limit(27);
    func_800660C0();
    set_text_font(ASSET_FONTS_FUNFONT);
    load_font(ASSET_FONTS_BIGFONT);
    reset_sound_volume(FALSE);
    set_time_trial_enabled(FALSE);
    gTitleDemoIndex = 0;
    sTitleScreenDemoIds = (s8 *) get_misc_asset(MISC_ASSET_TITLE_DEMOS);
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
    D_800DF9F4 = 0;
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
        func_80068508(0);
        if (scale != 1.0f) {
            render_texture_rectangle_scaled(&sMenuCurrDisplayList, sGameTitleTileOffsets, SCREEN_WIDTH_FLOAT_HALF, 52.0f, scale, scale, 0xFFFFFFFE, TEXRECT_POINT);
        } else {
            render_textured_rectangle(&sMenuCurrDisplayList, sGameTitleTileOffsets, SCREEN_WIDTH_HALF, 52, 255, 255, 255, 255);
        }
        if (!is_controller_missing()) {
            i = 0; 
            posY = (osTvType == TV_TYPE_PAL) ? SCREEN_HEIGHT - 22 : SCREEN_HEIGHT - 48;
            set_text_font(ASSET_FONTS_FUNFONT);
            set_text_background_colour(0, 0, 0, 0);
            while(gTitleMenuStrings[i] != NULL) {
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
    ObjectSegment* sp18;
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
            set_music_fade_timer(-768);
            sp28 = 0;
            transition_begin(&D_800E1E08);
        }
        if (gTitleDemoTimer <= 0) {
            sp28 = 1;
        }
    } else {
        gTitleDemoTimer = 0;
    }
    if (gMenuDelay == 0 && (func_800214C4() || sp28)) {
        if (gTitleDemoTimer){} // Fakematch
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
            D_800DF9F4 = 0;
            gOpacityDecayTimer = 0;
        }
    }
    if (gTitleRevealTimer) {
        if (gTitleRevealTimer < 32) {
            if (gTitleRevealTimer == 1) {
                play_sound_global(SOUND_WHOOSH1, 0);
            }
            gTitleRevealTimer += updateRate;
            if (gTitleRevealTimer >= 32) {
                gTitleRevealTimer = 32;
                sp18->object.distanceToCamera = 8.0f;
                play_sound_global(SOUND_EXPLOSION, 0);
            }
        } else {
            if (gTitleAudioCounter < 6.0f) {
                gTitleAudioCounter += updateRateF;
                if (gTitleAudioCounter > 0.67f && gMenuOptionCount == 0) {
                    play_sound_global(SOUND_VOICE_TT_DIDDY_KONG_RACING, 0);
                    gMenuOptionCount = 1;
                } else if ((gTitleAudioCounter > 2.83f) && (gMenuOptionCount == 1)) {
                    play_sound_global(SOUND_VOICE_TT_PRESS_START, 0);
                    gMenuOptionCount = 2;
                }
            }
        }
    }
    if (gTitleAudioCounter > 0.0f) {
        if (gTitleAudioCounter < 0.5f) {
            set_relative_volume_for_music((s32) ((f32) sMenuMusicVolume * (1.0f - gTitleAudioCounter)));
        } else if (gTitleAudioCounter < 4.5f) {
            set_relative_volume_for_music(((s32) sMenuMusicVolume >> 1));
        } else if (gTitleAudioCounter < 5.0f) {
            set_relative_volume_for_music((s32) ((f32) sMenuMusicVolume * (gTitleAudioCounter - 4.0f)));
        } else {
            set_relative_volume_for_music(*((s8*)&sMenuMusicVolume + 3));
        }
    }
    if (gTitleRevealTimer == 0) {
        if (D_801267D8[4] & (A_BUTTON | START_BUTTON)) {
            gTitleRevealTimer = 1;
        }
    } else if ((gMenuDelay == 0) && !is_controller_missing()) {
        s32 temp0 = gTitleScreenCurrentOption;
        // D_80126838 = +1 when going up, and -1 when going down.
        if ((D_80126838 < 0) && (gTitleScreenCurrentOption < 1)) {
            gTitleScreenCurrentOption++;
        }
        if ((D_80126838 > 0) && (gTitleScreenCurrentOption > 0)) {
            gTitleScreenCurrentOption--;
        }
        if (temp0 != gTitleScreenCurrentOption) {
            play_sound_global(SOUND_MENU_PICK2, (s32 *) (0 * contrIndex)); // TODO: The `* contrIndex` here is a fake match.
        }
        if (D_801267D8[4] & (A_BUTTON | START_BUTTON)) {
            for(contrIndex = 3; contrIndex > 0 && !(D_801267D8[contrIndex] & (A_BUTTON | START_BUTTON)); contrIndex--){}
            set_active_player_index(contrIndex);
            gMenuDelay = 1;
            transition_begin(&sMenuTransitionFadeIn);
            enable_new_screen_transitions();
            play_sound_global(SOUND_SELECT2, 0);
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
        D_800DF460 = 0;
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
    set_music_player_voice_limit(16);
    func_800660D0();
    unload_font(ASSET_FONTS_BIGFONT);
    reset_sound_volume(TRUE);
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
    set_music_player_voice_limit(24);
    play_music(SEQUENCE_MAIN_MENU);
    func_80000B18();
}

//Draws options menu screen
void render_options_menu_ui(UNUSED s32 updateRate) {
    s32 optionMenuTextIndex;
    s32 alpha;
    s32 yPos;

    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_background_colour(0, 0, 0, 0);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, gMenuText[ASSET_MENU_TEXT_OPTIONS], ALIGN_MIDDLE_CENTER); // OPTIONS
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, gMenuText[ASSET_MENU_TEXT_OPTIONS], ALIGN_MIDDLE_CENTER); // OPTIONS

    optionMenuTextIndex = 0;
    yPos = 76;

    set_text_font(ASSET_FONTS_FUNFONT);

    while (gOptionMenuStrings[optionMenuTextIndex] != NULL) {
        if (optionMenuTextIndex == D_800DF460) {
            alpha = gOptionBlinkTimer * 8;
            if (gOptionBlinkTimer >= 32) {
                alpha = 511 - alpha;
            }
        } else {
            alpha = 0;
        }
        set_text_colour(255, 255, 255, alpha, 255);
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, yPos, gOptionMenuStrings[optionMenuTextIndex], ALIGN_MIDDLE_CENTER);

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
        for (i = 0, xAxisPtr = gControllersXAxisDirection, yAxisPtr = gControllersYAxisDirection; i < MAXCONTROLLERS; i++) {
            buttonsPressed |= get_buttons_pressed_from_player(i);
            analogueX += *(xAxisPtr++);
            analogueY += *(yAxisPtr++);
        }
    }
    if ((buttonsPressed & B_BUTTON) || ((buttonsPressed & (A_BUTTON | START_BUTTON)) && D_800DF460 == 5)) {
        // Leave the option menu
        set_music_fade_timer(-128);
        gMenuDelay = -1;
        transition_begin(&sMenuTransitionFadeIn);
        play_sound_global(SOUND_MENU_BACK3, NULL);
    } else if ((buttonsPressed & (A_BUTTON | START_BUTTON)) && D_800DF460 >= 2) {
        // Go to a sub-menu
        gMenuDelay = 31;
        play_sound_global(SOUND_SELECT2, NULL);
        
    } else if (D_800DF460 == 0 && analogueX != 0) {
        switch ((u64) get_language()) {
            case LANGUAGE_ENGLISH:
                 set_language(LANGUAGE_FRENCH);
                 break;
            default:
                set_language(LANGUAGE_ENGLISH);
                break;
        }
        play_sound_global(SOUND_MENU_PICK2, NULL);
    } else if (D_800DF460 == 1 && analogueX != 0) {
        if (sEepromSettings & 0x2000000) {
            //0x2000000 SUBTITLES ENABLED?
            play_sound_global(SOUND_MENU_PICK2, NULL);
            unset_eeprom_settings_value(0x2000000);
            set_subtitles(0);
           gOptionMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_SUBTITLESOFF];
        } else {
            play_sound_global(SOUND_MENU_PICK2, NULL);
            set_eeprom_settings_value(0x2000000);
            set_subtitles(1);
            gOptionMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_SUBTITLESON];
        }
    } else {
        s32 prev_D_800DF460 = D_800DF460;
        if (analogueY < 0) {
            D_800DF460++;
            if (D_800DF460 >= 6) {
                D_800DF460 = 5;
            }
        }
        if (analogueY > 0) {
            D_800DF460--;
            if (D_800DF460 < 0) {
                D_800DF460 = 0;
            }
        }
        if (prev_D_800DF460 != D_800DF460) {
            play_sound_global(SOUND_MENU_PICK2, NULL);
        }
    }
    if (gMenuDelay > 30) {
        // Change screen to a sub-menu
        if (D_800DF460 == 2) {
            unload_big_font_1();
            menu_init(MENU_AUDIO_OPTIONS);
            return MENU_RESULT_CONTINUE;
        }
        if (D_800DF460 == 3) {
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
        func_80000B28();
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
    gMusicVolumeSliderValue = musicGetVolSliderPercentage();
    gSfxVolumeSliderValue = get_sfx_volume_slider();
    if (gActiveMagicCodes & CHEAT_MUSIC_MENU) { // Check if "JUKEBOX" cheat is active
        gAudioMenuStrings[6].unkC = gMusicTestString;
        gAudioMenuStrings[3].unk2 = 212;
        set_music_player_voice_limit(32);
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
            for(i = 0; i < 4; i++) {
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
            if (((buttonsPressed & (A_BUTTON | START_BUTTON)) && (gMenuOptionCount == gOptionsMenuItemIndex + 1)) || (buttonsPressed & B_BUTTON)) {
                gMenuDelay = -1;
                transition_begin(&sMenuTransitionFadeIn);
                if (gOpacityDecayTimer >= 0) {
                    set_music_fade_timer(-128);
                    
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
                    D_800DFAC8--;
                } else {
                    D_800DFAC8++;
                }
                if (D_800DFAC8 < 0) {
                    D_800DFAC8 = 2;
                }
                if (D_800DFAC8 >= 3) {
                    D_800DFAC8 = 0;
                }
                set_stereo_pan_mode(D_800DFAC8);
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
                    set_music_volume_slider(gMusicVolumeSliderValue);
                    if (!music_is_playing()) {
                        if (gOpacityDecayTimer >= 0) {
                            func_80000B28();
                            play_music(D_800DFABC);
                        } else {
                            func_80000B28();
                            set_music_player_voice_limit(24);
                            play_music(SEQUENCE_MAIN_MENU);
                            func_80000B18();
                        }
                    }
                }
            } else if (gMenuOptionCount >= 5 && gOptionsMenuItemIndex == 3) {
                if (contX < 0 && D_800DFABC > 0) {
                    D_800DFABC--;
                    sp30 = 1;
                } else if (contX > 0) {
                    if (D_800DFABC < (ALSeqFile_80115CF8_GetSeqCount() - 1)) {
                        D_800DFABC++;
                        sp30 = 1;
                    }
                }
                if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                    func_80000B28();
                    set_music_player_voice_limit(24);
                    play_music(D_800DFABC);
                    gOpacityDecayTimer = D_800DFABC;
                }
            }
            if (gOptionsMenuItemIndex == 1) {
                if (D_801269FC == NULL) {
                    play_sound_global(SOUND_VOICE_DIDDY_POSITIVE5, (s32 *) &D_801269FC);
                }
            } else if (D_801269FC != NULL) {
                func_8000488C((u8* ) D_801269FC);
            }
            if (sp30 == 3) {
                play_sound_global(SOUND_MENU_BACK3, NULL);
            } else if (sp30 == 2) {
                play_sound_global(SOUND_SELECT2, NULL);
            } else if (sp30 == 1) {
                play_sound_global(SOUND_MENU_PICK2, NULL);
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
        set_music_player_voice_limit(24);
        play_music(SEQUENCE_MAIN_MENU);
        set_music_fade_timer(0x100);
        func_80000B18();
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
    D_80126A64 = (u8 *) allocate_from_main_pool_safe(0x800, COLOUR_TAG_WHITE);
    D_80126A0C = (unk800861C8 *) allocate_from_main_pool_safe(0xA00, COLOUR_TAG_WHITE);
    D_80126A04 = &D_80126A0C[80];
    D_80126A08 = 0;
    D_80126BD4 = 0;
    D_80126BDC = 0.0f;
    D_80126A00 = 0;
    D_80126BE4 = 0;
    D_80126BEC = 0.0f;
    func_8009C674(D_800DFC78);
    allocate_menu_images(D_800DFCAC);
    func_8007FFEC(0xA);
    load_font(ASSET_FONTS_BIGFONT);
    D_800DFC10[0].texture = gMenuTextures[TEXTURE_ICON_SAVE_N64];
    D_800DFC20[0].texture = gMenuTextures[TEXTURE_ICON_SAVE_TT];
    D_800DFC30[0].texture = gMenuTextures[TEXTURE_ICON_SAVE_GHOSTS];
    D_800DFC40[0].texture = gMenuTextures[TEXTURE_ICON_SAVE_FILECABINET];
    D_800DFC50[0].texture = gMenuTextures[TEXTURE_ICON_SAVE_CPAK];
    D_800DFC60[0].texture = gMenuTextures[TEXTURE_ICON_SAVE_BIN];
    assign_menu_arrow_textures();
    mark_read_all_save_files();
    transition_begin(&sMenuTransitionFadeOut);
}

GLOBAL_ASM("asm/non_matchings/menu/func_800853D0.s")

#ifdef NON_EQUIVALENT
void func_80085B9C(UNUSED s32 updateRate) {
    s32 yPos; //yPos
    s32 var_s2; //for loop iterator?
    s32 var_s3; //bool
    s32 temp_f4;
    s32 videoWidth;
    s32 temp_v0;
    s32 drawTexturedRectangle; //bool
    s32 drawPleaseWait; //bool
    s32 drawOk; //bool
    s32 drawDialogueBox; //bool
    DrawTexture *tempTex;

    videoWidth = GET_VIDEO_WIDTH(get_video_width_and_height_as_s32());
    var_s3 = FALSE;
    drawTexturedRectangle = FALSE; //render textured rectangle
    drawPleaseWait = FALSE; //Draw Please Wait
    drawOk = FALSE; //Draw "OK?"
    drawDialogueBox = FALSE; //Render Dialogue Box
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
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, gMenuText[ASSET_MENU_TEXT_SAVEOPTIONS], ALIGN_MIDDLE_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, gMenuText[ASSET_MENU_TEXT_SAVEOPTIONS], ALIGN_MIDDLE_CENTER);
    if (drawTexturedRectangle) {
        yPos = (osTvType == TV_TYPE_PAL) ? SCREEN_HEIGHT_HALF_PAL : SCREEN_HEIGHT_HALF;
        yPos += ((s32) (gOptionBlinkTimer & 0x1F) >> 1);
        var_s2 = 0;
        tempTex = &gMenuSelectionArrowDown[var_s2];
        do {
            render_textured_rectangle(&sMenuCurrDisplayList, tempTex, SCREEN_WIDTH_HALF, yPos, 255, 255, 255, 255);
            tempTex++;
            var_s2++;
            yPos += 16;
        } while(var_s2 != 2);
    }
    if (var_s3) {
        temp_f4 = D_80126BDC;
        temp_v0 = 80 - (s32) ((D_80126BDC - temp_f4) * 164);
        while ((temp_v0 < videoWidth) && (temp_f4 < D_80126A08)) {
            func_800853D0(&D_80126A0C[temp_f4], temp_v0, 64);
            temp_f4++;
            temp_v0 += 164;
        }
        while ((temp_v0 > 0)  && (temp_f4 > 0)) {
            temp_f4--;
            temp_v0 -= 164;
            func_800853D0(&D_80126A0C[temp_f4], temp_v0, 64);
        }
    }
    if (drawTexturedRectangle) {
        temp_f4 = D_80126BEC;
        temp_v0 = 80 - (s32) ((D_80126BEC - temp_f4) * 164);
        while ((temp_v0 < videoWidth) && (temp_f4 < D_80126A00)) {
            func_800853D0(&D_80126A04[temp_f4], temp_v0, 144);
            temp_f4++;
            temp_v0 += 164;
        }
        while ((temp_v0 > 0) && (temp_f4 > 0)) {
            temp_f4--;
            temp_v0 -= 164;
            func_800853D0(&D_80126A04[temp_f4], temp_v0, 144);
        }
    }
    set_text_font(2);
    set_text_colour(255, 255, 255, 0, 255);
    if (drawOk) {
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 128, D_800E8208, ALIGN_MIDDLE_CENTER); // "OK?"
    }
    if (drawPleaseWait) {
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 128, gMenuText[ASSET_MENU_TEXT_PLEASEWAIT], ALIGN_MIDDLE_CENTER);
    }
    if (drawDialogueBox) {
        render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 7);
    }
    func_80080E6C();
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80085B9C.s")
#endif

s32 func_800860A8(s32 controllerIndex, s32 *arg1, unk800861C8 *arg2, s32 *arg3, s32 fileSize, UNUSED s32 arg5) {
    s32 ret = 0;

    if (*arg1 != 0) {
        ret = get_free_space(controllerIndex, &arg2[*arg3].fileSize, &sControllerPakNotesFree[controllerIndex]);
        if (ret == CONTROLLER_PAK_GOOD) {
            if (((s32)arg2[*arg3].fileSize >= fileSize) && (sControllerPakNotesFree[controllerIndex] > 0)) {
                arg2[*arg3].unk0 = 8; //CONTROLLER_PAK_UNK8 maybe?
                arg2[*arg3].controllerIndex = controllerIndex;
                (*arg3)++;
            }
        } else {
            SIDeviceStatus status = ret & 0xFF; //The upper bytes could be controllerIndex, so focus on the status
            if ((*arg1 < 0) && status == RUMBLE_PAK) {
                *arg1 = 0;
                ret = 0;
            } else if
                (status != CONTROLLER_PAK_WITH_BAD_ID &&
                 status != CONTROLLER_PAK_INCONSISTENT &&
                 status != CONTROLLER_PAK_BAD_DATA)
            {
                ret = 0;
            }
        }
    }

    return ret;
}

void func_800861C8(unk800861C8 *arg0, s32 *arg1) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (gSavefileData[i]->newGame) {
            arg0[*arg1].unk0 = 1;
            arg0[*arg1].unk1 = 0;
            arg0[*arg1].unk2 = 0;
            arg0[*arg1].controllerIndex = i;
            arg0[*arg1].fileSize = get_game_data_file_size();
            (*arg1)++;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_800862C4.s")

s32 func_800867D4(void) {
    s32 ret = 0;

    D_80126A00 = 0;

    switch (D_80126A0C[D_80126BD4].unk0) {
        case 1: //Some other type of game data?
            mark_read_save_file(D_80126A0C[D_80126BD4].controllerIndex);
            func_800861C8(D_80126A04, &D_80126A00);
            ret = func_800860A8(0, &D_80126A18, D_80126A04, &D_80126A00, get_game_data_file_size(), -1);
            break;
        case 2: //Some other type of time data?
            ret = func_800860A8(0, &D_80126A18, D_80126A04, &D_80126A00, get_time_data_file_size(), -1);
            break;
        case 3: //GAMD / Game Data
            func_800861C8(D_80126A04, &D_80126A00);
            ret = func_800860A8(1, &D_80126A1C, D_80126A04, &D_80126A00, get_game_data_file_size(), D_80126A0C[D_80126BD4].controllerIndex);
            break;
        case 4: //TIMD / Time Data
            D_80126A04[D_80126A00++].unk0 = 2;
            ret = func_800860A8(1, &D_80126A1C, D_80126A04, &D_80126A00, get_time_data_file_size(), D_80126A0C[D_80126BD4].controllerIndex);
            break;
        case 5: //GHSS / Ghost Data
            D_80126A04[D_80126A00++].unk0 = 9;
            ret = func_800860A8(1, &D_80126A1C, D_80126A04, &D_80126A00, func_80074B1C(), D_80126A0C[D_80126BD4].controllerIndex);
            break;
    }

    D_80126A04[D_80126A00++].unk0 = 7;

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

GLOBAL_ASM("asm/non_matchings/menu/func_80086AFC.s")
GLOBAL_ASM("asm/non_matchings/menu/func_800871D8.s")

s32 func_800874D0(s32 buttonsPressed, s32 arg1) {
    s32 ret;

    ret = 0;
    if (buttonsPressed & B_BUTTON) {
        gMenuOptionCount = 0;
        if (D_80126A10 != D_80126A14) {
            func_800871D8(8);
        } else {
            play_sound_global(SOUND_MENU_BACK3, NULL);
            ret = -1;
        }
    } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        play_sound_global(SOUND_SELECT2, NULL);
        gMenuOptionCount = 4;
    } else if ((arg1 < 0) && (D_80126BD4 > 0)) {
        play_sound_global(SOUND_MENU_PICK2, NULL);
        D_80126BD4--;
    } else if ((arg1 > 0) && (D_80126BD4 < (D_80126A08 - 1))) {
        play_sound_global(SOUND_MENU_PICK2, NULL);
        D_80126BD4++;
    }
    return ret;
}

s32 func_800875E4(s32 buttonsPressed, s32 arg1) {
    if (buttonsPressed & B_BUTTON) {
        play_sound_global(SOUND_MENU_BACK3, NULL);
        gMenuOptionCount = 3;
    } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        play_sound_global(SOUND_SELECT2, NULL);
        gMenuOptionCount = 6;
    } else if ((arg1 < 0) && (D_80126BE4 > 0)) {
        play_sound_global(SOUND_MENU_PICK2, NULL);
        D_80126BE4--;
    } else if ((arg1 > 0) && (D_80126BE4 < D_80126A00 - 1)) {
        play_sound_global(SOUND_MENU_PICK2, NULL);
        D_80126BE4++;
    }

    return 0;
}

s32 func_800876CC(s32 buttonsPressed, UNUSED s32 arg1) {
    if (buttonsPressed & B_BUTTON) {
        play_sound_global(SOUND_MENU_BACK3, NULL);
        gMenuOptionCount = 5;
    } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        play_sound_global(SOUND_SELECT2, NULL);
        gMenuOptionCount = 7;
        gOpacityDecayTimer = 0;
    }

    return 0;
}

GLOBAL_ASM("asm/non_matchings/menu/func_80087734.s")

s32 menu_save_options_loop(s32 updateRate) {
    s32 result;
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
        for(i = 0; i < 4; i++) {
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
            if (result != 0) {
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
                if (result != 0) {
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
    func_8009C4A8(D_800DFC78);
    assign_dialogue_box_id(7);
    free_from_memory_pool((void *)D_80126A0C);
    free_from_memory_pool((void *)D_80126A64);
}

#ifdef NON_EQUIVALENT
//Nearly complete
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
    //Is this really <= 0?
    for (i = 0; i <= 0; i++) {
        //sControllerPakIssueNotFound[i] = 0;
        sControllerPakFatalErrorFound[i] = 0;
        sControllerPakNoFreeSpace[i] = 0;
        sControllerPakBadData[i] = 0;
        ret = get_free_space(i, &bytesFree, &notesFree);
        pakStatus = ret & 0xFF; //Upper 2 bits are controller index
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
            //Bad data
            if (pakStatus == CONTROLLER_PAK_BAD_DATA) {
                sControllerPakBadData[i] = 1;
                pakStatusError9++;
            }
            //Error inconsistent
            if (pakStatus == CONTROLLER_PAK_INCONSISTENT) {
                //Repair file system
                repair_controller_pak(i);
            }
            //fatal error
            if (pakStatus == CONTROLLER_PAK_WITH_BAD_ID) {
                sControllerPakFatalErrorFound[i] = 1;
                pakStatusError3++;
            }
        }
    }
    if (   (pakStatusSuccess == 0)
        || (pakStatusError3  != 0)
        || (pakStatusErrorNoFreeSpace != 0)
        || (pakStatusError9 != 0)) {
        return NO_CONTROLLER_PAK; // Return unsuccessfully?
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
            if (controllerIndexVal < 0) {;
                controllerIndexVal++;
                i++;
            }
        } while (sControllerPakIssueNotFound[i] == 0);
    }

    *controllerIndex = controllerIndexVal;
    ret = get_controller_pak_file_list(controllerIndexVal, 16, &sCurrentControllerPakAllFileNames, &sCurrentControllerPakAllFileExtensions, &sCurrentControllerPakAllFileSizes, &sCurrentControllerPakAllFileTypes);

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

                if ((sCurrentControllerPakAllFileExtensions[i] != 0) && (*sCurrentControllerPakAllFileExtensions[i] != 0)) {
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

        packDirectoryFree(); //Free D_800DE440 from memory
        get_free_space(*controllerIndex, &sCurrentControllerPakFreeSpace, NULL); //Get Available Space in Controller Pak
        sCurrentControllerPakFreeSpace = sCurrentControllerPakFreeSpace / 256; //Bytes
        ret = pakStatus; //Really?
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

    // This has been hard limited to just the first controller pak, but can easily be modified to check the rest with i <= MAXCONTROLLERS
    for (i = 0; i <= 0 && errorFound == 0; i++) {
        if (sControllerPakFatalErrorFound[i] != 0) {
            gControllerPakMenuElement[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_PAKERROR];           // PAK ERROR
            gControllerPakMenuElement[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_PAKERROR];           // PAK ERROR
            gControllerPakMenuElement[2].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + i];       // CONTROLLER PAK 1 / 2 / 3 / 4
            gControllerPakMenuElement[3].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CONTPAKISDAMAGED_0]; // IRREPARABLY DAMAGED.
            gControllerPakMenuElement[4].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_TURNOFFN64_0];       // Switch off the N64
            gControllerPakMenuElement[5].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_TURNOFFN64_1];       // and remove the controller pak.
            sControllerPakError = PAK_ERROR_FATAL;
            errorFound = 1;
        } else if ((sControllerPakNoFreeSpace[i] != 0) && (sControllerPakDataPresent[i] == 0)) {
            gControllerPakMenuElement[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION];            // CAUTION
            gControllerPakMenuElement[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION];            // CAUTION
            gControllerPakMenuElement[2].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + i];       // CONTROLLER PAK 1 / 2 / 3 / 4
            gControllerPakMenuElement[3].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CONTPAKFULL];        // CONTROLLER PAK FULL
            gControllerPakMenuElement[4].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CONTINUE];           // CONTINUE
            gControllerPakMenuElement[5].unk14_a.asciiText = NULL;
            sControllerPakDataPresent[i] = 1;
            sControllerPakError = PAK_ERROR_FULL;
            errorFound = 1;
        } else if (sControllerPakBadData[i] != 0) {
            gControllerPakMenuElement[0].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION];            // CAUTION
            gControllerPakMenuElement[1].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION];            // CAUTION
            gControllerPakMenuElement[2].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + i];       // CONTROLLER PAK 1 / 2 / 3 / 4
            gControllerPakMenuElement[3].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_0];      // CORRUPT DATA.
            gControllerPakMenuElement[4].unk14_a.asciiText = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_1];      // TRY AGAIN!
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
        sGameTitleTileOffsets[i].texture = gMenuTextures[sGameTitleTileTextures[i]];
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
        render_textured_rectangle(&sMenuCurrDisplayList, sGameTitleTileOffsets, SCREEN_WIDTH_HALF, temp, 255, 255, 255, 255);
        reset_render_settings(&sMenuCurrDisplayList);
    }

    return out;
}

void func_800887C4(void) {
    func_8009C4A8((s16 *)sGameTitleTileTextures);
}

void func_800887E8(void) {
    s32 i;

    // Starting point
    D_80126AA0[0] = allocate_from_main_pool_safe(0x200, COLOUR_TAG_WHITE);

    // Fills in the table.
    for (i = 1; i < 16; i++) {
        D_80126AA0[i] = (char *)(((u32)D_80126AA0[0]) + (i * 0x20));
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
    D_800DF460 = 0;
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

//Visual Aid : https://i.imgur.com/7T2Scdr.png
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
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 33, gMenuText[ASSET_MENU_TEXT_CONTPAK], ALIGN_MIDDLE_CENTER); //CONTROLLER PAK - Drop Shadow
        set_text_colour(255, 255, 255, 0, 255);
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 30, gMenuText[ASSET_MENU_TEXT_CONTPAK], ALIGN_MIDDLE_CENTER); //CONTROLLER PAK - Main Text

        yPos += 48;

        assign_dialogue_box_id(6);
        set_current_dialogue_box_coords(6, 58, yPos, 262, yPos + 30);

        if (D_800DF460 == -1) {
            set_current_dialogue_background_colour(6, 255, 255, 255, (alpha >> 1) + 128);
        } else {
            set_current_dialogue_background_colour(6, 96, 192, 92, 224);
        }

        set_dialogue_font(6, ASSET_FONTS_FUNFONT);
        set_current_text_colour(6, 255, 255, 255, 0, 255);
        set_current_text_background_colour(6, 0, 0, 0, 0);
        render_dialogue_text(6, POS_CENTRED, 2, gMenuText[86 + gMenuOption], 1, 4); //ASSET_MENU_TEXT_CONTPAK1 - CONTROLLER PAK 1 / 2 / 3 / 4
        render_dialogue_text(6, POS_CENTRED, 16, gMenuText[ASSET_MENU_TEXT_FREEPAGESX], sCurrentControllerPakFreeSpace, 4); //FREE PAGES: ~
        render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 6);

        yPos += 34; //To 82

        set_dialogue_font(6, ASSET_FONTS_SMALLFONT);
        set_current_text_background_colour(6, 0, 0, 0, 0);
        for (i = -1; i < sControllerPakMenuNumberOfRows; i++) {
            assign_dialogue_box_id(6);
            set_current_dialogue_box_coords(6, 28, yPos, 292, yPos + 14);
            if (i < 0) {
                //Red background for table header
                set_current_dialogue_background_colour(6, 224, 48, 48, 224);
                set_current_text_colour(6, 224, 224, 48, 255, 255);
                noteText = gMenuText[ASSET_MENU_TEXT_NOTE]; //NOTE
                fileNameText = gMenuText[ASSET_MENU_TEXT_FILENAME]; //FILENAME
                pagesText = gMenuText[ASSET_MENU_TEXT_PAGES]; //PAGES
                numberOfPages = 1;
            } else {
                if (D_800DF460 == (i + gOpacityDecayTimer)) {
                    //White background for currently selected row
                    set_current_dialogue_background_colour(6, 255, 255, 255, (alpha >> 1) + 128);
                } else {
                    //Yellow background for all other rows
                    set_current_dialogue_background_colour(6, 224, 224, 48, 224);
                }
                set_current_text_colour(6, 16, 16, 160, 255, 255);
                noteText = (char *)&D_800E820C; //~
                pagesText = (char *)&D_800E820C; //~
                fileNameText = D_80126AA0[gOpacityDecayTimer + i];
                numberOfPages = sCurrentControllerPakAllFileSizes[gOpacityDecayTimer + i];
            }
            render_dialogue_text(6, 26, 2, noteText, gOpacityDecayTimer + i + 1, 4);
            render_dialogue_text(6, 56, 2, fileNameText, 1, 0);
            render_dialogue_text(6, 240, 2, pagesText, numberOfPages, 4);
            render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 6);
            yPos += 16;
        }
        if (gOpacityDecayTimer < (16 - sControllerPakMenuNumberOfRows)) {
            if ((gOptionBlinkTimer & 8) != 0) {
                render_textured_rectangle(&sMenuCurrDisplayList, gMenuSelectionArrowDown, SCREEN_WIDTH_HALF, yPos + 8, 255, 255, 255, 255);
                reset_render_settings(&sMenuCurrDisplayList);
            }
        } else {
            set_text_font(ASSET_FONTS_FUNFONT);
            if (D_800DF460 == 16) {
                set_text_colour(255, 255, 255, alpha, 255);
            } else {
                set_text_colour(255, 255, 255, 0, 255);
            }
            draw_text(&sMenuCurrDisplayList, POS_CENTRED, yPos, gMenuText[ASSET_MENU_TEXT_EXIT], ALIGN_TOP_CENTER); //EXIT
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

                //Render these three lines in this order
                //ASSET_MENU_TEXT_DELETENOTEX  - DELETE NOTE ~ ?
                //ASSET_MENU_TEXT_DELETE       - DELETE
                //ASSET_MENU_TEXT_CANCELDELETE - CANCEL
                render_dialogue_text(6, POS_CENTRED, yPos, gMenuText[ASSET_MENU_TEXT_DELETENOTEX + i], D_800DF460 + 1, 4);

                if (i != 0) {
                    yPos += 16;
                } else {
                    yPos += 20;
                }
            }
            render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 6);
        }
        //Deleting File
        if (D_80126C10 != 0) {
            set_text_colour(255, 255, 255, 0, 255);
            set_text_font(ASSET_FONTS_BIGFONT);
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 128, gMenuText[ASSET_MENU_TEXT_PLEASEWAIT], ALIGN_MIDDLE_CENTER);
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
                play_sound_global(SOUND_SELECT2, NULL);
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
                        if (delete_file(gMenuOption, D_800DF460) != CONTROLLER_PAK_GOOD) {
                            //Failed to delete the file
                            playCancelSound = TRUE;
                            gMenuDelay = 1;
                            transition_begin(&sMenuTransitionFadeIn);
                        } else {
                            //File deleted successfully
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
            } else if ((pressedButtons & B_BUTTON) || (D_800DF460 == 16 && (pressedButtons & (A_BUTTON | START_BUTTON)))) {
                playCancelSound = 1;
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
            } else {
                //D_800DF460 = selected menu index?
                switch (D_800DF460) {
                case -1:
                    if (yStick < 0) {
                        if(!xStick){} // Fakematch
                        D_800DF460 = 0;
                        playMoveSound = TRUE;
                    }
                    break;
                case 16:
                    if (yStick > 0) {
                        D_800DF460 = 15;
                        playMoveSound = TRUE;
                    }
                    break;
                default:
                    if (pressedButtons & (A_BUTTON | START_BUTTON)) {
                        //Check if the selected menu item is a file or blank
                        if ((sCurrentControllerPakAllFileTypes[D_800DF460] >= 3) && (sCurrentControllerPakAllFileTypes[D_800DF460] <= 6)) {
                            D_80126C10 = 0;
                            gMenuOptionCount = 2;
                            playSelectedSound = TRUE;
                        } else {
                            //If it's not, just play the "back" sound
                            playCancelSound = TRUE;
                        }
                    } else {
                        if (yStick > 0) {
                            D_800DF460--;
                            if (D_800DF460 < 0) {
                                D_800DF460 = 0;
                            } else {
                                playMoveSound = TRUE;
                            }
                        } else if (yStick < 0) {
                            D_800DF460++;
                            playMoveSound = TRUE;
                        }
                    }
                    if (D_800DF460 >= (gOpacityDecayTimer + sControllerPakMenuNumberOfRows)) {
                        gOpacityDecayTimer = (D_800DF460 - sControllerPakMenuNumberOfRows) + 1;
                    }
                    if (D_800DF460 < gOpacityDecayTimer) {
                        gOpacityDecayTimer = D_800DF460;
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
            //Menu Cancel Sound
            play_sound_global(SOUND_MENU_BACK3, NULL);
        } else if (playSelectedSound) {
            //Menu Item Selected Sound
            play_sound_global(SOUND_SELECT2, NULL);
        } else if (playMoveSound) {
            //Menu Moving Sound
            play_sound_global(SOUND_MENU_PICK2, NULL);
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
    D_80126C58[0] = 0;
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

#ifdef NON_EQUIVALENT

// Close to matching, but should be functionally equivalent.
void render_magic_codes_ui(s32 arg0) {
    s32 xPos, yPos;
    s32 yIncr;
    s32 i, j;
    s32 temp, alpha, green;
    char c;

    set_text_background_colour(0, 0, 0, 0);
    render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 7);
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, gMenuText[ASSET_MENU_TEXT_MAGICCODES], ALIGN_MIDDLE_CENTER); //"MAGIC CODES"
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, gMenuText[ASSET_MENU_TEXT_MAGICCODES], ALIGN_MIDDLE_CENTER); //"MAGIC CODES"
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_colour(255, 255, 255, 0, 255);

    c = 'A';
    yPos = 60;
    // Draw the input table
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 7; j++) {
            xPos = 64 + (j * 32);
            if (gOptionsMenuItemIndex == 5 && j == gCheatInputCurrentColumn && i == gCheatInputCurrentRow) {
                temp = gOptionBlinkTimer * 8;
                if (temp >= 256) {
                    temp = 511 - temp;
                }
                set_text_colour(128, 255, 192, (temp >> 1) + 128, 255);
            }
            if (c < '[') {
                draw_text(&sMenuCurrDisplayList, xPos, yPos, &c, ALIGN_MIDDLE_CENTER); // Draw the character
            } else if (j == 5) {
                draw_text(&sMenuCurrDisplayList, xPos, yPos, &D_800E8210, ALIGN_MIDDLE_CENTER); // D_800E8210 = "DEL"
            } else {
                draw_text(&sMenuCurrDisplayList, xPos, yPos, &D_800E8214, ALIGN_MIDDLE_CENTER); // D_800E8214 = "OK"
            }
            if ((5 == gOptionsMenuItemIndex) && (j == gCheatInputCurrentColumn) && (i == gCheatInputCurrentRow)) {
                set_text_colour(255, 255, 255, 0, 255);
            }
            c++;
            c &= 0xFF;
        }
        yPos += 0x16;
    }

    temp = gOptionBlinkTimer * 8;
    if (temp >= 256) {
        temp = 511 - temp;
    }

    set_text_font(ASSET_FONTS_FUNFONT);
    yPos = 164;
    yIncr = 16;
    if (osTvType == TV_TYPE_PAL) {
        yIncr = 24;
    }

    for (i = 0; gMagicCodeMenuStrings[i] != NULL; i++) {
        alpha = 0;
        if (i == gOptionsMenuItemIndex && gMenuOptionCount == 0) {
            alpha = temp;
        }
        set_text_colour(255, 255, 255, alpha, 255);
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, yPos, gMagicCodeMenuStrings[i], ALIGN_MIDDLE_CENTER);
        yPos += yIncr;
    }
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_colour(255, 255, 128, 128, 255);
    set_text_background_colour(0, 0, 128, 128);
    if (gOptionsMenuItemIndex == 4) {
        if (D_80126C4C == -1) {
            draw_text(&sMenuCurrDisplayList, POS_CENTRED, 144, gMenuText[ASSET_MENU_TEXT_BADCODE], ALIGN_MIDDLE_CENTER); //"Sorry, the code was incorrect"
        } else {
            // Draw cheat code name.
            draw_text(&sMenuCurrDisplayList, POS_CENTRED, 144, (char *)(*gCheatsAssetData) + (*gCheatsAssetData + 1)[D_80126C4C + 1], ALIGN_MIDDLE_CENTER);
        }
    } else if (5 == gOptionsMenuItemIndex) {
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, 144, D_80126C58, ALIGN_MIDDLE_CENTER);
    } else if (gOptionsMenuItemIndex == 6) {
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, 144, gMenuText[ASSET_MENU_TEXT_ALLCODESDELETED], ALIGN_MIDDLE_CENTER); //"All cheats have been deleted"
    }
    if (gMenuOptionCount != 0) {
        yPos = SCREEN_HEIGHT_HALF;
        if (osTvType == TV_TYPE_PAL) {
            yPos = SCREEN_HEIGHT_HALF + 14;
        }
        assign_dialogue_box_id(6);
        set_dialogue_font(6, ASSET_FONTS_FUNFONT);
        set_current_dialogue_box_coords(6, 76, yPos - 28, 244, yPos + 28);
        set_current_dialogue_background_colour(6, 0, 0, 0, 160);
        yPos = 4;
        for (i = 0; i < 3; i++) {
            alpha = 0;
            green = 0xFF;
            if (i == 0) {
                alpha = 64;
                green = 0;
            } else if (i == gMenuOptionCount) {
                alpha = temp;
            }
            set_current_text_colour(6, 255, green, 255, alpha, 255);

            // gMenuText[148] = "CLEAR ALL CODES?", [149] = "OK", [150] = "CANCEL"
            render_dialogue_text(6, POS_CENTRED, yPos, gMenuText[148 + i], 1, 4);

            if (i != 0) {
                yPos += 16;
            } else {
                yPos += 20;
            }
        }
        render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 6);
    }
    if (get_filtered_cheats() & CHEAT_ROM_CHECKSUM) {
        calculate_and_display_rom_checksum();
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/render_magic_codes_ui.s")
#endif

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
        for(i = 0; i < MAXCONTROLLERS; i++) {
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
                D_80126C58[gCheatInputStringLength] = (gCheatInputCurrentRow * 7) + gCheatInputCurrentColumn + 65;
                gCheatInputStringLength++;
                D_80126C58[gCheatInputStringLength] = 0;
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
            play_sound_global(SOUND_BOUNCE, NULL);
            if (gCheatInputStringLength > 0) {
                gCheatInputStringLength--;
                D_80126C58[gCheatInputStringLength] = 0;
            }
        }
        if (someBool2) {
            playSelectSound = TRUE;
            if (gCheatInputStringLength == 0) {
                gOptionsMenuItemIndex = 0;
            } else {
                cheatDataEntries = &(*gCheatsAssetData)[1];
                D_80126C4C = 0; // Index into the gCheatsAssetData cheatsTable
                while((D_80126C4C < (gNumberOfCheats * 2)) && !foundCheat)  {
                    foundCheat = TRUE;
                    cheatCodeText = ((char *) (*gCheatsAssetData)) + cheatDataEntries[D_80126C4C];
                    // D_80126C58 = char *gPlayerEnteredCode; (Or something like that)
                    i = -1;
                    do {
                        i++;
                        if (cheatCodeText[i] != D_80126C58[i]) {
                            foundCheat = FALSE;
                        }
                        if(!foundCheat) { 
                            do { } while (0); // Fakematch
                            break;
                        }
                    } while(cheatCodeText[i] != '\0' && D_80126C58[i] != '\0');
                    if(foundCheat) continue;
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
                *D_80126C58 = 0;
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
        play_sound_global(SOUND_MENU_BACK3, NULL);
    } else if (playSelectSound) {
        play_sound_global(SOUND_SELECT2, NULL);
    } else if (playPickSound) {
        play_sound_global(SOUND_MENU_PICK2, NULL);
    }
    
    gIgnorePlayerInputTime = 0;
    if (gMenuDelay < -30 || gMenuDelay > 30) {
        unload_big_font_2();
        if (gMenuDelay < 0) {
            if (gActiveMagicCodes & CHEAT_DISPLAY_CREDITS) {
                func_80000B28();
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

#ifdef NON_EQUIVALENT

// Should be functionally equivalent
void render_magic_codes_list_menu_text(s32 arg0) {
    s32 numOfUnlockedCheats;
    s32 alpha;
    s32 phi_v0;
    s32 yPos;
    s32 i;

    set_text_background_colour(0, 0, 0, 0);
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, gMenuText[ASSET_MENU_TEXT_MAGICCODESLIST], ALIGN_MIDDLE_CENTER); // MAGIC CODES LIST
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, gMenuText[ASSET_MENU_TEXT_MAGICCODESLIST], ALIGN_MIDDLE_CENTER); // MAGIC CODES LIST
    numOfUnlockedCheats = 0;
    phi_v0 = 1;
    for (i = 0; i < 32; i++) {
        if (phi_v0 & gUnlockedMagicCodes) {
            D_80126C80[numOfUnlockedCheats] = i;
            numOfUnlockedCheats += 1;
        }
        phi_v0 <<= 1;
    }
    yPos = 54;
    alpha = gOptionBlinkTimer;
    alpha *= 8;
    if (alpha >= 256) {
        alpha = 511 - alpha;
    }
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_colour(255, 255, 255, 0, 255);
    for (i = gMenuOptionCount; (i < gMenuOptionCount + gNumOnscreenMagicCodes) && (i < numOfUnlockedCheats); i++) {
        if (i == gOptionsMenuItemIndex) {
            set_text_colour(255, 255, 255, alpha, 255);
        }
        draw_text(&sMenuCurrDisplayList, 48, yPos, (char *)(*gCheatsAssetData) + ((*gCheatsAssetData + 1)[D_80126C80[i] * 2 + 1]), ALIGN_TOP_LEFT);
        if ((1 << D_80126C80[i]) & gActiveMagicCodes) {
            draw_text(&sMenuCurrDisplayList, 256, yPos, gMenuText[ASSET_MENU_TEXT_ON], ALIGN_TOP_LEFT); // ON
        } else {
            draw_text(&sMenuCurrDisplayList, 256, yPos, gMenuText[ASSET_MENU_TEXT_OFF], ALIGN_TOP_LEFT); // OFF
        }
        if (i == gOptionsMenuItemIndex) {
            set_text_colour(255, 255, 255, 0, 255);
        }
        yPos += 16;
    }
    if (i < gMenuOptionCount + gNumOnscreenMagicCodes) {
        if (numOfUnlockedCheats == gOptionsMenuItemIndex) {
            set_text_colour(255, 255, 255, alpha, 255);
        }
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, yPos, gMenuText[ASSET_MENU_TEXT_RETURN], ALIGN_TOP_CENTER); // RETURN
        return;
    }
    if (gOptionBlinkTimer & 8) {
        render_textured_rectangle(&sMenuCurrDisplayList, &gMenuSelectionArrowDown, SCREEN_WIDTH_HALF, yPos + 8, 255, 255, 255, 255);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/render_magic_codes_list_menu_text.s")
#endif

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
        play_sound_global(SOUND_SELECT2, NULL);
        code = 1 << D_80126C80[gOptionsMenuItemIndex];
        gActiveMagicCodes ^= code;       // Toggle active cheats?
        func_8008A8F8(code, 0x10, 0x20); // func_8008A8F8() = Clear flags?
        func_8008A8F8(code, 0x20, 0x10);
        func_8008A8F8(code, 0x1000, 0x6080);
        func_8008A8F8(code, 0x6080, 0x1000);
        func_8008A8F8(code, 0x800, 0x1F8000);
        func_8008A8F8(code, 0x1F8000, 0x800);
        func_8008A8F8(code, 0x8000, 0xF0000);
        func_8008A8F8(code, 0x10000, 0xE8000);
        func_8008A8F8(code, 0x20000, 0xD8000);
        func_8008A8F8(code, 0x40000, 0xB8000);
        func_8008A8F8(code, 0x80000, 0x78000);
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
        play_sound_global(SOUND_MENU_PICK2, NULL);
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
        play_sound_global(SOUND_MENU_BACK3, NULL);
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
    static u32 cksum=0;
    static u32 calculated=0;
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

//These vars have to be defined after calculate_and_display_rom_checksum since that function has a static var in it.

s32 D_800E1E1C = 0;

s8 D_800E1E20[8] = {
    0, -1, 1, 0, 0, 1, -1, 0
};

s8 D_800E1E28 = 0;

// TT Game Status textures, think these are potentially multi-part images.
s16 D_800E1E2C[10] = {
    0x4C, 0x4D, 0x4E, 0x4F, 0x5B, 0x5C, 0x00, 0x42, -1, 0
};

// TT game status textures. And these maybe just standalone ones.
s16 D_800E1E40[10] = {
    0x0D, 0x0E, 0x0F, 0x10, 0x08, 0x09, 0x00, 0x0A, -1, 0
};

void func_8008AEB4(s32 arg0, s32 *arg1) {
    switch (arg0) {
        default:
            D_800DFFD0 = 0;
            return;
        case 1:
        case 3:
            D_800DFFD0 = 1;
            return;
        case 2:
            D_800DFFD0 = 2;
            D_800DFFD4 = *arg1;
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
            gCurrCharacterSelectData = (CharacterSelectData (*)[10]) &gCharacterSelectBytesComplete;
        } else {
            gCurrCharacterSelectData = (CharacterSelectData (*)[10]) &gCharacterSelectBytesDrumStick;
        }
    } else if (is_tt_unlocked()) {
        gCurrCharacterSelectData = (CharacterSelectData (*)[10]) &gCharacterSelectBytesTT;
    } else {
        gCurrCharacterSelectData = (CharacterSelectData (*)[10]) &gCharacterSelectBytesDefault;
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
    play_music(SEQUENCE_CHOOSE_YOUR_RACER);
    for (i = 0; i < NUM_CHARACTERS; i++) {
        channelVolumes = D_800DFDB4[i];
        if (i != gMenuCurrentCharacter.channelIndex) {
            func_80001114(channelVolumes[0]);
            func_80001114(channelVolumes[1]);
        }
    }
    func_80001114(6);
    func_80000B18();
    func_8009C674(D_800DFDC8);
    allocate_menu_images(D_800DFDCC);
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
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, gMenuText[ASSET_MENU_TEXT_PLAYERSELECT], ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 255, 255, 0, 255);
        // Draw "Player Select" text
        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, gMenuText[ASSET_MENU_TEXT_PLAYERSELECT], ALIGN_MIDDLE_CENTER);
        if (gNumberOfReadyPlayers == gNumberOfActivePlayers && gNumberOfActivePlayers > 0) {
            yPos = 208;
            if (osTvType == TV_TYPE_PAL) {
                yPos = 234;
            }
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yPos, (char *) D_800E8230 /* "OK?" */, ALIGN_MIDDLE_CENTER);
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

    for(i = 0; i < MAXCONTROLLERS; i++) {
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
                play_sound_global(SOUND_SELECT2, NULL);
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
        //Character Selected
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
        play_sound_global(((*gCurrCharacterSelectData)[gPlayersCharacterArray[characterSelected]].voiceID + SOUND_VOICE_CHARACTER_SELECTED), &D_80126808[characterSelected]);
        if ((gNumberOfActivePlayers > 2) || ((gNumberOfActivePlayers > 1) && !(gActiveMagicCodes & CHEAT_TWO_PLAYER_ADVENTURE)) || (D_800DFFD0 == 1)) {
            set_music_fade_timer(-128);
        }
    } else {
        //Character Deselected
        for (i = 0; i < ARRAY_COUNT(gActivePlayersArray); i++) {
            if (gActivePlayersArray[i] && D_801263DC[i] != 0) {
                if (D_801267D8[i] & B_BUTTON) {
                    D_801263DC[i] = 0;
                    gNumberOfReadyPlayers--;
                    if (D_80126808[i] != 0) {
                        func_8000488C(D_80126808[i]);
                    }
                    play_sound_global(((*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID + SOUND_VOICE_CHARACTER_DESELECTED), &D_80126808[i]);
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
                    play_sound_global(((*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID + SOUND_VOICE_CHARACTER_DESELECTED), &D_80126808[i]);
                }
            } else {
                if (D_801267D8[i] & B_BUTTON) {
                    gNumberOfActivePlayers--;
                    gActivePlayersArray[i] = 0;
                    if (gNumberOfActivePlayers > 0) {
                        if (gMenuSelectedCharacter.channelIndex == (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID) {
                            if (gMenuCurrentCharacter.unk1 <= 0) {
                                for (found = FALSE, j = 0; j < ARRAY_COUNT(gActivePlayersArray) && !found; j++) {
                                    if (gActivePlayersArray[j]) {
                                        found = TRUE;
                                        gMenuCurrentCharacter.channelIndex = (*gCurrCharacterSelectData)[gPlayersCharacterArray[j]].voiceID;
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
                    play_sound_global(((*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID + SOUND_VOICE_CHARACTER_SELECT), &D_80126808[i]);
                } else {
                    charSelectData = (*gCurrCharacterSelectData) + gPlayersCharacterArray[i];
                    if (D_80126830[i] > 0) {
                        func_8008BFE8(i, charSelectData->upInput, ARRAY_COUNT(charSelectData->upInput), SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    } else if (D_80126830[i] < 0) {
                        func_8008BFE8(i, charSelectData->downInput, ARRAY_COUNT(charSelectData->downInput), SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    } else if (D_80126818[i] < 0) {
                        func_8008BFE8(i, charSelectData->rightInput, ARRAY_COUNT(charSelectData->rightInput), SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    } else if (D_80126818[i] > 0) {
                        func_8008BFE8(i, charSelectData->leftInput, ARRAY_COUNT(charSelectData->leftInput), SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    }
                    if (charSelectData->voiceID != (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID) {
                        gMenuCurrentCharacter.channelIndex = (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID;
                        gMenuCurrentCharacter.unk2 = 0;
                        gMenuCurrentCharacter.unk1 = 20;
                    }
                }
            }
        }
    }
}

#ifdef NON_EQUIVALENT

// Should be functionally equivalent
void randomise_ai_racer_slots(s32 arg0) {
    s32 i, j;
    s32 numCharacters;
    s32 s1;

    numCharacters = 7;
    if (is_drumstick_unlocked()) {
        numCharacters = 8;
    }
    if (is_tt_unlocked()) {
        numCharacters++;
    }

    if (arg0 < 8) {
        s1 = FALSE;
        for (i = 0; (i < arg0) && (!s1); i++) {
            if (gCharacterIdSlots[i] == 9) {
                s1 = TRUE;
            }
        }
        if (!s1) {
            gCharacterIdSlots[arg0] = 9;
            arg0++;
        }
    }
    i = arg0;
    while (i < 8) {
        s1 = FALSE; // Check for duplicate racer id.
        gCharacterIdSlots[i] = (*gCurrCharacterSelectData)[get_random_number_from_range(0, numCharacters)].voiceID;
        for (j = 0; j < i; j++) {
            if (gCharacterIdSlots[i] == gCharacterIdSlots[j]) {
                s1 = TRUE; // Duplicate found!
            }
        }
        if (s1) {
            continue; // Redo if duplicate was found.
        }
        i++;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/randomise_ai_racer_slots.s")
#endif

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
        // THIS MUST BE ON ONE LINE!
        for (i = 0; i < ARRAY_COUNT(gActivePlayersArray); i++) { activePlayers[i] = gActivePlayersArray[i]; }
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
            if (D_800DFFD0 == 0) {
                phi_t3++;
                if ((gActiveMagicCodes << 7) < 0) {
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
                func_80000B18();
                load_level_for_menu(ASSET_LEVEL_OPTIONSBACKGROUND, -1, 0);
                if (gNumberOfActivePlayers == 1 && !gPlayerHasSeenCautionMenu) {
                    menu_init(MENU_CAUTION);
                } else {
                    menu_init(MENU_GAME_SELECT);
                }
            } else {
                func_80000B28();
                func_800828B8();
                init_racer_headers();
                menu_init(MENU_TRACK_SELECT);
            }
        }
    } else if (gMenuDelay < 0) {
        gMenuDelay -= updateRate;
        if (gMenuDelay < -30) {
            func_80000B28();
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
        play_sound_global(menuPickSoundId, NULL);
    } else {
        // menuPickFailedSoundId seems to always be passed SOUND_HORN_DRUMSTICK?
        play_sound_global(menuPickFailedSoundId, NULL);
    }
}

void func_8008C128(void) {
    func_8009C4A8(D_800DFDC8);
    set_free_queue_state(0);
    unload_font(ASSET_FONTS_BIGFONT);
    set_free_queue_state(2);
    D_800DFFD0 = 0;
}

void func_8008C168(s32 updateRate) {
    if (gMenuCurrentCharacter.unk1 > 0) {
        gMenuCurrentCharacter.unk1 = gMenuCurrentCharacter.unk1 - updateRate;
        if (gMenuCurrentCharacter.unk1 <= 0) {
            if (D_801263B8.channelIndex >= 0) {
                func_80001114(D_800DFDB4[D_801263B8.channelIndex][0]);
                func_80001114(D_800DFDB4[0][D_801263B8.channelIndex * 2 + 1]);
            }
            D_801263B8.channelIndex = gMenuSelectedCharacter.channelIndex;
            if (gMenuSelectedCharacter.channelIndex >= 0) {
                D_801263B8.unk2 = gMenuSelectedCharacter.unk2;
            }
            gMenuSelectedCharacter.channelIndex = gMenuCurrentCharacter.channelIndex;
            if (gMenuSelectedCharacter.channelIndex >= 0) {
                gMenuSelectedCharacter.unk2 = gMenuCurrentCharacter.unk2;
                func_80001170(D_800DFDB4[gMenuSelectedCharacter.channelIndex][0]);
                func_80001170(D_800DFDB4[0][gMenuSelectedCharacter.channelIndex * 2 + 1]);
            }
        }
    }
    if (gMenuSelectedCharacter.channelIndex >= 0) {
        gMenuSelectedCharacter.unk2 += updateRate * 4;
        if (gMenuSelectedCharacter.unk2 > 127) {
            gMenuSelectedCharacter.unk2 = 127;
        }
        func_80001268(D_800DFDB4[gMenuSelectedCharacter.channelIndex][0], gMenuSelectedCharacter.unk2);
        func_80001268(D_800DFDB4[0][gMenuSelectedCharacter.channelIndex * 2 + 1], gMenuSelectedCharacter.unk3);
    }
    if (D_801263B8.channelIndex >= 0) {
        D_801263B8.unk2 -= updateRate * 4;
        if (D_801263B8.channelIndex != gMenuSelectedCharacter.channelIndex) {
            if (D_801263B8.unk2 < 0) {
                func_80001114(D_800DFDB4[D_801263B8.channelIndex][0]);
                func_80001114(D_800DFDB4[0][D_801263B8.channelIndex * 2 + 1]);
            } else {
                func_80001268(D_800DFDB4[D_801263B8.channelIndex][0], D_801263B8.unk2);
                func_80001268(D_800DFDB4[0][D_801263B8.channelIndex * 2 + 1], D_801263B8.unk3);
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
    } else if (gIgnorePlayerInputTime <= 0 && (get_buttons_pressed_from_player(PLAYER_ONE) & (A_BUTTON | B_BUTTON | START_BUTTON))) {
        play_sound_global(SOUND_SELECT2, NULL);
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
    D_800DF460 = 0;
    gMenuOptionCount = 2;
    transition_begin(&sMenuTransitionFadeOut);
    mark_read_all_save_files();
    set_ghost_none();
    gOpacityDecayTimer = 1;
    func_8009C6D4(0x43);
    func_8007FFEC(3);
    load_font(ASSET_FONTS_BIGFONT);
    play_music(SEQUENCE_CHOOSE_YOUR_RACER);

    for (i = 0; i < NUM_CHARACTERS; i++) {
        if (i != gMenuSelectedCharacter.channelIndex) {
            func_80001114(D_800DFDB4[i][0]);
            func_80001114(D_800DFDB4[i][1]);
        }
    }

    func_80001114(6);
    func_80000B18();
    if (is_adventure_two_unlocked()) {
        gGameSelectElements = gGameSelectTextElemsWithAdv2;
        gMenuOptionCount = 2;
    } else {
        gGameSelectElements = gGameSelectTextElemsNoAdv2;
        gMenuOptionCount = 1;
    }

    for (i = 0; i <= gMenuOptionCount; i++) {
        //Fakematch? What's the (i ^ 0)?
        gGameSelectElements[((i ^ 0) * 2) + 2].unk14_a.texture = gMenuTextures[TEXTURE_SURFACE_BUTTON_WOOD];
    }
}

void func_8008C698(UNUSED s32 updateRate) {
    s32 i;
    s32 filterAlpha;
    s32 fade;

    if (gMenuDelay >= -21 && gMenuDelay < 22) {
        fade = gOptionBlinkTimer * 8;
        fade = fade;
        if (fade >= 0x100) {
            fade = 0x1FF - fade;
        }
        set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);

        for (i = 0; i <= gMenuOptionCount; i++) {
            filterAlpha = 0;
            if (i == D_800DF460) {
                filterAlpha = fade;
            }
            //Fakematch? What's the (i ^ 0)?
            gGameSelectElements[((i ^ 0) * 2) + 3].filterAlpha = filterAlpha;
        }

        if (osTvType == TV_TYPE_PAL) {
            D_800DF79C = 0xC;
            D_800DF7A0 = 0;
        } else {
            D_800DF79C = 0;
            D_800DF7A0 = 0;
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
        if (D_800DF460 == gMenuOptionCount) {
            func_80000B28();
            gIsInTracksMode = TRUE;
            init_racer_headers();
            load_level_for_menu((s32)SPECIAL_MAP_ID_NO_LEVEL, -1, 0);
            menu_init(MENU_TRACK_SELECT);
        } else {
            gIsInAdventureTwo = D_800DF460;
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
                if (D_800DF460 == gMenuOptionCount) {
                    set_music_fade_timer(-0x80);
                }
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = 1;
                play_sound_global(SOUND_SELECT2, NULL);
            } else if (playerInputs & B_BUTTON) {
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = -1;
            } else {
                if (playerYDir < 0) {
                    if (D_800DF460 < gMenuOptionCount) {
                        D_800DF460++;
                        play_sound_global(SOUND_MENU_PICK2, NULL);
                    }
                }
                if (playerYDir > 0) {
                    if (D_800DF460 > 0) {
                        D_800DF460--;
                        play_sound_global(SOUND_MENU_PICK2, NULL);
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
    func_8009C674(D_800E0398);
    allocate_menu_images(D_800E03A4);
    func_8007FFEC(6);
    mark_read_all_save_files();
    gOpacityDecayTimer = 1;
    gSaveFileIndex = 0;
    gMenuDelay = 0;
    gMenuOptionCount = 0;
    gOptionBlinkTimer = 0;
    D_80126484 = FALSE;
    D_80126488 = FALSE;
    D_80126CC0 = 0;
    transition_begin(&sMenuTransitionFadeOut);
    load_font(ASSET_FONTS_BIGFONT);
    play_music(SEQUENCE_CHOOSE_YOUR_RACER);
    for (i = 0; i < NUM_CHARACTERS; i++) {
        if (i != gMenuSelectedCharacter.channelIndex) {
            func_80001114(D_800DFDB4[i][0]);
            func_80001114(D_800DFDB4[i][1]);
        }
    }
    func_80001114(6);
    func_80000B18();
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

#ifdef NON_EQUIVALENT
// Shouldn't have any major issues.
void render_file_select_menu(UNUSED s32 updateRate) {
    s32 s2;
    s32 s5;
    s32 y;
    s32 phi_v0_2;
    u8 tempName[8];
    u32 color;
    s32 i;

    if (osTvType == TV_TYPE_PAL) {
        y = 12;
    } else {
        y = 0;
    }

    func_8009BD5C();
    set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    for (i = 0; i < 3; i++) { // 3 files
        if (gSavefileInfo[i].isAdventure2 == gIsInAdventureTwo || gSavefileInfo[i].isStarted == 0) {
            color = COLOUR_RGBA32(176, 224, 192, 255);
        } else {
            color = COLOUR_RGBA32(106, 144, 115, 255);
        }
        func_80080580(NULL, gFileSelectButtons[i].x - 160, 120 - gFileSelectButtons[i].y, gFileSelectButtons[i].width,
            gFileSelectButtons[i].height, gFileSelectButtons[i].borderWidth, gFileSelectButtons[i].borderHeight, color, gMenuTextures[TEXTURE_SURFACE_BUTTON_WOOD]);
    }
    func_80080BC8(&sMenuCurrDisplayList);
    if (gOpacityDecayTimer == 0) {
        set_text_font(ASSET_FONTS_BIGFONT);
        set_text_background_colour(0, 0, 0, 0);
        s5 = 10;
        for (i = 0; i < 3; i++) {
            if (gSavefileInfo[i].isStarted != 0) {
                s2 = 0xB;
                func_8007BF1C(FALSE);
                if (gSavefileInfo[i].isAdventure2 != 0) {
                    s2 = 0xC;
                }
                render_menu_image(s2, gFileSelectElementPos[2] + gFileSelectButtons[i].x, gFileSelectElementPos[3] + gFileSelectButtons[i].y, 0, 0, 0, 128);
                func_80068508(1);
                gMenuImageStack->unk18 = gSavefileInfo[i].balloonCount / s5;
                render_menu_image(0, (gFileSelectElementPos[6] + gFileSelectButtons[i].x) - 6, gFileSelectElementPos[7] + gFileSelectButtons[i].y, 0, 0, 0, 128);
                gMenuImageStack->unk18 = gSavefileInfo[i].balloonCount % s5;
                render_menu_image(0, gFileSelectElementPos[6] + gFileSelectButtons[i].x + 6, gFileSelectElementPos[7] + gFileSelectButtons[i].y, 0, 0, 0, 128);
                func_80068508(0);
                sMenuGuiColourG = 64;
                sMenuGuiColourB = 64;
                render_menu_image(s5, gFileSelectElementPos[8] + gFileSelectButtons[i].x, gFileSelectElementPos[9] + gFileSelectButtons[i].y, 0, 0, 0, 128);
                sMenuGuiColourG = 255;
                sMenuGuiColourB = 255;
                func_8007BF1C(TRUE);
            } else {
                set_text_colour(255, 255, 255, 64, 255);
                draw_text(&sMenuCurrDisplayList, gFileSelectElementPos[4] + gFileSelectButtons[i].x, gFileSelectElementPos[5] + gFileSelectButtons[i].y + y, gMenuText[ASSET_MENU_TEXT_NEW], ALIGN_MIDDLE_CENTER);
            }
        }
    }
    phi_v0_2 = gOptionBlinkTimer * 8;
    if (phi_v0_2 >= 0x100) {
        phi_v0_2 = 0x1FF - phi_v0_2;
    }
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_background_colour(0, 0, 0, 0);
    set_text_colour(255, 255, 255, 0, 255);
    for (i = 0; i < 3; i++) {
        s2 = FALSE;
        if (D_80126484 != FALSE) {
            if (D_80126494 == 0 && i == gSaveFileIndex3) {
                s2 = TRUE;
            } else if (D_80126494 > 0 && i == gSaveFileIndex2) {
                s2 = TRUE;
            }
        } else if (D_80126488 != FALSE && i == gSaveFileIndex3) {
            s2 = TRUE;
        } else if (gMenuOptionCount == 0 && i == gSaveFileIndex) {
            s2 = TRUE;
        }
        if (s2) {
            s32 temp_t0 = phi_v0_2 | ~0xFF;
            func_80080E90(&sMenuCurrDisplayList, gFileSelectButtons[i].x, gFileSelectButtons[i].y + y, gFileSelectButtons[i].width, gFileSelectButtons[i].height,
                gFileSelectButtons[i].borderWidth, gFileSelectButtons[i].borderHeight, temp_t0, temp_t0, temp_t0, temp_t0);
        }
        if (D_80126CC0 == 0 || i != gSaveFileIndex) {
            trim_filename_string(gSavefileInfo[i].name, tempName);
            if (gSavefileInfo[i].isStarted == 0) {
                trim_filename_string(gFilenames[i], tempName);
            }
            if (tempName != NULL) {
                draw_text(&sMenuCurrDisplayList, gFileSelectElementPos[0] + gFileSelectButtons[i].x, gFileSelectElementPos[1] + gFileSelectButtons[i].y + y, tempName, ALIGN_MIDDLE_CENTER);
            }
        }
    }
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 19, gMenuText[ASSET_MENU_TEXT_GAMESELECT], ALIGN_TOP_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 16, gMenuText[ASSET_MENU_TEXT_GAMESELECT], ALIGN_TOP_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    y += 0xBB;
    if (D_80126484 != FALSE) {
        if (D_80126494 == 0) {
            set_text_font(ASSET_FONTS_FUNFONT);
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, y, gMenuText[ASSET_MENU_TEXT_GAMETOCOPY], ALIGN_MIDDLE_CENTER);
        } else if (D_80126494 == 1) {
            set_text_font(ASSET_FONTS_FUNFONT);
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, y, gMenuText[ASSET_MENU_TEXT_GAMETOCOPYTO], ALIGN_MIDDLE_CENTER);
        } else {
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, y, &D_800E8234, ALIGN_MIDDLE_CENTER);
        }
        return;
    }
    if (D_80126488 != FALSE) {
        if (D_80126494 == 0) {
            set_text_font(ASSET_FONTS_FUNFONT);
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, y, gMenuText[ASSET_MENU_TEXT_GAMETOERASE], ALIGN_MIDDLE_CENTER);
        } else {
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, y, &D_800E8238, ALIGN_MIDDLE_CENTER);
        }
        return;
    }
    if (D_80126CC0 == 0) {
        if (gMenuOptionCount == 1) {
            set_text_colour(255, 255, 255, phi_v0_2, 255);
        }
        draw_text(&sMenuCurrDisplayList, 90, y, gMenuText[ASSET_MENU_TEXT_COPY], ALIGN_MIDDLE_CENTER);
        if (gMenuOptionCount == 2) {
            set_text_colour(255, 255, 255, phi_v0_2, 255);
        } else {
            set_text_colour(255, 255, 255, 0, 255);
        }
        draw_text(&sMenuCurrDisplayList, 230, y, gMenuText[ASSET_MENU_TEXT_ERASE], ALIGN_MIDDLE_CENTER);
        return;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/render_file_select_menu.s")
#endif

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
                        play_sound_global(SOUND_HORN_DRUMSTICK, NULL);
                        break;
                    }
                }
                play_sound_global(SOUND_SELECT2, NULL);
                return 1;
            case 1:
                play_sound_global(SOUND_SELECT2, NULL);
                gSaveFileIndex3 = gSaveFileIndex;
                D_80126484 = TRUE;
                D_80126494 = 0;
                return 0;
            case 2:
                play_sound_global(SOUND_SELECT2, NULL);
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
        play_sound_global(SOUND_MENU_PICK2, NULL);
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
            play_sound_global(SOUND_MENU_BACK3, NULL);
            D_80126484 = FALSE;
            return;
        }
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            if (gSavefileInfo[gSaveFileIndex3].isStarted) {
                play_sound_global(SOUND_SELECT2, NULL);
                mark_read_save_file(gSaveFileIndex3);
                gSaveFileIndex2 = gSaveFileIndex3;
                D_80126494 = 1;
                return;
            }
            play_sound_global(SOUND_MENU_BACK3, NULL);
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
            play_sound_global(SOUND_MENU_PICK2, NULL);
        }
    } else if (D_80126494 == 1) {
        if (buttonsPressed & B_BUTTON) {
            play_sound_global(SOUND_MENU_BACK3, NULL);
            gSaveFileIndex3 = gSaveFileIndex2;
            D_80126494 = 0;
            return;
        }
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            if (!gSavefileInfo[gSaveFileIndex2].isStarted) {
                play_sound_global(SOUND_SELECT2, NULL);
                D_80126494 = 2;
                return;
            }
            play_sound_global(SOUND_MENU_BACK3, NULL);
            return;
        }
        prevValue = gSaveFileIndex2;
        if ((xAxisDirection < 0) && (gSaveFileIndex2 > 0)) {
            gSaveFileIndex2--;
        }
        if ((xAxisDirection > 0) && (gSaveFileIndex2 < 2)) {
            gSaveFileIndex2++;
        }
        if (prevValue != gSaveFileIndex2) {
            play_sound_global(SOUND_MENU_PICK2, NULL);
        }
    } else {
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            play_sound_global(SOUND_SELECT2, NULL);
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
            return;
        }
        if (buttonsPressed & B_BUTTON) {
            play_sound_global(SOUND_MENU_BACK3, NULL);
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
        buttonsPressed |= get_buttons_pressed_from_player(1);
        controllerXAxisDirection += gControllersXAxisDirection[1];
    }

    if (D_80126494 == 0) {
        if (buttonsPressed & B_BUTTON) {
            play_sound_global(SOUND_MENU_BACK3, NULL);
            D_80126488 = FALSE;
            return;
        } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            if (gSavefileInfo[gSaveFileIndex3].isStarted != 0) {
                play_sound_global(SOUND_SELECT2, NULL);
                D_80126494 = 1;
                return;
            }
            play_sound_global(SOUND_MENU_BACK3, NULL);
            return;
        }

        temp = gSaveFileIndex3;

        //Left
        if (controllerXAxisDirection < 0) {
            if (gSaveFileIndex3 > 0) {
                gSaveFileIndex3--;
            }
        }

        //Right
        if (controllerXAxisDirection > 0) {
            if (gSaveFileIndex3 < 2) {
                gSaveFileIndex3++;
            }
        }

        if (gSaveFileIndex3 != temp) {
            play_sound_global(SOUND_MENU_PICK2, NULL);
        }
    } else {
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            play_sound_global(SOUND_SELECT2, NULL);
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
            play_sound_global(SOUND_MENU_BACK3, NULL);
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
            for (i = 0; i < 3; i++) {
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
        } else if (D_80126CC0 != 0) {
            buttonsPressed = get_buttons_pressed_from_player(PLAYER_ONE);
            if ((buttonsPressed & B_BUTTON) && (D_800E0FA0 == 0)) {
                unload_big_font_4();
                D_80126CC0 = 0;
                gSavefileInfo[i].name[0] = 'D';
                gSavefileInfo[i].name[1] = 'K';
                gSavefileInfo[i].name[2] = 'R';
                gSavefileInfo[i].name[3] = '\0';
            } else if (menu_enter_filename_loop(updateRate) != 0) {
                unload_big_font_4();
                D_80126CC0 = 0;
                gSavefileInfo[gSaveFileIndex].isAdventure2 = 0;
                if (gIsInAdventureTwo != 0) {
                    gSavefileInfo[gSaveFileIndex].isAdventure2 = 1;
                }
                gSavefileInfo[gSaveFileIndex].isStarted = 1;
                gSavefileInfo[gSaveFileIndex].balloonCount = 0;
                settings->filename = compress_filename_string(gSavefileInfo[gSaveFileIndex].name, 3);
                mark_read_save_file(gSaveFileIndex);
                set_music_fade_timer(-128);
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = 1;
            }
        } else {
            currentMenuDelay = func_8008D5F8(updateRate);
            if (currentMenuDelay != 0) {
                if (currentMenuDelay > 0) {
                    if (gSavefileInfo[gSaveFileIndex].isStarted != 0) {
                        play_sound_global(SOUND_SELECT2, NULL);
                        mark_read_save_file(gSaveFileIndex);
                        set_music_fade_timer(-128);
                    } else {
                        D_80126CC0 = 1;
                        D_800E0FB0 = 0;
                        i = 0;
                        if (osTvType == TV_TYPE_PAL) {
                            i = 12;
                        }
                        func_80097874(i + 187, gFileSelectButtons[gSaveFileIndex].x + gFileSelectElementPos[0],
                            gFileSelectButtons[gSaveFileIndex].y + gFileSelectElementPos[1] + i, 0, &D_800E0FB0, gSavefileInfo[gSaveFileIndex].name, 3);
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
        func_80000B28();
        init_racer_headers();
        gTrophyRaceWorldId = 0;
        if (settings->newGame) {
            if (gIsInAdventureTwo) {
                settings->cutsceneFlags |= CUTSCENE_ADVENTURE_TWO;
            }
            func_8009ABD8((s8 *)get_misc_asset(MISC_ASSET_UNK19), 0, gNumberOfActivePlayers, 0, 0, NULL);
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
    }
    else {
        return MENU_RESULT_CONTINUE;
    }
}

void func_8008E428(void) {
    func_8009C4A8(D_800E0398);
    func_8007FF88();
    unload_font(ASSET_FONTS_BIGFONT);
}

/**
 * Set the texture IDs of the vehicle ID elements.
*/
void assign_vehicle_icon_textures(void) {
    gRaceSelectionCarTex[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_CAR_TOP];
    gRaceSelectionCarTex[1].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_CAR_BOTTOM];
    gRaceSelectionHoverTex[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_HOVERCRAFT_TOP];
    gRaceSelectionHoverTex[1].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_HOVERCRAFT_BOTTOM];
    gRaceSelectionPlaneTex[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_PLANE_TOP];
    gRaceSelectionPlaneTex[1].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_PLANE_BOTTOM];
}

/**
 * Set the texture IDs of the menu arrow elements.
*/
void assign_menu_arrow_textures(void) {
    gMenuSelectionArrowUp[0].texture = gMenuTextures[TEXTURE_ICON_ARROW_UP];
    gMenuSelectionArrowLeft[0].texture = gMenuTextures[TEXTURE_ICON_ARROW_LEFT];
    gMenuSelectionArrowDown[0].texture = gMenuTextures[TEXTURE_ICON_ARROW_DOWN];
    gMenuSelectionArrowRight[0].texture = gMenuTextures[TEXTURE_ICON_ARROW_RIGHT];
}

GLOBAL_ASM("asm/non_matchings/menu/func_8008E4EC.s")

UNUSED s32 func_8008E790(void) {
    return D_800E097C;
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
    trackMenuIds = (s8 **)get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    if (D_800DF488 != 0) {
        D_801269C8 = 0;
        D_801269CC = 0;
        D_800E0414 = 0;
        D_800E0418 = 0;
        D_800DF488 = 0;
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
        temp_a0 = D_800E0710[(var_a1 * 3)];
        var_s0 = (TextureHeader **) D_800E0730[var_a1];
        if (temp_a0 != -1) {
            func_8009C6D4(temp_a0);
            var_s0[0] = gMenuTextures[D_800E0710[(var_a1 * 3)]];
        } else {
            var_s0[0] = NULL;
        }
        temp_a0_2 = D_800E0710[(var_a1 * 3) + 1];
        if (temp_a0_2 != -1) {
            func_8009C6D4(temp_a0_2);
            var_s0[1] = (TextureHeader *) gMenuTextures[D_800E0710[(var_a1 * 3)]];
        } else {
            var_s0[1] = NULL;
        }
    }
    D_800E0970 = (unk800E0970 *) allocate_from_main_pool_safe(2880, COLOUR_TAG_YELLOW);
    D_800E0974 = (s32) (&D_800E0970[40]); //640 bytes forward
    D_800E096C = (s32) (&D_800E0970[80]); //1280 bytes forward
    //D_800E096C = (s32) (&D_800E0968[80]); //800 bytes past D_800E0968
    var_a0 = -160;
    var_v0 = 0;
    for (var_v0 = 0; var_v0 < 80; var_v0++) {
        D_800E0968[var_v0].x = var_a0;
        var_a0 = -var_a0;
        D_800E0968[var_v0].z = -1024;
        D_800E0968[var_v0].r = 0xFF;
        D_800E0968[var_v0].g = 0xFF;
        D_800E0968[var_v0].b = 0xFF;
    }
    for (var_v0 = 0; var_v0 < 40; var_v0++) {
        D_800E0970[var_v0].unk0 = 0x40;
        D_800E0970[var_v0].unk1 = 0;
        D_800E0970[var_v0].unk2 = 2;
        D_800E0970[var_v0].unk3 = 1;
    }
    D_80126924 = 0;
    set_background_draw_function(func_8008F618);
    resize_viewport(0, 80, gTrackSelectViewPortHalfY - (gTrackSelectViewPortHalfY >> 1), 240, (gTrackSelectViewPortHalfY >> 1) + gTrackSelectViewPortHalfY);
    copy_viewports_to_stack();
    camEnableUserView(0, 0);
    D_800E097C = 1;
    func_8009C674(D_800E07C4);
    allocate_menu_images(D_800E07E0);
    assign_menu_arrow_textures();

    D_800E05D4[0].texture = gMenuTextures[TEXTURE_UNK_08];
    D_800E05D4[1].texture = gMenuTextures[TEXTURE_UNK_09];
    D_800E05D4[2].texture = gMenuTextures[TEXTURE_UNK_0A];
    D_800E05F4[0].texture = gMenuTextures[TEXTURE_UNK_0B];
    D_800E05F4[1].texture = gMenuTextures[TEXTURE_UNK_0C];
    D_800E05F4[2].texture = gMenuTextures[TEXTURE_UNK_0D];

    for (idx = 0; idx < 4; idx++) {
        var_s2 = D_801268E8[idx];
        for (idx2 = 0; idx2 < 6; idx2++) {
            *var_s2 = -1;
            if (idx2 == 0) {
                if (idx < 4) {
                    *var_s2 = trackMenuIds[idx][idx2];
                }
            }
            else if (idx2 < 4) {
                if ((trackMenuIds[idx][idx2] != -1) && (settings->courseFlagsPtr[trackMenuIds[idx][idx2]] & 1)) {
                    *var_s2 = trackMenuIds[idx][idx2];
                }
            } else if (idx2 == 4) {
                var_a1_2 = 0;
                // This is almost definitely wrong.
                for (var_a0_2 = 0; var_a0_2 < 2; var_a0_2++) {
                    if ((trackMenuIds[idx][var_a0_2] != -1) && ((settings->courseFlagsPtr[trackMenuIds[idx][var_a0_2]] & 6) == 6)) {
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
    set_music_player_voice_limit(24);
    func_80000C1C();
    play_music(SEQUENCE_MAIN_MENU);
    set_relative_volume_for_music(sMenuMusicVolume);
    func_80000B18();
    set_D_800DD430(1); // Set an interrupt?
    gIsInAdventureTwo = D_800E0418;
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
        func_8009C4A8(D_800E07E8);
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
                func_8009C674(D_800E07E8);
                allocate_menu_images(D_800E0830);
                assign_vehicle_icon_textures();
                gRaceSelectionTTOn[0].texture = gMenuTextures[TEXTURE_ICON_TIMETRIAL_ON_TOP];
                gRaceSelectionTTOn[1].texture = gMenuTextures[TEXTURE_ICON_TIMETRIAL_ON_BOTTOM];
                gRaceSelectionTTOff[0].texture = gMenuTextures[TEXTURE_ICON_TIMETRIAL_OFF_TOP];
                gRaceSelectionTTOff[1].texture = gMenuTextures[TEXTURE_ICON_TIMETRIAL_OFF_BOTTOM];
                gRaceSelectionCarOptHighlight[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_CAR_HIGHLIGHT];
                gRaceSelectionCarOpt[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_CAR];
                gRaceSelectionHoverOptHighlight[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT_HIGHLIGHT];
                gRaceSelectionHoverOpt[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT];
                gRaceSelectionPlaneOptHighlight[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_PLANE_HIGHLIGHT];
                gRaceSelectionPlaneOpt[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_PLANE];
                gRaceSelectionTTOnOptHighlight[0].texture = gMenuTextures[TEXTURE_ICON_TIMETRIAL_OPT_ON];
                gRaceSelectionTTOffOptHighlight[0].texture = gMenuTextures[TEXTURE_ICON_TIMETRIAL_OPT_ON_HIGHLIGHT];
                gRaceSelectionTTOnOpt[0].texture = gMenuTextures[TEXTURE_ICON_TIMETRIAL_OPT_OFF];
                gRaceSelectionTTOffOpt[0].texture = gMenuTextures[TEXTURE_ICON_TIMETRIAL_OPT_OFF_HIGHLIGHT];
                gRaceSelectionPlayer1Texture[0].texture = gMenuTextures[TEXTURE_ICON_PLAYER_1];
                gRaceSelectionPlayer2Texture[0].texture = gMenuTextures[TEXTURE_ICON_PLAYER_2];
                gRaceSelectionPlayer3Texture[0].texture = gMenuTextures[TEXTURE_ICON_PLAYER_3];
                gRaceSelectionPlayer4Texture[0].texture = gMenuTextures[TEXTURE_ICON_PLAYER_4];
                gRaceSelectionVehicleTitleTexture[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_TITLE];
                gRaceSelectionTTTitleTexture[0].texture = gMenuTextures[TEXTURE_ICON_TT_TITLE];
                gRaceSelectionTTTexture[0].texture = gMenuTextures[TEXTURE_ICON_TT_HEAD];
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
        set_relative_volume_for_music(0);
    } else {
        sMenuMusicVolume += updateRate * 2;
        if (sMenuMusicVolume >= 81) {
            sMenuMusicVolume = 80;
        }
        set_relative_volume_for_music((u8)sMenuMusicVolume);
    }
    if (D_801267D0 < 0) {
        func_8008F534();
        D_800DF478 = 0;
        if (gNumberOfActivePlayers >= 3 || (gNumberOfActivePlayers == 2 && (gActiveMagicCodes << 7) >= 0)) {
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
            D_800DF478 = 1;
            return gNumberOfActivePlayers;
        }
        gTrophyRaceWorldId = D_801269CC + 1;
        D_800DF450 = 0;
        gTrophyRaceRound = 0;
        menu_init(MENU_TROPHY_RACE_ROUND);
        return MENU_RESULT_CONTINUE;
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}

void func_8008F534(void) {
    s32 i;

    camDisableUserView(0, 0);
    func_8009C4A8(D_800E07C4);
    set_free_queue_state(0);
    free_from_memory_pool(D_800E0970);
    set_free_queue_state(2);
    for (i = 0; i < 15; i += 3) {
        if (D_800E0710[i] != -1) {
            func_8009C508(D_800E0710[i]);
        }
        if (D_800E0710[i + 1] != -1) {
            func_8009C508(D_800E0710[i + 1]);
        }
    }
    unload_font(ASSET_FONTS_BIGFONT);
    func_8007FF88();
    func_80000B28();
    func_80000C2C();
    func_80001844();
    set_D_800DD430(0);
}

//https://decomp.me/scratch/ubeU1
GLOBAL_ASM("asm/non_matchings/menu/func_8008F618.s")
GLOBAL_ASM("asm/non_matchings/menu/renderTrackSelect.s")

#ifdef NON_EQUIVALENT
void func_8008FF1C(s32 updateRate) {
    s32 yOffset;
    s32 xOffset;
    s32 pad;
    s32 trackSelectY;
    s32 trackSelectX;
    s32 trackX;
    s32 temp_s1;
    s32 maxTrackY;
    s8 *trackMenuIds;
    Settings *settings;
    s32 temp_t7;
    TrackRenderDetails *curr;
    s32 new_var;
    s32 trackSelected;
    char *hubName;

    settings = get_settings();
    trackMenuIds = (s8 *)get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    if ((gMenuDelay > -23) && (gMenuDelay < 23)) {
        maxTrackY = (gFFLUnlocked == -1) ? 3 : 4;
        trackSelectX = (gTrackSelectX / X_TILE_SIZE);
        temp_s1 = (gTrackSelectY / -gTrackSelectViewportY);
        trackSelectY = temp_s1 - 1;
        new_var = -1;
        for (yOffset = new_var, curr = gTrackSelectRenderDetails; yOffset < 2; yOffset++) {
            for (xOffset = new_var; xOffset < 2; xOffset++) {
                trackX = trackSelectX + xOffset;
                if ((trackSelectY < 0) || (trackSelectY > maxTrackY) || (trackX < 0) || (trackX >= 6)) {
                    curr->visible = 0;
                } else {
                    curr->visible = 1;
                    hubName = get_level_name(get_hub_area_id(trackSelectY + 1));
                    trackSelected = D_801268E8[trackSelectY][trackX];
                    curr->hubName = hubName;
                    if (trackSelected != -1) {
                        curr->trackName = get_level_name(trackMenuIds[(trackSelectY * 6) + trackX]);
                        if (trackX == 4) {
                            if (((settings->trophies >> (trackSelectY * 2)) & 3) == 3) {
                                curr->visible = 2;
                            }
                        } else if (settings->courseFlagsPtr[trackMenuIds[(trackSelectY * 6) + trackX]] & 2) {
                            curr->visible = 2;
                        }
                    } else {
                        curr->trackName = (char *) gQMarkPtr;
                    }
                    curr->xOff = ((trackX * X_TILE_SIZE) - gTrackSelectX);
                    curr->yOff = ((-trackSelectY * gTrackSelectViewportY) - gTrackSelectY);
                    curr->opacity = 0xFF;
                    if ((trackX == gSelectedTrackX) && (trackSelectY == gSelectedTrackY)) {
                        curr->copyViewPort |= 0x80;
                        if (gOpacityDecayTimer < 32) {
                            curr->opacity = gOpacityDecayTimer * 8;
                        }
                    } else {
                        curr->copyViewPort &= 0xFF7F;
                    }
                    temp_t7 = curr->copyViewPort & 0xFF80;
                    curr->copyViewPort = temp_t7;
                    if (gMenuDelay == 0) {
                        if (trackSelectY > 0) {
                            curr->copyViewPort = ((temp_t7 | 1) & 0x7F) | (temp_t7 & 0xFF80);
                        }
                        if (trackX < 5) {
                            curr->copyViewPort = ((curr->copyViewPort | 2) & 0x7F) | (curr->copyViewPort & 0xFF80);
                        }
                        if (trackSelectY < maxTrackY) {
                            curr->copyViewPort = ((curr->copyViewPort | 4) & 0x7F) | (curr->copyViewPort & 0xFF80);
                        }
                        if (trackX > 0) {
                            curr->copyViewPort = ((curr->copyViewPort | 8) & 0x7F) | (curr->copyViewPort & 0xFF80);
                        }
                        if ((trackX == 4) && (trackSelectY == 4)) {
                            curr->copyViewPort = (curr->copyViewPort & 0x7D) | (curr->copyViewPort & 0xFF80);
                        }
                        if ((trackX == 5) && (trackSelectY == 3)) {
                            curr->copyViewPort = (curr->copyViewPort & 0x7B) | (curr->copyViewPort & 0xFF80);
                        }
                    }
                    if (trackX == 4) {
                        curr->border = 6;
                    } else if (trackX == 5) {
                        curr->border = 5;
                    } else {
                        curr->border = 4;
                    }
                }
                curr++;
            }
            trackSelectY++;
        }
        camDisableUserView(0, 1);
        func_8009BD5C();
        set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
        reset_render_settings(&sMenuCurrDisplayList);
        gDPPipeSync(sMenuCurrDisplayList++);
        D_80126928 = 64;
        D_8012692C = 32;
        D_801269F0 = 0;

        for (yOffset = 0; yOffset < ARRAY_COUNT(gTrackSelectRenderDetails); yOffset++) {
            if (gTrackSelectRenderDetails[yOffset].visible != 0) {
                renderTrackSelect(
                    gTrackSelectRenderDetails[yOffset].xOff,
                    gTrackSelectRenderDetails[yOffset].yOff,
                    gTrackSelectRenderDetails[yOffset].hubName,
                    gTrackSelectRenderDetails[yOffset].trackName,
                    gTrackSelectRenderDetails[yOffset].opacity,
                    gTrackSelectRenderDetails[yOffset].border,
                    ((u32)gTrackSelectRenderDetails[yOffset].viewPort) >> 0xF,
                    (gTrackSelectRenderDetails[yOffset].visible == 1) ? D_800E05D4 : D_800E05F4,
                    gTrackSelectRenderDetails[yOffset].copyViewPort & 0x7F
                );
            }
        }
        D_80126924 = 1 - D_80126924;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_8008FF1C.s")
#endif

GLOBAL_ASM("asm/non_matchings/menu/func_800904E8.s")

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
        if ((D_801269E8 - gTrackSelectX > 4.0f) || (D_801269E8 - gTrackSelectX < -4.0f) || ((D_801269EC - gTrackSelectY > 4.0f)) || (D_801269EC - gTrackSelectY < -4.0f)) {
            gMenuDelay = 1;
        } else if (D_800E1E1C) {
            play_sound_global(SOUND_SELECT2, NULL);
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
        resize_viewport(0, (var_t2 - (var_t1 * 4)) - 80, var_a2, (var_t1 * 4) + var_t2 + 80, var_t3);
        gMenuImageStack[4].unk8 = (f32) (sMenuImageProperties[4].unk8 * (1.0f + ((f32) var_t1 / 20.0f)));
        gMenuImageStack[6].unk8 = (f32) (sMenuImageProperties[6].unk8 * (1.0f + ((f32) var_t1 / 20.0f)));
        gMenuImageStack[5].unk8 = (f32) (sMenuImageProperties[5].unk8 * (1.0f + ((f32) var_t1 / 20.0f)));
    }
    camEnableUserView(0, 0);
    if (get_thread30_level_id_to_load() == 0) {
        if (gMenuDelay < 0) {
            sMenuMusicVolume -= updateRate * 4;
        }
        if ((gSelectedTrackX == D_801269C8) && (gSelectedTrackY == D_801269CC)) {
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
            D_800E097C = 0;
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
            camDisableUserView(0, 0);
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
                play_sound_global(SOUND_UNK_6A, NULL);
            }
        } else if (D_801267D8[4] & B_BUTTON) {
            disable_new_screen_transitions();
            transition_begin(&sMenuTransitionFadeIn);
            enable_new_screen_transitions();
            gMenuDelay = -1;
        } else {
            s32 prevValue = D_801269C8;
            s32 prevValue2 = D_801269CC;
            if ((D_80126820 < 0) && (D_801269C8 > 0)) {
                D_801269C8--;
            }
            if ((D_80126820 > 0) && (D_801269C8 < 5)) {
                D_801269C8++;
            }
            if ((D_801269CC == 4) && (D_801269C8 == 5)) {
                D_801269C8 = 4;
            }
            if (D_80126820 == 0) {
                if ((D_80126838 < 0) && (D_801269CC < var_a1)) {
                    D_801269CC++;
                }
                if ((D_80126838 > 0) && (D_801269CC > 0)) {
                    D_801269CC--;
                }
                if ((D_801269C8 == 5) && (D_801269CC == 4)) {
                    D_801269CC = 3;
                }
            }
            if ((prevValue != D_801269C8) || (D_801269CC != prevValue2)) {
                play_sound_global(SOUND_MENU_PICK2, NULL);
                gTrackIdForPreview = D_801268E8[D_801269CC][D_801269C8];
                gTrackSelectRow = D_801269CC + 1;
                D_801269E8 = (D_801269C8 * 320);
                D_801269EC = -(D_801269CC * gTrackSelectViewportY);
            }
        }
    }
}

void func_80090ED8(UNUSED s32 updateRate) {
    if (gMenuOptionCount == 1 && D_800E0414 == 0 && D_80126840 == 0) {
        play_sound_global(SOUND_VOICE_TT_SNORE, &D_80126840);
    }
}

#ifdef NON_EQUIVALENT

// Somewhat close to matching, but should be functionally equivalent.
void render_track_select_setup_ui(s32 updateRate) {
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    char *sp78;
    s32 sp74;
    Settings *settings; // sp70
    s32 temp;
    s32 i, j;
    s32 s3;
    s32 s4;
    s32 s7;

    sp80 = 0;
    sp78 = NULL;
    sp74 = FALSE;
    settings = get_settings();
    if (osTvType == TV_TYPE_PAL) {
        sp80 = 12;
    }
    if ((gNumberOfActivePlayers == 2) && (D_801269C8 < 4) && (gMenuOptionCount >= 2)) {
        sp74 = TRUE;
    }
    camDisableUserView(0, 1);
    func_8009BD5C();
    set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (gMenuDelay < 0) {
        if (gSelectedTrackX == 4) {
            sp84 = 6;
        } else if (gSelectedTrackX == 5) {
            sp84 = 5;
        } else {
            sp84 = 4;
        }
        gMenuImageStack[sp84].unkC = 0.0f;
        gMenuImageStack[sp84].unk10 = 0.0f;
        if (osTvType == TV_TYPE_PAL) {
            D_800DF454 = 1.2f;
        }
        func_8009CA60(sp84);
        D_800DF454 = 1.0f;
    }
    if ((gMenuDelay >= -22) && (gMenuDelay < 31)) {
        if (gMenuDelay < 0) {
            sMenuGuiOpacity = (gMenuDelay * 16) + 255;
        } else {
            sMenuGuiOpacity = 255;
        }
        if (sMenuGuiOpacity < 0) {
            sMenuGuiOpacity = 0;
        }
        sp7C = get_map_available_vehicles(gTrackIdForPreview);
        set_text_font(ASSET_FONTS_BIGFONT);
        set_text_colour(192, 192, 255, 0, sMenuGuiOpacity);
        set_text_background_colour(0, 0, 0, 0);
        draw_text(&sMenuCurrDisplayList, POS_CENTRED, 43, get_level_name(gTrackIdForPreview), ALIGN_MIDDLE_CENTER); // Draw track name?
        sp84 = gOptionBlinkTimer * 8;
        if (sp84 >= 256) {
            sp84 = 511 - sp84;
        }
        set_current_dialogue_background_colour(7, 255, sp84, 0, sMenuGuiOpacity);
        if ((gMenuOptionCount == -1) || ((gMenuOptionCount == 2) && (D_801269C8 == 4) && is_adventure_two_unlocked())) {
            s4 = get_text_width(gMenuText[ASSET_MENU_TEXT_ADVENTURE2], 0, 0);   // "ADVENTURE"
            temp = get_text_width(gMenuText[ASSET_MENU_TEXT_ADVENTURETWO2], 0, 0); // "ADVENTURE TWO"
            if (s4 < temp) {
                s4 = temp;
            }
            if (s4 < D_800E0700.width) {
                s4 = D_800E0700.width;
            } else {
                s4 += 0xC;
            }
            func_80080580(&sMenuCurrDisplayList, -(s4 >> 1), 0x78 - D_800E0700.y, s4, D_800E0700.height,
                D_800E0700.borderWidth, D_800E0700.borderHeight, sMenuGuiOpacity + 0xB0E0C000, gMenuTextures[43]);
            func_80080E6C();
            set_text_font(ASSET_FONTS_FUNFONT);
            s7 = D_800E0700.colourMax + D_800E0700.y + sp80;
            s7++;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 4; j += 2) {
                    if (j == 0) {
                        set_text_colour(0, 0, 0, 255, sMenuGuiOpacity >> 1);
                    } else {
                        s32 alpha = i;
                        if (i == D_800E0418) {
                            alpha = sp84;
                        }
                        set_text_colour(255, 255, 255, alpha, sMenuGuiOpacity);
                    }
                    // gMenuText[146] = "ADVENTURE", gMenuText[147] = "ADVENTURE TWO"
                    draw_text(&sMenuCurrDisplayList, 161 - j, s7 - j, gMenuText[146 + i], ALIGN_MIDDLE_CENTER);
                }
                s7 += 16;
            }
        }
        if (D_801269C8 < 4) {
            set_text_font(ASSET_FONTS_FUNFONT);
            set_text_colour(255, 64, 64, 96, sMenuGuiOpacity);
            draw_text(&sMenuCurrDisplayList, 56, 72 + sp80, gMenuText[ASSET_MENU_TEXT_BESTTIME], ALIGN_MIDDLE_LEFT);  // "BEST TIME"
            draw_text(&sMenuCurrDisplayList, 56, 92 + sp80, gMenuText[ASSET_MENU_TEXT_BESTLAP], ALIGN_MIDDLE_LEFT); // "BEST LAP"
            set_text_colour(255, 128, 255, 96, sMenuGuiOpacity);
            decompress_filename_string(settings->courseInitialsPtr[gPlayerSelectVehicle[PLAYER_ONE]][gTrackIdForPreview], &sp78, 3);
            draw_text(&sMenuCurrDisplayList, 250, 72 + sp80, &sp78, ALIGN_MIDDLE_CENTER);
            decompress_filename_string(settings->flapInitialsPtr[gPlayerSelectVehicle[PLAYER_ONE]][gTrackIdForPreview], &sp78, 3);
            draw_text(&sMenuCurrDisplayList, 250, 92 + sp80, &sp78, ALIGN_MIDDLE_CENTER);
            show_timestamp(settings->courseTimesPtr[gPlayerSelectVehicle[PLAYER_ONE]][gTrackIdForPreview], 22, 53, 128, 255, 255, FONT_COLOURFUL);
            show_timestamp(settings->flapTimesPtr[gPlayerSelectVehicle[PLAYER_ONE]][gTrackIdForPreview], 22, 33, 255, 192, 255, FONT_COLOURFUL);
            if (gMenuOptionCount != -1) {
                if (gNumberOfActivePlayers == 1) {
                    // Glow effect
                    set_current_dialogue_box_coords(7, 134, sp80 + 112, 186, sp80 + 137);
                    render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 7);
                    if (gMenuOptionCount <= 0) {
                        render_textured_rectangle(&sMenuCurrDisplayList, &gRaceSelectionVehicleTitleTexture, 136, sp80 + 114, 255, 0xFF, 255, sMenuGuiOpacity);
                    } else {
                        render_textured_rectangle(&sMenuCurrDisplayList, &gRaceSelectionTTTitleTexture, 136, sp80 + 114, 255, 255, 255, sMenuGuiOpacity);
                        for (i = 0; i < 2; i++) {
                            s32 yTemp = 0x97 + sp80 + (i * 0x18);
                            if (i == D_800E0414) {
                                render_textured_rectangle(&sMenuCurrDisplayList, D_800E0648[(i * 3) + 1], 0x68, yTemp, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                            } else {
                                render_textured_rectangle(&sMenuCurrDisplayList, D_800E0648[(i * 3) + 2], 0x68, yTemp, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                            }
                        }
                    }
                } else {
                    if (!sp74) {
                        s3 = (gNumberOfActivePlayers - 1) * gNumberOfActivePlayers;
                        for (i = 0; i < gNumberOfActivePlayers; i++) {

                            if (((gNumberOfActivePlayers == 1) && (i == gMenuOptionCount)) || ((gNumberOfActivePlayers >= 2) && (D_801269C4[i] == 0))) {
                                s32 temp_v0_9 = D_800E0688[s3 + (i * 2)];
                                s32 temp_v1 = D_800E0688[s3 + (i * 2) + 1] + sp80;
                                // Glow effect around Player image
                                set_current_dialogue_box_coords(7, temp_v0_9 - 2, temp_v1 - 2, temp_v0_9 + 0x32, temp_v1 + 0x17);
                                render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 7);
                            }

                            // "Player" text image
                            render_textured_rectangle(&sMenuCurrDisplayList, D_800E0660[i], D_800E0688[s3 + (i * 2)], D_800E0688[s3 + (i * 2) + 1] + sp80, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                        }
                    }
                }

                if ((gNumberOfActivePlayers >= 2) || gMenuOptionCount == 0) {
                    // Draws "Car", "Hover", "Plane" text choice images.
                    if (sp74 == 0) {
                        s32 yTemp = 0x8B + sp80;
                        s3 = ((gNumberOfActivePlayers - 1) * gNumberOfActivePlayers) / 2;
                        for (i = 0; i < 3; i++) {
                            if ((1 << i) & sp7C) {
                                if (gNumberOfActivePlayers > 0) {
                                    for (j = 0; j < gNumberOfActivePlayers; j++) {
                                        if (i == gPlayerSelectVehicle[j]) {
                                            // Highlighted
                                            render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[(i * 3) + 1], D_800E06B0[s3 + j], yTemp, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                                        } else if (settings->courseFlagsPtr[gTrackIdForPreview] & 2) {
                                            // Not highlighted
                                            render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[(i * 3) + 2], D_800E06B0[s3 + j], yTemp, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                                        } else {
                                            // Not available (Ghosted out)
                                            render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[(i * 3) + 2], D_800E06B0[s3 + j], yTemp, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity / 2);
                                        }
                                    }
                                }
                                yTemp += 0x18;
                            }
                        }
                    }
                }
                sp80 += 0x8B;
                s7 = sp80;
                if (gPlayerSelectVehicle[PLAYER_ONE] == 2) {
                    s7 = sp80 + 2;
                }
                if (gNumberOfActivePlayers == 1) {
                    if (gMenuOptionCount == 0) {
                        // Draw vehicle image for one player
                        render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[gPlayerSelectVehicle[PLAYER_ONE] * 3], 0x95, s7, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                    } else {
                        // Draw T.T. image for one player
                        render_textured_rectangle(&sMenuCurrDisplayList, D_800E0648[D_800E0414 * 3], 0x95, sp80, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                    }
                }
                if ((gNumberOfActivePlayers == 2) && (!sp74)) {
                    s7 = sp80;
                    // Draw vehicle image for first player
                    render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[gPlayerSelectVehicle[PLAYER_ONE] * 3], 0x4F, s7, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                    if (gPlayerSelectVehicle[PLAYER_TWO] == 2) {
                        s7 = sp80 + 2;
                    }
                    // Draw vehicle image for second player
                    render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[gPlayerSelectVehicle[PLAYER_TWO] * 3], 0xB0, s7, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                }

                reset_render_settings(&sMenuCurrDisplayList);

                if (gNumberOfActivePlayers < 3) {
                    // Draw border around vehicle images
                    if (!sp74) {
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
                }

                if (sp74) {
                    s32 temp_v0_12 = get_text_width(gMenuText[ASSET_MENU_TEXT_NUMBEROFRACERS], 0, 0); // "NUMBER OF RACERS"
                    if ((gTwoPlayerRacerCountMenu.width - 0xC) < temp_v0_12) {
                        s4 = temp_v0_12 + 0xC;
                    } else {
                        s4 = gTwoPlayerRacerCountMenu.width;
                    }
                    func_80080580(&sMenuCurrDisplayList, -(s4 >> 1), 0x78 - gTwoPlayerRacerCountMenu.y, s4, gTwoPlayerRacerCountMenu.height, gTwoPlayerRacerCountMenu.textPos[0], gTwoPlayerRacerCountMenu.textPos[1], 0xB0E0C0FF, gMenuTextures[43]);
                    func_80080E6C();
                    set_text_font(ASSET_FONTS_FUNFONT);
                    set_text_colour(0, 0, 0, 0xFF, 0x80);
                    draw_text(&sMenuCurrDisplayList, gTwoPlayerRacerCountMenu.textPos[2] + gTwoPlayerRacerCountMenu.x + 1, gTwoPlayerRacerCountMenu.textPos[3] + gTwoPlayerRacerCountMenu.y + 1, gMenuText[ASSET_MENU_TEXT_NUMBEROFRACERS], ALIGN_MIDDLE_CENTER);
                    set_text_colour(0xFF, 0xFF, 0xFF, 0, 0xFF);
                    draw_text(&sMenuCurrDisplayList, gTwoPlayerRacerCountMenu.textPos[2] + gTwoPlayerRacerCountMenu.x - 1, gTwoPlayerRacerCountMenu.textPos[3] + gTwoPlayerRacerCountMenu.y - 1, gMenuText[ASSET_MENU_TEXT_NUMBEROFRACERS], ALIGN_MIDDLE_CENTER);
                    func_80068508(1);
                    func_8007BF1C(FALSE);
                    for (i = 0; i < 3; i++) {
                        s32 index = i * 2;
                        if (i == gMultiplayerSelectedNumberOfRacers) {
                            if (gMenuOptionCount < 3) {
                                sMenuGuiColourG = 0xFF - sp84;
                                sMenuGuiColourB = 0xFF - sp84;
                            } else {
                                sMenuGuiColourG = 0;
                                sMenuGuiColourB = 0;
                            }
                        }
                        // X position
                        gMenuImageStack[0].unkC = (gTwoPlayerRacerCountMenu.textPos[4 + index] + gTwoPlayerRacerCountMenu.x) - 0xA0;
                        // Y position
                        gMenuImageStack[0].unk10 = (-gTwoPlayerRacerCountMenu.textPos[5 + index] - gTwoPlayerRacerCountMenu.y) + 0x78;
                        // Number value to draw.
                        gMenuImageStack[0].unk18 = index + 2;
                        func_8009CA60(0);
                        sMenuGuiColourG = 0xFF;
                        sMenuGuiColourB = 0xFF;
                    }
                    func_8007BF1C(TRUE);
                    func_80068508(0);
                }
            }
        }
        if (D_801269C8 < 4) {
            func_8007BF1C(FALSE);
            i = 11;
            if (gIsInAdventureTwo) {
                i = 12;
            }
            gMenuImageStack[i].unk10 = 42.0f;
            if ((settings->courseFlagsPtr[gTrackIdForPreview] & 2) || is_adventure_two_unlocked()) {
                gMenuImageStack[i].unkC = -128.0f;
                func_8009CA60(i);
            }
            if ((settings->courseFlagsPtr[gTrackIdForPreview] & 4) || is_adventure_two_unlocked()) {
                gMenuImageStack[i].unkC = 120.0f;
                func_8009CA60(i);
            }
            func_8007BF1C(TRUE);
        }
        if ((gNumberOfActivePlayers == 1) && (gMenuOptionCount >= 0) && (func_80092BE0(gTrackIdForPreview) >= 0)) {
            // Render small T.T. icon.
            render_textured_rectangle(&sMenuCurrDisplayList, &gRaceSelectionTTTexture, 0xCC, 0x7A, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
            reset_render_settings(&sMenuCurrDisplayList);
        }
        if (D_801269C8 != 5) {
            if (((gMenuOptionCount == 2) && !sp74) || ((gMenuOptionCount == 3) && sp74) || (gMenuOptionCount == 4)) {
                set_text_font(ASSET_FONTS_BIGFONT);
                set_text_colour(0xFF, 0xFF, 0xFF, 0, sMenuGuiOpacity);
                if (D_801269C8 >= 4) {
                    sp80 += 0x18;
                }
                draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 172, D_800E823C, ALIGN_MIDDLE_CENTER); // D_800E823C = "OK?"
            }
        }
        sMenuGuiOpacity = 0xFF;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/render_track_select_setup_ui.s")
#endif

GLOBAL_ASM("asm/non_matchings/menu/func_80092188.s")

s32 func_80092BE0(s32 mapId) {
    s8 *trackIdArray;
    s32 index;
    s32 temp;

    trackIdArray = (s8 *)get_misc_asset(MISC_ASSET_UNK1C);

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
    s16 temp;

    settings = get_settings();
    gTrackIdForPreview = ASSET_LEVEL_CENTRALAREAHUB;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    mapId = settings->unk4C->unk2;
    gPlayerSelectVehicle[PLAYER_ONE] = get_map_default_vehicle(mapId);
    result = get_map_race_type(mapId);
    if ((result == 5) || (result == 8) || (!(result & 0x40) && (!(settings->courseFlagsPtr[mapId] & 2)))) {
        temp = D_800E0758[mapId];
        if (temp != -1) {
            func_80000FDC(temp, 0, 1.0f);
        }
        gMenuOptionCount = -1;
    } else {
        temp = D_800E0758[mapId];
        if (temp != -1) {
            func_80000FDC(temp, 0, 0.5f);
        }
        set_music_player_voice_limit(0x18);
        play_music(SEQUENCE_MAIN_MENU);
        func_80000B18();
        gMenuOptionCount = 0;
        func_8009C674(D_800E0FB4);
        allocate_menu_images(D_800E0FD8);
        assign_vehicle_icon_textures();
        gRaceSelectionCarOptHighlight[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_CAR_HIGHLIGHT];
        gRaceSelectionCarOpt[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_CAR];
        gRaceSelectionHoverOptHighlight[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT_HIGHLIGHT];
        gRaceSelectionHoverOpt[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT];
        gRaceSelectionPlaneOptHighlight[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_PLANE_HIGHLIGHT];
        gRaceSelectionPlaneOpt[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_SELECT_PLANE];
        gRaceSelectionVehicleTitleTexture[0].texture = gMenuTextures[TEXTURE_ICON_VEHICLE_TITLE];
        gRaceSelectionTTTexture[0].texture = gMenuTextures[TEXTURE_ICON_TT_HEAD];

        transition_begin(&sMenuTransitionFadeOut);
        gOptionBlinkTimer = 0;
        gMenuDelay = 0;
        gTrackNameVoiceDelay = 30;
        load_font(ASSET_FONTS_BIGFONT);
        load_level_for_menu(mapId, -1, 1);
    }
    assign_dialogue_box_id(7);
    if (get_map_race_type(mapId) & 0x40) {
        func_800C31EC(get_map_world_id(mapId) + 0x3B);
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
    Settings* settings;
    char *levelName;

    filename = NULL;
    settings = get_settings();
    yOffset = 0;
    if (osTvType == TV_TYPE_PAL) {
        yOffset = 12;
    }
    sp58 = ((Settings4C *)((u8 *) settings->unk4C + gTrackIdForPreview))->unk2;
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
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 46,  levelName, ALIGN_MIDDLE_CENTER);
            set_text_colour(255, 255, 255, 0, 255);
            draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 43,  levelName, ALIGN_MIDDLE_CENTER);
            if (!(get_map_race_type(sp58) & 0x40)) {
                if (arg2 == 0) {
                    if (is_time_trial_enabled()) {
                        if (func_80092BE0(sp58) >= 0) {
                            render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionTTTexture, SCREEN_HEIGHT - 36, yOffset + 122, 255, 255, 255, sMenuGuiOpacity);
                        }
                        set_text_font(0);
                        set_text_colour(255, 64, 64, 96, 255);
                        draw_text(&sMenuCurrDisplayList, 88, yOffset + 72, gMenuText[ASSET_MENU_TEXT_BESTTIME], ALIGN_MIDDLE_CENTER);
                        draw_text(&sMenuCurrDisplayList, 88, yOffset + 92, gMenuText[ASSET_MENU_TEXT_BESTLAP], ALIGN_MIDDLE_CENTER);
                        set_text_colour(255, 128, 255, 96, 255);
                        decompress_filename_string(settings->courseInitialsPtr[gPlayerSelectVehicle[0]][sp58], (char *) &filename, 3);
                        draw_text(&sMenuCurrDisplayList, 258, yOffset + 72, (char*) &filename, ALIGN_MIDDLE_CENTER);
                        decompress_filename_string(settings->flapInitialsPtr[gPlayerSelectVehicle[0]][sp58], (char *) &filename, 3);
                        draw_text(&sMenuCurrDisplayList, 258, yOffset + 92, (char*) &filename, ALIGN_MIDDLE_CENTER);
                        show_timestamp(settings->courseTimesPtr[gPlayerSelectVehicle[0]][((Settings4C *)((u8 *) settings->unk4C + gTrackIdForPreview))->unk2], 26, 53, 128, 255, 255, 0);
                        show_timestamp(settings->flapTimesPtr[gPlayerSelectVehicle[0]][((Settings4C *)((u8 *) settings->unk4C + gTrackIdForPreview))->unk2], 26, 33, 255, 192, 255, 0);
                    }
                    greenAmount = gOptionBlinkTimer * 8;
                    if (greenAmount > 255) {
                        greenAmount = 511 - greenAmount;
                    }
                    set_current_dialogue_background_colour(7, 255, greenAmount, 0, 255);
                    set_current_dialogue_box_coords(7, 134, yOffset + 112, 186, yOffset + 137);
                    render_dialogue_box(&sMenuCurrDisplayList, NULL, NULL, 7);
                    render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionVehicleTitleTexture, 136, yOffset + 114, 255, 255, 255, 255);
                    
                    y = yOffset + 139;
                    savedY = y;
                        
                    for (i = 0; i < 3; i++) {
                        alpha = (arg1 < 2 && get_map_default_vehicle(sp58) != (Vehicle) i) ? 128 : 255;
                        if ((1 << i) & mask) {
                            if (i == gPlayerSelectVehicle[0]) {
                                render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[i*3+1], 104, y, 255, 255, 255, 255);
                            } else {
                                render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[i*3+2], 104, y, 255, 255, 255, alpha);
                            }
                            y += 24;
                        }
                    }
                    y = savedY;
                    if (gPlayerSelectVehicle[0] == 2) {
                        y += 2;
                    }
                    render_textured_rectangle(&sMenuCurrDisplayList, gRaceSelectionImages[gPlayerSelectVehicle[0]*3], 149, y, 255, 255, 255, 255);
                    reset_render_settings(&sMenuCurrDisplayList);
                    gMenuImageStack[7].unkC = 21.0f;
                    gMenuImageStack[7].unk10 = -52.0f;
                    func_8009CA60(7);
                    if (gMenuOptionCount != 0) {
                        set_text_font(FONT_LARGE);
                        set_text_background_colour(0, 0, 0, 0);
                        set_text_colour(255, 255, 255, 0, 255);
                        draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yOffset + 172, (char*) D_800E8240, ALIGN_MIDDLE_CENTER);
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
    mapId = ((Settings4C *)((u8 *)settings->unk4C + gTrackIdForPreview))->unk2;
    sp28 = FALSE;
    sp1C = 0;
    if (settings->courseFlagsPtr[mapId] & 2) {
        sp1C = 1;
    }
    if (settings->courseFlagsPtr[mapId] & 4) {
        sp1C = 2;
    }
    if (get_map_race_type(mapId) & 0x40) {
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
                    func_800C31EC(0x2710);
                }
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
                play_sound_global(SOUND_SELECT2, NULL);
            } else if (D_801267D8[0] & B_BUTTON) {
                play_sound_global(SOUND_MENU_BACK3, NULL);
                if (sp20 || sp28) {
                    if (sp28) {
                        func_800C31EC(0x2710);
                    }
                    transition_begin(&sMenuTransitionFadeIn);
                    gMenuDelay = -1;
                } else {
                    gMenuOptionCount = 0;
                }
            }
        } else {
            if (D_801267D8[0] & B_BUTTON) {
                play_sound_global(SOUND_MENU_BACK3, NULL);
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = -1;
            } else if (D_801267D8[0] & (A_BUTTON | START_BUTTON)) {
                gMenuOptionCount = 1;
                play_sound_global(SOUND_CAR_REV2, NULL);
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
                    play_sound_global(SOUND_MENU_PICK2, NULL);
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
    func_8009C4A8((s16 *)&D_800E0FB4);
    unload_font(ASSET_FONTS_BIGFONT);
    func_80000B28();
}

//Pause Menu
void func_80093A40(void) {
    s32 raceType;
    s32 i;
    Settings *settings;

    func_80072298(0);
    settings = get_settings();
    D_800E098C = -1;

    for (i = 0; ((get_active_player_count() > i) && (D_800E098C < 0)); i++) {
        if (get_buttons_held_from_player(i) & START_BUTTON) {
            D_800E098C = i;
        }
    }
    if (D_800E098C < 0) {
        D_800E098C = 0;
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
                gMenuOptionText[2] = (!gIsInTracksMode) ? gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY] : gMenuText[ASSET_MENU_TEXT_SELECTTRACK];
                gMenuOptionCap = 3;
            } else if (raceType == RACETYPE_DEFAULT) {
                gMenuOptionText[1] = gMenuText[ASSET_MENU_TEXT_RESTARTRACE];
                gMenuOptionText[2] = (!gIsInTracksMode) ? gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY] : gMenuText[ASSET_MENU_TEXT_SELECTTRACK];
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

#ifdef NON_EQUIVALENT
// In the right ballpark, but not right.
// Draw pause game screen?
void func_80093D40(UNUSED s32 updateRate) {
    s32 yOffset;
    s32 i;
    s32 x;
    ColourRGBA *colours;
    s32 baseYPos;
    s32 xPos;
    s32 alpha;

    for (i = 0, xPos = SCREEN_WIDTH_HALF; i < gMenuOptionCap; i++) {
        x = get_text_width(gMenuOptionText[i], 0, 0) + 8;
        if (xPos < x) {
            xPos = x;
        }
    }

    baseYPos = (osTvType == TV_TYPE_PAL) ? SCREEN_HEIGHT_HALF_PAL : SCREEN_HEIGHT_HALF;

    yOffset = ((gMenuOptionCap * 16) + 28);

    clear_dialogue_box_open_flag(7);
    assign_dialogue_box_id(7);

    yOffset >>= 1;
    xPos >>= 1;

    set_current_dialogue_box_coords(7, SCREEN_WIDTH_HALF - xPos, baseYPos - yOffset, xPos + SCREEN_WIDTH_HALF, yOffset + baseYPos);
    colours = &D_800E0990[get_player_id(D_800E098C)];
    set_current_dialogue_background_colour(7, colours->r, colours->g, colours->b, colours->a);
    set_dialogue_font(7, 0);
    set_current_text_background_colour(7, 128, 128, 255, 0);
    colours = &D_800E09A0[get_player_id(D_800E098C)];
    set_current_text_colour(7, colours->r, colours->g, colours->b, colours->a, 255);
    alpha = gOptionBlinkTimer * 8;
    if (alpha >= 256) {
        alpha = 511 - alpha;
    }
    if (gMenuSubOption != 0) {
        if (gTrophyRaceWorldId != 0) {
            yOffset -= 26;
            render_dialogue_text(7, POS_CENTRED, yOffset + 8, gMenuText[ASSET_MENU_TEXT_QUITTROPHYRACETITLE], 1, 12);
        } else {
            yOffset -= 26;
            render_dialogue_text(7, POS_CENTRED, yOffset + 8, gMenuText[ASSET_MENU_TEXT_QUITGAMETITLE], 1, 12);
        }
        if (gMenuSubOption == 1) {
            set_current_text_colour(7, 255, 255, 255, alpha, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, POS_CENTRED, yOffset + 28, gMenuText[ASSET_MENU_TEXT_OK], 1, 12); // OK
        if (gMenuSubOption == 2) {
            set_current_text_colour(7, 255, 255, 255, alpha, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, POS_CENTRED, yOffset + 44, gMenuText[ASSET_MENU_TEXT_CANCEL], 1, 12);
    } else {
        render_dialogue_text(7, POS_CENTRED, 12, gMenuText[ASSET_MENU_TEXT_PAUSEOPTIONS], D_800E098C + 1, 12);
        for (i = 0, yOffset = 32; i < gMenuOptionCap; i++, yOffset += 16) {
            if (i == gMenuOption) {
                set_current_text_colour(7, 255, 255, 255, alpha, 255);
            } else {
                set_current_text_colour(7, 255, 255, 255, 0, 255);
            }
            render_dialogue_text(7, POS_CENTRED, yOffset, gMenuOptionText[i], 1, 12);
        }
    }
    open_dialogue_box(7);
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80093D40.s")
#endif

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
        adjust_audio_volume(VOLUME_NORMAL);
        return 0;
    }

    adjust_audio_volume(VOLUME_LOWER);
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    update_controller_sticks();

    buttonsPressed = 0;
    if (gIgnorePlayerInputTime == 0) {
        buttonsPressed = get_buttons_pressed_from_player(D_800E098C);
    }

    if (gMenuDelay == 0) {
        if (gMenuSubOption != 0) {
            if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                play_sound_global(SOUND_SELECT2, NULL);
                if (gMenuSubOption == 1) {
                    gMenuDelay = 1;
                } else {
                    gMenuSubOption = 0;
                }
            } else if (buttonsPressed & B_BUTTON) {
                play_sound_global(SOUND_SELECT2, NULL);
                gMenuSubOption = 0;
            } else {
                temp = gMenuSubOption;
                playerId = D_800E098C;
                if (gControllersYAxisDirection[playerId] != 0) {
                    gMenuSubOption = 3 - gMenuSubOption;
                }
                if (temp != gMenuSubOption) {
                    play_sound_global(SOUND_MENU_PICK2, NULL);
                }
            }
        } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            play_sound_global(SOUND_SELECT2, NULL);
            if ((gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_QUITGAME]) ||
                    ((gTrophyRaceWorldId != 0) && (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_QUITTROPHYRACE]))) {
                gMenuSubOption = 2;
            } else {
                gMenuDelay = 1;
            }
        } else {
            temp = gMenuOption;
            playerId = D_800E098C;
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
                play_sound_global(SOUND_MENU_PICK2, NULL);
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
                adjust_audio_volume(VOLUME_NORMAL);
                return 1;
            }
            if ((gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_RESTARTRACE]) || (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_RESTARTCHALLENGE])) {
                if ((gIsInTracksMode == 0) && (D_800E0758[get_ingame_map_id()] != -1)) {
                    func_80000FDC(D_800E0758[get_ingame_map_id()], 0, 1.0f);
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
                adjust_audio_volume(VOLUME_NORMAL);
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
    gMenuPortraitKrunch[0].texture = gMenuTextures[TEXTURE_ICON_PORTRAIT_KRUNCH];
    gMenuPortraitDiddy[0].texture = gMenuTextures[TEXTURE_ICON_PORTRAIT_DIDDY];
    gMenuPortraitDrumstick[0].texture = gMenuTextures[TEXTURE_ICON_PORTRAIT_DRUMSTICK];
    gMenuPortraitBanjo[0].texture = gMenuTextures[TEXTURE_ICON_PORTRAIT_BANJO];
    gMenuPortraitBumper[0].texture = gMenuTextures[TEXTURE_ICON_PORTRAIT_BUMPER];
    gMenuPortraitConker[0].texture = gMenuTextures[TEXTURE_ICON_PORTRAIT_CONKER];
    gMenuPortraitTiptup[0].texture = gMenuTextures[TEXTURE_ICON_PORTRAIT_TIPTUP];
    gMenuPortraitTT[0].texture = gMenuTextures[TEXTURE_ICON_PORTRAIT_TT];
    gMenuPortraitPipsy[0].texture = gMenuTextures[TEXTURE_ICON_PORTRAIT_PIPSY];
    gMenuPortraitTimber[0].texture = gMenuTextures[TEXTURE_ICON_PORTRAIT_TIMBER];
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
    D_80126A90 = 0;
    if (gNumberOfActivePlayers == 1 && gTrophyRaceWorldId == 0) {
        if (is_in_tracks_mode() == TRUE) {
            gResultOptionText[0] = gMenuText[ASSET_MENU_TEXT_TRYAGAIN];
            gResultOptionText[1] = gMenuText[ASSET_MENU_TEXT_SELECTTRACK];
            gResultOptionText[2] = gMenuText[ASSET_MENU_TEXT_SELECTCHARACTER];
            gResultOptionCount = 3;
            D_80126A90 = 1;
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
    D_80126CC0 = 0;
    gOptionBlinkTimer = 0;
    gOpacityDecayTimer = 0;
    gMenuDelay = 0;
    D_800DF460 = 0;
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
        var_v1 = &D_800E0710[arg1 * 3];
        if (var_v1[0] != -1) {
            func_8009C6D4(var_v1[0]);
            D_80126BB8 = gMenuTextures[var_v1[0]];
        } else {
            D_80126BB8 = 0;
        }
        if (var_v1[1] != -1) {
            func_8009C6D4(var_v1[1]);
            D_80126BBC = gMenuTextures[var_v1[1]];
        } else {
            D_80126BBC = 0;
        }
        D_80126BC0 = var_v1[2];
        if (get_game_mode() == GAMEMODE_INGAME) {
            func_80078170(D_80126BB8, D_80126BBC, D_80126BC0);
        }
        camEnableUserView(0, 1);
        resize_viewport(0, 0, 0, gTrackSelectViewPortX, gTrackSelectViewportY);
    }
    adjust_audio_volume(VOLUME_LOWER_AMBIENT);
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
            allocate_menu_images(D_800E0A40);
            assign_racer_portrait_textures();
            settings = get_settings();
            D_800E0BEC->unk14_a.element = gRacerPortraits[settings->racers[settings->timeTrialRacer].character];
            if (!is_time_trial_enabled()) {
                for (i = 0; i < 8; i++) {
                    for (j = 0; j < 8; j++) {
                        if (i == settings->racers[j].starting_position) {
                            D_800E0CEC[7 - i].unk14_a.element = gRacerPortraits[settings->racers[j].character];
                        }
                    }
                }
                if (is_in_two_player_adventure()) {
                    for (i = 0; i < 6; i++) {
                        D_800E0CEC[i + 1].unk14_a.element = D_800E0CEC[i + 2].unk14_a.element;
                    }
                    D_800E0CEC[7].unk14_a.element = &D_80126850;
                    D_800E0CEC[0].unk14_a.element = &D_80126850;
                }
            }
            D_80126C54.unk0_s32 = -1;
            return;
        }
        func_8009C6D4(temp_a0);
        D_80126C54.unk0_s32++;
    }
}

void func_80094C14(s32 arg0) {
    gOptionBlinkTimer = (gOptionBlinkTimer + arg0) & 0x3F;
    D_80126A94 += arg0;
    if (gOpacityDecayTimer >= 0) {
        gOpacityDecayTimer += arg0;
        switch (D_800DF460) {
            case 0:
                if (normalise_time(240) < gOpacityDecayTimer) {
                    set_music_fade_timer(-256);
                    D_800DF460 = 1;
                }
                break;
            case 1:
                if (normalise_time(300) < gOpacityDecayTimer) {
                    set_music_player_voice_limit(24);
                    play_music(SEQUENCE_MAIN_MENU);
                    set_music_fade_timer(256);
                }
                break;
        }
        if (normalise_time(300) < gOpacityDecayTimer) {
            gOpacityDecayTimer = -1;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_80094D28.s")

void func_80095624(s32 status) {
    // status may contain controllerIndex in it's upper bits
    // so grab the lower bits for the SIDeviceStatus
    switch (status & 0xFF) {
        case NO_CONTROLLER_PAK:
        case CONTROLLER_PAK_CHANGED: /*Required to match*/ \
            D_80126C1C = sNoControllerPakMenuText;
            break;
        case CONTROLLER_PAK_FULL:
        case CONTROLLER_PAK_UNK6: /*Required to match*/ \
            D_80126C1C = sControllerPakFullMenuText;
            break;
        case RUMBLE_PAK:
            // If you wish to use / the Controller Pak / insert it now!
            D_80126C1C = sInsertControllerPakMenuText;
            break;
        case CONTROLLER_PAK_UNK8:
            //If you wish to use / the Rumble Pak / insert it now!
            D_80126C1C = sInsertRumblePakMenuText;
            break;
        case CONTROLLER_PAK_BAD_DATA:
            D_80126C1C = sCorruptDataMenuText;
            break;
        default:
            D_80126C1C = sBadControllerPakMenuText;
            break;
    }

    for (D_80126C24 = 0; D_80126C1C[D_80126C24] != 0; D_80126C24++) {
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_80095728.s")

void func_80096790(void) {
    s32 temp;
    s8 *temp2;

    temp2 = (s8 *)get_current_level_header();
    func_8009C4A8(D_800E0A24);
    temp = *temp2 - 1;

    if (D_80126BB8) {
        func_8009C508(D_800E0710[temp * 3]);
    }
    D_80126BB8 = 0;

    if (D_80126BBC) {
        func_8009C508(D_800E0710[(temp * 3) + 1]);
    }
    D_80126BBC = 0;

    unload_big_font_4();
    adjust_audio_volume(VOLUME_NORMAL);
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
    func_8009C674(D_800E0A24);
    allocate_menu_images(D_800E0A40);
    assign_racer_portrait_textures();
    load_font(ASSET_FONTS_BIGFONT);
    transition_begin(&sMenuTransitionFadeOut);
    set_music_player_voice_limit(24);
    play_music(SEQUENCE_MAIN_MENU);
    set_music_fade_timer(128);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80096978.s")

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
            play_sound_global(SOUND_WHOOSH1, NULL);
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
                    set_music_fade_timer(-128);
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
                if (D_80126838 > 0 && gMenuSubOption == 2) {
                    gMenuSubOption = 1;
                }
                if (D_80126838 < 0 && gMenuSubOption == 1) {
                    gMenuSubOption = 2;
                }
                if (prevOption != gMenuSubOption) {
                    playPickSound = TRUE;
                }
            }
        } else if (D_801267D8[4] & (A_BUTTON | START_BUTTON)) {
            playSelectSound = TRUE;
            if (gResultOptionText[gMenuOption] == gMenuText[28]) {
                gMenuSubOption = 2;
            } else {
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
                set_music_fade_timer(-128);
            }
        } else {
            prevOption = gMenuOption;
            if (D_80126838 < 0 && gMenuOption < (gResultOptionCount - 1)) {
                gMenuOption++;
            }
            if (D_80126838 > 0 && gMenuOption > 0) {
                gMenuOption--;
            }
            if (prevOption != gMenuOption) {
                playPickSound = TRUE;
            }
        }
        if (playBackSound) {
            play_sound_global(SOUND_MENU_BACK3, NULL);
        } else if (playSelectSound) {
            play_sound_global(SOUND_SELECT2, NULL);
        } else if (playPickSound) {
            play_sound_global(SOUND_MENU_PICK2, NULL);
        }
        
    } else {
        gMenuDelay += updateRate;
        if (gMenuDelay > 30) {
            func_800976CC();
            close_dialogue_box(7);
            assign_dialogue_box_id(7);
            if (gResultOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_TRYAGAIN]) {
                return (0x100 | 0x2); //This gets parsed in menu_logic_loop as a flag and an ID from the bottom 7 bits.
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
    func_8009C4A8(D_800E0A24);
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
            if (charIndex >= (s32)(sizeof(gFileNameValidChars) - 1)) {
                break;
            }
        }

        output *= sizeof(gFileNameValidChars); // output <<= 5;
        output |= charIndex & (sizeof(gFileNameValidChars) - 1);
    }

    return output;
}

void trim_filename_string(char* input, char* output) {
    s32 some_ptr;   
    u32 zxChar;
    char* ptr_to_input;
    char new_var;
    s32 another_ptr;
    char* one_more_ptr;

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

void func_80097874(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, char *arg5, s32 arg6) {
    D_800E0F90 = arg0;
    D_800E0F94 = arg1;
    D_800E0F98 = arg2;
    D_800E0F9C = arg3;
    D_80126C6C = arg4;
    D_80126C74 = arg5;
    D_80126C78 = arg6;
    D_800E0FA0 = 0;
    D_80126C50 = (f32)*D_80126C6C;
    D_80126C48 = FALSE;
    D_80126C3C = 0;
    D_80126C34 = 0;
    load_font(ASSET_FONTS_BIGFONT);
}

#ifdef NON_EQUIVALENT
// Minor differences, and is very close.
// Draw menu for "Enter your initials" when starting a new game.
// The text entry is a horizontal list of characters you scroll through.
// Visual Aid: https://imgur.com/llVwdTy
void render_enter_filename_ui(UNUSED s32 unused) {
    s32 sp6C;
    s32 i;
    s32 pad;
    s32 temp_f4;
    s32 yPos;
    s32 charIndex;
    char *fileName;
    s32 xPos;
    s32 xPosOffset;
    s32 charIndexOffset;

    temp_f4 = D_80126C50;
    sp6C = SCREEN_WIDTH_HALF - (s32) ((D_80126C50 - temp_f4) * 40);
    set_text_background_colour(0, 0, 0, 0);
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 2, D_800E0F90 - 22, gMenuText[ASSET_MENU_TEXT_ENTERINITIALS], ALIGN_MIDDLE_CENTER);
    set_text_colour(255, 128, 255, 96, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, D_800E0F90 - 24, gMenuText[ASSET_MENU_TEXT_ENTERINITIALS], ALIGN_MIDDLE_CENTER);
    yPos = D_800E0F90;
    for (i = 0; i < 2; i++) {
        xPos = sp6C;
        charIndex = temp_f4;
        if (i != 0) {
            xPos -= 40;
            charIndex--;
            xPosOffset = -40;
            charIndexOffset = -1;
        } else {
            xPosOffset = 40;
            charIndexOffset = 1;
        }
        while ((xPos >= -15) && (xPos < 336)) {
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
                D_800E0F8C = gFileNameValidChars[charIndex];
                draw_text(&sMenuCurrDisplayList, xPos, yPos, &D_800E0F8C, ALIGN_MIDDLE_CENTER);
            } else {
                set_text_font(ASSET_FONTS_FUNFONT);
                if (charIndex == 28) {
                    draw_text(&sMenuCurrDisplayList, xPos, yPos, &D_800E8244 /* "SP" */, ALIGN_MIDDLE_CENTER);
                } else if (charIndex == 29) {
                    draw_text(&sMenuCurrDisplayList, xPos, yPos, &D_800E8248 /* "DEL" */, ALIGN_MIDDLE_CENTER);
                } else {
                    draw_text(&sMenuCurrDisplayList, xPos, yPos, &D_800E824C /* "OK" */, ALIGN_MIDDLE_CENTER);
                }
            }
            xPos += xPosOffset;
            charIndex += charIndexOffset;
        }
    }
    trim_filename_string(D_80126C74, fileName);
    if (fileName != NULL) {
        set_text_font(D_800E0F9C);
        set_text_colour(0, 0, 0, 255, 128);
        draw_text(&sMenuCurrDisplayList, D_800E0F94 + 1, D_800E0F98 + 3, fileName, ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 255, 255, 0, 255);
        draw_text(&sMenuCurrDisplayList, D_800E0F94, D_800E0F98, fileName, ALIGN_MIDDLE_CENTER);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/render_enter_filename_ui.s")
#endif

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
    if (D_800E0FA0 < D_80126C78) {
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            if (*temp_a1 < 29) {
                D_80126C74[D_800E0FA0] = gFileNameValidChars[*temp_a1];
                D_800E0FA0++;
                D_80126C74[D_800E0FA0] = 0;
                play_sound_global(SOUND_SELECT2, NULL);
                if (D_800E0FA0 >= D_80126C78) {
                    *D_80126C6C = 30;
                }
            } else if (*temp_a1 == 29) {
                if (D_800E0FA0 > 0) {
                    D_800E0FA0--;
                    D_80126C74[D_800E0FA0] = 0;
                }
                play_sound_global(SOUND_MENU_BACK3, NULL);
            } else {
                if ((D_800E0FA0 != 0) || (D_80126C74[0] == 0)) {
                    for (var_v1 = D_800E0FA0; var_v1 < D_80126C78; var_v1++) {
                        D_80126C74[var_v1] = 32;
                    }
                }
                D_80126C74[D_80126C78] = '\0';
                play_sound_global(SOUND_SELECT2, NULL);
                D_80126C48 = TRUE;
            }
        } else if (buttonsPressed & B_BUTTON) {
            if (D_800E0FA0 > 0) {
                D_800E0FA0--;
            }
            D_80126C74[D_800E0FA0] = 0;
            play_sound_global(SOUND_MENU_BACK3, NULL);
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
                play_sound_global(SOUND_MENU_PICK2, NULL);
                *D_80126C6C = var_v0_2;
            }
        }
    } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        play_sound_global(SOUND_SELECT2, NULL);
        D_80126C48 = TRUE;
    } else if (buttonsPressed & B_BUTTON) {
        D_800E0FA0--;
        D_80126C74[D_800E0FA0] = 0;
        play_sound_global(SOUND_MENU_BACK3, NULL);
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
    D_800DF450 = 1;
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
        if(index != -1) continue;
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
    set_music_player_voice_limit(24);
    play_music(SEQUENCE_MAIN_MENU);
    set_music_fade_timer(256);
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

    levelIds = (s8 *)get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    if (osTvType == TV_TYPE_PAL) {
        yPos = 18;
    } else {
        yPos = 0;
    }

    worldName = get_level_name(get_hub_area_id(gTrophyRaceWorldId));
    levelName = get_level_name(levelIds[((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound]);
    set_text_background_colour(0, 0, 0, 0);
    set_text_font(ASSET_FONTS_BIGFONT);
    //Text Shadows first
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 35, (char *)worldName, ALIGN_MIDDLE_CENTER);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF + 1, 67, gMenuText[ASSET_MENU_TEXT_TROPHYRACE], ALIGN_MIDDLE_CENTER); // TROPHY RACE
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 32, (char *)worldName, ALIGN_MIDDLE_CENTER);
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, 64, gMenuText[ASSET_MENU_TEXT_TROPHYRACE], ALIGN_MIDDLE_CENTER); // TROPHY RACE
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yPos + 176, gMenuText[138 + gTrophyRaceRound], ALIGN_MIDDLE_CENTER); // ROUND ONE / ROUND TWO / ROUND THREE / ROUND FOUR
    draw_text(&sMenuCurrDisplayList, SCREEN_WIDTH_HALF, yPos + 208, (char *)levelName, ALIGN_MIDDLE_CENTER);
}

s32 menu_trophy_race_round_loop(s32 updateRate) {
    s8 *trackMenuIds;
    s16 temp_a2;
    s32 temp;

    trackMenuIds = (s8 *)get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS); //tracks_menu_ids
    if (gTrackNameVoiceDelay != 0) {
        gTrackNameVoiceDelay -= updateRate;
        if (gTrackNameVoiceDelay <= 0) {
            //This is mostly likely supposed to be a multi dimensional array
            temp = trackMenuIds[(((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound)];
            temp_a2 = D_800E0758[temp];
            if (temp_a2 != -1) {
                play_sound_global(temp_a2, NULL);
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
            set_music_fade_timer(-128);
        }
    }
    if (gMenuDelay >= 31) {
        unload_big_font_5();
        gTrackIdToLoad = trackMenuIds[(((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound)];
        D_800DF478 = 1;
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

GLOBAL_ASM("asm/non_matchings/menu/func_80098774.s")

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
    func_8009C674(D_800E1024);
    allocate_menu_images(D_800E1040);
    gPrevTrophyRaceRound = gTrophyRaceRound;
    do {
        if(++gTrophyRaceRound >= 4) break;
    } while((trackMenuIds[((gTrophyRaceWorldId - 1) * 6) + (gTrophyRaceRound)] == -1));
    
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
    for(i = 0; i < gRankingPlayerCount; i++) {
        for(j = 0; j < gRankingPlayerCount; j++) {
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
    for(i = 0; i < gRankingPlayerCount; i++){
        D_801263F8[i] = gTrophyRacePointsArray[settings->racers[i].starting_position];
    }
    for(i = 0; i < gRankingPlayerCount; i++){
        D_80126430[i] = i;
        sp48[i] = settings->racers[i].trophy_points + D_801263F8[i];
    }
    
    for (i = gRankingPlayerCount-1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if(sp48[j] < sp48[j+1]) {
                tempForSwap = sp48[j];
                sp48[j] = sp48[j+1];
                sp48[j+1] = tempForSwap;
                tempForSwap = D_80126430[j];
                D_80126430[j] = D_80126430[j+1];
                D_80126430[j+1] = tempForSwap;
            }
        }
    }
    
    if (is_in_two_player_adventure()) {
        j = 2;
    } else {
        j = gNumberOfActivePlayers;
    }
    for(i = 0; i < gRankingPlayerCount; i++) {
        if (D_80126430[i] < j) {
            D_80126420[i] = 1;
        } else {
            D_80126420[i] = 0;
        }
    }
    load_font(ASSET_FONTS_BIGFONT);
    set_music_player_voice_limit(24);
    play_music(SEQUENCE_MAIN_MENU);
    set_music_fade_timer(256);
    func_80098774(0);
    func_80081E54(*D_800E1048, 0.5f, 20.0f, 0.5f, 0, 0);
}

void func_80098EBC(s32 arg0) {
    s32 test;
    s32 new_var2;
    s32 fade;
    s32 i;
    
    gOptionBlinkTimer = (gOptionBlinkTimer + arg0) & 0x3F;
    test = gOptionBlinkTimer * 8;
    if (test >= 0x100) {
        test = 0x1FF - test;
    }
    for (i = 0; i < gRankingPlayerCount; i++) {
        fade = 0xFF;
        if ((gNumberOfActivePlayers < 3) && (((gMenuOptionCount == 0) && D_80126418[i]) || ((gMenuOptionCount != 0) && D_80126420[i]))) {
            fade = (test >> 1) + 0x80;
        }
        D_800E1088[i][0].filterRed = fade;
        D_800E1088[i][0].filterGreen = fade;
        D_800E1088[i][0].filterBlue = fade;
    }
    new_var2 = gMenuOptionCount;
    if ((new_var2 == 2) || (new_var2 == 3)) {
        draw_menu_elements(1, D_800E1048[0], 1.0f);
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
            func_80081E54(*D_800E1048, 0.5f, 0.0f, 0.0f, 0, 0);
        }
        break;
    case 1:
        if (func_80081F4C(updateRate) != 0) {
            gMenuOptionCount = 2;
            draw_menu_elements(1, *D_800E1048, 1.0f);
        }
        break;
    case 2:
        gOpacityDecayTimer += updateRate;
        if (gOpacityDecayTimer > 10) {
            gOpacityDecayTimer -= 10;
            temp5 = 0;
            for(i = 0; i < gRankingPlayerCount; i++) {
                if (D_801263F8[i] > 0) {
                    D_801263F8[i]--;
                    temp5 = 1;
                    settings->racers[i].trophy_points++;
                }
            }
            if (temp5) {
                play_sound_global(SOUND_TING_HIGH, NULL);
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
            play_sound_global(SOUND_MENU_PICK2, NULL);
        }
        if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
            set_music_fade_timer(-128);
            transition_begin(&sMenuTransitionFadeIn);
            gMenuOptionCount = 3;
            for(i = 0; i < gRankingPlayerCount; i++){
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
                for(temp6 = 0, i = 0; i < gRankingPlayerCount; i++) {
                    if (D_80126420[i] != 0) {
                        temp7 = settings->racers[D_80126430[i]].character;
                        if (temp6 == 0) {
                            sp34 = i;
                            D_80126438[temp6++] = temp7;
                            continue;
                        }
                        if (settings->racers[D_80126430[i]].trophy_points == settings->racers[D_80126430[sp34]].trophy_points) {
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
                    if (D_800DF450 != 0) {
                        D_800DF450 = 0;
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
    func_8009C4A8(D_800E1024);
    unload_font(ASSET_FONTS_BIGFONT);
}

s32 get_trophy_race_world_id(void) {
    return gTrophyRaceWorldId;
}

GLOBAL_ASM("asm/non_matchings/menu/func_8009963C.s")
GLOBAL_ASM("asm/non_matchings/menu/func_800998E0.s")

#ifdef NON_EQUIVALENT

// Should be functionally equivalent
void menu_ghost_data_init(void) {
    s32 i;
    SIDeviceStatus pakStatus;

    pakStatus = func_800756D4(D_801264D0, &D_801264DC, &D_801264EC, &D_801264E4, &D_801264F8);
    if (pakStatus == CONTROLLER_PAK_GOOD) {
        func_8009963C();
    }
    func_8009C674(&D_800E1708);
    allocate_menu_images(&D_800E174C);
    load_font(ASSET_FONTS_BIGFONT);
    D_800E153C[0].texture = gMenuTextures[TEXTURE_BACKGROUND_DINO_DOMAIN_TOP];
    D_800E153C[5].texture = gMenuTextures[TEXTURE_BACKGROUND_DINO_DOMAIN_BOTTOM];
    D_800E1594[0].texture = gMenuTextures[TEXTURE_BACKGROUND_SHERBERT_ISLAND_TOP];
    D_800E1594[5].texture = gMenuTextures[TEXTURE_BACKGROUND_SHERBERT_ISLAND_BOTTOM];
    D_800E15EC[0].texture = gMenuTextures[TEXTURE_BACKGROUND_SNOWFLAKE_MOUNTAIN_TOP];
    D_800E15EC[5].texture = gMenuTextures[TEXTURE_BACKGROUND_SNOWFLAKE_MOUNTAIN_BOTTOM];
    D_800E1644[0].texture = gMenuTextures[TEXTURE_BACKGROUND_DRAGON_FOREST_TOP];
    D_800E1644[5].texture = gMenuTextures[TEXTURE_BACKGROUND_DRAGON_FOREST_BOTTOM];
    D_800E169C[0].texture = gMenuTextures[TEXTURE_BACKGROUND_FUTURE_FUN_LAND_TOP];
    D_800E169C[5].texture = gMenuTextures[TEXTURE_BACKGROUND_FUTURE_FUN_LAND_BOTTOM];
    for (i = 0; i < 4; i++) {
        D_800E153C[i + 1].texture = D_800E153C[0].texture;
        D_800E153C[i + 6].texture = D_800E153C[5].texture;
        if (i & 1 == 1) {
            D_800E1594[i + 1].texture = D_800E1594[0].texture;
            D_800E1594[i + 6].texture = D_800E1594[5].texture;
        } else {
            D_800E1594[i + 1].texture = D_800E1594[5].texture;
            D_800E1594[i + 6].texture = D_800E1594[0].texture;
        }
        D_800E15EC[i + 1].texture = D_800E15EC[0].texture;
        D_800E15EC[i + 6].texture = D_800E15EC[5].texture;
        D_800E1644[i + 1].texture = D_800E1644[0].texture;
        D_800E1644[i + 6].texture = D_800E1644[5].texture;
        if (i & 1 == 1) {
            D_800E169C[i + 1].texture = D_800E169C[0].texture;
            D_800E169C[i + 6].texture = D_800E169C[5].texture;
        } else {
            D_800E169C[i + 1].texture = D_800E169C[5].texture;
            D_800E169C[i + 6].texture = D_800E169C[0].texture;
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

GLOBAL_ASM("asm/non_matchings/menu/func_80099E8C.s")

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
                play_sound_global(SOUND_SELECT2, NULL);
            } else if ((pressedButtons & B_BUTTON) || ((pressedButtons & (START_BUTTON | A_BUTTON)) && (D_801264D4 == 0))) {
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
                play_sound_global(SOUND_MENU_BACK3, NULL);
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
                    play_sound_global(SOUND_MENU_PICK2, NULL);
                }
            }
            break;
        case 1:
            if (pressedButtons & B_BUTTON) {
                gMenuOptionCount = 0;
                play_sound_global(SOUND_MENU_BACK3, NULL);
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
                        play_sound_global(SOUND_SELECT2, NULL);
                    } else {
                        gMenuDelay = 1;
                        transition_begin(&sMenuTransitionFadeIn);
                        play_sound_global(SOUND_MENU_BACK3, NULL);
                    }
                    gMenuOptionCount = 0;
                } else if (yStick < 0) {
                    gMenuOptionCount = 2;
                    play_sound_global(SOUND_MENU_PICK2, NULL);
                }
            }
            break;
        case 2:
            if (pressedButtons & (START_BUTTON | A_BUTTON | B_BUTTON)) {
                gMenuOptionCount = 0;
                play_sound_global(SOUND_MENU_BACK3, NULL);
            } else if (yStick > 0) {
                gMenuOptionCount = 1;
                play_sound_global(SOUND_MENU_PICK2, NULL);
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
    func_8009C4A8(D_800E1708);
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

    if ((phi_v1 == 0) && (get_misc_asset(MISC_ASSET_UNK19) == (s32 *)arg0)) {
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
        func_8009C674(D_800E1768);
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
        for(i = 0; i < gNumberOfActivePlayers; i++) {
            buttonsPressed |= get_buttons_pressed_from_player(i);
        }
    }
    if (func_800214C4() != 0) {
        D_801267EC += 3;
        if (D_801267EC[0] >= 0) {
            load_level_for_menu(D_801267EC[0], D_801267EC[1], D_801267EC[2]);
        } else {
            if (D_8012684C) {
                func_80000B18();
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
            render_textured_rectangle(&sMenuCurrDisplayList, gRacerPortraits[D_80126804[i]], 24, 16 + (44 * i), 255, 255, 255, 255);
        }
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}



void func_8009AF18(void) {
    if (D_80126804 != NULL) {
        func_8009C4A8(D_800E1768);
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
    D_800DF460 = 0;
    D_80126BD0 = 0;
    D_80126BD8 = 0;
    D_80126BE0 = 0;
    set_background_fill_colour(0, 0, 0);
    if (osTvType == TV_TYPE_PAL) {
        resize_viewport(0, 0, 38, SCREEN_WIDTH, 224);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT + 44);
    } else {
        resize_viewport(0, 0, 40, SCREEN_WIDTH, 196);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    copy_viewports_to_stack();
    camEnableUserView(0, 1);
    func_8009C674(D_800E17D8);
    allocate_menu_images(D_800E17F0);
    assign_racer_portrait_textures();
    load_font(ASSET_FONTS_BIGFONT);
    set_music_player_voice_limit(24);
    D_800E18F8 = 0x1000;
    if (gViewingCreditsFromCheat) {
        play_music(SEQUENCE_DARKMOON_CAVERNS);
        gCreditsArray[84] = gCreditsLastMessageArray[2]; // "THE END"
        gCreditsArray[85] = gCreditsLastMessageArray[3]; // "NO CHEAT"
        gCreditsArray[86] = gCreditsLastMessageArray[4]; // "THIS TIME."
        gViewingCreditsFromCheat = FALSE;
    } else {
        if (settings->bosses & 0x20) {
            play_music(SEQUENCE_CRESCENT_ISLAND);
            gCreditsArray[84] = gCreditsLastMessageArray[1]; // "TO BE CONTINUED ..."
            D_800E18F8 = 0x61F4;
            D_80126BCC = 9;
        } else {
            play_music(SEQUENCE_DARKMOON_CAVERNS);
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
        gCreditsArray[85] = (char *)(*gCheatsAssetData) + (cheatOffsets)[(cheatIndex << 1) + 1]; // Cheat name
        gCreditsArray[86] = (char *)(*gCheatsAssetData) + (cheatOffsets)[(cheatIndex << 1)];     // Cheat code
    }
    func_80000B18();
    enable_new_screen_transitions();
    set_D_800DD430(1);
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
    set_music_player_voice_limit(0x12);
    disable_new_screen_transitions();
    camDisableUserView(0, 0);
    set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, VIEWPORT_AUTO, VIEWPORT_AUTO);
    func_8009C4A8(D_800E17D8);
    unload_font(ASSET_FONTS_BIGFONT);
    set_D_800DD430(0);
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

    temp_v0 = (unk80069D20 *)get_active_camera_segment();

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
    if (!gIsInTracksMode && D_800DF478 == 0) {
        if (settings->newGame) {
            return 0;
        } else {
            return settings->courseId;
        }
    }
    D_800DF478 = 0;
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

#define CHEATS_ALLOWED_IN_ADVENTURE_AND_TIME_TRIAL (CHEAT_CONTROL_TT | CHEAT_CONTROL_DRUMSTICK |     \
    CHEAT_BIG_CHARACTERS | CHEAT_SMALL_CHARACTERS | CHEAT_HORN_CHEAT | CHEAT_SELECT_SAME_PLAYER |    \
    CHEAT_TWO_PLAYER_ADVENTURE | CHEAT_ULTIMATE_AI | CHEAT_EPC_LOCK_UP_DISPLAY | CHEAT_ROM_CHECKSUM) \

// Remember that ~ means NOT. So the challenge maps only allow cheats NOT included here.
#define CHEATS_ALLOWED_IN_CHALLENGES ~(CHEAT_START_WITH_10_BANANAS | CHEAT_DISABLE_BANANAS |         \
    CHEAT_DISABLE_WEAPONS | CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN |              \
    CHEAT_ALL_BALLOONS_ARE_BLUE | CHEAT_ALL_BALLOONS_ARE_YELLOW | CHEAT_ALL_BALLOONS_ARE_RAINBOW)

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
    unk8006BDB0 *temp = (unk8006BDB0 *)get_current_level_header();
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
    return (Settings **)gSavefileData;
}

UNUSED void func_8009C49C(void) {
    D_800DF488 = 0;
}

void func_8009C4A8(s16 *arg0) {
    s32 index = 0;
    while (arg0[index] != -1) {
        func_8009C508(arg0[index++]);
    }
}

void func_8009C508(s32 arg0) {
    if (D_80126750[arg0] != 0) {
        if (gMenuTextures[arg0] != 0) {
            if ((((*gAssetsMenuElementIds)[arg0] & 0xC000) == 0xC000) && (gMenuTextures[arg0] != 0)) {
                set_free_queue_state(0);
                free_texture(gMenuTextures[arg0]);
                set_free_queue_state(2);
            } else {
                if ((*gAssetsMenuElementIds)[arg0] & 0x8000) {
                    free_sprite((Sprite *) (u32) gMenuTextures[arg0]);
                } else {
                    if ((*gAssetsMenuElementIds)[arg0] & 0x4000) {
                        free_object((Object *) (u32) gMenuTextures[arg0]);
                    } else {
                        func_8005FF40((ObjectModel**)(u32)gMenuTextures[arg0]);
                    }
                }
            }
        }
        gMenuTextures[arg0] = 0;
        D_80126750[arg0] = 0;
        D_800DF758--;
        gParticlePtrList_flush();
    }
    if (D_800DF758 == 0) {
        if (gMenuImageStack != NULL) {
            free_from_memory_pool(gMenuImageStack);
            gMenuImageStack = NULL;
        }
        if (*gAssetsMenuElementIds != NULL) {
            free_from_memory_pool(*gAssetsMenuElementIds);
            *gAssetsMenuElementIds = NULL;
            D_800DF754 = (u16)0;
        }
    }
}

void func_8009C674(s16 *textureIndex) {
    s32 index = 0;
    while (textureIndex[index] != -1) {
        func_8009C6D4(textureIndex[index++]);
    }
}

// Educated guess says this is a function that renders texture tiles on screen.
GLOBAL_ASM("asm/non_matchings/menu/func_8009C6D4.s")

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

//https://decomp.me/scratch/rfLCI
GLOBAL_ASM("asm/non_matchings/menu/func_8009CA60.s")

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
    if (D_800DF4E4[arg0] == 0) {
        if (arg0 != 3) {
            sCurrentMenuID = 0;
            gDialogueSubmenu = 0;
        }
        gNeedToCloseDialogueBox = TRUE;
        D_800DF4E4[arg0] = 1;
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

    D_800DF4E4[dialogueOption] = 0;
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
            set_current_text_colour(1, 0, 0, 0x7F, 0x5A, 0x78); //Locked
        }
    } else {
        set_current_text_colour(1, 0xCF, 0xCF, 0xCF, 0x5A, 0xFF); // Selected Option
    }
    gDialogueOptionTangible = (u8)FALSE;
}

/**
 * Render a line of text at a given Y position, and pass through the text ID and option ID.
 */
void render_dialogue_option(char *text, s32 yOffset, s32 optionID) {
    set_option_text_colour(gDialogueSubmenu == sDialogueOptionMax);
    if (gDialogueSubmenu == sDialogueOptionMax) {
        gDialogueItemSelection = optionID;
    }
    render_dialogue_text(1, POS_CENTRED, gDialogueOptionYOffset, text, 1, 4);
    gDialogueOptionYOffset = (s8)(gDialogueOptionYOffset + yOffset);
    sDialogueOptionMax = (s8)(sDialogueOptionMax + 1);
}

/**
 * Sets dialogue option when the joystick is moved.
 * Will wrap around if it goes out of bounds.
 */
void handle_menu_joystick_input(void) {
    if (gControllersYAxisDirection[0] < 0) {
        gDialogueSubmenu = gDialogueSubmenu + 1;
        play_sound_global(SOUND_MENU_PICK, NULL);
    } else if (gControllersYAxisDirection[0] > 0) {
        gDialogueSubmenu = gDialogueSubmenu - 1;
        play_sound_global(SOUND_MENU_PICK, NULL);
    }

    if (gDialogueSubmenu < 0) {
        gDialogueSubmenu = sDialogueOptionMax - 1;
    }

    if (gDialogueSubmenu >= sDialogueOptionMax) {
        gDialogueSubmenu = 0;
    }
}

void func_8009D324(void) {
    D_800DF4D8 = 0;
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
    s32 buttonsPressed; // sp28
    Settings *settings; // sp24

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
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_VEHICLESELECT], 1, 4); // VEHICLE SELECT
            gDialogueOptionYOffset = 30;
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_CAR], 20, 0); // CAR
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_HOVERCRAFT], 20, 1); // HOVERCRAFT
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_PLANE], 20, 2); // PLANE
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_MAINMENU], 20, 3); // MAIN MENU
            break;
        case 3:
        case 0x63:
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_CHALLENGESELECT], 1, 4); // CHALLENGE SELECT
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
            func_800C31EC(7);
            sCurrentMenuID = 1;
            D_800DF4D8 = 1;
            break;
        case 1:
            gNextTajChallengeMenu = 0;
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_OPTIONS], 1, 4); // OPTIONS
            gDialogueOptionYOffset = 30;
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_CHANGEVEHICLE], 20, 0); // CHANGE VEHICLE
            if (settings->tajFlags & TAJ_FLAGS_UNLOCKED_A_CHALLENGE) {
                render_dialogue_option(gMenuText[ASSET_MENU_TEXT_CHALLENGES], 20, 1); // CHALLENGES
            }
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_RETURN], 20, 2); // RETURN
            handle_menu_joystick_input();
            if (buttonsPressed & B_BUTTON) {
                sp2C = 3;
                play_sound_global(SOUND_MENU_BACK3, NULL);
            } else if (buttonsPressed & A_BUTTON) {
                play_sound_global(SOUND_SELECT2, NULL);
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
                play_sound_global(SOUND_MENU_BACK3, NULL);
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
                play_sound_global(SOUND_MENU_BACK3, NULL);
                play_taj_voice_clip(SOUND_VOICE_TAJ_MENUBACK2, TRUE);
                sCurrentMenuID = 1;
                gDialogueSubmenu = 3;
            } else if (buttonsPressed & A_BUTTON) {
                sp2C = gDialogueItemSelection | 0x40;
                play_sound_global(SOUND_SELECT2, NULL);
                sCurrentMenuID = 0x63;
            }
            break;
        case -3:
        case -2:
        case -1:
            func_800C31EC(ASSET_GAME_TEXT_8 - sCurrentMenuID); //Wouldn't this be ASSET_GAME_TEXT_9?
            sCurrentMenuID = 4;
            break;
        case -4:
            func_800C31EC(ASSET_GAME_TEXT_17);
            gNextTajChallengeMenu = 0;
            sCurrentMenuID = 1;
            gDialogueSubmenu = 3;
            break;
        case -5:
            func_800C31EC(ASSET_GAME_TEXT_21);
            gNextTajChallengeMenu = 0;
            sCurrentMenuID = 7;
            gDialogueSubmenu = 0;
            break;
        case -8:
        case -7:
        case -6:
            func_800C31EC(ASSET_GAME_TEXT_12 - sCurrentMenuID);
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
    render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_LOSETOTAJ_0], 1, 4);    // BETTER LUCK
    render_dialogue_text(1, POS_CENTRED, 20, gMenuText[ASSET_MENU_TEXT_LOSETOTAJ_1], 1, 4); // NEXT TIME!
    gDialogueOptionYOffset = 50;
    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_TRYAGAIN], 20, 0); // TRY AGAIN
    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_EXIT], 20, 1); // EXIT
    handle_menu_joystick_input();
    if (playerInput & A_BUTTON) {
        play_sound_global(SOUND_SELECT2, NULL);
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
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_OPTIONS], 1, 4); // OPTIONS
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_STATUS], 0x14, 3);             // STATUS
            if (!is_in_two_player_adventure()) {
                if (is_time_trial_enabled()) {
                    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_TIMETRIALON], 0x14, 0); // TIME TRIAL ON
                } else {
                    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_TIMETRIALOFF], 0x14, 0); // TIME TRIAL OFF
                }
                if (has_ghost_to_save()) {
                    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_SAVEGHOST], 0x14, 1); // SAVE GHOST
                }
            }
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_RETURN], 0x14, 2); // RETURN
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
                if(gPreviousMenuID && !gPreviousMenuID && !gPreviousMenuID){} // Fakematch
                switch (gDialogueItemSelection) {
                    case 1:
                        play_sound_global(SOUND_SELECT2, NULL);
                        gSaveGhostDelayCounter = 0;
                        gPreviousMenuID = TT_MENU_ROOT;
                        sCurrentMenuID = TT_MENU_SAVE_GHOST;
                        break;
                    case 3:
                        play_sound_global(SOUND_SELECT2, NULL);
                        play_tt_voice_clip(SOUND_VOICE_TT_GAME_STATUS, TRUE);
                        func_8009C674(D_800E1E2C);
                        allocate_menu_images(D_800E1E40);
                        D_800E1E28 = 1;
                        sCurrentMenuID = TT_MENU_GAME_STATUS;
                        break;
                }
                currentOption = gDialogueItemSelection + 1;
            } else if (buttonsPressed & B_BUTTON) {
                play_sound_global(SOUND_MENU_BACK3, NULL);
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
                    render_dialogue_text(1, POS_CENTRED, yPos1, gTTSaveGhostPakErrorText[i], 1, 4);
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
        case TT_MENU_INTRODUCTION:
            {
            i = 52;
            while (gMenuText[i] != NULL) {
                render_dialogue_text(1, POS_CENTRED, 6 + ((i-52) * 16), gMenuText[i], 1, 4);
                i++;
            }
            if (buttonsPressed & (A_BUTTON | B_BUTTON)) {
                settings->cutsceneFlags |= CUTSCENE_TT_HELP;
                sCurrentMenuID = TT_MENU_ROOT;
            }
            }
            break;
        case TT_MENU_INSERT_CONT_PAK:
            render_dialogue_text(1, POS_CENTRED, 34, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_3], 1, 4); // If you wish to use
            render_dialogue_text(1, POS_CENTRED, 50, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_4], 1, 4); // the Controller Pak
            render_dialogue_text(1, POS_CENTRED, 66, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_6], 1, 4); // insert it now!
            if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                play_sound_global(SOUND_SELECT2, NULL);
                gSaveGhostDelayCounter = 0;
                gPreviousMenuID = TT_MENU_INSERT_RUMBLE_PAK;
                sCurrentMenuID = TT_MENU_SAVE_GHOST;
            } else if (buttonsPressed & B_BUTTON) {
                play_sound_global(SOUND_MENU_BACK3, NULL);
                sCurrentMenuID = TT_MENU_ROOT;
            }
            break;
        case TT_MENU_INSERT_RUMBLE_PAK:
            render_dialogue_text(1, POS_CENTRED, 34, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_3], 1, 4); // If you wish to use
            render_dialogue_text(1, POS_CENTRED, 50, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_5], 1, 4); // the Rumble Pak
            render_dialogue_text(1, POS_CENTRED, 66, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_6], 1, 4); // insert it now!
            if (buttonsPressed & (A_BUTTON | B_BUTTON | START_BUTTON)) {
                sCurrentMenuID = TT_MENU_ROOT;
            }
            break;
        case TT_MENU_SAVE_GHOST:
            render_dialogue_text(1, POS_CENTRED, 50, gMenuText[ASSET_MENU_TEXT_PLEASEWAIT], 1, 4); // PLEASE WAIT
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
                    case RUMBLE_PAK:
                        sCurrentMenuID = TT_MENU_INSERT_CONT_PAK;
                        break;
                    case NO_CONTROLLER_PAK:
                        // NO CONTROLLER PAK
                        // If you wish to change / Controller Pak or Rumble Pak, / please do so now.
                        gTTSaveGhostPakErrorText = sNoControllerPakMenuText;
                        sCurrentMenuID = TT_MENU_CONT_PAK_ERROR_1;
                        break;
                    case CONTROLLER_PAK_FULL:
                    case CONTROLLER_PAK_UNK6:
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
                    case CONTROLLER_PAK_UNK8:
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
    if ((sCurrentMenuID == TT_MENU_CONT_PAK_ERROR_1) ||
        (sCurrentMenuID == TT_MENU_CONT_PAK_ERROR_2) ||
        (sCurrentMenuID == TT_MENU_CONT_PAK_ERROR_3)) {
        render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_PAKERROR], 1, 4); // PAK ERROR
    }

    return currentOption;
}

GLOBAL_ASM("asm/non_matchings/menu/func_8009E3D0.s")

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
    render_dialogue_text(1, POS_CENTRED, 6, gMenuText[ASSET_MENU_TEXT_TROPHYRACE], 1, 4); // TROPHY RACE
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
    render_dialogue_text(1, POS_CENTRED, 30, gMenuText[ASSET_MENU_TEXT_ENTERTROPHYRACE], 1, 4); // ENTER TROPHY RACE
    set_option_text_colour(gDialogueSubmenu == 1);
    render_dialogue_text(1, POS_CENTRED, 50, gMenuText[ASSET_MENU_TEXT_EXIT], 1, 4); // EXIT
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

    sEepromSettings &= ~0xC; //Set bits 3 and 4 low first
    sEepromSettings |= langFlag; //Then set them according to the selected lang

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
