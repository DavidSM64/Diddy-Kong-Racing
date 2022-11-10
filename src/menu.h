#ifndef _MENU_H_
#define _MENU_H_

#include "types.h"
#include "structs.h"
#include "PR/gbi.h"
#include "audio.h"
#include "fade_transition.h"
#include "font.h"
#include "save_data.h"

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
    DIALOG_RACERESULT
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

typedef enum PakError {
    PAK_ERROR_NONE,
    PAK_ERROR_FATAL,
    PAK_ERROR_FULL,
    PAK_ERROR_CORRUPT
} PakError;

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
    union {
        struct {
            s8 unk2a;
            s8 unk3;
        };
        s16 unk2;
    };
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

typedef struct ButtonElement {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 borderWidth; // The glowing border that goes around this button
    s16 borderHeight;
    s16 colourMin; // The border oscillates between two colours in RGBA5551 format.
    s16 colourMax;
} ButtonElement;

typedef struct ButtonTextElement {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 borderWidth;
    s16 borderHeight;
    s16 textPos[8];
} ButtonTextElement;

/* Size: 0xE bytes. */
typedef struct CharacterSelectData {
    u8 upInput[2];
    u8 downInput[2];
    u8 rightInput[4];
    u8 LeftInput[4];
    s16 voiceID;
} CharacterSelectData;

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

/* Size: 0x10 bytes */
typedef struct unk800861C8 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 pad3[0x3];
    u8 controllerIndex;
    u8 pad7[0x5];
    u32 fileSize; // Game Data File Size
} unk800861C8;

/* Size: 0x10 bytes */
typedef struct unk800E0970 {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    s8 pad4[12];
} unk800E0970;

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

typedef struct TitleScreenDemos {
    s8 levelId;
    s8 numberOfPlayers;
    s8 cutsceneId;
} TitleScreenDemos;

#define X_TILE_SIZE 320

/* Size 0x10 bytes */
typedef struct TrackRenderDetails {
  /* 0x00 */ u8 *hubName;
  /* 0x04 */ u8 *trackName;
  /* 0x08 */ s16 xOff;
  /* 0x0A */ s16 yOff;
  /* 0x0C */ u8 visible;
  /* 0x0D */ u8 opacity;
    union {
        struct {
            /* 0x0E */ u8 copyViewPort;
            /* 0x0F */ u8 border;
        };
        /* 0x0E */ u16 viewPort;
    };
} TrackRenderDetails;

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
extern MapId gTrackIdForPreview;
extern s32 gTrackSelectRow;
extern s32 gSaveFileIndex;

extern s32 D_800DF4D0;
extern s32 gTrackIdToLoad;
extern s8 D_800DF4D8;
extern s8 gNextTajChallengeMenu;
extern s8 gNeedToCloseDialogueBox;
extern s8 D_800DF4E4[4];
extern s32 D_800DF4E8;
extern s8 gDialogueOptionTangible;

// Unused?
extern s32 D_800DF4F0[];

extern unk800DF510 sMenuImageProperties[18];

extern s16 *gAssetsMenuElementIds[1];
extern s16 D_800DF754;
extern s16 D_800DF758;
extern unk800DF510 *gMenuImageStack;

extern s32 sMenuMusicVolume;
extern s32 sMenuGuiOpacity;
extern s32 D_800DF768;

extern s32 D_800DF794;
extern MenuElement *D_800DF798;
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
extern char *D_800DFAE4[6];
extern char *D_800DFAFC[6];
extern char *D_800DFB14[6];
extern char *D_800DFB2C[5];
extern char *D_800DFB40[7];
extern char *D_800DFB5C[6];
extern char *D_800DFB74[6];
extern char *D_800DFB8C[6];
extern char *D_800DFBA4[6];
extern char *D_800DFBBC[8];
extern s32 D_800DFBDC;

// Unused?
extern char **D_800DFBE0[10];

extern s32 D_800DFC08;
extern s32 D_800DFC0C;

// Unused?
extern u8 D_800DFC70[8];

extern s16 D_800DFC78[26];

extern MenuElement gControllerPakMenuElement[7];

extern s32 gShowControllerPakMenu;

