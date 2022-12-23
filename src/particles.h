#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "types.h"
#include "structs.h"
#include "libultra_internal.h"

typedef struct unk800E2CF0 {
    u8 pad0[8];
    s16 unk8;
    u8 padA[13];
    u8 unk17;
} unk800E2CF0;

/* Size: 0x10 bytes */
typedef struct unk800E2D08 {
    s16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
} unk800E2D08;

typedef struct unk800AF024 {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    Vertex *unk8;
    Triangle *unkC;
} unk800AF024;

typedef struct XYStruct {
    s16 x, y;
} XYStruct;

typedef struct unk800B03C0_arg2 {
    u8 pad0[0xC];
    s16 y_rotation;
    s16 x_rotation;
    s16 z_rotation;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
} unk800B03C0_arg2;

typedef struct unk800B2260_C_44 {
    TextureHeader *texture;
} unk800B2260_C_44;

typedef struct unk800B1CB8 {
    u8 pad0[0x2C];
    s16 unk2C;
    u8 pad2E[0x1A];
    s16 unk48;
    u8 pad4A[0x26];
} unk800B1CB8;

/* Size: 0x78 bytes */
typedef struct unk800E2CD8 {
    unk800B1CB8 unk0;
    u8 pad80[8];
} unk800E2CD8;

/* Size: 32 bytes */
typedef struct Object_6C_800AF52C {
    ParticleBehavior *unk0;
    s16 unk4;
    u8 unk6;
    u8 unk7;
    s16 unk8;
    s16 unkA;
    union {
        Object **unkC_arr;
        struct {
            s16 unkC;
            s16 unkE;
        };
    };
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    u8 pad18[0x8];
} Object_6C_800AF52C;

extern unk800E2CF0 **gParticlesAssetTable;
extern s32 gParticlesAssetTableCount;
extern s32 D_80127CB8;
extern s32 D_80127CCC;
extern u16 D_80127CAE;
extern u16 D_80127CAC;
extern u16 D_80127CD0;
extern s32 D_80127CBC;
extern s32 D_80127CC0;
extern u16 D_80127CD2;
extern s32 D_80127CC4;
extern s32 D_80127CC8;
extern s32 D_80127CB4;
extern s16 D_80127CB0;
extern s16 D_80127CB2;
extern OSThread D_801295E0;

extern ParticleBehavior **gParticleBehavioursAssetTable;
extern s32 gParticleBehavioursAssetTableCount;

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
void func_800AF1E0(Object *arg0, s32 arg1, s32 arg2);
void func_800AF29C(Object *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5);
void func_800AF6E4(Object *obj, s32 arg1);
void func_800B2260(Object *arg0);
void func_800B263C(unk800B2260_C *arg0);
void init_particle_assets(void);
void func_800B2FBC(Object *arg0);
void func_800B03C0(Object *arg0, ObjectTransform *arg1, unk800B03C0_arg2 *arg2, Object *arg3);
void func_800B2040(unk800B2260_C *arg0);
void func_800B22FC(Object *arg0, s32 arg1);
void func_800B0010(Object *arg0, Object *arg1, unk800B03C0_arg2 *arg2, Object *arg3);

void func_800AF134(Object *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5); // Non Matching
void func_800AF404(s32 arg0); // Non Matching
void func_800AFC3C(Object *, s32); // Non Matching
void func_800AE728(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); // Non Matching
void func_800AF714(Object*, s32); // Non matching
Object* func_800B1130(s32, void*);
Object* func_800B0BAC();
Object *func_800B0698(s32, void*);
void func_800B26E0();
void func_800B3140(Object *);
void func_800B3240(Object *);
void func_800B3358(Object *);
void func_800B34B0(Object *);
void func_800B3564(Object *);

#endif
