#include "buildTexture.h"

#include <cmath> // for std::round

#include "helpers/dataHelper.h"
#include "helpers/imageHelper.h"
#include "helpers/gzipHelper.h"
#include "fileTypes/texture.hpp"

using namespace DkrAssetsTool;

size_t calculate_out_size(BuildInfo &info) {
    int numberOfTextures = info.srcFile->length_of_array("/images");
    std::string format = info.srcFile->get_string_uppercase("/format", DEFAULT_TEXTURE_FORMAT);
    
    size_t sizeOfAllImages = 0;
    
    for(int i = 0; i < numberOfTextures; i++) {
        fs::path localImagePath = info.srcFile->get_string("/images/" + std::to_string(i));
        fs::path filepath = info.localDirectory / localImagePath;
        
        sizeOfAllImages += ImageHelper::image_size(filepath, format);
    }
    
    return (numberOfTextures * sizeof(TextureHeader)) + sizeOfAllImages;
}

void BuildTexture::build(BuildInfo &info) {
    info.out.resize(calculate_out_size(info));
    
    int numberOfTextures = info.srcFile->length_of_array("/images");
    std::string format = info.srcFile->get_string_uppercase("/format", DEFAULT_TEXTURE_FORMAT);
    
    bool isCompressed = info.srcFile->get_bool("/compressed");
    bool isFlipped = info.srcFile->get_bool("/flipped-image", false);
    int frameAdvanceDelay = std::round(info.srcFile->get_float("/frame-advance-delay", 0) * TEXTURE_FPS);
    std::string renderMode = info.srcFile->get_string("/render-mode", "OPAQUE");
    
    int spriteX = info.srcFile->get_int("/sprite-x", 0);
    int spriteY = info.srcFile->get_int("/sprite-y", 0);
    
    bool writeSize = info.srcFile->get_bool("/write-size");
    
    uint8_t formatVal = DataHelper::vector_index_of<std::string>(TEXTURE_FORMAT_INT_TO_STRING, format);
    uint8_t renderModeVal = DataHelper::vector_index_of<std::string>(TEXTURE_RENDER_MODES, renderMode);
    
    size_t currentOffset = 0;
    
    bool wrapSClamped = info.srcFile->get_string_lowercase("/flags/wrap-s", "wrap") == "clamp";
    bool wrapTClamped = info.srcFile->get_string_lowercase("/flags/wrap-t", "wrap") == "clamp";
    bool antiAliased = info.srcFile->get_bool("/flags/anti-aliased");
    bool semiTransparent = info.srcFile->get_bool("/flags/semi-transparent");
    bool cutout = info.srcFile->get_bool("/flags/cutout");
    bool interlaced = info.srcFile->get_bool("/flags/interlaced");
    
    // TODO: Make flags not hardcoded!
    be_int16_t flags = (
        ((int)antiAliased << 0) |
        ((int)semiTransparent << 2) |
        ((int)cutout << 4) |
        ((int)wrapSClamped << 6) |
        ((int)wrapTClamped << 7) |
        ((int)interlaced << 10)
    );
    
    for(int i = 0; i < numberOfTextures; i++) {
        TextureHeader *header = reinterpret_cast<TextureHeader *>(&info.out[currentOffset]);
        
        header->format = (renderModeVal << 4) | formatVal;
        header->spriteX = spriteX;
        header->spriteY = spriteY;
        header->numberOfInstances = 1;
        header->numOfTextures = numberOfTextures;
        header->frameAdvanceDelay = frameAdvanceDelay;
        header->flags = flags;
        
        currentOffset += sizeof(TextureHeader);
        uint8_t *textureData = &info.out[currentOffset];
        
        fs::path localImgPath = info.srcFile->get_string("/images/" + std::to_string(i));
        
        N64Image img(info.localDirectory / localImgPath, format);
        
        int imgWidth = img.get_width();
        int imgHeight = img.get_height();
        
        header->width = imgWidth;
        header->height = imgHeight;
        
        // TODO: Check if width and/or height is greater than 255, and error if it is!
        
        if(writeSize) {
            header->textureSize = DataHelper::align16(sizeof(TextureHeader) + ImageHelper::image_size(imgWidth, imgHeight, format));
        } else {
            // ???
            header->isCompressed = 1;
        }
        
        if(isFlipped) {
            img.flip_vertically();
        }
        
        if(interlaced) {
            img.interlace();
        }
        
        img.copy_to(textureData);
        
        currentOffset += img.size();
    }
    
    if(!writeSize) {
        // Make sure `out` is 16-byte aligned only for this specific case?
        while(info.out.size() % 16 != 0) {
            info.out.push_back(0);
        }
    }
    
    /*
    if(_settings.debugBuildKeepUncompressed) {
        // Have the uncompressed binary in a seperate directory in the build folder.
        fs::path outUncompressedPath = _settings.pathToBuild / "debug/textures" /  (info.dstPath.stem().string() + ".bin");
        FileHelper::write_binary_file(out, outUncompressedPath, true);
    }
    */
    
    if(isCompressed) {
        std::vector<uint8_t> compressedHeader;
        
        // Copy header from first texture into compressedHeader vector.
        compressedHeader.insert(compressedHeader.end(), info.out.begin(), info.out.begin() + sizeof(TextureHeader));
        
        TextureHeader *compressedTexHeader = reinterpret_cast<TextureHeader *>(&compressedHeader[0]);
        compressedTexHeader->isCompressed = 1; // Very important for this to be set for compressed textures!
        
        info.out = GzipHelper::compress_gzip(info.out);
        
        // Add the compressed header to the start of compressedOut
        info.out.insert(info.out.begin(), compressedHeader.begin(), compressedHeader.end());
    }
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}
