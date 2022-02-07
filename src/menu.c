/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007F900 */

#include "menu.h"
#include "memory.h"
#include "fade_transition.h"

#include <PR/os_cont.h>
#include "asset_sections.h"
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
#include "thread30.h"
#include "unknown_00BC20.h"
#include "unknown_06B2B0.h"
#include "unknown_078050.h"
#include "controller_pak.h"
#include "unknown_0348C0.h"
#include "unknown_003260.h"

/**
 * @file Contains all the code used for every menu in the game.
 */

/************ .bss ************/

// The bss section needs to stay above the data section!
// Otherwise the bss variables will get reordered, which is bad.

DrawTexture *D_80126390;
DrawTexture *D_80126394;
s32 D_80126398;
s32 D_8012639C;
Gfx *D_801263A0;
char **D_801263A4;
Gfx *D_801263A8;
VertexList *D_801263AC;
s32 *D_801263B0;
unk801263C0 D_801263B4;
unk801263C0 D_801263B8;
s32 D_801263BC;
unk801263C0 D_801263C0;

s32 gIgnorePlayerInput;
UNUSED s32 sUnused_801263C8; // Set to 0 in menu_init, and never again.
unk801263CC (*D_801263CC)[8];

s32 D_801263D0;
s8 gActivePlayersArray[4];
s32 D_801263D8;
s8 D_801263DC[4];
s32 D_801263E0;
s32 D_801263E4;
s8 gPlayersCharacterArray[8]; // -1 = Non active player, or character id if >= 0
s8 gCharacterIdSlots[8];
s32 D_801263F8[8];
u8 D_80126418[8];
u8 D_80126420[8];
u8 D_80126428[8];
s8 D_80126430;
s8 D_80126431;
s32 D_80126434;
s32 D_80126438[4];

//Eeeprom save data bits stored at address 0xF
//bit 0      = Adventure Two is Unlocked
//bit 1      = Used to set the CHEAT_MIRRORED_TRACKS magic code flag
//bits 2-3   = Current language value
//bits 4-23  = Used to set the CHEAT_CONTROL_DRUMSTICK magic code flag
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
MenuElement **D_80126460;
s8 gControllersYAxisDirection[4]; // Y axis (-1 = down, 1 = up) for controller
s8 gControllersXAxis[4];
s8 gControllersYAxis[4];
s32 sUnused_80126470; // Set to 0 in the magic codes menu and 0xD000 elsewhere, otherwise unused.
s32 D_80126474;
s32 D_80126478;
s32 D_8012647C;
s32 D_80126480;
s32 D_80126484;
s32 D_80126488;
s32 D_8012648C;
s32 D_80126490;
s32 D_80126494;
s32 D_80126498;
s32 D_8012649C;

SavefileInfo gSavefileInfo[4];

s32 D_801264D0;
s32 D_801264D4;
s8 sDialogueOption;
s32 D_801264DC;
s8 D_801264E0;
s8 D_801264E1;

s8 sCurrentMenuID;
s32 D_801264E4;
s32 D_801264E8;
s32 D_801264EC;
s32 D_801264F0[2];
s32 D_801264F8[2];
s32 D_80126500;
s8 sDialogueOptionMax;
s32 D_80126508;
s16 D_8012650C;
s8 gDialogOptionYOffset;
s32 D_80126510;
s16 D_80126514;
s8 D_80126516;
s32 D_80126518;
s32 D_8012651C;
s32 D_80126520;
s32 D_80126524;
s32 D_80126528;
s32 D_8012652C;
Settings *D_80126530[4];
s8 D_80126540;
s8 D_80126541;
s32 D_80126544;
s32 gMultiplayerSelectedNumberOfRacersCopy; // Saved version gMultiplayerSelectedNumberOfRacers?
u32 *D_80126550[67];                        // lookup table? TEXTURES
s32 D_8012665C;
s32 D_80126660;
s32 D_80126664;
s32 D_80126668[58];
u8 D_80126750[128];
s32 D_801267D0;
s32 D_801267D4;
s32 D_801267D8[3];
s32 D_801267E4;
s32 D_801267E8;
s8 *D_801267EC;
s32 D_801267F0[5];
s32 D_80126804;
s32 D_80126808[4];
s32 D_80126818;
s32 D_8012681C;
s32 D_80126820;
s32 D_80126824;
UNUSED s8 sUnused_80126828; // Set to 0 in menu_init, and never used again.
s32 D_8012682C;
s16 D_80126830;
s32 D_80126834;
s16 D_80126838;
s16 D_8012683A;
s32 D_8012683C;
s32 D_80126840;
s32 D_80126844;
s32 D_80126848;
s32 D_8012684C;
s32 *D_80126850;
s32 D_80126854;
s32 D_80126858;
s32 D_8012685C;
s32 D_80126860;
s32 D_80126864;
s16 D_80126868;
s32 D_8012686C;
f32 D_80126870;
s8 *D_80126874;
s32 D_80126878[24];
f32 D_801268D8;
s32 D_801268DC;
s32 D_801268E0;
s32 D_801268E4;
s32 D_801268E8[12];
s32 D_80126918[3];
s32 D_80126924;
s32 D_80126928;
s32 D_8012692C;
s32 D_80126930[36];
s8 gPlayerSelectVehicle[4]; // Unknown number of entries.
u8 D_801269C4[4];
s32 D_801269C8;
s32 D_801269CC;
s32 gAudioOutputStrings[3];
s32 D_801269DC;
u32 *gMusicTestString;
s32 D_801269E4;
s32 D_801269E8;
s32 D_801269EC;
s32 D_801269F0;
s32 D_801269F4;
s32 D_801269F8;
s32 *D_801269FC;
s32 D_80126A00;
unk800860A8 *D_80126A04;
s32 D_80126A08;
s32 D_80126A0C;
s32 D_80126A10;
s32 D_80126A14;
s32 D_80126A18;
s32 D_80126A1C;
s32 D_80126A20[MAXCONTROLLERS]; // Looks to be an array for number notes free in each controller memory pak
u8 sControllerPakIssueNotFound[MAXCONTROLLERS]; //Flag to see if there's no known issues for the given controller pak
u8 sControllerPakFatalErrorFound[MAXCONTROLLERS]; //Flag to see if there's a fatal error for the given controller pak
u8 sControllerPakNoFreeSpace[MAXCONTROLLERS]; //Flag to see if there's no free space for the given controller pak
u8 sControllerPakBadData[MAXCONTROLLERS]; //Flag to see if there's bad data for the given controller pak
u8 *D_80126A40[8]; //Menu Text
u8 sControllerPakDataPresent[MAXCONTROLLERS]; //Flag to see if there's data present for the given controller pak? Not sure
s32 D_80126A64;
s32 D_80126A68;
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
u8 *D_80126AA0[16]; //Text to render
u8 *sCurrentControllerPakAllFileNames[16]; //Every file name on the controller pak
u8 *sCurrentControllerPakAllFileExtensions[16]; //Every file extension on the controller pak
u8  sCurrentControllerPakAllFileTypes[16]; //File type of all files on controller pak
u32 sCurrentControllerPakAllFileSizes[16]; //File size of all files on controller pak
u32 sCurrentControllerPakFreeSpace; //Space available in current controller pak
s32 D_80126BB4; //8 if PAL, 7 if not
s32 D_80126BB8;
s32 D_80126BBC;
s32 D_80126BC0;
s32 D_80126BC4;
s32 D_80126BC8;
s32 D_80126BCC;
s32 D_80126BD0;
s32 D_80126BD4;
s32 D_80126BD8;
f32 D_80126BDC;
s32 D_80126BE0;
s32 D_80126BE4;
s32 D_80126BE8;
f32 D_80126BEC;
s32 D_80126BF0[8];
s32 D_80126C10;
s32 D_80126C14;
s32 D_80126C18;
char **D_80126C1C;
s32 D_80126C20;
s32 D_80126C24;
s32 D_80126C28;
s32 *D_80126C2C;
u16 (*gCheatsAssetData)[30]; // Cheat table.
s32 D_80126C34;
s32 gNumberOfCheats;
s32 D_80126C3C;
u16 gCheatInputCurrentRow;
u16 gCheatInputCurrentColumn;
u16 gCheatInputStringLength;
s16 gOptionsMenuItemIndex;
char *gCheatInputString;
s16 D_80126C4C;
f32 D_80126C50;
s8 D_80126C54;
s8 D_80126C55;
s8 D_80126C56;
s8 D_80126C57;
u8 D_80126C58[20];
s32 *D_80126C6C;
s32 D_80126C70;
s32 D_80126C74;
s32 D_80126C78;
s32 D_80126C7C;
s16 D_80126C80[32];
s32 D_80126CC0;

/******************************/

/************ .data ************/

s8 D_800DF450 = 0;
f32 D_800DF454 = 1.0f;
s32 D_800DF458 = 1;
s32 gTitleScreenCurrentOption = 0; // 0 = "Start", 1 = "Options"
s32 D_800DF460 = 0;
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
s32 gTrackIdForPreview      = 0;
s32 gTrackSelectRow         = 0; // 1 = Dino Domain, 2 = Sherbet Island, etc.
s32 gSaveFileIndex          = 0;
s32 D_800DF4D0              = 0; // Unused?
s32 gTrackIdToLoad          = 0;
s8 D_800DF4D8               = 1;
s8 D_800DF4DC               = 0;
s8 D_800DF4E0               = 0;

s8 D_800DF4E4[4] = {
    0, 0, 0, 0
};

s32 D_800DF4E8 = 0; // Currently unknown, might be a different type.
s8 gDialogOptionTangible = FALSE;

// Unused?
s32 D_800DF4F0[] = {
    0x4000, 0x8000, 0x1000, 0x2000, 0x8000, 0x10, 0x400, 0x00
};

//MenuElement?
unk800DF510 sMenuImageProperties[18] = {
    { 0, 0, 0, 0x00, 1.0f, 0.0f, 0.0f, -32.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x01, 1.0f, 0.0f, 0.0f, -32.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x02, 1.0f, 0.0f, 0.0f, -32.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x03, 1.0f, 0.0f, 0.0f, -32.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x05, 0.215f, 0.0f, 0.0f, -500.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x06, 0.215f, 0.0f, 0.0f, -500.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x07, 0.215f, 0.0f, 0.0f, -500.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x04, 0.125f, 0.0f, -40.0f, -500.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x5B, 0.75f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x5C, 0.75f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x42, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x40, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x41, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x4C, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x4D, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x4E, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x4F, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0x5D, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0 },
};

s16 *D_800DF750[1] = { NULL }; // This is probably not correct.
s16 D_800DF754 = 0;
s16 D_800DF758 = 0;
unk800DF510 *gMenuImageStack = NULL;

s32 sMenuMusicVolume = 0x7F;
s32 sMenuGuiOpacity = 0xFF;
s32 D_800DF768 = 1;

FadeTransition sMenuTransitionFadeInFast = FADE_TRANSITION(0, FADE_COLOR_BLACK, 10, -1);
FadeTransition sMenuTransitionFadeIn = FADE_TRANSITION(0, FADE_COLOR_BLACK, 18, -1);
FadeTransition sMenuTransitionFadeOut = FADE_TRANSITION(0x80, FADE_COLOR_BLACK, 18, 0);
UNUSED FadeTransition sMenuTransitionFadeInWhite = FADE_TRANSITION(0, FADE_COLOR_WHITE, 18, -1);
UNUSED FadeTransition sMenuTransitionFadeOutWhite = FADE_TRANSITION(0x80, FADE_COLOR_WHITE, 18, 0);

s32 D_800DF794 = 4;
s32 D_800DF798 = 0;
s32 D_800DF79C = 0;

s32 D_800DF7A0 = 0;
char *gTitleMenuStrings[3] = { 0, 0, 0 };

// Version text shown on the title screen? See 1:15 in https://www.youtube.com/watch?v=OHSCLcA74ao.
char gVersionDisplayText[20] = "VERSION XXXXXXXX";

