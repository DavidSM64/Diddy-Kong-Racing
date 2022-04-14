#ifndef _STRUCTS_H_
#define _STRUCTS_H_

/* Note: Structs are not complete, take them with a grain of salt. */

#include "types.h"

/* Size: 0x20 bytes */
typedef struct MenuElement {
  // Element Position
  /* 0x00 */ s16 left;
  /* 0x02 */ s16 top;
  /* 0x04 */ s16 center;
  /* 0x06 */ s16 middle;
  /* 0x08 */ s16 right;
  /* 0x0A */ s16 bottom;
  // Element Color/Transparency
  /* 0x0C */ u8 filterRed;
  /* 0x0D */ u8 filterGreen;
  /* 0x0E */ u8 filterBlue;
  /* 0x0F */ u8 filterAlpha; // 0 = no filter color, 0xFF = full color.
  /* 0x10 */ u8 opacity;
  // Element Properties
  /* 0x11 */ u8 textFont;
  /* 0x12 */ u8 textAlignFlags;
  // Element Type
  /* 0x13 */ u8 elementType; // Source type? 0 = ascii text, 2 = number, 7 = texture
  union {
  /* 0x14 */ void *element;   // Generic pointer
  /* 0x14 */ char *asciiText; // Pointer to ascii text to be displayed on the screen.
  /* 0x14 */ u32 *texture;    // Pointer to texture to be displayed on the screen.
  /* 0x14 */ s32 *number;     // Pointer to a number to be displayed on the screen.
  /* 0x14 */ u16 *numberU16;  // Pointer to a number to be displayed on the screen.
  /* 0x14 */ s32 value;       // Some value for elementType == 5
  } unk14_a;
  // Element Background Color/Transparency
  /* 0x18 */ s16 backgroundRed;
  /* 0x1A */ s16 backgroundGreen;
  /* 0x1C */ s16 backgroundBlue;
  /* 0x1E */ s16 backgroundAlpha; // 0x0000 = No background, 0x00FF = full background color.
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
  /* 0x03 */ u8 unk3;
  /* 0x04 */ u8 unk4;
  /* 0x05 */ u8 numberOfInstances; // Always 1 in the ROM.
  /* 0x06 */ s16 flags;
      // 0x04 = Interlaced texture
      // 0x40 = U clamp flag. 0 = Wrap, 1 = Clamp
      // 0x80 = V clamp flag. 0 = Wrap, 1 = Clamp
  /* 0x08 */ s16 ciPaletteOffset;
  /* 0x0A */ s16 numberOfCommands; // initialized in RAM; Number of commands in the texture display list. (Usually 0x07)
  /* 0x0C */ s32* cmd; // initialized in RAM; Pointer to texture display list.
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
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 pad3[0xC];
    u8 unkF;
} Settings4C;

#define TAJ_FLAGS_CAR_CHAL_UNLOCKED    0x01
#define TAJ_FLAGS_HOVER_CHAL_UNLOCKED  0x02
#define TAJ_FLAGS_PLANE_CHAL_UNLOCKED  0x04
#define TAJ_FLAGS_UNLOCKED_A_CHALLENGE  (TAJ_FLAGS_CAR_CHAL_UNLOCKED | TAJ_FLAGS_HOVER_CHAL_UNLOCKED | TAJ_FLAGS_PLANE_CHAL_UNLOCKED)
#define TAJ_FLAGS_CAR_CHAL_COMPLETED   0x08
#define TAJ_FLAGS_HOVER_CHAL_COMPLETED 0x10
#define TAJ_FLAGS_PLANE_CHAL_COMPLETED 0x20

