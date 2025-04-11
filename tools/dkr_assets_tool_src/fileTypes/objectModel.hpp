#pragma once

#include "types.hpp"

typedef struct ObjectModelCollisionSphere {
    be_int16_t vertexIndex; // Position of the sphere (stored in vertices)
    be_int16_t radiusScale; // Radius = ((radiusScale / 64) * objectHeaderScale) * 50.0
} ObjectModelCollisionSphere;

typedef struct ObjectModel {
    /* 0x00 */ be_int32_t textures;  // TextureInfo offset
    /* 0x04 */ be_int32_t vertices;  // Vertices offset
    /* 0x08 */ be_int32_t triangles; // Triangles offset
    /* 0x0C */ be_int32_t reservedC; // Reserved for in-game only.
    /* 0x10 */ be_int32_t reserved10; // Reserved for in-game only.
    /* 0x14 */ be_int32_t attachPoints; // (Vehicle parts, Egg) Indices positions (stored in vertices).
    /* 0x18 */ be_int16_t numberOfAttachPoints;
    /* 0x1A */ be_int16_t unk1A;
    /* 0x1C */ be_int32_t collisionSpheres; // Used in func_80016748. Data is a pair of s16 values.
    /* 0x20 */ be_int16_t collisionSpheresSize; // Should be an even number.
    /* 0x22 */ be_int16_t numberOfTextures;
    /* 0x24 */ be_int16_t numberOfVertices;
    /* 0x26 */ be_int16_t numberOfTriangles;
    /* 0x28 */ be_int16_t numberOfBatches;
    /* 0x2A */ uint8_t unk2A;
    /* 0x2B */ uint8_t unk2B;
    /* 0x2C */ be_int32_t fileSize; // Size of the model file (including the header)
    /* 0x30 */ be_int16_t reservedReferences; // Reserved for in-game only.
    /* 0x32 */ be_int16_t reserved32; // Reserved for in-game only.
    /* 0x34 */ uint8_t unk34;
    /* 0x34 */ uint8_t unk35;
    /* 0x34 */ uint8_t unk36;
    /* 0x34 */ uint8_t unk37;
    /* 0x38 */ be_int32_t batches;
    /* 0x3C */ float unk3C;
    /* 0x40 */ be_int32_t reserved40; // Reserved for in-game only.
    /* 0x44 */ be_int32_t reservedAnimations; // Reserved for in-game only.
    /* 0x48 */ be_int16_t reservedNumberOfAnimations; // Reserved for in-game only.
    /* 0x4A */ be_int16_t numberOfAnimatedVertices; // Number of animated vertices
    /* 0x4C */ be_int32_t animatedVertexIndices; // Animated vertices list.
    /* 0x50 */ be_int16_t unk50; // Update rate maybe? Only checked if greater than 0.
    /* 0x52 */ be_int16_t reserved52; // Reserved for in-game only.
    /* 0x54 */ be_int32_t unused54; // Not used?
} ObjectModel;

// First keyframe uses s16 values to offset vertices.
typedef struct ObjectModelAnimationKeyframeVertexS16 {
    be_int16_t offsetX;
    be_int16_t offsetY;
    be_int16_t offsetZ;
} ObjectModelAnimationKeyframeVertexS16;

// Following keyframes use s8 values to offset vertices.
typedef struct ObjectModelAnimationKeyframeVertexS8 {
   int8_t offsetX;
   int8_t offsetY;
   int8_t offsetZ;
} ObjectModelAnimationKeyframeVertexS8;

typedef struct ObjectModelAnimationKeyframeHeader {
    uint8_t unk0[12]; // Every keyframe has a 12-byte header. (unknown what these bytes do)
} ObjectModelAnimationKeyframeHeader;

typedef struct ObjectModelAnimationHeader {
    be_int32_t keyframeCount;
} ObjectModelAnimationHeader;