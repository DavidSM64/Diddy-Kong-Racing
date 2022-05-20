#ifndef ENUMS_H
#define ENUMS_H

/* All the enums defined here can be used in asset files */

typedef enum Vehicle {
    VEHICLE_CAR,
    VEHICLE_HOVERCRAFT,
    VEHICLE_PLANE,

    NUMBER_OF_VEHICLE_TYPES
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
    RACETYPE_CHALLENGE        = 64, // For masking
    RACETYPE_CHALLENGE_BATTLE  = 64,
    RACETYPE_CHALLENGE_BANANAS = 65,
    RACETYPE_CHALLENGE_EGGS    = 66
} RaceType;

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
    ALIGN_TOP_LEFT      = VERT_ALIGN_TOP | HORZ_ALIGN_LEFT,
    ALIGN_TOP_CENTER    = VERT_ALIGN_TOP | HORZ_ALIGN_CENTER,
    ALIGN_TOP_RIGHT     = VERT_ALIGN_TOP | HORZ_ALIGN_RIGHT,
    ALIGN_MIDDLE_LEFT   = VERT_ALIGN_MIDDLE | HORZ_ALIGN_LEFT,
    ALIGN_MIDDLE_CENTER = VERT_ALIGN_MIDDLE | HORZ_ALIGN_CENTER,
    ALIGN_MIDDLE_RIGHT  = VERT_ALIGN_MIDDLE | HORZ_ALIGN_RIGHT,
    ALIGN_BOTTOM_LEFT   = VERT_ALIGN_BOTTOM | HORZ_ALIGN_LEFT,
    ALIGN_BOTTOM_CENTER = VERT_ALIGN_BOTTOM | HORZ_ALIGN_CENTER,
    ALIGN_BOTTOM_RIGHT  = VERT_ALIGN_BOTTOM | HORZ_ALIGN_RIGHT
} AlignmentFlags;

#endif
