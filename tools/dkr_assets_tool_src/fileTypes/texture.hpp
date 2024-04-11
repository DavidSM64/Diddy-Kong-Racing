#pragma once

#include <string>
#include "types.hpp"

const std::string DEFAULT_TEXTURE_FORMAT = "RGBA16";

const double TEXTURE_FPS = 60.0;
const int TEXTURE_TIME_ROUND_PLACES = 3; // Round time floats to 3 decimal places.

const std::vector<std::string> TEXTURE_FORMAT_INT_TO_STRING = {
    "RGBA32", "RGBA16", "I8", "I4", "IA16", "IA8", "IA4", "CI4", "CI8"
};

const std::vector<std::string> TEXTURE_RENDER_MODES = {
    "TRANSPARENT", "OPAQUE", "TRANSPARENT_2", "OPAQUE_2"
};

struct TextureHeader {
  /* 0x00 */ uint8_t width;
  /* 0x01 */ uint8_t height;
  /* 0x02 */ uint8_t format; // Lower 4 bits determines image format.
      // 0 = RGBA32
      // 1 = RGBA16
      // 2 = I8
      // 3 = I4
      // 4 = IA16
      // 5 = IA8
      // 6 = IA4
      // 7 = CI4 (16 colors)
      // 8 = CI8 (64 colors)
  /* 0x03 */ int8_t spriteX;
  /* 0x04 */ int8_t spriteY;
  /* 0x05 */ uint8_t numberOfInstances; // Always 1 in the ROM.
  /* 0x06 */ be_int16_t flags;
  /* 0x08 */ be_int16_t ciPaletteOffset;
  /* 0x0A */ be_int16_t numberOfCommands; // initialized in RAM; Number of commands in the texture display list. (Usually 0x07)
  /* 0x0C */ be_int32_t cmd; // initialized in RAM; Pointer to texture display list.
  /* 0x10 */ uint8_t unk10;
  /* 0x11 */ uint8_t unk11;
  /* 0x12 */ uint8_t numOfTextures; // For animated textures, static textures are just 0x01. Each texture has it's own header.
  /* 0x13 */ uint8_t unk13;
  /* 0x14 */ be_uint16_t frameAdvanceDelay; // How many frames to delay before moving to the next texture.
  /* 0x16 */ be_int16_t textureSize; // Size in number of bytes, including the header
  /* 0x18 */ uint8_t unk18;
  /* 0x19 */ uint8_t unk19;
  /* 0x1A */ uint8_t unk1A;
  /* 0x1B */ uint8_t unk1B;
  /* 0x1C */ uint8_t unk1C;
  /* 0x1D */ uint8_t isCompressed;
  /* 0x1E */ uint8_t unk1E;
  /* 0x1F */ uint8_t unk1F;
};
