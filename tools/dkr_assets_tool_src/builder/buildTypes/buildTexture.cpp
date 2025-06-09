#include "buildTexture.h"

#include <cmath>
#include <mutex>

#include "helpers/assetsHelper.h"
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
    BuildTextureCache &textureCache = info.get_texture_cache();
    const JsonFile &jsonFile = info.get_src_json_file();
    bool is3dTexture = info.get_section_build_id() == "ASSET_TEXTURES_3D";
    
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
    
    if(is3dTexture) {
        // Calculate sha1 of texture data, then add it to the texture cache. Need this so that we can reuse existing textures.
        std::string textureSha1 = DataHelper::make_sha1_hash_of_bytes(BytesView(info.out));
        textureCache.add_texture_to_sha1_cache(textureSha1, info.get_file_index());
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

std::mutex buildDeferredTexMutex;

size_t build_deferred_common(BuildInfo &baseInfo, std::vector<N64Image> &images, BuildTexture::DeferredTextureInfo &textureInfo) {
    std::vector<uint8_t> out(textureInfo.totalSize);
    
    
    bool wrapSClamped = textureInfo.wrapS == "clamp";
    bool wrapTClamped = textureInfo.wrapT == "clamp";
    
    size_t offset = 0;
    for(N64Image &img : images) {
        int imgWidth = img.get_width();
        int imgHeight = img.get_height();
        
        TextureHeader *header = reinterpret_cast<TextureHeader *>(&out[offset]);
        offset += sizeof(TextureHeader);
        uint8_t *textureData = &out[offset];
        
        uint8_t formatVal = DataHelper::vector_index_of<std::string>(TEXTURE_FORMAT_INT_TO_STRING, textureInfo.format);
        uint8_t renderModeVal = DataHelper::vector_index_of<std::string>(TEXTURE_RENDER_MODES, textureInfo.renderMode);
        
        header->width = imgWidth;
        header->height = imgHeight;
        header->format = (renderModeVal << 4) | formatVal;
        header->numberOfInstances = 1;
        header->numOfTextures = images.size();
        header->textureSize = DataHelper::align16(img.size() + sizeof(TextureHeader));
        
        if(header->numOfTextures > 1) {
            header->frameAdvanceDelay = textureInfo.frameAdvanceDelay;
        }
        
        int16_t flags = 0;
        
        if(wrapSClamped) {
            flags |= (1 << 6);
        }
        
        if(wrapTClamped) {
            flags |= (1 << 7);
        }
        
        if(textureInfo.shouldFlip) {
            img.flip_vertically();
        }
        
        if(!DataHelper::is_power_of_two(imgWidth)) {
            flags |= (1 << 10);
            img.interlace();
        }
        
        header->flags = flags;
        
        img.copy_to(textureData);
        offset += img.size();
    }
    
    // Need to check the texture cache to see if the texture already exists or not. 
    // Avoiding duplicate textures saves a lot of space in the ROM file.
    
    BuildTextureCache &textureCache = baseInfo.get_texture_cache();
    std::string textureSha1 = DataHelper::make_sha1_hash_of_bytes(BytesView(out));
    std::optional<int> foundTexIndex = textureCache.get_index_of_texture_hash(textureSha1);
    if(foundTexIndex.has_value()) {
        return foundTexIndex.value();
    }
    
    bool debugKeepUncompressed = GlobalSettings::get_value<bool>("/debug/keep-uncompressed", false);
    
    if(debugKeepUncompressed) {
        fs::path outUncompressedPath = GlobalSettings::get_decomp_path("build_subpath", "build/");
        outUncompressedPath /= "debug/custom-textures";
        outUncompressedPath /= textureInfo.buildId + ".bin";
        FileHelper::write_binary_file(out, outUncompressedPath, true);
    }
    
    size_t outIndex = baseInfo.get_collection().add_deferred_build_info("ASSET_TEXTURES_3D", textureInfo.buildId, baseInfo.get_build_id(), baseInfo.get_section_build_id(), out, 
        baseInfo.get_path_to_directory(), baseInfo.get_info_context());
        
    // Add the new texture to the cache.
    textureCache.add_texture_to_sha1_cache(textureSha1, outIndex);
    
    return outIndex;
}

size_t BuildTexture::build_deferred(BuildInfo &baseInfo, fs::path pathToImage, DeferredTextureInfo textureInfo) {
    if(textureInfo.format.empty() || textureInfo.renderMode.empty()) {
        ImageHelper::guess_texture_format_and_render_mode(pathToImage, textureInfo.format, textureInfo.renderMode);
    }
    
    std::vector<fs::path> texturePaths = ImageHelper::get_multiple_textures_from_one(pathToImage);
    
    DebugHelper::assert_(texturePaths.size() > 0, 
        "(BuildTexture::build_deferred) ImageHelper::get_multiple_textures_from_one() failed for ", pathToImage.filename());
    
    std::vector<N64Image> images;
    images.reserve(texturePaths.size());
    
    for(auto &path : texturePaths) {
        int width, height;
        ImageHelper::get_width_and_height(path, width, height);
        textureInfo.totalSize += DataHelper::align16(sizeof(TextureHeader) + ImageHelper::image_size(width, height, textureInfo.format));
        images.emplace_back(path, textureInfo.format, true);
    }
    
    DebugHelper::assert_(textureInfo.totalSize > 0, 
        "(BuildTexture::build_deferred) Could not calculate texture size for ", pathToImage.filename());
    
    if(texturePaths.size() > 1) {
        float animTexTiming = ImageHelper::guess_animated_texture_timing(pathToImage);
        textureInfo.frameAdvanceDelay = std::round(animTexTiming * TEXTURE_FPS);
    }
    
    if(textureInfo.wrapS.empty() || textureInfo.wrapT.empty()) {
        ImageHelper::guess_texture_wrap_mode(pathToImage, textureInfo.wrapS, textureInfo.wrapT);
    }
    
    textureInfo.buildId = baseInfo.get_build_id() + "_" + pathToImage.stem().generic_string();
    StringHelper::make_uppercase(textureInfo.buildId);
    
    return build_deferred_common(baseInfo, images, textureInfo);
}

size_t BuildTexture::build_deferred(BuildInfo &baseInfo, uint8_t *imgData, size_t imgDataLength, std::string mimeType, 
  std::string imgName, DeferredTextureInfo textureInfo) {
    DebugHelper::assert_(mimeType == "image/png", 
        "(BuildTexture::build_deferred) Only embedded .png files are supported! mimeType was \"", mimeType, "\"");
    
    int width, height;
    void *data = pngdata2rgba(imgData, (int)imgDataLength, &width, &height);
    
    DebugHelper::assert_(data != NULL, 
        "(BuildTexture::build_deferred) Failed to load color PNG data from ", imgName);
    
    if(textureInfo.format.empty() || textureInfo.renderMode.empty()) {
        ImageHelper::guess_texture_format_and_render_mode((rgba*)data, width, height, textureInfo.format, textureInfo.renderMode);
    }
    
    bool isColourImage = (textureInfo.format == "RGBA16") || (textureInfo.format == "RGBA32") || (textureInfo.format == "CI4") || (textureInfo.format == "CI8");
    
    if(!isColourImage) {
        // Free colour data, then load it as grayscale data instead.
        free(data); 
        data = pngdata2ia(imgData, (int)imgDataLength, &width, &height);
        DebugHelper::assert_(data != NULL, 
            "(BuildTexture::build_deferred) Failed to load grayscale PNG data from ", imgName);
    }
    
    // Embedded images are (currently) assumed to not be animated.
    std::vector<N64Image> images;
    images.reserve(1);
    
    textureInfo.totalSize = DataHelper::align16(sizeof(TextureHeader) + ImageHelper::image_size(width, height, textureInfo.format));
    
    images.emplace_back(data, width, height, textureInfo.format, true);
    
    free(data);
    
    textureInfo.buildId = baseInfo.get_build_id() + "_" + imgName;
    StringHelper::make_uppercase(textureInfo.buildId);
    
    return build_deferred_common(baseInfo, images, textureInfo);
}
