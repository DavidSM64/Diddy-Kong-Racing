#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

class ExtractParticle {
public:
    ExtractParticle(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractParticle();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
