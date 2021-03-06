#ifndef _UNKNOWN_080500_H_
#define _UNKNOWN_080500_H_

#include "types.h"
#include "structs.h"

#define CHEAT(index) 1 << index

typedef enum Cheats {
    CHEAT_CONTROL_TT               = CHEAT(0),
    CHEAT_CONTROL_DRUMSTICK        = CHEAT(1),
    CHEAT_MIRRORED_TRACKS          = CHEAT(2),
    CHEAT_HIGH_SPEED_RACING        = CHEAT(3),
    CHEAT_BIG_CHARACTERS           = CHEAT(4),
    CHEAT_SMALL_CHARACTERS         = CHEAT(5),
    CHEAT_MUSIC_MENU               = CHEAT(6),
    CHEAT_START_WITH_10_BANANAS    = CHEAT(7),
    CHEAT_HORN_CHEAT               = CHEAT(8),
    CHEAT_PRINT_COORDS             = CHEAT(9),
    CHEAT_DISPLAY_CREDITS          = CHEAT(10),
    CHEAT_DISABLE_WEAPONS          = CHEAT(11),
    CHEAT_DISABLE_BANANAS          = CHEAT(12),
    CHEAT_BANANAS_REDUCE_SPEED     = CHEAT(13),
    CHEAT_NO_LIMIT_TO_BANANAS      = CHEAT(14),
    CHEAT_ALL_BALLOONS_ARE_RED     = CHEAT(15),
    CHEAT_ALL_BALLOONS_ARE_GREEN   = CHEAT(16),
    CHEAT_ALL_BALLOONS_ARE_BLUE    = CHEAT(17),
    CHEAT_ALL_BALLOONS_ARE_YELLOW  = CHEAT(18),
    CHEAT_ALL_BALLOONS_ARE_RAINBOW = CHEAT(19),
    CHEAT_MAXIMUM_POWER_UP         = CHEAT(20),
    CHEAT_TURN_OFF_ZIPPERS         = CHEAT(21),
    CHEAT_SELECT_SAME_PLAYER       = CHEAT(22),
    CHEAT_FOUR_WHEEL_DRIVER        = CHEAT(23),
    CHEAT_TWO_PLAYER_ADVENTURE     = CHEAT(24),
    CHEAT_ULTIMATE_AI              = CHEAT(25),
    CHEAT_FREE_BALLOON             = CHEAT(26),
    CHEAT_EPC_LOCK_UP_DISPLAY      = CHEAT(27),
    CHEAT_ROM_CHECKSUM             = CHEAT(28)
} Cheats;

typedef enum MENU_ID {
    MENU_TITLE,
    MENU_LOGOS,
    MENU_UNUSED_2,
    MENU_CHARACTER_SELECT,
    MENU_UNUSED_4,
    MENU_UNKNOWN_5,
    MENU_FILE_SELECT,
    MENU_UNUSED_7,
    MENU_UNUSED_8,
    MENU_UNUSED_9,
    MENU_MAGIC_CODES,
    MENU_MAGIC_CODES_LIST,
    MENU_OPTIONS,
    MENU_AUDIO_OPTIONS,
    MENU_SAVE_OPTIONS,
    MENU_TRACK_SELECT,
    MENU_UNUSED_16,
    MENU_RESULTS,
    MENU_UNUSED_18,
    MENU_GAME_SELECT,
    MENU_TROPHY_RACE_ROUND,
    MENU_TROPHY_RACE_RANKINGS,
    MENU_UNUSED_22,
    MENU_UNKNOWN_23,
    MENU_GHOST_DATA,
    MENU_CREDITS,
    MENU_BOOT,
    MENU_UNUSED_27,
    MENU_CAUTION
} MENU_ID;

extern s8  D_800DF450;
extern f32 D_800DF454;
extern s32 D_800DF458;
extern s32 gTitleScreenCurrentOption;
extern s32 D_800DF460;
extern s32 D_800DF464;
extern s32 D_800DF468;
extern s32 D_800DF46C;
extern s32 gCurrentMenuId;
extern s32 D_800DF474;
extern s32 D_800DF478;
extern s32 gMenuDelay;
extern s32 gNumberOfReadyPlayers;
extern s32 D_800DF484;
extern s32 D_800DF488;
extern s32 D_800DF48C;
extern s32 D_800DF490;
extern s32 gIsInAdventureTwo;
extern s32 gPlayerHasSeenCautionMenu;
extern s32 D_800DF49C;

