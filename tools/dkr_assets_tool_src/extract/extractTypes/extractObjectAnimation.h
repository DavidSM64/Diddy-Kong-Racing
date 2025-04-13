#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

namespace DkrAssetsTool {

class ExtractObjectAnimation {
public:
    ExtractObjectAnimation(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractObjectAnimation();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
}