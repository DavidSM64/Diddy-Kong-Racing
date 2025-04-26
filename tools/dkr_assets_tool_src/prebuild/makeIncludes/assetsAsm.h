#pragma once

#include <string>

#include "helpers/fileHelper.h"
#include "helpers/asmHeader.h"
#include "helpers/jsonHelper.h"
#include "helpers/c/cContext.h"

namespace DkrAssetsTool {
class AssetsAsm {
public:
    AssetsAsm();
    ~AssetsAsm();
private:
    CContext _cContext;

    fs::path _outFilepath;
    fs::path _outPrefix;
    WritableAsmInclude _asm;
    
    void _write();
    void _write_asset_sections();
    void _write_asset_section(const JsonFile &mainJson, std::string &sectionId);
    
    void _write_main_table(std::vector<std::string> &mainOrder);
    
    void _write_deferred_asset(const JsonFile &mainJson, const std::string &sectionPtr);
    void _write_asset(const JsonFile &assetSectionJson);
    void _write_asset_table(const std::string &assetSectionId);
    std::string _get_ghost_level_and_vehicle(const JsonFile &ghostJson);
    void _write_deferred_asset_table(const JsonFile &mainJson, const std::string &sectionPtr, const std::string &assetSectionId);
};
}
