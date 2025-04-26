#include "buildLevelHeader.h"

using namespace DkrAssetsTool;

#include "helpers/assetsHelper.h"

#include "fileTypes/levelHeader.hpp"

#include <cstring> // for strncpy

void build_weather(BuildInfo &info, std::string ptr, LevelHeader_Weather &weather) {
    weather.enable      = info.srcFile->get_int(ptr + "/enable");
    weather.type        = info.srcFile->get_int(ptr + "/type");
    weather.intensity   = info.srcFile->get_int(ptr + "/intensity");
    weather.opacity     = info.srcFile->get_int(ptr + "/opacity");
    weather.velocity[0] = info.srcFile->get_int(ptr + "/velocity/x");
    weather.velocity[1] = info.srcFile->get_int(ptr + "/velocity/y");
    weather.velocity[2] = info.srcFile->get_int(ptr + "/velocity/z");
}

void build_ai_levels(BuildInfo &info, std::string ptr, LevelHeader_AiLevels &aiLevels) {
    aiLevels.baseAiLevel        = info.srcFile->get_int(ptr + "/base");
    aiLevels.silverCoinsAiLevel = info.srcFile->get_int(ptr + "/silver-coins");
    aiLevels.completedAiLevel   = info.srcFile->get_int(ptr + "/completed");
    aiLevels.tracksModeAiLevel  = info.srcFile->get_int(ptr + "/tracks-mode");
    aiLevels.trophyRaceAiLevel  = info.srcFile->get_int(ptr + "/trophy-race");
}

void build_fog(BuildInfo &info, std::string ptr, LevelHeader_Fog &fogInfo) {
    fogInfo.near      = info.srcFile->get_int(ptr + "/near");
    fogInfo.far       = info.srcFile->get_int(ptr + "/far");
    fogInfo.colour[0] = info.srcFile->get_int(ptr + "/colour/red");
    fogInfo.colour[1] = info.srcFile->get_int(ptr + "/colour/green");
    fogInfo.colour[2] = info.srcFile->get_int(ptr + "/colour/blue");
}

template<typename T>
T build_enum_bitfield(BuildInfo &info, std::string ptr) {
    const CContext &cContext = info.get_c_context();
    
    T out = 0;
    
    size_t numValues = info.srcFile->length_of_array(ptr);
    
    for(size_t i = 0; i < numValues; i++) {
        std::string enumSym = info.srcFile->get_string(ptr + "/" + std::to_string(i));
        out |= 1 << cContext.get_int_value_of_symbol(enumSym);
    }
    
    return out;
}

void build_level_name(BuildInfo &info) {
    DeferredAssetInfo deferInfo = AssetsHelper::get_deferred_asset_info("ASSET_LEVEL_NAMES");
    
    const CContext &cContext = info.get_c_context();
    CEnum *langEnum = cContext.get_enum("Language");
    
    size_t numLanguages = langEnum->get_member_count();
    
    std::vector<uint8_t> out;
    
    // TODO: Use the English name as the default, instead of an empty string.
    
    for(size_t i = 0; i < numLanguages; i++) {
        std::string langName;
        langEnum->get_symbol_of_value(i, langName);
        
        std::string levelLangName = info.srcFile->get_string("/name/" + langName);
        
        size_t langNameSize = levelLangName.size();
        size_t offset = out.size();
        out.resize(offset + langNameSize + 1); // Resize out to fit new string.
        char *outLangName = reinterpret_cast<char *>(&out[offset]);
        strncpy(outLangName, levelLangName.c_str(), langNameSize);
    }
    
    fs::path outPath = info.dstPath.parent_path() / deferInfo.outputPath / info.dstPath.filename();
    
    if(info.build_to_file()) {
        FileHelper::write_binary_file(out, outPath, true);
    } else {
        // TODO
    }
}

