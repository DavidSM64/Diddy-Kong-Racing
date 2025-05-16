#include "buildMisc.h"

using namespace DkrAssetsTool;

#include "fileTypes/misc.hpp"

#include "helpers/dataHelper.h"
#include "helpers/assetsHelper.h"
#include "helpers/miscHelper.h"
#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/c/cContext.h"

#include <functional>
#include <unordered_map>
#include <cstring> // for std::strcpy & std::memset

#define MISC_ARGS BuildInfo &info_, const JsonFile &jsonFile_
#define MISC_LAMDA(func) [](MISC_ARGS) { func(info_, jsonFile_); }

typedef void (*MiscFuncPtr)(MISC_ARGS);

void build_binary(BuildInfo &info, const JsonFile &jsonFile) {
    std::string rawPath = jsonFile.get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(build_binary) \"raw\" not specified!");
    
    fs::path dir = info.get_path_to_directory();
    
    if(info.build_to_file()) {
        // Copy file from rawPath to destination path.
        info.copy_to_dstPath(dir / rawPath);
    } else {
        // Load raw binary into info's out
        info.out = FileHelper::read_binary_file(dir / rawPath);
    }
}

void build_racer_stat(BuildInfo &info, const JsonFile &jsonFile) {
    if(info.build_to_file()) {
        // Make sure the enums in "/include/enums.h" are loaded.
        info.load_enums_into_c_context({ "enums.h" });
    }
    
    CContext &cContext = info.get_c_context();
    
    CEnum *characters = cContext.get_enum("Character");
    
    int numberOfCharacters;

    if(!characters->get_value_of_member("NUMBER_OF_CHARACTERS", numberOfCharacters)) {
        // Fallback to get_member_count if "NUMBER_OF_CHARACTERS" is not specified.
        numberOfCharacters = characters->get_member_count();
    }
    
    size_t outDataSize = sizeof(be_float) * numberOfCharacters;
    
    info.out.resize(outDataSize);
    
    be_float *values = reinterpret_cast<be_float *>(&info.out[0]);
    
    for(int i = 0; i < numberOfCharacters; i++) {
        std::string charId;
        if(!characters->get_symbol_of_value(i, charId)) {
            values[i] = -1; // Could not get symbol for character, so set it to -1 to indicate so.
            continue;
        }
        values[i] = jsonFile.get_float("/values/" + charId);
    }
}

void build_racer_acceleration(BuildInfo &info, const JsonFile &jsonFile) {
    size_t numberOfValues = jsonFile.length_of_array("/values");
    
    size_t outDataSize = sizeof(be_float) * numberOfValues;
    outDataSize = DataHelper::align8(outDataSize); // Make sure the data is 16-byte aligned.
    
    info.out.resize(outDataSize);
    
    be_float *values = reinterpret_cast<be_float *>(&info.out[0]);
    
    for(size_t i = 0; i < numberOfValues; i++) {
        values[i] = jsonFile.get_float("/values/" + std::to_string(i));
    }
}

void build_track_ids(BuildInfo &info, const JsonFile &jsonFile) {
    size_t numberOfIds = jsonFile.length_of_array("/ids");
    size_t outDataSize = DataHelper::align4(numberOfIds);
    info.out.resize(outDataSize);
    
    for(size_t i = 0; i < numberOfIds; i++) {
        std::string ptr = "/ids/" + std::to_string(i);
        if(jsonFile.is_value_null(ptr)) {
             info.out[i] = 0xFF; // Marks the end of the list for some files.
             continue;
        }
        std::string levelBuildId = jsonFile.get_string(ptr);
        info.out[i] = AssetsHelper::get_asset_index("ASSET_LEVEL_HEADERS", levelBuildId);
    }
}

