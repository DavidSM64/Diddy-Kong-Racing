#include "extractTTGhost.h"

#include "fileTypes/ttGhost.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/assetsHelper.h"

#include "extract/stats.h"

using namespace DkrAssetsTool;

void ExtractTTGhost::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting TTGhost", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    const ExtractStats &stats = info.get_stats();
    
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
    GhostHeader *ghostHeader = reinterpret_cast<GhostHeader *>(&rawBytes[0]);
    
    WritableJsonFile &jsonFile = info.get_json_file();
    jsonFile.set_string("/type", "TTGhost");
    
    std::string levelBuildId = stats.get_build_id_from_file_index("ASSET_LEVEL_HEADERS", ghostHeader->levelId);
    
    std::string vehicle = info.get_c_context().get_symbol_of_enum_int("Vehicle", ghostHeader->vehicleId);
    
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
    
    info.write_json_file();
}
