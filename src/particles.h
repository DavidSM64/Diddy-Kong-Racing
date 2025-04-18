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
    PARTICLE_RANDOM_SOURCE_ROLL = (1 << 3), // Unused
    PARTICLE_RANDOM_EMISSION_SPEED = (1 << 4),
    PARTICLE_RANDOM_EMISSION_DIR_YAW = (1 << 5),
    PARTICLE_RANDOM_EMISSION_DIR_PITCH = (1 << 6),
    PARTICLE_RANDOM_EMISSION_DIR_ROLL = (1 << 7), // Unused
    PARTICLE_RANDOM_VELOCITY_X = (1 << 8),
    PARTICLE_RANDOM_VELOCITY_Y = (1 << 9),
    PARTICLE_RANDOM_VELOCITY_Z = (1 << 10),
    PARTICLE_RANDOM_YAW = (1 << 11),
    PARTICLE_RANDOM_PITCH = (1 << 12),
    PARTICLE_RANDOM_ROLL = (1 << 13),
    PARTCILE_RANDOM_YAW_VELOCITY = (1 << 14),
    PARTCILE_RANDOM_PITCH_VELOCITY = (1 << 15),
    PARTCILE_RANDOM_ROLL_VELOCITY = (1 << 16),
    PARTICLE_RANDOM_SCALE = (1 << 17),
    PARTICLE_RANDOM_SCALE_VELOCITY = (1 << 18),
    PARTICLE_RANDOM_MOVEMENT_PARAM = (1 << 19),
    PARTICLE_RANDOM_COLOUR_RED = (1 << 20),
    PARTICLE_RANDOM_COLOUR_GREEN = (1 << 21),
    PARTICLE_RANDOM_COLOUR_BLUE = (1 << 22),
    PARTICLE_RANDOM_COLOUR_ALPHA = (1 << 23),
};

enum ParticleBehaviorFlags {
    PARTICLE_FLAGS_NONE = 0,
    PARTICLE_SOURCE_OFFSET_ENABLED = 0x1,
    PARTICLE_SOURCE_ROTATION_ENABLED = 0x2,
    PARTICLE_SOURCE_EMITS_WITH_VELOCITY = 0x4,
    PARTICLE_ROTATING_DIRECTION = 0x8,
    PARTICLE_VELOCITY_RELATIVE_TO_PARENT = 0x10,
    PARTICLE_VELOCITY_ABSOLUTE = 0x20,
    PARTICLE_VELOCITY_SCALED_FROM_PARENT = 0x40,
    PARTICLE_ROTATION_ABSOLUTE = 0x80,
    PARTICLE_BEHAVIOR_FLAG_100 = 0x100,
    PARTICLE_POINT_EMITTER_DISABLED = 0x200,
    PARTICLE_POINT = 0x400,
    PARTICLE_BEHAVIOR_FLAG_800 = 0x800,
    PARTICLE_SCALE_VELOCITY_INHERITS_PARENT_SPEED = 0x1000,
    PARTICLE_EMITTER_AWAITING_SPAWN = 0x2000,
    PARTICLE_LINE = 0x4000,
    PARTICLE_EMITTER_ENABLED = 0x8000
};

enum ParticleMovement {
    PARTICLE_MOVEMENT_NONE,
    PARTICLE_MOVEMENT_BASIC,
    PARTICLE_MOVEMENT_ACCELERATION,
    PARTICLE_MOVEMENT_ATTACHED_TO_PARENT,
    PARTICLE_MOVEMENT_BASIC_PARENT,
    PARTICLE_MOVEMENT_FORWARD,
};

enum ParticleField40 {
    PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED = 0x1,
    PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED = 0x2,
    PARTICLE_TEXTURE_ANIM_LOOP = 0x4,
    PARTICLE_CURRENT_ANIMATION_BACKWARD = 0x8,
    PARTICLE_F40_GRAVITY_1 = 0x10,
    PARTICLE_F40_GRAVITY_2 = 0x20,
    PARTICLE_F40_GRAVITY_3 = 0x40,
    PARTICLE_F40_800 = 0x800,
    PARTICLE_F40_1000 = 0x1000,
    PARTICLE_F40_2000 = 0x2000,
    PARTICLE_F40_4000 = 0x4000,
    PARTICLE_UNK_FLAG_8000 = 0x8000,
};

