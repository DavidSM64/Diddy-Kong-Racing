#include "extractLevelHeader.h"

#include <vector>
#include <string>

#include "helpers/debugHelper.h"
#include "helpers/assetsHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/stringHelper.h"
#include "helpers/c/cContext.h"

#include "fileTypes/levelHeader.hpp"

#include "extract/stats.h"

#include "text/dkrText.h"

using namespace DkrAssetsTool;

void extract_weather(WritableJsonFile &jsonFile, std::string ptr, LevelHeader_Weather &weather) {
    jsonFile.set_int(ptr + "/enable", weather.enable);
    jsonFile.set_int(ptr + "/type", weather.type);
    jsonFile.set_int(ptr + "/intensity", weather.intensity);
    jsonFile.set_int(ptr + "/opacity", weather.opacity);
    jsonFile.set_int(ptr + "/velocity/x", weather.velocity[0]);
    jsonFile.set_int(ptr + "/velocity/y", weather.velocity[1]);
    jsonFile.set_int(ptr + "/velocity/z", weather.velocity[2]);
}

void extract_ai_levels(WritableJsonFile &jsonFile, std::string ptr, LevelHeader_AiLevels &aiLevels) {
    jsonFile.set_int(ptr + "/base", aiLevels.baseAiLevel);
    jsonFile.set_int(ptr + "/silver-coins", aiLevels.silverCoinsAiLevel);
    jsonFile.set_int(ptr + "/completed", aiLevels.completedAiLevel);
    jsonFile.set_int(ptr + "/tracks-mode", aiLevels.tracksModeAiLevel);
    jsonFile.set_int(ptr + "/trophy-race", aiLevels.trophyRaceAiLevel);
}

void extract_fog(WritableJsonFile &jsonFile, std::string ptr, LevelHeader_Fog &fogInfo) {
    jsonFile.set_int(ptr + "/near", fogInfo.near);
    jsonFile.set_int(ptr + "/far", fogInfo.far);
    jsonFile.set_int(ptr + "/colour/red", fogInfo.colour[0]);
    jsonFile.set_int(ptr + "/colour/green", fogInfo.colour[1]);
    jsonFile.set_int(ptr + "/colour/blue", fogInfo.colour[2]);
}

void extract_name(ExtractInfo &info, WritableJsonFile &jsonFile, std::string ptr) {
    ExtractInfo &levelNameExtract = DeferredExtractions::get_extraction("ASSET_LEVEL_NAMES", info.get_file_index());
    
    // TODO: Use BytesView instead of std::vector
    std::vector<uint8_t> rawBytes;
    levelNameExtract.get_data_from_rom(rawBytes);
    
    CEnum *languages = info.get_c_context().get_enum("Language");
    
    size_t numLanguages = languages->get_member_count();
    
    size_t curOffset = 0;
    
    for(size_t i = 0; i < numLanguages; i++) {
        std::string lang;
        DebugHelper::assert(languages->get_symbol_of_value(i, lang), 
            "(extract_name) Index ", i, " is out of range.");
            
        // TODO: If a language (other than English) uses the same name as English, then don't bother exporting it.
        
        // Get the current language name.
        // curOffset = StringHelper::get_ascii_from_data(rawBytes, curOffset, levelNameInLang);
        DKRText levelNameText(rawBytes, curOffset);
        curOffset += levelNameText.bytes_size() + 1; // +1 because the null-terminator was not included.
        
        jsonFile.set_string(ptr + "/" + lang, levelNameText.get_text());
    }
}

template<typename T>
void extract_enum_bitfield(ExtractInfo &info, WritableJsonFile &jsonFile, std::string ptr, std::string enumName, T value) {
    size_t numBits = sizeof(T) * 8;
    
    CContext &cContext = info.get_c_context();
    
    size_t count = 0;
    for(size_t i = 0; i < numBits; i++) {
        size_t bitFlag = 1 << i;
        if((value & bitFlag) == 0) { // Make sure the bit is set.
            continue;
        }
        
        std::string enumSymbol = cContext.get_symbol_of_enum_int(enumName, i);
        
        jsonFile.set_string(ptr + "/" + std::to_string(count), enumSymbol);
        
        count++;
    }
}

