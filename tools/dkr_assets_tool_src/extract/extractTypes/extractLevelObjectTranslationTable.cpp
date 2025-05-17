#include "extractLevelObjectTranslationTable.h"

#include <string>

// Defines LOTT_ENTRY and LOTT_SIZE
#include "fileTypes/levelObjectTranslationTable.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/assetsHelper.h"

#include "extract/stats.h"

using namespace DkrAssetsTool;

void ExtractLOTT::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Level Object Translation Table", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    const ExtractStats &stats = info.get_stats();
    
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_string("/type", "LevelObjectTranslationTable");
    
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
    // Make sure the table bytes are formatted correctly.
    DebugHelper::assert(
        (rawBytes.size() / sizeof(LOTT_ENTRY)) == LOTT_SIZE, 
        "(ExtractLOTT::extract) LevelObjectTranslationTable data has an invalid size",
        ". Raw binary size = ", rawBytes.size(), 
        ", Entry size = ", sizeof(LOTT_ENTRY), 
        ", Table size = ", LOTT_SIZE
    );
    
    // Convert the raw bytes into an array of entries.
    LOTT_ENTRY *objectIndices = reinterpret_cast<LOTT_ENTRY *>(&rawBytes[0]);
    
    // This just shortens the table so that new entries can be merged in. (NULLs will be filled when built)
    size_t lastEntry = LOTT_SIZE;
    while((lastEntry > 0) && (objectIndices[lastEntry - 1] == LOTT_SIZE)) {
        lastEntry--;
    }
    
    for(size_t i = 0; i < lastEntry; i++) {
        LOTT_ENTRY entry = objectIndices[i];
        if(entry == LOTT_SIZE) { // Check if the entry is empty, and set it to null if so.
            jsonFile.set_null("/table/" + std::to_string(i));
            continue;
        }
        std::string objectBuildId = stats.get_build_id_from_file_index("ASSET_OBJECTS", entry);
        jsonFile.set_string("/table/" + std::to_string(i), objectBuildId);
    }
    
    info.write_json_file();
}
