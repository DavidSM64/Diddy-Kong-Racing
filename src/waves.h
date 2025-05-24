#ifndef _WAVES_H_
#define _WAVES_H_

#include "types.h"
#include "structs.h"

/* Size: 4 bytes */
typedef struct {
    u8 unk0[4];
} LevelModelSubArray;

/* Size: 0x1C bytes */
typedef struct {
    LevelModelSegment *block;
    s16 unk4; // something with x
    s16 unk6; // something with y AND used as playerIndex
    s16 unk8; // something with z
    u8 unkA; // some sort of x ratio
    u8 unkB; // some sort of z ratio / index of D_8012A0E8
    u32 unkC; // indexes D_800E30D4
    s16 unk10;
    s16 unk12;
    LevelModelSubArray unk14[2];
} LevelModel_Alternate;

/* Size: 0x40 bytes */
typedef struct unk800E3190 {
    f32 unk0;
    f32 unk4;
    f32 x_position;
    f32 z_position;
    f32 unk10;
    f32 radius;
    s16 unk18;
    u16 unk1A;
    u32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 unk31;
    u8 unk32;
    u8 pad33[0xE];
} unk800E3190;

typedef struct unk800E3184 {
    u8 unk0[8];
} unk800E3184;

typedef struct unk8012A5E8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s32 unk8;
} unk8012A5E8;

typedef struct WaveControlSine {
    s32 sineStep;   // Amount the sine angle increases by.
    f32 height;     // Peak height of the wave level.
    s32 sineBase;   // Value the sine angle starts at.
} WaveControlSine;

typedef struct WaveControl {
    s32 subdivisions; // Number of subdivisions the wave plane has. Higher values use more triangles
    s32 tileCount; // Number of wave tiles squared.
    WaveControlSine initSine[2];
    s32 seedSize; // count of elements in gWaveHeightTable
    s32 waveViewDist; // View distance refers to number of blocks away wavegen works on that tile. Vanilla sets 3 or 5.
    s32 doubleDensity; // If active, doubles the level of subdivisons done with waves.
    s32 textureId;
    s32 uvScaleX; // multiplier for texture width
    s32 uvScaleY; // multiplier for texture height
    s32 uvScrollX;
    s32 uvScrollY;
    f32 magnitude; // Global wave strength
    f32 unk44; // something related to height / scale
    f32 unk48; // used in vertex RGBA calculation
    s32 xlu; // Determines whether to use semitransparent or opaque render modes by default.
} WaveControl;

typedef struct unk800BFC54_arg0 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[4];
    u16 unk18;
    u16 unk1A;
    u32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
} unk800BFC54_arg0;

// /* Size: 10 bytes */
// typedef struct Vertex {
// /* 0x00 */ s16 x;
// /* 0x02 */ s16 y;
// /* 0x04 */ s16 z;
// /* 0x06 */ u8  r;
// /* 0x07 */ u8  g;
// /* 0x08 */ u8  b;
// /* 0x09 */ u8  a;
// } Vertex;

void waves_free(void);
void waves_visibility_reset(void);
s32 waves_visibility(LevelModelSegment *arg0);
void func_800BBDDC(LevelModel *level, LevelHeader *header);
void func_800BFE98(s32 updateRate);
void waves_init_header(LevelHeader *header);
void func_800BBE08(LevelModel *level, LevelHeader *header);
void obj_loop_wavepower(Object *obj);
void func_800BFC54(unk800BFC54_arg0 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_800BF3E4(Object *obj);
f32 log_wave_height(Object_Log *log, s32 updateRate);
void func_800BA288(s32 arg0, s32 arg1);
void func_800BF9F8(unk800BFC54_arg0 *arg0, f32 arg1, f32 arg2);
unk800E3190 *func_800BF634(Object *obj, f32 xPos, f32 zPos, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8);
void waves_alloc(void);
void wave_load_material(TextureHeader *tex, s32 rtile);

Object_64 *func_800BE654(s32, f32, f32);
void func_800BBF78(LevelModel *model);   // Non Matching
f32 func_800BB2F4(s32, f32, f32, Vec3f *);
void func_800B8C04(s32, s32, s32, s32, s32);
void wavegen_add(Object *);
f32 waves_get_y(s32, s32, s32);
void func_800BC6C8(void);
void func_800BCC70(LevelModel *arg0);

#endif
