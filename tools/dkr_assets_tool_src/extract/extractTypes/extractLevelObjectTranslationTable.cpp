#include "extractLevelObjectTranslationTable.h"

#include <string>

// Defines LOTT_ENTRY and LOTT_SIZE
#include "fileTypes/levelObjectTranslationTable.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/assetsHelper.h"

ExtractLOTT::ExtractLOTT(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Level Object Translation Table", YELLOW_TEXT, _outFilepath);
    
    WritableJsonFile jsonFile(_outFilepath);
    jsonFile.set_string("/type", "LevelObjectTranslationTable");
    
    std::vector<uint8_t> rawBytes;
    _info.get_data_from_rom(rawBytes);
    
    // Make sure the table bytes are formatted correctly.
    DebugHelper::assert(
        (rawBytes.size() / sizeof(LOTT_ENTRY)) == LOTT_SIZE, 
        "(ExtractLOTT::ExtractLOTT) LevelObjectTranslationTable data has an invalid size",
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
        std::string objectBuildId = AssetsHelper::get_build_id_of_index(_settings, "ASSET_OBJECTS", entry);
        jsonFile.set_string("/table/" + std::to_string(i), objectBuildId);
    }
    
    jsonFile.save();
}

ExtractLOTT::~ExtractLOTT() {
}
