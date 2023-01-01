#ifndef _RACER_H_
#define _RACER_H_

#include "types.h"
#include "structs.h"
#include "level_object_entries.h"

#define SEGMENT_NONE -1 // If the level in question does not use segmentation.

struct TempStruct8 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s8 unk10;
};

typedef enum ActivePlayers {
    PLAYER_COMPUTER = -1,
    PLAYER_ONE,
    PLAYER_TWO,
    PLAYER_THREE,
    PLAYER_FOUR
} ActivePlayers;

typedef enum CameraZoom {
    ZOOM_MEDIUM,
    ZOOM_FAR,
    ZOOM_CLOSE,
    ZOOM_VERY_CLOSE
} CameraZoom;

typedef enum BoostSound {
    BOOST_NONE,
    BOOST_RACE_START,
    BOOST_UNK2
} BoostSound;

// boost types suffixed with _FAST are the ones you get from releasing the throttle.
typedef enum BoostType {
    BOOST_SMALL,
    BOOST_MEDIUM,
    BOOST_LARGE,
    BOOST_UNK3,
    EMPOWER_BOOST,
    BOOST_SMALL_FAST = 4,
    BOOST_MEDIUM_FAST,
    BOOST_LARGE_FAST
} BoostType;

typedef enum AISkill {
    AI_MASTER,
    AI_EXPERT,
    AI_HARD,
    AI_MEDIUM,
    AI_EASY
} AISkill;

typedef enum AttackType {
    ATTACK_NONE,
    ATTACK_EXPLOSION,
    ATTACK_SPIN,
    ATTACK_UNK3,
    ATTACK_SQUISHED,
    ATTACK_FLUNG,
    ATTACK_BUBBLE
} AttackType;

typedef enum ShieldType {
    SHIELD_NONE,
    SHIELD_LEVEL1,
    SHIELD_LEVEL2,
    SHIELD_LEVEL3
} ShieldType;

typedef enum WeaponType {
    WEAPON_NONE = -1,
    WEAPON_ROCKET_HOMING,
    WEAPON_ROCKET,
    WEAPON_TRIPMINE,
    WEAPON_OIL_SLICK,
    WEAPON_NITRO_LEVEL_1,
    WEAPON_MAGNET_LEVEL_1,
    WEAPON_MAGNET_LEVEL_3,
    WEAPON_MAGNET_LEVEL_2,
    WEAPON_NITRO_LEVEL_2,
    WEAPON_UNK_09,
    WEAOON_BUBBLE_TRAP,
    WEAPON_UNK_11,
    WEAPON_SHIELD_LEVEL_1,
    WEAPON_SHIELD_LEVEL_2,
    WEAPON_SHIELD_LEVEL_3,
    WEAPON_NITRO_LEVEL_3,

    NUM_WEAPON_TYPES
} WeaponType;

typedef enum LightFlags {
    RACER_LIGHT_UNK00 = 0,
    RACER_LIGHT_TIMER = 0xF,
    RACER_LIGHT_UNK10 = (1 << 4),
    RACER_LIGHT_UNK20 = (1 << 5),
    RACER_LIGHT_NIGHT = (1 << 6),
    RACER_LIGHT_BRAKE = (1 << 7)
} LightFlags;

typedef struct ObjectCamera {
  /* 0x0014 */ ObjectTransform trans;
  /* 0x0018 */ f32 unk18;
  /* 0x001C */ f32 unk1C;
  /* 0x0020 */ f32 unk20;
  /* 0x0024 */ f32 x_velocity;
  /* 0x0028 */ f32 y_velocity;
  /* 0x002C */ f32 z_velocity;
  /* 0x0030 */ f32 unk30;
  /* 0x0034 */ s16 segmentIndex;
  /* 0x0036 */ s16 mode;
  /* 0x0038 */ s16 unk38;
  /* 0x003A */ s8 unk3A;
  /* 0x003B */ u8 zoom;
  /* 0x003C */ u8 unk3C;
  /* 0x003D */ u8 unk3D;
  /* 0x003E */ u8 unk3E;
  /* 0x003F */ u8 unk3F;
} ObjectCamera;

typedef struct TempStruct5 {
    f32 unk0;
    f32 unk4;
    s8 unk8[4][4];
} TempStruct5;

typedef struct Asset20 {
    f32 unk0;
    u8 pad4[0x6C];
    u8 unk70;
    f32 unk74;
    u8 pad78[0x8];
} Asset20;

typedef struct Unknown80046524 {
    s16 unk0;
    u8 pad2[0x38];
    s8 unk3A;
} Unknown80046524;

