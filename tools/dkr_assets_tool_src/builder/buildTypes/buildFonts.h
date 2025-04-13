#pragma once

#include "builder/buildInfo.h"
#include "misc/settings.hpp"

#include "fileTypes/fonts.hpp"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"

namespace DkrAssetsTool {
class BuildFonts {
public:
    BuildFonts(DkrAssetsSettings &settings, BuildInfo &info);
    ~BuildFonts();
private:
    DkrAssetsSettings &_settings;
    BuildInfo &_info;
    
    JsonFile *_get_font_file(fs::path &localFontPath);
    void _parse_ascii_encoding(JsonFile *fontJson, FontFile *fontFile);
};
}
