#pragma once

#include <string>
#include "extract/extractInfo.h"
#include "misc/settings.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

namespace DkrAssetsTool {

class ExtractBinary {
public:
    ExtractBinary(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractBinary();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
    
    void _extract_as_asset();
    void _extract_as_code();
};
}