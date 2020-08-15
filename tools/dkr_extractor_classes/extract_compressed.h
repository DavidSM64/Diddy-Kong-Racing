#pragma once

#include "extract.h"
#include "../dkr_decompressor_src/DKRCompression.h"

class ExtractCompressed : Extract {
public:
    ExtractCompressed(ConfigRange& range, ROM& rom, json::JSON& assetsJson, std::string outDirectory);
    ~ExtractCompressed();
};