// "Diddy Kong Racing" logo texture indices?
s16 sGameTitleTileTextures[12] = {
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, -1
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
    { "TIMBER", 14.0f, 14.5f, 16.5f, 17.0f, -80.0f, 208.0f, 160.0f, 208.0f, 400.0f, 208.0f },
    { "BUMPER", 19.0f, 19.5f, 21.5f, 22.0f, -80.0f, 208.0f, 160.0f, 208.0f, 400.0f, 208.0f },
    { "CONKER", 24.0f, 24.5f, 26.5f, 27.0f, -80.0f, 208.0f, 160.0f, 208.0f, 400.0f, 208.0f },
    { "TIPTUP", 29.0f, 29.5f, 31.5f, 32.0f, -80.0f, 208.0f, 160.0f, 208.0f, 400.0f, 208.0f },
    { "DRUMSTICK", 35.0f, 35.5f, 37.5f, 38.0f, -80.0f, 208.0f, 160.0f, 208.0f, 400.0f, 208.0f },
    { "PIPSY", 40.0f, 40.5f, 42.5f, 43.0f, -80.0f, 208.0f, 160.0f, 208.0f, 400.0f, 208.0f },
    { "BANJO", 45.0f, 45.5f, 47.5f, 48.0f, -80.0f, 208.0f, 160.0f, 208.0f, 400.0f, 208.0f },
    { "KRUNCH", 50.0f, 50.5f, 52.5f, 53.0f, -80.0f, 208.0f, 160.0f, 208.0f, 400.0f, 208.0f },
    { "WIZPIG", 57.5f, 58.0f, 60.0f, 60.5f, -80.0f, 208.0f, 160.0f, 208.0f, 400.0f, 208.0f },
    { "DIDDY", 63.5f, 64.0f, 66.0f, 66.5f, -80.0f, 208.0f, 160.0f, 208.0f, 400.0f, 208.0f }
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

// Unsure about typing with these arrays.
s32 D_800DFAE4[6] = { 0, 0, 0, 0, 0, 0 };
s32 D_800DFAFC[6] = { 0, 0, 0, 0, 0, 0 };
s32 D_800DFB14[6] = { 0, 0, 0, 0, 0, 0 };
s32 D_800DFB2C[5] = { 0, 0, 0, 0, 0 };
s32 D_800DFB40[7] = { 0, 0, 0, 0, 0, 0, 0 };
s32 D_800DFB5C[6] = { 0, 0, 0, 0, 0, 0 };
s32 D_800DFB74[6] = { 0, 0, 0, 0, 0, 0 };
s32 D_800DFB8C[6] = { 0, 0, 0, 0, 0, 0 };
s32 D_800DFBA4[6] = { 0, 0, 0, 0, 0, 0 };
s32 D_800DFBBC[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
s32 D_800DFBDC = 0;

// Unused?
s32 *D_800DFBE0[10] = {
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

MenuElement D_800DFCB4[7] = {
    { 161, 32,  161, 33,  161, 32,  0,   0,   0,   255, 128, 2, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 30,  160, 30,  160, 30,  255, 255, 255, 0,   255, 2, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 112, 160, 112, 160, 112, 255, 255, 255, 0,   255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 128, 160, 128, 160, 128, 255, 255, 255, 0,   255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 192, 160, 192, 160, 192, 255, 255, 255, 0,   255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 208, 160, 208, 160, 208, 255, 255, 255, 0,   255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0,  0, { NULL }, 0, 0, 0, 0 },
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
s32 D_800DFDD0[28] = {
    0xFFFF04FF, 0xFFFFFFFF, 0x010203FF, 0x0000FFFF,
    0x05FF00FF, 0xFFFF0203, 0xFFFF0009, 0xFFFF06FF,
    0x0100FFFF, 0x03FFFFFF, 0x0001FFFF, 0x07FF0201,
    0x00FFFFFF, 0xFFFF0005, 0x00FFFFFF, 0xFFFFFFFF,
    0x050607FF, 0x000301FF, 0xFFFF04FF, 0xFFFF0607,
    0xFFFF0002, 0x02FFFFFF, 0x0504FFFF, 0x07FFFFFF,
    0x000703FF, 0xFFFF0605, 0x04FFFFFF, 0xFFFF0004,
};

// Not sure what this is
s32 D_800DFE40[32] = {
    0xFFFF04FF, 0xFFFFFFFF, 0x01080203, 0x0000FFFF,
    0x040500FF, 0xFFFF0802, 0x03FF0009, 0xFFFF0607,
    0x080100FF, 0x03FFFFFF, 0x0001FFFF, 0x07FF0208,
    0x0100FFFF, 0xFFFF0005, 0x0001FFFF, 0xFFFFFFFF,
    0x050607FF, 0x00030108, 0xFFFF04FF, 0xFFFF0607,
    0xFFFF0002, 0x0802FFFF, 0x0504FFFF, 0x07FFFFFF,
    0x00070203, 0xFFFF0605, 0x04FFFFFF, 0xFFFF0004,
    0xFFFF0506, 0x0100FFFF, 0x0203FFFF, 0x00060000,
};

// Not sure what this is
s32 D_800DFEC0[32] = {
    0xFFFF04FF, 0xFFFFFFFF, 0x010203FF, 0x0000FFFF,
    0x050800FF, 0xFFFF0203, 0xFFFF0009, 0xFFFF0806,
    0x0100FFFF, 0x03FFFFFF, 0x0001FFFF, 0x06070201,
    0x00FFFFFF, 0xFFFF0005, 0x00FFFFFF, 0xFFFFFFFF,
    0x05080607, 0x00030001, 0xFFFF04FF, 0xFFFF0806,
    0x07FF0002, 0x0203FFFF, 0x080504FF, 0x07FFFFFF,
    0x000703FF, 0xFFFF0608, 0x0504FFFF, 0xFFFF0004,
    0x0102FFFF, 0x0504FFFF, 0x0607FFFF, 0x00080000,
};

// Not sure what this is
s32 D_800DFF40[36] = {
    0xFFFF04FF, 0xFFFFFFFF, 0x01080203, 0x0000FFFF,
    0x05FF00FF, 0xFFFF0802, 0x03FF0009, 0xFFFF06FF,
    0x080100FF, 0x03FFFFFF, 0x0001FFFF, 0x07FF0208,
    0x0100FFFF, 0xFFFF0005, 0x00FFFFFF, 0xFFFFFFFF,
    0x05090607, 0x000301FF, 0xFFFF04FF, 0xFFFF0906,
    0x07FF0002, 0x02FFFFFF, 0x090504FF, 0x07FFFFFF,
    0x000703FF, 0xFFFF0609, 0x0504FFFF, 0xFFFF0004,
    0xFFFF09FF, 0x0100FFFF, 0x0203FFFF, 0x000608FF,
    0x05FF0504, 0xFFFF0607, 0xFFFF0008, 0x00000000,
};

s32 D_800DFFD0 = 0;
s32 D_800DFFD4 = -1;

MenuElement gCautionMenuTextElements[14] = {
    { 161,  35, 161,  35, 161,  35,   0,   0,   0, 255, 128, 2, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160,  32, 160,  32, 160,  32, 255, 255, 255,   0, 255, 2, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160,  72, 160,  68, 160,  72, 255, 255, 255,   0, 255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160,  86, 160,  82, 160,  86, 255, 255, 255,   0, 255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 100, 160,  96, 160, 100, 255, 255, 255,   0, 255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 114, 160, 110, 160, 114, 255, 255, 255,   0, 255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 128, 160, 124, 160, 128, 255, 255, 255,   0, 255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 142, 160, 138, 160, 142, 255, 255, 255,   0, 255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 156, 160, 152, 160, 156, 255, 255, 255,   0, 255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 156, 160, 166, 160, 156, 255, 255, 255,   0, 255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 186, 160, 180, 160, 186, 255, 255, 255,   0, 255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 200, 160, 194, 160, 200, 255, 255, 255,   0, 255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    { 160, 200, 160, 208, 160, 200, 255, 255, 255,   0, 255, 0, 12, 0, { NULL }, 0, 0, 0, 0 },
    {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0,  0, 0, { NULL }, 0, 0, 0, 0 },
};

MenuElement gGameSelectTextElemsNoAdv2[7] = {
    { 161,  35, 161,  35, 161,  35,   0,   0,   0, 255, 128, 2, 12, 0, { NULL },   0,  0, 0, 0 },
    { 160,  32, 160,  32, 160,  32, 255, 255, 255,   0, 255, 2, 12, 0, { NULL },   0,  0, 0, 0 },
    { -96,  39, -96,  39, -96,  39, 176, 224, 192, 255, 255, 0,  0, 7, { NULL }, 192, 44, 4, 4 },
    { 160, 104, 160, 104, 160, 104, 255, 255, 255,   0, 255, 2, 12, 0, { NULL },   0,  0, 0, 0 },
    { -96,  -9, -96,  -9, -96,  -9, 176, 224, 192, 255, 255, 0,  0, 7, { NULL }, 192, 44, 4, 4 },
    { 160, 152, 160, 152, 160, 152, 255, 255, 255,   0, 255, 2, 12, 0, { NULL },   0,  0, 0, 0 },
    {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0,  0, 0, { NULL },   0,  0, 0, 0 },
};

MenuElement gGameSelectTextElemsWithAdv2[9] = {
    {  161,  35,  161,  35,  161,  35,   0,   0,   0, 255, 128, 2, 12, 0, { NULL },   0,  0, 0, 0 },
    {  160,  32,  160,  32,  160,  32, 255, 255, 255,   0, 255, 2, 12, 0, { NULL },   0,  0, 0, 0 },
    { -112,  55, -112,  55, -112,  55, 176, 224, 192, 255, 255, 0,  0, 7, { NULL }, 224, 44, 4, 4 },
    {  160,  88,  160,  88,  160,  88, 255, 255, 255,   0, 255, 2, 12, 0, { NULL },   0,  0, 0, 0 },
    { -112,   7, -112,   7, -112,   7, 176, 224, 192, 255, 255, 0,  0, 7, { NULL }, 224, 44, 4, 4 },
    {  160, 136,  160, 136,  160, 136, 255, 255, 255,   0, 255, 2, 12, 0, { NULL },   0,  0, 0, 0 },
    { -112, -41, -112, -41, -112, -41, 176, 224, 192, 255, 255, 0,  0, 7, { NULL }, 224, 44, 4, 4 },
    {  160, 184,  160, 184,  160, 184, 255, 255, 255,   0, 255, 2, 12, 0, { NULL },   0,  0, 0, 0 },
    {    0,   0,    0,   0,    0,   0,   0,   0,   0,   0,   0, 0,  0, 0, { NULL },   0,  0, 0, 0 },
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

unk800E03CC D_800E03CC[3] = {
    { 0x0018, 0x0051, 0x0058, 0x0040, 0x0004, 0x0004, 0x4080, 0xFFC0 },
    { 0x0074, 0x0051, 0x0058, 0x0040, 0x0004, 0x0004, 0x4080, 0xFFC0 },
    { 0x00D0, 0x0051, 0x0058, 0x0040, 0x0004, 0x0004, 0x4080, 0xFFC0 },
};

s16 D_800E03FC[10] = {
    0x002C, 0x0036, 0x0015, 0x0019, 0x002C, 0x001B, 0x003F, 0x0019, 0x002D, 0x0019
};

// Either 0 (2 racers), 1 (4 racers), or 2 (6 racers)
s32 gMultiplayerSelectedNumberOfRacers = 0;

s32 D_800E0414 = 0;
s32 D_800E0418 = 0;
DrawTexture D_800E041C[2] = { { NULL, -12, -8 }, { NULL, 0, 0 }};
DrawTexture D_800E042C[2] = { { NULL, -8, -12 }, { NULL, 0, 0 }};
DrawTexture D_800E043C[2] = { { NULL, -12, -8 }, { NULL, 0, 0 }};
DrawTexture D_800E044C[2] = { { NULL, -8, -12 }, { NULL, 0, 0 }};

DrawTexture D_800E045C[3] = { { NULL, 0, 0 }, { NULL, 0, 32 }, { NULL, 0, 0 } };
DrawTexture D_800E0474[3] = { { NULL, 0, 0 }, { NULL, 0, 32 }, { NULL, 0, 0 } };
DrawTexture D_800E048C[3] = { { NULL, 0, 0 }, { NULL, 0, 32 }, { NULL, 0, 0 } };
DrawTexture D_800E04A4[3] = { { NULL, 0, 0 }, { NULL, 0, 32 }, { NULL, 0, 0 } };
DrawTexture D_800E04BC[3] = { { NULL, 0, 0 }, { NULL, 0, 32 }, { NULL, 0, 0 } };
DrawTexture D_800E04D4[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E04E4[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E04F4[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0504[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0514[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0524[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0534[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0544[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0554[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0564[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0574[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0584[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0594[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E05A4[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E05B4[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E05C4[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };

// These are probably structs
s32 D_800E05D4[8] = { 0, 0xFFD0, 0, 0xFFF0, 0, 0x10, 0, 0 };
s32 D_800E05F4[8] = { 0, 0xFFD0, 0, 0xFFF0, 0, 0x10, 0, 0 };

DrawTexture D_800E0614[2] = { { NULL, -16, -16 }, { NULL, 0, 0 } };

DrawTexture *D_800E0624[9] = {
    D_800E045C, D_800E04D4, D_800E04E4, D_800E0474, D_800E04F4, D_800E0504, D_800E048C, D_800E0514, D_800E0524
};

DrawTexture *D_800E0648[6] = {
    D_800E04BC, D_800E0544, D_800E0564, D_800E04A4, D_800E0534, D_800E0554
};

DrawTexture *D_800E0660[6] = {
    D_800E0574, D_800E0584, D_800E0594, D_800E05A4, D_800E05B4, D_800E05C4
};

DrawTexture *D_800E0678[4] = {
    D_800E041C, D_800E042C, D_800E043C, D_800E044C
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

s16 D_800E06E4[14] = {
    0x50, 0x8C, 0xA0, 0x40, 0x04, 0x04, 0x50, 0x14, 0x3A, 0x28, 0x50, 0x28, 0x66, 0x28
};

s16 D_800E0700[8] = {
    0x50, 0x98, 0xA0, 0x28, 0x04, 0x04, 0x50, 0x0E
};

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

s32 D_800E0968 = 0;
s32 D_800E096C = 0;
s32 D_800E0970 = 0;
s32 D_800E0974 = 0;
const f32 D_800E7D04[1] = { 0.5f }; // .rodata
f32 *D_800E0978 = D_800E7D04;       // .data
s32 D_800E097C = 0;
s32 D_800E0980 = 0;
s32 D_800E0984 = 0;
s32 D_800E0988 = 0;
s32 D_800E098C = 0; //Player ID or controllerIndex maybe?

ColourRGBA D_800E0990[4] = {
    {  64,  64, 255, 160 },
    { 255,  64,  64, 160 },
    { 208, 192,  32, 176 },
    {  32, 192,  64, 176 },
};

ColourRGBA D_800E09A0[4] = {
    {   0, 255,   0, 128 },
    {   0, 255,   0,  96 },
    {   0,   0, 255,  96 },
    {   0,   0, 255, 128 },
};

char *D_800E09B0[5] = { 0, 0, 0, 0, 0 };
char *D_800E09C4[5] = { 0, 0, 0, 0, 0 };
char *D_800E09D8[5] = { 0, 0, 0, 0, 0 };
char *D_800E09EC[3] = { 0, 0, 0 };
char *D_800E09F8[3] = { 0, 0, 0 };
char *D_800E0A04[3] = { 0, 0, 0 };
s16 D_800E0A10 = 0;
char *D_800E0A14[4] = { 0, 0, 0, 0 };

s16 D_800E0A24[14] = {
    0x0005, 0x003B, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0039, 0x0037, 0x0038, 0x003A, 0x0000, 0x0001, 0xFFFF
};

s16 D_800E0A40[8] = {
    0x0004, 0x0000, 0x0001, 0xFFFF, 0x0300, 0x0000, 0x0012, 0xFFFF
};

DrawTexture D_800E0A50[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0A60[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0A70[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0A80[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0A90[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0AA0[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0AB0[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0AC0[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0AD0[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };
DrawTexture D_800E0AE0[2] = { { NULL, 0, 0 }, { NULL, 0, 0 } };

DrawTexture *D_800E0AF0[10] = {
    D_800E0A50, D_800E0A60, D_800E0A70, D_800E0A80,
    D_800E0A90, D_800E0AA0, D_800E0AB0, D_800E0AC0,
    D_800E0AD0, D_800E0AE0
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
    { 352, 172,  32, 172, -288, 172, 255, 255, 255, 0, 255, 0,  0, 3, { D_800E0A50 }, 0, 0, 0, 0 },
    { 452, 166, 132, 166, -188, 166, 255, 255, 255, 0, 255, 0, 12, 0, {      NULL  }, 0, 0, 0, 0 },
    { 560, 184, 240, 184,  -80, 184, 255, 255, 255, 0, 255, 0, 12, 0, {      NULL  }, 0, 0, 0, 0 },
    { 452, 180, 132, 180, -188, 180, 255, 192, 255, 0, 255, 0,  0, 1, {      NULL  }, 0, 0, 0, 0 },
    { 452, 198, 132, 198, -188, 198, 255, 192, 255, 0, 255, 0,  0, 1, {      NULL  }, 0, 0, 0, 0 },
    { 452, 216, 132, 216, -188, 216, 255, 192, 255, 0, 255, 0,  0, 1, {      NULL  }, 0, 0, 0, 0 },
    { 560, 200, 240, 200,  -80, 200, 128, 255, 255, 0, 255, 0,  0, 1, {      NULL  }, 0, 0, 0, 0 },
    {   0,   0,   0,   0,    0,   0,   0,   0,   0, 0,   0, 0,  0, 0, {      NULL  }, 0, 0, 0, 0 },
};

MenuElement D_800E0CEC[11] = {
    { 575, 172, 255, 172,  -65, 172, 255, 255, 255,   0, 255, 0,  0, 3, { D_800E0A50 }, 0, 0, 0, 0 },
    { 542, 172, 222, 172,  -98, 172, 255, 255, 255,   0, 255, 0,  0, 3, { D_800E0A50 }, 0, 0, 0, 0 },
    { 509, 172, 189, 172, -131, 172, 255, 255, 255,   0, 255, 0,  0, 3, { D_800E0A50 }, 0, 0, 0, 0 },
    { 476, 172, 156, 172, -164, 172, 255, 255, 255,   0, 255, 0,  0, 3, { D_800E0A50 }, 0, 0, 0, 0 },
    { 443, 172, 123, 172, -197, 172, 255, 255, 255,   0, 255, 0,  0, 3, { D_800E0A50 }, 0, 0, 0, 0 },
    { 410, 172,  90, 172, -230, 172, 255, 255, 255,   0, 255, 0,  0, 3, { D_800E0A50 }, 0, 0, 0, 0 },
    { 377, 172,  57, 172, -263, 172, 255, 255, 255,   0, 255, 0,  0, 3, { D_800E0A50 }, 0, 0, 0, 0 },
    { 344, 172,  24, 172, -296, 166, 255, 255, 255,   0, 255, 0,  0, 3, { D_800E0A50 }, 0, 0, 0, 0 },
    { 481, 166, 161, 166, -159, 166,   0,   0,   0, 255, 128, 0, 12, 0, {      NULL  }, 0, 0, 0, 0 },
    { 479, 164, 159, 164, -161, 164, 255, 255, 255,   0, 255, 0, 12, 0, {      NULL  }, 0, 0, 0, 0 },
    {   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0, 0,  0, 0, {      NULL  }, 0, 0, 0, 0 },

};



MenuElement D_800E0E4C[9] = {
    { 481, 174, 161, 174, -159, 174,   0,   0,   0, 255, 128, 0, 12, 0, {       NULL  }, 0, 0, 0, 0 },
    { 479, 172, 159, 172, -161, 172, 255, 255, 255,   0, 255, 0, 12, 0, {       NULL  }, 0, 0, 0, 0 },
    { 368, 192,  48, 192, -272, 192, 255,  64,  64,  96, 255, 0,  8, 0, {       NULL  }, 0, 0, 0, 0 },
    { 506, 187, 186, 187, -134, 187, 255, 192, 255,   0, 255, 0,  0, 1, {       NULL  }, 0, 0, 0, 0 },
    { 578, 192, 258, 192,  -62, 192, 255, 128, 255,  96, 255, 0, 12, 0, { &D_80126390 }, 0, 0, 0, 0 },
    { 368, 212,  48, 212, -272, 212, 255,  64,  64,  96, 255, 0,  8, 0, {       NULL  }, 0, 0, 0, 0 },
    { 506, 207, 186, 207, -134, 207, 128, 255, 255,   0, 255, 0,  0, 1, {       NULL  }, 0, 0, 0, 0 },
    { 578, 212, 258, 212,  -62, 212, 255, 128, 255,  96, 255, 0, 12, 0, { &D_80126394 }, 0, 0, 0, 0 },
    {   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0, 0,  0, 0, {       NULL  }, 0, 0, 0, 0 },
};

// Valid characters for name input. Must be u8, not char.
// The length of the array must be a power of two.
u8 gFileNameValidChars[32] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.?    ";

s32 D_800E0F8C = 0;
s32 D_800E0F90 = 192;
s32 D_800E0F94 = 160;
s32 D_800E0F98 = 120;
s32 D_800E0F9C = 2;
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

s32 D_800E0FE4 = 8; // Number of racers in trophy race? (1 to 8)
s32 gTrophyRaceWorldId = 0;
s32 D_800E0FEC = 0; // Trophy race round? (0 to 3)
s32 D_800E0FF0 = 0;

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

s32 D_800E1040 = 1;
s16 D_800E1044 = -1;

MenuElement D_800E1048[9][3] = {
    {
        { 481,   35, 161, 35, -159,  35,   0,   0,   0, 255, 128, 2, 12, 0, { NULL }, 0, 0, 0, 0 },
        { 480,   32, 160, 32, -160,  32, 255, 255, 255,   0, 255, 2, 12, 0, { NULL }, 0, 0, 0, 0 },
        {  64, -192,  64, 48,   64, 288, 255, 255, 255,   0, 255, 0,  0, 3, { &D_800E0A50 }, 0, 0, 0, 0 }
    },
    {
        {  32, -192,  32, 48,  32, 288, 255, 255, 255, 0, 255, 0, 0, 0, { gFirstPlace }, 0, 0, 0, 0 },
        { 130, -172, 130, 68, 130, 308, 255, 255, 255, 0, 255, 0, 4, 2, { &gTrophyRacePointsArray[0] }, 0, 0, 0, 0 },
        {  64, -150,  64, 90,  64, 330, 255, 255, 255, 0, 255, 0, 0, 3, { &D_800E0A50 }, 0, 0, 0, 0 }
    },
    {
        {  32, -150,  32,  90,  32, 330, 255, 255, 255, 0, 255, 0, 0, 0, { gSecondPlace }, 0, 0, 0, 0 },
        { 130, -130, 130, 110, 130, 350, 255, 192, 255, 0, 255, 0, 4, 2, { &gTrophyRacePointsArray[1] }, 0, 0, 0, 0 },
        {  64, -108,  64, 132,  64, 372, 255, 255, 255, 0, 255, 0, 0, 3, { &D_800E0A50 }, 0, 0, 0, 0 }
    },
    {
        {  32, -108,  32, 132,  32, 372, 255, 255, 255, 0, 255, 0, 0, 0, { gThirdPlace }, 0, 0, 0, 0 },
        { 130,  -88, 130, 152, 130, 392, 255, 128, 255, 0, 255, 0, 4, 2, { &gTrophyRacePointsArray[2] }, 0, 0, 0, 0 },
        {  64,  -66,  64, 174,  64, 414, 255, 255, 255, 0, 255, 0, 0, 3, { &D_800E0A50 }, 0, 0, 0, 0 }
    },
    {
        {  32, -66,  32, 174,  32,  414, 255, 255, 255, 0, 255, 0, 0, 0, { gFourthPlace }, 0, 0, 0, 0 },
        { 130, -46, 130, 194, 130,  434, 255,  64, 255, 0, 255, 0, 4, 2, { &gTrophyRacePointsArray[3] }, 0, 0, 0, 0 },
        { 220, 288, 220,  48, 220, -192, 255, 255, 255, 0, 255, 0, 0, 3, { &D_800E0A50 }, 0, 0, 0, 0 }
    },
    {
        { 188, 288, 188, 48, 188, -192, 255, 255, 255, 0, 255, 0, 0, 0, { gFifthPlace }, 0, 0, 0, 0 },
        { 286, 308, 286, 68, 286, -172, 255, 255, 255, 0, 255, 0, 4, 2, { &gTrophyRacePointsArray[4] }, 0, 0, 0, 0 },
        { 220, 330, 220, 90, 220, -160, 255, 255, 255, 0, 255, 0, 0, 3, { &D_800E0A50 }, 0, 0, 0, 0 }
    },
    {
        { 188, 330, 188,  90, 188, -150, 255, 255, 255, 0, 255, 0, 0, 0, { gSixthPlace }, 0, 0, 0, 0 },
        { 286, 350, 286, 110, 286, -130, 255, 192, 255, 0, 255, 0, 4, 2, { &gTrophyRacePointsArray[5] }, 0, 0, 0, 0 },
        { 220, 372, 220, 132, 220, -108, 255, 255, 255, 0, 255, 0, 0, 3, { &D_800E0A50 }, 0, 0, 0, 0 }
    },
    {
        { 188, 372, 188, 132, 188, -108, 255, 255, 255, 0, 255, 0, 0, 0, { gSeventhPlace }, 0, 0, 0, 0 },
        { 286, 392, 286, 152, 286,  -88, 255, 128, 255, 0, 255, 0, 4, 2, { &gTrophyRacePointsArray[6] }, 0, 0, 0, 0 },
        { 220, 414, 220, 174, 220,  -66, 255, 255, 255, 0, 255, 0, 0, 3, { &D_800E0A50 }, 0, 0, 0, 0 }
    },
    {
        { 188, 414, 188, 174, 188, -66, 255, 255, 255, 0, 255, 0, 0, 0, { gEighthPlace }, 0, 0, 0, 0 },
        { 286, 434, 286, 194, 286, -46, 255,  64, 255, 0, 255, 0, 4, 2, { &gTrophyRacePointsArray[7] }, 0, 0, 0, 0 },
        {   0,   0,   0,   0,   0,   0,   0,   0,   0, 0,   0, 0, 0, 0, { NULL }, 0, 0, 0, 0 }
    },
};

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

Gfx D_800E1780[11] = {
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

s32 gViewingCreditsFromCheat = 0; // Set to 1 if viewing credits from "WHODIDTHIS" cheat

MenuElement D_800E1B50[9] = {
    { 480, 104, 160, 104, -160, 104, 255,   0, 255, 48, 255, 0, 4, 0, { NULL }, 0, 0, 0, 0 },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, 2, 4, 0, { NULL }, 0, 0, 0, 0 },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255,  0, 255, 2, 4, 0, { NULL }, 0, 0, 0, 0 },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, 2, 4, 0, { NULL }, 0, 0, 0, 0 },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255,  0, 255, 2, 4, 0, { NULL }, 0, 0, 0, 0 },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, 2, 4, 0, { NULL }, 0, 0, 0, 0 },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255,  0, 255, 2, 4, 0, { NULL }, 0, 0, 0, 0 },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, 2, 4, 0, { NULL }, 0, 0, 0, 0 },
    {   0,   0,   0,   0,    0,   0,   0,   0,   0,  0,   0, 0, 0, 0, { NULL }, 0, 0, 0, 0 },
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

s8 D_800E1CF0[60] = {
    0, 0, 3, 0, 2, 1, 0, 0,
    2, 1, 1, 1, 2, 1, 3, 0,
    3, 3, 2, 1, 3, 3, 2, 2,
    1, 2, 2, 2, 3, 3, 1, 2,
    3, 3, 0, 3, 0, 0, 1, 1,
    1, 2, 0, 0, 1, 2, 0, 3,
    1, 1, 2, 1, 2, 2, 1, 1,
    2, 2, 1, 2
};

u16 D_800E1D2C[40] = {
    0x0000, 0x0000, 0x0100, 0x0000, 0x01FF, 0x00FF, 0x0001, 0x00FF,
    0x01FF, 0x00FF, 0x0100, 0x0000, 0x0100, 0xFF00, 0x01FF, 0xFF01,
    0x0001, 0xFF01, 0x01FF, 0xFF01, 0x0100, 0xFF00, 0x0000, 0xFF00,
    0x0000, 0x0000, 0x0001, 0x00FF, 0x0001, 0xFF01, 0x0000, 0xFF00,
    0x0001, 0x00FF, 0x01FF, 0x00FF, 0x01FF, 0xFF01, 0x0001, 0xFF01
};

s16 D_800E1D7C[20] = {
    0x00D8, 0x00D8, 0x00D8, 0x0100,
    0x00B0, 0x00B0, 0x00B0, 0x0100,
    0x0060, 0x0060, 0x0060, 0x0100,
    0x0088, 0x0088, 0x0088, 0x0100,
    0x0100, 0x0100, 0x0100, 0x0100
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

FadeTransition D_800E1DE8 = FADE_TRANSITION(0, FADE_COLOR_BLACK, 120, -1);

char gRareCopyrightString[24] = "(C) COPYRIGHT RARE 1997";

//Probably a FadeTransition, but that won't be certain
//FadeTransition D_800E1E08 = FADE_TRANSITION(0, FADE_COLOR_BLACK, 52, -1);
s16 D_800E1E08[4] = {
    0, 0, 0x34, -1
};

char *D_800E1E10 = " (ADV.";

s32 D_800E1E14 = 0;
s32 D_800E1E18 = 0;
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

/*******************************/

/************ .rodata ************/

const char D_800E8208[] = "OK?";
const char D_800E820C[] = "~";
const char D_800E8210[] = "DEL";
const char D_800E8214[] = "OK";
const char D_800E8218[] = "ROM checksum %08X,%d\n"; // Used with the "DODGYROMMER" cheat.
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
        case JAPANESE:
            langIndex = 4;
            break;
        case GERMAN:
            langIndex = 3;
            break;
        case FRENCH:
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
        gAudioOutputStrings[0] = gMenuText[0];           // STEREO
        gAudioOutputStrings[1] = gMenuText[1];           // MONO
        gAudioOutputStrings[2] = gMenuText[2];           // HEADPHONES
        gAudioMenuStrings[1].unkC = gMenuText[3];        // SFX VOLUME
        gAudioMenuStrings[2].unkC = gMenuText[4];        // MUSIC VOLUME
        gAudioMenuStrings[3].unkC = gMenuText[5];        // RETURN
        gAudioMenuStrings[4].unkC = gMenuText[6];        // AUDIO OPTIONS
        gAudioMenuStrings[5].unkC = gMenuText[6];        // AUDIO OPTIONS
        gMusicTestString = gMenuText[7];                 // MUSIC TEST 00
        gMagicCodeMenuStrings[0] = gMenuText[14];        // ENTER CODE
        gMagicCodeMenuStrings[1] = gMenuText[15];        // CLEAR ALL CODES
        gMagicCodeMenuStrings[2] = gMenuText[16];        // CODE LIST
        gMagicCodeMenuStrings[3] = gMenuText[5];         // RETURN
        D_800E0BEC[1].unk14_a.asciiText = gMenuText[29]; // LAP TIMES
        D_800E0BEC[2].unk14_a.asciiText = gMenuText[30]; // OVERALL TIME
        D_800E0CEC[8].unk14_a.asciiText = gMenuText[31]; // RACE ORDER
        D_800E0CEC[9].unk14_a.asciiText = gMenuText[31]; // RACE ORDER
        D_800E0E4C[0].unk14_a.asciiText = gMenuText[32]; // RECORD TIMES
        D_800E0E4C[1].unk14_a.asciiText = gMenuText[32]; // RECORD TIMES
        D_800E0E4C[2].unk14_a.asciiText = gMenuText[9];  // BEST TIME
        D_800E0E4C[5].unk14_a.asciiText = gMenuText[10]; // BEST LAP
        gOptionMenuStrings[0] = gMenuText[34];           // ENGLISH
        if (sEepromSettings & 0x2000000) {
            gOptionMenuStrings[1] = gMenuText[182]; // SUBTITLES ON
        } else {
            gOptionMenuStrings[1] = gMenuText[183]; // SUBTITLES OFF
        }
        gOptionMenuStrings[2] = gMenuText[6];                               // AUDIO OPTIONS
        gOptionMenuStrings[3] = gMenuText[165];                             // SAVE OPTIONS
        gOptionMenuStrings[4] = gMenuText[17];                              // MAGIC CODES
        gOptionMenuStrings[5] = gMenuText[5];                               // RETURN
        gFilenames[0] = gMenuText[72];                                      // GAME A
        gFilenames[1] = gMenuText[73];                                      // GAME B
        gFilenames[2] = gMenuText[74];                                      // GAME C
        D_800DFAE4[0] = gMenuText[90];                                      // CONTROLLER PAK ~
        D_800DFAE4[1] = gMenuText[91];                                      // IS NOT PRESENT.
        D_800DFAE4[3] = gMenuText[85];                                      // CANCEL
        D_800DFAFC[0] = gMenuText[90];                                      // CONTROLLER PAK ~
        D_800DFAFC[1] = gMenuText[93];                                      // CONTAINS CORRUPT DATA.
        D_800DFAFC[3] = gMenuText[94];                                      // ATTEMPT TO REPAIR
        D_800DFAFC[4] = gMenuText[85];                                      // CANCEL
        D_800DFB14[0] = gMenuText[90];                                      // CONTROLLER PAK ~
        D_800DFB14[1] = gMenuText[95];                                      // IRREPARABLY DAMAGED.
        D_800DFB14[3] = gMenuText[96];                                      // REFORMAT PAK
        D_800DFB14[4] = gMenuText[85];                                      // CANCEL
        D_800DFB2C[0] = gMenuText[90];                                      // CONTROLLER PAK ~
        D_800DFB2C[1] = gMenuText[97];                                      // FULL.
        D_800DFB2C[3] = gMenuText[98];                                      // CONTINUE
        D_800DFB40[0] = gMenuText[90];                                      // CONTROLLER PAK ~
        D_800DFB40[1] = gMenuText[99];                                      // DIFFERENT CONTROLLER
        D_800DFB40[2] = gMenuText[100];                                     // PAK IS INSERTED.
        D_800DFB40[4] = gMenuText[85];                                      // CANCEL
        D_800DFB5C[0] = gMenuText[90];                                      // CONTROLLER PAK ~
        D_800DFB5C[1] = gMenuText[102];                                     // CANNOT STORE ANY
        D_800DFB5C[2] = gMenuText[103];                                     // MORE GHOSTS.
        D_800DFB5C[4] = gMenuText[98];                                      // CONTINUE
        D_800DFB74[0] = gMenuText[90];                                      // CONTROLLER PAK ~
        D_800DFB74[1] = gMenuText[184];                                     // CORRUPT DATA.
        D_800DFB74[3] = gMenuText[23];                                      // TRY AGAIN
        D_800DFB74[4] = gMenuText[85];                                      // CANCEL
        D_800DFB8C[0] = gMenuText[153];                                     // Rumble Pak Detected
        D_800DFB8C[1] = gMenuText[154];                                     // Insert any Controller Paks
        D_800DFB8C[2] = gMenuText[155];                                     // you wish to use now!
        D_800DFB8C[4] = gMenuText[98];                                      // CONTINUE
        D_800DFBA4[0] = gMenuText[156];                                     // If you wish to use any
        D_800DFBA4[1] = gMenuText[157];                                     // Rumble Paks then please
        D_800DFBA4[2] = gMenuText[158];                                     // insert them now.
        D_800DFBA4[4] = gMenuText[98];                                      // CONTINUE
        D_800DFBBC[0] = gMenuText[104];                                     // SORRY, BUT YOU
        D_800DFBBC[1] = gMenuText[105];                                     // CAN'T LOAD GAMES
        D_800DFBBC[2] = gMenuText[106];                                     // FOR THE SECOND
        D_800DFBBC[3] = gMenuText[107];                                     // ADVENTURE UNTIL
        D_800DFBBC[4] = gMenuText[108];                                     // YOU HAVE COMPLETED
        D_800DFBBC[5] = gMenuText[109];                                     // THE FIRST.
        D_800DFBBC[7] = gMenuText[98];                                      // CONTINUE
        gTitleMenuStrings[0] = gMenuText[137];                              // START
        gTitleMenuStrings[1] = gMenuText[36];                               // OPTIONS
        gGameSelectTextElemsNoAdv2[0].unk14_a.asciiText = gMenuText[76];    // GAME SELECT
        gGameSelectTextElemsNoAdv2[1].unk14_a.asciiText = gMenuText[76];    // GAME SELECT
        gGameSelectTextElemsNoAdv2[3].unk14_a.asciiText = gMenuText[142];   // ADVENTURE
        gGameSelectTextElemsNoAdv2[5].unk14_a.asciiText = gMenuText[144];   // TRACKS
        gGameSelectTextElemsWithAdv2[0].unk14_a.asciiText = gMenuText[76];  // GAME SELECT
        gGameSelectTextElemsWithAdv2[1].unk14_a.asciiText = gMenuText[76];  // GAME SELECT
        gGameSelectTextElemsWithAdv2[3].unk14_a.asciiText = gMenuText[142]; // ADVENTURE
        gGameSelectTextElemsWithAdv2[5].unk14_a.asciiText = gMenuText[143]; // ADVENTURE TWO
        gGameSelectTextElemsWithAdv2[7].unk14_a.asciiText = gMenuText[144]; // TRACKS
        D_800E09B0[0] = gMenuText[69];                                      // BAD CONTROLLER PAK
        D_800E09C4[0] = gMenuText[68];                                      // CONTROLLER PAK FULL
        D_800E09D8[0] = gMenuText[67];                                      // NO CONTROLLER PAK
        D_800E09EC[4] = 0;
        D_800E09EC[5] = 0;
        D_800E09EC[0] = gMenuText[184]; // CORRUPT DATA.
        //Three messages
        //If you wish to change / Controller Pak or Rumble Pak, / please do so now.
        for (i = 0; i < 2; i++) {
            D_800E09B0[i + 1] = gMenuText[177 + i];
            D_800E09C4[i + 1] = gMenuText[177 + i];
            D_800E09D8[i + 1] = gMenuText[177 + i];
            D_800E09EC[i + 1] = gMenuText[177 + i];
        }
        j = 0;
        while (D_800E09EC[j] != 0) {
            j++;
        }
        D_800E09EC[j] = gMenuText[185];                                 // TRY AGAIN!
        D_800E0A04[0] = gMenuText[159];                                 // If you wish to use
        D_800E0A04[1] = gMenuText[160];                                 // the Controller Pak
        D_800E0A04[2] = gMenuText[162];                                 // insert it now!
        D_800E0A14[0] = gMenuText[159];                                 // If you wish to use
        D_800E0A14[1] = gMenuText[161];                                 // the Rumble Pak
        D_800E0A14[2] = gMenuText[162];                                 // insert it now!
        gCautionMenuTextElements[0].unk14_a.asciiText = gMenuText[152]; // CAUTION
        gCautionMenuTextElements[1].unk14_a.asciiText = gMenuText[152]; // CAUTION
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
GLOBAL_ASM("asm/non_matchings/menu/func_80080580.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80080BC8.s")

void func_80080E6C(void) {
    D_800E1DB8 = 0;
    D_800E1DB4 = (s32)(1 - D_800E1DB4);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80080E90.s")

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
    D_80126530[0] = allocate_from_main_pool_safe(sp20 * 4, COLOR_TAG_WHITE);
    D_80126530[0] = D_80126530[0];
    D_80126530[0]->courseFlagsPtr = (u8 *)D_80126530[0] + sizeof(Settings);
    D_80126530[0]->balloonsPtr = (u8 *)D_80126530[0]->courseFlagsPtr + sp28;
    D_80126530[1] = (u8 *)D_80126530[0] + sp20;
    D_80126530[1]->courseFlagsPtr = (u8 *)D_80126530[1] + sizeof(Settings);
    D_80126530[1]->balloonsPtr = (u8 *)D_80126530[1]->courseFlagsPtr + sp28;
    D_80126530[2] = (u8 *)D_80126530[1] + sp20;
    D_80126530[2]->courseFlagsPtr = (u8 *)D_80126530[2] + sizeof(Settings);
    D_80126530[2]->balloonsPtr = (u8 *)D_80126530[2]->courseFlagsPtr + sp28;
    D_80126530[3] = (u8 *)D_80126530[2] + sp20;
    D_80126530[3]->courseFlagsPtr = (u8 *)D_80126530[3] + sizeof(Settings);
    D_80126530[3]->balloonsPtr = (u8 *)D_80126530[3]->courseFlagsPtr + sp28;
    gCheatsAssetData = get_misc_asset(0x41);
    gNumberOfCheats = (s32)(*gCheatsAssetData);
    gMenuText = allocate_from_main_pool_safe(1024 * sizeof(char *), COLOR_TAG_WHITE);
    load_menu_text(ENGLISH);
    for (i = 0; i < 128; i++) {
        D_80126550[i] = NULL;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80081218.s")
#endif

void func_800813C0(void) {
    D_800DF458 = 1;
}

/**
 * Core function for initialising all menu elements.
 * Gets the current menu ID, then runs the init function of the respective menu element.
 */
void menu_init(u32 menuId) {
    s32 i;

    gCurrentMenuId = menuId;
    reset_controller_sticks();
    gIgnorePlayerInput = 1;
    D_801263BC = 0;
    sUnused_801263C8 = 0;
    sUnused_80126828 = 0;

    // Does not match with a for loop
    i = 0;
    while (i < 4) {
        D_80126808[i++] = 0;
    }

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
        case MENU_UNKNOWN_5:
            menu_5_init();
            break;
        case MENU_RESULTS:
            menu_11_init();
            break;
        case MENU_TROPHY_RACE_ROUND:
            menu_trophy_race_round_init();
            break;
        case MENU_TROPHY_RACE_RANKINGS:
            menu_trophy_race_rankings_init();
            break;
        case MENU_UNKNOWN_23:
            menu_23_init();
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
s32 menu_loop(Gfx **arg0, s32 **arg1, s32 **arg2, s32 **arg3, s32 updateRate) {
    s32 sp1C;

    D_801263A0 = *arg0;
    D_801263A8 = *arg1;
    D_801263AC = *arg2;
    D_801263B0 = *arg3;
    update_controller_sticks();
    switch (gCurrentMenuId) {
        case MENU_LOGOS:
            sp1C = menu_logo_screen_loop(updateRate);
            break;
        case MENU_TITLE:
            sp1C = menu_title_screen_loop(updateRate);
            break;
        case MENU_OPTIONS:
            sp1C = menu_options_loop(updateRate);
            break;
        case MENU_AUDIO_OPTIONS:
            sp1C = menu_audio_options_loop(updateRate);
            break;
        case MENU_SAVE_OPTIONS:
            sp1C = menu_save_options_loop(updateRate);
            break;
        case MENU_MAGIC_CODES:
            sp1C = menu_magic_codes_loop(updateRate);
            break;
        case MENU_MAGIC_CODES_LIST:
            sp1C = menu_magic_codes_list_loop(updateRate);
            break;
        case MENU_CHARACTER_SELECT:
            sp1C = menu_character_select_loop(updateRate);
            break;
        case MENU_FILE_SELECT:
            sp1C = menu_file_select_loop(updateRate);
            break;
        case MENU_GAME_SELECT:
            sp1C = menu_game_select_loop(updateRate);
            break;
        case MENU_TRACK_SELECT:
            sp1C = menu_track_select_loop(updateRate);
            break;
        case MENU_UNKNOWN_5:
            sp1C = menu_5_loop(updateRate);
            break;
        case MENU_RESULTS:
            sp1C = menu_results_loop(updateRate);
            break;
        case MENU_TROPHY_RACE_ROUND:
            sp1C = menu_trophy_race_round_loop(updateRate);
            break;
        case MENU_TROPHY_RACE_RANKINGS:
            sp1C = menu_trophy_race_rankings_loop(updateRate);
            break;
        case MENU_UNKNOWN_23:
            sp1C = menu_23_loop(updateRate);
            break;
        case MENU_GHOST_DATA:
            sp1C = menu_ghost_data_loop(updateRate);
            break;
        case MENU_CREDITS:
            sp1C = menu_credits_loop(updateRate);
            break;
        case MENU_BOOT:
            sp1C = menu_boot_loop(updateRate);
            break;
        case MENU_CAUTION:
            sp1C = menu_caution_loop(updateRate);
            break;
    }
    *arg0 = (Gfx *)D_801263A0;
    *arg1 = (s32 *)D_801263A8;
    *arg2 = (s32 *)D_801263AC;
    *arg3 = (s32 *)D_801263B0;
    return sp1C;
}

void func_80081800(s32 arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6) {
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 phi_s6;
    s32 phi_s5;
    s32 phi_s3;
    s32 sp44;
    s32 sp40;

    sMenuGuiColourR = arg3;
    sMenuGuiColourG = arg4;
    sMenuGuiColourB = arg5;
    if (arg6 == 0) {
        gMenuImageStack[0].unk10 = arg2;
        gMenuImageStack[1].unk10 = arg2 - 2;
        phi_s3 = 0;
        phi_s5 = 1;
        arg1 -= 0x27;
        phi_s6 = 0xC;
        sp44 = 0xB;
        sp40 = 0xA;
    } else {
        gMenuImageStack[2].unk10 = arg2;
        gMenuImageStack[3].unk10 = arg2 - 1;
        phi_s3 = 2;
        phi_s5 = 3;
        arg1 -= 0x1C;
        phi_s6 = 9;
        sp44 = 9;
        sp40 = 5;
    }
    func_80059790(arg0, &sp5C, &sp58, &sp54);
    func_80068508(1);
    func_8007BF1C(0);
    gMenuImageStack[phi_s3].unk18 = sp5C / 10;
    gMenuImageStack[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += phi_s6;
    gMenuImageStack[phi_s3].unk18 = sp5C % 10;
    gMenuImageStack[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += sp44;
    gMenuImageStack[phi_s5].unkC = arg1;
    func_8009CA60(phi_s5);
    arg1 += sp40;
    gMenuImageStack[phi_s3].unk18 = sp58 / 10;
    gMenuImageStack[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += phi_s6;
    gMenuImageStack[phi_s3].unk18 = sp58 % 10;
    gMenuImageStack[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += sp44;
    gMenuImageStack[phi_s5].unkC = arg1;
    func_8009CA60(phi_s5);
    arg1 += sp40;
    gMenuImageStack[phi_s3].unk18 = sp54 / 10;
    gMenuImageStack[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += phi_s6;
    gMenuImageStack[phi_s3].unk18 = sp54 % 10;
    gMenuImageStack[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    func_80068508(0);
    func_8007BF1C(1);
    sMenuGuiColourR = (u8)0xFF;
    sMenuGuiColourG = (u8)0xFF;
    sMenuGuiColourB = (u8)0xFF;
}

GLOBAL_ASM("asm/non_matchings/menu/func_80081C04.s")

void func_80081E54(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    D_800DF798 = arg0;
    D_800DF794 = 0;
    D_80126858 = arg1 * 60.0f;
    D_8012685C = arg2 * 60.0f;
    D_80126860 = arg3 * 60.0f;
    D_80126854 = 0;
    D_800DF79C = arg4;
    D_800DF7A0 = arg5;
    if (D_80126858 > 0) {
        func_80001D04(0x16, NULL);
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_80081F4C.s")

#ifdef NON_EQUIVALENT

void draw_menu_elements(s32 arg0, MenuElement *elem, f32 arg2) {
    s32 s5;
    s32 tempX, tempY;
    s32 xPos, yPos;

    s5 = FALSE;
    if (arg0 != 4) {
        func_80067F2C(&D_801263A0, (s32 *)&D_801263A8);
        while (elem->unk14_a.element != NULL) {
            if (&D_80126850 != elem->unk14_a.element) {
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
                    yPos = tempY + elem->middle;
                }
                switch (elem->elementType) {
                    case 0:
                        set_text_background_color(elem->backgroundRed, elem->backgroundGreen, elem->backgroundBlue, elem->backgroundAlpha);
                        set_text_color(elem->filterRed, elem->filterGreen, elem->filterBlue, elem->filterAlpha, elem->opacity);
                        set_text_font(elem->textFont);
                        draw_text(&D_801263A0, xPos, yPos + D_800DF79C, elem->unk14_a.asciiText, elem->textAlignFlags);
                        break;
                    case 1:
                        if (s5) {
                            s5 = FALSE;
                            func_8007B3D0(&D_801263A0);
                        }
                        sMenuGuiOpacity = elem->opacity;
                        func_80081800(
                            *elem->unk14_a.numberU16,
                            xPos - 0xA0,
                            (-yPos - D_800DF7A0) + 0x78,
                            elem->filterRed,
                            elem->filterGreen,
                            elem->filterBlue,
                            elem->textFont);
                        break;
                    case 2:
                        if (s5) {
                            s5 = FALSE;
                            func_8007B3D0(&D_801263A0);
                        }
                        func_80081C04(
                            *elem->unk14_a.number,
                            xPos - 0xA0,
                            (-yPos - D_800DF7A0) + 0x78,
                            elem->filterRed,
                            elem->filterGreen,
                            elem->filterBlue,
                            elem->opacity,
                            elem->textFont,
                            elem->textAlignFlags);
                        break;
                    case 3:
                        s5 = TRUE;
                        render_textured_rectangle(
                            &D_801263A0,
                            elem->unk14_a.texture,
                            xPos,
                            yPos + D_800DF79C,
                            elem->filterRed,
                            elem->filterGreen,
                            elem->filterBlue,
                            elem->opacity);
                        break;
                    case 4:
                        s5 = TRUE;
                        render_texture_rectangle_scaled(
                            &D_801263A0,
                            elem->unk14_a.element,
                            xPos,
                            yPos + D_800DF79C,
                            elem->backgroundRed / 256.0f,
                            elem->backgroundGreen / 256.0f,
                            (elem->filterRed << 24) | (elem->filterGreen << 16) | (elem->filterBlue << 8) | elem->opacity,
                            elem->textAlignFlags);
                        break;
                    case 5:
                        if (s5) {
                            s5 = FALSE;
                            func_8007B3D0(&D_801263A0);
                        }
                        func_80068508(1);
                        func_8007BF1C(0);
                        gMenuImageStack[elem->unk14_a.value].unkC = xPos - 0xA0;
                        gMenuImageStack[elem->unk14_a.value].unk10 = (-yPos - D_800DF7A0) + 0x78;
                        gMenuImageStack[elem->unk14_a.value].unk18 = elem->textFont;
                        gMenuImageStack[elem->unk14_a.value].unk4 = elem->backgroundRed;
                        gMenuImageStack[elem->unk14_a.value].unk2 = elem->backgroundGreen;
                        gMenuImageStack[elem->unk14_a.value].unk0 = elem->backgroundBlue;
                        gMenuImageStack[elem->unk14_a.value].unk8 = elem->backgroundAlpha / 256.0f;
                        sMenuGuiColourR = elem->filterRed;
                        sMenuGuiColourG = elem->filterGreen;
                        sMenuGuiColourB = elem->filterBlue;
                        D_800DF4B0 = elem->filterAlpha;
                        sMenuGuiOpacity = elem->opacity;
                        func_8009CA60(elem->unk14_a.value);
                        func_80068508(0);
                        func_8007BF1C(1);
                        break;
                    case 6:
                        func_80080E90(
                            &D_801263A0,
                            xPos,
                            yPos + D_800DF7A0,
                            elem->backgroundRed,
                            elem->backgroundGreen,
                            elem->backgroundBlue,
                            elem->backgroundAlpha,
                            elem->filterRed,
                            elem->filterGreen,
                            elem->filterBlue,
                            elem->opacity);
                        break;
                    case 7:
                        func_80080580(
                            &D_801263A0,
                            xPos,
                            yPos + D_800DF7A0,
                            elem->backgroundRed,
                            elem->backgroundGreen,
                            elem->backgroundBlue,
                            elem->backgroundAlpha,
                            (elem->filterRed << 0x18) | (elem->filterGreen << 0x10) | (elem->filterBlue << 8) | elem->opacity,
                            elem->unk14_a.element);
                        break;
                }
            }
            elem++; // Go onto the next element.
        }
        if (s5) {
            func_8007B3D0(&D_801263A0);
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
            settings->courseFlagsPtr[i] |= D_80126530[numWorlds]->courseFlagsPtr[i];
        }
    }

    settings->trophies = 0;
    settings->keys = 0;
    settings->bosses = 0;
    settings->cutsceneFlags = 0;
    for (i = 0; i < 3; i++) {
        settings->trophies |= D_80126530[i]->trophies;
        settings->keys |= D_80126530[i]->keys;
        settings->bosses |= D_80126530[i]->bosses;
        settings->cutsceneFlags |= D_80126530[i]->cutsceneFlags;
    }
}

void print_missing_controller_text(Gfx *dl, s32 updateRate) {
    s32 posY;

    D_800DF46C += updateRate;

    if (D_800DF46C & 0x10) {
        load_menu_text(get_language());
        set_text_font(FONT_COLOURFUL);
        set_text_color(255, 255, 255, 0, 0xFF);
        set_text_background_color(0, 0, 0, 0);
        posY = 208;
        if (osTvType == TV_TYPE_PAL) {
            posY = 234;
        }
        draw_text(dl, POS_CENTRED, posY, gMenuText[151], 0xC);
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
        func_80066940(0, 0, 38, SCREEN_WIDTH, SCREEN_HEIGHT - 16);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT + 44);
    } else {
        func_80066940(0, 0, 40, SCREEN_WIDTH, SCREEN_HEIGHT - 44);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    func_80066610();
    func_80066818(0, 1);
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
            func_800C01D8(&D_800E1DE8);
            gMenuDelay = 1;
        }
        sBootScreenTimer -= updateRate / 50.0f;
    } else {
        yOffset = 0;
        if (sBootScreenTimer < 2.17f && gMenuDelay == 0) {
            func_800C01D8(&D_800E1DE8);
            gMenuDelay = 1;
        }
        sBootScreenTimer -= updateRate / 60.0f;
    }
    if (sBootScreenTimer <= 0.0f) {
        func_80066894(0, 0);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, VIEWPORT_AUTO, VIEWPORT_AUTO);
        init_title_screen_variables();
        menu_init(MENU_TITLE);
    }
// This uses doubles instead of floats for precision in the counting.
    if (sBootScreenTimer < 8.5) {
        set_text_font(FONT_SMALL);
        set_text_background_color(0, 0, 0, 0);
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
            set_text_color(0xFF, 0xFF, 0, 0xFF, opacity);
            draw_text(&D_801263A0, 159, yOffset + 212, gRareCopyrightString, 0xC);
            draw_text(&D_801263A0, 161, yOffset + 212, gRareCopyrightString, 0xC);
            draw_text(&D_801263A0, POS_CENTRED, yOffset + 211, gRareCopyrightString, 0xC);
            draw_text(&D_801263A0, POS_CENTRED, yOffset + 213, gRareCopyrightString, 0xC);
        }
        yOffsetShadow = yOffset + 212;
        if (sBootScreenTimer > 8.0) {
            opacity = (8.5 - sBootScreenTimer) * 510.0;
        } else {
            opacity = 0xFF;
        }
        set_text_color(0xFF, 0xFF, 0xFF, 0xFF, opacity);
        draw_text(&D_801263A0, POS_CENTRED, yOffsetShadow, gRareCopyrightString, 0xC);
    }
    return 0;
}

/**
 * Sets some things needed after the title screen from the save buffer.
 */
void init_title_screen_variables(void) {
    if (sEepromSettings & 2) {
        set_magic_code_flags(2);
    }
    if ((sEepromSettings & 0xFFFFF0) == 0xFFFFF0) {
        set_magic_code_flags(1);
    }
    if (sEepromSettings & 1) {
        gIsInAdventureTwo = 1;
    } else {
        gIsInAdventureTwo = 0;
    }
    if ((sEepromSettings & 0x2000000) == 0) {
        func_800C2AF4(0);
    }
    load_menu_text(get_language());
}

GLOBAL_ASM("asm/non_matchings/menu/func_80083098.s")

void menu_title_screen_init(void) {
    s32 i;
    s32 temp;
    UNUSED s8 *tempArr;

    D_800DF488 = 1;
    D_801263BC = 0;
    gMenuDelay = 0;
    reset_character_id_slots();
    gSaveFileIndex = 0;
    gTitleScreenCurrentOption = 0;
    gNumberOfActivePlayers = 4;
    initialise_player_ids();
    play_music(1);
    sMenuMusicVolume = musicGetRelativeVolume();
    if (D_800DF458) {
        D_8012686C = 0;
        D_800DF458 = 0;
    } else {
        D_8012686C = 1;
    }
    D_80126870 = 0;
    D_801263E0 = 0;
    func_8009C674(sGameTitleTileTextures);
    for (i = 0; i < 11; i++) {
        sGameTitleTileOffsets[i].texture = D_80126550[sGameTitleTileTextures[i]];
    }
    set_music_player_voice_limit(0x1B);
    func_800660C0();
    set_text_font(FONT_COLOURFUL);
    func_800C4170(2);
    func_80000890(0);
    set_time_trial_enabled(FALSE);
    D_80126864 = 0;
    D_80126874 = get_misc_asset(0x42);
    temp = D_80126874[1];
    D_80126868 = 0;
    if (temp == -2) {
        temp = 0;
        D_80126868 = 0x258;
    }
    load_level_for_menu(D_80126874[0], temp, D_80126874[2]);
    D_801268D8 = 0;
    D_801268E0 = 0;
    D_801268DC = 0;
    D_800DF9F4 = 0;
    D_801263D8 = 0;
    gIsInTracksMode = FALSE;
}

GLOBAL_ASM("asm/non_matchings/menu/func_8008377C.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_title_screen_loop.s")

void func_80084118(void) {
    func_8009C4A8(sGameTitleTileTextures);
    set_music_player_voice_limit(0x10);
    func_800660D0();
    func_800C422C(2);
    func_80000890(1);
}

void menu_options_init(void) {
    D_801263BC = 0;
    gMenuDelay = 0;
    func_800C01D8(&sMenuTransitionFadeOut);
    func_800C4170(2);
    set_text_font(FONT_LARGE);
    set_music_player_voice_limit(0x18);
    play_music(0x18);
    func_80000B18();
}

//Draws options menu screen
void func_800841B8(UNUSED s32 arg0) {
    s32 optionMenuTextIndex;
    s32 alpha;
    s32 yPos;

    set_text_font(FONT_LARGE);
    set_text_background_color(0, 0, 0, 0);
    set_text_color(0, 0, 0, 255, 128);
    draw_text(&D_801263A0, 161, 35, gMenuText[36], 0xC); // OPTIONS
    set_text_color(255, 255, 255, 0, 255);
    draw_text(&D_801263A0, 160, 32, gMenuText[36], 0xC); // OPTIONS

    optionMenuTextIndex = 0;
    yPos = 76;

    set_text_font(FONT_COLOURFUL);

    while (gOptionMenuStrings[optionMenuTextIndex] != NULL) {
        if (optionMenuTextIndex == D_800DF460) {
            alpha = D_801263BC * 8;
            if (D_801263BC >= 32) {
                alpha = 511 - alpha;
            }
        } else {
            alpha = 0;
        }
        set_text_color(255, 255, 255, alpha, 255);
        draw_text(&D_801263A0, POS_CENTRED, yPos, gOptionMenuStrings[optionMenuTextIndex], 0xC);

        optionMenuTextIndex++;
        yPos += 28;
    }
}

#ifdef NON_EQUIVALENT
s32 menu_options_loop(s32 arg0) {
    s32 buttonsPressed;
    s32 analogX;
    s32 analogY;

    D_801263BC = (D_801263BC + arg0) & 0x3F;

    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += arg0;
        } else {
            gMenuDelay -= arg0;
        }
    }

    if (gMenuDelay >= -19 && gMenuDelay < 35) {
        func_800841B8(arg0);
    }

    buttonsPressed = 0;
    analogX = 0;
    analogY = 0;
    if (gIgnorePlayerInput == 0 && gMenuDelay == 0) {
        // Get input from all 4 controllers.
        s32 i;
        for (i = 0; i < 4; i++) {
            analogY += gControllersYAxisDirection[i];             // Y axis (-1 = down, 1 = up) for controller
            analogX += gControllersXAxisDirection[i];             // X axis (-1 = left, 1 = right) for controller
            buttonsPressed |= get_buttons_pressed_from_player(i); // Button presses for controller
        }
    }

    if ((buttonsPressed & B_BUTTON) || ((buttonsPressed & (A_BUTTON | START_BUTTON)) && D_800DF460 == 5)) {
        // Leave the option menu
        set_music_fade_timer(-128);
        gMenuDelay = -1;
        func_800C01D8(&sMenuTransitionFadeIn);
        func_80001D04(0x241, 0);
    } else if ((buttonsPressed & (A_BUTTON | START_BUTTON)) && D_800DF460 >= 2) {
        // Go to a sub-menu
        gMenuDelay = 31;
        func_80001D04(0xEF, 0);
    } else if (D_800DF460 == 0 && analogX != 0) {
        // Change language
        s32 currentLang = get_language();
        if ((currentLang >> 31) == 0 && currentLang == ENGLISH) {
            set_language(FRENCH);
        } else {
            set_language(ENGLISH);
        }
        func_80001D04(0xEB, 0);
    } else if (D_800DF460 == 1 && analogX != 0) {
        // Enable/Disable subtitles.
        if (sEepromSettings & 0x2000000) {
            func_80001D04(0xEB, NULL);
            unset_eeprom_settings_value(0);
            func_800C2AF4(0);
            gOptionMenuStrings[1] = gMenuText[183];
        } else {
            func_80001D04(0xEB, 0);
            set_eeprom_settings_value(0);
            func_800C2AF4(1);
            gOptionMenuStrings[1] = gMenuText[182];
        }
    } else {
        // Move up & down the list
        if (analogY < 0) {
            // Scroll down the list.
            D_800DF460++;
            if (D_800DF460 >= 6) {
                D_800DF460 = 5;
            }
            func_80001D04(0xEB, 0);
        }
        if (analogY > 0) {
            // Scroll up the list.
            D_800DF460--;
            if (D_800DF460 < 0) {
                D_800DF460 = 0;
            }
            func_80001D04(0xEB, 0);
        }
    }

    if (gMenuDelay >= 31) {
        // Change screen to a sub-menu
        if (D_800DF460 == 2) {
            func_80084734();
            menu_init(MENU_AUDIO_OPTIONS);
            return 0;
        }
        if (D_800DF460 == 3) {
            func_80084734();
            menu_init(MENU_SAVE_OPTIONS);
            return 0;
        }
        func_80084734();
        menu_init(MENU_MAGIC_CODES);
        return 0;
    }
    if (gMenuDelay < -30) {
        // Change screen back to the title screen.
        func_80000B28();
        func_80084734();
        menu_init(MENU_TITLE);
        return 0;
    }
    gIgnorePlayerInput = 0;
    return 0;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_options_loop.s")
#endif

void func_80084734(void) {
    func_800C422C(2);
}

void menu_audio_options_init(void) {
    gOptionsMenuItemIndex = 0;
    D_801263BC = 0;
    gMenuDelay = 0;
    D_801269FC = NULL;
    D_801263D8 = -1;
    func_8009C674(gOptionMenuTextures);
    allocate_menu_images(&gOptionMenuTextures[6]);
    func_8008E4B0();
    func_800C01D8(&sMenuTransitionFadeOut);
    func_8007FFEC(2);
    gMusicVolumeSliderValue = musicGetVolSliderPercentage();
    gSfxVolumeSliderValue = sfxGetVolumeSlider();
    if (gActiveMagicCodes & CHEAT_MUSIC_MENU) { // Check if "JUKEBOX" cheat is active
        gAudioMenuStrings[6].unkC = gMusicTestString;
        gAudioMenuStrings[3].unk2 = 0xD4;
        set_music_player_voice_limit(0x20);
        D_801263E0 = 5;
    } else {
        gAudioMenuStrings[6].unkC = NULL;
        gAudioMenuStrings[3].unk2 = 0xC0;
        D_801263E0 = 4;
    }
    func_800C4170(2);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80084854.s")

#ifdef NON_EQUIVALENT

// Almost matching, should be functionally equivalent
s32 menu_audio_options_loop(s32 arg0) {
    s32 buttonInputs;
    s32 sp30;
    s32 phi_a2;
    s32 contY;
    s32 contX;
    s32 i;

    sp30 = 0;
    D_801263BC = (s32)((D_801263BC + arg0) & 0x3F);
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += arg0;
        } else {
            gMenuDelay -= arg0;
        }
    }
    if (gMenuDelay >= -0x13 && gMenuDelay < 0x14) {
        func_80084854();
    }
    if (gIgnorePlayerInput == 0 && gMenuDelay == 0) {
        buttonInputs = 0;
        contX = 0;
        contY = 0;
        phi_a2 = 0;

        // Check all 4 controllers for inputs
        for (i = 0; i < 4; i++) {
            buttonInputs |= get_buttons_pressed_from_player(i);
            phi_a2 += clamp_joystick_x_axis(i);
            contY += gControllersYAxisDirection[i];
            contX += gControllersXAxisDirection[i];
        }

        if (phi_a2 < 0) {
            phi_a2 += 0x18;
            if (phi_a2 > 0) {
                phi_a2 = 0;
            }
        } else {
            phi_a2 -= 0x18;
            if (phi_a2 < 0) {
                phi_a2 = 0;
            }
        }

        if (((buttonInputs & (A_BUTTON | START_BUTTON)) && (D_801263E0 == gOptionsMenuItemIndex + 1)) || (buttonInputs & B_BUTTON)) {
            gMenuDelay = -1;
            func_800C01D8(&sMenuTransitionFadeIn);
            if (D_801263D8 >= 0) {
                set_music_fade_timer(-0x80);
            }
            sp30 = 3;
        } else if (contY < 0 && gOptionsMenuItemIndex < D_801263E0 - 1) {
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
            if (D_800DFAC8 > 2) {
                D_800DFAC8 = 0;
            }
            set_stereo_pan_mode(D_800DFAC8);
            sp30 = 1;
        } else if (((phi_a2 >> 2) != 0) && ((gOptionsMenuItemIndex == 1) || (gOptionsMenuItemIndex == 2))) {
            if (gOptionsMenuItemIndex == 1) {
                gSfxVolumeSliderValue += (phi_a2 >> 2);
                if (gSfxVolumeSliderValue < 0) {
                    gSfxVolumeSliderValue = 0;
                } else if (gSfxVolumeSliderValue >= 0x101) {
                    gSfxVolumeSliderValue = 0x100;
                }
                set_sfx_volume_slider(gSfxVolumeSliderValue);
            } else if (gOptionsMenuItemIndex == 2) {
                gMusicVolumeSliderValue += (phi_a2 >> 2);
                if (gMusicVolumeSliderValue < 0) {
                    gMusicVolumeSliderValue = 0;
                } else {
                    if (gMusicVolumeSliderValue >= 0x101) {
                        gMusicVolumeSliderValue = 0x100;
                    }
                }
                set_music_volume_slider(gMusicVolumeSliderValue);
                if (!music_is_playing()) {
                    if (D_801263D8 >= 0) {
                        func_80000B28();
                        play_music((u8)D_800DFABC);
                    } else {
                        func_80000B28();
                        set_music_player_voice_limit(0x18);
                        play_music(0x18);
                        func_80000B18();
                    }
                }
            }
        } else if (D_801263E0 >= 5 && gOptionsMenuItemIndex == 3) {
            if (contX < 0 && D_800DFABC > 0) {
                D_800DFABC--;
                sp30 = 1;
            } else if (contX > 0 && D_800DFABC < (ALSeqFile_80115CF8_GetSeqCount() - 1)) {
                D_800DFABC++;
                sp30 = 1;
            }
            if (buttonInputs & (A_BUTTON | START_BUTTON)) {
                func_80000B28();
                set_music_player_voice_limit(0x18);
                play_music((u8)D_800DFABC);
                D_801263D8 = D_800DFABC;
            }
        }

        if (gOptionsMenuItemIndex == 1 && D_801269FC == NULL) {
            func_80001D04(0x19B, &D_801269FC);
        } else if (D_801269FC != NULL) {
            func_8000488C(&D_801269FC);
        }

        if (sp30 == 3) {
            func_80001D04(0x241, NULL);
        } else if (sp30 == 2) {
            func_80001D04(0xEF, NULL);
        } else if (sp30 == 1) {
            func_80001D04(0xEB, NULL);
        }
    }
    if (gMenuDelay < -0x1E) {
        func_800851FC();
        menu_init(0xC);
        return 0;
    }
    gIgnorePlayerInput = 0;
    return 0;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_audio_options_loop.s")
#endif

void func_800851FC(void) {
    if (D_801269FC != NULL) {
        func_8000488C(D_801269FC);
    }
    if (D_801263D8 >= 0) {
        set_music_player_voice_limit(0x18);
        play_music(0x18);
        set_music_fade_timer(0x100);
        func_80000B18();
    }
    func_8009C4A8(gOptionMenuTextures);
    func_800C422C(2);
}

void menu_save_options_init(void) {
    D_80126A6C = 1;
    D_80126A10 = 0;
    D_80126A18 = 1;
    D_80126A1C = 1;
    gOptionsMenuItemIndex = 0;
    D_801263BC = 0;
    gMenuDelay = 0;
    D_801263E0 = 1;
    D_801263D8 = 0;
    D_80126A64 = (s32)allocate_from_main_pool_safe(0x800, COLOR_TAG_WHITE);
    D_80126A0C = (s32)allocate_from_main_pool_safe(0xA00, COLOR_TAG_WHITE);
    D_80126A04 = (s32)(D_80126A0C + 0x500);
    D_80126A08 = 0;
    D_80126BD4 = 0;
    D_80126BDC = 0.0f;
    D_80126A00 = 0;
    D_80126BE4 = 0;
    D_80126BEC = 0.0f;
    func_8009C674(D_800DFC78);
    allocate_menu_images(D_800DFCAC);
    func_8007FFEC(0xA);
    func_800C4170(2);
    D_800DFC10[0].texture = D_80126550[71];
    D_800DFC20[0].texture = D_80126550[72];
    D_800DFC30[0].texture = D_80126550[75];
    D_800DFC40[0].texture = D_80126550[74];
    D_800DFC50[0].texture = D_80126550[73];
    D_800DFC60[0].texture = D_80126550[70];
    func_8008E4B0();
    func_8006EBA8();
    func_800C01D8(&sMenuTransitionFadeOut);
}

GLOBAL_ASM("asm/non_matchings/menu/func_800853D0.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80085B9C.s")

s32 func_800860A8(s32 controllerIndex, s32 *arg1, unk800860A8 *arg2, s32 *arg3, s32 arg4) {
    s32 ret = 0;
    
    if (*arg1 != 0) {
        ret = get_free_space(controllerIndex, &arg2[*arg3].unkC, &D_80126A20[controllerIndex]);
        if (ret == 0) {
            if ((arg2[*arg3].unkC >= arg4) && (D_80126A20[controllerIndex] > 0)) {
                arg2[*arg3].unk0 = 8;
                arg2[*arg3].unk6 = controllerIndex;
                (*arg3)++;
            }
        } else {
            if ((*arg1 < 0) && ((ret & 0xFF) == 7)) {
                *arg1 = 0;
                ret = 0;
            } else {
                s32 temp_v1;
                temp_v1 = ret & 0xFF;
                if (temp_v1 != 3 && temp_v1 != 2 && temp_v1 != 9) {
                    ret = 0;
                }
            }
        }
    }

    return ret;
}

void func_800861C8(unk800861C8 *arg0, s32 *arg1) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (D_80126530[i]->newGame != 0) {
            arg0[*arg1].unk0 = 1;
            arg0[*arg1].unk1 = 0;
            arg0[*arg1].unk2 = 0;
            arg0[*arg1].unk6 = i;
            arg0[*arg1].unkC = get_game_data_file_size();
            (*arg1)++;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_800862C4.s")
GLOBAL_ASM("asm/non_matchings/menu/func_800867D4.s")

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
        if (D_801263E0 > 0 && D_80126A00 > 0) {
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
        D_801263E0 = 0;
        if (D_80126A10 != D_80126A14) {
            func_800871D8(8);
        } else {
            func_80001D04(0x241, NULL);
            ret = -1;
        }
    } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        func_80001D04(0xEF, NULL);
        D_801263E0 = 4;
    } else if ((arg1 < 0) && (D_80126BD4 > 0)) {
        func_80001D04(0xEB, NULL);
        D_80126BD4--;
    } else if ((arg1 > 0) && (D_80126BD4 < (D_80126A08 - 1))) {
        func_80001D04(0xEB, NULL);
        D_80126BD4++;
    }
    return ret;
}

s32 func_800875E4(s32 buttonsPressed, s32 arg1) {
    if (buttonsPressed & B_BUTTON) {
        func_80001D04(0x241, NULL);
        D_801263E0 = 3;
    } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        func_80001D04(0xEF, NULL);
        D_801263E0 = 6;
    } else if ((arg1 < 0) && (D_80126BE4 > 0)) {
        func_80001D04(0xEB, NULL);
        D_80126BE4--;
    } else if ((arg1 > 0) && (D_80126BE4 < D_80126A00 - 1)) {
        func_80001D04(0xEB, NULL);
        D_80126BE4++;
    }

    return 0;
}

s32 func_800876CC(s32 buttonsPressed, UNUSED s32 arg1) {
    if (buttonsPressed & B_BUTTON) {
        func_80001D04(0x241, NULL);
        D_801263E0 = 5;
    } else if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
        func_80001D04(0xEF, NULL);
        D_801263E0 = 7;
        D_801263D8 = 0;
    }

    return 0;
}

GLOBAL_ASM("asm/non_matchings/menu/func_80087734.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_save_options_loop.s")

void func_80087EB8(void) {
    func_800C422C(2);
    func_8007FF88();
    func_8009C4A8(D_800DFC78);
    assign_dialogue_box_id(7);
    free_from_memory_pool(D_80126A0C);
    free_from_memory_pool(D_80126A64);
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

        func_80076164(); //Free D_800DE440 from memory
        get_free_space(*controllerIndex, &sCurrentControllerPakFreeSpace, NULL); //Get Available Space in Controller Pak
        sCurrentControllerPakFreeSpace = sCurrentControllerPakFreeSpace / 256; //Bytes
        ret = pakStatus; //Really?
    }

    return ret;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80087F14.s")
#endif
GLOBAL_ASM("asm/non_matchings/menu/func_8008832C.s")

void menu_boot_init(void) {
    s32 i;

    func_800C01D8(&sMenuTransitionFadeOut);
    set_background_prim_colour(0, 0, 0);
    func_8009C674(&sGameTitleTileTextures);

    // Sets up the 11 texture pointers for the "Diddy Kong Racing" logo.
    for (i = 0; i < 11; i++) {
        sGameTitleTileOffsets[i].texture = D_80126550[sGameTitleTileTextures[i]];
    }

    // Reset variables for menu_boot_loop()
    D_80126C20 = 0; // D_80126C20 is the current state of the boot screen. Either 0, 1, or 2.
    D_80126C18 = 0; // D_80126C18 is a timer for the boot screen, counts up to 0x8C frames.
}

s32 menu_boot_loop(s32 arg0) {
    s32 out;
    s32 temp;
    s32 y;

    out = 0;

    y = 120;
    if (osTvType == TV_TYPE_PAL) {
        y = 132;
    }
    
    temp = y;

    switch (D_80126C20) {
        case 0:
            if (D_80126C18 < 32) {
                D_80126C18 += arg0;
                if (D_80126C18 >= 33) {
                    D_80126C18 = 32;
                }
            } else {
                func_800887E8();
                D_80126C20 = 1;
            }
            break;
        case 1:
            if (D_80126C18 < 140) {
                D_80126C18 += arg0;
                if (D_80126C18 >= 141) {
                    D_80126C18 = 140;
                }
            } else {
                func_800887C4();
                D_80126C20 = 2;
            }
            if (D_80126C18 >= 129) {
                temp = 300;
            }
            break;
        case 2:
            if (gMenuDelay && func_800C018C() == 0) {
                func_800C01D8(&sMenuTransitionFadeInFast);
            }
            temp = 300;
            out = func_800890AC(arg0);
            break;
    }

    if (temp < 300) {
        render_textured_rectangle(&D_801263A0, &sGameTitleTileOffsets, 160, temp, 255, 255, 255, 255);
        func_8007B3D0(&D_801263A0);
    }

    return out;
}

void func_800887C4(void) {
    func_8009C4A8((s16 *)sGameTitleTileTextures);
}

void func_800887E8(void) {
    s32 i;

    // Starting point
    D_80126AA0[0] = allocate_from_main_pool_safe(0x200, COLOR_TAG_WHITE);

    // Fills in the table.
    for (i = 1; i < 16; i++) {
        D_80126AA0[i] = (s32 *)(((u32)D_80126AA0[0]) + (i * 0x20));
    }

    for (i = 0; i < 1; i++) {
        sControllerPakDataPresent[i] = 0;
    }

    D_80126C10 = 0;
    D_801263E0 = 0;
    D_801263BC = 0;
    D_80126A68 = -1;
    load_menu_text(get_language());
    if (func_80087F14(&D_80126A68, 0) == 0) {
        gMenuDelay = 0;
    } else if (func_8008832C() == 0) {
        gMenuDelay = 0x14;
    }
    if (D_80126BC8 == 0 && !gShowControllerPakMenu) {
        gMenuDelay = 0x14;
    }
    D_800DF460 = 0;
    D_801263D8 = 0;
    func_8009C6D4(0x3F);
    func_8008E4B0();
    if (osTvType == TV_TYPE_PAL) {
        D_80126BB4 = 8;
    } else {
        D_80126BB4 = 7;
    }
    func_800C4170(2);
}

#ifdef NON_EQUIVALENT
void func_80088938(s32 arg0) {
    s32 alpha;
    s32 i;
    s8* phi_s2;
    s8* phi_s0;
    s8* phi_s4;
    s32 phi_s3 = 1;
    s32 yPos = 48;
    //s32 yPos;

    set_text_background_color(0, 0, 0, 0);
    alpha = D_801263BC << 3;
    if (alpha >= 256) {
        alpha = 511 - alpha;
    }
    if (D_80126BC8 != 0) {
        draw_menu_elements(1, D_800DFCB4, 1.0f);
    } else if (gShowControllerPakMenu != 0) {
        set_text_font(2);
        set_text_color(0, 0, 0, 255, 128);
        draw_text(&D_801263A0, 161, 33, gMenuText[35], 12);
        set_text_color(255, 255, 255, 0, 255);
        draw_text(&D_801263A0, 160, 30, gMenuText[35], 12);
        assign_dialogue_box_id(6);
        
        //HERE!
        set_current_dialogue_box_coords(6, 58, yPos, 262, yPos + 30);
        

        if (D_800DF460 == -1) {
            set_current_dialogue_background_colour(6, 255, 255, 255, (alpha >> 1) + 128);
        } else {
            set_current_dialogue_background_colour(6, 96, 192, 92, 224);
        }

        set_dialogue_font(6, 0);
        set_current_text_colour(6, 255, 255, 255, 0, 255);
        set_current_text_background_colour(6, 0, 0, 0, 0);
        render_dialogue_text(6, POS_CENTRED, 2, gMenuText[86 + D_80126A68], phi_s3, 4);
        render_dialogue_text(6, POS_CENTRED, 16, gMenuText[114], sCurrentControllerPakFreeSpace, 4);
        render_dialogue_box(&D_801263A0, NULL, NULL, 6);

        //HERE!
        yPos += 34; //To 82

        set_dialogue_font(6, 1);
        set_current_text_background_colour(6, 0, 0, 0, 0);
        for (i = -1; i < D_80126BB4; i++) {
            assign_dialogue_box_id(6);
            set_current_dialogue_box_coords(6, 28, yPos, 292, yPos + 14);
            if (i < 0) {
                set_current_dialogue_background_colour(6, 224, 48, 48, 224);
                set_current_text_colour(6, 224, 224, 48, 255, 255);
                phi_s2 = gMenuText[115];
                phi_s0 = gMenuText[116];
                phi_s4 = gMenuText[117];
                phi_s3 = 1;
            } else {
                phi_s2 = &D_800E820C;
                phi_s4 = &D_800E820C;
                if (D_800DF460 == (i + D_801263D8)) {
                    set_current_dialogue_background_colour(6, 255, 255, 255, (alpha >> 1) + 128);
                } else {
                    set_current_dialogue_background_colour(6, 224, 224, 48, 224);
                }
                set_current_text_colour(6, 16, 16, 160, 255, 255);
                phi_s0 = D_80126AA0[D_801263D8 + i];
                phi_s3 = (s32) (&sCurrentControllerPakAllFileSizes)[D_801263D8 + i];
            }
            render_dialogue_text(6, 26, 2, phi_s2, D_801263D8 + i + 1, 4);
            render_dialogue_text(6, 56, 2, phi_s0, 1, 0);
            render_dialogue_text(6, 240, 2, phi_s4, phi_s3, 4);
            render_dialogue_box(&D_801263A0, NULL, NULL, 6);
            yPos += 16;
        }
        if (D_801263D8 < (16 - D_80126BB4)) {
            if ((D_801263BC & 8) != 0) {
                render_textured_rectangle(&D_801263A0, (DrawTexture* ) &D_800E043C, 160, yPos + 8, (u8) 255, (u8) 255, (u8) 255, (u8) 255);
                func_8007B3D0(&D_801263A0);
            }
        } else {
            set_text_font(0);
            if (D_800DF460 == 16) {
                set_text_color(255, 255, 255, alpha, 255);
            } else {
                set_text_color(255, 255, 255, 0, 255);
            }
            draw_text(&D_801263A0, POS_CENTRED, yPos, gMenuText[51], 4);
        }
        if ((D_801263E0 != 0) && (D_80126C10 == 0)) {
            if (osTvType == TV_TYPE_PAL) {
                yPos = 134;
            } else {
                yPos = 120;
            }
            assign_dialogue_box_id(6);
            set_dialogue_font(6, 0);
            set_current_dialogue_box_coords(6, 76, yPos - 28, 244, yPos + 28);
            set_current_dialogue_background_colour(6, 0, 0, 0, 160);
            
            for (yPos = 4, i = 0; i < 3; i++) {
                if (i == 0) {
                    set_current_text_colour(6, 255, 0, 255, 64, 255);
                } else if (i == D_801263E0) {
                    set_current_text_colour(6, 255, 255, 255, alpha, 255);
                } else {
                    set_current_text_colour(6, 255, 255, 255, 0, 255);
                }
                render_dialogue_text(6, POS_CENTRED, yPos, gMenuText[111 + i], D_800DF460 + 1, 4);
                if (i != 0) {
                    yPos += 16;
                } else {
                    yPos += 20;
                }
            }
            render_dialogue_box(&D_801263A0, NULL, NULL, 6);
        }
        if (D_80126C10 != 0) {
            set_text_color(255, 255, 255, 0, 255);
            set_text_font(2);
            draw_text(&D_801263A0, 160, 128, gMenuText[124], 12);
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80088938.s")
#endif
GLOBAL_ASM("asm/non_matchings/menu/func_800890AC.s")

void func_800895A4(void) {
    func_8009C508(0x3F);
    free_from_memory_pool(D_80126AA0[0]);
    func_800C422C(2);
}

void menu_magic_codes_init(void) {
    gCheatInputCurrentRow = 0;
    gCheatInputCurrentColumn = 0;
    gOptionsMenuItemIndex = 0;
    gCheatInputStringLength = 0;
    sUnused_80126470 = 0;
    D_80126C4C = -1;
    D_80126C58[0] = 0;
    D_801263BC = 0;
    gMenuDelay = 0;
    D_801263D8 = 0;
    D_801263E0 = 0;
    func_800C01D8(&sMenuTransitionFadeOut);
    set_current_dialogue_box_coords(7, 0x32, 0x32, 0x10E, 0x84);
    set_current_dialogue_background_colour(7, 0, 0, 0, 0x80);
    assign_dialogue_box_id(7);
    func_800C4170(2);
}

#ifdef NON_EQUIVALENT

// Close to matching, but should be functionally equivalent.
void render_magic_codes_ui(s32 arg0) {
    s32 xPos, yPos;
    s32 yIncr;
    s32 i, j;
    s32 temp, alpha, green;
    char c;

    set_text_background_color(0, 0, 0, 0);
    render_dialogue_box(&D_801263A0, 0, 0, 7);
    set_text_font(FONT_LARGE);
    set_text_color(0, 0, 0, 0xFF, 0x80);
    draw_text(&D_801263A0, 0xA1, 0x23, gMenuText[17], 0xC); // gMenuText[17] = "MAGIC CODES"
    set_text_color(0xFF, 0xFF, 0xFF, 0, 0xFF);
    draw_text(&D_801263A0, 0xA0, 0x20, gMenuText[17], 0xC); // gMenuText[17] = "MAGIC CODES"
    set_text_font(FONT_COLOURFUL);
    set_text_color(0xFF, 0xFF, 0xFF, 0, 0xFF);

    c = 'A';
    yPos = 60;
    // Draw the input table
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 7; j++) {
            xPos = 64 + (j * 32);
            if (gOptionsMenuItemIndex == 5 && j == gCheatInputCurrentColumn && i == gCheatInputCurrentRow) {
                temp = D_801263BC * 8;
                if (temp >= 0x100) {
                    temp = 0x1FF - temp;
                }
                set_text_color(0x80, 0xFF, 0xC0, (temp >> 1) + 0x80, 0xFF);
            }
            if (c < '[') {
                draw_text(&D_801263A0, xPos, yPos, &c, 0xC); // Draw the character
            } else if (j == 5) {
                draw_text(&D_801263A0, xPos, yPos, &D_800E8210, 0xC); // D_800E8210 = "DEL"
            } else {
                draw_text(&D_801263A0, xPos, yPos, &D_800E8214, 0xC); // D_800E8214 = "OK"
            }
            if ((5 == gOptionsMenuItemIndex) && (j == gCheatInputCurrentColumn) && (i == gCheatInputCurrentRow)) {
                set_text_color(0xFF, 0xFF, 0xFF, 0, 0xFF);
            }
            c++;
            c &= 0xFF;
        }
        yPos += 0x16;
    }

    temp = D_801263BC * 8;
    if (temp >= 0x100) {
        temp = 0x1FF - temp;
    }

    set_text_font(FONT_COLOURFUL);
    yPos = 0xA4;
    yIncr = 16;
    if (osTvType == TV_TYPE_PAL) {
        yIncr = 24;
    }

    for (i = 0; gMagicCodeMenuStrings[i] != NULL; i++) {
        alpha = 0;
        if (i == gOptionsMenuItemIndex && D_801263E0 == 0) {
            alpha = temp;
        }
        set_text_color(0xFF, 0xFF, 0xFF, alpha, 0xFF);
        draw_text(&D_801263A0, POS_CENTRED, yPos, gMagicCodeMenuStrings[i], 0xC);
        yPos += yIncr;
    }
    set_text_font(FONT_COLOURFUL);
    set_text_color(0xFF, 0xFF, 0x80, 0x80, 0xFF);
    set_text_background_color(0, 0, 0x80, 0x80);
    if (gOptionsMenuItemIndex == 4) {
        if (D_80126C4C == -1) {
            draw_text(&D_801263A0, POS_CENTRED, 0x90, gMenuText[18], 0xC); // gMenuText[18] = "Sorry, the code was incorrect"
        } else {
            // Draw cheat code name.
            draw_text(&D_801263A0, POS_CENTRED, 0x90, (char *)(*gCheatsAssetData) + (*gCheatsAssetData + 1)[D_80126C4C + 1], 0xC);
        }
    } else if (5 == gOptionsMenuItemIndex) {
        draw_text(&D_801263A0, POS_CENTRED, 0x90, D_80126C58, 0xC);
    } else if (gOptionsMenuItemIndex == 6) {
        draw_text(&D_801263A0, POS_CENTRED, 0x90, gMenuText[19], 0xC); // gMenuText[19] = "All cheats have been deleted"
    }
    if (D_801263E0 != 0) {
        yPos = 0x78;
        if (osTvType == TV_TYPE_PAL) {
            yPos = 0x86;
        }
        assign_dialogue_box_id(6);
        set_dialogue_font(6, FONT_COLOURFUL);
        set_current_dialogue_box_coords(6, 0x4C, yPos - 0x1C, 0xF4, yPos + 0x1C);
        set_current_dialogue_background_colour(6, 0, 0, 0, 0xA0);
        yPos = 4;
        for (i = 0; i < 3; i++) {
            alpha = 0;
            green = 0xFF;
            if (i == 0) {
                alpha = 64;
                green = 0;
            } else if (i == D_801263E0) {
                alpha = temp;
            }
            set_current_text_colour(6, 0xFF, green, 0xFF, alpha, 0xFF);

            // gMenuText[148] = "CLEAR ALL CODES?", [149] = "OK", [150] = "CANCEL"
            render_dialogue_text(6, POS_CENTRED, yPos, gMenuText[148 + i], 1, 4);

            if (i != 0) {
                yPos += 0x10;
            } else {
                yPos += 0x14;
            }
        }
        render_dialogue_box(&D_801263A0, 0, 0, 6);
    }
    if ((get_filtered_cheats() << 3) < 0) {
        calculate_and_display_rom_checksum();
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/render_magic_codes_ui.s")
#endif

GLOBAL_ASM("asm/non_matchings/menu/menu_magic_codes_loop.s")

void func_8008A4C8(void) {
    func_800C422C(2);
}

void menu_magic_codes_list_init(void) {
    D_801263BC = 0;
    gMenuDelay = 0;
    D_801263E0 = 0;
    gOptionsMenuItemIndex = (u16)0;
    func_800C4170(2);
    func_8009C6D4(0x3F);
    func_8008E4B0();
    func_800C01D8(&sMenuTransitionFadeOut);
    if (osTvType == TV_TYPE_PAL) {
        D_80126C70 = 0xB;
    } else {
        D_80126C70 = 0xA;
    }
}

#ifdef NON_EQUIVALENT

// Should be functionally equivalent
void render_magic_codes_list_menu_text(s32 arg0) {
    s32 numOfUnlockedCheats;
    s32 fp;
    s32 phi_v0;
    s32 s2;
    s32 i;

    set_text_background_color(0, 0, 0, 0);
    set_text_font(FONT_LARGE);
    set_text_color(0, 0, 0, 0xFF, 0x80);
    draw_text(&D_801263A0, 0xA1, 0x23, gMenuText[20], 0xC); // MAGIC CODES LIST
    set_text_color(0xFF, 0xFF, 0xFF, 0, 0xFF);
    draw_text(&D_801263A0, 0xA0, 0x20, gMenuText[20], 0xC); // MAGIC CODES LIST
    numOfUnlockedCheats = 0;
    phi_v0 = 1;
    for (i = 0; i < 32; i++) {
        if (phi_v0 & gUnlockedMagicCodes) {
            D_80126C80[numOfUnlockedCheats] = i;
            numOfUnlockedCheats += 1;
        }
        phi_v0 <<= 1;
    }
    s2 = 0x36;
    fp = D_801263BC;
    fp *= 8;
    if (fp >= 0x100) {
        fp = 0x1FF - fp;
    }
    set_text_font(FONT_COLOURFUL);
    set_text_color(0xFF, 0xFF, 0xFF, 0, 0xFF);
    for (i = D_801263E0; (i < D_801263E0 + D_80126C70) && (i < numOfUnlockedCheats); i++) {
        if (i == gOptionsMenuItemIndex) {
            set_text_color(0xFF, 0xFF, 0xFF, fp, 0xFF);
        }
        draw_text(&D_801263A0, 0x30, s2, (char *)(*gCheatsAssetData) + ((*gCheatsAssetData + 1)[D_80126C80[i] * 2 + 1]), 0);
        if ((1 << D_80126C80[i]) & gActiveMagicCodes) {
            draw_text(&D_801263A0, 0x100, s2, gMenuText[21], 0); // ON
        } else {
            draw_text(&D_801263A0, 0x100, s2, gMenuText[22], 0); // OFF
        }
        if (i == gOptionsMenuItemIndex) {
            set_text_color(0xFF, 0xFF, 0xFF, 0, 0xFF);
        }
        s2 += 0x10;
    }
    if (i < D_801263E0 + D_80126C70) {
        if (numOfUnlockedCheats == gOptionsMenuItemIndex) {
            set_text_color(0xFF, 0xFF, 0xFF, fp, 0xFF);
        }
        draw_text(&D_801263A0, POS_CENTRED, s2, gMenuText[5], 4); // RETURN
        return;
    }
    if (D_801263BC & 8) {
        render_textured_rectangle(&D_801263A0, &D_800E043C, 0xA0, s2 + 8, 0xFF, 0xFF, 0xFF, 0xFF);
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

#ifdef NON_EQUIVALENT
s32 menu_magic_codes_list_loop(s32 arg0) {
    s32 phi_a2;
    s32 sp48;
    s32 buttonsPressed;
    s32 xAxis;
    s32 yAxis;
    s32 i;
    s32 phi_s1;
    s32 numUnlockedCodes;
    s32 code;

    sp48 = 0;
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += arg0;
        } else {
            gMenuDelay -= arg0;
        }
    }
    D_801263BC = (D_801263BC + arg0) & 0x3F;
    if (gMenuDelay >= -0x13 && gMenuDelay < 0x14) {
        render_magic_codes_list_menu_text(arg0);
    }

    buttonsPressed = 0;
    xAxis = 0;
    yAxis = 0;
    if (!gIgnorePlayerInput && gMenuDelay == 0) {
        for (i = 0; i < 4; i++) {
            buttonsPressed |= get_buttons_pressed_from_player(i);
            xAxis += gControllersXAxisDirection[i];
            yAxis += gControllersYAxisDirection[i];
        }
    }

    code = 1;
    numUnlockedCodes = 0;
    for (i = 0; i < 32; i++) { // 32 is the max number of cheats.
        if (code & gUnlockedMagicCodes) {
            D_80126C80[numUnlockedCodes] = i;
            numUnlockedCodes++;
        }
        code <<= 1;
    }

    if (((xAxis < 0) || (xAxis > 0)) && (numUnlockedCodes != gOptionsMenuItemIndex)) {
        func_80001D04(0xEF, NULL);
        phi_s1 = 1 << D_80126C80[gOptionsMenuItemIndex];
        gActiveMagicCodes ^= phi_s1;       // Toggle active cheats?
        func_8008A8F8(phi_s1, 0x10, 0x20); // func_8008A8F8() = Clear flags?
        func_8008A8F8(phi_s1, 0x20, 0x10);
        func_8008A8F8(phi_s1, 0x1000, 0x6080);
        func_8008A8F8(phi_s1, 0x6080, 0x1000);
        func_8008A8F8(phi_s1, 0x800, 0x1F8000);
        func_8008A8F8(phi_s1, 0x1F8000, 0x800);
        func_8008A8F8(phi_s1, 0x8000, 0xF0000);
        func_8008A8F8(phi_s1, 0x10000, 0xE8000);
        func_8008A8F8(phi_s1, 0x20000, 0xD8000);
        func_8008A8F8(phi_s1, 0x40000, 0xB8000);
        func_8008A8F8(phi_s1, 0x80000, 0x78000);
    }

    phi_a2 = gOptionsMenuItemIndex;

    if (yAxis < 0) {
        gOptionsMenuItemIndex++;
        if (numUnlockedCodes < gOptionsMenuItemIndex) {
            gOptionsMenuItemIndex = numUnlockedCodes;
        }
    }
    if (yAxis > 0) {
        gOptionsMenuItemIndex--;
        if ((s32)gOptionsMenuItemIndex < 0) {
            gOptionsMenuItemIndex = 0;
        }
    }

    if (gOptionsMenuItemIndex < D_801263E0) {
        D_801263E0 = gOptionsMenuItemIndex;
    } else if (gOptionsMenuItemIndex >= (D_801263E0 + D_80126C70)) {
        D_801263E0 = (gOptionsMenuItemIndex - D_80126C70) + 1;
    }

    if (gOptionsMenuItemIndex != phi_a2) {
        func_80001D04(0xEB, NULL);
    }

    if ((buttonsPressed & 0x9000) && (numUnlockedCodes == gOptionsMenuItemIndex)) {
        sp48 = -1;
    }
    if (buttonsPressed & 0x4000) {
        sp48 = -1;
    }
    if (sp48 != 0) {
        gMenuDelay = sp48;
        func_800C01D8(&sMenuTransitionFadeIn);
        func_80001D04(0x241, NULL);
    }
    if (gMenuDelay < -0x1E) {
        func_8008AD1C();
        menu_init(0xA);
        return 0;
    }
    gIgnorePlayerInput = 0;
    return 0;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_magic_codes_list_loop.s")
#endif

void func_8008AD1C(void) {
    func_8009C508(0x3F);
    func_800C422C(2);
}

#ifdef NON_EQUIVALENT

extern u8 *__ROM_END;

void calculate_and_display_rom_checksum(void) {
    s32 romOffset, numBytes, numBytesLeft;
    s32 i;
    u8 *tempBuffer;
    if (!D_800E1E18) {
        numBytesLeft = &__ROM_END;
        numBytesLeft -= 0x1000;
        romOffset = 0x1000;
        tempBuffer = allocate_from_main_pool_safe(0x5000, COLOR_TAG_BLACK);

        while (numBytesLeft > 0) {
            numBytes = numBytesLeft;
            if (numBytesLeft >= 0x5001) {
                numBytes = 0x5000;
            }
            dmacopy(romOffset, tempBuffer, numBytes);
            numBytesLeft -= numBytes;

            for (i = 0; i < numBytes; i++) {
                D_800E1E14 += tempBuffer[i];
            }

            romOffset += numBytes;
        }

        free_from_memory_pool(tempBuffer);
        D_800E1E18 = TRUE;
    }

    set_render_printf_background_color(0, 0, 0, 0x80);
    set_render_printf_position(0x20, 0x88);
    render_printf(D_800E8218, D_800E1E14, &__ROM_END); // D_800E8218 = "ROM checksum %08X,%d\n"
}
#else
GLOBAL_ASM("asm/non_matchings/menu/calculate_and_display_rom_checksum.s")
#endif

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

    for (i = 0; i < 8; i++) {
        gPlayersCharacterArray[i] = (i == controllerIndex) ? 1 : -1;
    }

    for (i = 0; i < 4; i++) {
        gActivePlayersArray[i] = (i == controllerIndex) ? 1 : 0;
    }
}

void menu_character_select_init(void) {
    s32 breakTheLoop;
    s32 i;
    u8 *temp;

    breakTheLoop = FALSE;
    initialise_player_ids();
    if (is_drumstick_unlocked()) {
        if (is_tt_unlocked()) {
            D_801263CC = D_800DFF40;
        } else {
            D_801263CC = D_800DFE40;
        }
    } else if (is_tt_unlocked()) {
        D_801263CC = D_800DFEC0;
    } else {
        D_801263CC = D_800DFDD0;
    }
    for (i = 0; i < 4; i++) {
        D_801263DC[i] = 0;
    }
    gNumberOfReadyPlayers = 0;
    gMenuDelay = 0;
    D_801263BC = 0;
    D_800DF484 = 0;
    for (i = 0; (i < 4) && (!breakTheLoop); i++) {
        if (gActivePlayersArray[i] != 0) {
            breakTheLoop = TRUE;
            D_801263C0.unk0 = (*D_801263CC)[gPlayersCharacterArray[i]].unkC;
            D_801263C0.unk2 = 0x7F;
            D_801263C0.unk1 = 1;
        }
    }
    D_801263B4.unk0 = -1;
    D_801263B4.unk2 = 0;
    D_801263B4.unk1 = 0;
    D_801263B8.unk0 = -1;
    D_801263B8.unk2 = 0;
    D_801263B8.unk1 = 0;
    play_music(0x1A);
    for (i = 0; i < 10; i++) {
        temp = D_800DFDB4[i];
        if (i != D_801263C0.unk0) {
            func_80001114(temp[0]);
            func_80001114(temp[1]);
        }
    }
    func_80001114(6);
    func_80000B18();
    func_8009C674(D_800DFDC8);
    allocate_menu_images(D_800DFDCC);
    func_800C01D8(&sMenuTransitionFadeOut);
    func_800C4170(2);
}

/**
 * Draws the "Player Select" and "OK?" text in the character select menu.
 */
void draw_character_select_text(UNUSED s32 arg0) {
    s32 yPos;
    if (gMenuDelay >= -0x16 && gMenuDelay < 0x17) {
        set_text_font(FONT_LARGE);
        set_text_background_color(0, 0, 0, 0);
        set_text_color(0, 0, 0, 0xFF, 0x80);
        // Draw "Player Select" text drop shadow
        draw_text(&D_801263A0, 0xA1, 0x23, gMenuText[135], 0xC);
        set_text_color(255, 255, 255, 0, 0xFF);
        // Draw "Player Select" text
        draw_text(&D_801263A0, 0xA0, 0x20, gMenuText[135], 0xC);
        if (gNumberOfReadyPlayers == gNumberOfActivePlayers && gNumberOfActivePlayers > 0) {
            yPos = 0xD0;
            if (osTvType == TV_TYPE_PAL) {
                yPos = 0xEA;
            }
            draw_text(&D_801263A0, 0xA0, yPos, D_800E8230 /* "OK?" */, 0xC);
        }
        func_8007B3D0(&D_801263A0);
        update_camera_fov(40.0f);
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_8008B358.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008B4C8.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008B758.s")

#ifdef NON_EQUIVALENT

// Should be functionally equivalent
void randomize_ai_racer_slots(s32 arg0) {
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
        gCharacterIdSlots[i] = (*D_801263CC)[get_random_number_from_range(0, numCharacters)].unkC;
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
GLOBAL_ASM("asm/non_matchings/menu/randomize_ai_racer_slots.s")
#endif

s32 menu_character_select_loop(s32 updateRate) {
    s32 i;
    s32 phi_a0;
    s32 phi_t3;
    s8 activePlayers[4];

    draw_character_select_text(updateRate);
    func_8008C168(updateRate);
    func_8008E4EC();

    for (i = 0; i < 4; i++) {
        if (D_801263DC[i] == 1) {
            D_801263DC[i] = 2;
        }
    }
    gIgnorePlayerInput = 0;
    if (gMenuDelay == 0) {
        // THIS MUST BE ON ONE LINE!
        for (i = 0; i < 4; i++) { activePlayers[i] = gActivePlayersArray[i]; }
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

            i = 0;
            for (phi_a0 = 0; phi_a0 < 4; phi_a0++) {
                if (gActivePlayersArray[phi_a0]) {
                    gCharacterIdSlots[i] = (*D_801263CC)[gPlayersCharacterArray[phi_a0]].unkC;
                    i++;
                }
            }
            randomize_ai_racer_slots(i);
            assign_player_ids(gActivePlayersArray);

            gIsInTracksMode = 1;
            if (phi_t3 >= gNumberOfActivePlayers) {
                func_80000B18();
                load_level_for_menu(0x27, -1, 0);
                if (gNumberOfActivePlayers == 1 && !gPlayerHasSeenCautionMenu) {
                    menu_init(MENU_CAUTION);
                } else {
                    menu_init(MENU_GAME_SELECT);
                }
            } else {
                func_80000B28();
                func_800828B8();
                func_8006E5BC();
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
    return 0;
}

void func_8008BFE8(s32 arg0, s8 *arg1, s32 arg2, u16 arg3, u16 arg4) {
    s32 someBool;
    s32 j;
    s32 i;

    j = 0;
    someBool = 1;
    while (someBool && j < arg2 && arg1[j] != -1) {
        someBool = 0;
        // Run this block if the DOUBLEVISION cheat isn't active.
        if (!(get_filtered_cheats() & CHEAT_SELECT_SAME_PLAYER)) {
            i = 0;
            while (i < 4 && !someBool) {
                if (i != arg0 && gPlayersCharacterArray[i] == arg1[j]) {
                    someBool = 1;
                }
                i++;
            }
            if (someBool) {
                j++;
            }
        }
    }
    if (!someBool) {
        gPlayersCharacterArray[arg0] = arg1[j];
        func_80001D04(arg3, NULL);
        return;
    }
    func_80001D04(arg4, NULL);
}

void func_8008C128(void) {
    func_8009C4A8((s16 *)&D_800DFDC8);
    set_free_queue_state(0);
    func_800C422C(2);
    set_free_queue_state(2);
    D_800DFFD0 = 0;
}

GLOBAL_ASM("asm/non_matchings/menu/func_8008C168.s")

/**
 * Initialises the timer and transition for the controller pak warning screen.
 * Only seen once per game session, as set by gPlayerHasSeenCautionMenu.
 */
void menu_caution_init(void) {
    gIgnorePlayerInput = 60;
    gMenuDelay = 0;
    func_800C4170(2);
    func_800C01D8(&sMenuTransitionFadeOut);
    gPlayerHasSeenCautionMenu = 1;
}

/**
 * Loops through the display of the caution screen.
 * Blocks player input for one second.
 */
s32 menu_caution_loop(s32 updateRate) {
    if (gMenuDelay) {
        gMenuDelay += updateRate;
    } else if (gIgnorePlayerInput <= 0 && (get_buttons_pressed_from_player(0) & (A_BUTTON | B_BUTTON | START_BUTTON))) {
        func_80001D04(0xEF, NULL);
        gMenuDelay = 1;
        func_800C01D8(&sMenuTransitionFadeIn);
    }
    if (gMenuDelay < 20) {
        draw_menu_elements(1, gCautionMenuTextElements, 1.0f);
    }
    if (gMenuDelay > 30) {
        unload_large_font();
        menu_init(MENU_GAME_SELECT);
    }
    if (gIgnorePlayerInput > 0) {
        gIgnorePlayerInput -= updateRate;
    }
    return 0;
}

/**
 * Explicitly says to unload the FONT_LARGE type.
 */
void unload_large_font(void) {
    func_800C422C(FONT_LARGE);
}

#ifdef NON_EQUIVALENT

void menu_game_select_init(void) {
    s32 i;

    gMenuDelay = 0;
    D_801263BC = 0;
    D_800DF460 = 0;
    D_801263E0 = 2;
    func_800C01D8(&sMenuTransitionFadeOut);
    func_8006EBA8();
    func_8001B790();
    D_801263D8 = 1;
    func_8009C6D4(0x43);
    func_8007FFEC(3);
    func_800C4170(2);
    play_music(0x1A);

    for (i = 0; i < 10; i++) {
        if (i != D_801263B4.unk0) {
            func_80001114(D_800DFDB4[i][0]);
            func_80001114(D_800DFDB4[i][1]);
        }
    }

    func_80001114(6);
    func_80000B18();
    if (is_adventure_two_unlocked()) {
        D_80126460 = gGameSelectTextElemsWithAdv2;
        D_801263E0 = 2;
    } else {
        D_80126460 = gGameSelectTextElemsNoAdv2;
        D_801263E0 = 1;
    }

    // This loop doesn't match.
    for (i = 0; i <= D_801263E0; i++) {
        u8 temp = i; // How do I make this a `mov`?
        (&((unk80126460 *)D_80126460)[temp] + 1)->elem[0].unk14_a.texture = D_80126550[67];
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_game_select_init.s")
#endif

#ifdef NON_EQUIVALENT
void func_8008C698(s32 arg0) {
    s32 fade;
    s32 i;
    s32 filterAlpha;
    u8 temp;

    if (gMenuDelay >= -21 && gMenuDelay < 22) {
        fade = D_801263BC * 8;
        fade = fade;
        if (fade >= 0x100) {
            fade = 0x1FF - fade;
        }
        func_80067F2C(&D_801263A0, (s32 *)&D_801263A8);

        for (i = 0; i <= D_801263E0; i++) {
            filterAlpha = 0;
            if (i == D_800DF460) {
                filterAlpha = fade;
            }
            // This doesn't match.
            temp = i; // How do I make this a `mov`?
            (&((unk80126460 *)D_80126460)[temp] + 1)->elem[1].filterAlpha = filterAlpha;
        }

        if (osTvType == TV_TYPE_PAL) {
            D_800DF79C = 0xC;
            D_800DF7A0 = 0;
        } else {
            D_800DF79C = 0;
            D_800DF7A0 = 0;
        }

        draw_menu_elements(1, (MenuElement *)D_80126460, 1.0f);
        func_80080BC8(&D_801263A0);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_8008C698.s")
#endif

#ifdef NON_EQUIVALENT

s32 menu_game_select_loop(s32 arg0) {
    s32 playerInputs;
    s32 playerYDir;
    s32 charSelectScene;
    s32 temp;

    func_8008C168();

    // Regalloc issue: This needs to use v1, not a2!
    D_801263BC = (D_801263BC + arg0) & 0x3F;

    if (D_801263D8 != 0) {
        D_801263D8++;
        if (D_801263D8 >= 3) {
            func_800828B8();
            D_801263D8 = 0;
        }
    }
    if (gMenuDelay != 0) {
        if (gMenuDelay < 0) {
            gMenuDelay -= arg0;
        } else {
            gMenuDelay += arg0;
        }
    }
    if (gMenuDelay >= 0x1F) {
        func_8008CACC();
        if (D_800DF460 == D_801263E0) {
            func_80000B28();
            gIsInTracksMode = TRUE;
            func_8006E5BC();
            load_level_for_menu(-1, -1, 0);
            menu_init(MENU_TRACK_SELECT);
        } else {
            gIsInAdventureTwo = D_800DF460;
            gIsInTracksMode = FALSE;
            gPlayerSelectVehicle[0] = 0;
            func_8006DB14(0);
            menu_init(MENU_FILE_SELECT);
        }
        return 0;
    } else if (gMenuDelay < -0x1E) {
        func_8008CACC();
        charSelectScene = 0;
        if (is_drumstick_unlocked()) {
            charSelectScene = 1;
        }
        if (is_tt_unlocked()) {
            charSelectScene ^= 3;
        }
        load_level_for_menu(0x16, -1, charSelectScene);
        func_8008AEB4(0, 0);
        menu_init(MENU_CHARACTER_SELECT);
        return 0;
    } else {
        func_8008C698(arg0);
        if ((gMenuDelay == 0) && (D_801263D8 == 0)) {
            playerInputs = get_buttons_pressed_from_player(0);
            playerYDir = gControllersYAxisDirection[0];
            playerInputs = playerInputs;
            if (gNumberOfActivePlayers == 2) {
                playerInputs |= get_buttons_pressed_from_player(1);
                playerYDir += gControllersYAxisDirection[1];
            }
            if (playerInputs & (A_BUTTON | START_BUTTON)) {
                if (D_800DF460 == D_801263E0) {
                    set_music_fade_timer(-0x80);
                }
                func_800C01D8(&sMenuTransitionFadeIn);
                gMenuDelay = 1;
                func_80001D04(0xEF, 0);
            } else if (playerInputs & B_BUTTON) {
                func_800C01D8(&sMenuTransitionFadeIn);
                gMenuDelay = -1;
            } else {
                if (playerYDir < 0) {
                    if (D_800DF460 < D_801263E0) {
                        D_800DF460++;
                        func_80001D04(0xEB, 0);
                    }
                }
                if (playerYDir > 0) {
                    if (D_800DF460 > 0) {
                        D_800DF460--;
                        func_80001D04(0xEB, 0);
                    }
                }
            }
        }
        gIgnorePlayerInput = FALSE;
        return 0;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_game_select_loop.s")
#endif

void func_8008CACC(void) {
    func_800C422C(2);
    func_8007FF88();
    func_8009C508(0x43);
}

void menu_file_select_init(void) {
    s32 i;
    s32 numLevels;
    s32 numWorlds;

    get_number_of_levels_and_worlds(&numLevels, &numWorlds);
    func_8009C674(D_800E0398);
    allocate_menu_images(D_800E03A4);
    func_8007FFEC(6);
    func_8006EBA8();
    D_801263D8 = 1;
    gSaveFileIndex = 0;
    gMenuDelay = 0;
    D_801263E0 = 0;
    D_801263BC = 0;
    D_80126484 = 0;
    D_80126488 = 0;
    D_80126CC0 = 0;
    func_800C01D8(&sMenuTransitionFadeOut);
    func_800C4170(2);
    play_music(0x1A);
    for (i = 0; i < 10; i++) {
        if (i != D_801263B4.unk0) {
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
    func_80067F2C(&D_801263A0, (s32 *)&D_801263A8);
    for (i = 0; i < 3; i++) { // 3 files
        if (gSavefileInfo[i].isAdventure2 == gIsInAdventureTwo || gSavefileInfo[i].isStarted == 0) {
            color = 0xB0E0C0FF;
        } else {
            color = 0x6A9073FF;
        }
        func_80080580(0, D_800E03CC[i].unk0 - 0xA0, 0x78 - D_800E03CC[i].unk2, D_800E03CC[i].unk4,
            D_800E03CC[i].unk6, D_800E03CC[i].unk8, D_800E03CC[i].unkA, color, D_80126550[67]);
    }
    func_80080BC8(&D_801263A0);
    if (D_801263D8 == 0) {
        set_text_font(FONT_LARGE);
        set_text_background_color(0, 0, 0, 0);
        s5 = 10;
        for (i = 0; i < 3; i++) {
            if (gSavefileInfo[i].isStarted != 0) {
                s2 = 0xB;
                func_8007BF1C(0);
                if (gSavefileInfo[i].isAdventure2 != 0) {
                    s2 = 0xC;
                }
                render_menu_image(s2, D_800E03FC[2] + D_800E03CC[i].unk0, D_800E03FC[3] + D_800E03CC[i].unk2, 0, 0, 0, 0x80);
                func_80068508(1);
                gMenuImageStack->unk18 = gSavefileInfo[i].balloonCount / s5;
                render_menu_image(0, (D_800E03FC[6] + D_800E03CC[i].unk0) - 6, D_800E03FC[7] + D_800E03CC[i].unk2, 0, 0, 0, 0x80);
                gMenuImageStack->unk18 = gSavefileInfo[i].balloonCount % s5;
                render_menu_image(0, D_800E03FC[6] + D_800E03CC[i].unk0 + 6, D_800E03FC[7] + D_800E03CC[i].unk2, 0, 0, 0, 0x80);
                func_80068508(0);
                sMenuGuiColourG = 0x40;
                sMenuGuiColourB = 0x40;
                render_menu_image(s5, D_800E03FC[8] + D_800E03CC[i].unk0, D_800E03FC[9] + D_800E03CC[i].unk2, 0, 0, 0, 0x80);
                sMenuGuiColourG = 0xFF;
                sMenuGuiColourB = 0xFF;
                func_8007BF1C(1);
            } else {
                set_text_color(255, 255, 255, 64, 255);
                draw_text(&D_801263A0, D_800E03FC[4] + D_800E03CC[i].unk0, D_800E03FC[5] + D_800E03CC[i].unk2 + y, gMenuText[75], 0xC);
            }
        }
    }
    phi_v0_2 = D_801263BC * 8;
    if (phi_v0_2 >= 0x100) {
        phi_v0_2 = 0x1FF - phi_v0_2;
    }
    set_text_font(FONT_COLOURFUL);
    set_text_background_color(0, 0, 0, 0);
    set_text_color(255, 255, 255, 0, 255);
    for (i = 0; i < 3; i++) {
        s2 = FALSE;
        if (D_80126484 != 0) {
            if (D_80126494 == 0 && i == D_8012648C) {
                s2 = TRUE;
            } else if (D_80126494 > 0 && i == D_80126490) {
                s2 = TRUE;
            }
        } else if (D_80126488 != 0 && i == D_8012648C) {
            s2 = TRUE;
        } else if (D_801263E0 == 0 && i == gSaveFileIndex) {
            s2 = TRUE;
        }
        if (s2) {
            s32 temp_t0 = phi_v0_2 | ~0xFF;
            func_80080E90(&D_801263A0, D_800E03CC[i].unk0, D_800E03CC[i].unk2 + y, D_800E03CC[i].unk4, D_800E03CC[i].unk6,
                D_800E03CC[i].unk8, D_800E03CC[i].unkA, temp_t0, temp_t0, temp_t0, temp_t0);
        }
        if (D_80126CC0 == 0 || i != gSaveFileIndex) {
            trim_filename_string(gSavefileInfo[i].name, tempName);
            if (gSavefileInfo[i].isStarted == 0) {
                trim_filename_string(gFilenames[i], tempName);
            }
            if (tempName != NULL) {
                draw_text(&D_801263A0, D_800E03FC[0] + D_800E03CC[i].unk0, D_800E03FC[1] + D_800E03CC[i].unk2 + y, tempName, 0xC);
            }
        }
    }
    set_text_font(FONT_LARGE);
    set_text_color(0, 0, 0, 255, 128);
    draw_text(&D_801263A0, 0xA1, 0x13, gMenuText[76], 4);
    set_text_color(255, 255, 255, 0, 255);
    draw_text(&D_801263A0, 0xA0, 0x10, gMenuText[76], 4);
    set_text_color(255, 255, 255, 0, 255);
    y += 0xBB;
    if (D_80126484 != 0) {
        if (D_80126494 == 0) {
            set_text_font(FONT_COLOURFUL);
            draw_text(&D_801263A0, 0xA0, y, gMenuText[77], 0xC);
        } else if (D_80126494 == 1) {
            set_text_font(FONT_COLOURFUL);
            draw_text(&D_801263A0, 0xA0, y, gMenuText[78], 0xC);
        } else {
            draw_text(&D_801263A0, 0xA0, y, &D_800E8234, 0xC);
        }
        return;
    }
    if (D_80126488 != 0) {
        if (D_80126494 == 0) {
            set_text_font(FONT_COLOURFUL);
            draw_text(&D_801263A0, 0xA0, y, gMenuText[79], 0xC);
        } else {
            draw_text(&D_801263A0, 0xA0, y, &D_800E8238, 0xC);
        }
        return;
    }
    if (D_80126CC0 == 0) {
        if (D_801263E0 == 1) {
            set_text_color(255, 255, 255, phi_v0_2, 255);
        }
        draw_text(&D_801263A0, 0x5A, y, gMenuText[80], 0xC);
        if (D_801263E0 == 2) {
            set_text_color(255, 255, 255, phi_v0_2, 255);
        } else {
            set_text_color(255, 255, 255, 0, 255);
        }
        draw_text(&D_801263A0, 0xE6, y, gMenuText[81], 0xC);
        return;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/render_file_select_menu.s")
#endif

GLOBAL_ASM("asm/non_matchings/menu/func_8008D5F8.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008D8BC.s")

#if 1
GLOBAL_ASM("asm/non_matchings/menu/func_8008DC7C.s")
#else
/* Size: 0x0C Bytes */
extern SavefileInfo gSavefileInfo[3]; // Filename structs?
extern s32 D_80126494;
extern s32 D_8012648C;

void func_8008DC7C(s32 arg0) {
    s32 temp_t6;
    s32 temp_a1;
    s32 phi_v1;
    s32 phi_v1_2;

    phi_v1 = get_buttons_pressed_from_player(0);
    temp_a1 = gControllersXAxisDirection;
    if (gNumberOfActivePlayers == 2) {
        phi_v1 = phi_v1 | get_buttons_pressed_from_player(1);
        temp_a1 += gControllersXAxisDirection + 1;
    }

    if (D_80126494 == 0) {
        if (phi_v1 & 0x4000) {
            func_80001D04(0x241, NULL);
            D_80126488 = 0;
        } else if (phi_v1 & 0x9000) {
            if (gSavefileInfo[D_8012648C].unk0 == 0) {
                func_80001D04(0x241, NULL);
            }
            func_80001D04(0xEF, NULL);
            D_80126494 = 1;
        }

        phi_v1_2 = D_8012648C;
        if (temp_a1 < 0) {
            phi_v1_2 = D_8012648C;
            if (D_8012648C > 0) {
                D_8012648C--;
                phi_v1_2 = D_8012648C;
            }
        }

        if (temp_a1 > 0) {
            temp_t6 = phi_v1_2 + 1;
            if (phi_v1_2 < 2) {
                D_8012648C = temp_t6;
                phi_v1_2 = temp_t6;
            }
        }

        //if (D_8012648C != phi_v1_2) {
        func_80001D04(0xEB, NULL);
        //}
    } else {
        if (phi_v1 & 0x9000) {
            func_80001D04(0xEF, NULL);
            func_8006ECAC(D_8012648C);
            gSavefileInfo[D_8012648C].unk0 = 0;
            gSavefileInfo[D_8012648C].unk1 = 0;
            gSavefileInfo[D_8012648C].unk2 = 0;
            gSavefileInfo[D_8012648C].name[0] = 'D';
            gSavefileInfo[D_8012648C].name[1] = 'K';
            gSavefileInfo[D_8012648C].name[2] = 'R';
            gSavefileInfo[D_8012648C].name[3] = '\0';
            gSaveFileIndex = (s32)D_8012648C;
            D_801263E0 = 0;
            D_80126488 = 0;
        } else if (phi_v1 & 0x4000) {
            func_80001D04(0x241, NULL);
            D_80126494 = 0;
        }
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/menu/menu_file_select_loop.s")

void func_8008E428(void) {
    func_8009C4A8(D_800E0398);
    func_8007FF88();
    func_800C422C(2);
}

void func_8008E45C(void) {
    D_800E045C[0].texture = D_80126550[24];
    D_800E045C[1].texture = D_80126550[25];
    D_800E0474[0].texture = D_80126550[26];
    D_800E0474[1].texture = D_80126550[27];
    D_800E048C[0].texture = D_80126550[28];
    D_800E048C[1].texture = D_80126550[29];
}

void func_8008E4B0(void) {
    D_800E041C[0].texture = D_80126550[61];
    D_800E042C[0].texture = D_80126550[60];
    D_800E043C[0].texture = D_80126550[63];
    D_800E044C[0].texture = D_80126550[62];
}

GLOBAL_ASM("asm/non_matchings/menu/func_8008E4EC.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_track_select_init.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008F00C.s")

#ifdef NON_EQUIVALENT
// Close to done with this function. Just a regalloc issue remains.

s32 menu_track_select_loop(s32 arg0) {
    s32 phi_a2;
    Settings *settings;
    s32 i = 0;

    settings = get_settings();
    D_801263BC = (D_801263BC + arg0) & 0x3F;
    if (get_thread30_level_id_to_load() == 0 && gMenuDelay != 0) {
        if (gMenuDelay < 0) {
            gMenuDelay -= arg0;
        } else {
            gMenuDelay += arg0;
        }
    }
    func_8008E4EC();

    gSPClearGeometryMode(D_801263A0++, G_CULL_FRONT)

        switch (D_801267D0) {
        case 0:
            func_8008FF1C(arg0);
            func_800904E8(arg0);
            func_80090918(arg0);
            break;
        case 1:
            func_80090ED8(arg0);
            render_track_select_setup_ui(arg0);
            func_80092188(arg0);
            break;
    }

    if (sMenuMusicVolume < 0) {
        set_relative_volume_for_music(0);
    } else {
        sMenuMusicVolume += arg0 * 2;
        if (sMenuMusicVolume >= 0x51) {
            sMenuMusicVolume = 0x50;
        }
        set_relative_volume_for_music((u8)sMenuMusicVolume);
    }
    if (D_801267D0 < 0) {
        func_8008F534();
        D_800DF478 = 0;
        if (gNumberOfActivePlayers >= 3 || gNumberOfActivePlayers == 2 && (gActiveMagicCodes << 7) >= 0) {
            phi_a2 = 0;
            if (is_drumstick_unlocked()) {
                phi_a2 = 1;
            }
            if (is_tt_unlocked()) {
                phi_a2 ^= 3;
            }
            load_level_for_menu(0x16, -1, phi_a2);
            func_8008AEB4(0, NULL);
            menu_init(MENU_CHARACTER_SELECT);
            return 0;
        }
        load_level_for_menu(0x27, -1, 0);
        menu_init(MENU_GAME_SELECT);
        return 0;
    }
    if (D_801267D0 >= 2) {
        func_8008F534();
        if (gMultiplayerSelectedNumberOfRacersCopy != gMultiplayerSelectedNumberOfRacers) {
            // regalloc issue with the for loop.
            for (i = 0; i < 8; i++) {
                settings->racers[i].starting_position = i;
            }
        }
        if (D_801269C8 != 4) {
            D_800DF478 = 1;
            return gNumberOfActivePlayers;
        }
        gTrophyRaceWorldId = D_801269CC + 1;
        D_800DF450 = 0;
        D_800E0FEC = 0;
        menu_init(MENU_TROPHY_RACE_ROUND);
        return 0;
    }
    gIgnorePlayerInput = 0;
    return 0;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_track_select_loop.s")
#endif

void func_8008F534(void) {
    s32 i;

    func_80066894(0, 0);
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
    func_800C422C(2);
    func_8007FF88();
    func_80000B28();
    func_80000C2C();
    func_80001844();
    func_8006F564(0);
}

GLOBAL_ASM("asm/non_matchings/menu/func_8008F618.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008FA54.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008FF1C.s")
GLOBAL_ASM("asm/non_matchings/menu/func_800904E8.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80090918.s")

void func_80090ED8(UNUSED s32 arg0) {
    if (D_801263E0 == 1 && D_800E0414 == 0 && D_80126840 == 0) {
        func_80001D04(0x132, &D_80126840);
    }
}

#ifdef NON_EQUIVALENT

// Somewhat close to matching, but should be functionally equivalent.
void render_track_select_setup_ui(s32 arg0) {
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
    if ((gNumberOfActivePlayers == 2) && (D_801269C8 < 4) && (D_801263E0 >= 2)) {
        sp74 = TRUE;
    }
    func_80066894(0, 1);
    func_8009BD5C();
    func_80067F2C(&D_801263A0, (s32 *)&D_801263A8);
    if (gMenuDelay < 0) {
        if (D_801269F4 == 4) {
            sp84 = 6;
        } else if (D_801269F4 == 5) {
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
    if ((gMenuDelay >= -0x16) && (gMenuDelay < 0x1F)) {
        if (gMenuDelay < 0) {
            sMenuGuiOpacity = (gMenuDelay * 0x10) + 0xFF;
        } else {
            sMenuGuiOpacity = 0xFF;
        }
        if (sMenuGuiOpacity < 0) {
            sMenuGuiOpacity = 0;
        }
        sp7C = func_8006B0F8(gTrackIdForPreview);
        set_text_font(FONT_LARGE);
        set_text_color(0xC0, 0xC0, 0xFF, 0, sMenuGuiOpacity);
        set_text_background_color(0, 0, 0, 0);
        draw_text(&D_801263A0, POS_CENTRED, 0x2B, func_8006BDDC(gTrackIdForPreview), 0xC); // Draw track name?
        sp84 = D_801263BC * 8;
        if (sp84 >= 0x100) {
            sp84 = 0x1FF - sp84;
        }
        set_current_dialogue_background_colour(7, 0xFF, sp84, 0, sMenuGuiOpacity);
        if ((D_801263E0 == -1) || ((D_801263E0 == 2) && (D_801269C8 == 4) && is_adventure_two_unlocked())) {
            s4 = func_800C4DA0(gMenuText[146], 0, 0);   // gMenuText[146] = "ADVENTURE"
            temp = func_800C4DA0(gMenuText[147], 0, 0); // gMenuText[147] = "ADVENTURE TWO"
            if (s4 < temp) {
                s4 = temp;
            }
            if (s4 < D_800E0700[2]) {
                s4 = D_800E0700[2];
            } else {
                s4 += 0xC;
            }
            func_80080580(&D_801263A0, -(s4 >> 1), 0x78 - D_800E0700[1], s4, D_800E0700[3],
                D_800E0700[4], D_800E0700[5], sMenuGuiOpacity + 0xB0E0C000, D_8012665C);
            func_80080E6C();
            set_text_font(FONT_COLOURFUL);
            s7 = D_800E0700[7] + D_800E0700[1] + sp80;
            s7++;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 4; j += 2) {
                    if (j == 0) {
                        set_text_color(0, 0, 0, 0xFF, sMenuGuiOpacity >> 1);
                    } else {
                        s32 alpha = i;
                        if (i == D_800E0418) {
                            alpha = sp84;
                        }
                        set_text_color(0xFF, 0xFF, 0xFF, alpha, sMenuGuiOpacity);
                    }
                    // gMenuText[146] = "ADVENTURE", gMenuText[147] = "ADVENTURE TWO"
                    draw_text(&D_801263A0, 0xA1 - j, s7 - j, gMenuText[146 + i], 0xC);
                }
                s7 += 16;
            }
        }
        if (D_801269C8 < 4) {
            set_text_font(FONT_COLOURFUL);
            set_text_color(0xFF, 0x40, 0x40, 0x60, sMenuGuiOpacity);
            draw_text(&D_801263A0, 0x38, 0x48 + sp80, gMenuText[9], 8);  // gMenuText[9] = "BEST TIME"
            draw_text(&D_801263A0, 0x38, 0x5C + sp80, gMenuText[10], 8); // gMenuText[10] = "BEST LAP"
            set_text_color(0xFF, 0x80, 0xFF, 0x60, sMenuGuiOpacity);
            decompress_filename_string(settings->courseInitialsPtr[gPlayerSelectVehicle[0]][gTrackIdForPreview], &sp78, 3);
            draw_text(&D_801263A0, 0xFA, 0x48 + sp80, &sp78, 0xC);
            decompress_filename_string(settings->flapInitialsPtr[gPlayerSelectVehicle[0]][gTrackIdForPreview], &sp78, 3);
            draw_text(&D_801263A0, 0xFA, 0x5C + sp80, &sp78, 0xC);
            func_80081800(settings->courseTimesPtr[gPlayerSelectVehicle[0]][gTrackIdForPreview], 0x16, 0x35, 0x80, 0xFF, 0xFF, 0);
            func_80081800(settings->flapTimesPtr[gPlayerSelectVehicle[0]][gTrackIdForPreview], 0x16, 0x21, 0xFF, 0xC0, 0xFF, 0);
            if (D_801263E0 != -1) {
                if (gNumberOfActivePlayers == 1) {
                    // Glow effect
                    set_current_dialogue_box_coords(7, 0x86, sp80 + 0x70, 0xBA, sp80 + 0x89);
                    render_dialogue_box(&D_801263A0, 0, 0, 7);
                    if (D_801263E0 <= 0) {
                        render_textured_rectangle(&D_801263A0, &D_800E05B4, 0x88, sp80 + 0x72, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                    } else {
                        render_textured_rectangle(&D_801263A0, &D_800E05C4, 0x88, sp80 + 0x72, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                        for (i = 0; i < 2; i++) {
                            s32 yTemp = 0x97 + sp80 + (i * 0x18);
                            if (i == D_800E0414) {
                                render_textured_rectangle(&D_801263A0, D_800E0648[(i * 3) + 1], 0x68, yTemp, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                            } else {
                                render_textured_rectangle(&D_801263A0, D_800E0648[(i * 3) + 2], 0x68, yTemp, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                            }
                        }
                    }
                } else {
                    if (!sp74) {
                        s3 = (gNumberOfActivePlayers - 1) * gNumberOfActivePlayers;
                        for (i = 0; i < gNumberOfActivePlayers; i++) {

                            if (((gNumberOfActivePlayers == 1) && (i == D_801263E0)) || ((gNumberOfActivePlayers >= 2) && (D_801269C4[i] == 0))) {
                                s32 temp_v0_9 = D_800E0688[s3 + (i * 2)];
                                s32 temp_v1 = D_800E0688[s3 + (i * 2) + 1] + sp80;
                                // Glow effect around Player image
                                set_current_dialogue_box_coords(7, temp_v0_9 - 2, temp_v1 - 2, temp_v0_9 + 0x32, temp_v1 + 0x17);
                                render_dialogue_box(&D_801263A0, 0, 0, 7);
                            }

                            // "Player" text image
                            render_textured_rectangle(&D_801263A0, D_800E0660[i], D_800E0688[s3 + (i * 2)], D_800E0688[s3 + (i * 2) + 1] + sp80, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                        }
                    }
                }

                if ((gNumberOfActivePlayers >= 2) || D_801263E0 == 0) {
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
                                            render_textured_rectangle(&D_801263A0, D_800E0624[(i * 3) + 1], D_800E06B0[s3 + j], yTemp, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                                        } else if (settings->courseFlagsPtr[gTrackIdForPreview] & 2) {
                                            // Not highlighted
                                            render_textured_rectangle(&D_801263A0, D_800E0624[(i * 3) + 2], D_800E06B0[s3 + j], yTemp, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                                        } else {
                                            // Not available (Ghosted out)
                                            render_textured_rectangle(&D_801263A0, D_800E0624[(i * 3) + 2], D_800E06B0[s3 + j], yTemp, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity / 2);
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
                if (gPlayerSelectVehicle[0] == 2) {
                    s7 = sp80 + 2;
                }
                if (gNumberOfActivePlayers == 1) {
                    if (D_801263E0 == 0) {
                        // Draw vehicle image for one player
                        render_textured_rectangle(&D_801263A0, D_800E0624[gPlayerSelectVehicle[0] * 3], 0x95, s7, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                    } else {
                        // Draw T.T. image for one player
                        render_textured_rectangle(&D_801263A0, D_800E0648[D_800E0414 * 3], 0x95, sp80, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                    }
                }
                if ((gNumberOfActivePlayers == 2) && (!sp74)) {
                    s7 = sp80;
                    // Draw vehicle image for first player
                    render_textured_rectangle(&D_801263A0, D_800E0624[gPlayerSelectVehicle[0] * 3], 0x4F, s7, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                    if (gPlayerSelectVehicle[1] == 2) {
                        s7 = sp80 + 2;
                    }
                    // Draw vehicle image for second player
                    render_textured_rectangle(&D_801263A0, D_800E0624[gPlayerSelectVehicle[1] * 3], 0xB0, s7, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
                }

                func_8007B3D0(&D_801263A0);

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
                    s32 temp_v0_12 = func_800C4DA0(gMenuText[136], 0, 0); // gMenuText[136] = "NUMBER OF RACERS"
                    if ((D_800E06E4[2] - 0xC) < temp_v0_12) {
                        s4 = temp_v0_12 + 0xC;
                    } else {
                        s4 = D_800E06E4[2];
                    }
                    func_80080580(&D_801263A0, -(s4 >> 1), 0x78 - D_800E06E4[1], s4, D_800E06E4[3], D_800E06E4[4], D_800E06E4[5], 0xB0E0C0FF, D_8012665C);
                    func_80080E6C();
                    set_text_font(FONT_COLOURFUL);
                    set_text_color(0, 0, 0, 0xFF, 0x80);
                    draw_text(&D_801263A0, D_800E06E4[6] + D_800E06E4[0] + 1, D_800E06E4[7] + D_800E06E4[1] + 1, gMenuText[136], 0xC);
                    set_text_color(0xFF, 0xFF, 0xFF, 0, 0xFF);
                    draw_text(&D_801263A0, D_800E06E4[6] + D_800E06E4[0] - 1, D_800E06E4[7] + D_800E06E4[1] - 1, gMenuText[136], 0xC);
                    // gMenuText[136] = "NUMBER OF RACERS"
                    func_80068508(1);
                    func_8007BF1C(0);
                    for (i = 0; i < 3; i++) {
                        s32 index = i * 2;
                        if (i == gMultiplayerSelectedNumberOfRacers) {
                            if (D_801263E0 < 3) {
                                sMenuGuiColourG = 0xFF - sp84;
                                sMenuGuiColourB = 0xFF - sp84;
                            } else {
                                sMenuGuiColourG = 0;
                                sMenuGuiColourB = 0;
                            }
                        }
                        // X position
                        gMenuImageStack[0].unkC = (D_800E06E4[index + 8] + D_800E06E4[0]) - 0xA0;
                        // Y position
                        gMenuImageStack[0].unk10 = (-D_800E06E4[index + 9] - D_800E06E4[1]) + 0x78;
                        // Number value to draw.
                        gMenuImageStack[0].unk18 = index + 2;
                        func_8009CA60(0);
                        sMenuGuiColourG = 0xFF;
                        sMenuGuiColourB = 0xFF;
                    }
                    func_8007BF1C(1);
                    func_80068508(0);
                }
            }
        }
        if (D_801269C8 < 4) {
            func_8007BF1C(0);
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
            func_8007BF1C(1);
        }
        if ((gNumberOfActivePlayers == 1) && (D_801263E0 >= 0) && (func_80092BE0(gTrackIdForPreview) >= 0)) {
            // Render small T.T. icon.
            render_textured_rectangle(&D_801263A0, &D_800E0614, 0xCC, 0x7A, 0xFF, 0xFF, 0xFF, sMenuGuiOpacity);
            func_8007B3D0(&D_801263A0);
        }
        if (D_801269C8 != 5) {
            if (((D_801263E0 == 2) && !sp74) || ((D_801263E0 == 3) && sp74) || (D_801263E0 == 4)) {
                set_text_font(FONT_LARGE);
                set_text_color(0xFF, 0xFF, 0xFF, 0, sMenuGuiOpacity);
                if (D_801269C8 >= 4) {
                    sp80 += 0x18;
                }
                draw_text(&D_801263A0, 0xA0, 0xAC, D_800E823C, 0xC); // D_800E823C = "OK?"
            }
        }
        sMenuGuiOpacity = 0xFF;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/render_track_select_setup_ui.s")
#endif

GLOBAL_ASM("asm/non_matchings/menu/func_80092188.s")

s32 func_80092BE0(s32 arg0) {
    s8 *trackIdArray;
    s32 index;
    s32 temp;

    trackIdArray = (s8 *)get_misc_asset(0x1C);

    index = 0;
    temp = -1;
    if (trackIdArray[0] != -1) {
        while (temp < 0) {
            if (arg0 == trackIdArray[index]) {
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

void menu_5_init(void) {
    Settings *settings;
    s32 result;
    s32 s0;
    s16 temp;

    settings = get_settings();
    gTrackIdForPreview = 0;
    D_801263BC = 0;
    gMenuDelay = 0;
    s0 = settings->unk4C->unk2;
    gPlayerSelectVehicle[0] = func_8006B0AC(s0);
    result = func_8006B14C(s0);
    if ((result == 5) || (result == 8) || (!(result & 0x40) && (!(settings->courseFlagsPtr[s0] & 2)))) {
        temp = D_800E0758[s0];
        if (temp != -1) {
            func_80000FDC(temp, 0, 1.0f);
        }
        D_801263E0 = -1;
    } else {
        temp = D_800E0758[s0];
        if (temp != -1) {
            func_80000FDC(temp, 0, 0.5f);
        }
        set_music_player_voice_limit(0x18);
        play_music(0x18);
        func_80000B18();
        D_801263E0 = 0;
        func_8009C674(&D_800E0FB4);
        allocate_menu_images(&D_800E0FD8);
        func_8008E45C();
        D_800E04D4[0].texture = D_80126550[31];
        D_800E04E4[0].texture = D_80126550[30];
        D_800E04F4[0].texture = D_80126550[33];
        D_800E0504[0].texture = D_80126550[32];
        D_800E0514[0].texture = D_80126550[35];
        D_800E0524[0].texture = D_80126550[34];
        D_800E05B4[0].texture = D_80126550[48];
        D_800E0614[0].texture = D_80126550[94];
        func_800C01D8(&sMenuTransitionFadeOut);
        D_801263BC = 0;
        gMenuDelay = 0;
        D_800E0980 = 0x1E;
        func_800C4170(2);
        load_level_for_menu(s0, -1, 1);
    }
    assign_dialogue_box_id(7);
    if (func_8006B14C(s0) & 0x40) {
        func_800C31EC(func_8006B190(s0) + 0x3B);
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_80092E94.s")

#ifdef NON_EQUIVALENT
// Regalloc issues
s32 menu_5_loop(s32 arg0) {
    s32 temp0;
    s32 vehicle2;
    s32 sp30;
    s32 vehicle;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    Settings *settings;

    if (D_801263E0 < 0) {
        return gTrackIdForPreview | 0x80;
    }
    settings = get_settings();
    sp24 = ((Settings4C *)((u8 *)settings->unk4C + gTrackIdForPreview))->unk2;
    sp28 = FALSE;
    temp0 = settings->courseFlagsPtr[sp24];
    sp1C = 0;
    if (temp0 & 2) {
        sp1C = 1;
    }
    if (temp0 & 4) {
        sp1C = 2;
    }
    if (func_8006B14C(sp24) & 0x40) {
        sp28 = TRUE;
    }
    sp20 = FALSE;
    if (!is_time_trial_enabled()) {
        if (sp1C == 1) {
            if (settings->worldId == 5 || (settings->bosses & (1 << settings->worldId))) {
                sp20 = TRUE;
            }
        }
    }
    D_801263BC = (D_801263BC + arg0) & 0x3F;
    func_80092E94(arg0, sp1C, sp20);
    if (sp1C < 2) {
        gPlayerSelectVehicle[0] = func_8006B0AC(sp24);
    }
    vehicle = gPlayerSelectVehicle[0];
    sp30 = func_8006B0F8(sp24);
    vehicle2 = vehicle;
    func_8008E4EC();
    if (gMenuDelay == 0) {
        if ((D_801263E0 != 0) || sp20 || sp28) {
            if (D_801267D8[0] & 0x9000) {
                if (sp28) {
                    func_800C31EC(0x2710);
                }
                gMenuDelay = 1;
                func_800C01D8(&sMenuTransitionFadeIn);
                func_80001D04(0xEF, NULL);
            } else if (D_801267D8[0] & 0x4000) {
                func_80001D04(0x241, NULL);
                if (sp20 || sp28) {
                    if (sp28) {
                        func_800C31EC(0x2710);
                    }
                    func_800C01D8(&sMenuTransitionFadeIn);
                    gMenuDelay = -1;
                } else {
                    D_801263E0 = 0;
                }
            }
        } else {
            if (D_801267D8[0] & 0x4000) {
                func_80001D04(0x241, NULL);
                func_800C01D8(&sMenuTransitionFadeIn);
                gMenuDelay = -1;
            } else if (D_801267D8[0] & 0x9000) {
                D_801263E0 = 1;
                func_80001D04(0x131, NULL);
            } else if (sp1C >= 2) {
                if (D_80126830 > 0) {
                    do {
                        vehicle--;
                    } while (!((1 << vehicle) & sp30) && (vehicle >= 0));
                }
                if (D_80126830 < 0) {
                    do {
                        vehicle++;
                    } while (!((1 << vehicle) & sp30) && (vehicle < 3));
                }
                if ((vehicle < 0) || (vehicle >= 3)) {
                    vehicle = vehicle2;
                }
                if (vehicle != vehicle2) {
                    func_80001D04(0xEB, NULL);
                    gPlayerSelectVehicle[0] = vehicle;
                }
            }
        }
    } else {
        if (gMenuDelay < 0) {
            gMenuDelay = gMenuDelay - arg0;
        } else {
            gMenuDelay = gMenuDelay + arg0;
        }
        if ((gMenuDelay >= 0x1F) || (gMenuDelay < -0x1E)) {
            func_80093A0C();
            if (gMenuDelay > 0) {
                return gTrackIdForPreview | 0x80;
            }
            return 0x103;
        }
    }
    gIgnorePlayerInput = 0;
    return 0;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_5_loop.s")
#endif

void func_80093A0C(void) {
    func_8009C4A8((s16 *)&D_800E0FB4);
    func_800C422C(2);
    func_80000B28();
}

GLOBAL_ASM("asm/non_matchings/menu/func_80093A40.s")

#ifdef NON_EQUIVALENT
// In the right ballpark, but not right.
void func_80093D40(s32 arg0) {
    s32 yOffset;
    s32 i;
    s32 xOffset;
    s32 x;
    ColourRGBA *colours;
    s32 xPos;
    s32 baseYPos;
    s32 alpha;

    i = 0;
    xPos = 160;
    if (D_800E0984 > 0) {
        do {
            //func_800C4DA0(text, x, font) x = diffX - x
            x = func_800C4DA0(&D_80126A40[i], 0, 0) + 8;
            if (xPos < x) {
                xPos = x;
            }
            i++;
        } while (i < D_800E0984);
    }
    if (osTvType == TV_TYPE_PAL) {
        baseYPos = 132;
    } else {
        baseYPos = 120;
    }
    func_800C56D0(7);
    assign_dialogue_box_id(7);
    yOffset = (s32) ((D_800E0984 * 16) + 28) >> 1;
    xOffset = xPos >> 1;
    set_current_dialogue_box_coords(7, 160 - xOffset, baseYPos - yOffset, xOffset + 160, yOffset + baseYPos);
    colours = &D_800E0990[get_player_id(D_800E098C)];
    set_current_dialogue_background_colour(7, colours->r, colours->g, colours->b, colours->a);
    set_dialogue_font(7, 0);
    set_current_text_background_colour(7, 128, 128, 255, 0);
    colours = &D_800E09A0[get_player_id(D_800E098C)];
    set_current_text_colour(7, colours->r, colours->g, colours->b, colours->a, 255);
    alpha = D_801263BC * 8;
    if (alpha >= 256) {
        alpha = 511 - alpha;
    }
    if (D_800E0988 != 0) {
        if (gTrophyRaceWorldId != 0) {
            i = yOffset - 26;
            render_dialogue_text(7, POS_CENTRED, i + 8, gMenuText[130], 1, 12); // QUIT TROPHY RACE?
        } else {
            i = yOffset - 26;
            render_dialogue_text(7, POS_CENTRED, i + 8, gMenuText[132], 1, 12); // QUIT GAME?
        }
        if (D_800E0988 == 1) {
            set_current_text_colour(7, 255, 255, 255, alpha, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, POS_CENTRED, i + 28, gMenuText[134], 1, 12); // OK
        if (D_800E0988 == 2) {
            set_current_text_colour(7, 255, 255, 255, alpha, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, POS_CENTRED, i + 44, gMenuText[85], 1, 12); // CANCEL
    } else {
        render_dialogue_text(7, POS_CENTRED, 12, gMenuText[133], D_800E098C + 1, 12); // PAUSE OPTIONS
        baseYPos = 32;
        if (D_800E0984 > 0) {
            do {
                if (i == D_80126A68) {
                    set_current_text_colour(7, 255, 255, 255, alpha, 255);
                } else {
                    set_current_text_colour(7, 255, 255, 255, 0, 255);
                }
                render_dialogue_text(7, POS_CENTRED, baseYPos, &D_80126A40[i], 1, 12);
                i++;
                baseYPos += 16;
            } while (i < D_800E0984);
        }
    }
    open_dialogue_box(7);
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80093D40.s")
#endif

GLOBAL_ASM("asm/non_matchings/menu/func_80094170.s")

void n_alSynRemovePlayer(void) {
    func_80072298(1);
    close_dialogue_box(7);
    assign_dialogue_box_id(7);
    D_800E0984 = 0;
}

void n_alSeqpDelete(void) {
    n_alSynRemovePlayer();
}

void func_80094604(void) {
    D_800E0A50[0].texture = D_80126550[50];
    D_800E0A60[0].texture = D_80126550[51];
    D_800E0A70[0].texture = D_80126550[52];
    D_800E0A90[0].texture = D_80126550[54];
    D_800E0A80[0].texture = D_80126550[53];
    D_800E0AA0[0].texture = D_80126550[55];
    D_800E0AB0[0].texture = D_80126550[56];
    D_800E0AC0[0].texture = D_80126550[57];
    D_800E0AD0[0].texture = D_80126550[58];
    D_800E0AE0[0].texture = D_80126550[59];
}

GLOBAL_ASM("asm/non_matchings/menu/func_80094688.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80094A5C.s")

void func_80094C14(s32 arg0) {
    D_801263BC = (D_801263BC + arg0) & 0x3F;
    D_80126A94 += arg0;
    if (D_801263D8 >= 0) {
        D_801263D8 += arg0;
        switch (D_800DF460) {
            case 0:
                if (func_8000C8B4(0xF0) < D_801263D8) {
                    set_music_fade_timer(-0x100);
                    D_800DF460 = 1;
                }
                break;
            case 1:
                if (func_8000C8B4(0x12C) < D_801263D8) {
                    set_music_player_voice_limit(0x18);
                    play_music(0x18);
                    set_music_fade_timer(0x100);
                }
                break;
        }
        if (func_8000C8B4(0x12C) < D_801263D8) {
            D_801263D8 = -1;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_80094D28.s")

#ifdef NON_EQUIVALENT
void func_80095624(s32 arg0) {
    switch (arg0 & 0xFF) {
        case 1:
        case 5:
            // Two addiu instructions need to swap positions here!
            D_80126C1C = D_800E09D8;
            break;
        case 4:
        case 6:
            // Two addiu instructions need to swap positions here!
            D_80126C1C = D_800E09C4;
            break;
        case 7:
            D_80126C1C = D_800E0A04;
            break;
        case 8:
            D_80126C1C = D_800E0A14;
            break;
        case 9:
            D_80126C1C = D_800E09EC;
            break;
        default:
            D_80126C1C = D_800E09B0;
            break;
    }

    for (D_80126C24 = 0; D_80126C1C[D_80126C24] != 0; D_80126C24++) {
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80095624.s")
#endif

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

    func_800981E8();
    func_80000968(0);
}

void menu_11_init(void) {
    Settings *settings;
    u16 *placements;
    s32 i;
    s8 temp_a2;

    settings = get_settings();
    D_80126BF0[0] = (s32)gMenuText[24];
    D_80126BF0[1] = (s32)gMenuText[23];
    D_80126BF0[2] = (s32)gMenuText[28];
    D_80126C14 = 3;

    for (i = 0; i < gNumberOfActivePlayers; i++) {
        temp_a2 = settings->racers[i].starting_position;
        if (temp_a2 < 4) {
            placements = settings->racers[i].placements;
            placements[temp_a2]++;
        }
    }

    D_801263E0 = -1;
    D_801263BC = 0;
    D_801263D8 = 0;
    gMenuDelay = 0;
    D_80126A68 = 0;
    gIgnorePlayerInput = 1;
    D_800E0988 = 0;
    func_8009C674(D_800E0A24);
    allocate_menu_images(D_800E0A40);
    func_80094604();
    func_800C4170(2);
    func_800C01D8(&sMenuTransitionFadeOut);
    set_music_player_voice_limit(0x18);
    play_music(0x18);
    set_music_fade_timer(0x80);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80096978.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_results_loop.s")

void func_800976CC(void) {
    func_8009C4A8(D_800E0A24);
    func_800C422C(2);
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
s32 compress_filename_string(unsigned char *filename, s32 length) {
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

#ifdef NON_EQUIVALENT

// Not matching, but functionally equivalent.
// Trims the trailing end of the string, so that spaces won't show up at the end.
s32 trim_filename_string(u8 *input, u8 *output) {
    s32 numSpaces, numSpacesProcessed;
    while (*input != '\0') {
        numSpaces = 0;
        numSpacesProcessed = 0;
        if (*input == ' ') {
            u8 *temp = input;
            temp++;
            numSpaces++;
            while (*temp == ' ') {
                temp++;
                numSpaces++;
            }
            if (*temp == '\0') {
                break;
            }
            while (numSpacesProcessed < numSpaces) {
                *(output++) = *(input++);
                numSpacesProcessed++;
            }
        } else {
            *(output++) = *(input++);
        }
    }
    *output = '\0';
}
#else
GLOBAL_ASM("asm/non_matchings/menu/trim_filename_string.s")
#endif

void func_80097874(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 arg5, s32 arg6) {
    D_800E0F90 = arg0;
    D_800E0F94 = arg1;
    D_800E0F98 = arg2;
    D_800E0F9C = arg3;
    D_80126C6C = arg4;
    D_80126C74 = arg5;
    D_80126C78 = arg6;
    D_800E0FA0 = 0;
    D_80126C50 = (f32)*D_80126C6C;
    gCheatInputString = NULL;
    D_80126C3C = 0;
    D_80126C34 = 0;
    func_800C4170(2);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80097918.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80097D10.s")

void func_800981E8(void) {
    func_800C422C(2);
}

// Gets triggered when entering trophy race in adventure mode.
void func_80098208(void) {
    Settings *settings = get_settings();
    gTrophyRaceWorldId = settings->worldId;
    D_800E0FEC = 0;
    settings->unk4C->unk0 = settings->courseId;
    settings->unk4C->unkF = 0;
    settings->unk4C->unk1 = 0;
    D_800DF450 = 1;
    set_time_trial_enabled(0);
}

#if 1
GLOBAL_ASM("asm/non_matchings/menu/menu_trophy_race_round_init.s")
#else
void menu_trophy_race_round_init(void) {
    s32 temp;
    s32 i;
    Settings *settings;
    s8 *temp_t9;

    settings = get_settings();
    temp_t9 = get_misc_asset(0x1A); // Returns level ids array.

    if (D_800E0FEC == 0) {
        for (i = 0; i < 8; i++) {
            settings->racers[i].trophy_points = 0;
        }
    }

    temp = temp_t9[((gTrophyRaceWorldId - 1) * 6) + D_800E0FEC];
    while (temp == -1) {
        temp = (temp + 1) & 3;
    }

    for (i = 0; i < gNumberOfActivePlayers; i++) {
        gPlayerSelectVehicle[i] = func_8006B0AC(temp);
    }

    func_8006DB14(func_8006B0AC(temp));
    load_level_for_menu(temp, -1, 1);

    gMenuDelay = 0;
    D_800E0980 = 10;
    func_800C4170(2);
    set_music_player_voice_limit(0x18);
    play_music(0x18);
    set_music_fade_timer(0x100);
}
#endif

void func_800983C0(UNUSED s32 arg0) {
    s32 yPos;
    char *sp28;
    char *sp24;
    s8 *sp20;

    sp20 = get_misc_asset(26);
    if (osTvType == TV_TYPE_PAL) {
        yPos = 18;
    } else {
        yPos = 0;
    }

    sp28 = func_8006BDDC(func_8006B1D4(gTrophyRaceWorldId));
    sp24 = func_8006BDDC(sp20[((gTrophyRaceWorldId - 1) * 6) + D_800E0FEC]);
    set_text_background_color(0, 0, 0, 0);
    set_text_font(FONT_LARGE);
    set_text_color(0, 0, 0, 255, 128);
    draw_text(&D_801263A0, 161, 35, sp28, 0xC);
    draw_text(&D_801263A0, 161, 67, gMenuText[70], 0xC); // TROPHY RACE
    set_text_color(255, 255, 255, 0, 255);
    draw_text(&D_801263A0, 160, 32, sp28, 0xC);
    draw_text(&D_801263A0, 160, 64, gMenuText[70], 0xC); // TROPHY RACE
    draw_text(&D_801263A0, 160, yPos + 176, gMenuText[138 + D_800E0FEC], 0xC); // ROUND ONE / ROUND TWO / ROUND THREE / ROUND FOUR
    draw_text(&D_801263A0, 160, yPos + 208, sp24, 0xC);
}

GLOBAL_ASM("asm/non_matchings/menu/menu_trophy_race_round_loop.s")

void func_80098754(void) {
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80098774.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_trophy_race_rankings_init.s")

#ifdef NON_EQUIVALENT
void func_80098EBC(s32 arg0) {
    s32 test;
    s32 fade;
    s32 i;

    D_801263BC = (D_801263BC + arg0) & 0x3F;

    test = D_801263BC * 8;
    if (test >= 0x100) {
        test = 0x1FF - test;
    }

    // Has regalloc issues starting here.
    for (i = 0; i < D_800E0FE4; i++) {
        fade = 0xFF;

        if (gNumberOfActivePlayers < 3 && ((D_801263E0 == 0 && D_80126418[i]) || (D_801263E0 != 0 && D_80126420[i]))) {
            fade = (test >> 1) + 0x80;
        }

        D_800E1048[i][0].filterRed = fade;
        D_800E1048[i][0].filterGreen = fade;
        D_800E1048[i][0].filterBlue = fade;
    }

    if (D_801263E0 == 2 || D_801263E0 == 3) {
        draw_menu_elements(1, &D_800E1048, 1.0f);
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/func_80098EBC.s")
#endif

GLOBAL_ASM("asm/non_matchings/menu/menu_trophy_race_rankings_loop.s")

void func_80099600(void) {
    func_8009C4A8(D_800E1024);
    func_800C422C(2);
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
    s32 sp70;

    sp70 = func_800756D4(D_801264D0, &D_801264DC, &D_801264EC, &D_801264E4, &D_801264F8);
    if (sp70 == 0) {
        func_8009963C();
    }
    func_8009C674(&D_800E1708);
    allocate_menu_images(&D_800E174C);
    func_800C4170(2);
    D_800E153C[0].texture = D_80126550[14];
    D_800E153C[5].texture = D_80126550[15];
    D_800E1594[0].texture = D_80126550[16];
    D_800E1594[5].texture = D_80126550[17];
    D_800E15EC[0].texture = D_80126550[18];
    D_800E15EC[5].texture = D_80126550[19];
    D_800E1644[0].texture = D_80126550[20];
    D_800E1644[5].texture = D_80126550[21];
    D_800E169C[0].texture = D_80126550[22];
    D_800E169C[5].texture = D_80126550[23];
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
    func_8008E45C();
    func_80094604();
    func_8008E4B0();
    D_801263BC = 0;
    D_801263E0 = 0;
    D_801263D8 = 0;
    gMenuDelay = 0;
    D_80126498 = 0;
    if (sp70 == 0) {
        func_800C01D8(&sMenuTransitionFadeOut);
        return;
    }
    gMenuDelay = 0x1E;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_ghost_data_init.s")
#endif

GLOBAL_ASM("asm/non_matchings/menu/func_80099E8C.s")

#ifdef NON_EQUIVALENT
// Regalloc issue: v0 & v1 need to swap!
s32 menu_ghost_data_loop(s32 arg0) {
    s32 i;
    s32 pressedButtons, xStick, yStick;
    s32 temp;
    s32 tempDelay;

    D_801263BC = (D_801263BC + arg0) & 0x3F;

    if ((gMenuDelay >= -0x13) && (gMenuDelay < 0x14)) {
        func_80099E8C();
    }

    pressedButtons = 0;
    if (gMenuDelay != 0) {
        if (gMenuDelay < 0) {
            gMenuDelay -= arg0;
        } else {
            gMenuDelay += arg0;
        }
    }

    xStick = 0;
    yStick = 0;
    if (!gIgnorePlayerInput && gMenuDelay == 0) {
        for (i = 0; i < 4; i++) {
            pressedButtons |= get_buttons_pressed_from_player(i);
            xStick += gControllersXAxisDirection[i];
            yStick += gControllersYAxisDirection[i];
        }
    }

    switch (D_801263E0) {
        case 0:
            if ((pressedButtons & (START_BUTTON | A_BUTTON)) && (D_801264D4 > 0)) {
                D_801263E0 = 2;
                func_80001D04(0xEF, 0);
            } else if ((pressedButtons & B_BUTTON) || ((pressedButtons & (START_BUTTON | A_BUTTON)) && (D_801264D4 == 0))) {
                gMenuDelay = 1;
                func_800C01D8(&sMenuTransitionFadeIn);
                func_80001D04(0x241, 0);
            } else {
                temp = D_80126498;
                if (yStick < 0 && D_80126498 < (D_801264D4 - 1)) {
                    D_80126498++;
                    if (D_80126498 >= D_801263D8 + 3) {
                        D_801263D8 = D_80126498 - 2;
                    }
                }
                if (yStick > 0 && D_80126498 > 0) {
                    D_80126498--;
                    if (D_80126498 < D_801263D8) {
                        D_801263D8 = D_80126498;
                    }
                }
                if (temp != D_80126498) {
                    func_80001D04(0xEB, 0);
                }
            }
            break;
        case 1:
            if (pressedButtons & B_BUTTON) {
                D_801263E0 = 0;
                func_80001D04(0x241, 0);
            } else {
                if (pressedButtons & (START_BUTTON | A_BUTTON)) {
                    if (func_800998E0(D_80126498) == 0) {
                        if (D_80126498 >= D_801264D4) {
                            D_80126498 = D_801264D4 - 1;
                        }
                        if (D_80126498 < 0) {
                            D_80126498 = 0;
                        }
                        if (D_80126498 < D_801263D8) {
                            D_801263D8 = D_80126498;
                        }
                        func_80001D04(0xEF, 0);
                    } else {
                        gMenuDelay = 1;
                        func_800C01D8(&sMenuTransitionFadeIn);
                        func_80001D04(0x241, 0);
                    }
                    D_801263E0 = 0;
                } else if (yStick < 0) {
                    D_801263E0 = 2;
                    func_80001D04(0xEB, 0);
                }
            }
            break;
        case 2:
            if (pressedButtons & (START_BUTTON | A_BUTTON | B_BUTTON)) {
                D_801263E0 = 0;
                func_80001D04(0x241, 0);
            } else if (yStick > 0) {
                D_801263E0 = 1;
                func_80001D04(0xEB, 0);
            }
            break;
    }

    gIgnorePlayerInput = FALSE;
    if (gMenuDelay >= 0x1F) {
        func_8009ABAC();
        menu_init(MENU_SAVE_OPTIONS);
    }
    return 0;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_ghost_data_loop.s")
#endif

void func_8009ABAC(void) {
    func_8009C4A8(D_800E1708);
    func_800C422C(2);
}

void func_8009ABD8(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 phi_v1;

    phi_v1 = 0;
    while (phi_v1 < arg1) {
        phi_v1++;
        while (-1 != *arg0) {
            arg0 += 3;
        }
        arg0++;
    }

    if ((phi_v1 == 0) && (get_misc_asset(0x19) == (s32 *)arg0)) {
        D_8012684C = 1;
    } else {
        D_8012684C = 0;
    }

    D_801267EC = arg0;
    D_80126824 = arg2;
    D_8012683C = arg3;
    D_80126844 = arg4;
    D_80126804 = arg5;
}

void menu_23_init(void) {
    if (D_80126804 != 0) {
        func_8009C674(D_800E1768);
        func_80094604();
    }
    load_level_for_menu(D_801267EC[0], D_801267EC[1], D_801267EC[2]);
    gMenuDelay = 0;
    D_801263E0 = 0;
}

GLOBAL_ASM("asm/non_matchings/menu/menu_23_loop.s")

void func_8009AF18(void) {
    if (D_80126804 != 0) {
        func_8009C4A8(D_800E1768);
    }
}

void menu_credits_init(void) {
    s32 cheat;
    s32 cheatIndex;
    u16 *cheatOffsets;
    Settings *settings;

    settings = get_settings();
    gMenuDelay = 0;
    D_80126BC4 = 0;
    D_80126BCC = 0;
    D_801263E0 = 0;
    D_801263D8 = 0x28;
    D_800DF460 = 0;
    D_80126BD0 = 0;
    D_80126BD8 = 0;
    D_80126BE0 = 0;
    set_background_fill_colour(0, 0, 0);
    if (osTvType == TV_TYPE_PAL) {
        func_80066940(0, 0, 38, SCREEN_WIDTH, 224);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT + 44);
    } else {
        func_80066940(0, 0, 40, SCREEN_WIDTH, 196);
        set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    func_80066610();
    func_80066818(0, 1);
    func_8009C674(D_800E17D8);
    allocate_menu_images(D_800E17F0);
    func_80094604();
    func_800C4170(2);
    set_music_player_voice_limit(0x18);
    D_800E18F8 = (u16)0x1000;
    if (gViewingCreditsFromCheat) {
        play_music(8);
        gCreditsArray[84] = gCreditsLastMessageArray[2]; // "THE END"
        gCreditsArray[85] = gCreditsLastMessageArray[3]; // "NO CHEAT"
        gCreditsArray[86] = gCreditsLastMessageArray[4]; // "THIS TIME."
        gViewingCreditsFromCheat = 0;
    } else {
        if (settings->bosses & 0x20) {
            play_music(0x25);
            gCreditsArray[84] = gCreditsLastMessageArray[1]; // "TO BE CONTINUED ..."
            D_800E18F8 = (u16)0x61F4;
            D_80126BCC = 9;
        } else {
            play_music(8);
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
    func_800C0170();
    func_8006F564(1);
}

void func_8009B1E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg4 >= 0x100) {
        arg4 = 0xFF;
    }
    if (arg4 < 0) {
        arg4 = 0;
    }

    gSPDisplayList(D_801263A0++, D_800E1780);
    gDPSetPrimColor(D_801263A0++, 0, 0, 0, 0, 0, arg4);
    gDPSetCombineMode(D_801263A0++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPFillRectangle(D_801263A0++, arg0, arg1, arg0 + arg2, arg1 + arg3);
    gDPPipeSync(D_801263A0++);
    gDPSetPrimColor(D_801263A0++, 0, 0, 255, 255, 255, 255);

    func_8007B3D0(&D_801263A0);
}

GLOBAL_ASM("asm/non_matchings/menu/menu_credits_loop.s")

void func_8009BCF0(void) {
    set_music_player_voice_limit(0x12);
    func_800C0180();
    func_80066894(0, 0);
    set_viewport_properties(0, VIEWPORT_AUTO, VIEWPORT_AUTO, VIEWPORT_AUTO, VIEWPORT_AUTO);
    func_8009C4A8(D_800E17D8);
    func_800C422C(2);
    func_8006F564(0);
}

void func_8009BD5C(void) {
    unk80069D20 *temp_v0;
    s16 sp2A;
    s16 sp28;
    s16 sp26;
    f32 sp20;
    f32 sp1C;
    f32 sp18;

    func_8006652C(0);
    func_800665E8(0);

    temp_v0 = (unk80069D20 *)func_80069D20();

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

    func_8001D5E0(0, 0, -1);
    func_80066CDC(&D_801263A0, &D_801263A8);

    temp_v0->unk0 = sp2A;
    temp_v0->unk2 = sp28;
    temp_v0->unk4 = sp26;
    temp_v0->unkC = sp20;
    temp_v0->unk10 = sp1C;
    temp_v0->unk14 = sp18;
}

void func_8009BE54() {
}

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

#ifdef NON_EQUIVALENT

#define STICK_DEADZONE 35
#define STICK_DELAY_AMOUNT 15

// Should be functionally equivalent
void update_controller_sticks(void) {
    s32 prevXAxis, prevYAxis;
    s32 i;
    for (i = 0; i < 4; i++) {
        prevXAxis = gControllersXAxis[i];
        prevYAxis = gControllersYAxis[i];
        gControllersXAxis[i] = clamp_joystick_x_axis(i);
        gControllersYAxis[i] = clamp_joystick_y_axis(i);
        gControllersXAxisDirection[i] = 0;
        gControllersYAxisDirection[i] = 0;
        if (gControllersXAxis[i] < -STICK_DEADZONE && prevXAxis > -STICK_DEADZONE) {
            gControllersXAxisDirection[i] = -1;
            gControllersXAxisDelay[i] = 0;
        }
        if (gControllersXAxis[i] > STICK_DEADZONE && prevXAxis < STICK_DEADZONE) {
            gControllersXAxisDirection[i] = 1;
            gControllersXAxisDelay[i] = 0;
        }
        if (gControllersYAxis[i] < -STICK_DEADZONE && prevYAxis > -STICK_DEADZONE) {
            gControllersYAxisDirection[i] = -1;
            gControllersYAxisDelay[i] = 0;
        }
        if (gControllersYAxis[i] > STICK_DEADZONE && prevYAxis < STICK_DEADZONE) {
            gControllersYAxisDirection[i] = 1;
            gControllersYAxisDelay[i] = 0;
        }
        if (gControllersYAxis[i] < -STICK_DEADZONE) {
            gControllersYAxisDelay[i]++;
        } else if (gControllersYAxis[i] > STICK_DEADZONE) {
            gControllersYAxisDelay[i]++;
        } else {
            gControllersYAxisDelay[i] = 0;
        }
        if (gControllersYAxisDelay[i] > STICK_DELAY_AMOUNT) {
            gControllersYAxis[i] = 0;
            gControllersYAxisDelay[i] = 0;
        }
        if (gControllersXAxis[i] < -STICK_DEADZONE) {
            gControllersXAxisDelay[i]++;
        } else if (gControllersXAxis[i] > STICK_DEADZONE) {
            gControllersXAxisDelay[i]++;
        } else {
            gControllersXAxisDelay[i] = 0;
        }
        if (gControllersXAxisDelay[i] > STICK_DELAY_AMOUNT) {
            gControllersXAxis[i] = 0;
            gControllersXAxisDelay[i] = 0;
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/update_controller_sticks.s")
#endif

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
    if (gActivePlayersArray[controllerIndex] == 0) {
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
    if (!func_8006B240()) {
        cheats &= ~CHEAT_MIRRORED_TRACKS; // Disable mirroring
    }
    if (func_8006B14C(get_settings()->courseId) & 0x40) {
        cheats &= CHEATS_ALLOWED_IN_CHALLENGES;
    }
    if (gIsInAdventureTwo && func_8006B240()) {
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

Settings **func_8009C490(void) {
    return (Settings **)D_80126530;
}

void func_8009C49C(void) {
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
        if (D_80126550[arg0] != 0) {
            if ((((*D_800DF750)[arg0] & 0xC000) == 0xC000) && (D_80126550[arg0] != 0)) {
                set_free_queue_state(0);
                free_texture((u32)D_80126550[arg0]);
                set_free_queue_state(2);
            } else {
                if ((*D_800DF750)[arg0] & 0x8000) {
                    free_sprite((u32)D_80126550[arg0]);
                } else {
                    if ((*D_800DF750)[arg0] & 0x4000) {
                        gParticlePtrList_addObject((u32)D_80126550[arg0]);
                    } else {
                        func_8005FF40((u32)D_80126550[arg0]);
                    }
                }
            }
        }
        D_80126550[arg0] = 0;
        D_80126750[arg0] = 0;
        D_800DF758--;
        gParticlePtrList_flush();
    }
    if (D_800DF758 == 0) {
        if (gMenuImageStack != NULL) {
            free_from_memory_pool(gMenuImageStack);
            gMenuImageStack = NULL;
        }
        if (*D_800DF750 != NULL) {
            free_from_memory_pool(*D_800DF750);
            *D_800DF750 = NULL;
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
        gMenuImageStack = allocate_from_main_pool_safe(sizeof(unk800DF510) * 18, COLOR_TAG_RED);
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

GLOBAL_ASM("asm/non_matchings/menu/func_8009CA60.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8009CD7C.s")

void func_8009CF68(s32 arg0) {
    if (D_800DF4E4[arg0] == 0) {
        if (arg0 != 3) {
            sCurrentMenuID = 0;
            sDialogueOption = 0;
        }
        D_800DF4E0 = 1;
        D_800DF4E4[arg0] = 1;
    }
}

void func_8009CFB0(void) {
    if (D_800DF4E0 != 0) {
        D_800DF4E0 = 0;
        close_dialogue_box(1);
        reset_controller_sticks();
    }
}

s32 func_8009CFEC(u32 dialogueOption) {
    s32 result;

    D_800DF4E4[dialogueOption] = 0;
    if ((func_800C3400() != 0) && (dialogueOption != DIALOG_CHALLENGE)) {
        return 0;
    }
    if (D_800DF4E0 != 0) {
        return 0;
    }
    if (dialogueOption != DIALOG_CHALLENGE) {
        func_8006F388(1);
    }
    result = 0;
    update_controller_sticks();
    assign_dialogue_box_id(1);
    open_dialogue_box(1);
    set_current_dialogue_background_colour(1, 0, 0, 0, 0x80);
    func_8001F450();
    switch (dialogueOption) {
        case DIALOG_TAJ:
            result = taj_menu_loop(); // Taj menu
            break;
        case DIALOG_TT:
            result = tt_menu_loop(); // T.T. menu
            break;
        case DIALOG_CHALLENGE:
            result = func_800C3564(); // Taj challenge completed/failed menu
            break;
        case DIALOG_TROPHY:
            result = trophy_race_cabinet_menu_loop(); // Trophy race cabinet menu
            break;
        case DIALOG_RACERESULT:
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
        if (gDialogOptionTangible != FALSE) {
            set_current_text_colour(1, 0, 0, 0x7F, 0x5A, 0x78); //Locked
        }
    } else {
        set_current_text_colour(1, 0xCF, 0xCF, 0xCF, 0x5A, 0xFF); // Selected Option
    }
    gDialogOptionTangible = (u8)FALSE;
}

/**
 * Render a line of text at a given Y position, and pass through the text ID and option ID.
 */
void render_dialogue_option(char *text, s32 yOffset, s32 optionID) {
    set_option_text_colour(sDialogueOption == sDialogueOptionMax);
    if (sDialogueOption == sDialogueOptionMax) {
        D_80126516 = optionID;
    }
    render_dialogue_text(1, POS_CENTRED, gDialogOptionYOffset, text, 1, 4);
    gDialogOptionYOffset = (s8)(gDialogOptionYOffset + yOffset);
    sDialogueOptionMax = (s8)(sDialogueOptionMax + 1);
}

/**
 * Sets dialogue option when the joystick is moved.
 * Will wrap around if it goes out of bounds.
 */
void handle_menu_joystick_input(void) {
    if (gControllersYAxisDirection[0] < 0) {
        sDialogueOption = sDialogueOption + 1;
        func_80001D04(0xB2, NULL);
    } else if (gControllersYAxisDirection[0] > 0) {
        sDialogueOption = sDialogueOption - 1;
        func_80001D04(0xB2, NULL);
    }

    if (sDialogueOption < 0) {
        sDialogueOption = sDialogueOptionMax - 1;
    }

    if (sDialogueOption >= sDialogueOptionMax) {
        sDialogueOption = 0;
    }
}

void func_8009D324(void) {
    D_800DF4D8 = 0;
}

void func_8009D330(s32 arg0) {
    D_800DF4DC = arg0;
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
    if ((D_800DF4DC != 0) && (sCurrentMenuID == 0)) {
        sCurrentMenuID = -D_800DF4DC;
    }
    if (sCurrentMenuID == 0) {
        sCurrentMenuID = 1;
    }
    if ((sCurrentMenuID > 0) && (sCurrentMenuID < 4)) {
        set_current_dialogue_box_coords(1, 24, 16, 184, 124);
        set_dialogue_font(1, FONT_COLOURFUL);
    }
    sp2C = 0;
    buttonsPressed = get_buttons_pressed_from_player(0);
    sDialogueOptionMax = 0;

    switch (sCurrentMenuID) {
        case 2:
        case 0x62:
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[40], 1, 4); // VEHICLE SELECT
            gDialogOptionYOffset = 30;
            render_dialogue_option(gMenuText[41], 20, 0); // CAR
            render_dialogue_option(gMenuText[42], 20, 1); // HOVERCRAFT
            render_dialogue_option(gMenuText[43], 20, 2); // PLANE
            render_dialogue_option(gMenuText[44], 20, 3); // MAIN MENU
            break;
        case 3:
        case 0x63:
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[45], 1, 4); // CHALLENGE SELECT
            gDialogOptionYOffset = 30;
            if (settings->tajFlags & TAJ_FLAGS_CAR_CHAL_UNLOCKED) {
                gDialogOptionTangible = settings->tajFlags & TAJ_FLAGS_CAR_CHAL_COMPLETED;
                render_dialogue_option(gMenuText[46], 0x14, 0); // CAR CHALLENGE
            }
            if (settings->tajFlags & TAJ_FLAGS_HOVER_CHAL_UNLOCKED) {
                gDialogOptionTangible = settings->tajFlags & TAJ_FLAGS_HOVER_CHAL_COMPLETED;
                render_dialogue_option(gMenuText[47], 0x14, 1); // HOVER CHALLENGE
            }
            if (settings->tajFlags & TAJ_FLAGS_PLANE_CHAL_UNLOCKED) {
                gDialogOptionTangible = settings->tajFlags & TAJ_FLAGS_PLANE_CHAL_COMPLETED;
                render_dialogue_option(gMenuText[48], 0x14, 2); // PLANE CHALLENGE
            }
            render_dialogue_option(gMenuText[44], 0x14, 3); // MAIN MENU
            break;
    }

    switch (sCurrentMenuID) {
        case 0:
            func_800C31EC(7);
            sCurrentMenuID = 1;
            D_800DF4D8 = 1;
            break;
        case 1:
            D_800DF4DC = 0;
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[36], 1, 4); // OPTIONS
            gDialogOptionYOffset = 30;
            render_dialogue_option(gMenuText[37], 0x14, 0); // CHANGE VEHICLE
            if (settings->tajFlags & TAJ_FLAGS_UNLOCKED_A_CHALLENGE) {
                render_dialogue_option(gMenuText[39], 0x14, 1); // CHALLENGES
            }
            render_dialogue_option(gMenuText[5], 0x14, 2); // RETURN
            handle_menu_joystick_input();
            if (buttonsPressed & B_BUTTON) {
                sp2C = 3;
                func_80001D04(0x241, 0);
            } else if (buttonsPressed & A_BUTTON) {
                func_80001D04(0xEF, 0);
                switch (D_80126516) {
                    case 1:
                        sCurrentMenuID = 3;
                        sDialogueOption = 0;
                        func_8003AC3C(0x239, 1);
                        break;
                    case 2:
                        sp2C = 3;
                        break;
                    case 0:
                        sCurrentMenuID = 2;
                        sDialogueOption = 0;
                        func_8003AC3C(0x234, 1);
                        break;
                }
            }
            break;
        case 2:
            handle_menu_joystick_input();
            if (buttonsPressed & B_BUTTON) {
                func_80001D04(0x241, 0);
                func_8003AC3C(0x238, 1);
                sCurrentMenuID = 1;
                sDialogueOption = 0;
            } else if (buttonsPressed & A_BUTTON) {
                if (D_80126516 != 3) {
                    sp2C = D_80126516 | 0x80;
                    sCurrentMenuID = 0x62;
                } else {
                    sCurrentMenuID = 1;
                    sDialogueOption = 0;
                    func_8003AC3C(0x238, 1);
                }
            }
            break;
        case 3:
            handle_menu_joystick_input();
            if ((buttonsPressed & B_BUTTON) || ((buttonsPressed & A_BUTTON) && (D_80126516 == 3))) {
                func_80001D04(0x241, 0);
                func_8003AC3C(0x23A, 1);
                sCurrentMenuID = 1;
                sDialogueOption = 3;
            } else if (buttonsPressed & A_BUTTON) {
                sp2C = D_80126516 | 0x40;
                func_80001D04(0xEF, 0);
                sCurrentMenuID = 0x63;
            }
            break;
        case -3:
        case -2:
        case -1:
            func_800C31EC(8 - sCurrentMenuID);
            sCurrentMenuID = 4;
            break;
        case -4:
            func_800C31EC(0x11);
            D_800DF4DC = 0;
            sCurrentMenuID = 1;
            sDialogueOption = 3;
            break;
        case -5:
            func_800C31EC(0x15);
            D_800DF4DC = 0;
            sCurrentMenuID = 7;
            sDialogueOption = 0;
            break;
        case -8:
        case -7:
        case -6:
            func_800C31EC(0xC - sCurrentMenuID);
            sCurrentMenuID = 6;
            sDialogueOption = 0;
            break;
        case 4:
            sp2C = (D_800DF4DC - 1) | 0x40;
            sCurrentMenuID = 5;
            close_dialogue_box(1);
            break;
        case 5:
            D_800DF4DC = 0;
            close_dialogue_box(1);
            break;
        case 6:
        case 7:
            sp2C = 4;
            if (sCurrentMenuID == 7) {
                sp2C = 3;
            }
            D_800DF4E0 = 0;
            close_dialogue_box(1);
            D_800DF4DC = 0;
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

    set_current_dialogue_box_coords(1, 0x18, 0x10, 0xB8, 0x87);
    set_dialogue_font(1, FONT_COLOURFUL);
    state = 0;
    playerInput = get_buttons_pressed_from_player(0);
    sDialogueOptionMax = 0;
    D_800DF4DC = 0;
    render_dialogue_text(1, POS_CENTRED, 6, gMenuText[49], 1, 4);    // BETTER LUCK
    render_dialogue_text(1, POS_CENTRED, 20, gMenuText[50], 1, 4); // NEXT TIME!
    gDialogOptionYOffset = 50;
    render_dialogue_option(gMenuText[23], 20, 0); // TRY AGAIN
    render_dialogue_option(gMenuText[51], 20, 1); // EXIT
    handle_menu_joystick_input();
    if (playerInput & A_BUTTON) {
        func_80001D04(0xEF, NULL);
        switch (D_80126516) {
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

#ifdef NON_MATCHING

// Has a couple minor issues, but should be functionally equivalent.
s32 tt_menu_loop(void) {
    s32 currentOption;
    s32 buttonsPressed;
    s32 i;
    s32 yPos1;
    s32 yPos2;
    Settings *settings;
    s32 result;

    settings = get_settings();

    if (is_in_two_player_adventure()) {
        settings->cutsceneFlags |= 2;
    }
    if (!(settings->cutsceneFlags & 2)) {
        sCurrentMenuID = TT_MENU_INTRODUCTION;
    }
    if ((sCurrentMenuID != TT_MENU_GAME_STATUS) && (sCurrentMenuID != TT_MENU_INTRODUCTION)) {
        currentOption = 0x78;
        if (func_8001B780() != 0) {
            currentOption = 0x88;
        }
        set_current_dialogue_box_coords(1, 0x18, 0x10, 0xC0, currentOption);
    } else {
        set_current_dialogue_box_coords(1, 0x18, 0x10, 0xB8, 0xDC);
    }
    set_dialogue_font(1, FONT_COLOURFUL);
    currentOption = 0;
    buttonsPressed = get_buttons_pressed_from_player(0);
    sDialogueOptionMax = 0;
    gDialogOptionYOffset = 32;
    switch (sCurrentMenuID) {
        case TT_MENU_ROOT:
        case TT_MENU_EXIT:
            render_dialogue_text(1, POS_CENTRED, 6, gMenuText[36], 1, 4); // OPTIONS
            render_dialogue_option(gMenuText[71], 0x14, 3);             // STATUS
            if (!is_in_two_player_adventure()) {
                if (is_time_trial_enabled()) {
                    render_dialogue_option(gMenuText[65], 0x14, 0); // TIME TRIAL ON
                } else {
                    render_dialogue_option(gMenuText[66], 0x14, 0); // TIME TRIAL OFF
                }
                if (func_8001B780() != 0) {
                    render_dialogue_option(gMenuText[27], 0x14, 1); // SAVE GHOST
                }
            }
            render_dialogue_option(gMenuText[5], 0x14, 2); // RETURN
            handle_menu_joystick_input();
            if (D_80126516 == 0) {
                if (gControllersXAxisDirection[0] > 0) {
                    if (!is_time_trial_enabled()) {
                        func_80036BCC(0x231, 1);
                    }
                    set_time_trial_enabled(TRUE);
                } else if (gControllersXAxisDirection[0] < 0) {
                    if (is_time_trial_enabled() == 1) {
                        func_80036BCC(0x230, 1);
                    }
                    set_time_trial_enabled(FALSE);
                }
            }
            if ((buttonsPressed & A_BUTTON) && (sCurrentMenuID != TT_MENU_EXIT)) {
                switch (D_80126516) {
                    case 1:
                        func_80001D04(0xEF, 0);
                        D_80126398 = 0;
                        D_8012639C = TT_MENU_ROOT;
                        sCurrentMenuID = TT_MENU_SAVE_GHOST;
                        break;
                    case 3:
                        func_80001D04(0xEF, 0);
                        func_80036BCC(0x22E, 1);
                        func_8009C674(D_800E1E2C);
                        allocate_menu_images(D_800E1E40);
                        D_800E1E28 = 1;
                        sCurrentMenuID = TT_MENU_GAME_STATUS;
                        break;
                }
                currentOption = D_80126516 + 1;
            } else if (buttonsPressed & B_BUTTON) {
                func_80001D04(0x241, 0);
                currentOption = 3;
            }
            if (sCurrentMenuID == TT_MENU_GAME_STATUS) {
                currentOption = 0;
            }
            if (currentOption == 3) {
                //FAKEMATCH?
                //if ((gControllersXAxisDirection && gControllersXAxisDirection) && gControllersXAxisDirection){}
                sCurrentMenuID = TT_MENU_EXIT;
            }
            if (sCurrentMenuID == TT_MENU_EXIT) {
                currentOption = 3;
            }
            break;
        case TT_MENU_CONT_PAK_ERROR_1:
            i = 0;
            while (D_801263A4[i] != NULL) {
                i++;
            }
            yPos1 = 58;
            if (i > 0) {
                i--;
                yPos1 -= (i * 8);
                i = 0;
                while (D_801263A4[i] != NULL) {
                    render_dialogue_text(1, POS_CENTRED, yPos1, D_801263A4[i], 1, 4);
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
                func_80036BCC(0x22F, 1);
            }
            break;
        case TT_MENU_INTRODUCTION:
            // RIGHT HERE is where I to swap the timing of assignment of these two vars
            yPos2 = 6;
            i = 52;
            while (gMenuText[i] != NULL) {
                render_dialogue_text(1, POS_CENTRED, yPos2, gMenuText[i], 1, 4);
                yPos2 += 16;
                i++;
            }
            if (buttonsPressed & (A_BUTTON | B_BUTTON)) {
                settings->cutsceneFlags |= 2;
                sCurrentMenuID = TT_MENU_ROOT;
            }
            break;
        case TT_MENU_INSERT_CONT_PAK:
            render_dialogue_text(1, POS_CENTRED, 34, gMenuText[159], 1, 4); // If you wish to use
            render_dialogue_text(1, POS_CENTRED, 50, gMenuText[160], 1, 4); // the Controller Pak
            render_dialogue_text(1, POS_CENTRED, 66, gMenuText[162], 1, 4); // insert it now!
            if (buttonsPressed & (A_BUTTON | START_BUTTON)) {
                func_80001D04(0xEF, 0);
                D_80126398 = 0;
                D_8012639C = TT_MENU_INSERT_RUMBLE_PAK;
                sCurrentMenuID = TT_MENU_SAVE_GHOST;
            } else if (buttonsPressed & B_BUTTON) {
                func_80001D04(0x241, 0);
                sCurrentMenuID = TT_MENU_ROOT;
            }
            break;
        case TT_MENU_INSERT_RUMBLE_PAK:
            render_dialogue_text(1, POS_CENTRED, 34, gMenuText[159], 1, 4); // If you wish to use
            render_dialogue_text(1, POS_CENTRED, 50, gMenuText[161], 1, 4); // the Rumble Pak
            render_dialogue_text(1, POS_CENTRED, 66, gMenuText[162], 1, 4); // insert it now!
            if (buttonsPressed & (A_BUTTON | B_BUTTON | START_BUTTON)) {
                sCurrentMenuID = TT_MENU_ROOT;
            }
            break;
        case TT_MENU_SAVE_GHOST:
            render_dialogue_text(1, POS_CENTRED, 50, gMenuText[124], 1, 4); // PLEASE WAIT
            D_80126398++;
            if (D_80126398 >= 5) {
                result = func_8001B738(0) & 0xFF;
                if (result == CONTROLLER_PAK_CHANGED) {
                    result = func_8001B738(0) & 0xFF;
                }
                switch (result) {
                    case CONTROLLER_PAK_GOOD:
                        sCurrentMenuID = D_8012639C;
                        break;
                    case RUMBLE_PAK:
                        sCurrentMenuID = TT_MENU_INSERT_CONT_PAK;
                        break;
                    case NO_CONTROLLER_PAK:
                        // NO CONTROLLER PAK
                        // If you wish to change / Controller Pak or Rumble Pak, / please do so now.
                        D_801263A4 = D_800E09D8;
                        sCurrentMenuID = TT_MENU_CONT_PAK_ERROR_1;
                        break;
                    case CONTROLLER_PAK_FULL:
                    case CONTROLLER_PAK_UNK6:
                        // CONTROLLER PAK FULL
                        // If you wish to change / Controller Pak or Rumble Pak, / please do so now.
                        D_801263A4 = D_800E09C4;
                        sCurrentMenuID = TT_MENU_CONT_PAK_ERROR_1;
                        break;
                    case CONTROLLER_PAK_BAD_DATA:
                        // CORRUPT DATA.
                        // If you wish to change / Controller Pak or Rumble Pak, / please do so now.
                        // TRY AGAIN!
                        D_801263A4 = D_800E09EC;
                        sCurrentMenuID = TT_MENU_CONT_PAK_ERROR_1;
                        break;
                    case CONTROLLER_PAK_INCONSISTENT:
                    case CONTROLLER_PAK_WITH_BAD_ID:
                    case CONTROLLER_PAK_CHANGED:
                    case CONTROLLER_PAK_UNK8:
                    default:
                        // BAD CONTROLLER PAK
                        // If you wish to change / Controller Pak or Rumble Pak, / please do so now.
                        D_801263A4 = D_800E09B0;
                        sCurrentMenuID = TT_MENU_CONT_PAK_ERROR_1;
                        break;
                }
            }
            break;
    }
    if ((sCurrentMenuID == TT_MENU_CONT_PAK_ERROR_1) ||
        (sCurrentMenuID == TT_MENU_CONT_PAK_ERROR_2) ||
        (sCurrentMenuID == TT_MENU_CONT_PAK_ERROR_3)) {
        render_dialogue_text(1, POS_CENTRED, 6, gMenuText[64], 1, 4); // PAK ERROR
    }

    return currentOption;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/tt_menu_loop.s")
#endif

GLOBAL_ASM("asm/non_matchings/menu/func_8009E3D0.s")

/**
 * Dialogue menu for the trophy cabinets in each world hub.
 */
s32 trophy_race_cabinet_menu_loop(void) {
    s32 currentOption;
    s32 buttonsPressed;

    set_current_dialogue_box_coords(1, 0x18, 0x10, 0xB8, 0x78);
    set_dialogue_font(1, FONT_COLOURFUL);
    currentOption = 0;
    buttonsPressed = get_buttons_pressed_from_player(0);
    render_dialogue_text(1, POS_CENTRED, 6, gMenuText[70], 1, 4); // TROPHY RACE
    if (gControllersYAxisDirection[0] < 0) {
        sDialogueOption++;
    } else if (gControllersYAxisDirection[0] > 0) {
        sDialogueOption--;
    }
    if (sDialogueOption < 0) {
        sDialogueOption = 0;
    }
    if (sDialogueOption > 1) {
        sDialogueOption = 1;
    }
    set_option_text_colour(sDialogueOption == 0);
    render_dialogue_text(1, POS_CENTRED, 30, gMenuText[180], 1, 4); // ENTER TROPHY RACE
    set_option_text_colour(sDialogueOption == 1);
    render_dialogue_text(1, POS_CENTRED, 50, gMenuText[51], 1, 4); // EXIT
    if (buttonsPressed & A_BUTTON) {
        currentOption = sDialogueOption + 1;
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
f32 func_8009E9B0(UNUSED DialogueBoxBackground *textbox, Gfx **dlist, Gfx **mat, VertexList **verts) {
    D_801263A0 = *dlist;
    D_801263A8 = *mat;
    D_801263AC = *verts;
    func_80067F2C(&D_801263A0, (s32 *)&D_801263A8);
    if (D_800E1E28 != 0 && sCurrentMenuID == 4) {
        func_8009E3D0();
    }
    *dlist = D_801263A0;
    *mat = D_801263A8;
    *verts = D_801263AC;
    return TRUE;
}

u64 *get_eeprom_settings_pointer(void) {
    return &sEepromSettings;
}

s32 set_eeprom_settings_value(u64 valueToSet) {
    sEepromSettings |= valueToSet;
    func_8006ECE0();
    return 1;
}

s32 unset_eeprom_settings_value(u64 valueToUnset) {
    sEepromSettings &= ~valueToUnset;
    func_8006ECE0();
    return 1;
}

u64 get_eeprom_settings(void) {
    return sEepromSettings;
}

/**
 * Returns the current language being used by the game.
 * 0 = English, 1 = German, 2 = French, 3 = Japanese
 */
s32 get_language(void) {
    s32 language = ENGLISH;
    switch (sEepromSettings & 0xC) {
        case 4:
            language = GERMAN;
            break;
        case 8:
            language = FRENCH;
            break;
        case 12:
            language = JAPANESE;
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
        case GERMAN:
            langFlag = 4;
            break;
        case FRENCH:
            langFlag = 8;
            break;
        case JAPANESE:
            langFlag = 12;
            break;
    }

    sEepromSettings &= ~0xC; //Set bits 3 and 4 low first
    sEepromSettings |= langFlag; //Then set them according to the selected lang

    load_menu_text(language);
    func_8006ECE0();
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
    return gActiveMagicCodes & 1;
}

/**
 * Returns 1 if Drumstick is avaliable to use, or 0 if not.
 */
s32 is_drumstick_unlocked(void) {
    return gActiveMagicCodes & 2;
}
