#pragma once

#include "extract.h"

class ExtractBinary : Extract {
public:
    ExtractBinary(ConfigRange& range, ROM& rom, json::JSON& assetsJson, std::string outDirectory);
    ~ExtractBinary();
};