void BuildLevelHeader::build(BuildInfo &info) {
    // Make sure the enums in "/include/enums.h" are loaded.
    info.load_enums_into_c_context({ "enums.h" });
    
    build_level_name(info);
    
    const CContext &cContext = info.get_c_context();
    
    info.out.resize(sizeof(LevelHeader));
    LevelHeader *header = reinterpret_cast<LevelHeader*>(&info.out[0]);
    
    // World ID
    std::string worldId = info.srcFile->get_string("/world");
    header->world = cContext.get_int_value_of_symbol(worldId);
    
    // Course Height
    header->courseHeight = info.srcFile->get_float("/course-height");
    
    // Track ID
    std::string trackId = info.srcFile->get_string("/model");
    header->geometry = AssetsHelper::get_asset_index("ASSET_LEVEL_MODELS", trackId);
    
    // Object Maps
    std::string collectableMapId = info.srcFile->get_string("/map-collectables");
    std::string objMap2Id = info.srcFile->get_string("/map-2");
    header->collectablesObjMap = AssetsHelper::get_asset_index("ASSET_LEVEL_OBJECT_MAPS", collectableMapId);
    header->objectMap2 = AssetsHelper::get_asset_index("ASSET_LEVEL_OBJECT_MAPS", objMap2Id);
    
    // Other
    header->velocityCap = info.srcFile->get_int("/max-velocity", 0);
    header->cameraFOV = info.srcFile->get_int("/fov", 60);
    header->laps = info.srcFile->get_int("/lap-count", 3);
    
    // Pulsing light data
    header->pulseLightData = -1; // Default value.
    std::string pulsatingLightId = info.srcFile->get_string("/pulsating-lights");
    if(!pulsatingLightId.empty()) {
       header->pulseLightData = AssetsHelper::get_asset_index("ASSET_MISC", pulsatingLightId);
    }
    
    // Race Type
    std::string raceTypeId = info.srcFile->get_string("/race-type");
    header->raceType = cContext.get_int_value_of_symbol(raceTypeId);
    
    // Audio related
    header->music = info.srcFile->get_int("/music");
    header->instruments = info.srcFile->get_int("/instruments");
    
    const size_t MAX_NUM_OF_MISC_ASSETS = 7;
    
    // Misc assets
    size_t numMiscAssets = 0;
    if(info.srcFile->has("/misc-assets")) {
        numMiscAssets = info.srcFile->length_of_array("/misc-assets");
        if(numMiscAssets > MAX_NUM_OF_MISC_ASSETS) {
            DebugHelper::warn("Level Headers are limited to 7 misc assets! You have ", numMiscAssets, ". Only setting the first 7.");
            numMiscAssets = MAX_NUM_OF_MISC_ASSETS;
        }
        for(size_t i = 0; i < numMiscAssets; i++) {
            std::string miscAssetId = info.srcFile->get_string("/misc-assets/" + std::to_string(i));
            header->miscAssets[i] = AssetsHelper::get_asset_index("ASSET_MISC", miscAssetId);
        }
    }
    
    // Fill the rest of the misc asset slots with -1
    for(size_t i = numMiscAssets; i < MAX_NUM_OF_MISC_ASSETS; i++) {
        header->miscAssets[i] = -1;
    }
    
    // Vehicle info
    std::string vehicle = info.srcFile->get_string("/default-vehicle", "VEHICLE_CAR");
    header->vehicle = cContext.get_int_value_of_symbol(vehicle);
    
    if(info.srcFile->has("/avaliable-vehicles")) {
        header->avaliableVehicles = build_enum_bitfield<int8_t>(info, "/avaliable-vehicles");
    }
    
    // AI levels
    build_ai_levels(info, "/ai-levels/adv1", header->adv1AiLevels);
    build_ai_levels(info, "/ai-levels/adv2", header->adv2AiLevels);
    
    // Weather
    build_weather(info, "/weather", header->weather);
    
    // Fog
    build_fog(info, "/fog", header->fog);
    
        
    // Background related stuff
    header->skybox = -1; // Default value
    header->specialSkyTexture = -1; // Default value
    if(info.srcFile->has("/background/skybox/id")) {
        std::string skyboxObjId = info.srcFile->get_string("/background/skybox/id");
        header->skybox = AssetsHelper::get_asset_index("ASSET_OBJECTS", skyboxObjId);
    } else if (info.srcFile->has("/background/skybox/special-sky")) { // Only used in wizpig 2
        header->specialSky        = info.srcFile->get_int("/background/skybox/special-sky");
        header->specialSkyTexture = info.srcFile->get_int("/background/skybox/special-sky-texture");
    }
    
    header->bgColour[0] = info.srcFile->get_int("/background/colour/red");
    header->bgColour[1] = info.srcFile->get_int("/background/colour/green");
    header->bgColour[2] = info.srcFile->get_int("/background/colour/blue");
    header->bgColourBottom[0] = info.srcFile->get_int("/background/multiplayer/gradient-colour/bottom/red");
    header->bgColourBottom[1] = info.srcFile->get_int("/background/multiplayer/gradient-colour/bottom/green");
    header->bgColourBottom[2] = info.srcFile->get_int("/background/multiplayer/gradient-colour/bottom/blue");
    header->bgColourTop[0] = info.srcFile->get_int("/background/multiplayer/gradient-colour/top/red");
    header->bgColourTop[1] = info.srcFile->get_int("/background/multiplayer/gradient-colour/top/green");
    header->bgColourTop[2] = info.srcFile->get_int("/background/multiplayer/gradient-colour/top/blue");
    
    // Unknowns
    header->unk1 = info.srcFile->get_int("/unknown/unk1");
    header->unk2 = info.srcFile->get_int("/unknown/unk2");
    header->unk3 = info.srcFile->get_int("/unknown/unk3");
    
    for(size_t i = 0; i < 4; i++) {
        header->unk4[i] = info.srcFile->get_int("/unknown/unk4/" + std::to_string(i));
    }
    
    for(size_t i = 0; i < 10; i++) {
        header->unkC[i] = info.srcFile->get_int("/unknown/unkC/" + std::to_string(i));
    }
    
    for(size_t i = 0; i < 10; i++) {
        header->unk16[i] = info.srcFile->get_int("/unknown/unk16/" + std::to_string(i));
    }
    
    header->unk2A = info.srcFile->get_int("/unknown/unk2A");
    
    for(size_t i = 0; i < 9; i++) {
        header->unk2B[i] = info.srcFile->get_int("/unknown/unk2B/" + std::to_string(i));
    }
    
    for(size_t i = 0; i < 5; i++) {
        header->unk44[i] = info.srcFile->get_int("/unknown/unk44/" + std::to_string(i));
    }
    
    for(size_t i = 0; i < 3; i++) {
        header->unk4F[i] = info.srcFile->get_int("/unknown/unk4F/" + std::to_string(i));
    }
    
    header->unk53 = info.srcFile->get_int("/unknown/unk53");
    
    header->unk56 = info.srcFile->get_int("/waves/unk56");
    header->unk57 = info.srcFile->get_int("/waves/unk57");
    header->unk58 = info.srcFile->get_int("/waves/unk58");
    header->unk59 = info.srcFile->get_int("/waves/unk59");
    header->unk5A = info.srcFile->get_int("/waves/unk5A");
    header->unk5C = info.srcFile->get_int("/waves/unk5C");
    header->unk5D = info.srcFile->get_int("/waves/unk5D");
    header->unk5E = info.srcFile->get_int("/waves/unk5E");
    header->unk60 = info.srcFile->get_int("/waves/unk60");
    header->wavePower = info.srcFile->get_int("/waves/wave-power");
    header->unk64 = info.srcFile->get_int("/waves/unk64");
    header->unk66 = info.srcFile->get_int("/waves/unk66");
    header->unk68 = info.srcFile->get_int("/waves/unk68");
    header->unk6A = info.srcFile->get_int("/waves/unk6A");
    header->unk6B = info.srcFile->get_int("/waves/unk6B");
    header->unk6C = info.srcFile->get_int("/waves/unk6C");
    header->unk6D = info.srcFile->get_int("/waves/unk6D");
    header->unk6E = info.srcFile->get_int("/waves/unk6E");
    header->unk70 = info.srcFile->get_int("/waves/unk70");
    header->unk71 = info.srcFile->get_int("/waves/unk71");
    header->unk72 = info.srcFile->get_int("/unknown/unk72");
    header->unk73 = info.srcFile->get_int("/unknown/unk73");
    
    header->unkA0 = info.srcFile->get_int("/unknown/unkA0");
    header->unkA2 = info.srcFile->get_int("/unknown/unkA2");
    header->unkA3 = info.srcFile->get_int("/unknown/unkA3");
    
    header->unkA8 = info.srcFile->get_int("/unknown/unkA8");
    header->unkAA = info.srcFile->get_int("/unknown/unkAA");
    
    header->unkB0 = info.srcFile->get_int("/unknown/unkB0");
    header->unkB2 = info.srcFile->get_int("/unknown/unkB2");
    header->unkB3 = info.srcFile->get_int("/unknown/unkB3");
    header->unkB4 = info.srcFile->get_int("/unknown/unkB4");
    header->unkB5 = info.srcFile->get_int("/unknown/unkB5");
    header->unkB6 = info.srcFile->get_int("/unknown/unkB6");
    header->unkB7 = info.srcFile->get_int("/unknown/unkB7");
    std::string bossRaceID = info.srcFile->get_string("/boss-race-id");
    header->bossRaceID = cContext.get_int_value_of_symbol(bossRaceID);
    header->unkB9 = info.srcFile->get_int("/unknown/unkB9");
    header->unkBC = info.srcFile->get_int("/unknown/unkBC");
    header->unkBD = info.srcFile->get_int("/unknown/unkBD");
    header->unkC4 = info.srcFile->get_int("/unknown/unkC4");
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}
