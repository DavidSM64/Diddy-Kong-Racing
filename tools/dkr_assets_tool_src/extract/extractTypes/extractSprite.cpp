#include "extractSprite.h"

#include <optional>
#include <string>

#include "fileTypes/sprite.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/assetsHelper.h"

#include "extract/stats.h"

using namespace DkrAssetsTool;

void ExtractSprite::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Sprite", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    WritableJsonFile &jsonFile = info.get_json_file();
    
    std::vector<uint8_t> rawBytes;
    info.get_data_from_rom(rawBytes);
    
    SpriteHeader *spriteHeader = reinterpret_cast<SpriteHeader *>(&rawBytes[0]);
    
    
    std::string texBuildId = info.get_stats().get_build_id_from_file_index("ASSET_TEXTURES_2D", spriteHeader->startTextureIndex);
    
    jsonFile.set_string("/type", "Sprite");
    jsonFile.set_string("/start-texture", texBuildId);
    jsonFile.set_int("/unk4", spriteHeader->unk4);
    jsonFile.set_int("/unk6", spriteHeader->unk6);
    
    std::string frameTexCountPtr = "/frame-tex-count";
    
    uint8_t *data = &rawBytes[sizeof(SpriteHeader)]; 
    size_t numOfFrames = (size_t)spriteHeader->numberOfFrames;
    
    for(size_t i = 0; i < numOfFrames; i++) {
        jsonFile.set_int(frameTexCountPtr + "/" + std::to_string(i), data[i + 1] - data[i]);
    }
    
    info.write_json_file();
}
