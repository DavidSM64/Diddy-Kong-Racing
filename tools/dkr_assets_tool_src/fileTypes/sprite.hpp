#pragma once

#include "types.hpp"

// Size: 12 bytes.
struct SpriteHeader {
    be_int16_t startTextureIndex;
    be_int16_t numberOfFrames;
    be_int16_t unk4;
    be_int16_t unk6;
    be_int32_t unk8; // Set in-game, always zero in ROM.
    //uint8_t data[1]; // Dynamic size, based on numberOfFrames.
};
