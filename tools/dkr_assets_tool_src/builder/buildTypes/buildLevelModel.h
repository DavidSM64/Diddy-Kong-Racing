#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

namespace DkrAssetsTool {
class BuildLevelModel {
public:
    BuildLevelModel(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildLevelModel();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
};
}