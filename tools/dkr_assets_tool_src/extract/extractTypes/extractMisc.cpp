#include "extractMisc.h"

#include "fileTypes/misc.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/assetsHelper.h"
#include "helpers/miscHelper.h"

#include <unordered_map>
#include <functional>
#include <string>

#define MISC_ARGS WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes
#define MISC_LAMDA(func) [this](MISC_ARGS) { func(jsonFile, rawBytes); }

typedef void (*MiscFuncPtr)(MISC_ARGS);

ExtractMisc::ExtractMisc(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Miscellaneous", YELLOW_TEXT, _outFilepath);
    
    _miscType = _info.get_tag<std::string>("miscType", "Binary");
    
    WritableJsonFile jsonFile(_outFilepath);
    jsonFile.set_string("/type", "Miscellaneous");
    jsonFile.set_string("/misc-type", _miscType);
    
    std::vector<uint8_t> rawBytes;
    _info.get_data_from_rom(rawBytes);
    
    const std::unordered_map<std::string, std::function<void(MISC_ARGS)>> miscFunctions = {
        {            "Binary", MISC_LAMDA(_extract_binary)             },
        {         "RacerStat", MISC_LAMDA(_extract_racer_stat)         },
        { "RacerAcceleration", MISC_LAMDA(_extract_racer_acceleration) },
        {          "TrackIds", MISC_LAMDA(_extract_track_ids)          },
        {        "MagicCodes", MISC_LAMDA(_extract_magic_codes)        },
        {  "TitleScreenDemos", MISC_LAMDA(_extract_title_screen_demos) },
    };
    
    // Make sure the misc type has a function to extract it.
    DebugHelper::assert(miscFunctions.find(_miscType) != miscFunctions.end(), 
        "(ExtractMisc::ExtractMisc) Misc type \"", _miscType, " has extract function associated with it.");
    
    // Call the specific _extract_* function based on misc type.
    miscFunctions.at(_miscType)(jsonFile, rawBytes);
    
    jsonFile.save();
}

ExtractMisc::~ExtractMisc() {
}

void ExtractMisc::_extract_binary(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes) {
    fs::path _outRawFilepath = _settings.pathToAssets / _info.get_out_filepath(".bin");
    jsonFile.set_string("/raw", _info.get_filename(".bin"));
    FileHelper::write_binary_file(rawBytes, _outRawFilepath, true);
}

void ExtractMisc::_extract_racer_stat(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes) {
    const int racerStatFloatRound = 2; // Round float to 2 decimal places.
    
    be_float *values = reinterpret_cast<be_float *>(&rawBytes[0]);
    CEnum *characters = _info.c_context->get_enum("Character");
    
    size_t numberOfFloats = rawBytes.size() / 4;
    for(size_t i = 0; i < numberOfFloats; i++) {
        std::string charId; 
        DebugHelper::assert(characters->get_symbol_of_value(i, charId), 
            "(ExtractMisc::_extract_racer_stat) Enum \"Character\" does not have the index: ", i);
        jsonFile.set_float("/values/" + charId, values[i], racerStatFloatRound);
    }
}

void ExtractMisc::_extract_racer_acceleration(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes) {
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

void ExtractMisc::_extract_track_ids(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes) {
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
        
        std::string levelBuildId = AssetsHelper::get_build_id_of_index(_settings, "ASSET_LEVEL_HEADERS", rawBytes[i]);
        jsonFile.set_string(ptr, levelBuildId);
    }
}

void ExtractMisc::_extract_magic_codes(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes) {
    MiscHelper::process_cheats_encryption(rawBytes); // Decrypt the cheats data.
    
    if(_settings.debugExtractKeepUncompressed) {
        fs::path unencryptedCheatsPath = _settings.pathToAssets / "debug/cheats" / _info.get_filename(".bin");
        FileHelper::write_binary_file(rawBytes, unencryptedCheatsPath, true);
    }
    
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

void ExtractMisc::_extract_title_screen_demos(WritableJsonFile &jsonFile, std::vector<uint8_t> &rawBytes) {
    TitleScreenDemos *demos = reinterpret_cast<TitleScreenDemos *>(&rawBytes[0]);
    
    size_t numberOfDemos = rawBytes.size() / 3;
    
    for(size_t i = 0; i < numberOfDemos; i++) {
        if(demos[i].levelId == -1) {
            break;
        }
        
        std::string ptr = "/entries/" + std::to_string(i);
        
        std::string levelBuildId = AssetsHelper::get_build_id_of_index(_settings, "ASSET_LEVEL_HEADERS", demos[i].levelId);
        
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
