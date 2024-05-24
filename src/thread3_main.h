#ifndef _THREAD3_MAIN_H_
#define _THREAD3_MAIN_H_

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "game.h"

typedef enum GameMode {
    GAMEMODE_INTRO = -1,
    GAMEMODE_INGAME,
    GAMEMODE_MENU,
    GAMEMODE_UNUSED_2,
    GAMEMODE_UNUSED_3,
    GAMEMODE_UNUSED_4,
    GAMEMODE_LOCKUP
} GameMode;

enum LevelLoadType {
    LEVEL_LOAD_NORMAL,
    LEVEL_LOAD_UNK1,
    LEVEL_LOAD_TROPHY_RACE,
    LEVEL_LOAD_LIGHTHOUSE_CUTSCENE,
    LEVEL_LOAD_FUTURE_FUN_LAND,
};

enum LevelLoadContext {
    LEVEL_CONTEXT_NONE,
    LEVEL_CONTEXT_TRACK_SELECT,
    LEVEL_CONTEXT_RESULTS,
    LEVEL_CONTEXT_TROPHY_ROUND,
    LEVEL_CONTEXT_TROPHY_RESULTS,
    LEVEL_CONTEXT_UNUSED,
    LEVEL_CONTEXT_CHARACTER_SELECT,
    LEVEL_CONTEXT_UNK7,
    LEVEL_CONTEXT_CREDITS
};

enum MenuResult {
    MENU_RESULT_CONTINUE,
    MENU_RESULT_RETURN_TO_GAME,
    MENU_RESULT_UNK2,
    MENU_RESULT_UNK3,
    MENU_RESULT_UNK4,
    MENU_RESULT_TRACKS_MODE,
    MENU_RESULT_UNK6,
    MENU_RESULT_UNK7,
    MENU_RESULT_UNK8,
    MENU_RESULT_UNK9,
    MENU_RESULT_UNK10,
    MENU_RESULT_UNK11,
    MENU_RESULT_UNK12,
    MENU_RESULT_UNK13,
    MENU_RESULT_UNK14,
    MENU_RESULT_UNK15,
    MENU_RESULT_UNK16,
    MENU_RESULT_UNK17,
    MENU_RESULT_UNK18,
};

enum MenuResultFlags {
    MENU_RESULT_FLAGS_0,
    MENU_RESULT_FLAGS_1 = (1 << 0),
    MENU_RESULT_FLAGS_2 = (1 << 1),
    MENU_RESULT_FLAGS_4 = (1 << 2),
    MENU_RESULT_FLAGS_8 = (1 << 3),
    MENU_RESULT_FLAGS_10 = (1 << 4),
    MENU_RESULT_FLAGS_20 = (1 << 5),
    MENU_RESULT_FLAGS_40 = (1 << 6),
    MENU_RESULT_FLAGS_80 = (1 << 7),
    MENU_RESULT_FLAGS_100 = (1 << 8),
    MENU_RESULT_FLAGS_200 = (1 << 9),
};

enum TrackFinishBits {
    RACE_UNATTEMPTED,
    RACE_VISITED = (1 << 0),
    RACE_CLEARED = (1 << 1),
    RACE_CLEARED_SILVER_COINS = (1 << 2),
};

/**
 * Bit 00: Read Eeprom Data flap times
 * Bit 01: Read Eeprom Data course times
 * Bit 02: Read Save File from bits 8 and 9
 * Bit 03: Read All Save Files
 * Bit 04: Write Eeprom Data flap times
 * Bit 05: Write Eeprom Data course times
 * Bit 06: Write Save Data from bits 10 and 11
 * Bit 07: Erase Save File from bits 10 and 11
 * Bit 08: Read Save File Number Part 1 @bug Also Read Eeprom settings
 * Bit 09: Read Save File Number Part 2 @bug Also Write Eeprom Settings
 * Bit 10: Write Save File Number Part 1
 * Bit 11: Write Save File Number Part 2
 */
extern s32 gSaveDataFlags;
#define SAVE_DATA_FLAG_INDEX_VALUE (1 << 0 | 1 << 1) //2 bits for 4 different values

