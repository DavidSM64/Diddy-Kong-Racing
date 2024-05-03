#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "types.h"
#include "structs.h"
#include "libultra_internal.h"

enum ObjectEmitterFlags {
    OBJ_EMIT_OFF,
    OBJ_EMIT_PARTICLE_1 = (1 << 0),
    OBJ_EMIT_PARTICLE_2 = (1 << 1),
    OBJ_EMIT_PARTICLE_3 = (1 << 2),
    OBJ_EMIT_PARTICLE_4 = (1 << 3),
    OBJ_EMIT_UNK_10 = (1 << 4),
    OBJ_EMIT_UNK_20 = (1 << 5),
    OBJ_EMIT_UNK_40 = (1 << 6),
    OBJ_EMIT_UNK_80 = (1 << 7),
    OBJ_EMIT_UNK_100 = (1 << 8),
    OBJ_EMIT_UNK_200 = (1 << 9),
    OBJ_EMIT_UNK_400 = (1 << 10),
    OBJ_EMIT_UNK_800 = (1 << 11),
    OBJ_EMIT_UNK_1000 = (1 << 12),
    OBJ_EMIT_UNK_2000 = (1 << 13),
    OBJ_EMIT_UNK_4000 = (1 << 14),
    OBJ_EMIT_UNK_8000 = (1 << 15),
};

enum ParticleFlags {
    PARTICLE_FLAGS_NONE,
    PARTICLE_GRAVITY = (1 << 0),
    PARTICLE_UNK00000002 = (1 << 1),
    PARTICLE_UNK00000004 = (1 << 2),
    PARTICLE_UNK00000008 = (1 << 3),
    PARTICLE_UNK00000010 = (1 << 4),
    PARTICLE_UNK00000020 = (1 << 5),
    PARTICLE_UNK00000040 = (1 << 6),
    PARTICLE_UNK00000080 = (1 << 7),
    PARTICLE_VEL_X = (1 << 8),
    PARTICLE_VEL_Y = (1 << 9),
    PARTICLE_VEL_Z = (1 << 10),
    PARTICLE_ANGLE_Y = (1 << 11),
    PARTICLE_ANGLE_X = (1 << 12),
    PARTICLE_ANGLE_Z = (1 << 13),
    PARTICLE_ANGLEVEL_Y = (1 << 14),
    PARTICLE_ANGLEVEL_X = (1 << 15),
    PARTICLE_ANGLEVEL_Z = (1 << 16),
    PARTICLE_UNK00020000 = (1 << 17),
    PARTICLE_UNK00040000 = (1 << 18),
    PARTICLE_FORWARDVEL = (1 << 19),
    PARTICLE_COLOURVEL_RED = (1 << 20),
    PARTICLE_COLOURVEL_GREEN = (1 << 21),
    PARTICLE_COLOURVEL_BLUE = (1 << 22),
    PARTICLE_COLOURVEL_ALPHA = (1 << 23),
    PARTICLE_UNK01000000 = (1 << 24),
    PARTICLE_UNK02000000 = (1 << 25),
    PARTICLE_UNK04000000 = (1 << 26),
    PARTICLE_UNK08000000 = (1 << 27),
    PARTICLE_UNK10000000 = (1 << 28),
    PARTICLE_UNK20000000 = (1 << 29),
    PARTICLE_UNK40000000 = (1 << 30),
    PARTICLE_UNK80000000 = (1 << 31),
};

enum ParticleMovement {
    PARTICLE_MOVEMENT_0,
    PARTICLE_MOVEMENT_1,
    PARTICLE_MOVEMENT_VELOCITIES,
    PARTICLE_MOVEMENT_VELOCITY_PARENT,
    PARTICLE_MOVEMENT_BASIC_PARENT,
    PARTICLE_MOVEMENT_VELOCITY,
};

typedef struct ParticleProperties {
  /* 0x00 */ u8 unk0;
  /* 0x01 */ u8 movementType;
  /* 0x02 */ u16 unk2;
  /* 0x04 */ s16 textureID;
  /* 0x06 */ s16 unk6;
  union {
    struct {
        /* 0x08 */ s16 lifeTime;
        union {
        /* 0x0A */ s16 lifeTimeRange;
        /* 0x0A */ u16 lifeTimeRangeUnsigned;
        };
    };
    /* 0x08 */ s32 lifeTimeWord;
  };
  /* 0x0C */ u8 opacity;
  /* 0x0D */ u8 opacityVel;
  /* 0x0E */ s16 opacityTimer;
  /* 0x10 */ f32 scale;
  /* 0x14 */ ColourRGBA colour;
} ParticleProperties;

