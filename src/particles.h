#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "types.h"
#include "structs.h"
#include "libultra_internal.h"

typedef struct unk800E2CF0 {
    u8 unk0;
    u8 unk1;
    u16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    u8 unkC;
    u8 unkD;
    s16 unkE;
    f32 scale;
    ColourRGBA colour;
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

typedef struct unk800B2260_C_44 {
    TextureHeader *texture;
} unk800B2260_C_44;

typedef struct unk800B1CB8_44_8 {
    u8 pad0[6];
    s16 unk6;
} unk800B1CB8_44_8;
typedef struct unk800B1CB8_44 {
    s16 unk0;
    u8 pad2[6];
    unk800B1CB8_44_8 **unk8;
} unk800B1CB8_44;

typedef struct unk800B1130_8 {
    u8 pad0[6];
    s16 unk6;
} unk800B1130_8;

typedef struct unk800B1130 {
    u8 pad0[8];
    unk800B1130_8 **unk8;
    u8 padC[0x6];
    u16 unk12;
} unk800B1130;

typedef struct unk800B1130_SP28 {
    s32 unk0;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} unk800B1130_SP28;

typedef struct ParticleAngle {
    s16 y_rotation;
    s16 x_rotation;
    s16 z_rotation;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} ParticleAngle;

typedef struct ParticleData {
    union {
  /* 0x0000 */ ParticleBehavior *behaviour;
  /* 0x0000 */ s32 unk0;
    };
  /* 0x0004 */ s16 flags;
  /* 0x0006 */ u8 unk6;
  /* 0x0007 */ u8 unk7;
  /* 0x0008 */ s16 unk8;
  /* 0x000A */ s16 unkA;
    union {
  /* 0x000C */ Vec3f pos;
  /* 0x000C */ ParticleAngle angle;
  /* 0x000C */ unk800AF29C_C unkC;
  /* 0x000C */ struct Particle **unkC_60;
  /* 0x000C */ unk800AF29C_C_400 unkC_400;
    };
  /* 0x0018 */ s16 unk18;
  /* 0x0018 */ s16 unk1A;
  /* 0x001C */ s16 unk1C;
  /* 0x001E */ s16 unk1E;
  /* 0x0020 */ s32 unk20;
  /* 0x0024 */ s32 unk24;
  /* 0x0028 */ s32 unk28;
  /* 0x002C */ s16 unk2C;
  /* 0x002E */ s16 unk2E;
} ParticleData;

typedef struct ParticleSegment {
  /* 0x0000 */ ObjectTransform trans;
  /* 0x0018 */ s16 unk18;
  /* 0x001A */ s16 unk1A;
  /* 0x001C */ f32 x_velocity;
  /* 0x0020 */ f32 y_velocity;
  /* 0x0024 */ f32 z_velocity;
  /* 0x0028 */ f32 unk28;
  union {
      SegmentPropertiesObject object;
      SegmentPropertiesParticle particle;
      SegmentPropertiesCamera camera;
  };
  /* 0x003C */ void *unk3C;
  /* 0x0040 */ s32 unk40;
} ParticleSegment;

typedef struct Particle {
  union {
  /* 0x0000 */ ParticleSegment segment;
  /* 0x0000 */ ParticleData data;
  };
  union {
  /* 0x0044 */ unk800B0698_44 *unk44;
  /* 0x0044 */ TextureHeader *unk44_0;
  /* 0x0044 */ unk800B2260_C_44 *unk44_1;
  /* 0x0044 */ struct unk800B1CB8_44 *unk44_2;
  };
  /* 0x0048 */ s16 behaviorId;
  /* 0x004A */ s16 unk4A;
  /* 0x004C */ f32 somePosX;
  /* 0x0050 */ f32 somePosY;
  union {
  /* 0x0054 */ f32 somePosZ;
  /* 0x0054 */ f32 *unk54_ptr;
  };
  /* 0x0058 */ f32 forwardVel;
  /* 0x005C */ s16 unk5C;
  /* 0x005E */ s16 unk5E;
  /* 0x0060 */ s16 unk60;
  /* 0x0062 */ s16 unk62;
  /* 0x0064 */ s16 unk64;
  /* 0x0066 */ s16 unk66;
  union {
  /* 0x0068 */ u8 unk68b;
  /* 0x0068 */ f32 unk68f;
  };
  /* 0x006C */ ColourRGBA colour;
  /* 0x0070 */ struct Particle *unk70;
  /* 0x0074 */ u8 unk74;
  /* 0x0075 */ u8 unk75;
  /* 0x0076 */ u8 unk76;
  /* 0x0077 */ s8 unk77;
} Particle;

// Almost an identical copy of Particle, but a few bytes shorter. Exists to make sure func_800B1CB8 matches.
typedef struct ParticleType {
    u8 pad[0x2C];
    s16 unk2C;
    u8 pad2[0x42];
} ParticleType;

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
void func_800AF0A4(Particle *particle);
void func_800AF0F0(Particle *particle);
void partInitTrigger(Particle *arg0, s32 arg1, s32 arg2);
void func_800AF29C(Particle *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5);
void func_800AF6E4(Object *obj, s32 arg1);
void func_800B2260(Particle *arg0);
void func_800B263C(Particle *arg0);
void init_particle_assets(void);
void func_800B2FBC(Particle *arg0);
void func_800B03C0(Particle *arg0, Particle *arg1, Particle *arg2, ParticleBehavior *arg3);
void func_800B2040(Particle *arg0);
void func_800B22FC(Particle *arg0, s32 arg1);
void func_800B0010(Particle *arg0, Particle *arg1, Particle *arg2, ParticleBehavior *arg3);
Particle *func_800B0698(Particle *arg0, Particle *arg1);
Particle *func_800B1CB8(s32 arg0);
void func_800AFE5C(Particle *arg0, Particle *arg1);
Particle *func_800B1130(Particle *arg0, Particle *arg1);
void func_800AF52C(Object *obj, s32 arg1);
void func_800AF134(Particle *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5);
void *memset(void *s, int c, size_t n);
void func_800B3740(Particle *particle, Gfx **dlist, MatrixS **mtx, Vertex **vtx, s32 flags);

void func_800AF404(s32 arg0); // Non Matching
void func_800AFC3C(Object *, s32); // Non Matching
void func_800AE728(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); // Non Matching
void func_800AF714(Object*, s32); // Non matching
Particle *func_800B0BAC();
void func_800B26E0();
void func_800B3140(Particle *);
void func_800B3240(Particle *);
void func_800B3358(Particle *);
void func_800B34B0(Particle *);
void func_800B3564(Particle *);
void func_800B4668(Object*, s32, s32, s32);
void func_800B46BC(Object*, s32, s32, s32);
void func_800B3E64(Object *); // Non Matching

#endif
