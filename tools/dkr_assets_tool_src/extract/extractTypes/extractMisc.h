#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

namespace DkrAssetsTool {

class ExtractMisc {
public:
    ExtractMisc(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractMisc();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
    
    void _extract_binary(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes);
    void _extract_racer_stat(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes);
    void _extract_racer_acceleration(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes);
    void _extract_track_ids(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes);
    void _extract_magic_codes(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes);
    void _extract_title_screen_demos(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes);
    
    std::string _miscType;
};
}