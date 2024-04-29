#ifndef ENUMS_H
#define ENUMS_H

#include "sound_ids.h"
#include "sequence_ids.h"
#include "asset_enums.h"

/* All the enums defined here can be used in asset files */

// Alias for brevity.
typedef AssetLevelHeadersEnum MapId;

// There are a few instances of comparing MapId with special, negative values.
typedef enum SpecialMapId {
    SPECIAL_MAP_ID_UNK_NEG10 = -10,
    SPECIAL_MAP_ID_UNK_NEG2 = -2,
    SPECIAL_MAP_ID_NO_LEVEL = -1,
} SpecialMapId;

typedef enum Character {
    CHARACTER_KRUNCH,
    CHARACTER_BUMPER,
    CHARACTER_TIPTUP,
    CHARACTER_CONKER,
    CHARACTER_TIMBER,
    CHARACTER_BANJO,
    CHARACTER_DRUMSTICK,
    CHARACTER_PIPSY,
    CHARACTER_TT,
    CHARACTER_DIDDY,
    NUMBER_OF_CHARACTERS
} Character;

typedef enum Vehicle {
    VEHICLE_CAR,
    VEHICLE_HOVERCRAFT,
    VEHICLE_PLANE,
    VEHICLE_FLYING_CAR,
    VEHICLE_LOOPDELOOP,
    VEHICLE_TRICKY,
    VEHICLE_BLUEY,
    VEHICLE_SMOKEY,
    VEHICLE_PTERODACTYL,
    VEHICLE_SNOWBALL,
    VEHICLE_CARPET,
    VEHICLE_BUBBLER,
    VEHICLE_WIZPIG,
    VEHICLE_ROCKET,
    
    VEHICLE_NO_OVERRIDE = -1, // Only used in Object Maps for the setup point.
    NUMBER_OF_VEHICLE_TYPES,
    NUMBER_OF_PLAYER_VEHICLES = 3
} Vehicle;

typedef enum CameraMode {
    CAMERA_CAR,
    CAMERA_PLANE,
    CAMERA_UNUSED,
    CAMERA_FIXED,
    CAMERA_HOVERCRAFT,
    CAMERA_FINISH_CHALLENGE,
    CAMERA_LOOP,
    CAMERA_FINISH_RACE
} CameraMode;

typedef enum Language {
    LANGUAGE_ENGLISH,
    LANGUAGE_GERMAN,
    LANGUAGE_FRENCH,
    LANGUAGE_JAPANESE
} Language;

typedef enum World {
    WORLD_NONE = -1, // This enum starts at -1 instead of 0.
    WORLD_CENTRAL_AREA,
    WORLD_DINO_DOMAIN,
    WORLD_SHERBET_ISLAND,
    WORLD_SNOWFLAKE_MOUNTAIN,
    WORLD_DRAGON_FOREST,
    WORLD_FUTURE_FUN_LAND
} World;

typedef enum RaceType {
    RACETYPE_DEFAULT           =  0,
    RACETYPE_HORSESHOE_GULCH   =  3,
    RACETYPE_HUBWORLD          =  5,
    RACETYPE_CUTSCENE_1        =  6, // Not sure what the difference between these two are.
    RACETYPE_CUTSCENE_2        =  7,
    RACETYPE_BOSS              =  8,
    RACETYPE_CHALLENGE_BATTLE  = 64,
    RACETYPE_CHALLENGE_BANANAS = 65,
    RACETYPE_CHALLENGE_EGGS    = 66,
    RACETYPE_CHALLENGE         = 0x40 // For masking
} RaceType;

enum BossSetupTypes {
    BOSS_RACE_TRICKY1,
    BOSS_RACE_BLUEY1,
    BOSS_RACE_SMOKEY1,
    BOSS_RACE_TRICKY2,
    BOSS_RACE_BLUEY2,
    BOSS_RACE_BUBBLER1,
    BOSS_RACE_BUBBLER2,
    BOSS_RACE_SMOKEY2,
    BOSS_RACE_WIZPIG1,
    BOSS_RACE_WIZPIG2
};

typedef enum ObjectModelType {
    OBJECT_MODEL_TYPE_3D_MODEL,
    OBJECT_MODEL_TYPE_SPRITE_BILLBOARD,
    OBJECT_MODEL_TYPE_VEHICLE_PART,
    OBJECT_MODEL_TYPE_UNKNOWN3,
    OBJECT_MODEL_TYPE_MISC
} ObjectModelType;

typedef enum WarpFlag {
    WARP_FLAG_NORMAL = -1, // Not a boss warp
    WARP_FLAG_BOSS_1,
    WARP_FLAG_BOSS_2
} WarpFlag;

typedef enum BalloonType {
    BALLOON_TYPE_BOOST,
    BALLOON_TYPE_MISSILE,
    BALLOON_TYPE_TRAP,
    BALLOON_TYPE_SHIELD,
    BALLOON_TYPE_MAGNET
} BalloonType;

typedef enum HorizontalAlignmentFlags {
    HORZ_ALIGN_LEFT   = 0,
    HORZ_ALIGN_RIGHT  = 1,
    HORZ_ALIGN_CENTER = 4
} HorizontalAlignmentFlags;

typedef enum VerticalAlignmentFlags {
    VERT_ALIGN_TOP    = 0,
    VERT_ALIGN_BOTTOM = 2,
    VERT_ALIGN_MIDDLE = 8
} VerticalAlignmentFlags;

typedef enum AlignmentFlags {
    ALIGN_TOP_LEFT      = VERT_ALIGN_TOP    | HORZ_ALIGN_LEFT,
    ALIGN_TOP_CENTER    = VERT_ALIGN_TOP    | HORZ_ALIGN_CENTER,
    ALIGN_TOP_RIGHT     = VERT_ALIGN_TOP    | HORZ_ALIGN_RIGHT,
    ALIGN_MIDDLE_LEFT   = VERT_ALIGN_MIDDLE | HORZ_ALIGN_LEFT,
    ALIGN_MIDDLE_CENTER = VERT_ALIGN_MIDDLE | HORZ_ALIGN_CENTER,
    ALIGN_MIDDLE_RIGHT  = VERT_ALIGN_MIDDLE | HORZ_ALIGN_RIGHT,
    ALIGN_BOTTOM_LEFT   = VERT_ALIGN_BOTTOM | HORZ_ALIGN_LEFT,
    ALIGN_BOTTOM_CENTER = VERT_ALIGN_BOTTOM | HORZ_ALIGN_CENTER,
    ALIGN_BOTTOM_RIGHT  = VERT_ALIGN_BOTTOM | HORZ_ALIGN_RIGHT
} AlignmentFlags;

typedef enum SurfaceType {
    SURFACE_DEFAULT,
    SURFACE_GRASS,
    SURFACE_SAND,
    SURFACE_ZIP_PAD,
    SURFACE_STONE,
    SURFACE_EGG_SPAWN,
    SURFACE_EGG_01,
    SURFACE_EGG_02,
    SURFACE_EGG_03,
    SURFACE_EGG_04,
    SURFACE_FROZEN_WATER,
    SURFACE_UNK0B,
    SURFACE_TAJ_PAD,
    SURFACE_SNOW,
    SURFACE_UNK0E,
    SURFACE_UNK0F,
    SURFACE_UNK10,
    SURFACE_INVIS_WALL,
    SURFACE_UNK12,

    SURFACE_NONE = 255
} SurfaceType;

#endif
