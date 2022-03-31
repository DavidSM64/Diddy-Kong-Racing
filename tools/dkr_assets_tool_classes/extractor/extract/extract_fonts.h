#pragma once

#include "extract.h"

class ExtractFonts : Extract {
public:
    ExtractFonts(std::string key, std::vector<uint8_t> data, std::string outFilepath, std::string folder, json::JSON &configJSON);
    ~ExtractFonts();
};
