#include "buildTexture.h"

#include <cmath> // for std::round

#include "helpers/dataHelper.h"
#include "helpers/imageHelper.h"
#include "helpers/gzipHelper.h"
#include "fileTypes/texture.hpp"

#include "misc/globalSettings.h"

#include "libs/bytes_view.hpp"

#include "builder/buildInfoCollection.h"

using namespace DkrAssetsTool;

size_t calculate_out_size(BuildInfo &info, const JsonFile &jsonFile) {
    int numberOfTextures = jsonFile.length_of_array("/images");
    std::string format = jsonFile.get_string_uppercase("/format", DEFAULT_TEXTURE_FORMAT);
    
    size_t sizeOfAllImages = 0;
    
    for(int i = 0; i < numberOfTextures; i++) {
        fs::path localImagePath = jsonFile.get_string("/images/" + std::to_string(i));
        fs::path filepath = info.get_path_to_directory() / localImagePath;
        
        sizeOfAllImages += ImageHelper::image_size(filepath, format);
    }
    
    return (numberOfTextures * sizeof(TextureHeader)) + sizeOfAllImages;
}

void BuildTexture::build(BuildInfo &info) {
    const JsonFile &jsonFile = info.get_src_json_file();
    
    info.out.resize(calculate_out_size(info, jsonFile));
    
    int numberOfTextures = jsonFile.length_of_array("/images");
    std::string format = jsonFile.get_string_uppercase("/format", DEFAULT_TEXTURE_FORMAT);
    
    bool isCompressed = jsonFile.get_bool("/compressed");
    bool isFlipped = jsonFile.get_bool("/flipped-image", false);
    int frameAdvanceDelay = std::round(jsonFile.get_float("/frame-advance-delay", 0) * TEXTURE_FPS);
    std::string renderMode = jsonFile.get_string("/render-mode", "OPAQUE");
    
    int spriteX = jsonFile.get_int("/sprite-x", 0);
    int spriteY = jsonFile.get_int("/sprite-y", 0);
    
    bool writeSize = jsonFile.get_bool("/write-size");
    
    uint8_t formatVal = DataHelper::vector_index_of<std::string>(TEXTURE_FORMAT_INT_TO_STRING, format);
    uint8_t renderModeVal = DataHelper::vector_index_of<std::string>(TEXTURE_RENDER_MODES, renderMode);
    
    size_t currentOffset = 0;
    
    bool wrapSClamped = jsonFile.get_string_lowercase("/flags/wrap-s", "wrap") == "clamp";
    bool wrapTClamped = jsonFile.get_string_lowercase("/flags/wrap-t", "wrap") == "clamp";
    bool antiAliased = jsonFile.get_bool("/flags/anti-aliased");
    bool semiTransparent = jsonFile.get_bool("/flags/semi-transparent");
    bool cutout = jsonFile.get_bool("/flags/cutout");
    bool interlaced = jsonFile.get_bool("/flags/interlaced");
    
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
        
        fs::path localImgPath = jsonFile.get_string("/images/" + std::to_string(i));
        
        N64Image img(info.get_path_to_directory() / localImgPath, format);
        
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
    
    bool debugKeepUncompressed = GlobalSettings::get_value<bool>("/debug/keep-uncompressed", false);
    
    if(debugKeepUncompressed) {
        fs::path outUncompressedPath = GlobalSettings::get_decomp_path("build_subpath", "build/");
        outUncompressedPath /= "debug/textures";
        outUncompressedPath /= info.get_src_json_file().get_filepath().filename().replace_extension(".bin");
        FileHelper::write_binary_file(info.out, outUncompressedPath, true);
    }
    
    if(isCompressed) {
        std::vector<uint8_t> compressedHeader;
        
        // Copy header from first texture into compressedHeader vector.
        compressedHeader.insert(compressedHeader.end(), info.out.begin(), info.out.begin() + sizeof(TextureHeader));
        
        TextureHeader *compressedTexHeader = reinterpret_cast<TextureHeader *>(&compressedHeader[0]);
        compressedTexHeader->isCompressed = 1; // Very important for this to be set for compressed textures!
        
        info.out = GzipHelper::compress_gzip(info.out);
        
        // Add the compressed header to the start of info.out.
        info.out.insert(info.out.begin(), compressedHeader.begin(), compressedHeader.end());
    }
    
    if(info.build_to_file()) {
        info.write_out_to_dstPath();
    }
}

size_t BuildTexture::build_deferred(BuildInfo &baseInfo, fs::path pathToImage) {
    std::string format = "RGBA16";
    std::string renderMode = "OPAQUE";
    
    N64Image img(pathToImage, format);
    
    int imgWidth = img.get_width();
    int imgHeight = img.get_height();
    
    std::vector<uint8_t> out(sizeof(TextureHeader) + ImageHelper::image_size(imgWidth, imgHeight, format));
    
    TextureHeader *header = reinterpret_cast<TextureHeader *>(&out[0]);
    uint8_t *textureData = &out[sizeof(TextureHeader)];
    
    uint8_t formatVal = DataHelper::vector_index_of<std::string>(TEXTURE_FORMAT_INT_TO_STRING, format);
    uint8_t renderModeVal = DataHelper::vector_index_of<std::string>(TEXTURE_RENDER_MODES, renderMode);
    
    header->width = imgWidth;
    header->height = imgHeight;
    header->format = (renderModeVal << 4) | formatVal;
    header->numberOfInstances = 1;
    header->numOfTextures = 1;
    header->textureSize = DataHelper::align16(out.size());
    
    be_int16_t flags = (
        ((int)1 << 10) |
        ((int)1 << 6) |
        ((int)1 << 7)
    );
    
    header->flags = flags;
    
    img.flip_vertically();
    img.interlace();
    img.copy_to(textureData);
    
    BuildInfoCollection &collection = baseInfo.get_collection();
    
    std::string buildId = baseInfo.get_build_id() + "_" + pathToImage.stem().generic_string();
    StringHelper::make_uppercase(buildId);
    
    bool debugKeepUncompressed = GlobalSettings::get_value<bool>("/debug/keep-uncompressed", false);
    
    if(debugKeepUncompressed) {
        fs::path outUncompressedPath = GlobalSettings::get_decomp_path("build_subpath", "build/");
        outUncompressedPath /= "debug/custom-textures";
        outUncompressedPath /= buildId + ".bin";
        FileHelper::write_binary_file(out, outUncompressedPath, true);
    }
    
    return collection.add_deferred_build_info("ASSET_TEXTURES_3D", buildId, out, baseInfo.get_path_to_directory(), baseInfo.get_info_context());
}
