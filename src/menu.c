/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x8007F900 */

#include "menu.h"
#include "memory.h"

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "fast3d.h"

/**
 * @file Contains all the code used for every menu in the game.
 */

extern s32 osTvType;

/************ .bss ************/

// The bss section needs to stay above the data section! 
// Otherwise the bss variables will get reordered, which is bad.

unk800DFC10 *D_80126390;
unk800DFC10 *D_80126394;
s32 D_80126398;
s32 D_8012639C;
Gfx *D_801263A0;
s32 D_801263A4;
s32 *D_801263A8;
s32 *D_801263AC;
s32 *D_801263B0;
s8 D_801263B4;
s32 D_801263B8;
s32 D_801263BC;
s32 D_801263C0;
s32 gIgnorePlayerInput;
s32 D_801263C8;

/* Size: 0xE bytes. */
typedef struct unk801263CC {
    u8 pad0[0xC];
    s16 unkC;
} unk801263CC;
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
s64 D_80126448;
f32 D_80126450;
u8 gControllersXAxisDelay[4];
u8 gControllersYAxisDelay[4];
s8 gControllersXAxisDirection[4]; // X axis (-1 = left, 1 = right) for controller
MenuElement **D_80126460;
s8 gControllersYAxisDirection[4]; // Y axis (-1 = down, 1 = up) for controller
u8 gControllersXAxis[4];
u8 gControllersYAxis[4];
s32 D_80126470;
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
s32 D_801264A0[12];
s32 D_801264D0;
s32 D_801264D4;
s8 D_801264D8;
s32 D_801264DC;
s8 D_801264E0;
s8 D_801264E1;
s8 D_801264E2;
s32 D_801264E4;
s32 D_801264E8;
s32 D_801264EC;
s32 D_801264F0[2];
s32 D_801264F8[2];
s32 D_80126500;
s8 D_80126504;
s32 D_80126508;
s16 D_8012650C;
s8 D_8012650E;
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
u32* D_80126550[67]; // lookup table?
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
s8* D_801267EC;
s32 D_801267F0[5];
s32 D_80126804;
s32 D_80126808;
s32 D_8012680C;
s32 D_80126810;
s32 D_80126814;
s32 D_80126818;
s32 D_8012681C;
s32 D_80126820;
s32 D_80126824;
s8  D_80126828;
s32 D_8012682C;
s32 D_80126830;
s32 D_80126834;
s16 D_80126838;
s16 D_8012683A;
s32 D_8012683C;
s32 D_80126840;
s32 D_80126844;
s32 D_80126848;
s32 D_8012684C;
s32 D_80126850;
s32 D_80126854;
s32 D_80126858;
s32 D_8012685C;
s32 D_80126860;
s32 D_80126864;
s32 D_80126868;
s32 D_8012686C;
s32 D_80126870;
s32 D_80126874;
s32 D_80126878[24];
s32 D_801268D8;
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
s32 D_801269C4;
s32 D_801269C8;
s32 D_801269CC;
s32 D_801269D0[3];
s32 D_801269DC;
u32 *D_801269E0;
s32 D_801269E4;
s32 D_801269E8;
s32 D_801269EC;
s32 D_801269F0;
s32 D_801269F4;
s32 D_801269F8;
s32 D_801269FC;
s32 D_80126A00;
s32 D_80126A04;
s32 D_80126A08;
s32 D_80126A0C;
s32 D_80126A10;
s32 D_80126A14;
s32 D_80126A18;
s32 D_80126A1C;
s32 D_80126A20[4];
s32 D_80126A30;
s32 D_80126A34;
s32 D_80126A38;
s32 D_80126A3C;
s32 D_80126A40[8];
s8 D_80126A60[2]; 
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
s32 *D_80126AA0[16];
s32 D_80126AE0[16];
s32 D_80126B20[16];
s32 D_80126B60[4];
s32 D_80126B70[16];
s32 D_80126BB0;
s32 D_80126BB4;
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
s32 D_80126C1C;
s32 D_80126C20;
s32 D_80126C24;
s32 D_80126C28;
s32 *D_80126C2C;
u16 (*gCheatsAssetData)[30]; // Cheat table.
s32 D_80126C34;
s32 D_80126C38;
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
u8  D_80126C58[20];
s32 *D_80126C6C;
s32 D_80126C70;
s32 D_80126C74;
s32 D_80126C78;
s32 D_80126C7C;
s32 D_80126C80[16];
s32 D_80126CC0;

/******************************/

/************ .data ************/

s8  D_800DF450 = 0;
f32 D_800DF454 = 1.0f;
s32 D_800DF458 = 1;
s32 gTitleScreenCurrentOption = 0; // 0 = "Start", 1 = "Options"
s32 D_800DF460 = 0;
s32 D_800DF464 = 4; // Currently unknown, might be a different type.
s32 D_800DF468 = 0;
s32 D_800DF46C = 0;
s32 gCurrentMenuId = 0; // Currently unknown, might be a different type.
s32 D_800DF474 = 0; // Currently unknown, might be a different type.
s32 D_800DF478 = 0; // Currently unknown, might be a different type.
s32 gMenuDelay = 0; // Currently unknown, might be a different type.
s32 gNumberOfReadyPlayers = 0;
s32 D_800DF484 = 0; // Currently unknown, might be a different type.
s32 D_800DF488 = 0;
s32 D_800DF48C = 0; // Currently unknown, might be a different type.
s32 D_800DF490 = 0; // Currently unknown, might be a different type.
s32 gIsInAdventureTwo = 0;
s32 gPlayerHasSeenCautionMenu = 0;
s32 D_800DF49C = 0; // Currently unknown, might be a different type.

unk800DF4A0 *D_800DF4A0 = NULL;

u8 D_800DF4A4 = 0xFF;
u8 D_800DF4A8 = 0xFF;
u8 D_800DF4AC = 0xFF;

s32 D_800DF4B0              = 0;
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
s8 D_800DF4EC = 0;

// Unused?
s32 D_800DF4F0[] = {
    0x4000, 0x8000, 0x1000, 0x2000,
    0x8000, 0x10, 0x400, 0x00
};

unk800DF510 D_800DF510[18] = {
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
    { 0, 0, 0, 0x5D, 1.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0 }
};

s16 *D_800DF750[1] = { NULL }; // This is probably not correct.
s16 D_800DF754 = 0;
s16 D_800DF758 = 0;
unk800DF510 *D_800DF75C = NULL;

s32 D_800DF760 = 0x7F;
s32 D_800DF764 = 0xFF;
s32 D_800DF768 = 1;

// Not sure about typing with these arrays.
s16 D_800DF76C[4] = { 
    0, 0, 10, -1 
};
s16 D_800DF774[4] = { 
    0, 0, 18, -1 
};
u16 D_800DF77C[12] = { 
    0x8000, 0x0000, 0x0012, 0x0000,
    0x00FF, 0xFFFF, 0x0012, 0xFFFF,
    0x80FF, 0xFFFF, 0x0012, 0x0000
};

s32 D_800DF794 = 4;
s32 D_800DF798 = 0;
s32 D_800DF79C = 0;

s32 D_800DF7A0 = 0;
s32 D_800DF7A4 = 0;
s32 D_800DF7A8 = 0; // Currently unknown, might be a different type.
s32 D_800DF7AC = 0; // Currently unknown, might be a different type.

// Version text shown on the title screen? See 1:15 in https://www.youtube.com/watch?v=OHSCLcA74ao.
char gVersionDisplayText[20] = "VERSION XXXXXXXX";

// "Diddy Kong Racing" logo texture indices?
s16 D_800DF7C4[12] = {
    0x50, 0x51, 0x52, 0x53, 
    0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5A, -1
};

MenuBootDrawTexture D_800DF7DC[12] = {
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
    0xFFFF, 0x00FF, 0xCC00, 0xFF00,
    0xFF99, 0x00FF, 0xFFFF, 0x6600,
    0x00FF, 0xFF33, 0x0000, 0x0F78
};

char *D_800DFA10[7] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

s16 D_800DFA2C[8] = {
    0x3D, 0x3C, 0x3F, 0x3E, 0x44, -1, -1, 0
};

unk800DFA3C D_800DFA3C[8] = {
    { 160,  80, 0xFF, 0xFF, 0xFF,    0, 0xFF, 0, 0, 12, NULL },
    { 160, 104, 0xFF, 0xFF, 0xFF,    0, 0xFF, 0, 0, 12, NULL },
    { 160, 144, 0xFF, 0xFF, 0xFF,    0, 0xFF, 0, 0, 12, NULL },
    { 160, 192, 0xFF, 0xFF, 0xFF,    0, 0xFF, 0, 0, 12, NULL },
    { 161,  35,    0,    0,    0, 0xFF, 0x80, 2, 0, 12, NULL },
    { 160,  32, 0xFF, 0x80, 0xFF,    0, 0xFF, 2, 0, 12, NULL },
    { 160, 188, 0xFF, 0xFF, 0xFF,    0, 0xFF, 0, 0, 12, NULL },
    {   0,   0,    0,    0,    0,    0,    0, 0, 0,  0, NULL }
};

s32 D_800DFABC = 0; // Currently unknown, might be a different type.

s32 gSfxVolumeSliderValue   = 256; // Value from 0 to 256
s32 gMusicVolumeSliderValue = 256; // Value from 0 to 256

s32 D_800DFAC8 = 0;

// Unsure about typing here.
u16 D_800DFACC[8] = {
    0x4040, 0xFFFF, 0xFF40, 0x40FF,
    0xFFD0, 0x40FF, 0x40FF, 0x40FF
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
    D_800DFAE4, D_800DFAFC, D_800DFB14, D_800DFB2C,
    D_800DFB40, D_800DFB5C, D_800DFB8C, D_800DFBA4, 
    D_800DFB74, D_800DFBBC
};

s32 D_800DFC08 = 0; // Currently unknown, might be a different type.
s32 D_800DFC0C = 0xFFFF; // Currently unknown, might be a different type.

unk800DFC10 D_800DFC10 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800DFC20 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800DFC30 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800DFC40 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800DFC50 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800DFC60 = { NULL, 0, 0, NULL, 0 };

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

s16 D_800DFCAC[4] = {
    0x000B, 0x000C, 0x0002, 0xFFFF
};

u16 D_800DFCB4[112] = {
    0x00A1, 0x0020, 0x00A1, 0x0021, 
    0x00A1, 0x0020, 0x0000, 0x00FF, 
    0x8002, 0x0C00, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 
    0x00A0, 0x001E, 0x00A0, 0x001E, 
    0x00A0, 0x001E, 0xFFFF, 0xFF00, 
    0xFF02, 0x0C00, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 
    0x00A0, 0x0070, 0x00A0, 0x0070, 
    0x00A0, 0x0070, 0xFFFF, 0xFF00, 
    0xFF00, 0x0C00, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 
    0x00A0, 0x0080, 0x00A0, 0x0080, 
    0x00A0, 0x0080, 0xFFFF, 0xFF00, 
    0xFF00, 0x0C00, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 
    0x00A0, 0x00C0, 0x00A0, 0x00C0, 
    0x00A0, 0x00C0, 0xFFFF, 0xFF00, 
    0xFF00, 0x0C00, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 
    0x00A0, 0x00D0, 0x00A0, 0x00D0, 
    0x00A0, 0x00D0, 0xFFFF, 0xFF00, 
    0xFF00, 0x0C00, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000
};

s32 D_800DFD94 = 0;

s32 gActiveMagicCodes = 0;
s32 gUnlockedMagicCodes = 0;

s32 D_800DFDA0[5] = { 0, 0, 0, 0, 0 };

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
    { 0x04, 0x64 }
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
    0x000703FF, 0xFFFF0605, 0x04FFFFFF, 0xFFFF0004
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
    0xFFFF0506, 0x0100FFFF, 0x0203FFFF, 0x00060000
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
    0x0102FFFF, 0x0504FFFF, 0x0607FFFF, 0x00080000
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
    0x05FF0504, 0xFFFF0607, 0xFFFF0008, 0x00000000
};

s32 D_800DFFD0 = 0;
s32 D_800DFFD4 = -1;

MenuElement D_800DFFD8[14] = {
    { 161,  35, 161,  35, 161,  35,   0,   0,   0, 255, 128, 2, 12, 0, NULL, 0, 0, 0, 0 },
    { 160,  32, 160,  32, 160,  32, 255, 255, 255,   0, 255, 2, 12, 0, NULL, 0, 0, 0, 0 },
    { 160,  72, 160,  68, 160,  72, 255, 255, 255,   0, 255, 0, 12, 0, NULL, 0, 0, 0, 0 },
    { 160,  86, 160,  82, 160,  86, 255, 255, 255,   0, 255, 0, 12, 0, NULL, 0, 0, 0, 0 },
    { 160, 100, 160,  96, 160, 100, 255, 255, 255,   0, 255, 0, 12, 0, NULL, 0, 0, 0, 0 },
    { 160, 114, 160, 110, 160, 114, 255, 255, 255,   0, 255, 0, 12, 0, NULL, 0, 0, 0, 0 },
    { 160, 128, 160, 124, 160, 128, 255, 255, 255,   0, 255, 0, 12, 0, NULL, 0, 0, 0, 0 },
    { 160, 142, 160, 138, 160, 142, 255, 255, 255,   0, 255, 0, 12, 0, NULL, 0, 0, 0, 0 },
    { 160, 156, 160, 152, 160, 156, 255, 255, 255,   0, 255, 0, 12, 0, NULL, 0, 0, 0, 0 },
    { 160, 156, 160, 166, 160, 156, 255, 255, 255,   0, 255, 0, 12, 0, NULL, 0, 0, 0, 0 },
    { 160, 186, 160, 180, 160, 186, 255, 255, 255,   0, 255, 0, 12, 0, NULL, 0, 0, 0, 0 },
    { 160, 200, 160, 194, 160, 200, 255, 255, 255,   0, 255, 0, 12, 0, NULL, 0, 0, 0, 0 },
    { 160, 200, 160, 208, 160, 200, 255, 255, 255,   0, 255, 0, 12, 0, NULL, 0, 0, 0, 0 },
    {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0,  0, 0, NULL, 0, 0, 0, 0 }
};
                                                                             
