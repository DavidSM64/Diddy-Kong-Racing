#pragma once

#include <string>
#include "extract/extractInfo.h"
#include "misc/settings.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

namespace DkrAssetsTool {

class ExtractFonts {
public:
    ExtractFonts(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractFonts();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
}