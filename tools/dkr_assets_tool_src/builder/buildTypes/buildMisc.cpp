#include "buildMisc.h"

using namespace DkrAssetsTool;

#include "helpers/dataHelper.h"
#include "helpers/assetsHelper.h"
#include "helpers/miscHelper.h"

#include <functional>
#include <unordered_map>
#include <cstring> // for std::strcpy & std::memset

#define MISC_ARGS BuildInfo &info, size_t &outDataSize
#define MISC_LAMDA(func) [this](MISC_ARGS) { return func(info, outDataSize); }

typedef void (*MiscFuncPtr)(MISC_ARGS);

BuildMisc::BuildMisc(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    //std::string rawPath = info.srcFile->get_string("raw");
    
    std::string miscType = info.srcFile->get_string("/misc-type");
    
    const std::unordered_map<std::string, std::function<uint8_t *(MISC_ARGS)>> miscFunctions = {
        {            "Binary", MISC_LAMDA(_build_binary)             },
        {         "RacerStat", MISC_LAMDA(_build_racer_stat)         },
        { "RacerAcceleration", MISC_LAMDA(_build_racer_acceleration) },
        {          "TrackIds", MISC_LAMDA(_build_track_ids)          },
        {        "MagicCodes", MISC_LAMDA(_build_magic_codes)        },
        {  "TitleScreenDemos", MISC_LAMDA(_build_title_screen_demos) },
    };
    
    size_t outDataSize;
    uint8_t *outData = miscFunctions.at(miscType)(info, outDataSize);
    
    if(outData == nullptr) {
       return;
    }
    
    FileHelper::write_binary_file(outData, outDataSize, info.dstPath, true);
    delete outData;
}

BuildMisc::~BuildMisc() {
    
}

uint8_t *BuildMisc::_build_binary(BuildInfo &info, size_t &outDataSize) {
    std::string rawPath = info.srcFile->get_string("/raw");
    
    DebugHelper::assert(!rawPath.empty(), "(BuildMisc::_build_binary) \"raw\" not specified!");
    
    // Copy file from rawPath to destination path.
    FileHelper::copy(_info.localDirectory / rawPath, info.dstPath);
    return nullptr;
}

uint8_t *BuildMisc::_build_racer_stat(BuildInfo &info, size_t &outDataSize) {
    // Load enums
    _preload_c_context();
    
    CEnum *characters = _c_context.get_enum("Character");
    
    int numberOfCharacters;

    if(!characters->get_value_of_member("NUMBER_OF_CHARACTERS", numberOfCharacters)) {
        // Fallback to get_member_count if "NUMBER_OF_CHARACTERS" is not specified.
        numberOfCharacters = characters->get_member_count();
    }
    
    outDataSize = sizeof(be_float) * numberOfCharacters;
    uint8_t *out = new uint8_t[outDataSize];
    std::memset(out, 0, outDataSize); // zero out memory.
    be_float *values = reinterpret_cast<be_float *>(out);
    
    for(int i = 0; i < numberOfCharacters; i++) {
        std::string charId;
        if(!characters->get_symbol_of_value(i, charId)) {
            values[i] = -1; // Could not get symbol for character, so set it to -1 to indicate so.
            continue;
        }
        values[i] = info.srcFile->get_float("/values/" + charId);
    }
    
    return out;
}

uint8_t *BuildMisc::_build_racer_acceleration(BuildInfo &info, size_t &outDataSize) {
    size_t numberOfValues = _info.srcFile->length_of_array("/values");
    
    outDataSize = sizeof(be_float) * numberOfValues;
    outDataSize = DataHelper::align8(outDataSize); // Make sure the data is 16-byte aligned.
    
    uint8_t *out = new uint8_t[outDataSize];
    std::memset(out, 0, outDataSize); // zero out memory.
    
    be_float *values = reinterpret_cast<be_float *>(out);
    
    for(size_t i = 0; i < numberOfValues; i++) {
        values[i] = info.srcFile->get_float("/values/" + std::to_string(i));
    }
    
    return out;
}

uint8_t *BuildMisc::_build_track_ids(BuildInfo &info, size_t &outDataSize) {
    size_t numberOfIds = _info.srcFile->length_of_array("/ids");
    outDataSize = DataHelper::align4(numberOfIds);
    uint8_t *out = new uint8_t[outDataSize];
    std::memset(out, 0, outDataSize); // zero out memory.
    
    for(size_t i = 0; i < numberOfIds; i++) {
        std::string ptr = "/ids/" + std::to_string(i);
        if(info.srcFile->is_value_null(ptr)) {
             out[i] = 0xFF; // Marks the end of the list for some files.
             continue;
        }
        std::string levelBuildId = info.srcFile->get_string(ptr);
        out[i] = AssetsHelper::get_asset_index(_settings, "ASSET_LEVEL_HEADERS", levelBuildId);
    }
    
    return out;
}

