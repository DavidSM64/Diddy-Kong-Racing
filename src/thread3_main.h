#ifndef _THREAD3_MAIN_H_
#define _THREAD3_MAIN_H_

#include "types.h"
#include "macros.h"
#include "structs.h"
#include "game.h"

typedef enum RenderContext {
    DRAW_INTRO = -1,
    DRAW_GAME,
    DRAW_MENU,
    DRAW_UNK_02,
    DRAW_UNK_03,
    DRAW_UNK_04,
    DRAW_CRASH_SCREEN
} RenderContext;

enum LevelLoadType {
    LEVEL_LOAD_NORMAL,
    LEVEL_LOAD_UNK1,
    LEVEL_LOAD_TROPHY_RACE,
    LEVEL_LOAD_LIGHTHOUSE_CUTSCENE,
    LEVEL_LOAD_FUTURE_FUN_LAND,
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
void func_8006CAE4(s32 numPlayers, s32 trackID, Vehicle vehicle);
void load_level_game(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId);
void unload_level_game(void);
void func_8006D8A4(void);
void func_8006D8E0(s32 arg0);
void func_8006D8F0(s32 arg0);
void func_8006D968(s8 *arg0);
RenderContext get_render_context(void);
UNUSED void func_8006DA1C(s32 arg0);
void load_menu_with_level_background(s32 menuId, s32 levelId, s32 cutsceneId);
void set_level_default_vehicle(Vehicle arg0);
void func_8006DB20(Vehicle vehicleId);
Vehicle get_level_default_vehicle(void);
void load_level_menu(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void unload_level_menu(void);
void update_menu_scene(s32 arg0);
void load_level_for_menu(s32 levelId, s32 numberOfPlayers, s32 cutsceneId);
void calc_and_alloc_heap_for_settings(void);
void func_8006E5BC(void);
void func_8006E770(Settings *settings, s32 arg1);
void func_8006E994(Settings *settings);
void func_8006EA58(void);
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
void func_8006F140(s32 arg0);
void func_8006F20C(void);
void begin_trophy_race_teleport(void);
void begin_lighthouse_rocket_cutscene(void);
void begin_level_teleport(s32 arg0);
void func_8006F388(u8 arg0);
void func_8006F398(void);
void set_frame_blackout_timer(void);
void pre_intro_loop(void);
s32 is_controller_missing(void);
s32 check_imem_validity(void);
void ingame_logic_loop(s32 updateRate);
void load_level(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void init_level_globals(void);
void alloc_displaylist_heap(s32 numberOfPlayers);
void default_alloc_displaylist_heap(void);

//Non Matching
void func_8006DCF8(s32 updateRate);

#endif
