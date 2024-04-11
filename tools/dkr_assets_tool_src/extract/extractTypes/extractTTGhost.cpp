#include "extractTTGhost.h"

#include "fileTypes/ttGhost.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/assetsHelper.h"

ExtractTTGhost::ExtractTTGhost(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting TTGhost", YELLOW_TEXT, _outFilepath);
    
    std::vector<uint8_t> rawBytes;
    _info.get_data_from_rom(rawBytes);
    
    GhostHeader *ghostHeader = reinterpret_cast<GhostHeader *>(&rawBytes[0]);
    
    WritableJsonFile jsonFile(_outFilepath);
    jsonFile.set_string("/type", "TTGhost");
    
    std::string levelBuildId = AssetsHelper::get_build_id_of_index(_settings, "ASSET_LEVEL_HEADERS", ghostHeader->levelId);
    
    std::string vehicle = _info.c_context->get_symbol_of_enum_int("Vehicle", ghostHeader->vehicleId);
    
    jsonFile.set_string("/header/level", levelBuildId);
    jsonFile.set_string("/header/vehicle", vehicle);
    
    // Default is assumed to be 9, since that seems to always be the case?
    // TODO: Make this a enum string?
    jsonFile.set_int_if_not_value("/header/character", ghostHeader->characterId, 9);
    
    jsonFile.set_float("/header/time", (double)ghostHeader->time / GHOST_TIME_FPS);
    
    size_t numberOfNodes = ghostHeader->nodeCount;
    
    GhostNode *ghostNodes = reinterpret_cast<GhostNode *>(&rawBytes[sizeof(GhostHeader)]);
    
    for(size_t i = 0; i < numberOfNodes; i++) {
        std::string ptr = "/nodes/" + std::to_string(i);
        
        jsonFile.set_int(ptr + "/x", ghostNodes[i].x);
        jsonFile.set_int(ptr + "/y", ghostNodes[i].y);
        jsonFile.set_int(ptr + "/z", ghostNodes[i].z);
        jsonFile.set_int(ptr + "/rz", ghostNodes[i].zRotation);
        jsonFile.set_int(ptr + "/rx", ghostNodes[i].xRotation);
        jsonFile.set_int(ptr + "/ry", ghostNodes[i].yRotation);
    }
    
    jsonFile.save();
}

ExtractTTGhost::~ExtractTTGhost() {
}