typedef struct ParticleDescriptor {
    /* 0x00 */ u8 kind; // ParticleKind
    /* 0x01 */ u8 movementType; // ParticleMovement
    /* 0x02 */ u16 unk2;
    /* 0x04 */ s16 textureID;
    /* 0x06 */ s16 textureFrameStep;
    /* 0x08 */ s16 lifeTime;
    union {
        /* 0x0A */ s16 lifeTimeRange; // Used by general particle
        struct {
            /* 0x0A */ u16 unkA : 6; // Used by line particle
            /* 0x0A */ u16 unkB : 6; // Used by line particle
        };
        /* 0x0A */ u16 qwe : 6; // Used by point particle
    };
    /* 0x0C */ u8 opacity;
    /* 0x0D */ u8 opacityVel;
    /* 0x0E */ s16 opacityTimer;
    /* 0x10 */ f32 scale;
    /* 0x14 */ ColourRGBA colour;
} ParticleDescriptor;

typedef struct XYStruct {
    s16 x, y;
} XYStruct;

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
    /* 0x14 */ Vec3s sourceRotation;
    /* 0x1A */ s16 maxParticlesFromSamePos;
    /* 0x1C */ Vec3s sourceAngularVelocity;
    /* 0x22 */ Vec3s emissionDirection;
    /* 0x28 */ s16 maxParticlesInSameDir;
    /* 0x22 */ Vec3s emissionDirAngularVelocity;
    /* 0x30 */ Vec3f velocityModifier; // The meaning of the modifier depends on the flags
    /* 0x3C */ f32 emissionSpeed;
    /* 0x40 */ s16 spawnInterval;
    /* 0x42 */ s16 burstCount;
    /* 0x44 */ Vec3s rotation;
    /* 0x4A */ Vec3s angularVelocity;
    /* 0x50 */ f32 scale;
    /* 0x54 */ f32 scaleVelocity;
    /* 0x58 */ f32 movementParam;

    // The following parameters are used to randomize the initial particle properties
    /* 0x5C */ s32 randomizationFlags;
    /* 0x60 */ s32 sourceDistanceRange;
    /* 0x64 */ Vec3s sourceDirRange;
    /* 0x6A */ Vec3s emissionDirRange;
    /* 0x70 */ s32 emissionSpeedRange;
    /* 0x74 */ Vec3i velocityModifierRange;
    /* 0x80 */ Vec3s rotationRange;
    /* 0x86 */ Vec3s angularVelocityRange;
    /* 0x8C */ s32 scaleRange;
    /* 0x90 */ s32 scaleVelocityRange;
    s32 movementParamRange;
    u8 colourRangeR;
    u8 colourRangeG;
    u8 colourRangeB;
    u8 colourRangeA;
    ColorLoopEntry *colorLoop;
} ParticleBehavior;

typedef struct unk800AF29C_C_400 {
    struct PointParticle **refPoints;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} unk800AF29C_C_400;

/* Size: 0x20 bytes */
typedef struct ParticleEmitter {
    /* 0x00 */ ParticleBehavior *behaviour;
    /* 0x04 */ s16 flags;
    union {
    /* 0x06 */ u8 sourceRotationCounter; // Used by general particles
    /* 0x06 */ u8 lineOpacity; // Used by line particles
    /* 0x06 */ u8 pointCount; // Used by point particles
    };
    union {
    /* 0x07 */ u8 emissionDirRotationCounter; // Used by general particles
    /* 0x07 */ u8 maxPointCount; // Used by point particles
    };
    /* 0x08 */ s16 descriptorID;
    union {
    /* 0x0A */ s16 line_unused; // Set to zero on particle spawn and neved read 
    /* 0x0A */ s16 point_opacity;
    /* 0x0A */ s16 timeFromLastSpawn; // Used by general particles
    };
    union {
    /* 0x000C */ Vec3f lineRefPoint; // Used for line particle
    /* 0x000C */ struct {
            struct PointParticle **refPoints;
            Vec2s pointSourceRotation;
            Vec2s pointEmissionDirection;
            };
    /* 0x000C */ struct {
            /* 0x000C */ Vec3s sourceRotation;
            /* 0x0012 */ Vec3s emissionDirection;
        };
    };
    /* 0x0018 */ Vec3s position; // Relative to parent object
    /* 0x001E */ s16 colorIndex;
} ParticleEmitter;

