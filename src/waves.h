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
    s16 originX; // something with x
    s16 originY; // something with y AND used as playerIndex
    s16 originZ; // something with z
    u8 unkA; // some sort of x ratio
    u8 unkB; // some sort of z ratio / index of D_8012A0E8
    u32 unkC; // indexes D_800E30D4
    s16 unk10;
    s16 unk12;
    LevelModelSubArray unk14[2];
} LevelModel_Alternate;

/* Size: 0x40 bytes */
typedef struct WaveGen {
  /* 0x00 */ f32 minZ;
  /* 0x04 */ f32 maxZ;
  /* 0x08 */ f32 x_position;
  /* 0x0C */ f32 z_position;
  /* 0x10 */ f32 radius;
  /* 0x14 */ f32 radiusSq;
  /* 0x18 */ u16 index;
  /* 0x1A */ u16 unk1A;
  /* 0x1C */ u32 unk1C;
  /* 0x20 */ f32 unk20;
  /* 0x24 */ f32 unk24;
  /* 0x28 */ f32 unk28;
  /* 0x2C */ f32 unk2C;
  /* 0x30 */ u8 unk30;
  /* 0x31 */ u8 unk31;
  /* 0x32 */ u8 unk32;
  /* 0x33 */ u8 unk33;
  u32 pad34[3];
} WaveGen;

typedef struct unk800E3184 {
    u8 unk0[8];
} unk800E3184;

typedef struct unk8012A5E8 {
    s16 blockID;
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

void waves_free(void);
void waves_visibility_reset(void);
s32 waves_block_hq(LevelModelSegment *block);
void func_800BBDDC(LevelModel *level, LevelHeader *header);
void func_800BFE98(s32 updateRate);
void waves_init_header(LevelHeader *header);
void func_800BBE08(LevelModel *level, LevelHeader *header);
void obj_loop_wavepower(Object *obj);
void wavegen_scale(WaveGen *gen, f32 radiusAdd, f32 arg2, f32 arg3, f32 arg4);
void wavegen_destroy(Object *obj);
f32 obj_wave_height(Object_Log *log, s32 updateRate);
void func_800BA288(s32 arg0, s32 arg1);
void func_800BF9F8(WaveGen *gen, f32 arg1, f32 arg2);
WaveGen *wavegen_register(Object *obj, f32 xPos, f32 zPos, f32 waveSize, s32 arg4, f32 arg5, f32 arg6, f32 arg7,
                          s32 flags);
void waves_alloc(void);
void wave_load_material(TextureHeader *tex, s32 rtile);
Object_Log *obj_wave_init(s32, f32, f32);
void func_800BBF78(LevelModel *model);
f32 func_800BB2F4(s32, f32, f32, Vec3f *);
void waves_visibility(s32, s32, s32, s32, s32);
void wavegen_add(Object *);
f32 waves_get_y(s32, s32, s32);
void func_800BC6C8(void);
void func_800BCC70(LevelModel *model);

#endif
