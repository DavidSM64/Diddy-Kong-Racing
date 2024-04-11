#include "buildLevelObjectTranslationTable.h"

// Defines LOTT_ENTRY and LOTT_SIZE
#include "fileTypes/levelObjectTranslationTable.hpp"

#include "helpers/assetsHelper.h"

BuildLOTT::BuildLOTT(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    LOTT_ENTRY entries[LOTT_SIZE];
    
    size_t numberOfEntries = _info.srcFile->length_of_array("/table");
    
    DebugHelper::assert(numberOfEntries <= LOTT_SIZE,
        "(BuildLOTT::BuildLOTT) The Level-Object Translation Table has too many entries! Can only have ", LOTT_SIZE, " entries.");

    for(size_t i = 0; i < numberOfEntries; i++) {
        std::string ptr = "/table/" + std::to_string(i);
        if(_info.srcFile->is_value_null(ptr)) {
            entries[i] = LOTT_SIZE;
            continue;
        }
        // Not null.
        std::string entryId = _info.srcFile->get_string(ptr);
        if(entryId.empty()) { 
            entries[i] = LOTT_SIZE;
            continue;
        }
        
        // Not empty.
        entries[i] = AssetsHelper::get_asset_index(_settings, "ASSET_OBJECTS", entryId);
    }
    
    // Fill rest of the entries as empty slots.
    for(size_t i = numberOfEntries; i < LOTT_SIZE; i++) {
        entries[i] = LOTT_SIZE;
    }
    
    FileHelper::write_binary_file(reinterpret_cast<uint8_t*>(entries), sizeof(LOTT_ENTRY) * LOTT_SIZE, 
        _info.dstPath, true);
}

BuildLOTT::~BuildLOTT() {
    
}