void ExtractLevelHeader::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Level Header", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    const ExtractStats &stats = info.get_stats();
    
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
    LevelHeader *header = reinterpret_cast<LevelHeader *>(&rawBytes[0]);
    
    CContext &cContext = info.get_c_context();
    
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_string("/type", "LevelHeader");
    
    // Name
    extract_name(info, jsonFile, "/name");
    
    // World ID
    std::string worldId = cContext.get_symbol_of_enum_int("World", header->world);
    jsonFile.set_string("/world", worldId);
    
    // Course Height
    jsonFile.set_float("/course-height", header->courseHeight);
    
    // Track ID
    std::string levelModelId = stats.get_build_id_from_file_index("ASSET_LEVEL_MODELS", header->geometry);
    jsonFile.set_string("/model", levelModelId);
    
    // Object Maps
    std::string collectablesMap = stats.get_build_id_from_file_index("ASSET_LEVEL_OBJECT_MAPS", header->collectablesObjMap);
    std::string objMap2 = stats.get_build_id_from_file_index("ASSET_LEVEL_OBJECT_MAPS", header->objectMap2);
    
    jsonFile.set_string("/map-collectables", collectablesMap);
    jsonFile.set_string("/map-2", objMap2);
    
    // Other
    jsonFile.set_int_if_not_zero("/max-velocity", header->velocityCap);
    jsonFile.set_int("/fov", header->cameraFOV);
    jsonFile.set_int_if_not_value("/lap-count", header->laps, 3);
    
    // Pulsing light data
    be_int32_t pulsatingLightsOffset = header->pulseLightData; 
    if(pulsatingLightsOffset != -1) {
        std::string pulseId = stats.get_build_id_from_file_index("ASSET_MISC", pulsatingLightsOffset);
        jsonFile.set_string("/pulsating-lights", pulseId);
    }
    
    // Race Type
    std::string raceTypeId = cContext.get_symbol_of_enum_int("RaceType", header->raceType);
    jsonFile.set_string("/race-type", raceTypeId);
    
    // Audio related
    jsonFile.set_int("/music", header->music);
    jsonFile.set_int("/instruments", header->instruments);
    
    // Misc assets
    for(size_t i = 0; i < 7; i++) {
        if(header->miscAssets[i] == -1)  {
            continue;
        }
        
        std::string miscAssetId = stats.get_build_id_from_file_index("ASSET_MISC", header->miscAssets[i]);
        
        jsonFile.set_string("/misc-assets/" + std::to_string(i), miscAssetId);
    }
    
    // Vehicle info
    std::string defaultVehicle = cContext.get_symbol_of_enum_int("Vehicle", header->vehicle);
    jsonFile.set_string("/default-vehicle", defaultVehicle);
    extract_enum_bitfield<int8_t>(info, jsonFile, "/avaliable-vehicles", "Vehicle", header->avaliableVehicles);
    
    // AI levels
    extract_ai_levels(jsonFile, "/ai-levels/adv1", header->adv1AiLevels);
    extract_ai_levels(jsonFile, "/ai-levels/adv2", header->adv2AiLevels);
    
    // Weather
    extract_weather(jsonFile, "/weather", header->weather);
    
    // Fog
    extract_fog(jsonFile, "/fog", header->fog);
    
    // Background related stuff
    if(header->skybox >= 0) {
        std::string skyboxObjId = stats.get_build_id_from_file_index("ASSET_OBJECTS", header->skybox);
        jsonFile.set_string("/background/skybox/id", skyboxObjId);
    }
    if(header->specialSky != 0) {
        jsonFile.set_int("/background/skybox/special-sky", header->specialSky);
        jsonFile.set_int("/background/skybox/special-sky-texture", header->specialSkyTexture);
    }
    jsonFile.set_int("/background/colour/red", header->bgColour[0]);
    jsonFile.set_int("/background/colour/green", header->bgColour[1]);
    jsonFile.set_int("/background/colour/blue", header->bgColour[2]);
    jsonFile.set_int("/background/multiplayer/gradient-colour/bottom/red", header->bgColourBottom[0]);
    jsonFile.set_int("/background/multiplayer/gradient-colour/bottom/green", header->bgColourBottom[1]);
    jsonFile.set_int("/background/multiplayer/gradient-colour/bottom/blue", header->bgColourBottom[2]);
    jsonFile.set_int("/background/multiplayer/gradient-colour/top/red", header->bgColourTop[0]);
    jsonFile.set_int("/background/multiplayer/gradient-colour/top/green", header->bgColourTop[1]);
    jsonFile.set_int("/background/multiplayer/gradient-colour/top/blue", header->bgColourTop[2]);
    
    // Unknowns
    jsonFile.set_int("/unknown/unk1", header->unk1);
    jsonFile.set_int("/unknown/unk2", header->unk2);
    jsonFile.set_int("/unknown/unk3", header->unk3);
    
    for(size_t i = 0; i < 4; i++) {
        jsonFile.set_int("/unknown/unk4/" + std::to_string(i), header->unk4[i]);
    }
    
    for(size_t i = 0; i < 10; i++) {
        jsonFile.set_int("/unknown/unkC/" + std::to_string(i), header->unkC[i]);
    }
    
    for(size_t i = 0; i < 10; i++) {
        jsonFile.set_int("/unknown/unk16/" + std::to_string(i), header->unk16[i]);
    }
    
    jsonFile.set_int("/unknown/unk2A", header->unk2A);
    
    for(size_t i = 0; i < 9; i++) {
        jsonFile.set_int("/unknown/unk2B/" + std::to_string(i), header->unk2B[i]);
    }
    
    for(size_t i = 0; i < 5; i++) {
        jsonFile.set_int("/unknown/unk44/" + std::to_string(i), header->unk44[i]);
    }
    
    for(size_t i = 0; i < 3; i++) {
        jsonFile.set_int("/unknown/unk4F/" + std::to_string(i), header->unk4F[i]);
    }
    
    jsonFile.set_int("/unknown/unk53", header->unk53);
    
    jsonFile.set_int("/waves/unk56", header->unk56);
    jsonFile.set_int("/waves/unk57", header->unk57);
    jsonFile.set_int("/waves/unk58", header->unk58);
    jsonFile.set_int("/waves/unk59", header->unk59);
    jsonFile.set_int("/waves/unk5A", header->unk5A);
    jsonFile.set_int("/waves/unk5C", header->unk5C);
    jsonFile.set_int("/waves/unk5D", header->unk5D);
    jsonFile.set_int("/waves/unk5E", header->unk5E);
    jsonFile.set_int("/waves/unk60", header->unk60);
    jsonFile.set_int("/waves/wave-power", header->wavePower);
    jsonFile.set_int("/waves/unk64", header->unk64);
    jsonFile.set_int("/waves/unk66", header->unk66);
    jsonFile.set_int("/waves/unk68", header->unk68);
    jsonFile.set_int("/waves/unk6A", header->unk6A);
    jsonFile.set_int("/waves/unk6B", header->unk6B);
    jsonFile.set_int("/waves/unk6C", header->unk6C);
    jsonFile.set_int("/waves/unk6D", header->unk6D);
    jsonFile.set_int("/waves/unk6E", header->unk6E);
    jsonFile.set_int("/waves/unk70", header->unk70);
    jsonFile.set_int("/waves/unk71", header->unk71);
    
    jsonFile.set_int("/unknown/unk72", header->unk72);
    jsonFile.set_int("/unknown/unk73", header->unk73);
    
    jsonFile.set_int("/unknown/unkA0", header->unkA0);
    jsonFile.set_int("/unknown/unkA2", header->unkA2);
    jsonFile.set_int("/unknown/unkA3", header->unkA3);
    
    jsonFile.set_int("/unknown/unkA8", header->unkA8);
    jsonFile.set_int("/unknown/unkAA", header->unkAA);
    
    jsonFile.set_int("/unknown/unkB0", header->unkB0);
    jsonFile.set_int("/unknown/unkB2", header->unkB2);
    jsonFile.set_int("/unknown/unkB3", header->unkB3);
    jsonFile.set_int("/unknown/unkB4", header->unkB4);
    jsonFile.set_int("/unknown/unkB5", header->unkB5);
    jsonFile.set_int("/unknown/unkB6", header->unkB6);
    jsonFile.set_int("/unknown/unkB7", header->unkB7);
    std::string bossRaceID = cContext.get_symbol_of_enum_int("BossSetupTypes", header->bossRaceID);
    jsonFile.set_string("/boss-race-id", bossRaceID);
    jsonFile.set_int("/unknown/unkB9", header->unkB9);
    jsonFile.set_int("/unknown/unkBC", header->unkBC);
    jsonFile.set_int("/unknown/unkBD", header->unkBD);
    jsonFile.set_int("/unknown/unkC4", header->unkC4);
    
    info.write_json_file();
}