typedef struct unk800DF4A0 {
    u8  pad0[0x5C];
    s32 unk5C;
    s32 unk60;
    u8  unk64[0xC];
    s32 unk70;
    u8  pad74[0x1C];
    s32 unk90;
    u8  pad94[0x30];
    s32 unkC4;
    s32 unkC8;
    s32 unkCC;
    u8  padD0[0x48];
    s32 unk118;
    u8  pad11C[0x100];
    s32 unk21C;
    u8  pad220[0x8];
    s32 unk228[4];
    u8  pad238[0x24];
    s32 unk25C;
    u8  pad260[0x78];
    s32 unk2D8;
    s32 unk2DC;
} unk800DF4A0;

extern unk800DF4A0* D_800DF4A0;

extern u8 D_800DF4A4;
extern u8 D_800DF4A8;
extern u8 D_800DF4AC;

extern s32 D_800DF4B0;
extern s32 D_800DF4B4;
extern s32 gIsInTracksMode;
extern s32 gNumberOfActivePlayers;
extern s32 gIsInTwoPlayerAdventure;
extern s32 gTrackIdForPreview;
extern s32 gTrackSelectRow;
extern s32 gSaveFileIndex;

extern s32 D_800DF4D0;
extern s32 gTrackIdToLoad;
extern s8 D_800DF4D8;
extern s8 D_800DF4DC;
extern s8 D_800DF4E0;
extern s8 D_800DF4E4[4];
extern s32 D_800DF4E8;
extern s8 D_800DF4EC;

// Unused?
extern s32 D_800DF4F0[];

/* Size: 0x20 bytes */
typedef struct unk800DF510 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s8  unk1A;
    s8  unk1B;
    s8  unk1C;
    s8  unk1D;
    u8  pad1E[2];
} unk800DF510;

extern unk800DF510 D_800DF510[18];

extern s16 *D_800DF750[1];
extern s16 D_800DF754;
extern s16 D_800DF758;
extern unk800DF510 *D_800DF75C;

extern s32 D_800DF760;
extern s32 D_800DF764;
extern s32 D_800DF768;

// Not sure about typing with these arrays.
extern s16 D_800DF76C[4];
extern s16 D_800DF774[4];
extern u16 D_800DF77C[12];

extern s32 D_800DF794;
extern s32 D_800DF798;
extern s32 D_800DF79C;

extern s32 D_800DF7A0;
extern s32 D_800DF7A4;
extern s32 D_800DF7A8;
extern s32 D_800DF7AC;

// Version text shown on the title screen? See 1:15 in https://www.youtube.com/watch?v=OHSCLcA74ao.
extern char gVersionDisplayText[20];

// Probably not unqiue to the boot menu.
typedef struct MenuBootDrawTexture {
    u32* texture; // Pointer to texture to draw. TODO: Make structure for texture header.
    s16 xOffset; // Offset from the center of the screen.
    s16 yOffset; // Offset from the center of the screen.
} MenuBootDrawTexture;

extern s16 D_800DF7C4[12];

extern MenuBootDrawTexture D_800DF7DC[12];

/* Size: 0x30 bytes */
typedef struct unk800DF83C {
    char* unk0; // Pointer to ascii text.
    f32  unk4;
    f32  unk8;
    f32  unkC;
    f32  unk10;
    f32  unk14;
    f32  unk18;
    f32  unk1C;
    f32  unk20;
    f32  unk24;
    f32  unk28;
} unk800DF83C;

// Title screen cinematic text
extern unk800DF83C D_800DF83C[10];

extern s32 D_800DF9F4;

extern u16 D_800DF9F8[12];

extern char *D_800DFA10[7];

extern s16 D_800DFA2C[8];

typedef struct unk800DFA3C {
    s16 unk0;
    s16 unk2;
    u8  unk4;
    u8  unk5;
    u8  unk6;
    u8  unk7;
    u8  unk8;
    u8  unk9;
    u8  unkA;
    u8  unkB;
    u32* unkC;
} unk800DFA3C;

extern unk800DFA3C D_800DFA3C[8];

extern s32 D_800DFABC;

extern s32 gSfxVolumeSliderValue;
extern s32 gMusicVolumeSliderValue;
extern s32 D_800DFAC8;

// Unsure about typing here.
extern u16 D_800DFACC[8];

extern s32 D_800DFADC;
extern s32 D_800DFAE0;


// Unsure about typing with these arrays.
extern s32 D_800DFAE4[6];
extern s32 D_800DFAFC[6];
extern s32 D_800DFB14[6];
extern s32 D_800DFB2C[5];
extern s32 D_800DFB40[7];
extern s32 D_800DFB5C[6];
extern s32 D_800DFB74[6];
extern s32 D_800DFB8C[6];
extern s32 D_800DFBA4[6];
extern s32 D_800DFBBC[8];
extern s32 D_800DFBDC;

// Unused?
extern s32* D_800DFBE0[10];

