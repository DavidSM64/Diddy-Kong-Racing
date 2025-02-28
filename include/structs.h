#ifndef _STRUCTS_H_
#define _STRUCTS_H_

/* Note: Structs are not complete, take them with a grain of salt. */

#include "types.h"
#include "enums.h"
#include "level_object_entries.h"
#include "object_properties.h"

// Stolen from PD
// This hacky structure allows coords to be accessed using
// coord->x, coord->y and coord->z, but also as
// coord->f[0], coord->f[1] and coord->f[2].
// In some places code only matches when using the float array.
typedef struct Vec3f {
  union {
    struct {
      f32 x;
      f32 y;
      f32 z;
    };
    f32 f[3];
  };
} Vec3f;

typedef struct Vec3s {
  union {
    struct {
      s16 y_rotation;
      s16 x_rotation;
      s16 z_rotation;
    };
    struct {
      s16 x;
      s16 y;
      s16 z;
    };
    s16 s[3];
  };
} Vec3s;

typedef struct Vec3i {
  union {
    struct {
      s32 x;
      s32 y;
      s32 z;
    };
    s32 i[3];
  };
} Vec3i;

typedef struct Vec4f {
  union {
    struct {
      f32 x;
      f32 y;
      f32 z;
      f32 w;
    };
    f32 f[4];
  };
} Vec4f;

/* Size: 0x24 / 36 bytes */
typedef struct SoundMask {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ u16 soundId;
    /* 0x0E */ u8 volume;
    /* 0x0F */ u8 pitch;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x14 */ s32 distance;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ struct SoundMask **soundMask;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
} SoundMask;

/* Size: 0x20 bytes */
typedef struct TextureHeader {
  /* 0x00 */ u8 width;
  /* 0x01 */ u8 height;
  /* 0x02 */ u8 format; // Lower 4 bits determines image format.
      // 0 = RGBA32
      // 1 = RGBA16
      // 2 = I8
      // 3 = I4
      // 4 = IA16
      // 5 = IA8
      // 6 = IA4
      // 7 = CI4 (16 colors)
      // 8 = CI8 (64 colors)
  /* 0x03 */ s8 unk3;
  /* 0x04 */ s8 unk4;
  /* 0x05 */ u8 numberOfInstances; // Always 1 in the ROM.
  /* 0x06 */ s16 flags;
      // 0x04 = Interlaced texture
      // 0x40 = U clamp flag. 0 = Wrap, 1 = Clamp
      // 0x80 = V clamp flag. 0 = Wrap, 1 = Clamp
  /* 0x08 */ s16 ciPaletteOffset;
  /* 0x0A */ s16 numberOfCommands; // initialized in RAM; Number of commands in the texture display list. (Usually 0x07)
  /* 0x0C */ s32 *cmd; // initialized in RAM; Pointer to texture display list.
  /* 0x10 */ u8 unk10;
  /* 0x11 */ u8 unk11;
  /* 0x12 */ u16 numOfTextures; // For animated textures, static textures are just 0x01. Each texture has it's own header.
  /* 0x14 */ u16 frameAdvanceDelay; // How many frames to delay before moving to the next texture.
  /* 0x16 */ s16 textureSize; // Size in number of bytes, including the header
  /* 0x18 */ u8 unk18;
  /* 0x19 */ u8 unk19;
  /* 0x1A */ u8 unk1A;
  /* 0x1B */ u8 unk1B;
  /* 0x1C */ u8 unk1C;
  /* 0x1D */ u8 isCompressed;
  /* 0x1E */ u8 unk1E;
  /* 0x1F */ u8 unk1F;
} TextureHeader;

// Probably not unique to the boot menu.
typedef struct DrawTexture {
    TextureHeader *texture; // Pointer to texture to draw.
    s16 xOffset; // Offset from the center of the screen.
    s16 yOffset; // Offset from the center of the screen.
} DrawTexture;

typedef struct Sprite {
  /* 0x00 */ s16 baseTextureId;
  /* 0x02 */ s16 numberOfFrames; // 1 means static texture
  /* 0x04 */ s16 numberOfInstances;
  /* 0x06 */ s16 unk6;
  /* 0x08 */ TextureHeader **frames;
  union {
    /* 0x0C */ u8 val[1]; // Actual size varies.
    /* 0x0C */ u8 *ptr[1]; // Display list?
  } unkC;
} Sprite;

/* Size: 0x20 bytes */
typedef struct MenuElement {
  // Element Position
  /* 0x00 */ s16 left; // Where the element spawns on entry.
  /* 0x02 */ s16 top;
  /* 0x04 */ s16 center; // Value of where the element moves to after entry
  /* 0x06 */ s16 middle;
  /* 0x08 */ s16 right; // Value of where the element moves to after exit
  /* 0x0A */ s16 bottom;
  // Element Color/Transparency
  /* 0x0C */ u8 filterRed;
  /* 0x0D */ u8 filterGreen;
  /* 0x0E */ u8 filterBlue;
  /* 0x0F */ u8 filterBlendFactor; // 0 = no filter color, 0xFF = full color.
  /* 0x10 */ u8 opacity;
  // Element Properties
  /* 0x11 */ u8 textFont;
  /* 0x12 */ u8 textAlignFlags;
  // Element Type
  /* 0x13 */ u8 elementType; // Source type? 0 = ascii text, 2 = number, 7 = texture
  union {
  /* 0x14 */ void *element;   // Generic pointer
  /* 0x14 */ char *asciiText; // Pointer to ascii text to be displayed on the screen.
  /* 0x14 */ TextureHeader *texture;    // Pointer to texture to be displayed on the screen.
  /* 0x14 */ DrawTexture *drawTexture;    // Pointer to texture to be displayed on the screen.
  /* 0x14 */ s32 *number;     // Pointer to a number to be displayed on the screen.
  /* 0x14 */ u16 *numberU16;  // Pointer to a number to be displayed on the screen.
  /* 0x14 */ s32 assetID;       // Some value for elementType == 5
  } t;
  union {
    struct {
        // Element Background Color/Transparency
        /* 0x18 */ s16 backgroundRed;
        /* 0x1A */ s16 backgroundGreen;
        /* 0x1C */ s16 backgroundBlue;
        /* 0x1E */ s16 backgroundAlpha; // 0x0000 = No background, 0x00FF = full background color.
    } background;
    struct {        
        // Texture Size
        /* 0x18 */ s16 width;
        /* 0x1A */ s16 height;
        /* 0x1C */ s16 borderWidth;
        /* 0x1E */ s16 borderHeight;
    } texture;
  } details;
} MenuElement;

#define TEX_FORMAT_RGBA32 0
#define TEX_FORMAT_RGBA16 1
#define TEX_FORMAT_I8     2
#define TEX_FORMAT_I4     3
#define TEX_FORMAT_IA16   4
#define TEX_FORMAT_IA8    5
#define TEX_FORMAT_IA4    6
#define TEX_FORMAT_CI4    7
#define TEX_FORMAT_CI8    8

/* Size: 0x18 bytes */
typedef struct Racer {
  /* 0x00 */ u32 trophy_points;
  /* 0x04 */ s8 best_times;
  /* 0x05 */ s8 character;
  /* 0x06 */ s8 starting_position;
  /* 0x07 */ s8 unk7;
  /* 0x08 */ u16 placements[4];
  /* 0x10 */ u16 course_time;
  /* 0x12 */ u16 lap_times[3];
} Racer;

/* Unknown Size */
typedef struct Settings4C {
    u8 courseID; //courseId?
    u8 unk1; // This value + 8 is cutsceneId index? gGameCurrentCutscene = gLevelSettings[gLevelSettings[1] + 8];
    s8 mapID; //mapId?
    u8 pad3[0xC];
    u8 entranceID; //entranceId?
} Settings4C;

#define TAJ_FLAGS_CAR_CHAL_UNLOCKED    0x01
#define TAJ_FLAGS_HOVER_CHAL_UNLOCKED  0x02
#define TAJ_FLAGS_PLANE_CHAL_UNLOCKED  0x04
#define TAJ_FLAGS_UNLOCKED_A_CHALLENGE  (TAJ_FLAGS_CAR_CHAL_UNLOCKED | TAJ_FLAGS_HOVER_CHAL_UNLOCKED | TAJ_FLAGS_PLANE_CHAL_UNLOCKED)
#define TAJ_FLAGS_CAR_CHAL_COMPLETED   0x08
#define TAJ_FLAGS_HOVER_CHAL_COMPLETED 0x10
#define TAJ_FLAGS_PLANE_CHAL_COMPLETED 0x20

#define CUTSCENE_NONE                      0x0
#define CUTSCENE_LIGHTHOUSE_ROCKET         0x1
#define CUTSCENE_TT_HELP                   0x2
#define CUTSCENE_ADVENTURE_TWO             0x4
#define CUTSCENE_DINO_DOMAIN_BOSS          0x8
#define CUTSCENE_SHERBET_ISLAND_BOSS       0x10
#define CUTSCENE_SNOWFLAKE_MOUNTAIN_BOSS   0x20
#define CUTSCENE_DRAGON_FOREST_BOSS        0x40
#define CUTSCENE_FUTURE_FUN_LAND_BOSS      0x80
#define CUTSCENE_DINO_DOMAIN_BOSS_2        0x100
#define CUTSCENE_SHERBET_ISLAND_BOSS_2     0x200
#define CUTSCENE_SNOWFLAKE_MOUNTAIN_BOSS_2 0x400
#define CUTSCENE_DRAGON_FOREST_BOSS_2      0x800
#define CUTSCENE_WIZPIG_FACE               0x2000
#define CUTSCENE_DINO_DOMAIN_KEY           0x4000
#define CUTSCENE_SHERBET_ISLAND_KEY        0x8000
#define CUTSCENE_SNOWFLAKE_MOUNTAIN_KEY    0x10000
#define CUTSCENE_DRAGON_FOREST_KEY         0x20000

