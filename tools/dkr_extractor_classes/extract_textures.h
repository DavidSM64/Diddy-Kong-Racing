#pragma once

#include "extract.h"
#include "../dkr_decompressor_src/DKRCompression.h"
#include "../n64graphics/n64graphics.h"

#define TEX_FORMAT_RGBA32 0
#define TEX_FORMAT_RGBA16 1
#define TEX_FORMAT_I8     2
#define TEX_FORMAT_I4     3
#define TEX_FORMAT_IA16   4
#define TEX_FORMAT_IA8    5
#define TEX_FORMAT_IA4    6
#define TEX_FORMAT_CI4    7

#define TEX_HEADER_SIZE 0x20

class ExtractTextures : Extract {
public:
    ExtractTextures(std::vector<uint8_t>& data, ROM& rom, std::string outFilepath);
    ~ExtractTextures();
    
private:
    void deinterlace(std::vector<uint8_t>& data, int width, int height, int bitDepth, int bufferSize);
    void process_texture(std::vector<uint8_t>& header, std::vector<uint8_t>& data);
    int get_texture_size(int width, int height, int textureFormat);
    
};
