#include "buildLevelHeader.h"

using namespace DkrAssetsTool;

#include "helpers/assetsHelper.h"

#include <cstring> // for strncpy

BuildLevelHeader::BuildLevelHeader(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    _preload_c_context(); // For enums
    
    _build_level_name();
    
    LevelHeader *header = new LevelHeader();
    
    // World ID
    std::string worldId = _info.srcFile->get_string("/world");
    header->world = _c_context.get_int_value_of_symbol(worldId);
    
    // Course Height
    header->courseHeight = _info.srcFile->get_float("/course-height");
    
    // Track ID
    std::string trackId = _info.srcFile->get_string("/model");
    header->geometry = AssetsHelper::get_asset_index(_settings, "ASSET_LEVEL_MODELS", trackId);
    
    // Object Maps
    std::string collectableMapId = _info.srcFile->get_string("/map-collectables");
    std::string objMap2Id = _info.srcFile->get_string("/map-2");
    header->collectablesObjMap = AssetsHelper::get_asset_index(_settings, "ASSET_LEVEL_OBJECT_MAPS", collectableMapId);
    header->objectMap2 = AssetsHelper::get_asset_index(_settings, "ASSET_LEVEL_OBJECT_MAPS", objMap2Id);
    
    // Other
    header->velocityCap = _info.srcFile->get_int("/max-velocity", 0);
    header->cameraFOV = _info.srcFile->get_int("/fov", 60);
    header->laps = _info.srcFile->get_int("/lap-count", 3);
    
    // Pulsing light data
    header->pulseLightData = -1; // Default value.
    std::string pulsatingLightId = _info.srcFile->get_string("/pulsating-lights");
    if(!pulsatingLightId.empty()) {
       header->pulseLightData = AssetsHelper::get_asset_index(_settings, "ASSET_MISC", pulsatingLightId);
    }
    
    // Race Type
    std::string raceTypeId = _info.srcFile->get_string("/race-type");
    header->raceType = _c_context.get_int_value_of_symbol(raceTypeId);
    
    // Audio related
    header->music = _info.srcFile->get_int("/music");
    header->instruments = _info.srcFile->get_int("/instruments");
    
    const size_t MAX_NUM_OF_MISC_ASSETS = 7;
    
    // Misc assets
    size_t numMiscAssets = 0;
    if(_info.srcFile->has("/misc-assets")) {
        numMiscAssets = _info.srcFile->length_of_array("/misc-assets");
        if(numMiscAssets > MAX_NUM_OF_MISC_ASSETS) {
            DebugHelper::warn("Level Headers are limited to 7 misc assets! You have ", numMiscAssets, ". Only setting the first 7.");
            numMiscAssets = MAX_NUM_OF_MISC_ASSETS;
        }
        for(size_t i = 0; i < numMiscAssets; i++) {
            std::string miscAssetId = _info.srcFile->get_string("/misc-assets/" + std::to_string(i));
            header->miscAssets[i] = AssetsHelper::get_asset_index(_settings, "ASSET_MISC", miscAssetId);
        }
    }
    
    // Fill the rest of the misc asset slots with -1
    for(size_t i = numMiscAssets; i < MAX_NUM_OF_MISC_ASSETS; i++) {
        header->miscAssets[i] = -1;
    }
    
    // Vehicle info
    std::string vehicle = _info.srcFile->get_string("/default-vehicle", "VEHICLE_CAR");
    header->vehicle = _c_context.get_int_value_of_symbol(vehicle);
    
    if(_info.srcFile->has("/avaliable-vehicles")) {
        header->avaliableVehicles = _build_enum_bitfield<int8_t>("/avaliable-vehicles");
    }
    
    // AI levels
    _build_ai_levels("/ai-levels/adv1", header->adv1AiLevels);
    _build_ai_levels("/ai-levels/adv2", header->adv2AiLevels);
    
    // Weather
    _build_weather("/weather", header->weather);
    
    // Fog
    _build_fog("/fog", header->fog);
    
        
    // Background related stuff
    header->skybox = -1; // Default value
    header->specialSkyTexture = -1; // Default value
    if(_info.srcFile->has("/background/skybox/id")) {
        std::string skyboxObjId = _info.srcFile->get_string("/background/skybox/id");
        header->skybox = AssetsHelper::get_asset_index(_settings, "ASSET_OBJECTS", skyboxObjId);
    } else if (_info.srcFile->has("/background/skybox/special-sky")) { // Only used in wizpig 2
        header->specialSky        = _info.srcFile->get_int("/background/skybox/special-sky");
        header->specialSkyTexture = _info.srcFile->get_int("/background/skybox/special-sky-texture");
    }
    
    header->bgColour[0] = _info.srcFile->get_int("/background/colour/red");
    header->bgColour[1] = _info.srcFile->get_int("/background/colour/green");
    header->bgColour[2] = _info.srcFile->get_int("/background/colour/blue");
    header->bgColourBottom[0] = _info.srcFile->get_int("/background/multiplayer/gradient-colour/bottom/red");
    header->bgColourBottom[1] = _info.srcFile->get_int("/background/multiplayer/gradient-colour/bottom/green");
    header->bgColourBottom[2] = _info.srcFile->get_int("/background/multiplayer/gradient-colour/bottom/blue");
    header->bgColourTop[0] = _info.srcFile->get_int("/background/multiplayer/gradient-colour/top/red");
    header->bgColourTop[1] = _info.srcFile->get_int("/background/multiplayer/gradient-colour/top/green");
    header->bgColourTop[2] = _info.srcFile->get_int("/background/multiplayer/gradient-colour/top/blue");
    
    // Unknowns
    header->unk1 = _info.srcFile->get_int("/unknown/unk1");
    header->unk2 = _info.srcFile->get_int("/unknown/unk2");
    header->unk3 = _info.srcFile->get_int("/unknown/unk3");
    
    for(size_t i = 0; i < 4; i++) {
        header->unk4[i] = _info.srcFile->get_int("/unknown/unk4/" + std::to_string(i));
    }
    
    for(size_t i = 0; i < 10; i++) {
        header->unkC[i] = _info.srcFile->get_int("/unknown/unkC/" + std::to_string(i));
    }
    
    for(size_t i = 0; i < 10; i++) {
        header->unk16[i] = _info.srcFile->get_int("/unknown/unk16/" + std::to_string(i));
    }
    
    header->unk2A = _info.srcFile->get_int("/unknown/unk2A");
    
    for(size_t i = 0; i < 9; i++) {
        header->unk2B[i] = _info.srcFile->get_int("/unknown/unk2B/" + std::to_string(i));
    }
    
    for(size_t i = 0; i < 5; i++) {
        header->unk44[i] = _info.srcFile->get_int("/unknown/unk44/" + std::to_string(i));
    }
    
    for(size_t i = 0; i < 3; i++) {
        header->unk4F[i] = _info.srcFile->get_int("/unknown/unk4F/" + std::to_string(i));
    }
    
    header->unk53 = _info.srcFile->get_int("/unknown/unk53");
    
    header->unk56 = _info.srcFile->get_int("/waves/unk56");
    header->unk57 = _info.srcFile->get_int("/waves/unk57");
    header->unk58 = _info.srcFile->get_int("/waves/unk58");
    header->unk59 = _info.srcFile->get_int("/waves/unk59");
    header->unk5A = _info.srcFile->get_int("/waves/unk5A");
    header->unk5C = _info.srcFile->get_int("/waves/unk5C");
    header->unk5D = _info.srcFile->get_int("/waves/unk5D");
    header->unk5E = _info.srcFile->get_int("/waves/unk5E");
    header->unk60 = _info.srcFile->get_int("/waves/unk60");
    header->wavePower = _info.srcFile->get_int("/waves/wave-power");
    header->unk64 = _info.srcFile->get_int("/waves/unk64");
    header->unk66 = _info.srcFile->get_int("/waves/unk66");
    header->unk68 = _info.srcFile->get_int("/waves/unk68");
    header->unk6A = _info.srcFile->get_int("/waves/unk6A");
    header->unk6B = _info.srcFile->get_int("/waves/unk6B");
    header->unk6C = _info.srcFile->get_int("/waves/unk6C");
    header->unk6D = _info.srcFile->get_int("/waves/unk6D");
    header->unk6E = _info.srcFile->get_int("/waves/unk6E");
    header->unk70 = _info.srcFile->get_int("/waves/unk70");
    header->unk71 = _info.srcFile->get_int("/waves/unk71");
    header->unk72 = _info.srcFile->get_int("/unknown/unk72");
    header->unk73 = _info.srcFile->get_int("/unknown/unk73");
    
    header->unkA0 = _info.srcFile->get_int("/unknown/unkA0");
    header->unkA2 = _info.srcFile->get_int("/unknown/unkA2");
    header->unkA3 = _info.srcFile->get_int("/unknown/unkA3");
    
    header->unkA8 = _info.srcFile->get_int("/unknown/unkA8");
    header->unkAA = _info.srcFile->get_int("/unknown/unkAA");
    
    header->unkB0 = _info.srcFile->get_int("/unknown/unkB0");
    header->unkB2 = _info.srcFile->get_int("/unknown/unkB2");
    header->unkB3 = _info.srcFile->get_int("/unknown/unkB3");
    header->unkB4 = _info.srcFile->get_int("/unknown/unkB4");
    header->unkB5 = _info.srcFile->get_int("/unknown/unkB5");
    header->unkB6 = _info.srcFile->get_int("/unknown/unkB6");
    header->unkB7 = _info.srcFile->get_int("/unknown/unkB7");
    std::string bossRaceID = _info.srcFile->get_string("/boss-race-id");
    header->bossRaceID = _c_context.get_int_value_of_symbol(bossRaceID);
    header->unkB9 = _info.srcFile->get_int("/unknown/unkB9");
    header->unkBC = _info.srcFile->get_int("/unknown/unkBC");
    header->unkBD = _info.srcFile->get_int("/unknown/unkBD");
    header->unkC4 = _info.srcFile->get_int("/unknown/unkC4");
    
    FileHelper::write_binary_file(reinterpret_cast<uint8_t*>(header), sizeof(LevelHeader), 
        _info.dstPath, true);
}