extern s32 gActiveMagicCodes;
extern s32 gUnlockedMagicCodes;

extern char *gMagicCodeMenuStrings[5];

extern u8 D_800DFDB4[10][2];

extern s16 D_800DFDC8[2];
extern s16 D_800DFDCC[2];

extern s32 D_800DFFD0;
extern s32 D_800DFFD4;

extern MenuElement gCautionMenuTextElements[14];

extern MenuElement gGameSelectTextElemsNoAdv2[7];

extern MenuElement gGameSelectTextElemsWithAdv2[9];

extern s16 D_800E0398[6];

extern s16 D_800E03A4[6];

extern ButtonElement gFileSelectButtons[3];

extern s16 gFileSelectElementPos[10];

extern s32 gMultiplayerSelectedNumberOfRacers;
extern s32 D_800E0414;
extern s32 D_800E0418;

extern DrawTexture gMenuSelectionArrowUp[2];
extern DrawTexture gMenuSelectionArrowLeft[2];
extern DrawTexture gMenuSelectionArrowDown[2];
extern DrawTexture gMenuSelectionArrowRight[2];

extern DrawTexture gRaceSelectionCarTex[3];
extern DrawTexture gRaceSelectionHoverTex[3];
extern DrawTexture gRaceSelectionPlaneTex[3];
extern DrawTexture gRaceSelectionTTOn[3];
extern DrawTexture gRaceSelectionTTOff[3];
extern DrawTexture gRaceSelectionCarOptHighlight[2];
extern DrawTexture gRaceSelectionCarOpt[2];
extern DrawTexture gRaceSelectionHoverOptHighlight[2];
extern DrawTexture gRaceSelectionHoverOpt[2];
extern DrawTexture gRaceSelectionPlaneOptHighlight[2];
extern DrawTexture gRaceSelectionPlaneOpt[2];
extern DrawTexture gRaceSelectionTTOnOptHighlight[2];
extern DrawTexture gRaceSelectionTTOffOptHighlight[2];
extern DrawTexture gRaceSelectionTTOnOpt[2];
extern DrawTexture gRaceSelectionTTOffOpt[2];
extern DrawTexture gRaceSelectionPlayer1Texture[2];
extern DrawTexture gRaceSelectionPlayer2Texture[2];
extern DrawTexture gRaceSelectionPlayer3Texture[2];
extern DrawTexture gRaceSelectionPlayer4Texture[2];
extern DrawTexture gRaceSelectionVehicleTitleTexture[2];
extern DrawTexture gRaceSelectionTTTitleTexture[2];
extern DrawTexture D_800E05D4[4];
extern DrawTexture D_800E05F4[4];
extern DrawTexture gRaceSelectionTTTexture[2];

extern DrawTexture *gRaceSelectionImages[9];

extern DrawTexture *D_800E0648[6];
extern DrawTexture *D_800E0660[6];

extern DrawTexture *gMenuSelectionArrows[4];

extern u16 D_800E0688[20];

extern u16 D_800E06B0[10];

extern s16 D_800E06C4[8];

extern s16 D_800E06D4[8];

extern ButtonTextElement gTwoPlayerRacerCountMenu;

extern ButtonElement D_800E0700;

extern s16 D_800E0710[16];

extern s16 D_800E0730[19];
extern s16 D_800E0758[54];

extern s16 D_800E07C4[14];

extern s16 D_800E07E0[4];

extern s16 D_800E07E8[36];

extern s16 D_800E0830[8];

extern s16 D_800E0840[148];

extern Vertex *D_800E0968;
extern s32 D_800E096C;
extern unk800E0970 *D_800E0970;
extern s32 D_800E0974;
extern char* gQMarkPtr;
extern s32 D_800E097C;
extern s32 D_800E0980;
extern s32 gMenuOptionCap;
extern s32 gMenuSubOption;
extern s32 D_800E098C;

extern s16 D_800E0A24[14];

extern s16 D_800E0A40[8];

