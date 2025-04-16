#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "types.h"
#include "structs.h"
#include <ultra64.h>

enum ParticleKind {
    PARTICLE_KIND_NONE = 0,
    PARTICLE_KIND_TRIANGLE = 1,
    PARTICLE_KIND_RECTANGLE = 2,
    PARTICLE_KIND_LINE = 3,
    PARTICLE_KIND_POINT = 4,
    PARTICLE_KIND_SPRITE = 128
};

// Flags representing which particle emitters are active for a game object
enum ObjectEmitterFlags {
    OBJ_EMIT_NONE,
    OBJ_EMIT_1 = (1 << 0),
    OBJ_EMIT_2 = (1 << 1),
    OBJ_EMIT_3 = (1 << 2),
    OBJ_EMIT_4 = (1 << 3),
    OBJ_EMIT_5 = (1 << 4),
    OBJ_EMIT_6 = (1 << 5),
    OBJ_EMIT_7 = (1 << 6),
    OBJ_EMIT_8 = (1 << 7),
    OBJ_EMIT_9 = (1 << 8),
    OBJ_EMIT_10 = (1 << 9),
    OBJ_EMIT_11 = (1 << 10),
    OBJ_EMIT_12 = (1 << 11),
    OBJ_EMIT_13 = (1 << 12),
    OBJ_EMIT_14 = (1 << 13),
    OBJ_EMIT_15 = (1 << 14),
    OBJ_EMIT_16 = (1 << 15),
    OBJ_EMIT_17 = (1 << 16),
    OBJ_EMIT_18 = (1 << 17),
    OBJ_EMIT_19 = (1 << 18),
    OBJ_EMIT_20 = (1 << 19),
};

