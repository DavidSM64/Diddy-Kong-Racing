#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

class BuildAudio {
public:
    BuildAudio(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildAudio();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
};
