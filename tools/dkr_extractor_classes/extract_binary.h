#pragma once

#include "extract.h"

class ExtractBinary : Extract {
public:
    ExtractBinary(std::vector<uint8_t>& data, ROM& rom, std::string outFilepath);
    ~ExtractBinary();
};