uint8_t *BuildMisc::_build_magic_codes(BuildInfo &info, size_t &outDataSize) {
    size_t numberOfCheats = _info.srcFile->length_of_array("/cheats");
    
    // The first two bytes are the total number of cheats
    outDataSize = sizeof(be_int16_t);
    
    // Then comes the lookup table.
    outDataSize += (numberOfCheats) * sizeof(be_int16_t) * 2;
    
    size_t offsetToText = outDataSize;
    
    // First loop to figure out the total size and offsets.
    for(size_t i = 0; i < numberOfCheats; i++) {
        std::string cheatPtr = "/cheats/" + std::to_string(i);
        
        // +1 for null terminator
        size_t codeLen = _info.srcFile->length_of_string(cheatPtr + "/code") + 1;
        size_t descLen = _info.srcFile->length_of_string(cheatPtr + "/description") + 1;
        
        outDataSize += codeLen + descLen;
    }
    
    // Make sure cheats data is 16-byte aligned.
    outDataSize = DataHelper::align16(outDataSize);
    
    uint8_t *out = new uint8_t[outDataSize];
    std::memset(out, 0, outDataSize); // zero out memory.
    be_int16_t *cheatsTable = reinterpret_cast<be_int16_t *>(&out[0]);
    
    // Set number of cheats.
    cheatsTable[0] = numberOfCheats;
    
    CheatsTableEntry *entries = reinterpret_cast<CheatsTableEntry *>(&cheatsTable[1]);
    
    // Second loop to write the data for each cheat entry.
    for(size_t i = 0; i < numberOfCheats; i++) {
        std::string cheatPtr = "/cheats/" + std::to_string(i);
        std::string code = _info.srcFile->get_string(cheatPtr + "/code");
        std::string description = _info.srcFile->get_string(cheatPtr + "/description");
        
        entries[i].codeOffset = offsetToText;
        offsetToText += code.size() + 1; // +1 for null terminator
        entries[i].descOffset = offsetToText;
        offsetToText += description.size() + 1; // +1 for null terminator
        
        char *codeOut = reinterpret_cast<char *>(&out[entries[i].codeOffset]);
        char *descriptionOut = reinterpret_cast<char *>(&out[entries[i].descOffset]);
        
        // Copy strings to out.
        std::strcpy(codeOut, code.c_str());
        std::strcpy(descriptionOut, description.c_str());
    }
    
    if(_settings.debugBuildKeepUncompressed) {
        fs::path unencryptedCheatsPath = _settings.pathToBuild / "debug/cheats" / info.dstPath.filename();
        FileHelper::write_binary_file(out, outDataSize, unencryptedCheatsPath, true);
    }
    
    MiscHelper::process_cheats_encryption(out, outDataSize); // Encrypt the cheats data.
    
    return out;
}

uint8_t *BuildMisc::_build_title_screen_demos(BuildInfo &info, size_t &outDataSize) {
    size_t numberOfEntries = _info.srcFile->length_of_array("/entries");
    
    size_t entriesSize = ((numberOfEntries + 1) * 3);
    outDataSize = DataHelper::align8(entriesSize);
    
    uint8_t *out = new uint8_t[outDataSize];
    std::memset(out, 0, outDataSize); // zero out memory.
    
    TitleScreenDemos *demos = reinterpret_cast<TitleScreenDemos *>(out);
    
    for(size_t i = 0; i < numberOfEntries; i++) {
        std::string ptr = "/entries/" + std::to_string(i);
        std::string levelBuildId = _info.srcFile->get_string(ptr + "/level");
        demos[i].levelId = AssetsHelper::get_asset_index(_settings, "ASSET_LEVEL_HEADERS", levelBuildId);
        
        // Different default values for the title screen.
        int defaultNumberOfPlayers = 0;
        int defaultCutsceneId = 0;
        if(levelBuildId != "ASSET_LEVEL_TITLESCREENSEQUENCE") {
            defaultNumberOfPlayers = -2;
            defaultCutsceneId = 100;
        }
        demos[i].numberOfPlayers = _info.srcFile->get_int(ptr + "/number-of-players", defaultNumberOfPlayers);
        demos[i].cutsceneId = _info.srcFile->get_int(ptr + "/cutscene-id", defaultCutsceneId);
    }
    demos[numberOfEntries].levelId = 0xFF; // Mark end of data with 0xFF.
    
    return out;
}

void BuildMisc::_preload_c_context() {
    fs::path includeFolder = _settings.pathToRepo / "include/";
    
    // Load all enums from these files.
    fs::path enumPaths[] = {
        includeFolder / "enums.h"
    };
    
    for(fs::path &enumPath : enumPaths) {
        CEnumsHelper::load_enums_from_file(&_c_context, enumPath);
    }
}