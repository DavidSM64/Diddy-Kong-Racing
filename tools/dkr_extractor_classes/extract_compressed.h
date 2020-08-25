#pragma once

#include "extract.h"
#include "../dkr_decompressor_src/DKRCompression.h"

class ExtractCompressed : Extract {
public:
    ExtractCompressed(std::vector<uint8_t> data, ROM& rom, std::string outFilepath);
    ~ExtractCompressed();
};
