#ifndef _MENU_H_
#define _MENU_H_

#include "types.h"
#include "structs.h"
#include "PR/gbi.h"
#include "fade_transition.h"
#include "font.h"

#define TT_MENU_ROOT              0
#define TT_MENU_CONT_PAK_ERROR_1  1
#define TT_MENU_CONT_PAK_ERROR_2  2
#define TT_MENU_CONT_PAK_ERROR_3  3
#define TT_MENU_GAME_STATUS       4
#define TT_MENU_INTRODUCTION      5
#define TT_MENU_INSERT_CONT_PAK   6
#define TT_MENU_INSERT_RUMBLE_PAK 7
#define TT_MENU_SAVE_GHOST        8
#define TT_MENU_EXIT              10

enum DialogueMenuCases {
    DIALOG_TAJ,
    DIALOG_UNK_01,
    DIALOG_TT,
    DIALOG_CHALLENGE,
    DIALOG_TROPHY,
    DIALOG_RACERESULT,
};

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

enum Language {
    ENGLISH,
    GERMAN,
    FRENCH,
    JAPANESE
};

/* Size: 0x20 bytes */
// So this is looking to be a struct for menu images.
typedef struct unk800DF510 {
    s16 unk0; //X1
    s16 unk2; //Y1
    s16 unk4;
    s16 unk6;
    f32 unk8;
    f32 unkC; // X offset
    f32 unk10; // Y offset
    f32 unk14;
    s16 unk18;
    s8  unk1A;
    s8  unk1B;
    s8  unk1C;
    s8  unk1D;
    u8  pad1E[2];
} unk800DF510;

typedef struct unk80126460 {
    MenuElement elem[2];
} unk80126460;

typedef struct unk801263C0 {
    s8 unk0;
    s8 unk1;
    s16 unk2;
} unk801263C0;

