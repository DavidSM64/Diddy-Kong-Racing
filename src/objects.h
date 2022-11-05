#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "types.h"
#include "structs.h"
#include "f3ddkr.h"
#include "object_functions.h"
#include "libc/math.h"

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
    BHV_UNK_2F,
    BHV_ANIMATION,
    BHV_ANIMATED_OBJECT,
    BHV_CAMERA_ANIMATION,
    BHV_INFO_POINT,
    BHV_CAR_ANIMATION,
    BHV_CHARACTER_SELECT,
    BHV_TRIGGER,
    BHV_VEHICLE_ANIMATION,
    BHV_ZIPPER_WATER,
    BHV_UNK_3A,
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
    BHV_UNK_57,
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
    BHV_UNK_6B,
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

struct RacerShieldGfx {
    s16 x_position;
    s16 y_position;
    s16 z_position;
    s16 y_offset;
    f32 scale;
    f32 turnSpeed;
};

/* Size: 0x8 bytes */
typedef struct unknown800DC6F0 {
    union {
        s8 unk00;
        s32 dummy_force_alignment; // Not sure of a better way to do this.
    } unk00_a;
    u16 unk04;
    u16 unk06;
} unknown800DC6F0;

/* Size: 0x3C bytes */
typedef struct unknown8011AECC {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    Object* unk28;
    u8 pad2C[0x2];
    s8 unk2E[4];
    s8 unk32[4];
    s8 unk36[4];
    s8 unk3A;
    s8 unk3B;
} unknown8011AECC;

/* Size: 0x40 bytes */
typedef struct unk800179D0 {
    s32 unk0;
    u32 *unk04;
    u32 *unk08;
    f32 unk0C[12];
    u32 unk3C;
} unk800179D0;

/* Unknown Size */
typedef struct unk800179D0_2 {
    s32 unk04;
} unk800179D0_2;

typedef struct unk8001D6E4_arg1_40 {
           u8 pad0[0x71];
/* 0x71 */ u8 unk71;
} unk8001D6E4_arg1_40;

typedef struct unk8001D6E4_arg1 {
/* 0x00 */ s16 unk0;
/* 0x02 */ s16 unk2;
/* 0x04 */ s16 unk4;
           u8  pad6[0x3A];
/* 0x40 */ unk8001D6E4_arg1_40 *unk40;
} unk8001D6E4_arg1;

/* Unknown Size */
typedef struct unk8000FD20_2 {
    u8 unk00[0x13];
    u8 unk13;
} unk8000FD20_2;

/* Unknown Size */
typedef struct unk8000FD20 {
    u8 unk00[0x4C];
    unk8000FD20_2 *unk4C;
} unk8000FD20;

/* Unknown Size. This might just be unk8000FD20. */
typedef struct unk8000FD34 {
    u8 unk00[0x5C];
    s32 unk5C;
} unk8000FD34;

extern unknown800DC6F0 D_800DC6F0;
extern unknown800DC6F0 D_800DC6F8;

extern s32 D_800DC700;
extern s32 D_800DC704;
extern s16 D_800DC708;
extern s32 D_800DC70C;
extern s16 D_800DC710;
extern s32 D_800DC714;
extern s32 D_800DC718;
extern s8 D_800DC71C;
extern s32 D_800DC720;
extern s16 D_800DC724;
extern s16 D_800DC728;
extern s16 D_800DC72C;
extern u8 gHasGhostToSave;
extern s32 D_800DC734;
extern u8 D_800DC738;
extern s8 D_800DC73C;
extern s8 D_800DC740;
extern s8 D_800DC744;
extern s8 D_800DC748;
extern s32 D_800DC74C[2];
extern s32 D_800DC754[2];
extern s32 D_800DC760;
extern s32 D_800DC768;

extern f32 D_800DC76C[15];

extern u16 D_800DC7A8[8];

extern s16 D_800DC7B8[52];

extern s16 D_800DC820[16];

extern s8 D_800DC840[8];

extern s8 D_800DC848;
extern s32 D_800DC858;
extern s32 D_800DC85C;

extern u8 D_800DC860;
extern u16 D_800DC864;

f32 sine_s(s16); //?

