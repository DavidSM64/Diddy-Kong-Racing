#include "extractMisc.h"

#include "fileTypes/misc.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/assetsHelper.h"
#include "helpers/miscHelper.h"

#include <unordered_map>
#include <functional>
#include <string>

#define MISC_ARGS ExtractInfo &info
#define MISC_LAMDA(func) [](MISC_ARGS) { func(info); }

using namespace DkrAssetsTool;

typedef void (*MiscFuncPtr)(MISC_ARGS);

void extract_binary(ExtractInfo &info) {
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_string("/raw", info.get_filename(".bin"));
    info.write_raw_data_file();
}

void extract_racer_stat(ExtractInfo &info) {
    WritableJsonFile &jsonFile = info.get_json_file();
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
    const int racerStatFloatRound = 2; // Round float to 2 decimal places.
    
    be_float *values = reinterpret_cast<be_float *>(&rawBytes[0]);
    CEnum *characters = info.get_c_context().get_enum("Character");
    
    size_t numberOfFloats = rawBytes.size() / 4;
    for(size_t i = 0; i < numberOfFloats; i++) {
        std::string charId; 
        DebugHelper::assert(characters->get_symbol_of_value(i, charId), 
            "(extract_racer_stat) Enum \"Character\" does not have the index: ", i);
        jsonFile.set_float("/values/" + charId, values[i], racerStatFloatRound);
    }
}

void extract_racer_acceleration(ExtractInfo &info) {
    WritableJsonFile &jsonFile = info.get_json_file();
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
    const int racerAccelFloatRound = 2; // Round float to 2 decimal places.
    
    be_float *floats = reinterpret_cast<be_float *>(&rawBytes[0]);
    
    size_t numFloats = rawBytes.size() / 4;
    
    for(size_t i = 0; i < numFloats; i++) {
        if(i > 0 && floats[i] == 0.0f) { // The zero is most likely padding.
            break;
        }
        std::string ptr = "/values/" + std::to_string(i);
        jsonFile.set_float(ptr, floats[i], racerAccelFloatRound);
    }
}

void extract_track_ids(ExtractInfo &info) {
    WritableJsonFile &jsonFile = info.get_json_file();
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
    size_t endPoint = rawBytes.size();
    
    // Get last non-zero value as the real end point. (Avoid padding)
    while(endPoint > 0 && rawBytes[endPoint - 1] == 0) {
        endPoint--;
    }
    
    for(size_t i = 0; i < endPoint; i++) {
        std::string ptr = "/ids/" + std::to_string(i);
        
        if(rawBytes[i] == 0xFF) { // 0xFF is the end of an id list.
            jsonFile.set_null(ptr);
            continue;
        }
        
        std::string levelBuildId = AssetsHelper::get_build_id_of_index("ASSET_LEVEL_HEADERS", rawBytes[i]);
        jsonFile.set_string(ptr, levelBuildId);
    }
}

void extract_magic_codes(ExtractInfo &info) {
    WritableJsonFile &jsonFile = info.get_json_file();
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
    MiscHelper::process_cheats_encryption(rawBytes); // Decrypt the cheats data.
    
    be_int16_t *cheatsTable = reinterpret_cast<be_int16_t *>(&rawBytes[0]);
    
    size_t numberOfCheats = cheatsTable[0];
    
    CheatsTableEntry *entries = reinterpret_cast<CheatsTableEntry *>(&cheatsTable[1]);
    
    std::string ptr = "/cheats";
    
    for(size_t i = 0; i < numberOfCheats; i++) {
        std::string cheatPtr = ptr + "/" + std::to_string(i);
        
        char *code = reinterpret_cast<char *>(&rawBytes[entries[i].codeOffset]);
        char *description = reinterpret_cast<char *>(&rawBytes[entries[i].descOffset]);
        
        jsonFile.set_string(cheatPtr + "/code", code);
        jsonFile.set_string(cheatPtr + "/description", description);
    }
    
}

void extract_title_screen_demos(ExtractInfo &info) {
    WritableJsonFile &jsonFile = info.get_json_file();
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
    TitleScreenDemos *demos = reinterpret_cast<TitleScreenDemos *>(&rawBytes[0]);
    
    size_t numberOfDemos = rawBytes.size() / 3;
    
    for(size_t i = 0; i < numberOfDemos; i++) {
        if(demos[i].levelId == -1) {
            break;
        }
        
        std::string ptr = "/entries/" + std::to_string(i);
        
        std::string levelBuildId = AssetsHelper::get_build_id_of_index("ASSET_LEVEL_HEADERS", demos[i].levelId);
        
        jsonFile.set_string(ptr + "/level", levelBuildId);
        
        // Different default values for the title screen.
        if(levelBuildId == "ASSET_LEVEL_TITLESCREENSEQUENCE") {
            jsonFile.set_int_if_not_zero(ptr + "/number-of-players", demos[i].numberOfPlayers);
            jsonFile.set_int_if_not_zero(ptr + "/cutscene-id", demos[i].cutsceneId);
        } else {
            jsonFile.set_int_if_not_value(ptr + "/number-of-players", demos[i].numberOfPlayers, -2);
            jsonFile.set_int_if_not_value(ptr + "/cutscene-id", demos[i].cutsceneId, 100);
        }
    }
}

void ExtractMisc::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Miscellaneous", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    std::string miscType = info.get_tag<std::string>("miscType", "Binary");
    
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_string("/type", "Miscellaneous");
    jsonFile.set_string("/misc-type", miscType);
    
    const std::unordered_map<std::string, std::function<void(MISC_ARGS)>> miscFunctions = {
        {            "Binary", MISC_LAMDA(extract_binary)             },
        {         "RacerStat", MISC_LAMDA(extract_racer_stat)         },
        { "RacerAcceleration", MISC_LAMDA(extract_racer_acceleration) },
        {          "TrackIds", MISC_LAMDA(extract_track_ids)          },
        {        "MagicCodes", MISC_LAMDA(extract_magic_codes)        },
        {  "TitleScreenDemos", MISC_LAMDA(extract_title_screen_demos) },
    };
    
    // Make sure the misc type has a function to extract it.
    DebugHelper::assert(miscFunctions.find(miscType) != miscFunctions.end(), 
        "(ExtractMisc::ExtractMisc) Misc type \"", miscType, " has extract function associated with it.");
    
    // Call the specific _extract_* function based on misc type.
    miscFunctions.at(miscType)(info);
    
    info.write_json_file();
}
