#pragma once

#include <string>

#include "types.hpp"

// 0x10 bytes
struct BetaJpFontHeader {
    uint8_t unk0;      // 0x06
    uint8_t x;         // 0x0C
    uint8_t y;         // 0x0C
    uint8_t charWidth; // 0x0C
    uint8_t height;    // 0x0C
    uint8_t unk5;      // 0x0C
    be_uint16_t imgWidth; // 0x00C0 (192)
    be_uint16_t unk8;  // 0x000C
    be_uint16_t unkA;  // 0x0480
    be_uint32_t unkC;  // 0x00000000
};

// 0x10 bytes
struct JpFontHeader {
    uint8_t unk0;
    uint8_t cellWidth;
    uint8_t cellHeight;
    uint8_t charWidth;
    uint8_t height;
    uint8_t unk5;
    uint8_t unk6;
    uint8_t unk7;
    be_uint32_t offset; // Offset in the file
    be_uint32_t bytesPerCharacter; // Number of bytes per character for this font.
};

// 0x10 bytes for the header, followed by image data.
struct JpFontChar {
    be_int32_t offsetToFirstImg;  // Always 0x10 
    be_int32_t offsetToSecondImg; // Offset to second image. (-1 if no second image)
    uint8_t firstImageFormat; // For decoding use `TEXTURE_FORMAT_INT_TO_STRING` in fileTypes/texture.hpp
    uint8_t secondImageFormat;
    uint8_t left;
    uint8_t top;
    uint8_t right;
    uint8_t bottom;
    uint8_t spacing;
    uint8_t pad;
};
