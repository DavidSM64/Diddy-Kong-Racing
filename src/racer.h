#ifndef _RACER_H_
#define _RACER_H_

#include "types.h"
#include "structs.h"
#include "level_object_entries.h"
#include "save_data.h"

#define SEGMENT_NONE -1 // If the level in question does not use segmentation.
#define GHOST_STAFF 2

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
    BOOST_SOUND_UNK2,
    BOOST_SOUND_UNK3,
    BOOST_SOUND_UNK4
} BoostSound;

typedef enum ObjectElevation {
    ELEVATION_LOW,
    ELEVATION_NORMAL,
    ELEVATION_HIGH,
    ELEVATION_HIGHEST
} ObjectElevation;

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

typedef enum MagnetType {
    MAGNET_LEVEL1,
    MAGNET_LEVEL2,
    MAGNET_LEVEL3
} MagnetType;

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
    WEAPON_BUBBLE_TRAP,
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

typedef enum RacerAIBehaviours {
    AI_EMPOWERED_BOOST,
    AI_GETS_BALLOON,
    AI_UNK_2,
    AI_BLUE_BALLOON
} RacerAIBehaviours;

typedef enum TajInteraction {
    TAJ_WANDER,
    TAJ_DIALOGUE,
    TAJ_TELEPORT,
} TajInteraction;

#define AI_MIN 0
#define AI_MAX 1
#define AI_MIN_STEP 2
#define AI_MAX_STEP 3

typedef struct ObjectCamera {
  /* 0x0014 */ ObjectTransform trans;
  /* 0x0018 */ f32 unk18;
  /* 0x001C */ f32 unk1C;
  /* 0x0020 */ f32 unk20;
  /* 0x0024 */ f32 offsetX;
  /* 0x0028 */ f32 offsetY;
  /* 0x002C */ f32 offsetZ;
  /* 0x0030 */ f32 unk30;
  /* 0x0034 */ s16 segmentIndex;
  /* 0x0036 */ s16 mode;
  /* 0x0038 */ s16 pitchOffset;
  /* 0x003A */ s8 unk3A;
  /* 0x003B */ u8 zoom;
  /* 0x003C */ u8 unk3C;
  /* 0x003D */ u8 unk3D;
  /* 0x003E */ u8 unk3E;
  /* 0x003F */ u8 unk3F;
} ObjectCamera;

typedef struct AIBehaviourTable {
    f32 unk0;
    f32 unk4;
    s8 percentages[4][4];
} AIBehaviourTable;

typedef struct Unknown80046524 {
    s16 unk0;
    u8 pad2[0x38];
    s8 unk3A;
} Unknown80046524;

