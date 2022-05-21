#ifndef _RACER_H_
#define _RACER_H_

#include "types.h"
#include "structs.h"
#include "level_object_entries.h"

typedef enum ActivePlayers {
    PLAYER_COMPUTER = -1,
    PLAYER_ONE,
    PLAYER_TWO,
    PLAYER_THREE,
    PLAYER_FOUR
} ActivePlayers;

typedef enum RaceStatus {
    STATUS_RACING,
    STATUS_FINISHED
} RaceStatus;

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

typedef enum BoostType {
    BOOST_SMALL,
    BOOST_MEDIUM,
    BOOST_LARGE,
    BOOST_UNK3,
    BOOST_SMALL_FAST,
    BOOST_MEDIUM_FAST,
    BOOST_LARGE_FAST,
} BoostType;

typedef struct ObjectCamera {
  /* 0x0014 */ ObjectTransform trans;
  /* 0x0018 */ f32 unk18;
  /* 0x001C */ f32 unk1C;
  /* 0x0020 */ f32 unk20;
  /* 0x0024 */ f32 x_velocity;
  /* 0x0028 */ f32 y_velocity;
  /* 0x002C */ f32 z_velocity;
  /* 0x0030 */ f32 unk30;
  /* 0x0034 */ s16 unk34;
  /* 0x0036 */ s16 mode;
  /* 0x0038 */ s16 unk38;
  /* 0x003A */ s8 unk3A;
  /* 0x003B */ u8 zoom;
  /* 0x003C */ u8 unk3C;
  /* 0x003D */ u8 unk3D;
  /* 0x003E */ u8 unk3E;
  /* 0x003F */ u8 unk3F;
} ObjectCamera;

typedef struct unk8004F77C {
    u8 unk0[0x20A];
    u8 flags;
} unk8004F77C;

/* Unknown Size */
typedef struct unk8005234C {
    u8 unk0[0x16C];
    s16 unk16C;
} unk8005234C;

// Also fairly certain this is NOT Object_Racer.
typedef struct Object_64_Unknown5 {
    u8 pad0[0x88];
    u8 unk89;
    u8 pad90[0xE9];
    s8 unk172;
    s8 unk173;
    s8 unk174;
    u8 pad175[0x5E];
    s8 unk1D3;
} Object_64_Unknown5;

typedef struct TempStruct5 {
    s8 pad0[8];
    s8 unk8[4][4];
} TempStruct5;

typedef struct Object_64_80053478 {
    u8 unk0[0x2C];
    f32 unk2C; // Forward Velocity?
    u8 unk30[0x1B1];
    s8 unk1E1; // Steering Value?
    u8 unk1E2[4];
    s8 unk1E6;
} Object_64_80053478;

/* Unknown Size */
typedef struct unk800535C4 {
    s16 unk0;
    s16 unk2;
} unk800535C4;

/* Unknown Size */
typedef struct unk800535C4_2 {
    /* 0x00  */ u8 unk0[0x9C];
    /* 0x9C  */ f32 oz;
    /* 0xA0  */ f32 ox;
    /* 0xA4  */ f32 oy;
    /* 0xA8  */ u8 unkA8[0xF8];
    /* 0x1A0 */ s16 unk1A0;
    /* 0x1A2 */ s16 unk1A2;
    /* 0x1A4 */ s16 unk1A4;
} unk800535C4_2;

/* Unknown Size */
typedef struct unk80056930 {
    u8 unk0[0x3];
    s8 unk3;
} unk80056930;

/* Unknown Size */
typedef struct unk800579B0 {
    u8 unk0[0x1E1];
    s8 unk1E1;
} unk800579B0;

extern ObjectCamera *gCameraObject;
extern s32 gObjLoopGoldenBalloonLength;
extern s16 D_800DCB54;
extern s32 D_800DCB58;
extern s32 D_800DCB5C;

// Not sure if D_800DCB58 & D_800DCB5C are actually a part of this array.
extern f32 D_800DCB60[14];

extern s32 D_800DCB98;
extern f32 gSurfaceTractionTable[19];

extern f32 D_800DCBE8[19];

// Unused? Not sure if this is actually an array or just some random data.
extern s32 D_800DCC34[19];

extern s32 D_800DCC80[13];

extern s16 D_800DCCB4[12];

extern u16 D_800DCCCC[20];

// Used for some sort of bit mask
extern s32 D_800DCCF4[19];

// Used for some sort of bit mask
extern s32 D_800DCD40[20];

extern s8 D_800DCD90[15];

// Unused?
extern s8 D_800DCDA0[8];

extern s8 D_800DCDA8[8];

// Unused?
extern s16 D_800DCDB0[16];

extern s32 gObjLoopGoldenBalloonChecksum;

extern s16 D_800DCDD4[4];

