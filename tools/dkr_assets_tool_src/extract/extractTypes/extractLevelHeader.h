#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/levelHeader.hpp"

class ExtractLevelHeader {
public:
    ExtractLevelHeader(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractLevelHeader();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
    
    void _extract_weather(WritableJsonFile &jsonFile, std::string ptr, LevelHeader_Weather &weather);
    void _extract_ai_levels(WritableJsonFile &jsonFile, std::string ptr, LevelHeader_AiLevels &aiLevels);
    void _extract_fog(WritableJsonFile &jsonFile, std::string ptr, LevelHeader_Fog &fogInfo);
    void _extract_name(WritableJsonFile &jsonFile, std::string ptr);
    
    template<typename T>
    void _extract_enum_bitfield(WritableJsonFile &jsonFile, std::string ptr, std::string enumName, T value);
};
