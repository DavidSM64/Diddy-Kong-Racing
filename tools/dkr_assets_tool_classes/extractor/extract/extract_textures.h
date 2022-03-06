#pragma once

#include "extract.h"
#include "../../common/textures.h"

class ExtractTextures : Extract {
public:
    ExtractTextures(std::string key, std::vector<uint8_t> data, std::string outFilepath,
        std::unordered_map<std::string, std::string> *tags);
    ~ExtractTextures();
private:
    void write_images(std::string outImagePath, std::vector<uint8_t> &data, json::JSON &out);
};