void build_magic_codes(BuildInfo &info, const JsonFile &jsonFile) {
    size_t numberOfCheats = jsonFile.length_of_array("/cheats");
    
    // The first two bytes are the total number of cheats
    size_t outDataSize = sizeof(be_int16_t);
    
    // Then comes the lookup table.
    outDataSize += (numberOfCheats) * sizeof(be_int16_t) * 2;
    
    size_t offsetToText = outDataSize;
    
    // First loop to figure out the total size and offsets.
    for(size_t i = 0; i < numberOfCheats; i++) {
        std::string cheatPtr = "/cheats/" + std::to_string(i);
        
        // +1 for null terminator
        size_t codeLen = jsonFile.length_of_string(cheatPtr + "/code") + 1;
        size_t descLen = jsonFile.length_of_string(cheatPtr + "/description") + 1;
        
        outDataSize += codeLen + descLen;
    }
    
    // Make sure cheats data is 16-byte aligned.
    outDataSize = DataHelper::align16(outDataSize);
    
    info.out.resize(outDataSize);
    
    be_int16_t *cheatsTable = reinterpret_cast<be_int16_t *>(&info.out[0]);
    
    // Set number of cheats.
    cheatsTable[0] = numberOfCheats;
    
    CheatsTableEntry *entries = reinterpret_cast<CheatsTableEntry *>(&cheatsTable[1]);
    
    // Second loop to write the data for each cheat entry.
    for(size_t i = 0; i < numberOfCheats; i++) {
        std::string cheatPtr = "/cheats/" + std::to_string(i);
        std::string code = jsonFile.get_string(cheatPtr + "/code");
        std::string description = jsonFile.get_string(cheatPtr + "/description");
        
        entries[i].codeOffset = offsetToText;
        offsetToText += code.size() + 1; // +1 for null terminator
        entries[i].descOffset = offsetToText;
        offsetToText += description.size() + 1; // +1 for null terminator
        
        char *codeOut = reinterpret_cast<char *>(&info.out[entries[i].codeOffset]);
        char *descriptionOut = reinterpret_cast<char *>(&info.out[entries[i].descOffset]);
        
        // Copy strings to info.out.
        std::strcpy(codeOut, code.c_str());
        std::strcpy(descriptionOut, description.c_str());
    }
    
    /*
    if(_settings.debugBuildKeepUncompressed) {
        fs::path unencryptedCheatsPath = _settings.pathToBuild / "debug/cheats" / info.dstPath.filename();
        FileHelper::write_binary_file(info.out, outDataSize, unencryptedCheatsPath, true);
    }
    */
    
    MiscHelper::process_cheats_encryption(info.out.data(), outDataSize); // Encrypt the cheats data.
}

void build_title_screen_demos(BuildInfo &info, const JsonFile &jsonFile) {
    size_t numberOfEntries = jsonFile.length_of_array("/entries");
    
    size_t entriesSize = ((numberOfEntries + 1) * 3);
    size_t outDataSize = DataHelper::align8(entriesSize);
    
    info.out.resize(outDataSize);
    
    TitleScreenDemos *demos = reinterpret_cast<TitleScreenDemos *>(&info.out[0]);
    
    for(size_t i = 0; i < numberOfEntries; i++) {
        std::string ptr = "/entries/" + std::to_string(i);
        std::string levelBuildId = jsonFile.get_string(ptr + "/level");
        demos[i].levelId = AssetsHelper::get_asset_index("ASSET_LEVEL_HEADERS", levelBuildId);
        
        // Different default values for the title screen.
        int defaultNumberOfPlayers = 0;
        int defaultCutsceneId = 0;
        if(levelBuildId != "ASSET_LEVEL_TITLESCREENSEQUENCE") {
            defaultNumberOfPlayers = -2;
            defaultCutsceneId = 100;
        }
        demos[i].numberOfPlayers = jsonFile.get_int(ptr + "/number-of-players", defaultNumberOfPlayers);
        demos[i].cutsceneId = jsonFile.get_int(ptr + "/cutscene-id", defaultCutsceneId);
    }
    demos[numberOfEntries].levelId = 0xFF; // Mark end of data with 0xFF.
}

void BuildMisc::build(BuildInfo &info) {
    const JsonFile &jsonFile = info.get_src_json_file();
    std::string miscType = jsonFile.get_string("/misc-type");
    
    const std::unordered_map<std::string, std::function<void(MISC_ARGS)>> miscFunctions = {
        {            "Binary", MISC_LAMDA(build_binary)             },
        {         "RacerStat", MISC_LAMDA(build_racer_stat)         },
        { "RacerAcceleration", MISC_LAMDA(build_racer_acceleration) },
        {          "TrackIds", MISC_LAMDA(build_track_ids)          },
        {        "MagicCodes", MISC_LAMDA(build_magic_codes)        },
        {  "TitleScreenDemos", MISC_LAMDA(build_title_screen_demos) },
    };
    
    miscFunctions.at(miscType)(info, jsonFile);
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}
