#ifndef _RACER_H_
#define _RACER_H_

#include "types.h"
#include "structs.h"

typedef struct ObjectCamera {
/* 0x0000 */ s16 y_rotation;
/* 0x0002 */ s16 x_rotation;
/* 0x0004 */ s16 z_rotation;
/* 0x0006 */ s16 unk6;
/* 0x0008 */ f32 scale;
/* 0x000C */ f32 x_position;
/* 0x0010 */ f32 y_position;
/* 0x0014 */ f32 z_position;
/* 0x0018 */ u8 pad18[0xC];
/* 0x0024 */ f32 unk24;
/* 0x0028 */ f32 unk28;
/* 0x002C */ f32 unk2C;
/* 0x0030 */ f32 unk30;
/* 0x0034 */ s16 unk34;
/* 0x0036 */ s16 unk36;
} ObjectCamera;

/* Unknown size */
typedef struct Object_64_8004C0A0 {
    u8 pad0[0x1D7];
    s8 unk1D7;
    u8 pad1D8[9];
    s8 unk1E1;
    u8 pad1E2[0x10];
    u8 unk1F2;
} Object_64_8004C0A0;

typedef struct Object_64_8004C140 {
    s16 unk0;
    u8 pad2[0x183];
    s8 unk185;
    u8 unk186;
    s8 unk187;
    u8 pad188[4];
    s16 unk18C;
    s16 unk18E;
    u8 pad190[0x39];
    u8 unk1C9;
    u8 pad1CA[0xC];
    s8 unk1D6;
    u8 pad1D7[4];
    s8 unk1DB;
    u8 pad1DC[0x28];
    s16 unk204;
} Object_64_8004C140;

typedef struct Object_64_8004D95C {
    u8 unk0[0x118];
    s32 unk118;
    u8 unk11C[0x38];
    Object *someObject;
    u8 unk158[0x7E];
    s8 unk1D6;
    s8 unk1D7;
} Object_64_8004D95C;

typedef struct unk8004F77C {
    u8 unk0[0x20A];
    u8 unk20A;
} unk8004F77C;

/* Unknown Size */
typedef struct unk8005234C {
    u8 unk0[0x16C];
    s16 unk16C;
} unk8005234C;

typedef struct Object_64_80053478 {
    u8 unk0[0x2C];
    f32 unk2C;
    u8 unk30[0x1B1];
    s8 unk1E1;
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
typedef struct Object_64_unk800570A4 {
    u8 unk0[0x108];
    s32 unk108;
    u8 unk10C[0x102];
    s16 unk20E;
    s8 unk210;
} Object_64_unk800570A4;

/* Unknown Size */
typedef struct unk80056930 {
    u8 unk0[0x3];
    s8 unk3;
} unk80056930;

/* Unknown size */
typedef struct Object_64_800575EC {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 ox1;
    /* 0x3C */ f32 oy1;
    /* 0x40 */ f32 oz1;
    /* 0x44 */ f32 ox2;
    /* 0x48 */ f32 oy2;
    /* 0x4C */ f32 oz2;
    /* 0x50 */ f32 ox3;
    /* 0x54 */ f32 oy3;
    /* 0x58 */ f32 oz3;
} Object_64_800575EC;

/* Unknown Size */
typedef struct unk800579B0 {
    u8 unk0[0x1E1];
    s8 unk1E1;
} unk800579B0;

typedef struct Object_64_800580B4 {
    u8 unk0[0x1D8];
    s8 unk1D8;
} Object_64_800580B4;

/* Unknown Size */
typedef struct unk8005C270 {
    u8 unk0[0x190];
    s16 unk190;
    s8 unk192;
    s8 unk193;
} unk8005C270;

extern s32 gObjLoopGoldenBalloonLength;
extern s16 D_800DCB54;
extern s32 D_800DCB58;
extern s32 D_800DCB5C;

// Not sure if D_800DCB58 & D_800DCB5C are actually a part of this array.
extern f32 D_800DCB60[14];

extern s32 D_800DCB98;
extern f32 D_800DCB9C[19];

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

extern s32 D_8011D534;

s32 get_random_number_from_range(s32, s32); //?
void func_8006FC30(Matrix, ObjectTransform *); // asm func
void func_8006FE74(Matrix *, ObjectTransform *); // Non Matching ?

s32 func_80044450(s32 arg0);
void func_8004C0A0(s32 arg0, Object *planeObj, Object_64_8004C0A0 *planeObj64);
void func_8004C140(Object *obj, Object_64_8004C140 *obj64);
void func_8004D95C(s32 arg0, s32 arg1, Object *obj, Object_64_8004D95C *obj64);
void func_8004F77C(unk8004F77C *arg0);
s32 func_80052188(void);
void func_800521B8(s32 arg0);
void func_8005234C(unk8005234C *arg0);
void func_80052988(Object *arg0, Object_64 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_80053478(Object_64_80053478 *obj);
void func_800535C4(unk800535C4 *arg0, unk800535C4_2 *arg1);
void func_80053664(Object_64 *arg0);
void play_char_horn_sound(Object *obj, Object_64 *obj64);
void func_80057048(Object *obj, s32 arg1);
void func_800570A4(Object *obj, s32 arg1, s32 arg2);
void func_800575EC(Object *obj, Object_64_800575EC *obj64);
void func_800579B0(unk800579B0 *arg0, s32 arg1, f32 arg2);
void func_800580B4(Object *obj, Object_64_800580B4 *obj64, s32 arg2, f32 arg3);
void func_80059790(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3);
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
void func_8005C25C(void);

//Non Matching
void set_ghost_position_and_rotation(Object *obj);
void func_800570B8(Object *obj, s32 arg1, s32 arg2, s32 arg3);
void func_800576E0(Object *obj, Object_64_8004C140 *obj64, s32 arg2);
void func_80057A40(Object *obj, Object_64_800580B4 *obj64, f32 arg2);

#endif
