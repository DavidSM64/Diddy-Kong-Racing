#include "buildSprite.h"

#include "fileTypes/sprite.hpp"
#include "helpers/dataHelper.h"
#include "helpers/assetsHelper.h"

using namespace DkrAssetsTool;

void BuildSprite::build(BuildInfo &info) {
    const JsonFile &jsonFile = info.get_src_json_file();
    size_t numberOfTextures = jsonFile.length_of_array("/frame-tex-count");
    
    size_t outSize = sizeof(SpriteHeader) + numberOfTextures + 1;
    outSize = DataHelper::align16(outSize);
    
    info.out.resize(outSize);
    
    SpriteHeader *spriteHeader = reinterpret_cast<SpriteHeader *>(&info.out[0]);
    
    std::string texBuildId = jsonFile.get_string("/start-texture");
    DebugHelper::assert_(!texBuildId.empty(), 
        "(BuildSprite::build) [/start-texture] was not defined!");
    
    spriteHeader->startTextureIndex = AssetsHelper::get_asset_index("ASSET_TEXTURES_2D", texBuildId);
    spriteHeader->unk4 = jsonFile.get_int("/unk4");
    spriteHeader->unk6 = jsonFile.get_int("/unk6");
    spriteHeader->unk8 = 0; // Set in-game, always zero in ROM.
    spriteHeader->numberOfFrames = numberOfTextures;
    
    std::string frameTexCountPtr = "/frame-tex-count";
    uint8_t *data = &info.out[sizeof(SpriteHeader)];
    
    uint8_t output = 0;
    for(size_t i = 0; i < numberOfTextures + 1; i++) {
        data[i] = output;
        output += jsonFile.get_int(frameTexCountPtr + "/" + std::to_string(i));
    }
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}
