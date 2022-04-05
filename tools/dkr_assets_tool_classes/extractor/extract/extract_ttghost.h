#pragma once

#include "extract.h"

class ExtractTTGhost : Extract {
public:
    ExtractTTGhost(std::string key, std::vector<uint8_t> data, std::string outFilepath, json::JSON &configJSON);
    ~ExtractTTGhost();
};
