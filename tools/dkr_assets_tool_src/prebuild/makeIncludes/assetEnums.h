#pragma once

#include <string>
#include <vector>

#include "misc/settings.hpp"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/c/cHeader.h"

class AssetEnums {
public:
    AssetEnums(DkrAssetsSettings &settings);
    ~AssetEnums();
private:
    DkrAssetsSettings &_settings;
    WritableCHeader _cHeader;
    fs::path _outFilepath;
    
    void _write_asset_section_enums();
    void _write_main_asset_enum(std::vector<std::string> &mainOrder);
    void _write_asset_section_enums(const std::string &sectionId, JsonFile *sectionJson);
    
    void _write_deferred_asset_section_enums(const std::string &sectionId, JsonFile *mainJson, 
        const std::string &deferInfoPtr);
};