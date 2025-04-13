#pragma once

#include <string>
#include "extract/extractInfo.h"
#include "misc/settings.hpp"

#include "helpers/imageHelper.h"

namespace DkrAssetsTool {

class ExtractTexture {
public:
    ExtractTexture(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractTexture();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
    bool _shouldFlipTexture = false;
    
   N64Image **_generate_texture_images(std::vector<uint8_t> &texData, size_t numImages);
};

}