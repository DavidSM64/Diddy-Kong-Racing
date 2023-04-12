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
    f32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
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

typedef struct unk800B1CB8_44_8 {
    u8 pad0[6];
    s16 unk6;
} unk800B1CB8_44_8;
typedef struct unk800B1CB8_44 {
    s16 unk0;
    u8 pad2[6];
    unk800B1CB8_44_8 **unk8;
} unk800B1CB8_44;

typedef struct unk800B1CB8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    f32 unk8;
    u8 padC[0xC];
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
    s16 unk2E;
    u8 pad30[0x4];
    f32 unk34;
    u8 unk38;
    u8 unk39;
    s16 unk3A;
    struct unk800B1CB8 *unk3C;
    s32 unk40;
    struct unk800B1CB8_44 *unk44;
    s16 unk48;
    s16 unk4A;
    u8 pad4C[0x8];
    f32 *unk54;
    f32 unk58;
    s16 unk5C;
    s16 unk5E;
    s16 unk60;
    s16 unk62;
    s16 unk64;
    s16 unk66;
    f32 unk68;
    ColourRGBA unk6C;
} unk800B1CB8;

/* Size: 0x78 bytes */
typedef struct unk800E2CD8 {
 unk800B1CB8 unk0;
    struct Particle *unk70;
    u8 pad74;
    u8 unk75;
    u8 unk76;
    u8 unk77;
} unk800E2CD8;

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

typedef struct Particle {
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
  /* 0x000C */ unk800AF29C_C unkC;
  /* 0x000C */ struct Particle2 **unkC_60;
  /* 0x000C */ unk800AF29C_C_400 unkC_400;
    };
  /* 0x0018 */ s16 unk18;
  /* 0x0018 */ s16 unk1A;
  /* 0x001C */ s16 unk1C;
  /* 0x001E */ s16 unk1E;
  /* 0x0020 */ s16 unk20;
  /* 0x0022 */ s16 unk22;
  /* 0x0024 */ s16 unk24;
  /* 0x0026 */ s16 unk26;
  /* 0x0028 */ s16 unk28;
  /* 0x002A */ s16 unk2A;
  /* 0x002C */ s16 unk2C;
  /* 0x002E */ s16 unk2E;
  /* 0x0030 */ f32 unk30;
  /* 0x0034 */ f32 unk34;
  union {
      struct {
          /* 0x0038 */ u8 unk38;
          /* 0x0039 */ u8 unk39;
          /* 0x003A */ s8 unk3A;
          /* 0x003B */ s8 unk3B;
      } byte;
      struct {
          /* 0x0038 */ s16 unk38;
          /* 0x003A */ s16 unk3A;
      } half;
      f32 unk38_f32;
  } unk38;
  /* 0x003C */ f32 unk3C;
  /* 0x0040 */ s32 unk40;

  union {
  /* 0x0044 */ unk800B0698_44 *unk44;
  /* 0x0044 */ TextureHeader *unk44_0;
  };
  /* 0x0048 */ s16 behaviorId;
  /* 0x004A */ s16 unk4A;
  /* 0x004C */ f32 unk4C_f32;
  /* 0x0050 */ f32 unk50_f32;
  /* 0x0054 */ f32 unk54_f32;
  /* 0x0058 */ f32 unk58_f32;
  union {
      struct {
  /* 0x005C */ s16 unk5C;
  /* 0x005E */ s16 unk5E;
      } unk5C_halfs;
  /* 0x005C */ s32 unk5C_s32;
  };
  union {
      struct {
  /* 0x0060 */ s16 unk60;
  /* 0x0062 */ s16 unk62;
      } unk60_halfs;
  /* 0x0060 */ s32 unk60_s32;
  };
  /* 0x0064 */ s16 unk64;
  /* 0x0066 */ s16 unk66;
  union {
  /* 0x0068 */ Object_68 **gfxData;
      struct {
  /* 0x0068 */ s16 unk68;
  /* 0x006A */ s16 unk6A;
      } unk68_halfs;
  };
  /* 0x006C */ s16 unk6C;
  /* 0x006E */ s16 unk6E;
} Particle;

