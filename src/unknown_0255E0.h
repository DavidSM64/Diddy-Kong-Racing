#ifndef _UNKNOWN_0255E0_H_
#define _UNKNOWN_0255E0_H_

#include "types.h"
#include "structs.h"
#include "f3ddkr.h"
#include "racer.h"

/* Size: 0x8 bytes */
typedef struct unknown800DC874 {
    union {
        s8 unk00;
        s32 dummy_force_alignment; // Not sure of a better way to do this.
    } unk00_a;
    u16 unk04;
    s16 unk06;
} unknown800DC874;

/* Size: 0x10 bytes */
typedef struct unk8011D0F8 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} unk8011D0F8;

/* Size: 0x10 bytes */
typedef struct unk8011D330 {
    u8 pad0[0x10];
} unk8011D330;

/* Size: 0xA bytes */
typedef struct unk8011D348 {
    u8 pad0[0x9];
    u8 unk9;
} unk8011D348;

/* Size: 0x8 bytes */
typedef struct unk8011D360 {
    struct unk8011D360 *unk0;
    s16 unk4;
    s16 unk6;
} unk8011D360;

/* Size: 0x38 bytes */
typedef struct unk8011D388 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    u8  unk28;
    u8  unk29;
    u8  unk2A;
    s16 unk2C;
    s16 unk2E;
    s32 unk30;
    Object *unk34;
} unk8011D388;

typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
} unk8011D468;

extern s32 D_800DC870;
extern unknown800DC874 D_800DC874;
extern unknown800DC874 D_800DC87C;

extern f32 D_800DC884[10];

extern f32 D_800DC8AC[27];

extern LevelModel *gCurrentLevelModel;
extern LevelHeader *gCurrentLevelHeader;

extern s32 D_800DC920;
extern s32 D_800DC928;

extern s8 D_800DC92C[24];

void func_8006FC30(Matrix, ObjectTransform *); // asm func

s32 func_800249E0(s32 arg0);
void func_800257D0(void);
void func_80027FC4(s32 arg0);
void func_80028044(s32 arg0);
void render_skydome(void);
void func_80028FA0(s32 arg0);
void add_segment_to_order(s32 segmentIndex, s32 *segmentsOrderIndex, u8 *segmentsOrder);
s32 func_8002A05C(s32 x, s32 z, s32 *arg2);
s32 func_8002A134(s32 *arg0, s16 xPos1, s16 yPos1, s16 zPos1, s16 xPos2, s16 yPos2, s16 zPos2);
LevelModelSegment *func_8002A2C8(s32 arg0);
LevelModelSegmentBoundingBox *func_8002A2DC(s32 arg0);
void func_8002ACC8(s32 arg0);
s32 func_8002ACD4(f32 *arg0, f32 *arg1, f32 *arg2);
s32 func_8002B9BC(Object *obj, f32 *arg1, f32 *arg2, s32 arg3);
void func_8002C71C(LevelModelSegment *segment);
LevelModel *get_current_level_model(void);
void func_80030750(s32 arg0, s16 *arg1, s16 *arg2, s8 *arg3, s8 *arg4, s8 *arg5);
void func_800307BC(s32 arg0);
void func_80030838(s32 arg0, s32 arg1);
void func_8003093C(s32 arg0);
void func_80031018(void);
void func_80027E24(s32 arg0);
s32 func_80029DE0(Object *obj, s32 segmentIndex);
s32 get_level_segment_index_from_position(f32 xPos, f32 yPos, f32 zPos);
void traverse_segments_bsp_tree(s32 nodeIndex, s32 segmentIndex, s32 segmentIndex2, u8 *segmentsOrder, s32 *segmentsOrderIndex);
void render_level_geometry_and_objects(void);
void func_8002D670(Object *obj, Object_50 *arg1);
void render_floor_decal(Object *obj, Object_50 *arg1);

//Non Matching
void render_level_segment(s32 segmentId, s32 nonOpaque);
s32 func_8002A5F8(LevelModelSegmentBoundingBox *bb);
void func_80030664(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5);
void render_scene(Gfx** dList, Matrix** mtx, s16** vtx, s8** tris, s32 updateRate);
void func_8002C7D4(void);
s32 func_8002A900(Object *arg0);
Gfx *func_8002581C(u8 *segmentIds, s32 numberOfSegments, s32 currentViewportIndex);
s32 func_80027568(void);
void func_8002C954(LevelModelSegment*, LevelModelSegmentBoundingBox*, s32);
s32 func_8002CC30(LevelModelSegment*);
s8 func_8002B0F4(s16, f32 xPos, f32 zPos, struct TempStruct8**);
s8 func_8002AD08(f32 yPos, f32* waterHeight, s32*);
void func_800278E8(s32);
void func_80028050(void);
void func_800289B8(void);
void func_80028CD0(s32);
void func_8002A31C(void);
void func_8002D8DC(s32, s32, s32);
void func_8007F24C(s8*, s32);
void func_800ACA20(Gfx**, Matrix**, s16**, ObjectSegment*);
void func_800AD030(ObjectSegment*);
void func_800B9C18(s32);
void func_800BA8E4(Gfx**, Matrix**, s32);

#endif
