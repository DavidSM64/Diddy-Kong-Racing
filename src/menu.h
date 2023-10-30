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

enum DialogueMenuCases {
    DIALOGUE_TAJ,
    DIALOGUE_UNK_01,
    DIALOGUE_TT,
    DIALOGUE_CHALLENGE,
    DIALOGUE_TROPHY,
    DIALOGUE_RACERESULT
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
    s8 unk13;
} unk80126A80;

/* Size: 0x10 bytes */
typedef struct unk800861C8 {
  /* 0x00 */ u8 saveFileType; //SaveFileType enum
  /* 0x01 */ u8 unk1;
  /* 0x02 */ u8 unk2;
  /* 0x03 */ u8 unk3;
  /* 0x04 */ s16 compressedFilename;
  /* 0x06 */ u8 controllerIndex;
  /* 0x07 */ u8 unk7;
  /* 0x08 */ char *unk8;
  /* 0x0C */ u32 fileSize; // Game Data File Size
} unk800861C8;

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

typedef struct unk8006BDB0 {
    u8 pad[0x4C];
    s8 unk4C;
} unk8006BDB0;

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

extern s32 gShowControllerPakMenu;
extern u8 *__ROM_END;

s32 get_random_number_from_range(s32, s32); // No file to pull from yet.

void func_8007FF88(void);
void func_80080E6C(void);
void reset_title_logo_scale(void);
void menu_init(u32 menuId);
s32 menu_loop(Gfx **currDisplayList, MatrixS **currHudMat, Vertex **currHudVerts, TriangleList **currHudTris, s32 updateRate);
void show_timestamp(s32 frameCount, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 fontID);
void func_80081E54(MenuElement *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5);
void func_800828B8(void);
void print_missing_controller_text(Gfx **dl, s32 updateRate);
void menu_logos_screen_init(void);
s32 menu_logo_screen_loop(s32 arg0);
void init_title_screen_variables(void);
void menu_title_screen_init(void);
void title_screen_exit(void);
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
void assign_menu_arrow_textures(void);
void func_8008F534(void);
void func_80090ED8(s32 updateRate);
s32 func_80092BE0(s32 mapId);
void menu_adventure_track_init(void);
void func_80093A0C(void);
void n_alSynRemovePlayer(void);
void n_alSeqpDelete(void);
void assign_racer_portrait_textures(void);
void func_80094C14(s32 updateRate);
void func_80096790(void);
void menu_results_init(void);
void func_800976CC(void);
void decompress_filename_string(u32 compressedFilename, char *output, s32 length);
s32 compress_filename_string(char *filename, s32 length);
void func_80097874(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, char *fileName, s32 fileNameLength);
void unload_big_font_4(void);
void func_80098208(void);
void draw_trophy_race_text(UNUSED s32 updateRate);
void unload_big_font_5(void);
void func_80099600(void);
s32 get_trophy_race_world_id(void);
void func_8009ABAC(void);
void func_8009ABD8(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s8 *arg5);
void menu_cinematic_init(void);
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
Settings **get_all_save_files_ptr(void);
void func_8009C4A8(s16 *arg0);
void func_8009C508(s32 arg0);
void func_8009C674(s16 *arg0);
void allocate_menu_images(s16 *imageSet);
void allocate_and_set_menu_image_properties(s32 imageID);
void func_8009CA58(void);
void func_8009CF68(s32 arg0);
void try_close_dialogue_box(void);
s32 npc_dialogue_loop(u32 arg0);
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
f32 func_8009E9B0(DialogueBoxBackground *arg0, Gfx **dlist, MatrixS **mat, Vertex **vtx);
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
s32 menu_adventure_track_loop(s32 updateRate);
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
void render_track_selection_viewport_border(ObjectModel *objMdl);
void render_adventure_track_setup(UNUSED s32 updateRate, s32 arg1, s32 arg2);
void menu_trophy_race_round_init(void);
void func_8008B358(void);
s32 menu_save_options_loop(s32 updateRate);
s32 menu_cinematic_loop(s32 updateRate);
s32 menu_magic_codes_list_loop(s32 updateRate);
void menu_trophy_race_rankings_init(void);
void calculate_and_display_rom_checksum(void);
s32 menu_trophy_race_rankings_loop(s32 updateRate);
s32 menu_results_loop(s32 updateRate);
s32 menu_options_loop(s32 updateRate);
void func_8008B4C8(void);
void func_8008B758(s8 *activePlayers);
s32 menu_audio_options_loop(s32 updateRate);
void func_8009963C(void);
void render_enter_filename_ui(UNUSED s32 updateRate);
void randomise_ai_racer_slots(s32 arg0);
void func_80081C04(s32 number, s32 x, s32 y, s32 r, s32 g, s32 b, s32 a, UNUSED s32 font, s32 alignment);
void func_8009CA60(s32 stackIndex);
void func_8008E4EC(void);
SIDeviceStatus func_800862C4(void);
void func_8009C6D4(s32 arg0);
s32 func_80087734(s32 buttonsPressed, s32 yAxis);
void func_800853D0(unk800861C8 *arg0, s32 x, s32 y);
void render_track_select(s32 x, s32 y, char *hubName, char *trackName, s32 rectOpacity, s32 imageId, s32 copyViewPort, DrawTexture *arg7, s32 arg8);
void func_80093D40(UNUSED s32 updateRate);
s32 func_80095728(Gfx **dlist, MatrixS **matrices, Vertex **vertices, s32 updateRate);
void func_80099E8C(UNUSED s32 updateRate);
s32 func_800998E0(s32 arg0);
void render_magic_codes_ui(s32 updateRate);
void render_magic_codes_list_menu_text(s32 updateRate);
void func_800904E8(s32 updateRate);

// Non Matching functions below here
void load_menu_text(s32 language); // Non Matching
void draw_menu_elements(s32 arg0, MenuElement *elem, f32 arg2);
s32 menu_controller_pak_loop(s32 updateRate);
void menu_game_select_init(void);
void render_file_select_menu(s32 arg0);
void func_8008FF1C(s32 updateRate);
void func_80090918(s32 updateRate);
void render_track_select_setup_ui(s32 updateRate);
void func_80092188(s32 updateRate);
void trim_filename_string(char *input, char *output);
void menu_ghost_data_init(void);
void update_controller_sticks(void);
s32 tt_menu_loop(void);
void menu_track_select_init(void);
void func_8009E3D0(void);
s32 menu_title_screen_loop(s32 updateRate);
s32 menu_magic_codes_loop(s32 updateRate);
s32 menu_credits_loop(s32 updateRate);
void func_8007FFEC(s32 arg0);
void func_800871D8(s32 arg0);
SIDeviceStatus func_80087F14(s32 *controllerIndex, s32 arg1);
void set_gIntDisFlag(s8 bool);
void func_80081218(void);
void func_80080580(Gfx **dlist, s32 startX, s32 startY, s32 width, s32 height, s32 borderWidth, s32 borderHeight, s32 colour, TextureHeader *tex);
void func_8008D8BC(s32 updateRate);

s32 func_8008F618(Gfx **dlist, MatrixS **mtx);
void func_80080BC8(Gfx **);
void func_80080E90(Gfx **dList, s32 startX, s32 startY, s32 width, s32 height, s32 borderWidth, s32 borderHeight, s32 colour0, s32 colour1, s32 colour2, s32 colour3);
void func_80084854(void);
s32 func_80086AFC(void);
void func_80085B9C(UNUSED s32 updateRate);
void func_80098774(s32);
void func_80096978(s32, f32);
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
