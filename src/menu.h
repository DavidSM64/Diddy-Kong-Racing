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

#define NUM_CHARACTERS 10

#define PLAYER_MENU 4

#define CINEMATIC_LEVELID   0
#define CINEMATIC_PLAYERS   1
#define CINEMATIC_CUTSCENE  2

enum PauseMenuResults {
    PAUSE_NONE,
    PAUSE_CONTINUE,
    PAUSE_RESET,
    PAUSE_QUIT_LOBBY,
    PAUSE_OPT_4,
    PAUSE_QUIT_TRACKS,
    PAUSE_OPT_6,
    PAUSE_QUIT_CHALLENGE,
    PAUSE_QUIT_CHARSELECT = 12,
};

enum PostRaceCases {
    POSTRACE_NONE,
    POSTRACE_OPT_1,
    POSTRACE_OPT_2,
    POSTRACE_OPT_3,
    POSTRACE_OPT_4,
    POSTRACE_OPT_5,
    POSTRACE_OPT_6,
    POSTRACE_OPT_7,
    POSTRACE_OPT_8,
    POSTRACE_OPT_9,
    POSTRACE_OPT_10,
    POSTRACE_OPT_11,
    POSTRACE_OPT_12,
    POSTRACE_OPT_13
};

enum PostRaceRenderStates {
    POSTRACE_ENTER,
    POSTRACE_HOLD,
    POSTRACE_SLIDE_OUT,
    POSTRACE_SLIDE_END = 4,
};

enum PostRaceStages {
    POSTRACE_STAGE_BEGIN,
    POSTRACE_STAGE_SHRINK_VIEWPORT,
    POSTRACE_STAGE_RACE_TIMES,
    POSTRACE_STAGE_RACE_ORDER,
    POSTRACE_STAGE_ENTER_INITIALS,
    POSTRACE_STAGE_RACE_RECORDS,
    POSTRACE_STAGE_OPTIONS,
    POSTRACE_STAGE_FADE_OUT,
    POSTRACE_STAGE_END
};

enum SaveMenuStages {
    SAVEMENU_ENTER,
    SAVEMENU_WAIT,
    SAVEMENU_INIT_SOURCE,
    SAVEMENU_CHOOSE_SOURCE,
    SAVEMENU_INIT_DEST,
    SAVEMENU_CHOOSE_DEST,
    SAVEMENU_CONFIRM,
    SAVEMENU_WRITE
};

enum PakMenuStages {
    PAKMENU_CHOOSE,
    PAKMENU_CONFIRM,
    PAKMENU_WRITE
};

enum CheatMenuStages {
    CHEATMENU_CHOOSE,
    CHEATMENU_KEYBOARD,
    CHEATMENU_MESSAGE,
};

enum TrackmenuStages {
    TRACKMENU_MIRROR = -1,
    TRACKMENU_OPT_1,
    TRACKMENU_CHOOSE,
    TRACKMENU_OPT_2,
    TRACKMENU_OPT_3,
    TRACKMENU_OPT_4
};

enum AdventureSetupStages {
    ADVENTURESETUP_PREVIEW = -1,
    ADVENTURESETUP_VEHICLE,
    ADVENTURESETUP_CONFIRM
};

enum ResultsStages {
    RESULTS_ENTER = -1,
    RESULTS_SCORE,
    RESULTS_OPTIONS,
};

enum TitleScreenStages {
    TITLESCREEN_START,
    TITLESCREEN_NAME,
    TITLESCREEN_PRESS_START
};

enum RankingsStages {
    RANKINGS_ENTER,
    RANKINGS_SWAP,
    RANKINGS_ORDER,
    RANKINGS_EXIT
};

enum GhostMenuStages {
    GHOSTMENU_CHOOSE,
    GHOSTMENU_ERASE,
    GHOSTMENU_CONFIRM
};

enum DialogueMenuCases {
    DIALOGUE_TAJ,
    DIALOGUE_UNK_01,
    DIALOGUE_TT,
    DIALOGUE_CHALLENGE,
    DIALOGUE_TROPHY,
    DIALOGUE_RACERESULT
};