enum ParticleRandomizationFlags {
    PARTICLE_RANDOM_SOURCE_DISTANCE = (1 << 0),
    PARTICLE_RANDOM_SOURCE_YAW = (1 << 1),
    PARTICLE_RANDOM_SOURCE_PITCH = (1 << 2),
    PARTICLE_UNK00000008 = (1 << 3),
    PARTICLE_UNK00000010 = (1 << 4),
    PARTICLE_UNK00000020 = (1 << 5),
    PARTICLE_UNK00000040 = (1 << 6),
    PARTICLE_UNK00000080 = (1 << 7),
    PARTICLE_RANDOM_VELOCITY_X = (1 << 8),
    PARTICLE_RANDOM_VELOCITY_Y = (1 << 9),
    PARTICLE_RANDOM_VELOCITY_Z = (1 << 10),
    PARTICLE_ANGLE_Y = (1 << 11),
    PARTICLE_ANGLE_X = (1 << 12),
    PARTICLE_ANGLE_Z = (1 << 13),
    PARTICLE_ANGLEVEL_Y = (1 << 14),
    PARTICLE_ANGLEVEL_X = (1 << 15),
    PARTICLE_ANGLEVEL_Z = (1 << 16),
    PARTICLE_RANDOM_SCALE = (1 << 17),
    PARTICLE_RANDOM_SCALE_VELOCITY = (1 << 18),
    PARTICLE_RANDOM_MOVEMENT_PARAM = (1 << 19),
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

enum ParticleBehaviorFlags {
    PARTICLE_FLAGS_NONE = 0,
    PARTICLE_SOURCE_OFFSET_ENABLED = 0x1,
    PARTICLE_SOURCE_ROTATION_ENABLED = 0x2,
    PARTICLE_SOURCE_EMITS_WITH_VELOCITY = 0x4,
    PARTICLE_BEHAVIOR_FLAG_8 = 0x8,
    PARTICLE_VELOCITY_RELATIVE_TO_PARENT = 0x10,
    PARTICLE_VELOCITY_ABSOLUTE = 0x20,
    PARTICLE_VELOCITY_SCALED_FROM_PARENT = 0x40,
    PARTICLE_ROTATION_ABSOLUTE = 0x80,
    PARTICLE_BEHAVIOR_FLAG_100 = 0x100,
    PARTICLE_BEHAVIOR_FLAG_200 = 0x200,
    PARTICLE_POINT = 0x400,
    PARTICLE_BEHAVIOR_FLAG_800 = 0x800,
    PARTICLE_SCALE_VELOCITY_INHERITS_PARENT_SPEED = 0x1000,
    PARTICLE_BEHAVIOR_FLAG_2000 = 0x2000,
    PARTICLE_LINE = 0x4000,
    PARTICLE_BEHAVIOR_FLAG_8000 = 0x8000
};

enum ParticleMovement {
    PARTICLE_MOVEMENT_NONE,
    PARTICLE_MOVEMENT_BASIC,
    PARTICLE_MOVEMENT_ACCELERATION,
    PARTICLE_MOVEMENT_VELOCITY_PARENT,
    PARTICLE_MOVEMENT_BASIC_PARENT,
    PARTICLE_MOVEMENT_VELOCITY,
};

enum ParticleField40 {
    PARTICLE_F40_1 = 0x1,
    PARTICLE_F40_2 = 0x2,
    PARTICLE_F40_4 = 0x4,
    PARTICLE_F40_8 = 0x8,
    PARTICLE_F40_GRAVITY_1 = 0x10,
    PARTICLE_F40_GRAVITY_2 = 0x20,
    PARTICLE_F40_GRAVITY_3 = 0x40,
    PARTICLE_F40_80 = 0x80,
    PARTICLE_F40_100 = 0x100,
    PARTICLE_F40_200 = 0x200,
    PARTICLE_F40_400 = 0x400,
    PARTICLE_F40_800 = 0x800,
    PARTICLE_F40_1000 = 0x1000,
    PARTICLE_F40_2000 = 0x2000,
    PARTICLE_F40_4000 = 0x4000,
    PARTICLE_F40_8000 = 0x8000,
};

typedef struct ParticleProperties {
  /* 0x00 */ u8 kind; // ParticleKind
  /* 0x01 */ u8 movementType; // ParticleMovement
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

typedef struct XYStruct {
    s16 x, y;
} XYStruct;

typedef struct unk800B1CB8_44_8 {
    u8 pad0[6];
    s16 unk6;
} unk800B1CB8_44_8;

typedef struct ColorLoopEntry {
    s32 unk0;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} ColorLoopEntry;

typedef struct ParticleAngle {
    Vec3s sourceRotation;
    Vec3s emissionDirection;
} ParticleAngle;

/* Size: 0xA0 bytes */
typedef struct ParticleBehavior {
    /* 0x00 */ s32 flags;
    /* 0x04 */ Vec3f emitterPos;
    /* 0x10 */ f32 sourceDistance;
    /* 0x14 */ Vec3s unk14;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ Vec2s unk1C;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    /* 0x30 */ Vec3f velocityModifier; // The meaning of the modifier depends on the flags
    /* 0x3C */ f32 emissionSpeed;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ Vec3s rotation;
    /* 0x4A */ Vec3s angularVelocity;
    f32 scale;
    f32 scaleVelocity;
    f32 movementParam;
    s32 randomizationFlags;
    s32 sourceDistanceRange;
    /* 0x64 */ Vec3s sourceDirRange;
    s16 angleRangeY2;
    s16 angleRangeX2;
    s16 angleRangeZ2;
    s32 emissionSpeedRange;
    Vec3i velocityModifierRange;
    s16 angleRangeY3;
    s16 angleRangeX3;
    s16 angleRangeZ3;
    s16 unk86;
    s16 unk88;
    s16 unk8A;
    s32 unk8C; // Something to do with scale
    s32 unk90; // Something to do with scale
    s32 movementParamRange;
    u8 colourRangeR;
    u8 colourRangeG;
    u8 colourRangeB;
    u8 colourRangeA;
    ColorLoopEntry *colorLoop;
} ParticleBehavior;

/* Size: 0x20 bytes */
typedef struct ParticleEmitter {
    /* 0x00 */ ParticleBehavior *behaviour;
    /* 0x04 */ s16 flags;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 lifeTime;
    /* 0x08 */ s16 propertyID;
    /* 0x0A */ s16 opacity;
    union {
    /* 0x000C */ Vec3f pos;
    /* 0x000C */ ParticleAngle angle;
    /* 0x000C */ struct PointParticle **unkC_60;
    /* 0x000C */ unk800AF29C_C_400 unkC_400;
    };
    /* 0x0018 */ Vec3s position; // Relative to parent object
    /* 0x001E */ s16 colorIndex;
} ParticleEmitter;

// TODO merge this struct with ObjectSegment
typedef struct ParticleSegment {
  /* 0x0000 */ ObjectTransform trans;
  /* 0x0018 */ s16 textureFrame;
  /* 0x001A */ s16 unk1A;
  /* 0x001C */ Vec3f velocity;
  /* 0x0028 */ f32 scaleVelocity;
  union {
      SegmentPropertiesObject object;
      SegmentPropertiesParticle particle;
      SegmentPropertiesCamera camera;
  };
  /* 0x003C */ Object *parentObj;
  /* 0x0040 */ s32 unk40;
} ParticleSegment;

typedef struct ParticleModel {
    /* 0x00 */ TextureHeader *texture;
    /* 0x04 */ s16 vertexCount;
    /* 0x06 */ s16 triangleCount;
    /* 0x08 */ Vertex *vertices;
    /* 0x0C */ Triangle *triangles;
} ParticleModel;

typedef struct Particle {
    /* 0x0000 */ ParticleSegment segment;
    union {
    /* 0x0044 */ ParticleModel *model;
    /* 0x0044 */ Sprite *sprite; // Unclear whether this is the same as unk80068514_arg4
    };
    /* 0x0048 */ s16 behaviorId;
    /* 0x004A */ s16 brightness;
    /* 0x004C */ Vec3f localPos;
    union {
    /* 0x0058 */ ParticleEmitter *lineEmitter;
    /* 0x0058 */ f32 forwardVel;
    /* 0x0058 */ f32 downAcceleration;
    /* 0x0058 */ f32 downOffset;
    /* 0x0058 */ f32 movementParam;
    };
    /* 0x005C */ s16 opacity;
    /* 0x005E */ s16 opacityVel;
    /* 0x0060 */ s16 opacityTimer;
    /* 0x0062 */ Vec3s angularVelocity;
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
} Particle;

typedef struct PointParticle {
    /* 0x0000 */ Particle base;
    /* 0x0070 */ ParticleEmitter *pointEmitter;
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 modelFrame;
    /* 0x0076 */ u8 unk76;
    /* 0x0077 */ s8 unk77;
} PointParticle;

void func_800AE270(void);
void func_800AE2A0(void);
void func_800AE2D8(void);
void free_particle_buffers(void);
void free_particle_vertices_triangles(void);
void free_particle_assets(void);
void generate_particle_shape_triangle(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void generate_particle_shape_quad(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void generate_particle_shape_line(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void generate_particle_shape_point(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void func_800AF0A4(Particle *particle);
void func_800AF0F0(Particle *particle);
void emitter_init(ParticleEmitter *emitter, s32 behaviourID, s32 propertyID);
void emitter_init_with_pos(ParticleEmitter *emitter, s32 behaviourID, s32 propertyID, s16 posX, s16 posY, s16 posZ);
void func_800AF6E4(Object *obj, s32 emitterIndex);
void emitter_cleanup(ParticleEmitter *emitter);
void func_800B263C(PointParticle *arg0);
void init_particle_assets(void);
void set_particle_texture_frame(Particle *particle);
void setup_particle_position(Particle *particle, Object *arg1, ParticleEmitter *arg2, ParticleBehavior *behaviour);
void particle_deallocate(Particle *particle);
void handle_particle_movement(Particle *particle, s32 updateRate);
void setup_particle_velocity(Particle *particle, Object *obj, ParticleEmitter *emitter, ParticleBehavior *behavior);
PointParticle *init_point_particle(Object *obj, ParticleEmitter *emitter);
Particle *particle_allocate(s32 kind);
void func_800AFE5C(Object *arg0, ParticleEmitter *emitter);
Particle *init_general_particle(Object *arg0, ParticleEmitter *arg1);
void func_800AF52C(Object *obj, s32 emitterIndex);
void emitter_change_settings(ParticleEmitter *emitter, s32 behaviourID, s32 propertyID, s16 velX, s16 velY, s16 velZ);
void render_particle(Particle *particle, Gfx **dList, MatrixS **mtx, Vertex **vtx, s32 flags);
void func_800B4668(Object *obj, s32 idx, s32 arg2, s32 arg3);
void func_800B46BC(Object *obj, s32 idx, s32 arg2, s32 arg3);
void obj_spawn_particle(Object *obj, s32 updateRate);
void func_800B3E64(PointParticle *particle);
void move_line_particle(Particle *particle);
void func_800AF714(Object *racerObj, s32 updateRate);
Particle* init_line_particle(Object* arg0, ParticleEmitter* arg1);

void func_800AF404(s32 updateRate); // Non Matching
void init_particle_buffers(s32 maxTriangleParticles, s32 maxRectangleParticles, s32 maxSpriteParticles,
                           s32 maxLineParticles, s32 maxPointParticles, s32 arg5); // Non Matching
void move_particle_basic_parent(Particle *);
void move_particle_velocity_parent(Particle *);
void move_particle_with_acceleration(Particle *);
void move_particle_basic(Particle *);
void move_particle_with_velocity(Particle *);

#endif
