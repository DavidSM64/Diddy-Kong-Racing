#include "extractTexture.h"

using namespace DkrAssetsTool;

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/gzipHelper.h"

#include "fileTypes/texture.hpp"

ExtractTexture::ExtractTexture(DkrAssetsSettings &settings, ExtractInfo &info) : _settings(settings), _info(info) {
    fs::path _outFilepath = _settings.pathToAssets / _info.get_out_filepath(".json");
    DebugHelper::info_custom("Extracting Texture", YELLOW_TEXT, _outFilepath);
    
    _shouldFlipTexture = _info.get_tag<bool>("flipTex", _info.assetSection->specific.textures.flipTexturesByDefault);
    
    std::vector<uint8_t> texHeaderBytes;
    std::vector<uint8_t> texData;
    
    info.rom->get_data(info.get_data_offset(), sizeof(TextureHeader), texHeaderBytes);
    
    TextureHeader *texHeader = reinterpret_cast<TextureHeader *>(&texHeaderBytes[0]);
    
    size_t numImages = texHeader->numOfTextures;
    bool isCompressed = (texHeader->isCompressed);
    
    if(isCompressed) {
        // Get compressed data. (sets texData)
        info.rom->get_data(info.get_data_offset() + sizeof(TextureHeader), info.get_data_size() - sizeof(TextureHeader), texData);
        // Decompress it.
        texData = GzipHelper::decompress_gzip(texData);
    } else {
        // Get data directly, since it isn't compressed. (sets texData)
        info.rom->get_data(info.get_data_offset(), info.get_data_size(), texData);
    }
    
    if(_settings.debugExtractKeepUncompressed) {
        // Have the uncompressed binary in a seperate directory in the assets folder.
        fs::path outUncompressedPath = _settings.pathToAssets / "debug/textures" / _info.get_filename(".bin");
        FileHelper::write_binary_file(texData, outUncompressedPath, true);
    }
    
    N64Image **images = _generate_texture_images(texData, numImages);
    
    size_t renderMode = (texHeader->format >> 4) & 0xF;
    
    DebugHelper::assert(renderMode < TEXTURE_RENDER_MODES.size(), "(ExtractTexture::ExtractTexture) Invalid rendermode value: ", renderMode);
    
    WritableJsonFile jsonFile(_outFilepath);
    
    fs::path outFolder = _settings.pathToAssets / _info.get_out_folder();
        
    if(numImages == 1) {
        fs::path imgPath = _info.get_filename(".png");
        jsonFile.set_path("/images/0", imgPath);
        images[0]->save(outFolder / imgPath);
        DebugHelper::assert(FileHelper::path_exists(outFolder / imgPath), "Image did not save!!!!");
    } else {
        std::string outImgFilename = _info.get_filename();
        for(size_t i = 0; i < numImages; i++) {
            fs::path imgPath(outImgFilename + "_" + std::to_string(i) + ".png");
            jsonFile.set_path("/images/" + std::to_string(i), imgPath);
            images[i]->save(outFolder / imgPath);
            DebugHelper::assert(FileHelper::path_exists(outFolder / imgPath), "Image did not save!!!!");
        }
    }
    
    jsonFile.set_string("/type", "Texture");
    jsonFile.set_string("/format", images[0]->get_format());
    jsonFile.set_string("/render-mode", TEXTURE_RENDER_MODES[renderMode]);
    jsonFile.set_bool_if_true("/flipped-image", _shouldFlipTexture);
    jsonFile.set_bool_if_true("/compressed", isCompressed);
    
    if(numImages > 1) {
        jsonFile.set_float("/frame-advance-delay", texHeader->frameAdvanceDelay / TEXTURE_FPS, TEXTURE_TIME_ROUND_PLACES);
    }
    
    // Write flags
    jsonFile.set_bool_if_true("/flags/anti-aliased", texHeader->flags & 0x1);
    jsonFile.set_bool_if_true("/flags/semi-transparent", texHeader->flags & 0x4);
    jsonFile.set_bool_if_true("/flags/cutout", texHeader->flags & 0x10);
    jsonFile.set_string("/flags/wrap-s", (texHeader->flags & 0x40) ? "Clamp" : "Wrap");
    jsonFile.set_string("/flags/wrap-t", (texHeader->flags & 0x80) ? "Clamp" : "Wrap");
    jsonFile.set_bool_if_true("/flags/interlaced", texHeader->flags & 0x400);
    
    if(texHeader->spriteX != 0 || texHeader->spriteY != 0) {
        jsonFile.set_int("/sprite-x", texHeader->spriteX);
        jsonFile.set_int("/sprite-y", texHeader->spriteY);
    }
    
    jsonFile.set_bool_if_true("/write-size", texHeader->textureSize != 0);
    
    jsonFile.save();
    
    // Cleanup
    delete images;
}

ExtractTexture::~ExtractTexture() {
}

N64Image **ExtractTexture::_generate_texture_images(std::vector<uint8_t> &texData, size_t numImages) {
    N64Image **images = new N64Image*[numImages];
    
    int curOffset = 0;
    for(size_t i = 0; i < numImages; i++) {
        TextureHeader *texHeader = reinterpret_cast<TextureHeader *>(&texData[curOffset]);
        std::string format = TEXTURE_FORMAT_INT_TO_STRING[texHeader->format & 0xF];
        
        images[i] = new N64Image(texHeader->width, texHeader->height, format, true);
        
        uint8_t *texImage = &texData[curOffset] + sizeof(TextureHeader);
        
        size_t calcSize = ImageHelper::image_size(texHeader->width, texHeader->height, format);
        
        images[i]->write_from(texImage, calcSize);
        
        // deinterlace the texture to make the .png image less jumbled up.
        if(texHeader->flags & 0x400) {
            images[i]->interlace();
        }
        
        // Need to flip most 3d textures for convience. 
        if(_shouldFlipTexture) {
            images[i]->flip_vertically();
        }
        
        curOffset += texHeader->textureSize; // Move onto next texture.
    }
    
    return images;
}
