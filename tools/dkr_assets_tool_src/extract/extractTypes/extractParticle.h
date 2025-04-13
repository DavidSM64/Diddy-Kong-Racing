#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

namespace DkrAssetsTool {

class ExtractParticle {
public:
    ExtractParticle(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractParticle();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};

}