/* Size: 0x118 bytes */
typedef struct Settings {
  /* 0x0000 */ s16 *balloonsPtr;
  /* 0x0004 */ s32 *courseFlagsPtr;
  /* 0x0008 */ u16 keys;
  /* 0x000A */ u16 unkA;
  /* 0x000C */ u16 bosses;
  /* 0x000E */ u16 trophies;
  /* 0x0010 */ u32 cutsceneFlags;
  /* Cutscene flags:
   * 0x1     = Lighthouse rocket cutscene
   * 0x2     = T.T. help prompt
   * 0x4     = Adventure 2 flag?
   * 0x8     = Dino domain boss cutscene
   * 0x10    = Sherbet island boss cutscene
   * 0x20    = Snowflake mountain boss cutscene
   * 0x40    = Dragon forest boss cutscene
   * 0x80    = Future Fun Land boss cutscene
   * 0x100   = Dino domain boss cutscene 2
   * 0x200   = Shertbet island boss cutscene 2
   * 0x400   = Snowflake mountain boss cutscene 2
   * 0x800   = Dragon forest boss cutscene 2
   * 0x2000  = Wizpig face cutscene
   * 0x4000  = Dino domain key cutscene
   * 0x8000  = Sherbet Island key cutscene
   * 0x10000 = Snowflake mountain key cutscene
   * 0x20000 = Dragon forest key cutscene
   */
  /* 0x0014 */ u16 tajFlags;
  /* Taj flags:
   * 0x1  = Car challenge unlocked
   * 0x2  = Hover challenge unlocked
   * 0x4  = Plane challenge unlocked
   * 0x8  = Car challenge completed
   * 0x10 = Hover challenge completed
   * 0x20 = Plane challenge completed
   */
  /* 0x0016 */ u8 ttAmulet;
  /* 0x0017 */ u8 wizpigAmulet;
  /* 0x0018 */ u16 *flapInitialsPtr[3];
  /* 0x0024 */ u16 *flapTimesPtr[3];
  /* 0x0030 */ u16 *courseInitialsPtr[3];
  /* 0x003C */ u16 *courseTimesPtr[3];
  /* 0x0048 */ u8 worldId;
  /* 0x0049 */ u8 courseId;
  /* 0x004A */ u8 gObjectCount;
  /* 0x004B */ u8 newGame;
  /* 0x004C */ Settings4C *unk4C;
  /* 0x0050 */ u32 filename;
  /* 0x0054 */ Racer racers[8];
  /* 0x0114 */ u8 timeTrialRacer;
  /* 0x0115 */ char unk115[2];
  /* 0x0117 */ u8 display_times;
} Settings;

/* Unknown size */
typedef struct LevelHeader_70 {
             u8 pad0[0x10];
  /* 0x10 */ u8 red;
  /* 0x11 */ u8 green;
  /* 0x12 */ u8 blue;
  /* 0x13 */ u8 alpha;
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
  /* 0x02 */ u8 unk2;
  /* 0x03 */ u8 unk3;
  /* 0x04 */ u8 unk4[4];

  /* 0x08 */ f32 course_height;

  /* 0x0C */ u8 padC[0x14];

  /* 0x20 */ s32 *unk20;

  /* 0x24 */ u8 pad24[0x10];

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

  /* 0x49 */ s8 unk49;
  /* 0x4A */ u8 unk4A;
  /* 0x4B */ s8 laps;
  /* 0x4C */ s8 race_type;
  /* 0x4D */ s8 vehicle;
  /* 0x4E */ s8 available_vehicles;

  /* 0x4F */ s8 unk4F[3];

  /* 0x52 */ u8 music;
  /* 0x53 */ u8 unk53;
  /* 0x54 */ u16 instruments;

  /* 0x56 */ u8 pad56[0x1A];

  /* 0x70 */ LevelHeader_70 *unk70;
  /* 0x74 */ s8 *unk74[7];

  // Weather related?
  /* 0x90 */ s16 weather_enable;
  /* 0x92 */ s16 unk92;
  /* 0x94 */ u8 unk94;
  /* 0x95 */ u8 unk95;
  /* 0x96 */ s16 unk96;
  /* 0x98 */ s16 unk98;
  /* 0x9A */ s16 unk9A;

  /* 0x9C */ s8 cameraFOV; // Must be a value within [0, 90]
  /* 0x9D */ u8 bgColorRed;
  /* 0x9E */ u8 bgColorGreen;
  /* 0x9F */ u8 bgColorBlue;
  /* 0xA0 */ s32 unkA0;
  /* 0xA4 */ TextureHeader *unkA4;
  /* 0xA8 */ u16 unkA8;
  /* 0xAA */ u16 unkAA;
  /* 0xAC */ PulsatingLightData *pulseLightData;

  /* 0xB0 */ s16 unkB0;
  /* 0xB2 */ u8 unkB2;
  /* 0xB3 */ u8 voiceLimit;
  /* 0xB3 */ u8 unkB4;
  /* 0xB3 */ u8 unkB5;
  /* 0xB3 */ u8 unkB6;
  /* 0xB3 */ u8 unkB7;
  /* 0xB4 */ u8 padB8[0x2];
  /* 0xBA */ s16 unkBA;
  /* 0xBE */ u8 unkBE;
  /* 0xBE */ u8 unkBF;
  /* 0xBE */ u8 unkC0;
  /* 0xC1 */ u8 unkC1;
  /* 0xC2 */ u8 unkC2;
  /* 0xC3 */ u8 unkC3;
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
    s16 u, v;
} TexCoords;

