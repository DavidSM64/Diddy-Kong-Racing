#pragma once

#include "extract/extractInfo.h"
#include "misc/settings.hpp"

class ExtractTTGhost {
public:
    ExtractTTGhost(DkrAssetsSettings &settings, ExtractInfo &info);
    ~ExtractTTGhost();
private:
    DkrAssetsSettings &_settings;
    ExtractInfo &_info;
};