/* Size: 0x118 bytes */
typedef struct Settings {
  // Balloon indices:
  // 0 = Total balloons
  // 1 = Dino Domain balloons
  // 2 = Sherbet Island balloons
  // 3 = Snowflake Mountain balloons
  // 4 = Dragon Forest balloons
  // 5 = Future Fun Land balloons
  /* 0x0000 */ s16 *balloonsPtr;

  // Course flag bits:
  // 0x1                   = Map has been visited.
  // 0x2                   = Map has been completed.
  // 0x4                   = Map's silver coin challenge has been completed.
  // 0x00000000-0xFFFF0000 = Used as bit fields for hub worlds to indicate whether or not a door can open when the player gets near it.
  /* 0x0004 */ s32 *courseFlagsPtr;

  // Key bits:
  // 0x02 = Dino Domain key
  // 0x04 = Sherbet Island key
  // 0x08 = Snowflake Mountain key
  // 0x10 = Dragon Forest key
  /* 0x0008 */ u16 keys;

  /* 0x000A */ u16 unkA;

  // Boss bits:
  // 0x001 = Wizpig 1
  // 0x002 = Tricky 1
  // 0x004 = Bubbler 1
  // 0x008 = Bluey 1
  // 0x010 = Smokey 1
  // 0x020 = Wizpig 2
  // 0x080 = Tricky 2
  // 0x100 = Bubbler 2
  // 0x200 = Bluey 2
  // 0x400 = Smokey 2
  /* 0x000C */ u16 bosses;

  // Trophy bits:
  // Bit field 0b00-0b11 = Empty, 3rd, 2nd, and 1st place trophies.
  // `trophies` consists of 5 of these bit fields, from LSB to MSB, Dino, Sherbet, Snowflake, Dragon, and FFL.
  /* 0x000E */ u16 trophies;

  // Cutscene flags:
  // 0x1     = Lighthouse rocket cutscene
  // 0x2     = T.T. help prompt
  // 0x4     = Adventure 2 flag?
  // 0x8     = Dino domain boss cutscene
  // 0x10    = Sherbet island boss cutscene
  // 0x20    = Snowflake mountain boss cutscene
  // 0x40    = Dragon forest boss cutscene
  // 0x80    = Future Fun Land boss cutscene
  // 0x100   = Dino domain boss cutscene 2
  // 0x200   = Shertbet island boss cutscene 2
  // 0x400   = Snowflake mountain boss cutscene 2
  // 0x800   = Dragon forest boss cutscene 2
  // 0x2000  = Wizpig face cutscene
  // 0x4000  = Dino domain key cutscene
  // 0x8000  = Sherbet Island key cutscene
  // 0x10000 = Snowflake mountain key cutscene
  // 0x20000 = Dragon forest key cutscene
  /* 0x0010 */ u32 cutsceneFlags;
  
  // Taj flags:
  // 0x1  = Car challenge unlocked
  // 0x2  = Hover challenge unlocked
  // 0x4  = Plane challenge unlocked
  // 0x8  = Car challenge completed
  // 0x10 = Hover challenge completed
  // 0x20 = Plane challenge completed
  /* 0x0014 */ u16 tajFlags;
  
  // Not a bitfield, just a  counter from 0-4.
  /* 0x0016 */ u8 ttAmulet;
  
  // Not a bitfield, just a  counter from 0-4.
  /* 0x0017 */ u8 wizpigAmulet;

  /* 0x0018 */ u16 *flapInitialsPtr[3];
  /* 0x0024 */ u16 *flapTimesPtr[3];
  /* 0x0030 */ u16 *courseInitialsPtr[3];
  /* 0x003C */ u16 *courseTimesPtr[3];
  /* 0x0048 */ u8 worldId;
  /* 0x0049 */ u8 courseId;
  /* 0x004A */ u8 gNumRacers;
  /* 0x004B */ u8 newGame;
  /* 0x004C */ Settings4C *unk4C;
  /* 0x0050 */ u32 filename;
  /* 0x0054 */ Racer racers[8];
  /* 0x0114 */ s8 timeTrialRacer;
  /* 0x0115 */ s8 unk115[2];
  /* 0x0117 */ s8 display_times;
} Settings;

/* Size: 8 bytes */
typedef struct LevelHeader_70_18 {
    s32 unk0; //0x0000001E
    u8 red; //0xFF
    u8 green; //0x70
    u8 blue; //0x00
    u8 alpha; //0xFF
} LevelHeader_70_18;

/* Unknown size */
typedef struct LevelHeader_70 {
  /* 0x00 */ s32 unk0;  //0x00000004
  /* 0x04 */ s32 unk4;  //0x00000000
  /* 0x08 */ s32 unk8;  //0x00000000
  /* 0x0C */ s32 unkC;  //0x00000000
  /* 0x10 */ u8 red;    //0x72
  /* 0x11 */ u8 green;  //0x75
  /* 0x12 */ u8 blue;   //0x73
  /* 0x13 */ u8 alpha;  //0x20
  /* 0x14 */ u8 red2;   //0xFF
  /* 0x15 */ u8 green2; //0x00
  /* 0x16 */ u8 blue2;  //0x00
  /* 0x17 */ u8 alpha2; //0xFF
  /* 0x18 */ LevelHeader_70_18 unk18[1]; // Actual length depends on unk0
} LevelHeader_70;

// Used to update the pulsating lights in Spaceport Alpha
typedef struct PulsatingLightDataFrame {
    u16 value;
    u16 time;
} PulsatingLightDataFrame;

typedef struct PulsatingLightData {
    u16 numberFrames;
    u16 currentFrame;
    u16 time;
    u16 totalTime;
    s32 outColorValue;
    PulsatingLightDataFrame frames[1]; // Length varies based on numberFrames.
} PulsatingLightData;

/* Size: 0xC4 bytes */
typedef struct LevelHeader {
  /* 0x00 */ s8 world;
  /* 0x01 */ u8 unk1;
  /* 0x02 */ s8 unk2;
  /* 0x03 */ s8 unk3;
  /* 0x04 */ s8 unk4[4];
  /* 0x08 */ f32 course_height;
  /* 0x0C */ u8 unkC[10];
  /* 0x16 */ u8 unk16[10];
  /* 0x20 */ s8 *AILevelTable;

  /* 0x24 */ u8 pad24[6];
  /* 0x2A */ u8 unk2A;
  /* 0x2B */ u8 pad2B[9];

  /* 0x34 */ s16 geometry;
  /* 0x36 */ s16 collectables; // Objects such as bananas, balloons, etc.
  /* 0x38 */ s16 skybox;

  // Fog related?
  /* 0x3A */ s16 fogNear;
  /* 0x3C */ s16 fogFar;
  /* 0x3E */ s16 fogR;
  /* 0x40 */ s16 fogG;
  /* 0x42 */ s16 fogB;

  /* 0x44 */ u8 unk44[0x5];

  /* 0x49 */ s8 skyDome;
  /* 0x4A */ s8 playerIndex;
  /* 0x4B */ s8 laps;
  /* 0x4C */ s8 race_type;
  /* 0x4D */ s8 vehicle;
  /* 0x4E */ s8 available_vehicles;

  /* 0x4F */ s8 unk4F[3];

  /* 0x52 */ u8 music;
  /* 0x53 */ u8 unk53;
  /* 0x54 */ u16 instruments;
  /* 0x56 */ u8 unk56;
  /* 0x57 */ u8 unk57;
  /* 0x58 */ u8 unk58;
  /* 0x59 */ u8 unk59;
  /* 0x5A */ s16 unk5A;
  /* 0x5C */ u8 unk5C;
  /* 0x5D */ u8 unk5D;
  /* 0x5E */ s16 unk5E;
  /* 0x60 */ s16 unk60;
  /* 0x62 */ s16 wavePower;
  /* 0x64 */ s16 unk64; // Some form of secondary power
  /* 0x66 */ s16 unk66;
  /* 0x68 */ s16 unk68;
  /* 0x6A */ u8 unk6A;
  /* 0x6B */ u8 unk6B;
  /* 0x6C */ s8 unk6C;
  /* 0x6D */ s8 unk6D;
  /* 0x6E */ s16 unk6E;

    //func_800B8134 Seems to use this struct, and it differs on unk70 only.
    union {
  /* 0x70 */ LevelHeader_70 *unk70;
        struct {
  /* 0x70 */ u8 unk70_u8;
  /* 0x71 */ u8 unk71;
        };
    };

  /* 0x74 */ LevelHeader_70 *unk74[7];

  // Weather related?
  /* 0x90 */ s16 weatherEnable; // This affects snow density, but for rain, it simply needs to be nonzero.
  /* 0x92 */ s16 weatherType;
  /* 0x94 */ u8 weatherIntensity;
  /* 0x95 */ u8 weatherOpacity;
  /* 0x96 */ s16 weatherVelX;
  /* 0x98 */ s16 weatherVelY;
  /* 0x9A */ s16 weatherVelZ;

  /* 0x9C */ s8 cameraFOV; // Must be a value within [0, 90]
  /* 0x9D */ u8 bgColorRed;
  /* 0x9E */ u8 bgColorGreen;
  /* 0x9F */ u8 bgColorBlue;
  /* 0xA0 */ s16 unkA0;
  /* 0xA2 */ s8 unkA2;
  /* 0xA3 */ s8 unkA3;
  /* 0xA4 */ TextureHeader *unkA4;
  /* 0xA8 */ s16 unkA8;
  /* 0xAA */ s16 unkAA;
  /* 0xAC */ PulsatingLightData *pulseLightData;

  /* 0xB0 */ s16 unkB0;
  /* 0xB2 */ u8 unkB2;
  /* 0xB3 */ u8 voiceLimit;
  /* 0xB4 */ u8 unkB4;
  /* 0xB5 */ u8 unkB5;
  /* 0xB6 */ u8 unkB6;
  /* 0xB7 */ u8 unkB7;
  /* 0xB8 */ s8 bossRaceID;
  /* 0xB9 */ u8 unkB9;
  /* 0xBA */ s16 unkBA;
  /* 0xBC */ u8 unkBC;
  /* 0xBD */ s8 unkBD;
  // Multiplayer gradient background
  /* 0xBE */ u8 BGColourBottomR;
  /* 0xBF */ u8 BGColourBottomG;
  /* 0xC0 */ u8 BGColourBottomB;
  /* 0xC1 */ u8 BGColourTopR;
  /* 0xC2 */ u8 BGColourTopG;
  /* 0xC3 */ u8 BGColourTopB;
} LevelHeader;