enum DialogIDsTaj {
    DIALOGUEPAGE_TAJ_CHALLENGE_WIN_3 = -8,
    DIALOGUEPAGE_TAJ_CHALLENGE_WIN_2 = -7,
    DIALOGUEPAGE_TAJ_CHALLENGE_WIN_1 = -6,
    DIALOGUEPAGE_TAJ_CHALLENGE_WIN = -5,
    DIALOGUEPAGE_TAJ_CHALLENGE_LOSE = -4,
    DIALOGUEPAGE_TAJ_CHALLENGE_PLANE = -3,
    DIALOGUEPAGE_TAJ_CHALLENGE_HOVER = -2,
    DIALOGUEPAGE_TAJ_CHALLENGE_CAR = -1,
    DIALOGUEPAGE_TAJ_TUTORIAL,
    DIALOGUEPAGE_TAJ_ROOT,
    DIALOGUEPAGE_TAJ_VEHICLE_SELECT,
    DIALOGUEPAGE_TAJ_CHALLENGES,
    DIALOGUEPAGE_TAJ_4,
    DIALOGUEPAGE_TAJ_5,
    DIALOGUEPAGE_TAJ_6,
    DIALOGUEPAGE_TAJ_7,
    DIALOGUEPAGE_TAJ_8,
    DIALOGUEPAGE_TAJ_VEHICLE_SELECT_2 = 98,
    DIALOGUEPAGE_TAJ_CHALLENGES_2
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
    CHEAT_ROM_CHECKSUM             = CHEAT(28),
    MAX_CHEATS                     = 32
} Cheats;

