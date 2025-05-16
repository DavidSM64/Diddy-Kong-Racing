#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

namespace DkrAssetsTool {

class ExtractLevelModel {
public:
    ExtractLevelModel(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractLevelModel();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
}