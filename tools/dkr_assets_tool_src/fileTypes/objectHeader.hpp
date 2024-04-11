#pragma once

#include <string>
#include <unordered_map>

#include "libs/bimap.hpp"

#include "types.hpp"

enum ObjectModelType {
    OBJECT_MODEL_TYPE_3D_MODEL,
    OBJECT_MODEL_TYPE_SPRITE_BILLBOARD,
    OBJECT_MODEL_TYPE_VEHICLE_PART,
    OBJECT_MODEL_TYPE_UNKNOWN3,
    OBJECT_MODEL_TYPE_MISC
};

// TODO: Figure out object header flags.
// bimap is useful here since the keys and values are 1 to 1.
const stde::bimap<std::string, int> OBJECT_HEADER_FLAGS = {
};

struct ObjectHeaderParticleData {
    struct bytes {
        uint8_t b0;
        uint8_t b1;
    };
    
    struct shorts {
        union {
            be_int16_t s0_s;
            bytes s0_b;
        };
        union {
            be_int16_t s1_s;
            bytes s1_b;
        };
    };
    
    union {
        be_int32_t upper;
        shorts upper_w;
    };
    
    union {
        be_int32_t lower;
        shorts lower_w;
    };
};

typedef struct ObjectHeader {
  /* 0x00 */ be_int32_t unk0; // The one use I've seen for this so far is water effect animation speed.
  /* 0x04 */ be_float shadowScale;
  /* 0x08 */ be_float unk8;
  /* 0x0C */ be_float scale;
  /* 0x10 */ be_int32_t modelIds;
  /* 0x14 */ be_int32_t vehiclePartIds;
  /* 0x18 */ be_int32_t vehiclePartIndices;
  /* 0x1C */ be_int32_t objectParticles;
             be_int32_t unk20;
  /* 0x24 */ be_int32_t unk24; // Lights
  /* 0x28 */ be_float shadeBrightness;
  /* 0x2C */ be_float shadeAmbient;
  /* 0x30 */ be_uint16_t flags;
  /* 0x32 */ be_int16_t shadowGroup;
  /* 0x34 */ be_int16_t unk34;
  /* 0x36 */ be_int16_t waterEffectGroup;
  /* 0x38 */ be_int16_t unk38;
  /* 0x3A */ uint8_t unk3A;
  /* 0x3B */ uint8_t unk3B;
  /* 0x3C */ uint8_t unk3C;
  /* 0x3D */ uint8_t unk3D;
  /* 0x3E */ be_int16_t shadeAngleY;
  /* 0x40 */ be_int16_t shadeAngleZ;
  /* 0x42 */ be_int16_t unk42;
  /* 0x44 */ be_int16_t unk44;
  /* 0x48 */ be_int16_t unk46;
  /* 0x48 */ be_int16_t unk48;
  /* 0x4A */ be_int16_t unk4A;
  /* 0x4C */ be_int16_t unk4C;
  /* 0x4E */ be_int16_t drawDistance;
  /* 0x50 */ be_int16_t unk50;
  /* 0x52 */ int8_t unk52; // Number of instances?
  /* 0x53 */ int8_t modelType;
  /* 0x54 */ int8_t behaviorId;
  /* 0x55 */ int8_t numberOfModelIds; // size of array pointed by Object->unk68
  /* 0x56 */ int8_t numberOfVehicleParts; // vehiclePartIds count
  /* 0x57 */ int8_t numberOfParticles; // Particle count?
  /* 0x58 */ int8_t unk58; // Index of some kind? 
  /* 0x59 */ uint8_t unk59;
  /* 0x5A */ int8_t numLightSources;
  /* 0x5B */ uint8_t unk5B; // Sound related?
  /* 0x5C */ uint8_t unk5C;
  /* 0x5D */ uint8_t unk5D; //Misc Asset index?
  /* 0x5E */ uint8_t unk5E;
  /* 0x5F */ uint8_t unk5F;
  /* 0x60 */ char internalName[16];
  /* 0x70 */ uint8_t unk70;
  /* 0x71 */ uint8_t unk71;
  /* 0x72 */ uint8_t unk72;
  /* 0x73 */ uint8_t unk73;
  /* 0x74 */ uint8_t unk74;
  /* 0x75 */ uint8_t unk75;
  /* 0x76 */ uint8_t unk76;
  /* 0x77 */ uint8_t unk77;
} ObjectHeader;