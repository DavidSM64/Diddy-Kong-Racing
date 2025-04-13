#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

namespace DkrAssetsTool {

class ExtractObjectModel {
public:
    ExtractObjectModel(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractObjectModel();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};

}
