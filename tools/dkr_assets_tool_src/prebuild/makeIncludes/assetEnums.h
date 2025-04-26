#pragma once

#include <string>
#include <vector>

#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/c/cHeader.h"

namespace DkrAssetsTool {
class AssetEnums {
public:
    AssetEnums();
    ~AssetEnums();
private:
    WritableCHeader _cHeader;
    fs::path _outFilepath;
    
    void _write_asset_section_enums();
    void _write_main_asset_enum(std::vector<std::string> &mainOrder);
    void _write_single_asset_section_enums(const std::string &sectionId, const JsonFile &sectionJson);
    void _write_asset_section_enums(const std::string &sectionId, const JsonFile &sectionJson);
    
    void _write_deferred_asset_section_enums(const std::string &sectionId, const JsonFile &mainJson, 
        const std::string &deferInfoPtr);
};
}
