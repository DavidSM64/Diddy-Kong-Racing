#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

namespace DkrAssetsTool {

class ExtractLOTT {
public:
    ExtractLOTT(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractLOTT();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
}
