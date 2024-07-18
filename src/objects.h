#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "types.h"
#include "structs.h"
#include "f3ddkr.h"
#include "object_functions.h"
#include "libc/math.h"
#include "camera.h"
#include "lights.h"


#define NEW_OBJECT_ENTRY(entryVar, entryId, entrySize, xPos, yPos, zPos) { \
    entryVar.x = (xPos);                                                   \
    entryVar.y = (yPos);                                                   \
    entryVar.z = (zPos);                                                   \
    entryVar.size = ((((entryId) >> 1) & 0x80) | (entrySize));             \
    entryVar.objectID = (s8)(entryId);                                     \
}

#define NODE_NONE 255

enum ObjectBehaviours {
    BHV_NONE,
    BHV_RACER,
    BHV_SCENERY,
    BHV_FISH,
    BHV_ANIMATOR,
    BHV_WEAPON,
    BHV_SMOKE,
    BHV_EXIT,
    BHV_AUDIO,
    BHV_AUDIO_LINE,
    BHV_CAMERA_CONTROL,
    BHV_SETUP_POINT,
    BHV_DINO_WHALE,
    BHV_CHECKPOINT,
    BHV_DOOR,
    BHV_FOG_CHANGER,
    BHV_AINODE,
    BHV_WEAPON_BALLOON,
    BHV_WEAPON_2,
    BHV_AUDIO_LINE_2,
    BHV_UNK_14,
    BHV_UNK_15,
    BHV_BOMB_EXPLOSION,
    BHV_BALLOON_POP,
    BHV_UNK_18,
    BHV_UNK_19,
    BHV_SKY_CONTROL,
    BHV_AUDIO_REVERB,
    BHV_TORCH_MIST,
    BHV_TEXTURE_SCROLL,
    BHV_MODECHANGE,
    BHV_STOPWATCH_MAN,
    BHV_BANANA,
    BHV_LIGHT_RGBA,
    BHV_UNK_22,
    BHV_UNK_23,
    BHV_BUOY_PIRATE_SHIP,
    BHV_WEATHER,
    BHV_BRIDGE_WHALE_RAMP,
    BHV_RAMP_SWITCH,
    BHV_SEA_MONSTER,
    BHV_BONUS,
    BHV_UNK_2A,
    BHV_LENS_FLARE,
    BHV_LENS_FLARE_SWITCH,
    BHV_COLLECT_EGG,
    BHV_EGG_CREATOR,
    BHV_CHARACTER_FLAG,
    BHV_UNK_30,
    BHV_ANIMATION,
    BHV_ANIMATED_OBJECT,
    BHV_CAMERA_ANIMATION,
    BHV_INFO_POINT,
    BHV_CAR_ANIMATION,
    BHV_CHARACTER_SELECT,
    BHV_TRIGGER,
    BHV_VEHICLE_ANIMATION,
    BHV_ZIPPER_WATER,
    BHV_TIMETRIAL_GHOST,
    BHV_WAVE_GENERATOR,
    BHV_WAVE_POWER,
    BHV_BUTTERFLY,
    BHV_PARK_WARDEN,
    BHV_UNK_3F,
    BHV_WORLD_KEY,
    BHV_BANANA_SPAWNER,
    BHV_TREASURE_SUCKER,
    BHV_LOG,
    BHV_LAVA_SPURT,
    BHV_POS_ARROW,
    BHV_HIT_TESTER,
    BHV_MIDI_FADE,
    BHV_HIT_TESTER_2,
    BHV_EFFECT_BOX,
    BHV_TROPHY_CABINET,
    BHV_BUBBLER,
    BHV_FLY_COIN,
    BHV_GOLDEN_BALLOON,
    BHV_LASER_BOLT,
    BHV_LASER_GUN,
    BHV_PARK_WARDEN_2,
    BHV_ANIMATED_OBJECT_2,
    BHV_ZIPPER_GROUND,
    BHV_OVERRIDE_POS,
    BHV_WIZPIG_SHIP,
    BHV_ANIMATED_OBJECT_3,
    BHV_ANIMATED_OBJECT_4,
    BHV_TAJ_TELEPOINT,
    BHV_SILVER_COIN,
    BHV_BOOST,
    BHV_WARDEN_SMOKE,
    BHV_UNK_5B,
    BHV_UNK_5C,
    BHV_ZIPPER_AIR,
    BHV_UNK_5E,
    BHV_DYNAMIC_LIGHT_OBJECT_2,
    BHV_SNOWBALL,
    BHV_SNOWBALL_2,
    BHV_TELEPORT,
    BHV_ROCKET_SIGNPOST,
    BHV_ROCKET_SIGNPOST_2,
    BHV_SNOWBALL_3,
    BHV_SNOWBALL_4,
    BHV_HIT_TESTER_3,
    BHV_HIT_TESTER_4,
    BHV_RANGE_TRIGGER,
    BHV_UNK_6A,
    BHV_BOSS_HAZARD_TRIGGER,
    BHV_FIREBALL_OCTOWEAPON,
    BHV_FROG,
    BHV_SILVER_COIN_2,
    BHV_TT_DOOR,
    BHV_MIDI_FADE_POINT,
    BHV_DOOR_OPENER,
    BHV_UNK_72,
    BHV_PIG_ROCKETEER,
    BHV_FIREBALL_OCTOWEAPON_2,
    BHV_LEVEL_NAME,
    BHV_MIDI_CHANNEL_SET,
    BHV_WIZPIG_GHOSTS,
    BHV_UNK_78,
    BHV_UNK_79,
    BHV_UNK_7A,
    BHV_UNK_7B,
    BHV_UNK_7C,
    BHV_UNK_7D,
    BHV_UNK_7E,
    BHV_UNK_7F
};