s32 roll_percent_chance(s32 chance);
void apply_plane_tilt_anim(s32 updateRate, Object *obj, Object_Racer *racer);
void racer_attack_handler_plane(Object *obj, Object_Racer *racer);
void update_carpet(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer);
void set_racer_tail_lights(Object_Racer *racer);
s32 should_taj_teleport(void);
void set_taj_status(TajInteraction status);
void slowly_reset_head_angle(Object_Racer *racer);
void func_80052988(Object *obj, Object_Racer *racer, s32 action, s32 arg3, s32 duration, s32 arg5, s32 flags, s32 arg7);
void handle_car_steering(Object_Racer *racer);
void func_800535C4(Object *obj, Object_Racer *racer);
void handle_car_velocity_control(Object_Racer *racer);
void play_char_horn_sound(Object *obj, Object_Racer *racer);
void racer_play_sound(Object *obj, s32 soundID);
void racer_play_sound_after_delay(Object *obj, s32 soundID, s32 delay);
void func_800575EC(Object *obj, Object_Racer *racer);
void handle_base_steering(Object_Racer *racer, s32 updateRate, f32 updateRateF);
void second_racer_camera_update(Object *obj, Object_Racer *racer, s32 mode, f32 updateRateF);
void get_timestamp_from_frames(s32 frameCount, s32 *minutes, s32 *seconds, s32 *hundredths);
void allocate_ghost_data(void);
void timetrial_reset_player_ghost(void);
void timetrial_swap_player_ghost(s32 mapID);
s32 timetrial_map_id(void);
s32 timetrial_load_player_ghost(s32 controllerID, s32 mapId, s16 arg2, s16 *characterID, s16 *time);
s32 load_tt_ghost(s32 ghostOffset, s32 size, s16 *outTime);
void timetrial_free_staff_ghost(void);
SIDeviceStatus timetrial_write_player_ghost(s32 controllerIndex, s32 mapId, s16 arg2, s16 arg3, s16 arg4);
s16 timetrial_ghost_full(void);
void disable_racer_input(void);
void racer_set_dialogue_camera(void);
void drm_checksum_balloon(void);
void drm_vehicle_traction(void);
s32 turn_head_towards_object(Object *obj, Object_Racer *racer, Object *targetObj, f32 distance);
void onscreen_ai_racer_physics(Object *obj, Object_Racer *racer, s32 arg2);
void func_8005C270(Object_Racer *racer);
f32 handle_racer_top_speed(Object *obj, Object_Racer *racer);
void play_random_character_voice(Object *obj, s32 soundID, s32 range, s32 flags);
void apply_vehicle_rotation_offset(Object_Racer *obj, s32 max, s16 yRotation, s16 xRotation, s16 zRotation);
void set_position_goal_from_path(Object *obj, Object_Racer *racer, f32 *x, f32 *y, f32 *z);
void update_onscreen_AI_racer(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF);
void update_camera_hovercraft(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_plane(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_loop(f32 updateRateF, Object *obj, Object_Racer *racer);
void update_camera_car(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_finish_challenge(f32 arg0, Object *obj, Object_Racer *racer);
void update_camera_finish_race(f32 arg0, Object *obj, Object_Racer *racer);
void update_camera_fixed(f32 updateRate, Object *obj, Object_Racer *racer);
void handle_racer_head_turning(Object *obj, Object_Racer *racer, s32 updateRate);
void racer_approach_object(Object *obj, Object_Racer *racer, f32 divisor);
void obj_init_racer(Object *obj, LevelObjectEntry_Racer *racer);
void racer_AI_pathing_inputs(Object *obj, Object_Racer *racer, s32 updateRate);
void increment_ai_behaviour_chances(Object *obj, Object_Racer *racer, s32 updateRate);
void onscreen_ai_racer_physics(Object *obj, Object_Racer *racer, s32 updateRate);
void update_player_camera(Object *obj, Object_Racer *racer, f32 updateRateF);
void racer_spinout_car(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF);
void racer_attack_handler_car(Object* obj, Object_Racer* racer, s32 updateRate);
void racer_attack_handler_hovercraft(Object* obj, Object_Racer* racer);
void racer_enter_door(Object_Racer *racer, s32 updateRate);
void func_8005250C(Object* obj, Object_Racer* racer, s32 updateRate);
void update_car_velocity_ground(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF);
f32 rotate_racer_in_water(Object *obj, Object_Racer *racer, Vec3f *pos, s8 arg3, s32 updateRate, s32 arg5, f32 arg6);
void update_AI_racer(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF);
void func_80042D20(Object *obj, Object_Racer *racer, s32 updateRate);
void handle_racer_items(Object *obj, Object_Racer *racer, s32 updateRate);
void drop_bananas(Object *obj, Object_Racer *racer, s32 number);
void update_player_racer(Object *obj, s32 updateRate);
void func_80045128(Object **racerObjs);
void timetrial_ghost_write(Object *obj, s32 updateRate);
void func_80046524(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer);

//Non Matching
s32 set_ghost_position_and_rotation(Object *obj);
void func_80054FD0(Object *obj, Object_Racer *racer, s32);
void func_80053750(Object *obj, Object_Racer *racer, f32);
void update_car_velocity_offground(Object *obj, Object_Racer *racer, s32, f32);
s32 func_80017248(void*, s32, s32*, Vec3f*, f32*, f32*, s8* surface);
void func_80059208(Object* obj, Object_Racer* racer, s32 updateRate);       /* extern */
void func_8004F7F4(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer);  /* extern */
void func_80049794(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer);  /* extern */
void func_8004CC20(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer);  /* extern */
void func_8004447C(Object *obj, Object_Racer *racer, s32 updateRate);
void func_800452A0(Object *obj, Object_Racer *racer, s32 updateRate);
void func_80045C48(Object *obj, Object_Racer *racer, s32 updateRate);
void racer_activate_magnet(Object *obj, Object_Racer *racer, s32 updateRate);
Object* func_8005698C(Object* racer, Object_Racer* obj, f32* dist);
void func_8005B818(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF);

#endif
