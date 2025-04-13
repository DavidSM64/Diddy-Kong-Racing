#pragma once

#include <vector>

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

namespace DkrAssetsTool {
class BuildMenuText {
public:
    BuildMenuText(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildMenuText();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
    
    size_t _get_total_string_lengths(std::vector<std::string> &menuTextOrder);
};
}