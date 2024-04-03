#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

class ExtractObjectModel {
public:
    ExtractObjectModel(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractObjectModel();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
