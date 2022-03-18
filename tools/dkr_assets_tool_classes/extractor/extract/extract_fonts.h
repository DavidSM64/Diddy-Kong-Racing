#pragma once

#include "extract.h"

class ExtractFonts : Extract {
public:
    ExtractFonts(std::string key, std::vector<uint8_t> data, std::string outFilepath, json::JSON &configJSON);
    ~ExtractFonts();
};
