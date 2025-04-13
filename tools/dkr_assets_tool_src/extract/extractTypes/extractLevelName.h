#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

namespace DkrAssetsTool {

class ExtractLevelName {
public:
    ExtractLevelName(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractLevelName();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
}