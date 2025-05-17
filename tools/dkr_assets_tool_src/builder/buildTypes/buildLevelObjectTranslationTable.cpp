#include "buildLevelObjectTranslationTable.h"

using namespace DkrAssetsTool;

// Defines LOTT_ENTRY and LOTT_SIZE
#include "fileTypes/levelObjectTranslationTable.hpp"

#include "helpers/assetsHelper.h"

void BuildLOTT::build(BuildInfo &info){
    info.out.resize(LOTT_SIZE * sizeof(LOTT_ENTRY));
    
    LOTT_ENTRY *entries = reinterpret_cast<LOTT_ENTRY *>(&info.out[0]);
    
    const JsonFile &jsonFile = info.get_src_json_file();
    
    size_t numberOfEntries = jsonFile.length_of_array("/table");
    
    DebugHelper::assert(numberOfEntries <= LOTT_SIZE,
        "(BuildLOTT::build) The Level-Object Translation Table has too many entries! Can only have ", LOTT_SIZE, " entries.");

    for(size_t i = 0; i < numberOfEntries; i++) {
        std::string ptr = "/table/" + std::to_string(i);
        if(jsonFile.is_value_null(ptr)) {
            entries[i] = LOTT_SIZE;
            continue;
        }
        // Not null.
        std::string entryId = jsonFile.get_string(ptr);
        if(entryId.empty()) { 
            entries[i] = LOTT_SIZE;
            continue;
        }
        
        // Not empty.
        entries[i] = AssetsHelper::get_asset_index("ASSET_OBJECTS", entryId);
    }
    
    // Fill rest of the entries as empty slots.
    for(size_t i = numberOfEntries; i < LOTT_SIZE; i++) {
        entries[i] = LOTT_SIZE;
    }
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
        
}