BuildLevelHeader::~BuildLevelHeader() {
    
}

void BuildLevelHeader::_build_weather(std::string ptr, LevelHeader_Weather &weather) {
    weather.enable      = _info.srcFile->get_int(ptr + "/enable");
    weather.type        = _info.srcFile->get_int(ptr + "/type");
    weather.intensity   = _info.srcFile->get_int(ptr + "/intensity");
    weather.opacity     = _info.srcFile->get_int(ptr + "/opacity");
    weather.velocity[0] = _info.srcFile->get_int(ptr + "/velocity/x");
    weather.velocity[1] = _info.srcFile->get_int(ptr + "/velocity/y");
    weather.velocity[2] = _info.srcFile->get_int(ptr + "/velocity/z");
}

void BuildLevelHeader::_build_ai_levels(std::string ptr, LevelHeader_AiLevels &aiLevels) {
    aiLevels.baseAiLevel        = _info.srcFile->get_int(ptr + "/base");
    aiLevels.silverCoinsAiLevel = _info.srcFile->get_int(ptr + "/silver-coins");
    aiLevels.completedAiLevel   = _info.srcFile->get_int(ptr + "/completed");
    aiLevels.tracksModeAiLevel  = _info.srcFile->get_int(ptr + "/tracks-mode");
    aiLevels.trophyRaceAiLevel  = _info.srcFile->get_int(ptr + "/trophy-race");
}