extern s32 D_800DFC08;
extern s32 D_800DFC0C;

typedef struct unk800DFC10 {
    u32 *unk0;
    s16 unk4;
    s16 unk6;
    u32 *unk8;
    s32 unkC;
} unk800DFC10;

extern unk800DFC10 D_800DFC10;
extern unk800DFC10 D_800DFC20;
extern unk800DFC10 D_800DFC30;
extern unk800DFC10 D_800DFC40;
extern unk800DFC10 D_800DFC50;
extern unk800DFC10 D_800DFC60;

// Unused?
extern u8 D_800DFC70[8];

extern s16 D_800DFC78[26];

extern s16 D_800DFCAC[4];

extern u16 D_800DFCB4[112];

extern s32 D_800DFD94;

extern s32 gActiveMagicCodes;
extern s32 gUnlockedMagicCodes;

extern s32 D_800DFDA0[5];

extern u8 D_800DFDB4[10][2];

extern s16 D_800DFDC8[2];
extern s16 D_800DFDCC[2];

// Not sure what this is
extern s32 D_800DFDD0[28];

// Not sure what this is
extern s32 D_800DFE40[32];

// Not sure what this is
extern s32 D_800DFEC0[32];

// Not sure what this is
extern s32 D_800DFF40[36];

extern s32 D_800DFFD0;
extern s32 D_800DFFD4;

extern MenuElement D_800DFFD8[14];
                                                                             
extern MenuElement D_800E0198[7];
                                                                        
extern MenuElement D_800E0278[9];

extern s16 D_800E0398[6];

extern s16 D_800E03A4[6];

extern u16 D_800E03B0[14];

extern u16 D_800E03CC[24];

extern u16 D_800E03FC[10];

extern s32 gMultiplayerSelectedNumberOfRacers;
extern s32 D_800E0414;
extern s32 D_800E0418;

extern unk800DFC10 D_800E041C;
extern unk800DFC10 D_800E042C;
extern unk800DFC10 D_800E043C;
extern unk800DFC10 D_800E044C;

extern unk800DFC10 D_800E045C;
extern s32 D_800E046C[2];
extern unk800DFC10 D_800E0474;
extern s32 D_800E0484[2];
extern unk800DFC10 D_800E048C;
extern s32 D_800E049C[2];
extern unk800DFC10 D_800E04A4;
extern s32 D_800E04B4[2];
extern unk800DFC10 D_800E04BC;
extern s32 D_800E04CC[2];
extern unk800DFC10 D_800E04D4;
extern unk800DFC10 D_800E04E4;
extern unk800DFC10 D_800E04F4;
extern unk800DFC10 D_800E0504;
extern unk800DFC10 D_800E0514;
extern unk800DFC10 D_800E0524;
extern unk800DFC10 D_800E0534;
extern unk800DFC10 D_800E0544;
extern unk800DFC10 D_800E0554;
extern unk800DFC10 D_800E0564;
extern unk800DFC10 D_800E0574;
extern unk800DFC10 D_800E0584;
extern unk800DFC10 D_800E0594;
extern unk800DFC10 D_800E05A4;
extern unk800DFC10 D_800E05B4;
extern unk800DFC10 D_800E05C4;

// These are probably structs
extern s32 D_800E05D4[8];
extern s32 D_800E05F4[8];

extern unk800DFC10 D_800E0614;

extern unk800DFC10 *D_800E0624[9];

extern unk800DFC10 *D_800E0648[6];

extern unk800DFC10 *D_800E0660[6];

extern unk800DFC10 *D_800E0678[4];

extern u16 D_800E0688[20];

extern u16 D_800E06B0[10];

extern s16 D_800E06C4[8];

extern s16 D_800E06D4[8];

extern u16 D_800E06E4[14];

extern u16 D_800E0700[8];

extern s16 D_800E0710[16];

extern s16 D_800E0730[19];
extern s16 D_800E0758[54];

extern s16 D_800E07C4[14];

extern s16 D_800E07E0[4];

extern s16 D_800E07E8[36];

extern s16 D_800E0830[8];

extern s16 D_800E0840[148];

extern s32 D_800E0968;
extern s32 D_800E096C;
extern s32 D_800E0970;
extern s32 D_800E0974;
extern f32* D_800E0978;
extern s32 D_800E097C;
extern s32 D_800E0980;
extern s32 D_800E0984;
extern s32 D_800E0988;
extern s32 D_800E098C;

extern s16 D_800E0990[8];

extern s16 D_800E09A0[8];

