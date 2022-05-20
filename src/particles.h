#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "types.h"
#include "structs.h"

/* Size: 0xA0 bytes */
typedef struct ParticleBehavior {
    s32 flags;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[4];
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    u8 pad28[0x74];
    s32 *unk9C;
} ParticleBehavior;

typedef struct unk800AF29C_C_4000 {
    f32 unkC;
    f32 unk10;
    f32 unk14;
} unk800AF29C_C_4000;

typedef struct unk800AF29C_C_400 {
    s32 *unkC;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} unk800AF29C_C_400;

typedef struct unk800AF29C_C {
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} unk800AF29C_C;

typedef struct unk800AF29C {
    ParticleBehavior *unk0;
    s16 unk4;
    u8 unk6;
    u8 unk7;
    s16 unk8;
    s16 unkA;
    union {
        unk800AF29C_C_4000 unkC_4000;
        unk800AF29C_C_400  unkC_400;
        unk800AF29C_C      unkC;
    } unkB;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
} unk800AF29C;

typedef struct unk800E2CF0 {
    u8 pad0[8];
    s16 unk8;
} unk800E2CF0;

/* Size: 0x10 bytes */
typedef struct unk800E2D08 {
    s16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
} unk800E2D08;

/* Size: 6 bytes */
typedef struct unk800E2D58 {
    s16 unk0, unk2, unk4;
} unk800E2D58;

typedef struct unk800AF024 {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    Vertex *unk8;
    Triangle *unkC;
} unk800AF024;

typedef struct unk800B2260_C {
    s32 unk0;
    s32 unk4;
    u8  pad8[0x32];
    s16 unk3A;
    u8  pad3C[0x34];
    void *unk70; // unk800B2260 *
    u8 unk74;
} unk800B2260_C;

//Could be the same as Object_6C
typedef struct unk800B2260 {
    ParticleBehavior *unk0;
    s16 unk4;
    u8  unk6;
    s16 unk8;
    s16 unkA;
    unk800B2260_C **unkC;
} unk800B2260;

typedef struct XYStruct {
    s16 x, y;
} XYStruct;

void func_800AE270(void);
void func_800AE2A0(void);
void func_800AE2D8(void);
void func_800AE374(void);
void func_800AE438(void);
void func_800AE490(void);
void func_800AEE14(unk800AF024 *arg0, Vertex **arg1, Triangle **arg2);
void func_800AEEB8(unk800AF024 *arg0, Vertex **arg1, Triangle **arg2);
void func_800AEF88(unk800AF024 *arg0, Vertex **arg1, Triangle **arg2);
void func_800AF024(unk800AF024 *arg0, Vertex **arg1, Triangle **arg2);
void func_800AF0A4(Object *obj);
void func_800AF0F0(Object *obj);
void func_800AF1E0(unk800AF29C *arg0, s32 arg1, s32 arg2);
void func_800AF29C(unk800AF29C *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5);
void func_800AF6E4(Object *obj, s32 arg1);
void func_800B2260(unk800B2260 *arg0);
void func_800B263C(unk800B2260_C *arg0);

void func_800AF134(unk800B2260 *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5); // Non Matching
void func_800AF404(s32 arg0); // Non Matching
void func_800AFC3C(Object *, s32); // Non Matching
void init_particle_assets(void); // Non Matching
void func_800AE728(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); // Non Matching
void func_800AF714(Object*, s32, f32); // Non matching

#endif