/* Size: 0x50 bytes */
typedef struct {
  /* 0x00 */ u32 unk00;
  /* 0x04 */ u32 unk04;
  /* 0x08 */ u32 unk08;
  /* 0x0C */ f32 unk0C;
  /* 0x10 */ u32 unk10;
  /* 0x14 */ u32 unk14;
  /* 0x18 */ f32 unk18;
  /* 0x1C */ u32 unk1C;
  /* 0x20 */ u32 unk20;
  /* 0x24 */ u32 unk24;
  /* 0x28 */ u32 unk28;
  /* 0x2C */ u32 unk2C;
  /* 0x30 */ u32 unk30;
  /* 0x34 */ u32 unk34;
  /* 0x38 */ u32 unk38;
  /* 0x3C */ u32 unk3C;
  /* 0x40 */ f32 unk40;
  /* 0x44 */ f32 unk44;
  /* 0x48 */ f32 unk48;
  /* 0x4C */ u32 unk4C;
} dkr_wave_t;

/* Size: 8 bytes */
typedef struct TextureInfo {
/* 0x00 */ TextureHeader *texture;
/* 0x04 */ u8 width;
/* 0x05 */ u8 height;
/* 0x06 */ u8 format;
/* 0x07 */ u8 unk7;
} TextureInfo;

/* Size: 10 bytes */
typedef struct Vertex {
/* 0x00 */ s16 x;
/* 0x02 */ s16 y;
/* 0x04 */ s16 z;
/* 0x06 */ u8  r;
/* 0x07 */ u8  g;
/* 0x08 */ u8  b;
/* 0x09 */ u8  a;
} Vertex;

/* Size: 4 bytes */
typedef struct TexCoords {
    union {
      struct {
        s16 u, v;
      };
      u32 texCoords; // For convenience?
    };
} TexCoords;

#define BACKFACE_CULL 0x00
#define BACKFACE_DRAW 0x40

/* Size: 0x10 bytes */
typedef struct Triangle {
    union {
        struct {
            /* 0x00 */ u8 flags; // 0x40 = Draw backface, 0x00 = Cull backface
            /* 0x01 */ u8 vi0;          // First vertex index
            /* 0x02 */ u8 vi1;          // Second vertex index
            /* 0x03 */ u8 vi2;          // Third vertex index
        };
    /* 0x00 */ u32 vertices; // For convenience?
               u8 verticesArray[4];
    };
/* 0x04 */ TexCoords uv0;   // Texture coordinates for the first vertex
/* 0x08 */ TexCoords uv1;   // Texture coordinates for the second vertex
/* 0x0C */ TexCoords uv2;   // Texture coordinates for the third vertex
} Triangle;

/* Size: 12 bytes */
typedef struct TriangleBatchInfo {
/* 0x00 */ u8  textureIndex; // 0xFF = No texture
/* 0x01 */ s8  unk1;
/* 0x02 */ s16 verticesOffset;
/* 0x04 */ s16 facesOffset;
/* 0x06 */ u8  unk6; // 0xFF = vertex colors, otherwise use dynamic lighting normals (Objects only)
/* 0x07 */ u8  unk7;
/* 0x08 */ u32 flags;
    // 0x00000002 = ???
    // 0x00000008 = ???
    // 0x00000010 = Depth write
    // 0x00000100 = Hidden/Invisible geometry
    // 0x00000200 = ??? Used in func_80060AC8
    // 0x00000800 = ???
    // 0x00002000 = ???
    // 0x00008000 = Environment mapping
    // 0x00010000 = Texture is animated
    // 0x00040000 = Has pulsating light data.
    // 0x70000000 = bits 28, 29, & 30 are some kind of index. Not used in any levels.
} TriangleBatchInfo;

/* Size: 8 bytes */
typedef struct ObjectModel_44 {
    union {
/* 0x00 */ s32 *anim;
/* 0x00 */ u8 *animData;
    };
/* 0x04 */ s32 unk4; // Number of frames in animation?
} ObjectModel_44;

typedef struct ObjectModel {
    /* 0x00 */ TextureInfo* textures;
    /* 0x04 */ Vertex* vertices;
    /* 0x08 */ Triangle* triangles;
    /* 0x0C */ s32* unkC;
    /* 0x10 */ s32* unk10;
    /* 0x14 */ s16 *unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 *unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 numberOfTextures;
    /* 0x24 */ s16 numberOfVertices;
    /* 0x26 */ s16 numberOfTriangles;
    /* 0x28 */ s16 numberOfBatches;
    /* 0x2A */ u8 pad2A[4];
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ char pad2F[1];
    /* 0x30 */ s16 references;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ TriangleBatchInfo* batches;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s32* unk40;
    /* 0x44 */ ObjectModel_44* animations;
    /* 0x48 */ s16 numberOfAnimations;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s32 *unk4C;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
} ObjectModel;      

/* Size: 0x44 bytes */
typedef struct LevelModelSegment {
/* 0x00 */ Vertex *vertices;
/* 0x04 */ Triangle *triangles;
/* 0x08 */ s32 unk8;
/* 0x0C */ TriangleBatchInfo *batches;
/* 0x10 */ s16 *unk10;
/* 0x14 */ u16 *unk14;
/* 0x18 */ f32 *unk18;
/* 0x1C */ s16 numberOfVertices;
/* 0x1E */ s16 numberOfTriangles;
/* 0x20 */ s16 numberOfBatches;
           u8 pad22[0x06];
/* 0x28 */ s16 unk28;
/* 0x2A */ s8 unk2A;
/* 0x2B */ s8 hasWaves;
/* 0x2C */ Vertex *unk2C;
/* 0x30 */ s16 unk30;
/* 0x32 */ s16 unk32;
           s16 *unk34;
/* 0x38 */ s16 unk38;
           u8 pad3A[2];
/* 0x3C */ s32 unk3C;
/* 0x40 */ u8 numberofOpaqueBatches;
           u8 pad41[0x3];
} LevelModelSegment;

typedef struct LevelModelSegmentBoundingBox {
    /* 0x00 */ s16 x1;
    /* 0x02 */ s16 y1;
    /* 0x04 */ s16 z1;
    /* 0x06 */ s16 x2;
    /* 0x08 */ s16 y2;
    /* 0x0A */ s16 z2;
} LevelModelSegmentBoundingBox;

/* Size: 8 bytes */
typedef struct BspTreeNode {
/* 0x00 */ s16 leftNode;   // less than split value
/* 0x02 */ s16 rightNode;  // greater or equal to split value?
/* 0x04 */ u8  splitType;  // 0 = Camera X, 1 = Camera Y, 2 = Camera Z
/* 0x05 */ u8  segmentIndex;
/* 0x06 */ s16 splitValue; // Decides left or right
} BspTreeNode;

typedef struct LevelModel {
/* 0x00 */ TextureInfo *textures;
/* 0x04 */ LevelModelSegment *segments;
/* 0x08 */ LevelModelSegmentBoundingBox *segmentsBoundingBoxes;
/* 0x0C */ u8 *unkC; //Unused? 
/* 0x10 */ u8 *segmentsBitfields;
/* 0x14 */ BspTreeNode *segmentsBspTree;
/* 0x18 */ s16 numberOfTextures;
/* 0x1A */ s16 numberOfSegments;
/* 0x1C */ s16 unk1C; // Unused? 
/* 0x1E */ s16 numberOfAnimatedTextures;
/* 0x20 */ s32 minimapSpriteIndex;
/* 0x24 */ u16 minimapRotation; // angle for icons on minimap?
/* 0x26 */ u16 unk26; // Unused? Common values: 0x0009, 0xFFFF, 0x0303
/* 0x28 */ f32 minimapXScale;
/* 0x2C */ f32 minimapYScale;
/* 0x30 */ s16 minimapOffsetXAdv1; // minimap X offset (Adventure 1)
/* 0x32 */ s16 minimapOffsetYAdv1; // minimap Y offset (Adventure 1)         
/* 0x34 */ s16 minimapOffsetXAdv2; // minimap X offset (Adventure 2)
/* 0x36 */ s16 minimapOffsetYAdv2; // minimap Y offset (Adventure 2)
/* 0x38 */ u32 minimapColor;
/* 0x3C */ s16 lowerXBounds;
/* 0x3E */ s16 upperXBounds;
/* 0x40 */ s16 lowerYBounds;
/* 0x42 */ s16 upperYBounds;
/* 0x44 */ s16 lowerZBounds;
/* 0x46 */ s16 upperZBounds;
/* 0x48 */ s32 modelSize;
} LevelModel;