MenuElement D_800E0198[7] = {                                                       
    { 161,  35, 161,  35, 161,  35,   0,   0,   0, 255, 128, 2, 12, 0, NULL,   0,  0, 0, 0 },
    { 160,  32, 160,  32, 160,  32, 255, 255, 255,   0, 255, 2, 12, 0, NULL,   0,  0, 0, 0 },
    { -96,  39, -96,  39, -96,  39, 176, 224, 192, 255, 255, 0,  0, 7, NULL, 192, 44, 4, 4 },
    { 160, 104, 160, 104, 160, 104, 255, 255, 255,   0, 255, 2, 12, 0, NULL,   0,  0, 0, 0 },
    { -96,  -9, -96,  -9, -96,  -9, 176, 224, 192, 255, 255, 0,  0, 7, NULL, 192, 44, 4, 4 },
    { 160, 152, 160, 152, 160, 152, 255, 255, 255,   0, 255, 2, 12, 0, NULL,   0,  0, 0, 0 },
    {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0,  0, 0, NULL,   0,  0, 0, 0 }
};   
                                                                        
MenuElement D_800E0278[9] = { 
    {  161,  35,  161,  35,  161,  35,   0,   0,   0, 255, 128, 2, 12, 0, NULL,   0,  0, 0, 0 },
    {  160,  32,  160,  32,  160,  32, 255, 255, 255,   0, 255, 2, 12, 0, NULL,   0,  0, 0, 0 },
    { -112,  55, -112,  55, -112,  55, 176, 224, 192, 255, 255, 0,  0, 7, NULL, 224, 44, 4, 4 },
    {  160,  88,  160,  88,  160,  88, 255, 255, 255,   0, 255, 2, 12, 0, NULL,   0,  0, 0, 0 },
    { -112,   7, -112,   7, -112,   7, 176, 224, 192, 255, 255, 0,  0, 7, NULL, 224, 44, 4, 4 },
    {  160, 136,  160, 136,  160, 136, 255, 255, 255,   0, 255, 2, 12, 0, NULL,   0,  0, 0, 0 },
    { -112, -41, -112, -41, -112, -41, 176, 224, 192, 255, 255, 0,  0, 7, NULL, 224, 44, 4, 4 },
    {  160, 184,  160, 184,  160, 184, 255, 255, 255,   0, 255, 2, 12, 0, NULL,   0,  0, 0, 0 },
    {    0,   0,    0,   0,    0,   0,   0,   0,   0,   0,   0, 0,  0, 0, NULL,   0,  0, 0, 0 }
};

s16 D_800E0398[6] = {
    0x00, 0x43, 0x40, 0x41, 0x42, -1
};

s16 D_800E03A4[6] = {
    0x00, 0x0B, 0x0C, 0x0A, -1, 0
};

u16 D_800E03B0[14] = {
    0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x004C, 0x0070, 
    0x00F4, 0x0070, 0x004C, 0x00D0, 
    0x00F4, 0x00D0
};

u16 D_800E03CC[24] = {
    0x0018, 0x0051, 0x0058, 0x0040, 
    0x0004, 0x0004, 0x4080, 0xFFC0, 
    0x0074, 0x0051, 0x0058, 0x0040, 
    0x0004, 0x0004, 0x4080, 0xFFC0, 
    0x00D0, 0x0051, 0x0058, 0x0040, 
    0x0004, 0x0004, 0x4080, 0xFFC0
};

u16 D_800E03FC[10] = {
    0x002C, 0x0036,
    0x0015, 0x0019,
    0x002C, 0x001B,
    0x003F, 0x0019,
    0x002D, 0x0019
};

// Either 0 (2 racers), 1 (4 racers), or 2 (6 racers)
s32 gMultiplayerSelectedNumberOfRacers = 0;

s32 D_800E0414 = 0;
s32 D_800E0418 = 0;

unk800DFC10 D_800E041C = { NULL, -12,  -8, 0, 0 };
unk800DFC10 D_800E042C = { NULL,  -8, -12, 0, 0 };
unk800DFC10 D_800E043C = { NULL, -12,  -8, 0, 0 };
unk800DFC10 D_800E044C = { NULL,  -8, -12, 0, 0 };

unk800DFC10 D_800E045C = { NULL, 0, 0, NULL, 0x20 };
s32 D_800E046C[2] = {0, 0}; // Not sure what these are.
unk800DFC10 D_800E0474 = { NULL, 0, 0, NULL, 0x20 };
s32 D_800E0484[2] = {0, 0}; // Not sure what these are.
unk800DFC10 D_800E048C = { NULL, 0, 0, NULL, 0x20 };
s32 D_800E049C[2] = {0, 0}; // Not sure what these are.
unk800DFC10 D_800E04A4 = { NULL, 0, 0, NULL, 0x20 };
s32 D_800E04B4[2] = {0, 0}; // Not sure what these are.
unk800DFC10 D_800E04BC = { NULL, 0, 0, NULL, 0x20 };
s32 D_800E04CC[2] = {0, 0}; // Not sure what these are.
unk800DFC10 D_800E04D4 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E04E4 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E04F4 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0504 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0514 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0524 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0534 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0544 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0554 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0564 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0574 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0584 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0594 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E05A4 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E05B4 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E05C4 = { NULL, 0, 0, NULL, 0 };

// These are probably structs
s32 D_800E05D4[8] = { 0, 0xFFD0, 0, 0xFFF0, 0, 0x10, 0, 0 };
s32 D_800E05F4[8] = { 0, 0xFFD0, 0, 0xFFF0, 0, 0x10, 0, 0 };

unk800DFC10 D_800E0614 = { NULL, -16, -16, 0, 0 };

unk800DFC10 *D_800E0624[9] = {
    &D_800E045C, &D_800E04D4, &D_800E04E4,
    &D_800E0474, &D_800E04F4, &D_800E0504,
    &D_800E048C, &D_800E0514, &D_800E0524
};

unk800DFC10 *D_800E0648[6] = {
    &D_800E04BC, &D_800E0544, &D_800E0564,
    &D_800E04A4, &D_800E0534, &D_800E0554
};

unk800DFC10 *D_800E0660[6] = {
    &D_800E0574, &D_800E0584, &D_800E0594,
    &D_800E05A4, &D_800E05B4, &D_800E05C4
};

unk800DFC10 *D_800E0678[4] = {
    &D_800E041C, &D_800E042C, &D_800E043C, &D_800E044C
};

u16 D_800E0688[20] = {  
    0x44, 0x72, 0x44, 0x72,
    0xCC, 0x72, 0x21, 0x72,
    0x88, 0x72, 0xEF, 0x72,
    0x21, 0x72, 0x66, 0x72,
    0xAA, 0x72, 0xEF, 0x72
};

u16 D_800E06B0[10] = {
    0x68, 0x21, 0xFB, 0x27, 
    0x8E, 0xF5, 0x27, 0x6C, 
    0xB0, 0xF5 
};

s16 D_800E06C4[8] = {
    0x0000, 0xFFC2, 0x0055, 0x0000,
    0x0000, 0x003E, 0xFFAB, 0x0000
};

s16 D_800E06D4[8] = {
    0x0000, 0xFFB6, 0x0055, 0x0000,
    0x0000, 0x004A, 0xFFAB, 0x0000
};

u16 D_800E06E4[14] = {
    0x50, 0x8C, 0xA0, 0x40,
    0x04, 0x04, 0x50, 0x14,
    0x3A, 0x28, 0x50, 0x28,
    0x66, 0x28
};

