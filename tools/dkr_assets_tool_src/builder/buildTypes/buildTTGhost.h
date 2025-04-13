#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/c/cContext.h"

namespace DkrAssetsTool {
class BuildTTGhost {
public:
    BuildTTGhost(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildTTGhost();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
    
    CContext _c_context; // C Code context. (For loading enums & structs)

    void _preload_c_context();
};
}