typedef struct ObjHeaderParticleEntry {
  /* 0x00 */ s32 upper;
  /* 0x04 */ s32 lower;
} ObjHeaderParticleEntry;

// Size: 0x18 bytes
typedef struct ObjectHeader24 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u16 unk6; //Misc Asset Id?
    union {
        u32 unk8;
        struct {
            u8 unk8A;
            u8 unk9;
            u8 unkA;
            u8 unkB;
        };
    };
    s16 homeX;
    s16 homeY;
    s16 homeZ;
    u16 radius;
    u16 unk14;
    u16 unk16;
} ObjectHeader24;

typedef struct ObjectHeader {
  /* 0x00 */ s32 unk0; // The one use I've seen for this so far is water effect animation speed.
  /* 0x04 */ f32 shadowScale;
  /* 0x08 */ f32 unk8;
  /* 0x0C */ f32 scale;
  /* 0x10 */ s32 *modelIds;
  /* 0x14 */ s32 *vehiclePartIds;
  /* 0x18 */ s8 *vehiclePartIndices;
  /* 0x1C */ ObjHeaderParticleEntry *objectParticles;
             s32 pad20;
  /* 0x24 */ ObjectHeader24 *unk24;
  /* 0x28 */ f32 shadeBrightness;
  /* 0x2C */ f32 shadeAmbient;
  /* 0x30 */ u16 flags;
  /* 0x32 */ s16 shadowGroup;
  /* 0x34 */ s16 unk34;
  /* 0x36 */ s16 waterEffectGroup;
  /* 0x38 */ s16 unk38;
  /* 0x3A */ u8 unk3A;
  /* 0x3B */ u8 unk3B;
  /* 0x3C */ u8 unk3C;
  /* 0x3D */ u8 unk3D;
  /* 0x3E */ s16 shadeAngleY;
  /* 0x40 */ s16 shadeAngleZ;
  /* 0x42 */ s16 unk42;
  /* 0x44 */ s16 unk44;
  /* 0x48 */ s16 unk46;
  /* 0x48 */ s16 unk48;
  /* 0x4A */ s16 unk4A;
  /* 0x4C */ s16 unk4C;
  /* 0x4E */ s16 drawDistance;
  /* 0x50 */ s16 unk50;
  /* 0x52 */ s8 unk52;
  /* 0x53 */ s8 modelType;
  /* 0x54 */ s8 behaviorId;
  /* 0x55 */ s8 numberOfModelIds; // size of array pointed by Object->unk68
  /* 0x56 */ s8 unk56;
  /* 0x57 */ s8 particleCount; // Number of different particle types that are attached
  /* 0x58 */ s8 unk58;
  /* 0x59 */ u8 pad59;
  /* 0x5A */ s8 numLightSources;
  /* 0x5B */ u8 unk5B;
  /* 0x5C */ u8 unk5C;
  /* 0x5D */ u8 unk5D; //Misc Asset index?
  /* 0x5E */ u8 pad5E[0x2];
  /* 0x60 */ char internalName[16];
  /* 0x70 */ u8 unk70;
  /* 0x71 */ u8 unk71;
  /* 0x72 */ u8 unk72;
             u8 pad73[0x5];
} ObjectHeader;

typedef struct Object_44_0 {
    u8 unk0;
    u8 unk1;
} Object_44_0;

