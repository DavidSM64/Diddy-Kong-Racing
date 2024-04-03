#pragma once

#include <string>

#include "types.hpp"

const int FONTS_NUMBER_OF_TEXTURE_INDICES = 32;

// Starts at ASCII index 32 and ends at 128.
const char FONTS_START_CHAR = ' ';
const int FONTS_NUMBER_OF_CHARACTERS = 96;

const fs::path FONTS_SUBDIRECTORY = "game_fonts/";

const size_t FONTS_NAME_LENGTH = 32;
const size_t FONTS_JUNKTEXT_LENGTH = 24;

// 0x8 bytes 
struct FontCharacter {
/* 0x0 */ int8_t texIndex;
/* 0x1 */ int8_t charWidth;
/* 0x2 */ int8_t offsetX;
/* 0x3 */ int8_t offsetY;
/* 0x4 */ int8_t texU;
/* 0x5 */ int8_t texV;
/* 0x6 */ int8_t texWidth;
/* 0x7 */ int8_t texHeight;
};

// 0x400 bytes
struct FontFile {
/* 0x000 */ char name[FONTS_NAME_LENGTH];
/* 0x020 */ be_int16_t fixedWidth;
/* 0x022 */ be_int16_t yOffset;
/* 0x024 */ be_int16_t specialCharacterWidth;
/* 0x026 */ be_int16_t tabWidth;
/* 0x028 */ char junkText[FONTS_JUNKTEXT_LENGTH];
/* 0x040 */ be_int16_t textureIndices[FONTS_NUMBER_OF_TEXTURE_INDICES];
/* 0x080 */ int32_t reservedForTexturePointers[FONTS_NUMBER_OF_TEXTURE_INDICES];
/* 0x100 */ FontCharacter characters[FONTS_NUMBER_OF_CHARACTERS];
};

struct FontData {
    be_uint32_t numberOfFonts;
    FontFile fonts[1]; // Dynamic number of fonts. (Based on numberOfFonts)
};
 