enum ObjectInteractionFlags {
    INTERACT_FLAGS_NONE,
    INTERACT_FLAGS_SOLID = (1 << 0),
    INTERACT_FLAGS_TANGIBLE = (1 << 1),
    INTERACT_FLAGS_UNK_0004 = (1 << 2),
    INTERACT_FLAGS_PUSHING = (1 << 3),
    INTERACT_FLAGS_UNK_0010 = (1 << 4),
    INTERACT_FLAGS_UNK_0020 = (1 << 5),
    INTERACT_FLAGS_COLLIDED = (1 << 6),
    INTERACT_FLAGS_UNK_0080 = (1 << 7),
    INTERACT_FLAGS_UNK_0100 = (1 << 8),
    INTERACT_FLAGS_UNK_0200 = (1 << 9),
    INTERACT_FLAGS_UNK_0400 = (1 << 10),
    INTERACT_FLAGS_UNK_0800 = (1 << 11),
    INTERACT_FLAGS_UNK_1000 = (1 << 12),
    INTERACT_FLAGS_UNK_2000 = (1 << 13),
    INTERACT_FLAGS_UNK_4000 = (1 << 14),
    INTERACT_FLAGS_UNK_8000 = (1 << 15),
};

enum ObjectSpawnFlags {
    OBJECT_SPAWN_NONE,
    OBJECT_SPAWN_UNK01          = (1 << 0),
    OBJECT_SPAWN_SHADOW         = (1 << 1),
    OBJECT_SPAWN_UNK04          = (1 << 2),
    OBJECT_SPAWN_UNK08          = (1 << 3),
    OBJECT_SPAWN_INTERACTIVE    = (1 << 4),
    OBJECT_SPAWN_UNK20          = (1 << 5)
};

enum ContPakErrors {
    CONTPAK_ERROR_MISSING = -1,
    CONTPAK_ERROR_NONE,
    CONTPAK_ERROR_UNKNOWN,
    CONTPAK_ERROR_FULL,
    CONTPAK_ERROR_DAMAGED
};

enum TajChallengeReasons {
    CHALLENGE_END_FINISH,
    CHALLENGE_END_QUIT,
    CHALLENGE_END_OOB // out of bounds
};

typedef struct RacerShieldGfx {
    s16 x_position;
    s16 y_position;
    s16 z_position;
    s16 y_offset;
    f32 scale;
    f32 turnSpeed;
} RacerShieldGfx;

typedef struct BossRaceVehicles {
    s8 playerVehicle;
    s8 bossVehicle;
} BossRaceVehicles;

typedef struct AssetObjectHeaders {
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
} AssetObjectHeaders;

/* Size: 0x3C bytes */
typedef struct CheckpointNode {
/* 0x00 */ f32 rotationXFrac;
/* 0x04 */ f32 rotationYFrac;
/* 0x08 */ f32 rotationZFrac;
/* 0x0C */ f32 unkC;
/* 0x10 */ f32 x;
/* 0x14 */ f32 y;
/* 0x18 */ f32 z;
/* 0x1C */ f32 scale;
/* 0x20 */ f32 distance;
/* 0x24 */ f32 unk24; // Appears to be exactly the same as distance?
/* 0x28 */ Object *obj;
/* 0x2C */ s16 unk2C;
/* 0x2E */ s8 unk2E[4];
/* 0x32 */ s8 unk32[4];
/* 0x36 */ s8 unk36[4]; // Appear to be flags of some sort?
/* 0x3A */ s8 altRouteID; // -1 if there's none to be found.
/* 0x3B */ s8 unk3B;
} CheckpointNode;

