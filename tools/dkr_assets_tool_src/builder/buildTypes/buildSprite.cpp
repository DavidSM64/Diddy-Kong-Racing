#include "buildSprite.h"

using namespace DkrAssetsTool;

#include "fileTypes/sprite.hpp"
#include "helpers/dataHelper.h"
#include "helpers/assetsHelper.h"

BuildSprite::BuildSprite(DkrAssetsSettings &settings, BuildInfo &info) : _settings(settings), _info(info) {
    size_t numberOfTextures = _info.srcFile->length_of_array("/frame-tex-count");
    
    size_t outSize = sizeof(SpriteHeader) + numberOfTextures + 1;
    outSize = DataHelper::align16(outSize);
    
    std::vector<uint8_t> out(outSize);
    
    SpriteHeader *spriteHeader = reinterpret_cast<SpriteHeader *>(&out[0]);
    
    std::string texBuildId = _info.srcFile->get_string("/start-texture");
    DebugHelper::assert(!texBuildId.empty(), "(BuildSprite::BuildSprite) [/start-texture] was not defined!");
    
    spriteHeader->startTextureIndex = AssetsHelper::get_asset_index(_settings, "ASSET_TEXTURES_2D", texBuildId);
    spriteHeader->unk4 = _info.srcFile->get_int("/unk4");
    spriteHeader->unk6 = _info.srcFile->get_int("/unk6");
    spriteHeader->unk8 = 0; // Set in-game, always zero in ROM.
    spriteHeader->numberOfFrames = numberOfTextures;
    
    std::string frameTexCountPtr = "/frame-tex-count";
    uint8_t *data = &out[sizeof(SpriteHeader)];
    
    uint8_t output = 0;
    for(size_t i = 0; i < numberOfTextures + 1; i++) {
        data[i] = output;
        output += _info.srcFile->get_int(frameTexCountPtr + "/" + std::to_string(i));
    }
    
    FileHelper::write_binary_file(out, _info.dstPath, true);
}

BuildSprite::~BuildSprite() {
    
}

