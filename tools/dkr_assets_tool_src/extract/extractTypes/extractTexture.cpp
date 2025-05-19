#include "extractTexture.h"

#include "helpers/debugHelper.h"
#include "helpers/fileHelper.h"
#include "helpers/jsonHelper.h"
#include "helpers/gzipHelper.h"

#include "fileTypes/texture.hpp"

#include "misc/globalSettings.h"

using namespace DkrAssetsTool;

// TODO: Refactor this to not use raw pointers.
std::vector<N64Image> generate_texture_images(std::vector<uint8_t> &texData, size_t numImages, bool shouldFlipTexture) {
    std::vector<N64Image> images;
    images.reserve(numImages);
    
    int curOffset = 0;
    for(size_t i = 0; i < numImages; i++) {
        TextureHeader *texHeader = reinterpret_cast<TextureHeader *>(&texData[curOffset]);
        std::string format = TEXTURE_FORMAT_INT_TO_STRING[texHeader->format & 0xF];
        
        images.emplace_back(texHeader->width, texHeader->height, format, true);
        
        uint8_t *texImage = &texData[curOffset] + sizeof(TextureHeader);
        
        size_t calcSize = ImageHelper::image_size(texHeader->width, texHeader->height, format);
        
        images[i].write_from(texImage, calcSize);
        
        // deinterlace the texture to make the .png image less jumbled up.
        if(texHeader->flags & 0x400) {
            images[i].interlace();
        }
        
        // Need to flip most 3d textures for convience. 
        if(shouldFlipTexture) {
            images[i].flip_vertically();
        }
        
        curOffset += texHeader->textureSize; // Move onto next texture.
    }
    
    return images;
}


void ExtractTexture::extract(ExtractInfo &info) {
    DebugHelper::info_custom("Extracting Texture", YELLOW_TEXT, info.get_out_filepath(".json"));
    
    bool flipTextureByDefault = info.get_from_config_section<bool>("/flip-textures-by-default", false);
    bool shouldFlipTexture = info.get_tag<bool>("flipTex", flipTextureByDefault);
    
    // TODO: Refactor this to use BytesView instead of a vector!
    std::vector<uint8_t> texHeaderBytes;
    std::vector<uint8_t> texData;
    
    info.get_data_from_rom(texHeaderBytes, 0, sizeof(TextureHeader));
    
    TextureHeader *texHeader = reinterpret_cast<TextureHeader *>(&texHeaderBytes[0]);
    
    size_t numImages = texHeader->numOfTextures;
    bool isCompressed = texHeader->isCompressed;
    
    if(isCompressed) {
        info.get_data_from_rom(texData, sizeof(TextureHeader));
        texData = GzipHelper::decompress_gzip(texData);
    } else {
        info.get_data_from_rom(texData);
    }
    
    if(GlobalSettings::get_value<bool>("/debug/keep-uncompressed", false)) {
        fs::path outUncompressedPath = GlobalSettings::get_decomp_path_to_vanilla_assets() / "debug/textures" / info.get_filename(".bin");
        FileHelper::write_binary_file(texData, outUncompressedPath, true);
    }
    
    std::vector<N64Image> images = generate_texture_images(texData, numImages, shouldFlipTexture);
    
    size_t renderMode = (texHeader->format >> 4) & 0xF;
    
    DebugHelper::assert(renderMode < TEXTURE_RENDER_MODES.size(), 
        "(ExtractTexture::extract) Invalid rendermode value: ", renderMode);
    
    WritableJsonFile &jsonFile = info.get_json_file();
    
    fs::path outFolder = GlobalSettings::get_decomp_path_to_vanilla_assets() / info.get_out_folder();
        
    if(numImages == 1) {
        fs::path imgPath = info.get_filename(".png");
        jsonFile.set_path("/images/0", imgPath);
        images[0].save(outFolder / imgPath);
        DebugHelper::assert_(FileHelper::path_exists(outFolder / imgPath), "(ExtractTexture::extract) Image ", imgPath, " did not save!");
    } else {
        std::string outImgFilename = info.get_filename();
        for(size_t i = 0; i < numImages; i++) {
            fs::path imgPath(outImgFilename + "_" + std::to_string(i) + ".png");
            jsonFile.set_path("/images/" + std::to_string(i), imgPath);
            images[i].save(outFolder / imgPath);
            DebugHelper::assert_(FileHelper::path_exists(outFolder / imgPath), "(ExtractTexture::extract) Image ", imgPath, " did not save!");
        }
    }
    
    jsonFile.set_string("/type", "Texture");
    jsonFile.set_string("/format", images[0].get_format());
    jsonFile.set_string("/render-mode", TEXTURE_RENDER_MODES[renderMode]);
    jsonFile.set_bool_if_true("/flipped-image", shouldFlipTexture);
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
    
    info.write_json_file();
}
