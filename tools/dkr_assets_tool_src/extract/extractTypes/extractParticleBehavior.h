#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

namespace DkrAssetsTool {

class ExtractParticleBehavior {
public:
    ExtractParticleBehavior(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractParticleBehavior();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
}