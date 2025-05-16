#include "buildTTGhost.h"

#include <cmath> // for std::round

#include "fileTypes/ttGhost.hpp"
#include "helpers/assetsHelper.h"
#include "helpers/dataHelper.h"
#include "helpers/c/cContext.h"

using namespace DkrAssetsTool;

void BuildTTGhost::build(BuildInfo &info) {
    if(info.build_to_file()) {
        // Make sure the enums in "/include/enums.h" are loaded.
        info.load_enums_into_c_context({ "enums.h" });
    }
    
    const JsonFile &jsonFile = info.get_src_json_file();
    
    size_t numberOfNodes = jsonFile.length_of_array("/nodes");
    
    size_t outSize = sizeof(GhostHeader) + (sizeof(GhostNode) * numberOfNodes);
    
    // Ghost Data must be 16-byte aligned.
    outSize = DataHelper::align16(outSize);
    
    info.out.resize(outSize);
    
    GhostHeader *ghostHeader = reinterpret_cast<GhostHeader *>(&info.out[0]);
    GhostNode *ghostNodes = reinterpret_cast<GhostNode *>(&info.out[sizeof(GhostHeader)]);
    
    std::string level = jsonFile.get_string("/header/level");
    ghostHeader->levelId = AssetsHelper::get_asset_index("ASSET_LEVEL_HEADERS", level);
    
    CContext &cContext = info.get_c_context();
    std::string vehicle = jsonFile.get_string("/header/vehicle");
    ghostHeader->vehicleId = cContext.get_int_value_of_symbol(vehicle);
    
    // Default character ID is 9 if not specified.
    ghostHeader->characterId = jsonFile.get_int("/header/character", 0x09);
    
    ghostHeader->time = std::round(jsonFile.get_float("/header/time") * GHOST_TIME_FPS);
    
    ghostHeader->nodeCount = numberOfNodes;
    
    for(size_t i = 0; i < numberOfNodes; i++) {
        std::string ptr = "/nodes/" + std::to_string(i);
        ghostNodes[i].x = jsonFile.get_int(ptr + "/x");
        ghostNodes[i].y = jsonFile.get_int(ptr + "/y");
        ghostNodes[i].z = jsonFile.get_int(ptr + "/z");
        ghostNodes[i].zRotation = jsonFile.get_int(ptr + "/rz");
        ghostNodes[i].xRotation = jsonFile.get_int(ptr + "/rx");
        ghostNodes[i].yRotation = jsonFile.get_int(ptr + "/ry");
    }
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}
