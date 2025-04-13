#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

namespace DkrAssetsTool {

class ExtractSprite {
public:
    ExtractSprite(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractSprite();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
}
