#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

class BuildBinary {
public:
    BuildBinary(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildBinary();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
};