void BuildLevelHeader::_build_fog(std::string ptr, LevelHeader_Fog &fogInfo) {
    fogInfo.near      = _info.srcFile->get_int(ptr + "/near");
    fogInfo.far       = _info.srcFile->get_int(ptr + "/far");
    fogInfo.colour[0] = _info.srcFile->get_int(ptr + "/colour/red");
    fogInfo.colour[1] = _info.srcFile->get_int(ptr + "/colour/green");
    fogInfo.colour[2] = _info.srcFile->get_int(ptr + "/colour/blue");
}

template<typename T>
T BuildLevelHeader::_build_enum_bitfield(std::string ptr) {
    T out = 0;
    
    size_t numValues = _info.srcFile->length_of_array(ptr);
    
    for(size_t i = 0; i < numValues; i++) {
        std::string enumSym = _info.srcFile->get_string(ptr + "/" + std::to_string(i));
        out |= 1 << _c_context.get_int_value_of_symbol(enumSym);
    }
    
    return out;
}

void BuildLevelHeader::_build_level_name() {
    DeferredAssetInfo deferInfo = AssetsHelper::get_deferred_asset_info(_settings, "ASSET_LEVEL_NAMES");
    
    CEnum *langEnum = _c_context.get_enum("Language");
    
    size_t numLanguages = langEnum->get_member_count();
    
    std::vector<uint8_t> out;
    
    // TODO: Use the English name as the default, instead of an empty string.
    
    for(size_t i = 0; i < numLanguages; i++) {
        std::string langName;
        langEnum->get_symbol_of_value(i, langName);
        
        std::string levelLangName = _info.srcFile->get_string("/name/" + langName);
        
        size_t langNameSize = levelLangName.size();
        size_t offset = out.size();
        out.resize(offset + langNameSize + 1); // Resize out to fit new string.
        char *outLangName = reinterpret_cast<char *>(&out[offset]);
        strncpy(outLangName, levelLangName.c_str(), langNameSize);
    }
    
    fs::path outPath = _info.dstPath.parent_path() / deferInfo.outputPath / _info.dstPath.filename();
    
    FileHelper::write_binary_file(out, outPath, true);
}

void BuildLevelHeader::_preload_c_context() {
    fs::path includeFolder = _settings.pathToRepo / "include/";
    
    // Load all enums from these files.
    fs::path enumPaths[] = {
        includeFolder / "enums.h"
    };
    
    for(fs::path &enumPath : enumPaths) {
        CEnumsHelper::load_enums_from_file(&_c_context, enumPath);
    }
}