// Not sure about typing with these.
extern s32 D_800E09B0[5];
extern s32 D_800E09C4[5];
extern s32 D_800E09D8[5];
extern s32 D_800E09EC[3];
extern s32 D_800E09F8[3];
extern s32 D_800E0A04[3];
extern s32 D_800E0A10;
extern s32 D_800E0A14[4];

extern s16 D_800E0A24[14];

extern s16 D_800E0A40[8];

extern unk800DFC10 D_800E0A50;
extern unk800DFC10 D_800E0A60;
extern unk800DFC10 D_800E0A70;
extern unk800DFC10 D_800E0A90;
extern unk800DFC10 D_800E0A80;
extern unk800DFC10 D_800E0AA0;
extern unk800DFC10 D_800E0AB0;
extern unk800DFC10 D_800E0AC0;
extern unk800DFC10 D_800E0AD0;
extern unk800DFC10 D_800E0AE0;

extern unk800DFC10* D_800E0AF0[10];

extern s16 D_800E0B18[74];

extern char gFirstPlace[4];
extern char gSecondPlace[4];
extern char gThirdPlace[4];
extern char gFourthPlace[4];
extern char gFifthPlace[4];
extern char gSixthPlace[4];
extern char gSeventhPlace[4];
extern char gEighthPlace[4];

extern char *gRacePlacementsArray[8];

extern MenuElement D_800E0BEC[8];

extern MenuElement D_800E0CEC[11];

extern MenuElement D_800E0E4C[9];

// Valid characters for name input. Must be u8, not char.
extern u8 gFileNameValidChars[32];

extern s32 D_800E0F8C;
extern s32 D_800E0F90;
extern s32 D_800E0F94;
extern s32 D_800E0F98;
extern s32 D_800E0F9C;
extern s32 D_800E0FA0;
extern s32 D_800E0FA4;
extern char D_800E0FA8[4];
extern s32 D_800E0FAC;
extern s32 D_800E0FB0;

extern s16 D_800E0FB4[18];

extern s16 D_800E0FD8[6];

extern s32 D_800E0FE4;
extern s32 gTrophyRaceWorldId;
extern s32 D_800E0FEC;
extern s32 D_800E0FF0;

// Unused? Not sure what this is.
extern u32 D_800E0FF4[4];

// Number of points to award in trophy race for each place?
extern s32 gTrophyRacePointsArray[8];

extern s16 D_800E1024[14];

extern s32 D_800E1040;
extern s16 D_800E1044;

extern MenuElement D_800E1048[9][3];

extern s16 D_800E13A8[138];

extern s16* D_800E14BC[32];

// Not sure what these arrays are supposed to be
extern s32 D_800E153C[10];
extern s32 D_800E1564[12];
extern s32 D_800E1594[10];
extern s32 D_800E15BC[12];
extern s32 D_800E15EC[10];
extern s32 D_800E1614[12];
extern s32 D_800E1644[10];
extern s32 D_800E166C[12];
extern s32 D_800E169C[10];
extern s32 D_800E16C4[12];

extern s32 *D_800E16F4[5];

extern s16 D_800E1708[34];

extern s16 D_800E174C[4];

extern s16 D_800E1754[10];

extern s16 D_800E1768[12];

//extern u32 D_800E1780[22];

extern s16 D_800E17D8[12];

extern s16 D_800E17F0[2];

extern s16 D_800E17F4[130];

extern u16 D_800E18F8;

// Unused?
extern u16 D_800E18FC[30];

// Credits text look-up table
extern char *gCreditsArray[87];

// Credits text look-up table (time trials time sheet)
extern char *gCreditsBestTimesArray[20];

// Another credits text look-up table
extern char *gCreditsLastMessageArray[5];

extern s32 gCheatsInCreditsArray[21];

extern s32 gViewingCreditsFromCheat;

extern MenuElement D_800E1B50[9];

//extern u32 D_800E1C70[24];

extern s8 D_800E1CD0[32];

extern s8 D_800E1CF0[60];

extern u16 D_800E1D2C[40];

extern s16 D_800E1D7C[20];

extern s32 *D_800E1DA4[2];

extern s32 *D_800E1DAC[2];

extern s32 D_800E1DB4;
extern s32 D_800E1DB8;
extern s32 D_800E1DBC;

extern s32 D_800E1DC0;
extern s32 D_800E1DC4;

extern s16 D_800E1DC8[16];

extern s16 D_800E1DE8[4];

extern char gRareCopyrightString[24];

extern s16 D_800E1E08[4];

extern s32 *D_800E1E10;

extern s32 D_800E1E14;
extern s32 D_800E1E18;
extern s32 D_800E1E1C;

extern s8 D_800E1E20[8];

extern s8 D_800E1E28;

extern s16 D_800E1E2C[10];

extern s16 D_800E1E40[10];

#endif
