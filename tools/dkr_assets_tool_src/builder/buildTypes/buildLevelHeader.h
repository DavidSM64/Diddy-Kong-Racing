#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/c/cContext.h"
#include "fileTypes/levelHeader.hpp"

class BuildLevelHeader {
public:
    BuildLevelHeader(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildLevelHeader();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
    
    CContext _c_context; // C Code context. (For loading enums & structs)

    void _build_weather(std::string ptr, LevelHeader_Weather &weather);
    void _build_ai_levels(std::string ptr, LevelHeader_AiLevels &aiLevels);
    void _build_fog(std::string ptr, LevelHeader_Fog &fogInfo);
    
    template<typename T>
    T _build_enum_bitfield(std::string ptr);

    void _build_level_name();
    
    void _preload_c_context();
};
