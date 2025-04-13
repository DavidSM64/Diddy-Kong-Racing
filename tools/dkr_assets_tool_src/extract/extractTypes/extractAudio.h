#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

namespace DkrAssetsTool {

class ExtractAudio {
public:
    ExtractAudio(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractAudio();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
}