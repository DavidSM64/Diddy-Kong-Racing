#pragma once

#include <map>
#include <vector>
#include <iostream>

#include "misc/settings.hpp"

#include "helpers/fileHelper.h"
#include "helpers/debugHelper.h"

#include "config.h"
#include "rom.h"
#include "extractInfo.h"
#include "assetTable.h"

#include "helpers/c/cContext.h"

namespace DkrAssetsTool {

class DkrExtract {
public:
    DkrExtract(DkrAssetsSettings &settings);
    ~DkrExtract();
    
private:
    DkrExtractConfig *_config = nullptr;
    DkrExtractROM *_rom = nullptr;
    DkrAssetsSettings &_settings;
    
    // The int is the group number, need to extract different sections first before others.
    // (Example being extracting the LevelObjectTranslationTable before any LevelObjectMaps)
    // This NEEDS to be a std::map, not a std::unordered_map.
    std::map<int, std::vector<ExtractInfo>> extractions;
    
    void _find_config();
    void _find_rom(const std::string &directory, bool recursive);
    
    void _extract();
    
    void _add_new_extraction(ExtractInfo &info, int group=0);
    
    void _get_code_extractions(uint32_t &romOffset);
    void _get_asset_extractions(uint32_t &romOffset);
    
    void _get_asset_files_from_table(DkrExtractAssetSection *assetSection, int sectionOffset, int tableSectionOffset);
    
    void _get_single_asset_info(DkrExtractAssetSection *assetSection, uint32_t romOffset, size_t length);

    void _get_asset_section_file_info(DkrExtractAssetSection *assetSection, DkrExtractAssetSectionFile *sectionFile, 
        size_t fileNum, uint32_t romOffset, size_t length);
        
    void _generate_section_json_file(DkrExtractAssetSection *assetSection, AssetTable *sectionTable = nullptr);
    
    void _generate_main_json_file();
    
    void _generate_obj_behavior_to_entry_json_file();
    
    void _preload_c_context();
    
    CContext _c_context;
};

}