extern DrawTexture D_800E0A50[2];
extern DrawTexture D_800E0A60[2];
extern DrawTexture D_800E0A70[2];
extern DrawTexture D_800E0A90[2];
extern DrawTexture D_800E0A80[2];
extern DrawTexture D_800E0AA0[2];
extern DrawTexture D_800E0AB0[2];
extern DrawTexture D_800E0AC0[2];
extern DrawTexture D_800E0AD0[2];
extern DrawTexture D_800E0AE0[2];

extern DrawTexture* D_800E0AF0[10];

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

extern char D_800E0F8C;
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
extern s32 gTrophyRaceRound;
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

//extern u32 dCreditsFade[22];

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

extern Gfx dMenuHudSettings[6];

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

extern char *D_800E1E10;

extern s32 D_800E1E14;
extern s32 D_800E1E18;
extern s32 D_800E1E1C;

extern s8 D_800E1E20[8];

extern s8 D_800E1E28;

extern s16 D_800E1E2C[10];

extern s16 D_800E1E40[10];

extern char *D_800E09F8[3];
extern char *gAudioOutputStrings[3];
extern char *gFilenames[3];
extern char *gMusicTestString;
extern char *sBadControllerPakMenuText[5];
extern char *sControllerPakFullMenuText[5];
extern char *sCorruptDataMenuText[3];
extern u64 sEepromSettings;
extern char *sInsertControllerPakMenuText[3];
extern char *sNoControllerPakMenuText[5];
extern char *sInsertRumblePakMenuText[4];
extern s32 *D_80126C2C;
extern Settings *gSavefileData[4];

extern DrawTexture D_800DFC10[2];
extern DrawTexture D_800DFC20[2];
extern DrawTexture D_800DFC30[2];
extern DrawTexture D_800DFC40[2];
extern DrawTexture D_800DFC50[2];
extern DrawTexture D_800DFC60[2];
extern Gfx *sMenuCurrDisplayList;
extern Mtx *sMenuCurrHudMat;
extern const char D_800E8208[];
extern s32 gOptionBlinkTimer;
extern s32 D_801263E0;
extern s32 D_80126A00;
extern unk800861C8 *D_80126A04;
extern s32 D_80126A08;
extern unk800861C8 *D_80126A0C; //Allocated 2560 bytes in menu_save_options_init. Possibly an array of 2 large structs.
extern f32 D_80126BDC;
extern f32 D_80126BEC;
extern SavefileInfo gSavefileInfo[4];

extern s8 gControllersXAxisDirection[4];
extern s8 gControllersYAxisDirection[4];
extern TextureHeader *D_80126550[128];
extern s32 D_801267D0;
extern u8 D_801269C4[4];
extern f32 gTrackSelectX;
extern f32 gTrackSelectY;
extern f32 D_801269E8;
extern f32 D_801269EC;
extern s8 gPlayerSelectVehicle[4];
extern s16 gFFLUnlocked;
extern s32 gOpacityDecayTimer;
extern s32 gTrackSelectViewportY;
extern s16 gFFLUnlocked;
extern s32 D_80126924;
extern s32 D_80126928;
extern s32 D_8012692C;
extern TrackRenderDetails gTrackSelectRenderDetails[9];
extern s32 D_801269F0;
extern s32 gSelectedTrackX;
extern s32 gSelectedTrackY;

s32 get_random_number_from_range(s32, s32); // No file to pull from yet.

