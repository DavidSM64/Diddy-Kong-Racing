#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/misc.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/miscHelper.h"
#include "helpers/c/cContext.h"

class BuildMisc {
public:
    BuildMisc(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildMisc();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
    CContext _c_context;
    
    uint8_t *_build_binary(BuildInfo &info, size_t &outDataSize);
    uint8_t *_build_racer_stat(BuildInfo &info, size_t &outDataSize);
    uint8_t *_build_racer_acceleration(BuildInfo &info, size_t &outDataSize);
    uint8_t *_build_track_ids(BuildInfo &info, size_t &outDataSize);
    uint8_t *_build_magic_codes(BuildInfo &info, size_t &outDataSize);
    uint8_t *_build_title_screen_demos(BuildInfo &info, size_t &outDataSize);
    uint8_t *_build_boss_data(BuildInfo &info, size_t &outDataSize);

    void _preload_c_context(); // For enums
};