/* Size: 0x40 bytes */
typedef struct unk800179D0 {
    s32 unk0;
    u32 *unk04;
    u32 *unk08;
    f32 unk0C[12];
    u32 unk3C;
} unk800179D0;

typedef struct struct_8000FC6C {
    f32 unk0;
    TextureHeader *unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} struct_8000FC6C;

typedef struct struct_8000FC6C_2 {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    s32 unkC;
    u8 unk10[0x26];
    s16 unk36;
    s16 unk38;
} struct_8000FC6C_2;

typedef struct TTGhostTable {
    u8 mapId;
    u8 defaultVehicleId;
    s32 ghostOffset;
} TTGhostTable;

typedef struct ObjectTransformExt {
    ObjectTransform trans;
    s16 animFrame;
    s16 unk1A;
} ObjectTransformExt;

typedef struct unk80022CFC_2 {
    u8 pad[0xA];
    s8 unkA;
} unk80022CFC_2;

typedef struct unk80022CFC_1 {
    u8 pad[0xC];
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 pad18[0x16];
    s16 unk2E;
    u8 pad30[0x9];
    s8 unk39;
    u8 pad3A[0x2];
    unk80022CFC_2* unk3C;
    s32 pad40[2];
    s16 unk48;
    u16 pad4A[0x16];
    s32 unk78;
} unk80022CFC_1;

typedef struct unk8001A7D8_arg0 {
    u8 pad0[4];
    s32 *unk4;
    u8 pad8[0x41];
    u8 unk49;
} unk8001A7D8_arg0;

typedef struct unk800149C0 {
    u8 pad0[4];
    u8 unk4;
    u8 pad5;
    s16 unk6;
} unk800149C0;

// Size: 0x80 bytes.
typedef struct Asset20 {
    f32 unk0;
    u8 pad4[0x68];
    s16 unk6C;
    s16 unk6E;
    u8 unk70;
    u8 unk71;
    u8 unk72;
    s8 unk73;
    f32 unk74;
    Sprite *unk78;
    TextureHeader *unk7C;
} Asset20;

#define CIC_ID 6103
extern s32 osCicId; // Used for an Anti-Piracy check in render_3d_model