u16 D_800E0700[8] = {
    0x50, 0x98, 0xA0, 0x28,
    0x04, 0x04, 0x50, 0x0E
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
f32 *D_800E0978 = D_800E7D04; // .data
s32 D_800E097C = 0;
s32 D_800E0980 = 0;
s32 D_800E0984 = 0;
s32 D_800E0988 = 0;
s32 D_800E098C = 0;

s16 D_800E0990[8] = {
    0x4040, 0xFFA0, 0xFF40, 0x40A0,
    0xD0C0, 0x20B0, 0x20C0, 0x40B0
};

s16 D_800E09A0[8] = {
    0x00FF, 0x0080, 0x00FF, 0x0060,
    0x0000, 0xFF60, 0x0000, 0xFF80
};

// Not sure about typing with these.
s32 D_800E09B0[5] = { 0, 0, 0, 0, 0 };
s32 D_800E09C4[5] = { 0, 0, 0, 0, 0 };
s32 D_800E09D8[5] = { 0, 0, 0, 0, 0 };
s32 D_800E09EC[3] = { 0, 0, 0 };
s32 D_800E09F8[3] = { 0, 0, 0 };
s32 D_800E0A04[3] = { 0, 0, 0 };
s32 D_800E0A10 = 0;
s32 D_800E0A14[4] = { 0, 0, 0, 0 };

s16 D_800E0A24[14] = {
    0x0005, 0x003B, 0x0032, 0x0033, 
    0x0034, 0x0035, 0x0036, 0x0039, 
    0x0037, 0x0038, 0x003A, 0x0000, 
    0x0001, 0xFFFF
};

s16 D_800E0A40[8] = {
    0x0004, 0x0000, 0x0001, 0xFFFF,
    0x0300, 0x0000, 0x0012, 0xFFFF
};

unk800DFC10 D_800E0A50 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0A60 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0A70 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0A80 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0A90 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0AA0 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0AB0 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0AC0 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0AD0 = { NULL, 0, 0, NULL, 0 };
unk800DFC10 D_800E0AE0 = { NULL, 0, 0, NULL, 0 };

unk800DFC10 *D_800E0AF0[10] = {
    &D_800E0A50, &D_800E0A60, &D_800E0A70, &D_800E0A80, 
    &D_800E0A90, &D_800E0AA0, &D_800E0AB0, &D_800E0AC0, 
    &D_800E0AD0, &D_800E0AE0
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
    { 352, 172,  32, 172, -288, 172, 255, 255, 255, 0, 255, 0,  0, 3, &D_800E0A50, 0, 0, 0, 0 },
    { 452, 166, 132, 166, -188, 166, 255, 255, 255, 0, 255, 0, 12, 0,        NULL, 0, 0, 0, 0 },
    { 560, 184, 240, 184,  -80, 184, 255, 255, 255, 0, 255, 0, 12, 0,        NULL, 0, 0, 0, 0 },
    { 452, 180, 132, 180, -188, 180, 255, 192, 255, 0, 255, 0,  0, 1,        NULL, 0, 0, 0, 0 },
    { 452, 198, 132, 198, -188, 198, 255, 192, 255, 0, 255, 0,  0, 1,        NULL, 0, 0, 0, 0 },
    { 452, 216, 132, 216, -188, 216, 255, 192, 255, 0, 255, 0,  0, 1,        NULL, 0, 0, 0, 0 },
    { 560, 200, 240, 200,  -80, 200, 128, 255, 255, 0, 255, 0,  0, 1,        NULL, 0, 0, 0, 0 },
    {   0,   0,   0,   0,    0,   0,   0,   0,   0, 0,   0, 0,  0, 0,        NULL, 0, 0, 0, 0 },
};   

MenuElement D_800E0CEC[11] = {                                                       
    { 575, 172, 255, 172,  -65, 172, 255, 255, 255,   0, 255, 0,  0, 3, &D_800E0A50, 0, 0, 0, 0 },
    { 542, 172, 222, 172,  -98, 172, 255, 255, 255,   0, 255, 0,  0, 3, &D_800E0A50, 0, 0, 0, 0 },
    { 509, 172, 189, 172, -131, 172, 255, 255, 255,   0, 255, 0,  0, 3, &D_800E0A50, 0, 0, 0, 0 },
    { 476, 172, 156, 172, -164, 172, 255, 255, 255,   0, 255, 0,  0, 3, &D_800E0A50, 0, 0, 0, 0 },
    { 443, 172, 123, 172, -197, 172, 255, 255, 255,   0, 255, 0,  0, 3, &D_800E0A50, 0, 0, 0, 0 },
    { 410, 172,  90, 172, -230, 172, 255, 255, 255,   0, 255, 0,  0, 3, &D_800E0A50, 0, 0, 0, 0 },
    { 377, 172,  57, 172, -263, 172, 255, 255, 255,   0, 255, 0,  0, 3, &D_800E0A50, 0, 0, 0, 0 },
    { 344, 172,  24, 172, -296, 166, 255, 255, 255,   0, 255, 0,  0, 3, &D_800E0A50, 0, 0, 0, 0 },
    { 481, 166, 161, 166, -159, 166,   0,   0,   0, 255, 128, 0, 12, 0,        NULL, 0, 0, 0, 0 },
    { 479, 164, 159, 164, -161, 164, 255, 255, 255,   0, 255, 0, 12, 0,        NULL, 0, 0, 0, 0 },
    {   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0, 0,  0, 0,        NULL, 0, 0, 0, 0 },
    
};



MenuElement D_800E0E4C[9] = {    
    { 481, 174, 161, 174, -159, 174,   0,   0,   0, 255, 128, 0, 12, 0,             NULL, 0, 0, 0, 0 },
    { 479, 172, 159, 172, -161, 172, 255, 255, 255,   0, 255, 0, 12, 0,             NULL, 0, 0, 0, 0 },
    { 368, 192,  48, 192, -272, 192, 255,  64,  64,  96, 255, 0,  8, 0,             NULL, 0, 0, 0, 0 },
    { 506, 187, 186, 187, -134, 187, 255, 192, 255,   0, 255, 0,  0, 1,             NULL, 0, 0, 0, 0 },
    { 578, 192, 258, 192,  -62, 192, 255, 128, 255,  96, 255, 0, 12, 0,      &D_80126390, 0, 0, 0, 0 },
    { 368, 212,  48, 212, -272, 212, 255,  64,  64,  96, 255, 0,  8, 0,             NULL, 0, 0, 0, 0 },
    { 506, 207, 186, 207, -134, 207, 128, 255, 255,   0, 255, 0,  0, 1,             NULL, 0, 0, 0, 0 },
    { 578, 212, 258, 212,  -62, 212, 255, 128, 255,  96, 255, 0, 12, 0,      &D_80126394, 0, 0, 0, 0 },
    {   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0, 0,  0, 0,             NULL, 0, 0, 0, 0 },
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
    0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 
    0x39, 0x3A, 0x3B, 0x00, 0x01, -1, 0x00    
};

s32 D_800E1040 = 1;
s16 D_800E1044 = -1;

MenuElement D_800E1048[9][3] = {
    {
        { 481,   35, 161, 35, -159,  35,   0,   0,   0, 255, 128, 2, 12, 0,        NULL, 0, 0, 0, 0 },
        { 480,   32, 160, 32, -160,  32, 255, 255, 255,   0, 255, 2, 12, 0,        NULL, 0, 0, 0, 0 },
        {  64, -192,  64, 48,   64, 288, 255, 255, 255,   0, 255, 0,  0, 3, &D_800E0A50, 0, 0, 0, 0 }
    },
    {
        {  32, -192,  32, 48,  32, 288, 255, 255, 255, 0, 255, 0, 0, 0,    gFirstPlace, 0, 0, 0, 0 },
        { 130, -172, 130, 68, 130, 308, 255, 255, 255, 0, 255, 0, 4, 2, &gTrophyRacePointsArray[0], 0, 0, 0, 0 },
        {  64, -150,  64, 90,  64, 330, 255, 255, 255, 0, 255, 0, 0, 3,    &D_800E0A50, 0, 0, 0, 0 }
    },
    {
        {  32, -150,  32,  90,  32, 330, 255, 255, 255, 0, 255, 0, 0, 0,   gSecondPlace, 0, 0, 0, 0 },
        { 130, -130, 130, 110, 130, 350, 255, 192, 255, 0, 255, 0, 4, 2, &gTrophyRacePointsArray[1], 0, 0, 0, 0 },
        {  64, -108,  64, 132,  64, 372, 255, 255, 255, 0, 255, 0, 0, 3,    &D_800E0A50, 0, 0, 0, 0 }
    },
    {
        {  32, -108,  32, 132,  32, 372, 255, 255, 255, 0, 255, 0, 0, 0,    gThirdPlace, 0, 0, 0, 0 },
        { 130,  -88, 130, 152, 130, 392, 255, 128, 255, 0, 255, 0, 4, 2, &gTrophyRacePointsArray[2], 0, 0, 0, 0 },
        {  64,  -66,  64, 174,  64, 414, 255, 255, 255, 0, 255, 0, 0, 3,    &D_800E0A50, 0, 0, 0, 0 }
    },
    {
        {  32, -66,  32, 174,  32,  414, 255, 255, 255, 0, 255, 0, 0, 0,   gFourthPlace, 0, 0, 0, 0 },
        { 130, -46, 130, 194, 130,  434, 255,  64, 255, 0, 255, 0, 4, 2, &gTrophyRacePointsArray[3], 0, 0, 0, 0 },
        { 220, 288, 220,  48, 220, -192, 255, 255, 255, 0, 255, 0, 0, 3,    &D_800E0A50, 0, 0, 0, 0 }
    },
    {
        { 188, 288, 188, 48, 188, -192, 255, 255, 255, 0, 255, 0, 0, 0,    gFifthPlace, 0, 0, 0, 0 },
        { 286, 308, 286, 68, 286, -172, 255, 255, 255, 0, 255, 0, 4, 2, &gTrophyRacePointsArray[4], 0, 0, 0, 0 },
        { 220, 330, 220, 90, 220, -160, 255, 255, 255, 0, 255, 0, 0, 3,    &D_800E0A50, 0, 0, 0, 0 }
    },
    {
        { 188, 330, 188,  90, 188, -150, 255, 255, 255, 0, 255, 0, 0, 0,    gSixthPlace, 0, 0, 0, 0 },
        { 286, 350, 286, 110, 286, -130, 255, 192, 255, 0, 255, 0, 4, 2, &gTrophyRacePointsArray[5], 0, 0, 0, 0 },
        { 220, 372, 220, 132, 220, -108, 255, 255, 255, 0, 255, 0, 0, 3,    &D_800E0A50, 0, 0, 0, 0 }
    },
    {
        { 188, 372, 188, 132, 188, -108, 255, 255, 255, 0, 255, 0, 0, 0,  gSeventhPlace, 0, 0, 0, 0 },
        { 286, 392, 286, 152, 286,  -88, 255, 128, 255, 0, 255, 0, 4, 2, &gTrophyRacePointsArray[6], 0, 0, 0, 0 },
        { 220, 414, 220, 174, 220,  -66, 255, 255, 255, 0, 255, 0, 0, 3,    &D_800E0A50, 0, 0, 0, 0 }
    },
    {
        { 188, 414, 188, 174, 188, -66, 255, 255, 255, 0, 255, 0, 0, 0,   gEighthPlace, 0, 0, 0, 0 },
        { 286, 434, 286, 194, 286, -46, 255,  64, 255, 0, 255, 0, 4, 2, &gTrophyRacePointsArray[7], 0, 0, 0, 0 },
        {   0,   0,   0,   0,   0,   0,   0,   0,   0, 0,   0, 0, 0, 0,           NULL, 0, 0, 0, 0 }
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

// Not sure what these arrays are supposed to be
s32 D_800E153C[10] = {
    0, 0x00000000, 
    0, 0x00400000,
    0, 0x00800000, 
    0, 0x00C00000,
    0, 0x01000000
};
s32 D_800E1564[12] = {
    0, 0x00000020, 
    0, 0x00400020, 
    0, 0x00800020, 
    0, 0x00C00020, 
    0, 0x01000020, 
    0, 0x00000000
};
s32 D_800E1594[10] = {
    0, 0x00000000, 
    0, 0x00400000,
    0, 0x00800000, 
    0, 0x00C00000,
    0, 0x01000000
};
s32 D_800E15BC[12] = {
    0, 0x00000020, 
    0, 0x00400020, 
    0, 0x00800020, 
    0, 0x00C00020, 
    0, 0x01000020, 
    0, 0x00000000
};
s32 D_800E15EC[10] = {
    0, 0x00000000, 
    0, 0x00400000,
    0, 0x00800000, 
    0, 0x00C00000,
    0, 0x01000000
};
s32 D_800E1614[12] = {
    0, 0x00000020, 
    0, 0x00400020, 
    0, 0x00800020, 
    0, 0x00C00020, 
    0, 0x01000020, 
    0, 0x00000000
};
s32 D_800E1644[10] = {
    0, 0x00000000, 
    0, 0x00400000,
    0, 0x00800000, 
    0, 0x00C00000,
    0, 0x01000000
};
s32 D_800E166C[12] = {
    0, 0x00000020, 
    0, 0x00400020, 
    0, 0x00800020, 
    0, 0x00C00020, 
    0, 0x01000020, 
    0, 0x00000000
};
s32 D_800E169C[10] = {
    0, 0x00000000, 
    0, 0x00400000,
    0, 0x00800000, 
    0, 0x00C00000,
    0, 0x01000000
};
s32 D_800E16C4[12] = {
    0, 0x00000020, 
    0, 0x00400020, 
    0, 0x00800020, 
    0, 0x00C00020, 
    0, 0x01000020, 
    0, 0x00000000
};

s32 *D_800E16F4[5] = {
    D_800E153C, D_800E1594, D_800E15EC, D_800E1644, 
    D_800E169C
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
    0x78, 0x12, 0x08, 0x06, 0xC0, 0x06, 0xD4, 0x1A, 
    0x78, 0x22
};

s16 D_800E1768[12] = {
    0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 
    0x3A, 0x3B, -1, 0
};

// Fast3D (F3DDKR) display list
u32 D_800E1780[22] = {
    0xE7000000, 0x00000000, 
    0xBA001402, 0x00000000, 
    0xBA001001, 0x00000000, 
    0xBA000E02, 0x00000000, 
    0xBA001102, 0x00000000, 
    0xBA001301, 0x00000000, 
    0xBA000C02, 0x00002000, 
    0xBA000903, 0x00000C00, 
    0xB9000002, 0x00000000, 
    0xB900031D, 0x00504340, 
    0xB8000000, 0x00000000
};

s16 D_800E17D8[12] = {
    0x0032, 0x0033, 0x0034, 0x0035, 
    0x0036, 0x0037, 0x0038, 0x0039, 
    0x003A, 0x003B, -1, 0
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
    { 480, 104, 160, 104, -160, 104, 255,   0, 255, 48, 255, 0, 4, 0, NULL, 0, 0, 0, 0 },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, 2, 4, 0, NULL, 0, 0, 0, 0 },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255,  0, 255, 2, 4, 0, NULL, 0, 0, 0, 0 },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, 2, 4, 0, NULL, 0, 0, 0, 0 },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255,  0, 255, 2, 4, 0, NULL, 0, 0, 0, 0 },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, 2, 4, 0, NULL, 0, 0, 0, 0 },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255,  0, 255, 2, 4, 0, NULL, 0, 0, 0, 0 },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255,  0, 255, 2, 4, 0, NULL, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, 0, 0, 0, 0 }
};

// Fast3D (F3DDKR) display list
u32 D_800E1C70[24] = {
    0xE7000000, 0x00000000, 
    0xBA001001, 0x00000000, 
    0xBA000E02, 0x00000000, 
    0xB9000002, 0x00000000, 
    0xB6000000, 0x00010001, 
    0xB8000000, 0x00000000, 
    0xFCFFFFFF, 0xFFFE793C, 
    0xEF000C0F, 0x00504240, 
    0xFC121824, 0xFF33FFFF, 
    0xEF082C0F, 0x00504240, 
    0xFCFFFFFF, 0xFFFDF6FB, 
    0xEF000C0F, 0x00504240
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
    1, 1, -1, 1, -1, 1, -1, -1,
    1, -1, -1, -1, 1, 1, 1, -1
};

s16 D_800E1DE8[4] = { 
    0, 0, 0x78, -1 
};

char gRareCopyrightString[24] = "(C) COPYRIGHT RARE 1997";

s16 D_800E1E08[4] = { 
    0, 0, 0x34, -1 
};

s32 *D_800E1E10 = " (ADV.";

s32 D_800E1E14 = 0;
s32 D_800E1E18 = 0;
s32 D_800E1E1C = 0;

s8 D_800E1E20[8] = { 
    0, -1, 1, 0, 0, 1, -1, 0 
};

s8 D_800E1E28 = 0;

s16 D_800E1E2C[10] = {
    0x4C, 0x4D, 0x4E, 0x4F, 0x5B, 0x5C, 0x00, 0x42,
    -1, 0
};