s32 roll_percent_chance(s32 chance);
void apply_plane_tilt_anim(s32 updateRate, Object *obj, Object_Racer *racer);
void racer_attack_handler_plane(Object *obj, Object_Racer *racer);
void update_carpet(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer);
void set_racer_tail_lights(Object_Racer *arg0);
s32 func_80052188(void);
void func_800521B8(s32 arg0);
void slowly_reset_head_angle(Object_Racer *racer);
void func_80052988(Object *obj, Object_Racer *arg1, s32 action, s32 arg3, s32 duration, s32 arg5, s32 arg6, s32 arg7);
void handle_car_steering(Object_Racer *racer);
void func_800535C4(Object *obj, Object_Racer *racer);
void handle_car_velocity_control(Object_Racer *racer);
void play_char_horn_sound(Object *obj, Object_Racer *racer);
void racer_play_sound(Object *obj, s32 soundID);
void func_800570A4(Object *obj, s32 arg1, s32 arg2);
void func_800575EC(Object *obj, Object_Racer *racer);
void handle_base_steering(Object_Racer *racer, s32 updateRate, f32 updateRateF);
void func_800580B4(Object *obj, Object_Racer *racer, s32 mode, f32 arg3);
void get_timestamp_from_frames(s32 frameCount, s32 *minutes, s32 *seconds, s32 *hundredths);
void func_800598D0(void);
void func_80059944(void);
void func_80059984(s32 arg0);
s32 func_800599A8(void);
s32 func_800599B8(s32 arg0, s32 mapId, s16 arg2, s16 *arg3, s16 *arg4);
s32 load_tt_ghost(s32 ghostOffset, s32 size, s16 *outTime);
void free_tt_ghost_data(void);
s32 func_80059B7C(s32 controllerIndex, s32 mapId, s16 arg2, s16 arg3, s16 arg4);
s16 func_80059E20(void);
void func_8005A3B0(void);
void func_8005A3C0(void);
void func_8005A3D0(void);
void antipiracy_modify_surface_traction_table(void);
s32 turn_head_towards_object(Object *obj, Object_Racer *racer, Object *targetObj, f32 distance);
void func_80055A84(Object *obj, Object_Racer *racer, s32 arg2);
void func_8005C270(Object_Racer *racer);
f32 handle_racer_top_speed(Object *obj, Object_Racer *racer);
void play_random_character_voice(Object *obj, s32 soundID, s32 range, s32 arg3);
void apply_vehicle_rotation_offset(Object_Racer *obj, s32 max, s16 yRotation, s16 xRotation, s16 zRotation);
void func_80059080(Object *obj, Object_Racer *racer, f32 *velX, f32 *velY, f32 *velZ);
void update_onscreen_AI_racer(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF);
void update_camera_hovercraft(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_plane(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_loop(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_car(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_finish_challenge(f32 arg0, Object *obj, Object_Racer *racer);
void update_camera_finish_race(f32 arg0, Object *obj, Object_Racer *racer);
void update_camera_fixed(f32 arg0, Object *obj, Object_Racer *racer);
void handle_racer_head_turning(Object *obj, Object_Racer *racer, s32 updateRate);
void racer_approach_object(Object *obj, Object_Racer *racer, f32 divisor);
void obj_init_racer(Object *obj, LevelObjectEntry_CharacterFlag *racer);
void func_80044170(Object *obj, Object_Racer *racer, s32 updateRate);
void func_80043ECC(s32 arg0, Object_Racer *racer, s32 updateRate);
void func_80055A84(Object *obj, Object_Racer *racer, s32 updateRate);
void update_player_camera(Object *obj, Object_Racer *racer, f32 updateRate);
void racer_spinout_car(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF);
void racer_attack_handler(Object* obj, Object_Racer* racer, s32 updateRate);
void func_80048C7C(Object* obj, Object_Racer* racer);
void racer_enter_door(Object_Racer *racer, s32 updateRate);
void func_8005250C(Object* obj, Object_Racer* racer, s32 updateRate);
void update_car_velocity_ground(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF);
f32 rotate_racer_in_water(Object* obj1, Object_Racer* racer, f32 *pos, s8 arg3, s32 updateRate, s32 arg5, f32 arg6);
void update_AI_racer(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF);
void func_80042D20(Object *obj, Object_Racer *racer, s32 updateRate);
void handle_racer_items(Object *obj, Object_Racer *racer, s32 updateRate);
void drop_bananas(Object *obj, Object_Racer *racer, s32 number);
void update_player_racer(Object *obj, s32 updateRate);

//Non Matching
void set_ghost_position_and_rotation(Object *obj);
void func_80054FD0(Object *obj, Object_Racer *racer, s32);
void func_80053750(Object *obj, Object_Racer *racer, f32);
void update_car_velocity_offground(Object *obj, Object_Racer *racer, s32, f32);
s32 func_80017248(void*, s32, s32*, Vec3f*, f32*, f32*, s8* surface);
void func_80059BF0(Object* obj, s32 updateRate);
void func_80059208(Object* obj, Object_Racer* racer, s32 updateRate);       /* extern */
void func_8004F7F4(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer);  /* extern */
void func_80046524(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer);  /* extern */
void func_80049794(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer);  /* extern */
void func_8004CC20(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer);  /* extern */
void func_8004447C(Object *obj, Object_Racer *racer, s32 updateRate);
void func_800452A0(Object *obj, Object_Racer *racer, s32 updateRate);
void func_80045C48(Object *obj, Object_Racer *racer, s32 updateRate);
void racer_activate_magnet(Object *obj, Object_Racer *racer, s32 updateRate);
Object* func_8005698C(Object* racer, Object_Racer* obj, f32* dist);
void func_8005B818(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF);

#endif