typedef struct Object_44_C {
    u8 pad0[0x4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8  pad10[0x6];
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
} Object_44_C;

typedef struct Object_44 {
    Object_44_0 *unk0;
    u8  pad4[8];
    Object_44_C *unkC;
} Object_44;

typedef struct ObjectInteraction {
 /* 0x00 */ struct Object *obj;
 /* 0x04 */ f32 x_position;
 /* 0x08 */ f32 y_position;
 /* 0x0C */ f32 z_position;
 /* 0x10 */ s8 hitboxRadius;
 /* 0x11 */ u8 unk11;
 /* 0x12 */ u8 pushForce;
 /* 0x13 */ u8 distance;
 /* 0x14 */ s16 flags;
 /* 0x16 */ s8 unk16;
 /* 0x17 */ s8 unk17;
 /* 0x18 */ s32 pad[4];
} ObjectInteraction;

typedef struct ShadowData {
    f32 scale;
    TextureHeader *texture;
    s16 meshStart;
    s16 meshEnd;
    s16 unkC;
    s16 unkE;
} ShadowData;

typedef struct WaterEffect {
    f32 scale;
    TextureHeader *texture;
    s16 meshStart;
    s16 meshEnd;
    s16 textureFrame;
    s16 animationSpeed;
    s16 unk10;
    s16 unk12;
} WaterEffect;

typedef struct ShadeProperties {
    f32 unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    f32 brightness;
    f32 ambient;
} ShadeProperties;

typedef f32 FakeHalfMatrix[2][4];
typedef struct Object_5C {
    union {
  /* 0x0000 */ Matrix matrices[4];
  /* 0x0000 */ FakeHalfMatrix _matrices[8]; // This is a hack. The Matrix[4] is the real one.
 };
  /* 0x0100 */ void *unk100;
  /* 0x0104 */ u8 unk104;
  /* 0x0105 */ u8 unk105;
  /* 0x0106 */ u8 unk106;
  /* 0x0107 */ u8 unk107;
  /* 0x0108 */ s32 unk108;
} Object_5C;

typedef struct Object_60 {
    s32 unk0;
    struct Object *unk4[10];
    s8 *unk2C;
} Object_60;

typedef struct Object_LaserGun {
  /* 0x00 */ s32 unk0;
  /* 0x00 */ s32 unk4;
  /* 0x00 */ s32 unk7;
  /* 0x0C */ s16 fireTimer;
  /* 0x0E */ s8 targeting;
  /* 0x0F */ s8 fireRate;
  /* 0x10 */ u8 laserDuration;
  /* 0x11 */ u8 radius;
} Object_LaserGun;

typedef struct Object_Laser {
  /* 0x000 */ s16 unk0;
  /* 0x004 */ u8  unk4[0x185];
  /* 0x187 */ s8  unk187;
} Object_Laser;

typedef struct Object_TrophyCabinet {
  /* 0x0 */ s32 unk0;
  /* 0x4 */ s16 unk4;
} Object_TrophyCabinet;

typedef struct Object_Animator {
  /* 0x00 */ s16 segmentId;
  /* 0x02 */ s16 batchId;
  /* 0x04 */ s16 speedFactorX;
  /* 0x06 */ s16 speedFactorY;
  /* 0x08 */ s16 xSpeed;
  /* 0x0A */ s16 ySpeed;
} Object_Animator;

typedef struct Object_Animation {
  /* 0x00 */ f32 unk0;
  /* 0x04 */ f32 unk4;
  /* 0x08 */ f32 unk8;
  /* 0x0C */ f32 x;
  /* 0x10 */ f32 y;
  /* 0x14 */ f32 z; 
  /* 0x18 */ u8 *unk18; 
  /* 0x1C */ struct Object *unk1C;
  /* 0x20 */ s32 unk20;
  /* 0x24 */ s16 unk24;
  /* 0x26 */ s16 unk26;
  /* 0x28 */ u16 unk28;
  /* 0x2A */ u16 startDelay;
  /* 0x2C */ u8 unk2C;
  /* 0x2D */ u8 unk2D;
  /* 0x2E */ u8 unk2E;
  /* 0x2F */ u8 unk2F;
  /* 0x30 */ s8 cameraID;
  /* 0x31 */ u8 unk31;
  /* 0x32 */ u8 unk32;
  /* 0x33 */ u8 unk33;
  /* 0x34 */ u8 unk34;
  /* 0x35 */ u8 unk35;
  /* 0x36 */ s16 pauseCounter;
  /* 0x38 */ u8 unk38;
  /* 0x39 */ u8 unk39;
  /* 0x3A */ u8 unk3A;
  /* 0x3V */ u8 unk3B;
  /* 0x3C */ u8 unk3C;
  /* 0x3D */ u8 unk3D;
  /* 0x3E */ u8 unk3E;
  /* 0x3F */ u8 unk3F;
  /* 0x40 */ u8 unk40;
  /* 0x41 */ u8 unk41;
  /* 0x42 */ u8 unk42;
  /* 0x43 */ u8 unk43;
  /* 0x44 */ u8 unk44;
  /* 0x45 */ u8 unk45;
  /* 0x46 */ u8 pad46[4];
  /* 0x4A */ s16 unk4A;
  /* 0x4C */ u8 pad4C[0x10];
  /* 0x5C */ s32 unk5C;
} Object_Animation;

typedef struct Object_Animation2 {
  /* 0x00 */ u8 pad0[6];
  /* 0x06 */ s16 flags;
} Object_Animation2;

typedef struct Object_OverridePos {
  /* 0x00 */ f32 x;
  /* 0x04 */ f32 y;
  /* 0x08 */ f32 z;
  /* 0x0C */ Object_Animation *anim;
} Object_OverridePos;

typedef struct Object_WeaponBalloon {
  /* 0x0 */ f32 scale;
  /* 0x4 */ s16 respawnTime;
  /* 0x6 */ s8 unk6[0x2];
} Object_WeaponBalloon;

typedef struct Object_Weapon {
  /* 0x00 */ struct Object *target;
  /* 0x04 */ struct Object *owner;
  /* 0x08 */ struct Object *hitObj;
  /* 0x0C */ f32 checkpointDist;
  /* 0x10 */ f32 forwardVel;
  /* 0x14 */ s16 unk14;
  /* 0x14 */ s16 unk16;
  /* 0x18 */ u8 weaponID;
  /* 0x19 */ s8 checkpoint;
  /* 0x19 */ s16 unk1A;
  /* 0x19 */ SoundMask *soundMask;
} Object_Weapon;

typedef struct Object_Butterfly {
  /* 0x000 */ Triangle triangles[8];
  /* 0x080 */ Vertex vertices[12];
  /* 0x0F8 */ TextureHeader *texture;
  /* 0x0FC */ u8 unkFC;
  /* 0x0FD */ u8 unkFD;
  /* 0x0FE */ u8 unkFE;
  /* 0x0FF */ u8 unkFF;
  /* 0x100 */ struct Object *unk100; 
  /* 0x104 */ u16 unk104;
  /* 0x106 */ s16 unk106;
  /* 0x108 */ f32 unk108;
  /* 0x10C */ f32 unk10C;
} Object_Butterfly;

typedef struct Object_Fish {
  /* 0x000 */ Triangle triangles[8];
  /* 0x080 */ Vertex vertices[12];
  /* 0x0F8 */ TextureHeader *texture;
  /* 0x0FC */ u8 unkFC;
  /* 0x0FD */ u8 unkFD;
  /* 0x0FE */ s16 unkFE;
  /* 0x100 */ s16 unk100;
  /* 0x102 */ s16 unk102;
  /* 0x104 */ s16 unk104;
  /* 0x106 */ s16 unk106;
  /* 0x108 */ f32 unk108;
  /* 0x10C */ f32 unk10C;
  /* 0x110 */ f32 unk110;
  /* 0x114 */ f32 unk114;
  /* 0x118 */ f32 unk118;
  /* 0x11c */ f32 unk11C;
} Object_Fish;

typedef struct Object_Boost {
  /* 0x000 */ u8 pad[0x70];
  /* 0x070 */ u8 unk70;
  /* 0x074 */ f32 unk74;
} Object_Boost;

typedef struct Object_EffectBox {
  /* 0x000 */ u8 pad0[0x1FE];
  /* 0x1FE */ u8 unk1FE;
  /* 0x1FF */ u8 unk1FF;
} Object_EffectBox;

typedef struct Object_EggCreator {
  /* 0x0 */ u8 pad0[4];
  /* 0x4 */ struct Object *currentEgg;
} Object_EggCreator;

typedef struct Object_CollectEgg {
  /* 0x0 */ u8 pad0[4];
  /* 0x4 */ struct Object *spawnerObj;
  /* 0x8 */ s16 hatchTimer;
  /* 0xA */ s8 racerID;
  /* 0xB */ s8 status;
} Object_CollectEgg;

typedef struct Object_UnkId58 {
  /* 0x000 */ u8 pad0[0x1D6];
  /* 0x1D6 */ s8 vehicleID;
} Object_UnkId58;

typedef struct Object_CharacterFlag {
  /* 0x00 */ Triangle triangles[2];
  /* 0x20 */ Vertex *vertices;
  /* 0x24 */ TextureHeader *texture;
} Object_CharacterFlag;

typedef struct Object_AnimCamera {
  /* 0x00 */ u8 pad0[0x30];
  /* 0x30 */ s8 cameraID;
  /* 0x31 */ u8 pad31[0xB];
  /* 0x3C */ s32 unk3C;
  /* 0x40 */ u8 pad40[4];
  /* 0x44 */ u8 unk44;
  /* 0x45 */ u8 pad45[5];
  /* 0x4A */ s16 unk4A;
  /* 0x4C */ u8 pad4C[8];
  /* 0x54 */ s8 unk54;
} Object_AnimCamera;

typedef struct Object_InfoPoint {
  /* 0x0 */ s16 unk0;
} Object_InfoPoint;

typedef struct Object_WorldKey {
  /* 0x0 */ s16 unk0;
} Object_WorldKey;

typedef struct Object_AudioLine {
  /* 0x00 */ u8 unk0;
  /* 0x01 */ u8 pad1;
  /* 0x02 */ u16 soundID;
  /* 0x04 */ u16 unk4;
  /* 0x06 */ u16 unk6;
  /* 0x08 */ union {
                 struct {
                     u8 unk8;
                     u8 unk9;
                     u8 unkA;
                     u8 padB;
                 } unk_struct;
                 s32 unk8_word;
             } unk_union;
  /* 0x0C */ u8 lineID;
  /* 0x0D */ u8 unkD;
  /* 0x0E */ u8 unkE;
  /* 0x0F */ u8 unkF;
  /* 0x10 */ u8 unk10;
  /* 0x11 */ u8 unk11;
  /* 0x12 */ u8 unk12;
} Object_AudioLine;

typedef struct Object_AudioReverb {
  /* 0x0 */ u16 pad0;
  /* 0x2 */ s16 unk2;
  /* 0x4 */ u8 lineID;
  /* 0x5 */ u8 unk5;
} Object_AudioReverb;

typedef struct Object_TexScroll {
  /* 0x0 */ s16 textureIndex;
  /* 0x2 */ s16 pad2;
  /* 0x4 */ s16 unk4;
  /* 0x6 */ s16 unk6;
  /* 0x8 */ s16 unk8;
  /* 0xA */ s16 unkA;
} Object_TexScroll;

typedef struct Object_Frog {
  /* 0x00 */ f32 homeX;
  /* 0x04 */ f32 homeY;
  /* 0x08 */ f32 homeZ;
  /* 0x0C */ f32 homeRadius;
  /* 0x10 */ f32 homeRadiusSquare;
  /* 0x14 */ u8 action;
  /* 0x15 */ u8 drumstick;
  /* 0x16 */ s16 hopTimer;
  /* 0x18 */ s8 hopFrame; // Animation frame while jumping
  /* 0x19 */ s8 squishCooldown;
  /* 0x1A */ s16 hopDirection;
  /* 0x1C */ f32 forwardVel;
  /* 0x20 */ f32 hopStartX;
  /* 0x24 */ f32 hopStartZ;
  /* 0x28 */ f32 hopTargetX;
  /* 0x2C */ f32 hopTargetZ;
  /* 0x30 */ f32 scaleY;
} Object_Frog;

typedef struct Object_Wizpig2 {
  /* 0x00 */ u8 pad0[0x70];
  /* 0x70 */ u8 unk70;
  /* 0x71 */ u8 pad71;
  /* 0x72 */ u8 unk72;
  /* 0x73 */ u8 pad73;
  /* 0x74 */ f32 unk74;
} Object_Wizpig2;

typedef struct Object_Exit {
  /* 0x00 */ f32 directionX;
  /* 0x04 */ f32 directionY;
  /* 0x08 */ f32 directionZ;
  /* 0x0C */ f32 rotationDiff; // Rotational offset, to test intersection when the exit is rotated.
  /* 0x10 */ s32 radius; // Activation radius.
  /* 0x14 */ s8 bossFlag; // Dictates boss level version. 0 is first encounter, 1 is rematch. -1 means no boss.
} Object_Exit;

typedef struct Object_AiNode {
   /* 0x00 */ struct Object *nodeObj[4];
   /* 0x10 */ s16 distToNode[4];
   /* 0x18 */ s8 directions[4];
} Object_AiNode;

/* Size: 0x224 - 548 bytes */
typedef struct Object_Racer {
  /* 0x000 */ s16 playerIndex; // -1 = AI Controlled, 0 to 3 = Object controlled
  /* 0x002 */ s8 racerIndex; // Unique ID for each racer object.
  /* 0x003 */ s8 characterId; // Affects minimap color, horn, voice, etc.
  /* 0x004 */ s32 unk4;
  /* 0x008 */ f32 forwardVel;
  /* 0x00C */ f32 animationSpeed;
  /* 0x010 */ s32 unk10;
  /* 0x014 */ s32 unk14;
  /* 0x018 */ s32 unk18;
  /* 0x01C */ s32 unk1C;
  /* 0x020 */ s32 unk20;
  /* 0x024 */ SoundMask *soundMask;
  /* 0x028 */ u16 lastSoundID;
  /* 0x02A */ u16 unk2A;
  /* 0x02C */ f32 velocity;
  /* 0x030 */ f32 lateral_velocity;
  /* 0x034 */ f32 unk34; // Vehicle pitch.
  /* 0x038 */ f32 ox1;
  /* 0x03C */ f32 oy1;
  /* 0x040 */ f32 oz1;
  /* 0x044 */ f32 ox2;
  /* 0x048 */ f32 oy2;
  /* 0x04C */ f32 oz2;
  /* 0x050 */ f32 ox3;
  /* 0x054 */ f32 oy3;
  /* 0x058 */ f32 oz3;
  /* 0x05C */ f32 prev_x_position;
  /* 0x060 */ f32 prev_y_position;
  /* 0x064 */ f32 prev_z_position;
  /* 0x068 */ f32 unk68; // xPos
  /* 0x06C */ f32 unk6C; // yPos
  /* 0x070 */ f32 unk70; // zPos
  /* 0x074 */ f32 unk74;
  /* 0x078 */ f32 carBobX;
  /* 0x07C */ f32 carBobY;
  /* 0x080 */ f32 carBobZ;
  /* 0x084 */ f32 unk84;
  /* 0x088 */ f32 unk88;
  /* 0x08C */ f32 stretch_height;
  /* 0x090 */ f32 stretch_height_cap;
  /* 0x094 */ f32 camera_zoom;
  /* 0x098 */ f32 unk98;
  /* 0x09C */ f32 pitch;
  /* 0x0A0 */ f32 roll;
  /* 0x0A4 */ f32 yaw;
  /* 0x0A8 */ f32 checkpoint_distance;
  /* 0x0AC */ f32 unkAC;
  /* 0x0B0 */ f32 unkB0;
  /* 0x0B4 */ f32 throttle;
  /* 0x0B8 */ f32 brake;
  /* 0x0BC */ f32 unkBC;
  /* 0x0C0 */ f32 buoyancy;
  /* 0x0C4 */ f32 unkC4;
  /* 0x0C8 */ f32 unkC8;
  /* 0x0CC */ f32 unkCC;
  /* 0x0D0 */ f32 unkD0;
  /* 0x0D4 */ f32 unkD4;
  /* 0x0D8 */ Vec3f unkD8;
  /* 0x0E4 */ Vec3f unkE4;
  /* 0x0F0 */ Vec3f unkF0;
  /* 0x0FC */ Vec3f unkFC;
  /* 0x108 */ struct Object *exitObj;
  /* 0x10C */ s32 unk10C;
  /* 0x110 */ s32 unk110;
  /* 0x114 */ s32 unk114;
  /* 0x118 */ struct VehicleSoundData *vehicleSound;
  /* 0x11C */ f32 unk11C;
  /* 0x120 */ f32 unk120;
  /* 0x124 */ f32 unk124;
  /* 0x128 */ s32 lap_times[5]; //mode_init_taj_race implies there should be at least 5 lap times.
  /* 0x13C */ s32 unk13C;
  /* 0x140 */ struct Object *magnetTargetObj;
  /* 0x144 */ struct Object *held_obj;
  /* 0x148 */ struct Object *approachTarget;
  /* 0x14C */ struct Object *zipperObj;
  /* 0x150 */ struct Object *unk150;
  /* 0x154 */ struct Object *unk154;
  /* 0x158 */ struct Object *nodeCurrent;
  /* 0x15C */ struct Object *challengeMarker;
  /* 0x160 */ s16 y_rotation_offset;
  /* 0x162 */ s16 x_rotation_offset;
  /* 0x164 */ s16 z_rotation_offset;
  /* 0x166 */ s16 unk166; // I don't know exactly what these are, but this one in particular seems to cause a Y position offset.
  /* 0x168 */ s16 unk168;
  /* 0x16A */ s16 headAngle;
  /* 0x166 */ s16 headAngleTarget;
  /* 0x16E */ s16 unk16E;
  /* 0x170 */ s16 unk170;
  /* 0x172 */ s8 balloon_type;
  /* 0x173 */ s8 balloon_quantity;
  /* 0x174 */ s8 balloon_level;
  /* 0x175 */ s8 magnetTimer;
  /* 0x176 */ s16 unk176;
  /* 0x178 */ void *magnetSoundMask;
  /* 0x17C */ SoundMask *shieldSoundMask;
  /* 0x180 */ SoundMask *bananaSoundMask;
  /* 0x184 */ s8 magnetModelID;
  /* 0x185 */ s8 bananas;
  /* 0x186 */ u8 unk186;
  /* 0x187 */ s8 attackType;
  /* 0x188 */ s8 unk188;
  /* 0x189 */ s8 shieldType;
  /* 0x18A */ s16 unk18A;
  /* 0x18C */ s16 unk18C;
  /* 0x18E */ s16 shieldTimer;
  /* 0x190 */ s16 courseCheckpoint;
  /* 0x192 */ s8 checkpoint;
  /* 0x193 */ s8 lap;
  /* 0x194 */ s8 countLap;
  /* 0x195 */ s8 magnetLevel3;
  /* 0x196 */ s16 cameraYaw;
  /* 0x198 */ s16 unk198;
  /* 0x19A */ s16 unk19A;
  /* 0x19C */ s16 unk19C;
  /* 0x19E */ s16 unk19E;
  /* 0x1A0 */ s16 steerVisualRotation;
  /* 0x1A2 */ s16 y_rotation_vel;
  /* 0x1A4 */ s16 x_rotation_vel;
  /* 0x1A6 */ s16 z_rotation_vel;
  /* 0x1A8 */ s16 unk1A8;
  /* 0x1AA */ s16 unk1AA;
  /* 0x1AC */ s16 finishPosition;
  /* 0x1AE */ s16 racePosition;
  /* 0x1B0 */ s16 unk1B0;
  /* 0x1B2 */ s16 unk1B2;
  /* 0x1B4 */ s32 unk1B4;
  /* 0x1B8 */ s16 unk1B8;
  /* 0x1BA */ s16 unk1BA;
  /* 0x1BC */ s16 unk1BC;
  /* 0x1BE */ s16 unk1BE;
  /* 0x1C0 */ s16 unk1C0;
  /* 0x1C2 */ s16 unk1C2;
  /* 0x1C4 */ s16 unk1C4;
  /* 0x1C6 */ s16 unk1C6;
  /* 0x1C8 */ u8 unk1C8;
  /* 0x1C9 */ u8 unk1C9;
  /* 0x1CA */ s8 unk1CA;
  /* 0x1CB */ u8 unk1CB;
  /* 0x1CC */ s8 aiSkill;
  /* 0x1CD */ u8 unk1CD;
  /* 0x1CE */ u8 unk1CE;
  /* 0x1CF */ s8 eggHudCounter;
  /* 0x1D0 */ s8 spectateCamID;
  /* 0x1D1 */ s8 unk1D1;
  /* 0x1D2 */ s8 unk1D2;
  /* 0x1D3 */ s8 boostTimer;
  /* 0x1D4 */ s8 unk1D4;
  /* 0x1D5 */ s8 unk1D5;
  /* 0x1D6 */ s8 vehicleID;
  /* 0x1D7 */ s8 vehicleIDPrev;
  /* 0x1D8 */ s8 raceFinished;
  /* 0x1D9 */ s8 unk1D9;
  /* 0x1DA */ u8 unk1DA;
  /* 0x1DB */ s8 spinout_timer;
  /* 0x1DC */ u8 wheel_surfaces[4];
  /* 0x1E0 */ s8 trickType; // This depends on which vehicle you're using, but this name fits the most for now.
  /* 0x1E1 */ s8 steerAngle;
  /* 0x1E2 */ s8 groundedWheels;
  /* 0x1E3 */ s8 unk1E3;
  /* 0x1E4 */ s8 unk1E4;
  /* 0x1E5 */ s8 waterTimer; // Set to a value, then counts down when leaving water.
  /* 0x1E6 */ s8 drift_direction;
  /* 0x1E7 */ s8 miscAnimCounter;
  /* 0x1E8 */ s8 unk1E8;
  /* 0x1E9 */ s8 unk1E9;
  /* 0x1EA */ s8 unk1EA;
  /* 0x1EB */ s8 tapTimerR;
  /* 0x1EC */ s8 tappedR;
  /* 0x1ED */ s8 squish_timer;
  /* 0x1EE */ u8 unk1EE;
  /* 0x1EF */ u8 boost_sound;
  /* 0x1F0 */ u8 unk1F0;
  /* 0x1F1 */ u8 unk1F1;
  /* 0x1F2 */ u8 unk1F2;
  /* 0x1F3 */ u8 unk1F3;
  /* 0x1F4 */ u8 startInput;
  /* 0x1F5 */ u8 zipperDirCorrection;
  /* 0x1F6 */ s8 unk1F6;
  /* 0x1F7 */ u8 transparency;
  /* 0x290 */ u8 indicator_type;
  /* 0x291 */ s8 indicator_timer;
  /* 0x1FA */ s8 drifting;
  /* 0x1FB */ s8 unk1FB;
  /* 0x1FC */ u8 unk1FC;
  /* 0x1FD */ s8 cameraIndex;
  /* 0x1FE */ u8 unk1FE;
  /* 0x1FF */ u8 unk1FF;
  /* 0x200 */ s8 transitionTimer;
  /* 0x201 */ s8 unk201;
  /* 0x202 */ s8 silverCoinCount;
  /* 0x203 */ s8 boostType;
  /* 0x204 */ s16 bubbleTrapTimer;
  /* 0x206 */ s16 unk206;
  /* 0x208 */ s8 unk208;
  /* 0x209 */ u8 unk209;
  /* 0x20A */ u8 lightFlags;
  /* 0x20B */ u8 unk20B;
  /* 0x20C */ u8 throttleReleased;
  /* 0x20D */ u8 unk20D;
  /* 0x20E */ u16 delaySoundID;
  /* 0x210 */ u8 delaySoundTimer;
  /* 0x211 */ s8 unk211;
  /* 0x212 */ s8 elevation; // Some maps like Icicle Pyramid have elevation levels that are communicated on the minimap.
  /* 0x213 */ s8 unk213;
  /* 0x214 */ s8 unk214;
  /* 0x215 */ s8 unk215;
  /* 0x216 */ u8 unk216;
  /* 0x217 */ u8 unk217;
  /* 0x218 */ s32 weaponSoundMask;
  /* 0x21C */ s32 unk21C;
  /* 0x220 */ s32 unk220;
} Object_Racer;

typedef struct Object_Door {
  /* 0x00 */ f32 homeY;
  /* 0x04 */ SoundMask *soundMask;
  /* 0x08 */ s32 jingleTimer;
  /* 0x0A */ s16 jingleCooldown;
  /* 0x0E */ s8 doorID;
  /* 0x0F */ u8 doorType;
  /* 0x10 */ u8 balloonCount;
  /* 0x11 */ u8 balloonCountUnused;
  /* 0x12 */ u8 radius;
  /* 0x13 */ s8 textID;
  /* 0x14 */ s8 keyID;
  /* 0x15 */ s8 openDir;
} Object_Door;

typedef struct Object_Trigger {
  /* 0x00 */ f32 directionX;
  /* 0x04 */ f32 directionY;
  /* 0x08 */ f32 directionZ;
  /* 0x0C */ f32 rotationDiff; // Rotational offset, to test intersection when the exit is rotated.
  /* 0x10 */ s32 radius;
  union {
  /* 0x14 */ u8 vehicleID;
  /* 0x14 */ u8 unk14;
  };
} Object_Trigger;

typedef struct Object_Audio {
  /* 0x00 */ u16 soundId;
  /* 0x02 */ u16 unk2;
  /* 0x04 */ u8 unk4;
  /* 0x05 */ u8 unk5;
  /* 0x06 */ u8 unk6;
  /* 0x07 */ u8 unk7;
  /* 0x08 */ SoundMask *soundMask;
  /* 0x0C */ u8 unkC;
  /* 0x0D */ u8 unkD;
} Object_Audio;

typedef struct Object_MidiFade {
  /* 0x00 */ u8 unk0;
  /* 0x01 */ u8 unk1;
  /* 0x02 */ u8 unk2;
  /* 0x04 */ f32 unk4;
  /* 0x08 */ f32 unk8;
  /* 0x0C */ f32 unkC;
  /* 0x10 */ f32 unk10;
  /* 0x14 */ f32 unk14;
  /* 0x18 */ f32 unk18;
  /* 0x1C */ f32 unk1C;
  /* 0x20 */ f32 unk20;
  /* 0x24 */ f32 unk24;
  /* 0x28 */ f32 unk28;
  /* 0x2C */ f32 unk2C;
  /* 0x2F */ u8 unk2F[16];
  /* 0x40 */ u8 unk40;
} Object_MidiFade;

typedef struct Object_MidiFadePoint {
  /* 0x00 */ u16 unk0;
  /* 0x02 */ u16 unk2;
  /* 0x04 */ f32 unk4;
  /* 0x08 */ f32 unk8;
  /* 0x0C */ u8 unkC[16];
  /* 0x1C */ u8 unk1C;
} Object_MidiFadePoint;

typedef struct Object_PosArrow {
  /* 0x000 */ s16 unk0;
  /* 0x004 */ u8 pad4[0x14E];
  /* 0x150 */ struct Object *unk150;
} Object_PosArrow;

typedef struct Object_Banana {
  /* 0x0 */ s32 unk0;
  /* 0x4 */ struct Object *spawner;
  /* 0x8 */ s8 unk8;
  /* 0x9 */ s8 droppedVehicleID;
} Object_Banana;

typedef struct Object_FogChanger {
  /* 0x0 */ s16 unk0;
} Object_FogChanger;

typedef struct Object_NPC {
   /* 0x00 */ f32 unk0;
   /* 0x04 */ f32 animFrameF;
   /* 0x08 */ s32 unk8;
   /* 0x0C */ s8 nodeBack1; // One node backwards
   /* 0x0D */ u8 nodeCurrent; // Intended target node
   /* 0x0E */ u8 nodeBack2; // Two nodes backward
   /* 0x0F */ u8 nodeForward1; // One node forward
   /* 0x10 */ u8 nodeForward2; // Two nodes forward
   /* 0x11 */ u8 fogR;
   /* 0x12 */ u8 fogG;
   /* 0x13 */ u8 fogB;
   /* 0x14 */ f32 forwardVel;
   /* 0x18 */ f32 unk18;
   /* 0x1C */ s16 unk1C;
   /* 0x1E */ s16 unk1E;
   /* 0x20 */ s16 fogNear;
   /* 0x22 */ s16 fogFar;
   /* 0x24 */ s32 unk24;
   /* 0x28 */ s16 unk28;
   /* 0x2A */ s16 unk2A;
   /* 0x2C */ s32 unk2C;
   /* 0x30 */ s32 unk30;
   /* 0x34 */ u16 musicFade;
   /* 0x36 */ s8 unk36;
} Object_NPC;

typedef struct Object_TT {
  /* 0x0 */ f32 unk0;
  /* 0x4 */ u8 pad4[0x9];
  /* 0xD */ u8 unkD;
} Object_TT;

typedef struct Object_Bridge_WhaleRamp {
  /* 0x0 */ f32 homeY;
  /* 0x4 */ SoundMask *soundMask;
} Object_Bridge_WhaleRamp;

typedef struct Object_64_80021400 {
  /* 0x00 */ u8 pad[0x2A];
  /* 0x2A */ s16 unk2A;
} Object_64_80021400;

typedef struct Object_80021400_64 {
  /* 0x000 */ u8 pad[0x64];
  /* 0x064 */ struct Object_64_80021400 *obj64;
} Object_80021400_64;

typedef struct Object_Log {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x04 */ u8 unk3;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ s8 unkE[2];
} Object_Log;

typedef struct Object_Fireball_Octoweapon {
    u8 pad0[0x1C];
    s32 soundMask;
} Object_Fireball_Octoweapon;

typedef struct Object_AnimatedObject {
    u8 pad0[0x20];
  /* 0x20 */ u32 soundMask;
  /* 0x24 */ s16 currentSound;
  /* 0x26 */ s16 unk26;
    s16 unk28;
    u8 pad2A[0xC];
    s16 unk36;
    s8 soundID;
    s8 unk39;
    s8 unk3A;
    s8 unk3B;
    s8 pad3C[0xC];
} Object_AnimatedObject;

typedef struct Object_WizpigRocket {
    u8 pad0[0x70];
    u8 unk70;
    u8 unk71;
    u8 unk72;
    u8 unk73;
    f32 unk74;
} Object_WizpigRocket;

typedef struct Object_8001E89C_64_C {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} Object_8001E89C_64_C;

typedef struct Object_8001E89C_64 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ Object_8001E89C_64_C *unkC;
} Object_8001E89C_64;

