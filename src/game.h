#ifndef _GAME_H_
#define _GAME_H_

#include "types.h"
#include "structs.h"
#include "fade_transition.h"
#include "racer.h"
#include "thread3_main.h"

extern Gfx *gDisplayLists[2];
extern s32 sLogicUpdateRate;
extern u8 gOverrideAA;
extern u8 gHideHUD;
extern s32 gMapId;
extern u8 gSkipCutbacks;

struct ConfigOptions {
    s8 antiAliasing;
    s8 screenPosX;
    s8 screenPosY;
    s8 screenMode;
    s8 regionMode;
    s8 frameCap;
    s8 dedither;
    s8 noCutbacks;
};

extern struct ConfigOptions gConfig;

/* Size: 6 bytes */
typedef struct LevelGlobalData {
    s8 world;
    s8 raceType;
    s8 vehicles; // Upper half: available vehicle, Lower half: default vehicle.
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
void func_8006BD10(f32 arg0);
s32 func_8006BD88(void);
u8 get_current_level_race_type(void);
LevelHeader *get_current_level_header(void);
u8 get_total_level_header_count(void);
char *get_level_name(s32 levelId);
void clear_audio_and_track(void);
void func_8006BFC8(s8 *arg0);
void frontCleanupMultiSelect(void);
TempStruct5 *func_8006C18C(void);
s8 func_8006C19C(void);
void push_level_property_stack(s32 levelId, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void pop_level_property_stack(s32 *levelId, s32 *entranceId, s32 *vehicleId, s32 *cutsceneId);
void clear_level_property_stack(void);
s16 get_level_property_stack_pos(void);
s32 func_8006C300(void);

#endif
