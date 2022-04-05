#pragma once

#include "../../common/util.h"
#include "../../common/textures.h"

class BuildTexture {
public:
    BuildTexture(std::string srcPath, std::string dstPath);
    ~BuildTexture();
private:
    void write_texture_data(std::vector<uint8_t> &out, int outOffset, std::vector<uint8_t> &rgbaData, 
        int width, int height, int format, bool interlace, bool flipTexture);
};