typedef struct Object_CharacterSelect {
    u8 pad0[0x14];
    f32 unk14;
    u8 pad18[0x10];
    s16 unk28;
    u8 unk2A[2];
    u8 unk2C;
    u8 pad2D[2];
    u8 unk2F;
    u8 pad30[6];
    s16 unk36;
    u8 unk38;
    u8 unk39;
    s8 unk3A;
    s8 unk3B;
    s8 unk3C;
    s8 pad3D[2];
    s8 unk3F;
    s8 unk40;
    s8 unk41;
    s8 pad42;
    s8 unk43;
} Object_CharacterSelect;
typedef struct Object_64 {
    union {
        Object_Laser laser;
        Object_TrophyCabinet trophy_cabinet;
        Object_Animator animator;
        Object_Animation animation;
        Object_Animation2 animation2;
        Object_WeaponBalloon weapon_balloon;
        Object_Weapon weapon;
        Object_Butterfly butterfly;
        Object_Fish fish;
        Object_Boost boost;
        Object_EffectBox effect_box;
        Object_EggCreator egg_creator;
        Object_CollectEgg egg;
        Object_UnkId58 unkid58;
        Object_CharacterFlag character_flag;
        Object_AnimCamera anim_camera;
        Object_InfoPoint info_point;
        Object_WorldKey world_key;
        Object_AudioLine audio_line;
        Object_AudioReverb audio_reverb;
        Object_TexScroll tex_scroll;
        Object_Frog frog;
        Object_Wizpig2 wizpig2;
        Object_Exit exit;
        Object_Racer racer;
        Object_Door door;
        Object_Trigger trigger;
        Object_Audio audio;
        Object_MidiFade midi_fade;
        Object_MidiFadePoint midi_fade_point;
        Object_PosArrow pos_arrow;
        Object_Banana banana;
        Object_FogChanger fog_changer;
        Object_NPC npc;
        Object_TT tt;
        Object_Bridge_WhaleRamp bridge_whale_ramp;
        Object_80021400_64 obj80021400_64;
        Object_Log log;
        Object_Fireball_Octoweapon fireball_octoweapon;
        Object_LaserGun lasergun;
        Object_AnimatedObject animatedObject;
        Object_WizpigRocket wizpigRocket;
        Object_8001E89C_64 obj8001E89C_64;
        Object_CharacterSelect characterSelect;
        Object_AiNode ai_node;
        Object_OverridePos override_pos;
    };
} Object_64;