Object *func_8000BF44(s32 arg0);
void func_8000BF8C(void);
void func_8000C460(void);
void func_8000C604(void);
s32 normalise_time(s32 timer);
void func_8000CBC0(void);
s32 func_8000CC20(Object *arg0);
u32 func_8000E0B0(void);
void func_8000E128(void);
s8 func_8000E138();
s8 func_8000E148();
s8 func_8000E158(void);
s8 func_8000E184();
void func_8000E194(void);
void func_8000E1B8(void);
s8 find_non_car_racers(void);
s8 check_if_silver_coin_race();
void func_8000E1EC(Object *object, s32 arg1);
void set_time_trial_enabled(s32 arg0);
u8 is_time_trial_enabled();
u8 func_8000E4D8(void);
Object *get_object(s32 index);
Object **func_8000E988(s32 *arg0, s32 *cnt);
s32 getObjectCount(void);
s32 func_8000E9C0(void);
void func_8000E9D0(Object *arg0);
void gParticlePtrList_addObject(Object *object);
s32 func_80010018(void);
s32 func_80010028(s32 arg0);
void func_80011390(void);
s32 func_8001139C();
s32 get_race_start_timer();
s32 func_800113BC();
s32 func_80011560(void);
void func_80012C30(void);
void func_80012C3C(Gfx** dlist);
void func_80012C98(Gfx **dlist);
void func_80012CE8(Gfx **dlist);
void func_80012D5C(Gfx **dlist, Matrix **mats, VertexList **verts, Object *object);
void func_80012F30(Object *arg0);
void render_object(Object *this);
void func_80013548(Object *arg0);
void func_800142B8(void);
u32 func_800179D0(void);
void func_80017E74(s32 arg0);
s16 func_80017E88(void);
Object *func_80018C6C(void);
void func_8001A8D4(s32 arg0);
s16 func_8001AE44();
s32 func_8001AE54();
s32 func_8001B288(void);
Object *func_8001B2E0(void);
s32 func_8001B3AC(s32 arg0);
Object *func_8001B640(void);
s32 func_8001B650(void);
s32 func_8001B738(s32 controllerIndex);
u8 has_ghost_to_save();
void func_8001B790(void);
f32 func_8001B834(Object *arg0, s32);
unknown8011AECC *func_8001BA00(s32 arg0);
unknown8011AECC *func_8001BA1C(s32 arg0, s32 arg1);
s32 func_8001BA64();
Object **get_racer_objects(s32 *cnt);
s32 *func_8001BA90(s32 *arg0);
Object **func_8001BAAC(s32 *numberOfObjects);
Object *get_object_struct(s32 indx);
void func_8001BC40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
u32 func_8001BD94(s32 arg0);
void func_8001D1AC(void);
void func_8001D1BC(s32 arg0);
u32 func_8001D1E4(s32 *arg0);
u32 func_8001D214(s32 arg0);
void func_8001D23C(s32 arg0, s32 arg1, s32 arg2);
void func_8001D258(f32 arg0, f32 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_8001D4B4(s32*, f32, f32, s16, s16, s16);
void calc_dyn_light_and_env_map_for_object(ObjectModel *model, Object *object, s32 arg2, f32 arg3);
s32 *get_misc_asset(s32 index);
s32 func_8001E2EC(s32 arg0);
void func_8001E344(s32 arg0);
void func_8001E36C(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3);
s16 func_8001E440();
void func_8001E450(s32 arg0);
void func_8001E45C(s32 arg0);
s32 func_8001E4B4(void);
s8 func_8001F3B8(void);
void func_8001F3C8(s32 arg0);
void func_8001F450(void);
s32 func_800210CC(s8 arg0);
s8 func_800214C4(void);
f32 lerp(f32 *arg0, u32 arg1, f32 arg2);
void func_800228DC(s32 arg0, s32 arg1, s32 arg2);
void func_800228EC(s32 arg0);
s8 func_8002341C(void);
s32 func_80023568(void);
s8 func_800235C0(void);
void func_800235D0(s32 arg0);
void run_object_init_func(Object *arg0, void *arg1, s32 arg2);
void run_object_loop_func(Object *obj, s32 arg1);
void func_8002458C(s32 arg0);
s16 *func_80024594(s32 *arg0, s32 *arg1);
void func_800245B4(s16 arg0);
void func_80012E28(Object *this);
f32 catmull_rom_interpolation(f32*, s32, f32);
f32 func_8002263C(f32 *, s32, f32, f32 *);
s32 func_80031F88(Object*, s32);
s16 func_8001C418(f32 yPos);
void func_80021400(s32 arg0);
s32 func_8001B668(s32 arg0);
s32 func_80011570(Object *obj, f32 xPos, f32 yPos, f32 zPos);
s32 func_8001BB18(s32 arg0);
void render_racer_shield(Gfx **dList, Matrix **mtx, VertexList **vtxList, Object *obj);
void render_racer_magnet(Gfx **dList, Matrix **mtx, VertexList **vtxList, Object *obj);
void set_and_normalize_D_8011AFE8(f32 arg0, f32 arg1, f32 arg2);

//Non Matching
void calc_dynamic_lighting_for_object_1(Object *, ObjectModel *, s16, Object *, f32, f32);
void calc_dynamic_lighting_for_object_2(Object *, ObjectModel *, s16, f32);
void gParticlePtrList_flush(void);
void decrypt_magic_codes(u8 *arg0, s32 length);
void func_80011960(Object*, s32, u32, Object_64*, u32, u32, u32, u32, f32);
void func_80011AD0(Object *this);
s32 func_80014814(s32 *);
void func_80015348(s32, s32);
Object *spawn_object(void *entry, s32);
s32 func_8001F460(Object*, s32, Object*);
s32 func_80016DE8(f32, f32, f32, f32, s32, unk80042178 *);
void func_8001BF20(void);
void func_8000B750(Object *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_80022E18(s32);                                 /* extern */
void func_80018CE0(Object* obj, f32 xPos, f32 yPos, f32 zPos, s32 updateRate);       /* extern */
s32 func_800185E4(s8, Object* obj, f32 xPos, f32 yPos, f32 zPos, f32* checkpointDistance, u8*); /* extern */
Object *func_8001B7A8(Object *arg0, s32 arg1, f32 *arg2);
void func_80011134(Object *, s32);
void func_800113CC(Object *, s32, s32, s32, s32);
s32 func_800143A8(ObjectModel*, Object*, s32, s32, s32);  /* extern */
void func_80068FA8(Gfx**, Matrix**, Object*, Object*, f32); /* extern */

#endif
