#ifndef _GAME_H_
#define _GAME_H_

#include "types.h"
#include "structs.h"
#include "fade_transition.h"
#include "racer.h"
#include "thread3_main.h"

/* Size: 6 bytes */
typedef struct LevelGlobalData {
    s8 world;
    s8 raceType;
    s8 vehicles; // Upper half: available vehicle, Lower half: default vehicle.
    s8 unk3; // Unused.
    s16 unk4; // Unused.
} LevelGlobalData;

enum NumberOfPlayers {
    ZERO_PLAYERS  = -1, // A.I. Only
    ONE_PLAYER    = 0,
    TWO_PLAYERS   = 1,
    THREE_PLAYERS = 2,
    FOUR_PLAYERS  = 3
};

enum CutsceneIDs {
    CUTSCENE_ID_NONE   = 0,
    CUTSCENE_ID_UNK_3  = 3,
    CUTSCENE_ID_UNK_5  = 5,
    CUTSCENE_ID_UNK_7  = 7,
    CUTSCENE_ID_UNK_A  = 0x0A,
    CUTSCENE_ID_UNK_64 = 0x64
};

Vehicle get_map_default_vehicle(s32 mapId);
s32 get_map_available_vehicles(s32 mapId);
s8 get_map_race_type(s32 mapId);
s8 get_map_world_id(s32 mapId);
s32 get_hub_area_id(s32 worldId);
void get_number_of_levels_and_worlds(s32 *outLevelCount, s32 *outWorldCount);
s32 check_if_in_race(void);
void start_level_music(f32 tempo);
s32 get_current_map_id(void);
u8 get_current_level_race_type(void);
LevelHeader *get_current_level_header(void);
u8 get_total_level_header_count(void);
char *get_level_name(s32 levelId);
void clear_audio_and_track(void);
void set_ai_level(s8 *aiLevelTable);
void free_ai_behaviour_table(void);
AIBehaviourTable *get_ai_behaviour_table(void);
s8 is_two_player_adventure_race(void);
void push_level_property_stack(s32 levelId, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void pop_level_property_stack(s32 *levelId, s32 *entranceId, s32 *vehicleId, s32 *cutsceneId);
void clear_level_property_stack(void);
s16 get_level_property_stack_pos(void);
s32 func_8006C300(void);

#endif