s16 D_800E1E40[10] = {
    0x0D, 0x0E, 0x0F, 0x10, 0x08, 0x09, 0x00, 0x0A,
    -1, 0
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

Settings *get_settings(void);
void func_8009C4A8(s16 *arg0);
void func_8009C674(s16 *arg0);
void func_8008E4B0(void);
s8 *func_8001E29C(s32 arg0);
void func_80001D04(s32, s32*);
void func_800660EC(f32 arg0);
void func_8009C508(s32 arg0);
void *allocate_from_main_pool_safe(s32, u32);
void func_800C4170(s32 arg0);
void play_music(s32 arg0);

GLOBAL_ASM("asm/non_matchings/menu/func_8007F900.s")

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
    D_800E1DB4 = (s32) (1 - D_800E1DB4);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80080E90.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80081218.s")

void func_800813C0(void) {
    D_800DF458 = 1;
}

#ifdef NON_MATCHING
void reset_controller_sticks(void);
void menu_logos_screen_init(void);
void menu_title_screen_init(void);
void menu_options_init(void);
void menu_audio_options_init(void);
void menu_save_options_init(void);
void menu_magic_codes_init(void);
void menu_magic_codes_list_init(void);
void menu_character_select_init(void);
void menu_game_select_init(void);
void menu_file_select_init(void);
void menu_track_select_init(void);
void menu_5_init(void);
void menu_11_init(void);
void menu_trophy_race_round_init(void);
void menu_trophy_race_rankings_init(void);
void menu_23_init(void);
void menu_ghost_data_init(void);
void menu_credits_init(void);
void menu_boot_init(void);
void menu_caution_init(void);

// Almost close to matching.
void menu_init(u32 menuId) {
    gCurrentMenuId = menuId;
    reset_controller_sticks();
    gIgnorePlayerInput = 1;
    D_801263BC = 0;
    D_801263C8 = 0;
    D_80126828 = 0;
    D_80126808 = 0;
    D_8012680C = 0; // This creates an extra lui
    D_80126810 = 0;
    D_80126814 = 0; // This creates an extra lui
    func_80001844();
    switch(gCurrentMenuId) {
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
    D_80126470 = 0xD000;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_init.s")
#endif

/**
 * Runs every frame. Calls the loop function of the current menu id
 */
s32 menu_loop(Gfx **arg0, s32 **arg1, s32 **arg2, s32 **arg3, s32 arg4) {
    s32 sp1C;

    D_801263A0 = *arg0;
    D_801263A8 = *arg1;
    D_801263AC = *arg2;
    D_801263B0 = *arg3;
    func_8009BF20();
    switch (gCurrentMenuId) {
        case MENU_LOGOS:
            sp1C = menu_logo_screen_loop(arg4);
            break;
        case MENU_TITLE:
            sp1C = menu_title_screen_loop(arg4);
            break;
        case MENU_OPTIONS:
            sp1C = menu_options_loop(arg4);
            break;
        case MENU_AUDIO_OPTIONS:
            sp1C = menu_audio_options_loop(arg4);
            break;
        case MENU_SAVE_OPTIONS:
            sp1C = menu_save_options_loop(arg4);
            break;
        case MENU_MAGIC_CODES:
            sp1C = menu_magic_codes_loop(arg4);
            break;
        case MENU_MAGIC_CODES_LIST:
            sp1C = menu_magic_codes_list_loop(arg4);
            break;
        case MENU_CHARACTER_SELECT:
            sp1C = menu_character_select_loop(arg4);
            break;
        case MENU_FILE_SELECT:
            sp1C = menu_file_select_loop(arg4);
            break;
        case MENU_GAME_SELECT:
            sp1C = menu_game_select_loop(arg4);
            break;
        case MENU_TRACK_SELECT:
            sp1C = menu_track_select_loop(arg4);
            break;
        case MENU_UNKNOWN_5:
            sp1C = menu_5_loop(arg4);
            break;
        case MENU_RESULTS:
            sp1C = menu_results_loop(arg4);
            break;
        case MENU_TROPHY_RACE_ROUND:
            sp1C = menu_trophy_race_round_loop(arg4);
            break;
        case MENU_TROPHY_RACE_RANKINGS:
            sp1C = menu_trophy_race_rankings_loop(arg4);
            break;
        case MENU_UNKNOWN_23:
            sp1C = menu_23_loop(arg4);
            break;
        case MENU_GHOST_DATA:
            sp1C = menu_ghost_data_loop(arg4);
            break;
        case MENU_CREDITS:
            sp1C = menu_credits_loop(arg4);
            break;
        case MENU_BOOT:
            sp1C = menu_boot_loop(arg4);
            break;
        case MENU_CAUTION:
            sp1C = menu_caution_loop(arg4);
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

    D_800DF4A4 = arg3;
    D_800DF4A8 = arg4;
    D_800DF4AC = arg5;
    if (arg6 == 0) {
        D_800DF75C[0].unk10 = arg2;
        D_800DF75C[1].unk10 = arg2 - 2;
        phi_s3 = 0;
        phi_s5 = 1;
        arg1 -= 0x27;
        phi_s6 = 0xC;
        sp44 = 0xB;
        sp40 = 0xA;
    } else {
        D_800DF75C[2].unk10 = arg2;
        D_800DF75C[3].unk10 = arg2 - 1;
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
    D_800DF75C[phi_s3].unk18 = sp5C / 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += phi_s6;
    D_800DF75C[phi_s3].unk18 = sp5C % 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += sp44;
    D_800DF75C[phi_s5].unkC = arg1;
    func_8009CA60(phi_s5);
    arg1 += sp40;
    D_800DF75C[phi_s3].unk18 = sp58 / 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += phi_s6;
    D_800DF75C[phi_s3].unk18 = sp58 % 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += sp44;
    D_800DF75C[phi_s5].unkC = arg1;
    func_8009CA60(phi_s5);
    arg1 += sp40;
    D_800DF75C[phi_s3].unk18 = sp54 / 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    arg1 += phi_s6;
    D_800DF75C[phi_s3].unk18 = sp54 % 10;
    D_800DF75C[phi_s3].unkC = arg1;
    func_8009CA60(phi_s3);
    func_80068508(0);
    func_8007BF1C(1);
    D_800DF4A4 = (u8)0xFF;
    D_800DF4A8 = (u8)0xFF;
    D_800DF4AC = (u8)0xFF;
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
GLOBAL_ASM("asm/non_matchings/menu/draw_menu_element.s")

void func_800828B8(void) {
    s32 i;
    s32 j;
    s32 num;
    Settings *settings;

    settings = get_settings();
    func_8006B224(&num, &j);
    
    for(i = 0; i < num; i++) {
        settings->courseFlagsPtr[i] = 0;
        for(j = 0; j < 3; j++) {
            settings->courseFlagsPtr[i] |= D_80126530[j]->courseFlagsPtr[i];
        }
    }
    
    settings->trophies = 0;
    settings->keys = 0;
    settings->bosses = 0;
    settings->cutsceneFlags = 0;
    for(i = 0; i < 3; i++) {
        settings->trophies |= D_80126530[i]->trophies;
        settings->keys |= D_80126530[i]->keys;
        settings->bosses |= D_80126530[i]->bosses;
        settings->cutsceneFlags |= D_80126530[i]->cutsceneFlags;
    }
}

void func_800829F8(s32 arg0, s32 arg1) {
    s32 temp;

    D_800DF46C += arg1;
    
    if (D_800DF46C & 0x10) {
        func_8007F900(get_language());
        set_text_font(0);
        set_text_color(0xFF, 0xFF, 0xFF, 0, 0xFF);
        set_text_background_color(0, 0, 0, 0);
        temp = 0xD0;
        if (osTvType == 0) {
            temp = 0xEA;
        }
        draw_text(arg0, -0x8000, temp, D_800DF4A0->unk25C, 0xC);
    }
}

void menu_logos_screen_init(void) {
    gMenuDelay = 0;
    D_80126450 = 16.0f;
    func_80077B5C(0, 0, 0);
    if (osTvType == 0) {
        func_80066940(0, 0, 0x26, 0x140, 0xE0);
        func_80066AA8(0, 0x8000, 0x8000, 0x140, 0x11C);
    } else {
        func_80066940(0, 0, 0x28, 0x140, 0xC4);
        func_80066AA8(0, 0x8000, 0x8000, 0x140, 0xF0);
    }
    func_80066610();
    func_80066818(0, 1);
}

GLOBAL_ASM("asm/non_matchings/menu/menu_logo_screen_loop.s")

void set_magic_code_flags(s32 flags);

void func_80082FAC(void) {
    if (D_80126448 & 2) {
        set_magic_code_flags(2);
    }
    if ((D_80126448 & 0xFFFFF0) == 0xFFFFF0) {
        set_magic_code_flags(1);
    }
    if (D_80126448 & 1) {
        gIsInAdventureTwo = 1;
    } else {
        gIsInAdventureTwo = 0;
    }
    if ((D_80126448 & 0x2000000) == 0) {
        func_800C2AF4(0);
    }
    func_8007F900(get_language());
}

GLOBAL_ASM("asm/non_matchings/menu/func_80083098.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_title_screen_init.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008377C.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_title_screen_loop.s")

void func_80084118(void) {
    func_8009C4A8(D_800DF7C4);
    func_80000BE0(0x10);
    func_800660D0();
    func_800C422C(2);
    func_80000890(1);
}

void menu_options_init(void) {
    D_801263BC = 0;
    gMenuDelay = 0;
    func_800C01D8(D_800DF77C);
    func_800C4170(2);
    set_text_font(2);
    func_80000BE0(0x18);
    play_music(0x18);
    func_80000B18();
}

void func_800841B8(s32 arg0) {
    s32 phi_s1;
    s32 phi_a3;
    s32 phi_s2;

    set_text_font(2);
    set_text_background_color(0, 0, 0, 0);
    set_text_color(0, 0, 0, 0xFF, 0x80);
    draw_text(&D_801263A0, 0xA1, 0x23, D_800DF4A0->unk90, 0xC);
    set_text_color(0xFF, 0xFF, 0xFF, 0, 0xFF);
    draw_text(&D_801263A0, 0xA0, 0x20, D_800DF4A0->unk90, 0xC);
    
    phi_s1 = 0;
    phi_s2 = 0x4C;
    
    set_text_font(0);
    
    while(D_800DFA10[phi_s1] != NULL) {
        if (phi_s1 == D_800DF460) {
            phi_a3 = D_801263BC * 8;
            if (D_801263BC >= 0x20) {
                phi_a3 = 0x1FF - phi_a3;
            }
        } else {
            phi_a3 = 0;
        }
        set_text_color(0xFF, 0xFF, 0xFF, phi_a3, 0xFF);
        draw_text(&D_801263A0, -0x8000, phi_s2, D_800DFA10[phi_s1], 0xC);
        
        phi_s1++;
        phi_s2 += 0x1C;
    }
}

#if 1
GLOBAL_ASM("asm/non_matchings/menu/menu_options_loop.s")
#else

void func_80084734(void);
void set_language(s32 language);

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
    
    if (gMenuDelay >= -0x13 && gMenuDelay < 0x23) {
        func_800841B8(arg0);
    }
    
    buttonsPressed = 0;
    analogX = 0;
    analogY = 0;
    if (gIgnorePlayerInput == 0 && gMenuDelay == 0) {
        // Get input from all 4 controllers.
        s32 i;
        for (i = 0; i < 4; i++) {
            analogY += gControllersYAxisDirection[i]; // Y axis (-1 = down, 1 = up) for controller
            analogX += gControllersXAxisDirection[i]; // X axis (-1 = left, 1 = right) for controller
            buttonsPressed |= get_button_inputs_from_player(i); // Button presses for controller
        }
    }
    
    if ((buttonsPressed & 0x4000) || ((buttonsPressed & 0x9000) && D_800DF460 == 5)) {
        // Leave the option menu
        func_80000C98(-0x80, D_800DF460, analogX);
        gMenuDelay = -1;
        func_800C01D8(D_800DF774);
        func_80001D04(0x241, 0);
    } else if ((buttonsPressed & 0x9000) && D_800DF460 >= 2) {
        // Go to a sub-menu
        gMenuDelay = 0x1F;
        func_80001D04(0xEF, 0);
    } else if (D_800DF460 == 0 && analogX != 0) {
        // Change language
        s32 temp_v0 = get_language();
        if ((temp_v0 >> 0x1F) == 0 && temp_v0 == 0) {
            set_language(2); // Sets language to french
        } else {
            set_language(0); // Sets language to english
        }
        func_80001D04(0xEB, 0);
    } else if (D_800DF460 == 1 && analogX != 0) {
        // Enable/Disable subtitles.
        if (D_80126448+4 & 0x2000000) {
            func_80001D04(0xEB, 0);
            func_8009EABC(0, 0x2000000);
            func_800C2AF4(0);
            D_800DFA10[1] = D_800DF4A0->unk2DC;
        } else {
            func_80001D04(0xEB, 0);
            func_8009EA78(0, 0x2000000);
            func_800C2AF4(1);
            D_800DFA10[1] = D_800DF4A0->unk2D8;
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
    
    if (gMenuDelay >= 0x1F) {
        // Change screen to a sub-menu
        switch(D_800DF460) {
            case 2:
                func_80084734();
                menu_init(MENU_AUDIO_OPTIONS);
                return 0;
            case 3:
                func_80084734();
                menu_init(MENU_SAVE_OPTIONS);
                return 0;
            default:
                func_80084734();
                menu_init(MENU_MAGIC_CODES);
                return 0;
        }
    }
    if (gMenuDelay < -0x1E) {
        // Change screen back to the title screen.
        func_80000B28();
        func_80084734();
        menu_init(MENU_TITLE);
        return 0;
    }
    gIgnorePlayerInput = 0;
    return 0;
}
#endif


void func_80084734(void) {
    func_800C422C(2);
}

void func_8009C8A4(s16 *arg0);

void menu_audio_options_init(void) {
    gOptionsMenuItemIndex = 0;
    D_801263BC = 0;
    gMenuDelay = 0;
    D_801269FC = 0;
    D_801263D8 = -1;
    func_8009C674(D_800DFA2C);
    func_8009C8A4(&D_800DFA2C[6]);
    func_8008E4B0();
    func_800C01D8(D_800DF77C);
    func_8007FFEC(2);
    gMusicVolumeSliderValue = musicGetVolSliderPercentage();
    gSfxVolumeSliderValue = sfxGetVolumeSlider();
    if (gActiveMagicCodes & CHEAT_MUSIC_MENU) { // Check if "JUKEBOX" cheat is active
        D_800DFA3C[6].unkC = D_801269E0;
        D_800DFA3C[3].unk2 = 0xD4;
        func_80000BE0(0x20);
        D_801263E0 = 5;
    } else {
        D_800DFA3C[6].unkC = NULL;
        D_800DFA3C[3].unk2 = 0xC0;
        D_801263E0 = 4;
    }
    func_800C4170(2);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80084854.s")

#if 1
GLOBAL_ASM("asm/non_matchings/menu/menu_audio_options_loop.s")
#else

extern s32 D_800DFABC;
extern s32 D_800DFAC8;

void func_800851FC(void);

s32 menu_audio_options_loop(s32 arg0) {
    s32 sp40;
    s32 sp30;
    s32 phi_a2;
    s32 phi_a3;
    s32 phi_t0;
    s32 phi_s0;

    sp30 = 0;
    D_801263BC = (s32) ((D_801263BC + arg0) & 0x3F);
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
        sp40 = 0;
        phi_a2 = 0;
        phi_a3 = 0;
        phi_t0 = 0;
        phi_s0 = 0;
        
        while(phi_s0 != 4) {
            sp40 |= get_button_inputs_from_player(phi_s0);
            phi_a2 += func_8006A59C(phi_s0);
            phi_a3 += gControllersYAxisDirection[phi_s0];
            phi_t0 += gControllersXAxisDirection[phi_s0];
            phi_s0++;
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
        
        if (((sp40 & 0x9000) && (D_801263E0 == gOptionsMenuItemIndex + 1)) || (sp40 & 0x4000)) {
            gMenuDelay = -1;
            func_800C01D8(D_800DF774);
            if (D_801263D8 >= 0) {
                func_80000C98(-0x80);
            }
            sp30 = 3;
        } else if (phi_a3 < 0 && gOptionsMenuItemIndex < D_801263E0 - 1) {
            gOptionsMenuItemIndex++;
            sp30 = 1;
        } else if (phi_a3 > 0 && gOptionsMenuItemIndex > 0) {
            gOptionsMenuItemIndex--;
            sp30 = 1;
        } else if (gOptionsMenuItemIndex == 0 && phi_t0 != 0) {
            if (phi_t0 < 0) {
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
            func_80065BD0(D_800DFAC8);
            sp30 = 1;
        } else if ((phi_a2 >> 2) != 0) {
            if(gOptionsMenuItemIndex == 2) {
                gSfxVolumeSliderValue += (phi_a2 >> 2);
                if (gSfxVolumeSliderValue < 0) {
                    gSfxVolumeSliderValue = 0;
                } else if (gSfxVolumeSliderValue >= 0x101) {
                    gSfxVolumeSliderValue = 0x100;
                }
                sfxSetVolumeSlider(gSfxVolumeSliderValue);
            } else if(gOptionsMenuItemIndex == 1) {
                gMusicVolumeSliderValue += (phi_a2 >> 2);
                if (gMusicVolumeSliderValue < 0) {
                    gMusicVolumeSliderValue = 0;
                } else {
                    if (gMusicVolumeSliderValue >= 0x101) {
                        gMusicVolumeSliderValue = 0x100;
                    }
                }
                func_80001A3C(gMusicVolumeSliderValue);
                if (!musicIsPlaying()) {
                    if (D_801263D8 >= 0) {
                        func_80000B28();
                        play_music((u8)D_800DFABC);
                    } else {
                        func_80000B28();
                        func_80000BE0(0x18);
                        play_music(0x18);
                        func_80000B18();
                    }
                }
            }
        } else if (D_801263E0 >= 5 && gOptionsMenuItemIndex == 1) {
            if (phi_t0 < 0 && D_800DFABC > 0) {
                D_800DFABC--;
                sp30 = 1;
            } else if (phi_t0 > 0 && D_800DFABC < (ALSeqFile_80115CF8_GetSeqCount() - 1)) {
                D_800DFABC++;
                sp30 = 1;
            }
            if (sp40 & 0x9000) {
                func_80000B28();
                func_80000BE0(0x18);
                play_music((u8)D_800DFABC);
                D_801263D8 = D_800DFABC;
            }
        }
        
        if (gOptionsMenuItemIndex == 1 && D_801269FC == 0) {
            func_80001D04(0x19B, &D_801269FC);
        } else if (D_801269FC != 0) {
            func_8000488C(D_801269FC);
        }
        
        if (sp30 == 3) {
            func_80001D04(0x241, 0);
        } else if (sp30 == 2) {
            func_80001D04(0xEF, 0);
        } else if (sp30 == 1) {
            func_80001D04(0xEB, 0);
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

#endif

void func_800851FC(void) {
    if (D_801269FC != 0) {
        func_8000488C(D_801269FC);
    }
    if (D_801263D8 >= 0) {
        func_80000BE0(0x18);
        play_music(0x18);
        func_80000C98(0x100);
        func_80000B18();
    }
    func_8009C4A8(D_800DFA2C);
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
    func_8009C8A4(D_800DFCAC);
    func_8007FFEC(0xA);
    func_800C4170(2);
    D_800DFC10.unk0 = D_80126550[71];
    D_800DFC20.unk0 = D_80126550[72];
    D_800DFC30.unk0 = D_80126550[75];
    D_800DFC40.unk0 = D_80126550[74];
    D_800DFC50.unk0 = D_80126550[73];
    D_800DFC60.unk0 = D_80126550[70];
    func_8008E4B0();
    func_8006EBA8();
    func_800C01D8(D_800DF77C);
}

GLOBAL_ASM("asm/non_matchings/menu/func_800853D0.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80085B9C.s")

/* Size: 0x10 Bytes */
typedef struct unk800860A8 {
    s8 unk0;
    u8 pad1[0x5];
    s8 unk6;
    u8 pad7[0x5];
    s32 unkC;
} unk800860A8;

s32 func_800860A8(s32 arg0, s32 *arg1, unk800860A8 *arg2, s32 *arg3, s32 arg4) {
    s32 temp_v1;
    s32 phi_t0;

    phi_t0 = 0;
    if (*arg1 != 0) {
        phi_t0 = func_80076194(arg0, &arg2[*arg3].unkC, &D_80126A20[arg0]);
        if (phi_t0 == 0) {
            if ((arg2[*arg3].unkC >= arg4) && (D_80126A20[arg0] > 0)) {
                arg2[*arg3].unk0 = 8;
                arg2[*arg3].unk6 = arg0;
                (*arg3)++;
            }
        } else {
            if((*arg1 < 0) && ((phi_t0 & 0xFF) == 7)) {
                *arg1 = 0;
                phi_t0 = 0;
            } else {
                temp_v1 = phi_t0 & 0xFF;
                if (temp_v1 != 3 && temp_v1 != 2 && temp_v1 != 9) {
                    phi_t0 = 0;
                }
            }
        }
    }
    
    return phi_t0;
}

/* Size: 0x10 bytes */
typedef struct unk800861C8 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 pad3;
    u16 pad4;
    s8  unk6;
    s8  pad7;
    u32 pad8;
    u32 unkC;
} unk800861C8;

void func_800861C8(unk800861C8* arg0, s32 *arg1) {
    s32 i;
    for(i = 0; i < 3; i++) {
        if (D_80126530[i]->newGame != 0) {
            arg0[*arg1].unk0 = 1;
            arg0[*arg1].unk1 = 0;
            arg0[*arg1].unk2 = 0;
            arg0[*arg1].unk6 = i;
            arg0[*arg1].unkC = func_80073C4C();
            (*arg1)++;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_800862C4.s")
GLOBAL_ASM("asm/non_matchings/menu/func_800867D4.s")

#if 1
GLOBAL_ASM("asm/non_matchings/menu/func_80086A48.s")
#else
void func_80086A48(s32 arg0) {
    f32 temp, temp2, temp3;
    temp = D_80126BD4;
    temp2 = D_80126BE4;
    while (arg0 > 0) {
        temp3 = 0.1f;
        if (D_80126A08 > 0) {
            D_80126BDC = D_80126BDC + temp3 * (temp - D_80126BDC);
        }
        if (D_801263E0 > 0 && D_80126A00 > 0) {
            D_80126BEC = D_80126BEC + temp3 * (temp2 - D_80126BEC);
        }
        arg0--;
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/menu/func_80086AFC.s")
GLOBAL_ASM("asm/non_matchings/menu/func_800871D8.s")


s32 func_800874D0(s32 arg0, s32 arg1) {
    s32 sp1C;

    sp1C = 0;
    if (arg0 & 0x4000) {
        D_801263E0 = 0;
        if (D_80126A10 != D_80126A14) {
            func_800871D8(8);
        } else {
            func_80001D04(0x241, NULL);
            sp1C = -1;
        }
    } else if (arg0 & 0x9000) {
        func_80001D04(0xEF, NULL);
        D_801263E0 = 4;
    } else if ((arg1 < 0) && (D_80126BD4 > 0)) {
        func_80001D04(0xEB, NULL);
        D_80126BD4 = (s32) (D_80126BD4 - 1);
    } else if ((arg1 > 0) && (D_80126BD4 < (D_80126A08 - 1))) {
        func_80001D04(0xEB, NULL);
        D_80126BD4 = (s32) (D_80126BD4 + 1);
    }
    return sp1C;
}

s32 func_800875E4(s32 arg0, s32 arg1) {
    if (arg0 & 0x4000) {
        func_80001D04(0x241, NULL);
        D_801263E0 = 3;
    } else if (arg0 & 0x9000) {
        func_80001D04(0xEF, NULL);
        D_801263E0 = 6;
    } else if ((arg1 < 0) && (D_80126BE4 > 0)) {
        func_80001D04(0xEB, NULL);
        D_80126BE4 = (s32) (D_80126BE4 - 1);
    } else if ((arg1 > 0) && (D_80126BE4 < D_80126A00 - 1)) {
        func_80001D04(0xEB, NULL);
        D_80126BE4 = (s32) (D_80126BE4 + 1);
    }
    
    return 0;
}


s32 func_800876CC(s32 arg0, s32 arg1) {
    if (arg0 & 0x4000) {
        func_80001D04(0x241, NULL);
        D_801263E0 = 5;
    } else if (arg0 & 0x9000) {
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
    func_800C5494(7);
    free_from_memory_pool(D_80126A0C);
    free_from_memory_pool(D_80126A64);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80087F14.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008832C.s")

void menu_boot_init(void) {
    s32 i;

    func_800C01D8(D_800DF77C);
    func_80077B34(0, 0, 0);
    func_8009C674(&D_800DF7C4);
    
    // Sets up the 11 texture pointers for the "Diddy Kong Racing" logo.
    for(i = 0; i < 11; i++) {
        D_800DF7DC[i].texture = D_80126550[D_800DF7C4[i]];
    }
    
    // Reset variables for menu_boot_loop()
    D_80126C20 = 0; // D_80126C20 is the current state of the boot screen. Either 0, 1, or 2.
    D_80126C18 = 0; // D_80126C18 is a timer for the boot screen, counts up to 0x8C frames.
}

#ifdef NON_MATCHING
void func_800887E8(void);
void func_800887C4(void);

s32 menu_boot_loop(s32 arg0) {
    s32 sp2C;
    s32 phi_v1;

    sp2C = 0;
    phi_v1 = 0x78;
    if (osTvType == 0) {
        phi_v1 = 0x84;
    }
    
    switch(D_80126C20) {
        case 0:
            if (D_80126C18 < 0x20) {
                D_80126C18 += arg0;
                if (D_80126C18 >= 0x21) {
                    D_80126C18 = 0x20;
                }
            } else {
                func_800887E8();
                D_80126C20 = 1;
            }
            break;
        case 1:
            if (D_80126C18 < 0x8C) {
                D_80126C18 += arg0;
                if (D_80126C18 >= 0x8D) {
                    D_80126C18 = 0x8C;
                }
            } else {
                func_800887C4();
                D_80126C20 = 2;
            }
            if (D_80126C18 >= 0x81) {
                phi_v1 = 0x12C;
            }
            break;
        case 2:
            if (gMenuDelay && func_800C018C(arg0, 0x12C) == 0) {
                func_800C01D8(&D_800DF76C, arg0);
            }
            sp2C = func_800890AC(arg0);
            phi_v1 = 0x12C;
            break;
    }
    
    if (phi_v1 < 0x12C) {
        func_80078AB8(&D_801263A0, &D_800DF7DC, 0xA0, phi_v1, 0xFF, 0xFF, 0xFF, 0xFF);
        func_8007B3D0(&D_801263A0);
    }
    
    return sp2C;
}
#else
GLOBAL_ASM("asm/non_matchings/menu/MenuBootLoop.s")
#endif

void func_800887C4(void) {
    func_8009C4A8((s16*)D_800DF7C4);
}

void func_800887E8(void) {
    s32 i;

    // Starting point
    D_80126AA0[0] = allocate_from_main_pool_safe(0x200, COLOR_TAG_WHITE);
    
    // Fills in the table.
    for(i = 1; i < 16; i++) {
        D_80126AA0[i] = (s32*)(((u32)D_80126AA0[0]) + (i * 0x20));
    }
    
    for(i = 0; i < 1; i++) {
        D_80126A60[i] = 0;
    }
    
    D_80126C10 = 0;
    D_801263E0 = 0;
    D_801263BC = 0;
    D_80126A68 = -1;
    func_8007F900(get_language());
    if (func_80087F14(&D_80126A68, 0) == 0) {
        gMenuDelay = 0;
    } else if (func_8008832C() == 0) {
        gMenuDelay = 0x14;
    }
    if (D_80126BC8 == 0 && D_800DFD94 == 0) {
        gMenuDelay = 0x14;
    }
    D_800DF460 = 0;
    D_801263D8 = 0;
    func_8009C6D4(0x3F);
    func_8008E4B0();
    if (osTvType == 0) {
        D_80126BB4 = 8;
    } else {
        D_80126BB4 = 7;
    }
    func_800C4170(2);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80088938.s")
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
    D_80126470 = 0;
    D_80126C4C = -1;
    D_80126C58[0] = 0;
    D_801263BC = 0;
    gMenuDelay = 0;
    D_801263D8 = 0;
    D_801263E0 = 0;
    func_800C01D8(D_800DF77C);
    func_800C4EDC(7, 0x32, 0x32, 0x10E, 0x84);
    func_800C4FBC(7, 0, 0, 0, 0x80);
    func_800C5494(7);
    func_800C4170(2);
}

GLOBAL_ASM("asm/non_matchings/menu/func_800896A4.s")
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
    func_800C01D8(D_800DF77C);
    if (osTvType == 0) {
        D_80126C70 = 0xB;
    } else {
        D_80126C70 = 0xA;
    }
}


GLOBAL_ASM("asm/non_matchings/menu/func_8008A56C.s")

void func_8008A8F8(s32 arg0, s32 arg1, s32 arg2) {
    if ((arg0 & arg1) && (arg0 & gActiveMagicCodes)) {
        gActiveMagicCodes &= ~arg2;
    }
}

#if 1
GLOBAL_ASM("asm/non_matchings/menu/menu_magic_codes_list_loop.s")
#else

extern s16 D_80126C80[0x1E]; // Array of shorts of the unlocked cheat's bit ids.
void func_8008AD1C(void);
void func_8008A56C(void);
s32 get_button_inputs_from_player(s32 arg0);

s32 menu_magic_codes_list_loop(s32 arg0) {
    s32 temp_t0;
    s32 phi_a2;
    s32 phi_s0;
    s32 sp48;
    s32 phi_s1;
    s32 phi_s2;
    s32 phi_a3_2;
    s32 phi_v0_2;
    s32 phi_s3;
    s8 *temp, *temp2;

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
        func_8008A56C();
    }
    
    phi_s3 = 0;
    phi_a2 = 0;
    phi_s2 = 0;
    if (!gIgnorePlayerInput && gMenuDelay == 0) {
        phi_s0 = 0; 
        temp = (s8*)&gControllersYAxisDirection;
        temp2 = (s8*)&gControllersXAxisDirection;
        while(phi_s0 < 4) {
            phi_s3 |= get_button_inputs_from_player(phi_s0);
            phi_a2 += *temp;
            phi_s2 += *temp2;
            temp++;
            temp2++;
            phi_s0++;
        }
    }
    
    phi_s0 = 0;
    phi_s1 = 1;
    phi_a3_2 = 0;
    while(phi_s0 < 32) { // 32 is the max number of cheats.
        if (phi_s1 & gUnlockedMagicCodes) {
            D_80126C80[phi_a3_2] = phi_s0;
            phi_a3_2++;
        }
        phi_s1 <<= 1;
        phi_s0++;
    }
    
    if (((phi_a2 < 0) || (phi_a2 > 0)) && (phi_a3_2 != gOptionsMenuItemIndex)) {
        func_80001D04(0xEF, NULL);
        phi_s1 = 1 << D_80126C80[gOptionsMenuItemIndex];
        gActiveMagicCodes ^= phi_s1; // Toggle active cheats?
        func_8008A8F8(phi_s1, 0x10, 0x20);  // func_8008A8F8() = Clear flags?
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
    
    if (phi_s2 < 0) {
        gOptionsMenuItemIndex++;
        if (phi_a3_2 < gOptionsMenuItemIndex) {
            gOptionsMenuItemIndex = phi_a3_2;
        }
    }
    if (phi_s2 > 0) {
        gOptionsMenuItemIndex--;
        if ((s32) gOptionsMenuItemIndex < 0) {
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
    
    if ((phi_s3 & 0x9000) && (phi_a3_2 == gOptionsMenuItemIndex)) {
        sp48 = -1;
    }
    if (phi_s3 & 0x4000) {
        sp48 = -1;
    }
    if (sp48 != 0) {
        gMenuDelay = sp48;
        func_800C01D8(D_800DF774);
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
#endif

void func_8008AD1C(void) {
    func_8009C508(0x3F);
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/menu/func_8008AD44.s")

void func_8008AEB4(s32 arg0, s32 *arg1) {
    switch(arg0) {
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
    
    for(i = 0; i < 4; i++) {
        gActivePlayersArray[i] = (i == controllerIndex) ? 1 : 0;
    }
}

GLOBAL_ASM("asm/non_matchings/menu/menu_character_select_init.s")

/**
 * Draws the "Player Select" and "OK?" text in the character select menu.
 */
void draw_character_select_text(s32 arg0) {
    s32 yPos;
    if (gMenuDelay >= -0x16 && gMenuDelay < 0x17) {
        set_text_font(2); // Set font to the Big Yellow Text
        set_text_background_color(0, 0, 0, 0);
        set_text_color(0, 0, 0, 0xFF, 0x80);
        // Draw "Player Select" text drop shadow
        draw_text(&D_801263A0, 0xA1, 0x23, D_800DF4A0->unk21C, 0xC); 
        set_text_color(0xFF, 0xFF, 0xFF, 0, 0xFF);
        // Draw "Player Select" text
        draw_text(&D_801263A0, 0xA0, 0x20, D_800DF4A0->unk21C, 0xC); 
        if (gNumberOfReadyPlayers == gNumberOfActivePlayers && gNumberOfActivePlayers > 0) {
            yPos = 0xD0;
            if (osTvType == 0) {
                yPos = 0xEA;
            }
            draw_text(&D_801263A0, 0xA0, yPos, D_800E8230 /* "OK?" */, 0xC);
        }
        func_8007B3D0(&D_801263A0);
        func_800660EC(40.0f);
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_8008B358.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008B4C8.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008B758.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008BB3C.s")

#if 1
GLOBAL_ASM("asm/non_matchings/menu/menu_character_select_loop.s")
#else

void func_8008C128(void);

s32 menu_character_select_loop(s32 arg0) {
    s32 i;
    s32 phi_a0;
    s32 phi_t3;
    s8 activePlayers[4];

    draw_character_select_text(arg0);
    func_8008C168(arg0);
    func_8008E4EC();
    
    for(i = 0; i < 4; i++){
        if (1 == D_801263DC[i]) {
            D_801263DC[i] = 2;
        }
    }
    gIgnorePlayerInput = 0;
    if (gMenuDelay == 0) {
        // Issue: this loop unrolls weirdly.
        for (i = 0; i < 4; i++) {
            activePlayers[i] = gActivePlayersArray[i];
        }
        func_8008B358();
        if (gNumberOfReadyPlayers == gNumberOfActivePlayers) {
            func_8008B4C8(); // Cancel/Confirm selected character?
        } else {
            func_8008B758(activePlayers); // Move and select characters?
        }
        return 0; // This return needs to be here.
    } else if (gMenuDelay > 0) {
        gMenuDelay += arg0;
        if (gMenuDelay >= 0x1F) {
            phi_t3 = 0;
            if (D_800DFFD0 == 0) {
                phi_t3++;
                if ((gActiveMagicCodes << 7) < 0) {
                    phi_t3++;
                }
            }
            func_8008C128();
            
            // Regalloc issue: gActivePlayersArray and phi_a0 need to switch registers.
            phi_a0 = 0;
            for(i = 0; i < 4; i++) {
                if (gActivePlayersArray[i]) {
                    gCharacterIdSlots[phi_a0] = (*D_801263CC)[gPlayersCharacterArray[i]].unkC;
                    phi_a0++;
                }
            }
            func_8008BB3C(phi_a0);
            func_8006A458(gActivePlayersArray);
            
            gIsInTracksMode = 1;
            if (phi_t3 >= gNumberOfActivePlayers) {
                func_80000B18();
                func_8006E2E8(0x27, -1, 0);
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
        gMenuDelay -= arg0;
        if (gMenuDelay < -0x1E) {
            func_80000B28();
            func_8008C128();
            gNumberOfActivePlayers = 1;
            menu_init(MENU_TITLE);
        }
    }
    return 0;
}

#endif

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
            while(i < 4 && !someBool){
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
    func_8009C4A8((s16*)&D_800DFDC8);
    set_free_queue_state(0);
    func_800C422C(2);
    set_free_queue_state(2);
    D_800DFFD0 = 0;
}

GLOBAL_ASM("asm/non_matchings/menu/func_8008C168.s")

void menu_caution_init(void) {
    gIgnorePlayerInput = 0x3C;
    gMenuDelay = 0;
    func_800C4170(2);
    func_800C01D8(D_800DF77C);
    gPlayerHasSeenCautionMenu = 1;
}

void func_8008C4E8(void);

void draw_menu_element(s32, MenuElement*, f32);

s32 menu_caution_loop(s32 arg0) {
    if (gMenuDelay != 0) {
        gMenuDelay += arg0;
    } else if (gIgnorePlayerInput <= 0 && get_button_inputs_from_player(0) & 0xD000) {
        func_80001D04(0xEF, NULL);
        gMenuDelay = 1;
        func_800C01D8(D_800DF774);
    }
    if (gMenuDelay < 0x14) {
        draw_menu_element(1, D_800DFFD8, 1.0f);
    }
    if (gMenuDelay >= 0x1F) {
        func_8008C4E8();
        menu_init(MENU_GAME_SELECT);
    }
    if (gIgnorePlayerInput > 0) {
        gIgnorePlayerInput -= arg0;
    }
    return 0;
}

void func_8008C4E8(void) {
    func_800C422C(2);
}

#ifdef NON_MATCHING

typedef struct unk80126460 {
    MenuElement unk0;
    MenuElement unk20;
} unk80126460;

void menu_game_select_init(void) {
    s32 i, j, index;

    gMenuDelay = 0;
    D_801263BC = 0;
    D_800DF460 = 0;
    D_801263E0 = 2;
    func_800C01D8(D_800DF77C);
    func_8006EBA8();
    func_8001B790();
    D_801263D8 = 1;
    func_8009C6D4(0x43);
    func_8007FFEC(3);
    func_800C4170(2);
    play_music(0x1A);
    
    for(i = 0; i < 10; i++) {
        if (i != D_801263B4) {
            func_80001114(D_800DFDB4[i][0]);
            func_80001114(D_800DFDB4[i][1]);
        }
    }
    
    func_80001114(6);
    func_80000B18();
    if (func_8009EC60()) {
        D_80126460 = D_800E0278;
        D_801263E0 = 2;
    } else {
        D_80126460 = D_800E0198;
        D_801263E0 = 1;
    }
    
    // This loop doesn't match.
    for(i = 0; i <= D_801263E0; i++) {
        ((unk80126460*)D_80126460 + i + 1)->unk0.texture = D_80126550[67];
    }
}
#else
GLOBAL_ASM("asm/non_matchings/menu/menu_game_select_init.s")
#endif

#if 1
GLOBAL_ASM("asm/non_matchings/menu/func_8008C698.s")
#else
typedef struct unk80126460 {
    MenuElement textShadow;
    MenuElement text;
} unk80126460;

extern unk80126460 *D_80126460[4];

void func_8008C698(s32 arg0) {
    s32 fade;
    s32 i;
    s32 filterAlpha;

    if (gMenuDelay >= -21 && gMenuDelay < 22) {
        fade = D_801263BC * 8;
        fade = fade;
        if (fade >= 0x100) {
            fade = 0x1FF - fade;
        }
        func_80067F2C(&D_801263A0, &D_801263A8);
        
        for(i = 0; i <= D_801263E0; i++) {
            filterAlpha = 0;
            if (i == D_800DF460) {
                filterAlpha = fade;
            }
            ((unk80126460*)(*D_80126460 + i + 1))->text.filterAlpha = filterAlpha;
        }
        
        if (osTvType == 0) {
            D_800DF79C = 0xC;
            D_800DF7A0 = 0;
        } else {
            D_800DF79C = 0;
            D_800DF7A0 = 0;
        }
        
        draw_menu_element(1, (MenuElement*)*D_80126460, 1.0f);
        func_80080BC8(&D_801263A0);
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/menu/menu_game_select_loop.s")

void func_8008CACC(void) {
    func_800C422C(2);
    func_8007FF88();
    func_8009C508(0x43);
}

void menu_file_select_init(void) {
    s32 i;
    s32 sp38;
    s32 sp34;

    func_8006B224(&sp38, &sp34);
    func_8009C674(D_800E0398);
    func_8009C8A4(D_800E03A4);
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
    func_800C01D8(D_800DF77C);
    func_800C4170(2);
    play_music(0x1A);
    for(i = 0; i < 10; i++) {
        if (i != D_801263B4) {
            func_80001114(D_800DFDB4[i][0]);
            func_80001114(D_800DFDB4[i][1]);
        }
    }
    func_80001114(6);
    func_80000B18();
}

GLOBAL_ASM("asm/non_matchings/menu/func_8008CC28.s")

GLOBAL_ASM("asm/non_matchings/menu/func_8008CD74.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008D5F8.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008D8BC.s")

#if 1
GLOBAL_ASM("asm/non_matchings/menu/func_8008DC7C.s")
#else
/* Size: 0x0C Bytes */
typedef struct unk801264A0 {
    u8 unk0;
    u8 unk1;
    u16 unk2;
    char name[4];
    u32 pad8;
} unk801264A0;

extern unk801264A0 D_801264A0[3]; // Filename structs?
extern s32 D_80126494;
extern s32 D_8012648C;

void func_8008DC7C(s32 arg0) {
    s32 temp_t6;
    s32 temp_a1;
    s32 phi_v1;
    s32 phi_v1_2;

    phi_v1 = get_button_inputs_from_player(0);
    temp_a1 = gControllersXAxisDirection;
    if (gNumberOfActivePlayers == 2) {
        phi_v1 = phi_v1 | get_button_inputs_from_player(1);
        temp_a1 += gControllersXAxisDirection+1;
    }
    
    if (D_80126494 == 0) {
        if (phi_v1 & 0x4000) {
            func_80001D04(0x241, NULL);
            D_80126488 = 0;
        } else if (phi_v1 & 0x9000) {
            if (D_801264A0[D_8012648C].unk0 == 0) {
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
            D_801264A0[D_8012648C].unk0 = 0;
            D_801264A0[D_8012648C].unk1 = 0;
            D_801264A0[D_8012648C].unk2 = 0;
            D_801264A0[D_8012648C].name[0] = 'D';
            D_801264A0[D_8012648C].name[1] = 'K';
            D_801264A0[D_8012648C].name[2] = 'R';
            D_801264A0[D_8012648C].name[3] = '\0';
            gSaveFileIndex = (s32) D_8012648C;
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
    D_800E045C.unk0 = D_80126550[24];
    D_800E045C.unk8 = D_80126550[25];
    D_800E0474.unk0 = D_80126550[26];
    D_800E0474.unk8 = D_80126550[27];
    D_800E048C.unk0 = D_80126550[28];
    D_800E048C.unk8 = D_80126550[29];
}

void func_8008E4B0(void) {
    D_800E041C.unk0 = D_80126550[61];
    D_800E042C.unk0 = D_80126550[60];
    D_800E043C.unk0 = D_80126550[63];
    D_800E044C.unk0 = D_80126550[62];
}

GLOBAL_ASM("asm/non_matchings/menu/func_8008E4EC.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_track_select_init.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8008F00C.s")

#ifdef NON_MATCHING

// Close to done with this function. Just a regalloc issue remains.

void func_8008F534(void);
void func_8008FF1C(s32 arg0);
void func_800904E8(s32 arg0);
void func_80090918(s32 arg0);
void func_80090ED8(s32 arg0);
void func_80090F30(s32 arg0);
void func_80092188(s32 arg0);
void func_8008E4EC(void);
s32 func_800C73E0(void);
void set_relative_volume_for_music(u8 arg0);

s32 menu_track_select_loop(s32 arg0) {
    s32 phi_a2;
    Settings *settings;
    s32 i = 0;

    settings = get_settings();
    D_801263BC = (D_801263BC + arg0) & 0x3F;
    if (func_800C73E0() == 0 && gMenuDelay != 0) {
        if (gMenuDelay < 0) {
            gMenuDelay -= arg0;
        } else {
            gMenuDelay += arg0;
        }
    }
    func_8008E4EC();
    
    fast3d_cmd(D_801263A0++, 0xB6000000, 0x00001000) // gSPClearGeometryMode(D_801263A0++, G_CULL_FRONT)
    
    switch(D_801267D0) {
        case 0:
            func_8008FF1C(arg0);
            func_800904E8(arg0);
            func_80090918(arg0);
            break;
        case 1:
            func_80090ED8(arg0);
            func_80090F30(arg0);
            func_80092188(arg0);
            break;
    }
    
    if (D_800DF760 < 0) {
        set_relative_volume_for_music(0);
    } else {
        D_800DF760 += arg0 * 2;
        if (D_800DF760 >= 0x51) {
            D_800DF760 = 0x50;
        }
        set_relative_volume_for_music((u8)D_800DF760);
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
            func_8006E2E8(0x16, -1, phi_a2);
            func_8008AEB4(0, NULL);
            menu_init(MENU_CHARACTER_SELECT);
            return 0;
        }
        func_8006E2E8(0x27, -1, 0);
        menu_init(MENU_GAME_SELECT);
        return 0;
    }
    if (D_801267D0 >= 2) {
        func_8008F534();
        if (gMultiplayerSelectedNumberOfRacersCopy != gMultiplayerSelectedNumberOfRacers) {
            // regalloc issue with the for loop.
            for(i = 0; i < 8; i++) {
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
    for(i = 0; i < 15; i += 3){
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

void func_80090ED8(s32 arg0) {
    if (D_801263E0 == 1 && D_800E0414 == 0 && D_80126840 == 0) {
        func_80001D04(0x132, &D_80126840);
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_80090F30.s")

GLOBAL_ASM("asm/non_matchings/menu/func_80092188.s")

s32 func_80092BE0(s32 arg0) {
    s8 *trackIdArray; 
    s32 index;
    s32 temp;
    
    trackIdArray = (s8 *)func_8001E29C(0x1C);
    
    index = 0;
    temp = -1;
    if (trackIdArray[0] != -1) {
        while(temp < 0) {
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
        s64 temp2 = 0x10 << temp;
        if ((temp2 & D_80126448) == 0) {
            temp = -1;
        }
    }
    
    return temp;
}

#if 1
GLOBAL_ASM("asm/non_matchings/menu/menu_5_init.s")
#else

extern s16 D_800E0758[8]; // Unknown number of entries.

void menu_5_init(void) {
    s32 temp_v0_2;
    s8 temp_s0;
    Settings *settings;

    settings = get_settings();
    gTrackIdForPreview = 0;
    D_801263BC = 0;
    gMenuDelay = 0;
    temp_s0 = settings->unk4C->unk2;
    gPlayerSelectVehicle = func_8006B0AC(temp_s0);
    temp_v0_2 = func_8006B14C(temp_s0);
    if (temp_v0_2 != 5) {
        if (temp_v0_2 != 8) {
            if ((temp_v0_2 & 0x40) == 0) {
                if ((*(settings->courseFlagsPtr + (temp_s0 * 4)) & 2) == 0) {
block_4:
                    if (D_800E0758[temp_s0] != -1) {
                        func_80000FDC(D_800E0758[temp_s0] & 0xFFFF, 0, 0x3F800000);
                    }
                    D_801263E0 = -1;
                } else {
block_7:
                    if (D_800E0758[temp_s0] != -1) {
                        func_80000FDC(D_800E0758[temp_s0] & 0xFFFF, 0, 0x3F000000);
                    }
                    func_80000BE0(0x18);
                    play_music(0x18);
                    func_80000B18();
                    D_801263E0 = 0;
                    func_8009C674(&D_800E0FB4);
                    func_8009C8A4(&D_800E0FD8);
                    func_8008E45C();
                    D_800E04D4 = (s32) D_80126550.unk7C;
                    D_800E04E4 = (s32) D_80126550.unk78;
                    D_800E04F4 = (s32) D_80126550.unk84;
                    D_800E0504 = (s32) D_80126550.unk80;
                    D_800E0514 = (s32) D_80126550.unk8C;
                    D_800E0524 = (s32) D_80126550.unk88;
                    D_800E05B4 = (s32) D_80126550.unkC0;
                    D_800E0614 = (s32) D_80126550.unk178;
                    func_800C01D8(D_800DF77C);
                    D_801263BC = 0;
                    gMenuDelay = 0;
                    D_800E0980 = 0x1E;
                    func_800C4170(2);
                    func_8006E2E8(temp_s0, -1, 1);
                }
            } else {
                goto block_7;
            }
        } else {
            goto block_4;
        }
    } else {
        goto block_4;
    }
    func_800C5494(7);
    if (func_8006B14C(temp_s0) & 0x40) {
        func_800C31EC(func_8006B190(temp_s0) + 0x3B);
    }
}
#endif

GLOBAL_ASM("asm/non_matchings/menu/func_80092E94.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_5_loop.s")

void func_80093A0C(void) {
    func_8009C4A8((s16*)&D_800E0FB4);
    func_800C422C(2);
    func_80000B28();
}

GLOBAL_ASM("asm/non_matchings/menu/func_80093A40.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80093D40.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80094170.s")

void func_800945B0(void) {
    func_80072298(1);
    func_800C5620(7);
    func_800C5494(7);
    D_800E0984 = 0;
}

void func_800945E4(void) {
    func_800945B0();
}

void func_80094604(void) {
    D_800E0A50.unk0 = D_80126550[50];
    D_800E0A60.unk0 = D_80126550[51];
    D_800E0A70.unk0 = D_80126550[52];
    D_800E0A90.unk0 = D_80126550[54];
    D_800E0A80.unk0 = D_80126550[53];
    D_800E0AA0.unk0 = D_80126550[55];
    D_800E0AB0.unk0 = D_80126550[56];
    D_800E0AC0.unk0 = D_80126550[57];
    D_800E0AD0.unk0 = D_80126550[58];
    D_800E0AE0.unk0 = D_80126550[59];
}

GLOBAL_ASM("asm/non_matchings/menu/func_80094688.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80094A5C.s")

void func_80094C14(s32 arg0) {
    D_801263BC = (D_801263BC + arg0) & 0x3F;
    D_80126A94 += arg0;
    if (D_801263D8 >= 0) {
        D_801263D8 += arg0;
        switch(D_800DF460) {
            case 0:
                if (func_8000C8B4(0xF0, &D_80126A94) < D_801263D8) {
                    func_80000C98(-0x100);
                    D_800DF460 = 1;
                }
                break;
            case 1:
                if (func_8000C8B4(0x12C, &D_80126A94) < D_801263D8) {
                    func_80000BE0(0x18);
                    play_music(0x18);
                    func_80000C98(0x100);
                }
                break;
        }
        if (func_8000C8B4(0x12C) < D_801263D8) {
            D_801263D8 = -1;
        }
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_80094D28.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80095624.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80095728.s")

void func_800981E8(void);

void func_80096790(void) {
    s32 temp;
    s8 *temp2;
    
    temp2 = (s8*)get_current_level_header();
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
    D_80126BF0[0] = (s32) D_800DF4A0->unk60;
    D_80126BF0[1] = (s32) D_800DF4A0->unk5C;
    D_80126BF0[2] = (s32) D_800DF4A0->unk70;
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
    func_8009C8A4(D_800E0A40);
    func_80094604();
    func_800C4170(2);
    func_800C01D8(D_800DF77C);
    func_80000BE0(0x18);
    play_music(0x18);
    func_80000C98(0x80);
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
    for(index = length - 1; index >= 0; ) {
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

#if 1
GLOBAL_ASM("asm/non_matchings/menu/func_800977D0.s")
#else
s32 func_800977D0(unsigned char *arg0, unsigned char *arg1) {
    s32 phi_v0 = 0;
    s32 phi_v1 = 0;
    while (*arg0 != '\0') {
        if (*arg0 == ' ') {
            arg0++;
            phi_v0++;
            while (*arg0 == ' ') {
                arg0++;
                phi_v0++;
            }
            if (*arg0 != '\0') {
                while(phi_v1 < phi_v0){
                    *arg1 = *arg0;
                    arg0++;
                    arg1++;
                    phi_v1++;
                }
            }
            
        } else {
            *(arg1++) = *(arg0++);
        }
    }
    *arg1 = '\0';
}
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
    D_80126C50 = (f32) *D_80126C6C;
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

extern s32 D_800E0980;
s8* func_8001E29C(s32 arg0);

#if 1
GLOBAL_ASM("asm/non_matchings/menu/menu_trophy_race_round_init.s")
#else
void menu_trophy_race_round_init(void) {
    s32 temp;
    s32 i;
    Settings *settings;
    s8 *temp_t9;

    settings = get_settings();
    temp_t9 = func_8001E29C(0x1A); // Returns level ids array.
    
    if (D_800E0FEC == 0) {
        for(i = 0; i < 8; i++) {
            settings->racers[i].trophy_points = 0;
        }
    }
    
    temp = temp_t9[((gTrophyRaceWorldId - 1) * 6) + D_800E0FEC];
    while(temp == -1) {
        temp = (temp + 1) & 3;
    }
    
    for(i = 0; i < gNumberOfActivePlayers; i++){
        gPlayerSelectVehicle[i] = func_8006B0AC(temp);
    }
    
    func_8006DB14(func_8006B0AC(temp));
    func_8006E2E8(temp, -1, 1);
    
    gMenuDelay = 0;
    D_800E0980 = 10;
    func_800C4170(2);
    func_80000BE0(0x18);
    play_music(0x18);
    func_80000C98(0x100);
}
#endif

void func_800983C0(s32 arg0) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s8* sp20;

    sp20 = func_8001E29C(0x1A);
    if (osTvType == 0) {
        sp2C = 0x12;
    } else {
        sp2C = 0;
    }
    
    sp28 = func_8006BDDC(func_8006B1D4(gTrophyRaceWorldId));
    sp24 = func_8006BDDC(sp20[((gTrophyRaceWorldId - 1) * 6) + D_800E0FEC]);
    set_text_background_color(0, 0, 0, 0);
    set_text_font(2);
    set_text_color(0, 0, 0, 0xFF, 0x80);
    draw_text(&D_801263A0, 0xA1, 0x23, sp28, 0xC);
    draw_text(&D_801263A0, 0xA1, 0x43, D_800DF4A0->unk118, 0xC);
    set_text_color(0xFF, 0xFF, 0xFF, 0, 0xFF);
    draw_text(&D_801263A0, 0xA0, 0x20, sp28, 0xC);
    draw_text(&D_801263A0, 0xA0, 0x40, D_800DF4A0->unk118, 0xC);
    draw_text(&D_801263A0, 0xA0, sp2C + 0xB0, D_800DF4A0->unk228[D_800E0FEC], 0xC);
    draw_text(&D_801263A0, 0xA0, sp2C + 0xD0, sp24, 0xC);
}

GLOBAL_ASM("asm/non_matchings/menu/menu_trophy_race_round_loop.s")

void func_80098754(void) {
    func_800C422C(2);
}

GLOBAL_ASM("asm/non_matchings/menu/func_80098774.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_trophy_race_rankings_init.s")

#if 1
GLOBAL_ASM("asm/non_matchings/menu/func_80098EBC.s")
#else
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
        
        D_800E1048+64[i][0].filterRed = fade;
        D_800E1048+64[i][0].filterGreen = fade;
        D_800E1048+64[i][0].filterBlue = fade;
    }
    
    if (D_801263E0 == 2 || D_801263E0 == 3) {
        draw_menu_element(1, &D_800E1048, 1.0f);
    }
}
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
GLOBAL_ASM("asm/non_matchings/menu/menu_ghost_data_init.s")
GLOBAL_ASM("asm/non_matchings/menu/func_80099E8C.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_ghost_data_loop.s")

void func_8009ABAC(void) {
    func_8009C4A8(D_800E1708);
    func_800C422C(2);
}

void func_8009ABD8(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 phi_v1;
    
    phi_v1 = 0;
    while(phi_v1 < arg1) {
        phi_v1++;
        while (-1 != *arg0) {
            arg0 += 3;
        }
        arg0++;
    }
    
    if ((phi_v1 == 0) && (func_8001E29C(0x19) == arg0)) {
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
    func_8006E2E8(D_801267EC[0], D_801267EC[1], D_801267EC[2]);
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
    func_80077B5C(0, 0, 0);
    if (osTvType == 0) {
        func_80066940(0, 0, 0x26, 0x140, 0xE0);
        func_80066AA8(0, 0x8000, 0x8000, 0x140, 0x11C);
    } else {
        func_80066940(0, 0, 0x28, 0x140, 0xC4);
        func_80066AA8(0, 0x8000, 0x8000, 0x140, 0xF0);
    }
    func_80066610();
    func_80066818(0, 1);
    func_8009C674(D_800E17D8);
    func_8009C8A4(D_800E17F0);
    func_80094604();
    func_800C4170(2);
    func_80000BE0(0x18);
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
        while(cheat != 0) {
            cheat >>= 1;
            cheatIndex++;
        }
        
        // The first u16 of gCheatsAssetData is the total number of cheats. 
        // After that is the offsets to the cheat strings.
        cheatOffsets = *gCheatsAssetData + 1; 
        gCreditsArray[85] = (char*)(*gCheatsAssetData) + (cheatOffsets)[(cheatIndex << 1) + 1]; // Cheat name
        gCreditsArray[86] = (char*)(*gCheatsAssetData) + (cheatOffsets)[(cheatIndex << 1)]; // Cheat code
    }
    func_80000B18();
    func_800C0170();
    func_8006F564(1);
}

GLOBAL_ASM("asm/non_matchings/menu/func_8009B1E4.s")
GLOBAL_ASM("asm/non_matchings/menu/menu_credits_loop.s")

void func_8009BCF0(void) {
    func_80000BE0(0x12);
    func_800C0180();
    func_80066894(0, 0);
    func_80066AA8(0, 0x8000, 0x8000, 0x8000, 0x8000);
    func_8009C4A8(D_800E17D8);
    func_800C422C(2);
    func_8006F564(0);
}

/* Unknown size */
typedef struct unk80069D20 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[6];
    f32 unkC;
    f32 unk10;
    f32 unk14;
} unk80069D20;

void func_8001D5E0(f32 arg0, f32 arg1, f32 arg2);

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
    
    temp_v0 = (unk80069D20*)func_80069D20();
    
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
    for(i = 0; i < 4; i++) {
        gControllersXAxisDirection[i] = 0;
        gControllersYAxisDirection[i] = 0;
        gControllersXAxisDelay[i] = 0;
        gControllersYAxisDelay[i] = 0;
        gControllersXAxis[i] = 0;
        gControllersYAxis[i] = 0;
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_8009BF20.s")

/**
 * Reset the character id number slots to the default.
 */
void reset_character_id_slots(void) {
    s32 i;
    gTrackSelectRow = 1; // 1 = Dino Domain
    for(i = 0; i < 8; i++) {
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

s8* func_8009C274(void) {
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
#define CHEATS_ALLOWED_IN_CHALLENGES ~(CHEAT_START_WITH_10_BANANAS | CHEAT_DISABLE_BANANAS |      \
    CHEAT_DISABLE_WEAPONS | CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN |           \
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

typedef struct unk8006BDB0 {
    u8 pad[0x4C];
    s8 unk4C;
} unk8006BDB0;

s32 func_8009C3D8(void) {
    unk8006BDB0 *temp = (unk8006BDB0*)get_current_level_header(); 
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

Settings** func_8009C490(void) {
    return (Settings**)D_80126530;
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

void func_8007B2BC(u32 arg0);
void func_8007CCB0(u32 arg0);
void particlePtrList_addObject(u32 arg0);
void func_8005FF40(u32 arg0);

void func_8009C508(s32 arg0) {
    if (D_80126750[arg0] != 0) {
        if (D_80126550[arg0] != 0) {
            if ((((*D_800DF750)[arg0] & 0xC000) == 0xC000) && (D_80126550[arg0] != 0)) {
                set_free_queue_state(0);
                func_8007B2BC((u32)D_80126550[arg0]);
                set_free_queue_state(2);
            } else {
                if ((*D_800DF750)[arg0] & 0x8000) {
                    func_8007CCB0((u32)D_80126550[arg0]);
                } else {
                    if ((*D_800DF750)[arg0] & 0x4000) {
                        particlePtrList_addObject((u32)D_80126550[arg0]);
                    } else {
                        func_8005FF40((u32)D_80126550[arg0]);
                    }
                }
            }
        }
        D_80126550[arg0] = 0;
        D_80126750[arg0] = 0;
        D_800DF758--;
        particlePtrList_flush();
    }
    if (D_800DF758 == 0) {
        if (D_800DF75C != NULL) {
            free_from_memory_pool(D_800DF75C);
            D_800DF75C = NULL;
        }
        if (*D_800DF750 != NULL) {
            free_from_memory_pool(*D_800DF750);
            *D_800DF750 = NULL;
            D_800DF754 = (u16)0;
        }
    }
}

void func_8009C674(s16 *arg0) {
    s32 index = 0;
    while (arg0[index] != -1) {
        func_8009C6D4(arg0[index++]);
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_8009C6D4.s")

void func_8009C904(s32 arg0);

void func_8009C8A4(s16 *arg0) {
    s32 index = 0;
    while (arg0[index] != -1) {
        func_8009C904(arg0[index++]);
    }
}

s32 get_random_number_from_range(s32, s32);
void func_8009C904(s32 arg0) {
    if (D_800DF75C == NULL) {
        D_800DF75C = allocate_from_main_pool_safe(sizeof(unk800DF510) * 18, COLOR_TAG_RED);
    }
    
    D_800DF75C[arg0].unk0 = D_800DF510[arg0].unk0;
    D_800DF75C[arg0].unk2 = D_800DF510[arg0].unk2;
    D_800DF75C[arg0].unk4 = D_800DF510[arg0].unk4;
    D_800DF75C[arg0].unk6 = D_800DF510[arg0].unk6;
    D_800DF75C[arg0].unkC = D_800DF510[arg0].unkC;
    D_800DF75C[arg0].unk10 = D_800DF510[arg0].unk10;
    D_800DF75C[arg0].unk14 = D_800DF510[arg0].unk14;
    D_800DF75C[arg0].unk8 = D_800DF510[arg0].unk8;
    D_800DF75C[arg0].unk18 = D_800DF510[arg0].unk18;
    D_800DF75C[arg0].unk1A = get_random_number_from_range(0, 0xFFFF);
    D_800DF75C[arg0].unk1B = get_random_number_from_range(0, 0xFFFF);
    D_800DF75C[arg0].unk1C = get_random_number_from_range(0, 0xFFFF);
    D_800DF75C[arg0].unk1D = D_800DF510[arg0].unk1D;
}

void func_8009CA58(void) {
}

GLOBAL_ASM("asm/non_matchings/menu/func_8009CA60.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8009CD7C.s")

void func_8009CF68(s32 arg0) {
    if (D_800DF4E4[arg0] == 0) {
        if (arg0 != 3) {
            D_801264E2 = 0;
            D_801264D8 = 0;
        }
        D_800DF4E0 = 1;
        D_800DF4E4[arg0] = 1;
    }
}

void func_8009CFB0(void) {
    if (D_800DF4E0 != 0) {
        D_800DF4E0 = 0;
        func_800C5620(1);
        reset_controller_sticks();
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_8009CFEC.s")

void func_8009D118(s32 arg0) {
    if (arg0 == 0) {
        func_800C5000(1, 0, 0, 0x7F, 0x5A, 0xFF);
        if (D_800DF4EC != 0) {
            func_800C5000(1, 0, 0, 0x7F, 0x5A, 0x78);
        }
    } else {
        func_800C5000(1, 0xCF, 0xCF, 0xCF, 0x5A, 0xFF);
    }
    D_800DF4EC = (u8)0;
}

void func_8009D1B8(s32 arg0, s32 arg1, s32 arg2) {
    func_8009D118(D_801264D8 == D_80126504);
    if (D_801264D8 == D_80126504) {
        D_80126516 = arg2;
    }
    func_800C5168(1, -0x8000, D_8012650E, arg0, 1, 4);
    D_8012650E = (s8) (D_8012650E + arg1);
    D_80126504 = (s8) (D_80126504 + 1);
}

void func_8009D26C(void) {
    if (gControllersYAxisDirection[0] < 0) {
        D_801264D8 = D_801264D8 + 1;
        func_80001D04(0xB2, NULL);
    } else if (gControllersYAxisDirection[0] > 0) {
        D_801264D8 = D_801264D8 - 1;
        func_80001D04(0xB2, NULL);
    }
    
    if (D_801264D8 < 0) {
        D_801264D8 = D_80126504 - 1;
    }
    
    if (D_801264D8 >= D_80126504) {
        D_801264D8 = 0;
    }
}

void func_8009D324(void) {
    D_800DF4D8 = 0;
}

void func_8009D330(s32 arg0) {
    D_800DF4DC = arg0;
}

void func_8009D33C(s32 arg0, s32 arg1) {
    if (D_801264E2 == arg0) {
        D_801264E2 = arg1;
    }
}

GLOBAL_ASM("asm/non_matchings/menu/func_8009D360.s")

s32 func_8009D9F4(void) {
    s32 state;
    s32 playerInput;

    func_800C4EDC(1, 0x18, 0x10, 0xB8, 0x87);
    func_800C4F7C(1, 0);
    state = 0;
    playerInput = get_button_inputs_from_player(0);
    D_80126504 = 0;
    D_800DF4DC = 0;
    func_800C5168(1, -0x8000, 6, D_800DF4A0->unkC4, 1, 4);
    func_800C5168(1, -0x8000, 0x14, D_800DF4A0->unkC8, 1, 4);
    D_8012650E = 0x32;
    func_8009D1B8(D_800DF4A0->unk5C, 0x14, 0);
    func_8009D1B8(D_800DF4A0->unkCC, 0x14, 1);
    func_8009D26C();
    if (playerInput & 0x8000) {
        func_80001D04(0xEF, NULL);
        switch(D_80126516) {
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

GLOBAL_ASM("asm/non_matchings/menu/func_8009DB3C.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8009E3D0.s")
GLOBAL_ASM("asm/non_matchings/menu/func_8009E7E8.s")

void func_8009E9A0(void) {

}

void func_8009E9A8(void) {

}

f32 func_8009E9B0(s32 arg0, Gfx **arg1, s32 *arg2, s32 *arg3) {
    D_801263A0 = *arg1;
    D_801263A8 = *arg2;
    D_801263AC = *arg3;
    func_80067F2C(&D_801263A0, &D_801263A8);
    if (D_800E1E28 != 0 && D_801264E2 == 4) {
        func_8009E3D0();
    }
    *arg1 = D_801263A0;
    *arg2 = D_801263A8;
    *arg3 = D_801263AC;
    return 1.0f;
}

s64* func_8009EA6C(void) {
    return &D_80126448;
}

s32 func_8009EA78(s64 arg0) {
    D_80126448 |= arg0;
    func_8006ECE0();
    return 1;
}

s32 func_8009EABC(s64 arg0) {
    D_80126448 &= ~arg0;
    func_8006ECE0();
    return 1;
}

s64 func_8009EB08(void) {
    return D_80126448;
}

/**
 * Returns the current language being used by the game.
 * 0 = English, 1 = German, 2 = French, 3 = Japanese
 */
s32 get_language(void) {
    s32 language = 0; // English
    switch(D_80126448 & 0xC) {
        case 4: // German
            language = 1;
            break;
        case 8: // French
            language = 2;
            break;
        case 12: // "Japanese"
            language = 3;
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
    s64 langFlag = 0; // English
    
    switch(language) {
        case 1: // German
            langFlag = 4;
            break;
        case 2: // French
            langFlag = 8;
            break;
        case 3: // "Japanese"
            langFlag = 12;
            break;
    }
    
    D_80126448 &= ~0xC;
    D_80126448 |= langFlag;
    
    func_8007F900();
    func_8006ECE0();
}

s32 func_8009EC60(void) {
    return D_80126448 & 1;
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
        return 0;
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