/* Size: 0x30 bytes */
typedef struct unk800DF83C {
    char *unk0; // Pointer to ascii text.
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

typedef struct unk800DFC10 {
    u32 *unk0;
    s16 unk4;
    s16 unk6;
    u32 *unk8;
    s32 unkC;
} unk800DFC10;

typedef struct unk800E03CC {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} unk800E03CC;

/* Size: 0xE bytes. */
typedef struct unk801263CC {
    u8 pad0[0xC];
    s16 unkC;
} unk801263CC;

/* Size: 0x0C Bytes */
typedef struct SavefileInfo {
    u8 isAdventure2;
    u8 isStarted;
    u16 balloonCount;
    char name[4];
    u32 pad8;
} SavefileInfo;

typedef struct unk800E153C {
    TextureHeader *texture;
    u32 unk4; // Flags?
} unk800E153C;

/* Size: 0x10 Bytes */
typedef struct unk800860A8 {
    s8 unk0;
    u8 pad1[0x5];
    s8 unk6;
    u8 pad7[0x5];
    s32 unkC;
} unk800860A8;

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

typedef struct unk8006BDB0 {
    u8 pad[0x4C];
    s8 unk4C;
} unk8006BDB0;

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
extern s32 *gMenuTextLangTable;

extern char **gMenuText;

extern u8 sMenuGuiColourR;
extern u8 sMenuGuiColourG;
extern u8 sMenuGuiColourB;

extern u8 D_800DF4B0;
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
extern s8 gDialogOptionTangible;

// Unused?
extern s32 D_800DF4F0[];

extern unk800DF510 sMenuImageProperties[18];

extern s16 *D_800DF750[1];
extern s16 D_800DF754;
extern s16 D_800DF758;
extern unk800DF510 *gMenuImageStack;

extern s32 sMenuMusicVolume;
extern s32 sMenuGuiOpacity;
extern s32 D_800DF768;

extern s32 D_800DF794;
extern s32 D_800DF798;
extern s32 D_800DF79C;

extern s32 D_800DF7A0;
extern char *gTitleMenuStrings[3];

// Version text shown on the title screen? See 1:15 in https://www.youtube.com/watch?v=OHSCLcA74ao.
extern char gVersionDisplayText[20];

extern s16 sGameTitleTileTextures[12];

extern DrawTexture sGameTitleTileOffsets[12];

// Title screen cinematic text
extern unk800DF83C D_800DF83C[10];

extern s32 D_800DF9F4;

extern u16 D_800DF9F8[12];

extern char *gOptionMenuStrings[7];

extern s16 gOptionMenuTextures[8];

extern unk800DFA3C gAudioMenuStrings[8];

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

extern s32 gShowControllerPakMenu;

extern s32 gActiveMagicCodes;
extern s32 gUnlockedMagicCodes;

extern char *gMagicCodeMenuStrings[5];

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

extern MenuElement gCautionMenuTextElements[14];

extern MenuElement gGameSelectTextElemsNoAdv2[7];

extern MenuElement gGameSelectTextElemsWithAdv2[9];

extern s16 D_800E0398[6];

extern s16 D_800E03A4[6];

extern unk800E03CC D_800E03CC[3];

extern s16 D_800E03FC[10];

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

extern s16 D_800E06E4[14];

extern s16 D_800E0700[8];

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

//extern u32 dMenuHudSettings[24];

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

extern char gRareCopyrightString[24];

//Probably a FadeTransition
//extern FadeTransition D_800E1E08;
extern s16 D_800E1E08[4];

extern s32 *D_800E1E10;

extern s32 D_800E1E14;
extern s32 D_800E1E18;
extern s32 D_800E1E1C;

extern s8 D_800E1E20[8];

extern s8 D_800E1E28;

extern s16 D_800E1E2C[10];

extern s16 D_800E1E40[10];

s32 get_random_number_from_range(s32, s32); // No file to pull from yet.

void func_8007FF88(void);
void func_80080E6C(void);
void func_800813C0(void);
void menu_init(u32 menuId);
s32 menu_loop(Gfx **arg0, s32 **arg1, s32 **arg2, s32 **arg3, s32 arg4);
void func_80081800(s32 arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6);
void func_80081E54(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5);
void func_800828B8(void);
void print_missing_controller_text(Gfx *dl, s32 updateRate);
void menu_logos_screen_init(void);
s32 menu_logo_screen_loop(s32 arg0);
void init_title_screen_variables(void);
void menu_title_screen_init(void);
void func_80084118(void);
void menu_options_init(void);
void func_800841B8(s32 arg0);
void func_80084734(void);
void menu_audio_options_init(void);
void func_800851FC(void);
void menu_save_options_init(void);
s32 func_800860A8(s32 arg0, s32 *arg1, unk800860A8 *arg2, s32 *arg3, s32 arg4);
void func_800861C8(unk800861C8 *arg0, s32 *arg1);
s32 func_800874D0(s32 arg0, s32 arg1);
s32 func_800875E4(s32 arg0, s32 arg1);
s32 func_800876CC(s32 arg0, s32 arg1);
void func_80087EB8(void);
void menu_boot_init(void);
void func_800887C4(void);
void func_800887E8(void);
void func_800895A4(void);
void func_8008A4C8(void);
void menu_magic_codes_list_init(void);
void func_8008A8F8(s32 arg0, s32 arg1, s32 arg2);
void func_8008AD1C(void);
void func_8008AEB4(s32 arg0, s32 *arg1);
void set_active_player_index(s32 controllerIndex);
void menu_character_select_init(void);
void draw_character_select_text(s32 arg0);
void func_8008BFE8(s32 arg0, s8 *arg1, s32 arg2, u16 arg3, u16 arg4);
void func_8008C128(void);
void menu_caution_init(void);
void unload_large_font(void);
void func_8008CACC(void);
void menu_file_select_init(void);
void render_menu_image(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_8008E428(void);
void func_8008E45C(void);
void func_8008E4B0(void);
void func_8008F534(void);
void func_80090ED8(s32 arg0);
s32 func_80092BE0(s32 arg0);
void menu_5_init(void);
void func_80093A0C(void);
void n_alSynRemovePlayer(void);
void n_alSeqpDelete(void);
void func_80094604(void);
void func_80094C14(s32 arg0);
void func_80096790(void);
void menu_11_init(void);
void func_800976CC(void);
void decompress_filename_string(u32 compressedFilename, char *output, s32 length);
s32 compress_filename_string(unsigned char *filename, s32 length);
void func_80097874(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 arg5, s32 arg6);
void func_800981E8(void);
void func_80098208(void);
void func_800983C0(s32 arg0);
void func_80098754(void);
void func_80099600(void);
s32 get_trophy_race_world_id(void);
void func_8009ABAC(void);
void func_8009ABD8(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void menu_23_init(void);
void func_8009AF18(void);
void menu_credits_init(void);
void func_8009B1E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_8009BCF0(void);
void func_8009BD5C(void);
void func_8009BE54();
void reset_controller_sticks(void);
void reset_character_id_slots(void);
s32 get_save_file_index(void);
s32 get_track_id_to_load(void);
s8 get_character_id_from_slot(s32 slot);
s8 get_character_id_from_slot_unused(s32 slot);
s8 get_player_selected_vehicle(s32 playerNum);
void set_player_selected_vehicle(s32 playerNum, s32 index);
s8 *func_8009C274(void);
s8 get_player_character(s32 controllerIndex);
void enable_tracks_mode(s32 boolean);
s32 is_in_tracks_mode(void);
void set_magic_code_flags(s32 flags);
s32 get_filtered_cheats(void);
s32 get_number_of_active_players(void);
s32 get_active_player_count(void);
s32 get_multiplayer_racer_count(void);
Settings** func_8009C490(void);
void func_8009C49C(void);
void func_8009C4A8(s16 *arg0);
void func_8009C508(s32 arg0);
void func_8009C674(s16 *arg0);
void allocate_menu_images(s16 *imageSet);
void allocate_and_set_menu_image_properties(s32 imageID);
void func_8009CA58(void);
void func_8009CF68(s32 arg0);
void func_8009CFB0(void);
s32 func_8009CFEC(u32 arg0);
void set_option_text_colour(s32 condition);
void render_dialogue_option(char *text, s32 yOffset, s32 optionID);
void handle_menu_joystick_input(void);
void func_8009D324(void);
void func_8009D330(s32 arg0);
void set_menu_id_if_option_equal(s32 IDToCheck, s32 IDToSet);
s32 taj_menu_loop(void);
s32 dialogue_race_defeat(void);
s32 trophy_race_cabinet_menu_loop(void);
void dialogue_open_stub(void);
void dialogue_close_stub(void);
f32 func_8009E9B0(DialogueBoxBackground *arg0, Gfx **dlist, Gfx **mat, VertexList **vtx);
s64 *func_8009EA6C(void);
s32 func_8009EA78(s64 arg0);
s32 func_8009EABC(s64 arg0);
s64 func_8009EB08(void);
s32 get_language(void);
void set_language(s32 language);
s32 is_adventure_two_unlocked(void);
s32 is_in_adventure_two(void);
s32 is_in_two_player_adventure(void);
s32 is_tt_unlocked(void);
s32 is_drumstick_unlocked(void);

// Non Matching functions below here
void load_menu_text(s32 language); // Non Matching
void draw_menu_elements(s32 arg0, MenuElement *elem, f32 arg2);
s32 menu_audio_options_loop(s32 arg0);
s32 menu_options_loop(s32 arg0);
s32 func_800890AC(s32);
s32 menu_boot_loop(s32 arg0);
void menu_magic_codes_init(void);
void render_magic_codes_list_menu_text(s32 arg0);
s32 menu_magic_codes_list_loop(s32 arg0);
void calculate_and_display_rom_checksum(void);
void randomize_ai_racer_slots(s32 arg0);
void menu_game_select_init(void);
void func_8008C698(s32 arg0);
s32 menu_game_select_loop(s32 arg0);
void render_file_select_menu(s32 arg0);
s32 menu_track_select_loop(s32 arg0);
void func_8008FF1C(s32 arg0);
void func_800904E8(s32 arg0);
void func_80090918(s32 arg0);
void render_track_select_setup_ui(s32 arg0);
void func_80092188(s32 arg0);
void func_8008E4EC(void);
s32 menu_5_loop(s32 arg0);
void func_80095624(s32 arg0);
s32 trim_filename_string(u8 *input, u8 *output);
void menu_trophy_race_round_init(void);
void menu_ghost_data_init(void);
s32 menu_ghost_data_loop(s32 arg0);
void update_controller_sticks(void);
s32 tt_menu_loop(void);
void menu_track_select_init(void);
void menu_trophy_race_rankings_init(void);

#endif