#define SAVE_DATA_FLAG_READ_FLAP_TIMES (1 << 0)
#define SAVE_DATA_FLAG_READ_COURSE_TIMES (1 << 1)
#define SAVE_DATA_FLAG_READ_SAVE_DATA (1 << 2)
#define SAVE_DATA_FLAG_READ_ALL_SAVE_DATA (1 << 3)
#define SAVE_DATA_FLAG_WRITE_FLAP_TIMES (1 << 4)
#define SAVE_DATA_FLAG_WRITE_COURSE_TIMES (1 << 5)
#define SAVE_DATA_FLAG_WRITE_SAVE_DATA (1 << 6)
#define SAVE_DATA_FLAG_ERASE_SAVE_DATA (1 << 7)
#define SAVE_DATA_FLAG_READ_EEPROM_SETTINGS (1 << 8) //@bug Bits 8 and 9 are reused for checking the read save file number
#define SAVE_DATA_FLAG_WRITE_EEPROM_SETTINGS (1 << 9) // ^^
#define SAVE_DATA_FLAG_READ_SAVE_FILE_NUMBER_BITS (1 << 8 | 1 << 9) //These are reused as above
#define SAVE_DATA_FLAG_WRITE_SAVE_FILE_NUMBER_BITS (1 << 10 | 1 << 11)

#define SAVE_DATA_FLAG_READ_EEPROM_INDEX(flags) (flags & (SAVE_DATA_FLAG_READ_FLAP_TIMES | SAVE_DATA_FLAG_READ_COURSE_TIMES))
#define SAVE_DATA_FLAG_WRITE_EEPROM_INDEX(flags) ((flags & (SAVE_DATA_FLAG_WRITE_FLAP_TIMES | SAVE_DATA_FLAG_WRITE_COURSE_TIMES)) >> 4)
#define SAVE_DATA_FLAG_READ_SAVE_FILE_NUMBER(flags) ((flags >> 8) & SAVE_DATA_FLAG_INDEX_VALUE)
#define SAVE_DATA_FLAG_WRITE_SAVE_FILE_NUMBER(flags) ((flags >> 10) & SAVE_DATA_FLAG_INDEX_VALUE)

void thread3_main(UNUSED void *unused);
void init_game(void);
void main_game_loop(void);
void load_next_ingame_level(s32 numPlayers, s32 trackID, Vehicle vehicle);
void load_level_game(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId);
void unload_level_game(void);
void set_drumstick_unlock_transition(void);
void race_postrace_type(s32 arg0);
void func_8006D8F0(s32 arg0);
void func_8006D968(s8 *arg0);
GameMode get_game_mode(void);
void load_menu_with_level_background(s32 menuId, s32 levelId, s32 cutsceneId);
void set_level_default_vehicle(Vehicle vehicleID);
void set_vehicle_id_for_menu(Vehicle vehicleId);
Vehicle get_level_default_vehicle(void);
void load_level_menu(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void unload_level_menu(void);
void update_menu_scene(s32 updateRate);
void load_level_for_menu(s32 levelId, s32 numberOfPlayers, s32 cutsceneId);
void calc_and_alloc_heap_for_settings(void);
void init_racer_headers(void);
void clear_lap_records(Settings *settings, s32 flags);
void clear_game_progress(Settings *settings);
void reset_save_data(void);
Settings *get_settings(void);
s8 is_game_paused(void);
s8 is_postrace_viewport_active(void);
s32 is_reset_pressed(void);
s32 get_ingame_map_id(void);
void mark_to_read_flap_times(void);
void mark_to_read_course_times(void);
void mark_to_read_flap_and_course_times(void);
void mark_read_save_file(s32 saveFileIndex);
void mark_read_all_save_files(void);
void mark_to_write_flap_times(void);
void mark_to_write_course_times(void);
void mark_to_write_flap_and_course_times(void);
void force_mark_write_save_file(s32 saveFileIndex);
void safe_mark_write_save_file(s32 saveFileIndex);
void mark_save_file_to_erase(s32 saveFileIndex);
void mark_read_eeprom_settings(void);
void mark_write_eeprom_settings(void);
s32 check_dmem_validity(void);
void level_transition_begin(s32 type);
void func_8006F20C(void);
void begin_trophy_race_teleport(void);
void begin_lighthouse_rocket_cutscene(void);
void begin_level_teleport(s32 levelID);
void set_pause_lockout_timer(u8 time);
void swap_lead_player(void);
void set_frame_blackout_timer(void);
void pre_intro_loop(void);
s32 is_controller_missing(void);
s32 check_imem_validity(void);
void ingame_logic_loop(s32 updateRate);
void load_level(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void init_level_globals(void);
void alloc_displaylist_heap(s32 numberOfPlayers);
void default_alloc_displaylist_heap(void);
void menu_logic_loop(s32 updateRate);

#endif
