#ifndef _GAME_H_
#define _GAME_H_

#include "types.h"
#include "structs.h"
#include "racer.h"

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

Vehicle leveltable_vehicle_default(s32 mapId);
s32 leveltable_vehicle_usable(s32 mapId);
s8 leveltable_type(s32 mapId);
s8 leveltable_world(s32 mapId);
s32 level_world_id(s32 worldId);
void level_count(s32 *outLevelCount, s32 *outWorldCount);
s32 level_is_race(void);
void level_music_start(f32 tempo);
s32 level_id(void);
u8 level_type(void);
LevelHeader *level_header(void);
u8 level_header_count(void);
char *level_name(s32 levelId);
void level_free(void);
void aitable_init(s8 *aiLevelTable);
void aitable_free(void);
AIBehaviourTable *aitable_get(void);
s8 race_is_adventure_2P(void);
void level_properties_push(s32 levelId, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void level_properties_pop(s32 *levelId, s32 *entranceId, s32 *vehicleId, s32 *cutsceneId);
void level_properties_reset(void);
s16 level_properties_get(void);
s32 func_8006C300(void);

#endif