typedef struct Particle2 {
  /* 0x0000 */ ObjectTransform trans;
  /* 0x0018 */ s16 unk18;
  /* 0x0018 */ s16 unk1A;
  /* 0x001C */ s16 unk1C;
  /* 0x001E */ s16 unk1E;
  /* 0x0020 */ s16 unk20;
  /* 0x0022 */ s16 unk22;
  /* 0x0024 */ s16 unk24;
  /* 0x0026 */ s16 unk26;
  /* 0x0028 */ s16 unk28;
  /* 0x002A */ s16 unk2A;
  /* 0x002C */ s16 unk2C;
  /* 0x002E */ s16 unk2E;
  /* 0x0030 */ f32 unk30;
  /* 0x0034 */ f32 unk34;
  union {
      struct {
          /* 0x0038 */ u8 unk38;
          /* 0x0039 */ u8 unk39;
          /* 0x003A */ s8 unk3A;
          /* 0x003B */ s8 unk3B;
      } byte;
      struct {
          /* 0x0038 */ s16 unk38;
          /* 0x003A */ s16 unk3A;
      } half;
      f32 unk38_f32;
  } unk38;
  /* 0x003C */ f32 unk3C;
  /* 0x0040 */ s32 unk40;

  union {
  /* 0x0044 */ unk800B0698_44 *unk44;
  /* 0x0044 */ TextureHeader *unk44_0;
  /* 0x0044 */ unk800B2260_C_44 *unk44_1;
  };
  /* 0x0048 */ s16 behaviorId;
  /* 0x004A */ s16 unk4A;
  /* 0x004C */ f32 unk4C_f32;
  /* 0x0050 */ f32 unk50_f32;
  /* 0x0054 */ f32 unk54_f32;
  /* 0x0058 */ f32 unk58_f32;
  union {
      struct {
  /* 0x005C */ s16 unk5C;
  /* 0x005E */ s16 unk5E;
      } unk5C_halfs;
  /* 0x005C */ s32 unk5C_s32;
  };
  union {
      struct {
  /* 0x0060 */ s16 unk60;
  /* 0x0062 */ s16 unk62;
      } unk60_halfs;
  /* 0x0060 */ s32 unk60_s32;
  };
  /* 0x0064 */ s16 unk64;
  /* 0x0066 */ s16 unk66;
  union {
  /* 0x0068 */ Object_68 **gfxData;
      struct {
  /* 0x0068 */ s16 unk68;
  /* 0x006A */ s16 unk6A;
      } unk68_halfs;
  };
  /* 0x006C */ s16 unk6C;
  /* 0x006E */ s16 unk6E;
  /* 0x0070 */ struct Particle *unk70;
  /* 0x0074 */ u8 unk74;
  /* 0x0075 */ u8 unk75;
  /* 0x0076 */ u8 unk76;
  /* 0x0077 */ u8 unk77;
} Particle2;

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
void partInitTrigger(Particle *arg0, s32 arg1, s32 arg2);
void func_800AF29C(Particle *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5);
void func_800AF6E4(Object *obj, s32 arg1);
void func_800B2260(Particle *arg0);
void func_800B263C(Particle2 *arg0);
void init_particle_assets(void);
void func_800B2FBC(Particle2 *arg0);
void func_800B03C0(Object *arg0, ObjectTransform *arg1, unk800B03C0_arg2 *arg2, Object *arg3);
void func_800B2040(Particle2 *arg0);
void func_800B22FC(Particle2 *arg0, s32 arg1);
void func_800B0010(Object *arg0, Object *arg1, unk800B03C0_arg2 *arg2, Object *arg3);
Particle2 *func_800B0698(unk800B1CB8 *arg0, Particle *arg1);
unk800B1CB8 *func_800B1CB8(s32 arg0);
void func_800AFE5C(unk800B1CB8 *arg0, Particle *arg1);
Particle2 *func_800B1130(unk800B1CB8 *arg0, Particle *arg1);
void func_800AF52C(Object *obj, s32 arg1);
void func_800AF134(Particle *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5);

void func_800AF404(s32 arg0); // Non Matching
void func_800AFC3C(Object *, s32); // Non Matching
void func_800AE728(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); // Non Matching
void func_800AF714(Object*, s32); // Non matching
Object *func_800B0BAC();
void func_800B26E0();
void func_800B3140(Particle2 *);
void func_800B3240(Particle2 *);
void func_800B3358(Particle2 *);
void func_800B34B0(Particle2 *);
void func_800B3564(Particle2 *);
void func_800B3740(Object *, Gfx **, MatrixS **, Vertex **, s32); // Non Matching
void func_800B4668(Object*, s32, s32, s32);
void func_800B46BC(Object*, s32, s32, s32);

#endif
