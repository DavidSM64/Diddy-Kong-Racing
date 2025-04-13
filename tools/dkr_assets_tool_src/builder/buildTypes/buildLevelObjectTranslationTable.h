#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

namespace DkrAssetsTool {
class BuildLOTT {
public:
    BuildLOTT(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildLOTT();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
};
}
