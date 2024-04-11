#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

class BuildObjectModel {
public:
    BuildObjectModel(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildObjectModel();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
};