typedef struct ParticleModel {
    /* 0x00 */ TextureHeader *texture;
    /* 0x04 */ s16 vertexCount;
    /* 0x06 */ s16 triangleCount;
    /* 0x08 */ Vertex *vertices;
    /* 0x0C */ Triangle *triangles;
} ParticleModel;

typedef struct Particle {
    /* 0x0000 */ ObjectTransform trans;
    /* 0x0018 */ s16 textureFrame;
    /* 0x001A */ s16 textureFrameStep;
    /* 0x001C */ Vec3f velocity;
    /* 0x0028 */ f32 scaleVelocity;
    /* 0x002C */ s16 kind;
    /* 0x002E */ s16 segmentID;
    /* 0x0030 */ f32 unk30;
    /* 0x0034 */ f32 unk34;
    /* 0x0038 */ u8 unk38;
    /* 0x0039 */ u8 movementType;
    /* 0x003A */ s16 destroyTimer;
    /* 0x003C */ Object *parentObj;
    /* 0x0040 */ s32 miscFlags;
    union {
    /* 0x0044 */ ParticleModel *model;
    /* 0x0044 */ Sprite *sprite; // Unclear whether this is the same as unk80068514_arg4
    };
    /* 0x0048 */ s16 unk_48;
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
    /* 0x0074 */ u8 pointIndex;
    /* 0x0075 */ u8 modelFrame;
    /* 0x0076 */ u8 unk76;
    /* 0x0077 */ s8 unk77;
} PointParticle;

void reset_particles(void);
void reset_particles_with_assets(void);
void free_unknown_particle_sprites(void);
void free_particle_buffers(void);
void free_particle_vertices_triangles(void);
void free_particle_assets(void);
void init_triangle_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void init_rectangle_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void init_line_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void init_point_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void set_triangle_texture_coords(Particle *particle);
void set_rectangle_texture_coords(Particle *particle);
void emitter_init(ParticleEmitter *emitter, s32 behaviourID, s32 particleID);
void emitter_init_with_pos(ParticleEmitter *emitter, s32 behaviourID, s32 particleID, s16 posX, s16 posY, s16 posZ);
void obj_disable_emitter(Object *obj, s32 emitterIndex);
void emitter_cleanup(ParticleEmitter *emitter);
void func_800B263C(PointParticle *arg0);
void init_particle_assets(void);
void update_particle_texture_frame(Particle *particle);
void setup_particle_position(Particle *particle, Object *obj, ParticleEmitter *emitter, ParticleBehavior *behaviour);
void particle_deallocate(Particle *particle);
void particle_update(Particle *particle, s32 updateRate);
void setup_particle_velocity(Particle *particle, Object *obj, ParticleEmitter *emitter, ParticleBehavior *behavior);
PointParticle *create_point_particle(Object *obj, ParticleEmitter *emitter);
Particle *particle_allocate(s32 kind);
void obj_trigger_emitter(Object *obj, ParticleEmitter *emitter);
Particle *create_general_particle(Object *obj, ParticleEmitter *emitter);
void obj_enable_emitter(Object *obj, s32 emitterIndex);
void emitter_change_settings(ParticleEmitter *emitter, s32 behaviourID, s32 particleID, s16 posX, s16 posY, s16 posZ);
void render_particle(Particle *particle, Gfx **dList, MatrixS **mtx, Vertex **vtx, s32 flags);
void func_800B4668(Object *obj, s32 idx, s32 arg2, s32 arg3);
void func_800B46BC(Object *obj, s32 idx, s32 arg2, s32 arg3);
void obj_spawn_particle(Object *obj, s32 updateRate);
void func_800B3E64(PointParticle *obj);
void update_line_particle(Particle *particle);
void update_vehicle_particles(Object *racerObj, s32 updateRate);
Particle* create_line_particle(Object* obj, ParticleEmitter* emitter);

void scroll_particle_textures(s32 updateRate); // Non Matching
void init_particle_buffers(s32 maxTriangleParticles, s32 maxRectangleParticles, s32 maxSpriteParticles,
                           s32 maxLineParticles, s32 maxPointParticles, s32 arg5); // Non Matching
void move_particle_basic_parent(Particle *);
void move_particle_attached_to_parent(Particle *);
void move_particle_with_acceleration(Particle *);
void move_particle_basic(Particle *);
void move_particle_forward(Particle *);

#endif
