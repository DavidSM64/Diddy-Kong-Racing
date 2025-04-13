#include "buildTTGhost.h"

using namespace DkrAssetsTool;

#include <cmath> // for std::round

#include "fileTypes/ttGhost.hpp"
#include "helpers/assetsHelper.h"
#include "helpers/dataHelper.h"

BuildTTGhost::BuildTTGhost(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    _preload_c_context();
    
    size_t numberOfNodes = _info.srcFile->length_of_array("/nodes");
    
    size_t outSize = sizeof(GhostHeader) + (sizeof(GhostNode) * numberOfNodes);
    
    // Ghost Data must be 16-byte aligned.
    outSize = DataHelper::align16(outSize);
    
    std::vector<uint8_t> out(outSize);
    
    GhostHeader *ghostHeader = reinterpret_cast<GhostHeader *>(&out[0]);
    GhostNode *ghostNodes = reinterpret_cast<GhostNode *>(&out[sizeof(GhostHeader)]);
    
    std::string level = _info.srcFile->get_string("/header/level");
    ghostHeader->levelId = AssetsHelper::get_asset_index(_settings, "ASSET_LEVEL_HEADERS", level);
    
    std::string vehicle = _info.srcFile->get_string("/header/vehicle");
    ghostHeader->vehicleId = _c_context.get_int_value_of_symbol(vehicle);
    
    // Default character ID is 9 if not specified.
    ghostHeader->characterId = _info.srcFile->get_int("/header/character", 0x09);
    
    ghostHeader->time = std::round(_info.srcFile->get_float("/header/time") * GHOST_TIME_FPS);
    
    ghostHeader->nodeCount = numberOfNodes;
    
    for(size_t i = 0; i < numberOfNodes; i++) {
        std::string ptr = "/nodes/" + std::to_string(i);
        ghostNodes[i].x = _info.srcFile->get_int(ptr + "/x");
        ghostNodes[i].y = _info.srcFile->get_int(ptr + "/y");
        ghostNodes[i].z = _info.srcFile->get_int(ptr + "/z");
        ghostNodes[i].zRotation = _info.srcFile->get_int(ptr + "/rz");
        ghostNodes[i].xRotation = _info.srcFile->get_int(ptr + "/rx");
        ghostNodes[i].yRotation = _info.srcFile->get_int(ptr + "/ry");
    }
    
    FileHelper::write_binary_file(out, _info.dstPath, true);
}

BuildTTGhost::~BuildTTGhost() {
    
}

void BuildTTGhost::_preload_c_context() {
    fs::path includeFolder = _settings.pathToRepo / "include/";
    
    // Load all enums from these files.
    fs::path enumPaths[] = {
        includeFolder / "enums.h",
    };
    
    for(fs::path &enumPath : enumPaths) {
        CEnumsHelper::load_enums_from_file(&_c_context, enumPath);
    }
}