// Size: 0xC
typedef struct Object_68_38 {
 /* 0x00 */ u8 unk0[8];
 /* 0x08 */ s32 unk8;
} Object_68_38;

typedef struct Object_68 {
  /* 0x00 */ union {
      ObjectModel *objModel;
      TextureHeader *texHeader;
  };
  /* 0x04 */ Vertex *unk4[2];
  /* 0x0C */ s32 *unkC;
  /* 0x10 */ s16 animationID;
  /* 0x12 */ s16 animationFrame;
  /* 0x14 */ s16 animationFrameCount;
  /* 0x16 */ s16 offsetX;
  /* 0x18 */ s16 offsetY;
  /* 0x1A */ s16 offsetZ;
  /* 0x1C */ s16 unk1C;
  /* 0x1E */ s8 unk1E;
  /* 0x1F */ s8 animationTaskNum;
  /* 0x20 */ s8 unk20;
  /* 0x21 */ s8 unk21;
  /* 0x22 */ s16 unk22;
  /* 0x24 */ s32 unk24;
  /* 0x28 */ s16 unk28;
  /* 0x2A */ s16 unk2A;
  /* 0x2C */ s32 unk2C;
  /* 0x30 */ s32 unk30;
  /* 0x34 */ u8 pad34[0x4];
  /* 0x38 */ Object_68_38 *unk38; //Array Size unknown
  /* 0x40 */ u8 pad40[0x14];
  /* 0x50 */ s16 unk50;
 } Object_68;
 