/* Size: 16 bytes */
typedef struct Triangle {
    union {
        struct {
            /* 0x00 */ u8 drawBackface; // 0x40 = Draw backface, 0x00 = Cull backface
            /* 0x01 */ u8 vi0;          // First vertex index
            /* 0x02 */ u8 vi1;          // Second vertex index
            /* 0x03 */ u8 vi2;          // Third vertex index
        };
    /* 0x00 */ u32 vertices; // For convenience?
    };
/* 0x04 */ TexCoords uv0;   // Texture coordinates for the first vertex
/* 0x08 */ TexCoords uv1;   // Texture coordinates for the second vertex
/* 0x0C */ TexCoords uv2;   // Texture coordinates for the third vertex
} Triangle;

/* Size: 12 bytes */
typedef struct TriangleBatchInfo {
/* 0x00 */ u8  textureIndex; // 0xFF = No texture
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
/* 0x00 */ s32 *anim;
/* 0x04 */ s32 unk4;
} ObjectModel_44;

typedef struct ObjectModel {
/* 0x00 */ TextureInfo *textures;
/* 0x04 */ Vertex *vertices;
/* 0x08 */ Triangle *triangles;
/* 0x0C */ s32 *unkC;
/* 0x10 */ s32 *unk10;
           u8 pad0[0x0E];
/* 0x22 */ s16 numberOfTextures;
/* 0x24 */ s16 numberOfVertices;
/* 0x26 */ s16 numberOfTriangles;
/* 0x28 */ s16 numberOfBatches;
           u8 pad2A[6];
/* 0x30 */ s16 unk30;
           u8 pad32[6];
/* 0x38 */ TriangleBatchInfo *batches;
/* 0x3C */ u8 pad3C[4];
/* 0x40 */ s32 *unk40;
/* 0x44 */ ObjectModel_44 *animations;
/* 0x48 */ s16 numberOfAnimations;
} ObjectModel;

/* Size: 0x44 bytes */
typedef struct LevelModelSegment {
/* 0x00 */ Vertex *vertices;
/* 0x04 */ Triangle *triangles;
           u8 pad8[4];
/* 0x0C */ TriangleBatchInfo *batches;
/* 0x10 */ s32 unk10;
/* 0x14 */ u8 *unk14;
/* 0x18 */ s16 *unk18;
/* 0x1C */ s16 numberOfVertices;
/* 0x1E */ s16 numberOfTriangles;
/* 0x20 */ s16 numberOfBatches;
           u8 pad22[0x09];
/* 0x2B */ s8 unk2B;           
           u8 pad2C[4];
/* 0x30 */ s16 unk30;
/* 0x32 */ s16 unk32;
           s16 *unk34;
/* 0x38 */ s16 unk38;
           u8 pad3A[6];
/* 0x40 */ u8 unk40;
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
    s16 leftNode;   // less than split value
    s16 rightNode;  // greater or equal to split value?
    u8  splitType;  // 0 = Camera X, 1 = Camera Y, 2 = Camera Z
    u8  segmentIndex;
    s16 splitValue; // Decides left or right
} BspTreeNode;

typedef struct LevelModel {
/* 0x00 */ TextureInfo *textures;
/* 0x04 */ LevelModelSegment *segments;
/* 0x08 */ LevelModelSegmentBoundingBox *segmentsBoundingBoxes;
/* 0x0C */ s32 unkC;
/* 0x10 */ u8 *segmentsBitfields;
/* 0x14 */ BspTreeNode *segmentsBspTree;
/* 0x18 */ s16 numberOfTextures;
/* 0x1A */ s16 numberOfSegments;
           u8 pad1C[4];
/* 0x20 */ s32 unk20; //spriteIndex?
           u8 pad24[0x14];
/* 0x38 */ u32 minimapColor;           
           u8 pad3C[0xC];
/* 0x48 */ s32 modelSize;
} LevelModel;

typedef struct Object_3C {
    u8 pad0[0x2];
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s8 unk8;
    u8 pad9[0x4];
    u8 unkD;
} Object_3C;

typedef enum {
    OBJECT_MODEL_TYPE_3D_MODEL,
    OBJECT_MODEL_TYPE_SPRITE_BILLBOARD,
    OBJECT_MODEL_TYPE_VEHICLE_PART,
    OBJECT_MODEL_TYPE_UNKNOWN3,
    OBJECT_MODEL_TYPE_UNKNOWN4,
} ObjectModelType;

