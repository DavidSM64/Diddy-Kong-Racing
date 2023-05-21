#ifndef _TRACKS_H_
#define _TRACKS_H_

#include "types.h"
#include "structs.h"
#include "f3ddkr.h"
#include "racer.h"

#define LOCAL_OFFSET_TO_RAM_ADDRESS(type, ptr) \
    ptr = (type)((s32)((u8*)ptr) + (s32)((u8*)mdl))

enum TriangleBatchFlags {
    BATCH_FLAGS_NONE = 0,
    BATCH_FLAGS_UNK00000001 = (1 << 0),
    BATCH_FLAGS_UNK00000002 = (1 << 1),
    BATCH_FLAGS_UNK00000004 = (1 << 2),
    BATCH_FLAGS_UNK00000008 = (1 << 3),
    BATCH_FLAGS_DEPTH_WRITE = (1 << 4),
    BATCH_FLAGS_UNK00000020 = (1 << 5),
    BATCH_FLAGS_UNK00000040 = (1 << 6),
    BATCH_FLAGS_UNK00000080 = (1 << 7),
    BATCH_FLAGS_HIDDEN = (1 << 8),
    BATCH_FLAGS_UNK00000200 = (1 << 9),
    BATCH_FLAGS_UNK00000400 = (1 << 10),
    BATCH_FLAGS_UNK00000800 = (1 << 11),
    BATCH_FLAGS_UNK00001000 = (1 << 12),
    BATCH_FLAGS_WATER =             (1 << 13),
    BATCH_FLAGS_FORCE_NO_SHADOWS =  (1 << 14),
    BATCH_FLAGS_ENVMAP = (1 << 15),
    BATCH_FLAGS_TEXTURE_ANIM = (1 << 16),
    BATCH_FLAGS_UNK00020000 = (1 << 17),
    BATCH_FLAGS_PULSATING_LIGHTS = (1 << 18),
    BATCH_FLAGS_UNK00080000 = (1 << 19),
    BATCH_FLAGS_UNK00100000 = (1 << 20),
    BATCH_FLAGS_UNK00200000 = (1 << 21),
    BATCH_FLAGS_UNK00400000 = (1 << 22),
    BATCH_FLAGS_UNK00800000 = (1 << 23),
    BATCH_FLAGS_UNK01000000 = (1 << 24),
    BATCH_FLAGS_UNK02000000 = (1 << 25),
    BATCH_FLAGS_UNK04000000 = (1 << 26),
    BATCH_FLAGS_UNK08000000 = (1 << 27),
    BATCH_FLAGS_UNK10000000 = (1 << 28),
    BATCH_FLAGS_UNK20000000 = (1 << 29),
    BATCH_FLAGS_UNK40000000 = (1 << 30),
    BATCH_FLAGS_UNK80000000 = (1 << 31),
};

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

/* Size: 0x10 bytes */
typedef struct unk8011D474 {
    TriangleList *unk0;
    TriangleList *unk4;
    Vertex *unk8;
    Vertex *unkC;
} unk8011D474;

/* Size: 0x8 bytes */
typedef struct unk8011D478 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} unk8011D478;

// In this struct, data is rightshifted 16 bytes, so make the smooth transition more precise.
typedef struct EnvironmentFog {
    s32 r;
    s32 g;
    s32 b;
    s32 near;
    s32 far;
} EnvironmentFog;

typedef struct EnvironmentFogCompact {
    u8 r;
    u8 g;
    u8 b;
    s16 near;
    s16 far;
} EnvironmentFogCompact;

/* Size: 0x38 bytes */
typedef struct FogData {
    EnvironmentFog fog;                 // Current fog properties. What you'll actually see ingame.
    EnvironmentFog addFog;              // Fog override. This will apply over the current fog to give a smooth transition effect.
    EnvironmentFogCompact intendedFog;  // Fog properties the game will try to be if the switch timer is 0.
    s32 switchTimer;
    Object *fogChanger;
} FogData;

typedef struct WaterProperties {
    f32 waveHeight;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    s8 type;
} WaterProperties;

enum WaveTypes {
    WATER_CALM = 11,
    WATER_WAVY = 14,
    WATER_UNK_F = 15
};