Object *func_8000BF44(s32 arg0);
void allocate_object_pools(void);
void clear_object_pointers(void);
void free_all_objects(void);
s32 normalise_time(s32 timer);
void func_8000CBC0(void);
s32 func_8000CC20(Object *obj);
s32 get_contpak_error(void);
void instShowBearBar(void);
s8 func_8000E138(void);
s8 func_8000E148(void);
s8 func_8000E158(void);
s8 func_8000E184(void);
void func_8000E194(void);
void fontUseFont(void);
s8 find_non_car_racers(void);
s8 check_if_silver_coin_race(void);
void despawn_player_racer(Object *obj, s32 vehicleID);
void set_time_trial_enabled(s32 status);
u8 is_time_trial_enabled(void);
u8 is_in_time_trial(void);
Object *get_object(s32 index);
Object **objGetObjList(s32 *arg0, s32 *cnt);
s32 get_object_count(void);
s32 get_particle_count(void);
void func_8000E9D0(Object *arg0);
void free_object(Object *);
s32 obj_table_ids(void);
s32 obj_id_valid(s32 arg0);
void path_enable(void);
s32 get_race_countdown(void);
s32 get_race_start_timer(void);
void ignore_bounds_check(void);
void func_80012C30(void);
void func_80012C3C(Gfx **dlist);
void func_80012C98(Gfx **dlist);
void func_80012CE8(Gfx **dlist);
void render_object(Gfx **dList, MatrixS **mtx, Vertex **verts, Object *obj);
void object_undo_player_tumble(Object *obj);
void render_object_parts(Object *obj);
void unset_temp_model_transforms(Object *obj);
void func_800142B8(void);
u32 func_800179D0(void);
void set_taj_challenge_type(s32 vehicleID);
s16 get_taj_challenge_type(void);
Object *find_taj_object(void);
void race_finish_adventure(s32 unusedArg);
s16 race_finish_timer(void);
u32 get_balloon_cutscene_timer(void);
s32 timetrial_valid_player_ghost(void);
Object *timetrial_player_ghost(void);
s32 timetrial_staff_ghost_check(Object* obj);
Object *timetrial_ghost_staff(void);
s32 timetrial_staff_unbeaten(void);
SIDeviceStatus timetrial_save_player_ghost(s32 controllerIndex);
u8 has_ghost_to_save(void);
void set_ghost_none(void);
f32 func_8001B834(Object_Racer *racer1, Object_Racer *racer2);
CheckpointNode *get_checkpoint_node(s32 checkpointID);
CheckpointNode *find_next_checkpoint_node(s32 splinePos, s32 arg1);
s32 get_checkpoint_count(void);
Object **get_racer_objects(s32 *numRacers);
Object **get_racer_objects_by_port(s32 *numRacers);
Object **get_racer_objects_by_position(s32 *numRacers);
Object *get_racer_object(s32 index);
void debug_render_checkpoint_node(s32 checkpointID, s32 pathID, Gfx** dList, MatrixS **mtx, Vertex **vtx);
Object *spectate_object(s32 cameraIndex);
void ainode_enable(void);
void ainode_tail_set(s32 nodeID);
Object *ainode_tail(s32 *nodeID);
Object *ainode_get(s32 nodeID);
void set_world_shading(f32 brightness, f32 ambient, s16 angleX, s16 angleY, s16 angleZ);
void set_shading_properties(ShadeProperties *arg0, f32 brightness, f32 ambient, s16 angleX, s16 angleY, s16 angleZ);
void calc_dyn_light_and_env_map_for_object(ObjectModel *model, Object *object, s32 arg2, f32 intensity);
s32 *get_misc_asset(s32 index);
s32 func_8001E2EC(s32 arg0);
void func_8001E344(s32 arg0);
void obj_bridge_pos(s32 timing, f32 *x, f32 *y, f32 *z);
s16 cutscene_id(void);
void cutscene_id_set(s32 cutsceneID);
void func_8001E45C(s32 cutsceneID);
s32 get_object_list_index(void);
s8 func_8001F3B8(void);
void func_8001F3C8(s32 arg0);
void func_8001F450(void);
s32 func_800210CC(s8 arg0);
s8 func_800214C4(void);
f32 lerp(f32 *arg0, u32 arg1, f32 arg2);
void func_800228DC(s32 arg0, s32 arg1, s32 arg2);
void init_racer_for_challenge(s32 vehicleID);
s8 is_taj_challenge(void);
s32 func_80023568(void);
s8 obj_door_override(void);
void obj_door_open(s32 setting);
void run_object_init_func(Object *obj, void *entry, s32 param);
void run_object_loop_func(Object *obj, s32 updateRate);
s16 *func_80024594(s32 *currentCount, s32 *maxCount);
void func_800245B4(s16 arg0);
void object_do_player_tumble(Object *this);
f32 catmull_rom_interpolation(f32 *data, s32 index, f32 x);
f32 cubic_spline_interpolation(f32 *data, s32 index, f32 x, f32 *derivative);
s16 obj_elevation(f32 yPos);
void func_80021400(s32 arg0);
s32 timetrial_init_player_ghost(s32 playerID);
s32 move_object(Object *obj, f32 xPos, f32 yPos, f32 zPos);
Object *get_racer_object_by_port(s32 index);
void render_racer_shield(Gfx **dList, MatrixS **mtx, Vertex **vtxList, Object *obj);
void render_racer_magnet(Gfx **dList, MatrixS **mtx, Vertex **vtxList, Object *obj);
void update_envmap_position(f32 x, f32 y, f32 z);
s32 init_object_water_effect(Object *obj, WaterEffect *waterEffect);
s32 timetrial_load_staff_ghost(s32 mapId);
void render_3d_billboard(Object *obj);
void render_misc_model(Object *obj, Vertex *verts, u32 numVertices, Triangle *triangles, u32 numTriangles,
                       TextureHeader *tex, u32 flags, u32 texOffset, f32 scale);