typedef struct ObjectHeader {
             u8 pad0[0x4];
  /* 0x04 */ f32 unk4;
  /* 0x08 */ f32 unk8;
  /* 0x0C */ f32 scale;
             u8 pad10[0x20];
  /* 0x30 */ u16 unk30;
  /* 0x32 */ s16 unk32;
             u8 pad34[9];
  /* 0x3D */ u8 unk3D;
             u8 pad3E[16];
             s16 unk4E; //Used in func_8002A900?
             u8 pad50[3];
  /* 0x53 */ s8 modelType;
  /* 0x54 */ s8 behaviorId;
  /* 0x55 */ s8 numberOfModelIds; // size of array pointed by Object->unk68
             u8 pad56;
  /* 0x57 */ s8 unk57;
             u8 pad58[0x8];
  /* 0x60 */ char internalName[16];
  /* 0x70 */ u8 unk70;
  /* 0x71 */ u8 unk71;
             u8 pad72[0x6];
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

typedef struct Object_4C {
    void *unk0;
    u8 pad4[0xC];
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    s16 unk14;
    s8 unk16;
    s8 unk17;
} Object_4C;

typedef struct Object_50 {
    f32 unk0;
    u8 pad4[0x4];
    s16 unk8;
    s16 unkA;
} Object_50;

typedef struct Object_54 {
    s32 unk0;
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
} Object_54;

typedef struct Object_5C {
    u8 pad0[0x100];
    void *unk100;
} Object_5C;

typedef struct Object_60 {
    s32 unk0;
    void *unk4; // Object* pointer
} Object_60;

struct Object;

typedef struct Object_Original {
    union {
        f32 unk0;
        struct {
            s8 unk0;
            s8 unk1;
            s8 unk2;
            s8 unk3;
        } unk0_b;
    } unk0_a;
    s32 unk4;
    u8 pad8[4];
    union {
        struct {
            u8 byteC;
            u8 byteD;
        } bytes;
        s16 half;
    } unkCD;
    u8 unkE;
    s8 unkF;
    u8 unk10;
    u8 unk11;
    u8 pad12[6];
    u8 unk18;
    u8 pad19[7];
    u32 unk20;
    u32 unk24;
    s16 unk28;
    s16 unk2A;
    s32 unk2C;
    s32 unk30;
    s16 unk34;
    s8 unk36;
    u8 pad37[0x39];
    u8 unk70;
    u8 unk71;
    u8 unk72;
    u8 unk73;
    f32 unk74;
    f32 unk78;
    f32 unk7C;
    f32 unk80;
    u8 pad84[0x30];
    /* 0xB4 */ f32 throttle;
    /* 0xB8 */ f32 brake;
    u8 padBC[0x14];
    f32 unkD0;
    u8 padD0[0x24];
    u32 unkF8;
    u8 unkFC;
    u8 padFD[0xB];
    s32 unk108;
    u8 pad10C[0xC];
    s32 unk118;
    u8 pad11C[0x44];
    s16 unk160;
    s16 unk162;
    s16 unk164;
    s16 unk166;
    u8 pad166[0x28];
    u16 unk190;
    u8 unk192;
    u8 unk193;
    u8 pad194[0x26];
    u16 unk1BA;
    u8 pad1BC[0x1A];
    s8 unk1D6;
    s8 unk1D7;
    s8 unk1D8;
    u8 pad1D9[0x19];
    u8 unk1F2;
    u8 unk1F3;
    u8 pad1F4[3];
    u8 unk1F7; // Used in func_8002A900
} Object_Original;

typedef struct Object_Laser {
	s16 unk0;
	u8  unk4[0x185];
	s8  unk187;
} Object_Laser;

typedef struct Object_TrophyCabinet {
    s32 unk0;
    s16 unk4;
} Object_TrophyCabinet;

typedef struct Object_Animator {
    /* 0x00 */ s16 segmentId;
    /* 0x02 */ s16 batchId;
    /* 0x04 */ s16 xSpeedFactor;
    /* 0x06 */ s16 ySpeedFactor;
    /* 0x08 */ s16 xSpeed;
    /* 0x0A */ s16 ySpeed;
} Object_Animator;

typedef struct Object_Animation {
  /* 0x00 */ u8 pad0[0x4A];
  /* 0x4A */ s16 unk4A;
} Object_Animation;

typedef struct Object_WeaponBalloon {
    f32 unk0;
    s16 unk4;
    s8 unk6[0x2];
} Object_WeaponBalloon;

typedef struct Object_Butterfly {
  /* 0x00  */ Triangle triangles[8];
  /* 0x80  */ Vertex vertices[12];
  /* 0xF8  */ TextureHeader *texture;
  /* 0xFC  */ u8 unkFC;
  /* 0xFD  */ u8 unkFD;
  /* 0xFE  */ u8 unkFE;
  /* 0xFF  */ u8 unkFF;
  /* 0x100 */ s32 unk100;
  /* 0x104 */ s16 unk104;
  /* 0x106 */ s16 unk106;
  /* 0x108 */ f32 unk108;
} Object_Butterfly;

typedef struct Object_EffectBox {
    u8 pad0[0x1FE];
    u8 unk1FE;
    u8 unk1FF;
} Object_EffectBox;

typedef struct Object_EggCreator {
    u8 pad0[4];
    struct Object *unk4;
} Object_EggCreator;

typedef struct Object_UnkId58 {
    u8 pad0[0x1D6];
    s8 unk1D6;
} Object_UnkId58;

typedef struct Object_CharacterFlag {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s16 *unk20;
    u8  *unk24;
} Object_CharacterFlag;

typedef struct Object_80035F6C_2 {
    u8 pad0[3];
    s8 unk3;
} Object_80035F6C_2;

typedef struct Object_Snowball {
    u8 pad0[0x20];
    u32 unk20;
    s16 unk24;
    u8 pad28[0x12];
    s8 unk38;
} Object_Snowball;

typedef struct Object_AnimCamera {
    u8 pad0[0x30];
    s8 unk30;
    u8 pad31[0x13];
    s8 unk44;
} Object_AnimCamera;

typedef struct Object_AnimCar {
    u8 pad0[0x148];
    struct Object *unk148;
} Object_AnimCar;

typedef struct Object_InfoPoint {
    s16 unk0;
} Object_InfoPoint;

typedef struct Object_TTDoor {
    f32 unk0;
    u8 pad4[4];
    s32 unk8;
    u8 padC[3];
    s8 unkF;
    u8 pad10[2];
    u8 unk12;
    u8 unk13;
} Object_TTDoor;

typedef struct Object_WorldKey {
    s16 unk0;
} Object_WorldKey;

typedef struct Object_AudioLine {
    u8 unk0;
    u8 pad1;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    union {
        struct {
            u8 unk8;
            u8 unk9;
            u8 unkA;
            u8 padB;
        } unk_struct;
        s32 unk8_word;
    } unk_union;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u8 unk12;
} Object_AudioLine;

typedef struct Object_AudioReverb {
    u16 pad0;
    s16 unk2;
    u8 unk4;
    u8 unk5;
} Object_AudioReverb;

typedef struct Object_TexScroll {
    s16 unk0;
    s16 pad2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} Object_TexScroll;

typedef struct Object_Frog {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[3];
    u8 unk19;
    u8 pad1A[6];
    f32 unk20;
    f32 unk24;
    u8 pad28[8];
    f32 unk30;
} Object_Frog;

typedef struct Object_Wizpig2 {
    u8 pad0[0x70];
    u8 unk70;
    u8 pad71;
    u8 unk72;
    u8 pad73;
    f32 unk74;
} Object_Wizpig2;

typedef struct Object_Exit {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s8 unk14;
} Object_Exit;

typedef struct Object_Racer {
  /* 0x000 */ s16 playerIndex; // -1 = AI Controlled, 0 to 3 = Object controlled
  /* 0x002 */ u8 pad2;
  /* 0x003 */ s8 characterId; // Affects minimap color, horn, voice, etc.
  /* 0x004 */ u8 pad4[0x20];
  /* 0x024 */ s32 unk24;
  /* 0x028 */ u16 unk28;
  /* 0x02A */ u16 unk2A;
  /* 0x02C */ f32 velocity;
  /* 0x030 */ f32 lateral_velocity;
  /* 0x034 */ u8 pad[0x4];
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
  /* 0x068 */ u8 pad68[0x24];
  /* 0x08C */ f32 stretch_height;
  /* 0x090 */ f32 stretch_height_cap;
  /* 0x094 */ f32 camera_zoom;
  /* 0x098 */ u8 pad98[0x4];
  /* 0x09C */ f32 pitch;
  /* 0x0A0 */ u8 padA0[0x8];
  /* 0x0A8 */ f32 checkpoint_distance;
  /* 0x0AC */ u8 padAC[0x8];
  /* 0x0B4 */ f32 throttle;
  /* 0x0B8 */ f32 brake;
  /* 0x0BC */ u8 padBC[0x4C];
  /* 0x108 */ s32 unk108;
  /* 0x10C */ u8 pad10C[0xC];
  /* 0x118 */ s32 unk118;
  /* 0x11C */ u8 pad11C[0xC];
  /* 0x128 */ u32 lap_times[3];
  /* 0x134 */ u8 pad134[0x10];
  /* 0x144 */ struct Object *held_obj;
  /* 0x148 */ struct Object *unk148;
  /* 0x14C */ struct Object *unk14C;
  /* 0x150 */ u8 pad150[0x4];
  /* 0x154 */ struct Object *unk154;
  /* 0x158 */ u8 pad158[0x1A];
  /* 0x172 */ u8 balloon_type;
  /* 0x173 */ u8 balloon_quantity;
  /* 0x174 */ u8 balloon_level;
  /* 0x175 */ u8 pad175[0xE];
  /* 0x183 */ s8 unk183;
  /* 0x184 */ s8 pad184;
  /* 0x185 */ s8 bananas;
  /* 0x186 */ u8 unk186;
  /* 0x187 */ s8 unk187;
  /* 0x188 */ u8 pad188[0x4];
  /* 0x18C */ s16 unk18C;
  /* 0x18E */ s16 unk18E;
  /* 0x190 */ u8 pad190[0x10];
  /* 0x1A0 */ s16 unk1A0;
  /* 0x1A2 */ s16 unk1A2;
  /* 0x1A4 */ s16 unk1A4;
  /* 0x1A6 */ u8 pad1A6[0x23];
  /* 0x1C9 */ u8 unk1C9;
  /* 0x1CA */ s8 unk1CA;
  /* 0x1CB */ u8 pad1CB[0x3];
  /* 0x1CE */ u8 unk1CE;
  /* 0x1CF */ u8 pad1CF[0x4];
  /* 0x1D3 */ s8 unk1D3;
  /* 0x1D4 */ u8 pad1D4[0x2];
  /* 0x1D6 */ s8 unk1D6;
  /* 0x1D7 */ s8 unk1D7;
  /* 0x1D8 */ s8 unk1D8;
  /* 0x1D9 */ u8 pad1D9[0x2];
  /* 0x1DB */ s8 spinout_timer;
  /* 0x1DC */ u8 wheel_surfaces[4];
  /* 0x1E0 */ u8 pad1E0[0x1];
  /* 0x1E1 */ s8 unk1E1;
  /* 0x1E2 */ s8 unk1E2;
  /* 0x1E3 */ u8 pad1E3[0x3];
  /* 0x1E6 */ s8 drift_direction;
  /* 0x1E7 */ u8 pad1E7[0x6];
  /* 0x1ED */ s8 squish_timer;
  /* 0x1EE */ u8 pad1EE[0x1];
  /* 0x1EF */ u8 boost_sound;
  /* 0x1F0 */ u8 pad1F0[0x2];
  /* 0x1F2 */ u8 unk1F2;
  /* 0x1F3 */ u8 pad1F3[0x2];
  /* 0x1F5 */ u8 unk1F5;
  /* 0x1F6 */ u8 pad1F6[0x1];
  /* 0x1F7 */ u8 transparency;
  /* 0x0290 */ u8 indicator_type;
  /* 0x0291 */ s8 indicator_timer;
  /* 0x1FA */ u8 pad1FA[0x6];
  /* 0x200 */ s8 unk200;
  /* 0x201 */ u8 pad201[0x2];
  /* 0x203 */ s8 unk203;
  /* 0x204 */ s16 unk204;
  /* 0x206 */ u8 pad206[0x6];
  /* 0x20C */ u8 unk20C;
  /* 0x20D */ u8 pad20D[0x1];
  /* 0x20E */ s16 unk20E;
  /* 0x210 */ s8 unk210;
  /* 0x211 */ u8 pad211[0x2];
  /* 0x213 */ s8 unk213;
  /* 0x214 */ s8 unk214;
  /* 0x215 */ s8 unk215;
  /* 0x216 */ u8 pad216[0x6];
  /* 0x21C */ u8 unk21C;
} Object_Racer;

typedef struct Object_Bonus {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s8 unk14;
} Object_Bonus;

typedef struct Object_ModeChange {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s8 unk14;
} Object_ModeChange;

typedef struct Object_GoldenBalloon {
    f32 unk0;
    u8 pad4[0x8];
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    s8 unk10;
    f32 unk14;
} Object_GoldenBalloon;

typedef struct Object_Door {
    f32 unk0;
    u8 pad4[0x4];
    s32 unk8;
    s16 padA;
    s8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    u8 unk14;
} Object_Door;

typedef struct Object_Trigger {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s32 unk10;
    s8 unk14;
} Object_Trigger;

typedef struct Object_Audio {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
} Object_Audio;

typedef struct Object_MidiFade {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 unk2F[16];
    u8 unk40;
} Object_MidiFade;

typedef struct Object_MidiFadePoint {
    u16 unk0;
    u16 unk2;
    f32 unk4;
    f32 unk8;
    u8 unkC[16];
    u8 unk1C;
} Object_MidiFadePoint;

typedef struct Object_PosArrow {
    s16 unk0;
    u8 pad4[0x14E];
    struct Object *unk150;
} Object_PosArrow;

typedef struct Object_Banana {
    u8 pad0[4];
    struct Object *spawner;
} Object_Banana;

typedef struct Object_FogChanger {
    s16 unk0;
} Object_FogChanger;

typedef struct Object_64 {
    union {
        Object_Original original;
        Object_Laser laser;
        Object_TrophyCabinet trophy_cabinet;
        Object_Animator animator;
        Object_Animation animation;
        Object_WeaponBalloon weapon_balloon;
        Object_Butterfly butterfly;
        Object_EffectBox effect_box;
        Object_EggCreator egg_creator;
        Object_UnkId58 unkid58;
        Object_CharacterFlag character_flag;
        Object_80035F6C_2 obj80035F6C_2;
        Object_Snowball snowball;
        Object_AnimCamera anim_camera;
        Object_AnimCar anim_car;
        Object_InfoPoint info_point;
        Object_TTDoor tt_door;
        Object_WorldKey world_key;
        Object_AudioLine audio_line;
        Object_AudioReverb audio_reverb;
        Object_TexScroll tex_scroll;
        Object_Frog frog;
        Object_Wizpig2 wizpig2;
        Object_Exit exit;
        Object_Racer racer;
        Object_Bonus bonus;
        Object_ModeChange mode_change;
        Object_GoldenBalloon golden_balloon;
        Object_Door door;
        Object_Trigger trigger;
        Object_Audio audio;
        Object_MidiFade midi_fade;
        Object_MidiFadePoint midi_fade_point;
        Object_PosArrow pos_arrow;
        Object_Banana banana;
        Object_FogChanger fog_changer;
    };
} Object_64;

typedef struct Object_68 {
    u8 pad00[0x20];
    s8 unk20;
 } Object_68;

/* Size: 0x20 bytes */
typedef struct Object_6C {
    u8  pad0[0x4];
    s16 unk4;
    u8  pad6[0x1A];
} Object_6C;

/* Size: 0x018 bytes */
typedef struct ObjectTransform {
  /* 0x0000 */ s16 y_rotation;
  /* 0x0002 */ s16 x_rotation;
  /* 0x0004 */ s16 z_rotation;
  /* 0x0006 */ s16 unk6; // Flags?
  /* 0x0008 */ f32 scale;
  /* 0x000C */ f32 x_position;
  /* 0x0010 */ f32 y_position;
  /* 0x0014 */ f32 z_position;
} ObjectTransform;

/* Size: 0x44 bytes */
typedef struct ObjectSegment {
  /* 0x0000 */ ObjectTransform trans;
  /* 0x0018 */ s16 unk18;
  /* 0x001A */ s16 unk1A;
  /* 0x001C */ f32 x_velocity;
  /* 0x0020 */ f32 y_velocity;
  /* 0x0024 */ f32 z_velocity;
  /* 0x0028 */ f32 unk28;

  union {
      struct {
          /* 0x002C */ s16 upper;
          /* 0x002E */ s16 lower;
      } half;
      /* 0x002C */ f32 word;
  } unk2C;

  /* 0x0030 */ f32 unk30;

  union {
    /* 0x0034 */ f32 unk34;
    /* 0x0034 */ s16 levelSegmentIndex;
  } unk34_a;

  union {
      struct {
          /* 0x0038 */ u8 upper;
          /* 0x0039 */ u8 lower;
      } half;
      /* 0x0038 */ s16 word;
  } unk38;

  /* 0x003A */ s8 unk3A;
  /* 0x003B */ s8 unk3B;

  union {
    /* 0x003C */ Object_3C* unk3C;
    /* 0x003C */ f32 unk3C_f;
  } unk3C_a;

  /* 0x0040 */ ObjectHeader *header;
} ObjectSegment;

/* Size: 0x0630 bytes */
typedef struct Object {
  /* 0x0000 */ ObjectSegment segment;
  /* 0x0044 */ void *unk44;
  /* 0x0048 */ s16 behaviorId;
  /* 0x004A */ s16 unk4A;
  /* 0x004C */ Object_4C *unk4C; //player + 0x318
  /* 0x0050 */ Object_50 *unk50; //player + 0x2F4
  /* 0x0054 */ Object_54 *unk54; //player + 0x2C0
  /* 0x0058 */ void *unk58; //player + 0x304
  /* 0x005C */ Object_5C *unk5C;

  /* 0x0060 */ Object_60 *unk60; //player + 0x340
  /* 0x0064 */ Object_64 *unk64; //player + 0x98
  /* 0x0068 */ Object_68 **unk68; //player + 0x80
  /* 0x006C */ Object_6C *unk6C; //player + 0x370
  /* 0x0070 */ u32 unk70;

  /* 0x0074 */ u32 unk74;

  union {
  /* 0x0078 */ s32 unk78;
  /* 0x0078 */ f32 unk78f;
  };

  union {
      struct {
          s16 upper;
          s16 lower;
      } half;
      s32 word;
  } unk7C;

  /* 0x0080 */ void *unk80;
  /* 0x0084 */ u32 unk84;
  /* 0x0088 */ u32 unk88;

  /* 0x008C */ u32 unk8C;
  /* 0x0090 */ u32 unk90;
  /* 0x0094 */ u32 unk94;

  /* 0x0098 */ Object_64 obj;

  // May be a part of obj (likely Object_Player).
  /* 0x02B8 */ u8 pad2A8[0x8];

  /* 0x02C0 */ f32 unk2C0;

  /* 0x02C4 */ u8 red;
  /* 0x02C5 */ u8 blue;
  /* 0x02C6 */ u8 green;
  /* 0x02C7 */ u8 alpha;

  /* 0x02C8 */ u32 unk2C8;
  /* 0x02CC */ u32 unk2CC;
  /* 0x02D0 */ u32 unk2D0;
  /* 0x02D4 */ u32 unk2D4;
  /* 0x02D8 */ u32 unk2D8;

  /* 0x02DC */ u16 unk2DC;
  /* 0x02DE */ u16 unk2DE;
  /* 0x02E0 */ u16 unk2E0;

  /* 0x02E2 */ u16 unk2E2;
  /* 0x02E4 */ u32 unk2E4;

  /* 0x02E8 */ f32 unk2E8;
  /* 0x02EC */ f32 unk2EC;
  /* 0x02F0 */ u32 unk2F0;

  /* 0x02F4 */ f32 shadow_scale;
  /* 0x02F8 */ void *unk2F8;
  /* 0x02FC */ u16 unk2FC;
  /* 0x02FE */ u16 unk2FE;
  /* 0x0300 */ u32 unk300;

  /* 0x0304 */ f32 unk0304;

  /* 0x0308 */ u32 unk308;
  /* 0x030C */ u32 unk30C;
  /* 0x0310 */ u32 unk310;
  /* 0x0314 */ u32 unk314;

  /* 0x0318 */ void *nearest_obj_ptr;
  /* 0x031C */ f32 unk31C;
  /* 0x0320 */ f32 unk320;
  /* 0x0324 */ f32 unk324;

  /* 0x0328 */ u32 unk328;
  /* 0x032C */ u32 unk32C;
  /* 0x0330 */ u32 unk330;
  /* 0x0334 */ u32 unk334;
  /* 0x0338 */ u32 unk338;
  /* 0x033C */ u32 unk33C;

  /* 0x0340 */ u32 unk340;
  /* 0x0344 */ void *unk344;
  /* 0x0348 */ void *unk348;
  /* 0x034C */ void *unk34C;
  /* 0x0350 */ void *unk350;

  /* 0x0354 */ u32 unk354;
  /* 0x0358 */ u32 unk358;
  /* 0x035C */ u32 unk35C;
  /* 0x0360 */ u32 unk360;
  /* 0x0364 */ u32 unk364;
  /* 0x0368 */ u32 unk368;
  /* 0x036C */ u32 unk36C;

  /* 0x0370 */ void *unk370;
  /* 0x0374 */ s32 unk374;

  u32 unk378[174]; // Not an array. Unknown values.
} Object;

typedef struct unk80027FC4 {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} unk80027FC4;

// Unused
typedef struct GhostHeaderChecksum {
	u8  levelID;
    u8  vehicleID; // 0 = Car, 1 = Hovercraft, 2 = Plane
} GhostHeaderChecksum;

/* Size: 8 bytes */
typedef struct GhostHeader {
    //GhostHeaderChecksum checksum;
    s16 checksum;
    u8  characterID; // 9 = T.T.
    u8  unk3; // Might just be padding?
    s16 time; // In frames, where 60 frames = 1 second.
    s16 nodeCount;
} GhostHeader;

/* Size: 12 bytes */
typedef struct GhostNode {
    s16 x;
    s16 y;
    s16 z;
    s16 zRotation; // This order is correct.
    s16 xRotation;
    s16 yRotation;
} GhostNode;

/* Size: 12 bytes */
typedef struct GhostDataFrame {
    u8 pad0[12];
} GhostDataFrame;

/* Size: 0x18 bytes */
typedef struct unk8011D510 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} unk8011D510;

typedef struct unk80042178 {
    u8 pad0[0x20];
} unk80042178;

#endif