extern s32 D_800DC870;
extern unknown800DC874 D_800DC874;
extern unknown800DC874 D_800DC87C;

extern f32 D_800DC884[10];

extern LevelModel *gCurrentLevelModel;
extern LevelHeader *gCurrentLevelHeader;

extern s32 D_800DC920;
extern s32 D_800DC928;

extern s8 D_800DC92C[24];

s32 set_scene_viewport_num(s32 arg0);
void func_800257D0(void);
void spawn_skydome(s32 arg0);
void set_skydome_visbility(s32 renderSky);
void render_skydome(void);
void set_anti_aliasing(s32 settings);
void add_segment_to_order(s32 segmentIndex, s32 *segmentsOrderIndex, u8 *segmentsOrder);
s32 get_inside_segment_count_xz(s32 x, s32 z, s32 *arg2);
s32 get_inside_segment_count_xyz(s32 *arg0, s16 xPos1, s16 yPos1, s16 zPos1, s16 xPos2, s16 yPos2, s16 zPos2);
LevelModelSegment *get_segment(s32 arg0);
LevelModelSegmentBoundingBox *get_segment_bounding_box(s32 arg0);
void func_8002ACC8(s32 arg0);
s32 func_8002ACD4(f32 *arg0, f32 *arg1, f32 *arg2);
s32 func_8002B9BC(Object *obj, f32 *arg1, f32 *arg2, s32 arg3);
void func_8002C71C(LevelModelSegment *segment);
LevelModel *get_current_level_model(void);
void get_fog_settings(s32 playerID, s16 *near, s16 *far, u8 *r, u8 *g, u8 *b);
void reset_fog(s32 playerID);
void update_fog(s32 playerID, s32 updateRate);
void apply_fog(s32 playerID);
void compute_scene_camera_transform_matrix(void);
void func_80027E24(s32 updateRate);
s32 check_if_inside_segment(Object *obj, s32 segmentIndex);
s32 get_level_segment_index_from_position(f32 xPos, f32 yPos, f32 zPos);
void traverse_segments_bsp_tree(s32 nodeIndex, s32 segmentIndex, s32 segmentIndex2, u8 *segmentsOrder, s32 *segmentsOrderIndex);
void render_level_geometry_and_objects(void);
void func_8002D670(Object *obj, ShadowData *shadow);
void render_object_shadow(Object *obj, ShadowData *shadow);
s32 should_segment_be_visible(LevelModelSegmentBoundingBox *bb);
s32 check_if_in_draw_range(Object *obj);
void func_8002C954(LevelModelSegment *segment, LevelModelSegmentBoundingBox *bbox, s32 arg2);
void draw_gradient_background(void);
void func_8002D8DC(s32 arg0, s32 arg1, s32 arg2);
void obj_loop_fogchanger(Object* obj);
void initialise_player_viewport_vars(s32 updateRate);
s32 get_wave_properties(f32 yPos, f32 *waterHeight, Vec3f *rotation);
void render_level_segment(s32 segmentId, s32 nonOpaque);
void render_scene(Gfx** dList, MatrixS** mtx, Vertex** vtx, TriangleList** tris, s32 updateRate);


void func_80030664(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5);
void free_track(void);
void func_8002581C(u8 *segmentIds, s32 numberOfSegments, s32 currentViewportIndex);
s32 func_80027568(void);
s32 func_8002CC30(LevelModelSegment*);
s8 func_8002B0F4(s16, f32 xPos, f32 zPos, WaterProperties***); // Definitely not triple pointer, but easiest way to fix warns.
void func_800278E8(s32);
void func_80028050(void);
void initialise_player_viewport_vars(s32);
void func_8002A31C(void);
void update_colour_cycle(s8*, s32);
void func_800AD030(ObjectSegment*);
void func_800B9C18(s32);
void func_800BA8E4(Gfx**, MatrixS**, s32);
void func_8002DE30(Object*);
void func_8002E234(Object*, s32);
void func_80030DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_8002BAB0(s16, f32, f32, f32*);
void func_800249F0(u32 arg0, u32 arg1, s32 arg2, Vehicle vehicle, u32 arg4, u32 arg5, u32 arg6);
void func_800B82B4(LevelModel *, LevelHeader *, s32);
void func_8000C8F8(u32, u32);
void func_80025510(s32);

#endif