/* Size: 0x10 bytes */
typedef struct unk800E2D08 {
    s16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
} unk800E2D08;

typedef struct XYStruct {
    s16 x, y;
} XYStruct;

typedef struct unk800B1CB8_44_8 {
    u8 pad0[6];
    s16 unk6;
} unk800B1CB8_44_8;

typedef struct unk800B1130_SP28 {
    s32 unk0;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} unk800B1130_SP28;


// Size: 8 bytes
typedef struct Particle_58_0_9C {
    u8 pad0[4];
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
} Particle_58_0_9C;

typedef struct Particle_58_0 {
    s32 unk0;
    u8 pad4[0x2];
    u8 unk6;
    u8 pad7[0x5];
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 pad18[0x6];
    s16 unk1E;
    u8 pad20[0x7C];
    Particle_58_0_9C *unk9C;
} Particle_58_0;

typedef struct Particle_58 {
    Particle_58_0 *unk0;
    u8 pad4[0x2];
    u8 unk6;
    u8 pad7[0x5];
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 pad18[0x6];
    s16 unk1E;
} Particle_58;

typedef struct ParticleSegment_3C {
    u8 pad0[0x1C];
    f32 unk1C;
    f32 unk20;
    f32 unk24;
} ParticleSegment_3C;

typedef struct ParticleAngle {
    s16 y_rotation;
    s16 x_rotation;
    s16 z_rotation;
    s16 y_direction;
    s16 x_direction;
    s16 z_direction;
} ParticleAngle;

typedef struct ParticleData {
    union {
  /* 0x0000 */ ParticleBehavior *behaviour;
  /* 0x0000 */ s32 unk0;
    };
  /* 0x0004 */ s16 flags;
  /* 0x0006 */ u8 unk6;
  /* 0x0007 */ u8 lifeTime;
  /* 0x0008 */ s16 propertyID;
  /* 0x000A */ s16 opacity;
    union {
  /* 0x000C */ Vec3f pos;
  /* 0x000C */ ParticleAngle angle;
  /* 0x000C */ struct Particle **unkC_60;
  /* 0x000C */ unk800AF29C_C_400 unkC_400;
    };
  /* 0x0018 */ s16 baseVelX;
  /* 0x0018 */ s16 baseVelY;
  /* 0x001C */ s16 baseVelZ;
  /* 0x001E */ s16 unk1E;
  /* 0x0020 */ s32 unk20;
  /* 0x0024 */ s32 unk24;
  /* 0x0028 */ s32 unk28;
  /* 0x002C */ s16 unk2C;
  /* 0x002E */ s16 unk2E;
} ParticleData;

typedef struct ParticleSegment {
  /* 0x0000 */ ObjectTransform trans;
  /* 0x0018 */ s16 textureFrame;
  /* 0x001A */ s16 unk1A;
  /* 0x001C */ f32 x_velocity;
  /* 0x0020 */ f32 y_velocity;
  /* 0x0024 */ f32 z_velocity;
  /* 0x0028 */ f32 scaleVel;
  union {
      SegmentPropertiesObject object;
      SegmentPropertiesParticle particle;
      SegmentPropertiesCamera camera;
  };
  /* 0x003C */ void *unk3C;
  union {
    struct {
        /* 0x0040 */ s16 unk40_s16;
        /* 0x0042 */ s16 unk42;
    };
    s32 unk40;
  };
} ParticleSegment;

typedef struct ParticleModel {
    /* 0x00 */ TextureHeader *texture;
    /* 0x04 */ s16 vertexCount;
    /* 0x06 */ s16 triangleCount;
    /* 0x08 */ Vertex *vertices;
    /* 0x0C */ Triangle *triangles;
} ParticleModel;

typedef struct ParticleOtherSomething {
    /* 0x00 */ s16 textureCount;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ unk800B1CB8_44_8 **unk8;
} ParticleOtherSomething;

