#pragma once

#include <string>
#include "extract/extractInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/types.hpp"

namespace DkrAssetsTool {

class ExtractObjectHeader {
public:
    ExtractObjectHeader(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractObjectHeader();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
    
    void _flags_to_string(WritableJsonFile &jsonFile, be_uint16_t flags);
};

}
