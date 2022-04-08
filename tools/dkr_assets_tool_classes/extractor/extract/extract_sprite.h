#pragma once

#include "extract.h"

class ExtractSprite : Extract {
public:
    ExtractSprite(std::string key, std::vector<uint8_t> data, std::string outFilepath, json::JSON &configJSON);
    ~ExtractSprite();
};