void func_8007FF88(void);
void func_80080E6C(void);
void func_800813C0(void);
void menu_init(u32 menuId);
s32 menu_loop(Gfx **currDisplayList, Mtx **currHudMat, VertexList **currHudVerts, TriangleList **currHudTris, s32 updateRate);
void show_timestamp(s32 frameCount, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 fontID);
void func_80081E54(MenuElement *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5);
void func_800828B8(void);
void print_missing_controller_text(Gfx **dl, s32 updateRate);
void menu_logos_screen_init(void);
s32 menu_logo_screen_loop(s32 arg0);
void init_title_screen_variables(void);
void menu_title_screen_init(void);
void func_80084118(void);
void menu_options_init(void);
void render_options_menu_ui(s32 updateRate);
void unload_big_font_1(void);
void menu_audio_options_init(void);
void func_800851FC(void);
void menu_save_options_init(void);
s32 func_800860A8(s32 controllerIndex, s32 *arg1, unk800861C8 *arg2, s32 *arg3, s32 fileSize, s32 arg5);
void func_800861C8(unk800861C8 *arg0, s32 *arg1);
s32 func_800874D0(s32 buttonsPressed, s32 arg1);
s32 func_800875E4(s32 buttonsPressed, s32 arg1);
s32 func_800876CC(s32 buttonsPressed, s32 arg1);
void func_80087EB8(void);
void menu_boot_init(void);
void func_800887C4(void);
void func_800887E8(void);
void func_800895A4(void);
void unload_big_font_2(void);
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
void unload_big_font_3(void);
void func_8008CACC(void);
void menu_file_select_init(void);
void render_menu_image(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_8008E428(void);
void assign_vehicle_icon_textures(void);
void func_8008E4B0(void);
void func_8008F534(void);
void func_80090ED8(s32 updateRate);
s32 func_80092BE0(MapId mapId);
void menu_5_init(void);
void func_80093A0C(void);
void n_alSynRemovePlayer(void);
void n_alSeqpDelete(void);
void assign_racer_portrait_textures(void);
void func_80094C14(s32 arg0);
void func_80096790(void);
void menu_11_init(void);
void func_800976CC(void);
void decompress_filename_string(u32 compressedFilename, char *output, s32 length);
s32 compress_filename_string(char *filename, s32 length);
void func_80097874(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, char *arg5, s32 arg6);
void unload_big_font_4(void);
void func_80098208(void);
void draw_trophy_race_text(UNUSED s32 updateRate);
void unload_big_font_5(void);
void func_80099600(void);
s32 get_trophy_race_world_id(void);
void func_8009ABAC(void);
void func_8009ABD8(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void menu_23_init(void);
void func_8009AF18(void);
void menu_credits_init(void);
void render_credits_fade(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
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
void set_next_taj_challenge_menu(s32 arg0);
void set_menu_id_if_option_equal(s32 IDToCheck, s32 IDToSet);
s32 taj_menu_loop(void);
s32 dialogue_race_defeat(void);
s32 trophy_race_cabinet_menu_loop(void);
void dialogue_open_stub(void);
void dialogue_close_stub(void);
f32 func_8009E9B0(DialogueBoxBackground *arg0, Gfx **dlist, Mtx **mat, VertexList **vtx);
u64 *get_eeprom_settings_pointer(void);
s32 set_eeprom_settings_value(u64 valueToSet);
s32 unset_eeprom_settings_value(u64 valueToUnset);
u64 get_eeprom_settings(void);
s32 get_language(void);
void set_language(s32 language);
s32 is_adventure_two_unlocked(void);
s32 is_in_adventure_two(void);
s32 is_in_two_player_adventure(void);
s32 is_tt_unlocked(void);
s32 is_drumstick_unlocked(void);
s32 menu_character_select_loop(s32 updateRate);
s32 menu_caution_loop(s32 updateRate);
void func_8008DC7C(UNUSED s32 updateRate);
s32 menu_5_loop(s32 updateRate);
void func_80095624(s32 status);
s32 menu_boot_loop(s32 arg0);
void menu_magic_codes_init(void);
s32 menu_game_select_loop(s32 updateRate);
s32 menu_ghost_data_loop(s32 updateRate);
s32 menu_trophy_race_round_loop(s32 updateRate);
void render_controller_pak_ui(UNUSED s32 updateRate);
PakError check_for_controller_pak_errors(void);
void func_80093A40(void);
s32 render_pause_menu(UNUSED Gfx **dl, s32 updateRate);
s32 menu_track_select_loop(s32 updateRate);
s32 func_800867D4(void);
s32 menu_enter_filename_loop(s32 updateRate);
s32 menu_file_select_loop(s32 updateRate);
s32 func_8008D5F8(s32 updateRate);
void func_8008C168(s32 updateRate);
void func_8008C698(s32 updateRate);
void func_80083098(f32);
void func_8008F00C(s32);

// Non Matching functions below here
void load_menu_text(s32 language); // Non Matching
void draw_menu_elements(s32 arg0, MenuElement *elem, f32 arg2);
s32 menu_audio_options_loop(s32 arg0);
s32 menu_options_loop(s32 updateRate);
s32 menu_controller_pak_loop(s32 updateRate);
void render_magic_codes_list_menu_text(s32 arg0);
s32 menu_magic_codes_list_loop(s32 arg0);
void calculate_and_display_rom_checksum(void);
void randomise_ai_racer_slots(s32 arg0);
void menu_game_select_init(void);
void render_file_select_menu(s32 arg0);
void func_8008FF1C(s32 updateRate);
void func_800904E8(s32 updateRate);
void func_80090918(s32 updateRate);
void render_track_select_setup_ui(s32 updateRate);
void func_80092188(s32 updateRate);
void func_8008E4EC(void);
void trim_filename_string(char *input, char *output);
void menu_trophy_race_round_init(void);
void menu_ghost_data_init(void);
void update_controller_sticks(void);
s32 tt_menu_loop(void);
void menu_track_select_init(void);
void menu_trophy_race_rankings_init(void);
void func_8009E3D0(void);
s32 menu_title_screen_loop(s32 updateRate);
s32 menu_save_options_loop(s32 updateRate);
s32 menu_magic_codes_loop(s32 updateRate);
s32 menu_results_loop(s32 updateRate);
s32 menu_trophy_race_rankings_loop(s32 updateRate);
s32 menu_23_loop(s32 updateRate);
s32 menu_credits_loop(s32 updateRate);
void func_8009CA60(s32 imageID);
void func_8007FFEC(s32 arg0);
void func_800871D8(s32 arg0);
SIDeviceStatus func_80087F14(s32 *controllerIndex, s32 arg1);
void func_8009C6D4(s32 arg0);
void func_8008B358(void);
void func_8008B4C8(void);
void func_8008B758(s8 *activePlayers);
void func_8006F564(s8 arg0);
void func_80099E8C(s32 updateRate);
void func_80092E94(UNUSED s32 updateRate, s32 arg1, s32 arg2);
s32 func_800998E0(s32 arg0);
void func_80081218(void);
void func_80080580(Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, void *arg8);
void func_800853D0(unk800861C8 *arg0, s32 arg1, s32 arg2);
void render_enter_filename_ui(UNUSED s32 unused);
void func_8008D8BC(s32 updateRate);
void renderTrackSelect(s32 arg0, s32 arg1, s8 *arg2, s8 *arg3, s32 arg4, s32 arg5, s32 arg6, DrawTexture *arg7, s32 arg8);
s32 func_80095728(Gfx **gfx, Mtx **mtx, VertexList **vtx, s32 updateRate);
s32 func_8008F618(Gfx **dlist, Mtx **mat);

typedef enum MenuTextures {
/* 0x00 */ TEXTURE_UNK_00,
/* 0x01 */ TEXTURE_UNK_01,
/* 0x02 */ TEXTURE_UNK_02,
/* 0x03 */ TEXTURE_UNK_03,
/* 0x04 */ TEXTURE_UNK_04,
/* 0x05 */ TEXTURE_UNK_05,
/* 0x06 */ TEXTURE_UNK_06,
/* 0x07 */ TEXTURE_UNK_07,
/* 0x08 */ TEXTURE_UNK_08,
/* 0x09 */ TEXTURE_UNK_09,
/* 0x0A */ TEXTURE_UNK_0A,
/* 0x0B */ TEXTURE_UNK_0B,
/* 0x0C */ TEXTURE_UNK_0C,
/* 0x0D */ TEXTURE_UNK_0D,
/* 0x0E */ TEXTURE_BACKGROUND_DINO_DOMAIN_TOP,
/* 0x0F */ TEXTURE_BACKGROUND_DINO_DOMAIN_BOTTOM,
/* 0x10 */ TEXTURE_BACKGROUND_SHERBERT_ISLAND_TOP,
/* 0x11 */ TEXTURE_BACKGROUND_SHERBERT_ISLAND_BOTTOM,
/* 0x12 */ TEXTURE_BACKGROUND_SNOWFLAKE_MOUNTAIN_TOP,
/* 0x13 */ TEXTURE_BACKGROUND_SNOWFLAKE_MOUNTAIN_BOTTOM,
/* 0x14 */ TEXTURE_BACKGROUND_DRAGON_FOREST_TOP,
/* 0x15 */ TEXTURE_BACKGROUND_DRAGON_FOREST_BOTTOM,
/* 0x16 */ TEXTURE_BACKGROUND_FUTURE_FUN_LAND_TOP,
/* 0x17 */ TEXTURE_BACKGROUND_FUTURE_FUN_LAND_BOTTOM,
/* 0x18 */ TEXTURE_ICON_VEHICLE_CAR_TOP,
/* 0x19 */ TEXTURE_ICON_VEHICLE_CAR_BOTTOM,
/* 0x1A */ TEXTURE_ICON_VEHICLE_HOVERCRAFT_TOP,
/* 0x1B */ TEXTURE_ICON_VEHICLE_HOVERCRAFT_BOTTOM,
/* 0x1C */ TEXTURE_ICON_VEHICLE_PLANE_TOP,
/* 0x1D */ TEXTURE_ICON_VEHICLE_PLANE_BOTTOM,
/* 0x1E */ TEXTURE_ICON_VEHICLE_SELECT_CAR,
/* 0x1F */ TEXTURE_ICON_VEHICLE_SELECT_CAR_HIGHLIGHT,
/* 0x20 */ TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT,
/* 0x21 */ TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT_HIGHLIGHT,
/* 0x22 */ TEXTURE_ICON_VEHICLE_SELECT_PLANE,
/* 0x23 */ TEXTURE_ICON_VEHICLE_SELECT_PLANE_HIGHLIGHT,
/* 0x24 */ TEXTURE_ICON_TIMETRIAL_ON_TOP,
/* 0x25 */ TEXTURE_ICON_TIMETRIAL_ON_BOTTOM,
/* 0x26 */ TEXTURE_ICON_TIMETRIAL_OFF_TOP,
/* 0x27 */ TEXTURE_ICON_TIMETRIAL_OFF_BOTTOM,
/* 0x28 */ TEXTURE_ICON_TIMETRIAL_OPT_ON,
/* 0x29 */ TEXTURE_ICON_TIMETRIAL_OPT_OFF,
/* 0x2A */ TEXTURE_ICON_TIMETRIAL_OPT_ON_HIGHLIGHT,
/* 0x2B */ TEXTURE_ICON_TIMETRIAL_OPT_OFF_HIGHLIGHT,
/* 0x2C */ TEXTURE_ICON_PLAYER_1,
/* 0x2D */ TEXTURE_ICON_PLAYER_2,
/* 0x2E */ TEXTURE_ICON_PLAYER_3,
/* 0x2F */ TEXTURE_ICON_PLAYER_4,
/* 0x30 */ TEXTURE_ICON_VEHICLE_TITLE,
/* 0x31 */ TEXTURE_ICON_TT_TITLE,
/* 0x32 */ TEXTURE_ICON_PORTRAIT_KRUNCH,
/* 0x33 */ TEXTURE_ICON_PORTRAIT_DIDDY,
/* 0x34 */ TEXTURE_ICON_PORTRAIT_DRUMSTICK,
/* 0x35 */ TEXTURE_ICON_PORTRAIT_BUMPER,
/* 0x36 */ TEXTURE_ICON_PORTRAIT_BANJO,
/* 0x37 */ TEXTURE_ICON_PORTRAIT_CONKER,
/* 0x38 */ TEXTURE_ICON_PORTRAIT_TIPTUP,
/* 0x39 */ TEXTURE_ICON_PORTRAIT_TT,
/* 0x3A */ TEXTURE_ICON_PORTRAIT_PIPSY,
/* 0x3B */ TEXTURE_ICON_PORTRAIT_TIMBER,
/* 0x3C */ TEXTURE_ICON_ARROW_LEFT,
/* 0x3D */ TEXTURE_ICON_ARROW_UP,
/* 0x3E */ TEXTURE_ICON_ARROW_RIGHT,
/* 0x3F */ TEXTURE_ICON_ARROW_DOWN,
/* 0x40 */ TEXTURE_ICON_BALLOON_GOLD,
/* 0x41 */ TEXTURE_ICON_BALLOON_DIAMOND,
/* 0x42 */ TEXTURE_ICON_MARKER_CROSS,
/* 0x43 */ TEXTURE_SURFACE_BUTTON_WOOD,
/* 0x44 */ TEXTURE_UNK_44,
/* 0x45 */ TEXTURE_UNK_45,
/* 0x46 */ TEXTURE_ICON_SAVE_BIN,
/* 0x47 */ TEXTURE_ICON_SAVE_N64,
/* 0x48 */ TEXTURE_ICON_SAVE_TT,
/* 0x49 */ TEXTURE_ICON_SAVE_CPAK,
/* 0x4A */ TEXTURE_ICON_SAVE_FILECABINET,
/* 0x4B */ TEXTURE_ICON_SAVE_GHOSTS,
/* 0x4C */ TEXTURE_UNK_4C,
/* 0x4D */ TEXTURE_UNK_4D,
/* 0x4E */ TEXTURE_UNK_4E,
/* 0x4F */ TEXTURE_UNK_4F,
/* 0x50 */ TEXTURE_TITLE_SEGMENT_01,
/* 0x51 */ TEXTURE_TITLE_SEGMENT_02,
/* 0x52 */ TEXTURE_TITLE_SEGMENT_03,
/* 0x53 */ TEXTURE_TITLE_SEGMENT_04,
/* 0x54 */ TEXTURE_TITLE_SEGMENT_05,
/* 0x55 */ TEXTURE_TITLE_SEGMENT_06,
/* 0x56 */ TEXTURE_TITLE_SEGMENT_07,
/* 0x57 */ TEXTURE_TITLE_SEGMENT_08,
/* 0x58 */ TEXTURE_TITLE_SEGMENT_09,
/* 0x59 */ TEXTURE_TITLE_SEGMENT_10,
/* 0x5A */ TEXTURE_TITLE_SEGMENT_11,
/* 0x5B */ TEXTURE_UNK_5B,
/* 0x5C */ TEXTURE_UNK_5C,
/* 0x5D */ TEXTURE_UNK_5D,
/* 0x5E */ TEXTURE_ICON_TT_HEAD,
/* 0x5F */ TEXTURE_UNK_5F,
/* 0x60 */ TEXTURE_UNK_60,
/* 0x61 */ TEXTURE_UNK_61,
/* 0x62 */ TEXTURE_UNK_62,
/* 0x63 */ TEXTURE_UNK_63,
/* 0x64 */ TEXTURE_UNK_64,
/* 0x65 */ TEXTURE_UNK_65,
/* 0x66 */ TEXTURE_UNK_66,
/* 0x67 */ TEXTURE_UNK_67,
/* 0x68 */ TEXTURE_UNK_68,
/* 0x69 */ TEXTURE_UNK_69,
/* 0x6A */ TEXTURE_UNK_6A,
/* 0x6B */ TEXTURE_UNK_6B,
/* 0x6C */ TEXTURE_UNK_6C,
/* 0x6D */ TEXTURE_UNK_6D,
/* 0x6E */ TEXTURE_UNK_6E,
/* 0x6F */ TEXTURE_UNK_6F,
/* 0x70 */ TEXTURE_UNK_70,
/* 0x71 */ TEXTURE_UNK_71,
/* 0x72 */ TEXTURE_UNK_72,
/* 0x73 */ TEXTURE_UNK_73,
/* 0x74 */ TEXTURE_UNK_74,
/* 0x75 */ TEXTURE_UNK_75,
/* 0x76 */ TEXTURE_UNK_76,
/* 0x77 */ TEXTURE_UNK_77,
/* 0x78 */ TEXTURE_UNK_78,
/* 0x79 */ TEXTURE_UNK_79,
/* 0x7A */ TEXTURE_UNK_7A,
/* 0x7B */ TEXTURE_UNK_7B,
/* 0x7C */ TEXTURE_UNK_7C,
/* 0x7D */ TEXTURE_UNK_7D,
/* 0x7E */ TEXTURE_UNK_7E,
/* 0x7F */ TEXTURE_UNK_7F,

    NUM_MENU_TEXTURES

} MenuTextures;

#endif