void func_8000B290(void);
void func_80016BC4(Object *obj);
s32 ainode_register(Object *obj);
void obj_taj_create_balloon(s32 blockID, f32 x, f32 y, f32 z);
Object *func_8001B7A8(Object *racer, s32 position, f32 *distance);
s32 func_8000FD34(Object *obj, Object_5C *matrices);
void func_8000E4E8(s32 index);
void objFreeAssets(Object *obj, s32 count, s32 objType);
void func_8001709C(Object *obj);
s32 play_footstep_sounds(Object *obj, s32 arg1, s32 frame, s32 oddSoundId, s32 evenSoundId);
void render_3d_misc(Object *obj);
Object *spectate_nearest(Object *obj, s32 *cameraId);
s32 init_object_shadow(Object *obj, ShadowData *shadow);
s32 render_mesh(ObjectModel *objModel, Object *obj, s32 startIndex, s32 flags, s32 someBool);
void render_bubble_trap(ObjectTransform *trans, Object_68 *gfxData, Object *obj, s32 flags);
void gParticlePtrList_flush(void);
s32 init_object_shading(Object *obj, ShadeProperties *shadeData);
ObjectHeader *load_object_header(s32 index);
s32 func_8000F99C(Object *);
void try_free_object_header(s32 index);
s32 get_object_property_size(Object *obj, Object_64 *obj64);
void light_setup_light_sources(Object *obj);
s32 init_object_interaction_data(Object *obj, ObjectInteraction *interactObj);
s32 obj_init_emitter(Object *obj, ParticleEmitter *emitter);
s32 obj_init_property_flags(s32 behaviorId);
void tt_ghost_beaten(s32 arg0, s16 *playerId);
void obj_init_animcamera(Object *, Object *);
Object *obj_butterfly_node(f32 x, f32 y, f32 z, f32 maxDistCheck, s32 dontCheckYAxis);
void func_8002125C(Object *charSelectObj, LevelObjectEntry_CharacterSelect *entry, Object_CharacterSelect *charSelect, UNUSED s32 index);
void func_80021104(Object *obj, Object_Animation *animObj, LevelObjectEntry_Animation *entry);
s32 func_8001955C(Object *obj, s32 checkpoint, u8 arg2, s32 arg3, s32 arg4, f32 checkpointDist, f32 *outX, f32 *outY, f32 *outZ);
void func_80016500(Object *obj, Object_Racer *racer);
void func_8000C8F8(s32, s32);
u8 timetrial_init_staff_ghost(s32 trackId);
s8 set_course_finish_flags(Settings *settings);
void process_object_interactions(void);
void render_3d_model(Object *obj);
void mode_end_taj_race(s32 reason);
void ainode_update(void);
void func_8001E6EC(s8);
Object *func_8000FD54(s32 objectHeaderIndex);
void sort_objects_by_dist(s32 startIndex, s32 lastIndex);
void func_80016748(Object *obj0, Object *obj1);
void race_finish_time_trial(void);
s32 obj_dist_racer(f32 x, f32 y, f32 z, f32 radius, s32 is2dCheck, Object **sortObj);
void mode_init_taj_race(void);
void func_8000BADC(s32 updateRate);
f32 func_8002277C(f32 *data, s32 index, f32 x);
void race_transition_adventure(s32 updateRate);
void func_8001E4C4(void);
void func_8000B020(s32 numberOfVertices, s32 numberOfTriangles);

//Non Matching
void calc_dynamic_lighting_for_object_1(Object *, ObjectModel *, s16, Object *, f32, f32);
void calc_dynamic_lighting_for_object_2(Object *, ObjectModel *, s16, f32);
void decrypt_magic_codes(s32 *data, s32 length);
s32 func_80014814(s32 *);
Object *spawn_object(LevelObjectEntryCommon *entry, s32);
s32 func_8001F460(Object*, s32, Object*);
void func_8000B750(Object *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_80018CE0(Object* obj, f32 xPos, f32 yPos, f32 zPos, s32 updateRate);
s32 func_800185E4(s8, Object* obj, f32 xPos, f32 yPos, f32 zPos, f32* checkpointDistance, u8*); 
void func_80011134(Object *, s32);
Object *find_furthest_telepoint(f32 x, f32 z);
void func_8006017C(ObjectModel *);
void func_80012F94(Object *);
void func_800101AC(Object *, s32);
void func_800135B8(Object *);
void func_8000CC7C(Vehicle, u32, s32);
void func_80017E98(void);
void spectate_update(void);
void func_8001E93C(void);
void func_80019808(s32 updateRate);
void func_80014090(Object*, s32, ObjectHeader*);
void func_80008438(Object**, s32, s32);
void func_8001E89C(void);
CheckpointNode *func_800230D0(Object*, Object_Racer*);
void func_80010994(s32 updateRate);
void func_800159C8(Object *, Object *);
void func_80011264(ObjectModel *, Object *);
void func_800245F0(ObjectModel *, Object *, f32); //asm func in unknown_0251F0
s32 object_animate(Object *obj); //asm func in unknown_062930
s32 func_80014B50(s32 arg0, s32 arg1, f32 arg2, u32 arg3);
s16 func_8001CD28(s32 arg0, s32 arg1, s32 arg2, s32 arg3); // NON MATCHING

#endif