/* Size: 0x20 bytes */
typedef struct ParticleEmitter {
    /* 0x00 */ struct Particle *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8  padC[0x14];
} ParticleEmitter;

/* Size: 0xA0 bytes */
typedef struct ParticleBehavior {
    s32 flags;
    f32 velX;
    f32 velY;
    f32 velZ;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s16 unk40;
    s16 unk42;
    s16 angleOffsetY;
    s16 angleOffsetX;
    s16 angleOffsetZ;
    s16 angleVelY;
    s16 angleVelX;
    s16 angleVelZ;
    f32 unk50;
    f32 unk54;
    f32 forwardVel;
    s32 behaviourFlags;
    s32 gravityRange1;
    s16 angleRangeY1;
    s16 angleRangeX1;
    s16 angleRangeZ1;
    s16 angleRangeY2;
    s16 angleRangeX2;
    s16 angleRangeZ2;
    s32 gravityRange2;
    s32 velocityRangeX1;
    s32 velocityRangeY1;
    s32 velocityRangeZ1;
    s16 angleRangeY3;
    s16 angleRangeX3;
    s16 angleRangeZ3;
    s16 unk86;
    s16 unk88;
    s16 unk8A;
    s32 unk8C; // Something to do with scale
    s32 unk90; // Something to do with scale
    s32 velocityRange;
    u8 colourRangeR;
    u8 colourRangeG;
    u8 colourRangeB;
    u8 colourRangeA;
    s32 *unk9C;
} ParticleBehavior;

typedef struct unk800AF29C_C_400 {
    s32 *unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} unk800AF29C_C_400;

typedef struct unk800B2260_C {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x24];
    s16 unk2C;
    u8 pad2E[0xC];
    s16 unk3A;
    u8 pad3C[0x8];
    void *unk44;
    u8 pad48[0x28];
    void *unk70;
    u8 unk74;
} unk800B2260_C;

/* Size: 0x018 bytes */
typedef struct ObjectTransform {
  /* 0x0000 */ s16 y_rotation;
  /* 0x0002 */ s16 x_rotation;
  /* 0x0004 */ s16 z_rotation;
  /* 0x0006 */ s16 flags;
  /* 0x0008 */ f32 scale;
  /* 0x000C */ f32 x_position;
  /* 0x0010 */ f32 y_position;
  /* 0x0014 */ f32 z_position;
} ObjectTransform;

typedef struct SegmentPropertiesObject {
  /* 0x002C */ s16 unk2C;
  /* 0x002E */ s16 segmentID;
  /* 0x0030 */ f32 distanceToCamera;
  /* 0x0034 */ s16 cameraSegmentID;
  /* 0x0036 */ s16 unk36;
  /* 0x0038 */ s8 unk38;
  /* 0x0039 */ u8 opacity;
  /* 0x003A */ s8 modelIndex;
  /* 0x003B */ s8 animationID;
} SegmentPropertiesObject;

typedef struct SegmentPropertiesParticle {
  /* 0x002C */ s16 unk2C;
  /* 0x002E */ s16 blockID;
  /* 0x0030 */ f32 unk30;
  /* 0x0034 */ f32 unk34;
  /* 0x0038 */ u8 unk38;
  /* 0x0039 */ u8 movementType;
  /* 0x003A */ s16 destroyTimer;
} SegmentPropertiesParticle;

typedef struct SegmentPropertiesCamera {
  /* 0x002C */ f32 unk2C;
  /* 0x0030 */ f32 distanceToCamera;
  /* 0x0034 */ f32 unk34;
  /* 0x0038 */ s16 unk38;
  /* 0x003A */ s16 unk3A;
} SegmentPropertiesCamera;

/* Size: 0x44 bytes */
typedef struct ObjectSegment {
  /* 0x0000 */ ObjectTransform trans;
  /* 0x0018 */ s16 animFrame;
  /* 0x001A */ s16 unk1A;
  /* 0x001C */ f32 x_velocity;
  /* 0x0020 */ f32 y_velocity;
  /* 0x0024 */ f32 z_velocity;
  /* 0x0028 */ f32 unk28;
  union {
      SegmentPropertiesObject object;
      SegmentPropertiesParticle particle;
      SegmentPropertiesCamera camera;
  };
  /* 0x003C */ LevelObjectEntry* level_entry;
  /* 0x0040 */ ObjectHeader *header;
} ObjectSegment;

typedef struct Object_LightData_UnkC_Unk44 {
    u8 pad0[8];
    Vertex *unk8;
} Object_LightData_UnkC_Unk44;

typedef struct Object_LightData_UnkC {
  /* 0x00 */ ObjectTransform trans;
  /* 0x18 */ u8 pad18[0x22];
  /* 0x3A */ s16 unk3A;
  /* 0x3C */ u8 pad3C[0x8];
  /* 0x44 */ Object_LightData_UnkC_Unk44 *unk44;
  /* 0x48 */ u8 pad48[0x14];
  /* 0x5C */ s16 unk5C;
  /* 0x5E */ u8 pad5E[0xE];
  /* 0x6C */ u8 unk6C;
  /* 0x6D */ u8 unk6D;
  /* 0x6E */ u8 unk6E;
  /* 0x6F */ u8 pad6F[0x6];
  /* 0x75 */ u8 unk75;
  /* 0x76 */ u8 pad76;
  /* 0x77 */ s8 unk77;
} Object_LightData_UnkC;

typedef struct Object_LightData {
  /* 0x00 */ u8 pad0[6];
  /* 0x06 */ u8 unk6;
  /* 0x07 */ u8 pad7[5];
  /* 0x0C */ Object_LightData_UnkC **unkC;
} Object_LightData;

/* Size: 0x0630 bytes */
typedef struct Object {
  /* 0x0000 */ ObjectSegment segment;
  /* 0x0044 */ Vertex *unk44;
  /* 0x0048 */ s16 behaviorId;
  /* 0x004A */ s16 objectID; // First 9 bits are object ID, last 7 bits are header size
  /* 0x004C */ ObjectInteraction *interactObj; //player + 0x318
  /* 0x0050 */ ShadowData *shadow; //player + 0x2F4
  /* 0x0054 */ ShadeProperties *shading; //player + 0x2C0
  /* 0x0058 */ WaterEffect *waterEffect; //player + 0x304
  /* 0x005C */ Object_5C *unk5C;
  /* 0x0060 */ Object_60 *unk60; //player + 0x340
  /* 0x0064 */ Object_64 *unk64; //player + 0x98
  /* 0x0068 */ Object_68 **unk68; //player + 0x80
  /* 0x006C */ ParticleEmitter *particleEmitter; //player + 0x370
  /* 0x0070 */ Object_LightData **lightData;
  /* 0x0074 */ u32 particleEmitFlags;
  /* 0x0078 */ ObjProperties properties;
  /* 0x0080 */ void *unk80;
  /* 0x0084 */ u32 unk84;
  /* 0x0088 */ u32 unk88;
  /* 0x008C */ u32 unk8C;
  /* 0x0090 */ u32 unk90;
  /* 0x0094 */ u32 unk94;
  /* 0x0098 */ s32 unk98;
} Object;

// Unused
typedef struct GhostHeaderUnk0 {
  u8 levelID;
  u8 vehicleID; // 0 = Car, 1 = Hovercraft, 2 = Plane
} GhostHeaderUnk0;

/* Size: 8 bytes */
typedef struct GhostHeader {
    union {
      GhostHeaderUnk0 unk0;
      s16 checksum;
    };
    union {
      struct {
        u8 characterID; // 9 = T.T.
        u8 unk3;
      };
      s16 unk2;
    };
    union {
        struct {
            u8 unk4;
            s8 unk5;
        };
        s16 time; // In frames, where 60 frames = 1 second.
    };
    s16 nodeCount;
} GhostHeader;

/* Size: 12 bytes */
typedef struct GhostNode {
  /* 0x00 */ s16 x;
  /* 0x02 */ s16 y;
  /* 0x04 */ s16 z;
  /* 0x06 */ s16 zRotation; // This order is correct.
  /* 0x08 */ s16 xRotation;
  /* 0x0A */ s16 yRotation;
} GhostNode;

typedef struct ByteColour {
    u8 red;
    u8 green;
    u8 blue;
} ByteColour;

typedef struct {
union {
struct {
 u8 r;
 u8 g;
 u8 b;
 u8 a;
};
u32 word;
};
} ColourRGBA;

#endif