typedef struct Particle {
  union {
  /* 0x0000 */ ParticleSegment segment;
  /* 0x0000 */ ParticleData data;
  };
  union {
  /* 0x0044 */ ParticleModel *modelData;
  /* 0x0044 */ ParticleOtherSomething *unk44_1;
  };
  /* 0x0048 */ s16 behaviorId;
  /* 0x004A */ s16 brightness;
  /* 0x004C */ f32 baseVelX;
  /* 0x0050 */ f32 baseVelY;
  union {
  /* 0x0054 */ f32 baseVelZ;
  /* 0x0054 */ f32 *unk54_ptr;
  };
  union {
  /* 0x0058 */ Particle_58 **unk58_ptr;
  /* 0x0058 */ f32 forwardVel;
  };
  /* 0x005C */ s16 opacity;
  /* 0x005E */ s16 opacityVel;
  /* 0x0060 */ s16 opacityTimer;
  /* 0x0062 */ s16 angleVelY;
  /* 0x0064 */ s16 angleVelX;
  /* 0x0066 */ s16 angleVelZ;
  union {
  /* 0x0068 */ f32 gravity;
  struct {
  /* 0x0068 */ u8 unk68b;
  /* 0x0069 */ u8 unk69b;
  /* 0x006A */ s8 unk6Ab;
  /* 0x006B */ s8 unk6Bb;
  };
  };
  /* 0x006C */ ColourRGBA colour;
  /* 0x0070 */ struct Particle *unk70;
  /* 0x0074 */ u8 unk74;
  /* 0x0075 */ u8 modelFrame;
  /* 0x0076 */ u8 unk76;
  /* 0x0077 */ s8 unk77;
} Particle;

// Size: 8 bytes
typedef struct unkParticleBehaviorUnk9C {
    s32 unk0;
    u8 r;
    u8 g;
    u8 b;
    u8 pad7; // Probably alpha
} unkParticleBehaviorUnk9C;

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
void generate_particle_shape_triangle(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void generate_particle_shape_quad(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void func_800AEF88(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void func_800AF024(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void func_800AF0A4(Particle *particle);
void func_800AF0F0(Particle *particle);
void partInitTrigger(Particle *particle, s32 behaviourID, s32 propertyID);
void func_800AF29C(Particle *arg0, s32 behaviourID, s32 propertyID, s16 velX, s16 velY, s16 velZ);
void func_800AF6E4(Object *obj, s32 arg1);
void func_800B2260(Particle *arg0);
void func_800B263C(Particle *arg0);
void init_particle_assets(void);
void set_particle_texture_frame(Particle *particle);
void func_800B03C0(Particle *particle, Particle *arg1, Particle *arg2, ParticleBehavior *behaviour);
void func_800B2040(Particle *arg0);
void handle_particle_movement(Particle *particle, s32 updateRate);
void func_800B0010(Particle *arg0, Particle *arg1, Particle *arg2, ParticleBehavior *arg3);
Particle *func_800B0698(Particle *arg0, Particle *arg1);
Particle *func_800B1CB8(s32 arg0);
void func_800AFE5C(Particle *arg0, Particle *arg1);
Particle *func_800B1130(Particle *arg0, Particle *arg1);
void func_800AF52C(Object *obj, s32 arg1);
void func_800AF134(Particle *particle, s32 behaviourID, s32 propertyID, s16 velX, s16 velY, s16 velZ);
void render_particle(Particle *particle, Gfx **dList, MatrixS **mtx, Vertex **vtx, s32 flags);
void func_800B4668(Object *obj, s32 idx, s32 arg2, s32 arg3);
void func_800B46BC(Object *obj, s32 idx, s32 arg2, s32 arg3);
void obj_spawn_particle(Object *obj, s32 updateRate);
void func_800B3E64(Object *obj);
void func_800B26E0(Particle *particle);
void func_800AF714(Object *racerObj, s32 updateRate);
Particle* func_800B0BAC(Object* arg0, Particle* arg1);

void func_800AF404(s32 updateRate); // Non Matching
void func_800AE728(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); // Non Matching
void move_particle_basic_parent(Particle *);
void move_particle_velocity_parent(Particle *);
void move_particle_with_velocities(Particle *);
void move_particle_basic(Particle *);
void move_particle_with_velocity(Particle *);

#endif
