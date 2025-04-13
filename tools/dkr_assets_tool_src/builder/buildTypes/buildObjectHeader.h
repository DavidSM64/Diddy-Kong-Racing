#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/c/cContext.h"

namespace DkrAssetsTool {
class BuildObjectHeader {
public:
    BuildObjectHeader(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildObjectHeader();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
    CContext _c_context;
    
    be_uint16_t _string_to_flags();
    void _preload_c_context();
};
}