#include "extractSprite.h"

using namespace DkrAssetsTool;

#include "fileTypes/sprite.hpp"

#include "helpers/jsonHelper.h"
#include "helpers/assetsHelper.h"

ExtractSprite::ExtractSprite(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Sprite", YELLOW_TEXT, _outFilepath);
    
    WritableJsonFile jsonFile(_outFilepath);
    
    std::vector<uint8_t> rawBytes;
    _info.get_data_from_rom(rawBytes);
    
    SpriteHeader *spriteHeader = reinterpret_cast<SpriteHeader *>(&rawBytes[0]);
    
    std::string texBuildId = AssetsHelper::get_build_id_of_index(_settings, "ASSET_TEXTURES_2D", spriteHeader->startTextureIndex);
    
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
    
    jsonFile.save();
}

ExtractSprite::~ExtractSprite() {
}