extern ObjectTransform D_8011D510;

extern s32 gCurrentStickX;

s32 get_random_number_from_range(s32, s32); //?
void func_8006FC30(Matrix, ObjectTransform *); // asm func
void func_8006FE74(Matrix *, ObjectTransform *); // Non Matching ?

s32 func_80044450(s32 cap);
void func_8004C0A0(s32 arg0, Object *planeObj, Object_Racer *planeObj64);
void func_8004C140(Object *obj, Object_Racer *racer);
void func_8004D95C(s32 arg0, s32 arg1, Object *obj, Object_Racer *racer);
void func_8004F77C(unk8004F77C *arg0);
s32 func_80052188(void);
void func_800521B8(s32 arg0);
void func_8005234C(Object_Racer *racer);
void func_80052988(Object *obj, Object_Racer *arg1, s32 action, s32 arg3, s32 duration, s32 arg5, s32 arg6, s32 arg7);
void handle_car_steering(Object_Racer *racer);
void func_800535C4(unk800535C4 *arg0, unk800535C4_2 *arg1);
void handle_car_velocity_control(Object_Racer *racer);
void play_char_horn_sound(Object *obj, Object_Racer *racer);
void func_80057048(Object *obj, s32 arg1);
void func_800570A4(Object *obj, s32 arg1, s32 arg2);
void func_800575EC(Object *obj, Object_Racer *racer);
void func_800579B0(Object_Racer *racer, s32 arg1, f32 updateRate);
void func_800580B4(Object *obj, Object_Racer *racer, s32 mode, f32 arg3);
void get_timestamp_from_frames(s32 frameCount, s32 *minutes, s32 *seconds, s32 *hundredths);
void func_800598D0(void);
void func_80059944(void);
void func_80059984(s32 arg0);
s32 func_800599A8(void);
s32 func_800599B8(s32 arg0, s32 arg1, s16 arg2, s16 *arg3, s16 *arg4);
s32 load_tt_ghost(s32 ghostOffset, s32 size, s16 *outTime);
void free_tt_ghost_data(void);
s32 func_80059B7C(s32 controllerIndex, s32 arg1, s16 arg2, s16 arg3, s16 arg4);
s16 func_80059E20(void);
void func_8005A3B0(void);
void func_8005A3C0(void);
void func_8005A3D0(void);
void antipiracy_modify_surface_traction_table(void);
s32 func_80052388(Object *obj1, Object_Racer *racer, Object *obj2, f32 distance);
void func_80055A84(Object *obj, Object_Racer *racer, s32 arg2);
void func_8005C270(Object_Racer *racer);
f32 handle_racer_top_speed(Object *obj, Object_Racer *racer);
void func_800570B8(Object *obj, s32 arg1, s32 arg2, s32 arg3);
void apply_vehicle_rotation_offset(Object_Racer *obj, s32 max, s16 yRotation, s16 xRotation, s16 zRotation);
void func_80059080(Object *obj, Object_Racer *racer, f32 *velX, f32 *velY, f32 *velZ);
void func_80054110(Object *obj, Object_Racer *racer, s32 updateRate, f32 arg3);
void update_camera_hovercraft(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_plane(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_loop(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_car(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_finish_challenge(f32 arg0, Object *obj, Object_Racer *racer);
void update_camera_finish_race(f32 arg0, Object *obj, Object_Racer *racer);
void update_camera_fixed(f32 arg0, struct Object *obj, Object_Racer *racer);
void func_800521C4(Object *obj, Object_Racer *racer, s32 arg2);
void func_80050754(Object *obj, Object_Racer *racer, f32 divisor);
void obj_init_racer(Object *obj, LevelObjectEntry_CharacterFlag *racer);
void func_80044170(Object *obj, Object_Racer *racer, s32 updateRate);
void func_80043ECC(s32 arg0, Object_64_Unknown5 *arg1, s32 updateRate);
void func_80055A84(Object *obj, Object_Racer *racer, s32 updateRate);
void func_80057A40(Object *obj, Object_Racer *racer, f32 updateRate);

//Non Matching
void set_ghost_position_and_rotation(Object *obj);
void func_800576E0(Object *obj, Object_Racer *racer, s32 arg2);
void func_80055EC0(Object *obj, Object_Racer *racer, s32);
void func_80054FD0(Object *obj, Object_Racer *racer, s32);
void func_8005492C(Object *obj, Object_Racer *racer, s32, f32);
void func_80053E9C(Object *obj, Object_Racer *racer, s32);
void func_80053750(Object *obj, Object_Racer *racer, f32);
void func_80052D7C(Object *obj, Object_Racer *racer, s32, f32);
void func_80052B64(Object *obj, Object_Racer *racer, s32, f32);
s32 func_80017248(void*, s32, s32*, void*, f32*, s32*, s8*);

#endif
