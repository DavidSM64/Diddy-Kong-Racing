#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

namespace DkrAssetsTool {
class BuildTexture {
public:
    BuildTexture(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildTexture();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
    
    size_t _calculate_out_size();
};
}
