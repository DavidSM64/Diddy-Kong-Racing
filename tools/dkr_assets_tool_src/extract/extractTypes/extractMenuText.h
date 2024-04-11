#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

class ExtractMenuText {
public:
    ExtractMenuText(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractMenuText();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