typedef enum MENU_ID {
    MENU_TITLE,
    MENU_LOGOS,
    MENU_UNUSED_2,
    MENU_CHARACTER_SELECT,
    MENU_UNUSED_4,
    MENU_TRACK_SELECT_ADVENTURE,
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
    MENU_NEWGAME_CINEMATIC,
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

typedef enum TitleDemoIndex {
    DEMO_LEVEL_ID,
    DEMO_PLAYER_COUNT,
    DEMO_CUTSCENE_ID,

    DEMO_INDEX_SIZE
} TitleDemoIndex;

/* Size: 0x20 bytes */
// So this is looking to be a struct for menu images.
typedef struct MenuAsset {
    s16 y_rotation;
    s16 x_rotation;
    s16 z_rotation;
    s16 spriteID;
    f32 scale;
    f32 x;
    f32 y;
    f32 z;
    s16 spriteOffset;
    s8 unk1A;
    s8 unk1B;
    s8 unk1C;
    s8 unk1D;
    s8 unk1E;
    s8 unk1F;
} MenuAsset;

typedef struct unk80080BC8 {
    Vertex *vertices;
    s32 *unk4;
    Triangle *triangles;
    s32 *unkC;
    TextureHeader *texture;
    s32 *unk14;
    s32 unk18;
    s32 unk1C;
} unk80080BC8;

typedef struct unk80126460 {
    MenuElement elem[2];
} unk80126460;

typedef struct unk801263C0 {
    s8 channelIndex;
    s8 unk1;
    union {
        struct {
            s8 unk2a;
            s8 unk3;
        };
        s16 unk2;
    };
} unk801263C0;

typedef struct unk80126C54 {
    union {
        struct {
            u8 unk0;
            u8 unk1;
            u8 unk2;
            u8 unk3;
        };
        s32 unk0_s32;
    };
} unk80126C54;

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
    char *unkC;
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
    s8 upInput[2];
    s8 downInput[2];
    s8 rightInput[4];
    s8 leftInput[4];
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

typedef struct MenuColour {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 opacity;
} MenuColour;

// Unknown Size
typedef struct unk80126A80 {
    u8 pad0[0x13];
    s8 highlight;
} unk80126A80;

/* Size: 0x10 bytes */
typedef struct SaveFileData {
  /* 0x00 */ u8 saveFileType; //SaveFileType enum
  /* 0x01 */ u8 unk1;
  /* 0x02 */ u8 balloonCount;
  /* 0x03 */ u8 adventureTwo;
  /* 0x04 */ s16 compressedFilename;
  /* 0x06 */ u8 controllerIndex;
  /* 0x07 */ u8 saveFileNumber;
  /* 0x08 */ char *saveFileExt;
  /* 0x0C */ u32 fileSize; // Game Data File Size
} SaveFileData;

// Size: 12 bytes
typedef struct unk80126878 {
  /* 0x00 */ char *text;
  /* 0x04 */ s16 x;
  /* 0x06 */ s16 y;
  /* 0x08 */ s32 colourIndex;
} unk80126878;

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

typedef struct unk8009CA602 {
    ObjectTransform trans;
    s16 unk18;
    s16 unk1A;
    s8 unk1C;
    s8 unk1D;
} unk8009CA602;

typedef struct TitleScreenDemos {
    s8 levelId;
    s8 numberOfPlayers;
    s8 cutsceneId;
} TitleScreenDemos;

#define X_TILE_SIZE 320

/* Size 0x10 bytes */
typedef struct TrackRenderDetails {
  /* 0x00 */ char *hubName;
  /* 0x04 */ char *trackName;
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

extern s32 gShowControllerPakMenu;
extern u8 *__ROM_END;

s32 get_random_number_from_range(s32, s32); // No file to pull from yet.

void menu_button_free(void);
void menu_geometry_end(void);
void reset_title_logo_scale(void);
void menu_init(u32 menuId);
s32 menu_loop(Gfx **currDisplayList, MatrixS **currHudMat, Vertex **currHudVerts, TriangleList **currHudTris, s32 updateRate);
void menu_timestamp_render(s32 frameCount, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 fontID);
void postrace_offsets(MenuElement *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5);
void trackmenu_set_records(void);
void menu_missing_controller(Gfx **dl, s32 updateRate);
void menu_logos_screen_init(void);
s32 menu_logo_screen_loop(s32 updateRate);
void init_title_screen_variables(void);
void menu_title_screen_init(void);
void titlescreen_free(void);
void menu_options_init(void);
void optionscreen_render(s32 updateRate);
void optionscreen_free(void);
void menu_audio_options_init(void);
void soundoptions_free(void);
void menu_save_options_init(void);
SIDeviceStatus savemenu_check_space(s32 controllerIndex, s32 *arg1, SaveFileData *arg2, s32 *arg3, s32 fileSize, s32 arg5);
void savemenu_blank_save_destination(SaveFileData *arg0, s32 *arg1);
s32 savemenu_input_source(s32 buttonsPressed, s32 arg1);
s32 savemenu_input_dest(s32 buttonsPressed, s32 arg1);
s32 savemenu_input_confirm(s32 buttonsPressed, s32 arg1);
void savemenu_free(void);
void menu_boot_init(void);
void bootscreen_free(void);
void bootscreen_init_cpak(void);
void pakmenu_free(void);
void cheatmenu_free(void);
void menu_magic_codes_list_init(void);
void cheatlist_exclusive(s32 arg0, s32 arg1, s32 arg2);
void cheatlist_free(void);
void charselect_prev(s32 arg0, s32 *arg1);
void titlescreen_controller_assign(s32 controllerIndex);
void menu_character_select_init(void);
void charselect_render_text(s32 arg0);
void charselect_move(s32 arg0, s8 *arg1, s32 arg2, u16 menuPickSoundId, u16 menuPickFailedSoundId);
void charselect_free(void);
void menu_caution_init(void);
void caution_free(void);
void gameselect_free(void);
void menu_file_select_init(void);
void fileselect_render_element(s32 imageID, s32 xOffset, s32 yOffset, s32 red, s32 green, s32 blue, s32 opacity);
void fileselect_free(void);
void menu_init_vehicle_textures(void);
void menu_init_arrow_textures(void);
void menu_track_select_unload(void);
void trackmenu_timetrial_sound(s32 updateRate);
s32 trackmenu_staff_beaten(s32 mapId);
void menu_adventure_track_init(void);
void adventuretrack_free(void);
void menu_dialogue_end(void);
void menu_close_dialogue(void);
void menu_racer_portraits(void);
void postrace_music_fade(s32 updateRate);
void postrace_free(void);
void menu_results_init(void);
void results_free(void);
void filename_decompress(u32 compressedFilename, char *output, s32 length);
s32 filename_compress(char *filename, s32 length);
void filename_init(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, char *fileName, s32 fileNameLength);
void menu_unload_bigfont(void);
void trophyround_adventure(void);
void trophyround_render(UNUSED s32 updateRate);
void trophyround_free(void);
void rankings_free(void);
s32 get_trophy_race_world_id(void);
void ghostmenu_free(void);
void cinematic_start(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s8 *arg5);
void menu_cinematic_init(void);
void cinematic_free(void);
void menu_credits_init(void);
void credits_fade(s32 x1, s32 y1, s32 x2, s32 y2, s32 a);
void credits_free(void);
void menu_camera_centre(void);
void reset_controller_sticks(void);
void reset_character_id_slots(void);
s32 get_save_file_index(void);
s32 get_track_id_to_load(void);
s8 get_character_id_from_slot(s32 slot);
s8 get_character_id_from_slot_unused(s32 slot);
s8 get_player_selected_vehicle(s32 playerNum);
void set_player_selected_vehicle(s32 playerNum, s32 index);
s8 *charselect_status(void);
s8 get_player_character(s32 controllerIndex);
void enable_tracks_mode(s32 boolean);
s32 is_in_tracks_mode(void);
void set_magic_code_flags(s32 flags);
s32 get_filtered_cheats(void);
s32 get_number_of_active_players(void);
s32 get_active_player_count(void);
s32 get_multiplayer_racer_count(void);
Settings **get_all_save_files_ptr(void);
void menu_assetgroup_free(s16 *arg0);
void menu_asset_free(s32 arg0);
void menu_assetgroup_load(s16 *textureIndex);
void menu_imagegroup_load(s16 *imageSet);
void menu_image_load(s32 imageID);
void menu_imagegroup_free(void);
void dialogue_npc_finish(s32 arg0);
void dialogue_try_close(void);
s32 npc_dialogue_loop(u32 dialogueOption);
void set_option_text_colour(s32 condition);
void render_dialogue_option(char *text, s32 yOffset, s32 optionID);
void handle_menu_joystick_input(void);
void set_next_taj_challenge_menu(s32 arg0);
void set_menu_id_if_option_equal(s32 IDToCheck, s32 IDToSet);
s32 taj_menu_loop(void);
s32 dialogue_race_defeat(void);
s32 trophy_race_cabinet_menu_loop(void);
void dialogue_open_stub(void);
void dialogue_close_stub(void);
f32 dialogue_ortho(DialogueBoxBackground *arg0, Gfx **dlist, MatrixS **mat, Vertex **verts);
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
void fileselect_input_erase(UNUSED s32 updateRate);
s32 menu_adventure_track_loop(s32 updateRate);
void postrace_message(SIDeviceStatus status);
s32 menu_boot_loop(s32 updateRate);
void menu_magic_codes_init(void);
s32 menu_game_select_loop(s32 updateRate);
s32 menu_ghost_data_loop(s32 updateRate);
s32 menu_trophy_race_round_loop(s32 updateRate);
void pakmenu_render(UNUSED s32 updateRate);
PakError check_for_controller_pak_errors(void);
void menu_pause_init(void);
s32 menu_pause_loop(UNUSED Gfx **dl, s32 updateRate);
s32 menu_track_select_loop(s32 updateRate);
SIDeviceStatus savemenu_load_destinations(void);
s32 filename_enter(s32 updateRate);
s32 menu_file_select_loop(s32 updateRate);
s32 fileselect_input_root(s32 updateRate);
void charselect_music_channels(s32 updateRate);
void gameselect_render(s32 updateRate);
void func_80083098(f32);
void trackmenu_assets(s32);
void render_track_selection_viewport_border(ObjectModel *objMdl);
void adventuretrack_render(UNUSED s32 updateRate, s32 arg1, s32 arg2);
void menu_trophy_race_round_init(void);
void charselect_new_player(void);
s32 menu_save_options_loop(s32 updateRate);
s32 menu_cinematic_loop(s32 updateRate);
s32 menu_magic_codes_list_loop(s32 updateRate);
void menu_trophy_race_rankings_init(void);
void cheatmenu_checksum(void);
s32 menu_trophy_race_rankings_loop(s32 updateRate);
s32 menu_results_loop(s32 updateRate);
s32 menu_options_loop(s32 updateRate);
void charselect_pick(void);
void charselect_input(s8 *activePlayers);
s32 menu_audio_options_loop(s32 updateRate);
void ghostmenu_generate(void);
void filename_render(UNUSED s32 updateRate);
void charselect_assign_ai(s32 arg0);
void menu_number_render(s32 number, s32 x, s32 y, s32 r, s32 g, s32 b, s32 a, UNUSED s32 font, s32 alignment);
void menu_element_render(s32 elementID);
void menu_input(void);
SIDeviceStatus savemenu_load_sources(void);
void menu_asset_load(s32 arg0);
s32 savemenu_input_message(s32 buttonsPressed, s32 yAxis);
void savemenu_render_element(SaveFileData *arg0, s32 x, s32 y);
void trackmenu_render_2D(s32 x, s32 y, char *hubName, char *trackName, s32 rectOpacity, s32 imageId, s32 copyViewPort, DrawTexture *arg7, s32 arg8);
void pausemenu_render(UNUSED s32 updateRate);
s32 menu_postrace(Gfx **dlist, MatrixS **matrices, Vertex **vertices, s32 updateRate);
void ghostmenu_render(UNUSED s32 updateRate);
s32 ghostmenu_erase(s32 arg0);
void cheatmenu_render(s32 updateRate);
void cheatlist_render(s32 updateRate);
void trackmenu_track_view(s32 updateRate);
void savemenu_render(UNUSED s32 updateRate);
void draw_menu_elements(s32 flags, MenuElement *elems, f32 scale);
void fileselect_render(UNUSED s32 updateRate);
void savemenu_render_error(SIDeviceStatus deviceStatus);
SIDeviceStatus savemenu_write(void);
void trackmenu_setup_render(s32 updateRate);
void rankings_render_order(s32 updateRate);
void results_render(UNUSED s32 updateRate, f32 opacity);

// Non Matching functions below here
void load_menu_text(s32 language); // Non Matching
s32 menu_controller_pak_loop(s32 updateRate);
void menu_game_select_init(void);
void func_8008FF1C(s32 updateRate);
void trackmenu_input(s32 updateRate);
void func_80092188(s32 updateRate);
void filename_trim(char *input, char *output);
void menu_ghost_data_init(void);
void update_controller_sticks(void);
s32 tt_menu_loop(void);
void menu_track_select_init(void);
void dialogue_tt_gamestatus(void);
s32 menu_title_screen_loop(s32 updateRate);
s32 menu_magic_codes_loop(s32 updateRate);
s32 menu_credits_loop(s32 updateRate);
void func_8007FFEC(s32 arg0);
SIDeviceStatus func_80087F14(s32 *controllerIndex, s32 arg1);
void set_gIntDisFlag(s8 setting);
void init_save_data(void);
void func_80080580(Gfx **dlist, s32 startX, s32 startY, s32 width, s32 height, s32 borderWidth, s32 borderHeight, s32 colour, TextureHeader *tex);
void fileselect_input_copy(s32 updateRate);

s32 func_8008F618(Gfx **dlist, MatrixS **mtx);
void func_80080BC8(Gfx **);
void func_80080E90(Gfx **dList, s32 startX, s32 startY, s32 width, s32 height, s32 borderWidth, s32 borderHeight, s32 colour0, s32 colour1, s32 colour2, s32 colour3);
void func_80084854(void);
void func_80098774(s32);
void func_80094D28(UNUSED s32 updateRate);

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
